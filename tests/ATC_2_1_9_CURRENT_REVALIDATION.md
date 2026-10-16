# Revalidate the ATC 2.1.9 validation branch on Linux

## Current candidate: base literals, signed bases and SI prefixes

The candidate after 3f0725b contains new engine changes. Modern Windows Release
v141_xp/C++17 x64 and Win32 each passed All 376/376, base literals 58/58,
signed-base output 44/44 and SI/numeric controls 160/160. These groups overlap
coverage and must not be added as unique tests. Linux and native XP have NOT
yet been revalidated for this candidate; the older approvals below do not apply.

On the Linux VM, update the validation branch without merging local changes:

```sh
git switch validation/atc-2.1.9-linux-fixes
git pull --ff-only
git rev-parse HEAD
git status --short
python3 tests/test-linux-checkpoint-driver.py
python3 tests/revalidate-atc-linux-checkpoint.py --check-only
python3 tests/revalidate-atc-linux-checkpoint.py
```

After the driver finishes, use the exact executable paths recorded in its new
results directory. Run the three focused suites separately on BOTH the Release
and ASan/UBSan executables (replace /absolute/path/to/atc below):

```sh
python3 tests/run-atc-base-literals.py /absolute/path/to/atc
python3 tests/run-atc-signed-bases.py /absolute/path/to/atc
python3 tests/run-atc-si-prefixes.py /absolute/path/to/atc
```

Expected focused counts are 58, 44 and 160. The optional --baseline argument of
the signed-base runner adds byte-identical positive-output comparisons against a
separately built prior binary; without it only current mathematical/history
checks run. Preserve every new results directory and sanitizer log. The driver
still owns the historical 128 checks per mode; focused results are separate.
No expectation or process deadline has been increased. A failing or incomplete
run must not be called approved, and absence of diagnostics is not universal
memory-safety proof. Send the complete logs/results back for review.

## Previous published checkpoint (historical evidence)

Modern Windows x64 and Win32 each passed 376/376. The received native XP SP3 x86
R2 archive also passed 376/376; see `ATC_2_1_9_WINDOWS_XP_VALIDATION.md` and
`ATC_2_1_9_XP_R2_RESULTS.json`. Linux evidence for checkpoint
`3f0725bad149c5871b95acfa20907cdc0373b7b6` has now also been reviewed:
Release 128/128, ASan/UBSan 128/128 and consolidated LSan 128/128.
See `ATC_2_1_9_VALIDATION_SUMMARY.md` for provenance and the original driver failure.
The subsequent engine and driver changes require a new real Linux execution.

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

Sanitizer diagnostics now use a separate, new directory for each suite and mode.
The driver scans both the suite output and all separate sanitizer files for errors,
and records their SHA-256 hashes. LSan still runs with leak detection, verbosity
and thread inspection enabled; missing inspection evidence is an infrastructure
error. No application expectations or deadlines have changed. Portable driver
checks can be run with `python3 tests/test-linux-checkpoint-driver.py`; they do
not substitute for running the full driver on Linux.

No merge, tag or release is implied by this validation branch.
