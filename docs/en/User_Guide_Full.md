# Advanced Trigonometry Calculator Full User Guide

Version: ATC 2.1.7  
Language: English  
Author: Renato Alexandre dos Santos Freitas

This guide is the expanded repository user guide for Advanced Trigonometry
Calculator (ATC). It is based on the existing online user guide, the current
2.1.7 documentation, and the automated regression coverage available in this
repository.

## 1. What ATC is

ATC is a free, open-source Windows command-line mathematical application. It is
designed for fast local mathematical work through typed commands and
expressions.

Typical use cases:

- quick scientific calculations;
- trigonometry and inverse trigonometry;
- complex-number calculations;
- matrix work;
- statistics and probability;
- DSP helpers;
- polynomial simplification;
- equation solving and systems of equations;
- reusable variables and expressions;
- guided interactive calculation modules;
- TXT-file based command workflows.

## 2. What ATC is not

ATC deliberately focuses on practical command-driven mathematical computation
instead of trying to be a universal CAS.

- ATC is not a full general-purpose CAS like Mathematica, Maple, SageMath, or
  SymPy.
- ATC is not designed to symbolically prove arbitrary mathematical theorems.
- ATC is not intended to replace domain-specific professional engineering
  validation tools.
- ATC focuses on numeric computation, command-driven workflows, educational
  use, implemented symbolic/numeric hybrid features, and fast local execution.
- Some symbolic behavior exists, but only where explicitly supported and
  tested.

## 3. Input basics

ATC expressions are typed directly at the prompt.

```text
2+3*4
sqrt(9)
sin(pi/2)
log(100)
```

Stable example outputs:

```text
#0=14
#1=3
#2=1
#3=2
```

ATC uses `_` as a negative marker in many documented inputs and outputs:

```text
_6+2
```

Expected result:

```text
#0=-4
```

Scientific notation uses uppercase `E`:

```text
1E3
1E-3
```

## 4. Interactive prompt

ATC 2.1.7 includes a custom prompt editor:

- `Tab` completes documented commands, mathematical functions, aliases and user
  functions;
- repeated `Tab` cycles possible completions;
- `Up` and `Down` navigate command history;
- `Left`, `Right`, `Home`, `End`, `Delete` and `Backspace` edit the current
  input line.

This improves speed while keeping calculation semantics in the normal ATC
parser.

## 5. Angle mode

Use:

```text
mode
```

The menu offers:

```text
radian -> 1
degree -> 2
gradian -> 3
```

Examples:

```text
sin(pi/2)
sin(30)
```

Use `sin(pi/2)` in radian mode and `sin(30)` in degree mode.

## 6. Precision

ATC 2.1.7 supports:

- `double`
- Boost `mp_float`

Persisted precision mode:

```text
higherprecision(1)
higherprecision(0)
```

The setting is applied after restarting ATC.

Useful precision commands:

```text
dp15dppi
dp50dppi
dp50dpe
dp50dpmaxprecpi
```

Stable high-precision examples:

```text
dp50dppi
3.14159265358979323846264338327950288419716939937511

dp50dpe
2.71828182845904523536028747135266249775724709369996
```

`maxprec` is useful when a single expression needs higher precision without
changing the persisted precision mode.

## 7. Constants and previous answers

Common constants:

```text
pi
e
i
INF
_INF
true
false
```

Previous result references use ATC result indexes, for example:

```text
#0
#1
```

Use this to build calculations step by step.

## 8. Arithmetic

Examples:

```text
2+3*4
(2+3)*4
8/4
2^10
5!
abs(_7)
100rest(3)
100quotient(3)
rtD4D(16)
```

Stable expected outputs include:

```text
2+3*4      -> 14
(2+3)*4    -> 20
2^10       -> 1024
5!         -> 120
abs(_7)    -> 7
rtD4D(16)  -> 2
```

## 9. Trigonometry

Examples:

```text
sin(pi/2)
cos(0)
tan(pi/4)
sec(0)
cosec(pi/2)
cotan(pi/4)
asin(1)
acos(1)
atan(1)
acosec(1)
asec(1)
acotan(1)
```

When using degree mode:

```text
mode
sin(30)
```

Expected:

```text
#n=0.5
```

## 10. Hyperbolic functions

Examples:

```text
sinh(0)
cosh(0)
tanh(0)
sech(0)
cosech(1)
cotanh(1)
asinh(0)
acosh(1)
atanh(0)
asech(1)
acosech(1)
acotanh(2)
```

These are useful for scientific and engineering formulas involving hyperbolic
relationships.

## 11. Logarithms

Examples:

```text
log(100)
ln(e)
logb2b(8)
```

Expected:

```text
log(100)  -> 2
ln(e)     -> 1
logb2b(8) -> 3
```

## 12. Complex numbers

ATC supports complex values with `i`.

Examples:

```text
2i
3(2i)
sin(30+30i)
asin(sin(30+30i))
```

Complex-number behavior depends on the selected angle mode for trigonometric
functions.

## 13. Automatic multiplication

ATC can infer multiplication in documented forms.

Examples:

```text
2pi
pi2
2e
2(3+4)
(1+1)(2+3)
2sin(pi/2)
sin(pi/2)2
2i
3(2i)
```

With variables:

```text
x=4
2x
x(4)
(4)x
xpi
pix
xe
xsin(pi/2)
```

When a variable name exists exactly, ATC should prefer the existing variable
over splitting it into implied products.

## 14. Variables

Examples:

```text
data=5
data+1
energy=10
energy+1
```

ATC 2.1.7 accepts broader variable names than older parser versions while
preserving reserved function and constant names.

Useful commands:

```text
see variables
renamed variables
eliminate variables
see results
eliminate results
```

## 15. Matrices

Create a matrix:

```text
create matrix(foo\2\2\3)
```

Matrix helpers:

```text
min(foo)
max(foo)
avg(foo)
linsnum(foo)
colsnum(foo)
getlins(foo)
getcols(foo)
```

Matrix arithmetic:

```text
foo+foo
foo-foo
foo*foo
foo^2
foo^T
foo^R
foo/2
2*foo
```

Use matrices for tabular numeric workflows, linear algebra helpers and repeated
numeric data.

## 16. Statistics and probability

List helpers:

```text
min(3\_1\2)
max(3\_1\2)
avg(2\4\6)
```

Expected:

```text
min(3\_1\2) -> -1
max(3\_1\2) -> 3
avg(2\4\6)  -> 4
```

Gaussian/probability helpers:

```text
gerror(0)
gerrorc(0)
gerrorinv(0)
gerrorcinv(1)
qfunc(0)
qfuncinv(0.5)
```

Guided module:

```text
statistics calculations
```

Use the guided module for menu-based workflows such as variance and standard
deviation where available.

## 17. DSP

Signal helpers:

```text
sinc(0)
sinc(1)
fft(1\0\0\0)
fft(1\2\3)
ifft(1\0\0\0)
ifft(1\1\1\1)
```

Use these commands for compact signal-processing experiments and educational
checks.

## 18. Polynomial tools

Simplify supported polynomial forms:

```text
simplify polynomial(x)
simplify polynomial(x+1)
simplify polynomial(x+x+1)
simplify polynomial(x^2-5*x+6)
simplify polynomial((x-2)*(x-3))
simplify polynomial((x+1)*(x+1))
simplify polynomial((x-1)^2)
simplify polynomial((x+2)*(x-2))
simplify polynomial((x+2i)*(x-2i))
simplify polynomial(((x-5)(x+2))/(x-5))
```

Convert roots to a polynomial:

```text
roots to polynomial(2\3)
roots to polynomial(2\7\12)
roots to polynomial(6.5i\_6.5i)
roots to polynomial(1+2i\1-2i)
roots to polynomial(0\1\2)
```

Stable example:

```text
roots to polynomial(2\3)
(1+0i)x^2+(_5+0i)x^1+(6+0i)
```

## 19. Equation solving

Quadratic command:

```text
solve quadratic equation(1\_5\6)
solve quadratic equation(1\_2\1)
solve quadratic equation(1\2\5)
```

Systems:

```text
solve equations system(1\1\5;1\_1\1)
```

Polynomial equations:

```text
solve equation(x+2)
solve equation(x^2-5*x+6)
solve equation(x^7-12)
solve equation(1\2\3\4\5)
solve equation((x-1)(x-2))
solve equation(((x-5)(x+2))/(x-5))
solve equation(x^25-100)
```

Stable examples:

```text
solve equation(x+2)
x1=-2

solve equation(x^2-5*x+6)
x1=3
x2=2
```

## 20. Solver

The `solver(...)` command supports numerical solving paths and selected
fast-path normalizations.

Examples:

```text
solver(sin(x)-0.5)
solver(0.5-sin(x))
solver(cos(x)-cos(60))
solver(tan(x)-tan(45))
solver(asin(sin(30))-x)
solver(qfunc(x)-qfunc(0.34233))
solver(x^2-12x-9)
solver(x+2)
solver(((x-5)(x+2))/(x-5))
solver((x-e+pii)(x-e-pii))
```

Angle-mode behavior matters for trigonometric solver examples. In degree mode,
`solver(sin(x)-0.5)` is expected to return a degree-based solution.

## 21. Function study

Examples:

```text
function study(x+1)
function study(x^2)
function study(x^2-4)
function study(_x^2)
function study(1/(x-1))
function study((x^2-1)/(x-1))
function study((1-x^2)/(x^2-4))
function study(x/(x^2-9))
function study((x+1)/(x^2+1))
```

Function study reports items such as domain, intercepts, asymptotes,
symmetries, sign, monotony, concavity and codomain where supported.

## 22. Graph

Examples:

```text
graph settings
graph(x)
graph(x;_2\2\1)
```

Graph behavior is console-based. Automated tests cover deterministic smoke
paths and settings mutation; full visual inspection is still best done
manually.

## 23. Guided calculation modules

ATC includes guided menus for:

```text
triangles rectangles solver
arithmetic matrix solver
financial calculations
geometry calculations
statistics calculations
physics calculations
unit conversions
microeconomics calculations
```

These modules prompt for values and options. They are useful when the user
prefers guided input over a single compact expression.

## 24. Financial, geometry, physics and unit conversion recipes

Finance:

```text
financial calculations
100*15/100
```

Geometry:

```text
geometry calculations
```

Physics:

```text
physics calculations
```

Unit conversion:

```text
unit conversions
```

Microeconomics:

```text
microeconomics calculations
```

For guided menus, exact output depends on the selected options and entered
values.

## 25. Time commands

Examples:

```text
time
calendar(2026)
day of week(y2026m6d20)
day of week(d20m6y2026)
time difference calculations
actual time response
```

Interactive or continuously running tools include stopwatch, timer, big timer,
clock and big clock variants. Use them manually when real time or opened
windows are involved.

## 26. Sorting

Numeric sorting:

```text
ascending order(3\1\2)
descending order(3\1\2)
ascending order(_3\1\_2\0)
descending order(_3\1\_2\0)
```

ASCII sorting:

```text
ascii order
inverse ascii order
```

Some sorting commands can export reports.

## 27. TXT processing and command bridge

Core TXT commands:

```text
predefine txt
solve txt
solve txt(name)
open txt("C:\Temp\file.txt")
to solve
enable txt detector
eliminate strings
atc from cmd
atc over cmd
auto solve txt
```

Typical flow:

1. Create a TXT file with one ATC command per line.
2. Run `predefine txt` and provide the path.
3. Run `solve txt`.
4. ATC creates an `_answers.txt` response file.

Example TXT input:

```text
2+2
sqrt(9)
solver(x-2)
solve equation((x-1)(x-2))
simplify polynomial((x+1)(x-1))
2++
2+3
```

ATC should keep processing after an invalid line and report the syntax error
for that line.

## 28. Scripting

The online guide documents scripting helpers such as:

```text
print(...)
get(...)
sprint(...)
while
for
if
else
switch
case
cls()
break
return
replace
replace by index
count occurrences
delete x occurrences
is contained
calc
is equal
get positive value
is to write
is variable
is contained variable
is contained by index
strlen
```

Use scripting for repeatable command workflows. Keep scripts small and test
them with known values before using them on larger calculations.

## 29. User functions

User functions live under the ATC user-functions folder. Autocomplete can
suggest available user functions as `atc_<name>(` completions.

Use user functions when an expression should be reused by name.

## 30. Settings and environment commands

Common commands:

```text
current settings
verbose resolution
verbose resolution(1)
verbose resolution(0)
numerical systems
si prefixes
actual time response
dimensions
window
about
auto adjust window
enable atc intro
disable atc intro
clean history
clean
exit
```

Use `current settings` to inspect persisted configuration.

## 31. File and folder commands

ATC manages folders such as:

- ATC data folder;
- Scripts examples;
- Source code;
- Strings;
- To solve;
- User functions.

Commands may open Explorer, Notepad or external viewers. In automated testing,
these actions are mocked; in normal use they open real windows.

## 32. Export prompts

Some commands ask:

```text
Export result? (Yes -> 1 \ No -> 0)
```

Use:

```text
1
```

to export, or:

```text
0
```

to skip export.

## 33. Verbose resolution

Enable:

```text
verbose resolution(1)
```

Disable:

```text
verbose resolution(0)
```

Verbose mode explains calculation processing. It is useful for learning and
debugging, but normal calculations are quieter with verbose mode disabled.

## 34. Recipes / Usage profiles

### Engineering

```text
solve equation(x^2-5*x+6)
create matrix(foo\2\2\3)
foo^2
unit conversions
physics calculations
```

### Education

```text
2+3*4
sin(pi/2)
mode
geometry calculations
function study(x^2)
```

### DSP

```text
sinc(0)
fft(1\0\0\0)
ifft(1\1\1\1)
sin(pi/2)+cos(0)
```

### Statistics

```text
avg(2\4\6)
min(3\_1\2)
max(3\_1\2)
statistics calculations
qfunc(0)
```

### Finance

```text
financial calculations
100*15/100
```

## 35. Practical troubleshooting

If an expression fails:

- check parentheses balance;
- check angle mode;
- check whether `_` is needed for negative input;
- check whether the command is interactive;
- simplify the expression and test smaller pieces;
- use `verbose resolution(1)` for a more detailed trace;
- confirm whether the feature is documented and covered by regression tests.

## 36. Documentation and test coverage

The repository includes:

```text
docs/Testing.md
tests/ATC_AUTOMATED_TEST_CASES.md
tests/ATC_USER_GUIDE_COVERAGE.md
```

Current validated regression result:

```text
Summary: 359 passed, 0 failed
```

This guide should evolve with the tests and the documented behavior of ATC
2.1.7.
