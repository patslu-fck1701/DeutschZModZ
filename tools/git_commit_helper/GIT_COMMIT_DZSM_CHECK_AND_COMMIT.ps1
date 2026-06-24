$ErrorActionPreference = "Continue"

$RepoRoot = "P:\GitHub_DeutschZModZ\DeutschZModZ"
$HelperRoot = Join-Path $RepoRoot "tools\git_commit_helper"
$CommitMessageFile = Join-Path $HelperRoot "DZSM_GIT_COMMIT_MESSAGE.txt"

Write-Host "DeutschZ Git Commit Helper"
Write-Host "Repo: $RepoRoot"
Write-Host ""

if (-not (Test-Path $RepoRoot)) {
    Write-Host "FEHLER: RepoRoot fehlt."
    exit 2
}

Set-Location $RepoRoot

Write-Host "Git Version:"
git --version

Write-Host ""
Write-Host "Git Status:"
git status --short

Write-Host ""
Write-Host "Commit Message:"
Get-Content $CommitMessageFile

Write-Host ""
Write-Host "Sicherheitsregel:"
Write-Host "- Es wird NICHT automatisch gepusht."
Write-Host "- Bitte pruefen, ob keine privaten Reports/Backups/Secrets im Commit landen."
Write-Host ""

$answer = Read-Host "Jetzt alles git adden und committen? (JA zum Ausfuehren)"
if ($answer -ne "JA") {
    Write-Host "Abgebrochen. Kein Commit."
    exit 0
}

git add DeutschZ_SystemManager_Tool
git add DeutschZ_SystemManager_Tool_Dokumentation
git add tools\build_wrapper
git add tools\git_commit_helper

git status --short

$answer2 = Read-Host "Commit mit obiger Message erstellen? (JA zum Commit)"
if ($answer2 -ne "JA") {
    Write-Host "Abgebrochen nach git add. Kein Commit."
    exit 0
}

git commit -F $CommitMessageFile
Write-Host ""
Write-Host "Commit fertig. Push bitte manuell ausfuehren, wenn alles passt:"
Write-Host "git push"
pause
