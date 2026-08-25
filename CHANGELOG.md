# Changelog

All notable project changes should be documented in this file.

Current release details are recorded here. Historical release sections retain
their original dates and validation evidence.

## 2.1.8 - 2026-08-25

### Solver correctness

- Added validation of candidate roots against the original expression before a
  solution is returned.
- Added support for validated real and complex solutions, including complex
  polynomial cases.
- Added a general numerical fallback when the existing solver path does not
  produce a valid root.
- Fixed direct complex evaluation involving stored results and general exponent
  expressions.
- Added the message `ATC was unable to find a valid solution.` when no candidate
  satisfies the original expression.

### Settings and file robustness

- Bounded settings-file retries and closed file handles safely across valid,
  missing, empty, malformed, permanent read-failure, and permanent write-failure
  cases.

### Windows builds

- Added a modern Release x64 build using the v143 toolset.
- Preserved Windows XP SP3 x86 compatibility in the Release x86 build and
  validated the same executable on Windows 11 x64 through WOW64.
- Added optional external Windows Terminal profile installation and removal
  without changing `settings.json`, the default terminal, or the classic
  shortcut. Windows Terminal is not required by ATC.
- Updated product copyright metadata to `Copyright (C) 2011-2026`.

### Testing

Current validated results for the Release x64 and Release x86 builds:

```text
All: 376 passed, 0 failed
SolverComplex: 14 passed, 0 failed
Txt: 15 passed, 0 failed
Settings: 7 passed, 0 failed
```

The exact x86 release executable also passed manual smoke tests on Windows XP
SP3 x86 and Windows 11 x64 through WOW64.

The optional Windows Terminal profile was also approved manually on Windows 11.
The profile identity and icon, interactive calculations, `calendar`, resizing,
scrolling, persistence, and user-selected colors behaved as expected.

## 2.1.7 - 2026-06-09

### Added

- Added persistent switching between `double` and Boost `mp_float` precision
  modes.
- Added automated regression coverage based on documented ATC behavior.
- Added memory stress tooling for repeated polynomial, roots-to-polynomial, and
  equation-solver scenarios.
- Added broader regression coverage for automatic multiplication deduction.
- Added coverage for matrix-variable use with `min`, `max`, and `avg`.
- Added Windows 11 console behavior checks.
- Added Linux-style Tab completion for the interactive prompt, including
  documented commands, mathematical functions, dynamic user functions and
  repeated-Tab cycling through ambiguous matches.
- Added Up/Down command history navigation while typing expressions.
- Added a script benchmark runner for the Multiplication Table 1-100 workflow.

### Changed

- Improved fixed decimal output for high-precision constants such as `pi` and
  `e`.
- Improved `verbose resolution` output so user-facing calculation traces are
  clearer and internal menu input evaluation remains quiet.
- Relaxed variable-name restrictions while preserving exact reserved names.
- Improved Windows 11 console behavior, including default intro handling and
  color mapping under Windows Terminal.
- Improved Release heap reserve/commit settings for x64 and x86 builds.
- Improved autocomplete ordering so the shortest closest match is inserted
  first and subsequent Tab presses can cycle alternatives.
- Improved script execution performance for common `print("...", ...)`
  statements by avoiding the temporary TXT-processing path when the command can
  be handled safely in memory.
- Improved script loop throughput by evaluating simple scalar script
  assignments, loop conditions and integer `print` arguments without invoking
  the full expression-processing path.
- Reduced script memory pressure by avoiding large matrix scratch allocations
  for scalar expressions in `initialProcessor()`.

### Fixed

- Fixed `dp50dppi`, `dp50dpe`, and related high-precision formatting paths.
- Fixed several textual polynomial paths for `solve equation(...)`.
- Fixed polynomial simplification for simple textual polynomials and simple
  products of polynomial factors.
- Fixed rational-cancellation paths used by `simplify polynomial(...)`,
  `solver(...)`, and `solve equation(...)`.
- Fixed solver/equation paths involving symbolic constants such as `pi`, `e`,
  and complex `pii`.
- Fixed avoidable dynamic-allocation and release issues in several common
  numeric paths.
- Fixed repeated script-processing allocation growth in `processTxt()`,
  `initialProcessor()`, and `arithSolver()`.

### Testing

- Historical validated regression result for ATC 2.1.7 Release x64 and Release
  x86:

```text
Summary: 377 passed, 0 failed
```

- Current isolated coverage result:

```text
Summary: 68 passed, 0 failed
```

- Current script benchmark result for `Multiplication Table 1-100` on Release
  x64:

```text
Summary: 4 passed, 0 failed
```

See `docs/Testing.md` and `tests/ATC_AUTOMATED_TEST_CASES.md` for more detail.
