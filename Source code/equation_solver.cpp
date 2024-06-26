﻿




#include "stdafx.h"

boolean notSolved = true, fromEquationSolver = false, equationSolverRunning = false, polySimplifier = false, solveMultiPoly = false, simplifying = true, progress = false, product = false;
char charMaster[DIM] = "", roots[DIM] = "", answers[DIM] = "", polyNo[DIM] = "", stringHelper[DIM] = "";
int parentPol[DIM];
int nrRoots = 0, rootIndex = 1, maxExponent = 0, _rf = 0;
double lastDividerR = 1, lastDividerI = 0, natureValue = 1, lastElement = 0, lastElementI = 0;
char splitResult[dime][dime];
double expressionCoefR[dime], expressionCoefI[dime], realRoots[dime];

void solveQuadraticEquation(char arithTrig[DIM], double result1, double result2, int index) {
	char values[DIM] = "", value[DIM] = "", saveValue[DIM] = "";
	int v = 0, ct = 0;
	double aR = 0, aI = 0, bR = 0, bI = 0, cR = 0, cI = 0;
	int i = 23;
	while (arithTrig[i] != '\0' && arithTrig[i] != ')') {
		if (arithTrig[i] == '\\') {
			ct++;
		}
		values[v] = arithTrig[i];
		v++;
		i++;
	}
	values[v] = '\0';
	if (ct != 2) {
		puts("\nError: You must include a, b and c values.\n");
	}
	else {
		v = 0;
		i = 0;
		while (values[i] != '\\') {
			value[v] = values[i];
			i++;
			v++;
		}
		value[v] = '\0';
		solveMath(value);
		if (verified == 1) {
			aR = resultR;
			aI = resultI;
			i++;
			v = 0;
			while (values[i] != '\\') {
				value[v] = values[i];
				i++;
				v++;
			}
			value[v] = '\0';
			solveMath(value);
			if (verified == 1) {
				bR = resultR;
				bI = resultI;
				i++;
				v = 0;
				while (values[i] != '\0') {
					value[v] = values[i];
					i++;
					v++;
				}
				value[v] = '\0';
				solveMath(value);
				if (verified == 1) {
					cR = resultR;
					cI = resultI;
					multiplication(-1, 0, bR, bI);
					double minusbR = resultR, minusbI = resultI;
					multiplication(bR, bI, bR, bI);
					double bRquad = resultR, bIquad = resultI;
					multiplication(aR, aI, cR, cI);
					double acR = resultR, acI = resultI;
					multiplication(2, 0, aR, aI);
					double twoaR = resultR, twoaI = resultI;
					multiplication(4, 0, acR, acI);
					double fouracR = resultR, fouracI = resultI;
					subtraction(bRquad, bIquad, fouracR, fouracI);
					double radicandR = resultR, radicandI = resultI;
					exponentiation(radicandR, radicandI, 0.5, 0, 1);
					double sqrtR = resultR, sqrtI = resultI;
					subtraction(minusbR, minusbI, sqrtR, sqrtI);
					double minusR = resultR, minusI = resultI;
					sum(minusbR, minusbI, sqrtR, sqrtI);
					double plusR = resultR, plusI = resultI;
					division(plusR, plusI, twoaR, twoaI);
					double x1R = resultR, x1I = resultI;
					division(minusR, minusI, twoaR, twoaI);
					double x2R = resultR, x2I = resultI;
					convertComplex2Exponential(x1R, x1I);
					if (x1R > 0 && x1I > 0) {
						printf("x%d=%s+%si\n", index, respR, respI);
					}
					else {
						if (x1R > 0 && x1I < 0) {
							printf("x%d=%s%si\n", index, respR, respI);
						}
						else {
							if (x1R < 0 && x1I > 0) {
								printf("x%d=%s+%si\n", index, respR, respI);
							}
							else {
								if (x1R < 0 && x1I < 0) {
									printf("x%d=%s%si\n", index, respR, respI);
								}
								else {
									if (x1R == 0 && x1I == 0) {
										printf("x%d=%s\n", index, respR);
									}
									else {
										if (x1R == 0 && x1I != 0) {
											printf("x%d=%si\n", index, respI);
										}
										else {
											if (x1R != 0 && x1I == 0) {
												printf("x%d=%s\n", index, respR);
											}
											else {
												printf("x%d=%s+%si\n", index, respR, respI);
											}
										}
									}
								}
							}
						}
					}
					index++;
					convertComplex2Exponential(x2R, x2I);
					if (x2R > 0 && x2I > 0) {
						printf("x%d=%s+%si\n", index, respR, respI);
					}
					else {
						if (x2R > 0 && x2I < 0) {
							printf("x%d=%s%si\n", index, respR, respI);
						}
						else {
							if (x2R < 0 && x2I > 0) {
								printf("x%d=%s+%si\n", index, respR, respI);
							}
							else {
								if (x2R < 0 && x2I < 0) {
									printf("x%d=%s%si\n", index, respR, respI);
								}
								else {
									if (x2R == 0 && x2I == 0) {
										printf("x%d=%s\n", index, respR);
									}
									else {
										if (x2R == 0 && x2I != 0) {
											printf("x%d=%si\n", index, respI);
										}
										else {
											if (x2R != 0 && x2I == 0) {
												printf("x%d=%s\n", index, respR);
											}
											else {
												printf("x%d=%s+%si\n", index, respR, respI);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void rootsToPolynomial(char rootsF[DIM]) {
	isDivisible = true;
	char report[DIM] = "";
	double valuesRootsR[DIM], valuesRootsI[DIM], polynomialR[DIM], polynomialI[DIM], newPolynomialR[DIM], newPolynomialI[DIM];
	int i = 0, numberRoots = 0, rootIndex = 1, saveNumberRoots = 0;
	for (i = 0; rootsF[i] != '\0'; i++) {
		if (rootsF[i] == '\\') {
			numberRoots++;
		}
	}
	numberRoots++;
	if (numberRoots == 1) {
		solveMath(rootsF);
		multiplication(resultR, resultI, lastDividerR, lastDividerI);
		char Report[dime] = "";
		sprintf(Report, convertToString("%s(%G+%Gi)x^1-(%G+%Gi)"), report, lastDividerR, lastDividerI, resultR, resultI);
		if (isContained("E", Report)) {
			sprintf(Report, convertToString("%s(%f+%fi)x^1-(%f+%fi)"), report, lastDividerR, lastDividerI, resultR, resultI);
		}
		sprintf(report, "%s", Report);
		if (isContained("(-", report)) {
			replace("(-", "(_", report);
			sprintf(report, "%s", expressionF);
		}
		if (isContained("+-", report)) {
			replace("+-", "-", report);
			sprintf(report, "%s", expressionF);
		}
		if (isContained("-(-", report)) {
			replace("-(-", "-(_", report);
			sprintf(report, "%s", expressionF);
		}
		if (isContained(".000000", report)) {
			replace(".000000", "", report);
			sprintf(report, "%s", expressionF);
		}
		if (isContained(")))", report)) {
			replace(")))", "))", report);
			sprintf(report, "%s", expressionF);
		}
		if (isContained("(((", report)) {
			replace("(((", "((", report);
			sprintf(report, "%s", expressionF);
		}
		if (strlen(expressionF) > 0) {
			sprintf(report, "%s", expressionF);
		}
		sprintf(expressionF, "(%s)", report);
	}
	else {
		for (i = 0; i < numberRoots * 100; i++) {
			valuesRootsR[i] = 0;
			valuesRootsI[i] = 0;
			polynomialR[i] = 0;
			polynomialI[i] = 0;
			newPolynomialR[i] = 0;
			newPolynomialI[i] = 0;
		}
		int members = 0;
		i = 0;
		char toValue[DIM] = "";
		while (members < numberRoots) {
			int b = 0;
			while (rootsF[i] != '\\' && rootsF[i] != '\0') {
				toValue[b] = rootsF[i];
				b++;
				i++;
			}
			toValue[b] = '\0';
			solveMath(toValue);
			valuesRootsR[members] = resultR;
			valuesRootsI[members] = resultI;
			members++;
			sprintf(toValue, "");
			i++;
		}
		i = 0;
		int g = 0;
		double restR = 0, restI = 0;
		char value[200] = "";
		char * pointer;
		double rearrangeValuesR[dime], rearrangeValuesI[dime];
		while (i < members) {
			if (valuesRootsR[i] == 0 && valuesRootsI[i] == 0) {
				rearrangeValuesR[g] = 0; rearrangeValuesI[g] = 0;
				g++;
			}

			i++;
		}
		i = 0;
		while (i < members) {
			if (valuesRootsR[i] != 0 && valuesRootsI[i] == 0) {
				double resultRR = 0, resultII = 0;
				sprintf(value, "%s", convert2Exponential(valuesRootsR[i]));
				resultRR = strtod(value, &pointer);
				sprintf(value, "%s", convert2Exponential(valuesRootsI[i]));
				resultII = strtod(value, &pointer);
				re_complex(resultRR, resultII, 1.0, 0.0);
				restR = resultR; restI = resultI;
				if (abs(restR) == 0 && abs(restI) == 0) {
					rearrangeValuesR[g] = valuesRootsR[i]; rearrangeValuesI[g] = valuesRootsI[i];
					valuesRootsR[i] = 0; valuesRootsI[i] = 0;
					g++;
				}
			}
			i++;
		}
		i = 0;
		while (i < members) {
			if (valuesRootsR[i] == 0 && valuesRootsI[i] != 0) {
				double resultRR = 0, resultII = 0;
				sprintf(value, "%s", convert2Exponential(valuesRootsR[i]));
				resultRR = strtod(value, &pointer);
				sprintf(value, "%s", convert2Exponential(valuesRootsI[i]));
				resultII = strtod(value, &pointer);
				re_complex(resultRR, resultII, 0.0, 1.0);
				restR = resultR; restI = resultI;
				if (abs(restR) == 0 && abs(restI) == 0) {
					rearrangeValuesR[g] = valuesRootsR[i]; rearrangeValuesI[g] = valuesRootsI[i];
					valuesRootsR[i] = 0; valuesRootsI[i] = 0;
					g++;
				}
			}
			i++;
		}

		i = 0;
		while (i < members) {
			if (valuesRootsR[i] != 0 || valuesRootsI[i] != 0) {
				rearrangeValuesR[g] = valuesRootsR[i];
				rearrangeValuesI[g] = valuesRootsI[i];
				g++;
			}
			i++;
		}
		i = 0;
		while (i < members) {
			valuesRootsR[i] = rearrangeValuesR[i];
			valuesRootsI[i] = rearrangeValuesI[i];
			i++;
		}
		members = 0;
		polynomialR[0] = 1;
		polynomialI[0] = 0;
		polynomialR[1] = valuesRootsR[0] * -1;
		polynomialI[1] = valuesRootsI[0] * -1;
		double saveResultR[dime][dime], saveResultI[dime][dime];
		double polynomialRF[DIM], polynomialIF[DIM];
		while (members < numberRoots) {
			for (i = 0; i < members * 2; i++) {
				polynomialRF[i] = 0;
				polynomialIF[i] = 0;
			}
			resultR = 0;
			resultI = 0;
			newPolynomialR[0] = 1;
			newPolynomialI[0] = 0;
			newPolynomialR[1] = valuesRootsR[members] * -1;
			newPolynomialI[1] = valuesRootsI[members] * -1;
			int j = 0, pol = 0;
			for (i = 0; i < members * 2; i++) {
				for (j = 0; j < 2; j++) {
					resultR = 0;
					resultI = 0;
					multiplication(polynomialR[i], polynomialI[i], newPolynomialR[j],
						newPolynomialI[j]);
					saveResultR[i][j] = resultR;
					saveResultI[i][j] = resultI;
				}
			}
			for (i = 0; i < members * 2; i++) {
				for (j = 0; j < 2; j++) {
					if (i == 0 && j == 0) {
						polynomialRF[pol] = saveResultR[i][j];
						polynomialIF[pol] = saveResultI[i][j];
						pol++;
					}
					else {
						if (i == (members * 2 - 1) && j == 1) {
							polynomialRF[pol] = saveResultR[i][j];
							polynomialIF[pol] = saveResultI[i][j];
							pol++;
						}
						else {
							if ((saveResultR[i][j] == 0 && saveResultR[i + 1][j - 1] == 0 &&
								saveResultI[i][j] == 0 && saveResultI[i + 1][j - 1] == 0) ==
								false) {
								polynomialRF[pol] = saveResultR[i][j] + saveResultR[i + 1][j - 1];
								saveResultR[i][j] = 0;
								saveResultR[i + 1][j - 1] = 0;
								polynomialIF[pol] = saveResultI[i][j] + saveResultI[i + 1][j - 1];
								saveResultI[i][j] = 0;
								saveResultI[i + 1][j - 1] = 0;
								pol++;
							}
						}
					}
				}
			}
			members++;
			int savePol = pol;
			if (pol > 3) {
				savePol--;
			}
			int exp = members;
			char Report[DIM] = "";
			for (pol = 0; pol < savePol; pol++) {
				if (members == numberRoots) {
					if (exp > 1) {
						multiplication(polynomialRF[pol], polynomialIF[pol], lastDividerR,
							lastDividerI);
						char toSimplify[100] = "";
						convertComplex2Exponential(resultR, resultI);
						sprintf(toSimplify, convertToString("%s+%si"), respR, respI);
						if (isContained("E", toSimplify)) {
							sprintf(toSimplify, convertToString("%f+%fi"), resultR, resultI);
						}
						if (isContained("-", toSimplify)) {
							replace("-", "_", toSimplify);
							sprintf(toSimplify, "%s", expressionF);
						}
						solveMath(toSimplify);
						convertComplex2Exponential(resultR, resultI);
						sprintf(Report, convertToString("%s(%s+%si)x^%d+"), report, respR, respI,
							exp);
						if (isContained("E", Report)) {
							sprintf(Report, convertToString("%s(%f+%fi)x^%d+"), report, resultR, resultI,
								exp);
						}
					}
					else {
						if (exp == 1) {
							multiplication(polynomialRF[pol], polynomialIF[pol], lastDividerR,
								lastDividerI);
							char toSimplify[100] = "";
							convertComplex2Exponential(resultR, resultI);
							sprintf(toSimplify, convertToString("%s+%si"), respR, respI);
							if (isContained("E", toSimplify)) {
								sprintf(toSimplify, convertToString("%f+%fi"), resultR, resultI);
							}
							if (isContained("-", toSimplify)) {
								replace("-", "_", toSimplify);
								sprintf(toSimplify, "%s", expressionF);
							}
							solveMath(toSimplify);
							convertComplex2Exponential(resultR, resultI);
							sprintf(Report, convertToString("%s(%s+%si)x^1+"), report, respR, respI);
							if (isContained("E", Report)) {
								sprintf(Report, convertToString("%s(%f+%fi)x^%d+"), report, resultR, resultI,
									exp);
							}
						}
						else {
							if (exp == 0) {
								multiplication(polynomialRF[pol], polynomialIF[pol], lastDividerR,
									lastDividerI);
								char toSimplify[100] = "";
								convertComplex2Exponential(resultR, resultI);
								sprintf(toSimplify, convertToString("%s+%si"), respR, respI);
								if (isContained("E", toSimplify)) {
									sprintf(toSimplify, convertToString("%f+%fi"), resultR, resultI);
								}
								if (isContained("-", toSimplify)) {
									replace("-", "_", toSimplify);
									sprintf(toSimplify, "%s", expressionF);
								}
								solveMath(toSimplify);
								convertComplex2Exponential(resultR, resultI);
								sprintf(Report, convertToString("%s(%s+%si)"), report, respR,
									respI);
								if (isContained("E", Report)) {
									sprintf(Report, convertToString("%s(%f+%fi)"), report, resultR, resultI);
								}
							}
						}
					}
					sprintf(report, "%s", Report);
				}
				polynomialR[pol] = polynomialRF[pol];
				polynomialRF[pol] = 0;
				polynomialI[pol] = polynomialIF[pol];
				polynomialIF[pol] = 0;
				exp--;
				if (isContained("(-", report)) {
					replace("(-", "(_", report);
					sprintf(report, "%s", expressionF);
				}
				replaceTimes = 0;
				if (isContained(".000000", report)) {
					replace(".000000", "", report);
					sprintf(report, "%s", expressionF);
				}
				if (isContained("+-", report)) {
					replace("+-", "-", report);
					sprintf(report, "%s", expressionF);
				}

			}
		}
		if (report[strlen(report) - 1] == '+') {
			report[strlen(report) - 1] = '\0';
		}
		sprintf(expressionF, "%s", report);
		if (polySimplifier == false) {

			sprintf(expressionF, "%s", report);

		}
		else {
			char finalPolynomial[DIM] = "";
			int h = 0, g = 0;
			while (report[g] != '\0') {
				finalPolynomial[h] = report[g];
				g++;
				h++;
			}
			finalPolynomial[h] = '\0';
			sprintf(expressionF, "(%s)", finalPolynomial);
		}
	}
}


double equationSolver(char equation[DIM]) {
	boolean hasFloatNum = false;
	char saveToCalcX[DIM] = "";
	char originalEquation[DIM] = "";
	sprintf(originalEquation, "%s", equation);
	int SaveMaxExponent = 0;
	maxExponent = 0;
	char toCalcX[DIM] = "";
	char toReplace[DIM] = "";
	double RootR[dime], RootI[dime], valuesEqR[DIM], valuesEqI[DIM], resultSubR[dime], resultSubI[dime];
	int i = 0;
	rootIndex = 1;
	sprintf(answers, "");
	char expression[DIM] = "";
	if (isContained("x)", equation) && strlen(equation) == strEnd) {
		equation[strlen(equation) - 1] = '\0';
	}
	double rootR = 0, rootI = 0;
	int saveMaxExponent = 0;
	char divider[100] = "";
	char saveToZeroDiv[DIM] = "";
	char saveEquation[DIM] = "";
	lastElement = 0;
	lastElementI = 0;
	bool isFirstDegree = false;
	if (!isDivisible) {
		isDivisible = false;
		equationSolverRunning = true;
		sprintf(expressionF, "%s", saveExpressionF);
	}
	else {
		if (isContained("\\", originalEquation)) {
			sprintf(saveEquation, "%s", originalEquation);
			maxExponent = 0;
			sprintf(expression, "%s", originalEquation);
			equationSolverRunning = true;
			solving = false;
			for (i = 0; originalEquation[i] != '\0'; i++) {
				if (originalEquation[i] == '\\') {
					maxExponent++;
				}
			}
			int members = maxExponent;
			i = 0;
			char toValue[DIM] = "";
			while (members >= 0) {
				int b = 0;
				while (originalEquation[i] != '\\' && originalEquation[i] != '\0') {
					toValue[b] = originalEquation[i];
					b++;
					i++;
				}
				toValue[b] = '\0';
				solveMath(toValue);
				if (resultR == -7777777) {
					puts("\nError: Empty input.");
					return 0;
				}
				valuesEqR[members] = resultR;
				valuesEqI[members] = resultI;
				members--;
				sprintf(toValue, "");
				i++;
			}
			i = maxExponent;
			double maxValueR = valuesEqR[maxExponent], maxValueI = valuesEqI[maxExponent];
			for (i = maxExponent; i >= 0; i--) {
				division(valuesEqR[i], valuesEqI[i], maxValueR, maxValueI);
				valuesEqR[i] = resultR;
				valuesEqI[i] = resultI;
			}
			saveMaxExponent = maxExponent;
			for (i = maxExponent; i > 0; i--) {
				char ValueR[DIM] = "";
				sprintf(ValueR, "%f", valuesEqR[i]);
				for (int v = 0; v < abs((int)(strlen(ValueR))); v++) {
					if (ValueR[v] == '-')
						ValueR[v] = '_';
				}
				char ValueI[DIM] = "";
				sprintf(ValueI, "%f", valuesEqI[i]);
				for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
					if (ValueI[v] == '-')
						ValueI[v] = '_';
				}

				sprintf(toCalcX, "%s(%s+%si)1*(res)^%d+", toCalcX, ValueR, ValueI, i);
			}
			lastDividerR = valuesEqR[0];
			lastDividerI = valuesEqI[0];

			char ValueR[DIM] = "";
			sprintf(ValueR, "%f", valuesEqR[i]);
			for (int v = 0; v < abs((int)strlen(ValueR)); v++) {
				if (ValueR[v] == '-')
					ValueR[v] = '_';
			}
			char ValueI[DIM] = "";
			sprintf(ValueI, "%f", valuesEqI[i]);
			for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
				if (ValueI[v] == '-')
					ValueI[v] = '_';
			}
			sprintf(toCalcX, "%s(%s+%si)", toCalcX, ValueR, ValueI);
			if (isContained(".000000", toCalcX)) {
				replace(".000000", "", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			sprintf(expressionF, "(%s)", toCalcX);
			sprintf(toCalcX, "%s", expressionF);
		}
		else {
			sprintf(saveEquation, "%s", originalEquation);
			sprintf(equation, "%s", originalEquation);
			if (isContained("-x", equation)) {
				replace("-x", "+_x", equation);
				sprintf(equation, "%s", expressionF);
			}
			sprintf(toCalcX, "");
			sprintf(saveToZeroDiv, "%s", equation);
			replaceTimes = 0;
			if (isContained(")*(", equation) || isContained(")(", equation) ||
				isContained(")/(", equation)) {
				if (isContained(")(", equation)) {
					replace(")(", ")*(", equation);
					sprintf(equation, "%s", expressionF);
				}
				resultR = 0;
				resultI = 0;
				product = true;
				simplifyPolynomial(equation);
				product = false;
				sprintf(saveEquation, "%s", expressionF);
				sprintf(equation, "%s", expressionF);
			}
			replaceTimes = 0;
			if (isContained("((", equation)) {
				replace("((", "(", equation);
				sprintf(equation, "%s", expressionF);
			}
			if (isContained("))", equation)) {
				replace("))", ")", equation);
				sprintf(equation, "%s", expressionF);
			}
			sprintf(expression, "%s", expressionF);
			int countLeft = countOccurrences("(", equation);
			int countRight = countOccurrences(")", equation);
			if (countLeft > countRight) {
				char newEquation[DIM] = "";
				sprintf(newEquation, "%s)", equation);
				sprintf(equation, "%s", newEquation);
			}
			if (countLeft < countRight) {
				char newEquation[DIM] = "";
				sprintf(newEquation, "(%s", equation);
				sprintf(equation, "%s", newEquation);
			}
			replaceTimes = 0;
			if (isContained("x", equation) && !isContained("x^", equation)) {
				replace("x", "X^1", equation);
				replace("X", "x", expressionF);
				sprintf(equation, "%s", expressionF);
			}
			replaceTimes = 0;

			if (isContained("[", equation)) {
				replace("[", "(", equation);
				sprintf(equation, "%s", expressionF);
			}
			if (isContained("]", equation)) {
				replace("]", ")", equation);
				sprintf(equation, "%s", expressionF);
			}
			if (isContained("(((", equation)) {
				replace("(((", "((", equation);
				sprintf(equation, "%s", expressionF);
			}
			if (isContained(")))", equation)) {
				replace(")))", "))", equation);
				sprintf(equation, "%s", expressionF);
			}
			replaceTimes = 0;
			sprintf(expressionF, "");
			if (isContained("[", equation)) {
				replace("[", "(", equation);
				sprintf(equation, "%s", expressionF);
			}
			if (isContained("]", equation)) {
				replace("]", ")", equation);
				sprintf(equation, "%s", expressionF);
			}
			removeTriplPars(equation);

			sprintf(equation, "%s", expressionF);
			if (isContained("+)", equation)) {
				replace("+)", ")", equation);
				sprintf(equation, "%s", expressionF);
			}
			if (isContained("++", equation)) {
				replace("++", "", equation);
				sprintf(equation, "%s", expressionF);
			}
			if (isContained("(*", equation)) {
				replace("(*", "(", equation);
				sprintf(equation, "%s", expressionF);
			}
			if (isContained("(*(", equation)) {
				replace("(*(", "((", equation);
				sprintf(equation, "%s", expressionF);
			}
			if (isContained("(*(", equation)) {
				replace("(*(", "((", equation);
				sprintf(equation, "%s", expressionF);
			}
			if (!dataVerifier(equation, 0, 0, 0, 1)) {
				if (countOccurrences(")", equation) > countOccurrences("(", equation)) {
					int u = countOccurrences(")", equation) - countOccurrences("(", equation);
					if (u == 1) {
						equation[strlen(equation) - 1] = '\0';
					}
				}
				if (countOccurrences(")", equation) < countOccurrences("(", equation)) {
					int u = countOccurrences("(", equation) - countOccurrences(")", equation);
					if (u == 1) {
						int b = 0;
						while (b < abs((int)strlen(equation))) {
							equation[b] = equation[b + 1];
							b++;
						}
						equation[b] = '\0';
					}
				}
			}
			sprintf(saveEquation, "%s", equation);
			sprintf(toCalcX, "%s", equation);
			solving = false;
			equationSolverRunning = true;
			sprintf(toCalcX, "%s", saveEquation);
			maxExponent = 0;
			char exponent[DIM] = "";
			int g = 0, k = 0;
			for (g = 0; equation[g] != '\0'; g++) {
				if (equation[g - 1] == 'x' && equation[g] == '^') {
					int saveG = g - 2;
					g++;
					k = 0;
					while (verifyNumber(equation[g])) {
						exponent[k] = equation[g];
						k++;
						g++;
					}
					exponent[k] = '\0';
					solveMath(exponent);
					if ((int)resultR > maxExponent) {
						maxExponent = (int)resultR;
					}
				}
			}
			sprintf(charMaster, "nothingL");
			char maxExpX[100] = "";
			sprintf(maxExpX, "x^%d", maxExponent);
			while (isContained(maxExpX, toCalcX) && verifyLetter(toCalcX[strStart - 1]) == false &&
				verifyNumber(toCalcX[strStart - 1]) == false) {
				char value[100] = "", valueF[100] = "";
				sprintf(value, "x^%d", maxExponent);
				sprintf(valueF, "1*(res)^%d", maxExponent);
				replace(value, valueF, toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			sprintf(charMaster, "");
			while (isContained(maxExpX, toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
				char value[100] = "", valueF[100] = "";
				sprintf(value, "%cx^%d", toCalcX[strStart - 1], maxExponent);
				sprintf(valueF, "%c*1*(res)^%d", toCalcX[strStart - 1], maxExponent);
				replace(value, valueF, toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			if (isContained("x+", toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
				replace("x+", "*1*(res)^1+", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			if (isContained("x-", toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
				replace("x-", "*1*(res)^1-", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			if (isContained("x", toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
				replace("x", "*1*(res)", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			sprintf(charMaster, "");
			if (isContained("x+", toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
				replace("x+", "*1*(res)^1+", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			if (isContained("x-", toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
				replace("x-", "*1*(res)^1-", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			if (isContained("x", toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
				replace("x", "*1*(res)", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			if (isContained("x", toCalcX) && !verifyNumber(toCalcX[strStart - 1])) {
				replace("x", "1*(res)", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
		}
		sprintf(saveToCalcX, "%s", toCalcX);
		char maxExp[10] = "";
		sprintf(maxExp, ")^%d", maxExponent);
		if (maxExponent > 0) {
			sprintf(expressionF, ")1*(res%s", maxExp);
			if (countOccurrences(maxExp, saveToCalcX) > 1 || !isContained(expressionF, saveToCalcX)) {
				maxExponent = getCorrectExponent(saveToCalcX, maxExp, maxExponent);
			}
			else {
				sprintf(expressionF, ")1*(res%s", maxExp);
				if (isContained(expressionF, saveToCalcX)) {
					int t = strStart;
					while (saveToCalcX[t] != '(') {
						t--;
					}
					t++;
					int v = 0;
					while (saveToCalcX[t] != ')') {
						expressionF[v] = saveToCalcX[t];
						v++; t++;
					}
					expressionF[v] = '\0';
					solveMath(expressionF);
					lastDividerR = resultR; lastDividerI = resultI;
				}
			}
		}
		if (isContained(".", toCalcX)) {
			hasFloatNum = true;
		}

		if (lastElement == 0 && lastElementI == 0) {
			sprintf(expressionF, "%s+(0.00000000000000001)/(1)", toCalcX);
			sprintf(toCalcX, "%s", expressionF);
			sprintf(saveToCalcX, "%s", toCalcX);
		}
		int g = 0, k = 0;
		if ((lastDividerR != 0 || lastDividerI != 0) && maxExponent > 0) {
			int maxMaxExponent = maxExponent;
			sprintf(divider, "(%f+%fi)", lastDividerR, lastDividerI);

			for (int y = 0; divider[y] != '\0'; y++) {
				if (divider[y] == '-') {
					divider[y] = '_';
				}
			}
			if (isContained(".000000", divider)) {
				replace(".000000", "", divider);
				sprintf(divider, "%s", expressionF);
			}
			char newExpre[DIM] = "";
			char toNoDivider[DIM] = "";
			sprintf(toNoDivider, "%s", toCalcX);
			replaceTimes = 0;
			if (isContained("(*(", toCalcX)) {
				replace("(*(", "((", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			if (!dataVerifier(toCalcX, 0, 0, 0, 1)) {
				removeDuplPars(toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			sprintf(newExpre, "(%s)/%s", toCalcX, divider);
			if (dataVerifier(newExpre, 0, 0, 0, 1)) {
				sprintf(toCalcX, "%s", newExpre);
			}
			else {
				sprintf(newExpre, "%s/%s", toCalcX, divider);
				sprintf(toCalcX, "%s", newExpre);
			}
			if (isContained(".000000", expression)) {
				replace(".000000", "", expression);
				sprintf(expression, "%s", expressionF);
			}
			char helpExtract[DIM] = "";
			int u = 0, t = 0, v = 0;
			sprintf(helpExtract, "%s", toNoDivider);
			if (isContained("(((", helpExtract)) {
				replace("(((", "((", helpExtract);
				sprintf(helpExtract, "%s", expressionF);
			}
			if (isContained(")))", helpExtract)) {
				replace(")))", "))", helpExtract);
				sprintf(helpExtract, "%s", expressionF);
			}
			sprintf(saveToCalcX, "%s", toCalcX);
			char saveHelper[DIM] = "";
			sprintf(saveHelper, "%s", helpExtract);
			char toCalcLastEle[DIM] = "";
			sprintf(toCalcLastEle, "%s", saveHelper);
			if (isContained("res", toCalcLastEle)) {
				replaceTimes = 0;
				replace("res", "0", toCalcLastEle);
				sprintf(toCalcLastEle, "%s", expressionF);
				solveMath(toCalcLastEle);
				lastElement = resultR; lastElementI = resultI;
			}
			double posLastElement = 0, posLastElementI = 0;
			multiplication(-1.0, 0.0, lastElement, lastElementI);
			posLastElement = resultR; posLastElementI = resultI;
			char posLastEle[dime] = "";
			sprintf(posLastEle, "%f+%fi", posLastElement, posLastElementI);
			replaceTimes = 0;
			if (isContained("-", posLastEle)) {
				replace("-", "_", posLastEle);
				sprintf(posLastEle, "%s", expressionF);
			}
			if (isContained(".000000", posLastEle)) {
				replace(".000000", "", posLastEle);
				sprintf(posLastEle, "%s", expressionF);
			}
			int findToRemove = 0;
			if (isContained(")x^1+(", equation)) {
				replaceTimes = 0;
				char LastEle[dime] = "";
				sprintf(LastEle, "^1+(%f+%fi)", lastElement, lastElementI);
				replaceTimes = 0;
				if (isContained("-", LastEle)) {
					replace("-", "_", LastEle);
					sprintf(LastEle, "%s", expressionF);
				}
				if (isContained(".000000", LastEle)) {
					replace(".000000", "", LastEle);
					sprintf(LastEle, "%s", expressionF);
				}
				replaceTimes = 1;
				if (isContained(LastEle, saveHelper)) {
					replace(LastEle, "^1+(0+0i)", saveHelper);
					sprintf(saveHelper, "%s", expressionF);
					findToRemove = 1;
				}
			}
			if (maxExponent > 0) {
				int hasImaginary = false;
				sprintf(expression, "");
				while (u < maxExponent) {
					replaceTimes = 0;
					resultR = 0; resultI = 0;
					sprintf(helpExtract, "%s", saveHelper);
					sprintf(toReplace, "1*(res)^%d+", maxExponent - u);
					if (isContained(toReplace, helpExtract)) {
						replace(toReplace, "1*(1)+", helpExtract);
						sprintf(helpExtract, "%s", expressionF);
						if (isContained("res", helpExtract)) {
							replace("res", "0", helpExtract);
							sprintf(helpExtract, "%s", expressionF);
						}
						solveMath(helpExtract);
						if (findToRemove == 0) {
							sum(resultR, resultI, posLastElement, posLastElementI);
						}
						division(resultR, resultI, lastDividerR, lastDividerI);
						sprintf(expression, "%s\\%f+%fi", expression, resultR, resultI);
						expressionCoefR[u] = resultR; expressionCoefI[u] = resultI;
						if (resultI != 0) {
							hasImaginary = true;
						}
					}
					else {
						replaceTimes = 0;
						resultR = 0; resultI = 0;
						sprintf(helpExtract, "%s", saveHelper);
						sprintf(toReplace, "1*(res)^%d", maxExponent - u);
						if (isContained(toReplace, helpExtract)) {
							replace(toReplace, "1*(1)", helpExtract);
							sprintf(helpExtract, "%s", expressionF);
							if (isContained("res", helpExtract)) {
								replace("res", "0", helpExtract);
								sprintf(helpExtract, "%s", expressionF);
							}
							solveMath(helpExtract);
							if (findToRemove == 0) {
								sum(resultR, resultI, posLastElement, posLastElementI);
							}
							division(resultR, resultI, lastDividerR, lastDividerI);
							sprintf(expression, "%s\\%f+%fi", expression, resultR, resultI);
							expressionCoefR[u] = resultR; expressionCoefI[u] = resultI;
							if (resultI != 0) {
								hasImaginary = true;
							}
						}
						else {
							resultR = 0; resultI = 0;
							sprintf(expression, "%s\\%f+%fi", expression, resultR, resultI);
							expressionCoefR[u] = resultR; expressionCoefI[u] = resultI;
						}
					}
					u++;
				}
				division(lastElement, lastElementI, lastDividerR, lastDividerI);
				lastElement = resultR; lastElementI = resultI;
				sprintf(expression, "%s\\%f+%fi", expression, lastElement, lastElementI);
				expressionCoefR[u] = lastElement; expressionCoefI[u] = lastElementI;

				if (resultI != 0) {
					hasImaginary = true;
				}
				if (isContained("-", expression)) {
					replace("-", "_", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (expression[0] == '\\') {
					int y = 1;
					for (y = 1; y < abs((int)strlen(expression)); y++) {
						expression[y - 1] = expression[y];
					}
					expression[y - 1] = '\0';
				}
				if (isContained(".000000", expression)) {
					replaceTimes = 0;
					replace(".000000", "", expression);
					sprintf(expression, "%s", expressionF);
				}
				replaceTimes = 0;
				double SolutionR[200], SolutionI[200];
				int solvedIndex = 0;
				double saveExpressionCoefR[dime], saveExpressionCoefI[dime];
				for (int uu = 0; uu < dime; uu++) {
					saveExpressionCoefR[uu] = 0.0;
					saveExpressionCoefI[uu] = 0.0;
				}
				for (int uu = 0; uu <= maxExponent; uu++) {
					saveExpressionCoefR[uu] = expressionCoefR[uu];
					saveExpressionCoefI[uu] = expressionCoefI[uu];
				}
				if (maxExponent == 1) {
					replaceTimes = 0;
					replace("res", "0", toCalcX);
					solveMath(expressionF);
					multiplication(-1.0, 0.0, resultR, resultI);
					RootR[0] = resultR; RootI[0] = resultI;
					SolutionR[0] = resultR; SolutionI[0] = resultI;
					solvedIndex++;
					notSolved = false;
				}
				else {
					resultR = 0; resultI = 0;
					int x = 0;
					char value[DIM] = "";
					int n = 1;
					int countSolutions = 0;
					float local = 0;
					int step = 0;
					int saveProgress = 0;
					int Progress = 0;
					char newFunction[DIM] = "";
					char savingPoly[DIM] = "";
					char divisionFactor[DIM] = "";
					char newDivider[DIM] = "";
					sprintf(savingPoly, "%s", toCalcX);
					int count = 0;
					int saveG = -1;
					g = 0;
					replaceTimes = 0;
					countSolutions = 0;
					int precisionN = 8;
					int z = 0, h = 0;
					double saveExpressionCoefR_1 = 0, saveExpressionCoefR_Max = 0;
					char forSummatory[DIM] = "", forExpressionMax[DIM] = "";
					int k = 0;
					if (!hasFloatNum) {
						saveMaxExponent = maxExponent;
						g = 0;
						int countEnterings = 0;
						int f = 1;
						saveExpressionCoefR_1 = 0, saveExpressionCoefR_Max = 0;
						int p = maxExponent;
						if (abs(expressionCoefR[p]) < 1E-9&& abs(expressionCoefI[p]) < 1E-9) {
							while (abs(expressionCoefR[p]) < 1E-9&& abs(expressionCoefI[p]) < 1E-9) {
								SolutionR[solvedIndex] = 0;
								SolutionI[solvedIndex] = 0;
								solvedIndex++;
								maxExponent--;
								p--;
							}
						}
						int m = solvedIndex;
						int nCycle = 0;
						int lastRootR = 0, lastRootI = 0;
						do {
							if (maxExponent > 1) {
								saveExpressionCoefR_1 = 0, saveExpressionCoefR_Max = 0;
								saveExpressionCoefR_Max = expressionCoefR[maxExponent];
								sprintf(forExpressionMax, "%s", convert2Exponential(expressionCoefR[maxExponent]));
								saveExpressionCoefR_1 = expressionCoefR[1];
								z = 0;
								g = 0;
								h = lastRootR + 1;
								for (h; g < maxExponent && z < 500; h++) {
									int _rf = 0;
									double SummatoryR = 0, SummatoryI = 0;
									while (_rf < maxExponent) {
										resultR = pot(h, maxExponent - _rf, 1);
										resultR = expressionCoefR[_rf] * resultR;
										SummatoryR = SummatoryR + resultR;
										SummatoryI = SummatoryI + 0;
										_rf++;
									}
									sprintf(forSummatory, "%s", convert2Exponential(SummatoryR*-1));
									if (isEqual(forSummatory, forExpressionMax)) {
										lastRootR = abs(h);
										RootR[g] = h; RootI[g] = 0;
										xValuesR = RootR[g];
										xValuesI = RootI[g];
										int _rf = 0;
										double SummatoryR = 0, SummatoryI = 0;
										while (_rf < maxExponent) {
											exponentiation(xValuesR, xValuesI, (double)maxExponent - _rf, 0.0, 1);
											multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);
											SummatoryR = SummatoryR + resultR;
											SummatoryI = SummatoryI + resultI;
											_rf++;
										}
										sum(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
										SummatoryR = resultR; SummatoryI = resultI;
										if (abs(SummatoryR) < 0.1&&abs(SummatoryI) < 0.1) {
											SolutionR[solvedIndex] = RootR[g];
											SolutionI[solvedIndex] = RootI[g];
											solvedIndex++;
											saveExpressionCoefR_Max = saveExpressionCoefR_Max / h;
											saveExpressionCoefR_1 = saveExpressionCoefR_1 + h;
											g++;
										}

									}
									h = h * -1;
									_rf = 0;
									SummatoryR = 0, SummatoryI = 0;
									while (_rf < maxExponent) {
										resultR = pot(h, maxExponent - _rf, 1);
										resultR = expressionCoefR[_rf] * resultR;
										SummatoryR = SummatoryR + resultR;
										SummatoryI = SummatoryI + 0;
										_rf++;
									}
									sprintf(forSummatory, "%s", convert2Exponential(SummatoryR*-1));
									if (isEqual(forSummatory, forExpressionMax)) {
										lastRootR = abs(h);
										RootR[g] = h; RootI[g] = 0;
										xValuesR = RootR[g];
										xValuesI = RootI[g];
										int _rf = 0;
										double SummatoryR = 0, SummatoryI = 0;
										while (_rf < maxExponent) {
											exponentiation(xValuesR, xValuesI, (double)maxExponent - _rf, 0.0, 1);
											multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);
											SummatoryR = SummatoryR + resultR;
											SummatoryI = SummatoryI + resultI;
											_rf++;
										}
										sum(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
										SummatoryR = resultR; SummatoryI = resultI;
										if (abs(SummatoryR) < 0.1&&abs(SummatoryI) < 0.1) {
											SolutionR[solvedIndex] = RootR[g];
											SolutionI[solvedIndex] = RootI[g];
											solvedIndex++;
											saveExpressionCoefR_Max = saveExpressionCoefR_Max / h;
											saveExpressionCoefR_1 = saveExpressionCoefR_1 + h;
											g++;
										}

									}
									h = h * -1;
									z++;
								}

								k = 0;
								if (k < g) {
									while (k < g) {
										int y = 1;
										while (y - 1 < maxExponent) {
											multiplication(expressionCoefR[y - 1], expressionCoefI[y - 1], SolutionR[m], SolutionI[m]);
											sum(expressionCoefR[y], expressionCoefI[y], resultR, resultI);
											expressionCoefR[y] = resultR; expressionCoefI[y] = resultI;
											y++;
										}
										maxExponent--;
										k++;
										m++;
									}
								}
							}
							if (maxExponent > 1) {
								saveExpressionCoefR_1 = 0, saveExpressionCoefR_Max = 0;
								int real = 0;
								g = 0;
								saveExpressionCoefR_1 = 0; saveExpressionCoefR_Max = 0;
								if (abs(expressionCoefI[maxExponent]) >= 1) {
									saveExpressionCoefR_Max = expressionCoefI[maxExponent];
									sprintf(forExpressionMax, "%s", convert2Exponential(abs(expressionCoefI[maxExponent])));
									real = 1;
								}
								else {
									saveExpressionCoefR_Max = expressionCoefR[maxExponent];
									sprintf(forExpressionMax, "%s", convert2Exponential(abs(expressionCoefR[maxExponent])));
								}
								saveExpressionCoefR_1 = expressionCoefI[1];
								z = 0;

								h = lastRootI + 1;
								for (h; g < maxExponent && z < 500; h++) {
									int _rf = 0;
									double SummatoryR = 0, SummatoryI = 0;
									while (_rf < maxExponent) {
										exponentiation(0, h, maxExponent - _rf, 0.0, 1);
										multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);
										SummatoryR = SummatoryR + resultR;
										SummatoryI = SummatoryI + resultI;
										_rf++;
									}
									sprintf(forSummatory, "%s", convert2Exponential(abs(SummatoryI)));
									if (isEqual(forSummatory, forExpressionMax)) {
										RootR[g] = 0; RootI[g] = h;
										xValuesR = RootR[g];
										xValuesI = RootI[g];
										int _rf = 0;
										double SummatoryR = 0, SummatoryI = 0;
										while (_rf < maxExponent) {
											exponentiation(xValuesR, xValuesI, (double)maxExponent - _rf, 0.0, 1);
											multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);
											SummatoryR = SummatoryR + resultR;
											SummatoryI = SummatoryI + resultI;
											_rf++;
										}
										sum(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
										SummatoryR = resultR; SummatoryI = resultI;
										if (abs(SummatoryR) < 0.1&&abs(SummatoryI) < 0.1) {
											SolutionR[solvedIndex] = RootR[g];
											SolutionI[solvedIndex] = RootI[g];
											solvedIndex++;
											saveExpressionCoefR_Max = saveExpressionCoefR_Max / h;
											saveExpressionCoefR_1 = saveExpressionCoefR_1 + h;
											g++;
										}

									}
									else {
										sprintf(forSummatory, "%s", convert2Exponential(abs(SummatoryR)));
										if (isEqual(forSummatory, forExpressionMax) && abs(SummatoryI) < 1 && real == 1) {
											RootR[g] = 0; RootI[g] = h;
											xValuesR = RootR[g];
											xValuesI = RootI[g];
											int _rf = 0;
											double SummatoryR = 0, SummatoryI = 0;
											while (_rf < maxExponent) {
												exponentiation(xValuesR, xValuesI, (double)maxExponent - _rf, 0.0, 1);
												multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);
												SummatoryR = SummatoryR + resultR;
												SummatoryI = SummatoryI + resultI;
												_rf++;
											}
											sum(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
											SummatoryR = resultR; SummatoryI = resultI;
											if (abs(SummatoryR) < 0.1&&abs(SummatoryI) < 0.1) {
												SolutionR[solvedIndex] = RootR[g];
												SolutionI[solvedIndex] = RootI[g];
												solvedIndex++;
												saveExpressionCoefR_Max = saveExpressionCoefR_Max / h;
												saveExpressionCoefR_1 = saveExpressionCoefR_1 + h;
												g++;
											}

										}
									}
									h = h * -1;
									_rf = 0;
									SummatoryR = 0, SummatoryI = 0;
									while (_rf < maxExponent) {
										exponentiation(0, h, maxExponent - _rf, 0.0, 1);
										multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);
										SummatoryR = SummatoryR + resultR;
										SummatoryI = SummatoryI + resultI;
										_rf++;
									}
									sprintf(forSummatory, "%s", convert2Exponential(abs(SummatoryI)));
									if (isEqual(forSummatory, forExpressionMax)) {
										RootR[g] = 0; RootI[g] = h;
										xValuesR = RootR[g];
										xValuesI = RootI[g];
										int _rf = 0;
										double SummatoryR = 0, SummatoryI = 0;
										while (_rf < maxExponent) {
											exponentiation(xValuesR, xValuesI, (double)maxExponent - _rf, 0.0, 1);
											multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);
											SummatoryR = SummatoryR + resultR;
											SummatoryI = SummatoryI + resultI;
											_rf++;
										}
										sum(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
										SummatoryR = resultR; SummatoryI = resultI;
										if (abs(SummatoryR) < 0.1&&abs(SummatoryI) < 0.1) {
											SolutionR[solvedIndex] = RootR[g];
											SolutionI[solvedIndex] = RootI[g];
											solvedIndex++;
											saveExpressionCoefR_Max = saveExpressionCoefR_Max / h;
											saveExpressionCoefR_1 = saveExpressionCoefR_1 + h;
											g++;
										}

									}
									else {
										sprintf(forSummatory, "%s", convert2Exponential(abs(SummatoryR)));
										if (isEqual(forSummatory, forExpressionMax) && abs(SummatoryI) < 1 && real == 1) {
											RootR[g] = 0; RootI[g] = h;
											xValuesR = RootR[g];
											xValuesI = RootI[g];
											int _rf = 0;
											double SummatoryR = 0, SummatoryI = 0;
											while (_rf < maxExponent) {
												exponentiation(xValuesR, xValuesI, (double)maxExponent - _rf, 0.0, 1);
												multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);
												SummatoryR = SummatoryR + resultR;
												SummatoryI = SummatoryI + resultI;
												_rf++;
											}
											sum(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
											SummatoryR = resultR; SummatoryI = resultI;
											if (abs(SummatoryR) < 0.1&&abs(SummatoryI) < 0.1) {
												SolutionR[solvedIndex] = RootR[g];
												SolutionI[solvedIndex] = RootI[g];
												solvedIndex++;
												saveExpressionCoefR_Max = saveExpressionCoefR_Max / h;
												saveExpressionCoefR_1 = saveExpressionCoefR_1 + h;
												g++;
											}

										}
									}
									h = h * -1;
									z++;
								}

								k = 0;
								if (k < g) {
									while (k < g) {
										int y = 1;
										while (y - 1 < maxExponent) {
											multiplication(expressionCoefR[y - 1], expressionCoefI[y - 1], SolutionR[m], SolutionI[m]);
											sum(expressionCoefR[y], expressionCoefI[y], resultR, resultI);
											expressionCoefR[y] = resultR; expressionCoefI[y] = resultI;
											y++;
										}
										maxExponent--;
										k++;
										m++;
									}
								}

							}
							nCycle++;
							if (nCycle < solvedIndex) {
								nCycle = solvedIndex;
							}
							if (maxExponent > 0 && nCycle < maxExponent) {
								solvedIndex = saveMaxExponent - maxExponent;
								m = solvedIndex;
							}
						} while (maxExponent > 0 && nCycle < maxExponent);
						g = 0;
						int gg = 0;
						while (g < solvedIndex&&solvedIndex < maxMaxExponent&&gg < maxMaxExponent * 2) {
							xValuesR = SolutionR[g];
							xValuesI = SolutionI[g];
							int _rf = 0;
							double SummatoryR = 0, SummatoryI = 0;
							while (_rf < maxExponent) {
								exponentiation(xValuesR, xValuesI, maxExponent - _rf, 0.0, 1);
								multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);
								SummatoryR = SummatoryR + resultR;
								SummatoryI = SummatoryI + resultI;
								_rf++;
							}
							sum(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
							SummatoryR = resultR; SummatoryI = resultI;
							if (abs(SummatoryR) < 1E-9&&abs(SummatoryI) < 1E-9) {
								SolutionR[solvedIndex] = xValuesR;
								SolutionI[solvedIndex] = xValuesI;
								int y = 1;
								while (y - 1 < maxExponent) {
									multiplication(expressionCoefR[y - 1], expressionCoefI[y - 1], SolutionR[solvedIndex], SolutionI[solvedIndex]);
									sum(expressionCoefR[y], expressionCoefI[y], resultR, resultI);
									expressionCoefR[y] = resultR; expressionCoefI[y] = resultI;
									y++;
								}
								solvedIndex++;
								maxExponent--;
								g = 0;
							}
							g++;
							gg++;
						}
						precisionN = 8;
						if (maxExponent == 1) {
							int _rf = 0;
							double SummatoryR = 0, SummatoryI = 0;
							while (_rf < maxExponent) {
								exponentiation(0, 0, maxExponent - _rf, 0.0, 1);
								multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);
								SummatoryR = SummatoryR + resultR;
								SummatoryI = SummatoryI + resultI;
								_rf++;
							}
							sum(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
							SummatoryR = resultR; SummatoryI = resultI;
							multiplication(-1, 0, SummatoryR, SummatoryI);
							SolutionR[solvedIndex] = resultR; SolutionI[solvedIndex] = resultI;
							solvedIndex++;
						}

					}

					if (maxExponent > 1 || maxExponent == maxMaxExponent) {
						char * pointer;


						double saveExpressionCoefRN[dime], saveExpressionCoefIN[dime];
						int saveMaxExponent = maxExponent;
						while (_rf <= maxExponent) {
							saveExpressionCoefRN[_rf] = expressionCoefR[_rf];
							saveExpressionCoefIN[_rf] = expressionCoefI[_rf];
							_rf++;
						}


						rasf = 0;

						int count = 0;
						double deltaxR = 1, deltaxI = 0;
						int i = 0;
						do {
							i = 0;
							double xValueR = 0, xValueI = 0, solR = 0, solI = 0;

							double fxDevR = 0, fxDevI = 0;
							char lastFx[DIM] = "", currentFx[DIM] = "";
							while (i < 150) {
								xValuesR = xValueR; xValuesI = xValueI;
								int _rf = 0;
								double SummatoryR = 0, SummatoryI = 0;
								while (_rf < maxExponent) {
									exponentiation(xValuesR, xValuesI, (double)maxExponent - _rf, 0.0, 1);
									multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);

									SummatoryR = SummatoryR + resultR;
									SummatoryI = SummatoryI + resultI;
									_rf++;
								}
								sum(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
								double fxR = resultR, fxI = resultI;
								sprintf(currentFx, "%G+%Gi", abs(fxR), abs(fxI));
								if (isEqual(currentFx, lastFx) && abs(fxR) < 1E-6&&abs(fxI) < 1E-6&&i > 10) {
									break;
								}

								xValuesR = xValueR + deltaxR;
								xValuesI = xValueI + deltaxI;
								_rf = 0;
								SummatoryR = 0; SummatoryI = 0;
								while (_rf < maxExponent) {
									exponentiation(xValuesR, xValuesI, (double)maxExponent - _rf, 0.0, 1);
									multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);

									SummatoryR = SummatoryR + resultR;
									SummatoryI = SummatoryI + resultI;
									_rf++;
								}
								sum(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
								double fxplusaR = resultR, fxplusaI = resultI;
								subtraction(fxplusaR, fxplusaI, fxR, fxI);
								division(resultR, resultI, deltaxR, deltaxI);

								if (resultR != 0 || resultI != 0) {
									fxDevR = resultR, fxDevI = resultI;
								}

								division(fxR, fxI, fxDevR, fxDevI);
								subtraction(xValueR, xValueI, resultR, resultI);
								if (i < 5) {
									xValueR = quo(resultR); xValueI = quo(resultI);
								}
								else {
									xValueR = resultR; xValueI = resultI;
								}

								solR = xValueR; solI = xValueI;

								sprintf(lastFx, "%s", currentFx);
								i++;
							}
							if (i <= 150) {

								RootR[count] = solR + 0.7; RootI[count] = solI + 0.7;

								int y = 1;
								while (y - 1 < maxExponent) {
									multiplication(expressionCoefR[y - 1], expressionCoefI[y - 1], RootR[count], RootI[count]);
									sum(expressionCoefR[y], expressionCoefI[y], resultR, resultI);
									expressionCoefR[y] = resultR; expressionCoefI[y] = resultI;
									y++;
								}
								maxExponent--;
								count++;
							}
						} while (maxExponent > 0);

						maxExponent = saveMaxExponent;
						_rf = 0;
						while (_rf <= maxExponent) {
							expressionCoefR[_rf] = saveExpressionCoefRN[_rf];
							expressionCoefI[_rf] = saveExpressionCoefIN[_rf];
							_rf++;
						}

						_rf = 0;
						resultR = 0; resultI = 0;
						int x = 0;
						char value[DIM] = "";
						int n = 1;
						float local = 0;
						int step = 0;
						int saveProgress = 0;
						int Progress = 0;
						char newFunction[DIM] = "";
						char savingPoly[DIM] = "";
						char divisionFactor[DIM] = "";
						char newDivider[DIM] = "";
						sprintf(savingPoly, "%s", toCalcX);
						count = 0;
						int saveG = -1;
						g = 0;
						replaceTimes = 0;
						countSolutions = 0;
						precisionN = 6;
						double summaR = 0, summaI = 0;
						double expressCoefR[200], expressCoefI[200];
						double expresR[dime], expresI[dime];
						int r = 0;
						for (r = 0; r <= maxExponent; r++) {
							expresR[r] = expressionCoefR[r];
							expresI[r] = expressionCoefI[r];
						}
						int breakAction = 0;
						double saveRootR, saveRootI;
						notSolved = true;
						if (maxMaxExponent <= 40) {
							while (((!notSolved&&n < breakAction) || (notSolved&&countSolutions < maxMaxExponent - 1)) && n < 7777) {
								g = 0;
								double sumRootsR = 0, sumRootsI = 0;
								while (g < maxExponent) {
									xValuesR = RootR[g];
									xValuesI = RootI[g];
									saveRootR = RootR[g];
									saveRootI = RootI[g];
									int _rf = 0;
									double SummatoryR = 0, SummatoryI = 0;
									while (_rf < maxExponent) {
										exponentiation(xValuesR, xValuesI, (double)maxExponent - _rf, 0.0, 1);
										multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);
										expressCoefR[_rf] = expressionCoefR[_rf];
										expressCoefI[_rf] = expressionCoefI[_rf];
										SummatoryR = SummatoryR + resultR;
										SummatoryI = SummatoryI + resultI;
										_rf++;
									}
									sum(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
									expressCoefR[_rf] = expressionCoefR[_rf];
									expressCoefI[_rf] = expressionCoefI[_rf];
									summaR = resultR; summaI = resultI;
									sprintf(value, "%s", convert2Exponential(RootR[g]));
									SolutionR[solvedIndex] = strtod(value, &pointer);
									sprintf(value, "%s", convert2Exponential(RootI[g]));
									SolutionI[solvedIndex] = strtod(value, &pointer);

									if (abs(SolutionR[solvedIndex]) < 1E-5) {
										SolutionR[solvedIndex] = 0;
									}
									if (abs(SolutionI[solvedIndex]) < 1E-5) {
										SolutionI[solvedIndex] = 0;
									}

									double saveLastR = expressionCoefR[maxExponent], saveLastI = expressionCoefI[maxExponent];

									expressCoefR[0] = 1; expressCoefI[0] = 0;
									int y = 1;
									while (y - 1 < maxExponent) {
										multiplication(expressCoefR[y - 1], expressCoefI[y - 1], SolutionR[solvedIndex], SolutionI[solvedIndex]);
										sum(expressCoefR[y], expressCoefI[y], resultR, resultI);
										expressCoefR[y] = resultR; expressCoefI[y] = resultI;
										y++;
									}
									double saveResultR = expressCoefR[y - 2], saveResultI = expressCoefI[y - 2];

									xValuesR = M_PI;
									xValuesI = 0;
									double SummatoryCR = 0, SummatoryCI = 0;
									_rf = 0;
									while (_rf < (maxExponent - 1)) {
										exponentiation(xValuesR, xValuesI, (maxExponent - 1) - _rf, 0.0, 1);
										multiplication(expressCoefR[_rf], expressCoefI[_rf], resultR, resultI);
										SummatoryCR = SummatoryCR + resultR;
										SummatoryCI = SummatoryCI + resultI;
										_rf++;
									}
									sum(SummatoryCR, SummatoryCI, expressCoefR[_rf], expressCoefI[_rf]);
									SummatoryCR = resultR; SummatoryCI = resultI;
									_rf = 0;
									SummatoryR = 0; SummatoryI = 0;
									while (_rf < maxExponent) {
										exponentiation(xValuesR, xValuesI, maxExponent - _rf, 0.0, 1);
										multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);
										SummatoryR = SummatoryR + resultR;
										SummatoryI = SummatoryI + resultI;
										_rf++;
									}
									sum(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
									SummatoryR = resultR; SummatoryI = resultI;
									multiplication(SummatoryCR, SummatoryCI, xValuesR, xValuesI);
									double saveR = resultR, saveI = resultI;
									multiplication(SummatoryCR, SummatoryCI, SolutionR[solvedIndex], SolutionI[solvedIndex]);
									subtraction(saveR, saveI, resultR, resultI);
									division(SummatoryR, SummatoryI, resultR, resultI);
									char result[20] = "";
									sprintf(result, "%s", convert2Exponential(resultR));
									char result_I[20] = "";
									sprintf(result_I, "%s", convert2Exponential(resultI));

									if (isEqual("1", result) && isEqual("0", result_I) && (summaR == 0 || summaI == 0) && maxExponent < 5) {
										re_complex(expressionCoefR[maxExponent], expressionCoefI[maxExponent], SolutionR[solvedIndex], SolutionI[solvedIndex]);
										sprintf(result, "%s", convert2Exponential(resultR));
										sprintf(result_I, "%s", convert2Exponential(resultI));
										if (isEqual("0", result) && isEqual("0", result_I)) {
											int v = 0, u = 0;
											while (v < maxExponent) {
												if (v != g) {
													RootR[u] = RootR[v];
													RootI[u] = RootI[v];
													u++;
												}
												v++;
											}
											countSolutions++;
											n = 0;
											g = 0;
											solvedIndex++;
											maxExponent--;
											int y = 1;
											while (y - 1 < maxExponent) {
												expressionCoefR[y] = expressCoefR[y]; expressionCoefI[y] = expressCoefI[y];
												y++;
											}
										}
									}
									else {
										double numR = summaR, numI = summaI, denR = 1, denI = 0;
										int w = 0, h = 0;
										while (w < maxExponent) {
											if (w != g) {
												subtraction(RootR[g], RootI[g], RootR[w], RootI[w]);
												resultSubR[h] = resultR;
												resultSubI[h] = resultI;
												h++;
											}
											w++;
										}
										int k = h;
										h = 1;
										while (h < k) {
											multiplication(resultSubR[0], resultSubI[0], resultSubR[h], resultSubI[h]);
											resultSubR[0] = resultR;
											resultSubI[0] = resultI;
											h++;
										}
										denR = resultSubR[0];
										denI = resultSubI[0];
										division(numR, numI, denR, denI);
										subtraction(RootR[g], RootI[g], resultR, resultI);
										RootR[g] = resultR;
										RootI[g] = resultI;
										double res_1 = 0, res_2 = 0, res_1Conj = 0, res_2Conj = 0;
										if (g % 2 == 1 && maxExponent > 4) {
											res_1 = RootR[g] - saveRootR;
											res_2 = RootI[g] - saveRootI;
											xValuesR = RootR[g - 1];
											xValuesI = RootI[g - 1];
											double saveRootR2 = RootR[g - 1];
											double	saveRootI2 = RootI[g - 1];
											int _rf = 0;
											double SummatoryR = 0, SummatoryI = 0;
											while (_rf < maxExponent) {
												exponentiation(xValuesR, xValuesI, (double)maxExponent - _rf, 0.0, 1);
												multiplication(expressionCoefR[_rf], expressionCoefI[_rf], resultR, resultI);
												expressCoefR[_rf] = expressionCoefR[_rf];
												expressCoefI[_rf] = expressionCoefI[_rf];
												SummatoryR = SummatoryR + resultR;
												SummatoryI = SummatoryI + resultI;
												_rf++;
											}
											sum(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
											expressCoefR[_rf] = expressionCoefR[_rf];
											expressCoefI[_rf] = expressionCoefI[_rf];
											summaR = resultR; summaI = resultI;
											double numR = summaR, numI = summaI, denR = 1, denI = 0;
											int w = 0, h = 0;
											while (w < maxExponent) {
												if (w != g - 1) {
													subtraction(RootR[g - 1], RootI[g - 1], RootR[w], RootI[w]);
													resultSubR[h] = resultR;
													resultSubI[h] = resultI;
													h++;
												}
												w++;
											}
											int k = h;
											h = 1;
											while (h < k) {
												multiplication(resultSubR[0], resultSubI[0], resultSubR[h], resultSubI[h]);
												resultSubR[0] = resultR;
												resultSubI[0] = resultI;
												h++;
											}
											denR = resultSubR[0];
											denI = resultSubI[0];
											division(numR, numI, denR, denI);
											subtraction(RootR[g - 1], RootI[g - 1], resultR, resultI);
											RootR[g - 1] = resultR;
											RootI[g - 1] = resultI;
											res_1Conj = RootR[g - 1] - saveRootR2;
											res_2Conj = RootI[g - 1] - saveRootI2;
										}
										if (abs(res_1) < 1E-16&&abs(res_2) < 1E-16&&maxExponent > 2 && n > 117 && g % 2 == 1 && maxExponent > 4) {
											if (abs(res_1Conj) < 1E-16&&abs(res_2Conj) < 1E-16&&maxExponent > 2 && n > 117) {
												int y = 1;
												while (y - 1 < maxExponent - 1) {
													multiplication(expressionCoefR[y - 1], expressionCoefI[y - 1], RootR[g - 1], RootI[g - 1]);
													sum(expressionCoefR[y], expressionCoefI[y], resultR, resultI);
													expressionCoefR[y] = resultR; expressionCoefI[y] = resultI;
													y++;
												}

												y = 1;
												while (y - 1 < maxExponent - 2) {
													multiplication(expressionCoefR[y - 1], expressionCoefI[y - 1], SolutionR[solvedIndex], SolutionI[solvedIndex]);
													sum(expressionCoefR[y], expressionCoefI[y], resultR, resultI);
													expressionCoefR[y] = resultR; expressionCoefI[y] = resultI;
													y++;
												}
												solvedIndex++;
												SolutionR[solvedIndex] = RootR[g - 1]; SolutionI[solvedIndex] = RootI[g - 1];
												solvedIndex++;
												int v = 0, u = 0;
												while (v < maxExponent) {
													if (v != g - 1 && v != g) {
														RootR[u] = RootR[v];
														RootI[u] = RootI[v];
														u++;
													}
													v++;
												}
												maxExponent = maxExponent - 2;
												countSolutions = countSolutions + 2;
												n = 0;
												g = 0;
											}
											else {
												int y = 1;
												while (y - 1 < maxExponent - 1) {
													multiplication(expressionCoefR[y - 1], expressionCoefI[y - 1], SolutionR[solvedIndex], SolutionI[solvedIndex]);
													sum(expressionCoefR[y], expressionCoefI[y], resultR, resultI);
													expressionCoefR[y] = resultR; expressionCoefI[y] = resultI;
													y++;
												}
												solvedIndex++;
												int v = 0, u = 0;
												while (v < maxExponent) {
													if (v != g) {
														RootR[u] = RootR[v];
														RootI[u] = RootI[v];
														u++;
													}
													v++;
												}
												maxExponent--;
												countSolutions++;
												n = 0;
												g = 0;
											}
										}
										else {
											if (notSolved) {
												for (r = 0; r <= maxExponent; r++) {
													expresR[r] = expressionCoefR[r];
													expresI[r] = expressionCoefI[r];
												}
												sumRootsR = 0; sumRootsI = 0;
												for (int kw = 0; kw < maxExponent; kw++) {
													if (kw != g) {
														int y = 1;
														while (y - 1 < maxExponent) {
															multiplication(expresR[y - 1], expresI[y - 1], RootR[kw], RootI[kw]);
															sum(expresR[y], expresI[y], resultR, resultI);
															expresR[y] = resultR; expresI[y] = resultI;
															y++;
														}
													}
													sum(sumRootsR, sumRootsI, RootR[kw], RootI[kw]);
													sumRootsR = resultR; sumRootsI = resultI;
													division(sumRootsR, sumRootsI, expressCoefR[1], expressCoefI[1]);
													if (abs(resultR) <= 1 && abs(resultR) > 0.99999&&abs(resultI) < 0.0001) {
														notSolved = false;
														breakAction = n + 237;
													}
												}
												multiplication(-1.0, 0.0, expresR[1], expresI[1]);
												double helperR = resultR, helperI = resultI;
												double fromHelperR, fromHelperI;
												double fromAlgR, fromAlgI;
												multiplication(0.73, 0.0, helperR, helperI);
												fromHelperR = resultR; fromHelperI = resultI;
												multiplication(0.27, 0.0, RootR[g], RootI[g]);
												fromAlgR = resultR; fromAlgI = resultI;
												sum(fromAlgR, fromAlgI, fromHelperR, fromHelperI);
												RootR[g] = resultR;
												RootI[g] = resultI;
											}
											if (g >= 1) {
												double rootR1, rootI1, rootR2, rootI2;
												multiplication(RootR[g - 1], RootI[g - 1], -1.0, 0.0);
												rootR1 = resultR; rootI1 = resultI;
												multiplication(RootR[g], RootI[g], -1.0, 0.0);
												rootR2 = resultR; rootI2 = resultI;
												double bR, bI, cR, cI;
												sum(rootR1, rootI1, rootR2, rootI2);
												bR = resultR; bI = resultI;
												multiplication(rootR1, rootI1, rootR2, rootI2);
												cR = resultR; cI = resultI;
												multiplication(-1, 0, bR, bI);
												double minusbR = resultR, minusbI = resultI;
												multiplication(bR, bI, bR, bI);
												double bRquad = resultR, bIquad = resultI;
												multiplication(1.0, 0.0, cR, cI);
												double acR = resultR, acI = resultI;
												multiplication(2, 0, 1.0, 0.0);
												double twoaR = resultR, twoaI = resultI;
												multiplication(4, 0, acR, acI);
												double fouracR = resultR, fouracI = resultI;
												subtraction(bRquad, bIquad, fouracR, fouracI);
												double radicandR = resultR, radicandI = resultI;
												exponentiation(radicandR, radicandI, 0.5, 0, 1);
												double sqrtR = resultR, sqrtI = resultI;
												subtraction(minusbR, minusbI, sqrtR, sqrtI);
												double minusR = resultR, minusI = resultI;
												sum(minusbR, minusbI, sqrtR, sqrtI);
												double plusR = resultR, plusI = resultI;
												division(plusR, plusI, twoaR, twoaI);
												double x1R = resultR, x1I = resultI;
												division(minusR, minusI, twoaR, twoaI);
												double x2R = resultR, x2I = resultI;
												RootR[g - 1] = x1R; RootI[g - 1] = x1I;
												RootR[g] = x2R; RootI[g] = x2I;
											}
										}
									}
									g++;
								}
								n++;
							}
						}
						else {
							if (maxExponent > 40) {
								saveMaxExponent = maxExponent;
								g = 0;
								double expDerivateR[dime], expDerivateI[dime], saveExpDerivateR[dime], saveExpDerivateI[dime];
								_rf = 0;
								while (_rf < maxExponent) {
									multiplication(expressionCoefR[_rf], expressionCoefI[_rf], (double)maxExponent - _rf, 0.0);
									expDerivateR[_rf] = resultR;
									expDerivateI[_rf] = resultI;
									saveExpDerivateR[_rf] = resultR;
									saveExpDerivateI[_rf] = resultI;
									_rf++;
								}
								_rf = 0;
								double saveExpressionCoefRN[dime], saveExpressionCoefIN[dime];
								while (_rf <= maxExponent) {
									saveExpressionCoefRN[_rf] = expressionCoefR[_rf];
									saveExpressionCoefIN[_rf] = expressionCoefI[_rf];
									expressCoefR[_rf] = expressionCoefR[_rf];
									expressCoefI[_rf] = expressionCoefI[_rf];
									_rf++;
								}
								int countSolutions = 0;
								_rf = 0;
								while (_rf <= maxExponent) {
									expressCoefR[_rf] = expressionCoefR[_rf];
									expressCoefI[_rf] = expressionCoefI[_rf];
									_rf++;
								}
								saveMaxExponent = maxExponent;
								n = 0;
								RootR[g] = 0; RootI[g] = 0;
								while (countSolutions < saveMaxExponent) {
									if (n == 2000) {
										countSolutions++;
										n = 0;

										int y = 1;
										while (y - 1 < maxExponent) {
											multiplication(expressCoefR[y - 1], expressCoefI[y - 1], RootR[g], RootI[g]);
											sum(expressCoefR[y], expressCoefI[y], resultR, resultI);
											expressCoefR[y] = resultR; expressCoefI[y] = resultI;
											y++;
										}
										_rf = 0;
										while (_rf < maxExponent) {
											multiplication(expressCoefR[_rf], expressCoefI[_rf], (double)maxExponent - _rf, 0.0);
											expDerivateR[_rf] = resultR;
											expDerivateI[_rf] = resultI;
											_rf++;
										}
										g++;
										RootR[g] = RootR[g - 1]; RootI[g] = RootI[g - 1];
										maxExponent--;
									}
									else {
										double SummDerivateR = 0, SummDerivateI = 0;
										xValuesR = RootR[g];
										xValuesI = RootI[g];
										_rf = 0;
										double SummatoryR = 0, SummatoryI = 0;
										while (_rf < maxExponent) {
											exponentiation(xValuesR, xValuesI, maxExponent - _rf, 0.0, 1);
											multiplication(expressCoefR[_rf], expressCoefI[_rf], resultR, resultI);
											SummatoryR = SummatoryR + resultR;
											SummatoryI = SummatoryI + resultI;
											_rf++;
										}
										sum(SummatoryR, SummatoryI, expressCoefR[_rf], expressCoefI[_rf]);
										SummatoryR = resultR; SummatoryI = resultI;
										SummDerivateR = 0; SummDerivateI = 0;
										_rf = 0;
										while (_rf < maxExponent - 1) {
											exponentiation(xValuesR, xValuesI, maxExponent - _rf - 1, 0.0, 1);
											multiplication(expDerivateR[_rf], expDerivateI[_rf], resultR, resultI);
											SummDerivateR = SummDerivateR + resultR;
											SummDerivateI = SummDerivateI + resultI;
											_rf++;
										}
										sum(SummDerivateR, SummDerivateI, expDerivateR[_rf], expDerivateI[_rf]);
										SummDerivateR = resultR; SummDerivateI = resultI;
										division(SummatoryR, SummatoryI, SummDerivateR, SummDerivateI);
										subtraction(xValuesR, xValuesI, resultR, resultI);
										RootR[g] = resultR;
										RootI[g] = resultI;
										if (n > 1000) {
											xValuesR = RootR[g];
											xValuesI = RootI[g];
											_rf = 0;
											SummatoryR = 0; SummatoryI = 0;
											while (_rf < saveMaxExponent) {
												exponentiation(xValuesR, xValuesI, saveMaxExponent - _rf, 0.0, 1);
												multiplication(saveExpressionCoefRN[_rf], saveExpressionCoefIN[_rf], resultR, resultI);
												SummatoryR = SummatoryR + resultR;
												SummatoryI = SummatoryI + resultI;
												_rf++;
											}
											sum(SummatoryR, SummatoryI, saveExpressionCoefRN[_rf], saveExpressionCoefIN[_rf]);
											SummatoryR = resultR; SummatoryI = resultI;
											SummDerivateR = 0; SummDerivateI = 0;
											_rf = 0;
											while (_rf < saveMaxExponent - 1) {
												exponentiation(xValuesR, xValuesI, saveMaxExponent - _rf - 1, 0.0, 1);
												multiplication(saveExpDerivateR[_rf], saveExpDerivateI[_rf], resultR, resultI);
												SummDerivateR = SummDerivateR + resultR;
												SummDerivateI = SummDerivateI + resultI;
												_rf++;
											}
											sum(SummDerivateR, SummDerivateI, saveExpDerivateR[_rf], saveExpDerivateI[_rf]);
											SummDerivateR = resultR; SummDerivateI = resultI;
											division(SummatoryR, SummatoryI, SummDerivateR, SummDerivateI);
											subtraction(xValuesR, xValuesI, resultR, resultI);
											RootR[g] = resultR;
											RootI[g] = resultI;
										}
									}

									n++;
								}
								maxExponent = saveMaxExponent;
							}
						}
					}
				}
				int y = 0;
				char value[100] = "";
				char *pointer;
				if (maxExponent == 0) {
					notSolved = false;
				}
				while (y < maxExponent) {
					sprintf(value, "%s", convert2Exponential(RootR[y]));
					RootR[y] = strtod(value, &pointer);
					sprintf(value, "%s", convert2Exponential(RootI[y]));
					RootI[y] = strtod(value, &pointer);
					SolutionR[solvedIndex] = RootR[y];
					SolutionI[solvedIndex] = RootI[y];
					solvedIndex++; y++;
				}
				maxExponent = maxMaxExponent;
				if (maxExponent >= 2 && !notSolved&&SolutionR[0] != 0 && SolutionI[0] != 0) {
					int n = 0;
					while (n < 100) {
						g = 0;
						while (g < maxExponent) {
							xValuesR = SolutionR[g];
							xValuesI = SolutionI[g];
							int _rf = 0;
							double SummatoryR = 0, SummatoryI = 0;
							while (_rf < maxExponent) {
								exponentiation(xValuesR, xValuesI, (double)maxExponent - _rf, 0.0, 1);
								multiplication(saveExpressionCoefR[_rf], saveExpressionCoefI[_rf], resultR, resultI);
								SummatoryR = SummatoryR + resultR;
								SummatoryI = SummatoryI + resultI;
								_rf++;
							}
							sum(SummatoryR, SummatoryI, saveExpressionCoefR[_rf], saveExpressionCoefI[_rf]);
							double numR = resultR, numI = resultI, resultSubR[dime], resultSubI[dime], denR = 1, denI = 0;
							int w = 0, h = 0;
							while (w < maxExponent) {
								if (w != g) {
									subtraction(SolutionR[g], SolutionI[g], SolutionR[w], SolutionI[w]);
									resultSubR[h] = resultR;
									resultSubI[h] = resultI;
									h++;
								}
								w++;
							}
							int k = h;
							h = 1;
							while (h < k) {
								multiplication(resultSubR[0], resultSubI[0], resultSubR[h], resultSubI[h]);
								resultSubR[0] = resultR;
								resultSubI[0] = resultI;
								h++;
							}
							denR = resultSubR[0];
							denI = resultSubI[0];
							division(numR, numI, denR, denI);
							subtraction(SolutionR[g], SolutionI[g], resultR, resultI);
							SolutionR[g] = resultR;
							SolutionI[g] = resultI;
							g++;
						}
						n++;
					}
				}
				if (maxExponent >= 2 && !notSolved&&SolutionR[0] != 0) {
					int zz = 0;
					do {
						for (int ii = 1; ii < maxExponent; ii++) {
							double rootR1, rootI1, rootR2, rootI2;
							multiplication(SolutionR[ii - 1], SolutionI[ii - 1], -1.0, 0.0);
							rootR1 = resultR; rootI1 = resultI;
							multiplication(SolutionR[ii], SolutionI[ii], -1.0, 0.0);
							rootR2 = resultR; rootI2 = resultI;
							double bR, bI, cR, cI;
							sum(rootR1, rootI1, rootR2, rootI2);
							bR = resultR; bI = resultI;
							multiplication(rootR1, rootI1, rootR2, rootI2);
							cR = resultR; cI = resultI;
							multiplication(-1, 0, bR, bI);
							double minusbR = resultR, minusbI = resultI;
							multiplication(bR, bI, bR, bI);
							double bRquad = resultR, bIquad = resultI;
							multiplication(1.0, 0.0, cR, cI);
							double acR = resultR, acI = resultI;
							multiplication(2, 0, 1.0, 0.0);
							double twoaR = resultR, twoaI = resultI;
							multiplication(4, 0, acR, acI);
							double fouracR = resultR, fouracI = resultI;
							subtraction(bRquad, bIquad, fouracR, fouracI);
							double radicandR = resultR, radicandI = resultI;
							exponentiation(radicandR, radicandI, 0.5, 0, 1);
							double sqrtR = resultR, sqrtI = resultI;
							subtraction(minusbR, minusbI, sqrtR, sqrtI);
							double minusR = resultR, minusI = resultI;
							sum(minusbR, minusbI, sqrtR, sqrtI);
							double plusR = resultR, plusI = resultI;
							division(plusR, plusI, twoaR, twoaI);
							double x1R = resultR, x1I = resultI;
							division(minusR, minusI, twoaR, twoaI);
							double x2R = resultR, x2I = resultI;
							SolutionR[ii - 1] = x1R; SolutionI[ii - 1] = x1I;
							SolutionR[ii] = x2R; SolutionI[ii] = x2I;
						}
						zz++;
					} while (zz < 100);
				}

				g = 0;
				rootIndex = 1;
				sprintf(answers, "");
				while (g < maxExponent) {
					rootR = SolutionR[g];
					rootI = SolutionI[g];
					if (isContained("\\", saveEquation) || isContained("x^", saveEquation) ||
						(equation_solver == (boolean)true && isContained("x", saveEquation) &&
							isContained("x^", equation) == (boolean)false)) {
						convertComplex2Exponential(rootR, rootI);
						if (abs(rootR) < 1E-4) {
							rootR = 0;
						}
						if (abs(rootI) < 1E-4) {
							rootI = 0;
						}
						if (rootR > 0 && rootI > 0) {
							sprintf(answers, "%sx%d=%s+%si\n", answers, rootIndex, respR, respI);
							sprintf(roots, "%s\\%s+%si", roots, respR, respI);
						}
						else {
							if (rootR > 0 && rootI < 0) {
								sprintf(answers, "%sx%d=%s%si\n", answers, rootIndex, respR, respI);
								sprintf(roots, "%s\\%s%si", roots, respR, respI);
							}
							else {
								if (rootR < 0 && rootI > 0) {
									sprintf(answers, "%sx%d=%s+%si\n", answers, rootIndex, respR, respI);
									char rootRExp[100] = "";
									sprintf(rootRExp, "%s", respR);
									replace("-", "_", rootRExp);
									sprintf(rootRExp, "%s", expressionF);
									sprintf(roots, "%s\\%s+%si", roots, rootRExp, respI);
								}
								else {
									if (rootR < 0 && rootI < 0) {
										sprintf(answers, "%sx%d=%s%si\n", answers, rootIndex, respR, respI);
										char rootRExp[100] = "";
										sprintf(rootRExp, "%s", respR);
										replace("-", "_", rootRExp);
										sprintf(rootRExp, "%s", expressionF);
										sprintf(roots, "%s\\%s%si", roots, rootRExp, respI);
									}
									else {
										if (rootR == 0 && rootI == 0) {
											sprintf(answers, "%sx%d=%s\n", answers, rootIndex, respR);
											sprintf(roots, "%s\\%s", roots, respR);
										}
										else {
											if (rootR == 0 && rootI != 0) {
												sprintf(answers, "%sx%d=%si\n", answers, rootIndex, respI);
												char rootIExp[100] = "";
												sprintf(rootIExp, "%si", respI);
												if (isContained("-", rootIExp)) {
													replace("-", "_", rootIExp);
													sprintf(rootIExp, "%s", expressionF);
												}
												sprintf(roots, "%s\\%s", roots, rootIExp);
											}
											else {
												if (rootR != 0 && rootI == 0) {
													sprintf(answers, "%sx%d=%s\n", answers, rootIndex,
														respR);
													char rootRExp[100] = "";
													sprintf(rootRExp, "%s", respR);
													if (isContained("-", rootRExp)) {
														replace("-", "_", rootRExp);
														sprintf(rootRExp, "%s", expressionF);
													}
													sprintf(roots, "%s\\%s", roots, rootRExp);
												}
												else {
													sprintf(answers, "%sx%d=%s+%si\n", answers, rootIndex,
														respR, respI);
													sprintf(roots, "%s\\%s+%si", roots, respR, respI);
												}
											}
										}
									}
								}
							}
						}
					}
					rootIndex++;
					g++;
					if (roots[0] == '\\') {
						int y = 1;
						for (y = 1; y < abs((int)strlen(roots)); y++) {
							roots[y - 1] = roots[y];
						}
						roots[y - 1] = '\0';
					}
					if (isContained(".000000", roots)) {
						replace(".000000", "", roots);
						sprintf(roots, "%s", expressionF);
					}
					if (isContained(".000000", answers)) {
						replace(".000000", "", answers);
						sprintf(answers, "%s", expressionF);
					}
				}
				if (isContained("__", roots)) {
					replace("__", "_", roots);
					sprintf(roots, "%s", expressionF);
				}
				if (polySimplifier == (boolean)false) {
					if (isContained(".000000", answers)) {
						replace(".000000", "", answers);
						sprintf(answers, "%s", expressionF);
					}
					sprintf(expressionF, "%s", answers);
				}
			}
			else {
				if (isContained(".000000", answers)) {
					replace(".000000", "", answers);
					sprintf(answers, "%s", expressionF);
				}
				sprintf(expressionF, "%s", answers);
				return resultR;
			}
		}
		else {
			solving = true;
			equationSolverRunning = false;
			removeDuplPars(saveToZeroDiv);
			sprintf(saveToZeroDiv, "%s", expressionF);
			if (isContained("(-", saveToZeroDiv)) {
				replace("(-", "(_", saveToZeroDiv);
				sprintf(saveToZeroDiv, "%s", expressionF);
			}
			if (isContained("+-", saveToZeroDiv)) {
				replace("+-", "+_", saveToZeroDiv);
				sprintf(saveToZeroDiv, "%s", expressionF);
			}
			replaceTimes = 0;
			if (isContained("(res)", toCalcX)) {
				replace("(res)", "x", toCalcX);
				sprintf(saveToZeroDiv, "%s", expressionF);
			}
			solveMath(saveToZeroDiv);
			lastDividerI = resultI;
			lastDividerR = resultR;
		}
	}
	equationSolverRunning = false;
	solving = true;
	return 0;
}
void simpleSimplifyPolynomial(char expression[DIM]) {
	isDivisible = true;
	replaceTimes = 0;
	int countLeft = countOccurrences("(", expression);
	int countRight = countOccurrences(")", expression);
	if (countRight > countLeft) {
		sprintf(expressionF, "(%s", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (countRight < countLeft) {
		sprintf(expressionF, "%s)", expression);
		sprintf(expression, "%s", expressionF);
	}
	lastDividerR = 1;
	LastDividerR = 1;
	sprintf(roots, "");
	char expressionS[DIM] = "";
	char toSimplify[DIM] = "";
	char exprProcessed[DIM] = "";
	sprintf(expressionS, "%s", expression);
	if (isContained(")(", expressionS)) {
		replace(")(", ")*(", expressionS);
		sprintf(expressionS, "%s", expressionF);
	}
	char divExpression[DIM] = "";
	int saveStrEnd = 0;
	int i = 0, j = 0;
	char newExpression[DIM] = "";
	int v = 0, vv = 0, vvv = 0, po = 0;
	char operaTor[DIM] = "";
	char operators[DIM] = "";
	int error = 0;
	char polys[dime][dime];
	while (expressionS[v] != '\0') {
		sprintf(operaTor, "%c%c%c", expressionS[v], expressionS[v + 1], expressionS[v + 2]);

		if (expressionS[v] == '(' && expressionS[v + 1] == '/') {
			v = v + 2;
			error = 1;
		}
		if (expressionS[v] == ')' && expressionS[v + 1] == ')' && error == 1) {
			v++;
			error = 0;
		}
		polys[vv][po] = expressionS[v];
		po++;

		if (isEqual(")+(", operaTor)) {
			operators[vv] = '+';
			polys[vv][po] = '\0';
			vv++;
			v++;
			po = 0;
		}
		if (isEqual(")*(", operaTor)) {
			operators[vv] = '*';
			polys[vv][po] = '\0';
			vv++;
			v++;
			po = 0;
		}
		if (isEqual(")/(", operaTor)) {
			operators[vv] = '/';
			polys[vv][po] = '\0';
			vv++;
			v++;
			po = 0;
		}
		if (isEqual(")-(", operaTor)) {
			operators[vv] = '-';
			polys[vv][po] = '\0';
			vv++;
			v++;
			po = 0;
		}
		v++;
		vvv++;
	}
	polys[vv][po] = '\0';
	if (vv == 0) {
		sprintf(expressionF, "%s", expressionS);
	}
	else {
		char polyN[DIM] = "";
		int m = 0, n = 0;
		for (n = 0; n <= vv; n++) {
			for (m = 0; polys[n][m] != '\0'; m++) {
				sprintf(polyN, "%s%c", polyN, polys[n][m]);
			}
			sprintf(polyN, "");
		}
		operators[vv] = '\0';
		replaceTimes = 0;

		int g = 0;
		int so = 0;
		char poly_1[DIM] = "", poly_2[DIM] = "";
		for (so = 0; so < vv; so++) {
			int sa = so;
			while (operators[so] == '/') {
				g = 0;
				while (polys[sa][g] != '\0') {
					poly_1[g] = polys[sa][g];
					g++;
				}
				poly_1[g] = '\0';
				g = 0;
				while (polys[so + 1][g] != '\0') {
					poly_2[g] = polys[so + 1][g];
					g++;
				}
				poly_2[g] = '\0';
				div_polynomial(poly_1, poly_2);
				sprintf(poly_1, "%s", expressionF);
				sprintf(poly_2, "(0x^1+1)");
				g = 0;
				while (poly_1[g] != '\0') {
					polys[sa][g] = poly_1[g];
					g++;
				}
				polys[sa][g] = '\0';
				g = 0;
				while (poly_2[g] != '\0') {
					polys[so + 1][g] = poly_2[g];
					g++;
				}
				polys[so + 1][g] = '\0';
				operators[so] = '*';
				so++;
			}
		}
		operators[so] = '\0';
		for (so = 0; so < vv; so++) {
			int sa = so;
			while (operators[so] == '*') {
				g = 0;
				while (polys[sa][g] != '\0') {
					poly_1[g] = polys[sa][g];
					g++;
				}
				poly_1[g] = '\0';
				g = 0;
				while (polys[so + 1][g] != '\0') {
					poly_2[g] = polys[so + 1][g];
					g++;
				}
				poly_2[g] = '\0';
				multi_polynomial(poly_1, poly_2);
				sprintf(poly_1, "%s", expressionF);
				sprintf(poly_2, "(0x^1+1)");


				g = 0;
				while (poly_1[g] != '\0') {
					polys[sa][g] = poly_1[g];
					g++;
				}
				polys[sa][g] = '\0';
				g = 0;
				while (poly_2[g] != '\0') {
					polys[so + 1][g] = poly_2[g];
					g++;
				}
				polys[so + 1][g] = '\0';
				operators[so] = '*';
				so++;
			}
		}

		int h = 0;
		for (h = 0; h < vv; h++) {
			if (h == 0) {
				g = 0;
				while (polys[h][g] != '\0') {
					poly_1[g] = polys[h][g];
					g++;
				}
				poly_1[g] = '\0';
			}
			if (operators[h] == '*') {
				g = 0;
				while (polys[h + 1][g] != '\0') {
					poly_2[g] = polys[h + 1][g];
					g++;
				}
				poly_2[g] = '\0';
				multi_polynomial(poly_1, poly_2);
				sprintf(poly_1, "%s", expressionF);
			}
			if (operators[h] == '/') {
				g = 0;
				while (polys[h + 1][g] != '\0') {
					poly_2[g] = polys[h + 1][g];
					g++;
				}
				poly_2[g] = '\0';
				div_polynomial(poly_1, poly_2);
				sprintf(poly_1, "%s", expressionF);
			}
			if (operators[h] == '-') {
				g = 0;
				while (polys[h + 1][g] != '\0') {
					poly_2[g] = polys[h + 1][g];
					g++;
				}
				poly_2[g] = '\0';
				sub_polynomial(poly_1, poly_2);
				sprintf(poly_1, "%s", expressionF);
			}
			if (operators[h] == '+') {
				g = 0;
				while (polys[h + 1][g] != '\0') {
					poly_2[g] = polys[h + 1][g];
					g++;
				}
				poly_2[g] = '\0';
				sum_polynomial(poly_1, poly_2);
				sprintf(poly_1, "%s", expressionF);
			}
		}
		removeDuplPars(poly_1);
		sprintf(poly_1, "%s", expressionF);
		sprintf(expressionF, "(%s)", poly_1);
		if (isContained(".000000", expressionF)) {
			replace(".000000", "", expressionF);
		}
	}

}

void simplifyPolynomial(char expression[DIM]) {
	if (isContained(")+0", expression) && expression[strEnd] == '\0') {
		expression[strStart + 1] = '\0';
	}
	if (!isContained("((", expression) && !isContained("))", expression)) {
		simpleSimplifyPolynomial(expression);
	}
	else {
		replaceTimes = 0;
		int parL = countOccurrences("(", expression);
		int parR = countOccurrences(")", expression);
		if (parL == 1 && parR == 1 && !isContained("[", expression)) {
			replace("(", "", expression);
			replace(")", "", expressionF);
			sprintf(expression, "%s", expressionF);
		}
		isDivisible = true;
		sprintf(roots, "");
		char expressionS[DIM] = "";
		char Expression[DIM] = "";
		sprintf(expressionS, "%s", expression);
		int i = 0, j = 0;
		replaceTimes = 0;
		if (isContained(")(", expressionS)) {
			replace(")(", ")*(", expressionS);
			sprintf(expressionS, "%s", expressionF);
		}
		int parent[DIM];
		int s = 0;
		for (s = 0; s < abs((int)strlen(expressionS)); s++) {
			parent[s] = 0;
		}
		getNumerationPol(expressionS);
		int maxPar = 0;
		for (s = 0; expressionS[s] != '\0' && s < abs((int)strlen(expressionS)); s++) {
			parent[s] = parentPol[s];
			if (parent[s] > maxPar) {
				maxPar = parent[s];
			}
		}
		int countMax = 0;
		for (s = 0; expressionS[s] != '\0' && s < abs((int)strlen(expressionS)); s++) {
			parent[s] = parentPol[s];
			if (parent[s] == maxPar) {
				countMax++;
			}
		}
		int y = 0, u = 0, d = 0;
		char splitPoly[DIM] = "";
		char operators[dime] = "";
		char getSimpleExpression[DIM] = "";
		char getRestExpression[DIM] = "";
		char parentNum[dime][dime];
		int type[dime];
		if (maxPar > 0) {
			if (parent[0] == 0) {
				y = 0;
				while (parent[y] == 0 && y < abs((int)strlen(expressionS))) {
					getSimpleExpression[y] = expressionS[y];
					y++;
				}
				y--;
				getSimpleExpression[y] = '\0';
				int c = 0;
				while (y < (int)strlen(expressionS)) {
					getRestExpression[c] = expressionS[y];
					c++;
					y++;
				}
				getRestExpression[c] = '\0';
				sprintf(expressionF, "((%s)*(0x^1+1))%s", getSimpleExpression, getRestExpression);
				sprintf(expressionS, "%s", expressionF);
				getNumerationPol(expressionS);
				maxPar = 0;
				for (s = 0; expressionS[s] != '\0' && s < abs((int)strlen(expressionS)); s++) {
					parent[s] = parentPol[s];
					if (parent[s] > maxPar) {
						maxPar = parent[s];
					}
				}
			}
			if (parent[strlen(expressionS) - 1] == 0) {
				int c = 0;
				y = (int)strlen(expressionS) - 1;
				while (parent[y] == 0) {
					y--;
				}
				y = y + 2;
				int d = y;
				c = 0;
				while (parent[y] == 0 && y < abs((int)strlen(expressionS))) {
					getSimpleExpression[c] = expressionS[y];
					c++;
					y++;
				}
				getSimpleExpression[c] = '\0';
				c = 0;
				y = 0;
				while (y < d) {
					getRestExpression[c] = expressionS[y];
					c++;
					y++;
				}
				getRestExpression[c] = '\0';
				sprintf(expressionF, "%s(%s*(0x^1+1))", getRestExpression, getSimpleExpression);
				sprintf(expressionS, "%s", expressionF);
				getNumerationPol(expressionS);
				maxPar = 0;
				for (s = 0; expressionS[s] != '\0' && s < abs((int)strlen(expressionS)); s++) {
					parent[s] = parentPol[s];
					if (parent[s] > maxPar) {
						maxPar = parent[s];
					}
				}
			}
			y = 0;
			while (expressionS[y] != '\0') {
				if (parent[y] == 0) {
					d = 0;
					while (parent[y] == 0) {
						parentNum[u][d] = expressionS[y];
						y++;
						d++;
					}
					if ((expressionS[y - 1] == '+' || expressionS[y - 1] == '-' ||
						expressionS[y - 1] == '*' || expressionS[y - 1] == '/') && expressionS[y] == '(') {
						operators[u] = expressionS[y - 1];
						y--;
						d--;
					}
					parentNum[u][d] = '\0';
					for (d = 0; parentNum[u][d] != '\0'; d++) {
						sprintf(splitPoly, "%s%c", splitPoly, parentNum[u][d]);
					}
					sprintf(splitPoly, "%s\n%c", splitPoly, operators[u]);
					type[u] = 0;
					u++;
				}
				else {
					d = 0;
					int h = parent[y];
					y++;
					while (parent[y] != h) {
						parentNum[u][d] = expressionS[y];
						y++;
						d++;
					}
					if ((expressionS[y + 1] == '+' || expressionS[y + 1] == '-' ||
						expressionS[y + 1] == '*' || expressionS[y + 1] == '/') && expressionS[y] == ')') {
						operators[u] = expressionS[y + 1];
						y++;
					}
					parentNum[u][d] = '\0';
					for (d = 0; parentNum[u][d] != '\0'; d++) {
						sprintf(splitPoly, "%s%c", splitPoly, parentNum[u][d]);
					}
					sprintf(splitPoly, "%s\n", splitPoly);
					type[u] = 1;
					u++;
				}
				y++;
			}
			char expr[DIM] = "";
			y = 0;
			int size[dime];
			while (y < u) {
				d = 0;
				while (parentNum[y][d] != '\0') {
					expr[d] = parentNum[y][d];
					d++;
				}
				expr[d] = '\0';
				if (type[y] == 1) {
					simplifyPolynomial(expr);
					size[y] = (int)strlen(expressionF);
				}
				else {
					simpleSimplifyPolynomial(expr);
					size[y] = (int)strlen(expressionF);
				}
				d = 0;
				while (expressionF[d] != '\0') {
					parentNum[y][d] = expressionF[d];
					d++;
				}
				parentNum[y][d] = '\0';
				y++;
			}
			y = 0;
			d = 0;
			int p = 0;
			char newExpression[DIM] = "";
			while (y < u) {
				d = 0;
				if (!(parentNum[y][d] == '(' && parentNum[y][d + 1] == '(')) {
					newExpression[p] = '(';
					p++;
				}
				while (d < size[y]) {
					newExpression[p] = parentNum[y][d];
					d++;
					p++;
				}
				if (!(parentNum[y][d - 1] == ')' && parentNum[y][d - 2] == ')')) {
					newExpression[p] = ')';
					p++;
				}
				if (operators[y] == '+' || operators[y] == '-' ||
					operators[y] == '*' || operators[y] == '/') {
					newExpression[p] = operators[y];
					p++;
				}
				y++;
			}
			newExpression[p] = '\0';
			simpleSimplifyPolynomial(newExpression);
		}
		else {
			simpleSimplifyPolynomial(expression);
		}
		if (!isDivisible) {
			sprintf(expressionF, "%s", saveExpressionF);
		}
		if (isContained(".000000", expressionF)) {
			replace(".000000", "", expressionF);
		}
	}
}

void getNumerationPol(char expressionS[DIM]) {
	int parent[DIM];
	int s = 0, c, d, k, l, h;
	for (s = 0; s < abs((int)strlen(expressionS)); s++) {
		parent[s] = 0;
	}
	int cp = 0, mark = 0;
	c = 0;
	d = 0;
	k = 0;
	l = 0;
	h = 0;
	for (s = 0; expressionS[s] != '\0' && s < abs((int)strlen(expressionS)); s++) {
		if (expressionS[s] == '(' && expressionS[s + 1] == '(') {
			d = 0;
			c++;
			parent[s] = c;
			d = 1;
			k = c;
		}
		else {
			if (expressionS[s] == ')' && expressionS[s - 1] == ')') {
				d = 0;
				h = 0;
				l = 2;
				do {
					l = 0;
					h = 0;
					while (h < abs((int)strlen(expressionS))) {
						if (parent[h] == k) {
							l++;
						}
						if (l == 2) {
							l = 0;
							k--;
						}
						h++;
					}
				} while (l == 2);
				h = 0;
				while (l != 1 && h < abs((int)strlen(expressionS))) {
					h = 0;
					l = 0;
					while (h < abs((int)strlen(expressionS))) {
						if (parent[h] == k) {
							l++;
						}
						if (l == 2) {
							k--;
							h = 0;
							l = 0;
						}
						h++;
					}
				}
				parent[s] = k;
			}
			else {
				parent[s] = 0;
			}
		}
	}

	char pare[DIM] = "", pareF[DIM] = "";
	for (s = 0; expressionS[s] != '\0' && s < abs((int)strlen(expressionS)); s++) {
		parentPol[s] = parent[s];
		sprintf(pareF, "%s%d", pare, parent[s]);
		sprintf(pare, "%s", pareF);
	}
}

int getCorrectExponent(char expression[DIM], char maxExp[10], int maxExponent) {
	replaceTimes = 0;
	char  saveToCalcX[DIM] = "";
	sprintf(saveToCalcX, "%s", expression);
	char divider[DIM] = "";
	do {
		sprintf(saveToCalcX, "%s", expression);
		char to_replace[DIM] = "";
		char replacement[DIM] = "";
		sprintf(to_replace, "(res)^%d", maxExponent);
		if (!isContained(to_replace, saveToCalcX)) {
			while (!isContained(to_replace, saveToCalcX)) {
				maxExponent--;
				sprintf(to_replace, "(res)^%d", maxExponent);
			}
		}
		sprintf(replacement, "(aaaa)^%d", maxExponent);
		if (isContained(to_replace, saveToCalcX)) {
			replace(to_replace, replacement, saveToCalcX);
			if (isContained("res", expressionF)) {
				replace("res", "0", expressionF);
				sprintf(saveToCalcX, "%s", expressionF);
			}
			else {
				sprintf(saveToCalcX, "%s", expressionF);
			}
		}
		char saveEquationF[DIM] = "";
		sprintf(saveEquationF, "%s", saveToCalcX);
		if (isContained("aaaa", saveToCalcX)) {
			replace("aaaa", "0", saveToCalcX);
			sprintf(saveToCalcX, "%s", expressionF);
		}
		solveMath(saveToCalcX);
		sprintf(saveToCalcX, "%s", saveEquationF);
		lastElement = resultR, lastElementI = resultI;
		if (isContained("aaaa", saveToCalcX)) {
			replace("aaaa", "1", saveToCalcX);
			sprintf(saveToCalcX, "%s", expressionF);
		}
		solveMath(saveToCalcX);
		subtraction(resultR, resultI, lastElement, lastElementI);
		lastDividerR = resultR; lastDividerI = resultI;
		if (lastDividerR == 0 && lastDividerI == 0 && maxExponent > 1) {
			maxExponent--;
		}
		else {
			return maxExponent;
		}
	} while (lastDividerR == 0 && lastDividerI == 0 && maxExponent >= 1);
	return maxExponent;
}



void simplifyExpression(char data[DIM]) {
	boolean toSimplify = true;
	char expression[DIM] = "";
	sprintf(expression, "%s", data);
	isDivisible = true;
	sprintf(expressionF, "");
	sprintf(roots, "");
	sprintf(answers, "");
	replaceTimes = 0;
	if (isEqual("x", expression)) {
		replace("x", "(X-0)", expression);
		sprintf(expression, "%s", expressionF);
		replace("X", "x", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("*1i", expression)) {
		replace("*1i", "i", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("-x", expression)) {
		replace("-x", "+_1x", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("+x", expression)) {
		replace("+x", "+1x", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("(x)", expression)) {
		replace("(x)", "X", expression);
		replace("X", "x", expressionF);
		sprintf(expression, "%s", expressionF);
	}
	replaceTimes = 0;
	if (isContained(")-(", expression)) {
		replace(")-(", ")+_1*(", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("(-", expression)) {
		replace("(-", "(_", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("-", expression)) {
		replace("-", "+_", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained(")_(", expression)) {
		replace(")_(", ")-(", expression);
		sprintf(expression, "%s", expressionF);
	}
	replaceTimes = 0;
	if (isContained("*x", expression)) {
		replace("*x", "x", expression);
		sprintf(expression, "%s", expressionF);
	}
	replaceTimes = 1;
	while (isContained("x", expression)) {
		if (isContained("x", expression) && expression[strEnd] != '^') {
			replace("x", "X^1", expression);
			sprintf(expression, "%s", expressionF);
		}
		else {
			expression[strStart] = 'X';
		}
	}
	replaceTimes = 0;
	if (isContained("X", expression)) {
		replace("X", "x", expression);
		sprintf(expression, "%s", expressionF);
	}
	char checkDivision[DIM] = "";
	sprintf(checkDivision, "%s", expression);
	boolean hasSimpleDivisions = false;
	if ((isContained("/", expression)) && studyFunction == false) {
		if (!isContained("/x", expression) && isContained("/", expression)) {
			int i = 0;
			for (i = 0; i < abs((int)strlen(expression)); i++) {
				if (expression[i] == '(') {
					char collectChars[DIM] = "";
					int y = 0;
					boolean hasOperators = false;
					while ((verifyNumber(expression[i]) || (expression[i] == '/'&&expression[i + 1] != 'x') || expression[i] == '*' || expression[i] == '^' || expression[i] == '+' || expression[i] == '(' || expression[i] == ')' || expression[i] == 'i') && i < abs((int)strlen(expression))) {
						collectChars[y] = expression[i];
						if (expression[i] == '/' || expression[i] == '*' || expression[i] == '^') {
							hasOperators = true;
						}
						y++, i++;
					}
					collectChars[y] = '\0';


					if (abs((int)(strlen(collectChars))) > 0 && hasOperators) {
						solveMath(collectChars);
						char replacement[DIM] = "";
						sprintf(replacement, "%G+%Gi", resultR, resultI);
						replaceTimes = 0;
						if (isContained("-", replacement)) {
							replace("-", "_", replacement);
							sprintf(replacement, "%s", expressionF);
						}
						replaceTimes = 1;
						replace(collectChars, replacement, expression);
						sprintf(expression, "%s", expressionF);
						i = 0;
					}
				}
			}
		}
		if (isContained("/", expression)) {

			char addPars[DIM] = "";
			int y = 0, w = 0;
			boolean division = false;
			while (y < abs((int)strlen(expression))) {
				if (expression[y] == '(') {
					addPars[w] = expression[y]; w++, y++;
					while (expression[y] != ')') {
						addPars[w] = expression[y];
						w++; y++;
					}
				}
				if (verifyForNumbers(expression[y])) {
					if (expression[y - 1] == '/') {
						division = true;
					}
					else {
						division = false;
					}
					addPars[w] = '('; w++;
					while (verifyForNumbers(expression[y])) {
						addPars[w] = expression[y];
						w++; y++;
					}
					addPars[w] = ')'; w++;

					if ((expression[y] == '+' || y == strlen(expression) || expression[y] == ')') && !division) {

						addPars[w] = '/'; w++;
						addPars[w] = '('; w++;
						addPars[w] = '1'; w++;
						addPars[w] = ')'; w++;
					}
					addPars[w] = expression[y];
					w++;
				}
				else {
					addPars[w] = expression[y];
					division = false;
					w++;
				}
				y++;
			}
			sprintf(expression, "%s", addPars);
			if (verifyNumber(expression[strlen(expression) - 1]) || expression[strlen(expression) - 1] == 'x') {
				int u = abs((int)strlen(expression)) - 1;
				while (u > 0 && verifyNumber(expression[u])) {
					u--;
				}
				if (expression[u] == '+') {
					sprintf(expression, "%s/1", expression);
				}
			}
			for (int h = 0; h < abs((int)strlen(expression)); h++) {
				if (verifyForNumber(expression[h]) && (h == 0 || expression[h - 1] == '+')) {
					char saveNum[dime] = "";
					int k = 0;
					if (expression[h - 1] == '+') {
						saveNum[k] = '+'; k++;
					}
					while (verifyForNumber(expression[h]) && expression[h] != '+'&&expression[h] != '/'&& h < abs((int)strlen(expression))) {
						saveNum[k] = expression[h];
						k++; h++;
					}
					saveNum[k] = '\0';
					char nextChar = expression[h];
					if (expression[h] == '+' || (h == abs((int)strlen(expression)) && saveNum[0] == '+')) {
						char replacement[dime] = "";
						sprintf(replacement, "%s/1%c", saveNum, nextChar);
						replaceTimes = 1;
						sprintf(saveNum, "%s%c", saveNum, nextChar);
						replace(saveNum, replacement, expression);
						sprintf(expression, "%s", expressionF);
					}
					if (expression[h] == '/'&&verifyNumber(expression[h + 1])) {
						h++;
						while (verifyNumber(expression[h]) && h < abs((int)strlen(expression))) {
							h++;
						}
					}
				}
			}
		}
	}
	replaceTimes = 0;
	if (isContained(")D(", expression)) {
		replace(")D(", ")/(", expression);
		sprintf(expression, "%s", expressionF);
	}

	if (isContained("/x+", expression) && studyFunction == (boolean)false) {
		replace("/x+", "/(x+0)+", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("/x", expression) && strEnd == abs((int)strlen(expression)) && studyFunction == (boolean)false) {
		replace("/x", "/(x+0)", expression);
		sprintf(expression, "%s", expressionF);
	}
	replaceTimes = 1;
	while (isContained("/", expression) && studyFunction == (boolean)false) {
		if (isContained("/", expression) && strStart > 0 && verifyNumber(expression[strStart - 1])) {
			int y = strStart - 1;
			while (y > 0 && verifyNumber(expression[y])) {
				y--;
			}
			if (y == 0 || expression[y] == '+' || expression[y] == '*') {
				int w = 0;
				if (y > 0) {
					y++;
				}
				char number[DIM] = "";
				while (verifyNumber(expression[y])) {
					number[w] = expression[y];
					w++; y++;
				}
				number[w] = '\0';
				char replacement[DIM] = "";
				char toReplace[DIM] = "";
				sprintf(toReplace, "%s/", number);
				sprintf(replacement, "(0x+%s)D", number);
				replace(toReplace, replacement, expression);
				sprintf(expression, "%s", expressionF);
			}
			else {
				if (isContained("/", expression)) {
					expression[strStart] = 'D';
				}
			}
		}
		else {
			if (isContained("/", expression)) {
				expression[strStart] = 'D';
			}
		}
	}
	replaceTimes = 0;
	if (isContained("D", expression)) {
		replace("D", "/", expression);
		sprintf(expression, "%s", expressionF);
	}
	replaceTimes = 1;
	while (isContained("/", expression) && studyFunction == (boolean)false) {
		if (isContained("/", expression) && verifyNumber(expression[strStart + 1])) {
			int y = strStart + 1;
			int w = 0;
			char number[DIM] = "";
			while (verifyNumber(expression[y])) {
				number[w] = expression[y];
				w++; y++;
			}
			number[w] = '\0';
			char replacement[DIM] = "";
			char toReplace[DIM] = "";
			sprintf(toReplace, "/%s", number);
			sprintf(replacement, "/(0x+%s)", number);
			replace(toReplace, replacement, expression);
			sprintf(expression, "%s", expressionF);

		}
		else {
			if (isContained("/", expression)) {
				expression[strStart] = 'D';
			}
		}
	}
	replaceTimes = 0;
	if (isContained("D", expression)) {
		replace("D", "/", expression);
		sprintf(expression, "%s", expressionF);
	}

	if (isContained("M", expression)) {
		replace("M", "*", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (!isContained("/x", expression) && !isContained("x/", expression) && studyFunction == (boolean)false) {
		sprintf(expression, "%s+0", expression);
	}
	if (isContained("))/(", expression) && toSimplify == (boolean)true) {
		sprintf(expressionF, "%s", expression);
		simplifyPolynomial(expressionF);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("/", expression) && studyFunction == (boolean)false && toSimplify == (boolean)true) {
		if (isContained("x", expression)) {
			replaceTimes = 1;
			while (isContained("x", expression)) {
				if (verifyNumber(expression[strStart - 1])) {
					replace("x", "*X", expression);
					sprintf(expression, "%s", expressionF);
				}
				else {
					if (expression[strStart - 1] == '/' && !(expression[strEnd] == '^')) {
						replace("x", "X", expression);
						sprintf(expression, "%s", expressionF);
					}
					else {
						if (expression[strEnd] == '^') {
							char getExp[12] = "";
							int h = 0, m = strEnd + 1;
							while (verifyNumber(expression[m]) && m < abs((int)strlen(expression))) {
								getExp[h] = expression[m];
								h++; m++;
							}
							getExp[h] = '\0';
							char replacement[DIM] = "";
							char toReplace[DIM] = "";
							sprintf(replacement, "(X^%sS0)", getExp);
							sprintf(toReplace, "x^%s", getExp);
							replace(toReplace, replacement, expression);
							sprintf(expression, "%s", expressionF);
						}
						else {
							replace("x", "X", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
				}
			}
			replaceTimes = 0;
			if (isContained("X", expression)) {
				replace("X", "x", expression);
				sprintf(expression, "%s", expressionF);
			}
		}
		replaceTimes = 0;
		if (isContained("X", expression)) {
			replace("X", "x", expression);
			sprintf(expression, "%s", expressionF);
		}
		replaceTimes = 0;
		if (isContained("X", expression)) {
			replace("X", "x", expression);
			sprintf(expression, "%s", expressionF);
		}
		replaceTimes = 1;
		if (isContained("x", expression) && strStart == 0) {
			replace("x", "1x", expression);
			sprintf(expression, "%s", expressionF);
		}
		replaceTimes = 0;
		if (isContained("_x", expression)) {
			replace("_x", "_1x", expression);
			sprintf(expression, "%s", expressionF);
		}
		if (isContained("+x", expression)) {
			replace("+x", "+1x", expression);
			sprintf(expression, "%s", expressionF);
		}
		replaceTimes = 0;
		if (isContained("_(", expression)) {
			replace("_(", "(_1)(", expression);
			sprintf(expression, "%s", expressionF);
		}
		replaceTimes = 1;
		if (isContained("/", expression) && studyFunction == (boolean)false) {
			replaceTimes = 1;
			if (isContained(")/(", expression)) {
				replaceTimes = 0;
				if (isContained("+_(", expression)) {
					replaceTimes = 1;
					while (isContained("+_(", expression)) {
						char poly[DIM] = "";
						int i = strEnd, h = 0;
						int kr = 0, kl = 1;
						while (kr != kl) {
							poly[h] = expression[i];
							i++; h++;
							if (expression[i] == ')') {
								kr++;
							}
							if (expression[i] == '(') {
								kl++;
							}
						}
						char polyNum[DIM] = "";
						sprintf(polyNum, "_(%s)", poly);
						sprintf(expressionF, "(0x^1-1)*(%s)", poly);
						simplifyPolynomial(expressionF);
						removeTriplPars(expressionF);
						sprintf(poly, "%s", expressionF);
						replaceTimes = 1;
						replace(polyNum, poly, expression);
						sprintf(expression, "%s", expressionF);
						replaceTimes = 0;
					}
				}
				char alphabet[DIM] = "ABCDEFGHIJKLMNOPQRSTUWVXYZabcdefghijklmnopqrstuwvxyz";
				char saveConversions[dime][dime];
				int z = 0;
				for (z = 0; z < abs((int)strlen(expression)); z++) {
					if (verifyNumerator(expression[z - 1]) && expression[z] == '/'&&verifyNumerator(expression[z + 1])) {
						expression[z] = '!';
					}
				}
				z = 0;
				while (!(isContained("/", expression) && verifyNumberExpression(expression[strStart - 1]) && verifyNumberExpression(expression[strEnd]))) {
					replaceTimes = 1;
					replace("/", "!", expression);
					sprintf(expression, "%s", expressionF);
				}
				replaceTimes = 0;
				if (isContained(")/(", expression)) {
					replaceTimes = 0;
					if (isContained("*(", expression)) {
						replace("*(", "(", expression);
						sprintf(expression, "%s", expressionF);
					}
					if (isContained("(", expression)) {
						replaceTimes = 1;
						int i = 0;
						while (isContainedByIndex("(", expression, i)) {
							if (isContainedByIndex("(", expression, i) && verifyNumerator(expression[strStart - 1])) {
								while (isContainedByIndex("(", expression, i) && verifyNumerator(expression[strStart - 1])) {
									expression[strStart] = 'P';
									i = strStart - 1;
									char num[DIM] = "";
									while (verifyNumerator(expression[i])) {
										i--;
									}
									i++;
									int v = i;
									int p = 0;
									while (verifyNumerator(expression[i])) {
										num[p] = expression[i];
										p++; i++;
									}
									num[p] = '\0';
									char new_expression[DIM] = "";
									sprintf(new_expression, "%s", num);
									char toReplace[DIM] = "";
									solveMath(num);
									sprintf(num, "%f+%fi", resultR, resultI);
									replaceTimes = 0;
									if (isContained("-", num)) {
										replace("-", "_", num);
										sprintf(num, "%s", expressionF);
									}
									replaceTimes = 1;
									if (abs((int)strlen(num)) == 0) {
										sprintf(num, "0");
									}
									sprintf(toReplace, "(0x+%s)*", num);
									replaceTimes = 1;
									replace(new_expression, toReplace, expression);
									sprintf(expression, "%s", expressionF);
									char expr[DIM] = "";
									int o = 0;
									if (isContainedByIndex("/", expression, i)) {
										int u = strStart;
										o = 0;
										while (v < u) {
											expr[o] = expression[v];
											v++; o++;
										}
										expr[o] = '\0';
										char saveExpr[DIM] = "";
										sprintf(saveExpr, "%s", expr);
										if (isContained("P", expr)) {
											replace("P", "(", expr);
											sprintf(expr, "%s", expressionF);
										}
										simpleSimplifyPolynomial(expr);
										replaceTimes = 0;
										if (isContained("+", expressionF)) {
											replace("+", "S", expressionF);
										}
										replaceTimes = 0;
										if (isContained("(((", expressionF)) {
											replace("(((", "((", expressionF);
										}
										if (isContained(")))", expressionF)) {
											replace(")))", "))", expressionF);
										}
										if (isContained("(", expressionF)) {
											replace("(", "P", expressionF);
										}
										replaceTimes = 1;
										replace(saveExpr, expressionF, expression);
										sprintf(expression, "%s", expressionF);
										if (isContained("(((", expression)) {
											replace("(((", "((", expression);
											sprintf(expression, "%s", expressionF);
										}
										if (isContained(")))", expression)) {
											replace(")))", "))", expression);
											sprintf(expression, "%s", expressionF);
										}
										if (isContainedByIndex("/", expression, i)) {
											expression[strStart] = 'D';
										}
									}
								}
							}
							else {
								if (expression[strStart] == '(') {
									expression[strStart] = 'P';
								}
							}
						}
						replaceTimes = 0;
						if (isContained("P", expression)) {
							replace("P", "(", expression);
							sprintf(expression, "%s", expressionF);
						}
						if (isContained("P", expression)) {
							replace("P", "(", expression);
							sprintf(expression, "%s", expressionF);
						}
						if (isContained("!", expression)) {
							replace("!", "/", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
					replaceTimes = 0;
					replaceTimes = 0;
					if (isContained(")*", expression)) {
						replace(")*", ")", expression);
						sprintf(expression, "%s", expressionF);
					}
					if (isContained(")", expression)) {
						replaceTimes = 1;
						while (isContained(")", expression)) {
							if (isContained(")", expression) && verifyNumerator(expression[strStart + 1])) {
								while (isContained(")", expression) && verifyNumerator(expression[strStart + 1])) {
									expression[strStart] = 'P';
									int i = strStart + 1;
									char num[DIM] = "";
									int v = i;
									int p = 0;
									while (verifyNumerator(expression[i])) {
										num[p] = expression[i];
										p++; i++;
									}
									num[p] = '\0';
									int f = 0;
									int countDivs = countOccurrences("/", expression) + countOccurrences("D", expression);
									if (countDivs > 1) {
										while ((expression[i - 1] == 'P'&&expression[i] == 'D') == false && (expression[i - 1] == 'P'&&expression[i] == '/') == false && i > 0) {
											i--;
										}
										i--;
										while ((expression[i - 1] == 'P'&&expression[i] == 'D') == false && (expression[i - 1] == 'P'&&expression[i] == '/') == false && i > 0 && expression[i] != '+') {
											i--;
										}
										if (expression[i] == '+') {
											i++;
										}
									}
									else {
										while ((expression[i - 1] == 'P'&&expression[i] == 'D') == false && (expression[i - 1] == 'P'&&expression[i] == '/') == false && i > 0 && expression[i] != '+') {
											i--;
										}
										i--;
										while (i > 0) {
											i--;
										}
									}
									int l = 0;
									char extractText[DIM] = "";
									while (((expression[i] == '/' || expression[i] == 'D') && expression[i + 1] == '(') == false) {
										extractText[l] = expression[i];
										i++; l++;
									}
									extractText[l] = '\0';
									replaceTimes = 0;
									if (isContained("P", extractText)) {
										replace("P", ")", extractText);
										sprintf(extractText, "%s", expressionF);
									}
									replaceTimes = 1;
									char new_expression[DIM] = "";
									sprintf(new_expression, "%s", num);
									char simplify[DIM] = "";
									char simplified[DIM] = "";
									char toReplace[DIM] = "";
									solveMath(num);
									sprintf(num, "%f+%fi", resultR, resultI);
									if (abs((int)strlen(num)) == 0) {
										sprintf(num, "0");
									}
									replaceTimes = 0;
									if (isContained("-", num)) {
										replace("-", "_", num);
										sprintf(num, "%s", expressionF);
									}
									replaceTimes = 1;
									if (abs((int)strlen(num)) == 0) {
										sprintf(num, "0");
									}
									if (expression[i] == '/') {
										sprintf(toReplace, "%s*(0x+%s)/", extractText, num);
									}
									if (expression[i] == 'D') {
										sprintf(toReplace, "%s*(0x+%s)D", extractText, num);
									}
									sprintf(simplify, "%s*(0x+%s)", extractText, num);
									char saveSimplify[DIM] = "";
									sprintf(saveSimplify, "%s", simplify);
									if (isContained("(x)", simplify)) {
										replace("(x)", "X", simplify);
										replace("X", "x", expressionF);
										sprintf(simplify, "%s", expressionF);
									}
									if (isContained("S", toReplace)) {
										replaceTimes = 0;
										replace("S", "+", toReplace);
										sprintf(toReplace, "%s", expressionF);
									}
									if (isContained("S", simplify)) {
										replaceTimes = 0;
										replace("S", "+", simplify);
										sprintf(simplify, "%s", expressionF);
									}
									simpleSimplifyPolynomial(simplify);
									sprintf(simplified, "%s", expressionF);
									if (expression[i] == '/') {
										sprintf(extractText, "%s/", extractText);
									}
									if (expression[i] == 'D') {
										sprintf(extractText, "%sD", extractText);
									}
									replaceTimes = 0;
									if (isContained("P", expression)) {
										replace("P", ")", expression);
										sprintf(expression, "%s", expressionF);
									}
									replaceTimes = 1;
									replace(extractText, toReplace, expression);
									sprintf(expression, "%s", expressionF);
									replaceTimes = 0;
									if (isContained("S", saveSimplify)) {
										replaceTimes = 0;
										replace("S", "+", saveSimplify);
										sprintf(saveSimplify, "%s", expressionF);
									}
									replaceTimes = 1;
									replace(saveSimplify, simplified, expression);
									sprintf(expression, "%s", expressionF);
									if (isContained("(((", expression)) {
										replace("(((", "((", expression);
										sprintf(expression, "%s", expressionF);
									}
									if (isContained(")))", expression)) {
										replace(")))", "))", expression);
										sprintf(expression, "%s", expressionF);
									}
									replaceTimes = 0;
									if (isContained("P", toReplace)) {
										replace("P", ")", toReplace);
										sprintf(toReplace, "%s", expressionF);
									}
									replaceTimes = 1;
									sprintf(expressionF, ")%s", new_expression);
									sprintf(new_expression, "%s", expressionF);
									replace(new_expression, ")", expression);
									sprintf(expression, "%s", expressionF);
								}
								replaceTimes = 1;
							}
							else {
								if (expression[strStart] == ')') {
									expression[strStart] = 'P';
								}
							}
						}
						replaceTimes = 0;
					}
					if (isContained("P", expression)) {
						replace("P", ")", expression);
						sprintf(expression, "%s", expressionF);
					}
					replaceTimes = 0;
					if (isContained("P", expression)) {
						replace("P", ")", expression);
						sprintf(expression, "%s", expressionF);
					}
					if (isContained("D", expression)) {
						replace("D", "/", expression);
						sprintf(expression, "%s", expressionF);
					}
					if (isContained("(x)", expression)) {
						replace("(x)", "X", expression);
						replace("X", "x", expressionF);
						sprintf(expression, "%s", expressionF);
					}
					replaceTimes = 0;
					if (isContained("(x)", expression)) {
						replaceTimes = 1;
						while (isContained("(x)", expression)) {
							if (verifyNumber(expression[strStart - 1])) {
								replace("(x)", "*X", expression);
							}
							else {
								replace("(x)", "X", expression);
							}
							sprintf(expression, "%s", expressionF);
						}
						replaceTimes = 0;
						if (isContained("X", expression)) {
							replace("X", "x", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
					if (isContained("X", expression)) {
						replace("X", "x", expression);
						sprintf(expression, "%s", expressionF);
					}
					while (isContained(")/(", expression)) {

						char num[DIM] = "";
						int i = strStart, j = strStart + 1, h = 0;
						int kr = 1, kl = 0;
						while (kr != kl) {
							i--;
							if (expression[i] == ')') {
								kr++;
							}
							if (expression[i] == '(') {
								kl++;
							}
						}
						h = 0;
						while (i < j) {
							num[h] = expression[i];
							i++; h++;
						}
						num[h] = '\0';
						char saveNum[DIM] = "";
						sprintf(saveNum, "%s", num);
						sprintf(expressionF, "(%s)*(0x^1+1)", num);
						if (isContained("S", expressionF)) {
							replaceTimes = 0;
							replace("S", "+", expressionF);
							sprintf(num, "%s", expressionF);
						}
						simplifyPolynomial(expressionF);
						removeTriplPars(expressionF);
						sprintf(num, "%s", expressionF);
						if (isContained("+", num)) {
							replaceTimes = 0;
							replace("+", "S", num);
							sprintf(num, "%s", expressionF);
						}
						replaceTimes = 1;
						replace(saveNum, num, expression);
						sprintf(expression, "%s", expressionF);
						if (isContained(")/(", expression)) {
							expression[strStart + 1] = 'D';
							i = strEnd - 1, h = 0;
							char den[DIM] = "";
							kr = 0, kl = 1;
							while (kr != kl) {
								den[h] = expression[i];
								i++; h++;
								if (expression[i] == ')') {
									kr++;
								}
								if (expression[i] == '(') {
									kl++;
								}
							}
							den[h] = ')';
							den[h + 1] = '\0';
							char saveDen[DIM] = "";
							sprintf(saveDen, "%s", den);
							sprintf(expressionF, "(%s)*(0x^1+1)", den);
							if (isContained("S", expressionF)) {
								replaceTimes = 0;
								replace("S", "+", expressionF);
								sprintf(den, "%s", expressionF);
							}
							simplifyPolynomial(expressionF);
							removeTriplPars(expressionF);
							sprintf(den, "%s", expressionF);
							if (isContained("+", den)) {
								replaceTimes = 0;
								replace("+", "S", den);
								sprintf(den, "%s", expressionF);
							}
							replaceTimes = 1;
							replace(saveDen, den, expression);
							sprintf(expression, "%s", expressionF);
						}
					}
					replaceTimes = 0;
					if (isContained("D", expression)) {
						replace("D", "/", expression);
						sprintf(expression, "%s", expressionF);
					}

					replaceTimes = 0;
					if (isContained("X", expression)) {
						replace("X", "x", expression);
						sprintf(expression, "%s", expressionF);
					}
				}

				if (isContained("+", expression)) {
					replace("+", "S", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("*x/", expression)) {
					while (isContained("*x/", expression)) {
						int y = strEnd;
						int p = 0;
						char value[dime] = "";
						while (verifyValue(expression[y])) {
							value[p] = expression[y];
							p++; y++;
						}
						value[p] = '\0';
						char toReplace[dime] = "";
						sprintf(toReplace, "*x/%s", value);
						sprintf(expressionF, "*1/%s*x", value);
						replaceTimes = 1;
						replace(toReplace, expressionF, expression);
						sprintf(expression, "%s", expressionF);
					}
				}
				if (isContained("*", expression)) {
					while (isContained("*", expression)) {
						replaceTimes = 1;
						int y = strStart - 1, w = 0;
						char expressioN[DIM] = "";
						while (verifyValue(expression[y])) {
							y--;
						}
						y++;
						w = 0;
						while (expression[y] != '+'&&expression[y] != '\0') {
							expressioN[w] = expression[y];
							w++; y++;
						}
						expressioN[w] = '\0';
						sprintf(expressionF, "(%s)*(0x^1+1)", expressioN);
						replaceTimes = 0;
						if (isContained("S", expressionF)) {
							replace("S", "+", expressionF);
						}
						if (isContained("((", expressionF)) {
							replace("((", "([", expressionF);
						}
						if (isContained("))", expressionF)) {
							replace("))", "])", expressionF);
						}
						simpleSimplifyPolynomial(expressionF);
						replaceTimes = 0;
						if (isContained("(((", expressionF)) {
							replace("(((", "((", expressionF);
						}
						if (isContained(")))", expressionF)) {
							replace(")))", "))", expressionF);
						}
						if (isContained("+", expressionF)) {
							replace("+", "S", expressionF);
						}
						replaceTimes = 1;
						sprintf(expressionF, "%s/(0x^1S1)", expressionF);
						replace(expressioN, expressionF, expression);
						sprintf(expression, "%s", expressionF);
					}
				}
				replaceTimes = 1;
				if (isContained("x", expression)) {
					replaceTimes = 1;
					while (isContained("x", expression)) {
						if (isContained("x", expression) && (verifyOperator(expression[strEnd]) || verifyOperator(expression[strStart - 1]))) {
							while (isContained("x", expression) && (verifyOperator(expression[strEnd]) || verifyOperator(expression[strStart - 1]))) {
								replace("x", "X", expression);
								sprintf(expression, "%s", expressionF);
							}
						}
						else {
							if (isContained("x", expression) && !(verifyOperator(expression[strEnd]) && verifyOperator(expression[strStart - 1]))) {
								replace("x", "X/1", expression);
								sprintf(expression, "%s", expressionF);
							}
							else {
								if (isContained("x", expression) && strStart == 0 && !verifyOperator(expression[strEnd])) {
									replace("x", "X/1", expression);
									sprintf(expression, "%s", expressionF);
								}
								else {
									replace("x", "X", expression);
									sprintf(expression, "%s", expressionF);
								}
							}
						}
					}
					replaceTimes = 0;
					if (isContained("X", expression)) {
						replace("X", "x", expression);
						sprintf(expression, "%s", expressionF);
					}
				}
				replaceTimes = 1;
				while (isContained("*x", expression)) {
					if (!(isContained("*x", expression) && verifyNumber(expression[strStart - 1]))) {
						while (!(isContained("*x", expression) && verifyNumber(expression[strStart - 1]))) {
							replaceTimes = 1;
							replace("*x", "x", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
					if (isContained("*x", expression) && verifyNumber(expression[strStart - 1])) {
						while (isContained("*x", expression) && verifyNumber(expression[strStart - 1])) {
							replaceTimes = 1;
							char dataBeforeX[DIM] = "";
							if (verifyValue(expression[strStart - 1])) {
								int y = strStart - 1;
								while (verifyValue(expression[y])) {
									y--;
								}
								int v = 0;
								y++;
								while (verifyValue(expression[y]) && expression[y] != '*') {
									dataBeforeX[v] = expression[y];
									v++; y++;
								}
								dataBeforeX[v] = '\0';
								if (abs((int)strlen(dataBeforeX)) == 0) {
									sprintf(dataBeforeX, "0");
								}
								char saveDataBeforeX[DIM] = "";
								sprintf(saveDataBeforeX, "%s*x", dataBeforeX);
								sprintf(expressionF, "(0x+%s)*(x+0)", dataBeforeX);
								simpleSimplifyPolynomial(expressionF);
								removeTriplPars(expressionF);
								replaceTimes = 0;
								if (isContained("+", expressionF)) {
									replace("+", "S", expressionF);
								}
								replaceTimes = 1;
								sprintf(expressionF, "%s/(0x^1S1)", expressionF);
								replace(saveDataBeforeX, expressionF, expression);
								sprintf(expression, "%s", expressionF);
							}
						}
					}
				}
				replaceTimes = 1;
				if (isContained("/", expression)) {
					while (!(isContained("/", expression) && verifyNumberExpression(expression[strStart - 1]) && verifyNumberExpression(expression[strEnd])) && isContained("/", expression)) {
						replace("/", "D", expression);
						sprintf(expression, "%s", expressionF);
					}
					replaceTimes = 0;
					if (isContained("D", expression)) {
						replace("D", "/", expression);
						sprintf(expression, "%s", expressionF);
					}
					replaceTimes = 1;
					if (isContained("/", expression)) {
						char numbersData[DIM] = "";
						int y = 0, c = 0;
						for (y; expression[y] != '\0'; y++) {
							if (isContainedByIndex("/", expression, y)) {
								while (isContainedByIndex("/", expression, y)) {
									y = strEnd;
									while (expression[y] != '+'&&expression[y] != '\0') {
										y++;
									}
									if (expression[y] == '\0') {
										break;
									}
								}
								if (expression[y] == '\0') {
									break;
								}
							}
							if (expression[y] == '\0') {
								break;
							}
						}
						replaceTimes = 0;
					}
				}
				if (isContained("D", expression)) {
					replace("D", "/", expression);
					sprintf(expression, "%s", expressionF);
				}
				z = 0;
				replaceTimes = 0;
				if (isContained(")S(", expression)) {
					replace(")S(", ")+(", expression);
					sprintf(expression, "%s", expressionF);
				}
				while (!(isContained("/", expression) && verifyNumberExpression(expression[strStart - 1]) && verifyNumberExpression(expression[strEnd]))) {
					replaceTimes = 1;
					replace("/", "!", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("/", expression) && verifyNumberExpression(expression[strStart - 1]) && verifyNumberExpression(expression[strEnd])) {
					while (isContained("/", expression) && verifyNumberExpression(expression[strStart - 1]) && verifyNumberExpression(expression[strEnd])) {
						if (isContained("/", expression) && verifyNumberExpression(expression[strStart - 1]) && verifyNumberExpression(expression[strEnd])) {
							char num[DIM] = "";
							int i = strStart - 1, j = strStart, h = 0, k = 0;
							int kr = 1, kl = 0;
							while (verifyNumberExpression(expression[i])) {
								i--;
							}
							i++;
							k = i;
							h = 0;
							while (i < j) {
								num[h] = expression[i];
								i++; h++;
							}
							num[h] = '\0';
							char saveNum[DIM] = "";

							sprintf(saveNum, "%s", num);
							if (isContained("S", num)) {
								replace("S", "+", num);
								sprintf(num, "%s", expressionF);
							}
							replaceTimes = 0;

							if (!isContained("x", num)) {
								sprintf(expressionF, "(0x^1+%s)*(0x^1+1)", num);
							}
							else {
								sprintf(expressionF, "(%s)*(0x^1+1)", num);
							}
							simpleSimplifyPolynomial(expressionF);
							removeTriplPars(expressionF);
							replaceTimes = 0;
							if (isContained("+", expressionF)) {
								replace("+", "S", expressionF);
							}
							sprintf(saveConversions[z], "%s", expressionF);
							replaceTimes = 1;
							char smallText[10] = "";
							sprintf(smallText, "%c", alphabet[z]);
							replaceByIndex(saveNum, smallText, expression, k);
							z++;
							sprintf(expression, "%s", expressionF);
							if (isContained("/", expression)) {
								expression[strStart] = '!';
								i = strEnd, h = 0; j = strStart;
								char den[DIM] = "";
								if (!(expression[strEnd] == '(')) {
									while (verifyNumberExpression(expression[i])) {
										den[h] = expression[i];
										i++; h++;
									}
									den[h] = '\0';
								}
								else {
									int kr = 0, kl = 1;
									den[h] = expression[i];
									h++;
									i++;
									while (i < abs((int)strlen(expression)) && kr < kl) {
										den[h] = expression[i];
										i++; h++;
										if (den[h - 1] == ')') {
											kr++;
										}
										if (den[h - 1] == '(') {
											kl++;
										}
									}
									den[h] = '\0';
								}
								char saveDen[DIM] = "";

								sprintf(saveDen, "%s", den);
								replaceTimes = 0;
								if (isContained("S", den)) {
									replace("S", "+", den);
									sprintf(den, "%s", expressionF);
								}

								if (!isContained("x", den)) {
									sprintf(expressionF, "(0x^1+%s)*(0x^1+1)", den);
								}
								else {
									sprintf(expressionF, "(%s)*(0x^1+1)", den);
								}
								simpleSimplifyPolynomial(expressionF);
								removeTriplPars(expressionF);


								replaceTimes = 0;
								if (isContained("+", expressionF)) {
									replace("+", "S", expressionF);
								}

								sprintf(saveConversions[z], "%s", expressionF);
								replaceTimes = 0;
								if (isContained("+", den)) {
									replace("+", "S", den);
									sprintf(den, "%s", expressionF);
								}

								replaceTimes = 1;
								char smallText[10] = "";
								sprintf(smallText, "%c", alphabet[z]);
								replace(saveDen, smallText, expression);
								z++;
								sprintf(expression, "%s", expressionF);
								replaceTimes = 0;
								if (isContained("+", num)) {
									replace("+", "S", num);
									sprintf(num, "%s", expressionF);
								}

							}
						}
						else {
							replaceTimes = 1;
							replace("/", "!", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
					replaceTimes = 0;
					if (isContained("!", expression)) {
						replace("!", "/", expression);
						sprintf(expression, "%s", expressionF);
					}
					removeTriplPars(expression);
					sprintf(expression, "%s", expressionF);
					int lettersTotal = z;
					z = 0;
					replaceTimes = 1;
					while (z < lettersTotal) {
						char smallText[10] = "";
						sprintf(smallText, "%c", alphabet[z]);
						replace(smallText, saveConversions[z], expression);
						sprintf(expression, "%s", expressionF);
						z++;
					}
					replaceTimes = 0;
					if (isContained("!", expression)) {
						replace("!", "/", expression);
						sprintf(expression, "%s", expressionF);
					}
				}
				replaceTimes = 0;
				if (isContained("D", expression)) {
					replace("D", "/", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("A", expression)) {
					replace("A", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained(")(", expression)) {
					replace(")(", ")*(", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("x", expression) && verifyValue(expression[strStart - 1]) && verifyNumber(expression[strStart - 1])) {
					replaceTimes = 1;
					do {
						if (isContained("x", expression) && verifyValue(expression[strStart - 1]) && verifyNumber(expression[strStart - 1])) {
							int i = strStart - 1;
							char num[DIM] = "";
							while (verifyValue(expression[i])) {
								i--;
							}
							i++;
							int p = 0;
							while (verifyValue(expression[i])) {
								num[p] = expression[i];
								p++; i++;
							}
							num[p] = '\0';
							solveMath(num);
							sprintf(num, "%sx", num);
							sprintf(expressionF, "((%fS%fi)X^1S(0S0i))", resultR, resultI);
							replaceTimes = 0;
							if (isContained("-", expressionF)) {
								replace("-", "_", expressionF);
							}
							if (isContained(".0000000000000", expressionF)) {
								replace(".0000000000000", "", expressionF);
							}
							replace(num, expressionF, expression);
							sprintf(expression, "%s", expressionF);
						}
						else {
							replaceTimes = 0;
							replace("x", "X", expression);
							sprintf(expression, "%s", expressionF);
						}
					} while (isContained("x", expression));
					replaceTimes = 0;
					if (isContained("X", expression)) {
						replace("X", "x", expression);
						sprintf(expression, "%s", expressionF);
					}
				}
				replaceTimes = 0;
				if (isContained("X", expression)) {
					replace("X", "x", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("/", expression)) {
					replaceTimes = 1;
					while (isContained("/", expression)) {
						if (isContained("/", expression) && verifyNumber(expression[strStart - 1])) {
							while (isContained("/", expression) && verifyNumber(expression[strStart - 1])) {
								int i = strStart - 1;
								char num[DIM] = "";
								while (verifyNumber(expression[i])) {
									i--;
								}
								i++;
								int p = 0;
								while (verifyNumber(expression[i])) {
									num[p] = expression[i];
									p++; i++;
								}
								num[p] = '\0';
								char new_expression[DIM] = "";
								sprintf(new_expression, "%s/", num);
								char toReplace[DIM] = "";
								sprintf(toReplace, "(0xS%s)D", num);
								replaceTimes = 1;
								replace(new_expression, toReplace, expression);
								sprintf(expression, "%s", expressionF);
							}
						}
						else {
							replace("/", "D", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
					replaceTimes = 0;
					replace("D", "/", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("/", expression)) {
					replaceTimes = 1;
					while (isContained("/", expression)) {
						if (isContained("/", expression) && verifyNumber(expression[strEnd])) {
							while (isContained("/", expression) && verifyNumber(expression[strEnd])) {
								int i = strEnd;
								char den[DIM] = "";
								int p = 0;
								while (verifyNumber(expression[i])) {
									den[p] = expression[i];
									p++; i++;
								}
								den[p] = '\0';
								char new_expression[DIM] = "";
								sprintf(new_expression, "/%s", den);
								char toReplace[DIM] = "";
								sprintf(toReplace, "D(0xS%s)", den);
								replace(new_expression, toReplace, expression);
								sprintf(expression, "%s", expressionF);
							}
						}
						else {
							replace("/", "D", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
					replaceTimes = 0;
					replace("D", "/", expression);
					sprintf(expression, "%s", expressionF);
				}
			}

			replaceTimes = 1;
			int b = 0;

			if (isContained("*(", expression)) {
				while (isContained("*(", expression)) {
					if (verifyForNumber(expression[strStart - 1])) {
						int h = strEnd;
						int v = 0;
						char pieceExpre[dime] = "";
						int kl = 1, kr = 0;
						while (kl != kr) {
							if (expression[h] == '(') {
								kl++;
							}
							if (expression[h] == ')') {
								kr++;
							}
							if (kl != kr) {
								pieceExpre[v] = expression[h];
								h++; v++;
							}
						}
						pieceExpre[v] = '\0';
						replaceTimes = 1;
						char number[dime] = "";
						char value[dime] = "";
						int b = 0, c = 0, d = 0;
						int r = strStart - 1;
						while (verifyForNumber(expression[r])) {
							r--;
						}
						r++;
						if (verifyForNumber(expression[r])) {
							b = 0;
							d = 0;
							c = r;
							while (verifyForNumber(expression[c])) {
								number[b] = expression[c];
								value[d] = expression[c];
								c++; b++; d++;
							}
							value[d] = '\0';
							while (c <= strStart) {
								number[b] = expression[c];
								c++; b++;
							}
						}
						number[b] = '\0';
						value[d] = '\0';
						char newNumber[dime] = "";
						if (expression[strStart] == '*') {
							sprintf(newNumber, "(0x^1S%s)M", value);
						}
						replace(number, newNumber, expression);
						sprintf(expression, "%s", expressionF);
					}
					if (expression[strStart] == '*') {
						expression[strStart] = 'M';
					}
					if (expression[strStart] == '/') {
						expression[strStart] = 'D';
					}
				}
				replaceTimes = 0;
				if (isContained("S", expression)) {
					replace("S", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("M", expression)) {
					replace("M", "*", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("D", expression)) {
					replace("D", "/", expression);
					sprintf(expression, "%s", expressionF);
				}
			}
			if (isContained("D", expression)) {
				replace("D", "/", expression);
				sprintf(expression, "%s", expressionF);
			}
			if (isContained("M", expression)) {
				replace("M", "*", expression);
				sprintf(expression, "%s", expressionF);
			}
			b = 0;
			if (isContained("+", expression)) {
				replaceTimes = 1;
				while (isContained("+", expression)) {
					if (expression[strStart - 1] == ')'&&expression[strEnd] == '(') {
						expression[strStart] = 'A';
					}
					else {
						expression[strStart] = 'S';
					}
				}
				replaceTimes = 0;
				if (isContained("A", expression)) {
					replace("A", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
			}
			if (isContained("+", expression)) {
				while (isContained("+", expression)) {
					if (isContainedByIndex("+", expression, b)) {
						expression[strStart] = 'P';
						char number[dime] = "";
						int n = 0;
						b = strStart - 1;
						while (verifyValue(expression[b])) {
							b--;
						}
						b++;
						while (verifyValue(expression[b])) {
							number[n] = expression[b];
							n++; b++;
						}
						number[n] = '\0';
						if (strlen(number) > 0) {
							char saveNumber[dime] = "";
							sprintf(saveNumber, "%s", number);
							if (isContained("x", number)) {
								sprintf(expressionF, "(%s)/(0xS1)", number);
							}
							else {
								sprintf(expressionF, "(0xS%s)/(0xS1)", number);
							}
							sprintf(number, "%s", expressionF);
							replaceTimes = 1;
							replaceByIndex(saveNumber, number, expression, b - (int)strlen(saveNumber));
							sprintf(expression, "%s", expressionF);
						}
					}
					else {
						expression[strStart] = 'P';
						b = strStart;
					}
				}
				replaceTimes = 0;
				if (isContained("P", expression)) {
					replace("P", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
			}
			replaceTimes = 0;
			char greatDenominator[DIM] = "";
			double great = 0;
			if (isContained("/", expression)) {
				double Exponent = 0, Divider = 0, saveExponent = 0, saveDivider = 0;
				char saveExpressionSS[DIM] = "";
				sprintf(saveExpressionSS, "%s", expression);
				sprintf(saveSimplification, "%s", expression);
				countSplits = countOccurrences("+", expression);
				split("+", expression);
				char expressionToSimplify[DIM] = "";
				char expressionSimplified[DIM] = "";
				int v = 0;
				while (v < countSplits) {
					sprintf(expressionToSimplify, "%s", splitResult[v]);
					sprintf(expressionSimplified, "%s", splitResult[v]);
					replaceTimes = 0;
					replace("S", "+", expressionSimplified);
					sprintf(expressionSimplified, "%s", expressionF);
					if (countOccurrences("0x", expressionSimplified) < 2) {
						sprintf(expressionF, "%s", expressionSimplified);
						sprintf(expressionSimplified, "%s", expressionF);
						simpleSimplifyPolynomial(expressionSimplified);
						if (isDivisible) {
							sprintf(expressionSimplified, "%s", expressionF);
							if (!isContained("/", expressionSimplified)) {
								sprintf(expressionSimplified, "%s/(0x+1)", expressionSimplified);
							}
						}
						replaceTimes = 0;
						replace("+", "S", expressionSimplified);
						sprintf(expressionSimplified, "%s", expressionF);
						sprintf(expression, "%s", saveExpressionSS);
						replaceTimes = 1;
						replace(expressionToSimplify, expressionSimplified, saveExpressionSS);
						sprintf(saveExpressionSS, "%s", expressionF);
					}
					sprintf(expression, "%s", saveExpressionSS);
					v++;
				}
				replaceTimes = 0;
				removeTriplPars(expression);
				sprintf(expression, "%s", expressionF);
				int u = 0;
				countSplits = countOccurrences("+", expression);
				split("+", expression);
				char saveCharResult[200][200];
				while (u <= countSplits) {
					sprintf(saveCharResult[u], "%s", splitResult[u]);
					u++;
				}
				u = 0;
				char numerator[200][200], denominator[200][200];
				while (u <= countSplits) {
					split("/", saveCharResult[u]);
					if (!isContained("x", splitResult[0])) {
						sprintf(numerator[u], "(0xS%s)", splitResult[0]);
					}
					else {
						sprintf(numerator[u], "(%s)", splitResult[0]);
					}
					if (!isContained("x", splitResult[1])) {
						sprintf(denominator[u], "(0xS%s)", splitResult[1]);
					}
					else {
						sprintf(denominator[u], "(%s)", splitResult[1]);
					}
					u++;
				}
				replaceTimes = 0;

				int m = 0;
				int c = 0;
				int equalNum = 0;
				replaceTimes = 0;
				char intermediate[DIM] = "";
				sprintf(expression, "");
				while (c <= countSplits) {
					replaceTimes = 0;
					equalNum = 0;
					if (isContained("S", numerator[c])) {
						replace("S", "+", numerator[c]);
						sprintf(numerator[c], "%s", expressionF);
					}
					if (isContained("(((", numerator[c])) {
						replace("(((", "((", numerator[c]);
						sprintf(numerator[c], "%s", expressionF);
					}
					if (isContained(")))", numerator[c])) {
						replace(")))", "))", numerator[c]);
						sprintf(numerator[c], "%s", expressionF);
					}
					sprintf(expressionF, "(%s)*(0x^1+1)", numerator[c]);
					simpleSimplifyPolynomial(expressionF);
					sprintf(roots, "");
					sprintf(numerator[c], "%s", expressionF);
					if (isContained("(((", numerator[c]) && isContained(")))", numerator[c])) {
						replace("(((", "((", numerator[c]);
						sprintf(numerator[c], "%s", expressionF);
						replace(")))", "))", numerator[c]);
						sprintf(numerator[c], "%s", expressionF);
					}
					sprintf(intermediate, "%s", numerator[c]);
					m = 0;
					while (m <= countSplits) {
						if (isContained("S", denominator[m])) {
							replace("S", "+", denominator[m]);
							sprintf(denominator[m], "%s", expressionF);
						}
						if (isContained("(((", denominator[m])) {
							replace("(((", "((", denominator[m]);
							sprintf(denominator[m], "%s", expressionF);
						}
						if (isContained(")))", denominator[m])) {
							replace(")))", "))", denominator[m]);
							sprintf(denominator[m], "%s", expressionF);
						}
						sprintf(expressionF, "(%s)*(0x^1+1)", denominator[m]);
						simpleSimplifyPolynomial(expressionF);
						sprintf(roots, "");
						sprintf(denominator[m], "%s", expressionF);
						if (m != c && (!isContained(denominator[m], intermediate) || (isEqual(numerator[c], denominator[m]) && equalNum == 0))) {
							if (isEqual(numerator[c], denominator[m])) {
								equalNum++;
							}
							if (!isEqual(denominator[m], denominator[c])) {
								sprintf(intermediate, "%s*%s", intermediate, denominator[m]);
							}
						}
						m++;
					}
					if (c == 0) {
						sprintf(expression, "%s", intermediate);
					}
					else {
						if (c <= countSplits) {
							sprintf(expression, "%s+%s", expression, intermediate);
						}
					}
					c++;
				}
				replaceTimes = 0;
				if (isContained("S", expression)) {
					replace("S", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
				replaceTimes = 0;
				if (isContained("(((", expression)) {
					replace("(((", "((", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained(")))", expression)) {
					replace(")))", "))", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("S", expression)) {
					replace("S", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
				replaceTimes = 0;
				if (isContained("+(", expression)) {
					replace("+(", "+[", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained(")x", expression)) {
					replace(")x", "]x", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained(")+[", expression)) {
					replace(")+[", ")+(", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("ix", expression)) {
					replace("ix", "i]x", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("((", expression)) {
					replace("((", "([", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("))", expression)) {
					replace("))", "])", expression);
					sprintf(expression, "%s", expressionF);
				}
				replaceTimes = 0;
				if (isContained("{", expression)) {
					replace("{", "(", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("}", expression)) {
					replace("}", ")", expression);
					sprintf(expression, "%s", expressionF);
				}
				simplifyPolynomial(expression);
				sprintf(expression, "%s", expressionF);
				replaceTimes = 0;
				if (isContained("S", expression)) {
					replace("S", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
				sprintf(expressionF, "%s", expression);
			}
			else {
				replaceTimes = 0;
				if (isContained("(x)", expression)) {
					replace("(x)", "X", expression);
					replace("X", "x", expressionF);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("_x", expression)) {
					replace("_x", "_1x", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("-", expression)) {
					replace("-", "+_", expression);
					sprintf(expression, "%s", expressionF);
				}
				replaceTimes = 0;
				if (isContained("*", expression)) {
					replace("*", "", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("S", expression)) {
					replaceTimes = 0;
					replace("S", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
				sprintf(expression, "%s", expressionF);

			}

			if (isContained("(x)", expression)) {
				replace("(x)", "X", expression);
				replace("X", "x", expressionF);
				sprintf(expression, "%s", expressionF);
			}
			replaceTimes = 1;
			if (isContained("x", expression) && strStart == 0) {
				replace("x", "1x", expression);
				sprintf(expression, "%s", expressionF);
			}
			replaceTimes = 0;
			if (isContained("_x", expression)) {
				replace("_x", "_1x", expression);
				sprintf(expression, "%s", expressionF);
			}
			if (isContained("+x", expression)) {
				replace("+x", "+1x", expression);
				sprintf(expression, "%s", expressionF);
			}
			replaceTimes = 0;
			if (isContained("i)", expression)) {
				replace("i)", "i]", expression);
				sprintf(expression, "%s", expressionF);
				int i = 0;
				while (i < abs((int)strlen(expression))) {
					if (expression[i] == '('&&verifyValue(expression[i + 1]) && expression[i - 2] != ')') {
						expression[i] = '[';
					}
					i++;
				}
				sprintf(expressionF, "%s", expression);
			}
			else {
				replaceTimes = 0;
				if (isContained("*", expression)) {
					replace("*", "", expression);
					sprintf(expression, "%s", expressionF);
				}
				char equa[dime] = "";
				boolean putPars = true;
				char newEquation[DIM] = "";
				char value[dime] = "";
				int q = 0, p = 0;
				while (p < abs((int)strlen(expression))) {
					if (verifyValue(expression[p])) {
						if (expression[p - 1] == 'x' && expression[p] == '^' && verifyValue(expression[p + 1])) {
							equa[q] = ' ';
							p++; q++;
							while (verifyValue(expression[p])) {
								equa[q] = ' ';
								q++; p++;
							}
						}
						if ((expression[p - 1] == ')' || verifyValue(expression[p - 1])) && (expression[p] == '*' || expression[p] == '/') && (expression[p + 1] == '(' || expression[p + 1] == 'x')) {
							equa[q] = ' ';
						}
						else {
							equa[q] = expression[p];
						}
					}
					else {
						equa[q] = ' ';
					}
					p++; q++;
				}
				equa[q] = '\0';
				char equaSimplified[DIM] = "";
				p = 0, q = 0;
				while (p < abs((int)strlen(equa))) {
					if (verifyValue(equa[p])) {
						q = 0;
						while (verifyValue(equa[p])) {
							value[q] = equa[p];
							p++; q++;
						}
						p--;
						value[q] = '\0';
						solveMath(value);
						if (putPars) {
							sprintf(value, convertToString("[%f+%fi]"), resultR, resultI);
						}
						else {
							sprintf(value, convertToString("[%f+%fi]"), resultR, resultI);
							putPars = true;
						}
						if (isContained("+-", value)) {
							replace("+-", "+_", value);
							sprintf(value, "%s", expressionF);
						}
						if (isContained("-", value)) {
							replace("-", "_", value);
							sprintf(value, "%s", expressionF);
						}
						sprintf(equaSimplified, "%s%s", equaSimplified, value);
					}
					else {
						if (expression[p] == 'x') {
							putPars = false;
						}
						sprintf(equaSimplified, "%s%c", equaSimplified, equa[p]);
					}
					p++;
				}
				equaSimplified[strlen(equaSimplified)] = '\0';
				p = 0; q = 0;
				while (p < abs((int)strlen(equaSimplified))) {
					if (equaSimplified[p] == ' ') {
						if (expression[q - 1] == 'x' && expression[q] == '^' && verifyValue(expression[q + 1])) {
							equaSimplified[p] = expression[q];
							p++;
							q++;
							while (verifyValue(expression[q])) {
								equaSimplified[p] = expression[q];
								q++; p++;
							}

						}
						if ((expression[q - 1] == ')' || verifyValue(expression[q - 1])) && (expression[q] == '*' || expression[q] == '/') && (expression[q + 1] == '(' || expression[q + 1] == 'x')) {
							equaSimplified[p] = expression[q];
							p++;
							q++;
						}
						if (verifyValue(expression[q])) {
							while (verifyValue(expression[q])) {
								q++;
							}
						}
						equaSimplified[p] = expression[q];
						q++;
					}
					p++;
				}
				equaSimplified[p] = '\0';
				sprintf(expressionF, "%s", equaSimplified);
				if (isContained(".000000", equaSimplified)) {
					replace(".000000", "", equaSimplified);
					sprintf(equaSimplified, "%s", expressionF);
				}
				if (isContained("(x", equaSimplified)) {
					replace("(x", "([1+0i]x", equaSimplified);
					sprintf(equaSimplified, "%s", expressionF);
				}
				if (isContained("(", equaSimplified)) {
					sprintf(expressionF, "%s", equaSimplified);
				}
				else {
					sprintf(expressionF, "(%s)", equaSimplified);
				}
			}
			replaceTimes = 0;
			if (isContained("[", expression)) {
				replace("[", "(", expression);
				sprintf(expression, "%s", expressionF);
			}
			if (isContained("]", expression)) {
				replace("]", ")", expression);
				sprintf(expression, "%s", expressionF);
			}
			sprintf(expressionF, "%s", expression);
		}
	}
	sprintf(expressionF, "%s", expression);
}


char* convertToString(char* string) {
	sprintf(stringHelper, "%s", string);
	return stringHelper;
}

void convertToPoly(char expressionToConvert[DIM]) {
	char originalEquation[DIM] = "";
	char expression[DIM] = "";
	char saveEquation[DIM] = "";
	char toCalcX[DIM] = "";
	double valuesEqR[200], valuesEqI[200];
	int i = 0, saveMaxExponent = 0;
	sprintf(originalEquation, "%s", expressionToConvert);
	sprintf(saveEquation, "%s", originalEquation);
	maxExponent = 0;
	sprintf(expression, "%s", originalEquation);
	equationSolverRunning = true;
	solving = false;
	for (i = 0; originalEquation[i] != '\0'; i++) {
		if (originalEquation[i] == '\\') {
			maxExponent++;
		}
	}
	int members = maxExponent;
	i = 0;
	char toValue[DIM] = "";
	while (members >= 0) {
		int b = 0;
		while (originalEquation[i] != '\\' && originalEquation[i] != '\0') {
			toValue[b] = originalEquation[i];
			b++;
			i++;
		}
		toValue[b] = '\0';
		solveMath(toValue);
		valuesEqR[members] = resultR;
		valuesEqI[members] = resultI;
		members--;
		sprintf(toValue, "");
		i++;
	}
	i = maxExponent;
	double maxValueR = valuesEqR[maxExponent], maxValueI = valuesEqI[maxExponent];
	for (i = maxExponent; i >= 0; i--) {
		division(valuesEqR[i], valuesEqI[i], maxValueR, maxValueI);
		valuesEqR[i] = resultR;
		valuesEqI[i] = resultI;
	}
	saveMaxExponent = maxExponent;
	for (i = maxExponent; i > 0; i--) {
		char ValueR[DIM] = "";
		sprintf(ValueR, "%f", valuesEqR[i]);
		for (int v = 0; v < abs((int)(strlen(ValueR))); v++) {
			if (ValueR[v] == '-')
				ValueR[v] = '_';
		}
		char ValueI[DIM] = "";
		sprintf(ValueI, "%f", valuesEqI[i]);
		for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
			if (ValueI[v] == '-')
				ValueI[v] = '_';
		}

		sprintf(toCalcX, "%s(%s+%si)1*(res)^%d+", toCalcX, ValueR, ValueI, i);
	}
	lastDividerR = valuesEqR[0];
	lastDividerI = valuesEqI[0];

	char ValueR[DIM] = "";
	sprintf(ValueR, "%f", valuesEqR[i]);
	for (int v = 0; v < abs((int)strlen(ValueR)); v++) {
		if (ValueR[v] == '-')
			ValueR[v] = '_';
	}
	char ValueI[DIM] = "";
	sprintf(ValueI, "%f", valuesEqI[i]);
	for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
		if (ValueI[v] == '-')
			ValueI[v] = '_';
	}
	sprintf(toCalcX, "%s(%s+%si)", toCalcX, ValueR, ValueI);
	if (isContained(".000000", toCalcX)) {
		replace(".000000", "", toCalcX);
		sprintf(toCalcX, "%s", expressionF);
	}
	sprintf(toCalcX, "%s", expressionF);
}

void decrementPoly(int maxExponent, double resR, double resI) {
	int i = 0;
	double rootR, rootI;
	rootR = resR;
	rootI = resI;
	char toValue[DIM] = "";
	double valuesEqR[200], valuesEqI[200];
	replaceTimes = 0;
	int members = maxExponent;
	i = 0;
	while (members >= 0) {
		valuesEqR[members] = expressionCoefR[maxExponent - members];
		valuesEqI[members] = expressionCoefI[maxExponent - members];
		members--;
	}
	i = maxExponent;
	double valueCoefR = 0, valueCoefI = 0, newCoefR[DIM], newCoefI[DIM];
	valueCoefR = valuesEqR[maxExponent]; valueCoefI = valuesEqI[maxExponent];
	int newMaxExponent = maxExponent - 1;
	members = newMaxExponent;
	while (members >= 0) {
		newCoefR[members] = valueCoefR; newCoefI[members] = valueCoefI;
		multiplication(rootR, rootI, valueCoefR, valueCoefI);
		sum(resultR, resultI, valuesEqR[members], valuesEqI[members]);
		valueCoefR = resultR; valueCoefI = resultI;
		members--;
	}
	for (i = 0; i < maxExponent; i++) {
		expressionCoefR[i] = newCoefR[i]; expressionCoefI[i] = newCoefI[i];
	}
	expressionCoefR[maxExponent - i] = newCoefR[i]; expressionCoefI[maxExponent - i] = newCoefI[i];
}

void getRealRoot(double real[dime], double  imaginary[dime], int maxExponent, double guess) {
	int i = 0;
	nrRoots = 0;
	double previous = 0, actual = 0;
	double start = guess;
	double x1 = 0, x2 = 0;
	while (start < 1000) {
		_rf = 0;
		xValuesR = start; xValuesI = 0;
		double SummatoryR = 0, SummatoryI = 0;
		while (_rf < maxExponent) {
			exponentiation(xValuesR, xValuesI, maxExponent - _rf, 0.0, 1);
			multiplication(real[_rf], imaginary[_rf], resultR, resultI);
			SummatoryR = SummatoryR + resultR;
			SummatoryI = SummatoryI + resultI;
			_rf++;
		}
		sum(SummatoryR, SummatoryI, real[_rf], imaginary[_rf]);
		SummatoryR = resultR; SummatoryI = resultI;
		previous = actual;
		actual = resultR;
		if (previous > 0 && actual < 0) {
			x1 = start - M_PI / 10; x2 = start;
			realRoots[nrRoots] = x1;
			nrRoots++;

		}
		if (previous < 0 && actual > 0) {
			x1 = start - M_PI / 10; x2 = start;
			realRoots[nrRoots] = x1;
			nrRoots++;
		}
		start = start + M_PI / 10;

	}
}