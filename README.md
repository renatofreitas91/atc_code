# Advanced Trigonometry Calculator (ATC)

![License: GPL-3.0](https://img.shields.io/badge/License-GPL--3.0-blue.svg)
![Platform: Windows](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Status: Open Source](https://img.shields.io/badge/Status-Open%20Source-brightgreen.svg)

Advanced Trigonometry Calculator (ATC) is a free, open-source command-line
mathematical application developed by **Renato Alexandre dos Santos Freitas**.

ATC is designed for text-based scientific and mathematical calculations in a
console environment. It supports direct expression evaluation, reusable
variables, matrices, equation-solving commands, polynomial tools, complex
numbers, and configurable numerical precision.

## Project Overview

ATC provides a practical command-line calculation environment for students,
engineers, developers, and open-source users who prefer plain-text mathematical
input.

The project focuses on numerical calculation workflows rather than presenting
itself as a full computer algebra system. Users enter expressions or documented
ATC commands, and results are returned directly in the terminal.

ATC 2.1.7 focuses on:

- predictable switching between `double` and Boost `mp_float` precision modes;
- improved high-precision formatting;
- stronger equation solver, polynomial simplifier, and solver behavior;
- broader automated regression coverage based on the user guide;
- improved Windows console behavior;
- reduced unnecessary dynamic allocation in several numeric paths.

## Features

ATC includes support for:

- arithmetic expressions;
- trigonometry and inverse trigonometry;
- hyperbolic and inverse hyperbolic functions;
- logarithms and custom logarithm syntax;
- complex numbers;
- variables and reusable expressions;
- automatic multiplication deduction, such as `2pi`, `2(3+4)`, `(x+1)y`,
  and `2sin(pi/2)`;
- matrices and matrix-related helper commands;
- statistics and probability functions;
- DSP functions such as `sinc`, `fft`, and `ifft`;
- polynomial simplification;
- equation solving, including coefficient-form and supported textual
  polynomial forms;
- systems of equations;
- `double` and Boost `mp_float` precision modes;
- command-line automation for selected report-exporting commands.

ATC also includes documented commands for settings, file/folder workflows,
TXT command bridging, graph settings, date/time calculations, and other
console-based utilities.

## Example Commands

Examples below use ATC syntax. Output may vary depending on angle mode,
precision mode, and persisted settings.

```text
2+3*4
```

```text
#0=14
```

```text
sin(pi/2)
```

```text
#1=1
```

```text
log(100)
```

```text
#2=2
```

```text
sqrt(9)
```

```text
#3=3
```

```text
2pi
```

```text
#4=6.28319
```

```text
simplify polynomial((x-2)*(x-3))
```

```text
(1+0i)x^2+(_5+0i)x^1+(6+0i)
```

```text
solve equation(x^2-5*x+6)
```

```text
x1=3
x2=2
```

```text
roots to polynomial(2\3)
```

```text
(1+0i)x^2+(_5+0i)x^1+(6+0i)
```

```text
create matrix(foo\2\2\3)
```

This creates a documented matrix value using ATC's matrix command syntax.

## High Precision Mode

ATC 2.1.7 supports persistent switching between:

- `double`
- Boost `mp_float`

The selected mode is stored in:

```text
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator\higherPrecision.txt
```

Accepted values:

- `0`: use `double`
- `1`: use Boost `mp_float`

Users can switch modes with:

```text
higherprecision(1)
higherprecision(0)
```

The setting is applied after restarting ATC.

Validated high-precision examples include:

```text
dp50dppi
```

```text
3.14159265358979323846264338327950288419716939937511
```

```text
dp50dpe
```

```text
2.71828182845904523536028747135266249775724709369996
```

ATC also supports temporary high-precision evaluation through the documented
`maxprec` prefix without permanently changing the persisted precision mode.

## Automated Testing

ATC 2.1.7 includes an automated regression suite based on the documented user
guide behavior.

Current validated result for both Release x64 and Release x86:

```text
Summary: 338 passed, 0 failed
```

Regression coverage includes arithmetic, constants, trigonometry, inverse
trigonometry, hyperbolic functions, logarithms, matrices, variable names,
automatic multiplication, polynomial simplification, equation solving, solver
paths, function study, graph settings, date/time commands, TXT command bridge
commands, persistent settings, interactive menu behavior, and precision mode
persistence.

Run the regression suite after building ATC:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1 -AtcExe .\x64\Release\atc.exe
```

The test runner temporarily touches ATC user-setting files under:

```text
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator
```

It backs up and restores the settings it modifies.

## Build Requirements

ATC is a C++ Windows console application. The repository includes a Visual
Studio solution:

```text
Advanced Trigonometry Calculator.sln
```

Build instructions may vary depending on the Visual Studio/MSBuild environment,
installed Windows SDK, compiler toolset, and target platform.

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

Expected Release x64 executable:

```text
x64\Release\atc.exe
```

Expected Release x86 executable:

```text
Release\atc.exe
```

Adjust the MSBuild path and platform values according to your installed Visual
Studio/C++ environment.

## Documentation

The current 2.1.7 documentation and release notes are maintained in:

- `docs/ATC_2.1.7_DOCUMENTATION.md`
- `docs/RELEASE_2.1.7.md`
- `tests/ATC_AUTOMATED_TEST_CASES.md`
- `tests/ATC_USER_GUIDE_COVERAGE.md`

The technical documentation is the source of truth for current behavior,
validated examples, regression coverage, known limitations, and release notes.

Project documentation should be maintained in Portuguese and English. Code
comments, when present, should be written in English.

## License

Advanced Trigonometry Calculator is licensed under the **GNU General Public
License v3.0 (GPL-3.0)**.

See:

```text
Advanced Trigonometry Calculator/License.txt
```

## Author

Advanced Trigonometry Calculator is developed and maintained by:

**Renato Alexandre dos Santos Freitas**

The project is open source and has a long-term development history dating back
to 2011.

## Contributing

Contributions are welcome. Useful contributions include:

- bug reports with reproducible commands;
- documentation improvements;
- additional regression tests;
- careful fixes for parser, solver, precision, matrix, or memory behavior;
- validation on supported Windows environments.

When contributing, keep changes focused, avoid unsupported claims, and include
tests or validation notes whenever possible.
