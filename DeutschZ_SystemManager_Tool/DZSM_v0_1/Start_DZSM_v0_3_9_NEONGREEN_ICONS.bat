@echo off
chcp 65001 >nul
title DeutschZ System Manager v0.3.9 NEONGREEN-ICONS
echo ============================================================
echo DeutschZ System Manager v0.3.9 NEONGREEN-ICONS
echo P:\Root = DayZ Tools WorkDrive/Vanilla + Legacy
echo Sauberer Projektstand = P:\GitHub_DeutschZModZ\DeutschZModZ
echo Keine Loeschung, kein Spiegeln, kein OC, Upload-Paket + NeonGreen Icons
echo ============================================================
echo.
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0DZSM_v0_3_9_NeonGreen_Icons.ps1"
exit /b 0
