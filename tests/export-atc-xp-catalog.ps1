param(
    [Parameter(Mandatory=$true)][string]$AtcExe,
    [Parameter(Mandatory=$true)][string]$OutputDirectory
)

# Runs the authoritative All suite on the host while recording portable inputs
# and assertion contracts. No observed output is used as an expected result.
$ErrorActionPreference = 'Stop'
$repo = Split-Path -Parent $PSScriptRoot
$AtcExe = [IO.Path]::GetFullPath($AtcExe)
$OutputDirectory = [IO.Path]::GetFullPath($OutputDirectory)
if (Test-Path -LiteralPath $OutputDirectory) { throw 'OutputDirectory must be new.' }
$null = New-Item -ItemType Directory -Path $OutputDirectory
$assets = Join-Path $OutputDirectory 'package'
$capture = Join-Path $OutputDirectory 'host-capture'
$null = New-Item -ItemType Directory -Path $assets,$capture
$sourceAssets = Join-Path $repo 'Advanced Trigonometry Calculator'
foreach ($item in @('License.txt','About execution of application.txt','Scripts examples','User functions')) {
    Copy-Item -LiteralPath (Join-Path $sourceAssets $item) -Destination $assets -Recurse
}
foreach ($item in @('Strings','To solve')) {
    $null = New-Item -ItemType Directory -Path (Join-Path $assets $item) -Force
}
Copy-Item -LiteralPath $AtcExe -Destination (Join-Path $assets 'atc.exe')
Get-ChildItem -LiteralPath (Split-Path -Parent $AtcExe) -Filter '*.dll' -File | Copy-Item -Destination $assets
Copy-Item -Path (Join-Path $assets '*') -Destination $capture -Recurse
[IO.File]::WriteAllText((Join-Path $capture 'atc_path.txt'), $capture, [Text.Encoding]::ASCII)

$global:AtcXp = @{
    Root = $capture
    Events = New-Object System.Collections.Generic.List[object]
    Previous = @{}
    Processes = 0
    Auxiliaries = 0
    Output = $OutputDirectory
    Runner = Join-Path $PSScriptRoot 'run-atc-regression.ps1'
}

function Convert-XpText([string]$Text) {
    # Replace escaped regex paths before ordinary strings.
    $Text.Replace([regex]::Escape($global:AtcXp.Root), '@DATA_REGEX@').Replace($global:AtcXp.Root, '@DATA@')
}

function Get-XpSnapshot {
    $snapshot = @{}
    $files = @(Get-ChildItem -LiteralPath $global:AtcXp.Root -File -Filter '*.txt')
    $temp = Join-Path $global:AtcXp.Root 'runner-temp'
    if (Test-Path -LiteralPath $temp) {
        $files += @(Get-ChildItem -LiteralPath $temp -File -Recurse)
        $snapshot['runner-temp'] = '@DIRECTORY@'
        foreach ($dir in Get-ChildItem -LiteralPath $temp -Directory -Recurse) {
            $snapshot[$dir.FullName.Substring($global:AtcXp.Root.Length + 1)] = '@DIRECTORY@'
        }
    }
    foreach ($file in $files) {
        $relative = $file.FullName.Substring($global:AtcXp.Root.Length + 1)
        $snapshot[$relative] = [Convert]::ToBase64String([IO.File]::ReadAllBytes($file.FullName))
    }
    return ,$snapshot
}

function Get-XpChanges {
    $now = Get-XpSnapshot
    $changes = New-Object System.Collections.Generic.List[object]
    foreach ($key in $now.Keys) {
        if (-not $global:AtcXp.Previous.ContainsKey($key) -or $global:AtcXp.Previous[$key] -cne $now[$key]) {
            if ($now[$key] -eq '@DIRECTORY@') { $changes.Add(@{path=$key; directory=$true}) }
            else { $changes.Add(@{path=$key; base64=$now[$key]}) }
        }
    }
    foreach ($key in $global:AtcXp.Previous.Keys) {
        if (-not $now.ContainsKey($key)) { $changes.Add(@{path=$key; delete=$true}) }
    }
    $global:AtcXp.Previous = $now
    return ,@($changes.ToArray())
}

function Add-XpAssertion($Event, [string]$Kind, [string]$Value='', [string]$Path='') {
    $Event.assertions.Add(@{kind=$Kind; value=(Convert-XpText $Value); path=(Convert-XpText $Path)})
}

function Start-XpProcess([string]$Name,[string]$Arguments,[string[]]$InputLines,[string]$WorkingDirectory) {
    $global:AtcXp.Processes++
    $event = @{
        kind='process'; id=$global:AtcXp.Processes; name=$Name
        arguments=(Convert-XpText $Arguments)
        stdin=@($InputLines | ForEach-Object { Convert-XpText $_ })
        cwd=(Convert-XpText $WorkingDirectory)
        changes=(Get-XpChanges); environment=@{}
        assertions=New-Object System.Collections.Generic.List[object]
    }
    Get-ChildItem Env: | Where-Object { $_.Name -like 'ATC_*' } | ForEach-Object {
        $event.environment[$_.Name] = Convert-XpText $_.Value
    }
    foreach ($frame in Get-PSCallStack) {
        $vars = $frame.GetFrameVariables()
        $v = @{}
        foreach ($key in $vars.Keys) { $v[$key] = $vars[$key].Value }
        switch ($frame.FunctionName) {
            { $_ -in @('Test-AtcExpression','Test-AtcExpressionInDirectory','Test-AtcSessionExpression') } {
                Add-XpAssertion $event 'output_regex' $v.ExpectedRegex
            }
            'Test-AtcSolverResidue' {
                $event.assertions.Add(@{kind='solver_residue'; root_regex=$v.RootRegex; tolerance=$v.Tolerance; root_index=0; residue_index=2})
            }
            'Test-AtcExpressionWithVariablesFile' { Add-XpAssertion $event 'file_regex' $v.ExpectedVariablesRegex $variablesPath }
            'Test-AtcExpressionAndFileValue' { Add-XpAssertion $event 'file_value' $v.ExpectedValue $v.Path }
            'Test-AtcExpressionAndFileRegex' { Add-XpAssertion $event 'file_regex' $v.ExpectedFileRegex $v.Path }
            'Test-AtcExpressionAndFileValues' {
                foreach ($path in $v.PathValues.Keys) { Add-XpAssertion $event 'file_value' $v.PathValues[$path] $path }
            }
            'Test-MockedExternalCommand' {
                Add-XpAssertion $event 'file_regex' $v.ExpectedLogRegex $v.logPath
                if ($null -ne $v.AfterRun) { Add-XpAssertion $event 'absent' '' $disableTxtDetectorPath }
            }
            'Test-AtcExportExpression' { Add-XpAssertion $event 'file_regex' $v.ExpectedFileRegex $v.reportPath }
            'Test-AtcDeclineExportExpression' { Add-XpAssertion $event 'output_not_regex' 'Your report was saved successfully' }
            'Test-TxtProcessingFlow' {
                if ($Name -eq 'txt/command bridge: solve real txt file with mocked open') {
                    Add-XpAssertion $event 'output_regex' 'x1=2[\s\S]*x2=1[\s\S]*\(1\+0i\)x\^2[\s\S]*\(_1\+0i\)'
                    Add-XpAssertion $event 'file_regex' '#\d+=4[\s\S]*#\d+=3[\s\S]*#\d+=2[\s\S]*>solve equation\(\(x-1\)\(x-2\)\)[\s\S]*>simplify polynomial\(\(x\+1\)\(x-1\)\)[\s\S]*Error in syntax[\s\S]*#\d+=5' $v.answerPath
                    Add-XpAssertion $event 'file_regex' 'openTxt\|.*input_answers\.txt' $v.logPath
                }
            }
            'Test-AutoSolveTxtWatcherFlow' {
                Add-XpAssertion $event 'file_regex' '#\d+=4[\s\S]*#\d+=3[\s\S]*>solve equation\(\(x-1\)\(x-2\)\)' $v.answerPath
                Add-XpAssertion $event 'output_regex' 'x1=2[\s\S]*x2=1'
                Add-XpAssertion $event 'file_not_regex' 'SOLVE_NOW' $v.inputPath
                Add-XpAssertion $event 'file_regex' 'openTxt\|.*auto-watch_answers\.txt' $v.logPath
            }
            'Test-EliminateStringsMock' {
                Add-XpAssertion $event 'absent' '' $v.markerPath
                Add-XpAssertion $event 'file_regex' 'eliminateStrings\|.*Strings' $v.environment.ATC_TEST_EXTERNAL_OPEN_LOG
            }
        }
    }
    if ($event.assertions.Count -eq 0) { throw "Missing assertion contract: $Name" }
    $global:AtcXp.Events.Add($event)
    return $event
}

function Finish-XpProcess($Event,$Result) {
    # Only changes made by the harness between processes become fixtures.
    # Executable-produced state is preserved and tested, never replayed.
    $global:AtcXp.Previous = Get-XpSnapshot
    $Event.host_exit_code = $Result.ExitCode
    $Event.host_timed_out = $Result.TimedOut
}

function Add-XpAuxiliary([string]$Name,[string]$Kind,[string]$Path,[string]$Value='') {
    $global:AtcXp.Auxiliaries++
    $event = @{
        kind='auxiliary'; id=('aux-' + $global:AtcXp.Auxiliaries); name=$Name
        changes=(Get-XpChanges); assertions=New-Object System.Collections.Generic.List[object]
    }
    Add-XpAssertion $event $Kind $Value $Path
    $global:AtcXp.Events.Add($event)
}

function Save-XpCatalog($Results) {
    $checks = @()
    foreach ($result in $Results) {
        $members = @($global:AtcXp.Events | Where-Object { $_.name -eq $result.Name } | ForEach-Object { $_.id })
        if ($result.Name -eq 'txt/command bridge: full solve txt flow') {
            $members = @($global:AtcXp.Events | Where-Object {
                $_.name -in @('txt/command bridge: predefine real txt path','txt/command bridge: solve real txt file with mocked open')
            } | ForEach-Object { $_.id })
        }
        if ($members.Count -eq 0) { throw "Unmapped official check: $($result.Name)" }
        $checks += @{name=$result.Name; members=$members; host_passed=$result.Passed}
    }
    if ($global:AtcXp.Processes -ne 369 -or $global:AtcXp.Auxiliaries -ne 8 -or $checks.Count -ne 376) {
        throw "Catalog count drift: processes=$($global:AtcXp.Processes), direct checks=$($global:AtcXp.Auxiliaries), logical checks=$($checks.Count)"
    }
    $names = @($checks | ForEach-Object { $_.name } | Select-Object -Unique)
    if ($names.Count -ne 376) { throw 'Duplicate official check names.' }
    if (@($checks | Where-Object { -not $_.host_passed }).Count -ne 0) { throw 'Authoritative host suite did not pass.' }
    $localChanges = @(& git -C $repo diff --name-only HEAD)
    $sourceHashes = @{}
    foreach ($path in (& git -C $repo ls-files 'Advanced Trigonometry Calculator')) {
        if ($path -match '\.(cpp|h|asm|vcxproj|rc)$') {
            $sourceHashes[$path] = (Get-FileHash -LiteralPath (Join-Path $repo $path) -Algorithm SHA256).Hash.ToLowerInvariant()
        }
    }
    $manifest = @{
        schema=1; source_commit=(& git -C $repo rev-parse HEAD)
        local_tracked_changes=$localChanges; source_worktree_clean=($localChanges.Count -eq 0)
        source_files_sha256=$sourceHashes
        runner_sha256=(Get-FileHash -LiteralPath $global:AtcXp.Runner -Algorithm SHA256).Hash.ToLowerInvariant()
        executable_sha256=(Get-FileHash -LiteralPath (Join-Path $assets 'atc.exe') -Algorithm SHA256).Hash.ToLowerInvariant()
        timeout_seconds=20; process_count=369; direct_auxiliary_count=8; check_count=376
        count_note='369 processes + 8 direct checks - 1 TXT composite grouping = 376 logical checks (net auxiliary difference: 7).'
        capture_root=$global:AtcXp.Root; events=@($global:AtcXp.Events.ToArray()); checks=$checks
    }
    $json = $manifest | ConvertTo-Json -Depth 30
    [IO.File]::WriteAllText((Join-Path $OutputDirectory 'catalog.json'), $json, (New-Object Text.UTF8Encoding($false)))
    Write-Host "XP catalog: 369 processes, 376 checks; $OutputDirectory"
}

$global:AtcXp.Previous = Get-XpSnapshot
$source = [IO.File]::ReadAllText($global:AtcXp.Runner)
$replacements = @{
    '    $workingDirectory = $WorkingDirectory' = '    $xpEvent = Start-XpProcess $Name $Arguments $InputLines $WorkingDirectory' + "`n" + '    $workingDirectory = $WorkingDirectory'
    '    if ($timedOut) {' = '    Finish-XpProcess $xpEvent $result' + "`n" + '    if ($timedOut) {'
    'function Test-FileValue([string]$Name, [string]$Path, [string]$ExpectedValue) {' = 'function Test-FileValue([string]$Name, [string]$Path, [string]$ExpectedValue) {' + "`n" + '    Add-XpAuxiliary $Name file_value $Path $ExpectedValue'
    'function Test-DirectoryExists([string]$Name, [string]$Path) {' = 'function Test-DirectoryExists([string]$Name, [string]$Path) {' + "`n" + '    Add-XpAuxiliary $Name directory_exists $Path'
    'function Test-FileExists([string]$Name, [string]$Path) {' = 'function Test-FileExists([string]$Name, [string]$Path) {' + "`n" + '    Add-XpAuxiliary $Name file_exists $Path'
    '$failed = @($results | Where-Object { -not $_.Passed })' = 'Save-XpCatalog $results' + "`n" + '$failed = @($results | Where-Object { -not $_.Passed })'
}
foreach ($key in $replacements.Keys) {
    if ($source.Split(@($key),[StringSplitOptions]::None).Count -ne 2) { throw "Instrumentation anchor drift: $key" }
    $source = $source.Replace($key, $replacements[$key])
}
$source = $source.Replace('$PSScriptRoot', ("'" + $PSScriptRoot.Replace("'","''") + "'"))
& ([scriptblock]::Create($source)) -AtcExe (Join-Path $capture 'atc.exe') -AtcDataDir $capture -AtcPackageDir $assets -Mode All
exit $LASTEXITCODE
