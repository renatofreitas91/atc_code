# ATC 2.1.8 Final Release Rev4 Manifest

Official release date: 2026-08-25 (25 August 2026 / 25 de agosto de 2026).

## Provenance

- Source branch: `atc-2.1.8-rc1-editorial-finalization`.
- Initial revision for this phase: `fcc9163dc890203bae22ef35b7c4be5b68ea9cb1`.
- The approved ATC executables were frozen before rev4 packaging and were not rebuilt.
- The operational OneDrive tree was inventoried read-only. Its older executables and runtime-created user files were excluded.
- Rev4 staging and generated evidence are outside Git under `outputs/final-release-rev4-approved`.

## Frozen Executables

| Architecture | Configuration | Size | SHA-256 |
| --- | --- | ---: | --- |
| x64 | Release, x64, v143 | 2,422,272 bytes | `CA4E41D1F9F3ACBE76CBD5DC3F6736F43A21A0CC51052439C036DB49D15109BF` |
| x86 | Release, Win32, v141_xp / MSVC 14.16 | 2,349,056 bytes | `9FA3EAC41D9CEA7680EC66B5665E92F695C2A17E89FE9531F9608D8043F0CDAB` |

Both report `FileVersion 2.1.8.0` and `ProductVersion 2.1.8.0`. The x86 image is PE x86, Windows CUI, with OS and subsystem version 5.01. Its import table does not contain `InitializeCriticalSectionEx`, `FlsAlloc`, `FlsFree`, `FlsGetValue`, `FlsSetValue`, or `IsThreadAFiber`.

## Final ZIP Packages

| Package | Size | SHA-256 |
| --- | ---: | --- |
| `ATC-2.1.8-final-release-rev4-Windows-x64.zip` | 1,210,161 bytes | `1D971C0837AF730AFA16D12A01B87A0A95057B5C2B70431FABF11A1E47DD4CA4` |
| `ATC-2.1.8-final-release-rev4-Windows-XP-WOW64-x86.zip` | 1,122,687 bytes | `1AA015FC488DD851DB1EFC51217D67E50D26A877D5CF3FAF880B148568D26576` |
| `Advanced Trigonometry Calculator.zip` (combined public package) | 2,392,519 bytes | `8694E70AC9FFCEF1E9664574C73AC811C35F39A60B7ADF927DB359022C949B02` |

The packages passed inventory, internal checksum, path-with-spaces extraction, Windows Terminal integration, prohibited-content, and command-mode `1+1` checks. Both command-mode runs returned `#0=2`, with empty standard error, no timeout, and no orphan ATC process.

## Installer Definitions

The original operational Inno Setup files were preserved unchanged and replaced for version control by parameterized definitions in `tools/installer`. The definitions:

- set version 2.1.8, file version 2.1.8.0, and copyright 2011-2026;
- preserve the historical AppId so 2.1.8 upgrades or replaces the corresponding installation;
- install per-user in the writable `{userdocs}` tree without elevation;
- retain Start Menu and optional desktop/legacy Quick Launch shortcuts;
- remove automatic startup and forced `taskkill /f` behavior;
- use normal Inno close-application handling;
- declare x64 mode for x64 and Windows XP SP3 minimum for x86;
- include Windows Terminal integration as content only and never enable it silently.

Inno Setup 5.6.1 compiled both definitions successfully:

| Installer | Size | SHA-256 |
| --- | ---: | --- |
| `Setup-ATC-2.1.8-Windows-x64.exe` | 1,398,866 bytes | `F71DD3A770C872D506FF73DAE1CFBEB19E474CDFF8DF289E3372C0B675B1BA02` |
| `Setup-ATC-2.1.8-Windows-XP-WOW64-x86.exe` | 1,333,262 bytes | `9EAC3D3868B8F5016F2E1884983A5A2DFF7FA1525D0DC8DD55BF61B2883EBC81` |

Static metadata inspection passed. The exact x64 and x86 setup hashes completed real install, payload-hash, command-mode `1+1`, and uninstall validation on Windows 10 with exit code 0, empty standard error, and no orphan ATC process. The exact x86 setup also installed and operated successfully on Windows XP SP3 x86.

## Current Gate

The rev4 ZIP packages and both installers are approved. The release source is ready for the annotated local `v2.1.8` tag and publication to the public GitHub repository. Signing and site publication remain separate actions.
