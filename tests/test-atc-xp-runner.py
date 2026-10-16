#!/usr/bin/env python3
"""Infrastructure checks for the native XP harness, also compatible with 3.4."""
from __future__ import print_function
import ctypes
from ctypes import wintypes
import io
import os
import runpy
import subprocess
import sys
import unittest
import uuid

HERE = os.path.dirname(os.path.abspath(__file__))
RUNNER = runpy.run_path(os.path.join(HERE, 'run-atc-xp.py'))


@unittest.skipUnless(os.name == 'nt', 'Windows Job Objects required')
class RunnerTests(unittest.TestCase):
    def setUp(self):
        self.root = os.path.join(HERE, '..', 'work', 'xp-harness-' + uuid.uuid4().hex[:8])
        os.makedirs(self.root)

    def execute(self, script, timeout=5, expected='READY'):
        event = {'id': 1, 'name': 'harness probe', 'cwd': self.root,
                 'arguments': subprocess.list2cmdline(['-c', script]),
                 'stdin': [], 'environment': {},
                 'assertions': [{'kind': 'output_regex', 'value': expected}]}
        return RUNNER['run_process'](event, sys.executable, self.root, self.root, timeout)

    def test_stdout_stderr_are_drained(self):
        result = self.execute("import sys; sys.stderr.write('E'*100000+'\\n'); print('READY')")
        self.assertEqual(result['status'], 'PASS', result)

    def test_wrong_expectation_fails(self):
        result = self.execute("print('WRONG')")
        self.assertEqual(result['status'], 'FAIL', result)

    def test_timeout_is_distinct(self):
        result = self.execute('import time; time.sleep(10)', timeout=0.2)
        self.assertEqual(result['status'], 'TIMEOUT', result)

    def test_crash_is_distinct(self):
        result = self.execute('import ctypes; ctypes.windll.kernel32.ExitProcess(0xC0000374)')
        self.assertEqual(result['status'], 'CRASH', result)
        self.assertEqual(result['exit_code_hex'], '0xC0000374')

    def test_descendant_is_terminated(self):
        script = ("import subprocess,sys; p=subprocess.Popen([sys.executable,'-c',"
                  "'import time; time.sleep(60)']); print('READY '+str(p.pid))")
        result = self.execute(script)
        self.assertEqual(result['status'], 'PASS', result)
        pid = int(result['output_tail'].split()[-1])
        kernel = ctypes.WinDLL('kernel32', use_last_error=True)
        kernel.OpenProcess.argtypes = [wintypes.DWORD, wintypes.BOOL, wintypes.DWORD]
        kernel.OpenProcess.restype = wintypes.HANDLE
        kernel.WaitForSingleObject.argtypes = [wintypes.HANDLE, wintypes.DWORD]
        kernel.CloseHandle.argtypes = [wintypes.HANDLE]
        handle = kernel.OpenProcess(0x100000, False, pid)
        if handle:
            try:
                self.assertEqual(kernel.WaitForSingleObject(handle, 5000), 0)
            finally:
                kernel.CloseHandle(handle)

    def test_fixture_escape_rejected(self):
        with self.assertRaises(ValueError):
            RUNNER['safe_child'](self.root, '..\\outside.txt')

    def test_legacy_path_limit_checked(self):
        catalog = {'events': [{'changes': [{'path': 'x' * 250}], 'assertions': []}]}
        with self.assertRaises(ValueError):
            RUNNER['validate_runtime_paths'](catalog, self.root)


if __name__ == '__main__':
    unittest.main(verbosity=2)
