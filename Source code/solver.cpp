

#include "stdafx.h"

boolean solverRunning = false, retrySolver = false;
double xValuesR = 0, xValuesI = 0, saveResultRFR = 0, saveResultRFI = 0;

double solver(char expression[DIM]) {
	if (isContained("x", expression)) {
		replace("x", "res", expression);
		sprintf(expression, "%s", expressionF);
	}
	solverRunning = true;
	solving = false;
	resultR = 0; resultI = 0;
	char equation[DIM] = "", saveEquation[DIM] = "";
	sprintf(equation, "%s", expression);
	char const * equationF = equation;
	double precisionR = 0.01, precisionI = 0, resultFR = -0.1, resultFI = 0, savePrecisionR = 0.01, savePrecisionI = 0, saveResultR = -0.1, saveResultI = 0;
	char Xequal[100] = "";
	int waitTime = 60, timesToEvaluate = 420, timesEvaluated = 0, interactions = 30;
	boolean initialR = true, initialI = true, imaginary = true, counter = true;
	if (retrySolver == (boolean)true) {
		precisionI = 0.01; resultFI = -0.1;
		savePrecisionI = 0.01; saveResultI = -0.1;
	}
	resultR = resultFR;
	resultI = resultFI;
	boolean to_solve = dataVerifier(equation, 0, 0, 1, 1);
	if (to_solve) {
		xValuesR = resultFR; xValuesI = resultFI;
		sprintf(equation, "%s", equationF);
		calcNow(equation, 0, 0);
		while (isSolved() == false && timesEvaluated < timesToEvaluate) {
			timesEvaluated++;
			if (resultFR >= (saveResultR*-1) || initialR == (boolean)true) {
				saveResultR = saveResultR * 10;
				savePrecisionR = savePrecisionR * 10;
				precisionR = savePrecisionR;
				resultFR = saveResultR;
				initialR = false;
			}
			if (retrySolver == (boolean)true) {
				if (resultFI >= (saveResultI*-1) || initialI == (boolean)true) {
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
				sprintf(equation, "%s", equationF);
				calcNow(equation, 0, 0);
				if (resultR < 0) {
					do {
						timesEvaluated++;
						if (resultR < 0) {
							resultFR = resultFR + precisionR;
							xValuesR = resultFR; xValuesI = resultFI;
							sprintf(equation, "%s", equationF);
							calcNow(equation, 0, 0);
						}
						if (resultR > 0) {
							resultFR = resultFR - precisionR;
							precisionR = precisionR / 10;
							xValuesR = resultFR; xValuesI = resultFI;
							sprintf(equation, "%s", equationF);
							calcNow(equation, 0, 0);
						}
					} while (resultR != 0 && resultFR < (saveResultR*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
				}
				else {
					do {
						timesEvaluated++;
						if (resultR > 0) {
							resultFR = resultFR + precisionR;
							xValuesR = resultFR; xValuesI = resultFI;
							sprintf(equation, "%s", equationF);
							calcNow(equation, 0, 0);
						}
						else {
							if (resultR < 0) {
								resultFR = resultFR - precisionR;
								precisionR = precisionR / 10;
								xValuesR = resultFR; xValuesI = resultFI;
								sprintf(equation, "%s", equationF);
								calcNow(equation, 0, 0);
							}
						}
					} while (resultR != 0 && resultFR < (saveResultR*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);

				}
				if (resultR == 0) {
					break;
				}
			}
			timesEvaluated++;
			if (retrySolver == (boolean)true) {
				while (resultI != 0 && resultFI < (saveResultI*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0) {
					timesEvaluated++;
					xValuesR = resultFR; xValuesI = resultFI;
					sprintf(equation, "%s", equationF);
					calcNow(equation, 0, 0);
					if (resultI < 0) {
						do {
							timesEvaluated++;
							if (resultI < 0) {
								resultFI = resultFI + precisionI;
								xValuesR = resultFR; xValuesI = resultFI;
								sprintf(equation, "%s", equationF);
								calcNow(equation, 0, 0);
							}
							if (resultI > 0) {
								resultFI = resultFI - precisionI;
								precisionI = precisionI / 10;
								xValuesR = resultFR; xValuesI = resultFI;
								sprintf(equation, "%s", equationF);
								calcNow(equation, 0, 0);
							}
						} while (resultI != 0 && resultFI < (saveResultI*-1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
					}
					else {
						do {
							timesEvaluated++;
							if (resultI > 0) {
								resultFI = resultFI + precisionI;
								xValuesR = resultFR; xValuesI = resultFI;
								sprintf(equation, "%s", equationF);
								calcNow(equation, 0, 0);
							}
							else {
								if (resultI < 0) {
									resultFI = resultFI - precisionI;
									precisionI = precisionI / 10;
									xValuesR = resultFR; xValuesI = resultFI;
									sprintf(equation, "%s", equationF);
									calcNow(equation, 0, 0);
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
		if (retrySolver == (boolean)false && ((resultR > -1E-2&&resultR < 1E-2) == false || (resultI > -1E-2&&resultI < 1E-2) == false)) {
			retrySolver = true;
			solver(expression);
			resultFR = resultR; resultFI = resultI;
			solverRunning = false;
			solving = true;
			return resultFR;
		}
		resultR = resultFR; resultI = resultFI;
		solverRunning = false;
		solving = true;
		return resultFR;
	}
	else {
		puts("\n\nYour expression has errors.\n\n");
		solverRunning = false;
		solving = true;
		return NULL;
	}
	solverRunning = false;
	solving = true;
	return NULL;
}

boolean isSolved() {
	if (resultR == 0 && resultI == 0) {
		return true;
	}
	return false;
}