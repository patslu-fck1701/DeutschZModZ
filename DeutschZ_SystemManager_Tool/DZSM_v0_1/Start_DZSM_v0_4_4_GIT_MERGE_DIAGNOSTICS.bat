@echo off
chcp 65001 >nul
title DeutschZ System Manager v0.4.4 GIT-MERGE-DIAGNOSTICS
echo ============================================================
echo DeutschZ System Manager v0.4.4 GIT-MERGE-DIAGNOSTICS
echo Git Merge Diagnose + Final Uploadpaket
echo ============================================================
echo.
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0DZSM_v0_4_4_Git_Merge_Diagnostics.ps1"
exit /b 0
