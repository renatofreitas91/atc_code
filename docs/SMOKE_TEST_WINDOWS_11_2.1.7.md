# ATC 2.1.7 Windows 11 Smoke-Test Checklist

Date: 2026-06-30
Target version: Advanced Trigonometry Calculator 2.1.7
Scope: manual Windows 11 release smoke test

## Purpose

This checklist covers the final manual Windows 11 validation pass before
publishing the ATC 2.1.7 package. It complements the automated regression suite
and focuses on console behavior, first-run behavior and user-facing package
flows that should not be fully automated.

## Preconditions

- Use a clean ATC 2.1.7 package candidate extracted from the release ZIP.
- Run on Windows 11 with the default console host or Windows Terminal profile
  intended for release validation.
- Keep GitHub Actions disabled.
- Do not reuse a directory from an older ATC test unless the test explicitly
  checks upgrade or persistence behavior.

## Checklist

| Area | Manual Steps | Expected Result | Status |
|---|---|---|---|
| Clean ZIP extraction | Extract the package into a new folder with a normal user account. | Files extract without permission errors or blocked-file warnings. | Not run |
| First launch | Start `atc.exe` from the extracted folder. | ATC opens without crash, unexpected administrator prompt or unreadable console colors. | Not run |
| Intro/console layout | Observe the startup/initial console state on Windows 11. | No large black artifacts, broken layout, hidden prompt or unusable window controls. | Not run |
| Basic arithmetic | Run `2+2+2`. | ATC returns `#0=6` or equivalent indexed result. | Not run |
| Solver command | Run `solver(sin(x)-0.5)` in degree mode or a known stable solver command. | ATC returns the expected numeric result without syntax errors or hangs. | Not run |
| Equation solver | Run `solve equation((x-1)(x-2))` and decline export with `0`. | ATC prints roots `2` and `1`, then returns to the prompt. | Not run |
| Matrix command | Create a small matrix variable and run addition, multiplication and transpose. | Matrix output is formatted correctly and the prompt remains responsive. | Not run |
| Script execution | Run a bundled script example from `Scripts examples`. | Script completes, prints expected output and does not cause excessive memory growth. | Not run |
| TXT/file processing | If included in the package, run a small `solve txt` or predefined TXT flow. | A response file is generated or handled as documented, without opening unexpected apps during validation. | Not run |
| User guide/documentation | Open the included user guide or documentation file from the package. | Documentation opens successfully and matches ATC 2.1.7 naming/version expectations. | Not run |
| Settings persistence | Change a safe setting, exit ATC, restart ATC and inspect the setting. | The setting persists as documented and can be restored. | Not run |
| High precision persistence | Toggle high precision on and off with the documented command. | ATC persists the selected precision mode across restart. | Not run |
| Matrix parallelism disable switch | Start ATC with `ATC_DISABLE_MATRIX_PARALLELISM=1` and run a matrix operation. | Matrix output remains correct, proving the serial fallback path is usable. | Not run |
| Exit behavior | Use `exit` and close through the window controls. | ATC exits cleanly with no hanging process. | Not run |
| Error handling | Run a malformed expression such as `2++22`. | ATC reports a controlled syntax error and remains usable. | Not run |
| General stability | Repeat a few commands in the same session. | No unexpected warnings, crashes, memory spikes or corrupted prompt state. | Not run |

## Pass Criteria

- No crash, hang or forced termination.
- No unexpected administrator requirement for normal calculator use.
- No unreadable Windows 11 console rendering.
- No unexpected warning or error during the tested commands.
- Settings and precision persistence behave as documented.
- The package documentation opens and identifies ATC 2.1.7.

## Notes

- This checklist is intentionally manual because Windows 11 console rendering
  and packaged-document opening are user-environment dependent.
- If a failure is found, record the Windows build, console host, package path,
  command sequence and screenshots where useful.
