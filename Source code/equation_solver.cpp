

#include "stdafx.h"

boolean equationSolverRunning = false;

void equationSolver(char equation[DIM]) {
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
	while (i >= 0) {
		i--;
	}
	i = maxExponent;
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
			sprintf(toCalcX, "%s(%s+%si)x^%d+", toCalcX, ValueR, ValueI, i);
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
			double rootR = solver(toCalcX);
			double rootI = resultI;
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