param(
    [Parameter(Mandatory = $true)]
    [string]$PackageRoot
)

$ErrorActionPreference = "Stop"
$repositoryRoot = [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot "..\.."))
$packageRootPath = [System.IO.Path]::GetFullPath($PackageRoot)
$source = Join-Path $repositoryRoot "tools\windows-terminal"
$destination = Join-Path $packageRootPath "Windows-Terminal-Integration"
$atcExecutable = Join-Path $packageRootPath "atc.exe"

if (-not (Test-Path -LiteralPath $packageRootPath -PathType Container)) {
    throw "Package root does not exist: $packageRootPath"
}
if (-not (Test-Path -LiteralPath $atcExecutable -PathType Leaf)) {
    throw "Package root does not contain atc.exe: $packageRootPath"
}
if (Test-Path -LiteralPath $destination) {
    throw "Refusing to overwrite existing integration: $destination"
}

Copy-Item -LiteralPath $source -Destination $destination -Recurse
Write-Host "Windows Terminal integration added: $destination"
Write-Host "Regenerate package checksums before validation."
