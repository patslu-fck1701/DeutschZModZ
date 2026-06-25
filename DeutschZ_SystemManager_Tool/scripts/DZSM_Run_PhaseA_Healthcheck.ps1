Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$ScriptRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
. (Join-Path $ScriptRoot 'lib\DZSM_PathTools.ps1')

$DzsmRoot = Resolve-Path (Join-Path $ScriptRoot '..')
$Config = Read-DZSMPathsConfig -DzsmRoot $DzsmRoot.Path
$Findings = New-Object System.Collections.Generic.List[object]
$ReportPaths = New-DZSMReportPaths -Config $Config

Add-DZSMFinding $Findings 'INFO' 'Scope' 'Phase A focused healthcheck started.' $DzsmRoot.Path

# Run the same path checks first.
Test-DZSMPathReadable $Findings 'LiveSettingsRoot' $Config.LiveSettingsRoot $true | Out-Null
Test-DZSMPathReadable $Findings 'ReadyModsPath' $Config.ReadyModsPath $true | Out-Null
Test-DZSMPathReadable $Findings 'SourceFilesPath' $Config.SourceFilesPath $true | Out-Null

foreach ($mod in $Config.PhaseAMods) {
    Test-DZSMReadyMod $Findings $Config.ReadyModsPath $mod
}

# Detect latest server logs if present below profiles.
$profilesCandidates = @(
    (Join-Path $Config.LiveSettingsRoot 'profiles'),
    (Join-Path $Config.LiveSettingsRoot 'Profiles'),
    (Join-Path $Config.LiveSettingsRoot 'profile'),
    (Join-Path $Config.LiveSettingsRoot 'Profile')
)
$profiles = $profilesCandidates | Where-Object { Test-Path -LiteralPath $_ } | Select-Object -First 1
if ($profiles) {
    Add-DZSMFinding $Findings 'OK' 'Logs' 'Profile/log directory candidate exists.' $profiles
    $scriptLog = Get-ChildItem -LiteralPath $profiles -Filter 'script_*.log' -File -ErrorAction SilentlyContinue | Sort-Object LastWriteTime -Descending | Select-Object -First 1
    if ($scriptLog) {
        $text = Get-Content -LiteralPath $scriptLog.FullName -Raw -ErrorAction SilentlyContinue
        foreach ($needle in @('DeutschZ_Core','DeutschZ_ExpansionBridge','DeutschZ_KotHZ','DeutschZ_ConvoyZ')) {
            if ($text -like "*$needle*") { Add-DZSMFinding $Findings 'OK' 'Logs' "Latest script log contains $needle" $scriptLog.FullName }
            else { Add-DZSMFinding $Findings 'WARN' 'Logs' "Latest script log does not contain $needle" $scriptLog.FullName }
        }
        if ($text -like '*SCRIPT    (E)*' -or $text -like '*SCRIPT       : Error*' -or $text -like "*Can't compile*") {
            Add-DZSMFinding $Findings 'ERROR' 'Logs' 'Latest script log contains possible script error text.' $scriptLog.FullName
        } else {
            Add-DZSMFinding $Findings 'OK' 'Logs' 'No obvious script compile error marker found in latest script log.' $scriptLog.FullName
        }
    } else {
        Add-DZSMFinding $Findings 'WARN' 'Logs' 'No script_*.log found in profile directory.' $profiles
    }
} else {
    Add-DZSMFinding $Findings 'INFO' 'Logs' 'No profile/log directory found under LiveSettingsRoot; upload logs manually for analysis.' $Config.LiveSettingsRoot
}

$meta = @{
    Hostname = $env:COMPUTERNAME
    User = $env:USERNAME
    Pwd = (Get-Location).Path
    Mode = 'PhaseAHealthcheck'
}
$summary = Write-DZSMReports -Config $Config -ReportPaths $ReportPaths -Findings $Findings -Meta $meta

Write-Host ''
Write-Host 'DZSM FIX25 PHASE A HEALTHCHECK DONE'
Write-Host ('Upload ZIP : ' + $ReportPaths.UploadZip)
Write-Host ('Counts     : OK={0} WARN={1} ERROR={2} INFO={3}' -f $summary.Counts.OK,$summary.Counts.WARN,$summary.Counts.ERROR,$summary.Counts.INFO)
if ($summary.Counts.ERROR -gt 0) { exit 2 }
if ($summary.Counts.WARN -gt 0) { exit 1 }
exit 0
