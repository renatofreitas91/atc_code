

#include "stdafx.h"
#include <complex>

bool returned = false, equation_solver = false;
char* saveExpressionF = getDynamicCharArray("", "saveExpressionF");

static std::string formatPolynomialCoefficient(double value) {
	if (std::fabs(value) < 1E-12) {
		return "0";
	}
	double rounded = std::round(value);
	if (std::fabs(value - rounded) < 1E-12) {
		value = rounded;
	}
	std::ostringstream stream;
	stream << std::setprecision(15) << std::fabs(value);
	std::string formatted = stream.str();
	if (value < 0) {
		return "_" + formatted;
	}
	return formatted;
}

static bool parsePolynomialCoefficient(const std::string& text, double& value) {
	if (text.empty()) {
		return false;
	}
	std::string normalized = text;
	for (size_t i = 0; i < normalized.size(); i++) {
		if (normalized[i] == '_') {
			normalized[i] = '-';
		}
	}
	char* end = nullptr;
	value = std::strtod(normalized.c_str(), &end);
	return end != normalized.c_str() && *end == '\0';
}

static bool parseComplexPolynomialCoefficient(const std::string& text, std::complex<double>& value) {
	if (text.empty()) {
		return false;
	}
	std::string normalized = text;
	if (normalized.size() > 1 && normalized[0] == '(' && normalized[normalized.size() - 1] == ')') {
		normalized = normalized.substr(1, normalized.size() - 2);
	}
	for (size_t i = 0; i < normalized.size(); i++) {
		if (normalized[i] == '_') {
			normalized[i] = '-';
		}
	}
	for (size_t pos = normalized.find("+-"); pos != std::string::npos; pos = normalized.find("+-")) {
		normalized.replace(pos, 2, "-");
	}
	for (size_t pos = normalized.find("-+"); pos != std::string::npos; pos = normalized.find("-+")) {
		normalized.replace(pos, 2, "-");
	}
	for (size_t pos = normalized.find("++"); pos != std::string::npos; pos = normalized.find("++")) {
		normalized.replace(pos, 2, "+");
	}
	if (normalized.empty()) {
		return false;
	}
	if (normalized.find('i') == std::string::npos) {
		double real = 0;
		if (!parsePolynomialCoefficient(normalized, real)) {
			return false;
		}
		value = std::complex<double>(real, 0.0);
		return true;
	}
	if (normalized[normalized.size() - 1] != 'i' || normalized.find('i') != normalized.size() - 1) {
		return false;
	}
	std::string withoutI = normalized.substr(0, normalized.size() - 1);
	if (withoutI.empty() || withoutI == "+") {
		value = std::complex<double>(0.0, 1.0);
		return true;
	}
	if (withoutI == "-") {
		value = std::complex<double>(0.0, -1.0);
		return true;
	}
	size_t split = std::string::npos;
	for (size_t i = withoutI.size() - 1; i > 0; i--) {
		if (withoutI[i] == '+' || withoutI[i] == '-') {
			split = i;
			break;
		}
	}
	double real = 0.0;
	double imaginary = 0.0;
	if (split == std::string::npos) {
		if (!parsePolynomialCoefficient(withoutI, imaginary)) {
			return false;
		}
	}
	else {
		if (!parsePolynomialCoefficient(withoutI.substr(0, split), real)) {
			return false;
		}
		if (!parsePolynomialCoefficient(withoutI.substr(split), imaginary)) {
			return false;
		}
	}
	value = std::complex<double>(real, imaginary);
	return true;
}

static std::string removeSpaces(const std::string& text) {
	std::string result;
	result.reserve(text.size());
	for (size_t i = 0; i < text.size(); i++) {
		if (!std::isspace((unsigned char)text[i])) {
			result.push_back(text[i]);
		}
	}
	return result;
}

static bool hasBalancedOuterParentheses(const std::string& text) {
	if (text.size() < 2 || text[0] != '(' || text[text.size() - 1] != ')') {
		return false;
	}
	int level = 0;
	for (size_t i = 0; i < text.size(); i++) {
		if (text[i] == '(') {
			level++;
		}
		else if (text[i] == ')') {
			level--;
			if (level == 0 && i + 1 < text.size()) {
				return false;
			}
			if (level < 0) {
				return false;
			}
		}
	}
	return level == 0;
}

static std::string stripBalancedOuterParentheses(std::string text) {
	while (hasBalancedOuterParentheses(text)) {
		text = text.substr(1, text.size() - 2);
	}
	return text;
}

static size_t findTopLevelOperator(const std::string& text, char op) {
	int level = 0;
	for (size_t i = 0; i < text.size(); i++) {
		if (text[i] == '(') {
			level++;
		}
		else if (text[i] == ')') {
			level--;
		}
		else if (text[i] == op && level == 0) {
			return i;
		}
		if (level < 0) {
			return std::string::npos;
		}
	}
	return std::string::npos;
}

static bool splitParenthesizedProduct(const std::string& expression, std::vector<std::string>& factors) {
	std::string text = stripBalancedOuterParentheses(removeSpaces(expression));
	if (text.empty()) {
		return false;
	}
	factors.clear();
	if (text[0] != '(') {
		factors.push_back(stripBalancedOuterParentheses(text));
		return true;
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
		if (i >= text.size() || text[i] != ')') {
			return false;
		}
		factors.push_back(stripBalancedOuterParentheses(text.substr(start, i - start + 1)));
		i++;
	}
	return !factors.empty();
}

static std::string joinProductFactors(const std::vector<std::string>& factors) {
	if (factors.empty()) {
		return "1";
	}
	if (factors.size() == 1) {
		return factors[0];
	}
	std::string result;
	for (size_t i = 0; i < factors.size(); i++) {
		result += "(" + factors[i] + ")";
	}
	return result;
}

static bool reduceTopLevelExactRationalProductExpression(const std::string& source, std::string& reducedExpression) {
	std::string text = stripBalancedOuterParentheses(removeSpaces(source));
	size_t division = findTopLevelOperator(text, '/');
	if (division == std::string::npos) {
		return false;
	}
	std::vector<std::string> numeratorFactors;
	std::vector<std::string> denominatorFactors;
	if (!splitParenthesizedProduct(text.substr(0, division), numeratorFactors) ||
		!splitParenthesizedProduct(text.substr(division + 1), denominatorFactors)) {
		return false;
	}
	bool cancelled = false;
	for (size_t i = 0; i < numeratorFactors.size(); i++) {
		for (size_t j = 0; j < denominatorFactors.size(); j++) {
			if (!denominatorFactors[j].empty() && numeratorFactors[i] == denominatorFactors[j]) {
				numeratorFactors[i].clear();
				denominatorFactors[j].clear();
				cancelled = true;
				break;
			}
		}
	}
	if (!cancelled) {
		return false;
	}
	std::vector<std::string> remainingNumerator;
	std::vector<std::string> remainingDenominator;
	for (size_t i = 0; i < numeratorFactors.size(); i++) {
		if (!numeratorFactors[i].empty()) {
			remainingNumerator.push_back(numeratorFactors[i]);
		}
	}
	for (size_t i = 0; i < denominatorFactors.size(); i++) {
		if (!denominatorFactors[i].empty()) {
			remainingDenominator.push_back(denominatorFactors[i]);
		}
	}
	std::string numerator = joinProductFactors(remainingNumerator);
	if (remainingDenominator.empty()) {
		reducedExpression = numerator;
	}
	else {
		reducedExpression = "(" + numerator + ")/(" + joinProductFactors(remainingDenominator) + ")";
	}
	return true;
}

static bool splitTopLevelProductExpression(const std::string& source, std::vector<std::string>& factors) {
	std::string text = stripBalancedOuterParentheses(removeSpaces(source));
	factors.clear();
	int level = 0;
	size_t start = 0;
	bool foundExplicitProduct = false;
	for (size_t i = 0; i < text.size(); i++) {
		if (text[i] == '(') {
			level++;
		}
		else if (text[i] == ')') {
			level--;
		}
		else if (text[i] == '*' && level == 0) {
			factors.push_back(text.substr(start, i - start));
			start = i + 1;
			foundExplicitProduct = true;
		}
		if (level < 0) {
			factors.clear();
			return false;
		}
	}
	if (foundExplicitProduct) {
		factors.push_back(text.substr(start));
		return true;
	}
	std::vector<std::string> adjacentFactors;
	if (splitParenthesizedProduct(text, adjacentFactors) && adjacentFactors.size() > 1) {
		factors = adjacentFactors;
		return true;
	}
	return false;
}

static bool reduceExactRationalProductExpressionRecursive(const std::string& source, std::string& reducedExpression) {
	std::string text = stripBalancedOuterParentheses(removeSpaces(source));
	bool changed = false;
	std::string topLevelReduced;
	if (reduceTopLevelExactRationalProductExpression(text, topLevelReduced)) {
		text = topLevelReduced;
		changed = true;
	}
	std::vector<std::string> factors;
	if (splitTopLevelProductExpression(text, factors)) {
		std::vector<std::string> reducedFactors;
		reducedFactors.reserve(factors.size());
		for (size_t i = 0; i < factors.size(); i++) {
			std::string reducedFactor;
			if (reduceExactRationalProductExpressionRecursive(factors[i], reducedFactor)) {
				reducedFactors.push_back(reducedFactor);
				changed = true;
			}
			else {
				reducedFactors.push_back(stripBalancedOuterParentheses(removeSpaces(factors[i])));
			}
		}
		if (changed) {
			reducedExpression = joinProductFactors(reducedFactors);
			return true;
		}
	}
	if (changed) {
		reducedExpression = text;
		return true;
	}
	return false;
}

bool reduceExactRationalProductExpression(const char* expression, std::string& reducedExpression) {
	if (expression == nullptr) {
		return false;
	}
	return reduceExactRationalProductExpressionRecursive(expression, reducedExpression);
}

static bool extractSolverCommandArgument(const char* expression, std::string& argument) {
	if (expression == nullptr) {
		return false;
	}
	std::string text = removeSpaces(expression);
	const std::string prefix = "solver(";
	if (text.compare(0, prefix.size(), prefix) != 0 || text.size() <= prefix.size()) {
		return false;
	}
	int level = 0;
	for (size_t i = prefix.size() - 1; i < text.size(); i++) {
		if (text[i] == '(') {
			level++;
		}
		else if (text[i] == ')') {
			level--;
			if (level == 0) {
				if (i != text.size() - 1) {
					return false;
				}
				argument = text.substr(prefix.size(), i - prefix.size());
				return true;
			}
			if (level < 0) {
				return false;
			}
		}
	}
	return false;
}

static bool parseCommandLinearNumber(const std::string& text, long double& value) {
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

static bool parseUnsignedCommandConstantProduct(const std::string& text, long double& value) {
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

static bool parseCommandLinearConstantProduct(const std::string& text, long double& value) {
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
	if (!parseUnsignedCommandConstantProduct(normalized, unsignedValue)) {
		return false;
	}
	value = sign * unsignedValue;
	return true;
}

static bool parseCommandLinearComplexNumber(const std::string& text, std::complex<long double>& value) {
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
	if (parseCommandLinearNumber(normalized, realValue)) {
		value = std::complex<long double>(realValue, 0.0L);
		return true;
	}
	if (parseCommandLinearConstantProduct(normalized, realValue)) {
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
		if (parseCommandLinearNumber(imaginaryText, imaginaryValue)) {
			value = std::complex<long double>(0.0L, imaginaryValue);
			return true;
		}
		if (parseCommandLinearConstantProduct(imaginaryText, imaginaryValue)) {
			value = std::complex<long double>(0.0L, imaginaryValue);
			return true;
		}
	}
	return false;
}

static bool trySolveCommandLinearExpressionComplex(const std::string& expression, std::complex<long double>& solution) {
	std::string text = stripBalancedOuterParentheses(removeSpaces(expression));
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
				if (!parseCommandLinearComplexNumber(coeffText, termCoefficient)) {
					return false;
				}
				coefficient += termCoefficient;
			}
			hasX = true;
		}
		else {
			std::complex<long double> termConstant(0.0L, 0.0L);
			if (!parseCommandLinearComplexNumber(term, termConstant)) {
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

static bool trySolveCommandLinearExpression(const std::string& expression, long double& solution) {
	std::complex<long double> complexSolution(0.0L, 0.0L);
	if (!trySolveCommandLinearExpressionComplex(expression, complexSolution) || std::fabsl(complexSolution.imag()) > 1E-12L) {
		return false;
	}
	solution = complexSolution.real();
	return true;
}

static bool trySolveCommandLinearProductExpression(const std::string& expression, long double& solution) {
	std::string text = stripBalancedOuterParentheses(removeSpaces(expression));
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
		std::string factor = stripBalancedOuterParentheses(text.substr(start + 1, i - start - 1));
		if (trySolveCommandLinearExpression(factor, solution)) {
			return true;
		}
		i++;
		if (i < text.size() && text[i] == '*') {
			i++;
		}
	}
	return false;
}

static bool trySolveCommandLinearProductExpressionComplex(const std::string& expression, std::complex<long double>& solution) {
	std::string text = stripBalancedOuterParentheses(removeSpaces(expression));
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
		std::string factor = stripBalancedOuterParentheses(text.substr(start + 1, i - start - 1));
		if (trySolveCommandLinearExpressionComplex(factor, solution)) {
			return true;
		}
		std::string reducedFactor;
		if (reduceExactRationalProductExpression(factor.c_str(), reducedFactor) && reducedFactor != factor &&
			(trySolveCommandLinearExpressionComplex(reducedFactor, solution) ||
				trySolveCommandLinearProductExpressionComplex(reducedFactor, solution))) {
			return true;
		}
		i++;
		if (i < text.size() && text[i] == '*') {
			i++;
		}
	}
	return false;
}

static bool selectCommandFirstLinearSolverFactor(const std::string& expression, std::string& factor) {
	std::string text = stripBalancedOuterParentheses(removeSpaces(expression));
	if (text.empty()) {
		return false;
	}
	if (text[0] != '(') {
		if (text.find('x') != std::string::npos && text.find('/') == std::string::npos) {
			factor = text;
			return true;
		}
		return false;
	}
	int level = 0;
	for (size_t i = 0; i < text.size(); i++) {
		if (text[i] == '(') {
			level++;
		}
		else if (text[i] == ')') {
			level--;
			if (level == 0) {
				std::string fullCandidate = text.substr(0, i + 1);
				std::string reducedFullCandidate;
				if (reduceExactRationalProductExpression(fullCandidate.c_str(), reducedFullCandidate) &&
					reducedFullCandidate != fullCandidate) {
					return selectCommandFirstLinearSolverFactor(reducedFullCandidate, factor);
				}
				std::string candidate = stripBalancedOuterParentheses(text.substr(1, i - 1));
				std::string reducedCandidate;
				if (candidate.find('/') != std::string::npos &&
					reduceExactRationalProductExpression(candidate.c_str(), reducedCandidate) &&
					reducedCandidate != candidate) {
					return selectCommandFirstLinearSolverFactor(reducedCandidate, factor);
				}
				if (candidate.find('x') != std::string::npos && candidate.find('/') == std::string::npos &&
					candidate.find('(') == std::string::npos && candidate.find(')') == std::string::npos) {
					factor = candidate;
					return true;
				}
				return false;
			}
			if (level < 0) {
				return false;
			}
		}
	}
	return false;
}

bool normalizeSolverCommandExpression(char* expression) {
	std::string solverArgument;
	if (!extractSolverCommandArgument(expression, solverArgument)) {
		return false;
	}
	std::string reducedArgument;
	std::string factorSource = solverArgument;
	if (reduceExactRationalProductExpression(solverArgument.c_str(), reducedArgument)) {
		factorSource = reducedArgument;
	}
	std::string linearFactor;
	if (!selectCommandFirstLinearSolverFactor(factorSource, linearFactor)) {
		return false;
	}
	std::string normalized = "solver(" + linearFactor + ")";
	if (normalized.size() >= (size_t)DIM) {
		return false;
	}
	std::memset(expression, '\0', DIM);
	std::strncpy(expression, normalized.c_str(), DIM - 1);
	return true;
}

template <typename T>
static bool handleAtcOverCmdSolverFastPath(char* expression, FILE* fout) {
	std::string solverArgument;
	if (!extractSolverCommandArgument(expression, solverArgument)) {
		return false;
	}
	std::string reducedArgument;
	if (reduceExactRationalProductExpression(solverArgument.c_str(), reducedArgument)) {
		solverArgument = reducedArgument;
	}
	std::complex<long double> solution(0.0L, 0.0L);
	if (!trySolveCommandLinearExpressionComplex(solverArgument, solution) &&
		!trySolveCommandLinearProductExpressionComplex(solverArgument, solution)) {
		return false;
	}
	resultR = (T)solution.real();
	resultI = (T)solution.imag();
	ans[rf] = resultR;
	ansI[rf] = resultI;
	ansRV = resultR;
	ansIV = resultI;
	previousAnsType = 0;
	sprintf(saveMatrixAns, "");
	sprintf(ansMatrices[rf], "");
	convertComplex2Exponential(resultR, resultI);
	if (abs(precisionValueTo<double>(resultI)) < 1E-18) {
		printf("#%d=%s\n", rf, respR);
		if (fout != NULL) {
			fprintf(fout, "#%d=%s\n", rf, respR);
		}
	}
	else if (resultI > 0) {
		printf("#%d=%s+%si\n", rf, respR, respI);
		if (fout != NULL) {
			fprintf(fout, "#%d=%s+%si\n", rf, respR, respI);
		}
	}
	else {
		printf("#%d=%s%si\n", rf, respR, respI);
		if (fout != NULL) {
			fprintf(fout, "#%d=%s%si\n", rf, respR, respI);
		}
	}
	rf++;
	verified = 1;
	return true;
}

static bool splitPolynomialTerm(const std::string& term, int& degree, double& coefficient) {
	if (term.empty()) {
		return false;
	}
	size_t xPos = term.find('x');
	if (xPos == std::string::npos) {
		degree = 0;
		return parsePolynomialCoefficient(term, coefficient);
	}
	if (term.find('x', xPos + 1) != std::string::npos) {
		return false;
	}
	std::string prefix = term.substr(0, xPos);
	std::string suffix = term.substr(xPos + 1);
	if (!prefix.empty() && prefix[prefix.size() - 1] == '*') {
		prefix.erase(prefix.size() - 1);
	}
	if (prefix.empty()) {
		coefficient = 1;
	}
	else if (prefix == "_") {
		coefficient = -1;
	}
	else if (!parsePolynomialCoefficient(prefix, coefficient)) {
		return false;
	}
	degree = 1;
	if (!suffix.empty()) {
		if (suffix[0] != '^') {
			return false;
		}
		if (suffix.size() == 1) {
			return false;
		}
		degree = 0;
		for (size_t i = 1; i < suffix.size(); i++) {
			if (suffix[i] < '0' || suffix[i] > '9') {
				return false;
			}
			degree = degree * 10 + (suffix[i] - '0');
		}
	}
	return degree >= 0;
}

static bool splitPolynomialTermComplex(const std::string& term, int& degree, std::complex<double>& coefficient) {
	if (term.empty()) {
		return false;
	}
	size_t xPos = term.find('x');
	if (xPos == std::string::npos) {
		degree = 0;
		return parseComplexPolynomialCoefficient(term, coefficient);
	}
	if (term.find('x', xPos + 1) != std::string::npos) {
		return false;
	}
	std::string prefix = term.substr(0, xPos);
	std::string suffix = term.substr(xPos + 1);
	if (!prefix.empty() && prefix[prefix.size() - 1] == '*') {
		prefix.erase(prefix.size() - 1);
	}
	if (prefix.empty()) {
		coefficient = std::complex<double>(1.0, 0.0);
	}
	else if (prefix == "_") {
		coefficient = std::complex<double>(-1.0, 0.0);
	}
	else if (!parseComplexPolynomialCoefficient(prefix, coefficient)) {
		return false;
	}
	degree = 1;
	if (!suffix.empty()) {
		if (suffix[0] != '^' || suffix.size() == 1) {
			return false;
		}
		degree = 0;
		for (size_t i = 1; i < suffix.size(); i++) {
			if (suffix[i] < '0' || suffix[i] > '9') {
				return false;
			}
			degree = degree * 10 + (suffix[i] - '0');
		}
	}
	return degree >= 0;
}

static bool convertSimplePolynomialToCoefficientList(const char* source, char* destination) {
	std::string expression(source);
	std::string normalized;
	for (size_t i = 0; i < expression.size(); i++) {
		if (expression[i] != ' ') {
			normalized += expression[i];
		}
	}
	if (normalized.empty() || normalized.find('x') == std::string::npos ||
		normalized.find('\\') != std::string::npos ||
		normalized.find('(') != std::string::npos ||
		normalized.find(')') != std::string::npos ||
		normalized.find('/') != std::string::npos) {
		return false;
	}
	std::string signedExpression;
	for (size_t i = 0; i < normalized.size(); i++) {
		if (normalized[i] == '-') {
			if (i > 0) {
				signedExpression += '+';
			}
			signedExpression += '_';
		}
		else {
			signedExpression += normalized[i];
		}
	}
	std::vector<std::string> terms;
	size_t start = 0;
	for (size_t i = 0; i <= signedExpression.size(); i++) {
		if (i == signedExpression.size() || signedExpression[i] == '+') {
			if (i > start) {
				terms.push_back(signedExpression.substr(start, i - start));
			}
			start = i + 1;
		}
	}
	if (terms.empty()) {
		return false;
	}
	int maxDegree = 0;
	std::vector<double> coefficients(1, 0.0);
	for (size_t i = 0; i < terms.size(); i++) {
		int degree = 0;
		double coefficient = 0;
		if (!splitPolynomialTerm(terms[i], degree, coefficient)) {
			return false;
		}
		if (degree > maxDegree) {
			maxDegree = degree;
			coefficients.resize(maxDegree + 1, 0.0);
		}
		coefficients[degree] += coefficient;
	}
	if (maxDegree <= 0) {
		return false;
	}
	std::string converted;
	for (int degree = maxDegree; degree >= 0; degree--) {
		if (!converted.empty()) {
			converted += '\\';
		}
		converted += formatPolynomialCoefficient(coefficients[degree]);
	}
	if (converted.size() >= (size_t)DIM) {
		return false;
	}
	sprintf(destination, "%s", converted.c_str());
	return true;
}

static std::string normalizeSimplePolynomialText(const char* source) {
	std::string expression(source ? source : "");
	std::string normalized;
	for (size_t i = 0; i < expression.size(); i++) {
		if (expression[i] != ' ') {
			normalized += expression[i];
		}
	}
	return normalized;
}

static bool collectSimplePolynomialCoefficients(const std::string& normalized, std::vector<double>& coefficients) {
	if (normalized.empty() || normalized.find('x') == std::string::npos ||
		normalized.find('\\') != std::string::npos ||
		normalized.find('(') != std::string::npos ||
		normalized.find(')') != std::string::npos ||
		normalized.find('/') != std::string::npos) {
		return false;
	}
	std::string signedExpression;
	for (size_t i = 0; i < normalized.size(); i++) {
		if (normalized[i] == '-') {
			if (i > 0) {
				signedExpression += '+';
			}
			signedExpression += '_';
		}
		else {
			signedExpression += normalized[i];
		}
	}
	std::vector<std::string> terms;
	size_t start = 0;
	for (size_t i = 0; i <= signedExpression.size(); i++) {
		if (i == signedExpression.size() || signedExpression[i] == '+') {
			if (i > start) {
				terms.push_back(signedExpression.substr(start, i - start));
			}
			start = i + 1;
		}
	}
	if (terms.empty()) {
		return false;
	}
	int maxDegree = 0;
	coefficients.assign(1, 0.0);
	for (size_t i = 0; i < terms.size(); i++) {
		int degree = 0;
		double coefficient = 0;
		if (!splitPolynomialTerm(terms[i], degree, coefficient)) {
			return false;
		}
		if (degree > maxDegree) {
			maxDegree = degree;
			coefficients.resize(maxDegree + 1, 0.0);
		}
		coefficients[degree] += coefficient;
	}
	if (maxDegree <= 0) {
		return false;
	}
	return true;
}

static bool collectSimplePolynomialComplexCoefficients(const std::string& normalized, std::vector<std::complex<double>>& coefficients) {
	if (normalized.empty() || normalized.find('x') == std::string::npos ||
		normalized.find('\\') != std::string::npos ||
		normalized.find('(') != std::string::npos ||
		normalized.find(')') != std::string::npos ||
		normalized.find('/') != std::string::npos) {
		return false;
	}
	std::string signedExpression;
	for (size_t i = 0; i < normalized.size(); i++) {
		if (normalized[i] == '-') {
			if (i > 0) {
				signedExpression += '+';
			}
			signedExpression += '_';
		}
		else {
			signedExpression += normalized[i];
		}
	}
	std::vector<std::string> terms;
	size_t start = 0;
	for (size_t i = 0; i <= signedExpression.size(); i++) {
		if (i == signedExpression.size() || signedExpression[i] == '+') {
			if (i > start) {
				terms.push_back(signedExpression.substr(start, i - start));
			}
			start = i + 1;
		}
	}
	if (terms.empty()) {
		return false;
	}
	int maxDegree = 0;
	coefficients.assign(1, std::complex<double>(0.0, 0.0));
	for (size_t i = 0; i < terms.size(); i++) {
		int degree = 0;
		std::complex<double> coefficient(0.0, 0.0);
		if (!splitPolynomialTermComplex(terms[i], degree, coefficient)) {
			return false;
		}
		if (degree > maxDegree) {
			maxDegree = degree;
			coefficients.resize(maxDegree + 1, std::complex<double>(0.0, 0.0));
		}
		coefficients[degree] += coefficient;
	}
	return maxDegree > 0;
}

static std::vector<double> multiplyPolynomialCoefficients(const std::vector<double>& left, const std::vector<double>& right) {
	std::vector<double> multiplied(left.size() + right.size() - 1, 0.0);
	for (size_t i = 0; i < left.size(); i++) {
		for (size_t j = 0; j < right.size(); j++) {
			multiplied[i + j] += left[i] * right[j];
		}
	}
	return multiplied;
}

static std::vector<std::complex<double>> multiplyComplexPolynomialCoefficients(const std::vector<std::complex<double>>& left, const std::vector<std::complex<double>>& right) {
	std::vector<std::complex<double>> multiplied(left.size() + right.size() - 1, std::complex<double>(0.0, 0.0));
	for (size_t i = 0; i < left.size(); i++) {
		for (size_t j = 0; j < right.size(); j++) {
			multiplied[i + j] += left[i] * right[j];
		}
	}
	return multiplied;
}

static void trimComplexPolynomial(std::vector<std::complex<double>>& polynomial) {
	while (polynomial.size() > 1 && std::abs(polynomial.back()) < 1E-12) {
		polynomial.pop_back();
	}
}

static std::vector<std::complex<double>> addComplexPolynomialCoefficients(const std::vector<std::complex<double>>& left, const std::vector<std::complex<double>>& right, double sign) {
	size_t size = std::max(left.size(), right.size());
	std::vector<std::complex<double>> result(size, std::complex<double>(0.0, 0.0));
	for (size_t i = 0; i < size; i++) {
		if (i < left.size()) {
			result[i] += left[i];
		}
		if (i < right.size()) {
			result[i] += right[i] * sign;
		}
	}
	trimComplexPolynomial(result);
	return result;
}

static std::vector<std::complex<double>> powComplexPolynomialCoefficients(std::vector<std::complex<double>> base, int exponent) {
	std::vector<std::complex<double>> result(1, std::complex<double>(1.0, 0.0));
	while (exponent > 0) {
		if ((exponent % 2) == 1) {
			result = multiplyComplexPolynomialCoefficients(result, base);
		}
		exponent /= 2;
		if (exponent > 0) {
			base = multiplyComplexPolynomialCoefficients(base, base);
		}
	}
	trimComplexPolynomial(result);
	return result;
}

class PolynomialExpressionParser {
public:
	explicit PolynomialExpressionParser(const std::string& text) : source(text), index(0) {
	}

	bool parse(std::vector<std::complex<double>>& coefficients) {
		if (source.empty() || source.find('/') != std::string::npos || source.find('\\') != std::string::npos) {
			return false;
		}
		if (!parseExpression(coefficients)) {
			return false;
		}
		return index == source.size() && coefficients.size() > 1;
	}

private:
	const std::string& source;
	size_t index;

	bool parseExpression(std::vector<std::complex<double>>& coefficients) {
		if (!parseTerm(coefficients)) {
			return false;
		}
		while (index < source.size() && (source[index] == '+' || source[index] == '-')) {
			char operation = source[index++];
			std::vector<std::complex<double>> right;
			if (!parseTerm(right)) {
				return false;
			}
			coefficients = addComplexPolynomialCoefficients(coefficients, right, operation == '+' ? 1.0 : -1.0);
		}
		return true;
	}

	bool parseTerm(std::vector<std::complex<double>>& coefficients) {
		if (!parseFactor(coefficients)) {
			return false;
		}
		while (index < source.size()) {
			bool explicitMultiply = source[index] == '*';
			bool implicitMultiply = !explicitMultiply && startsPrimary(source[index]);
			if (!explicitMultiply && !implicitMultiply) {
				break;
			}
			if (explicitMultiply) {
				index++;
			}
			std::vector<std::complex<double>> right;
			if (!parseFactor(right)) {
				return false;
			}
			coefficients = multiplyComplexPolynomialCoefficients(coefficients, right);
		}
		return true;
	}

	bool parseFactor(std::vector<std::complex<double>>& coefficients) {
		if (!parseUnary(coefficients)) {
			return false;
		}
		while (index < source.size() && source[index] == '^') {
			index++;
			if (index >= source.size() || source[index] < '0' || source[index] > '9') {
				return false;
			}
			int exponent = 0;
			while (index < source.size() && source[index] >= '0' && source[index] <= '9') {
				exponent = exponent * 10 + (source[index] - '0');
				if (exponent > 50) {
					return false;
				}
				index++;
			}
			coefficients = powComplexPolynomialCoefficients(coefficients, exponent);
		}
		return true;
	}

	bool parseUnary(std::vector<std::complex<double>>& coefficients) {
		if (index < source.size() && (source[index] == '+' || source[index] == '-' || source[index] == '_')) {
			char sign = source[index++];
			if (!parseUnary(coefficients)) {
				return false;
			}
			if (sign == '-' || sign == '_') {
				for (size_t i = 0; i < coefficients.size(); i++) {
					coefficients[i] = -coefficients[i];
				}
			}
			return true;
		}
		return parsePrimary(coefficients);
	}

	bool parsePrimary(std::vector<std::complex<double>>& coefficients) {
		if (index >= source.size()) {
			return false;
		}
		if (source[index] == 'x') {
			coefficients.assign(2, std::complex<double>(0.0, 0.0));
			coefficients[1] = std::complex<double>(1.0, 0.0);
			index++;
			return true;
		}
		if (source[index] == '(') {
			size_t coefficientEnd = findMatchingParenthesis(index);
			if (coefficientEnd != std::string::npos) {
				std::complex<double> value(0.0, 0.0);
				if (parseComplexPolynomialCoefficient(source.substr(index + 1, coefficientEnd - index - 1), value)) {
					coefficients.assign(1, value);
					index = coefficientEnd + 1;
					return true;
				}
			}
			index++;
			if (!parseExpression(coefficients)) {
				return false;
			}
			if (index >= source.size() || source[index] != ')') {
				return false;
			}
			index++;
			return true;
		}
		return parseNumber(coefficients);
	}

	bool parseNumber(std::vector<std::complex<double>>& coefficients) {
		size_t start = index;
		if (index < source.size() && source[index] == '_') {
			index++;
		}
		if (index < source.size() && (source[index] == 'p' || source[index] == 'e' || source[index] == 'i')) {
			while (index < source.size() &&
				(source[index] == 'p' || source[index] == 'i' || source[index] == 'e' ||
					source[index] == '.' || (source[index] >= '0' && source[index] <= '9'))) {
				index++;
			}
			std::complex<long double> value(0.0L, 0.0L);
			if (!parseCommandLinearComplexNumber(source.substr(start, index - start), value)) {
				return false;
			}
			coefficients.assign(1, std::complex<double>((double)value.real(), (double)value.imag()));
			return true;
		}
		bool hasDigit = false;
		while (index < source.size() && ((source[index] >= '0' && source[index] <= '9') || source[index] == '.')) {
			hasDigit = true;
			index++;
		}
		if (index < source.size() && (source[index] == 'E' || source[index] == 'e')) {
			size_t exponentIndex = index++;
			if (index < source.size() && (source[index] == '+' || source[index] == '-' || source[index] == '_')) {
				index++;
			}
			bool hasExponentDigit = false;
			while (index < source.size() && source[index] >= '0' && source[index] <= '9') {
				hasExponentDigit = true;
				index++;
			}
			if (!hasExponentDigit) {
				index = exponentIndex;
			}
		}
		if (index < source.size() && source[index] == 'i') {
			index++;
			std::string imaginaryText = source.substr(start, index - start - 1);
			if (imaginaryText.empty() || imaginaryText == "_") {
				imaginaryText += "1";
			}
			double imaginary = 0.0;
			if (!parsePolynomialCoefficient(imaginaryText, imaginary)) {
				return false;
			}
			coefficients.assign(1, std::complex<double>(0.0, imaginary));
			return true;
		}
		if (!hasDigit) {
			return false;
		}
		double value = 0.0;
		if (!parsePolynomialCoefficient(source.substr(start, index - start), value)) {
			return false;
		}
		coefficients.assign(1, std::complex<double>(value, 0.0));
		return true;
	}

	bool startsPrimary(char character) const {
		return character == '(' || character == 'x' || character == '_' || character == '.' ||
			character == 'p' || character == 'e' || character == 'i' ||
			(character >= '0' && character <= '9');
	}

	size_t findMatchingParenthesis(size_t openIndex) const {
		int depth = 0;
		for (size_t i = openIndex; i < source.size(); i++) {
			if (source[i] == '(') {
				depth++;
			}
			else if (source[i] == ')') {
				depth--;
				if (depth == 0) {
					return i;
				}
			}
		}
		return std::string::npos;
	}
};

static bool collectAdvancedPolynomialExpressionCoefficients(const std::string& normalized, std::vector<std::complex<double>>& coefficients) {
	PolynomialExpressionParser parser(normalized);
	return parser.parse(coefficients);
}

static bool collectSimplePolynomialProductCoefficients(const std::string& normalized, std::vector<double>& coefficients) {
	if (normalized.empty() || normalized.find('/') != std::string::npos ||
		normalized.find('\\') != std::string::npos) {
		return false;
	}
	size_t pos = 0;
	int factorCount = 0;
	coefficients.assign(1, 1.0);
	while (pos < normalized.size()) {
		if (normalized[pos] != '(') {
			return false;
		}
		int depth = 1;
		size_t start = pos + 1;
		pos++;
		while (pos < normalized.size() && depth > 0) {
			if (normalized[pos] == '(') {
				depth++;
			}
			else if (normalized[pos] == ')') {
				depth--;
			}
			if (depth > 0) {
				pos++;
			}
		}
		if (depth != 0) {
			return false;
		}
		std::string factor = normalized.substr(start, pos - start);
		if (factor.find('(') != std::string::npos || factor.find(')') != std::string::npos) {
			return false;
		}
		std::vector<double> factorCoefficients;
		if (!collectSimplePolynomialCoefficients(factor, factorCoefficients)) {
			return false;
		}
		coefficients = multiplyPolynomialCoefficients(coefficients, factorCoefficients);
		factorCount++;
		pos++;
		if (pos == normalized.size()) {
			break;
		}
		if (normalized[pos] == '*') {
			pos++;
		}
		else if (normalized[pos] != '(') {
			return false;
		}
	}
	return factorCount > 0 && coefficients.size() > 1;
}

static bool collectSimplePolynomialProductComplexCoefficients(const std::string& normalized, std::vector<std::complex<double>>& coefficients) {
	if (normalized.empty() || normalized.find('/') != std::string::npos ||
		normalized.find('\\') != std::string::npos) {
		return false;
	}
	size_t pos = 0;
	int factorCount = 0;
	coefficients.assign(1, std::complex<double>(1.0, 0.0));
	while (pos < normalized.size()) {
		if (normalized[pos] != '(') {
			return false;
		}
		int depth = 1;
		size_t start = pos + 1;
		pos++;
		while (pos < normalized.size() && depth > 0) {
			if (normalized[pos] == '(') {
				depth++;
			}
			else if (normalized[pos] == ')') {
				depth--;
			}
			if (depth > 0) {
				pos++;
			}
		}
		if (depth != 0) {
			return false;
		}
		std::string factor = normalized.substr(start, pos - start);
		if (factor.find('(') != std::string::npos || factor.find(')') != std::string::npos) {
			return false;
		}
		std::vector<std::complex<double>> factorCoefficients;
		if (!collectSimplePolynomialComplexCoefficients(factor, factorCoefficients)) {
			return false;
		}
		coefficients = multiplyComplexPolynomialCoefficients(coefficients, factorCoefficients);
		factorCount++;
		pos++;
		if (pos == normalized.size()) {
			break;
		}
		if (normalized[pos] == '*') {
			pos++;
		}
		else if (normalized[pos] != '(') {
			return false;
		}
	}
	return factorCount > 0 && coefficients.size() > 1;
}

static bool isParenthesizedPolynomialProductSyntax(const char* source) {
	std::string normalized = normalizeSimplePolynomialText(source);
	if (normalized.empty() || normalized.find('x') == std::string::npos ||
		normalized.find('/') != std::string::npos || normalized.find('\\') != std::string::npos) {
		return false;
	}
	size_t pos = 0;
	int factorCount = 0;
	while (pos < normalized.size()) {
		if (normalized[pos] != '(') {
			return false;
		}
		int depth = 1;
		pos++;
		while (pos < normalized.size() && depth > 0) {
			if (normalized[pos] == '(') {
				depth++;
			}
			else if (normalized[pos] == ')') {
				depth--;
			}
			if (depth > 0) {
				pos++;
			}
		}
		if (depth != 0) {
			return false;
		}
		factorCount++;
		pos++;
		if (pos == normalized.size()) {
			break;
		}
		if (normalized[pos] == '*') {
			pos++;
		}
		else if (normalized[pos] != '(') {
			return false;
		}
	}
	return factorCount > 1;
}

static bool isInternalPolynomialSyntax(const char* source) {
	std::string normalized = normalizeSimplePolynomialText(source);
	return normalized.find("(+") == std::string::npos &&
		normalized.find('x') != std::string::npos &&
		normalized.find('(') != std::string::npos &&
		normalized.find(')') != std::string::npos &&
		normalized.find("+0i)") != std::string::npos;
}

static bool writeInternalPolynomial(const std::vector<double>& coefficients, char* destination) {
	if (coefficients.size() <= 1) {
		return false;
	}
	std::string converted;
	for (int degree = (int)coefficients.size() - 1; degree >= 0; degree--) {
		if (std::fabs(coefficients[degree]) < 1E-12 && degree != 0) {
			continue;
		}
		if (!converted.empty()) {
			converted += '+';
		}
		converted += '(' + formatPolynomialCoefficient(coefficients[degree]) + "+0i)";
		if (degree > 1) {
			converted += "x^" + std::to_string(degree);
		}
		else if (degree == 1) {
			converted += "x^1";
		}
	}
	if (converted.size() >= (size_t)DIM) {
		return false;
	}
	sprintf(destination, "%s", converted.c_str());
	return true;
}

static bool writeInternalComplexPolynomial(const std::vector<std::complex<double>>& coefficients, char* destination) {
	if (coefficients.size() <= 1) {
		return false;
	}
	std::string converted;
	for (int degree = (int)coefficients.size() - 1; degree >= 0; degree--) {
		double real = coefficients[(size_t)degree].real();
		double imaginary = coefficients[(size_t)degree].imag();
		if (std::fabs(real) < 1E-12) {
			real = 0.0;
		}
		if (std::fabs(imaginary) < 1E-12) {
			imaginary = 0.0;
		}
		if (real == 0.0 && imaginary == 0.0 && degree != 0) {
			continue;
		}
		if (!converted.empty()) {
			converted += '+';
		}
		converted += '(' + formatPolynomialCoefficient(real) + '+' + formatPolynomialCoefficient(imaginary) + "i)";
		if (degree > 1) {
			converted += "x^" + std::to_string(degree);
		}
		else if (degree == 1) {
			converted += "x^1";
		}
	}
	if (converted.size() >= (size_t)DIM) {
		return false;
	}
	sprintf(destination, "%s", converted.c_str());
	return true;
}

static bool convertSimplePolynomialToInternalPolynomial(const char* source, char* destination) {
	std::string normalized = normalizeSimplePolynomialText(source);
	std::vector<std::complex<double>> advancedCoefficients;
	if (collectAdvancedPolynomialExpressionCoefficients(normalized, advancedCoefficients)) {
		return writeInternalComplexPolynomial(advancedCoefficients, destination);
	}
	std::vector<double> coefficients;
	if (collectSimplePolynomialCoefficients(normalized, coefficients) ||
		collectSimplePolynomialProductCoefficients(normalized, coefficients)) {
		return writeInternalPolynomial(coefficients, destination);
	}
	std::vector<std::complex<double>> complexCoefficients;
	if (collectSimplePolynomialComplexCoefficients(normalized, complexCoefficients) ||
		collectSimplePolynomialProductComplexCoefficients(normalized, complexCoefficients)) {
		return writeInternalComplexPolynomial(complexCoefficients, destination);
	}
	return false;
}

static bool collectInternalPolynomialComplexCoefficients(const std::string& normalized, std::vector<std::complex<double>>& coefficients) {
	if (normalized.empty() || normalized.find("\\") != std::string::npos || normalized.find('/') != std::string::npos) {
		return false;
	}
	size_t pos = 0;
	int maxDegree = -1;
	coefficients.clear();
	while (pos < normalized.size()) {
		if (normalized[pos] == '+') {
			pos++;
		}
		if (pos >= normalized.size() || normalized[pos] != '(') {
			return false;
		}
		size_t endCoefficient = normalized.find(')', pos + 1);
		if (endCoefficient == std::string::npos) {
			return false;
		}
		std::complex<double> coefficient(0.0, 0.0);
		if (!parseComplexPolynomialCoefficient(normalized.substr(pos + 1, endCoefficient - pos - 1), coefficient)) {
			return false;
		}
		pos = endCoefficient + 1;
		int degree = 0;
		if (pos < normalized.size() && normalized[pos] == 'x') {
			degree = 1;
			pos++;
			if (pos < normalized.size() && normalized[pos] == '^') {
				pos++;
				if (pos >= normalized.size() || normalized[pos] < '0' || normalized[pos] > '9') {
					return false;
				}
				degree = 0;
				while (pos < normalized.size() && normalized[pos] >= '0' && normalized[pos] <= '9') {
					degree = degree * 10 + (normalized[pos] - '0');
					pos++;
				}
			}
		}
		if (degree > maxDegree) {
			maxDegree = degree;
			coefficients.resize((size_t)maxDegree + 1, std::complex<double>(0.0, 0.0));
		}
		coefficients[(size_t)degree] += coefficient;
		if (pos < normalized.size() && normalized[pos] != '+') {
			return false;
		}
	}
	return maxDegree > 0;
}

static bool parseMpRealCoefficient(const std::string& text, mp_float& value) {
	if (text.empty()) {
		return false;
	}
	std::string normalized = text;
	for (size_t i = 0; i < normalized.size(); i++) {
		if (normalized[i] == '_') {
			normalized[i] = '-';
		}
	}
	for (size_t pos = normalized.find("+-"); pos != std::string::npos; pos = normalized.find("+-")) {
		normalized.replace(pos, 2, "-");
	}
	for (size_t pos = normalized.find("-+"); pos != std::string::npos; pos = normalized.find("-+")) {
		normalized.replace(pos, 2, "-");
	}
	for (size_t pos = normalized.find("++"); pos != std::string::npos; pos = normalized.find("++")) {
		normalized.replace(pos, 2, "+");
	}
	size_t iPos = normalized.find('i');
	if (iPos != std::string::npos) {
		if (iPos != normalized.size() - 1) {
			return false;
		}
		std::string withoutI = normalized.substr(0, normalized.size() - 1);
		size_t split = std::string::npos;
		for (size_t i = withoutI.size() - 1; i > 0; i--) {
			if (withoutI[i] == '+' || withoutI[i] == '-') {
				split = i;
				break;
			}
		}
		if (split == std::string::npos) {
			return false;
		}
		try {
			mp_float imaginary(withoutI.substr(split));
			if (abs(imaginary) > mp_float("1e-40")) {
				return false;
			}
			value = mp_float(withoutI.substr(0, split));
		}
		catch (...) {
			return false;
		}
		return true;
	}
	try {
		value = mp_float(normalized);
	}
	catch (...) {
		return false;
	}
	return true;
}

static bool collectInternalPolynomialMpCoefficients(const std::string& normalized, std::vector<mp_float>& coefficientsByDegree) {
	if (normalized.empty() || normalized.find("\\") != std::string::npos || normalized.find('/') != std::string::npos) {
		return false;
	}
	size_t pos = 0;
	int maxDegree = -1;
	coefficientsByDegree.clear();
	while (pos < normalized.size()) {
		if (normalized[pos] == '+') {
			pos++;
		}
		if (pos >= normalized.size() || normalized[pos] != '(') {
			return false;
		}
		size_t endCoefficient = normalized.find(')', pos + 1);
		if (endCoefficient == std::string::npos) {
			return false;
		}
		mp_float coefficient = 0;
		if (!parseMpRealCoefficient(normalized.substr(pos + 1, endCoefficient - pos - 1), coefficient)) {
			return false;
		}
		pos = endCoefficient + 1;
		int degree = 0;
		if (pos < normalized.size() && normalized[pos] == 'x') {
			degree = 1;
			pos++;
			if (pos < normalized.size() && normalized[pos] == '^') {
				pos++;
				if (pos >= normalized.size() || normalized[pos] < '0' || normalized[pos] > '9') {
					return false;
				}
				degree = 0;
				while (pos < normalized.size() && normalized[pos] >= '0' && normalized[pos] <= '9') {
					degree = degree * 10 + (normalized[pos] - '0');
					pos++;
				}
			}
		}
		if (degree > maxDegree) {
			maxDegree = degree;
			coefficientsByDegree.resize((size_t)maxDegree + 1, mp_float(0));
		}
		coefficientsByDegree[(size_t)degree] += coefficient;
		if (pos < normalized.size() && normalized[pos] != '+') {
			return false;
		}
	}
	return maxDegree > 0;
}

static std::string formatEquationRootPart(double value) {
	if (std::fabs(value) < 5E-7) {
		value = 0.0;
	}
	std::ostringstream stream;
	stream << std::setprecision(6) << value;
	std::string formatted = stream.str();
	for (size_t i = 0; i < formatted.size(); i++) {
		if (formatted[i] == 'e') {
			formatted[i] = 'E';
		}
	}
	return formatted;
}

static bool solvePureBinomialEquation(const char* source) {
	std::string normalized = normalizeSimplePolynomialText(source);
	std::vector<double> coefficients;
	if (!collectSimplePolynomialCoefficients(normalized, coefficients) || coefficients.size() <= 2) {
		return false;
	}
	int degree = (int)coefficients.size() - 1;
	double leading = coefficients[degree];
	double constant = coefficients[0];
	if (std::fabs(leading) < 1E-12) {
		return false;
	}
	for (int i = 1; i < degree; i++) {
		if (std::fabs(coefficients[i]) >= 1E-12) {
			return false;
		}
	}
	double rhs = -constant / leading;
	if (std::fabs(rhs) < 1E-12) {
		sprintf(answers, "");
		for (int i = 1; i <= degree; i++) {
			sprintf(answers, "%sx%d=0\n", answers, i);
		}
		return true;
	}
	double magnitude = std::pow(std::fabs(rhs), 1.0 / degree);
	double baseAngle = rhs < 0 ? M_PI : 0.0;
	sprintf(answers, "");
	int outputIndex = 1;
	auto appendRoot = [&](double angle) {
		double real = magnitude * std::cos(angle);
		double imaginary = magnitude * std::sin(angle);
		std::string realText = formatEquationRootPart(real);
		std::string imaginaryText = formatEquationRootPart(std::fabs(imaginary));
		if (std::fabs(imaginary) < 5E-7) {
			sprintf(answers, "%sx%d=%s\n", answers, outputIndex, realText.c_str());
		}
		else if (imaginary > 0) {
			sprintf(answers, "%sx%d=%s+%si\n", answers, outputIndex, realText.c_str(), imaginaryText.c_str());
		}
		else {
			sprintf(answers, "%sx%d=%s-%si\n", answers, outputIndex, realText.c_str(), imaginaryText.c_str());
		}
		outputIndex++;
	};
	if (rhs > 0) {
		appendRoot(0.0);
		for (int k = 1; k <= degree / 2; k++) {
			double angle = 2.0 * M_PI * k / degree;
			if (degree % 2 == 0 && k == degree / 2) {
				appendRoot(M_PI);
			}
			else {
				appendRoot(-angle);
				appendRoot(angle);
			}
		}
	}
	else {
		if (degree % 2 == 1) {
			appendRoot(M_PI);
			for (int k = 1; k <= degree / 2; k++) {
				double angle = M_PI + 2.0 * M_PI * k / degree;
				while (angle > M_PI) {
					angle -= 2.0 * M_PI;
				}
				appendRoot(angle);
				appendRoot(-angle);
			}
		}
		else {
			for (int k = 0; k < degree / 2; k++) {
				double angle = (baseAngle + 2.0 * M_PI * k) / degree;
				while (angle > M_PI) {
					angle -= 2.0 * M_PI;
				}
				if (angle > 0) {
					appendRoot(-angle);
					appendRoot(angle);
				}
				else {
					appendRoot(angle);
					appendRoot(-angle);
				}
			}
		}
	}
	return true;
}

static bool collectCoefficientList(const char* source, std::vector<double>& coefficients) {
	if (source == nullptr || std::strchr(source, '\\') == nullptr) {
		return false;
	}
	coefficients.clear();
	const char* current = source;
	while (*current != '\0') {
		const char* next = std::strchr(current, '\\');
		std::string part = next ? std::string(current, next - current) : std::string(current);
		if (part.empty()) {
			return false;
		}
		for (size_t i = 0; i < part.size(); i++) {
			if (part[i] == '_') {
				part[i] = '-';
			}
		}
		char* end = nullptr;
		double value = std::strtod(part.c_str(), &end);
		if (end == part.c_str() || *end != '\0') {
			return false;
		}
		coefficients.push_back(value);
		if (next == nullptr) {
			break;
		}
		current = next + 1;
	}
	while (coefficients.size() > 1 && std::fabs(coefficients.front()) < 1E-12) {
		coefficients.erase(coefficients.begin());
	}
	return coefficients.size() > 1;
}

static std::complex<double> evaluatePolynomial(const std::vector<double>& coefficients, const std::complex<double>& x) {
	std::complex<double> result(0.0, 0.0);
	for (size_t i = 0; i < coefficients.size(); i++) {
		result = result * x + coefficients[i];
	}
	return result;
}

static std::complex<double> evaluateComplexPolynomial(const std::vector<std::complex<double>>& coefficients, const std::complex<double>& x) {
	std::complex<double> result(0.0, 0.0);
	for (size_t i = 0; i < coefficients.size(); i++) {
		result = result * x + coefficients[i];
	}
	return result;
}

static void appendEquationRoot(int index, const std::complex<double>& root) {
	double real = root.real();
	double imaginary = root.imag();
	if (std::fabs(real) < 5E-7) {
		real = 0.0;
	}
	if (std::fabs(imaginary) < 5E-7) {
		imaginary = 0.0;
	}
	std::string realText = formatEquationRootPart(real);
	std::string imaginaryText = formatEquationRootPart(std::fabs(imaginary));
	if (imaginary == 0.0) {
		sprintf(answers, "%sx%d=%s\n", answers, index, realText.c_str());
	}
	else if (imaginary > 0.0) {
		sprintf(answers, "%sx%d=%s+%si\n", answers, index, realText.c_str(), imaginaryText.c_str());
	}
	else {
		sprintf(answers, "%sx%d=%s-%si\n", answers, index, realText.c_str(), imaginaryText.c_str());
	}
}

static bool trySolveIntegerRootPolynomial(const std::vector<std::complex<double>>& coefficients) {
	if (coefficients.size() <= 2 || coefficients.size() > 80) {
		return false;
	}
	std::vector<long double> polynomial;
	polynomial.reserve(coefficients.size());
	for (size_t i = 0; i < coefficients.size(); i++) {
		if (std::fabs(coefficients[i].imag()) > 1E-7) {
			return false;
		}
		polynomial.push_back((long double)coefficients[i].real());
	}
	std::vector<long double> rootsFound;
	int currentDegree = (int)polynomial.size() - 1;
	while (currentDegree > 0) {
		bool found = false;
		for (int candidateAbs = 0; candidateAbs <= 1000 && !found; candidateAbs++) {
			for (int signIndex = 0; signIndex < 2 && !found; signIndex++) {
				if (candidateAbs == 0 && signIndex == 1) {
					continue;
				}
				long double candidate = signIndex == 0 ? (long double)candidateAbs : -(long double)candidateAbs;
				std::vector<long double> quotient((size_t)currentDegree, 0.0L);
				quotient[0] = polynomial[0];
				for (int i = 1; i < currentDegree; i++) {
					quotient[(size_t)i] = polynomial[(size_t)i] + candidate * quotient[(size_t)i - 1];
				}
				long double remainder = polynomial[(size_t)currentDegree] + candidate * quotient[(size_t)currentDegree - 1];
				long double scale = 1.0L;
				for (size_t i = 0; i < polynomial.size(); i++) {
					scale = std::max(scale, std::fabs(polynomial[i]));
				}
				if (std::fabs(remainder) <= scale * 1E-10L) {
					rootsFound.push_back(candidate);
					polynomial = quotient;
					currentDegree--;
					found = true;
				}
			}
		}
		if (!found) {
			break;
		}
	}
	if (currentDegree != 0 || rootsFound.empty()) {
		return false;
	}
	std::sort(rootsFound.begin(), rootsFound.end(), [](long double a, long double b) {
		return a > b;
	});
	sprintf(answers, "");
	for (size_t i = 0; i < rootsFound.size(); i++) {
		appendEquationRoot((int)i + 1, std::complex<double>((double)rootsFound[i], 0.0));
	}
	return true;
}

static bool trySolveCandidateComplexRootPolynomial(const std::vector<std::complex<double>>& coefficients, int zeroRootCount) {
	if (coefficients.size() <= 2 || coefficients.size() > 80) {
		return false;
	}
	std::vector<std::complex<double>> polynomial = coefficients;
	std::vector<std::complex<double>> rootsFound;
	while (polynomial.size() > 1) {
		bool found = false;
		std::complex<double> selectedRoot(0.0, 0.0);
		std::vector<std::complex<double>> selectedQuotient;
		std::vector<std::complex<double>> candidates;
		for (int value = 0; value <= 1000; value++) {
			candidates.push_back(std::complex<double>((double)value, 0.0));
			if (value != 0) {
				candidates.push_back(std::complex<double>(-(double)value, 0.0));
			}
		}
		for (int halfValue = 1; halfValue <= 2000; halfValue++) {
			double value = halfValue / 2.0;
			candidates.push_back(std::complex<double>(0.0, value));
			candidates.push_back(std::complex<double>(0.0, -value));
		}
		for (size_t candidateIndex = 0; candidateIndex < candidates.size() && !found; candidateIndex++) {
			std::complex<double> candidate = candidates[candidateIndex];
			int degree = (int)polynomial.size() - 1;
			std::vector<std::complex<double>> quotient((size_t)degree, std::complex<double>(0.0, 0.0));
			quotient[0] = polynomial[0];
			for (int i = 1; i < degree; i++) {
				quotient[(size_t)i] = polynomial[(size_t)i] + candidate * quotient[(size_t)i - 1];
			}
			std::complex<double> remainder = polynomial[(size_t)degree] + candidate * quotient[(size_t)degree - 1];
			double scale = 1.0;
			for (size_t i = 0; i < polynomial.size(); i++) {
				scale = std::max(scale, std::abs(polynomial[i]));
			}
			if (std::abs(remainder) <= scale * 1E-8) {
				selectedRoot = candidate;
				selectedQuotient = quotient;
				found = true;
			}
		}
		if (!found) {
			return false;
		}
		rootsFound.push_back(selectedRoot);
		polynomial = selectedQuotient;
	}
	for (int i = 0; i < zeroRootCount; i++) {
		rootsFound.push_back(std::complex<double>(0.0, 0.0));
	}
	std::sort(rootsFound.begin(), rootsFound.end(), [](const std::complex<double>& a, const std::complex<double>& b) {
		if (std::fabs(a.real() - b.real()) > 1E-7) {
			return a.real() > b.real();
		}
		return a.imag() < b.imag();
	});
	sprintf(answers, "");
	for (size_t i = 0; i < rootsFound.size(); i++) {
		appendEquationRoot((int)i + 1, rootsFound[i]);
	}
	return true;
}

static bool trySolveInternalPolynomialIntegerRootsMp(const std::string& normalized) {
	std::vector<mp_float> coefficientsByDegree;
	if (!collectInternalPolynomialMpCoefficients(normalized, coefficientsByDegree)) {
		return false;
	}
	int detectedDegree = (int)coefficientsByDegree.size() - 1;
	if (detectedDegree > 1 && detectedDegree <= 80 && abs(coefficientsByDegree[(size_t)detectedDegree] - 1) <= mp_float("1e-30")) {
		std::vector<mp_float> expectedByDegree(1, mp_float(1));
		for (int root = 1; root <= detectedDegree; root++) {
			std::vector<mp_float> next(expectedByDegree.size() + 1, mp_float(0));
			for (size_t i = 0; i < expectedByDegree.size(); i++) {
				next[i + 1] += expectedByDegree[i];
				next[i] -= mp_float(root) * expectedByDegree[i];
			}
			expectedByDegree = next;
		}
		bool matchesConsecutiveRoots = expectedByDegree.size() == coefficientsByDegree.size();
		for (size_t i = 0; i < coefficientsByDegree.size() && matchesConsecutiveRoots; i++) {
			mp_float scale = abs(expectedByDegree[i]);
			if (scale < 1) {
				scale = 1;
			}
			if (abs(coefficientsByDegree[i] - expectedByDegree[i]) > scale * mp_float("1e-10")) {
				matchesConsecutiveRoots = false;
			}
		}
		if (matchesConsecutiveRoots) {
			sprintf(answers, "");
			for (int root = detectedDegree; root >= 1; root--) {
				appendEquationRoot(detectedDegree - root + 1, std::complex<double>((double)root, 0.0));
			}
			return true;
		}
	}
	std::vector<mp_float> polynomial;
	polynomial.reserve(coefficientsByDegree.size());
	for (int degree = (int)coefficientsByDegree.size() - 1; degree >= 0; degree--) {
		polynomial.push_back(coefficientsByDegree[(size_t)degree]);
	}
	if (polynomial.size() <= 2 || polynomial.size() > 80 || abs(polynomial[0]) < mp_float("1e-40")) {
		return false;
	}
	std::vector<int> rootsFound;
	int currentDegree = (int)polynomial.size() - 1;
	while (currentDegree > 0) {
		bool found = false;
		for (int candidateAbs = 0; candidateAbs <= 1000 && !found; candidateAbs++) {
			for (int signIndex = 0; signIndex < 2 && !found; signIndex++) {
				if (candidateAbs == 0 && signIndex == 1) {
					continue;
				}
				mp_float candidate = signIndex == 0 ? mp_float(candidateAbs) : -mp_float(candidateAbs);
				std::vector<mp_float> quotient((size_t)currentDegree, mp_float(0));
				quotient[0] = polynomial[0];
				for (int i = 1; i < currentDegree; i++) {
					quotient[(size_t)i] = polynomial[(size_t)i] + candidate * quotient[(size_t)i - 1];
				}
				mp_float remainder = polynomial[(size_t)currentDegree] + candidate * quotient[(size_t)currentDegree - 1];
				mp_float scale = 1;
				for (size_t i = 0; i < polynomial.size(); i++) {
					mp_float magnitude = abs(polynomial[i]);
					if (magnitude > scale) {
						scale = magnitude;
					}
				}
				if (abs(remainder) <= scale * mp_float("1e-35")) {
					rootsFound.push_back(signIndex == 0 ? candidateAbs : -candidateAbs);
					polynomial = quotient;
					currentDegree--;
					found = true;
				}
			}
		}
		if (!found) {
			break;
		}
	}
	if (currentDegree != 0 || rootsFound.empty()) {
		return false;
	}
	std::sort(rootsFound.begin(), rootsFound.end(), [](int a, int b) {
		return a > b;
	});
	sprintf(answers, "");
	for (size_t i = 0; i < rootsFound.size(); i++) {
		appendEquationRoot((int)i + 1, std::complex<double>((double)rootsFound[i], 0.0));
	}
	return true;
}

static bool solveDescendingComplexCoefficientEquation(const std::vector<std::complex<double>>& coefficients) {
	std::vector<std::complex<double>> activeCoefficients = coefficients;
	int zeroRootCount = 0;
	while (activeCoefficients.size() > 1 && std::abs(activeCoefficients.back()) < 1E-12) {
		activeCoefficients.pop_back();
		zeroRootCount++;
	}
	int degree = (int)activeCoefficients.size() - 1;
	if ((degree <= 0 && zeroRootCount == 0) || degree > 120 || std::abs(activeCoefficients.front()) < 1E-12) {
		return false;
	}
	if (degree <= 0) {
		sprintf(answers, "");
		for (int i = 0; i < zeroRootCount; i++) {
			appendEquationRoot(i + 1, std::complex<double>(0.0, 0.0));
		}
		return true;
	}
	if (zeroRootCount == 0 && trySolveIntegerRootPolynomial(activeCoefficients)) {
		return true;
	}
	if (trySolveCandidateComplexRootPolynomial(activeCoefficients, zeroRootCount)) {
		return true;
	}
	if (degree == 1) {
		sprintf(answers, "");
		appendEquationRoot(1, -activeCoefficients[1] / activeCoefficients[0]);
		for (int i = 0; i < zeroRootCount; i++) {
			appendEquationRoot(i + 2, std::complex<double>(0.0, 0.0));
		}
		return true;
	}
	std::vector<std::complex<double>> rootsLocal((size_t)degree);
	double radius = 1.0;
	for (size_t i = 1; i < activeCoefficients.size(); i++) {
		radius = std::max(radius, 1.0 + std::abs(activeCoefficients[i] / activeCoefficients.front()));
	}
	for (int i = 0; i < degree; i++) {
		double angle = 2.0 * M_PI * i / degree;
		rootsLocal[(size_t)i] = std::polar(radius, angle);
	}
	for (int iteration = 0; iteration < 4000; iteration++) {
		double maxDelta = 0.0;
		for (int i = 0; i < degree; i++) {
			std::complex<double> denominator = activeCoefficients.front();
			for (int j = 0; j < degree; j++) {
				if (i != j) {
					denominator *= rootsLocal[(size_t)i] - rootsLocal[(size_t)j];
				}
			}
			if (std::abs(denominator) < 1E-30) {
				rootsLocal[(size_t)i] += std::complex<double>(1E-8 * (i + 1), -1E-8 * (i + 1));
				continue;
			}
			std::complex<double> delta = evaluateComplexPolynomial(activeCoefficients, rootsLocal[(size_t)i]) / denominator;
			if (!std::isfinite(delta.real()) || !std::isfinite(delta.imag())) {
				return false;
			}
			rootsLocal[(size_t)i] -= delta;
			maxDelta = std::max(maxDelta, std::abs(delta));
		}
		if (maxDelta < 1E-12) {
			break;
		}
	}
	std::sort(rootsLocal.begin(), rootsLocal.end(), [](const std::complex<double>& a, const std::complex<double>& b) {
		if (std::fabs(a.real() - b.real()) > 1E-7) {
			return a.real() > b.real();
		}
		return a.imag() < b.imag();
	});
	sprintf(answers, "");
	for (int i = 0; i < degree; i++) {
		appendEquationRoot(i + 1, rootsLocal[(size_t)i]);
	}
	for (int i = 0; i < zeroRootCount; i++) {
		appendEquationRoot(degree + i + 1, std::complex<double>(0.0, 0.0));
	}
	return true;
}

static bool solveDescendingCoefficientEquation(const std::vector<double>& coefficients) {
	int degree = (int)coefficients.size() - 1;
	if (degree <= 0 || degree > 120 || std::fabs(coefficients.front()) < 1E-12) {
		return false;
	}
	if (degree == 1) {
		sprintf(answers, "");
		appendEquationRoot(1, std::complex<double>(-coefficients[1] / coefficients[0], 0.0));
		return true;
	}
	std::vector<std::complex<double>> rootsLocal((size_t)degree);
	double radius = 1.0;
	for (size_t i = 1; i < coefficients.size(); i++) {
		radius = std::max(radius, 1.0 + std::fabs(coefficients[i] / coefficients.front()));
	}
	for (int i = 0; i < degree; i++) {
		double angle = 2.0 * M_PI * i / degree;
		rootsLocal[(size_t)i] = std::polar(radius, angle);
	}
	for (int iteration = 0; iteration < 4000; iteration++) {
		double maxDelta = 0.0;
		for (int i = 0; i < degree; i++) {
			std::complex<double> denominator(coefficients.front(), 0.0);
			for (int j = 0; j < degree; j++) {
				if (i != j) {
					denominator *= rootsLocal[(size_t)i] - rootsLocal[(size_t)j];
				}
			}
			if (std::abs(denominator) < 1E-30) {
				rootsLocal[(size_t)i] += std::complex<double>(1E-8 * (i + 1), -1E-8 * (i + 1));
				continue;
			}
			std::complex<double> delta = evaluatePolynomial(coefficients, rootsLocal[(size_t)i]) / denominator;
			if (!std::isfinite(delta.real()) || !std::isfinite(delta.imag())) {
				return false;
			}
			rootsLocal[(size_t)i] -= delta;
			maxDelta = std::max(maxDelta, std::abs(delta));
		}
		if (maxDelta < 1E-12) {
			break;
		}
	}
	std::sort(rootsLocal.begin(), rootsLocal.end(), [](const std::complex<double>& a, const std::complex<double>& b) {
		if (std::fabs(a.real() - b.real()) > 1E-7) {
			return a.real() > b.real();
		}
		return a.imag() < b.imag();
	});
	sprintf(answers, "");
	for (int i = 0; i < degree; i++) {
		appendEquationRoot(i + 1, rootsLocal[(size_t)i]);
	}
	return true;
}

static bool solveCoefficientListEquation(const char* source) {
	std::vector<double> coefficients;
	if (!collectCoefficientList(source, coefficients)) {
		return false;
	}
	return solveDescendingCoefficientEquation(coefficients);
}

static bool solveLinearFactorProductEquation(const char* source) {
	if (source == nullptr) {
		return false;
	}
	std::string normalized = normalizeSimplePolynomialText(source);
	std::vector<std::string> factors;
	if (!splitTopLevelProductExpression(normalized, factors)) {
		factors.clear();
		factors.push_back(stripBalancedOuterParentheses(removeSpaces(normalized)));
	}
	if (factors.empty()) {
		return false;
	}
	std::vector<std::complex<long double>> rootsFound;
	rootsFound.reserve(factors.size());
	for (size_t i = 0; i < factors.size(); i++) {
		std::complex<long double> root(0.0L, 0.0L);
		if (!trySolveCommandLinearExpressionComplex(factors[i], root)) {
			return false;
		}
		rootsFound.push_back(root);
	}
	std::sort(rootsFound.begin(), rootsFound.end(), [](const std::complex<long double>& a, const std::complex<long double>& b) {
		if (std::fabsl(a.real() - b.real()) > 1E-12L) {
			return a.real() > b.real();
		}
		return a.imag() > b.imag();
	});
	sprintf(answers, "");
	for (size_t i = 0; i < rootsFound.size(); i++) {
		appendEquationRoot((int)i + 1, std::complex<double>((double)rootsFound[i].real(), (double)rootsFound[i].imag()));
	}
	return true;
}

static bool solveSimplePolynomialEquation(const char* source) {
	std::string normalized = normalizeSimplePolynomialText(source);
	if (solveLinearFactorProductEquation(normalized.c_str())) {
		return true;
	}
	if (trySolveInternalPolynomialIntegerRootsMp(normalized)) {
		return true;
	}
	std::vector<double> coefficients;
	if (collectSimplePolynomialCoefficients(normalized, coefficients) ||
		collectSimplePolynomialProductCoefficients(normalized, coefficients)) {
		std::vector<double> descending;
		descending.reserve(coefficients.size());
		for (int degree = (int)coefficients.size() - 1; degree >= 0; degree--) {
			descending.push_back(coefficients[(size_t)degree]);
		}
		return solveDescendingCoefficientEquation(descending);
	}
	std::vector<std::complex<double>> complexCoefficients;
	if (!collectSimplePolynomialComplexCoefficients(normalized, complexCoefficients) &&
		!collectSimplePolynomialProductComplexCoefficients(normalized, complexCoefficients) &&
		!collectInternalPolynomialComplexCoefficients(normalized, complexCoefficients)) {
		return false;
	}
	std::vector<std::complex<double>> descendingComplex;
	descendingComplex.reserve(complexCoefficients.size());
	for (int degree = (int)complexCoefficients.size() - 1; degree >= 0; degree--) {
		descendingComplex.push_back(complexCoefficients[(size_t)degree]);
	}
	return solveDescendingComplexCoefficientEquation(descendingComplex);
}


template<typename T>
bool commands(char* expression, char* path, T result1, T result2, FILE* save) {
	if (isContained("\\\\", expression)) {
		printf("\nError inside argument of command. \n\n ==> ATC has detected \"\\\" followed by  \"\\\", i.e. \"\\\\\".\n\n");
		return true;
	}
	replaceTimes = 0;
	int parenthesesL = countOccurrences("(", expression);
	int parenthesesR = countOccurrences(")", expression);
	if (parenthesesL != parenthesesR) {
		printf("\nError in parentheses. \n ==> The number of left and right parentheses entered must be equal.\n ==> The expression that you have entered has %d left parenthesis and %d right parenthesis.\n\n", parenthesesL, parenthesesR);
		return true;
	}
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\sendCommand.txt", atcPath);
	FILE* fp = fopen(toOpen, "w");
	if (fp != NULL) {
		fclose(fp);
	}
	char* arithTrig = getDynamicCharArray("", "arithTrig");
	sprintf(arithTrig, "%s", expression);
	FILE* fout = NULL, * fclean = NULL;
	char* stringV = getDynamicCharArray("", "stringV");
	fout = NULL;
	while (fout == NULL) {
		fout = fopen(path, "a+");
	}
	int i = 0, r = 0, year = 0, s = 0;
	bool command = false;

	i = 0;
	char* functionStudyCommand = getDynamicCharArray("", "functionStudyCommand");
	int functionStudyIndex = 0;
	for (int commandIndex = 0; commandIndex < abs((int)strlen(arithTrig)); commandIndex++) {
		if (arithTrig[commandIndex] != ' ' && arithTrig[commandIndex] != '\t') {
			functionStudyCommand[functionStudyIndex] = arithTrig[commandIndex];
			functionStudyIndex++;
		}
	}
	functionStudyCommand[functionStudyIndex] = '\0';
	if (isCommand(functionStudyCommand, "functionstudy")) {
		command = true;
		notUseHigherPrecison = true;
		if (functionStudyCommand[13] == '(') {
			int tDev = 14, tGet = 0;
			char* exprDev = getDynamicCharArray("", "exprDev");
			sprintf(exprDev, "");
			int parenthesisDepth = 1;
			while (tDev < abs((int)strlen(functionStudyCommand)) && parenthesisDepth > 0) {
				if (functionStudyCommand[tDev] == '(') {
					parenthesisDepth++;
				}
				if (functionStudyCommand[tDev] == ')') {
					parenthesisDepth--;
					if (parenthesisDepth == 0) {
						break;
					}
				}
				exprDev[tGet] = functionStudyCommand[tDev];
				tGet++; tDev++;
			}
			exprDev[tGet] = '\0';
			std::string reducedRationalProduct;
			bool rationalProductReduced = false;
			if (reduceExactRationalProductExpression(exprDev, reducedRationalProduct) && reducedRationalProduct.size() < (size_t)DIM) {
				sprintf(exprDev, "%s", reducedRationalProduct.c_str());
				rationalProductReduced = true;
			}
			char* data = getDynamicCharArray("", "data");
			sprintf(data, "");
			char* errorText = getDynamicCharArray("", "errorText");
			sprintf(errorText, "");
			sprintf(data, "%s", exprDev);
			sprintf(saveExpressionF, "%s", data);
			if (isContained(")(", data)) {
				replace(")(", ")*(", data);
				sprintf(data, "%s", expressionF);

			}
			char* solution = getDynamicCharArray("", "solution");
			sprintf(solution, "");
			synTest = 0;
			sprintf(roots, "");
			sprintf(OutputText, "");
			replaceTimes = 0;
			resultR = 0;
			resultI = 0;
			if (!isContained("x", data)) {
				puts("\nVariable 'x' is missing in your expression.\n");
			}
			else {
				synTest = 0;
				lastDividerR = 1;
				LastDividerR = 1;
				lastDividerI = 0;
				LastDividerI = 0;
				if (isContained("x/", data) && strStart == 0) {
					replace("x/", "(x-0)/", data);
					sprintf(data, "%s", expressionF);
				}
				if (isContained("/x", data) && strEnd == abs((int)strlen(data))) {
					replace("/x", "/(x-0)", data);
					sprintf(data, "%s", expressionF);
				}
				sprintf(solution, "%s", data);
				if (isContained("(x)", solution)) {
					replaceTimes = 0;
					replace("(x)", "x", solution);
					sprintf(solution, "%s", expressionF);
				}
				functionStudy<T>(solution);
			}
			_delete(exprDev, "exprDev");
			exprDev = nullptr;
			_delete(data, "data");
			data = nullptr;
			_delete(errorText, "errorText");
			errorText = nullptr;
			_delete(solution, "solution");
			solution = nullptr;
		}
		puts("");
		notUseHigherPrecison = false;
	}
	_delete(functionStudyCommand, "functionStudyCommand");
	functionStudyCommand = nullptr;
	if (isCommand(arithTrig, "graph")) {
		command = true;
		notUseHigherPrecison = true;
		if (arithTrig[5] == '(') {
			int tDev = 6, tGet = 0;
			char* exprDev = getDynamicCharArray("", "exprDev");
			sprintf(exprDev, "");
			while ((arithTrig[tDev] == ')' && arithTrig[tDev + 1] == '+' && arithTrig[tDev + 2] == '0' && arithTrig[tDev + 3] == '\0') == false && tDev < abs((int)strlen(arithTrig))) {
				exprDev[tGet] = arithTrig[tDev];
				tGet++; tDev++;
			}
			exprDev[tGet] = '\0';
			designGraph<T>(exprDev);
			_delete(exprDev, "exprDev");
			exprDev = nullptr;
		}
		puts("");
		notUseHigherPrecison = false;
	}
	if (isCommand(arithTrig, "memfactor")) {
		command = true;
		setMemFactor();
		puts("");
	}
	if (isCommand(arithTrig, "fft")) {
		command = true;
		if (arithTrig[3] == '(') {
			int tDev = 4, tGet = 0;
			char* exprDev = getDynamicCharArray("", "exprDev");
			sprintf(exprDev, "");
			while ((arithTrig[tDev] == ')' && arithTrig[tDev + 1] == '+' && arithTrig[tDev + 2] == '0' && arithTrig[tDev + 3] == '\0') == false && tDev < abs((int)strlen(arithTrig))) {
				exprDev[tGet] = arithTrig[tDev];
				tGet++; tDev++;
			}
			exprDev[tGet] = '\0';
			fft(exprDev);
			_delete(exprDev, "exprDev");
			exprDev = nullptr;
		}
	}
	if (isCommand(arithTrig, "ascendingorder")) {
		command = true;
		if (arithTrig[14] == '(') {
			int tDev = 15, tGet = 0;
			char* exprDev = getDynamicCharArray("", "exprDev");
			sprintf(exprDev, "");
			while ((arithTrig[tDev] == ')' && arithTrig[tDev + 1] == '+' && arithTrig[tDev + 2] == '0' && arithTrig[tDev + 3] == '\0') == false && tDev < abs((int)strlen(arithTrig))) {
				exprDev[tGet] = arithTrig[tDev];
				tGet++; tDev++;
			}
			exprDev[tGet] = '\0';
			ascendingOrder<T>(exprDev);
			_delete(exprDev, "exprDev");
			exprDev = nullptr;
		}
	}
	if (isCommand(arithTrig, "descendingorder")) {
		command = true;
		if (arithTrig[15] == '(') {
			int tDev = 16, tGet = 0;
			char* exprDev = getDynamicCharArray("", "exprDev");
			sprintf(exprDev, "");
			while ((arithTrig[tDev] == ')' && arithTrig[tDev + 1] == '+' && arithTrig[tDev + 2] == '0' && arithTrig[tDev + 3] == '\0') == false && tDev < abs((int)strlen(arithTrig))) {
				exprDev[tGet] = arithTrig[tDev];
				tGet++; tDev++;
			}
			exprDev[tGet] = '\0';
			descendingOrder<T>(exprDev);
			_delete(exprDev, "exprDev");
			exprDev = nullptr;
		}
	}
	if (isCommand(arithTrig, "ifft")) {
		command = true;
		if (arithTrig[4] == '(') {
			int tDev = 5, tGet = 0;
			char* exprDev = getDynamicCharArray("", "exprDev");
			sprintf(exprDev, "");
			while ((arithTrig[tDev] == ')' && arithTrig[tDev + 1] == '+' && arithTrig[tDev + 2] == '0' && arithTrig[tDev + 3] == '\0') == false && tDev < abs((int)strlen(arithTrig))) {
				exprDev[tGet] = arithTrig[tDev];
				tGet++; tDev++;
			}
			exprDev[tGet] = '\0';
			ifft(exprDev);
			_delete(exprDev, "exprDev");
			exprDev = nullptr;
		}
	}
	if (isCommand(arithTrig, "simplifypolynomial")) {
		command = true;
		equation_solver = true;
		isDivisible = true;
		lastDividerR = 1, lastDividerI = 0;
		notUseHigherPrecison = true;
		if (arithTrig[18] == '(') {
			int tDev = 19, tGet = 0;
			char* exprDev = getDynamicCharArray("", "exprDev");
			sprintf(exprDev, "");
			while ((arithTrig[tDev] == ')' && arithTrig[tDev + 1] == '+' && arithTrig[tDev + 2] == '0' && arithTrig[tDev + 3] == '\0') == false && tDev < abs((int)strlen(arithTrig))) {
				exprDev[tGet] = arithTrig[tDev];
				tGet++; tDev++;
			}
			exprDev[tGet] = '\0';
			std::string reducedRationalProduct;
			bool rationalProductReduced = false;
			if (reduceExactRationalProductExpression(exprDev, reducedRationalProduct) && reducedRationalProduct.size() < (size_t)DIM) {
				sprintf(exprDev, "%s", reducedRationalProduct.c_str());
				rationalProductReduced = true;
			}
			char* data = getDynamicCharArray("", "data");
			sprintf(data, "");
			char* errorText = getDynamicCharArray("", "errorText");
			sprintf(errorText, "");
			polySimplifier = false;
			sprintf(data, "%s", exprDev);
			char* internalPolynomial = getDynamicCharArray("", "internalPolynomial");
			bool hasInternalPolynomial = convertSimplePolynomialToInternalPolynomial(data, internalPolynomial);
			if (rationalProductReduced && strcmp(data, "1") == 0) {
				sprintf(internalPolynomial, "(0+0i)x^1+(1+0i)");
				hasInternalPolynomial = true;
			}
			if (rationalProductReduced && hasInternalPolynomial) {
				sprintf(data, "%s", internalPolynomial);
			}
			if (hasInternalPolynomial) {
				sprintf(data, "%s", internalPolynomial);
			}
			sprintf(saveExpressionF, "%s", data);
			char* solution = getDynamicCharArray("", "solution");
			sprintf(solution, "");
			synTest = 0;
			if (dataVerifier<T>(data, (T)0, (T)0, 1, 1)) {
				sprintf(OutputText, "");
				replaceTimes = 0;
				resultR = 0;
				resultI = 0;
				if (!isContained("x", data)) {
					sprintf(solution, "\nVariable 'x' is missing in your expression.\n");
				}
				else {
					synTest = 0;
					lastDividerR = 0;
					LastDividerR = 0;
					lastDividerI = 0;
					LastDividerI = 0;
					replaceTimes = 0;
					if (rationalProductReduced && hasInternalPolynomial) {
						sprintf(expressionF, "%s", data);
					}
					else if (hasInternalPolynomial) {
						sprintf(expressionF, "");
						polySimplifier = true;
						simplifyPolynomial<T>(data);
						polySimplifier = false;
					}
					else {
						int parL = countOccurrences("(", data);
						int parR = countOccurrences(")", data);
						replaceTimes = 0;
						if (parL == 1 && parR == 1) {


							isContained("(", data);
							if (strStart == 0) {
								isContained(")", data);

								if (strEnd == abs((int)strlen(data))) {


									replace("(", "", data);
									replace(")", "", expressionF);
									sprintf(data, "%s", expressionF);


								}
							}
						}
						manageExpression<T>(data, (T)0, (T)0, 1);
						sprintf(data, "%s", expressionF);
						replaceTimes = 0;
						if (isContained("(x)", data)) {
							replace("(x)", "x", data);
							sprintf(data, "%s", expressionF);
						}
						sprintf(roots, "");
						sprintf(expressionF, "");
						simplifyExpression(data);
						sprintf(data, "(%s)*(0x^1+1)", expressionF);
						sprintf(roots, "");
						sprintf(expressionF, "");
						simplifyPolynomial<T>(data);
					}
					if (abs((int)strlen(expressionF)) > 0) {
						sprintf(solution, "%s", expressionF);
					}
					else {
						sprintf(solution, "Error: Impossible simplify that polynomial.");
					}

				}
				char* report = getDynamicCharArray("", "report");
				sprintf(report, "");
				sprintf(report, "\n%s\n", expressionF);
				puts(report);
				int option = processingTxtFile ? 0 : -1;
				while (option != 0 && option != 1) {
					I_O = true;
					puts("\nExport result? (Yes -> 1 \\ No -> 0)");
					option = (int)getValue<T>();
				}
				if (option == 1) {
					saveToReport(report);
				}
				_delete(report, "report");
				report = nullptr;
			}
			_delete(exprDev, "exprDev");
			exprDev = nullptr;
			_delete(internalPolynomial, "internalPolynomial");
			internalPolynomial = nullptr;
			_delete(data, "data");
			data = nullptr;
			_delete(errorText, "errorText");
			errorText = nullptr;
			_delete(solution, "solution");
			solution = nullptr;
		}
		puts("");
		notUseHigherPrecison = false;
	}
	if (isCommand(arithTrig, "disableatcintro")) {
		command = true;
		FILE* create = NULL;
		char* toOpen = getDynamicCharArray("", "toOpen");
		sprintf(toOpen, "");
		sprintf(toOpen, "%s\\aboutDisabled.txt", atcPath);
		create = fopen(toOpen, "w");
		if (create != NULL) {
			fclose(create);
			printf("\n==> Restart the application to apply changes entering \"restart atc\". <==\n\n");
		}
		else {
			printf("\n==> It was not possible to disable atc intro. <==\n\n");

		}
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
	}
	if (isCommand(arithTrig, "unitconversions")) {
		command = true;
		unitConversions<T>();
		puts("");
	}
	if (isCommand(arithTrig, "microeconomicscalculations")) {
		command = true;
		microeconomicsCalculations();
		puts("");
	}
	if (isCommand(arithTrig, "physicscalculations")) {
		notUseHigherPrecison = true;
		command = true;
		physicsCalculations();
		puts("");
		notUseHigherPrecison = false;
	}
	if (isCommand(arithTrig, "graphsettings")) {
		command = true;
		graphSettings<T>();
		puts("");
	}
	if (isCommand(arithTrig, "statisticscalculations")) {
		command = true;
		statisticsCalculations();
		puts("");
	}
	if (isCommand(arithTrig, "geometrycalculations")) {
		command = true;
		geometryCalculations<T>();
		puts("");
	}
	if (isCommand(arithTrig, "financialcalculations")) {
		command = true;
		financialCalculations();
		puts("");
	}
	if (isCommand(arithTrig, "composecommand")) {
		command = true;
		if (arithTrig[14] == '(') {
			int tDev = 15, tGet = 0;
			char* exprDev = getDynamicCharArray("", "exprDev");
			sprintf(exprDev, "");
			while ((arithTrig[tDev] == ')' && arithTrig[tDev + 1] == '+' && arithTrig[tDev + 2] == '0' && arithTrig[tDev + 3] == '\0') == false && tDev < abs((int)strlen(arithTrig))) {
				exprDev[tGet] = arithTrig[tDev];
				tGet++; tDev++;
			}
			exprDev[tGet] = '\0';
			stringVariableToString(exprDev);
			if (abs((int)strlen(variableSTring)) != 0) {
				atcProg<T>(variableSTring);
			}
			_delete(exprDev, "exprDev");
			exprDev = nullptr;
		}
	}
	if (isCommand(arithTrig, "atcProg")) {
		command = true;
		if (arithTrig[7] == '(') {
			int tDev = 8, tGet = 0;
			char* exprDev = getDynamicCharArray("", "exprDev");
			sprintf(exprDev, "");
			while ((arithTrig[tDev] == ')' && arithTrig[tDev + 1] == '+' && arithTrig[tDev + 2] == '0' && arithTrig[tDev + 3] == '\0') == false && tDev < abs((int)strlen(arithTrig))) {
				exprDev[tGet] = arithTrig[tDev];
				tGet++; tDev++;
			}
			exprDev[tGet] = '\0';
			atcProg<T>(exprDev);
			_delete(exprDev, "exprDev");
			exprDev = nullptr;
		}
		puts(" ");
	}
	if (isCommand(arithTrig, "if")) {
		command = true;
		if (arithTrig[2] == '(') {
			int tDev = 3, tGet = 0;
			char* exprDev = getDynamicCharArray("", "exprDev");
			sprintf(exprDev, "");
			while ((arithTrig[tDev] == ')' && arithTrig[tDev + 1] == '+' && arithTrig[tDev + 2] == '0' && arithTrig[tDev + 3] == '\0') == false && tDev < abs((int)strlen(arithTrig))) {
				exprDev[tGet] = arithTrig[tDev];
				tGet++; tDev++;
			}
			exprDev[tGet] = '\0';
			bool errorFound = false;
			int kr = 0, kl = 0;
			for (int i = 0; i < abs((int)strlen(exprDev)); i++) {
				if (exprDev[i] == '(') {
					kl++;
				}
				if (exprDev[i] == ')') {
					kr++;
				}
				if (kr > kl) {
					printf("\n\nError: Seems that you have entered right parentheses before the corresponding left parentheses.\n\n");
					errorFound = true;
					fputs("\nError: Seems that you have entered right parentheses before the corresponding left parentheses.\n", save);
					break;
				}
			}
			if (kr != kl && !errorFound) {
				printf("\n\nError: Seems that you entered parentheses are not matching correctly.\n\n");
				errorFound = true;
				fputs("\nError: Seems that you entered parentheses are not matching correctly.\n", save);

			}
			if (!errorFound) {
				replaceTimes = 1;
				returned = advancedEvaluator<T>(exprDev);
				if (runningScript == false && creatingMatrix == 0) {
					if (returned) {
						printf("\nTrue\n");
						fputs("\nTrue\n", save);
					}
					else {
						printf("\nFalse\n");
						fputs("\nFalse\n", save);
					}
				}

			}

			if (runningScript == false && creatingMatrix == 0) {
				puts(" ");
			}
			if (creatingMatrix == 0) {
				Clock(0);
			}
			_delete(exprDev, "exprDev");
			exprDev = nullptr;
		}
	}
	if (isCommand(arithTrig, "donate")) {
		command = true;
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"start https://sourceforge.net/p/advantrigoncalc/donate/?source=navbar\""), NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "atcfacebook")) {
		command = true;
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"start https://www.facebook.com/advantrigoncalc/\""), NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "atcsourceforge")) {
		command = true;
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"start https://sourceforge.net/projects/advantrigoncalc/\""), NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "trianglesrectanglessolver")) {
		command = true;
		trianglesRectanglesSolver<T>();
		puts("");
	}
	if (isCommand(arithTrig, "arithmeticmatrixsolver")) {
		command = true;
		arithmeticMatrixSolver();
		puts("");
	}
	if (isCommand(arithTrig, "currentsettings")) {
		command = true;
		currentSettings();
		puts("");
	}
	if (isCommand(arithTrig, "atcfromcmd")) {
		command = true;
		char* comm = getDynamicCharArray("", "comm");
		sprintf(comm, "");
		sprintf(comm, "/C \"setx PATH \"%%PATH%%;%s\"", atcPath);
		if (atcTestDisableExternalOpen()) {
			recordExternalOpen("atcFromCmd", comm);
		}
		else {
			using namespace std;
			std::string s = string(comm);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		}
		puts("\n==> You can now run cmd.exe and enter e.g. \"atc time\" <==\n");
		puts("");
		_delete(comm, "comm");
		comm = nullptr;
	}
	if (isCommand(arithTrig, "newatctab") || isCommand(arithTrig, "newatcinstance") || isCommand(arithTrig, "newtab") || isCommand(arithTrig, "newinstance")) {
		command = true;
		openNewATCInstance();
		puts("");
	}
	if (isCommand(arithTrig, "atcovercmd")) {
		command = true;
		puts("\n==> ATC is ready to process data. <==\n");
		int tD = 0;
		char* trigData = getDynamicCharArray("", "trigData");
		sprintf(trigData, "");
		clock_t start_processing, end_processing;
		do {
			usRFunctions[0] = ','; usRFuncTrans[0] = ',';
			usRFunctions[1] = '\0'; usRFuncTrans[1] = '\0';
			fflush(NULL);
			tD = 0;
			printf(">");
			gets_s(trigData, DIM);
			start_processing = clock();
			puts("\n==> Processing... <==\n");
			sprintf(path, "%s\\history.txt", atcPath);
			toSolve<T>(rf);
			for (tD = 0; trigData[tD] != 0; tD++) {
				if (trigData[tD] == '{') {
					trigData[tD] = '(';
				}
				if (trigData[tD] == '}') {
					trigData[tD] = ')';
				}
			}
			char* fTrig = getDynamicCharArray("", "fTrig");
			char* arithTrig = getDynamicCharArray("", "arithTrig");
			for (tD = 0; tD < abs((int)strlen(trigData)); tD++) {
				fflush(NULL);

				sprintf(fTrig, "");

				sprintf(arithTrig, "");
				fout = NULL;
				while (fout == NULL) {
					fout = fopen(path, "a+");
				}
				varRename[0] = '\0'; revariable[0] = '\0';
				validVar = 1;
				fTrig[0] = '\0';
				i = 0;
				int fl = 1, fr = 0;
				while (tD < abs((int)strlen(trigData)) && trigData[tD] != ',' && tD < abs((int)strlen(trigData))) {
					if (trigData[tD - 6] == 'p' && trigData[tD - 5] == 'r' && trigData[tD - 4] == 'i' && trigData[tD - 3] == 'n' && trigData[tD - 2] == 't' && trigData[tD - 1] == '(') {
						arithTrig[i] = trigData[tD];
						i++; tD++;
						while (fl > fr && tD < abs((int)strlen(trigData))) {
							if (trigData[tD] == '(') {
								fl++;
							}
							if (trigData[tD] == ')') {
								fr++;
							}
							arithTrig[i] = trigData[tD];
							i++; tD++;
						}
						arithTrig[i] = '\0';
					}
					else {
						arithTrig[i] = trigData[tD];
						i++; tD++;
					}
				}
				arithTrig[i] = '\0';
				sprintf(fTrig, "%s", arithTrig);
				if (!handleAtcOverCmdSolverFastPath<T>(arithTrig, fout)) {
					main_core<T>(arithTrig, fTrig, fout, path, result1, result2, 1);
				}
				sprintf(arithTrig, ""); sprintf(fTrig, ""); arithTrig[0] = '\0'; fTrig[0] = '\0';
				if (verified == 1) {
					result1 = precisionValueTo<T>(resultR);
					result2 = precisionValueTo<T>(resultI);
					verified = 0;
				}

			}
			_delete(fTrig, "fTrig");
			fTrig = nullptr;
			_delete(arithTrig, "arithTrig");
			arithTrig = nullptr;
			if (continu != 1) {
				fclose(fout);
			}
			char* Path = getDynamicCharArray("", "Path");
			sprintf(Path, "%s\\temp.txt", atcPath);
			FILE* Try = NULL;
			Try = fopen(Path, "r");
			if (Try != NULL) {
				fclose(Try);
				Try = fopen(Path, "w");
				fclose(Try);
			}
			end_processing = clock();
			T time_ms = (end_processing - start_processing) / (CLOCKS_PER_SEC / 1000);
			T time_s = qu<T>(time_ms, (T)1000);
			T time_ms_final = re<T>(time_ms, (T)1000);
			convertComplex2Exponential(time_s, time_ms_final);
			printf("==> Processed in %ss and %sms. ATC is ready to process more data. <==\n\n", respR, respI);
			_delete(Path, "Path");
			Path = nullptr;
		} while (continu == 1);
		_delete(trigData, "trigData");
		trigData = nullptr;
	}
	if (isCommand(arithTrig, "autosolvetxt")) {
		command = true;
		int p = 0;
		char* paTH = getDynamicCharArray("", "paTH");
		sprintf(paTH, "");
		i = 0;
		puts("\n==> Drag to here the file for automatic processing and press the button \"Enter\" <==\n");
		while (abs((int)strlen(paTH)) == 0) {
			gets_s(paTH, DIM);
		}
		puts("\n==> Waiting for the flag \"SOLVE_NOW\" be detected in the last line of this file. <==\n");
		bool ready = false;
		while (ready == readyToSolve(paTH)) {
			Sleep(2000);
		}
		processTxt<T>(paTH, rf);
		printf("\n==> Close the file with the answers to continue. <==\n\n");
		fprintf(fout, "\n==> Close the file with the answers to continue. <==\n\n");
		_delete(paTH, "paTH");
		paTH = nullptr;
		openTxt();
	}
	if (isCommand(arithTrig, "solveequation")) {
		ansRV = 0;
		ansIV = 0;
		command = true;
		equation_solver = true;
		notUseHigherPrecison = true;
		resultR = 0; resultI = 0;
		lastDividerR = 1, lastDividerI = 0, natureValue = 1;
		sprintf(roots, ""), sprintf(answers, "");
		isDivisible = true;
		lastDividerR = 1, lastDividerI = 0;

		if (arithTrig[13] == '(') {
			int tDev = 14, tGet = 0;
			char* exprDev = getDynamicCharArray("", "exprDev");
			while ((arithTrig[tDev] == ')' && arithTrig[tDev + 1] == '+' && arithTrig[tDev + 2] == '0' && arithTrig[tDev + 3] == '\0') == false && tDev < abs((int)strlen(arithTrig))) {
				exprDev[tGet] = arithTrig[tDev];
				tGet++; tDev++;
			}
			exprDev[tGet] = '\0';
			std::string reducedRationalProduct;
			if (reduceExactRationalProductExpression(exprDev, reducedRationalProduct) && reducedRationalProduct.size() < (size_t)DIM) {
				sprintf(exprDev, "%s", reducedRationalProduct.c_str());
			}
			if (abs((int)strlen(exprDev)) > 0) {
				polySimplifier = false;
				char* data = getDynamicCharArray("", "data");
				sprintf(data, "");
				sprintf(data, "%s", exprDev);
				char* coefficientData = getDynamicCharArray("", "coefficientData");
				char* report = getDynamicCharArray("", "report");
				bool solvedByBinomialFastPath = solvePureBinomialEquation(exprDev);
				bool solvedByCoefficientFastPath = !solvedByBinomialFastPath && solveCoefficientListEquation(exprDev);
				bool solvedBySimplePolynomialFastPath = !solvedByBinomialFastPath && !solvedByCoefficientFastPath && solveSimplePolynomialEquation(exprDev);
				bool rejectedKnownPolynomial = !solvedByBinomialFastPath && !solvedByCoefficientFastPath && !solvedBySimplePolynomialFastPath &&
					(isParenthesizedPolynomialProductSyntax(exprDev) || isInternalPolynomialSyntax(exprDev));
				if (solvedByBinomialFastPath || solvedByCoefficientFastPath || solvedBySimplePolynomialFastPath) {
					sprintf(report, "\n%s\n", answers);
					puts(report);
					int option = processingTxtFile ? 0 : -1;
					while (option != 0 && option != 1) {
						I_O = true;
						puts("\nExport result? (Yes -> 1 \\ No -> 0)");
						option = (int)getValue<T>();
					}
					if (option == 1) {
						saveToReport(report);
					}
				}
				else if (rejectedKnownPolynomial) {
					puts("\n==> ATC was unable to solve this polynomial with the fast polynomial path. <==\n");
				}
				if (convertSimplePolynomialToCoefficientList(data, coefficientData)) {
					sprintf(data, "%s", coefficientData);
				}
				sprintf(saveExpressionF, "%s", data);
				if (!solvedByBinomialFastPath && !solvedByCoefficientFastPath && !solvedBySimplePolynomialFastPath && !rejectedKnownPolynomial && !isContained("\\", data)) {
					if (isContained("x", exprDev)) {
						synTest = 0;

						if (dataVerifier<T>(data, (T)0, (T)0, 1, 1)) {
							sprintf(OutputText, "");
							replaceTimes = 0;
							lastDividerR = 0;
							LastDividerR = 0;
							lastDividerI = 0;
							LastDividerI = 0;
							sprintf(saveSimplified, "");
							sprintf(saveSimplification, "");
							sprintf(expressionF, "");
							replaceTimes = 0;

							int parL = countOccurrences("(", data);
							int parR = countOccurrences(")", data);

							replaceTimes = 0;
							if (parL == 1 && parR == 1) {
								isContained("(", data);
								if (strStart == 0) {
									isContained(")", data);
									if (strEnd == abs((int)strlen(data))) {
										replace("(", "", data);
										replace(")", "", expressionF);
										sprintf(data, "%s", expressionF);
									}
								}
							}

							manageExpression<T>(data, (T)0, (T)0, 1);
							sprintf(data, "%s", expressionF);
							replaceTimes = 0;

							if (isContained("(x)", data)) {
								replace("(x)", "x", data);
								sprintf(data, "%s", expressionF);
							}
							sprintf(roots, "");
							sprintf(expressionF, "");
							simplifyExpression(data);
							sprintf(roots, "");
							sprintf(data, "%s", expressionF);
							progress = true;
							equationSolver<T>(data);
							progress = false;
							sprintf(report, "");
							sprintf(report, "\n%s\n", answers);
							if (!isContained("IND", report)) {
								puts(report);
								int option = processingTxtFile ? 0 : -1;
								while (option != 0 && option != 1) {
									I_O = true;
									puts("\nExport result? (Yes -> 1 \\ No -> 0)");
									option = (int)getValue<T>();
								}
								if (option == 1) {
									saveToReport(report);
								}
							}
							else {
								puts("\n==> ATC was unable to calculate the solution for your polynomial. <==\n");
							}
							sprintf(OutputText, "");
							replaceTimes = 0;
							lastDividerR = 0;
							LastDividerR = 0;
							lastDividerI = 0;
							LastDividerI = 0;
							sprintf(saveSimplified, "");
							sprintf(saveSimplification, "");
							sprintf(expressionF, "");
						}
					}
					else {
						puts("\nError: No 'x' detected.");
					}
				}
				else if (!solvedByBinomialFastPath && !solvedByCoefficientFastPath && !solvedBySimplePolynomialFastPath && !rejectedKnownPolynomial) {
					synTest = 0;
					sprintf(report, "");
					if (dataVerifier<T>(data, (T)0, (T)0, 1, 1)) {
						sprintf(OutputText, "");
						replaceTimes = 0;
						lastDividerR = 0;
						LastDividerR = 0;
						lastDividerI = 0;
						LastDividerI = 0;
						sprintf(saveSimplified, "");
						sprintf(saveSimplification, "");
						sprintf(expressionF, "");
						replaceTimes = 0;
						int parL = countOccurrences("(", data);
						int parR = countOccurrences(")", data);
						replaceTimes = 0;
						if (parL == 1 && parR == 1) {
							isContained("(", data);
							if (strStart == 0) {
								isContained(")", data);
								if (strEnd == abs((int)strlen(data))) {
									replace("(", "", data);
									replace(")", "", expressionF);
									sprintf(data, "%s", expressionF);
								}
							}
						}
						progress = true;
						equationSolver<T>(data);
						progress = false;
						sprintf(report, "\n%s\n", answers);
						puts(report);
						int option = processingTxtFile ? 0 : -1;
						while (option != 0 && option != 1) {

							I_O = true;
							puts("\nExport result? (Yes -> 1 \\ No -> 0)");
							option = (int)getValue<T>();
						}
						if (option == 1) {
							saveToReport(report);
						}
						sprintf(OutputText, "");
						replaceTimes = 0;
						lastDividerR = 0;
						LastDividerR = 0;
						lastDividerI = 0;
						LastDividerI = 0;
						sprintf(saveSimplified, "");
						sprintf(saveSimplification, "");
					}
				}
				_delete(exprDev, "exprDev");
				exprDev = nullptr;
				_delete(data, "data");
				data = nullptr;
				_delete(coefficientData, "coefficientData");
				coefficientData = nullptr;



				_delete(report, "report");
				report = nullptr;
			}
			else {
				puts("\nError: Empty input.");
			}
		}
		sprintf(arithTrig, "");
		puts("");
		notUseHigherPrecison = false;
		ansRV = ans[rf - 1];
		ansIV = ansI[rf - 1];
		sprintf(expressionF, "");
		sprintf(expr, "");

	}
	if (isCommand(arithTrig, "rootstopolynomial")) {
		command = true;
		notUseHigherPrecison = true;
		if (arithTrig[17] == '(') {
			int tDev = 18, tGet = 0;
			char* exprDev = getDynamicCharArray("", "exprDev");
			sprintf(exprDev, "");
			while ((arithTrig[tDev] == ')' && arithTrig[tDev + 1] == '+' && arithTrig[tDev + 2] == '0' && arithTrig[tDev + 3] == '\0') == false && tDev < abs((int)strlen(arithTrig))) {
				exprDev[tGet] = arithTrig[tDev];
				tGet++; tDev++;
			}
			exprDev[tGet] = '\0';
			polySimplifier = false;
			lastDividerR = 1, lastDividerI = 0;
			rootsToPolynomial(exprDev);
			puts("");
			puts(expressionF);
			char* reportF = getDynamicCharArray("", "reportF");
			sprintf(reportF, "");
			sprintf(reportF, "%s", expressionF);
			int option = processingTxtFile ? 0 : -1;
			while (option != 0 && option != 1) {
				I_O = true;
				puts("\nExport result? (Yes -> 1 \\ No -> 0)");
				option = (int)getValue<T>();
			}
			if (option == 1) {
				saveToReport(reportF);
			}
			_delete(exprDev, "exprDev");
			exprDev = nullptr;
			_delete(reportF, "reportF");
			reportF = nullptr;
		}
		puts("");
		notUseHigherPrecison = false;
	}
	if (isCommand(arithTrig, "solvequadraticequation") && arithTrig[i + 22] == '(') {
		puts("");
		command = true;
		solveQuadraticEquation(arithTrig, result1, result2, 1);
		puts("");
	}
	if (isCommand(arithTrig, "opentxt") && arithTrig[i + 7] == '(') {
		char* vaString = getDynamicCharArray("", "vaString");
		sprintf(vaString, "");
		int x = 0, y = 0;
		y = i + 8;
		for (x = 0; y < abs((int)strlen(arithTrig)) && (arithTrig[y - 1] == ')' && arithTrig[y] == '+' && arithTrig[y + 1] == '0' && arithTrig[y + 2] == '\0') == false; x++) {
			stringV[x] = arithTrig[y];
			y++;
		}
		stringV[x] = '\0';
		stringV[abs((int)strlen(stringV)) - 1] = '\0';
		sprintf(expressionF, "%s", stringV);
		replaceTimes = 0;
		if (isContained("\"", expressionF)) {
			replace("\"", "", expressionF);
		}
		if (isContained("RASF", expressionF)) {
			replaceTimes = 0;
			replace("RASF", " ", expressionF);
		}
		printf("\n==> Close the open file to continue. <==\n\n");
		openTxt();
		puts(" ");
		arithTrig[0] = '\0'; command = true;
		_delete(vaString, "vaString");
		vaString = nullptr;
	}
	if (isCommand(arithTrig, "sprint") && arithTrig[i + 6] == '(') {
		if (isContained("\",", arithTrig)) {
			char* arguments = getDynamicCharArray("", "arguments");
			sprintf(arguments, "");
			int p = 0, q = strEnd;
			while (q < abs((int)strlen(arithTrig))) {
				arguments[p] = arithTrig[q];
				p++; q++;
			}
			arguments[p] = '\0';
			char* saveArguments = getDynamicCharArray("", "saveArguments");
			sprintf(saveArguments, "");
			sprintf(saveArguments, "%s", arguments);
			renamer(arguments);
			replaceTimes = 1;
			if (!isEqual(arguments, saveArguments)) {
				replace(saveArguments, arguments, arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
			_delete(arguments, "arguments");
			arguments = nullptr;
			_delete(saveArguments, "saveArguments");
			saveArguments = nullptr;
		}
		char* vaString = getDynamicCharArray("", "vaString");
		sprintf(vaString, "");
		int x = 0, y = 0;
		y = i + 7;
		for (x = 0; y < abs((int)strlen(arithTrig)) && (arithTrig[y - 1] == ')' && arithTrig[y] == '+' && arithTrig[y + 1] == '0' && arithTrig[y + 2] == '\0') == false; x++) {
			stringV[x] = arithTrig[y];
			y++;
		}
		stringV[x] = '\0';
		stringV[abs((int)strlen(stringV)) - 1] = '\0';
		sprint(stringV, result1, result2);
		puts(" ");
		arithTrig[0] = '\0'; command = true;
		_delete(vaString, "vaString");
		vaString = nullptr;
	}
	if (isCommand(arithTrig, "asciiorder")) {
		arithTrig[0] = '\0'; command = true;
		asciiOrder();
		fprintf(fout, "\n");
		printf("\n");
	}
	if (isCommand(arithTrig, "inverseasciiorder")) {
		arithTrig[0] = '\0'; command = true;
		inverseAsciiOrder();
		fprintf(fout, "\n");
		printf("\n");
	}
	if (isCommand(arithTrig, "print") && arithTrig[i + 5] == '(') {
		if (isContained("\",", arithTrig)) {
			char* arguments = getDynamicCharArray("", "arguments");
			sprintf(arguments, "");
			int p = 0, q = strEnd;
			while (q < abs((int)strlen(arithTrig))) {
				arguments[p] = arithTrig[q];
				p++; q++;
			}
			arguments[p] = '\0';
			char* saveArguments = getDynamicCharArray("", "saveArguments");
			sprintf(saveArguments, "");
			sprintf(saveArguments, "%s", arguments);
			renamer(arguments);
			replaceTimes = 1;
			if (!isEqual(arguments, saveArguments)) {
				replace(saveArguments, arguments, arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
			_delete(arguments, "arguments");
			arguments = nullptr;
			_delete(saveArguments, "saveArguments");
			saveArguments = nullptr;
		}
		char* vaString = getDynamicCharArray("", "vaString");
		sprintf(vaString, "");
		int x = 0, y = 0;
		y = i + 6;
		if (arithTrig[i + 6] != '\"') {
			for (x = 0; arithTrig[y] != ')' && ((arithTrig[y] == '+' && arithTrig[y + 1] == '0' && arithTrig[y + 2] == '\0') == false); x++) {
				vaString[x] = arithTrig[y];
				y++;
			}
			vaString[x] = '\0';
			stringVariableToString(vaString);
			if (abs((int)strlen(variableSTring)) != 0) {
				print(variableSTring, result1, result2);
				puts(" ");
			}
		}
		else {
			y = i + 7;
			for (x = 0; y < abs((int)strlen(arithTrig)) && (arithTrig[y] == ')' && arithTrig[y] == '+' && arithTrig[y + 1] == '0' && arithTrig[y + 2] == '\0') == false; x++) {
				stringV[x] = arithTrig[y];
				y++;
			}
			stringV[x] = '\0';
			stringV[abs((int)strlen(stringV)) - 3] = '\0';
			print(stringV, result1, result2);
			puts(" ");
		}
		arithTrig[0] = '\0'; command = true;
		_delete(vaString, "vaString");
		vaString = nullptr;
	}
	if (isCommand(arithTrig, "logoff")) {
		continu = 0;
		command = true;
		if (IsPreviousToWindowsVista()) {
			system("C:\\WINDOWS\\System32\\shutdown -l");
		}
		else {
			system("C:\\WINDOWS\\System32\\shutdown /l");
		}
	}
	if (isCommand(arithTrig, "enabletxtdetector")) {
		command = true;
		if (atcTestDisableExternalOpen()) {
			char* toOpen = getDynamicCharArray("", "toOpen");
			sprintf(toOpen, "%s\\disable_txt_detector.txt", atcPath);
			remove(toOpen);
			recordExternalOpen("enableTxtDetector", toOpen);
			_delete(toOpen, "toOpen");
			toOpen = nullptr;
		}
		else {
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"del disable_txt_detector.txt\""), NULL, SW_SHOW);
			Sleep(200);
		}
		puts(" ");
	}
	if (isCommand(arithTrig, "enableatcintro")) {
		command = true;
		puts(" ");
		FILE* start;
		char* path4ATC = getDynamicCharArray("", "path4ATC");
		sprintf(path4ATC, "");
		sprintf(path4ATC, "%s\\onStart.txt", atcPath);
		start = fopen(path4ATC, "w");
		fprintf(start, "enableatcintro");
		fclose(start);
		printf("\n==> Restart the application to apply changes entering \"restart atc\". <==\n\n");
		_delete(path4ATC, "path4ATC");
		path4ATC = nullptr;
	}
	if (isCommand(arithTrig, "history")) {
		command = true;
		puts(" ");
		printf("\n==> Close the history to continue. <==\n\n");
		char* path4ATC = getDynamicCharArray("", "path4ATC");
		sprintf(path4ATC, "");
		sprintf(path4ATC, "notepad.exe %s\\history.txt", atcPath);
		system(path4ATC);
		_delete(path4ATC, "path4ATC");
		path4ATC = nullptr;
	}
	if (isCommand(arithTrig, "resetall")) {
		command = true;
		puts(" ");
		FILE* start;
		char* path4ATC = getDynamicCharArray("", "path4ATC");
		sprintf(path4ATC, "");
		sprintf(path4ATC, "%s\\onStart.txt", atcPath);
		start = fopen(path4ATC, "w");
		fprintf(start, "resetall");
		fclose(start);
		printf("\n==> Restart the application to apply changes entering \"restart atc\". <==\n\n");
		_delete(path4ATC, "path4ATC");
		path4ATC = nullptr;
	}
	if (isCommand(arithTrig, "resetallnow")) {
		command = true;
		puts(" ");
		FILE* start;
		char* path4ATC = getDynamicCharArray("", "path4ATC");
		sprintf(path4ATC, "");
		sprintf(path4ATC, "%s\\onStart.txt", atcPath);
		start = fopen(path4ATC, "w");
		fprintf(start, "resetall");
		fclose(start);
		continu = 0;
		sprintf(path4ATC, "%s\\atc.exe", atcPath);
		using namespace std;
		std::string s = string(path4ATC);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), sw, NULL, NULL, SW_SHOW);
		_delete(path4ATC, "path4ATC");
		path4ATC = nullptr;
	}
	if (isCommand(arithTrig, "resetsettings")) {
		command = true;
		puts(" ");
		FILE* start;
		char* path4ATC = getDynamicCharArray("", "path4ATC");
		sprintf(path4ATC, "");
		sprintf(path4ATC, "%s\\onStart.txt", atcPath);
		start = fopen(path4ATC, "w");
		fprintf(start, "resetsettings");
		fclose(start);
		printf("\n==> Restart the application to apply changes entering \"restart atc\". <==\n\n");
		_delete(path4ATC, "path4ATC");
		path4ATC = nullptr;
	}
	if (isCommand(arithTrig, "resetsettingsnow")) {
		command = true;
		puts(" ");
		FILE* start;
		char* path4ATC = getDynamicCharArray("", "path4ATC");
		sprintf(path4ATC, "");
		sprintf(path4ATC, "%s\\onStart.txt", atcPath);
		start = fopen(path4ATC, "w");
		fprintf(start, "resetsettings");
		fclose(start);
		continu = 0;
		sprintf(path4ATC, "%s\\atc.exe", atcPath);
		using namespace std;
		std::string s = string(path4ATC);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), sw, NULL, NULL, SW_SHOW);
		_delete(path4ATC, "path4ATC");
		path4ATC = nullptr;
	}
	if (isCommand(arithTrig, "atcfolder")) {
		command = true;
		char* comm = getDynamicCharArray("", "comm");
		sprintf(comm, "");
		sprintf(comm, "/C \"explorer %s\"", atcPath);
		using namespace std;
		std::string s = string(comm);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		puts("");
		_delete(comm, "comm");
		comm = nullptr;
	}
	if (isCommand(arithTrig, "sourcecode")) {
		command = true;
		char* comm = getDynamicCharArray("", "comm");
		sprintf(comm, "");
		sprintf(comm, "/C \"explorer %s\\Source code\\\"", atcPath);
		using namespace std;
		std::string s = string(comm);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		puts("");
		_delete(comm, "comm");
		comm = nullptr;
	}
	if (isCommand(arithTrig, "scriptsexamples")) {
		command = true;
		char* comm = getDynamicCharArray("", "comm");
		sprintf(comm, "");
		sprintf(comm, "/C \"explorer %s\\Scripts examples\\\"", atcPath);
		using namespace std;
		std::string s = string(comm);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		puts("");
		_delete(comm, "comm");
		comm = nullptr;
	}
	if (isCommand(arithTrig, "strings")) {
		command = true;
		char* comm = getDynamicCharArray("", "comm");
		sprintf(comm, "");
		sprintf(comm, "/C \"explorer %s\\Strings\\\"", atcPath);
		using namespace std;
		std::string s = string(comm);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		puts("");
		_delete(comm, "comm");
		comm = nullptr;
	}
	if (isCommand(arithTrig, "userfunctions")) {
		command = true;
		char* comm = getDynamicCharArray("", "comm");
		sprintf(comm, "");
		sprintf(comm, "/C \"explorer %s\\User functions\\\"", atcPath);
		using namespace std;
		std::string s = string(comm);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		puts("");
		_delete(comm, "comm");
		comm = nullptr;
	}
	if (isCommand(arithTrig, "checkforupdates")) {
		command = true;
		check4Updates();
		puts("");
	}
	if (isCommand(arithTrig, "tosolve")) {
		command = true;
		char* comm = getDynamicCharArray("", "comm");
		sprintf(comm, "");
		sprintf(comm, "/C \"explorer %s\\To solve\\\"", atcPath);
		if (atcTestDisableExternalOpen()) {
			recordExternalOpen("toSolve", comm);
		}
		else {
			using namespace std;
			std::string s = string(comm);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		}
		puts("");
		_delete(comm, "comm");
		comm = nullptr;
	}
	if (isCommand(arithTrig, "restartatc")) {
		command = true;
		continu = 0;
		char* path4ATC = getDynamicCharArray("", "path4ATC");
		sprintf(path4ATC, "");
		sprintf(path4ATC, "%s\\atc.exe", atcPath);
		using namespace std;
		std::string s = string(path4ATC);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		_delete(path4ATC, "path4ATC");
		path4ATC = nullptr;
		ShellExecute(NULL, _T("open"), sw, NULL, NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "runatc")) {
		command = true;
		puts(" ");
		char* path4ATC = getDynamicCharArray("", "path4ATC");
		sprintf(path4ATC, "");
		sprintf(path4ATC, "%s\\atc.exe", atcPath);
		using namespace std;
		std::string s = string(path4ATC);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), sw, NULL, NULL, SW_SHOW);
		_delete(path4ATC, "path4ATC");
		path4ATC = nullptr;
	}
	if (isCommand(arithTrig, "updateportable")) {
		command = true;
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"start http://sourceforge.net/projects/advantrigoncalc/files/Advanced%20Trigonometry%20Calculator.zip/download\""), NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "update")) {
		command = true;
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"start https://sourceforge.net/projects/advantrigoncalc/files/Setup%20Advanced%20Trigonometry%20Calculator%20x86.exe/download\""), NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "updatex64")) {
		command = true;
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"start https://sourceforge.net/projects/advantrigoncalc/files/Setup%20Advanced%20Trigonometry%20Calculator%20x64.exe/download\""), NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "userguide")) {
		command = true;
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("Advanced Trigonometry Calculator - User Guide.pdf"), NULL, NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "sleep")) {
		command = true;
		puts(" ");
		ShellExecute(NULL, _T("runas"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"powercfg -hibernate off\""), NULL, SW_SHOW);
		Sleep(5000);
		system("C:\\WINDOWS\\System32\\Rundll32.exe powrprof.dll,SetSuspendState Sleep");
	}
	if (isCommand(arithTrig, "lock")) {
		command = true;
		puts(" ");
		system("C:\\WINDOWS\\System32\\Rundll32.exe User32.dll,LockWorkStation");
	}
	if (isCommand(arithTrig, "hibernate")) {
		command = true;
		puts(" ");
		ShellExecute(NULL, _T("runas"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"powercfg -hibernate on\""), NULL, SW_SHOW);
		Sleep(5000);
		system("C:\\WINDOWS\\System32\\rundll32.exe PowrProf.dll,SetSuspendState Hibernate");
	}
	if (isCommand(arithTrig, "shutdown")) {
		continu = 0;
		command = true;
		if (IsPreviousToWindowsVista()) {
			system("C:\\WINDOWS\\System32\\shutdown -s");
		}
		else {
			system("C:\\WINDOWS\\System32\\shutdown /s");
		}
	}
	if (isCommand(arithTrig, "shutdownnow")) {
		continu = 0;
		command = true;
		if (IsPreviousToWindowsVista()) {
			system("C:\\WINDOWS\\System32\\shutdown -s -t 0");
		}
		else {
			system("C:\\WINDOWS\\System32\\shutdown /s /t 0");
		}
	}
	if (isCommand(arithTrig, "restartpc")) {
		continu = 0;
		command = true;
		if (IsPreviousToWindowsVista()) {
			system("C:\\WINDOWS\\System32\\shutdown -r");
		}
		else {
			system("C:\\WINDOWS\\System32\\shutdown /r");
		}
	}
	if (isCommand(arithTrig, "restartpcnow")) {
		continu = 0;
		command = true;
		if (IsPreviousToWindowsVista()) {
			system("C:\\WINDOWS\\System32\\shutdown -r -t 0");
		}
		else {
			system("C:\\WINDOWS\\System32\\shutdown /r /t 0");
		}
	}
	if (isCommand(arithTrig, "exit")) {
		continu = 0;
		fprintf(fout, "\n");
		if (Pressed == 1) {
			char* toOpen = getDynamicCharArray("", "toOpen");
			sprintf(toOpen, "");
			sprintf(toOpen, "%s\\exit.txt", atcPath);
			FILE* exit = fopen(toOpen, "w");
			fclose(exit);
			_delete(toOpen, "toOpen");
			toOpen = nullptr;
		}
		command = true;
	}
	if (isCommand(arithTrig, "clean")) {
		cls(); command = true;
		arithTrig[0] = '\0';
		fprintf(fout, "\n");
	}
	if (isCommand(arithTrig, "about")) {
		arithTrig[0] = '\0'; command = true;
		cls();
		about2();
		fprintf(fout, "\n");
	}
	if (isCommand(arithTrig, "mode")) {
		arithTrig[0] = '\0'; command = true;
		printf("\n==> Configuration of mode <==\n\n");
		fprintf(fout, "\n==> Configuration of mode <==\n\n");
		mode();
		fprintf(fout, "\n");
		printf("\n");
	}
	if (isCommand(arithTrig, "cleanhistory")) {
		fclean = NULL;
		while (fclean == NULL) {
			fclean = fopen(path, "w");
		}command = true;
		fclose(fclean);
		printf("\n==> The history was cleaned sucessfully. <==\n\n");
		fprintf(fout, "\n==> The history was cleaned sucessfully. <==\n\n");
		arithTrig[0] = '\0';
	}
	if (isCommand(arithTrig, "colors")) {
		arithTrig[0] = '\0'; command = true;
		printf("\n==> Configuration of background and text colors <==\n\n");
		fprintf(fout, "\n==> Configuration of background and text colors <==\n\n");
		colors();
	}
	if (isCommand(arithTrig, "dimensions")) {
		arithTrig[0] = '\0'; command = true;
		printf("\n==> Dimensional configuration of the application window <==\n\n");
		fprintf(fout, "\n==> Dimensional configuration of the application window <==\n\n");
		dimensions();
	}
	if (isCommand(arithTrig, "window")) {
		arithTrig[0] = '\0'; command = true;
		printf("\n==> Configuration of the position, width and height of the application window <==\n\n");
		fprintf(fout, "\n==> Configuration of the position, width and height of the application window <==\n\n");
		window();
	}
	if (isCommand(arithTrig, "solveequationssystem") && arithTrig[i + 20] == '(') {
		int correct = 1, vi = 0, vj = 0;
		count = 2;
		if (arithTrig[i + 25] == '(') {
			i = i + 26;
		}
		else {
			if (arithTrig[i + 20] == '(') {
				i = i + 21;
			}
		}
		char* matrix = getDynamicCharArray("", "matrix");
		sprintf(matrix, "");
		int p = 0, countR = 0, countL = 0;
		for (p = i; p < abs((int)strlen(arithTrig)); p++) {
			if (arithTrig[p] == '(' || arithTrig[p] == '{') {
				countL++;
			}
			if (arithTrig[p] == ')' || arithTrig[p] == '}') {
				countR++;
			}
		}
		if (countR > 0) {
			countR--;
		}
		if (countL == countR) {
			processor(p,  i, countL,  countR,  arithTrig, matrix, fout, correct, result1);
		}
		else {
			printf("\nError in parentheses. \n ==> The number of left and right parenthesis entered must be equal.\n ==> Enter \"[\" or \"{\" is the same as \"(\" and \"]\" or \"}\" is the same as \")\".\n ==> The expression that you entered has %d left parenthesis and %d right parenthesis.\n\n\n", countL, countR);
			fprintf(fout, "\nError in parentheses. \n ==> The number of left and right parenthesis entered must be equal.\n ==> Enter \"[\" or \"{\" is the same as \"(\" and \"]\" or \"}\" is the same as \")\".\n ==> The expression that you entered has %d left parenthesis and %d right parenthesis.\n\n\n", countL, countR);
		}
		arithTrig[0] = '\0'; command = true;
		_delete(matrix, "matrix");
		matrix = nullptr;
	}
	if (isCommand(arithTrig, "autoadjustwindow")) {
		command = true;
		autoAdjustWindow();
	}
	if (isCommand(arithTrig, "eliminatevariables")) {
		FILE* open = NULL;
		int r = 0;
		char* toPath = getDynamicCharArray("", "toPath");
		sprintf(toPath, "");
		sprintf(toPath, "%s\\variables.txt", atcPath);
		while (open == NULL && r < 100) {
			open = fopen(toPath, "w");
			r++;
		}
		if (r < 100) {
			sprintf(saveVariablesTextFile, "");
			command = true;
			fclose(open);
			open = NULL;
			r = 0;
			char* toPath = getDynamicCharArray("", "toPath");
			sprintf(toPath, "");
			sprintf(toPath, "%s\\renamedVar.txt", atcPath);
			while (open == NULL && r < 100) {
				open = fopen(toPath, "w");
				r++;
			}
			if (r < 100) {
				fclose(open);
				sprintf(saveRenamedVariablesTextFile, "");
				printf("\n==> The variables were eliminated sucessfully. <==\n\n");
				fprintf(fout, "\n==> The variables were eliminated sucessfully. <==\n\n");
				arithTrig[0] = '\0';
			}
			_delete(toPath, "toPath");
			toPath = nullptr;
		}
		_delete(toPath, "toPath");
		toPath = nullptr;
	}
	if (isCommand(arithTrig, "eliminatestrings")) {
		FILE* open = NULL;
		int r = 0;
		char* toPath = getDynamicCharArray("", "toPath");
		sprintf(toPath, "");
		sprintf(toPath, "%s\\stringVariable.txt", atcPath);
		while (open == NULL && r < 100) {
			open = fopen(toPath, "w");
			r++;
		}
		if (r < 100) {
			command = true;
			fclose(open);
			if (atcTestDisableExternalOpen()) {
				char* stringsPath = getDynamicCharArray("", "stringsPath");
				const char* testStringsPath = getenv("ATC_TEST_STRINGS_DIR");
				if (testStringsPath != nullptr && testStringsPath[0] != '\0') {
					sprintf(stringsPath, "%s", testStringsPath);
				}
				else {
					sprintf(stringsPath, "%s\\Strings", atcPath);
				}
				DIR* directory = opendir(stringsPath);
				if (directory != NULL) {
					struct dirent* entry;
					while ((entry = readdir(directory)) != NULL) {
						if (entry->d_type == DT_REG) {
							char* filePath = getDynamicCharArray("", "filePath");
							sprintf(filePath, "%s\\%s", stringsPath, entry->d_name);
							remove(filePath);
							_delete(filePath, "filePath");
							filePath = nullptr;
						}
					}
					closedir(directory);
				}
				CreateDirectoryA(stringsPath, NULL);
				recordExternalOpen("eliminateStrings", stringsPath);
				_delete(stringsPath, "stringsPath");
				stringsPath = nullptr;
			}
			else {
				ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"rmdir /Q /S Strings\""), NULL, SW_SHOW);
				ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"mkdir Strings\""), NULL, SW_SHOW);
			}
			printf("\n==> The strings were eliminated sucessfully. <==\n\n");
			fprintf(fout, "\n==> The strings were eliminated sucessfully. <==\n\n");
			arithTrig[0] = '\0';
		}
		_delete(toPath, "toPath");
		toPath = nullptr;
	}
	if (isCommand(arithTrig, "stopwatch") && arithTrig[i + 9] == '(' || isCommand(arithTrig, "runstopwatch") && arithTrig[i + 12] == '(') {
		if (isCommand(arithTrig, "runstopwatch")) {
			command = true;
			char* comm = getDynamicCharArray("", "comm");
			sprintf(comm, "");
			char* commandToExecute = getDynamicCharArray("", "commandToExecute");
			replace("run", "", arithTrig);
			sprintf(commandToExecute, "%s", expressionF);
			replace("+0", "", commandToExecute);
			sprintf(commandToExecute, "%s", expressionF);
			sprintf(comm, "/C \"pause&\"%s\\atc.exe\" \"%s\"&pause&exit\"", atcPath, commandToExecute);
			using namespace std;
			std::string s = string(comm);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
			puts("");
			_delete(comm, "comm");
			comm = nullptr;
			_delete(commandToExecute, "commandToExecute");
			commandToExecute = nullptr;
		}
		else {
			ShowConsoleCursor(FALSE);
			printf("\nPress \"Enter\" button to mark time.\n");
			fprintf(fout, "\nPress \"Enter\" button to mark time.\n");
			int ct = 0, countT = 0;
			char* countTimes = getDynamicCharArray("", "countTimes");
			sprintf(countTimes, "");
			char* pause = getDynamicCharArray("", "pause");
			sprintf(pause, "");
			T stopTime = 0;
			if (arithTrig[i] == 'c') {
				i = i + 11;
			}
			else {
				i = i + 10;
			}
			ct = 0;
			while (i < abs((int)strlen(arithTrig)) && arithTrig[i] != ')') {
				countTimes[ct] = arithTrig[i];
				ct++; i++;
			}
			countTimes[ct] = '\0';
			countT = abs((int)calcNow(countTimes, result1, result2));
			if (verified == 1) {
				clock_t start, end;
				start = clock();
				ct = 0;
				while (ct < countT) {
					char* pause = getDynamicCharArray("", "pause");
					sprintf(pause, "");
					gets_s(pause, 1000);
					end = clock();
					stopTime = (T)(end - start) / CLOCKS_PER_SEC;
					int days = (int)qu<T>(stopTime, 86400);
					int hours = (int)qu<T>(re<T>(stopTime, 86400), 3600);
					int minutes = (int)qu<T>(re<T>(re<T>(stopTime, 86400), 3600), 60);
					int seconds = (int)re<T>(re<T>(re<T>(stopTime, 86400), 3600), 60);
					int miliseconds = (int)(1000 * (stopTime - qu<T>(stopTime, 1)));
					printf("t%d=", ct + 1);
					fprintf(fout, "t%d=", ct + 1);
					if (days != 0) {
						printf("%dd ", days);
						fprintf(fout, "%dd ", days);
					}
					if (hours != 0) {
						printf("%dh ", hours);
						fprintf(fout, "%dh ", hours);
					}
					if (minutes != 0) {
						printf("%dm ", minutes);
						fprintf(fout, "%dm ", minutes);
					}

					if (seconds != 0) {
						printf("%ds ", seconds);
						fprintf(fout, "%ds ", seconds);
					}
					if (miliseconds != 0) {
						printf("%dms ", miliseconds);
						fprintf(fout, "%dms ", miliseconds);
					}
					printf("\n");
					fprintf(fout, "\n");
					ct++;
					_delete(pause, "pause");
					pause = nullptr;
				}
				if (arG > 1) {
					exit(0);
				}
			}
			puts("");
			fputs("\n", fout);
			command = true;
			arithTrig[0] = '\0';
			ShowConsoleCursor(TRUE);
			_delete(countTimes, "countTimes");
			countTimes = nullptr;
			_delete(pause, "pause");
			pause = nullptr;
			_delete(toOpen, "toOpen");
			toOpen = nullptr;
			_delete(arithTrig, "arithTrig");
			arithTrig = nullptr;
			_delete(stringV, "stringV");
			stringV = nullptr;
			_delete(toOpen, "toOpen");
			toOpen = nullptr;
			_delete(arithTrig, "arithTrig");
			arithTrig = nullptr;
			_delete(stringV, "stringV");
			stringV = nullptr;
			return command;
		}
	}
	if (isCommand(arithTrig, "eliminateresults")) {
		r = 0; command = true;
		while (r < rf) {
			ans[r] = 0;
			ansI[r] = 0;
			sprintf(ansMatrices[r], "");
			r++;
		}
		rf = 0;
		printf("\n==> The results were eliminated successfully. <==\n\n");
		fprintf(fout, "\n==> The results were eliminated successfully. <==\n\n");
		sprintf(arithTrig, "");
	}
	if (isCommand(arithTrig, "seestrings")) {
		FILE* open = NULL;
		int r = 0;
		char* toOpen = getDynamicCharArray("", "toOpen");
		sprintf(toOpen, "");
		sprintf(toOpen, "%s\\stringVariable.txt", atcPath);
		while (open == NULL && r < 100) {
			open = fopen(toOpen, "a+");
			r++;
		}
		if (r < 100) {
			command = true;
			int w;
			char* seeVar = getDynamicCharArray("", "seeVar");
			sprintf(seeVar, "");
			for (w = 0; (seeVar[w] = fgetc(open)) != EOF; w++);
			seeVar[w] = '\0';
			fclose(open);
			if (0 < abs((int)strlen(seeVar))) {
				printf("\nString name\n\n%s\n", seeVar);
				fprintf(fout, "\nString name\n\n%s\n", seeVar);
			}
			else {
				printf("\n==> No string created! <==\n\n");
				fprintf(fout, "\n==> No string created! <==\n\n");
			}
			arithTrig[0] = '\0';
			_delete(seeVar, "seeVar");
			seeVar = nullptr;
		}
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
	}
	if (isCommand(arithTrig, "seevariables")) {
		FILE* open = NULL;
		int r = 0;
		char* toOpen = getDynamicCharArray("", "toOpen");
		sprintf(toOpen, "");
		sprintf(toOpen, "%s\\variables.txt", atcPath);
		while (open == NULL && r < 100) {
			open = fopen(toOpen, "a+");
			r++;
		}
		if (r < 100) {
			command = true;
			int w;
			char* seeVar = getDynamicCharArray("", "seeVar");
			sprintf(seeVar, "");
			for (w = 0; (seeVar[w] = fgetc(open)) != EOF; w++);
			seeVar[w] = '\0';
			fclose(open);
			if (0 < abs((int)strlen(seeVar))) {
				printf("\nVariable value\n\n%s\n", seeVar);
				fprintf(fout, "\nVariable value\n\n%s\n", seeVar);
			}
			else {
				printf("\n==> No variable created! <==\n\n");
				fprintf(fout, "\n==> No variable created! <==\n\n");
			}
			arithTrig[0] = '\0';
			_delete(seeVar, "seeVar");
			seeVar = nullptr;
		}
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
	}
	if (isCommand(arithTrig, "eliminateabbreviations")) {
		FILE* open = NULL;	 command = true;
		char* toOpen = getDynamicCharArray("", "toOpen");
		sprintf(toOpen, "");
		sprintf(toOpen, "%s\\pathName.txt", atcPath);
		while (open == NULL) {
			open = fopen(toOpen, "w");
		}
		printf("\n==> The abbreviations were eliminated successfully. <==\n\n");
		fprintf(fout, "\n==> The abbreviations were eliminated successfully. <==\n\n");
		arithTrig[0] = '\0';
		fclose(open);
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
	}
	if (isCommand(arithTrig, "seeabbreviations")) {
		FILE* open = NULL;	   command = true;
		char* toOpen = getDynamicCharArray("", "toOpen");
		sprintf(toOpen, "");
		sprintf(toOpen, "%s\\pathName.txt", atcPath);
		while (open == NULL) {
			open = fopen(toOpen, "a+");
		}
		char* dataPath = getDynamicCharArray("", "dataPath");
		sprintf(dataPath, "");
		int b = 0;
		for (b = 0; (dataPath[b] = fgetc(open)) != EOF; b++);
		dataPath[b] = '\0';
		arithTrig[0] = '\0'; command = true;
		if (0 < abs((int)strlen(dataPath))) {
			printf("\nAbbreviations paths\n\n%s\n", dataPath);
			fprintf(fout, "\nAbbreviations paths\n\n%s\n", dataPath);
		}
		else {
			printf("\n==> No abbreviation created! <==\n\n");
			fprintf(fout, "\n==> No abbreviation created! <==\n\n");
		}
		fclose(open);
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
		_delete(dataPath, "dataPath");
		dataPath = nullptr;
	}
	if (isCommand(arithTrig, "seeresults")) {
		arithTrig[0] = '\0'; command = true;
		if (rf > 0) {
			printf("\nResult value\n\n");
			fprintf(fout, "\nResult value\n\n");
			r = 0;
			while (r < rf) {
				if (strlen(ansMatrices[r]) == 0) {
					convertComplex2Exponential(ans[r], ansI[r]);
					if (ans[r] > 0 && ansI[r] > 0) {
						printf("#%d=%s+%si\n", r, respR, respI);
						fprintf(fout, "#%d=%s+%si\n", r, respR, respI);
					}
					if (ans[r] > 0 && ansI[r] < 0) {
						printf("#%d=%s%si\n", r, respR, respI);
						fprintf(fout, "#%d=%s%si\n", r, respR, respI);
					}
					if (ans[r] < 0 && ansI[r] > 0) {
						printf("#%d=%s+%si\n", r, respR, respI);
						fprintf(fout, "#%d=%s+%si\n", r, respR, respI);
					}
					if (ans[r] < 0 && ansI[r] < 0) {
						printf("#%d=%s%si\n", r, respR, respI);
						fprintf(fout, "#%d=%s%si\n", r, respR, respI);
					}
					if (ans[r] == 0 && ansI[r] == 0) {
						printf("#%d=%s\n", r, respR);
						fprintf(fout, "#%d=%s\n", r, respR);
					}
					if (ans[r] == 0 && ansI[r] != 0) {
						printf("#%d=%si\n", r, respI);
						fprintf(fout, "#%d=%si\n", r, respI);
					}
					if (ans[r] != 0 && ansI[r] == 0) {
						printf("#%d=%s\n", r, respR);
						fprintf(fout, "#%d=%s\n", r, respR);
					}
				}
				else {
					convert2Vector(ansMatrices[r]);
					char* report = getDynamicCharArray("", "report");
					sprintf(report, "");
					for (i = 0; i < numVectorLines; i++) {
						for (int k = 0; k < numVectorCols; k++) {
							convertComplex2Exponential(vectorR[i][k], vectorI[i][k]);
							sprintf(report, "%s%s+%si ", report, respR, respI);
						}
						sprintf(report, "%s\n", report);
					}
					printf("#%d=\n", r);
					puts(report);
					fprintf(fout, "#%d=\n%s", r, report);
					_delete(report, "report");
					report = nullptr;
				}
				r++;
			}
			printf("\n");
			fprintf(fout, "\n");
		}
		else {
			printf("\n==> No calculated result! <==\n\n");
			fprintf(fout, "\n==> No calculated result! <==\n\n");
		}
	}
	if (isCommand(arithTrig, "renamedvariables")) {
		arithTrig[0] = '\0'; command = true;
		FILE* open = NULL;
		int r = 0;
		char* toOpen = getDynamicCharArray("", "toOpen");
		sprintf(toOpen, "");
		sprintf(toOpen, "%s\\renamedVar.txt", atcPath);
		while (open == NULL && r < 100) {
			open = fopen(toOpen, "a+");
			r++;
		}
		if (r < 100) {
			int w;
			char* seeVar = getDynamicCharArray("", "seeVar");
			sprintf(seeVar, "");
			for (w = 0; (seeVar[w] = fgetc(open)) != EOF; w++);
			seeVar[w] = '\0';
			fclose(open);
			if (0 < abs((int)strlen(seeVar))) {
				printf("\nVariable renaming\n\n%s\n", seeVar);
				fprintf(fout, "\nVariable renaming\n\n%s\n", seeVar);
			}
			else {
				printf("\n==> No variable created! <==\n\n");
				fprintf(fout, "\n==> No variable created! <==\n\n");
			}
			_delete(seeVar, "seeVar");
			seeVar = nullptr;
		}
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
	}
	if (isCommand(arithTrig, "numericalsystems")) {
		char* arithTrig = getDynamicCharArray("", "arithTrig");
		sprintf(arithTrig, ""); command = true;
		arithTrig[0] = '\0';
		printf("\n==> Configuration of numerical systems response <==\n\n");
		fprintf(fout, "\n==> Configuration of numerical systems response <==\n\n");
		numSystemsController<T>();
		fprintf(fout, "\n");
		printf("\n");
		_delete(arithTrig, "arithTrig");
		arithTrig = nullptr;
	}
	if (isCommand(arithTrig, "higherprecision")) {
		int requestedState = -1;
		if (arithTrig[15] == '(' && (arithTrig[16] == '0' || arithTrig[16] == '1')) {
			requestedState = arithTrig[16] - '0';
		}
		char* arithTrig = getDynamicCharArray("", "arithTrig");
		sprintf(arithTrig, ""); command = true;
		arithTrig[0] = '\0';
		printf("\n==> Configuration of higher precision to improve precision of calculations <==\n\n");
		fprintf(fout, "\n==> Configuration of higher precision to improve precision of calculations <==\n\n");
		higherPrecisionController<T>(requestedState);
		fprintf(fout, "\n");
		printf("\n");
		_delete(arithTrig, "arithTrig");
		arithTrig = nullptr;
	}
	if (isCommand(arithTrig, "timer") && arithTrig[i + 5] == '(' || isCommand(arithTrig, "runtimer") && arithTrig[i + 8] == '(') {
		if (isCommand(arithTrig, "runtimer")) {
			command = true;
			char* comm = getDynamicCharArray("", "comm");
			sprintf(comm, "");
			char* commandToExecute = getDynamicCharArray("", "commandToExecute");
			sprintf(commandToExecute, "");
			replace("run", "", arithTrig);
			sprintf(commandToExecute, "%s", expressionF);
			replace("+0", "", commandToExecute);
			sprintf(commandToExecute, "%s", expressionF);
			sprintf(comm, "/C \"MODE con cols=69 lines=13&\"%s\\atc.exe\" \"%s\"&exit\"", atcPath, commandToExecute);
			using namespace std;
			std::string s = string(comm);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
			puts("");
			_delete(comm, "comm");
			comm = nullptr;
			_delete(commandToExecute, "commandToExecute");
			commandToExecute = nullptr;
		}
		else {
			cls();
			ShowConsoleCursor(FALSE);
			if (arithTrig[i + 5] == '(') {
				i = i + 6;

			}
			int t = i, p = 0;
			for (t; t < abs((int)strlen(arithTrig)); t++) {
				if (arithTrig[t] == ')') {
					p++;
				}
			}
			if (p != 1) {
				printf("\n\n==> You need to terminate the expression with ')' character. <==\n\n");
			}
			else {
				char* timeF = getDynamicCharArray("", "timeF");
				sprintf(timeF, "");
				sprintf(expression, "");
				t = 0;
				int b = i;
				while (arithTrig[b] != ')') {
					expression[t] = arithTrig[b];
					b++; t++;
				}
				expression[t] = '\0';
				b = 0;
				int sep = 0;
				for (t = 0; t < abs((int)strlen(expression)); t++) {
					if (expression[t] == ':' || expression[t] == '0' || expression[t] == '1' || expression[t] == '2' || expression[t] == '3' || expression[t] == '4' || expression[t] == '5' || expression[t] == '6' || expression[t] == '7' || expression[t] == '8' || expression[t] == '9') {
						b++;
						if (expression[t] == ':') {
							sep++;
						}
					}
				}
				if (b == abs((int)strlen(expression)) && sep == 2) {
					sprintf(timeF, "");
					t = 0;
					while (arithTrig[i] != ':' && arithTrig[i] != ')') {
						timeF[t] = arithTrig[i];
						t++; i++;
					}
					i++;
					timeF[t] = '\0';
					int hours = (int)calcNow(timeF, result1, result2);
					if (verified == 1) {
						sprintf(timeF, "");
						t = 0;
						while (arithTrig[i] != ':' && arithTrig[i] != ')' && i < abs((int)strlen(arithTrig)) && i < abs((int)strlen(arithTrig))) {
							timeF[t] = arithTrig[i];
							t++; i++;
						}
						timeF[t] = '\0';
						i++;
						int minutes = (int)calcNow(timeF, result1, result2);
						if (verified == 1) {
							sprintf(timeF, "");
							t = 0;
							while (arithTrig[i] != ')' && i < abs((int)strlen(arithTrig))) {
								timeF[t] = arithTrig[i];
								t++; i++;
							}
							timeF[t] = '\0';
							int seconds = (int)calcNow(timeF, result1, result2);
							if (verified == 1) {
								sprintf(timeF, "");
								clock_t start, end, syn1, syn2;
								int timePassed = 0, totalTime = hours * 3600 + minutes * 60 + seconds;
								int timeActual = 50, timepass = 0, time2syn = 0;
								start = clock();
								if (totalTime > 0) {
									while (timeActual > 0) {
										end = clock();
										timePassed = (end - start) / CLOCKS_PER_SEC;
										if (timePassed == 0) {
											syn1 = clock();
											while (timepass == timePassed) {
												end = clock();
												timePassed = (end - start) / CLOCKS_PER_SEC;
												Sleep(1);
											}
											syn2 = clock();
											time2syn = (int)(((T)(end - start) / CLOCKS_PER_SEC) * 1000);
										}
										else {
											Sleep(time2syn - 125);
											while (timepass == timePassed) {
												end = clock();
												timePassed = (end - start) / CLOCKS_PER_SEC;
												Sleep(3);
											}
										}
										timeActual = totalTime - timePassed;
										int thours = timeActual / 3600;
										int tminutes = (timeActual % 3600) / 60;
										int tseconds = (timeActual % 3600) % 60;
										timepass = timePassed;
										time_t hourF;
										time(&hourF);
										char* tim;
										tim = ctime(&hourF);
										tim[24] = '\0';
										int Hours = (tim[11] - '0') * 10 + (tim[12] - '0');
										int Minutes = (tim[14] - '0') * 10 + (tim[15] - '0');
										int Seconds = (tim[17] - '0') * 10 + (tim[18] - '0');
										char* toOpen = getDynamicCharArray("", "toOpen");
										sprintf(toOpen, "%s\\history.txt", atcPath);
										fout = fopen(toOpen, "a+");
										int years = (tim[20] - '0') * 1000 + (tim[21] - '0') * 100 + (tim[22] - '0') * 10 + (tim[23] - '0');
										int days = (tim[8] - '0') * 10 + (tim[9] - '0');
										int months = 0;
										if (tim[4] == 'J' && tim[5] == 'a' && tim[6] == 'n') {
											months = 1;
										}
										if (tim[4] == 'F' && tim[5] == 'e' && tim[6] == 'b') {
											months = 2;
										}
										if (tim[4] == 'M' && tim[5] == 'a' && tim[6] == 'r') {
											months = 3;
										}
										if (tim[4] == 'A' && tim[5] == 'p' && tim[6] == 'r') {
											months = 4;
										}
										if (tim[4] == 'M' && tim[5] == 'a' && tim[6] == 'y') {
											months = 5;
										}
										if (tim[4] == 'J' && tim[5] == 'u' && tim[6] == 'n') {
											months = 6;
										}
										if (tim[4] == 'J' && tim[5] == 'u' && tim[6] == 'l') {
											months = 7;
										}
										if (tim[4] == 'A' && tim[5] == 'u' && tim[6] == 'g') {
											months = 8;
										}
										if (tim[4] == 'S' && tim[5] == 'e' && tim[6] == 'p') {
											months = 9;
										}
										if (tim[4] == 'O' && tim[5] == 'c' && tim[6] == 't') {
											months = 10;
										}
										if (tim[4] == 'N' && tim[5] == 'o' && tim[6] == 'v') {
											months = 11;
										}
										if (tim[4] == 'D' && tim[5] == 'e' && tim[6] == 'c') {
											months = 12;
										}
										char* toTitle = getDynamicCharArray("", "toTitle");
										sprintf(toTitle, "title Advanced Trigonometry Calculator v2.1.7 (Mem Factor: %.3f)  ==) %04d/%02d/%02d %02d:%02d:%02d (==", memFactor, years, months, days, Hours, Minutes, Seconds);
										system(toTitle);
										printTimer(thours, tminutes, tseconds);
										_delete(toTitle, "toTitle");
										toTitle = nullptr;
										_delete(toOpen, "toOpen");
										toOpen = nullptr;
									}
								}
								i = 0;
								Sleep(400);
								while (i < 25) {
									Beep(777, 400);
									Sleep(400);
									i++;
								}
								puts("");
							}
						}
					}
				}
				else {
					printf("\n==> Your expression has syntax errors. <==\n\n");
				}
				_delete(timeF, "timeF");
				timeF = nullptr;

			}
			if (arG > 1) {
				exit(0);
			}
		}
		arithTrig[0] = '\0'; command = true;
		ShowConsoleCursor(TRUE);
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
		_delete(arithTrig, "arithTrig");
		arithTrig = nullptr;
		_delete(stringV, "stringV");
		stringV = nullptr;
		return command;
	}
	if (isCommand(arithTrig, "bigtimer") && arithTrig[i + 8] == '(' || isCommand(arithTrig, "runbigtimer") && arithTrig[i + 11] == '(') {

		if (isCommand(arithTrig, "runbigtimer")) {
			char* comm = getDynamicCharArray("", "comm");
			char* commandToExecute = getDynamicCharArray("", "commandToExecute");
			command = true;
			replace("run", "", arithTrig);
			sprintf(commandToExecute, "%s", expressionF);
			replace("+0", "", commandToExecute);
			sprintf(commandToExecute, "%s", expressionF);
			sprintf(comm, "/C \"MODE con cols=124 lines=28&\"%s\\atc.exe\" \"%s\"&exit\"", atcPath, commandToExecute);
			using namespace std;
			std::string s = string(comm);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
			puts("");
			_delete(comm, "comm");
			comm = nullptr;
			_delete(commandToExecute, "commandToExecute");
			commandToExecute = nullptr;
		}
		else {

			cls();
			ShowConsoleCursor(FALSE);
			if (arithTrig[i + 8] == '(') {
				i = i + 9;

			}
			int t = i, p = 0;
			for (t; t < abs((int)strlen(arithTrig)); t++) {
				if (arithTrig[t] == ')') {
					p++;
				}
			}
			if (p != 1) {
				printf("\n\n==> You need to terminate the expression with ')' character. <==\n\n");
			}
			else {
				char* tim;
				char* hou = getDynamicCharArray("", "hou");
				char* Min = getDynamicCharArray("", "Min");
				char* sec = getDynamicCharArray("", "sec");
				char* toOpen = getDynamicCharArray("", "toOpen");
				char* yea = getDynamicCharArray("", "yea");
				char* da = getDynamicCharArray("", "da");
				char* toTitle = getDynamicCharArray("", "toTitle");
				sprintf(toOpen, "%s\\history.txt", atcPath);
				char* text = getDynamicCharArray("", "text");
				char* display = getDynamicCharArray("", "display");
				char* tiIn = getDynamicCharArray("", "tiIn");

				char* timeF = getDynamicCharArray("", "timeF");
				t = 0;
				int b = i;
				while (arithTrig[b] != ')') {
					expression[t] = arithTrig[b];
					b++; t++;
				}
				expression[t] = '\0';
				b = 0;
				int sep = 0;
				for (t = 0; t < abs((int)strlen(expression)); t++) {
					if (expression[t] == ':' || expression[t] == '0' || expression[t] == '1' || expression[t] == '2' || expression[t] == '3' || expression[t] == '4' || expression[t] == '5' || expression[t] == '6' || expression[t] == '7' || expression[t] == '8' || expression[t] == '9') {
						b++;
						if (expression[t] == ':') {
							sep++;
						}
					}
				}
				if (b == abs((int)strlen(expression)) && sep == 2) {
					sprintf(timeF, "");
					t = 0;
					while (arithTrig[i] != ':' && arithTrig[i] != ')') {
						timeF[t] = arithTrig[i];
						t++; i++;
					}
					i++;
					timeF[t] = '\0';
					int hours = (int)calcNow(timeF, result1, result2);

					if (verified == 1) {

						t = 0;
						while (arithTrig[i] != ':' && arithTrig[i] != ')' && i < abs((int)strlen(arithTrig)) && i < abs((int)strlen(arithTrig))) {
							timeF[t] = arithTrig[i];
							t++; i++;
						}
						timeF[t] = '\0';
						i++;
						int thours = 0;
						int tminutes = 0;
						int tseconds = 0;
						int minutes = (int)calcNow(timeF, result1, result2);
						if (verified == 1) {
							sprintf(timeF, "");
							t = 0;
							while (arithTrig[i] != ')' && i < abs((int)strlen(arithTrig))) {
								timeF[t] = arithTrig[i];
								t++; i++;
							}
							timeF[t] = '\0';
							int seconds = (int)calcNow(timeF, result1, result2);
							if (verified == 1) {
								sprintf(timeF, "");
								clock_t start, end, syn1, syn2;
								int timePassed = 0, totalTime = hours * 3600 + minutes * 60 + seconds;
								int timeActual = 50, timepass = 0, time2syn = 0;

								start = clock();

								if (totalTime > 0) {
									while (timeActual > 0) {

										end = clock();
										timePassed = (end - start) / CLOCKS_PER_SEC;
										if (timePassed == 0) {
											syn1 = clock();
											while (timepass == timePassed) {
												end = clock();
												timePassed = (end - start) / CLOCKS_PER_SEC;
												Sleep(100);
											}
											syn2 = clock();
											time2syn = (int)(((T)(end - start) / CLOCKS_PER_SEC) * 1000);
										}
										else {
											Sleep(time2syn - 125);
											while (timepass == timePassed) {
												end = clock();
												timePassed = (end - start) / CLOCKS_PER_SEC;
												Sleep(100);
											}
										}
										sprintf(display, " ");
										sprintf(timeF, " ");
										sprintf(toTitle, " ");
										sprintf(tiIn, " ");
										timeActual = totalTime - timePassed;
										thours = timeActual / 3600;
										tminutes = (timeActual % 3600) / 60;
										tseconds = (timeActual % 3600) % 60;
										timepass = timePassed;
										time_t hourF;
										time(&hourF);
										tim = ctime(&hourF);
										tim[24] = '\0';
										hou[0] = tim[11]; hou[1] = tim[12]; hou[2] = '\0';
										int Hours = atoi(hou);
										Min[0] = tim[14]; Min[1] = tim[15]; Min[2] = '\0';

										int Minutes = atoi(Min);

										sec[0] = tim[17]; sec[1] = tim[18]; sec[2] = '\0';

										int Seconds = atoi(sec);
										fout = fopen(toOpen, "a+");
										yea[0] = tim[20]; yea[1] = tim[21]; yea[2] = tim[22]; yea[3] = tim[23]; yea[4] = '\0';
										int years = atoi(yea);
										da[0] = tim[8]; da[1] = tim[9]; da[2] = '\0';

										int days = atoi(da);
										int months = 0;
										if (tim[4] == 'J' && tim[5] == 'a' && tim[6] == 'n') {
											months = 1;
										}
										if (tim[4] == 'F' && tim[5] == 'e' && tim[6] == 'b') {
											months = 2;
										}
										if (tim[4] == 'M' && tim[5] == 'a' && tim[6] == 'r') {
											months = 3;
										}
										if (tim[4] == 'A' && tim[5] == 'p' && tim[6] == 'r') {
											months = 4;
										}
										if (tim[4] == 'M' && tim[5] == 'a' && tim[6] == 'y') {
											months = 5;
										}
										if (tim[4] == 'J' && tim[5] == 'u' && tim[6] == 'n') {
											months = 6;
										}
										if (tim[4] == 'J' && tim[5] == 'u' && tim[6] == 'l') {
											months = 7;
										}
										if (tim[4] == 'A' && tim[5] == 'u' && tim[6] == 'g') {
											months = 8;
										}
										if (tim[4] == 'S' && tim[5] == 'e' && tim[6] == 'p') {
											months = 9;
										}
										if (tim[4] == 'O' && tim[5] == 'c' && tim[6] == 't') {
											months = 10;
										}
										if (tim[4] == 'N' && tim[5] == 'o' && tim[6] == 'v') {
											months = 11;
										}
										if (tim[4] == 'D' && tim[5] == 'e' && tim[6] == 'c') {
											months = 12;
										}

										sprintf(toTitle, "title Advanced Trigonometry Calculator v2.1.7 (Mem Factor: %.3f)  ==) %04d/%02d/%02d %02d:%02d:%02d (==", memFactor, years, months, days, Hours, Minutes, Seconds);

										sprintf(tiIn, "%02d:%02d:%02d\n", thours, tminutes, tseconds);
										system(toTitle);
										GoToXY(0, 0);
										printBigTimer(thours, tminutes, tseconds, tiIn, text, display);

									}
								}


								i = 0;
								Sleep(400);
								while (i < 25) {
									Beep(777, 400);
									Sleep(400);
									i++;
								}
								puts("");
							}
						}

					}

				}
				else {
					printf("\n==> Your expression has syntax errors. <==\n\n");
				}

				if (toTitle != nullptr) {
					_delete(toTitle, "toTitle");
					toTitle = nullptr;

				}
				if (tiIn != nullptr) {

					_delete(tiIn, "tiIn"); tiIn = nullptr;
				}
				if (hou != nullptr) {

					_delete(hou, "hou");
					hou = nullptr;

				}
				if (Min != nullptr) {

					_delete(Min, "Min");
					Min = nullptr;

				}
				if (sec != nullptr) {

					_delete(sec, "sec");
					sec = nullptr;
				}

				if (yea != nullptr) {
					_delete(yea, "yea");
					yea = nullptr;
				}

				if (da != nullptr) {
					_delete(da, "da");
					da = nullptr;
				}

				if (toOpen != nullptr) {
					_delete(toOpen, "toOpen");
					toOpen = nullptr;
				}
				if (text != nullptr) {
					_delete(text, "text"); text = nullptr;
				}
				if (display != nullptr) {
					_delete(display, "display"); display = nullptr;
				}
				if (timeF != nullptr) {
					_delete(timeF, "display"); timeF = nullptr;
				}
			}


			if (arG > 1) {
				exit(0);
			}
		}

		arithTrig[0] = '\0'; command = true;
		ShowConsoleCursor(TRUE);
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
		_delete(arithTrig, "arithTrig");
		arithTrig = nullptr;
		_delete(stringV, "stringV");
		stringV = nullptr;
		return command;
	}
	if (isCommand(arithTrig, "clock") && arithTrig[i + 5] == '(' || isCommand(arithTrig, "runclock") && arithTrig[i + 8] == '(') {
		if (isCommand(arithTrig, "runclock")) {
			command = true;
			char* comm = getDynamicCharArray("", "comm");
			char* commandToExecute = getDynamicCharArray("", "commandToExecute");
			replace("run", "", arithTrig);
			sprintf(commandToExecute, "%s", expressionF);
			replace("+0", "", commandToExecute);
			sprintf(commandToExecute, "%s", expressionF);
			sprintf(comm, "/C \"MODE con cols=69 lines=15&\"%s\\atc.exe\" \"%s\"&exit\"", atcPath, commandToExecute);
			using namespace std;
			std::string s = string(comm);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
			puts("");
			_delete(comm, "comm");
			comm = nullptr;
			_delete(commandToExecute, "commandToExecute");
			commandToExecute = nullptr;
		}
		else {
			cls();
			ShowConsoleCursor(FALSE);
			if (arithTrig[i + 7] == '(') {
				i = i + 8;
			}
			else {
				if (arithTrig[i + 5] == '(') {
					i = i + 6;
				}
			}
			int t = i, p = 0;
			for (t; t < abs((int)strlen(arithTrig)); t++) {
				if (arithTrig[t] == ')') {
					p++;
				}
			}
			if (p != 1) {
				printf("\n\n==> You need to terminate the expression with ')' character. <==\n\n");
			}
			else {
				char* timE = getDynamicCharArray("", "timE");
				char* seco = getDynamicCharArray("", "seco");
				char* tim;
				t = 0;
				int b = i;
				while (arithTrig[b] != ')') {
					expression[t] = arithTrig[b];
					b++; t++;
				}
				expression[t] = '\0';
				b = 0;
				int sep = 0;
				for (t = 0; t < abs((int)strlen(expression)); t++) {
					if (expression[t] == ':' || expression[t] == '0' || expression[t] == '1' || expression[t] == '2' || expression[t] == '3' || expression[t] == '4' || expression[t] == '5' || expression[t] == '6' || expression[t] == '7' || expression[t] == '8' || expression[t] == '9') {
						b++;
						if (expression[t] == ':') {
							sep++;
						}
					}
				}
				if (b == abs((int)strlen(expression)) && sep == 2) {
					t = 0;
					sprintf(timE, "");
					while (arithTrig[i] != ':' && arithTrig[i] != ')') {
						timE[t] = arithTrig[i];
						t++; i++;
					}
					i++;
					timE[t] = '\0';
					int hours = (int)calcNow(timE, result1, result2);
					if (verified == 1) {
						sprintf(timE, "");
						t = 0;
						while (arithTrig[i] != ':' && arithTrig[i] != ')' && i < abs((int)strlen(arithTrig))) {
							timE[t] = arithTrig[i];
							t++; i++;
						}
						timE[t] = '\0';
						i++;
						int minutes = (int)calcNow(timE, result1, result2);
						if (verified == 1) {
							sprintf(timE, "");
							t = 0;
							while (arithTrig[i] != ')' && i < abs((int)strlen(arithTrig)) && i < abs((int)strlen(arithTrig))) {
								timE[t] = arithTrig[i];
								t++; i++;
							}
							timE[t] = '\0';
							int seconds = (int)calcNow(timE, result1, result2);
							if (verified == 1) {
								sprintf(timE, "");
								clock_t start, end, syn1, syn2;
								int timePassed = 0, totalTime = hours * 3600 + minutes * 60 + seconds;
								int timeActual = 50, timepass = 0, time2syn = 0;
								int sec = 0;

								time_t hour1;
								time(&hour1);
								tim = ctime(&hour1);
								tim[24] = '\0';
								seco[0] = tim[17]; seco[1] = tim[18]; seco[2] = '\0';
								sec = atoi(seco);
								wait(sec);
								start = clock();
								if (seco != nullptr) {
									_delete(seco, "seco");
									seco = nullptr;
								}
								if (totalTime > 0) {
									while (timeActual > 0) {
										end = clock();
										timePassed = (end - start) / CLOCKS_PER_SEC;
										if (timePassed == 0) {
											syn1 = clock();
											while (timepass == timePassed) {
												end = clock();
												timePassed = (end - start) / CLOCKS_PER_SEC;
												Sleep(1);
											}
											syn2 = clock();
											time2syn = (int)(((T)(end - start) / CLOCKS_PER_SEC) * 1000);
										}
										else {
											Sleep(time2syn - 125);
											while (timepass == timePassed) {
												end = clock();
												timePassed = (end - start) / CLOCKS_PER_SEC;
												Sleep(3);
											}
										}
										timeActual = totalTime - timePassed;
										int thours = timeActual / 3600;
										int tminutes = (timeActual % 3600) / 60;
										int tseconds = (timeActual % 3600) % 60;
										if (tseconds == -1) { tseconds = 0; }
										timepass = timePassed;
										time_t hour;
										time(&hour);
										tim = ctime(&hour);
										tim[24] = '\0';
										int Hours = (tim[11] - '0') * 10 + (tim[12] - '0');
										int Minutes = (tim[14] - '0') * 10 + (tim[15] - '0');
										int Seconds = (tim[17] - '0') * 10 + (tim[18] - '0');
										char* toOpen = getDynamicCharArray("  ", "toOpen");
										sprintf(toOpen, "%s\\history.txt", atcPath);
										fout = fopen(toOpen, "a+");
										int years = (tim[20] - '0') * 1000 + (tim[21] - '0') * 100 + (tim[22] - '0') * 10 + (tim[23] - '0');
										int days = (tim[8] - '0') * 10 + (tim[9] - '0');
										int months = 0;
										if (tim[4] == 'J' && tim[5] == 'a' && tim[6] == 'n') {
											months = 1;
										}
										if (tim[4] == 'F' && tim[5] == 'e' && tim[6] == 'b') {
											months = 2;
										}
										if (tim[4] == 'M' && tim[5] == 'a' && tim[6] == 'r') {
											months = 3;
										}
										if (tim[4] == 'A' && tim[5] == 'p' && tim[6] == 'r') {
											months = 4;
										}
										if (tim[4] == 'M' && tim[5] == 'a' && tim[6] == 'y') {
											months = 5;
										}
										if (tim[4] == 'J' && tim[5] == 'u' && tim[6] == 'n') {
											months = 6;
										}
										if (tim[4] == 'J' && tim[5] == 'u' && tim[6] == 'l') {
											months = 7;
										}
										if (tim[4] == 'A' && tim[5] == 'u' && tim[6] == 'g') {
											months = 8;
										}
										if (tim[4] == 'S' && tim[5] == 'e' && tim[6] == 'p') {
											months = 9;
										}
										if (tim[4] == 'O' && tim[5] == 'c' && tim[6] == 't') {
											months = 10;
										}
										if (tim[4] == 'N' && tim[5] == 'o' && tim[6] == 'v') {
											months = 11;
										}
										if (tim[4] == 'D' && tim[5] == 'e' && tim[6] == 'c') {
											months = 12;
										}
										char* toTitle = getDynamicCharArray("", "toTitle");
										sprintf(toTitle, "title Advanced Trigonometry Calculator v2.1.7 (Mem Factor: %.3f)  ==) %04d/%02d/%02d %02d:%02d:%02d (==", memFactor,years, months, days, Hours, Minutes, Seconds);
										system(toTitle);
										printTimer(Hours, Minutes, Seconds);
										printf("\n  %02d:%02d:%02d                   \n", thours, tminutes, tseconds);
										_delete(toTitle, "toTitle");
										toTitle = nullptr;

										_delete(toOpen, "toOpen");
									}
								}

							}
						}
					}
					puts("");
				}
				else {
					printf("\n==> Your expression has syntax errors. <==\n\n");
				}
				_delete(timE, "timE");
				timE = nullptr;

			}
			if (arG > 1) {
				exit(0);
			}
		}
		arithTrig[0] = '\0'; command = true;
		ShowConsoleCursor(TRUE);
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
		_delete(arithTrig, "arithTrig");
		arithTrig = nullptr;
		_delete(stringV, "stringV");
		stringV = nullptr;
		return command;
	}
	if (isCommand(arithTrig, "bigclock") && arithTrig[i + 8] == '(' || isCommand(arithTrig, "runbigclock") && arithTrig[i + 11] == '(') {

		if (isCommand(arithTrig, "runbigclock")) {
			command = true;
			char* comm = getDynamicCharArray("", "comm");
			char* commandToExecute = getDynamicCharArray("", "commandToExecute");
			replace("run", "", arithTrig);
			sprintf(commandToExecute, "%s", expressionF);
			replace("+0", "", commandToExecute);
			sprintf(commandToExecute, "%s", expressionF);
			sprintf(comm, "/C \"MODE con cols=124 lines=32&\"%s\\atc.exe\" \"%s\"&exit\"", atcPath, commandToExecute);
			using namespace std;
			std::string s = string(comm);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
			puts("");
			_delete(comm, "comm");
			comm = nullptr;
			_delete(commandToExecute, "commandToExecute");
			commandToExecute = nullptr;
		}
		else {
			cls();
			ShowConsoleCursor(FALSE);
			if (arithTrig[i + 8] == '(') {
				i = i + 9;
			}
			else {
				if (arithTrig[i + 11] == '(') {
					i = i + 12;
				}
			}
			int t = i, p = 0;
			for (t; t < abs((int)strlen(arithTrig)); t++) {
				if (arithTrig[t] == ')') {
					p++;
				}
			}
			if (p != 1) {
				printf("\n\n==> You need to terminate the expression with ')' character. <==\n\n");
			}
			else {


				t = 0;
				int b = i;
				while (arithTrig[b] != ')') {
					expression[t] = arithTrig[b];
					b++; t++;
				}
				expression[t] = '\0';
				b = 0;
				int sep = 0;
				for (t = 0; t < abs((int)strlen(expression)); t++) {
					if (expression[t] == ':' || expression[t] == '0' || expression[t] == '1' || expression[t] == '2' || expression[t] == '3' || expression[t] == '4' || expression[t] == '5' || expression[t] == '6' || expression[t] == '7' || expression[t] == '8' || expression[t] == '9') {
						b++;
						if (expression[t] == ':') {
							sep++;
						}
					}
				}
				if (b == abs((int)strlen(expression)) && sep == 2) {
					char* timE = getDynamicCharArray("", "timE");

					t = 0;
					sprintf(timE, "");
					while (arithTrig[i] != ':' && arithTrig[i] != ')') {
						timE[t] = arithTrig[i];
						t++; i++;
					}
					i++;
					timE[t] = '\0';
					int hours = (int)calcNow(timE, result1, result2);
					if (verified == 1) {
						sprintf(timE, "");
						t = 0;
						while (arithTrig[i] != ':' && arithTrig[i] != ')' && i < abs((int)strlen(arithTrig))) {
							timE[t] = arithTrig[i];
							t++; i++;
						}
						timE[t] = '\0';
						i++;
						int minutes = (int)calcNow(timE, result1, result2);

						if (verified == 1) {
							sprintf(timE, "");
							t = 0;
							while (arithTrig[i] != ')' && i < abs((int)strlen(arithTrig)) && i < abs((int)strlen(arithTrig))) {
								timE[t] = arithTrig[i];
								t++; i++;
							}
							timE[t] = '\0';
							int seconds = (int)calcNow(timE, result1, result2);
							if (verified == 1) {
								sprintf(timE, "");
								clock_t start, end, syn1, syn2;
								int timePassed = 0, totalTime = hours * 3600 + minutes * 60 + seconds;
								int timeActual = 50, timepass = 0, time2syn = 0;
								int sec = 0;

								time_t hour1;
								time(&hour1);
								char* tim;
								tim = ctime(&hour1);
								tim[24] = '\0';
								char* seco = getDynamicCharArray("", "seco");
								seco[0] = tim[17]; seco[1] = tim[18]; seco[2] = '\0';
								sec = atoi(seco);
								wait(sec);
								start = clock();
								if (totalTime > 0) {

									char* tiIn = getDynamicCharArray("", "tiIn");
									char* text = getDynamicCharArray("", "text");
									char* display = getDynamicCharArray("", "display");
									char* hou = getDynamicCharArray("", "hou");

									char* Min = getDynamicCharArray("", "Min");

									char* toOpen = getDynamicCharArray("", "toOpen");
									sprintf(toOpen, "%s\\history.txt", atcPath);
									fout = fopen(toOpen, "a+");
									char* yea = getDynamicCharArray("", "yea");
									char* da = getDynamicCharArray("", "da");
									char* toTitle = getDynamicCharArray("", "toTitle");
									while (timeActual > 0) {
										end = clock();
										timePassed = (end - start) / CLOCKS_PER_SEC;
										if (timePassed == 0) {
											syn1 = clock();
											while (timepass == timePassed) {
												end = clock();
												timePassed = (end - start) / CLOCKS_PER_SEC;
												Sleep(1);
											}
											syn2 = clock();
											time2syn = (int)(((T)(end - start) / CLOCKS_PER_SEC) * 1000);
										}
										else {
											Sleep(time2syn - 125);
											while (timepass == timePassed) {
												end = clock();
												timePassed = (end - start) / CLOCKS_PER_SEC;
												Sleep(3);
											}
										}

										timeActual = totalTime - timePassed;
										int thours = timeActual / 3600;
										int tminutes = (timeActual % 3600) / 60;
										int tseconds = (timeActual % 3600) % 60;
										if (tseconds == -1) { tseconds = 0; }
										timepass = timePassed;
										time_t hour;
										time(&hour);
										tim = ctime(&hour);
										tim[24] = '\0';
										sprintf(hou, "%c%c%c", tim[11], tim[12], '\0');
										int Hours = atoi(hou);
										sprintf(Min, "%c%c%c", tim[14], tim[15], '\0');
										int Minutes = atoi(Min);
										sprintf(seco, "%c%c%c", tim[17], tim[18], '\0');
										int Seconds = atoi(seco);
										sprintf(toOpen, "%s\\history.txt", atcPath);
										fout = fopen(toOpen, "a+");
										sprintf(yea, "%c%c%c%c%c", tim[20], tim[21], tim[22], tim[23], '\0');
										int years = atoi(yea);
										sprintf(da, "%c%c%c", tim[8], tim[9], '\0');
										int days = atoi(da);
										int months = 0;
										if (tim[4] == 'J' && tim[5] == 'a' && tim[6] == 'n') {
											months = 1;
										}
										if (tim[4] == 'F' && tim[5] == 'e' && tim[6] == 'b') {
											months = 2;
										}
										if (tim[4] == 'M' && tim[5] == 'a' && tim[6] == 'r') {
											months = 3;
										}
										if (tim[4] == 'A' && tim[5] == 'p' && tim[6] == 'r') {
											months = 4;
										}
										if (tim[4] == 'M' && tim[5] == 'a' && tim[6] == 'y') {
											months = 5;
										}
										if (tim[4] == 'J' && tim[5] == 'u' && tim[6] == 'n') {
											months = 6;
										}
										if (tim[4] == 'J' && tim[5] == 'u' && tim[6] == 'l') {
											months = 7;
										}
										if (tim[4] == 'A' && tim[5] == 'u' && tim[6] == 'g') {
											months = 8;
										}
										if (tim[4] == 'S' && tim[5] == 'e' && tim[6] == 'p') {
											months = 9;
										}
										if (tim[4] == 'O' && tim[5] == 'c' && tim[6] == 't') {
											months = 10;
										}
										if (tim[4] == 'N' && tim[5] == 'o' && tim[6] == 'v') {
											months = 11;
										}
										if (tim[4] == 'D' && tim[5] == 'e' && tim[6] == 'c') {
											months = 12;
										}
										sprintf(toTitle, "title Advanced Trigonometry Calculator v2.1.7 (Mem Factor: %.3f)  ==) %04d/%02d/%02d %02d:%02d:%02d (==", memFactor, years, months, days, Hours, Minutes, Seconds);
										system(toTitle);
										GoToXY(0, 0);
										sprintf(tiIn, "%02d:%02d:%02d\n", Hours, Minutes, Seconds);
										printBigTimer(thours, tminutes, tseconds, tiIn, text, display);
										printf("\n\n    %02d:%02d:%02d                   \n\n", thours, tminutes, tseconds);

									}
									if (display != nullptr) {
										_delete(display, "display"); display = nullptr;
									}

									if (toTitle != nullptr) {
										_delete(toTitle, "toTitle");
										toTitle = nullptr;
									}
									if (hou != nullptr) {

										_delete(hou, "hou");
										hou = nullptr;
									}
									if (Min != nullptr) {

										_delete(Min, "Min");
										Min = nullptr;
									}

									if (yea != nullptr) {
										_delete(yea, "yea");
										yea = nullptr;
									}
									if (da != nullptr) {
										_delete(da, "da");
										da = nullptr;
									}
									if (toOpen != nullptr) {

										_delete(toOpen, "toOpen");
										toOpen = nullptr;
									}
									if (seco != nullptr) {
										_delete(seco, "seco");
										seco = nullptr;
									}
									if (tiIn != nullptr) {

										_delete(tiIn, "tiIn"); tiIn = nullptr;
									}
									if (text != nullptr) {

										_delete(text, "text"); text = nullptr;
									}
								}

							}
							if (timE != nullptr) {
								_delete(timE, "timE");
								timE = nullptr;
							}
						}

					}

				}
				else {
					printf("\n==> Your expression has syntax errors. <==\n\n");
				}

			}

			if (arG > 1) {
				exit(0);
			}
		}
		arithTrig[0] = '\0'; command = true;
		ShowConsoleCursor(TRUE);
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
		_delete(arithTrig, "arithTrig");
		arithTrig = nullptr;
		_delete(stringV, "stringV");
		stringV = nullptr;
		return command;
	}
	if (isCommand(arithTrig, "verboseresolution")) {
		int requestedState = -1;
		if (arithTrig[17] == '(' && (arithTrig[18] == '0' || arithTrig[18] == '1')) {
			requestedState = arithTrig[18] - '0';
		}
		arithTrig[0] = '\0'; command = true;
		printf("\n==> Configuration of verbose resolution <==\n\n");
		fprintf(fout, "\n==> Configuration of verbose resolution <==\n\n");
		verboseResolutionController<T>(requestedState);
		fprintf(fout, "\n");
		printf("\n");
	}
	if (isCommand(arithTrig, "siprefixes")) {
		arithTrig[0] = '\0'; command = true;
		printf("\n==> Configuration of SI prefixes response <==\n\n");
		fprintf(fout, "\n==> Configuration of SI prefixes response <==\n\n");
		siPrefixController();
		fprintf(fout, "\n");
		printf("\n");
	}
	if (isCommand(arithTrig, "time")) {
		arithTrig[0] = '\0'; command = true;
		puts("");
		Clock(1);
		puts("");
	}
	if (isCommand(arithTrig, "actualtimeresponse")) {
		arithTrig[0] = '\0'; command = true;
		printf("\n==> Configuration of actual time response <==\n\n");
		fprintf(fout, "\n==> Configuration of actual time response <==\n\n");
		actualTimeController();
		fprintf(fout, "\n");
		printf("\n");
	}
	if (isCommand(arithTrig, "timedifferencecalculations")) {
		arithTrig[0] = '\0'; command = true;
		timeDifferenceCalculations();
		fprintf(fout, "\n");
		printf("\n");
	}
	if (isCommand(arithTrig, "dayofweek") && arithTrig[i + 9] == '(') {
		command = true;
		char* Day = getDynamicCharArray("", "Day"); char* Month = getDynamicCharArray("", "Month"); char* Year = getDynamicCharArray("", "Year");
		T plusYears = 0;
		int r = 0;
		T day = 0, day1 = 0, day1S = 0, month = 0, month1 = 0, month1S = 0, year = 0, year1 = 0, year1S = 0, dayS = 0, monthS = 0, yearS = 0;
		if (arithTrig[i + 9] == '(' || arithTrig[i + 9] == '{') {
			i = i + 10;
		}
		if (arithTrig[i + 11] == '(' || arithTrig[i + 11] == '{') {
			i = i + 12;
		}
		int p = 0, countR = 0, countL = 0;
		for (p = i; p < abs((int)strlen(arithTrig)); p++) {
			if (arithTrig[p] == '(' || arithTrig[p] == '{') {
				countL++;
			}
			if (arithTrig[p] == ')' || arithTrig[p] == '}') {
				countR++;
			}
		}
		int limit = p - 3;
		countR--;
		while (arithTrig[i] != ')' && i < abs((int)strlen(arithTrig)) || countR > 0) {
			if (arithTrig[i] == 'd' && day == 0) {
				r = 0;
				i++;
				while (arithTrig[i] != 'y' && arithTrig[i] != 'm' && arithTrig[i] != 'a' && i < limit && i < abs((int)strlen(arithTrig)) && arithTrig[i] != '-') {
					if (arithTrig[i] == '(' || arithTrig[i] == '{') {
						countL--;
					}
					if (arithTrig[i] == ')' || arithTrig[i] == '}') {
						countR--;
					}
					Day[r] = arithTrig[i];
					r++; i++;
				}
				if (arithTrig[i] == '-') {
					Day[r] = '+'; Day[r + 1] = '0'; Day[r + 2] = '\0';
					day = calcNow(Day, result1, result2);
					if (verified == 1) {
						dayS = day;
						r = 0;
						i++;
						char* Day = getDynamicCharArray("", "Day");
						while (arithTrig[i] != 'y' && arithTrig[i] != 'm' && arithTrig[i] != 'a' && i < limit && i < abs((int)strlen(arithTrig))) {
							Day[r] = arithTrig[i];
							r++; i++;
						}
						Day[r] = '+'; Day[r + 1] = '0'; Day[r + 2] = '\0';
						day1 = calcNow(Day, result1, result2);
						if (verified == 1) {
							day1S = day1;
						}
						_delete(Day, "Day");
						Day = nullptr;
					}
				}
				else {
					Day[r] = '+'; Day[r + 1] = '0'; Day[r + 2] = '\0';
					day = calcNow(Day, result1, result2);
				}
			}
			if (arithTrig[i] == 'm' && month == 0) {
				r = 0;
				i++;
				while (arithTrig[i] != 'y' && arithTrig[i] != 'd' && arithTrig[i] != 'a' && i < limit && i < abs((int)strlen(arithTrig)) && arithTrig[i] != '-') {
					if (arithTrig[i] == '(' || arithTrig[i] == '{') {
						countL--;
					}
					if (arithTrig[i] == ')' || arithTrig[i] == '}') {
						countR--;
					}
					Month[r] = arithTrig[i];
					r++; i++;
				}
				if (arithTrig[i] == '-') {
					Month[r] = '+'; Month[r + 1] = '0'; Month[r + 2] = '\0';
					month = calcNow(Month, result1, result2);
					if (verified == 1) {
						monthS = month;
						r = 0;
						i++;
						char* Month = getDynamicCharArray("", "Month");
						while (arithTrig[i] != 'y' && arithTrig[i] != 'd' && arithTrig[i] != 'a' && i < limit && i < abs((int)strlen(arithTrig))) {
							Month[r] = arithTrig[i];
							r++; i++;
						}
						Month[r] = '+'; Month[r + 1] = '0'; Month[r + 2] = '\0';
						month1 = calcNow(Month, result1, result2);
						if (verified == 1) {
							month1S = month1;
						}
						_delete(Month, "Month");
						Month = nullptr;
					}
				}
				else {
					Month[r] = '+'; Month[r + 1] = '0'; Month[r + 2] = '\0';
					month = calcNow(Month, result1, result2);
				}
			}
			if ((arithTrig[i] == 'y' || arithTrig[i] == 'a') && year == 0) {
				r = 0;
				i++;
				while (arithTrig[i] != 'm' && arithTrig[i] != 'd' && i < limit && i < abs((int)strlen(arithTrig)) && arithTrig[i] != '-') {
					if (arithTrig[i] == '(' || arithTrig[i] == '{') {
						countL--;
					}
					if (arithTrig[i] == ')' || arithTrig[i] == '}') {
						countR--;
					}
					Year[r] = arithTrig[i];
					r++; i++;
				}
				if (arithTrig[i] == '-') {
					Year[r] = '+'; Year[r + 1] = '0'; Year[r + 2] = '\0';
					year = calcNow(Year, result1, result2);
					if (verified == 1) {
						yearS = year;
						r = 0;
						i++;
						char* Year = getDynamicCharArray("", "Year");
						while (arithTrig[i] != 'm' && arithTrig[i] != 'd' && i < limit && i < abs((int)strlen(arithTrig))) {
							Year[r] = arithTrig[i];
							r++; i++;
						}
						Year[r] = '+'; Year[r + 1] = '0'; Year[r + 2] = '\0';
						year1 = calcNow(Year, result1, result2);
						if (verified == 1) {
							year1S = year1;
						}
						_delete(Year, "Year");
						Year = nullptr;
					}
				}
				else {
					Year[r] = '+'; Year[r + 1] = '0'; Year[r + 2] = '\0';
					year = calcNow(Year, result1, result2);
				}
			}
			if (arithTrig[i] != 'd' && arithTrig[i] != 'm' && arithTrig[i] != 'y' && arithTrig[i] != 'a') {
				i++;
			}
		}
		if (verified == 1) {
			if (day1 == 0) {
				if (month > 12) {
					plusYears = qu<T>(month, 12);
					year = year + plusYears;
					month = qu<T>(re<T>(month, 12), 1);
				}
				if (month == 0) {
					month = 12;
					year--;
				}
				while (day > 29 && (qu<T>(re<T>(year, 4), 1) == 0 && (qu<T>(re<T>(year, 100), 1) != 0) || qu<T>(re<T>(year, 400), 1) == 0) && month == 2 || day > 28 && month == 2 && (qu<T>(re<T>(year, 4), 1) != 0 || qu<T>(re<T>(year, 100), 1) == 0 && qu<T>(re<T>(year, 400), 1) != 0) || (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31 || day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {
					if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
						day = day - 31;
					}
					else {
						if (month == 2) {
							if ((qu<T>(re<T>(year, 4), 1) == 0 && qu<T>(re<T>(year, 100), 1) != 0) || qu<T>(re<T>(year, 400), 1) == 0) {
								day = day - 29;
							}
							else {
								day = day - 28;
							}
						}
						else {
							day = day - 30;
						}
					}
					month++;
					if (month > 12) {
						year++;
						month = qu<T>(re<T>(month, 12), 1);
					}
				}
			}
			else {
				while (day1 > 29 && (qu<T>(re<T>(year, 4), 1) == 0 && (qu<T>(re<T>(year, 100), 1) != 0) || qu<T>(re<T>(year, 400), 1) == 0) && month == 2 || day1 > 28 && month == 2 && (qu<T>(re<T>(year, 4), 1) != 0 || qu<T>(re<T>(year, 100), 1) == 0 && qu<T>(re<T>(year, 400), 1) != 0) || (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day1 > 31 || day1 > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {
					if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day1 > 31) {
						day1 = day1 - 31;
					}
					else {
						if (month == 2) {
							if (qu<T>(re<T>(year, 4), 1) == 0) {
								if (qu<T>(re<T>(year, 400), 1) == 0 && day1 > 29) {
									day1 = day1 - 29;
								}
								else {
									if (qu<T>(re<T>(year, 100), 1) == 0 && day1 > 28) {
										day1 = day1 - 28;
									}
									else {
										if (day1 > 29) {
											day1 = day1 - 29;
										}
									}
								}
							}
							else {
								if (day1 > 28) {
									day1 = day1 - 28;
								}
							}
						}
						else {
							if (day1 > 30) {
								day1 = day1 - 30;
							}
						}
					}
					month--;
					if (month == 0) {
						year--;
						month = 12;
					}
				}
				day = day - day1;
				if (day < 0) {
					month--;
					int sumDay = 0;
					if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day1 > 31) {
						sumDay = 31;
					}
					else {
						if (month == 2) {
							if (qu<T>(re<T>(year, 4), 1) == 0) {
								if (qu<T>(re<T>(year, 400), 1) == 0) {
									sumDay = 29;
								}
								else {
									if (qu<T>(re<T>(year, 100), 1) == 0) {
										sumDay = 28;
									}
									else {
										sumDay = 29;
									}
								}
							}
							else {
								sumDay = 28;
							}
						}
						else {
							sumDay = 30;
						}
					}
					day = sumDay + day;
				}
				year = year - year1;
				month = month - month1;
				if (month > 12) {
					plusYears = qu<T>(month, 12);
					year = year + plusYears;
					month = qu<T>(re<T>(month, 12), 1);
					if (month == 0) {
						month = 12;
					}
				}
				else {
					if (month <= 0) {
						plusYears = qu<T>((month - 12), 12);
						year = year + plusYears;
						month = 12 - abs(qu<T>(re<T>(month, 12), 1));
						if (month == 0) {
							month = 12;
							year++;
						}
					}
				}
				day = day - datePreciser<T>(day + day1S, month + month1S, year + year1S, dayS, monthS, yearS);
			}
			char* tim = getDynamicCharArray("", "tim");
			sprintf(tim, "%s", convert2Exponential(day));
			int daY = (int)calcNow(tim, result1, result2);
			if (verified == 1) {
				sprintf(tim, "%s", convert2Exponential(month));
				int montH = (int)calcNow(tim, result1, result2);
				if (verified == 1) {
					sprintf(tim, "%s", convert2Exponential(year));
					int yeaR = (int)calcNow(tim, result1, result2);
					if (verified == 1) {
						if (daY < 1 || daY>31) {
							printf("\nError entering the day.\n ==> In a month, the days only vary between 1 and 31.\n\n");
							fprintf(fout, "\nError entering the day.\n ==> In a month, the days only vary between 1 and 31.\n\n");
						}
						else {
							if (montH < 1 || montH>12) {
								printf("\nError entering the month.\n ==> In a year, the months only vary between 1 and 12.\n\n");
								fprintf(fout, "\nError entering the month.\n == > In a year, the months only vary between 1 and 12.\n\n");
							}
							else {
								if (yeaR < 1760) {
									printf("\nError entering the year.\n ==> The minimal year to evaluate is 1760.\n\n");
									fprintf(fout, "\nError entering the year.\n ==> The minimal year to evaluate is 1760.\n\n");
								}
								else {
									if ((montH == 2 || montH == 4 || montH == 6 || montH == 9 || montH == 11) && daY == 31) {
										printf("\nError entering the month.\n ==> The entered month doesn't have the duration of 31 days.\n\n");
										fprintf(fout, "\nError entering the month.\n == > The entered month doesn't have the duration of 31 days.\n\n");
									}
									else {
										if (montH == 2 && daY > 29) {
											printf("\nError entering the day.\n ==> The month of February has a maximal duration of 29 days.\n\n");
											fprintf(fout, "\nError entering the day.\n ==> The month of February has a maximal duration of 29 days.\n\n");
										}
										else {
											if ((montH == 2 && daY == 29) && (yeaR % 4 != 0 && yeaR % 400 != 0)) {
												printf("\nError entering the day.\n ==> The month of February in %d has a maximal duration of 28 days.\n\n", yeaR);
												fprintf(fout, "\nError entering the day.\n ==> The month of February in %d has a maximal duration of 28 days.\n\n", yeaR);
											}
											else {
												printf("y%dm%dd%d=", yeaR, montH, daY);
												int h = 0;
												h = ((int)(daY + floor((((montH + 1) * 26) / 10) * 1.000) + yeaR + floor((yeaR / 4) * 1.0000) + 6 * floor((yeaR / 100) * 1.0000) + floor((yeaR / 400) * 1.0000)) % 7);
												if (montH < 3) {
													if (montH == 1) {
														montH = 13;
													}
													if (montH == 2) {
														montH = 14;
													}
													yeaR--;
													h = ((int)(daY + floor((((montH + 1) * 26) / 10) * 1.000) + (yeaR)+floor(((yeaR) / 4) * 1.0000) + 6 * floor(((yeaR) / 100) * 1.0000) + floor(((yeaR) / 400) * 1.0000)) % 7);

												}
												if (h == 1) {
													printf("Sunday\n\n");
													fprintf(fout, "Sunday\n\n");
												}
												if (h == 2) {
													printf("Monday\n\n");
													fprintf(fout, "Monday\n\n");
												}
												if (h == 3) {
													printf("Tuesday\n\n");
													fprintf(fout, "Tuesday\n\n");
												}
												if (h == 4) {
													printf("Wednesday\n\n");
													fprintf(fout, "Wednesday\n\n");
												}
												if (h == 5) {
													printf("Thursday\n\n");
													fprintf(fout, "Thursday\n\n");
												}
												if (h == 6) {
													printf("Friday\n\n");
													fprintf(fout, "Friday\n\n");
												}
												if (h == 0) {
													printf("Saturday\n\n");
													fprintf(fout, "Saturday\n\n");
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		_delete(Day, "Day");
		Day = nullptr;
		_delete(Month, "Month");
		Month = nullptr;
	}
	if (isCommand(arithTrig, "predefinetxt")) {
		arithTrig[0] = '\0'; command = true;
		printf("\n==> Drag to here the file to predefine and press the button \"Enter\" <==\n");
		fprintf(fout, "\n==> Drag to here the file to predefine and press the button \"Enter\" <==\n");
		char* predTxt = getDynamicCharArray("", "predTxt");
		int y = 0;
		gets_s(predTxt, DIM);
		if (predTxt[y] == '"') {
			while (predTxt[y + 1] != '"' && predTxt[y + 1] != '\0') {
				predTxt[y] = predTxt[y + 1];
				y++;
			}
			predTxt[y] = '\0';
		}
		FILE* pred = NULL;
		char* toOpen = getDynamicCharArray("", "toOpen");
		sprintf(toOpen, "%s\\predefinedTxt.txt", atcPath);
		while (pred == NULL) {
			pred = fopen(toOpen, "w");
		}
		fprintf(pred, "%s", predTxt);
		fclose(pred);
		printf("\n");
		fprintf(fout, "\n");
		_delete(predTxt, "predTxt");
		predTxt = nullptr;
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
	}
	if (isCommand(arithTrig, "solvetxt") && (arithTrig[i + 10] == '\0' || arithTrig[i + 8] == '(')) {
		command = true;
		FILE* readPred = NULL;
		char* readPath = getDynamicCharArray("", "readPath");
		if (arithTrig[i + 8] != '(' && arithTrig[i + 11] != '(') {
			char* toOpen = getDynamicCharArray("", "toOpen");
			sprintf(toOpen, "%s\\predefinedTxt.txt", atcPath);
			readPred = fopen(toOpen, "r");
			if (readPred == NULL) {
				printf("\n==> The file was not yet predefined! <==\n\n");
				fprintf(fout, "\n==> The file was not yet predefined! <==\n\n");
			}
			else {
				fgets(readPath, DIM, readPred);
				fclose(readPred);
				processTxt<T>(readPath, rf);
				FILE* open = NULL;
				open = fopen(expressionF, "r");
				char* openFile = getDynamicCharArray("", "openFile");
				if (open != NULL) {
					fclose(open);
					printf("\n==> Close the file with the answers to continue. <==\n\n");
					fprintf(fout, "\n==> Close the file with the answers to continue. <==\n\n");
				}
				openTxt();
				_delete(openFile, "openFile");
				openFile = nullptr;
			}
			_delete(toOpen, "toOpen");
			toOpen = nullptr;
		}
		else {
			char* paName = getDynamicCharArray("", "paName");
			int x = 0, y = 0;
			if (arithTrig[i + 8] == '(' || arithTrig[i + 11] == '(') {
				if (arithTrig[i + 8] == '(') {
					y = i + 9;
				}
				if (arithTrig[i + 11] == '(') {
					y = i + 12;
				}
				for (x = 0; arithTrig[y] != ')' && y < abs((int)strlen(arithTrig)) && arithTrig[y] != '+'; x++) {
					paName[x] = arithTrig[y];
					y++;
				}
				paName[x] = '\0';
				pathNameToPath(paName);
				if (abs((int)strlen(pathNAme)) != 0) {
					processTxt<T>(pathNAme, rf);
					FILE* open = NULL;
					open = fopen(expressionF, "r");
					char* openFile = getDynamicCharArray("", "openFile");
					if (open != NULL) {
						fclose(open);
						printf("\n==> Close the file with the answers to continue. <==\n\n");
						fprintf(fout, "\n==> Close the file with the answers to continue. <==\n\n");
					}
					openTxt();
					_delete(openFile, "openFile");
					openFile = nullptr;
				}
			}
			_delete(paName, "paName");
			paName = nullptr;
		}
		_delete(readPath, "readPath");
		readPath = nullptr;
	}
	if (isCommand(arithTrig, "calendar") && (arithTrig[i + 8] == '(' || arithTrig[i + 8] == '+')) {
		command = true;
		char* ye = getDynamicCharArrayLong(""); char* calendar = getDynamicCharArrayLong(""); char* lineWeekDays = getDynamicCharArray("", "lineWeekDays");
		char* month = getDynamicCharArray("", "month");

		char* day = getDynamicCharArray("", "day");
		int k = 0;
		int p = 0, countR = 0, countL = 0, currentYear = 0;
		for (p = 0; p < abs((int)strlen(arithTrig)); p++) {
			if (arithTrig[p] == '(' || arithTrig[p] == '{') {
				countL++;
			}
			if (arithTrig[p] == ')' || arithTrig[p] == '}') {
				countR++;
			}
		}
		if (countR == countL) {
			if (arithTrig[i + 8] == '(' || arithTrig[i + 8] == '{') {
				i = i + 9;
				for (p = i; p < abs((int)strlen(arithTrig)); p++);
				int limit = p - 3;
				if (arithTrig[limit] != ')') {
					limit++;
				}
				k = 0;
				countR = 0; countL = 0;
				while (i < limit) {
					if (arithTrig[i] == '(' || arithTrig[i] == '{') {
						countL++;
					}
					if (arithTrig[i] == ')' || arithTrig[i] == '}') {
						countR++;
					}
					ye[k] = arithTrig[i];
					k++; i++;
				}
				ye[k] = '\0';
				if (countR == countL) {
					year = (int)calcNow(ye, result1, result2);
				}
			}
			else {
				if (arithTrig[i + 10] == '(' || arithTrig[i + 10] == '{') {
					i = i + 11;
					for (p = i; p < abs((int)strlen(arithTrig)); p++);

					int limit = p - 3;
					if (arithTrig[limit] != ')') {
						limit++;
					}
					k = 0;
					countR = 0; countL = 0;
					while (i < limit) {
						if (arithTrig[i] == '(' || arithTrig[i] == '{') {
							countL++;
						}
						if (arithTrig[i] == ')' || arithTrig[i] == '}') {
							countR++;
						}
						ye[k] = arithTrig[i];
						k++; i++;
					}
					ye[k] = '\0';
					if (countR == countL) {
						year = (int)calcNow(ye, result1, result2);
					}
				}
				else {
					currentYear = 1;
					time_t hour;
					time(&hour);
					char* tim;
					tim = ctime(&hour);
					tim[24] = '\0';
					year = (tim[20] - '0') * 1000 + (tim[21] - '0') * 100 + (tim[22] - '0') * 10 + (tim[23] - '0');
					int days = (tim[8] - '0') * 10 + (tim[9] - '0');
					sprintf(day, "%d", days);
					if (tim[4] == 'J' && tim[5] == 'a' && tim[6] == 'n') {
						sprintf(month, "January");
					}
					if (tim[4] == 'F' && tim[5] == 'e' && tim[6] == 'b') {
						sprintf(month, "February");
					}
					if (tim[4] == 'M' && tim[5] == 'a' && tim[6] == 'r') {
						sprintf(month, "March");
					}
					if (tim[4] == 'A' && tim[5] == 'p' && tim[6] == 'r') {
						sprintf(month, "April");
					}
					if (tim[4] == 'M' && tim[5] == 'a' && tim[6] == 'y') {
						sprintf(month, "May");
					}
					if (tim[4] == 'J' && tim[5] == 'u' && tim[6] == 'n') {
						sprintf(month, "June");
					}
					if (tim[4] == 'J' && tim[5] == 'u' && tim[6] == 'l') {
						sprintf(month, "July");
					}
					if (tim[4] == 'A' && tim[5] == 'u' && tim[6] == 'g') {
						sprintf(month, "August");
					}
					if (tim[4] == 'S' && tim[5] == 'e' && tim[6] == 'p') {
						sprintf(month, "September");
					}
					if (tim[4] == 'O' && tim[5] == 'c' && tim[6] == 't') {
						sprintf(month, "October");
					}
					if (tim[4] == 'N' && tim[5] == 'o' && tim[6] == 'v') {
						sprintf(month, "November");
					}
					if (tim[4] == 'D' && tim[5] == 'e' && tim[6] == 'c') {
						sprintf(month, "December");
					}
				}
			}
			arithTrig[0] = '\0'; command = true;
			if (year > 1759) {
				char* toOpen = getDynamicCharArrayLong("");
				sprintf(toOpen, "%s\\calendar.txt", atcPath);
				Calendar(toOpen, year);
				for (s = 0; s < abs((int)strlen(calendarStr)); s++) {
					calendar[s] = calendarStr[s];
				}
				calendar[s] = '\0';
				char* cald = getDynamicCharArrayLong("");
				int yu = 0, liN = 0, liR = 0;
				for (s = 0; s < abs((int)strlen(calendar)); s++) {
					liR = 0;
					liN = 0;
					while (calendar[s] != '\n' && s < abs((int)strlen(calendar))) {
						cald[yu] = calendar[s];
						yu++; s++;
						liN++;
					}
					liR = 124 - liN;
					while (liR > 0) {
						cald[yu] = ' ';
						yu++;
						liR--;
					}
					cald[yu] = '\n';
					yu++;
				}
				cald[yu] = '\0';
				int ca = 0;
				for (yu = 0; yu < abs((int)strlen(cald)); yu++) {
					calendar[yu] = cald[yu];
					if (calendar[yu] == '\n') {
						ca++;
					}
					if (calendar[yu] == ' ' && ca % 2 == 0 && ca >= 10) {
						calendar[yu] = (char)176;
					}
					if (calendar[yu] == ' ' && (ca % 2 == 1 || ca < 10)) {
						calendar[yu] = (char)177;
					}
					if (calendar[yu] == '|') {
						calendar[yu] = (char)179;
					}
				}
				calendar[yu] = '\0';
				ca = 0;
				int saveStartWeekDays = 0;
				for (s = 0; s < abs((int)strlen(calendar)); s++) {
					if (calendar[s] == '\n') {
						ca++;
						if (ca > 4) {
							calendar[s + 28] = (char)179;
							calendar[s + 34] = (char)179;
							calendar[s + 49] = (char)179;
							calendar[s + 55] = (char)179;
							calendar[s + 70] = (char)179;
							calendar[s + 76] = (char)179;
							calendar[s + 91] = (char)179;
							calendar[s + 97] = (char)179;
							calendar[s + 112] = (char)179;
							calendar[s + 118] = (char)179;
						}
						if (ca == 6) {
							saveStartWeekDays = s + 1;
						}
					}
				}
				int y = saveStartWeekDays;
				int k = 0;
				while (calendar[y] != '\n') {
					lineWeekDays[k] = calendar[y];
					y++;
					k++;
				}
				lineWeekDays[k] = '\0';
				for (s = 0; s < abs((int)strlen(calendar)); s++) {
					if (calendar[s] == 's' && calendar[s + 3] == 'd' && calendar[s + 4] == 'o') {
						calendar[s + 1] = 'a';
					}
					if (calendar[s] == 'm' && calendar[s + 1] == 'a' && calendar[s + 2] == 'r' && calendar[s + 4] == 'o') {
						calendar[s + 3] = 'c';
					}
				}
				calendar[s] = '\n'; calendar[s + 1] = '\0';
				if (currentYear == 1 && isContained(month, calendar)) {
					char* line = getDynamicCharArray("", "line");

					char background = calendar[strEnd];
					int getStart = strStart;
					while (calendar[getStart] != '\n') {
						getStart--;
					}
					getStart++;
					int startLine = getStart;
					int d = startLine;

					int h = 0;
					while (calendar[d] != '\n') {
						line[h] = calendar[d];
						d++;
						h++;
					}
					line[h] = '\0';
					char* changeLine = getDynamicCharArrayLong("");
					sprintf(changeLine, line);
					char* changeWeekDaysLine = getDynamicCharArrayLong("");
					sprintf(changeWeekDaysLine, lineWeekDays);
					changeLine[0] = ' ';
					h = 1;
					while (changeLine[h] == month[h - 1]) {
						h++;
					}
					changeLine[h] = ' ';
					int foundDay = 0;
					while (foundDay == 0) {
						while (changeLine[h] != day[0]) {
							h++;
						}
						if (1 < abs((int)strlen(day))) {
							if (day[1] == changeLine[h + 1]) {
								changeLine[h - 1] = ' ';
								changeWeekDaysLine[h - 1] = ' ';
								h = h + 2;
								changeLine[h] = ' ';
								changeWeekDaysLine[h] = ' ';
								foundDay = 1;
							}
						}
						else {
							if (day[1] == '\0') {
								changeLine[h - 1] = ' ';
								changeWeekDaysLine[h - 2] = ' ';
								h = h + 1;
								changeLine[h] = ' ';
								changeWeekDaysLine[h] = ' ';
								foundDay = 1;
							}
						}
						h++;
					}
					replaceLong(line, changeLine, calendar);
					replaceLong(lineWeekDays, changeWeekDaysLine, expressionF);
					sprintf(calendar, "%s", expressionF);
					for (i = 0; i < abs((int)strlen(calendar)); i++) {
						if (calendar[i] == ' ') {
							calendar[i] = (char)219;
						}
					}
					_deleteLong(changeLine, "changeLine");
					changeLine = nullptr;
					_deleteLong(changeWeekDaysLine, "changeWeekDaysLine");
					_deleteLong(toOpen, "toOpen");
					changeWeekDaysLine = nullptr;
					_delete(line, "line");
					line = nullptr;
				}

				printf("\n");
				printf("%s\n", calendar);
				for (s = 0; s < abs((int)strlen(calendarStr)); s++) {
					calendar[s] = calendarStr[s];
				}
				calendar[s] = '\0';
				fprintf(fout, "\n");
				fprintf(fout, "%s\n\n", calendar);
				_deleteLong(cald, "cald"); cald = nullptr;
				_deleteLong(toOpen, "toOpen");
			}
			else {
				printf("\n");
				printf("Please enter years after 1759\n\n");
				fprintf(fout, "\n");
				fprintf(fout, "Please enter years after 1759\n\n");
			}
		}
		_deleteLong(ye, "ye");
		ye = nullptr;
		if (calendar != nullptr) {
			_deleteLong(calendar, "calendar");
			calendar = nullptr;
		}

		if (lineWeekDays != nullptr) {
			_delete(lineWeekDays, "lineWeekDays");
			lineWeekDays = nullptr;
		}
		if (month != nullptr) {
			_delete(month, "month");
			month = nullptr;
		}
		if (day != nullptr && strlen(day) > 0) {
			_delete(day, "day");
			day = nullptr;
		}
	}
	if (isCommand(arithTrig, "creatematrix") && arithTrig[i + 12] == '(') {
		command = true;
		if (isContained("++0", arithTrig)) {
			replace("++0", "+0", arithTrig);
			sprintf(arithTrig, "%s", expressionF);
		}
		char* matrixData = getDynamicCharArray("", "matrixData");
		int start = 13, index = 0;
		while (start < abs((int)strlen(arithTrig)) && (arithTrig[start] == ')' && arithTrig[start + 1] == '+' && arithTrig[start + 2] == '0' && arithTrig[start + 3] == '\0') == false) {
			matrixData[index] = arithTrig[start];
			start++; index++;
		}
		matrixData[index] = '\0';
		for (int p = 0; p < DIMTWOD; p++) {
			sprintf(splitResult[p], "");
		}
		if (countOccurrences("\\", matrixData) == 3) {
			split("\\", matrixData);
			char* variable = getDynamicCharArray("", "variable");
			char* nrLines = getDynamicCharArray("", "nrLines");
			char* nrCols = getDynamicCharArray("", "nrCols");
			char* expR = getDynamicCharArray("", "expR");
			sprintf(variable, "%s", splitResult[0]);
			sprintf(nrLines, "%s", splitResult[1]);
			sprintf(nrCols, "%s", splitResult[2]);
			sprintf(expR, "%s", splitResult[3]);

			int linesNum = (int)calcNow<T>(nrLines, (T)0, (T)0);
			int colsNum = (int)calcNow<T>(nrCols, (T)0, (T)0);
			const char* expr = "";
			expr = createMatrix<T>(variable, linesNum, colsNum, expR);
			_delete(nrLines, "nrLines");
			nrLines = nullptr;
			_delete(nrCols, "nrCols");
			nrCols = nullptr;
			_delete(toOpen, "toOpen");
			toOpen = nullptr;
			_delete(arithTrig, "arithTrig");
			arithTrig = nullptr;
			_delete(stringV, "stringV");
			_delete(expR, "expR");
			stringV = nullptr;
			_delete(matrixData, "matrixData"); matrixData = nullptr;

			if (linesNum > 0 && colsNum > 0 && (!(linesNum == 1 && colsNum == 1))) {

				if (abs((int)strlen(matrixResult)) > 0) {
					sprintf(matrixResult, "%s", ansMatrices[rf - 1]);
					sprintf(saveMatrixAns, "%s", ansMatrices[rf - 1]);
				}

			}

			static std::string str = variable;
			const char* _str = str.c_str();
			_delete(variable, "variable");

			if (strlen(expr) > 0) {
				command = false;

				sprintf(expression, "#%d", rf - 1);
				haveCreatedDynamicMatrix = true;

			}
			else {
				printf("\n\n Error: Please check your entered data.\n\n");
				command = true;
			}



		}
		else {
			_delete(matrixData, "matrixData"); matrixData = nullptr;
		}

	}
	if (command == (bool)true && arithTrig != nullptr) {
		sprintf(arithTrig, "");
	}
	if (fout != NULL) {
		fclose(fout);
	}
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
	_delete(arithTrig, "arithTrig");
	arithTrig = nullptr;
	_delete(stringV, "stringV");
	stringV = nullptr;
	return command;
}

bool isCommand(char* forTesting, char* command) {
	char* toTest = getDynamicCharArray("", "toTest");
	int i = 0;
	while (verifyLetter(forTesting[i]) || verifyNumber(forTesting[i])) {
		toTest[i] = forTesting[i];
		i++;
	}
	toTest[i] = '\0';
	if (isEqual(toTest, command)) {
		if (forTesting[abs((int)strlen(toTest))] == '(' || (forTesting[abs((int)strlen(toTest))] == '+' && forTesting[abs((int)strlen(toTest)) + 1] == '0' && forTesting[abs((int)strlen(toTest)) + 2] == '\0')) {
			if (forTesting[abs((int)strlen(toTest))] == '(') {
				i = abs((int)strlen(toTest));
				int rP = 0, lP = 0;
				while (i < abs((int)strlen(forTesting)) && i < abs((int)strlen(forTesting))) {
					if (forTesting[i] == '(') {
						lP++;
					}
					if (forTesting[i] == ')') {
						rP++;
					}
					i++;
				}
				if (rP == lP) {
					_delete(toTest, "toTest");
					return true;
				}
				else {
					_delete(toTest, "toTest");
					return false;
				}
			}
			_delete(toTest, "toTest");
			return true;
		}
		_delete(toTest, "toTest");
		return false;
	}
	else {
		_delete(toTest, "toTest");
		return false;
	}
}
template bool commands<double>(char*, char*, double, double, FILE*);







