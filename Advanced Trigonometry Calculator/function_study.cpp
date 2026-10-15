
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
	for (int i = 0; i < DIMDOUBLE; i++) {
		coefficients[i] = (T)0;
	}
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
			char* variable = strchr(term, 'x');
			if (variable != nullptr) {
				exponent = 1;
				char* exponentMarker = strchr(variable + 1, '^');
				if (exponentMarker != nullptr) {
					exponent = atoi(exponentMarker + 1);
				}
				if (variable != term) {
					char* coefficientText = getDynamicCharArray("", "functionStudySimpleCoefficient");
					int coefficientIndex = 0;
					for (char* coefficient = term; coefficient < variable; coefficient++) {
						if (*coefficient != '*') {
							coefficientText[coefficientIndex++] = *coefficient == '_' ? '-' : *coefficient;
						}
					}
					coefficientText[coefficientIndex] = '\0';
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
	while (hasBalancedOuterParentheses(polynomial) && polynomial[1] == '(') {
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
	while (hasBalancedOuterParentheses(source) && source[1] == '(') {
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
		int coefficientDepth = 1;
		i++;
		while (source[i] != '\0' && coefficientDepth > 0) {
			if (source[i] == '(') coefficientDepth++;
			if (source[i] == ')') coefficientDepth--;
			if (coefficientDepth == 0) break;
			i++;
		}
		if (source[i] == '\0' || coefficientDepth != 0) {
			break;
		}
		int end = i;
		char* coefficient = getDynamicCharArray("", "functionStudyLeadingCoefficient");
		int c = 0;
		for (int k = start; k < end; k++) {
			coefficient[c] = source[k] == '_' ? '-' : source[k];
			c++;
		}
		coefficient[c] = '\0';
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
	while (hasBalancedOuterParentheses(source) && source[1] == '(') {
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
		// Canonical coefficients are complex, e.g. (1+0i).  The plus
		// inside that coefficient is not a polynomial term separator.
		int coefficientDepth = 1;
		// Canonical coefficients are complex, e.g. (1+0i). Consume nested
		// coefficient parentheses before treating ')' as the term boundary.
		while (source[i] != '\0' && coefficientDepth > 0) {
			if (source[i] == '(') coefficientDepth++;
			if (source[i] == ')') coefficientDepth--;
			if (coefficientDepth == 0) break;
			coefficient[c] = source[i] == '_' ? '-' : source[i];
			c++;
			i++;
		}
		coefficient[c] = '\0';
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

// Real roots for the function-study coefficient representation. Derivative
// roots partition the line into monotone intervals, including repeated roots.
static long double studyPolynomialValue(const std::vector<double>& c, long double x) {
	long double value = 0;
	for (size_t i = c.size(); i > 0; --i) value = value * x + c[i - 1];
	return value;
}

static std::vector<double> studyPolynomialDerivative(const std::vector<double>& c) {
	std::vector<double> derivative(c.size() > 1 ? c.size() - 1 : 1, 0);
	for (size_t i = 1; i < c.size(); ++i) derivative[i - 1] = c[i] * i;
	return derivative;
}

static void studyUniqueRoots(std::vector<double>& roots) {
	std::sort(roots.begin(), roots.end());
	roots.erase(std::unique(roots.begin(), roots.end(), [](double a, double b) {
		return std::abs(a - b) < 1E-9 * std::max(1.0, std::max(std::abs(a), std::abs(b)));
	}), roots.end());
}

static std::vector<double> studyRealPolynomialRoots(std::vector<double> c) {
	while (c.size() > 1 && c.back() == 0) c.pop_back();
	if (c.size() <= 1) return {};
	if (c.front() == 0) {
		c.erase(c.begin());
		std::vector<double> roots = studyRealPolynomialRoots(c);
		roots.push_back(0);
		studyUniqueRoots(roots);
		return roots;
	}
	if (c.size() == 2) return { -c[0] / c[1] };
	double scale = 0;
	for (double v : c) scale = std::max(scale, std::abs(v));
	for (double& v : c) v /= scale;
	double bound = 1;
	for (size_t i = 0; i + 1 < c.size(); ++i) bound = std::max(bound, 1 + std::abs(c[i] / c.back()));
	std::vector<double> critical = studyRealPolynomialRoots(studyPolynomialDerivative(c));
	std::vector<double> points = { -bound }, roots;
	for (double x : critical) if (x > -bound && x < bound) points.push_back(x);
	points.push_back(bound);
	for (double x : critical) {
		long double magnitude = 0;
		for (size_t i = c.size(); i > 0; --i) magnitude = magnitude * std::abs(x) + std::abs(c[i - 1]);
		if (std::abs(studyPolynomialValue(c, x)) <= 1E-12L * magnitude) roots.push_back(x);
	}
	for (size_t i = 1; i < points.size(); ++i) {
		long double left = points[i - 1], right = points[i];
		long double lv = studyPolynomialValue(c, left), rv = studyPolynomialValue(c, right);
		if (lv == 0 || rv == 0 || (lv > 0) == (rv > 0)) continue;
		for (int iteration = 0; iteration < 160; ++iteration) {
			long double middle = (left + right) / 2;
			long double mv = studyPolynomialValue(c, middle);
			if (mv == 0) { left = right = middle; break; }
			if ((lv > 0) == (mv > 0)) { left = middle; lv = mv; }
			else right = middle;
			if (right - left < 1E-13L * std::max(1.0L, std::abs(middle))) break;
		}
		roots.push_back((double)((left + right) / 2));
	}
	studyUniqueRoots(roots);
	return roots;
}

template <typename T>
static std::vector<double> studyPolynomialCoefficients(char* polynomial) {
	T* coefficients = getDynamicArray<T>(DIMDOUBLE);
	int degree = 0;
	parseFunctionStudyPolynomial<T>(polynomial, coefficients, &degree);
	std::vector<double> result(degree + 1);
	for (int i = 0; i <= degree; ++i) result[i] = precisionDisplayDouble(coefficients[i]);
	_delete(coefficients, "studyCoefficients");
	while (result.size() > 1 && result.back() == 0) result.pop_back();
	return result;
}

template <typename T>
static void solveFunctionStudyPolynomialEquation(char* polynomial) {
	T* coefficients = getDynamicArray<T>(DIMDOUBLE);
	int degree = 0;
	parseFunctionStudyPolynomial<T>(polynomial, coefficients, &degree);
	expressionF[0] = '\0';
	int rootCount = 0;
	auto appendRoot = [&](T root) {
		int used = (int)strlen(expressionF);
		if (used < DIM - 1) {
			int written = snprintf(expressionF + used, DIM - used, "x%d=%.15g\n",
				rootCount + 1, precisionDisplayDouble(root));
			if (written > 0 && used + written < DIM) rootCount++;
		}
	};

	if (degree == 1 && abs(precisionDisplayDouble(coefficients[1])) >= 1E-12) {
		appendRoot(-coefficients[0] / coefficients[1]);
	}
	else if (degree == 2 && abs(precisionDisplayDouble(coefficients[2])) >= 1E-12) {
		const T a = coefficients[2];
		const T b = coefficients[1];
		const T c = coefficients[0];
		T discriminant = b * b - (T)4 * a * c;
		double displayedDiscriminant = precisionDisplayDouble(discriminant);
		if (displayedDiscriminant >= -1E-10) {
			if (abs(displayedDiscriminant) < 1E-10) discriminant = (T)0;
			using std::sqrt;
			const T rootOffset = sqrt(discriminant);
			T firstRoot = (-b + rootOffset) / ((T)2 * a);
			T secondRoot = (-b - rootOffset) / ((T)2 * a);
			if (precisionDisplayDouble(firstRoot) < precisionDisplayDouble(secondRoot)) {
				T swapRoot = firstRoot;
				firstRoot = secondRoot;
				secondRoot = swapRoot;
			}
			appendRoot(firstRoot);
			if (abs(precisionDisplayDouble(rootOffset)) > 1E-10) {
				appendRoot(secondRoot);
			}
		}
	}
	else if (degree > 2) {
		std::vector<double> polynomialCoefficients(degree + 1);
		for (int i = 0; i <= degree; ++i) polynomialCoefficients[i] = precisionDisplayDouble(coefficients[i]);
		std::vector<double> roots = studyRealPolynomialRoots(polynomialCoefficients);
		for (auto root = roots.rbegin(); root != roots.rend(); ++root) appendRoot((T)*root);
	}
	_delete(coefficients, "functionStudyEquationCoefficients"); coefficients = nullptr;
}

template <typename T>
static void writeFunctionStudyPolynomial(T* coefficients, int degree, char* output) {
	output[0] = '\0';
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
		int used = (int)strlen(output);
		if (used > 0 && used < DIM - 1) {
			output[used++] = '+';
			output[used] = '\0';
		}
		if (used < DIM - 1) {
			if (exponent > 0) {
				snprintf(output + used, DIM - used, "(%s+0i)x^%d", coefficientText, exponent);
			}
			else {
				snprintf(output + used, DIM - used, "(%s+0i)", coefficientText);
			}
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
static void printFunctionStudyRationalTable(char* numerator, char* denominator,
	char* originalNumerator, char* originalDenominator, T* rootsR, T* rootsI,
	int count, int mode) {
	std::vector<T> points;
	for (int i = 0; i < count; i++) {
		if (abs(precisionDisplayDouble(rootsI[i])) < 1E-7) points.push_back(rootsR[i]);
	}
	std::sort(points.begin(), points.end());
	points.erase(std::unique(points.begin(), points.end(), [](T a, T b) {
		return sameFunctionStudyValue<T>(a, b);
	}), points.end());
	auto polynomialAt = [](char* expression, T x) {
		T value = (T)0;
		evaluateCanonicalPolynomial<T>(expression, x, &value);
		return value;
	};
	auto sample = [&](size_t interval) {
		if (points.empty()) return (T)0;
		if (interval == 0) return points.front() - (T)(1 + abs(precisionDisplayDouble(points.front())));
		if (interval == points.size()) return points.back() + (T)(1 + abs(precisionDisplayDouble(points.back())));
		return (points[interval - 1] + points[interval]) / (T)2;
	};
	auto sign = [](T value) { return value > 0 ? "+" : (value < 0 ? "-" : "0"); };
	printf("\nx\t-inf\t");
	for (T x : points) printf("%.3f\t\t", precisionDisplayDouble(x));
	printf("+inf\n");
	if (mode == 0) {
		printf("\nNumerator-> %s\nDenominator-> %s\n", numerator, denominator);
		for (int row = 0; row < 2; row++) {
			char* polynomial = row == 0 ? numerator : denominator;
			printf("%s\t", row == 0 ? "Numerator" : "Denominator");
			for (size_t interval = 0; interval <= points.size(); interval++) {
				printf("%s\t", sign(polynomialAt(polynomial, sample(interval))));
				if (interval < points.size()) {
					T value = polynomialAt(polynomial, points[interval]);
					printf("%s\t", abs(precisionDisplayDouble(value)) < 1E-8 ? "0" : sign(value));
				}
			}
			puts("");
		}
	}
	printf("%s\t", mode == 0 ? "f(x)" : (mode == 1 ? "f'(x)" : "f''(x)"));
	for (size_t interval = 0; interval <= points.size(); interval++) {
		T x = sample(interval);
		T n = polynomialAt(numerator, x), d = polynomialAt(denominator, x);
		printf("%s\t", sign(n / d));
		if (interval < points.size()) {
			x = points[interval];
			n = polynomialAt(numerator, x); d = polynomialAt(denominator, x);
			T originalD = polynomialAt(originalDenominator, x);
			printf("%s\t", abs(precisionDisplayDouble(originalD)) < 1E-8 ||
				abs(precisionDisplayDouble(d)) < 1E-8 ? "undefined" :
				(abs(precisionDisplayDouble(n)) < 1E-8 ? "0" : sign(n / d)));
		}
	}
	puts("");
	if (mode == 0) return;
	printf("f(x)\t");
	for (size_t interval = 0; interval <= points.size(); interval++) {
		T x = sample(interval);
		T derivative = polynomialAt(numerator, x) / polynomialAt(denominator, x);
		printf("%s\t", mode == 1 ? (derivative > 0 ? "/^" : (derivative < 0 ? "\\v" : "constant")) :
			(derivative > 0 ? "\\_/" : (derivative < 0 ? "/^\\" : "linear")));
		if (interval < points.size()) {
			x = points[interval];
			T d = polynomialAt(originalDenominator, x);
			if (abs(precisionDisplayDouble(d)) < 1E-8) printf("undefined\t");
			else printf("%.3f\t", precisionDisplayDouble(normalizeFunctionStudyValue<T>(polynomialAt(originalNumerator, x) / d)));
		}
	}
	puts("");
	for (size_t i = 0; i < points.size(); i++) {
		T x = points[i], d = polynomialAt(originalDenominator, x);
		if (abs(precisionDisplayDouble(d)) < 1E-8 || abs(precisionDisplayDouble(polynomialAt(numerator, x))) > 1E-7) continue;
		T left = polynomialAt(numerator, sample(i)) / polynomialAt(denominator, sample(i));
		T right = polynomialAt(numerator, sample(i + 1)) / polynomialAt(denominator, sample(i + 1));
		if (left * right < 0) {
			printf("%s: (%.3f,%.3f)\n", mode == 2 ? "Inflection point" : (left < 0 ? "Local min" : "Local max"),
				precisionDisplayDouble(x), precisionDisplayDouble(normalizeFunctionStudyValue<T>(polynomialAt(originalNumerator, x) / d)));
		}
	}
}

static std::vector<double> studyPolynomialProduct(const std::vector<double>& a, const std::vector<double>& b) {
	std::vector<double> result(a.size() + b.size() - 1, 0);
	for (size_t i = 0; i < a.size(); ++i) for (size_t j = 0; j < b.size(); ++j) result[i + j] += a[i] * b[j];
	return result;
}

static bool studyPolynomialZeroAt(const std::vector<double>& c, double x) {
	long double scale = 0;
	for (size_t i = c.size(); i > 0; --i) scale = scale * std::abs(x) + std::abs(c[i - 1]);
	return std::abs(studyPolynomialValue(c, x)) <= 1E-10L * scale;
}

// One-sided limit at a denominator zero, including removable holes and
// common factors with unequal multiplicities. side is -1 (left) or +1.
static double studyRationalBoundary(std::vector<double> n, std::vector<double> d, double x, int side) {
	int no = 0, od = 0;
	while (n.size() > 1 && studyPolynomialZeroAt(n, x)) { n = studyPolynomialDerivative(n); ++no; }
	while (d.size() > 1 && studyPolynomialZeroAt(d, x)) { d = studyPolynomialDerivative(d); ++od; }
	double ratio = (double)(studyPolynomialValue(n, x) / studyPolynomialValue(d, x));
	if (ratio == 0 || no > od) return 0;
	if (no == od) return ratio;
	if (side < 0 && (od - no) % 2) ratio = -ratio;
	return std::copysign(std::numeric_limits<double>::infinity(), ratio);
}

static double studyRationalInfinity(const std::vector<double>& n, const std::vector<double>& d, int side) {
	if (n.size() < d.size() || n.back() == 0) return 0;
	double ratio = n.back() / d.back();
	if (n.size() == d.size()) return ratio;
	if (side < 0 && (n.size() - d.size()) % 2) ratio = -ratio;
	return std::copysign(std::numeric_limits<double>::infinity(), ratio);
}

// A rational function is continuous and monotone between denominator zeros
// and derivative zeros. Its image is the union of these interval images;
// excluded domain points contribute limits, never attained extrema.
template <typename T>
static void printFunctionStudyGeneralRange(char* numerator, char* denominator) {
	std::vector<double> n = studyPolynomialCoefficients<T>(numerator), d = studyPolynomialCoefficients<T>(denominator);
	std::vector<double> derivative = studyPolynomialProduct(studyPolynomialDerivative(n), d);
	std::vector<double> sub = studyPolynomialProduct(n, studyPolynomialDerivative(d));
	derivative.resize(std::max(derivative.size(), sub.size()), 0);
	for (size_t i = 0; i < sub.size(); ++i) derivative[i] -= sub[i];
	std::vector<double> poles = studyRealPolynomialRoots(d);
	std::vector<double> points = studyRealPolynomialRoots(derivative);
	points.insert(points.end(), poles.begin(), poles.end());
	studyUniqueRoots(points);
	struct Interval { double lo, hi; bool lc, hc; double lx, hx; };
	std::vector<Interval> intervals;
	for (size_t i = 0; i <= points.size(); ++i) {
		double left = i == 0 ? studyRationalInfinity(n, d, -1) : studyRationalBoundary(n, d, points[i - 1], 1);
		double right = i == points.size() ? studyRationalInfinity(n, d, 1) : studyRationalBoundary(n, d, points[i], -1);
		bool lc = i > 0 && !studyPolynomialZeroAt(d, points[i - 1]);
		bool hc = i < points.size() && !studyPolynomialZeroAt(d, points[i]);
		double lx = i == 0 ? 0 : points[i - 1], hx = i == points.size() ? 0 : points[i];
		if (left > right) { std::swap(left, right); std::swap(lc, hc); std::swap(lx, hx); }
		if (left == right) {
			lc = hc = true;
			lx = hx = points.empty() ? 0 : (i == 0 ? points.front() - 1 : (i == points.size() ? points.back() + 1 : (points[i - 1] + points[i]) / 2));
		}
		intervals.push_back({left, right, lc, hc, lx, hx});
	}
	std::sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) { return a.lo < b.lo; });
	std::vector<Interval> image;
	for (const Interval& interval : intervals) {
		if (image.empty() || interval.lo > image.back().hi ||
			(interval.lo == image.back().hi && !interval.lc && !image.back().hc)) { image.push_back(interval); continue; }
		Interval& last = image.back();
		if (interval.lo == last.lo && interval.lc) { last.lc = true; last.lx = interval.lx; }
		if (interval.hi > last.hi) { last.hi = interval.hi; last.hc = interval.hc; last.hx = interval.hx; }
		else if (interval.hi == last.hi && interval.hc) { last.hc = true; last.hx = interval.hx; }
	}
	printf("\nCodomain: ");
	for (size_t i = 0; i < image.size(); ++i) {
		const Interval& interval = image[i];
		if (i) printf("U");
		if (image.size() == 1 && std::isinf(interval.lo) && std::isinf(interval.hi)) { printf("R"); continue; }
		if (interval.lo == interval.hi) { printf("{%.3f}", interval.lo); continue; }
		if (std::isinf(interval.lo)) printf("]-inf,");
		else printf("%c%.3f,", interval.lc ? '[' : ']', interval.lo == 0 ? 0 : interval.lo);
		if (std::isinf(interval.hi)) printf("+inf[");
		else printf("%.3f%c", interval.hi == 0 ? 0 : interval.hi, interval.hc ? ']' : '[');
	}
	puts("");
	bool extremum = false;
	if (image.front().lc && std::isfinite(image.front().lo)) { printf("Min: (%.3f,%.3f)\n", normalizeFunctionStudyValue<T>(image.front().lx), normalizeFunctionStudyValue<T>(image.front().lo)); extremum = true; }
	if (image.back().hc && std::isfinite(image.back().hi)) { printf("Max: (%.3f,%.3f)\n", normalizeFunctionStudyValue<T>(image.back().hx), normalizeFunctionStudyValue<T>(image.back().hi)); extremum = true; }
	if (!extremum) puts("No absolute minimum or maximum.");
}

// For real rational polynomials of degree <= 2, y is in the image precisely
// when N(x)-y*D(x)=0 has a real root at which D(x) is nonzero.
template <typename T>
static bool printFunctionStudyQuadraticRange(char* numerator, char* denominator) {
	T* nc = getDynamicArray<T>(DIMDOUBLE); T* dc = getDynamicArray<T>(DIMDOUBLE);
	int nd = 0, dd = 0;
	parseFunctionStudyPolynomial<T>(numerator, nc, &nd);
	parseFunctionStudyPolynomial<T>(denominator, dc, &dd);
	if (nd > 2 || dd > 2) {
		_delete(nc, "rangeNumerator"); _delete(dc, "rangeDenominator");
		printFunctionStudyGeneralRange<T>(numerator, denominator);
		return true;
	}
	double n[3], d[3];
	for (int i = 0; i < 3; i++) { n[i] = precisionDisplayDouble(nc[i]); d[i] = precisionDisplayDouble(dc[i]); }
	_delete(nc, "rangeNumerator"); _delete(dc, "rangeDenominator");
	auto realRoots = [](double a, double b, double c) {
		std::vector<double> roots;
		if (abs(a) < 1E-12) { if (abs(b) >= 1E-12) roots.push_back(-c / b); }
		else {
			double delta = b * b - 4 * a * c;
			if (delta >= -1E-10) {
				delta = std::max(0.0, delta);
				roots.push_back((-b + sqrt(delta)) / (2 * a));
				if (delta > 1E-10) roots.push_back((-b - sqrt(delta)) / (2 * a));
			}
		}
		return roots;
	};
	auto preimage = [&](double y, double* x) {
		double a = n[2] - y * d[2], b = n[1] - y * d[1], c = n[0] - y * d[0];
		std::vector<double> candidates = realRoots(a, b, c);
		if (abs(a) < 1E-12 && abs(b) < 1E-12 && abs(c) < 1E-12) candidates = { 0, 1, -1, 2 };
		for (double root : candidates) {
			double divisor = (d[2] * root + d[1]) * root + d[0];
			if (abs(divisor) > 1E-8) { *x = root; return true; }
		}
		return false;
	};
	std::vector<double> boundaries = realRoots(d[1]*d[1]-4*d[2]*d[0],
		-2*n[1]*d[1]+4*(n[2]*d[0]+d[2]*n[0]), n[1]*n[1]-4*n[2]*n[0]);
	if (dd > 0 && abs(d[dd]) > 1E-12) boundaries.push_back(n[dd] / d[dd]);
	for (double& boundary : boundaries) if (abs(boundary) < 1E-12) boundary = 0.0;
	std::sort(boundaries.begin(), boundaries.end());
	boundaries.erase(std::unique(boundaries.begin(), boundaries.end(), [](double a, double b) { return abs(a-b) < 1E-8; }), boundaries.end());
	std::vector<bool> cells;
	double x = 0;
	for (size_t i = 0; i <= boundaries.size(); i++) {
		double y = boundaries.empty() ? 0 : (i == 0 ? boundaries.front()-1-abs(boundaries.front()) :
			(i == boundaries.size() ? boundaries.back()+1+abs(boundaries.back()) : (boundaries[i-1]+boundaries[i])/2));
		cells.push_back(preimage(y, &x));
		if (i < boundaries.size()) cells.push_back(preimage(boundaries[i], &x));
	}
	printf("\nCodomain: ");
	bool printed = false;
	for (size_t i = 0; i < cells.size(); i++) {
		if (!cells[i]) continue;
		size_t start = i;
		while (i + 1 < cells.size() && cells[i+1]) i++;
		if (printed) printf("U");
		printed = true;
		if (start == 0 && i + 1 == cells.size()) { printf("]-inf,+inf["); continue; }
		if (start == i && start % 2 == 1) { printf("{%.3f}", boundaries[start/2]); continue; }
		if (start == 0) printf("]-inf,");
		else printf("%c%.3f,", start % 2 == 1 ? '[' : ']', boundaries[(start-1)/2]);
		if (i + 1 == cells.size()) printf("+inf[");
		else printf("%.3f%c", boundaries[i/2], i % 2 == 1 ? ']' : '[');
	}
	puts("");
	bool extremum = false;
	if (!cells.front()) {
		for (size_t i = 1; i < cells.size(); i++) if (cells[i]) {
			if (i % 2 == 1 && preimage(boundaries[i/2], &x)) { printf("Min: (%.3f,%.3f)\n", abs(x) < 1E-9 ? 0.0 : x, boundaries[i/2]); extremum = true; }
			break;
		}
	}
	if (!cells.back()) {
		for (size_t i = cells.size()-1; i > 0; i--) if (cells[i]) {
			if (i % 2 == 1 && preimage(boundaries[i/2], &x)) { printf("Max: (%.3f,%.3f)\n", abs(x) < 1E-9 ? 0.0 : x, boundaries[i/2]); extremum = true; }
			break;
		}
	}
	if (!extremum) puts("No absolute minimum or maximum.");
	return true;
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
			int h = strStart + 1;
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
			// Use the canonical coefficient derivative path for every polynomial.
			snprintf(numerator, DIM, "%s", saveFunctionF);
			snprintf(denominator, DIM, "(1+0i)");
			snprintf(originalFunction, DIM, "%s/(1+0i)", saveFunctionF);
		}

		if (abs((int)strlen(denominator)) > 0) {
			solveFunctionStudyPolynomialEquation<T>(denominator);
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
					// Zeros of the denominator split the sign chart but are not
					// zeros of the function itself.
					if (abs((int)strlen(denominator)) == 0 || !isContained("=", denominator)) {
						zeroR[z] = rootR; zeroI[z] = rootI; z++;
					}
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
			bool isFunctionZero = true;
			for (int pole = 0; pole < pl; pole++) {
				if (sameFunctionStudyValue<T>(linearRoot, poleZerosR[pole]) &&
					abs(precisionDisplayDouble(poleZerosI[pole])) < 1E-7) {
					isFunctionZero = false;
					break;
				}
			}
			if (isFunctionZero) {
				zeroR[z] = linearRoot; zeroI[z] = (T)0;
				printf("\n(%.3G,0)", precisionDisplayDouble(linearRoot));
				z++;
			}
			poleZerosR[pl] = linearRoot; poleZerosI[pl] = (T)0;
			pl++;
		}
		else {
				solveFunctionStudyPolynomialEquation<T>(saveFunction);
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
			T rootR = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultR));
			T rootI = normalizeFunctionStudyValue<T>(precisionValueTo<T>(resultI));
			bool isFunctionZero = true;
			for (int pole = 0; pole < pl; pole++) {
				if (sameFunctionStudyValue<T>(rootR, poleZerosR[pole]) &&
					abs(precisionDisplayDouble(poleZerosI[pole])) < 1E-7) {
					isFunctionZero = false;
					break;
				}
			}
			if (isFunctionZero) {
				zeroR[z] = rootR; zeroI[z] = rootI;
				printf("\n(%.3G,0)", precisionDisplayDouble(rootR));
				z++;
			}
			poleZerosR[pl] = rootR; poleZerosI[pl] = rootI;
			pl++;
		}
		// Keep the sign chart's breakpoints to real zeros of f and real
		// denominator roots (vertical asymptotes), without duplicates.
		for (int pole = 0; pole < pl; pole++) {
			if (abs(precisionDisplayDouble(poleZerosI[pole])) > 1E-7) continue;
			bool present = false;
			for (int root = 0; root < z; root++) {
				if (sameFunctionStudyValue<T>(zeroR[root], poleZerosR[pole])) {
					present = true;
					break;
				}
			}
			if (!present) {
				zeroR[z] = poleZerosR[pole];
				zeroI[z] = (T)0;
				z++;
			}
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
		T yyDenominator = (T)1;
		evaluateCanonicalPolynomial<T>(denominator, (T)0, &yyDenominator);
		if (yyDenominator != 0) {
			printf("\n(0,%.3f)\n", precisionDisplayDouble(resultR));
			intersectYY = precisionValueTo<T>(resultR);
			coDomain[u++] = intersectYY;
		}
		else puts("The function does not intersect the yy-axis.");
		printf("\n==> Asymptotes <==\n");
		char* verticalAsymptotes = getDynamicCharArray("", "verticalAsymptotes");
		if (abs((int)strlen(denominator)) > 0) {
			solveFunctionStudyPolynomialEquation<T>(denominator);
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
				if (parseFunctionStudyRootValue<T>(value, &rootR, &rootI) &&
					std::isinf(studyRationalBoundary(studyPolynomialCoefficients<T>(numerator),
						studyPolynomialCoefficients<T>(denominator), precisionDisplayDouble(rootR), 1))) {
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
		// Compare N(-x)D(x) with +/-N(x)D(-x), and preserve domain symmetry.
		std::vector<double> symmetryN = studyPolynomialCoefficients<T>(numerator);
		std::vector<double> symmetryD = studyPolynomialCoefficients<T>(denominator);
		std::vector<double> reflectedN = symmetryN, reflectedD = symmetryD;
		for (size_t k = 1; k < reflectedN.size(); k += 2) reflectedN[k] = -reflectedN[k];
		for (size_t k = 1; k < reflectedD.size(); k += 2) reflectedD[k] = -reflectedD[k];
		std::vector<double> lhs = studyPolynomialProduct(reflectedN, symmetryD);
		std::vector<double> rhs = studyPolynomialProduct(symmetryN, reflectedD);
		bool even = true, odd = true;
		double symmetryScale = 0;
		for (size_t k = 0; k < lhs.size(); ++k) symmetryScale = std::max(symmetryScale, std::max(std::abs(lhs[k]), std::abs(rhs[k])));
		for (size_t k = 0; k < lhs.size(); ++k) {
			if (std::abs(lhs[k] - rhs[k]) > 1E-12 * symmetryScale) even = false;
			if (std::abs(lhs[k] + rhs[k]) > 1E-12 * symmetryScale) odd = false;
		}
		std::vector<double> domainRoots = studyRealPolynomialRoots(symmetryD);
		for (double root : domainRoots) {
			bool reflectedRoot = false;
			for (double other : domainRoots) if (std::abs(root + other) < 1E-8 * std::max(1.0, std::abs(root))) reflectedRoot = true;
			if (!reflectedRoot) { even = odd = false; break; }
		}
		puts(even ? "\nThe function is even." : "\nThe function is not even.");
		puts(odd ? "\nThe function is odd." : "\nThe function is not odd.");
		if (!even && !odd) puts("\nThere is no symmetry of the graph with respect to the yy axis or the origin.");
		int y = 0, p = 0;
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

			printFunctionStudyRationalTable<T>(numerator, denominator, numerator, denominator, sortZeroR, sortZeroI, o, 0);

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
				solveFunctionStudyPolynomialEquation<T>(data);
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
				resultR = (sortZeroR[o - 1] + sortZeroR[o]) / (T)2; resultI = 0;
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
			printf("\nf(x)=%s\n", isEqual(denominator, "(1+0i)") ? numerator : expressionF);
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
			if (isEqual(denominator, "(1+0i)")) {
				removeDuplPars(new_numerator);
				if (isContained("x", new_numerator)) printf("\nf'(x)=(%s)\n", new_numerator);
				else printf("\nf'(x)=%s\n", new_numerator);
			}
			else {
				printf("\nf'(x)=%s\n", new_derivate);
			}

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
				solveFunctionStudyPolynomialEquation<T>(new_numerator);
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
			solveFunctionStudyPolynomialEquation<T>(denominator);
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
			printFunctionStudyRationalTable<T>(new_numerator, new_denominator, numerator, denominator, sortZeroR, sortZeroI, saveZ, 1);
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

			replaceTimes = 0;
			sprintf(expressionF, "");
			solveFunctionStudyPolynomialEquation<T>(sec_new_numerator);
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
			solveFunctionStudyPolynomialEquation<T>(denominator);
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
			printFunctionStudyRationalTable<T>(sec_new_numerator, sec_new_denominator, numerator, denominator, sortZeroR, sortZeroI, saveZ, 2);
			resultR = saveResultR;  resultI = saveResultI;
			sprintf(expressionF, "");
			variableController("x");
			printf("\n==> Codomain and absolute extremes <==\n");
			puts(" ");
			if (!printFunctionStudyQuadraticRange<T>(numerator, denominator)) {
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
				solveFunctionStudyPolynomialEquation<T>(new_numerator);
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
			}
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

		new_derivate = nullptr;
		new_numerator = nullptr;
		new_denominator = nullptr;
		_delete(coDomain, "coDomain"); coDomain = nullptr;
		_delete(zeroR, "zeroR"); zeroR = nullptr;
		_delete(zeroI, "zeroI"); zeroI = nullptr;
		_delete(sortZeroR, "sortZeroR"); sortZeroR = nullptr;
		_delete(sortZeroI, "sortZeroI"); sortZeroI = nullptr;



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






