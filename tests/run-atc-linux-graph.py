#!/usr/bin/env python3
"""Check graph drawing and arrow navigation on a Linux pseudo-terminal."""
import argparse
import json
import math
import re
import time
from pathlib import Path
from atc_linux_terminal import TerminalSession


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--timeout', type=float, default=300,
                        help='Per-case deadline; sanitized graph evaluation is slow')
    parser.add_argument('--output-dir', type=Path)
    args = parser.parse_args()
    executable = args.executable.resolve(strict=True)
    if args.output_dir:
        args.output_dir.mkdir(parents=True, exist_ok=True)
    results = []
    for label, expression, multiple in [
            ('single', 'radsin(x)', False),
            ('multiple', r'radsin(x)\radcos(x)', True)]:
        session = TerminalSession(executable, ['graph(' + expression + ')'], args.timeout)
        start = time.monotonic()
        error = None
        try:
            with session:
                session.expect(lambda data: b'Press Enter to view the graph.' in data, 'graph prompt')
                session.send(b'\n')
                session.expect(lambda data: b'x = -10.000000 ' in data, 'initial cursor')
                session.send(b'\x1b[C')
                session.expect(lambda data: b'x = -9.833333 ' in data, 'first right arrow')
                session.send(b'\x1b[C')
                session.expect(lambda data: b'x = -9.666667 ' in data, 'second right arrow')
                session.send(b'\x1b[D')
                session.expect(lambda data: data.count(b'x = -9.833333 ') >= 2, 'first left arrow')
                session.send(b'\x1b[D')
                session.expect(lambda data: data.count(b'x = -10.000000 ') >= 2, 'return to initial x')
                session.send(b'\x1b')
                session.expect(lambda data: b'Do you want to see the graph data in table form?' in data,
                               'table prompt after Escape')
                session.send(b'0\n')
                session.finish()
                for character in ['│', '▒', '▓', '[X]'] + (['[Y]'] if multiple else []):
                    assert character in session.text, 'Missing graph character/label ' + character
                for function, symbol, wanted in [('radsin', 'X', math.sin(-10))] + (
                        [('radcos', 'Y', math.cos(-10))] if multiple else []):
                    match = re.search(function + r'\(x\) \[' + symbol + r'\]: ([+-]?\d+\.\d+)', session.text)
                    assert match and math.isclose(float(match[1]), wanted, abs_tol=1E-6), 'Incorrect initial f(x)'
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
    print(f'SUMMARY graph={len(results)} passed={len(results)-failures} failed={failures}', flush=True)
    return bool(failures)


if __name__ == '__main__':
    raise SystemExit(main())
