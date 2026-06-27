# Advanced Trigonometry Calculator (ATC)

![License: GPLv3](https://img.shields.io/badge/License-GPLv3-blue.svg)
![Platform: Windows](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Status: Open Source](https://img.shields.io/badge/Status-Open%20Source-brightgreen.svg)

Advanced Trigonometry Calculator (ATC) is an open-source command-line scientific and mathematical calculator developed by **Renato Alexandre dos Santos Freitas**.

ATC is designed to evaluate text-based mathematical expressions and support advanced numerical calculations in a console environment. It is intended to be useful for students, engineers, scientists, developers, and mathematics enthusiasts who prefer a direct command-line workflow.

## Table of Contents

- [Project Overview](#project-overview)
- [Why ATC?](#why-atc)
- [Features](#features)
- [Example Usage](#example-usage)
- [Getting Started](#getting-started)
- [Build / Requirements](#build--requirements)
- [Documentation](#documentation)
- [Project Structure](#project-structure)
- [Design Principles](#design-principles)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [License](#license)
- [Author](#author)

## Project Overview

Advanced Trigonometry Calculator provides a text-based calculation environment for scientific and mathematical work. It supports direct expression evaluation, command-based workflows, reusable variables, matrix operations, equation solving, and high-precision numerical calculations.

The project focuses on practical console usage: users enter commands or mathematical expressions, ATC evaluates them, and results are returned in the terminal. This makes the tool suitable for repeatable calculations, learning, experimentation, and technical workflows where plain-text input is valuable.

## Why ATC?

ATC follows a command-line driven philosophy:

- mathematical expressions are written as text;
- calculations can be repeated and documented more easily;
- users can inspect and learn from the syntax they enter;
- the project remains transparent through open-source development;
- the console workflow keeps interaction direct and script-friendly;
- the project has evolved over the long term since 2011.

The goal is not to replace every specialized mathematical platform, but to provide a capable, transparent, and maintainable command-line calculator for a broad range of numerical and educational use cases.

## Features

| Category | Capabilities |
| --- | --- |
| Trigonometry | Circular and hyperbolic functions |
| Algebra | Expressions, equations, systems of equations |
| Complex Numbers | Arithmetic and expressions with complex values |
| Matrices | Matrix creation and manipulation |
| Statistics | Statistical calculations |
| Numerical Computing | High-precision numerical calculations |
| User Workflow | Variables, reusable expressions, command-line usage |

Main capabilities include:

- trigonometric calculations;
- hyperbolic functions;
- complex numbers;
- logarithms;
- statistics;
- matrices;
- equation solving;
- systems of equations;
- variables and reusable expressions;
- high-precision numerical calculations;
- scientific and engineering-style calculations;
- text-based command interface.

## Example Usage

Examples below show typical ATC commands. Output formatting may depend on the current ATC configuration, such as angle mode, precision settings, or selected numerical mode.

```text
sin(pi/2)
```

Illustrative output:

```text
#0=1
```

```text
log(100)
```

Illustrative output:

```text
#1=2
```

```text
solver(x-2)
```

Illustrative output:

```text
#2=2
```

```text
solve equation(x^2-4=0)
```

Depending on the accepted equation syntax and current parser path, equation-solving commands may also be written in ATC's documented polynomial forms.

```text
create matrix(A\2\2\1)
```

Matrix commands and exact output formats depend on the matrix operation being used.

## Getting Started

1. Download or build ATC.
2. Run the executable in a command-line environment.
3. Enter mathematical expressions or ATC commands.
4. Read the calculated result in the console.
5. Explore the available commands and documentation.

## Build / Requirements

ATC is primarily a C++ command-line application. Windows is the primary platform.

The repository contains a Visual Studio solution:

```text
Advanced Trigonometry Calculator.sln
```

Build instructions may vary depending on the Visual Studio/C++ environment used. Users should inspect the repository files and project configuration for exact build steps, target platforms, and release/debug settings.

Typical build workflows may involve opening the solution in Visual Studio or invoking MSBuild with the desired configuration and platform. Exact compiler and toolset requirements should be confirmed from the project configuration available in the repository.

## Documentation

Documentation and release information may be found in the repository, including:

- `docs/ATC_2.1.7_DOCUMENTATION.md`;
- `docs/RELEASE_2.1.7.md`;
- `tests/ATC_AUTOMATED_TEST_CASES.md`;
- `tests/ATC_USER_GUIDE_COVERAGE.md`;
- user guide files included with ATC distributions or project assets;
- project pages associated with the ATC open-source project.

If documentation locations change, the repository files should be considered the authoritative source for the current version.

## Project Structure

The repository contains the source code and supporting files required to build and maintain ATC. The exact structure may evolve as the project continues to be developed.

Current high-level areas include:

| Path | Purpose |
| --- | --- |
| `Advanced Trigonometry Calculator/` | Main C++ source code and project files |
| `docs/` | Technical documentation and release notes |
| `tests/` | Automated regression tests and coverage notes |
| `icons/` | Icon assets used by the project |
| `tools/` | Supporting development utilities, when present |
| `Advanced Trigonometry Calculator.sln` | Visual Studio solution file |

## Design Principles

ATC development is guided by practical engineering and educational goals:

- correctness in mathematical behavior;
- reproducibility of text-based calculations;
- transparency through open-source code;
- maintainability over long-term project evolution;
- educational value for users learning mathematical syntax and numerical methods;
- practical command-line usage for day-to-day calculation workflows.

## Roadmap

Future work may include:

- improving mathematical capabilities;
- expanding automated test coverage;
- improving documentation;
- improving command-line usability;
- continuing code maintenance and refactoring;
- improving examples and user guidance.

No specific release dates are promised in this roadmap.

## Contributing

Contributions are welcome. Useful ways to help include:

- reporting bugs;
- suggesting features;
- improving documentation;
- submitting pull requests;
- testing mathematical commands and edge cases;
- reviewing examples and user guidance.

When contributing, keep changes focused, explain the behavior being changed, and include tests or validation notes when possible.

## License

This project is licensed under the GNU General Public License v3.0.

See `Advanced Trigonometry Calculator/License.txt` for details.

## Author

Developed and maintained by **Renato Alexandre dos Santos Freitas**.

Advanced Trigonometry Calculator is an open-source project with long-term development history dating back to 2011.
