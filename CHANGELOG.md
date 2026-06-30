# Changelog

All notable project changes should be documented in this file.

This project uses the existing release documentation as the source of truth.
Dates and version details should be kept aligned with `docs/RELEASE_2.1.7.md`.

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

- Current validated regression result for Release x64 and Release x86:

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
