# ATC 2.1.8 final candidate rev3 manifest

Date of candidate preparation: 2026-08-25. This is not an official release
date. No compilation, tag, signing, upload, or publication was performed during
candidate preparation or the subsequent close-out commits.

## Source and executable provenance

- Worktree HEAD: `fddfb9f3e9b6c1fa32e918b267b6f83bb307800b`.
- Package content: that HEAD plus the reviewed, uncommitted Windows Terminal
  integration and current documentation changes listed by `git status`.
- x64 source executable: `build/windows-terminal-x64-release/bin/atc.exe`.
- x86 source executable: `build/xp-x86-release/bin/atc.exe`.
- Packaging reused the approved files byte for byte. It did not rebuild or edit
  either PE file.

| Candidate | Configuration/toolset | Executable size | Executable SHA-256 |
| --- | --- | ---: | --- |
| Windows x64 | Release, x64, v143 | 2,422,272 | `CA4E41D1F9F3ACBE76CBD5DC3F6736F43A21A0CC51052439C036DB49D15109BF` |
| Windows XP/WOW64 x86 | Release, Win32, v141_xp / MSVC 14.16 | 2,349,056 | `9FA3EAC41D9CEA7680EC66B5665E92F695C2A17E89FE9531F9608D8043F0CDAB` |

`fc /b` reported no differences between each source executable and its
extracted package copy. Static x86 evidence confirms machine `14C` (x86),
Windows CUI, OS version 5.01, subsystem version 5.01, and no direct imports of
`InitializeCriticalSectionEx`, `FlsAlloc`, `FlsFree`, `FlsGetValue`,
`FlsSetValue`, or `IsThreadAFiber`.

## Candidate archives

| Archive | Size | SHA-256 |
| --- | ---: | --- |
| `ATC-2.1.8-final-candidate-rev3-Windows-x64.zip` | 1,210,368 | `29C6A67DE31913E5796F4DB7A093FF6EACEA300BB3CF9403900FFAEEE47B44C0` |
| `ATC-2.1.8-final-candidate-rev3-Windows-XP-WOW64-x86.zip` | 1,122,893 | `A7A66E6E7BFEC6039317EC7645E033A9F12728A92E37078D59E429966C5248BB` |

Each archive contains `atc.exe`, the bilingual PDF user guide, changelog,
license, source/version/readme notices, English and Portuguese Markdown guides,
and `checksums.txt`. `Windows-Terminal-Integration` contains only the installer,
uninstaller, local README, and official icon. The integration is optional on
modern Windows and is never executed automatically; direct `atc.exe` remains
the primary Windows XP path.

The archives contain no worktree, `.git`, build/output/test caches, generated
runtime state, ATC 3 files, embedded personal path, private-key marker, or
password assignment.

## Validation

- Both archives were extracted to new directories whose paths contain spaces.
- Required inventory and every internal SHA-256 entry passed.
- Extracted executable sizes and hashes matched the approved sources.
- The optional profile installed twice without duplication, targeted the
  extracted executable, preserved the sentinel personal `settings.json`, and
  removed only ATC-owned fragment files.
- Command smoke `"1+1"`: x64 and x86 returned result `2`, exit code 0, empty
  stderr, no timeout, and no orphan ATC process.
- A first redirected interactive attempt without the runner's `"atc over cmd"`
  argument timed out after console-size diagnostics. It was terminated and left
  no orphan. The supported command-mode package smoke then passed on both files;
  no executable or archive was changed.
- Previously approved executable regressions remain `All 376/0`,
  `SolverComplex 14/0`, `Txt 15/0`, and `Settings 7/0` for both builds.
- The user manually approved the Windows Terminal integration on Windows 11 and
  the exact x86 candidate in the classic Windows XP environment. Unrecorded
  environment details are not inferred.

## Preserved rev2 archives

| Archive | Size | SHA-256 |
| --- | ---: | --- |
| `ATC-2.1.8-RC1-internal-rev2-Windows-x64.zip` | 1,211,945 | `8388280BA9714EF4F4B6CE449D6968A8BD7226A7A411D0D9C335D66BD83602EC` |
| `ATC-2.1.8-RC1-internal-rev2-Windows-XP-WOW64-x86.zip` | 1,113,994 | `355AC71F06D106429E2645F2DA6E713025B0C5858E15AFD448CAB3EDD48A499E` |

## Git classification and close-out commit structure

The close-out work is separated into small reviewed commits:

1. Windows Terminal integration scripts, icon, package helper, builder, and
   focused automated tests.
2. Windows Terminal technical documentation and manual validation records.
3. Current 2.1.8 changelog/release-note consolidation and this manifest.
4. The independent `versioninfo.rc` copyright correction.
5. The narrow `.gitignore` rule for the accidental nested build directory.

Keep outside Git: PE dumps and header/import transcripts, smoke stdout/stderr,
all `tmp` trees and renderings, extracted package validation directories, ZIPs,
generated builds, and historical output evidence. Preserve them locally until
release closure; do not delete them as part of commit preparation.

ATC 3 planning, clean-core code, and clean CLI material are outside the 2.1.8
candidate scope and are not package members. Multithreading and multicore work
remain possible future 2.x work and are not claimed by 2.1.8.

## Decision

The rev3 archives are technically suitable for future staging and commit
review. They are not a final public release and must not be published, tagged,
or promoted without explicit authorization.

**ATC 2.1.8 - FINAL CANDIDATE PACKAGED AND VALIDATED; AWAITS AUTHORIZATION FOR STAGING, COMMIT, AND PROMOTION.**
