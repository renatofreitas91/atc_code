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
$autoCompletePath = Join-Path $sourceDir "auto_complete.cpp"

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
Test-SourcePatterns "app environment commands are exposed by autocomplete" (Join-Path $sourceDir "auto_complete.cpp") @(
    'auto adjust window',
    'about',
    'history',
    'user guide',
    'run atc',
    'restart atc'
)
Test-SourcePatterns "autocomplete exposes mathematical functions and aliases" $autoCompletePath @(
    'solve equation\(\)',
    'solveequation\(\)',
    'solver\(\)',
    'simplify polynomial\(\)',
    'function study\(\)',
    'roots to polynomial\(\)',
    'cos\(\)',
    'acos\(\)',
    'sin\(\)',
    'asin\(\)',
    'tan\(\)',
    'atan\(\)',
    'sec\(\)',
    'asec\(\)',
    'cosec\(\)',
    'acosec\(\)',
    'cotan\(\)',
    'acotan\(\)',
    'cosh\(\)',
    'acosh\(\)',
    'sinh\(\)',
    'asinh\(\)',
    'tanh\(\)',
    'atanh\(\)',
    'sech\(\)',
    'asech\(\)',
    'cosech\(\)',
    'acosech\(\)',
    'cotanh\(\)',
    'acotanh\(\)',
    'degsin\(\)',
    'radsin\(\)',
    'gonsin\(\)',
    'sinc\(\)',
    'log\(\)',
    'ln\(\)',
    'logb b\(\)',
    'rtD D\(\)',
    'sqrt\(\)',
    'cbrt\(\)',
    'afact\(\)',
    'abs\(\)',
    'det\(\)',
    'gerror\(\)',
    'gerrorinv\(\)',
    'gerrorc\(\)',
    'gerrorcinv\(\)',
    'qfunc\(\)',
    'qfuncinv\(\)',
    'min\(\)',
    'max\(\)',
    'avg\(\)',
    'linsnum\(\)',
    'colsnum\(\)',
    'getlins\(\)',
    'getcols\(\)'
)
Test-SourcePatterns "autocomplete exposes scripting and dynamic user functions" $autoCompletePath @(
    'strlen\(\)',
    'countoccurrences\(\)',
    'iscontained\(\)',
    'iscontainedbyindex\(\)',
    'iscontainedvariable\(\)',
    'isequal\(\)',
    'isvariable\(\)',
    'istowrite\(\)',
    'atc\(\)',
    'calc\(\)',
    'for\(\)',
    'appendUserFunctionSuggestions',
    'User functions\\\\\*\.txt',
    'atc_'
)
Test-SourcePatterns "autocomplete exposes application commands and command aliases" $autoCompletePath @(
    'maxprec',
    'maxprecision',
    'higher precision',
    'higherprecision\(\)',
    'mode',
    'numerical systems',
    'si prefixes',
    'verbose resolution',
    'current settings',
    'new tab',
    'new instance',
    'new atc tab',
    'new atc instance',
    'predefine txt',
    'solve txt',
    'auto solve txt',
    'open txt\(\)',
    'opentxt\(\)',
    'atc from cmd',
    'atc over cmd',
    'day of week\(\)',
    'stopwatch\(\)',
    'timer\(\)',
    'calendar\(\)',
    'time difference calculations'
)
Test-SourcePatterns "autocomplete line editor supports history navigation" $autoCompletePath @(
    'loadInputHistory',
    'history\.txt',
    "line\[0\] == '>'",
    'specialKey == 72',
    'specialKey == 80',
    'historyIndex',
    'draftLine',
    'redrawConsoleInputLine\(editorLine, cursor, previousLength\)'
)
Test-SourcePatterns "autocomplete supports cycling through ambiguous matches" $autoCompletePath @(
    'findCompletionMatches',
    'replaceCompletionToken',
    'compareCompletionCandidate',
    'left\.length\(\) < right\.length\(\)',
    'std::sort\(matches\.begin\(\), matches\.end\(\), compareCompletionCandidate\)',
    'std::vector<std::string> suggestions = getAutoCompleteSuggestions\(\);',
    'completionCyclePrefix',
    'completionCycleMatches',
    'completionCycleIndex',
    'completionCycleStart',
    'cycleIndex = \(i \+ 1\) % cycleMatches\.size\(\)',
    'line\.replace\(prefixStart, prefix\.length\(\), replacement\)'
)
Test-SourcePattern "auto adjust window writes window and dimensions settings" $dataCorePath 'void autoAdjustWindow\(\)[\s\S]*applyConsoleDimensionsSafe\(160, 2000\)[\s\S]*window\.txt[\s\S]*dimensions\.txt[\s\S]*MODE con cols=%d lines=%d'
Test-SourcePattern "auto adjust window command calls layout helper" $commandsPath 'isCommand\(arithTrig, "autoadjustwindow"\)[\s\S]*autoAdjustWindow\(\);'
Test-SourcePattern "about command clears screen and opens about screen" $commandsPath 'isCommand\(arithTrig, "about"\)[\s\S]*cls\(\);[\s\S]*about2\(\);'
Test-SourcePattern "about screen reads about execution text and waits for enter" $settingsPath 'void about2\(\)[\s\S]*About execution of application\.txt[\s\S]*PRESS THE BUTTON \\"Enter\\"[\s\S]*gets_s\(about, 15000\)'
Test-SourcePattern "history command opens history file in notepad" $commandsPath 'isCommand\(arithTrig, "history"\)[\s\S]*Close the history to continue[\s\S]*notepad\.exe %s\\\\history\.txt[\s\S]*system\(path4ATC\);'
Test-SourcePattern "user guide command opens local PDF" $commandsPath 'isCommand\(arithTrig, "userguide"\)[\s\S]*Advanced Trigonometry Calculator - User Guide\.pdf[\s\S]*ShellExecute'
Test-SourcePattern "run atc command launches atc executable" $commandsPath 'isCommand\(arithTrig, "runatc"\)[\s\S]*%s\\\\atc\.exe[\s\S]*ShellExecute\(NULL, _T\("open"\), sw'
Test-SourcePattern "restart atc command exits current loop and launches atc executable" $commandsPath 'isCommand\(arithTrig, "restartatc"\)[\s\S]*continu = 0;[\s\S]*%s\\\\atc\.exe[\s\S]*ShellExecute\(NULL, _T\("open"\), sw'
Test-SourcePatterns "updates and external links branches" $commandsPath @(
    'isCommand\(arithTrig, "checkforupdates"\)',
    'isCommand\(arithTrig, "updateportable"\)',
    'isCommand\(arithTrig, "update"\)',
    'isCommand\(arithTrig, "updatex64"\)',
    'isCommand\(arithTrig, "donate"\)',
    'isCommand\(arithTrig, "atcfacebook"\)',
    'isCommand\(arithTrig, "atcsourceforge"\)'
)
Test-SourcePatterns "updates and external links are exposed by autocomplete" (Join-Path $sourceDir "auto_complete.cpp") @(
    'check for updates',
    'update',
    'update x64',
    'update portable',
    'donate',
    'atc facebook',
    'atc sourceforge'
)
Test-SourcePatterns "check for updates uses hosted version endpoint" (Join-Path $sourceDir "check_for_updates.cpp") @(
    'void check4Updates\(\)',
    'advantrigoncalc\.sourceforge\.io',
    '/atc_version\.html',
    'HttpGetRequest\(server, path\)',
    'update portable',
    'update x64'
)
Test-SourcePattern "update portable opens SourceForge ZIP download" $commandsPath 'isCommand\(arithTrig, "updateportable"\)[\s\S]*Advanced%20Trigonometry%20Calculator\.zip/download'
Test-SourcePattern "update opens SourceForge x86 installer download" $commandsPath 'isCommand\(arithTrig, "update"\)[\s\S]*Setup%20Advanced%20Trigonometry%20Calculator%20x86\.exe/download'
Test-SourcePattern "update x64 opens SourceForge x64 installer download" $commandsPath 'isCommand\(arithTrig, "updatex64"\)[\s\S]*Setup%20Advanced%20Trigonometry%20Calculator%20x64\.exe/download'
Test-SourcePattern "donate opens SourceForge donation page" $commandsPath 'isCommand\(arithTrig, "donate"\)[\s\S]*sourceforge\.net/p/advantrigoncalc/donate/\?source=navbar'
Test-SourcePattern "ATC Facebook command opens official page" $commandsPath 'isCommand\(arithTrig, "atcfacebook"\)[\s\S]*https://www\.facebook\.com/advantrigoncalc/'
Test-SourcePattern "ATC SourceForge command opens project page" $commandsPath 'isCommand\(arithTrig, "atcsourceforge"\)[\s\S]*https://sourceforge\.net/projects/advantrigoncalc/'
Test-SourcePatterns "reset command branches" $commandsPath @(
    'isCommand\(arithTrig, "resetall"\)',
    'isCommand\(arithTrig, "resetallnow"\)',
    'isCommand\(arithTrig, "resetsettings"\)',
    'isCommand\(arithTrig, "resetsettingsnow"\)'
)
Test-SourcePatterns "reset and colors commands are exposed by autocomplete" (Join-Path $sourceDir "auto_complete.cpp") @(
    'reset all',
    'reset all now',
    'reset settings',
    'reset settings now',
    'colors'
)
Test-SourcePattern "reset all writes onStart resetall marker" $commandsPath 'isCommand\(arithTrig, "resetall"\)[\s\S]*onStart\.txt[\s\S]*fprintf\(start, "resetall"\)[\s\S]*Restart the application to apply changes'
Test-SourcePattern "reset all now writes marker and relaunches ATC" $commandsPath 'isCommand\(arithTrig, "resetallnow"\)[\s\S]*onStart\.txt[\s\S]*fprintf\(start, "resetall"\)[\s\S]*continu = 0;[\s\S]*%s\\\\atc\.exe[\s\S]*ShellExecute'
Test-SourcePattern "reset settings writes onStart resetsettings marker" $commandsPath 'isCommand\(arithTrig, "resetsettings"\)[\s\S]*onStart\.txt[\s\S]*fprintf\(start, "resetsettings"\)[\s\S]*Restart the application to apply changes'
Test-SourcePattern "reset settings now writes marker and relaunches ATC" $commandsPath 'isCommand\(arithTrig, "resetsettingsnow"\)[\s\S]*onStart\.txt[\s\S]*fprintf\(start, "resetsettings"\)[\s\S]*continu = 0;[\s\S]*%s\\\\atc\.exe[\s\S]*ShellExecute'
Test-SourcePatterns "startup reset all removes broad user data and restores UI settings" $dataCorePath @(
    'history\.txt',
    'variables\.txt',
    'higherPrecision\.txt',
    'renamedVar\.txt',
    'pathName\.txt',
    'predefinedTxt\.txt',
    'rmdir /Q /S',
    'mkdir',
    'Strings',
    'aboutDisabled\.txt',
    'applySettings\(Colors\);[\s\S]*applySettings\(Window\);[\s\S]*applySettings\(Dimensions\);'
)
Test-SourcePatterns "startup reset settings removes configuration files only" $dataCorePath @(
    'numSystems\.txt',
    'siPrefixes\.txt',
    'higherPrecision\.txt',
    'actualTime\.txt',
    'colors\.txt',
    'dimensions\.txt',
    'window\.txt',
    'mode\.txt',
    'verboseResolution\.txt',
    'onStart\.txt',
    'applySettings\(Colors\);[\s\S]*applySettings\(Window\);[\s\S]*applySettings\(Dimensions\);'
)
Test-SourcePatterns "colors uses console keys and persists colors.txt" $settingsPath @(
    'void colors\(\)',
    'getDynamicCharArray\("color 73"',
    'bGround = _getch\(\);',
    'cTxt = _getch\(\);',
    'express\[6\] = bGround;',
    'express\[7\] = cTxt;',
    'applyConsoleColorSafe\(express\);',
    'system\(express\);',
    'colors\.txt',
    'fprintf\(open, "%s", express\);'
)
Test-SourcePatterns "folder helper command branches" $commandsPath @(
    'isCommand\(arithTrig, "atcfolder"\)',
    'isCommand\(arithTrig, "sourcecode"\)',
    'isCommand\(arithTrig, "scriptsexamples"\)',
    'isCommand\(arithTrig, "strings"\)',
    'isCommand\(arithTrig, "userfunctions"\)',
    'isCommand\(arithTrig, "tosolve"\)',
    'isCommand\(arithTrig, "autosolvetxt"\)'
)
Test-SourcePatterns "folder helper commands are exposed by autocomplete" (Join-Path $sourceDir "auto_complete.cpp") @(
    'atc folder',
    'source code',
    'scripts examples',
    'user functions',
    'strings',
    'to solve',
    'auto solve txt'
)
Test-SourcePattern "ATC folder command opens ATC data folder" $commandsPath 'isCommand\(arithTrig, "atcfolder"\)[\s\S]*/C \\"explorer %s\\"[\s\S]*ShellExecute'
Test-SourcePattern "source code command opens Source code folder" $commandsPath 'isCommand\(arithTrig, "sourcecode"\)[\s\S]*explorer %s\\\\Source code\\\\[\s\S]*ShellExecute'
Test-SourcePattern "scripts examples command opens Scripts examples folder" $commandsPath 'isCommand\(arithTrig, "scriptsexamples"\)[\s\S]*explorer %s\\\\Scripts examples\\\\[\s\S]*ShellExecute'
Test-SourcePattern "strings command opens Strings folder" $commandsPath 'isCommand\(arithTrig, "strings"\)[\s\S]*explorer %s\\\\Strings\\\\[\s\S]*ShellExecute'
Test-SourcePattern "user functions command opens User functions folder" $commandsPath 'isCommand\(arithTrig, "userfunctions"\)[\s\S]*explorer %s\\\\User functions\\\\[\s\S]*ShellExecute'
Test-SourcePattern "to solve command opens To solve folder" $commandsPath 'isCommand\(arithTrig, "tosolve"\)[\s\S]*explorer %s\\\\To solve\\\\[\s\S]*ShellExecute'
Test-SourcePattern "auto solve txt waits for SOLVE_NOW and opens answer file" $commandsPath 'isCommand\(arithTrig, "autosolvetxt"\)[\s\S]*Drag to here the file for automatic processing[\s\S]*readyToSolve\(paTH\)[\s\S]*processTxt<T>\(paTH, rf\)[\s\S]*openTxt\(\);'
Test-SourcePattern "open txt guarded in main loop" (Join-Path $sourceDir "main.cpp") "isContained\(""open txt"", arith\)"
Test-SourcePattern "open txt command normalizes quotes and spaces" $commandsPath 'isCommand\(arithTrig, "opentxt"\)[\s\S]*replace\("\\"", "", expressionF\)[\s\S]*replace\("RASF", " ", expressionF\)[\s\S]*openTxt\(\);'
Test-SourcePattern "openTxt opens notepad only when file exists" $dataCorePath 'void openTxt\(\)[\s\S]*fopen\(expressionF, "r"\)[\s\S]*if \(open != NULL\)[\s\S]*notepad\.exe %s[\s\S]*system\(openFile\);'
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
Test-SourcePatterns "PC-control command branches are present but isolated from runtime tests" $commandsPath @(
    'isCommand\(arithTrig, "shutdown"\)',
    'isCommand\(arithTrig, "shutdownnow"\)',
    'isCommand\(arithTrig, "restartpc"\)',
    'isCommand\(arithTrig, "restartpcnow"\)',
    'isCommand\(arithTrig, "hibernate"\)',
    'isCommand\(arithTrig, "logoff"\)',
    'isCommand\(arithTrig, "sleep"\)',
    'isCommand\(arithTrig, "lock"\)'
)
Test-SourcePatterns "PC-control commands are exposed by autocomplete" $autoCompletePath @(
    'shutdown',
    'shutdown now',
    'restart pc',
    'restart pc now',
    'hibernate',
    'log off',
    'sleep',
    'lock'
)
Test-SourcePatterns "PC-control commands target Windows system actions" $commandsPath @(
    'shutdown -s',
    'shutdown /s',
    'shutdown -s -t 0',
    'shutdown /s /t 0',
    'shutdown -r',
    'shutdown /r',
    'shutdown -r -t 0',
    'shutdown /r /t 0',
    'shutdown -l',
    'shutdown /l',
    'SetSuspendState Sleep',
    'SetSuspendState Hibernate',
    'LockWorkStation'
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
Test-AtcSmoke "clock zero-duration smoke" "clock(0:0:0)" "^$"
Test-AtcSmoke "big clock zero-duration smoke" "big clock(0:0:0)" "^$"
Test-AtcSmoke "timer syntax guard smoke" "timer(0)" "Your expression has syntax errors"
Test-AtcSmoke "big timer syntax guard smoke" "big timer(0)" "Your expression has syntax errors"

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
