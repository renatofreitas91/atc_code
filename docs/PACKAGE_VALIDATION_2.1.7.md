# ATC 2.1.7 Package/ZIP Validation Checklist

Date: 2026-06-30
Target version: Advanced Trigonometry Calculator 2.1.7
Scope: final package candidate validation

## Purpose

This checklist defines the manual package checks required before publishing an
ATC 2.1.7 ZIP on the public download page. It does not create the final ZIP and
does not replace the automated regression suite.

## Package Naming

Recommended naming convention:

```text
Advanced Trigonometry Calculator 2.1.7.zip
```

If a platform-specific package is prepared, include the target explicitly:

```text
Advanced Trigonometry Calculator 2.1.7 Windows.zip
Advanced Trigonometry Calculator 2.1.7 x64.zip
Advanced Trigonometry Calculator 2.1.7 x86.zip
```

## Checklist

| Area | Validation Step | Expected Result | Status |
|---|---|---|---|
| Package identity | Confirm ZIP filename, extracted folder name and visible documentation mention ATC 2.1.7. | Naming is consistent and release-ready. | Not run |
| x64 executable | Confirm the expected x64 `atc.exe` is present if the package includes x64 binaries. | Executable launches on supported Windows x64 systems. | Not run |
| x86 executable | Confirm the expected x86/Win32 `atc.exe` is present if the package includes x86 binaries. | Executable launches on supported Windows systems. | Not run |
| Required resources | Confirm icons, resource files and bundled text/help files are present. | ATC starts with correct metadata and no missing-resource errors. | Not run |
| Required DLLs | Check whether the package requires external DLLs or runtime files. | Required runtime dependencies are included or clearly documented. | Not run |
| Documentation | Confirm user guide, release notes, license and relevant documentation are included. | Documentation opens and references ATC 2.1.7. | Not run |
| Examples | Confirm `Scripts examples` or equivalent example content is included. | Example scripts are usable from the package layout. | Not run |
| License | Confirm GPL-3.0 license information is present. | License file is included and readable. | Not run |
| Version strings | Launch ATC and inspect visible version strings and resource metadata where practical. | Version is 2.1.7 and matches release notes. | Not run |
| Temporary files | Search the package for temporary, debug or local-only files. | No `.obj`, `.pdb` if not intended, logs, temp folders, debug dumps or local paths are shipped. | Not run |
| Source snapshots | If source snapshots are included, confirm they are intentional and current. | Included source content matches the release policy. | Not run |
| First-run behavior | Extract into a clean folder and run ATC. | ATC creates only expected user data and starts without crash. | Not run |
| Windows 10 extraction | Extract and open the ZIP on Windows 10. | ZIP opens and files extract without corruption. | Not run |
| Windows 11 extraction | Extract and open the ZIP on Windows 11. | ZIP opens and files extract without corruption. | Not run |
| Antivirus/SmartScreen note | Observe any blocking or warning behavior during launch. | Any expected warning is documented; no suspicious package artifacts are present. | Not run |
| No CI activation | Confirm the package/repository state does not include an active `.github/workflows` release workflow. | GitHub Actions remains disabled until explicitly activated later. | Not run |

## Suggested File Exclusions

Before creating the public ZIP, exclude:

- build intermediates such as `.obj`, `.tlog`, `.idb`, `.ilk` and temporary
  compiler artifacts;
- local benchmark output;
- local regression temp folders;
- debug logs, crash dumps and editor backup files;
- user-specific absolute paths or generated local settings;
- `.git`, `.vs`, `.venv-docs` and other local tooling state.

## Pass Criteria

- Package extracts cleanly on Windows 10 and Windows 11.
- The expected executable files are present and launch.
- Required documentation, examples, resources and license files are included.
- No temporary/debug/local-only files are included.
- Version strings and package name consistently identify ATC 2.1.7.
- First-run behavior is clean and does not require administrator privileges for
  normal calculator use.

## Notes

- Do not create the final ZIP from this checklist alone; use it to validate the
  final package candidate after the package layout is prepared.
- Do not create a Git tag until the final package candidate has passed this
  checklist and the Windows 11 smoke test.
