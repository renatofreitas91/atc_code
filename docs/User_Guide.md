# Advanced Trigonometry Calculator User Guide

This is a basic repository-level user guide for Advanced Trigonometry
Calculator (ATC). It does not replace the full ATC user guide distributed with
the application.

For current technical behavior, see:

- `docs/ATC_2.1.7_DOCUMENTATION.md`
- `docs/RELEASE_2.1.7.md`
- `tests/ATC_USER_GUIDE_COVERAGE.md`

## What ATC Is

ATC is a free, open-source Windows command-line mathematical application. Users
enter expressions or documented ATC commands, and ATC prints results in the
console.

ATC is focused on practical numerical workflows and documented command
behavior.

## Basic Expressions

```text
2+3*4
sqrt(9)
sin(pi/2)
log(100)
```

Example output:

```text
#0=14
#1=3
#2=1
#3=2
```

## Angle Mode

ATC supports configurable angle modes through the `mode` command:

```text
mode
```

The menu presents:

```text
radian -> 1
degree -> 2
gradian -> 3
```

## Precision Mode

ATC can persistently switch between `double` and Boost `mp_float`:

```text
higherprecision(1)
higherprecision(0)
```

The selected mode is applied after restarting ATC.

Useful high-precision examples:

```text
dp50dppi
dp50dpe
dp50dpmaxprecpi
```

## Variables

ATC supports user variables and reusable expressions. Variable-name behavior in
2.1.7 is broader than earlier parser restrictions, while exact reserved names
remain protected.

Example:

```text
data=5
data+1
```

## Matrices

ATC supports matrix commands and matrix-related helper functions.

Example:

```text
create matrix(foo\2\2\3)
min(foo)
max(foo)
avg(foo)
```

## Polynomial and Equation Commands

Examples:

```text
simplify polynomial((x-2)*(x-3))
roots to polynomial(2\3)
solve equation(x^2-5*x+6)
solve quadratic equation(1\_5\6)
solve equations system(1\1\5;1\_1\1)
```

Supported textual polynomial behavior is documented in
`docs/ATC_2.1.7_DOCUMENTATION.md`.

## Solver

The `solver(...)` command supports documented numerical solving paths.

Examples:

```text
solver(sin(x)-0.5)
solver(x^2-12x-9)
```

Solver behavior depends on expression type, configured angle mode, and the
available solver path.

## Verbose Resolution

Verbose resolution can be controlled with:

```text
verbose resolution
verbose resolution(1)
verbose resolution(0)
```

In 2.1.7, verbose output is intended to explain user-facing calculations while
avoiding internal startup/menu noise.

## More Help

Inside ATC, try:

```text
user guide
current settings
```

For automated coverage of documented behavior, see:

```text
tests\ATC_AUTOMATED_TEST_CASES.md
tests\ATC_USER_GUIDE_COVERAGE.md
```
