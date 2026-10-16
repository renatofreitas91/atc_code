# Revalidate the Windows/XP R2 source checkpoint on Linux

Modern Windows x64 and Win32 each passed 376/376. The received native XP SP3 x86
R2 archive also passed 376/376; see `ATC_2_1_9_WINDOWS_XP_VALIDATION.md` and
`ATC_2_1_9_XP_R2_RESULTS.json`. These results do not approve the latest changes
on Linux. The earlier Linux 128/128 records apply to the older source checkpoint.

From a new or clean checkout of `validation/atc-2.1.9-linux-fixes` on Linux:

```sh
git pull --ff-only
python3 tests/revalidate-atc-linux-checkpoint.py --check-only
python3 tests/revalidate-atc-linux-checkpoint.py
```

The driver supports both a Git checkout and a source archive with CHECKPOINT.json.
It records the exact revision and source hashes before building and verifies the
files remain unchanged after the run. Use a normal Linux terminal where LSan can
suspend threads. Requirements are Python 3.9+, CMake 3.20+, GCC/C++17, Boost and
the util-linux `script` command. Nothing is installed automatically.

Two fresh optimized builds are made: Release with `-O3 -DNDEBUG`, and the same
optimization with ASan/UBSan and diagnostic symbols. The instrumented executable
is reused for a separate leak-enabled LSan pass. Each of Release, ASan/UBSan and
LSan executes seven suites: functional 35, input 8, additional/multiprecision 40,
studies 26, scripts 7, graphs 2, terminal/startup 10. Expected coverage is 128 in
each mode. All existing expectations and per-case deadlines are preserved.

Results are retained under a new `work/linux-revalidation-...` directory, including
compiler/build logs, binary hashes, environment options and per-suite logs. Send
that complete folder back for audit. The driver reports build failures, missing
or incomplete execution, sanitizer diagnostics and test failures separately;
unexecuted cases are not declared failed. Graphs under instrumentation can take
several minutes. The default is one build job; `--jobs 2` is optional.

No merge, tag or release is implied by this validation branch.
