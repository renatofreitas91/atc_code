

#include "stdafx.h"
#include "calc.h"

void sinc(double x, double y) {
	if (x == 0.0 && y == 0.0) {
		resultR = 1.0; resultI = 0;
	}
	else {
		if (x != 0.0 || y != 0.0) {
			complex_sin(M_PI*x, M_PI*y);
			division(resultR, resultI, M_PI*x, M_PI*y);
		}
		else {
			if (rasf > 0.0) {
				printf("\nError in function domain.\n\n ==> For normalized sinc function the valid domain is [-INF, INF].\n\n");
				printf(" ==> Your function argument: ");
				complexNumber(x, y);
			}
		}
	}
}