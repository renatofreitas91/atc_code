param(
    [string]$AtcExe = (Join-Path $PSScriptRoot "..\x64\Release\atc.exe"),
    [string]$AtcDataDir = (Join-Path $env:USERPROFILE "Pictures\Advanced Trigonometry Calculator"),
    [int]$TimeoutSeconds = 20,
    [ValidateSet("All", "Double", "MpFloat", "Persistence")]
    [string]$Mode = "All"
)

$ErrorActionPreference = "Stop"

$AtcExe = [System.IO.Path]::GetFullPath($AtcExe)
$AtcDataDir = [System.IO.Path]::GetFullPath($AtcDataDir)
$higherPrecisionPath = Join-Path $AtcDataDir "higherPrecision.txt"
$aboutDisabledPath = Join-Path $AtcDataDir "aboutDisabled.txt"
$variablesPath = Join-Path $AtcDataDir "variables.txt"
$modePath = Join-Path $AtcDataDir "mode.txt"
$graphPath = Join-Path $AtcDataDir "graph.txt"
$actualTimePath = Join-Path $AtcDataDir "actualTime.txt"
$predefinedTxtPath = Join-Path $AtcDataDir "predefinedTxt.txt"
$renamedVarPath = Join-Path $AtcDataDir "renamedVar.txt"
$stringVariablePath = Join-Path $AtcDataDir "stringVariable.txt"
$pathNamePath = Join-Path $AtcDataDir "pathName.txt"
$numSystemsPath = Join-Path $AtcDataDir "numSystems.txt"
$siPrefixesPath = Join-Path $AtcDataDir "siPrefixes.txt"
$verboseResolutionPath = Join-Path $AtcDataDir "verboseResolution.txt"
$colorsPath = Join-Path $AtcDataDir "colors.txt"
$dimensionsPath = Join-Path $AtcDataDir "dimensions.txt"
$windowPath = Join-Path $AtcDataDir "window.txt"
$onStartPath = Join-Path $AtcDataDir "onStart.txt"
$historyPath = Join-Path $AtcDataDir "history.txt"
$exitPath = Join-Path $AtcDataDir "exit.txt"
$disableTxtDetectorPath = Join-Path $AtcDataDir "disable_txt_detector.txt"
$scriptsExamplesDir = Join-Path $AtcDataDir "Scripts examples"
$sourceCodeDir = Join-Path $AtcDataDir "Source code"
$stringsDir = Join-Path $AtcDataDir "Strings"
$toSolveDir = Join-Path $AtcDataDir "To solve"
$userFunctionsDir = Join-Path $AtcDataDir "User functions"
$userGuidePdfPath = Join-Path $AtcDataDir "Advanced Trigonometry Calculator - User Guide.pdf"
$licensePath = Join-Path $AtcDataDir "License.txt"
$aboutExecutionPath = Join-Path $AtcDataDir "About execution of application.txt"
$scriptExamplePath = Join-Path $scriptsExamplesDir "conditions_script_example.txt"
$sourceCodeExamplePath = Join-Path $sourceCodeDir "commands.cpp"

if (-not (Test-Path $AtcExe)) {
    throw "ATC executable not found: $AtcExe"
}

New-Item -ItemType Directory -Path $AtcDataDir -Force | Out-Null

function Get-OptionalFileContent([string]$Path) {
    if (Test-Path $Path) {
        return Get-Content -Raw -Path $Path
    }
    return $null
}

$originalHigherPrecision = Get-OptionalFileContent $higherPrecisionPath
$originalAboutDisabled = Get-OptionalFileContent $aboutDisabledPath
$originalVariables = Get-OptionalFileContent $variablesPath
$originalMode = Get-OptionalFileContent $modePath
$originalGraph = Get-OptionalFileContent $graphPath
$originalActualTime = Get-OptionalFileContent $actualTimePath
$originalPredefinedTxt = Get-OptionalFileContent $predefinedTxtPath
$originalRenamedVar = Get-OptionalFileContent $renamedVarPath
$originalStringVariable = Get-OptionalFileContent $stringVariablePath
$originalPathName = Get-OptionalFileContent $pathNamePath
$originalNumSystems = Get-OptionalFileContent $numSystemsPath
$originalSiPrefixes = Get-OptionalFileContent $siPrefixesPath
$originalVerboseResolution = Get-OptionalFileContent $verboseResolutionPath
$originalColors = Get-OptionalFileContent $colorsPath
$originalDimensions = Get-OptionalFileContent $dimensionsPath
$originalWindow = Get-OptionalFileContent $windowPath
$originalOnStart = Get-OptionalFileContent $onStartPath
$originalHistory = Get-OptionalFileContent $historyPath
$originalExit = Get-OptionalFileContent $exitPath
$originalDisableTxtDetector = Get-OptionalFileContent $disableTxtDetectorPath
$hadHigherPrecision = Test-Path $higherPrecisionPath
$hadAboutDisabled = Test-Path $aboutDisabledPath
$hadVariables = Test-Path $variablesPath
$hadMode = Test-Path $modePath
$hadGraph = Test-Path $graphPath
$hadActualTime = Test-Path $actualTimePath
$hadPredefinedTxt = Test-Path $predefinedTxtPath
$hadRenamedVar = Test-Path $renamedVarPath
$hadStringVariable = Test-Path $stringVariablePath
$hadPathName = Test-Path $pathNamePath
$hadNumSystems = Test-Path $numSystemsPath
$hadSiPrefixes = Test-Path $siPrefixesPath
$hadVerboseResolution = Test-Path $verboseResolutionPath
$hadColors = Test-Path $colorsPath
$hadDimensions = Test-Path $dimensionsPath
$hadWindow = Test-Path $windowPath
$hadOnStart = Test-Path $onStartPath
$hadHistory = Test-Path $historyPath
$hadExit = Test-Path $exitPath
$hadDisableTxtDetector = Test-Path $disableTxtDetectorPath

function Set-HigherPrecision([string]$Value) {
    Set-Content -Path $higherPrecisionPath -Value $Value -NoNewline
}

function Invoke-AtcCommand([string]$Expression, [string[]]$InputLines = @()) {
    $processInfo = New-Object System.Diagnostics.ProcessStartInfo
    $processInfo.FileName = $AtcExe
    $processInfo.Arguments = '"' + $Expression.Replace('"', '\"') + '"'
    $processInfo.WorkingDirectory = Split-Path -Parent $AtcExe
    $processInfo.RedirectStandardOutput = $true
    $processInfo.RedirectStandardError = $true
    $processInfo.RedirectStandardInput = $true
    $processInfo.UseShellExecute = $false

    $process = [System.Diagnostics.Process]::Start($processInfo)
    $stdoutTask = $process.StandardOutput.ReadToEndAsync()
    $stderrTask = $process.StandardError.ReadToEndAsync()
    foreach ($line in $InputLines) {
        $process.StandardInput.WriteLine($line)
    }
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
        StdOut = $stdoutTask.Result
        StdErr = $stderrTask.Result
    }
}

function Test-AtcExpression([string]$Name, [string]$Expression, [string]$ExpectedRegex, [string[]]$InputLines = @()) {
    $result = Invoke-AtcCommand $Expression $InputLines
    $combined = (($result.StdOut + $result.StdErr) -replace "`r", "").Trim()
    $passed = ($result.ExitCode -eq 0) -and ($combined -match $ExpectedRegex)

    [pscustomobject]@{
        Passed = $passed
        Name = $Name
        Expression = $Expression
        ExitCode = $result.ExitCode
        Output = $combined
        Expected = $ExpectedRegex
    }
}

function Test-AtcExpressionWithVariables([string]$Name, [string]$Expression, [string]$ExpectedRegex, [string]$VariablesContent, [string[]]$InputLines = @()) {
    Set-Content -Path $variablesPath -Value $VariablesContent -NoNewline
    Test-AtcExpression $Name $Expression $ExpectedRegex $InputLines
}

function Test-AtcExpressionWithFixtureFile([string]$Name, [string]$Expression, [string]$ExpectedRegex, [string]$Path, [string]$Content, [string[]]$InputLines = @()) {
    Set-Content -Path $Path -Value $Content -NoNewline
    Test-AtcExpression $Name $Expression $ExpectedRegex $InputLines
}

function Test-AtcExpressionWithVariablesFile([string]$Name, [string]$Expression, [string]$ExpectedRegex, [string]$VariablesContent, [string]$ExpectedVariablesRegex, [string[]]$InputLines = @()) {
    Set-Content -Path $variablesPath -Value $VariablesContent -NoNewline
    $result = Test-AtcExpression $Name $Expression $ExpectedRegex $InputLines
    $variables = ""
    if (Test-Path $variablesPath) {
        $variables = (Get-Content -Raw -Path $variablesPath) -replace "`r", ""
    }

    if ($variables -notmatch $ExpectedVariablesRegex) {
        $result.Passed = $false
        $result.Output = ($result.Output + "`nvariables:`n" + $variables).Trim()
        $result.Expected = $result.Expected + " and variables " + $ExpectedVariablesRegex
    }

    $result
}

function Test-FileValue([string]$Name, [string]$Path, [string]$ExpectedValue) {
    $actual = ""
    if (Test-Path $Path) {
        $content = Get-Content -Raw -Path $Path
        if ($null -ne $content) {
            $actual = ($content -replace "`r", "").Trim()
        }
    }

    [pscustomobject]@{
        Passed = ($actual -eq $ExpectedValue)
        Name = $Name
        Expression = "file:$Path"
        ExitCode = 0
        Output = $actual
        Expected = [regex]::Escape($ExpectedValue)
    }
}

function Test-DirectoryExists([string]$Name, [string]$Path) {
    [pscustomobject]@{
        Passed = (Test-Path -Path $Path -PathType Container)
        Name = $Name
        Expression = "directory:$Path"
        ExitCode = 0
        Output = $Path
        Expected = "directory exists"
    }
}

function Test-FileExists([string]$Name, [string]$Path) {
    [pscustomobject]@{
        Passed = (Test-Path -Path $Path -PathType Leaf)
        Name = $Name
        Expression = "file:$Path"
        ExitCode = 0
        Output = $Path
        Expected = "file exists"
    }
}

function Test-AtcExpressionAndFileValue([string]$Name, [string]$Expression, [string]$ExpectedRegex, [string]$Path, [string]$ExpectedValue, [string[]]$InputLines = @()) {
    $result = Test-AtcExpression $Name $Expression $ExpectedRegex $InputLines
    $actual = ""
    if (Test-Path $Path) {
        $content = Get-Content -Raw -Path $Path
        if ($null -ne $content) {
            $actual = ($content -replace "`r", "").Trim()
        }
    }

    if ($actual -ne $ExpectedValue) {
        $result.Passed = $false
        $result.Output = ($result.Output + "`nfile:$Path`n" + $actual).Trim()
        $result.Expected = $result.Expected + " and file value " + [regex]::Escape($ExpectedValue)
    }

    $result
}

function Test-AtcExpressionAndFileRegex([string]$Name, [string]$Expression, [string]$ExpectedRegex, [string]$Path, [string]$ExpectedFileRegex, [string[]]$InputLines = @()) {
    $result = Test-AtcExpression $Name $Expression $ExpectedRegex $InputLines
    $actual = ""
    if (Test-Path $Path) {
        $content = Get-Content -Raw -Path $Path
        if ($null -ne $content) {
            $actual = ($content -replace "`r", "").Trim()
        }
    }

    if ($actual -notmatch $ExpectedFileRegex) {
        $result.Passed = $false
        $result.Output = ($result.Output + "`nfile:$Path`n" + $actual).Trim()
        $result.Expected = $result.Expected + " and file regex " + $ExpectedFileRegex
    }

    $result
}

function Test-AtcExpressionWithEnvironment([string]$Name, [string]$Expression, [string]$ExpectedRegex, [hashtable]$Environment, [string[]]$InputLines = @()) {
    $previousValues = @{}
    $hadValues = @{}
    foreach ($key in $Environment.Keys) {
        $previousValues[$key] = [Environment]::GetEnvironmentVariable($key, "Process")
        $hadValues[$key] = $null -ne $previousValues[$key]
        [Environment]::SetEnvironmentVariable($key, [string]$Environment[$key], "Process")
    }

    try {
        Test-AtcExpression $Name $Expression $ExpectedRegex $InputLines
    }
    finally {
        foreach ($key in $Environment.Keys) {
            if ($hadValues[$key]) {
                [Environment]::SetEnvironmentVariable($key, $previousValues[$key], "Process")
            }
            else {
                [Environment]::SetEnvironmentVariable($key, $null, "Process")
            }
        }
    }
}

function Test-MockedExternalCommand([string]$Name, [string]$Expression, [string]$ExpectedRegex, [string]$ExpectedLogRegex, [scriptblock]$BeforeRun = $null, [scriptblock]$AfterRun = $null) {
    $flowDir = Join-Path $PSScriptRoot "temp\txt-flow"
    New-Item -ItemType Directory -Path $flowDir -Force | Out-Null
    $logPath = Join-Path $flowDir ("external-" + (($Name -replace "[^A-Za-z0-9]+", "-").Trim("-")) + ".log")
    Remove-Item -Path $logPath -Force -ErrorAction SilentlyContinue
    if ($null -ne $BeforeRun) {
        & $BeforeRun
    }

    $environment = @{
        ATC_TEST_DISABLE_EXTERNAL_OPEN = "1"
        ATC_TEST_EXTERNAL_OPEN_LOG = $logPath
    }
    $result = Test-AtcExpressionWithEnvironment $Name $Expression $ExpectedRegex $environment

    $log = ""
    if (Test-Path $logPath) {
        $log = (Get-Content -Raw -Path $logPath) -replace "`r", ""
    }
    if ($log -notmatch $ExpectedLogRegex) {
        $result.Passed = $false
        $result.Output = ($result.Output + "`nexternal-open-log:`n" + $log).Trim()
        $result.Expected = $result.Expected + " and external open log " + $ExpectedLogRegex
    }
    if ($null -ne $AfterRun) {
        & $AfterRun $result
    }
    $result
}

function Test-TxtProcessingFlow {
    $flowDir = Join-Path $PSScriptRoot "temp\txt-flow"
    New-Item -ItemType Directory -Path $flowDir -Force | Out-Null
    $inputPath = Join-Path $flowDir "input.txt"
    $answerPath = Join-Path $flowDir "input_answers.txt"
    $logPath = Join-Path $flowDir "solve-txt-open.log"
    Remove-Item -Path $answerPath -Force -ErrorAction SilentlyContinue
    Remove-Item -Path $logPath -Force -ErrorAction SilentlyContinue

    $inputContent = @(
        "2+2",
        "sqrt(9)",
        "solver(x-2)",
        "solve equation((x-1)(x-2))",
        "simplify polynomial((x+1)(x-1))",
        "2++",
        "2+3"
    ) -join "`r`n"
    Set-Content -Path $inputPath -Value $inputContent

    $environment = @{
        ATC_TEST_DISABLE_EXTERNAL_OPEN = "1"
        ATC_TEST_EXTERNAL_OPEN_LOG = $logPath
    }
    $predefine = Test-AtcExpressionWithEnvironment "txt/command bridge: predefine real txt path" "predefine txt" "Drag to here the file to predefine" $environment @($inputPath)
    $solve = Test-AtcExpressionWithEnvironment "txt/command bridge: solve real txt file with mocked open" "solve txt" "Close the file with the answers to continue" $environment

    $answer = ""
    if (Test-Path $answerPath) {
        $answer = (Get-Content -Raw -Path $answerPath) -replace "`r", ""
    }
    $log = ""
    if (Test-Path $logPath) {
        $log = (Get-Content -Raw -Path $logPath) -replace "`r", ""
    }

    $expectedAnswerRegex = "#\d+=4[\s\S]*#\d+=3[\s\S]*#\d+=2[\s\S]*>solve equation\(\(x-1\)\(x-2\)\)[\s\S]*>simplify polynomial\(\(x\+1\)\(x-1\)\)[\s\S]*Error in syntax[\s\S]*#\d+=5"
    $expectedSolveOutputRegex = "x1=2[\s\S]*x2=1[\s\S]*\(1\+0i\)x\^2[\s\S]*\(_1\+0i\)"
    $passed = $predefine.Passed -and $solve.Passed -and (Test-Path $answerPath) -and ($answer -match $expectedAnswerRegex) -and ($solve.Output -match $expectedSolveOutputRegex) -and ($log -match "openTxt\|.*input_answers\.txt")

    [pscustomobject]@{
        Passed = $passed
        Name = "txt/command bridge: full solve txt flow"
        Expression = "predefine txt -> solve txt"
        ExitCode = if ($predefine.ExitCode -ne 0) { $predefine.ExitCode } else { $solve.ExitCode }
        Output = ("predefine:`n" + $predefine.Output + "`nsolve:`n" + $solve.Output + "`nanswers:`n" + $answer + "`nexternal-open-log:`n" + $log).Trim()
        Expected = "predefined txt path, answer file with expected results, invalid line error, and mocked openTxt"
    }
}

function Test-AutoSolveTxtWatcherFlow {
    $flowDir = Join-Path $PSScriptRoot "temp\txt-flow"
    New-Item -ItemType Directory -Path $flowDir -Force | Out-Null
    $inputPath = Join-Path $flowDir "auto-watch.txt"
    $answerPath = Join-Path $flowDir "auto-watch_answers.txt"
    $logPath = Join-Path $flowDir "auto-solve-txt-open.log"
    Remove-Item -Path $answerPath -Force -ErrorAction SilentlyContinue
    Remove-Item -Path $logPath -Force -ErrorAction SilentlyContinue

    $inputContent = @(
        "2+2",
        "solver(x-3)",
        "solve equation((x-1)(x-2))",
        "SOLVE_NOW"
    ) -join "`r`n"
    Set-Content -Path $inputPath -Value $inputContent

    $environment = @{
        ATC_TEST_DISABLE_EXTERNAL_OPEN = "1"
        ATC_TEST_EXTERNAL_OPEN_LOG = $logPath
    }
    $result = Test-AtcExpressionWithEnvironment "txt/command bridge: auto solve txt watcher real file" "auto solve txt" "Waiting for the flag `"SOLVE_NOW`"[\s\S]*Close the file with the answers to continue" $environment @($inputPath)

    $answer = ""
    if (Test-Path $answerPath) {
        $answer = (Get-Content -Raw -Path $answerPath) -replace "`r", ""
    }
    $inputAfter = ""
    if (Test-Path $inputPath) {
        $inputAfter = (Get-Content -Raw -Path $inputPath) -replace "`r", ""
    }
    $log = ""
    if (Test-Path $logPath) {
        $log = (Get-Content -Raw -Path $logPath) -replace "`r", ""
    }

    if (-not (Test-Path $answerPath) -or
        ($answer -notmatch "#\d+=4[\s\S]*#\d+=3[\s\S]*>solve equation\(\(x-1\)\(x-2\)\)") -or
        ($result.Output -notmatch "x1=2[\s\S]*x2=1") -or
        ($inputAfter -match "SOLVE_NOW") -or
        ($log -notmatch "openTxt\|.*auto-watch_answers\.txt")) {
        $result.Passed = $false
        $result.Output = ($result.Output + "`nanswers:`n" + $answer + "`ninput-after:`n" + $inputAfter + "`nexternal-open-log:`n" + $log).Trim()
        $result.Expected = $result.Expected + " and answer file, consumed SOLVE_NOW flag, expected results, mocked openTxt"
    }
    $result
}

function Test-EliminateStringsMock {
    $flowDir = Join-Path $PSScriptRoot "temp\txt-flow"
    $testStringsDir = Join-Path $flowDir "Strings"
    New-Item -ItemType Directory -Path $testStringsDir -Force | Out-Null
    $markerPath = Join-Path $testStringsDir "temporary-string.txt"
    Set-Content -Path $markerPath -Value "temporary" -NoNewline

    $environment = @{
        ATC_TEST_DISABLE_EXTERNAL_OPEN = "1"
        ATC_TEST_EXTERNAL_OPEN_LOG = (Join-Path $flowDir "eliminate-strings-open.log")
        ATC_TEST_STRINGS_DIR = $testStringsDir
    }
    Remove-Item -Path $environment.ATC_TEST_EXTERNAL_OPEN_LOG -Force -ErrorAction SilentlyContinue
    $result = Test-AtcExpressionWithEnvironment "txt/command bridge: eliminate strings with temporary folder" "eliminate strings" "strings were eliminated sucessfully" $environment

    $log = ""
    if (Test-Path $environment.ATC_TEST_EXTERNAL_OPEN_LOG) {
        $log = (Get-Content -Raw -Path $environment.ATC_TEST_EXTERNAL_OPEN_LOG) -replace "`r", ""
    }
    if ((Test-Path $markerPath) -or ($log -notmatch "eliminateStrings\|.*Strings")) {
        $result.Passed = $false
        $result.Output = ($result.Output + "`nexternal-open-log:`n" + $log + "`nmarker-exists:" + (Test-Path $markerPath)).Trim()
        $result.Expected = $result.Expected + " and temporary string file removed with mocked log"
    }
    $result
}

function Test-AtcExpressionAndFileValues([string]$Name, [string]$Expression, [string]$ExpectedRegex, [hashtable]$PathValues, [string[]]$InputLines = @()) {
    $result = Test-AtcExpression $Name $Expression $ExpectedRegex $InputLines
    foreach ($path in $PathValues.Keys) {
        $actual = ""
        if (Test-Path $path) {
            $content = Get-Content -Raw -Path $path
            if ($null -ne $content) {
                $actual = ($content -replace "`r", "").Trim()
            }
        }

        if ($actual -ne $PathValues[$path]) {
            $result.Passed = $false
            $result.Output = ($result.Output + "`nfile:$path`n" + $actual).Trim()
            $result.Expected = $result.Expected + " and file " + $path + " value " + [regex]::Escape($PathValues[$path])
        }
    }

    $result
}

function Test-AtcExportExpression([string]$Name, [string]$Expression, [string]$ExpectedConsoleRegex, [string]$ExpectedFileRegex) {
    $reportPath = Join-Path $PSScriptRoot ("tmp-" + (($Name -replace "[^A-Za-z0-9]+", "-").Trim("-")) + ".txt")
    Set-Content -Path $reportPath -Value "" -NoNewline

    $result = Test-AtcExpression $Name $Expression $ExpectedConsoleRegex @("1", $reportPath)
    $report = ""
    if (Test-Path $reportPath) {
        $report = (Get-Content -Raw -Path $reportPath) -replace "`r", ""
    }
    $filePassed = $report -match $ExpectedFileRegex

    Remove-Item -Path $reportPath -Force -ErrorAction SilentlyContinue

    if (-not $filePassed) {
        $result.Passed = $false
        $result.Output = ($result.Output + "`nreport:`n" + $report).Trim()
        $result.Expected = $result.Expected + " and report " + $ExpectedFileRegex
    }

    $result
}

function Test-AtcDeclineExportExpression([string]$Name, [string]$Expression, [string]$ExpectedConsoleRegex) {
    $result = Test-AtcExpression $Name $Expression ($ExpectedConsoleRegex + "[\s\S]*Export result\?") @("0")
    if ($result.Output -match "Your report was saved successfully") {
        $result.Passed = $false
        $result.Expected = $result.Expected + " and no successful export message"
    }

    $result
}

$doubleTests = @(
    @{ Name = "addition"; Expression = "1+1"; Expected = "^#\d+=2$" },
    @{ Name = "precedence"; Expression = "2+3*4"; Expected = "^#\d+=14$" },
    @{ Name = "parentheses"; Expression = "(2+3)*4"; Expected = "^#\d+=20$" },
    @{ Name = "division"; Expression = "8/4"; Expected = "^#\d+=2$" },
    @{ Name = "power"; Expression = "2^10"; Expected = "^#\d+=1024$" },
    @{ Name = "negative marker"; Expression = "_6+2"; Expected = "^#\d+=-4$" },
    @{ Name = "sqrt"; Expression = "sqrt(9)"; Expected = "^#\d+=3$" },
    @{ Name = "cbrt"; Expression = "cbrt(27)"; Expected = "^#\d+=3$" },
    @{ Name = "scientific notation positive exponent"; Expression = "1E3"; Expected = "^#\d+=1000$" },
    @{ Name = "scientific notation negative exponent"; Expression = "1E-3"; Expected = "^#\d+=0\.001$" },
    @{ Name = "pi constant"; Expression = "pi"; Expected = "^#\d+=3\.14159" },
    @{ Name = "true constant"; Expression = "true"; Expected = "^#\d+=1$" },
    @{ Name = "false constant"; Expression = "false"; Expected = "^#\d+=0$" },
    @{ Name = "true in arithmetic"; Expression = "true+1"; Expected = "^#\d+=2$" },
    @{ Name = "false in arithmetic"; Expression = "false+1"; Expected = "^#\d+=1$" },
    @{ Name = "positive infinity"; Expression = "INF"; Expected = "^#\d+=INF$" },
    @{ Name = "negative infinity"; Expression = "_INF"; Expected = "^#\d+=-INF$" },
    @{ Name = "infinity quotient"; Expression = "INF/INF"; Expected = "^#\d+=1$" },
    @{ Name = "sin identity"; Expression = "sin(pi/2)"; Expected = "^#\d+=1$" },
    @{ Name = "cos identity"; Expression = "cos(0)"; Expected = "^#\d+=1$" },
    @{ Name = "log base 10"; Expression = "log(100)"; Expected = "^#\d+=2$" },
    @{ Name = "natural log"; Expression = "ln(e)"; Expected = "^#\d+=1$" },
    @{ Name = "dp15 pi"; Expression = "dp15dppi"; Expected = "^#\d+=3\.141592653589793$" },
    @{ Name = "maxprec prefix 50dp pi"; Expression = "dp50dpmaxprecpi"; Expected = "^#\d+=3\.14159265358979323846264338327950288419716939937511$" },
    @{ Name = "maxprec prefix 50dp e"; Expression = "dp50dpmaxprece"; Expected = "^#\d+=2\.71828182845904523536028747135266249775724709369996$" }
)

$precisionModeTests = @(
    @{
        Name = "maxprec pi leaves persisted double mode"
        Expression = "dp50dpmaxprecpi"
        Expected = "^#\d+=3\.14159265358979323846264338327950288419716939937511$"
        FileExpected = "0"
    },
    @{
        Name = "double mode after maxprec remains rounded"
        Expression = "dp20dppi"
        Expected = "^#\d+=3\.14159265358979311600$"
        FileExpected = "0"
    }
)

$guideFunctionTests = @(
    @{ Name = "tan identity"; Expression = "tan(pi/4)"; Expected = "^#\d+=1$" },
    @{ Name = "sec identity"; Expression = "sec(0)"; Expected = "^#\d+=1$" },
    @{ Name = "cosec identity"; Expression = "cosec(pi/2)"; Expected = "^#\d+=1$" },
    @{ Name = "cotan identity"; Expression = "cotan(pi/4)"; Expected = "^#\d+=1$" },
    @{ Name = "asin"; Expression = "asin(1)"; Expected = "^#\d+=1\.5708$" },
    @{ Name = "acos"; Expression = "acos(1)"; Expected = "^#\d+=0$" },
    @{ Name = "atan"; Expression = "atan(1)"; Expected = "^#\d+=0\.785398$" },
    @{ Name = "sinh zero"; Expression = "sinh(0)"; Expected = "^#\d+=0$" },
    @{ Name = "cosh zero"; Expression = "cosh(0)"; Expected = "^#\d+=1$" },
    @{ Name = "tanh zero"; Expression = "tanh(0)"; Expected = "^#\d+=0$" },
    @{ Name = "sech zero"; Expression = "sech(0)"; Expected = "^#\d+=1$" },
    @{ Name = "acosh one"; Expression = "acosh(1)"; Expected = "^#\d+=0$" },
    @{ Name = "asinh zero"; Expression = "asinh(0)"; Expected = "^#\d+=0$" },
    @{ Name = "atanh zero"; Expression = "atanh(0)"; Expected = "^#\d+=0$" },
    @{ Name = "asech one"; Expression = "asech(1)"; Expected = "^#\d+=0$" },
    @{ Name = "acosech one"; Expression = "acosech(1)"; Expected = "^#\d+=0\.881374$" },
    @{ Name = "cotanh one"; Expression = "cotanh(1)"; Expected = "^#\d+=1\.31304$" },
    @{ Name = "acotanh two"; Expression = "acotanh(2)"; Expected = "^#\d+=0\.549306$" },
    @{ Name = "cosech one"; Expression = "cosech(1)"; Expected = "^#\d+=0\.850918$" },
    @{ Name = "arc cosecant one"; Expression = "acosec(1)"; Expected = "^#\d+=1\.5708$" },
    @{ Name = "arc secant one"; Expression = "asec(1)"; Expected = "^#\d+=0$" },
    @{ Name = "arc cotangent one"; Expression = "acotan(1)"; Expected = "^#\d+=0\.785398$" },
    @{ Name = "sinc zero"; Expression = "sinc(0)"; Expected = "^#\d+=1$" },
    @{ Name = "sinc normalized zero"; Expression = "sinc(1)"; Expected = "^#\d+=0$" },
    @{ Name = "factorial operator"; Expression = "5!"; Expected = "^#\d+=120$" },
    @{ Name = "inverse factorial"; Expression = "afact(120)"; Expected = "^#\d+=5$" },
    @{ Name = "absolute value"; Expression = "abs(_7)"; Expected = "^#\d+=7$" },
    @{ Name = "remainder"; Expression = "100rest(3)"; Expected = "^#\d+=1$" },
    @{ Name = "integer quotient"; Expression = "100quotient(3)"; Expected = "^#\d+=33$" },
    @{ Name = "custom root degree"; Expression = "rtD4D(16)"; Expected = "^#\d+=2$" },
    @{ Name = "custom log base"; Expression = "logb2b(8)"; Expected = "^#\d+=3$" },
    @{ Name = "list minimum"; Expression = "min(3\_1\2)"; Expected = "^#\d+=-1$" },
    @{ Name = "list maximum"; Expression = "max(3\_1\2)"; Expected = "^#\d+=3$" },
    @{ Name = "list average"; Expression = "avg(2\4\6)"; Expected = "^#\d+=4$" },
    @{ Name = "gaussian error"; Expression = "gerror(0)"; Expected = "^#\d+=0$" },
    @{ Name = "complementary gaussian error"; Expression = "gerrorc(0)"; Expected = "^#\d+=1$" },
    @{ Name = "q function"; Expression = "qfunc(0)"; Expected = "^#\d+=0\.5$" },
    @{ Name = "q function inverse"; Expression = "qfuncinv(0.5)"; Expected = "^#\d+=0$" },
    @{ Name = "gaussian error inverse"; Expression = "gerrorinv(0)"; Expected = "^#\d+=0$" },
    @{ Name = "complementary gaussian error inverse"; Expression = "gerrorcinv(1)"; Expected = "^#\d+=0$" },
    @{ Name = "fft impulse"; Expression = "fft(1\0\0\0)"; Expected = "X\[0\]=1\s+X\[1\]=1\s+X\[2\]=1\s+X\[3\]=1" },
    @{ Name = "fft odd length"; Expression = "fft(1\2\3)"; Expected = "X\[0\]=6\s+X\[1\]=-1\.500000\+0\.866025i\s+X\[2\]=-1\.500000-0\.866025i" },
    @{ Name = "ifft impulse"; Expression = "ifft(1\0\0\0)"; Expected = "x\[0\]=0\.250000\s+x\[1\]=0\.250000\s+x\[2\]=0\.250000\s+x\[3\]=0\.250000" },
    @{ Name = "ifft constant spectrum"; Expression = "ifft(1\1\1\1)"; Expected = "x\[0\]=1\s+x\[1\]=0\s+x\[2\]=0\s+x\[3\]=0" }
)

$implicitMultiplicationTests = @(
    @{ Name = "number before pi"; Expression = "2pi"; Expected = "^#\d+=6\.28319$" },
    @{ Name = "pi before number"; Expression = "pi2"; Expected = "^#\d+=6\.28319$" },
    @{ Name = "number before e"; Expression = "2e"; Expected = "^#\d+=5\.43656$" },
    @{ Name = "number before function"; Expression = "2sin(pi/2)"; Expected = "^#\d+=2$" },
    @{ Name = "function result before number"; Expression = "sin(pi/2)2"; Expected = "^#\d+=2$" },
    @{ Name = "number before parentheses"; Expression = "2(3+4)"; Expected = "^#\d+=14$" },
    @{ Name = "adjacent parentheses"; Expression = "(1+1)(2+3)"; Expected = "^#\d+=10$" },
    @{ Name = "parentheses before function"; Expression = "(1+1)sin(pi/2)"; Expected = "^#\d+=2$" },
    @{ Name = "number before imaginary unit"; Expression = "2i"; Expected = "^#\d+=2i$" },
    @{ Name = "parenthesized imaginary factor"; Expression = "3(2i)"; Expected = "^#\d+=6i$" },
    @{ Name = "number before custom root"; Expression = "2rtD4D(16)"; Expected = "^#\d+=4$" },
    @{ Name = "number before custom log base"; Expression = "2logb2b(8)"; Expected = "^#\d+=6$" }
)

$parserSyntaxGuardTests = @(
    @{ Name = "consecutive plus"; Expression = "2++22"; Expected = "consecutive arithmetic symbols[\s\S]*Error in syntax" },
    @{ Name = "missing right parenthesis"; Expression = "((3+3)"; Expected = "Error in parentheses[\s\S]*2 left parenthesis and 1 right parenthesis" },
    @{ Name = "extra right parenthesis"; Expression = "3+)"; Expected = "Error in parentheses[\s\S]*0 left parenthesis and 1 right parenthesis" },
    @{ Name = "function missing right parenthesis"; Expression = "sin((30)"; Expected = "Error in parentheses[\s\S]*2 left parenthesis and 1 right parenthesis" },
    @{ Name = "function extra right parenthesis"; Expression = "cos(30))"; Expected = "Error in parentheses[\s\S]*1 left parenthesis and 2 right parenthesis" },
    @{ Name = "multiply divide symbols"; Expression = "2*/3"; Expected = "consecutive arithmetic symbols[\s\S]*Error in syntax" },
    @{ Name = "empty sqrt"; Expression = "sqrt()"; Expected = "Error in parentheses[\s\S]*Error in syntax" },
    @{ Name = "empty log"; Expression = "log()"; Expected = "Error in parentheses[\s\S]*Error in syntax" },
    @{ Name = "unclosed arithmetic group"; Expression = "(2+3"; Expected = "Error in parentheses[\s\S]*1 left parenthesis and 0 right parenthesis" },
    @{ Name = "plus multiply symbols"; Expression = "2+*2"; Expected = "consecutive arithmetic symbols[\s\S]*Error in syntax" },
    @{ Name = "empty tan"; Expression = "tan()"; Expected = "Error in parentheses[\s\S]*Error in syntax" },
    @{ Name = "unfinished function"; Expression = "sin("; Expected = "Error in parentheses[\s\S]*1 left parenthesis and 0 right parenthesis" },
    @{ Name = "function missing left parenthesis"; Expression = "cos)"; Expected = "Error in parentheses[\s\S]*0 left parenthesis and 1 right parenthesis" },
    @{ Name = "operator before close parenthesis"; Expression = "2(3+)"; Expected = "arithmetic symbol previous to `"\)`"[\s\S]*Error in syntax" }
)

$matrixVariableContent = "foo 1 0:2 0*3 0:4 0`n"
$matrixVariableTests = @(
    @{ Name = "matrix variable minimum"; Expression = "min(foo)"; Expected = "^#\d+=1$" },
    @{ Name = "matrix variable maximum"; Expression = "max(foo)"; Expected = "^#\d+=4$" },
    @{ Name = "matrix variable average"; Expression = "avg(foo)"; Expected = "^#\d+=2\.5$" }
)

$matrixGuideFunctionContent = "foo 1 0:2 0:3 0*4 0:5 0:6 0`nbar 1 0:2 0*3 0:4 0*5 0:6 0`n"
$matrixGuideFunctionTests = @(
    @{ Name = "matrix rows count 2x3"; Expression = "linsnum(foo)"; Expected = "^#\d+=2$" },
    @{ Name = "matrix columns count 2x3"; Expression = "colsnum(foo)"; Expected = "^#\d+=3$" },
    @{ Name = "matrix rows count 3x2"; Expression = "linsnum(bar)"; Expected = "^#\d+=3$" },
    @{ Name = "matrix columns count 3x2"; Expression = "colsnum(bar)"; Expected = "^#\d+=2$" },
    @{ Name = "matrix get rows"; Expression = "getlins(foo)"; Expected = "#\d+=\s+1\+0i\s+2\+0i\s+3\+0i\s+4\+0i\s+5\+0i\s+6\+0i" },
    @{ Name = "matrix get columns"; Expression = "getcols(bar)"; Expected = "#\d+=\s+1\+0i\s+2\+0i\s+3\+0i\s+4\+0i\s+5\+0i\s+6\+0i" },
    @{ Name = "matrix get first row range"; Expression = "getlins(foo\0\0)"; Expected = "#\d+=\s+1\+0i\s+2\+0i\s+3\+0i" },
    @{ Name = "matrix get second and third columns range"; Expression = "getcols(foo\1\2)"; Expected = "#\d+=\s+2\+0i\s+3\+0i\s+5\+0i\s+6\+0i" },
    @{ Name = "non-square matrix minimum"; Expression = "min(bar)"; Expected = "^#\d+=1$" },
    @{ Name = "non-square matrix maximum"; Expression = "max(bar)"; Expected = "^#\d+=6$" },
    @{ Name = "non-square matrix average"; Expression = "avg(bar)"; Expected = "^#\d+=3\.5$" }
)

$matrixArithmeticContent = "foo 3 0:4 0:5 0*8 0:7 0:6 0*9 0:7 0:5 0`n"
$matrixArithmeticTests = @(
    @{ Name = "matrix addition with same variable"; Expression = "foo+foo"; Expected = "#\d+=\s+6\+0i\s+8\+0i\s+10\+0i\s+16\+0i\s+14\+0i\s+12\+0i\s+18\+0i\s+14\+0i\s+10\+0i" },
    @{ Name = "matrix subtraction with same variable"; Expression = "foo-foo"; Expected = "#\d+=\s+0\+0i\s+0\+0i\s+0\+0i\s+0\+0i\s+0\+0i\s+0\+0i\s+0\+0i\s+0\+0i\s+0\+0i" },
    @{ Name = "matrix multiplication with same variable"; Expression = "foo*foo"; Expected = "#\d+=\s+86\+0i\s+75\+0i\s+64\+0i\s+134\+0i\s+123\+0i\s+112\+0i\s+128\+0i\s+120\+0i\s+112\+0i" },
    @{ Name = "matrix power"; Expression = "foo^2"; Expected = "#\d+=\s+86\+0i\s+75\+0i\s+64\+0i\s+134\+0i\s+123\+0i\s+112\+0i\s+128\+0i\s+120\+0i\s+112\+0i" },
    @{ Name = "matrix transpose shortcut"; Expression = "foo^T"; Expected = "#\d+=\s+3\+0i\s+8\+0i\s+9\+0i\s+4\+0i\s+7\+0i\s+7\+0i\s+5\+0i\s+6\+0i\s+5\+0i" },
    @{ Name = "matrix rank shortcut"; Expression = "foo^R"; Expected = "^#\d+=3$" }
)

$matrixPairContent = "foo 1 0:2 0:3 0*4 0:5 0:6 0`nbar 6 0:5 0:4 0*3 0:2 0:1 0`n"
$matrixPairTests = @(
    @{ Name = "matrix addition with another variable"; Expression = "foo+bar"; Expected = "#\d+=\s+7\+0i\s+7\+0i\s+7\+0i\s+7\+0i\s+7\+0i\s+7\+0i" },
    @{ Name = "matrix subtraction with another variable"; Expression = "foo-bar"; Expected = "#\d+=\s+-5\+0i\s+-3\+0i\s+-1\+0i\s+1\+0i\s+3\+0i\s+5\+0i" }
)

$rectangularMatrixContent = "bar 1 0:2 0:3 0*4 0:5 0:6 0`n"
$rectangularMatrixTests = @(
    @{ Name = "rectangular matrix transpose"; Expression = "bar^T"; Expected = "#\d+=\s+1\+0i\s+4\+0i\s+2\+0i\s+5\+0i\s+3\+0i\s+6\+0i" }
)

$matrixScalarContent = "foo 2 0:4 0*6 0:8 0`nsmall 2 0:4 0*6 0:8 0`n"
$matrixScalarTests = @(
    @{ Name = "scalar before matrix multiplication"; Expression = "2*foo"; Expected = "#\d+=\s+4\+0i\s+8\+0i\s+12\+0i\s+16\+0i" },
    @{ Name = "matrix divided by scalar"; Expression = "foo/2"; Expected = "#\d+=\s+1\+0i\s+2\+0i\s+3\+0i\s+4\+0i" },
    @{ Name = "reserved-prefix matrix variable"; Expression = "small"; Expected = "#\d+=\s+2\+0i\s+4\+0i\s+6\+0i\s+8\+0i" },
    @{ Name = "scalar before reserved-prefix matrix"; Expression = "2*small"; Expected = "#\d+=\s+4\+0i\s+8\+0i\s+12\+0i\s+16\+0i" },
    @{ Name = "reserved-prefix matrix divided by scalar"; Expression = "small/2"; Expected = "#\d+=\s+1\+0i\s+2\+0i\s+3\+0i\s+4\+0i" }
)

$complexMatrixContent = "cmat 1 2:3 0*_4 0:5 0`ncmatb 2 1:1 1*4 0:1 2`n"
$complexMatrixTests = @(
    @{ Name = "complex matrix average"; Expression = "avg(cmat)"; Expected = "^#\d+=2\.25\+0\.5i$" },
    @{ Name = "complex matrix addition"; Expression = "cmat+cmatb"; Expected = "#\d+=\s+3\+3i\s+4\+1i\s+4\+0i\s+6\+2i" },
    @{ Name = "complex matrix subtraction"; Expression = "cmat-cmatb"; Expected = "#\d+=\s+-1\+1i\s+2\+-1i\s+-4\+0i\s+4\+-2i" }
)

$matrixIndexSessionContent = "foo 1 0:2 0:3 0*4 0:5 0:6 0`n"
$matrixIndexSessionTests = @(
    @{
        Name = "matrix index read and persisted cell update"
        Expression = "atc over cmd"
        Expected = "ATC is ready to process data[\s\S]*#\d+=2[\s\S]*#\d+=99[\s\S]*#\d+=99[\s\S]*#\d+=\s+1\+0i\s+2\+0i\s+3\+0i\s+4\+0i\s+5\+0i\s+99\+0i"
        VariablesExpected = "foo 1 0:2 0:3 0\*4 0:5 0:99 0"
        InputLines = @("foo[0][1]", "foo[1][2]=99", "foo=foo[1][2]=99", "foo", "exit")
    }
)

$createMatrixTests = @(
    @{
        Name = "constant 2x2 matrix"
        Expression = "create matrix(foo\2\2\3)"
        Expected = "#\d+=\s+3\+0i\s+3\+0i\s+3\+0i\s+3\+0i"
        VariablesContent = ""
        VariablesExpected = "foo 3 0:3 0\*3 0:3 0"
    },
    @{
        Name = "expression 2x3 matrix"
        Expression = "create matrix(bar\2\3\1+2)"
        Expected = "#\d+=\s+3\+0i\s+3\+0i\s+3\+0i\s+3\+0i\s+3\+0i\s+3\+0i"
        VariablesContent = ""
        VariablesExpected = "bar 3 0:3 0:3 0\*3 0:3 0:3 0"
    }
)

$relaxedVariableNameContent = "data 7 0`nenergy 7 0`nbeta 7 0`nalpha 7 0`nmatx 7 0`nmatrixvar 7 0`nsinx 7 0`nbvar 7 0`n"
$relaxedVariableNameTests = @(
    @{ Name = "variable name starting with d"; Expression = "data+1"; Expected = "^#\d+=8$" },
    @{ Name = "variable name containing e"; Expression = "energy+1"; Expected = "^#\d+=8$" },
    @{ Name = "variable name containing b"; Expression = "beta+1"; Expected = "^#\d+=8$" },
    @{ Name = "variable name starting with a"; Expression = "alpha+1"; Expected = "^#\d+=8$" },
    @{ Name = "variable name starting with m"; Expression = "matx+1"; Expected = "^#\d+=8$" },
    @{ Name = "long matrix-like variable name"; Expression = "matrixvar+1"; Expected = "^#\d+=8$" },
    @{ Name = "variable name with function prefix"; Expression = "sinx+1"; Expected = "^#\d+=8$" },
    @{ Name = "variable name with reserved prefix"; Expression = "bvar+1"; Expected = "^#\d+=8$" }
)

$reservedPrefixVariableContent = "cosdata 7 0`ntanbeta 7 0`nmaxvalue 7 0`navgvalue 7 0`nlogbook 7 0`n"
$reservedPrefixVariableTests = @(
    @{ Name = "variable name with cosine prefix"; Expression = "cosdata+1"; Expected = "^#\d+=8$" },
    @{ Name = "variable name with tangent prefix"; Expression = "tanbeta+1"; Expected = "^#\d+=8$" },
    @{ Name = "variable name with max prefix"; Expression = "maxvalue+1"; Expected = "^#\d+=8$" },
    @{ Name = "variable name with avg prefix"; Expression = "avgvalue+1"; Expected = "^#\d+=8$" },
    @{ Name = "variable name with log prefix"; Expression = "logbook+1"; Expected = "^#\d+=8$" }
)

$uppercaseNegativeVariableContent = "Y -0.7082039324999838 0`n"
$uppercaseNegativeVariableTests = @(
    @{ Name = "uppercase negative scalar variable"; Expression = "Y"; Expected = "^#\d+=-0\.708204$" },
    @{ Name = "uppercase negative scalar in addition"; Expression = "Y+1"; Expected = "^#\d+=0\.291796$" },
    @{ Name = "uppercase negative scalar in polynomial expression"; Expression = "Y^2-12Y-9"; Expected = "^#\d+=8\.24762E-12$" }
)

$implicitVariableContent = "x 2 0`ny 3 0`n"
$implicitVariableTests = @(
    @{ Name = "number before variable"; Expression = "2x"; Expected = "^#\d+=4$" },
    @{ Name = "variable before number"; Expression = "x2"; Expected = "^#\d+=4$" },
    @{ Name = "variable before parentheses"; Expression = "x(4)"; Expected = "^#\d+=8$" },
    @{ Name = "parentheses before variable"; Expression = "(4)x"; Expected = "^#\d+=8$" },
    @{ Name = "variable before pi"; Expression = "xpi"; Expected = "^#\d+=6\.28319$" },
    @{ Name = "pi before variable"; Expression = "pix"; Expected = "^#\d+=6\.28319$" },
    @{ Name = "variable before Euler number"; Expression = "xe"; Expected = "^#\d+=5\.43656$" },
    @{ Name = "variable before function"; Expression = "xsin(pi/2)"; Expected = "^#\d+=2$" },
    @{ Name = "function before variable"; Expression = "sin(pi/2)x"; Expected = "^#\d+=2$" },
    @{ Name = "variable before imaginary unit"; Expression = "xi"; Expected = "^#\d+=2i$" },
    @{ Name = "parenthesized variable expression before variable"; Expression = "(x+1)y"; Expected = "^#\d+=9$" },
    @{ Name = "adjacent variable fallback"; Expression = "xy"; Expected = "^#\d+=6$" },
    @{ Name = "spaced variable fallback"; Expression = "x y"; Expected = "^#\d+=6$" }
)

$implicitCompositeVariableContent = "x 2 0`ny 3 0`nxy 11 0`n"
$implicitCompositeVariableTests = @(
    @{ Name = "composite variable has priority"; Expression = "xy"; Expected = "^#\d+=11$" },
    @{ Name = "spaced composite variable has priority after whitespace normalization"; Expression = "x y"; Expected = "^#\d+=11$" }
)

$longCompositeVariableContent = "foo 2 0`nbar 3 0`nfoobar 17 0`n"
$longCompositeVariableTests = @(
    @{ Name = "long composite variable has priority"; Expression = "foobar"; Expected = "^#\d+=17$" },
    @{ Name = "spaced long composite variable has priority after whitespace normalization"; Expression = "foo bar"; Expected = "^#\d+=17$" }
)

$guideExportTests = @(
    @{ Name = "ascending numeric order"; Expression = "ascending order(3\1\2)"; ConsoleExpected = "Your report was saved successfully"; FileExpected = "1\+0i, 2\+0i, 3\+0i" },
    @{ Name = "descending numeric order"; Expression = "descending order(3\1\2)"; ConsoleExpected = "Your report was saved successfully"; FileExpected = "3\+0i, 2\+0i, 1\+0i" },
    @{ Name = "ascending numeric order with negatives"; Expression = "ascending order(_3\1\_2\0)"; ConsoleExpected = "Your report was saved successfully"; FileExpected = "-3\+0i, -2\+0i, 0\+0i, 1\+0i" },
    @{ Name = "descending numeric order with negatives"; Expression = "descending order(_3\1\_2\0)"; ConsoleExpected = "Your report was saved successfully"; FileExpected = "1\+0i, 0\+0i, -2\+0i, -3\+0i" },
    @{ Name = "roots to polynomial"; Expression = "roots to polynomial(2\3)"; ConsoleExpected = "Your report was saved successfully"; FileExpected = "\(1\+0i\)x\^2\+\(_5\+0i\)x\^1\+\(6\+0i\)" },
    @{ Name = "roots to cubic polynomial"; Expression = "roots to polynomial(2\7\12)"; ConsoleExpected = "Your report was saved successfully"; FileExpected = "\(1\+0i\)x\^3\+\(_21\+0i\)x\^2\+\(122\+0i\)x\^1\+\(_168\+0i\)" },
    @{ Name = "roots to polynomial with complex conjugates"; Expression = "roots to polynomial(6.5i\_6.5i)"; ConsoleExpected = "Your report was saved successfully"; FileExpected = "\(1\+0i\)x\^2\+\(0\+0i\)x\^1\+\(42\.25\+0i\)" },
    @{ Name = "roots to polynomial with shifted complex conjugates"; Expression = "roots to polynomial(1+2i\1-2i)"; ConsoleExpected = "Your report was saved successfully"; FileExpected = "\(1\+0i\)x\^2\+\(_2\+0i\)x\^1\+\(5\+0i\)" },
    @{ Name = "roots to polynomial with zero root"; Expression = "roots to polynomial(0\1\2)"; ConsoleExpected = "Your report was saved successfully"; FileExpected = "\(1\+0i\)x\^3\+\(_3\+0i\)x\^2\+\(2\+0i\)x\^1\+\(0\+0i\)" }
)

$exportDeclineTests = @(
    @{ Name = "decline ascending numeric order export"; Expression = "ascending order(3\1\2)"; ConsoleExpected = "1\+0i, 2\+0i, 3\+0i" },
    @{ Name = "decline roots to polynomial export"; Expression = "roots to polynomial(2\3)"; ConsoleExpected = "\(1\+0i\)x\^2\+\(_5\+0i\)x\^1\+\(6\+0i\)" },
    @{ Name = "decline simplify polynomial export"; Expression = "simplify polynomial((x-2)*(x-3))"; ConsoleExpected = "\(1\+0i\)x\^2\+\(_5\+0i\)x\^1\+\(6\+0i\)" },
    @{ Name = "decline equation export"; Expression = "solve equation(x+2)"; ConsoleExpected = "x1=-2" }
)

$asciiSortingTests = @(
    @{
        Name = "ascending ascii order"
        Expression = "ascii order"
        Expected = "apple\s+banana\s+cherry[\s\S]*Export result\?[\s\S]*Continue\?"
        InputLines = @("banana\apple\cherry", "0", "0")
    },
    @{
        Name = "descending ascii order"
        Expression = "inverse ascii order"
        Expected = "cherry\s+banana\s+apple[\s\S]*Export result\?[\s\S]*Continue\?"
        InputLines = @("banana\apple\cherry", "0", "0")
    }
)

$polynomialSimplifyTests = @(
    @{ Name = "identity x"; Expression = "simplify polynomial(x)"; Expected = "\(1\+0i\)x\^1\+\(0\+0i\)" },
    @{ Name = "linear expression"; Expression = "simplify polynomial(x+1)"; Expected = "\(1\+0i\)x\^1\+\(1\+0i\)" },
    @{ Name = "combine like terms"; Expression = "simplify polynomial(x+x+1)"; Expected = "\(2\+0i\)x\^1\+\(1\+0i\)" },
    @{ Name = "quadratic textual polynomial"; Expression = "simplify polynomial(x^2-5*x+6)"; Expected = "\(1\+0i\)x\^2\+\(_5\+0i\)x\^1\+\(6\+0i\)" },
    @{ Name = "binomial product"; Expression = "simplify polynomial((x-2)*(x-3))"; Expected = "\(1\+0i\)x\^2\+\(_5\+0i\)x\^1\+\(6\+0i\)" },
    @{ Name = "square binomial"; Expression = "simplify polynomial((x+1)*(x+1))"; Expected = "\(1\+0i\)x\^2\+\(2\+0i\)x\^1\+\(1\+0i\)" },
    @{ Name = "powered binomial"; Expression = "simplify polynomial((x-1)^2)"; Expected = "\(1\+0i\)x\^2\+\(_2\+0i\)x\^1\+\(1\+0i\)" },
    @{ Name = "repeated binomial product cubic"; Expression = "simplify polynomial((x-1)(x-1)(x-1))"; Expected = "\(1\+0i\)x\^3\+\(_3\+0i\)x\^2\+\(3\+0i\)x\^1\+\(_1\+0i\)" },
    @{ Name = "difference of squares product"; Expression = "simplify polynomial((x+2)*(x-2))"; Expected = "\(1\+0i\)x\^2\+\(_4\+0i\)" },
    @{ Name = "imaginary conjugate product"; Expression = "simplify polynomial((x+2i)*(x-2i))"; Expected = "\(1\+0i\)x\^2\+\(4\+0i\)" },
    @{ Name = "cubic factor with quadratic"; Expression = "simplify polynomial((x+1)*(x^2+x+1))"; Expected = "\(1\+0i\)x\^3\+\(2\+0i\)x\^2\+\(2\+0i\)x\^1\+\(1\+0i\)" },
    @{ Name = "quartic product"; Expression = "simplify polynomial((x^2-1)*(x^2+1))"; Expected = "\(1\+0i\)x\^4\+\(_1\+0i\)" },
    @{ Name = "scaled binomial product"; Expression = "simplify polynomial((2*x+1)*(x-3))"; Expected = "\(2\+0i\)x\^2\+\(_5\+0i\)x\^1\+\(_3\+0i\)" },
    @{ Name = "scaled binomial product with positive middle term"; Expression = "simplify polynomial((3*x-2)*(2*x+5))"; Expected = "\(6\+0i\)x\^2\+\(11\+0i\)x\^1\+\(_10\+0i\)" },
    @{ Name = "complex roots written as subtracted groups"; Expression = "simplify polynomial((x-(1+2i))*(x-(1-2i)))"; Expected = "\(1\+0i\)x\^2\+\(_2\+0i\)x\^1\+\(5\+0i\)" },
    @{ Name = "complex conjugate product"; Expression = "simplify polynomial((x-1)(x+6.5i)(x-6.5i))"; Expected = "\(1\+0i\)x\^3\+\(_1\+0i\)x\^2\+\(42\.25\+0i\)x\^1\+\(_42\.25\+0i\)" },
    @{ Name = "complex product with zero root"; Expression = "simplify polynomial((x-1)(x-0)(x-0.5i)(x-2))"; Expected = "\(1\+0i\)x\^4\+\(_3\+_0\.5i\)x\^3\+\(2\+1\.5i\)x\^2\+\(0\+_1i\)x\^1\+\(0\+0i\)" },
    @{ Name = "rational product cancels all factors to one"; Expression = "simplify polynomial(((x-7)(x+8))/((x-7)(x+8)))"; Expected = "\(0\+0i\)x\^1\+\(1\+0i\)" },
    @{ Name = "rational product cancels common factor"; Expression = "simplify polynomial(((x-5)(x+2))/(x-5))"; Expected = "\(1\+0i\)x\^1\+\(2\+0i\)" },
    @{ Name = "nested rational product cancels common factor"; Expression = "simplify polynomial((((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5)))"; Expected = "\(1\+0i\)x\^2\+\(4\+0i\)x\^1\+\(4\+0i\)" }
)

$equationSolverTests = @(
    @{ Name = "quadratic two real roots"; Expression = "solve quadratic equation(1\_5\6)"; Expected = "x1=3\s+x2=2" },
    @{ Name = "quadratic repeated root"; Expression = "solve quadratic equation(1\_2\1)"; Expected = "x1=1\s+x2=1" },
    @{ Name = "quadratic complex roots"; Expression = "solve quadratic equation(1\2\5)"; Expected = "x1=-1\+2i\s+x2=-1-2i" },
    @{ Name = "quadratic symmetric roots"; Expression = "solve quadratic equation(1\0\_4)"; Expected = "x1=2\s+x2=-2" },
    @{ Name = "linear equations system"; Expression = "solve equations system(1\1\5;1\_1\1)"; Expected = "x1=3\s+x2=2" },
    @{ Name = "linear equations system alternate"; Expression = "solve equations system(2\1\5;1\_1\1)"; Expected = "x1=2\s+x2=1" }
)

$solverFunctionTests = @(
    @{ Name = "trigonometric equation radian mode"; Expression = "solver(sin(x)-0.5)"; Expected = "^#\d+=0\.523599"; ModeValue = "1" },
    @{ Name = "trigonometric equation degree mode"; Expression = "solver(sin(x)-0.5)"; Expected = "^#\d+=30$"; ModeValue = "2" },
    @{ Name = "trigonometric equation gradian mode"; Expression = "solver(sin(x)-0.5)"; Expected = "^#\d+=33\.3333"; ModeValue = "3" },
    @{ Name = "complex trigonometric equation degree mode"; Expression = "solver(sin(x)-0.5+0.5i)"; Expected = "^#\d+=25\.9136-30\.4033i"; ModeValue = "2" },
    @{ Name = "mirrored trigonometric equation degree mode"; Expression = "solver(0.5-sin(x))"; Expected = "^#\d+=30$"; ModeValue = "2" },
    @{ Name = "complex trigonometric expression target degree mode"; Expression = "solver(sin(x)-sin(30+30i))"; Expected = "^#\d+=30\+30i"; ModeValue = "2" },
    @{ Name = "mirrored sine target degree mode"; Expression = "solver(sin(30)-sin(x))"; Expected = "^#\d+=30$"; ModeValue = "2" },
    @{ Name = "cosine target degree mode"; Expression = "solver(cos(x)-cos(60))"; Expected = "^#\d+=60$"; ModeValue = "2" },
    @{ Name = "mirrored cosine target degree mode"; Expression = "solver(cos(60)-cos(x))"; Expected = "^#\d+=60$"; ModeValue = "2" },
    @{ Name = "tangent target degree mode"; Expression = "solver(tan(x)-tan(45))"; Expected = "^#\d+=45$"; ModeValue = "2" },
    @{ Name = "mirrored tangent target degree mode"; Expression = "solver(tan(45)-tan(x))"; Expected = "^#\d+=45$"; ModeValue = "2" },
    @{ Name = "inverse trigonometric linear target degree mode"; Expression = "solver(asin(sin(30))-x)"; Expected = "^#\d+=30$"; ModeValue = "2" },
    @{ Name = "complex inverse trigonometric linear target degree mode"; Expression = "solver(asin(sin(30+30i))-x)"; Expected = "^#\d+=30\+30i"; ModeValue = "2" },
    @{ Name = "qfunc target"; Expression = "solver(qfunc(x)-qfunc(0.34233))"; Expected = "^#\d+=0\.34233$"; ModeValue = "1" },
    @{ Name = "mirrored qfunc target"; Expression = "solver(qfunc(0.34233)-qfunc(x))"; Expected = "^#\d+=0\.34233$"; ModeValue = "1" },
    @{ Name = "polynomial Newton equation"; Expression = "solver(x^2-12x-9)"; Expected = "^#\d+=-0\.708204$"; ModeValue = "1" },
    @{ Name = "linear polynomial fast path"; Expression = "solver(x+2)"; Expected = "^#\d+=-2$"; ModeValue = "1" },
    @{ Name = "complex linear symbolic constant solver fast path"; Expression = "solver(x-e+pii)"; Expected = "^#\d+=2\.71828-3\.14159i$"; ModeValue = "1" },
    @{ Name = "complex product symbolic constant solver fast path"; Expression = "solver((x-e+pii)(x-e-pii))"; Expected = "^#\d+=2\.71828-3\.14159i$"; ModeValue = "1" },
    @{ Name = "rational product linear fast path"; Expression = "solver(((x-5)(x+2))/(x-5))"; Expected = "^#\d+=-2$"; ModeValue = "1" },
    @{ Name = "nested rational product linear fast path"; Expression = "solver((((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5)))"; Expected = "^#\d+=-2$"; ModeValue = "1" },
    @{ Name = "triple nested rational product linear fast path"; Expression = "solver((((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5)))"; Expected = "^#\d+=-2$"; ModeValue = "1" },
    @{ Name = "quartic nested rational product linear fast path"; Expression = "solver((((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5)))"; Expected = "^#\d+=-2$"; ModeValue = "1" },
    @{ Name = "complex mixed rational product solver fast path"; Expression = "solver((((x-e+pii)(x-e-pii))/(x-e+pii))*(((x-e+pii)(x-e-pii))/(x-e-pii))*(((x-e+pii)(x-e-pii))/(x-e+pii)))"; Expected = "^#\d+=2\.71828\+3\.14159i$"; ModeValue = "1" },
    @{ Name = "complex hyperbolic cosh target radian mode"; Expression = "solver(cosh(x)-cosh(2+2i))"; Expected = "^#\d+=2\+2i"; ModeValue = "1" },
    @{ Name = "mirrored hyperbolic cosh target radian mode"; Expression = "solver(cosh(12)-cosh(x))"; Expected = "^#\d+=12$"; ModeValue = "1" },
    @{ Name = "mirrored complex hyperbolic cosh target radian mode"; Expression = "solver(cosh(2+2i)-cosh(x))"; Expected = "^#\d+=2\+2i"; ModeValue = "1" },
    @{ Name = "complex hyperbolic sinh target radian mode"; Expression = "solver(sinh(x)-sinh(2+2i))"; Expected = "^#\d+=2\+2i"; ModeValue = "1" },
    @{ Name = "mirrored complex hyperbolic sinh target radian mode"; Expression = "solver(sinh(2+2i)-sinh(x))"; Expected = "^#\d+=2\+2i"; ModeValue = "1" },
    @{ Name = "complex hyperbolic tanh target radian mode"; Expression = "solver(tanh(x)-tanh(2+2i))"; Expected = "^#\d+=2\+2i"; ModeValue = "1" },
    @{ Name = "mirrored complex hyperbolic tanh target radian mode"; Expression = "solver(tanh(2+2i)-tanh(x))"; Expected = "^#\d+=2\+2i"; ModeValue = "1" }
)

$equationExportTests = @(
    @{ Name = "linear equation export"; Expression = "solve equation(x+2)"; ConsoleExpected = "Your report was saved successfully"; FileExpected = "x1=-2" },
    @{ Name = "cubic coefficient equation export"; Expression = "solve equation(1\8\1\_42)"; ConsoleExpected = "Your report was saved successfully"; FileExpected = "x1=2\s+x2=-3\s+x3=-7" },
    @{ Name = "quadratic textual polynomial export"; Expression = "solve equation(x^2-5*x+6)"; ConsoleExpected = "Your report was saved successfully"; FileExpected = "x1=3\s+x2=2" },
    @{ Name = "degree seven textual polynomial export"; Expression = "solve equation(x^7-12)"; ConsoleExpected = "Your report was saved successfully"; FileExpected = "x1=1\.42616\s+x2=0\.889197-1\.11502i\s+x3=0\.889197\+1\.11502i\s+x4=-0\.317351-1\.3904i\s+x5=-0\.317351\+1\.3904i\s+x6=-1\.28493-0\.618788i\s+x7=-1\.28493\+0\.618788i" }
)

$equationFastPathTests = @(
    @{
        Name = "coefficient list quartic"
        Expression = "solve equation(1\2\3\4\5)"
        Expected = "x1=0\.287815-1\.41609i\s+x2=0\.287815\+1\.41609i\s+x3=-1\.28782-0\.857897i\s+x4=-1\.28782\+0\.857897i"
    },
    @{
        Name = "coefficient list degree thirty"
        Expression = "solve equation(1\2\3\4\5\6\7\8\9\10\11\12\13\14\15\16\17\18\19\20\21\22\23\24\25\26\27\28\29\30\31)"
        Expected = "x1=1\.03864-0\.250812i[\s\S]*x30=-1\.13496\+0\.113718i"
    },
    @{
        Name = "implicit product two real roots"
        Expression = "solve equation((x-1)(x-2))"
        Expected = "x1=2\s+x2=1"
    },
    @{
        Name = "single parenthesized linear factor"
        Expression = "solve equation((x-5))"
        Expected = "x1=5"
    },
    @{
        Name = "rational product cancels common factor"
        Expression = "solve equation(((x-5)(x+2))/(x-5))"
        Expected = "x1=-2"
    },
    @{
        Name = "nested rational product cancels common factor"
        Expression = "solve equation((((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5)))"
        Expected = "x1=-2\s+x2=-2"
    },
    @{
        Name = "quartic nested rational product cancels common factor"
        Expression = "solve equation((((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5)))"
        Expected = "x1=-2\s+x2=-2\s+x3=-2\s+x4=-2"
    },
    @{
        Name = "quintic nested rational product cancels common factor"
        Expression = "solve equation((((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5)))"
        Expected = "x1=-2\s+x2=-2\s+x3=-2\s+x4=-2\s+x5=-2"
    },
    @{
        Name = "nested rational product with pi factor"
        Expression = "solve equation((((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5))*(((x-5)(x+pi))/(x-5)))"
        Expected = "x1=-2\s+x2=-2\s+x3=-2\s+x4=-2\s+x5=-2\s+x6=-3\.14159"
    },
    @{
        Name = "nested rational product with pi and e factors"
        Expression = "solve equation((((x-5)(x+2))/(x-5))*(((x-5)(x+pi))/(x-5))*(((x-5)(x+e))/(x-5)))"
        Expected = "x1=-2\s+x2=-2\.71828\s+x3=-3\.14159"
    },
    @{
        Name = "single parenthesized complex linear factor"
        Expression = "solve equation((x-0.5i))"
        Expected = "x1=0\+0\.5i"
    },
    @{
        Name = "implicit product with complex linear factor"
        Expression = "solve equation((x+2)(x+3i))"
        Expected = "x1=0-3i\s+x2=-2"
    },
    @{
        Name = "rational product cancels symbolic complex factor"
        Expression = "solve equation(((x-e+pii)(x-e-pii))/(x-e-pii))"
        Expected = "x1=2\.71828-3\.14159i"
    },
    @{
        Name = "linear symbolic complex factor"
        Expression = "solve equation((x-e+2pii))"
        Expected = "x1=2\.71828-6\.28319i"
    },
    @{
        Name = "implicit product three real roots"
        Expression = "solve equation((x-1)(x-2)(x-6))"
        Expected = "x1=6\s+x2=2\s+x3=1"
    },
    @{
        Name = "implicit product with zero root"
        Expression = "solve equation((x-0)(x-1)(x-2))"
        Expected = "x1=2\s+x2=1\s+x3=0"
    },
    @{
        Name = "implicit product symmetric quartic"
        Expression = "solve equation((x-1)(x+1)(x-2)(x+2))"
        Expected = "x1=2\s+x2=1\s+x3=-1\s+x4=-2"
    },
    @{
        Name = "implicit product five real roots"
        Expression = "solve equation((x-1)(x-2)(x-3)(x-4)(x-5))"
        Expected = "x1=5\s+x2=4\s+x3=3\s+x4=2\s+x5=1"
    },
    @{
        Name = "implicit product complex roots"
        Expression = "solve equation((x-1)(x+6.5i)(x-6.5i))"
        Expected = "x1=1\s+x2=0\+6\.5i\s+x3=0-6\.5i"
    },
    @{
        Name = "implicit product one complex root"
        Expression = "solve equation((x-1)(x-2)(x+6.9i))"
        Expected = "x1=2\s+x2=1\s+x3=0-6\.9i"
    },
    @{
        Name = "invalid implicit product is rejected"
        Expression = "solve equation((x-1)(x-2)(x6.9))"
        Expected = "ATC was unable to solve this polynomial with the fast polynomial path"
    },
    @{
        Name = "internal complex quadratic"
        Expression = "solve equation((1+0i)x^2+(0+0i)x^1+(42.25+0i))"
        Expected = "x1=0-6\.5i\s+x2=0\+6\.5i"
    },
    @{
        Name = "internal complex polynomial with zero root"
        Expression = "solve equation((1+0i)x^4+(_3+_0.5i)x^3+(2+1.5i)x^2+(0+_1i)x^1+(0+0i))"
        Expected = "x1=2\s+x2=1\s+x3=0\s+x4=0\+0\.5i"
    },
    @{
        Name = "internal repeated cubic root"
        Expression = "solve equation((1+0i)x^3+(_3+0i)x^2+(3+0i)x^1+(_1+0i))"
        Expected = "x1=1\s+x2=1\s+x3=1"
    },
    @{
        Name = "internal quadratic from subtracted complex groups"
        Expression = "solve equation((1+0i)x^2+(_2+0i)x^1+(5+0i))"
        Expected = "x1=1-2i\s+x2=1\+2i"
    },
    @{
        Name = "internal fourth roots of one"
        Expression = "solve equation((1+0i)x^4+(0+0i)x^3+(0+0i)x^2+(0+0i)x^1+(_1+0i))"
        Expected = "x1=1\s+x2=0-1i\s+x3=0\+1i\s+x4=-1"
    },
    @{
        Name = "internal fourth roots of minus one"
        Expression = "solve equation((1+0i)x^4+(0+0i)x^3+(0+0i)x^2+(0+0i)x^1+(1+0i))"
        Expected = "x1=0\.707107-0\.707107i\s+x2=0\.707107\+0\.707107i\s+x3=-0\.707107-0\.707107i\s+x4=-0\.707107\+0\.707107i"
    },
    @{
        Name = "textual tenth roots of unity"
        Expression = "solve equation(x^10-1)"
        Expected = "x1=1\s+x2=0\.809017-0\.587785i[\s\S]*x9=-0\.809017\+0\.587785i\s+x10=-1"
    },
    @{
        Name = "textual degree twenty five roots"
        Expression = "solve equation(x^25-100)"
        Expected = "x1=1\.20226\s+x2=1\.16449-0\.298991i[\s\S]*x24=-1\.19278-0\.150684i\s+x25=-1\.19278\+0\.150684i"
    },
    @{
        Name = "internal expanded roots one to twenty"
        Expression = "solve equation((1+0i)x^20+(_210+0i)x^19+(20615+0i)x^18+(_1256850+0i)x^17+(53327946+0i)x^16+(_1672280820+0i)x^15+(40171771630+0i)x^14+(_756111184500+0i)x^13+(11310276995381+0i)x^12+(_135585182899530+0i)x^11+(1307535010540395+0i)x^10+(_10142299865511450+0i)x^9+(63030812099294896+0i)x^8+(_311333643161390592+0i)x^7+(1206647803780373248+0i)x^6+(_3599979517947607552+0i)x^5+(8037811822645051392+0i)x^4+(_12870931245150986240+0i)x^3+(13803759753640706048+0i)x^2+(_8752948036761601024+0i)x^1+(2432902008176640000+0i))"
        Expected = "x1=20\s+x2=19[\s\S]*x19=2\s+x20=1"
    },
    @{
        Name = "internal expanded roots one to thirty rounded"
        Expression = "solve equation((1+0i)x^30+(_465+0i)x^29+(103385+0i)x^28+(_14631225+0i)x^27+(1480321269+0i)x^26+(_114009431445+0i)x^25+(6949189247325+0i)x^24+(_344092707928125+0i)x^23+(14097793282984516+0i)x^22+(_484338676679532672+0i)x^21+(14090257524223082496+0i)x^20+(_349600545868057542656+0i)x^19+(7435941626111728812032+0i)x^18+(_136055808711963340439552+0i)x^17+(2145883249334502293504000+0i)x^16+(_29197210605623744019824640+0i)x^15+(342563613932937757170073600+0i)x^14+(_3460266110493899526852575232+0i)x^13+(30006513636556699728284221440+0i)x^12+(_222457423246962051116563431424+0i)x^11+(1401937624086807321099265638400+0i)x^10+(_7454161471690659788189314580480+0i)x^9+(33114629767614991037213800660992+0i)x^8+(_121365366674745170158145442414592+0i)x^7+(360930788158836595287765381283840+0i)x^6+(_851899888505423116603166520508416+0i)x^5+(1547794975254719999379763051364352+0i)x^4+(_2070792202024595295229681577492480+0i)x^3+(1902893785240927722307038455267328+0i)x^2+(_1059681761389533906927603618414592+0i)x^1+(265252859812191104246398737973248+0i))"
        Expected = "x1=30\s+x2=29[\s\S]*x29=2\s+x30=1"
    }
)

$functionStudyTests = @(
    @{
        Name = "linear polynomial"
        Expression = "function study(x+1)"
        Expected = "\(-1,0\)[\s\S]*\(0,1\.000\)[\s\S]*The function is not even\.[\s\S]*The function is not odd\.[\s\S]*f\(x\)=\(1\+0i\)x\^1\+\(1\+0i\)[\s\S]*f'\(x\)=\(1\+0i\)[\s\S]*Codomain: \]-inf,\+inf\["
    },
    @{
        Name = "rational even function"
        Expression = "function study((1-x^2)/(x^2-4))"
        Expected = "Df=R\\\{2,-2\}[\s\S]*\(1,0\)[\s\S]*\(-1,0\)[\s\S]*x=2[\s\S]*x=-2[\s\S]*The function is even\.[\s\S]*f'\(x\)=\(\(6\+0i\)x\^1\+\(0\+0i\)\)[\s\S]*Min: \(0\.000,-0\.250\)"
    },
    @{
        Name = "rational odd function"
        Expression = "function study(x/(x^2-9))"
        Expected = "Df=R\\\{3,-3\}[\s\S]*\(0,0\)[\s\S]*x=3[\s\S]*x=-3[\s\S]*The function is odd\.[\s\S]*Numerator-> \(1\+0i\)x\^1\+\(0\+0i\)[\s\S]*Denominator-> \(1\+0i\)x\^2\+\(0\+0i\)x\^1\+\(_9\+0i\)"
    },
    @{
        Name = "polynomial parabola minimum"
        Expression = "function study(x^2)"
        Expected = "f\(x\)=\(1\+0i\)x\^2\+\(0\+0i\)x\^1\+\(0\+0i\)[\s\S]*f'\(x\)=\(\(2\+0i\)x\^1\+\(0\+0i\)\)[\s\S]*x\s+-inf\s+0\.000\s+\+inf[\s\S]*Codomain: \[0\.000,\+inf\[[\s\S]*Min: \(0\.000,0\.000\)"
    },
    @{
        Name = "shifted polynomial parabola minimum"
        Expression = "function study(x^2-4)"
        Expected = "\(2,0\)[\s\S]*\(-2,0\)[\s\S]*\(0,-4\.000\)[\s\S]*The function is even\.[\s\S]*f\(x\)=\(1\+0i\)x\^2\+\(0\+0i\)x\^1\+\(_4\+0i\)[\s\S]*Codomain: \[-4\.000,\+inf\[[\s\S]*Min: \(0\.000,-4\.000\)"
    },
    @{
        Name = "polynomial parabola maximum"
        Expression = "function study(_x^2)"
        Expected = "f\(x\)=\(_1\+0i\)x\^2\+\(0\+0i\)x\^1\+\(0\+0i\)[\s\S]*f'\(x\)=\(\(_2\+0i\)x\^1\+\(0\+0i\)\)[\s\S]*x\s+-inf\s+0\.000\s+\+inf[\s\S]*Codomain: \]-inf,0\.000\][\s\S]*Max: \(0\.000,0\.000\)"
    },
    @{
        Name = "rational real vertical asymptote"
        Expression = "function study(1/(x-1))"
        Expected = "Df=R\\\{1\}[\s\S]*Has as vertical asymptotes the lines below:[\s\S]*x=1[\s\S]*Has a horizontal asymptote when lim x-> \+inf: 0\.000"
    },
    @{
        Name = "rational removable discontinuity"
        Expression = "function study((x^2-1)/(x-1))"
        Expected = "Df=R\\\{1\}[\s\S]*It does not have vertical asymptotes\.[\s\S]*It does not have a horizontal asymptote when lim x-> \+inf"
    },
    @{
        Name = "rational complex denominator roots"
        Expression = "function study((x+1)/(x^2+1))"
        Expected = "Df=R[\s\S]*It does not have vertical asymptotes\.[\s\S]*Has a horizontal asymptote when lim x-> \+inf: 0\.000"
    }
)

$graphTests = @(
    @{
        Name = "graph settings display"
        Expression = "graph settings"
        Expected = "Current settings:[\s\S]*Auto Y-axis:[\s\S]*Auto X-axis:"
        InputLines = @("0")
    },
    @{
        Name = "linear graph smoke"
        Expression = "graph(x)"
        Expected = "Graph non-interactive mode[\s\S]*Function: x[\s\S]*Current settings:[\s\S]*Xmin:[\s\S]*Xmax:[\s\S]*Ymin:[\s\S]*Ymax:"
        InputLines = @()
    },
    @{
        Name = "interactive navigation simulation"
        Expression = "graph(x)"
        Expected = "Graph navigation test[\s\S]*Index: 2[\s\S]*x = -4\.8"
        InputLines = @("0")
        GraphContent = "_5`n7`n1`n_3`n3`n1`n0`n0"
        Environment = @{ ATC_GRAPH_NAVIGATION_TEST = "RRRLLR" }
    },
    @{
        Name = "navigation clamps at left edge"
        Expression = "graph(x)"
        Expected = "Graph navigation test[\s\S]*Index: 0[\s\S]*x = -5\.000000[\s\S]*x \[X\]: -5\.000000"
        InputLines = @("0")
        GraphContent = "_5`n7`n1`n_3`n3`n1`n0`n0"
        Environment = @{ ATC_GRAPH_NAVIGATION_TEST = "LLLL" }
    },
    @{
        Name = "navigation clamps at right edge"
        Expression = "graph(x)"
        Expected = "Graph navigation test[\s\S]*Index: 120[\s\S]*x = 7\.000000[\s\S]*x \[X\]: 7\.000000"
        InputLines = @("0")
        GraphContent = "_5`n7`n1`n_3`n3`n1`n0`n0"
        Environment = @{ ATC_GRAPH_NAVIGATION_TEST = ("R" * 160) }
    },
    @{
        Name = "explicit graph range navigation"
        Expression = "graph(x;_2\2\1)"
        Expected = "Graph navigation test[\s\S]*Index: 60[\s\S]*x = 0\.000000[\s\S]*x \[X\]: 0\.000000"
        InputLines = @("0")
        Environment = @{ ATC_GRAPH_NAVIGATION_TEST = ("R" * 60) }
    }
)

$graphSettingsMutationTests = @(
    @{
        Name = "graph settings mutation"
        Expression = "graph settings"
        Expected = "Would you like to change them\?[\s\S]*Auto X-axis\?[\s\S]*Xmin\?[\s\S]*Yscale\?"
        InputLines = @("1", "0", "_5", "5", "1", "0", "_2", "2", "1")
        FileExpected = "_5`n5`n1`n_2`n2`n1`n0`n0"
    }
)

$dateCommandTests = @(
    @{
        Name = "current time format"
        Expression = "time"
        Expected = "^(Monday|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday), (January|February|March|April|May|June|July|August|September|October|November|December) \d{1,2}(st|nd|rd|th), \d{4}, \d{1,2}h \d{1,2}m \d{1,2}s$"
    },
    @{ Name = "day of week current regression date"; Expression = "day of week(y2026m6d20)"; Expected = "y2026m6d20=Saturday" },
    @{ Name = "day of week millennium"; Expression = "day of week(y2000m1d1)"; Expected = "y2000m1d1=Saturday" },
    @{ Name = "day of week leap day"; Expression = "day of week(y2024m2d29)"; Expected = "y2024m2d29=Thursday" },
    @{ Name = "day of week alternate argument order"; Expression = "day of week(d20m6y2026)"; Expected = "y2026m6d20=Saturday" },
    @{
        Name = "calendar fixed year"
        Expression = "calendar(2026)"
        Expected = "2026[\s\S]*January[\s\S]*February[\s\S]*March[\s\S]*April[\s\S]*May[\s\S]*June[\s\S]*July[\s\S]*August[\s\S]*September[\s\S]*October[\s\S]*November[\s\S]*December"
    },
    @{
        Name = "time difference fixed interval"
        Expression = "time difference calculations"
        Expected = "Time difference: 0 years, 0 months, 1 days, 1 hours, 2 minutes and 3 seconds[\s\S]*Time difference: 90123 seconds[\s\S]*Time difference: 0\.27% of 2020"
        InputLines = @("3", "2020", "1", "1", "0", "0", "0", "2020", "1", "2", "1", "2", "3", "0", "0")
    }
)

$actualTimeResponseTests = @(
    @{
        Name = "enable actual time response"
        Expression = "actual time response"
        Expected = "Configuration of actual time response[\s\S]*Enable -> 1[\s\S]*Disable -> 0"
        InputLines = @("1")
        FileExpected = "1"
    },
    @{
        Name = "disable actual time response"
        Expression = "actual time response"
        Expected = "Configuration of actual time response[\s\S]*Enable -> 1[\s\S]*Disable -> 0"
        InputLines = @("0")
        FileExpected = "0"
    }
)

$deepInteractiveModuleTests = @(
    @{
        Name = "unit conversions length"
        Expression = "unit conversions"
        Expected = "What to convert\\?[\s\S]*Length -> 1[\s\S]*Meter: 1[\s\S]*Kilometer: 0\.001[\s\S]*Continue\\?"
        InputLines = @("1", "1", "1", "0", "0")
    },
    @{
        Name = "microeconomics profit"
        Expression = "microeconomics calculations"
        Expected = "What to calculate\\?[\s\S]*Profit -> 6[\s\S]*Total Revenue\\?[\s\S]*Total Expenses\\?[\s\S]*Profit: 6[\s\S]*Continue\\?"
        InputLines = @("6", "10", "4", "0")
    },
    @{
        Name = "physics acceleration"
        Expression = "physics calculations"
        Expected = "What to calculate\?[\s\S]*Acceleration -> 1[\s\S]*Initial Speed[\s\S]*Final Speed[\s\S]*Time[\s\S]*Acceleration[\s\S]*Acceleration: 5"
        InputLines = @("1", "0", "10", "2", "x", "0")
    },
    @{
        Name = "statistics population measures"
        Expression = "statistics calculations"
        Expected = "Population Measures[\s\S]*Mean: 4[\s\S]*Variance: 2\.66667[\s\S]*Standard Deviation: 1\.63299"
        InputLines = @("1", "2\4\6", "0")
    },
    @{
        Name = "geometry square"
        Expression = "geometry calculations"
        Expected = "Square -> 1[\s\S]*Side\\?[\s\S]*Area: 4[\s\S]*Perimeter: 8"
        InputLines = @("1", "2", "0")
    },
    @{
        Name = "financial simple interest"
        Expression = "financial calculations"
        Expected = 'Simple Interest -> 3[\s\S]*Principal\?[\s\S]*Rate \(%\)\?[\s\S]*Time\?[\s\S]*Simple Interest: \$10\.00'
        InputLines = @("3", "100", "5", "2", "0")
    },
    @{
        Name = "triangles rectangles solver"
        Expression = "triangles rectangles solver"
        Expected = "Report of results[\s\S]*The opposite is equal to 2\.5[\s\S]*The hypotenuse is equal to 5[\s\S]*Do you want to export the report\\?"
        InputLines = @("5", "30", "0", "0")
    },
    @{
        Name = "arithmetic matrix solver sum"
        Expression = "arithmetic matrix solver"
        Expected = "What to do\?[\s\S]*Sum of Matrices -> 1[\s\S]*Matrix sum:[\s\S]*3\+0i[\s\S]*Export result\?"
        InputLines = @("1", "1", "2", "0", "0")
    }
)

$txtCommandBridgeTests = @(
    @{
        Name = "solve txt without predefined file"
        Expression = "solve txt"
        Expected = "The file was not yet predefined"
        InputLines = @()
        ClearPredefined = $true
    },
    @{
        Name = "predefine txt path"
        Expression = "predefine txt"
        Expected = "Drag to here the file to predefine"
        InputLines = @("C:\Temp\atc fixture.txt")
        FileExpected = "C:\Temp\atc fixture.txt"
    },
    @{
        Name = "predefine txt quoted dragged path"
        Expression = "predefine txt"
        Expected = "Drag to here the file to predefine"
        InputLines = @('"C:\Temp\atc fixture with spaces.txt"')
        FileExpected = "C:\Temp\atc fixture with spaces.txt"
    },
    @{
        Name = "open txt missing file does not launch editor"
        Expression = 'open txt("C:\Temp\atc-regression-missing-file.txt")'
        Expected = "Close the open file to continue"
        InputLines = @()
    },
    @{
        Name = "solve txt missing path abbreviation"
        Expression = "solve txt(missing)"
        Expected = "This path abbreviation not exist"
        InputLines = @()
        FixturePath = $pathNamePath
        FixtureContent = "fixture C:\Temp\atc-fixture.txt`n"
    },
    @{
        Name = "atc over cmd one expression"
        Expression = "atc over cmd"
        Expected = "ATC is ready to process data[\s\S]*Processing[\s\S]*#\d+=4[\s\S]*Processed in"
        InputLines = @("2+2", "exit")
    },
    @{
        Name = "atc over cmd invalid expression"
        Expression = "atc over cmd"
        Expected = "ATC is ready to process data[\s\S]*Processing[\s\S]*consecutive arithmetic symbols[\s\S]*Error in syntax[\s\S]*Processed in"
        InputLines = @("2++22", "exit")
    },
    @{
        Name = "atc over cmd multiple lines"
        Expression = "atc over cmd"
        Expected = "ATC is ready to process data[\s\S]*#\d+=4[\s\S]*#\d+=3[\s\S]*Processed in"
        InputLines = @("2+2", "sqrt(9)", "exit")
    },
    @{
        Name = "atc over cmd nested rational solver"
        Expression = "atc over cmd"
        Expected = "ATC is ready to process data[\s\S]*Processing[\s\S]*#\d+=-2[\s\S]*Processed in"
        InputLines = @("solver((((x-5)(x+2))/(x-5))*(((x-5)(x+2))/(x-5)))", "exit")
    }
)

$fileFolderPathTests = @(
    @{ Name = "ATC data folder exists"; Path = $AtcDataDir },
    @{ Name = "Scripts examples folder exists"; Path = $scriptsExamplesDir },
    @{ Name = "Source code folder exists"; Path = $sourceCodeDir },
    @{ Name = "Strings folder exists"; Path = $stringsDir },
    @{ Name = "To solve folder exists"; Path = $toSolveDir },
    @{ Name = "User functions folder exists"; Path = $userFunctionsDir }
)

$fileFolderFileTests = @(
    @{ Name = "user guide PDF exists"; Path = $userGuidePdfPath },
    @{ Name = "license file exists"; Path = $licensePath },
    @{ Name = "about execution file exists"; Path = $aboutExecutionPath },
    @{ Name = "script example file exists"; Path = $scriptExamplePath },
    @{ Name = "source code snapshot file exists"; Path = $sourceCodeExamplePath }
)

$variableResultManagementTests = @(
    @{
        Name = "see variables with fixture"
        Expression = "see variables"
        Expected = "Variable value[\s\S]*alpha 7 0[\s\S]*beta 8 0"
        FixturePath = $variablesPath
        FixtureContent = "alpha 7 0`nbeta 8 0`n"
    },
    @{
        Name = "renamed variables with fixture"
        Expression = "renamed variables"
        Expected = "Variable renaming[\s\S]*longname short"
        FixturePath = $renamedVarPath
        FixtureContent = "longname short`n"
    },
    @{
        Name = "see strings with fixture"
        Expression = "see strings"
        Expected = "String name[\s\S]*greeting"
        FixturePath = $stringVariablePath
        FixtureContent = "greeting`n"
    },
    @{
        Name = "see abbreviations with fixture"
        Expression = "see abbreviations"
        Expected = "Abbreviations paths[\s\S]*demo=C:\\Temp\\demo.txt"
        FixturePath = $pathNamePath
        FixtureContent = "demo=C:\Temp\demo.txt`n"
    }
)

$variableResultEmptyStateTests = @(
    @{
        Name = "see variables empty"
        Expression = "see variables"
        Expected = "No variable created"
        FixturePath = $variablesPath
        FixtureContent = ""
    },
    @{
        Name = "renamed variables empty"
        Expression = "renamed variables"
        Expected = "No variable created"
        FixturePath = $renamedVarPath
        FixtureContent = ""
    },
    @{
        Name = "see strings empty"
        Expression = "see strings"
        Expected = "No string created"
        FixturePath = $stringVariablePath
        FixtureContent = ""
    },
    @{
        Name = "see abbreviations empty"
        Expression = "see abbreviations"
        Expected = "No abbreviation created"
        FixturePath = $pathNamePath
        FixtureContent = ""
    },
    @{
        Name = "see results empty"
        Expression = "see results"
        Expected = "No calculated result"
        FixturePath = $historyPath
        FixtureContent = ""
    }
)

$variableResultMutationTests = @(
    @{
        Name = "eliminate variables clears variable files"
        Expression = "eliminate variables"
        Expected = "variables were eliminated sucessfully"
        VariablesContent = "alpha 7 0`n"
        RenamedContent = "longname short`n"
    },
    @{
        Name = "eliminate abbreviations clears path file"
        Expression = "eliminate abbreviations"
        Expected = "abbreviations were eliminated successfully"
        PathContent = "demo=C:\Temp\demo.txt`n"
    },
    @{
        Name = "see and eliminate results"
        Expression = "atc over cmd"
        Expected = "Result value[\s\S]*#0=4[\s\S]*results were eliminated successfully[\s\S]*No calculated result"
        InputLines = @("2+2", "see results", "eliminate results", "see results", "exit")
    }
)

$persistentSettingsTests = @(
    @{
        Name = "mode persisted as gradian"
        Expression = "mode"
        Expected = "Configuration of mode[\s\S]*radian -> 1[\s\S]*degree -> 2[\s\S]*gradian -> 3"
        InputLines = @("3")
        Path = $modePath
        FileExpected = "3"
    },
    @{
        Name = "numerical systems enabled"
        Expression = "numerical systems"
        Expected = "Configuration of numerical systems response[\s\S]*Enable -> 1[\s\S]*Disable -> 0"
        InputLines = @("1")
        Path = $numSystemsPath
        FileExpected = "1"
    },
    @{
        Name = "si prefixes enabled"
        Expression = "si prefixes"
        Expected = "Configuration of SI prefixes response[\s\S]*Enable -> 1[\s\S]*Disable -> 0"
        InputLines = @("1")
        Path = $siPrefixesPath
        FileExpected = "1"
    },
    @{
        Name = "verbose resolution enabled"
        Expression = "verbose resolution"
        Expected = "Configuration of verbose resolution[\s\S]*Enable -> 1[\s\S]*Disable -> 0"
        InputLines = @("1")
        Path = $verboseResolutionPath
        FileExpected = "1"
    },
    @{
        Name = "verbose resolution inline enable"
        Expression = "verbose resolution(1)"
        Expected = "Configuration of verbose resolution"
        InputLines = @()
        Path = $verboseResolutionPath
        FileExpected = "1"
    },
    @{
        Name = "actual time response enabled"
        Expression = "actual time response"
        Expected = "Configuration of actual time response[\s\S]*Enable -> 1[\s\S]*Disable -> 0"
        InputLines = @("1")
        Path = $actualTimePath
        FileExpected = "1"
    },
    @{
        Name = "dimensions persisted"
        Expression = "dimensions"
        Expected = "Dimensional configuration of the application window[\s\S]*Number of lines:[\s\S]*Number of columns:"
        InputLines = @("40", "120")
        Path = $dimensionsPath
        FileExpected = "MODE con cols=120 lines=40"
    },
    @{
        Name = "window persisted"
        Expression = "window"
        Expected = "Configuration of the position, width and height of the application window[\s\S]*X-axis value[\s\S]*Y-axis value[\s\S]*Width value[\s\S]*Height value"
        InputLines = @("10", "20", "500", "600")
        Path = $windowPath
        FileExpected = "10`n20`n500`n600"
    },
    @{
        Name = "higher precision inline enable"
        Expression = "higher precision(1)"
        Expected = "Configuration of higher precision[\s\S]*Higher Precision saved: Boost mp_float will be used after restarting ATC"
        InputLines = @()
        Path = $higherPrecisionPath
        FileExpected = "1"
    }
)

$interactiveMenuTests = @(
    @{
        Name = "mode rejects invalid option then persists degree"
        Expression = "mode"
        Expected = "Configuration of mode[\s\S]*Error, incorrect choice[\s\S]*degree -> 2"
        InputLines = @("9", "2")
        Path = $modePath
        FileExpected = "2"
    },
    @{
        Name = "numerical systems rejects invalid option then disables"
        Expression = "numerical systems"
        Expected = "Configuration of numerical systems response[\s\S]*Error, incorrect choice[\s\S]*Disable -> 0"
        InputLines = @("9", "0")
        Path = $numSystemsPath
        FileExpected = "0"
    },
    @{
        Name = "si prefixes rejects invalid option then disables"
        Expression = "si prefixes"
        Expected = "Configuration of SI prefixes response[\s\S]*Error, incorrect choice[\s\S]*Disable -> 0"
        InputLines = @("9", "0")
        Path = $siPrefixesPath
        FileExpected = "0"
    },
    @{
        Name = "verbose resolution rejects invalid option then disables"
        Expression = "verbose resolution"
        Expected = "Configuration of verbose resolution[\s\S]*Error, incorrect choice[\s\S]*Disable -> 0"
        InputLines = @("9", "0")
        Path = $verboseResolutionPath
        FileExpected = "0"
    },
    @{
        Name = "actual time response rejects invalid option then disables"
        Expression = "actual time response"
        Expected = "Configuration of actual time response[\s\S]*Error, incorrect choice[\s\S]*Disable -> 0"
        InputLines = @("9", "0")
        Path = $actualTimePath
        FileExpected = "0"
    },
    @{
        Name = "higher precision interactive enable"
        Expression = "higher precision"
        Expected = "Configuration of higher precision[\s\S]*Enable -> 1[\s\S]*Higher Precision saved: Boost mp_float will be used after restarting ATC"
        InputLines = @("1")
        Path = $higherPrecisionPath
        FileExpected = "1"
    },
    @{
        Name = "higher precision inline disable"
        Expression = "higher precision(0)"
        Expected = "Configuration of higher precision[\s\S]*Higher Precision saved: double will be used after restarting ATC"
        InputLines = @()
        Path = $higherPrecisionPath
        FileExpected = "0"
    },
    @{
        Name = "higher precision rejects invalid option then enables"
        Expression = "higher precision"
        Expected = "Configuration of higher precision[\s\S]*Error, incorrect choice[\s\S]*Enable -> 1[\s\S]*Higher Precision saved: Boost mp_float will be used after restarting ATC"
        InputLines = @("9", "1")
        Path = $higherPrecisionPath
        FileExpected = "1"
    }
)

$appEnvironmentTests = @(
    @{
        Name = "about screen exits after Enter"
        Expression = "about"
        Expected = "PRESS THE BUTTON `"Enter`" TO ACCESS THE ENVIRONMENT-RESOLUTION CALCULATIONS"
        InputLines = @("")
    },
    @{
        Name = "auto adjust window persists dimensions"
        Expression = "auto adjust window"
        Expected = "^$"
        Path = $dimensionsPath
        FileRegex = "^MODE con cols=\d+ lines=2000$"
    },
    @{
        Name = "enable ATC intro writes startup flag"
        Expression = "enable atc intro"
        Expected = "Restart the application to apply changes"
        Path = $onStartPath
        FileExpected = "enableatcintro"
    },
    @{
        Name = "disable ATC intro creates disabled marker"
        Expression = "disable atc intro"
        Expected = "Restart the application to apply changes"
        Path = $aboutDisabledPath
        FileExpected = ""
    },
    @{
        Name = "clean history removes previous entries"
        Expression = "clean history"
        Expected = "history was cleaned sucessfully"
        Path = $historyPath
        InitialContent = "previous history`n"
        FileExpected = "==> The history was cleaned sucessfully. <==`n`n>clean history"
    },
    @{
        Name = "clean command exits successfully"
        Expression = "clean"
        Expected = "^$"
    },
    @{
        Name = "exit command exits successfully"
        Expression = "exit"
        Expected = "^$"
        Path = $exitPath
        RemoveBefore = $true
        FileExpected = ""
    }
)

$mpFloatTests = @(
    @{ Name = "mp_float pi 50dp"; Expression = "dp50dppi"; Expected = "^#\d+=3\.14159265358979323846264338327950288419716939937511$" },
    @{ Name = "mp_float e 50dp"; Expression = "dp50dpe"; Expected = "^#\d+=2\.71828182845904523536028747135266249775724709369996$" },
    @{ Name = "mp_float fixed zero padding"; Expression = "dp50dp1+1"; Expected = "^#\d+=2\.00000000000000000000000000000000000000000000000000$" },
    @{ Name = "mp_float sin identity"; Expression = "sin(pi/2)"; Expected = "^#\d+=1$" }
)

$verboseResolutionBehaviorTests = @(
    @{
        Name = "verbose output explains arithmetic expression"
        Expression = "2+3*4"
        Expected = "initialProcessor[\s\S]*Expression: 2\+3\*4[\s\S]*arithSolver[\s\S]*Simplified expression by arithSolver[\s\S]*#\d+=(14|1\.4E1)"
        FixturePath = $verboseResolutionPath
        FixtureContent = "1"
    }
)

$results = New-Object System.Collections.Generic.List[object]

try {
    Set-Content -Path $aboutDisabledPath -Value "1" -NoNewline
    Set-Content -Path $modePath -Value "1" -NoNewline
    Set-Content -Path $numSystemsPath -Value "0" -NoNewline
    Set-Content -Path $siPrefixesPath -Value "0" -NoNewline
    Set-Content -Path $verboseResolutionPath -Value "0" -NoNewline
    Set-Content -Path $actualTimePath -Value "0" -NoNewline

    if ($Mode -eq "All" -or $Mode -eq "Double") {
        Set-HigherPrecision "0"
        foreach ($test in $doubleTests) {
            $results.Add((Test-AtcExpression "double: $($test.Name)" $test.Expression $test.Expected))
        }
        foreach ($test in $precisionModeTests) {
            Set-HigherPrecision "0"
            $results.Add((Test-AtcExpressionAndFileValue "precision mode: $($test.Name)" $test.Expression $test.Expected $higherPrecisionPath $test.FileExpected))
        }
        foreach ($test in $guideFunctionTests) {
            $results.Add((Test-AtcExpression "guide function: $($test.Name)" $test.Expression $test.Expected))
        }
        foreach ($test in $implicitMultiplicationTests) {
            $results.Add((Test-AtcExpression "implicit multiplication: $($test.Name)" $test.Expression $test.Expected))
        }
        foreach ($test in $parserSyntaxGuardTests) {
            $results.Add((Test-AtcExpression "parser syntax guard: $($test.Name)" $test.Expression $test.Expected))
        }
        foreach ($test in $matrixVariableTests) {
            $results.Add((Test-AtcExpressionWithVariables "guide function: $($test.Name)" $test.Expression $test.Expected $matrixVariableContent))
        }
        foreach ($test in $matrixGuideFunctionTests) {
            $results.Add((Test-AtcExpressionWithVariables "guide function: $($test.Name)" $test.Expression $test.Expected $matrixGuideFunctionContent))
        }
        foreach ($test in $matrixArithmeticTests) {
            $results.Add((Test-AtcExpressionWithVariables "matrix arithmetic: $($test.Name)" $test.Expression $test.Expected $matrixArithmeticContent))
        }
        foreach ($test in $matrixPairTests) {
            $results.Add((Test-AtcExpressionWithVariables "matrix arithmetic: $($test.Name)" $test.Expression $test.Expected $matrixPairContent))
        }
        foreach ($test in $rectangularMatrixTests) {
            $results.Add((Test-AtcExpressionWithVariables "matrix arithmetic: $($test.Name)" $test.Expression $test.Expected $rectangularMatrixContent))
        }
        foreach ($test in $matrixScalarTests) {
            $results.Add((Test-AtcExpressionWithVariables "matrix arithmetic: $($test.Name)" $test.Expression $test.Expected $matrixScalarContent))
        }
        foreach ($test in $complexMatrixTests) {
            $results.Add((Test-AtcExpressionWithVariables "matrix arithmetic: $($test.Name)" $test.Expression $test.Expected $complexMatrixContent))
        }
        foreach ($test in $matrixIndexSessionTests) {
            $results.Add((Test-AtcExpressionWithVariablesFile "matrix indexing: $($test.Name)" $test.Expression $test.Expected $matrixIndexSessionContent $test.VariablesExpected $test.InputLines))
        }
        foreach ($test in $createMatrixTests) {
            $results.Add((Test-AtcExpressionWithVariablesFile "matrix creation: $($test.Name)" $test.Expression $test.Expected $test.VariablesContent $test.VariablesExpected))
        }
        foreach ($test in $relaxedVariableNameTests) {
            $results.Add((Test-AtcExpressionWithVariables "variable names: $($test.Name)" $test.Expression $test.Expected $relaxedVariableNameContent))
        }
        foreach ($test in $reservedPrefixVariableTests) {
            $results.Add((Test-AtcExpressionWithVariables "variable names: $($test.Name)" $test.Expression $test.Expected $reservedPrefixVariableContent))
        }
        foreach ($test in $uppercaseNegativeVariableTests) {
            $results.Add((Test-AtcExpressionWithVariables "variable names: $($test.Name)" $test.Expression $test.Expected $uppercaseNegativeVariableContent))
        }
        foreach ($test in $implicitVariableTests) {
            $results.Add((Test-AtcExpressionWithVariables "implicit multiplication: $($test.Name)" $test.Expression $test.Expected $implicitVariableContent))
        }
        foreach ($test in $implicitCompositeVariableTests) {
            $results.Add((Test-AtcExpressionWithVariables "implicit multiplication: $($test.Name)" $test.Expression $test.Expected $implicitCompositeVariableContent))
        }
        foreach ($test in $longCompositeVariableTests) {
            $results.Add((Test-AtcExpressionWithVariables "variable names: $($test.Name)" $test.Expression $test.Expected $longCompositeVariableContent))
        }
        foreach ($test in $guideExportTests) {
            $results.Add((Test-AtcExportExpression "guide command: $($test.Name)" $test.Expression $test.ConsoleExpected $test.FileExpected))
        }
        foreach ($test in $exportDeclineTests) {
            $results.Add((Test-AtcDeclineExportExpression "export prompt: $($test.Name)" $test.Expression $test.ConsoleExpected))
        }
        foreach ($test in $asciiSortingTests) {
            $results.Add((Test-AtcExpression "sorting: $($test.Name)" $test.Expression $test.Expected $test.InputLines))
        }
        foreach ($test in $polynomialSimplifyTests) {
            $results.Add((Test-AtcExpression "polynomial simplify: $($test.Name)" $test.Expression $test.Expected @("0")))
        }
        foreach ($test in $equationSolverTests) {
            $results.Add((Test-AtcExpression "equation solver: $($test.Name)" $test.Expression $test.Expected))
        }
        foreach ($test in $solverFunctionTests) {
            Set-Content -Path $modePath -Value $test.ModeValue -NoNewline
            Set-Content -Path $variablesPath -Value "x 1000 0" -NoNewline
            $results.Add((Test-AtcExpression "solver function: $($test.Name)" $test.Expression $test.Expected))
            Set-Content -Path $modePath -Value "1" -NoNewline
        }
        foreach ($test in $equationExportTests) {
            $results.Add((Test-AtcExportExpression "equation solver: $($test.Name)" $test.Expression $test.ConsoleExpected $test.FileExpected))
        }
        foreach ($test in $equationFastPathTests) {
            $results.Add((Test-AtcExpression "equation fast path: $($test.Name)" $test.Expression $test.Expected @("0")))
        }
        foreach ($test in $functionStudyTests) {
            $results.Add((Test-AtcExpression "function study: $($test.Name)" $test.Expression $test.Expected))
        }
        foreach ($test in $graphTests) {
            if ($test.ContainsKey("GraphContent")) {
                Set-Content -Path $graphPath -Value $test.GraphContent -NoNewline
            }
            if ($test.ContainsKey("Environment")) {
                $results.Add((Test-AtcExpressionWithEnvironment "graph: $($test.Name)" $test.Expression $test.Expected $test.Environment $test.InputLines))
            }
            else {
                $results.Add((Test-AtcExpression "graph: $($test.Name)" $test.Expression $test.Expected $test.InputLines))
            }
        }
        foreach ($test in $graphSettingsMutationTests) {
            $results.Add((Test-AtcExpressionAndFileValue "graph: $($test.Name)" $test.Expression $test.Expected $graphPath $test.FileExpected $test.InputLines))
        }
        foreach ($test in $dateCommandTests) {
            $inputLines = @()
            if ($test.ContainsKey("InputLines")) {
                $inputLines = $test.InputLines
            }
            $results.Add((Test-AtcExpression "date/time command: $($test.Name)" $test.Expression $test.Expected $inputLines))
        }
        foreach ($test in $actualTimeResponseTests) {
            $results.Add((Test-AtcExpressionAndFileValue "date/time command: $($test.Name)" $test.Expression $test.Expected $actualTimePath $test.FileExpected $test.InputLines))
        }
        foreach ($test in $deepInteractiveModuleTests) {
            $results.Add((Test-AtcExpression "deep interactive module: $($test.Name)" $test.Expression $test.Expected $test.InputLines))
        }
        foreach ($test in $txtCommandBridgeTests) {
            if ($test.ContainsKey("ClearPredefined") -and $test.ClearPredefined) {
                Remove-Item -Path $predefinedTxtPath -Force -ErrorAction SilentlyContinue
            }
            if ($test.ContainsKey("FixturePath")) {
                Set-Content -Path $test.FixturePath -Value $test.FixtureContent -NoNewline
            }
            if ($test.ContainsKey("FileExpected")) {
                $results.Add((Test-AtcExpressionAndFileValue "txt/command bridge: $($test.Name)" $test.Expression $test.Expected $predefinedTxtPath $test.FileExpected $test.InputLines))
            }
            else {
                $results.Add((Test-AtcExpression "txt/command bridge: $($test.Name)" $test.Expression $test.Expected $test.InputLines))
            }
        }
        $results.Add((Test-MockedExternalCommand "txt/command bridge: atc from cmd mocked PATH update" "atc from cmd" "You can now run cmd\.exe" "atcFromCmd\|/C"))
        $results.Add((Test-MockedExternalCommand "txt/command bridge: to solve mocked folder open" "to solve" "^$" "toSolve\|/C ""explorer"))
        $results.Add((Test-MockedExternalCommand "txt/command bridge: enable txt detector removes disable flag" "enable txt detector" "^$" "enableTxtDetector\|.*disable_txt_detector\.txt" { Set-Content -Path $disableTxtDetectorPath -Value "1" -NoNewline } { param($result) if (Test-Path $disableTxtDetectorPath) { $result.Passed = $false; $result.Output = ($result.Output + "`ndisable_txt_detector still exists").Trim(); $result.Expected = $result.Expected + " and disable flag removed" } }))
        $results.Add((Test-TxtProcessingFlow))
        $results.Add((Test-AutoSolveTxtWatcherFlow))
        $results.Add((Test-EliminateStringsMock))
        foreach ($test in $fileFolderPathTests) {
            $results.Add((Test-DirectoryExists "file/folder command: $($test.Name)" $test.Path))
        }
        foreach ($test in $fileFolderFileTests) {
            $results.Add((Test-FileExists "file/folder command: $($test.Name)" $test.Path))
        }
        foreach ($test in $variableResultManagementTests) {
            $results.Add((Test-AtcExpressionWithFixtureFile "variable/result management: $($test.Name)" $test.Expression $test.Expected $test.FixturePath $test.FixtureContent))
        }
        foreach ($test in $variableResultEmptyStateTests) {
            $results.Add((Test-AtcExpressionWithFixtureFile "variable/result management: $($test.Name)" $test.Expression $test.Expected $test.FixturePath $test.FixtureContent))
        }
        foreach ($test in $variableResultMutationTests) {
            if ($test.Name -eq "eliminate variables clears variable files") {
                Set-Content -Path $variablesPath -Value $test.VariablesContent -NoNewline
                Set-Content -Path $renamedVarPath -Value $test.RenamedContent -NoNewline
                $expectedFiles = @{}
                $expectedFiles[$variablesPath] = ""
                $expectedFiles[$renamedVarPath] = ""
                $results.Add((Test-AtcExpressionAndFileValues "variable/result management: $($test.Name)" $test.Expression $test.Expected $expectedFiles))
            }
            elseif ($test.Name -eq "eliminate abbreviations clears path file") {
                Set-Content -Path $pathNamePath -Value $test.PathContent -NoNewline
                $results.Add((Test-AtcExpressionAndFileValue "variable/result management: $($test.Name)" $test.Expression $test.Expected $pathNamePath ""))
            }
            else {
                $results.Add((Test-AtcExpression "variable/result management: $($test.Name)" $test.Expression $test.Expected $test.InputLines))
            }
        }
        foreach ($test in $persistentSettingsTests) {
            $results.Add((Test-AtcExpressionAndFileValue "persistent settings: $($test.Name)" $test.Expression $test.Expected $test.Path $test.FileExpected $test.InputLines))
        }
        foreach ($test in $interactiveMenuTests) {
            $results.Add((Test-AtcExpressionAndFileValue "interactive menu: $($test.Name)" $test.Expression $test.Expected $test.Path $test.FileExpected $test.InputLines))
        }
        foreach ($test in $verboseResolutionBehaviorTests) {
            $results.Add((Test-AtcExpressionWithFixtureFile "verbose resolution: $($test.Name)" $test.Expression $test.Expected $test.FixturePath $test.FixtureContent))
        }
        Set-Content -Path $verboseResolutionPath -Value "0" -NoNewline
        Set-Content -Path $modePath -Value "3" -NoNewline
        Set-Content -Path $numSystemsPath -Value "1" -NoNewline
        Set-Content -Path $siPrefixesPath -Value "1" -NoNewline
        Set-Content -Path $actualTimePath -Value "1" -NoNewline
        Set-Content -Path $higherPrecisionPath -Value "1" -NoNewline
        Set-Content -Path $verboseResolutionPath -Value "1" -NoNewline
        Set-Content -Path $colorsPath -Value "color 17" -NoNewline
        Set-Content -Path $windowPath -Value "10`n20`n500`n600`n" -NoNewline
        Set-Content -Path $dimensionsPath -Value "MODE con cols=120 lines=40" -NoNewline
        $results.Add((Test-AtcExpression "persistent settings: current settings reads fixture" "current settings" "Mode-+> Radian Degree GRADIAN[\s\S]*Numerical Systems Response-+> ENABLED Disabled[\s\S]*SI Prefixes Response-+> ENABLED Disabled[\s\S]*Actual Time Response-+> ENABLED Disabled[\s\S]*Higher Precision-+> ENABLED Disabled[\s\S]*Verbose Resolution-+> ENABLED Disabled[\s\S]*Colors-+> Text: WHITE - Background: BLUE[\s\S]*Window-+> x: 10 - y: 20 - Width: 500 - Height: 600[\s\S]*Dimensions-+> Lines: 40 - Columns: 120"))
        Set-Content -Path $verboseResolutionPath -Value "0" -NoNewline
        foreach ($test in $appEnvironmentTests) {
            if ($test.ContainsKey("RemoveBefore") -and $test.RemoveBefore) {
                Remove-Item -Path $test.Path -Force -ErrorAction SilentlyContinue
            }
            if ($test.ContainsKey("InitialContent")) {
                Set-Content -Path $test.Path -Value $test.InitialContent -NoNewline
            }
            $inputLines = if ($test.ContainsKey("InputLines")) { $test.InputLines } else { @() }
            if ($test.ContainsKey("FileRegex")) {
                $results.Add((Test-AtcExpressionAndFileRegex "app environment: $($test.Name)" $test.Expression $test.Expected $test.Path $test.FileRegex $inputLines))
            }
            elseif ($test.ContainsKey("Path")) {
                $results.Add((Test-AtcExpressionAndFileValue "app environment: $($test.Name)" $test.Expression $test.Expected $test.Path $test.FileExpected $inputLines))
            }
            else {
                $results.Add((Test-AtcExpression "app environment: $($test.Name)" $test.Expression $test.Expected $inputLines))
            }
        }
    }

    if ($Mode -eq "All" -or $Mode -eq "MpFloat") {
        Set-Content -Path $modePath -Value "1" -NoNewline
        Set-Content -Path $numSystemsPath -Value "0" -NoNewline
        Set-Content -Path $siPrefixesPath -Value "0" -NoNewline
        Set-Content -Path $actualTimePath -Value "0" -NoNewline
        Set-HigherPrecision "1"
        foreach ($test in $mpFloatTests) {
            $results.Add((Test-AtcExpression "mp_float: $($test.Name)" $test.Expression $test.Expected))
        }
    }

    if ($Mode -eq "All" -or $Mode -eq "Persistence") {
        Set-Content -Path $modePath -Value "1" -NoNewline
        Set-Content -Path $numSystemsPath -Value "0" -NoNewline
        Set-Content -Path $siPrefixesPath -Value "0" -NoNewline
        Set-Content -Path $actualTimePath -Value "0" -NoNewline
        Set-HigherPrecision "0"
        $results.Add((Test-AtcExpression "persistence: enable higher precision" "higherprecision(1)" "Boost mp_float"))
        $results.Add((Test-FileValue "persistence: file saved as mp_float" $higherPrecisionPath "1"))
        $results.Add((Test-AtcExpression "persistence: restart reads mp_float" "dp50dppi" "^#\d+=3\.14159265358979323846264338327950288419716939937511$"))
        $results.Add((Test-AtcExpression "persistence: disable higher precision" "higherprecision(0)" "double"))
        $results.Add((Test-FileValue "persistence: file saved as double" $higherPrecisionPath "0"))
    }
}
finally {
    if ($hadHigherPrecision) {
        Set-Content -Path $higherPrecisionPath -Value $originalHigherPrecision -NoNewline
    }
    else {
        Remove-Item -Path $higherPrecisionPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadAboutDisabled) {
        Set-Content -Path $aboutDisabledPath -Value $originalAboutDisabled -NoNewline
    }
    else {
        Remove-Item -Path $aboutDisabledPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadVariables) {
        Set-Content -Path $variablesPath -Value $originalVariables -NoNewline
    }
    else {
        Remove-Item -Path $variablesPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadMode) {
        Set-Content -Path $modePath -Value $originalMode -NoNewline
    }
    else {
        Remove-Item -Path $modePath -Force -ErrorAction SilentlyContinue
    }

    if ($hadGraph) {
        Set-Content -Path $graphPath -Value $originalGraph -NoNewline
    }
    else {
        Remove-Item -Path $graphPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadActualTime) {
        Set-Content -Path $actualTimePath -Value $originalActualTime -NoNewline
    }
    else {
        Remove-Item -Path $actualTimePath -Force -ErrorAction SilentlyContinue
    }

    if ($hadPredefinedTxt) {
        Set-Content -Path $predefinedTxtPath -Value $originalPredefinedTxt -NoNewline
    }
    else {
        Remove-Item -Path $predefinedTxtPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadRenamedVar) {
        Set-Content -Path $renamedVarPath -Value $originalRenamedVar -NoNewline
    }
    else {
        Remove-Item -Path $renamedVarPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadStringVariable) {
        Set-Content -Path $stringVariablePath -Value $originalStringVariable -NoNewline
    }
    else {
        Remove-Item -Path $stringVariablePath -Force -ErrorAction SilentlyContinue
    }

    if ($hadPathName) {
        Set-Content -Path $pathNamePath -Value $originalPathName -NoNewline
    }
    else {
        Remove-Item -Path $pathNamePath -Force -ErrorAction SilentlyContinue
    }

    if ($hadNumSystems) {
        Set-Content -Path $numSystemsPath -Value $originalNumSystems -NoNewline
    }
    else {
        Remove-Item -Path $numSystemsPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadSiPrefixes) {
        Set-Content -Path $siPrefixesPath -Value $originalSiPrefixes -NoNewline
    }
    else {
        Remove-Item -Path $siPrefixesPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadVerboseResolution) {
        Set-Content -Path $verboseResolutionPath -Value $originalVerboseResolution -NoNewline
    }
    else {
        Remove-Item -Path $verboseResolutionPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadColors) {
        Set-Content -Path $colorsPath -Value $originalColors -NoNewline
    }
    else {
        Remove-Item -Path $colorsPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadDimensions) {
        Set-Content -Path $dimensionsPath -Value $originalDimensions -NoNewline
    }
    else {
        Remove-Item -Path $dimensionsPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadWindow) {
        Set-Content -Path $windowPath -Value $originalWindow -NoNewline
    }
    else {
        Remove-Item -Path $windowPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadOnStart) {
        Set-Content -Path $onStartPath -Value $originalOnStart -NoNewline
    }
    else {
        Remove-Item -Path $onStartPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadHistory) {
        Set-Content -Path $historyPath -Value $originalHistory -NoNewline
    }
    else {
        Remove-Item -Path $historyPath -Force -ErrorAction SilentlyContinue
    }

    if ($hadExit) {
        Set-Content -Path $exitPath -Value $originalExit -NoNewline
    }
    else {
        Remove-Item -Path $exitPath -Force -ErrorAction SilentlyContinue
    }
    if ($hadDisableTxtDetector) {
        Set-Content -Path $disableTxtDetectorPath -Value $originalDisableTxtDetector -NoNewline
    }
    else {
        Remove-Item -Path $disableTxtDetectorPath -Force -ErrorAction SilentlyContinue
    }
}

$failed = @($results | Where-Object { -not $_.Passed })

foreach ($result in $results) {
    $status = if ($result.Passed) { "PASS" } else { "FAIL" }
    Write-Host ("[{0}] {1} :: {2}" -f $status, $result.Name, $result.Expression)
    if (-not $result.Passed) {
        Write-Host ("       expected: {0}" -f $result.Expected)
        Write-Host ("       exitcode: {0}" -f $result.ExitCode)
        Write-Host ("       output:   {0}" -f $result.Output)
    }
}

Write-Host ""
Write-Host ("Summary: {0} passed, {1} failed" -f ($results.Count - $failed.Count), $failed.Count)

if ($failed.Count -gt 0) {
    exit 1
}

exit 0
