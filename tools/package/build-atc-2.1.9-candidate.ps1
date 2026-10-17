param(
    [Parameter(Mandatory = $true)] [string]$OutputRoot,
    [Parameter(Mandatory = $true)] [string]$X64Executable,
    [Parameter(Mandatory = $true)] [string]$X86Executable,
    [Parameter(Mandatory = $true)] [ValidatePattern('^[0-9a-fA-F]{64}$')] [string]$X64SHA256,
    [Parameter(Mandatory = $true)] [ValidatePattern('^[0-9a-fA-F]{64}$')] [string]$X86SHA256,
    [Parameter(Mandatory = $true)] [string]$X64Toolset,
    [Parameter(Mandatory = $true)] [string]$X86Toolset,
    [string]$Revision = "candidate1"
)

$ErrorActionPreference = "Stop"
$repositoryRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot "..\.."))
$outputRootPath = [IO.Path]::GetFullPath($OutputRoot)
if ($outputRootPath.TrimEnd('\') -eq $repositoryRoot.TrimEnd('\')) {
    throw "OutputRoot must not be the repository root"
}
$expectedX64 = $X64SHA256
$expectedX86 = $X86SHA256
$head = (& git -c "safe.directory=$($repositoryRoot.Replace('\', '/'))" -C $repositoryRoot rev-parse HEAD).Trim()

function Assert-CandidateExecutable([string]$Path, [string]$Hash, [int]$Machine) {
    $resolved = [IO.Path]::GetFullPath($Path)
    $file = Get-Item -LiteralPath $resolved -ErrorAction Stop
    $actual = (Get-FileHash -LiteralPath $resolved -Algorithm SHA256).Hash
    if ($file.Length -eq 0 -or $actual -ne $Hash) {
        throw "Candidate executable mismatch: $resolved ($($file.Length), $actual)"
    }
    $info = [Diagnostics.FileVersionInfo]::GetVersionInfo($resolved)
    if ($info.FileVersion -ne "2.1.9.0" -or $info.ProductVersion -ne "2.1.9.0") {
        throw "Executable version is not 2.1.9.0: $resolved"
    }
    $stream = [IO.File]::OpenRead($resolved)
    $reader = New-Object IO.BinaryReader($stream)
    try {
        if ($reader.ReadUInt16() -ne 0x5A4D) { throw "Invalid DOS signature: $resolved" }
        $stream.Position = 0x3C
        $offset = $reader.ReadUInt32()
        $stream.Position = $offset
        if ($reader.ReadUInt32() -ne 0x4550 -or $reader.ReadUInt16() -ne $Machine) {
            throw "Executable architecture mismatch: $resolved"
        }
    }
    finally { $reader.Dispose() }
    $resolved
}

function Write-Utf8([string]$Path, [string]$Text) {
    [IO.File]::WriteAllText($Path, $Text, (New-Object Text.UTF8Encoding($false)))
}

function New-Candidate([string]$Name, [string]$Executable, [string]$Architecture, [string]$Toolset, [string]$Compatibility) {
    $root = Join-Path (Join-Path $outputRootPath "staging") $Name
    $zip = Join-Path $outputRootPath ($Name + ".zip")
    if ((Test-Path -LiteralPath $root) -or (Test-Path -LiteralPath $zip)) {
        throw "Refusing to overwrite candidate: $Name"
    }
    New-Item -ItemType Directory -Path (Join-Path $root "docs") -Force | Out-Null
    Copy-Item -LiteralPath $Executable -Destination (Join-Path $root "atc.exe")
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "docs\pdf\ATC_2_1_9_Bilingual_User_Guide.pdf") -Destination (Join-Path $root "Advanced Trigonometry Calculator - User Guide.pdf")
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "CHANGELOG.md") -Destination $root
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "Advanced Trigonometry Calculator\License.txt") -Destination (Join-Path $root "LICENSE.txt")
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "Advanced Trigonometry Calculator\About execution of application.txt") -Destination $root
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "docs\en\User_Guide_Full.md") -Destination (Join-Path $root "docs\User_Guide_EN.md")
    Copy-Item -LiteralPath (Join-Path $repositoryRoot "docs\pt-PT\User_Guide_Full.md") -Destination (Join-Path $root "docs\User_Guide_PT-PT.md")
    & (Join-Path $PSScriptRoot "Add-ATCWindowsTerminalIntegration.ps1") -PackageRoot $root
    $manifest = [ordered]@{ SourceHEAD = $head; FilesSHA256 = [ordered]@{} }
    $sourceNames = @(& git -c core.quotepath=false -C $repositoryRoot ls-files --cached --others --exclude-standard)
    if ($LASTEXITCODE -ne 0) { throw "Cannot enumerate candidate sources" }
    foreach ($name in ($sourceNames | Sort-Object -Unique)) {
        $source = [IO.Path]::GetFullPath((Join-Path $repositoryRoot $name))
        $outputPrefix = $outputRootPath.TrimEnd([IO.Path]::DirectorySeparatorChar) + [IO.Path]::DirectorySeparatorChar
        if ($source.StartsWith($outputPrefix, [StringComparison]::OrdinalIgnoreCase)) { continue }
        if (Test-Path -LiteralPath $source -PathType Leaf) {
            $manifest.FilesSHA256[$name] = (Get-FileHash -LiteralPath $source -Algorithm SHA256).Hash
        }
    }
    Write-Utf8 (Join-Path $root "SOURCE_MANIFEST.json") ($manifest | ConvertTo-Json -Depth 6)

    $readme = @"
Advanced Trigonometry Calculator 2.1.9 - validation candidate $Revision

Architecture: $Architecture
Compatibility: $Compatibility

Run atc.exe directly. The classic Console Host path remains available and is
the primary path on Windows XP. Windows Terminal is optional and is never
started or installed automatically.

On a modern Windows system, optional profile scripts are in
Windows-Terminal-Integration. Install for the current user with:
powershell -ExecutionPolicy Bypass -File ".\Windows-Terminal-Integration\Install-ATCWindowsTerminalProfile.ps1" -AtcExecutable ".\atc.exe"

Remove it with:
powershell -ExecutionPolicy Bypass -File ".\Windows-Terminal-Integration\Uninstall-ATCWindowsTerminalProfile.ps1"

The scripts also document -CreateShortcut, -RemoveShortcut, -Scope AllUsers,
and -WindowsTerminalExecutable. Do not run these optional scripts on Windows XP.
"@
    Write-Utf8 (Join-Path $root "README.txt") $readme
    Write-Utf8 (Join-Path $root "SOURCE.txt") "Project: Advanced Trigonometry Calculator`r`nVersion: 2.1.9`r`nSource repository: https://github.com/renatofreitas91/atc_code`r`nSource HEAD: $head`r`nPackage integration: local candidate; source manifest recorded separately; HEAD alone may not identify local changes`r`nNo executable was rebuilt during packaging.`r`n"
    Write-Utf8 (Join-Path $root "VERSION.txt") "Product: Advanced Trigonometry Calculator`r`nVersion: 2.1.9`r`nState: validation candidate $Revision; not publicly released`r`nArchitecture: $Architecture`r`nToolset: $Toolset`r`nCompatibility: $Compatibility`r`nFileVersion: 2.1.9.0`r`nProductVersion: 2.1.9.0`r`nOfficial release date: not defined`r`n"

    $lines = [Collections.Generic.List[string]]::new()
    $lines.Add("Algorithm: SHA-256")
    Get-ChildItem -LiteralPath $root -Recurse -File | Where-Object Name -ne "checksums.txt" |
        Sort-Object FullName | ForEach-Object {
            $relative = $_.FullName.Substring($root.Length + 1).Replace('\', '/')
            $hash = (Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256).Hash.ToLowerInvariant()
            $lines.Add("$hash  $relative")
        }
    Write-Utf8 (Join-Path $root "checksums.txt") (($lines -join "`r`n") + "`r`n")
    Compress-Archive -Path (Join-Path $root "*") -DestinationPath $zip -CompressionLevel Optimal
    [pscustomobject]@{ Package=$Name; Zip=$zip; Size=(Get-Item $zip).Length; SHA256=(Get-FileHash $zip -Algorithm SHA256).Hash }
}

$x64 = Assert-CandidateExecutable $X64Executable $expectedX64 0x8664
$x86 = Assert-CandidateExecutable $X86Executable $expectedX86 0x14c
New-Item -ItemType Directory -Path $outputRootPath -Force | Out-Null
@(
    New-Candidate "ATC-2.1.9-final-candidate-$Revision-Windows-x64" $x64 "Windows x64" $X64Toolset "Target: Windows x64; validate this candidate on the target system. Windows Terminal integration optional."
    New-Candidate "ATC-2.1.9-final-candidate-$Revision-Windows-XP-WOW64-x86" $x86 "Windows x86" $X86Toolset "Target: Windows XP x86 classic Console Host and modern Windows through WOW64; native XP validation required."
) | Format-Table -AutoSize
