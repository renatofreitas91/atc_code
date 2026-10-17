#!/usr/bin/env python3
"""Regress complex arguments, nonzero small components and exact power axes."""
import argparse
import cmath
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import uuid


CASES = [
    ('sqrt(3+4i)', 2+1j), ('sqrt(3-4i)', 2-1j),
    ('sqrt(_3+4i)', 1+2j), ('sqrt(_3-4i)', 1-2j),
    ('sqrt(0)', 0j), ('sqrt(_1)', 1j), ('sqrt(_1E-30)', 1e-15j),
    ('cbrt(2+11i)', 2+1j), ('ln(3+4i)', cmath.log(3+4j)),
    ('log(3+4i)', cmath.log10(3+4j)), ('rtD2D(3+4i)', 2+1j),
    ('1+1E-15i', 1+1e-15j), ('1-1E-15i', 1-1e-15j),
    ('1E-15+i', 1e-15+1j), ('_1E-15+i', -1e-15+1j),
    ('1+1E-30i', 1+1e-30j), ('1E-30+i', 1e-30+1j),
    ('(1E-15i)+(2E-15i)', 3e-15j), ('(1E-15i)-(1E-15i)', 0j),
    ('i^2', -1+0j), ('i^4', 1+0j), ('(1+i)^2', 2j),
    ('(_1)^0.5+0i', 1j), ('(_2)^3+0i', -8+0j),
]


def clean_output(raw):
    text = raw.decode('utf-8', errors='replace').replace('\r', '')
    text = re.sub(r'\x1b\]0;.*?\x07', '', text)
    return re.sub(r'\x1b\[[0-?]*[ -/]*[@-~]', '', text)


def matches(value, expected):
    try:
        actual = complex(value.replace('i', 'j'))
    except (ValueError, AttributeError):
        return False
    # Check components independently: a large real part must not hide loss of
    # a tiny imaginary part. Exact zero expectations also detect axis residues.
    return all(a == 0 if b == 0 else abs(a-b) <= abs(b)*5e-6
               for a, b in ((actual.real, expected.real),
                            (actual.imag, expected.imag)))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--output-dir', type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    source = args.executable.resolve(strict=True)
    out = (args.output_dir or root/'work'/('complex-components-'+uuid.uuid4().hex)).resolve()
    out.mkdir(parents=True, exist_ok=False)
    report = {'binary_sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
              'runner_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              'expected_checks': 2*(len(CASES)+1), 'results': []}
    env = dict(os.environ)
    env.pop('ATC_DATA_DIR', None)
    for precision in ('0', '1'):
        data = out/('precision-'+precision)
        data.mkdir()
        shutil.copy2(source, data/source.name)
        fixtures = {'atc_path.txt': str(data), 'aboutDisabled.txt': '1',
                    'mode.txt': '1', 'higherPrecision.txt': precision,
                    'numSystems.txt': '0', 'siPrefixes.txt': '0',
                    'verboseResolution.txt': '0', 'actualTime.txt': '0'}
        for name, value in fixtures.items():
            (data/name).write_text(value, encoding='utf-8')
        for index in range(len(CASES)+1):
            (data/'variables.txt').write_text('')
            (data/'history.txt').write_text('')
            session = index == len(CASES)
            expression, expected = CASES[index] if not session else (
                'answer references', [1+1e-30j, 1+1e-30j, 1e-30+1j, 1e-30+1j])
            argv = [str(data/source.name)] + ([] if session else [expression])
            stdin = b'1+1E-30i\n#0\n1E-30+i\n#2\nexit\n' if session else b''
            code, stdout, stderr = 'TIMEOUT', b'', b''
            try:
                result = subprocess.run(argv, input=stdin, cwd=data, env=env,
                                        capture_output=True, timeout=30)
                code, stdout, stderr = result.returncode, result.stdout, result.stderr
            except subprocess.TimeoutExpired as error:
                stdout, stderr = error.stdout or b'', error.stderr or b''
            (data/(str(index)+'-stdout.log')).write_bytes(stdout)
            (data/(str(index)+'-stderr.log')).write_bytes(stderr)
            values = re.findall(r'#\d+=([^\n]+)', clean_output(stdout))
            targets = expected if session else [expected]
            history = (data/'history.txt').read_text(errors='replace')
            history_values = re.findall(r'#\d+=([^\r\n]+)', history)
            passed = code == 0 and len(values) == len(targets) and all(
                matches(value, target) for value, target in zip(values, targets))
            history_ok = len(history_values) == len(targets) and all(
                matches(value, target) for value, target in zip(history_values, targets))
            diagnostics = bool(re.search(r'ERROR: .*Sanitizer|runtime error:|'
                                         r'AddressSanitizer:DEADLYSIGNAL', stderr.decode(errors='replace')))
            row = {'precision': precision, 'expression': expression,
                   'expected': [str(v) for v in targets], 'obtained': values,
                   'history_values': history_values, 'history_matches': history_ok,
                   'exit_code': code, 'sanitizer_diagnostics': diagnostics,
                   'status': 'PASS' if passed and history_ok and not diagnostics else 'FAIL'}
            report['results'].append(row)
            report['passed'] = sum(r['status'] == 'PASS' for r in report['results'])
            (out/'results.json').write_text(json.dumps(report, indent=2)+'\n')
            print(row['status'], precision, expression, values, flush=True)
    print('RESULTS', out, flush=True)
    return int(report['passed'] != report['expected_checks'])


if __name__ == '__main__':
    raise SystemExit(main())
