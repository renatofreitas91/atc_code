

#include "stdafx.h"
#include "calc.h"


void sinc(double x, double y) {
	resultR = 0; resultI = 0;
	if (x != 0 || y != 0) {
		complex_sin(M_PI*x, M_PI*y);
		division(resultR, resultI, M_PI*x, M_PI*y);
	}
	else {
		resultR = 1.0; resultI = 0;
	}
	round_complex();
}