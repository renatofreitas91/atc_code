#!/usr/bin/env python3
"""Portable infrastructure tests; these do not execute or validate ATC on Linux."""
import importlib.util
from pathlib import Path
import unittest
import uuid

spec = importlib.util.spec_from_file_location(
    'checkpoint_driver', Path(__file__).with_name('revalidate-atc-linux-checkpoint.py'))
driver = importlib.util.module_from_spec(spec)
spec.loader.exec_module(driver)


class DiagnosticTests(unittest.TestCase):
    def inspect(self, diagnostic='', output='PASS example\n', leak=True):
        # Keep fixtures in the workspace; avoid Python 3.14's private temporary
        # directory ACLs in restricted Windows execution environments.
        parent = Path(__file__).resolve().parents[1] / 'work'
        parent.mkdir(exist_ok=True)
        root = parent / ('driver-selftest-' + uuid.uuid4().hex)
        root.mkdir()
        try:
            log = root / 'suite.log'
            log.write_text(output, encoding='utf-8')
            directory = root / 'diagnostics'
            directory.mkdir()
            if diagnostic:
                (directory / 'sanitizer.123').write_text(diagnostic, encoding='utf-8')
            result = driver.inspect_sanitizers(log, directory, leak)
            if diagnostic:
                self.assertEqual(len(result['sanitizer_logs']), 1)
                self.assertEqual(len(result['sanitizer_logs'][0]['sha256']), 64)
            return result
        finally:
            for path in root.glob('diagnostics/*'):
                path.unlink()
            if (root / 'diagnostics').exists():
                (root / 'diagnostics').rmdir()
            if (root / 'suite.log').exists():
                (root / 'suite.log').unlink()
            root.rmdir()

    def test_verbose_success_is_not_a_failure(self):
        result = self.inspect('AddressSanitizer: failed to intercept x\n'
                              'LeakSanitizer: checking for leaks\nProcessing thread 123.\n')
        self.assertFalse(result['sanitizer_diagnostics_found'])
        self.assertFalse(result['sanitizer_infrastructure_error'])
        self.assertEqual(result['thread_inspections_observed'], 1)

    def test_separate_errors_are_not_hidden(self):
        for error in ('ERROR: AddressSanitizer: heap-buffer-overflow',
                      'ERROR: LeakSanitizer: detected memory leaks',
                      'runtime error: out of bounds', 'AddressSanitizer:DEADLYSIGNAL'):
            with self.subTest(error=error):
                self.assertTrue(self.inspect(error, leak=False)['sanitizer_diagnostics_found'])

    def test_stderr_fallback_is_scanned(self):
        self.assertTrue(self.inspect(output='runtime error: overflow', leak=False)
                        ['sanitizer_diagnostics_found'])

    def test_missing_lsan_evidence_is_infrastructure_error(self):
        self.assertTrue(self.inspect()['sanitizer_infrastructure_error'])

    def test_failed_thread_inspection_is_infrastructure_error(self):
        self.assertTrue(self.inspect('Failed to suspend threads')['sanitizer_infrastructure_error'])

    def test_silent_asan_success_needs_no_diagnostic_file(self):
        result = self.inspect(leak=False)
        self.assertFalse(result['sanitizer_diagnostics_found'])
        self.assertFalse(result['sanitizer_infrastructure_error'])


if __name__ == '__main__':
    unittest.main()
