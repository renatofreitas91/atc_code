

#include "stdafx.h"

boolean equationSolverRunning = false;

void equationSolver_2(char equation[DIM], int rootIndex) {
	equationSolverRunning = true;
	double valuesEqR[DIM], valuesEqI[DIM];
	int i = 0, maxExponent = 0, saveMaxExponent = 0;
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
	do {
		saveMaxExponent = maxExponent;
		double valuesEqRx[DIM], valuesEqIx[DIM];
		char expression[DIM] = "", toCalcX[DIM] = "";
		for (i = maxExponent; i > 0; i--) {
			char ValueR[DIM] = "";
			sprintf(ValueR, "%G", valuesEqR[i]);
			for (int v = 0; v < abs((int)(strlen(ValueR))); v++) {
				if (ValueR[v] == '-')
					ValueR[v] = '_';
			}
			char ValueI[DIM] = "";
			sprintf(ValueI, "%G", valuesEqI[i]);
			for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
				if (ValueI[v] == '-')
					ValueI[v] = '_';
			}
			sprintf(toCalcX, "%s(%s+%si)*(x)^%d+", toCalcX, ValueR, ValueI, i);
			sprintf(expression, "%s%s+%si\\", expression, ValueR, ValueI);
		}
		char ValueR[DIM] = "";
		sprintf(ValueR, "%G", valuesEqR[i]);
		for (int v = 0; v < abs((int)strlen(ValueR)); v++) {
			if (ValueR[v] == '-')
				ValueR[v] = '_';
		}
		char ValueI[DIM] = "";
		sprintf(ValueI, "%G", valuesEqI[i]);
		for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
			if (ValueI[v] == '-')
				ValueI[v] = '_';
		}
		sprintf(toCalcX, "%s(%s+%si)", toCalcX, ValueR, ValueI);
		sprintf(expression, "%s%s+%si", expression, ValueR, ValueI);
		if (maxExponent == 2) {
			char command[DIM] = "";
			sprintf(command, "solvequadraticequation(%s)", expression);
			solveQuadraticEquation(command, 0, 0, rootIndex);
			maxExponent = 0;
		}
		else {
			char toPowerX[DIM] = "";
			for (i = maxExponent - 1; i >= 0; i--) {
				division(valuesEqR[i], valuesEqI[i], valuesEqR[maxExponent], valuesEqI[maxExponent]);
				multiplication(resultR, resultI, -1, 0);
				valuesEqRx[i] = resultR; valuesEqIx[i] = resultI;
			}
			if (maxExponent > 1) {
				for (i = maxExponent - 1; i > 0; i--) {
					char ValueR[DIM] = "";
					sprintf(ValueR, "%G", valuesEqRx[i]);
					for (int v = 0; v < abs((int)(strlen(ValueR))); v++) {
						if (ValueR[v] == '-')
							ValueR[v] = '_';
					}
					char ValueI[DIM] = "";
					sprintf(ValueI, "%G", valuesEqIx[i]);
					for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
						if (ValueI[v] == '-')
							ValueI[v] = '_';
					}
					sprintf(toPowerX, "%s(%s+%si)*(x)^%d+", toPowerX, ValueR, ValueI, i);
				}
				char ValueR[DIM] = "";
				sprintf(ValueR, "%G", valuesEqRx[i]);
				for (int v = 0; v < abs((int)strlen(ValueR)); v++) {
					if (ValueR[v] == '-')
						ValueR[v] = '_';
				}
				char ValueI[DIM] = "";
				sprintf(ValueI, "%G", valuesEqIx[i]);
				for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
					if (ValueI[v] == '-')
						ValueI[v] = '_';
				}
				sprintf(toPowerX, "(%s(%s+%si))^(1/%d)", toPowerX, ValueR, ValueI, maxExponent);
				int solve = 0;
				resultR = 0; resultI = 0;
				variableController("x", resultR);
				for (solve = 0; solve < 100; solve++) {
					calcNow(toPowerX, 0, 0);
					variableController("x", resultR);
				}
			}
			double rootR = resultR;
			double rootI = resultI;
			resultR = 0; resultI = 0;
			variableController("x", resultR);
			if (rootR > 0 && rootI > 0) {
				printf("x%d=%G+%Gi\n", rootIndex, rootR, rootI);
			}
			else {
				if (rootR > 0 && rootI < 0) {
					printf("x%d=%G%Gi\n", rootIndex, rootR, rootI);
				}
				else {
					if (rootR < 0 && rootI > 0) {
						printf("x%d=%G+%Gi\n", rootIndex, rootR, rootI);
					}
					else {
						if (rootR < 0 && rootI < 0) {
							printf("x%d=%G%Gi\n", rootIndex, rootR, rootI);
						}
						else {
							if (rootR == 0 && rootI == 0) {
								printf("x%d=%G\n", rootIndex, rootR);
							}
							else {
								if (rootR == 0 && rootI != 0) {
									printf("x%d=%Gi\n", rootIndex, rootI);
								}
								else {
									if (rootR != 0 && rootI == 0) {
										printf("x%d=%G\n", rootIndex, rootR);
									}
									else {
										printf("x%d=%G+%Gi\n", rootIndex, rootR, rootI);
									}
								}
							}
						}
					}
				}
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
	} while (maxExponent > 0);
	equationSolverRunning = false;
}

void equationSolver(char equation[DIM]) {
	puts("");
	equationSolverRunning = true;
	double valuesEqR[DIM], valuesEqI[DIM];
	int i = 0, maxExponent = 0, rootIndex = 1, saveMaxExponent = 0;
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
	do {
		char toCalcX[DIM] = "";
		char expression[DIM] = "";
		for (i = maxExponent; i > 0; i--) {
			char ValueR[DIM] = "";
			sprintf(ValueR, "%G", valuesEqR[i]);
			for (int v = 0; v < abs((int)(strlen(ValueR))); v++) {
				if (ValueR[v] == '-')
					ValueR[v] = '_';
			}
			char ValueI[DIM] = "";
			sprintf(ValueI, "%G", valuesEqI[i]);
			for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
				if (ValueI[v] == '-')
					ValueI[v] = '_';
			}
			sprintf(toCalcX, "%s(%s+%si)*(res)^%d+", toCalcX, ValueR, ValueI, i);
			sprintf(expression, "%s%s+%si\\", expression, ValueR, ValueI);
		}
		char ValueR[DIM] = "";
		sprintf(ValueR, "%G", valuesEqR[i]);
		for (int v = 0; v < abs((int)strlen(ValueR)); v++) {
			if (ValueR[v] == '-')
				ValueR[v] = '_';
		}
		char ValueI[DIM] = "";
		sprintf(ValueI, "%G", valuesEqI[i]);
		for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
			if (ValueI[v] == '-')
				ValueI[v] = '_';
		}
		sprintf(toCalcX, "%s(%s+%si)", toCalcX, ValueR, ValueI);
		sprintf(expression, "%s%s+%si", expression, ValueR, ValueI);
		if (maxExponent == 2) {
			char command[DIM] = "";
			sprintf(command, "solvequadraticequation(%s)", expression);
			solveQuadraticEquation(command, 0, 0, rootIndex);
			maxExponent = 0;
		}
		else {
			retrySolver = false; retrySolver_2 = false; retrySolver_3 = false;
			double rootR = solver(toCalcX);
			double rootI = resultI;
			if (abs(rootR) > 1E15) {
				equationSolver_2(expression, rootIndex);
				maxExponent = 0;
			}
			else {
				if (rootR > 0 && rootI > 0) {
					printf("x%d=%G+%Gi\n", rootIndex, rootR, rootI);
				}
				else {
					if (rootR > 0 && rootI < 0) {
						printf("x%d=%G%Gi\n", rootIndex, rootR, rootI);
					}
					else {
						if (rootR < 0 && rootI > 0) {
							printf("x%d=%G+%Gi\n", rootIndex, rootR, rootI);
						}
						else {
							if (rootR < 0 && rootI < 0) {
								printf("x%d=%G%Gi\n", rootIndex, rootR, rootI);
							}
							else {
								if (rootR == 0 && rootI == 0) {
									printf("x%d=%G\n", rootIndex, rootR);
								}
								else {
									if (rootR == 0 && rootI != 0) {
										printf("x%d=%Gi\n", rootIndex, rootI);
									}
									else {
										if (rootR != 0 && rootI == 0) {
											printf("x%d=%G\n", rootIndex, rootR);
										}
										else {
											printf("x%d=%G+%Gi\n", rootIndex, rootR, rootI);
										}
									}
								}
							}
						}
					}
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
	equationSolverRunning = false;
}

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

void rootsToPolynomial(char roots[DIM]) {
	double valuesRootsR[DIM], valuesRootsI[DIM], polynomialR[DIM], polynomialI[DIM], newPolynomialR[DIM], newPolynomialI[DIM];
	int i = 0, numberRoots = 0, rootIndex = 1, saveNumberRoots = 0;
	char report[DIM] = "";
	for (i = 0; roots[i] != '\0'; i++) {
		if (roots[i] == '\\') {
			numberRoots++;
		}
	}
	numberRoots++;
	if (numberRoots == 1) {
		puts("\nError: At minimum two roots must be entered.\n");
	}
	else {
		for (i = 0; i < numberRoots * 7; i++) {
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
				sprintf(report, "%s\nFinal polynomial:\n", report);
			}
			for (pol = 0; pol < savePol; pol++) {
				if (exp > 1) {
					sprintf(report, "%s(%G+%Gi)x^%d+", report, polynomialRF[pol], polynomialIF[pol], exp);
				}
				else {
					if (exp == 1) {
						sprintf(report, "%s(%G+%Gi)x+", report, polynomialRF[pol], polynomialIF[pol]);
					}
					else {
						sprintf(report, "%s(%G+%Gi)", report, polynomialRF[pol], polynomialIF[pol]);
					}
				}
				polynomialR[pol] = polynomialRF[pol];
				polynomialRF[pol] = 0;
				polynomialI[pol] = polynomialIF[pol];
				polynomialIF[pol] = 0;
				exp--;
			}
			sprintf(report, "%s\n", report);
		}
	}
	puts(report);
	puts("Export result? (Yes -> 1 \\ No -> 0)");
	int option = (int)getValue();
	if (option == 1) {
		saveToReport(report);
	}
}