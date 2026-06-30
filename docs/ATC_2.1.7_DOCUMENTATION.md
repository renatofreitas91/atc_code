# Advanced Trigonometry Calculator 2.1.7 - current technical documentation

Date: 2026-06-09
Last updated: 2026-06-27

This document describes the current state of ATC 2.1.7 after the precision,
equation solver, regression-test, Windows console, documentation and
memory-improvement work.

## Scope of 2.1.7

ATC 2.1.7 focuses on making precision mode predictable between application
restarts, fixing high precision formatting, improving command-line testability,
adding automatic regression coverage based on the full user guide, improving
Windows 11 console behavior, and reducing unnecessary dynamic allocation in
common numeric paths. It also relaxes previous variable-name restrictions while
preserving exact reserved names.

## Documentation Map

Use these documents together:

- `docs/en/User_Guide_Full.md`: complete user-facing guide and Quick Start;
- `docs/en/ATC_Cookbook.md`: practical recipes and usage workflows;
- `docs/en/Best_Practices.md`: reliable usage and bug-report practices;
- `docs/en/Architecture.md`: module architecture and execution flow;
- `docs/en/Developer_Guide.md`: high-level source overview;
- `docs/en/Developer_Reference.md`: contribution checklists and practical
  development notes;
- `docs/SOFTWARE_REQUIREMENTS_SPECIFICATION.md`: formal requirements,
  acceptance criteria and traceability reference;
- `docs/en/Testing.md`: regression, isolated coverage and manual gaps.

## What ATC is not

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

## Recipes / Usage Profiles

These examples summarize practical ways to approach ATC 2.1.7. They use
documented commands and validated behavior where stable output is shown.

### Engineering

- Objective: solve a supported polynomial equation.
  Command: `solve equation(x^2-5*x+6)`.
  Expected stable output: `x1=3`, `x2=2`.
  Use when a polynomial equation fits the documented solver paths.
- Objective: create and reuse a matrix.
  Command: `create matrix(foo\2\2\3)`, then `foo+foo`.
  Use when matrix values should be stored and reused.
- Objective: use guided physics or unit conversion workflows.
  Command: `physics calculations` or `unit conversions`.
  Output: example placeholder, because these are interactive menus.

### Education

- Objective: demonstrate precedence.
  Command: `2+3*4`.
  Expected stable output: `#0=14`.
- Objective: demonstrate trigonometry in radian mode.
  Command: `sin(pi/2)`.
  Expected stable output: `#0=1`.
- Objective: use guided geometry workflows.
  Command: `geometry calculations`.
  Output: example placeholder, because this is an interactive menu.

### DSP

- Objective: evaluate signal helpers.
  Command: `sinc(0)`.
  Expected stable output: `#0=1`.
- Objective: process short numeric sequences.
  Command: `fft(1\0\0\0)`.
  Use for documented DSP examples involving list-style input.

### Statistics

- Objective: calculate list average.
  Command: `avg(2\4\6)`.
  Expected stable output: `#0=4`.
- Objective: inspect list bounds.
  Commands: `min(3\_1\2)` and `max(3\_1\2)`.
  Expected stable outputs: `#0=-1` and `#1=3`.
- Objective: use guided statistical calculations.
  Command: `statistics calculations`.
  Output: example placeholder, because this is an interactive menu.

### Finance

- Objective: use guided financial calculations.
  Command: `financial calculations`.
  Output: example placeholder, because this is an interactive menu.
- Objective: calculate a simple percentage directly.
  Command: `100*15/100`.
  Expected stable output: `#0=15`.

## Interactive prompt and autocomplete

The ATC interactive prompt now uses a custom line editor that supports
Linux-style Tab completion and history navigation while preserving the existing
command-processing architecture.

Current behavior:

- `Tab` completes documented commands, mathematical functions, aliases and
  user functions available in the ATC `User functions` folder;
- if there is more than one possible completion, repeated `Tab` presses cycle
  through the alternatives;
- matches are ordered by shortest closest match first, then by
  case-insensitive alphabetical order;
- completions insert the useful call prefix, for example `sin(`, `solver(` or
  `solve equation(`, so the user can continue typing the argument;
- `Up` and `Down` navigate previous expressions from `history.txt`;
- `Left`, `Right`, `Home`, `End`, `Delete` and `Backspace` provide normal line
  editing;
- completion suggestions are cached for the current input line to avoid
  rebuilding the full vocabulary on every repeated `Tab` press.

This feature is implemented before the expression reaches `main_core<T>()`.
It helps input ergonomics only; mathematical interpretation remains in the
existing parser and command-processing modules.

## Documentation policy

Project documentation should be maintained in Portuguese and English from this
point forward. Code comments, when present, should be written in English only.

The repository README was rewritten as a professional English open-source
README and published to the GitHub `main` branch in commit:

```text
f71e507 Improve project README
```

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

Additional 2.1.7 fast-path validation covers exact rational cancellation and
symbolic constants such as `pi`, `e` and complex `pii`.

Validated examples include:

```text
solve equation(((x-5)(x+2))/(x-5))
solve equation((((x-5)(x+2))/(x-5))*(((x-5)(x+pi))/(x-5))*(((x-5)(x+e))/(x-5)))
solve equation(((x-e+pii)(x-e-pii))/(x-e-pii))
solver(((x-5)(x+2))/(x-5))
solver((x-e+pii)(x-e-pii))
solver((((x-e+pii)(x-e-pii))/(x-e+pii))*(((x-e+pii)(x-e-pii))/(x-e-pii))*(((x-e+pii)(x-e-pii))/(x-e+pii)))
```

These paths must not bypass the normal output flow or print results before the
main processing core.

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

Rational polynomial products with exact cancellable factors are also covered in
the regression suite, for example:

```text
simplify polynomial(((x-5)(x+2))/(x-5))
simplify polynomial((((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5)))
```

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

## Windows 11 console behavior

Windows 11 commonly hosts console applications inside Windows Terminal. This
host does not behave like the classic console window for all background,
viewport and window-position operations, so ATC 2.1.7 disables the graphical
intro by default on Windows 11.

Technical behavior:

- Windows 11 detection uses `RtlGetVersion` loaded dynamically from
  `ntdll.dll`, avoiding unreliable `GetVersionEx` results on modern Windows.
- The traditional intro remains available on older Windows versions and can
  still be controlled by the existing intro commands and marker files.
- Windows Terminal color handling uses a Win32-to-ANSI color mapping so ATC
  color `3` remains aqua/cyan instead of becoming ANSI yellow.
- `new tab`, `new instance`, `new atc tab` and `new atc instance` attempt to
  launch ATC through `wt.exe new-tab` and fall back to a classic `cmd.exe`
  window when Windows Terminal is not available.
- The Windows 11 intro is intentionally disabled by default because Windows
  Terminal does not reliably preserve the classic console viewport behavior
  used by the original intro.

## Verbose resolution

Verbose resolution is persisted in:

```text
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator\verboseResolution.txt
```

Accepted values:

- `0`: disabled
- `1`: enabled

Interactive and direct command forms are supported:

```text
verbose resolution
verbose resolution(1)
verbose resolution(0)
```

The setting is no longer applied globally during startup. ATC keeps verbose
output disabled while loading the application and only enables it for the
calculation explanation phase. This avoids internal startup noise while still
showing useful resolution steps such as `initialProcessor`, `arithSolver`,
simplified expressions and the final result for the user's expression.

The verbose trace was also cleaned so display-only trailing `+0` terms are not
printed for user expressions, function arguments are shown as evaluated
arguments, and internal menu input evaluation remains quiet even when verbose
resolution is enabled.

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

Current validated result for both Release x64 and Release x86:

```text
Summary: 374 passed, 0 failed
```

The isolated coverage helper currently validates:

```text
Summary: 68 passed, 0 failed
```

The SourceForge package validation helper currently validates:

```text
Summary: 44 passed, 0 failed
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
- direct matrix/vector indexing and persisted indexed matrix updates, for
  example `foo[0][1]`, `foo[1][2]=99` and `foo=foo[1][2]=99` in one session
- relaxed variable names, including names that start with or contain letters
  previously reserved by parser shortcuts
- automatic multiplication with constants, functions, parentheses, imaginary
  values, guide delimiters and variables
- DSP functions: `sinc`, `fft`, `ifft`
- probability/statistics inline functions: `gerror`, `gerrorinv`,
  `gerrorc`, `gerrorcinv`, `qfunc`, `qfuncinv`
- numeric sorting with report export
- ASCII and inverse ASCII sorting interactive flows
- roots-to-polynomial report export
- textual polynomial simplification, including simple factor products
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
- long-running time command branches, plus safe smoke checks for
  `stopwatch(1)`, `clock(0:0:0)`, `big clock(0:0:0)` and timer syntax guards
- verbose-resolution persisted setting, cleaned verbose output behavior, and
  suppression of verbose traces for internal menu inputs
- Windows 11 console source-level behavior checks
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
- `processTxt()` now releases temporary answer arrays used while processing TXT
  and script commands
- `arithSolver()` now releases temporary amplitude/sign arrays on the normal
  return path
- `initialProcessor()` now allocates matrix scratch matrices lazily, so scalar
  script expressions do not reserve matrix buffers they never use
- common script `print("...", ...)` statements can now bypass the temporary
  TXT-processing file path and execute directly in memory
- simple scalar script assignments, loop conditions and integer `print`
  arguments now use a lightweight in-memory evaluator, with fallback to the
  full expression engine for unsupported expressions
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

The multiplication-table script benchmark is available through:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-script-benchmark.ps1 -AtcExe .\x64\Release\atc.exe
```

Latest Release x64 validation:

```text
Summary: 4 passed, 0 failed
ElapsedSeconds: 7.41
PeakWorkingSetMB: 119.56
```

These changes were build-verified and the command-line regression suite remains
green:

```text
Summary: 374 passed, 0 failed
```

Release x86 and Release x64 were rebuilt successfully with MSBuild. Both
builds report `0 Warning(s), 0 Error(s)`.

## Build command

Release x64 build:

```powershell
& 'C:\Program Files\Microsoft Visual Studio\18\Insiders\MSBuild\Current\Bin\MSBuild.exe' '.\Advanced Trigonometry Calculator.sln' /p:Configuration=Release /p:Platform=x64 /m:1
```

Expected executable:

```text
x64\Release\atc.exe
```

Release Win32/x86 builds are also supported by the solution and are used as a
compatibility target for older Windows versions. The current regression suite
has been validated against both `x64\Release\atc.exe` and `Release\atc.exe`.

## Known remaining validation gaps

The following areas from the user guide are intentionally not part of the
automatic suite yet:

- PC control commands such as shutdown, restart, hibernate, lock
- full-duration time features that run continuously or open clock/timer views
- commands that open external browsers or editors
- full live manual graph rendering and live key-buffer behavior
- remaining branches inside deeply interactive modules such as triangles,
  arithmetic matrix solver, finance, physics, conversions, statistics menus and
  microeconomics

## Operational notes

The test runner temporarily touches:

```text
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator\higherPrecision.txt
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator\aboutDisabled.txt
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator\variables.txt
```

It backs up and restores their previous contents.

## Resumo em portugues

Este documento descreve o estado tecnico atual do Advanced Trigonometry
Calculator 2.1.7. A versao 2.1.7 concentra-se em tornar a transicao entre
`double` e Boost `mp_float` previsivel entre reinicios, corrigir formatacao de
alta precisao, reforcar os caminhos de `solve equation`, `solver` e
`simplify polynomial`, melhorar o comportamento da consola no Windows 11,
reduzir consumo de memoria e aumentar a cobertura automatizada baseada no guia
de utilizador.

Pontos principais:

- o README publico do repositorio foi reescrito em ingles e publicado no branch
  `main` do GitHub no commit `f71e507 Improve project README`;
- a documentacao do projeto deve passar a ser mantida em portugues e ingles;
- comentarios no codigo, quando existirem, devem ficar apenas em ingles;
- `higherprecision(1)` e `higherprecision(0)` controlam a persistencia entre
  `double` e Boost `mp_float`;
- `verbose resolution`, `verbose resolution(1)` e `verbose resolution(0)` estao
  suportados, sem ativar logs verbosos durante o arranque interno;
- os caminhos rapidos de solver/equation cobrem cancelamentos racionais exatos,
  constantes simbolicas `pi`, `e` e casos complexos com `pii`;
- a suite automatizada valida atualmente `359 passed, 0 failed` em Release x64
  e Release x86;
- a cobertura isolada valida atualmente `65 passed, 0 failed`, incluindo
  autocomplete, navegacao por historico e ramos de comandos interativos;
- x64 e Win32/x86 continuam a ser alvos de build, mantendo compatibilidade com
  Windows antigo e Windows 11.
