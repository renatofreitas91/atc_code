#!/usr/bin/env python3
"""Verify focused runners retain evidence but remove per-case executables."""
import contextlib
import importlib.util
import io
import json
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest import mock


class StorageTests(unittest.TestCase):
    def exercise(self, runner_name, outcome, baseline=False):
        spec = importlib.util.spec_from_file_location(
            'focused_runner', Path(__file__).with_name(runner_name))
        runner = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(runner)
        runner.CASES = [('1', '1')]
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            source = root/'atc'
            source.write_bytes(b'test executable')
            output = root/'results'
            commands = []

            class Process:
                returncode = 0

                def __init__(self, argv, **kwargs):
                    commands.append(argv)
                    self.assert_executable = Path(argv[0])
                    if not self.assert_executable.is_file():
                        raise AssertionError('Executable removed before launch')
                    if outcome == 'spawn-error':
                        raise OSError('simulated launch failure')
                    self.stdout = kwargs['stdout']
                    self.stderr = kwargs['stderr']
                    self.data = Path(kwargs['cwd'])

                def communicate(self, *args, **kwargs):
                    if outcome == 'interrupt' and kwargs.get('timeout'):
                        raise KeyboardInterrupt
                    if outcome == 'timeout' and kwargs.get('timeout'):
                        raise subprocess.TimeoutExpired(commands[-1], kwargs['timeout'])
                    text = '#0=1\nIn binary=1\nIn octal=1\nIn hexadecimal=1\n'
                    self.stdout.write(text.encode())
                    self.stderr.write(b'')
                    (self.data/'history.txt').write_text(text)

                def kill(self):
                    self.returncode = -9

            argv = [runner_name, str(source), '--output-dir', str(output)]
            if baseline:
                argv += ['--baseline', str(source)]
            with mock.patch('sys.argv', argv), mock.patch.object(
                    runner.subprocess, 'Popen', Process), contextlib.redirect_stdout(io.StringIO()):
                if outcome in ('spawn-error', 'interrupt'):
                    with self.assertRaises(OSError if outcome == 'spawn-error' else KeyboardInterrupt):
                        runner.main()
                else:
                    self.assertEqual(runner.main(), int(outcome == 'timeout'))
            self.assertEqual(source.read_bytes(), b'test executable')
            self.assertTrue(commands)
            self.assertFalse(list(output.rglob('atc')))
            self.assertTrue(list(output.rglob('stdout.log')))
            self.assertTrue(list(output.rglob('stderr.log')))
            if outcome not in ('spawn-error', 'interrupt'):
                report = json.loads((output/'results.json').read_text())
                self.assertEqual(report['expected_checks'], 2)
                self.assertEqual(len(report['results']), 2)
                self.assertEqual(report['passed'], 2 if outcome == 'success' else 0)

    def test_literal_success(self):
        self.exercise('run-atc-base-literals.py', 'success')

    def test_literal_timeout(self):
        self.exercise('run-atc-base-literals.py', 'timeout')

    def test_literal_launch_error(self):
        self.exercise('run-atc-base-literals.py', 'spawn-error')

    def test_literal_interrupt(self):
        self.exercise('run-atc-base-literals.py', 'interrupt')

    def test_signed_interrupt(self):
        self.exercise('run-atc-signed-bases.py', 'interrupt')

    def test_signed_success_with_baseline(self):
        self.exercise('run-atc-signed-bases.py', 'success', baseline=True)

    def test_signed_timeout(self):
        self.exercise('run-atc-signed-bases.py', 'timeout')

    def test_signed_launch_error(self):
        self.exercise('run-atc-signed-bases.py', 'spawn-error')


if __name__ == '__main__':
    unittest.main()
