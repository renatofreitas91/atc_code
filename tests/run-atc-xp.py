#!/usr/bin/env python3
"""Replay the approved Windows catalog with Python 3.4 and standard libraries.

No PowerShell is required on the target. The exporter records harness fixture
changes, not executable-produced state. Expected values come from the original
regression assertions. Every invocation creates and preserves a new runtime.
"""
from __future__ import print_function

import argparse
import base64
import collections
import ctypes
from ctypes import wintypes
import hashlib
import io
import json
import math
import os
import platform
import re
import shutil
import struct
import subprocess
import sys
import threading
import time
import traceback
import uuid


def sha256(path):
    digest = hashlib.sha256()
    with open(path, 'rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            digest.update(block)
    return digest.hexdigest()


def save_json(path, value):
    with io.open(path, 'w', encoding='utf-8') as stream:
        stream.write(json.dumps(value, indent=2, ensure_ascii=True))
        stream.write(u'\n')


def expand(text, data):
    return text.replace('@DATA_REGEX@', re.escape(data)).replace('@DATA@', data)


def normalized(text):
    return text.replace('\r', '').strip()


def safe_child(root, relative):
    result = os.path.abspath(os.path.join(root, relative))
    if not result.lower().startswith(os.path.abspath(root).lower() + os.sep):
        raise ValueError('Fixture path escapes runtime: ' + relative)
    return result


def read_text(path):
    if not os.path.isfile(path):
        return ''
    with io.open(path, 'r', encoding='cp1252', errors='replace') as stream:
        return normalized(stream.read())


class Job(object):
    """XP-compatible job handle; closing it kills only assigned descendants."""
    def __init__(self):
        class BasicLimits(ctypes.Structure):
            _fields_ = [('ProcessTime', ctypes.c_longlong),
                       ('JobTime', ctypes.c_longlong), ('Flags', wintypes.DWORD),
                       ('MinimumWorkingSet', ctypes.c_size_t),
                       ('MaximumWorkingSet', ctypes.c_size_t),
                       ('ActiveProcessLimit', wintypes.DWORD),
                       ('Affinity', ctypes.c_size_t), ('Priority', wintypes.DWORD),
                       ('SchedulingClass', wintypes.DWORD)]

        class IoCounters(ctypes.Structure):
            _fields_ = [(name, ctypes.c_ulonglong) for name in
                        ('ReadOperations', 'WriteOperations', 'OtherOperations',
                         'ReadBytes', 'WriteBytes', 'OtherBytes')]

        class ExtendedLimits(ctypes.Structure):
            _fields_ = [('Basic', BasicLimits), ('Io', IoCounters),
                       ('ProcessMemoryLimit', ctypes.c_size_t),
                       ('JobMemoryLimit', ctypes.c_size_t),
                       ('PeakProcessMemory', ctypes.c_size_t),
                       ('PeakJobMemory', ctypes.c_size_t)]

        self.kernel = ctypes.WinDLL('kernel32', use_last_error=True)
        self.kernel.CreateJobObjectW.argtypes = [ctypes.c_void_p, wintypes.LPCWSTR]
        self.kernel.CreateJobObjectW.restype = wintypes.HANDLE
        self.kernel.SetInformationJobObject.argtypes = [wintypes.HANDLE,
                                                       ctypes.c_int,
                                                       ctypes.c_void_p,
                                                       wintypes.DWORD]
        self.kernel.SetInformationJobObject.restype = wintypes.BOOL
        self.kernel.AssignProcessToJobObject.argtypes = [wintypes.HANDLE,
                                                         wintypes.HANDLE]
        self.kernel.AssignProcessToJobObject.restype = wintypes.BOOL
        self.kernel.CloseHandle.argtypes = [wintypes.HANDLE]
        self.kernel.CloseHandle.restype = wintypes.BOOL
        self.handle = self.kernel.CreateJobObjectW(None, None)
        if not self.handle:
            raise ctypes.WinError(ctypes.get_last_error())
        limits = ExtendedLimits()
        limits.Basic.Flags = 0x2000  # JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE
        if not self.kernel.SetInformationJobObject(self.handle, 9,
                                                   ctypes.byref(limits),
                                                   ctypes.sizeof(limits)):
            error = ctypes.WinError(ctypes.get_last_error())
            self.close()
            raise error

    def assign(self, process):
        if not self.kernel.AssignProcessToJobObject(self.handle,
                                                    int(process._handle)):
            raise ctypes.WinError(ctypes.get_last_error())

    def close(self):
        if self.handle:
            handle, self.handle = self.handle, None
            if not self.kernel.CloseHandle(handle):
                raise ctypes.WinError(ctypes.get_last_error())


class Capture(threading.Thread):
    """Drain continuously, retain the official 200-line tail and bounded logs."""
    def __init__(self, source, path):
        threading.Thread.__init__(self)
        self.daemon = True
        self.source = source
        self.path = path
        self.lines = collections.deque(maxlen=200)
        self.pending = b''
        self.written = 0
        self.error = None
        self.truncated = False

    def append(self, line):
        line = line.rstrip(b'\r')
        if len(line) > 4096:
            line = line[:4096] + b'...[line truncated]'
        self.lines.append(line.decode('cp1252', 'replace'))

    def run(self):
        try:
            with open(self.path, 'wb') as log:
                while True:
                    block = self.source.read(4096)
                    if not block:
                        break
                    room = max(0, 16 * 1024 * 1024 - self.written)
                    log.write(block[:room])
                    self.written += min(len(block), room)
                    self.truncated = self.truncated or len(block) > room
                    pieces = (self.pending + block).split(b'\n')
                    for line in pieces[:-1]:
                        self.append(line)
                    self.pending = pieces[-1]
                    # Preserve a bounded prefix until the next newline.
                    if len(self.pending) > 8192:
                        self.pending = self.pending[:8192]
                if self.pending:
                    self.append(self.pending)
        except Exception:
            self.error = traceback.format_exc()
        finally:
            self.source.close()

    def text(self):
        return '\n'.join(self.lines)


def apply_changes(event, data, capture_root):
    for change in event.get('changes', []):
        path = safe_child(data, change['path'])
        if change.get('directory'):
            if not os.path.isdir(path):
                os.makedirs(path)
        elif change.get('delete'):
            if os.path.isfile(path):
                os.remove(path)
            elif os.path.exists(path):
                os.rmdir(path)  # Only an empty harness-owned fixture directory.
        else:
            parent = os.path.dirname(path)
            if not os.path.isdir(parent):
                os.makedirs(parent)
            content = base64.b64decode(change['base64'])
            content = content.replace(capture_root.encode('cp1252'),
                                      data.encode('cp1252'))
            with open(path, 'wb') as stream:
                stream.write(content)


def result_value(output, index):
    match = re.search(r'^#' + str(index) + r'=(.+)$', output, re.M)
    return match.group(1).strip() if match else None


def check_assertions(event, output, data):
    failures = []
    for assertion in event['assertions']:
        kind = assertion['kind']
        value = expand(assertion.get('value', ''), data)
        path = expand(assertion.get('path', ''), data)
        actual = output if kind.startswith('output_') else read_text(path)
        passed = False
        if kind in ('output_regex', 'file_regex'):
            passed = re.search(value, actual, re.I) is not None
        elif kind in ('output_not_regex', 'file_not_regex'):
            passed = re.search(value, actual, re.I) is None
        elif kind == 'file_value':
            passed = actual.lower() == value.lower()  # PowerShell -eq
        elif kind == 'file_exists':
            passed = os.path.isfile(path)
        elif kind == 'directory_exists':
            passed = os.path.isdir(path)
        elif kind == 'absent':
            passed = not os.path.exists(path)
        elif kind == 'solver_residue':
            root = result_value(output, assertion['root_index'])
            residue = result_value(output, assertion['residue_index'])
            magnitude = float('inf')
            if residue is not None:
                try:
                    magnitude = abs(complex(residue.replace('i', 'j')))
                except ValueError:
                    pass
            passed = (root is not None and
                      re.search(assertion['root_regex'], root, re.I) is not None
                      and math.isfinite(magnitude)
                      and magnitude <= assertion['tolerance'])
            actual = 'root={0}, residue={1}, magnitude={2}'.format(root, residue,
                                                                  magnitude)
            value = 'root /{0}/; |residue| <= {1}'.format(
                assertion['root_regex'], assertion['tolerance'])
        else:
            raise ValueError('Unknown assertion: ' + kind)
        if not passed:
            failures.append({'kind': kind, 'path': path, 'expected': value,
                             'actual_tail': actual[-12000:]})
    return failures


def run_process(event, exe, data, logs, timeout):
    started = time.monotonic()
    arguments = expand(event['arguments'], data)
    cwd = expand(event['cwd'], data)
    command = '"' + exe + '" ' + arguments
    stdin = '\r\n'.join(expand(line, data) for line in event['stdin'])
    if event['stdin']:
        stdin += '\r\n'
    environment = dict((key, value) for key, value in os.environ.items()
                       if not key.upper().startswith('ATC_'))
    environment.update(dict((key, expand(value, data)) for key, value in
                            event['environment'].items()))
    result = {'id': event['id'], 'name': event['name'], 'status': 'INFRA_ERROR',
              'arguments': arguments, 'cwd': cwd, 'stdin': stdin,
              'environment_overrides': event['environment'], 'errors': []}
    process = None
    job = None
    readers = []
    try:
        job = Job()
        process = subprocess.Popen(command, executable=exe, cwd=cwd,
                                   env=environment, stdin=subprocess.PIPE,
                                   stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                   shell=False)
        result['pid'] = process.pid
        job.assign(process)
        for label, source in [('stdout', process.stdout), ('stderr', process.stderr)]:
            reader = Capture(source, os.path.join(logs, '{0:03d}.{1}.txt'.format(
                event['id'], label)))
            reader.start()
            readers.append(reader)
        try:
            process.stdin.write(stdin.encode('cp1252'))
            process.stdin.close()
        except (IOError, OSError):
            # Preserve the actual exit status if the child exits before stdin.
            pass
        timed_out = False
        while process.poll() is None:
            if time.monotonic() - started >= timeout:
                timed_out = True
                break
            time.sleep(0.02)
        job.close()
        job = None
        try:
            process.wait(timeout=5)
        except subprocess.TimeoutExpired:
            process.kill()
            process.wait(timeout=5)
            result['errors'].append('Process survived job close.')
        for reader in readers:
            reader.join(5)
            if reader.is_alive():
                result['errors'].append('Output reader did not reach EOF.')
            if reader.error:
                result['errors'].append(reader.error)
        result['exit_code'] = process.returncode
        result['exit_code_hex'] = '0x{0:08X}'.format(process.returncode & 0xffffffff)
        output = normalized(readers[0].text() + readers[1].text())
        result['output_tail'] = output
        result['log_truncated'] = any(reader.truncated for reader in readers)
        result['assertion_failures'] = check_assertions(event, output, data)
        if result['errors']:
            result['status'] = 'INFRA_ERROR'
        elif timed_out:
            result['status'] = 'TIMEOUT'
        elif process.returncode & 0x80000000:
            result['status'] = 'CRASH'
        elif process.returncode != 0 or result['assertion_failures']:
            result['status'] = 'FAIL'
        else:
            result['status'] = 'PASS'
    except Exception:
        result['errors'].append(traceback.format_exc())
    finally:
        if job is not None:
            try:
                job.close()
            except Exception:
                result['errors'].append(traceback.format_exc())
        if process is not None and process.poll() is None:
            try:
                process.kill()
                process.wait(timeout=5)
            except Exception:
                result['errors'].append(traceback.format_exc())
        for reader in readers:
            reader.join(5)
        result['elapsed_seconds'] = time.monotonic() - started
    return result


def audit_catalog(catalog):
    if catalog['schema'] != 1 or catalog['check_count'] != 376:
        raise ValueError('Unsupported catalog or logical check count.')
    events = catalog['events']
    processes = [event for event in events if event['kind'] == 'process']
    auxiliary = [event for event in events if event['kind'] == 'auxiliary']
    if len(processes) != 369 or len(auxiliary) != 8:
        raise ValueError('Expected 369 processes and 8 direct auxiliary checks.')
    ids = [event['id'] for event in events]
    if len(set(ids)) != len(ids):
        raise ValueError('Duplicate event IDs.')
    checks = catalog['checks']
    if len(checks) != 376 or len(set(c['name'] for c in checks)) != 376:
        raise ValueError('Duplicate/missing logical checks.')
    members = [member for check in checks for member in check['members']]
    if collections.Counter(members) != collections.Counter(ids):
        raise ValueError('Each process/direct check must belong to one check.')
    for event in events:
        if not event['assertions']:
            raise ValueError('Missing assertions: ' + event['name'])
        for assertion in event['assertions']:
            if 'regex' in assertion['kind']:
                re.compile(expand(assertion['value'], r'C:\ATC-XP\data'), re.I)
            if assertion['kind'] == 'solver_residue':
                re.compile(assertion['root_regex'], re.I)


def validate_runtime_paths(catalog, data):
    paths = [data]
    for event in catalog['events']:
        paths.extend(os.path.join(data, change['path'])
                     for change in event.get('changes', []))
        paths.extend(expand(assertion['path'], data)
                     for assertion in event['assertions'] if assertion.get('path'))
    if max(len(path) for path in paths) >= 260:
        raise ValueError('Runtime paths exceed the legacy 259-character limit. '
                         'Extract the package to C:\\ATC-XP-tests or use --runs '
                         'with a shorter directory.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    here = os.path.dirname(os.path.abspath(__file__))
    parser.add_argument('--exe', default=os.path.join(here, 'package', 'atc.exe'))
    parser.add_argument('--assets', default=os.path.join(here, 'package'))
    parser.add_argument('--catalog', default=os.path.join(here, 'catalog.json'))
    parser.add_argument('--runs', default=os.path.join(here, 'runs'))
    parser.add_argument('--audit-only', action='store_true')
    args = parser.parse_args()
    with io.open(args.catalog, 'r', encoding='utf-8') as stream:
        catalog = json.load(stream)
    audit_catalog(catalog)
    if args.audit_only:
        print('Catalog OK: 369 processes; 8 direct checks; 376 logical checks.')
        return 0
    if os.name != 'nt':
        parser.error('Execution requires Windows; --audit-only is portable.')
    exe = os.path.abspath(args.exe)
    if sha256(exe) != catalog['executable_sha256']:
        parser.error('Executable SHA-256 differs from the approved Win32 artifact.')
    with open(exe, 'rb') as stream:
        stream.seek(0x3c)
        pe_offset = struct.unpack('<I', stream.read(4))[0]
        stream.seek(pe_offset)
        if stream.read(6) != b'PE\0\0\x4c\x01':
            parser.error('Expected a Win32 x86 PE executable.')
    if not os.path.isdir(args.runs):
        os.makedirs(args.runs)
    root = os.path.join(os.path.abspath(args.runs), 'xp-' + uuid.uuid4().hex[:12])
    validate_runtime_paths(catalog, os.path.join(root, 'data'))
    os.mkdir(root)
    data = os.path.join(root, 'data')
    shutil.copytree(os.path.abspath(args.assets), data)
    runtime_exe = os.path.join(data, 'atc.exe')
    shutil.copy2(exe, runtime_exe)
    # DLLs beside the selected artifact take precedence over bundled DLLs.
    for name in os.listdir(os.path.dirname(exe)):
        if name.lower().endswith('.dll'):
            shutil.copy2(os.path.join(os.path.dirname(exe), name), data)
    with open(os.path.join(data, 'atc_path.txt'), 'wb') as stream:
        stream.write(data.encode('cp1252'))
    logs = os.path.join(root, 'logs')
    os.makedirs(logs)
    version = sys.getwindowsversion()
    native_xp = (version.major == 5 and version.minor == 1 and
                 struct.calcsize('P') == 4)
    report = {'source_commit': catalog['source_commit'],
              'source_worktree_clean': catalog.get('source_worktree_clean'),
              'local_tracked_changes': catalog.get('local_tracked_changes', []),
              'source_files_sha256': catalog.get('source_files_sha256', {}),
              'executable_sha256': sha256(runtime_exe),
              'runner_sha256': sha256(os.path.abspath(__file__)),
              'catalog_sha256': sha256(os.path.abspath(args.catalog)),
              'official_runner_sha256': catalog['runner_sha256'],
              'python': sys.version, 'platform': platform.platform(),
              'windows_version': list(version),
              'native_xp_x86': native_xp, 'runtime': data,
              'timeout_seconds': catalog['timeout_seconds'],
              'events': [], 'checks': []}
    report['bundled_dll_sha256'] = dict(
        (name, sha256(os.path.join(data, name))) for name in os.listdir(data)
        if name.lower().endswith('.dll'))
    print('Native XP x86: {0}; runtime: {1}'.format(native_xp, data))
    print(catalog['count_note'])
    sys.stdout.flush()
    results = {}
    interrupted = False
    try:
        for event in catalog['events']:
            try:
                apply_changes(event, data, catalog['capture_root'])
                if event['kind'] == 'process':
                    result = run_process(event, runtime_exe, data, logs,
                                         catalog['timeout_seconds'])
                else:
                    failures = check_assertions(event, '', data)
                    result = {'id': event['id'], 'name': event['name'],
                              'status': 'FAIL' if failures else 'PASS',
                              'assertion_failures': failures}
            except Exception:
                result = {'id': event['id'], 'name': event['name'],
                          'status': 'INFRA_ERROR', 'errors': [traceback.format_exc()]}
            results[event['id']] = result
            report['events'].append(result)
            position = ('{0}/369'.format(event['id']) if event['kind'] == 'process'
                        else str(event['id']))
            print('{0} [{1}] {2}'.format(result['status'], position, event['name']))
            sys.stdout.flush()
            save_json(os.path.join(root, 'results.json'), report)
    except KeyboardInterrupt:
        interrupted = True
    precedence = ['INFRA_ERROR', 'CRASH', 'TIMEOUT', 'FAIL', 'PASS']
    for check in catalog['checks']:
        statuses = [results[member]['status'] for member in check['members']
                    if member in results]
        if len(statuses) != len(check['members']):
            status = 'NOT_RUN'
        else:
            status = next(s for s in precedence if s in statuses)
        report['checks'].append({'name': check['name'], 'status': status,
                                 'members': check['members']})
    counts = dict(collections.Counter(check['status'] for check in report['checks']))
    report['counts'] = counts
    report['completed_processes'] = sum(isinstance(key, int) for key in results)
    report['interrupted'] = interrupted
    report['full_catalog_passed'] = counts.get('PASS', 0) == 376
    report['xp_catalog_passed'] = report['full_catalog_passed'] and native_xp
    save_json(os.path.join(root, 'results.json'), report)
    print('SUMMARY {0}; processes={1}/369; report={2}'.format(
        json.dumps(counts, sort_keys=True), report['completed_processes'],
        os.path.join(root, 'results.json')))
    if counts.get('INFRA_ERROR') or counts.get('NOT_RUN'):
        return 2
    return 0 if report['full_catalog_passed'] else 1


if __name__ == '__main__':
    try:
        sys.exit(main())
    except Exception:
        print('INFRA_ERROR: ' + traceback.format_exc(), file=sys.stderr)
        sys.exit(2)
