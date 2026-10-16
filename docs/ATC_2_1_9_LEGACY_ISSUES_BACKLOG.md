# ATC 2.1.9 Legacy Issues Backlog

## Provenance and scope

Recovered and re-triaged on 2026-10-16 from the document with this name in the
2026-07-01 workspace. This is an updated triage record, not a verbatim copy.
The original collected discoveries from ATC Online, ATC 3.0 audits, user-guide
review and legacy captures for a conservative 2.x maintenance release.

No ATC 3.0 private engine, parser, adapter or implementation has been imported.
Architectural evolution and new command families remain outside this backlog.
Observations require public inputs, persistent state, independent expectations,
architecture comparisons and regression coverage before a fix is accepted.

## Initial triage (before the local corrections below)

Reference HEAD: `3f0725bad149c5871b95acfa20907cdc0373b7b6`.
Reproduction uses the previously validated Release v141_xp x86/x64 binaries,
not a new build. Exact executable hashes, inputs, outputs and fixtures are in
the separate audit results. Every case has a new directory, mode=2 (degrees),
double precision and empty persisted variables. Numerical-system output is
enabled only for the base-output group. Official process deadline: 20 seconds.

| ID | Original issue | Current evidence | Disposition |
| --- | --- | --- | --- |
| L219-SOLVER-001 | solver(sin(x)-sin(30+30i)) returned sentinel -765432+234567i in historical captures | Now returns 30+30i, exit 0 on both architectures; existing All regression expects that value | Specific historical case resolved; not a claim of universal solver correctness |
| L219-NUMSYS-001 | Negative/scientific binary, octal and hexadecimal output | Negative finite output is still malformed on both architectures; scientific binary exponents also need review | Open, high priority; add focused expected-value coverage before engine changes |
| L219-NONFINITE-001 | _INF-1, INF+INF, INF*_INF, 1/INF produced complex NaN text | All four still produce complex NaN forms on both architectures, exit 0 | Open; approve real/complex non-finite policy before changing behavior |
| L219-NUMPARSE-001 | B1010, O12, H10 unexpectedly returned 0 | Reproduced on the checkpoint; user confirmed B=binary, O=octal, H=hexadecimal, P=SI prefix | Local correction under validation; see follow-up below |

## Demonstrated base-output defect

With numSystems.txt=1:

| Input | Obtained binary / octal / hexadecimal | Signed mathematical representation |
| --- | --- | --- |
| _1 | -11111111 / -77777777 / -FFFFFFFF | -1 / -1 / -1 |
| _10 | -11110110 / -77777766 / -FFFFFFF6 | -1010 / -12 / -A |
| _0.5 | -11111111.1 / -77777777.4 / -FFFFFFFF.8 | -0.1 / -0.4 / -0.8 |

In numerical_systems.cpp, negative formatting computes base^c + decimal, with
c rounded up to a multiple of eight, then writes another minus sign. For _1
this yields 255 then -11111111 in binary. This statically explains the observed
complement-like output; it is not ordinary signed-magnitude formatting.
The same pattern exists in direct, scientific-mantissa and exponent branches.
Positive 0, 1, 10 and 0.5 produce the expected ordinary base representations.

For 0.001 the binary output includes *10^-11110111. The exponent magnitude
11110111 is binary 247, not the expected small magnitude of a normalized binary
exponent near -10. The negative-exponent path also constructs a complement
before printing a minus sign. This needs dedicated scientific-format tests;
do not condemn all scientific strings merely because their exponent is printed
in its own base (for example binary 1001 represents decimal 9).

## Parser and non-finite boundaries

The code contains numericalSystems() dispatch to binaryToDecimal(),
octalToDecimal() and hexadecimalToDecimal(), but static existence of these
functions does not prove the public parser reaches them with an intact token.
The first runtime loss of B1010/O12/H10 has not yet been instrumented.
binaryToDecimal() also contains a reverse-copy loop leaving i=-1 followed by
a loop indexing binary2[i]; this is a separate static out-of-bounds risk that
must be isolated, not assumed to explain every prefix result.

The original backlog deliberately left non-finite policy undecided. Real-axis
targets such as positive infinity plus positive infinity imply positive infinity,
but the engine also supports complex arithmetic, undefined products and signed
zeros. Specify their domain boundaries before introducing global special cases.

## Acceptance gate

1. Fix one demonstrated cause at a time, without private ATC 3.0 code.
2. Add focused tests with independent expected values, not captured bad outputs.
3. Preserve Windows-1252, C++17 and v141_xp compatibility.
4. Rebuild x86/x64 and rerun focused tests plus the complete regression suite.
5. Revalidate Linux sanitizers and native XP for new engine changes.
6. Record deliberate output corrections; do not infer release approval from
   this reproduction audit. No engine changes were made during this triage.

## Follow-up: base literal parsing

After the initial triage, the user confirmed the marker semantics. Independent
targets are B1010=10, O12=10 and H10=16. Corrections remain in the isolated
worktree; they are not part of the earlier approved 3f0725b checkpoint.

Debugger evidence on the unmodified x64 binary:

- manageExpression enters with B1010+0 and exits with B*1010+0.
- A data watchpoint captures the first '*' write in manageExpression<double>,
  offset +0x2823 (instruction at the original module RVA 0xb6e73).
- numericalSystems<double> subsequently receives only "B" and returns 0.
- Guarding this pass exposes a duplicate split in initialProcessor<double>;
  its write was also captured with a data watchpoint.
- arithSolver's variable-name processing truncates fractional base literals at
  their decimal point. Numeric base markers must bypass that variable path.
- verifyNumber includes '_' and 'E'; it must not be used to decide that a unary
  '_' alone finishes a factor in implicit multiplication.
- H1E is already H(1*10^(0)) at manageExpression entry: decimal scientific
  normalization must leave hexadecimal E digits intact.

The implementation protects base tokens in both coefficient passes, in implicit
multiplication, and in decimal-exponent normalization. It also resets the reverse
digit index before conversion and bounds fractional-copy reads in all three base
converters. No replacement parser or private ATC 3.0 code is used.

tests/run-atc-base-literals.py exercises 29 cases in each of double and
multiprecision modes, separately from the unchanged historical 376 checks.
It includes integer/fractional literals, external unary minus, mixed bases,
hexadecimal A/E digits, precedence and ordinary-expression/solver controls.
New engine changes require new Linux and native XP runs. Negative base output,
non-finite arithmetic, and the broader SI-prefix grammar remain separate items.

Final Windows validation of this local patch: Release x64 and Win32 v141_xp
builds PASS; focused tests 58/58 and historical All 376/376 on each architecture,
with no orphan processes in either final run. Expectations and historical counts
are unchanged. This validates the covered literal cases, not every grammar edge.

## Follow-up: signed base output and scientific precision

The negative-output complement construction is now replaced by magnitude
conversion, with the existing formatting supplying the sign once. The same
correction applies to negative scientific exponents in binary, octal and hex.
The original _1, _2 and _12 examples now produce -1/-1/-1, -10/-2/-2 and
-1100/-14/-C respectively, including the user's bp12bp... forms.

An initial strict rational-oracle run after the sign fix passed 32/38 cases.
The six failures demonstrated an independent inherited scientific precision
problem: reconstructing the mantissa from fractional logarithms changed exact
dyadic values into approximations, even for positive inputs. The implementation
now scales the original value with ldexp in the active type (base 2/8/16 shifts
1/3/4), retaining the computed integer exponent and range-checking its conversion.
No additional decimal places or new output digit budget was introduced.

The dedicated suite tests 22 cases in each precision mode (44 logical checks),
with three independently decoded rational base values per case, console/history
agreement, and 12 byte-identical ordinary positive controls against the preceding
validated binary. Exact integer/dyadic targets remain exact; the original 1e-5
relative tolerance for non-dyadic values is unchanged. Three new ordinary positive
cases expanded the original 38-case probe to 44 rather than replacing failures.

Both architectures passed 44/44 signed-output checks and 58/58 literal checks.
Both final All runs passed 376/376, without orphan processes or recorded failures,
crashes, timeouts or infrastructure errors.
These local changes are not committed and need new Linux and native XP validation.
Non-finite arithmetic policy and broader SI-prefix parsing remain open.

## Follow-up: legacy SI prefixes and small-value preservation

The existing grammar supports the 20 legacy SI prefixes, including Pk, Pda,
fractional coefficients, ordinary operators and persisted-variable controls.
No new prefixes or ATC 3.0 implementation were added. A baseline probe passed
107/114 checks on each Windows architecture; all seven failures are preserved.

CDB demonstrates that Pf reaches prefToNumber as the correct f prefix and
produces 1e-15 before roundSolution<double>. The latter changes that value to
zero solely because its absolute decimal exponent is -15/-16. The generic
final-expression call is removed: small magnitude is not evidence of round-off.
The same check covers small plain numeric literals and imaginary components.

prefToNumber<T> also deduced double for its old pot(10.0, exponent, 1) calls.
Selecting T alone exposed smaller generic-power residuals, so SI factors now
use bounded integer multiplication in T and one reciprocal for negative powers.
The fixed 50-decimal tests retain their original mathematical expectations.
Default multiprecision scientific formatting additionally converted T to double;
it now streams the active type, with the same 15 fractional mantissa digits.

Removing blanket zeroing revealed two previously hidden residuals in All:
sinc(1), and a real negative base raised to an integer with a spurious imaginary
component. The initial All passed 374/376 on both architectures, not approved.
The corrections use exact normalized-sinc zeros at nonzero real integers and
the real power path for finite negative bases and finite integer exponents.
Fractional powers and complex arguments remain on the complex path. INF/NaN
policy has not been changed. No historical expectations or deadlines changed.

The final dedicated suite contains 80 inputs in each of double/multiprecision
modes (160 checks), including real and imaginary tiny values, sinc and powers.
It is separate from the unchanged historical 376 checks. The earlier 114 and
134-check probes are retained rather than silently replaced by the larger set.
New Linux/sanitizer and native XP validation is still required for these edits.

Final Windows validation: Release x64/Win32 v141_xp builds PASS; each architecture
passes SI/control 160/160, base literals 58/58, signed-base output 44/44 and
historical All 376/376 (369 processes plus 7 auxiliary checks). SI text outputs
match across architectures. No final failures, crashes, timeouts, infrastructure
errors or runner-owned orphan processes. Win32 retains the pre-existing C4018
warning at main_aux_processor.cpp:510. git diff --check passes. No commit/push.
