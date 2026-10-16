@echo off
setlocal
set "PYTHON=C:\Python34\python.exe"
set "ATC=C:\ATC\atc_source\Release\atc.exe"
if not "%~1"=="" set "ATC=%~1"
if not exist "%PYTHON%" (
  echo Install the included Python 3.4.4 x86 MSI in C:\Python34 first.
  exit /b 2
)
if not exist "%ATC%" (
  echo ATC executable not found: "%ATC%"
  echo Usage: run-atc-xp.cmd "C:\path\atc.exe"
  exit /b 2
)
"%PYTHON%" --version
"%PYTHON%" "%~dp0run-atc-xp.py" --exe "%ATC%" --catalog "%~dp0catalog.json" --assets "%~dp0package" --runs "%~dp0runs"
set "ATC_RESULT=%ERRORLEVEL%"
echo.
echo Runner exit code: %ATC_RESULT%
echo Results are in a new folder below "%~dp0runs".
exit /b %ATC_RESULT%
