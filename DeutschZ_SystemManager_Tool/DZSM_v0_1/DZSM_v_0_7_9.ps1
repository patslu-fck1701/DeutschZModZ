#requires -Version 5.1
# DeutschZ System Manager - v0.7.9 FIX37 INPUT_DISCORD_DONE_SUMMARY
# Safe scope: D:\DeutschZ_System_Manager + final UNC live paths + read-only repo source check. No build. No git write. No repo fallback.

$ErrorActionPreference = "Continue"
try { [Console]::OutputEncoding = [System.Text.Encoding]::UTF8 } catch {}

$Version = "v0.7.9 FIX37 INPUT_DISCORD_DONE_SUMMARY"
$SafeName = "DZSM_v_0_7_9"

$Root = "D:\DeutschZ_System_Manager"
$ToolDir = Join-Path $Root "DZSM_v0_1"
$ReportsRoot = Join-Path $Root "reports"
$UploadDir = Join-Path $ReportsRoot "_UPLOAD_FUER_CHATGPT"
$ArchiveRoot = Join-Path $ToolDir "_archive_old_versions"
$RunStamp = Get-Date -Format "yyyy-MM-dd_HH-mm-ss"
$RunArchive = Join-Path $ArchiveRoot ("archive_" + $RunStamp)
$RunLog = Join-Path $Root "DZSM_v_0_7_9_RUN.log"
$StartLog = Join-Path $Root "DZSM_v_0_7_9_START.log"

$LiveRoot = "\\DESKTOP-9P1CO5V\Users\Public\DayZ_Settings\Neue"
$LiveSourceFilesPath = "\\DESKTOP-9P1CO5V\Users\Public\DayZ_Settings\Neue\Source Files"
$LiveReadyModsPath = "\\DESKTOP-9P1CO5V\Users\Public\DayZ_Settings\Neue\Ready Mods"
$LiveMissionCePath = "\\DESKTOP-9P1CO5V\Users\Public\DayZ_Settings\Neue\mpmission\dayzOffline.chernarusplus"
$LiveProfilesPath = "\\DESKTOP-9P1CO5V\Users\Public\DayZ_Settings\Neue\profiles"
$LiveLogsPath = "\\DESKTOP-9P1CO5V\Users\Public\DayZ_Settings\Neue\Logs"

$PDriveLetter = "P:"
$PDriveRoot = "P:\"
$PDriveSubstSource = "C:\Users\patsl\Documents\DayZ Projects"
$DayZToolsSteamAppId = "830640"

$SafeServerSettingsExportFolderName = "SERVERSETTINGS_SAFE_EXPORT"
$SafeServerSettingsExportZipName = "SERVERSETTINGS_SAFE_EXPORT.zip"
$PhaseAFolderName = "PHASE_A_READY_TO_COPY"
$PhaseAZipName = "PHASE_A_READY_TO_COPY.zip"
$UploadZipName = "DZSM_UPLOAD_PACKAGE.zip"
$CeEventFixFolderName = "CE_EVENT_FIX_READY_TO_COPY"
$TypesPresetFolderName = "TYPES_PRESET_READY_TO_COPY"
$TypesBaselineFolderName = "STANDARD_TYPES_BASELINE"
$TypesBaselineRoot = Join-Path $ToolDir $TypesBaselineFolderName
$VanillaTypesPath = "\\DESKTOP-9P1CO5V\Users\Public\DayZ_Settings\Neue\Vanilla_types.xml"
$GitRepoPath = "P:\GitHub_DeutschZModZ\DeutschZModZ"
$RepoCurrentSourcePath = "P:\GitHub_DeutschZModZ\DeutschZModZ\DeutschZModZ"
$GitPlanFolderName = "GITHUB_SYNC_PLAN"
$GitHubInboxFolderName = "_DZSM_INBOX"
$CommitMessageFileName = "GITHUB_COMMIT_MESSAGE.txt"
$UploadSlimFolderName = "_DZSM_UPLOAD_SLIM_CONTENT"
$VehicleSpawnFolderName = "VEHICLE_SPAWN_READY_TO_COPY"
$ServerToolSettingsFolderName = "ServerToolSettings"
$ServerToolSettingsDir = Join-Path $ToolDir $ServerToolSettingsFolderName
$WebhookSettingsFileName = "webhooks.txt"
$WebhookSettingsFile = Join-Path $ServerToolSettingsDir $WebhookSettingsFileName
$DesktopFileOutputFolderName = "Datei Ausgabe"
$DesktopFileOutputArchiveFolderName = "Datei Ausgabe Archiv"
$VanillaEventsPath = "\\DESKTOP-9P1CO5V\Users\Public\DayZ_Settings\Neue\Vanilla_events.xml"
$LogFreshnessMinutes = 30

$Global:SelectedTypesPreset = "ALL"
$Global:SelectedVehicleSpawnPreset = "ALL"
$Global:LogAnalysisStatus = "NOT_RUN"
$Global:LogAnalysisSummaryText = ""
$Global:DiscordSendStatus = "NOT_RUN"
$Global:WebhookCheckStatus = "NOT_RUN"
$Global:GitHubPreparationMode = "NOT_RUN"

$Global:HadError = $false
$Global:Warnings = New-Object System.Collections.Generic.List[string]
$Global:ReportFiles = New-Object System.Collections.Generic.List[string]

function Ensure-Dir {
    param([string]$PathValue)
    if (-not [string]::IsNullOrWhiteSpace($PathValue)) {
        if (-not (Test-Path -LiteralPath $PathValue)) {
            New-Item -ItemType Directory -Path $PathValue -Force | Out-Null
        }
    }
}

function Write-Utf8NoBom {
    param([string]$PathValue, [string]$Text)
    $parent = Split-Path -Parent $PathValue
    Ensure-Dir $parent
    $enc = New-Object System.Text.UTF8Encoding($false)
    [System.IO.File]::WriteAllText($PathValue, $Text, $enc)
}

function Add-Report {
    param([string]$Name, [System.Collections.Generic.List[string]]$Lines)
    $path = Join-Path $UploadDir $Name
    Write-Utf8NoBom -PathValue $path -Text (($Lines -join [Environment]::NewLine) + [Environment]::NewLine)
    $Global:ReportFiles.Add($path) | Out-Null
}

function Append-Log {
    param([string]$Text)
    $line = "[" + (Get-Date -Format "yyyy-MM-dd HH:mm:ss") + "] " + $Text
    Add-Content -LiteralPath $RunLog -Value $line -Encoding UTF8
}

function Write-Status {
    param([string]$Text, [string]$Color = "Gray")
    try { Write-Host $Text -ForegroundColor $Color } catch { Write-Host $Text }
    Append-Log $Text
}

function Add-Warn {
    param([string]$Text)
    $Global:Warnings.Add($Text) | Out-Null
    Write-Status ("WARN: " + $Text) "Yellow"
}


function Get-DZSMDesktopPath {
    try {
        $desktop = [Environment]::GetFolderPath("Desktop")
        if (-not [string]::IsNullOrWhiteSpace($desktop) -and (Test-Path -LiteralPath $desktop)) { return $desktop }
    } catch {}
    try {
        $shell = New-Object -ComObject WScript.Shell
        $desktop = $shell.SpecialFolders.Item("Desktop")
        if (-not [string]::IsNullOrWhiteSpace($desktop) -and (Test-Path -LiteralPath $desktop)) { return $desktop }
    } catch {}
    return Join-Path $env:USERPROFILE "Desktop"
}

function New-DZSMShortcut {
    param(
        [string]$ShortcutPath,
        [string]$TargetPath,
        [string]$WorkingDirectory,
        [string]$IconPath,
        [string]$Description
    )
    try {
        $parent = Split-Path -Parent $ShortcutPath
        Ensure-Dir $parent
        $shell = New-Object -ComObject WScript.Shell
        $lnk = $shell.CreateShortcut($ShortcutPath)
        $lnk.TargetPath = $TargetPath
        if (-not [string]::IsNullOrWhiteSpace($WorkingDirectory)) { $lnk.WorkingDirectory = $WorkingDirectory }
        if (-not [string]::IsNullOrWhiteSpace($IconPath) -and (Test-Path -LiteralPath $IconPath)) { $lnk.IconLocation = $IconPath }
        if (-not [string]::IsNullOrWhiteSpace($Description)) { $lnk.Description = $Description }
        $lnk.Save()
        return $true
    } catch {
        Add-Warn ("Desktop-Shortcut konnte nicht erstellt werden: " + $ShortcutPath + " :: " + $_.Exception.Message)
        return $false
    }
}

function Remove-OldDesktopArtifacts {
    param([string]$DesktopPath)
    try {
        foreach ($name in @("Analyse Starten.lnk", "DZSM Uploadpaket.lnk", "DZSM_UPLOAD_PACKAGE.lnk")) {
            $p = Join-Path $DesktopPath $name
            if (Test-Path -LiteralPath $p) { Remove-Item -LiteralPath $p -Force -ErrorAction SilentlyContinue }
        }
        foreach ($f in Get-ChildItem -LiteralPath $DesktopPath -Filter "DZSM_UPLOAD_PACKAGE*.zip" -File -ErrorAction SilentlyContinue) {
            Remove-Item -LiteralPath $f.FullName -Force -ErrorAction SilentlyContinue
        }
        foreach ($f in Get-ChildItem -LiteralPath $DesktopPath -Filter "DZSM_v_*.lnk" -File -ErrorAction SilentlyContinue) {
            Remove-Item -LiteralPath $f.FullName -Force -ErrorAction SilentlyContinue
        }
    } catch {}
}

function Install-DesktopStartShortcut {
    $desktop = Get-DZSMDesktopPath
    Remove-OldDesktopArtifacts -DesktopPath $desktop
    $batPath = Join-Path $ToolDir ($SafeName + ".bat")
    $iconPath = Join-Path $ToolDir "icons\\DZSM_Analyse_GlassGreen.ico"
    $shortcut = Join-Path $desktop "Analyse Starten.lnk"
    $ok = New-DZSMShortcut -ShortcutPath $shortcut -TargetPath $batPath -WorkingDirectory $ToolDir -IconPath $iconPath -Description "DeutschZ System Manager Analyse starten"
    if ($ok) { Write-Status ("Desktop-Shortcut erstellt: " + $shortcut) "Green" }
}

function Publish-DesktopUploadPackage {
    param([string]$UploadPackagePath)
    $desktop = Get-DZSMDesktopPath
    if ([string]::IsNullOrWhiteSpace($UploadPackagePath) -or -not (Test-Path -LiteralPath $UploadPackagePath)) {
        Add-Warn "DZSM_UPLOAD_PACKAGE.zip konnte nicht auf den Desktop kopiert werden, weil das Uploadpaket fehlt."
        return ""
    }
    try {
        foreach ($f in Get-ChildItem -LiteralPath $desktop -Filter "DZSM_UPLOAD_PACKAGE*.zip" -File -ErrorAction SilentlyContinue) {
            Remove-Item -LiteralPath $f.FullName -Force -ErrorAction SilentlyContinue
        }
        $dest = Join-Path $desktop "DZSM_UPLOAD_PACKAGE.zip"
        Copy-Item -LiteralPath $UploadPackagePath -Destination $dest -Force
        $iconPath = Join-Path $ToolDir "icons\\DZSM_Upload_GlassGreen.ico"
        $shortcut = Join-Path $desktop "DZSM Uploadpaket.lnk"
        $null = New-DZSMShortcut -ShortcutPath $shortcut -TargetPath $dest -WorkingDirectory $desktop -IconPath $iconPath -Description "Aktuelles DZSM Uploadpaket fuer ChatGPT"
        Write-Status ("Uploadpaket auf Desktop aktualisiert: " + $dest) "Green"
        return $dest
    } catch {
        Add-Warn ("DZSM_UPLOAD_PACKAGE.zip konnte nicht auf den Desktop kopiert werden: " + $_.Exception.Message)
        return ""
    }
}

function Ensure-PDriveAndDayZTools {
    $lines = New-Object System.Collections.Generic.List[string]
    $lines.Add("09 P DRIVE / DAYZ TOOLS STATUS") | Out-Null
    $lines.Add("==============================") | Out-Null
    $lines.Add("PDriveRoot: $PDriveRoot") | Out-Null
    $lines.Add("SubstSource: $PDriveSubstSource") | Out-Null
    $lines.Add("DayZToolsSteamAppId: $DayZToolsSteamAppId") | Out-Null
    $lines.Add("") | Out-Null

    if (Test-Path -LiteralPath $PDriveRoot) {
        $lines.Add("OK: P: existiert bereits. Mount und DayZ Tools Start werden uebersprungen.") | Out-Null
        Write-Status "P: existiert bereits - Mount/DayZ Tools werden uebersprungen." "Green"
        return $lines
    }

    $lines.Add("INFO: P: fehlt. SUBST-Mount wird versucht.") | Out-Null
    Write-Status "P: fehlt - versuche SUBST Mount." "Yellow"

    if (Test-Path -LiteralPath $PDriveSubstSource) {
        try {
            $cmd = 'subst P: "' + $PDriveSubstSource + '"'
            $lines.Add("CMD: " + $cmd) | Out-Null
            cmd.exe /c $cmd | Out-Null
            Start-Sleep -Seconds 1
        } catch {
            $lines.Add("WARN: SUBST Exception: " + $_.Exception.Message) | Out-Null
            Add-Warn ("P: SUBST fehlgeschlagen: " + $_.Exception.Message)
        }
    } else {
        $lines.Add("WARN: SubstSource nicht gefunden: " + $PDriveSubstSource) | Out-Null
        Add-Warn ("P: SubstSource nicht gefunden: " + $PDriveSubstSource)
    }

    if (Test-Path -LiteralPath $PDriveRoot) {
        $lines.Add("OK: P: wurde erfolgreich gemountet. DayZ Tools Start wird uebersprungen.") | Out-Null
        Write-Status "P: erfolgreich gemountet - DayZ Tools Start wird uebersprungen." "Green"
        return $lines
    }

    $lines.Add("WARN: P: nach SUBST weiterhin nicht vorhanden. DayZ Tools wird als Fallback gestartet.") | Out-Null
    Add-Warn "P: fehlt weiterhin nach SUBST. DayZ Tools wird als Fallback gestartet."
    try {
        Start-Process ("steam://rungameid/" + $DayZToolsSteamAppId) | Out-Null
        $lines.Add("OK: DayZ Tools Start angefordert via steam://rungameid/" + $DayZToolsSteamAppId) | Out-Null
        Write-Status "DayZ Tools Start angefordert." "Yellow"
        Start-Sleep -Seconds 5
        if (Test-Path -LiteralPath $PDriveRoot) {
            $lines.Add("OK: P: ist nach DayZ Tools Start vorhanden.") | Out-Null
        } else {
            $lines.Add("WARN: P: ist auch nach DayZ Tools Start noch nicht vorhanden.") | Out-Null
        }
    } catch {
        $lines.Add("WARN: DayZ Tools Start fehlgeschlagen: " + $_.Exception.Message) | Out-Null
        Add-Warn ("DayZ Tools Start fehlgeschlagen: " + $_.Exception.Message)
    }
    return $lines
}

function Get-FileSha1 {
    param([string]$PathValue)
    try {
        if (Test-Path -LiteralPath $PathValue) {
            return (Get-FileHash -LiteralPath $PathValue -Algorithm SHA1).Hash
        }
    } catch {}
    return ""
}

function Get-DirStats {
    param([string]$PathValue)
    $result = [ordered]@{ Exists = $false; TopFiles = 0; TopDirs = 0; TopFileBytes = 0 }
    try {
        if (Test-Path -LiteralPath $PathValue) {
            $result.Exists = $true
            $items = Get-ChildItem -LiteralPath $PathValue -Force -ErrorAction SilentlyContinue
            $result.TopFiles = @($items | Where-Object { -not $_.PSIsContainer }).Count
            $result.TopDirs = @($items | Where-Object { $_.PSIsContainer }).Count
            $sum = 0
            foreach ($f in @($items | Where-Object { -not $_.PSIsContainer })) { $sum += [int64]$f.Length }
            $result.TopFileBytes = $sum
        }
    } catch {}
    return $result
}

function Test-XmlFile {
    param([string]$PathValue)
    try {
        [xml]$null = Get-Content -LiteralPath $PathValue -Raw -Encoding UTF8
        return $null
    } catch {
        return $_.Exception.Message
    }
}

function Test-JsonFile {
    param([string]$PathValue)
    try {
        $raw = Get-Content -LiteralPath $PathValue -Raw -Encoding UTF8
        $null = $raw | ConvertFrom-Json
        return $null
    } catch {
        return $_.Exception.Message
    }
}

function Redact-DZSMSensitiveText {
    param([string]$Text)
    if ($null -eq $Text) { return "" }
    $t = [string]$Text
    try { $t = [regex]::Replace($t, '(?i)(RConPassword\s+)([^\r\n\s]+)', '${1}<REDACTED_RCON_PASSWORD>') } catch {}
    try { $t = [regex]::Replace($t, '(?i)("?(?:password|rconpassword|adminpassword|token|secret|apikey|api_key|webhook|webhookurl|discordwebhook)"?\s*[:=]\s*")[^"]*(")', '${1}<REDACTED_SECRET>${2}') } catch {}
    try { $t = [regex]::Replace($t, '(?i)("?(?:password|rconpassword|adminpassword|token|secret|apikey|api_key|webhook|webhookurl|discordwebhook)"?\s*[:=]\s*)[^\r\n,}]+', '${1}<REDACTED_SECRET>') } catch {}
    try { $t = [regex]::Replace($t, '(?i)https://(?:discord|discordapp)\.com/api/webhooks/[^\s"''<>]+', '<REDACTED_DISCORD_WEBHOOK>') } catch {}
    return $t
}

function Copy-DZSMSafeTextFile {
    param([string]$SourcePath, [string]$TargetPath)
    Ensure-Dir (Split-Path -Parent $TargetPath)
    try {
        $raw = Get-Content -LiteralPath $SourcePath -Raw -Encoding UTF8 -ErrorAction Stop
        $safe = Redact-DZSMSensitiveText -Text $raw
        Write-Utf8NoBom -PathValue $TargetPath -Text $safe
    } catch {
        try { Copy-Item -LiteralPath $SourcePath -Destination $TargetPath -Force -ErrorAction Stop } catch {}
    }
}

function Copy-SafeMissionExport {
    param([string]$SourceMission, [string]$TargetMission)
    Ensure-Dir $TargetMission
    if (-not (Test-Path -LiteralPath $SourceMission)) { return }

    $allowedExtensions = @(".xml", ".json", ".c", ".map", ".txt", ".csv")
    $excludeParts = @("\storage_", "\storage\", "\backup\", "\logs\", "\crash", "\adm\", "\players.db", "\script_", "\server_console", "\DayZServer_x64", "\.git\", "\keys\")
    $files = Get-ChildItem -LiteralPath $SourceMission -Recurse -File -Force -ErrorAction SilentlyContinue
    foreach ($f in $files) {
        $fullLower = $f.FullName.ToLowerInvariant()
        $skip = $false
        foreach ($part in $excludeParts) {
            if ($fullLower.Contains($part.ToLowerInvariant())) { $skip = $true; break }
        }
        if ($skip) { continue }
        if ($allowedExtensions -notcontains $f.Extension.ToLowerInvariant()) { continue }

        $rel = $f.FullName.Substring($SourceMission.Length).TrimStart("\")
        $dest = Join-Path $TargetMission $rel
        Copy-DZSMSafeTextFile -SourcePath $f.FullName -TargetPath $dest
    }
}


function Test-DZSMXmlRootName {
    param([string]$PathValue, [string]$ExpectedRoot)
    try {
        [xml]$tmp = Get-Content -LiteralPath $PathValue -Raw -Encoding UTF8
        if ($null -ne $tmp.DocumentElement -and $tmp.DocumentElement.Name.ToLowerInvariant() -eq $ExpectedRoot.ToLowerInvariant()) { return $true }
    } catch {}
    return $false
}

function Get-DZSMTypesRefs {
    param([string]$MissionRoot)
    $result = New-Object System.Collections.Generic.List[object]
    if ([string]::IsNullOrWhiteSpace($MissionRoot) -or -not (Test-Path -LiteralPath $MissionRoot)) { return $result }

    $seen = New-Object 'System.Collections.Generic.HashSet[string]'
    $dbTypes = Join-Path $MissionRoot "db\types.xml"
    if (Test-Path -LiteralPath $dbTypes) {
        $null = $seen.Add("db\types.xml")
        $result.Add([pscustomobject]@{ Rel = "db\types.xml"; Full = $dbTypes; Source = "db"; Kind = "types" }) | Out-Null
    }

    $corePath = Join-Path $MissionRoot "cfgeconomycore.xml"
    if (Test-Path -LiteralPath $corePath) {
        try {
            [xml]$coreXml = Get-Content -LiteralPath $corePath -Raw -Encoding UTF8
            foreach ($ce in @($coreXml.economycore.ce)) {
                $folder = [string]$ce.folder
                foreach ($fileNode in @($ce.file)) {
                    $name = [string]$fileNode.name
                    $type = [string]$fileNode.type
                    if ([string]::IsNullOrWhiteSpace($folder) -or [string]::IsNullOrWhiteSpace($name)) { continue }
                    $rel = ($folder.TrimEnd("\") + "\" + $name.TrimStart("\"))
                    if ($seen.Contains($rel)) { continue }
                    $full = Join-Path $MissionRoot $rel
                    if (-not (Test-Path -LiteralPath $full)) { continue }

                    $isTypes = $false
                    if (-not [string]::IsNullOrWhiteSpace($type) -and $type.ToLowerInvariant() -eq "types") { $isTypes = $true }
                    if (-not $isTypes) { $isTypes = Test-DZSMXmlRootName -PathValue $full -ExpectedRoot "types" }
                    if (-not $isTypes) { continue }

                    $null = $seen.Add($rel)
                    $result.Add([pscustomobject]@{ Rel = $rel; Full = $full; Source = "cfgeconomycore"; Kind = "types" }) | Out-Null
                }
            }
        } catch {
            Add-Warn ("Types Scanner: cfgeconomycore.xml konnte nicht gelesen werden: " + $_.Exception.Message)
        }
    }
    return $result
}


function Copy-DZSMTypesBaselineIfMissing {
    param(
        [System.Collections.Generic.List[object]]$TypeRefs,
        [string]$MissionRoot
    )
    $created = $false
    $filesRoot = Join-Path $TypesBaselineRoot "files"
    $manifestPath = Join-Path $TypesBaselineRoot "STANDARD_TYPES_MANIFEST.csv"
    if (-not (Test-Path -LiteralPath $manifestPath)) {
        if (Test-Path -LiteralPath $TypesBaselineRoot) { Remove-Item -LiteralPath $TypesBaselineRoot -Recurse -Force -ErrorAction SilentlyContinue }
        Ensure-Dir $filesRoot
        foreach ($r in $TypeRefs) {
            $dest = Join-Path $filesRoot $r.Rel
            Ensure-Dir (Split-Path -Parent $dest)
            Copy-Item -LiteralPath $r.Full -Destination $dest -Force
        }
        $core = Join-Path $MissionRoot "cfgeconomycore.xml"
        if (Test-Path -LiteralPath $core) {
            $destCore = Join-Path $filesRoot "cfgeconomycore.xml"
            Copy-Item -LiteralPath $core -Destination $destCore -Force
        }
        $created = $true
    }

    $manifest = New-Object System.Collections.Generic.List[string]
    $manifest.Add("RelativePath,Bytes,SHA1") | Out-Null
    if (Test-Path -LiteralPath $filesRoot) {
        foreach ($f in Get-ChildItem -LiteralPath $filesRoot -Recurse -File -ErrorAction SilentlyContinue) {
            $rel = $f.FullName.Substring($filesRoot.Length).TrimStart("\")
            $manifest.Add(('"{0}",{1},{2}' -f $rel.Replace('"','""'), $f.Length, (Get-FileSha1 $f.FullName))) | Out-Null
        }
    }
    Write-Utf8NoBom $manifestPath (($manifest -join [Environment]::NewLine) + [Environment]::NewLine)
    return $created
}


function Read-DZSMMenuChoice {
    param(
        [string]$Choices,
        [string]$Prompt,
        [string]$Fallback = ""
    )
    $cleanChoices = ([string]$Choices).ToUpperInvariant()
    $fallbackClean = ([string]$Fallback).ToUpperInvariant()
    if ([string]::IsNullOrWhiteSpace($cleanChoices)) { return $fallbackClean }

    while ($true) {
        try {
            Write-Host "" -ForegroundColor Gray
            Write-Host "Eingabe wartet. Buchstabe tippen und ENTER druecken. Keine Auto-Auswahl." -ForegroundColor Gray
            if (-not [string]::IsNullOrWhiteSpace($fallbackClean)) {
                Write-Host ("ENTER ohne Buchstabe = " + $fallbackClean) -ForegroundColor DarkGray
            }
            $answer = Read-Host $Prompt
            if ([string]::IsNullOrWhiteSpace($answer)) {
                if (-not [string]::IsNullOrWhiteSpace($fallbackClean)) { return $fallbackClean }
                Write-Host "Keine Eingabe erkannt. Bitte einen Buchstaben eingeben." -ForegroundColor Yellow
                continue
            }
            $c = $answer.Trim().Substring(0,1).ToUpperInvariant()
            if ($cleanChoices.Contains($c)) { return $c }
            Write-Host ("Ungueltige Auswahl '" + $c + "'. Erlaubt: " + ($cleanChoices.ToCharArray() -join "/")) -ForegroundColor Yellow
        } catch {
            Add-Warn ("Menue-Auswahl fehlgeschlagen: " + $_.Exception.Message)
            if (-not [string]::IsNullOrWhiteSpace($fallbackClean)) { return $fallbackClean }
        }
    }
}

function Read-DZSMTypesPresetChoice {
    try {
        Write-Host ""
        Write-Host "╔══════════════════════════════════════════════════════════════════════╗" -ForegroundColor Green
        Write-Host "║                 D E U T S C H Z  -  T Y P E S                    ║" -ForegroundColor Green
        Write-Host "╠══════════════════════════════════════════════════════════════════════╣" -ForegroundColor Green
        Write-Host "║ S = Standard   gespeicherter Standard / aktueller Grundstand        ║" -ForegroundColor Green
        Write-Host "║ H = Hardcore   33 Prozent von Standard                             ║" -ForegroundColor Green
        Write-Host "║ P = PvP        Waffen/Mags/Ammo/Gear x3, Rest 10%, Food bleibt     ║" -ForegroundColor Green
        Write-Host "║ D = Deathmatch Waffen/Mags/Ammo/Gear x6, Rest deaktiviert          ║" -ForegroundColor Green
        Write-Host "║ V = Vanilla    Vanilla_types.xml + EconomyCore Extra-Types aus     ║" -ForegroundColor Green
        Write-Host "║ A = Alle Presets nur erzeugen                                      ║" -ForegroundColor DarkGray
        Write-Host "╚══════════════════════════════════════════════════════════════════════╝" -ForegroundColor Green
        return (Read-DZSMMenuChoice -Choices "SHPDVA" -Prompt "Types Setup waehlen [S/H/P/D/V/A]:" -Fallback "A")
    } catch {
        Add-Warn ("Types Auswahl konnte nicht gelesen werden: " + $_.Exception.Message)
    }
    return "A"
}

function Get-DZSMTypeClass {
    param([string]$TypeName)
    if ([string]::IsNullOrWhiteSpace($TypeName)) { return "Other" }
    $n = $TypeName.ToLowerInvariant()
    $foodKeys = @("food","mfp_","drink","soda","water","mre","apple","pear","plum","banana","rice","beans","cereal","powderedmilk","honey","jam","mushroom","meat","fish","tuna","sardines","peaches","spaghetti","bacon","brisket","salty","cracker","chips","candy","chocolate","cola","kvass","vodka","beer")
    foreach ($k in $foodKeys) { if ($n.Contains($k)) { return "Food" } }

    $combatKeys = @(
        "ammo","bullet","round","cartridge","mag_","magazine","clip","grenade","explosive","detonator","landmine","m67","rgn","rdg",
        "weapon","rifle","gun","pistol","shotgun","sniper","smg","ak","m4","m16","m14","fal","lar","svd","vsd","vss","val","sks","mosin","tundra","winchester","blaze","repeater","scout","aug","famas","glock","fnx","deagle","colt","cz","cr527","mp5","ump","bizon","pp19","saiga","crossbow","snafu","a2",
        "optic","scope","sight","suppressor","silencer","muzzle","buttstock","handguard","bayonet","bipod","grip","rail","light_attachment",
        "vest","plate","carrier","armor","armour","helmet","helm","ballistic","pouch","holster","belt","military","tactical","combat","gorka","nbc","mvs","redos","6sh","body","hammer","nvg","nightvision"
    )
    foreach ($k in $combatKeys) { if ($n.Contains($k)) { return "Combat" } }
    return "Other"
}

function Get-DZSMScaledCeValue {
    param([string]$ValueText, [double]$Factor, [bool]$ForceZero)
    $v = 0
    if (-not [int]::TryParse([string]$ValueText, [ref]$v)) { return $null }
    if ($ForceZero) { return 0 }
    if ($v -le 0) { return 0 }
    $scaled = [int][Math]::Round(([double]$v * $Factor), 0)
    if ($scaled -lt 1) { $scaled = 1 }
    return $scaled
}

function Set-DZSMTypeChildValue {
    param([System.Xml.XmlElement]$TypeNode, [string]$ChildName, [int]$Value)
    try {
        $child = $TypeNode.SelectSingleNode($ChildName)
        if ($null -ne $child) { $child.InnerText = [string]$Value }
    } catch {}
}

function Write-DZSMTypesPresetXml {
    param(
        [string]$SourcePath,
        [string]$TargetPath,
        [string]$PresetName
    )
    Ensure-Dir (Split-Path -Parent $TargetPath)
    if ($PresetName -eq "STANDARD") {
        Copy-Item -LiteralPath $SourcePath -Destination $TargetPath -Force
        return
    }

    [xml]$x = Get-Content -LiteralPath $SourcePath -Raw -Encoding UTF8
    if ($null -eq $x.DocumentElement -or $x.DocumentElement.Name.ToLowerInvariant() -ne "types") {
        Copy-Item -LiteralPath $SourcePath -Destination $TargetPath -Force
        return
    }

    $changed = 0
    foreach ($t in @($x.DocumentElement.SelectNodes("type"))) {
        if ($null -eq $t) { continue }
        $name = [string]$t.GetAttribute("name")
        if ([string]::IsNullOrWhiteSpace($name)) { $name = [string]$t.name }
        $class = Get-DZSMTypeClass -TypeName $name
        $nom = $t.SelectSingleNode("nominal")
        $min = $t.SelectSingleNode("min")
        if ($null -eq $nom -and $null -eq $min) { continue }

        $factor = 1.0
        $forceZero = $false
        if ($PresetName -eq "HARDCORE") {
            $factor = 0.33
        } elseif ($PresetName -eq "PVP") {
            if ($class -eq "Combat") { $factor = 3.0 }
            elseif ($class -eq "Food") { $factor = 1.0 }
            else { $factor = 0.10 }
        } elseif ($PresetName -eq "DEATHMATCH") {
            if ($class -eq "Combat") { $factor = 6.0 }
            else { $forceZero = $true }
        }

        if ($null -ne $nom) {
            $newNom = Get-DZSMScaledCeValue -ValueText $nom.InnerText -Factor $factor -ForceZero $forceZero
            if ($null -ne $newNom) { Set-DZSMTypeChildValue -TypeNode $t -ChildName "nominal" -Value $newNom; $changed++ }
        }
        if ($null -ne $min) {
            $newMin = Get-DZSMScaledCeValue -ValueText $min.InnerText -Factor $factor -ForceZero $forceZero
            if ($null -ne $newMin) { Set-DZSMTypeChildValue -TypeNode $t -ChildName "min" -Value $newMin; $changed++ }
        }
    }
    $x.Save($TargetPath)
}


function Write-DZSMVanillaEconomyCore {
    param([string]$SourceCorePath, [string]$TargetCorePath)
    Ensure-Dir (Split-Path -Parent $TargetCorePath)
    if (-not (Test-Path -LiteralPath $SourceCorePath)) { return $false }
    try {
        [xml]$core = Get-Content -LiteralPath $SourceCorePath -Raw -Encoding UTF8
        foreach ($ce in @($core.economycore.ce)) {
            $folder = [string]$ce.folder
            foreach ($fileNode in @($ce.file)) {
                $name = [string]$fileNode.name
                $type = [string]$fileNode.type
                if ([string]::IsNullOrWhiteSpace($folder) -or [string]::IsNullOrWhiteSpace($name)) { continue }
                $rel = ($folder.TrimEnd("\") + "\" + $name.TrimStart("\"))
                $isTypes = $false
                if (-not [string]::IsNullOrWhiteSpace($type) -and $type.ToLowerInvariant() -eq "types") { $isTypes = $true }
                if (-not $isTypes -and $name.ToLowerInvariant().EndsWith("types.xml")) { $isTypes = $true }
                if ($isTypes -and $rel.ToLowerInvariant() -ne "db\types.xml") {
                    try { $null = $ce.RemoveChild($fileNode) } catch {}
                }
            }
        }
        foreach ($ce in @($core.economycore.ce)) {
            try { if (@($ce.file).Count -eq 0) { $null = $core.economycore.RemoveChild($ce) } } catch {}
        }
        $core.Save($TargetCorePath)
        return $true
    } catch {
        Add-Warn ("Vanilla cfgeconomycore Fehler: " + $_.Exception.Message)
        return $false
    }
}


function Copy-DZSMPresetToSelected {
    param([string]$PresetRoot, [string]$SelectedRoot, [string]$ChoiceName)
    if (Test-Path -LiteralPath $SelectedRoot) { Remove-Item -LiteralPath $SelectedRoot -Recurse -Force -ErrorAction SilentlyContinue }
    Ensure-Dir $SelectedRoot
    if (Test-Path -LiteralPath $PresetRoot) {
        Copy-Item -Path (Join-Path $PresetRoot "*") -Destination $SelectedRoot -Recurse -Force -ErrorAction SilentlyContinue
        Write-Utf8NoBom (Join-Path $SelectedRoot "SELECTED_PRESET.txt") ("Selected preset: $ChoiceName" + [Environment]::NewLine + "DZSM wrote no live files. Copy manually after backup." + [Environment]::NewLine)
    }
}

function Invoke-DZSMTypesPresetScanner {
    param([string]$MissionRoot)

    $report = New-Object System.Collections.Generic.List[string]
    $report.Add("65 TYPES PRESET SCANNER") | Out-Null
    $report.Add("=======================") | Out-Null
    $report.Add("MissionRoot: $MissionRoot") | Out-Null
    $report.Add("VanillaTypesPath: $VanillaTypesPath") | Out-Null
    $report.Add("BaselineRoot: $TypesBaselineRoot") | Out-Null
    $report.Add("Regel: DZSM schreibt NICHT live. Presets werden nur unter TYPES_PRESET_READY_TO_COPY erzeugt.") | Out-Null
    $report.Add("") | Out-Null

    $typesRoot = Join-Path $UploadDir $TypesPresetFolderName
    if (Test-Path -LiteralPath $typesRoot) { Remove-Item -LiteralPath $typesRoot -Recurse -Force -ErrorAction SilentlyContinue }
    Ensure-Dir $typesRoot

    $refs = Get-DZSMTypesRefs -MissionRoot $MissionRoot
    $report.Add("Gefundene Types-Dateien: " + $refs.Count) | Out-Null
    foreach ($r in $refs) { $report.Add("  REF: " + $r.Rel + " | " + $r.Source) | Out-Null }

    if ($refs.Count -eq 0) {
        Add-Warn "Types Scanner: Keine Types-Dateien gefunden."
        Add-Report "65_TYPES_PRESET_SCANNER.txt" $report
        return
    }

    $baselineCreated = Copy-DZSMTypesBaselineIfMissing -TypeRefs $refs -MissionRoot $MissionRoot
    if ($baselineCreated) { $report.Add("STANDARD_BASELINE: CREATED_FROM_CURRENT_RUN") | Out-Null }
    else { $report.Add("STANDARD_BASELINE: EXISTING_REUSED") | Out-Null }

    $baselineFilesRoot = Join-Path $TypesBaselineRoot "files"
    $compare = New-Object System.Collections.Generic.List[string]
    $compare.Add("RelativePath,CurrentSHA1,StandardSHA1,Status") | Out-Null
    $changedCount = 0
    foreach ($r in $refs) {
        $baseFile = Join-Path $baselineFilesRoot $r.Rel
        $curHash = Get-FileSha1 $r.Full
        $baseHash = Get-FileSha1 $baseFile
        $status = "OK_MATCH_STANDARD"
        if ([string]::IsNullOrWhiteSpace($baseHash)) { $status = "MISSING_IN_STANDARD_BASELINE"; $changedCount++ }
        elseif ($curHash -ne $baseHash) { $status = "DIFFERS_FROM_STANDARD"; $changedCount++ }
        $compare.Add(('"{0}",{1},{2},{3}' -f $r.Rel.Replace('"','""'), $curHash, $baseHash, $status)) | Out-Null
    }
    Write-Utf8NoBom (Join-Path $UploadDir "66_TYPES_STANDARD_COMPARE.csv") (($compare -join [Environment]::NewLine) + [Environment]::NewLine)
    $report.Add("Aktuelle Types unterscheiden sich vom gespeicherten Standard: " + $changedCount) | Out-Null

    $choice = Read-DZSMTypesPresetChoice
    $validChoice = $choice
    if (@("S","H","P","D","V","A") -notcontains $validChoice) { $validChoice = "A" }
    $report.Add("Auswahl: " + $validChoice) | Out-Null
    $Global:SelectedTypesPreset = $validChoice

    $presetMap = [ordered]@{
        "STANDARD" = "STANDARD"
        "HARDCORE" = "HARDCORE"
        "PVP" = "PVP"
        "DEATHMATCH" = "DEATHMATCH"
    }
    foreach ($presetName in $presetMap.Keys) {
        $presetRoot = Join-Path $typesRoot $presetName
        Ensure-Dir $presetRoot
        foreach ($r in $refs) {
            $sourceForPreset = $r.Full
            if ($presetName -eq "STANDARD") {
                $candidate = Join-Path $baselineFilesRoot $r.Rel
                if (Test-Path -LiteralPath $candidate) { $sourceForPreset = $candidate }
            }
            $target = Join-Path $presetRoot $r.Rel
            try {
                Write-DZSMTypesPresetXml -SourcePath $sourceForPreset -TargetPath $target -PresetName $presetName
            } catch {
                Add-Warn ("Types Preset $presetName Fehler bei " + $r.Rel + ": " + $_.Exception.Message)
            }
        }
        $readme = @(
            "TYPES PRESET: $presetName",
            "====================",
            "Dieses Paket ist Ready-to-Copy. DZSM hat live nichts geaendert.",
            "Basis: gespeicherter STANDARD_TYPES_BASELINE Stand.",
            "Vor dem Einspielen Server stoppen und Backup machen.",
            "Ziel: Dateien relativ nach mpmission\dayzOffline.chernarusplus kopieren."
        ) -join [Environment]::NewLine
        Write-Utf8NoBom (Join-Path $presetRoot "README_TYPES_PRESET.txt") ($readme + [Environment]::NewLine)
    }

    $vanillaRoot = Join-Path $typesRoot "VANILLA"
    Ensure-Dir $vanillaRoot
    Ensure-Dir (Join-Path $vanillaRoot "db")
    $vanillaOk = $false
    if (Test-Path -LiteralPath $VanillaTypesPath) {
        Copy-Item -LiteralPath $VanillaTypesPath -Destination (Join-Path $vanillaRoot "db\types.xml") -Force
        $vanillaOk = $true
    } else {
        Add-Warn ("Vanilla_types.xml fehlt: " + $VanillaTypesPath)
        $report.Add("VANILLA_TYPES: MISSING") | Out-Null
    }
    $coreSource = Join-Path $MissionRoot "cfgeconomycore.xml"
    $coreTarget = Join-Path $vanillaRoot "cfgeconomycore.xml"
    $coreVanillaOk = Write-DZSMVanillaEconomyCore -SourceCorePath $coreSource -TargetCorePath $coreTarget
    $readmeVanilla = @(
        "TYPES PRESET: VANILLA",
        "=====================",
        "Dieses Paket setzt db\types.xml aus Vanilla_types.xml.",
        "cfgeconomycore.xml wird als Ready-to-Copy erzeugt: zusaetzliche EconomyCore-Types werden entfernt/deaktiviert.",
        "DZSM hat live nichts geaendert.",
        "VanillaTypesPath: $VanillaTypesPath",
        "Vanilla types gefunden: $vanillaOk",
        "Vanilla cfgeconomycore erzeugt: $coreVanillaOk"
    ) -join [Environment]::NewLine
    Write-Utf8NoBom (Join-Path $vanillaRoot "README_TYPES_PRESET.txt") ($readmeVanilla + [Environment]::NewLine)

    $choiceFolder = ""
    if ($validChoice -eq "S") { $choiceFolder = "STANDARD" }
    elseif ($validChoice -eq "H") { $choiceFolder = "HARDCORE" }
    elseif ($validChoice -eq "P") { $choiceFolder = "PVP" }
    elseif ($validChoice -eq "D") { $choiceFolder = "DEATHMATCH" }
    elseif ($validChoice -eq "V") { $choiceFolder = "VANILLA" }
    if (-not [string]::IsNullOrWhiteSpace($choiceFolder)) {
        Copy-DZSMPresetToSelected -PresetRoot (Join-Path $typesRoot $choiceFolder) -SelectedRoot (Join-Path $typesRoot "SELECTED_TYPES_PRESET_TO_COPY") -ChoiceName $choiceFolder
        $report.Add("SELECTED_READY_TO_COPY: " + $choiceFolder) | Out-Null
        $Global:SelectedTypesPreset = $choiceFolder
    } else {
        $report.Add("SELECTED_READY_TO_COPY: NONE_ALL_PRESETS_GENERATED") | Out-Null
        $Global:SelectedTypesPreset = "ALL"
    }

    $manifest = New-Object System.Collections.Generic.List[string]
    $manifest.Add("RelativePath,Bytes,SHA1") | Out-Null
    foreach ($f in Get-ChildItem -LiteralPath $typesRoot -Recurse -File -ErrorAction SilentlyContinue) {
        $rel = $f.FullName.Substring($typesRoot.Length).TrimStart("\")
        $manifest.Add(('"{0}",{1},{2}' -f $rel.Replace('"','""'), $f.Length, (Get-FileSha1 $f.FullName))) | Out-Null
    }
    Write-Utf8NoBom (Join-Path $UploadDir "67_TYPES_PRESET_READY_TO_COPY_MANIFEST.csv") (($manifest -join [Environment]::NewLine) + [Environment]::NewLine)

    $readmeAll = @(
        "TYPES PRESET READY TO COPY",
        "==========================",
        "DZSM schreibt nichts live. Alle Dateien manuell kopieren nach mpmission\dayzOffline.chernarusplus.",
        "STANDARD = gespeicherter Standard vom ersten Scannerlauf.",
        "HARDCORE = 33 Prozent von Standard.",
        "PVP = Combat x3, sonst 10 Prozent, Food bleibt Standard.",
        "DEATHMATCH = Combat x6, Rest deaktiviert.",
        "VANILLA = Vanilla_types.xml nach db\types.xml, EconomyCore Extra-Types entfernt.",
        "SELECTED_TYPES_PRESET_TO_COPY = deine Auswahl aus dem kleinen Auswahlbild, falls Taste gedrueckt wurde."
    ) -join [Environment]::NewLine
    Write-Utf8NoBom (Join-Path $typesRoot "README_TYPES_PRESET_READY_TO_COPY.txt") ($readmeAll + [Environment]::NewLine)

    Add-Report "65_TYPES_PRESET_SCANNER.txt" $report
}


function Get-DZSMWebhookFromFile {
    param([string]$PathValue)
    try {
        if ([string]::IsNullOrWhiteSpace($PathValue) -or -not (Test-Path -LiteralPath $PathValue)) { return "" }
        foreach ($line in Get-Content -LiteralPath $PathValue -ErrorAction SilentlyContinue) {
            $t = ([string]$line).Trim()
            if ($t.StartsWith("#") -or [string]::IsNullOrWhiteSpace($t)) { continue }
            if ($t -match '^DiscordStatusWebhook\s*=\s*(.+)$') { $t = $Matches[1].Trim() }
            if ($t -match '^https://discord\.com/api/webhooks/') { return $t }
        }
    } catch {}
    return ""
}

function Ensure-DZSMServerToolSettings {
    Ensure-Dir $ServerToolSettingsDir
    $template = @(
        "# DeutschZ System Manager Webhooks",
        "# Lokale Datei. Wird NICHT ins Uploadpaket kopiert und NICHT nach GitHub vorbereitet.",
        "# Eintragen als DiscordStatusWebhook=https://discord.com/api/webhooks/...",
        "# Alternativ reicht auch eine rohe Webhook-URL in einer eigenen Zeile.",
        "DiscordStatusWebhook=",
        "",
        "# Discord Invite Links/Steam Links duerfen in Reports bleiben, API-Webhooks werden redacted."
    ) -join [Environment]::NewLine

    if (-not (Test-Path -LiteralPath $WebhookSettingsFile)) {
        Write-Utf8NoBom $WebhookSettingsFile ($template + [Environment]::NewLine)
    }

    $desktop = Get-DZSMDesktopPath
    $desktopWebhookFile = ""
    if (-not [string]::IsNullOrWhiteSpace($desktop)) { $desktopWebhookFile = Join-Path $desktop "DZSM_webhooks.txt" }

    $toolWebhook = Get-DZSMWebhookFromFile -PathValue $WebhookSettingsFile
    $desktopWebhook = ""
    if (-not [string]::IsNullOrWhiteSpace($desktopWebhookFile) -and (Test-Path -LiteralPath $desktopWebhookFile)) {
        $desktopWebhook = Get-DZSMWebhookFromFile -PathValue $desktopWebhookFile
    }

    try {
        if ([string]::IsNullOrWhiteSpace($toolWebhook) -and -not [string]::IsNullOrWhiteSpace($desktopWebhook)) {
            Copy-Item -LiteralPath $desktopWebhookFile -Destination $WebhookSettingsFile -Force -ErrorAction SilentlyContinue
            $toolWebhook = $desktopWebhook
        } elseif (-not [string]::IsNullOrWhiteSpace($toolWebhook)) {
            if (-not [string]::IsNullOrWhiteSpace($desktopWebhookFile)) {
                Copy-Item -LiteralPath $WebhookSettingsFile -Destination $desktopWebhookFile -Force -ErrorAction SilentlyContinue
            }
        } elseif (-not [string]::IsNullOrWhiteSpace($desktopWebhookFile) -and -not (Test-Path -LiteralPath $desktopWebhookFile)) {
            Copy-Item -LiteralPath $WebhookSettingsFile -Destination $desktopWebhookFile -Force -ErrorAction SilentlyContinue
        }
    } catch {}

    $lines = New-Object System.Collections.Generic.List[string]
    $lines.Add("69 SERVER TOOL SETTINGS") | Out-Null
    $lines.Add("=======================") | Out-Null
    $lines.Add("ServerToolSettingsDir: $ServerToolSettingsDir") | Out-Null
    $lines.Add("WebhookSettingsFile: $WebhookSettingsFile") | Out-Null
    $lines.Add("DesktopCopy: DZSM_webhooks.txt") | Out-Null
    if (-not [string]::IsNullOrWhiteSpace($toolWebhook)) { $lines.Add("WebhookSource: CONFIGURED") | Out-Null }
    else { $lines.Add("WebhookSource: NOT_CONFIGURED") | Out-Null }
    $lines.Add("Regel: Webhook-Datei wird nicht ins Uploadpaket kopiert.") | Out-Null
    Add-Report "69_SERVER_TOOL_SETTINGS.txt" $lines
}

function Get-DZSMDiscordWebhook {
    try {
        $toolWebhook = Get-DZSMWebhookFromFile -PathValue $WebhookSettingsFile
        if (-not [string]::IsNullOrWhiteSpace($toolWebhook)) { return $toolWebhook }
        $desktop = Get-DZSMDesktopPath
        if (-not [string]::IsNullOrWhiteSpace($desktop)) {
            $desktopFile = Join-Path $desktop "DZSM_webhooks.txt"
            $desktopWebhook = Get-DZSMWebhookFromFile -PathValue $desktopFile
            if (-not [string]::IsNullOrWhiteSpace($desktopWebhook)) {
                Copy-Item -LiteralPath $desktopFile -Destination $WebhookSettingsFile -Force -ErrorAction SilentlyContinue
                return $desktopWebhook
            }
        }
    } catch {}
    return ""
}

function Test-DZSMDiscordWebhookConfig {
    $lines = New-Object System.Collections.Generic.List[string]
    $lines.Add("76 WEBHOOK CHECK") | Out-Null
    $lines.Add("================") | Out-Null
    $lines.Add("SettingsFile: $WebhookSettingsFile") | Out-Null
    try {
        $webhook = Get-DZSMDiscordWebhook
        if ([string]::IsNullOrWhiteSpace($webhook)) {
            $lines.Add("Status: NO_WEBHOOK_CONFIGURED") | Out-Null
            $lines.Add("Hinweis: DZSM_webhooks.txt auf dem Desktop bearbeiten und DiscordStatusWebhook= setzen.") | Out-Null
            Add-Report "76_WEBHOOK_CHECK.txt" $lines
            return "NO_WEBHOOK_CONFIGURED"
        }
        $redacted = ($webhook -replace '(https://discord\.com/api/webhooks/\d+/).+$', '$1[REDACTED]')
        $lines.Add("WebhookConfigured: True") | Out-Null
        $lines.Add("WebhookRedacted: $redacted") | Out-Null
        try {
            $resp = Invoke-WebRequest -Uri $webhook -Method Get -UseBasicParsing -TimeoutSec 10
            $lines.Add("HTTPStatus: " + $resp.StatusCode) | Out-Null
            if ($resp.StatusCode -ge 200 -and $resp.StatusCode -lt 300) { $lines.Add("Status: OK") | Out-Null; Add-Report "76_WEBHOOK_CHECK.txt" $lines; return "OK" }
            $lines.Add("Status: WARN_HTTP") | Out-Null
            Add-Warn ("Discord Webhook Check HTTP Status: " + $resp.StatusCode)
            Add-Report "76_WEBHOOK_CHECK.txt" $lines
            return "WARN_HTTP"
        } catch {
            $lines.Add("Status: CHECK_ERROR") | Out-Null
            $lines.Add("Error: " + $_.Exception.Message) | Out-Null
            Add-Warn ("Discord Webhook Check fehlgeschlagen: " + $_.Exception.Message)
            Add-Report "76_WEBHOOK_CHECK.txt" $lines
            return "CHECK_ERROR"
        }
    } catch {
        $lines.Add("Status: ERROR") | Out-Null
        $lines.Add("Error: " + $_.Exception.Message) | Out-Null
        Add-Warn ("Discord Webhook Check Fehler: " + $_.Exception.Message)
        Add-Report "76_WEBHOOK_CHECK.txt" $lines
        return "ERROR"
    }
}

function Read-DZSMVehicleSpawnChoice {
    try {
        Write-Host ""
        Write-Host "╔══════════════════════════════════════════════════════════════════════╗" -ForegroundColor Green
        Write-Host "║          D E U T S C H Z  -  F A H R Z E U G S P A W N S          ║" -ForegroundColor Green
        Write-Host "╠══════════════════════════════════════════════════════════════════════╣" -ForegroundColor Green
        Write-Host "║ S = Standard   aktueller gespeicherter Stand                        ║" -ForegroundColor Green
        Write-Host "║ V = Vanilla    Vanilla_events.xml falls vorhanden, sonst Standard   ║" -ForegroundColor Green
        Write-Host "║ E = Erhoeht    Fahrzeug-Events x2                                  ║" -ForegroundColor Green
        Write-Host "║ F = 100 FULL   Fahrzeug-Events active=1, nominal/min auf max        ║" -ForegroundColor Green
        Write-Host "║ A = Alle Varianten nur erzeugen                                    ║" -ForegroundColor DarkGray
        Write-Host "╚══════════════════════════════════════════════════════════════════════╝" -ForegroundColor Green
        return (Read-DZSMMenuChoice -Choices "SVEFA" -Prompt "Fahrzeugspawn Setup waehlen [S/V/E/F/A]:" -Fallback "A")
    } catch {
        Add-Warn ("Fahrzeugspawn Auswahl konnte nicht gelesen werden: " + $_.Exception.Message)
    }
    return "A"
}

function Test-DZSMVehicleEventName {
    param([string]$Name)
    if ([string]::IsNullOrWhiteSpace($Name)) { return $false }
    $n = $Name.ToLowerInvariant()
    $keys = @("vehicle", "sedan", "hatchback", "offroad", "truck", "boat", "civilian", "ada", "olga", "sarka", "gunter", "m3s", "humvee", "helicopter", "heli")
    foreach ($k in $keys) { if ($n.Contains($k)) { return $true } }
    return $false
}

function Get-DZSMIntXmlText {
    param([System.Xml.XmlElement]$Node, [string]$ChildName)
    try {
        $c = $Node.SelectSingleNode($ChildName)
        if ($null -eq $c) { return 0 }
        $v = 0
        if ([int]::TryParse([string]$c.InnerText, [ref]$v)) { return $v }
    } catch {}
    return 0
}

function Set-DZSMEventChildValue {
    param([System.Xml.XmlElement]$EventNode, [string]$ChildName, [int]$Value)
    try {
        $child = $EventNode.SelectSingleNode($ChildName)
        if ($null -eq $child) {
            $child = $EventNode.OwnerDocument.CreateElement($ChildName)
            $null = $EventNode.AppendChild($child)
        }
        $child.InnerText = [string]$Value
    } catch {}
}

function Write-DZSMVehicleEventsPresetXml {
    param([string]$SourcePath, [string]$TargetPath, [string]$PresetName)
    Ensure-Dir (Split-Path -Parent $TargetPath)
    if (-not (Test-Path -LiteralPath $SourcePath)) { return 0 }
    if ($PresetName -eq "STANDARD") {
        Copy-Item -LiteralPath $SourcePath -Destination $TargetPath -Force
        return 0
    }
    [xml]$x = Get-Content -LiteralPath $SourcePath -Raw -Encoding UTF8
    $changed = 0
    foreach ($e in @($x.SelectNodes("//event"))) {
        if ($null -eq $e) { continue }
        $n = [string]$e.GetAttribute("name")
        if (-not (Test-DZSMVehicleEventName -Name $n)) { continue }
        if ($PresetName -eq "ERHOEHT") {
            Set-DZSMEventChildValue -EventNode $e -ChildName "active" -Value 1
            foreach ($child in @("nominal", "min", "max")) {
                $v = Get-DZSMIntXmlText -Node $e -ChildName $child
                if ($v -gt 0) { Set-DZSMEventChildValue -EventNode $e -ChildName $child -Value ([Math]::Max(1, [int][Math]::Round($v * 2.0))) }
            }
            $changed++
        } elseif ($PresetName -eq "FULL100") {
            $max = Get-DZSMIntXmlText -Node $e -ChildName "max"
            $nom = Get-DZSMIntXmlText -Node $e -ChildName "nominal"
            if ($max -le 0) { $max = [Math]::Max($nom, 1) }
            Set-DZSMEventChildValue -EventNode $e -ChildName "active" -Value 1
            Set-DZSMEventChildValue -EventNode $e -ChildName "nominal" -Value $max
            Set-DZSMEventChildValue -EventNode $e -ChildName "min" -Value $max
            Set-DZSMEventChildValue -EventNode $e -ChildName "max" -Value $max
            $changed++
        }
    }
    $x.Save($TargetPath)
    return $changed
}

function Copy-DZSMVehiclePresetToSelected {
    param([string]$PresetRoot, [string]$SelectedRoot, [string]$ChoiceName)
    if (Test-Path -LiteralPath $SelectedRoot) { Remove-Item -LiteralPath $SelectedRoot -Recurse -Force -ErrorAction SilentlyContinue }
    Ensure-Dir $SelectedRoot
    if (Test-Path -LiteralPath $PresetRoot) {
        Copy-Item -Path (Join-Path $PresetRoot "*") -Destination $SelectedRoot -Recurse -Force -ErrorAction SilentlyContinue
        Write-Utf8NoBom (Join-Path $SelectedRoot "SELECTED_VEHICLE_SPAWN.txt") ("Selected vehicle spawn preset: $ChoiceName" + [Environment]::NewLine + "DZSM wrote no live files. Copy manually after backup." + [Environment]::NewLine)
    }
}

function Invoke-DZSMVehicleSpawnSetup {
    param([string]$MissionRoot)
    $root = Join-Path $UploadDir $VehicleSpawnFolderName
    if (Test-Path -LiteralPath $root) { Remove-Item -LiteralPath $root -Recurse -Force -ErrorAction SilentlyContinue }
    Ensure-Dir $root
    $report = New-Object System.Collections.Generic.List[string]
    $report.Add("72 VEHICLE SPAWN SETUP") | Out-Null
    $report.Add("======================") | Out-Null
    $report.Add("MissionRoot: $MissionRoot") | Out-Null
    $report.Add("VanillaEventsPath: $VanillaEventsPath") | Out-Null
    $report.Add("Regel: DZSM schreibt NICHT live. Ready-to-Copy Dateien werden erzeugt.") | Out-Null
    $events = Join-Path $MissionRoot "db\events.xml"
    if (-not (Test-Path -LiteralPath $events)) {
        Add-Warn ("Vehicle Spawn Setup: db/events.xml fehlt: " + $events)
        Add-Report "72_VEHICLE_SPAWN_SETUP.txt" $report
        return
    }
    $choice = Read-DZSMVehicleSpawnChoice
    if (@("S","V","E","F","A") -notcontains $choice) { $choice = "A" }
    $Global:SelectedVehicleSpawnPreset = $choice
    $report.Add("Auswahl: $choice") | Out-Null
    $map = [ordered]@{
        "STANDARD" = "STANDARD"
        "ERHOEHT" = "ERHOEHT"
        "FULL100" = "FULL100"
    }
    foreach ($presetName in $map.Keys) {
        $presetRoot = Join-Path $root $presetName
        Ensure-Dir (Join-Path $presetRoot "db")
        $changed = Write-DZSMVehicleEventsPresetXml -SourcePath $events -TargetPath (Join-Path $presetRoot "db\events.xml") -PresetName $presetName
        Write-Utf8NoBom (Join-Path $presetRoot "README_VEHICLE_SPAWN_PRESET.txt") ((@(
            "VEHICLE SPAWN PRESET: $presetName",
            "==============================",
            "Ready-to-Copy. DZSM hat live nichts geaendert.",
            "Ziel: db\events.xml nach mpmission\dayzOffline.chernarusplus\db\events.xml kopieren.",
            "Geaenderte Fahrzeug-Events: $changed"
        ) -join [Environment]::NewLine) + [Environment]::NewLine)
        $report.Add("Preset $presetName changedVehicleEvents=$changed") | Out-Null
    }
    $vanillaRoot = Join-Path $root "VANILLA"
    Ensure-Dir (Join-Path $vanillaRoot "db")
    if (Test-Path -LiteralPath $VanillaEventsPath) {
        Copy-Item -LiteralPath $VanillaEventsPath -Destination (Join-Path $vanillaRoot "db\events.xml") -Force
        $report.Add("VANILLA: from Vanilla_events.xml") | Out-Null
    } else {
        Copy-Item -LiteralPath $events -Destination (Join-Path $vanillaRoot "db\events.xml") -Force
        $report.Add("VANILLA: Vanilla_events.xml fehlt, Fallback Standard-Kopie") | Out-Null
        Add-Warn ("Vanilla_events.xml fehlt fuer Vehicle-Setup, Fallback Standard: " + $VanillaEventsPath)
    }
    Write-Utf8NoBom (Join-Path $vanillaRoot "README_VEHICLE_SPAWN_PRESET.txt") ((@(
        "VEHICLE SPAWN PRESET: VANILLA",
        "=============================",
        "Wenn Vanilla_events.xml vorhanden ist, wurde diese benutzt. Sonst Standard-Fallback.",
        "DZSM hat live nichts geaendert."
    ) -join [Environment]::NewLine) + [Environment]::NewLine)
    $choiceFolder = ""
    if ($choice -eq "S") { $choiceFolder = "STANDARD" }
    elseif ($choice -eq "V") { $choiceFolder = "VANILLA" }
    elseif ($choice -eq "E") { $choiceFolder = "ERHOEHT" }
    elseif ($choice -eq "F") { $choiceFolder = "FULL100" }
    if (-not [string]::IsNullOrWhiteSpace($choiceFolder)) {
        Copy-DZSMVehiclePresetToSelected -PresetRoot (Join-Path $root $choiceFolder) -SelectedRoot (Join-Path $root "SELECTED_VEHICLE_SPAWN_TO_COPY") -ChoiceName $choiceFolder
        $Global:SelectedVehicleSpawnPreset = $choiceFolder
        $report.Add("SELECTED_READY_TO_COPY: $choiceFolder") | Out-Null
    } else {
        $Global:SelectedVehicleSpawnPreset = "ALL"
        $report.Add("SELECTED_READY_TO_COPY: NONE_ALL_PRESETS_GENERATED") | Out-Null
    }
    $manifest = New-Object System.Collections.Generic.List[string]
    $manifest.Add("RelativePath,Bytes,SHA1") | Out-Null
    foreach ($f in Get-ChildItem -LiteralPath $root -Recurse -File -ErrorAction SilentlyContinue) {
        $rel = $f.FullName.Substring($root.Length).TrimStart("\")
        $manifest.Add(('"{0}",{1},{2}' -f $rel.Replace('"','""'), $f.Length, (Get-FileSha1 $f.FullName))) | Out-Null
    }
    Write-Utf8NoBom (Join-Path $UploadDir "73_VEHICLE_SPAWN_READY_TO_COPY_MANIFEST.csv") (($manifest -join [Environment]::NewLine) + [Environment]::NewLine)
    Write-Utf8NoBom (Join-Path $root "README_VEHICLE_SPAWN_READY_TO_COPY.txt") ((@(
        "VEHICLE SPAWN READY TO COPY",
        "===========================",
        "STANDARD = aktueller Stand.",
        "VANILLA = Vanilla_events.xml falls vorhanden, sonst Standard-Fallback.",
        "ERHOEHT = Fahrzeug-Events x2.",
        "FULL100 = Fahrzeug-Events active=1 und nominal/min auf max.",
        "SELECTED_VEHICLE_SPAWN_TO_COPY = deine Auswahl."
    ) -join [Environment]::NewLine) + [Environment]::NewLine)
    Add-Report "72_VEHICLE_SPAWN_SETUP.txt" $report
}

function Invoke-DZSMLogAnalysis {
    $report = New-Object System.Collections.Generic.List[string]
    $report.Add("74 AUTOMATISCHE LOGAUSWERTUNG") | Out-Null
    $report.Add("=============================") | Out-Null
    $report.Add("LogPath: $LiveLogsPath") | Out-Null
    $report.Add("FreshnessMinutes: $LogFreshnessMinutes") | Out-Null
    $report.Add("") | Out-Null
    $status = "OK"
    $summary = "Keine Logdaten ausgewertet."
    $lastFile = Join-Path $ServerToolSettingsDir "last_log_timestamp.txt"
    try {
        if (-not (Test-Path -LiteralPath $LiveLogsPath)) {
            $status = "MISSING_LOG_PATH"
            $summary = "Logpfad nicht erreichbar."
            Add-Warn ("Logs nicht erreichbar: " + $LiveLogsPath)
        } else {
            $files = @(Get-ChildItem -LiteralPath $LiveLogsPath -Recurse -File -ErrorAction SilentlyContinue | Where-Object { $_.Extension -match '^(\.log|\.rpt|\.adm|\.mdmp)$' } | Sort-Object LastWriteTime -Descending | Select-Object -First 20)
            $report.Add("Gefundene Logdateien ausgewertet: " + $files.Count) | Out-Null
            if ($files.Count -eq 0) {
                $status = "NO_LOG_FILES"
                $summary = "Keine Logdateien gefunden."
                Add-Warn "Logs nicht aktualisiert: keine Logdateien gefunden."
            } else {
                $newest = $files[0]
                $age = (New-TimeSpan -Start $newest.LastWriteTime -End (Get-Date)).TotalMinutes
                $report.Add("NewestLog: " + $newest.FullName) | Out-Null
                $report.Add("NewestLogTime: " + $newest.LastWriteTime.ToString("yyyy-MM-dd HH:mm:ss")) | Out-Null
                $report.Add("NewestLogAgeMinutes: " + ([Math]::Round($age,1))) | Out-Null
                if ($age -gt $LogFreshnessMinutes) {
                    $status = "STALE_LOGS"
                    Add-Warn ("Logs nicht aktuell: neueste Logdatei ist aelter als $LogFreshnessMinutes Minuten.")
                }
                $lastKnown = ""
                if (Test-Path -LiteralPath $lastFile) { $lastKnown = (Get-Content -LiteralPath $lastFile -Raw -ErrorAction SilentlyContinue).Trim() }
                $curStamp = $newest.LastWriteTimeUtc.ToString("o")
                if (-not [string]::IsNullOrWhiteSpace($lastKnown) -and $lastKnown -eq $curStamp) {
                    if ($status -eq "OK") { $status = "UNCHANGED_SINCE_LAST_RUN" }
                    Add-Warn "Logs seit letztem DZSM-Start nicht aktualisiert."
                }
                Write-Utf8NoBom $lastFile ($curStamp + [Environment]::NewLine)
                $errorCount = 0; $warnCount = 0
                $samples = New-Object System.Collections.Generic.List[string]
                foreach ($f in $files) {
                    if ($f.Extension.ToLowerInvariant() -eq ".mdmp") {
                        $errorCount++
                        $samples.Add(("MDMP/Crashdump gefunden: " + $f.Name)) | Out-Null
                        continue
                    }
                    try {
                        $tail = Get-Content -LiteralPath $f.FullName -Tail 2000 -ErrorAction SilentlyContinue
                        foreach ($line in $tail) {
                            $s = [string]$line
                            if ($s -match '(?i)(fatal|exception|crash|error|cannot|failed|null pointer|access violation|script compile)') {
                                $errorCount++
                                if ($samples.Count -lt 40) { $samples.Add((Redact-DZSMSensitiveText -Text ($f.Name + ": " + $s))) | Out-Null }
                            } elseif ($s -match '(?i)(warn|warning|fix-me|obsolete|invalid|disabled)') {
                                $warnCount++
                                if ($samples.Count -lt 40) { $samples.Add((Redact-DZSMSensitiveText -Text ($f.Name + ": " + $s))) | Out-Null }
                            }
                        }
                    } catch {}
                }
                $report.Add("ErrorLikeCount: $errorCount") | Out-Null
                $report.Add("WarningLikeCount: $warnCount") | Out-Null
                $report.Add("Samples:") | Out-Null
                foreach ($s in $samples) { $report.Add("  " + $s) | Out-Null }
                $summary = "Logs $status | Errors=$errorCount | Warnings=$warnCount | Newest=" + $newest.Name
            }
        }
    } catch {
        $status = "LOG_ANALYSIS_ERROR"
        $summary = "Logauswertung Fehler: " + $_.Exception.Message
        Add-Warn $summary
    }
    $Global:LogAnalysisStatus = $status
    $Global:LogAnalysisSummaryText = $summary
    $report.Add("") | Out-Null
    $report.Add("Status: $status") | Out-Null
    $report.Add("Summary: $summary") | Out-Null
    Add-Report "74_LOG_ANALYSIS.txt" $report
}


function Archive-DZSMDesktopFileOutputOnStart {
    $desktop = Get-DZSMDesktopPath
    $source = Join-Path $desktop $DesktopFileOutputFolderName
    $archiveDesktop = Join-Path $desktop $DesktopFileOutputArchiveFolderName
    $lines = New-Object System.Collections.Generic.List[string]
    $lines.Add("78 DESKTOP DATEI AUSGABE START ARCHIV") | Out-Null
    $lines.Add("=====================================") | Out-Null
    $lines.Add("Quelle: $source") | Out-Null
    $lines.Add("ArchivDesktop: $archiveDesktop") | Out-Null

    try {
        if (-not (Test-Path -LiteralPath $source)) {
            $lines.Add("Status: SKIP - Datei Ausgabe existiert noch nicht") | Out-Null
            Add-Report "78_DESKTOP_DATEI_AUSGABE_ARCHIVE.txt" $lines
            return
        }
        $items = @(Get-ChildItem -LiteralPath $source -Force -ErrorAction SilentlyContinue)
        if ($items.Count -eq 0) {
            $lines.Add("Status: SKIP - Datei Ausgabe ist leer") | Out-Null
            Add-Report "78_DESKTOP_DATEI_AUSGABE_ARCHIVE.txt" $lines
            return
        }

        Ensure-Dir $archiveDesktop
        Ensure-Dir $RunArchive
        $stage = Join-Path $RunArchive ("Datei_Ausgabe_Archiv_" + $RunStamp)
        if (Test-Path -LiteralPath $stage) { Remove-Item -LiteralPath $stage -Recurse -Force -ErrorAction SilentlyContinue }
        Ensure-Dir $stage

        $categories = @{
            "01_PHASE_A_START_MODLIST" = @("PHASE_A", "MODLIST", "STARTPARAMETER")
            "02_CE_EVENTS" = @("CE_EVENT", "EVENT_FIX")
            "03_TYPES_SETTINGS" = @("TYPES", "SELECTED_TYPES")
            "04_VEHICLE_SPAWNS" = @("VEHICLE", "FAHRZEUG")
            "05_GITHUB_SYNC" = @("GITHUB", "COMMIT")
            "99_INFO_UND_SONSTIGES" = @("README", "INFO")
        }

        foreach ($item in $items) {
            $upper = $item.Name.ToUpperInvariant()
            $cat = "99_INFO_UND_SONSTIGES"
            foreach ($key in $categories.Keys) {
                foreach ($needle in $categories[$key]) {
                    if ($upper.Contains($needle)) { $cat = $key; break }
                }
                if ($cat -ne "99_INFO_UND_SONSTIGES") { break }
            }
            $catDir = Join-Path $stage $cat
            Ensure-Dir $catDir
            Copy-Item -LiteralPath $item.FullName -Destination (Join-Path $catDir $item.Name) -Recurse -Force -ErrorAction SilentlyContinue
            $lines.Add("ARCHIVE_ITEM: " + $item.Name + " -> " + $cat) | Out-Null
        }

        $info = @(
            "DEUTSCHZ DATEI AUSGABE ARCHIV",
            "==============================",
            "Archiviert vor DZSM-Start: " + (Get-Date -Format "yyyy-MM-dd HH:mm:ss"),
            "Quelle: $source",
            "Zweck: Vorherigen Ready-to-Copy Stand nachvollziehbar sichern, bevor neue Settings erzeugt werden.",
            "Kategorien:",
            "01_PHASE_A_START_MODLIST",
            "02_CE_EVENTS",
            "03_TYPES_SETTINGS",
            "04_VEHICLE_SPAWNS",
            "05_GITHUB_SYNC",
            "99_INFO_UND_SONSTIGES"
        ) -join [Environment]::NewLine
        Write-Utf8NoBom (Join-Path $stage "ARCHIV_INFO.txt") ($info + [Environment]::NewLine)

        $zipName = ("{0}__Datei_Ausgabe__Vor_DZSM_Start.zip" -f $RunStamp)
        $zipPath = Join-Path $archiveDesktop $zipName
        if (Test-Path -LiteralPath $zipPath) { Remove-Item -LiteralPath $zipPath -Force -ErrorAction SilentlyContinue }
        Compress-Archive -Path (Join-Path $stage "*") -DestinationPath $zipPath -Force
        $lines.Add("Status: ARCHIVED") | Out-Null
        $lines.Add("ArchivZip: $zipPath") | Out-Null
        Write-Status ("Alte Desktop Datei Ausgabe archiviert: " + $zipPath) "Green"
    } catch {
        $lines.Add("Status: ERROR") | Out-Null
        $lines.Add("Error: " + $_.Exception.Message) | Out-Null
        Add-Warn ("Datei Ausgabe Start-Archiv Fehler: " + $_.Exception.Message)
    }
    Add-Report "78_DESKTOP_DATEI_AUSGABE_ARCHIVE.txt" $lines
}

function Publish-DZSMDesktopFileOutput {
    $desktop = Get-DZSMDesktopPath
    $target = Join-Path $desktop $DesktopFileOutputFolderName
    try {
        if (Test-Path -LiteralPath $target) { Remove-Item -LiteralPath $target -Recurse -Force -ErrorAction SilentlyContinue }
        Ensure-Dir $target

        $catInfo = Join-Path $target "00_INFO"
        $catPhase = Join-Path $target "01_PHASE_A_START_MODLIST"
        $catCe = Join-Path $target "02_CE_EVENT_FIX"
        $catTypes = Join-Path $target ("03_TYPES_SETTING_" + $Global:SelectedTypesPreset)
        $catVehicle = Join-Path $target ("04_VEHICLE_SPAWNS_" + $Global:SelectedVehicleSpawnPreset)
        $catGithub = Join-Path $target "05_GITHUB_SYNC"
        $catReports = Join-Path $target "90_REPORTS"
        foreach ($d in @($catInfo,$catPhase,$catCe,$catTypes,$catVehicle,$catGithub,$catReports)) { Ensure-Dir $d }

        $readme = New-Object System.Collections.Generic.List[string]
        $readme.Add("DEUTSCHZ DATEI AUSGABE") | Out-Null
        $readme.Add("======================") | Out-Null
        $readme.Add("Diese Dateien sind fertig zum manuellen Einspielen auf den Server vorbereitet.") | Out-Null
        $readme.Add("DZSM hat live nichts geaendert. Vor dem Kopieren Backup machen und Server stoppen.") | Out-Null
        $readme.Add("") | Out-Null
        $readme.Add("Ausgewaehltes Types Setup: " + $Global:SelectedTypesPreset) | Out-Null
        $readme.Add("Ausgewaehltes Fahrzeugspawn Setup: " + $Global:SelectedVehicleSpawnPreset) | Out-Null
        $readme.Add("") | Out-Null
        $readme.Add("Kategorien:") | Out-Null
        $readme.Add("00_INFO") | Out-Null
        $readme.Add("01_PHASE_A_START_MODLIST") | Out-Null
        $readme.Add("02_CE_EVENT_FIX") | Out-Null
        $readme.Add("03_TYPES_SETTING_" + $Global:SelectedTypesPreset) | Out-Null
        $readme.Add("04_VEHICLE_SPAWNS_" + $Global:SelectedVehicleSpawnPreset) | Out-Null
        $readme.Add("05_GITHUB_SYNC") | Out-Null
        $readme.Add("90_REPORTS") | Out-Null

        $quick = New-Object System.Collections.Generic.List[string]
        $quick.Add("SCHNELL SETTINGS UEBERSICHT") | Out-Null
        $quick.Add("===========================") | Out-Null
        $quick.Add("Stand: " + (Get-Date -Format "yyyy-MM-dd HH:mm:ss")) | Out-Null
        $quick.Add("Types Setup: " + $Global:SelectedTypesPreset) | Out-Null
        $quick.Add("Fahrzeugspawn Setup: " + $Global:SelectedVehicleSpawnPreset) | Out-Null
        $quick.Add("Mission/CE Ziel: $LiveMissionCePath") | Out-Null
        $quick.Add("Regel: Manuell kopieren, Server vorher stoppen, Backup behalten.") | Out-Null

        $phaseSrc = Join-Path $UploadDir $PhaseAFolderName
        if (Test-Path -LiteralPath $phaseSrc) {
            Copy-Item -Path (Join-Path $phaseSrc "*") -Destination $catPhase -Recurse -Force -ErrorAction SilentlyContinue
            $readme.Add("Kopiert: PHASE_A_READY_TO_COPY -> 01_PHASE_A_START_MODLIST") | Out-Null
        }

        $ceSrc = Join-Path $UploadDir $CeEventFixFolderName
        if (Test-Path -LiteralPath $ceSrc) {
            Copy-Item -Path (Join-Path $ceSrc "*") -Destination $catCe -Recurse -Force -ErrorAction SilentlyContinue
            $readme.Add("Kopiert: CE_EVENT_FIX_READY_TO_COPY -> 02_CE_EVENT_FIX") | Out-Null
        }

        $typesRoot = Join-Path $UploadDir $TypesPresetFolderName
        $typesSel = Join-Path $typesRoot "SELECTED_TYPES_PRESET_TO_COPY"
        if (Test-Path -LiteralPath $typesSel) {
            Copy-Item -Path (Join-Path $typesSel "*") -Destination $catTypes -Recurse -Force -ErrorAction SilentlyContinue
            $readme.Add("Kopiert: SELECTED_TYPES_PRESET_TO_COPY -> " + (Split-Path -Leaf $catTypes)) | Out-Null
            $quick.Add("Types Quelle: " + $catTypes) | Out-Null
        } elseif (Test-Path -LiteralPath $typesRoot) {
            Copy-Item -LiteralPath $typesRoot -Destination (Join-Path $catTypes "ALLE_TYPES_PRESETS") -Recurse -Force -ErrorAction SilentlyContinue
            $readme.Add("Kopiert: alle Types Presets, weil A/ALL gewaehlt wurde") | Out-Null
            $quick.Add("Types Quelle: alle Presets unter " + $catTypes) | Out-Null
        }

        $vehicleRoot = Join-Path $UploadDir $VehicleSpawnFolderName
        $vehicleSel = Join-Path $vehicleRoot "SELECTED_VEHICLE_SPAWN_TO_COPY"
        if (Test-Path -LiteralPath $vehicleSel) {
            Copy-Item -Path (Join-Path $vehicleSel "*") -Destination $catVehicle -Recurse -Force -ErrorAction SilentlyContinue
            $readme.Add("Kopiert: SELECTED_VEHICLE_SPAWN_TO_COPY -> " + (Split-Path -Leaf $catVehicle)) | Out-Null
            $quick.Add("Fahrzeugspawn Quelle: " + $catVehicle) | Out-Null
        } elseif (Test-Path -LiteralPath $vehicleRoot) {
            Copy-Item -LiteralPath $vehicleRoot -Destination (Join-Path $catVehicle "ALLE_VEHICLE_PRESETS") -Recurse -Force -ErrorAction SilentlyContinue
            $readme.Add("Kopiert: alle Fahrzeugspawn Presets, weil A/ALL gewaehlt wurde") | Out-Null
            $quick.Add("Fahrzeugspawn Quelle: alle Presets unter " + $catVehicle) | Out-Null
        }

        $githubRoot = Join-Path $UploadDir $GitPlanFolderName
        if (Test-Path -LiteralPath $githubRoot) {
            Copy-Item -Path (Join-Path $githubRoot "*") -Destination $catGithub -Recurse -Force -ErrorAction SilentlyContinue
            $readme.Add("Kopiert: GITHUB_SYNC_PLAN -> 05_GITHUB_SYNC") | Out-Null
        }
        $commitFile = Join-Path $UploadDir $CommitMessageFileName
        if (Test-Path -LiteralPath $commitFile) { Copy-Item -LiteralPath $commitFile -Destination $catGithub -Force -ErrorAction SilentlyContinue }

        foreach ($reportName in @("65_TYPES_PRESET_SCANNER.txt","72_VEHICLE_SPAWN_SETUP.txt","74_LOG_ANALYSIS.txt","75_DISCORD_STATUS.txt","76_WEBHOOK_CHECK.txt","78_DESKTOP_DATEI_AUSGABE_ARCHIVE.txt","99_NAECHSTE_SCHRITTE.txt")) {
            $rp = Join-Path $UploadDir $reportName
            if (Test-Path -LiteralPath $rp) { Copy-Item -LiteralPath $rp -Destination $catReports -Force -ErrorAction SilentlyContinue }
        }

        Write-Utf8NoBom (Join-Path $catInfo "README_DATEI_AUSGABE.txt") (($readme -join [Environment]::NewLine) + [Environment]::NewLine)
        Write-Utf8NoBom (Join-Path $catInfo "SCHNELL_SETTINGS_UEBERSICHT.txt") (($quick -join [Environment]::NewLine) + [Environment]::NewLine)
        Write-Utf8NoBom (Join-Path $target "README_DATEI_AUSGABE.txt") (($readme -join [Environment]::NewLine) + [Environment]::NewLine)
        Write-Status ("Desktop Datei Ausgabe aktualisiert: " + $target) "Green"
    } catch {
        Add-Warn ("Desktop Datei Ausgabe konnte nicht erstellt werden: " + $_.Exception.Message)
    }
}

function Send-DZSMDiscordStatus {
    param([bool]$Success)
    $webhook = Get-DZSMDiscordWebhook
    $lines = New-Object System.Collections.Generic.List[string]
    $lines.Add("75 DISCORD STATUS") | Out-Null
    $lines.Add("=================") | Out-Null
    $configured = -not [string]::IsNullOrWhiteSpace($webhook)
    $lines.Add("WebhookConfigured: $configured") | Out-Null
    if (-not $configured) {
        $Global:DiscordSendStatus = "NO_WEBHOOK_CONFIGURED"
        $lines.Add("Status: NO_WEBHOOK_CONFIGURED") | Out-Null
        Add-Warn "Discord Status nicht gesendet: Webhook fehlt in ServerToolSettings\\webhooks.txt. Desktop-Kopie DZSM_webhooks.txt bearbeiten."
        Add-Report "75_DISCORD_STATUS.txt" $lines
        return
    }
    try {
        $state = "DONE"
        if (-not $Success) { $state = "FAIL" }
        $content = @(
            "**DeutschZ System Manager $Version**",
            "Status: $state",
            "Types Setup: $Global:SelectedTypesPreset",
            "Fahrzeugspawn Setup: $Global:SelectedVehicleSpawnPreset",
            "Logauswertung: $Global:LogAnalysisSummaryText",
            "Warnungen: " + $Global:Warnings.Count,
            "UploadDir: $UploadDir",
            "Datei Ausgabe: " + (Join-Path (Get-DZSMDesktopPath) $DesktopFileOutputFolderName)
        ) -join "`n"
        $payload = @{ content = $content } | ConvertTo-Json -Depth 4
        Invoke-RestMethod -Uri $webhook -Method Post -ContentType "application/json" -Body $payload -TimeoutSec 12 | Out-Null
        $Global:DiscordSendStatus = "SENT"
        $lines.Add("Status: SENT") | Out-Null
    } catch {
        $Global:DiscordSendStatus = "SEND_ERROR"
        $lines.Add("Status: SEND_ERROR") | Out-Null
        $lines.Add("Error: " + $_.Exception.Message) | Out-Null
        Add-Warn ("Discord Status senden fehlgeschlagen: " + $_.Exception.Message)
    }
    Add-Report "75_DISCORD_STATUS.txt" $lines
}

function Write-PhaseAPackage {
    $phaseDir = Join-Path $UploadDir $PhaseAFolderName
    if (Test-Path -LiteralPath $phaseDir) { Remove-Item -LiteralPath $phaseDir -Recurse -Force }
    Ensure-Dir $phaseDir

    $fallbackModlist = "@CF;@Dabs Framework;@Community-Online-Tools;@VPPAdminTools;@DayZ-Expansion-Bundle;@DayZ-Expansion-Licensed;@Expansion AI Buddy V2;@BaseBuildingPlus;@Code Lock;@RaG_Core;@RaG_BaseItems;@RedFalcon Flight System Heliz;@CarNoKill;@[FREE] Advanced Battle Pass v2;@MegaFoodPack;@NoxZ_Phone;@NVG + Scope;@RevScopes;@Modular Vest System;@ReDos Bags;@ArmA2 Trucks;@SNAFU Weapons;@SprayZ;@DeutschZ_Core;@DeutschZ_ExpansionBridge;@DeutschZ_KotHZ(InfectedSiege);@DeutschZ_ConvoyZ;@DeutschZ_Screen_Menu"
    $sourceModlist = Join-Path $LiveRoot "modlist.txt"
    $modlist = $fallbackModlist

    if (Test-Path -LiteralPath $sourceModlist) {
        try {
            $bytes = [System.IO.File]::ReadAllBytes($sourceModlist)
            $modlist = [System.Text.Encoding]::UTF8.GetString($bytes)
            $modlist = $modlist.Trim()
            if ($modlist.StartsWith([char]0xFEFF)) { $modlist = $modlist.TrimStart([char]0xFEFF) }
            if ($modlist.StartsWith("-mod=")) { $modlist = $modlist.Substring(5) }
        } catch {
            Add-Warn "modlist.txt konnte nicht gelesen werden, Fallback-Modlist verwendet."
            $modlist = $fallbackModlist
        }
    }

    $parts = New-Object System.Collections.Generic.List[string]
    foreach ($p in ($modlist -split ";")) {
        $clean = $p.Trim()
        if ($clean.Length -gt 0) { $parts.Add($clean) | Out-Null }
    }

    # Remove old/wrong DeutschZ entries and append correct Phase A order.
    $filtered = New-Object System.Collections.Generic.List[string]
    foreach ($p in $parts) {
        $n = $p.ToLowerInvariant()
        if ($n -eq "@deutschz_core") { continue }
        if ($n -eq "@deutschz_expansionbridge") { continue }
        if ($n -eq "@deutschz_kothz") { continue }
        if ($n -eq "@deutschz_kothz(infectedsiege)") { continue }
        if ($n -eq "@deutschz_convoyz") { continue }
        if ($n -eq "@deutschz_screen_menu") { continue }
        $filtered.Add($p) | Out-Null
    }
    foreach ($p in @("@DeutschZ_Core", "@DeutschZ_ExpansionBridge", "@DeutschZ_KotHZ(InfectedSiege)", "@DeutschZ_ConvoyZ", "@DeutschZ_Screen_Menu")) {
        $filtered.Add($p) | Out-Null
    }

    $final = ($filtered -join ";")
    Write-Utf8NoBom (Join-Path $phaseDir "modlist.txt") $final
    Write-Utf8NoBom (Join-Path $phaseDir "server_startparameter.txt") ("-mod=" + $final)
    $readme = "PHASE A APPLY" + [Environment]::NewLine +
              "=============" + [Environment]::NewLine +
              "Kopiere modlist.txt nur manuell in die Hoster-Modlist." + [Environment]::NewLine +
              "Kein -mod= in modlist.txt." + [Environment]::NewLine +
              "KotHZ-Ordnername: @DeutschZ_KotHZ(InfectedSiege)." + [Environment]::NewLine +
              "DeutschZ-Reihenfolge: Core -> ExpansionBridge -> KotHZ -> ConvoyZ -> Screen_Menu." + [Environment]::NewLine
    Write-Utf8NoBom (Join-Path $phaseDir "README_PHASE_A_APPLY.txt") $readme

    $zipPath = Join-Path $UploadDir $PhaseAZipName
    if (Test-Path -LiteralPath $zipPath) { Remove-Item -LiteralPath $zipPath -Force }
    Compress-Archive -Path (Join-Path $phaseDir "*") -DestinationPath $zipPath -Force

    return $final
}

function Copy-DZSMPackageItemSafe {
    param([string]$SourcePath, [string]$TargetRoot, [string]$RelativePath)
    if (-not (Test-Path -LiteralPath $SourcePath)) { return }
    $target = Join-Path $TargetRoot $RelativePath
    Ensure-Dir (Split-Path -Parent $target)
    Copy-Item -LiteralPath $SourcePath -Destination $target -Force -ErrorAction SilentlyContinue
}

function Copy-DZSMPackageFolderSafe {
    param([string]$SourceFolder, [string]$TargetFolder)
    if (-not (Test-Path -LiteralPath $SourceFolder)) { return }
    if (Test-Path -LiteralPath $TargetFolder) { Remove-Item -LiteralPath $TargetFolder -Recurse -Force -ErrorAction SilentlyContinue }
    Ensure-Dir (Split-Path -Parent $TargetFolder)
    Copy-Item -LiteralPath $SourceFolder -Destination $TargetFolder -Recurse -Force -ErrorAction SilentlyContinue
}

function Build-UploadPackage {
    $zipPath = Join-Path $UploadDir $UploadZipName
    if (Test-Path -LiteralPath $zipPath) { Remove-Item -LiteralPath $zipPath -Force }

    $slimRoot = Join-Path $UploadDir $UploadSlimFolderName
    if (Test-Path -LiteralPath $slimRoot) { Remove-Item -LiteralPath $slimRoot -Recurse -Force -ErrorAction SilentlyContinue }
    Ensure-Dir $slimRoot

    foreach ($f in Get-ChildItem -LiteralPath $UploadDir -File -Force -ErrorAction SilentlyContinue) {
        if ($f.Name -eq $UploadZipName) { continue }
        if ($f.Extension.ToLowerInvariant() -eq ".zip") {
            if ($f.Name -eq $PhaseAZipName) { Copy-DZSMPackageItemSafe -SourcePath $f.FullName -TargetRoot $slimRoot -RelativePath $f.Name }
            continue
        }
        if (@(".txt", ".csv", ".md", ".json", ".log") -contains $f.Extension.ToLowerInvariant()) {
            Copy-DZSMPackageItemSafe -SourcePath $f.FullName -TargetRoot $slimRoot -RelativePath $f.Name
        }
    }

    foreach ($folderName in @($PhaseAFolderName, $CeEventFixFolderName, $GitPlanFolderName)) {
        $folder = Join-Path $UploadDir $folderName
        if (Test-Path -LiteralPath $folder) { Copy-DZSMPackageFolderSafe -SourceFolder $folder -TargetFolder (Join-Path $slimRoot $folderName) }
    }

    $typesRoot = Join-Path $UploadDir $TypesPresetFolderName
    if (Test-Path -LiteralPath $typesRoot) {
        $typesSlim = Join-Path $slimRoot $TypesPresetFolderName
        Ensure-Dir $typesSlim
        foreach ($name in @("README_TYPES_PRESET_READY_TO_COPY.txt", "SELECTED_TYPES_PRESET_TO_COPY")) {
            $source = Join-Path $typesRoot $name
            if (Test-Path -LiteralPath $source) {
                if ((Get-Item -LiteralPath $source).PSIsContainer) { Copy-DZSMPackageFolderSafe -SourceFolder $source -TargetFolder (Join-Path $typesSlim $name) }
                else { Copy-DZSMPackageItemSafe -SourcePath $source -TargetRoot $typesSlim -RelativePath $name }
            }
        }
    }



    $vehicleRoot = Join-Path $UploadDir $VehicleSpawnFolderName
    if (Test-Path -LiteralPath $vehicleRoot) {
        $vehicleSlim = Join-Path $slimRoot $VehicleSpawnFolderName
        Ensure-Dir $vehicleSlim
        foreach ($name in @("README_VEHICLE_SPAWN_READY_TO_COPY.txt", "SELECTED_VEHICLE_SPAWN_TO_COPY")) {
            $source = Join-Path $vehicleRoot $name
            if (Test-Path -LiteralPath $source) {
                if ((Get-Item -LiteralPath $source).PSIsContainer) { Copy-DZSMPackageFolderSafe -SourceFolder $source -TargetFolder (Join-Path $vehicleSlim $name) }
                else { Copy-DZSMPackageItemSafe -SourcePath $source -TargetRoot $vehicleSlim -RelativePath $name }
            }
        }
    }

    $note = @(
        "DZSM_UPLOAD_PACKAGE_SLIM",
        "========================",
        "Dieses Uploadpaket ist absichtlich klein.",
        "SERVERSETTINGS_SAFE_EXPORT.zip bleibt separat im UploadDir/Desktop und wird nicht mehr in DZSM_UPLOAD_PACKAGE.zip verschachtelt.",
        "TYPES_PRESET_READY_TO_COPY enthaelt im Uploadpaket nur README und SELECTED_TYPES_PRESET_TO_COPY, nicht alle Varianten.",
        "VEHICLE_SPAWN_READY_TO_COPY enthaelt im Uploadpaket nur README und SELECTED_VEHICLE_SPAWN_TO_COPY, nicht alle Varianten.",
        "Secrets/Webhooks/Passwoerter werden in Safe-Textkopien redacted. Discord/Steam-Links bleiben erhalten, Discord API Webhooks werden entfernt."
    ) -join [Environment]::NewLine
    Write-Utf8NoBom (Join-Path $slimRoot "README_UPLOAD_PACKAGE_SLIM.txt") ($note + [Environment]::NewLine)

    $items = Get-ChildItem -LiteralPath $slimRoot -Force -ErrorAction SilentlyContinue
    if (@($items).Count -gt 0) {
        Compress-Archive -Path (Join-Path $slimRoot "*") -DestinationPath $zipPath -Force
    }
    return $zipPath
}


function Set-DZSMClipboardText {
    param([string]$Text)
    $ok = $false
    try {
        Set-Clipboard -Value $Text -ErrorAction Stop
        $ok = $true
    } catch {
        try { $Text | clip.exe; $ok = $true } catch {}
    }
    return $ok
}

function Read-DZSMGitModeChoice {
    try {
        Write-Host ""
        Write-Host "╔══════════════════════════════════════════════════════════════════════╗" -ForegroundColor Green
        Write-Host "║              D E U T S C H Z  -  G I T H U B                     ║" -ForegroundColor Green
        Write-Host "╠══════════════════════════════════════════════════════════════════════╣" -ForegroundColor Green
        Write-Host "║ M = Manuell: Commit-Message + Plan, keine Repo-Aenderung            ║" -ForegroundColor Green
        Write-Host "║ A = Automatisch: lokalen Repo-Inbox-Ordner vorbereiten              ║" -ForegroundColor Yellow
        Write-Host "║ N = Nein: GitHub-Vorbereitung ueberspringen                         ║" -ForegroundColor DarkGray
        Write-Host "╚══════════════════════════════════════════════════════════════════════╝" -ForegroundColor Green
        Write-Host "GitHub wird niemals ohne deine Auswahl committet oder gepusht." -ForegroundColor Gray
        return (Read-DZSMMenuChoice -Choices "MAN" -Prompt "GitHub Vorbereitung waehlen [M/A/N]:" -Fallback "M")
    } catch {
        Add-Warn ("GitHub Auswahl konnte nicht gelesen werden: " + $_.Exception.Message)
    }
    return "M"
}

function New-DZSMCommitMessageText {
    param([string]$Mode)
    $warnText = "0"
    try { $warnText = [string]$Global:Warnings.Count } catch {}
    $stamp = Get-Date -Format "yyyy-MM-dd HH:mm"
    $lines = @(
        "DZSM: update system manager and server analysis state",
        "",
        "- Version: $Version",
        "- Timestamp: $stamp",
        "- Mode: $Mode",
        "- Live paths: Source Files, Ready Mods, Mission/CE, Profiles",
        "- Repo current source path checked read-only",
        "- Upload package: slim ChatGPT package generated",
        "- Safety: no git commit/push executed by DZSM",
        "- Warnings: $warnText",
        "",
        "Notes:",
        "- Secrets/passwords/webhooks filtered from safe text exports",
        "- Discord invite links and Steam links kept",
        "- Commit via GitHub Desktop after review"
    )
    return ($lines -join [Environment]::NewLine)
}

function Write-DZSMGitHubPlan {
    param([string]$Mode, [string]$CommitMessage)
    $planRoot = Join-Path $UploadDir $GitPlanFolderName
    if (Test-Path -LiteralPath $planRoot) { Remove-Item -LiteralPath $planRoot -Recurse -Force -ErrorAction SilentlyContinue }
    Ensure-Dir $planRoot

    Write-Utf8NoBom (Join-Path $planRoot $CommitMessageFileName) ($CommitMessage + [Environment]::NewLine)

    $structure = @(
        "SUGGESTED REPO STRUCTURE",
        "========================",
        "Repo: $GitRepoPath",
        "Aktueller Source-Pfad laut Patrick: $RepoCurrentSourcePath",
        "",
        "ModZ/DeutschZ_Core/",
        "ModZ/DeutschZ_ExpansionBridge/",
        "ModZ/DeutschZ_KotHZ/",
        "ModZ/DeutschZ_ConvoyZ/",
        "ModZ/DeutschZ_GroundZero/",
        "ModZ/DeutschZ_CourierZ/",
        "ModZ/DeutschZ_OperationDeutschZ/",
        "ServerSettings/README.md",
        "DZSM/README.md",
        "Docs/",
        "",
        "Nicht ins Repo: profiles, storage, logs, crashlogs, RPT, ADM, mdmp, secrets, tokens, pbo, bisign, biprivatekey, Workshop Upload Runtime."
    ) -join [Environment]::NewLine
    Write-Utf8NoBom (Join-Path $planRoot "SUGGESTED_STRUCTURE.txt") ($structure + [Environment]::NewLine)

    $filters = @(
        "SECRET FILTER RULES",
        "===================",
        "Gefiltert: Passwoerter, RConPassword, Tokens, API Keys, Discord API Webhooks, Webhook URLs.",
        "Erlaubt: Discord Invite Links, Steam Links, Workshop Links, normale Dokumentationslinks.",
        "DZSM fuehrt keine git push/commit/reset/clean Befehle automatisch aus."
    ) -join [Environment]::NewLine
    Write-Utf8NoBom (Join-Path $planRoot "SECRET_FILTER_RULES.txt") ($filters + [Environment]::NewLine)

    $readme = @(
        "GITHUB SYNC PLAN",
        "================",
        "Auswahl: $Mode",
        "Commit Message wurde erstellt und in die Zwischenablage kopiert, wenn Windows Clipboard verfuegbar war.",
        "GitHub Desktop: Commit Message einfuegen, Aenderungen pruefen, dann committen.",
        "Automatik bedeutet nur lokaler Repo-Inbox-Ordner, kein git commit und kein git push."
    ) -join [Environment]::NewLine
    Write-Utf8NoBom (Join-Path $planRoot "README_GITHUB_SYNC_PLAN.txt") ($readme + [Environment]::NewLine)
    return $planRoot
}

function Copy-DZSMGitPlanToRepoInbox {
    param([string]$PlanRoot)
    if (-not (Test-Path -LiteralPath $GitRepoPath)) {
        Add-Warn ("GitHub Repo Pfad nicht erreichbar: " + $GitRepoPath)
        return $false
    }
    try {
        $inboxRoot = Join-Path $GitRepoPath $GitHubInboxFolderName
        $target = Join-Path $inboxRoot ("DZSM_SYNC_" + $RunStamp)
        Ensure-Dir $target
        Copy-Item -Path (Join-Path $PlanRoot "*") -Destination $target -Recurse -Force -ErrorAction Stop
        return $true
    } catch {
        Add-Warn ("GitHub Auto-Inbox Fehler: " + $_.Exception.Message)
        return $false
    }
}

function Invoke-DZSMGitHubPreparation {
    $mode = Read-DZSMGitModeChoice
    $Global:GitHubPreparationMode = $mode
    $commitMessage = New-DZSMCommitMessageText -Mode $mode
    $commitPath = Join-Path $UploadDir $CommitMessageFileName
    Write-Utf8NoBom $commitPath ($commitMessage + [Environment]::NewLine)
    $clipOk = Set-DZSMClipboardText -Text $commitMessage

    $planRoot = $null
    if ($mode -ne "N") { $planRoot = Write-DZSMGitHubPlan -Mode $mode -CommitMessage $commitMessage }
    $autoCopied = $false
    if ($mode -eq "A" -and $null -ne $planRoot) { $autoCopied = Copy-DZSMGitPlanToRepoInbox -PlanRoot $planRoot }

    $desktop = Get-DZSMDesktopPath
    if (-not [string]::IsNullOrWhiteSpace($desktop) -and (Test-Path -LiteralPath $desktop)) {
        try { Write-Utf8NoBom (Join-Path $desktop $CommitMessageFileName) ($commitMessage + [Environment]::NewLine) } catch {}
    }

    $lines = New-Object System.Collections.Generic.List[string]
    $lines.Add("68 GITHUB SYNC PLAN") | Out-Null
    $lines.Add("===================") | Out-Null
    $lines.Add("RepoPath: $GitRepoPath") | Out-Null
    $lines.Add("Mode: $mode") | Out-Null
    $lines.Add("Clipboard: $clipOk") | Out-Null
    $lines.Add("AutoInboxCopied: $autoCopied") | Out-Null
    $lines.Add("CommitMessageFile: $commitPath") | Out-Null
    $lines.Add("PlanFolder: " + (Join-Path $UploadDir $GitPlanFolderName)) | Out-Null
    Add-Report "68_GITHUB_SYNC_PLAN.txt" $lines
}


Ensure-Dir $Root
Ensure-Dir $ToolDir
Ensure-Dir $ReportsRoot
Ensure-Dir $UploadDir
Ensure-Dir $ArchiveRoot
Ensure-Dir $RunArchive

function Archive-OldRootLogs {
    param([string]$KeepRunLog, [string]$KeepStartLog)
    try {
        $target = Join-Path $RunArchive "root_logs"
        Ensure-Dir $target
        $patterns = @("DZSM*_RUN.log", "DZSM*_START.log")
        foreach ($pat in $patterns) {
            foreach ($f in Get-ChildItem -LiteralPath $Root -Filter $pat -File -ErrorAction SilentlyContinue) {
                if ($f.FullName -eq $KeepRunLog) { continue }
                if ($f.FullName -eq $KeepStartLog) { continue }
                $dest = Join-Path $target $f.Name
                if (Test-Path -LiteralPath $dest) {
                    $base = [System.IO.Path]::GetFileNameWithoutExtension($f.Name)
                    $ext = [System.IO.Path]::GetExtension($f.Name)
                    $dest = Join-Path $target ($base + "_" + (Get-Date -Format "HHmmssfff") + $ext)
                }
                Move-Item -LiteralPath $f.FullName -Destination $dest -Force -ErrorAction SilentlyContinue
            }
        }
    } catch {}
}

Archive-OldRootLogs -KeepRunLog $RunLog -KeepStartLog $StartLog

Write-Utf8NoBom $StartLog ("DZSM v0.7.9 started " + (Get-Date -Format "yyyy-MM-dd HH:mm:ss"))
Write-Utf8NoBom $RunLog ("DZSM v0.7.9 run log " + (Get-Date -Format "yyyy-MM-dd HH:mm:ss") + [Environment]::NewLine)

# Clean current upload dir except archives? Only current upload products.
foreach ($old in @("DZSM_UPLOAD_PACKAGE.zip", "PHASE_A_READY_TO_COPY.zip", "SERVERSETTINGS_SAFE_EXPORT.zip")) {
    $oldPath = Join-Path $UploadDir $old
    if (Test-Path -LiteralPath $oldPath) {
        Ensure-Dir $RunArchive
        Move-Item -LiteralPath $oldPath -Destination (Join-Path $RunArchive $old) -Force
    }
}

Write-Status "DeutschZ System Manager - $Version" "Green"
Write-Status "Root: $Root" "Gray"
Write-Status "UploadDir: $UploadDir" "Gray"
Install-DesktopStartShortcut
Ensure-DZSMServerToolSettings
Archive-DZSMDesktopFileOutputOnStart
$Global:WebhookCheckStatus = Test-DZSMDiscordWebhookConfig
$pdriveReport = Ensure-PDriveAndDayZTools
Add-Report "09_PDRIVE_DAYZTOOLS_STATUS.txt" $pdriveReport

# 00 Summary
$lines = New-Object System.Collections.Generic.List[string]
$lines.Add("00 ZUSAMMENFASSUNG") | Out-Null
$lines.Add("==================") | Out-Null
$lines.Add("Version: $Version") | Out-Null
$lines.Add("") | Out-Null
$lines.Add("Verbindliche aktuelle Live-Pfade:") | Out-Null
$lines.Add("Source Files: $LiveSourceFilesPath") | Out-Null
$lines.Add("Ready Mods:   $LiveReadyModsPath") | Out-Null
$lines.Add("Mission/CE:   $LiveMissionCePath") | Out-Null
$lines.Add("Profiles:     $LiveProfilesPath") | Out-Null
$lines.Add("") | Out-Null
$lines.Add("Regel: Wenn UNC nicht erreichbar ist, wird das als Hinweis gemeldet. Kein Fallback auf Repo-Configpfade.") | Out-Null
$lines.Add("Sicherheitsregeln: kein Git, kein Repo-Write, kein Build, kein Workshop-Upload, keine Secrets roh exportieren.") | Out-Null
Add-Report "00_ZUSAMMENFASSUNG.txt" $lines

# 01 Live paths
$lines = New-Object System.Collections.Generic.List[string]
$lines.Add("01 LIVE PATHS STATUS") | Out-Null
$lines.Add("====================") | Out-Null
$lines.Add("Version: $Version") | Out-Null
$lines.Add("Regel: Diese vier UNC-Pfade sind verbindlich. Kein automatisches Umschwenken auf Repo-Configpfade.") | Out-Null
foreach ($entry in @(
    @{Name="Source Files"; Path=$LiveSourceFilesPath},
    @{Name="Ready Mods"; Path=$LiveReadyModsPath},
    @{Name="Mission/CE"; Path=$LiveMissionCePath},
    @{Name="Profiles"; Path=$LiveProfilesPath}
)) {
    $stats = Get-DirStats $entry.Path
    if ($stats.Exists) {
        $lines.Add("OK: " + $entry.Name) | Out-Null
        $lines.Add("  Pfad: " + $entry.Path) | Out-Null
        $lines.Add("  TopFiles=" + $stats.TopFiles + " TopDirs=" + $stats.TopDirs + " TopFileBytes=" + $stats.TopFileBytes) | Out-Null
    } else {
        $lines.Add("WARN: " + $entry.Name + " nicht erreichbar") | Out-Null
        $lines.Add("  Pfad: " + $entry.Path) | Out-Null
        Add-Warn ($entry.Name + " nicht erreichbar: " + $entry.Path)
    }
}
Add-Report "01_LIVE_PATHS_STATUS.txt" $lines

# 02 Ready mods
$lines = New-Object System.Collections.Generic.List[string]
$lines.Add("02 READY MODS LAYOUT CHECK") | Out-Null
$lines.Add("==========================") | Out-Null
$lines.Add("Quelle: $LiveReadyModsPath") | Out-Null
$lines.Add("Zweck: Aktueller Steam-/Workshop-Uploadstand. Keine Source-Pruefung.") | Out-Null
$lines.Add("Hinweis: KotHZ akzeptiert fuer Ready Mods den Alias @DeutschZ_KotHZ, weil der Server-Modlist-Name @DeutschZ_KotHZ(InfectedSiege) lauten kann.") | Out-Null
if (-not (Test-Path -LiteralPath $LiveReadyModsPath)) {
    $lines.Add("STATUS: WARN - Ready Mods nicht erreichbar") | Out-Null
} else {
    $lines.Add("STATUS: OK - Ready Mods erreichbar") | Out-Null
    $mods = @(
        @{Folder="@DeutschZ_Core"; Pbo="DeutschZ_Core.pbo"; Required=$true; Alias=""},
        @{Folder="@DeutschZ_ExpansionBridge"; Pbo="DeutschZ_ExpansionBridge.pbo"; Required=$true; Alias=""},
        @{Folder="@DeutschZ_KotHZ(InfectedSiege)"; Pbo="DeutschZ_KotHZ.pbo"; Required=$true; Alias="@DeutschZ_KotHZ"},
        @{Folder="@DeutschZ_ConvoyZ"; Pbo="DeutschZ_ConvoyZ.pbo"; Required=$true; Alias=""},
        @{Folder="@DeutschZ_Screen_Menu"; Pbo="DeutschZ_Screen_Menu.pbo"; Required=$false; Alias=""}
    )
    foreach ($m in $mods) {
        $modPath = Join-Path $LiveReadyModsPath $m.Folder
        $usedAlias = $false
        $aliasPath = ""
        if (-not (Test-Path -LiteralPath $modPath) -and -not [string]::IsNullOrWhiteSpace($m.Alias)) {
            $aliasPath = Join-Path $LiveReadyModsPath $m.Alias
            if (Test-Path -LiteralPath $aliasPath) {
                $modPath = $aliasPath
                $usedAlias = $true
            }
        }

        $lines.Add("") | Out-Null
        $lines.Add("MOD: " + $m.Folder) | Out-Null
        if ($usedAlias) {
            $lines.Add("  Status: OK_ALIAS_READY_FOLDER") | Out-Null
            $lines.Add("  Modlist-Name: " + $m.Folder) | Out-Null
            $lines.Add("  Ready-Mods-Ordner: " + $m.Alias) | Out-Null
        }
        if (-not (Test-Path -LiteralPath $modPath)) {
            if ($m.Required) { $lines.Add("  Status: FEHLT_REQUIRED") | Out-Null; Add-Warn ("Required Ready-Mod fehlt: " + $m.Folder) }
            else { $lines.Add("  Status: FEHLT_OPTIONAL") | Out-Null }
            continue
        }
        $addons = Join-Path $modPath "addons"
        $keys = Join-Path $modPath "Keys"
        if (-not $usedAlias) { $lines.Add("  Status: OK Ordner vorhanden") | Out-Null }
        $lines.Add("  Pfad: " + $modPath) | Out-Null
        if (Test-Path -LiteralPath $addons) {
            $pboFiles = @(Get-ChildItem -LiteralPath $addons -Filter "*.pbo" -File -ErrorAction SilentlyContinue)
            $bisigns = @(Get-ChildItem -LiteralPath $addons -Filter "*.bisign" -File -ErrorAction SilentlyContinue)
            $subDirs = @(Get-ChildItem -LiteralPath $addons -Directory -ErrorAction SilentlyContinue)
            $lines.Add("  addons: OK | PBO=" + $pboFiles.Count + " | BISIGN=" + $bisigns.Count + " | Unterordner=" + $subDirs.Count) | Out-Null
            $expected = Join-Path $addons $m.Pbo
            if (Test-Path -LiteralPath $expected) {
                $file = Get-Item -LiteralPath $expected
                $sha = Get-FileSha1 $expected
                $lines.Add("  Erwartete PBO: OK | " + $m.Pbo + " | Bytes=" + $file.Length + " | SHA1=" + $sha) | Out-Null
            } else {
                $lines.Add("  Erwartete PBO: FEHLT | " + $m.Pbo) | Out-Null
                if ($m.Required) { Add-Warn ("Expected PBO fehlt: " + $expected) }
            }
            foreach ($sd in $subDirs) {
                $lines.Add("  WARN: Unterordner in addons gefunden: " + $sd.Name + " (pruefen, ob versehentlich Source statt PBO hochgeladen wurde)") | Out-Null
            }
        } else {
            $lines.Add("  addons: FEHLT") | Out-Null
            if ($m.Required) { Add-Warn ("addons Ordner fehlt: " + $addons) }
        }
        if (Test-Path -LiteralPath $keys) {
            $bikeys = @(Get-ChildItem -LiteralPath $keys -Filter "*.bikey" -File -ErrorAction SilentlyContinue)
            $lines.Add("  Keys: OK | BIKEY=" + $bikeys.Count) | Out-Null
        } else {
            $lines.Add("  Keys: FEHLT/optional") | Out-Null
        }
    }

    $aliasOnly = Join-Path $LiveReadyModsPath "@DeutschZ_KotHZ"
    $namedFolder = Join-Path $LiveReadyModsPath "@DeutschZ_KotHZ(InfectedSiege)"
    if ((Test-Path -LiteralPath $aliasOnly) -and (Test-Path -LiteralPath $namedFolder)) {
        $lines.Add("") | Out-Null
        $lines.Add("WARN: Beide KotHZ-Ordner existieren. Einer reicht. Doppelte Ready-Mods vermeiden.") | Out-Null
        Add-Warn "Beide KotHZ Ready-Mod Ordner existieren: @DeutschZ_KotHZ und @DeutschZ_KotHZ(InfectedSiege)."
    }
}
Add-Report "02_READY_MODS_LAYOUT_CHECK.txt" $lines

# 03 Source files
$lines = New-Object System.Collections.Generic.List[string]
$lines.Add("03 SOURCE FILES CHECK") | Out-Null
$lines.Add("=====================") | Out-Null
$lines.Add("Quelle: $LiveSourceFilesPath") | Out-Null
$lines.Add("Zweck: Aktueller Arbeits-Source-Stand. Keine PBO/Upload-Quelle.") | Out-Null
$lines.Add("Repo-Source aktuell/zusatzlich: $RepoCurrentSourcePath") | Out-Null
if (Test-Path -LiteralPath $RepoCurrentSourcePath) { $lines.Add("STATUS: OK - Repo-Source aktuell erreichbar") | Out-Null } else { $lines.Add("STATUS: HINWEIS - Repo-Source aktuell nicht erreichbar") | Out-Null }
if (-not (Test-Path -LiteralPath $LiveSourceFilesPath)) {
    $lines.Add("STATUS: WARN - Source Files nicht erreichbar") | Out-Null
} else {
    $lines.Add("STATUS: OK - Source Files erreichbar") | Out-Null
    foreach ($name in @("DeutschZ_Core","DeutschZ_ExpansionBridge","DeutschZ_KotHZ","DeutschZ_ConvoyZ","DeutschZ_GroundZero","DeutschZ_CourierZ","DeutschZ_OperationDeutschZ")) {
        $p = Join-Path $LiveSourceFilesPath $name
        if (Test-Path -LiteralPath $p) { $lines.Add("OK: " + $name + " -> " + $p) | Out-Null }
        else { $lines.Add("FEHLT/optional: " + $name + " -> " + $p) | Out-Null }
    }
    $legacyTerms = @("LBmaster","LBAdvancedGroups","LBAdminTool","SFKOTH","BasicMap","VPPAdmin","AdvancedGroups","MarkerBridge","MarkerBackend","ExpansionEventAI_Stub","SurvivorM_Mirek")
    $legacyHits = New-Object System.Collections.Generic.List[string]
    $sourceFiles = Get-ChildItem -LiteralPath $LiveSourceFilesPath -Recurse -File -ErrorAction SilentlyContinue
    foreach ($f in $sourceFiles) {
        foreach ($term in $legacyTerms) {
            if ($f.FullName.IndexOf($term, [System.StringComparison]::OrdinalIgnoreCase) -ge 0) {
                $legacyHits.Add($f.FullName) | Out-Null
                break
            }
        }
    }
    $lines.Add("") | Out-Null
    $lines.Add("Altlasten-Schnellsuche in Dateinamen/Pfaden:") | Out-Null
    if ($legacyHits.Count -eq 0) { $lines.Add("OK: Keine Altlasten in schneller Pfad-/Dateinamensuche gefunden.") | Out-Null }
    else {
        foreach ($h in $legacyHits) { $lines.Add("WARN: " + $h) | Out-Null }
    }
}
$lines.Add("") | Out-Null
$lines.Add("Repo-Source-Schnellcheck:") | Out-Null
if (Test-Path -LiteralPath $RepoCurrentSourcePath) {
    foreach ($name in @("DeutschZ_Core","DeutschZ_ExpansionBridge","DeutschZ_KotHZ","DeutschZ_ConvoyZ","DeutschZ_GroundZero","DeutschZ_CourierZ","DeutschZ_OperationDeutschZ")) {
        $rp = Join-Path $RepoCurrentSourcePath $name
        if (Test-Path -LiteralPath $rp) { $lines.Add("OK_REPO_SOURCE: " + $name + " -> " + $rp) | Out-Null }
        else { $lines.Add("FEHLT/optional_REPO_SOURCE: " + $name + " -> " + $rp) | Out-Null }
    }
} else {
    $lines.Add("HINWEIS: Repo-Source-Pfad nicht erreichbar. Keine Fallback-Nutzung, nur Check.") | Out-Null
}
Add-Report "03_SOURCE_FILES_CHECK.txt" $lines

# Safe export mission
$exportRoot = Join-Path $UploadDir $SafeServerSettingsExportFolderName
if (Test-Path -LiteralPath $exportRoot) { Remove-Item -LiteralPath $exportRoot -Recurse -Force }
$exportMissionRoot = Join-Path $exportRoot "mpmission\dayzOffline.chernarusplus"
Copy-SafeMissionExport -SourceMission $LiveMissionCePath -TargetMission $exportMissionRoot

# Profile safe inventory only
$profileReportLines = New-Object System.Collections.Generic.List[string]
$profileReportLines.Add("05 PROFILES SAFE INVENTORY") | Out-Null
$profileReportLines.Add("==========================") | Out-Null
$profileReportLines.Add("Quelle: $LiveProfilesPath") | Out-Null
$profileReportLines.Add("Regel: Profiles werden nicht roh exportiert. Logs/Storage/Spielerdaten/Secrets bleiben draussen.") | Out-Null
if (Test-Path -LiteralPath $LiveProfilesPath) {
    $profileReportLines.Add("STATUS: OK - Profiles erreichbar") | Out-Null
    $top = @(Get-ChildItem -LiteralPath $LiveProfilesPath -Force -ErrorAction SilentlyContinue | Select-Object -First 80)
    foreach ($item in $top) {
        if ($item.PSIsContainer) { $profileReportLines.Add("- DIR  " + $item.Name) | Out-Null }
        else { $profileReportLines.Add("- FILE " + $item.Name + " | Bytes=" + $item.Length) | Out-Null }
    }
} else {
    $profileReportLines.Add("STATUS: WARN - Profiles nicht erreichbar") | Out-Null
}
Add-Report "05_PROFILES_SAFE_INVENTORY.txt" $profileReportLines

# Mission healthcheck
$lines = New-Object System.Collections.Generic.List[string]
$lines.Add("04 MISSION CE HEALTHCHECK") | Out-Null
$lines.Add("=========================") | Out-Null
$lines.Add("LiveMissionCePath: $LiveMissionCePath") | Out-Null
$lines.Add("ExportMissionRoot: $exportMissionRoot") | Out-Null
$xmlErrors = New-Object System.Collections.Generic.List[string]
$jsonErrors = New-Object System.Collections.Generic.List[string]
$coreRefs = New-Object System.Collections.Generic.List[string]
$coreMissing = New-Object System.Collections.Generic.List[string]

if (Test-Path -LiteralPath $exportMissionRoot) {
    foreach ($f in Get-ChildItem -LiteralPath $exportMissionRoot -Recurse -File -ErrorAction SilentlyContinue) {
        if ($f.Extension.ToLowerInvariant() -eq ".xml") {
            $err = Test-XmlFile $f.FullName
            if ($err) { $xmlErrors.Add($f.FullName + " :: " + $err) | Out-Null }
        } elseif ($f.Extension.ToLowerInvariant() -eq ".json") {
            $err = Test-JsonFile $f.FullName
            if ($err) { $jsonErrors.Add($f.FullName + " :: " + $err) | Out-Null }
        }
    }
    $corePath = Join-Path $exportMissionRoot "cfgeconomycore.xml"
    if (Test-Path -LiteralPath $corePath) {
        try {
            [xml]$coreXml = Get-Content -LiteralPath $corePath -Raw -Encoding UTF8
            foreach ($ce in $coreXml.economycore.ce) {
                $folder = [string]$ce.folder
                foreach ($fileNode in $ce.file) {
                    $name = [string]$fileNode.name
                    $type = [string]$fileNode.type
                    if (-not [string]::IsNullOrWhiteSpace($folder) -and -not [string]::IsNullOrWhiteSpace($name)) {
                        $rel = $folder + "\" + $name
                        $coreRefs.Add($rel + " | type=" + $type) | Out-Null
                        $target = Join-Path $exportMissionRoot $rel
                        if (-not (Test-Path -LiteralPath $target)) {
                            $coreMissing.Add($rel) | Out-Null
                        }
                    }
                }
            }
        } catch {
            $xmlErrors.Add("cfgeconomycore.xml reference read failed :: " + $_.Exception.Message) | Out-Null
        }
    } else {
        $xmlErrors.Add("cfgeconomycore.xml fehlt im Safe Export") | Out-Null
    }
} else {
    $lines.Add("STATUS: WARN - ExportMissionRoot nicht vorhanden, wahrscheinlich Mission/CE nicht erreichbar.") | Out-Null
}

$lines.Add("") | Out-Null
$lines.Add("XML Parse Errors: " + $xmlErrors.Count) | Out-Null
foreach ($e in $xmlErrors) { $lines.Add("  XML_ERROR: " + $e) | Out-Null }
$lines.Add("JSON Parse Errors: " + $jsonErrors.Count) | Out-Null
foreach ($e in $jsonErrors) { $lines.Add("  JSON_ERROR: " + $e) | Out-Null }
$lines.Add("cfgeconomycore Referenzen: " + $coreRefs.Count) | Out-Null
foreach ($r in $coreRefs) { $lines.Add("  REF: " + $r) | Out-Null }
if ($coreMissing.Count -eq 0) { $lines.Add("cfgeconomycore Referenzen: OK") | Out-Null }
else {
    $lines.Add("cfgeconomycore Referenzen fehlen: " + $coreMissing.Count) | Out-Null
    foreach ($m in $coreMissing) { $lines.Add("  MISSING: " + $m) | Out-Null; Add-Warn ("cfgeconomycore Referenz fehlt: " + $m) }
}
Add-Report "04_MISSION_CE_HEALTHCHECK.txt" $lines
Add-Report "61_SERVERSETTINGS_EXPORT_HEALTHCHECK.txt" $lines

# Event alignment
$lines = New-Object System.Collections.Generic.List[string]
$lines.Add("12 EVENT WATCHLIST") | Out-Null
$lines.Add("==================") | Out-Null
$eventsXml = Join-Path $exportMissionRoot "db\events.xml"
$spawnsXml = Join-Path $exportMissionRoot "cfgeventspawns.xml"
$expEventsXml = Join-Path $exportMissionRoot "expansion_ce\expansion_events.xml"
$eventDefs = New-Object 'System.Collections.Generic.HashSet[string]'
$spawnDefs = New-Object 'System.Collections.Generic.HashSet[string]'
$expDefs = New-Object 'System.Collections.Generic.HashSet[string]'
try {
    if (Test-Path -LiteralPath $eventsXml) {
        [xml]$x = Get-Content -LiteralPath $eventsXml -Raw -Encoding UTF8
        foreach ($e in $x.events.event) { if ($e.name) { $null = $eventDefs.Add([string]$e.name) } }
    }
} catch {}
try {
    if (Test-Path -LiteralPath $spawnsXml) {
        [xml]$x = Get-Content -LiteralPath $spawnsXml -Raw -Encoding UTF8
        foreach ($e in $x.eventposdef.event) { if ($e.name) { $null = $spawnDefs.Add([string]$e.name) } }
    }
} catch {}
try {
    if (Test-Path -LiteralPath $expEventsXml) {
        [xml]$x = Get-Content -LiteralPath $expEventsXml -Raw -Encoding UTF8
        foreach ($e in $x.events.event) { if ($e.name) { $null = $expDefs.Add([string]$e.name) } }
    }
} catch {}
$lines.Add("db/events.xml Events: " + $eventDefs.Count) | Out-Null
$lines.Add("cfgeventspawns.xml Events: " + $spawnDefs.Count) | Out-Null
$lines.Add("expansion_events.xml Events: " + $expDefs.Count) | Out-Null
$watch = @("ItemPlanks","StaticAirplaneCrate","StaticContaminatedArea","StaticHeliCrash","StaticMilitaryConvoy","StaticPoliceSituation","StaticTrain","VehicleBoat","VehicleCivilianSedan","VehicleHatchback02","VehicleOffroad02","VehicleOffroadHatchback","VehicleSedan02","VehicleTruck01")
foreach ($w in $watch) {
    $def = $eventDefs.Contains($w) -or $expDefs.Contains($w)
    $spawn = $spawnDefs.Contains($w)
    $status = "OK"
    if ($def -and -not $spawn) { $status = "WARN_NO_SPAWNS" }
    elseif (-not $def -and $spawn) { $status = "WARN_SPAWN_WITHOUT_DEFINITION" }
    elseif (-not $def -and -not $spawn) { $status = "NOT_PRESENT" }
    $lines.Add($w + ": Definition=" + $def + " SpawnPositions=" + $spawn + " Status=" + $status) | Out-Null
}
Add-Report "12_EVENT_WATCHLIST.txt" $lines
Add-Report "63_CE_EVENT_ALIGNMENT_CHECK.txt" $lines

# CE event action pack - safe ready-to-copy only, no live write
$ceFixRoot = Join-Path $UploadDir $CeEventFixFolderName
if (Test-Path -LiteralPath $ceFixRoot) { Remove-Item -LiteralPath $ceFixRoot -Recurse -Force -ErrorAction SilentlyContinue }
Ensure-Dir $ceFixRoot
Ensure-Dir (Join-Path $ceFixRoot "db")
Ensure-Dir (Join-Path $ceFixRoot "expansion_ce")
$ceFixLines = New-Object System.Collections.Generic.List[string]
$ceFixLines.Add("64 CE EVENT ACTION PACK") | Out-Null
$ceFixLines.Add("=======================") | Out-Null
$ceFixLines.Add("Zweck: Copy-Paket fuer Events mit Definition=True aber ohne cfgeventspawns-Positionen.") | Out-Null
$ceFixLines.Add("Regel: DZSM schreibt NICHT live. Diese Dateien sind nur vorbereitet unter CE_EVENT_FIX_READY_TO_COPY.") | Out-Null
$ceFixLines.Add("Empfehlung: Nur verwenden, wenn die Console weiterhin 'setup is invalid, event will be disabled' meldet.") | Out-Null
$ceFixLines.Add("") | Out-Null
$ceFixLines.Add("Betroffene Watchlist:") | Out-Null
foreach ($w in $watch) {
    $def = $eventDefs.Contains($w) -or $expDefs.Contains($w)
    $spawn = $spawnDefs.Contains($w)
    if ($def -and -not $spawn) { $ceFixLines.Add("  DISABLE_CANDIDATE: " + $w) | Out-Null }
}
$disabledDb = New-Object System.Collections.Generic.List[string]
$disabledExp = New-Object System.Collections.Generic.List[string]
try {
    if (Test-Path -LiteralPath $eventsXml) {
        [xml]$dbx = Get-Content -LiteralPath $eventsXml -Raw -Encoding UTF8
        foreach ($e in $dbx.events.event) {
            $n = [string]$e.name
            if ($watch -contains $n) {
                $hasSpawn = $spawnDefs.Contains($n)
                if (-not $hasSpawn) {
                    if ($e.active) { $e.active = "0" }
                    if ($e.nominal) { $e.nominal = "0" }
                    if ($e.min) { $e.min = "0" }
                    $disabledDb.Add($n) | Out-Null
                }
            }
        }
        $dbTarget = Join-Path $ceFixRoot "db\events.xml"
        $dbx.Save($dbTarget)
    }
} catch {
    $ceFixLines.Add("DB_EVENTS_FIX_ERROR: " + $_.Exception.Message) | Out-Null
    Add-Warn ("CE Event Action Pack db/events.xml Fehler: " + $_.Exception.Message)
}
try {
    if (Test-Path -LiteralPath $expEventsXml) {
        [xml]$expx = Get-Content -LiteralPath $expEventsXml -Raw -Encoding UTF8
        foreach ($e in $expx.events.event) {
            $n = [string]$e.name
            if ($watch -contains $n) {
                $hasSpawn = $spawnDefs.Contains($n)
                if (-not $hasSpawn) {
                    if ($e.active) { $e.active = "0" }
                    if ($e.nominal) { $e.nominal = "0" }
                    if ($e.min) { $e.min = "0" }
                    $disabledExp.Add($n) | Out-Null
                }
            }
        }
        $expTarget = Join-Path $ceFixRoot "expansion_ce\expansion_events.xml"
        $expx.Save($expTarget)
    }
} catch {
    $ceFixLines.Add("EXPANSION_EVENTS_FIX_ERROR: " + $_.Exception.Message) | Out-Null
    Add-Warn ("CE Event Action Pack expansion_events.xml Fehler: " + $_.Exception.Message)
}
$readmeCe = @(
"CE EVENT FIX READY TO COPY",
"==========================",
"",
"Dieses Paket ist ein MANUELLER Vorschlag. DZSM hat live nichts geaendert.",
"",
"Zielpfade beim Einspielen:",
"db\events.xml -> mpmission\dayzOffline.chernarusplus\db\events.xml",
"expansion_ce\expansion_events.xml -> mpmission\dayzOffline.chernarusplus\expansion_ce\expansion_events.xml",
"",
"Wirkung:",
"Events aus der Watchlist ohne cfgeventspawns-Positionen werden auf active=0, nominal=0, min=0 gesetzt.",
"Damit sollen Console-Warnungen wie 'setup is invalid, event will be disabled' verschwinden, ohne Positionen zu erfinden.",
"",
"Vorher Backup machen. Nur einspielen, wenn du diese Vanilla/Expansion DynamicEvents bewusst deaktivieren willst.",
"DeutschZ KotHZ/ConvoyZ ist davon nicht betroffen."
) -join [Environment]::NewLine
Write-Utf8NoBom (Join-Path $ceFixRoot "README_CE_EVENT_FIX_READY_TO_COPY.txt") ($readmeCe + [Environment]::NewLine)
$ceFixLines.Add("") | Out-Null
$ceFixLines.Add("Generierte Dateien:") | Out-Null
$ceFixLines.Add("  CE_EVENT_FIX_READY_TO_COPY\README_CE_EVENT_FIX_READY_TO_COPY.txt") | Out-Null
if (Test-Path -LiteralPath (Join-Path $ceFixRoot "db\events.xml")) { $ceFixLines.Add("  CE_EVENT_FIX_READY_TO_COPY\db\events.xml") | Out-Null }
if (Test-Path -LiteralPath (Join-Path $ceFixRoot "expansion_ce\expansion_events.xml")) { $ceFixLines.Add("  CE_EVENT_FIX_READY_TO_COPY\expansion_ce\expansion_events.xml") | Out-Null }
$ceFixLines.Add("") | Out-Null
$ceFixLines.Add("db/events.xml deaktiviert: " + ($disabledDb -join ", ")) | Out-Null
$ceFixLines.Add("expansion_ce/expansion_events.xml deaktiviert: " + ($disabledExp -join ", ")) | Out-Null
Add-Report "64_CE_EVENT_ACTION_PACK.txt" $ceFixLines

# Types preset scanner - safe ready-to-copy only, no live write
Invoke-DZSMTypesPresetScanner -MissionRoot $exportMissionRoot

# Vehicle spawn setup - safe ready-to-copy only, no live write
Invoke-DZSMVehicleSpawnSetup -MissionRoot $exportMissionRoot

# Automatic log analysis
Invoke-DZSMLogAnalysis

# Phase A
$phaseLine = Write-PhaseAPackage
$lines = New-Object System.Collections.Generic.List[string]
$lines.Add("06 PHASE A MODLIST READY TO COPY") | Out-Null
$lines.Add("================================") | Out-Null
$lines.Add("Quelle fuer Basis-Mods: " + (Join-Path $LiveRoot "modlist.txt")) | Out-Null
$lines.Add("Regel: Kein -mod= davor. Kein BOM. Direkt mit @ anfangen.") | Out-Null
$lines.Add("") | Out-Null
$lines.Add("DeutschZ Pflichtreihenfolge:") | Out-Null
$lines.Add("1. @DeutschZ_Core") | Out-Null
$lines.Add("2. @DeutschZ_ExpansionBridge") | Out-Null
$lines.Add("3. @DeutschZ_KotHZ(InfectedSiege)") | Out-Null
$lines.Add("4. @DeutschZ_ConvoyZ") | Out-Null
$lines.Add("5. @DeutschZ_Screen_Menu optional") | Out-Null
$lines.Add("") | Out-Null
$lines.Add("KOPIERFERTIGE modlist.txt ZEILE:") | Out-Null
$lines.Add($phaseLine) | Out-Null
Add-Report "06_PHASE_A_MODLIST_READY_TO_COPY.txt" $lines
Add-Report "70_PHASE_A_MODLIST_READY_TO_COPY.txt" $lines

$lines2 = New-Object System.Collections.Generic.List[string]
$lines2.Add("-mod=" + $phaseLine) | Out-Null
Add-Report "07_PHASE_A_SERVER_STARTPARAMETER_READY_TO_COPY.txt" $lines2
Add-Report "71_PHASE_A_SERVER_STARTPARAMETER_READY_TO_COPY.txt" $lines2

# BOM check
$lines = New-Object System.Collections.Generic.List[string]
$lines.Add("08 BOM ENCODING CHECK") | Out-Null
$lines.Add("=====================") | Out-Null
foreach ($fileName in @("PHASE_A_READY_TO_COPY\modlist.txt", "PHASE_A_READY_TO_COPY\server_startparameter.txt", "06_PHASE_A_MODLIST_READY_TO_COPY.txt")) {
    $p = Join-Path $UploadDir $fileName
    if (Test-Path -LiteralPath $p) {
        $bytes = [System.IO.File]::ReadAllBytes($p)
        $hasBom = ($bytes.Length -ge 3 -and $bytes[0] -eq 239 -and $bytes[1] -eq 187 -and $bytes[2] -eq 191)
        $first = ""
        if ($bytes.Length -gt 0) { $first = [string]$bytes[0] }
        $lines.Add($fileName + ": BOM=" + $hasBom + " FirstByte=" + $first) | Out-Null
    } else {
        $lines.Add($fileName + ": FEHLT") | Out-Null
    }
}
Add-Report "08_BOM_ENCODING_CHECK.txt" $lines
Add-Report "77_PHASE_A_MODLIST_ENCODING_GUARD.txt" $lines

# Safe export zip
if (Test-Path -LiteralPath $exportRoot) {
    $readme = "SERVERSETTINGS SAFE EXPORT" + [Environment]::NewLine +
              "==========================" + [Environment]::NewLine +
              "Quelle Mission/CE: $LiveMissionCePath" + [Environment]::NewLine +
              "Quelle Profiles: $LiveProfilesPath" + [Environment]::NewLine +
              "Regel: Storage/Logs/Secrets/Spielerdaten werden nicht roh exportiert." + [Environment]::NewLine
    Write-Utf8NoBom (Join-Path $exportRoot "README_SAFE_EXPORT.txt") $readme
    $manifest = New-Object System.Collections.Generic.List[string]
    $manifest.Add("RelativePath,Bytes,SHA1") | Out-Null
    foreach ($f in Get-ChildItem -LiteralPath $exportRoot -Recurse -File -ErrorAction SilentlyContinue) {
        $rel = $f.FullName.Substring($exportRoot.Length).TrimStart("\")
        $manifest.Add(('"{0}",{1},{2}' -f $rel.Replace('"','""'), $f.Length, (Get-FileSha1 $f.FullName))) | Out-Null
    }
    Write-Utf8NoBom (Join-Path $UploadDir "58_SERVERSETTINGS_SAFE_EXPORT_MANIFEST.csv") (($manifest -join [Environment]::NewLine) + [Environment]::NewLine)
    Write-Utf8NoBom (Join-Path $UploadDir "11_SAFE_EXPORT_MANIFEST.csv") (($manifest -join [Environment]::NewLine) + [Environment]::NewLine)

    $safeZip = Join-Path $UploadDir $SafeServerSettingsExportZipName
    if (Test-Path -LiteralPath $safeZip) { Remove-Item -LiteralPath $safeZip -Force }
    Compress-Archive -Path (Join-Path $exportRoot "*") -DestinationPath $safeZip -Force
}

# Summary json
$summary = [ordered]@{
    version = $Version
    runStamp = $RunStamp
    root = $Root
    toolDir = $ToolDir
    reportsDir = $ReportsRoot
    uploadDir = $UploadDir
    desktopPath = (Get-DZSMDesktopPath)
    liveSourceFilesPath = $LiveSourceFilesPath
    repoCurrentSourcePath = $RepoCurrentSourcePath
    liveReadyModsPath = $LiveReadyModsPath
    liveMissionCePath = $LiveMissionCePath
    liveProfilesPath = $LiveProfilesPath
    liveLogsPath = $LiveLogsPath
    vanillaTypesPath = $VanillaTypesPath
    typesBaselineRoot = $TypesBaselineRoot
    selectedTypesPreset = $Global:SelectedTypesPreset
    selectedVehicleSpawnPreset = $Global:SelectedVehicleSpawnPreset
    logAnalysisStatus = $Global:LogAnalysisStatus
    discordSendStatus = $Global:DiscordSendStatus
    webhookCheckStatus = $Global:WebhookCheckStatus
    repoConfigIsAuthoritative = $false
    gitWrite = $false
    repoWrite = $false
    build = $false
    warnings = @($Global:Warnings)
}
Write-Utf8NoBom (Join-Path $UploadDir "15_DZSM_SUMMARY.json") ($summary | ConvertTo-Json -Depth 8)

# Next steps
$lines = New-Object System.Collections.Generic.List[string]
$lines.Add("99 NAECHSTE SCHRITTE") | Out-Null
$lines.Add("====================") | Out-Null
$lines.Add("1. Wenn alle vier Live-Pfade OK sind: Reports im Uploadordner pruefen.") | Out-Null
$lines.Add("2. Bei Servertest Phase A verwenden: @DeutschZ_Core;@DeutschZ_ExpansionBridge;@DeutschZ_KotHZ(InfectedSiege);@DeutschZ_ConvoyZ;@DeutschZ_Screen_Menu") | Out-Null
$lines.Add("3. Wenn Event-Watchlist WARN_NO_SPAWNS zeigt: optional CE_EVENT_FIX_READY_TO_COPY pruefen oder echte Spawnpositionen ergaenzen.") | Out-Null
$lines.Add("4. Types/Fahrzeug Presets aus Desktop\Datei Ausgabe nutzen, niemals ohne Backup.") | Out-Null
$lines.Add("5. GroundZero/CourierZ erst nach sauberem Test nachziehen.") | Out-Null
$lines.Add("6. Keine Git-/Repo-Aktion parallel zum Servertest.") | Out-Null
Add-Report "99_NAECHSTE_SCHRITTE.txt" $lines

Invoke-DZSMGitHubPreparation
Publish-DZSMDesktopFileOutput
$preFinalSuccess = -not $Global:HadError
Send-DZSMDiscordStatus -Success $preFinalSuccess

# Upload package log
$lines = New-Object System.Collections.Generic.List[string]
$lines.Add("26 UPLOAD PACKAGE LOG") | Out-Null
$lines.Add("=====================") | Out-Null
$lines.Add("UploadDir: $UploadDir") | Out-Null
$lines.Add("Version: $Version") | Out-Null
$lines.Add("Reports: " + $Global:ReportFiles.Count) | Out-Null
Add-Report "26_UPLOAD_PACKAGE_LOG.txt" $lines

$uploadZip = Build-UploadPackage
$desktopUploadZip = Publish-DesktopUploadPackage -UploadPackagePath $uploadZip

function Wait-DZSMCountdown {
    param([int]$Seconds = 30)
    try {
        Write-Host ""
        for ($i = $Seconds; $i -gt 0; $i--) {
            $msg = "Fenster schliesst in $i Sekunden. Taste = sofort schliessen.   "
            try { Write-Host -NoNewline ("`r" + $msg) -ForegroundColor DarkGray } catch { Write-Host -NoNewline ("`r" + $msg) }
            try {
                if ([Console]::KeyAvailable) {
                    [Console]::ReadKey($true) | Out-Null
                    break
                }
            } catch {}
            Start-Sleep -Seconds 1
        }
        Write-Host ""
    } catch {
        Start-Sleep -Seconds $Seconds
    }
}

function Write-DZSMClassicFrame {
    param(
        [bool]$Success
    )

    $statusColor = "Green"
    if (-not $Success) { $statusColor = "Red" }

    $logoLines = @(
"██████╗ ███████╗██╗   ██╗████████╗███████╗ ██████╗██╗  ██╗███████╗",
"██╔══██╗██╔════╝██║   ██║╚══██╔══╝██╔════╝██╔════╝██║  ██║╚══███╔╝",
"██║  ██║█████╗  ██║   ██║   ██║   ███████╗██║     ███████║  ███╔╝ ",
"██║  ██║██╔══╝  ██║   ██║   ██║   ╚════██║██║     ██╔══██║ ███╔╝  ",
"██████╔╝███████╗╚██████╔╝   ██║   ███████║╚██████╗██║  ██║███████╗",
"╚═════╝ ╚══════╝ ╚═════╝    ╚═╝   ╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝"
    )

    if ($Success) {
        $statusLines = @(
"║                    ██████╗  ██████╗ ███╗   ██╗███████╗                    ║",
"║                    ██╔══██╗██╔═══██╗████╗  ██║██╔════╝                    ║",
"║                    ██║  ██║██║   ██║██╔██╗ ██║█████╗                      ║",
"║                    ██║  ██║██║   ██║██║╚██╗██║██╔══╝                      ║",
"║                    ██████╔╝╚██████╔╝██║ ╚████║███████╗                    ║",
"║                    ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚══════╝                    ║"
        )
    } else {
        $statusLines = @(
"║                    ███████╗ █████╗ ██╗██╗                                  ║",
"║                    ██╔════╝██╔══██╗██║██║                                  ║",
"║                    █████╗  ███████║██║██║                                  ║",
"║                    ██╔══╝  ██╔══██║██║██║                                  ║",
"║                    ██║     ██║  ██║██║███████╗                             ║",
"║                    ╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝                             ║"
        )
    }

    foreach ($l in $logoLines) { Write-Host $l -ForegroundColor $statusColor }
    Write-Host "" 
    Write-Host "╔══════════════════════════════════════════════════════════════════════════════╗" -ForegroundColor $statusColor
    Write-Host "║                                                                              ║" -ForegroundColor $statusColor
    Write-Host "║                         D E U T S C H Z - A N A L Y Z E                    ║" -ForegroundColor $statusColor
    Write-Host "║                                                                              ║" -ForegroundColor $statusColor
    Write-Host "╠══════════════════════════════════════════════════════════════════════════════╣" -ForegroundColor $statusColor
    Write-Host "║                                                                              ║" -ForegroundColor $statusColor
    foreach ($l in $statusLines) { Write-Host $l -ForegroundColor $statusColor }
    Write-Host "║                                                                              ║" -ForegroundColor $statusColor
    Write-Host "╚══════════════════════════════════════════════════════════════════════════════╝" -ForegroundColor $statusColor
}


function Get-DZSMFinalChangeSummary {
    $items = New-Object System.Collections.Generic.List[string]
    try { $items.Add("Types Setup: " + $Global:SelectedTypesPreset) | Out-Null } catch {}
    try { $items.Add("Fahrzeugspawns: " + $Global:SelectedVehicleSpawnPreset) | Out-Null } catch {}
    try { $items.Add("GitHub Vorbereitung: " + $Global:GitHubPreparationMode) | Out-Null } catch {}
    try { $items.Add("Discord: " + $Global:DiscordSendStatus + " / Webhook: " + $Global:WebhookCheckStatus) | Out-Null } catch {}
    try { $items.Add("Logs: " + $Global:LogAnalysisStatus + " - " + $Global:LogAnalysisSummaryText) | Out-Null } catch {}
    try { $items.Add("Desktop: Datei Ausgabe und DZSM_UPLOAD_PACKAGE aktualisiert") | Out-Null } catch {}
    try { $items.Add("Ready-to-Copy: Phase A, CE Events, Types und Fahrzeugspawns erzeugt") | Out-Null } catch {}
    try { $items.Add("Warnungen: " + $Global:Warnings.Count) | Out-Null } catch {}
    return $items
}

function Show-FinalResult {
    param(
        [bool]$Success,
        [string]$UploadPackagePath
    )

    Write-Status "" "Gray"
    Write-Status "Analyse fertiggestellt." "Gray"
    Write-Status "Uploadpaket: $UploadPackagePath" "Gray"
    if ($Global:Warnings.Count -gt 0) { Write-Status ("Warnungen: " + $Global:Warnings.Count) "Yellow" }
    else { Write-Status "Warnungen: 0" "Gray" }
    Write-Status "" "Gray"

    Write-DZSMClassicFrame -Success $Success

    Write-Status "" "Gray"
    if ($Success) { Write-Status "Status: DONE" "Green" }
    else { Write-Status "Status: FAIL" "Red" }

    Write-Host "" 
    if ($Success) { Write-Host "Aenderungen in diesem Lauf:" -ForegroundColor Green }
    else { Write-Host "Ergebnis dieses Laufs:" -ForegroundColor Red }
    foreach ($item in (Get-DZSMFinalChangeSummary)) {
        if ($Success) { Write-Host ("  - " + $item) -ForegroundColor Green }
        else { Write-Host ("  - " + $item) -ForegroundColor Red }
        Append-Log ("FINAL_SUMMARY: " + $item)
    }
    Write-Status "Beenden eingeleitet. Taste schliesst sofort, sonst 30 Sekunden warten." "Gray"
}

$success = $true
if ($Global:HadError) { $success = $false }
if ([string]::IsNullOrWhiteSpace($uploadZip) -or -not (Test-Path -LiteralPath $uploadZip)) { $success = $false }

Show-FinalResult -Success $success -UploadPackagePath $uploadZip
if ($success) { exit 0 }
exit 1
