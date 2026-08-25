@echo off
setlocal EnableExtensions EnableDelayedExpansion

set "REPO=%~dp0.."
for %%I in ("%REPO%") do set "REPO=%%~fI"
set "SOLUTION=%REPO%\Advanced Trigonometry Calculator.sln"
set "OUT=%REPO%\build\xp-x86-release"

if not defined BOOST_ROOT set "BOOST_ROOT=C:\boost_1_90_0"
if not defined UCRT_VERSION set "UCRT_VERSION=10.0.26100.0"

set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
  echo ERROR: vswhere.exe was not found.
  exit /b 2
)

if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" set "VSROOT=%ProgramFiles(x86)%\Microsoft Visual Studio\2022\BuildTools"
if not defined VSROOT for /f "tokens=*" %%I in ('"%VSWHERE%" -latest -version "[17.0,18.0)" -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath') do set "VSROOT=%%I"
if not defined VSROOT (
  echo ERROR: Visual Studio C++ Build Tools were not found.
  exit /b 3
)

set "Path="
call "%VSROOT%\VC\Auxiliary\Build\vcvarsall.bat" x86 -vcvars_ver=14.16
if errorlevel 1 exit /b !errorlevel!

set "MSVC_ROOT=%VCToolsInstallDir:~0,-1%"
set "UCRT_ROOT=%ProgramFiles(x86)%\Windows Kits\10"
set "SDK71_ROOT=%ProgramFiles(x86)%\Microsoft SDKs\Windows\v7.1A"

if not exist "%BOOST_ROOT%\boost" (
  echo ERROR: BOOST_ROOT is invalid: "%BOOST_ROOT%"
  exit /b 4
)
if not exist "%UCRT_ROOT%\Lib\%UCRT_VERSION%\ucrt\x86\libucrt.lib" (
  echo ERROR: UCRT %UCRT_VERSION% x86 library was not found.
  exit /b 5
)
if not exist "%SDK71_ROOT%\Lib\Kernel32.Lib" (
  echo ERROR: Windows SDK 7.1A was not found.
  exit /b 6
)

set "INCLUDE=%BOOST_ROOT%;%MSVC_ROOT%\include;%UCRT_ROOT%\Include\%UCRT_VERSION%\ucrt;%VSROOT%\VC\Auxiliary\VS\include;%SDK71_ROOT%\Include"
set "LIB=%MSVC_ROOT%\lib\x86;%UCRT_ROOT%\Lib\%UCRT_VERSION%\ucrt\x86;%VSROOT%\VC\Auxiliary\VS\lib\x86;%SDK71_ROOT%\Lib"
set "LIBPATH=%MSVC_ROOT%\lib\x86;%VSROOT%\VC\Auxiliary\VS\lib\x86;%SDK71_ROOT%\Lib"

"%VSROOT%\MSBuild\Current\Bin\MSBuild.exe" "%SOLUTION%" ^
  /t:Rebuild ^
  /p:Configuration=Release ^
  /p:Platform=x86 ^
  /p:PlatformToolset=v141_xp ^
  /p:UseEnv=true ^
  "/p:IntDir=%OUT%\obj\\" ^
  "/p:OutDir=%OUT%\bin\\" ^
  /m:1

exit /b !errorlevel!
