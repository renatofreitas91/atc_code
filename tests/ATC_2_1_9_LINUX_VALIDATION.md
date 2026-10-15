# ATC 2.1.9 — Linux validation of the Windows checkpoint

Base commit: `e5c23e80446c2fa031fb17a4d11c5040a184cacc`.

Validation completed on Linux with GCC 15.2.0, CMake 4.2.3 and Boost 1.90, using C++17. The Linux changes preserve the Windows checkpoint as their parent. No merge with main or release is involved.

## Changes

- Guard negative indices in angular/polynomial solvers, expression scanning and script formatting; initialize and clear file handles after closing them.
- Define matrix scratch ownership and free buffers after their last use.
- Support Linux cursor editing, arrow navigation, UTF-8 console graphics, graph study bars and startup countdown updates.
- Recognize dropped TXT paths and locate script examples relative to the executable; preserve nested script data paths and execute for-loop initialization as an assignment.
- Use coefficient derivatives for function studies, isolating real roots between derivative roots and preserving repeated roots. Determine the image of higher-degree rational functions by joining the images of continuous monotone intervals, retaining excluded domain points and checking multiplicities at poles.
- Determine symmetry from polynomial identities and the original domain; omit yy intersections at excluded zero.

The previous polynomial derivative path used overlapping sprintf source/destination buffers. An extracted reproducer loses the leading term in GCC Release while retaining it under ASan. The function-study path now reuses the canonical coefficient derivative routine. General equation solving and multiprecision arithmetic are not replaced.

## Results

| Suite | GCC Release | Optimized ASan/UBSan |
| --- | --- | --- |
| Functional: 34 original + one rational regression | 35/35 | 35/35 |
| LF, CR, CRLF, EOF and terminal input | 8/8 | 8/8 |
| Implicit products, lists, precision, angular solvers, Newton residual | 40/40 | 40/40 |
| Polynomial and rational studies | 26/26 | 26/26 |
| Dropped TXT paths and scripts | 7/7 | 7/7 |

Function studies also pass 26/26 with GCC Debug and unoptimized ASan/UBSan. The six formerly failing expressions have byte-identical cleaned output in all four configurations: `x^3`, `x^4`, `x^3-3*x`, `1/(x^3)`, `x^3/(x^2+1)` and `x^4/(x^2+1)`.

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

LeakSanitizer has not produced a valid report: thread suspension is denied in the validation environment. This was reproduced again on 2026-10-15 for all three matrix cases with detect_leaks=1. The ASan runs with detect_leaks=0 do not establish the absence of leaks.

Native Windows approval requires rebuilding and rerunning the original 376 checks independently for Release x64 and Win32 with MSVC v141_xp. Source compatibility with C++17 was reviewed; native Windows execution remains pending. These Linux results do not substitute for that gate.

Function studies use the existing real double coefficient representation. The numerical tests cover the listed regressions, repeated roots, shifted cubic roots and removable holes; they are not a proof for arbitrarily ill-conditioned polynomials.
