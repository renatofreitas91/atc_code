# ATC 2.1.9 — mandatory separate Windows XP validation

Status: **pending; required for final approval**. The user confirmed this requirement on 2026-10-15. The supported XP architectures (x86, x64 or both) must be established before the native run.

## Identify the exact artifacts and environment

Record the source commit, clean/local source differences, compiler/toolset, C++17 setting, SDK, Release configuration, target architecture, linker subsystem version, executable SHA-256 and runtime dependencies. Transfer and verify the same Windows artifact that was approved by the modern Windows regression run.

Record the Windows XP edition, service pack, OS architecture, machine/VM, CPU features, console configuration, locale and working/data directory. Record x86 and x64 evidence separately if both are in scope. Use isolated data and preserve existing installations/checkouts.

## Native runtime checks

1. Start ATC on the actual Windows XP environment and record startup/loader errors, missing imports or DLL dependencies. Capture the startup screen and the ten-second progress/countdown, including Enter bypass.
2. Run the functional catalog on XP: arithmetic/complex values, multiprecision pi/e, implicit multiplication, lists, matrix dimensions/addition/multiplication, angular solvers, Newton and numerical residuals, polynomial/rational studies, persisted settings and scripts. Preserve per-case input, expected result, output and exit code. The target catalog is the original 376 checks; document any harness limitation and any uncovered case explicitly.
3. The runner itself must run on XP. If its current PowerShell/.NET requirements are unsupported, prepare a compatible harness or external orchestration that starts the ATC binary on XP and captures its native output. Establish equivalent case coverage before approval.
4. Exercise console editing and navigation: Tab completion, Backspace/Delete, left/right arrows, Home/End, history/draft restoration, long lines and file paths with spaces. Test TXT drag-and-drop plus Enter and script-generated output.
5. Exercise one and multiple graph functions: function labels, connected curves, axes, movement bars, numerical f(x), left/right movement, Escape and optional table output. Capture the actual XP console presentation.
6. Exercise repeated launches and normal exits with isolated settings; check for crashes and orphan processes. Any unexpected behavior requires a reproducible case tied to the exact artifact/environment.

## Evidence required for approval

- Exact commit and executable hash for each architecture.
- OS/SP/CPU and build/runtime dependency records.
- Complete per-case results and overall counts, with no uninvestigated failures.
- Console, graph and script integration evidence.
- Explicit coverage gaps and any revised harness used on XP.

Linux ASan/UBSan/LSan results and the 376/376 runs on newer Windows remain separate evidence. XP approval requires its own completed runtime record. No merge, tag or release is implied by this plan.
