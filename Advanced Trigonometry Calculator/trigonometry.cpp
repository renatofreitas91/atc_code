

#include "stdafx.h"
#include "calc.h"


PrecisionValue INF = DBL_MAX;
PrecisionValue mINF = -DBL_MAX;

template <typename T>
void cotan(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		complex_tan<T>(x, y);
		division<T>(1.0, 0.0, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For cotangent function the valid domain is {x| x != 0 + kpi, k = ..., -1, 0, 1, ...}  \n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void sec(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		complex_cos<T>(x, y);
		division<T>(1.0, 0.0, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For secant function the valid domain is {x| x != pi/2 + kpi, k = ..., -1, 0, 1, ...}  \n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void cosec(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		complex_sin<T>(x, y);
		division<T>(1.0, 0.0, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For cosecant function the valid domain is {x| x != 0 + kpi, k = ..., -1, 0, 1, ...}  \n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void arcosec(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		division<T>(1.0, 0.0, x, y);
		complex_asin<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc cosecant function the valid domain is [-INF, INF] ^ != [-1, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void arcsec(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		division<T>(1.0, 0.0, x, y);
		complex_acos<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc secant function the valid domain is ]-INF, INF[ ^ != [-1, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void arcotg(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		division<T>(1.0, 0.0, x, y);
		complex_atan<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc cotangent function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void complex_cos<T>(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		exponentiation<T>(M_E, 0.0, -1 * y, x, 1);
		T napR = precisionValueTo<T>(resultR), napI = precisionValueTo<T>(resultI);
		exponentiation<T>(M_E, 0.0, y, -1 * x, 1);
		T nap2R = precisionValueTo<T>(resultR), nap2I = precisionValueTo<T>(resultI);
		sum<T>(napR, napI, nap2R, nap2I);
		T sumR = precisionValueTo<T>(resultR), sumI = precisionValueTo<T>(resultI);
		division<T>(sumR, sumI, 2.0, 0.0);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For cosine function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void complex_sin<T>(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		exponentiation<T>(M_E, 0.0, -1 * y, x, 1);
		T napR = precisionValueTo<T>(resultR), napI = precisionValueTo<T>(resultI);
		exponentiation<T>(M_E, 0.0, y, -1 * x, 1);
		T nap2R = precisionValueTo<T>(resultR), nap2I = precisionValueTo<T>(resultI);
		subtraction<T>(napR, napI, nap2R, nap2I);
		T sumR = precisionValueTo<T>(resultR), sumI = precisionValueTo<T>(resultI);
		division<T>(sumR, sumI, 0.0, 2.0);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For sine function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void complex_tan<T>(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		complex_sin<T>(x, y);
		T numR = precisionValueTo<T>(resultR), numI = precisionValueTo<T>(resultI);
		complex_cos<T>(x, y);
		T denR = precisionValueTo<T>(resultR), denI = precisionValueTo<T>(resultI);
		division<T>(numR, numI, denR, denI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For tangent function the valid domain is {x| x != pi/2 + kpi, k = ..., -1, 0, 1, ...}  \n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void complex_asin<T>(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		T radicandR = 1 - pot<T>(x, 2.0, 1) + pot<T>(y, 2.0, 1);
		T radicandI = -1 * 2 * x*y;
		exponentiation<T>(radicandR, radicandI, 1 / 2.0, 0.0, 1);
		T logpR = precisionValueTo<T>(resultR), logpI = precisionValueTo<T>(resultI);
		sum<T>(logpR, logpI, -1 * y, x);
		T logFR = precisionValueTo<T>(resultR), logFI = precisionValueTo<T>(resultI);
		complex_log<T>(logFR, logFI);
		multiplication<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), T(0.0), T(-1));
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc sine function the valid domain is [-1, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void complex_acos<T>(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		T radicandR = -1 * pot<T>(x, 2.0, 1) + pot<T>(y, 2.0, 1) + 1;
		T radicandI = -2 * x*y;
		exponentiation<T>(radicandR, radicandI, 1 / 2.0, 0.0, 1);
		multiplication<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), 0.0, -1.0);
		T logpR = precisionValueTo<T>(resultR), logpI = precisionValueTo<T>(resultI);
		sum<T>(logpR, logpI, x, y);
		T logFR = precisionValueTo<T>(resultR), logFI = precisionValueTo<T>(resultI);
		complex_log<T>(logFR, logFI);
		multiplication<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), T(0.0), T(1));
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc cosine function the valid domain is [-1, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void complex_atan<T>(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		T numR = 1 + y, numI = -1 * x;
		T denR = 1 - y, denI = x;
		division<T>(numR, numI, denR, denI);
		complex_log<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
		multiplication<T>(0.0, 1 / 2.0, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc tangent function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
T arg(T a, T b) {
	T arg_ab = 0;
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

template void cotan<double>(double, double);
template void cotan<mp_float>(mp_float, mp_float);
template void sec<double>(double, double);
template void sec<mp_float>(mp_float, mp_float);
template void cosec<double>(double, double);
template void cosec<mp_float>(mp_float, mp_float);
template void arcosec<double>(double, double);
template void arcosec<mp_float>(mp_float, mp_float);
template void arcsec<double>(double, double);
template void arcsec<mp_float>(mp_float, mp_float);
template void arcotg<double>(double, double);
template void arcotg<mp_float>(mp_float, mp_float);
template void complex_cos<double>(double, double);
template void complex_cos<mp_float>(mp_float, mp_float);
template void complex_sin<double>(double, double);
template void complex_sin<mp_float>(mp_float, mp_float);
template void complex_tan<double>(double, double);
template void complex_tan<mp_float>(mp_float, mp_float);
template void complex_asin<double>(double, double);
template void complex_asin<mp_float>(mp_float, mp_float);
template void complex_acos<double>(double, double);
template void complex_acos<mp_float>(mp_float, mp_float);
template void complex_atan<double>(double, double);
template void complex_atan<mp_float>(mp_float, mp_float);
template double arg<double>(double, double);
template mp_float arg<mp_float>(mp_float, mp_float);
