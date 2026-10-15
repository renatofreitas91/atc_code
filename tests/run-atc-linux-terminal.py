#!/usr/bin/env python3
"""Exercise Linux editing, completion, history and the timed startup screen."""
import argparse
import json
import math
import re
import time
from pathlib import Path
from atc_linux_terminal import TerminalSession

NUMBER = re.compile(rb'#\d+=([+-]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?)')
BAR = re.compile(rb'\r((?:\xe2\x96\x92|\xe2\x96\x93)+)(10|0\d)s')


def prompt(data):
    return data.rstrip().endswith(b'>')


def editing(session, exchanges, expected_text=None):
    wanted = []
    session.expect(prompt, 'initial input prompt')
    for keys, value in exchanges:
        wanted.append(value)
        session.send(keys)
        session.expect(lambda data: len(NUMBER.findall(data)) >= len(wanted) and prompt(data),
                       'expression result and next prompt')
    actual = [float(number) for number in NUMBER.findall(bytes(session.output))]
    assert len(actual) == len(wanted) and all(
        math.isclose(a, b, abs_tol=1E-9) for a, b in zip(actual, wanted)), (actual, wanted)
    if expected_text:
        assert expected_text in session.text, 'Completion did not produce ' + expected_text
    session.send(b'exit\n')
    session.finish()


def startup(session, skip):
    session.expect(lambda data: any(int(m[2]) == 10 for m in BAR.finditer(data)), '10-second startup bar')
    acknowledged = time.monotonic()
    if skip:
        session.send(b'\n')
    session.expect(prompt, 'input prompt after startup')
    reached_prompt = time.monotonic()
    raw = bytes(session.output)
    raw.decode('utf-8')  # Fail if the startup still emits legacy invalid bytes.
    assert '▒▒▒' in session.text and '\ufffd' not in session.text
    if skip:
        assert reached_prompt - acknowledged < 3, 'Enter did not skip the countdown promptly'
    else:
        bars = list(BAR.finditer(raw))
        values = [int(match[2]) for match in bars]
        assert values == list(range(10, -1, -1)), 'Missing or repeated countdown ticks: ' + str(values)
        for match in bars:
            blocks = match[1].decode('utf-8')
            assert len(blocks) == 80
            assert blocks.count('▓') == (10 - int(match[2])) * 8, 'Incorrect progress fill'
        times = [next(t for end, t in session.observations if end >= match.end()) for match in bars]
        assert 8.5 <= times[-1] - times[0] <= 12, 'Countdown duration was not approximately ten seconds'
        assert all(0.6 <= right - left <= 1.4 for left, right in zip(times, times[1:])), times
    session.send(b'exit\n')
    session.finish()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--timeout', type=float, default=60)
    parser.add_argument('--output-dir', type=Path)
    args = parser.parse_args()
    executable = args.executable.resolve(strict=True)
    if args.output_dir:
        args.output_dir.mkdir(parents=True, exist_ok=True)
    left, right = b'\x1b[D', b'\x1b[C'
    up, down = b'\x1b[A', b'\x1b[B'
    home, end, delete = b'\x1b[H', b'\x1b[F', b'\x1b[3~'
    cases = [
        ('backspace', [(b'12+34\x7f5\n', 47)], None),
        ('delete', [(b'12+345' + left * 2 + delete + b'\n', 47)], None),
        ('left-right-insertion', [(b'12+35' + left * 2 + right + b'4\n', 357)], None),
        ('home-end', [(b'2+3' + home + b'1' + end + b'4\n', 46)], None),
        ('empty-boundaries', [(b'\x7f' + delete + left + right + home + end + b'2+3\n', 5)], None),
        ('tab-completion', [(b'si\t0)\n', 0)], '>sin(0)'),
        ('wrapped-line-editing', [(b'1+' * 60 + b'12' + left + b'\x7f' + right + b'3\n', 83)], None),
        ('history-and-draft', [(b'7+1\n', 8), (b'6+1' + up + down + b'\n', 7),
                               (up * 2 + b'\n', 8)], None),
    ]
    results = []
    for label, exchanges, expected_text in cases + [
            ('startup-countdown', None, None), ('startup-enter', None, None)]:
        session = TerminalSession(executable, timeout=args.timeout, intro=exchanges is None)
        error = None
        start = time.monotonic()
        try:
            with session:
                if exchanges is None:
                    startup(session, label == 'startup-enter')
                else:
                    editing(session, exchanges, expected_text)
        except Exception as caught:
            error = str(caught)
        row = {'case': label, 'passed': error is None, 'error': error,
               'seconds': round(time.monotonic() - start, 2),
               'exit': session.process.returncode if session.process else None}
        results.append(row)
        print(('PASS ' if row['passed'] else 'FAIL ') + label + ': ' + str(row), flush=True)
        if args.output_dir:
            (args.output_dir / (label + '.log')).write_text(session.text)
        elif error:
            print(session.text[-4000:])
    if args.output_dir:
        (args.output_dir / 'results.json').write_text(json.dumps(results, indent=2))
    failures = sum(not row['passed'] for row in results)
    print(f'SUMMARY terminal={len(results)} passed={len(results)-failures} failed={failures}', flush=True)
    return bool(failures)


if __name__ == '__main__':
    raise SystemExit(main())
