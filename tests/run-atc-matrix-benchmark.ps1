param(
    [string]$AtcExe = (Join-Path $PSScriptRoot "..\x64\Release\atc.exe"),
    [string]$AtcDataDir = (Join-Path $env:USERPROFILE "Pictures\Advanced Trigonometry Calculator"),
    [int]$Iterations = 5,
    [int]$TimeoutSeconds = 30
)

$ErrorActionPreference = "Stop"

$AtcExe = [System.IO.Path]::GetFullPath($AtcExe)
$AtcDataDir = [System.IO.Path]::GetFullPath($AtcDataDir)

if (-not (Test-Path $AtcExe)) {
    throw "ATC executable not found: $AtcExe"
}

New-Item -ItemType Directory -Path $AtcDataDir -Force | Out-Null

$variablesPath = Join-Path $AtcDataDir "variables.txt"
$aboutDisabledPath = Join-Path $AtcDataDir "aboutDisabled.txt"
$onStartPath = Join-Path $AtcDataDir "onStart.txt"

function Get-OptionalFileContent([string]$Path) {
    if (Test-Path $Path) {
        return Get-Content -Raw -Path $Path
    }
    return $null
}

function Restore-OptionalFile([string]$Path, [bool]$HadFile, [AllowNull()][string]$Content) {
    if ($HadFile) {
        Set-Content -Path $Path -Value $Content -NoNewline
    }
    elseif (Test-Path $Path) {
        Remove-Item -LiteralPath $Path -Force
    }
}

function New-MatrixVariableLine([string]$Name, [int]$Rows, [int]$Columns, [string]$Cell) {
    $cells = @()
    for ($column = 0; $column -lt $Columns; $column++) {
        $cells += $Cell
    }
    $row = $cells -join ":"
    $rowValues = @()
    for ($i = 0; $i -lt $Rows; $i++) {
        $rowValues += $row
    }
    return $Name + " " + ($rowValues -join "*")
}

function Normalize-AtcOutput([string]$Text) {
    return (($Text -replace "`r", "") -replace "#\d+=", "#N=").Trim()
}

function Invoke-AtcCommand([string]$Expression, [bool]$DisableParallelism) {
    $processInfo = New-Object System.Diagnostics.ProcessStartInfo
    $processInfo.FileName = $AtcExe
    $processInfo.Arguments = '"' + $Expression.Replace('"', '\"') + '"'
    $processInfo.WorkingDirectory = Split-Path -Parent $AtcExe
    $processInfo.RedirectStandardOutput = $true
    $processInfo.RedirectStandardError = $true
    $processInfo.RedirectStandardInput = $true
    $processInfo.UseShellExecute = $false
    if ($DisableParallelism) {
        $processInfo.EnvironmentVariables["ATC_DISABLE_MATRIX_PARALLELISM"] = "1"
    }
    elseif ($processInfo.EnvironmentVariables.ContainsKey("ATC_DISABLE_MATRIX_PARALLELISM")) {
        $processInfo.EnvironmentVariables.Remove("ATC_DISABLE_MATRIX_PARALLELISM")
    }

    $process = [System.Diagnostics.Process]::Start($processInfo)
    $stdoutTask = $process.StandardOutput.ReadToEndAsync()
    $stderrTask = $process.StandardError.ReadToEndAsync()
    $process.StandardInput.Close()
    if (-not $process.WaitForExit($TimeoutSeconds * 1000)) {
        try {
            $process.Kill()
        }
        catch {
        }
        throw "Timed out after $TimeoutSeconds seconds: $Expression"
    }
    $process.WaitForExit()

    [pscustomobject]@{
        ExitCode = $process.ExitCode
        Output = ($stdoutTask.Result + $stderrTask.Result)
    }
}

function Measure-MatrixCommand([string]$Name, [string]$Expression, [string]$VariablesContent) {
    $serialOutput = $null
    $parallelOutput = $null

    $serialElapsed = [System.Diagnostics.Stopwatch]::StartNew()
    for ($i = 0; $i -lt $Iterations; $i++) {
        Set-Content -Path $variablesPath -Value $VariablesContent -NoNewline
        $serial = Invoke-AtcCommand $Expression $true
        if ($serial.ExitCode -ne 0) {
            throw "Serial command failed for $Name with exit code $($serial.ExitCode)"
        }
        $serialOutput = Normalize-AtcOutput $serial.Output
    }
    $serialElapsed.Stop()

    $parallelElapsed = [System.Diagnostics.Stopwatch]::StartNew()
    for ($i = 0; $i -lt $Iterations; $i++) {
        Set-Content -Path $variablesPath -Value $VariablesContent -NoNewline
        $parallel = Invoke-AtcCommand $Expression $false
        if ($parallel.ExitCode -ne 0) {
            throw "Parallel command failed for $Name with exit code $($parallel.ExitCode)"
        }
        $parallelOutput = Normalize-AtcOutput $parallel.Output
    }
    $parallelElapsed.Stop()

    if ($serialOutput -ne $parallelOutput) {
        throw "Serial and parallel outputs differ for $Name"
    }

    [pscustomobject]@{
        Name = $Name
        Iterations = $Iterations
        SerialMs = [math]::Round($serialElapsed.Elapsed.TotalMilliseconds, 2)
        ParallelMs = [math]::Round($parallelElapsed.Elapsed.TotalMilliseconds, 2)
        Ratio = if ($serialElapsed.Elapsed.TotalMilliseconds -gt 0) { [math]::Round($parallelElapsed.Elapsed.TotalMilliseconds / $serialElapsed.Elapsed.TotalMilliseconds, 3) } else { 0 }
    }
}

$originalVariables = Get-OptionalFileContent $variablesPath
$originalAboutDisabled = Get-OptionalFileContent $aboutDisabledPath
$originalOnStart = Get-OptionalFileContent $onStartPath
$hadVariables = Test-Path $variablesPath
$hadAboutDisabled = Test-Path $aboutDisabledPath
$hadOnStart = Test-Path $onStartPath

try {
    Set-Content -Path $aboutDisabledPath -Value "1" -NoNewline
    Set-Content -Path $onStartPath -Value "disableatcintro" -NoNewline

    $real15 = @(
        (New-MatrixVariableLine "bma" 15 15 "1 0"),
        (New-MatrixVariableLine "bmb" 15 15 "2 0")
    ) -join "`n"
    $rectangular = New-MatrixVariableLine "bmr" 15 16 "1 0"

    $benchmarks = @(
        (Measure-MatrixCommand "15x15 addition" "bma+bmb" $real15),
        (Measure-MatrixCommand "15x15 scalar multiplication" "2*bma" $real15),
        (Measure-MatrixCommand "15x16 transpose" "bmr^T" $rectangular),
        (Measure-MatrixCommand "15x15 matrix multiplication" "bma*bmb" $real15)
    )

    $benchmarks | Format-Table -AutoSize
}
finally {
    Restore-OptionalFile $variablesPath $hadVariables $originalVariables
    Restore-OptionalFile $aboutDisabledPath $hadAboutDisabled $originalAboutDisabled
    Restore-OptionalFile $onStartPath $hadOnStart $originalOnStart
}
