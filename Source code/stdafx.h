
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
#include "atc_functions.h"
#define DIM 5500
#define dim 20
#define _USE_MATH_DEFINES
#include <math.h>
#include <dirent.h> 
extern double xValuesR, xValuesI, mINF, INF, ansRV, ansIV, resultR, resultI, ans[DIM], ansI[DIM], resultFI, valInd[DIM][DIM], values[DIM][DIM], valuesI[DIM][DIM], valuesS[DIM][DIM], valuesSI[DIM][DIM], valuesF[DIM][DIM], valuesFI[DIM][DIM];
extern int  maxLength, executedSolver, strStart, strEnd, rasf, processingOK, isFromMain, isFromSolveNow, verify, arG, feedbackValidation, isFromSolveNow, nPlaces, Mode, validVar, valid, valRenamedVar, synTest, count, continu, cleanhistory, rf, verified, verbose;
extern char atcPath[DIM], calendarStr[DIM], revariable[DIM], varRename[DIM], expressionF[DIM], pathNAme[DIM], variableSTring[DIM], integral[DIM], usRFunctions[DIM], usRFuncTrans[DIM];
extern boolean equationSolverRunning, solverRunning, solving, fromInitialProcessor;
double functionProcessor(char trigon[DIM], double result, double amplitude, double res);
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
double solver(char expression[DIM]);
double atcProg(char expression[DIM]);
int variableValidator(char variable[DIM]);
int matrixToValues(char matrix[DIM], double result);
void variableController(char variable[DIM], double result);
void manageExpression(char arithTrig[DIM], double result1, double result2, int verify);
void decimalToBinary(double decimal, char path[DIM], int bp);
void decimalToOctal(double decimal, char path[DIM], int op);
void decimalToHexadecimal(double decimal, char path[DIM], int hp);
void prefixDeterminator(double n, char path[DIM]);
void DayofWeek(int d, int m, int y, char calendar[DIM]);
void Calendar(char yearCalendar[DIM], int year);
void variableRenamer(char variable[DIM]);
void pathNameController(char pathName[DIM], char path[DIM]);
void pathNameToPath(char pathName[DIM]);
void stringVariableController(char stringVariable[DIM], char string[DIM]);
void stringVariableToString(char stringVariable[DIM]);
void renamer(char expression[DIM]);
void variableToMultiply(char expression[DIM]);
void toMultiply(char expression[DIM], double result1, double result2);
void print(char text[DIM], double result1, double result2);
void sprint(char text[DIM], double result1, double result2);
void customFuncRenamer(char variable[DIM]);
void replace(char toReplace[DIM], char replacement[DIM], char string[DIM]);
void fmsum(int lins, int cols, double v[dim][dim], double u[dim][dim], double r[dim][dim], double vI[dim][dim], double uI[dim][dim], double rI[dim][dim]);
void fmsubt(int lins, int cols, double v[dim][dim], double u[dim][dim], double r[dim][dim], double vI[dim][dim], double uI[dim][dim], double rI[dim][dim]);
void fmmulr(int lins, int cols, double v[dim][dim], double r[dim][dim], double re, double vI[dim][dim], double rI[dim][dim], double reI);
void fmmulm(int lins2, int cols1, int lins1, int cols2, double v[dim][dim], double u[dim][dim], double r[dim][dim], double vI[dim][dim], double uI[dim][dim], double rI[dim][dim]);
void saveToReport(char report[DIM]);
void equationSolver(char equation[DIM]);
void solveQuadraticEquation(char arithTrig[DIM], double result1, double result2, int index);
boolean verifyPrefix(char prefix[DIM]);
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
