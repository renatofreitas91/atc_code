

#include "stdafx.h"
#include "calc.h"

void sum(double numR, double numI, double denR, double denI) {
	resultR = numR + denR;
	resultI = numI + denI;
}

void subtraction(double numR, double numI, double denR, double denI) {
	resultR = numR - denR;
	resultI = numI - denI;
}

void multiplication(double numR, double numI, double denR, double denI) {
	resultR = numR * denR - numI * denI;
	resultI = numR * denI + numI * denR;
}

void division(double numR, double numI, double denR, double denI) {
	double realNum = numR * denR + numI * denI;
	double imagNum = numI * denR - numR * denI;
	double realDen = denR * denR + denI * denI;
	resultR = realNum / realDen;
	resultI = imagNum / realDen;
}

double abs_complex(double real, double imaginary) {
	resultR = sqrt(real*real + imaginary * imaginary);
	resultI = 0;
	return resultR;
}

void qu_complex(double dividend, double dividendI, double divider, double dividerI) {
	double  rest = 0;
	char quot[DIM] = "", quotI[DIM] = "", quo[DIM] = "", quoI[DIM] = "";
	char *pointer;
	int i = 0;
	division(dividend, dividendI, divider, dividerI);
	sprintf(quot, "%f", resultR);
	i = 0;
	while (quot[i] != '.'&&quot[i] != '\0') {
		quo[i] = quot[i];
		i++;
	}
	quo[i] = '\0';
	resultR = strtod(quo, &pointer);
	i = 0;
	sprintf(quotI, "%f", resultI);
	while (quotI[i] != '.'&&quot[i] != '\0') {
		quoI[i] = quotI[i];
		i++;
	}
	quoI[i] = '\0';
	resultI = strtod(quoI, &pointer);
}

void exponentiation(double a, double b, double c, double d, int sig) {
	if (sig == 0) {
		if (a == 0 && b == 0 && c == 0 && d == 0) {
			resultR = -1; resultI = 0;
		}
		else {
			a = a * -1; b = b * -1;
			exponentiation(a, b, c, d, 1);
			resultR = resultR * -1;
			resultI = resultI * -1;
		}
	}
	else {
		if (sig == 1) {
			if (a == 0 && b == 0 && c == 0 && d == 0) {
				resultR = 1.0; resultI = 0;
			}
			else {
				if (b != 0 || d != 0 || a < 0) {
					double r = sqrt(pow(a, 2.0) + pow(b, 2.0));
					double arg_ab = atan2(b, a);
					double part1 = pow(r, c)*pow(M_E, -d * arg_ab);
					double part2 = cos(d*log(r) + c * arg_ab);
					double part3 = sin(d*log(r) + c * arg_ab);
					resultR = part1 * part2;
					resultI = part1 * part3;
				}
				else {
					resultR = pot(a, c, sig);
					resultI = 0;
				}
			}
		}
	}
}

void re_complex(double dividend, double dividendI, double divider, double dividerI) {
	double  qui = 0, rest = 0;
	qu_complex(dividend, dividendI, divider, dividerI);
	multiplication(resultR, resultI, divider, dividerI);
	subtraction(dividend, dividendI, resultR, resultI);
}

double fl(double number) {
	double qu, res = 0;
	char quot[DIM] = "", quo[DIM] = "0.";
	char *pointer;
	int i = 0, j = 2;
	sprintf(quot, "%f", number);
	while (quot[i] != '.') {
		i++;
	}
	i++;
	while (quot[i] != '\0') {
		quo[j] = quot[i];
		j++; i++;
	}
	quo[j] = '\0';
	qu = strtod(quo, &pointer);
	return qu;
}

double pot(double base, double exponent, int sig) {
	double result = 0;
	if (abs(exponent) >= 1 || exponent == 0) {
		double rest = 0, result2 = 0;
		double exponent1, exponent2;
		int k = 0;
		if (sig == 0) {
			if (base == 0 && exponent == 0) {
				return -1.0;
			}
			base = base * -1;
			result = -1 * pot((double)base, (double)exponent, 1);
		}
		else {
			if (sig == 1) {
				if (base == 0 && exponent == 0) {
					return 1.0;
				}
				exponent1 = quo(exponent);
				exponent2 = multi(exponent);
				result2 = base;
				if (exponent < 0) {
					exponent1 = exponent1 * -1;
				}
				if (exponent1 > 1) {
					k = (int)exponent1 - 1;
					while (k > 1) {
						if ((int)exponent1%k == 0) {
							break;
						}
						k--;
					}
					result2 = pow(base, exponent1 / (double)k);
					for (int i = 1; i < k; i++) {
						result2 = result2 * pow(base, exponent1 / (double)k);
					}
				}
				else {
					if (exponent1 == 1) {
						result2 = base;
					}
				}

				if (exponent < 0) {
					result2 = 1 / result2;
				}
				if (exponent < 0 && exponent2>0) {
					exponent2 = exponent2 * -1;
				}
				if (exponent1 >= 1) {
					result = pow((double)base, (double)exponent2)*result2;
				}
				else {
					if (exponent != 0) {
						result = pow((double)base, (double)exponent2);
					}
					else {
						result = 1;
					}
				}
			}
		}
	}
	else {
		result = rt((double)base, 1 / (double)exponent, sig);
	}
	return result;
}


double multi(double multip) {
	double mu;
	char mult[DIM] = "", mul[DIM] = "";
	char *pointer;
	int i = 0, j = 0;
	sprintf(mult, "%.150f", multip);
	mul[0] = '0'; i++;
	while (mult[j] != '.') { j++; }
	while (mult[j] != '\0') {
		mul[i] = mult[j];
		i++;
		j++;
	}
	mul[i] = '\0';
	mu = strtod(mul, &pointer);
	if (multip < 0 && mu >= 0) {
		mu = mu * -1;
	}
	return mu;
}

double quo(double quotient) {
	double qu, quoti;
	char quot[DIM] = "", quo[DIM] = "";
	char *pointer;
	int i = 0;
	sprintf(quot, "%.150f", quotient);
	while (quot[i] != '.'&&quot[i] != '\0') {
		quo[i] = quot[i];
		i++;
	}
	quo[i] = '\0';
	qu = strtod(quo, &pointer);
	quoti = quotient - (quotient - qu);
	return quoti;
}

double qu(double dividend, double divider) {
	double quotient, qu, rest = 0;
	char quot[DIM] = "", quo[DIM] = "";
	char *pointer;
	int i = 0;
	quotient = dividend / divider;
	sprintf(quot, "%f", quotient);
	while (quot[i] != '.'&&quot[i] != '\0') {
		quo[i] = quot[i];
		i++;
	}
	quo[i] = '\0';
	qu = strtod(quo, &pointer);
	return qu;
}

double re(double dividend, double divider) {
	double quotient, qui = 0, res, rest = 0;
	char quot[DIM] = "", quo[DIM] = "";
	char *pointer;
	int i = 0;
	quotient = dividend / divider;
	sprintf(quot, "%.300f", quotient);
	while (quot[i] != '.'&&quot[i] != '\0'&&i < abs((int)strlen(quot))) {
		quo[i] = quot[i];
		i++;
	}
	quo[i] = '\0';
	qui = strtod(quo, &pointer);
	res = quotient - qui;
	rest = qu(res*divider, 1);
	return rest;
}

double arcfact(double f) {
	int i = 1;
	if (f >= 0) {
		while (fact(i) < f) {
			i++;
		}
	}
	else {
		i = 0;
	}
	return i;
}

double fact(double d) {
	double result = d;
	if (re(d, 1.0) == 0) {
		if (d > 0) {
			d--;
			while (d >= 1) {
				result = result * d;
				d--;
			}
		}
		else {
			if (d == 0) {
				result = 1;
			}
			else {
				result = 0;
			}
		}
	}
	else {
		result = 0;
	}
	return result;
}

double returnDeciPart(double number) {
	double qu;
	char quot[DIM] = "", quo[DIM] = "";
	char *pointer;
	int i = 0;
	sprintf(quot, "%.100f", number);
	while (quot[i] != '.'&&quot[i] != '\0') {
		quo[i] = quot[i];
		i++;
	}
	quo[i] = '\0';
	qu = strtod(quo, &pointer);
	return qu;
}

int summatorial(int integer) {
	int result = 0, i = integer;
	while (i > 0) {
		result = result + i;
		i--;
	}
	return result;
}

double rt(double radicand, double degree, int sig) {
	double result = -1.79769E308, precision = 1.79769E308;
	int i = 0, j = 0;
	if (radicand == 0) {
		result = 0;
		return result;
	}
	if (sig == 0) {
		radicand = radicand * -1;
		result = -1 * rt((double)radicand, (double)degree, 1);
		sig = 1;
	}
	else {
		if (sig == 1) {
			if (degree < 0) {
				degree = degree * -1;
				j = 1;
			}
			result = pow(10.0, log10(radicand) / degree);
			if (j == 1) {
				result = 1 / result;
				j = 0;
			}
		}
	}
	return result;
}
