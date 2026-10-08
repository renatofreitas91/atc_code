# ATC 2.1.9 Linux build

## Supported bootstrap environment

- Ubuntu 22.04 x86_64
- GCC/G++ from Ubuntu `build-essential`
- CMake 3.20 or newer
- Boost development headers

Install dependencies:

```sh
sudo apt-get update
sudo apt-get install --yes build-essential cmake libboost-all-dev
```

Configure and build:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

If linking succeeds, run from the repository root so the legacy relative data
files remain discoverable during this bootstrap phase:

```sh
./build/atc
```

## Current status

The repository contains a GitHub Actions workflow at
`.github/workflows/linux-gcc.yml` using `ubuntu-22.04`. The current Windows host
does not have WSL, Docker, or a native Linux GCC environment, so the workflow is
the authoritative route to the first GCC diagnostic log.

The first portability change makes `stdafx.h` include Win32 SDK, console, shell,
resource, and compatibility headers only when `_WIN32` is defined. Standard C++
and Boost headers remain common. On POSIX, only the narrow system headers needed
for directory enumeration, case-insensitive comparisons, terminal detection,
and file descriptors are introduced.

No parser, solver, evaluator, matrix, polynomial, complex, or mathematical
algorithm has been changed.

## Latest compiler frontier

A supplementary Emscripten/Clang POSIX syntax probe confirms:

- `main.cpp`: compiles;
- `arithmetic_matrix_solver.cpp`: compiles after the bounded-input compatibility
  wrapper and standard template-declaration ordering;
- `atc_core.cpp`: passes after conditioning launcher process handling to Windows
  and replacing directory creation through `cmd.exe` with the minimal platform
  API.
- `auto_complete.cpp`: passes after adding native regular-file enumeration,
  bounded string copy, path joining, and console character input to the minimal
  platform layer;
- `boolean_evaluator.cpp`: compiles without further changes;
- next blocker: `commands.cpp`, with 110 mostly cascading diagnostics from its
  repeated Windows shell/process integration, plus direct directory creation
  and beep calls.

No `commands.cpp` change was made at this checkpoint. Its Windows-only system
commands and its portable operations must be classified before introducing the
next narrow platform boundary.

The Ubuntu workflow must still be run to obtain the authoritative GCC count.

## Platform exclusions in the initial CMake build

The Linux target excludes these Windows-only translation units:

- `check_for_updates.cpp` — WinHTTP updater.
- `crash_handler.cpp` — Win32 exception and dump handling.
- `xp_compat.cpp` — Windows XP import compatibility.
- `xp_compat_imports.asm` — MASM/Windows XP import aliases; it is not part of
  the CMake source list.

The main program and legacy mathematical engine remain in the target. Other
Windows calls intentionally remain visible so GCC can identify the next minimal
compatibility boundary.

## Windows compatibility

All original Windows includes and pragmas remain active under `_WIN32`. No
`std::filesystem` dependency has been introduced, avoiding a premature conflict
with the historical `v141_xp` toolset. The existing Visual Studio solution and
Windows build scripts remain the Windows build authority.

## `commands.cpp` portability checkpoint

`commands.cpp` passes the supplementary POSIX syntax probe with zero errors.
The measured progression was `110 -> 109 -> 107 -> 0`: directory creation
reused the existing abstraction, beep gained a terminal-bell fallback, and the
remaining TCHAR/shell cascades were removed by intention-specific platform
functions or `_WIN32` confinement.

On Linux, `xdg-open` is executed directly through detached `fork`/`exec` for
URLs, files, and directories. ATC relaunches also use direct `exec`; no Linux
shell command construction or `system()` was added. Power/session commands,
PATH registration, and five separately sized console commands are recognized
but explicitly reported as Windows-only.

The global probe passes seven consecutive units, from `arithmetic.cpp` through
`conversions.cpp`. The next blocker is `data_processing_core.cpp`, with 206
mostly cascading Win32 diagnostics; it was classified but not modified.

The Ubuntu workflow could not be run against uncommitted workspace changes
without publishing a branch. The local probe remains supplementary and the
prepared Ubuntu 22.04 GCC workflow remains authoritative once published.

## `data_processing_core.cpp` portability checkpoint

`data_processing_core.cpp` now passes the POSIX syntax probe. Diagnostics fell
from `206 -> 26 -> 0`. Win32 console/window/input code remains intact under
`_WIN32`; POSIX uses small ANSI, terminal-input, current-directory, process,
and native file-removal paths without Win32 type aliases or shell commands.

The Linux presentation is intentionally simpler: pixel window placement,
mouse automation, keyboard injection, and precise console-window resizing are
Windows-only. Essential CLI behavior—screen clearing, cursor visibility,
colors, title, paths, startup reset processing, opening files, and launching a
new ATC instance—has a POSIX implementation.

The global probe passes 11 consecutive units through
`dynamic_allocations.cpp`. `equation_solver.cpp` is the next blocker with two
independent template-language errors, not a Win32 cascade. It remains
unchanged pending the next phase.

## `scripting.cpp` portability checkpoint

`scripting.cpp` now passes the supplementary POSIX syntax probe. Diagnostics
progressed `16 -> 13 -> 9 -> 6 -> 0`: primary-template syntax, Microsoft `%n`
configuration, interactive console input, and non-trivial `mp_float` varargs
were handled separately.

Windows retains `_set_printf_count_output` around `%n`, `_isatty/_fileno`, and
`_getch`. POSIX uses native `%n`, `isatty/fileno`, and the existing `termios`
character reader. Redirected input behavior remains unchanged. The six
`%e/%E`, `%g/%G`, and `%a/%A` arguments are explicitly converted to the
`double` required by the C variadic format contract; all format strings and
precision fields remain unchanged.

No scripting language, parser, control-flow, variable, output-format, or
mathematical behavior was redesigned. The syntax remains compatible with
MSVC/`v141_xp`. Existing scripting regression and benchmark runners require a
rebuilt Windows executable and were not run. `git diff --check` passes.

The global probe reaches 30 consecutive translation units through
`scripting.cpp`. The next blocker is `settings.cpp`, with 29 predominantly
Win32 console/window/input diagnostics, including `_getch` and `_flushall`. No
change to that larger platform block was started.

## `polynomial_arithmetic.cpp` template checkpoint

`polynomial_arithmetic.cpp` now passes the supplementary POSIX syntax probe.
The primary-template definitions of `sum_polynomial`, `sub_polynomial`,
`multi_polynomial`, and `div_polynomial` used the invalid `function<T>(...)`
form. Only `<T>` was removed from those four definition names.

Declarations, template parameters, parameters, calls, explicit `double`
instantiations, and mathematical bodies remain unchanged. Diagnostics fell
from `8 -> 0`; the four explicit-instantiation errors vanished with the four
primary corrections and were cascading diagnostics. The syntax remains
compatible with GCC, MSVC, and `v141_xp`.

The regression suite already covers polynomial products, simplification,
rational cancellation/division, roots conversion, and equation solving. It was
not run because it requires a rebuilt Windows executable unavailable in this
environment. `git diff --check` passes.

The global probe reaches 29 consecutive translation units through
`safe_chararray.cpp`. The next blocker is `scripting.cpp`, with 16 diagnostics
across Microsoft printf configuration, Microsoft console input, one invalid
template definition with two cascades, and six non-POD `mp_float` variadic
arguments. No change to that mixed block was started.

## `main_processor.cpp` interface checkpoint

`main_processor.cpp` now passes the supplementary POSIX syntax probe. Calls to
`math_processor` and `variableValidator` now explicitly select the `T` already
active in their enclosing templates because that type cannot be deduced from a
sole `char*` argument. The incompatible two-argument `variableController` call
now uses its sole declared and defined `char*` interface; the implementation
continues to consume the already assigned global `resultR` and `resultI`.

Diagnostics progressed `3 -> 2 -> 1 -> 0`. Only the three call sites changed;
declarations, definitions, bodies, processing flow, variable behavior, and
mathematics are unchanged. The corrections use standard syntax compatible
with GCC, MSVC, and `v141_xp`. Existing arithmetic and variable-management
regressions require a rebuilt Windows executable and were not run.

`git diff --check` passes. The global probe reaches 26 consecutive translation
units through `physics_calculations.cpp`. The next blocker is
`polynomial_arithmetic.cpp`, with four invalid primary-template definition
forms and four cascading explicit-instantiation errors (eight diagnostics in
total). No change to that file was started.

## `main_aux_processor.cpp` output-flush checkpoint

The one `_flushall()` call occurs after the current output file is closed and
before `verboseResolution.txt` is opened for reading and result processing
continues. It is an output synchronization point, not keyboard-input cleanup.

The call now uses `atcFlushOutputStreams()`. Its Windows implementation retains
`_flushall()` for historical MSVC/`v141_xp` behavior; its POSIX implementation
uses standard `fflush(nullptr)` to flush open output streams. No
`fflush(stdin)` or input-side behavior was added, and application flow is
unchanged.

`main_aux_processor.cpp` passes the supplementary POSIX syntax probe (`1 ->
0`) and `git diff --check` passes. The global probe reaches 22 consecutive
translation units. `main_processor.cpp` is the next blocker with three C++
interface/template diagnostics: two non-deducible template calls and one
call/declaration arity mismatch. It remains unchanged.

## `hyperbolic.cpp` template checkpoint

`hyperbolic.cpp` now passes the supplementary POSIX syntax probe. The six
primary-template definitions for `complex_cosh`, `complex_sinh`,
`complex_tanh`, `arsinh`, `arcosh`, and `artanh` used the non-standard
`function<T>(...)` definition form. Only `<T>` was removed from each definition
name. Declarations, template parameters, parameters, calls, explicit
instantiations, and mathematical bodies are unchanged.

Diagnostics fell from `18 -> 0`. The 12 explicit-instantiation errors vanished
with the six primary corrections and were therefore cascading diagnostics.
The syntax remains compatible with GCC, MSVC, and `v141_xp`.

Existing regression coverage exercises the six direct hyperbolic operations
at simple reference values and complex `sinh`, `cosh`, and `tanh` solver
targets. The suite was not run because it requires a rebuilt Windows
executable unavailable in the current environment. `git diff --check` passes.

The global probe now passes 21 consecutive translation units through
`main.cpp`. The next blocker is `main_aux_processor.cpp`, with one POSIX
portability error: `_flushall` is a Microsoft CRT function and is undeclared.
No change to that next file was started.

## `graph.cpp` portability checkpoint

`graph.cpp` now passes the POSIX syntax probe. `<io.h>` is included only on
Windows because its sole users are `_isatty` and `_fileno` in the Win32 console
detector. POSIX defaults to non-interactive graph output and uses ANSI for the
shared cursor-position operation. Graph calculations and formatting remain
unchanged, and the Windows/XP path retains its original console APIs.

The global probe passes 17 consecutive translation units. The next blocker is
`hyperbolic.cpp`, with six primary non-standard template definitions and 12
cascading explicit-instantiation diagnostics, for a total of 18. It remains
unchanged.

## `equation_solver.cpp` template checkpoint

`equation_solver.cpp` passes after two structural C++ corrections: the missing
template introducer was restored on the `getCorrectExponent` forward
declaration, and the `simpleSimplifyPolynomial` definition was changed from
illegal function-template partial-specialization syntax to normal primary
template definition syntax. Function bodies and mathematical behavior are
unchanged. The syntax is conservative and compatible with `v141_xp`.

The global POSIX probe now passes 12 consecutive translation units. The next
blocker is `equations_system_solver.cpp`, with three independent instances of
the same non-standard function-template definition form; it remains unchanged.

## `equations_system_solver.cpp` template checkpoint

The three errors are reduced to zero. Correct template declarations and
explicit `<T>` calls were preserved; only `<T>` was removed from the three
primary-template definitions. Mathematical bodies and interfaces are
unchanged, and the syntax remains compatible with `v141_xp`.

The global probe passes 16 consecutive translation units through
`geometry_calculations.cpp`. `graph.cpp` is the next blocker with one fatal
platform-header diagnostic: `<io.h>` is included unconditionally. It remains
unchanged pending the next phase.

## `settings.cpp` platform checkpoint

`settings.cpp` now passes the supplementary POSIX syntax probe. Its 29 initial
diagnostics were resolved in four semantic groups, with a compile after each:
`29 -> 27 -> 26 -> 1 -> 0`.

The two `_getch` calls reuse `atcGetChar()` and the output flush in `about()`
reuses `atcFlushOutputStreams()`. Existing platform helpers now cover console
dimensions, window application/maximization, and colors. Pixel window
measurement/positioning remains Windows-only. POSIX uses logical ATC dimension
defaults and ANSI colors. Three legacy Windows color shell fallbacks are
confined to `_WIN32`.

The sole new abstraction is `atcEnterKeyPressed()`: it preserves
`GetKeyState(VK_RETURN)` on Windows and uses a non-blocking POSIX `select()` on
standard input. This is conservative for MSVC/`v141_xp`; no compiler-specific
workaround was introduced.

No setting meaning, default, persisted file name/format, angular mode,
precision, parser, solver, or mathematical operation changed. The existing
settings regressions require a rebuilt Windows executable and were not run.
The broader path/storage policy was deliberately left outside this minimal
blocker fix.

`git diff --check` passes. The global probe reaches 36 consecutive translation
units through `time.cpp`. The next blocker is
`triangles_rectangles_solver.cpp`, with two `_flushall` diagnostics; it remains
unchanged. The Ubuntu 22.04 GCC workflow has not run because the changes are
still local.

## `triangles_rectangles_solver.cpp` stream-flush checkpoint

The first `_flushall()` follows the introductory output and precedes each
interactive solver iteration. The second follows the standard
`getValue<T>()` hypotenuse read and precedes mathematical branching. Both are
stream/output synchronization points; neither represents low-level keyboard
buffer cleanup.

Both now call the existing `atcFlushOutputStreams()`. Windows retains
`_flushall()` inside that abstraction and POSIX uses `fflush(nullptr)`. No new
helper and no `fflush(stdin)` were introduced. Diagnostics fell from `2 -> 0`.
All geometry, trigonometry, validation, units, precision, messages, and flow
remain unchanged, preserving MSVC/`v141_xp` compatibility.

The existing regression for the hypotenuse/angle path was identified but not
run because it requires a rebuilt Windows executable. `git diff --check`
passes.

Probe inventory:

- Total translation units no probe: 38
- Translation units PASS: 37
- Translation units ainda bloqueadas: 1

The remaining blocker is `trigonometry.cpp`, with six invalid primary-template
definition forms and 12 cascading explicit-instantiation errors (18
diagnostics). It remains unchanged. The Ubuntu 22.04 GCC workflow is still
pending publication of the local changes.

## `trigonometry.cpp` and completion of the syntax probe

The final six invalid definitions were `complex_cos<T>`, `complex_sin<T>`,
`complex_tan<T>`, `complex_asin<T>`, `complex_acos<T>`, and
`complex_atan<T>`. Each was the definition of a primary template already
declared correctly in `calc.h`. Calls and the `double`/`mp_float` explicit
instantiations were also correct.

Only `<T>` was removed from each definition name. Parameters, return types,
template parameters, calls, explicit instantiations, and mathematical bodies
are unchanged. Diagnostics fell from `18 -> 0`; the 12 instantiation errors
vanished without further edits and were therefore cascades. This standard
syntax remains compatible with GCC, MSVC, and `v141_xp`.

Final local probe result:

```text
Total translation units: 38
PASS:                    38
Blocked:                  0
```

`git diff --check` passes. This closes only the supplementary unit-level POSIX
syntax phase, not the final Linux build.

### Prepared Ubuntu validation

- Suggested branch: `codex/atc-2.1.9-linux-gcc-validation`
- Workflow: `.github/workflows/linux-gcc.yml`, named
  `Linux GCC portability build`, on Ubuntu 22.04
- Configure: `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release`
- Compile/link: `cmake --build build -j2`
- Expected logs: dependency installation, CMake configure/generate, GCC
  compile diagnostics, and linker result
- Expected transient output: `build/atc`
- Uploaded artifact after a successful link:
  `atc-2.1.9-linux-experimental` containing `build/atc`, retained for seven
  days and explicitly not presented as an official distribution

The branch has not been created or pushed. Publication awaits explicit user
authorization; no release, tag, merge, or functional-backlog change was made.
After a successful real build, validation should proceed to startup and Linux
smoke tests.

The proposed branch content comprises 20 modified tracked project/source
files, plus the new `CMakeLists.txt`, Linux workflow,
`platform/atc_platform.h`, and the two portability reports. Local
`build-portability/` and `work-portability-probe/` outputs are diagnostic
scratch data and must not be included in the branch.

The local validation branch was created at the exact public 2.1.8 base commit
`18fb797db78afcf69bd3ee329a50d12c6065c4ec`, preserving the full working tree.
No WSL distribution, Docker/Podman engine, or native GCC is available on this
host, so Ubuntu configure/compile/link cannot be run locally. A Windows Release
x64 build was attempted but stopped before compilation with `MSB8020` because
the `v141_xp` toolset is not installed. The project was not retargeted.

Current phase-2 status:

| Indicator | Result |
|---|---|
| Translation units POSIX | 38/38 PASS |
| CMake configuration Ubuntu | NOT RUN |
| GCC compilation | NOT RUN |
| Linux link | NOT RUN |
| `build/atc` | Not generated |
| First Linux startup | NOT RUN |
| Smoke tests | 0/0 (NOT RUN) |
| `git diff --check` | PASS |
| Windows XP | Preserved in code / toolset unavailable |
| Windows 11 | Preserved in code / build not reached |

### First Ubuntu 22.04 GCC run

GitHub Actions run `37736637304` configured and generated the Release build
successfully, then failed while compiling `commands.cpp`. The preceding
string-literal, format, and unused-value diagnostics are warnings and are not
the cause of failure. The first fatal group comes from the Ubuntu 22.04 Boost
1.74 headers: `boost::is_unsigned` and `boost::is_signed` instantiate static
members whose type is an internal unnamed enum, and GCC rejects their ODR use
under C++17 with “declared using unnamed type, is used but never defined”.

The local experimental branch now applies `-fpermissive` only to
`commands.cpp` and only when the CMake compiler is GNU. This confines the
compatibility exception to the one affected translation unit; ATC source,
algorithms, parser, solver, and MSVC/`v141_xp` flags are unchanged. The fix is
local and has not been pushed. A second Ubuntu run therefore remains pending
explicit authorization.

`-fpermissive` can also downgrade unrelated C++ conformance errors in
`commands.cpp` to warnings. It is therefore an explicitly experimental,
temporary workaround and should be removed once Boost/GCC compatibility is
resolved more rigorously. Independently, two genuine GCC library-surface
errors in that file used `std::fabsl`, which is not provided in the runner's
`std` namespace. Both arguments are `long double`; the calls now use the C++17
`std::fabs(long double)` overload. `<cmath>` was already included through
`stdafx.h`; both `1E-12L` tolerances and comparison logic are unchanged.

### Second Ubuntu 22.04 GCC run

GitHub Actions run `37737665054` checked out commit `76719d6`, configured the
Release build successfully, and confirmed that `commands.cpp` now compiles.
The build then failed in `data_processing_core.cpp`. Inspection of the complete
GCC log found one fatal group: the explicit generic instantiation of
`convert2Exponential<PrecisionValue>` forces Boost 1.74 signed/unsigned traits
to ODR-use the same internal unnamed-enum members. The four Boost diagnostics
are one root cause; the later `gmake` failures are cascades. All other compiler
diagnostics in this run are warnings. Link and artifact upload were not reached.

The minimal local correction replaces only that generic `PrecisionValue`
instantiation with a non-template overload. It inspects the existing
`boost::variant<double, mp_float>` and delegates to the unchanged `double` or
`mp_float` `convert2Exponential` implementation. No formatting, precision,
parser, solver, or mathematical algorithm changes. Isolated C++17 syntax
probes pass for both `data_processing_core.cpp` and `commands.cpp`, and
`git diff --check` passes. A new Ubuntu run is still required to validate the
full GCC compile and link; runtime remains unvalidated.

### Third Ubuntu 22.04 GCC run

GitHub Actions run `37738182961` checked out commit `c0a3783`, which contains
the non-template `PrecisionValue` overload and no explicit
`convert2Exponential<PrecisionValue>` instantiation. CMake Release configuration
and `commands.cpp` compilation passed, but `data_processing_core.cpp` still
failed with the same four Boost 1.74 unnamed-enum linkage diagnostics in
`is_unsigned.hpp` and `is_signed.hpp`; the three following `gmake` errors are
cascades. The remaining diagnostics in the complete 7,436-line log are
warnings. Link and artifact upload were not reached.

A local object-symbol inspection independently confirms that overload
resolution emits `convert2Exponential(double)`, `convert2Exponential(mp_float)`,
and the non-template `convert2Exponential(PrecisionValue)` only. It does not
emit `convert2Exponential<PrecisionValue>`. The rigorous dispatch correction is
therefore active, but the Ubuntu result disproves the earlier hypothesis that
this generic instantiation was the cause of the remaining Boost/GCC failure.
No additional `-fpermissive`, Boost-header modification, or speculative source
change was made. Runtime remains unvalidated.

### Boost 1.74/GCC root-cause investigation

The complete failure was reproduced independently with GCC 11.3 and the
Boost.Multiprecision 1.74 headers. The relevant instantiation chain is:

```text
ATC mixed mp_float comparison
  -> Boost.Multiprecision mixed relational operator enable_if
  -> number_category<B>::value comparison with number_kind_complex
  -> number construction/canonical classification of number_category_type
  -> boost::is_unsigned<number_category_type> / boost::is_signed<...>
  -> is_unsigned_values / is_signed_values anonymous-enum static members
```

GCC correctly rejects the required out-of-class definitions because the
members have the anonymous enum type, which has no linkage. The include route
from `stdafx.h` through Boost.Math `erf.hpp`, `gamma.hpp`, constants,
LexicalCast, and Boost.TypeTraits makes the failing traits visible, but does
not instantiate them and is not the cause.

An instrumented Boost 1.74 probe identified three ATC entry points: the
`PrecisionValue`/`mp_float` relational adapters in `precision_types.h`, the
zero comparisons in `complexNumber<mp_float>`, and `n < 0` in
`prefixDeterminator<mp_float>`. The adapters now use the existing
`mp_float::compare` member. The two data-processing functions use a small
sign helper whose `mp_float` overload compares the underlying backends; the
generic form retains the historical relational operations for other types.
Only the predicates were changed. Numeric values, transformations, output
formatting, precision, tolerances, parser, solver, and algorithms are intact.

Two minimal cases distinguish the library mechanism from the ATC call sites.
A direct `boost::is_signed`/`boost::is_unsigned` query for an anonymous enum
reproduces all four diagnostics. Constructing a `cpp_dec_float_50` from an
anonymous enum reproduces the same trait failure with Multiprecision 1.74.
The equivalent numeric probe compiles and runs with Boost 1.90. Boost commit
`8bb54d07fd7c` (first released in the 1.76 line) introduced Multiprecision's
standard integer traits and removed most Boost.TypeTraits use, explaining the
version difference without requiring an installed-header patch.

After the localized ATC changes, the instrumented 1.74 probe reports zero
matches for the failing `number_category_type` trait chain. The diagnostic
checkout and header overlay are untracked and do not modify installed Boost.
`git diff --check` passes. A real Ubuntu 22.04 workflow remains required to
confirm compilation and link; no runtime claim is made.

### Official validation of `9a11b4f` and Ubuntu TU bisection

Workflow `37765519036` tested SHA `9a11b4f2bbd6fabedd5a724ed331aacb51e7d060`.
Dependency installation and CMake Release configuration passed, as did
`commands.cpp`, but `data_processing_core.cpp` retained the same four anonymous
enum diagnostics. Link and artifact upload were not reached. This disproves the
local probe's zero-match result for the official environment and means the
commit did not meet Level A.

An isolated Ubuntu 22.04/GCC/Boost 1.74 diagnostic branch then reused the exact
CMake compile command with `-j1`, unlimited template backtrace, template-tree
display, and caret suppression. Boost headers alone, `precision_types.h` alone,
and `stdafx.h` alone all compile. Removing only `complexNumber<mp_float>`, each
explicit-instantiation group, or every explicit `mp_float` instantiation does
not change the four errors. Removing all identified non-template `mp_float`
dispatch sites also does not change them. The error is therefore in source
semantics compiled by the complete TU, not header inclusion or that adjacent
`complexNumber` log entry.

A diagnostic-only `-fpermissive` object (never linked or used as a product
result) exposed calls from `character_to_prefDet<mp_float>` to heterogeneous
`mp_float`/`double` comparisons, from `manageExpression<mp_float>` to
`mp_float`/`double` equality comparisons, and from
`variableValidator<mp_float>` to `mp_float`/`int` equality comparisons. These
are demonstrated contributors. However, typing all those temporary threshold
operands still leaves the same four Release diagnostics, so they are not yet a
complete causal set and no source correction has been adopted. The optimized
typed object emits no remaining `is_valid_mixed_compare` symbol even though GCC
reports the traits at end of compilation; further source-level bisection is
required before a permanent fix.

### Function-body quarter bisection

The diagnostic harness inventories 151 global bodies: 118 non-templates, 32
primary templates, and one explicit specialization. It replaces selected
bodies with signature-preserving `{ throw 0; }` stubs and records compile exit,
unsigned/signed fatal counts, and the first unrelated error. No case below
produced an unrelated error.

Population controls proved independent template and non-template triggers.
The truly isolated matrix was:

```text
isolated template Q1      PASS 0
isolated template Q2      PASS 0
isolated template Q3      FAIL 4
isolated template Q4      PASS 0
isolated non-template Q1  PASS 0
isolated non-template Q2  PASS 0
isolated non-template Q3  PASS 0
isolated non-template Q4  FAIL 4
```

Each of the 38 functions in the two failing quarters was compiled alone, with
every other body stubbed. Exactly two independently reproduce the four traits:
template `toSolve<T>` (inventory line 3955) and non-template
`isContainedInUserFunction` (line 6695). The other 36 isolated bodies pass.

For each trigger the harness generated a reduced source, ran the real CMake
command with `-E`, and compiled the resulting `.ii`. Both preprocessing steps
pass and both `.ii` files reproduce unsigned=2 and signed=2 with no prior
error. The large `.ii` files, objects, and logs remain runner-only. No product
source correction has been made.

### C-Reduce root cause: dirent `d_type` / `DT_REG`

The two independent C-Reduce jobs in workflow `37807689921` validated their
final reproducers. `toSolve<T>` fell from 185649 lines and 8508390 bytes to 45
lines and 1236 bytes; `isContainedInUserFunction` fell from 185488 lines and
8502542 bytes to the same 45-line, 1236-byte mechanism. Each final source keeps
exactly two `is_unsigned_values` and two `is_signed_values` errors.

Both reductions map to `dir->d_type == DT_REG`, at source lines 3979 and 6712.
On Ubuntu 22.04, `dirent::d_type` is `unsigned char` and `DT_REG` has the
anonymous enum type. The ATC global overload set admits a Boost.Multiprecision
candidate during `operator==` resolution; its conversion constraints classify
the enum through the broken Boost 1.74 signed/unsigned traits.

Workflow `37823242203` tested a diagnostic-only rewrite to fundamental `int`
on both operands:

```text
toSolve original                    FAIL 4 (unsigned=2, signed=2)
toSolve typed                       PASS 0
isContainedInUserFunction original  FAIL 4 (unsigned=2, signed=2)
isContainedInUserFunction typed     PASS 0
full TU original                    FAIL 4
full TU with both typed             PASS 0
```

An executable probe confirmed identical results for `DT_REG`, `DT_DIR`,
`DT_UNKNOWN`, and `DT_FIFO`. `int` is deliberate: the bundled Windows
`dirent.h` declares `d_type` as `int` and maps `DT_REG` to `S_IFREG`, so byte
narrowing would not preserve Windows values. The final product diff changes
only the two comparisons.

Official workflow `37824236815` confirms that `commands.cpp` and
`data_processing_core.cpp` compile. Compilation reached 71% and first failed
at `processing_core.cpp:364`, where GCC does not expose `std::fabsl`. Link and
artifact upload were not reached; that next blocker remains unmodified.

Visual Studio 2022 selected MSVC 14.16 and `v141_xp`, but the local build then
stopped before the changed TU because this checkout lacks its configured Boost
include directory. The expression uses syntax supported by that compiler, but
a complete Windows build and runtime validation remain pending.
