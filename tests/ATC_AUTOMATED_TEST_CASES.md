# Advanced Trigonometry Calculator - automated test cases

Source reference: https://advantrigoncalc.sourceforge.io/full_user_guide/index.html

This suite is designed as a smoke/regression layer for ATC 2.1.7. It focuses on
safe command-line tests that can run repeatedly without opening GUI features,
changing the PC state, or requiring user interaction.

## Goals

- Confirm that the core calculator still solves arithmetic, constants, logs and
  trigonometric expressions.
- Confirm decimal precision formatting (`dp...dp...`) in both `double` and
  Boost `mp_float` modes.
- Confirm the persistent transition between `double` and `mp_float` across ATC
  process restarts.
- Catch regressions like `dp50dppi` returning zero or a rounded `double`
  approximation while higher precision is enabled.
- Keep the runner safe: no shutdown, restart, timer, alarm, calendar GUI or PC
  control commands.
- Track source-level coverage for interactive prompt ergonomics such as Tab
  completion and history navigation without requiring a live console session.

## Automated coverage

For `solve equation(...)`, the SourceForge implementation confirms that values
separated by `\` are interpreted as polynomial coefficients from the highest
degree term down to the constant term. ATC also accepts simple textual
polynomials such as `x^7-12`, which are normalized to that coefficient form
before reaching the solver.

| Area | Case | Command | Expected |
| --- | --- | --- | --- |
| Arithmetic | integer addition | `1+1` | `#n=2` |
| Arithmetic | operator precedence | `2+3*4` | `#n=14` |
| Arithmetic | parentheses | `(2+3)*4` | `#n=20` |
| Arithmetic | division | `8/4` | `#n=2` |
| Arithmetic | power | `2^10` | `#n=1024` |
| Arithmetic | negative marker | `_6+2` | `#n=-4` |
| Arithmetic | square root | `sqrt(9)` | `#n=3` |
| Arithmetic | cube root | `cbrt(27)` | `#n=3` |
| Constants | pi basic value | `pi` | starts with `3.14159` |
| Trigonometry | sine identity | `sin(pi/2)` | `#n=1` |
| Trigonometry | cosine identity | `cos(0)` | `#n=1` |
| Trigonometry | tangent identity | `tan(pi/4)` | `#n=1` |
| Trigonometry | secant identity | `sec(0)` | `#n=1` |
| Trigonometry | cosecant identity | `cosec(pi/2)` | `#n=1` |
| Trigonometry | cotangent identity | `cotan(pi/4)` | `#n=1` |
| Trigonometry | inverse sine | `asin(1)` | `#n=1.5708` |
| Trigonometry | inverse cosine | `acos(1)` | `#n=0` |
| Trigonometry | inverse tangent | `atan(1)` | `#n=0.785398` |
| Hyperbolic | sine hyperbolic zero | `sinh(0)` | `#n=0` |
| Hyperbolic | cosine hyperbolic zero | `cosh(0)` | `#n=1` |
| Hyperbolic | tangent hyperbolic zero | `tanh(0)` | `#n=0` |
| Hyperbolic | secant hyperbolic zero | `sech(0)` | `#n=1` |
| Hyperbolic | inverse hyperbolic cosine | `acosh(1)` | `#n=0` |
| Hyperbolic | inverse hyperbolic sine | `asinh(0)` | `#n=0` |
| Hyperbolic | inverse hyperbolic tangent | `atanh(0)` | `#n=0` |
| Hyperbolic | inverse hyperbolic secant | `asech(1)` | `#n=0` |
| Hyperbolic | inverse hyperbolic cosecant | `acosech(1)` | `#n=0.881374` |
| Hyperbolic | hyperbolic cotangent | `cotanh(1)` | `#n=1.31304` |
| Hyperbolic | inverse hyperbolic cotangent | `acotanh(2)` | `#n=0.549306` |
| Hyperbolic | hyperbolic cosecant | `cosech(1)` | `#n=0.850918` |
| Trigonometry | arc cosecant | `acosec(1)` | `#n=1.5708` |
| Trigonometry | arc secant | `asec(1)` | `#n=0` |
| Trigonometry | arc cotangent | `acotan(1)` | `#n=0.785398` |
| Digital signal processing | normalized sinc zero | `sinc(0)` | `#n=1` |
| Digital signal processing | normalized sinc at 1 | `sinc(1)` | `#n=0` |
| Digital signal processing | FFT impulse | `fft(1\0\0\0)` | four bins equal to `1` |
| Digital signal processing | FFT odd-length sequence | `fft(1\2\3)` | `6`, `-1.500000+0.866025i`, `-1.500000-0.866025i` |
| Digital signal processing | IFFT impulse | `ifft(1\0\0\0)` | four samples equal to `0.250000` |
| Digital signal processing | IFFT constant spectrum | `ifft(1\1\1\1)` | `x[0]=1`, remaining samples `0` |
| Logarithm | base 10 log | `log(100)` | `#n=2` |
| Logarithm | natural log | `ln(e)` | `#n=1` |
| Logarithm | custom base log | `logb2b(8)` | `#n=3` |
| Arithmetic | factorial operator | `5!` | `#n=120` |
| Arithmetic | inverse factorial | `afact(120)` | `#n=5` |
| Arithmetic | absolute value | `abs(_7)` | `#n=7` |
| Arithmetic | remainder | `100rest(3)` | `#n=1` |
| Arithmetic | integer quotient | `100quotient(3)` | `#n=33` |
| Arithmetic | custom root degree | `rtD4D(16)` | `#n=2` |
| Boolean constants | true | `true` | `#n=1` |
| Boolean constants | false | `false` | `#n=0` |
| Boolean constants | true in arithmetic | `true+1` | `#n=2` |
| Boolean constants | false in arithmetic | `false+1` | `#n=1` |
| Infinity constant | positive infinity | `INF` | `#n=INF` |
| Infinity constant | negative infinity | `_INF` | `#n=-INF` |
| Infinity constant | infinity quotient | `INF/INF` | `#n=1` |
| Implicit multiplication | number before pi | `2pi` | `#n=6.28319` |
| Implicit multiplication | pi before number | `pi2` | `#n=6.28319` |
| Implicit multiplication | number before Euler number | `2e` | `#n=5.43656` |
| Implicit multiplication | number before function | `2sin(pi/2)` | `#n=2` |
| Implicit multiplication | function result before number | `sin(pi/2)2` | `#n=2` |
| Implicit multiplication | number before parentheses | `2(3+4)` | `#n=14` |
| Implicit multiplication | adjacent parentheses | `(1+1)(2+3)` | `#n=10` |
| Implicit multiplication | parentheses before function | `(1+1)sin(pi/2)` | `#n=2` |
| Implicit multiplication | number before imaginary unit | `2i` | `#n=2i` |
| Implicit multiplication | parenthesized imaginary factor | `3(2i)` | `#n=6i` |
| Implicit multiplication | number before custom root | `2rtD4D(16)` | `#n=4` |
| Implicit multiplication | number before custom log base | `2logb2b(8)` | `#n=6` |
| Implicit multiplication | number before variable | `2x` with `x = 2` | `#n=4` |
| Implicit multiplication | variable before number | `x2` with `x = 2` | `#n=4` |
| Implicit multiplication | variable before parentheses | `x(4)` with `x = 2` | `#n=8` |
| Implicit multiplication | parentheses before variable | `(4)x` with `x = 2` | `#n=8` |
| Implicit multiplication | variable before pi | `xpi` with `x = 2` | `#n=6.28319` |
| Implicit multiplication | pi before variable | `pix` with `x = 2` | `#n=6.28319` |
| Implicit multiplication | variable before Euler number | `xe` with `x = 2` | `#n=5.43656` |
| Implicit multiplication | variable before function | `xsin(pi/2)` with `x = 2` | `#n=2` |
| Implicit multiplication | function before variable | `sin(pi/2)x` with `x = 2` | `#n=2` |
| Implicit multiplication | variable before imaginary unit | `xi` with `x = 2` | `#n=2i` |
| Implicit multiplication | parenthesized expression before variable | `(x+1)y` with `x = 2`, `y = 3` | `#n=9` |
| Implicit multiplication | adjacent variable fallback | `xy` with `x = 2`, `y = 3` and no `xy` | `#n=6` |
| Implicit multiplication | spaced variable fallback | `x y` with `x = 2`, `y = 3` and no `xy` | `#n=6` |
| Implicit multiplication | composite variable priority | `xy` with `xy = 11` | `#n=11` |
| Implicit multiplication | spaced composite variable priority | `x y` with `xy = 11` | `#n=11` |
| Variable names | reserved/function prefixes | `cosdata`, `tanbeta`, `maxvalue`, `avgvalue`, `logbook` | resolved as variables, not function calls |
| Variable names | long composite priority | `foobar` and `foo bar` with `foobar = 17` | `#n=17` |
| Matrices / lists | minimum | `min(3\_1\2)` | `#n=-1` |
| Matrices / lists | maximum | `max(3\_1\2)` | `#n=3` |
| Matrices / lists | average | `avg(2\4\6)` | `#n=4` |
| Matrices / lists | matrix variable minimum | `min(foo)` with `foo = 1 0:2 0*3 0:4 0` | `#n=1` |
| Matrices / lists | matrix variable maximum | `max(foo)` with `foo = 1 0:2 0*3 0:4 0` | `#n=4` |
| Matrices / lists | matrix variable average | `avg(foo)` with `foo = 1 0:2 0*3 0:4 0` | `#n=2.5` |
| Matrices / lists | row count, 2x3 matrix | `linsnum(foo)` with `foo = 1 0:2 0:3 0*4 0:5 0:6 0` | `#n=2` |
| Matrices / lists | column count, 2x3 matrix | `colsnum(foo)` with `foo = 1 0:2 0:3 0*4 0:5 0:6 0` | `#n=3` |
| Matrices / lists | row count, 3x2 matrix | `linsnum(bar)` with `bar = 1 0:2 0*3 0:4 0*5 0:6 0` | `#n=3` |
| Matrices / lists | column count, 3x2 matrix | `colsnum(bar)` with `bar = 1 0:2 0*3 0:4 0*5 0:6 0` | `#n=2` |
| Matrices / lists | get matrix rows | `getlins(foo)` | prints the 2x3 matrix values |
| Matrices / lists | get matrix columns | `getcols(bar)` | prints the 3x2 matrix values |
| Matrices / lists | get matrix row range | `getlins(foo\0\0)` | prints the first row of `foo` |
| Matrices / lists | get matrix column range | `getcols(foo\1\2)` | prints the second and third columns of `foo` |
| Matrices / lists | non-square matrix minimum | `min(bar)` | `#n=1` |
| Matrices / lists | non-square matrix maximum | `max(bar)` | `#n=6` |
| Matrices / lists | non-square matrix average | `avg(bar)` | `#n=3.5` |
| Matrices / Matrizes | matrix addition with same variable | `foo+foo` | doubled matrix |
| Matrices / Matrizes | matrix subtraction with same variable | `foo-foo` | zero matrix |
| Matrices / Matrizes | matrix multiplication with same variable | `foo*foo` | same result as `foo^2` |
| Matrices / Matrizes | matrix power | `foo^2` | matrix square |
| Matrices / Matrizes | matrix transpose shortcut | `foo^T` | transposed matrix |
| Matrices / Matrizes | matrix rank shortcut | `foo^R` | `#n=3` |
| Matrices / Matrizes | create constant 2x2 matrix | `create matrix(foo\2\2\3)` | prints a 2x2 matrix and stores `foo 3 0:3 0*3 0:3 0` |
| Matrices / Matrizes | create expression 2x3 matrix | `create matrix(bar\2\3\1+2)` | prints a 2x3 matrix and stores `bar 3 0:3 0:3 0*3 0:3 0:3 0` |
| Variables | starts with previously restricted `d` | `data+1` with `data = 7` | `#n=8` |
| Variables | contains previously restricted `e` | `energy+1` with `energy = 7` | `#n=8` |
| Variables | contains previously restricted `b` | `beta+1` with `beta = 7` | `#n=8` |
| Variables | starts with previously restricted `a` | `alpha+1` with `alpha = 7` | `#n=8` |
| Variables | starts with previously restricted `m` | `matx+1` with `matx = 7` | `#n=8` |
| Variables | long matrix-like name | `matrixvar+1` with `matrixvar = 7` | `#n=8` |
| Variables | function-name prefix without exact collision | `sinx+1` with `sinx = 7` | `#n=8` |
| Variables | reserved-prefix name without exact collision | `bvar+1` with `bvar = 7` | `#n=8` |
| Statistics / probability | gaussian error | `gerror(0)` | `#n=0` |
| Statistics / probability | complementary gaussian error | `gerrorc(0)` | `#n=1` |
| Statistics / probability | Q function | `qfunc(0)` | `#n=0.5` |
| Statistics / probability | inverse gaussian error | `gerrorinv(0)` | `#n=0` |
| Statistics / probability | inverse complementary gaussian error | `gerrorcinv(1)` | `#n=0` |
| Statistics / probability | inverse Q function | `qfuncinv(0.5)` | `#n=0` |
| Sorting | ascending numeric order | `ascending order(3\1\2)` | exports `1+0i, 2+0i, 3+0i` |
| Sorting | descending numeric order | `descending order(3\1\2)` | exports `3+0i, 2+0i, 1+0i` |
| Sorting | ascending order with negative values | `ascending order(_3\1\_2\0)` | exports `-3+0i, -2+0i, 0+0i, 1+0i` |
| Sorting | descending order with negative values | `descending order(_3\1\_2\0)` | exports `1+0i, 0+0i, -2+0i, -3+0i` |
| Sorting / Ordenacao | ascending ASCII order | `ascii order` with `banana\apple\cherry`, then `0`, `0` | prints `apple`, `banana`, `cherry` |
| Sorting / Ordenacao | descending ASCII order | `inverse ascii order` with `banana\apple\cherry`, then `0`, `0` | prints `cherry`, `banana`, `apple` |
| Polynomial tools | roots to polynomial | `roots to polynomial(2\3)` | exports `(1+0i)x^2+(_5+0i)x^1+(6+0i)` |
| Polynomial tools | roots to cubic polynomial | `roots to polynomial(2\7\12)` | exports `(1+0i)x^3+(_21+0i)x^2+(122+0i)x^1+(_168+0i)` |
| Polynomial tools | roots to polynomial with complex conjugates | `roots to polynomial(6.5i\_6.5i)` | exports `(1+0i)x^2+(0+0i)x^1+(42.25+0i)` |
| Polynomial tools | roots to polynomial with shifted complex conjugates | `roots to polynomial(1+2i\1-2i)` | exports `(1+0i)x^2+(_2+0i)x^1+(5+0i)` |
| Polynomial tools | roots to polynomial with zero root | `roots to polynomial(0\1\2)` | exports `(1+0i)x^3+(_3+0i)x^2+(2+0i)x^1+(0+0i)` |
| Export prompts | decline sorting export | `ascending order(3\1\2)`, then `0` | prints the result and does not print export-success text |
| Export prompts | decline roots-to-polynomial export | `roots to polynomial(2\3)`, then `0` | prints the result and does not print export-success text |
| Export prompts | decline simplify-polynomial export | `simplify polynomial((x-2)*(x-3))`, then `0` | prints the result and does not print export-success text |
| Export prompts | decline equation export | `solve equation(x+2)`, then `0` | prints the result and does not print export-success text |
| Polynomial tools | simplify identity | `simplify polynomial(x)` | `(1+0i)x^1+(0+0i)` |
| Polynomial tools | simplify linear polynomial | `simplify polynomial(x+1)` | `(1+0i)x^1+(1+0i)` |
| Polynomial tools | simplify and combine terms | `simplify polynomial(x+x+1)` | `(2+0i)x^1+(1+0i)` |
| Polynomial tools | simplify quadratic polynomial | `simplify polynomial(x^2-5*x+6)` | `(1+0i)x^2+(_5+0i)x^1+(6+0i)` |
| Polynomial tools | simplify binomial product | `simplify polynomial((x-2)*(x-3))` | `(1+0i)x^2+(_5+0i)x^1+(6+0i)` |
| Polynomial tools | simplify square binomial | `simplify polynomial((x+1)*(x+1))` | `(1+0i)x^2+(2+0i)x^1+(1+0i)` |
| Polynomial tools | simplify scaled binomial product | `simplify polynomial((2*x+1)*(x-3))` | `(2+0i)x^2+(_5+0i)x^1+(_3+0i)` |
| Polynomial tools | simplify complex conjugate product | `simplify polynomial((x-1)(x+6.5i)(x-6.5i))` | `(1+0i)x^3+(_1+0i)x^2+(42.25+0i)x^1+(_42.25+0i)` |
| Polynomial tools | simplify complex product with zero root | `simplify polynomial((x-1)(x-0)(x-0.5i)(x-2))` | `(1+0i)x^4+(_3+_0.5i)x^3+(2+1.5i)x^2+(0+_1i)x^1+(0+0i)` |
| Equation solver | quadratic, two real roots | `solve quadratic equation(1\_5\6)` | `x1=3`, `x2=2` |
| Equation solver | quadratic, repeated root | `solve quadratic equation(1\_2\1)` | `x1=1`, `x2=1` |
| Equation solver | quadratic, complex roots | `solve quadratic equation(1\2\5)` | `x1=-1+2i`, `x2=-1-2i` |
| Equation solver | quadratic, symmetric real roots | `solve quadratic equation(1\0\_4)` | `x1=2`, `x2=-2` |
| Equation solver | 2x2 equations system | `solve equations system(1\1\5;1\_1\1)` | `x1=3`, `x2=2` |
| Equation solver | alternate 2x2 equations system | `solve equations system(2\1\5;1\_1\1)` | `x1=2`, `x2=1` |
| Equation solver | coefficient-list quartic fast path | `solve equation(1\2\3\4\5)` | four complex roots |
| Equation solver | coefficient-list degree 30 fast path | `solve equation(1\2\...\31)` | 30 complex/real roots |
| Equation solver | implicit product, two real roots | `solve equation((x-1)(x-2))` | `x1=2`, `x2=1` |
| Equation solver | implicit product, three real roots | `solve equation((x-1)(x-2)(x-6))` | `x1=6`, `x2=2`, `x3=1` |
| Equation solver | implicit product with zero root | `solve equation((x-0)(x-1)(x-2))` | `x1=2`, `x2=1`, `x3=0` |
| Equation solver | implicit product with complex roots | `solve equation((x-1)(x+6.5i)(x-6.5i))` | `x1=1`, `x2=-6.5i`, `x3=+6.5i` |
| Equation solver | implicit product with one complex root | `solve equation((x-1)(x-2)(x+6.9i))` | `x1=2`, `x2=1`, `x3=-6.9i` |
| Equation solver | invalid implicit product rejection | `solve equation((x-1)(x-2)(x6.9))` | clear fast-path rejection instead of blank/unsafe solving |
| Equation solver | internal complex quadratic | `solve equation((1+0i)x^2+(0+0i)x^1+(42.25+0i))` | roots `-6.5i`, `+6.5i` |
| Equation solver | internal complex polynomial with zero root | `solve equation((1+0i)x^4+(_3+_0.5i)x^3+(2+1.5i)x^2+(0+_1i)x^1+(0+0i))` | roots `2`, `1`, `0`, `0.5i` |
| Equation solver | expanded roots 1 to 20 | expanded degree-20 internal polynomial | roots `20` down to `1` |
| Equation solver | rounded expanded roots 1 to 30 | rounded degree-30 internal polynomial | roots `30` down to `1` |
| Equation solver | linear equation export report | `solve equation(x+2)` | exports `x1=-2` to a temporary `.txt` |
| Equation solver | cubic coefficient equation export report | `solve equation(1\8\1\_42)` | exports `x1=2`, `x2=-3`, `x3=-7` |
| Equation solver | quadratic textual polynomial export report | `solve equation(x^2-5*x+6)` | exports `x1=3`, `x2=2` to a temporary `.txt` |
| Equation solver | 7th degree textual polynomial export report | `solve equation(x^7-12)` | exports 7 real/complex roots to a temporary `.txt` |
| Function study | rational even function | `function study((1-x^2)/(x^2-4))` | domain, zeros, asymptotes, even symmetry, derivative and minimum |
| Function study | rational odd function | `function study(x/(x^2-9))` | domain, zero, asymptotes, odd symmetry and numerator/denominator extraction |
| Function study | polynomial parabola minimum | `function study(x^2)` | derivative root at `0`, codomain `[0,+inf[` and minimum at `(0,0)` |
| Function study | polynomial parabola maximum | `function study(_x^2)` | derivative root at `0`, codomain `]-inf,0]` and maximum at `(0,0)` |
| Graphing | graph settings display | `graph settings` then `0` | prints current graph settings without mutating them |
| Graphing | non-interactive linear graph smoke | `graph(x)` with redirected input/output | prints graph non-interactive summary and current settings, then exits |
| Graphing | graph left/right navigation simulation | `graph(x)` with `ATC_GRAPH_NAVIGATION_TEST=RRRLLR` | prints deterministic navigation index and x value |
| Graphing | graph settings mutation | `graph settings` with manual X/Y values | writes the expected `graph.txt` contents |
| Date/time / Tempo | current time format | `time` | prints weekday, month, day, year and `hh mm ss` format |
| Date/time | day of week regression date | `day of week(y2026m6d20)` | `Saturday` |
| Date/time | day of week millennium | `day of week(y2000m1d1)` | `Saturday` |
| Date/time | day of week leap day | `day of week(y2024m2d29)` | `Thursday` |
| Date/time | day of week alternate argument order | `day of week(d20m6y2026)` | `Saturday` |
| Date/time / Tempo | fixed year calendar | `calendar(2026)` | prints all months from January to December |
| Date/time / Tempo | fixed time difference | `time difference calculations` with two fixed timestamps | `1 days, 1 hours, 2 minutes and 3 seconds`, `90123 seconds` |
| Date/time / Tempo | enable actual time response | `actual time response`, then `1` | writes `actualTime.txt = 1` |
| Date/time / Tempo | disable actual time response | `actual time response`, then `0` | writes `actualTime.txt = 0` |
| TXT / command bridge | solve txt without predefined file | `solve txt` with no `predefinedTxt.txt` | prints `The file was not yet predefined` |
| TXT / command bridge | predefine txt path | `predefine txt`, then a fixture path | writes that path to `predefinedTxt.txt` |
| File/folder commands / Ficheiros-pastas | predefine txt quoted dragged path | `predefine txt`, then `"C:\Temp\atc fixture with spaces.txt"` | strips quotes and writes the normalized path |
| File/folder commands / Ficheiros-pastas | open txt missing file | `open txt("C:\Temp\atc-regression-missing-file.txt")` | follows the safe missing-file path without launching Notepad |
| File/folder commands / Ficheiros-pastas | solve txt missing path abbreviation | `solve txt(missing)` with fixture `pathName.txt` | confirms path-abbreviation lookup reads `pathName.txt` and reports missing abbreviation |
| File/folder commands / Ficheiros-pastas | ATC data folder target | filesystem fixture check | confirms the ATC data folder exists |
| File/folder commands / Ficheiros-pastas | Scripts examples folder target | filesystem fixture check | confirms the folder opened by `scripts examples` exists |
| File/folder commands / Ficheiros-pastas | Source code folder target | filesystem fixture check | confirms the folder opened by `source code` exists |
| File/folder commands / Ficheiros-pastas | Strings folder target | filesystem fixture check | confirms the folder opened by `strings` exists |
| File/folder commands / Ficheiros-pastas | To solve folder target | filesystem fixture check | confirms the folder opened by `to solve` exists |
| File/folder commands / Ficheiros-pastas | User functions folder target | filesystem fixture check | confirms the folder opened by `user functions` exists |
| File/folder commands / Ficheiros-pastas | installed user guide PDF | filesystem fixture check | confirms the installed user guide PDF exists |
| File/folder commands / Ficheiros-pastas | installed license/about files | filesystem fixture check | confirms `License.txt` and `About execution of application.txt` exist |
| File/folder commands / Ficheiros-pastas | installed examples/source snapshots | filesystem fixture check | confirms a script example and source-code snapshot exist |
| TXT / command bridge | atc over cmd smoke | `atc over cmd`, then `2+2`, `exit` | processes the redirected command and prints `#n=4` |
| Variables/results / Gestao | see variables | `see variables` with fixture `variables.txt` | prints stored variables |
| Variables/results / Gestao | renamed variables | `renamed variables` with fixture `renamedVar.txt` | prints variable renaming data |
| Variables/results / Gestao | see strings | `see strings` with fixture `stringVariable.txt` | prints stored string names |
| Variables/results / Gestao | see abbreviations | `see abbreviations` with fixture `pathName.txt` | prints stored abbreviations |
| Variables/results / Gestao | empty readback states | `see variables`, `renamed variables`, `see strings`, `see abbreviations`, `see results` with empty fixture files | prints the expected empty-state messages |
| Variables/results / Gestao | eliminate variables | `eliminate variables` | clears `variables.txt` and `renamedVar.txt` |
| Variables/results / Gestao | eliminate abbreviations | `eliminate abbreviations` | clears `pathName.txt` |
| Variables/results / Gestao | see and eliminate results | `atc over cmd`, then `2+2`, `see results`, `eliminate results`, `see results`, `exit` | prints `#0=4`, clears results, then reports no calculated result |
| Persistent settings / Configuracoes | mode | `mode`, then `3` | writes `mode.txt = 3` |
| Persistent settings / Configuracoes | numerical systems | `numerical systems`, then `1` | writes `numSystems.txt = 1` |
| Persistent settings / Configuracoes | SI prefixes | `si prefixes`, then `1` | writes `siPrefixes.txt = 1` |
| Persistent settings / Configuracoes | verbose resolution | `verbose resolution`, then `1` | writes `verboseResolution.txt = 1` |
| Persistent settings / Configuracoes | cleaned verbose calculation trace | `2+3*4` with `verboseResolution.txt = 1` | prints user-facing processor steps without internal menu/input noise |
| Persistent settings / Configuracoes | actual time response | `actual time response`, then `1` | writes `actualTime.txt = 1` |
| Persistent settings / Configuracoes | dimensions | `dimensions`, then `40`, `120` | writes `MODE con cols=120 lines=40` |
| Persistent settings / Configuracoes | window | `window`, then `10`, `20`, `500`, `600` | writes window position and size |
| Persistent settings / Configuracoes | higher precision inline enable | `higher precision(1)` | writes `higherPrecision.txt = 1` without prompting |
| Persistent settings / Configuracoes | current settings readback | `current settings` with prepared settings files | prints persisted mode, toggles, colors, window and dimensions |
| Interactive menus / Menus interativos | mode invalid retry | `mode`, then `9`, `2` | rejects invalid option and writes `mode.txt = 2` |
| Interactive menus / Menus interativos | numerical systems invalid retry | `numerical systems`, then `9`, `0` | rejects invalid option and writes `numSystems.txt = 0` |
| Interactive menus / Menus interativos | SI prefixes invalid retry | `si prefixes`, then `9`, `0` | rejects invalid option and writes `siPrefixes.txt = 0` |
| Interactive menus / Menus interativos | verbose resolution invalid retry | `verbose resolution`, then `9`, `0` | rejects invalid option and writes `verboseResolution.txt = 0` |
| Interactive menus / Menus interativos | actual time response invalid retry | `actual time response`, then `9`, `0` | rejects invalid option and writes `actualTime.txt = 0` |
| Interactive menus / Menus interativos | higher precision interactive enable | `higher precision`, then `1` | writes `higherPrecision.txt = 1` |
| Interactive menus / Menus interativos | higher precision inline disable | `higher precision(0)` | writes `higherPrecision.txt = 0` without prompting |
| Interactive menus / Menus interativos | higher precision invalid retry | `higher precision`, then `9`, `1` | rejects invalid option and writes `higherPrecision.txt = 1` |
| App environment / Ambiente UI | enable ATC intro | `enable atc intro` | writes `onStart.txt = enableatcintro` |
| App environment / Ambiente UI | disable ATC intro | `disable atc intro` | creates `aboutDisabled.txt` |
| Windows 11 console behavior | intro default-disable branch | source check | confirms `RtlGetVersion`, build `>= 22000` and `shouldDisableATCIntroByDefault()` are present |
| Windows 11 console behavior | ANSI color mapping | source check | confirms Win32 color order maps aqua/cyan correctly instead of ANSI yellow |
| Windows 11 console behavior | new ATC instance commands | source check | confirms `new tab`, `new instance`, `new atc tab`, `new atc instance`, `wt.exe new-tab` and `cmd.exe` fallback |
| Interactive prompt | Tab autocomplete vocabulary | source check | confirms mathematical functions, solver commands, settings commands and command aliases are exposed to completion |
| Interactive prompt | dynamic user functions | source check | confirms `User functions` entries can be suggested as `atc_<name>(` completions |
| Interactive prompt | ambiguous completion cycling | source check | confirms repeated Tab can cycle possible matches instead of only printing a list |
| Interactive prompt | history navigation | source check | confirms Up/Down arrow handling and draft restoration while editing |
| App environment / Ambiente UI | clean history | `clean history` | removes previous history entries and records the cleanup command |
| App environment / Ambiente UI | clean | `clean` | exits successfully after clearing console |
| App environment / Ambiente UI | exit | `exit` | exits successfully and leaves an empty `exit.txt` marker |
| Precision | decimal places in double mode | `dp15dppi` | 15 decimal places |
| Precision | on-demand max precision prefix | `dp50dpmaxprecpi` | exact 50 decimal digits while keeping `higherPrecision.txt = 0` |
| Precision | double mode after max precision | `dp20dppi` after `dp50dpmaxprecpi` | returns the rounded double value, proving `maxprec` is temporary |
| Precision | on-demand max precision prefix for Euler number | `dp50dpmaxprece` | exact 50 decimal digits without changing persisted precision mode |
| Higher precision | 50 decimal pi | `dp50dppi` | exact 50 decimal digits |
| Higher precision | 50 decimal Euler number | `dp50dpe` | exact 50 decimal digits |
| Higher precision | fixed formatting | `dp50dp1+1` | `2.` plus 50 zeroes |
| Persistence | enable mp_float | `higherprecision(1)` | file contains `1` |
| Persistence | restart in mp_float | `dp50dppi` | exact 50 decimal digits |
| Persistence | disable mp_float | `higherprecision(0)` | file contains `0` |

## Manual or future automated coverage

These areas are documented in the user guide, but should not be run blindly by
the automated smoke runner until stable non-interactive command forms are
defined:

- App folder commands that open Explorer or editors.
- Long-running time features such as clock, timer, stopwatch and alarms.
- PC control commands such as shutdown, restart, suspend or lock.
- TXT detector / bridge commands that open shell windows, mutate the system
  PATH, or require a file-watcher scenario.
- `eliminate strings`, because it mutates the `Strings` folder through shell
  commands.
- Interactive `colors` mutation, because it uses `_getch()` rather than normal
  redirected input. `colors.txt` readback is covered through `current settings`.
- UI commands that open windows or files, such as `about`, `history`,
  `user guide`, `run atc`, `restart atc` and `auto adjust window`.

Manual/isolated app-environment coverage should verify that `about`, `history`
and `user guide` open the expected local files/windows, that `run atc` starts a
new ATC process, that `restart atc` restarts without losing persisted settings,
and that `auto adjust window` changes the console layout without corrupting
`window.txt` or `dimensions.txt`.
- Full interactive graph navigation with arrow keys, because it requires a real
  console input buffer.
- Interactive menus for statistics, arithmetic matrix solver, finance, physics and other
  module screens.
- Full `.txt` processing that opens the generated answer file, because it should
  use isolated fixture folders rather than the user's personal ATC folders.

## Isolated Coverage

Some high-side-effect commands are checked by
`tests/run-atc-isolated-coverage.ps1`. That script verifies command branches and
guard logic by source inspection, and executes only short safe smoke checks.
It currently covers:

- app environment branches: `auto adjust window`, `about`, `history`,
  `user guide`, `run atc`, `restart atc`
- app environment command targets: `auto adjust window` writes window and
  dimensions settings, `about` reads the about execution text, `history` opens
  `history.txt`, `user guide` opens the local PDF, and `run atc` /
  `restart atc` launch `atc.exe` with `restart atc` ending the current loop
- update/link branches: `check for updates`, `update`, `update x64`,
  `update portable`, `donate`, `atc facebook`, `atc sourceforge`
- update/link command targets: update checking reads
  `advantrigoncalc.sourceforge.io/atc_version.html`, update commands point to
  SourceForge x86/x64/ZIP downloads, and external link commands point to the
  SourceForge donation page, ATC Facebook page and ATC SourceForge project page
- reset/settings branches and `colors` persistence logic
- reset/settings command targets: reset commands write the expected
  `onStart.txt` markers, `now` variants relaunch `atc.exe`, startup reset
  branches delete the documented settings/data file groups, and `colors`
  persists a `color XY` command to `colors.txt`
- folder helpers and `open txt` guard logic
- folder/open-file command targets: folder commands point to the expected ATC
  data subfolders, `auto solve txt` waits for `SOLVE_NOW` before processing,
  and `open txt` normalizes quotes/spaces and only launches Notepad when the
  target file exists
- `eliminate strings` branch and duplicate-`fclose` regression guard
- TXT detector/command bridge branches and startup detector guard
- menu-driven calculation module branches
- graph key-buffer branch logic
- long-running time command branches plus a short `stopwatch(1)` smoke
- interactive prompt autocomplete vocabulary, ambiguous-match cycling, dynamic
  user function suggestions, and Up/Down history navigation

Latest isolated coverage result:

```text
Summary: 61 passed, 0 failed
```

## Runner

Run after building Release x64:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1
```

Or pass the executable explicitly:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-regression.ps1 -AtcExe ".\x64\Release\atc.exe"
```

The runner backs up and restores `higherPrecision.txt` and `aboutDisabled.txt`
from the normal ATC data folder:

```text
%USERPROFILE%\Pictures\Advanced Trigonometry Calculator
```

## Memory Stress Runner

Repeated memory measurements for heavier polynomial and equation solver paths
are kept separate from the functional smoke suite:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-atc-memory-stress.ps1 -Iterations 10
```

The runner records per-command elapsed time, peak working set and peak private
memory to CSV files under:

```text
tests\memory-stress-reports
```

It also backs up and restores `variables.txt` for the matrix-variable and
relaxed-variable-name tests.
