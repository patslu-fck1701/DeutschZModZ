@echo off
chcp 65001 >nul
title DeutschZ Build Wrapper - CheckOnly
echo ============================================================
echo DeutschZ Build Wrapper - CheckOnly
echo Repo: P:\GitHub_DeutschZModZ\DeutschZModZ
echo Keine PBOs bauen, nur Bereitschaft pruefen.
echo ============================================================
echo.
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0DeutschZ_Build_Wrapper.ps1"
pause
