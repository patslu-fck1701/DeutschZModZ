Set-StrictMode -Version Latest

function Get-DZSMRoot {
    param([string]$ScriptRoot)
    $root = Resolve-Path (Join-Path $ScriptRoot '..') -ErrorAction SilentlyContinue
    if ($root) { return $root.Path }
    return (Split-Path -Parent $ScriptRoot)
}

function Read-DZSMPathsConfig {
    param([string]$DzsmRoot)
    $path = Join-Path $DzsmRoot 'config\DZSM_PATHS.json'
    if (-not (Test-Path -LiteralPath $path)) {
        throw "DZSM paths config missing: $path"
    }
    return Get-Content -LiteralPath $path -Raw -Encoding UTF8 | ConvertFrom-Json
}

function New-DZSMReportPaths {
    param($Config)
    $reportsRoot = $Config.ReportsRoot
    $uploadDir = Split-Path -Parent $Config.UploadForChatGPT
    New-Item -ItemType Directory -Force -Path $reportsRoot | Out-Null
    New-Item -ItemType Directory -Force -Path $uploadDir | Out-Null
    $stamp = Get-Date -Format 'yyyy-MM-dd_HH-mm-ss'
    return [pscustomobject]@{
        Stamp = $stamp
        ReportTxt = Join-Path $reportsRoot "DZSM_FIX25_PATH_REPORT_$stamp.txt"
        ReportJson = Join-Path $reportsRoot "DZSM_FIX25_PATH_REPORT_$stamp.json"
        UploadZip = $Config.UploadForChatGPT
        TempDir = Join-Path $reportsRoot "_DZSM_FIX25_UPLOAD_$stamp"
    }
}

function Add-DZSMFinding {
    param(
        [System.Collections.Generic.List[object]]$List,
        [ValidateSet('OK','WARN','ERROR','INFO')] [string]$Level,
        [string]$Area,
        [string]$Message,
        [string]$Path = ''
    )
    $List.Add([pscustomobject]@{
        Level = $Level
        Area = $Area
        Message = $Message
        Path = $Path
    }) | Out-Null
}

function Test-DZSMPathReadable {
    param(
        [System.Collections.Generic.List[object]]$Findings,
        [string]$Area,
        [string]$Path,
        [bool]$Required = $true
    )
    if ([string]::IsNullOrWhiteSpace($Path)) {
        Add-DZSMFinding $Findings 'ERROR' $Area 'Path is empty.' $Path
        return $false
    }
    if (Test-Path -LiteralPath $Path) {
        Add-DZSMFinding $Findings 'OK' $Area 'Path exists.' $Path
        return $true
    }
    if ($Required) {
        Add-DZSMFinding $Findings 'ERROR' $Area 'Required path missing or not reachable.' $Path
    } else {
        Add-DZSMFinding $Findings 'WARN' $Area 'Optional path missing or not reachable.' $Path
    }
    return $false
}

function Get-DZSMChildPathInfo {
    param([string]$Path)
    if (-not (Test-Path -LiteralPath $Path)) { return $null }
    try {
        $item = Get-Item -LiteralPath $Path -ErrorAction Stop
        return [pscustomobject]@{
            FullName = $item.FullName
            Name = $item.Name
            Exists = $true
            LastWriteTime = $item.LastWriteTime
            Length = if ($item.PSIsContainer) { 0 } else { $item.Length }
            IsDirectory = [bool]$item.PSIsContainer
        }
    } catch {
        return [pscustomobject]@{
            FullName = $Path
            Name = Split-Path -Leaf $Path
            Exists = $false
            LastWriteTime = $null
            Length = 0
            IsDirectory = $false
            Error = $_.Exception.Message
        }
    }
}

function Test-DZSMModline {
    param(
        [System.Collections.Generic.List[object]]$Findings,
        [string]$Modline
    )
    if ([string]::IsNullOrWhiteSpace($Modline)) {
        Add-DZSMFinding $Findings 'ERROR' 'Modlist' 'Modlist is empty.'
        return
    }
    if ($Modline.StartsWith('-mod=')) {
        Add-DZSMFinding $Findings 'ERROR' 'Modlist' 'Modlist must not start with -mod= for hoster modlist field.'
    } else {
        Add-DZSMFinding $Findings 'OK' 'Modlist' 'Modlist has no -mod= prefix.'
    }
    if ($Modline[0] -ne '@') {
        Add-DZSMFinding $Findings 'ERROR' 'Modlist' 'Modlist must start directly with @CF. Check BOM/space/invisible chars.'
    } elseif ($Modline.StartsWith('@CF;')) {
        Add-DZSMFinding $Findings 'OK' 'Modlist' 'Modlist starts directly with @CF.'
    } else {
        Add-DZSMFinding $Findings 'WARN' 'Modlist' 'Modlist starts with @ but not @CF; check ordering.'
    }
    $neededOrder = @('@DeutschZ_Core','@DeutschZ_ExpansionBridge','@DeutschZ_KotHZ(InfectedSiege)','@DeutschZ_ConvoyZ','@DeutschZ_Screen_Menu')
    $last = -1
    foreach ($m in $neededOrder) {
        $idx = $Modline.IndexOf($m, [StringComparison]::Ordinal)
        if ($idx -lt 0) {
            Add-DZSMFinding $Findings 'ERROR' 'Modlist' "Missing required DeutschZ mod: $m"
            continue
        }
        if ($idx -lt $last) {
            Add-DZSMFinding $Findings 'ERROR' 'Modlist' "Wrong DeutschZ order near: $m"
        } else {
            Add-DZSMFinding $Findings 'OK' 'Modlist' "Order OK for: $m"
        }
        $last = $idx
    }
}

function Test-DZSMReadyMod {
    param(
        [System.Collections.Generic.List[object]]$Findings,
        [string]$ReadyModsPath,
        $Mod
    )
    $folder = Join-Path $ReadyModsPath $Mod.ReadyFolder
    $exists = Test-DZSMPathReadable $Findings "ReadyMods/$($Mod.Key)" $folder ([bool]$Mod.Required)
    if (-not $exists) { return }

    $addons = Join-Path $folder 'addons'
    if (-not (Test-Path -LiteralPath $addons)) {
        Add-DZSMFinding $Findings 'ERROR' "ReadyMods/$($Mod.Key)" 'addons folder missing.' $addons
        return
    }
    Add-DZSMFinding $Findings 'OK' "ReadyMods/$($Mod.Key)" 'addons folder exists.' $addons

    $pbo = Join-Path $addons ($Mod.ExpectedPboBase + '.pbo')
    if (Test-Path -LiteralPath $pbo) {
        Add-DZSMFinding $Findings 'OK' "ReadyMods/$($Mod.Key)" "Expected PBO found: $($Mod.ExpectedPboBase).pbo" $pbo
    } else {
        $anyPbo = Get-ChildItem -LiteralPath $addons -Filter '*.pbo' -File -ErrorAction SilentlyContinue | Select-Object -First 10
        if ($anyPbo) {
            Add-DZSMFinding $Findings 'WARN' "ReadyMods/$($Mod.Key)" "Expected PBO name not found, but other PBO exists: $($anyPbo[0].Name)" $addons
        } else {
            Add-DZSMFinding $Findings 'ERROR' "ReadyMods/$($Mod.Key)" 'No PBO found in addons.' $addons
        }
    }

    $badSourceFolders = @('scripts','Script','Scripts','config.cpp')
    foreach ($bad in $badSourceFolders) {
        $badPath = Join-Path $folder $bad
        if (Test-Path -LiteralPath $badPath) {
            Add-DZSMFinding $Findings 'WARN' "ReadyMods/$($Mod.Key)" "Source-like entry found in Ready Mods root: $bad" $badPath
        }
    }
}

function Test-DZSMSourceMod {
    param(
        [System.Collections.Generic.List[object]]$Findings,
        [string]$SourceFilesPath,
        $Mod,
        [array]$ForbiddenLegacyNames
    )
    $folder = Join-Path $SourceFilesPath $Mod.SourceFolder
    $exists = Test-DZSMPathReadable $Findings "SourceFiles/$($Mod.Key)" $folder ([bool]$Mod.Required)
    if (-not $exists) { return }

    $hasConfig = Test-Path -LiteralPath (Join-Path $folder 'config.cpp')
    $hasScripts = Test-Path -LiteralPath (Join-Path $folder 'scripts')
    if ($hasConfig) { Add-DZSMFinding $Findings 'OK' "SourceFiles/$($Mod.Key)" 'config.cpp found.' (Join-Path $folder 'config.cpp') }
    else { Add-DZSMFinding $Findings 'WARN' "SourceFiles/$($Mod.Key)" 'config.cpp not found at source root.' $folder }
    if ($hasScripts) { Add-DZSMFinding $Findings 'OK' "SourceFiles/$($Mod.Key)" 'scripts folder found.' (Join-Path $folder 'scripts') }
    else { Add-DZSMFinding $Findings 'WARN' "SourceFiles/$($Mod.Key)" 'scripts folder not found at source root.' $folder }

    foreach ($legacy in $ForbiddenLegacyNames) {
        try {
            $hit = Get-ChildItem -LiteralPath $folder -Recurse -Force -ErrorAction SilentlyContinue |
                Where-Object { $_.Name -like "*$legacy*" -or $_.FullName -like "*$legacy*" } |
                Select-Object -First 1
            if ($hit) {
                Add-DZSMFinding $Findings 'WARN' "SourceFiles/$($Mod.Key)" "Legacy name detected: $legacy" $hit.FullName
            }
        } catch {
            Add-DZSMFinding $Findings 'WARN' "SourceFiles/$($Mod.Key)" "Legacy scan failed for $legacy : $($_.Exception.Message)" $folder
        }
    }
}

function Write-DZSMReports {
    param(
        $Config,
        $ReportPaths,
        [System.Collections.Generic.List[object]]$Findings,
        [hashtable]$Meta
    )
    $summary = [pscustomobject]@{
        GeneratedAt = (Get-Date).ToString('s')
        Version = $Config.Version
        Meta = $Meta
        Counts = [pscustomobject]@{
            OK = ($Findings | Where-Object Level -eq 'OK').Count
            WARN = ($Findings | Where-Object Level -eq 'WARN').Count
            ERROR = ($Findings | Where-Object Level -eq 'ERROR').Count
            INFO = ($Findings | Where-Object Level -eq 'INFO').Count
        }
        Findings = $Findings
    }
    $summary | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $ReportPaths.ReportJson -Encoding UTF8

    $lines = New-Object System.Collections.Generic.List[string]
    $lines.Add('DZSM FIX25 PATH REPORT') | Out-Null
    $lines.Add('GeneratedAt: ' + $summary.GeneratedAt) | Out-Null
    $lines.Add('Version: ' + $Config.Version) | Out-Null
    $lines.Add('') | Out-Null
    $lines.Add(('Counts: OK={0} WARN={1} ERROR={2} INFO={3}' -f $summary.Counts.OK,$summary.Counts.WARN,$summary.Counts.ERROR,$summary.Counts.INFO)) | Out-Null
    $lines.Add('') | Out-Null
    foreach ($f in $Findings) {
        $line = '[{0}] {1} - {2}' -f $f.Level, $f.Area, $f.Message
        if ($f.Path) { $line += ' | ' + $f.Path }
        $lines.Add($line) | Out-Null
    }
    $lines | Set-Content -LiteralPath $ReportPaths.ReportTxt -Encoding UTF8

    if (Test-Path -LiteralPath $ReportPaths.TempDir) { Remove-Item -LiteralPath $ReportPaths.TempDir -Recurse -Force }
    New-Item -ItemType Directory -Force -Path $ReportPaths.TempDir | Out-Null
    Copy-Item -LiteralPath $ReportPaths.ReportTxt -Destination (Join-Path $ReportPaths.TempDir (Split-Path -Leaf $ReportPaths.ReportTxt)) -Force
    Copy-Item -LiteralPath $ReportPaths.ReportJson -Destination (Join-Path $ReportPaths.TempDir (Split-Path -Leaf $ReportPaths.ReportJson)) -Force
    $configCopy = Join-Path $ReportPaths.TempDir 'DZSM_PATHS.json'
    ($Config | ConvertTo-Json -Depth 8) | Set-Content -LiteralPath $configCopy -Encoding UTF8

    $modlistSource = Join-Path $Config.DZSMRoot $Config.PhaseAModListFile
    if (Test-Path -LiteralPath $modlistSource) {
        Copy-Item -LiteralPath $modlistSource -Destination (Join-Path $ReportPaths.TempDir 'PhaseA_Current_Modlist.txt') -Force
    }
    if (Test-Path -LiteralPath $ReportPaths.UploadZip) { Remove-Item -LiteralPath $ReportPaths.UploadZip -Force }
    Compress-Archive -Path (Join-Path $ReportPaths.TempDir '*') -DestinationPath $ReportPaths.UploadZip -Force
    Remove-Item -LiteralPath $ReportPaths.TempDir -Recurse -Force

    return $summary
}
