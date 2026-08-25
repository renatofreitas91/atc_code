

#include "stdafx.h"

bool solverRunning = false, retrySolver = false, retrySolver_2 = false, retrySolver_3 = false, poly = true;
PrecisionValue xValuesR = 0, xValuesI = 0, saveResultRFR = 0, saveResultRFI = 0;
int countEntriesSolver = 0;
char* saveSimplification = getDynamicCharArray("", "saveSimplification"), * saveSimplified = getDynamicCharArray("", "saveSimplified");

static bool parseSolverLinearNumber(const std::string& text, long double& value) {
	if (text.empty()) {
		return false;
	}
	std::string normalized = text;
	for (size_t i = 0; i < normalized.size(); i++) {
		if (normalized[i] == '_') {
			normalized[i] = '-';
		}
	}
	if (normalized == "pi" || normalized == "+pi") {
		value = acosl(-1.0L);
		return true;
	}
	if (normalized == "-pi") {
		value = -acosl(-1.0L);
		return true;
	}
	if (normalized == "e" || normalized == "+e") {
		value = expl(1.0L);
		return true;
	}
	if (normalized == "-e") {
		value = -expl(1.0L);
		return true;
	}
	char* end = nullptr;
	value = std::strtold(normalized.c_str(), &end);
	return end != normalized.c_str() && *end == '\0';
}

static bool parseUnsignedSolverConstantProduct(const std::string& text, long double& value) {
	if (text.empty()) {
		return false;
	}
	value = 1.0L;
	size_t index = 0;
	bool consumedFactor = false;
	while (index < text.size()) {
		if (text.compare(index, 2, "pi") == 0) {
			value *= acosl(-1.0L);
			index += 2;
			consumedFactor = true;
		}
		else if (text[index] == 'e') {
			value *= expl(1.0L);
			index++;
			consumedFactor = true;
		}
		else {
			char* end = nullptr;
			long double factor = std::strtold(text.c_str() + index, &end);
			if (end == text.c_str() + index) {
				return false;
			}
			value *= factor;
			index = (size_t)(end - text.c_str());
			consumedFactor = true;
		}
	}
	return consumedFactor;
}

static bool parseSolverConstantProduct(const std::string& text, long double& value) {
	if (text.empty()) {
		return false;
	}
	std::string normalized = text;
	for (size_t i = 0; i < normalized.size(); i++) {
		if (normalized[i] == '_') {
			normalized[i] = '-';
		}
	}
	long double sign = 1.0L;
	if (normalized[0] == '+') {
		normalized.erase(0, 1);
	}
	else if (normalized[0] == '-') {
		sign = -1.0L;
		normalized.erase(0, 1);
	}
	long double unsignedValue = 0.0L;
	if (!parseUnsignedSolverConstantProduct(normalized, unsignedValue)) {
		return false;
	}
	value = sign * unsignedValue;
	return true;
}

static bool parseSolverLinearComplexNumber(const std::string& text, std::complex<long double>& value) {
	if (text.empty()) {
		return false;
	}
	std::string normalized = text;
	for (size_t i = 0; i < normalized.size(); i++) {
		if (normalized[i] == '_') {
			normalized[i] = '-';
		}
	}
	long double realValue = 0.0L;
	if (parseSolverLinearNumber(normalized, realValue) || parseSolverConstantProduct(normalized, realValue)) {
		value = std::complex<long double>(realValue, 0.0L);
		return true;
	}
	if (normalized == "i" || normalized == "+i") {
		value = std::complex<long double>(0.0L, 1.0L);
		return true;
	}
	if (normalized == "-i") {
		value = std::complex<long double>(0.0L, -1.0L);
		return true;
	}
	if (normalized[normalized.size() - 1] == 'i') {
		std::string imaginaryText = normalized.substr(0, normalized.size() - 1);
		if (imaginaryText.empty() || imaginaryText == "+") {
			value = std::complex<long double>(0.0L, 1.0L);
			return true;
		}
		if (imaginaryText == "-") {
			value = std::complex<long double>(0.0L, -1.0L);
			return true;
		}
		long double imaginaryValue = 0.0L;
		if (parseSolverLinearNumber(imaginaryText, imaginaryValue) || parseSolverConstantProduct(imaginaryText, imaginaryValue)) {
			value = std::complex<long double>(0.0L, imaginaryValue);
			return true;
		}
	}
	return false;
}

static bool trySolveSolverLinearExpressionComplex(const std::string& expression, std::complex<long double>& solution) {
	std::string text;
	text.reserve(expression.size());
	for (size_t i = 0; i < expression.size(); i++) {
		if (!std::isspace((unsigned char)expression[i])) {
			text.push_back(expression[i]);
		}
	}
	if (text.empty() || text.find('(') != std::string::npos || text.find(')') != std::string::npos ||
		text.find('/') != std::string::npos || text.find('\\') != std::string::npos) {
		return false;
	}
	std::complex<long double> coefficient(0.0L, 0.0L);
	std::complex<long double> constant(0.0L, 0.0L);
	bool hasX = false;
	size_t start = 0;
	while (start < text.size()) {
		size_t end = start + 1;
		while (end < text.size() && text[end] != '+' && text[end] != '-') {
			end++;
		}
		std::string term = text.substr(start, end - start);
		size_t xPos = term.find('x');
		if (xPos != std::string::npos) {
			if (term.find('x', xPos + 1) != std::string::npos) {
				return false;
			}
			std::string suffixText = term.substr(xPos + 1);
			if (!suffixText.empty() && suffixText != "^1") {
				return false;
			}
			std::string coeffText = term.substr(0, xPos);
			if (coeffText.empty() || coeffText == "+") {
				coefficient += std::complex<long double>(1.0L, 0.0L);
			}
			else if (coeffText == "-" || coeffText == "_") {
				coefficient -= std::complex<long double>(1.0L, 0.0L);
			}
			else {
				std::complex<long double> termCoefficient(0.0L, 0.0L);
				if (!parseSolverLinearComplexNumber(coeffText, termCoefficient)) {
					return false;
				}
				coefficient += termCoefficient;
			}
			hasX = true;
		}
		else {
			std::complex<long double> termConstant(0.0L, 0.0L);
			if (!parseSolverLinearComplexNumber(term, termConstant)) {
				return false;
			}
			constant += termConstant;
		}
		start = end;
	}
	if (!hasX || std::abs(coefficient) < 1E-30L) {
		return false;
	}
	solution = -constant / coefficient;
	return true;
}

static bool trySolveSolverLinearExpression(const std::string& expression, long double& solution) {
	std::string text;
	text.reserve(expression.size());
	for (size_t i = 0; i < expression.size(); i++) {
		if (!std::isspace((unsigned char)expression[i])) {
			text.push_back(expression[i]);
		}
	}
	if (text.empty() || text.find('(') != std::string::npos || text.find(')') != std::string::npos ||
		text.find('/') != std::string::npos || text.find('\\') != std::string::npos) {
		return false;
	}
	long double coefficient = 0.0L;
	long double constant = 0.0L;
	bool hasX = false;
	size_t start = 0;
	while (start < text.size()) {
		size_t end = start + 1;
		while (end < text.size() && text[end] != '+' && text[end] != '-') {
			end++;
		}
		std::string term = text.substr(start, end - start);
		size_t xPos = term.find('x');
		if (xPos != std::string::npos) {
			if (term.find('x', xPos + 1) != std::string::npos) {
				return false;
			}
			if (term.find('^') != std::string::npos && term.find("^1") == std::string::npos) {
				return false;
			}
			std::string coeffText = term.substr(0, xPos);
			if (coeffText.empty() || coeffText == "+") {
				coefficient += 1.0L;
			}
			else if (coeffText == "-" || coeffText == "_") {
				coefficient -= 1.0L;
			}
			else {
				long double termCoefficient = 0.0L;
				if (!parseSolverLinearNumber(coeffText, termCoefficient)) {
					return false;
				}
				coefficient += termCoefficient;
			}
			hasX = true;
		}
		else {
			long double termConstant = 0.0L;
			if (!parseSolverLinearNumber(term, termConstant)) {
				return false;
			}
			constant += termConstant;
		}
		start = end;
	}
	if (!hasX || fabsl(coefficient) < 1E-30L) {
		return false;
	}
	solution = -constant / coefficient;
	return true;
}

static std::string stripSolverBalancedOuterParentheses(const std::string& source) {
	std::string text = source;
	bool changed = true;
	while (changed && text.size() >= 2 && text[0] == '(' && text[text.size() - 1] == ')') {
		changed = false;
		int level = 0;
		bool wrapsWholeExpression = true;
		for (size_t i = 0; i < text.size(); i++) {
			if (text[i] == '(') {
				level++;
			}
			else if (text[i] == ')') {
				level--;
				if (level == 0 && i != text.size() - 1) {
					wrapsWholeExpression = false;
					break;
				}
			}
			if (level < 0) {
				wrapsWholeExpression = false;
				break;
			}
		}
		if (wrapsWholeExpression && level == 0) {
			text = text.substr(1, text.size() - 2);
			changed = true;
		}
	}
	return text;
}

static bool trySolveSolverLinearProductExpression(const std::string& expression, long double& solution) {
	std::string text;
	text.reserve(expression.size());
	for (size_t i = 0; i < expression.size(); i++) {
		if (!std::isspace((unsigned char)expression[i])) {
			text.push_back(expression[i]);
		}
	}
	text = stripSolverBalancedOuterParentheses(text);
	if (text.empty() || text[0] != '(') {
		return false;
	}
	size_t i = 0;
	while (i < text.size()) {
		if (text[i] != '(') {
			return false;
		}
		int level = 0;
		size_t start = i;
		for (; i < text.size(); i++) {
			if (text[i] == '(') {
				level++;
			}
			else if (text[i] == ')') {
				level--;
				if (level == 0) {
					break;
				}
			}
			if (level < 0) {
				return false;
			}
		}
		if (i >= text.size()) {
			return false;
		}
		std::string factor = stripSolverBalancedOuterParentheses(text.substr(start + 1, i - start - 1));
		if (trySolveSolverLinearExpression(factor, solution)) {
			return true;
		}
		std::string reducedFactor;
		if (reduceExactRationalProductExpression(factor.c_str(), reducedFactor) && reducedFactor != factor &&
			(trySolveSolverLinearExpression(reducedFactor, solution) ||
				trySolveSolverLinearProductExpression(reducedFactor, solution))) {
			return true;
		}
		i++;
		if (i < text.size() && text[i] == '*') {
			i++;
		}
	}
	return false;
}

static bool trySolveSolverLinearProductExpressionComplex(const std::string& expression, std::complex<long double>& solution) {
	std::string text;
	text.reserve(expression.size());
	for (size_t i = 0; i < expression.size(); i++) {
		if (!std::isspace((unsigned char)expression[i])) {
			text.push_back(expression[i]);
		}
	}
	text = stripSolverBalancedOuterParentheses(text);
	if (text.empty() || text[0] != '(') {
		return false;
	}
	size_t i = 0;
	while (i < text.size()) {
		if (text[i] != '(') {
			return false;
		}
		int level = 0;
		size_t start = i;
		for (; i < text.size(); i++) {
			if (text[i] == '(') {
				level++;
			}
			else if (text[i] == ')') {
				level--;
				if (level == 0) {
					break;
				}
			}
			if (level < 0) {
				return false;
			}
		}
		if (i >= text.size()) {
			return false;
		}
		std::string factor = stripSolverBalancedOuterParentheses(text.substr(start + 1, i - start - 1));
		if (trySolveSolverLinearExpressionComplex(factor, solution)) {
			return true;
		}
		std::string reducedFactor;
		if (reduceExactRationalProductExpression(factor.c_str(), reducedFactor) && reducedFactor != factor &&
			(trySolveSolverLinearExpressionComplex(reducedFactor, solution) ||
				trySolveSolverLinearProductExpressionComplex(reducedFactor, solution))) {
			return true;
		}
		i++;
		if (i < text.size() && text[i] == '*') {
			i++;
		}
	}
	return false;
}


static std::complex<double> evaluateSolverPolynomialFallback(const std::vector<std::complex<double>>& coefficients, std::complex<double> x) {
	std::complex<double> value(0.0, 0.0);
	for (int i = (int)coefficients.size() - 1; i >= 0; --i) {
		value = value * x + coefficients[(size_t)i];
	}
	return value;
}

static bool parseSolverPolynomialFallbackNumber(std::string text, double& value) {
	if (text.empty()) {
		return false;
	}
	for (size_t i = 0; i < text.size(); ++i) {
		if (text[i] == '_') {
			text[i] = '-';
		}
	}
	if (text == "+" || text.empty()) {
		value = 1.0;
		return true;
	}
	if (text == "-") {
		value = -1.0;
		return true;
	}
	char* end = nullptr;
	value = std::strtod(text.c_str(), &end);
	return end != text.c_str() && *end == '\0';
}

static bool collectSolverPolynomialFallbackCoefficients(const char* expression, std::vector<std::complex<double>>& coefficients) {
	if (expression == nullptr) {
		return false;
	}
	std::string text(expression);
	std::string normalized;
	for (size_t i = 0; i < text.size(); ++i) {
		if (!std::isspace((unsigned char)text[i])) {
			normalized += text[i];
		}
	}
	if (normalized.empty() || normalized.find('x') == std::string::npos) {
		return false;
	}
	if (normalized.size() >= 2 && normalized[0] == '(' && normalized[normalized.size() - 1] == ')') {
		normalized = normalized.substr(1, normalized.size() - 2);
	}
	std::vector<std::string> terms;
	size_t start = 0;
	for (size_t i = 1; i < normalized.size(); ++i) {
		if (normalized[i] == '+' || normalized[i] == '-') {
			terms.push_back(normalized.substr(start, i - start));
			start = i;
		}
	}
	terms.push_back(normalized.substr(start));
	coefficients.assign(1, std::complex<double>(0.0, 0.0));
	for (size_t i = 0; i < terms.size(); ++i) {
		std::string term = terms[i];
		if (term.empty()) {
			return false;
		}
		size_t xPosition = term.find('x');
		int degree = 0;
		double coefficient = 0.0;
		if (xPosition == std::string::npos) {
			if (!parseSolverPolynomialFallbackNumber(term, coefficient)) {
				return false;
			}
		}
		else {
			std::string prefix = term.substr(0, xPosition);
			if (!prefix.empty() && prefix[prefix.size() - 1] == '*') {
				prefix.erase(prefix.size() - 1);
			}
			if (!parseSolverPolynomialFallbackNumber(prefix, coefficient)) {
				return false;
			}
			degree = 1;
			if (xPosition + 1 < term.size()) {
				if (term[xPosition + 1] != '^') {
					return false;
				}
				char* end = nullptr;
				long parsedDegree = std::strtol(term.c_str() + xPosition + 2, &end, 10);
				if (end == term.c_str() + xPosition + 2 || *end != '\0' || parsedDegree < 0 || parsedDegree > 256) {
					return false;
				}
				degree = (int)parsedDegree;
			}
		}
		if ((size_t)degree >= coefficients.size()) {
			coefficients.resize((size_t)degree + 1, std::complex<double>(0.0, 0.0));
		}
		coefficients[(size_t)degree] += coefficient;
	}
	while (coefficients.size() > 1 && std::abs(coefficients.back()) < 1E-14) {
		coefficients.pop_back();
	}
	return coefficients.size() > 1;
}

static bool parseSolverComplexLiteralFallback(std::string text, std::complex<double>& value) {
	if (text.empty()) {
		return false;
	}
	if (text.size() >= 2 && text[0] == '(' && text[text.size() - 1] == ')') {
		text = text.substr(1, text.size() - 2);
	}
	if (text.find('*') != std::string::npos) {
		std::string withoutStars;
		for (char ch : text) {
			if (ch != '*') {
				withoutStars += ch;
			}
		}
		text = withoutStars;
	}
	if (text.find('i') == std::string::npos) {
		double realValue = 0.0;
		if (!parseSolverPolynomialFallbackNumber(text, realValue)) {
			return false;
		}
		value = std::complex<double>(realValue, 0.0);
		return true;
	}
	if (text[text.size() - 1] != 'i' || text.find('i') != text.size() - 1) {
		return false;
	}
	std::string withoutI = text.substr(0, text.size() - 1);
	size_t split = std::string::npos;
	for (size_t i = 1; i < withoutI.size(); ++i) {
		if (withoutI[i] == '+' || withoutI[i] == '-') {
			split = i;
		}
	}
	double realValue = 0.0;
	double imaginaryValue = 0.0;
	if (split == std::string::npos) {
		if (withoutI.empty() || withoutI == "+") {
			imaginaryValue = 1.0;
		}
		else if (withoutI == "-") {
			imaginaryValue = -1.0;
		}
		else if (!parseSolverPolynomialFallbackNumber(withoutI, imaginaryValue)) {
			return false;
		}
	}
	else {
		if (!parseSolverPolynomialFallbackNumber(withoutI.substr(0, split), realValue)) {
			return false;
		}
		std::string imaginaryText = withoutI.substr(split);
		if (imaginaryText == "+") {
			imaginaryValue = 1.0;
		}
		else if (imaginaryText == "-") {
			imaginaryValue = -1.0;
		}
		else if (!parseSolverPolynomialFallbackNumber(imaginaryText, imaginaryValue)) {
			return false;
		}
	}
	value = std::complex<double>(realValue, imaginaryValue);
	return true;
}

static bool evaluateSolverConstantFallbackExpression(const std::string& expression, std::complex<double>& value) {
	if (expression.empty() || expression.find('x') != std::string::npos) {
		return false;
	}
	std::string text;
	for (char ch : expression) {
		if (!std::isspace((unsigned char)ch)) {
			text += ch == '_' ? '-' : ch;
		}
	}
	double sign = 1.0;
	if (!text.empty() && text[0] == '+') {
		text.erase(0, 1);
	}
	else if (!text.empty() && text[0] == '-') {
		sign = -1.0;
		text.erase(0, 1);
	}
	size_t powerPosition = text.rfind("^");
	if (powerPosition != std::string::npos) {
		char* end = nullptr;
		long exponent = std::strtol(text.c_str() + powerPosition + 1, &end, 10);
		if (end != text.c_str() + powerPosition + 1 && *end == '\0' && exponent >= 0 && exponent <= 32) {
			std::complex<double> base;
			if (parseSolverComplexLiteralFallback(text.substr(0, powerPosition), base)) {
				value = std::complex<double>(sign, 0.0);
				for (long i = 0; i < exponent; ++i) {
					value *= base;
				}
				return std::isfinite(value.real()) && std::isfinite(value.imag());
			}
		}
	}
	if (parseSolverComplexLiteralFallback(text, value)) {
		value *= sign;
		return std::isfinite(value.real()) && std::isfinite(value.imag());
	}
	return false;
}

static bool splitSolverTopLevelPolynomialTerms(const std::string& expression, std::vector<std::string>& terms) {
	std::string text;
	for (char ch : expression) {
		if (!std::isspace((unsigned char)ch)) {
			text += ch == '_' ? '-' : ch;
		}
	}
	int level = 0;
	size_t start = 0;
	for (size_t i = 0; i < text.size(); ++i) {
		if (text[i] == '(' || text[i] == '[' || text[i] == '{') {
			level++;
		}
		else if (text[i] == ')' || text[i] == ']' || text[i] == '}') {
			level--;
			if (level < 0) {
				return false;
			}
		}
		else if (i > 0 && level == 0 && (text[i] == '+' || text[i] == '-')) {
			terms.push_back(text.substr(start, i - start));
			start = i;
		}
	}
	if (level != 0) {
		return false;
	}
	terms.push_back(text.substr(start));
	return terms.size() == 2;
}

static bool parseSolverMonomialXPowerTerm(const std::string& term, std::complex<double>& coefficient, int& degree) {
	std::string text = term;
	if (text.empty()) {
		return false;
	}
	double sign = 1.0;
	if (text[0] == '+') {
		text.erase(0, 1);
	}
	else if (text[0] == '-') {
		sign = -1.0;
		text.erase(0, 1);
	}
	size_t xPosition = text.find('x');
	if (xPosition == std::string::npos || text.find('x', xPosition + 1) != std::string::npos) {
		return false;
	}
	std::string prefix = text.substr(0, xPosition);
	if (!prefix.empty() && prefix[prefix.size() - 1] == '*') {
		prefix.erase(prefix.size() - 1);
	}
	double coefficientR = 1.0;
	if (!prefix.empty() && !parseSolverPolynomialFallbackNumber(prefix, coefficientR)) {
		return false;
	}
	degree = 1;
	if (xPosition + 1 < text.size()) {
		if (text[xPosition + 1] != '^') {
			return false;
		}
		char* end = nullptr;
		long parsedDegree = std::strtol(text.c_str() + xPosition + 2, &end, 10);
		if (end == text.c_str() + xPosition + 2 || *end != '\0' || parsedDegree < 1 || parsedDegree > 256) {
			return false;
		}
		degree = (int)parsedDegree;
	}
	coefficient = std::complex<double>(sign * coefficientR, 0.0);
	return true;
}

static bool trySolveSolverComplexBinomialFallback(const char* expression, double& rootR, double& rootI) {
	if (expression == nullptr) {
		return false;
	}
	std::vector<std::string> terms;
	if (!splitSolverTopLevelPolynomialTerms(expression, terms)) {
		return false;
	}
	std::complex<double> coefficient(0.0, 0.0), constant(0.0, 0.0);
	int degree = 0;
	bool firstIsMonomial = parseSolverMonomialXPowerTerm(terms[0], coefficient, degree);
	bool secondIsMonomial = parseSolverMonomialXPowerTerm(terms[1], coefficient, degree);
	std::string constantTerm;
	if (firstIsMonomial && !secondIsMonomial) {
		constantTerm = terms[1];
	}
	else if (!firstIsMonomial && secondIsMonomial) {
		constantTerm = terms[0];
	}
	else {
		return false;
	}
	if (degree < 1 || std::abs(coefficient) < 1E-14 || !evaluateSolverConstantFallbackExpression(constantTerm, constant)) {
		return false;
	}
	std::complex<double> target = -constant / coefficient;
	std::complex<double> root;
	if (degree == 1) {
		root = target;
	}
	else if (std::fabs(target.imag()) < 1E-14 && target.real() >= 0.0) {
		root = std::complex<double>(std::pow(target.real(), 1.0 / (double)degree), 0.0);
	}
	else {
		root = std::polar(std::pow(std::abs(target), 1.0 / (double)degree), std::arg(target) / (double)degree);
	}
	if (std::fabs(root.real()) < 1E-9) {
		root.real(0.0);
	}
	if (std::fabs(root.imag()) < 1E-9) {
		root.imag(0.0);
	}
	if (std::fabs(root.real() - std::round(root.real())) < 1E-9) {
		root.real(std::round(root.real()));
	}
	if (std::fabs(root.imag() - std::round(root.imag())) < 1E-9) {
		root.imag(std::round(root.imag()));
	}
	rootR = root.real();
	rootI = root.imag();
	return std::isfinite(rootR) && std::isfinite(rootI);
}

static bool trySolvePolynomialFallbackAfterAdvancedSolver(const char* expression, double& rootR, double& rootI) {
	if (trySolveSolverComplexBinomialFallback(expression, rootR, rootI)) {
		return true;
	}
	std::vector<std::complex<double>> coefficients;
	if (!collectSolverPolynomialFallbackCoefficients(expression, coefficients)) {
		return false;
	}
	int degree = (int)coefficients.size() - 1;
	int nonZeroTerms = 0;
	for (size_t termIndex = 0; termIndex < coefficients.size(); ++termIndex) {
		if (std::abs(coefficients[termIndex]) > 1E-14) {
			nonZeroTerms++;
		}
	}
	if (degree > 1 && nonZeroTerms == 2 && std::abs(coefficients[0]) > 1E-14 && std::abs(coefficients[(size_t)degree]) > 1E-14) {
		std::complex<double> target = -coefficients[0] / coefficients[(size_t)degree];
		std::complex<double> root;
		if (std::fabs(target.imag()) < 1E-14 && target.real() >= 0.0) {
			root = std::complex<double>(std::pow(target.real(), 1.0 / (double)degree), 0.0);
		}
		else {
			double magnitude = std::pow(std::abs(target), 1.0 / (double)degree);
			double angle = std::arg(target) / (double)degree;
			root = std::polar(magnitude, angle);
		}
		if (std::fabs(root.real()) < 1E-9) {
			root.real(0.0);
		}
		if (std::fabs(root.imag()) < 1E-9) {
			root.imag(0.0);
		}
		if (std::fabs(root.real() - std::round(root.real())) < 1E-9) {
			root.real(std::round(root.real()));
		}
		if (std::fabs(root.imag() - std::round(root.imag())) < 1E-9) {
			root.imag(std::round(root.imag()));
		}
		rootR = root.real();
		rootI = root.imag();
		return std::isfinite(rootR) && std::isfinite(rootI);
	}
	if (degree == 1) {
		std::complex<double> root = -coefficients[0] / coefficients[1];
		rootR = root.real();
		rootI = root.imag();
		return std::isfinite(rootR) && std::isfinite(rootI);
	}
	std::vector<std::complex<double>> monic((size_t)degree + 1);
	std::complex<double> leading = coefficients[(size_t)degree];
	if (std::abs(leading) < 1E-14) {
		return false;
	}
	for (int i = 0; i <= degree; ++i) {
		monic[(size_t)i] = coefficients[(size_t)i] / leading;
	}
	std::vector<std::complex<double>> rootsLocal((size_t)degree);
	double radius = 1.0;
	for (int i = 0; i < degree; ++i) {
		radius = std::max(radius, 1.0 + std::abs(monic[(size_t)i]));
	}
	const double twoPi = 2.0 * M_PI;
	for (int i = 0; i < degree; ++i) {
		double angle = twoPi * (double)i / (double)degree;
		rootsLocal[(size_t)i] = std::polar(radius, angle);
	}
	for (int iteration = 0; iteration < 256; ++iteration) {
		double maxDelta = 0.0;
		for (int i = 0; i < degree; ++i) {
			std::complex<double> denominator(1.0, 0.0);
			for (int j = 0; j < degree; ++j) {
				if (i != j) {
					denominator *= rootsLocal[(size_t)i] - rootsLocal[(size_t)j];
				}
			}
			if (std::abs(denominator) < 1E-18) {
				denominator = std::complex<double>(1E-18, 0.0);
			}
			std::complex<double> delta = evaluateSolverPolynomialFallback(monic, rootsLocal[(size_t)i]) / denominator;
			rootsLocal[(size_t)i] -= delta;
			maxDelta = std::max(maxDelta, std::abs(delta));
		}
		if (maxDelta < 1E-12) {
			break;
		}
	}
	int bestIndex = -1;
	double bestResidual = std::numeric_limits<double>::infinity();
	for (int i = 0; i < degree; ++i) {
		double residual = std::abs(evaluateSolverPolynomialFallback(coefficients, rootsLocal[(size_t)i]));
		if (residual < bestResidual - 1E-8 ||
			(std::fabs(residual - bestResidual) <= 1E-8 && bestIndex >= 0 && rootsLocal[(size_t)i].imag() > rootsLocal[(size_t)bestIndex].imag())) {
			bestResidual = residual;
			bestIndex = i;
		}
	}
	if (bestIndex < 0 || bestResidual > 1E-5) {
		return false;
	}
	std::complex<double> root = rootsLocal[(size_t)bestIndex];
	rootR = std::fabs(root.real()) < 1E-9 ? 0.0 : root.real();
	rootI = std::fabs(root.imag()) < 1E-9 ? 0.0 : root.imag();
	if (std::fabs(rootR - std::round(rootR)) < 1E-9) {
		rootR = std::round(rootR);
	}
	if (std::fabs(rootI - std::round(rootI)) < 1E-9) {
		rootI = std::round(rootI);
	}
	return std::isfinite(rootR) && std::isfinite(rootI);
}

template <typename T>
bool isSolved();
template <typename T>
void advancedSolver(char* expression);
static bool validateSolverRootWithInitialProcessor(char* expression, double rootR, double rootI);
static bool trySolveSimpleFunctionByDerivative(char* expression, double& rootR, double& rootI);

template<typename T>
T solver(char* expression) {
	char* data = getDynamicCharArray("", "data");
	replaceTimes = 0;
	poly = true;
	char* equation = getDynamicCharArray("", "equation"); char* saveEquation = getDynamicCharArray("", "saveEquation"); char* notSolvedEquation = getDynamicCharArray("", "notSolvedEquation");
	sprintf(saveEquation, "%s", expression);
	sprintf(equation, "%s", expression);
	sprintf(notSolvedEquation, "%s", expr);
	std::string solverExpression(expression != nullptr ? expression : "");
	std::string reducedRationalProduct;
	if (reduceExactRationalProductExpression(solverExpression.c_str(), reducedRationalProduct)) {
		solverExpression = reducedRationalProduct;
		sprintf(saveEquation, "%s", solverExpression.c_str());
		sprintf(equation, "%s", solverExpression.c_str());
	}
std::complex<long double> complexLinearSolution(0.0L, 0.0L);
	if (trySolveSolverLinearExpressionComplex(solverExpression, complexLinearSolution) ||
		trySolveSolverLinearProductExpressionComplex(solverExpression, complexLinearSolution)) {
		resultR = (T)complexLinearSolution.real();
		resultI = (T)complexLinearSolution.imag();
		verified = 1;
		_delete(equation, "equation"); equation = nullptr;
		_delete(saveEquation, "saveEquation"); saveEquation = nullptr;
		_delete(notSolvedEquation, "notSolvedEquation"); notSolvedEquation = nullptr;
		_delete(data, "data"); data = nullptr;
		return (T)complexLinearSolution.real();
	}
	double complexBinomialRootR = 0.0, complexBinomialRootI = 0.0;
	if (trySolveSolverComplexBinomialFallback(solverExpression.c_str(), complexBinomialRootR, complexBinomialRootI)) {
		resultR = complexBinomialRootR;
		resultI = complexBinomialRootI;
		verified = 1;
		_delete(equation, "equation"); equation = nullptr;
		_delete(saveEquation, "saveEquation"); saveEquation = nullptr;
		_delete(notSolvedEquation, "notSolvedEquation"); notSolvedEquation = nullptr;
		_delete(data, "data"); data = nullptr;
		return precisionValueTo<T>(resultR);
	}
	double simpleFunctionRootR = 0.0, simpleFunctionRootI = 0.0;
	if (trySolveSimpleFunctionByDerivative(expression, simpleFunctionRootR, simpleFunctionRootI) &&
		validateSolverRootWithInitialProcessor(expression, simpleFunctionRootR, simpleFunctionRootI)) {
		resultR = simpleFunctionRootR;
		resultI = simpleFunctionRootI;
		verified = 1;
		_delete(equation, "equation"); equation = nullptr;
		_delete(saveEquation, "saveEquation"); saveEquation = nullptr;
		_delete(notSolvedEquation, "notSolvedEquation"); notSolvedEquation = nullptr;
		_delete(data, "data"); data = nullptr;
		return precisionValueTo<T>(resultR);
	}
	if (isContained("\\", expression)) {
		int d = 0, check_integral = 0;;
		for (d = 0; d < abs((int)strlen(expression)); d++) {
			if (expression[d] == '\\') {
				check_integral++;
			}
		}
		if (check_integral == 2) {
			d = 0;
			int e = 0;
			char* getValue = getDynamicCharArray("", "getValue");
			while (expression[d] != '\\') {
				getValue[e] = expression[d];
				e++;
				d++;
			}
			getValue[e] = '\0';
			T a = solveMath<T>(getValue);
			d++;
			e = 0;
			sprintf(getValue, "");
			while (expression[d] != '\\') {
				getValue[e] = expression[d];
				e++;
				d++;
			}
			getValue[e] = '\0';
			T b = solveMath<T>(getValue);
			d++;
			char* function = getDynamicCharArray("", "function");
			e = 0;
			while (d < abs((int)strlen(expression))) {
				function[e] = expression[d];
				e++;
				d++;
			}
			function[e] = '\0';
			T area = calculateIntegral(a, b, function);
			sprintf(saveSimplified, "");
			sprintf(saveSimplification, "");
			sprintf(expressionF, "");
			sprintf(roots, "");
			poly = false;
			_delete(equation, "equation"); equation = nullptr;
			_delete(saveEquation, "saveEquation"); saveEquation = nullptr;
			_delete(notSolvedEquation, "notSolvedEquation"); notSolvedEquation = nullptr;
			_delete(getValue, "getValue"); getValue = nullptr;
			_delete(function, "function"); function = nullptr;
			_delete(data, "data");

			return area;
		}
	}
	bool to_solve = dataVerifier<T>(equation, (T)0, (T)0, 0, 1);
	solverRunning = true;

	if (to_solve) {
		if (poly) {
			equation_solver = true;
			notUseHigherPrecison = true;
			polySimplifier = false;
			sprintf(saveSimplified, "");
			sprintf(saveSimplification, "");
			sprintf(expressionF, "");
			sprintf(roots, "");
			sprintf(saveEquation, "%s", expression);
			sprintf(equation, "%s", saveEquation);
			equation_solver = true;
			resultR = 0; resultI = 0;
			lastDividerR = 1, lastDividerI = 0, natureValue = 1;
			sprintf(roots, ""), sprintf(answers, "");
			isDivisible = true;
			lastDividerR = 1, lastDividerI = 0;
			polySimplifier = false;

			sprintf(data, "%s", equation);
			sprintf(saveExpressionF, "%s", data);
			if (!isContained("\\", data)) {
				synTest = 0;
				if (dataVerifier<T>(data, (T)0, (T)0, 0, 1)) {
					sprintf(OutputText, "");
					replaceTimes = 0;
					lastDividerR = 0;
					LastDividerR = 0;
					lastDividerI = 0;
					LastDividerI = 0;
				}
			}
			replaceTimes = 0;
			sprintf(saveSimplified, "%s", expressionF);
			resultR = 0; resultI = 0;
			double earlyPolynomialRootR = 0.0, earlyPolynomialRootI = 0.0;
			bool solvedByPolynomialIsolation = trySolvePolynomialFallbackAfterAdvancedSolver(data, earlyPolynomialRootR, earlyPolynomialRootI) ||
				trySolvePolynomialFallbackAfterAdvancedSolver(expression, earlyPolynomialRootR, earlyPolynomialRootI) ||
				trySolvePolynomialFallbackAfterAdvancedSolver(saveEquation, earlyPolynomialRootR, earlyPolynomialRootI);
			if (solvedByPolynomialIsolation) {
				resultR = earlyPolynomialRootR;
				resultI = earlyPolynomialRootI;
			}
			else {
				advancedSolver<T>(data);
			}
			solverRunning = false;
			equationSolverRunning = false;
			poly = false;
			sprintf(saveSimplified, "");
			sprintf(saveSimplification, "");
			sprintf(expressionF, "");
			sprintf(roots, "");
			if (resultR != -765432 && resultI != 234567) {
				_delete(equation, "equation"); equation = nullptr;
				_delete(saveEquation, "saveEquation"); saveEquation = nullptr;
				_delete(notSolvedEquation, "notSolvedEquation"); notSolvedEquation = nullptr;
				_delete(data, "data");

				return precisionValueTo<T>(resultR);
			}
			else {
				double fallbackRootR = 0.0, fallbackRootI = 0.0;
				if (trySolvePolynomialFallbackAfterAdvancedSolver(data, fallbackRootR, fallbackRootI)) {
					resultR = fallbackRootR;
					resultI = fallbackRootI;
					solverRunning = false;
					equationSolverRunning = false;
					poly = false;
					_delete(equation, "equation"); equation = nullptr;
					_delete(saveEquation, "saveEquation"); saveEquation = nullptr;
					_delete(notSolvedEquation, "notSolvedEquation"); notSolvedEquation = nullptr;
					_delete(data, "data"); data = nullptr;
					return (T)fallbackRootR;
				}
				poly = true;
				replaceTimes = 0;
				if (isContained("res", data)) {
					replace("res", "x", data);
					sprintf(data, "%s", expressionF);
				}
				manageExpression<T>(data, (T)0, (T)0, 1);
				sprintf(data, "%s", expressionF);
				replaceTimes = 0;
				if (isContained("(x)", data)) {
					replace("(x)", "x", data);
					sprintf(data, "%s", expressionF);
				}
				simplifyExpression(data);
				sprintf(data, "%s", expressionF);
				sprintf(answers, "");
				equationSolver<T>(data);
				int i = 0, j = 0, z = 0;
				T* zeroR = getDynamicArray<T>(DIMDOUBLE);
				T* zeroI = getDynamicArray<T>(DIMDOUBLE);
				char* value = getDynamicCharArray("", "value");
				replaceTimes = 0;
				char* saveExpF = getDynamicCharArray("", "saveExpF");
				sprintf(saveExpF, "%s", answers);
				while (isContained("=", saveExpF)) {
					j = 0;
					i = strEnd;
					saveExpF[strStart] = ' ';
					while (i < abs((int)strlen(saveExpF)) && saveExpF[i] != '\n') {
						value[j] = saveExpF[i];
						i++; j++;
					}
					value[j] = '\0';
					replaceTimes = 1;
					if (isContained("-", value) && strStart == 0) {
						replace("-", "_", value);
						sprintf(value, "%s", expressionF);
					}
					solveMath<T>(value);
					zeroR[z] = precisionValueTo<T>(resultR); zeroI[z] = precisionValueTo<T>(resultI);
					z++;
					if (zeroI[z - 1] != 0 || zeroR[z - 1] != 0) {
						break;
					}
				}
				T saveResultR = zeroR[z - 1], saveResultI = zeroI[z - 1];
				xValuesR = saveResultR;
				xValuesI = saveResultI;
				solverRunning = true;
				replaceTimes = 0;
				if (isContained("x", equation)) {
					replace("x", "res", equation);
					sprintf(equation, "%s", expressionF);
				}
				solveMath<T>(equation);
				if (abs(precisionValueTo<T>(resultR)) < 1E-2 && abs(precisionValueTo<T>(resultI)) < 1E-2) {
					resultR = saveResultR;
					resultI = saveResultI;
					solverRunning = false;
					equationSolverRunning = false;
					poly = false;
					sprintf(saveSimplified, "");
					sprintf(saveSimplification, "");
					sprintf(expressionF, "");
					sprintf(roots, "");
					_delete(equation, "equation"); equation = nullptr;
					_delete(saveEquation, "saveEquation"); saveEquation = nullptr;
					_delete(notSolvedEquation, "notSolvedEquation"); notSolvedEquation = nullptr;
					_delete(data, "data");
					_delete(value, "value"); value = nullptr;
					return precisionValueTo<T>(resultR);
				}

				_delete(saveExpF, "saveExpF"); saveExpF = nullptr;
				_delete(value, "value"); value = nullptr;
			}



		}

		poly = false;
		if (isContained("x", expression)) {
			replace("x", "res", expression);
			sprintf(expression, "%s+1-1", expressionF);
		}
		solverRunning = true;
		solving = false;
		resultR = 0; resultI = 0;
		T precisionR = 0.01, precisionI = 0, resultFR = -0.1, resultFI = 0, savePrecisionR = 0.01, savePrecisionI = 0, saveResultR = -0.1, saveResultI = 0;
		char* Xequal = getDynamicCharArray("", "Xequal");
		int timesToEvaluate = 300, timesEvaluated = 0, interactions = 30;
		bool initialR = true, initialI = true, imaginary = true, counter = true;
		if (retrySolver) {
			precisionI = 0.01; resultFI = -0.1;
			savePrecisionI = 0.01; saveResultI = -0.1;
		}
		resultR = resultFR;
		resultI = resultFI;
		xValuesR = resultFR; xValuesI = resultFI; saveResultR = -0.1; saveResultI = 0;
		if ((retrySolver == (bool)false || retrySolver) && retrySolver_2 == (bool)false && retrySolver_3 == (bool)false) {
			xValuesR = resultFR; xValuesI = resultFI;
			while (isSolved<T>() == false && timesEvaluated < timesToEvaluate) {
				timesEvaluated++;
				if (resultFR >= (saveResultR * -1) || initialR) {
					saveResultR = saveResultR * 10;
					savePrecisionR = savePrecisionR * 10;
					precisionR = savePrecisionR;
					resultFR = saveResultR;
					initialR = false;
				}
				if (retrySolver) {
					if (resultFI >= (saveResultI * -1) || initialI) {
						saveResultI = saveResultI * 10;
						savePrecisionI = savePrecisionI * 10;
						precisionI = savePrecisionI;
						resultFI = saveResultI;
						initialI = false;
					}
				}
				while (precisionValueTo<T>(resultR) != 0 && resultFR < (saveResultR * -1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0) {
					timesEvaluated++;
					xValuesR = resultFR; xValuesI = resultFI;
					solveMath<T>(equation);
					if (precisionValueTo<T>(resultR) < 0) {
						do {
							timesEvaluated++;
							if (precisionValueTo<T>(resultR) < 0) {
								resultFR = resultFR + precisionR;
								xValuesR = resultFR; xValuesI = resultFI;
								solveMath<T>(equation);
							}
							if (precisionValueTo<T>(resultR) > 0) {
								resultFR = resultFR - precisionR;
								precisionR = precisionR / 10;
								xValuesR = resultFR; xValuesI = resultFI;
								solveMath<T>(equation);
							}
						} while (precisionValueTo<T>(resultR) != 0 && resultFR < (saveResultR * -1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
					}
					else {
						do {
							timesEvaluated++;
							if (precisionValueTo<T>(resultR) > 0) {
								resultFR = resultFR + precisionR;
								xValuesR = resultFR; xValuesI = resultFI;
								solveMath<T>(equation);
							}
							else {
								if (precisionValueTo<T>(resultR) < 0) {
									resultFR = resultFR - precisionR;
									precisionR = precisionR / 10;
									xValuesR = resultFR; xValuesI = resultFI;
									solveMath<T>(equation);
								}
							}
						} while (precisionValueTo<T>(resultR) != 0 && resultFR < (saveResultR * -1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
					}
					if (precisionValueTo<T>(resultR) == 0) {
						break;
					}
				}
				timesEvaluated++;
				if (retrySolver) {
					while (precisionValueTo<T>(resultI) != 0 && resultFI < (saveResultI * -1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0) {
						timesEvaluated++;
						xValuesR = resultFR; xValuesI = resultFI;
						solveMath<T>(equation);
						if (precisionValueTo<T>(resultI) < 0) {
							do {
								timesEvaluated++;
								if (precisionValueTo<T>(resultI) < 0) {
									resultFI = resultFI + precisionI;
									xValuesR = resultFR; xValuesI = resultFI;
									solveMath<T>(equation);
								}
								if (precisionValueTo<T>(resultI) > 0) {
									resultFI = resultFI - precisionI;
									precisionI = precisionI / 10;
									xValuesR = resultFR; xValuesI = resultFI;
									solveMath<T>(equation);
								}
							} while (precisionValueTo<T>(resultI) != 0 && resultFI < (saveResultI * -1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
						}
						else {
							do {
								timesEvaluated++;
								if (precisionValueTo<T>(resultI) > 0) {
									resultFI = resultFI + precisionI;
									xValuesR = resultFR; xValuesI = resultFI;
									solveMath<T>(equation);
								}
								else {
									if (precisionValueTo<T>(resultI) < 0) {
										resultFI = resultFI - precisionI;
										precisionI = precisionI / 10;
										xValuesR = resultFR; xValuesI = resultFI;
										solveMath<T>(equation);
									}
								}
							} while (precisionValueTo<T>(resultI) != 0 && resultFI < (saveResultI * -1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
						}
						if (precisionValueTo<T>(resultI) == 0) {
							break;
						}
					}
				}
			}
		}
		else {
			if (retrySolver_2 && retrySolver == (bool)false && retrySolver_3 == (bool)false) {
				xValuesR = 1E9; xValuesI = 0;
				solveMath<T>(equation);
				T minMaxR = precisionValueTo<T>(resultR), minMaxI = precisionValueTo<T>(resultI);
				int i = 0, j = 0, interval = 499, c = 1, d = 0;
				int* x_values = getDynamicArray<int>(1000);
				T* y_valuesR = getDynamicArray<T>(1000);
				T* y_valuesI = getDynamicArray<T>(1000);
				int firstValueR = 0, secondValueR = 0, selected_X = 0;
				for (i = -interval; i < interval; i++) {
					xValuesR = (T)i; xValuesI = 0;
					solveMath<T>(equation);
					x_values[j] = i;
					y_valuesR[j] = precisionValueTo<T>(resultR);
					y_valuesI[j] = precisionValueTo<T>(resultI);
					j++;
				}
				bool zero = false;
				while (i < 2 * interval - 2) {
					for (i = d; i < 2 * interval - 2; i++) {
						if (y_valuesR[i] > y_valuesR[i + 1] && y_valuesR[i + 3] > y_valuesR[i + 4] && y_valuesR[i + 3] > y_valuesR[i + 1]) {
							firstValueR = x_values[i + 2];
							secondValueR = x_values[i + 4];
							selected_X = x_values[i + 3];
							zero = true;
							break;
						}
						if (y_valuesR[i] < y_valuesR[i + 1] && y_valuesR[i + 3] < y_valuesR[i + 4] && y_valuesR[i + 3] < y_valuesR[i + 1]) {
							firstValueR = x_values[i + 2];
							secondValueR = x_values[i + 4];
							selected_X = x_values[i + 3];
							zero = true;
							break;
						}
					}
					if (zero) {
						zero = false;
						if (y_valuesR[firstValueR] != INF * 2 && y_valuesR[secondValueR] != INF * 2 && y_valuesR[selected_X] != INF * 2) {
							xValuesR = firstValueR; xValuesI = 0;
							T negYR = solveMath<T>(equation);
							T negYI = precisionValueTo<T>(resultI);
							xValuesR = secondValueR; xValuesI = 0;
							T posYR = solveMath<T>(equation);
							T posYI = precisionValueTo<T>(resultI);
							T dividend = (((negYR + negYI) - (posYR + posYI)) * -1) / 2;
							division<T>(dividend, 0, minMaxR, minMaxI);
							multiplication<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), -1, 0);
							sum<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), selected_X, 0);
							if (precisionValueTo<T>(resultR) > mINF && precisionValueTo<T>(resultR)<INF && precisionValueTo<T>(resultI)>mINF && precisionValueTo<T>(resultI) < INF) {
								resultFR = precisionValueTo<T>(resultR); resultFI = precisionValueTo<T>(resultI);
								if (physics == (bool)false) {
								}
								xValuesR = resultFR; xValuesI = resultFI;
								solveMath<T>(equation);
								c++;
							}
						}
						d = i + 1;
					}
					i++;
				}
				xValuesR = resultFR; xValuesI = resultFI;
				solveMath<T>(equation);
				_delete(x_values, "x_values");
				x_values = nullptr;
				_delete(y_valuesR, "y_valuesR");
				y_valuesR = nullptr;
				_delete(y_valuesI, "y_valuesI");
				y_valuesI = nullptr;
			}
		}
		if ((retrySolver == (bool)false && retrySolver_2 == (bool)false && retrySolver_3 == (bool)false && ((precisionValueTo<T>(resultR) > -1E-2 && precisionValueTo<T>(resultR) < 1E-2) == false || (precisionValueTo<T>(resultI) > -1E-2 && precisionValueTo<T>(resultI) < 1E-2) == false)) && equationSolverRunning == (bool)false) {
			retrySolver = true;
			solverRunning = true;
			solver<T>(expression);
			resultFR = precisionValueTo<T>(resultR); resultFI = precisionValueTo<T>(resultI);
			solverRunning = false;
			solving = true;
			equationSolverRunning = false;
			sprintf(saveSimplified, "");
			sprintf(saveSimplification, "");
			sprintf(expressionF, "");
			sprintf(roots, "");
			_delete(equation, "equation"); equation = nullptr;
			_delete(saveEquation, "saveEquation"); saveEquation = nullptr;
			_delete(notSolvedEquation, "notSolvedEquation"); notSolvedEquation = nullptr;
			_delete(data, "data");
			_delete(Xequal, "Xequal"); Xequal = nullptr;

			return resultFR;
		}
		if ((retrySolver && retrySolver_2 == (bool)false && retrySolver_3 == (bool)false && ((precisionValueTo<T>(resultR) > -1E-7 && precisionValueTo<T>(resultR) < 1E-7) == false || (precisionValueTo<T>(resultI) > -1E-7 && precisionValueTo<T>(resultI) < 1E-7) == false)) && equationSolverRunning == (bool)false) {
			retrySolver = false;
			retrySolver_2 = true;
			solverRunning = true;
			solver<T>(expression);
			resultFR = precisionValueTo<T>(resultR); resultFI = precisionValueTo<T>(resultI);
			solverRunning = false;
			equationSolverRunning = false;
			solving = true;
			puts("");
			sprintf(saveSimplified, "");
			sprintf(saveSimplification, "");
			sprintf(expressionF, "");
			sprintf(roots, "");
			_delete(equation, "equation"); equation = nullptr;
			_delete(saveEquation, "saveEquation"); saveEquation = nullptr;
			_delete(notSolvedEquation, "notSolvedEquation"); notSolvedEquation = nullptr;
			_delete(data, "data");
			_delete(Xequal, "Xequal"); Xequal = nullptr;

			return resultFR;
		}
		if ((retrySolver == (bool)false && retrySolver_2 && retrySolver_3 == (bool)false && ((precisionValueTo<T>(resultR) > -1 && precisionValueTo<T>(resultR) < 1) == false || (precisionValueTo<T>(resultI) > -1 && precisionValueTo<T>(resultI) < 1) == false)) && equationSolverRunning == (bool)false) {
			retrySolver_2 = false;
			retrySolver_3 = true;
			solverRunning = true;
			solver<T>(expression);
			resultFR = precisionValueTo<T>(resultR); resultFI = precisionValueTo<T>(resultI);
			solverRunning = false;
			equationSolverRunning = false;
			solving = true;
			sprintf(saveSimplified, "");
			sprintf(saveSimplification, "");
			sprintf(expressionF, "");
			sprintf(roots, "");
			_delete(equation, "equation"); equation = nullptr;
			_delete(saveEquation, "saveEquation"); saveEquation = nullptr;
			_delete(notSolvedEquation, "notSolvedEquation"); notSolvedEquation = nullptr;
			_delete(data, "data");
			_delete(Xequal, "Xequal"); Xequal = nullptr;

			return resultFR;
		}
		resultR = resultFR; resultI = resultFI;
		solverRunning = false;
		equationSolverRunning = false;
		solving = true;
		sprintf(saveSimplified, "");
		sprintf(saveSimplification, "");
		sprintf(expressionF, "");
		sprintf(roots, "");
		if (resultFR == -0.1) {
			printf("\\nATC was unable to find a valid solution.\\n\\n");
			feedbackValidation = 1;
		}
		_delete(equation, "equation"); equation = nullptr;
		_delete(saveEquation, "saveEquation"); saveEquation = nullptr;
		_delete(notSolvedEquation, "notSolvedEquation"); notSolvedEquation = nullptr;
		_delete(Xequal, "Xequal"); Xequal = nullptr;
		_delete(data, "data");

		return resultFR;
	}
	else {
		puts("\n\nYour expression has errors.\n\n");
		solverRunning = false;
		equationSolverRunning = false;
		solving = true;
		sprintf(saveSimplified, "");
		sprintf(saveSimplification, "");
		sprintf(expressionF, "");
		sprintf(roots, "");
		_delete(equation, "equation"); equation = nullptr;
		_delete(saveEquation, "saveEquation"); saveEquation = nullptr;
		_delete(notSolvedEquation, "notSolvedEquation"); notSolvedEquation = nullptr;
		_delete(data, "data");

		return NULL;
	}
	solverRunning = false;
	equationSolverRunning = false;
	solving = true;
	sprintf(saveSimplified, "");
	sprintf(saveSimplification, "");
	sprintf(expressionF, "");
	sprintf(roots, "");
	_delete(equation, "equation"); equation = nullptr;
	_delete(saveEquation, "saveEquation"); saveEquation = nullptr;
	_delete(notSolvedEquation, "notSolvedEquation"); notSolvedEquation = nullptr;

	return NULL;
}


template <typename T>

bool isSolved() {
	if (resultR == 0 && resultI == 0) {
		return true;
	}
	return false;
}




template <typename T>
void advancedSolver(char* expression) {
	rasf = 0;
	bool foundNotValid = false;
	xValuesR = M_PI / 2; xValuesI = 0;
	T xValueR = (T)(M_PI / 2), xValueI = 0, previousSolR = (T)(M_PI / 2), previousSolI = 0;
	int i = 0;
	T deltaxR = (T)(M_PI / 2), deltaxI = 0;
	char* toSolve = getDynamicCharArray("", "toSolve"); 	char* toHelp = getDynamicCharArray("", "toHelp");
	T fxDevR = 1, fxDevI = 0;
	replaceTimes = 0;
	replace("x", "res", expression);
	sprintf(toSolve, "%s", expressionF);
	solverRunning = true;
	T solR = 1, solI = 0;
	while (i < 175) {
		xValuesR = xValueR; xValuesI = xValueI;
		initialProcessor<T>(toSolve, (T)0);
		T fxR = precisionValueTo<T>(resultR), fxI = precisionValueTo<T>(resultI);
		xValuesR = xValueR + deltaxR;
		xValuesI = xValueI + deltaxI;

		initialProcessor<T>(toSolve, (T)0);
		T fxplusaR = precisionValueTo<T>(resultR), fxplusaI = precisionValueTo<T>(resultI);

		subtraction<T>(fxplusaR, fxplusaI, fxR, fxI);
		division<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), deltaxR, deltaxI);
		if (precisionValueTo<T>(resultR) != 0 || precisionValueTo<T>(resultI) != 0) {
			fxDevR = precisionValueTo<T>(resultR), fxDevI = precisionValueTo<T>(resultI);
		}

		division<T>(fxR, fxI, fxDevR, fxDevI);
		subtraction<T>(xValueR, xValueI, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
		if (abs(previousSolR - solR) < 1E-6 && abs(previousSolI - solI) < 1E-6) {
			T xR1, xR2, xI1, xI2, resR1, resR2, resI1, resI2;
			if (abs(precisionValueTo<T>(resultR)) < 1E-6)
			{
				resultR = 0;
			}
			if (abs(precisionValueTo<T>(resultI)) < 1E-6)
			{
				resultI = 0;
			}
			xR1 = quo(precisionValueTo<T>(resultR)); xI1 = quo(precisionValueTo<T>(resultI));
			xR2 = precisionValueTo<T>(resultR); xI2 = precisionValueTo<T>(resultI);

			xValuesR = xR1; xValuesI = xI1;
			initialProcessor<T>(toSolve, (T)0);
			resR1 = precisionValueTo<T>(resultR); resI1 = precisionValueTo<T>(resultI);
			xValuesR = xR2; xValuesI = xI2;
			initialProcessor<T>(toSolve, (T)0);
			resR2 = precisionValueTo<T>(resultR); resI2 = precisionValueTo<T>(resultI);
			if (abs(resR2) >= abs(resR1) && abs(resI2) >= abs(resI1)) {
				solR = xR1; solI = xI1;

			}
			else {
				solR = xR2; solI = xI2;
			}
			break;

		}
		else {
			xValueR = precisionValueTo<T>(resultR); xValueI = precisionValueTo<T>(resultI);
			previousSolR = solR; previousSolI = solI;
			solR = xValueR; solI = xValueI;
		}
		i++;
	}
	if (i < 175) {
		int mode = 1;
		T saveResultR = solR, saveResultI = solI;
		while (mode < 4) {
			if (mode == 1) {
				re_complex<T>(saveResultR, saveResultI, 2 * M_PI, 0.0);
			}
			if (mode == 2) {
				re_complex<T>(saveResultR, saveResultI, 360, 0.0);
			}
			if (mode == 3) {
				re_complex<T>(saveResultR, saveResultI, 400, 0.0);
			}
			T savePossibleSolR = precisionValueTo<T>(resultR), savePossibleSolI = precisionValueTo<T>(resultI);
			xValuesR = savePossibleSolR; xValuesI = savePossibleSolI;
			initialProcessor<T>(toSolve, (T)0);
			T fxR = precisionValueTo<T>(resultR), fxI = precisionValueTo<T>(resultI);
			if (abs(fxR) < 1E-6 && abs(fxI) < 1E-6) {
				solR = savePossibleSolR; solI = savePossibleSolI;
				resultR = solR; resultI = solI;
				break;
			}
			mode++;
		}
		if (mode == 4) {
			resultR = saveResultR; resultI = saveResultI;
		}
	}
	else {
		resultR = -765432; resultI = 234567;
	}
	_delete(toSolve, "toSolve"); toSolve = nullptr;
	_delete(toHelp, "toHelp"); toHelp = nullptr;

	solverRunning = false;
}

template <typename T>
static T solverAbs(T value) {
	return value < (T)0 ? -value : value;
}

static bool parseSolverComplexConstant(const std::string& source, std::complex<double>& value) {
	std::string text;
	for (char ch : source) {
		if (!std::isspace((unsigned char)ch)) {
			text += ch == '_' ? '-' : ch;
		}
	}
	value = std::complex<double>(0.0, 0.0);
	size_t index = 0;
	while (index < text.size()) {
		double sign = 1.0;
		if (text[index] == '+') {
			++index;
		}
		else if (text[index] == '-') {
			sign = -1.0;
			++index;
		}
		char* endPtr = nullptr;
		double number = std::strtod(text.c_str() + index, &endPtr);
		if (endPtr == text.c_str() + index) {
			if (index < text.size() && text[index] == 'i') {
				number = 1.0;
			}
			else {
				return false;
			}
		}
		else {
			index = static_cast<size_t>(endPtr - text.c_str());
		}
		if (index + 2 <= text.size() && text[index] == '*' && text[index + 1] == '1') {
			index += 2;
		}
		if (index < text.size() && text[index] == 'i') {
			value += std::complex<double>(0.0, sign * number);
			++index;
		}
		else {
			value += std::complex<double>(sign * number, 0.0);
		}
	}
	return true;
}

static bool extractFullSolverFunctionArgument(const std::string& text, const std::string& functionName, std::string& argument) {
	std::string prefix = functionName + "(";
	if (text.compare(0, prefix.size(), prefix) != 0) {
		return false;
	}
	int depth = 0;
	for (size_t index = prefix.size() - 1; index < text.size(); ++index) {
		if (text[index] == '(') {
			++depth;
		}
		else if (text[index] == ')') {
			--depth;
			if (depth == 0) {
				if (index != text.size() - 1) {
					return false;
				}
				argument = text.substr(prefix.size(), index - prefix.size());
				return true;
			}
			if (depth < 0) {
				return false;
			}
		}
	}
	return false;
}

static bool evaluateSolverTargetExpression(const std::string& source, std::complex<double>& value) {
	std::string text;
	for (char ch : source) {
		if (!std::isspace((unsigned char)ch)) {
			text += ch == '_' ? '-' : ch;
		}
	}
	if (text.empty()) {
		return false;
	}
	if (parseSolverComplexConstant(text, value)) {
		return true;
	}
	const char* inverseFunctions[] = { "asin", "acos", "atan", "asinh", "acosh", "atanh" };
	const char* directFunctions[] = { "sin", "cos", "tan", "sinh", "cosh", "tanh" };
	for (int index = 0; index < 6; ++index) {
		std::string inverseArgument;
		std::string directArgument;
		if (extractFullSolverFunctionArgument(text, inverseFunctions[index], inverseArgument) &&
			extractFullSolverFunctionArgument(inverseArgument, directFunctions[index], directArgument) &&
			evaluateSolverTargetExpression(directArgument, value)) {
			return true;
		}
	}
	if (text.find('x') != std::string::npos) {
		return false;
	}
	double sign = 1.0;
	if (text[0] == '+') {
		text.erase(0, 1);
	}
	else if (text[0] == '-') {
		sign = -1.0;
		text.erase(0, 1);
	}
	if (text.empty()) {
		return false;
	}
	char* targetExpression = getDynamicCharArray(const_cast<char*>(text.c_str()), "targetExpression");
	bool previousSolverRunning = solverRunning;
	solverRunning = true;
	initialProcessor<double>(targetExpression, 0.0);
	solverRunning = previousSolverRunning;
	value = std::complex<double>(sign * precisionValueTo<double>(resultR), sign * precisionValueTo<double>(resultI));
	_delete(targetExpression, "targetExpression");
	targetExpression = nullptr;
	return true;
}

static bool extractSolverSameFunctionArgument(const std::string& source, const std::string& functionName, std::string& argument) {
	std::string text;
	for (char ch : source) {
		if (!std::isspace((unsigned char)ch)) {
			text += ch;
		}
	}
	std::string prefix = "-" + functionName + "(";
	if (text.compare(0, prefix.size(), prefix) != 0 || text.empty()) {
		return false;
	}
	int depth = 0;
	for (size_t index = prefix.size() - 1; index < text.size(); ++index) {
		if (text[index] == '(') {
			++depth;
		}
		else if (text[index] == ')') {
			--depth;
			if (depth == 0) {
				if (index != text.size() - 1) {
					return false;
				}
				argument = text.substr(prefix.size(), index - prefix.size());
				return true;
			}
			if (depth < 0) {
				return false;
			}
		}
	}
	return false;
}

static bool extractSolverFunctionTargetMinusFunctionX(const std::string& source, const std::string& functionName, std::string& argument) {
	std::string text;
	for (char ch : source) {
		if (!std::isspace((unsigned char)ch)) {
			text += ch;
		}
	}
	std::string prefix = functionName + "(";
	if (text.compare(0, prefix.size(), prefix) != 0) {
		return false;
	}
	int depth = 0;
	size_t closeIndex = std::string::npos;
	for (size_t index = prefix.size() - 1; index < text.size(); ++index) {
		if (text[index] == '(') {
			++depth;
		}
		else if (text[index] == ')') {
			--depth;
			if (depth == 0) {
				closeIndex = index;
				break;
			}
			if (depth < 0) {
				return false;
			}
		}
	}
	if (closeIndex == std::string::npos || closeIndex <= prefix.size()) {
		return false;
	}
	std::string suffix = text.substr(closeIndex + 1);
	std::string negativeFunction = "-" + functionName + "(x)";
	std::string internalNegativeFunction = "+_1*" + functionName + "(x)";
	if (suffix != negativeFunction && suffix != internalNegativeFunction) {
		return false;
	}
	argument = text.substr(prefix.size(), closeIndex - prefix.size());
	return true;
}

static int getSolverAngularMode(int explicitAngularMode) {
	if (explicitAngularMode != 0) {
		return explicitAngularMode;
	}
	return applySettings(4);
}

static std::complex<double> convertSolverRootFromInternalDomain(std::complex<double> root, int explicitAngularMode) {
	int angularMode = getSolverAngularMode(explicitAngularMode);
	if (angularMode == 2) {
		return root * (180.0 / M_PI);
	}
	if (angularMode == 3) {
		return root * (200.0 / M_PI);
	}
	return root;
}

static bool validateSolverRootWithInitialProcessor(char* expression, double rootR, double rootI) {
	if (expression == nullptr) {
		return false;
	}
	std::string savedExpressionF(expressionF == nullptr ? "" : expressionF);
	PrecisionValue savedResultR = resultR;
	PrecisionValue savedResultI = resultI;
	PrecisionValue savedXValuesR = xValuesR;
	PrecisionValue savedXValuesI = xValuesI;
	bool savedSolverRunning = solverRunning;
	int savedReplaceTimes = replaceTimes;
	char* validationExpression = getDynamicCharArray("", "solverValidationExpression");

	replaceTimes = 0;
	replace("x", "res", expression);
	sprintf(validationExpression, "%s", expressionF);
	xValuesR = rootR;
	xValuesI = rootI;
	solverRunning = true;
	initialProcessor<double>(validationExpression, 0.0);

	double fxR = precisionValueTo<double>(resultR);
	double fxI = precisionValueTo<double>(resultI);
	bool validated = std::fabs(fxR) < 1E-6 && std::fabs(fxI) < 1E-6;

	sprintf(expressionF, "%s", savedExpressionF.c_str());
	resultR = savedResultR;
	resultI = savedResultI;
	xValuesR = savedXValuesR;
	xValuesI = savedXValuesI;
	solverRunning = savedSolverRunning;
	replaceTimes = savedReplaceTimes;
	_delete(validationExpression, "solverValidationExpression");
	validationExpression = nullptr;
	return validated;
}

static bool trySolveLinearXExpression(char* expression, double& rootR, double& rootI) {
	if (expression == nullptr) {
		return false;
	}
	std::string text;
	for (char ch : std::string(expression)) {
		if (!std::isspace((unsigned char)ch)) {
			text += ch;
		}
	}
	if (text.size() <= 1) {
		return false;
	}
	if (text.compare(0, 2, "x-") == 0 && text.find('x', 1) == std::string::npos) {
		std::complex<double> value;
		if (!evaluateSolverTargetExpression(text.substr(1), value)) {
			return false;
		}
		rootR = value.real();
		rootI = value.imag();
		return true;
	}
	if (text.compare(0, 3, "_x+") == 0 && text.find('x', 2) == std::string::npos) {
		std::complex<double> value;
		if (!evaluateSolverTargetExpression(text.substr(2), value)) {
			return false;
		}
		rootR = value.real();
		rootI = value.imag();
		return true;
	}
	if (text.size() >= 2 && text.compare(text.size() - 2, 2, "-x") == 0 && text.find('x') == text.size() - 1) {
		std::complex<double> value;
		if (!evaluateSolverTargetExpression(text.substr(0, text.size() - 2), value)) {
			return false;
		}
		rootR = value.real();
		rootI = value.imag();
		return true;
	}
	if (text.size() >= 2 && text.compare(text.size() - 2, 2, "_x") == 0 && text.find('x') == text.size() - 1) {
		std::string target = text.substr(0, text.size() - 2);
		if (!target.empty() && target[target.size() - 1] == '+') {
			target.erase(target.size() - 1);
		}
		std::complex<double> value;
		if (!evaluateSolverTargetExpression(target, value)) {
			return false;
		}
		rootR = value.real();
		rootI = value.imag();
		return true;
	}
	if (text.size() >= 5 && text.compare(text.size() - 5, 5, "+_1*x") == 0 && text.find('x') == text.size() - 1) {
		std::complex<double> value;
		if (!evaluateSolverTargetExpression(text.substr(0, text.size() - 5), value)) {
			return false;
		}
		rootR = value.real();
		rootI = value.imag();
		return true;
	}
	return false;
}

static bool trySolveSimpleFunctionByDerivative(char* expression, double& rootR, double& rootI) {
	if (expression == nullptr) {
		return false;
	}
	std::string text(expression);
	struct SolverFunction {
		const char* name;
		int functionIndex;
		int explicitAngularMode;
	};
	const SolverFunction functions[] = {
		{ "sin", 0, 0 }, { "cos", 1, 0 }, { "tan", 2, 0 },
		{ "radsin", 0, 1 }, { "radcos", 1, 1 }, { "radtan", 2, 1 },
		{ "degsin", 0, 2 }, { "degcos", 1, 2 }, { "degtan", 2, 2 },
		{ "gonsin", 0, 3 }, { "goncos", 1, 3 }, { "gontan", 2, 3 },
		{ "sinh", 3, 1 }, { "cosh", 4, 1 }, { "tanh", 5, 1 }
	};
	const int functionCount = sizeof(functions) / sizeof(functions[0]);
	for (int entryIndex = 0; entryIndex < functionCount; ++entryIndex) {
		int functionIndex = functions[entryIndex].functionIndex;
		bool angularFunction = functionIndex < 3;
		std::string invertedSameFunctionArgument;
		if (extractSolverFunctionTargetMinusFunctionX(text, functions[entryIndex].name, invertedSameFunctionArgument)) {
			std::complex<double> argumentValue;
			if (evaluateSolverTargetExpression(invertedSameFunctionArgument, argumentValue)) {
				rootR = argumentValue.real();
				rootI = argumentValue.imag();
				return true;
			}
		}
		std::string prefix = std::string(functions[entryIndex].name) + "(x)";
		if (text.compare(0, prefix.size(), prefix) != 0 || text.size() <= prefix.size()) {
			continue;
		}
		std::string sameFunctionArgument;
		if (extractSolverSameFunctionArgument(text.substr(prefix.size()), functions[entryIndex].name, sameFunctionArgument)) {
			std::complex<double> argumentValue;
			if (evaluateSolverTargetExpression(sameFunctionArgument, argumentValue)) {
				// f(x) - f(a) = 0 always admits x = a. Returning the identity
				// root also avoids re-entering the expression processor from the solver.
				rootR = argumentValue.real();
				rootI = argumentValue.imag();
				return true;
			}
		}
		std::complex<double> constant;
		if (!evaluateSolverTargetExpression(text.substr(prefix.size()), constant)) {
			continue;
		}
		std::complex<double> target = -constant;
		auto evaluate = [&](std::complex<double> x) {
			if (functionIndex == 0) {
				return std::sin(x) - target;
			}
			if (functionIndex == 1) {
				return std::cos(x) - target;
			}
			if (functionIndex == 2) {
				return std::tan(x) - target;
			}
			if (functionIndex == 3) {
				return std::sinh(x) - target;
			}
			if (functionIndex == 4) {
				return std::cosh(x) - target;
			}
			return std::tanh(x) - target;
		};
		auto derivative = [&](std::complex<double> x) {
			if (functionIndex == 0) {
				return std::cos(x);
			}
			if (functionIndex == 1) {
				return -std::sin(x);
			}
			if (functionIndex == 2) {
				std::complex<double> cosX = std::cos(x);
				return 1.0 / (cosX * cosX);
			}
			if (functionIndex == 3) {
				return std::cosh(x);
			}
			if (functionIndex == 4) {
				return std::sinh(x);
			}
			std::complex<double> coshX = std::cosh(x);
			return 1.0 / (coshX * coshX);
		};
		std::complex<double> guesses[] = {
			std::complex<double>(0.0, 0.0),
			target,
			std::complex<double>(target.real(), target.imag()),
			std::complex<double>(0.0, 0.0),
			std::complex<double>(M_PI / 6.0, 0.0),
			std::complex<double>(-M_PI / 6.0, 0.0),
			std::complex<double>(M_PI / 4.0, 0.0),
			std::complex<double>(M_PI / 2.0, 0.0),
			std::complex<double>(1.0, 1.0),
			std::complex<double>(2.0, 2.0),
			std::complex<double>(-2.0, -2.0)
		};
		for (std::complex<double> guess : guesses) {
			std::complex<double> x = guess;
			for (int iteration = 0; iteration < 40; ++iteration) {
				std::complex<double> fx = evaluate(x);
				if (std::abs(fx) < 1E-10) {
					if (angularFunction) {
						x = convertSolverRootFromInternalDomain(x, functions[entryIndex].explicitAngularMode);
					}
					rootR = x.real();
					rootI = x.imag();
					if (std::fabs(rootR - std::round(rootR)) < 1E-9) {
						rootR = std::round(rootR);
					}
					if (std::fabs(rootI - std::round(rootI)) < 1E-9) {
						rootI = std::round(rootI);
					}
					return true;
				}
				std::complex<double> fxDerivative = derivative(x);
				if (std::abs(fxDerivative) < 1E-12) {
					break;
				}
				std::complex<double> next = x - fx / fxDerivative;
				if (!std::isfinite(next.real()) || !std::isfinite(next.imag())) {
					break;
				}
				x = next;
			}
		}
	}
	return false;
}
template double solver<double>(char*);
template <>
mp_float solver<mp_float>(char* expression) {
	double value = solver<double>(expression);
	return (mp_float)value;
}
