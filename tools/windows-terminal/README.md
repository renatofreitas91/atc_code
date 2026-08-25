# ATC 2.1.8 Windows Terminal integration

This optional integration adds an ATC profile to Windows Terminal. It does not
modify `settings.json`, change the default terminal application, or replace the
classic ATC shortcut.

Place this directory beside `atc.exe` as `Windows-Terminal-Integration`, then run:

```powershell
powershell -ExecutionPolicy Bypass -File ".\Windows-Terminal-Integration\Install-ATCWindowsTerminalProfile.ps1" -AtcExecutable ".\atc.exe"
```

Remove the current-user integration with:

```powershell
powershell -ExecutionPolicy Bypass -File ".\Windows-Terminal-Integration\Uninstall-ATCWindowsTerminalProfile.ps1"
```

Add `-CreateShortcut` during installation and `-RemoveShortcut` during removal
to manage the optional Windows Terminal Start Menu shortcut. The classic
shortcut always continues to launch `atc.exe` directly.

`-Scope AllUsers` uses the system-wide fragments directory and requires an
elevated PowerShell session. Current-user installation is the default and does
not require administrator rights.

When Windows Terminal is unavailable, installation finishes without changing
the system. ATC remains fully usable through the classic Windows console.

The installer checks both a resolvable `wt.exe`/`WindowsTerminal.exe` and a
registered Windows Terminal MSIX package. A disabled `wt.exe` app execution
alias does not prevent profile installation. In that state the optional
shortcut is skipped because it has no reliable executable target.

For an unpackaged or portable Windows Terminal stored at an arbitrary path,
provide `-WindowsTerminalExecutable` when no Terminal executable is available
through `PATH`. This limitation follows the distribution model documented by
Microsoft and does not affect the generated profile fragment.
