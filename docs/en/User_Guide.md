# Advanced Trigonometry Calculator User Guide

This is a basic repository-level user guide for Advanced Trigonometry
Calculator (ATC). It does not replace the full ATC user guide distributed with
the application.

For current technical behavior, see:

- `docs/en/User_Guide_Full.md`
- `docs/pt-PT/User_Guide_Full.md`
- `docs/ATC_2.1.7_DOCUMENTATION.md`
- `docs/RELEASE_2.1.7.md`
- `tests/ATC_USER_GUIDE_COVERAGE.md`

## What ATC Is

ATC is a free, open-source Windows command-line mathematical application. Users
enter expressions or documented ATC commands, and ATC prints results in the
console.

ATC is focused on practical numerical workflows and documented command
behavior.

## What ATC is not

ATC deliberately focuses on practical command-driven mathematical computation
instead of trying to be a universal computer algebra system.

- ATC is not a full general-purpose CAS like Mathematica, Maple, SageMath, or
  SymPy.
- ATC is not designed to symbolically prove arbitrary mathematical theorems.
- ATC is not intended to replace domain-specific professional engineering
  validation tools.
- ATC focuses on numeric computation, command-driven workflows, educational
  use, implemented symbolic/numeric hybrid features, and fast local execution.
- Some symbolic behavior exists, but only where explicitly supported and
  tested.

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

## Interactive Prompt

The ATC prompt supports command-line editing while typing:

- press `Tab` to complete documented commands, mathematical functions and user
  functions;
- press `Tab` again to cycle through alternative matches when more than one
  completion is possible;
- use the `Up` and `Down` arrows to reuse previous expressions;
- use `Left`, `Right`, `Home`, `End`, `Delete` and `Backspace` for normal line
  editing.

Autocomplete inserts the closest available match first and can be used more
than once in the same expression.

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

## Recipes / Usage Profiles

These recipes give short, practical entry points into ATC without requiring the
full user guide first. Outputs are shown only where they are stable across the
validated 2.1.7 regression suite.

### Engineering

**Objective:** solve a polynomial equation.

```text
solve equation(x^2-5*x+6)
```

Expected stable output:

```text
x1=3
x2=2
```

Use this when a supported polynomial form can be solved through ATC's equation
solver paths.

**Objective:** perform a unit conversion.

```text
unit conversions
```

Expected output: example placeholder, because this is an interactive menu.

Use this when working through ATC's documented conversion menus.

**Objective:** run a physics calculation.

```text
physics calculations
```

Expected output: example placeholder, because this is an interactive menu.

Use this for documented physics workflows where ATC prompts for the required
values.

**Objective:** create and reuse a matrix.

```text
create matrix(foo\2\2\3)
foo+foo
```

Use this when a matrix should be created once and reused in later matrix
expressions.

### Education

**Objective:** evaluate arithmetic with operator precedence.

```text
2+3*4
```

Expected stable output:

```text
#0=14
```

Use this for quick arithmetic checks and classroom examples.

**Objective:** evaluate a trigonometric identity.

```text
sin(pi/2)
```

Expected stable output in radian mode:

```text
#0=1
```

Use this when teaching or checking angle-mode-sensitive trigonometry.

**Objective:** study geometry through the guided menu.

```text
geometry calculations
```

Expected output: example placeholder, because this is an interactive menu.

Use this for documented geometry calculations that require prompted inputs.

### DSP

**Objective:** evaluate a normalized signal helper.

```text
sinc(0)
```

Expected stable output:

```text
#0=1
```

Use this for simple signal-processing checks.

**Objective:** run a discrete Fourier transform example.

```text
fft(1\0\0\0)
```

Use this for documented DSP workflows involving short numeric sequences.

**Objective:** combine trigonometry with numeric processing.

```text
sin(pi/2)+cos(0)
```

Expected stable output:

```text
#0=2
```

Use this for compact trigonometric processing expressions.

### Statistics

**Objective:** calculate a mean from a list.

```text
avg(2\4\6)
```

Expected stable output:

```text
#0=4
```

Use this for quick list-based average calculations.

**Objective:** calculate minimum and maximum values.

```text
min(3\_1\2)
max(3\_1\2)
```

Expected stable outputs:

```text
#0=-1
#1=3
```

Use this when inspecting small datasets directly in the command line.

**Objective:** use the statistics menu.

```text
statistics calculations
```

Expected output: example placeholder, because this is an interactive menu.

Use this for guided statistical workflows such as variance and standard
deviation where available in the menu.

### Finance

**Objective:** open guided financial calculations.

```text
financial calculations
```

Expected output: example placeholder, because this is an interactive menu.

Use this for documented financial workflows such as interest and percentage
calculations.

**Objective:** calculate a simple percentage with arithmetic.

```text
100*15/100
```

Expected stable output:

```text
#0=15
```

Use this for quick percentage checks without entering an interactive menu.

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
