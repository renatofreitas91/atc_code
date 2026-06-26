param(
    [string]$AtcExe = (Join-Path $PSScriptRoot "..\x64\Release\atc.exe"),
    [string]$AtcDataDir = (Join-Path $env:USERPROFILE "Pictures\Advanced Trigonometry Calculator"),
    [int]$Iterations = 10,
    [int]$TimeoutSeconds = 30
)

$ErrorActionPreference = "Stop"

$AtcExe = [System.IO.Path]::GetFullPath($AtcExe)
$AtcDataDir = [System.IO.Path]::GetFullPath($AtcDataDir)
$higherPrecisionPath = Join-Path $AtcDataDir "higherPrecision.txt"
$aboutDisabledPath = Join-Path $AtcDataDir "aboutDisabled.txt"

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
$hadHigherPrecision = Test-Path $higherPrecisionPath
$hadAboutDisabled = Test-Path $aboutDisabledPath

function Invoke-AtcMeasuredCommand([string]$Expression, [string[]]$InputLines = @()) {
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

    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    $peakWorkingSet = 0L
    $peakPrivateMemory = 0L
    while (-not $process.HasExited) {
        if ($stopwatch.Elapsed.TotalSeconds -gt $TimeoutSeconds) {
            try {
                $process.Kill()
            }
            catch {
            }
            throw "Timed out after $TimeoutSeconds seconds: $Expression"
        }

        try {
            $process.Refresh()
            if ($process.WorkingSet64 -gt $peakWorkingSet) {
                $peakWorkingSet = $process.WorkingSet64
            }
            if ($process.PrivateMemorySize64 -gt $peakPrivateMemory) {
                $peakPrivateMemory = $process.PrivateMemorySize64
            }
        }
        catch {
        }
        Start-Sleep -Milliseconds 25
    }
    $process.WaitForExit()
    $stopwatch.Stop()

    $stdout = $process.StandardOutput.ReadToEnd()
    $stderr = $process.StandardError.ReadToEnd()

    [pscustomobject]@{
        Expression = $Expression
        ExitCode = $process.ExitCode
        ElapsedMs = [math]::Round($stopwatch.Elapsed.TotalMilliseconds, 1)
        PeakWorkingSetMB = [math]::Round($peakWorkingSet / 1MB, 2)
        PeakPrivateMemoryMB = [math]::Round($peakPrivateMemory / 1MB, 2)
        OutputLength = ($stdout + $stderr).Length
    }
}

$reportRoot = Join-Path $PSScriptRoot "memory-stress-reports"
New-Item -ItemType Directory -Path $reportRoot -Force | Out-Null

$tests = @(
    @{
        Name = "simplify quadratic"
        Expression = "simplify polynomial(x^2-5*x+6)"
        Input = @("0")
    },
    @{
        Name = "simplify product"
        Expression = "simplify polynomial((x-2)*(x-3))"
        Input = @("0")
    },
    @{
        Name = "roots to polynomial"
        Expression = "roots to polynomial(2\7\12)"
        Input = @("0")
    },
    @{
        Name = "solve quadratic textual"
        Expression = "solve equation(x^2-5*x+6)"
        Input = @("0")
    },
    @{
        Name = "solve degree seven textual"
        Expression = "solve equation(x^7-12)"
        Input = @("0")
    },
    @{
        Name = "solve cubic coefficient"
        Expression = "solve equation(1\8\1\_42)"
        Input = @("0")
    },
    @{
        Name = "solve coefficient degree thirty"
        Expression = "solve equation(1\2\3\4\5\6\7\8\9\10\11\12\13\14\15\16\17\18\19\20\21\22\23\24\25\26\27\28\29\30\31)"
        Input = @("0")
    },
    @{
        Name = "solve internal roots one to twenty"
        Expression = "solve equation((1+0i)x^20+(_210+0i)x^19+(20615+0i)x^18+(_1256850+0i)x^17+(53327946+0i)x^16+(_1672280820+0i)x^15+(40171771630+0i)x^14+(_756111184500+0i)x^13+(11310276995381+0i)x^12+(_135585182899530+0i)x^11+(1307535010540395+0i)x^10+(_10142299865511450+0i)x^9+(63030812099294896+0i)x^8+(_311333643161390592+0i)x^7+(1206647803780373248+0i)x^6+(_3599979517947607552+0i)x^5+(8037811822645051392+0i)x^4+(_12870931245150986240+0i)x^3+(13803759753640706048+0i)x^2+(_8752948036761601024+0i)x^1+(2432902008176640000+0i))"
        Input = @("0")
    },
    @{
        Name = "solve internal roots one to thirty rounded"
        Expression = "solve equation((1+0i)x^30+(_465+0i)x^29+(103385+0i)x^28+(_14631225+0i)x^27+(1480321269+0i)x^26+(_114009431445+0i)x^25+(6949189247325+0i)x^24+(_344092707928125+0i)x^23+(14097793282984516+0i)x^22+(_484338676679532672+0i)x^21+(14090257524223082496+0i)x^20+(_349600545868057542656+0i)x^19+(7435941626111728812032+0i)x^18+(_136055808711963340439552+0i)x^17+(2145883249334502293504000+0i)x^16+(_29197210605623744019824640+0i)x^15+(342563613932937757170073600+0i)x^14+(_3460266110493899526852575232+0i)x^13+(30006513636556699728284221440+0i)x^12+(_222457423246962051116563431424+0i)x^11+(1401937624086807321099265638400+0i)x^10+(_7454161471690659788189314580480+0i)x^9+(33114629767614991037213800660992+0i)x^8+(_121365366674745170158145442414592+0i)x^7+(360930788158836595287765381283840+0i)x^6+(_851899888505423116603166520508416+0i)x^5+(1547794975254719999379763051364352+0i)x^4+(_2070792202024595295229681577492480+0i)x^3+(1902893785240927722307038455267328+0i)x^2+(_1059681761389533906927603618414592+0i)x^1+(265252859812191104246398737973248+0i))"
        Input = @("0")
    },
    @{
        Name = "simplify complex product"
        Expression = "simplify polynomial((x-1)(x-0)(x-0.5i)(x-2))"
        Input = @("0")
    }
)

$rows = New-Object System.Collections.Generic.List[object]

try {
    Set-Content -Path $higherPrecisionPath -Value "0" -NoNewline
    Set-Content -Path $aboutDisabledPath -Value "1" -NoNewline

    foreach ($test in $tests) {
        for ($iteration = 1; $iteration -le $Iterations; $iteration++) {
            $measurement = Invoke-AtcMeasuredCommand $test.Expression $test.Input
            $rows.Add([pscustomobject]@{
                Test = $test.Name
                Iteration = $iteration
                Expression = $measurement.Expression
                ExitCode = $measurement.ExitCode
                ElapsedMs = $measurement.ElapsedMs
                PeakWorkingSetMB = $measurement.PeakWorkingSetMB
                PeakPrivateMemoryMB = $measurement.PeakPrivateMemoryMB
                OutputLength = $measurement.OutputLength
            })
        }
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
}

$csvPath = Join-Path $reportRoot ("memory-stress-" + (Get-Date -Format "yyyyMMdd-HHmmss") + ".csv")
$rows | Export-Csv -Path $csvPath -NoTypeInformation

$summary = $rows |
    Group-Object Test |
    ForEach-Object {
        $items = @($_.Group)
        [pscustomobject]@{
            Test = $_.Name
            Runs = $items.Count
            AvgElapsedMs = [math]::Round(($items | Measure-Object ElapsedMs -Average).Average, 1)
            MaxPeakWorkingSetMB = [math]::Round(($items | Measure-Object PeakWorkingSetMB -Maximum).Maximum, 2)
            AvgPeakWorkingSetMB = [math]::Round(($items | Measure-Object PeakWorkingSetMB -Average).Average, 2)
            MaxPeakPrivateMemoryMB = [math]::Round(($items | Measure-Object PeakPrivateMemoryMB -Maximum).Maximum, 2)
            ExitCodes = (($items | Select-Object -ExpandProperty ExitCode -Unique) -join ",")
        }
    }

$summary | Format-Table -AutoSize
Write-Host ""
Write-Host "CSV: $csvPath"
