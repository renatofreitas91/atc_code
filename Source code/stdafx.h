
#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "resource.h"
#include <boost/math/special_functions/erf.hpp>
#include "calc.h"
#include <conio.h>
#include "atc_functions.h"
#define dIm 10000
#define DIM 5900
#define dim 1000
#define _USE_MATH_DEFINES
#include <math.h>
#include <dirent.h> 
#include <tchar.h>
#include <Shellapi.h>
#include <tlhelp32.h>
extern double expressionCoefR[dim], expressionCoefI[dim], X_k_R[dim], X_k_I[dim], lastElement, lastElementI, LastDividerR, LastDividerI, natureValue, lastDividerR, lastDividerI, returnedR, returnedI, xValuesR, xValuesI, mINF, INF, ansRV, ansIV, resultR, resultI, ans[DIM], ansI[DIM], resultFI, valInd[DIM][DIM], values[DIM][DIM], valuesI[DIM][DIM], valuesS[DIM][DIM], valuesSI[DIM][DIM], valuesF[DIM][DIM], valuesFI[DIM][DIM];
extern int xATC, yATC, colsATC, linesATC, widthATC, heightATC, Pressed, toSendCommand, countSplits, maxExponent, numSysNum, parentPol[DIM], replaceTimes, countEnters, countReturn, countBreak, Break, countUseReturn, countUseBreak, executedSolver, strStart, strEnd, rasf, processingOK, isFromMain, isFromSolveNow, verify, arG, feedbackValidation, isFromSolveNow, nPlaces, Mode, validVar, valid, valRenamedVar, synTest, count, continu, cleanhistory, rf, verified, verbose;
extern char dimensionsTxt[300], windowTxt[300], validChars[DIM], lastCommand[DIM], saveSimplified[DIM], saveSimplification[DIM], splitResult[200][200], answers[DIM], saveExpressionFF[DIM], saveArithTrig[DIM], saveExpressionF[DIM], OutputText[DIM], roots[DIM], charMaster[DIM], saveEquation[DIM], atcPath[DIM], calendarStr[DIM], revariable[DIM], varRename[DIM], expressionF[DIM], pathNAme[DIM], variableSTring[DIM], integral[DIM], usRFunctions[DIM], usRFuncTrans[DIM];
extern boolean fromEquationSolver, progress, starting, studyFunction, I_O, isDivisible, solveMultiPoly, polySimplifier, physics, equationSolverRunning, solverRunning, solving, retrySolver, retrySolver_2, retrySolver_3, returned, runningScript, equation_solver, poly;
double functionProcessor(char trigon[DIM], double result, double amplitude, int res);
double initialProcessor(char arithTrig[DIM], double result);
double arithSolver(char trigon1[DIM], double result);
double processVariable(char variable[DIM]);
double binaryToDecimal(char binary[DIM]);
double octalToDecimal(char octal[DIM]);
double hexadecimalToDecimal(char hexadecimal[DIM]);
double convertToNumber(char number[DIM]);
double main_core(char arithTrig[DIM], char fTrig[DIM], FILE *fout, char path[DIM], double result1, double result2, int isFromMain);
double main_sub_core(char arithTrig[DIM], FILE *fout, int verify, char path[DIM], int txt, char variable[DIM], int v, int j, double result1, double result2, int isFromMain, int var, int valGet, int command);
double solveNow(char toSolveNow[DIM], double result1, double result2);
double numericalSystems(char numSystem[DIM]);
double calcNow(char toCalc[DIM], double result1, double result2);
double atcProg(char expression[DIM]);
double calculateIntegral(double a, double b, char function[DIM]);
double math_processor(char expression[DIM]);
double solve(char equation[DIM]);
double solver(char expression[DIM]);
int variableValidator(char variable[DIM]);
int matrixToValues(char matrix[DIM], double result);
int atcProgramming(char script[DIM]);
int strlength(char stringV[DIM]);
int countOccurrences(char to_find[DIM], char expression[DIM]);
int deleteXOccurrences(char to_find[DIM], char expression[DIM], int x);
int getCorrectExponent(char expression[DIM], char maxExp[10], int maxExponent);
void getNumerationPol(char expression[DIM]);
void simplifyPolynomial(char expression[DIM]);
void split(char splitter[DIM], char data[DIM]);
void getDimensions();
void decrementPoly(int maxExponent, double resR, double resI);
void simpleSimplifyPolynomial(char expression[DIM]);
void variableController(char variable[DIM], double result);
void manageExpression(char arithTrig[DIM], double result1, double result2, int verify);
void decimalToBinary(double decimal, char path[DIM], int bp);
void decimalToOctal(double decimal, char path[DIM], int op);
void decimalToHexadecimal(double decimal, char path[DIM], int hp);
void prefixDeterminator(double n, char path[DIM]);
void DayofWeek(int d, int m, int y, char calendar[DIM]);
void Calendar(char yearCalendar[DIM], int year);
void fft(char values[DIM]);
void ifft(char values[DIM]);
void variableRenamer(char variable[DIM]);
void print(char data[DIM]);
void simplifyExpression(char expression[DIM]);
void pathNameController(char pathName[DIM], char path[DIM]);
void pathNameToPath(char pathName[DIM]);
void functionStudy(char function[DIM]);
void stringVariableController(char stringVariable[DIM], char string[DIM]);
void stringVariableToString(char stringVariable[DIM]);
void renamer(char expression[DIM]);
void variableToMultiply(char expression[DIM]);
void toMultiply(char expression[DIM], double result1, double result2);
void print(char text[DIM], double result1, double result2);
void sprint(char text[DIM], double result1, double result2);
void customFuncRenamer(char variable[DIM]);
void designGraph(char functionF[DIM]);
void replace(char toReplace[DIM], char replacement[DIM], char string[DIM]);
void replaceByIndex(char toReplace[DIM], char replacement[DIM], char string[DIM], int index);
void fmsum(int lins, int cols, double v[dim][dim], double u[dim][dim], double r[dim][dim], double vI[dim][dim], double uI[dim][dim], double rI[dim][dim]);
void fmsubt(int lins, int cols, double v[dim][dim], double u[dim][dim], double r[dim][dim], double vI[dim][dim], double uI[dim][dim], double rI[dim][dim]);
void fmmulr(int lins, int cols, double v[dim][dim], double r[dim][dim], double re, double vI[dim][dim], double rI[dim][dim], double reI);
void fmmulm(int lins2, int cols1, int lins1, int cols2, double v[dim][dim], double u[dim][dim], double r[dim][dim], double vI[dim][dim], double uI[dim][dim], double rI[dim][dim]);
void saveToReport(char report[DIM]);
double equationSolver(char equation[DIM]);
void solveQuadraticEquation(char arithTrig[DIM], double result1, double result2, int index);
void fmtranspose(int lins, int  cols, double vMS[dim][dim], double vMSI[dim][dim]);
void fmdeterminant(int lins, int  cols, double vMS[dim][dim], double vMSI[dim][dim]);
void startDetProcessing(char matrix[DIM]);
void rootsToPolynomial(char rooots[DIM]);
void fminverse(int lins, int  cols, double vMS[dim][dim], double vMSI[dim][dim]);
void fmpowerm(double vMS[dim][dim], double vMSI[dim][dim], int power, int lins, int cols);
void fmrank(int lins, int cols, double vMS[dim][dim], double vMSI[dim][dim]);
void sum_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]);
void sub_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]);
void multi_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]);
void div_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]);
void removeDuplPars(char expression[DIM]);
void removeTriplPars(char expression[DIM]);
void setWindow(int x, int y);
void setDimensions(int cols, int lines);
boolean simpleEvaluator(char expression[DIM]);
boolean advancedEvaluator(char expression[DIM]);
boolean isContainedVariable(char to_find[DIM], char string[DIM]);
boolean verifyPrefix(char prefix[DIM]);
boolean verifyNumberExpression(char number);
boolean processTxt(char path[DIM], int re);
boolean dataVerifier(char data[DIM], double result1, double result2, int comment, int verify);
boolean searchExtension(char filename[DIM], char extension[DIM]);
boolean commands(char arithTrig[DIM], char path[DIM], double result1, double result2);
boolean atcFunctions(char functionName[DIM]);
boolean isToWrite(char arith[DIM]);
boolean isCommand(char forTesting[DIM], char command[DIM]);
boolean readyToSolve(char paTh[DIM]);
boolean isEqual(char to_find[DIM], char string[DIM]);
boolean isContained(char to_find[DIM], char string[DIM]);
boolean isVariable(char variable[DIM]);
boolean isContainedByIndex(char to_find[DIM], char string[DIM], int index);
boolean verifyOperator(char operatorF);
boolean verifyNumerator(char number);
boolean isContainedInUserFunction(char variable[DIM]);
boolean verifyCoefficient(char number);
boolean verifyForNumber(char number);
boolean verifyFraction(char number);
boolean verifyMultiplication(char number);
char * getDerivative(char expression[DIM]);
char* convertToString(char* string);
char* convertToSpaces(char* data);