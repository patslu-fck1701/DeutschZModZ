@echo off
chcp 65001 >nul
title DeutschZ Git Commit Helper
echo ============================================================
echo DeutschZ Git Commit Helper
echo Repo: P:\GitHub_DeutschZModZ\DeutschZModZ
echo Kein automatischer Push.
echo ============================================================
echo.
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0GIT_COMMIT_DZSM_CHECK_AND_COMMIT.ps1"
