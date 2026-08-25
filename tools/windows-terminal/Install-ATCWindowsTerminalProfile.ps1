param(
    [string]$AtcExecutable = (Join-Path $PSScriptRoot "..\atc.exe"),
    [ValidateSet("CurrentUser", "AllUsers")]
    [string]$Scope = "CurrentUser",
    [string]$FragmentRoot = "",
    [string]$WindowsTerminalExecutable = "",
    [switch]$CreateShortcut
)

$ErrorActionPreference = "Stop"
$profileGuid = "{13f1a9c7-83d4-5f62-9e71-1e91ca4da218}"
$profileName = "Advanced Trigonometry Calculator 2.1.8"
$fragmentFileName = "atc.json"
$iconFileName = "atc.ico"

function Write-Utf8NoBom([string]$Path, [string]$Content) {
    $encoding = New-Object System.Text.UTF8Encoding($false)
    [System.IO.File]::WriteAllText($Path, $Content, $encoding)
}

function Test-IsAdministrator {
    $identity = [Security.Principal.WindowsIdentity]::GetCurrent()
    $principal = New-Object Security.Principal.WindowsPrincipal($identity)
    return $principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

$atcPath = [System.IO.Path]::GetFullPath($AtcExecutable)
if (-not (Test-Path -LiteralPath $atcPath -PathType Leaf)) {
    throw "ATC executable not found: $atcPath"
}

$terminalPath = $null
$terminalInstalled = $false
$detectionMethod = ""
if (-not [string]::IsNullOrWhiteSpace($WindowsTerminalExecutable)) {
    $candidate = [System.IO.Path]::GetFullPath($WindowsTerminalExecutable)
    if (Test-Path -LiteralPath $candidate -PathType Leaf) {
        $terminalPath = $candidate
        $terminalInstalled = $true
        $detectionMethod = "explicit executable"
    }
}
else {
    $terminalCommand = Get-Command wt.exe, WindowsTerminal.exe -ErrorAction SilentlyContinue | Select-Object -First 1
    if ($null -ne $terminalCommand) {
        $terminalPath = $terminalCommand.Source
        $terminalInstalled = $true
        $detectionMethod = "resolvable executable"
    }
    elseif ($env:ATC_TEST_WINDOWS_TERMINAL_PACKAGE_PRESENT -eq "1") {
        $terminalInstalled = $true
        $detectionMethod = "test package registration"
    }
    else {
        try {
            $terminalPackage = Get-AppxPackage -Name "Microsoft.WindowsTerminal*" -ErrorAction Stop | Select-Object -First 1
            if ($null -ne $terminalPackage) {
                $terminalInstalled = $true
                $detectionMethod = "registered MSIX package"
            }
        }
        catch {
            # Package discovery is unavailable on older Windows and some PowerShell hosts.
        }
    }
}

if (-not $terminalInstalled) {
    Write-Host "Windows Terminal was not found. ATC remains available through its classic executable."
    exit 0
}

if ($Scope -eq "AllUsers" -and -not (Test-IsAdministrator)) {
    throw "AllUsers installation requires an elevated PowerShell session."
}

if ([string]::IsNullOrWhiteSpace($FragmentRoot)) {
    $basePath = if ($Scope -eq "AllUsers") { $env:ProgramData } else { $env:LocalAppData }
    if ([string]::IsNullOrWhiteSpace($basePath)) {
        throw "The Windows known-folder environment variable for $Scope is unavailable."
    }
    $FragmentRoot = Join-Path $basePath "Microsoft\Windows Terminal\Fragments\ATC"
}
$fragmentRootPath = [System.IO.Path]::GetFullPath($FragmentRoot)

$sourceIcon = Join-Path $PSScriptRoot $iconFileName
if (-not (Test-Path -LiteralPath $sourceIcon -PathType Leaf)) {
    throw "ATC icon not found: $sourceIcon"
}

New-Item -ItemType Directory -Path $fragmentRootPath -Force | Out-Null
Copy-Item -LiteralPath $sourceIcon -Destination (Join-Path $fragmentRootPath $iconFileName) -Force

$profile = [ordered]@{
    guid = $profileGuid
    name = $profileName
    commandline = '"' + $atcPath + '"'
    startingDirectory = [System.IO.Path]::GetDirectoryName($atcPath)
    tabTitle = "ATC 2.1.8"
    suppressApplicationTitle = $true
    colorScheme = "ATC 2.1.8"
    icon = $iconFileName
    hidden = $false
    closeOnExit = "graceful"
}

$scheme = [ordered]@{
    name = "ATC 2.1.8"
    background = "#101418"
    foreground = "#E6E9ED"
    black = "#101418"
    red = "#D65C5C"
    green = "#78B86B"
    yellow = "#D6B85C"
    blue = "#5C8FD6"
    purple = "#A879D6"
    cyan = "#62B5B5"
    white = "#D7DCE2"
    brightBlack = "#5C6570"
    brightRed = "#F07A7A"
    brightGreen = "#98D68A"
    brightYellow = "#EDD27A"
    brightBlue = "#7AABF0"
    brightPurple = "#C59AEF"
    brightCyan = "#82D2D2"
    brightWhite = "#FFFFFF"
}

$fragment = [ordered]@{
    profiles = @($profile)
    schemes = @($scheme)
}
$json = $fragment | ConvertTo-Json -Depth 8
$fragmentPath = Join-Path $fragmentRootPath $fragmentFileName
Write-Utf8NoBom $fragmentPath ($json + "`r`n")

if ($CreateShortcut) {
    if ([string]::IsNullOrWhiteSpace($terminalPath)) {
        Write-Warning "Windows Terminal is installed, but no executable or app execution alias is resolvable. The profile was installed; the optional shortcut was skipped."
    }
    else {
    $programs = if ($Scope -eq "AllUsers") {
        [Environment]::GetFolderPath([Environment+SpecialFolder]::CommonPrograms)
    }
    else {
        [Environment]::GetFolderPath([Environment+SpecialFolder]::Programs)
    }
    if ([string]::IsNullOrWhiteSpace($programs)) {
        throw "The Start Menu Programs folder is unavailable."
    }
    $shortcutPath = Join-Path $programs "Advanced Trigonometry Calculator - Windows Terminal.lnk"
    $shell = New-Object -ComObject WScript.Shell
    $shortcut = $shell.CreateShortcut($shortcutPath)
    $shortcut.TargetPath = $terminalPath
    $shortcut.Arguments = '-p "' + $profileGuid + '"'
    $shortcut.WorkingDirectory = [System.IO.Path]::GetDirectoryName($atcPath)
    $shortcut.IconLocation = "$atcPath,0"
    $shortcut.Description = $profileName
    $shortcut.Save()
    Write-Host "Windows Terminal shortcut installed: $shortcutPath"
    }
}

Write-Host "ATC Windows Terminal profile installed: $fragmentPath"
Write-Host "Windows Terminal detection: $detectionMethod"
Write-Host "The classic ATC executable and Windows terminal defaults were not changed."
