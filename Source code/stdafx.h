

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
#define DIM 5000
#define _USE_MATH_DEFINES
#include <math.h>
#include <dirent.h> 
extern double resultR, resultI, ans[DIM], ansI[DIM], resultFI, valInd[DIM][DIM], values[DIM][DIM], valuesI[DIM][DIM], valuesS[DIM][DIM], valuesSI[DIM][DIM], valuesF[DIM][DIM], valuesFI[DIM][DIM];
extern int Mode, validVar, valid, valRenamedVar, synTest, count, continu, cleanhistory, rf, verified;
extern char calendarStr[DIM], revariable[DIM], varRename[DIM], expressionF[DIM], pathNAme[DIM], variableSTring[DIM], integral[DIM], usRFunctions[DIM], usRFuncTrans[DIM];
double functionProcessor(char trigon[DIM], double result, double amplitude, double res);
double initialProcessor(char arithTrig[DIM], double result);
double arithSolver(char trigon1[DIM], double result);
int processTxt(char path[DIM], int re);
double processVariable(char variable[DIM]);
void variableController(char variable[DIM], double result);
int variableValidator(char variable[DIM]);
double binaryToDecimal(char binary[DIM]);
double octalToDecimal(char octal[DIM]);
double hexadecimalToDecimal(char hexadecimal[DIM]);
void decimalToBinary(double decimal, char path[DIM], int bp);
void decimalToOctal(double decimal, char path[DIM], int op);
void decimalToHexadecimal(double decimal, char path[DIM], int hp);
double numericalSystems(char numSystem[DIM]);
int prefDet(double n, char path[DIM]);
double convertToNumber(char number[DIM]);
void DayofWeek(int d, int m, int y, char calendar[DIM]);
void Calendar(char yearCalendar[DIM], int year);
int dataVerifier(char data[DIM], double result1, double result2, int comment, int verify);
void variableRenamer(char variable[DIM]);
void pathNameController(char pathName[DIM], char path[DIM]);
void pathNameToPath(char pathName[DIM]);
void stringVariableController(char stringVariable[DIM], char string[DIM]);
void stringVariableToString(char stringVariable[DIM]);
void matrixToValues(char matrix[DIM], double result);
void renamer(char expression[DIM]);
void variableToMultiply(char expression[DIM]);
void toMultiply(char expression[DIM], double result1, double result2);
int verifyPrefix(char prefix[DIM]);
void manageExpression(char arithTrig[DIM], double result1, double result2, int verify);
int searchExtension(char filename[DIM], char extension[DIM]);
void toSolve(int re);
int commands(char arithTrig[DIM], char path[DIM], double result1, double result2);
double main_core(char arithTrig[DIM], char fTrig[DIM], FILE *fout, char path[DIM], double result1, double result2, int isFromMain);
double main_sub_core(char arithTrig[DIM], FILE *fout, int verify, char path[DIM], int txt, char variable[DIM], int v, int j, double result1, double result2, int isFromMain, int var, int valGet, int command);
boolean atcFunctions(char functionName[DIM]);
void print(char text[DIM], double result1, double result2);
int verifyNumerical(char number);
double solveNow(char toSolveNow[DIM], double result1, double result2);
int isToWrite(char arith[DIM]);
void sprint(char text[DIM], double result1, double result2);
void customFuncRenamer(char variable[DIM]);
void showValues();
boolean isCommand(char forTesting[DIM], char command[DIM]);
boolean readyToSolve(char paTh[DIM]);