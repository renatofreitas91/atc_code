#!/usr/bin/env python3
"""Check current version metadata while keeping historical releases intact."""
from pathlib import Path
import re


def main():
    root = Path(__file__).resolve().parents[1]

    def read(name):
        return (root/name).read_bytes().decode('latin1')

    match = re.search(r'project\(AdvancedTrigonometryCalculator VERSION (\d+\.\d+\.\d+)', read('CMakeLists.txt'))
    assert match, 'CMake project version missing'
    version = match.group(1)
    assert version == '2.1.9', 'Unexpected candidate version'
    app = 'Advanced Trigonometry Calculator/'
    for name in ('settings.cpp', 'atc_core.cpp', 'commands.cpp',
                 'check_for_updates.cpp', 'About execution of application.txt'):
        text = read(app+name)
        found = re.findall(r'v2\.1\.\d+(?: RC\d+)?', text)
        assert found and set(found) == {'v'+version}, (name, found)
    resource = read(app+'versioninfo.rc')
    for field in ('FILEVERSION', 'PRODUCTVERSION'):
        assert re.search(r'\b'+field+r'\s+2,1,9,0\b', resource), field
    for field in ('FileVersion', 'ProductVersion'):
        assert '"'+field+'", "'+version+'.0"' in resource, field
    for suffix in ('Windows-x64', 'Windows-XP-WOW64-x86'):
        new = read('tools/installer/Setup-ATC-'+version+'-'+suffix+'.iss')
        old = read('tools/installer/Setup-ATC-2.1.8-'+suffix+'.iss')
        assert '#define MyAppVersion "'+version+'"' in new
        assert 'VersionInfoVersion='+version+'.0' in new
        assert 'OutputBaseFilename=Setup-ATC-'+version+'-'+suffix in new
        assert re.search(r'^AppId=.*$', new, re.M).group() == re.search(r'^AppId=.*$', old, re.M).group()
        assert '#define MyAppVersion "2.1.8"' in old
    terminal = read('tools/windows-terminal/Install-ATCWindowsTerminalProfile.ps1')
    assert 'Advanced Trigonometry Calculator '+version+'"' in terminal
    assert 'tabTitle = "ATC '+version+'"' in terminal
    assert 'colorScheme = "ATC '+version+'"' in terminal
    assert '{13f1a9c7-83d4-5f62-9e71-1e91ca4da218}' in terminal
    assert 'Advanced Trigonometry Calculator '+version in read('tests/run-atc-windows-terminal-integration-tests.ps1')
    for language, label in (('en', 'Version'), ('pt-PT', 'Vers')):
        text = read('docs/'+language+'/User_Guide_Full.md')
        assert re.search(label+r'[^\n]*ATC '+re.escape(version), text)
    assert '## '+version+' - Unreleased' in read('CHANGELOG.md')
    assert '## 2.1.8 - 2026-08-25' in read('CHANGELOG.md')
    package = read('tools/package/build-atc-'+version+'-candidate.ps1')
    assert 'ATC_2_1_9_Bilingual_User_Guide.pdf' in package
    assert '$expectedX64 = $X64SHA256' in package and '$expectedX86 = $X86SHA256' in package
    assert '2.1.8' not in package
    validator = read('tests/run-atc-'+version+'-candidate-package-validation.ps1')
    assert 'PE versions are '+version+'.0' in validator
    assert 'SOURCE_MANIFEST.json' in validator
    assert '2.1.8' not in read('tools/docs/build_pdfs.py')
    assert 'ATC '+version in read('tools/windows-terminal/README.md')
    assert (root/'docs/pdf/ATC_2_1_9_Bilingual_User_Guide.pdf').is_file()
    print('PASS version '+version+': application, PE resources, installers, Terminal, package scripts and guide sources; historical identity preserved.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
