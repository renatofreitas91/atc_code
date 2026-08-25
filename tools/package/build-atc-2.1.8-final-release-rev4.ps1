param(
    [Parameter(Mandatory = $true)] [string]$OutputRoot,
    [Parameter(Mandatory = $true)] [string]$X64Executable,
    [Parameter(Mandatory = $true)] [string]$X86Executable
)

$ErrorActionPreference = "Stop"
$repositoryRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot "..\.."))
$outputRootPath = [IO.Path]::GetFullPath($OutputRoot)
$expectedX64 = "CA4E41D1F9F3ACBE76CBD5DC3F6736F43A21A0CC51052439C036DB49D15109BF"
$expectedX86 = "9FA3EAC41D9CEA7680EC66B5665E92F695C2A17E89FE9531F9608D8043F0CDAB"

function Assert-Executable([string]$Path, [string]$Hash, [long]$Size) {
    $resolved = [IO.Path]::GetFullPath($Path)
    $file = Get-Item -LiteralPath $resolved -ErrorAction Stop
    $actual = (Get-FileHash -LiteralPath $resolved -Algorithm SHA256).Hash
    if ($file.Length -ne $Size -or $actual -ne $Hash) {
        throw "Frozen executable mismatch: $resolved ($($file.Length), $actual)"
    }
    $resolved
}

function Write-Utf8([string]$Path, [string]$Text) {
    [IO.File]::WriteAllText($Path, $Text, (New-Object Text.UTF8Encoding($false)))
}

function New-Release([string]$Name, [string]$Executable, [string]$Architecture, [string]$Toolset, [string]$Compatibility) {
    $root = Join-Path (Join-Path $outputRootPath "staging") $Architecture
    $zip = Join-Path $outputRootPath ($Name + ".zip")
    if ((Test-Path -LiteralPath $root) -or (Test-Path -LiteralPath $zip)) {
        throw "Refusing to overwrite rev4 output: $Name"
    }
    New-Item -ItemType Directory -Path (Join-Path $root "docs") -Force | Out-Null
    Copy-Item -LiteralPath $Executable -Destination (Join-Path $root "atc.exe")
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "docs\pdf\ATC_2_1_8_Bilingual_User_Guide.pdf") -Destination (Join-Path $root "Advanced Trigonometry Calculator - User Guide.pdf")
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "CHANGELOG.md") -Destination $root
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "Advanced Trigonometry Calculator\License.txt") -Destination (Join-Path $root "LICENSE.txt")
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "Advanced Trigonometry Calculator\About execution of application.txt") -Destination $root
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "docs\en\User_Guide_Full.md") -Destination (Join-Path $root "docs\User_Guide_EN.md")
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "docs\pt-PT\User_Guide_Full.md") -Destination (Join-Path $root "docs\User_Guide_PT-PT.md")
    & (Join-Path $PSScriptRoot "Add-ATCWindowsTerminalIntegration.ps1") -PackageRoot $root

    $readme = @"
Advanced Trigonometry Calculator 2.1.8
Official release date: 2026-08-25

Architecture: $Architecture
Compatibility: $Compatibility

Run atc.exe directly. The classic Console Host path remains available and is
the primary path on Windows XP. Windows Terminal is optional and is never
started or installed automatically.

On a modern Windows system, optional profile scripts are in
Windows-Terminal-Integration. See its README for current-user, all-users,
portable Terminal, shortcut, and removal instructions.
"@
    Write-Utf8 (Join-Path $root "README.txt") $readme
    Write-Utf8 (Join-Path $root "SOURCE.txt") "Project: Advanced Trigonometry Calculator`r`nVersion: 2.1.8`r`nSource tag: v2.1.8`r`nSource repository: https://github.com/renatofreitas91/atc_code`r`n"
    Write-Utf8 (Join-Path $root "VERSION.txt") "Advanced Trigonometry Calculator 2.1.8`r`nRelease status: Final`r`nOfficial release date: 2026-08-25`r`nArchitecture: $Architecture`r`nToolset: $Toolset`r`nCompatibility: $Compatibility`r`nFileVersion: 2.1.8.0`r`nProductVersion: 2.1.8.0`r`nCopyright (C) 2011-2026`r`n"

    $lines = [Collections.Generic.List[string]]::new()
    $lines.Add("Algorithm: SHA-256")
    Get-ChildItem -LiteralPath $root -Recurse -File | Where-Object Name -ne "checksums.txt" | Sort-Object FullName | ForEach-Object {
        $relative = $_.FullName.Substring($root.Length + 1).Replace('\', '/')
        $hash = (Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256).Hash.ToLowerInvariant()
        $lines.Add("$hash  $relative")
    }
    Write-Utf8 (Join-Path $root "checksums.txt") (($lines -join "`r`n") + "`r`n")
    Compress-Archive -Path (Join-Path $root "*") -DestinationPath $zip -CompressionLevel Optimal
    [pscustomobject]@{ Package=$Name; Zip=$zip; Size=(Get-Item $zip).Length; SHA256=(Get-FileHash $zip -Algorithm SHA256).Hash }
}

$x64 = Assert-Executable $X64Executable $expectedX64 2422272
$x86 = Assert-Executable $X86Executable $expectedX86 2349056
New-Item -ItemType Directory -Path $outputRootPath -Force | Out-Null
@(
    New-Release "ATC-2.1.8-final-release-rev4-Windows-x64" $x64 "x64" "Release | x64 | v143" "Compatible x64 Windows; Windows Terminal integration optional."
    New-Release "ATC-2.1.8-final-release-rev4-Windows-XP-WOW64-x86" $x86 "x86" "Release | Win32 | v141_xp / MSVC 14.16" "Windows XP classic Console Host and modern Windows through WOW64."
) | Format-Table -AutoSize
