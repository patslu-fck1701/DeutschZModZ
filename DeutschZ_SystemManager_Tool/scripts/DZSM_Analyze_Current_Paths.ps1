Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$ScriptRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
. (Join-Path $ScriptRoot 'lib\DZSM_PathTools.ps1')

$DzsmRoot = Resolve-Path (Join-Path $ScriptRoot '..')
$Config = Read-DZSMPathsConfig -DzsmRoot $DzsmRoot.Path
$Findings = New-Object System.Collections.Generic.List[object]
$ReportPaths = New-DZSMReportPaths -Config $Config

Add-DZSMFinding $Findings 'INFO' 'Scope' 'FIX25 path analysis started.' $DzsmRoot.Path
Add-DZSMFinding $Findings 'INFO' 'Policy' 'No Git, no build, no PBO pack, no Workshop upload.'

Test-DZSMPathReadable $Findings 'LiveSettingsRoot' $Config.LiveSettingsRoot $true | Out-Null
Test-DZSMPathReadable $Findings 'ReadyModsPath' $Config.ReadyModsPath $true | Out-Null
Test-DZSMPathReadable $Findings 'SourceFilesPath' $Config.SourceFilesPath $true | Out-Null

$modlistPath = Join-Path $DzsmRoot.Path $Config.PhaseAModListFile
if (Test-Path -LiteralPath $modlistPath) {
    $modline = (Get-Content -LiteralPath $modlistPath -Raw -Encoding UTF8).Trim()
    Test-DZSMModline $Findings $modline
} else {
    Add-DZSMFinding $Findings 'ERROR' 'Modlist' 'PhaseA modlist file missing.' $modlistPath
}

foreach ($mod in $Config.PhaseAMods) {
    Test-DZSMReadyMod $Findings $Config.ReadyModsPath $mod
    Test-DZSMSourceMod $Findings $Config.SourceFilesPath $mod $Config.ForbiddenLegacyNames
}

foreach ($later in $Config.KnownLaterSources) {
    $path = Join-Path $Config.SourceFilesPath $later
    if (Test-Path -LiteralPath $path) {
        Add-DZSMFinding $Findings 'INFO' 'LaterSources' "Later source present but not Phase A active: $later" $path
    } else {
        Add-DZSMFinding $Findings 'INFO' 'LaterSources' "Later source not present or not checked: $later" $path
    }
}

$mfp = Join-Path $Config.LiveSettingsRoot 'mpmissions\dayzOffline.chernarusplus\expansion_ce\types_MFP_Food.xml'
if (Test-Path -LiteralPath $mfp) {
    Add-DZSMFinding $Findings 'OK' 'MFP' 'MFP food types file exists at expected mission path.' $mfp
} else {
    Add-DZSMFinding $Findings 'WARN' 'MFP' 'MFP food types file not found at expected mission path. Ignore only if cfgeconomycore no longer references it.' $mfp
}

$meta = @{
    Hostname = $env:COMPUTERNAME
    User = $env:USERNAME
    Pwd = (Get-Location).Path
    ReadyModsPath = $Config.ReadyModsPath
    SourceFilesPath = $Config.SourceFilesPath
    LiveSettingsRoot = $Config.LiveSettingsRoot
}
$summary = Write-DZSMReports -Config $Config -ReportPaths $ReportPaths -Findings $Findings -Meta $meta

Write-Host ''
Write-Host 'DZSM FIX25 PATH ANALYSIS DONE'
Write-Host ('Report TXT : ' + $ReportPaths.ReportTxt)
Write-Host ('Report JSON: ' + $ReportPaths.ReportJson)
Write-Host ('Upload ZIP : ' + $ReportPaths.UploadZip)
Write-Host ('Counts     : OK={0} WARN={1} ERROR={2} INFO={3}' -f $summary.Counts.OK,$summary.Counts.WARN,$summary.Counts.ERROR,$summary.Counts.INFO)

if ($summary.Counts.ERROR -gt 0) {
    Write-Host 'RESULT: ERROR - fix required before trusting paths.' -ForegroundColor Red
    exit 2
}
if ($summary.Counts.WARN -gt 0) {
    Write-Host 'RESULT: WARN - usable, but check warnings.' -ForegroundColor Yellow
    exit 1
}
Write-Host 'RESULT: OK - paths and Phase A layout look good.' -ForegroundColor Green
exit 0
