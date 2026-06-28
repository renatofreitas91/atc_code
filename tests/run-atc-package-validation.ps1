param(
    [string]$PackagePath = (Join-Path $PSScriptRoot "..\..\sourceforge_package\Advanced Trigonometry Calculator 2.1.7")
)

$ErrorActionPreference = "Stop"

$PackagePath = [System.IO.Path]::GetFullPath($PackagePath)
$results = New-Object System.Collections.Generic.List[object]

function Add-Result([string]$Name, [bool]$Passed, [string]$Evidence, [string]$Expected) {
    $script:results.Add([pscustomobject]@{
        Passed = $Passed
        Name = $Name
        Evidence = $Evidence
        Expected = $Expected
    })
}

function Test-PathExists([string]$Name, [string]$RelativePath, [string]$Type = "Any") {
    $path = Join-Path $PackagePath $RelativePath
    $exists = switch ($Type) {
        "File" { Test-Path -LiteralPath $path -PathType Leaf }
        "Directory" { Test-Path -LiteralPath $path -PathType Container }
        default { Test-Path -LiteralPath $path }
    }
    Add-Result $Name $exists $RelativePath "$Type exists"
}

function Test-PathAbsent([string]$Name, [string]$RelativePath) {
    $path = Join-Path $PackagePath $RelativePath
    Add-Result $Name (-not (Test-Path -LiteralPath $path)) $RelativePath "path absent"
}

function Test-FileContains([string]$Name, [string]$RelativePath, [string]$Pattern) {
    $path = Join-Path $PackagePath $RelativePath
    if (-not (Test-Path -LiteralPath $path -PathType Leaf)) {
        Add-Result $Name $false $RelativePath $Pattern
        return
    }
    $content = Get-Content -LiteralPath $path -Raw
    Add-Result $Name ($content -match $Pattern) $RelativePath $Pattern
}

function Test-Checksums() {
    $checksumPath = Join-Path $PackagePath "checksums.txt"
    if (-not (Test-Path -LiteralPath $checksumPath -PathType Leaf)) {
        Add-Result "checksums file exists" $false "checksums.txt" "file exists"
        return
    }

    $lines = @(Get-Content -LiteralPath $checksumPath | Where-Object { $_.Trim() })
    $allGood = $true
    $evidence = New-Object System.Collections.Generic.List[string]

    foreach ($line in $lines) {
        if ($line -notmatch '^([0-9a-fA-F]{64})\s\s(.+)$') {
            $allGood = $false
            $evidence.Add("invalid line: $line")
            continue
        }
        $expectedHash = $Matches[1].ToLowerInvariant()
        $relative = $Matches[2].Replace('/', [System.IO.Path]::DirectorySeparatorChar)
        $file = Join-Path $PackagePath $relative
        if (-not (Test-Path -LiteralPath $file -PathType Leaf)) {
            $allGood = $false
            $evidence.Add("missing file: $relative")
            continue
        }
        $actualHash = (Get-FileHash -Algorithm SHA256 -LiteralPath $file).Hash.ToLowerInvariant()
        if ($actualHash -ne $expectedHash) {
            $allGood = $false
            $evidence.Add("hash mismatch: $relative")
        }
    }

    $expectedCount = (Get-ChildItem -LiteralPath $PackagePath -Recurse -File | Where-Object { $_.Name -ne "checksums.txt" } | Measure-Object).Count
    if ($lines.Count -ne $expectedCount) {
        $allGood = $false
        $evidence.Add("checksum count $($lines.Count), file count $expectedCount")
    }

    Add-Result "checksums validate every packaged file" $allGood (($evidence -join "; ") -replace "^$", "$($lines.Count) checksums") "all hashes match"
}

Test-PathExists "package root exists" "." "Directory"

foreach ($rootFile in @("README.txt", "VERSION.txt", "SOURCE.txt", "LICENSE.txt", "CHANGELOG.md", "checksums.txt")) {
    Test-PathExists "root file: $rootFile" $rootFile "File"
}

foreach ($arch in @("x64", "x86")) {
    Test-PathExists "$arch runtime folder" $arch "Directory"
    Test-PathExists "$arch atc.exe" "$arch\atc.exe" "File"
    Test-PathExists "$arch atc_launcher.exe" "$arch\atc_launcher.exe" "File"
    Test-PathExists "$arch license copy" "$arch\License.txt" "File"
    Test-PathExists "$arch scripts examples" "$arch\Scripts examples" "Directory"
    Test-PathExists "$arch user functions" "$arch\User functions" "Directory"
    Test-PathExists "$arch strings folder" "$arch\Strings" "Directory"
    Test-PathExists "$arch to solve folder" "$arch\To solve" "Directory"
    Test-PathAbsent "$arch duplicated source folder removed" "$arch\Source code"
    Test-PathAbsent "$arch duplicated launcher source folder removed" "$arch\Source code ATC Launcher"
    Test-PathAbsent "$arch generated TXT answer removed" "$arch\To solve\example-1_answers.txt"
    Test-FileContains "$arch source notice points to GitHub" "$arch\Source code of application.txt" "github\.com/renatofreitas91/atc_code"
}

Test-PathAbsent "x86 temporary string fixture removed" "x86\Strings\Portugal.txt"

foreach ($doc in @(
    "ATC_Full_User_Guide_EN.pdf",
    "ATC_Full_User_Guide_PT-PT.pdf",
    "ATC_Cookbook_EN.pdf",
    "ATC_Cookbook_PT-PT.pdf",
    "ATC_Best_Practices_EN.pdf",
    "ATC_Best_Practices_PT-PT.pdf",
    "ATC_Release_2.1.7_EN.pdf",
    "ATC_Release_2.1.7_PT-PT.pdf"
)) {
    Test-PathExists "docs PDF: $doc" "docs\$doc" "File"
}

Test-FileContains "README explains x64 and x86 choice" "README.txt" "Use x64\\atc\.exe[\s\S]*Use x86\\atc\.exe"
Test-FileContains "SOURCE references GitHub" "SOURCE.txt" "https://github\.com/renatofreitas91/atc_code"
Test-FileContains "VERSION identifies ATC 2.1.7" "VERSION.txt" "Version: 2\.1\.7"
Test-Checksums

$failed = @($results | Where-Object { -not $_.Passed })

foreach ($result in $results) {
    $status = if ($result.Passed) { "PASS" } else { "FAIL" }
    Write-Host ("[{0}] {1}" -f $status, $result.Name)
    if (-not $result.Passed) {
        Write-Host ("       expected: {0}" -f $result.Expected)
        Write-Host ("       evidence: {0}" -f $result.Evidence)
    }
}

Write-Host ""
Write-Host ("Summary: {0} passed, {1} failed" -f ($results.Count - $failed.Count), $failed.Count)

if ($failed.Count -gt 0) {
    exit 1
}

exit 0
