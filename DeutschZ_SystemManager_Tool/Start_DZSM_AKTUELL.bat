@echo off
chcp 65001 >nul
title DeutschZ System Manager AKTUELL - v0.6.6 FIX 9
color 0A
echo ============================================================
echo DeutschZ System Manager AKTUELL - v0.6.6 FIX 9
echo ============================================================
echo.
set "PS1=
D:\DeutschZ_System_Manager\DZSM_v0_1\DZSM_v0_6_6_FULL_ANALYSIS_FIX_10_KEY_CLOSE_UPLOAD_ONLY.ps1
"
if not exist "%PS1%" (
    color 0C
    echo FEHLER: PS1 fehlt: %PS1%
    echo Fenster bleibt offen. Taste druecken zum Beenden.
    pause >nul
    exit /b 1
)
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PS1%"
exit /b %ERRORLEVEL%
