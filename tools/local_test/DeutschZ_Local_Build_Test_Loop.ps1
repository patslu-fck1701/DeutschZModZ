param(
    [int]$Rounds = 1,
    [int]$TestSeconds = 90,
    [string]$RepoRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ",
    [string]$ServerRoot = "F:\Programme\steamapps\common\DayZServer",
    [string]$DeployRoot = "P:\ReadyMods",
    [string]$KeyName = "DeutschZLocal"
)

$ErrorActionPreference = "Stop"

$Mods = @(
    "DeutschZ_Core",
    "DeutschZ_ExpansionBridge",
    "DeutschZ_CourierZ",
    "DeutschZ_ConvoyZ",
    "DeutschZ_KotHZ",
    "DeutschZ_GroundZero"
)

$RequiredConfigPatterns = @(
    "class\s+CfgPatches",
    "class\s+CfgMods",
    "class\s+gameScriptModule",
    "class\s+worldScriptModule",
    "class\s+missionScriptModule",
    "files\[\]"
)

$ExpectedConfigs = @(
    "DeutschZ\Core\CoreConfig.json",
    "DeutschZ\ConvoyZ\Settings.json",
    "DeutschZ\ConvoyZ\Events.json",
    "DeutschZ\CourierZ\CourierZConfig.json",
    "DeutschZ\CourierZ\CourierZState.json",
    "DeutschZ\KotHZ\Config\KotH_Config_Chernarus.json",
    "DeutschZ\KotHZ\Config\Loot_Pools.json",
    "DeutschZ\GroundZero\GroundZeroConfig.json",
    "DeutschZ\GroundZero\GroundZeroState.json"
)

$ErrorPatterns = @(
    "SCRIPT ERROR",
    "Can't compile",
    "Can.t compile",
    "Undefined function",
    "Unknown type",
    "Can't open file",
    "Cannot open object",
    "No entry",
    "PBO failed",
    "Signature mismatch",
    "Wrong signature",
    "Invalid file",
    "Virtual Machine Exception",
    "ACCESS_VIOLATION"
)

$SuccessPatterns = @(
    "DeutschZ",
    "Config loaded",
    "Config created",
    "MissionServer initialized",
    "Bootstrap",
    "profiles\\DeutschZ"
)

function New-RunDirectory {
    $root = Join-Path $RepoRoot "local_test_results"
    New-Item -ItemType Directory -Force -Path $root | Out-Null
    $stamp = Get-Date -Format "yyyy-MM-dd_HH-mm-ss"
    $dir = Join-Path $root $stamp
    $i = 1
    while (Test-Path -LiteralPath $dir) {
        $dir = Join-Path $root ("{0}_{1}" -f $stamp, $i)
        $i++
    }
    New-Item -ItemType Directory -Force -Path $dir | Out-Null
    return $dir
}

function Add-ReportLine {
    param([string]$Path, [string]$Text = "")
    Add-Content -LiteralPath $Path -Value $Text -Encoding UTF8
}

function Join-ProcessArguments {
    param([string[]]$Arguments)
    $quoted = @()
    foreach ($arg in $Arguments) {
        if ($arg -match '[\s"]') {
            $quoted += '"' + ($arg -replace '"', '\"') + '"'
        } else {
            $quoted += $arg
        }
    }
    return ($quoted -join " ")
}

function Invoke-ExternalTool {
    param(
        [string]$FilePath,
        [string[]]$Arguments,
        [string]$WorkingDirectory
    )

    $psi = New-Object System.Diagnostics.ProcessStartInfo
    $psi.FileName = $FilePath
    $psi.Arguments = Join-ProcessArguments $Arguments
    $psi.WorkingDirectory = $WorkingDirectory
    $psi.UseShellExecute = $false
    $psi.RedirectStandardOutput = $true
    $psi.RedirectStandardError = $true

    $process = New-Object System.Diagnostics.Process
    $process.StartInfo = $psi
    [void]$process.Start()
    $stdout = $process.StandardOutput.ReadToEnd()
    $stderr = $process.StandardError.ReadToEnd()
    $process.WaitForExit()

    return [PSCustomObject]@{
        ExitCode = $process.ExitCode
        Output = (($stdout, $stderr) -join [Environment]::NewLine)
        Command = "$FilePath $($psi.Arguments)"
    }
}

function Assert-PathReady {
    param([string]$Path, [string]$Label)
    if (-not (Test-Path -LiteralPath $Path)) {
        throw "$Label fehlt oder ist nicht erreichbar: $Path"
    }
}

function Get-ServerBatchPath {
    $candidates = @(
        (Join-Path $ServerRoot "Server.bat"),
        (Join-Path $ServerRoot "server.bat"),
        (Join-Path $ServerRoot "start.bat")
    )
    foreach ($candidate in $candidates) {
        if (Test-Path -LiteralPath $candidate) {
            return $candidate
        }
    }
    throw "Keine vorhandene Server.bat/server.bat/start.bat im Serverroot gefunden. Server.bat wird nicht neu erstellt."
}

function Get-ProfilePathFromBatch {
    param([string]$BatchPath)
    $lines = Get-Content -LiteralPath $BatchPath
    $launchLine = $lines |
        Where-Object { $_ -notmatch '^\s*::' -and $_ -match 'DayZServer_x64\.exe' -and $_ -match '-profiles=' } |
        Select-Object -First 1
    if ($launchLine) {
        $match = [regex]::Match($launchLine, '-profiles="?([^"\s]+)"?')
        if ($match.Success) {
            return Join-Path $ServerRoot $match.Groups[1].Value
        }
    }
    return Join-Path $ServerRoot "profiles"
}

function Test-ModSource {
    param([string]$ModName, [string]$Report)
    $modRoot = Join-Path $RepoRoot "mods\$ModName"
    Assert-PathReady $modRoot "Mod-Source $ModName"

    $required = @("config.cpp", "mod.cpp", '$PBOPREFIX$', "scripts")
    foreach ($item in $required) {
        $path = Join-Path $modRoot $item
        if (-not (Test-Path -LiteralPath $path)) {
            throw "${ModName}: Pflichtdatei/Pflichtordner fehlt: $item"
        }
    }

    $configPath = Join-Path $modRoot "config.cpp"
    $config = Get-Content -Raw -LiteralPath $configPath
    foreach ($pattern in $RequiredConfigPatterns) {
        if ($config -notmatch $pattern) {
            throw "${ModName}: config.cpp fehlt Muster: $pattern"
        }
    }

    $opens = ([regex]::Matches($config, "\{")).Count
    $closes = ([regex]::Matches($config, "\}")).Count
    if ($opens -ne $closes) {
        throw "${ModName}: config.cpp Klammern unbalanciert: {=$opens }=$closes"
    }

    Add-ReportLine $Report "$ModName source OK: $modRoot"
}

function Remove-OldArtifacts {
    param([string]$ModName, [string]$Report)
    $paths = @(
        (Join-Path $DeployRoot "@$ModName\Addons"),
        (Join-Path $ServerRoot "@$ModName\Addons")
    )
    foreach ($dir in $paths) {
        New-Item -ItemType Directory -Force -Path $dir | Out-Null
        $resolved = (Resolve-Path -LiteralPath $dir).Path
        if (-not ($resolved.StartsWith($DeployRoot) -or $resolved.StartsWith($ServerRoot))) {
            throw "Unsicherer Artifact-Pfad: $resolved"
        }
        Get-ChildItem -LiteralPath $dir -File -Filter "$ModName.pbo" -ErrorAction SilentlyContinue | Remove-Item -Force
        Get-ChildItem -LiteralPath $dir -File -Filter "$ModName.pbo.*.bisign" -ErrorAction SilentlyContinue | Remove-Item -Force
        Add-ReportLine $Report "Alte Artefakte entfernt: $dir"
    }
}

function Ensure-SigningKey {
    param([string]$Report)
    $keyDir = Join-Path $DeployRoot "_keys"
    New-Item -ItemType Directory -Force -Path $keyDir | Out-Null
    $private = Join-Path $keyDir "$KeyName.biprivatekey"
    $public = Join-Path $keyDir "$KeyName.bikey"
    if ((Test-Path -LiteralPath $private) -and (Test-Path -LiteralPath $public)) {
        Add-ReportLine $Report "Signing-Key vorhanden: $private"
        return @{ Private = $private; Public = $public }
    }

    $createKey = "F:\Programme\steamapps\common\DayZ Tools\Bin\DsUtils\DSCreateKey.exe"
    Assert-PathReady $createKey "DSCreateKey"
    Push-Location $keyDir
    try {
        & $createKey $KeyName | Out-String | Add-Content -LiteralPath $Report -Encoding UTF8
    } finally {
        Pop-Location
    }
    Assert-PathReady $private "Private Signing-Key"
    Assert-PathReady $public "Public Signing-Key"
    Add-ReportLine $Report "Signing-Key erstellt: $private"
    return @{ Private = $private; Public = $public }
}

function Build-Mod {
    param([string]$ModName, [hashtable]$Key, [string]$BuildReport)
    $builder = "F:\Programme\steamapps\common\DayZ Tools\Bin\AddonBuilder\AddonBuilder.exe"
    $signer = "F:\Programme\steamapps\common\DayZ Tools\Bin\DsUtils\DSSignFile.exe"
    Assert-PathReady $builder "AddonBuilder"
    Assert-PathReady $signer "DSSignFile"

    $src = Join-Path $RepoRoot "mods\$ModName"
    $out = Join-Path $DeployRoot "@$ModName\Addons"
    New-Item -ItemType Directory -Force -Path $out | Out-Null

    Add-ReportLine $BuildReport ""
    Add-ReportLine $BuildReport "===== BUILD $ModName ====="
    Add-ReportLine $BuildReport "Source: $src"
    Add-ReportLine $BuildReport "Output: $out"

    $buildResult = Invoke-ExternalTool -FilePath $builder -Arguments @($src, $out, "-clear", "-packonly", "-prefix=$ModName") -WorkingDirectory $RepoRoot
    Add-ReportLine $BuildReport "Command: $($buildResult.Command)"
    Add-Content -LiteralPath $BuildReport -Value $buildResult.Output -Encoding UTF8

    $pbo = Join-Path $out "$ModName.pbo"
    if (-not (Test-Path -LiteralPath $pbo)) {
        throw "${ModName}: PBO wurde nicht erzeugt: $pbo"
    }

    $signResult = Invoke-ExternalTool -FilePath $signer -Arguments @($Key.Private, "$ModName.pbo") -WorkingDirectory $out
    Add-ReportLine $BuildReport "Command: $($signResult.Command)"
    Add-Content -LiteralPath $BuildReport -Value $signResult.Output -Encoding UTF8
    if ($signResult.ExitCode -ne 0) {
        throw "${ModName}: DSSignFile Exitcode $($signResult.ExitCode)"
    }

    $bisign = Join-Path $out "$ModName.pbo.$KeyName.bisign"
    if (-not (Test-Path -LiteralPath $bisign)) {
        throw "${ModName}: Signatur fehlt nach DSSignFile: $bisign"
    }

    Add-ReportLine $BuildReport "Build/sign OK: $pbo"
}

function Deploy-Mod {
    param([string]$ModName, [hashtable]$Key, [string]$DeployReport)
    $srcAddons = Join-Path $DeployRoot "@$ModName\Addons"
    $dstRoot = Join-Path $ServerRoot "@$ModName"
    $dstAddons = Join-Path $dstRoot "Addons"
    $dstKeys = Join-Path $dstRoot "Keys"
    New-Item -ItemType Directory -Force -Path $dstAddons, $dstKeys | Out-Null

    Copy-Item -LiteralPath (Join-Path $srcAddons "$ModName.pbo") -Destination $dstAddons -Force
    Copy-Item -LiteralPath (Join-Path $srcAddons "$ModName.pbo.$KeyName.bisign") -Destination $dstAddons -Force
    Copy-Item -LiteralPath $Key.Public -Destination (Join-Path $dstKeys "$KeyName.bikey") -Force
    New-Item -ItemType Directory -Force -Path (Join-Path $ServerRoot "keys") | Out-Null
    Copy-Item -LiteralPath $Key.Public -Destination (Join-Path $ServerRoot "keys\$KeyName.bikey") -Force

    Add-ReportLine $DeployReport "Deployed $ModName -> $dstRoot"
}

function Copy-ProfileFallbackIfMissing {
    param([string]$ProfilePath, [string]$ServerReport)
    $target = Join-Path $ProfilePath "DeutschZ"
    $missingExpected = @()
    foreach ($rel in $ExpectedConfigs) {
        $candidate = Join-Path $ProfilePath $rel
        if (-not (Test-Path -LiteralPath $candidate)) {
            $missingExpected += $rel
        }
    }

    if ((Test-Path -LiteralPath $target) -and $missingExpected.Count -eq 0) {
        Add-ReportLine $ServerReport "profiles\DeutschZ vollstaendig vorhanden: $target"
        return
    }

    $fallback = Join-Path $RepoRoot "DeutschZ_PROFILE_CONFIGS_COPY_TO_PROFILES\DeutschZ"
    if (-not (Test-Path -LiteralPath $fallback)) {
        Add-ReportLine $ServerReport "profiles\DeutschZ unvollstaendig, Fallback fehlt ebenfalls: $fallback"
        return
    }

    New-Item -ItemType Directory -Force -Path $target | Out-Null
    Get-ChildItem -LiteralPath $fallback -Force | ForEach-Object {
        Copy-Item -LiteralPath $_.FullName -Destination $target -Recurse -Force
    }
    Add-ReportLine $ServerReport "profiles\DeutschZ fehlte/war unvollstaendig und wurde aus Fallback kopiert: $fallback -> $target"
    if ($missingExpected.Count -gt 0) {
        Add-ReportLine $ServerReport "Vor Fallback fehlten: $($missingExpected -join ', ')"
    }
}

function Get-LatestLog {
    param([string]$ProfilePath, [string[]]$Patterns)
    foreach ($pattern in $Patterns) {
        $file = Get-ChildItem -LiteralPath $ProfilePath -File -Filter $pattern -ErrorAction SilentlyContinue |
            Sort-Object LastWriteTime -Descending |
            Select-Object -First 1
        if ($file) { return $file }
    }
    return $null
}

function Copy-LatestLog {
    param([System.IO.FileInfo]$File, [string]$Destination)
    if ($File -and (Test-Path -LiteralPath $File.FullName)) {
        Copy-Item -LiteralPath $File.FullName -Destination $Destination -Force
    } else {
        Set-Content -LiteralPath $Destination -Value "Log nicht gefunden." -Encoding UTF8
    }
}

function Start-ServerBatchAndMonitor {
    param([string]$RunDir, [string]$ServerReport)
    $batch = Get-ServerBatchPath
    $profilePath = Get-ProfilePathFromBatch $batch
    New-Item -ItemType Directory -Force -Path $profilePath | Out-Null

    Add-ReportLine $ServerReport "Server-Batch: $batch"
    Add-ReportLine $ServerReport "Profile-Pfad: $profilePath"
    Add-ReportLine $ServerReport "Startzeit: $(Get-Date -Format o)"

    $before = @(Get-Process DayZServer_x64 -ErrorAction SilentlyContinue | Select-Object -ExpandProperty Id)
    if ($before.Count -gt 0) {
        Add-ReportLine $ServerReport "Vor Test liefen DayZServer-Prozesse, werden beendet: $($before -join ', ')"
        foreach ($processId in $before) {
            Stop-Process -Id $processId -Force -ErrorAction SilentlyContinue
        }
        Start-Sleep -Seconds 5
        $before = @()
    }

    $startInfo = Start-Process -FilePath "cmd.exe" -ArgumentList "/c", "`"$batch`"" -WorkingDirectory $ServerRoot -PassThru -WindowStyle Hidden
    Add-ReportLine $ServerReport "Batch-Prozess gestartet: PID $($startInfo.Id)"

    $serverProc = $null
    $deadline = (Get-Date).AddSeconds(45)
    while ((Get-Date) -lt $deadline -and -not $serverProc) {
        Start-Sleep -Seconds 2
        $serverProc = Get-Process DayZServer_x64 -ErrorAction SilentlyContinue |
            Where-Object { $before -notcontains $_.Id } |
            Sort-Object StartTime -Descending |
            Select-Object -First 1
    }

    if (-not $serverProc) {
        Add-ReportLine $ServerReport "Kein neuer DayZServer_x64-Prozess nach Batchstart gefunden."
    } else {
        Add-ReportLine $ServerReport "DayZServer-Prozess erkannt: PID $($serverProc.Id)"
    }

    Start-Sleep -Seconds $TestSeconds

    $alive = $false
    if ($serverProc) {
        $alive = [bool](Get-Process -Id $serverProc.Id -ErrorAction SilentlyContinue)
    }
    Add-ReportLine $ServerReport "Alive nach $TestSeconds Sekunden: $alive"

    Copy-ProfileFallbackIfMissing -ProfilePath $profilePath -ServerReport $ServerReport

    $latestScript = Get-LatestLog $profilePath @("script_*.log")
    $latestError = Get-LatestLog $profilePath @("error_*.log", "crash_*.log", "ErrorMessage_*")
    $latestRpt = Get-LatestLog $profilePath @("DayZServer_x64_*.RPT")
    $latestConsole = Get-LatestLog $profilePath @("server_console*.log")

    Copy-LatestLog $latestScript (Join-Path $RunDir "latest_script.log")
    Copy-LatestLog $latestError (Join-Path $RunDir "latest_error.log")
    Copy-LatestLog $latestRpt (Join-Path $RunDir "latest_rpt.log")
    Copy-LatestLog $latestConsole (Join-Path $RunDir "latest_console.log")

    Add-ReportLine $ServerReport ""
    Add-ReportLine $ServerReport "Expected config status:"
    foreach ($rel in $ExpectedConfigs) {
        $path = Join-Path $profilePath $rel
        Add-ReportLine $ServerReport ("{0} : {1}" -f (Join-Path (Split-Path $profilePath -Leaf) $rel), (Test-Path -LiteralPath $path))
    }

    $scanFiles = @($latestScript, $latestError, $latestRpt, $latestConsole) | Where-Object { $_ }
    Add-ReportLine $ServerReport ""
    Add-ReportLine $ServerReport "Detected error patterns:"
    foreach ($file in $scanFiles) {
        $matches = Select-String -LiteralPath $file.FullName -Pattern $ErrorPatterns -SimpleMatch -ErrorAction SilentlyContinue | Select-Object -First 80
        foreach ($match in $matches) {
            Add-ReportLine $ServerReport ("{0}:{1}:{2}" -f $file.Name, $match.LineNumber, $match.Line)
        }
    }

    Add-ReportLine $ServerReport ""
    Add-ReportLine $ServerReport "Detected success patterns:"
    foreach ($file in $scanFiles) {
        $matches = Select-String -LiteralPath $file.FullName -Pattern $SuccessPatterns -SimpleMatch -ErrorAction SilentlyContinue | Select-Object -First 80
        foreach ($match in $matches) {
            Add-ReportLine $ServerReport ("{0}:{1}:{2}" -f $file.Name, $match.LineNumber, $match.Line)
        }
    }

    if ($serverProc -and (Get-Process -Id $serverProc.Id -ErrorAction SilentlyContinue)) {
        Add-ReportLine $ServerReport "Server wird beendet: PID $($serverProc.Id)"
        Stop-Process -Id $serverProc.Id -Force
    }
}

Assert-PathReady $RepoRoot "RepoRoot"
Assert-PathReady (Join-Path $RepoRoot "mods") "Source-Ordner"
Assert-PathReady $ServerRoot "ServerRoot"
Assert-PathReady (Join-Path $ServerRoot "DayZServer_x64.exe") "DayZServer_x64.exe"
Assert-PathReady "F:\Programme\steamapps\common\DayZ Tools\Bin\AddonBuilder\AddonBuilder.exe" "AddonBuilder"
Assert-PathReady "F:\Programme\steamapps\common\DayZ Tools\Bin\DsUtils\DSSignFile.exe" "DSSignFile"

for ($round = 1; $round -le $Rounds; $round++) {
    $runDir = New-RunDirectory
    $buildReport = Join-Path $runDir "build_report.txt"
    $deployReport = Join-Path $runDir "deploy_report.txt"
    $serverReport = Join-Path $runDir "server_test_report.txt"

    Set-Content -LiteralPath $buildReport -Value "DeutschZ Local Build Report - Runde $round - $(Get-Date -Format o)" -Encoding UTF8
    Set-Content -LiteralPath $deployReport -Value "DeutschZ Deploy Report - Runde $round - $(Get-Date -Format o)" -Encoding UTF8
    Set-Content -LiteralPath $serverReport -Value "DeutschZ Server Test Report - Runde $round - $(Get-Date -Format o)" -Encoding UTF8

    try {
        Add-ReportLine $buildReport "RepoRoot: $RepoRoot"
        Add-ReportLine $buildReport "ServerRoot: $ServerRoot"
        Add-ReportLine $buildReport "DeployRoot: $DeployRoot"

        foreach ($mod in $Mods) {
            Test-ModSource -ModName $mod -Report $buildReport
        }

        $key = Ensure-SigningKey -Report $buildReport

        foreach ($mod in $Mods) {
            Remove-OldArtifacts -ModName $mod -Report $deployReport
            Build-Mod -ModName $mod -Key $key -BuildReport $buildReport
            Deploy-Mod -ModName $mod -Key $key -DeployReport $deployReport
        }

        Start-ServerBatchAndMonitor -RunDir $runDir -ServerReport $serverReport
        Write-Host "Runde $round fertig. Report: $runDir"
    } catch {
        Add-ReportLine $buildReport "FEHLER: $($_.Exception.Message)"
        Add-ReportLine $deployReport "FEHLER: $($_.Exception.Message)"
        Add-ReportLine $serverReport "FEHLER: $($_.Exception.Message)"
        Write-Error $_
        break
    }
}
