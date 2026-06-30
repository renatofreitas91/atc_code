# GitHub Actions CI Plan

This document proposes a GitHub Actions CI workflow for Advanced Trigonometry
Calculator (ATC). It is a planning document only. The proposed workflow is kept
outside `.github/workflows/` until the project is ready to enable CI on GitHub.

## Goals

- Build ATC automatically on Windows.
- Validate the Release x64 target.
- Validate the Release x86 target where the runner environment supports it.
- Run the main regression suite.
- Run the dedicated matrix parallelism tests.
- Prevent test runners from sharing the same ATC data directory.
- Document known CI limitations before activation.

## Proposed Workflow File

The proposed workflow is stored at:

```text
docs/ci/atc-ci.proposed.yml
```

To activate it later, copy or move it to:

```text
.github/workflows/atc-ci.yml
```

Do not activate it until the Visual Studio/MSBuild environment has been
confirmed on the selected GitHub runner.

## Execution Model

The proposed workflow uses sequential jobs:

1. `build-x64`
2. `test-x64`
3. `build-x86`
4. `test-x86`

The jobs are intentionally sequential because ATC regression runners mutate
settings, variable files and temporary files in the ATC data directory. Each
test job must use its own isolated `-AtcDataDir` under `RUNNER_TEMP`.

The workflow must not run the regression suite and matrix tests in parallel
against the same data directory.

## Build Strategy

The solution file is:

```text
Advanced Trigonometry Calculator.sln
```

Primary build command:

```powershell
msbuild ".\Advanced Trigonometry Calculator.sln" /p:Configuration=Release /p:Platform=x64 /m:1
```

x86 build command:

```powershell
msbuild ".\Advanced Trigonometry Calculator.sln" /p:Configuration=Release /p:Platform=x86 /m:1
```

`/m:1` is recommended initially to reduce risk from old Visual Studio project
settings, precompiled headers and shared intermediate outputs.

## Test Strategy

Main regression runner:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1 `
  -AtcExe .\x64\Release\atc.exe `
  -AtcDataDir "$env:RUNNER_TEMP\atc-data-regression-x64"
```

Matrix parallelism runner:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-matrix-parallelism.ps1 `
  -AtcExe .\x64\Release\atc.exe `
  -AtcDataDir "$env:RUNNER_TEMP\atc-data-matrix-x64"
```

The x86 job should use equivalent isolated directories, for example:

```text
%RUNNER_TEMP%\atc-data-regression-x86
%RUNNER_TEMP%\atc-data-matrix-x86
```

## Matrix Parallelism Validation

The dedicated matrix tests compare:

- serial execution forced with `ATC_DISABLE_MATRIX_PARALLELISM=1`;
- default runtime behavior;
- deterministic repeated execution.

The compile-time switch `ATC_ENABLE_MATRIX_PARALLELISM=0` is not proposed as a
mandatory CI gate yet. It can be added later as a separate build matrix entry if
CI time and runner compatibility are acceptable.

## Known Limitations

- The Visual Studio project currently targets `v141_xp`.
- GitHub-hosted Windows runners may not include all XP-compatible C++ toolset
components by default.
- If `v141_xp` is unavailable on hosted runners, the project should use a
self-hosted Windows runner with the validated Visual Studio/MSBuild setup.
- The workflow must not assume that x86 is always available on every runner.
- Test runners must not run in parallel unless each process has a fully
isolated ATC data directory.
- The CI proposal does not replace manual validation of console UI behavior,
Windows 11 terminal rendering, package layout or SourceForge ZIP validation.

## Activation Checklist

Before enabling the workflow:

1. Confirm that the selected runner can build `v141_xp`.
2. Confirm x64 Release build success.
3. Confirm x86 Release build success or mark x86 as allowed to fail while the
   runner is being prepared.
4. Confirm main regression suite passes with isolated `-AtcDataDir`.
5. Confirm matrix parallelism tests pass with isolated `-AtcDataDir`.
6. Confirm no CI job writes to the developer/user default ATC data directory.
7. Decide whether artifacts should be uploaded for x64/x86 executables.

## Future Improvements

- Add an optional compile-time-disabled matrix parallelism job.
- Add a lightweight matrix benchmark job that runs manually with
  `workflow_dispatch`.
- Add package validation once the SourceForge release package layout is final.
- Add documentation link checks after the docs structure stabilizes.
