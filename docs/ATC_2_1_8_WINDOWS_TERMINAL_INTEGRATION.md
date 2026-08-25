# ATC 2.1.8 Windows Terminal integration

## Architecture

The Windows Terminal profile is an optional external integration. The ATC 2.x
executable remains a normal console application and does not require
Windows Terminal, `wt.exe`, JSON fragments, Internet access, or modern Windows
APIs to start. Windows XP and systems without Windows Terminal continue to use
the classic Console Host and the classic shortcut directly to `atc.exe`.

The integration never edits the user's Windows Terminal `settings.json`, never
sets ATC as the default profile, and never changes the default terminal
application.

Detection does not rely solely on the `wt.exe` app execution alias. The
installer first accepts an explicitly supplied executable, then checks for
`wt.exe` or `WindowsTerminal.exe`, and finally queries registered
`Microsoft.WindowsTerminal*` MSIX packages. This prevents a false negative when
Terminal is installed but its app execution alias is disabled. An optional
shortcut is created only when an executable target is resolvable.

This follows Microsoft's documented distinction between packaged, unpackaged,
and portable Windows Terminal distributions. A portable or unpackaged Terminal
kept at an arbitrary path cannot be discovered reliably when neither executable
is resolvable; pass that path with `-WindowsTerminalExecutable`. The profile
fragment itself still uses Microsoft's documented unpackaged-application
fragment directories.

## Current runtime audit

ATC discovers its data directory from its working directory and records it in
`atc_path.txt`. Its settings, history, temporary files, imported text, exported
answers, strings, user functions, and files such as `dimensions.txt` and
`window.txt` are resolved from `atcPath`. The Terminal profile therefore uses
the directory containing the installed `atc.exe` as `startingDirectory`.

The existing executable uses classic console APIs for dimensions, screen
buffers, title, and window placement. It already detects Windows Terminal at
runtime and avoids moving or maximizing the outer console window there. Console
buffer operations use guarded fallbacks. No executable change was required for
this profile integration.

The repository has no maintained installer definition. The current RC1 package
builder produces portable ZIP packages. Future package staging can use
`tools/package/Add-ATCWindowsTerminalIntegration.ps1` to copy the optional
`Windows-Terminal-Integration` directory beside `atc.exe`. The frozen rev2
builder and approved RC1 ZIP files are not modified by this work.

## Profile

- Name: `Advanced Trigonometry Calculator 2.1.8`
- Tab title: `ATC 2.1.8`
- GUID: `{13f1a9c7-83d4-5f62-9e71-1e91ca4da218}`
- Color scheme: `ATC 2.1.8`, with all 16 terminal colors
- Icon: the existing ATC `icon.ico`
- Command: the absolute path of the selected `atc.exe`
- Starting directory: the directory containing that executable

The GUID is permanent. Reinstalling replaces the same fragment and cannot add a
duplicate profile. The relative icon is progressive enhancement: Windows
Terminal 1.24 and later load media from the fragment directory; older Terminal
versions may omit the icon without preventing the profile from working.

## Current-user installation

From the portable package directory:

```powershell
powershell -ExecutionPolicy Bypass -File ".\Windows-Terminal-Integration\Install-ATCWindowsTerminalProfile.ps1" -AtcExecutable ".\atc.exe"
```

The fragment is installed at:

```text
%LocalAppData%\Microsoft\Windows Terminal\Fragments\ATC\atc.json
```

Add `-CreateShortcut` to create the optional Windows Terminal Start Menu
shortcut. The classic shortcut is unaffected.

## All-users installation

Run an elevated PowerShell session and add `-Scope AllUsers`. The fragment is
installed at:

```text
%ProgramData%\Microsoft\Windows Terminal\Fragments\ATC\atc.json
```

All-users mode is intended for a future installer. It is not required for the
portable package.

## Removal and restoration

Remove the current-user profile with:

```powershell
powershell -ExecutionPolicy Bypass -File ".\Windows-Terminal-Integration\Uninstall-ATCWindowsTerminalProfile.ps1"
```

Add `-RemoveShortcut` if the optional shortcut was installed. Removal deletes
only `atc.json`, `atc.ico`, and the explicitly named ATC shortcut. It does not
remove shared fragment directories, other profiles, personal settings, or
Windows Terminal. Run the installation command again to restore the profile.

## Compatibility and limitations

- Windows Terminal is not installed by ATC and is not available on Windows XP.
- Missing Windows Terminal is a nonfatal condition; no fragment is installed.
- The profile is discovered after Windows Terminal reloads its settings. An
  already open window may need to be closed and reopened.
- Relative fragment media requires Windows Terminal 1.24 or later. The profile
  remains functional without the icon on older versions.
- Visual verification of profile discovery, colors, resizing, selection, copy,
  and paste requires a real interactive Windows Terminal session.
- The classic Console Host path remains the compatibility baseline for XP.

Official references:

- [JSON fragment extensions](https://learn.microsoft.com/windows/terminal/json-fragment-extensions)
- [Windows Terminal command-line arguments and execution alias](https://learn.microsoft.com/windows/terminal/command-line-arguments)
- [Windows Terminal distribution types](https://learn.microsoft.com/windows/terminal/distributions)

## Validation scope

`tests/run-atc-windows-terminal-integration-tests.ps1` validates isolated
current-user-equivalent installation, JSON syntax, UTF-8 encoding, stable GUID,
paths containing spaces, complete colors, icon identity, idempotence, nonfatal
Terminal absence, and ownership-safe removal. It uses a temporary fragment root
and never changes the real user profile or `settings.json`.

## Validation results - 2026-08-25

Automated integration tests:

```text
Windows Terminal integration: 16 passed, 0 failed
```

The tests covered first installation, valid UTF-8 JSON, stable identity, paths
with spaces, all 16 scheme colors, icon identity, repeated installation,
ownership-safe removal, absent Terminal, registered Terminal with an unavailable
alias, executable discovery through `PATH`, preservation of `settings.json`, portable package staging, and the
portable default path to the adjacent `atc.exe`.

Fresh executable builds were produced from the same source state. The external
integration does not compile into either executable:

| Build | Toolset | Size | SHA-256 | Subsystem |
| --- | --- | ---: | --- | --- |
| Release x64 | v143 | 2,422,272 | `CA4E41D1F9F3ACBE76CBD5DC3F6736F43A21A0CC51052439C036DB49D15109BF` | Windows CUI 5.02 |
| Release x86 | v141_xp / MSVC 14.16 | 2,349,056 | `9FA3EAC41D9CEA7680EC66B5665E92F695C2A17E89FE9531F9608D8043F0CDAB` | Windows CUI 5.01 |

Both fresh builds passed:

```text
All: 376 passed, 0 failed
SolverComplex: 14 passed, 0 failed
Txt: 15 passed, 0 failed
Settings: 7 passed, 0 failed
Orphan ATC processes: none
```

The x86 import audit found none of `InitializeCriticalSectionEx`, `FlsAlloc`,
`FlsFree`, `FlsGetValue`, `FlsSetValue`, or `IsThreadAFiber`. No `wt.exe`
dependency or Windows Terminal import was added to either executable.

Automated integration validation passed `16/0`. The user subsequently approved
the integration on real Windows 11, confirming profile identity and icon,
interactive calculations, `calendar`, resizing, scrolling, persistence, and
respect for user-selected colors. The same user also approved the exact x86
candidate in the classic Windows XP environment. Detailed environment versions
were not recorded. No executable contains or requires this optional integration.
