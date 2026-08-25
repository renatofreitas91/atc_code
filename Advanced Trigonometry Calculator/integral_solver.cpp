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
	solveMath<T>(function);
	T y_0 = precisionValueTo<T>(resultR);
	xValuesR = b; xValuesI = 0;
	solveMath<T>(function);
	T y_n = precisionValueTo<T>(resultR);
	T summatory = y_n + y_0;
	for (int i = 1; i < n; i++) {
		xValuesR = deltaX * i + a; xValuesI = 0;
		solveMath<T>(function);
		if (i % 2 == 1) {
			summatory = summatory + precisionValueTo<T>(resultR) * 4;
		}
		else {
			summatory = summatory + precisionValueTo<T>(resultR) * 2;
		}
	}
	result = finalMultiplier * summatory;
	solverRunning = false;
	solving = true;
	return result;
}
template double calculateIntegral<double>(double, double, char*);
