# Advanced Trigonometry Calculator (ATC)

![License: GPL-3.0](https://img.shields.io/badge/License-GPL--3.0-blue.svg)
![Platform: Windows](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Status: Open Source](https://img.shields.io/badge/Status-Open%20Source-brightgreen.svg)

Advanced Trigonometry Calculator (ATC) is a free, open-source command-line
mathematical application for Windows, developed by **Renato Alexandre dos
Santos Freitas**.

ATC evaluates text-based mathematical expressions and documented ATC commands
in a console environment. It focuses on practical numerical workflows and does
not claim broad symbolic-algebra capabilities.

## Project Overview

ATC is intended for students, engineers, developers, and users who prefer a
plain-text calculator workflow. It supports direct expression evaluation,
variables, matrices, polynomial tools, equation solving commands, complex
numbers, and configurable numerical precision.

Version 2.1.7 focuses on precision-mode persistence, equation and polynomial
fixes, broader regression coverage, Windows console behavior, memory
improvements, command-line editing, and clearer verbose-resolution output.

## What ATC is not

ATC deliberately focuses on practical command-driven mathematical computation
instead of trying to be a universal CAS.

- ATC is not a full general-purpose CAS like Mathematica, Maple, SageMath, or
  SymPy.
- ATC is not designed to symbolically prove arbitrary mathematical theorems.
- ATC is not intended to replace domain-specific professional engineering
  validation tools.
- ATC focuses on numeric computation, command-driven workflows, educational
  use, implemented symbolic/numeric hybrid features, and fast local execution.
- Some symbolic behavior exists, but only where explicitly supported and
  tested.

## Features

- Arithmetic expressions
- Trigonometry and inverse trigonometry
- Hyperbolic and inverse hyperbolic functions
- Logarithms and custom logarithm syntax
- Complex numbers
- Variables and reusable expressions
- Automatic multiplication deduction, such as `2pi`, `2(3+4)`, and
  `2sin(pi/2)`
- Matrices and matrix helper commands
- Statistics and probability functions
- DSP functions such as `sinc`, `fft`, and `ifft`
- Polynomial simplification
- Equation solving and systems of equations
- `double` and Boost `mp_float` precision modes
- Command-line automation for selected report-exporting commands
- Tab completion for documented commands, mathematical functions, and user
  functions while typing expressions
- Up/Down history navigation in the interactive prompt

## Example Commands

Quick start:

```text
2+2
sin(pi/2)
mode
solve equation(x^2-5*x+6)
solver(x+2)
create matrix(foo\2\2\3)
see variables
exit
```

More examples:

```text
2+3*4
sin(pi/2)
log(100)
2pi
simplify polynomial((x-2)*(x-3))
solve equation(x^2-5*x+6)
roots to polynomial(2\3)
create matrix(foo\2\2\3)
solver(sin(x)-0.5)
```

Example output:

```text
#0=14
#1=1
#2=2
```

Output formatting depends on ATC settings such as angle mode, precision mode,
and persisted user configuration.

## High Precision Mode

ATC 2.1.7 supports persistent switching between:

- `double`
- Boost `mp_float`

The selected mode is stored under the user's ATC data folder:

```text
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator\higherPrecision.txt
```

Users can switch modes with:

```text
higherprecision(1)
higherprecision(0)
```

The setting is applied after restarting ATC.

Validated high-precision commands include:

```text
dp50dppi
dp50dpe
dp50dpmaxprecpi
```

## Automated Testing

ATC 2.1.7 includes an automated regression suite based on documented user-guide
behavior.

Current validated result for both Release x64 and Release x86:

```text
Summary: 377 passed, 0 failed
```

The isolated coverage helper currently validates 68 source-level and safe
smoke checks, including command exposure, autocomplete behavior and selected
long-running time command guards.

Script throughput is also covered by a dedicated Multiplication Table 1-100
benchmark:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-script-benchmark.ps1 -AtcExe .\x64\Release\atc.exe
```

Run the regression suite after building ATC:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1 -AtcExe .\x64\Release\atc.exe
```

More testing details are available in [docs/Testing.md](docs/Testing.md).

## Build Requirements

ATC is a C++ Windows console application. The repository includes:

```text
Advanced Trigonometry Calculator.sln
```

Build instructions may vary depending on the Visual Studio/MSBuild
environment, Windows SDK, compiler toolset, and target platform.

The project has been built and validated with Release x64 and Release x86
targets. The x86 target remains relevant for compatibility with older Windows
versions.

## Building from Source

Typical workflows are:

- open `Advanced Trigonometry Calculator.sln` in Visual Studio and build the
  desired Release configuration;
- or run MSBuild from a Visual Studio Developer PowerShell / Developer Command
  Prompt environment.

Example Release x64 build command:

```powershell
& 'C:\Program Files\Microsoft Visual Studio\18\Insiders\MSBuild\Current\Bin\MSBuild.exe' '.\Advanced Trigonometry Calculator.sln' /p:Configuration=Release /p:Platform=x64 /m:1
```

Expected Release executables:

```text
x64\Release\atc.exe
Release\atc.exe
```

Adjust the MSBuild path and platform values according to your installed
Visual Studio/C++ environment.

The latest Release x86 and Release x64 builds completed successfully with
`0 Warning(s), 0 Error(s)`.

## Documentation / Documentacao

English is the reference language for open-source and community-facing
documents. Portuguese is maintained to support the Portuguese-speaking
community.

- [Documentation index](docs/README.md)
- [English documentation](docs/en/)
- [Documentação em português](docs/pt-PT/)
- [PDF downloads](docs/pdf/)
- [Full User Guide EN](docs/en/User_Guide_Full.md)
- [Guia Completo PT-PT](docs/pt-PT/User_Guide_Full.md)
- [ATC Cookbook](docs/en/ATC_Cookbook.md)
- [Cookbook PT-PT](docs/pt-PT/ATC_Cookbook.md)
- [Best Practices](docs/en/Best_Practices.md)
- [Boas Praticas PT-PT](docs/pt-PT/Best_Practices.md)
- [User Guide](docs/User_Guide.md)
- [Developer Guide](docs/Developer_Guide.md)
- [Developer Reference](docs/en/Developer_Reference.md)
- [Architecture](docs/Architecture.md)
- [Software Requirements Specification](docs/SOFTWARE_REQUIREMENTS_SPECIFICATION.md)
- [Testing](docs/Testing.md)
- [ATC 2.1.7 Technical Documentation](docs/ATC_2.1.7_DOCUMENTATION.md)
- [ATC 2.1.7 Release Notes](docs/RELEASE_2.1.7.md)
- [Automated Test Cases](tests/ATC_AUTOMATED_TEST_CASES.md)
- [User Guide Coverage Notes](tests/ATC_USER_GUIDE_COVERAGE.md)
- [Changelog](CHANGELOG.md)

When a Markdown document changes in one language, the corresponding document in
the other language should be reviewed. PDF files should be regenerated after
relevant Markdown changes.

## License

Advanced Trigonometry Calculator is licensed under the **GNU General Public
License v3.0 (GPL-3.0)**.

See [Advanced Trigonometry Calculator/License.txt](Advanced%20Trigonometry%20Calculator/License.txt).

## Author

Advanced Trigonometry Calculator is developed and maintained by:

**Renato Alexandre dos Santos Freitas**

The project is open source and has a long-term development history dating back
to 2011.

## Contributing

Contributions are welcome. Please read [CONTRIBUTING.md](CONTRIBUTING.md)
before submitting changes.

Useful contributions include bug reports, documentation improvements,
additional regression tests, and careful fixes for parser, solver, precision,
matrix, or memory behavior.
