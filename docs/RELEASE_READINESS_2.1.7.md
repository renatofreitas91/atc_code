# ATC 2.1.7 Release Readiness Checklist

Date: 2026-06-30
Project: Advanced Trigonometry Calculator (ATC)
Target version: 2.1.7
Author: Renato Alexandre dos Santos Freitas
License: GPL-3.0

## Purpose

This document records the final release-readiness status for ATC 2.1.7. It is
intended to support the public release decision without introducing new
features, parser redesigns, solver redesigns, architectural refactors, new
multithreading subsystems or GitHub Actions activation.

## Build Status

Required final builds:

| Target | Configuration | Status | Notes |
|---|---|---|---|
| x64 | Release | Passed | MSBuild 18.3.0, 0 warnings, 0 errors. |
| x86 | Release | Passed | MSBuild 18.3.0, 0 warnings, 0 errors. |

Build notes:

- GitHub Actions remains inactive.
- The proposed CI workflow remains in `docs/ci/atc-ci.proposed.yml`.
- The project still depends on the local Visual Studio/MSBuild environment and
  may require the `v141_xp` toolset for legacy Windows compatibility targets.

## Test Status

Required final validation:

| Test Area | Expected Status | Notes |
|---|---|---|
| Full regression suite | Passed | `377 passed, 0 failed` on x64 Release. |
| Dedicated matrix parallelism tests | Passed | `10 passed, 0 failed` on x64 Release and `10 passed, 0 failed` on x86 Release. |
| Matrix benchmark script | Passed | x64 Release benchmark completed with serial/parallel ratios recorded. |
| Script benchmark | Passed | `4 passed, 0 failed`; elapsed time 10.3 seconds; peak RAM 119.71 MB. |
| `git diff --check` | Passed | No whitespace errors; Git reported only LF/CRLF normalization warnings. |

Test runner notes:

- Automated test runners must not run in parallel against the same ATC data
  directory.
- Each test process should use an isolated `-AtcDataDir` when practical.
- Tests that would open external applications are either mocked, bypassed or
  left as manual validation items.

## Documentation Status

Reviewed documentation areas:

- `README.md`
- `CHANGELOG.md`
- `docs/RELEASE_2.1.7.md`
- `docs/SOFTWARE_REQUIREMENTS_SPECIFICATION.md`
- `docs/Architecture.md`
- `docs/Developer_Guide.md`
- `docs/User_Guide.md`
- `docs/Testing.md`
- `CONTRIBUTING.md`
- `SECURITY.md`
- `CODE_OF_CONDUCT.md`
- `docs/CI_PLAN.md`
- `docs/MULTITHREADING_ANALYSIS.md`
- `docs/ARCHITECTURE_REVIEW.md`
- English documentation under `docs/en/`

Documentation readiness:

- Version references are aligned to ATC 2.1.7.
- The main automated regression count is aligned to `377 passed, 0 failed`.
- Obsolete duplicated release summaries were removed from English-facing
  documentation.
- CI documentation clearly states that GitHub Actions is not active yet.
- Multithreading documentation remains limited to the existing matrix kernel
  implementation.

## Known Limitations

- ATC is not a full general-purpose CAS.
- Some symbolic behavior exists only where explicitly implemented and tested.
- Windows 11 console rendering can still require manual visual validation
  across different console hosts.
- External UI flows such as browser, Explorer, Notepad, shutdown, restart,
  hibernate, sleep and lock are not fully exercised by unattended tests.
- Long-running interactive tools such as clock, stopwatch and timer views are
  partially manual validation targets.
- Full live graph interaction with physical keyboard input remains a manual
  validation area.
- Deep branches of guided modules may still require targeted manual checks even
  when representative automated coverage exists.
- GitHub-hosted CI may not provide the legacy toolset required for all intended
  Windows compatibility targets; a self-hosted runner may be needed later.

## Supported Platforms

Release target:

- Windows native command-line execution.
- x64 Release build.
- x86/Win32 Release build.
- Compatibility goal from older Windows versions through Windows 11, subject to
  the selected compiler/toolset and console host behavior.

Build environment:

- Visual Studio/MSBuild on Windows.
- Build instructions may vary depending on the installed Visual Studio and C++
  toolset.

## Release Risks

| Risk | Level | Mitigation |
|---|---|---|
| Large legacy source files and global state remain in the ATC 2.x codebase. | Medium | Avoid broad refactors during 2.1.7 stabilization; track long-term work in architecture docs. |
| Parser, solver and polynomial paths are complex and interdependent. | Medium | Run the full regression suite before release and avoid behavior changes. |
| Windows console rendering differs across console hosts. | Medium | Keep Windows 11 console validation as a manual release gate. |
| External-application commands are difficult to validate unattended. | Low | Keep automated tests mocked/bypassed and document manual checks. |
| GitHub Actions is not active for the project yet. | Low | Keep CI proposal documented and activate only after runner/toolset verification. |
| Matrix parallelism could regress on very small matrices if thresholds change. | Low | Keep the runtime disable switch and run dedicated matrix tests/benchmarks. |

## Recommendation

ATC 2.1.7 is suitable to remain in release-candidate stabilization after the
successful x64/x86 builds, full regression suite, dedicated matrix tests and
benchmark scripts recorded in this checklist.

The final release commit should still require a manual Windows 11
console/package smoke test before publishing binaries. Further parser redesign,
solver redesign, RAII migration, module splitting, new multithreading
subsystems and ATC 3.x architecture work should remain out of scope for this
release.
