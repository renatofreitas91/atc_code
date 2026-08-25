param(
    [ValidateSet("CurrentUser", "AllUsers")]
    [string]$Scope = "CurrentUser",
    [string]$FragmentRoot = "",
    [switch]$RemoveShortcut
)

$ErrorActionPreference = "Stop"

function Test-IsAdministrator {
    $identity = [Security.Principal.WindowsIdentity]::GetCurrent()
    $principal = New-Object Security.Principal.WindowsPrincipal($identity)
    return $principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

if ($Scope -eq "AllUsers" -and -not (Test-IsAdministrator)) {
    throw "AllUsers removal requires an elevated PowerShell session."
}

if ([string]::IsNullOrWhiteSpace($FragmentRoot)) {
    $basePath = if ($Scope -eq "AllUsers") { $env:ProgramData } else { $env:LocalAppData }
    if ([string]::IsNullOrWhiteSpace($basePath)) {
        throw "The Windows known-folder environment variable for $Scope is unavailable."
    }
    $FragmentRoot = Join-Path $basePath "Microsoft\Windows Terminal\Fragments\ATC"
}
$fragmentRootPath = [System.IO.Path]::GetFullPath($FragmentRoot)

foreach ($name in @("atc.json", "atc.ico")) {
    $ownedPath = Join-Path $fragmentRootPath $name
    if (Test-Path -LiteralPath $ownedPath -PathType Leaf) {
        Remove-Item -LiteralPath $ownedPath -Force
    }
}

if ((Test-Path -LiteralPath $fragmentRootPath -PathType Container) -and
    @(Get-ChildItem -LiteralPath $fragmentRootPath -Force).Count -eq 0) {
    Remove-Item -LiteralPath $fragmentRootPath
}

if ($RemoveShortcut) {
    $programs = if ($Scope -eq "AllUsers") {
        [Environment]::GetFolderPath([Environment+SpecialFolder]::CommonPrograms)
    }
    else {
        [Environment]::GetFolderPath([Environment+SpecialFolder]::Programs)
    }
    if (-not [string]::IsNullOrWhiteSpace($programs)) {
        $shortcutPath = Join-Path $programs "Advanced Trigonometry Calculator - Windows Terminal.lnk"
        if (Test-Path -LiteralPath $shortcutPath -PathType Leaf) {
            Remove-Item -LiteralPath $shortcutPath -Force
        }
    }
}

Write-Host "ATC Windows Terminal integration removed."
Write-Host "Personal Terminal settings and the classic ATC executable were not changed."
