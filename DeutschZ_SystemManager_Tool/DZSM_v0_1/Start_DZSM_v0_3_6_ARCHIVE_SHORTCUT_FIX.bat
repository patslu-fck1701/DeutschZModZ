@echo off
chcp 65001 >nul
title DeutschZ System Manager v0.3.6 ARCHIVE-SHORTCUT-FIX
echo ============================================================
echo DeutschZ System Manager v0.3.6 ARCHIVE-SHORTCUT-FIX
echo P:\Root = DayZ Tools WorkDrive/Vanilla + Legacy
echo Sauberer Projektstand = P:\GitHub_DeutschZModZ\DeutschZModZ
echo Keine Loeschung, kein Spiegeln, kein OC, Archiv-Fix + Desktop-Links
echo ============================================================
echo.
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0DZSM_v0_3_6_Archive_Shortcut_Fix.ps1"
exit /b 0
