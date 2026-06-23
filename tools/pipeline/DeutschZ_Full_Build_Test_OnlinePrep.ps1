param(
    [ValidateSet("Full", "Validate", "Build", "Test", "Package")]
    [string]$Mode = "Full",
    [int]$Rounds = 3,
    [int]$TestSeconds = 90,
    [string]$RepoRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ",
    [string]$ServerRoot = "F:\Programme\steamapps\common\DayZServer",
    [string]$DeployRoot = "P:\ReadyMods",
    [string]$KeyName = "DeutschZLocal"
)

$ErrorActionPreference = "Stop"

$BaseMods = @(
    "DeutschZ_Core",
    "DeutschZ_ExpansionBridge",
    "DeutschZ_KotHZ",
    "DeutschZ_ConvoyZ",
    "DeutschZ_GroundZero",
    "DeutschZ_CourierZ"
)

$OperationMod = "DeutschZ_OperationDeutschZ"
$AllMods = $BaseMods + $OperationMod

$RequiredConfigPatterns = @(
    "class\s+CfgPatches",
    "class\s+CfgMods",
    "dependencies\[\]",
    "class\s+defs",
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
    "DeutschZ\CourierZ\CourierZState.backup.json",
    "DeutschZ\KotHZ\Config\KotH_Config_Chernarus.json",
    "DeutschZ\KotHZ\Config\Loot_Pools.json",
    "DeutschZ\GroundZero\GroundZeroConfig.json",
    "DeutschZ\GroundZero\GroundZeroState.json",
    "DeutschZ\OperationDeutschZ\OperationDeutschZConfig.json",
    "DeutschZ\OperationDeutschZ\OperationDeutschZState.json"
)

$ErrorPatterns = @(
    "SCRIPT ERROR",
    "requires addon",
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
    "Scripted variables corrupted",
    "Virtual Machine Exception",
    "ACCESS_VIOLATION"
)

$KnownWarningPatterns = @(
    "Trader does not exist Main_Trader",
    "Trader does not exist SellAll",
    "types_expansion.xml",
    "CE old type",
    "CfgWorlds/DefaultWorld/Weather",
    "No entry 'bin\config.bin/CfgSoundShaders",
    "No entry 'bin\config.bin/CfgSoundSets"
)

$OperationExpectedLogLines = @(
    "[DeutschZ_OperationDeutschZ] Init start",
    "[DeutschZ_OperationDeutschZ] Profile folders ensured",
    "[DeutschZ_OperationDeutschZ] Config created",
    "[DeutschZ_OperationDeutschZ] Config loaded",
    "[DeutschZ_OperationDeutschZ] State created",
    "[DeutschZ_OperationDeutschZ] State loaded",
    "[DeutschZ_OperationDeutschZ] Init done"
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

function Set-Report {
    param([string]$Path, [string]$Title)
    Set-Content -LiteralPath $Path -Value "$Title - $(Get-Date -Format o)" -Encoding UTF8
}

function Assert-PathReady {
    param([string]$Path, [string]$Label)
    if (-not (Test-Path -LiteralPath $Path)) {
        throw "$Label fehlt oder ist nicht erreichbar: $Path"
    }
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

function Get-ServerBatchPath {
    $candidates = @(
        (Join-Path $ServerRoot "start.bat"),
        (Join-Path $ServerRoot "Server.bat"),
        (Join-Path $ServerRoot "server.bat")
    )
    foreach ($candidate in $candidates) {
        if (Test-Path -LiteralPath $candidate) {
            return $candidate
        }
    }
    throw "Keine vorhandene start.bat/Server.bat/server.bat im Serverroot gefunden. Es wird keine neue Batch erzeugt."
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

function Get-ModLineFromBatch {
    param([string]$BatchPath)
    $lines = Get-Content -LiteralPath $BatchPath
    $launchLine = $lines |
        Where-Object { $_ -notmatch '^\s*::' -and $_ -match 'DayZServer_x64\.exe' -and $_ -match '-mod=' } |
        Select-Object -First 1
    if (-not $launchLine) {
        return ""
    }
    $match = [regex]::Match($launchLine, '-mod=([^"]+)|"-mod=([^"]+)"')
    if ($match.Success) {
        if ($match.Groups[2].Value) { return $match.Groups[2].Value }
        return $match.Groups[1].Value
    }
    return $launchLine
}

function Assert-PipelineReadiness {
    param([string]$Report)
    Assert-PathReady $RepoRoot "RepoRoot"
    Assert-PathReady (Join-Path $RepoRoot "mods") "Source-Ordner"
    Assert-PathReady $ServerRoot "ServerRoot"
    Assert-PathReady (Join-Path $ServerRoot "DayZServer_x64.exe") "DayZServer_x64.exe"
    Assert-PathReady "F:\Programme\steamapps\common\DayZ Tools\Bin\AddonBuilder\AddonBuilder.exe" "AddonBuilder"
    Assert-PathReady "F:\Programme\steamapps\common\DayZ Tools\Bin\DsUtils\DSSignFile.exe" "DSSignFile"
    Assert-PathReady "F:\Programme\steamapps\common\DayZ Tools\Bin\DsUtils\DSCreateKey.exe" "DSCreateKey"
    New-Item -ItemType Directory -Force -Path $DeployRoot | Out-Null

    $batch = Get-ServerBatchPath
    Add-ReportLine $Report "RepoRoot OK: $RepoRoot"
    Add-ReportLine $Report "ServerRoot OK: $ServerRoot"
    Add-ReportLine $Report "DeployRoot OK: $DeployRoot"
    Add-ReportLine $Report "Start-Batch unveraendert verwendet: $batch"
    Add-ReportLine $Report "Batch-Modline: $(Get-ModLineFromBatch $batch)"
}

function Get-RequiredAddonsText {
    param([string]$ConfigText)
    $match = [regex]::Match($ConfigText, 'requiredAddons\[\]\s*=\s*\{([^}]*)\}', [System.Text.RegularExpressions.RegexOptions]::Singleline)
    if (-not $match.Success) {
        return @()
    }
    return @([regex]::Matches($match.Groups[1].Value, '"([^"]+)"') | ForEach-Object { $_.Groups[1].Value })
}

function Test-RequiredAddonsPolicy {
    param([string]$ModName, [string]$RequiredReport)
    $configPath = Join-Path $RepoRoot "mods\$ModName\config.cpp"
    $config = Get-Content -Raw -LiteralPath $configPath
    $addons = Get-RequiredAddonsText $config
    Add-ReportLine $RequiredReport "$ModName requiredAddons: $($addons -join ', ')"

    if ($addons -contains "DZ_Gear_Radio") {
        throw "${ModName}: DZ_Gear_Radio ist nicht erlaubt, bis der lokale CfgPatches-Name verifiziert ist."
    }

    if ($ModName -eq "DeutschZ_Core") {
        if ($config -match 'class\s+DZ_BrokenTransmitter\s*:\s*PersonalRadio') {
            throw "DeutschZ_Core: DZ_BrokenTransmitter darf nicht mehr von PersonalRadio ableiten."
        }
        if ($config -match 'class\s+DZ_RedSmokeBeacon\s*:\s*PersonalRadio') {
            throw "DeutschZ_Core: DZ_RedSmokeBeacon darf nicht mehr von PersonalRadio ableiten."
        }
        Add-ReportLine $RequiredReport "DeutschZ_Core radio fix OK: kein DZ_Gear_Radio, keine PersonalRadio-Ableitung fuer DeutschZ-Funkitems."
    }
}

function Test-ModSource {
    param([string]$ModName, [string]$Report, [string]$ConfigReport)
    $modRoot = Join-Path $RepoRoot "mods\$ModName"
    Assert-PathReady $modRoot "Mod-Source $ModName"

    foreach ($item in @("config.cpp", "mod.cpp", '$PBOPREFIX$', "scripts")) {
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
    Add-ReportLine $ConfigReport "$ModName config.cpp Pflichtmuster OK"

    foreach ($scriptFolder in @("3_Game", "4_World", "5_Mission")) {
        if ($config -match [regex]::Escape("scripts/$scriptFolder")) {
            $scriptPath = Join-Path $modRoot "scripts\$scriptFolder"
            if (-not (Test-Path -LiteralPath $scriptPath)) {
                throw "${ModName}: config.cpp referenziert scripts/$scriptFolder, Ordner fehlt"
            }
            Add-ReportLine $ConfigReport "$ModName scripts/$scriptFolder vorhanden"
        }
    }

    $opens = ([regex]::Matches($config, "\{")).Count
    $closes = ([regex]::Matches($config, "\}")).Count
    if ($opens -ne $closes) {
        throw "${ModName}: config.cpp Klammern unbalanciert: {=$opens }=$closes"
    }

    $forbidden = Get-ChildItem -LiteralPath $modRoot -Recurse -Force -ErrorAction SilentlyContinue |
        Where-Object {
            $_.Name -eq '$temp' -or
            $_.Extension -in @(".pbo", ".bisign", ".bikey") -or
            $_.FullName -match '\\SteamWorkshop_Beschreibungen\\' -or
            $_.FullName -match '\\CHANGELOGS_CURRENT\\'
        }
    if ($forbidden) {
        throw "${ModName}: Source enthaelt verbotene Build/Workshop-Artefakte: $($forbidden[0].FullName)"
    }

    Add-ReportLine $Report "$ModName source OK: $modRoot"
}

function Remove-OldArtifacts {
    param([string]$ModName, [string]$Report)
    foreach ($dir in @((Join-Path $DeployRoot "@$ModName\Addons"), (Join-Path $ServerRoot "@$ModName\Addons"))) {
        New-Item -ItemType Directory -Force -Path $dir | Out-Null
        $resolved = (Resolve-Path -LiteralPath $dir).Path
        if (-not ($resolved.StartsWith((Resolve-Path -LiteralPath $DeployRoot).Path) -or $resolved.StartsWith((Resolve-Path -LiteralPath $ServerRoot).Path))) {
            throw "Unsicherer Artefakt-Pfad: $resolved"
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

function Copy-DirectoryContents {
    param([string]$Source, [string]$Destination)
    if (-not (Test-Path -LiteralPath $Source)) {
        return
    }
    New-Item -ItemType Directory -Force -Path $Destination | Out-Null
    Get-ChildItem -LiteralPath $Source -Force | ForEach-Object {
        Copy-Item -LiteralPath $_.FullName -Destination $Destination -Recurse -Force
    }
}

function Copy-ProfileFallbacks {
    param([string]$ProfilePath, [string]$Report)
    $target = Join-Path $ProfilePath "DeutschZ"
    $repoFallback = Join-Path $RepoRoot "DeutschZ_PROFILE_CONFIGS_COPY_TO_PROFILES\DeutschZ"
    $onlineFallback = Join-Path $RepoRoot "tools\online_testserver\profile_defaults\DeutschZ"

    Copy-DirectoryContents -Source $repoFallback -Destination $target
    Copy-DirectoryContents -Source $onlineFallback -Destination $target
    Add-ReportLine $Report "Profile-Fallbacks kopiert/gegengeprueft nach: $target"
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

function Test-KnownWarningLine {
    param([string]$Line)
    if ($Line -like "*Warning Message: No entry 'bin\config.bin/CfgWorlds/*") {
        return $true
    }
    if ($Line -like "*Warning Message: No entry 'bin\config.bin/CfgVehicles/*") {
        return $true
    }
    foreach ($pattern in $KnownWarningPatterns) {
        if ($Line -like "*$pattern*") {
            return $true
        }
    }
    return $false
}

function Start-ServerBatchAndMonitor {
    param(
        [string]$RunDir,
        [string]$ServerReport,
        [string]$ConfigReport,
        [string]$OperationReport
    )
    $batch = Get-ServerBatchPath
    $profilePath = Get-ProfilePathFromBatch $batch
    $modLine = Get-ModLineFromBatch $batch
    $operationInBatch = $modLine -like "*@$OperationMod*"
    New-Item -ItemType Directory -Force -Path $profilePath | Out-Null

    Add-ReportLine $ServerReport "Server-Batch: $batch"
    Add-ReportLine $ServerReport "Profile-Pfad: $profilePath"
    Add-ReportLine $ServerReport "Batch-Modline: $modLine"
    Add-ReportLine $ServerReport "OperationDeutschZ in Batch-Modline: $operationInBatch"
    Add-ReportLine $ServerReport "Startzeit: $(Get-Date -Format o)"
    Add-ReportLine $OperationReport "OperationDeutschZ in unveraenderter Batch-Modline: $operationInBatch"

    $before = @(Get-Process DayZServer_x64 -ErrorAction SilentlyContinue | Select-Object -ExpandProperty Id)
    if ($before.Count -gt 0) {
        Add-ReportLine $ServerReport "Vor Test liefen DayZServer-Prozesse, werden beendet: $($before -join ', ')"
        foreach ($processId in $before) {
            Stop-Process -Id $processId -Force -ErrorAction SilentlyContinue
        }
        Start-Sleep -Seconds 5
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

    if ($serverProc) {
        Add-ReportLine $ServerReport "DayZServer-Prozess erkannt: PID $($serverProc.Id)"
    } else {
        Add-ReportLine $ServerReport "Kein neuer DayZServer_x64-Prozess nach Batchstart gefunden."
    }

    Start-Sleep -Seconds $TestSeconds

    $alive = $false
    if ($serverProc) {
        $alive = [bool](Get-Process -Id $serverProc.Id -ErrorAction SilentlyContinue)
    }
    Add-ReportLine $ServerReport "Alive nach $TestSeconds Sekunden: $alive"

    Copy-ProfileFallbacks -ProfilePath $profilePath -Report $ConfigReport

    $latestScript = Get-LatestLog $profilePath @("script_*.log")
    $latestError = Get-LatestLog $profilePath @("error_*.log", "crash_*.log", "ErrorMessage_*")
    $latestRpt = Get-LatestLog $profilePath @("DayZServer_x64_*.RPT")
    $latestConsole = Get-LatestLog $profilePath @("server_console*.log")

    Copy-LatestLog $latestScript (Join-Path $RunDir "latest_script.log")
    Copy-LatestLog $latestError (Join-Path $RunDir "latest_error.log")
    Copy-LatestLog $latestRpt (Join-Path $RunDir "latest_rpt.log")
    Copy-LatestLog $latestConsole (Join-Path $RunDir "latest_console.log")

    Add-ReportLine $ConfigReport "Expected config status:"
    foreach ($rel in $ExpectedConfigs) {
        $path = Join-Path $profilePath $rel
        Add-ReportLine $ConfigReport ("{0} : {1}" -f $rel, (Test-Path -LiteralPath $path))
    }

    $scanFiles = @($latestScript, $latestError, $latestRpt, $latestConsole) | Where-Object { $_ }
    $hardMatches = 0
    $knownWarnings = 0
    Add-ReportLine $ServerReport ""
    Add-ReportLine $ServerReport "Detected error/warning patterns:"
    foreach ($file in $scanFiles) {
        $matches = Select-String -LiteralPath $file.FullName -Pattern $ErrorPatterns -SimpleMatch -ErrorAction SilentlyContinue | Select-Object -First 120
        foreach ($match in $matches) {
            $isKnown = Test-KnownWarningLine $match.Line
            if ($isKnown) { $knownWarnings++ } else { $hardMatches++ }
            Add-ReportLine $ServerReport ("{0}:{1}:known={2}:{3}" -f $file.Name, $match.LineNumber, $isKnown, $match.Line)
        }
    }

    Add-ReportLine $OperationReport ""
    Add-ReportLine $OperationReport "OperationDeutschZ expected log lines:"
    $operationLogHits = 0
    foreach ($line in $OperationExpectedLogLines) {
        $found = $false
        foreach ($file in $scanFiles) {
            if (Select-String -LiteralPath $file.FullName -Pattern $line -SimpleMatch -Quiet -ErrorAction SilentlyContinue) {
                $found = $true
                break
            }
        }
        if ($found) { $operationLogHits++ }
        Add-ReportLine $OperationReport ("{0} : {1}" -f $line, $found)
    }

    $operationConfig = Test-Path -LiteralPath (Join-Path $profilePath "DeutschZ\OperationDeutschZ\OperationDeutschZConfig.json")
    $operationState = Test-Path -LiteralPath (Join-Path $profilePath "DeutschZ\OperationDeutschZ\OperationDeutschZState.json")
    $operationSafeBoot = ($operationInBatch -and $operationLogHits -eq $OperationExpectedLogLines.Count -and $operationConfig -and $operationState)

    Add-ReportLine $OperationReport ""
    Add-ReportLine $OperationReport "OperationDeutschZ config vorhanden: $operationConfig"
    Add-ReportLine $OperationReport "OperationDeutschZ state vorhanden: $operationState"
    Add-ReportLine $OperationReport "OperationDeutschZ Safe-Boot bestanden: $operationSafeBoot"
    if (-not $operationInBatch) {
        Add-ReportLine $OperationReport "BLOCKER: Die originale Batch enthaelt @$OperationMod nicht. Sie wurde regelgemaess nicht geaendert; deshalb kann der lokale Start die Safe-Boot-Logzeilen nicht erzeugen."
    }

    if ($serverProc -and (Get-Process -Id $serverProc.Id -ErrorAction SilentlyContinue)) {
        Add-ReportLine $ServerReport "Server wird beendet: PID $($serverProc.Id)"
        Stop-Process -Id $serverProc.Id -Force
    }

    return [PSCustomObject]@{
        Alive = $alive
        HardMatches = $hardMatches
        KnownWarnings = $knownWarnings
        OperationSafeBoot = $operationSafeBoot
        OperationInBatch = $operationInBatch
        ProfilePath = $profilePath
        BatchPath = $batch
    }
}

function New-OnlinePackage {
    param(
        [hashtable]$Key,
        [string]$PackageReport,
        [string]$ServerResultText
    )

    $packageRoot = Join-Path $RepoRoot "online_testserver_package"
    $repoResolved = (Resolve-Path -LiteralPath $RepoRoot).Path
    if (Test-Path -LiteralPath $packageRoot) {
        $packageResolved = (Resolve-Path -LiteralPath $packageRoot).Path
        if (-not $packageResolved.StartsWith($repoResolved)) {
            throw "Unsicherer Paketpfad: $packageResolved"
        }
        Remove-Item -LiteralPath $packageRoot -Recurse -Force
    }

    New-Item -ItemType Directory -Force -Path $packageRoot | Out-Null
    New-Item -ItemType Directory -Force -Path (Join-Path $packageRoot "keys") | Out-Null
    New-Item -ItemType Directory -Force -Path (Join-Path $packageRoot "docs") | Out-Null

    foreach ($mod in $AllMods) {
        $srcAddons = Join-Path $DeployRoot "@$mod\Addons"
        $dstMod = Join-Path $packageRoot "@$mod"
        $dstAddons = Join-Path $dstMod "addons"
        $dstKeys = Join-Path $dstMod "keys"
        New-Item -ItemType Directory -Force -Path $dstAddons, $dstKeys | Out-Null
        Copy-Item -LiteralPath (Join-Path $srcAddons "$mod.pbo") -Destination $dstAddons -Force
        Copy-Item -LiteralPath (Join-Path $srcAddons "$mod.pbo.$KeyName.bisign") -Destination $dstAddons -Force
        Copy-Item -LiteralPath $Key.Public -Destination (Join-Path $dstKeys "$KeyName.bikey") -Force
        Add-ReportLine $PackageReport "Paketmod OK: @$mod"
    }

    Copy-Item -LiteralPath $Key.Public -Destination (Join-Path $packageRoot "keys\$KeyName.bikey") -Force

    $profileTarget = Join-Path $packageRoot "profiles\DeutschZ"
    Copy-DirectoryContents -Source (Join-Path $RepoRoot "DeutschZ_PROFILE_CONFIGS_COPY_TO_PROFILES\DeutschZ") -Destination $profileTarget
    Copy-DirectoryContents -Source (Join-Path $RepoRoot "tools\online_testserver\profile_defaults\DeutschZ") -Destination $profileTarget

    $docs = Join-Path $packageRoot "docs"
    Set-Content -LiteralPath (Join-Path $docs "LOADORDER_ONLINE_TESTSERVER.txt") -Encoding UTF8 -Value ($AllMods | ForEach-Object { "@$_" })
    Set-Content -LiteralPath (Join-Path $docs "SERVERMODLINE_ONLINE_TESTSERVER.txt") -Encoding UTF8 -Value ('-mod=@CF;@Dabs Framework;@DayZ-Expansion-Licensed;@DayZ-Expansion-Bundle;@SNAFU Weapons;' + (($AllMods | ForEach-Object { "@$_" }) -join ';'))
    Set-Content -LiteralPath (Join-Path $docs "TEST_REPORT.txt") -Encoding UTF8 -Value @(
        "DeutschZ Online-Testserver Package",
        "Generated: $(Get-Date -Format o)",
        "Source: $RepoRoot",
        "ReadyMods: $DeployRoot",
        "Signing key: $KeyName",
        "",
        $ServerResultText
    )
    Set-Content -LiteralPath (Join-Path $docs "DEPLOYMENT_CHECKLIST.txt") -Encoding UTF8 -Value @(
        "1. Copy all @DeutschZ_* folders to the server root.",
        "2. Copy keys\DeutschZLocal.bikey to the server keys folder.",
        "3. Copy profiles\DeutschZ to the server profile root or merge it with an existing DeutschZ profile.",
        "4. Use the load order from LOADORDER_ONLINE_TESTSERVER.txt.",
        "5. Add @DeutschZ_OperationDeutschZ after the six existing DeutschZ mods for safe-boot testing.",
        "6. Keep EnableOperationDeutschZ = 0 for the first online test."
    )
    Set-Content -LiteralPath (Join-Path $docs "KNOWN_ISSUES.txt") -Encoding UTF8 -Value @(
        "Known issues / notes",
        "",
        "- Local start.bat is not modified by the pipeline.",
        "- OperationDeutschZ safe-boot log lines appear only when start.bat or the online testserver modline loads @DeutschZ_OperationDeutschZ.",
        "- Vanilla/third-party DayZ warnings about CfgWorlds/CfgVehicles No entry are classified separately from DeutschZ compile/signature failures."
    )
    Set-Content -LiteralPath (Join-Path $docs "ASSET_WORKFLOW_CANVA_ADOBE.md") -Encoding UTF8 -Value @(
        "# Asset Workflow: Canva / Adobe",
        "",
        "- Canva: Workshop banners, event overview cards, load-order graphics, OperationDeutschZ campaign board, Discord/social posts.",
        "- Adobe/Photoshop: PAA texture preparation, item icons, UV-safe retextures, crate/keycard/insignia designs.",
        "- Do not copy third-party logos, workshop images, or assets without explicit permission.",
        "- For texture work: preserve original pixel size, no crop, no rotation, keep UV layout intact."
    )
    Set-Content -LiteralPath (Join-Path $docs "GITHUB_CODERABBIT_DRIVE_WORKFLOW.md") -Encoding UTF8 -Value @(
        "# GitHub / CodeRabbit / Google Drive Workflow",
        "",
        "- GitHub remains the source of truth for code.",
        "- Use branches per fix and clean commits for testserver releases.",
        "- CodeRabbit can review PR diffs for config.cpp, hooks, JSON handling, null checks and risky changes.",
        "- Google Drive is for backups, screenshots, log packages, design files and release-package sharing, not source of truth.",
        "- Do not commit $temp, PBOs, bisigns, bikeys, or workshop files unless Patrick explicitly asks."
    )

    Add-ReportLine $PackageReport "Online-Testserver-Paket erzeugt: $packageRoot"
    return $packageRoot
}

for ($round = 1; $round -le $Rounds; $round++) {
    $runDir = New-RunDirectory
    $sourceReport = Join-Path $runDir "source_validation_report.txt"
    $requiredAddonsReport = Join-Path $runDir "required_addons_report.txt"
    $configCppReport = Join-Path $runDir "config_cpp_report.txt"
    $buildReport = Join-Path $runDir "build_report.txt"
    $deployReport = Join-Path $runDir "deploy_report.txt"
    $serverReport = Join-Path $runDir "server_start_report.txt"
    $configReport = Join-Path $runDir "config_creation_report.txt"
    $operationReport = Join-Path $runDir "operation_deutschz_report.txt"
    $packageReport = Join-Path $runDir "online_testserver_package_report.txt"

    Set-Report $sourceReport "DeutschZ Source Validation Report Runde $round"
    Set-Report $requiredAddonsReport "DeutschZ RequiredAddons Report Runde $round"
    Set-Report $configCppReport "DeutschZ Config.cpp Report Runde $round"
    Set-Report $buildReport "DeutschZ Build Report Runde $round"
    Set-Report $deployReport "DeutschZ Deploy Report Runde $round"
    Set-Report $serverReport "DeutschZ Server Start Report Runde $round"
    Set-Report $configReport "DeutschZ Config Creation Report Runde $round"
    Set-Report $operationReport "DeutschZ OperationDeutschZ Report Runde $round"
    Set-Report $packageReport "DeutschZ Online-Testserver Package Report Runde $round"
    foreach ($logName in @("latest_script.log", "latest_error.log", "latest_rpt.log", "latest_console.log")) {
        Set-Content -LiteralPath (Join-Path $runDir $logName) -Value "Log noch nicht erzeugt." -Encoding UTF8
    }

    try {
        Add-ReportLine $sourceReport "Mode: $Mode"
        Add-ReportLine $sourceReport "RunDir: $runDir"
        Assert-PipelineReadiness -Report $sourceReport

        foreach ($mod in $AllMods) {
            Test-ModSource -ModName $mod -Report $sourceReport -ConfigReport $configCppReport
            Test-RequiredAddonsPolicy -ModName $mod -RequiredReport $requiredAddonsReport
        }

        if ($Mode -eq "Validate") {
            Write-Host "Validate fertig. Report: $runDir"
            continue
        }

        $key = Ensure-SigningKey -Report $buildReport

        if ($Mode -in @("Full", "Build", "Package")) {
            foreach ($mod in $AllMods) {
                Remove-OldArtifacts -ModName $mod -Report $deployReport
                Build-Mod -ModName $mod -Key $key -BuildReport $buildReport
                Deploy-Mod -ModName $mod -Key $key -DeployReport $deployReport
            }
        }

        $serverResult = $null
        if ($Mode -in @("Full", "Test")) {
            $serverResult = Start-ServerBatchAndMonitor -RunDir $runDir -ServerReport $serverReport -ConfigReport $configReport -OperationReport $operationReport
            Add-ReportLine $serverReport "Hard pattern count: $($serverResult.HardMatches)"
            Add-ReportLine $serverReport "Known warning count: $($serverResult.KnownWarnings)"
            Add-ReportLine $serverReport "Operation safe boot: $($serverResult.OperationSafeBoot)"
        }

        if ($Mode -in @("Full", "Package")) {
            if (-not $serverResult) {
                $serverResultText = "Package mode: no local server test was requested in this run."
            } else {
                $serverResultText = @(
                    "Server batch: $($serverResult.BatchPath)",
                    "Profile path: $($serverResult.ProfilePath)",
                    "Server alive after test window: $($serverResult.Alive)",
                    "Hard pattern count: $($serverResult.HardMatches)",
                    "Known warning count: $($serverResult.KnownWarnings)",
                    "OperationDeutschZ in batch: $($serverResult.OperationInBatch)",
                    "OperationDeutschZ safe boot: $($serverResult.OperationSafeBoot)"
                ) -join [Environment]::NewLine
            }
            $packageRoot = New-OnlinePackage -Key $key -PackageReport $packageReport -ServerResultText $serverResultText
            Add-ReportLine $packageReport "PackageRoot: $packageRoot"
        }

        Write-Host "Runde $round fertig. Report: $runDir"
    } catch {
        Add-ReportLine $sourceReport "FEHLER: $($_.Exception.Message)"
        Add-ReportLine $requiredAddonsReport "FEHLER: $($_.Exception.Message)"
        Add-ReportLine $configCppReport "FEHLER: $($_.Exception.Message)"
        Add-ReportLine $buildReport "FEHLER: $($_.Exception.Message)"
        Add-ReportLine $deployReport "FEHLER: $($_.Exception.Message)"
        Add-ReportLine $serverReport "FEHLER: $($_.Exception.Message)"
        Add-ReportLine $configReport "FEHLER: $($_.Exception.Message)"
        Add-ReportLine $operationReport "FEHLER: $($_.Exception.Message)"
        Add-ReportLine $packageReport "FEHLER: $($_.Exception.Message)"
        Write-Error $_
        break
    }
}
