

#include "stdafx.h"

boolean solverRunning = false, retrySolver = false, retrySolver_2 = false, retrySolver_3 = false, poly = true;
double xValuesR = 0, xValuesI = 0, saveResultRFR = 0, saveResultRFI = 0;
int countEntriesSolver = 0;

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
			sprintf(saveEquation, "%s", expression);
			sprintf(equation, "%s", expression);
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
			sprintf(data, "%s+1-1", expressionF);
			simplifyExpression(data);
			sprintf(data, "%s", expressionF);
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
				replace("x", "(res)", equation);
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

boolean isSolved() {
	if (resultR == 0 && resultI == 0) {
		return true;
	}
	return false;
}