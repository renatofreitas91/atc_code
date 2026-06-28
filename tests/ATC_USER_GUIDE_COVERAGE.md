# ATC User Guide Coverage Matrix

Source document:

```text
C:\Users\renat\OneDrive\Documentos\Advanced Trigonometry Calculator\Advanced Trigonometry Calculator\x64\Advanced Trigonometry Calculator - User Guide.pdf
```

This file tracks the documented ATC surface so release 2.1.7 does not forget
commands that are described in the user guide. The automated smoke suite covers
safe, deterministic command-line cases. Interactive, GUI, PC-control and
external-link commands are intentionally kept as manual coverage.

Documentation-only additions such as the Quick Start, ATC Cookbook, Best
Practices and Developer Reference should use commands already present in this
matrix whenever possible. If a documented recipe cannot be executed safely in
automation, it should remain clearly marked as an interactive/manual workflow.

## Automated

These areas have direct automated regression tests in
`tests/run-atc-regression.ps1`.

| Guide area | Covered commands/features |
| --- | --- |
| Arithmetic | `+`, `-`, `*`, `/`, `^`, `_`, `!`, `sqrt()`, `cbrt()`, `afact()`, `abs()`, `rest()`, `quotient()`, `rtD D()` |
| Constants | `pi`, `e` through `ln(e)`, `true`, `false`, `INF`, decimal precision prefixes |
| Trigonometry | `cos()`, `acos()`, `sin()`, `asin()`, `tan()`, `atan()`, `sec()`, `asec()`, `cosec()`, `acosec()`, `cotan()`, `acotan()` |
| Hyperbolic | `cosh()`, `acosh()`, `sinh()`, `asinh()`, `tanh()`, `atanh()`, `sech()`, `asech()`, `cosech()`, `acosech()`, `cotanh()`, `acotanh()` |
| Digital signal processing | `sinc()`, `fft()`, `ifft()` |
| Logarithms | `log()`, `ln()`, `logb b()` |
| Statistics / probability functions | `gerror()`, `gerrorinv()`, `gerrorc()`, `gerrorcinv()`, `qfunc()`, `qfuncinv()` |
| Lists and matrix variables / Matrizes | `create matrix()`, `min()`, `max()`, `avg()`, `linsnum()`, `colsnum()`, `getlins()`, `getcols()`, row/column range extraction, direct matrix/vector indexing with `[]`, persisted indexed update, matrix `+`, `-`, `*`, `^2`, `^T`, `^R` |
| Sorting / Ordenacao | `ascending order()`, `descending order()`, `ascii order()`, `inverse ascii order()` |
| Polynomial tools | `roots to polynomial()`, `simplify polynomial()` |
| Equation tools | `solve quadratic equation()`, `solve equations system()`, `solve equation()` |
| Function study | rational even/odd function studies and simple parabolas `x^2`, `_x^2` |
| Graphing | `graph settings` display and mutation, non-interactive `graph()` smoke output, deterministic navigation simulation for left/right arrows, edge clamping and explicit graph-range navigation |
| Time and calendar / Tempo | `time`, `calendar()`, `actual time response`, `time difference calculations`, `day of week()` |
| TXT and command bridge / Ponte TXT-comandos | `predefine txt`, `solve txt` missing-predefined guard, full real-file `solve txt` flow with mocked answer-file opening, `atc over cmd` redirected smoke/error/multiline flows, mocked `atc from cmd`, mocked `to solve`, mocked `enable txt detector`, mocked `eliminate strings` |
| File/folder commands / Comandos de ficheiros-pastas | quoted path handling in `predefine txt`, missing-file safe path for `open txt()`, missing abbreviation path in `solve txt()`, existence of ATC target folders, and installed guide/license/example/source files |
| Variables/results management / Gestao de variaveis-resultados | `see variables`, `renamed variables`, `eliminate variables`, `see results`, `eliminate results`, `see strings`, `see abbreviations`, `eliminate abbreviations`, including populated and empty readback states |
| Persistent settings / Configuracoes persistentes | `current settings`, `mode`, `numerical systems`, `si prefixes`, `verbose resolution`, `higher precision`, `actual time response`, `dimensions`, `window`, persisted `colors.txt` readback |
| Interactive menus / Menus interativos | invalid-choice retry and persistence for `mode`, `numerical systems`, `si prefixes`, `verbose resolution`, `actual time response`, plus `higher precision` interactive and inline forms |
| Deep interactive modules / Modulos interativos profundos | safe runtime smoke paths for `unit conversions`, `microeconomics calculations`, `physics calculations`, `statistics calculations`, `geometry calculations`, `financial calculations`, `triangles rectangles solver`, and `arithmetic matrix solver` |
| App environment / Ambiente UI | `enable atc intro`, `disable atc intro`, `clean`, `clean history`, `exit` and the `exit.txt` marker |
| Windows 11 console behavior | static coverage for Windows 11 intro default-disable logic, `RtlGetVersion` detection, Windows Terminal color mapping and `new tab` / `new instance` fallback |
| Interactive prompt | Tab autocomplete vocabulary, repeated-Tab cycling, dynamic user-function suggestions and Up/Down history navigation |
| PC-control commands | source-level coverage for command exposure, autocomplete exposure and Windows target actions for shutdown, restart, hibernate, log off, sleep and lock; runtime execution remains intentionally blocked |
| SourceForge package | `run-atc-package-validation.ps1` checks staged package root files, x64/x86 runtime folders, generated PDFs, absence of duplicated source folders/generated answers, GitHub source notices and SHA256 checksums |
| Precision mode | `higherprecision(1)`, `higherprecision(0)`, persistent `double`/`mp_float`, temporary `maxprec` prefix and post-`maxprec` double fallback |
| Automatic multiplication | constants, functions, parentheses, imaginary unit, variables, variable-constant adjacency and variable-function adjacency |
| Variable names | relaxed variable-name handling, function/reserved-prefix names and composite-variable priority |
| Export prompts | text-file export path and declined export path for equation/sorting/polynomial reports |

## Manual Or Isolated Test Needed

These commands are documented, but should not be run blindly in the default
smoke runner because they open windows, mutate user settings, require a custom
interactive session, depend on external services, or control the operating
system. Most command branches below are verified by
`tests/run-atc-isolated-coverage.ps1`; full human interaction is still manual.

| Guide area | Commands/features | Reason |
| --- | --- | --- |
| App environment | `auto adjust window`, `about`, `history`, `user guide`, `run atc`, `restart atc` | `about` and `auto adjust window` have redirected runtime coverage; isolated source-level coverage verifies command exposure, expected file/process targets and setting writes for the whole group; full runtime interaction remains manual for commands that open Notepad/PDFs or launch ATC processes |
| Updates and links | `check for updates`, `update`, `update x64`, `update portable`, `donate`, `atc facebook`, `atc sourceforge` | Isolated source-level coverage verifies autocomplete exposure, update-check endpoint, SourceForge installer/ZIP targets and external link URLs; full runtime execution remains manual because these commands use network/download/browser side effects |
| Reset/settings screens | `reset all`, `reset all now`, `reset settings`, `reset settings now`, interactive `colors` mutation | Isolated source-level coverage verifies autocomplete exposure, `onStart.txt` markers, relaunch behavior for `now` commands, reset file groups and `colors.txt` persistence; full runtime execution remains manual because reset commands delete user settings/data and `colors` uses `_getch()` |
| File/folder helpers | Runtime opening of `atc folder`, `source code`, `scripts examples`, `user functions`, `strings`, `auto solve txt`, and existing-file `open txt` | Isolated source-level coverage verifies autocomplete exposure, Explorer targets, `auto solve txt` watcher flow, quote/space normalization for `open txt`, and the guard that only opens Notepad when the file exists; `to solve` now has mocked runtime coverage, while full runtime execution remains manual for commands that open Explorer/Notepad or wait for file flags |
| TXT detector and command bridge | physical answer-file opening and `roots to polynomial` inside `solve txt` input files | Direct `predefine txt` -> `solve txt`, including arithmetic, `solver`, `solve equation`, `simplify polynomial`, invalid-line recovery, `auto solve txt` with a real `SOLVE_NOW` watcher fixture, `enable txt detector`, `atc from cmd`, `to solve`, and `eliminate strings`, is now covered with safe mocks. Remaining gaps: physical answer-file opening and `roots to polynomial` inside TXT require dedicated fixtures |
| Deep interactive modules | Remaining menu branches inside `triangles rectangles solver`, `arithmetic matrix solver`, `financial calculations`, `geometry calculations`, `statistics calculations`, `physics calculations`, `unit conversions`, `microeconomics calculations` | The default runner now covers one safe smoke path per module; exhaustive per-option coverage is still future work |
| Graphing | Full manual console rendering and live key-buffer behavior | Core settings mutation, deterministic left/right navigation, edge clamping and explicit range movement are covered through automated non-interactive fixtures; physical arrow-key input remains manual |
| Long-running time tools | `stopwatch()`, `run stopwatch()`, `timer()`, `run timer()`, `run big timer()`, `clock()`, `run clock()`, `big clock()`, `run big clock()` | Isolated coverage verifies all command branches, short `stopwatch(1)` marking, zero-duration `clock`/`big clock` execution and timer syntax guards; full-duration countdowns, alarms and opened `run` windows remain manual |
| PC control runtime execution | `shutdown`, `shutdown now`, `restart pc`, `restart pc now`, `hibernate`, `log off`, `sleep`, `lock` | Source-level/autocomplete/target-action coverage exists; executing these commands remains unsafe for automation |

## Source Extraction Note

The PDF was extracted locally to inspect its command surface. The extracted
text is intentionally not required by the runner; this matrix is the maintained
release checklist.
