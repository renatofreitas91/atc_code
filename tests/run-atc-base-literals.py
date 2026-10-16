#!/usr/bin/env python3
"""Focused base-literal regressions, separate from the historical 376 checks."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import time
import uuid

CASES = [('B1010', '10'), ('O12', '10'), ('H10', '16'),
         ('B0', '0'), ('B1', '1'), ('O7', '7'), ('H9', '9'),
         ('HA', '10'), ('HF', '15'), ('HAF', '175'),
         ('H1A', '26'), ('H1E', '30'), ('H1E2', '482'),
         ('B10.1', '2.5'), ('O12.4', '10.5'), ('HA.8', '10.5'),
         ('B.1', '0.5'), ('O.4', '0.5'), ('H.8', '0.5'),
         ('_B1010', '-10'), ('_O12', '-10'), ('_H10', '-16'),
         ('B1010+O12+H10', '36'), ('2*B1010', '20'),
         ('(H10+O12)*2', '52'), ('B10^3', '8'),
         ('2(3+4)', '14'), ('2pi', '6.28319'),
         ('solver(sin(x)-sin(30+30i))', '30+30i')]


def values_equal(expression, expected, obtained):
    try:
        actual_number = complex(obtained.replace('i', 'j'))
        expected_number = complex(expected.replace('i', 'j'))
        return (abs(actual_number - expected_number) <= 0.00001
                if expression == '2pi' else actual_number == expected_number)
    except (ValueError, AttributeError):
        return False


def extra_fixtures(index, expression, precision):
    return {}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--output-dir', type=Path)
    args = parser.parse_args()
    source = args.executable.resolve()
    root = Path(__file__).resolve().parents[1]
    out = args.output_dir or root / 'work' / ('base-literals-' + uuid.uuid4().hex)
    out.mkdir(parents=True, exist_ok=False)
    source_hashes = {name: hashlib.sha256(
        (root / 'Advanced Trigonometry Calculator' / name).read_bytes()).hexdigest()
        for name in ('data_processing_core.cpp', 'processing_core.cpp',
                     'numerical_systems.cpp', 'main_aux_processor.cpp')}
    rows = []
    for precision in ('0', '1'):
        for index, (expression, expected) in enumerate(CASES):
            data = out / ('precision-' + precision) / str(index)
            data.mkdir(parents=True)
            executable = data / source.name
            shutil.copy2(source, executable)
            for asset in ('License.txt', 'About execution of application.txt'):
                shutil.copy2(root / 'Advanced Trigonometry Calculator' / asset, data / asset)
            for dirname in ('Strings', 'To solve', 'User functions'):
                (data / dirname).mkdir()
            fixtures = {'atc_path.txt': str(data.resolve()),
                        'onStart.txt': 'disableatcintro', 'aboutDisabled.txt': '1',
                        'higherPrecision.txt': precision, 'mode.txt': '2',
                        'numSystems.txt': '0', 'actualTime.txt': '0',
                        'siPrefixes.txt': '0', 'verboseResolution.txt': '0',
                        'variables.txt': ''}
            fixtures.update(extra_fixtures(index, expression, precision))
            for name, value in fixtures.items():
                (data / name).write_text(value, encoding='utf-8')
            started = time.monotonic()
            status = 'FAIL'
            with (data / 'stdout.log').open('wb') as stdout, (data / 'stderr.log').open('wb') as stderr:
                process = subprocess.Popen([str(executable.resolve()), expression], cwd=data,
                    stdin=subprocess.PIPE, stdout=stdout, stderr=stderr)
                try:
                    process.communicate(b'', timeout=20)
                except subprocess.TimeoutExpired:
                    status = 'TIMEOUT'
                    process.kill()
                    process.communicate()
            output = (data / 'stdout.log').read_bytes().decode('utf-8', errors='replace')
            match = re.search(r'^#\d+=([^\r\n]+)', output, re.M)
            value = match.group(1) if match else None
            if status != 'TIMEOUT':
                equal = values_equal(expression, expected, value)
                status = ('PASS' if process.returncode == 0 and equal else
                          'CRASH' if process.returncode < 0 or process.returncode > 255 else 'FAIL')
            rows.append({'expression': expression, 'expected': expected, 'obtained': value,
                         'status': status, 'exit_code': process.returncode,
                         'precision': precision, 'cwd': str(data), 'fixtures': fixtures,
                         'seconds': round(time.monotonic() - started, 3)})
            print(status, precision, expression, repr(value), flush=True)
            report = {'binary_sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
                      'source_files_sha256': source_hashes,
                      'results': rows, 'passed': sum(r['status'] == 'PASS' for r in rows),
                      'expected_checks': 2 * len(CASES)}
            (out / 'results.json').write_text(json.dumps(report, indent=2), encoding='utf-8')
    print('RESULTS', out, flush=True)
    return int(any(r['status'] != 'PASS' for r in rows))


if __name__ == '__main__':
    raise SystemExit(main())
