#!/usr/bin/env python3
"""Check Linux line boundaries and EOF against the actual ATC executable."""
import argparse
import math
import re
import shlex
import shutil
import subprocess
import tempfile
from pathlib import Path


def check(executable, name, data, expected, tty=False, high_precision=False):
    # Keep the working directory inside a disposable parent so the test can
    # detect path-separator leaks outside the intended session directory.
    with tempfile.TemporaryDirectory(prefix="atc-input-") as parent:
        cwd = Path(parent) / "session"
        cwd.mkdir()
        if high_precision:
            (cwd / "higherPrecision.txt").write_text("1")
        command = [str(executable)]
        if tty:
            command = ["script", "-qefc", shlex.quote(str(executable)), "/dev/null"]
        run = subprocess.run(command, input=data, cwd=cwd, capture_output=True,
                             timeout=30)
        output = run.stdout.decode("utf-8", errors="replace")
        values = [float(value) for value in re.findall(
            r"#\d+=([+-]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?)", output)]
        if run.returncode != 0 or len(values) != len(expected) or any(
            not math.isclose(actual, wanted, abs_tol=1e-10)
            for actual, wanted in zip(values, expected)
        ):
            raise AssertionError(f"{name}: exit={run.returncode}, values={values}\n"
                                 f"{output}\n{run.stderr.decode(errors='replace')}")
        escaped_paths = [path.name for path in Path(parent).iterdir()
                         if "\\" in path.name]
        if escaped_paths:
            raise AssertionError(f"{name}: POSIX run created escaped paths: "
                                 f"{escaped_paths}")
        if expected and not (cwd / "history.txt").is_file():
            raise AssertionError(f"{name}: history.txt was not persisted in "
                                 "the session directory")
        if not (cwd / "higherPrecision.txt").is_file():
            raise AssertionError(f"{name}: higherPrecision.txt was not persisted "
                                 "in the session directory")
        print(f"PASS {name}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    args = parser.parse_args()
    executable = args.executable.resolve(strict=True)
    expressions = b"1+1\n2*3\n10/2\n2^3\nsqrt(4)\nsin(0)\nexit\n"
    check(executable, "LF separates expressions", expressions, [2, 6, 5, 8, 2, 0])
    check(executable, "CR separates expressions", b"1+1\r2*3\rexit\r", [2, 6])
    check(executable, "CRLF separates expressions", b"1+1\r\n2*3\r\nexit\r\n", [2, 6])
    check(executable, "closed stdin exits", b"", [])
    check(executable, "EOF after newline exits", b"1+1\n", [2])
    check(executable, "final unterminated expression", b"2*3", [6])
    check(executable, "high precision LF and EOF", b"1+1\n2*3", [2, 6],
          high_precision=True)
    if shutil.which("script") is None:
        raise RuntimeError("util-linux script is required for the pseudo-TTY check")
    # The leading blank line acknowledges the existing interactive intro.
    check(executable, "pseudo-TTY LF", b"\n" + expressions, [2, 6, 5, 8, 2, 0], tty=True)


if __name__ == "__main__":
    main()
