#include "stdafx.h"

double xValuesR = 0, xValuesI = 0;
boolean solverRunning = false, fromInitialProcessor = false;

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
	double precisionR = 0.01, precisionI = 0, resultFR = -0.1, resultFI = 0, savePrecisionR = 0.01, savePrecisionI = 0, saveResultR = -0.1, saveResultI = 0, time_s = 0, time_ms = 0, save_time = 0;
	char Xequal[100] = "";
	int waitTime = 60, timesToEvaluate = 300, timesEvaluated = 0;
	boolean initialR = true, initialI = true, imaginary = true;
	clock_t start, end;
	resultR = resultFR;
	resultI = resultFI;
	start = clock();
	boolean to_solve = dataVerifier(equation, 0, 0, 1, 1);
	if (to_solve) {
		xValuesR = resultFR; xValuesI = resultFI;
		sprintf(equation, "%s", equationF);
		calcNow(equation, 0, 0);
		while (isSolved() == false && time_s < waitTime && timesEvaluated < timesToEvaluate) {
			timesEvaluated++;
			if (resultFR >= (saveResultR*-1) || initialR == (boolean)true) {
				saveResultR = saveResultR * 10;
				savePrecisionR = savePrecisionR * 10;
				precisionR = savePrecisionR;
				resultFR = saveResultR;
				initialR = false;
			}
			if (resultFI >= (saveResultI*-1) || initialI == (boolean)true) {
				if (((resultI <-1E-9 || resultI>1E-9) || fromInitialProcessor == (boolean)true) && imaginary == (boolean)true) {
					resultFI = -0.1;
					saveResultI = -0.1;
					precisionI = 0.01;
					savePrecisionI = 0.01;
					imaginary = false;
				}
				saveResultI = saveResultI * 10;
				savePrecisionI = savePrecisionI * 10;
				precisionI = savePrecisionI;
				resultFI = saveResultI;
				initialI = false;
			}
			while (resultR != 0 && resultFR < (saveResultR*-1) && time_s < waitTime && timesEvaluated < timesToEvaluate) {
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
						end = clock();
						time_ms = (end - start) / (CLOCKS_PER_SEC / 1000);
						time_s = qu(time_ms, 1000);
						if (save_time != time_s) {
							save_time = time_s;
						}
					} while (resultR != 0 && resultFR < (saveResultR*-1) && time_s < waitTime&& timesEvaluated < timesToEvaluate);
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
						end = clock();
						time_ms = (end - start) / (CLOCKS_PER_SEC / 1000);
						time_s = qu(time_ms, 1000);
						if (save_time != time_s) {
							save_time = time_s;
						}
					} while (resultR != 0 && resultFR < (saveResultR*-1) && time_s < waitTime&& timesEvaluated < timesToEvaluate);

				}
				if (time_s >= waitTime) {
					printf("\n\nError: Unable to find value for x.\n\n");
					solverRunning = false;
					solving = true;
					return -7000;
				}
				else {
					if (resultR == 0) {
						break;
					}
				}
				end = clock();
				time_ms = (end - start) / (CLOCKS_PER_SEC / 1000);
				time_s = qu(time_ms, 1000);
				if (save_time != time_s) {
					save_time = time_s;
				}
			}
			while (resultI != 0 && resultFI < (saveResultI*-1) && time_s < waitTime && timesEvaluated < timesToEvaluate) {
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
						end = clock();
						time_ms = (end - start) / (CLOCKS_PER_SEC / 1000);
						time_s = qu(time_ms, 1000);
						if (save_time != time_s) {
							save_time = time_s;
						}
					} while (resultI != 0 && resultFI < (saveResultI*-1) && time_s < waitTime&& timesEvaluated < timesToEvaluate);
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
						end = clock();
						time_ms = (end - start) / (CLOCKS_PER_SEC / 1000);
						time_s = qu(time_ms, 1000);
						if (save_time != time_s) {
							save_time = time_s;
						}
					} while (resultI != 0 && resultFI < (saveResultI*-1) && time_s < waitTime&& timesEvaluated < timesToEvaluate);

				}
				if (time_s >= waitTime) {
					printf("\n\nError: Unable to find value for x.\n\n");
					solverRunning = false;
					solving = true;
					return -7000;
				}
				else {
					if (resultI == 0) {
						break;
					}
				}
				end = clock();
				time_ms = (end - start) / (CLOCKS_PER_SEC / 1000);
				time_s = qu(time_ms, 1000);
				if (save_time != time_s) {
					save_time = time_s;
				}
			}
			end = clock();
			time_ms = (end - start) / (CLOCKS_PER_SEC / 1000);
			time_s = qu(time_ms, 1000);
			if (save_time != time_s) {
				save_time = time_s;
			}
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