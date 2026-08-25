#define MyAppName "Advanced Trigonometry Calculator"
#define MyAppVersion "2.1.8"
#define MyAppPublisher "Renato Alexandre dos Santos Freitas"
#define MyAppURL "https://github.com/renatofreitas91/atc_code"
#define MyAppExeName "atc.exe"
#ifndef PackageRoot
  #error PackageRoot must identify the extracted ATC 2.1.8 x64 package
#endif

[Setup]
AppId={{5D7DF26A-4FB0-412C-9477-E2CD61328F42}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
AppCopyright=Copyright (C) 2011-2026 - Renato Freitas
VersionInfoVersion=2.1.8.0
VersionInfoCompany={#MyAppPublisher}
VersionInfoDescription={#MyAppName} 2.1.8 x64 Setup
VersionInfoCopyright=Copyright (C) 2011-2026 - Renato Freitas
DefaultDirName={userdocs}\{#MyAppName}
DefaultGroupName={#MyAppName}
PrivilegesRequired=lowest
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64
AllowNoIcons=yes
CloseApplications=yes
RestartApplications=no
LicenseFile={#PackageRoot}\LICENSE.txt
InfoBeforeFile={#PackageRoot}\README.txt
InfoAfterFile={#PackageRoot}\SOURCE.txt
SetupIconFile={#PackageRoot}\Windows-Terminal-Integration\atc.ico
OutputBaseFilename=Setup-ATC-2.1.8-Windows-x64
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "portuguese"; MessagesFile: "compiler:Languages\Portuguese.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "{#PackageRoot}\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{userdesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon
Name: "{group}\Advanced Trigonometry Calculator - User Guide"; Filename: "{app}\Advanced Trigonometry Calculator - User Guide.pdf"

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
