# ATC 2.1.9 portability audit — first delivery

Date: 2026-10-07
Baseline: `18fb797db78afcf69bd3ee329a50d12c6065c4ec` (`v2.1.8`)

## Scope and invariants

This first pass does not change the parser, solver, mathematical algorithms,
operator precedence, numerical formulas, messages, or tests. Its only source
change is a minimal CMake build description for a compiler-driven portability
probe.

## Repository structure

- Main Windows solution: `Advanced Trigonometry Calculator.sln`.
- Main executable entry point: `Advanced Trigonometry Calculator/main.cpp`.
- Legacy application and mathematical implementation: the `.cpp` files under
  `Advanced Trigonometry Calculator/`.
- Public headers and shared declarations: `atc_core.h`, `atc_functions.h`,
  `calc.h`, `precision_types.h`, `safe_chararray.h`, and `safe_index.h`.
- Parser/core/solver files referenced by Visual Studio: expected below `src/`,
  but absent from this repository and all reachable history.
- Tests: PowerShell regression, package, SRS, benchmark, and Windows Terminal
  scripts under `tests/`. No native Linux test runner is present.
- Build tooling: Visual Studio solution/project plus Windows `.cmd` and
  PowerShell packaging scripts. There was no root CMake project before this
  change.
- External dependencies: Boost headers; Windows system libraries including
  WinHTTP, WinINet, Shell32, and DbgHelp. No vendored Boost tree is present.
- Resources: Windows `.rc`, `.ico`, installer scripts, documentation, sample
  scripts, polynomial/Vieta data, and text settings.

## Blockers for Linux

### 1. The published source tree is incomplete

The Visual Studio project references 48 files below `../src/commands`,
`../src/core`, `../src/math`, `../src/matrix`, `../src/parser`, and
`../src/polynomial`. None is present, there is no submodule, and the public
repository history has no `src/` tree. This also prevents a reproducible clean
MSVC build of the committed project as described by the `.vcxproj`.

A later filesystem search found the referenced tree in a separate local branch,
`atc-3.0-private-checkpoint`, under the 2026-06-09 Codex workspace. That tree
contains 64 tracked paths and originated in private ATC 3.0 work beginning with
commit `fa47aafd0c7b390e5c8f0cbfc85fb6f33080e2e5` on 2026-07-13. It is not part
of the 2.1.8 release lineage: the public release and private checkpoint diverge
after merge base `8949af4f66ac6579734bb10d6d99216f5752c783`, with one public-only commit
and 30 private-only commits. Copying that tree into 2.1.9 would import a new
parser, solver, command/session layer, and mathematical core, violating this
phase's compatibility constraint. The safe 2.1.9 correction is therefore to
remove the stale `../src` entries from the Visual Studio project, not to merge
the ATC 3.0 tree.

Priority: **Linux blocker and build-reproducibility blocker**.

### 2. Every legacy translation unit inherits Windows headers

Forty-one application `.cpp` files include `stdafx.h`. That header includes
`windows.h`, `conio.h`, `io.h`, `tchar.h`, `shellapi.h`, `tlhelp32.h`, the
Windows resource header, and a Windows implementation of `dirent.h`.

Priority: **Linux blocker**.

### 3. Direct Win32 behavior is mixed with application behavior

Representative dependencies include `ShellExecute`, `Sleep`, Win32 console
input/output, process inspection, file enumeration, crash handling, WinHTTP,
hard-coded `C:\\WINDOWS\\system32\\cmd.exe`, and command-shell deletion or
directory creation. The largest concentrations are in `commands.cpp`,
`data_processing_core.cpp`, `atc_core.cpp`, `settings.cpp`,
`main_aux_processor.cpp`, `graph.cpp`, and `auto_complete.cpp`.

Priority: **Linux blocker**.

### 4. Microsoft CRT and console extensions

The code uses `_getch`, `conio.h`, `io.h`, secure CRT `_s` functions and other
underscore-prefixed runtime functions. Several calls rely on Microsoft-specific
signatures rather than portable C/C++ APIs.

Priority: **Linux blocker** where compilation fails; **important** where the
behavior or error handling differs.

### 5. Filesystem and persistence semantics

Settings and runtime data are coupled to Windows paths, backslashes, shell
commands, and the current working directory. Case-sensitive filename behavior
has not been encoded in tests. The repository also contains filenames with
spaces and mixed capitalization that need exact spelling on Linux.

Priority: **important**, becoming a blocker for affected commands.

## Important portability risks

- The codebase does not state a language standard in the Visual Studio project;
  the bootstrap selects C++17 so MSVC and GCC receive one explicit contract.
- Windows `long double` generally has the same precision as `double`, while
  Linux x86_64 GCC commonly uses extended precision. Exact formatting,
  tolerances, overflow boundaries, NaN/Infinity propagation, and rounding can
  consequently differ even when `pow`, `sqrt`, trigonometric, logarithmic, and
  exponential calls are standard-conforming.
- Windows crash handling, updater behavior, URL/document launching, hibernation
  commands, console styling, and legacy XP imports need platform policy rather
  than mechanical POSIX substitutions.
- PowerShell-only regression runners do not yet prove identical behavior on
  Linux. Tests should be made data-driven or wrapped by a portable runner before
  changing expected output.
- Text resources need a controlled UTF-8 policy. Git currently only declares
  `* text=auto`; output encoding and console code-page assumptions remain to be
  audited at runtime.

Priority: **important**.

## Optional improvements

- Add CI jobs for Ubuntu 22.04 and 24.04 after the first GCC build works.
- Add CMake presets after the minimal command-line workflow stabilizes.
- Replace shell-based file operations with `std::filesystem` behind a small
  platform boundary.
- Add explicit fixed-width integer types only where serialization or binary
  layout requires them; do not mechanically replace arithmetic types.
- Normalize formatting and line endings separately from functional changes.

## Affected files, grouped by concern

- Build graph: `Advanced Trigonometry Calculator.vcxproj`, new root
  `CMakeLists.txt`, and the absent `src/` tree.
- Global platform coupling: `stdafx.h`, `targetver.h`, `resource.h`, `winres.h`,
  `dirent.h`, and all `.cpp` files including `stdafx.h`.
- Windows-only units: `check_for_updates.cpp`, `crash_handler.cpp`,
  `xp_compat.cpp`, `xp_compat_imports.asm`, Windows resources, Commander, and
  Launcher sources.
- Highest mixed-platform complexity: `commands.cpp`,
  `data_processing_core.cpp`, `atc_core.cpp`, `settings.cpp`,
  `main_aux_processor.cpp`, `graph.cpp`, `auto_complete.cpp`, `scripting.cpp`,
  `numerical_systems.cpp`, and `time.cpp`.
- Tests/build scripts: all current scripts under `tests/` and `tools/` are
  Windows-oriented and require a portable execution path, not changed expected
  results.

## First concrete alteration

The root `CMakeLists.txt` describes the committed legacy executable sources,
requires Boost headers, keeps the existing Windows-only units on Windows, and
excludes only the updater, crash handler, and XP compatibility units on Linux.
It deliberately does not hide the remaining Win32 coupling: the first GCC run
should identify the exact compiler frontier before any compatibility layer is
designed.

The Visual Studio project and filter file were also corrected by removing only
the stale `../src` entries. Legitimate 2.1.8 additions such as `atc_core.cpp`,
`atc_core.h`, `xp_compat.cpp`, the MASM XP import source, and their build
customizations were preserved. Both XML files parse successfully and every
remaining `ClCompile`, `ClInclude`, and `MASM` path exists in the checkout.

Expected commands:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

## Regression risk

- Current change: **low**. No existing Visual Studio files or runtime sources
  are modified, and no mathematical behavior changes.
- Next step (`stdafx.h` split plus platform abstraction): **medium**, because
  console input, timing, shell launching, and persistence are intertwined with
  command execution.
- Parser/solver/math modifications: **not authorized by this phase**. Any such
  need discovered by GCC must first be documented and covered by regression
  evidence.

## Verification status

- Repository and CMake source inventory: checked.
- Existing Visual Studio project inventory: repaired; no referenced compile,
  include, or MASM path is missing after removal of the stale ATC 3.0 entries.
- CMake configure: invoked with CMake 4.4.3. Source parsing reached compiler
  detection, then stopped with `No CMAKE_CXX_COMPILER could be found`.
- Linux compile/build: not executable on this Windows host because neither WSL
  nor GCC/Clang is installed. It must be run on Ubuntu or CI next.
- Windows MSBuild inventory now reaches toolchain selection. The default build
  requires the unavailable legacy `v141_xp` toolset. A modern `v143` attempt
  located the compiler after the stale source references were removed, but the
  host build process stopped on its duplicated `Path`/`PATH` environment and
  sandboxed temporary-directory access before compiling. This is an environment
  limitation rather than a source diagnostic.
- Windows regression suite: not run because no executable was produced. Runtime
  edits are limited to platform declarations, the standard `main` signature,
  and compatibility wrappers; mathematical code remains unchanged.

## Phase 2 compiler-driven results

The current host has no WSL distribution, Docker/Podman, or native Linux GCC.
An Ubuntu 22.04 GCC workflow was therefore added as the authoritative Linux
build. A locally installed Emscripten 6.0.8 Clang/sysroot was used only as a
supplementary POSIX syntax probe; it is not presented as a substitute for GCC.

Initial `main.cpp` probe:

- 1 cascading `dirent.h` error caused by the application source directory being
  placed on the global include path;
- 2 leaked Win32 types (`BOOL` and `HWND`) in the common declarations;
- 1 non-standard `void main` diagnostic.

After removing the unnecessary global include directory, isolating the Win32
declaration, using `bool` for cursor visibility, and changing `main` to return
zero after the unchanged application call, `main.cpp` compiles successfully in
the POSIX probe. It emits only three pre-existing unused-static-function
warnings from `stdafx.h`.

The first whole-target syntax pass produced approximately 187 errors before
stopping in `commands.cpp`. Most were cascades from four causes:

- Microsoft CRT: repeated `gets_s` calls;
- non-standard template lookup: `convert2Exponential` was declared after the
  template that invokes it;
- shared platform primitives: `Sleep` and `TRUE`/`FALSE`;
- direct Win32 blocks: `ShellExecute`, process snapshots, Windows file
  enumeration, console types, `_getch`, and related constants.

A minimal `platform/atc_platform.h` now supplies only bounded line input,
millisecond sleeping through `std::this_thread::sleep_for`, and legacy Boolean
constants on non-Windows builds. The template declaration was moved before its
use without changing its implementation. `arithmetic_matrix_solver.cpp`, which
previously reported 13 errors, now passes the POSIX syntax probe.

The next precise blocker is `atc_core.cpp`: 10 errors, all from two Windows-only
blocks. One enumerates processes and launches `atc_launcher.exe`; the other
creates directories through `cmd.exe` and `ShellExecute`. They require explicit
platform policy. They have intentionally not been replaced with `system()`.

### `atc_core.cpp` resolution

The 10 `atc_core.cpp` errors are now reduced to zero in the POSIX compiler
probe.

- Process enumeration and `atc_launcher.exe` startup remain unchanged inside
  `_WIN32`. Linux skips only this external Windows launcher integration and
  continues into the common `on_start()` and main application flow.
- The former asynchronous `cmd.exe` directory creation was replaced by
  `atcCreateDirectories` and `atcJoinPath` in `platform/atc_platform.h`.
- Windows uses `GetFileAttributesA` and recursive `CreateDirectoryA`, both
  compatible with the XP target. POSIX uses `stat`, `mkdir`, and validates
  `EEXIST` as an existing directory.
- The exact required tree is created: the selected folder and its `Strings`
  child. The `hasFolder.txt` marker is written only after both directories are
  available. No `system()` or `std::filesystem` is used.

The nine `auto_complete.cpp` errors are now reduced to zero in the POSIX
compiler probe. The minimal platform layer now provides:

- regular-file name enumeration through the existing Win32 file APIs on
  Windows and `opendir`/`readdir`/`stat` on POSIX;
- a bounded, always-null-terminated string copy used in place of the
  Microsoft-only `strncpy_s` call;
- single-character terminal input using `_getch` on Windows and `termios` on
  POSIX, including translation of the four ANSI arrow sequences already used
  by the editor into its existing key codes;
- native path joining for the `User functions` directory and `history.txt`.

The ordered whole-target pass now confirms five consecutive units without
errors: `arithmetic.cpp`, `arithmetic_matrix_solver.cpp`, `atc_core.cpp`,
`auto_complete.cpp`, and `boolean_evaluator.cpp`.

The next blocker is `commands.cpp`, with 110 diagnostics. They remain heavily
cascaded: nearly all arise from repeated `ShellExecute`/`_T`/`LPCWSTR` usage,
plus one direct `CreateDirectoryA` site and two `Beep` sites. The affected
commands include opening URLs/files/folders, spawning ATC or `cmd.exe`, Windows
power-management operations, and several detached command windows. This is a
larger Windows-integration boundary and has only been mapped in this checkpoint;
`commands.cpp` itself remains unchanged. The separate functional correctness
backlog remains frozen.

### `commands.cpp` resolution

The initial 110 diagnostics were fully explained by repeated platform symbols:
63 `_T`, 28 `SW_SHOW` associated with 28 `ShellExecute` calls, 16 `LPCWSTR`,
one direct `CreateDirectoryA`, and two direct `Beep` diagnostics. The measured
reduction was `110 -> 109 -> 107 -> 0` after directory creation, beep, and the
shell/TCHAR group respectively.

The 28 shell calls were classified as six URL opens, one document open, four
ATC relaunches, six directory opens, five auxiliary console-window launches,
three maintenance operations, one PATH registration, and two power-management
operations. The minimal platform API now contains `atcOpenUrl`, `atcOpenFile`,
`atcOpenDirectory`, `atcLaunchExecutable`, `atcRemoveRegularFiles`, `atcBeep`,
and `atcSetConsoleTitle`.

Windows continues to use `ShellExecuteA`, `Beep`, and `SetConsoleTitleA`, all
available to the XP target. POSIX opens desktop resources with detached
`fork`/`exec` of `xdg-open`, launches ATC without a shell, emits the terminal
bell, and uses the standard terminal title escape. No `system()` was introduced
on Linux and no fake TCHAR aliases were added.

PATH registration, session/power operations, and the five auxiliary commands
that depend on separately sized Windows console windows remain explicitly
Windows-only. Linux recognizes them and reports that they are unavailable.
History, URLs, the user guide, ATC relaunch, and data-directory opening have
portable paths.

The ordered pass now confirms seven consecutive units through
`conversions.cpp`. The next blocker is `data_processing_core.cpp`, with 206
diagnostics: 70 unknown types, 126 undeclared identifiers, six missing global
API members, and four parser follow-ons. The main clusters are Win32 console,
input, window, shell, OS-version, and environment code; 119 diagnostics are
concentrated around lines 6000-6499. No correction to this broad next file was
started.

### `data_processing_core.cpp` resolution

The 206 diagnostics formed nine source clusters rather than 206 independent
defects: startup/runtime integration (8), mouse and screen clearing (18), PATH
and current-directory handling (14), reset shell commands and cursor control
(16), Windows version detection (15), mouse/console capability detection (9),
console layout/color/process launch (57), keyboard/mouse/window interaction
(62), and automatic window adjustment (7).

The measured reduction was `206 -> 26 -> 0`. The first step isolated the large
Win32 console, window, input, mouse, and OS-version blocks and supplied narrow
POSIX behavior. The remaining 26 diagnostics were exactly the two PATH shell
calls (8), two TCHAR current-directory blocks (6), and three startup reset shell
blocks (12); native current-directory and file removal eliminated them.

Existing platform functions were reused for paths, file/directory opening,
executable launch, regular-file removal, title setting, directory creation, and
sleeping. New small helpers are `atcStringsEqualIgnoreCase`,
`atcGetCurrentDirectory`, `atcClearKeyboardInput`, and
`atcRemoveFileInDirectory`.

Windows retains its original console sizing, positioning, coloring, mouse
automation, keyboard injection, Windows Terminal detection, `wt.exe`/`cmd.exe`
launch, and OS-version implementations under `_WIN32`. POSIX uses ANSI for
clear-screen, cursor visibility, color, and title; direct `fork`/`exec` for a
new ATC instance; `getcwd` for the current directory; and native file removal
for startup resets. Pixel window positioning, mouse automation, synthetic
keyboard input, and detailed terminal resizing remain Windows-only; the POSIX
paths are safe no-ops or retain logical dimension state where appropriate.

The ordered global probe now passes 11 consecutive translation units through
`dynamic_allocations.cpp`. The next blocker is `equation_solver.cpp`, with two
independent standard C++ template diagnostics: `getCorrectExponent<double>` is
called while only a non-template declaration is visible, and
`simpleSimplifyPolynomial<T>` attempts an illegal partial specialization of a
function template. These are not cascades and were not changed in this phase.

### `equation_solver.cpp` template conformance

The two diagnostics were declaration/definition syntax defects, not algorithm
defects.

- `getCorrectExponent` was defined as `template<typename T>` and explicitly
  instantiated for `double`, but its earlier declaration in `stdafx.h` was
  non-template. Adding the missing template introducer makes the declaration,
  call, definition, and explicit instantiation agree.
- `simpleSimplifyPolynomial` already had a correct function-template
  declaration. Its definition used `simpleSimplifyPolynomial<T>`, which is
  parsed as an attempted partial specialization; C++ does not permit partial
  specialization of function templates. The definition now uses the standard
  primary-template form `simpleSimplifyPolynomial(...)`.

No return type, parameter, function body, calculation, or call site changed.
Both corrections use long-established template syntax supported by MSVC and
the `v141_xp` toolset. `equation_solver.cpp` now passes the POSIX compiler
probe. Existing regression runners cover exponents, polynomial simplification,
and equation solving, but require a rebuilt Windows executable unavailable in
the current toolchain environment.

The ordered pass confirms 12 consecutive units through `equation_solver.cpp`.
The next blocker is `equations_system_solver.cpp`, with three independent
occurrences of the same illegal definition syntax: `rearrangeValues<T>`,
`showSolutions<T>`, and `getSolutions<T>`. They are standard C++ template
errors rather than Win32 or cascading diagnostics and were not modified.

### `equations_system_solver.cpp` template conformance

All three declarations were already correct function templates:
`rearrangeValues` and `getSolutions` in `calc.h`, and `showSolutions` in
`stdafx.h`. Their explicit `<T>` call sites were also correct. Only the three
definitions incorrectly repeated `<T>` after the function name, causing each
primary template definition to be parsed as an illegal function-template
partial specialization.

The definitions now use the standard forms `rearrangeValues(...)`,
`showSolutions(...)`, and `getSolutions(...)`. No declaration, return type,
parameter, call site, or function body changed. This conservative template
syntax is supported by GCC, MSVC, and `v141_xp`.

`equations_system_solver.cpp` now passes the POSIX probe. Two existing direct
regressions cover 2x2 systems, but the runner requires a rebuilt Windows
executable, which is unavailable in the current environment.

The global pass now confirms 16 consecutive units through
`geometry_calculations.cpp`. The next blocker is `graph.cpp`, with one fatal
Microsoft CRT/platform error: its unconditional `#include <io.h>` is not
available on POSIX. No `graph.cpp` change was started.

### `graph.cpp` platform-header resolution

`<io.h>` is required only by `_isatty` and `_fileno` in the Windows-only
interactive-console detector. The include was therefore moved inside the
existing `_WIN32` block; no POSIX replacement header is needed.

Removing that fatal include exposed two small platform boundaries that had
previously been hidden: the interactive-console state was declared only on
Windows although the common graph flow reads it, and the cursor helpers used
Win32 types directly. The common state now defaults to non-interactive and is
overridden by the existing Windows detector. `GoToXY` retains the Win32 console
API on Windows and uses an ANSI cursor-position sequence on POSIX;
`GetConsoleCursorPosition` remains Windows-only, matching its declaration.

Graph generation, expressions, points, axes, scales, navigation calculations,
and output layout were not changed. `graph.cpp` passes the POSIX probe and
`<io.h>` remains available to the XP-compatible Windows path.

The global pass now confirms 17 consecutive units through `graph.cpp`. The
next blocker is `hyperbolic.cpp`, with 18 template diagnostics: six primary
illegal function-template definition forms (`complex_cosh<T>`,
`complex_sinh<T>`, `complex_tanh<T>`, `arsinh<T>`, `arcosh<T>`, and
`artanh<T>`) plus 12 cascading undefined-template instantiation errors. No
change to that file was started.

### `hyperbolic.cpp` template conformance

The six declarations in `calc.h`, their template parameters, all explicit
`<T>` calls, and the two explicit instantiations (`double` and `mp_float`) per
function were already correct. Only the primary-template definitions repeated
`<T>` after the function name. The affected definitions were `complex_cosh`,
`complex_sinh`, `complex_tanh`, `arsinh`, `arcosh`, and `artanh`.

Removing `<T>` from those six definition names changes the invalid apparent
function-template partial specializations into standard primary-template
definitions. Parameters, return types, template parameters, call sites,
explicit instantiations, and every function body remain unchanged. In
particular, no hyperbolic formula, conversion, precision, domain rule, complex
handling, or error behavior changed. The conservative syntax is common to GCC,
MSVC, and `v141_xp`.

The isolated diagnostic count is `18 -> 0`; all 12 explicit-instantiation
diagnostics disappeared without further changes, confirming that they were
cascades. Existing regressions cover `sinh(0)`, `cosh(0)`, `tanh(0)`,
`asinh(0)`, `acosh(1)`, `atanh(0)`, and complex hyperbolic solver targets.
They were not run because the runner depends on a rebuilt Windows executable,
which is unavailable in this environment.

`git diff --check` passes. The ordered global probe now passes 21 consecutive
translation units through `main.cpp`. The next blocker is
`main_aux_processor.cpp`, with one platform diagnostic: the Microsoft CRT
function `_flushall` is undeclared on POSIX. It was classified but not changed.

### `main_aux_processor.cpp` output-flush boundary

The sole `_flushall()` call was at `main_aux_processor.cpp:2048`, inside the
`continu == 1` result-processing path. It occurs after the optional `fout`
stream has been closed and immediately before `verboseResolution.txt` is
opened for reading and `initialProcessor` is called. It does not precede
keyboard input, external execution, program termination, or state-file output.
Its functional intent is to make pending output visible before the next
processing phase, not to clear input.

A semantic `atcFlushOutputStreams()` operation was added to the platform
layer. Windows retains the historical `_flushall()` call. POSIX uses the
standard `fflush(nullptr)` operation, which flushes all open output streams;
no undefined `fflush(stdin)` behavior was introduced. The call site now uses
that abstraction. No parser, solver, calculation, message, command rule, or
control flow changed, and the Windows/MSVC/`v141_xp` behavior is preserved.

`main_aux_processor.cpp` diagnostics fell from `1 -> 0` in the supplementary
POSIX compiler probe, and `git diff --check` passes. The ordered global probe
now passes 22 consecutive translation units through
`main_aux_processor.cpp`. The next blocker is `main_processor.cpp`, with three
C++ interface diagnostics: two template calls (`math_processor` and
`variableValidator`) cannot infer `T`, and the visible one-argument
`variableController` declaration does not match a two-argument call. No change
to that file was started.

### `main_processor.cpp` interface and template conformance

The three diagnostics were independent call-interface defects. Both
`math_processor<T>(char*)` and `variableValidator<T>(char*)` were correctly
declared and defined as templates, but `T` does not occur in their function
parameters and therefore cannot be deduced from the original calls. Their
call sites already execute inside `main_processor<T>` and
`math_processor<T>`, respectively, so the existing active type is now selected
explicitly with `math_processor<T>(...)` and `variableValidator<T>(...)`.

`variableController` has one declaration and one matching definition,
`void variableController(char*)`, with no overload or default parameter. The
two-argument call was also present in the 2.1.8 source, but never matched an
interface. The implementation reads the global `resultR` and `resultI` values,
which are assigned immediately before this call. The extraneous `resultR`
argument was therefore removed, aligning the call with the existing interface
without changing the value source or behavior.

Compilation progressed `3 -> 2 -> 1 -> 0` after the three isolated call-site
corrections. No declaration, definition, parameter, return type, function body,
processing order, variable rule, parser, solver, message, or mathematical
operation changed. The syntax is standard and compatible with GCC, MSVC, and
`v141_xp`.

Existing regressions cover ordinary mathematical processing, variable
assignment and validation, variable persistence, valid names, and renamed
variables. They were not run because the suite requires a rebuilt Windows
executable unavailable in the current environment. `git diff --check` passes.

The ordered global probe now passes 26 consecutive translation units through
`physics_calculations.cpp`. The next blocker is
`polynomial_arithmetic.cpp`, with eight template diagnostics: four primary
definitions (`sum_polynomial<T>`, `sub_polynomial<T>`,
`multi_polynomial<T>`, and `div_polynomial<T>`) use the illegal apparent
function-template partial-specialization form, followed by four cascading
explicit-instantiation errors. It was classified but not changed.

### `polynomial_arithmetic.cpp` template conformance

The declarations of `sum_polynomial`, `sub_polynomial`, `multi_polynomial`,
and `div_polynomial` in `stdafx.h` were already correct primary function
templates. Their explicit `<T>` calls and explicit `double` instantiations were
also correct. Only the four definitions repeated `<T>` after the function
name, which is parsed as a forbidden function-template partial specialization.

The four definition names now use the standard primary-template form without
`<T>`. Return types, parameters, template parameters, calls, explicit
instantiations, and every function body remain unchanged. No polynomial sum,
subtraction, multiplication, division, normalization, coefficient, degree,
rounding, simplification, representation, or error behavior changed. The
syntax is common to GCC, MSVC, and `v141_xp`.

The isolated diagnostic count fell from `8 -> 0`. The four explicit-
instantiation errors disappeared without additional changes, confirming that
they were cascades. Existing regressions cover polynomial simplification and
products extensively, including rational factor cancellation/division,
roots-to-polynomial conversion, and equation solving. They were not run
because the suite requires a rebuilt Windows executable unavailable in the
current environment.

`git diff --check` passes. The ordered global probe now passes 29 consecutive
translation units through `safe_chararray.cpp`. The next blocker is
`scripting.cpp`, with 16 diagnostics: four Microsoft
`_set_printf_count_output` uses, three Microsoft console-input API uses, one
invalid `atcProgramming<T>` primary-template definition plus two cascading
instantiation errors, and six unsafe `mp_float` variadic `printf`/`sprintf`
arguments. This mixed platform/template/type-safety block was classified but
not changed.

### `scripting.cpp` portability and varargs conformance

The 16 diagnostics were resolved as four independent groups, with an isolated
compile after each group: `16 -> 13 -> 9 -> 6 -> 0`.

- `atcProgramming<T>` was the primary function-template definition, not a
  specialization. Only `<T>` was removed from its definition name. Both
  explicit-instantiation cascades then disappeared.
- `_set_printf_count_output` surrounds the two `%n` operations. Windows still
  enables and disables `%n` through the Microsoft CRT exactly as before.
  POSIX already supports `%n`, so only the four CRT configuration calls are
  confined to `_WIN32`; the format strings and `printf`/`sprintf` calls are
  unchanged.
- The three Microsoft console identifiers formed one interactive-input check
  and read. `atcIsInteractiveInput()` now selects `_isatty/_fileno` on Windows
  and `isatty/fileno` on POSIX, while the existing `atcGetChar()` preserves
  `_getch` on Windows and non-echo `termios` input on POSIX. The redirected
  `getchar()` and CR/LF path is unchanged.
- The six unsafe varargs calls were the `%e/%E`, `%g/%G`, and `%a/%A` paths in
  `print` and `sprint`. These C formats require a `double`; each calculated
  value is now explicitly converted through `precisionValueTo<double>` before
  entering the variadic call. Format strings, flags, width, precision,
  notation, and buffers are unchanged. This enforces the existing C-format
  contract and removes undefined passage of a non-trivial `mp_float`; it does
  not add a new precision truncation policy.

No scripting syntax, command name, tokenization, control flow, evaluation,
variable behavior, return value, functional message, file format, parser,
solver, or mathematical operation changed. The implementation remains
compatible with GCC, MSVC, and `v141_xp`. Existing formatted-print scripting
coverage and the script benchmark require a rebuilt Windows executable and
were not run in this environment.

`git diff --check` passes. The ordered global probe now passes 30 consecutive
translation units through `scripting.cpp`. The next blocker is `settings.cpp`,
with 29 diagnostics dominated by Win32 window, console, and keyboard APIs,
plus `_getch` and `_flushall`. This larger platform block was classified but
not changed.

### `settings.cpp` platform checkpoint

The 29 initial diagnostics were classified before modification: two `_getch`
uses, one `_flushall`, two console-buffer identifiers, 23 window/Win32
diagnostics (including cascades), and one `GetKeyState(VK_RETURN)` use. The
isolated probe progressed by logical group: `29 -> 27 -> 26 -> 1 -> 0`.

- The two single-character settings inputs now reuse `atcGetChar()`.
- The output synchronization point in `about()` now reuses
  `atcFlushOutputStreams()`; it was not treated as input cleanup.
- Existing semantic helpers handle console dimensions, window placement,
  maximization, and ANSI/Windows color application. Raw pixel measurement and
  fallback `MoveWindow` operations remain confined to `_WIN32`.
- POSIX initializes persisted window dimensions from the ATC logical values
  and uses the existing logical column default; Windows retains its rectangle
  and screen-buffer queries.
- The only new platform function is `atcEnterKeyPressed()`: Windows preserves
  `GetKeyState(VK_RETURN)`, while POSIX performs a non-blocking `select()` on
  standard input.
- The three legacy `system("color ...")` fallbacks are now Windows-only;
  POSIX uses the already-applied ANSI color path.

Settings names, defaults, persisted file names and formats, angular mode,
precision, command flow, parser, solver, and mathematics are unchanged. The
path/storage policy was not redesigned in this checkpoint. Existing
regressions cover modes, numerical systems, SI prefixes, verbose resolution,
time, dimensions/window persistence, settings readback, invalid-option retry,
auto-adjustment, graph settings, and missing/empty/malformed settings files.
They were not run because they require a rebuilt Windows executable unavailable
in this environment.

`settings.cpp` passes the supplementary POSIX syntax probe and
`git diff --check` passes. The ordered global probe now passes 36 consecutive
translation units through `time.cpp`. The next blocker is
`triangles_rectangles_solver.cpp`, with two independent Microsoft CRT
`_flushall` diagnostics. It was classified but not changed. The authoritative
Ubuntu 22.04 GCC workflow remains pending publication of the local changes.

### `triangles_rectangles_solver.cpp` stream-flush checkpoint

Both `_flushall()` calls were inspected separately. The first follows the
solver introduction and precedes each interactive iteration; it synchronizes
the output already presented before the cycle begins. The second follows the
normal `getValue<T>()` read of the hypotenuse and precedes the mathematical
branching. Neither call performs low-level keyboard handling or shows an
input-buffer cleanup requirement.

Both calls now reuse `atcFlushOutputStreams()`. Windows therefore retains the
historical `_flushall()` implementation, while POSIX uses `fflush(nullptr)`.
No `fflush(stdin)`, new abstraction, or input-clearing behavior was added.
The isolated diagnostic count is `2 -> 0`.

Only the two call names changed. Triangle/rectangle formulas, trigonometry,
validation, units, results, precision, messages, parser behavior, and control
flow are unchanged. The syntax remains compatible with MSVC and `v141_xp`.
An existing regression exercises the hypotenuse/angle path and verifies the
reported opposite side and hypotenuse. It was not run because the suite needs
a rebuilt Windows executable unavailable in this environment.

`git diff --check` passes. The ordered supplementary POSIX probe contains 38
translation units: 37 pass and one remains blocked. The sole blocker is the
last unit, `trigonometry.cpp`, with 18 diagnostics: six primary function-
template definitions use the invalid `function<T>(...)` form and 12 explicit-
instantiation diagnostics are cascades. It was classified but not changed.
The authoritative Ubuntu 22.04 GCC workflow remains pending publication.

### `trigonometry.cpp` template-conformance checkpoint

The six affected primary function templates are `complex_cos`, `complex_sin`,
`complex_tan`, `complex_asin`, `complex_acos`, and `complex_atan`. Their
declarations in `calc.h`, `template <typename T>` parameters, explicit `<T>`
calls, and explicit `double`/`mp_float` instantiations were already correct.
Only the definitions incorrectly repeated `<T>` after the function name,
making them look like forbidden function-template partial specializations.

The six definition names now use the standard primary-template form. No
parameter, return type, template parameter, call, explicit instantiation, or
function body changed. In particular, all direct, inverse, complex, angular,
domain, precision, normalization, parser, and message behavior remains
untouched. The syntax is common to GCC, MSVC, and `v141_xp`, with no
compiler-specific conditional.

The isolated diagnostic count fell from `18 -> 0`. All 12 explicit-
instantiation diagnostics disappeared after the six definition-name fixes,
confirming that they were cascades. `git diff --check` passes.

The supplementary local POSIX syntax-probe phase is now complete:

- Total translation units: 38
- Translation units PASS: 38
- Translation units blocked: 0

This is not yet a final Linux build. The next checkpoint is a real CMake/GCC
configure, compile, link, startup, and smoke-test run on Ubuntu 22.04. The
suggested temporary validation branch is
`codex/atc-2.1.9-linux-gcc-validation`; it has not been created or pushed.
The existing `Linux GCC portability build` workflow installs GCC, CMake, and
Boost, runs `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release`, then
`cmake --build build -j2`. After a successful link it uploads `build/atc` for
seven days as `atc-2.1.9-linux-experimental`, explicitly a diagnostic build
rather than an official distribution. Publishing the branch requires explicit
user authorization. No tag, release, merge, or functional-backlog work was
started.

The local validation branch was created from the exact 2.1.8 release commit
`18fb797db78afcf69bd3ee329a50d12c6065c4ec`. The removed `..\src\...` Visual
Studio entries were audited as stale private/modular ATC 3.0 references; the
four `v141_xp` configurations and public 2.1.8 sources remain. No private ATC
3.0 implementation is present in the proposed branch.

This host has no WSL distribution, Docker/Podman, or native GCC. Ubuntu CMake,
GCC, link, startup, and smoke tests are therefore not run. The attempted MSVC
Release x64 validation stopped before compilation with `MSB8020` because the
`v141_xp` toolset is unavailable; the project was deliberately not retargeted.

The first official Ubuntu 22.04 workflow run (`37736637304`) passed checkout,
dependency installation, and CMake Release configuration, then failed during
GCC compilation of `commands.cpp`. The first real errors are in the distro's
Boost 1.74 `is_unsigned.hpp`/`is_signed.hpp`: static trait values typed as an
internal unnamed enum are ODR-used during C++17 Release code generation and
GCC rejects their lack of linkage. Earlier diagnostics are non-fatal warnings.

A minimal local CMake correction adds `-fpermissive` only to `commands.cpp`
when the compiler ID is GNU. It does not alter ATC source behavior or any
Windows/MSVC setting, and avoids weakening diagnostics for the other 37 Linux
translation units. This correction has not been pushed; a confirming Ubuntu
run awaits explicit authorization.

Because `-fpermissive` can convert other conformance failures in
`commands.cpp` into warnings, it is documented as an experimental workaround
that must be removed in favor of a stricter solution. Two additional real GCC
errors in the same unit were corrected independently: `std::fabsl` was changed
to the standard overloaded `std::fabs` at the complex linear-solution
imaginary tolerance check and the root-ordering real tolerance check. Both
operands are `long double`, `<cmath>` is already present, and the `1E-12L`
tolerances and algorithms are unchanged.

The second Ubuntu 22.04 workflow run (`37737665054`) checked out `76719d6`,
passed CMake Release configuration, and compiled `commands.cpp`. The complete
log contains one subsequent fatal group in `data_processing_core.cpp`: the
explicit generic instantiation `convert2Exponential<PrecisionValue>` makes
Boost 1.74 signed/unsigned traits ODR-use internal unnamed-enum members. Its
four Boost errors share this root cause; the later build-system errors are
cascades, and the remaining compiler diagnostics are warnings.

The local correction declares a non-template `PrecisionValue` overload which
dispatches the existing `boost::variant<double, mp_float>` to the unchanged
numeric template specialization, and removes only the invalid/problematic
generic variant instantiation. This preserves the selected concrete value,
formatting, precision, and Windows/MSVC/`v141_xp` behavior. Isolated C++17
syntax probes for `data_processing_core.cpp` and `commands.cpp` pass, as does
`git diff --check`. The workflow did not reach link, artifact upload, startup,
or smoke tests; another authorized push/run is required for those validations.
