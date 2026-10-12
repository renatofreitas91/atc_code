#!/usr/bin/env python3
"""Run representative ATC mathematical regressions on a Linux executable."""
import argparse
import re
import shutil
import subprocess
import tempfile
from dataclasses import dataclass, field
from pathlib import Path


@dataclass(frozen=True)
class Case:
    area: str
    name: str
    expression: str
    expected: str
    stdin: bytes = b""
    files: dict[str, str] = field(default_factory=dict)


CASES = [
    Case("arithmetic", "addition", "1+1", r"^#\d+=2$"),
    Case("arithmetic", "precedence", "2+3*4", r"^#\d+=14$"),
    Case("arithmetic", "parentheses", "(2+3)*4", r"^#\d+=20$"),
    Case("arithmetic", "division", "8/4", r"^#\d+=2$"),
    Case("arithmetic", "power", "2^10", r"^#\d+=1024$"),
    Case("arithmetic", "negative marker", "_6+2", r"^#\d+=-4$"),
    Case("arithmetic", "square root", "sqrt(9)", r"^#\d+=3$"),
    Case("trigonometry", "sine identity", "sin(pi/2)", r"^#\d+=1$"),
    Case("trigonometry", "cosine identity", "cos(0)", r"^#\d+=1$"),
    Case("trigonometry", "tangent identity", "tan(pi/4)", r"^#\d+=1$"),
    Case("trigonometry", "inverse sine", "asin(1)", r"^#\d+=1\.5708$"),
    Case("trigonometry", "inverse cosine", "acos(1)", r"^#\d+=0$"),
    Case("trigonometry", "inverse tangent", "atan(1)", r"^#\d+=0\.785398$"),
    Case("logarithms", "base ten", "log(100)", r"^#\d+=2$"),
    Case("logarithms", "natural logarithm", "ln(e)", r"^#\d+=1$"),
    Case("exponentials", "Euler power", "e^2", r"^#\d+=7\.38906$"),
    Case("complex", "addition", "(1+2i)+(3-4i)", r"^#\d+=4-2i$"),
    Case("complex", "multiplication", "(1+2i)*(3-4i)", r"^#\d+=11\+2i$"),
    Case("complex", "imaginary square root", "sqrt(_1)", r"^#\d+=1i$"),
    Case("polynomials", "simplify product",
         "simplify polynomial((x-2)*(x-3))",
         r"\(1\+0i\)x\^2\+\(_5\+0i\)x\^1\+\(6\+0i\)",
         b"0\n"),
    Case("equations", "quadratic roots", "solve equation((x-1)(x-2))",
         r"x1=2[\s\S]*x2=1", b"0\n"),
    Case("equations", "linear root", "solve equation(x+2)", r"x1=-2", b"0\n"),
    Case("matrices", "minimum", "min(foo)", r"^#\d+=1$",
         files={"variables.txt": "foo 1 0:2 0*3 0:4 0\n"}),
    Case("matrices", "dimensions", "linsnum(foo)", r"^#\d+=2$",
         files={"variables.txt": "foo 1 0:2 0:3 0*4 0:5 0:6 0\n"}),
    Case("matrices", "addition", "foo+bar",
         r"#\d+=\s+7\+0i\s+7\+0i\s+7\+0i\s+7\+0i\s+7\+0i\s+7\+0i",
         files={"variables.txt":
                "foo 1 0:2 0:3 0*4 0:5 0:6 0\n"
                "bar 6 0:5 0:4 0*3 0:2 0:1 0\n"}),
    Case("matrices", "multiplication", "foo*foo",
         r"#\d+=\s+86\+0i\s+75\+0i\s+64\+0i[\s\S]*112\+0i",
         files={"variables.txt":
                "foo 3 0:4 0:5 0*8 0:7 0:6 0*9 0:7 0:5 0\n"}),
    Case("precision", "50 digit pi", "dp50dpmaxprecpi",
         r"^#\d+=3\.14159265358979323846264338327950288419716939937511$"),
    Case("precision", "mp_float pi", "dp50dppi",
         r"^#\d+=3\.14159265358979323846264338327950288419716939937511$",
         files={"higherPrecision.txt": "1"}),
    Case("precision", "mp_float padding", "dp50dp1+1",
         r"^#\d+=2\.00000000000000000000000000000000000000000000000000$",
         files={"higherPrecision.txt": "1"}),
    Case("invalid", "consecutive operators", "2++22",
         r"consecutive arithmetic symbols[\s\S]*Error in syntax"),
    Case("invalid", "missing parenthesis", "((3+3)",
         r"Error in parentheses[\s\S]*2 left parenthesis and 1 right parenthesis"),
    Case("invalid", "empty square root", "sqrt()",
         r"Error in parentheses[\s\S]*Error in syntax"),
    Case("edge", "division by zero", "1/0", r"^#\d+=NAN\+NANi$"),
    Case("edge", "positive infinity", "INF", r"^#\d+=INF$"),
]


def clean_output(data):
    text = data.decode("utf-8", errors="replace").replace("\r", "")
    text = re.sub(r"\x1b\]0;.*?\x07", "", text)
    return text.strip()


def run_case(executable, case):
    with tempfile.TemporaryDirectory(prefix="atc-functional-") as directory:
        cwd = Path(directory)
        session_executable = cwd / "atc"
        shutil.copy2(executable, session_executable)
        defaults = {
            "aboutDisabled.txt": "1",
            "mode.txt": "1",
            "numSystems.txt": "0",
            "siPrefixes.txt": "0",
            "verboseResolution.txt": "0",
            "actualTime.txt": "0",
            "higherPrecision.txt": "0",
        }
        defaults.update(case.files)
        for name, content in defaults.items():
            (cwd / name).write_text(content, encoding="utf-8")
        result = subprocess.run(
            [str(session_executable), case.expression],
            input=case.stdin,
            cwd=cwd,
            capture_output=True,
            timeout=30,
        )
        actual = clean_output(result.stdout + result.stderr)
        passed = result.returncode == 0 and re.search(case.expected, actual) is not None
        return passed, result.returncode, actual


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    args = parser.parse_args()
    executable = args.executable.resolve(strict=True)
    failures = 0
    for index, case in enumerate(CASES, 1):
        try:
            passed, exit_code, actual = run_case(executable, case)
        except subprocess.TimeoutExpired:
            passed, exit_code, actual = False, "timeout", "<timed out>"
        status = "PASS" if passed else "FAIL"
        print(f"{status} [{index}/{len(CASES)}] {case.area}: {case.name}")
        print(f"  input:    {case.expression}")
        print(f"  expected: /{case.expected}/")
        print(f"  obtained: {actual!r}")
        print(f"  exit:     {exit_code}")
        if not passed:
            failures += 1
    print(f"SUMMARY total={len(CASES)} passed={len(CASES)-failures} failed={failures}")
    raise SystemExit(1 if failures else 0)


if __name__ == "__main__":
    main()
