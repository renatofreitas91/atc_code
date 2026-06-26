
#include "stdafx.h"

bool studyFunction = false;

template <typename T>
static void writeFunctionStudyPolynomial(T* coefficients, int degree, char* output);

static bool hasBalancedOuterParentheses(const char* expression) {
	if (expression == nullptr) {
		return false;
	}
	int len = abs((int)strlen(expression));
	if (len < 2 || expression[0] != '(' || expression[len - 1] != ')') {
		return false;
	}
	int depth = 0;
	for (int i = 0; i < len; i++) {
		if (expression[i] == '(') {
			depth++;
		}
		if (expression[i] == ')') {
			depth--;
			if (depth == 0 && i < len - 1) {
				return false;
			}
		}
	}
	return depth == 0;
}

template <typename T>
static T normalizeFunctionStudyValue(T value) {
	return abs(precisionDisplayDouble(value)) < 1E-9 ? (T)0 : value;
}

template <typename T>
static bool sameFunctionStudyValue(T left, T right) {
	return abs(precisionDisplayDouble(left - right)) < 1E-7;
}

static void normalizeFunctionStudyPolynomial(char* expression) {
	if (expression == nullptr || abs((int)strlen(expression)) == 0) {
		return;
	}
	char* source = getDynamicCharArray(expression, "functionStudyPolynomialSource");
	while (hasBalancedOuterParentheses(source)) {
		int len = abs((int)strlen(source));
		for (int i = 1; i < len - 1; i++) {
			source[i - 1] = source[i];
		}
		source[len - 2] = '\0';
	}
	char* normalized = getDynamicCharArray("", "functionStudyPolynomialNormalized");
	char* term = getDynamicCharArray("", "functionStudyPolynomialTerm");
	int depth = 0, termIndex = 0;
	char pendingOperator = '+';
	for (int i = 0; i <= abs((int)strlen(source)); i++) {
		char current = source[i];
		bool split = false;
		if ((current == '+' || current == '-') && depth == 0 && termIndex > 0) {
			split = true;
		}
		if (current == '\0') {
			split = true;
		}
		if (split) {
			term[termIndex] = '\0';
			if (abs((int)strlen(term)) > 0) {
				if (abs((int)strlen(normalized)) == 0) {
					if (pendingOperator == '-') {
						sprintf(normalized, "-(%s)", term);
					}
					else {
						sprintf(normalized, "(%s)", term);
					}
				}
				else {
					sprintf(normalized, "%s%c(%s)", normalized, pendingOperator, term);
				}
			}
			termIndex = 0;
			if (current == '\0') {
				break;
			}
			pendingOperator = current;
			continue;
		}
		if (current == '(') {
			depth++;
		}
		if (current == ')') {
			depth--;
		}
		term[termIndex] = current;
		termIndex++;
	}
	if (abs((int)strlen(normalized)) > 0) {
		sprintf(expression, "%s", normalized);
	}
	_delete(source, "functionStudyPolynomialSource"); source = nullptr;
	_delete(normalized, "functionStudyPolynomialNormalized"); normalized = nullptr;
	_delete(term, "functionStudyPolynomialTerm"); term = nullptr;
}

template <typename T>
static bool buildCanonicalFromSimplePolynomial(char* expression, char* output) {
	if (expression == nullptr || abs((int)strlen(expression)) == 0) {
		return false;
	}
	T* coefficients = getDynamicArray<T>(DIMDOUBLE);
	char* source = getDynamicCharArray(expression, "functionStudySimplePolynomialSource");
	while (hasBalancedOuterParentheses(source)) {
		int len = abs((int)strlen(source));
		for (int i = 1; i < len - 1; i++) {
			source[i - 1] = source[i];
		}
		source[len - 2] = '\0';
	}
	int depth = 0, termIndex = 0, degree = 0;
	char sign = '+';
	char* term = getDynamicCharArray("", "functionStudySimplePolynomialTerm");
	bool parsed = true;
	for (int i = 0; i <= abs((int)strlen(source)); i++) {
		char current = source[i];
		bool split = false;
		if ((current == '+' || current == '-') && depth == 0 && termIndex > 0) {
			split = true;
		}
		if (current == '\0') {
			split = true;
		}
		if (split) {
			term[termIndex] = '\0';
			while (hasBalancedOuterParentheses(term)) {
				int len = abs((int)strlen(term));
				for (int k = 1; k < len - 1; k++) {
					term[k - 1] = term[k];
				}
				term[len - 2] = '\0';
			}
			int exponent = 0;
			T coefficient = sign == '-' ? (T)-1 : (T)1;
			if (isContained("x", term)) {
				exponent = 1;
				if (strStart > 0) {
					char* coefficientText = getDynamicCharArray("", "functionStudySimpleCoefficient");
					for (int k = 0; k < strStart; k++) {
						if (term[k] != '*') {
							coefficientText[abs((int)strlen(coefficientText))] = term[k] == '_' ? '-' : term[k];
						}
					}
					if (abs((int)strlen(coefficientText)) > 0) {
						if (isEqual(coefficientText, "-")) {
							coefficient *= (T)-1;
						}
						else {
							coefficient *= (T)atof(coefficientText);
						}
					}
					_delete(coefficientText, "functionStudySimpleCoefficient"); coefficientText = nullptr;
				}
				if (term[strEnd] == '^') {
					exponent = atoi(term + strEnd + 1);
				}
			}
			else {
				for (int k = 0; k < abs((int)strlen(term)); k++) {
					if (term[k] == '_') {
						term[k] = '-';
					}
				}
				coefficient *= (T)atof(term);
			}
			if (exponent < 0 || exponent >= DIMDOUBLE) {
				parsed = false;
				break;
			}
			coefficients[exponent] += coefficient;
			if (exponent > degree && coefficients[exponent] != 0) {
				degree = exponent;
			}
			termIndex = 0;
			if (current == '\0') {
				break;
			}
			sign = current;
			continue;
		}
		if (current == '(') {
			depth++;
		}
		if (current == ')') {
			depth--;
		}
		if (current != ' ' && current != '\t') {
			term[termIndex] = current;
			termIndex++;
		}
	}
	if (parsed) {
		writeFunctionStudyPolynomial<T>(coefficients, degree, output);
	}
	_delete(coefficients, "functionStudySimplePolynomialCoefficients"); coefficients = nullptr;
	_delete(source, "functionStudySimplePolynomialSource"); source = nullptr;
	_delete(term, "functionStudySimplePolynomialTerm"); term = nullptr;
	return parsed;
}

template <typename T>
static T powerInt(T base, int exponent) {
	T value = (T)1;
	for (int i = 0; i < exponent; i++) {
		value *= base;
	}
	return value;
}

template <typename T>
static bool evaluateCanonicalPolynomial(char* expression, T xValue, T* value) {
	if (expression == nullptr || !isContained("i)", expression)) {
		return false;
	}
	char* polynomial = getDynamicCharArray(expression, "functionStudyCanonicalPolynomial");
	while (hasBalancedOuterParentheses(polynomial)) {
		int len = abs((int)strlen(polynomial));
		for (int i = 1; i < len - 1; i++) {
			polynomial[i - 1] = polynomial[i];
		}
		polynomial[len - 2] = '\0';
	}
	T total = (T)0;
	bool foundTerm = false;
	int i = 0;
	while (i < abs((int)strlen(polynomial))) {
		if (polynomial[i] != '(') {
			i++;
			continue;
		}
		int start = i + 1;
		int depth = 1;
		i++;
		while (polynomial[i] != '\0' && depth > 0) {
			if (polynomial[i] == '(') {
				depth++;
			}
			if (polynomial[i] == ')') {
				depth--;
			}
			i++;
		}
		if (depth != 0) {
			_delete(polynomial, "functionStudyCanonicalPolynomial"); polynomial = nullptr;
			return false;
		}
		int end = i - 1;
		char* coefficient = getDynamicCharArray("", "functionStudyPolynomialCoefficient");
		int c = 0;
		for (int k = start; k < end; k++) {
			coefficient[c] = polynomial[k] == '_' ? '-' : polynomial[k];
			c++;
			if (polynomial[k] == 'i') {
				break;
			}
		}
		coefficient[c] = '\0';
		for (int k = 0; k < abs((int)strlen(coefficient)); k++) {
			if (coefficient[k] == 'i') {
				coefficient[k] = '\0';
				break;
			}
		}
		T coefficientValue = (T)atof(coefficient);
		int exponent = 0;
		if (polynomial[i] == 'x') {
			exponent = 1;
			i++;
			if (polynomial[i] == '^') {
				i++;
				exponent = atoi(polynomial + i);
				while (polynomial[i] >= '0' && polynomial[i] <= '9') {
					i++;
				}
			}
		}
		total += coefficientValue * powerInt<T>(xValue, exponent);
		foundTerm = true;
		_delete(coefficient, "functionStudyPolynomialCoefficient"); coefficient = nullptr;
	}
	_delete(polynomial, "functionStudyCanonicalPolynomial"); polynomial = nullptr;
	if (foundTerm) {
		*value = total;
	}
	return foundTerm;
}

template <typename T>
static bool splitFunctionStudyRational(char* expression, char* numerator, char* denominator) {
	int depth = 0;
	for (int i = 0; i < abs((int)strlen(expression)); i++) {
		if (expression[i] == '(') {
			depth++;
		}
		if (expression[i] == ')') {
			depth--;
		}
		if (expression[i] == '/' && depth == 0) {
			int n = 0;
			for (int k = 0; k < i; k++) {
				numerator[n] = expression[k];
				n++;
			}
			numerator[n] = '\0';
			int d = 0;
			for (int k = i + 1; k < abs((int)strlen(expression)); k++) {
				denominator[d] = expression[k];
				d++;
			}
			denominator[d] = '\0';
			return true;
		}
	}
	return false;
}

template <typename T>
static T solveFunctionStudyExpression(char* expression) {
	T xValue = precisionValueTo<T>(resultR);
	char* rationalNumerator = getDynamicCharArray("", "functionStudyRationalNumerator");
	char* rationalDenominator = getDynamicCharArray("", "functionStudyRationalDenominator");
	T numeratorValue = (T)0, denominatorValue = (T)0, polynomialValue = (T)0;
	if (splitFunctionStudyRational<T>(expression, rationalNumerator, rationalDenominator) &&
		evaluateCanonicalPolynomial<T>(rationalNumerator, xValue, &numeratorValue) &&
		evaluateCanonicalPolynomial<T>(rationalDenominator, xValue, &denominatorValue)) {
		_delete(rationalNumerator, "functionStudyRationalNumerator"); rationalNumerator = nullptr;
		_delete(rationalDenominator, "functionStudyRationalDenominator"); rationalDenominator = nullptr;
		if (denominatorValue == 0) {
			return numeratorValue >= 0 ? (T)1E50 : (T)-1E50;
		}
		resultR = numeratorValue / denominatorValue;
		resultI = 0;
		return numeratorValue / denominatorValue;
	}
	if (evaluateCanonicalPolynomial<T>(expression, xValue, &polynomialValue)) {
		_delete(rationalNumerator, "functionStudyRationalNumerator"); rationalNumerator = nullptr;
		_delete(rationalDenominator, "functionStudyRationalDenominator"); rationalDenominator = nullptr;
		resultR = polynomialValue;
		resultI = 0;
		return polynomialValue;
	}
	_delete(rationalNumerator, "functionStudyRationalNumerator"); rationalNumerator = nullptr;
	_delete(rationalDenominator, "functionStudyRationalDenominator"); rationalDenominator = nullptr;
	T value = solveMath<T>(expression);
	resultR = value;
	return value;
}

template <typename T>
static T leadingPolynomialCoefficient(char* polynomial, int* degree) {
	*degree = 0;
	T lead = (T)0;
	char* source = getDynamicCharArray(polynomial, "functionStudyLeadingPolynomial");
	while (hasBalancedOuterParentheses(source)) {
		int len = abs((int)strlen(source));
		for (int i = 1; i < len - 1; i++) {
			source[i - 1] = source[i];
		}
		source[len - 2] = '\0';
	}
	int bestDegree = -1;
	int i = 0;
	while (i < abs((int)strlen(source))) {
		if (source[i] != '(') {
			i++;
			continue;
		}
		int start = i + 1;
		while (source[i] != '\0' && source[i] != ')') {
			i++;
		}
		if (source[i] == '\0') {
			break;
		}
		int end = i;
		char* coefficient = getDynamicCharArray("", "functionStudyLeadingCoefficient");
		int c = 0;
		for (int k = start; k < end; k++) {
			coefficient[c] = source[k] == '_' ? '-' : source[k];
			c++;
			if (source[k] == 'i') {
				break;
			}
		}
		coefficient[c] = '\0';
		for (int k = 0; k < abs((int)strlen(coefficient)); k++) {
			if (coefficient[k] == 'i') {
				coefficient[k] = '\0';
				break;
			}
		}
		int currentDegree = 0;
		i++;
		if (source[i] == 'x') {
			currentDegree = 1;
			i++;
			if (source[i] == '^') {
				i++;
				currentDegree = atoi(source + i);
				while (source[i] >= '0' && source[i] <= '9') {
					i++;
				}
			}
		}
		if (currentDegree > bestDegree) {
			bestDegree = currentDegree;
			lead = (T)atof(coefficient);
		}
		_delete(coefficient, "functionStudyLeadingCoefficient"); coefficient = nullptr;
	}
	_delete(source, "functionStudyLeadingPolynomial"); source = nullptr;
	if (bestDegree >= 0) {
		*degree = bestDegree;
	}
	return lead;
}

template <typename T>
static void parseFunctionStudyPolynomial(char* polynomial, T* coefficients, int* degree) {
	*degree = 0;
	for (int i = 0; i < DIMDOUBLE; i++) {
		coefficients[i] = (T)0;
	}
	char* source = getDynamicCharArray(polynomial, "functionStudyParsePolynomial");
	while (hasBalancedOuterParentheses(source)) {
		int len = abs((int)strlen(source));
		for (int i = 1; i < len - 1; i++) {
			source[i - 1] = source[i];
		}
		source[len - 2] = '\0';
	}
	int i = 0;
	while (i < abs((int)strlen(source))) {
		if (source[i] != '(') {
			i++;
			continue;
		}
		i++;
		char* coefficient = getDynamicCharArray("", "functionStudyParseCoefficient");
		int c = 0;
		while (source[i] != '\0' && source[i] != ')' && source[i] != '+') {
			coefficient[c] = source[i] == '_' ? '-' : source[i];
			c++;
			i++;
		}
		coefficient[c] = '\0';
		while (source[i] != '\0' && source[i] != ')') {
			i++;
		}
		if (source[i] == ')') {
			i++;
		}
		int exponent = 0;
		if (source[i] == 'x') {
			exponent = 1;
			i++;
			if (source[i] == '^') {
				i++;
				exponent = atoi(source + i);
				while (source[i] >= '0' && source[i] <= '9') {
					i++;
				}
			}
		}
		if (exponent >= 0 && exponent < DIMDOUBLE) {
			coefficients[exponent] += (T)atof(coefficient);
			if (exponent > *degree && coefficients[exponent] != 0) {
				*degree = exponent;
			}
		}
		_delete(coefficient, "functionStudyParseCoefficient"); coefficient = nullptr;
	}
	_delete(source, "functionStudyParsePolynomial"); source = nullptr;
}

template <typename T>
static void writeFunctionStudyPolynomial(T* coefficients, int degree, char* output) {
	sprintf(output, "");
	while (degree > 0 && abs(precisionDisplayDouble(coefficients[degree])) < 1E-10) {
		degree--;
	}
	for (int exponent = degree; exponent >= 0; exponent--) {
		double coefficient = precisionDisplayDouble(coefficients[exponent]);
		if (abs(coefficient) < 1E-10) {
			coefficient = 0.0;
		}
		char* coefficientText = getDynamicCharArray("", "functionStudyCoefficientText");
		sprintf(coefficientText, "%.12G", coefficient);
		for (int i = 0; i < abs((int)strlen(coefficientText)); i++) {
			if (coefficientText[i] == '-') {
				coefficientText[i] = '_';
			}
		}
		if (exponent > 0) {
			sprintf(output, "%s(%s+0i)x^%d", output, coefficientText, exponent);
		}
		else {
			sprintf(output, "%s(%s+0i)", output, coefficientText);
		}
		if (exponent > 0) {
			sprintf(output, "%s+", output);
		}
		_delete(coefficientText, "functionStudyCoefficientText"); coefficientText = nullptr;
	}
}

template <typename T>
static int derivativeFunctionStudyPolynomial(T* source, int sourceDegree, T* derivative) {
	for (int i = 0; i < DIMDOUBLE; i++) {
		derivative[i] = (T)0;
	}
	if (sourceDegree <= 0) {
		return 0;
	}
	for (int exponent = 1; exponent <= sourceDegree; exponent++) {
		derivative[exponent - 1] = source[exponent] * (T)exponent;
	}
	return sourceDegree - 1;
}

template <typename T>
static int multiplyFunctionStudyPolynomial(T* left, int leftDegree, T* right, int rightDegree, T* product) {
	for (int i = 0; i < DIMDOUBLE; i++) {
		product[i] = (T)0;
	}
	int degree = 0;
	for (int i = 0; i <= leftDegree; i++) {
		for (int j = 0; j <= rightDegree; j++) {
			if (i + j < DIMDOUBLE) {
				product[i + j] += left[i] * right[j];
				if (i + j > degree && product[i + j] != 0) {
					degree = i + j;
				}
			}
		}
	}
	return degree;
}

template <typename T>
static int subtractFunctionStudyPolynomial(T* left, int leftDegree, T* right, int rightDegree, T* difference) {
	for (int i = 0; i < DIMDOUBLE; i++) {
		difference[i] = (T)0;
	}
	int degree = leftDegree > rightDegree ? leftDegree : rightDegree;
	for (int i = 0; i <= degree; i++) {
		difference[i] = left[i] - right[i];
	}
	while (degree > 0 && abs(precisionDisplayDouble(difference[degree])) < 1E-10) {
		degree--;
	}
	return degree;
}

template <typename T>
static bool divideFunctionStudyPolynomial(T* dividend, int dividendDegree, T* divisor, int divisorDegree, T* quotient, int* quotientDegree) {
	for (int i = 0; i < DIMDOUBLE; i++) {
		quotient[i] = (T)0;
	}
	*quotientDegree = 0;
	if (divisorDegree < 0 || abs(precisionDisplayDouble(divisor[divisorDegree])) < 1E-10 || dividendDegree < divisorDegree) {
		return false;
	}
	T* remainder = getDynamicArray<T>(DIMDOUBLE);
	for (int i = 0; i <= dividendDegree; i++) {
		remainder[i] = dividend[i];
	}
	for (int degree = dividendDegree; degree >= divisorDegree; degree--) {
		T factor = remainder[degree] / divisor[divisorDegree];
		int quotientIndex = degree - divisorDegree;
		quotient[quotientIndex] = factor;
		if (quotientIndex > *quotientDegree && abs(precisionDisplayDouble(factor)) >= 1E-10) {
			*quotientDegree = quotientIndex;
		}
		for (int i = 0; i <= divisorDegree; i++) {
			remainder[quotientIndex + i] -= factor * divisor[i];
		}
	}
	bool exact = true;
	for (int i = 0; i <= dividendDegree; i++) {
		if (abs(precisionDisplayDouble(remainder[i])) > 1E-7) {
			exact = false;
			break;
		}
	}
	while (*quotientDegree > 0 && abs(precisionDisplayDouble(quotient[*quotientDegree])) < 1E-10) {
		(*quotientDegree)--;
	}
	_delete(remainder, "functionStudyPolynomialRemainder"); remainder = nullptr;
	return exact;
}

template <typename T>
static bool getSingleLinearRoot(char* polynomial, T* root) {
	T* coefficients = getDynamicArray<T>(DIMDOUBLE);
	int degree = 0;
	parseFunctionStudyPolynomial<T>(polynomial, coefficients, &degree);
	bool hasRoot = false;
	if (degree == 1 && coefficients[1] != 0) {
		*root = normalizeFunctionStudyValue<T>((T)0 - coefficients[0] / coefficients[1]);
		hasRoot = true;
	}
	_delete(coefficients, "functionStudyLinearRootCoefficients"); coefficients = nullptr;
	return hasRoot;
}

template <typename T>
static bool parseFunctionStudyRootValue(char* value, T* realRoot, T* imaginaryRoot) {
	if (value == nullptr || abs((int)strlen(value)) == 0) {
		return false;
	}
	if (isContained("i", value)) {
		return false;
	}
	char* valueToSolve = getDynamicCharArray(value, "functionStudyRootValue");
	for (int i = 0; i < abs((int)strlen(valueToSolve)); i++) {
		if (valueToSolve[i] == '-') {
			valueToSolve[i] = '_';
		}
	}
	solveMath<T>(valueToSolve);
	*realRoot = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR));
	*imaginaryRoot = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
	_delete(valueToSolve, "functionStudyRootValue"); valueToSolve = nullptr;
	return abs(precisionDisplayDouble(*imaginaryRoot)) < 1E-9;
}

template <typename T>
static bool numeratorIsZeroAtRoot(char* numerator, T root) {
	if (numerator == nullptr || abs((int)strlen(numerator)) == 0) {
		return false;
	}
	T value = (T)0;
	if (!evaluateCanonicalPolynomial<T>(numerator, root, &value)) {
		return false;
	}
	return abs(precisionDisplayDouble(value)) < 1E-7;
}

template <typename T>
static void reduceFunctionStudyRationalByFactor(char* numerator, char* denominator, char* factor) {
	T* numeratorCoefficients = getDynamicArray<T>(DIMDOUBLE);
	T* denominatorCoefficients = getDynamicArray<T>(DIMDOUBLE);
	T* factorCoefficients = getDynamicArray<T>(DIMDOUBLE);
	T* reducedNumerator = getDynamicArray<T>(DIMDOUBLE);
	T* reducedDenominator = getDynamicArray<T>(DIMDOUBLE);
	int numeratorDegree = 0, denominatorDegree = 0, factorDegree = 0;
	int reducedNumeratorDegree = 0, reducedDenominatorDegree = 0;
	parseFunctionStudyPolynomial<T>(numerator, numeratorCoefficients, &numeratorDegree);
	parseFunctionStudyPolynomial<T>(denominator, denominatorCoefficients, &denominatorDegree);
	parseFunctionStudyPolynomial<T>(factor, factorCoefficients, &factorDegree);
	bool numeratorDivides = divideFunctionStudyPolynomial<T>(numeratorCoefficients, numeratorDegree, factorCoefficients, factorDegree, reducedNumerator, &reducedNumeratorDegree);
	bool denominatorDivides = divideFunctionStudyPolynomial<T>(denominatorCoefficients, denominatorDegree, factorCoefficients, factorDegree, reducedDenominator, &reducedDenominatorDegree);
	if (numeratorDivides && denominatorDivides) {
		writeFunctionStudyPolynomial<T>(reducedNumerator, reducedNumeratorDegree, numerator);
		writeFunctionStudyPolynomial<T>(reducedDenominator, reducedDenominatorDegree, denominator);
	}
	_delete(numeratorCoefficients, "functionStudyReduceNumerator"); numeratorCoefficients = nullptr;
	_delete(denominatorCoefficients, "functionStudyReduceDenominator"); denominatorCoefficients = nullptr;
	_delete(factorCoefficients, "functionStudyReduceFactor"); factorCoefficients = nullptr;
	_delete(reducedNumerator, "functionStudyReducedNumerator"); reducedNumerator = nullptr;
	_delete(reducedDenominator, "functionStudyReducedDenominator"); reducedDenominator = nullptr;
}

template <typename T>
static void buildFunctionStudyRationalDerivative(char* numerator, char* denominator, char* derivativeNumerator, char* derivativeDenominator) {
	T* numeratorCoefficients = getDynamicArray<T>(DIMDOUBLE);
	T* denominatorCoefficients = getDynamicArray<T>(DIMDOUBLE);
	T* numeratorDerivative = getDynamicArray<T>(DIMDOUBLE);
	T* denominatorDerivative = getDynamicArray<T>(DIMDOUBLE);
	T* leftProduct = getDynamicArray<T>(DIMDOUBLE);
	T* rightProduct = getDynamicArray<T>(DIMDOUBLE);
	T* quotientNumerator = getDynamicArray<T>(DIMDOUBLE);
	T* quotientDenominator = getDynamicArray<T>(DIMDOUBLE);
	int numeratorDegree = 0, denominatorDegree = 0;
	parseFunctionStudyPolynomial<T>(numerator, numeratorCoefficients, &numeratorDegree);
	parseFunctionStudyPolynomial<T>(denominator, denominatorCoefficients, &denominatorDegree);
	int numeratorDerivativeDegree = derivativeFunctionStudyPolynomial<T>(numeratorCoefficients, numeratorDegree, numeratorDerivative);
	int denominatorDerivativeDegree = derivativeFunctionStudyPolynomial<T>(denominatorCoefficients, denominatorDegree, denominatorDerivative);
	int leftProductDegree = multiplyFunctionStudyPolynomial<T>(numeratorDerivative, numeratorDerivativeDegree, denominatorCoefficients, denominatorDegree, leftProduct);
	int rightProductDegree = multiplyFunctionStudyPolynomial<T>(numeratorCoefficients, numeratorDegree, denominatorDerivative, denominatorDerivativeDegree, rightProduct);
	int quotientNumeratorDegree = subtractFunctionStudyPolynomial<T>(leftProduct, leftProductDegree, rightProduct, rightProductDegree, quotientNumerator);
	int quotientDenominatorDegree = multiplyFunctionStudyPolynomial<T>(denominatorCoefficients, denominatorDegree, denominatorCoefficients, denominatorDegree, quotientDenominator);
	writeFunctionStudyPolynomial<T>(quotientNumerator, quotientNumeratorDegree, derivativeNumerator);
	writeFunctionStudyPolynomial<T>(quotientDenominator, quotientDenominatorDegree, derivativeDenominator);
	_delete(numeratorCoefficients, "functionStudyNumeratorCoefficients"); numeratorCoefficients = nullptr;
	_delete(denominatorCoefficients, "functionStudyDenominatorCoefficients"); denominatorCoefficients = nullptr;
	_delete(numeratorDerivative, "functionStudyNumeratorDerivative"); numeratorDerivative = nullptr;
	_delete(denominatorDerivative, "functionStudyDenominatorDerivative"); denominatorDerivative = nullptr;
	_delete(leftProduct, "functionStudyLeftProduct"); leftProduct = nullptr;
	_delete(rightProduct, "functionStudyRightProduct"); rightProduct = nullptr;
	_delete(quotientNumerator, "functionStudyQuotientNumerator"); quotientNumerator = nullptr;
	_delete(quotientDenominator, "functionStudyQuotientDenominator"); quotientDenominator = nullptr;
}

template <typename T>
void functionStudy(char* function) {
	sprintf(roots, "");
	ansRV = 0;
	ansIV = 0;
	processVariable<T>("x");
	T saveXR = precisionValueTo<T>(resultR), saveXI = precisionValueTo<T>(resultI);
	replaceTimes = 0;
	if (isContained("(x)", function)) {
		replace("(x)", "x", function);
		sprintf(function, "%s", expressionF);
	}
	if (countOccurrences("/", function) > 1) {
		puts("\nError: Simplify your fractions first. You only can insert a fraction (a numerator divided by a denominator).\n");
	}
	else {
		studyFunction = true;
		T* coDomain = getDynamicArray<T>(DIMDOUBLE);
		int u = 0;
		char* saveFunctionF = getDynamicCharArray(function, "saveFunctionF");
		char* originalFunction = getDynamicCharArray("", "originalFunction");
		sprintf(originalFunction, "%s", function);
		T* poleZerosR = getDynamicArray<T>(DIMDOUBLE); T* poleZerosI = getDynamicArray<T>(DIMDOUBLE);
		T intersectYY = 0, horizontalAssimptote = 0;
		int pl = 0;
		T* zeroR = getDynamicArray<T>(DIMDOUBLE); T* zeroI = getDynamicArray<T>(DIMDOUBLE);
		char* numerator = getDynamicCharArray("", "numerator"); char* denominator = getDynamicCharArray("", "denominator");
		if (isContained("/", saveFunctionF)) {
			int g = 0;
			while (saveFunctionF[g] != '/') {
				numerator[g] = saveFunctionF[g];
				g++;
			}
			numerator[g] = '\0';
			int h = strStart + 2;
			g = 0;
			while (h < abs((int)strlen(saveFunctionF))) {
				denominator[g] = saveFunctionF[h];
				g++;
				h++;
			}
			denominator[g] = '\0';
			if (isContained("((", numerator) && !dataVerifier<T>(numerator, 0, 0, 0, 1)) {
				replace("((", "(", numerator);
				sprintf(numerator, "%s", expressionF);
			}
			if (isContained("))", numerator) && !dataVerifier<T>(numerator, 0, 0, 0, 1)) {
				replace("))", ")", numerator);
				sprintf(numerator, "%s", expressionF);
			}
			if (isContained("(((", numerator) && !dataVerifier<T>(numerator, 0, 0, 0, 1)) {
				replace("(((", "((", numerator);
				sprintf(numerator, "%s", expressionF);
			}
			if (isContained(")))", numerator) && !dataVerifier<T>(numerator, 0, 0, 0, 1)) {
				replace(")))", "))", numerator);
				sprintf(numerator, "%s", expressionF);
			}
			if (isContained("(((", denominator) && !dataVerifier<T>(denominator, 0, 0, 0, 1)) {
				replace("(((", "((", denominator);
				sprintf(denominator, "%s", expressionF);
			}
			if (isContained(")))", denominator) && !dataVerifier<T>(denominator, 0, 0, 0, 1)) {
				replace(")))", "))", denominator);
				sprintf(denominator, "%s", expressionF);
			}
			sprintf(saveFunctionF, "(%s)/(%s)", numerator, denominator);
			if (isContained("((", saveFunctionF) && !dataVerifier<T>(saveFunctionF, 0, 0, 0, 1)) {
				replace("((", "(", saveFunctionF);
				sprintf(saveFunctionF, "%s", expressionF);
			}
			if (isContained("))", saveFunctionF) && !dataVerifier<T>(saveFunctionF, 0, 0, 0, 1)) {
				replace("))", ")", saveFunctionF);
				sprintf(saveFunctionF, "%s", expressionF);
			}

			if (!buildCanonicalFromSimplePolynomial<T>(numerator, expressionF)) {
				normalizeFunctionStudyPolynomial(numerator);
				sprintf(expressionF, "(%s)*(0x^1+1)", numerator);
				sprintf(numerator, "%s", expressionF);
				simpleSimplifyPolynomial<T>(numerator);
			}
			sprintf(numerator, "%s", expressionF);
			if (!buildCanonicalFromSimplePolynomial<T>(denominator, expressionF)) {
				normalizeFunctionStudyPolynomial(denominator);
				sprintf(expressionF, "(%s)*(0x^1+1)", denominator);
				sprintf(denominator, "%s", expressionF);
				simpleSimplifyPolynomial<T>(denominator);
			}
			sprintf(denominator, "%s", expressionF);
			sprintf(originalFunction, "%s/%s", numerator, denominator);
		}
		else {
			if (!buildCanonicalFromSimplePolynomial<T>(saveFunctionF, expressionF)) {
				normalizeFunctionStudyPolynomial(saveFunctionF);
				sprintf(expressionF, "(%s)*(0x^1+1)", saveFunctionF);
				sprintf(saveFunctionF, "%s", expressionF);
				simpleSimplifyPolynomial<T>(saveFunctionF);
			}
			sprintf(saveFunctionF, "%s", expressionF);
			sprintf(originalFunction, "%s", saveFunctionF);
		}

		if (abs((int)strlen(denominator)) > 0) {
			equationSolver<T>(denominator);
			puts("\n==> Domain <==\n");
			printf("\nDf=R");
			int i = 0, j = 0, z = 0;
			char* value = getDynamicCharArray("", "value");
			replaceTimes = 0;
			char* saveExpF = getDynamicCharArray("", "saveExpF");
			sprintf(saveExpF, "%s", expressionF);
			bool printedDomainHeader = false;
			while (isContained("=", saveExpF)) {
				j = 0;
				i = strEnd;
				saveExpF[strStart] = ' ';
				while (i < abs((int)strlen(saveExpF)) && saveExpF[i] != '\n') {
					value[j] = saveExpF[i];
					i++; j++;
				}
				value[j] = '\0';
				T rootR = (T)0, rootI = (T)0;
				if (parseFunctionStudyRootValue<T>(value, &rootR, &rootI)) {
					if (!printedDomainHeader) {
						printf("\\{");
						printedDomainHeader = true;
					}
					else {
						printf(",");
					}
					printf("%s", value);
					zeroR[z] = rootR; zeroI[z] = rootI;
					poleZerosR[pl] = rootR; poleZerosI[pl] = rootI;
					pl++;
					z++;
				}
			}
			if (printedDomainHeader) {
				printf("}\n");
			}
			else {
				printf("\n");
			}
			_delete(saveExpF, "saveExpF"); saveExpF = nullptr;
			_delete(value, "value"); value = nullptr;
		}
		char* saveFunction = getDynamicCharArray("", "saveFunction");
		if (abs((int)strlen(numerator)) > 0) {
			sprintf(saveFunction, "%s", numerator);
		}
		else {
			sprintf(saveFunction, "%s", saveFunctionF);
		}

		printf("\n==> Zeros and intersection with yy-axis <==\n");
		puts("\nIt intersects the xx-axis in the points below:");
		int i = 0, j = 0, z = 0;
		char* value = getDynamicCharArray("", "value");
		replaceTimes = 0;
		char* saveExpF = getDynamicCharArray("", "saveExpF");
		T linearRoot = (T)0;
		if (getSingleLinearRoot<T>(saveFunction, &linearRoot)) {
			zeroR[z] = linearRoot; zeroI[z] = (T)0;
			poleZerosR[pl] = linearRoot; poleZerosI[pl] = (T)0;
			printf("\n(%.3G,0)", precisionDisplayDouble(linearRoot));
			pl++;
			z++;
		}
		else {
			equationSolver<T>(saveFunction);
			sprintf(saveExpF, "%s", expressionF);
		}
		while (abs((int)strlen(saveExpF)) > 0 && isContained("=", saveExpF)) {
			j = 0;
			i = strEnd;
			saveExpF[strStart] = ' ';
			while (i < abs((int)strlen(saveExpF)) && saveExpF[i] != '\n') {
				value[j] = saveExpF[i];
				i++; j++;
			}
			value[j] = '\0';
			if (isContained("-", value)) {
				replace("-", "_", value);
				sprintf(value, "%s", expressionF);
			}
			solveMath<T>(value);
			zeroR[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR)); zeroI[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
			printf("\n(%.3G,0)", precisionDisplayDouble(zeroR[z]));
			poleZerosR[pl] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR)); poleZerosI[pl] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
			pl++;
			z++;
		}
		T* sortZeroR = getDynamicArray<T>(DIMDOUBLE); T* sortZeroI = getDynamicArray<T>(DIMDOUBLE);
		T theSmallerR, theSmallerI = 0;
		int  saveZ = z;
		int o = 0, saveIndex = -1;
		while (o < saveZ) {
			theSmallerR = 1E12;
			theSmallerI = 0;
			saveIndex = -1;
			for (z = 0; z < saveZ; z++) {
				if (theSmallerR > zeroR[z]) {
					theSmallerR = zeroR[z];
					theSmallerI = zeroI[z];
					saveIndex = z;
				}
			}
			if (saveIndex < 0 || theSmallerR == 1E12) {
				break;
			}
			zeroR[saveIndex] = 1E12;
			zeroI[saveIndex] = 0;
			sortZeroR[o] = theSmallerR;
			sortZeroI[o] = theSmallerI;
			o++;
		}
		T saveResultR, saveResultI;
		processVariable<T>("x");
		saveResultR = precisionValueTo<T>(resultR); saveResultI = precisionValueTo<T>(resultI);
		resultR = 0; resultI = 0;
		sprintf(expressionF, "");
		variableController("x");
		solveFunctionStudyExpression<T>(originalFunction);
		resultR = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR));
		puts("\n\nIt intersects the yy-axis in the point below:\n");
		printf("\n(0,%.3f)\n", precisionDisplayDouble(resultR));
		intersectYY = precisionValueTo<T>(resultR);
		coDomain[u] = intersectYY;
		u++;
		printf("\n==> Asymptotes <==\n");
		char* verticalAsymptotes = getDynamicCharArray("", "verticalAsymptotes");
		if (abs((int)strlen(denominator)) > 0) {
			equationSolver<T>(denominator);
			int i = 0, j = 0, z = 0;
			char* value = getDynamicCharArray("", "value");
			replaceTimes = 0;
			char* saveExpF = getDynamicCharArray("", "saveExpF");
			sprintf(saveExpF, "%s", expressionF);
			bool printedVerticalAsymptotes = false;
			while (isContained("=", saveExpF)) {
				j = 0;
				i = strEnd;
				saveExpF[strStart] = ' ';
				while (i < abs((int)strlen(saveExpF)) && saveExpF[i] != '\n') {
					value[j] = saveExpF[i];
					i++; j++;
				}
				value[j] = '\0';
				T rootR = (T)0, rootI = (T)0;
				if (parseFunctionStudyRootValue<T>(value, &rootR, &rootI) && !numeratorIsZeroAtRoot<T>(numerator, rootR)) {
					if (!printedVerticalAsymptotes) {
						puts("\nHas as vertical asymptotes the lines below:");
						printedVerticalAsymptotes = true;
					}
					printf("\nx=%s", value);
					zeroR[z] = rootR; zeroI[z] = rootI;
					z++;
				}
			}
			if (printedVerticalAsymptotes) {
				printf("\n");
			}
			else {
				puts("\nIt does not have vertical asymptotes.");
			}
			_delete(saveExpF, "saveExpF"); saveExpF = nullptr;
			_delete(value, "value"); value = nullptr;
		}
		processVariable<T>("x");
		saveResultR = precisionValueTo<T>(resultR); saveResultI = precisionValueTo<T>(resultI);
		char* valueF = getDynamicCharArray("", "valueF");
		bool horizontalAsymptoteFound = false;
		if (abs((int)strlen(denominator)) > 0) {
			int numeratorDegree = 0, denominatorDegree = 0;
			T numeratorLead = leadingPolynomialCoefficient<T>(numerator, &numeratorDegree);
			T denominatorLead = leadingPolynomialCoefficient<T>(denominator, &denominatorDegree);
			if (denominatorLead != 0 && numeratorDegree <= denominatorDegree) {
				horizontalAssimptote = numeratorDegree < denominatorDegree ? (T)0 : numeratorLead / denominatorLead;
				resultR = horizontalAssimptote;
				resultI = 0;
				horizontalAsymptoteFound = true;
			}
		}
		if (!horizontalAsymptoteFound) {
			resultR = 1E50; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			solveFunctionStudyExpression<T>(originalFunction);
			sprintf(valueF, "%.3f", precisionDisplayDouble(resultR));
			if (isContained("-", valueF)) {
				replace("-", "_", valueF);
				sprintf(valueF, "%s", expressionF);
			}
			solveMath<T>(valueF);
		}
		if (horizontalAsymptoteFound || abs(precisionValueTo<T>(resultR)) < 1E50) {
			printf("\nHas a horizontal asymptote when lim x-> +inf: %.3f\n", precisionDisplayDouble(resultR));
			horizontalAssimptote = precisionValueTo<T>(resultR);
			coDomain[u] = horizontalAssimptote;
			u++;
		}
		else {
			puts("\nIt does not have a horizontal asymptote when lim x-> +inf");
		}
		if (!horizontalAsymptoteFound) {
			resultR = -1E50; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			solveFunctionStudyExpression<T>(originalFunction);
			sprintf(valueF, "%.3f", precisionDisplayDouble(resultR));
			if (isContained("-", valueF)) {
				replace("-", "_", valueF);
				sprintf(valueF, "%s", expressionF);
			}
			solveMath<T>(valueF);
		}
		if (horizontalAsymptoteFound || abs(precisionValueTo<T>(resultR)) < 1E50) {
			printf("\nHas a horizontal asymptote when lim x-> -inf: %.3f\n", precisionDisplayDouble(resultR));
			horizontalAssimptote = precisionValueTo<T>(resultR);
		}
		else {
			puts("\nIt does not have a horizontal asymptote when lim x-> -inf");
		}
		printf("\n==> Symmetries <==\n");
		char* saveDenominator = getDynamicCharArray("", "saveDenominator");
		sprintf(saveDenominator, "%s", denominator);
		T*  minusfx = getDynamicArray<T>(DIMDOUBLE); T* fxminusx = getDynamicArray<T>(DIMDOUBLE); T* fx = getDynamicArray<T>(DIMDOUBLE);
		int y = 0, p = 0;
		while (y < 10000) {
			T sampleX = (T)(y - 5000);
			resultR = sampleX;
			resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			fx[p] = solveFunctionStudyExpression<T>(originalFunction);
			resultR = -sampleX;
			resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			fxminusx[p] = solveFunctionStudyExpression<T>(originalFunction);
			minusfx[p] = fx[p] * -1;
			y = y + 1000;
			p++;
		}
		y = 0;
		int yy = 0;
		p = 0;
		while (y < 10000) {
			if (sameFunctionStudyValue<T>(fxminusx[p], fx[p])) {
				while (sameFunctionStudyValue<T>(fxminusx[p], fx[p]) && y < 10000) {
					yy = yy + 1000; y = y + 1000;
					p++;
				}
			}
			else {
				y = y + 1000;
				p++;
			}
		}
		int neitherEvenAndOdd = 0;
		if (yy == 10000) {
			puts("\nThe function is even.");
		}
		else {
			neitherEvenAndOdd++;
			puts("\nThe function is not even.");
		}
		yy = 0;
		y = 0;
		p = 0;
		while (y < 10000) {
			if (sameFunctionStudyValue<T>(fxminusx[p], minusfx[p])) {
				while (sameFunctionStudyValue<T>(fxminusx[p], minusfx[p]) && y < 10000) {
					yy = yy + 1000; y = y + 1000;
					p++;
				}
			}
			else {
				y = y + 1000;
				p++;
			}
		}
		if (yy == 10000) {
			puts("\nThe function is odd.");
		}
		else {
			neitherEvenAndOdd++;
			puts("\nThe function is not odd.");
		}
		if (neitherEvenAndOdd == 2) {
			puts("\nThere is no symmetry of the graph with respect to the yy axis or the origin.");
		}
		sprintf(denominator, "%s", saveDenominator);
		printf("\n==> Function signal <==\n\n");
		if (abs((int)strlen(numerator)) == 0 && abs((int)strlen(denominator)) == 0) {
			z = 0;
			char* yLessThanZero = getDynamicCharArray("", "yLessThanZero"); char*  yMoreThanZero = getDynamicCharArray("", "yMoreThanZero");
			resultR = -1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			T negativeMax = solveFunctionStudyExpression<T>(saveFunction);
			resultR = 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			T positiveMax = solveFunctionStudyExpression<T>(saveFunction);
			if (negativeMax < 0 && positiveMax < 0) {
				sprintf(yLessThanZero, "%s\n f(x) < 0 if x E ]-inf,%.3f[ U", yLessThanZero, sortZeroR[0]);
				sprintf(yMoreThanZero, "%s f(x) > 0 if x E", yMoreThanZero);
				while (z + 1 < saveZ) {
					if (z + 3 < saveZ) {
						if (z % 2 == 0) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ U", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ U", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
					else {
						if (z % 2 == 0) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ ", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ ", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
				}
				if (yLessThanZero[abs((int)strlen(yLessThanZero)) - 1] == 'U') {
					sprintf(yLessThanZero, "%s ]%.3f,+inf[\n", yLessThanZero, sortZeroR[saveZ - 1]);
				}
				else {
					sprintf(yLessThanZero, "%sU ]%.3f,+inf[\n", yLessThanZero, sortZeroR[saveZ - 1]);
				}
				puts(yLessThanZero);
				puts(yMoreThanZero);
			}
			if (negativeMax > 0 && positiveMax > 0) {
				sprintf(yMoreThanZero, "%s\n f(x) > 0 if x E ]-inf,%.3f[ U", yMoreThanZero, sortZeroR[0]);
				sprintf(yLessThanZero, "%s f(x) < 0 if x E", yLessThanZero);
				while (z + 1 < saveZ) {
					if (z + 3 < saveZ) {
						if (z % 2 == 1) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ U", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ U", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
					else {
						if (z % 2 == 1) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ ", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ ", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
				}
				if (yMoreThanZero[abs((int)strlen(yMoreThanZero)) - 1] == 'U') {
					sprintf(yMoreThanZero, "%s ]%.3f,+inf[\n", yMoreThanZero, sortZeroR[saveZ - 1]);
				}
				else {
					sprintf(yMoreThanZero, "%sU ]%.3f,+inf[\n", yMoreThanZero, sortZeroR[saveZ - 1]);
				}
				puts(yLessThanZero);
				puts(yMoreThanZero);
			}
			if (negativeMax > 0 && positiveMax < 0) {
				sprintf(yMoreThanZero, "%s\n f(x) > 0 if x E ]-inf,%.3f[ U", yMoreThanZero, sortZeroR[0]);
				sprintf(yLessThanZero, "%s f(x) < 0 if x E", yLessThanZero);
				while (z + 1 < saveZ) {
					if (z + 3 < saveZ) {
						if (z % 2 == 1) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ U", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ U", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
					else {
						if (z % 2 == 1) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ ", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ ", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
				}
				if (yLessThanZero[abs((int)strlen(yLessThanZero)) - 1] == 'U') {
					sprintf(yLessThanZero, "%s ]%.3f,+inf[\n", yLessThanZero, sortZeroR[saveZ - 1]);
				}
				else {
					sprintf(yLessThanZero, "%sU ]%.3f,+inf[\n", yLessThanZero, sortZeroR[saveZ - 1]);
				}
				puts(yLessThanZero);
				puts(yMoreThanZero);
			}
			if (negativeMax < 0 && positiveMax> 0) {
				sprintf(yLessThanZero, "%s\n f(x) < 0 if x E ]-inf,%.3f[ U", yLessThanZero, sortZeroR[0]);
				sprintf(yMoreThanZero, "%s f(x) > 0 if x E", yMoreThanZero);
				while (z + 1 < saveZ) {
					if (z + 3 < saveZ) {
						if (z % 2 == 0) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ U", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ U", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
					else {
						if (z % 2 == 0) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ ", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ ", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
				}
				if (yMoreThanZero[abs((int)strlen(yMoreThanZero)) - 1] == 'U') {
					sprintf(yMoreThanZero, "%s ]%.3f,+inf[\n", yMoreThanZero, sortZeroR[saveZ - 1]);
				}
				else {
					sprintf(yMoreThanZero, "%sU ]%.3f,+inf[\n", yMoreThanZero, sortZeroR[saveZ - 1]);
				}
				puts(yLessThanZero);
				puts(yMoreThanZero);
			}
			_delete(yLessThanZero, "yLessThanZero");
			yLessThanZero = nullptr;
			_delete(yMoreThanZero, "yMoreThanZero");
			yMoreThanZero = nullptr;
		}
		else {
			T theSmallerR, theSmallerI = 0;
			int  saveZ = pl;
			int o = 0, saveIndex = -1;
			while (o < saveZ) {
				theSmallerR = 1E12;
				theSmallerI = 0;
				saveIndex = -1;
				for (z = 0; z < saveZ; z++) {
					if (theSmallerR > poleZerosR[z]) {
						theSmallerR = poleZerosR[z];
						theSmallerI = poleZerosI[z];
						saveIndex = z;
					}
				}
				if (saveIndex < 0 || theSmallerR == 1E12) {
					break;
				}
				poleZerosR[saveIndex] = 1E12;
				poleZerosI[saveIndex] = 0;
				sortZeroR[o] = theSmallerR;
				sortZeroI[o] = theSmallerI;
				o++;
			}

			char* displayNumerator = getDynamicCharArray(numerator, "displayNumerator");
			char* displayDenominator = getDynamicCharArray(denominator, "displayDenominator");
			removeTriplPars(displayNumerator);
			sprintf(displayNumerator, "%s", expressionF);
			removeDuplPars(displayNumerator);
			sprintf(displayNumerator, "%s", expressionF);
			printf("\nNumerator-> %s\n", displayNumerator);
			printf("\nDenominator-> %s\n", displayDenominator);
			_delete(displayNumerator, "displayNumerator"); displayNumerator = nullptr;
			_delete(displayDenominator, "displayDenominator"); displayDenominator = nullptr;
			printf("\nx\t\t-inf\t");
			o = 0;
			while (o < saveZ) {
				if (o < saveZ - 1) {
					printf("%.3f\t\t", sortZeroR[o]);
				}
				else {
					printf("%.3f\t", sortZeroR[o]);
				}
				o++;
			}
			printf("+inf\n");
			printf("\nNumerator\t");
			resultR = sortZeroR[0] - 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			solveFunctionStudyExpression<T>(numerator);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				sprintf(expressionF, "");
				variableController("x");
				solveFunctionStudyExpression<T>(numerator);
				if (abs(precisionValueTo<T>(resultR)) < 0.1) {
					printf("0\t");
				}
				else {
					if (resultR > 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
				}
				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					sprintf(expressionF, "");
					variableController("x");
					solveFunctionStudyExpression<T>(numerator);
					if (resultR > 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
					y++;
				}
			}
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			solveFunctionStudyExpression<T>(numerator);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			printf("\nDenominator\t");
			resultR = sortZeroR[0] - 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			solveFunctionStudyExpression<T>(denominator);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				sprintf(expressionF, "");
				variableController("x");
				solveFunctionStudyExpression<T>(denominator);
				if (abs(precisionValueTo<T>(resultR)) < 0.1) {
					printf("0\t");
				}
				else {
					if (resultR > 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
				}
				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					sprintf(expressionF, "");
					variableController("x");
					solveFunctionStudyExpression<T>(denominator);
					if (resultR > 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
					y++;
				}
			}
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			variableController("x");
			solveFunctionStudyExpression<T>(denominator);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			printf("\nf(x)\t\t");
			resultR = sortZeroR[0] - 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			resultR = solveFunctionStudyExpression<T>(numerator) / solveFunctionStudyExpression<T>(denominator);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			y = 0;
			o = 0;
			char* expre = getDynamicCharArray("", "expre");
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				sprintf(expressionF, "");
				variableController("x");
				resultR = solveFunctionStudyExpression<T>(numerator) / solveFunctionStudyExpression<T>(denominator);
				if (abs(precisionValueTo<T>(resultR)) > 1E4 || abs(precisionValueTo<T>(resultI)) > 1E4) {
					resultR = pot<T>((T)10, (T)400, 1);
					printf("%.2f\t", precisionDisplayDouble(resultR));
				}
				else {

					sprintf(expre, "%.2f\t", precisionDisplayDouble(resultR));
					if (isContained("ind", expre)) {
						printf("ind\t");
					}
					else {
						printf("%s", expre);
					}

				}

				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					sprintf(expressionF, "");
					variableController("x");
					resultR = solveFunctionStudyExpression<T>(numerator) / solveFunctionStudyExpression<T>(denominator);
					if (resultR > 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
					y++;
				}
			}
			_delete(expre, "expre");
			expre = nullptr;
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			resultR = solveFunctionStudyExpression<T>(numerator) / solveFunctionStudyExpression<T>(denominator);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
		}
		puts(" ");
		printf("\n==> Monotony interval and relative extremes <==\n");
		char* new_derivate = getDynamicCharArray("", "new_derivate");
		char* new_numerator = getDynamicCharArray("", "new_numerator");
		char* new_denominator = getDynamicCharArray("", "new_denominator");
		if (abs((int)strlen(numerator)) == 0 && abs((int)strlen(denominator)) == 0) {
			removeTriplPars(saveFunction);
			printf("\nf(x)=%s\n", expressionF);
			char* derivate = getDerivative<T>(saveFunction);
			printf("\nf'(x)=%s\n", derivate);
			printf("\nx\t-inf\t");
			replaceTimes = 0;
			char* data = getDynamicCharArray("", "data");
			sprintf(data, "%s", derivate);
			z = 0;
			T derivativeLinearRoot = (T)0;
			if (getSingleLinearRoot<T>(data, &derivativeLinearRoot)) {
				zeroR[z] = normalizeFunctionStudyValue<T>(derivativeLinearRoot);
				zeroI[z] = (T)0;
				z++;
			}
			else {
				equationSolver<T>(data);
				sprintf(saveExpF, "%s", expressionF);
				while (isContained("=", saveExpF)) {
					j = 0;
					i = strEnd;
					saveExpF[strStart] = ' ';
					while (i < abs((int)strlen(saveExpF)) && saveExpF[i] != '\n') {
						value[j] = saveExpF[i];
						i++; j++;
					}
					value[j] = '\0';
					if (isContained("-", value)) {
						replace("-", "_", value);
						sprintf(value, "%s", expressionF);
					}
					solveMath<T>(value);
					zeroR[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR)); zeroI[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
					z++;
				}
			}
			saveZ = z;
			o = 0; saveIndex = -1;
			while (o < saveZ) {
				theSmallerR = 1E12;
				theSmallerI = 0;
				saveIndex = -1;
				for (z = 0; z < saveZ; z++) {
					if (theSmallerR > zeroR[z]) {
						theSmallerR = zeroR[z];
						theSmallerI = zeroI[z];
						saveIndex = z;
					}
				}
				if (saveIndex < 0 || theSmallerR == 1E12) {
					break;
				}
				zeroR[saveIndex] = 1E12;
				zeroI[saveIndex] = 0;
				sortZeroR[o] = theSmallerR;
				sortZeroI[o] = theSmallerI;
				o++;
			}
			o = 0;
			y = 0;
			while (o < saveZ) {
				printf("%.3f\t", sortZeroR[o]);
				o++;
				y++;
				if (o < saveZ) {
					printf("\t");
					y++;
				}
			}
			printf("+inf\n");
			printf("\nf'(x)\t");
			resultR = sortZeroR[0] - 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			solveFunctionStudyExpression<T>(data);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				printf("0\t");
				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					sprintf(expressionF, "");
					variableController("x");
					solveFunctionStudyExpression<T>(data);
					if (resultR > 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
					y++;
				}
			}
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			solveFunctionStudyExpression<T>(data);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			printf("\nf(x)\t");
			resultR = sortZeroR[0] - 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			solveFunctionStudyExpression<T>(data);
			if (resultR > 0) {
				printf("/^\t");
			}
			else {
				printf("\\v\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				sprintf(expressionF, "");
				variableController("x");
				solveFunctionStudyExpression<T>(saveFunction);
				printf("%.3f\t", precisionDisplayDouble(resultR));
				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					sprintf(expressionF, "");
					variableController("x");
					solveFunctionStudyExpression<T>(data);
					if (resultR > 0) {
						printf("/^\t");
					}
					else {
						printf("\\v\t");
					}
					y++;
				}
			}
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			solveFunctionStudyExpression<T>(data);
			if (resultR > 0) {
				printf("/^\t");
			}
			else {
				printf("\\v\t");
			}
			o = 0;
			puts(" ");
			printf("\n==> Direction of concavity and inflection points <==\n");
			printf("\nf'(x)=%s\n", data);
			derivate = getDerivative<T>(data);
			printf("\nf''(x)=%s\n", derivate);
			if (!isContained("x", derivate)) {
				if (isContained("_", derivate)) {
					puts("\nThe function has no inflection points and the concavity is always facing down.\n");
				}
				else {
					puts("\nThe function has no inflection points and the concavity is always facing up.\n");
				}
			}
			_delete(data, "data"); data = nullptr;
		}
		else {
			pl = 0;
			sprintf(saveFunctionF, "%s/%s", numerator, denominator);
			removeTriplPars(saveExpressionF);
			printf("\nf(x)=%s\n", expressionF);
			if (isContained("x-", numerator)) {
				replace("x-", "x^1-", numerator);
				sprintf(numerator, "%s", expressionF);
			}
			buildFunctionStudyRationalDerivative<T>(numerator, denominator, new_numerator, new_denominator);
			if (isContained("x^1)", new_numerator) && abs((int)strlen(new_numerator)) == strEnd) {
				new_numerator[abs((int)strlen(new_numerator)) - 1] = '\0';
			}
			if (isContained("x^1)", new_denominator) && abs((int)strlen(new_denominator)) == strEnd) {
				new_denominator[abs((int)strlen(new_denominator)) - 1] = '\0';
			}
			sprintf(new_derivate, "(%s)/(%s)", new_numerator, new_denominator);
			printf("\nf'(x)=%s\n", new_derivate);
			printf("\nx\t-inf\t");
			replaceTimes = 0;
			removeDuplPars(new_numerator);
			sprintf(new_numerator, "%s", expressionF);
			int i = 0, j = 0, z = 0;
			char* value = getDynamicCharArray("", "value");
			replaceTimes = 0;
			char* saveExpF = getDynamicCharArray("", "saveExpF");
			T derivativeLinearRoot = (T)0;
			if (getSingleLinearRoot<T>(new_numerator, &derivativeLinearRoot)) {
				zeroR[z] = normalizeFunctionStudyValue<T>(derivativeLinearRoot);
				zeroI[z] = (T)0;
				poleZerosR[pl] = zeroR[z];
				poleZerosI[pl] = (T)0;
				pl++;
				z++;
			}
			else {
				sprintf(expressionF, "");
				equationSolver<T>(new_numerator);
				sprintf(saveExpF, "%s", expressionF);
				while (isContained("=", saveExpF)) {
					j = 0;
					i = strEnd;
					saveExpF[strStart] = ' ';
					while (i < abs((int)strlen(saveExpF)) && saveExpF[i] != '\n') {
						value[j] = saveExpF[i];
						i++; j++;
					}
					value[j] = '\0';
					if (isContained("-", value)) {
						replace("-", "_", value);
						sprintf(value, "%s", expressionF);
					}
					solveMath<T>(value);
					zeroR[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR)); zeroI[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
					poleZerosR[pl] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR)); poleZerosI[pl] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
					pl++;
					z++;
				}
			}
			sprintf(expressionF, "");
			equationSolver<T>(denominator);
			i = 0; j = 0; z = 0;
			replaceTimes = 0;
			sprintf(saveExpF, "%s", expressionF);
			while (isContained("=", saveExpF)) {
				j = 0;
				i = strEnd;
				saveExpF[strStart] = ' ';
				while (i < abs((int)strlen(saveExpF)) && saveExpF[i] != '\n') {
					value[j] = saveExpF[i];
					i++; j++;
				}
				value[j] = '\0';
				if (isContained("-", value)) {
					replace("-", "_", value);
					sprintf(value, "%s", expressionF);
				}
				solveMath<T>(value);
				zeroR[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR)); zeroI[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
				poleZerosR[pl] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR)); poleZerosI[pl] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
				pl++;
				z++;
			}
			T theSmallerR, theSmallerI = 0;
			int  saveZ = pl;
			int o = 0, saveIndex = -1;
			while (o < saveZ) {
				theSmallerR = 1E12;
				theSmallerI = 0;
				saveIndex = -1;
				for (z = 0; z < saveZ; z++) {
					if (theSmallerR > poleZerosR[z]) {
						theSmallerR = poleZerosR[z];
						theSmallerI = poleZerosI[z];
						saveIndex = z;
					}
				}
				if (saveIndex < 0 || theSmallerR == 1E12) {
					break;
				}
				poleZerosR[saveIndex] = 1E12;
				poleZerosI[saveIndex] = 0;
				if ((o == 0 && theSmallerR != 1E12) || (o > 0 && !sameFunctionStudyValue<T>(sortZeroR[o - 1], theSmallerR) && theSmallerR != 1E12)) {
					sortZeroR[o] = theSmallerR;
					sortZeroI[o] = theSmallerI;
					o++;
				}
				else {
					saveZ--;
				}
			}
			saveZ = o;
			o = 0;
			y = 0;
			while (o < saveZ) {
				printf("%.3f\t", sortZeroR[o]);
				o++;
				y++;
				if (o < saveZ) {
					printf("\t");
					y++;
				}
			}
			printf("+inf\n");
			printf("\nf'(x)\t");
			resultR = sortZeroR[0] - 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			removeDuplPars(new_numerator);
			sprintf(new_numerator, "%s", expressionF);
			removeDuplPars(new_denominator);
			sprintf(new_denominator, "%s", expressionF);
			resultR = solveFunctionStudyExpression<T>(new_numerator) / solveFunctionStudyExpression<T>(new_denominator);
			if (resultR >= 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			y = 0;
			o = 0;
			char* expre = getDynamicCharArray("", "expre");
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				sprintf(expressionF, "");
				variableController("x");
				resultR = solveFunctionStudyExpression<T>(new_numerator) / solveFunctionStudyExpression<T>(new_denominator);
				if (abs(precisionValueTo<T>(resultR)) > 1E4 || abs(precisionValueTo<T>(resultI)) > 1E4) {
					resultR = pot<T>((T)10, (T)400, 1);
					printf("%.2f\t", precisionDisplayDouble(resultR));
				}
				else {

					sprintf(expre, "%.2f\t", precisionDisplayDouble(resultR));
					if (isContained("ind", expre)) {
						printf("ind\t");
					}
					else {
						printf("%s", expre);
					}

				}
				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					sprintf(expressionF, "");
					variableController("x");
					resultR = solveFunctionStudyExpression<T>(new_numerator) / solveFunctionStudyExpression<T>(new_denominator);
					if (resultR >= 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
					y++;
				}
			}
			_delete(expre, "expre"); expre = nullptr;
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			resultR = solveFunctionStudyExpression<T>(new_numerator) / solveFunctionStudyExpression<T>(new_denominator);
			if (resultR >= 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			printf("\nf(x)\t");
			T slopeHelper = 0;
			resultR = sortZeroR[0] - 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			resultR = solveFunctionStudyExpression<T>(originalFunction);
			if (resultR >= 0) {
				printf("/^\t");
			}
			else {
				printf("\\v\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				sprintf(expressionF, "");
				variableController("x");
				resultR = solveFunctionStudyExpression<T>(originalFunction);
				if (abs(precisionValueTo<T>(resultR)) > 1E6 || abs(precisionValueTo<T>(resultI)) > 1E6) {
					resultR = pot<T>((T)10, (T)400, 1);
				}
				printf("%.3f\t", precisionDisplayDouble(resultR));
				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] - 0.25; resultI = 0;
					slopeHelper = solveFunctionStudyExpression<T>(originalFunction);
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					sprintf(expressionF, "");
					variableController("x");
					resultR = solveFunctionStudyExpression<T>(originalFunction);
					if (resultR > slopeHelper) {
						printf("/^\t");
					}
					else {
						printf("\\v\t");
					}
					y++;
				}
			}
			resultR = sortZeroR[o - 1] - 0.25; resultI = 0;
			slopeHelper = solveFunctionStudyExpression<T>(originalFunction);
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			resultR = solveFunctionStudyExpression<T>(originalFunction);
			if (resultR > slopeHelper) {
				printf("/^\t");
			}
			else {
				printf("\\v\t");
			}
			o = 0;
			puts(" ");
			_delete(value, "value");
			value = nullptr;
			_delete(saveExpF, "saveExpF");
			saveExpF = nullptr;
		}
		if (abs((int)strlen(numerator)) == 0 && abs((int)strlen(denominator)) == 0) {
			printf("\n==> Codomain and absolute extremes <==\n");
			if (saveZ == 1) {
				T extremumX = sortZeroR[0];
				resultR = extremumX;
				resultI = sortZeroI[0];
				sprintf(expressionF, "");
				variableController("x");
				T extremumY = precisionValueTo<T>(solveFunctionStudyExpression<T>(saveFunction));
				resultR = extremumX + (T)1000;
				resultI = (T)0;
				sprintf(expressionF, "");
				variableController("x");
				T farY = precisionValueTo<T>(solveFunctionStudyExpression<T>(saveFunction));
				if (farY >= extremumY) {
					printf("\nCodomain: [%.3f,+inf[\n", precisionDisplayDouble(extremumY));
					printf("\nMin: (%.3f,%.3f)\n", precisionDisplayDouble(extremumX), precisionDisplayDouble(extremumY));
				}
				else {
					printf("\nCodomain: ]-inf,%.3f]\n", precisionDisplayDouble(extremumY));
					printf("\nMax: (%.3f,%.3f)\n", precisionDisplayDouble(extremumX), precisionDisplayDouble(extremumY));
				}
				puts("");
			}
			else {
				printf("\nCodomain: ]-inf,");
				while (o < saveZ) {
					resultR = sortZeroR[o];
					resultI = sortZeroI[o];
					sprintf(expressionF, "");
					variableController("x");
					resultR = solveFunctionStudyExpression<T>(saveFunction);
					if (o % 2 == 0) {
						printf("%.3f[", precisionDisplayDouble(resultR));
					}
					else {
						printf("U]%.3f,", precisionDisplayDouble(resultR));
					}
					o++;
				}
				printf("+inf[\n");
				o = 0;
				T max = 0;
				int indexMax = 0;
				T Min = 0;
				int indexMin = 0;
				o = 0;
				while (o < saveZ) {
					resultR = sortZeroR[o];
					resultI = sortZeroI[o];
					sprintf(expressionF, "");
					variableController("x");
					resultR = solveFunctionStudyExpression<T>(saveFunction);
					if (resultR > max) {
						max = precisionValueTo<T>(resultR);
						indexMax = o;
					}
					o++;
				}
				o = 0;
				while (o < saveZ) {
					resultR = sortZeroR[o];
					resultI = sortZeroI[o];
					sprintf(expressionF, "");
					variableController("x");
					resultR = solveFunctionStudyExpression<T>(saveFunction);
					if (resultR < Min) {
						Min = precisionValueTo<T>(resultR);
						indexMin = o;
					}
					o++;
				}
				if (max != 0) {
					printf("\nMax: (%.3f,%.3f)\n", sortZeroR[indexMax], max);
				}
				if (Min != 0) {
					printf("\nMin: (%.3f,%.3f)\n", sortZeroR[indexMin], Min);
				}
				puts("");
			}
		}
		else {
			puts(" ");
			printf("\n==> Direction of concavity and inflection points <==\n");
			pl = 0;
			sprintf(saveFunctionF, "(%s)/(%s)", new_numerator, new_denominator);
			printf("\nf'(x)=%s\n", saveFunctionF);
			char* sec_new_derivate = getDynamicCharArray("", "sec_new_derivate");
			char* sec_new_numerator = getDynamicCharArray("", "sec_new_numerator");
			char* sec_new_denominator = getDynamicCharArray("", "sec_new_denominator");
			buildFunctionStudyRationalDerivative<T>(new_numerator, new_denominator, sec_new_numerator, sec_new_denominator);
			reduceFunctionStudyRationalByFactor<T>(sec_new_numerator, sec_new_denominator, denominator);
			if (isContained("x^1)", sec_new_numerator) && abs((int)strlen(sec_new_numerator)) == strEnd) {
				sec_new_numerator[abs((int)strlen(sec_new_numerator)) - 1] = '\0';
			}
			if (isContained("x^1)", sec_new_denominator) && abs((int)strlen(sec_new_denominator)) == strEnd) {
				sec_new_denominator[abs((int)strlen(sec_new_denominator)) - 1] = '\0';
			}
			sprintf(sec_new_derivate, "(%s)/(%s)", sec_new_numerator, sec_new_denominator);
			sprintf(expressionF, "%s", sec_new_derivate);
			if (isContained("(((", expressionF)) {
				replace("(((", "((", expressionF);
			}
			if (isContained(")))", expressionF)) {
				replace(")))", "))", expressionF);
			}
			sprintf(sec_new_derivate, "%s", expressionF);
			printf("\nf''(x)=%s\n", sec_new_derivate);
			printf("\nx\t-inf\t");
			replaceTimes = 0;
			sprintf(expressionF, "");
			equationSolver<T>(sec_new_numerator);
			int i = 0, j = 0, z = 0;
			char* value = getDynamicCharArray("", "value");
			replaceTimes = 0;
			char* saveExpF = getDynamicCharArray("", "saveExpF");
			sprintf(saveExpF, "%s", expressionF);
			while (isContained("=", saveExpF)) {
				j = 0;
				i = strEnd;
				saveExpF[strStart] = ' ';
				while (i < abs((int)strlen(saveExpF)) && saveExpF[i] != '\n') {
					value[j] = saveExpF[i];
					i++; j++;
				}
				value[j] = '\0';
				if (isContained("-", value)) {
					replace("-", "_", value);
					sprintf(value, "%s", expressionF);
				}
				solveMath<T>(value);
				zeroR[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR)); zeroI[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
				poleZerosR[pl] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR)); poleZerosI[pl] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
				pl++;
				z++;
			}
			sprintf(expressionF, "");
			equationSolver<T>(denominator);
			i = 0; j = 0; z = 0;
			replaceTimes = 0;
			sprintf(saveExpF, "%s", expressionF);
			char* ValueR = getDynamicCharArray("", "ValueR");
			while (isContained("=", saveExpF)) {
				j = 0;
				i = strEnd;
				saveExpF[strStart] = ' ';
				while (i < abs((int)strlen(saveExpF)) && saveExpF[i] != '\n') {
					value[j] = saveExpF[i];
					i++; j++;
				}
				value[j] = '\0';
				if (isContained("-", value)) {
					replace("-", "_", value);
					sprintf(value, "%s", expressionF);
				}
				solveMath<T>(value);

				sprintf(ValueR, convertToString("%.2f"), precisionDisplayDouble(resultR));
				for (int v = 0; v < abs((int)(abs((int)strlen(ValueR)))); v++) {
					if (ValueR[v] == '-')
						ValueR[v] = '_';
				}
				solveMath<T>(ValueR);
				zeroR[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR)); zeroI[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
				poleZerosR[pl] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR)); poleZerosI[pl] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
				pl++;
				z++;

			}
			_delete(ValueR, "ValueR");
			ValueR = nullptr;
			T theSmallerR, theSmallerI = 0;
			int  saveZ = pl;
			int o = 0, saveIndex = -1;
			while (o < saveZ) {
				theSmallerR = 1E12;
				theSmallerI = 0;
				saveIndex = -1;
				for (z = 0; z < pl; z++) {
					if (theSmallerR > poleZerosR[z]) {
						theSmallerR = poleZerosR[z];
						theSmallerI = poleZerosI[z];
						saveIndex = z;
					}
				}
				if (saveIndex < 0 || theSmallerR == 1E12) {
					break;
				}
				poleZerosR[saveIndex] = 1E12;
				poleZerosI[saveIndex] = 0;
				if ((o == 0 && theSmallerR != 1E12) || (o > 0 && !sameFunctionStudyValue<T>(sortZeroR[o - 1], theSmallerR) && theSmallerR != 1E12)) {
					sortZeroR[o] = theSmallerR;
					sortZeroI[o] = theSmallerI;
					o++;
				}
				else {
					saveZ--;
				}
			}
			saveZ = o;
			o = 0;
			y = 0;
			while (o < saveZ) {
				printf("%.3f\t", sortZeroR[o]);
				o++;
				y++;
				if (o < saveZ) {
					printf("\t");
					y++;
				}
			}
			printf("+inf\n");
			printf("\nf''(x)\t");
			resultR = -1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			resultR = solveFunctionStudyExpression<T>(sec_new_derivate);
			if (resultR >= 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			y = 0;
			o = 0;
			char* expre = getDynamicCharArray("", "expre");
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				sprintf(expressionF, "");
				variableController("x");
				resultR = solveFunctionStudyExpression<T>(sec_new_derivate);
				if (abs(precisionValueTo<T>(resultR)) > 1E4 || abs(precisionValueTo<T>(resultI)) > 1E4) {
					resultR = pot<T>((T)10, (T)400, 1);
					printf("%.2f\t", precisionDisplayDouble(resultR));
				}
				else {

					sprintf(expre, "%.2f\t", precisionDisplayDouble(resultR));
					if (isContained("ind", expre)) {
						printf("ind\t");
					}
					else {
						printf("%s", expre);
					}

				}
				y++;
				if (o < saveZ) {
					if (saveZ - o >= 1) {
						resultR = sortZeroR[o] + 0.77; resultI = 0;
					}
					else {
						resultR = 1000; resultI = 0;
					}
					sprintf(expressionF, "");
					variableController("x");
					resultR = solveFunctionStudyExpression<T>(sec_new_derivate);
					if (resultR >= 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
					y++;
				}
				o++;
			}
			printf("\nf(x)\t");
			resultR = -1000; resultI = 0;
			sprintf(expressionF, "");
			variableController("x");
			resultR = solveFunctionStudyExpression<T>(sec_new_derivate);
			if (resultR < 0) {
				printf("/^\\\t");
			}
			else {
				printf("\\_/\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				sprintf(expressionF, "");
				variableController("x");
				resultR = solveFunctionStudyExpression<T>(originalFunction);
				if (abs(precisionValueTo<T>(resultR)) > 1E4 || abs(precisionValueTo<T>(resultI)) > 1E4) {
					resultR = pot<T>((T)10, (T)400, 1);
					printf("%.2f\t", precisionDisplayDouble(resultR));
				}
				else {

					sprintf(expre, "%.2f\t", precisionDisplayDouble(resultR));
					if (isContained("ind", expre)) {
						printf("ind\t");
					}
					else {
						printf("%s", expre);
					}

				}
				y++;
				if (o < saveZ) {
					if (saveZ - o >= 1) {
						resultR = sortZeroR[o] + 0.77; resultI = 0;
					}
					else {
						resultR = 1000; resultI = 0;
					}
					sprintf(expressionF, "");
					variableController("x");
					resultR = solveFunctionStudyExpression<T>(sec_new_derivate);
					if (resultR < 0) {
						printf("/^\\\t");
					}
					else {
						printf("\\_/\t");
					}
					y++;
				}
				o++;
			}
			_delete(expre, "expre");
			expre = nullptr;
			puts(" ");
			resultR = saveResultR;  resultI = saveResultI;
			sprintf(expressionF, "");
			variableController("x");
			printf("\n==> Codomain and absolute extremes <==\n");
			puts(" ");
			o = 0; saveIndex = -1;
			saveZ = u;
			while (o < saveZ) {
				theSmallerR = 1E12;
				theSmallerI = 0;
				saveIndex = -1;
				for (z = 0; z < u; z++) {
					if (theSmallerR > coDomain[z]) {
						theSmallerR = coDomain[z];
						saveIndex = z;
					}
				}
				if (saveIndex < 0 || theSmallerR == 1E12) {
					break;
				}
				coDomain[saveIndex] = 1E12;
				if ((o == 0 && theSmallerR != 1E12) || (o > 0 && !sameFunctionStudyValue<T>(sortZeroR[o - 1], theSmallerR) && theSmallerR != 1E12)) {
					sortZeroR[o] = theSmallerR;
					sortZeroI[o] = theSmallerI;
					o++;
				}
				else {
					saveZ--;
				}
			}
			saveZ = u;
			o = 0;
			printf("\nCodomain: ]-inf,");
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o];
				resultI = sortZeroI[o];
				if (saveZ == 1) {
					printf("%.3f]", precisionDisplayDouble(resultR));
				}
				else {
					if (o % 2 == 0) {
						printf("%.3f[", precisionDisplayDouble(resultR));
					}
					else {
						printf("U]%.3f,", precisionDisplayDouble(resultR));
					}
				}
				o++;
			}
			if (saveZ != 1) {
				printf("+inf[\n");
			}
			o = 0;
			saveZ = pl;
			saveIndex = -1;
			while (o < saveZ) {
				theSmallerR = 1E12;
				theSmallerI = 0;
				saveIndex = -1;
				for (z = 0; z < pl; z++) {
					if (theSmallerR > poleZerosR[z]) {
						theSmallerR = poleZerosR[z];
						theSmallerI = poleZerosI[z];
						saveIndex = z;
					}
				}
				if (saveIndex < 0 || theSmallerR == 1E12) {
					break;
				}
				poleZerosR[saveIndex] = 1E12;
				poleZerosI[saveIndex] = 0;
				if ((o == 0 && theSmallerR != 1E12) || (o > 0 && !sameFunctionStudyValue<T>(sortZeroR[o - 1], theSmallerR) && theSmallerR != 1E12)) {
					sortZeroR[o] = theSmallerR;
					sortZeroI[o] = theSmallerI;
					o++;
				}
				else {
					saveZ--;
				}
			}
			saveZ = o;
			i = 0, j = 0, z = 0;
			replaceTimes = 0;
			pl = 0;
			T derivativeLinearRoot = (T)0;
			if (getSingleLinearRoot<T>(new_numerator, &derivativeLinearRoot)) {
				zeroR[z] = normalizeFunctionStudyValue<T>(derivativeLinearRoot);
				zeroI[z] = (T)0;
				poleZerosR[pl] = zeroR[z];
				poleZerosI[pl] = (T)0;
				pl++;
				z++;
			}
			else {
				sprintf(expressionF, "");
				equationSolver<T>(new_numerator);
				sprintf(saveExpF, "%s", expressionF);
				while (isContained("=", saveExpF)) {
					j = 0;
					i = strEnd;
					saveExpF[strStart] = ' ';
					while (i < abs((int)strlen(saveExpF)) && saveExpF[i] != '\n') {
						value[j] = saveExpF[i];
						i++; j++;
					}
					value[j] = '\0';
					if (isContained("-", value)) {
						replace("-", "_", value);
						sprintf(value, "%s", expressionF);
					}
					solveMath<T>(value);
					zeroR[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR)); zeroI[z] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
					poleZerosR[pl] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR)); poleZerosI[pl] = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
					pl++;
					z++;
				}
			}
			saveZ = pl;
			o = 0, saveIndex = -1;
			while (o < saveZ) {
				theSmallerR = 1E12;
				theSmallerI = 0;
				saveIndex = -1;
				for (z = 0; z < pl; z++) {
					if (theSmallerR > poleZerosR[z]) {
						theSmallerR = poleZerosR[z];
						theSmallerI = poleZerosI[z];
						saveIndex = z;
					}
				}
				if (saveIndex < 0 || theSmallerR == 1E12) {
					break;
				}
				poleZerosR[saveIndex] = 1E12;
				poleZerosI[saveIndex] = 0;
				if ((o == 0 && theSmallerR != 1E12) || (o > 0 && !sameFunctionStudyValue<T>(sortZeroR[o - 1], theSmallerR) && theSmallerR != 1E12)) {
					sortZeroR[o] = theSmallerR;
					sortZeroI[o] = theSmallerI;
					o++;
				}
				else {
					saveZ--;
				}

			}
			saveZ = o;


			o = 0;
			T max = 0;
			int indexMax = 0;
			T Min = 0;
			int indexMin = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o];
				resultI = sortZeroI[o];
				sprintf(expressionF, "");
				variableController("x");
				resultR = solveFunctionStudyExpression<T>(originalFunction);
				if (resultR > max) {
					max = precisionValueTo<T>(resultR);
					indexMax = o;
				}
				o++;
			}
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o];
				resultI = sortZeroI[o];
				sprintf(expressionF, "");
				variableController("x");
				resultR = solveFunctionStudyExpression<T>(originalFunction);
				if (resultR < Min) {
					Min = precisionValueTo<T>(resultR);
					indexMin = o;
				}
				o++;
			}
			if (max != 0) {
				printf("\nMax: (%.3f,%.3f)\n", sortZeroR[indexMax], max);
			}
			if (Min != 0) {
				printf("\nMin: (%.3f,%.3f)\n", sortZeroR[indexMin], Min);
			}
			puts("");
			_delete(sec_new_derivate, "sec_new_derivate");
			sec_new_derivate = nullptr;
			_delete(sec_new_numerator, "sec_new_numerator");
			sec_new_numerator = nullptr;
			_delete(sec_new_denominator, "sec_new_denominator");
			sec_new_denominator = nullptr;
			_delete(value, "value");
			value = nullptr;
			_delete(saveExpF, "saveExpF");
			saveExpF = nullptr;
		}
		studyFunction = false;
		_delete(saveFunctionF, "saveFunctionF");
		_delete(originalFunction, "originalFunction");
		_delete(numerator, "numerator");
		_delete(denominator, "denominator");
		_delete(saveFunction, "saveFunction");
		_delete(value, "value");
		_delete(saveExpF, "saveExpF");
		_delete(verticalAsymptotes, "verticalAsymptotes");
		_delete(valueF, "valueF");
		_delete(saveDenominator, "saveDenominator");
		_delete(new_derivate, "new_derivate");
		_delete(new_numerator, "new_numerator");
		_delete(new_denominator, "new_denominator");
		saveFunctionF = nullptr;
		originalFunction = nullptr;
		numerator = nullptr;
		denominator = nullptr;
		saveFunction = nullptr;
		value = nullptr;
		saveExpF = nullptr;
		verticalAsymptotes = nullptr;
		valueF = nullptr;
		saveDenominator = nullptr;
		new_derivate = nullptr;
		new_numerator = nullptr;
		new_denominator = nullptr;
		_delete(coDomain, "coDomain"); coDomain = nullptr;
		_delete(zeroR, "zeroR"); zeroR = nullptr;
		_delete(zeroI, "zeroI"); zeroI = nullptr;
		_delete(sortZeroR, "sortZeroR"); sortZeroR = nullptr;
		_delete(sortZeroI, "sortZeroI"); sortZeroI = nullptr;
		_delete(minusfx, "minusfx"); minusfx = nullptr;
		_delete(fxminusx, "fxminusx"); fxminusx = nullptr;
		_delete(fx, "fx"); fx = nullptr;
	}
	resultR = saveXR; resultI = saveXI;
	variableController("x");
	if (rf > 0) {
		ansRV = ans[rf - 1];
		ansIV = ansI[rf - 1];
	}
}

template void functionStudy<double>(char*);

template <>
void functionStudy<mp_float>(char* function) { functionStudy<double>(function); }

void functionStudy(char* function) { functionStudy<double>(function); }






