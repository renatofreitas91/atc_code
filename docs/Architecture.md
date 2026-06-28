# Advanced Trigonometry Calculator Architecture

This document describes the high-level architecture of Advanced Trigonometry
Calculator (ATC). It avoids implementation claims that are not visible in the
repository.

## Overview

ATC is a Windows console application written in C++. It is organized around a
command-line input loop, command routing, expression processing, mathematical
modules, persisted settings, and regression tests.

## Module Architecture and Execution Flow

The following diagram gives a compact view of the main ATC modules. It is
intended as a mental map for new contributors rather than a complete call graph.

Textual overview:

```text
User Input
  |
  v
Console Prompt / Command Editor
  |
  v
Tokenizer / Parser
  |
  v
Expression Engine
  |
  v
Feature Modules
  - Arithmetic
  - Trigonometry
  - Complex Numbers
  - Matrices
  - Statistics
  - DSP
  - Polynomial Tools
  - Equation Solver
  - Numerical Solver
  - Graph
  - TXT Processing
  - Guided Modules
  |
  v
Output / Results Store / Files
```

```mermaid
flowchart LR
    CLI["CLI / User Input"] --> Parser["Command Parser"]
    TXT["TXT Processing / File Input"] --> Parser
    Parser --> Expr["Expression Parser"]
    Parser --> Settings["History / Logs / Settings"]
    Expr --> Solver["Solver Engine"]
    Expr --> Numeric["Numeric Engine"]
    Expr --> Matrix["Matrix Engine"]
    Parser --> Domain["Statistics / Physics / Finance / Geometry / Unit Conversion modules"]
    Solver --> Output["Output Renderer"]
    Numeric --> Output
    Matrix --> Output
    Domain --> Output
    Output --> Settings
```

The normal execution path is command-driven. Some commands are handled before
the mathematical expression parser, while others are normalized and then routed
to the relevant numeric or domain module.

```mermaid
flowchart TD
    A["user command"] --> B["command normalization"]
    B --> C["command detection"]
    C --> D{"special command?"}
    D -->|yes| E["dispatch to module"]
    D -->|no| F["expression parsing"]
    F --> E
    E --> G["computation"]
    G --> H["formatted output"]
    H --> I["history/log update"]
```

In practice, `main.cpp`, `main_aux_processor.cpp`, `main_processor.cpp`,
`processing_core.cpp`, and `commands.cpp` share responsibility for this flow.
Specialized modules then handle the mathematical or workflow-specific work.

## Input to Output Flow

ATC input normally starts at the console prompt. The custom command editor
collects the line, supports history/autocomplete, and sends the resulting text
into the normal command-processing flow. From there, ATC decides whether the
input is a direct expression, a named command or an interactive guided module.

Direct expressions are evaluated immediately:

```text
2+2
sin(pi/2)
```

Named commands select a specific workflow:

```text
mode
solve equation(x^2-5*x+6)
```

Guided modules open menus or interactive prompts:

```text
financial calculations
unit conversions
```

The result is formatted for the console, stored in the session result list
when appropriate, and may also be written to files for report/export commands.

## Results and Variables

ATC stores visible calculation results as indexed entries such as `#0`, `#1`
and later values. These references allow step-by-step work without retyping
long expressions.

Named variables are handled through the command/expression processing layer and
persisted runtime files where the existing feature requires it. Matrix
variables and scalar variables share the same high-level user workflow but are
handled by different internal paths.

## Precision Model

ATC 2.1.7 can run the main typed runtime flow using `double` or Boost
`mp_float`. Startup reads the persisted setting and dispatches the template
runtime accordingly. This keeps the public command flow mostly unchanged while
allowing higher precision for supported numeric paths.

## Automatic Multiplication

The expression engine includes support for documented implicit multiplication
forms such as adjacent constants, factors and functions. This is a convenience
feature, not a general symbolic algebra system. Parser changes in this area
should be tested against arithmetic, variables, functions, matrices, polynomial
tools, `solver(...)` and `solve equation(...)`.

## TXT Processing

TXT workflows route file input into the same command-processing model used by
interactive input. The automated tests use temporary folders and mocks for
window/file opening side effects so the public workflow can be checked without
opening real user applications.

## Architectural Limits

ATC deliberately focuses on command-driven numerical work and implemented
hybrid symbolic/numeric features. It should not be treated as a full
general-purpose CAS. Unsupported symbolic transformations should fail clearly
or remain on documented fallback paths.

## Where New Modules Fit

New user-facing modules should usually integrate at the command-dispatch layer,
then delegate actual calculation work to a focused module file. They should
also add:

- autocomplete vocabulary when useful;
- regression or smoke coverage;
- user-guide documentation;
- notes for manual validation if the module is deeply interactive.

## CLI Entry Point

The main application starts in `Advanced Trigonometry Calculator/main.cpp`.

Startup responsibilities include:

- initializing ATC paths and runtime state;
- reading persisted settings such as precision mode;
- choosing the typed runtime path for `double` or Boost `mp_float`;
- handling command-line arguments and interactive console flow.

Interactive line input is delegated to `auto_complete.cpp`, which handles
line editing, history navigation and Tab completion before the command string
is passed into the normal processing flow.

## Command Dispatcher

Command routing is spread across the main processor files and command modules:

- `main.cpp`
- `main_aux_processor.cpp`
- `main_processor.cpp`
- `commands.cpp`

These files coordinate whether input is treated as a direct expression, a
special ATC command, a variable assignment, a matrix operation, a file/TXT
workflow, or an interactive menu action.

Autocomplete is intentionally kept outside the mathematical processors. It
helps the user complete command/function names and previous expressions, but
does not decide calculation semantics.

## Processing Core

`processing_core.cpp` contains the central expression-processing functions,
including:

- `initialProcessor<T>()`
- `arithSolver<T>()`
- `functionProcessor<T>()`

This layer evaluates arithmetic expressions, calls mathematical functions,
handles parts of implicit multiplication and formatting, and routes values
through the selected precision type.

## Mathematical Modules

Mathematical behavior is split across focused files, including:

- `trigonometry.cpp`
- `hyperbolic.cpp`
- `logarithmic.cpp`
- `statistics.cpp`
- `statistics_calculations.cpp`
- `digital_signal_processing.cpp`
- `polynomial_arithmetic.cpp`
- `equation_solver.cpp`
- `equations_system_solver.cpp`
- `solver.cpp`
- `function_study.cpp`
- `graph.cpp`
- `arithmetic_matrix_solver.cpp`

Some modules are command-oriented, while others provide lower-level numerical
or formatting support.

## Persistence Files

ATC stores user settings and runtime data under the user's ATC data folder,
commonly:

```text
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator
```

Persisted files include settings such as:

- `higherPrecision.txt`
- `mode.txt`
- `verboseResolution.txt`
- `actualTime.txt`
- `dimensions.txt`
- `window.txt`
- `variables.txt`
- `renamedVar.txt`
- `pathName.txt`

The exact set of files may vary depending on which commands have been used.

## Windows Console Behavior

ATC is a console application and contains Windows-specific behavior for console
display, colors, window settings, and Windows Terminal compatibility.

Current 2.1.7 behavior includes:

- Windows 11 detection through `RtlGetVersion`;
- default intro handling for Windows 11 console environments;
- Win32-to-ANSI color mapping for Windows Terminal scenarios;
- commands that can launch new ATC instances or tabs when `wt.exe` is
  available, with fallback behavior.

## Tests

Tests are PowerShell-based and live in `tests/`.

The main regression runner executes ATC commands against built executables and
checks output patterns. The suite covers a broad set of documented behavior but
intentionally avoids unsafe PC-control commands. Deeply interactive modules have
safe runtime smoke coverage, while exhaustive per-option validation remains
manual or future automated work.

## Build Files

The root solution is:

```text
Advanced Trigonometry Calculator.sln
```

The main Visual Studio project is:

```text
Advanced Trigonometry Calculator/Advanced Trigonometry Calculator.vcxproj
```

The project uses a Windows console subsystem and currently includes Release x64
and Release x86 configurations.
