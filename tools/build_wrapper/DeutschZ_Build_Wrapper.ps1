param(
    [switch]$Build,
    [switch]$DryRun,
    [switch]$Force
)

$ErrorActionPreference = "Continue"

$RepoRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ"
$ModsRoot = Join-Path $RepoRoot "mods"
$ReadyModsRoot = "P:\ReadyMods"
$BuildWrapperRoot = Join-Path $RepoRoot "tools\build_wrapper"
$LogRoot = Join-Path $BuildWrapperRoot "logs"
$ConfigPath = Join-Path $BuildWrapperRoot "BUILD_CONFIG.json"
$TimeStamp = Get-Date -Format "yyyy-MM-dd_HH-mm-ss"
$LogFile = Join-Path $LogRoot ("BUILD_WRAPPER_" + $TimeStamp + ".log")

New-Item -ItemType Directory -Path $LogRoot -Force | Out-Null

function Write-BWLog {
    param([string]$Text)
    $line = "[" + (Get-Date -Format "HH:mm:ss") + "] " + $Text
    $line | Out-File -FilePath $LogFile -Append -Encoding UTF8
    Write-Host $line
}

function Test-PathSafe {
    param([string]$Path)
    try { return (Test-Path $Path) } catch { return $false }
}

function Find-AddonBuilder {
    $candidates = @(
        "F:\programme\steamapps\common\DayZ Tools\Bin\AddonBuilder\AddonBuilder.exe",
        "F:\Programme\steamapps\common\DayZ Tools\Bin\AddonBuilder\AddonBuilder.exe",
        "C:\Program Files (x86)\Steam\steamapps\common\DayZ Tools\Bin\AddonBuilder\AddonBuilder.exe",
        "C:\Program Files\Steam\steamapps\common\DayZ Tools\Bin\AddonBuilder\AddonBuilder.exe"
    )
    foreach ($c in $candidates) {
        if (Test-PathSafe $c) { return $c }
    }
    return $null
}

function Get-BuildConfig {
    if (Test-PathSafe $ConfigPath) {
        try {
            return (Get-Content $ConfigPath -Raw -Encoding UTF8 | ConvertFrom-Json)
        } catch {
            Write-BWLog "WARNUNG: BUILD_CONFIG.json konnte nicht gelesen werden: $($_.Exception.Message)"
        }
    }
    return $null
}

Write-BWLog "DeutschZ Build Wrapper gestartet."
Write-BWLog "RepoRoot: $RepoRoot"
Write-BWLog "ModsRoot: $ModsRoot"
Write-BWLog "ReadyModsRoot: $ReadyModsRoot"
Write-BWLog "Modus: Build=$Build DryRun=$DryRun Force=$Force"

$activeMods = @(
    "DeutschZ_Core",
    "DeutschZ_ExpansionBridge",
    "DeutschZ_KotHZ",
    "DeutschZ_ConvoyZ",
    "DeutschZ_GroundZero",
    "DeutschZ_CourierZ",
    "DeutschZ_OperationDeutschZ"
)

$ok = $true

Write-BWLog "Pruefe P:\ readiness..."
if (-not (Test-PathSafe "P:\")) {
    Write-BWLog "FEHLER: P:\ ist nicht aktiv."
    $ok = $false
}

$requiredPDriveItems = @("bin","Core","DZ","scripts","system")
foreach ($item in $requiredPDriveItems) {
    $p = Join-Path "P:\" $item
    if (Test-PathSafe $p) { Write-BWLog "OK P-Drive/DayZ Tools: $p" }
    else { Write-BWLog "WARNUNG/OPTIONAL: P-Drive Element fehlt: $p" }
}

if (-not (Test-PathSafe $RepoRoot)) {
    Write-BWLog "FEHLER: RepoRoot fehlt: $RepoRoot"
    $ok = $false
}
if (-not (Test-PathSafe $ModsRoot)) {
    Write-BWLog "FEHLER: ModsRoot fehlt: $ModsRoot"
    $ok = $false
}
if (-not (Test-PathSafe $ReadyModsRoot)) {
    Write-BWLog "WARNUNG: ReadyModsRoot fehlt: $ReadyModsRoot"
}

Write-BWLog "Pruefe aktive Mods in Reihenfolge..."
foreach ($mod in $activeMods) {
    $modPath = Join-Path $ModsRoot $mod
    if (Test-PathSafe $modPath) {
        Write-BWLog "OK Mod vorhanden: $mod"
        foreach ($rel in @("mod.cpp","README.md","CHANGELOG.md")) {
            $fp = Join-Path $modPath $rel
            if (Test-PathSafe $fp) { Write-BWLog "  OK: $rel" }
            else { Write-BWLog "  WARNUNG fehlt/optional: $rel" }
        }
    } else {
        Write-BWLog "FEHLT Mod: $mod"
        if ($mod -ne "DeutschZ_OperationDeutschZ") { $ok = $false }
    }
}

$addonBuilder = Find-AddonBuilder
if ($addonBuilder) {
    Write-BWLog "OK AddonBuilder gefunden: $addonBuilder"
} else {
    Write-BWLog "WARNUNG: AddonBuilder.exe nicht gefunden. CheckOnly funktioniert trotzdem."
}

$config = Get-BuildConfig
$allowRealBuild = $false
if ($config -and $config.allow_real_build -eq $true) {
    $allowRealBuild = $true
}

Write-BWLog "BuildConfig allow_real_build=$allowRealBuild"
Write-BWLog "Workshop-Regel: Workshopdateien werden vom Build Wrapper nicht geaendert."
Write-BWLog "P-Root-Regel: P:\Root wird nicht aufgeraeumt, nicht exportiert, nicht geloescht."
Write-BWLog "ReadyMods-Regel: ReadyMods ist Build-/PBO-Ausgabe."

if (-not $ok) {
    Write-BWLog "ABBRUCH: Pflichtpruefung fehlgeschlagen. Kein Build."
    exit 2
}

if (-not $Build) {
    Write-BWLog "CHECK-ONLY abgeschlossen. Kein Build ausgefuehrt."
    Write-BWLog "Zum echten Build spaeter BUILD_CONFIG.json bewusst freischalten und -Build verwenden."
    exit 0
}

if (-not $allowRealBuild -and -not $Force) {
    Write-BWLog "BUILD BLOCKIERT: BUILD_CONFIG.json erlaubt allow_real_build nicht."
    Write-BWLog "Sicherheitsregel: Kein echter Build ohne bewusste Freigabe."
    exit 3
}

if (-not $addonBuilder) {
    Write-BWLog "BUILD BLOCKIERT: AddonBuilder.exe nicht gefunden."
    exit 4
}

$stagingRoot = Join-Path $ReadyModsRoot ("_DZSM_BUILD_STAGING\" + $TimeStamp)
New-Item -ItemType Directory -Path $stagingRoot -Force | Out-Null
Write-BWLog "Build-Staging: $stagingRoot"

Write-BWLog "ECHTER BUILD-MODUS ist vorbereitet, aber konservativ."
Write-BWLog "Naechster Implementierungsschritt: pro Mod genaue PBO-Source-Unterordner aus BUILD_CONFIG.json verwenden."
Write-BWLog "Noch keine PBOs gebaut, um Mischstaende und falsche Source-Erkennung zu vermeiden."
exit 0
