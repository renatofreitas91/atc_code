

#include "stdafx.h"
#include "calc.h"
template <typename T>
void complex_log(T a, T b) {
	if (b == 0 && a > 0) {
		resultR = ln<T>(a);
		resultI = 0;
	}
	else {
		if (a >= mINF && a <= INF && b >= mINF && b <= INF) {
			resultR = 0; resultI = 0;
			resultR = ln<T>(pot<T>(pot<T>(a, (T)2.0, 1) + pot<T>(b, (T)2.0, 1), (T)0.5, 1));
			resultI = atan2(b, a);
		}
		else {
			if (rasf > 0) {
				printf("\nError in function domain.\n\n ==> For complex natural logarithm function the valid domain is [-INF, INF].\n\n");
				printf(" ==> Your function argument: ");
				complexNumber<T>(a, b);
			}
		}
	}
}
template <typename T>
T ln(T z) {
	T result1 = 0;
	result1 = log10(z) / log10(M_E);
	return result1;
}


template void complex_log<double>(double, double);
template void complex_log<mp_float>(mp_float, mp_float);
template double ln<double>(double);
template mp_float ln<mp_float>(mp_float);
