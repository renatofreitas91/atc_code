

#include "stdafx.h"
#include "calc.h"


double INF = DBL_MAX;
double mINF = INF * -1;

void cotan(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		complex_tan(x, y);
		division(1.0, 0.0, resultR, resultI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For cotangent function the valid domain is {x| x != 0 + kpi, k = ..., -1, 0, 1, ...}  \n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}

void sec(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		complex_cos(x, y);
		division(1.0, 0.0, resultR, resultI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For secant function the valid domain is {x| x != pi/2 + kpi, k = ..., -1, 0, 1, ...}  \n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}

void cosec(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		complex_sin(x, y);
		division(1.0, 0.0, resultR, resultI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For cosecant function the valid domain is {x| x != 0 + kpi, k = ..., -1, 0, 1, ...}  \n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}

void arcosec(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		division(1.0, 0.0, x, y);
		complex_asin(resultR, resultI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc cosecant function the valid domain is [-INF, INF] ^ != [-1, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}

void arcsec(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		division(1.0, 0.0, x, y);
		complex_acos(resultR, resultI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc secant function the valid domain is ]-INF, INF[ ^ != [-1, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}

void arcotg(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		division(1.0, 0.0, x, y);
		complex_atan(resultR, resultI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc cotangent function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}

void complex_cos(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		exponentiation(M_E, 0.0, -1 * y, x, 1);
		double napR = resultR, napI = resultI;
		exponentiation(M_E, 0.0, y, -1 * x, 1);
		double nap2R = resultR, nap2I = resultI;
		sum(napR, napI, nap2R, nap2I);
		double sumR = resultR, sumI = resultI;
		division(sumR, sumI, 2.0, 0.0);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For cosine function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}

void complex_sin(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		exponentiation(M_E, 0.0, -1 * y, x, 1);
		double napR = resultR, napI = resultI;
		exponentiation(M_E, 0.0, y, -1 * x, 1);
		double nap2R = resultR, nap2I = resultI;
		subtraction(napR, napI, nap2R, nap2I);
		double sumR = resultR, sumI = resultI;
		division(sumR, sumI, 0.0, 2.0);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For sine function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}

void complex_tan(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		complex_sin(x, y);
		double numR = resultR, numI = resultI;
		complex_cos(x, y);
		double denR = resultR, denI = resultI;
		division(numR, numI, denR, denI);
		char response[DIM] = "";
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For tangent function the valid domain is {x| x != pi/2 + kpi, k = ..., -1, 0, 1, ...}  \n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}

void complex_asin(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		double radicandR = 1 - pot(x, 2.0, 1) + pot(y, 2.0, 1);
		double radicandI = -1 * 2 * x*y;
		exponentiation(radicandR, radicandI, 1 / 2.0, 0.0, 1);
		double logpR = resultR, logpI = resultI;
		sum(logpR, logpI, -1 * y, x);
		double logFR = resultR, logFI = resultI;
		complex_log(logFR, logFI);
		multiplication(resultR, resultI, 0.0, -1);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc sine function the valid domain is [-1, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}

void complex_acos(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		double radicandR = -1 * pot(x, 2.0, 1) + pot(y, 2.0, 1) + 1;
		double radicandI = -2 * x*y;
		exponentiation(radicandR, radicandI, 1 / 2.0, 0.0, 1);
		multiplication(resultR, resultI, 0.0, -1.0);
		double logpR = resultR, logpI = resultI;
		sum(logpR, logpI, x, y);
		double logFR = resultR, logFI = resultI;
		complex_log(logFR, logFI);
		multiplication(resultR, resultI, 0.0, 1);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc cosine function the valid domain is [-1, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}

void complex_atan(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		double numR = 1 + y, numI = -1 * x;
		double denR = 1 - y, denI = x;
		division(numR, numI, denR, denI);
		complex_log(resultR, resultI);
		multiplication(0.0, 1 / 2.0, resultR, resultI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc tangent function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}

double arg(double a, double b) {
	double arg_ab = 0;
	if (a > 0) {
		arg_ab = atan(b / a);
	}
	else {
		if (a < 0 && b >0) {
			arg_ab = M_PI + atan(b / a);
		}
		else {
			if (a < 0 && b < 0) {
				arg_ab = -M_PI + atan(b / a);
			}
			else {
				if (a < 0 && b == 0) {
					arg_ab = M_PI;
				}
				else {
					if (a == 0 && b < 0) {
						arg_ab = -M_PI / 2;
					}
					else {
						if (a == 0 && b > 0) {
							arg_ab = M_PI / 2;
						}
						else {
							arg_ab = 0;
						}
					}
				}
			}
		}
	}
	return arg_ab;
}