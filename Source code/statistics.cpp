

#include "calc.h"
#include "stdafx.h"

double gerrorc(double q) {
	if (q >= mINF && q <= INF) {
		double result = 0;
		result = boost::math::erfc(q);
		return result;
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For Gauss complementary error function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(q, 0);
			return -7.0;
		}
	}
	return 0;
}

double gerrorcinv(double a) {
	double result = 0;
	if (a <= 2 && a >= 0) {
		if (a == 0) { result = pow(2.0, 2000); return result; }
		result = boost::math::erfc_inv(a);
		return result;
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For Gauss complementary inverser error function the valid domain is [0, 2].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(a, 0);
			return -7.0;
		}
	}
	return 0;
}

double gerror(double q) {
	if (q >= mINF && q <= INF) {
		double result = 0;
		result = boost::math::erf(q);
		return result;
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For Gauss error function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(q, 0);
			return -7.0;
		}
	}
	return 0;
}

double gerrorinv(double e) {
	double result = 0;
	if (e <= 1 && e >= -1) {
		if (e == 1) { result = pow(2.0, 2000); return result; }
		if (e == -1) { result = -pow(2.0, 2000); return result; }
		result = boost::math::erf_inv(e);
		return result;
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For Gauss error function the valid domain is [-1, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(e, 0);
			return -7.0;
		}
	}
	return 0;
}

double qfunc(double x) {
	if (x >= mINF && x <= INF) {
		double result = 0, y = 0;
		y = x / sqrt(2.0);
		result = 0.5*gerrorc(y);
		return result;
	}
	else {
		if (x == 0) {
			return 0.5;
		}
		else {
			if (rasf > 0) {
				printf("\nError in function domain.\n\n ==> For Q-function the valid domain is [-INF, INF].\n\n");
				printf(" ==> Your function argument: ");
				complexNumber(x, 0);
				return -7.0;
			}
		}
	}
	return 0;
}

double qfuncinv(double p) {
	if (p >= 0 && p <= 1) {
		double result = 0, d = 0;
		d = p / 0.5;
		result = sqrt(2.0)*gerrorcinv(d);
		return result;
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For inverse Q-function the valid domain is [0, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(p, 0);
			return -7.0;
		}
	}
	return 0;
}
