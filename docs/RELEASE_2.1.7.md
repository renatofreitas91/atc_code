# Advanced Trigonometry Calculator 2.1.7 release notes

Release date: 2026-06-09

## Highlights

- Added persistent switching between `double` and Boost `mp_float`.
- Fixed 50-decimal-place output for high precision constants such as `pi` and
  `e`.
- Fixed `solve equation(x^7-12)` and other simple textual polynomial equations.
- Fixed `simplify polynomial(...)` for simple textual polynomials and simple
  products of polynomial factors.
- Added an automatic regression suite based on the full user guide.
- Improved command-line automation for commands that export reports to `.txt`.
- Reduced RAM use and fixed several dynamic-allocation issues in sorting, DSP,
  statistics, update checking, startup and date/time parsing code paths.
- Added a memory stress runner for repeated polynomial simplifier,
  roots-to-polynomial and equation solver commands.
- Fixed direct `min(...)`, `max(...)` and `avg(...)` list calculations and
  validated the same functions with matrix variable names.
- Relaxed user variable-name restrictions while preserving exact reserved
  function, constant and numeric-prefix names.
- Added regression coverage for automatic multiplication deduction.

## Precision mode persistence

ATC now reads and writes:

```text
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator\higherPrecision.txt
```

Values:

- `0`: `double`
- `1`: Boost `mp_float`

Users can switch modes with:

```text
higherprecision(1)
higherprecision(0)
```

The selected mode is applied after restarting ATC.

## High precision fixes

The command:

```text
dp50dppi
```

now returns:

```text
3.14159265358979323846264338327950288419716939937511
```

The command:

```text
dp50dpe
```

now returns:

```text
2.71828182845904523536028747135266249775724709369996
```

Technical changes:

- fixed decimal output no longer uses `printf("%f")` with Boost multiprecision
  values
- `pi` and `e` use Boost constants in `mp_float` mode
- decimal-place parsing avoids contaminating result state for simple integer
  precision values

## Equation solver fixes

ATC now normalizes simple textual polynomial equations before passing them to
the coefficient-based solver.

Validated commands:

```text
solve equation(x+2)
solve equation(x^2-5*x+6)
solve equation(x^7-12)
```

Expected examples:

```text
solve equation(x+2)
x1=-2

solve equation(x^2-5*x+6)
x1=3
x2=2
```

For:

```text
solve equation(x^7-12)
```

ATC now returns seven roots:

```text
x1=1.42616
x2=0.889197+1.11502i
x3=0.889197-1.11502i
x4=-0.317351+1.3904i
x5=-0.317351-1.3904i
x6=-1.28493-0.618788i
x7=-1.28493+0.618788i
```

## Export automation

Commands that ask whether to export a report can now be driven by redirected
stdin in automated runs.

This supports test flows such as:

```text
1
C:\path\to\report.txt
```

Interactive use remains unchanged.

## Polynomial simplification fixes

`simplify polynomial(...)` now keeps `x` symbolic for simple textual polynomial
inputs instead of evaluating it as zero before simplification.

Validated commands now include:

```text
simplify polynomial(x)
simplify polynomial(x+1)
simplify polynomial(x+x+1)
simplify polynomial(x^2-5*x+6)
simplify polynomial((x-2)*(x-3))
simplify polynomial((x+1)*(x+1))
simplify polynomial((2*x+1)*(x-3))
```

Example:

```text
simplify polynomial((x-2)*(x-3))
(1+0i)x^2+(_5+0i)x^1+(6+0i)
```

## Memory and allocation fixes

Several 2.1.7 code paths no longer reserve large global buffers when the input
size is known:

- numeric sorting now allocates result buffers based on the number of submitted
  values and frees them before returning
- `fft(...)` and `ifft(...)` allocate numeric buffers based on the number of
  samples instead of `DIMDOUBLE`
- the even-size `fft(...)` loop no longer reads past the logical end of the
  input and no longer depends on oversized zero-filled arrays
- statistics menu operations free temporary arrays and allocate list buffers
  based on the number of submitted values
- dynamic string helpers now consistently preserve null termination and handle
  null inputs more safely
- deletion helpers now release arrays directly instead of clearing every element
  immediately before `delete[]`
- normal and long character-array deletion helpers now use the correct buffer
  capacity when validating before release
- update checking now owns the HTTP response with `std::string` and closes
  WinHTTP handles before returning
- startup reuses the global `forsprintf` buffer instead of leaking the first
  allocation
- date/time command paths now use small stack buffers for two/four-character
  fields instead of allocating `DIM`-sized temporaries
- alphabetical sorting normalization now avoids repeated `DIM` allocations for
  one/two-character replacement keys
- the dynamic-allocation tracker is disabled by default so internal
  `Variable-> ... variableData-> ...` diagnostics no longer appear in normal
  interactive output
- `function study(...)` now releases `poleZerosR` and `poleZerosI` before
  returning, avoiding repeated memory growth in that path
- Release builds now set linker heap reserve/commit explicitly
  (`x64: /HEAP:150000000,4194304`; `Win32: /HEAP:50000000,1048576`) and remove
  duplicate manual `/STACK` options from `AdditionalOptions`

## Variable-name improvements

ATC now accepts broader Latin-letter variable names such as `data`, `energy`,
`beta`, `alpha`, `matx`, `matrixvar`, `sinx` and `bvar`. This removes many
legacy single-letter parser restrictions without allowing exact collisions with
reserved names such as `sin`, `log`, `pi`, `e`, `i`, `B`, `O`, `H`, `P`, `D`,
`b`, `min`, `max` and `avg`.

The parsing changes also protect guide syntaxes that use internal delimiter
letters, including `rtD...D(...)` and `logb...b(...)`.

## Automatic multiplication coverage

The suite now validates inferred multiplication across constants, functions,
parentheses, imaginary values, custom guide syntax and variables. Covered forms
include `2pi`, `pi2`, `2e`, `2sin(pi/2)`, `sin(pi/2)2`, `2(3+4)`,
`(1+1)(2+3)`, `2i`, `3(2i)`, `2rtD4D(16)`, `2logb2b(8)`, `2x`, `x2`,
`x(4)`, `(4)x`, `xy` and `x y`.

Composite variable names keep priority after whitespace normalization. If `xy`
exists, `xy` and `x y` resolve to that variable; if only `x` and `y` exist, the
same forms resolve as `x*y`.

## Regression testing

New files:

```text
tests\run-atc-regression.ps1
tests\run-atc-memory-stress.ps1
tests\ATC_AUTOMATED_TEST_CASES.md
```

Run:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1 -AtcExe .\x64\Release\atc.exe
```

Current result:

```text
Summary: 122 passed, 0 failed
```

Memory stress run:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-memory-stress.ps1 -Iterations 10
```

Latest Release x64 10-iteration peak working-set observations:

```text
simplify polynomial(...)       ~115-117 MB
roots to polynomial(...)       ~115 MB
solve equation(x^2-5*x+6)      ~141 MB
solve equation(1\8\1\_42)      ~144 MB
solve equation(x^7-12)         ~165 MB
```

Covered areas:

- arithmetic
- constants
- trigonometry and inverse trigonometry
- hyperbolic and inverse hyperbolic functions
- logarithms
- custom arithmetic/log guide syntax: `rest`, `quotient`, `rtD...D`,
  `logb...b`, `afact`
- matrix/list guide syntax: `min`, `max`, `avg`, including matrix variables
- matrix guide helpers: `linsnum`, `colsnum`, `getlins`, `getcols`
- relaxed variable names persisted through `variables.txt`
- automatic multiplication deduction
- digital signal processing: `sinc`, `fft`, `ifft`
- probability/statistics inline functions
- sorting with `.txt` report export
- roots-to-polynomial report export
- textual polynomial simplification
- quadratic equation solver
- 2x2 equations system solver
- textual polynomial equation solver
- coefficient-form cubic equation solver
- `double` and Boost `mp_float` precision behavior
- restart persistence of precision mode

## Build verification

Release x64 build succeeds with MSBuild:

```powershell
& 'C:\Program Files\Microsoft Visual Studio\18\Insiders\MSBuild\Current\Bin\MSBuild.exe' '.\Advanced Trigonometry Calculator.sln' /p:Configuration=Release /p:Platform=x64 /m:1
```

## Known limitations

The automatic suite intentionally avoids:

- shutdown, restart, hibernate, sleep and lock commands
- clock, stopwatch and timer views
- commands that open folders, browsers or editors
- ASCII sorting custom interactive mode
- deeply interactive modules such as conversions, finance, physics,
  microeconomics, matrix and statistics menus

## Files touched in this release work

Important code areas:

```text
Advanced Trigonometry Calculator\main.cpp
Advanced Trigonometry Calculator\commands.cpp
Advanced Trigonometry Calculator\main_aux_processor.cpp
Advanced Trigonometry Calculator\processing_core.cpp
Advanced Trigonometry Calculator\scripting.cpp
Advanced Trigonometry Calculator\stdafx.h
Advanced Trigonometry Calculator\dynamic_allocations.cpp
Advanced Trigonometry Calculator\digital_signal_processing.cpp
Advanced Trigonometry Calculator\sorting.cpp
Advanced Trigonometry Calculator\statistics_calculations.cpp
Advanced Trigonometry Calculator\check_for_updates.cpp
Advanced Trigonometry Calculator\versioninfo.rc
```

Documentation and tests:

```text
docs\ATC_2.1.7_DOCUMENTATION.md
docs\RELEASE_2.1.7.md
tests\ATC_AUTOMATED_TEST_CASES.md
tests\run-atc-regression.ps1
```
