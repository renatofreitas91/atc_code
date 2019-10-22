

#include "stdafx.h"

boolean solverRunning = false, retrySolver = false, retrySolver_2 = false, retrySolver_3 = false, poly = true;
double xValuesR = 0, xValuesI = 0, saveResultRFR = 0, saveResultRFI = 0;
int countEntriesSolver = 0;
char saveSimplification[DIM] = "", saveSimplified[DIM] = "";

double solver(char expression[DIM]) {
	replaceTimes = 0;
	char equation[DIM] = "", saveEquation[DIM] = "";
	sprintf(saveEquation, "%s", expression);
	sprintf(equation, "%s", expression);
	if (isContained("\\", expression)) {
		int d = 0, check_integral = 0;;
		for (d = 0; expression[d] != '\0'; d++) {
			if (expression[d] == '\\') {
				check_integral++;
			}
		}
		if (check_integral == 2) {
			d = 0;
			int e = 0;
			char getValue[DIM] = "";
			while (expression[d] != '\\') {
				getValue[e] = expression[d];
				e++;
				d++;
			}
			getValue[e] = '\0';
			double a = math_processor(getValue);
			d++;
			e = 0;
			sprintf(getValue, "");
			while (expression[d] != '\\') {
				getValue[e] = expression[d];
				e++;
				d++;
			}
			getValue[e] = '\0';
			double b = math_processor(getValue);
			d++;
			char function[DIM] = "";
			e = 0;
			while (expression[d] != '\0') {
				function[e] = expression[d];
				e++;
				d++;
			}
			function[e] = '\0';
			double area = calculateIntegral(a, b, function);
			return area;
		}
	}
	boolean to_solve = dataVerifier(equation, 0, 0, 0, 1);
	solverRunning = true;

	if (to_solve) {
		if (poly) {
			sprintf(saveEquation, "%s+0", expression);
			sprintf(equation, "%s", saveEquation);
			equation_solver = true;
			resultR = 0; resultI = 0;
			lastDividerR = 1, lastDividerI = 0, natureValue = 1;
			sprintf(roots, ""), sprintf(answers, "");
			isDivisible = true;
			lastDividerR = 1, lastDividerI = 0;
			polySimplifier = false;
			char data[DIM] = "";
			sprintf(data, "%s", equation);
			sprintf(saveExpressionF, "%s", data);
			if (!isContained("\\", data)) {
				synTest = 0;
				if (dataVerifier(data, 0, 0, 0, 1)) {
					sprintf(OutputText, "");
					replaceTimes = 0;
					lastDividerR = 0;
					LastDividerR = 0;
					lastDividerI = 0;
					LastDividerI = 0;
				}
			}
			manageExpression(data, 0, 0, 1);
			sprintf(data, "%s", expressionF);
			replaceTimes = 0;
			if (isContained("(x)", data)) {
				replace("(x)", "x", data);
				sprintf(data, "%s", expressionF);
			}
			simplifyExpression(data);
			sprintf(data, "%s", expressionF);
			sprintf(saveSimplified, "%s", expressionF);
			equationSolver(data);
			int i = 0, j = 0, z = 0;
			double zeroR[dim], zeroI[dim];
			char value[dim] = "";
			replaceTimes = 0;
			char saveExpF[DIM] = "";
			sprintf(saveExpF, "%s", answers);
			while (isContained("=", saveExpF)) {
				j = 0;
				i = strEnd;
				saveExpF[strStart] = ' ';
				while (saveExpF[i] != '\0'&&saveExpF[i] != '\n') {
					value[j] = saveExpF[i];
					i++; j++;
				}
				value[j] = '\0';
				replaceTimes = 1;
				if (isContained("-", value) && strStart == 0) {
					replace("-", "_", value);
					sprintf(value, "%s", expressionF);
				}
				math_processor(value);
				zeroR[z] = resultR; zeroI[z] = resultI;
				z++;
				if (zeroI[z - 1] == 0 && zeroR[z - 1] != 0) {
					break;
				}
			}
			double saveResultR = zeroR[z - 1], saveResultI = zeroI[z - 1];
			xValuesR = saveResultR;
			xValuesI = saveResultI;
			solverRunning = true;
			replaceTimes = 0;
			if (isContained("x", equation)) {
				replace("x", "res", equation);
				sprintf(equation, "%s", expressionF);
			}
			math_processor(equation);
			if (abs(resultR) < 1E-2&&abs(resultI) < 1E-2) {
				resultR = saveResultR;
				resultI = saveResultI;
				solverRunning = false;
				equationSolverRunning = false;
				poly = false;
				return resultR;
			}
			solverRunning = false;
		}
		poly = false;
		if (isContained("x", expression)) {
			replace("x", "res", expression);
			sprintf(expression, "%s", expressionF);
		}
		solverRunning = true;
		solving = false;
		resultR = 0; resultI = 0;
		double precisionR = 0.01, precisionI = 0, resultFR = -0.1, resultFI = 0, savePrecisionR = 0.01, savePrecisionI = 0, saveResultR = -0.1, saveResultI = 0;
		char Xequal[100] = "";
		int timesToEvaluate = 300, timesEvaluated = 0, interactions = 30;
		boolean initialR = true, initialI = true, imaginary = true, counter = true;
		if (retrySolver) {
			precisionI = 0.01; resultFI = -0.1;
			savePrecisionI = 0.01; saveResultI = -0.1;
		}
		resultR = resultFR;
		resultI = resultFI;
		xValuesR = resultFR; xValuesI = resultFI; saveResultR = -0.1; saveResultI = 0;
		if ((retrySolver == (boolean)false || retrySolver) && retrySolver_2 == (boolean)false && retrySolver_3 == (boolean)false) {
			xValuesR = resultFR; xValuesI = resultFI;
			while (isSolved() == false && timesEvaluated < timesToEvaluate) {
				timesEvaluated++;
				if (resultFR >= (saveResultR*-1) || initialR) {
					saveResultR = saveResultR * 10;
					savePrecisionR = savePrecisionR * 10;
					precisionR = savePrecisionR;
					resultFR = saveResultR;
					initialR = false;
				}
				if (retrySolver) {
					if (resultFI >= (saveResultI*-1) || initialI) {
						saveResultI = saveResultI * 10;
						savePrecisionI = savePrecisionI * 10;
						precisionI = savePrecisionI;
						resultFI = saveResultI;
						initialI = false;
					}
				}
				while (resultR != 0 && resultFR < (saveResultR*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0) {
					timesEvaluated++;
					xValuesR = resultFR; xValuesI = resultFI;
					math_processor(equation);
					if (resultR < 0) {
						do {
							timesEvaluated++;
							if (resultR < 0) {
								resultFR = resultFR + precisionR;
								xValuesR = resultFR; xValuesI = resultFI;
								math_processor(equation);
							}
							if (resultR > 0) {
								resultFR = resultFR - precisionR;
								precisionR = precisionR / 10;
								xValuesR = resultFR; xValuesI = resultFI;
								math_processor(equation);
							}
						} while (resultR != 0 && resultFR < (saveResultR*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
					}
					else {
						do {
							timesEvaluated++;
							if (resultR > 0) {
								resultFR = resultFR + precisionR;
								xValuesR = resultFR; xValuesI = resultFI;
								math_processor(equation);
							}
							else {
								if (resultR < 0) {
									resultFR = resultFR - precisionR;
									precisionR = precisionR / 10;
									xValuesR = resultFR; xValuesI = resultFI;
									math_processor(equation);
								}
							}
						} while (resultR != 0 && resultFR < (saveResultR*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
					}
					if (resultR == 0) {
						break;
					}
				}
				timesEvaluated++;
				if (retrySolver) {
					while (resultI != 0 && resultFI < (saveResultI*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0) {
						timesEvaluated++;
						xValuesR = resultFR; xValuesI = resultFI;
						math_processor(equation);
						if (resultI < 0) {
							do {
								timesEvaluated++;
								if (resultI < 0) {
									resultFI = resultFI + precisionI;
									xValuesR = resultFR; xValuesI = resultFI;
									math_processor(equation);
								}
								if (resultI > 0) {
									resultFI = resultFI - precisionI;
									precisionI = precisionI / 10;
									xValuesR = resultFR; xValuesI = resultFI;
									math_processor(equation);
								}
							} while (resultI != 0 && resultFI < (saveResultI*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
						}
						else {
							do {
								timesEvaluated++;
								if (resultI > 0) {
									resultFI = resultFI + precisionI;
									xValuesR = resultFR; xValuesI = resultFI;
									math_processor(equation);
								}
								else {
									if (resultI < 0) {
										resultFI = resultFI - precisionI;
										precisionI = precisionI / 10;
										xValuesR = resultFR; xValuesI = resultFI;
										math_processor(equation);
									}
								}
							} while (resultI != 0 && resultFI < (saveResultI*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
						}
						if (resultI == 0) {
							break;
						}
					}
				}
			}
		}
		else {
			if (retrySolver_2 && retrySolver == (boolean)false && retrySolver_3 == (boolean)false) {
				xValuesR = 1E9; xValuesI = 0;
				math_processor(equation);
				double minMaxR = resultR, minMaxI = resultI;
				int i = 0, j = 0, interval = 499, c = 1, d = 0;
				int x_values[1000];
				double y_valuesR[1000];
				double y_valuesI[1000];
				int firstValueR = 0, secondValueR = 0, selected_X = 0;
				for (i = -interval; i < interval; i++) {
					xValuesR = (double)i; xValuesI = 0;
					math_processor(equation);
					x_values[j] = i;
					y_valuesR[j] = resultR;
					y_valuesI[j] = resultI;
					j++;
				}
				boolean zero = false;
				while (i < 2 * interval - 2) {
					for (i = d; i < 2 * interval - 2; i++) {
						if (y_valuesR[i] > y_valuesR[i + 1] && y_valuesR[i + 3] > y_valuesR[i + 4] && y_valuesR[i + 3] > y_valuesR[i + 1]) {
							firstValueR = x_values[i + 2];
							secondValueR = x_values[i + 4];
							selected_X = x_values[i + 3];
							zero = true;
							break;
						}
						if (y_valuesR[i] < y_valuesR[i + 1] && y_valuesR[i + 3] < y_valuesR[i + 4] && y_valuesR[i + 3] < y_valuesR[i + 1]) {
							firstValueR = x_values[i + 2];
							secondValueR = x_values[i + 4];
							selected_X = x_values[i + 3];
							zero = true;
							break;
						}
					}
					if (zero) {
						zero = false;
						if (y_valuesR[firstValueR] != INF * 2 && y_valuesR[secondValueR] != INF * 2 && y_valuesR[selected_X] != INF * 2) {
							xValuesR = firstValueR; xValuesI = 0;
							double negYR = math_processor(equation);
							double negYI = resultI;
							xValuesR = secondValueR; xValuesI = 0;
							double posYR = math_processor(equation);
							double posYI = resultI;
							double dividend = (((negYR + negYI) - (posYR + posYI))*-1) / 2;
							division(dividend, 0, minMaxR, minMaxI);
							multiplication(resultR, resultI, -1, 0);
							sum(resultR, resultI, selected_X, 0);
							if (resultR > mINF&&resultR<INF&&resultI>mINF&&resultI < INF) {
								resultFR = resultR; resultFI = resultI;
								if (physics == (boolean)false) {
								}
								xValuesR = resultFR; xValuesI = resultFI;
								math_processor(equation);
								c++;
							}
						}
						d = i + 1;
					}
					i++;
				}
				xValuesR = resultFR; xValuesI = resultFI;
				math_processor(equation);
			}
		}
		if ((retrySolver == (boolean)false && retrySolver_2 == (boolean)false && retrySolver_3 == (boolean)false && ((resultR > -1E-2&&resultR < 1E-2) == false || (resultI > -1E-2&&resultI < 1E-2) == false)) && equationSolverRunning == (boolean)false) {
			retrySolver = true;
			solverRunning = true;
			solver(expression);
			resultFR = resultR; resultFI = resultI;
			solverRunning = false;
			solving = true;
			equationSolverRunning = false;
			return resultFR;
		}
		if ((retrySolver && retrySolver_2 == (boolean)false && retrySolver_3 == (boolean)false && ((resultR > -1E-7&&resultR < 1E-7) == false || (resultI > -1E-7&&resultI < 1E-7) == false)) && equationSolverRunning == (boolean)false) {
			retrySolver = false;
			retrySolver_2 = true;
			solverRunning = true;
			solver(expression);
			resultFR = resultR; resultFI = resultI;
			solverRunning = false;
			equationSolverRunning = false;
			solving = true;
			puts("");
			return resultFR;
		}
		if ((retrySolver == (boolean)false && retrySolver_2 && retrySolver_3 == (boolean)false && ((resultR > -1 && resultR < 1) == false || (resultI > -1 && resultI < 1) == false)) && equationSolverRunning == (boolean)false) {
			retrySolver_2 = false;
			retrySolver_3 = true;
			solverRunning = true;
			solver(expression);
			resultFR = resultR; resultFI = resultI;
			solverRunning = false;
			equationSolverRunning = false;
			solving = true;
			return resultFR;
		}
		resultR = resultFR; resultI = resultFI;
		solverRunning = false;
		equationSolverRunning = false;
		solving = true;
		return resultFR;
	}
	else {
		puts("\n\nYour expression has errors.\n\n");
		solverRunning = false;
		equationSolverRunning = false;
		solving = true;
		return NULL;
	}
	solverRunning = false;
	equationSolverRunning = false;
	solving = true;
	return NULL;
}



void decrementPoly(char toCalcX[DIM], char expression[DIM], double resR, double resI) {
	int i = 0;
	double rootR, rootI;
	rootR = resR;
	rootI = resI;
	char toValue[DIM] = "";
	double valuesEqR[200], valuesEqI[200];
	replaceTimes = 0;
	int maxExponent = 0;
	for (i = 0; i < 200; i++) {
		valuesEqR[i] = 0;
		valuesEqI[i] = 0;
		i++;
	}
	for (i = 0; expression[i] != '\0'; i++) {
		if (expression[i] == '\\') {
			maxExponent++;
		}
	}
	int members = maxExponent;
	i = 0;
	while (members >= 0) {
		int b = 0;
		while (expression[i] != '\\'&&expression[i] != '\0') {
			toValue[b] = expression[i];
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
	sprintf(toCalcX, "");
	sprintf(expression, "");
	for (i = maxExponent; i > 0; i--) {
		char ValueR[DIM] = "";
		sprintf(ValueR, "%G", valuesEqR[i]);
		if (isContained("E", ValueR)) {
			sprintf(ValueR, "%f", valuesEqR[i]);
		}
		for (int v = 0; v < abs((int)(strlen(ValueR))); v++) {
			if (ValueR[v] == '-')
				ValueR[v] = '_';
		}
		char ValueI[DIM] = "";

		sprintf(ValueI, "%G", valuesEqI[i]);
		if (isContained("E", ValueI)) {
			sprintf(ValueI, "%f", valuesEqI[i]);
		}
		for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
			if (ValueI[v] == '-')
				ValueI[v] = '_';
		}
		sprintf(toCalcX, "%s(%s+%si)*(res)^%d+", toCalcX, ValueR, ValueI, i);
		sprintf(expression, "%s%s+%si\\", expression, ValueR, ValueI);
	}
	char ValueR[DIM] = "";
	sprintf(ValueR, "%G", valuesEqR[i]);
	if (isContained("E", ValueR)) {
		sprintf(ValueR, "%f", valuesEqR[i]);
	}
	for (int v = 0; v < abs((int)strlen(ValueR)); v++) {
		if (ValueR[v] == '-')
			ValueR[v] = '_';
	}
	char ValueI[DIM] = "";
	sprintf(ValueI, "%G", valuesEqI[i]);
	if (isContained("E", ValueI)) {
		sprintf(ValueI, "%f", valuesEqI[i]);
	}
	for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
		if (ValueI[v] == '-')
			ValueI[v] = '_';
	}
	sprintf(toCalcX, "%s(%s+%si)", toCalcX, ValueR, ValueI);
	sprintf(expression, "%s%s+%si", expression, ValueR, ValueI);
	double valueCoefR = 0, valueCoefI = 0, newCoefR[DIM], newCoefI[DIM];
	valueCoefR = valuesEqR[maxExponent]; valueCoefI = valuesEqI[maxExponent];
	int newMaxExponent = maxExponent - 1;
	members = newMaxExponent;
	while (members >= 0) {
		newCoefR[members] = valueCoefR; newCoefI[members] = valueCoefI;
		multiplication(rootR, rootI, valueCoefR, valueCoefI);
		sum(resultR, resultI, valuesEqR[members], valuesEqI[members]);
		valueCoefR = resultR; valueCoefI = 0;
		members--;
	}
	for (i = 0; i < maxExponent; i++) {
		valuesEqR[i] = 0; valuesEqI[i] = 0;
	}
	for (i = 0; i < maxExponent; i++) {
		valuesEqR[i] = newCoefR[i]; valuesEqI[i] = newCoefI[i];
	}
	sprintf(toCalcX, "");
	sprintf(expression, "");
	for (i = maxExponent - 1; i > 0; i--) {
		char ValueR[DIM] = "";
		if (abs(valuesEqR[i]) < 1E-1) {
			valuesEqR[i] = 0;
		}
		sprintf(ValueR, "%G", valuesEqR[i]);
		if (isContained("E", ValueR)) {
			sprintf(ValueR, "%f", valuesEqR[i]);
		}
		for (int v = 0; v < abs((int)(strlen(ValueR))); v++) {
			if (ValueR[v] == '-')
				ValueR[v] = '_';
		}
		char ValueI[DIM] = "";
		if (abs(valuesEqI[i]) < 1E-1) {
			valuesEqI[i] = 0;
		}
		sprintf(ValueI, "%G", valuesEqI[i]);
		if (isContained("E", ValueI)) {
			sprintf(ValueI, "%f", valuesEqI[i]);
		}
		for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
			if (ValueI[v] == '-')
				ValueI[v] = '_';
		}
		sprintf(toCalcX, "%s(%s+%si)*(res)^%d+", toCalcX, ValueR, ValueI, i);
		sprintf(expression, "%s%s+%si\\", expression, ValueR, ValueI);
	}
	if (abs(valuesEqR[i]) < 1E-1) {
		valuesEqR[i] = 0;
	}
	sprintf(ValueR, "%G", valuesEqR[i]);
	if (isContained("E", ValueR)) {
		sprintf(ValueR, "%f", valuesEqR[i]);
	}
	for (int v = 0; v < abs((int)strlen(ValueR)); v++) {
		if (ValueR[v] == '-')
			ValueR[v] = '_';
	}
	if (abs(valuesEqI[i]) < 1E-1) {
		valuesEqI[i] = 0;
	}
	sprintf(ValueI, "%G", valuesEqI[i]);
	if (isContained("E", ValueI)) {
		sprintf(ValueI, "%f", valuesEqI[i]);
	}
	for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
		if (ValueI[v] == '-')
			ValueI[v] = '_';
	}
	sprintf(toCalcX, "%s(%s+%si)", toCalcX, ValueR, ValueI);
	sprintf(expression, "%s%s+%si", expression, ValueR, ValueI);
	if (isContained(".000000", toCalcX)) {
		replace(".000000", "", toCalcX);
		sprintf(toCalcX, "%s", expressionF);
	}
	if (isContained(".000000", expression)) {
		replace(".000000", "", expression);
		sprintf(expression, "%s", expressionF);
	}
	sprintf(expressionF, "%s", toCalcX);
	sprintf(saveExpressionF, "%s", expression);
}

double getRealSolution(char toCalcX[DIM], char expression[DIM]) {
	puts(toCalcX);
	puts(expression);
	replaceTimes = 0;
	char equation[DIM] = "", saveEquation[DIM] = "";
	sprintf(saveEquation, "%s", toCalcX);
	sprintf(equation, "%s", toCalcX);
	boolean to_solve = dataVerifier(equation, 0, 0, 0, 1);
	solverRunning = true;
	if (to_solve) {
		if (isContained("x", toCalcX)) {
			replace("x", "res", toCalcX);
			sprintf(toCalcX, "%s", expressionF);
		}
		resultR = 0; resultI = 0;
		double precisionR = 0.01, precisionI = 0, resultFR = -0.1, resultFI = 0, savePrecisionR = 0.01, savePrecisionI = 0, saveResultR = -0.1, saveResultI = 0;
		char Xequal[100] = "";
		int timesToEvaluate = 300, timesEvaluated = 0, interactions = 30;
		boolean initialR = true, initialI = true, imaginary = true, counter = true;
		resultR = resultFR;
		resultI = resultFI;
		xValuesR = resultFR; xValuesI = resultFI; saveResultR = -0.1; saveResultI = 0;
		xValuesR = resultFR; xValuesI = resultFI;
		while (isSolved() == false && timesEvaluated < timesToEvaluate) {
			timesEvaluated++;
			if (resultFR >= (saveResultR*-1) || initialR) {
				saveResultR = saveResultR * 10;
				savePrecisionR = savePrecisionR * 10;
				precisionR = savePrecisionR;
				resultFR = saveResultR;
				initialR = false;
			}
			while (resultR != 0 && resultFR < (saveResultR*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0) {
				timesEvaluated++;
				xValuesR = resultFR; xValuesI = resultFI;
				math_processor(equation);
				if (resultR < 0) {
					do {
						timesEvaluated++;
						if (resultR < 0) {
							resultFR = resultFR + precisionR;
							xValuesR = resultFR; xValuesI = resultFI;
							math_processor(equation);
						}
						if (resultR > 0) {
							resultFR = resultFR - precisionR;
							precisionR = precisionR / 10;
							xValuesR = resultFR; xValuesI = resultFI;
							math_processor(equation);
						}
					} while (resultR != 0 && resultFR < (saveResultR*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
				}
				else {
					do {
						timesEvaluated++;
						if (resultR > 0) {
							resultFR = resultFR + precisionR;
							xValuesR = resultFR; xValuesI = resultFI;
							math_processor(equation);
						}
						else {
							if (resultR < 0) {
								resultFR = resultFR - precisionR;
								precisionR = precisionR / 10;
								xValuesR = resultFR; xValuesI = resultFI;
								math_processor(equation);
							}
						}
					} while (resultR != 0 && resultFR < (saveResultR*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
				}
				if (resultR == 0) {
					break;
				}
			}
			timesEvaluated++;

		}
		resultR = resultFR; resultI = resultFI;
		return resultFR;
	}
	else {
		puts("\n\nYour expression has errors.\n\n");
		return NULL;
	}
	return NULL;
}

double getImaginarySolution(char toCalcX[DIM], char expression[DIM]) {
	puts(toCalcX);
	puts(expression);
	replaceTimes = 0;
	char equation[DIM] = "", saveEquation[DIM] = "";
	sprintf(saveEquation, "%s", toCalcX);
	sprintf(equation, "%s", toCalcX);
	boolean to_solve = dataVerifier(equation, 0, 0, 0, 1);
	solverRunning = true;
	if (to_solve) {
		if (isContained("x", toCalcX)) {
			replace("x", "res", toCalcX);
			sprintf(toCalcX, "%s", expressionF);
		}
		resultR = 0; resultI = 0;
		double precisionR = 0, precisionI = 0.01, resultFR = 0, resultFI = -0.1, savePrecisionR = 0, savePrecisionI = 0.01, saveResultR = 0, saveResultI = -0.1;
		char Xequal[100] = "";
		int timesToEvaluate = 300, timesEvaluated = 0, interactions = 30;
		boolean initialR = true, initialI = true, imaginary = true, counter = true;
		resultR = resultFR;
		resultI = resultFI;
		xValuesR = resultFR; xValuesI = resultFI; saveResultR = 0; saveResultI = -0.1;
		xValuesR = resultFR; xValuesI = resultFI;
		while (isSolved() == false && timesEvaluated < timesToEvaluate) {
			timesEvaluated++;
			if (resultFI >= (saveResultI*-1) || initialI) {
				saveResultI = saveResultI * 10;
				savePrecisionI = savePrecisionI * 10;
				precisionI = savePrecisionI;
				resultFI = saveResultI;
				initialI = false;
			}
			while (resultI != 0 && resultFI < (saveResultI*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0) {
				timesEvaluated++;
				xValuesR = resultFR; xValuesI = resultFI;
				math_processor(equation);
				if (resultI < 0) {
					do {
						timesEvaluated++;
						if (resultI < 0) {
							resultFI = resultFI + precisionI;
							xValuesR = resultFR; xValuesI = resultFI;
							math_processor(equation);
						}
						if (resultI > 0) {
							resultFI = resultFI - precisionI;
							precisionI = precisionI / 10;
							xValuesR = resultFR; xValuesI = resultFI;
							math_processor(equation);
						}
					} while (resultI != 0 && resultFI < (saveResultI*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
				}
				else {
					do {
						timesEvaluated++;
						if (resultI > 0) {
							resultFI = resultFI + precisionI;
							xValuesR = resultFR; xValuesI = resultFI;
							math_processor(equation);
						}
						else {
							if (resultI < 0) {
								resultFI = resultFI - precisionI;
								precisionI = precisionI / 10;
								xValuesR = resultFR; xValuesI = resultFI;
								math_processor(equation);
							}
						}
					} while (resultI != 0 && resultFI < (saveResultI*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
				}
				if (resultR == 0) {
					break;
				}
			}
			timesEvaluated++;

		}
		resultR = resultFR; resultI = resultFI;
		return resultFR;
	}
	else {
		puts("\n\nYour expression has errors.\n\n");
		return NULL;
	}
	return NULL;
}

boolean isSolved() {
	if (resultR == 0 && resultI == 0) {
		return true;
	}
	return false;
}