

#include "calc.h"
#include "stdafx.h"

void complex_cosh(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF&& y >= mINF && y <= INF) {
		exponentiation(M_E, 0.0, x, y, 1);
		double napR = resultR, napI = resultI;
		exponentiation(M_E, 0.0, -1 * x, -1 * y, 1);
		double nap2R = resultR, nap2I = resultI;
		sum(napR, napI, nap2R, nap2I);
		double sumR = resultR, sumI = resultI;
		division(sumR, sumI, 2.0, 0.0);
		round_complex();
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For hyperbolic cosine function the valid domain is [-INF, INF].\n\n");
			complexNumber(x, y);
		}
	}
}

void complex_sinh(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF&& y >= mINF && y <= INF) {
		exponentiation(M_E, 0.0, x, y, 1);
		double napR = resultR, napI = resultI;
		exponentiation(M_E, 0.0, -1 * x, -1 * y, 1);
		double nap2R = resultR, nap2I = resultI;
		subtraction(napR, napI, nap2R, nap2I);
		double sumR = resultR, sumI = resultI;
		division(sumR, sumI, 2.0, 0.0);
		round_complex();
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For hyperbolic sine function the valid domain is [-INF, INF].\n\n");
			complexNumber(x, y);
		}
	}
}

void complex_tanh(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF&& y >= mINF && y <= INF) {
		complex_sinh(x, y);
		double numR = resultR, numI = resultI;
		complex_cosh(x, y);
		double denR = resultR, denI = resultI;
		division(numR, numI, denR, denI);
		round_complex();
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For hyperbolic tangent function the valid domain is [-INF, INF].\n\n");
			complexNumber(x, y);
		}
	}
}

void cotanh(double x, double y) {
	if (x >= mINF && x <= INF&& y >= mINF && y <= INF) {
		complex_tanh(x, y);
		division(1.0, 0.0, resultR, resultI);
		round_complex();
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For hyperbolic cotangent function the valid domain is [-INF, INF].\n\n");
			complexNumber(x, y);
		}
	}
}

void sech(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF&& y >= mINF && y <= INF) {
		complex_cosh(x, y);
		division(1.0, 0.0, resultR, resultI);
		round_complex();
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For hyperbolic secant function the valid domain is [-INF, INF].\n\n");
			complexNumber(x, y);
		}
	}
}

void cosech(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF&& y >= mINF && y <= INF) {
		complex_sinh(x, y);
		division(1.0, 0.0, resultR, resultI);
		round_complex();
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For hyperbolic cosecant function the valid domain is [-INF, INF].\n\n");
			complexNumber(x, y);
		}
	}
}

void arsinh(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF&& y >= mINF && y <= INF) {
		double radicandR = pot(x, 2.0, 1) - pot(y, 2.0, 1) + 1;
		double radicandI = 2 * x*y;
		exponentiation(radicandR, radicandI, 1 / 2.0, 0.0, 1);
		sum(x, y, resultR, resultI);
		complex_log(resultR, resultI);
		round_complex();
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc hyperbolic sine function the valid domain is [-INF, INF].\n\n");
			complexNumber(x, y);
		}
	}
}

void arcosh(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF&& y >= mINF && y <= INF) {
		double radicandR = pot(x, 2.0, 1) - pot(y, 2.0, 1) - 1;
		double radicandI = 2 * x*y;
		exponentiation(radicandR, radicandI, 1 / 2.0, 0.0, 1);
		sum(x, y, resultR, resultI);
		complex_log(resultR, resultI);
		round_complex();
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc hyperbolic cosine function the valid domain is [-INF, INF].\n\n");
			complexNumber(x, y);
		}
	}

}

void artanh(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF&& y >= mINF && y <= INF) {
		double numR = 1 + x, numI = y;
		double denR = 1 - x, denI = -1 * y;
		division(numR, numI, denR, denI);
		complex_log(resultR, resultI);
		multiplication(1 / 2.0, 0.0, resultR, resultI);
		round_complex();
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc hyperbolic tangent function the valid domain is [-1, 1].\n\n");
			complexNumber(x, y);
		}
	}

}

void arcoth(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF&& y >= mINF && y <= INF) {
		division(1.0, 0.0, x, y);
		artanh(resultR, resultI);
		round_complex();
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc hyperbolic cotangent function the valid domain is [-INF, -1] U [1, INF].\n\n");
			complexNumber(x, y);
		}
	}

}

void arsech(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF&& y >= mINF && y <= INF) {
		division(1.0, 0.0, x, y);
		arcosh(resultR, resultI);
		round_complex();
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc hyperbolic secant function the valid domain is [0, 1].\n\n");
			complexNumber(x, y);
		}
	}

}

void arcsch(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF&& y >= mINF && y <= INF) {
		division(1.0, 0.0, x, y);
		arsinh(resultR, resultI);
		round_complex();
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc hyperbolic cosecant function the valid domain is [-INF, INF] ^ != 0.\n\n");
			complexNumber(x, y);
		}
	}
}