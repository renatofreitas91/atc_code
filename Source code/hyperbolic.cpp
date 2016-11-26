

#include "calc.h"
#include "stdafx.h"


void cotanh(double x, double y) {
	complex_tanh(x, y);
	division(1.0, 0.0, resultR, resultI);
	round_complex();
}

void sech(double x, double y) {
	complex_cosh(x, y);
	division(1.0, 0.0, resultR, resultI);
	round_complex();
}

void cosech(double x, double y) {
	resultR = 0; resultI = 0;
	complex_sinh(x, y);
	division(1.0, 0.0, resultR, resultI);
	round_complex();
}

void arsinh(double x, double y) {
	resultR = 0; resultI = 0;
	double radicandR = pot(x, 2.0, 1) - pot(y, 2.0, 1) + 1;
	double radicandI = 2 * x*y;
	exponentiation(radicandR, radicandI, 1 / 2.0, 0.0, 1);
	sum(x, y, resultR, resultI);
	complex_log(resultR, resultI);
	round_complex();
}

void arcosh(double x, double y) {
	resultR = 0; resultI = 0;
	if (x >= 1 || y >= 1) {
		double radicandR = pot(x, 2.0, 1) - pot(y, 2.0, 1) - 1;
		double radicandI = 2 * x*y;
		exponentiation(radicandR, radicandI, 1 / 2.0, 0.0, 1);
		sum(x, y, resultR, resultI);
		complex_log(resultR, resultI);
	}
	round_complex();
}

void artanh(double x, double y) {
	resultR = 0; resultI = 0;
	if (abs(x) < 1 || abs(y) < 1) {
		double numR = 1 + x, numI = y;
		double denR = 1 - x, denI = -1 * y;
		division(numR, numI, denR, denI);
		complex_log(resultR, resultI);
		multiplication(1 / 2.0, 0.0, resultR, resultI);
	}
	round_complex();
}

void arcoth(double x, double y) {
	resultR = 0; resultI = 0;
	if (abs(x) > 1 || abs(y) > 1) {
		division(1.0, 0.0, x, y);
		artanh(resultR, resultI);
	}
	round_complex();
}

void arsech(double x, double y) {
	resultR = 0; resultI = 0;
	if (x > 0 && x <= 1 || y > 0 && y <= 1) {
		division(1.0, 0.0, x, y);
		arcosh(resultR, resultI);
	}
	round_complex();
}

void arcsch(double x, double y) {
	resultR = 0; resultI = 0;
	if (x != 0 || y != 0) {
		division(1.0, 0.0, x, y);
		arsinh(resultR, resultI);
	}
	round_complex();
}