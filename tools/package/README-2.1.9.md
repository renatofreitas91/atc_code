# ATC 2.1.9 candidate packaging

Use `build-atc-2.1.9-candidate.ps1` for separate x64 and x86 candidate ZIPs.
Packaging does not compile, publish, tag or approve executables.

Required inputs are `OutputRoot`, `X64Executable`, `X86Executable`,
`X64SHA256`, `X86SHA256`, `X64Toolset` and `X86Toolset`. Supply hashes from the
validation evidence for those exact executables and record the actual toolsets.
`Revision` defaults to `candidate1`. Output paths must be new; existing packages
are not overwritten.

Both binaries must expose FileVersion and ProductVersion `2.1.9.0` and the
matching PE architecture. The script checks their supplied hashes before
packaging. It includes the current bilingual guide, a source-file hash manifest,
package checksums and metadata explicitly identifying an unpublished candidate.
A source manifest records the checkout; matching an executable to validated
sources still requires the associated build and runtime evidence.

Validate each extracted candidate with
`tests/run-atc-2.1.9-candidate-package-validation.ps1 -PackageRoot <directory>`.
The separate `run-atc-2.1.9-package-validation.ps1` checks the older combined
x64/x86 directory layout and is not the validator for these separate ZIPs.

The two `Setup-ATC-2.1.9-*.iss` definitions take the corresponding extracted
candidate as `PackageRoot`. AppId and Windows Terminal profile GUID remain
stable. Installer compilation and native Windows execution require their own
validation; preparing these scripts does not complete those gates.

Historical 2.1.8 scripts and manifests remain unchanged. To reproduce an old
package, use its historical source checkout and inputs rather than running the
old packager against the current 2.1.9 tools.
