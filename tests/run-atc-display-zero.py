#!/usr/bin/env python3
"""Check canonical exact-zero display without clamping small nonzero values."""
from fractions import Fraction
import importlib.util
from pathlib import Path

spec = importlib.util.spec_from_file_location(
    'zero_runner', Path(__file__).with_name('run-atc-base-literals.py'))
runner = importlib.util.module_from_spec(spec)
spec.loader.exec_module(runner)
runner.CASES = [('0', '0'), ('_0', '0'), ('0*_1', '0'), ('_1*0', '0'),
                ('0/_1', '0'), ('(_0)^3', '0'), ('(_0)^2', '0'),
                ('1E-15', '1E-15'), ('_1E-15', '-1E-15'),
                ('1E-30', '1E-30'), ('_1E-30', '-1E-30'),
                ('Pf', '1E-15'), ('_Pf', '-1E-15')]


def matches(expression, expected, obtained):
    if expected == '0':
        return obtained == '0'  # Numeric equality alone cannot catch displayed -0.
    try:
        return Fraction(obtained) == Fraction(expected)
    except (TypeError, ValueError, ZeroDivisionError):
        return False


runner.values_equal = matches
if __name__ == '__main__':
    raise SystemExit(runner.main())
