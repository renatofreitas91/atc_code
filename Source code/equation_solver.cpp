

#include "stdafx.h"

boolean equationSolverRunning = false, polySimplifier = false, solveMultiPoly = false;
char charMaster[DIM] = "", roots[DIM] = "";
int parentPol[DIM];

void solveQuadraticEquation(char arithTrig[DIM], double result1, double result2, int index) {
	char values[DIM] = "", value[DIM] = "", saveValue[DIM] = "";
	int v = 0, ct = 0;
	double aR = 0, aI = 0, bR = 0, bI = 0, cR = 0, cI = 0;
	int i = 23;
	while (arithTrig[i] != '\0'&&arithTrig[i] != ')') {
		if (arithTrig[i] == '\\') {
			ct++;
		}
		values[v] = arithTrig[i];
		v++; i++;
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
			i++; v++;
		}
		value[v] = '\0';
		calcNow(value, result1, result2);
		if (verified == 1) {
			aR = resultR;
			aI = resultI;
			i++; v = 0;
			while (values[i] != '\\') {
				value[v] = values[i];
				i++; v++;
			}
			value[v] = '\0';
			calcNow(value, result1, result2);
			if (verified == 1) {
				bR = resultR;
				bI = resultI;
				i++; v = 0;
				while (values[i] != '\0') {
					value[v] = values[i];
					i++; v++;
				}
				value[v] = '\0';
				calcNow(value, result1, result2);
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

void rootsToPolynomial(char roots[DIM]) {
	char report[DIM] = "";
	double valuesRootsR[DIM], valuesRootsI[DIM], polynomialR[DIM], polynomialI[DIM], newPolynomialR[DIM], newPolynomialI[DIM];
	int i = 0, numberRoots = 0, rootIndex = 1, saveNumberRoots = 0;
	for (i = 0; roots[i] != '\0'; i++) {
		if (roots[i] == '\\') {
			numberRoots++;
		}
	}
	numberRoots++;
	if (numberRoots == 1) {
		if (polySimplifier == (boolean)false) {
			sprintf(report, "%s\nFinal polynomial:\n", report);
		}
		calcNow(roots, 0, 0);
		sprintf(report, "(x-(%f+%fi))", resultR, resultI);
		if (isContained("(-", report)) {
			replace("(-", "(_", report);
			sprintf(report, expressionF);
		}
		if (isContained("+-", report)) {
			replace("+-", "+_", report);
			sprintf(report, expressionF);
		}
		if (isContained(".000000", report)) {
			replace(".000000", "", report);
			sprintf(report, expressionF);
		}
		sprintf(expressionF, report);
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
			while (roots[i] != '\\'&&roots[i] != '\0') {
				toValue[b] = roots[i];
				b++; i++;
			}
			toValue[b] = '\0';
			calcNow(toValue, 0, 0);
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
				polynomialRF[i] = 0; polynomialIF[i] = 0;
			}
			resultR = 0; resultI = 0;
			newPolynomialR[0] = 1;
			newPolynomialI[0] = 0;
			newPolynomialR[1] = valuesRootsR[members] * -1;
			newPolynomialI[1] = valuesRootsI[members] * -1;
			int j = 0, pol = 0;
			for (i = 0; i < members * 2; i++) {
				for (j = 0; j < 2; j++) {
					resultR = 0; resultI = 0;
					multiplication(polynomialR[i], polynomialI[i], newPolynomialR[j], newPolynomialI[j]);
					saveResultR[i][j] = resultR; saveResultI[i][j] = resultI;
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
							if ((saveResultR[i][j] == 0 && saveResultR[i + 1][j - 1] == 0 && saveResultI[i][j] == 0 && saveResultI[j + 1][j - 1] == 0) == false) {
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
			if (members == numberRoots) {
				if (polySimplifier == (boolean)false) {
					sprintf(report, "%s\nFinal polynomial:\n", report);
				}
				else {
					sprintf(report, "%s\nPolynomial simplified:\n", report);
				}
			}

			for (pol = 0; pol < savePol; pol++) {
				if (polySimplifier == (boolean)false || members == numberRoots) {
					if (exp > 1) {
						sprintf(report, "%s(%f+%fi)x^%d+", report, polynomialRF[pol], polynomialIF[pol], exp);
					}
					else {
						if (exp == 1) {
							sprintf(report, "%s(%f+%fi)x+", report, polynomialRF[pol], polynomialIF[pol]);
						}
						else {
							sprintf(report, "%s(%f+%fi)", report, polynomialRF[pol], polynomialIF[pol]);
						}
					}
				}
				polynomialR[pol] = polynomialRF[pol];
				polynomialRF[pol] = 0;
				polynomialI[pol] = polynomialIF[pol];
				polynomialIF[pol] = 0;
				exp--;
				if (polySimplifier == (boolean)false || members == numberRoots) {
					if (isContained("(-", report)) {
						replace("(-", "(_", report);
						sprintf(report, expressionF);
					}
					if (isContained("+-", report)) {
						replace("+-", "+_", report);
						sprintf(report, expressionF);
					}
					if (isContained(".000000", report)) {
						replace(".000000", "", report);
						sprintf(report, expressionF);
					}

				}
			}
			if (polySimplifier == (boolean)false || members == numberRoots) {
				sprintf(report, "%s\n", report);
			}
		}
		if (polySimplifier == (boolean)false) {
			puts(report);
			int option = -1;
			while (option != 0 && option != 1) {
				puts("Export result? (Yes -> 1 \\ No -> 0)");
				option = (int)getValue();
			}
			if (option == 1) {
				saveToReport(report);
			}
		}
		else {
			isContained("Polynomial simplified:\n", report);
			char finalPolynomial[DIM] = "";
			int h = 0, g = strEnd;
			while (report[g] != '\0') {
				finalPolynomial[h] = report[g];
				g++;
				h++;
			}
			finalPolynomial[h] = '\0';
			sprintf(expressionF, finalPolynomial);
		}
	}
}

void equationSolver(char equation[DIM]) {
	int rootIndex = 1;
	double rootR = 0, rootI = 0;
	int i = 0, maxExponent = 0, saveMaxExponent = 0;
	char toCalcX[DIM] = "";
	char saveEquation[DIM] = "";
	if (isContained(")*(", equation) || isContained(")(", equation) || isContained(")-(", equation) || isContained(")/(", equation)) {
		simplifyPolynomial(equation);
		sprintf(saveEquation, expressionF);
		sprintf(equation, expressionF);
	}
	else {
		sprintf(saveEquation, equation);
	}
	if (isContained("\\", equation)) {
		puts("");
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
			while (equation[i] != '\\'&&equation[i] != '\0') {
				toValue[b] = equation[i];
				b++; i++;
			}
			toValue[b] = '\0';
			calcNow(toValue, 0, 0);
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
		if (isContained("x^", equation) == (boolean)false || (equation_solver == (boolean)true && isContained("x", equation) && isContained("x^", equation) == (boolean)false)) {
			maxExponent = 1;
			sprintf(toCalcX, equation);
			equationSolverRunning = true;
			solving = false;
			if (equation_solver == (boolean)true && isContained("x", equation) && isContained("x^", equation) == (boolean)false) {
				sprintf(charMaster, "nothingL");
				while (isContained("x", toCalcX) && verifyLetter(toCalcX[strStart - 1]) == (boolean)false && verifyNumber(toCalcX[strStart - 1]) == (boolean)false) {
					char value[100] = "", valueF[100] = "";
					sprintf(value, "x");
					sprintf(valueF, "1*(res)^1");
					replace(value, valueF, toCalcX);
					sprintf(toCalcX, expressionF);
				}
				sprintf(charMaster, "");
				while (isContained("x", toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
					char value[100] = "", valueF[100] = "";
					sprintf(value, "%cx", toCalcX[strStart - 1]);
					sprintf(valueF, "%c*(res)^1", toCalcX[strStart - 1]);
					replace(value, valueF, toCalcX);
					sprintf(toCalcX, expressionF);
				}
				sprintf(charMaster, "");
				char saveToCalcX[DIM] = "";
				sprintf(saveToCalcX, toCalcX);
				char maxExp[10] = "";
				sprintf(maxExp, ")^%d", maxExponent);
				double dividerValue = 0;
				char divider[DIM] = "";
				while (isContained(maxExp, saveToCalcX)) {
					int b = strStart;
					while (saveToCalcX[b] != '(') {
						b--;
					}
					if (saveToCalcX[b - 1] == '*') {
						b = b - 2;
						while (verifyValue(saveToCalcX[b])) {
							b--;
						}
						b++;
						int t = 0;
						int s = b - 1;
						if (saveToCalcX[b - 1] == '-' || saveToCalcX[b - 1] == '_') {
							divider[t] = '_'; t++;

						}
						while (saveToCalcX[b + 1] != '(') {
							divider[t] = saveToCalcX[b];
							b++;
							t++;
						}
						divider[t] = '\0';
						calcNow(divider, 0, 0);
						if (isContained("_", divider) && saveToCalcX[s] == '-') {
							replace("_", "-", divider);
							sprintf(divider, expressionF);
						}
						dividerValue = dividerValue + resultR;
						char toReplace[DIM] = "";
						sprintf(toReplace, "%s*(res%s", divider, maxExp);
						isContained(toReplace, saveToCalcX);
						int y = strStart;
						while (y < strEnd) {
							saveToCalcX[y] = ' ';
							y++;
						}
						replace(" ", "", saveToCalcX);
						sprintf(saveToCalcX, expressionF);
					}
				}
				sprintf(divider, "%f", dividerValue);
				for (int y = 0; divider[y] != '\0'; y++) {
					if (divider[y] == '-') {
						divider[y] = '_';
					}
				}
				char newExpre[DIM] = "";
				char toTest[DIM] = "";
				sprintf(toTest, "(%s)", toCalcX);
				boolean testNeedPar = dataVerifier(toTest, 0, 0, 0, 1);
				if (testNeedPar) {
					sprintf(newExpre, "(%s)/%s", toCalcX, divider);
				}
				else {
					sprintf(newExpre, "%s/%s", toCalcX, divider);
				}
				sprintf(toCalcX, newExpre);
			}
		}
		else {
			equationSolverRunning = true;
			sprintf(toCalcX, equation);
			maxExponent = 1;
			char exponent[DIM] = "";
			int g = 0, k = 0;
			for (g = 0; equation[g] != '\0'; g++) {
				if (equation[g - 1] == 'x'&&equation[g] == '^') {
					int saveG = g - 2;
					g++; k = 0;
					while (verifyNumber(equation[g])) {
						exponent[k] = equation[g];
						k++; g++;
					}
					exponent[k] = '\0';
					calcNow(exponent, 0, 0);
					if ((int)resultR > maxExponent) {
						maxExponent = (int)resultR;
					}
				}
			}
			sprintf(charMaster, "nothingL");
			char maxExpX[100] = "";
			maxExponent = maxExponent;
			sprintf(maxExpX, "x^%d", maxExponent);
			while (isContained(maxExpX, toCalcX) && verifyLetter(toCalcX[strStart - 1]) == (boolean)false && verifyNumber(toCalcX[strStart - 1]) == (boolean)false) {
				char value[100] = "", valueF[100] = "";
				sprintf(value, "x^%d", maxExponent);
				sprintf(valueF, "1*(res)^%d", maxExponent);
				replace(value, valueF, toCalcX);
				sprintf(toCalcX, expressionF);
			}
			sprintf(charMaster, "");
			while (isContained(maxExpX, toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
				char value[100] = "", valueF[100] = "";
				sprintf(value, "%cx^%d", toCalcX[strStart - 1], maxExponent);
				sprintf(valueF, "%c*(res)^%d", toCalcX[strStart - 1], maxExponent);
				replace(value, valueF, toCalcX);
				sprintf(toCalcX, expressionF);
			}
			if (isContained("x", toCalcX)) {
				replace("x", "(res)", toCalcX);
				sprintf(toCalcX, expressionF);
			}
			sprintf(charMaster, "");
			char saveToCalcX[DIM] = "";
			sprintf(saveToCalcX, toCalcX);
			char maxExp[10] = "";
			sprintf(maxExp, ")^%d", maxExponent);
			double dividerValue = 0;
			char divider[DIM] = "";
			while (isContained(maxExp, saveToCalcX)) {
				int b = strStart;
				while (saveToCalcX[b] != '(') {
					b--;
				}
				if (saveToCalcX[b - 1] == '*') {
					b = b - 2;
					while (verifyValue(saveToCalcX[b])) {
						b--;
					}
					b++;
					int t = 0;
					int s = b - 1;
					if (saveToCalcX[b - 1] == '-' || saveToCalcX[b - 1] == '_') {
						divider[t] = '_'; t++;
					}
					while (saveToCalcX[b + 1] != '(') {
						divider[t] = saveToCalcX[b];
						b++;
						t++;
					}
					divider[t] = '\0';
					calcNow(divider, 0, 0);
					if (isContained("_", divider) && saveToCalcX[s] == '-') {
						replace("_", "-", divider);
						sprintf(divider, expressionF);
					}
					dividerValue = dividerValue + resultR;
					char toReplace[DIM] = "";
					sprintf(toReplace, "%s*(res%s", divider, maxExp);
					isContained(toReplace, saveToCalcX);
					int y = strStart;
					while (y < strEnd) {
						saveToCalcX[y] = ' ';
						y++;
					}
					replace(" ", "", saveToCalcX);
					sprintf(saveToCalcX, expressionF);
				}
			}
			if (dividerValue == 0) {
				dividerValue = 1;
			}
			sprintf(divider, "%f", dividerValue);
			for (int y = 0; divider[y] != '\0'; y++) {
				if (divider[y] == '-') {
					divider[y] = '_';
				}
			}
			char newExpre[DIM] = "";
			char toTest[DIM] = "";
			sprintf(toTest, "(%s)", toCalcX);
			boolean testNeedPar = dataVerifier(toTest, 0, 0, 0, 1);
			if (testNeedPar) {
				sprintf(newExpre, "(%s)/%s", toCalcX, divider);
			}
			else {
				sprintf(newExpre, "%s/%s", toCalcX, divider);
			}
			sprintf(toCalcX, newExpre);
		}
	}
	double RootR[dim], RootI[dim], to_numR[dim], to_numI[dim];
	int g = 0;
	while (g < maxExponent) {
		RootR[g] = 0.4; RootI[g] = 0.9;
		if (g < 3) {
			exponentiation(RootR[g], RootI[g], g, 0, 1);
		}
		else {
			multiplication(RootR[g], RootI[g], g, 0);
		}
		RootR[g] = resultR; RootI[g] = resultI;
		to_numR[g] = resultR; to_numI[g] = resultI;
		g++;
	}
	double saveResultR = -1, saveResultI = -1;
	int n = 0;
	resultR = 1; resultI = 1;
	while ((abs(saveResultR) > 1E-7 || abs(saveResultI) > 1E-7) && n < 37) {
		g = 0;
		while (g < maxExponent) {
			xValuesR = RootR[g]; xValuesI = RootI[g];
			calcNow(toCalcX, 0, 0);
			saveResultR = resultR; saveResultI = resultI;
			double numR = resultR, numI = resultI, resultSubR[dim], resultSubI[dim], denR = 1, denI = 0;
			int w = 0, h = 0;
			while (w < maxExponent) {
				if (w != g) {
					subtraction(RootR[g], RootI[g], RootR[w], RootI[w]);
					resultSubR[h] = resultR; resultSubI[h] = resultI;
					h++;
				}w++;
			}
			int k = h;
			h = 1;
			while (h < k) {
				multiplication(resultSubR[0], resultSubI[0], resultSubR[h], resultSubI[h]);
				resultSubR[0] = resultR; resultSubI[0] = resultI;
				h++;
			}
			denR = resultSubR[0]; denI = resultSubI[0];
			division(numR, numI, denR, denI);
			subtraction(RootR[g], RootI[g], resultR, resultI);
			RootR[g] = resultR; RootI[g] = resultI;
			g++;
		}
		n++;
	}
	char answers[DIM] = "";
	g = 0;
	while (g < maxExponent) {
		rootR = RootR[g]; rootI = RootI[g];
		if ((rootI > 1E-27&&rootI < 1E-5) || (rootI < -1E-27&&rootI>-0.001)) {
			rootI = 0;
		}
		if ((rootR > 1E-27&&rootR < 1E-5) || (rootR < -1E-27&&rootR>-0.001)) {
			rootR = 0;
		}
		if (isContained("\\", saveEquation) || isContained("x^", saveEquation) || (equation_solver == (boolean)true && isContained("x", saveEquation) && isContained("x^", equation) == (boolean)false)) {
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
						sprintf(rootRExp, expressionF);
						sprintf(roots, "%s\\%s+%fi", roots, rootRExp, rootI);
					}
					else {
						if (rootR < 0 && rootI < 0) {
							sprintf(answers, "%sx%d=%f%fi\n", answers, rootIndex, rootR, rootI);
							char rootRExp[100] = "";
							sprintf(rootRExp, "%f", rootR);
							replace("-", "_", rootRExp);
							sprintf(rootRExp, expressionF);
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
										sprintf(rootIExp, expressionF);
									}
									sprintf(roots, "%s\\%s", roots, rootIExp);
								}
								else {
									if (rootR != 0 && rootI == 0) {
										sprintf(answers, "%sx%d=%f\n", answers, rootIndex, rootR);
										char rootRExp[100] = "";
										sprintf(rootRExp, "%f", rootR);
										if (isContained("-", rootRExp)) {
											replace("-", "_", rootRExp);
											sprintf(rootRExp, expressionF);
										}
										sprintf(roots, "%s\\%s", roots, rootRExp);
									}
									else {
										sprintf(answers, "%sx%d=%f+%fi\n", answers, rootIndex, rootR, rootI);
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
			sprintf(roots, expressionF);
		}
		if (isContained(".000000", answers)) {
			replace(".000000", "", answers);
			sprintf(answers, expressionF);
		}
	}
	if (polySimplifier == (boolean)false) {
		if (isContained("\\", saveEquation) || isContained("x^", saveEquation) || (equation_solver == (boolean)true && isContained("x", saveEquation) && isContained("x^", saveEquation) == (boolean)false)) {
			puts(" ");
			puts(answers);
			int option = -1;
			while (option != 0 && option != 1) {
				puts("Export result? (Yes -> 1 \\ No -> 0)");
				option = (int)getValue();
			}
			if (option == 1) {
				saveToReport(answers);
			}
		}
		else {
			resultR = RootR[g - 1];
			resultI = RootI[g - 1];
		}
	}
	solving = true;
	equationSolverRunning = false;
}


void simpleSimplifyPolynomial(char expression[DIM]) {
	polySimplifier = true;
	sprintf(roots, "");
	char expressionS[DIM] = "";
	char toSimplify[DIM] = "";
	char exprProcessed[DIM] = "";
	sprintf(expressionS, expression);
	char divExpression[DIM] = "";
	int saveStrEnd = 0;
	int i = 0, j = 0;
	if (isContained(")(", expressionS)) {
		replace(")(", ")*(", expressionS);
		sprintf(expressionS, expressionF);
	}
	char newExpression[DIM] = "";
	int v = 0, vv = 0, vvv = 0;
	char operaTor[DIM] = "";
	char operators[DIM] = "";
	char noSignalsExpression[DIM] = "";
	while (expressionS[v] != '\0') {
		sprintf(operaTor, "%c%c%c", expressionS[v], expressionS[v + 1], expressionS[v + 2]);
		noSignalsExpression[vvv] = expressionS[v];
		if (isEqual(")+(", operaTor)) {
			operators[vv] = '+';
			vv++;
			noSignalsExpression[vvv] = ' ';
			v = v + 2;
		}
		if (isEqual(")*(", operaTor)) {
			operators[vv] = '*';
			vv++;
			noSignalsExpression[vvv] = ' ';
			v = v + 2;
		}
		if (isEqual(")/(", operaTor)) {
			operators[vv] = '/';
			vv++;
			noSignalsExpression[vvv] = ' ';
			v = v + 2;
		}
		if (isEqual(")-(", operaTor)) {
			operators[vv] = '-';
			vv++;
			noSignalsExpression[vvv] = ' ';
			v = v + 2;
		}
		v++;
		vvv++;
	}
	noSignalsExpression[vvv] = '\0';
	if (isContained(" ", noSignalsExpression)) {
		replace(" ", ")_(", noSignalsExpression);
		replace(")_(", ") (", expressionF);
		sprintf(noSignalsExpression, expressionF);
	}
	operators[vv] = '\0';
	replaceTimes = 1;
	int count_spaces = 0;
	int y = 0;
	int h = 0;
	count_spaces = 0;
	y = 0;
	h = 0;
	int ff = 0;
	char replacement[DIM] = "";
	char saveExpression[DIM] = "";
	int otherOp = 0;
	int saveOp = 0;
	char saveOperators[DIM] = "";
	char passedOperators[DIM] = "";
	if (isContained("/", operators)) {
		for (h = 0; h < vv; h++) {
			count_spaces = 0;
			sprintf(passedOperators, "");
			while (operators[h] == '/') {
				sprintf(passedOperators, "%s%c", passedOperators, operators[h]);
				for (y = 0; noSignalsExpression[y] != '\0'; y++) {
					if (noSignalsExpression[y] == ' ') {
						count_spaces++;
					}
					if (count_spaces - 1 == h) {
						break;
					}
				}
				int fg = y;
				y--;
				while (noSignalsExpression[y] != ' '&&y != 0) {
					y--;
				}
				int u = 0;
				char math_expression_1[DIM] = "";
				if (y > 0) {
					y++;
				}
				while (y < fg) {
					math_expression_1[u] = noSignalsExpression[y];
					y++; u++;
				}
				math_expression_1[u] = '\0';
				y++;
				u = 0;
				char math_expression_2[DIM] = "";
				while (noSignalsExpression[y] != ' '&&noSignalsExpression[y] != '\0') {
					math_expression_2[u] = noSignalsExpression[y];
					y++; u++;
				}
				math_expression_2[u] = '\0';
				div_polynomial(math_expression_1, math_expression_2);
				char toReplace[DIM] = "";
				sprintf(toReplace, "%s %s", math_expression_1, math_expression_2);
				if (noSignalsExpression[y] == ' ') {
					sprintf(replacement, "%s ", expressionF);
				}
				else {
					sprintf(replacement, expressionF);
				}
				replace(toReplace, expressionF, noSignalsExpression);
				sprintf(noSignalsExpression, expressionF);
				h++;
			}
			if (operators[h] != '/') {
				saveOperators[saveOp] = operators[h];
				saveOp++;
				sprintf(passedOperators, "%s%c", passedOperators, operators[h]);
				replace(replacement, "", noSignalsExpression);
				sprintf(noSignalsExpression, expressionF);
				sprintf(newExpression, "%s%s", newExpression, replacement);
				if (operators[h + 1] == '/') {
					h = -1;
				}
				else {
					h++;
				}
				replace(passedOperators, "", operators);
				sprintf(operators, expressionF);
				vv = (int)strlen(operators);
			}
		}
		saveOperators[saveOp] = '\0';
		if (strlen(saveOperators) > 0) {
			sprintf(operators, saveOperators);
		}
		sprintf(noSignalsExpression, newExpression);
		count_spaces = 0;
		vv = (int)strlen(operators);
	}
	count_spaces = 0;
	y = 0;
	h = 0;
	y = 0;
	h = 0;
	ff = 0;
	sprintf(replacement, "");
	sprintf(saveExpression, "");
	otherOp = 0;
	saveOp = 0;
	sprintf(saveOperators, "");
	sprintf(passedOperators, "");
	if (isContained("*", operators)) {
		for (h = 0; h < vv; h++) {
			count_spaces = 0;
			sprintf(passedOperators, "");
			while (operators[h] == '*') {
				sprintf(passedOperators, "%s%c", passedOperators, operators[h]);
				for (y = 0; noSignalsExpression[y] != '\0'; y++) {
					if (noSignalsExpression[y] == ' ') {
						count_spaces++;
					}
					if (count_spaces - 1 == h) {
						break;
					}
				}
				int fg = y;
				y--;
				while (noSignalsExpression[y] != ' '&&y != 0) {
					y--;
				}
				int u = 0;
				char math_expression_1[DIM] = "";
				if (y > 0) {
					y++;
				}
				while (y < fg) {
					math_expression_1[u] = noSignalsExpression[y];
					y++; u++;
				}
				math_expression_1[u] = '\0';
				y++;
				u = 0;
				char math_expression_2[DIM] = "";
				while (noSignalsExpression[y] != ' '&&noSignalsExpression[y] != '\0') {
					math_expression_2[u] = noSignalsExpression[y];
					y++; u++;
				}
				math_expression_2[u] = '\0';
				multi_polynomial(math_expression_1, math_expression_2);
				char toReplace[DIM] = "";
				sprintf(toReplace, "%s %s", math_expression_1, math_expression_2);
				if (noSignalsExpression[y] == ' ') {
					sprintf(replacement, "%s ", expressionF);
				}
				else {
					sprintf(replacement, expressionF);
				}
				replace(toReplace, expressionF, noSignalsExpression);
				sprintf(noSignalsExpression, expressionF);
				h++;
			}
			if (operators[h] != '*') {
				saveOperators[saveOp] = operators[h];
				saveOp++;
				sprintf(passedOperators, "%s%c", passedOperators, operators[h]);
				replace(replacement, "", noSignalsExpression);
				sprintf(noSignalsExpression, expressionF);
				sprintf(newExpression, "%s%s", newExpression, replacement);
				if (operators[h + 1] == '*') {
					h = -1;
				}
				else {
					h++;
				}
				replace(passedOperators, "", operators);
				sprintf(operators, expressionF);
				vv = (int)strlen(operators);
			}
		}
		saveOperators[saveOp] = '\0';
		if (strlen(saveOperators) > 0) {
			sprintf(operators, saveOperators);
		}
		sprintf(noSignalsExpression, newExpression);
		count_spaces = 0;
		vv = (int)strlen(operators);
	}
	y = 0;
	h = 0;
	for (h = 0; h < vv; h++) {
		count_spaces = 0;
		if (operators[h] == '*') {
			for (y = 0; noSignalsExpression[y] != '\0'; y++) {
				if (noSignalsExpression[y] == ' ') {
					count_spaces++;
				}
				if (count_spaces - 1 == h) {
					break;
				}
			}
			int fg = y;
			y--;
			while (noSignalsExpression[y] != ' '&&y != 0) {
				y--;
			}
			int u = 0;
			if (y > 0) {
				y++;
			}
			char math_expression_1[DIM] = "";
			while (y < fg) {
				math_expression_1[u] = noSignalsExpression[y];
				y++; u++;
			}
			math_expression_1[u] = '\0';
			y++;
			u = 0;
			char math_expression_2[DIM] = "";
			while (noSignalsExpression[y] != ' '&&noSignalsExpression[y] != '\0') {
				math_expression_2[u] = noSignalsExpression[y];
				y++; u++;
			}
			math_expression_2[u] = '\0';
			multi_polynomial(math_expression_1, math_expression_2);
			char toReplace[DIM] = "";
			sprintf(toReplace, "%s %s", math_expression_1, math_expression_2);
			replace(toReplace, expressionF, noSignalsExpression);
			sprintf(noSignalsExpression, expressionF);
		}
		if (operators[h] == '/') {
			for (y = 0; noSignalsExpression[y] != '\0'; y++) {
				if (noSignalsExpression[y] == ' ') {
					count_spaces++;
				}
				if (count_spaces - 1 == h) {
					break;
				}
			}
			int fg = y;
			y--;
			while (noSignalsExpression[y] != ' '&&y != 0) {
				y--;
			}
			int u = 0;
			char math_expression_1[DIM] = "";
			if (y > 0) {
				y++;
			}
			while (y < fg) {
				math_expression_1[u] = noSignalsExpression[y];
				y++; u++;
			}
			math_expression_1[u] = '\0';
			y++;
			u = 0;
			char math_expression_2[DIM] = "";
			while (noSignalsExpression[y] != ' '&&noSignalsExpression[y] != '\0') {
				math_expression_2[u] = noSignalsExpression[y];
				y++; u++;
			}
			math_expression_2[u] = '\0';
			div_polynomial(math_expression_1, math_expression_2);
			char toReplace[DIM] = "";
			sprintf(toReplace, "%s %s", math_expression_1, math_expression_2);
			replace(toReplace, expressionF, noSignalsExpression);
			sprintf(noSignalsExpression, expressionF);
		}
		if (operators[h] == '-') {
			for (y = 0; noSignalsExpression[y] != '\0'; y++) {
				if (noSignalsExpression[y] == ' ') {
					count_spaces++;
				}
				if (count_spaces - 1 == h) {
					break;
				}
			}
			int fg = y;
			y--;
			while (noSignalsExpression[y] != ' '&&y != 0) {
				y--;
			}
			int u = 0;
			char math_expression_1[DIM] = "";
			if (y > 0) {
				y++;
			}
			while (y < fg) {
				math_expression_1[u] = noSignalsExpression[y];
				y++; u++;
			}
			math_expression_1[u] = '\0';
			y++;
			u = 0;
			char math_expression_2[DIM] = "";
			while (noSignalsExpression[y] != ' '&&noSignalsExpression[y] != '\0') {
				math_expression_2[u] = noSignalsExpression[y];
				y++; u++;
			}
			math_expression_2[u] = '\0';
			char savemath_expression_2[DIM] = "";
			sprintf(savemath_expression_2, math_expression_2);
			sub_polynomial(math_expression_1, math_expression_2);
			char toReplace[DIM] = "";
			sprintf(toReplace, "%s %s", math_expression_1, savemath_expression_2);
			replace(toReplace, expressionF, noSignalsExpression);
			sprintf(noSignalsExpression, expressionF);
		}
		if (operators[h] == '+') {
			for (y = 0; noSignalsExpression[y] != '\0'; y++) {
				if (noSignalsExpression[y] == ' ') {
					count_spaces++;
				}
				if (count_spaces - 1 == h) {
					break;
				}
			}
			int fg = y;
			y--;
			while (noSignalsExpression[y] != ' '&&y != 0) {
				y--;
			}
			int u = 0;
			char math_expression_1[DIM] = "";
			if (y > 0) {
				y++;
			}
			while (y < fg) {
				math_expression_1[u] = noSignalsExpression[y];
				y++; u++;
			}
			math_expression_1[u] = '\0';
			y++;
			u = 0;
			char math_expression_2[DIM] = "";
			while (noSignalsExpression[y] != ' '&&noSignalsExpression[y] != '\0') {
				math_expression_2[u] = noSignalsExpression[y];
				y++; u++;
			}
			math_expression_2[u] = '\0';
			sum_polynomial(math_expression_1, math_expression_2);
			char toReplace[DIM] = "";
			sprintf(toReplace, "%s %s", math_expression_1, math_expression_2);
			replace(toReplace, expressionF, noSignalsExpression);
			sprintf(noSignalsExpression, expressionF);
		}
	}
	sprintf(expressionF, noSignalsExpression);
	replaceTimes = 0;
}
void simplifyPolynomial(char expression[DIM]) {
	sprintf(roots, "");
	polySimplifier = true;
	char expressionS[DIM] = "";
	char toSimplify[DIM] = "";
	char exprProcessed[DIM] = "";
	sprintf(expressionS, expression);
	char divExpression[DIM] = "";
	int saveStrEnd = 0;
	int i = 0, j = 0;
	if (isContained(")(", expressionS)) {
		replace(")(", ")*(", expressionS);
		sprintf(expressionS, expressionF);
	}
	int parent[DIM];
	int s = 0, c, d, k, l, h;
	for (s = 0; s < abs((int)strlen(expressionS)); s++) {
		parent[s] = 0;
	}
	int cp = 0, mark = 0;
	c = 0; d = 0; k = 0; l = 0; h = 0;
	getNumerationPol(expressionS);
	for (s = 0; expressionS[s] != '\0'&&s < abs((int)strlen(expressionS)); s++) {
		parent[s] = parentPol[s];
	}
	char newExpressionS[DIM] = "";
	sprintf(newExpressionS, expressionS);
	j = 0;
	l = 0; k = 0;
	int max = 0;
	char saveExpression[DIM] = "";
	char expToSolve[DIM] = "";
	for (j = 0; j < s; j++) {
		if (parent[j] == 0) {
			k = 0;
			expToSolve[k] = expressionS[j];
			k++; j++;
			while (parent[j] == 0 && j < s) {
				expToSolve[k] = expressionS[j];
				j++; k++;
			}
			expToSolve[k] = '\0';
			simpleSimplifyPolynomial(expToSolve);
			sprintf(saveExpression, "%s%s", saveExpression, expressionF);
			h++;
		}
		else {
			k = 0;
			l = parent[j];
			j++;
			while (parent[j] != l && j < s) {
				expToSolve[k] = expressionS[j];
				j++; k++;
			}
			expToSolve[k] = '\0';
			simplifyPolynomial(expToSolve);
			sprintf(saveExpression, "%s%s", saveExpression, expressionF);
		}
	}
	replaceTimes = 0;
	simpleSimplifyPolynomial(saveExpression);
	polySimplifier = false;
}

void getNumerationPol(char expressionS[DIM]) {
	if (isContained(")(", expressionS)) {
		replace(")(", ")*(", expressionS);
		sprintf(expressionS, expressionF);
	}
	int parent[DIM];
	int s = 0, c, d, k, l, h;
	for (s = 0; s < abs((int)strlen(expressionS)); s++) {
		parent[s] = 0;
	}
	int cp = 0, mark = 0;
	c = 0; d = 0; k = 0; l = 0; h = 0;
	for (s = 0; expressionS[s] != '\0'&&s < abs((int)strlen(expressionS)); s++) {
		if (expressionS[s] == '('&&expressionS[s + 1] == '(') {
			d = 0;
			c++;
			parent[s] = c;
			d = 1;
			k = c;
		}
		else {
			if (expressionS[s] == ')'&&expressionS[s - 1] == ')') {
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
	for (s = 0; expressionS[s] != '\0'&&s < abs((int)strlen(expressionS)); s++) {
		parentPol[s] = parent[s];
	}
}