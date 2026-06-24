@echo off
chcp 65001 >nul
title DeutschZ System Manager v0.4.6 DESKTOP-NAMES-CLEANUP
echo ============================================================
echo DeutschZ System Manager v0.4.6 DESKTOP-NAMES-CLEANUP
echo Desktop Namen + Git Diagnose
echo ============================================================
echo.
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0DZSM_v0_4_6_Desktop_Names_Cleanup.ps1"
exit /b 0
