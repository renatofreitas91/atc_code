# ATC 2.1.9: local Linux fixes awaiting release validation

Base commit: `aaeac075f1f76489ea4d2729795d14ba37f3b98d` on
`validation/atc-2.1.9-linux-fixes`. The changes described here are local and
uncommitted. The base commit alone does not identify these fixed binaries.

## Defects and fixes

- A base prefix at position zero read `arithTrig[-1]`, one byte before its
  3100-byte allocation. Check the index before reading the preceding character.
- Overlapping `sprintf` calls corrupted expression construction differently in
  optimized and instrumented builds. Append at the current terminator instead
  of passing the destination as a source. No solver algorithm was changed.
- The square root of a negative real number contained a trigonometric rounding
  residue on its real axis. Calculate that real-axis square root directly.
- Root and logarithm dispatch discarded the evaluated imaginary argument.
  Pass `vI[1]` at the six affected call sites.
- Complex arithmetic discarded small nonzero components during evaluation and
  formatting. Preserve those values; use integer powers and the principal
  square root to preserve exact axes without a blanket numerical clamp.
- Literal result extraction now removes the Linux console-title OSC sequence
  while preserving the original raw log.
- Literal/SI and signed-base runners retained an executable for every case and
  repeatedly hashed it. Hash each source binary once and remove each temporary
  copy after its process exits. Preserve fixtures, stdout, stderr and JSON.
  Timeout and interruption terminate/reap the child before removing its copy.

The C++ changes use existing dependencies and standard C++17 facilities. The
Windows headers already define `NOMINMAX`. Native MSVC v141_xp builds and Windows
execution remain required; this review is not a Windows approval.

## Linux evidence before the directory-handle fix

Results directory relative to the repository:
`work/linux-revalidation-20261016T214613Z-d493f7`.

| Group | GCC Release | Optimized ASan/UBSan |
| --- | --- | --- |
| Main driver | 128/128 | 128/128 |
| Base literals | 58/58 | 58/58 |
| Signed bases | 44/44 | 44/44 |
| SI and numeric controls | 160/160 | 160/160 |
| Complex components and answer references | 50/50 | 50/50 |

The driver includes the original 34 functional checks plus one rational check,
8 input checks, 40 additional checks, 26 study checks, 7 script checks, 2 graph
checks and 10 terminal checks. Groups overlap; these are executions, not a count
of independent tests. ASan/UBSan runs above disabled leak checking and showed no
sanitizer diagnostics in the tested paths.

Builds used GCC 15.2.0, CMake 4.2.3 and Boost 1.90.0, with `-O3 -DNDEBUG`;
instrumentation added `-fsanitize=address,undefined -fno-omit-frame-pointer -g`.
Exact commands, file manifests and binary hashes are retained in `results.json`.

The storage-only runner changes followed those executions. Engine hashes are
unchanged. Eight storage regression checks cover success, launch errors,
timeouts and interruption. A small real ASan/UBSan subset also checked all
three affected suite entry points and left zero per-case executables.

Original results were preserved after removing redundant test executables and
regenerable object files. Canonical binaries, logs, fixtures and JSON remain.
The orchestrator was interrupted after writing its eighth successful row;
its missing final aggregate flag must not be presented as a normal driver exit.

## Native LSan follow-up: directory resource leak

The native run `lsan-recheck-20261016T224159Z-5b84e0` completed all seven
main suites (128/128) with valid leak/thread inspections and no diagnostics.
Its focused literal suite then aborted all 58 processes: each leaked two
32816-byte directory allocations (65632 bytes total). The allocation stack
points to `isContainedInUserFunction()` calling `opendir()`; both its early
match return and normal exhaustion path omitted `closedir()`.

Two `closedir(d)` calls now close successful opens exactly once, before either
return; failed opens remain untouched. No `dirent` data is used after closing.
The same portable `dirent` API is already used elsewhere on Windows and Linux.
No mathematical code changed in this follow-up.

`tests/test-user-function-directory.py` compiles the actual function with
resource counters. It tests missing and empty directories, unmatched files and
the early matching return, repeating successful-open paths 100 times. The old
function fails; the fix passes with ASan/UBSan (leaks disabled in the restricted
session). This isolated check does not replace native full-binary LSan.

The build/test evidence above applies to the preceding local patch. New
full-binary validation is recorded separately under
`work/lsan-directory-fix/validation`; old binaries and raw logs are preserved.

## Release blockers

1. Obtain valid LSan thread-inspection and leak-check reports outside the
   restricted tool session. The original tool-session runs hit ptrace restrictions. The later native run
   found the directory leak described above; absence of leaks cannot be claimed
   for the corrected binary until it has a valid native rerun.
2. Review and fix the final candidate identity before cross-platform validation.
   Preserve the local patch and its hash until the changes are committed.
3. Repeat Windows x64 and Win32 validation and native XP x86 validation using
   that exact candidate. Older 376/376 results do not approve these local fixes.
4. Consolidate source/binary hashes and original logs, review known defects,
   finalize the changelog, and verify version strings and distribution packages.

No commit, push, merge, tag or release is part of this local validation.
