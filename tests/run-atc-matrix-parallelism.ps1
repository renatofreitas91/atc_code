param(
    [string]$AtcExe = (Join-Path $PSScriptRoot "..\x64\Release\atc.exe"),
    [string]$AtcDataDir = (Join-Path $env:USERPROFILE "Pictures\Advanced Trigonometry Calculator"),
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

function Invoke-AtcMatrixCommand([string]$Expression, [bool]$DisableParallelism) {
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

function Test-MatrixParallelOperation([string]$Name, [string]$Expression, [string]$ExpectedRegex, [string]$VariablesContent) {
    Set-Content -Path $variablesPath -Value $VariablesContent -NoNewline
    $serial = Invoke-AtcMatrixCommand $Expression $true
    Set-Content -Path $variablesPath -Value $VariablesContent -NoNewline
    $parallel = Invoke-AtcMatrixCommand $Expression $false

    $serialOutput = Normalize-AtcOutput $serial.Output
    $parallelOutput = Normalize-AtcOutput $parallel.Output
    $deterministic = $true
    $lastOutput = $parallelOutput

    for ($i = 0; $i -lt 2; $i++) {
        Set-Content -Path $variablesPath -Value $VariablesContent -NoNewline
        $repeat = Invoke-AtcMatrixCommand $Expression $false
        $repeatOutput = Normalize-AtcOutput $repeat.Output
        if ($repeatOutput -ne $lastOutput) {
            $deterministic = $false
        }
        $lastOutput = $repeatOutput
    }

    $passed = ($serial.ExitCode -eq 0) -and
        ($parallel.ExitCode -eq 0) -and
        ($serialOutput -eq $parallelOutput) -and
        ($parallelOutput -match $ExpectedRegex) -and
        $deterministic

    [pscustomobject]@{
        Passed = $passed
        Name = $Name
        Expression = $Expression
        Expected = $ExpectedRegex
        ExitCode = $parallel.ExitCode
        Output = if ($passed) { "serial and parallel output matched" } else { ("serial exit={0}:`n{1}`nparallel exit={2}:`n{3}" -f $serial.ExitCode, $serialOutput.Substring(0, [Math]::Min(1200, $serialOutput.Length)), $parallel.ExitCode, $parallelOutput.Substring(0, [Math]::Min(1200, $parallelOutput.Length))) }
    }
}

$originalVariables = Get-OptionalFileContent $variablesPath
$originalAboutDisabled = Get-OptionalFileContent $aboutDisabledPath
$originalOnStart = Get-OptionalFileContent $onStartPath
$hadVariables = Test-Path $variablesPath
$hadAboutDisabled = Test-Path $aboutDisabledPath
$hadOnStart = Test-Path $onStartPath

$results = New-Object System.Collections.Generic.List[object]

try {
    Set-Content -Path $aboutDisabledPath -Value "1" -NoNewline
    Set-Content -Path $onStartPath -Value "disableatcintro" -NoNewline

    $real15 = @(
        (New-MatrixVariableLine "mpa" 15 15 "1 0"),
        (New-MatrixVariableLine "mpb" 15 15 "2 0")
    ) -join "`n"

    $complex15 = @(
        (New-MatrixVariableLine "mpc" 15 15 "1 2"),
        (New-MatrixVariableLine "mpd" 15 15 "2 1")
    ) -join "`n"

    $rectangular = New-MatrixVariableLine "mpr" 15 16 "1 0"

    $results.Add((Test-MatrixParallelOperation "matrix parallel: real addition" "mpa+mpb" "3\+0i" $real15))
    $results.Add((Test-MatrixParallelOperation "matrix parallel: real subtraction" "mpb-mpa" "1\+0i" $real15))
    $results.Add((Test-MatrixParallelOperation "matrix parallel: scalar multiplication" "2*mpa" "2\+0i" $real15))
    $results.Add((Test-MatrixParallelOperation "matrix parallel: rectangular transpose" "mpr^T" "1\+0i" $rectangular))
    $results.Add((Test-MatrixParallelOperation "matrix parallel: matrix multiplication" "mpa*mpb" "30\+0i" $real15))
    $results.Add((Test-MatrixParallelOperation "matrix parallel: complex addition" "mpc+mpd" "3\+3i" $complex15))
    $results.Add((Test-MatrixParallelOperation "matrix parallel: complex subtraction" "mpc-mpd" "-1\+1i" $complex15))
}
finally {
    Restore-OptionalFile $variablesPath $hadVariables $originalVariables
    Restore-OptionalFile $aboutDisabledPath $hadAboutDisabled $originalAboutDisabled
    Restore-OptionalFile $onStartPath $hadOnStart $originalOnStart
}

$failed = @($results | Where-Object { -not $_.Passed })

foreach ($result in $results) {
    if ($result.Passed) {
        Write-Host ("[PASS] {0}" -f $result.Name)
    }
    else {
        Write-Host ("[FAIL] {0}" -f $result.Name)
        Write-Host ("       Expression: {0}" -f $result.Expression)
        Write-Host ("       Expected: {0}" -f $result.Expected)
        Write-Host ("       Output: {0}" -f $result.Output)
    }
}

Write-Host ""
Write-Host ("Summary: {0} passed, {1} failed" -f ($results.Count - $failed.Count), $failed.Count)

if ($failed.Count -gt 0) {
    exit 1
}
