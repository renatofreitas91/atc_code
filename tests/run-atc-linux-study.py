#!/usr/bin/env python3
"""Mathematical regressions for real polynomial and rational function studies."""
import argparse
import importlib.util
import re
import sys
from pathlib import Path

spec = importlib.util.spec_from_file_location('functional', Path(__file__).with_name('run-atc-linux-functional.py'))
functional = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = functional
spec.loader.exec_module(functional)

CASES = [
    ('(1-x^2)/(x^2-4)', [
        r'^f\(x\)\t-\tundefined\t\+\t0\t-\t0\t\+\tundefined\t-',
        r"^f'\(x\)\t-\tundefined\t-\t0\t\+\tundefined\t\+",
        r"^f''\(x\)\t-\tundefined\t\+\tundefined\t-",
        r'Local min: \(0\.000,-0\.250\)',
        r'Codomain: \]-inf,-1\.000\[U\[-0\.250,\+inf\[',
        r'No absolute minimum or maximum\.']),
    ('x/(x^2-9)', [
        r"^f'\(x\)\t-\tundefined\t-\tundefined\t-",
        r'^f\(x\)\t\\v\tundefined\t\\v\tundefined\t\\v',
        r"^f''\(x\)\t-\tundefined\t\+\t0\t-\tundefined\t\+",
        r'Inflection point: \(0\.000,-?0\.000\)', r'^Codomain: \]-inf,\+inf\[$']),
    ('x^2-4', [r"^f'\(x\)\t-\t0\t\+", r"^f''\(x\)\t\+",
        r'Codomain: \[-4\.000,\+inf\[', r'^Min: \(0\.000,-4\.000\)$']),
    ('0-x^2+4', [r'Codomain: \]-inf,4\.000\]', r'^Max: \(-?0\.000,4\.000\)$']),
    ('(x^2+1)/(x^2+2)', [r'Codomain: \[0\.500,1\.000\[',
        r'^Min: \(0\.000,0\.500\)$', r'Inflection point: \(-0\.816,0\.625\)']),
    ('(x^2-1)/(x-1)', [r'Codomain: \]-inf,2\.000\[U\]2\.000,\+inf\[',
        r"^f'\(x\)\t\+\tundefined\t\+", r'No absolute minimum or maximum\.']),
    ('1/x', [r'Codomain: \]-inf,0\.000\[U\]0\.000,\+inf\[',
        r"^f'\(x\)\t-\tundefined\t-", r'No absolute minimum or maximum\.']),
    ('1/(x^2-2)', [r"^f''\(x\)\t\+\tundefined\t-\tundefined\t\+",
        r'Codomain: \]-inf,-0\.500\]U\]0\.000,\+inf\[']),
    ('1/(x^2+1)', [r'Codomain: \]0\.000,1\.000\]', r'^Max: \(-?0\.000,1\.000\)$']),
    ('x^3', [r"^f'\(x\)\t\+\t0\t\+", r"^f''\(x\)\t-\t0\t\+", r'Inflection point: \(0\.000,0\.000\)', r'^Codomain: R$', r'No absolute minimum or maximum\.']),
    ('x^4', [r"^f'\(x\)\t-\t0\t\+", r"^f''\(x\)\t\+\t0\t\+", r'^Codomain: \[0\.000,\+inf\[$', r'^Min: \(0\.000,0\.000\)$']),
    ('x^3-3*x', [r'^\(-1\.73,0\)$', r'^\(0,0\)$', r'^\(1\.73,0\)$', r"^f'\(x\)\t\+\t0\t-\t0\t\+", r'Local max: \(-1\.000,2\.000\)', r'Local min: \(1\.000,-2\.000\)', r'^Codomain: R$', r'No absolute minimum or maximum\.']),
    ('1/(x^3)', [r'The function is odd\.', r'The function is not even\.', r'The function does not intersect the yy-axis\.', r'^x=0$', r"^f'\(x\)\t-\tundefined\t-", r"^f''\(x\)\t-\tundefined\t\+", r'^Codomain: \]-inf,0\.000\[U\]0\.000,\+inf\[$', r'No absolute minimum or maximum\.']),
    ('x^3/(x^2+1)', [r"^f'\(x\)\t\+\t0\t\+", r'^Codomain: R$', r'Inflection point: \(-1\.732,-1\.299\)', r'Inflection point: \(0\.000,0\.000\)', r'Inflection point: \(1\.732,1\.299\)', r'No absolute minimum or maximum\.']),
    ('x^4/(x^2+1)', [r"^f'\(x\)\t-\t0\t\+", r'^Codomain: \[0\.000,\+inf\[$', r'^Min: \(0\.000,0\.000\)$']),
    ('x^4-2*x^2+1', [r'^\(-1,0\)$', r'^\(1,0\)$', r"^f'\(x\)\t-\t0\t\+\t0\t-\t0\t\+", r'^Codomain: \[0\.000,\+inf\[$', r'^Min: \(-?1\.000,0\.000\)$']),
    ('0-x^4', [r'^Codomain: \]-inf,0\.000\]$', r'^Max: \(0\.000,-?0\.000\)$']),
    ('(x^3-1)/(x-1)', [r'^Df=R\\\{1\}$', r'^Codomain: \[0\.750,\+inf\[$', r'^Min: \(-0\.500,0\.750\)$']),
    ('x^3/(x^2)', [r'^Df=R\\\{0\}$', r'^Codomain: \]-inf,0\.000\[U\]0\.000,\+inf\[$', r'No absolute minimum or maximum\.']),
    ('x/(x^3)', [r'^x=0$', r'The function is even\.', r'^Codomain: \]0\.000,\+inf\[$', r'No absolute minimum or maximum\.']),
    ('1/(x^3-x)', [r'^Codomain: \]-inf,0\.000\[U\]0\.000,\+inf\[$', r'^x=-1$', r'^x=0$', r'^x=1$', r'No absolute minimum or maximum\.']),
    ('1/(x^4+1)', [r'^Codomain: \]0\.000,1\.000\]$', r'^Max: \(0\.000,1\.000\)$']),
    ('(x^4-1)/(x^2-1)', [r'^Codomain: \[1\.000,2\.000\[U\]2\.000,\+inf\[$', r'^Min: \(0\.000,1\.000\)$']),

    ('x^3-3*x+1', [r'^\(-1\.88,0\)$', r'^\(0\.347,0\)$', r'^\(1\.53,0\)$', r'Local max: \(-1\.000,3\.000\)', r'Local min: \(1\.000,-1\.000\)', r'^Codomain: R$', r'No absolute minimum or maximum\.']),
    ('x^3+x+1', [r'^\(-0\.682,0\)$', r"^f'\(x\)\t\+", r'^Codomain: R$', r'No absolute minimum or maximum\.']),
    ('x^4-5*x^2+4', [r'^\(-2,0\)$', r'^\(-1,0\)$', r'^\(1,0\)$', r'^\(2,0\)$', r'^Codomain: \[-2\.250,\+inf\[$', r'^Min: \(-?1\.581,-2\.250\)$']),

]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    args = parser.parse_args()
    failures = 0
    for expression, patterns in CASES:
        case = functional.Case('study', expression, 'function study(' + expression + ')', '.*')
        _, rc, output = functional.run_case(args.executable.resolve(), case)
        missing = [p for p in patterns if re.search(p, output, re.M) is None]
        forbidden = []
        if expression in ('x^3', 'x^3-3*x', '1/(x^3)', 'x^3/(x^2+1)', 'x^3/(x^2)', 'x/(x^3)', '1/(x^3-x)'):
            forbidden += [r'^Min:', r'^Max:']
        if expression in ('x^4', '0-x^4', 'x^4/(x^2+1)'):
            forbidden += [r'Inflection point:']
        unexpected = [p for p in forbidden if re.search(p, output, re.M)]
        passed = rc == 0 and not missing and not unexpected and 'Error in parentheses' not in output
        failures += not passed
        print(('PASS ' if passed else 'FAIL ') + expression, flush=True)
        if not passed:
            print('exit:', rc, 'missing:', missing, 'unexpected:', unexpected, '\n', output)
    print(f'SUMMARY study={len(CASES)} passed={len(CASES)-failures} failed={failures}')
    return bool(failures)

if __name__ == '__main__':
    sys.exit(main())
