@echo off
chcp 65001 >nul
title DeutschZ System Manager v0.4.8 BUILDWRAPPER-SOURCE-LOCATOR
echo ============================================================
echo DeutschZ System Manager v0.4.8 BUILDWRAPPER-SOURCE-LOCATOR
echo BuildWrapper Source Locator + Uploadpaket
echo ============================================================
echo.
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0DZSM_v0_4_8_BuildWrapper_Source_Locator.ps1"
exit /b 0
