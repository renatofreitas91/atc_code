# ATC 2.1.8 Release Notes

Official release date: 2026-08-25 (25 August 2026 / 25 de agosto de 2026).

## Full release notes

### Advanced Trigonometry Calculator 2.1.8

ATC 2.1.8 is a correctness and compatibility update for the existing
calculator.

#### Solver

- Candidate roots are checked against the original expression before they are
  returned.
- The solver handles validated real and complex roots, including complex
  polynomial cases.
- A general numerical fallback is available when the earlier solving path does
  not produce a valid root.
- Direct calculations using stored complex results and general exponent
  expressions are evaluated consistently.
- When no validated candidate is found, ATC reports
  `ATC was unable to find a valid solution.`

#### Robustness

- Settings-file retry loops are bounded.
- File handles are closed safely across valid, missing, empty, malformed and
  permanent I/O failure cases.
- Regression coverage includes consecutive settings runs and persistent read
  and write failures.

#### Windows builds

- **Windows x64:** recommended modern build for compatible x64 Windows.
- **Windows x86:** compatible with Windows XP SP3 x86 and validated on modern
  x64 Windows through WOW64.

The x86 statement applies to the exact released x86 artefact. It does not imply
that x64 supports Windows XP or that every future build will have the same hash.

- Added an optional external Windows Terminal profile integration while
  preserving the classic Console Host path and shortcut.
- Windows Terminal remains optional and is not a dependency of either
  executable. The integration was manually confirmed on Windows 11, and the
  x86 executable was manually confirmed in the classic Windows XP environment.
- Product copyright metadata is `Copyright (C) 2011-2026`.

#### Validation

- All: 376 passed, 0 failed.
- SolverComplex: 14 passed, 0 failed.
- Txt: 15 passed, 0 failed.
- Settings: 7 passed, 0 failed.
- No orphan ATC processes were observed after the automated suites.

#### Updating

1. Download the package matching the required architecture.
2. Extract it to a new directory rather than overwriting a running copy.
3. Preserve user-created settings or data files before replacing an older
   directory.
4. Verify the package with the published SHA-256 checksum.
5. Start `atc.exe` from the extracted directory.

Final package SHA-256 checksums:

- Windows x64: `1D971C0837AF730AFA16D12A01B87A0A95057B5C2B70431FABF11A1E47DD4CA4`
- Windows XP/WOW64 x86: `1AA015FC488DD851DB1EFC51217D67E50D26A877D5CF3FAF880B148568D26576`

## Short announcement

ATC 2.1.8 improves real and complex equation solving by validating returned
roots and adding a general numerical fallback. It also hardens settings-file
handling and retains a Windows XP SP3-compatible x86 build that has been tested
on modern Windows through WOW64. A modern x64 build is available for compatible
x64 Windows. The final package SHA-256 checksums accompany the release.
