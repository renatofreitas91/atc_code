
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
#define DIM 3100
#define DIME 40000
#define dime 600
#define _USE_MATH_DEFINES
#include <math.h>
#include <dirent.h> 
#include <tchar.h>
#include <Shellapi.h>
#include <tlhelp32.h>
#include <cstdlib>
#include <cstring>
#include <fstream> 
#include <string>



extern double vectorR[dime][dime], vectorI[dime][dime], realRoots[dime], rootsR[dime], rootsI[dime], expressionCoefR[dime], expressionCoefI[dime], X_k_R[dime], X_k_I[dime], lastElement, lastElementI, LastDividerR, LastDividerI, natureValue, lastDividerR, lastDividerI, returnedR, returnedI, xValuesR, xValuesI, mINF, INF, ansRV, ansIV, resultR, resultI, ans[DIM], ansI[DIM], resultFI, valInd[DIM][DIM], values[DIM][DIM], valuesI[DIM][DIM], valuesS[DIM][DIM], valuesSI[DIM][DIM], valuesF[DIM][DIM], valuesFI[DIM][DIM];
extern int _rf, higherPrecision, previousAnsType, matrixMode, numVectorLines, numVectorCols, check4Vector, vectorType, nrRoots, xATC, yATC, colsATC, linesATC, widthATC, heightATC, Pressed, toSendCommand, countSplits, maxExponent, numSysNum, parentPol[DIM], replaceTimes, countEnters, countReturn, countBreak, Break, countUseReturn, countUseBreak, executedSolver, strStart, strEnd, rasf, processingOK, isFromMain, isFromSolveNow, verify, arG, feedbackValidation, isFromSolveNow, nPlaces, Mode, validVar, valid, valRenamedVar, synTest, count, continu, cleanhistory, rf, verified, verbose;
extern char expr[DIM], resp[DIM], respR[DIM], respI[DIM], matrixValue[DIM], returnCharArray[DIM], saveUserFunctionsRenamedVariablesTextFile[DIME], saveUserFunctionsVariablesTextFile[DIME], saveScriptRenamedVariablesTextFile[DIME], saveScriptVariablesTextFile[DIME], saveRenamedVariablesTextFile[DIME], saveRenamedTxtVariablesTextFile[DIME], actualTime[DIM], verboseRes[DIM], numSys[DIM], siPref[DIM], context[30], saveTxtVariablesTextFile[DIME], saveVariablesTextFile[DIME], ansMatrices[DIM][DIM], saveMatrixAns[DIM], matrixResult[DIM], vectorString[DIM], customFolderPath[DIM], saveATCPath[DIM], renamedVariable[DIM], dimensionsTxt[dime], windowTxt[dime], validChars[DIM], lastCommand[DIM], saveSimplified[DIM], saveSimplification[DIM], splitResult[dime][dime], answers[DIM], saveExpressionFF[DIM], saveArithTrig[DIM], saveExpressionF[DIM], OutputText[DIM], roots[DIM], charMaster[DIM], saveEquation[DIM], atcPath[DIM], calendarStr[DIM], revariable[DIM], varRename[DIM], expressionF[DIM], pathNAme[DIM], variableSTring[DIM], integral[DIM], usRFunctions[DIM], usRFuncTrans[DIM], expressionF2[DIM];
extern boolean useForVariables, notUseHigherPrecison, notSolved, variableControllersUsed, product, fromEquationSolver, progress, starting, studyFunction, I_O, isDivisible, solveMultiPoly, polySimplifier, physics, equationSolverRunning, solverRunning, solving, retrySolver, retrySolver_2, retrySolver_3, returned, runningScript, equation_solver, poly;
double functionProcessor(char trigon[DIM], double result, double amplitude, int res, char argNotNumber[DIM]);
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
int autoComplete(char * query);
int variableValidator(char variable[DIM]);
int matrixToValues(char matrix[DIM], double result);
int atcProgramming(char script[DIM]);
int strlength(char stringV[DIM]);
int countOccurrences(char to_find[DIM], char expression[DIM]);
int deleteXOccurrences(char to_find[DIM], char expression[DIM], int x);
int getCorrectExponent(char expression[DIM], char maxExp[10], int maxExponent);
int linesNumber(char values[DIM]);
int colsNumber(char values[DIM]);
void convertComplex2Exponential(double valueR, double valueI);
void getNumerationPol(char expression[DIM]);
void simplifyPolynomial(char expression[DIM]);
void split(char splitter[DIM], char data[DIM]);
double solveMath(char expression[DIM]);
void asciiOrder();
void inverseAsciiOrder();
void autoAdjustWindow();
void getDimensions();
void ascendingOrder(char values[DIM]);
void descendingOrder(char values[DIM]);
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
void check4Updates();
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
void fmsum(int lins, int cols, double v[dime][dime], double u[dime][dime], double r[dime][dime], double vI[dime][dime], double uI[dime][dime], double rI[dime][dime]);
void fmsubt(int lins, int cols, double v[dime][dime], double u[dime][dime], double r[dime][dime], double vI[dime][dime], double uI[dime][dime], double rI[dime][dime]);
void fmmulr(int lins, int cols, double v[dime][dime], double r[dime][dime], double re, double vI[dime][dime], double rI[dime][dime], double reI);
void fmmulm(int lins2, int cols1, int lins1, int cols2, double v[dime][dime], double u[dime][dime], double r[dime][dime], double vI[dime][dime], double uI[dime][dime], double rI[dime][dime]);
void saveToReport(char report[DIM]);
double equationSolver(char equation[DIM]);
void solveQuadraticEquation(char arithTrig[DIM], double result1, double result2, int index);
void fmtranspose(int lins, int  cols, double vMS[dime][dime], double vMSI[dime][dime], double mTransposeR[dime][dime], double mTransposeI[dime][dime]);
void fmdeterminant(int lins, int  cols, double vMS[dime][dime], double vMSI[dime][dime]);
void startDetProcessing(char matrix[DIM]);
void rootsToPolynomial(char rooots[DIM]);
void fminverse(int lins, int  cols, double vMS[dime][dime], double vMSI[dime][dime], double inverseR[dime][dime], double inverseI[dime][dime]);
void fmpowerm(double v[dime][dime], double vI[dime][dime], double r[dime][dime], double rI[dime][dime], int power, int lins, int cols);
int fmrank(int lins, int cols, double vMS[dime][dime], double vMSI[dime][dime]);
void sum_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]);
void sub_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]);
void multi_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]);
void div_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]);
void removeDuplPars(char expression[DIM]);
void removeTriplPars(char expression[DIM]);
void setWindow(int x, int y);
void setDimensions(int cols, int lines);
void convert2Vector(char arithTrig[DIM]);
void maximum(char values[DIM]);
void minimum(char values[DIM]);
void getCols(char data[DIM]);
void getLines(char data[DIM]);
void average(char values[DIM]);
void advancedSolver(char expression[DIM]);
boolean fmdivm(int lins2, int cols1, int lins1, int cols2, double v[dime][dime], double u[dime][dime], double vI[dime][dime], double uI[dime][dime]);
boolean simpleEvaluator(char expression[DIM]);
boolean verifyForNumbers(char number);
boolean advancedEvaluator(char expression[DIM]);
boolean isContainedVariable(char to_find[DIM], char string[DIM]);
boolean verifyPrefix(char prefix[DIM]);
boolean verifyNumberExpression(char number);
boolean processTxt(char path[DIM], int re);
boolean dataVerifier(char data[DIM], double result1, double result2, int comment, int verify);
boolean searchExtension(char filename[DIM], char extension[DIM]);
boolean commands(char expression[DIM], char path[DIM], double result1, double result2, FILE* save);
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
void GoToXY(int column, int line);
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
void getRealRoot(double real[dime], double  imaginary[dime], int maxExponent, double guess);
char* convertVector2String(double vectorR[dime][dime], double vectorI[dime][dime], int numLines, int numCols);
char * convert2Exponential(double value);
