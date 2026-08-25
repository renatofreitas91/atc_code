param(
    [string]$IntegrationDirectory = (Join-Path $PSScriptRoot "..\tools\windows-terminal"),
    [string]$TemporaryRoot = (Join-Path $PSScriptRoot "..\tmp\windows-terminal-integration-tests")
)

$ErrorActionPreference = "Stop"
$integrationDirectory = [System.IO.Path]::GetFullPath($IntegrationDirectory)
$temporaryRoot = [System.IO.Path]::GetFullPath($TemporaryRoot)
$installScript = Join-Path $integrationDirectory "Install-ATCWindowsTerminalProfile.ps1"
$uninstallScript = Join-Path $integrationDirectory "Uninstall-ATCWindowsTerminalProfile.ps1"
$packageHelper = Join-Path $PSScriptRoot "..\tools\package\Add-ATCWindowsTerminalIntegration.ps1"
$results = New-Object System.Collections.Generic.List[object]

function Add-Result([string]$Name, [bool]$Passed, [string]$Evidence) {
    $script:results.Add([pscustomobject]@{ Name = $Name; Passed = $Passed; Evidence = $Evidence })
}

function Invoke-Script([string]$ScriptPath, [string[]]$Arguments, [string]$Name, [hashtable]$Environment = @{}) {
    $stdout = Join-Path $temporaryRoot "$Name-stdout.txt"
    $stderr = Join-Path $temporaryRoot "$Name-stderr.txt"
    $rawArguments = @("-NoProfile", "-ExecutionPolicy", "Bypass", "-File", $ScriptPath) + $Arguments
    $argumentList = ($rawArguments | ForEach-Object {
        '"' + $_.Replace('"', '\"') + '"'
    }) -join " "
    $startInfo = New-Object System.Diagnostics.ProcessStartInfo
    $startInfo.FileName = "powershell.exe"
    $startInfo.Arguments = $argumentList
    $startInfo.UseShellExecute = $false
    $startInfo.CreateNoWindow = $true
    $startInfo.RedirectStandardOutput = $true
    $startInfo.RedirectStandardError = $true
    foreach ($key in $Environment.Keys) {
        $startInfo.EnvironmentVariables[$key] = [string]$Environment[$key]
    }
    $process = New-Object System.Diagnostics.Process
    $process.StartInfo = $startInfo
    [void]$process.Start()
    if (-not $process.WaitForExit(20000)) {
        Stop-Process -Id $process.Id -Force
        throw "$Name timed out."
    }
    $process.WaitForExit()
    $stdoutText = $process.StandardOutput.ReadToEnd()
    $stderrText = $process.StandardError.ReadToEnd()
    [System.IO.File]::WriteAllText($stdout, $stdoutText)
    [System.IO.File]::WriteAllText($stderr, $stderrText)
    return [pscustomobject]@{
        ExitCode = $process.ExitCode
        Stdout = $stdoutText
        Stderr = $stderrText
    }
}

if (Test-Path -LiteralPath $temporaryRoot) {
    Remove-Item -LiteralPath $temporaryRoot -Recurse -Force
}
New-Item -ItemType Directory -Path $temporaryRoot -Force | Out-Null
$settingsPath = Join-Path $temporaryRoot "personal settings.json"
Set-Content -LiteralPath $settingsPath -Value '{"preserve":true}' -NoNewline
$settingsHash = (Get-FileHash $settingsPath -Algorithm SHA256).Hash

$packageRoot = Join-Path $temporaryRoot "ATC package with spaces"
$fragmentRoot = Join-Path $temporaryRoot "Local App Data\Microsoft\Windows Terminal\Fragments\ATC"
$atcPath = Join-Path $packageRoot "atc.exe"
$terminalPath = Join-Path $temporaryRoot "Windows Terminal\wt.exe"
New-Item -ItemType Directory -Path $packageRoot -Force | Out-Null
New-Item -ItemType Directory -Path (Split-Path -Parent $terminalPath) -Force | Out-Null
[System.IO.File]::WriteAllBytes($atcPath, [byte[]](77, 90, 0, 0))
[System.IO.File]::WriteAllBytes($terminalPath, [byte[]](77, 90, 0, 0))

$installArguments = @(
    "-AtcExecutable", $atcPath,
    "-FragmentRoot", $fragmentRoot,
    "-WindowsTerminalExecutable", $terminalPath
)
$first = Invoke-Script $installScript $installArguments "install-first"
$fragmentPath = Join-Path $fragmentRoot "atc.json"
$iconPath = Join-Path $fragmentRoot "atc.ico"

Add-Result "first install exits successfully" ($first.ExitCode -eq 0 -and [string]::IsNullOrWhiteSpace($first.Stderr)) "exit=$($first.ExitCode); stderr=$($first.Stderr)"
Add-Result "fragment and icon installed" ((Test-Path $fragmentPath -PathType Leaf) -and (Test-Path $iconPath -PathType Leaf)) $fragmentRoot

$bytes = [System.IO.File]::ReadAllBytes($fragmentPath)
$hasBom = $bytes.Length -ge 3 -and $bytes[0] -eq 0xEF -and $bytes[1] -eq 0xBB -and $bytes[2] -eq 0xBF
Add-Result "fragment is UTF-8 without BOM" (-not $hasBom) "length=$($bytes.Length)"

$json = Get-Content -LiteralPath $fragmentPath -Raw | ConvertFrom-Json
$profile = @($json.profiles)[0]
$scheme = @($json.schemes)[0]
Add-Result "stable profile identity" ($profile.guid -eq "{13f1a9c7-83d4-5f62-9e71-1e91ca4da218}" -and $profile.name -eq "Advanced Trigonometry Calculator 2.1.8" -and $profile.tabTitle -eq "ATC 2.1.8") "$($profile.guid); $($profile.name); $($profile.tabTitle)"
Add-Result "command and working directory use real paths" ($profile.commandline -eq ('"' + $atcPath + '"') -and $profile.startingDirectory -eq $packageRoot) "$($profile.commandline); $($profile.startingDirectory)"
Add-Result "profile does not claim defaults" ($profile.PSObject.Properties.Name -notcontains "defaultProfile") (($profile.PSObject.Properties.Name) -join ",")
Add-Result "complete color scheme" ((@("black","red","green","yellow","blue","purple","cyan","white","brightBlack","brightRed","brightGreen","brightYellow","brightBlue","brightPurple","brightCyan","brightWhite") | Where-Object { $scheme.PSObject.Properties.Name -notcontains $_ }).Count -eq 0) (($scheme.PSObject.Properties.Name) -join ",")
Add-Result "official icon copied unchanged" ((Get-FileHash $iconPath -Algorithm SHA256).Hash -eq (Get-FileHash (Join-Path $integrationDirectory "atc.ico") -Algorithm SHA256).Hash) $iconPath

$firstHash = (Get-FileHash $fragmentPath -Algorithm SHA256).Hash
$second = Invoke-Script $installScript $installArguments "install-second"
$secondHash = (Get-FileHash $fragmentPath -Algorithm SHA256).Hash
Add-Result "second install is idempotent" ($second.ExitCode -eq 0 -and $firstHash -eq $secondHash -and @(Get-ChildItem $fragmentRoot -Filter *.json).Count -eq 1) "first=$firstHash; second=$secondHash"

$foreignFile = Join-Path $fragmentRoot "foreign-file.txt"
Set-Content -LiteralPath $foreignFile -Value "preserve" -NoNewline
$remove = Invoke-Script $uninstallScript @("-FragmentRoot", $fragmentRoot) "uninstall"
Add-Result "removal deletes only ATC-owned files" ($remove.ExitCode -eq 0 -and -not (Test-Path $fragmentPath) -and -not (Test-Path $iconPath) -and (Test-Path $foreignFile)) $fragmentRoot

$absentRoot = Join-Path $temporaryRoot "terminal-absent"
$absent = Invoke-Script $installScript @("-AtcExecutable", $atcPath, "-FragmentRoot", $absentRoot, "-WindowsTerminalExecutable", (Join-Path $temporaryRoot "missing-wt.exe")) "terminal-absent"
Add-Result "missing Terminal is nonfatal and has no side effects" ($absent.ExitCode -eq 0 -and -not (Test-Path $absentRoot) -and $absent.Stdout -match "not found") "exit=$($absent.ExitCode); stdout=$($absent.Stdout)"

$resolvableRoot = Join-Path $temporaryRoot "resolvable fragments\ATC"
$resolvable = Invoke-Script $installScript @("-AtcExecutable", $atcPath, "-FragmentRoot", $resolvableRoot) "resolvable-alias" @{ PATH = ((Split-Path -Parent $terminalPath) + ";" + $env:PATH) }
Add-Result "Terminal executable resolves through PATH" ($resolvable.ExitCode -eq 0 -and (Test-Path (Join-Path $resolvableRoot "atc.json") -PathType Leaf) -and $resolvable.Stdout -match "resolvable executable") "exit=$($resolvable.ExitCode); stdout=$($resolvable.Stdout)"

$aliasDisabledRoot = Join-Path $temporaryRoot "alias-disabled fragments\ATC"
$aliasDisabled = Invoke-Script $installScript @("-AtcExecutable", $atcPath, "-FragmentRoot", $aliasDisabledRoot) "alias-disabled" @{ ATC_TEST_WINDOWS_TERMINAL_PACKAGE_PRESENT = "1" }
$aliasDisabledFragment = Join-Path $aliasDisabledRoot "atc.json"
Add-Result "registered Terminal works without wt.exe alias" ($aliasDisabled.ExitCode -eq 0 -and (Test-Path $aliasDisabledFragment -PathType Leaf) -and $aliasDisabled.Stdout -match "package registration") "exit=$($aliasDisabled.ExitCode); stdout=$($aliasDisabled.Stdout)"

$portableRoot = Join-Path $temporaryRoot "portable package"
New-Item -ItemType Directory -Path $portableRoot -Force | Out-Null
Copy-Item -LiteralPath $atcPath -Destination (Join-Path $portableRoot "atc.exe")
$package = Invoke-Script $packageHelper @("-PackageRoot", $portableRoot) "package-helper"
$portableIntegration = Join-Path $portableRoot "Windows-Terminal-Integration"
Add-Result "package helper adds optional integration" ($package.ExitCode -eq 0 -and (Test-Path (Join-Path $portableIntegration "Install-ATCWindowsTerminalProfile.ps1")) -and (Test-Path (Join-Path $portableIntegration "atc.ico"))) $portableIntegration

$portableFragmentRoot = Join-Path $temporaryRoot "portable fragments\ATC"
$portableInstall = Invoke-Script (Join-Path $portableIntegration "Install-ATCWindowsTerminalProfile.ps1") @("-FragmentRoot", $portableFragmentRoot, "-WindowsTerminalExecutable", $terminalPath) "portable-install"
$portableJson = Get-Content -LiteralPath (Join-Path $portableFragmentRoot "atc.json") -Raw | ConvertFrom-Json
Add-Result "portable default resolves adjacent atc.exe" ($portableInstall.ExitCode -eq 0 -and @($portableJson.profiles)[0].commandline -eq ('"' + (Join-Path $portableRoot "atc.exe") + '"')) @($portableJson.profiles)[0].commandline
Add-Result "personal settings.json remains untouched" ((Get-FileHash $settingsPath -Algorithm SHA256).Hash -eq $settingsHash) $settingsPath

$failed = @($results | Where-Object { -not $_.Passed })
foreach ($result in $results) {
    $status = if ($result.Passed) { "PASS" } else { "FAIL" }
    Write-Host "[$status] $($result.Name)"
    if (-not $result.Passed) { Write-Host "       $($result.Evidence)" }
}
Write-Host ""
Write-Host "Summary: $($results.Count - $failed.Count) passed, $($failed.Count) failed"
if ($failed.Count -gt 0) { exit 1 }
exit 0
