@echo off
chcp 65001 >nul
title DeutschZ System Manager v0.4.1 MEMORY-COMMIT-PACKAGE
echo ============================================================
echo DeutschZ System Manager v0.4.1 MEMORY-COMMIT-PACKAGE
echo P:\Root = DayZ Tools WorkDrive/Vanilla + Legacy
echo Sauberer Projektstand = P:\GitHub_DeutschZModZ\DeutschZModZ
echo Keine Loeschung, kein Spiegeln, kein OC, Memory + Commit + Build Wrapper
echo ============================================================
echo.
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0DZSM_v0_4_1_Memory_Commit_Package.ps1"
exit /b 0
