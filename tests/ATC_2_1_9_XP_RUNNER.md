# Native Windows XP x86 regression runner

The target runner uses Python 3.4 standard libraries and CMD. Install the official
Python 3.4.4 **x86** MSI in `C:\Python34`. Python 3.5+ does not support XP.

## Preparing the portable package on modern Windows

From the isolated repository worktree, export the authoritative PowerShell suite:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tests\export-atc-xp-catalog.ps1 -AtcExe Release\atc.exe -OutputDirectory work\xp-export-NEW
```

The destination must not exist. The exporter copies the executable, DLLs beside
it, the licence, execution notes, script examples and user functions. It runs the
unmodified assertions of `run-atc-regression.ps1 -Mode All` on an isolated copy.
It writes `catalog.json` only when all official checks pass. The catalogue records
the source commit, original runner hash and executable SHA-256.

Copy `catalog.json`, the exported `package` directory, `run-atc-xp.py` and
`run-atc-xp.cmd` to the delivery directory. Keep `host-capture` and host logs outside
the delivery package. Include the official Python MSI separately if needed.

The exporter records only changes made by the **harness** before each process,
including creation of empty directories. It does not replay executable-produced
state. Persistence, output files, residue checks and external-command mock logs
are therefore evaluated against the target executable's actual results. Expected
output is taken from assertion contracts, never from observed successful output.
Specialized TXT/export predicates are explicitly mirrored in the exporter; review
them against the authoritative functions whenever that suite changes.

## Running in the XP VM

Extract the complete delivery folder to `C:\ATC-XP-tests` (a short path avoids XP's
legacy path length limit). Leave the existing installation untouched. In CMD:

```bat
C:\Python34\python.exe --version
cd /d C:\ATC-XP-tests
run-atc-xp.cmd
```

The CMD wrapper selects the already copied artifact at
`C:\ATC\atc_source\Release\atc.exe`. For a different location pass its full path:

```bat
run-atc-xp.cmd "C:\ATC-XP-tests\package\atc.exe"
```

The runner refuses an executable whose SHA-256 differs from the host-approved
Win32 binary, and verifies its x86 PE machine field. Each run copies that binary
and the supplied assets into a new `runs\xp-...\data` directory and writes a new
`atc_path.txt` there. It does not modify the selected executable's installation.

The official timeout remains 20 seconds per process. A Windows Job Object limits
cleanup to the runner's assigned process and its descendants, using APIs present
in XP. Failure to establish process containment is an infrastructure error.
Stdout/stderr are drained concurrently. Each stream retains the authoritative
200-line/4096-character tail for checks; disk logs are capped at 16 MiB per stream
and truncation is recorded. Results are saved after every event.

`results.json` contains environment/version information, executable/catalog/runner
hashes, command line, stdin, working directory, test environment overrides, exit
codes, assertions, durations and final counts. Copy the entire run folder back
to the host, including `logs`, for review.

## Counts and interpretation

The catalogue contains **369 native ATC processes and eight direct auxiliary
checks**. Two TXT processes form one official logical test. Thus
`369 + 8 - 1 = 376` unique logical checks. The historical summary's “7 auxiliary
checks” is the net difference `376 - 369`, not the raw number of direct checks.
Every event belongs to exactly one logical check; the audit enforces this.

`PASS`, `FAIL`, `TIMEOUT`, `CRASH`, `INFRA_ERROR` and `NOT_RUN` remain distinct.
Exit code 0 means all 376 catalogue checks passed, 1 means test failures, and 2
means infrastructure failure or incomplete execution. `native_xp_x86` records
whether execution actually occurred under Windows 5.1 in a 32-bit interpreter.
Passing on modern Windows does not approve XP.

The catalogue includes simulated graph navigation, not full native console input.
Manual XP startup/countdown, editing keys, history/drafts, drag-and-drop and actual
graph rendering/navigation still require separate evidence as specified in
`ATC_2_1_9_WINDOWS_XP_VALIDATION.md`. Passing this catalogue does not alone close
those interactive requirements.

No application source or expected mathematical value is changed by this runner.
