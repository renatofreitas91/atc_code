#!/usr/bin/env python3
"""Focused XP calendar diagnosis. Does not change the official All catalogue."""
from __future__ import print_function
import argparse
import ctypes
from ctypes import wintypes
import hashlib
import io
import json
import os
import runpy
import shutil
import sys
import threading
import time
import uuid


def save(path, value):
    with io.open(path, 'w', encoding='utf-8') as stream:
        stream.write(json.dumps(value, indent=2, ensure_ascii=True) + u'\n')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--base', default=os.path.dirname(os.path.abspath(__file__)))
    parser.add_argument('--exe', default=r'C:\ATC\atc_source\Release\atc.exe')
    args = parser.parse_args()
    base = os.path.abspath(args.base)
    harness = runpy.run_path(os.path.join(base, 'run-atc-xp.py'))
    with io.open(os.path.join(base, 'catalog.json'), encoding='utf-8') as stream:
        catalog = json.load(stream)
    harness['audit_catalog'](catalog)
    if harness['sha256'](args.exe) != catalog['executable_sha256']:
        raise ValueError('Selected executable differs from the approved artifact.')
    official = next(event for event in catalog['events']
                    if event['name'] == 'date/time command: calendar fixed year')
    root = os.path.join(base, 'runs', 'calendar-diagnostic-' + uuid.uuid4().hex[:10])
    os.makedirs(root)
    report = {'kind': 'focused diagnosis, not an All suite result',
              'official_timeout_seconds': 20, 'source_commit': catalog['source_commit'],
              'executable_sha256': catalog['executable_sha256'],
              'diagnostic_sha256': harness['sha256'](os.path.abspath(__file__)),
              'python': sys.version, 'windows_version': list(sys.getwindowsversion()),
              'probes': []}
    kernel = ctypes.WinDLL('kernel32', use_last_error=True)
    kernel.GetProcessTimes.argtypes = [wintypes.HANDLE] + [ctypes.POINTER(wintypes.FILETIME)] * 4
    kernel.GetProcessTimes.restype = wintypes.BOOL
    psapi = ctypes.WinDLL('psapi', use_last_error=True)

    class Memory(ctypes.Structure):
        _fields_ = [('cb', wintypes.DWORD), ('PageFaultCount', wintypes.DWORD)] + [
            (name, ctypes.c_size_t) for name in (
                'PeakWorkingSetSize', 'WorkingSetSize', 'QuotaPeakPagedPoolUsage',
                'QuotaPagedPoolUsage', 'QuotaPeakNonPagedPoolUsage',
                'QuotaNonPagedPoolUsage', 'PagefileUsage', 'PeakPagefileUsage')]

    psapi.GetProcessMemoryInfo.argtypes = [wintypes.HANDLE, ctypes.POINTER(Memory), wintypes.DWORD]
    psapi.GetProcessMemoryInfo.restype = wintypes.BOOL
    BaseJob = harness['Job']

    def probe(name, interactive=False, timeout=20):
        folder = os.path.join(root, name)
        data = os.path.join(folder, 'data')
        shutil.copytree(os.path.join(base, 'package'), data)
        exe = os.path.join(data, 'atc.exe')
        shutil.copy2(args.exe, exe)
        for file_name in os.listdir(os.path.dirname(os.path.abspath(args.exe))):
            if file_name.lower().endswith('.dll'):
                shutil.copy2(os.path.join(os.path.dirname(args.exe), file_name), data)
        settings = {'atc_path.txt': data, 'aboutDisabled.txt': '1',
                    'mode.txt': '1', 'higherPrecision.txt': '0',
                    'numSystems.txt': '0', 'siPrefixes.txt': '0',
                    'verboseResolution.txt': '0', 'actualTime.txt': '0'}
        for file_name, value in settings.items():
            with open(os.path.join(data, file_name), 'wb') as stream:
                stream.write(value.encode('cp1252'))
        logs = os.path.join(folder, 'logs')
        os.makedirs(logs)
        samples = []
        monitor_errors = []
        stop = threading.Event()
        worker = [None]
        observed_process = [None]
        start = time.monotonic()

        def sample(process):
            try:
                while not stop.is_set():
                    row = {'elapsed_seconds': time.monotonic() - start}
                    create, exit_time, system, user = [wintypes.FILETIME() for _ in range(4)]
                    if kernel.GetProcessTimes(int(process._handle), ctypes.byref(create),
                                              ctypes.byref(exit_time), ctypes.byref(system),
                                              ctypes.byref(user)):
                        row['cpu_seconds'] = ((system.dwHighDateTime << 32) + system.dwLowDateTime +
                                              (user.dwHighDateTime << 32) + user.dwLowDateTime) / 1e7
                    memory = Memory()
                    memory.cb = ctypes.sizeof(memory)
                    if psapi.GetProcessMemoryInfo(int(process._handle), ctypes.byref(memory), memory.cb):
                        row['working_set_bytes'] = memory.WorkingSetSize
                        row['private_commit_bytes'] = memory.PagefileUsage
                    for label, path in [('calendar', os.path.join(data, 'calendar.txt')),
                                        ('stdout', os.path.join(logs, '001.stdout.txt')),
                                        ('stderr', os.path.join(logs, '001.stderr.txt'))]:
                        if os.path.isfile(path):
                            row[label + '_bytes'] = os.path.getsize(path)
                    samples.append(row)
                    stop.wait(0.25)
            except Exception as error:
                monitor_errors.append(repr(error))

        class ObservedJob(BaseJob):
            def assign(self, process):
                BaseJob.assign(self, process)
                observed_process[0] = process
                worker[0] = threading.Thread(target=sample, args=(process,))
                worker[0].daemon = True
                worker[0].start()

        event = dict(official)
        event.update({'id': 1, 'name': name, 'cwd': data, 'changes': [],
                      'stdin': ['calendar(2026)', 'exit'] if interactive else [],
                      'arguments': '"atc over cmd"' if interactive else official['arguments']})
        # Replace only the diagnostic invocation's job class to observe the
        # exact process created by the already validated shared harness.
        invoke = harness['run_process']
        original_job = invoke.__globals__['Job']
        invoke.__globals__['Job'] = ObservedJob
        try:
            result = invoke(event, exe, data, logs, timeout)
        finally:
            invoke.__globals__['Job'] = original_job
            stop.set()
            if worker[0] is not None:
                worker[0].join(3)
        result['timeout_seconds'] = timeout
        result['diagnostic_extended_timeout'] = timeout != 20
        result['samples'] = samples
        result['monitor_errors'] = monitor_errors
        calendar = os.path.join(data, 'calendar.txt')
        if os.path.isfile(calendar):
            result['calendar_sha256'] = harness['sha256'](calendar)
            result['calendar_bytes'] = os.path.getsize(calendar)
        if samples:
            result['last_cpu_seconds'] = samples[-1].get('cpu_seconds')
        if observed_process[0] is not None:
            create, exit_time, system, user = [wintypes.FILETIME() for _ in range(4)]
            if kernel.GetProcessTimes(int(observed_process[0]._handle), ctypes.byref(create),
                                      ctypes.byref(exit_time), ctypes.byref(system),
                                      ctypes.byref(user)):
                result['final_cpu_seconds'] = ((system.dwHighDateTime << 32) + system.dwLowDateTime +
                                                (user.dwHighDateTime << 32) + user.dwLowDateTime) / 1e7
        report['probes'].append(result)
        save(os.path.join(root, 'diagnosis.json'), report)
        print('{0}: {1}, wall={2:.3f}s, CPU={3}s'.format(
            name, result['status'], result['elapsed_seconds'], result.get('final_cpu_seconds')))
        sys.stdout.flush()
        return result

    first = probe('01-fresh-command')
    second = probe('02-fresh-command-repeat')
    third = probe('03-fresh-interactive', interactive=True)
    if any(item['status'] == 'TIMEOUT' for item in (first, second, third)):
        probe('04-diagnostic-60-seconds', timeout=60)
    report['official_20_second_probe_statuses'] = [p['status'] for p in (first, second, third)]
    report['full_suite_approval'] = False
    save(os.path.join(root, 'diagnosis.json'), report)
    print('Report: ' + os.path.join(root, 'diagnosis.json'))
    print('Return the complete calendar-diagnostic folder, including logs and data.')
    return 0 if all(p['status'] == 'PASS' for p in (first, second, third)) else 1


if __name__ == '__main__':
    try:
        sys.exit(main())
    except Exception as error:
        print('INFRA_ERROR: ' + repr(error), file=sys.stderr)
        sys.exit(2)
