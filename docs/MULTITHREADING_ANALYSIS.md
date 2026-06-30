# ATC Multithreading Analysis

This document analyses where multithreading could safely and usefully be
introduced in Advanced Trigonometry Calculator (ATC) without changing current
CLI, script, output, precision or regression-test behavior.

No implementation changes are proposed here. This is a design and risk
assessment document.

## Executive Summary

ATC should not be made globally multithreaded in its current architecture. The
main processing flow uses shared mutable state extensively, including global
result variables, global text buffers, persisted variable buffers, matrix
scratch buffers, history/settings files, output buffers and direct console
printing. Running complete commands in parallel would create race conditions and
would make output order non-deterministic.

The safest strategy is to keep the command pipeline single-threaded and
introduce small, isolated parallel kernels inside computation-heavy routines
that already operate on explicit input/output arrays. Candidate areas include:

- matrix element-wise operations;
- selected matrix multiplication loops;
- selected statistics reductions after parsing is complete;
- selected DSP loops;
- possibly polynomial coefficient multiplication after refactoring to local
  data structures.

The recommended first implementation target is matrix element-wise operations
and matrix multiplication, because these routines already accept matrix
pointers as parameters and can preserve deterministic output by writing each
cell to a unique output location.

## Current Threading Constraints

The current codebase is optimized around a single-threaded command interpreter.
Important shared state includes:

- `resultR`, `resultI`, `ans`, `ansI`, `ansRV`, `ansIV`;
- `expressionF`, `saveExpressionF`, `saveSimplified`, `saveSimplification`;
- `matrixResult`, `matrixValue`, `vectorString`, `saveMatrixAns`;
- `saveVariablesTextFile`, `saveTxtVariablesTextFile`,
  `saveScriptVariablesTextFile`, renamed-variable buffers and string buffers;
- `context`, `runningScript`, `processingTxtFile`, `matrixMode`,
  `higherPrecision`, `Mode`, `rf`, `verbose`, `feedbackValidation`;
- dynamic-allocation tracking through the global `dynamicAllocation` object;
- global output/history/settings files under the ATC data directory;
- direct `printf`, `puts`, `fprintf`, `fopen` and console cursor/window calls.

These variables are not protected by locks and many functions write to them as
part of normal expression evaluation. Therefore, parallelism must not call the
general parser/evaluator (`main_core`, `calcNow`, `processTxt`,
`atcProgramming`, `commands`, `variableController`) from multiple worker
threads until a larger refactor introduces isolated evaluation contexts.

## Candidate Areas

| Area | Classification | Expected Gain | Main Risk | Notes |
| --- | --- | --- | --- | --- |
| Matrix addition/subtraction/scalar multiplication | Safe to parallelize now | Medium for large matrices | Low if each cell writes to a unique output cell | Good first target. Preserve row-major output after computation. |
| Matrix multiplication | Safe to parallelize now, with care | High for larger matrices | Medium due complex arithmetic and cache locality | Parallelize outer rows or output cells only. Do not print inside workers. |
| Matrix transpose | Safe to parallelize now | Low to medium | Low | Simple independent cell writes. |
| Matrix power | Possible but requires refactor | Medium to high | Medium | Uses repeated multiplication and shared temporaries; parallelize underlying multiplication first. |
| Matrix inverse/rank/determinant | Possible but requires refactor | Medium | High | Gaussian elimination/pivoting has sequential dependencies and global mode/output behavior. |
| Polynomial expansion/simplification | Possible but requires refactor | Medium to high for high degree | High | Current polynomial paths mix parsing, string rewriting, coefficient state and output. Need local coefficient vectors first. |
| Roots to polynomial | Possible but requires refactor | Medium for many roots | Medium | Root-factor convolution can be parallelized by degree range, but output ordering and coefficient rounding must remain deterministic. |
| Equation solver root polishing | Unsafe initially | Unclear | High | Solver writes global state and relies on deterministic ordering/reporting. Sorting roots must stay stable. |
| Statistics reductions | Safe after parsing | Low to medium | Low to medium | Mean/variance/min/max can parallel-reduce local arrays. Parsing and printing must stay single-threaded. |
| DSP `fft` / `ifft` | Possible but requires refactor | Medium | Medium | Current implementation uses shared arrays and direct formatted output. A local FFT kernel could be parallelized later. |
| Batch/script execution | Unsafe / not worth it initially | Low to medium | High | Scripts depend on order, variables, `break`, `return`, input/output and persisted state. |
| TXT/script file processing | Unsafe for command execution | Low to medium | High | Lines can mutate shared variables/results and output files. Only pre-scan/tokenization could be parallel later. |
| Output generation | Unsafe initially | Low | High | CLI output order is part of behavior. Build strings locally, then emit single-threaded. |
| Regression test runner | Safe outside ATC process | High wall-clock reduction | Medium | PowerShell can run isolated ATC processes in parallel only if each uses an isolated data directory. |

## Safe to Parallelize Now

### Matrix Element-Wise Operations

Functions such as `fmsum`, `fmsubt`, `fmmulr` and `fmtranspose` operate on
explicit input/output matrix arrays. The computation for each cell is
independent:

- input matrices are read-only during the kernel;
- each worker can write a distinct output cell;
- formatted output can remain after the parallel section;
- no parser or variable controller is needed inside worker threads.

Recommended approach:

1. Keep function signatures unchanged.
2. Add a local threshold, for example only parallelize when
   `lines * columns >= 1024`.
3. Parallelize by rows.
4. Do not call `printf`, `convertComplex2Exponential`, `calcNow`,
   `variableController` or allocation tracking inside worker bodies.
5. Preserve final row-major output.

### Matrix Multiplication

Matrix multiplication has a larger CPU cost and is a good candidate once the
basic element-wise operations are proven stable. Parallelization should assign
one row or one output cell per worker. Each output cell must use local
accumulators for real and imaginary parts.

Risks:

- small matrices may become slower due thread overhead;
- `mp_float` operations are heavier and may allocate internally;
- deterministic numerical output must be verified in both `double` and
  `mp_float` modes.

### Statistics After Parsing

Some statistics paths parse a population into local arrays and then perform
independent reductions. After parsing is complete, parallel reductions can be
considered for:

- sum;
- min/max;
- variance partial sums;
- frequency counting only after refactoring to local maps or sorted arrays.

The guided interactive prompts and final output must remain single-threaded.

## Possible but Requires Refactor

### Polynomial Expansion and Simplification

Polynomial simplification currently relies heavily on string normalization,
parser side effects and global buffers. It should not be parallelized directly.

A safer future design would split the work into:

1. parse expression into a local polynomial representation;
2. multiply/add local coefficient vectors;
3. normalize coefficients locally;
4. format output on the main thread.

Only step 2 should be considered for parallel execution. This would allow
parallel convolution or divide-and-conquer multiplication for high-degree
products, while preserving output formatting.

### Roots to Polynomial

`roots to polynomial` is conceptually a good candidate because repeated root
factor multiplication is CPU-heavy for larger root lists. However, current ATC
behavior depends on exact coefficient formatting and complex-root handling.

Recommended refactor:

- convert roots into local complex coefficient vectors;
- multiply factors using a deterministic order;
- optionally parallelize independent factor-pair multiplication;
- round/format only after all workers finish.

### DSP `fft` / `ifft`

The current DSP implementation has nested loops and local arrays, but also
direct output and shared global state through the surrounding command pipeline.
Parallelizing the existing function directly would be risky.

A better design is:

- create a pure local FFT/IFFT kernel;
- return local result arrays;
- format output on the main thread;
- only then consider parallel stages for larger input sizes.

### Matrix Inverse, Rank and Determinant

These algorithms use pivoting and elimination, which are not embarrassingly
parallel. They also have mode/reporting interactions. Some row operations could
eventually be parallelized inside each pivot step, but only after:

- pivot selection is isolated;
- temporary matrices are local;
- no output or global mode changes occur inside the elimination loop;
- deterministic pivot behavior is preserved.

## Unsafe or Not Worth It Initially

### Full Command Processing

Do not run multiple user commands concurrently inside the same ATC process.
Reasons:

- commands share `resultR`, `resultI`, `ans`, `rf` and history;
- variables and renamed variables are stored in shared text buffers;
- files under the ATC data directory are read/written during command execution;
- output order is part of CLI behavior;
- settings can change during commands.

### Script Execution

Script execution must remain single-threaded initially. Scripts can mutate
variables, depend on loop order, use `break`, `return`, `get`, `print`,
`sprint`, string variables and persisted state. Parallel script-line execution
would break semantics.

Safe future work may include optimizing independent internals of one script
command, but not executing multiple script statements in parallel.

### TXT Processing

TXT processing should remain ordered. TXT files may contain variable
assignments, commands with export prompts, solver calls and invalid lines that
must be reported in sequence. Parallel line execution would break answer-file
ordering and shared variable behavior.

### Output Rendering and Console/UI

Console output, graph rendering, menus, autocomplete, history navigation,
window sizing, Windows Terminal behavior and file/browser/editor opening must
remain single-threaded. Worker threads should never call UI, console cursor,
window-management or external-open functions.

### Dynamic Allocation Tracker

The dynamic allocation tracking structure is global and not protected by a
mutex. Worker threads should avoid project allocation helpers unless the
allocator/tracker is made thread-safe or disabled in worker-local kernels.

## Shared Mutable State and Race-Condition Hotspots

| Hotspot | Risk | Threading Guidance |
| --- | --- | --- |
| `resultR`, `resultI`, `ans`, `ansI`, `rf` | Cross-command result corruption | Main thread only. |
| `expressionF` and parser scratch strings | Parser races and incorrect replacements | Main thread only unless evaluation context is refactored. |
| `matrixResult`, `matrixValue`, `vectorString` | Matrix output/state corruption | Build local results in workers; assign global string after join. |
| `saveVariablesTextFile` and related buffers | Lost variable updates | Main thread only. |
| `context`, `runningScript`, `processingTxtFile` | Wrong variable namespace | Main thread only. |
| `dynamicAllocation` | Tracking corruption | Avoid in workers or protect later. |
| `printf`, `puts`, `fprintf` | Interleaved output | Main thread only. |
| Settings/history files | File races | Main thread only. |
| `boost::multiprecision::cpp_dec_float` values | Potential heavy copies/allocations | Use local values, avoid shared mutation. |

## Risk Matrix

| Candidate | Benefit | Risk | Classification |
| --- | --- | --- | --- |
| Matrix sum/subtraction/scalar multiplication | Medium | Low | Safe to parallelize now |
| Matrix multiplication | High | Medium | Safe to parallelize now, with thresholds |
| Matrix transpose | Low/Medium | Low | Safe to parallelize now |
| Statistics sum/variance reductions | Low/Medium | Medium | Safe after parsing |
| DSP pure kernel | Medium | Medium | Possible after refactor |
| Roots-to-polynomial factor multiplication | Medium | Medium | Possible after refactor |
| Polynomial simplification | High | High | Possible after refactor |
| Matrix inverse/rank/determinant | Medium | High | Possible after refactor |
| Script command execution | Low | High | Unsafe initially |
| TXT line execution | Low/Medium | High | Unsafe initially |
| Output rendering | Low | High | Unsafe / not worth it |
| Regression runner process-level parallelism | High | Medium | Safe outside ATC with isolated data dirs |

## Recommended First Implementation Target

The best first target is matrix arithmetic kernels:

1. `fmsum`
2. `fmsubt`
3. `fmmulr`
4. `fmtranspose`
5. `fmmulm`

Reasons:

- they are CPU-bound for larger matrices;
- they already use explicit input/output arrays;
- output can remain deterministic if formatting is done after computation;
- correctness can be validated with existing matrix regression tests;
- the implementation can be guarded by a size threshold;
- failure impact is localized compared with parser or solver threading.

Implementation should start with `double`/`PrecisionValue` matrix paths and use
a compile-time or runtime switch so threading can be disabled quickly if older
Windows compatibility issues appear.

## Required Tests Before Implementation

Before introducing any thread code, add or confirm these tests:

- matrix addition/subtraction/multiplication with real values;
- matrix operations with complex values;
- rectangular transpose;
- scalar-matrix multiplication;
- matrix power using multiplication internally;
- x64 and x86 Release builds;
- `double` and Boost `mp_float` modes;
- repeated matrix operations in one session;
- memory stress for matrix operations;
- deterministic output comparison across repeated runs;
- Windows 11 console smoke test to ensure output remains ordered;
- regression suite must remain green.

For future polynomial/DSP threading, add:

- high-degree polynomial simplification benchmarks;
- roots-to-polynomial with real roots, complex roots and repeated roots;
- FFT/IFFT deterministic output tests;
- large statistics dataset tests with known results;
- Memory Factor checks for each threaded path.

## Phased Roadmap

### Phase 0 - Baseline and Guardrails

- Keep ATC command processing single-threaded.
- Add performance baselines for matrix, DSP, statistics and polynomial paths.
- Add a runtime setting or compile-time flag to disable internal parallelism.
- Document deterministic-output requirements for worker kernels.

### Phase 1 - Matrix Kernels

- Parallelize only local matrix kernels with explicit input/output arrays.
- Use row-level partitioning and a minimum-size threshold.
- Keep output formatting, report generation and global assignments on the main
  thread.
- Validate x64/x86, `double` and `mp_float`.

Status for ATC 2.1.7 development:

- Implemented for `fmsum`, `fmsubt`, `fmmulr`, `fmtranspose` and `fmmulm`.
- Uses row-range worker partitioning with `std::thread`.
- Worker count is capped and is derived from useful row chunks and estimated
  cell work, so medium matrices do not create more threads than useful.
- `fmmulm` estimates work using output cells multiplied by the shared inner
  dimension, because matrix multiplication is more expensive than element-wise
  kernels.
- The runtime switch `ATC_DISABLE_MATRIX_PARALLELISM=1` disables the threaded
  path.
- The compile-time switch `ATC_ENABLE_MATRIX_PARALLELISM=0` disables the
  threaded path at build time.
- Worker threads only read input matrix cells and write unique output cells.
- Formatting, result strings, output rendering and global state updates remain
  on the main thread.
- The current threshold is intentionally conservative so documented regression
  matrices and small user matrices stay on the serial path.
- Dedicated validation is available in
  `tests/run-atc-matrix-parallelism.ps1`.
- Serial vs default runtime benchmark support is available in
  `tests/run-atc-matrix-benchmark.ps1`.

### Phase 2 - Statistics Reductions

- Refactor statistics calculations to parse data once into local arrays.
- Parallelize sum/min/max/variance reductions for sufficiently large datasets.
- Keep guided menus and formatted output single-threaded.

### Phase 3 - DSP Pure Kernels

- Extract pure FFT/IFFT kernels that do not print and do not mutate globals.
- Parallelize only larger workloads.
- Keep output formatting deterministic and single-threaded.

### Phase 4 - Polynomial and Roots Refactor

- Introduce local polynomial coefficient structures.
- Separate parsing, computation and formatting.
- Consider parallel coefficient convolution or divide-and-conquer factor
  multiplication only after deterministic local behavior is proven.

### Phase 5 - Process-Level Test Parallelism

- Improve the PowerShell regression runner to run independent ATC processes in
  parallel with isolated temporary ATC data directories.
- Do not share `%USERPROFILE%\Pictures\Advanced Trigonometry Calculator`
  between parallel test workers.
- Keep order-dependent and persistence tests serial.

### Phase 6 - Evaluation Context Refactor

- Long term, introduce an explicit `EvaluationContext` containing result state,
  variables, buffers, mode/settings snapshots and output sinks.
- Only after this refactor should ATC consider parallel command evaluation or
  concurrent TXT processing.

## Conclusion

ATC can benefit from multithreading, but only if introduced in narrow,
computation-only sections. The current global-state architecture makes broad
parallelism unsafe. Matrix kernels are the clearest first target, followed by
statistics reductions and pure DSP kernels. Parser, solver, scripts, TXT
processing, output rendering and UI behavior should remain single-threaded
until the project has isolated evaluation contexts and thread-safe ownership of
memory, variables and output.
