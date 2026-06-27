# Advanced Trigonometry Calculator Testing

This document explains the current test infrastructure for Advanced
Trigonometry Calculator (ATC).

## Regression Test Runner

The main automated regression runner is:

```text
tests\run-atc-regression.ps1
```

Run it after building ATC:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1 -AtcExe .\x64\Release\atc.exe
```

For x86 builds:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1 -AtcExe .\Release\atc.exe
```

Current validated result for both Release x64 and Release x86:

```text
Summary: 338 passed, 0 failed
```

## Memory Stress Runner

The memory stress runner is:

```text
tests\run-atc-memory-stress.ps1
```

Example:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-memory-stress.ps1 -Iterations 10
```

It currently focuses on repeated polynomial simplification,
roots-to-polynomial, and textual/coefficient equation solver commands.

## Isolated Coverage Helper

The isolated coverage helper is:

```text
tests\run-atc-isolated-coverage.ps1
```

Use it when a specific area needs focused validation outside the full
regression run.

## Current Automated Coverage

The regression suite currently covers:

- arithmetic basics and precedence;
- constants and precision formatting;
- trigonometry and inverse trigonometry;
- hyperbolic and inverse hyperbolic functions;
- logarithms and custom guide syntax;
- complex-number paths used by documented commands;
- matrix/list functions and matrix helper commands;
- variable names and implicit multiplication;
- sorting and ASCII sorting flows;
- roots-to-polynomial report export;
- polynomial simplification;
- equation solving and systems of equations;
- solver paths including selected trigonometric, hyperbolic, polynomial, and
  rational-cancellation cases;
- function study examples;
- graph settings and deterministic graph navigation simulation;
- date/time commands that can be automated safely;
- TXT detector / command bridge commands;
- file/folder command existence checks;
- variable/result management commands;
- persistent settings and menu retry behavior;
- verbose-resolution behavior;
- `double` and Boost `mp_float` precision mode persistence.

The detailed test matrix is maintained in:

```text
tests\ATC_AUTOMATED_TEST_CASES.md
```

## Known Manual or Interactive Validation Gaps

The automated suite intentionally avoids or only partially covers:

- shutdown, restart, hibernate, sleep, lock, and similar PC-control commands;
- clock, stopwatch, timer, and continuously running views;
- commands that open external browsers or editors;
- full live manual graph rendering and key-buffer behavior;
- deeply interactive modules such as triangles, arithmetic matrix solver,
  conversions, finance, physics, microeconomics, and statistics menus.

These areas should be validated manually or covered later with safe,
non-destructive automation.

## Settings Modified by Tests

The regression runner may temporarily touch ATC setting files under:

```text
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator
```

The runner backs up and restores the settings it modifies.

## Recommended Validation Before Changes

For most changes:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1 -AtcExe .\x64\Release\atc.exe
```

For memory-sensitive work, also run the memory stress runner when practical.
