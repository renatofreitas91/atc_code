#include "stdafx.h"

template <typename T>
T calculateIntegral(T a, T b, char* function) {
	if (isContained("x", function)) {
		replace("x", "res", function);
		sprintf(function, "%s", expressionF);
	}
	solverRunning = true;
	solving = false;
	T result = 0;
	int n = 128;
	T deltaX = (b - a) / n;
	T finalMultiplier = deltaX / 3;
	xValuesR = a; xValuesI = 0;
	solveMath(function);
	T y_0 = resultR;
	xValuesR = b; xValuesI = 0;
	solveMath(function);
	T y_n = resultR;
	T summatory = y_n + y_0;
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