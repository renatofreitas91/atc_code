#!/usr/bin/env python3
"""Build and revalidate an immutable source checkpoint in a normal Linux terminal."""
import argparse
import datetime
import hashlib
import json
import os
from pathlib import Path
import platform
import re
import shutil
import subprocess
import sys
import time
import uuid

SUITES = [('functional', 35), ('input-smoke', 8), ('additional', 40),
          ('study', 26), ('scripts', 7), ('graph', 2), ('terminal', 10)]


def digest(path):
    result = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1048576), b''):
            result.update(block)
    return result.hexdigest()


def write_json(path, value):
    path.write_text(json.dumps(value, indent=2) + '\n', encoding='utf-8')


def verify(root, manifest):
    for relative, expected in manifest['files_sha256'].items():
        path = root / relative
        if not path.is_file() or digest(path) != expected:
            raise ValueError('Checkpoint file mismatch: ' + relative)


def load_manifest(root):
    checkpoint = root / 'CHECKPOINT.json'
    if checkpoint.is_file():
        manifest = json.loads(checkpoint.read_text(encoding='utf-8'))
        manifest['origin'] = 'archive checkpoint'
        return manifest
    # A repository checkout can be tested directly after git pull. Record its
    # exact current bytes and tracked changes without creating a root manifest.
    def git(*arguments):
        return subprocess.check_output(['git', '-C', str(root)] + list(arguments))
    names = [name.decode('utf-8') for name in git('ls-files', '-z').split(b'\0') if name]
    changes = git('diff', '--name-only', 'HEAD').decode('utf-8').splitlines()
    return {'origin': 'git checkout',
            'source_commit': git('rev-parse', 'HEAD').decode('ascii').strip(),
            'source_worktree_clean': not changes,
            'local_tracked_changes': changes,
            'files_sha256': {name: digest(root / name) for name in names}}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--jobs', type=int, default=1)
    parser.add_argument('--check-only', action='store_true')
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    manifest = load_manifest(root)
    verify(root, manifest)
    if args.check_only:
        print('Hashes OK ({}, commit {}, tracked clean={}); no builds or tests executed.'.format(
            manifest['origin'], manifest['source_commit'], manifest['source_worktree_clean']))
        return 0
    if not sys.platform.startswith('linux'):
        parser.error('Run on Linux; --check-only can run on other systems.')
    if args.jobs < 1:
        parser.error('--jobs must be positive.')
    tag = datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ')
    output = root / 'work' / ('linux-revalidation-' + tag + '-' + uuid.uuid4().hex[:6])
    output.mkdir(parents=True)
    report = {'source_commit': manifest['source_commit'],
              'source_worktree_clean': manifest['source_worktree_clean'],
              'manifest_origin': manifest['origin'],
              'source_snapshot_sha256': hashlib.sha256(json.dumps(manifest['files_sha256'], sort_keys=True).encode('utf-8')).hexdigest(),
              'files_sha256': manifest['files_sha256'],
              'local_tracked_changes': manifest['local_tracked_changes'],
              'platform': platform.platform(), 'python': sys.version,
              'builds': [], 'suites': [], 'linux_approved': False}

    def save():
        write_json(output / 'results.json', report)

    def command(argv, log, env=None):
        started = time.monotonic()
        with log.open('wb') as stream:
            process = subprocess.run(argv, cwd=root, env=env, stdout=stream,
                                     stderr=subprocess.STDOUT)
        return {'command': argv, 'exit_code': process.returncode,
                'elapsed_seconds': round(time.monotonic() - started, 3),
                'log': str(log.relative_to(output)), 'log_sha256': digest(log)}

    save()
    missing = [tool for tool in ('cmake', 'g++', 'script') if not shutil.which(tool)]
    if missing:
        report['preflight_error'] = 'Missing tools: ' + ', '.join(missing)
        save()
        print(report['preflight_error'])
        return 2
    environment = dict(os.environ)
    environment.update({'LC_ALL': 'C', 'PYTHONUNBUFFERED': '1'})
    for key in ('ASAN_OPTIONS', 'UBSAN_OPTIONS', 'LSAN_OPTIONS', 'ATC_DATA_DIR'):
        environment.pop(key, None)
    try:
        for name, argv in [('compiler', ['g++', '--version']),
                           ('cmake', ['cmake', '--version'])]:
            report[name] = command(argv, output / (name + '.log'), environment)
        executables = {}
        for label, instrumented in [('release', False), ('asan-ubsan', True)]:
            build = output / ('build-' + label)
            print('BUILD ' + label + ' (full log in ' + str(output) + ')', flush=True)
            configure = ['cmake', '-S', str(root), '-B', str(build),
                         '-DCMAKE_BUILD_TYPE=Release',
                         '-DCMAKE_CXX_FLAGS_RELEASE=-O3 -DNDEBUG']
            if instrumented:
                configure += ['-DCMAKE_CXX_FLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer -g',
                              '-DCMAKE_EXE_LINKER_FLAGS=-fsanitize=address,undefined']
            entry = {'configuration': label}
            report['builds'].append(entry)
            entry['configure'] = command(configure, output / (label + '-configure.log'), environment)
            if entry['configure']['exit_code'] != 0:
                entry['status'] = 'FAIL'
                save()
                continue
            entry['build'] = command(['cmake', '--build', str(build), '--parallel', str(args.jobs)],
                                     output / (label + '-build.log'), environment)
            entry['status'] = 'PASS' if entry['build']['exit_code'] == 0 else 'FAIL'
            if entry['status'] == 'PASS':
                executable = build / 'atc'
                entry['binary_sha256'] = digest(executable)
                executables[label] = executable
                entry['runtime_libraries'] = command(['ldd', str(executable)],
                    output / (label + '-libraries.log'), environment)
            save()
        modes = [('release', 'release', False), ('asan-ubsan', 'asan-ubsan', False),
                 ('lsan', 'asan-ubsan', True)]
        for mode, build_name, leak_check in modes:
            for suite, expected in SUITES:
                row = {'mode': mode, 'suite': suite, 'expected_checks': expected,
                       'status': 'NOT_RUN', 'observed_pass_lines': 0}
                report['suites'].append(row)
                if build_name not in executables:
                    row['reason'] = 'Required build did not succeed.'
                    save()
                    continue
                env = dict(environment)
                if mode != 'release':
                    env['ASAN_OPTIONS'] = 'detect_leaks={}:halt_on_error=1:abort_on_error=1'.format(int(leak_check))
                    env['UBSAN_OPTIONS'] = 'halt_on_error=1:print_stacktrace=1'
                    if leak_check:
                        env['LSAN_OPTIONS'] = 'verbosity=1:log_threads=1'
                row['sanitizer_environment'] = {key: env[key] for key in
                    ('ASAN_OPTIONS', 'UBSAN_OPTIONS', 'LSAN_OPTIONS') if key in env}
                argv = [sys.executable, str(root / 'tests' / ('run-atc-linux-' + suite + '.py')),
                        str(executables[build_name])]
                if suite in ('graph', 'terminal'):
                    argv += ['--timeout', '300' if suite == 'graph' else '60',
                             '--output-dir', str(output / (mode + '-' + suite + '-details'))]
                print('START {} / {} ({} checks)'.format(mode, suite, expected), flush=True)
                log = output / (mode + '-' + suite + '.log')
                row.update(command(argv, log, env))
                text = log.read_text(encoding='utf-8', errors='replace')
                count = len(re.findall(r'^PASS\b', text, re.M))
                row['observed_pass_lines'] = count
                diagnostics = bool(re.search(r'ERROR: (?:AddressSanitizer|LeakSanitizer)|SUMMARY: .*Sanitizer|runtime error:|LeakSanitizer has encountered', text))
                row['sanitizer_diagnostics_found'] = diagnostics
                restricted = bool(re.search(r'LeakSanitizer.*ptrace|Failed to suspend threads|Could not attach to thread', text, re.I))
                row['status'] = ('INFRA_ERROR' if restricted else
                                 'PASS' if row['exit_code'] == 0 and count == expected and not diagnostics
                                 else 'FAIL')
                print('{} {} / {}: {}/{}'.format(row['status'], mode, suite, count, expected), flush=True)
                save()
        verify(root, manifest)
        report['checkpoint_unchanged_after_execution'] = True
        report['mode_totals'] = {mode: {
            'expected_checks': 128,
            'observed_pass_lines': sum(row['observed_pass_lines'] for row in report['suites'] if row['mode'] == mode),
            'all_seven_suites_passed': all(row['status'] == 'PASS' for row in report['suites'] if row['mode'] == mode)
        } for mode, _, _ in modes}
        report['linux_approved'] = len(report['suites']) == 21 and all(
            row['status'] == 'PASS' for row in report['suites'])
    except KeyboardInterrupt:
        report['interrupted'] = True
    except Exception as error:
        report['infrastructure_error'] = repr(error)
    finally:
        save()
    print('RESULTS ' + str(output), flush=True)
    print(json.dumps(report.get('mode_totals', {}), indent=2), flush=True)
    return 0 if report['linux_approved'] else 1


if __name__ == '__main__':
    raise SystemExit(main())
