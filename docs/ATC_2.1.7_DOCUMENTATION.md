# Advanced Trigonometry Calculator 2.1.7 - current technical documentation

Date: 2026-06-09

This document describes the current state of ATC 2.1.7 after the precision,
equation solver, regression-test and memory-improvement work.

## Scope of 2.1.7

ATC 2.1.7 focuses on making precision mode predictable between application
restarts, fixing high precision formatting, improving command-line testability,
adding automatic regression coverage based on the full user guide, and reducing
unnecessary dynamic allocation in common numeric paths. It also relaxes previous
variable-name restrictions while preserving exact reserved names.

## Precision modes

ATC now supports persistent transition between:

- `double`
- Boost `mp_float`

The selected mode is stored in:

```text
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator\higherPrecision.txt
```

Accepted values:

- `0`: use `double`
- `1`: use Boost `mp_float`

The executable reads this file at startup and dispatches the main template flow
to the correct numeric type.

## Higher precision commands

Interactive and direct command-line control are supported:

```text
higherprecision(1)
higherprecision(0)
```

Expected behavior:

- `higherprecision(1)` saves Boost `mp_float` for the next ATC run.
- `higherprecision(0)` saves `double` for the next ATC run.
- The setting survives application restarts.

## Fixed precision output

Decimal-place formatting now works with both `double` and Boost `mp_float`.

Important validated commands:

```text
dp15dppi
dp50dppi
dp50dpe
dp50dp1+1
```

Validated high precision results:

```text
dp50dppi = 3.14159265358979323846264338327950288419716939937511
dp50dpe  = 2.71828182845904523536028747135266249775724709369996
```

Implementation notes:

- `dp...dp...` formatting avoids `printf("%f")` for `mp_float`.
- Stream formatting with `std::fixed` and `std::setprecision(...)` is used.
- `pi` and `e` use Boost constants when running under `mp_float`.

## Equation solver

The SourceForge implementation shows that values separated by `\` represent
polynomial coefficients from highest degree to constant term.

Example:

```text
solve equation(1\0\0\0\0\0\0\_12)
```

represents:

```text
x^7 - 12
```

ATC 2.1.7 now also accepts simple textual polynomials and normalizes them to the
coefficient form before calling the numeric solver.

Validated examples:

```text
solve equation(x+2)
solve equation(x^2-5*x+6)
solve equation(x^7-12)
```

Expected results:

```text
solve equation(x+2)
x1=-2

solve equation(x^2-5*x+6)
x1=3
x2=2

solve equation(x^7-12)
x1=1.42616
x2=0.889197+1.11502i
x3=0.889197-1.11502i
x4=-0.317351+1.3904i
x5=-0.317351-1.3904i
x6=-1.28493-0.618788i
x7=-1.28493+0.618788i
```

Supported textual polynomial pattern:

- one variable: `x`
- integer non-negative exponents, for example `x^7`
- optional `*` between coefficient and `x`, for example `5*x`
- `+`, `-` and ATC negative marker `_`
- no parentheses or division in the normalizer path

Expressions outside that simple pattern continue through the existing solver
path.

## Polynomial simplification

ATC 2.1.7 now preserves the symbolic variable when `simplify polynomial(...)`
receives simple textual polynomials. The command normalizes supported textual
forms to ATC's internal polynomial representation before calling the existing
simplifier, avoiding the previous path where `x` could be evaluated as zero.

Validated examples:

```text
simplify polynomial(x)
simplify polynomial(x+1)
simplify polynomial(x+x+1)
simplify polynomial(x^2-5*x+6)
simplify polynomial((x-2)*(x-3))
simplify polynomial((x+1)*(x+1))
simplify polynomial((2*x+1)*(x-3))
```

Expected results include:

```text
simplify polynomial(x^2-5*x+6)
(1+0i)x^2+(_5+0i)x^1+(6+0i)

simplify polynomial((x-2)*(x-3))
(1+0i)x^2+(_5+0i)x^1+(6+0i)
```

Supported textual polynomial simplification pattern:

- one variable: `x`
- integer non-negative exponents, for example `x^2`
- optional `*` between coefficient and `x`, for example `2*x`
- `+`, `-` and ATC negative marker `_`
- simple products of parenthesized polynomial factors, for example
  `(x-2)*(x-3)`

## Export prompts and automation

Some ATC commands ask:

```text
Export result? (Yes -> 1 \ No -> 0)
```

ATC normally uses `_getch()` for this prompt. In 2.1.7, redirected stdin is also
supported so automated tests can provide:

```text
1
C:\path\to\report.txt
```

Normal interactive console use still uses `_getch()`.

## Variable names

ATC 2.1.7 allows normal user variables to use the full Latin alphabet more
freely. Names such as `data`, `energy`, `beta`, `alpha`, `matx`, `matrixvar`,
`sinx` and `bvar` are validated in persisted `variables.txt` use and can be
used in expressions such as:

```text
data+1
sinx+1
bvar+1
```

Exact reserved names remain protected to avoid ambiguity with functions,
constants and numeric-system prefixes. Examples include `sin`, `cos`, `log`,
`ln`, `pi`, `e`, `i`, `B`, `O`, `H`, `P`, `D`, `b`, `min`, `max` and `avg`.

The parser also protects guide syntax with internal delimiters, including:

```text
rtD4D(16)
logb2b(8)
```

## Automatic multiplication

ATC continues to infer multiplication from adjacent values in common calculator
syntax. The 2.1.7 regression suite now validates these forms:

```text
2pi
pi2
2e
2sin(pi/2)
sin(pi/2)2
2(3+4)
(1+1)(2+3)
(1+1)sin(pi/2)
2i
3(2i)
2rtD4D(16)
2logb2b(8)
```

Variables also participate in implicit multiplication:

```text
2x
x2
x(4)
(4)x
xy
x y
```

When a composite variable exists, the composite name has priority. For example,
if `xy` exists, `xy` and `x y` resolve to that variable after whitespace
normalization. If only `x` and `y` exist, the same forms are interpreted as
`x*y`.

## Automatic regression tests

The automatic test runner is:

```text
tests\run-atc-regression.ps1
```

Run after building Release x64:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1 -AtcExe .\x64\Release\atc.exe
```

Current validated result:

```text
Summary: 122 passed, 0 failed
```

Coverage includes:

- arithmetic basics
- constants
- trigonometry
- hyperbolic functions
- inverse trigonometric and inverse hyperbolic functions
- logarithms
- custom arithmetic/log syntax from the guide: `rest`, `quotient`, `rtD...D`,
  `logb...b`, `afact`
- matrix/list functions: `min`, `max`, `avg`, both with direct lists and with
  matrix variable names
- matrix guide helpers: `linsnum`, `colsnum`, `getlins`, `getcols`
- relaxed variable names, including names that start with or contain letters
  previously reserved by parser shortcuts
- automatic multiplication with constants, functions, parentheses, imaginary
  values, guide delimiters and variables
- DSP functions: `sinc`, `fft`, `ifft`
- probability/statistics inline functions: `gerror`, `gerrorinv`,
  `gerrorc`, `gerrorcinv`, `qfunc`, `qfuncinv`
- numeric sorting with report export
- roots-to-polynomial report export
- textual polynomial simplification, including simple factor products
- quadratic equation solver
- 2x2 equations system solver
- textual polynomial equation solver
- coefficient-form cubic equation solver
- `double` mode precision formatting
- Boost `mp_float` mode precision formatting
- persistence between `double` and `mp_float`

The detailed test matrix is documented in:

```text
tests\ATC_AUTOMATED_TEST_CASES.md
```

## Memory improvements

The 2.1.7 codebase now avoids several avoidable large allocations and leaks:

- `ascending order(...)` and `descending order(...)` allocate temporary numeric
  arrays according to the number of values submitted, and release those arrays
  before returning
- `fft(...)` and `ifft(...)` allocate sample/result arrays using the real sample
  count instead of `DIMDOUBLE`
- even-length `fft(...)` uses bounded half-size loops, avoiding reads outside
  the logical input range
- statistics menu operations now free temporary arrays and allocate population
  arrays according to the number of submitted values
- dynamic character-array helpers clamp copies to the destination capacity and
  force `\0` termination
- dynamic deletion helpers no longer clear full buffers immediately before
  `delete[]`, avoiding unnecessary writes across large arrays
- normal and long character-array deletion helpers now use the correct `DIM`
  and `LONGDIM` capacities
- the update checker now closes WinHTTP handles on successful requests and uses
  `std::string` ownership for the response buffer
- repeated date/time parsing paths now use small stack buffers instead of
  allocating `DIM`-sized temporary character arrays
- alphabetical sorting normalization now uses small stack buffers for
  one/two-character replacement keys instead of repeated `DIM` allocations
- the global `forsprintf` buffer is reused during `mainType()` startup instead
  of being overwritten by a second allocation
- the dynamic-allocation tracker is disabled by default in normal builds, so
  internal diagnostics such as `Variable-> ... variableData-> ...` are not
  printed during interactive calculations
- `function study(...)` now releases the `poleZerosR` and `poleZerosI` dynamic
  arrays before returning, avoiding repeated memory growth in that analysis
  path
- Release linker settings now define heap reserve/commit explicitly. Release
  x64 uses `/HEAP:150000000,4194304`; Release Win32 uses
  `/HEAP:50000000,1048576`. Stack reserve/commit remains explicit through the
  Visual Studio linker fields instead of duplicated `/STACK` options.

Memory stress validation is available through:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-memory-stress.ps1 -Iterations 10
```

The stress runner currently covers repeated polynomial simplification,
roots-to-polynomial, and textual/coefficient equation solver commands. The
latest 10-iteration run measured these peak working-set ranges in Release x64:

```text
simplify polynomial(...)       ~115-117 MB
roots to polynomial(...)       ~115 MB
solve equation(x^2-5*x+6)      ~141 MB
solve equation(1\8\1\_42)      ~144 MB
solve equation(x^7-12)         ~165 MB
```

These changes were build-verified and the command-line regression suite remains
green:

```text
Summary: 122 passed, 0 failed
```

## Build command

Release x64 build:

```powershell
& 'C:\Program Files\Microsoft Visual Studio\18\Insiders\MSBuild\Current\Bin\MSBuild.exe' '.\Advanced Trigonometry Calculator.sln' /p:Configuration=Release /p:Platform=x64 /m:1
```

Expected executable:

```text
x64\Release\atc.exe
```

## Known remaining validation gaps

The following areas from the user guide are intentionally not part of the
automatic suite yet:

- PC control commands such as shutdown, restart, hibernate, lock
- time features that run continuously or open clock/timer views
- app folder commands that open Explorer or editors
- ASCII sorting, because it enters a custom interactive loop
- interactive modules for statistics, matrices, finance, physics, conversions
  and microeconomics

## Operational notes

The test runner temporarily touches:

```text
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator\higherPrecision.txt
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator\aboutDisabled.txt
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator\variables.txt
```

It backs up and restores their previous contents.
