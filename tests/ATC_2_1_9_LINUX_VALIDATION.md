# ATC 2.1.9 — Linux validation of the Windows checkpoint

Base commit: `e5c23e80446c2fa031fb17a4d11c5040a184cacc`.

Validation completed on Linux with GCC 15.2.0, CMake 4.2.3 and Boost 1.90, using C++17. The Linux fixes derive from the Windows checkpoint above. No merge with main or release is involved.

## Changes

- Guard negative indices in angular/polynomial solvers, expression scanning and script formatting; initialize and clear file handles after closing them.
- Define matrix scratch ownership and free buffers after their last use.
- Support Linux cursor editing, arrow navigation, UTF-8 console graphics, graph study bars and startup countdown updates.
- Recognize dropped TXT paths and locate script examples relative to the executable; preserve nested script data paths and execute for-loop initialization as an assignment.
- Use coefficient derivatives for function studies, isolating real roots between derivative roots and preserving repeated roots. Determine the image of higher-degree rational functions by joining the images of continuous monotone intervals, retaining excluded domain points and checking multiplicities at poles.
- Determine symmetry from polynomial identities and the original domain; omit yy intersections at excluded zero.

The previous polynomial derivative path used overlapping sprintf source/destination buffers. An extracted reproducer loses the leading term in GCC Release while retaining it under ASan. The function-study path now reuses the canonical coefficient derivative routine. General equation solving and multiprecision arithmetic are not replaced.

## Results

| Suite | GCC Release | Optimized ASan/UBSan | External-terminal LSan |
| --- | --- | --- | --- |
| Functional: 34 original + one rational regression | 35/35 | 35/35 | 35/35 |
| LF, CR, CRLF, EOF and input pseudo-terminal | 8/8 | 8/8 | 8/8 |
| Implicit products, lists, precision, angular solvers, Newton residual | 40/40 | 40/40 | 40/40 |
| Polynomial and rational studies | 26/26 | 26/26 | 26/26 |
| Dropped TXT paths and scripts | 7/7 | 7/7 | 7/7 |
| Interactive single/multiple graphs | 2/2 | 2/2 | 2/2 |
| Console editing, history and startup | 10/10 | 10/10 | 10/10 |
| Total | **128/128** | **128/128** | **128/128** |

The application source validated here is `4cfb6a26b74a8296c48674ca0f6830912b9ad0fa`. This consolidation changes tests/documentation only. The application tree, instrumented binary hash, case counts and log hashes are recorded in `ATC_2_1_9_LINUX_RESULTS.json`. Raw logs are retained in the local validation workspace and are not bundled in the repository.

The preceding `3109fe34290c8072ad93934f5a405e87301c7a44` checkpoint also passed 26/26 studies with GCC Debug and unoptimized ASan/UBSan; its six formerly failing expressions had byte-identical cleaned output in all four configurations. The latest 4cfb6a2 application source was revalidated in Release and optimized ASan/UBSan, including those same expressions: `x^3`, `x^4`, `x^3-3*x`, `1/(x^3)`, `x^3/(x^2+1)` and `x^4/(x^2+1)`.

Release flags: `-O3 -DNDEBUG -std=c++17`. Debug flags: `-O0 -g -std=c++17`. Sanitizer builds add `-fsanitize=address,undefined -fno-omit-frame-pointer -g` to equivalent optimization levels. No optimization was disabled to hide the defect.

## Reproduction

From the repository root, replace `/path/to/atc` with the executable to test:

```sh
python3 tests/run-atc-linux-functional.py /path/to/atc
python3 tests/run-atc-linux-input-smoke.py /path/to/atc
python3 tests/run-atc-linux-additional.py /path/to/atc
python3 tests/run-atc-linux-study.py /path/to/atc
python3 tests/run-atc-linux-scripts.py /path/to/atc
```

For ASan/UBSan validation use the instrumented executable and export:

```sh
export ASAN_OPTIONS=detect_leaks=0:halt_on_error=1:abort_on_error=1
export UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1
```

Matrix dimensions, addition and multiplication are covered by the functional runner. Every case runs with isolated data.

## Pending gates

LeakSanitizer is blocked by thread-suspension restrictions inside the Codex execution environment. On 2026-10-15 the user ran the instrumented binary from a normal Ubuntu terminal with `ASAN_OPTIONS=detect_leaks=1:halt_on_error=1`: functional 35/35, additional 40/40, studies 26/26 and scripts 7/7 passed with exit zero and no reported leaks or sanitizer diagnostics (108 cases across four suites). This includes matrix dimensions, addition and multiplication. The approval is limited to the tested paths.

The remaining external-terminal LSan run also passed on 2026-10-15: entry 8/8, graphs 2/2 and terminal/startup 10/10, with exit zero, detect_leaks=1 recorded in the environment manifest, thread scanning present in detailed logs and no reported leaks or sanitizer diagnostics. This brings the combined LSan coverage to **128 cases across seven suites**, limited to their tested paths. The executable hash matches the instrumented 4cfb6a2 binary. To reproduce from the repository root with the instrumented executable, run:

```sh
bash tests/run-atc-linux-lsan-remaining.sh /path/to/instrumented/atc
```

The driver records sanitizer options, executable hash, detailed output and exit codes in a new timestamped directory. It deliberately fails on any suite failure. Graphs have a 300-second per-case deadline because optimized ASan graph evaluation took approximately 73 and 154 seconds in the previous validation.

The latest validated source is `4cfb6a26b74a8296c48674ca0f6830912b9ad0fa`. Its commit records Windows Release x64 and Win32 376/376 passes; those native executions were not performed in the Linux session. Linux test expectations were updated for the descending printed root order and the equivalent `]-inf,+inf[` range notation.

**Windows XP runtime validation is a separate mandatory approval gate.** Target architectures remain to be agreed. See `ATC_2_1_9_WINDOWS_XP_VALIDATION.md`; compiling with v141_xp and passing on newer Windows do not complete this gate.

Function studies use the existing real double coefficient representation. The numerical tests cover the listed regressions, repeated roots, shifted cubic roots and removable holes; they are not a proof for arbitrarily ill-conditioned polynomials.

## Reproducible terminal checks

The new graph runner uses a real pseudo-terminal and isolated executable/data files. It checks single/multiple functions, X/Y labels, UTF-8 bars, numerical cursor values, right/left navigation, Escape and normal process exit:

```sh
python3 tests/run-atc-linux-graph.py /path/to/atc --timeout 300 --output-dir /new/log/directory
```

The terminal runner checks Backspace, Delete, left/right insertion, Home/End, empty-line boundaries, Tab completion, editing a wrapped line, history with draft restoration, the complete ten-second countdown and Enter bypass. It checks each countdown tick and the corresponding filled bar length:

```sh
python3 tests/run-atc-linux-terminal.py /path/to/atc --output-dir /new/log/directory
```

The shared helper uses the Python standard library and terminates its owned process group on timeout. These checks do not inspect the pixels of the user's terminal emulator; a final visual review of font, colors and placement remains useful.
