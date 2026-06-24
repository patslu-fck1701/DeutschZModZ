
# DeutschZ System Manager v0.3.6 ARCHIVE-SHORTCUT-FIX
# Sicherer lokaler Windows-Helfer fuer Patrick / DeutschZ.
# Keine Loeschung, keine Formatierung, keine Uebertaktung, kein PBO-Dekompilieren.
# P:\Root = DayZ Tools WorkDrive/Vanilla-Arbeitsbereich + Legacy/Mischbereich.
# Sauberer Projektstand = P:\GitHub_DeutschZModZ\DeutschZModZ.
# ReadyMods = Build-/PBO-Ausgabe.

$ErrorActionPreference = "Continue"

# ------------------------------------------------------------
# STANDARDSTRUKTUR
# ------------------------------------------------------------
if (Test-Path "D:\") {
    $DZSMBaseRoot = "D:\DeutschZ_System_Manager"
    $DZSMStorageDrive = "D:"
    $DZSMDriveMode = "D_AVAILABLE_STANDARD_STRUCTURE"
} else {
    $DZSMBaseRoot = "C:\DeutschZ_System_Manager"
    $DZSMStorageDrive = "C:"
    $DZSMDriveMode = "C_FALLBACK_STANDARD_STRUCTURE_NO_D_DRIVE"
}

$BackupsRoot = Join-Path $DZSMBaseRoot "backups"
$AppRoot = Join-Path $DZSMBaseRoot "app"
$DocsRoot = Join-Path $DZSMBaseRoot "docs"
$DZSMInstallRoot = Join-Path $DZSMBaseRoot "DZSM_v0_1"
$ReportsRoot = Join-Path $DZSMBaseRoot "reports"
$ScriptsRoot = Join-Path $DZSMBaseRoot "scripts"
$ArbeitsstandFile = Join-Path $DZSMBaseRoot "Arbeitsstand aktuell.txt"
$ArchiveRoot = Join-Path $DZSMInstallRoot "_archive_old_versions"
$CurrentVersionToken = "0_3_6"

$DeutschZRepoRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ"
$GitHubExportRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ\DeutschZ_SystemManager_Tool"
$GitHubSafetyDocsRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ\DeutschZ_SystemManager_Tool_Dokumentation"

$structureDirs = @($DZSMBaseRoot, $BackupsRoot, $AppRoot, $DocsRoot, $DZSMInstallRoot, $ReportsRoot, $ScriptsRoot, $ArchiveRoot)
foreach ($dir in $structureDirs) {
    New-Item -ItemType Directory -Path $dir -Force | Out-Null
}

# ------------------------------------------------------------
# REPORTDATEIEN
# ------------------------------------------------------------
$ReportFile          = Join-Path $ReportsRoot "00_ZUSAMMENFASSUNG.txt"
$ProgramsFile        = Join-Path $ReportsRoot "01_INSTALLIERTE_PROGRAMME.csv"
$DrivesFile          = Join-Path $ReportsRoot "02_LAUFWERKE.csv"
$NetworkFile         = Join-Path $ReportsRoot "03_NETZWERK.txt"
$ProcessesFile       = Join-Path $ReportsRoot "04_PROZESSE_TOP_RAM.csv"
$SteamFile           = Join-Path $ReportsRoot "05_STEAM_DAYZ_CHECK.txt"
$PathsFile           = Join-Path $ReportsRoot "06_BEKANNTE_PFADE_CHECK.txt"
$StartupFile         = Join-Path $ReportsRoot "07_AUTOSTART.txt"
$PDriveFile          = Join-Path $ReportsRoot "08_P_DRIVE_CHECK.txt"
$MountLogFile        = Join-Path $ReportsRoot "09_DAYZTOOLS_MOUNT_LOG.txt"
$BackupPlanFile      = Join-Path $ReportsRoot "10_BACKUP_PLAN.txt"
$DeutschZFile        = Join-Path $ReportsRoot "11_DEUTSCHZ_STRUCTURE_CHECK.txt"
$CleanupFile         = Join-Path $ReportsRoot "12_CLEANUP_RISK_CHECK_FAST.txt"
$MigrationFile       = Join-Path $ReportsRoot "13_WINDOWS_SSD_MIGRATION_CHECK.txt"
$FolderCheckFile     = Join-Path $ReportsRoot "14_IMPORTANT_FOLDER_CHECK_FAST.csv"
$SummaryJsonFile     = Join-Path $ReportsRoot "15_DZSM_SUMMARY.json"
$SelfCleanupFile     = Join-Path $ReportsRoot "16_DZSM_SELF_CLEANUP.txt"
$AutoBackupLogFile   = Join-Path $ReportsRoot "17_SAFE_AUTO_BACKUP_LOG.txt"
$StructureFile       = Join-Path $ReportsRoot "18_DZSM_STANDARD_STRUCTURE.txt"
$GitHubExportLogFile = Join-Path $ReportsRoot "19_GITHUB_EXPORT_LOG.txt"
$SafetyDocsLogFile   = Join-Path $ReportsRoot "21_GITHUB_SAFETY_DOCS_LOG.txt"
$WorkDriveNotesFile  = Join-Path $ReportsRoot "22_P_ROOT_WORKDRIVE_NOTES.txt"
$LMStudioPolicyFile   = Join-Path $ReportsRoot "23_LMSTUDIO_MODEL_POLICY.txt"
$ShortcutLogFile      = Join-Path $ReportsRoot "24_DESKTOP_SHORTCUTS_LOG.txt"
$NextFile            = Join-Path $ReportsRoot "99_NAECHSTE_SCHRITTE.txt"

$allReportFiles = @(
    $ReportFile,$ProgramsFile,$DrivesFile,$NetworkFile,$ProcessesFile,$SteamFile,$PathsFile,$StartupFile,
    $PDriveFile,$MountLogFile,$BackupPlanFile,$DeutschZFile,$CleanupFile,$MigrationFile,$FolderCheckFile,
    $SummaryJsonFile,$SelfCleanupFile,$AutoBackupLogFile,$StructureFile,$GitHubExportLogFile,
    $SafetyDocsLogFile,$WorkDriveNotesFile,$LMStudioPolicyFile,$ShortcutLogFile,$NextFile
)
foreach ($rf in $allReportFiles) {
    if (Test-Path $rf) { Remove-Item $rf -Force -ErrorAction SilentlyContinue }
}

# ------------------------------------------------------------
# HELFER
# ------------------------------------------------------------
function Test-PathFast($path) {
    try { return (Test-Path $path) } catch { return $false }
}

function Convert-BytesToGB($bytes) {
    if ($null -eq $bytes -or $bytes -eq "") { return "" }
    return [math]::Round(([double]$bytes / 1GB), 2)
}

function Append-Line($file, $text) {
    $text | Out-File -FilePath $file -Append -Encoding UTF8
}

function Write-Log($text) {
    $line = "[$(Get-Date -Format 'HH:mm:ss')] $text"
    $line | Out-File -FilePath $MountLogFile -Append -Encoding UTF8
    Write-Host $line
}

function Write-Section($title) {
    "`r`n============================================================" | Out-File -FilePath $ReportFile -Append -Encoding UTF8
    $title | Out-File -FilePath $ReportFile -Append -Encoding UTF8
    "============================================================" | Out-File -FilePath $ReportFile -Append -Encoding UTF8
}

function Safe-Out($title, $scriptBlock) {
    Write-Section $title
    try {
        & $scriptBlock | Out-String -Width 350 | Out-File -FilePath $ReportFile -Append -Encoding UTF8
    } catch {
        "FEHLER bei $title : $($_.Exception.Message)" | Out-File -FilePath $ReportFile -Append -Encoding UTF8
    }
}

function Get-FolderQuickInfo($path) {
    $exists = Test-PathFast $path
    $fileCountTop = ""
    $dirCountTop = ""
    $sizeTopGB = ""
    $lastWrite = ""
    if ($exists) {
        try {
            $items = Get-ChildItem -Path $path -Force -ErrorAction SilentlyContinue
            $files = $items | Where-Object { -not $_.PSIsContainer }
            $dirs = $items | Where-Object { $_.PSIsContainer }
            $fileCountTop = ($files | Measure-Object).Count
            $dirCountTop = ($dirs | Measure-Object).Count
            $bytes = ($files | Measure-Object -Property Length -Sum).Sum
            $sizeTopGB = Convert-BytesToGB $bytes
            $lastWrite = (Get-Item $path -ErrorAction SilentlyContinue).LastWriteTime
        } catch {}
    }
    return [PSCustomObject]@{
        Path = $path
        Exists = $exists
        TopLevelFiles = $fileCountTop
        TopLevelFolders = $dirCountTop
        TopLevelFileSizeGB = $sizeTopGB
        LastWriteTime = $lastWrite
    }
}

function Get-SteamPath {
    $candidates = @()
    try {
        $steamReg = Get-ItemProperty "HKCU:\Software\Valve\Steam" -ErrorAction SilentlyContinue
        if ($steamReg.SteamPath) { $candidates += $steamReg.SteamPath }
    } catch {}
    $candidates += @(
        "F:\Programme",
        "C:\Program Files (x86)\Steam",
        "C:\Program Files\Steam",
        "D:\Steam",
        "D:\SteamLibrary",
        "F:\SteamLibrary"
    )
    foreach ($c in $candidates | Select-Object -Unique) {
        if ($c -and (Test-PathFast (Join-Path $c "steam.exe"))) {
            try { return (Resolve-Path $c).Path } catch { return $c }
        }
    }
    return $null
}

function Get-SteamLibraries($steamPath) {
    $libs = @()
    if ($steamPath) { $libs += $steamPath }
    if ($steamPath) {
        $vdf = Join-Path $steamPath "steamapps\libraryfolders.vdf"
        if (Test-PathFast $vdf) {
            try {
                $lines = Get-Content $vdf -ErrorAction SilentlyContinue
                foreach ($line in $lines) {
                    if ($line -match '"path"\s+"(.+)"') {
                        $p = $Matches[1] -replace '\\\\','\'
                        if (Test-PathFast $p) { $libs += $p }
                    }
                }
            } catch {}
        }
    }
    return ($libs | Select-Object -Unique)
}

function Find-DayZToolsPath($steamPath) {
    $libs = Get-SteamLibraries $steamPath
    $candidates = @()
    foreach ($lib in $libs) {
        $candidates += Join-Path $lib "steamapps\common\DayZ Tools"
        $candidates += Join-Path $lib "steamapps\common\DayZTools"
    }
    foreach ($lib in $libs) {
        $manifest = Join-Path $lib "steamapps\appmanifest_830640.acf"
        if (Test-PathFast $manifest) {
            try {
                $content = Get-Content $manifest -ErrorAction SilentlyContinue
                foreach ($line in $content) {
                    if ($line -match '"installdir"\s+"(.+)"') {
                        $dir = $Matches[1]
                        $candidates += Join-Path $lib ("steamapps\common\" + $dir)
                    }
                }
            } catch {}
        }
    }
    foreach ($c in $candidates | Select-Object -Unique) {
        if (Test-PathFast $c) {
            try { return (Resolve-Path $c).Path } catch { return $c }
        }
    }
    return $null
}

function Find-WorkDriveExe($dayzToolsPath) {
    $candidates = @()
    if ($dayzToolsPath) {
        $candidates += Join-Path $dayzToolsPath "Bin\WorkDrive\WorkDrive.exe"
        $candidates += Join-Path $dayzToolsPath "Bin\WorkDrive.exe"
        $candidates += Join-Path $dayzToolsPath "WorkDrive\WorkDrive.exe"
        $candidates += Join-Path $dayzToolsPath "WorkDrive.exe"
    }
    foreach ($c in $candidates) {
        if (Test-PathFast $c) {
            try { return (Resolve-Path $c).Path } catch { return $c }
        }
    }
    if ($dayzToolsPath -and (Test-PathFast $dayzToolsPath)) {
        try {
            $found = Get-ChildItem -Path $dayzToolsPath -Filter "WorkDrive.exe" -File -Recurse -ErrorAction SilentlyContinue | Select-Object -First 1
            if ($found) { return $found.FullName }
        } catch {}
    }
    return $null
}

function Wait-ForPDrive($seconds) {
    for ($i = 1; $i -le $seconds; $i++) {
        if (Test-PathFast "P:\") { return $true }
        Start-Sleep -Seconds 1
    }
    return (Test-PathFast "P:\")
}

function Try-StartDayZToolsAndMountP {
    Write-Log "Starte P-Drive Vorbereitung..."

    if (Test-PathFast "P:\") {
        Write-Log "P:\ ist bereits aktiv/gemountet. DayZ Tools Start wird uebersprungen."
        return
    }

    Write-Log "P:\ ist noch nicht aktiv. Suche Steam/DayZ Tools..."
    $steamPath = Get-SteamPath
    if ($steamPath) { Write-Log "Steam gefunden: $steamPath" }
    else { Write-Log "Steam.exe nicht gefunden." }

    $dayzToolsPath = $null
    if ($steamPath) {
        $dayzToolsPath = Find-DayZToolsPath $steamPath
        if ($dayzToolsPath) { Write-Log "DayZ Tools Ordner gefunden: $dayzToolsPath" }
        else { Write-Log "DayZ Tools Ordner nicht gefunden. Versuche Steam App 830640." }

        try {
            $steamExe = Join-Path $steamPath "steam.exe"
            if (Test-PathFast $steamExe) {
                Write-Log "Oeffne DayZ Tools ueber Steam AppID 830640..."
                Start-Process -FilePath $steamExe -ArgumentList "-applaunch 830640" -ErrorAction SilentlyContinue
                Start-Sleep -Seconds 10
            }
        } catch {
            Write-Log "DayZ Tools konnte nicht ueber Steam gestartet werden: $($_.Exception.Message)"
        }
    }

    if (Test-PathFast "P:\") {
        Write-Log "P:\ ist nach DayZ Tools Start aktiv."
        return
    }

    if (-not $dayzToolsPath -and $steamPath) {
        $dayzToolsPath = Find-DayZToolsPath $steamPath
    }

    $workDrive = Find-WorkDriveExe $dayzToolsPath
    if ($workDrive) {
        Write-Log "WorkDrive.exe gefunden: $workDrive"
        try {
            Write-Log "Fuehre WorkDrive.exe /mount aus..."
            $proc = Start-Process -FilePath $workDrive -ArgumentList "/mount" -PassThru -Wait -ErrorAction SilentlyContinue
            Write-Log "WorkDrive /mount beendet. ExitCode: $($proc.ExitCode)"
        } catch {
            Write-Log "WorkDrive /mount fehlgeschlagen: $($_.Exception.Message)"
        }
    } else {
        Write-Log "WorkDrive.exe wurde nicht gefunden. Manuell in DayZ Tools mounten."
    }

    if (Wait-ForPDrive 15) { Write-Log "P:\ ist aktiv." }
    else { Write-Log "P:\ ist weiterhin NICHT aktiv. Scan dokumentiert das." }
}


function Invoke-DZSMSelfCleanup {
    "DeutschZ System Manager v0.3.6 - Selbstbereinigung alter Versionen" | Out-File -FilePath $SelfCleanupFile -Encoding UTF8
    "Datum: $(Get-Date)" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
    "InstallRoot: $DZSMInstallRoot" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
    "Aktuelle Version Token: $CurrentVersionToken" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
    "Regel: Alte Versionen werden NICHT geloescht, sondern nach _archive_old_versions verschoben." | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
    "v0.3.6 Fix: Erfasst jetzt auch alte BAT/PS1/README/Config/ZIP-Dateien im Arbeitsordner." | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
    "" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8

    New-Item -ItemType Directory -Path $ArchiveRoot -Force | Out-Null

    $currentScriptRoot = $PSScriptRoot
    try { $currentScriptRootFull = (Resolve-Path $currentScriptRoot).Path } catch { $currentScriptRootFull = $currentScriptRoot }

    $currentScriptPath = $PSCommandPath
    try { $currentScriptPathFull = (Resolve-Path $currentScriptPath).Path } catch { $currentScriptPathFull = $currentScriptPath }

    $currentBatName = "Start_DZSM_v0_3_6_ARCHIVE_SHORTCUT_FIX.bat"
    $currentPs1Name = "DZSM_v0_3_6_Archive_Shortcut_Fix.ps1"
    $currentKeepNames = @(
        $currentBatName,
        $currentPs1Name,
        "README_START.txt",
        "DZSM_Config.json"
    )

    $archiveTarget = Join-Path $ArchiveRoot (Get-Date -Format "yyyy-MM-dd_HH-mm-ss")
    New-Item -ItemType Directory -Path $archiveTarget -Force | Out-Null

    "Aktueller ScriptRoot: $currentScriptRootFull" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
    "Aktueller ScriptPath: $currentScriptPathFull" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
    "Archivziel: $archiveTarget" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
    "" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8

    $candidates = @()
    try {
        # Direkte Dateien im Arbeitsordner erfassen.
        $topFiles = Get-ChildItem -Path $DZSMInstallRoot -File -ErrorAction SilentlyContinue
        foreach ($f in $topFiles) {
            $name = $f.Name
            $isDZSMFile =
                ($name -like "Start_DZSM_*.bat") -or
                ($name -like "DZSM_*.ps1") -or
                ($name -like "DZSM_v*.zip") -or
                ($name -like "DeutschZ_System_Manager*.zip") -or
                ($name -like "README_START*.txt") -or
                ($name -like "DZSM_Config*.json") -or
                ($name -like "*DZSM*.log") -or
                ($name -like "*DZSM*.tmp") -or
                ($name -like "*DZSM*.bak")

            if ($isDZSMFile -and ($currentKeepNames -notcontains $name)) {
                $candidates += $f
            }
        }

        # Alte entpackte Versionsordner erfassen, aber Archiv und aktuellen ScriptRoot nie verschieben.
        $topDirs = Get-ChildItem -Path $DZSMInstallRoot -Directory -ErrorAction SilentlyContinue
        foreach ($d in $topDirs) {
            $isArchive = $d.FullName -like "$ArchiveRoot*"
            $isCurrentRoot = $d.FullName -eq $currentScriptRootFull
            $isOldVersionDir =
                ($d.Name -like "DZSM_v*") -or
                ($d.Name -like "DZSM_*") -or
                ($d.Name -like "*BACKUP*") -or
                ($d.Name -like "*STANDARD*") -or
                ($d.Name -like "*GITHUB*")

            if ($isOldVersionDir -and (-not $isArchive) -and (-not $isCurrentRoot) -and ($d.Name -notlike "*0_3_6*")) {
                $candidates += $d
            }
        }
    } catch {
        "Fehler beim Suchen alter Versionen: $($_.Exception.Message)" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
    }

    $candidates = $candidates | Sort-Object FullName -Unique

    if (-not $candidates -or $candidates.Count -eq 0) {
        "Keine alten DZSM-Dateien/Versionen gefunden." | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
        return
    }

    "Gefundene alte DZSM-Dateien/Versionen:" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
    foreach ($item in $candidates) {
        " - $($item.FullName)" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
    }
    "" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8

    foreach ($item in $candidates) {
        try {
            $dest = Join-Path $archiveTarget $item.Name

            if (Test-PathFast $dest) {
                if ($item.PSIsContainer) {
                    $dest = Join-Path $archiveTarget ($item.Name + "_" + (Get-Date -Format "HHmmss"))
                } else {
                    $dest = Join-Path $archiveTarget ($item.BaseName + "_" + (Get-Date -Format "HHmmss") + $item.Extension)
                }
            }

            Move-Item -Path $item.FullName -Destination $dest -Force -ErrorAction Stop
            "OK archiviert: $($item.FullName) -> $dest" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
        } catch {
            "FEHLER beim Archivieren: $($item.FullName) : $($_.Exception.Message)" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
        }
    }

    "" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
    "Selbstbereinigung fertig. Alte Dateien wurden archiviert, nicht geloescht." | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8
}


function Write-DZSMStandardStructureReport {
    "DeutschZ System Manager v0.3.6 - Standardstruktur" | Out-File -FilePath $StructureFile -Encoding UTF8
    "Datum: $(Get-Date)" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "Drive-Modus: $DZSMDriveMode" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "Aktive DZSM-Pfade:" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "Base: $DZSMBaseRoot" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "Backups: $BackupsRoot" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "App: $AppRoot" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "Docs: $DocsRoot" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "DZSM_v0_1: $DZSMInstallRoot" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "Reports: $ReportsRoot" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "Scripts: $ScriptsRoot" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "Arbeitsstand: $ArbeitsstandFile" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "GitHub Export: $GitHubExportRoot" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "Safety-Dokumentation: $GitHubSafetyDocsRoot" | Out-File -FilePath $StructureFile -Append -Encoding UTF8
    "" | Out-File -FilePath $StructureFile -Append -Encoding UTF8

    foreach ($dir in @($DZSMBaseRoot, $BackupsRoot, $AppRoot, $DocsRoot, $DZSMInstallRoot, $ReportsRoot, $ScriptsRoot, $ArchiveRoot)) {
        if (Test-PathFast $dir) { "OK: $dir" | Out-File -FilePath $StructureFile -Append -Encoding UTF8 }
        else { "FEHLT: $dir" | Out-File -FilePath $StructureFile -Append -Encoding UTF8 }
    }

    $arbeitsstandText = @"
DeutschZ System Manager - Arbeitsstand aktuell
==============================================

Datum: $(Get-Date)
Aktuelle Version: v0.3.6 ARCHIVE-SHORTCUT-FIX
Startdatei: Start_DZSM_v0_3_6_ARCHIVE_SHORTCUT_FIX.bat

Aktive Struktur:
- Base: $DZSMBaseRoot
- Backups: $BackupsRoot
- App: $AppRoot
- Docs: $DocsRoot
- DZSM_v0_1: $DZSMInstallRoot
- Reports: $ReportsRoot
- Scripts: $ScriptsRoot
- GitHub Export: $GitHubExportRoot
- Safety-Dokumentation: $GitHubSafetyDocsRoot

Projekt-Regeln:
- Sauberer Projektstand: P:\GitHub_DeutschZModZ\DeutschZModZ
- P:\Root: DayZ Tools WorkDrive/Vanilla-Arbeitsbereich + Legacy/Mischbereich
- ReadyMods: Build-/PBO-Ausgabe, nicht GitHub-Quelle
- P:\ niemals Backup-Ziel
- Keine automatische Loeschung/Verschiebung von DayZ-Tools-/Vanilla-Daten
- SAFE AUTO BACKUP nutzt kein /MIR und kein /PURGE

Letzter Lauf:
- PC: $env:COMPUTERNAME
- Benutzer: $env:USERNAME
- Drive-Modus: $DZSMDriveMode
"@
    $arbeitsstandText | Out-File -FilePath $ArbeitsstandFile -Encoding UTF8
}

function Write-DZSMPDriveWorkDriveNotes {
    "DeutschZ System Manager v0.3.6 - P-Root / DayZ Tools WorkDrive Notes" | Out-File -FilePath $WorkDriveNotesFile -Encoding UTF8
    "Datum: $(Get-Date)" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    "" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8

    "Entscheidung ab v0.3.6:" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    "- P:\Root ist DayZ Tools WorkDrive / Vanilla-Arbeitsbereich / Legacy-Mischbereich." | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    "- P:\Root ist NICHT der saubere DeutschZ-GitHub-Projektstand." | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    "- P:\Root wird NICHT breit als Backup-Quelle genutzt." | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    "- P:\Root wird NICHT nach GitHub exportiert." | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    "- DayZ-Tools-/Vanilla-Ordner werden NICHT geloescht oder verschoben." | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    "- Sauberer Projektstand ist: P:\GitHub_DeutschZModZ\DeutschZModZ" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    "- ReadyMods ist Build-/PBO-Ausgabe, nicht GitHub-Quelle." | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    "" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8

    if (-not (Test-PathFast "P:\")) {
        "P:\ ist nicht aktiv. Keine WorkDrive-Notizen möglich." | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
        return
    }

    $dayzToolsVanillaItems = @("bin","Core","DZ","graphics","gui","languagecore","scripts","system","worlds_chernarusplus_data.txt","bin.txt","core.txt","graphics.txt","gui.txt","languagecore.txt","scripts.txt","system.txt")
    "DayZ Tools / Vanilla WorkDrive Elemente:" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    foreach ($item in $dayzToolsVanillaItems) {
        $p = Join-Path "P:\" $item
        if (Test-PathFast $p) { "OK/BEHALTEN: $p" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8 }
        else { "FEHLT/OPTIONAL: $p" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8 }
    }

    "" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    "Bekannte Projekt-/Ausgabeordner:" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    foreach ($p in @("P:\GitHub_DeutschZModZ", "P:\GitHub_DeutschZModZ\DeutschZModZ", "P:\ReadyMods", "P:\GitHub_DeutschZServerConfig")) {
        if (Test-PathFast $p) { "OK: $p" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8 }
        else { "FEHLT/OPTIONAL: $p" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8 }
    }

    "" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    "Legacy-/Risiko-Hinweise Top-Level, nur dokumentieren, nicht loeschen:" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    $knownLegacyNames = @("LBmaster","LBAdvancedGroups","LBAdminTool","SFKOTH","BasicMap","VPPAdmin","AdvancedGroups","MarkerBridge","MarkerBackend","ExpansionEventAI","SurvivorM_Mirek","- Kopie","ModFikes")
    try {
        $items = Get-ChildItem -Path "P:\" -Force -ErrorAction SilentlyContinue
        $foundAny = $false
        foreach ($risk in $knownLegacyNames) {
            $matches = $items | Where-Object { $_.Name -like "*$risk*" } | Select-Object -First 50
            foreach ($m in $matches) {
                $foundAny = $true
                "LEGACY-HINWEIS: $($m.FullName)" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
            }
        }
        if (-not $foundAny) { "Keine bekannten Legacy-Hinweise im Top-Level gefunden." | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8 }
    } catch {
        "Fehler beim kurzen P:\ Root Check: $($_.Exception.Message)" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    }

    "" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
    "Wichtig: Diese Treffer sind kein automatischer Loeschauftrag." | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8
}

function Invoke-DZSMAutoBackup {
    "DeutschZ System Manager v0.3.6 - SAFE AUTO BACKUP" | Out-File -FilePath $AutoBackupLogFile -Encoding UTF8
    "Datum: $(Get-Date)" | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8
    "BackupRoot: $BackupsRoot" | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8
    "Regel: Es wird nichts geloescht. Es wird NICHT gespiegelt. Kein /MIR, kein /PURGE." | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8
    "P:\Root wird nicht pauschal gesichert." | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8
    "Sauberer Projektstand fuer Backup: $DeutschZRepoRoot" | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8
    "" | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8

    New-Item -ItemType Directory -Path $BackupsRoot -Force | Out-Null
    $ComputerBackupRoot = Join-Path $BackupsRoot $env:COMPUTERNAME
    New-Item -ItemType Directory -Path $ComputerBackupRoot -Force | Out-Null

    $backupJobs = @(
        [PSCustomObject]@{ Name="Desktop"; Source="$env:USERPROFILE\Desktop"; Destination=(Join-Path $ComputerBackupRoot "Desktop") },
        [PSCustomObject]@{ Name="Codex"; Source="$env:USERPROFILE\Documents\Codex"; Destination=(Join-Path $ComputerBackupRoot "Codex") },
        [PSCustomObject]@{ Name="DeutschZModZ_GitHub_Root"; Source=$DeutschZRepoRoot; Destination=(Join-Path $ComputerBackupRoot "DeutschZModZ_GitHub_Root") },
        [PSCustomObject]@{ Name="DZSM_Reports"; Source=$ReportsRoot; Destination=(Join-Path $ComputerBackupRoot "DZSM_Reports") }
    )

    $manualRoot = Join-Path $ComputerBackupRoot "_MANUELL_PRUEFEN"
    New-Item -ItemType Directory -Path $manualRoot -Force | Out-Null
    @"
Diese Ordner bitte spaeter manuell pruefen:
- $env:USERPROFILE\Downloads
- $env:USERPROFILE\Pictures
- $env:USERPROFILE\Videos
- $env:USERPROFILE\Documents
- P:\Root Legacy-/DayZ-Tools-Dateien`r`n- LM Studio/.lmstudio Modelle nur manuell pruefen, nicht automatisch sichern
Hinweis: P:\Root wird nicht pauschal kopiert, weil es DayZ Tools WorkDrive/Vanilla-Daten und Altlasten enthaelt.
"@ | Out-File -FilePath (Join-Path $manualRoot "MANUELL_PRUEFEN.txt") -Encoding UTF8

    foreach ($job in $backupJobs) {
        "" | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8
        "------------------------------------------------------------" | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8
        "Backup Job: $($job.Name)" | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8
        "Quelle: $($job.Source)" | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8
        "Ziel: $($job.Destination)" | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8

        if (-not (Test-PathFast $job.Source)) {
            "SKIP: Quelle existiert nicht." | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8
            continue
        }
        if ($job.Destination -like "P:\*") {
            "BLOCKIERT: Ziel liegt auf P:\. P:\ darf niemals Backup-Ziel sein." | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8
            continue
        }

        New-Item -ItemType Directory -Path $job.Destination -Force | Out-Null
        $robocopyLog = Join-Path $ReportsRoot ("17_ROBOCOPY_" + $job.Name + ".log")

        $args = @(
            "`"$($job.Source)`"",
            "`"$($job.Destination)`"",
            "/E",
            "/XO",
            "/R:1",
            "/W:1",
            "/MT:4",
            "/COPY:DAT",
            "/DCOPY:DAT",
            "/XJ",
            "/NP",
            "/TEE",
            "/XD",
            "`"$ArchiveRoot`"",
            "`"$BackupsRoot`"",
            "`"$GitHubExportRoot`"",
            "/XF",
            "*.tmp",
            "*.bak",
            "/LOG+:`"$robocopyLog`""
        )

        try {
            $proc = Start-Process -FilePath "robocopy.exe" -ArgumentList $args -Wait -PassThru -NoNewWindow
            "Robocopy ExitCode: $($proc.ExitCode)" | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8
            if ($proc.ExitCode -le 7) { "OK/INFO: Robocopy Code <= 7." | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8 }
            else { "WARNUNG: Robocopy Fehlercode > 7." | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8 }
        } catch {
            "FEHLER: Robocopy konnte nicht gestartet werden: $($_.Exception.Message)" | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8
        }
    }
}

function Invoke-DZSMGitHubExport {
    "DeutschZ System Manager v0.3.6 - GitHub Export" | Out-File -FilePath $GitHubExportLogFile -Encoding UTF8
    "Datum: $(Get-Date)" | Out-File -FilePath $GitHubExportLogFile -Append -Encoding UTF8
    "Ziel: $GitHubExportRoot" | Out-File -FilePath $GitHubExportLogFile -Append -Encoding UTF8
    "Regel: Whitelist-basiert. Keine Backups, keine Reports, keine P:\Root-Daten." | Out-File -FilePath $GitHubExportLogFile -Append -Encoding UTF8
    "" | Out-File -FilePath $GitHubExportLogFile -Append -Encoding UTF8

    if (-not (Test-PathFast "P:\")) {
        "SKIP: P:\ nicht aktiv." | Out-File -FilePath $GitHubExportLogFile -Append -Encoding UTF8
        return
    }
    if (-not (Test-PathFast $DeutschZRepoRoot)) {
        "SKIP: DeutschZRepoRoot fehlt: $DeutschZRepoRoot" | Out-File -FilePath $GitHubExportLogFile -Append -Encoding UTF8
        return
    }

    New-Item -ItemType Directory -Path $GitHubExportRoot -Force | Out-Null

@"
# DeutschZ System Manager - GitHub Export

# Keine privaten/temporären Daten ins Repo
backups/
reports/
_archive_old_versions/
*.log
*.tmp
*.bak
*.zip

Thumbs.db
Desktop.ini
"@ | Out-File -FilePath (Join-Path $GitHubExportRoot ".gitignore") -Encoding UTF8

@"
# DeutschZ System Manager Tool

Automatischer Export des lokalen DeutschZ System Managers.

Sauberer Projektstand:
$DeutschZRepoRoot

P:\Root ist DayZ Tools WorkDrive/Vanilla-Arbeitsbereich und Legacy-Mischbereich.
Backups und Reports werden nicht blind exportiert.
"@ | Out-File -FilePath (Join-Path $GitHubExportRoot "README.md") -Encoding UTF8

    $jobs = @(
        [PSCustomObject]@{ Name="app"; Source=$AppRoot; Destination=(Join-Path $GitHubExportRoot "app") },
        [PSCustomObject]@{ Name="docs"; Source=$DocsRoot; Destination=(Join-Path $GitHubExportRoot "docs") },
        [PSCustomObject]@{ Name="scripts"; Source=$ScriptsRoot; Destination=(Join-Path $GitHubExportRoot "scripts") },
        [PSCustomObject]@{ Name="DZSM_v0_1"; Source=$DZSMInstallRoot; Destination=(Join-Path $GitHubExportRoot "DZSM_v0_1") }
    )

    foreach ($job in $jobs) {
        if (-not (Test-PathFast $job.Source)) {
            "SKIP: $($job.Name) Quelle fehlt: $($job.Source)" | Out-File -FilePath $GitHubExportLogFile -Append -Encoding UTF8
            continue
        }

        New-Item -ItemType Directory -Path $job.Destination -Force | Out-Null
        $robocopyLog = Join-Path $ReportsRoot ("20_GITHUB_EXPORT_ROBOCOPY_" + $job.Name + ".log")
        $args = @(
            "`"$($job.Source)`"",
            "`"$($job.Destination)`"",
            "/E",
            "/XO",
            "/R:1",
            "/W:1",
            "/MT:4",
            "/COPY:DAT",
            "/DCOPY:DAT",
            "/XJ",
            "/NP",
            "/TEE",
            "/XD",
            "`"$ArchiveRoot`"",
            "`"$BackupsRoot`"",
            "`"$ReportsRoot`"",
            "`"$GitHubExportRoot`"",
            "/XF",
            "*.log",
            "*.tmp",
            "*.bak",
            "*.zip",
            "/LOG+:`"$robocopyLog`""
        )

        try {
            $proc = Start-Process -FilePath "robocopy.exe" -ArgumentList $args -Wait -PassThru -NoNewWindow
            "Job $($job.Name) ExitCode: $($proc.ExitCode)" | Out-File -FilePath $GitHubExportLogFile -Append -Encoding UTF8
        } catch {
            "FEHLER bei GitHub Export Job $($job.Name): $($_.Exception.Message)" | Out-File -FilePath $GitHubExportLogFile -Append -Encoding UTF8
        }
    }

    if (Test-PathFast $ArbeitsstandFile) {
        Copy-Item -Path $ArbeitsstandFile -Destination (Join-Path $GitHubExportRoot "Arbeitsstand aktuell.txt") -Force -ErrorAction SilentlyContinue
    }
}

function Write-DZSMGitHubSafetyDocuments {
    "DeutschZ System Manager v0.3.6 - GitHub Safety Documentation" | Out-File -FilePath $SafetyDocsLogFile -Encoding UTF8
    "Datum: $(Get-Date)" | Out-File -FilePath $SafetyDocsLogFile -Append -Encoding UTF8

    if (-not (Test-PathFast $DeutschZRepoRoot)) {
        "SKIP: RepoRoot nicht gefunden: $DeutschZRepoRoot" | Out-File -FilePath $SafetyDocsLogFile -Append -Encoding UTF8
        return
    }

    New-Item -ItemType Directory -Path $GitHubSafetyDocsRoot -Force | Out-Null

    $readme = @"
# DeutschZ System Manager Tool

Der DeutschZ System Manager ist ein lokales Windows-Hilfstool fuer Analyse, Strukturpruefung, Safe-Backup und GitHub-Export.

## Wichtige Einordnung

- Sauberer Projektstand: P:\GitHub_DeutschZModZ\DeutschZModZ
- P:\Root: DayZ Tools WorkDrive/Vanilla-Arbeitsbereich und Legacy-Mischbereich
- ReadyMods: Build-/PBO-Ausgabe
- P:\Root wird nicht automatisch geloescht, verschoben, gesichert oder exportiert.

## Grundregeln

- keine Formatierung
- kein Overclocking
- kein PBO-Dekompilieren
- kein /MIR
- kein /PURGE
- keine privaten Reports/Backups blind in GitHub
"@

    $disclaimer = @"
# Haftungs- und Nutzungshinweis

Nutzung auf eigene Verantwortung.

Keine Gewaehr fuer Datenverlust, falsche Bedienung, falsche Pfade, unvollstaendige Backups oder Fehlkonfigurationen.

Dieses Dokument ist keine Rechtsberatung. Es ist technische Nutzungs- und Sicherheitsdokumentation.

Vor groesseren Aenderungen muss ein geprueftes Backup vorhanden sein.
"@

    $safety = @"
# Sicherheitsregeln

## P:\ Regel

P:\ ist virtuell und darf niemals Backup-Ziel sein.

P:\Root enthaelt DayZ Tools WorkDrive/Vanilla-Daten und Legacy-Dateien.
Diese Daten duerfen nicht automatisch geloescht oder verschoben werden.

## GitHub-Regel

Nach GitHub duerfen nicht blind:
- backups
- reports
- logs
- private Pfade
- Secrets
- fremde PBOs
- fremde Mod-Inhalte

## Robocopy-Regel

Erlaubt:
- kopieren
- ergaenzen
- aktualisieren

Nicht erlaubt:
- /MIR
- /PURGE
- blindes Loeschen
"@

    $usage = @"
# Bedienungsanleitung

Startdatei:

Start_DZSM_v0_3_6_ARCHIVE_SHORTCUT_FIX.bat

Ablauf:
1. Standardstruktur erstellen/pruefen
2. P:\ pruefen
3. DayZ Tools nur starten, wenn P:\ fehlt
4. P:\Root als WorkDrive/Legacy dokumentieren
5. Safe Auto Backup ausfuehren
6. GitHub-Export erstellen
7. Safety-Dokumente erzeugen
8. Reports schreiben
"@

    $privacy = @"
# Datenschutz- und Report-Hinweise

Reports koennen lokale Pfade, PC-Name, Benutzername, Laufwerke, Prozesse, Netzwerkdaten und Projektpfade enthalten.

Reports nicht ungeprueft veroeffentlichen.
"@

    $changelog = @"
# DeutschZ System Manager Tool - Changelog

## v0.3.6 ARCHIVE-SHORTCUT-FIX

- P:\Root wird als DayZ Tools WorkDrive/Vanilla-Arbeitsbereich und Legacy-Mischbereich behandelt
- sauberer Projektstand: P:\GitHub_DeutschZModZ\DeutschZModZ
- Safe Backup sichert nicht mehr pauschal den kompletten P-Drive-Root
- ReadyMods ist Build-/PBO-Ausgabe
- erstellt 22_P_ROOT_WORKDRIVE_NOTES.txt

## v0.3.3 DOCUMENTATION-SAFETY

- erstellt Safety-/Nutzungsdokumente

## v0.3.2 GITHUB-EXPORT

- erstellt GitHub-Export-Kopie

## v0.3.1 STANDARD-STRUCTURE

- nutzt feste DZSM-Ordnerstruktur
"@

    $files = @(
        [PSCustomObject]@{ Path=(Join-Path $GitHubSafetyDocsRoot "README_DZSM.md"); Content=$readme },
        [PSCustomObject]@{ Path=(Join-Path $GitHubSafetyDocsRoot "DISCLAIMER_NUTZUNG_AUF_EIGENE_VERANTWORTUNG.md"); Content=$disclaimer },
        [PSCustomObject]@{ Path=(Join-Path $GitHubSafetyDocsRoot "SAFETY_RULES.md"); Content=$safety },
        [PSCustomObject]@{ Path=(Join-Path $GitHubSafetyDocsRoot "USAGE_GUIDE.md"); Content=$usage },
        [PSCustomObject]@{ Path=(Join-Path $GitHubSafetyDocsRoot "PRIVACY_AND_REPORTS.md"); Content=$privacy },
        [PSCustomObject]@{ Path=(Join-Path $GitHubSafetyDocsRoot "CHANGELOG_DZSM.md"); Content=$changelog }
    )

    foreach ($f in $files) {
        try {
            $f.Content | Out-File -FilePath $f.Path -Encoding UTF8
            "OK erstellt/aktualisiert: $($f.Path)" | Out-File -FilePath $SafetyDocsLogFile -Append -Encoding UTF8
        } catch {
            "FEHLER bei Datei $($f.Path): $($_.Exception.Message)" | Out-File -FilePath $SafetyDocsLogFile -Append -Encoding UTF8
        }
    }

    try {
        if (Test-PathFast $GitHubExportRoot) {
            $exportDocs = Join-Path $GitHubExportRoot "docs\safety"
            New-Item -ItemType Directory -Path $exportDocs -Force | Out-Null
            foreach ($f in $files) {
                Copy-Item -Path $f.Path -Destination (Join-Path $exportDocs (Split-Path $f.Path -Leaf)) -Force -ErrorAction SilentlyContinue
            }
        }
    } catch {}
}


function Write-DZSMLMStudioPolicy {
    "DeutschZ System Manager v0.3.6 - LM Studio / Modell Policy" | Out-File -FilePath $LMStudioPolicyFile -Encoding UTF8
    "Datum: $(Get-Date)" | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    "" | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    "Entscheidung ab v0.3.6:" | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    "- LM Studio ist optional/experimentell." | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    "- Lokale LM Studio Modelle werden NICHT automatisch gesichert." | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    "- Lokale LM Studio Modelle werden NICHT nach GitHub exportiert." | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    "- .lmstudio wird nicht als notwendiger Bestandteil von DZSM bewertet." | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    "- Grund: Das aktuell vorhandene Modell funktioniert noch nicht zuverlaessig." | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    "" | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    "Bekannter Problem-/Testpfad:" | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    "C:\Users\patsl\.lmstudio\models\lmstudio-community\Qwen2.5-Coder-14B-Instruct-GGUF\Qwen2.5-Coder-14B-Instruct-Q3_K_L.gguf" | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    "" | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    if (Test-PathFast "$env:USERPROFILE\.lmstudio") {
        "STATUS: .lmstudio Ordner vorhanden, wird aber bewusst NICHT gesichert." | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    } else {
        "STATUS: .lmstudio Ordner nicht vorhanden." | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
    }
    "Spaeter kann LM Studio wieder aufgenommen werden, wenn es wirklich genutzt wird und das Modell sauber laeuft." | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8
}


function Update-DZSMDesktopShortcuts {
    param(
        [string]$ShortcutLogFile
    )

    "DeutschZ System Manager v0.3.6 - Desktop-Verknuepfungen" | Out-File -FilePath $ShortcutLogFile -Encoding UTF8
    "Datum: $(Get-Date)" | Out-File -FilePath $ShortcutLogFile -Append -Encoding UTF8
    "Regel: Es werden nur alte DZSM-.lnk Verknuepfungen entfernt, keine echten Dateien." | Out-File -FilePath $ShortcutLogFile -Append -Encoding UTF8
    "" | Out-File -FilePath $ShortcutLogFile -Append -Encoding UTF8

    $desktop = [Environment]::GetFolderPath("Desktop")
    if (-not (Test-PathFast $desktop)) {
        "Desktop-Ordner nicht gefunden: $desktop" | Out-File -FilePath $ShortcutLogFile -Append -Encoding UTF8
        return
    }

    $currentBat = Join-Path $PSScriptRoot "Start_DZSM_v0_3_6_ARCHIVE_SHORTCUT_FIX.bat"
    $currentPs1 = Join-Path $PSScriptRoot "DZSM_v0_3_6_Archive_Shortcut_Fix.ps1"

    # Alte DZSM-Links entfernen, aber nur .lnk Dateien.
    try {
        $oldLinks = Get-ChildItem -Path $desktop -Filter "*.lnk" -File -ErrorAction SilentlyContinue |
            Where-Object {
                $_.Name -like "*DZSM*" -or
                $_.Name -like "*DeutschZ System Manager*" -or
                $_.Name -like "*DeutschZ_System_Manager*"
            }

        foreach ($lnk in $oldLinks) {
            try {
                Remove-Item -Path $lnk.FullName -Force -ErrorAction Stop
                "OK alte Verknuepfung entfernt: $($lnk.FullName)" | Out-File -FilePath $ShortcutLogFile -Append -Encoding UTF8
            } catch {
                "WARNUNG alte Verknuepfung konnte nicht entfernt werden: $($lnk.FullName) : $($_.Exception.Message)" | Out-File -FilePath $ShortcutLogFile -Append -Encoding UTF8
            }
        }
    } catch {
        "WARNUNG beim Suchen alter Verknuepfungen: $($_.Exception.Message)" | Out-File -FilePath $ShortcutLogFile -Append -Encoding UTF8
    }

    try {
        $shell = New-Object -ComObject WScript.Shell

        if (Test-PathFast $currentBat) {
            $batShortcut = $shell.CreateShortcut((Join-Path $desktop "DeutschZ System Manager - Start.lnk"))
            $batShortcut.TargetPath = $currentBat
            $batShortcut.WorkingDirectory = $PSScriptRoot
            $batShortcut.Description = "Startet den aktuellen DeutschZ System Manager"
            $batShortcut.IconLocation = "$env:SystemRoot\System32\WindowsPowerShell\v1.0\powershell.exe,0"
            $batShortcut.Save()
            "OK neue BAT-Verknuepfung erstellt: DeutschZ System Manager - Start.lnk -> $currentBat" | Out-File -FilePath $ShortcutLogFile -Append -Encoding UTF8
        } else {
            "WARNUNG aktuelle BAT nicht gefunden: $currentBat" | Out-File -FilePath $ShortcutLogFile -Append -Encoding UTF8
        }

        if (Test-PathFast $currentPs1) {
            $ps1Shortcut = $shell.CreateShortcut((Join-Path $desktop "DeutschZ System Manager - Script PS1.lnk"))
            $ps1Shortcut.TargetPath = "powershell.exe"
            $ps1Shortcut.Arguments = "-NoProfile -ExecutionPolicy Bypass -File `"$currentPs1`""
            $ps1Shortcut.WorkingDirectory = $PSScriptRoot
            $ps1Shortcut.Description = "Startet das aktuelle DZSM PowerShell-Script direkt"
            $ps1Shortcut.IconLocation = "$env:SystemRoot\System32\WindowsPowerShell\v1.0\powershell.exe,0"
            $ps1Shortcut.Save()
            "OK neue PS1-Verknuepfung erstellt: DeutschZ System Manager - Script PS1.lnk -> $currentPs1" | Out-File -FilePath $ShortcutLogFile -Append -Encoding UTF8
        } else {
            "WARNUNG aktuelle PS1 nicht gefunden: $currentPs1" | Out-File -FilePath $ShortcutLogFile -Append -Encoding UTF8
        }
    } catch {
        "FEHLER beim Erstellen der Desktop-Verknuepfungen: $($_.Exception.Message)" | Out-File -FilePath $ShortcutLogFile -Append -Encoding UTF8
    }
}

# ------------------------------------------------------------
# START
# ------------------------------------------------------------
"DeutschZ System Manager v0.3.6 - DayZ Tools / P-Drive Mount Log" | Out-File -FilePath $MountLogFile -Encoding UTF8

try { Invoke-DZSMSelfCleanup } catch { "SelfCleanup fehlgeschlagen: $($_.Exception.Message)" | Out-File -FilePath $SelfCleanupFile -Append -Encoding UTF8 }
try { Write-DZSMStandardStructureReport } catch { "Strukturbericht fehlgeschlagen: $($_.Exception.Message)" | Out-File -FilePath $StructureFile -Append -Encoding UTF8 }
try { Update-DZSMDesktopShortcuts -ShortcutLogFile $ShortcutLogFile } catch { "Desktop-Verknuepfungen fehlgeschlagen: $($_.Exception.Message)" | Out-File -FilePath $ShortcutLogFile -Append -Encoding UTF8 }

Try-StartDayZToolsAndMountP

try { Write-DZSMPDriveWorkDriveNotes } catch { "WorkDrive Notes fehlgeschlagen: $($_.Exception.Message)" | Out-File -FilePath $WorkDriveNotesFile -Append -Encoding UTF8 }
try { Write-DZSMLMStudioPolicy } catch { "LM Studio Policy fehlgeschlagen: $($_.Exception.Message)" | Out-File -FilePath $LMStudioPolicyFile -Append -Encoding UTF8 }
try { Invoke-DZSMAutoBackup } catch { "Safe Auto Backup fehlgeschlagen: $($_.Exception.Message)" | Out-File -FilePath $AutoBackupLogFile -Append -Encoding UTF8 }
try { Invoke-DZSMGitHubExport } catch { "GitHub Export fehlgeschlagen: $($_.Exception.Message)" | Out-File -FilePath $GitHubExportLogFile -Append -Encoding UTF8 }
try { Write-DZSMGitHubSafetyDocuments } catch { "Safety Docs fehlgeschlagen: $($_.Exception.Message)" | Out-File -FilePath $SafetyDocsLogFile -Append -Encoding UTF8 }

# ------------------------------------------------------------
# HAUPTREPORT
# ------------------------------------------------------------
"DeutschZ System Manager v0.3.6 ARCHIVE-SHORTCUT-FIX - Inventurbericht" | Out-File -FilePath $ReportFile -Encoding UTF8
"PC: $env:COMPUTERNAME" | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"Benutzer: $env:USERNAME" | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"Datum: $(Get-Date)" | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"Reportordner: $ReportsRoot" | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"DZSM-Basisordner: $DZSMBaseRoot" | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"Backupordner: $BackupsRoot" | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"Sauberer Projektstand: $DeutschZRepoRoot" | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"P-Root-Regel: P:\Root ist DayZ Tools WorkDrive/Vanilla-Arbeitsbereich + Legacy/Mischbereich." | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"ReadyMods-Regel: ReadyMods ist Build-/PBO-Ausgabe, nicht GitHub-Quelle." | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"LM-Studio-Regel: .lmstudio und lokale Modelle werden aktuell NICHT automatisch gesichert/exportiert." | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"Modus: Nur lesen / Safe Backup / GitHub Export / keine Loeschung / keine Uebertaktung" | Out-File -FilePath $ReportFile -Append -Encoding UTF8

Safe-Out "WINDOWS" {
    Get-CimInstance Win32_OperatingSystem |
        Select-Object Caption, Version, BuildNumber, OSArchitecture, WindowsDirectory, SystemDirectory, InstallDate, LastBootUpTime
}

Safe-Out "CPU" {
    Get-CimInstance Win32_Processor |
        Select-Object Name, NumberOfCores, NumberOfLogicalProcessors, MaxClockSpeed, CurrentClockSpeed, SocketDesignation
}

Safe-Out "MAINBOARD" {
    Get-CimInstance Win32_BaseBoard |
        Select-Object Manufacturer, Product, Version, SerialNumber
}

Safe-Out "BIOS" {
    Get-CimInstance Win32_BIOS |
        Select-Object Manufacturer, SMBIOSBIOSVersion, ReleaseDate
}

Safe-Out "RAM" {
    Get-CimInstance Win32_ComputerSystem | Select-Object @{n="TotalPhysicalMemoryGB";e={Convert-BytesToGB $_.TotalPhysicalMemory}}
    Get-CimInstance Win32_PhysicalMemory |
        Select-Object BankLabel, Manufacturer, @{n="CapacityGB";e={Convert-BytesToGB $_.Capacity}}, Speed, ConfiguredClockSpeed, PartNumber
}

Safe-Out "GRAFIK" {
    Get-CimInstance Win32_VideoController |
        Select-Object Name, @{n="AdapterRAM_GB";e={Convert-BytesToGB $_.AdapterRAM}}, DriverVersion, VideoModeDescription
}

$drives = Get-CimInstance Win32_LogicalDisk | Select-Object DeviceID, VolumeName, FileSystem,
    @{n="SizeGB";e={Convert-BytesToGB $_.Size}},
    @{n="FreeGB";e={Convert-BytesToGB $_.FreeSpace}},
    @{n="FreePercent";e={ if ($_.Size) {[math]::Round(($_.FreeSpace/$_.Size)*100,1)} else {""} }},
    DriveType
$drives | Export-Csv -Path $DrivesFile -NoTypeInformation -Encoding UTF8
Safe-Out "LAUFWERKE / PARTITIONEN" { $drives | Format-Table -AutoSize }

Safe-Out "PHYSISCHE DATENTRAEGER" {
    Get-CimInstance Win32_DiskDrive |
        Select-Object Model, InterfaceType, MediaType, @{n="SizeGB";e={Convert-BytesToGB $_.Size}}, Status
}

$net = Get-CimInstance Win32_NetworkAdapterConfiguration | Where-Object {$_.IPEnabled -eq $true} |
    Select-Object Description, DHCPEnabled, IPAddress, DefaultIPGateway, DNSServerSearchOrder, MACAddress
$net | Format-List | Out-String | Out-File -FilePath $NetworkFile -Encoding UTF8
Safe-Out "NETZWERK" { $net | Format-List }

"HKCU Run:" | Out-File -FilePath $StartupFile -Encoding UTF8
Get-ItemProperty "HKCU:\Software\Microsoft\Windows\CurrentVersion\Run" -ErrorAction SilentlyContinue | Out-String -Width 350 | Out-File -FilePath $StartupFile -Append -Encoding UTF8
"`r`nHKLM Run:" | Out-File -FilePath $StartupFile -Append -Encoding UTF8
Get-ItemProperty "HKLM:\Software\Microsoft\Windows\CurrentVersion\Run" -ErrorAction SilentlyContinue | Out-String -Width 350 | Out-File -FilePath $StartupFile -Append -Encoding UTF8
Safe-Out "AUTOSTART" { Get-Content $StartupFile }

Get-Process | Sort-Object WorkingSet -Descending | Select-Object -First 75 ProcessName, Id, CPU, @{n="RAM_MB";e={[math]::Round($_.WorkingSet/1MB,1)}} |
    Export-Csv -Path $ProcessesFile -NoTypeInformation -Encoding UTF8
Safe-Out "TOP 25 PROZESSE NACH RAM" {
    Import-Csv $ProcessesFile | Select-Object -First 25 | Format-Table -AutoSize
}

$programs = @()
$regPaths = @(
 "HKLM:\Software\Microsoft\Windows\CurrentVersion\Uninstall\*",
 "HKLM:\Software\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall\*",
 "HKCU:\Software\Microsoft\Windows\CurrentVersion\Uninstall\*"
)
foreach ($p in $regPaths) {
    $programs += Get-ItemProperty $p -ErrorAction SilentlyContinue |
        Where-Object {$_.DisplayName} |
        Select-Object DisplayName, DisplayVersion, Publisher, InstallLocation, InstallDate
}
$programs | Sort-Object DisplayName | Export-Csv -Path $ProgramsFile -NoTypeInformation -Encoding UTF8

# Steam / DayZ Check
"Steam / DayZ Check" | Out-File -FilePath $SteamFile -Encoding UTF8
$steamPath = Get-SteamPath
if ($steamPath) { Append-Line $SteamFile "SteamPath: $steamPath" }
$dayzToolsPath = if ($steamPath) { Find-DayZToolsPath $steamPath } else { $null }
if ($dayzToolsPath) { Append-Line $SteamFile "DayZ Tools Pfad: $dayzToolsPath" }
$workDrive = Find-WorkDriveExe $dayzToolsPath
if ($workDrive) { Append-Line $SteamFile "WorkDrive.exe: $workDrive" }
try {
    if ($steamPath) {
        $libVdf = Join-Path $steamPath "steamapps\libraryfolders.vdf"
        if (Test-PathFast $libVdf) {
            Append-Line $SteamFile "`r`nlibraryfolders.vdf gefunden: $libVdf"
            Get-Content $libVdf -ErrorAction SilentlyContinue | Out-File -FilePath $SteamFile -Append -Encoding UTF8
        }
    }
} catch {}

# P Drive Check
"P:\ Virtual/DeutschZ Check" | Out-File -FilePath $PDriveFile -Encoding UTF8
Append-Line $PDriveFile "Datum: $(Get-Date)"
Append-Line $PDriveFile "Regel: P:\ ist virtuell. P:\Root = DayZ Tools WorkDrive/Vanilla + Legacy. Sauberer Stand = $DeutschZRepoRoot"
Append-Line $PDriveFile "Test-Path P:\ = $(Test-PathFast 'P:\')"
Append-Line $PDriveFile "`r`n--- SUBST Ausgabe ---"
try { cmd.exe /c subst | Out-File -FilePath $PDriveFile -Append -Encoding UTF8 } catch {}
Append-Line $PDriveFile "`r`n--- Wichtige P:\ Pfade ---"
foreach ($p in @($DeutschZRepoRoot, "$DeutschZRepoRoot\mods", "P:\ReadyMods", $GitHubExportRoot, $GitHubSafetyDocsRoot)) {
    if (Test-PathFast $p) { Append-Line $PDriveFile "OK: $p" } else { Append-Line $PDriveFile "FEHLT/OPTIONAL: $p" }
}

# Known paths
"Bekannte Pfade Check" | Out-File -FilePath $PathsFile -Encoding UTF8
$knownPaths = @(
    $DZSMBaseRoot, $BackupsRoot, $AppRoot, $DocsRoot, $DZSMInstallRoot, $ReportsRoot, $ScriptsRoot,
    $DeutschZRepoRoot, "$DeutschZRepoRoot\mods", "P:\ReadyMods", $GitHubExportRoot, $GitHubSafetyDocsRoot,
    "F:\Programme\steamapps\common\DayZ", "$env:USERPROFILE\Documents\Codex"
)
foreach ($p in $knownPaths) {
    if (Test-PathFast $p) { Append-Line $PathsFile "OK: $p" } else { Append-Line $PathsFile "FEHLT/OPTIONAL: $p" }
}

# Backup Plan
"DeutschZ System Manager v0.3.6 - Backup Plan" | Out-File -FilePath $BackupPlanFile -Encoding UTF8
Append-Line $BackupPlanFile "Datum: $(Get-Date)"
Append-Line $BackupPlanFile "Backup-Ziel: $BackupsRoot"
Append-Line $BackupPlanFile "Sauberer Projektstand: $DeutschZRepoRoot"
Append-Line $BackupPlanFile "P:\Root wird NICHT pauschal gesichert."
Append-Line $BackupPlanFile "P:\Root bleibt DayZ Tools WorkDrive/Vanilla + Legacy."
Append-Line $BackupPlanFile "ReadyMods bleibt Build-/PBO-Ausgabe."
Append-Line $BackupPlanFile "Kein /MIR, kein /PURGE, keine Loeschung."

# DeutschZ Structure Check
"DeutschZ System Manager v0.3.6 - DeutschZ Structure Check" | Out-File -FilePath $DeutschZFile -Encoding UTF8
Append-Line $DeutschZFile "Sauberer Projektstand: $DeutschZRepoRoot"
Append-Line $DeutschZFile "P:\Root wird nur als WorkDrive/Legacy dokumentiert."
$dzModsRoot = Join-Path $DeutschZRepoRoot "mods"
foreach ($p in @($DeutschZRepoRoot, $dzModsRoot, "$DeutschZRepoRoot\tools", "$DeutschZRepoRoot\tools\build_wrapper", "$DeutschZRepoRoot\DeutschZ_SystemManager_Tool", "$DeutschZRepoRoot\DeutschZ_SystemManager_Tool_Dokumentation")) {
    if (Test-PathFast $p) { Append-Line $DeutschZFile "OK: $p" } else { Append-Line $DeutschZFile "FEHLT/OPTIONAL: $p" }
}
$modOrder = @("DeutschZ_Core","DeutschZ_ExpansionBridge","DeutschZ_KotHZ","DeutschZ_ConvoyZ","DeutschZ_GroundZero","DeutschZ_CourierZ","DeutschZ_OperationDeutschZ")
foreach ($m in $modOrder) {
    $mp = Join-Path $dzModsRoot $m
    if (Test-PathFast $mp) { Append-Line $DeutschZFile "OK Mod: $m" } else { Append-Line $DeutschZFile "FEHLT Mod: $m" }
}

# Cleanup Risk FAST - only clean project root
"DeutschZ System Manager v0.3.6 - Cleanup Risk Check FAST" | Out-File -FilePath $CleanupFile -Encoding UTF8
Append-Line $CleanupFile "Regel: Kein breiter P:\Root-Scan. P:\Root wird in 22_P_ROOT_WORKDRIVE_NOTES.txt dokumentiert."
Append-Line $CleanupFile "Pruefung nur im sauberen Projektstand: $DeutschZRepoRoot"
$riskNames = @("LBmaster","LBAdvancedGroups","LBAdminTool","SFKOTH","BasicMap","VPPAdmin","AdvancedGroups","MarkerBridge","MarkerBackend","ExpansionEventAI","SurvivorM_Mirek")
foreach ($root in @($DeutschZRepoRoot, "$DeutschZRepoRoot\mods")) {
    Append-Line $CleanupFile "`r`n--- FAST Root: $root ---"
    if (-not (Test-PathFast $root)) { Append-Line $CleanupFile "FEHLT/NICHT AKTIV"; continue }
    try {
        $items = Get-ChildItem -Path $root -Force -ErrorAction SilentlyContinue
        foreach ($risk in $riskNames) {
            $matches = $items | Where-Object { $_.Name -like "*$risk*" } | Select-Object -First 20
            foreach ($match in $matches) { Append-Line $CleanupFile "RISIKO-HINWEIS: $($match.FullName)" }
        }
    } catch { Append-Line $CleanupFile "Fehler: $($_.Exception.Message)" }
}

# Migration check
"DeutschZ System Manager v0.3.6 - Windows SSD Migration Check" | Out-File -FilePath $MigrationFile -Encoding UTF8
Append-Line $MigrationFile "WindowsDirectory: $env:windir"
Append-Line $MigrationFile "Vor Windows-Neuinstallation zuerst Backup unter $BackupsRoot pruefen."
Append-Line $MigrationFile "DayZ nicht verschieben, wenn es bereits auf SSD/F: liegt."
Append-Line $MigrationFile "Ohne USB-Stick und geprueftes Backup keine Formatierung."
Append-Line $MigrationFile "P:\Root nicht als sauberes Projekt sichern; sauberer Stand ist $DeutschZRepoRoot."

# Folder quick check
$folderRows = New-Object System.Collections.Generic.List[Object]
foreach ($path in @($DZSMBaseRoot, $BackupsRoot, $ReportsRoot, $DeutschZRepoRoot, "$DeutschZRepoRoot\mods", "P:\ReadyMods", "F:\Programme\steamapps\common\DayZ", "$env:USERPROFILE\Documents\Codex")) {
    $folderRows.Add((Get-FolderQuickInfo $path)) | Out-Null
}
$folderRows | Export-Csv -Path $FolderCheckFile -NoTypeInformation -Encoding UTF8

# JSON Summary
try {
    $summary = [PSCustomObject]@{
        Tool = "DeutschZ System Manager"
        Version = "0.3.4 GITHUB-ROOT-ONLY-WORKDRIVE-AWARE"
        ComputerName = $env:COMPUTERNAME
        UserName = $env:USERNAME
        Date = (Get-Date).ToString("s")
        ReportsRoot = $ReportsRoot
        BackupsRoot = $BackupsRoot
        CleanProjectRoot = $DeutschZRepoRoot
        PDriveRootPolicy = "DayZ Tools WorkDrive/Vanilla workspace plus legacy/mixed files; do not delete/move/export/broad-backup automatically"
        ReadyModsPolicy = "Build/PBO output only, not GitHub source"
        GitHubExportRoot = $GitHubExportRoot
        SafetyDocsRoot = $GitHubSafetyDocsRoot
        DestructiveActions = $false
        DesktopShortcutPolicy = "Create current BAT/PS1 desktop shortcuts and remove old DZSM .lnk shortcuts only"
        ArchivePolicy = "Archive old DZSM files from install root, never delete"
    }
    $summary | ConvertTo-Json -Depth 5 | Out-File -FilePath $SummaryJsonFile -Encoding UTF8
} catch {}

# Next steps
@"
DeutschZ System Manager - Naechste Schritte
==========================================

Reportordner:
$ReportsRoot

Wichtig:
- P:\Root ist DayZ Tools WorkDrive/Vanilla + Legacy.
- P:\Root nicht loeschen, nicht verschieben, nicht pauschal sichern/exportieren.
- Sauberer Projektstand:
  $DeutschZRepoRoot
- ReadyMods ist Build-/PBO-Ausgabe.
- Backups liegen unter:
  $BackupsRoot

Bitte bei Bedarf hochladen:
1. 00_ZUSAMMENFASSUNG.txt
2. 17_SAFE_AUTO_BACKUP_LOG.txt
3. 19_GITHUB_EXPORT_LOG.txt
4. 21_GITHUB_SAFETY_DOCS_LOG.txt
5. 22_P_ROOT_WORKDRIVE_NOTES.txt`r`n6. 23_LMSTUDIO_MODEL_POLICY.txt`r`n7. 24_DESKTOP_SHORTCUTS_LOG.txt
6. 11_DEUTSCHZ_STRUCTURE_CHECK.txt
"@ | Out-File -FilePath $NextFile -Encoding UTF8

Write-Section "ERGEBNIS"
"v0.3.6 fertig." | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"P:\Root wurde als DayZ Tools WorkDrive/Vanilla + Legacy eingeordnet." | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"Sauberer Projektstand: $DeutschZRepoRoot" | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"Backup: $BackupsRoot" | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"GitHub Export: $GitHubExportRoot" | Out-File -FilePath $ReportFile -Append -Encoding UTF8
"Safety Docs: $GitHubSafetyDocsRoot" | Out-File -FilePath $ReportFile -Append -Encoding UTF8

# EXAKTE ABSCHLUSSANZEIGE
Write-Host @"
Analyse fertiggestellt........
Beenden des Programms eingeleitet.

          ┌─┐
          │▒│
          │▒│
          │▒│
          │▒│
          │▒│
   ┌──────┘▒└──────┐
   │▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│
┌──┘▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒└──┐
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│
└──┐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒┌──┘
   │▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│
   └┐▒▒▒▒▒▒▒▒▒▒▒▒┌┘
    └┐▒▒▒▒▒▒▒▒▒┌┘
     └┐▒▒▒▒▒▒┌┘
      └─────┘

          FUCK OFFFFFFFFFFFFFFFFFFFF
"@
Start-Sleep -Seconds 7
exit 0
