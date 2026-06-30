param(
    [string]$AtcExe = (Join-Path $PSScriptRoot "..\x64\Release\atc.exe"),
    [string]$AtcDataDir = (Join-Path $env:USERPROFILE "Pictures\Advanced Trigonometry Calculator"),
    [int]$TimeoutSeconds = 30,
    [double]$MaxElapsedSeconds = 20.0,
    [double]$MaxPeakWorkingSetMB = 160.0
)

$ErrorActionPreference = "Stop"

$AtcExe = [System.IO.Path]::GetFullPath($AtcExe)
$AtcDataDir = [System.IO.Path]::GetFullPath($AtcDataDir)

if (-not (Test-Path $AtcExe)) {
    throw "ATC executable not found: $AtcExe"
}

New-Item -ItemType Directory -Path $AtcDataDir -Force | Out-Null

$variablesPath = Join-Path $AtcDataDir "variables.txt"
$renamedVarPath = Join-Path $AtcDataDir "renamedVar.txt"
$aboutDisabledPath = Join-Path $AtcDataDir "aboutDisabled.txt"
$onStartPath = Join-Path $AtcDataDir "onStart.txt"

function Get-OptionalFileContent([string]$Path) {
    if (Test-Path $Path) {
        return Get-Content -Raw -Path $Path
    }
    return $null
}

function Set-ContentWithRetry([string]$Path, [AllowNull()][string]$Value) {
    for ($attempt = 1; $attempt -le 10; $attempt++) {
        try {
            Set-Content -Path $Path -Value $Value -NoNewline
            return
        }
        catch {
            if ($attempt -eq 10) {
                throw
            }
            Start-Sleep -Milliseconds 100
        }
    }
}

function Remove-ItemWithRetry([string]$Path, [switch]$Recurse) {
    for ($attempt = 1; $attempt -le 10; $attempt++) {
        try {
            if ($Recurse) {
                Remove-Item -LiteralPath $Path -Recurse -Force
            }
            else {
                Remove-Item -LiteralPath $Path -Force
            }
            return
        }
        catch {
            if ($attempt -eq 10) {
                throw
            }
            Start-Sleep -Milliseconds 100
        }
    }
}

$originalVariables = Get-OptionalFileContent $variablesPath
$originalRenamedVar = Get-OptionalFileContent $renamedVarPath
$originalAboutDisabled = Get-OptionalFileContent $aboutDisabledPath
$originalOnStart = Get-OptionalFileContent $onStartPath
$hadVariables = Test-Path $variablesPath
$hadRenamedVar = Test-Path $renamedVarPath
$hadAboutDisabled = Test-Path $aboutDisabledPath
$hadOnStart = Test-Path $onStartPath

$scriptPath = Join-Path $PSScriptRoot "temp_multiplication_table_1_100_script.txt"
$outputPath = Join-Path $PSScriptRoot "temp_multiplication_table_1_100_output.txt"
$scriptWorkDir = Join-Path $PSScriptRoot "temp_multiplication_table_1_100_script"

try {
    Set-Content -Path $aboutDisabledPath -Value "1" -NoNewline
    Set-Content -Path $onStartPath -Value "disableatcintro" -NoNewline

    @(
        "script",
        "print(`"\n\nMultiplication Table 1-100\n`");",
        "x=0;",
        "j=0;",
        "for(x=1;x<=100;x=x+5){",
        "    for(j=1;j<=10;j=j+1){",
        "        print(`"%dx%d=%d\t%dx%d=%d\t%dx%d=%d\t%dx%d=%d\t%dx%d=%d`",x,j,x*j,x+1,j,(x+1)*j,x+2,j,(x+2)*j,x+3,j,(x+3)*j,x+4,j,(x+4)*j);",
        "    }",
        "    print(`" `");",
        "}"
    ) | Set-Content -Path $scriptPath -Encoding ASCII

    $processInfo = New-Object System.Diagnostics.ProcessStartInfo
    $processInfo.FileName = $AtcExe
    $processInfo.Arguments = '"' + $scriptPath + '"'
    $processInfo.WorkingDirectory = Split-Path -Parent $AtcExe
    $processInfo.RedirectStandardOutput = $true
    $processInfo.RedirectStandardError = $true
    $processInfo.RedirectStandardInput = $true
    $processInfo.UseShellExecute = $false

    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    $process = [System.Diagnostics.Process]::Start($processInfo)
    $stdoutTask = $process.StandardOutput.ReadToEndAsync()
    $stderrTask = $process.StandardError.ReadToEndAsync()
    $process.StandardInput.WriteLine("exit")
    $process.StandardInput.Close()

    $peakWorkingSet = 0L
    while (-not $process.HasExited -and $stopwatch.Elapsed.TotalSeconds -lt $TimeoutSeconds) {
        try {
            $process.Refresh()
            if ($process.WorkingSet64 -gt $peakWorkingSet) {
                $peakWorkingSet = $process.WorkingSet64
            }
        }
        catch {
        }
        Start-Sleep -Milliseconds 50
    }

    if (-not $process.HasExited) {
        try {
            $process.Kill()
        }
        catch {
        }
        throw "Timed out after $TimeoutSeconds seconds."
    }

    $process.WaitForExit()
    $stopwatch.Stop()

    $output = $stdoutTask.Result + $stderrTask.Result
    Set-Content -Path $outputPath -Value $output

    $elapsedSeconds = [math]::Round($stopwatch.Elapsed.TotalSeconds, 2)
    $peakWorkingSetMB = [math]::Round($peakWorkingSet / 1MB, 2)
    $normalizedOutput = $output -replace "`r", ""

    $checks = @()
    $checks += [pscustomobject]@{
        Name = "script benchmark exits successfully"
        Passed = ($process.ExitCode -eq 0)
        Detail = "ExitCode=$($process.ExitCode)"
    }
    $checks += [pscustomobject]@{
        Name = "script benchmark elapsed time"
        Passed = ($elapsedSeconds -le $MaxElapsedSeconds)
        Detail = "ElapsedSeconds=$elapsedSeconds MaxElapsedSeconds=$MaxElapsedSeconds"
    }
    $checks += [pscustomobject]@{
        Name = "script benchmark peak RAM"
        Passed = ($peakWorkingSetMB -le $MaxPeakWorkingSetMB)
        Detail = "PeakWorkingSetMB=$peakWorkingSetMB MaxPeakWorkingSetMB=$MaxPeakWorkingSetMB"
    }
    $checks += [pscustomobject]@{
        Name = "script benchmark output"
        Passed = ($normalizedOutput -match "Multiplication Table 1-100" -and $normalizedOutput -match "100x10=1000")
        Detail = "OutputChars=$($output.Length)"
    }

    foreach ($check in $checks) {
        if ($check.Passed) {
            Write-Host "[PASS] $($check.Name) - $($check.Detail)"
        }
        else {
            Write-Host "[FAIL] $($check.Name) - $($check.Detail)"
        }
    }

    $failed = @($checks | Where-Object { -not $_.Passed })
    Write-Host "Summary: $($checks.Count - $failed.Count) passed, $($failed.Count) failed"

    if ($failed.Count -gt 0) {
        exit 1
    }
}
finally {
    if ($hadVariables) {
        Set-ContentWithRetry -Path $variablesPath -Value $originalVariables
    }
    elseif (Test-Path $variablesPath) {
        Remove-ItemWithRetry -Path $variablesPath
    }

    if ($hadRenamedVar) {
        Set-ContentWithRetry -Path $renamedVarPath -Value $originalRenamedVar
    }
    elseif (Test-Path $renamedVarPath) {
        Remove-ItemWithRetry -Path $renamedVarPath
    }

    if ($hadAboutDisabled) {
        Set-ContentWithRetry -Path $aboutDisabledPath -Value $originalAboutDisabled
    }
    elseif (Test-Path $aboutDisabledPath) {
        Remove-ItemWithRetry -Path $aboutDisabledPath
    }

    if ($hadOnStart) {
        Set-ContentWithRetry -Path $onStartPath -Value $originalOnStart
    }
    elseif (Test-Path $onStartPath) {
        Remove-ItemWithRetry -Path $onStartPath
    }

    if (Test-Path $scriptPath) {
        Remove-ItemWithRetry -Path $scriptPath
    }

    if (Test-Path $outputPath) {
        Remove-ItemWithRetry -Path $outputPath
    }

    if (Test-Path $scriptWorkDir) {
        Remove-ItemWithRetry -Path $scriptWorkDir -Recurse
    }
}
