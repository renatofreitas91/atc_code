# ATC 2.1.9 — mandatory separate Windows XP validation

Status: **R2 native automatic catalogue passed; manual checks confirmed by the user**.
The mandatory target is Windows XP x86 (32-bit). This approval covers the tested
artifact and paths, not every possible runtime condition or a final release.

## Completed R2 validation

The received `xp-8e47a9692894.zip` records Windows XP 5.1 build 2600 SP3,
Python 3.4.4 x86 and **376/376 PASS**, with 369 ATC processes and no recorded
failures, timeouts, crashes or infrastructure errors. The audit verified the
archive CRC, executable identity, catalogue/runner/source hashes and consistency
of all 738 stdout/stderr logs. Output and solver-residue assertions were checked
again from the archived streams. Intermediate file assertions remain supported
by the recorded native runner evaluation.

The Win32 executable SHA-256 is
`ab787b1b4d73fd9fa2069cc5bb4db837efd27aa41f5bddb84d0b9150aeb3a198`.
The evidence ZIP SHA-256 is
`8db9b7b5566c8805967ad0ba0fcfc92cb2f6a9ac6566d1ba80ff265212b9e2fe`.
`calendar(2026)` passed in 0.201 seconds under the unchanged official
20-second process timeout. The previous calendar crashes/timeouts did not recur
in that complete run. The user subsequently confirmed the manual console,
startup, graph/TXT checks and repeated interactive calendar calls with normal
idle CPU. These manual confirmations are user-reported evidence.

The artifact was built with Release Win32, MSVC 14.16/v141_xp, C++17,
Windows SDK 7.1A targeting components and subsystem version 5.01. Modern Windows
Win32 and x64 All runs also passed 376/376 for the same application sources.

The tested source was based on `4ba2078303283426a92031d917a85cbe5db1e7da`
with the local source hashes recorded in `ATC_2_1_9_XP_R2_RESULTS.json`.
The checkpoint commit normalizes two trailing-whitespace lines. The local IDE
toolset selection and window dimensions are excluded from the published patch;
the validation builds explicitly overrode the toolset to v141_xp. Raw archives,
binaries and logs remain outside Git. Linux revalidation of these newer source
changes is pending.

The following procedure remains the reproducibility checklist for future builds.

## Identify the exact artifacts and environment

Record the source commit, clean/local source differences, compiler/toolset, C++17 setting, SDK, Release configuration, target architecture, linker subsystem version, executable SHA-256 and runtime dependencies. Transfer and verify the same Win32 artifact that was approved by the modern Windows regression run.

Record the Windows XP edition, service pack, OS architecture, machine/VM, CPU features, console configuration, locale and working/data directory. Identify all native runtime evidence as Windows XP x86 (32-bit). Use isolated data and preserve existing installations/checkouts.

## Native runtime checks

1. Start ATC on the actual Windows XP environment and record startup/loader errors, missing imports or DLL dependencies. Capture the startup screen and the ten-second progress/countdown, including Enter bypass.
2. Run the functional catalog on XP: arithmetic/complex values, multiprecision pi/e, implicit multiplication, lists, matrix dimensions/addition/multiplication, angular solvers, Newton and numerical residuals, polynomial/rational studies, persisted settings and scripts. Preserve per-case input, expected result, output and exit code. The target catalog is the original 376 checks; document any harness limitation and any uncovered case explicitly.
3. The runner itself must run on XP. If its current PowerShell/.NET requirements are unsupported, prepare a compatible harness or external orchestration that starts the ATC binary on XP and captures its native output. Establish equivalent case coverage before approval.
4. Exercise console editing and navigation: Tab completion, Backspace/Delete, left/right arrows, Home/End, history/draft restoration, long lines and file paths with spaces. Test TXT drag-and-drop plus Enter and script-generated output.
5. Exercise one and multiple graph functions: function labels, connected curves, axes, movement bars, numerical f(x), left/right movement, Escape and optional table output. Capture the actual XP console presentation.
6. Exercise repeated launches and normal exits with isolated settings; check for crashes and orphan processes. Any unexpected behavior requires a reproducible case tied to the exact artifact/environment.

## Evidence required for approval

- Exact commit and executable hash of the Win32 artifact executed on XP x86.
- OS/SP/CPU and build/runtime dependency records.
- Complete per-case results and overall counts, with no uninvestigated failures.
- Console, graph and script integration evidence.
- Explicit coverage gaps and any revised harness used on XP.

Linux ASan/UBSan/LSan results and the 376/376 runs on newer Windows remain separate evidence. XP approval requires its own completed runtime record. No merge, tag or release is implied by this plan.
