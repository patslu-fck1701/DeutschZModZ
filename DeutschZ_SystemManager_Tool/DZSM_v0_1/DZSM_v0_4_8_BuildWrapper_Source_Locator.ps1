# DeutschZ System Manager v0.4.8 BUILDWRAPPER-SOURCE-LOCATOR
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
$GitHubExportRoot = Join-Path $DeutschZRepoRoot "DeutschZ_SystemManager_Tool"
$GitHubSafetyDocsRoot = Join-Path $DeutschZRepoRoot "DeutschZ_SystemManager_Tool_Dokumentation"
$BuildWrapperRoot = Join-Path $DeutschZRepoRoot "tools\build_wrapper"
$GitCommitHelperRoot = Join-Path $DeutschZRepoRoot "tools\git_commit_helper"
$CurrentVersionToken = "0_4_8"

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
$GitCommitHelperLogFile = Join-Path $ReportsRoot "29_GIT_COMMIT_HELPER_LOG.txt"
$GitMergeStatusFile = Join-Path $ReportsRoot "30_GIT_MERGE_STATUS.txt"
$GitConflictFilesFile = Join-Path $ReportsRoot "31_GIT_CONFLICT_FILES.txt"
$GitConflictMarkersFile = Join-Path $ReportsRoot "32_GIT_CONFLICT_MARKERS_CONTEXT.txt"
$GitMergeGuideFile = Join-Path $ReportsRoot "33_GIT_MERGE_DECISION_GUIDE.md"
$ModSourceLocatorFile = Join-Path $ReportsRoot "34_MOD_SOURCE_LOCATOR.txt"
$NextFile = Join-Path $ReportsRoot "99_NAECHSTE_SCHRITTE.txt"

function Test-PathFast($p) { try { Test-Path $p } catch { $false } }
function Append-Line($f,$t) { $t | Out-File -FilePath $f -Append -Encoding UTF8 }
function GB($b) { if ($null -eq $b -or $b -eq "") { "" } else { [math]::Round(([double]$b/1GB),2) } }

foreach ($f in @($ReportFile,$DeutschZFile,$SelfCleanupFile,$BackupLogFile,$StructureFile,$GitHubExportLogFile,$SafetyDocsLogFile,$WorkDriveNotesFile,$LMStudioPolicyFile,$ShortcutLogFile,$BugReportLogFile,$UploadPackageLogFile,$BuildWrapperLogFile,$MemoryPackageLogFile,$GitCommitHelperLogFile,$GitMergeStatusFile,$GitConflictFilesFile,$GitConflictMarkersFile,$GitMergeGuideFile,$ModSourceLocatorFile,$NextFile)) {
    if (Test-PathFast $f) { Remove-Item $f -Force -ErrorAction SilentlyContinue }
}

function Invoke-SelfCleanup {
    "DeutschZ System Manager v0.4.8 - Selbstbereinigung" | Out-File $SelfCleanupFile -Encoding UTF8
    Append-Line $SelfCleanupFile "InstallRoot: $DZSMInstallRoot"
    Append-Line $SelfCleanupFile "Archivziel Root: $ArchiveRoot"
    $archiveTarget = Join-Path $ArchiveRoot (Get-Date -Format "yyyy-MM-dd_HH-mm-ss")
    New-Item -ItemType Directory -Path $archiveTarget -Force | Out-Null
    $keep = @("Start_DZSM_v0_4_8_BUILDWRAPPER_SOURCE_LOCATOR.bat","DZSM_v0_4_8_BuildWrapper_Source_Locator.ps1","README_START.txt","DZSM_Config.json")
    $candidates = @()
    Get-ChildItem -Path $DZSMInstallRoot -File -ErrorAction SilentlyContinue | ForEach-Object {
        if ((($_.Name -like "Start_DZSM_*.bat") -or ($_.Name -like "DZSM_*.ps1") -or ($_.Name -like "DZSM_v*.zip") -or ($_.Name -like "README_START*.txt") -or ($_.Name -like "DZSM_Config*.json")) -and ($keep -notcontains $_.Name)) { $candidates += $_ }
    }
    foreach ($item in $candidates) {
        try { Move-Item $item.FullName (Join-Path $archiveTarget $item.Name) -Force -ErrorAction Stop; Append-Line $SelfCleanupFile "OK archiviert: $($item.FullName)" }
        catch { Append-Line $SelfCleanupFile "FEHLER: $($item.FullName) $($_.Exception.Message)" }
    }
    if ($candidates.Count -eq 0) { Append-Line $SelfCleanupFile "Keine alten DZSM-Dateien gefunden." }
}

function Write-Structure {
    "DeutschZ System Manager v0.4.8 - Standardstruktur" | Out-File $StructureFile -Encoding UTF8
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
Aktuelle Version: v0.4.8 BUILDWRAPPER-SOURCE-LOCATOR
Startdatei: Start_DZSM_v0_4_8_BUILDWRAPPER_SOURCE_LOCATOR.bat
Uploadpaket: $UploadPackageRoot
Memory: $MemoryRoot
BuildWrapper: $BuildWrapperRoot
GitCommitHelper: $GitCommitHelperRoot
"@ | Out-File $ArbeitsstandFile -Encoding UTF8
}

function Write-WorkDriveNotes {
    "DeutschZ System Manager v0.4.8 - P-Root / WorkDrive Notes" | Out-File $WorkDriveNotesFile -Encoding UTF8
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
    "DeutschZ System Manager v0.4.8 - LM Studio / Modell Policy" | Out-File $LMStudioPolicyFile -Encoding UTF8
    Append-Line $LMStudioPolicyFile "LM Studio ist optional/experimentell."
    Append-Line $LMStudioPolicyFile ".lmstudio und GGUF-Modelle werden NICHT automatisch gesichert/exportiert."
}

function Update-BugReports {
    "DeutschZ System Manager v0.4.8 - BugReport Arbeitsordner" | Out-File $BugReportLogFile -Encoding UTF8
    foreach ($d in @($BugReportRoot,(Join-Path $BugReportRoot "offen"),(Join-Path $BugReportRoot "geloest"),(Join-Path $BugReportRoot "notizen"),(Join-Path $BugReportRoot "logs"))) { New-Item -ItemType Directory -Path $d -Force | Out-Null }
    if (-not (Test-PathFast (Join-Path $BugReportRoot "BUGREPORT_AKTUELL.md"))) { "# DZSM BugReport aktuell" | Out-File (Join-Path $BugReportRoot "BUGREPORT_AKTUELL.md") -Encoding UTF8 }
    if (-not (Test-PathFast (Join-Path $BugReportRoot "LOESUNGSWEGE_UND_VERMEIDUNG.md"))) { "# DZSM Loesungswege und Vermeidung" | Out-File (Join-Path $BugReportRoot "LOESUNGSWEGE_UND_VERMEIDUNG.md") -Encoding UTF8 }
    if (-not (Test-PathFast (Join-Path $BugReportRoot "KNOWN_ISSUES.md"))) { "# DZSM Known Issues" | Out-File (Join-Path $BugReportRoot "KNOWN_ISSUES.md") -Encoding UTF8 }
    Append-Line $BugReportLogFile "OK BugReportRoot: $BugReportRoot"
}

function Invoke-Backup {
    "DeutschZ System Manager v0.4.8 - SAFE AUTO BACKUP" | Out-File $BackupLogFile -Encoding UTF8
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
        $args = @("`"$($job.Source)`"","`"$($job.Dest)`"","/E","/XO","/R:1","/W:1","/MT:4","/COPY:DAT","/DCOPY:DAT","/XJ","/NP","/XD","`"$BackupsRoot`"","`"$UploadPackageRoot`"","/XF","*.tmp","*.bak","/LOG+:`"$rlog`"")
        try { $p = Start-Process robocopy.exe -ArgumentList $args -Wait -PassThru -NoNewWindow; Append-Line $BackupLogFile "Robocopy ExitCode: $($p.ExitCode)" }
        catch { Append-Line $BackupLogFile "FEHLER Robocopy: $($_.Exception.Message)" }
    }
}

function Update-GitHubExport {
    "DeutschZ System Manager v0.4.8 - GitHub Export" | Out-File $GitHubExportLogFile -Encoding UTF8
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
    "DeutschZ System Manager v0.4.8 - GitHub Safety Docs" | Out-File $SafetyDocsLogFile -Encoding UTF8
    if (-not (Test-PathFast $DeutschZRepoRoot)) { Append-Line $SafetyDocsLogFile "SKIP Repo fehlt"; return }
    New-Item -ItemType Directory -Path $GitHubSafetyDocsRoot -Force | Out-Null
    "# DZSM README`nNutzung auf eigene Verantwortung. Keine Rechtsberatung." | Out-File (Join-Path $GitHubSafetyDocsRoot "README_DZSM.md") -Encoding UTF8
    "# Disclaimer`nKeine Gewaehr. Vor Nutzung pruefen. Backups Pflicht." | Out-File (Join-Path $GitHubSafetyDocsRoot "DISCLAIMER_NUTZUNG_AUF_EIGENE_VERANTWORTUNG.md") -Encoding UTF8
    "# Safety Rules`nKein Loeschen, kein Formatieren, kein OC, kein PBO-Dekompilieren, kein /MIR, kein /PURGE." | Out-File (Join-Path $GitHubSafetyDocsRoot "SAFETY_RULES.md") -Encoding UTF8
    "# Privacy`nReports koennen lokale Pfade enthalten. Nicht ungeprueft veroeffentlichen." | Out-File (Join-Path $GitHubSafetyDocsRoot "PRIVACY_AND_REPORTS.md") -Encoding UTF8
    "# Changelog`nv0.4.8 BUILDWRAPPER-SOURCE-LOCATOR" | Out-File (Join-Path $GitHubSafetyDocsRoot "CHANGELOG_DZSM.md") -Encoding UTF8
    Append-Line $SafetyDocsLogFile "OK Safety Docs erstellt."
}


function Update-BuildWrapper {
    "DeutschZ System Manager v0.4.8 - Build Wrapper Source Locator" | Out-File $BuildWrapperLogFile -Encoding UTF8
    "Datum: $(Get-Date)" | Out-File $BuildWrapperLogFile -Append -Encoding UTF8
    "Ziel: Build Wrapper erstellt plus Source-/ModsRoot-Locator." | Out-File $BuildWrapperLogFile -Append -Encoding UTF8
    "" | Out-File $BuildWrapperLogFile -Append -Encoding UTF8

    "DeutschZ System Manager v0.4.8 - Mod Source Locator" | Out-File $ModSourceLocatorFile -Encoding UTF8
    "Datum: $(Get-Date)" | Out-File $ModSourceLocatorFile -Append -Encoding UTF8
    "Zweck: Klaeren, wo die aktiven DeutschZ-Modquellen wirklich liegen." | Out-File $ModSourceLocatorFile -Append -Encoding UTF8
    "" | Out-File $ModSourceLocatorFile -Append -Encoding UTF8

    $activeMods = @(
        "DeutschZ_Core",
        "DeutschZ_ExpansionBridge",
        "DeutschZ_KotHZ",
        "DeutschZ_ConvoyZ",
        "DeutschZ_GroundZero",
        "DeutschZ_CourierZ",
        "DeutschZ_OperationDeutschZ"
    )

    function Write-ModLocatorLine([string]$Text) {
        $Text | Out-File -FilePath $ModSourceLocatorFile -Append -Encoding UTF8
    }

    function Count-ActiveModsInRoot([string]$ModsRoot) {
        $count = 0
        foreach ($m in $activeMods) {
            if (Test-PathFast (Join-Path $ModsRoot $m)) { $count++ }
        }
        return $count
    }

    function Find-DZSMRepoCandidates {
        $candidates = New-Object System.Collections.Generic.List[string]

        foreach ($p in @(
            "P:\GitHub_DeutschZModZ\DeutschZModZ",
            "$env:USERPROFILE\Documents\DayZ Projects\GitHub_DeutschZModZ\DeutschZModZ",
            "C:\Users\patsl\Documents\DayZ Projects\GitHub_DeutschZModZ\DeutschZModZ",
            "D:\GitHub_DeutschZModZ\DeutschZModZ",
            "D:\DeutschZModZ",
            "C:\GitHub_DeutschZModZ\DeutschZModZ"
        )) {
            if ($p -and -not $candidates.Contains($p)) { $candidates.Add($p) }
        }

        # Gezielt, nicht breit: nur naheliegende Projektwurzeln scannen.
        foreach ($scanRoot in @(
            "P:\GitHub_DeutschZModZ",
            "$env:USERPROFILE\Documents\DayZ Projects\GitHub_DeutschZModZ",
            "C:\Users\patsl\Documents\DayZ Projects\GitHub_DeutschZModZ",
            "D:\DeutschZ_System_Manager",
            "D:\GitHub_DeutschZModZ"
        )) {
            try {
                if (Test-PathFast $scanRoot) {
                    Get-ChildItem -Path $scanRoot -Directory -Recurse -ErrorAction SilentlyContinue |
                        Where-Object { $_.Name -eq "DeutschZModZ" -or $_.Name -eq "DeutschZModZ-main" } |
                        ForEach-Object {
                            if (-not $candidates.Contains($_.FullName)) { $candidates.Add($_.FullName) }
                        }
                }
            } catch {}
        }

        return @($candidates)
    }

    function Resolve-DZSMModsRoot {
        $repoCandidates = Find-DZSMRepoCandidates
        Write-ModLocatorLine "---- Repo-Kandidaten ----"

        $best = $null
        $bestScore = -1

        foreach ($repo in $repoCandidates) {
            $exists = Test-PathFast $repo
            $modsRoot = Join-Path $repo "mods"
            $modsExists = Test-PathFast $modsRoot
            $score = if ($modsExists) { Count-ActiveModsInRoot $modsRoot } else { 0 }

            Write-ModLocatorLine ("Repo: {0}" -f $repo)
            Write-ModLocatorLine ("  Exists: {0}" -f $exists)
            Write-ModLocatorLine ("  ModsRoot: {0}" -f $modsRoot)
            Write-ModLocatorLine ("  ModsRootExists: {0}" -f $modsExists)
            Write-ModLocatorLine ("  ActiveModCount: {0}" -f $score)

            if ($modsExists) {
                foreach ($m in $activeMods) {
                    $mp = Join-Path $modsRoot $m
                    if (Test-PathFast $mp) { Write-ModLocatorLine ("    OK Mod: {0}" -f $m) }
                    else { Write-ModLocatorLine ("    FEHLT Mod: {0}" -f $m) }
                }
            }

            if ($score -gt $bestScore) {
                $bestScore = $score
                $best = [ordered]@{
                    RepoRoot = $repo
                    ModsRoot = $modsRoot
                    Score = $score
                    ModsRootExists = $modsExists
                }
            }
        }

        Write-ModLocatorLine ""
        Write-ModLocatorLine "---- Einzelne DeutschZ-Modordner Suche in naheliegenden Wurzeln ----"
        foreach ($root in @(
            "P:\",
            "$env:USERPROFILE\Documents\DayZ Projects",
            "C:\Users\patsl\Documents\DayZ Projects",
            "D:\DeutschZ_System_Manager",
            "D:\GitHub_DeutschZModZ"
        )) {
            if (-not (Test-PathFast $root)) {
                Write-ModLocatorLine "SKIP Root fehlt: $root"
                continue
            }
            foreach ($m in $activeMods) {
                try {
                    $found = Get-ChildItem -Path $root -Directory -Recurse -ErrorAction SilentlyContinue |
                        Where-Object { $_.Name -eq $m } |
                        Select-Object -First 5
                    foreach ($f in $found) {
                        Write-ModLocatorLine ("FOUND {0}: {1}" -f $m, $f.FullName)
                    }
                } catch {
                    Write-ModLocatorLine ("WARN Suche fehlgeschlagen fuer {0} in {1}: {2}" -f $m,$root,$_.Exception.Message)
                }
            }
        }

        return $best
    }

    "PDriveExists: $(Test-PathFast 'P:\')" | Out-File $BuildWrapperLogFile -Append -Encoding UTF8
    "ConfiguredRepoRoot: $DeutschZRepoRoot" | Out-File $BuildWrapperLogFile -Append -Encoding UTF8
    "ConfiguredModsRoot: $(Join-Path $DeutschZRepoRoot 'mods')" | Out-File $BuildWrapperLogFile -Append -Encoding UTF8

    $resolved = Resolve-DZSMModsRoot
    if ($null -eq $resolved) {
        "FEHLER: Kein Repo-/ModsRoot-Kandidat gefunden." | Out-File $BuildWrapperLogFile -Append -Encoding UTF8
        Write-ModLocatorLine "FEHLER: Kein Repo-/ModsRoot-Kandidat gefunden."
        return
    }

    $resolvedRepoRoot = [string]$resolved.RepoRoot
    $resolvedModsRoot = [string]$resolved.ModsRoot
    $resolvedScore = [int]$resolved.Score

    "" | Out-File $BuildWrapperLogFile -Append -Encoding UTF8
    "ResolvedRepoRoot: $resolvedRepoRoot" | Out-File $BuildWrapperLogFile -Append -Encoding UTF8
    "ResolvedModsRoot: $resolvedModsRoot" | Out-File $BuildWrapperLogFile -Append -Encoding UTF8
    "ResolvedActiveModCount: $resolvedScore" | Out-File $BuildWrapperLogFile -Append -Encoding UTF8

    if (-not (Test-PathFast $resolvedRepoRoot)) {
        "ABBRUCH: ResolvedRepoRoot existiert nicht." | Out-File $BuildWrapperLogFile -Append -Encoding UTF8
        return
    }

    $localBuildWrapperRoot = Join-Path $resolvedRepoRoot "tools\build_wrapper"
    New-Item -ItemType Directory -Path $localBuildWrapperRoot -Force | Out-Null
    New-Item -ItemType Directory -Path (Join-Path $localBuildWrapperRoot "logs") -Force | Out-Null

    $wrapperPs1Path = Join-Path $localBuildWrapperRoot "DeutschZ_Build_Wrapper.ps1"
    $wrapperBatPath = Join-Path $localBuildWrapperRoot "DeutschZ_Build_Wrapper_CheckOnly.bat"
    $wrapperConfigPath = Join-Path $localBuildWrapperRoot "BUILD_CONFIG.json"
    $wrapperReadmePath = Join-Path $localBuildWrapperRoot "README_BUILD_WRAPPER.md"

$wrapperPs1 = @'
param(
    [switch]$Build,
    [switch]$DryRun,
    [switch]$Force
)

$ErrorActionPreference = "Continue"

$ActiveMods = @(
    "DeutschZ_Core",
    "DeutschZ_ExpansionBridge",
    "DeutschZ_KotHZ",
    "DeutschZ_ConvoyZ",
    "DeutschZ_GroundZero",
    "DeutschZ_CourierZ",
    "DeutschZ_OperationDeutschZ"
)

function Test-PathSafe([string]$Path) {
    try { return (Test-Path $Path) } catch { return $false }
}

function Count-ActiveMods([string]$ModsRoot) {
    $count = 0
    foreach ($m in $ActiveMods) {
        if (Test-PathSafe (Join-Path $ModsRoot $m)) { $count++ }
    }
    return $count
}

function Resolve-RepoAndMods {
    $candidates = @(
        "P:\GitHub_DeutschZModZ\DeutschZModZ",
        "$env:USERPROFILE\Documents\DayZ Projects\GitHub_DeutschZModZ\DeutschZModZ",
        "C:\Users\patsl\Documents\DayZ Projects\GitHub_DeutschZModZ\DeutschZModZ",
        "D:\GitHub_DeutschZModZ\DeutschZModZ",
        "D:\DeutschZModZ",
        "C:\GitHub_DeutschZModZ\DeutschZModZ"
    ) | Select-Object -Unique

    $bestRepo = $null
    $bestMods = $null
    $bestScore = -1

    foreach ($repo in $candidates) {
        $mods = Join-Path $repo "mods"
        $score = if (Test-PathSafe $mods) { Count-ActiveMods $mods } else { 0 }
        if ($score -gt $bestScore) {
            $bestScore = $score
            $bestRepo = $repo
            $bestMods = $mods
        }
    }

    return [ordered]@{
        RepoRoot = $bestRepo
        ModsRoot = $bestMods
        Score = $bestScore
    }
}

$Resolved = Resolve-RepoAndMods
$RepoRoot = [string]$Resolved.RepoRoot
$ModsRoot = [string]$Resolved.ModsRoot
$ReadyModsRoot = "P:\ReadyMods"
$BuildWrapperRoot = Join-Path $RepoRoot "tools\build_wrapper"
$LogRoot = Join-Path $BuildWrapperRoot "logs"
New-Item -ItemType Directory -Path $LogRoot -Force | Out-Null
$LogFile = Join-Path $LogRoot ("BUILD_WRAPPER_" + (Get-Date -Format "yyyy-MM-dd_HH-mm-ss") + ".log")

function L([string]$Text) {
    $Text | Tee-Object -FilePath $LogFile -Append
}

L "DeutschZ Build Wrapper v0.4.8 CheckOnly"
L "PDriveExists: $(Test-PathSafe 'P:\')"
L "ResolvedRepoRoot: $RepoRoot"
L "ResolvedModsRoot: $ModsRoot"
L "ResolvedActiveModCount: $($Resolved.Score)"
L "ReadyModsRoot: $ReadyModsRoot"
L ""

if (-not (Test-PathSafe $RepoRoot)) {
    L "ABBRUCH: RepoRoot existiert nicht."
    L "Hinweis: DZSM_UPLOAD_PACKAGE hochladen, damit Pfade geprueft werden koennen."
    pause
    exit 2
}

if (-not (Test-PathSafe $ModsRoot)) {
    L "ABBRUCH: ModsRoot fehlt: $ModsRoot"
    L "Das ist kein Buildfehler, sondern ein Quellen-/Repo-Strukturproblem."
    L "Erwartet wird ein Ordner: <RepoRoot>\mods"
    L "Beispiel: P:\GitHub_DeutschZModZ\DeutschZModZ\mods"
    L "Kein Build ausgefuehrt."
    pause
    exit 3
}

$missingRequired = @()
foreach ($m in $ActiveMods) {
    $p = Join-Path $ModsRoot $m
    if (Test-PathSafe $p) {
        L "OK Mod: $m => $p"
    } else {
        L "FEHLT Mod: $m => $p"
        if ($m -ne "DeutschZ_OperationDeutschZ") {
            $missingRequired += $m
        }
    }
}

if ($missingRequired.Count -gt 0) {
    L ""
    L "ABBRUCH: Pflichtmods fehlen: $($missingRequired -join ', ')"
    L "Kein Build ausgefuehrt."
    pause
    exit 4
}

L ""
L "CheckOnly erfolgreich: Modquelle ist eindeutig genug."
L "Echter Build bleibt gesperrt, bis BUILD_CONFIG.json allow_real_build=true enthaelt."
L "Kein Build ausgefuehrt."
pause
exit 0
'@

    $wrapperPs1 | Out-File -FilePath $wrapperPs1Path -Encoding UTF8

$wrapperBat = @"
@echo off
chcp 65001 >nul
title DeutschZ Build Wrapper - CheckOnly
echo ============================================================
echo DeutschZ Build Wrapper - CheckOnly v0.4.8
echo Source Locator aktiv
echo Kein echter Build.
echo ============================================================
echo.
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0DeutschZ_Build_Wrapper.ps1"
"@
    $wrapperBat | Out-File -FilePath $wrapperBatPath -Encoding ASCII

$config = [ordered]@{
    name = "DeutschZ Build Wrapper"
    version = "0.4.8"
    allow_real_build = $false
    mode = "check-only source-locator"
    configured_repo_root = $DeutschZRepoRoot
    resolved_repo_root = $resolvedRepoRoot
    resolved_mods_root = $resolvedModsRoot
    resolved_active_mod_count = $resolvedScore
    rules = @{
        no_workshop_file_changes = $true
        no_p_root_cleanup = $true
        no_legacy_delete = $true
        no_mixed_readymods_state = $true
        require_clear_mods_root = $true
    }
}
$config | ConvertTo-Json -Depth 8 | Out-File -FilePath $wrapperConfigPath -Encoding UTF8

$readme = @"
# DeutschZ Build Wrapper v0.4.8

Standard: CheckOnly.

Diese Version sucht die Modquelle, statt starr nur diesen Pfad zu erwarten:

```text
P:\GitHub_DeutschZModZ\DeutschZModZ\mods
```

Wenn `mods` fehlt, wird kein Build gestartet.

Siehe DZSM Report:

```text
34_MOD_SOURCE_LOCATOR.txt
```

## Wichtig

Wenn der Report zeigt, dass `mods` im GitHub-Root fehlt, muss zuerst der echte Source-Ordner geklaert/kopiert/committed werden. Build erst danach.
"@
    $readme | Out-File -FilePath $wrapperReadmePath -Encoding UTF8

    "OK BuildWrapper erstellt: $localBuildWrapperRoot" | Out-File $BuildWrapperLogFile -Append -Encoding UTF8
    "OK Source Locator Report: $ModSourceLocatorFile" | Out-File $BuildWrapperLogFile -Append -Encoding UTF8
}


function Update-Memory {
    "DeutschZ System Manager v0.4.8 - Memory Package" | Out-File $MemoryPackageLogFile -Encoding UTF8
    New-Item -ItemType Directory -Path $MemoryRoot -Force | Out-Null
    $memoryFile = Join-Path $MemoryRoot "CHATGPT_ERINNERUNG_AKTUELL.md"
    $statusFile = Join-Path $MemoryRoot "MEMORY_STATUS.json"
@"
# ChatGPT Erinnerung / Projektstand fuer Patrick / DeutschZ / DZSM

Stand: 2026-06-24
Version: DZSM v0.4.8 BUILDWRAPPER-SOURCE-LOCATOR

MEMORY_STATUS: AKTUALISIERT
MEMORY_ACTION_FOR_CHATGPT: NEU_SPEICHERN_WENN_DIESER_STAND_FEHLT_ODER_ABWEICHT
USER_INTENT: Patrick will eventuell alte Chats loeschen. Diese Datei dient als uebertragbarer Projekt-/Erinnerungsstand.
SENSIBLE_DATEN: Keine Passwoerter, keine Keys, keine Secrets speichern.

## Kernregeln
- Deutsch, direkt, praezise.
- DeutschZ ist eigenes DayZ-Mod-Oekosystem.
- Keine Fremdmod-Code/Config/UI/Asset-Kopien.
- Workshopdateien nicht automatisch aendern.
- P:\Root ist DayZ Tools WorkDrive/Vanilla/Legacy, nicht GitHub-Quelle.
- Sauberer Projektstand: P:\GitHub_DeutschZModZ\DeutschZModZ
- ReadyMods ist Build-/PBO-Ausgabe.
- P:\ niemals Backup-Ziel.
- LM Studio/.lmstudio/GGUF nicht automatisch sichern/exportieren.
- Benutzer-Verknuepfung DeutschZ_System_Manager - Verknuepfung.lnk schuetzen.
- Desktop soll nur zwei Elemente zeigen:
  1. DeutschZ - SystemManager
  2. DeutschZ - Vollstaendige Analyse starten
- Im Ordner DeutschZ - SystemManager:
  - Uploadpaket fuer ChatGPT
  - Reports oeffnen
  - Build Wrapper pruefen
- Aktive Mods:
  1. DeutschZ_Core
  2. DeutschZ_ExpansionBridge
  3. DeutschZ_KotHZ
  4. DeutschZ_ConvoyZ
  5. DeutschZ_GroundZero
  6. DeutschZ_CourierZ
  7. DeutschZ_OperationDeutschZ
- Core Pflicht, ExpansionBridge einzige direkte Expansion-Schicht.
- Eventmods keine gegenseitigen Abhaengigkeiten.
- OperationDeutschZ darf spaeter orchestrieren.
- Alle Events ohne Expansion crashfrei.
- Signalstation strikt von KotHZ trennen.
- Green Mountain ist Trader/SafeZone, keine Eventlocation.
- M249-Regel: nur Vanilla M249 und Mag_M249_Box200Rnd blocken, GCGNM249/GCGN_M249 erlauben.
- Build Wrapper: P:\GitHub_DeutschZModZ\DeutschZModZ\tools\build_wrapper
- Git Commit Helper: P:\GitHub_DeutschZModZ\DeutschZModZ\tools\git_commit_helper

"@ | Out-File $memoryFile -Encoding UTF8
    [ordered]@{memory_status="AKTUALISIERT";memory_action_for_chatgpt="NEU_SPEICHERN_WENN_DIESER_STAND_FEHLT_ODER_ABWEICHT";version="DZSM v0.4.8 BUILDWRAPPER-SOURCE-LOCATOR";date=(Get-Date).ToString("s");secrets_included=$false;should_store_if_missing=$true} | ConvertTo-Json | Out-File $statusFile -Encoding UTF8
    if (Test-PathFast $GitHubSafetyDocsRoot) {
        $repoMemory = Join-Path $GitHubSafetyDocsRoot "memory"
        New-Item -ItemType Directory -Path $repoMemory -Force | Out-Null
        Copy-Item $memoryFile (Join-Path $repoMemory "CHATGPT_ERINNERUNG_AKTUELL.md") -Force
        Copy-Item $statusFile (Join-Path $repoMemory "MEMORY_STATUS.json") -Force
    }
    Append-Line $MemoryPackageLogFile "OK Memory erstellt."
}

function Update-GitCommitHelper {
    "DeutschZ System Manager v0.4.8 - Git Commit Helper" | Out-File $GitCommitHelperLogFile -Encoding UTF8
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
    Append-Line $GitCommitHelperLogFile "OK GitCommitHelper erstellt: $GitCommitHelperRoot"
    Append-Line $GitCommitHelperLogFile "OK Commit Message: $(Join-Path $GitCommitHelperRoot "DZSM_GIT_COMMIT_MESSAGE.txt")"
}

function Find-DZSMGitExe {
    try {
        $cmdGit = Get-Command git.exe -ErrorAction SilentlyContinue
        if ($cmdGit -and $cmdGit.Source -and (Test-PathFast $cmdGit.Source)) { return $cmdGit.Source }
    } catch {}
    foreach ($c in @("C:\Program Files\Git\cmd\git.exe","C:\Program Files\Git\bin\git.exe","C:\Program Files (x86)\Git\cmd\git.exe","C:\Program Files (x86)\Git\bin\git.exe")) {
        if (Test-PathFast $c) { return $c }
    }
    try {
        $ghRoot = Join-Path $env:LOCALAPPDATA "GitHubDesktop"
        if (Test-PathFast $ghRoot) {
            $embedded = Get-ChildItem -Path $ghRoot -Filter git.exe -Recurse -File -ErrorAction SilentlyContinue |
                Where-Object { $_.FullName -like "*\resources\app\git\cmd\git.exe" -or $_.FullName -like "*\resources\app\git\mingw64\bin\git.exe" } |
                Sort-Object FullName -Descending | Select-Object -First 1
            if ($embedded -and (Test-PathFast $embedded.FullName)) { return $embedded.FullName }
        }
    } catch {}
    return $null
}

function Invoke-DZSMGit {
    param([string]$GitExe,[string[]]$Arguments)
    if (-not $GitExe -or -not (Test-PathFast $GitExe)) { return @("FEHLER: git.exe wurde nicht gefunden.") }
    try { $output = & $GitExe @Arguments 2>&1; if ($null -eq $output) { return @() }; return @($output) }
    catch { return @("FEHLER bei git $($Arguments -join ' '): $($_.Exception.Message)") }
}

function Update-GitMergeDiagnostics {
    "DeutschZ System Manager v0.4.8 - Git Merge Diagnostics" | Out-File $GitMergeStatusFile -Encoding UTF8
    "Datum: $(Get-Date)" | Out-File $GitMergeStatusFile -Append -Encoding UTF8
    "RepoRoot: $DeutschZRepoRoot" | Out-File $GitMergeStatusFile -Append -Encoding UTF8

    "DeutschZ System Manager v0.4.8 - Git Conflict Files" | Out-File $GitConflictFilesFile -Encoding UTF8
    "DeutschZ System Manager v0.4.8 - Git Conflict Marker Context" | Out-File $GitConflictMarkersFile -Encoding UTF8

@"
# Git Merge Entscheidungshilfe fuer Patrick

main / HEAD / Current Change = lokaler PC-Stand.
origin/main / Incoming Change = GitHub-Stand.

Wenn dein PC-Stand der aktuelle Masterstand sein soll:
- Accept Current Change ist meistens richtig.
- Danach speichern.
- Dann Continue merge.
"@ | Out-File $GitMergeGuideFile -Encoding UTF8

    if (-not (Test-PathFast $DeutschZRepoRoot)) {
        Append-Line $GitMergeStatusFile "FEHLER: RepoRoot fehlt."
        Append-Line $GitConflictFilesFile "FEHLER: RepoRoot fehlt."
        Append-Line $GitConflictMarkersFile "FEHLER: RepoRoot fehlt."
        return
    }
    if (-not (Test-PathFast (Join-Path $DeutschZRepoRoot ".git"))) {
        Append-Line $GitMergeStatusFile "FEHLER: Kein .git Ordner im RepoRoot gefunden."
        Append-Line $GitConflictFilesFile "FEHLER: Kein .git Ordner im RepoRoot gefunden."
        Append-Line $GitConflictMarkersFile "FEHLER: Kein .git Ordner im RepoRoot gefunden."
        Append-Line $GitMergeGuideFile "`nRepoRoot wirkt nicht wie Git-Repository. GitHub Desktop Pfad pruefen."
        return
    }

    $gitExe = Find-DZSMGitExe
    Append-Line $GitMergeStatusFile "GitExe: $gitExe"
    if (-not $gitExe) {
        Append-Line $GitMergeStatusFile "FEHLER: git.exe nicht gefunden. PATH/GitHub Desktop/Git for Windows pruefen."
        Append-Line $GitConflictFilesFile "FEHLER: git.exe nicht gefunden. Keine Konfliktdateiliste moeglich."
        Append-Line $GitConflictMarkersFile "FEHLER: git.exe nicht gefunden. Keine Marker-Kontextanalyse moeglich."
        Append-Line $GitMergeGuideFile "`nGit wurde nicht gefunden. Wenn dein PC-Stand aktuell ist: in GitHub Desktop/VS Code Accept Current Change waehlen."
        return
    }

    Push-Location $DeutschZRepoRoot
    try {
        Append-Line $GitMergeStatusFile "---- git version ----"
        Invoke-DZSMGit $gitExe @("--version") | Out-File $GitMergeStatusFile -Append -Encoding UTF8
        Append-Line $GitMergeStatusFile "---- git branch --show-current ----"
        Invoke-DZSMGit $gitExe @("branch","--show-current") | Out-File $GitMergeStatusFile -Append -Encoding UTF8
        Append-Line $GitMergeStatusFile "---- git status --short --branch ----"
        Invoke-DZSMGit $gitExe @("status","--short","--branch") | Out-File $GitMergeStatusFile -Append -Encoding UTF8
        Append-Line $GitMergeStatusFile "---- git status ----"
        Invoke-DZSMGit $gitExe @("status") | Out-File $GitMergeStatusFile -Append -Encoding UTF8

        $gitDir = Join-Path $DeutschZRepoRoot ".git"
        Append-Line $GitMergeStatusFile "---- Merge State ----"
        foreach ($stateFile in @("MERGE_HEAD","MERGE_MSG","MERGE_MODE","REBASE_HEAD","CHERRY_PICK_HEAD")) {
            $p = Join-Path $gitDir $stateFile
            if (Test-PathFast $p) { Append-Line $GitMergeStatusFile "STATE: $stateFile vorhanden"; try { Get-Content $p | Out-File $GitMergeStatusFile -Append -Encoding UTF8 } catch {} }
            else { Append-Line $GitMergeStatusFile "STATE: $stateFile nicht vorhanden" }
        }

        $unmerged = @(Invoke-DZSMGit $gitExe @("diff","--name-only","--diff-filter=U") | Where-Object { $_ -and $_ -notlike "FEHLER:*" })
        Append-Line $GitMergeStatusFile "---- Unmerged files ----"
        if ($unmerged.Count -eq 0) { Append-Line $GitMergeStatusFile "Keine unmerged/conflicted files laut git diff." } else { $unmerged | Out-File $GitMergeStatusFile -Append -Encoding UTF8 }

        Append-Line $GitConflictFilesFile "---- git ls-files -u ----"
        Invoke-DZSMGit $gitExe @("ls-files","-u") | Out-File $GitConflictFilesFile -Append -Encoding UTF8
        Append-Line $GitConflictFilesFile "---- Unmerged Datei-Liste ----"
        if ($unmerged.Count -gt 0) { foreach ($f in $unmerged) { Append-Line $GitConflictFilesFile "KONFLIKT: $f" } } else { Append-Line $GitConflictFilesFile "Keine Konfliktdateien laut git." }

        if ($unmerged.Count -gt 0) {
            foreach ($f in $unmerged) {
                $full = Join-Path $DeutschZRepoRoot $f
                Append-Line $GitConflictMarkersFile "============================================================"
                Append-Line $GitConflictMarkersFile "DATEI: $f"
                Append-Line $GitConflictMarkersFile "============================================================"
                if (-not (Test-PathFast $full)) { Append-Line $GitConflictMarkersFile "FEHLT lokal: $full"; continue }
                $lines = Get-Content $full -ErrorAction SilentlyContinue
                $markerIndexes = New-Object System.Collections.Generic.List[int]
                for ($i=0; $i -lt $lines.Count; $i++) {
                    if ($lines[$i] -match "^(<<<<<<<|=======|>>>>>>>)") { $markerIndexes.Add($i) }
                }
                if ($markerIndexes.Count -eq 0) { Append-Line $GitConflictMarkersFile "Keine Konfliktmarker im Text gefunden." }
                else {
                    Append-Line $GitConflictMarkersFile "Marker-Anzahl: $($markerIndexes.Count)"
                    foreach ($idx in $markerIndexes) {
                        $start = [Math]::Max(0, $idx - 8)
                        $end = [Math]::Min($lines.Count - 1, $idx + 16)
                        Append-Line $GitConflictMarkersFile "---- Kontext um Zeile $($idx+1) ----"
                        for ($j=$start; $j -le $end; $j++) { ("{0,6}: {1}" -f ($j+1), $lines[$j]) | Out-File $GitConflictMarkersFile -Append -Encoding UTF8 }
                    }
                }
            }
        } else {
            Append-Line $GitConflictMarkersFile "Keine Konfliktdateien laut git."
        }
    } catch {
        Append-Line $GitMergeStatusFile "FEHLER: $($_.Exception.Message)"
    } finally {
        Pop-Location
    }
}


function Update-DeutschZStructureReport {
    "DeutschZ System Manager v0.4.8 - DeutschZ Structure Check" | Out-File $DeutschZFile -Encoding UTF8
    foreach ($p in @($DeutschZRepoRoot,(Join-Path $DeutschZRepoRoot "mods"),(Join-Path $DeutschZRepoRoot "tools"),$BuildWrapperRoot,$GitCommitHelperRoot,$GitHubExportRoot,$GitHubSafetyDocsRoot)) {
        if (Test-PathFast $p) { Append-Line $DeutschZFile "OK: $p" } else { Append-Line $DeutschZFile "FEHLT/OPTIONAL: $p" }
    }

    Append-Line $DeutschZFile ""
    Append-Line $DeutschZFile "---- Mod Source Schnellcheck ----"
    $activeMods = @("DeutschZ_Core","DeutschZ_ExpansionBridge","DeutschZ_KotHZ","DeutschZ_ConvoyZ","DeutschZ_GroundZero","DeutschZ_CourierZ","DeutschZ_OperationDeutschZ")
    $modsRoot = Join-Path $DeutschZRepoRoot "mods"
    if (Test-PathFast $modsRoot) {
        foreach ($m in $activeMods) {
            $mp = Join-Path $modsRoot $m
            if (Test-PathFast $mp) { Append-Line $DeutschZFile "OK Mod im RepoRoot\mods: $m" }
            else { Append-Line $DeutschZFile "FEHLT Mod im RepoRoot\mods: $m" }
        }
    } else {
        Append-Line $DeutschZFile "KRITISCH FUER BUILD: Der Ordner RepoRoot\mods fehlt."
        Append-Line $DeutschZFile "Build Wrapper darf keinen echten Build starten, bis die Modquelle eindeutig ist."
    }
}


function Update-MainReport {
    "DeutschZ System Manager v0.4.8 BUILDWRAPPER-SOURCE-LOCATOR - Inventurbericht" | Out-File $ReportFile -Encoding UTF8
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
        "Desktop: DeutschZ - SystemManager + DeutschZ - Vollstaendige Analyse starten",
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
    "DeutschZ System Manager v0.4.8 - Desktop Namen / Oberordner" | Out-File $ShortcutLogFile -Encoding UTF8
    $desktop = [Environment]::GetFolderPath("Desktop")
    $desktopFolder = Join-Path $desktop "DeutschZ - SystemManager"
    New-Item -ItemType Directory -Path $desktopFolder -Force | Out-Null
    Append-Line $ShortcutLogFile "Desktop: $desktop"
    Append-Line $ShortcutLogFile "Oberordner: $desktopFolder"
    Append-Line $ShortcutLogFile "Regel: Auf Desktop bleiben nur Oberordner und Start-Verknuepfung sichtbar."
    Append-Line $ShortcutLogFile "Start-Link Name: DeutschZ - Vollstaendige Analyse starten.lnk"

    $desktopAutoLinks = @("DeutschZ System Manager - Start.lnk","DeutschZ - Vollstaendige Analyse starten.lnk","DeutschZ - Vollständige Analyse starten.lnk","DeutschZ System Manager - Upload Reports.lnk","DeutschZ System Manager - Reports.lnk","DeutschZ Build Wrapper - Check.lnk","DeutschZ System Manager - Script PS1.lnk","DZSM - Start.lnk","DZSM - Script PS1.lnk","DZSM - Upload Reports.lnk")
    foreach ($l in $desktopAutoLinks) {
        $p = Join-Path $desktop $l
        if (Test-PathFast $p) { Remove-Item $p -Force -ErrorAction SilentlyContinue; Append-Line $ShortcutLogFile "OK Desktop Auto-Link entfernt/ersetzt: $p" }
    }

    $folderAutoLinks = @("Upload Reports.lnk","Reports.lnk","Build Wrapper - Check.lnk","Uploadpaket fuer ChatGPT.lnk","Uploadpaket für ChatGPT.lnk","Reports oeffnen.lnk","Reports öffnen.lnk","Build Wrapper pruefen.lnk","Build Wrapper prüfen.lnk","Script PS1 - Intern.lnk")
    foreach ($l in $folderAutoLinks) {
        $p = Join-Path $desktopFolder $l
        if (Test-PathFast $p) { Remove-Item $p -Force -ErrorAction SilentlyContinue; Append-Line $ShortcutLogFile "OK Ordner Auto-Link entfernt/ersetzt: $p" }
    }

    $shell = New-Object -ComObject WScript.Shell
    $iconStart = Join-Path $PSScriptRoot "icons\DZSM_Start_DarkGlass_Green_v047.ico"
    $iconFolder = Join-Path $PSScriptRoot "icons\DZSM_Folder_DarkGlass_Green_v047.ico"
    $iconUpload = Join-Path $PSScriptRoot "icons\DZSM_Upload_DarkGlass_Green_v047.ico"
    $iconReports = Join-Path $PSScriptRoot "icons\DZSM_Reports_DarkGlass_Green_v047.ico"
    $iconBuild = Join-Path $PSScriptRoot "icons\DZSM_Build_DarkGlass_Green_v047.ico"

    $startTarget = Join-Path $PSScriptRoot "Start_DZSM_v0_4_8_BUILDWRAPPER_SOURCE_LOCATOR.bat"
    if (Test-PathFast $startTarget) {
        $s = $shell.CreateShortcut((Join-Path $desktop "DeutschZ - Vollstaendige Analyse starten.lnk"))
        $s.TargetPath = $startTarget
        $s.WorkingDirectory = $PSScriptRoot
        $s.Description = "Startet die vollstaendige DeutschZ System Manager Analyse"
        if (Test-PathFast $iconStart) { $s.IconLocation = $iconStart }
        $s.Save()
        Append-Line $ShortcutLogFile "OK Desktop Start-Link erstellt."
    }

    # Ordnericon robust: Attribute entfernen, desktop.ini neu schreiben, Attribute wieder setzen
    try {
        $desktopIni = Join-Path $desktopFolder "desktop.ini"
        if (Test-PathFast $desktopIni) {
            cmd.exe /c "attrib -h -s -r ""$desktopIni""" | Out-Null
            Remove-Item $desktopIni -Force -ErrorAction SilentlyContinue
        }
        if (Test-PathFast $iconFolder) {
@"
[.ShellClassInfo]
IconResource=$iconFolder,0
IconFile=$iconFolder
IconIndex=0
InfoTip=DeutschZ System Manager Werkzeuge
"@ | Set-Content -Path $desktopIni -Encoding ASCII -Force
            cmd.exe /c "attrib +h +s ""$desktopIni""" | Out-Null
            cmd.exe /c "attrib +r ""$desktopFolder""" | Out-Null
            Append-Line $ShortcutLogFile "OK Oberordner Icon gesetzt."
        }
    } catch {
        Append-Line $ShortcutLogFile "WARNUNG Oberordner Icon: $($_.Exception.Message)"
    }

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

function Write-Next {
@"
DeutschZ System Manager - Naechste Schritte
==========================================
Aktuelle Version: v0.4.8 BUILDWRAPPER-SOURCE-LOCATOR

Bitte ab jetzt hochladen:
$UploadPackageRoot\DZSM_UPLOAD_PACKAGE.zip

Dieses Paket muss enthalten:
- 27_BUILD_WRAPPER_LOG.txt
- 28_MEMORY_PACKAGE_LOG.txt
- 29_GIT_COMMIT_HELPER_LOG.txt
- 30_GIT_MERGE_STATUS.txt
- 31_GIT_CONFLICT_FILES.txt
- 32_GIT_CONFLICT_MARKERS_CONTEXT.txt
- 33_GIT_MERGE_DECISION_GUIDE.md
- CHATGPT_ERINNERUNG_AKTUELL.md
- MEMORY_STATUS.json
- DZSM_GIT_COMMIT_MESSAGE.txt

Desktop soll zeigen:
- DeutschZ - SystemManager
- DeutschZ - Vollstaendige Analyse starten

Git Commit Helper:
$GitCommitHelperRoot\GIT_COMMIT_DZSM_CHECK_AND_COMMIT.bat
"@ | Out-File $NextFile -Encoding UTF8
}

function Update-UploadPackage {
    "DeutschZ System Manager v0.4.8 - Upload-Paket FINAL" | Out-File $UploadPackageLogFile -Encoding UTF8
    New-Item -ItemType Directory -Path $UploadPackageRoot -Force | Out-Null
    Get-ChildItem -Path $UploadPackageRoot -File -ErrorAction SilentlyContinue | Remove-Item -Force -ErrorAction SilentlyContinue

    $files = @("00_ZUSAMMENFASSUNG.txt","11_DEUTSCHZ_STRUCTURE_CHECK.txt","16_DZSM_SELF_CLEANUP.txt","17_SAFE_AUTO_BACKUP_LOG.txt","18_DZSM_STANDARD_STRUCTURE.txt","19_GITHUB_EXPORT_LOG.txt","21_GITHUB_SAFETY_DOCS_LOG.txt","22_P_ROOT_WORKDRIVE_NOTES.txt","23_LMSTUDIO_MODEL_POLICY.txt","24_DESKTOP_SHORTCUTS_LOG.txt","25_BUGREPORT_WORKSPACE_LOG.txt","26_UPLOAD_PACKAGE_LOG.txt","27_BUILD_WRAPPER_LOG.txt","28_MEMORY_PACKAGE_LOG.txt","29_GIT_COMMIT_HELPER_LOG.txt","30_GIT_MERGE_STATUS.txt","31_GIT_CONFLICT_FILES.txt","32_GIT_CONFLICT_MARKERS_CONTEXT.txt","33_GIT_MERGE_DECISION_GUIDE.md","99_NAECHSTE_SCHRITTE.txt")
    foreach ($fn in $files) {
        $src=Join-Path $ReportsRoot $fn
        if (Test-PathFast $src) { Copy-Item $src (Join-Path $UploadPackageRoot $fn) -Force; Append-Line $UploadPackageLogFile "OK kopiert: $fn" }
        else { Append-Line $UploadPackageLogFile "FEHLT: $fn" }
    }
    foreach ($extra in @((Join-Path $MemoryRoot "CHATGPT_ERINNERUNG_AKTUELL.md"),(Join-Path $MemoryRoot "MEMORY_STATUS.json"),(Join-Path $GitCommitHelperRoot "DZSM_GIT_COMMIT_MESSAGE.txt"))) {
        if (Test-PathFast $extra) { Copy-Item $extra (Join-Path $UploadPackageRoot (Split-Path $extra -Leaf)) -Force; Append-Line $UploadPackageLogFile "OK kopiert: $(Split-Path $extra -Leaf)" }
        else { Append-Line $UploadPackageLogFile "FEHLT: $extra" }
    }

    "Uploadpaket fuer ChatGPT. Diesen Ordner oder DZSM_UPLOAD_PACKAGE.zip hochladen." | Out-File (Join-Path $UploadPackageRoot "README_UPLOAD_HINWEIS.txt") -Encoding UTF8

    # Am Ende den finalen Upload-Log nochmal aktualisiert kopieren
    Copy-Item $UploadPackageLogFile (Join-Path $UploadPackageRoot "26_UPLOAD_PACKAGE_LOG.txt") -Force -ErrorAction SilentlyContinue

    $zip = Join-Path $UploadPackageRoot "DZSM_UPLOAD_PACKAGE.zip"
    if (Test-PathFast $zip) { Remove-Item $zip -Force }
    Compress-Archive -Path (Join-Path $UploadPackageRoot "*") -DestinationPath $zip -Force
    Append-Line $UploadPackageLogFile "OK ZIP erstellt: $zip"
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
Update-GitMergeDiagnostics
Update-DeutschZStructureReport
Update-MainReport
Write-Next
Update-Shortcuts
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
