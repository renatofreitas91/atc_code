# ATC Best Practices

These practices help users get reliable results from Advanced Trigonometry
Calculator 2.1.7.

## Start Small

Build complex calculations from smaller expressions. Store intermediate
results with variables or reuse `#0`, `#1`, and later result references.

## Validate Parentheses Early

When an expression becomes long, first test the inner factors. This is
especially useful for rational expressions, polynomial products and solver
inputs.

## Confirm Angle Mode

Use:

```text
mode
```

before trigonometric calculations. Degree, radian and gradian mode change the
meaning of commands such as `sin(30)`.

## Use Documented Negative Syntax

ATC commonly prints negative coefficients with `_`, for example `_5`. Use the
documented syntax when entering negative coefficient lists or command forms
that expect it.

## Use Verbose Resolution for Debugging

Enable diagnostic output only when needed:

```text
verbose resolution(1)
verbose resolution(0)
```

Verbose output is useful while investigating parser behavior, but normal
calculations should usually run with it disabled.

## Choose the Right Solver Path

Use `solve equation(...)` for supported polynomial and equation forms. Use
`solver(...)` for numerical root-finding workflows.

## Use TXT Workflows for Repetition

For repeated command batches, use the TXT workflow instead of retyping long
sequences. Keep the input file small and reproducible while debugging.

## Preserve Reproducible Examples

When reporting a bug, include:

- exact ATC version;
- precision mode;
- angle mode;
- commands entered;
- expected result;
- actual result;
- whether `verbose resolution` was enabled.

## Respect ATC's Scope

ATC is not a replacement for domain-specific professional validation tools.
For critical engineering, financial or scientific decisions, compare important
results with independent methods.

## Avoid Undocumented Behavior

Do not build workflows that depend on behavior not described in the user guide,
release notes or tests. Parser and solver internals can change while preserving
documented behavior.

