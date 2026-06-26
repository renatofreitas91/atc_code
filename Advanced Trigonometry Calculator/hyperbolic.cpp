

#include "calc.h"
#include "stdafx.h"

template <typename T>
void complex_cosh<T>(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		exponentiation<T>(M_E, 0.0, x, y, 1);
		T napR = precisionValueTo<T>(resultR), napI = precisionValueTo<T>(resultI);

		exponentiation<T>(M_E, 0.0, -1 * x, -1 * y, 1);
		T nap2R = precisionValueTo<T>(resultR), nap2I = precisionValueTo<T>(resultI);

		sum<T>(napR, napI, nap2R, nap2I);
		T sumR = precisionValueTo<T>(resultR), sumI = precisionValueTo<T>(resultI);

		division<T>(sumR, sumI, 2.0, 0.0);
	}
	else {
		if (rasf > 0 && physics == (bool)false) {
			printf("\nError in function domain.\n\n ==> For hyperbolic cosine function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>

void complex_sinh<T>(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		exponentiation<T>(M_E, 0.0, x, y, 1);
		T napR = precisionValueTo<T>(resultR), napI = precisionValueTo<T>(resultI);

		exponentiation<T>(M_E, 0.0, -1 * x, -1 * y, 1);
		T nap2R = precisionValueTo<T>(resultR), nap2I = precisionValueTo<T>(resultI);

		subtraction<T>(napR, napI, nap2R, nap2I);
		T sumR = precisionValueTo<T>(resultR), sumI = precisionValueTo<T>(resultI);

		division<T>(sumR, sumI, 2.0, 0.0);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For hyperbolic sine function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void complex_tanh<T>(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		complex_sinh<T>(x, y);
		T numR = precisionValueTo<T>(resultR), numI = precisionValueTo<T>(resultI);

		complex_cosh<T>(x, y);
		T denR = precisionValueTo<T>(resultR), denI = precisionValueTo<T>(resultI);

		division<T>(numR, numI, denR, denI);
	}
	else {
		if (rasf > 0 && physics == (bool)false) {
			printf("\nError in function domain.\n\n ==> For hyperbolic tangent function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>

void cotanh(T x, T y) {
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		complex_tanh<T>(x, y);
		T tR = precisionValueTo<T>(resultR), tI = precisionValueTo<T>(resultI);

		division<T>(1.0, 0.0, tR, tI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For hyperbolic cotangent function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>

void sech(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		complex_cosh<T>(x, y);
		T cR = precisionValueTo<T>(resultR), cI = precisionValueTo<T>(resultI);

		division<T>(1.0, 0.0, cR, cI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For hyperbolic secant function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void cosech(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		complex_sinh<T>(x, y);
		T sR = precisionValueTo<T>(resultR), sI = precisionValueTo<T>(resultI);

		division<T>(1.0, 0.0, sR, sI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For hyperbolic cosecant function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>

void arsinh<T>(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		T radicandR = pot<T>(x, 2.0, 1) - pot<T>(y, 2.0, 1) + 1;
		T radicandI = 2 * x * y;

		exponentiation<T>(radicandR, radicandI, 1 / 2.0, 0.0, 1);
		T expR = precisionValueTo<T>(resultR), expI = precisionValueTo<T>(resultI);

		sum<T>(x, y, expR, expI);
		T sumR = precisionValueTo<T>(resultR), sumI = precisionValueTo<T>(resultI);

		complex_log<T>(sumR, sumI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc hyperbolic sine function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>

void arcosh<T>(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		T radicandR = pot<T>(x, 2.0, 1) - pot<T>(y, 2.0, 1) - 1;
		T radicandI = 2 * x * y;

		exponentiation<T>(radicandR, radicandI, 1 / 2.0, 0.0, 1);
		T expR = precisionValueTo<T>(resultR), expI = precisionValueTo<T>(resultI);

		sum<T>(x, y, expR, expI);
		T sumR = precisionValueTo<T>(resultR), sumI = precisionValueTo<T>(resultI);

		complex_log<T>(sumR, sumI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc hyperbolic cosine function the valid domain is [-INF, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>
void artanh<T>(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		T numR = 1 + x, numI = y;
		T denR = 1 - x, denI = -1 * y;

		division<T>(numR, numI, denR, denI);
		T divR = precisionValueTo<T>(resultR), divI = precisionValueTo<T>(resultI);

		complex_log<T>(divR, divI);
		T logR = precisionValueTo<T>(resultR), logI = precisionValueTo<T>(resultI);

		multiplication<T>(1 / 2.0, 0.0, logR, logI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc hyperbolic tangent function the valid domain is [-1, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>

void arcoth(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		division<T>(1.0, 0.0, x, y);
		T divR = precisionValueTo<T>(resultR), divI = precisionValueTo<T>(resultI);

		artanh<T>(divR, divI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc hyperbolic cotangent function the valid domain is [-INF, -1] U [1, INF].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>

void arsech(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		division<T>(1.0, 0.0, x, y);
		T divR = precisionValueTo<T>(resultR), divI = precisionValueTo<T>(resultI);

		arcosh<T>(divR, divI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc hyperbolic secant function the valid domain is [0, 1].\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}
template <typename T>

void arcsch(T x, T y) {
	resultR = 0; resultI = 0;
	if (x >= mINF && x <= INF && y >= mINF && y <= INF) {
		division<T>(1.0, 0.0, x, y);
		T divR = precisionValueTo<T>(resultR), divI = precisionValueTo<T>(resultI);

		arsinh<T>(divR, divI);
	}
	else {
		if (rasf > 0) {
			printf("\nError in function domain.\n\n ==> For arc hyperbolic cosecant function the valid domain is [-INF, INF] ^ != 0.\n\n");
			printf(" ==> Your function argument: ");
			complexNumber(x, y);
		}
	}
}

template void complex_cosh<double>(double, double);
template void complex_cosh<mp_float>(mp_float, mp_float);
template void complex_sinh<double>(double, double);
template void complex_sinh<mp_float>(mp_float, mp_float);
template void complex_tanh<double>(double, double);
template void complex_tanh<mp_float>(mp_float, mp_float);
template void cotanh<double>(double, double);
template void cotanh<mp_float>(mp_float, mp_float);
template void sech<double>(double, double);
template void sech<mp_float>(mp_float, mp_float);
template void cosech<double>(double, double);
template void cosech<mp_float>(mp_float, mp_float);
template void arsinh<double>(double, double);
template void arsinh<mp_float>(mp_float, mp_float);
template void arcosh<double>(double, double);
template void arcosh<mp_float>(mp_float, mp_float);
template void artanh<double>(double, double);
template void artanh<mp_float>(mp_float, mp_float);
template void arcoth<double>(double, double);
template void arcoth<mp_float>(mp_float, mp_float);
template void arsech<double>(double, double);
template void arsech<mp_float>(mp_float, mp_float);
template void arcsch<double>(double, double);
template void arcsch<mp_float>(mp_float, mp_float);
