param(
    [Parameter(Mandatory = $true)]
    [string]$OutputRoot,

    [Parameter(Mandatory = $true)]
    [string]$X64Executable,

    [Parameter(Mandatory = $true)]
    [string]$X86Executable,

    [string]$PdfPath = "docs\pdf\ATC_2_1_8_Bilingual_User_Guide.pdf",
    [string]$Revision = "rev2"
)

$ErrorActionPreference = "Stop"

$repositoryRoot = [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot "..\.."))
$outputRoot = [System.IO.Path]::GetFullPath($OutputRoot)
$pdfPath = [System.IO.Path]::GetFullPath((Join-Path $repositoryRoot $PdfPath))
$expectedX64 = "0566FDD5AACE9DCF7FE7FD57CB7D15B9648CED2F4B0E08A8904B748D42CCB28A"
$expectedX86 = "2DDBF63C9AE1E5BF05FC066A8001FA0F82615DCD1DEFA275AB9FEC12B8D4CFBA"
$executableProvenance = "59903e660100ec2e46e9a6a9b7f5d8e6928075a6"
$packageContentProvenance = (& git -C $repositoryRoot rev-parse HEAD).Trim()

function Assert-FileHash([string]$Path, [string]$ExpectedHash) {
    $resolved = [System.IO.Path]::GetFullPath($Path)
    if (-not (Test-Path -LiteralPath $resolved -PathType Leaf)) {
        throw "Required file does not exist: $resolved"
    }
    $actual = (Get-FileHash -LiteralPath $resolved -Algorithm SHA256).Hash
    if ($actual -ne $ExpectedHash) {
        throw "Hash mismatch for $resolved. Expected $ExpectedHash, got $actual."
    }
    return $resolved
}

function Write-Utf8NoBom([string]$Path, [string]$Content) {
    $encoding = New-Object System.Text.UTF8Encoding($false)
    [System.IO.File]::WriteAllText($Path, $Content, $encoding)
}

function New-Package(
    [string]$PackageName,
    [string]$Executable,
    [string]$Architecture,
    [string]$Configuration,
    [string]$CompatibilityText
) {
    $stagingRoot = Join-Path $outputRoot "staging"
    $packageRoot = Join-Path $stagingRoot $PackageName
    $zipPath = Join-Path $outputRoot "$PackageName.zip"

    if ((Test-Path -LiteralPath $packageRoot) -or (Test-Path -LiteralPath $zipPath)) {
        throw "Refusing to overwrite an existing revision: $PackageName"
    }

    New-Item -ItemType Directory -Path (Join-Path $packageRoot "docs") -Force | Out-Null
    Copy-Item -LiteralPath $Executable -Destination (Join-Path $packageRoot "atc.exe")
    Copy-Item -LiteralPath $pdfPath -Destination (Join-Path $packageRoot "Advanced Trigonometry Calculator - User Guide.pdf")
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "CHANGELOG.md") -Destination $packageRoot
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "Advanced Trigonometry Calculator\License.txt") -Destination (Join-Path $packageRoot "LICENSE.txt")
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "Advanced Trigonometry Calculator\About execution of application.txt") -Destination $packageRoot
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "docs\en\User_Guide_Full.md") -Destination (Join-Path $packageRoot "docs\User_Guide_EN.md")
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "docs\pt-PT\User_Guide_Full.md") -Destination (Join-Path $packageRoot "docs\User_Guide_PT-PT.md")

    $readme = @"
Advanced Trigonometry Calculator 2.1.8 - Internal RC1 revision 2

This package contains the $Architecture executable.

Run atc.exe from this directory. The application creates its user settings
files in its normal data location or working directory as applicable.

Package selection:
- Use the x64 package on compatible x64 Windows when possible.
- Use the x86 package on Windows XP SP3 x86 or on modern x64 Windows through WOW64.

$CompatibilityText

The checksums.txt file uses SHA-256.

This is an internal release candidate. It has not been publicly released.
See docs for the English and Portuguese user guides.
"@
    Write-Utf8NoBom (Join-Path $packageRoot "README.txt") $readme

    $source = @"
Project: Advanced Trigonometry Calculator
Source repository: https://github.com/renatofreitas91/atc_code
Executable provenance HEAD: $executableProvenance
Package content provenance HEAD: $packageContentProvenance
Configuration: $Configuration
License: GNU General Public License v3.0; see LICENSE.txt.
"@
    Write-Utf8NoBom (Join-Path $packageRoot "SOURCE.txt") $source

    $version = @"
Product: Advanced Trigonometry Calculator
Version: 2.1.8
State: Internal RC1 candidate revision 2
Architecture: $Architecture
Validated compatibility: $CompatibilityText
FileVersion: 2.1.8.0
ProductVersion: 2.1.8.0
Official release date: not defined
"@
    Write-Utf8NoBom (Join-Path $packageRoot "VERSION.txt") $version

    $manifestLines = New-Object System.Collections.Generic.List[string]
    $manifestLines.Add("Algorithm: SHA-256")
    Get-ChildItem -LiteralPath $packageRoot -Recurse -File |
        Where-Object { $_.Name -ne "checksums.txt" } |
        Sort-Object { $_.FullName.Substring($packageRoot.Length + 1).Replace('\', '/') } |
        ForEach-Object {
            $relative = $_.FullName.Substring($packageRoot.Length + 1).Replace('\', '/')
            $hash = (Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256).Hash.ToLowerInvariant()
            $manifestLines.Add("$hash  $relative")
        }
    Write-Utf8NoBom (Join-Path $packageRoot "checksums.txt") (($manifestLines -join "`r`n") + "`r`n")

    Compress-Archive -Path (Join-Path $packageRoot "*") -DestinationPath $zipPath -CompressionLevel Optimal
    [pscustomobject]@{
        Package = $PackageName
        Zip = $zipPath
        Size = (Get-Item -LiteralPath $zipPath).Length
        SHA256 = (Get-FileHash -LiteralPath $zipPath -Algorithm SHA256).Hash
    }
}

$x64 = Assert-FileHash $X64Executable $expectedX64
$x86 = Assert-FileHash $X86Executable $expectedX86
if (-not (Test-Path -LiteralPath $pdfPath -PathType Leaf)) {
    throw "Release guide PDF does not exist: $pdfPath"
}

New-Item -ItemType Directory -Path $outputRoot -Force | Out-Null
$results = @(
    New-Package "ATC-2.1.8-RC1-internal-$Revision-Windows-x64" $x64 "Windows x64" "Release | x64 | v143" "Recommended for compatible x64 Windows."
    New-Package "ATC-2.1.8-RC1-internal-$Revision-Windows-XP-WOW64-x86" $x86 "Windows x86" "Release | Win32 | v141_xp" "Validated on Windows XP SP3 x86 and Windows 11 x64 through WOW64."
)

$results | Format-Table -AutoSize
