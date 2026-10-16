#!/usr/bin/env python3
"""Exercise the legacy SI-prefix grammar with exact rational expectations."""
from fractions import Fraction
import math
import importlib.util
from pathlib import Path

spec = importlib.util.spec_from_file_location(
    'literal_runner', Path(__file__).with_name('run-atc-base-literals.py'))
runner = importlib.util.module_from_spec(spec)
spec.loader.exec_module(runner)

PREFIXES = [('Y', 24), ('Z', 21), ('E', 18), ('P', 15), ('T', 12),
            ('G', 9), ('M', 6), ('k', 3), ('h', 2), ('da', 1),
            ('d', -1), ('c', -2), ('m', -3), ('u', -6), ('n', -9),
            ('p', -12), ('f', -15), ('a', -18), ('z', -21), ('y', -24)]
runner.CASES = [('P' + prefix, '1E' + str(power)) for prefix, power in PREFIXES]
runner.CASES += [('2P' + prefix, '2E' + str(power)) for prefix, power in PREFIXES]
runner.CASES += [('_Pk', '-1000'), ('_2Pk', '-2000'), ('0.5Pk', '500'),
                 ('2*Pk', '2000'), ('2Pk+3', '2003'), ('(2+3)*Pk', '5000'),
                 ('2Pk*3Pm', '6'), ('Pk/Pm', '1000000'), ('(2Pk)^2', '4000000'),
                 ('dp12dp(Pk+Pm)', '1000.001'), ('dp12dp(2Pk+3Pm)', '2000.003'),
                 ('dp50dpmaxprec2PY', '2E24'), ('dp50dpmaxprec2Py', '2E-24')]
runner.CASES += [('1E-15', '1E-15'), ('_1E-15', '-1E-15'),
                 ('1E-16', '1E-16'), ('1E-17', '1E-17'), ('1E-15+0', '1E-15'),
                 ('1E-15*2', '2E-15'), ('(Pf)', '1E-15'), ('Pf+0', '1E-15'),
                 ('_Pf', '-1E-15'), ('Pf*1', '1E-15')]
runner.CASES += [('sinc(0)', '1'), ('sinc(1)', '0'), ('sinc(_2)', '0'),
                 ('sinc(1)+Pf', '1E-15'), ('sinc(0.5)', str(2 / math.pi)),
                 ('sinc(i)', str(math.sinh(math.pi) / math.pi)),
                 ('(_2)^2', '4'), ('(_2)^3', '-8'), ('(_2)^_2', '0.25'),
                 ('(_2)^0.5', '1.414213562373095i')]
runner.CASES += [('Pf*i', '1E-15i'), ('1+Pf*i', '1+1E-15i'), ('_Pf*i', '-1E-15i')]
persisted_start = len(runner.CASES)
runner.CASES += [('Pk', '1000'), ('2Pk', '2000'), ('Pm', '0.001'), ('2m', '22')]


def exact_value(expression, expected, obtained):
    try:
        if obtained is None or 'e' in obtained:
            return False  # Preserve the legacy uppercase scientific exponent marker.
        if expression in ('Pf*i', '1+Pf*i', '_Pf*i'):
            return complex(obtained.replace('i', 'j')) == complex(expected.replace('i', 'j'))
        if expression in ('sinc(0.5)', 'sinc(i)', '(_2)^0.5'):
            return abs(complex(obtained.replace('i', 'j')) -
                       complex(expected.replace('i', 'j'))) <= 0.00001
        return Fraction(obtained) == Fraction(expected)
    except (ValueError, TypeError, AttributeError, ZeroDivisionError):
        return False


def fixtures(index, expression, precision):
    if index >= persisted_start:
        return {'variables.txt': 'k 7 0\nm 11 0\n', 'siPrefixes.txt': '1'}
    return {}


runner.values_equal = exact_value
runner.extra_fixtures = fixtures

if __name__ == '__main__':
    raise SystemExit(runner.main())
