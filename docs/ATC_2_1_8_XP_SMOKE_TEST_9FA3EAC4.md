# ATC 2.1.8 Windows XP SP3 x86 smoke test

## Result

**APPROVED BY MANUAL USER VALIDATION**

The user confirmed that the exact approved x86 candidate started in the classic
Windows environment, passed the smoke and general-use checks, and had no
functional dependency on Windows Terminal. The exact VM metadata, Service Pack
evidence, timestamps, and complete command transcript were not recorded in this
validation report.

Static PE evidence identifies x86, Windows CUI, operating system/subsystem 5.01,
with the audited incompatible direct imports absent. This static evidence is
distinct from the manual runtime confirmation above.

## Required artefact

- Build: Release x86, v141_xp / MSVC 14.16
- Size: 2,349,056 bytes
- SHA-256: `9FA3EAC41D9CEA7680EC66B5665E92F695C2A17E89FE9531F9608D8043F0CDAB`
- PE: x86, Windows CUI, operating system/subsystem 5.01

Before copying to the VM, confirm the import table has no direct references to
`InitializeCriticalSectionEx`, `FlsAlloc`, `FlsFree`, `FlsGetValue`,
`FlsSetValue`, or `IsThreadAFiber`, and no other known XP-incompatible import.

Do not substitute an earlier XP binary or overwrite earlier evidence. Stop if
the independently calculated size or hash differs.

## Environment evidence

1. Record the VM product, architecture, Windows edition, version, and Service Pack.
2. Record the hash tool and its version.
3. Confirm the VM is Windows XP SP3 x86 and has no Windows Terminal dependency.

## Runtime smoke

1. Start the exact executable and confirm no loader error appears.
2. Confirm the ATC prompt appears normally.
3. Run `1+1`; expect `2`.
4. Run `solver(x^2+1)`; expect a valid complex root such as `1i`.
5. Run `current settings` and confirm settings can be read.
6. Make one reversible setting change, restart ATC, and confirm persistence.
7. Confirm required state files are created without loops.
8. Confirm `window.txt` is read and written normally after restart.
9. Confirm the optional integration neither invokes `wt.exe` nor produces an
   error when Windows Terminal and modern PowerShell are absent.
10. Run `exit` and confirm normal termination with exit code 0 where observable.
11. Confirm Task Manager shows no orphan `atc.exe`.
12. Restore the setting and retain logs/screenshots as new evidence.

The detailed steps above remain the reproducible checklist. Items not explicitly
listed in the result paragraph are not claimed as separately observed evidence.
