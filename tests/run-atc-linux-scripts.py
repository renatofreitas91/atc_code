#!/usr/bin/env python3
"""Run the Windows-style dropped-TXT workflow with Linux path quoting."""
import argparse
import os
import shutil
import subprocess
import tempfile
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    args = parser.parse_args()
    executable = args.executable.resolve(strict=True)
    env = os.environ.copy()
    env['ATC_TEST_DISABLE_EXTERNAL_OPEN'] = '1'
    for form in ('single', 'double', 'plain', 'escaped', 'stdin', 'empty'):
        with tempfile.TemporaryDirectory(prefix='atc-drop-regression-') as directory:
            root = Path(directory)
            file = root / 'Example script.txt'
            file.write_text('' if form == 'empty' else '2+3\n')
            path = str(file)
            expression = {
                'single': "'" + path + "' ", 'double': '"' + path + '" ',
                'plain': path, 'escaped': path.replace(' ', '\\ '),
                'stdin': "'" + path + "' ", 'empty': "'" + path + "' ",
            }[form]
            command = [str(executable)] if form == 'stdin' else [str(executable), expression]
            result = subprocess.run(command, input=(expression + '\nexit\n').encode() if form == 'stdin' else b'',
                                    cwd=root, env=env, capture_output=True, timeout=30)
            answers = root / 'Example script_answers.txt'
            assert result.returncode == 0 and answers.exists() and (form == 'empty' or '#0=5' in answers.read_text()), (form, result.stdout, result.stderr)
            assert b'runtime error:' not in result.stderr, result.stderr
            print('PASS dropped TXT:', form, flush=True)
    with tempfile.TemporaryDirectory(prefix='atc-table-regression-') as directory:
        root = Path(directory)
        source = Path(__file__).resolve().parents[1] / 'Advanced Trigonometry Calculator/Scripts examples/Multiplication Table 1-100_script_generator.txt'
        file = root / source.name
        shutil.copy2(source, file)
        result = subprocess.run([str(executable), "'" + str(file) + "' "], cwd=root, env=env,
                                capture_output=True, timeout=30)
        output = result.stdout.decode(errors='replace')
        assert result.returncode == 0 and '1x1=1' in output and '100x10=1000' in output and '0x0=0' not in output, (output, result.stderr)
        assert b'runtime error:' not in result.stderr, result.stderr
        print('PASS actual multiplication-table script', flush=True)
    print('SUMMARY scripts=7 passed=7 failed=0')

if __name__ == '__main__':
    main()
