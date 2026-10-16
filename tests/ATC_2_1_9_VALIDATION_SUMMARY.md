# ATC 2.1.9 validation checkpoint

Evidence reviewed on 2026-10-16. No release, merge or version-label change is implied.

Reference: `3f0725bad149c5871b95acfa20907cdc0373b7b6`.
Windows/XP binaries were built before the documentation checkpoint; the commit
records their source fixes and evidence. This is not a claim that each binary
was rebuilt from a clean checkout of that final commit.

| Platform / mode | Reviewed result | Evidence |
| --- | --- | --- |
| Modern Windows x64 Release v141_xp/C++17 | 376/376 | Final Windows runner logs |
| Modern Windows Win32 Release v141_xp/C++17 | 376/376 | Final Windows runner logs |
| Native Windows XP Professional SP3 x86 | 376/376 | xp-8e47a9692894.zip; committed XP report |
| Linux GCC Release | 128/128 | testes.zip: original logs and results.json |
| Linux GCC ASan/UBSan | 128/128 | testes.zip: original logs and results.json |
| Linux leak-enabled LSan, consolidated | 128/128 | Original five passing suites plus two separated-log rechecks |

Windows uses 369 processes and seven net auxiliary checks, not 376 distinct
processes. The XP record explains eight direct auxiliary assertions and the
two-process TXT group counted as one logical check. Linux uses different coverage:
functional 35, input 8, additional/multiprecision 40, study 26, scripts 7,
graph 2 and terminal 10. Counts across platforms are not equivalent coverage.

## Linux evidence audit

GCC 15.2.0; CMake 4.2.3; Boost 1.90.0 as recorded in the supplied report.
Both optimized builds succeeded. All 21 original suite-log hashes matched
results.json. The JSON records a clean source worktree and unchanged source
hashes after execution; this is recorded evidence, not a remote checkout inspection.

The original driver returned 1 with linux_approved=false. Leak-enabled functional
and additional suites counted 9/35 and 14/40: verbose sanitizer stderr was appended
to application stdout, invalidating anchored comparisons even when the numeric
answer was correct (for example, 1+1 returned #0=2). Thus original LSan was 76/128.
That original failure is retained, not overwritten by the consolidated result.

Recheck archives lsan-functional-separated.zip and lsan-additional-separated.zip
contain 35/35 and 40/40 PASS respectively, both exit 0, with detect_leaks=1,
halt_on_error=1, verbosity=1 and log_threads=1. Only diagnostic routing changed
via log_path. All 75 sanitizer files show leak checks and thread inspections;
no sanitizer error, leak report or inspection failure was found. Functional
verification records binary SHA-256
`a052b399bc32c1aa9a423899ff9c617d4770905d77c739b80ce8d36c1a72a580`,
matching the original instrumented build. Additional verification records the
same executable path but no independent binary hash: exact binary identity there
relies on the supplied execution record. No binary was included for rehashing.

## Remaining work

- Run the updated diagnostic-separating driver on Linux to establish one complete
  successful execution. Portable infrastructure tests alone do not validate Linux.
- Review unresolved file-I/O failure paths before deciding whether more engine
  fixes are required; do not equate this checkpoint with complete I/O safety.
- Assemble and smoke-test final distribution packages with assets and dependencies.
- Obtain explicit authorization before changing the displayed version, committing,
  pushing, merging, tagging or releasing.

No sanitizer findings in tested paths is not proof of absence of all memory defects.

## Subsequent base/SI candidate, awaiting cross-validation

The changes after the reference checkpoint correct B/O/H token handling and
fractional conversion, signed/scientific base output, SI factors in the active
numeric type and multiprecision formatting. They remove absolute-magnitude
zeroing of ordinary results and address exact sinc zeros and finite real integer
powers at their origin. No private ATC 3.0 implementation is imported, and the
displayed application version is not changed.

Final modern Windows results on both x64 and Win32: Release v141_xp/C++17 build
PASS, All 376/376, base literals 58/58, signed-base output 44/44 and SI/control
160/160. No final crashes, timeouts, infrastructure errors or runner-owned orphan
processes. Win32 retains the pre-existing C4018 warning. These new changes still
require Linux Release/ASan/UBSan/LSan and native XP execution. See
ATC_2_1_9_CURRENT_REVALIDATION.md for the Linux procedure and the recovered backlog
for root causes and preserved intermediate failures. Historical approvals above
are not approvals of this new candidate. Commit/push is authorized only for the
validation checkpoint, not merge, tag or release.
