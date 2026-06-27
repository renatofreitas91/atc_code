param(
    [string]$AtcExe = (Join-Path $PSScriptRoot "..\x64\Release\atc.exe"),
    [int]$TimeoutSeconds = 8
)

$ErrorActionPreference = "Stop"

$AtcExe = [System.IO.Path]::GetFullPath($AtcExe)
$repoRoot = [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot ".."))
$sourceDir = Join-Path $repoRoot "Advanced Trigonometry Calculator"
$commandsPath = Join-Path $sourceDir "commands.cpp"
$settingsPath = Join-Path $sourceDir "settings.cpp"
$dataCorePath = Join-Path $sourceDir "data_processing_core.cpp"
$graphPath = Join-Path $sourceDir "graph.cpp"

if (-not (Test-Path $AtcExe)) {
    throw "ATC executable not found: $AtcExe"
}

$results = New-Object System.Collections.Generic.List[object]

function Add-Result([string]$Name, [bool]$Passed, [string]$Evidence, [string]$Expected) {
    $script:results.Add([pscustomobject]@{
        Passed = $Passed
        Name = $Name
        Evidence = $Evidence
        Expected = $Expected
    })
}

function Test-SourcePattern([string]$Name, [string]$Path, [string]$Pattern) {
    $content = Get-Content -Raw -Path $Path
    Add-Result $Name ($content -match $Pattern) $Path $Pattern
}

function Test-SourcePatterns([string]$Name, [string]$Path, [string[]]$Patterns) {
    $content = Get-Content -Raw -Path $Path
    $missing = @($Patterns | Where-Object { $content -notmatch $_ })
    Add-Result $Name ($missing.Count -eq 0) $Path (($missing -join " | "))
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

    [pscustomobject]@{
        ExitCode = $process.ExitCode
        Output = (($process.StandardOutput.ReadToEnd() + $process.StandardError.ReadToEnd()) -replace "`r", "").Trim()
    }
}

function Test-AtcSmoke([string]$Name, [string]$Expression, [string]$ExpectedRegex, [string[]]$InputLines = @()) {
    try {
        $result = Invoke-AtcCommand $Expression $InputLines
        Add-Result $Name (($result.ExitCode -eq 0) -and ($result.Output -match $ExpectedRegex)) $result.Output $ExpectedRegex
    }
    catch {
        Add-Result $Name $false $_.Exception.Message $ExpectedRegex
    }
}

# Source-only checks for commands that open windows, browsers, elevated shells,
# reset settings, or launch other ATC processes.
Test-SourcePatterns "app environment command branches" $commandsPath @(
    'isCommand\(arithTrig, "autoadjustwindow"\)',
    'isCommand\(arithTrig, "about"\)',
    'isCommand\(arithTrig, "history"\)',
    'isCommand\(arithTrig, "userguide"\)',
    'isCommand\(arithTrig, "runatc"\)',
    'isCommand\(arithTrig, "restartatc"\)'
)
Test-SourcePatterns "updates and external links branches" $commandsPath @(
    'isCommand\(arithTrig, "checkforupdates"\)',
    'isCommand\(arithTrig, "updateportable"\)',
    'isCommand\(arithTrig, "update"\)',
    'isCommand\(arithTrig, "updatex64"\)',
    'isCommand\(arithTrig, "donate"\)',
    'isCommand\(arithTrig, "atcfacebook"\)',
    'isCommand\(arithTrig, "atcsourceforge"\)'
)
Test-SourcePatterns "reset command branches" $commandsPath @(
    'isCommand\(arithTrig, "resetall"\)',
    'isCommand\(arithTrig, "resetallnow"\)',
    'isCommand\(arithTrig, "resetsettings"\)',
    'isCommand\(arithTrig, "resetsettingsnow"\)'
)
Test-SourcePattern "colors uses console keys and persists colors.txt" $settingsPath "void colors\(\)[\s\S]*_getch\(\)[\s\S]*colors\.txt"
Test-SourcePatterns "folder helper command branches" $commandsPath @(
    'isCommand\(arithTrig, "atcfolder"\)',
    'isCommand\(arithTrig, "sourcecode"\)',
    'isCommand\(arithTrig, "scriptsexamples"\)',
    'isCommand\(arithTrig, "strings"\)',
    'isCommand\(arithTrig, "userfunctions"\)',
    'isCommand\(arithTrig, "tosolve"\)',
    'isCommand\(arithTrig, "autosolvetxt"\)'
)
Test-SourcePattern "open txt guarded in main loop" (Join-Path $sourceDir "main.cpp") "isContained\(""open txt"", arith\)"
Test-SourcePattern "eliminate strings command exists" $commandsPath "isCommand\(arithTrig, ""eliminatestrings""\)[\s\S]*stringVariable\.txt[\s\S]*rmdir /Q /S Strings[\s\S]*mkdir Strings"
Test-SourcePattern "eliminate strings has no duplicate fclose" $commandsPath "(?s)isCommand\(arithTrig, ""eliminatestrings""\)(?:(?!fclose\(open\);\s*fclose\(open\);).)*ShellExecute"
Test-SourcePatterns "txt detector and command bridge branches" $commandsPath @(
    'isCommand\(arithTrig, "enabletxtdetector"\)',
    'isCommand\(arithTrig, "atcfromcmd"\)',
    'isCommand\(arithTrig, "atcovercmd"\)',
    'isCommand\(arithTrig, "autosolvetxt"\)'
)
Test-SourcePatterns "new ATC tab command branches" $commandsPath @(
    'isCommand\(arithTrig, "newatctab"\)',
    'isCommand\(arithTrig, "newatcinstance"\)',
    'isCommand\(arithTrig, "newtab"\)',
    'isCommand\(arithTrig, "newinstance"\)'
)
Test-SourcePatterns "new ATC instance opens Windows Terminal or cmd fallback" $dataCorePath @(
    'SearchPathA\(NULL, "wt\.exe"',
    'new-tab --title',
    'C:\\\\WINDOWS\\\\system32\\\\cmd\.exe'
)
Test-SourcePatterns "Windows 11 disables intro by default" $dataCorePath @(
    'RtlGetVersion',
    'dwBuildNumber >= 22000',
    'shouldDisableATCIntroByDefault\(\)[\s\S]*IsWindows11OrGreater\(\)'
)
Test-SourcePattern "startup skips intro on Windows 11 unless legacy host allows it" (Join-Path $sourceDir "main.cpp") 'ab == NULL && !shouldDisableATCIntroByDefault\(\)[\s\S]*continu = about\(\)'
Test-SourcePattern "startup uses Windows 11 safe layout after skipped intro" (Join-Path $sourceDir "main.cpp") 'continu = 1;[\s\S]*applyStartupConsoleLayoutSafe\(\);'
Test-SourcePatterns "Windows 11 startup layout avoids Win32 window control in Windows Terminal" $dataCorePath @(
    'void applyStartupConsoleLayoutSafe\(\)',
    'isWindowsTerminalHost\(\) \|\| shouldDisableATCIntroByDefault\(\)',
    'maximizeConsoleWindowSafe\(\);[\s\S]*repaintConsoleViewportSafe\(\);[\s\S]*return;',
    'void maximizeConsoleWindowSafe\(\)[\s\S]*if \(isWindowsTerminalHost\(\)\) \{[\s\S]*return;',
    'ShowWindow\(hwnd, SW_SHOWNORMAL\);[\s\S]*MoveWindow\(hwnd, 0, 0, targetWidth, targetHeight, TRUE\);',
    'applySettings\(Window\);[\s\S]*applySettings\(Dimensions\);'
)
Test-SourcePatterns "Windows Terminal blocks legacy window fallbacks in settings" $settingsPath @(
    'shouldUseLegacyConsoleWindowManagement\(\) && !applyConsoleWindowSafe\(x, y, width, height\)',
    'shouldUseLegacyConsoleWindowManagement\(\) && !applyConsoleWindowSafe\(\(int\)x, \(int\)y, \(int\)width, \(int\)height\)',
    'shouldUseLegacyConsoleWindowManagement\(\) && !applyConsoleWindowSafe\(0, 0, 760, 760\)',
    'if \(shouldUseLegacyConsoleWindowManagement\(\)\) \{[\s\S]*ShowWindow\(b, SW_SHOWMAXIMIZED\);'
)
Test-SourcePatterns "Windows console to ANSI color mapping preserves aqua text" $dataCorePath @(
    'ansiOrder\[8\] = \{ 0, 4, 2, 6, 1, 5, 3, 7 \}',
    'return \(background \? 40 : 30\) \+ ansiColor',
    'return \(background \? 100 : 90\) \+ ansiColor'
)
Test-SourcePatterns "txt detector startup processing" $dataCorePath @(
    'disable_txt_detector\.txt',
    'To solve',
    'ATC has detected %d file\(s\)'
)
Test-SourcePatterns "interactive calculation module branches" $commandsPath @(
    'isCommand\(arithTrig, "trianglesrectanglessolver"\)',
    'isCommand\(arithTrig, "arithmeticmatrixsolver"\)',
    'isCommand\(arithTrig, "financialcalculations"\)',
    'isCommand\(arithTrig, "geometrycalculations"\)',
    'isCommand\(arithTrig, "statisticscalculations"\)',
    'isCommand\(arithTrig, "physicscalculations"\)',
    'isCommand\(arithTrig, "unitconversions"\)',
    'isCommand\(arithTrig, "microeconomicscalculations"\)'
)
Test-SourcePattern "graph interactive key-buffer logic" $graphPath "GetStdHandle\(STD_INPUT_HANDLE\)[\s\S]*ReadConsoleInput[\s\S]*KEY_EVENT"
Test-SourcePatterns "long-running time command branches" $commandsPath @(
    'isCommand\(arithTrig, "stopwatch"\)',
    'isCommand\(arithTrig, "runstopwatch"\)',
    'isCommand\(arithTrig, "timer"\)',
    'isCommand\(arithTrig, "runtimer"\)',
    'isCommand\(arithTrig, "bigtimer"\)',
    'isCommand\(arithTrig, "runbigtimer"\)',
    'isCommand\(arithTrig, "clock"\)',
    'isCommand\(arithTrig, "runclock"\)',
    'isCommand\(arithTrig, "bigclock"\)',
    'isCommand\(arithTrig, "runbigclock"\)'
)

# Short smoke checks for long-running commands that can terminate immediately.
Test-AtcSmoke "stopwatch one-mark smoke" "stopwatch(1)" "Press ""Enter"" button to mark time[\s\S]*t1=" @("")

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
