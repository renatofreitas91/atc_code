




#include "stdafx.h"

boolean equationSolverRunning = false, polySimplifier = false, solveMultiPoly = false, simplifying = true;
char charMaster[DIM] = "", roots[DIM] = "", answers[DIM] = "", polyNo[DIM] = "", stringHelper[DIM] = "";
int parentPol[DIM];
int rootIndex = 1, maxExponent = 0;
double lastDividerR = 1, lastDividerI = 0, natureValue = 1;
char splitResult[200][200];

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
						printf("x%d=%f+%fi\n", index, x1R, x1I);
					}
					else {
						if (x1R > 0 && x1I < 0) {
							printf("x%d=%f%fi\n", index, x1R, x1I);
						}
						else {
							if (x1R < 0 && x1I > 0) {
								printf("x%d=%f+%fi\n", index, x1R, x1I);
							}
							else {
								if (x1R < 0 && x1I < 0) {
									printf("x%d=%f%fi\n", index, x1R, x1I);
								}
								else {
									if (x1R == 0 && x1I == 0) {
										printf("x%d=%f\n", index, x1R);
									}
									else {
										if (x1R == 0 && x1I != 0) {
											printf("x%d=%fi\n", index, x1I);
										}
										else {
											if (x1R != 0 && x1I == 0) {
												printf("x%d=%f\n", index, x1R);
											}
											else {
												printf("x%d=%f+%fi\n", index, x1R, x1I);
											}
										}
									}
								}
							}
						}
					}
					index++;
					if (x2R > 0 && x2I > 0) {
						printf("x%d=%f+%fi\n", index, x2R, x2I);
					}
					else {
						if (x2R > 0 && x2I < 0) {
							printf("x%d=%f%fi\n", index, x2R, x2I);
						}
						else {
							if (x2R < 0 && x2I > 0) {
								printf("x%d=%f+%fi\n", index, x2R, x2I);
							}
							else {
								if (x2R < 0 && x2I < 0) {
									printf("x%d=%f%fi\n", index, x2R, x2I);
								}
								else {
									if (x2R == 0 && x2I == 0) {
										printf("x%d=%f\n", index, x2R);
									}
									else {
										if (x2R == 0 && x2I != 0) {
											printf("x%d=%fi\n", index, x2I);
										}
										else {
											if (x2R != 0 && x2I == 0) {
												printf("x%d=%f\n", index, x2R);
											}
											else {
												printf("x%d=%f+%fi\n", index, x2R, x2I);
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
		sprintf(report, convertToString("%s(%f+%fi)x^1-(%f+%fi)"), report, lastDividerR, lastDividerI, resultR,
			resultI);
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
						sprintf(toSimplify, convertToString("%f+%fi"), resultR, resultI);
						if (isContained("-", toSimplify)) {
							replace("-", "_", toSimplify);
							sprintf(toSimplify, "%s", expressionF);
						}
						math_processor(toSimplify);
						sprintf(Report, convertToString("%s(%f+%fi)x^%d+"), report, resultR, resultI,
							exp);
					}
					else {
						if (exp == 1) {
							multiplication(polynomialRF[pol], polynomialIF[pol], lastDividerR,
								lastDividerI);
							char toSimplify[100] = "";
							sprintf(toSimplify, convertToString("%f+%fi"), resultR, resultI);
							if (isContained("-", toSimplify)) {
								replace("-", "_", toSimplify);
								sprintf(toSimplify, "%s", expressionF);
							}
							math_processor(toSimplify);
							sprintf(Report, convertToString("%s(%f+%fi)x^1+"), report, resultR, resultI);
						}
						else {
							multiplication(polynomialRF[pol], polynomialIF[pol], lastDividerR,
								lastDividerI);
							char toSimplify[100] = "";
							sprintf(toSimplify, convertToString("%f+%fi"), resultR, resultI);
							if (isContained("-", toSimplify)) {
								replace("-", "_", toSimplify);
								sprintf(toSimplify, "%s", expressionF);
							}
							math_processor(toSimplify);
							sprintf(Report, convertToString("%s(%f+%fi)"), report, resultR,
								resultI);
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

int equationSolver_2(char equation[DIM]) {
	maxExponent = 0;
	natureValue = 0;
	double ResultR = 0, ResultI = 0;
	char toCalcX[DIM] = "";
	double rootR = 0, rootI = 0;
	equationSolverRunning = true;
	double valuesEqR[DIM], valuesEqI[DIM];
	int i = 0, saveMaxExponent = 0;
	for (i = 0; equation[i] != '\0'; i++) {
		if (equation[i] == '\\') {
			maxExponent++;
		}
	}
	int members = maxExponent;
	i = 0;
	char toValue[DIM] = "";
	while (members >= 0) {
		int b = 0;
		while (equation[i] != '\\'&&equation[i] != '\0') {
			toValue[b] = equation[i];
			b++; i++;
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
		valuesEqR[i] = resultR; valuesEqI[i] = resultI;
	}
	saveMaxExponent = maxExponent;
	do {
		sprintf(toCalcX, "");
		char expression[DIM] = "";
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
			sprintf(toCalcX, "%s(%s+%si)*(res)^%d+", toCalcX, ValueR, ValueI, i);
			sprintf(expression, "%s%s+%si\\", expression, ValueR, ValueI);
		}
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
		sprintf(expression, "%s%s+%si", expression, ValueR, ValueI);
		if (isContained(".000000", expression)) {
			replace(".000000", "", expression);
			sprintf(expression, "%s", expressionF);
		}


		retrySolver = false; retrySolver_2 = false; retrySolver_3 = false;
		double rootR = natureRootTest(toCalcX, valuesEqR[0], valuesEqI[0]);
		rootI = resultI;
		if (rootR == -77777) {
			sprintf(expressionF, "%s", toCalcX);
			resultR = 0; resultI = 0;
			return 0;
		}
		else {
			if (rootR > 0 && rootI > 0) {
				sprintf(answers, "%sx%d=%f+%fi\n", answers, rootIndex, rootR, rootI);
				sprintf(roots, "%s\\%f+%fi", roots, rootR, rootI);
			}
			else {
				if (rootR > 0 && rootI < 0) {
					sprintf(answers, "%sx%d=%f%fi\n", answers, rootIndex, rootR, rootI);
					sprintf(roots, "%s\\%f%fi", roots, rootR, rootI);
				}
				else {
					if (rootR < 0 && rootI > 0) {
						sprintf(answers, "%sx%d=%f+%fi\n", answers, rootIndex, rootR, rootI);
						char rootRExp[100] = "";
						sprintf(rootRExp, "%f", rootR);
						replace("-", "_", rootRExp);
						sprintf(rootRExp, "%s", expressionF);
						sprintf(roots, "%s\\%s+%fi", roots, rootRExp, rootI);
					}
					else {
						if (rootR < 0 && rootI < 0) {
							sprintf(answers, "%sx%d=%f%fi\n", answers, rootIndex, rootR, rootI);
							char rootRExp[100] = "";
							sprintf(rootRExp, "%f", rootR);
							replace("-", "_", rootRExp);
							sprintf(rootRExp, "%s", expressionF);
							sprintf(roots, "%s\\%s%fi", roots, rootRExp, rootI);
						}
						else {
							if (rootR == 0 && rootI == 0) {
								sprintf(answers, "%sx%d=%f\n", answers, rootIndex, rootR);
								sprintf(roots, "%s\\%f", roots, rootR);
							}
							else {
								if (rootR == 0 && rootI != 0) {
									sprintf(answers, "%sx%d=%fi\n", answers, rootIndex, rootI);
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
										sprintf(answers, "%sx%d=%f\n", answers, rootIndex,
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
										sprintf(answers, "%sx%d=%f+%fi\n", answers, rootIndex,
											rootR, rootI);
										sprintf(roots, "%s\\%f+%fi", roots, rootR, rootI);
									}
								}
							}
						}
					}
				}
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
				if (isContained("\\-0\\", roots)) {
					replace("\\-0\\", "\\0\\", roots);
					sprintf(roots, "%s", expressionF);
				}
				if (roots[0] == '-') {
					roots[0] = '_';
				}
				rootIndex++;
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
				for (i = 0; i < saveMaxExponent; i++) {
					valuesEqR[i] = 0; valuesEqI[i] = 0;
				}
				for (i = 0; i < maxExponent; i++) {
					valuesEqR[i] = newCoefR[i]; valuesEqI[i] = newCoefI[i];
				}
				maxExponent--;
			}
		}
	} while (maxExponent > 0);
	sprintf(expressionF, "%s", toCalcX);
	resultR = ResultR; resultI = ResultI;
	return (int)ResultR;
}
double equationSolver(char equation[DIM]) {
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
	double lastElement = 0;
	double lastElementI = 0;
	bool isFirstDegree = false;
	if (!isDivisible) {
		isDivisible = true;
		simplifyExpression(saveExpressionF);
		sprintf(saveExpressionF, "%s", expressionF);
		sprintf(roots, "");
		equationSolver(saveExpressionF);
		rootsToPolynomial(roots);
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
			if (isContained("[", equation)) {
				replace("[", "(", equation);
				sprintf(equation, "%s", expressionF);
			}
			if (isContained("]", equation)) {
				replace("]", ")", equation);
				sprintf(equation, "%s", expressionF);
			}
			replaceTimes = 0;
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
			if (isContained("(((", equation)) {
				replace("(((", "((", equation);
				sprintf(equation, "%s", expressionF);
			}
			if (isContained(")))", equation)) {
				replace(")))", "))", equation);
				sprintf(equation, "%s", expressionF);
			}
			if (!dataVerifier(equation, 0, 0, 0, 1)) {
				if (countOccurrences(")", equation) > countOccurrences("(", equation)) {
					int u = countOccurrences(")", equation) - countOccurrences("(", equation);
					if (u == 1) {
						equation[strlen(equation) - 1] = '\0';
					}
				}

			}
			sprintf(saveEquation, "%s", equation);
			solving = false;
			equationSolverRunning = true;
			sprintf(toCalcX, "%s", saveEquation);
			maxExponent = 1;
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
				replace("x+", "1*(res)^1+", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			if (isContained("x-", toCalcX)) {
				replace("x-", "1*(res)^1-", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			if (isContained("x", toCalcX)) {
				replace("x", "1*(res)", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
			}
			sprintf(charMaster, "");
		}
		sprintf(saveToCalcX, "%s", toCalcX);
		char maxExp[10] = "";
		sprintf(maxExp, ")^%d", maxExponent);
		SaveMaxExponent = maxExponent;
		maxExponent = getCorrectExponent(saveToCalcX, maxExp, maxExponent);
		int g = 0, k = 0;
		int l = 1;
		g = 0;
		resultR = 0.1; resultI = 0.1;
		sprintf(saveToCalcX, "");
		sprintf(saveToCalcX, "%s", toCalcX);
		resultR = 0;
		resultI = 0;
		if (isContained("res", toCalcX)) {
			replace("res", "0", toCalcX);
			math_processor(expressionF);
		}
		double lastElement = resultR;
		double lastElementI = resultI;
		if (lastElement == 0 && lastElementI == 0) {
			sprintf(expressionF, "%s+0.00000000000000001", saveToCalcX);
			sprintf(toCalcX, "%s", expressionF);
		}
		sprintf(toCalcX, "%s", saveToCalcX);
		sprintf(saveToCalcX, "%s", toCalcX);
		char toReplace[DIM] = "";
		sprintf(toReplace, "(res)^%d", SaveMaxExponent - 1);
		replace(toReplace, "(1)", toCalcX);
		replace("res", "0", expressionF);
		math_processor(expressionF);
		double firstElement = resultR - lastElement;
		double firstElementI = resultI - lastElementI;
		sprintf(toReplace, "(res)^%d", SaveMaxExponent - 2);
		replace(toReplace, "(1)", toCalcX);
		replace("res", "0", expressionF);
		math_processor(expressionF);
		char toCalC[DIM] = "";
		sprintf(toCalcX, "%s", saveToCalcX);
		if (SaveMaxExponent != maxExponent) {
			while (SaveMaxExponent > maxExponent) {
				char toReplace[DIM] = "";
				sprintf(toReplace, "(res)^%d", SaveMaxExponent);
				replace(toReplace, "(0)", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
				SaveMaxExponent--;
			}
			sprintf(toReplace, "(res)^%d", SaveMaxExponent);
			replace(toReplace, "(1)", toCalcX);
			if (isContained("res", expressionF)) {
				replace("res", "0", expressionF);
			}
			math_processor(expressionF);
			resultR = resultR - lastElement;
			resultI = resultI - lastElementI;
			lastDividerR = resultR;
			lastDividerI = resultI;
		}
		char helpExtract[DIM] = "";
		int u = 0, t = 0, v = 0;
		sprintf(helpExtract, "%s", toCalcX);
		if (isContained("(((", helpExtract)) {
			replace("(((", "((", helpExtract);
			sprintf(helpExtract, "%s", expressionF);
		}
		if (isContained(")))", helpExtract)) {
			replace(")))", "))", helpExtract);
			sprintf(helpExtract, "%s", expressionF);
		}
		char saveHelper[DIM] = "";
		sprintf(saveHelper, "%s", helpExtract);
		sprintf(expression, "");
		while (u < maxExponent) {
			sprintf(helpExtract, "%s", saveHelper);
			sprintf(toReplace, "(res)^%d", maxExponent - u);
			if (isContained(toReplace, helpExtract)) {
				replace(toReplace, "(1)", helpExtract);
				sprintf(helpExtract, "%s", expressionF);
				if (isContained("res", helpExtract)) {
					replace("res", "0", helpExtract);
					sprintf(helpExtract, "%s", expressionF);
				}
				math_processor(helpExtract);
				resultR = resultR - lastElement;
				resultI = resultI - lastElementI;
				sprintf(expression, "%s\\%f+%fi", expression, resultR, resultI);
			}
			else {
				resultR = 0; resultI = 0;
				sprintf(expression, "%s\\%f+%fi", expression, resultR, resultI);
			}
			u++;
		}
		resultR = 0;
		resultI = 0;
		sprintf(expression, "%s\\%f+%fi", expression, lastElement, lastElementI);
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
		if (lastDividerR != 0 || lastDividerI != 0) {
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
			char toTest[DIM] = "";
			replaceTimes = 0;
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
			int saveExponentMax = maxExponent;
			resultR = equationSolver_2(expression);
			if (saveExponentMax != maxExponent) {
				sprintf(toCalcX, "%s", expressionF);
			}
			else {
				resultR = 0; resultI = 0;
			}
			if (maxExponent > 0) {
				resultR = 0; resultI = 0;
				if (maxExponent == 1) {
					isFirstDegree = true;
					maxExponent = 2;
					sprintf(expressionF, "(%s)*(res)", toCalcX);
					sprintf(toCalcX, "%s", expressionF);
				}

				int g = 0;
				boolean natural = true;
				double f = 0;
				while (f <= 1000 && g < maxExponent&&natural) {
					xValuesR = f; xValuesI = 0;
					if (re(abs(lastElement), f) == 0) {
						RootR[g] = f * -1; RootI[g] = 0.1;
						multiplication(RootR[g], RootI[g], g + 1, 0);
						RootR[g] = resultR; RootI[g] = resultI;
						RootR[g] = resultR;
						RootI[g] = resultI;
						to_numR[g] = resultR;
						to_numI[g] = resultI;
						lastElement = lastElement / f;
						g++;
					}
					else {
						f = f * -1;
						xValuesR = f; xValuesI = 0;
						if (re(abs(lastElement), f) == 0) {
							RootR[g] = f * -1; RootI[g] = 0.1;
							multiplication(RootR[g], RootI[g], g + 1, 0);
							RootR[g] = resultR; RootI[g] = resultI;
							RootR[g] = resultR;
							RootI[g] = resultI;
							to_numR[g] = resultR;
							to_numI[g] = resultI;
							lastElement = lastElement / (f*-1);
							g++;
						}
						f = f * -1;
					}
					f = abs(f) + 1;
					if (f > 1000 - 1) {
						natural = false;
					}
				}
				if (g == 0 || f > 1000 - 1) {
					natural = false;
					RootR[g] = 0.1; RootI[g] = 0.1;
					g++;
				}
				int v = g;
				while (g < maxExponent) {
					RootR[g] = RootR[v - 1]; RootI[g] = RootI[v - 1] + 0.1;
					multiplication(RootR[g], RootI[g], g + 1, 0);
					RootR[g] = resultR; RootI[g] = resultI;
					RootR[g] = resultR;
					RootI[g] = resultI;
					to_numR[g] = resultR;
					to_numI[g] = resultI;
					g++;
				}
				int n = 0;
				int x = 0;
				resultR = 1;
				resultI = 1;
				double saveResultR = 0, saveResultI = 0;
				char value[DIM] = "";
				boolean solved = false;
				int k = 0;
				int limit = (int)(maxExponent * maxExponent * 2.5);
				if (limit < 84) {
					limit = 84;
				}
				while (solved == false && n < limit) {
					g = 0;
					int k = 0;
					solved = false;
					replaceTimes = 0;
					while (solved == false && g < maxExponent) {
						xValuesR = RootR[g];
						xValuesI = RootI[g];
						math_processor(toCalcX);
						saveResultR = resultR;
						saveResultI = resultI;
						char value[dim] = "";
						sprintf(value, "%.9f+%.9fi", resultR, resultI);
						if (isContained("-", value)) {
							replace("-", "_", value);
							sprintf(value, "%s", expressionF);
						}
						math_processor(value);
						if (resultR == 0 && resultI == 0) {
							k++;
							if (k == maxExponent) {
								solved = true;
							}
						}
						double numR = saveResultR, numI = saveResultI, denR = 1, denI = 0;
						int w = 0, h = 0;
						while (solved == false && w < maxExponent) {
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
						while (solved == false && h < k) {
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
						g++;
					}
					n++;
				}
				g = 0;
				while (g < maxExponent) {
					rootR = RootR[g];
					rootI = RootI[g];
					if ((rootI > 1E-27 && rootI < 1E-12) || (rootI < -1E-27 && rootI > -0.001)) {
						rootI = 0;
					}
					if ((rootR > 1E-27 && rootR < 1E-12) || (rootR < -1E-27 && rootR > -0.001)) {
						rootR = 0;
					}
					if (isContained("\\", saveEquation) || isContained("x^", saveEquation) ||
						(equation_solver == (boolean)true && isContained("x", saveEquation) &&
							isContained("x^", equation) == (boolean)false)) {
						if (rootR > 0 && rootI > 0) {
							sprintf(answers, "%sx%d=%f+%fi\n", answers, rootIndex, rootR, rootI);
							sprintf(roots, "%s\\%f+%fi", roots, rootR, rootI);
						}
						else {
							if (rootR > 0 && rootI < 0) {
								sprintf(answers, "%sx%d=%f%fi\n", answers, rootIndex, rootR, rootI);
								sprintf(roots, "%s\\%f%fi", roots, rootR, rootI);
							}
							else {
								if (rootR < 0 && rootI > 0) {
									sprintf(answers, "%sx%d=%f+%fi\n", answers, rootIndex, rootR, rootI);
									char rootRExp[100] = "";
									sprintf(rootRExp, "%f", rootR);
									replace("-", "_", rootRExp);
									sprintf(rootRExp, "%s", expressionF);
									sprintf(roots, "%s\\%s+%fi", roots, rootRExp, rootI);
								}
								else {
									if (rootR < 0 && rootI < 0) {
										sprintf(answers, "%sx%d=%f%fi\n", answers, rootIndex, rootR, rootI);
										char rootRExp[100] = "";
										sprintf(rootRExp, "%f", rootR);
										replace("-", "_", rootRExp);
										sprintf(rootRExp, "%s", expressionF);
										sprintf(roots, "%s\\%s%fi", roots, rootRExp, rootI);
									}
									else {
										if (rootR == 0 && rootI == 0) {
											sprintf(answers, "%sx%d=%f\n", answers, rootIndex, rootR);
											sprintf(roots, "%s\\%f", roots, rootR);
										}
										else {
											if (rootR == 0 && rootI != 0) {
												sprintf(answers, "%sx%d=%fi\n", answers, rootIndex, rootI);
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
													sprintf(answers, "%sx%d=%f\n", answers, rootIndex,
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
													sprintf(answers, "%sx%d=%f+%fi\n", answers, rootIndex,
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
				if (isFirstDegree || isContained("0x", originalEquation)) {
					replaceTimes = 1;
					if (isContained("\\0", roots) && roots[strEnd] != '.') {
						replace("\\0", "", roots);
						sprintf(roots, "%s", expressionF);
					}
					else {
						if (isContained("0\\", roots)) {
							replace("0\\", "", roots);
							sprintf(roots, "%s", expressionF);
						}
						else {
							if (isContained("\\_0-0i", roots)) {
								replace("\\_0-0i", "", roots);
								sprintf(roots, "%s", expressionF);
							}
							else {
								if (isContained("_0-0i\\", roots)) {
									replace("_0-0i\\", "", roots);
									sprintf(roots, "%s", expressionF);
								}
								else {
									if (isContained("\\0-0i", roots)) {
										replace("\\0-0i", "", roots);
										sprintf(roots, "%s", expressionF);
									}
									else {
										if (isContained("0-0i\\", roots)) {
											replace("0-0i\\", "", roots);
											sprintf(roots, "%s", expressionF);
										}
										else {
											if (isContained("\\0+0i", roots)) {
												replace("\\0+0i", "", roots);
												sprintf(roots, "%s", expressionF);
											}
											else {
												if (isContained("0+0i\\", roots)) {
													replace("0+0i\\", "", roots);
													sprintf(roots, "%s", expressionF);
												}
												else {
													if (isContained("\\_0+0i", roots)) {
														replace("\\_0+0i", "", roots);
														sprintf(roots, "%s", expressionF);
													}
													else {
														if (isContained("_0+0i\\", roots)) {
															replace("_0+0i\\", "", roots);
															sprintf(roots, "%s", expressionF);
														}
														else {
															if (isContained("0i\\", roots) && roots[strEnd] != '.') {
																replace("0i\\", "", roots);
																sprintf(roots, "%s", expressionF);
															}
															else {
																if (isContained("\\0i", roots) && roots[strEnd] != '.') {
																	replace("\\0i", "", roots);
																	sprintf(roots, "%s", expressionF);
																}
																else {
																	if (isContained("_0-0i\\", roots)) {
																		replace("_0-0i\\", "", roots);
																		sprintf(roots, "%s", expressionF);
																	}
																	else {
																		if (isContained("\\_0-0i", roots)) {
																			replace("\\_0-0i", "", roots);
																			sprintf(roots, "%s", expressionF);
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
						}
					}
					if (isContained("=0+0i\n", answers)) {
						replace("=0+0i\n", "deleted\n", answers);
						sprintf(answers, "%s", expressionF);
					}
					else {
						if (isContained("=0\n", answers) && answers[strEnd] != '.') {
							replace("=0\n", "deleted\n", answers);
							sprintf(answers, "%s", expressionF);
						}
						else {
							if (isContained("=-0-0i\n", answers)) {
								replace("=-0-0i\n", "deleted\n", answers);
								sprintf(answers, "%s", expressionF);
							}
							else {
								if (isContained("=0-0i\n", answers)) {
									replace("=0-0i\n", "deleted\n", answers);
									sprintf(answers, "%s", expressionF);
								}
								else {
									if (isContained("=-0i\n", answers)) {
										replace("=-0i\n", "deleted\n", answers);
										sprintf(answers, "%s", expressionF);
									}
								}
							}
						}
					}
					replaceTimes = 1;
					if (isContained("deleted\n", answers)) {
						char toRemove[DIM] = "";
						int o = strStart;
						while (answers[o] != '\n'&&o > 0) {
							o--;
						}
						if (o == -1 || answers[o] == '\n') {
							o++;
						}
						int x = 0;
						while (answers[o] != '\0'&&answers[o] != '\n') {
							toRemove[x] = answers[o];
							x++; o++;
						}
						toRemove[x] = '\0';
						replace(toRemove, "", answers);
						sprintf(answers, "%s", expressionF);
					}
					replaceTimes = 0;
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
			if (isContained("(-", saveToZeroDiv)) {
				replace("(-", "(_", saveToZeroDiv);
				sprintf(saveToZeroDiv, "%s", expressionF);
			}
			if (isContained("+-", saveToZeroDiv)) {
				replace("+-", "+_", saveToZeroDiv);
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
		sprintf(expressionF, "(%s)", poly_1);
		if (isContained(".000000", expressionF)) {
			replace(".000000", "", expressionF);
		}
	}
}

void simplifyPolynomial(char expression[DIM]) {
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
	double dividerValueR = 0, dividerValueI = 0;
	char divider[DIM] = "";
	do {
		while (isContained(maxExp, saveToCalcX)) {
			int b = strStart;
			while (saveToCalcX[b] != '(') {
				b--;
			}
			if (saveToCalcX[b - 1] == '*') {
				if (!(saveToCalcX[b - 2] == '1' && saveToCalcX[b - 3] == ')')) {
					b = b - 2;
					while (verifyValue(saveToCalcX[b])) {
						b--;
					}
				}
				else {
					b = b - 4;
					while (saveToCalcX[b] != '(') {
						b--;
					}
					int f = 0;
					divider[f] = '(';
					f++;
					b++;
					while (saveToCalcX[b] != ')') {
						divider[f] = saveToCalcX[b];
						b++;
						f++;
					}
					while (saveToCalcX[b] != '*') {
						divider[f] = saveToCalcX[b];
						b++;
						f++;
					}
					divider[f] = '\0';
				}
				b++;
				int t = 0;
				int s = b - 1;
				if (strlen(divider) == 0) {
					if (saveToCalcX[b - 1] == '-' || saveToCalcX[b - 1] == '_') {
						divider[t] = '_';
						t++;
					}
					while (!(saveToCalcX[b + 1] == '(' && saveToCalcX[b + 2] == 'r' &&
						saveToCalcX[b + 3] == 'e' && saveToCalcX[b + 4] == 's'&& saveToCalcX[b + 5] == ')')) {
						divider[t] = saveToCalcX[b];
						b++;
						t++;
					}
					divider[t] = '\0';
					if (isContained("_", divider) && saveToCalcX[s] == '-') {
						replace("_", "-", divider);
						sprintf(divider, "%s", expressionF);
					}
				}
				math_processor(divider);
				char toSimplify[100] = "";
				sprintf(toSimplify, convertToString("%f+%fi"), resultR, resultI);
				if (isContained("-", toSimplify)) {
					replace("-", "_", toSimplify);
					sprintf(toSimplify, "%s", expressionF);
				}
				math_processor(toSimplify);
				dividerValueR = dividerValueR + resultR;
				dividerValueI = dividerValueI + resultI;
				char toReplace[DIM] = "";
				sprintf(toReplace, "%s*(res%s", divider, maxExp);
				isContained(toReplace, saveToCalcX);
				int y = strStart;
				while (y < strEnd) {
					saveToCalcX[y] = ' ';
					y++;
				}
				replace(" ", "", saveToCalcX);
				sprintf(saveToCalcX, "%s", expressionF);
				sprintf(divider, "");
			}
		}
		if (dividerValueR == 0 && dividerValueI == 0 && maxExponent > 1) {
			maxExponent--;
		}
		else {
			lastDividerR = dividerValueR;
			lastDividerI = dividerValueI;
			return maxExponent;
		}
	} while (dividerValueR == 0 && dividerValueI == 0 && maxExponent >= 1);
	lastDividerR = dividerValueR;
	lastDividerI = dividerValueI;
	return maxExponent;
}

void simplifyExpression(char data[DIM]) {
	char expression[DIM] = "";
	sprintf(expression, "%s", data);
	sprintf(expressionF, "");
	sprintf(roots, "");
	sprintf(answers, "");
	replaceTimes = 0;
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
	if (isContained("-", expression)) {
		replace("-", "+_", expression);
		sprintf(expression, "%s", expressionF);
	}

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
				}
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
						char saveDataBeforeX[DIM] = "";
						sprintf(saveDataBeforeX, "%s*x", dataBeforeX);
						sprintf(expressionF, "(0x+%s)(x+0)", dataBeforeX);
						simpleSimplifyPolynomial(expressionF);
						removeTriplPars(expressionF);
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
					if (verifyNumberExpression(expression[y])) {
						c = 0;
						while (verifyNumberExpression(expression[y])) {
							numbersData[c] = expression[y];
							c++; y++;
						}
						numbersData[c] = '\0';
						if (expression[y] != ')'&&expression[y + 1] != '/'&&expression[y + 2] != '('&&expression[y] != '/'&&expression[y] != ')') {
							char saveNumbersData[DIM] = "";
							sprintf(saveNumbersData, "%s", numbersData);
							sprintf(expressionF, "(0xS%s)/(0xS1)", numbersData);
							sprintf(numbersData, "%s", expressionF);
							replaceTimes = 1;
							replace(saveNumbersData, numbersData, expression);
							sprintf(expression, "%s", expressionF);
							if (isContainedByIndex(numbersData, expression, y)) {
								y = strEnd;
							}
						}
						else {
							char saveNumbersData[DIM] = "";
							sprintf(saveNumbersData, "%s", numbersData);
							sprintf(expressionF, "(0xS%s)", numbersData);
							sprintf(numbersData, "%s", expressionF);
							replaceTimes = 1;
							replace(saveNumbersData, numbersData, expression);
							sprintf(expression, "%s", expressionF);
							if (isContainedByIndex(numbersData, expression, y)) {
								y = strEnd;
							}
						}
					}
				}
				replaceTimes = 0;
			}
		}
		if (isContained("D", expression)) {
			replace("D", "/", expression);
			sprintf(expression, "%s", expressionF);
		}


		char alphabet[DIM] = "ABCDEFGHIJKLMNOPQRSTUWVXYZabcdefghijklmnopqrstuwvxyz";
		char saveConversions[dim][dim];
		int z = 0;
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
					replace(saveNum, smallText, expression);
					z++;
					sprintf(expression, "%s", expressionF);
					if (isContained("/", expression)) {
						expression[strStart] = '!';
						i = strEnd, h = 0; j = strStart;
						char den[DIM] = "";
						while (verifyNumberExpression(expression[i])) {
							den[h] = expression[i];
							i++; h++;
						}
						den[h] = '\0';
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
		if (isContained("/", expression) && verifyNumber(expression[strStart - 1])) {
			replaceTimes = 1;
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
				replace(new_expression, toReplace, expression);
				sprintf(expression, "%s", expressionF);
			}
			replaceTimes = 0;
			replace("D", "/", expression);
			sprintf(expression, "%s", expressionF);
		}
		if (isContained("/", expression) && verifyNumber(expression[strEnd])) {
			replaceTimes = 1;
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
			replaceTimes = 0;
			replace("D", "/", expression);
			sprintf(expression, "%s", expressionF);
		}
	}
	if (isContained("/", expression)) {
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
		if (isContained("(((", expression)) {
			replace("(((", "((", expression);
			sprintf(expression, "%s", expressionF);
		}
		if (isContained(")))", expression)) {
			replace(")))", "))", expression);
			sprintf(expression, "%s", expressionF);
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
		simpleSimplifyPolynomial(expression);
		sprintf(expression, "%s", expressionF);
		replaceTimes = 0;
		if (isContained("S", expression)) {
			replace("S", "+", expression);
			sprintf(expression, "%s", expressionF);
		}
		sprintf(expressionF, "%s", expression);
	}
	else {
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
			sprintf(expressionF, "(%s)", equaSimplified);
		}
	}
}


char* convertToString(char* string) {
	sprintf(stringHelper, "%s", string);
	return stringHelper;
}

double natureRootTest(char expression[DIM], double valuePolyR, double valuePolyI) {
	char polynomial[DIM] = "";
	sprintf(polynomial, "%s", expression);
	double k = 0;
	while (k <= 100) {
		xValuesR = k * -1;
		xValuesI = 0;
		math_processor(polynomial);
		if (resultR > -1E-12&&resultR<1E-12 && resultI >-1E-12&&resultI < 1E-12) {
			resultR = k * -1; resultI = 0;
			return resultR;
		}
		xValuesR = k;
		xValuesI = 0;
		math_processor(polynomial);
		if (resultR > -1E-12&&resultR<1E-12 && resultI >-1E-12&&resultI < 1E-12) {
			resultR = k; resultI = 0;
			return resultR;
		}
		xValuesI = k * -1;
		xValuesR = 0;
		math_processor(polynomial);
		if (resultR > -1E-12&&resultR<1E-12 && resultI >-1E-12&&resultI < 1E-12) {
			resultI = k * -1; resultR = 0;
			return resultR;
		}
		xValuesI = k;
		xValuesR = 0;
		math_processor(polynomial);
		if (resultR > -1E-12&&resultR<1E-12 && resultI >-1E-12&&resultI < 1E-12) {
			resultI = k; resultR = 0;
			return resultR;
		}
		k++;
		natureValue = k;
		resultR = 0;
		resultI = 0;
	}
	return -77777;
}

