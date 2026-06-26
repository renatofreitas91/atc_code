#include "stdafx.h"
#include "calc.h"
#include <cmath> // Garante acesso direto a fabs, floor, ceil, trunc, modf
template <typename T>
void sum(T numR, T numI, T denR, T denI) {
	resultR = numR + denR;
	resultI = numI + denI;
}
template <typename T>
void subtraction(T numR, T numI, T denR, T denI) {
	resultR = numR - denR;
	resultI = numI - denI;
}
template <typename T>
void multiplication(T numR, T numI, T denR, T denI) {
	resultR = numR * denR - numI * denI;
	resultI = numR * denI + numI * denR;
}
template <typename T>
void division(T numR, T numI, T denR, T denI) {
	T realNum = numR * denR + numI * denI;
	T imagNum = numI * denR - numR * denI;
	T realDen = denR * denR + denI * denI;

	resultR = realNum / realDen;
	resultI = imagNum / realDen;
}
template <typename T>
T abs_complex(T real, T imaginary) {
	T result = sqrt(real * real + imaginary * imaginary);
	return result;
}
template <typename T>
int exponentiation(T a, T b, T c, T d, int sig) {
	if (a == 0 && b == 0 && c == 0 && d == 0) {
		resultR = (sig == 0) ? -1.0 : 1.0;
		resultI = 0.0;
		return 0;
	}

	if (b != 0 || d != 0 || a < 0) {
		T r = sqrt(a * a + b * b);
		T arg_ab = atan2(b, a);

		T part1 = pow(r, c) * exp(-d * arg_ab);
		T part2 = cos(d * log(r) + c * arg_ab);
		T part3 = sin(d * log(r) + c * arg_ab);

		resultR = part1 * part2;
		resultI = part1 * part3;
	}
	else {
		resultR = pot(a, c, 1);
		resultI = 0.0;
	}

	if (sig == 0) {
		resultR = (T)0 - precisionValueTo<T>(resultR);
		resultI = (T)0 - precisionValueTo<T>(resultI);
	}
	return 0;
}

template <typename T>
T pot(T base, T exponent, int sig) {
	T base_trabalho = base;
	T result = 0;

	if (fabs(exponent) >= 1 || exponent == 0) {
		if (base_trabalho == 0 && exponent == 0) {
			return (sig == 0) ? -1.0 : 1.0;
		}

		T exponent1 = quo(exponent);
		T exponent2 = multi(exponent);
		T result2 = base_trabalho;

		if (exponent < 0) {
			exponent1 = exponent1 * -1;
		}

		if (exponent1 > 1) {
			// CORREÇÃO: Evita degradação O(N) para primos grandes em WebAssembly.
			// Se o expoente for maior que um limite prático, usamos o pow nativo diretamente.
			if (exponent1 > 100000.0) {
				result2 = pow(base_trabalho, exponent1);
			}
			else {
				int k = (int)exponent1 - 1;
				while (k > 1) {
					if ((int)exponent1 % k == 0) {
						break;
					}
					k--;
				}
				result2 = pow(base_trabalho, exponent1 / (T)k);
				for (int i = 1; i < k; i++) {
					result2 = result2 * pow(base_trabalho, exponent1 / (T)k);
				}
			}
		}
		else if (exponent1 == 1) {
			result2 = base_trabalho;
		}

		if (exponent < 0) {
			result2 = (T)1 / result2;
		}
		if (exponent < 0 && exponent2 > 0) {
			exponent2 = exponent2 * -1;
		}

		if (exponent1 >= 1) {
			result = pow(base_trabalho, exponent2) * result2;
		}
		else {
			if (exponent != 0) {
			result = pow(base_trabalho, exponent2);
		}
		else {
			result = (T)1;
		}
		}
	}
	else {
		result = rt<T>(base_trabalho, (T)1 / exponent, 1);
	}

	if (sig == 0) {
		result = -result;
	}
	return result;
}
template <typename T>
T arcfact(T f) {
	int i = 1;
	if (f >= 0) {
		// CORREÇÃO: Adicionado teto de segurança 'i < 172' para evitar loops infinitos.
		// 171! é o maior fatorial representável num T de 64 bits (~1.79e308).
		while (fact<T>((T)i) < f && i < 172) {
			i++;
		}
	}
	else {
		i = 0;
	}
	return i;
}

template <typename T>
T rt(T radicand, T degree, int sig) {
	if (radicand == 0) return 0.0;

	if (sig == 0) {
		radicand = radicand * -1;
		return -1 * rt(radicand, degree, 1);
	}

	int j = 0;
	if (degree < 0) {
		degree = degree * -1;
		j = 1;
	}

	T result = pow(10.0, log10(radicand) / degree);
	if (j == 1) {
		result = 1 / result;
	}
	return result;
}
template <typename T>
void qu_complex(T dividend, T dividendI, T divider, T dividerI) {
	division<T>(dividend, dividendI, divider, dividerI);
	resultR = trunc(precisionValueTo<T>(resultR));
	resultI = trunc(precisionValueTo<T>(resultI));
}

template <typename T>
void re_complex(T dividend, T dividendI, T divider, T dividerI) {
	qu_complex(dividend, dividendI, divider, dividerI);
	multiplication<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), divider, dividerI);
	subtraction<T>(dividend, dividendI, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
}
template <typename T>
T fl(T number) {
	T numberLeft = trunc(number);
	return number - numberLeft;
}

template <typename T>
T multi(T multip) {
	T numberLeft = trunc(multip);
	return multip - numberLeft;
}

template <typename T>
T quo(T quotient) {
	return trunc(quotient);
}

template <typename T>
T qu(T dividend, T divider) {
	return trunc(dividend / divider);
}
template <typename T>
T re(T a, T b) {
	T res = fmod(a, b);
	if (res < 0 && b > 0) res += b;
	if (res > 0 && b < 0) res += b;
	return res;
}

template <typename T>
T returnDeciPart(T number) {
	T intPart;
	return modf(number, &intPart);
}

template <typename T>
T fact(T d) {
	if (fabs(d - round(d)) > 1e-12) return 0.0;

	T rounded_d = round(d);
	if (rounded_d < 0.0) return 0.0;
	if (rounded_d == 0.0) return 1.0;

	T result = 1.0;
	for (T i = 2.0; i <= rounded_d; i += 1.0) {
		result *= i;
	}
	return result;
}

template <>
void sum<PrecisionValue>(PrecisionValue numR, PrecisionValue numI, PrecisionValue denR, PrecisionValue denI) {
	resultR = precisionValueTo<mp_float>(numR) + precisionValueTo<mp_float>(denR);
	resultI = precisionValueTo<mp_float>(numI) + precisionValueTo<mp_float>(denI);
}

template <>
void subtraction<PrecisionValue>(PrecisionValue numR, PrecisionValue numI, PrecisionValue denR, PrecisionValue denI) {
	resultR = precisionValueTo<mp_float>(numR) - precisionValueTo<mp_float>(denR);
	resultI = precisionValueTo<mp_float>(numI) - precisionValueTo<mp_float>(denI);
}

template <>
void multiplication<PrecisionValue>(PrecisionValue numR, PrecisionValue numI, PrecisionValue denR, PrecisionValue denI) {
	mp_float a = precisionValueTo<mp_float>(numR);
	mp_float b = precisionValueTo<mp_float>(numI);
	mp_float c = precisionValueTo<mp_float>(denR);
	mp_float d = precisionValueTo<mp_float>(denI);
	resultR = a * c - b * d;
	resultI = a * d + b * c;
}

template <>
void division<PrecisionValue>(PrecisionValue numR, PrecisionValue numI, PrecisionValue denR, PrecisionValue denI) {
	mp_float a = precisionValueTo<mp_float>(numR);
	mp_float b = precisionValueTo<mp_float>(numI);
	mp_float c = precisionValueTo<mp_float>(denR);
	mp_float d = precisionValueTo<mp_float>(denI);
	mp_float realDen = c * c + d * d;

	resultR = (a * c + b * d) / realDen;
	resultI = (b * c - a * d) / realDen;
}

template <>
int exponentiation<PrecisionValue>(PrecisionValue a, PrecisionValue b, PrecisionValue c, PrecisionValue d, int sig) {
	return exponentiation(
		precisionValueTo<mp_float>(a),
		precisionValueTo<mp_float>(b),
		precisionValueTo<mp_float>(c),
		precisionValueTo<mp_float>(d),
		sig);
}

int summatorial(int integer) {
	if (integer <= 0) return 0;
	return (integer * (integer + 1)) / 2;
}
template void sum<double>(double, double, double, double);
template void subtraction<double>(double, double, double, double);
template void multiplication<double>(double, double, double, double);
template void division<double>(double, double, double, double);
template int exponentiation<double>(double, double, double, double, int);
template double abs_complex<double>(double, double);
template double pot<double>(double, double, int);
template double qu<double>(double, double);
template double re<double>(double, double);
template double fact<double>(double);

template void sum<mp_float>(mp_float, mp_float, mp_float, mp_float);
template void subtraction<mp_float>(mp_float, mp_float, mp_float, mp_float);
template void multiplication<mp_float>(mp_float, mp_float, mp_float, mp_float);
template void division<mp_float>(mp_float, mp_float, mp_float, mp_float);
template int exponentiation<mp_float>(mp_float, mp_float, mp_float, mp_float, int);
template mp_float abs_complex<mp_float>(mp_float, mp_float);
template mp_float pot<mp_float>(mp_float, mp_float, int);
template mp_float qu<mp_float>(mp_float, mp_float);
template mp_float re<mp_float>(mp_float, mp_float);
template mp_float fact<mp_float>(mp_float);
template void qu_complex<double>(double, double, double, double);
template void qu_complex<mp_float>(mp_float, mp_float, mp_float, mp_float);
template void re_complex<double>(double, double, double, double);
template void re_complex<mp_float>(mp_float, mp_float, mp_float, mp_float);
template double arcfact<double>(double);
template mp_float arcfact<mp_float>(mp_float);
template double rt<double>(double, double, int);
template mp_float rt<mp_float>(mp_float, mp_float, int);


template double fl<double>(double);
template double returnDeciPart<double>(double);
template mp_float fl<mp_float>(mp_float);
template mp_float returnDeciPart<mp_float>(mp_float);
