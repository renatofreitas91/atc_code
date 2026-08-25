@echo off
setlocal EnableExtensions EnableDelayedExpansion

set "REPO=%~dp0.."
for %%I in ("%REPO%") do set "REPO=%%~fI"
set "SOLUTION=%REPO%\Advanced Trigonometry Calculator.sln"
set "OUT=%REPO%\build\modern-x64-release"

if not defined BOOST_ROOT set "BOOST_ROOT=C:\boost_1_90_0"
if not exist "%BOOST_ROOT%\boost" (
  echo ERROR: BOOST_ROOT is invalid: "%BOOST_ROOT%"
  exit /b 2
)

set "VSROOT=%ProgramFiles(x86)%\Microsoft Visual Studio\2022\BuildTools"
if not exist "%VSROOT%\VC\Auxiliary\Build\vcvarsall.bat" (
  echo ERROR: Visual Studio 2022 Build Tools were not found.
  exit /b 3
)

set "Path="
call "%VSROOT%\VC\Auxiliary\Build\vcvarsall.bat" x64 -vcvars_ver=14.44
if errorlevel 1 exit /b !errorlevel!
set "INCLUDE=%BOOST_ROOT%;%INCLUDE%"

"%VSROOT%\MSBuild\Current\Bin\MSBuild.exe" "%SOLUTION%" ^
  /t:Rebuild ^
  /p:Configuration=Release ^
  /p:Platform=x64 ^
  /p:PlatformToolset=v143 ^
  /p:UseEnv=true ^
  "/p:IntDir=%OUT%\obj\\" ^
  "/p:OutDir=%OUT%\bin\\" ^
  /m:1

exit /b !errorlevel!
