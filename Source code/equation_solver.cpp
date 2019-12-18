﻿




#include "stdafx.h"

boolean fromEquationSolver = false, equationSolverRunning = false, polySimplifier = false, solveMultiPoly = false, simplifying = true, progress = false;
char charMaster[DIM] = "", roots[DIM] = "", answers[DIM] = "", polyNo[DIM] = "", stringHelper[DIM] = "";
int parentPol[DIM];
int rootIndex = 1, maxExponent = 0;
double lastDividerR = 1, lastDividerI = 0, natureValue = 1, lastElement = 0, lastElementI = 0;
char splitResult[200][200];
double expressionCoefR[dim], expressionCoefI[dim];

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
		math_processor(value);
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
			math_processor(value);
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
				math_processor(value);
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
					if (x1R > 0 && x1I > 0) {
						printf("x%d=%G+%Gi\n", index, x1R, x1I);
					}
					else {
						if (x1R > 0 && x1I < 0) {
							printf("x%d=%G%Gi\n", index, x1R, x1I);
						}
						else {
							if (x1R < 0 && x1I > 0) {
								printf("x%d=%G+%Gi\n", index, x1R, x1I);
							}
							else {
								if (x1R < 0 && x1I < 0) {
									printf("x%d=%G%Gi\n", index, x1R, x1I);
								}
								else {
									if (x1R == 0 && x1I == 0) {
										printf("x%d=%G\n", index, x1R);
									}
									else {
										if (x1R == 0 && x1I != 0) {
											printf("x%d=%Gi\n", index, x1I);
										}
										else {
											if (x1R != 0 && x1I == 0) {
												printf("x%d=%G\n", index, x1R);
											}
											else {
												printf("x%d=%G+%Gi\n", index, x1R, x1I);
											}
										}
									}
								}
							}
						}
					}
					index++;
					if (x2R > 0 && x2I > 0) {
						printf("x%d=%G+%Gi\n", index, x2R, x2I);
					}
					else {
						if (x2R > 0 && x2I < 0) {
							printf("x%d=%G%Gi\n", index, x2R, x2I);
						}
						else {
							if (x2R < 0 && x2I > 0) {
								printf("x%d=%G+%Gi\n", index, x2R, x2I);
							}
							else {
								if (x2R < 0 && x2I < 0) {
									printf("x%d=%G%Gi\n", index, x2R, x2I);
								}
								else {
									if (x2R == 0 && x2I == 0) {
										printf("x%d=%G\n", index, x2R);
									}
									else {
										if (x2R == 0 && x2I != 0) {
											printf("x%d=%Gi\n", index, x2I);
										}
										else {
											if (x2R != 0 && x2I == 0) {
												printf("x%d=%G\n", index, x2R);
											}
											else {
												printf("x%d=%G+%Gi\n", index, x2R, x2I);
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
		math_processor(rootsF);
		multiplication(resultR, resultI, lastDividerR, lastDividerI);
		char Report[dim] = "";
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
			math_processor(toValue);
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
		double rearrangeValuesR[dim], rearrangeValuesI[dim];
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
				sprintf(value, "%G", valuesRootsR[i]);
				resultRR = strtod(value, &pointer);
				sprintf(value, "%G", valuesRootsI[i]);
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
				sprintf(value, "%G", valuesRootsR[i]);
				resultRR = strtod(value, &pointer);
				sprintf(value, "%G", valuesRootsI[i]);
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
		double saveResultR[dim][dim], saveResultI[dim][dim];
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
						sprintf(toSimplify, convertToString("%G+%Gi"), resultR, resultI);
						if (isContained("E", toSimplify)) {
							sprintf(toSimplify, convertToString("%f+%fi"), resultR, resultI);
						}
						if (isContained("-", toSimplify)) {
							replace("-", "_", toSimplify);
							sprintf(toSimplify, "%s", expressionF);
						}
						math_processor(toSimplify);
						sprintf(Report, convertToString("%s(%G+%Gi)x^%d+"), report, resultR, resultI,
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
							sprintf(toSimplify, convertToString("%G+%Gi"), resultR, resultI);
							if (isContained("E", toSimplify)) {
								sprintf(toSimplify, convertToString("%f+%fi"), resultR, resultI);
							}
							if (isContained("-", toSimplify)) {
								replace("-", "_", toSimplify);
								sprintf(toSimplify, "%s", expressionF);
							}
							math_processor(toSimplify);
							sprintf(Report, convertToString("%s(%G+%Gi)x^1+"), report, resultR, resultI);
							if (isContained("E", Report)) {
								sprintf(Report, convertToString("%s(%f+%fi)x^%d+"), report, resultR, resultI,
									exp);
							}
						}
						else {
							multiplication(polynomialRF[pol], polynomialIF[pol], lastDividerR,
								lastDividerI);
							char toSimplify[100] = "";
							sprintf(toSimplify, convertToString("%G+%Gi"), resultR, resultI);
							if (isContained("E", toSimplify)) {
								sprintf(toSimplify, convertToString("%f+%fi"), resultR, resultI);
							}
							if (isContained("-", toSimplify)) {
								replace("-", "_", toSimplify);
								sprintf(toSimplify, "%s", expressionF);
							}
							math_processor(toSimplify);
							sprintf(Report, convertToString("%s(%G+%Gi)"), report, resultR,
								resultI);
							if (isContained("E", Report)) {
								sprintf(Report, convertToString("%s(%f+%fi)"), report, resultR, resultI);
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
	replaceTimes = 0;
	char saveToCalcX[DIM] = "";
	char originalEquation[DIM] = "";
	sprintf(originalEquation, "%s", equation);
	int SaveMaxExponent = 0;
	maxExponent = 0;
	char toCalcX[DIM] = "";
	char toReplace[DIM] = "";
	double RootR[dim], RootI[dim], to_numR[dim], to_numI[dim], valuesEqR[DIM], valuesEqI[DIM], resultSubR[dim], resultSubI[dim];
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
				math_processor(toValue);
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
				simplifyPolynomial(equation);
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
					math_processor(exponent);
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
			if (isContained("x+", toCalcX)) {
				replace("x+", "*1*(res)^1+", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			if (isContained("x-", toCalcX)) {
				replace("x-", "*1*(res)^1-", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			if (isContained("x", toCalcX)) {
				replace("x", "*1*(res)", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			sprintf(charMaster, "");
			if (isContained("x+", toCalcX)) {
				replace("x+", "*1*(res)^1+", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			if (isContained("x-", toCalcX)) {
				replace("x-", "*1*(res)^1-", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			if (isContained("x", toCalcX)) {
				replace("x", "*1*(res)", toCalcX);
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
					math_processor(expressionF);
					lastDividerR = resultR; lastDividerI = resultI;
				}
			}
		}
		if (lastElement == 0 && lastElementI == 0) {
			sprintf(expressionF, "(%s+0.00000000000000001)", toCalcX);
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
				math_processor(toCalcLastEle);
				lastElement = resultR; lastElementI = resultI;
			}
			double posLastElement = 0, posLastElementI = 0;
			multiplication(-1.0, 0.0, lastElement, lastElementI);
			posLastElement = resultR; posLastElementI = resultI;
			char posLastEle[dim] = "";
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
				char LastEle[dim] = "";
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
						math_processor(helpExtract);
						if (findToRemove == 0) {
							sum(resultR, resultI, posLastElement, posLastElementI);
						}
						division(resultR, resultI, lastDividerR, lastDividerI);
						sprintf(expression, "%s\\%f+%fi", expression, resultR, resultI);
						expressionCoefR[u] = resultR; expressionCoefI[u] = resultI;
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
							math_processor(helpExtract);
							if (findToRemove == 0) {
								sum(resultR, resultI, posLastElement, posLastElementI);
							}
							division(resultR, resultI, lastDividerR, lastDividerI);
							sprintf(expression, "%s\\%f+%fi", expression, resultR, resultI);
							expressionCoefR[u] = resultR; expressionCoefI[u] = resultI;
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
				int solveIndex = 0;
				double SolutionR[200], SolutionI[200];
				int solvedIndex = 0;
				if (maxExponent == 1) {
					replaceTimes = 0;
					replace("res", "0", toCalcX);
					math_processor(expressionF);
					multiplication(-1.0, 0.0, resultR, resultI);
					RootR[0] = resultR; RootI[0] = resultI;
				}
				else {
					g = 0;
					RootR[g] = M_E / 2; RootI[g] = M_PI / 2;
					g++;
					while (g < maxExponent) {
						RootR[g] = RootR[0];
						RootI[g] = RootI[0];
						multiplication(RootR[g], RootI[g], g + 1, 0);
						RootR[g] = resultR; RootI[g] = resultI;
						to_numR[g] = resultR;
						to_numI[g] = resultR;
						g++;
					}

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
					char *pointer;
					g = 0;
					replaceTimes = 0;
					countSolutions = 0;
					while (n < 1000 && countSolutions < maxMaxExponent - 1) {
						g = 0;
						while (g < maxExponent) {
							xValuesR = RootR[g];
							xValuesI = RootI[g];
							int rf = 0;
							double SummatoryR = 0, SummatoryI = 0;
							while (rf < maxExponent) {
								exponentiation(xValuesR, xValuesI, (double)maxExponent - rf, 0.0, 1);
								multiplication(expressionCoefR[rf], expressionCoefI[rf], resultR, resultI);
								SummatoryR = SummatoryR + resultR;
								SummatoryI = SummatoryI + resultI;
								rf++;
							}
							sum(SummatoryR, SummatoryI, expressionCoefR[rf], expressionCoefI[rf]);
							if (resultR == 0 && resultI == 0) {
								sprintf(value, "%f", RootR[g]);
								RootR[g] = strtod(value, &pointer);
								sprintf(value, "%f", RootI[g]);
								RootI[g] = strtod(value, &pointer);
								SolutionR[solvedIndex] = RootR[g];
								SolutionI[solvedIndex] = RootI[g];
								int v = 0, u = 0;
								while (v < maxExponent) {
									if (v != g) {
										RootR[u] = RootR[v];
										RootI[u] = RootI[v];
										u++;
									}
									v++;
								}
								int y = 1;
								while (y - 1 < maxExponent) {
									multiplication(expressionCoefR[y - 1], expressionCoefI[y - 1], SolutionR[solvedIndex], SolutionI[solvedIndex]);
									sum(expressionCoefR[y], expressionCoefI[y], resultR, resultI);
									expressionCoefR[y] = resultR; expressionCoefI[y] = resultI;
									y++;
								}
								countSolutions++;
								n = 0;
								g = 0;
								solvedIndex++;
								maxExponent--;
							}
							else {
								double numR = resultR, numI = resultI, denR = 1, denI = 0;
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
							}
							g++;
						}
						n++;
					}
				}
				int y = 0;
				while (y < maxExponent) {
					SolutionR[solvedIndex] = RootR[y];
					SolutionI[solvedIndex] = RootI[y];
					solvedIndex++; y++;
				}
				maxExponent = maxMaxExponent;
				g = 0;
				rootIndex = 1;
				sprintf(answers, "");
				while (g < maxExponent) {
					rootR = SolutionR[g];
					rootI = SolutionI[g];
					if (isContained("\\", saveEquation) || isContained("x^", saveEquation) ||
						(equation_solver == (boolean)true && isContained("x", saveEquation) &&
							isContained("x^", equation) == (boolean)false)) {
						if (abs(rootR) < 1E-6) {
							rootR = 0;
						}
						if (abs(rootI) < 1E-6) {
							rootI = 0;
						}
						if (rootR > 0 && rootI > 0) {
							sprintf(answers, "%sx%d=%G+%Gi\n", answers, rootIndex, rootR, rootI);
							sprintf(roots, "%s\\%f+%fi", roots, rootR, rootI);
						}
						else {
							if (rootR > 0 && rootI < 0) {
								sprintf(answers, "%sx%d=%G%Gi\n", answers, rootIndex, rootR, rootI);
								sprintf(roots, "%s\\%f%fi", roots, rootR, rootI);
							}
							else {
								if (rootR < 0 && rootI > 0) {
									sprintf(answers, "%sx%d=%G+%Gi\n", answers, rootIndex, rootR, rootI);
									char rootRExp[100] = "";
									sprintf(rootRExp, "%f", rootR);
									replace("-", "_", rootRExp);
									sprintf(rootRExp, "%s", expressionF);
									sprintf(roots, "%s\\%s+%fi", roots, rootRExp, rootI);
								}
								else {
									if (rootR < 0 && rootI < 0) {
										sprintf(answers, "%sx%d=%G%Gi\n", answers, rootIndex, rootR, rootI);
										char rootRExp[100] = "";
										sprintf(rootRExp, "%f", rootR);
										replace("-", "_", rootRExp);
										sprintf(rootRExp, "%s", expressionF);
										sprintf(roots, "%s\\%s%fi", roots, rootRExp, rootI);
									}
									else {
										if (rootR == 0 && rootI == 0) {
											sprintf(answers, "%sx%d=%G\n", answers, rootIndex, rootR);
											sprintf(roots, "%s\\%f", roots, rootR);
										}
										else {
											if (rootR == 0 && rootI != 0) {
												sprintf(answers, "%sx%d=%Gi\n", answers, rootIndex, rootI);
												char rootIExp[100] = "";
												sprintf(rootIExp, "%fi", rootI);
												if (isContained("-", rootIExp)) {
													replace("-", "_", rootIExp);
													sprintf(rootIExp, "%s", expressionF);
												}
												sprintf(roots, "%s\\%s", roots, rootIExp);
											}
											else {
												if (rootR != 0 && rootI == 0) {
													sprintf(answers, "%sx%d=%G\n", answers, rootIndex,
														rootR);
													char rootRExp[100] = "";
													sprintf(rootRExp, "%f", rootR);
													if (isContained("-", rootRExp)) {
														replace("-", "_", rootRExp);
														sprintf(rootRExp, "%s", expressionF);
													}
													sprintf(roots, "%s\\%s", roots, rootRExp);
												}
												else {
													sprintf(answers, "%sx%d=%G+%Gi\n", answers, rootIndex,
														rootR, rootI);
													sprintf(roots, "%s\\%f+%fi", roots, rootR, rootI);
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
			math_processor(saveToZeroDiv);
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
	char polys[dim][dim];
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
		(expressionF, "%s", expressionS);
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
	char operators[dim] = "";
	char getSimpleExpression[DIM] = "";
	char getRestExpression[DIM] = "";
	char parentNum[dim][dim];
	int type[dim];
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
		int size[dim];
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
		math_processor(saveToCalcX);
		sprintf(saveToCalcX, "%s", saveEquationF);
		lastElement = resultR, lastElementI = resultI;
		if (isContained("aaaa", saveToCalcX)) {
			replace("aaaa", "1", saveToCalcX);
			sprintf(saveToCalcX, "%s", expressionF);
		}
		math_processor(saveToCalcX);
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
	if (isContained("*1i", expression)) {
		replace("*1i", "i", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained(")-(", expression)) {
		replace(")-(", ")_(", expression);
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
	if (!isContained(")+", expression)) {
		if (isContained(")/", expression) || isContained(")*", expression)) {
			while (isContained(")/", expression) || isContained(")*", expression)) {
				if (verifyForNumber(expression[strEnd])) {
					toSimplify = false;
					replaceTimes = 1;
					char number[dim] = "";
					char value[dim] = "";
					int b = 0, c = 0, d = 0;
					if (verifyForNumber(expression[strEnd])) {
						b = 0;
						d = 0;
						c = strStart;
						while (c < strEnd) {
							number[b] = expression[c];
							c++; b++;
						}
						while (verifyForNumber(expression[c])) {
							number[b] = expression[c];
							value[d] = expression[c];
							c++; b++; d++;
						}
					}
					number[b] = '\0';
					value[d] = '\0';
					char newNumber[dim] = "";
					if (expression[strEnd - 1] == '/') {
						sprintf(newNumber, ")M(0x^1S%s^_1)", value);
					}
					if (expression[strEnd - 1] == '*') {
						sprintf(newNumber, ")M(0x^1S%s)", value);
					}
					replace(number, newNumber, expression);
					sprintf(expression, "%s", expressionF);
				}
				if (expression[strEnd - 1] == '*') {
					expression[strEnd - 1] = 'M';
				}
				if (expression[strEnd - 1] == '/') {
					expression[strEnd - 1] = 'D';
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

		if (isContained("/(", expression) || isContained("*(", expression)) {
			while (isContained("/(", expression) || isContained("*(", expression)) {
				if (verifyForNumber(expression[strStart - 1])) {
					toSimplify = false;
					int h = strEnd;
					int v = 0;
					char pieceExpre[dim] = "";
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
					char number[dim] = "";
					char value[dim] = "";
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
					char newNumber[dim] = "";
					if (expression[strStart] == '/') {
						sprintf(newNumber, "((0xS%s)*(0x^1S%s^_1))/((0x^1S%s^_1)M", value, value, value);
						sprintf(expressionF, "%s)", pieceExpre);
						replaceTimes = 1;
						replace(pieceExpre, expressionF, expression);
						sprintf(expression, "%s", expressionF);
						replaceTimes = 0;
					}
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
	}
	if (isContained("/", expression) || isContained("*", expression)) {
		replaceTimes = 0;
		while (isContained("/", expression)) {
			if (verifyFraction(expression[strStart - 1]) && verifyFraction(expression[strEnd]) && expression[strStart] == '/') {
				int b = strStart;
				while (verifyFraction(expression[b])) {
					b--;
				}
				if (expression[b] != '^') {
					b++;
					int v = 0;
					char fraction[dim] = "";
					while (verifyFraction(expression[b])) {
						fraction[v] = expression[b];
						b++; v++;
					}
					fraction[v] = '\0';
					math_processor(fraction);
					if (expression[b] != ')') {
						sprintf(expressionF, "(%f+%fi)", resultR, resultI);
					}
					else {
						sprintf(expressionF, "%f+%fi", resultR, resultI);
					}
					if (isContained("-", expressionF)) {
						replace("-", "_", expressionF);
					}
					if (isContained(".000000", expressionF)) {
						replace(".000000", "", expressionF);
					}
					replace(fraction, expressionF, expression);
					sprintf(expression, "%s", expressionF);
				}
				else {
					expression[strStart] = 'D';
				}
			}
			else {
				expression[strStart] = 'D';
			}
		}
		while (isContained("*", expression)) {
			if (verifyMultiplication(expression[strStart - 1]) && verifyMultiplication(expression[strEnd]) && expression[strStart] == '*') {
				int b = strStart;
				while (verifyMultiplication(expression[b])) {
					b--;
				}
				if (expression[b] != '^') {
					b++;
					int v = 0;
					char multiplication[dim] = "";
					while (verifyMultiplication(expression[b])) {
						multiplication[v] = expression[b];
						b++; v++;
					}
					multiplication[v] = '\0';
					math_processor(multiplication);
					if (expression[b] != ')') {
						sprintf(expressionF, "(%f+%fi)", resultR, resultI);
					}
					else {
						sprintf(expressionF, "%f+%fi", resultR, resultI);
					}
					if (isContained("-", expressionF)) {
						replace("-", "_", expressionF);
					}
					if (isContained(".000000", expressionF)) {
						replace(".000000", "", expressionF);
					}
					replace(multiplication, expressionF, expression);
					sprintf(expression, "%s", expressionF);
				}
				else {
					expression[strStart] = 'M';
				}
			}
			else {
				expression[strStart] = 'M';
			}
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
	if (toSimplify == false) {
		sprintf(expressionF, "%s", expression);
		simplifyPolynomial(expressionF);
	}
	if (isContained(")+0", expression) && strEnd == abs((int)strlen(expression)) && toSimplify == (boolean)true) {
		toSimplify = false;
		sprintf(expressionF, "%s", expression);
		simplifyPolynomial(expressionF);
	}
	if (isContained("/", expression) && studyFunction == (boolean)false && toSimplify == (boolean)true) {
		if (isContained("(x)", expression)) {
			replaceTimes = 1;
			while (isContained("(x)", expression)) {
				if (verifyNumber(expression[strStart - 1])) {
					replace("(x)", "*X", expression);
					sprintf(expression, "%s", expressionF);
				}
				else {
					if (expression[strStart - 1] == '/' && !(expression[strEnd] == '^')) {
						replace("(x)", "(X)", expression);
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
							sprintf(toReplace, "(x)^%s", getExp);
							replace(toReplace, replacement, expression);
							sprintf(expression, "%s", expressionF);
						}
						else {
							replace("(x)", "X", expression);
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
		char alphabet[DIM] = "ABCDEFGHIJKLMNOPQRSTUWVXYZabcdefghijklmnopqrstuwvxyz";
		char saveConversions[dim][dim];
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
							math_processor(num);
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
							math_processor(num);
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
			}
			replaceTimes = 0;
			while (isContained(")/(", expression)) {
				char num[DIM] = "";
				int i = strStart, j = strStart + 1, h = 0;
				int kr = 1, kl = 0;
				while (kr != kl && i > 0) {
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
				sprintf(expressionF, "%s*(0x^1+1)", num);
				if (isContained("S", expressionF)) {
					replaceTimes = 0;
					replace("S", "+", expressionF);
					sprintf(num, "%s", expressionF);
				}
				simpleSimplifyPolynomial(expressionF);
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
					while (kr != kl && i < abs((int)strlen(expression))) {
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
					sprintf(expressionF, "%s*(0x^1+1)", den);
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
		}
		replaceTimes = 0;
		if (isContained("!", expression)) {
			replace("!", "/", expression);
			sprintf(expression, "%s", expressionF);
		}
		replaceTimes = 1;
		if (isContained("*x/", expression)) {
			while (isContained("*x/", expression)) {
				int y = strEnd;
				int p = 0;
				char value[dim] = "";
				while (verifyValue(expression[y])) {
					value[p] = expression[y];
					p++; y++;
				}
				value[p] = '\0';
				char toReplace[dim] = "";
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
					replace("*x", "*X", expression);
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
		replaceTimes = 0;
		if (isContained("X", expression)) {
			replace("X", "x", expression);
			sprintf(expression, "%s", expressionF);
		}
		replaceTimes = 0;
		if (isContained("D", expression)) {
			replace("D", "/", expression);
			sprintf(expression, "%s", expressionF);
		}
		replaceTimes = 1;
		int y = 0;
		if (isContained("/", expression)) {
			while (isContained("/", expression)) {
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
					replaceTimes = 0;
					if (isContained("S", num)) {
						replace("S", "+", num);
						sprintf(num, "%s", expressionF);
					}

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

		if (isContained("!", expression)) {
			replace("!", "/", expression);
			sprintf(expression, "%s", expressionF);
		}
		if (isContained("+", expression)) {
			while (isContained("+", expression)) {
				if (isContained("+", expression) && verifyNumerator(expression[strStart + 1])) {
					expression[strStart] = 'A';
					y = strStart + 1;
					char numbersData[DIM] = "";
					int c = 0;
					if (verifyNumberExpression(expression[y])) {
						c = 0;
						while (verifyNumberExpression(expression[y])) {
							numbersData[c] = expression[y];
							c++; y++;
						}
						numbersData[c] = '\0';
						char saveNumbersData[DIM] = "";
						sprintf(saveNumbersData, "%s", numbersData);
						if (!isContained("x", numbersData)) {
							sprintf(expressionF, "(0xS%s)/(0xS1)", numbersData);
						}
						else {
							sprintf(expressionF, "(%s)/(0xS1)", numbersData);
						}
						sprintf(numbersData, "%s", expressionF);
						replaceTimes = 1;
						replaceByIndex(saveNumbersData, numbersData, expression, y - (int)strlen(saveNumbersData));
						sprintf(expression, "%s", expressionF);
						if (isContainedByIndex(numbersData, expression, y)) {
							y = strEnd;
						}
					}
				}
				else {
					expression[strStart] = 'A';
				}
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
					math_processor(num);
					sprintf(num, "%sx", num);
					sprintf(expressionF, "((%fS%fi)X^1S(0S0i))", resultR, resultI);
					replaceTimes = 0;
					if (isContained("-", expressionF)) {
						replace("-", "_", expressionF);
					}
					if (isContained(".0000000000000", expressionF)) {
						replace(".0000000000000", "", expressionF);
					}
					replaceTimes = 1;
					replace(num, expressionF, expression);
					sprintf(expression, "%s", expressionF);
				}
				else {
					replaceTimes = 1;
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
		replaceTimes = 1;
		int b = 0;
		if (isContained("+", expression)) {
			while (isContained("+", expression)) {
				if (isContained("+", expression) && verifyValue(expression[strStart - 1])) {
					expression[strStart] = 'P';
					char number[dim] = "";
					int n = 0, k = 0;
					b = strStart - 1;
					while (verifyValue(expression[b])) {
						b--;
					}
					b++;
					k = b;
					while (verifyValue(expression[b])) {
						number[n] = expression[b];
						n++; b++;
					}
					number[n] = '\0';
					char saveNumber[dim] = "";
					sprintf(saveNumber, "%s", number);
					sprintf(expressionF, "(0xS%s)/(0xS1)", number);
					sprintf(number, "%s", expressionF);
					replaceTimes = 1;
					replaceByIndex(saveNumber, number, expression, k);
					sprintf(expression, "%s", expressionF);
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
		b = 0;
		if (isContained("+", expression)) {
			while (isContained("+", expression)) {
				if (isContainedByIndex("+", expression, b)) {
					expression[strStart] = 'P';
					char number[dim] = "";
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
						char saveNumber[dim] = "";
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
				removeTriplPars(expressionF);
				simpleSimplifyPolynomial(expressionF);
				sprintf(roots, "");
				processVariable("x");
				double saveR = resultR, saveI = resultI;
				resultR = M_PI * M_E; resultI = M_PI * M_E;
				variableController("x", 0);
				removeDuplPars(denominator[m]);
				sprintf(denominator[m], "%s", expressionF);
				math_processor(denominator[m]);
				if (great < abs_complex(resultR, resultI)) {
					sprintf(greatDenominator, "%s", denominator[m]);
					great = abs_complex(resultR, resultI);
				}
				resultR = saveR; resultI = saveI;
				variableController("x", 0);
				m++;
			}
			m = 0;
			while (m <= countSplits) {
				if (isContained("S", numerator[m])) {
					replace("S", "+", numerator[m]);
					sprintf(numerator[m], "%s", expressionF);
				}
				removeDuplPars(numerator[m]);
				sprintf(numerator[m], "%s", expressionF);
				removeDuplPars(denominator[m]);
				sprintf(denominator[m], "%s", expressionF);
				sprintf(expressionF, "(%s)*(0x+1)", denominator[m]);
				simpleSimplifyPolynomial(expressionF);
				sprintf(denominator[m], "%s", expressionF);
				removeDuplPars(denominator[m]);
				sprintf(denominator[m], "%s", expressionF);
				sprintf(expressionF, "(%s)/(%s)", greatDenominator, denominator[m]);
				simpleSimplifyPolynomial(expressionF);
				char firstFract[DIM] = "";
				sprintf(firstFract, "%s", expressionF);
				multi_polynomial(firstFract, numerator[m]);
				char secondFract[DIM] = "";
				sprintf(secondFract, "%s", expressionF);
				sprintf(intermediate, "%s", expressionF);
				if (m == 0) {
					sprintf(expression, "%s", intermediate);
				}
				else {
					if (m <= countSplits) {
						sprintf(expression, "%s+%s", expression, intermediate);
					}
				}
				m++;
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
		char equa[dim] = "";
		boolean putPars = true;
		char newEquation[DIM] = "";
		char value[dim] = "";
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
				math_processor(value);
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
		math_processor(toValue);
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
