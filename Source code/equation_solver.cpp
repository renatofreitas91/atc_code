




#include "stdafx.h"

boolean equationSolverRunning = false, polySimplifier = false, solveMultiPoly = false, simplifying = true;;
char charMaster[DIM] = "", roots[DIM] = "", polyNo[DIM] = "";
int parentPol[DIM];
double lastDividerR = 1, lastDividerI = 0;

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
		sprintf(report, "%s(%f+%fi)x-(%f+%fi)", report, lastDividerR, lastDividerI, resultR,
			resultI);
		if (isContained("(-", report)) {
			replace("(-", "(_", report);
			sprintf(report, "%s", expressionF);
		}
		if (isContained("+-", report)) {
			replace("+-", "+_", report);
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
		if (isContained("))", report)) {
			replace("))", ")", report);
			sprintf(report, "%s", expressionF);
		}
		if (strlen(expressionF) > 0) {
			sprintf(report, "(%s)", expressionF);
		}
		sprintf(expressionF, "%s", report);
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
		members = 0;
		polynomialR[0] = 1;
		polynomialI[0] = 0;
		polynomialR[1] = valuesRootsR[0] * -1;
		polynomialI[1] = valuesRootsI[0] * -1;
		double saveResultR[dim][dim], saveResultI[dim][dim];
		double polynomialRF[DIM], polynomialIF[DIM];
		while (members < numberRoots) {
			for (i = 0; i < members * 3; i++) {
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
								saveResultI[i][j] == 0 && saveResultI[j + 1][j - 1] == 0) ==
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
						sprintf(toSimplify, "%.4f+%.4fi", resultR, resultI);
						if (isContained("-", toSimplify)) {
							replace("-", "_", toSimplify);
							sprintf(toSimplify, "%s", expressionF);
						}
						math_processor(toSimplify);
						if (resultR != 0 || resultI != 0) {
							sprintf(Report, "%s(%f+%fi)x^%d+", report, resultR, resultI,
								exp);
						}
					}
					else {
						if (exp == 1) {
							multiplication(polynomialRF[pol], polynomialIF[pol], lastDividerR,
								lastDividerI);
							char toSimplify[100] = "";
							sprintf(toSimplify, "%.4f+%.4fi", resultR, resultI);
							if (isContained("-", toSimplify)) {
								replace("-", "_", toSimplify);
								sprintf(toSimplify, "%s", expressionF);
							}
							math_processor(toSimplify);
							if (resultR != 0 || resultI != 0) {
								sprintf(Report, "%s(%f+%fi)x+", report, resultR, resultI);
							}
						}
						else {
							multiplication(polynomialRF[pol], polynomialIF[pol], lastDividerR,
								lastDividerI);
							sprintf(Report, "%s(%f+%fi)", report, resultR,
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
				if (isContained("+-", report)) {
					replace("+-", "+_", report);
					sprintf(report, "%s", expressionF);
				}
				if (isContained(".000000", report)) {
					replace(".000000", "", report);
					sprintf(report, "%s", expressionF);
				}
			}
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
			sprintf(expressionF, "%s", finalPolynomial);
		}
	}
}

void equationSolver(char equation[DIM]) {
	bool isFirstDegree = false;
	if (!isDivisible) {
		sprintf(expressionF, equation);
	}
	else {
		char saveToZeroDiv[DIM] = "";
		sprintf(saveToZeroDiv, "%s", equation);
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
		replaceTimes = 1;
		if (isContained("((", equation) && isContained("))", equation)) {
			replace("((", "(", equation);
			sprintf(equation, "%s", expressionF);
			replace("))", ")", equation);
			sprintf(equation, "%s", expressionF);
		}
		replaceTimes = 0;
		int rootIndex = 1;
		double rootR = 0, rootI = 0;
		int i = 0, maxExponent = 0, saveMaxExponent = 0;
		char toCalcX[DIM] = "";
		char saveEquation[DIM] = "";
		sprintf(expressionF, "");
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
		if (isContained("[", equation)) {
			replace("[", "(", equation);
			sprintf(equation, "%s", expressionF);
		}
		if (isContained("]", equation)) {
			replace("]", ")", equation);
			sprintf(equation, "%s", expressionF);
		}
		if (!dataVerifier(equation, 0, 0, 0, 1)) {
			if (isContained("((", equation)) {
				replace("((", "(", equation);
				sprintf(equation, "%s", expressionF);
				if (isContained("))", equation)) {
					replace("))", ")", equation);
					sprintf(equation, "%s", expressionF);
				}
			}
		}
		sprintf(saveEquation, "%s", equation);
		char divider[100] = "";
		if (isContained("\\", equation)) {
			equationSolverRunning = true;
			solving = false;
			double valuesEqR[DIM], valuesEqI[DIM];
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
				while (equation[i] != '\\' && equation[i] != '\0') {
					toValue[b] = equation[i];
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
				sprintf(toCalcX, "%s(%s+%si)*(res)^%d+", toCalcX, ValueR, ValueI, i);
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
		}
		else {
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
			char saveToCalcX[DIM] = "";
			sprintf(saveToCalcX, "%s", toCalcX);
			char maxExp[10] = "";
			sprintf(maxExp, ")^%d", maxExponent);
			maxExponent = getCorrectExponent(saveToCalcX, maxExp, maxExponent);

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
			if (maxExponent == 1) {
				isFirstDegree = true;
				maxExponent = 2;
				sprintf(toCalcX, "%s*(res)", toCalcX);
			}
			double RootR[dim], RootI[dim], to_numR[dim], to_numI[dim];
			int g = 0;
			while (g < maxExponent) {
				RootR[g] = 0.1;
				RootI[g] = 0.1;
				multiplication(RootR[g], RootI[g], g + 1, 0);
				RootR[g] = resultR;
				RootI[g] = resultI;
				to_numR[g] = resultR;
				to_numI[g] = resultI;
				g++;
			}
			double saveResultR = -1, saveResultI = -1;
			int n = 0;
			resultR = 1;
			resultI = 1;
			boolean notSolved = true;
			while (notSolved&&n < 30) {
				g = 0;
				notSolved = false;
				replaceTimes = 0;
				while (g < maxExponent) {
					xValuesR = RootR[g];
					xValuesI = RootI[g];
					math_processor(toCalcX);
					char value[dim] = "";
					sprintf(value, "%.10f+%.10fi", resultR, resultI);
					if (isContained("-", value)) {
						replace("-", "_", value);
						sprintf(value, "%s", expressionF);
					}
					math_processor(value);
					saveResultR = resultR;
					saveResultI = resultI;
					if ((saveResultR == 0 && saveResultI == 0) == false) {
						notSolved = true;
					}
					double numR = resultR, numI = resultI, resultSubR[dim], resultSubI[dim], denR = 1, denI = 0;
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
					g++;
				}
				n++;
			}
			char answers[DIM] = "";
			g = 0;
			while (g < maxExponent) {
				rootR = RootR[g];
				rootI = RootI[g];
				if ((rootI > 1E-27 && rootI < 1E-5) || (rootI < -1E-27 && rootI > -0.001)) {
					rootI = 0;
				}
				if ((rootR > 1E-27 && rootR < 1E-5) || (rootR < -1E-27 && rootR > -0.001)) {
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
								sprintf(roots, "%s\\%s+%Gi", roots, rootRExp, rootI);
							}
							else {
								if (rootR < 0 && rootI < 0) {
									sprintf(answers, "%sx%d=%f%fi\n", answers, rootIndex, rootR, rootI);
									char rootRExp[100] = "";
									sprintf(rootRExp, "%f", rootR);
									replace("-", "_", rootRExp);
									sprintf(rootRExp, "%s", expressionF);
									sprintf(roots, "%s\\%s%Gi", roots, rootRExp, rootI);
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
												if (isContained("-", roots)) {
													if (isContained("-", roots)) {
														replace("-", "_", roots);
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
			if (isFirstDegree) {
				if (isContained("\\0", roots)) {
					replace("\\0", "", roots);
					sprintf(roots, "%s", expressionF);
				}
				else {
					if (isContained("0\\", roots)) {
						replace("0\\", "", roots);
						sprintf(roots, "%s", expressionF);
					}
				}
				if (isContained("x1=0\n", answers)) {
					replace("x1=0\n", "", answers);
					sprintf(answers, "%s", expressionF);
				}
				else {
					if (isContained("\nx2=0\0", answers)) {
						replace("\nx2=0\0", "", answers);
						sprintf(answers, "%s", expressionF);
					}
				}
			}
			if (polySimplifier == (boolean)false) {
				if ((isContained("\\", saveEquation) || isContained("x^", saveEquation) ||
					(equation_solver == (boolean)true && isContained("x", saveEquation) &&
						isContained("x^", saveEquation) == (boolean)false)) && solverRunning == false) {
					sprintf(expressionF, "%s", answers);
				}
				else {
					if (RootR[0] == 0 && RootI[0] == 0) {
						resultR = RootR[1];
						resultI = RootI[1];
					}
					else {
						resultR = RootR[0];
						resultI = RootI[0];
					}
				}
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

		equationSolverRunning = false;
		solving = true;
	}
}




void simpleSimplifyPolynomial(char expression[DIM]) {
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
				sprintf(poly_2, "(0x+1)");
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
				sprintf(poly_2, "(0x+1)");


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
		sprintf(expressionF, "%s", poly_1);
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
			sprintf(expressionF, "((%s)*(0x+1))%s", getSimpleExpression, getRestExpression);
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
			sprintf(expressionF, "%s(%s*(0x+1))", getRestExpression, getSimpleExpression);
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
		simpleSimplifyPolynomial(expressionS);
	}
	if (!isDivisible) {
		sprintf(expressionF, "%s", saveExpressionF);
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
				sprintf(toSimplify, "%.4f+%.4fi", resultR, resultI);
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
		if (dividerValueR == 0 && dividerValueI == 0 && maxExponent >= 1) {
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
void simplifyExpression(char expression[DIM]) {
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
				if (expression[p - 1] == 'x' && expression[p] == '^' && verifyNumber(expression[p + 1])) {
					equa[q] = ' ';
					p++; q++;
					while (verifyNumber(expression[p])) {
						equa[q] = ' ';
						q++; p++;
					}
				}
				if (expression[p - 1] == ')' && (expression[p] == '*' || expression[p] == '/') && expression[p + 1] == '(') {
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
					sprintf(value, "[%f+%fi]", resultR, resultI);
				}
				else {
					sprintf(value, "[%f+%fi]", resultR, resultI);
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
				if (expression[q - 1] == 'x' && expression[q] == '^' && verifyNumber(expression[q + 1])) {
					equaSimplified[p] = expression[q];
					p++;
					q++;
					while (verifyNumber(expression[q])) {
						equaSimplified[p] = expression[q];
						q++; p++;
					}

				}
				if (expression[q - 1] == ')' && (expression[q] == '*' || expression[q] == '/') && expression[q + 1] == '(') {
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
		sprintf(expressionF, "%s", equaSimplified);
	}
}