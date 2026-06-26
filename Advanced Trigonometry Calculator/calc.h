#include "precision_types.h"

int summatorial(int integer);
template <typename T>T ln(T z);
template <typename T> T pot(T base, T exponent, int sig);
template <typename T> T re(T dividend, T divider);
template <typename T> T qu(T dividend, T divider);
template <typename T> T multi(T multip);
template <typename T> T quo(T quotient);
template <typename T> T fl(T number);
template <typename T> T returnDeciPart(T number);
template <typename T> T qfunc(T x);
template <typename T> T qfuncinv(T p);
template <typename T> T gerror(T q);
template <typename T> T gerrorinv(T e);
template <typename T> T gerrorc(T q);
template <typename T> T gerrorcinv(T a);
template <typename T> T arcfact(T f);
template <typename T> T arg(T a, T b);
template <typename T> T fact(T d);
template <typename T> T getValue();
template <typename T> T getPosValue();
template <typename T> T abs_complex(T real, T imaginary);
template <typename T> T confidenceLevelToZscore(T confidence_level);
void currentSettings();
template <typename T> void cotan(T x, T y);
template <typename T> void sec(T x, T y);
template <typename T> void cosec(T x, T y);
template <typename T> void cotanh(T x, T y);
template <typename T> void sech(T x, T y);
template <typename T> void cosech(T x, T y);
template <typename T> void sinc(T x, T y);
template <typename T> void arsinh(T x, T y);
template <typename T> void arcosh(T x, T y);
template <typename T> void artanh(T x, T y);
template <typename T> void arcoth(T x, T y);
template <typename T> void arsech(T x, T y);
template <typename T> void arcsch(T x, T y);
template <typename T> void arcosec(T x, T y);
template <typename T> void arcsec(T x, T y);
template <typename T> void arcotg(T x, T y);
template <typename T> void complex_log(T a, T b);
template <typename T> 
void qu_complex(T dividend, T dividendI, T divider, T dividerI);
template <typename T> void re_complex(T dividend, T dividendI, T divider, T dividerI);
template <typename T> void complex_cos(T x, T y);
template <typename T> void complex_sin(T x, T y);
template <typename T> void complex_tan(T x, T y);
template <typename T> void complex_cosh(T x, T y);
template <typename T> void complex_sinh(T x, T y);
template <typename T> void complex_tanh(T x, T y);

template <typename T> void complex_asin(T x, T y);
template <typename T> void complex_acos(T x, T y);
template <typename T> void complex_atan(T x, T y);
void roundSolution();

template <typename T> 
void solveSystem(T** values, T** valuesI);
template <typename T> void rearrangeValues(T** valInd, T** values, T** valuesI, T** valuesF, T** valuesFI);
template <typename T> void getSolutions(T** values, T** valuesI);
template <typename T> void sum(T numR, T numI, T denR, T denI);
template <typename T> void subtraction(T numR, T numI, T denR, T denI);
template <typename T> void multiplication(T numR, T numI, T denR, T denI);
template <typename T> void division(T numR, T numI, T denR, T denI);

template <typename T>
int exponentiation(T a, T b, T c, T d, int sig);
template <typename T> T rt(T radicand, T degree, int sig);
template <typename T>
void trianglesRectanglesSolver();
void arithmeticMatrixSolver();
void financialCalculations();
template <typename T>
void geometryCalculations();
void statisticsCalculations();
void physicsCalculations();
template <typename T>

void unitConversions();