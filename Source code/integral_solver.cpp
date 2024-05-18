#include "stdafx.h"


double calculateIntegral(double a, double b, char function[DIM]) {
	if (isContained("x", function)) {
		replace("x", "res", function);
		sprintf(function, "%s", expressionF);
	}
	solverRunning = true;
	solving = false;
	double result = 0;
	int n = 128;
	double deltaX = (b - a) / n;
	double finalMultiplier = deltaX / 3;
	xValuesR = a; xValuesI = 0;
	solveMath(function);
	double y_0 = resultR;
	xValuesR = b; xValuesI = 0;
	solveMath(function);
	double y_n = resultR;
	double summatory = y_n + y_0;
	for (int i = 1; i < n; i++) {
		xValuesR = deltaX * i + a; xValuesI = 0;
		solveMath(function);
		if (i % 2 == 1) {
			summatory = summatory + resultR * 4;
		}
		else {
			summatory = summatory + resultR * 2;
		}
	}
	result = finalMultiplier * summatory;
	solverRunning = false;
	solving = true;
	return result;
}