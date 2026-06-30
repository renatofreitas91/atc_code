# ATC Architecture Quality Review

This document is an architectural review of the Advanced Trigonometry
Calculator (ATC) codebase after the ATC 2.1.7 matrix multithreading and CI
preparation work.

It is an analysis and planning document only. It does not propose immediate
behavioral changes, mathematical changes, API changes, or new multithreaded
subsystems.

## Executive Summary

ATC has grown into a broad command-line mathematical application with a large
feature surface: expression processing, equation solving, matrix arithmetic,
graphing, scripts, TXT processing, guided modules, persistent settings, and
Windows console integration. The current codebase is functional and heavily
covered by regression tests, but its architecture is still shaped by a
monolithic C/C++ style: many global variables, large source files, long
functions, manual dynamic memory ownership, and broad include coupling through
`stdafx.h`.

The highest-value architectural work is not adding more features. It is
stabilizing module boundaries, reducing shared mutable state, introducing
ownership wrappers around existing dynamic allocation helpers, and separating
parsing, computation, persistence, and rendering. These changes should be
phased carefully and protected by the existing regression suite.

Current size indicators:

| Area | Observation |
|---|---|
| Largest source files | `data_processing_core.cpp` ~7324 lines, `commands.cpp` ~6275, `equation_solver.cpp` ~5356, `processing_core.cpp` ~4001 |
| Largest functions | `equationSolver` ~2139 lines, `simplifyExpression` ~1961, `initialProcessor` ~1887, `functionStudy` ~1757 |
| Global state | Large `extern` block in `stdafx.h` exposes parser, settings, output, solver, matrix and runtime flags globally |
| Manual ownership | Widespread `getDynamic*`, `_delete`, `_Delete`, `char*`, `sprintf`, and array management |
| Compile-time coupling | Most `.cpp` files include `stdafx.h`, which includes Windows, Boost, resource, dynamic allocation and global declarations |

The recommended direction is a staged modernization that preserves the current
behavior while creating safer boundaries around the most volatile areas.

## Top 20 Architectural Improvements

| Rank | Recommendation | Impact | Effort | Risk | Maintainability Benefit | Performance Benefit | Scalability Benefit |
|---:|---|---|---|---|---|---|---|
| 1 | Split `processing_core.cpp` into parser normalization, arithmetic solver, function dispatcher and output formatting units | Very high | High | High | Very high | Medium | High |
| 2 | Split `data_processing_core.cpp` into variable storage, expression utilities, settings/file helpers, matrix parsing and command bridge helpers | Very high | High | High | Very high | Medium | High |
| 3 | Split `equation_solver.cpp` into polynomial model, root solving, simplification, fast-path rational cancellation and export/reporting | Very high | High | High | Very high | High | High |
| 4 | Introduce a small `AtcRuntimeContext` struct for execution flags currently stored as globals | Very high | High | High | Very high | Low | High |
| 5 | Introduce RAII wrappers for dynamic arrays returned by `getDynamic*` while keeping existing helpers as compatibility APIs | Very high | Medium | Medium | Very high | Medium | High |
| 6 | Replace repeated `sprintf(buffer, "%s...", buffer, ...)` concatenation patterns with append-only string/report builders | High | Medium | Medium | High | High | Medium |
| 7 | Create a `Matrix` value/handle abstraction for real/imaginary matrices and dimensions | High | High | High | High | High | High |
| 8 | Separate command detection from command execution in `commands.cpp` | High | Medium | Medium | High | Low | High |
| 9 | Move persistent file paths and settings into a settings repository/service object | High | Medium | Medium | High | Low | Medium |
| 10 | Reduce `stdafx.h` responsibilities by moving `extern` declarations into focused module headers | High | Medium | Medium | High | Medium | High |
| 11 | Introduce immutable input views for expression strings instead of passing mutable `char*` everywhere | High | High | High | High | Medium | High |
| 12 | Encapsulate result state (`resultR`, `resultI`, `ans`, `history`, `#n`) behind a result manager | High | Medium | Medium | High | Low | High |
| 13 | Convert guided modules into smaller menu/controller/calculation/reporting parts | Medium | Medium | Low | Medium | Low | Medium |
| 14 | Create a dedicated output renderer interface for console, report export, TXT answer generation and script print output | Medium | Medium | Medium | High | Medium | High |
| 15 | Add internal data models for polynomial coefficients and complex roots instead of passing text buffers through every stage | High | High | High | High | High | High |
| 16 | Introduce module-level unit tests for pure computation kernels after extracting them from UI/global state | High | High | Medium | High | Medium | High |
| 17 | Replace magic dimension globals (`DIM`, `dime`, `DIMTWOD`, `DIMDOUBLE`) with named capacity policies | Medium | Medium | Medium | High | Medium | Medium |
| 18 | Centralize external process/file-open behavior behind a testable adapter | Medium | Low | Low | Medium | Low | Medium |
| 19 | Move large ASCII/console drawing routines into static data tables or resources | Medium | Low | Low | Medium | Low | Low |
| 20 | Define stable module ownership rules in developer documentation before large refactors | High | Low | Low | High | Low | High |

## Quick Wins

These items should take less than one day each and can be performed without
changing mathematical behavior if guarded by tests.

### 1. Document Module Ownership

Create a short ownership map in the developer documentation:

- parser and expression normalization;
- command routing;
- mathematical engines;
- settings and persistence;
- output rendering;
- scripting/TXT processing;
- dynamic allocation and memory diagnostics.

Risk: Low.  
Benefit: Reduces accidental cross-module edits.

### 2. Add File Headers With Module Purpose

Add short English comments at the top of large source files explaining what
belongs there and what should not be added there.

Risk: Low.  
Benefit: Helps stop further growth of already oversized files.

### 3. Add TODO Markers for Split Boundaries

Without moving code, mark candidate boundaries in:

- `processing_core.cpp`;
- `data_processing_core.cpp`;
- `equation_solver.cpp`;
- `commands.cpp`.

Risk: Low.  
Benefit: Prepares future extraction.

### 4. Create a Report Builder Utility Proposal

Document a future replacement for repeated `sprintf(report, "%s...", report)`.
This pattern copies existing content repeatedly and can become expensive for
large reports.

Risk: Low.  
Benefit: Better performance and simpler memory ownership later.

### 5. Add Guidelines for Test Runner Isolation

Keep CI and local testing documentation explicit: ATC runners must not share
the same data directory when run concurrently.

Risk: Low.  
Benefit: Avoids false failures and hidden data races in tests.

### 6. Identify Safe RAII Wrapper Entry Points

List candidate wrappers such as `DynamicCharBuffer`, `DynamicArray<T>`, and
`DynamicMatrix<T>` without replacing existing APIs yet.

Risk: Low.  
Benefit: Creates a migration route away from manual `_delete` calls.

### 7. Move Duplicate Include Notes Out of Source

`check_for_updates.cpp` currently includes `stdafx.h` twice. Small cleanup can
be made later with minimal risk.

Risk: Low.  
Benefit: Minor compile hygiene.

### 8. Keep New Code Out of `stdafx.h`

Adopt a rule that new features should not add global state to `stdafx.h` unless
there is no reasonable alternative.

Risk: Low.  
Benefit: Prevents further global coupling.

## Medium-Term Refactors

### 1. Parser and Expression Pipeline Extraction

Current concern:

- `initialProcessor` is approximately 1887 lines.
- It mixes normalization, validation, function dispatch, arithmetic solving and
  side effects.

Recommended split:

1. lexical cleanup and command prefix handling;
2. parenthesis and syntax validation;
3. implicit multiplication normalization;
4. function call dispatch;
5. arithmetic evaluation;
6. output/result update.

Risk: High.  
Mitigation: Extract one pure helper at a time and run full regression after
each step.

### 2. Equation Solver Decomposition

Current concern:

- `equation_solver.cpp` combines textual parsing, polynomial simplification,
  coefficient models, numeric solving, rational cancellation, export prompts
  and report output.

Recommended split:

- `PolynomialExpressionParser`;
- `PolynomialModel`;
- `PolynomialSimplifier`;
- `EquationRootSolver`;
- `RationalFactorReducer`;
- `EquationReportRenderer`.

Risk: High.  
Mitigation: Preserve existing command outputs exactly and add golden tests for
edge cases before extraction.

### 3. Matrix Data Model

Current concern:

- Matrix operations pass separate real/imaginary `T**` arrays and dimensions.
- Memory ownership is manual.
- Output formatting is mixed into computation functions.

Recommended split:

- `ComplexMatrixView`;
- `MutableComplexMatrixView`;
- `MatrixStorage`;
- `MatrixKernel`;
- `MatrixRenderer`.

Risk: Medium to high.  
Mitigation: Start with views that wrap existing arrays without owning memory.

### 4. Runtime Context Object

Current concern:

- Execution flags such as mode, solver state, script state, matrix mode,
  precision mode and output state are global.
- This makes test isolation, concurrency and reasoning harder.

Recommended approach:

- create `AtcRuntimeContext`;
- pass it first to newly extracted helpers;
- migrate existing globals gradually.

Risk: High.  
Mitigation: Keep globals as backing storage initially and expose context views.

### 5. Output Renderer Separation

Current concern:

- Computation functions often call `puts`, `printf`, export prompts, history
  updates or file writes directly.

Recommended interfaces:

- console renderer;
- report renderer;
- script/TXT output sink;
- test/mock renderer.

Risk: Medium.  
Mitigation: Start with wrappers around existing calls.

### 6. Persistent Settings Repository

Current concern:

- Many modules directly know file paths and persistent setting files.

Recommended approach:

- centralize read/write operations;
- expose typed settings access;
- keep existing file formats unchanged.

Risk: Medium.  
Mitigation: Add compatibility tests for every setting file.

## Long-Term Roadmap for ATC 3.x

### Phase 1: Stabilize Boundaries

- Freeze public command behavior with golden regression tests.
- Define ownership boundaries for parser, solver, matrix, settings and output.
- Add developer rules for new modules and global state.

Expected benefit:

- higher maintainability;
- fewer regressions when changing internals.

### Phase 2: Introduce Safe Internal Models

- Add non-owning views for strings, matrices and polynomial coefficients.
- Add RAII wrappers for new internal allocations.
- Keep old helper APIs available as compatibility adapters.

Expected benefit:

- lower leak risk;
- cleaner future refactors;
- better memory diagnostics.

### Phase 3: Extract Pure Computation Kernels

- Move matrix, polynomial, statistics, DSP and numerical conversion kernels
  away from output and global state.
- Add unit-style tests for pure kernels.

Expected benefit:

- faster tests;
- safer optimization;
- easier future WebAssembly/backend reuse.

### Phase 4: Context-Based Execution

- Replace most global execution state with an explicit runtime context.
- Allow multiple isolated ATC sessions in tests.
- Make script/TXT processing easier to reason about.

Expected benefit:

- better test isolation;
- safer future concurrency;
- clearer ownership.

### Phase 5: Modular ATC 3.x Core

- Keep CLI behavior stable.
- Internally separate:
  - command parsing;
  - expression evaluation;
  - mathematical engines;
  - persistence;
  - rendering;
  - automation/file bridge.

Expected benefit:

- sustainable feature growth;
- lower compile time;
- better package and platform options.

## Detailed Findings

### Code Duplication

Observed duplication patterns:

- guided modules repeat input/menu/report loops;
- matrix functions repeat report construction and export prompting;
- settings menus repeat option validation and persistence logic;
- TXT/script/command bridge code repeats file path and external open handling;
- polynomial and solver paths repeat parsing and formatting responsibilities.

Recommended direction:

- extract reusable menu prompts;
- centralize report/export flow;
- centralize file path handling;
- keep mathematical computation separate from formatting.

### Oversized Files and Functions

Highest priority files to split:

| File | Approx. Lines | Suggested Split |
|---|---:|---|
| `data_processing_core.cpp` | 7324 | variables, string utilities, settings helpers, expression helpers, command bridge |
| `commands.cpp` | 6275 | command table, command parser, command handlers, external actions |
| `equation_solver.cpp` | 5356 | polynomial parser, simplifier, root solver, rational reducer, export |
| `processing_core.cpp` | 4001 | initial processor, arithmetic solver, function processor, renderer |
| `main.cpp` | 2810 | startup, Windows console setup, main loop, TXT processing |
| `function_study.cpp` | 2476 | domain, asymptotes, derivative analysis, sign tables, codomain |

Largest functions to target:

| Function | Approx. Lines | Risk |
|---|---:|---|
| `equationSolver` | 2139 | High |
| `simplifyExpression` | 1961 | High |
| `initialProcessor` | 1887 | High |
| `functionStudy` | 1757 | High |
| `manageExpression` | 1578 | High |
| `dataVerifier` | 1469 | High |
| `main_sub_core` | 1430 | High |

### Encapsulation Opportunities

Areas that need clearer ownership:

- result state: `resultR`, `resultI`, `ans`, `ansI`, result numbering;
- precision mode: double vs `mp_float`;
- expression buffers: `expressionF`, `resp`, `respR`, `respI`;
- matrix mode and matrix dimensions;
- script/TXT execution state;
- settings persistence paths;
- external process opening.

Recommended rule:

New code should receive state through arguments or context objects instead of
adding more globals.

### Global State

`stdafx.h` exposes a large `extern` surface containing integers, booleans,
buffers, result values, vectors, matrices and runtime flags. This creates:

- hidden dependencies between modules;
- difficult test isolation;
- risky future parallelization;
- unclear ownership and lifetime;
- slower compile cycles due broad include coupling.

Recommended migration:

1. document each global group;
2. move declarations into focused headers;
3. introduce a runtime context for new extracted helpers;
4. gradually reduce direct global access.

### Unsafe Ownership Patterns

The project has improved dynamic allocation tracking, but ownership remains
manual. Typical patterns include:

- raw `char*` buffers;
- raw `T*` and `T**` arrays;
- manual `_delete` and `_Delete` calls;
- repeated mutable string formatting;
- shared global dynamic buffers.

Recommended migration:

- keep existing helpers for compatibility;
- add RAII wrappers around them;
- use wrapper types in new extracted code first;
- migrate high-risk functions only after regression tests cover them.

### Manual Memory Management Toward RAII

Potential wrapper candidates:

| Wrapper | Purpose |
|---|---|
| `DynamicCharBuffer` | owns a dynamic char buffer and deletes automatically |
| `DynamicArray<T>` | owns a dynamic one-dimensional ATC array |
| `DynamicMatrix<T>` | owns ATC 2D arrays with line cleanup |
| `ScopedAtcState` | saves/restores global flags during operations |
| `ReportBuilder` | append-only string/report construction |

Risk:

- Medium. RAII wrappers are safe if introduced around new code first, but risky
  if old ownership contracts are changed too quickly.

### Expensive Copies

Potential expensive copy patterns:

- repeated `sprintf(buffer, "%s...", buffer, ...)`;
- repeated report construction in matrix, time and guided modules;
- script print/output accumulation;
- parsing stages that copy full expressions repeatedly;
- polynomial simplification text transformations.

Recommended direction:

- introduce append-only builders;
- pass read-only expression inputs by `const char*` or string view-like wrappers
  where possible;
- avoid copying full buffers during each append;
- keep output text identical.

### Include Dependencies and Compile Time

Current state:

- almost every `.cpp` includes `stdafx.h`;
- `stdafx.h` includes Windows, Boost, resources, project headers and many
  global declarations;
- this makes each translation unit sensitive to broad header changes.

Recommended direction:

1. keep `stdafx.h` stable;
2. avoid adding new dependencies to it;
3. move module-specific declarations into module headers;
4. forward declare where possible;
5. use smaller headers for extracted pure kernels.

Risk:

- Medium. Header changes can affect the Visual Studio precompiled header flow,
  especially with `v141_xp`.

## Risk Assessment Summary

| Area | Risk | Why |
|---|---|---|
| Parser extraction | High | Many command paths depend on exact text transformation behavior |
| Equation solver extraction | High | Fast paths, complex roots and export prompts are tightly coupled |
| Matrix data model | Medium/High | Memory layout and output formatting must remain exact |
| Runtime context migration | High | Many globals are read/written across modules |
| RAII wrappers | Medium | Safe if additive, risky if replacing ownership too quickly |
| Output renderer | Medium | User-visible formatting must remain unchanged |
| Include cleanup | Medium | PCH/toolset compatibility must be preserved |
| Guided module cleanup | Low/Medium | Mostly menu/report structure, but interactive flows need tests |

## Recommended Order of Work

1. Document module ownership and do not add new globals.
2. Add report builder and dynamic buffer wrapper as internal utilities.
3. Extract small pure helpers from `processing_core.cpp`.
4. Extract polynomial model helpers from `equation_solver.cpp`.
5. Introduce non-owning matrix views.
6. Separate output rendering from selected computation functions.
7. Introduce `AtcRuntimeContext` for new code paths.
8. Gradually migrate legacy globals and manual buffers.

## Non-Goals

This review does not recommend:

- changing mathematical results;
- changing command syntax;
- adding new mathematical features;
- adding new multithreaded subsystems;
- activating GitHub Actions;
- replacing the whole codebase at once;
- removing Windows XP compatibility goals without a separate decision.

## Final Recommendation

The ATC codebase should continue to prioritize behavior preservation and test
coverage while slowly carving out safer internal modules. The most important
architectural investment is to reduce hidden coupling: large functions, global
state and manual ownership are the main risks to future maintenance.

For ATC 2.1.7, only low-risk documentation and targeted internal hardening
should be considered. Larger structural refactors should be planned for ATC 3.x
and introduced behind regression tests, one boundary at a time.
