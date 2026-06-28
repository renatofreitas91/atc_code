param(
    [string]$AtcExe = (Join-Path $PSScriptRoot "..\x64\Release\atc.exe"),
    [string]$AtcDataDir = (Join-Path $env:USERPROFILE "Pictures\Advanced Trigonometry Calculator"),
    [int]$ParserLatencyMs = 20,
    [int]$StartupLimitMs = 1000,
    [int]$ComplexPathLimitMs = 500,
    [double]$MemoryFactorLimit = 3.0,
    [int]$StressIterations = 500,
    [int]$TimeoutSeconds = 120,
    [switch]$SkipStress
)

$ErrorActionPreference = "Stop"

$AtcExe = [System.IO.Path]::GetFullPath($AtcExe)
$AtcDataDir = [System.IO.Path]::GetFullPath($AtcDataDir)

if (-not (Test-Path $AtcExe)) {
    throw "ATC executable not found: $AtcExe"
}

New-Item -ItemType Directory -Path $AtcDataDir -Force | Out-Null

$higherPrecisionPath = Join-Path $AtcDataDir "higherPrecision.txt"
$aboutDisabledPath = Join-Path $AtcDataDir "aboutDisabled.txt"
$predefinedTxtPath = Join-Path $AtcDataDir "predefinedTxt.txt"

function Get-OptionalFileContent([string]$Path) {
    if (Test-Path $Path) {
        return Get-Content -Raw -Path $Path
    }
    return $null
}

function Restore-OptionalFile([string]$Path, [bool]$HadFile, [string]$Content) {
    if ($HadFile) {
        Set-Content -Path $Path -Value $Content -NoNewline
    }
    else {
        Remove-Item -LiteralPath $Path -Force -ErrorAction SilentlyContinue
    }
}

$originalHigherPrecision = Get-OptionalFileContent $higherPrecisionPath
$originalAboutDisabled = Get-OptionalFileContent $aboutDisabledPath
$originalPredefinedTxt = Get-OptionalFileContent $predefinedTxtPath
$hadHigherPrecision = Test-Path $higherPrecisionPath
$hadAboutDisabled = Test-Path $aboutDisabledPath
$hadPredefinedTxt = Test-Path $predefinedTxtPath

$results = New-Object System.Collections.Generic.List[object]

function Add-Result(
    [string]$Stage,
    [string]$Name,
    [bool]$Passed,
    [string]$Details,
    [double]$ElapsedMs = 0,
    [string]$Requirement = ""
) {
    $script:results.Add([pscustomobject]@{
        Stage = $Stage
        Name = $Name
        Passed = $Passed
        Requirement = $Requirement
        ElapsedMs = [math]::Round($ElapsedMs, 2)
        Details = $Details
    })
}

function New-AtcProcess([hashtable]$Environment = @{}) {
    $processInfo = New-Object System.Diagnostics.ProcessStartInfo
    $processInfo.FileName = $AtcExe
    $processInfo.WorkingDirectory = Split-Path -Parent $AtcExe
    $processInfo.RedirectStandardOutput = $true
    $processInfo.RedirectStandardError = $true
    $processInfo.RedirectStandardInput = $true
    $processInfo.UseShellExecute = $false
    foreach ($key in $Environment.Keys) {
        $processInfo.Environment[$key] = [string]$Environment[$key]
    }
    [System.Diagnostics.Process]::Start($processInfo)
}

function Invoke-AtcSession([string[]]$Lines, [int]$Timeout = $TimeoutSeconds, [hashtable]$Environment = @{}) {
    $process = New-AtcProcess $Environment
    $stdoutTask = $process.StandardOutput.ReadToEndAsync()
    $stderrTask = $process.StandardError.ReadToEndAsync()
    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    $peakWorkingSet = 0L
    $sampleWorkingSet = 0L
    $sampleTaken = $false

    foreach ($line in $Lines) {
        $process.StandardInput.WriteLine($line)
    }
    $process.StandardInput.Close()

    while (-not $process.HasExited) {
        if ($stopwatch.Elapsed.TotalSeconds -gt $Timeout) {
            try {
                $process.Kill()
            }
            catch {
            }
            throw "Timed out after $Timeout seconds while running ATC session."
        }

        try {
            $process.Refresh()
            if (-not $sampleTaken -and $process.WorkingSet64 -gt 0) {
                $sampleWorkingSet = $process.WorkingSet64
                $sampleTaken = $true
            }
            if ($process.WorkingSet64 -gt $peakWorkingSet) {
                $peakWorkingSet = $process.WorkingSet64
            }
        }
        catch {
        }
        Start-Sleep -Milliseconds 10
    }

    $process.WaitForExit()
    $stopwatch.Stop()

    [pscustomobject]@{
        ExitCode = $process.ExitCode
        StdOut = $stdoutTask.Result
        StdErr = $stderrTask.Result
        ElapsedMs = $stopwatch.Elapsed.TotalMilliseconds
        BaselineWorkingSetBytes = $sampleWorkingSet
        PeakWorkingSetBytes = $peakWorkingSet
    }
}

function Invoke-AtcCommandArgument([string]$Expression, [string[]]$InputLines = @(), [int]$Timeout = $TimeoutSeconds, [hashtable]$Environment = @{}) {
    $processInfo = New-Object System.Diagnostics.ProcessStartInfo
    $processInfo.FileName = $AtcExe
    $processInfo.Arguments = '"' + $Expression.Replace('"', '\"') + '"'
    $processInfo.WorkingDirectory = Split-Path -Parent $AtcExe
    $processInfo.RedirectStandardOutput = $true
    $processInfo.RedirectStandardError = $true
    $processInfo.RedirectStandardInput = $true
    $processInfo.UseShellExecute = $false
    foreach ($key in $Environment.Keys) {
        $processInfo.Environment[$key] = [string]$Environment[$key]
    }

    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    $process = [System.Diagnostics.Process]::Start($processInfo)
    $stdoutTask = $process.StandardOutput.ReadToEndAsync()
    $stderrTask = $process.StandardError.ReadToEndAsync()
    $peakWorkingSet = 0L
    foreach ($line in $InputLines) {
        $process.StandardInput.WriteLine($line)
    }
    $process.StandardInput.Close()

    while (-not $process.HasExited) {
        if ($stopwatch.Elapsed.TotalSeconds -gt $Timeout) {
            try {
                $process.Kill()
            }
            catch {
            }
            throw "Timed out after $Timeout seconds: $Expression"
        }
        try {
            $process.Refresh()
            if ($process.WorkingSet64 -gt $peakWorkingSet) {
                $peakWorkingSet = $process.WorkingSet64
            }
        }
        catch {
        }
        Start-Sleep -Milliseconds 10
    }
    $process.WaitForExit()
    $stopwatch.Stop()

    [pscustomobject]@{
        ExitCode = $process.ExitCode
        StdOut = $stdoutTask.Result
        StdErr = $stderrTask.Result
        ElapsedMs = $stopwatch.Elapsed.TotalMilliseconds
        PeakWorkingSetBytes = $peakWorkingSet
    }
}

function Measure-AtcPromptReady([int]$LimitMs) {
    $process = New-AtcProcess
    $stdoutTask = $process.StandardOutput.ReadToEndAsync()
    $stderrTask = $process.StandardError.ReadToEndAsync()
    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()

    try {
        $process.StandardInput.WriteLine("exit")
        $process.StandardInput.Close()
        if (-not $process.WaitForExit($LimitMs)) {
            try {
                $process.Kill()
            }
            catch {
            }
        }
    }
    finally {
        if (-not $process.HasExited) {
            try {
                $process.Kill()
            }
            catch {
            }
        }
        $stopwatch.Stop()
    }

    $output = ($stdoutTask.Result + $stderrTask.Result) -replace "`r", ""

    [pscustomobject]@{
        Ready = ($process.HasExited -and $process.ExitCode -eq 0 -and $output -match "(?m)>")
        ElapsedMs = $stopwatch.Elapsed.TotalMilliseconds
        Output = $output
    }
}

function Test-Stage1ParserSyntaxGuard {
    $validInputs = @(
        "2pi",
        "3e",
        "2(3+4)",
        "(2+3)(4+5)",
        "2sin(pi/2)",
        "3cos(0)",
        "4tan(pi/4)",
        "2sqrt(9)",
        "3ln(e)",
        "2log(100)",
        "(2+1)(3+2)",
        "(4-1)(6-2)",
        "2(pi+1)",
        "(pi)(e)",
        "2i",
        "2pii",
        "(1+2i)(3+4i)",
        "sin(30)",
        "cos(60)",
        "tan(45)",
        "sqrt(16)+cbrt(27)",
        "abs(_5)",
        "100rest(3)",
        "100quotient(3)",
        "qfunc(0.5)",
        "gerror(0.5)",
        "sinc(0)",
        "max(1\2\3)",
        "min(1\2\3)",
        "avg(1\2\3)",
        "2asin(0.5)",
        "3acos(0.5)",
        "4atan(1)",
        "2sinh(1)",
        "2cosh(1)",
        "2tanh(1)",
        "2sec(60)",
        "2cosec(30)",
        "2cotan(45)"
    )

    $malformedInputs = @(
        "2++22",
        "((3+3)",
        "3+)",
        "sin((30)",
        "cos(30))",
        "2*/3",
        "sqrt()",
        "log()",
        "((x-1)",
        "((x-1)(x-2)",
        "(2+3",
        "(2+3))(",
        "2+*2",
        "tan()",
        "x=(",
        "matrix[",
        "sin(30))(",
        "2//2",
        "2^^2",
        "acos()",
        "ln()",
        "solver()",
        "sin(",
        "cos)",
        "2(3+)"
    )

    $totalElapsed = 0.0
    $combinedBuilder = New-Object System.Text.StringBuilder
    $crashes = 0
    $crashInputs = New-Object System.Collections.Generic.List[string]
    foreach ($input in $validInputs) {
        $extraInput = @()
        if ($input -match "^(solve equation|simplify polynomial|roots to polynomial)") {
            $extraInput = @("0")
        }
        $result = Invoke-AtcCommandArgument -Expression $input -InputLines $extraInput -Timeout 10
        $totalElapsed += $result.ElapsedMs
        if ($result.ExitCode -ne 0) {
            $crashes++
            $crashInputs.Add(("{0} => exit {1}" -f $input, $result.ExitCode))
        }
        $text = ($result.StdOut + $result.StdErr) -replace "`r", ""
        [void]$combinedBuilder.AppendLine($text)
    }
    foreach ($input in $malformedInputs) {
        $extraInput = @()
        if ($input -match "^(solve equation|simplify polynomial|roots to polynomial)") {
            $extraInput = @("0")
        }
        $result = Invoke-AtcCommandArgument -Expression $input -InputLines $extraInput -Timeout 10
        $totalElapsed += $result.ElapsedMs
        if ($result.ExitCode -ne 0) {
            $crashes++
            $crashInputs.Add(("{0} => exit {1}" -f $input, $result.ExitCode))
        }
        $text = ($result.StdOut + $result.StdErr) -replace "`r", ""
        [void]$combinedBuilder.AppendLine($text)
    }
    $combined = $combinedBuilder.ToString()
    $averageLatency = $totalElapsed / ($validInputs.Count + $malformedInputs.Count)
    $errorTokenCount = ([regex]::Matches($combined, "Error|Invalid|syntax|parenthes|consecutive|unable|required", "IgnoreCase")).Count
    $passed = ($crashes -eq 0) -and
        ($errorTokenCount -ge 20) -and
        ($combined -match "#\d+=")

    Add-Result "Stage 1" "parser and syntax guard matrix" $passed ("Inputs={0}; malformed={1}; errors={2}; avgProcess={3} ms; crashes={4}; crashInputs=[{5}]; expression latency target={6} ms" -f ($validInputs.Count + $malformedInputs.Count), $malformedInputs.Count, $errorTokenCount, [math]::Round($averageLatency, 2), $crashes, ($crashInputs -join "; "), $ParserLatencyMs) $averageLatency "FR-010, FR-060, NFR-002"
}

function Test-Stage2PersistenceStartup {
    Set-Content -Path $higherPrecisionPath -Value "0" -NoNewline
    [void](Invoke-AtcCommandArgument -Expression "higherprecision(1)" -Timeout 30)

    $startupProbe = Invoke-AtcCommandArgument -Expression "2+2" -Timeout 30
    $mpResult = Invoke-AtcCommandArgument -Expression "dp50dppi" -Timeout 30
    $combined = (($mpResult.StdOut + $mpResult.StdErr) -replace "`r", "")
    $persisted = ""
    if (Test-Path $higherPrecisionPath) {
        $persisted = (Get-Content -Raw -Path $higherPrecisionPath).Trim()
    }

    $passed = ($startupProbe.ExitCode -eq 0) -and
        ($startupProbe.ElapsedMs -lt $StartupLimitMs) -and
        (($startupProbe.StdOut + $startupProbe.StdErr) -match "#\d+=4") -and
        ($persisted -eq "1") -and
        ($mpResult.ExitCode -eq 0) -and
        ($combined -match "3\.1415926535897932384626433832795028841971693993751")

    Add-Result "Stage 2" "precision persistence and startup gate" $passed ("startupProbe={0} ms; higherPrecision={1}; mpOutput={2}" -f [math]::Round($startupProbe.ElapsedMs, 2), $persisted, (($combined -split "`n" | Select-String -Pattern "#\d+=" | Select-Object -First 1) -join "")) $startupProbe.ElapsedMs "FR-056, NFR-001, NFR-005"
}

function Test-Stage3AlgebraMemoryStress {
    if ($SkipStress) {
        Add-Result "Stage 3" "algebra memory stress" $true "Skipped by -SkipStress" 0 "FR-022, FR-024, NFR-003, NFR-004"
        return
    }

    $degree20Polynomial = "(x-1)(x-2)(x-3)(x-4)(x-5)(x-6)(x-7)(x-8)(x-9)(x-10)(x-11)(x-12)(x-13)(x-14)(x-15)(x-16)(x-17)(x-18)(x-19)(x-20)"
    $degree20Expanded = "(1+0i)x^20+(_210+0i)x^19+(20615+0i)x^18+(_1256850+0i)x^17+(53327946+0i)x^16+(_1672280820+0i)x^15+(40171771630+0i)x^14+(_756111184500+0i)x^13+(11310276995381+0i)x^12+(_135585182899530+0i)x^11+(1307535010540395+0i)x^10+(_10142299865511450+0i)x^9+(63030812099294896+0i)x^8+(_311333643161390592+0i)x^7+(1206647803780373248+0i)x^6+(_3599979517947607552+0i)x^5+(8037811822645051392+0i)x^4+(_12870931245150986240+0i)x^3+(13803759753640706048+0i)x^2+(_8752948036761601024+0i)x^1+(2432902008176640000+0i)"

    $measurements = New-Object System.Collections.Generic.List[object]
    for ($i = 1; $i -le $StressIterations; $i++) {
        $measurements.Add((Invoke-AtcCommandArgument -Expression "simplify polynomial($degree20Polynomial)" -InputLines @("0") -Timeout $TimeoutSeconds))
        $measurements.Add((Invoke-AtcCommandArgument -Expression "solve equation($degree20Expanded)" -InputLines @("0") -Timeout $TimeoutSeconds))
    }
    $operationCount = $StressIterations * 2
    $averagePathMs = (($measurements | Measure-Object ElapsedMs -Average).Average)
    $baseline = [math]::Max($measurements[0].PeakWorkingSetBytes, 1)
    $peak = [math]::Max((($measurements | Measure-Object PeakWorkingSetBytes -Maximum).Maximum), $baseline)
    $memoryFactor = $peak / $baseline
    $combined = (($measurements | ForEach-Object { $_.StdOut + $_.StdErr }) -join "`n") -replace "`r", ""
    $badExitCodes = @($measurements | Where-Object { $_.ExitCode -ne 0 })

    $passed = ($badExitCodes.Count -eq 0) -and
        ($averagePathMs -lt $ComplexPathLimitMs) -and
        ($memoryFactor -le $MemoryFactorLimit) -and
        ($combined -match "x1=") -and
        ($combined -match "x20=")

    Add-Result "Stage 3" "degree-20 polynomial and solver memory stress" $passed ("iterations={0}; operations={1}; avgPath={2} ms; baselineMB={3}; peakMB={4}; memoryFactor={5}; badExitCodes={6}" -f $StressIterations, $operationCount, [math]::Round($averagePathMs, 2), [math]::Round($baseline / 1MB, 2), [math]::Round($peak / 1MB, 2), [math]::Round($memoryFactor, 3), $badExitCodes.Count) $averagePathMs "FR-022, FR-024, NFR-003, NFR-004"
}

function Test-Stage4TxtProcessingFixtures {
    $fixtureRoot = Join-Path $PSScriptRoot "temp\srs-txt"
    $sentinelDir = Join-Path $fixtureRoot "unrelated"
    $fixturePath = Join-Path $fixtureRoot "test_commands.txt"
    $answerPath = Join-Path $fixtureRoot "test_commands_answers.txt"
    $openLogPath = Join-Path $fixtureRoot "external-open.log"
    New-Item -ItemType Directory -Path $fixtureRoot -Force | Out-Null
    New-Item -ItemType Directory -Path $sentinelDir -Force | Out-Null
    $sentinelFile = Join-Path $sentinelDir "must_not_change.txt"
    Set-Content -Path $sentinelFile -Value "keep-me" -NoNewline
    Remove-Item -LiteralPath $answerPath -Force -ErrorAction SilentlyContinue
    Remove-Item -LiteralPath $openLogPath -Force -ErrorAction SilentlyContinue

    $commands = @(
        "2+2",
        "2*3",
        "solver(x-3)",
        "solve equation((x-1)(x-2))",
        "simplify polynomial((x-1)(x-2))",
        "SOLVE_NOW"
    ) -join "`r`n"
    Set-Content -Path $fixturePath -Value $commands

    $environment = @{
        ATC_TEST_DISABLE_EXTERNAL_OPEN = "1"
        ATC_TEST_EXTERNAL_OPEN_LOG = $openLogPath
    }
    $measurement = Invoke-AtcCommandArgument -Expression "auto solve txt" -InputLines @($fixturePath) -Timeout 90 -Environment $environment

    $answerCreated = $false
    for ($i = 0; $i -lt 100; $i++) {
        if (Test-Path $answerPath) {
            $answerCreated = $true
            break
        }
        Start-Sleep -Milliseconds 50
    }

    $answer = ""
    if ($answerCreated) {
        $answer = (Get-Content -Raw -Path $answerPath) -replace "`r", ""
    }
    $sentinel = ""
    if (Test-Path $sentinelFile) {
        $sentinel = Get-Content -Raw -Path $sentinelFile
    }
    $inputAfter = ""
    if (Test-Path $fixturePath) {
        $inputAfter = (Get-Content -Raw -Path $fixturePath) -replace "`r", ""
    }
    $openLog = ""
    if (Test-Path $openLogPath) {
        $openLog = (Get-Content -Raw -Path $openLogPath) -replace "`r", ""
    }

    $passed = ($measurement.ExitCode -eq 0) -and
        $answerCreated -and
        ($answer -match "#\d+=4") -and
        ($answer -match "#\d+=6") -and
        ($answer -match "#\d+=3") -and
        ($answer -match "solve equation\(\(x-1\)\(x-2\)\)") -and
        (($measurement.StdOut + $measurement.StdErr) -match "x1=2[\s\S]*x2=1") -and
        ($inputAfter -notmatch "SOLVE_NOW") -and
        ($openLog -match "openTxt\|.*test_commands_answers\.txt") -and
        ($sentinel -eq "keep-me")

    Add-Result "Stage 4" "command bridge TXT detector fixture" $passed ("answerCreated={0}; sentinel='{1}'; openLog={2}; elapsed={3} ms" -f $answerCreated, $sentinel, ($openLog -replace "`n", " "), [math]::Round($measurement.ElapsedMs, 2)) $measurement.ElapsedMs "FR-050, NFR-014"
}

try {
    Set-Content -Path $aboutDisabledPath -Value "1" -NoNewline
    Set-Content -Path $higherPrecisionPath -Value "0" -NoNewline

    Test-Stage1ParserSyntaxGuard
    Test-Stage2PersistenceStartup
    Test-Stage3AlgebraMemoryStress
    Test-Stage4TxtProcessingFixtures
}
finally {
    Restore-OptionalFile $higherPrecisionPath $hadHigherPrecision $originalHigherPrecision
    Restore-OptionalFile $aboutDisabledPath $hadAboutDisabled $originalAboutDisabled
    Restore-OptionalFile $predefinedTxtPath $hadPredefinedTxt $originalPredefinedTxt
}

$failed = @($results | Where-Object { -not $_.Passed })
$passed = @($results | Where-Object { $_.Passed })

$results | Format-Table Stage, Name, Passed, Requirement, ElapsedMs, Details -AutoSize -Wrap
Write-Host ""
Write-Host ("Summary: {0} passed, {1} failed" -f $passed.Count, $failed.Count)

if ($failed.Count -gt 0) {
    Write-Host ""
    Write-Host "Failures:"
    $failed | Format-List Stage, Name, Requirement, ElapsedMs, Details
    exit 1
}

exit 0
