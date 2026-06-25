@echo off
setlocal EnableExtensions EnableDelayedExpansion
chcp 65001 >nul
title DeutschZ System Manager - DZSM v0.7.9

set "ROOT=D:\DeutschZ_System_Manager"
set "TOOLDIR=%ROOT%\DZSM_v0_1"
set "ARCHIVE=%TOOLDIR%\_archive_old_versions\archive_%DATE:~-4%-%DATE:~3,2%-%DATE:~0,2%_%TIME:~0,2%-%TIME:~3,2%-%TIME:~6,2%"
set "ARCHIVE=%ARCHIVE: =0%"
set "PS1NAME=DZSM_v_0_7_9.ps1"
set "BATNAME=DZSM_v_0_7_9.bat"
set "PS1=%TOOLDIR%\%PS1NAME%"

if not exist "%ROOT%" mkdir "%ROOT%" >nul 2>nul
if not exist "%TOOLDIR%" mkdir "%TOOLDIR%" >nul 2>nul
if not exist "%TOOLDIR%\_archive_old_versions" mkdir "%TOOLDIR%\_archive_old_versions" >nul 2>nul
if not exist "%ARCHIVE%" mkdir "%ARCHIVE%" >nul 2>nul

if not exist "%~dp0%PS1NAME%" (
  echo FEHLER: %PS1NAME% liegt nicht neben %BATNAME%.
  echo ZIP komplett entpacken und dann %BATNAME% starten.
  echo.
  pause
  exit /b 1
)

REM Alles Alte im Toolordner archivieren, aber Systemordner und lokale Settings behalten.
for /D %%D in ("%TOOLDIR%\*") do (
  if /I not "%%~nxD"=="_archive_old_versions" if /I not "%%~nxD"=="icons" if /I not "%%~nxD"=="STANDARD_TYPES_BASELINE" if /I not "%%~nxD"=="ServerToolSettings" (
    move /Y "%%~fD" "%ARCHIVE%\" >nul 2>nul
  )
)
for %%F in ("%TOOLDIR%\*") do (
  if /I not "%%~nxF"=="%BATNAME%" if /I not "%%~nxF"=="%PS1NAME%" if /I not "%%~nxF"=="DZSM_Config.json" if /I not "%%~nxF"=="VERSION.txt" if /I not "%%~nxF"=="README_START.txt" if /I not "%%~nxF"=="PATCH_NOTES_DZSM_v_0_7_9.md" (
    move /Y "%%~fF" "%ARCHIVE%\" >nul 2>nul
  )
)

if /I not "%~dp0%PS1NAME%"=="%TOOLDIR%\%PS1NAME%" copy /Y "%~dp0%PS1NAME%" "%TOOLDIR%\%PS1NAME%" >nul
if /I not "%~f0"=="%TOOLDIR%\%BATNAME%" copy /Y "%~dp0%BATNAME%" "%TOOLDIR%\%BATNAME%" >nul
if exist "%~dp0DZSM_Config.json" copy /Y "%~dp0DZSM_Config.json" "%TOOLDIR%\DZSM_Config.json" >nul
if exist "%~dp0VERSION.txt" copy /Y "%~dp0VERSION.txt" "%TOOLDIR%\VERSION.txt" >nul
if exist "%~dp0README_START.txt" copy /Y "%~dp0README_START.txt" "%TOOLDIR%\README_START.txt" >nul
if exist "%~dp0PATCH_NOTES_DZSM_v_0_7_9.md" copy /Y "%~dp0PATCH_NOTES_DZSM_v_0_7_9.md" "%TOOLDIR%\PATCH_NOTES_DZSM_v_0_7_9.md" >nul
if exist "%~dp0icons" xcopy /E /I /Y "%~dp0icons" "%TOOLDIR%\icons" >nul

cls
echo DeutschZ System Manager - DZSM v0.7.9
echo Root: %ROOT%
echo ToolDir: %TOOLDIR%
echo Archiv: %ARCHIVE%
echo.

where powershell.exe >nul 2>nul
if errorlevel 1 (
  echo FEHLER: powershell.exe nicht gefunden.
  echo.
  pause
  exit /b 1
)

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PS1%"
set "EC=%ERRORLEVEL%"
echo.
echo DZSM beendet mit Exitcode %EC%.
echo.
echo Taste schliesst sofort, sonst 30 Sekunden warten.
timeout /t 30
exit /b %EC%
