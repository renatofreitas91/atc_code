

#include "stdafx.h"
#include "calc.h"

double ln(double z) {
	double result1 = 0;
	result1 = log10(z) / log10(M_E);
	return result1;
}

void complex_log(double a, double b) {
	if (b == 0 && a > 0) {
		resultR = ln(a);
		resultI = 0;
	}
	else {
		resultR = 0; resultI = 0;
		resultR = ln(pot(pot(a, 2.0, 1) + pot(b, 2.0, 1), 0.5, 1));
		resultI = atan2(b, a);
	}
}