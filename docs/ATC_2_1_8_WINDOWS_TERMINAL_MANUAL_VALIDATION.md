# ATC 2.1.8 Windows 11 manual validation

## Result

**APPROVED BY MANUAL USER VALIDATION**

The user confirmed on a real Windows 11 installation that the `ATC 2.1.8`
profile displayed the correct name, title, and icon; ATC started and remained
interactive; calculations and `calendar` worked; resizing and scrolling worked;
user-selected colors were respected; and persistence and general operation were
acceptable. The exact Windows build, Windows Terminal version/distribution,
alias state, timestamps, and individual command transcript were not recorded.

Automated integration evidence remains `16 passed, 0 failed`. Static checks and
automated evidence are distinct from the manual confirmation above.

## Required artefact

- Build: Release x64, v143
- Size: 2,422,272 bytes
- SHA-256: `CA4E41D1F9F3ACBE76CBD5DC3F6736F43A21A0CC51052439C036DB49D15109BF`

Stop if the independently calculated size or hash differs.

## Preserve the original state

1. Record the Windows 11 edition/build and Windows Terminal version/distribution.
2. Record whether the `wt.exe` app execution alias is enabled.
3. Back up only the ATC fragment directory if it already exists.
4. Do not edit or replace the user's `settings.json`.
5. Record the classic ATC shortcut target before testing.

## Profile installation

1. Run the current-user installer with the absolute path to the required `atc.exe`.
2. Close every Windows Terminal window and start Windows Terminal again.
3. Confirm exactly one profile named `Advanced Trigonometry Calculator 2.1.8`.
4. Confirm GUID `{13f1a9c7-83d4-5f62-9e71-1e91ca4da218}` in the fragment.
5. Confirm tab title `ATC 2.1.8` and the official ATC icon.
6. Confirm the `ATC 2.1.8` scheme contains all 16 colors and remains legible.
7. Confirm `commandline` contains the correctly escaped absolute executable path.
8. Confirm `startingDirectory` equals the directory containing `atc.exe`.

## Interactive runtime

1. Open the ATC profile and calculate `1+1`; expect `2`.
2. Create a history entry and change a reversible setting.
3. Reopen the profile; confirm history and the setting persist in the ATC directory.
4. Resize repeatedly; confirm no block or loop in `window.txt`/`dimensions.txt`.
5. Verify scroll, mouse/keyboard selection, copy, and paste.
6. Run `exit`; confirm normal process exit and expected tab closure.
7. Confirm no orphan `atc.exe` remains.

## Idempotence and removal

1. Run installation again; confirm the profile still appears exactly once.
2. Confirm the classic shortcut still launches `atc.exe` directly.
3. Run removal and restart Terminal.
4. Confirm only the ATC profile/icon disappeared and other profiles remain.
5. Confirm personal Terminal settings and the classic shortcut still work.

## Alias-disabled case

Only if it is safe to change the alias temporarily:

1. Disable the Windows Terminal app execution alias in Windows Settings.
2. Confirm `Get-Command wt.exe` no longer resolves it.
3. Run the profile installer; confirm package detection installs the profile.
4. Confirm the optional shortcut is skipped instead of receiving a broken target.
5. Re-enable the alias and restore the exact original state.

The detailed steps above remain the reproducible checklist. Items not explicitly
listed in the result paragraph are not claimed as separately observed evidence.
