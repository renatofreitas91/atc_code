# Contributing to Advanced Trigonometry Calculator

Thank you for your interest in improving Advanced Trigonometry Calculator
(ATC).

ATC is a long-running C++ command-line mathematical application. Contributions
should be careful, focused, and validated with examples or tests whenever
possible.

## Reporting Bugs

When reporting a bug, include:

- the exact ATC command or expression used;
- the actual output;
- the expected output;
- whether the issue appears in `double`, Boost `mp_float`, or both;
- the build target, such as Release x64 or Release x86;
- any relevant settings, such as angle mode or precision mode.

Small reproducible examples are the most useful reports.

## Proposing Improvements

Feature proposals should explain:

- the user problem being solved;
- the proposed command syntax, if relevant;
- expected examples and outputs;
- compatibility concerns with existing ATC syntax;
- whether the change needs documentation and tests.

Avoid proposing behavior that would conflict with existing documented commands.

## Coding Expectations

- Keep changes focused and compatible with the current architecture.
- Do not rename public commands or shared functions without a clear reason.
- Prefer existing project patterns over introducing new frameworks or build
  systems.
- Preserve Windows console compatibility requirements.
- Code comments, when needed, should be written in English.
- Avoid unsupported claims in code comments or documentation.

## Testing Expectations

Before submitting changes, run the relevant regression tests when possible:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1 -AtcExe .\x64\Release\atc.exe
```

For memory-sensitive changes, also consider:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-memory-stress.ps1 -Iterations 10
```

If tests cannot be run, explain why and include manual validation steps.

## Documentation Expectations

- Update `README.md` only for project-level entry-point information.
- Put technical details in `docs/`.
- Update `CHANGELOG.md` for notable user-facing or maintenance changes.
- English is the reference language for open-source/community-facing
  documentation.
- Portuguese documentation is maintained to support the Portuguese-speaking
  community.
- When a document changes in one language, check whether the corresponding
  document in the other language and generated PDF files also need updates.
- Do not claim unsupported symbolic-algebra features.

## Pull Request Checklist

- The change is focused.
- Existing behavior is preserved unless intentionally changed.
- Relevant tests or manual validation were run.
- Documentation was updated when behavior changed.
- GPL-3.0 license and author attribution are preserved.
