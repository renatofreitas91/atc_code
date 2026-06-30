# Advanced Trigonometry Calculator 2.1.7 release notes

Release date: 2026-06-09
Last updated: 2026-06-30

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
- Improved Windows 11 console behavior: the ATC intro is disabled by default on
  Windows 11, console colors are mapped correctly when Windows Terminal uses
  ANSI/VT sequences, and ATC can open new instances as Windows Terminal tabs
  when `wt.exe` is available.
- Improved `verbose resolution`: direct `verbose resolution(1)` and
  `verbose resolution(0)` commands are supported, and verbose output is no
  longer enabled during startup internals.
- Added exact rational-cancellation fast-path coverage for solver/equation
  paths using real roots, `pi`, `e` and complex `pii` constants.
- Added interactive prompt improvements: Tab completion, repeated-Tab cycling
  for ambiguous matches, broader command/function suggestions, dynamic user
  function suggestions and Up/Down history navigation.
- Improved script execution for common `print("...", ...)` statements by
  bypassing the temporary TXT-processing path when the line can be evaluated
  safely in memory.
- Reduced script memory pressure by freeing repeated TXT-processing arrays and
  allocating matrix scratch buffers only when matrix processing is actually
  needed.
- Rewrote and published the repository README to the GitHub `main` branch in
  commit `f71e507 Improve project README`.

## Documentation policy

Project documentation should be maintained in Portuguese and English from this
point forward. Code comments, when present, should be written in English only.

## Documentation improvements

ATC 2.1.7 documentation was expanded to make the project easier to learn,
test and contribute to:

- added a one-page Quick Start near the beginning of the user guides;
- added an ATC Cookbook with practical workflows and safe example commands;
- added Best Practices for reliable use and reproducible bug reports;
- expanded the Architecture Overview with module and execution-flow diagrams;
- added a Developer Reference with contribution checklists;
- reorganized the full user guide around a more natural learning path;
- linked user documentation, coverage notes and regression status more clearly;
- generated bilingual Markdown/PDF documentation and DOCX full user guides.

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

Additional validated rational and symbolic-constant cases include:

```text
solve equation(((x-5)(x+2))/(x-5))
solve equation((((x-5)(x+2))/(x-5))*(((x-5)(x+pi))/(x-5))*(((x-5)(x+e))/(x-5)))
solve equation(((x-e+pii)(x-e-pii))/(x-e-pii))
solver(((x-5)(x+2))/(x-5))
solver((x-e+pii)(x-e-pii))
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

Exact cancellable rational products are also covered, including:

```text
simplify polynomial(((x-5)(x+2))/(x-5))
simplify polynomial((((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5)))
```

## Verbose resolution

`verbose resolution` remains available as an interactive menu. ATC 2.1.7 also
supports:

```text
verbose resolution(1)
verbose resolution(0)
```

The setting is persisted in `verboseResolution.txt`, but it is no longer applied
globally during startup. This prevents verbose traces from internal startup
work while preserving useful calculation traces for user expressions.

Verbose output was also made easier to read: display-only trailing `+0` terms
are hidden, evaluated function arguments are labelled directly, function results
are printed without the old interactor wording, and internal menu prompts keep
their evaluation quiet even when verbose resolution is enabled.

## Interactive prompt and autocomplete

The main ATC prompt now supports line editing and autocomplete while the user
is writing an expression. Pressing `Tab` completes the closest documented
command, mathematical function, alias or user function. When several matches
are possible, repeated `Tab` presses cycle through them.

Autocomplete suggestions are ordered by shortest closest match first and then
case-insensitively. The same expression can receive multiple completions, which
is useful for longer mathematical input.

The prompt also supports `Up` and `Down` history navigation and normal cursor
editing keys. The completion list is cached per input line to avoid rebuilding
the vocabulary repeatedly while the user cycles suggestions.

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
- script execution now avoids repeated `processTxt()`/temporary-file overhead
  for simple `print("...", ...)` statements
- script execution now evaluates simple scalar assignments, loop conditions and
  integer `print` arguments through a lightweight in-memory path, while keeping
  the legacy parser as fallback for more complex expressions
- `processTxt()` now releases temporary answer arrays used while processing TXT
  and script commands
- `initialProcessor()` no longer allocates four large matrix scratch matrices
  for scalar expressions
- `arithSolver()` now releases temporary amplitude and sign arrays on the
  normal return path
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
tests\run-atc-script-benchmark.ps1
tests\ATC_AUTOMATED_TEST_CASES.md
```

Run:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1 -AtcExe .\x64\Release\atc.exe
```

Current result for both Release x64 and Release x86:

```text
Summary: 377 passed, 0 failed
```

Script benchmark validation for the `Multiplication Table 1-100` workflow:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-script-benchmark.ps1 -AtcExe .\x64\Release\atc.exe
```

Latest Release x64 result:

```text
Summary: 4 passed, 0 failed
ElapsedSeconds: 7.41
PeakWorkingSetMB: 119.56
```

Current isolated coverage result:

```text
Summary: 68 passed, 0 failed
```

Current SourceForge package validation result:

```text
Summary: 44 passed, 0 failed
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
- direct matrix/vector indexing and persisted indexed matrix updates
- relaxed variable names persisted through `variables.txt`
- automatic multiplication deduction
- digital signal processing: `sinc`, `fft`, `ifft`
- probability/statistics inline functions
- sorting with `.txt` report export
- ASCII and inverse ASCII sorting interactive flows
- roots-to-polynomial report export
- textual polynomial simplification
- exact rational polynomial cancellation in simplifier, solver and equation
  solver paths
- quadratic equation solver
- 2x2 equations system solver
- textual polynomial equation solver
- coefficient-form cubic equation solver
- high-degree coefficient equations and internal expanded polynomial forms
- graph settings display, graph settings mutation, graph smoke tests,
  deterministic graph navigation simulation, navigation edge clamping and
  explicit graph-range navigation
- TXT detector / command bridge commands, including `atc over cmd`, mocked
  `atc from cmd`, mocked `to solve`, mocked `enable txt detector`, safe
  `eliminate strings`, and real-file `solve txt` response generation
- file/folder command existence checks
- safe app-environment runtime paths, including `about` and
  `auto adjust window`
- safe runtime smoke coverage for deep interactive modules: unit conversions,
  microeconomics, physics, statistics, geometry, financial calculations,
  triangles rectangles solver and arithmetic matrix solver
- persistent settings and interactive menu retry behavior
- interactive prompt autocomplete vocabulary, repeated-Tab cycling and
  Up/Down history navigation
- long-running time command branches, short stopwatch marking, zero-duration
  clock checks and timer syntax guards
- verbose-resolution persisted setting, cleaned verbose output behavior, and
  suppression of verbose traces for internal menu inputs
- Windows 11 console source-level behavior checks
- `double` and Boost `mp_float` precision behavior
- restart persistence of precision mode

## Build verification

Release x64 build succeeds with MSBuild:

```powershell
& 'C:\Program Files\Microsoft Visual Studio\18\Insiders\MSBuild\Current\Bin\MSBuild.exe' '.\Advanced Trigonometry Calculator.sln' /p:Configuration=Release /p:Platform=x64 /m:1
```

Release Win32/x86 builds are also supported by the solution and remain a
compatibility target for older Windows versions. The current regression suite
has been validated against both `x64\Release\atc.exe` and `Release\atc.exe`.

The latest Release x86 and Release x64 builds completed successfully with
`0 Warning(s), 0 Error(s)`.

## Known limitations

The automatic suite intentionally avoids:

- shutdown, restart, hibernate, sleep and lock commands
- full-duration clock, stopwatch and timer views
- commands that open external browsers or editors, except for TXT/file flows
  covered through explicit test mocks
- full live manual graph rendering and live key-buffer behavior
- remaining branches inside deeply interactive modules such as triangles,
  arithmetic matrix solver, conversions, finance, physics, microeconomics and
  statistics menus

## Files touched in this release work

Important code areas:

```text
Advanced Trigonometry Calculator\main.cpp
Advanced Trigonometry Calculator\auto_complete.cpp
Advanced Trigonometry Calculator\commands.cpp
Advanced Trigonometry Calculator\dirent.h
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
README.md
```

Documentation and tests:

```text
docs\ATC_2.1.7_DOCUMENTATION.md
docs\RELEASE_2.1.7.md
tests\ATC_AUTOMATED_TEST_CASES.md
tests\ATC_USER_GUIDE_COVERAGE.md
tests\run-atc-regression.ps1
tests\run-atc-isolated-coverage.ps1
```
