
# DeutschZ System Manager v0.4.6 DESKTOP-NAMES-CLEANUP
$ErrorActionPreference = "Continue"

if (Test-Path "D:\") {
    $DZSMBaseRoot = "D:\DeutschZ_System_Manager"
    $DZSMDriveMode = "D_AVAILABLE_STANDARD_STRUCTURE"
} else {
    $DZSMBaseRoot = "C:\DeutschZ_System_Manager"
    $DZSMDriveMode = "C_FALLBACK_STANDARD_STRUCTURE_NO_D_DRIVE"
}

$BackupsRoot = Join-Path $DZSMBaseRoot "backups"
$AppRoot = Join-Path $DZSMBaseRoot "app"
$DocsRoot = Join-Path $DZSMBaseRoot "docs"
$DZSMInstallRoot = Join-Path $DZSMBaseRoot "DZSM_v0_1"
$ReportsRoot = Join-Path $DZSMBaseRoot "reports"
$ScriptsRoot = Join-Path $DZSMBaseRoot "scripts"
$BugReportRoot = Join-Path $DZSMBaseRoot "bugreports"
$MemoryRoot = Join-Path $DZSMBaseRoot "memory"
$UploadPackageRoot = Join-Path $ReportsRoot "_UPLOAD_FUER_CHATGPT"
$ArchiveRoot = Join-Path $DZSMInstallRoot "_archive_old_versions"
$ArbeitsstandFile = Join-Path $DZSMBaseRoot "Arbeitsstand aktuell.txt"
$DeutschZRepoRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ"
$GitHubExportRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ\DeutschZ_SystemManager_Tool"
$GitHubSafetyDocsRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ\DeutschZ_SystemManager_Tool_Dokumentation"
$BuildWrapperRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ\tools\build_wrapper"
$GitCommitHelperRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ\tools\git_commit_helper"
$CurrentVersionToken = "0_4_6"

foreach ($dir in @($DZSMBaseRoot,$BackupsRoot,$AppRoot,$DocsRoot,$DZSMInstallRoot,$ReportsRoot,$ScriptsRoot,$BugReportRoot,$MemoryRoot,$UploadPackageRoot,$ArchiveRoot)) {
    New-Item -ItemType Directory -Path $dir -Force | Out-Null
}

$ReportFile = Join-Path $ReportsRoot "00_ZUSAMMENFASSUNG.txt"
$DeutschZFile = Join-Path $ReportsRoot "11_DEUTSCHZ_STRUCTURE_CHECK.txt"
$SelfCleanupFile = Join-Path $ReportsRoot "16_DZSM_SELF_CLEANUP.txt"
$BackupLogFile = Join-Path $ReportsRoot "17_SAFE_AUTO_BACKUP_LOG.txt"
$StructureFile = Join-Path $ReportsRoot "18_DZSM_STANDARD_STRUCTURE.txt"
$GitHubExportLogFile = Join-Path $ReportsRoot "19_GITHUB_EXPORT_LOG.txt"
$SafetyDocsLogFile = Join-Path $ReportsRoot "21_GITHUB_SAFETY_DOCS_LOG.txt"
$WorkDriveNotesFile = Join-Path $ReportsRoot "22_P_ROOT_WORKDRIVE_NOTES.txt"
$LMStudioPolicyFile = Join-Path $ReportsRoot "23_LMSTUDIO_MODEL_POLICY.txt"
$ShortcutLogFile = Join-Path $ReportsRoot "24_DESKTOP_SHORTCUTS_LOG.txt"
$BugReportLogFile = Join-Path $ReportsRoot "25_BUGREPORT_WORKSPACE_LOG.txt"
$UploadPackageLogFile = Join-Path $ReportsRoot "26_UPLOAD_PACKAGE_LOG.txt"
$BuildWrapperLogFile = Join-Path $ReportsRoot "27_BUILD_WRAPPER_LOG.txt"
$MemoryPackageLogFile = Join-Path $ReportsRoot "28_MEMORY_PACKAGE_LOG.txt"
$GitCommitHelperLogFile = Join-Path $ReportsRoot "29_GIT_COMMIT_HELPER_LOG.txt","29_GIT_COMMIT_HELPER_LOG.txt"
$GitCommitHelperLogFile = Join-Path $ReportsRoot "29_GIT_COMMIT_HELPER_LOG.txt`r`n- 30_GIT_MERGE_STATUS.txt`r`n- 31_GIT_CONFLICT_FILES.txt`r`n- 32_GIT_CONFLICT_MARKERS_CONTEXT.txt`r`n- 33_GIT_MERGE_DECISION_GUIDE.md"
$GitMergeStatusFile = Join-Path $ReportsRoot "30_GIT_MERGE_STATUS.txt"
$GitConflictFilesFile = Join-Path $ReportsRoot "31_GIT_CONFLICT_FILES.txt"
$GitConflictMarkersFile = Join-Path $ReportsRoot "32_GIT_CONFLICT_MARKERS_CONTEXT.txt"
$GitMergeGuideFile = Join-Path $ReportsRoot "33_GIT_MERGE_DECISION_GUIDE.md"
$NextFile = Join-Path $ReportsRoot "99_NAECHSTE_SCHRITTE.txt"

function Test-PathFast($p) { try { Test-Path $p } catch { $false } }
function Append-Line($f,$t) { $t | Out-File -FilePath $f -Append -Encoding UTF8 }
function GB($b) { if ($null -eq $b -or $b -eq "") { "" } else { [math]::Round(([double]$b/1GB),2) } }

# Clean current report files only
foreach ($f in @($ReportFile,$DeutschZFile,$SelfCleanupFile,$BackupLogFile,$StructureFile,$GitHubExportLogFile,$SafetyDocsLogFile,$WorkDriveNotesFile,$LMStudioPolicyFile,$ShortcutLogFile,$BugReportLogFile,$UploadPackageLogFile,$BuildWrapperLogFile,$MemoryPackageLogFile,$GitCommitHelperLogFile,$GitMergeStatusFile,$GitConflictFilesFile,$GitConflictMarkersFile,$GitMergeGuideFile,$NextFile)) {
    if (Test-PathFast $f) { Remove-Item $f -Force -ErrorAction SilentlyContinue }
}

function Invoke-SelfCleanup {
    "DeutschZ System Manager v0.4.6 - Selbstbereinigung" | Out-File $SelfCleanupFile -Encoding UTF8
    Append-Line $SelfCleanupFile "InstallRoot: $DZSMInstallRoot"
    Append-Line $SelfCleanupFile "Archivziel Root: $ArchiveRoot"
    $archiveTarget = Join-Path $ArchiveRoot (Get-Date -Format "yyyy-MM-dd_HH-mm-ss")
    New-Item -ItemType Directory -Path $archiveTarget -Force | Out-Null
    $keep = @("Start_DZSM_v0_4_6_DESKTOP_NAMES_CLEANUP.bat","DZSM_v0_4_6_Desktop_Names_Cleanup.ps1","README_START.txt","DZSM_Config.json")
    $candidates = @()
    Get-ChildItem -Path $DZSMInstallRoot -File -ErrorAction SilentlyContinue | ForEach-Object {
        if ((($_.Name -like "Start_DZSM_*.bat") -or ($_.Name -like "DZSM_*.ps1") -or ($_.Name -like "DZSM_v*.zip") -or ($_.Name -like "README_START*.txt") -or ($_.Name -like "DZSM_Config*.json")) -and ($keep -notcontains $_.Name)) {
            $candidates += $_
        }
    }
    foreach ($item in $candidates) {
        try {
            Move-Item $item.FullName (Join-Path $archiveTarget $item.Name) -Force -ErrorAction Stop
            Append-Line $SelfCleanupFile "OK archiviert: $($item.FullName)"
        } catch { Append-Line $SelfCleanupFile "FEHLER: $($item.FullName) $($_.Exception.Message)" }
    }
    if ($candidates.Count -eq 0) { Append-Line $SelfCleanupFile "Keine alten DZSM-Dateien gefunden." }
}

function Write-Structure {
    "DeutschZ System Manager v0.4.6 - Standardstruktur" | Out-File $StructureFile -Encoding UTF8
    foreach ($line in @(
        "Drive-Modus: $DZSMDriveMode",
        "Base: $DZSMBaseRoot",
        "Backups: $BackupsRoot",
        "App: $AppRoot",
        "Docs: $DocsRoot",
        "DZSM_v0_1: $DZSMInstallRoot",
        "Reports: $ReportsRoot",
        "Scripts: $ScriptsRoot",
        "BugReports: $BugReportRoot",
        "Memory: $MemoryRoot",
        "UploadPackage: $UploadPackageRoot",
        "BuildWrapper: $BuildWrapperRoot",
        "GitCommitHelper: $GitCommitHelperRoot"
    )) { Append-Line $StructureFile $line }
    @"
DeutschZ System Manager - Arbeitsstand aktuell
==============================================
Datum: $(Get-Date)
Aktuelle Version: v0.4.6 DESKTOP-NAMES-CLEANUP
Startdatei: Start_DZSM_v0_4_6_DESKTOP_NAMES_CLEANUP.bat
Uploadpaket: $UploadPackageRoot
Memory: $MemoryRoot
BuildWrapper: $BuildWrapperRoot
GitCommitHelper: $GitCommitHelperRoot
"@ | Out-File $ArbeitsstandFile -Encoding UTF8
}

function Write-WorkDriveNotes {
    "DeutschZ System Manager v0.4.6 - P-Root / WorkDrive Notes" | Out-File $WorkDriveNotesFile -Encoding UTF8
    Append-Line $WorkDriveNotesFile "P:\Root ist DayZ Tools WorkDrive / Vanilla / Legacy-Mischbereich."
    Append-Line $WorkDriveNotesFile "Sauberer Projektstand: $DeutschZRepoRoot"
    Append-Line $WorkDriveNotesFile "ReadyMods ist Build-/PBO-Ausgabe."
    Append-Line $WorkDriveNotesFile "P:\Root wird nicht breit gesichert/exportiert/verschoben/geloescht."
    foreach ($item in @("bin","Core","DZ","graphics","gui","languagecore","scripts","system")) {
        $p = Join-Path "P:\" $item
        if (Test-PathFast $p) { Append-Line $WorkDriveNotesFile "OK/BEHALTEN: $p" } else { Append-Line $WorkDriveNotesFile "FEHLT/OPTIONAL: $p" }
    }
}

function Write-LMStudioPolicy {
    "DeutschZ System Manager v0.4.6 - LM Studio / Modell Policy" | Out-File $LMStudioPolicyFile -Encoding UTF8
    Append-Line $LMStudioPolicyFile "LM Studio ist optional/experimentell."
    Append-Line $LMStudioPolicyFile ".lmstudio und GGUF-Modelle werden NICHT automatisch gesichert/exportiert."
    Append-Line $LMStudioPolicyFile "Bekannter Testpfad: C:\Users\patsl\.lmstudio\models\lmstudio-community\Qwen2.5-Coder-14B-Instruct-GGUF\Qwen2.5-Coder-14B-Instruct-Q3_K_L.gguf"
}

function Update-BugReports {
    "DeutschZ System Manager v0.4.6 - BugReport Arbeitsordner" | Out-File $BugReportLogFile -Encoding UTF8
    foreach ($d in @($BugReportRoot,(Join-Path $BugReportRoot "offen"),(Join-Path $BugReportRoot "geloest"),(Join-Path $BugReportRoot "notizen"),(Join-Path $BugReportRoot "logs"))) {
        New-Item -ItemType Directory -Path $d -Force | Out-Null
    }
    if (-not (Test-PathFast (Join-Path $BugReportRoot "BUGREPORT_AKTUELL.md"))) { "# DZSM BugReport aktuell" | Out-File (Join-Path $BugReportRoot "BUGREPORT_AKTUELL.md") -Encoding UTF8 }
    if (-not (Test-PathFast (Join-Path $BugReportRoot "LOESUNGSWEGE_UND_VERMEIDUNG.md"))) { "# DZSM Loesungswege und Vermeidung" | Out-File (Join-Path $BugReportRoot "LOESUNGSWEGE_UND_VERMEIDUNG.md") -Encoding UTF8 }
    if (-not (Test-PathFast (Join-Path $BugReportRoot "KNOWN_ISSUES.md"))) { "# DZSM Known Issues" | Out-File (Join-Path $BugReportRoot "KNOWN_ISSUES.md") -Encoding UTF8 }
    Append-Line $BugReportLogFile "OK BugReportRoot: $BugReportRoot"
}

function Invoke-Backup {
    "DeutschZ System Manager v0.4.6 - SAFE AUTO BACKUP" | Out-File $BackupLogFile -Encoding UTF8
    Append-Line $BackupLogFile "BackupRoot: $BackupsRoot"
    Append-Line $BackupLogFile "Kein /MIR, kein /PURGE, keine Loeschung."
    $computerRoot = Join-Path $BackupsRoot $env:COMPUTERNAME
    New-Item -ItemType Directory -Path $computerRoot -Force | Out-Null
    $jobs = @(
        @{Name="Desktop"; Source="$env:USERPROFILE\Desktop"; Dest=(Join-Path $computerRoot "Desktop")},
        @{Name="Codex"; Source="$env:USERPROFILE\Documents\Codex"; Dest=(Join-Path $computerRoot "Codex")},
        @{Name="DeutschZModZ_GitHub_Root"; Source=$DeutschZRepoRoot; Dest=(Join-Path $computerRoot "DeutschZModZ_GitHub_Root")},
        @{Name="DZSM_Reports"; Source=$ReportsRoot; Dest=(Join-Path $computerRoot "DZSM_Reports")}
    )
    foreach ($job in $jobs) {
        Append-Line $BackupLogFile "Backup Job: $($job.Name)"
        if (-not (Test-PathFast $job.Source)) { Append-Line $BackupLogFile "SKIP Quelle fehlt: $($job.Source)"; continue }
        New-Item -ItemType Directory -Path $job.Dest -Force | Out-Null
        $rlog = Join-Path $ReportsRoot ("17_ROBOCOPY_" + $job.Name + ".log")
        $args = @("`"$($job.Source)`"","`"$($job.Dest)`"","/E","/XO","/R:1","/W:1","/MT:4","/COPY:DAT","/DCOPY:DAT","/XJ","/NP","/TEE","/XD","`"$BackupsRoot`"","`"$UploadPackageRoot`"","/XF","*.tmp","*.bak","/LOG+:`"$rlog`"")
        try {
            $p = Start-Process robocopy.exe -ArgumentList $args -Wait -PassThru -NoNewWindow
            Append-Line $BackupLogFile "Robocopy ExitCode: $($p.ExitCode)"
        } catch { Append-Line $BackupLogFile "FEHLER Robocopy: $($_.Exception.Message)" }
    }
}

function Update-GitHubExport {
    "DeutschZ System Manager v0.4.6 - GitHub Export" | Out-File $GitHubExportLogFile -Encoding UTF8
    if (-not (Test-PathFast $DeutschZRepoRoot)) { Append-Line $GitHubExportLogFile "SKIP Repo fehlt"; return }
    New-Item -ItemType Directory -Path $GitHubExportRoot -Force | Out-Null
    "# DeutschZ System Manager Tool" | Out-File (Join-Path $GitHubExportRoot "README.md") -Encoding UTF8
    "backups/`nreports/`n*.log`n*.zip`n_archive_old_versions/" | Out-File (Join-Path $GitHubExportRoot ".gitignore") -Encoding UTF8
    foreach ($name in @("app","docs","scripts","DZSM_v0_1")) {
        $src = if ($name -eq "DZSM_v0_1") { $DZSMInstallRoot } else { Join-Path $DZSMBaseRoot $name }
        $dst = Join-Path $GitHubExportRoot $name
        if (Test-PathFast $src) {
            New-Item -ItemType Directory -Path $dst -Force | Out-Null
            $args=@("`"$src`"","`"$dst`"","/E","/XO","/R:1","/W:1","/XJ","/NP","/XD","`"$ArchiveRoot`"","`"$BackupsRoot`"","`"$ReportsRoot`"","/XF","*.log","*.tmp","*.bak","*.zip")
            $p=Start-Process robocopy.exe -ArgumentList $args -Wait -PassThru -NoNewWindow
            Append-Line $GitHubExportLogFile "Job $name ExitCode: $($p.ExitCode)"
        }
    }
}

function Update-SafetyDocs {
    "DeutschZ System Manager v0.4.6 - GitHub Safety Docs" | Out-File $SafetyDocsLogFile -Encoding UTF8
    if (-not (Test-PathFast $DeutschZRepoRoot)) { Append-Line $SafetyDocsLogFile "SKIP Repo fehlt"; return }
    New-Item -ItemType Directory -Path $GitHubSafetyDocsRoot -Force | Out-Null
    "# DZSM README`nNutzung auf eigene Verantwortung. Keine Rechtsberatung." | Out-File (Join-Path $GitHubSafetyDocsRoot "README_DZSM.md") -Encoding UTF8
    "# Disclaimer`nKeine Gewaehr. Vor Nutzung pruefen. Backups Pflicht." | Out-File (Join-Path $GitHubSafetyDocsRoot "DISCLAIMER_NUTZUNG_AUF_EIGENE_VERANTWORTUNG.md") -Encoding UTF8
    "# Safety Rules`nKein Loeschen, kein Formatieren, kein OC, kein PBO-Dekompilieren, kein /MIR, kein /PURGE." | Out-File (Join-Path $GitHubSafetyDocsRoot "SAFETY_RULES.md") -Encoding UTF8
    "# Privacy`nReports koennen lokale Pfade enthalten. Nicht ungeprueft veroeffentlichen." | Out-File (Join-Path $GitHubSafetyDocsRoot "PRIVACY_AND_REPORTS.md") -Encoding UTF8
    "# Changelog`nv0.4.6 DESKTOP-NAMES-CLEANUP" | Out-File (Join-Path $GitHubSafetyDocsRoot "CHANGELOG_DZSM.md") -Encoding UTF8
    Append-Line $SafetyDocsLogFile "OK Safety Docs erstellt."
}

function Update-BuildWrapper {
    "DeutschZ System Manager v0.4.6 - Build Wrapper" | Out-File $BuildWrapperLogFile -Encoding UTF8
    if (-not (Test-PathFast $DeutschZRepoRoot)) { Append-Line $BuildWrapperLogFile "SKIP Repo fehlt"; return }
    New-Item -ItemType Directory -Path $BuildWrapperRoot -Force | Out-Null
    New-Item -ItemType Directory -Path (Join-Path $BuildWrapperRoot "logs") -Force | Out-Null
    @"
param([switch]`$Build,[switch]`$DryRun,[switch]`$Force)
`$RepoRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ"
`$ModsRoot = Join-Path `$RepoRoot "mods"
`$ReadyModsRoot = "P:\ReadyMods"
`$LogRoot = Join-Path `$RepoRoot "tools\build_wrapper\logs"
New-Item -ItemType Directory -Path `$LogRoot -Force | Out-Null
`$LogFile = Join-Path `$LogRoot ("BUILD_WRAPPER_" + (Get-Date -Format "yyyy-MM-dd_HH-mm-ss") + ".log")
function L(`$t) { `$t | Tee-Object -FilePath `$LogFile -Append }
L "DeutschZ Build Wrapper CheckOnly"
L "RepoRoot: `$RepoRoot"
L "ModsRoot: `$ModsRoot"
L "ReadyModsRoot: `$ReadyModsRoot"
L "PDrive: " + (Test-Path "P:\")
foreach (`$m in @("DeutschZ_Core","DeutschZ_ExpansionBridge","DeutschZ_KotHZ","DeutschZ_ConvoyZ","DeutschZ_GroundZero","DeutschZ_CourierZ","DeutschZ_OperationDeutschZ")) {
    `$p = Join-Path `$ModsRoot `$m
    if (Test-Path `$p) { L "OK Mod: `$m" } else { L "FEHLT Mod: `$m" }
}
L "CheckOnly: Kein Build ausgefuehrt."
"@ | Out-File (Join-Path $BuildWrapperRoot "DeutschZ_Build_Wrapper.ps1") -Encoding UTF8
    "@echo off`r`npowershell.exe -NoProfile -ExecutionPolicy Bypass -File ""%~dp0DeutschZ_Build_Wrapper.ps1""`r`npause" | Out-File (Join-Path $BuildWrapperRoot "DeutschZ_Build_Wrapper_CheckOnly.bat") -Encoding ASCII
    [ordered]@{name="DeutschZ Build Wrapper";version="0.4.2";allow_real_build=$false;mode="check-only"} | ConvertTo-Json | Out-File (Join-Path $BuildWrapperRoot "BUILD_CONFIG.json") -Encoding UTF8
    "# DeutschZ Build Wrapper`nStandard: CheckOnly. Echter Build gesperrt." | Out-File (Join-Path $BuildWrapperRoot "README_BUILD_WRAPPER.md") -Encoding UTF8
    Append-Line $BuildWrapperLogFile "OK BuildWrapper erstellt: $BuildWrapperRoot"
}

function Update-Memory {
    "DeutschZ System Manager v0.4.6 - Memory Package" | Out-File $MemoryPackageLogFile -Encoding UTF8
    New-Item -ItemType Directory -Path $MemoryRoot -Force | Out-Null
    $memoryFile = Join-Path $MemoryRoot "CHATGPT_ERINNERUNG_AKTUELL.md"
    $statusFile = Join-Path $MemoryRoot "MEMORY_STATUS.json"
@"
# ChatGPT Erinnerung / Projektstand fuer Patrick / DeutschZ / DZSM

Stand: 2026-06-24
Version: DZSM v0.4.6 DESKTOP-NAMES-CLEANUP

MEMORY_STATUS: AKTUALISIERT
MEMORY_ACTION_FOR_CHATGPT: NEU_SPEICHERN_WENN_DIESER_STAND_FEHLT_ODER_ABWEICHT
USER_INTENT: Patrick will eventuell alte Chats loeschen. Diese Datei dient als uebertragbarer Projekt-/Erinnerungsstand.
SENSIBLE_DATEN: Keine Passwoerter, keine Keys, keine Secrets speichern.

## Wichtigste Regeln

- Sprache: Deutsch.
- Patrick will schnelle, direkte, praezise Arbeit.
- DeutschZ ist ein eigenes DayZ-Mod-Oekosystem.
- Keine fremden Mod-Codes, Klassen, Configs, UI oder Assets kopieren.
- Workshopdateien/SteamWorkshop_Beschreibungen nicht automatisch aendern.
- P:\Root ist DayZ Tools WorkDrive/Vanilla-Arbeitsbereich + Legacy-Mischbereich.
- Sauberer Projektstand: P:\GitHub_DeutschZModZ\DeutschZModZ
- ReadyMods ist Build-/PBO-Ausgabe, nicht GitHub-Quelle.
- P:\ niemals Backup-Ziel.
- LM Studio/.lmstudio/GGUF-Modelle nicht automatisch sichern/exportieren.
- Benutzer-Verknuepfung `DeutschZ_System_Manager - Verknuepfung.lnk` nicht loeschen.
- Nur exakt bekannte DZSM-Auto-Verknuepfungen ersetzen.
- Core Pflicht, ExpansionBridge einzige direkte Expansion-Schicht.
- Aktive Mods/Reihenfolge:
  1. DeutschZ_Core
  2. DeutschZ_ExpansionBridge
  3. DeutschZ_KotHZ
  4. DeutschZ_ConvoyZ
  5. DeutschZ_GroundZero
  6. DeutschZ_CourierZ
  7. DeutschZ_OperationDeutschZ
- Eventmods duerfen untereinander nicht abhaengen; OperationDeutschZ darf spaeter orchestrieren.
- Alle Events muessen ohne Expansion crashfrei laufen.
- Signalstation/Sendestation strikt von KotHZ trennen.
- Green Mountain ist Trader/SafeZone und keine Eventlocation.
- M249-Regel: nur Vanilla M249 und Mag_M249_Box200Rnd blocken; GCGNM249/GCGN_M249 erlauben.
- DZSM Standardstruktur:
  D:\DeutschZ_System_Manager\backups
  D:\DeutschZ_System_Manager\app
  D:\DeutschZ_System_Manager\docs
  D:\DeutschZ_System_Manager\DZSM_v0_1
  D:\DeutschZ_System_Manager\reports
  D:\DeutschZ_System_Manager\scripts
  D:\DeutschZ_System_Manager\bugreports
  D:\DeutschZ_System_Manager\memory
  D:\DeutschZ_System_Manager\reports\_UPLOAD_FUER_CHATGPT
- Build Wrapper:
  P:\GitHub_DeutschZModZ\DeutschZModZ\tools\build_wrapper
  Standard: CheckOnly, echter Build gesperrt bis allow_real_build bewusst true ist.
- Git Commit Helper:
  P:\GitHub_DeutschZModZ\DeutschZModZ\tools\git_commit_helper
  Kein automatischer Push.

"@ | Out-File $memoryFile -Encoding UTF8
    [ordered]@{memory_status="AKTUALISIERT";memory_action_for_chatgpt="NEU_SPEICHERN_WENN_DIESER_STAND_FEHLT_ODER_ABWEICHT";version="DZSM v0.4.6 DESKTOP-NAMES-CLEANUP";date=(Get-Date).ToString("s");secrets_included=$false;should_store_if_missing=$true} | ConvertTo-Json | Out-File $statusFile -Encoding UTF8
    if (Test-PathFast $GitHubSafetyDocsRoot) {
        $repoMemory = Join-Path $GitHubSafetyDocsRoot "memory"
        New-Item -ItemType Directory -Path $repoMemory -Force | Out-Null
        Copy-Item $memoryFile (Join-Path $repoMemory "CHATGPT_ERINNERUNG_AKTUELL.md") -Force
        Copy-Item $statusFile (Join-Path $repoMemory "MEMORY_STATUS.json") -Force
    }
    Append-Line $MemoryPackageLogFile "OK Memory erstellt."
}

function Update-GitCommitHelper {
    "DeutschZ System Manager v0.4.6 - Git Commit Helper" | Out-File $GitCommitHelperLogFile -Encoding UTF8
    if (-not (Test-PathFast $DeutschZRepoRoot)) { Append-Line $GitCommitHelperLogFile "SKIP Repo fehlt"; return }
    New-Item -ItemType Directory -Path $GitCommitHelperRoot -Force | Out-Null
    $msg = @"
chore(dzsm): add system manager, safety docs, upload package and build wrapper

- add/update DeutschZ System Manager tool export
- add safety and usage documentation
- add ChatGPT memory package for project continuity
- add upload package for support/report transfer
- add build wrapper check-only setup
- keep P:\Root as DayZ Tools WorkDrive/legacy area
- keep ReadyMods as build/PBO output
- avoid Workshop file changes
- avoid backing up/exporting LM Studio models
"@
    $msg | Out-File (Join-Path $GitCommitHelperRoot "DZSM_GIT_COMMIT_MESSAGE.txt") -Encoding UTF8
@"
`$RepoRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ"
`$HelperRoot = Join-Path `$RepoRoot "tools\git_commit_helper"
`$CommitMessageFile = Join-Path `$HelperRoot "DZSM_GIT_COMMIT_MESSAGE.txt"
Set-Location `$RepoRoot
git status --short
Get-Content `$CommitMessageFile
`$a = Read-Host "Jetzt git add + commit? (JA)"
if (`$a -ne "JA") { exit 0 }
git add DeutschZ_SystemManager_Tool DeutschZ_SystemManager_Tool_Dokumentation tools\build_wrapper tools\git_commit_helper
git status --short
`$b = Read-Host "Commit erstellen? (JA)"
if (`$b -ne "JA") { exit 0 }
git commit -F `$CommitMessageFile
Write-Host "Commit fertig. Push manuell: git push"
pause
"@ | Out-File (Join-Path $GitCommitHelperRoot "GIT_COMMIT_DZSM_CHECK_AND_COMMIT.ps1") -Encoding UTF8
    "@echo off`r`npowershell.exe -NoProfile -ExecutionPolicy Bypass -File ""%~dp0GIT_COMMIT_DZSM_CHECK_AND_COMMIT.ps1""" | Out-File (Join-Path $GitCommitHelperRoot "GIT_COMMIT_DZSM_CHECK_AND_COMMIT.bat") -Encoding ASCII
    "# Git Commit Helper" | Out-File (Join-Path $GitCommitHelperRoot "README_GIT_COMMIT_HELPER.md") -Encoding UTF8
    Append-Line $GitCommitHelperLogFile "OK GitCommitHelper erstellt."
}

function Update-DeutschZStructureReport {
    "DeutschZ System Manager v0.4.6 - DeutschZ Structure Check" | Out-File $DeutschZFile -Encoding UTF8
    foreach ($p in @($DeutschZRepoRoot,(Join-Path $DeutschZRepoRoot "mods"),(Join-Path $DeutschZRepoRoot "tools"),$BuildWrapperRoot,$GitCommitHelperRoot,$GitHubExportRoot,$GitHubSafetyDocsRoot)) {
        if (Test-PathFast $p) { Append-Line $DeutschZFile "OK: $p" } else { Append-Line $DeutschZFile "FEHLT/OPTIONAL: $p" }
    }
}

function Update-MainReport {
    "DeutschZ System Manager v0.4.6 DESKTOP-NAMES-CLEANUP - Inventurbericht" | Out-File $ReportFile -Encoding UTF8
    foreach ($line in @(
        "PC: $env:COMPUTERNAME",
        "Benutzer: $env:USERNAME",
        "Datum: $(Get-Date)",
        "Reportordner: $ReportsRoot",
        "Backupordner: $BackupsRoot",
        "Sauberer Projektstand: $DeutschZRepoRoot",
        "Uploadpaket: $UploadPackageRoot",
        "Memory: $MemoryRoot",
        "BuildWrapper: $BuildWrapperRoot",
        "GitCommitHelper: $GitCommitHelperRoot",
        "P-Root-Regel: WorkDrive/Vanilla/Legacy, nicht GitHub-Quelle",
        "ReadyMods-Regel: Build-/PBO-Ausgabe",
        "LM-Studio-Regel: nicht automatisch sichern/exportieren"
    )) { Append-Line $ReportFile $line }
    Append-Line $ReportFile ""
    Get-CimInstance Win32_OperatingSystem | Select-Object Caption,Version,BuildNumber,OSArchitecture,WindowsDirectory,LastBootUpTime | Out-String | Out-File $ReportFile -Append -Encoding UTF8
    Get-CimInstance Win32_Processor | Select-Object Name,NumberOfCores,NumberOfLogicalProcessors,MaxClockSpeed | Out-String | Out-File $ReportFile -Append -Encoding UTF8
    Get-CimInstance Win32_VideoController | Select-Object Name,@{n="AdapterRAM_GB";e={GB $_.AdapterRAM}},DriverVersion | Out-String | Out-File $ReportFile -Append -Encoding UTF8
    Get-CimInstance Win32_LogicalDisk | Select-Object DeviceID,VolumeName,FileSystem,@{n="SizeGB";e={GB $_.Size}},@{n="FreeGB";e={GB $_.FreeSpace}} | Out-String | Out-File $ReportFile -Append -Encoding UTF8
}



function Update-Shortcuts {
    "DeutschZ System Manager v0.4.6 - Desktop Namen / Oberordner" | Out-File $ShortcutLogFile -Encoding UTF8
    $desktop = [Environment]::GetFolderPath("Desktop")
    $desktopFolder = Join-Path $desktop "DeutschZ - SystemManager"
    New-Item -ItemType Directory -Path $desktopFolder -Force | Out-Null

    Append-Line $ShortcutLogFile "Desktop: $desktop"
    Append-Line $ShortcutLogFile "Oberordner: $desktopFolder"
    Append-Line $ShortcutLogFile "Regel: Auf Desktop bleiben nur Oberordner und Start-Verknuepfung sichtbar."
    Append-Line $ShortcutLogFile "Start-Link Name: DeutschZ - Vollstaendige Analyse starten.lnk"
    Append-Line $ShortcutLogFile "Geschuetzt: DeutschZ_System_Manager - Verknuepfung.lnk wird nicht geloescht."

    # Nur exakt bekannte alte Auto-Links entfernen. Keine Wildcards.
    $desktopAutoLinks = @(
        "DeutschZ System Manager - Start.lnk",
        "DeutschZ - Vollstaendige Analyse starten.lnk",
        "DeutschZ - Vollständige Analyse starten.lnk",
        "DeutschZ System Manager - Upload Reports.lnk",
        "DeutschZ System Manager - Reports.lnk",
        "DeutschZ Build Wrapper - Check.lnk",
        "DeutschZ System Manager - Script PS1.lnk",
        "DZSM - Start.lnk",
        "DZSM - Script PS1.lnk",
        "DZSM - Upload Reports.lnk"
    )
    foreach ($l in $desktopAutoLinks) {
        $p = Join-Path $desktop $l
        if (Test-PathFast $p) {
            Remove-Item $p -Force -ErrorAction SilentlyContinue
            Append-Line $ShortcutLogFile "OK Desktop Auto-Link entfernt/ersetzt: $p"
        }
    }

    $folderAutoLinks = @(
        "Upload Reports.lnk",
        "Reports.lnk",
        "Build Wrapper - Check.lnk",
        "Uploadpaket fuer ChatGPT.lnk",
        "Uploadpaket für ChatGPT.lnk",
        "Reports oeffnen.lnk",
        "Reports öffnen.lnk",
        "Build Wrapper pruefen.lnk",
        "Build Wrapper prüfen.lnk",
        "Script PS1 - Intern.lnk"
    )
    foreach ($l in $folderAutoLinks) {
        $p = Join-Path $desktopFolder $l
        if (Test-PathFast $p) {
            Remove-Item $p -Force -ErrorAction SilentlyContinue
            Append-Line $ShortcutLogFile "OK Ordner Auto-Link entfernt/ersetzt: $p"
        }
    }

    $shell = New-Object -ComObject WScript.Shell

    $iconStart = Join-Path $PSScriptRoot "icons\DZSM_Start_DarkGlass_Green_v046.ico"
    $iconFolder = Join-Path $PSScriptRoot "icons\DZSM_Folder_DarkGlass_Green_v046.ico"
    $iconUpload = Join-Path $PSScriptRoot "icons\DZSM_Upload_DarkGlass_Green_v046.ico"
    $iconReports = Join-Path $PSScriptRoot "icons\DZSM_Reports_DarkGlass_Green_v046.ico"
    $iconBuild = Join-Path $PSScriptRoot "icons\DZSM_Build_DarkGlass_Green_v046.ico"

    # Desktop: nur Start-Link
    $startTarget = Join-Path $PSScriptRoot "Start_DZSM_v0_4_6_DESKTOP_NAMES_CLEANUP.bat"
    if (Test-PathFast $startTarget) {
        $s = $shell.CreateShortcut((Join-Path $desktop "DeutschZ - Vollstaendige Analyse starten.lnk"))
        $s.TargetPath = $startTarget
        $s.WorkingDirectory = $PSScriptRoot
        $s.Description = "Startet die vollstaendige DeutschZ System Manager Analyse"
        if (Test-PathFast $iconStart) { $s.IconLocation = $iconStart }
        $s.Save()
        Append-Line $ShortcutLogFile "OK Desktop Start-Link erstellt: DeutschZ - Vollstaendige Analyse starten.lnk"
    }

    # Oberordner: Folder Icon via desktop.ini
    try {
        if (Test-PathFast $iconFolder) {
            $desktopIni = Join-Path $desktopFolder "desktop.ini"
@"
[.ShellClassInfo]
IconResource=$iconFolder,0
IconFile=$iconFolder
IconIndex=0
InfoTip=DeutschZ System Manager Werkzeuge
"@ | Out-File -FilePath $desktopIni -Encoding ASCII
            attrib +s "$desktopFolder" | Out-Null
            attrib +h +s "$desktopIni" | Out-Null
            Append-Line $ShortcutLogFile "OK Oberordner Icon gesetzt."
        }
    } catch {
        Append-Line $ShortcutLogFile "WARNUNG Oberordner Icon: $($_.Exception.Message)"
    }

    # Oberordner: interne Links mit sauberen Namen
    if (Test-PathFast $UploadPackageRoot) {
        $u = $shell.CreateShortcut((Join-Path $desktopFolder "Uploadpaket fuer ChatGPT.lnk"))
        $u.TargetPath = $UploadPackageRoot
        $u.WorkingDirectory = $UploadPackageRoot
        $u.Description = "Upload-Paket fuer ChatGPT"
        if (Test-PathFast $iconUpload) { $u.IconLocation = $iconUpload }
        $u.Save()
        Append-Line $ShortcutLogFile "OK Ordner-Link erstellt: Uploadpaket fuer ChatGPT"
    }

    if (Test-PathFast $ReportsRoot) {
        $r = $shell.CreateShortcut((Join-Path $desktopFolder "Reports oeffnen.lnk"))
        $r.TargetPath = $ReportsRoot
        $r.WorkingDirectory = $ReportsRoot
        $r.Description = "DZSM Reports oeffnen"
        if (Test-PathFast $iconReports) { $r.IconLocation = $iconReports }
        $r.Save()
        Append-Line $ShortcutLogFile "OK Ordner-Link erstellt: Reports oeffnen"
    }

    $buildTarget = Join-Path $BuildWrapperRoot "DeutschZ_Build_Wrapper_CheckOnly.bat"
    if (Test-PathFast $buildTarget) {
        $b = $shell.CreateShortcut((Join-Path $desktopFolder "Build Wrapper pruefen.lnk"))
        $b.TargetPath = $buildTarget
        $b.WorkingDirectory = $BuildWrapperRoot
        $b.Description = "DeutschZ Build Wrapper CheckOnly pruefen"
        if (Test-PathFast $iconBuild) { $b.IconLocation = $iconBuild }
        $b.Save()
        Append-Line $ShortcutLogFile "OK Ordner-Link erstellt: Build Wrapper pruefen"
    }

    try {
        Start-Process "$env:SystemRoot\System32\ie4uinit.exe" -ArgumentList "-show" -WindowStyle Hidden -ErrorAction SilentlyContinue
        Append-Line $ShortcutLogFile "OK Icon-Refresh angestossen."
    } catch {}
}


function Update-UploadPackage {
    "DeutschZ System Manager v0.4.6 - Upload-Paket FINAL" | Out-File $UploadPackageLogFile -Encoding UTF8
    New-Item -ItemType Directory -Path $UploadPackageRoot -Force | Out-Null
    Get-ChildItem -Path $UploadPackageRoot -File -ErrorAction SilentlyContinue | Remove-Item -Force -ErrorAction SilentlyContinue
    $files = @("00_ZUSAMMENFASSUNG.txt","11_DEUTSCHZ_STRUCTURE_CHECK.txt","16_DZSM_SELF_CLEANUP.txt","17_SAFE_AUTO_BACKUP_LOG.txt","18_DZSM_STANDARD_STRUCTURE.txt","19_GITHUB_EXPORT_LOG.txt","21_GITHUB_SAFETY_DOCS_LOG.txt","22_P_ROOT_WORKDRIVE_NOTES.txt","23_LMSTUDIO_MODEL_POLICY.txt","24_DESKTOP_SHORTCUTS_LOG.txt","25_BUGREPORT_WORKSPACE_LOG.txt","26_UPLOAD_PACKAGE_LOG.txt","27_BUILD_WRAPPER_LOG.txt","28_MEMORY_PACKAGE_LOG.txt","29_GIT_COMMIT_HELPER_LOG.txt","29_GIT_COMMIT_HELPER_LOG.txt`r`n- 30_GIT_MERGE_STATUS.txt`r`n- 31_GIT_CONFLICT_FILES.txt`r`n- 32_GIT_CONFLICT_MARKERS_CONTEXT.txt`r`n- 33_GIT_MERGE_DECISION_GUIDE.md",
        "30_GIT_MERGE_STATUS.txt",
        "31_GIT_CONFLICT_FILES.txt",
        "32_GIT_CONFLICT_MARKERS_CONTEXT.txt",
        "33_GIT_MERGE_DECISION_GUIDE.md","99_NAECHSTE_SCHRITTE.txt")
    foreach ($fn in $files) {
        $src=Join-Path $ReportsRoot $fn
        if (Test-PathFast $src) { Copy-Item $src (Join-Path $UploadPackageRoot $fn) -Force; Append-Line $UploadPackageLogFile "OK kopiert: $fn" }
        else { Append-Line $UploadPackageLogFile "FEHLT: $fn" }
    }
    foreach ($extra in @(
        @(Join-Path $MemoryRoot "CHATGPT_ERINNERUNG_AKTUELL.md"),
        @(Join-Path $MemoryRoot "MEMORY_STATUS.json"),
        @(Join-Path $GitCommitHelperRoot "DZSM_GIT_COMMIT_MESSAGE.txt")
    )) {
        if (Test-PathFast $extra) { Copy-Item $extra (Join-Path $UploadPackageRoot (Split-Path $extra -Leaf)) -Force }
    }
    "Uploadpaket fuer ChatGPT. Diesen Ordner oder DZSM_UPLOAD_PACKAGE.zip hochladen." | Out-File (Join-Path $UploadPackageRoot "README_UPLOAD_HINWEIS.txt") -Encoding UTF8
    $zip = Join-Path $UploadPackageRoot "DZSM_UPLOAD_PACKAGE.zip"
    if (Test-PathFast $zip) { Remove-Item $zip -Force }
    Compress-Archive -Path (Join-Path $UploadPackageRoot "*") -DestinationPath $zip -Force
    Append-Line $UploadPackageLogFile "OK ZIP erstellt: $zip"
}

function Write-Next {
@"
DeutschZ System Manager - Naechste Schritte
==========================================
Aktuelle Version: v0.4.6 DESKTOP-NAMES-CLEANUP

Bitte ab jetzt hochladen:
$UploadPackageRoot\DZSM_UPLOAD_PACKAGE.zip

Dieses Paket muss enthalten:
- 27_BUILD_WRAPPER_LOG.txt
- 28_MEMORY_PACKAGE_LOG.txt
- 29_GIT_COMMIT_HELPER_LOG.txt`r`n- 30_GIT_MERGE_STATUS.txt`r`n- 31_GIT_CONFLICT_FILES.txt`r`n- 32_GIT_CONFLICT_MARKERS_CONTEXT.txt`r`n- 33_GIT_MERGE_DECISION_GUIDE.md
- CHATGPT_ERINNERUNG_AKTUELL.md
- MEMORY_STATUS.json
- DZSM_GIT_COMMIT_MESSAGE.txt

Git Commit Helper:
$GitCommitHelperRoot\GIT_COMMIT_DZSM_CHECK_AND_COMMIT.bat
"@ | Out-File $NextFile -Encoding UTF8
}

Invoke-SelfCleanup
Write-Structure
Write-WorkDriveNotes
Write-LMStudioPolicy
Update-BugReports
Invoke-Backup
Update-GitHubExport
Update-SafetyDocs
Update-BuildWrapper
Update-Memory
Update-GitCommitHelper
Update-DeutschZStructureReport
Update-MainReport
Write-Next
Update-Shortcuts
Update-GitMergeDiagnostics
Update-UploadPackage

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
Start-Sleep -Seconds 5
exit 0
