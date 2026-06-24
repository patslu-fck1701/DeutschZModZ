$RepoRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ"
$HelperRoot = Join-Path $RepoRoot "tools\git_commit_helper"
$CommitMessageFile = Join-Path $HelperRoot "DZSM_GIT_COMMIT_MESSAGE.txt"
Set-Location $RepoRoot
git status --short
Get-Content $CommitMessageFile
$a = Read-Host "Jetzt git add + commit? (JA)"
if ($a -ne "JA") { exit 0 }
git add DeutschZ_SystemManager_Tool DeutschZ_SystemManager_Tool_Dokumentation tools\build_wrapper tools\git_commit_helper
git status --short
$b = Read-Host "Commit erstellen? (JA)"
if ($b -ne "JA") { exit 0 }
git commit -F $CommitMessageFile
Write-Host "Commit fertig. Push manuell: git push"
pause
