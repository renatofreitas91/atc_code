param([Parameter(Mandatory = $true)] [string]$PackageRoot)
$ErrorActionPreference = "Stop"
$root = [IO.Path]::GetFullPath($PackageRoot)
$failures = [Collections.Generic.List[string]]::new()
function Assert([bool]$Condition, [string]$Name) {
    if ($Condition) { Write-Host "[PASS] $Name" } else { Write-Host "[FAIL] $Name"; $script:failures.Add($Name) }
}

$required = @(
    "atc.exe", "README.txt", "SOURCE.txt", "VERSION.txt", "CHANGELOG.md",
    "LICENSE.txt", "checksums.txt", "Advanced Trigonometry Calculator - User Guide.pdf",
    "docs\User_Guide_EN.md", "docs\User_Guide_PT-PT.md",
    "Windows-Terminal-Integration\Install-ATCWindowsTerminalProfile.ps1",
    "Windows-Terminal-Integration\Uninstall-ATCWindowsTerminalProfile.ps1",
    "Windows-Terminal-Integration\README.md", "Windows-Terminal-Integration\atc.ico"
)
foreach ($item in $required) {
    Assert (Test-Path -LiteralPath (Join-Path $root $item) -PathType Leaf) "required file: $item"
}
Assert (-not (Test-Path -LiteralPath (Join-Path $root ".git"))) "no Git metadata"
$development = Get-ChildItem -LiteralPath $root -Recurse -Directory -Force |
    Where-Object { $_.Name -in @("tmp", "build", "outputs", ".git") }
Assert (-not $development) "no development directories"

$lines = @(Get-Content -LiteralPath (Join-Path $root "checksums.txt") |
    Where-Object { $_ -and $_ -notmatch '^Algorithm:' })
$files = @(Get-ChildItem -LiteralPath $root -Recurse -File |
    Where-Object Name -ne "checksums.txt")
Assert ($lines.Count -eq $files.Count) "checksum covers every packaged file"
foreach ($line in $lines) {
    if ($line -notmatch '^([0-9a-f]{64})  (.+)$') {
        $failures.Add("malformed checksum: $line")
        continue
    }
    $expected = $Matches[1]
    $relative = $Matches[2]
    $path = Join-Path $root $relative.Replace('/', '\')
    Assert ((Test-Path $path) -and ((Get-FileHash $path -Algorithm SHA256).Hash -eq $expected)) "checksum: $relative"
}

$personal = Join-Path $root "personal settings.json"
Set-Content -LiteralPath $personal -Value '{"preserve":true}' -NoNewline
$before = (Get-FileHash $personal -Algorithm SHA256).Hash
$testFragments = Join-Path ([IO.Path]::GetTempPath()) ("atc-package-fragments-" + [guid]::NewGuid().ToString("N"))
$env:ATC_TEST_WINDOWS_TERMINAL_PACKAGE_PRESENT = "1"
try {
    $install = Join-Path $root "Windows-Terminal-Integration\Install-ATCWindowsTerminalProfile.ps1"
    $uninstall = Join-Path $root "Windows-Terminal-Integration\Uninstall-ATCWindowsTerminalProfile.ps1"
    & $install -AtcExecutable (Join-Path $root "atc.exe") -FragmentRoot $testFragments
    Assert (Test-Path (Join-Path $testFragments "atc.json")) "profile installation succeeds"
    & $install -AtcExecutable (Join-Path $root "atc.exe") -FragmentRoot $testFragments
    $json = Get-Content -LiteralPath (Join-Path $testFragments "atc.json") -Raw | ConvertFrom-Json
    Assert ($json.profiles.Count -eq 1) "profile installation is idempotent"
    $expectedCommand = '"' + (Join-Path $root "atc.exe") + '"'
    Assert ($json.profiles[0].commandline -eq $expectedCommand) "profile targets extracted executable"
    Assert ((Get-FileHash $personal -Algorithm SHA256).Hash -eq $before) "personal settings remain unchanged"
    & $uninstall -FragmentRoot $testFragments
    Assert (-not (Test-Path (Join-Path $testFragments "atc.json"))) "profile removal succeeds"
} finally {
    Remove-Item Env:ATC_TEST_WINDOWS_TERMINAL_PACKAGE_PRESENT -ErrorAction SilentlyContinue
    Remove-Item -LiteralPath $personal -Force -ErrorAction SilentlyContinue
    Remove-Item -LiteralPath $testFragments -Recurse -Force -ErrorAction SilentlyContinue
}

if ($failures.Count) { Write-Host "Summary: $($failures.Count) failed"; exit 1 }
Write-Host "Summary: package validation passed"; exit 0
