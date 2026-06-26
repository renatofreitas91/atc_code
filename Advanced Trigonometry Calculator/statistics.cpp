

#include "calc.h"
#include "stdafx.h"
template <typename T>
T gerrorc(T q) {
	if (q >= mINF && q <= INF) {
		T result = 0;
		result = boost::math::erfc(q);
		return result;
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For Gauss complementary error function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber<T>(q, 0);
			return -7.0;
		}
	}
	return 0;
}
template <typename T>
T gerrorcinv(T a) {
	T result = 0;
	if (a <= 2 && a >= 0) {
		if (a == 0) { result = pot<T>(T(2.0), 2000, 1); return result; }
		result = boost::math::erfc_inv(a);
		return result;
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For Gauss complementary inverser error function the valid domain is [0, 2].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber<T>(a, 0);
			return -7.0;
		}
	}
	return 0;
}
template <typename T>
T gerror(T q) {
	if (q >= mINF && q <= INF) {
		T result = 0;
		result = boost::math::erf(q);
		return result;
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For Gauss error function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber<T>(q, 0);
			return -7.0;
		}
	}
	return 0;
}
template <typename T>
T gerrorinv(T e) {
	T result = 0;
	if (e <= 1 && e >= -1) {
		if (e == 1) { result = pot<T>(T(2.0), 2000, 1); return result; }
		if (e == -1) { result = -pot<T>(T(2.0), 2000, 1); return result; }
		result = boost::math::erf_inv(e);
		return result;
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For Gauss error function the valid domain is [-1, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber<T>(e, 0);
			return -7.0;
		}
	}
	return 0;
}
template <typename T>
T qfunc(T x) {
	if (x >= mINF && x <= INF) {
		T result = 0, y = 0;
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
				complexNumber<T>(x, 0);
				return -7.0;
			}
		}
	}
	return 0;
}
template <typename T>
T qfuncinv(T p) {
	if (p >= 0 && p <= 1) {
		T result = 0, d = 0;
		d = p / 0.5;
		result = sqrt(2.0)*gerrorcinv(d);
		return result;
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For inverse Q-function the valid domain is [0, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber<T>(p, 0);
			return -7.0;
		}
	}
	return 0;
}

template double gerrorc<double>(double);
template mp_float gerrorc<mp_float>(mp_float);
template double gerrorcinv<double>(double);
template mp_float gerrorcinv<mp_float>(mp_float);
template double gerror<double>(double);
template mp_float gerror<mp_float>(mp_float);
template double gerrorinv<double>(double);
template mp_float gerrorinv<mp_float>(mp_float);
template double qfunc<double>(double);
template mp_float qfunc<mp_float>(mp_float);
template double qfuncinv<double>(double);
template mp_float qfuncinv<mp_float>(mp_float);
