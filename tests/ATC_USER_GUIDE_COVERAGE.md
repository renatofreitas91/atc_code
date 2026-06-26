# ATC User Guide Coverage Matrix

Source document:

```text
C:\Users\renat\OneDrive\Documentos\Advanced Trigonometry Calculator\Advanced Trigonometry Calculator\x64\Advanced Trigonometry Calculator - User Guide.pdf
```

This file tracks the documented ATC surface so release 2.1.7 does not forget
commands that are described in the user guide. The automated smoke suite covers
safe, deterministic command-line cases. Interactive, GUI, PC-control and
external-link commands are intentionally kept as manual coverage.

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
| Lists and matrix variables / Matrizes | `create matrix()`, `min()`, `max()`, `avg()`, `linsnum()`, `colsnum()`, `getlins()`, `getcols()`, matrix `+`, `-`, `*`, `^2`, `^T`, `^R` |
| Sorting / Ordenacao | `ascending order()`, `descending order()`, `ascii order()`, `inverse ascii order()` |
| Polynomial tools | `roots to polynomial()`, `simplify polynomial()` |
| Equation tools | `solve quadratic equation()`, `solve equations system()`, `solve equation()` |
| Function study | rational even/odd function studies and simple parabolas `x^2`, `_x^2` |
| Graphing | `graph settings` display and mutation, non-interactive `graph()` smoke output, and deterministic navigation simulation for left/right arrows |
| Time and calendar / Tempo | `time`, `calendar()`, `actual time response`, `time difference calculations`, `day of week()` |
| TXT and command bridge / Ponte TXT-comandos | `predefine txt`, `solve txt` missing-predefined guard, `atc over cmd` redirected smoke |
| File/folder commands / Comandos de ficheiros-pastas | quoted path handling in `predefine txt`, missing-file safe path for `open txt()`, missing abbreviation path in `solve txt()`, existence of ATC target folders, and installed guide/license/example/source files |
| Variables/results management / Gestao de variaveis-resultados | `see variables`, `renamed variables`, `eliminate variables`, `see results`, `eliminate results`, `see strings`, `see abbreviations`, `eliminate abbreviations`, including populated and empty readback states |
| Persistent settings / Configuracoes persistentes | `current settings`, `mode`, `numerical systems`, `si prefixes`, `verbose resolution`, `higher precision`, `actual time response`, `dimensions`, `window`, persisted `colors.txt` readback |
| Interactive menus / Menus interativos | invalid-choice retry and persistence for `mode`, `numerical systems`, `si prefixes`, `verbose resolution`, `actual time response`, plus `higher precision` interactive and inline forms |
| App environment / Ambiente UI | `enable atc intro`, `disable atc intro`, `clean`, `clean history`, `exit` and the `exit.txt` marker |
| Precision mode | `higherprecision(1)`, `higherprecision(0)`, persistent `double`/`mp_float`, temporary `maxprec` prefix and post-`maxprec` double fallback |
| Automatic multiplication | constants, functions, parentheses, imaginary unit, variables, variable-constant adjacency and variable-function adjacency |
| Variable names | relaxed variable-name handling, function/reserved-prefix names and composite-variable priority |
| Export prompts | text-file export path and declined export path for equation/sorting/polynomial reports |

## Manual Or Isolated Test Needed

These commands are documented, but should not be run blindly in the default
smoke runner because they open windows, mutate user settings, require a custom
interactive session, depend on external services, or control the operating
system.

| Guide area | Commands/features | Reason |
| --- | --- | --- |
| App environment | `auto adjust window`, `about`, `history`, `user guide`, `run atc`, `restart atc` | Manual/isolated checklist documented; opens windows, changes the console/window, or launches external UI |
| Updates and links | `check for updates`, `update`, `update x64`, `update portable`, `donate`, `atc facebook`, `atc sourceforge` | Network/external browser/update side effects |
| Reset/settings screens | `reset all`, `reset all now`, `reset settings`, `reset settings now`, interactive `colors` mutation | Broad configuration reset, restart side effects, or `_getch()`-based interactive input |
| File/folder helpers | Runtime opening of `atc folder`, `source code`, `scripts examples`, `user functions`, `strings`, `to solve`, `auto solve txt`, and existing-file `open txt` | Opens folders/files, waits for file watcher flags, or launches Notepad/Explorer |
| Strings cleanup | `eliminate strings` | Mutates `stringVariable.txt` and the `Strings` folder through shell commands |
| TXT detector and command bridge | `enable txt detector`, `atc from cmd`, `to solve`, full `solve txt` processing with opened answer file | Requires admin PATH mutation, shell windows, or a multi-process/file-watcher scenario |
| Interactive solvers | `solver()`, `triangles rectangles solver`, `arithmetic matrix solver`, `financial calculations`, `geometry calculations`, `statistics calculations`, `physics calculations`, `unit conversions`, `microeconomics calculations` | Menu-driven modules |
| Graphing | Full manual console rendering and live key-buffer behavior | Core settings mutation and left/right navigation logic are covered through automated non-interactive fixtures |
| Long-running time tools | `stopwatch()`, `run stopwatch()`, `timer()`, `run timer()`, `run big timer()`, `clock()`, `run clock()`, `big clock()`, `run big clock()` | Long-running/interactive time features |
| PC control | `shutdown`, `shutdown now`, `restart pc`, `restart pc now`, `hibernate`, `log off`, `sleep`, `lock` | Unsafe for automation |
| Matrix return/update workflows | Returning and updating matrix values from general expressions | Partially covered by matrix arithmetic variable fixtures; indexed update workflows still need dedicated tests |

## Source Extraction Note

The PDF was extracted locally to inspect its command surface. The extracted
text is intentionally not required by the runner; this matrix is the maintained
release checklist.
