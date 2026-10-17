#!/usr/bin/env python3
"""Check signed base output against an independent rational-number oracle."""
import argparse
from fractions import Fraction
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import uuid

CASES = [(s, s.replace('_', '-')) for s in
         ('0', '1', '2', '10', '12', '_1', '_2', '_12', '0.5', '_0.5', '1E3', '_1E3',
          '1E-3', '_1E-3', '1E8', '_1E8', '1E-8', '_1E-8')]
CASES += [('bp12bp_1', '-1'), ('bp12bp_2', '-2'), ('bp12bp_12', '-12'),
          ('dp12dp_1', '-1')]
BASES = {'binary': 2, 'octal': 8, 'hexadecimal': 16}


def base_fraction(text, base):
    negative = text.startswith('-')
    text = text.lstrip('+-')
    whole, dot, fractional = text.partition('.')
    value = Fraction(int(whole or '0', base))
    if dot and fractional:
        value += Fraction(int(fractional, base), base ** len(fractional))
    return -value if negative else value


def represented_value(text, base):
    mantissa, marker, exponent = text.partition('*10^')
    value = base_fraction(mantissa, base)
    if marker:
        power = base_fraction(exponent, base)
        if power.denominator != 1 or abs(power) > 10000:
            raise ValueError('Invalid or unbounded exponent: ' + exponent)
        value *= Fraction(base) ** int(power)
    return value


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--baseline', type=Path)
    parser.add_argument('--output-dir', type=Path)
    args = parser.parse_args()
    repo = Path(__file__).resolve().parents[1]
    source = args.executable.resolve()
    out = args.output_dir or repo / 'work' / ('signed-bases-' + uuid.uuid4().hex)
    out.mkdir(parents=True, exist_ok=False)
    binary_sha256 = hashlib.sha256(source.read_bytes()).hexdigest()
    baseline_sha256 = (hashlib.sha256(args.baseline.read_bytes()).hexdigest()
                       if args.baseline else None)
    rows = []
    for precision in ('0', '1'):
        for index, (expression, target) in enumerate(CASES):
            variants = [('current', source)]
            # Small positive numbers intentionally receive corrected negative
            # scientific exponents; they are not unchanged-output controls.
            # Scientific mantissas/exponents are deliberately corrected too;
            # only ordinary positive formatting must be byte-for-byte unchanged.
            unchanged_control = expression in ('0', '1', '2', '10', '12', '0.5')
            if args.baseline and unchanged_control:
                variants.append(('baseline', args.baseline.resolve()))
            outputs = {}
            return_codes = {}
            for variant, executable in variants:
                data = out / ('mp-' + precision) / str(index) / variant
                data.mkdir(parents=True)
                local_exe = data / executable.name
                shutil.copy2(executable, local_exe)
                for name in ('License.txt', 'About execution of application.txt'):
                    shutil.copy2(repo / 'Advanced Trigonometry Calculator' / name, data / name)
                for name in ('Strings', 'To solve', 'User functions'):
                    (data / name).mkdir()
                fixtures = {'atc_path.txt': str(data.resolve()), 'onStart.txt': 'disableatcintro',
                            'aboutDisabled.txt': '1', 'higherPrecision.txt': precision,
                            'mode.txt': '2', 'numSystems.txt': '1', 'siPrefixes.txt': '0',
                            'actualTime.txt': '0', 'verboseResolution.txt': '0', 'variables.txt': ''}
                for name, value in fixtures.items():
                    (data / name).write_text(value, encoding='utf-8')
                try:
                    with (data / 'stdout.log').open('wb') as stdout, (data / 'stderr.log').open('wb') as stderr:
                        process = subprocess.Popen([str(local_exe.resolve()), expression], cwd=data,
                            stdin=subprocess.PIPE, stdout=stdout, stderr=stderr)
                        try:
                            process.communicate(b'', timeout=20)
                            return_codes[variant] = process.returncode
                        except subprocess.TimeoutExpired:
                            process.kill()
                            process.communicate()
                            return_codes[variant] = 'TIMEOUT'
                        except BaseException:
                            process.kill()
                            process.communicate()
                            raise
                finally:
                    # Preserve logs/fixtures; the source binary and its hash identify this run.
                    local_exe.unlink()
                text = (data / 'stdout.log').read_bytes().decode('utf-8', errors='replace')
                outputs[variant] = dict(re.findall(r'In (binary|octal|hexadecimal)=([^\r\n]+)', text))
                if variant == 'current':
                    history = (data / 'history.txt').read_bytes().decode('utf-8', errors='replace') if (data / 'history.txt').exists() else ''
                    history_matches = all('In ' + name + '=' + value in history for name, value in outputs[variant].items())
            expected = Fraction(target)
            failures = []
            if any(code != 0 for code in return_codes.values()):
                failures.append('Nonzero exit or timeout: ' + repr(return_codes))
            for name, base in BASES.items():
                try:
                    value = represented_value(outputs['current'][name], base)
                    # Retain the legacy finite digit budget; exact dyadic and
                    # integer fixtures below require exact values, not tolerance.
                    exact = expected.denominator & (expected.denominator - 1) == 0
                    tolerance = 0 if exact else abs(expected) / 100000
                    if abs(value - expected) > tolerance:
                        failures.append(name + ': wrong mathematical value')
                    if expected < 0 and not outputs['current'][name].startswith('-'):
                        failures.append(name + ': missing negative sign')
                except (ValueError, KeyError, ZeroDivisionError) as error:
                    failures.append(name + ': ' + repr(error))
            if not history_matches:
                failures.append('Console/history mismatch')
            if 'baseline' in outputs and outputs['baseline'] != outputs['current']:
                failures.append('Positive control output changed')
            status = ('TIMEOUT' if 'TIMEOUT' in return_codes.values() else
                      'CRASH' if any(isinstance(code, int) and (code < 0 or code > 255)
                                     for code in return_codes.values()) else
                      'FAIL' if failures else 'PASS')
            row = {'expression': expression, 'precision': precision, 'expected': str(expected),
                   'outputs': outputs, 'exit_codes': return_codes, 'failures': failures,
                   'status': status}
            rows.append(row)
            report = {'binary_sha256': binary_sha256,
                      'baseline_sha256': baseline_sha256,
                      'results': rows, 'passed': sum(r['status'] == 'PASS' for r in rows),
                      'expected_checks': 2 * len(CASES)}
            (out / 'results.json').write_text(json.dumps(report, indent=2), encoding='utf-8')
            print(row['status'], precision, expression, outputs['current'], failures, flush=True)
    print('RESULTS', out, flush=True)
    return int(any(row['failures'] for row in rows))


if __name__ == '__main__':
    raise SystemExit(main())
