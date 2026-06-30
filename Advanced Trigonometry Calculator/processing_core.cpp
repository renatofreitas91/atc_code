

#include "stdafx.h"
char* matrixResult = getDynamicCharArray("", "matrixResult"), * matrixValue = getDynamicCharArray(" ", "matrixValue"), * expr = getDynamicCharArray("", "expr");
bool checkMatrixIndex = false;

static std::string verboseDisplayExpression(const char* expression) {
	if (expression == nullptr) {
		return "";
	}
	std::string text(expression);
	if (text.size() > 2 && text.compare(text.size() - 2, 2, "+0") == 0) {
		text.erase(text.size() - 2);
	}
	return text;
}

template <typename T>
static void printVerboseComplexValue(const char* label, T realValue, T imaginaryValue) {
	convertComplex2Exponential(realValue, imaginaryValue);
	printf("%s: ", label);
	if (realValue > 0 && imaginaryValue > 0) {
		printf("%s+%si\n", respR, respI);
	}
	else if (realValue > 0 && imaginaryValue < 0) {
		printf("%s%si\n", respR, respI);
	}
	else if (realValue < 0 && imaginaryValue > 0) {
		printf("%s+%si\n", respR, respI);
	}
	else if (realValue < 0 && imaginaryValue < 0) {
		printf("%s%si\n", respR, respI);
	}
	else if (realValue == 0 && imaginaryValue == 0) {
		printf("%s\n", convert2Exponential(realValue));
	}
	else if (realValue == 0 && imaginaryValue != 0) {
		printf("%si\n", convert2Exponential(imaginaryValue));
	}
	else {
		printf("%s\n", convert2Exponential(realValue));
	}
}

static void normalizeCoreBooleanInfinityConstants(char* expression) {
	if (expression == nullptr || abs((int)strlen(expression)) == 0) {
		return;
	}
	std::string source(expression);
	std::string normalized;
	for (size_t i = 0; i < source.size();) {
		bool leftBoundary = i == 0 || (!std::isalnum((unsigned char)source[i - 1]) && source[i - 1] != '_');
		if (leftBoundary && source.compare(i, 5, "false") == 0 &&
			(i + 5 == source.size() || !std::isalnum((unsigned char)source[i + 5]))) {
			normalized += "0";
			i += 5;
			continue;
		}
		if (leftBoundary && source.compare(i, 4, "true") == 0 &&
			(i + 4 == source.size() || !std::isalnum((unsigned char)source[i + 4]))) {
			normalized += "1";
			i += 4;
			continue;
		}
		if (leftBoundary && source.compare(i, 4, "_INF") == 0 &&
			(i + 4 == source.size() || !std::isalnum((unsigned char)source[i + 4]))) {
			normalized += "(0-10^400)";
			i += 4;
			continue;
		}
		if (leftBoundary && source.compare(i, 3, "INF") == 0 &&
			(i + 3 == source.size() || !std::isalnum((unsigned char)source[i + 3]))) {
			normalized += "(10^400)";
			i += 3;
			continue;
		}
		normalized += source[i];
		i++;
	}
	sprintf(expression, "%s", normalized.c_str());
}

static bool getTopLevelFunctionArgument(const char* expression, const char* functionName, std::string& argument) {
	if (expression == nullptr || functionName == nullptr) {
		return false;
	}
	std::string text(expression);
	std::string prefix = std::string(functionName) + "(";
	if (text.compare(0, prefix.size(), prefix) != 0 || text.size() <= prefix.size()) {
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

static bool parseCoreLinearNumber(const std::string& text, long double& value) {
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

static bool parseUnsignedCoreConstantProduct(const std::string& text, long double& value) {
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

static bool parseCoreConstantProduct(const std::string& text, long double& value) {
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
	if (!parseUnsignedCoreConstantProduct(normalized, unsignedValue)) {
		return false;
	}
	value = sign * unsignedValue;
	return true;
}

static bool parseCoreLinearComplexNumber(const std::string& text, std::complex<long double>& value) {
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
	if (parseCoreLinearNumber(normalized, realValue) || parseCoreConstantProduct(normalized, realValue)) {
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
		if (parseCoreLinearNumber(imaginaryText, imaginaryValue) || parseCoreConstantProduct(imaginaryText, imaginaryValue)) {
			value = std::complex<long double>(0.0L, imaginaryValue);
			return true;
		}
	}
	return false;
}

static bool trySolveCoreLinearExpressionComplex(const std::string& expression, std::complex<long double>& solution) {
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
				if (!parseCoreLinearComplexNumber(coeffText, termCoefficient)) {
					return false;
				}
				coefficient += termCoefficient;
			}
			hasX = true;
		}
		else {
			std::complex<long double> termConstant(0.0L, 0.0L);
			if (!parseCoreLinearComplexNumber(term, termConstant)) {
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

static bool trySolveCoreLinearExpression(const std::string& expression, long double& solution) {
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
			std::string suffixText = term.substr(xPos + 1);
			if (!suffixText.empty() && suffixText != "^1") {
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
				if (!parseCoreLinearNumber(coeffText, termCoefficient)) {
					return false;
				}
				coefficient += termCoefficient;
			}
			hasX = true;
		}
		else {
			long double termConstant = 0.0L;
			if (!parseCoreLinearNumber(term, termConstant)) {
				return false;
			}
			constant += termConstant;
		}
		start = end;
	}
	if (!hasX || std::fabsl(coefficient) < 1E-30L) {
		return false;
	}
	solution = -constant / coefficient;
	return true;
}

static std::string stripCoreBalancedOuterParentheses(const std::string& source) {
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

static bool trySolveCoreLinearProductExpression(const std::string& expression, long double& solution) {
	std::string text;
	text.reserve(expression.size());
	for (size_t i = 0; i < expression.size(); i++) {
		if (!std::isspace((unsigned char)expression[i])) {
			text.push_back(expression[i]);
		}
	}
	text = stripCoreBalancedOuterParentheses(text);
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
		std::string factor = stripCoreBalancedOuterParentheses(text.substr(start + 1, i - start - 1));
		if (trySolveCoreLinearExpression(factor, solution)) {
			return true;
		}
		std::string reducedFactor;
		if (reduceExactRationalProductExpression(factor.c_str(), reducedFactor) && reducedFactor != factor &&
			(trySolveCoreLinearExpression(reducedFactor, solution) ||
				trySolveCoreLinearProductExpression(reducedFactor, solution))) {
			return true;
		}
		i++;
		if (i < text.size() && text[i] == '*') {
			i++;
		}
	}
	return false;
}

static bool trySolveCoreLinearProductExpressionComplex(const std::string& expression, std::complex<long double>& solution) {
	std::string text;
	text.reserve(expression.size());
	for (size_t i = 0; i < expression.size(); i++) {
		if (!std::isspace((unsigned char)expression[i])) {
			text.push_back(expression[i]);
		}
	}
	text = stripCoreBalancedOuterParentheses(text);
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
		std::string factor = stripCoreBalancedOuterParentheses(text.substr(start + 1, i - start - 1));
		if (trySolveCoreLinearExpressionComplex(factor, solution)) {
			return true;
		}
		std::string reducedFactor;
		if (reduceExactRationalProductExpression(factor.c_str(), reducedFactor) && reducedFactor != factor &&
			(trySolveCoreLinearExpressionComplex(reducedFactor, solution) ||
				trySolveCoreLinearProductExpressionComplex(reducedFactor, solution))) {
			return true;
		}
		i++;
		if (i < text.size() && text[i] == '*') {
			i++;
		}
	}
	return false;
}

template double initialProcessor<double>(char* arithTrig, double result);
template mp_float initialProcessor<mp_float>(char* arithTrig, mp_float result);
template bool tryEvaluateSolverFastPath<double>(char* expression, double& solution);
template bool tryEvaluateSolverFastPath<mp_float>(char* expression, mp_float& solution);

template<typename T>
bool tryEvaluateSolverFastPath(char* expression, T& solution) {
	std::string solverArgument;
	if (!getTopLevelFunctionArgument(expression, "solver", solverArgument)) {
		return false;
	}
	std::string reducedRationalProduct;
	if (reduceExactRationalProductExpression(solverArgument.c_str(), reducedRationalProduct)) {
		solverArgument = reducedRationalProduct;
	}
	std::complex<long double> complexSolution(0.0L, 0.0L);
	if (!trySolveCoreLinearExpressionComplex(solverArgument, complexSolution) &&
		!trySolveCoreLinearProductExpressionComplex(solverArgument, complexSolution)) {
		return false;
	}
	solution = (T)complexSolution.real();
	resultR = solution;
	resultI = (T)complexSolution.imag();
	verified = 1;
	return true;
}

template<typename T>
T initialProcessor(char* arithTrig, T result) {
	normalizeCoreBooleanInfinityConstants(arithTrig);
	replaceTimes = 0;
	T fastPathSolution = 0;
	if (tryEvaluateSolverFastPath(arithTrig, fastPathSolution)) {
		return fastPathSolution;
	}
	std::string solverArgument;
	if (getTopLevelFunctionArgument(arithTrig, "solver", solverArgument)) {
		std::string reducedSolverArgument;
		std::string solverFastArgument = solverArgument;
		if (reduceExactRationalProductExpression(solverArgument.c_str(), reducedSolverArgument)) {
			solverFastArgument = reducedSolverArgument;
		}
		std::complex<long double> complexSolution(0.0L, 0.0L);
		if (trySolveCoreLinearExpressionComplex(solverFastArgument, complexSolution) ||
			trySolveCoreLinearProductExpressionComplex(solverFastArgument, complexSolution)) {
			resultR = (T)complexSolution.real();
			resultI = (T)complexSolution.imag();
			verified = 1;
			return (T)complexSolution.real();
		}
		char* solverExpression = getDynamicCharArray(const_cast<char*>(solverArgument.c_str()), "solverExpression");
		T solverResult = solver<T>(solverExpression);
		_delete(solverExpression, "solverExpression");
		solverExpression = nullptr;
		return solverResult;
	}
	char* saveFunc = getDynamicCharArray("", "saveFunc");
	char* simplified = getDynamicCharArray("", "simplified");
	char** vectors = new char* [DIMTWOD];
	for (int w = 0; w < DIMTWOD; w++) {
		vectors[w] = getDynamicCharArray("", "vectors[w]");
	}
	char* func = getDynamicCharArray("", "func");

	check4Vector = 1;

	if (verbose == 1 && solving) {
		printf("\n\n==> initialProcessor <==\n\nExpression: %s\n", verboseDisplayExpression(arithTrig).c_str());
	}
	if (abs((int)strlen(arithTrig)) == 0 || isEqual("0", arithTrig)) {
		resultR = 0;
		resultI = 0;
		_delete(saveFunc, "saveFunc");
		_delete(func, "func");
		_delete(simplified, "simplified");
		_Delete(vectors, DIMTWOD, DIMDOUBLE, "vectors[w]");
		return 0;
	}
	int* signalVectors = getDynamicIntArray();
	int numVectorCols1 = 0, numVectorLines1 = 0, countVectors = 0;
	char* arTrig = getDynamicCharArray("", "arTrig"); char* trigon = getDynamicCharArray("", "trigon"); char* trig = getDynamicCharArray("", "trig"); char* paRect = getDynamicCharArray("", "paRect");
	char* cN = getDynamicCharArray("", "cN"); char* ex = getDynamicCharArray("", "ex");
	int* parent = getDynamicIntArray();
	int facto = 0, *sig = getDynamicIntArray(), s = 0, rectPar = 0, h = 0, i = 0, rePar = 0, so = 0, j = 0, g = 0, count = 0, e = 0, d = 0, th = 0, f = 0, trigo = 1, trigono = 0, co = 0, k = 0, l = 0, tr = 0, pa = 0, paren = 1, pare = 0, tg = 0, p = 0, a = 0, c = 1, r = 0, iN = 0, iL = 0;
	T exp = 1, result1 = 0, result2 = 0, amplitude = 1;
	PrecisionValue* triArith = getDynamicDoubleArray(); PrecisionValue* triArithI = getDynamicDoubleArray();
	PrecisionValue** vector1_R = nullptr, ** vector1_I = nullptr, ** res_vectorR = nullptr, ** res_vectorI = nullptr;
	auto ensureMatrixScratch = [&]() {
		if (vector1_R != nullptr) {
			return;
		}
		vector1_R = new PrecisionValue* [DIMTWOD];
		for (int i = 0; i < DIMTWOD; ++i) {
			vector1_R[i] = getDynamicDoubleArray();
		}
		vector1_I = new PrecisionValue* [DIMTWOD];
		for (int i = 0; i < DIMTWOD; ++i) {
			vector1_I[i] = getDynamicDoubleArray();
		}
		res_vectorR = new PrecisionValue* [DIMTWOD];
		for (int i = 0; i < DIMTWOD; ++i) {
			res_vectorR[i] = getDynamicDoubleArray();
		}
		res_vectorI = new PrecisionValue* [DIMTWOD];
		for (int i = 0; i < DIMTWOD; ++i) {
			res_vectorI[i] = getDynamicDoubleArray();
		}
	};

	for (s = 0; s < DIMDOUBLE; s++) {
		triArith[s] = 0;
		triArithI[s] = 0;
		signalVectors[s] = -1;
		sig[s] = -1;
	}

	for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
		if (arithTrig[i] == '{') {
			arithTrig[i] = '(';
		}
		if (arithTrig[i] == '}') {
			arithTrig[i] = ')';
		}
		if (arithTrig[i] == '^' && arithTrig[i + 1] == '-') {
			arithTrig[i + 1] = '_';
		}
		if (arithTrig[i] == 'E' && arithTrig[i + 1] == '_') {
			arithTrig[i + 1] = '-';
		}
		if ((arithTrig[i] == 'B' || arithTrig[i] == 'O' || arithTrig[i] == 'H') && arithTrig[i + 1] == '_') {
			arithTrig[i + 1] = '-';
		}
	}
	arithTrig[i] = '+'; arithTrig[i + 1] = '('; arithTrig[i + 2] = '0'; arithTrig[i + 3] = ')'; arithTrig[i + 4] = '\0';
	for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
		if (arithTrig[s] == '+' && arithTrig[s - 1] == 'E' && arithTrig[s - 2] != 'P') {
			r = s;
			s--;
			while (arithTrig[s] != '*' && arithTrig[s] != '/' && arithTrig[s] != '^' && arithTrig[s] != '+' && (arithTrig[s] != '-' && arithTrig[s - 1] != 'H') && arithTrig[s] != 'H' && s > 0) {
				s--;
			}
			s--;
			if (arithTrig[s] != 'H') {
				int k = r;
				while (arithTrig[k + 1] != '\0') {
					arithTrig[k] = arithTrig[k + 1];
					k++;
				}
				arithTrig[k] = '\0';
			}
			s = r;
		}
	}
	char* paTrig = getDynamicCharArray(arithTrig, "paTrig");

	s = 0;
	for (s; s < abs((int)strlen(paTrig)); s++) {
		if ((paTrig[s] == 'E' || paTrig[s] == 'P') && (s == 0 || paTrig[s - 1] == '_' || paTrig[s - 1] == '*' || paTrig[s - 1] == '/' || paTrig[s - 1] == '^' || paTrig[s - 1] == '+' || (paTrig[s - 1] == '-' && paTrig[s - 2] != 'H') || paTrig[s - 1] == '(')) {
			arithTrig[s] = '1';
			for (s; s < abs((int)strlen(paTrig)); s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; s < abs((int)strlen(paTrig)); s++) {
		if ((paTrig[s] == 'i' && paTrig[s - 1] == 'p' || paTrig[s] == 'e' || paTrig[s] == ')' || arithTrig[s] == 'a' || arithTrig[s] == 'c' || arithTrig[s] == 'd' || arithTrig[s] == 'f' || arithTrig[s] == 'g' || arithTrig[s] == 'h' || arithTrig[s] == 'j' || arithTrig[s] == 'k' || arithTrig[s] == 'm' || arithTrig[s] == 'n' || arithTrig[s] == 'o' || arithTrig[s] == 'p' || arithTrig[s] == 'q' || arithTrig[s] == 'r' || arithTrig[s] == 's' || arithTrig[s] == 't' || arithTrig[s] == 'u' || arithTrig[s] == 'w' || arithTrig[s] == 'v' || arithTrig[s] == 'y' || arithTrig[s] == 'z' || arithTrig[s] == 'G' || arithTrig[s] == 'I' || arithTrig[s] == 'J' || arithTrig[s] == 'K' || arithTrig[s] == 'L' || arithTrig[s] == 'M' || arithTrig[s] == 'N' || arithTrig[s] == 'O' || arithTrig[s] == 'Q' || arithTrig[s] == 'R' || arithTrig[s] == 'S' || arithTrig[s] == 'T' || arithTrig[s] == 'U' || arithTrig[s] == 'V' || arithTrig[s] == 'Y' || arithTrig[s] == 'Z') && (paTrig[s + 1] == 'E' || paTrig[s + 1] == 'P')) {
			s++;
			arithTrig[s] = '1';
			for (s; s < abs((int)strlen(paTrig)); s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	int u = 0;
	for (u = 0; u < abs((int)strlen(arithTrig)); u++) {
		paTrig[u] = arithTrig[u];
	}
	paTrig[u] = '\0';
	u = 0;
	for (u; u < abs((int)strlen(paTrig)); u++) {
		if (verifyLetter(paTrig[u]) == 0) {
			while (verifyLetter(paTrig[u]) == 0 && u < abs((int)strlen(paTrig))) {
				u++;
			}
		}
		if (verifyLetter(paTrig[u]) == 1 && firstLetterVariable(paTrig[u]) == 0) {
			while (verifyLetter(paTrig[u]) == 1) {
				u++;
			}
		}
		if (firstLetterVariable(paTrig[u]) == 1 && firstLetterVariable(paTrig[u - 1]) == 0 && paTrig[u + 1] != 'i') {
			u++;
			while (verifyLetter(paTrig[u]) == 1) {
				u++;
			}
			if (paTrig[u] != '\\' && paTrig[u] != '*' && paTrig[u] != '+' && paTrig[u] != '-' && paTrig[u] != '/' && paTrig[u] != '^' && paTrig[u] != '!' && paTrig[u] != ')' && paTrig[u] != '[' && paTrig[u] != ']') {
				T check = 0;
				if (verifyLetter(paTrig[u - 1]) == 1) {
					int z = u - 1, v = 0;
					char* toVal = getDynamicCharArray(" ", "toVal");
					while (verifyLetter(paTrig[z]) == 1) {
						z--;
					}
					z++;
					while (verifyLetter(paTrig[z]) == 1) {
						toVal[v] = paTrig[z];
						z++; v++;
					}
					toVal[v] = '?'; toVal[v + 1] = '\0';
					check = functionProcessor<T>(toVal, 0, 0, 0, "");
					_delete(toVal, "toVal"); toVal = nullptr;

				}
				if (check != 0.5) {
					arithTrig[u] = '*';
					for (u; u < abs((int)strlen(paTrig)); u++) {
						arithTrig[u + 1] = paTrig[u];
					}
					arithTrig[u + 1] = '\0';
					u = 0;
					for (u = 0; u < abs((int)strlen(arithTrig)); u++) {
						paTrig[u] = arithTrig[u];
					}
					paTrig[u] = '\0';
					u = 0;
				}
			}
		}
	}

	s = 0;
	for (s; s < abs((int)strlen(paTrig)); s++) {
		if (paTrig[s] == ')' && paTrig[s + 1] == '(') {
			s++;
			arithTrig[s] = '*';
			for (s; s < abs((int)strlen(paTrig)); s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; s < abs((int)strlen(paTrig)); s++) {
		if ((arithTrig[s] == 'G' || arithTrig[s] == 'I' || arithTrig[s] == 'J' || arithTrig[s] == 'K' || arithTrig[s] == 'L' || arithTrig[s] == 'M' || arithTrig[s] == 'N' || arithTrig[s] == 'O' || arithTrig[s] == 'P' || arithTrig[s] == 'Q' || arithTrig[s] == 'R' || arithTrig[s] == 'S' || arithTrig[s] == 'T' || arithTrig[s] == 'U' || arithTrig[s] == 'V' || arithTrig[s] == 'X' || arithTrig[s] == 'Y' || arithTrig[s] == 'Z' || arithTrig[s] == 'a' || arithTrig[s] == 'c' || arithTrig[s] == 'd' || arithTrig[s] == 'f' || arithTrig[s] == 'g' || arithTrig[s] == 'h' || arithTrig[s] == 'j' || arithTrig[s] == 'k' || arithTrig[s] == 'm' || arithTrig[s] == 'n' || arithTrig[s] == 'o' || arithTrig[s] == 'p' || arithTrig[s] == 'q' || arithTrig[s] == 'r' || arithTrig[s] == 's' || arithTrig[s] == 't' || arithTrig[s] == 'u' || arithTrig[s] == 'w' || arithTrig[s] == 'v' || arithTrig[s] == 'y' || arithTrig[s] == 'z') && (paTrig[s + 1] == '1' && paTrig[s + 2] == 'E')) {
			s++;
			arithTrig[s] = '*';
			for (s; s < abs((int)strlen(paTrig)); s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; s < abs((int)strlen(paTrig)); s++) {
		if ((paTrig[s] == '1' || paTrig[s] == '2' || paTrig[s] == '3' || paTrig[s] == '4' || paTrig[s] == '5' || paTrig[s] == '6' || paTrig[s] == '7' || paTrig[s] == '8' || paTrig[s] == '9' || paTrig[s] == '0' || paTrig[s] == 'i' && paTrig[s + 1] != 'e' && paTrig[s - 1] == 'p' || (paTrig[s - 1] == 'v' && paTrig[s - 2] == 'l' && paTrig[s - 3] == 'o' && paTrig[s - 4] == 's' && paTrig[s + 1] == 'r') == false && paTrig[s] == 'e' && paTrig[s - 1] != 'c' && paTrig[s - 1] != 'd' && paTrig[s - 1] != 'r' && paTrig[s - 1] != 's' && paTrig[s - 1] != 'i' && paTrig[s + 2] != 't' || paTrig[s] == ')') && (paTrig[s + 1] == '(' || paTrig[s + 1] == 'a' || paTrig[s + 1] == 's' || paTrig[s + 1] == 'c' || (paTrig[s + 1] == 't' && paTrig[s - 1] != 'g' && paTrig[s] != 'e') || paTrig[s + 1] == 'l' || paTrig[s + 1] == 'p' || paTrig[s + 1] == 'e' || paTrig[s + 1] == 'r' && paTrig[s + 2] != 'r' || paTrig[s + 1] == 'd' || paTrig[s + 1] == 'm' || paTrig[s + 1] == 'q' || paTrig[s + 1] == 'g' && paTrig[s - 1] != 'd')) {
			s++;
			arithTrig[s] = '*';
			for (s; s < abs((int)strlen(paTrig)); s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; s < abs((int)strlen(paTrig)); s++) {
		if ((paTrig[s] == '1' || paTrig[s] == '2' || paTrig[s] == '3' || paTrig[s] == '4' || paTrig[s] == '5' || paTrig[s] == '6' || paTrig[s] == '7' || paTrig[s] == '8' || paTrig[s] == '9' || paTrig[s] == '0' || paTrig[s] == 'p' || paTrig[s] == 'e' || verifyLetter(paTrig[s]) == 1 && paTrig[s] != 'b' && paTrig[s] != 'D') && (paTrig[s - 1] == ')')) {
			arithTrig[s] = '*';
			for (s; s < abs((int)strlen(paTrig)); s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; s < abs((int)strlen(paTrig)); s++) {
		if ((paTrig[s + 1] == '1' || paTrig[s + 1] == '2' || paTrig[s + 1] == '3' || paTrig[s + 1] == '4' || paTrig[s + 1] == '5' || paTrig[s + 1] == '6' || paTrig[s + 1] == '7' || paTrig[s + 1] == '8' || paTrig[s + 1] == '9' || paTrig[s + 1] == '0' || paTrig[s + 1] == 'p' || paTrig[s + 1] == 'e') && (paTrig[s - 1] == 'p' && paTrig[s] == 'i' && paTrig[s + 1] != 'e' || paTrig[s] == 'e' && paTrig[s - 1] != 'i')) {
			s++;
			arithTrig[s] = '*';
			for (s; s < abs((int)strlen(paTrig)); s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; s < abs((int)strlen(paTrig)); s++) {
		if (paTrig[s] == '_' && (paTrig[s + 1] == '(' || paTrig[s + 1] == 'r' && paTrig[s + 2] == 'e' && paTrig[s + 3] == 's')) {
			arithTrig[s + 1] = '1'; arithTrig[s + 2] = '*'; s++;
			for (s; s < abs((int)strlen(paTrig)); s++) {
				arithTrig[s + 2] = paTrig[s];
			}
			arithTrig[s + 2] = '\0';
			s = 0;
			for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; s < abs((int)strlen(paTrig)); s++) {
		if ((paTrig[s - 2] == 'r' && paTrig[s - 1] == 'e' && paTrig[s] == 's' && paTrig[s + 2] != '(' && paTrig[s + 1] != '!' && verifyLetter(paTrig[s + 1]) == 0) && (paTrig[s + 1] != '+' && paTrig[s + 1] != '-' && paTrig[s + 1] != '*' && paTrig[s + 1] != '/' && paTrig[s + 1] != '^' && paTrig[s + 1] != ')' && paTrig[s + 1] != 'b')) {
			s++;
			arithTrig[s] = '*';
			for (s; s < abs((int)strlen(paTrig)); s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; s < abs((int)strlen(paTrig)); s++) {
		if ((paTrig[s] == 'e' || paTrig[s - 1] == 'p' && paTrig[s] == 'i') && (paTrig[s + 1] == 'p' && paTrig[s + 2] == 'i' || paTrig[s + 1] == 'e')) {
			s++;
			arithTrig[s] = '*';
			for (s; s < abs((int)strlen(paTrig)); s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; s < abs((int)strlen(paTrig)); s++) {
		if (paTrig[s + 1] == '_' && paTrig[s] != '\\' && paTrig[s] != ';' && paTrig[s] != '+' && paTrig[s] != '-' && paTrig[s] != '*' && paTrig[s] != '/' && paTrig[s] != '^' && paTrig[s] != '(' && (paTrig[s] != 'D' && paTrig[s - 1] != 't' && paTrig[s - 2] != 'r') && (paTrig[s] != 'b' && paTrig[s - 1] != 'g' && paTrig[s - 2] != 'o' && paTrig[s - 3] != 'l')) {
			s++;
			arithTrig[s] = '*';
			for (s; s < abs((int)strlen(paTrig)); s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
		parent[s] = 0;
	}

	int cp = 0, mark = 0;
	c = 0; d = 0; k = 0; l = 0; h = 0;
	for (s = 0; s < abs((int)strlen(arithTrig)) && s < abs((int)strlen(arithTrig)); s++) {
		if (arithTrig[s] == '(') {
			d = 0;
			c++;
			parent[s] = c;
			d = 1;
			k = c;
		}
		else {
			if (arithTrig[s] == ')') {
				d = 0;
				h = 0;
				l = 2;
				do {
					l = 0;
					h = 0;
					while (h < abs((int)strlen(arithTrig))) {
						if (parent[h] == k) {
							l++;
						}
						if (l == 2) {
							l = 0;
							k--;
						}
						h++;
					}
				} while (l == 2);
				h = 0;
				while (l != 1 && h < abs((int)strlen(arithTrig))) {
					h = 0;
					l = 0;
					while (h < abs((int)strlen(arithTrig))) {
						if (parent[h] == k) {
							l++;
						}
						if (l == 2) {
							k--;
							h = 0;
							l = 0;
						}
						h++;
					}
				}
				parent[s] = k;
			}
			else {
				parent[s] = 0;
			}
		}
	}
	int klp = s;
	arithTrig[s] = '\0';
	int curPar = 0, cur = 0;
	for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
		if (arithTrig[i] == '(' || arithTrig[i] == ')') {
			curPar = 1;
		}
	}
	arithTrig[i] = '\0';
	if (curPar == 0) {
		result1 = arithSolver(arithTrig, result);

		_Delete(vector1_R, DIMTWOD, dime, "vector1_R,DIMTWOD,dime");

		_Delete(vector1_I, DIMTWOD, dime, "vector1_I,DIMTWOD,dime");

		_Delete(res_vectorR, DIMTWOD, dime, "res_vectorR,DIMTWOD,dime");

		_Delete(res_vectorI, DIMTWOD, dime, "res_vectorI,DIMTWOD,dime");

		_delete(triArith, "triArith"); triArith = nullptr;
		_delete(triArithI, "triArithI"); triArithI = nullptr;
		_delete(arTrig, "arTrig"); arTrig = nullptr;
		_delete(paRect, "paRect"); paRect = nullptr;
		_delete(trig, "trig"); trig = nullptr;
		sprintf(cN, "");
		if (cN != nullptr) {
			_delete(cN, "cN"); cN = nullptr;
		}
		_delete(triArithI, "triArithI"); triArithI = nullptr;
		_delete(triArith, "triArith"); triArith = nullptr;
		_delete(paTrig, "paTrig"); paTrig = nullptr;
		_delete(trigon, "trigon"); trigon = nullptr;
		_delete(ex, "ex"); ex = nullptr;

		_delete(paTrig, "paTrig"); paTrig = nullptr;
		_delete(simplified, "simplified"); simplified = nullptr;
		_delete(saveFunc, "saveFunc"); saveFunc = nullptr;
		_deleteShort(func, "func");
		_Delete(vectors, DIMTWOD, DIMDOUBLE, "vectors[w]");
		_delete(signalVectors, "signalVectors"); signalVectors = nullptr;
		_delete(parent, "parent"); parent = nullptr;
		_delete(sig, "sig"); sig = nullptr;

		return result1;
	}
	a = 0;
	int de = 0, b = 0, ju = 0;
	c = 0;
	char* pas = getDynamicCharArray("", "pas");
	int se = 0;
	int thj = 0;
	if (curPar == 1) {
		char* op = getDynamicCharArray("", "op");
		for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
			int jk = 0;

			while (parent[i] < 1 && i <= klp && i < abs((int)strlen(arithTrig))) {

				bool hasFunctionParenthesis = false;
				int functionProbe = i;
				if (arithTrig[functionProbe] == '_') {
					functionProbe++;
				}
				while (functionProbe < abs((int)strlen(arithTrig)) && arithTrig[functionProbe] != '+' && arithTrig[functionProbe] != '-' && arithTrig[functionProbe] != '*' && arithTrig[functionProbe] != '/' && arithTrig[functionProbe] != '^' && arithTrig[functionProbe] != '!' && arithTrig[functionProbe] != ')') {
					if (arithTrig[functionProbe] == '(') {
						hasFunctionParenthesis = true;
						break;
					}
					functionProbe++;
				}
				if (hasFunctionParenthesis && (arithTrig[i] == '_' && (arithTrig[i + 1] == 'm' || arithTrig[i + 1] == 'g' || arithTrig[i + 1] == 's' || arithTrig[i + 1] == 'c' || arithTrig[i + 1] == 't' || arithTrig[i + 1] == 'a' || arithTrig[i + 1] == 'l' || arithTrig[i + 1] == 'd' || arithTrig[i + 1] == 'r') || arithTrig[i] == 'q' || arithTrig[i] == 's' || arithTrig[i] == 'c' || arithTrig[i] == 't' || arithTrig[i] == 'a' || arithTrig[i] == 'r' && (arithTrig[i + 3] == 't' && arithTrig[i + 4] != 'g' && arithTrig[i + 4] != 'a' || arithTrig[i + 1] == 'a' && arithTrig[i + 2] == 'd' || arithTrig[i + 1] == 't' && arithTrig[i + 2] == 'D') || arithTrig[i] == 'd' || arithTrig[i] == 'l' || arithTrig[i] == 'g' || arithTrig[i] == 'm')) {
					if (arithTrig[i] == '_') {
						thj = 1;
					}
					if (arithTrig[i - 1] == '1' || arithTrig[i - 1] == '2' || arithTrig[i - 1] == '3' || arithTrig[i - 1] == '4' || arithTrig[i - 1] == '5' || arithTrig[i - 1] == '6' || arithTrig[i - 1] == '7' || arithTrig[i - 1] == '8' || arithTrig[i - 1] == '9' || arithTrig[i - 1] == '0' || arithTrig[i - 1] == 'i' || arithTrig[i - 1] == 'e' || arithTrig[i - 1] == ')') {
						jk = 1;
					}ju = 0;
					while (arithTrig[i] != '(' && i < abs((int)strlen(arithTrig))) {
						if ((arithTrig[i] == 'b' && arithTrig[i - 1] != 'c' && arithTrig[i - 1] != 'a') || arithTrig[i] == 'D') {
							op[ju] = arithTrig[i];
							ju++; i++;
							while ((arithTrig[i] == 'b' && arithTrig[i + 1] == '(') == false && (arithTrig[i] == 'D' && arithTrig[i + 1] == '(') == false && i < abs((int)strlen(arithTrig))) {
								op[ju] = arithTrig[i];
								ju++; i++;
							}
						}
						op[ju] = arithTrig[i];
						ju++; i++;
					}
					op[ju] = '\0';
				}
				else {
					a = 0; if (arithTrig[i] == '_' && arithTrig[i + 1] != 's' && arithTrig[i + 1] != 'c' && arithTrig[i + 1] != 't' && arithTrig[i + 1] != 'a' && arithTrig[i + 1] != 'l' && arithTrig[i + 1] != 'd' && arithTrig[i + 1] != 'r' && arithTrig[i + 1] != 'g' && arithTrig[i + 1] != 'm') {
						pas[a] = arithTrig[i]; a++; i++;
					}
					while (arithTrig[i] != '+' && arithTrig[i] != '-' && arithTrig[i] != '*' && arithTrig[i] != '/' && arithTrig[i] != '^' && arithTrig[i] != '!' && arithTrig[i] != ')') {
						pas[a] = arithTrig[i];
						a++;
						i++;
						if (arithTrig[i] == '-' && arithTrig[i - 1] == 'E' || arithTrig[i] == '-' && arithTrig[i - 1] == 'O' || arithTrig[i] == '-' && arithTrig[i - 1] == 'B' || arithTrig[i] == '-' && arithTrig[i - 1] == 'H') {
							pas[a] = arithTrig[i];
							a++;
							i++;
						}
					}
				}
				pas[a] = '\0';

				if (jk == 1) {
					arTrig[c] = '*';
				}
				if (c < i && i < abs((int)strlen(arithTrig)) && (arithTrig[i] == '+' || arithTrig[i] == '-' || arithTrig[i] == '*' || arithTrig[i] == '/' || arithTrig[i] == '^' || arithTrig[i] == '!')) {
					arTrig[c] = arithTrig[i]; c++;
				}
				if (abs((int)strlen(pas)) > 0) {
					check4Vector = 1;
					triArith[b] = arithSolver(pas, result);
					triArithI[b] = resultI;
					if (b > 0 && (arTrig[b - 1] == '^' || (c > 0 && arTrig[c - 1] == '^'))) {
						if (isEqual("T", pas)) {
							triArith[b] = -7654321;
							triArithI[b] = 0;
						}
						if (isEqual("R", pas)) {
							triArith[b] = -1234567;
							triArithI[b] = 0;
						}
					}

					if (check4Vector == 2) {
						triArith[b] = 1;
						matrixMode = 1;
						triArithI[b] = 0;
						signalVectors[b] = countVectors;
						sprintf(vectors[countVectors], "%s", vectorString);
						countVectors++;
					}
					pas[0] = '\0';
					b++;
				}
				i++;
				if (abs((int)strlen(op)) > 0) {
					i--;
				}

			}
			pas[a] = '\0';
			cur = parent[i];
			j = i;
			if (parent[i] == cur) {
				i = j;
				a = 0;
				i++;
				while (parent[i] != cur && i < abs((int)strlen(arithTrig))) {
					pas[a] = arithTrig[i];
					a++; i++;
				}
				pas[a] = '\0';
				int kl = 0;
				for (de = 0; de < abs((int)strlen(pas)); de++) {
					if (pas[de] == '(' || pas[de] == ')') {
						kl = 1;
					}
				}
				a = 0;
				if (kl == 0) {
					renamer(pas);
					sprintf(pas, "%s", expressionF);
					if (isContained("det", op)) {
						startDetProcessing(pas);
						triArith[b] = resultR;
						triArithI[b] = resultI;
						if (op[0] == '_') {
							triArith[b] = precisionValueTo<T>(triArith[b]) * -1;
							triArithI[b] = precisionValueTo<T>(triArithI[b]) * -1;
							sig[b] = 0;
						}
					}
					else {
						if (isContained("strlen", op)) {
							triArith[b] = (T)strlength(pas);
							triArithI[b] = 0;
						}
						else {
							if (isContained("colsnum", op)) {
								triArith[b] = (T)colsNumber(pas);
								triArithI[b] = 0;
							}
							else {
								if (isContained("linsnum", op)) {
									triArith[b] = (T)linesNumber(pas);
									triArithI[b] = 0;
								}
								else {
									if (isContained("countoccurrences", op)) {
										if (countOccurrences("\\", arithTrig) == 1) {
											renamer(pas);
											sprintf(pas, "%s", expressionF);
											int p = 0, q = 0;
											char* string = getDynamicCharArray("", "string");
											char* to_find = getDynamicCharArray("", "to_find");
											while (pas[p] != '\\') {
												to_find[p] = pas[p];
												p++;
											}
											to_find[p] = '\0';
											renamer(to_find);
											sprintf(to_find, "%s", expressionF);
											p++;
											q = 0;
											while (p < abs((int)strlen(pas))) {
												string[q] = pas[p];
												p++; q++;
											}
											string[q] = '\0';
											renamer(string);
											sprintf(string, "%s", expressionF);
											stringVariableToString(to_find);
											sprintf(to_find, "%s", variableSTring);
											stringVariableToString(string);
											sprintf(string, "%s", variableSTring);
											triArith[b] = (T)countOccurrences(to_find, string);
											triArithI[b] = 0;
											_delete(string, "string"); string = nullptr;
											_delete(to_find, "to_find"); to_find = nullptr;

										}
										else {
											puts("\nError: Please use a \"\\\" to separate the variables.\n");
										}
									}
									else {
										if (isContained("calc", op)) {
											renamer(pas);
											sprintf(pas, "%s", expressionF);
											stringVariableToString(pas);
											sprintf(pas, "%s", variableSTring);
											calcNow<T>(pas, (T)0, (T)0);
											triArith[b] = resultR;
											triArithI[b] = resultI;
										}
										else {

											if (isContained("getlins", op)) {
												getLines(pas);
												if (numVectorCols > 1 || numVectorLines > 1) {
													matrixMode = 1;
													signalVectors[b] = countVectors;
													sprintf(vectors[countVectors], "%s", matrixValue);
													countVectors++;
													triArith[b] = 1;
													triArithI[b] = 0;
												}
												else {
													triArith[b] = vectorR[0][0];
													triArithI[b] = vectorI[0][0];
													signalVectors[b] = -1;
													matrixMode = 0;
												}
											}
											else {
												if (isContained("getcols", op)) {
													getCols(pas);
													if (numVectorCols > 1 || numVectorLines > 1) {
														matrixMode = 1;
														signalVectors[b] = countVectors;
														sprintf(vectors[countVectors], "%s", matrixValue);
														countVectors++;
														triArith[b] = 1;
														triArithI[b] = 0;
													}
													else {
														triArith[b] = vectorR[0][0];
														triArithI[b] = vectorI[0][0];
														signalVectors[b] = -1;
														matrixMode = 0;
													}
												}
												else {
													check4Vector = 1;
													triArith[b] = arithSolver(pas, result);
													triArithI[b] = resultI;
													if (b > 0 && (arTrig[b - 1] == '^' || (c > 0 && arTrig[c - 1] == '^'))) {
														if (isEqual("T", pas)) {
															triArith[b] = -7654321;
															triArithI[b] = 0;
														}
														if (isEqual("R", pas)) {
															triArith[b] = -1234567;
															triArithI[b] = 0;
														}
													}
													if (check4Vector == 2) {
														matrixMode = 1;
														signalVectors[b] = countVectors;
														sprintf(vectors[countVectors], "%s", vectorString);
														triArith[b] = 1;
														triArithI[b] = 0;
														countVectors++;
														sprintf(matrixValue, "%s", vectorString);
													}
													sprintf(expressionF, pas);
													sig[b] = 1;
													char* matrixArgument = getDynamicCharArray(pas, "matrixArgument");
													pas[0] = '\0';
													ju = 0;

													if (abs((int)strlen(op)) > 0) {

														PrecisionValue** vector1_R, ** vector1_I;
														vector1_R = new PrecisionValue* [DIMTWOD];

														for (int i = 0; i < DIMTWOD; ++i) {
															vector1_R[i] = getDynamicDoubleArray();
														}
														vector1_I = new PrecisionValue* [DIMTWOD];

														for (int i = 0; i < DIMTWOD; ++i) {
															vector1_I[i] = getDynamicDoubleArray();
														}
														int numVectorCols1 = 0, numVectorLines1 = 0;
														sprintf(saveFunc, "%s", op);

														if (isContained("avg", op)) {
															average(abs((int)strlen(matrixValue)) > 0 ? matrixValue : matrixArgument);
															triArith[b] = resultR;
															triArithI[b] = resultI;
															if (op[0] == '_') {
																triArith[b] = precisionValueTo<T>(triArith[b]) * -1;
																triArithI[b] = precisionValueTo<T>(triArithI[b]) * -1;
																sig[b] = 0;
															}
															matrixMode = 0;
															sprintf(matrixValue, "");
															signalVectors[b] = -1;

														}
														else {
															if (isContained("max", op)) {
																maximum(abs((int)strlen(matrixValue)) > 0 ? matrixValue : matrixArgument);
																triArith[b] = resultR;
																triArithI[b] = resultI;
																if (op[0] == '_') {
																	triArith[b] = precisionValueTo<T>(triArith[b]) * -1;
																	triArithI[b] = precisionValueTo<T>(triArithI[b]) * -1;
																	sig[b] = 0;
																}
																matrixMode = 0;
																sprintf(matrixValue, "");
																signalVectors[b] = -1;
															}
															else {
																if (isContained("min", op)) {
																	minimum(abs((int)strlen(matrixValue)) > 0 ? matrixValue : matrixArgument);
																	triArith[b] = resultR;
																	triArithI[b] = resultI;
																	if (op[0] == '_') {
																		triArith[b] = precisionValueTo<T>(triArith[b]) * -1;
																		triArithI[b] = precisionValueTo<T>(triArithI[b]) * -1;
																		sig[b] = 0;
																	}
																	matrixMode = 0;
																	sprintf(matrixValue, "");
																	signalVectors[b] = -1;
																}
																else {
																	if (op[3] == 't' && (op[2] == 's' || op[2] == 'o' && op[1] != 'c')) {
																		if (abs((int)strlen(matrixValue)) > 0) {
																			convert2Vector(matrixValue);
																			sprintf(matrixValue, "");
																			int n = 0;
																			int m = 0;
																			for (n = 0; n < numVectorLines; n++) {
																				for (m = 0; m < numVectorCols; m++) {
																					sprintf(op, "%s", saveFunc);
																					resultI = vectorI[n][m]; resultR = triArithI[b - 1];

																					vector1_R[n][m] = functionProcessor<T>(op, vectorR[n][m], triArith[b - 1], rf, "");
																					triArith[b] = 0;
																					vector1_I[n][m] = precisionValueTo<T>(resultI);
																					triArithI[b] = 0;
																				}
																			}
																			numVectorCols1 = numVectorCols;
																			numVectorLines1 = numVectorLines;
																			sprintf(matrixResult, convertVector2String(vector1_R, vector1_I, numVectorLines1, numVectorCols1));
																			sprintf(vectors[countVectors - 1], "%s", matrixResult);
																		}
																		else {

																			resultI = triArithI[b]; resultR = triArithI[b - 1];

																			triArith[b - 1] = functionProcessor<T>(op, triArith[b], triArith[b - 1], rf, "");
																			triArith[b] = 0;
																			triArithI[b - 1] = resultI;
																			triArithI[b] = 0;

																		}
																		arTrig[b - 1] = '+';
																	}
																	else {
																		if (abs((int)strlen(matrixValue)) > 0) {

																			if (!isContained("atc_", op)) {

																				convert2Vector(matrixValue);

																				sprintf(matrixValue, "");
																				int n = 0;
																				int m = 0;
																				for (n = 0; n < numVectorLines; n++) {
																					for (m = 0; m < numVectorCols; m++) {
																						sprintf(op, "%s", saveFunc);
																						resultI = vectorI[n][m];
																						if (isContained("C:\\", expressionF)) {
																							sprintf(expressionF, "");
																						}

																						vector1_R[n][m] = functionProcessor<T>(op, vectorR[n][m], amplitude, rf, "");
																						vector1_I[n][m] = precisionValueTo<T>(resultI);
																					}
																				}

																				numVectorCols1 = numVectorCols;
																				numVectorLines1 = numVectorLines;
																				numVectorCols1 = numVectorCols;
																				numVectorLines1 = numVectorLines;
																				sprintf(matrixResult, convertVector2String(vector1_R, vector1_I, numVectorLines1, numVectorCols1));

																			}
																			else {

																				functionProcessor<T>(op, 0, amplitude, rf, "");

																			}

																			if (countVectors > 0) {
																				sprintf(vectors[countVectors - 1], "%s", matrixResult);
																			}
																			else {
																				sprintf(vectors[countVectors], "%s", matrixResult);

																			}

																		}
																		else {

																			triArith[b] = functionProcessor<T>(op, triArith[b], amplitude, rf, "");
																			triArithI[b] = resultI;

																		}

																	}

																}

															}

														}

														if (thj == 1) { thj = 0; sig[b] = 0; }
														else {
															sig[b] = 1;
														}
														pas[0] = '\0';
														ju = 0;

														_delete(matrixArgument, "matrixArgument"); matrixArgument = nullptr;

														_Delete(vector1_R, DIMTWOD, dime, "vector1_R,DIMTWOD,dime");
														vector1_R = nullptr;
														_Delete(vector1_I, DIMTWOD, dime, "vector1_I,DIMTWOD,dime");

														vector1_I = nullptr;


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

				if (kl == 1) {
					sprintf(expr, "%s", pas);
					std::string solverOriginalExpression(expr);
					renamer(pas);

					sprintf(pas, "%s", expressionF);
					if (isContained("solver", op)) {
						retrySolver = false; retrySolver_2 = false; retrySolver_3 = false; equation_solver = true;
						poly = true;
						replaceTimes = 0;
						sprintf(roots, ""), sprintf(answers, "");
						sprintf(expressionF, "%s", expr);
						std::string solverExpression(expr);
						std::string solverFastExpression = solverExpression;
						std::string originalSolverArgument = solverOriginalExpression;
						if (solverFastExpression.find('x') == std::string::npos) {
							std::string topLevelSolverArgument;
							if (getTopLevelFunctionArgument(arithTrig, "solver", topLevelSolverArgument) &&
								topLevelSolverArgument.find('x') != std::string::npos) {
								originalSolverArgument = topLevelSolverArgument;
							}
						}
						if (solverFastExpression.find('x') == std::string::npos &&
							originalSolverArgument.find('x') != std::string::npos) {
							solverFastExpression = originalSolverArgument;
						}
						std::string reducedRationalProduct;
						if (reduceExactRationalProductExpression(solverFastExpression.c_str(), reducedRationalProduct)) {
							solverFastExpression = reducedRationalProduct;
						}
						long double linearSolution = 0.0L;
						if (trySolveCoreLinearExpression(solverFastExpression, linearSolution) ||
							trySolveCoreLinearProductExpression(solverFastExpression, linearSolution)) {
							resultR = (T)linearSolution;
							resultI = 0;
							verified = 1;
							triArith[b] = (T)linearSolution;
						}
						else {
							triArith[b] = solver<T>(expr);
						}
						sprintf(roots, ""), sprintf(answers, "");
						equation_solver = false;
						triArithI[b] = resultI;
						if (op[0] == '_') {
							triArith[b] = precisionValueTo<T>(triArith[b]) * -1;
							triArithI[b] = precisionValueTo<T>(triArithI[b]) * -1;
							sig[b] = 0;
						}
					}
					else {
						if (isContained("det", op)) {
							startDetProcessing(pas);
							triArith[b] = resultR;
							triArithI[b] = resultI;
							if (op[0] == '_') {
								triArith[b] = precisionValueTo<T>(triArith[b]) * -1;
								triArithI[b] = precisionValueTo<T>(triArithI[b]) * -1;
								sig[b] = 0;
							}
						}
						else {
							if (isContained("strlen", op)) {
								triArith[b] = (T)strlength(pas);
								triArithI[b] = 0;
							}
							else {
								if (isContained("colsnum", op)) {
									triArith[b] = (T)colsNumber(pas);
									triArithI[b] = 0;
								}
								else {
									if (isContained("linsnum", op)) {
										triArith[b] = (T)linesNumber(pas);
										triArithI[b] = 0;
									}
									else {
										if (isContained("countoccurrences", op)) {
											if (countOccurrences("\\", arithTrig) == 1) {
												renamer(pas);
												sprintf(pas, "%s", expressionF);
												int p = 0, q = 0;
												char* string = getDynamicCharArray("", "string");
												char* to_find = getDynamicCharArray("", "to_find");
												while (pas[p] != '\\') {
													to_find[p] = pas[p];
													p++;
												}
												to_find[p] = '\0';
												renamer(to_find);
												sprintf(to_find, "%s", expressionF);
												p++;
												q = 0;
												while (p < abs((int)strlen(pas))) {
													string[q] = pas[p];
													p++; q++;
												}
												string[q] = '\0';
												renamer(string);
												sprintf(string, "%s", expressionF);
												stringVariableToString(to_find);
												sprintf(to_find, "%s", variableSTring);
												stringVariableToString(string);
												sprintf(string, "%s", variableSTring);
												triArith[b] = (T)countOccurrences(to_find, string);
												triArithI[b] = 0;
											}
											else {
												puts("\nError: Please use a \"\\\" to separate the variables.\n");
											}
										}
										else {
											if (isContained("calc", op)) {
												renamer(pas);
												sprintf(pas, "%s", expressionF);
												stringVariableToString(pas);
												sprintf(pas, "%s", variableSTring);
												calcNow<T>(pas, (T)0, (T)0);
												triArith[b] = resultR;
												triArithI[b] = resultI;;
											}
											else {
												if (isContained("getlins", op)) {
													getLines(pas);
													if (numVectorCols > 1 || numVectorLines > 1) {
														matrixMode = 1;
														signalVectors[b] = countVectors;
														sprintf(vectors[countVectors], "%s", matrixValue);
														countVectors++;
														triArith[b] = 1;
														triArithI[b] = 0;
													}
													else {
														triArith[b] = vectorR[0][0];
														triArithI[b] = vectorI[0][0];
														signalVectors[b] = -1;
														matrixMode = 0;
													}
												}
												else {
													if (isContained("getcols", op)) {
														getCols(pas);
														if (numVectorCols > 1 || numVectorLines > 1) {
															matrixMode = 1;
															signalVectors[b] = countVectors;
															sprintf(vectors[countVectors], "%s", matrixValue);
															countVectors++;
															triArith[b] = 1;
															triArithI[b] = 0;
														}
														else {
															triArith[b] = vectorR[0][0];
															triArithI[b] = vectorI[0][0];
															signalVectors[b] = -1;
															matrixMode = 0;
														}
													}
													else {

														check4Vector = 1;
														triArith[b] = initialProcessor(pas, result);
														triArithI[b] = resultI;
														if (abs((int)strlen(matrixResult)) > 0) {
															matrixMode = 1;
															signalVectors[b] = countVectors;
															sprintf(vectors[countVectors], "%s", matrixResult);
															countVectors++;
															triArith[b] = 1;
															triArithI[b] = 0;
															sprintf(matrixValue, "%s", matrixResult);
														}
														sprintf(expressionF, pas);
														sig[b] = 1;
														char* matrixArgument = getDynamicCharArray(pas, "matrixArgument");
														if (abs((int)strlen(op)) > 0) {
															if (isContained("avg", op)) {
																average(abs((int)strlen(matrixValue)) > 0 ? matrixValue : matrixArgument);
																triArith[b] = resultR;
																triArithI[b] = resultI;
																if (op[0] == '_') {
																	triArith[b] = precisionValueTo<T>(triArith[b]) * -1;
																	triArithI[b] = precisionValueTo<T>(triArithI[b]) * -1;
																	sig[b] = 0;
																}
																matrixMode = 0;
																sprintf(matrixValue, "");
																signalVectors[b] = -1;
															}
															else {
																if (isContained("max", op)) {
																	maximum(abs((int)strlen(matrixValue)) > 0 ? matrixValue : matrixArgument);
																	triArith[b] = resultR;
																	triArithI[b] = resultI;
																	if (op[0] == '_') {
																		triArith[b] = precisionValueTo<T>(triArith[b]) * -1;
																		triArithI[b] = precisionValueTo<T>(triArithI[b]) * -1;
																		sig[b] = 0;
																	}
																	matrixMode = 0;
																	sprintf(matrixValue, "");
																	signalVectors[b] = -1;
																}
																else {
																	if (isContained("min", op)) {
																		minimum(abs((int)strlen(matrixValue)) > 0 ? matrixValue : matrixArgument);
																		triArith[b] = resultR;
																		triArithI[b] = resultI;
																		if (op[0] == '_') {
																			triArith[b] = precisionValueTo<T>(triArith[b]) * -1;
																			triArithI[b] = precisionValueTo<T>(triArithI[b]) * -1;
																			sig[b] = 0;
																		}
																		matrixMode = 0;
																		sprintf(matrixValue, "");
																		signalVectors[b] = -1;
																	}
																	else {

																		PrecisionValue** vector1_R, ** vector1_I;
																		vector1_R = new PrecisionValue* [DIMTWOD];

																		for (int i = 0; i < DIMTWOD; ++i) {
																			vector1_R[i] = getDynamicDoubleArray();
																		}
																		vector1_I = new PrecisionValue* [DIMTWOD];

																		for (int i = 0; i < DIMTWOD; ++i) {
																			vector1_I[i] = getDynamicDoubleArray();
																		}

																		int numVectorCols1 = 0, numVectorLines1 = 0;
																		if (abs((int)strlen(matrixValue)) > 0) {
																			convert2Vector(matrixValue);
																			sprintf(matrixValue, "");
																			int n = 0;
																			int m = 0;
																			sprintf(saveFunc, "%s", op);
																			for (n = 0; n < numVectorLines; n++) {
																				for (m = 0; m < numVectorCols; m++) {
																					sprintf(op, "%s", saveFunc);
																					resultI = vectorI[n][m];
																					amplitude = 1;
																					vector1_R[n][m] = functionProcessor<T>(op, vectorR[n][m], amplitude, rf, "");
																					vector1_I[n][m] = precisionValueTo<T>(resultI);
																				}
																			}
																			numVectorCols1 = numVectorCols;
																			numVectorLines1 = numVectorLines;
																			sprintf(matrixResult, convertVector2String(vector1_R, vector1_I, numVectorLines1, numVectorCols1));
																			sprintf(vectors[countVectors - 1], "%s", matrixResult);
																		}
																		else {
																			resultI = triArithI[b];
																			triArith[b] = functionProcessor<T>(op, triArith[b], amplitude, rf, "");
																			triArithI[b] = resultI;
																		}

																		_Delete(vector1_R, DIMTWOD, dime, "vector1_R,DIMTWOD,dime");  // Delete the array of pointers

																		_Delete(vector1_I, DIMTWOD, dime, "vector1_I,DIMTWOD,dime");  // Delete the array of pointers

																	}
																}


															}
															if (thj == 1) { thj = 0; sig[b] = 0; }
															else {
																sig[b] = 1;
															}
															_delete(matrixArgument, "matrixArgument"); matrixArgument = nullptr;
															pas[0] = '\0';

															ju = 0;

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
				b++;
			}
			sprintf(op, "");
		}
		_delete(op, "op"); op = nullptr;
		arTrig[c] = '=';
	}

	int negFact = 0;
	for (s = 0; s < c; s++) {
		if (arTrig[s] == '!') {
			if (precisionValueTo<T>(triArith[s]) < 0.0) {
				negFact = 1;
			}
			while (arTrig[s] == '!') {
				triArith[s] = fact<T>(abs(precisionValueTo<T>(triArith[s])));
				while (s < c) {
					arTrig[s] = arTrig[s + 1];
					s++;
				}
				s = 0;
			}
			if (negFact == 1) {
				triArith[s] = precisionValueTo<T>(triArith[s])*-1;
			}
		}
	}
	a = 0;
	int fr;
	so = 0;
	int ca = 0;
	PrecisionValue asdf = 0, asdfI = 0;
	for (so = 0; so < c; so++) {
		int sa = so;

		int b = 0;
		if (arTrig[so] == '^' && arTrig[so + 1] == '^' && signalVectors[so + 1] == -1 && signalVectors[so] == -1) {
			while (arTrig[so] == '^' && a != 1) {
				if (arTrig[so + 1] != '^' && arTrig[so - 1] == '^' && a != 2) {
					asdf = triArith[so + 1];
					asdfI = triArithI[so + 1];
					if (sig[so] == -1) {
						if (precisionValueTo<T>(triArith[so]) < 0 || precisionValueTo<T>(triArithI[so]) < 0 && precisionValueTo<T>(triArith[so]) == 0) {
							sig[so] = 0;
						}
						else { sig[so] = 1; }
					}
					exponentiation<T>(precisionValueTo<T>(triArith[so]), precisionValueTo<T>(triArithI[so]), precisionValueTo<T>(asdf), precisionValueTo<T>(asdfI), sig[so]);
					asdf = precisionValueTo<T>(resultR);
					asdfI = precisionValueTo<T>(resultI);
					triArith[so + 1] = 1;
					triArith[so] = 1;
					triArithI[so + 1] = 0;
					triArithI[so] = 0;
					arTrig[so] = '*';
					so--;
					a = 2;
				}
				else {
					if (arTrig[so + 1] == '^' && a == 0) {
						so++;
						fr = so;
					}
					else {
						if (a == 2) {
							while (a != 1) {
								if (sig[so] == -1) {
									if (precisionValueTo<T>(triArith[so]) < 0 || (precisionValueTo<T>(triArithI[so]) < 0 && precisionValueTo<T>(triArith[so]) == 0)) {
										sig[so] = 0;
									}
									else { sig[so] = 1; }
								}
								exponentiation<T>(precisionValueTo<T>(triArith[so]), precisionValueTo<T>(triArithI[so]), precisionValueTo<T>(asdf), precisionValueTo<T>(asdfI), sig[so]);
								asdf = precisionValueTo<T>(resultR);
								asdfI = precisionValueTo<T>(resultI);
								triArith[so] = 1; triArithI[so] = 0;
								arTrig[so] = '*';
								so--;
								if (arTrig[so] != '^') {
									a = 1;
									so = fr++;
								}
							}
						}
					}
				}
				if (a == 1) {
					triArith[sa] = asdf; a = 0;
					triArithI[sa] = asdfI;
				}
			}
		}
		else {
			if (arTrig[so] == '^' && arTrig[so + 1] != '^' && signalVectors[so + 1] == -1 && signalVectors[so] == -1) {
				while (arTrig[so] == '^') {
					if (sig[sa] == -1) {
						if (precisionValueTo<T>(triArith[sa]) < 0 || (precisionValueTo<T>(triArithI[sa]) < 0 && precisionValueTo<T>(triArith[sa]) == 0)) {
							sig[sa] = 0;
						}
						else { sig[sa] = 1; }
					}
					exponentiation<T>(precisionValueTo<T>(triArith[sa]), precisionValueTo<T>(triArithI[sa]), precisionValueTo<T>(triArith[so + 1]), precisionValueTo<T>(triArithI[so + 1]), sig[sa]);
					triArith[sa] = resultR; triArithI[sa] = resultI;
					triArith[so + 1] = 1; triArithI[so + 1] = 0;
					arTrig[so] = '*';
					so = so + 1;
				}
			}
		}
	}

	int RF = 0;
	for (RF = 0; RF < c; RF++) {
		convertComplex2Exponential(triArith[RF], triArithI[RF]);
		if (precisionValueTo<T>(triArith[RF]) > 0 && precisionValueTo<T>(triArithI[RF]) < 0) {
			sprintf(simplified, "%s(%s%si)%c", simplified, respR, respI, arTrig[RF]);
		}
		else {
			if (precisionValueTo<T>(triArith[RF]) < 0 && precisionValueTo<T>(triArithI[RF]) > 0) {
				sprintf(simplified, "%s(%s+%si)%c", simplified, respR, respI, arTrig[RF]);
			}
			else {
				if (precisionValueTo<T>(triArith[RF]) < 0 && precisionValueTo<T>(triArithI[RF]) < 0) {
					sprintf(simplified, "%s(%s%si)%c", simplified, respR, respI, arTrig[RF]);
				}
				else {
					if (precisionValueTo<T>(triArith[RF]) == 0 && precisionValueTo<T>(triArithI[RF]) == 0) {
						sprintf(simplified, "%s%s%c", simplified, convert2Exponential(triArith[RF]), arTrig[RF]);
					}
					else {
						if (precisionValueTo<T>(triArith[RF]) == 0 && precisionValueTo<T>(triArithI[RF]) != 0) {
							sprintf(simplified, "%s%si%c", simplified, convert2Exponential(triArithI[RF]), arTrig[RF]);
						}
						else {
							if (precisionValueTo<T>(triArith[RF]) != 0 && precisionValueTo<T>(triArithI[RF]) == 0) {
								sprintf(simplified, "%s%s%c", simplified, convert2Exponential(triArith[RF]), arTrig[RF]);
							}
							else {
								sprintf(simplified, "%s(%s+%si)%c", simplified, respR, respI, arTrig[RF]);
							}
						}
					}
				}
			}
		}
	}
	rasf = abs((int)strlen(simplified));
	while (simplified[rasf - 1] == '+' && simplified[rasf] == '0') {
		rasf = rasf - 2;
		simplified[rasf] = '\0';
	}
	rasf = abs((int)strlen(simplified));
	if (simplified[rasf - 1] == '+') {
		simplified[rasf - 1] = '\0';
	}
	if (verbose == 1 && solving) {
		printf("\nSimplified expression by initialProcessor: %s\n\n", verboseDisplayExpression(simplified).c_str());
	}

	if (countVectors > 0 || matrixMode == 1) {
		ensureMatrixScratch();
	}

	for (so = 0; so < c; so++) {
		if (arTrig[so] == '^') {
			if (signalVectors[so + 1] == -1 && signalVectors[so] != -1) {
				convert2Vector(vectors[signalVectors[so]]);
				if (((int)precisionValueTo<T>(triArith[so + 1]) >= 0 || (int)precisionValueTo<T>(triArith[so + 1]) < -1) && (int)precisionValueTo<T>(triArith[so + 1]) != -7654321 && (int)precisionValueTo<T>(triArith[so + 1]) != -1234567) {
					fmpowerm(vectorR, vectorI, res_vectorR, res_vectorI, (int)precisionValueTo<T>(triArith[so + 1]), numVectorLines, numVectorCols);
				}
				if ((int)precisionValueTo<T>(triArith[so + 1]) == -7654321) {
					fmtranspose(numVectorLines, numVectorCols, vectorR, vectorI, res_vectorR, res_vectorI);
					int savenumVectorCols = numVectorCols;
					numVectorCols = numVectorLines;
					numVectorLines = savenumVectorCols;
				}
				if ((int)precisionValueTo<T>(triArith[so + 1] )== -1) {
					fminverse(numVectorLines, numVectorCols, vectorR, vectorI, res_vectorR, res_vectorI);
				}
				if ((int)precisionValueTo<T>(triArith[so + 1]) == -1234567) {
					convert2Vector(vectors[signalVectors[so]]);
					int n = 0;
					int m = 0;
					for (n = 0; n < numVectorLines; n++) {
						for (m = 0; m < numVectorCols; m++) {
							vector1_R[n][m] = vectorR[n][m];
							vector1_I[n][m] = vectorI[n][m];
						}
					}
					numVectorCols1 = numVectorCols;
					numVectorLines1 = numVectorLines;
					signalVectors[so] = -1;
					signalVectors[so + 1] = -1;
					triArithI[so] = 0;
					triArith[so] = (T)fmrank(numVectorLines1, numVectorCols1, vector1_R, vector1_I);
					triArithI[so + 1] = 0;
					triArith[so + 1] = 1;
					arTrig[so] = '*';
				}
				else {
					triArith[so] = 1; triArithI[so] = 0;
					signalVectors[so] = -1;
					countVectors++;
					sprintf(vectors[countVectors], "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines, numVectorCols));
					signalVectors[so + 1] = countVectors;
					countVectors++;
					arTrig[so] = '*';
				}
			}
		}
	}

	for (so = 0; so < c; so++) {
		int sa = so;
		if (signalVectors[sa] != -1) {
			convert2Vector(vectors[signalVectors[sa]]);
			int n = 0;
			int m = 0;
			for (n = 0; n < numVectorLines; n++) {
				for (m = 0; m < numVectorCols; m++) {
					vector1_R[n][m] = vectorR[n][m];
					vector1_I[n][m] = vectorI[n][m];
				}
			}
			numVectorCols1 = numVectorCols;
			numVectorLines1 = numVectorLines;
			countVectors++;
			signalVectors[sa] = countVectors;
			sprintf(vectors[countVectors], "%s", convertVector2String(vector1_R, vector1_I, numVectorLines1, numVectorCols1));
			countVectors++;
		}
		while (arTrig[so] == '/') {
			if (signalVectors[so + 1] == -1 && signalVectors[sa] != -1) {
				convert2Vector(vectors[signalVectors[sa]]);
				division<T>(1.0, 0.0, precisionValueTo<T>(triArith[so + 1]), precisionValueTo<T>(triArithI[so + 1]));
				fmmulr(numVectorLines1, numVectorCols1, vector1_R, res_vectorR, resultR, vector1_I, res_vectorI, resultI);
				countVectors++;
				signalVectors[sa] = countVectors;
				sprintf(vectors[countVectors], "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
				countVectors++;
				triArith[so + 1] = 1; triArithI[so + 1] = 0;
				signalVectors[so + 1] = -1;
				arTrig[so] = '*';
			}
			else {
				if (signalVectors[so + 1] == -1 && signalVectors[sa] == -1) {
					division(triArith[sa], triArithI[sa], triArith[so + 1], triArithI[so + 1]);
					triArith[sa] = resultR; triArithI[sa] = resultI;
					triArith[so + 1] = 1; triArithI[so + 1] = 0;
					arTrig[so] = '*';
				}
				else {
					if (signalVectors[so + 1] != -1 && signalVectors[sa] != -1) {
						convert2Vector(vectors[signalVectors[sa]]);
						int n = 0;
						int m = 0;
						for (n = 0; n < numVectorLines; n++) {
							for (m = 0; m < numVectorCols; m++) {
								vector1_R[n][m] = vectorR[n][m];
								vector1_I[n][m] = vectorI[n][m];
							}
						}
						numVectorCols1 = numVectorCols;
						numVectorLines1 = numVectorLines;
						convert2Vector(vectors[signalVectors[so + 1]]);
						if (fmdivm(numVectorLines, numVectorCols1, numVectorLines1, numVectorCols, vector1_R, vectorR, vector1_I, vectorI)) {
							triArith[sa] = resultR; triArithI[sa] = resultI;
							triArith[so + 1] = 1; triArithI[so + 1] = 0;
							signalVectors[so + 1] = -1;
							signalVectors[sa] = -1;
							arTrig[so] = '*';
						}
						else {
							printf("\nError: The quotient of matrices is not consistent over all matrices members.");
						}
					}
				}
			}
			so++;
		}
	}

	for (so = 0; so < c; so++) {
		int sa = so;
		if (signalVectors[sa] != -1) {
			convert2Vector(vectors[signalVectors[sa]]);
			int n = 0;
			int m = 0;
			for (n = 0; n < numVectorLines; n++) {
				for (m = 0; m < numVectorCols; m++) {
					vector1_R[n][m] = vectorR[n][m];
					vector1_I[n][m] = vectorI[n][m];
				}
			}
			numVectorCols1 = numVectorCols;
			numVectorLines1 = numVectorLines;
			countVectors++;
			signalVectors[sa] = countVectors;
			sprintf(vectors[countVectors], "%s", convertVector2String(vector1_R, vector1_I, numVectorLines1, numVectorCols1));
			countVectors++;

		}
		while (arTrig[so] == '*') {
			if (signalVectors[so + 1] != -1 && signalVectors[sa] != -1) {
				convert2Vector(vectors[signalVectors[sa]]);
				int n = 0;
				int m = 0;
				for (n = 0; n < numVectorLines; n++) {
					for (m = 0; m < numVectorCols; m++) {
						vector1_R[n][m] = vectorR[n][m];
						vector1_I[n][m] = vectorI[n][m];
					}
				}
				numVectorCols1 = numVectorCols;
				numVectorLines1 = numVectorLines;
				convert2Vector(vectors[signalVectors[so + 1]]);
				fmmulm(numVectorLines, numVectorCols1, numVectorLines1, numVectorCols, vector1_R, vectorR, res_vectorR, vector1_I, vectorI, res_vectorI);
				countVectors++;
				signalVectors[sa] = countVectors;
				sprintf(vectors[countVectors], "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
				countVectors++;
				triArith[so + 1] = 1;
				triArithI[so + 1] = 0;
				signalVectors[so + 1] = -1;
				arTrig[so] = '*';

			}
			else {
				if (signalVectors[so + 1] != -1 && signalVectors[sa] == -1) {
					convert2Vector(vectors[signalVectors[so + 1]]);
					fmmulr(numVectorLines, numVectorCols, vectorR, res_vectorR, triArith[sa], vectorI, res_vectorI, triArithI[sa]);
					countVectors++;
					signalVectors[sa] = countVectors;
					sprintf(vectors[countVectors], "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
					countVectors++;
					triArith[so + 1] = 1;
					triArithI[so + 1] = 0;
					signalVectors[so + 1] = -1;
					arTrig[so] = '*';
				}
				else {
					if (signalVectors[so + 1] == -1 && signalVectors[sa] != -1) {
						convert2Vector(vectors[signalVectors[sa]]);
						fmmulr(numVectorLines, numVectorCols, vectorR, res_vectorR, triArith[so + 1], vectorI, res_vectorI, triArithI[so + 1]);
						countVectors++;
						signalVectors[sa] = countVectors;
						sprintf(vectors[countVectors], "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
						countVectors++;
						triArith[so + 1] = 1;
						triArithI[so + 1] = 0;
						signalVectors[so + 1] = -1;
						arTrig[so] = '*';
					}
					else {

						if (signalVectors[so + 1] == -1 && signalVectors[sa] == -1) {
							multiplication(triArith[sa], triArithI[sa], triArith[so + 1], triArithI[so + 1]);
							triArith[sa] = resultR; triArithI[sa] = resultI;
							triArith[so + 1] = 1; triArithI[so + 1] = 0;
							arTrig[so] = '*';
						}
					}
				}
			}
			so++;
		}
	}

	int lo = 0;
	result1 = 0;
	result2 = 0;
	T resRank = 0;
	for (j = 0; j < c; j++) {
		if (j == 0) {
			if (signalVectors[0] != -1) {
				convert2Vector(vectors[signalVectors[0]]);
				int n = 0;
				int m = 0;
				for (n = 0; n < numVectorLines; n++) {
					for (m = 0; m < numVectorCols; m++) {
						vector1_R[n][m] = vectorR[n][m];
						vector1_I[n][m] = vectorI[n][m];
					}
				}
				numVectorCols1 = numVectorCols;
				numVectorLines1 = numVectorLines;
				countVectors++;
				signalVectors[0] = countVectors;
				sprintf(vectors[countVectors], "%s", convertVector2String(vector1_R, vector1_I, numVectorLines1, numVectorCols1));
				countVectors++;
				sprintf(matrixResult, "%s", convertVector2String(vector1_R, vector1_I, numVectorLines1, numVectorCols1));
			}
			else {

				result1 = precisionValueTo<T>(triArith[0]);
				result2 = precisionValueTo<T>(triArithI[0]);
			}
		}
		if (arTrig[j] == '^') {
			if (signalVectors[j + 1] == -1 && signalVectors[j] != -1) {
				convert2Vector(vectors[signalVectors[j]]);
				int val = (int)precisionValueTo<T>(triArith[j + 1]);

				if ((val >= 0 || val < -1) && val != -7654321 && val != -1234567) {

					if(higherPrecision== 1) {
						fmpowerm(vectorR, vectorI, res_vectorR, res_vectorI, (int)precisionValueTo<double>(triArith[j + 1]), numVectorLines, numVectorCols);
					}
					else {
						fmpowerm(vectorR, vectorI, res_vectorR, res_vectorI, (int)precisionValueTo<mp_float>(triArith[j + 1]), numVectorLines, numVectorCols);
					}
				}
				if ((int)precisionValueTo<T>(triArith[j + 1]) == -7654321) {
					fmtranspose(numVectorLines, numVectorCols, vectorR, vectorI, res_vectorR, res_vectorI);
					int savenumVectorCols = numVectorCols;
					numVectorCols = numVectorLines;
					numVectorLines = savenumVectorCols;
				}
				if ((int)precisionValueTo<T>(triArith[j + 1]) == -1) {
					fminverse(numVectorLines, numVectorCols, vectorR, vectorI, res_vectorR, res_vectorI);
				}
				if ((int)precisionValueTo<T>(triArith[j + 1]) == -1234567) {
					convert2Vector(vectors[signalVectors[j]]);
					int n = 0;
					int m = 0;
					for (n = 0; n < numVectorLines; n++) {
						for (m = 0; m < numVectorCols; m++) {
							vector1_R[n][m] = vectorR[n][m];
							vector1_I[n][m] = vectorI[n][m];
						}
					}
					numVectorCols1 = numVectorCols;
					numVectorLines1 = numVectorLines;
					signalVectors[j] = -1;
					signalVectors[j + 1] = -1;
					triArithI[j] = 0;
					triArith[j] = 0;
					triArith[j + 1] = 0;
					triArithI[j + 1] = 0;
					resRank = resRank + (T)fmrank(numVectorLines1, numVectorCols1, vector1_R, vector1_I);
				}
				else {
					countVectors++;
					signalVectors[j] = countVectors;
					sprintf(vectors[countVectors], "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines, numVectorCols));
					countVectors++;
					triArith[j + 1] = 1;
					triArithI[j + 1] = 0;
					signalVectors[j + 1] = -1;
					arTrig[j] = '*';
					sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines, numVectorCols));

				}
			}
			else {
				exponentiation<T>(result1, result2, precisionValueTo<T>(triArith[j + 1]), precisionValueTo<T>(triArithI[j + 1]), 1);
				result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
			}
		}
		if (arTrig[j] == '*') {
			if (signalVectors[j + 1] != -1 && signalVectors[j] != -1) {
				convert2Vector(matrixResult);
				int n = 0;
				int m = 0;
				for (n = 0; n < numVectorLines; n++) {
					for (m = 0; m < numVectorCols; m++) {
						vector1_R[n][m] = vectorR[n][m];
						vector1_I[n][m] = vectorI[n][m];
					}
				}
				numVectorCols1 = numVectorCols;
				numVectorLines1 = numVectorLines;
				convert2Vector(vectors[signalVectors[j + 1]]);
				fmmulm(numVectorLines, numVectorCols1, numVectorLines1, numVectorCols, vector1_R, vectorR, res_vectorR, vector1_I, vectorI, res_vectorI);
				countVectors++;
				signalVectors[j + 1] = countVectors;
				sprintf(vectors[countVectors], "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
				countVectors++;
				triArith[j] = 1;
				triArithI[j] = 0;
				signalVectors[j] = -1;
				sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));

			}
			else {
				if (signalVectors[j + 1] != -1 && signalVectors[j] == -1) {
					convert2Vector(vectors[signalVectors[j + 1]]);
					fmmulr(numVectorLines, numVectorCols, vectorR, res_vectorR, triArith[j], vectorI, res_vectorI, triArithI[j]);
					countVectors++;
					signalVectors[j + 1] = countVectors;
					sprintf(vectors[countVectors], "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
					countVectors++;
					triArith[j] = 1;
					triArithI[j] = 0;
					signalVectors[j] = -1;
					arTrig[j] = '*';
					sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
				}
				else {
					if (signalVectors[j + 1] == -1 && signalVectors[j] != -1) {
						convert2Vector(vectors[signalVectors[j]]);

						fmmulr(numVectorLines, numVectorCols, vectorR, res_vectorR, triArith[j + 1], vectorI, res_vectorI, triArithI[j + 1]);
						countVectors++;
						signalVectors[j + 1] = countVectors;
						sprintf(vectors[countVectors], "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
						countVectors++;
						triArith[j] = 1;
						triArithI[j] = 0;
						signalVectors[j] = -1;
						arTrig[j] = '*';
						sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
					}
					else {
						multiplication<T>(result1, result2, precisionValueTo<T>(triArith[j + 1]), precisionValueTo<T>(triArithI[j + 1]));
						result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
					}
				}
			}
		}
		if (arTrig[j] == '/') {
			if (signalVectors[j + 1] == -1 && signalVectors[j] != -1) {
				convert2Vector(matrixResult);
				division<T>(1.0, 0.0, precisionValueTo<T>(triArith[j + 1]), precisionValueTo<T>(triArithI[j + 1]));
				fmmulr(numVectorLines, numVectorCols, vector1_R, res_vectorR, resultR, vector1_I, res_vectorI, resultI);
				countVectors++;
				signalVectors[j + 1] = countVectors;
				sprintf(vectors[countVectors], "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
				countVectors++;
				triArith[j] = 1;
				triArithI[j] = 0;
				signalVectors[j] = -1;
				arTrig[j] = '*';
				sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
			}
			else {
				if (signalVectors[j + 1] != -1 && signalVectors[j] != -1) {
					convert2Vector(vectors[signalVectors[j]]);
					int n = 0;
					int m = 0;
					for (n = 0; n < numVectorLines; n++) {
						for (m = 0; m < numVectorCols; m++) {
							vector1_R[n][m] = vectorR[n][m];
							vector1_I[n][m] = vectorI[n][m];
						}
					}
					numVectorCols1 = numVectorCols;
					numVectorLines1 = numVectorLines;
					convert2Vector(vectors[signalVectors[j + 1]]);
					if (fmdivm(numVectorLines, numVectorCols1, numVectorLines1, numVectorCols, vector1_R, vectorR, vector1_I, vectorI)) {
						triArith[j] = resultR; triArithI[j] = resultI;
						signalVectors[j + 1] = -1;
						signalVectors[j] = -1;
						result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
					}
					else {
						printf("\nError: The quotient of matrices is not consistent over all matrices members.");
					}
				}
				else {
					division<T>(result1, result2, precisionValueTo<T>(triArith[j + 1]), precisionValueTo<T>(triArithI[j + 1]));
					result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
				}
			}
		}
		if (arTrig[j] == '-') {
			if (signalVectors[j + 1] != -1 && signalVectors[j] != -1) {
				convert2Vector(matrixResult);
				int n = 0;
				int m = 0;
				for (n = 0; n < numVectorLines; n++) {
					for (m = 0; m < numVectorCols; m++) {
						vector1_R[n][m] = vectorR[n][m];
						vector1_I[n][m] = vectorI[n][m];
					}
				}
				numVectorCols1 = numVectorCols;
				numVectorLines1 = numVectorLines;
				convert2Vector(vectors[signalVectors[j + 1]]);
				fmsubt(numVectorLines, numVectorCols, vector1_R, vectorR, res_vectorR, vector1_I, vectorI, res_vectorI);
				countVectors++;
				signalVectors[j + 1] = countVectors;
				sprintf(vectors[countVectors], "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
				countVectors++;
				signalVectors[j] = -1;
				sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));

			}
			else {
				subtraction<T>(result1, result2, precisionValueTo<T>(triArith[j + 1]), precisionValueTo<T>(triArithI[j + 1]));
				result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
			}
		}
		if (arTrig[j] == '+') {
			if (signalVectors[j + 1] != -1 && signalVectors[j] != -1) {
				convert2Vector(matrixResult);
				int n = 0;
				int m = 0;
				for (n = 0; n < numVectorLines; n++) {
					for (m = 0; m < numVectorCols; m++) {
						vector1_R[n][m] = vectorR[n][m];
						vector1_I[n][m] = vectorI[n][m];
					}
				}
				numVectorCols1 = numVectorCols;
				numVectorLines1 = numVectorLines;
				convert2Vector(vectors[signalVectors[j + 1]]);
				fmsum(numVectorLines, numVectorCols, vector1_R, vectorR, res_vectorR, vector1_I, vectorI, res_vectorI);
				countVectors++;
				signalVectors[j + 1] = countVectors;
				sprintf(vectors[countVectors], "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
				countVectors++;
				signalVectors[j] = -1;
				triArith[j] = 1;
				triArithI[j] = 0;
				sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
			}
			if (signalVectors[j + 1] != -1 && signalVectors[j] == -1) {
				convert2Vector(vectors[signalVectors[j + 1]]);
				signalVectors[j + 1] = countVectors;
				sprintf(vectors[countVectors], "%s", convertVector2String(vectorR, vectorI, numVectorLines, numVectorCols));
				countVectors++;
				triArith[j] = 1;
				triArithI[j] = 0;
				signalVectors[j] = -1;
				arTrig[j] = '*';
				sprintf(matrixResult, "%s", convertVector2String(vectorR, vectorI, numVectorLines, numVectorCols));
			}
			else {
				if (signalVectors[j + 1] == -1 && signalVectors[j] != -1) {
					convert2Vector(vectors[signalVectors[j]]);
					countVectors++;
					signalVectors[j + 1] = countVectors;
					sprintf(vectors[countVectors], "%s", convertVector2String(vectorR, vectorI, numVectorLines, numVectorCols));
					countVectors++;
					triArith[j] = 1;
					triArithI[j] = 0;
					signalVectors[j] = -1;
					arTrig[j] = '*';
					sprintf(matrixResult, "%s", convertVector2String(vectorR, vectorI, numVectorLines, numVectorCols));
				}
				else {
					sum<T>(result1, result2, precisionValueTo<T>(triArith[j + 1]), precisionValueTo<T>(triArithI[j + 1]));
					result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
				}
			}
		}
	}

	resultR = result1;
	resultI = result2;
	result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);

	_Delete(vector1_R, DIMTWOD, dime, "vector1_R,DIMTWOD,dime");

	_Delete(vector1_I, DIMTWOD, dime, "vector1_I,DIMTWOD,dime");

	_Delete(res_vectorR, DIMTWOD, dime, "res_vectorR,DIMTWOD,dime");

	_Delete(res_vectorI, DIMTWOD, dime, "res_vectorI,DIMTWOD,dime");
	_delete(triArith, "triArith"); triArith = nullptr;
	_delete(triArithI, "triArithI"); triArithI = nullptr;
	_delete(arTrig, "arTrig"); arTrig = nullptr;
	_delete(paRect, "paRect"); paRect = nullptr;
	_delete(trig, "trig"); trig = nullptr;
	sprintf(cN, "");
	if (cN != nullptr && strlen(cN) >= 0) {
		_delete(cN, "cN"); cN = nullptr;
	}
	_delete(paTrig, "paTrig"); paTrig = nullptr;
	_delete(pas, "pas"); pas = nullptr;
	_delete(func, "func"); func = nullptr;
	_delete(trigon, "trigon"); trigon = nullptr;
	_delete(ex, "ex"); ex = nullptr;
	_delete(simplified, "simplified"); simplified = nullptr;
	_delete(saveFunc, "saveFunc"); saveFunc = nullptr;
	_Delete(vectors, DIMTWOD, DIMDOUBLE, "vectors[w]");
	_delete(signalVectors, "signalVectors"); signalVectors = nullptr;
	_delete(parent, "parent"); parent = nullptr;
	_delete(sig, "sig"); sig = nullptr;
	return result1;
}
template<typename T>
T arithSolver(char* trigon1, T result) {

	if (isEqual("0", trigon1)) {
		resultR = 0;
		resultI = 0;
		return 0;
	}
	if (!runningScript && matrixMode == 1 && isEqual("T", trigon1)) {
		resultR = -7654321;
		resultI = 0;
		return -7654321;
	}
	if (!runningScript && matrixMode == 1 && isEqual("R", trigon1)) {
		resultR = -1234567;
		resultI = 0;
		return -1234567;
	}
	int rasf = abs((int)strlen(trigon1));

	if (verbose == 1 && solving) {
		printf("\n\n==> arithSolver <==\n\nExpression: %s\n", verboseDisplayExpression(trigon1).c_str());
	}
	resultR = 0; resultI = 0;
	int i = 0, negImag = 0, j = 0, e = 0, f = 0, h = 0, so = 0, sa = 0, n = 0, c = 0, *sig = getDynamicIntArray(), sign = 0, s = 0, facto = 0, y = 0, sif = 0, res = 0, v = 0;
	char* number2 = getDynamicCharArray("", "number2"); char* ex = getDynamicCharArray("", "ex"); char* trigon = getDynamicCharArray("", "trigon");
	char* amp = getDynamicCharArray("", "amp"); char* prefCalc = getDynamicCharArray("", "prefCalc");
	T exp = 1, result1 = T(0), result2 = T(0), fa = T(0);
	PrecisionValue* ampl = getDynamicDoubleArray(), * amplI = getDynamicDoubleArray();
	for (i = 0; i < abs((int)strlen(trigon1)); i++) {
		ampl[i] = 0; amplI[i] = 0;
	}
	if (trigon1[i - 1] != '=') {
		trigon1[i] = '='; trigon1[i + 1] = '\0';
	}
	i = 0;
	for (i = 0; i < abs((int)strlen(trigon1)); i++) {
		if (trigon1[i] == '-' && (trigon1[i - 1] == 'B' || trigon1[i - 1] == 'O' || trigon1[i - 1] == 'H') && (trigon1[i - 2] == '_' || trigon1[i - 2] == '+' || trigon1[i - 2] == '-' || trigon1[i - 2] == '*' || trigon1[i - 2] == '/' || trigon1[i - 2] == '^' || i - 1 == 0)) {
			trigon1[i] = '_';
		}
	}
	int si = 0;
	j = 0;
	for (i = 0; i < abs((int)strlen(trigon1)); i++) {
		if (trigon1[i] != '*' && trigon1[i] != '+' && trigon1[i] != '-' && trigon1[i] != '/' && trigon1[i] != '^' && trigon1[i] != '=') {
			if (trigon1[i] == '_') {
				number2[j] = trigon1[i];
				j++; i++;
			}
			if ((trigon1[i] == 'B' || trigon1[i] == 'O' || trigon1[i] == 'H') && trigon1[i + 1] == '-') {
				number2[j] = trigon1[i];
				j++; i++;
				number2[j] = trigon1[i];
				j++; i++;
				number2[j] = trigon1[i];
				j++; i++;
				while (trigon1[i] != '*' && trigon1[i] != '+' && trigon1[i] != '-' && trigon1[i] != '/' && trigon1[i] != '^' && trigon1[i] != '=') {
					number2[j] = trigon1[i];
					j++; i++;
				}
				number2[j] = '\0';
			}
			while (trigon1[i] != '*' && trigon1[i] != '+' && trigon1[i] != '-' && trigon1[i] != '/' && trigon1[i] != '^' && trigon1[i] != '=') {
				if (((trigon1[i] == 'B' || trigon1[i] == 'O' || trigon1[i] == 'H') && trigon1[i + 1] != '-' && trigon1[i + 1] != '+' && trigon1[i + 1] != '*' && trigon1[i + 1] != '/' && trigon1[i + 1] != '^' && trigon1[i + 1] != '=') || (trigon1[i] == 'E' && trigon1[i + 1] != '=')) {
					number2[j] = trigon1[i];
					number2[j + 1] = trigon1[i + 1];
					j = j + 2; i = i + 2;
					while (trigon1[i] != '*' && trigon1[i] != '+' && trigon1[i] != '-' && trigon1[i] != '/' && trigon1[i] != '^' && trigon1[i] != '=') {
						if (trigon1[i] == '=') { number2[j] = '\0'; j++; i++; sif = 1; }
						number2[j] = trigon1[i];
						j++; i++;
					}
				}
				else {
					number2[j] = trigon1[i];
					j++; i++;
				}
			}
			i--;
			if (sif == 0 && !isContained("[", number2)) {
				number2[j] = '.';
				number2[j + 1] = '0';
				number2[j + 2] = '\0';
			}
		}
		if (isContained("][", number2)) {
			if (isContained("[", number2)) {
				char* variable = getDynamicCharArray("", "variable");
				int p = strStart + 1, m = 0;
				if (p > 1) {
					if (p - 2 > 0 && verifyLetter(number2[p - 2])) {
						int k = p - 2;
						while (k > 0 && verifyLetter(number2[k])) {
							k--;
						}

						int v = 0;
						while (number2[k] != '[') {
							variable[v] = number2[k];
							k++; v++;
						}
						variable[v] = '\0';
						checkMatrixIndex = true;
						processVariable<T>(variable);
						checkMatrixIndex = false;

					}
				}
				char* firstInt = getDynamicCharArray("", "firstInt"); char* secondInt = getDynamicCharArray("", "secondInt");
				while (number2[p] != ']' && p < abs((int)strlen(number2))) {
					firstInt[m] = number2[p];
					m++; p++;
				}
				firstInt[m] = '\0';
				p += 2; m = 0;
				while (number2[p] != ']' && p < abs((int)strlen(number2))) {
					secondInt[m] = number2[p];
					m++; p++;
				}
				secondInt[m] = '\0';


				int indexIF = (int)calcNow<T>(firstInt, (T)0, (T)0);

				int indexJF = (int)calcNow<T>(secondInt, (T)0, (T)0);
				processVariable<T>(variable);
				ampl[n] = precisionValueTo<T>(vectorR[indexIF][indexJF]);
				amplI[n] = precisionValueTo<T>(vectorI[indexIF][indexJF]);
				check4Vector = 0;
				_delete(firstInt, "firstInt");
				_delete(secondInt, "secondInt");
				_delete(variable, "variable"); variable = nullptr;
			}
		}
		else {
			if (isContained("[", number2)) {
				char* variable = getDynamicCharArray("", "variable");
				int p = strStart + 1, m = 0;
				if (p > 1) {
					if (p - 2 > 0 && verifyLetter(number2[p - 2])) {
						int k = p - 2;
						while (k > 0 && verifyLetter(number2[k])) {
							k--;
						}

						int v = 0;
						while (number2[k] != '[') {
							variable[v] = number2[k];
							k++; v++;
						}
						variable[v] = '\0';
						checkMatrixIndex = true;
						processVariable<T>(variable);
						checkMatrixIndex = false;
					}
				}
				char* firstInt = getDynamicCharArray("", "firstInt"); char* secondInt = getDynamicCharArray("", "secondInt");
				while (number2[p] != ']' && p < abs((int)strlen(number2))) {
					firstInt[m] = number2[p];
					m++; p++;
				}
				firstInt[m] = '\0';


				int indexIF = (int)calcNow<T>(firstInt, (T)0, (T)0);

				int indexJF = -1;
				processVariable<T>(variable);
				check4Vector = 0;
				ampl[n] = precisionValueTo<T>(vectorR[0][indexIF]);
				amplI[n] = precisionValueTo<T>(vectorI[0][indexIF]);


				_delete(firstInt, "firstInt"); firstInt = nullptr;
				_delete(variable, "variable"); variable = nullptr;

			}
			else {
				int complex = 0;
				if (number2[0] == 'i') {
					complex = 1;
					for (y = 0; number2[y + 1] != '\0'; y++) {
						number2[y] = number2[y + 1];
					}
					number2[y] = '\0';
				}
				if (number2[0] == '_' && number2[1] == 'i' && number2[2] == '1') {
					complex = 1;
					for (y = 0; number2[y + 1] != '\0'; y++) {
						number2[y] = number2[y + 1];
					}
					number2[y] = '\0';
					negImag = 1;
				}
				if (number2[abs((int)strlen(number2)) - 4] != 'p' && number2[abs((int)strlen(number2)) - 3] == 'i') {
					complex = 1;
					for (y = abs((int)strlen(number2)) - 3; number2[y + 1] != '\0'; y++) {
						number2[y] = number2[y + 1];
					}
					number2[y] = '\0';
				}
				for (y = 0; y < abs((int)strlen(number2)); y++) {
					if (number2[y] == '=') {
						number2[y] = '\0';
						break;
					}
				}
				for (y = 0; y < abs((int)strlen(number2)); y++) {
					if (number2[y] == '!') {
						facto++;
					}
				}
				if (facto > 0) {
					y = 0;
					while (number2[y] != '!') {
						y++;
					}
					number2[y] = '.'; number2[y + 1] = '0'; number2[y + 2] = '\0';
				}
				v = 0;
				for (j = 0; j < abs((int)strlen(number2)); j++) {
					if (number2[j] == 'P') {
						y = j;
						while (number2[j] != '.') {
							prefCalc[v] = number2[j];
							v++; j++;
						}
						prefCalc[v] = '\0';
						number2[y] = '.'; number2[y + 1] = '0'; number2[y + 2] = '\0';
					}
				}
				if (number2[0] == '#') {
					res = 1;
					for (y = 0; number2[y + 1] != '\0' && number2[y + 1] != 'E'; y++) {
						number2[y] = number2[y + 1];
					}
					number2[y] = '\0';
					ampl[n] =convertToNumber<T>(number2);
					amplI[n] = convertToNumber<T>(number2);
					if (strlen(ansMatrices[(int)(precisionValueTo<T>(ampl[n]))]) == 0) {
						ampl[n] = ans[(int)(precisionValueTo<T>(ampl[n]))];
						amplI[n] = ansI[(int)(precisionValueTo<T>(amplI[n]))];
						complex = 2;
						y++;
						if (number2[y] == 'E') {
							number2[0] = '1';
							j = 1;
							while (y < abs((int)strlen(number2))) {
								number2[j] = number2[y];
								j++; y++;
							}
							number2[j] = '\0';
							T atual = precisionValueTo<T>(ampl[n]);
							T fator = convertToNumber<T>(number2); 

							ampl[n] = atual * fator;
						}
						number2[0] = '\0';
					}
					else {

						convert2Vector(ansMatrices[(int)(precisionValueTo<T>(ampl[n]))]);
						y = y + 2;
						if (number2[y] == 'E') {
							number2[0] = '1';
							j = 1;
							while (y < abs((int)strlen(number2))) {
								number2[j] = number2[y];
								j++; y++;
							}
							number2[j] = '\0';
							T expValue = convertToNumber<T>(number2);
							PrecisionValue** res_vectorR, ** res_vectorI;
							res_vectorR = new PrecisionValue* [DIMTWOD];

							for (int i = 0; i < DIMTWOD; ++i) {
								res_vectorR[i] = getDynamicDoubleArray();
							}
							res_vectorI = new PrecisionValue* [DIMTWOD];

							for (int i = 0; i < DIMTWOD; ++i) {
								res_vectorI[i] = getDynamicDoubleArray();
							}
							char* answerString = getDynamicCharArray("", "answerString");
							fmmulr(numVectorLines, numVectorCols, vectorR, res_vectorR, expValue, vectorI, res_vectorI, 0.0);
							sprintf(answerString, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines, numVectorCols));
							convert2Vector(answerString);


							_Delete(res_vectorR, DIMTWOD, dime, "res_vectorR,DIMTWOD,dime");
							_Delete(res_vectorI, DIMTWOD, dime, "res_vectorI,DIMTWOD,dime");
							_delete(answerString, "answerString"); answerString = nullptr;

						}
						number2[0] = '\0';
						check4Vector = 2;
					}
				}

				if (number2[0] == '_' && number2[1] == '#') {
					res = 1;
					for (y = 0; number2[y + 2] != '\0' && number2[y + 2] != 'E'; y++) {
						number2[y] = number2[y + 2];
					}
					number2[y] = '\0';
					ampl[n] = convertToNumber<T>(number2);
					amplI[n] = convertToNumber<T>(number2);
					if (strlen(ansMatrices[(int)precisionValueTo<T>(ampl[n])]) == 0) {
						ampl[n] = precisionValueTo<T>(ans[(int)(precisionValueTo<T>(ampl[n]))]) * -1;
						amplI[n] = precisionValueTo<T>(ansI[(int)(precisionValueTo<T>(amplI[n]))]) * -1;
						y = y + 2;
						if (number2[y] == 'E') {
							number2[0] = '1';
							j = 1;
							while (y < abs((int)strlen(number2))) {
								number2[j] = number2[y];
								j++; y++;
							}
							number2[j] = '\0';
							ampl[n] = precisionValueTo<T>(ampl[n]) * convertToNumber<T>(number2);
						}
						number2[0] = '\0';
					}
					else {

						convert2Vector(ansMatrices[(int)precisionValueTo<T>(ampl[n])]);
						PrecisionValue** res_vectorR, ** res_vectorI;
						res_vectorR = new PrecisionValue* [DIMTWOD];

						for (int i = 0; i < DIMTWOD; ++i) {
							res_vectorR[i] = getDynamicDoubleArray();
						}
						res_vectorI = new PrecisionValue* [DIMTWOD];

						for (int i = 0; i < DIMTWOD; ++i) {
							res_vectorI[i] = getDynamicDoubleArray();
						}
						char* answerString = getDynamicCharArray("", "answerString");
						fmmulr(numVectorLines, numVectorCols, vectorR, res_vectorR, -1.0, vectorI, res_vectorI, 0.0);
						sprintf(answerString, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines, numVectorCols));
						convert2Vector(answerString);
						check4Vector = 2;
						y = y + 2;
						if (number2[y] == 'E') {
							number2[0] = '1';
							j = 1;
							while (y < abs((int)strlen(number2))) {
								number2[j] = number2[y];
								j++; y++;
							}
							number2[j] = '\0';
							T expValue = convertToNumber<T>(number2);
							fmmulr(numVectorLines, numVectorCols, vectorR, res_vectorR, expValue, vectorI, res_vectorI, 0.0);
							sprintf(answerString, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines, numVectorCols));
							convert2Vector(answerString);
						}
						number2[0] = '\0';

						_Delete(res_vectorR, DIMTWOD, dime, "res_vectorR,DIMTWOD,dime");
						_Delete(res_vectorI, DIMTWOD, dime, "res_vectorI,DIMTWOD,dime");
						_delete(answerString, "answerString"); answerString = nullptr;

					}
				}
				sif = 0;
				int df = j;
				j = 0;
				if (number2[0] != 'B' && number2[0] != 'O' && number2[0] != 'H' && number2[0] != 'P') {
					if (number2[0] == '_' && number2[1] != 'e' && number2[1] != 'p' && number2[1] != 'B' && number2[1] != 'O' && number2[1] != 'H' && (number2[1] == 'I' && number2[2] == 'N' && number2[3] == 'F') == false) {
						if (number2[1] == '.') {
							j = abs((int)strlen(number2));
							while (j > 1) {
								number2[j] = number2[j - 1];
								j--;
							}
							number2[j] = '0';
						}
						for (j = 0; j < abs((int)strlen(number2)); j++) {
							number2[j] = number2[j + 1];
						}
						if (number2[0] != '0' && number2[0] != '1' && number2[0] != '2' && number2[0] != '3' && number2[0] != '4' && number2[0] != '5' && number2[0] != '6' && number2[0] != '7' && number2[0] != '8' && number2[0] != '9') {
							sign = 1;
							for (j = 0; j < abs((int)strlen(number2)); j++) {
								if (number2[j] == '.') {
									number2[j] = '\0';
								}
							}
						}
						if (res == 0) {
							ampl[n] = -1 * convertToNumber<T>(number2);
						}
					}
					else {
						if (res == 0 && number2[0] != '_') {
							ampl[n] = convertToNumber<T>(number2);
						}
					}
					if (prefCalc[0] == 'P') {
						if (prefCalc[1] == 'd' && prefCalc[2] == 'a') {
							prefCalc[1] = 'D';
						}
						ampl[n] = precisionValueTo<T>(ampl[n]) * prefToNumber<T>(prefCalc[1]);
					}
					number2[df] = '\0';
				}
				T var = 0;
				if (firstLetterVariable(number2[0])) {
					for (j = 0; j < abs((int)strlen(number2)); j++) {
						if (number2[j] == '.') {
							number2[j] = '\0';
						}
					}

					processVariable<T>(number2);
					ampl[n] = resultR;
					amplI[n] = resultI;

					if (precisionValueTo<T>(resultR) != 0) {
						ampl[n] = resultR;
						if (sign == 1) {
							sign = 0;
							ampl[n] =precisionValueTo<T>(ampl[n]) * -1;
						}
					}
					if (precisionValueTo<T>(resultI) != 0) {
						complex = 2;
						amplI[n] = resultI;
						if (sign == 1) {
							sign = 0;
							amplI[n] = precisionValueTo<T>(amplI[n]) * -1;
						}
					}
				}
				if (number2[1] == 'f' || number2[1] == 'h' || number2[1] == 'j' || number2[1] == 'k' || number2[1] == 'm' || number2[1] == 'n' || number2[1] == 'o' || number2[1] == 'p' && number2[2] != 'i' || number2[1] == 'u' || number2[1] == 'w' || number2[1] == 'v' || number2[1] == 'y' || number2[1] == 'z' || number2[1] == 'G' || number2[1] == 'I' || number2[1] == 'J' || number2[1] == 'K' || number2[1] == 'L' || number2[1] == 'M' || number2[1] == 'N' || number2[1] == 'Q' || number2[1] == 'R' || number2[1] == 'S' || number2[1] == 'T' || number2[1] == 'U' || number2[1] == 'V' || number2[1] == 'X' || number2[1] == 'Y' || number2[1] == 'Z' || number2[0] == 'x') {
					if (number2[0] == '_') {
						for (j = 0; number2[j + 1] != '\0'; j++) {
							number2[j] = number2[j + 1];
						}
						number2[j] = '\0';
						sign = 1;
						for (j = 0; j < abs((int)strlen(number2)); j++) {
							if (number2[j] == '.') {
								number2[j] = '\0';
							}
						}
						processVariable<T>(number2);

						ampl[n] = resultR;
						amplI[n] = resultI;

						if (sign == 1) {
							sign = 0;
							ampl[n] =precisionValueTo<T>(ampl[n]) * -1;
							amplI[n] = precisionValueTo<T>(amplI[n]) * -1;
						}
					}
				}
				if (number2[0] == 'B' || number2[0] == 'O' || number2[0] == 'H') {
					if (number2[0] == 'B') {
						if (isContained("B.", number2)) {
							replace("B.", "B0.", number2);
							sprintf(number2, "%s", expressionF);
						}
						if (isContained("B_.", number2)) {
							replace("B_.", "B_0.", number2);
							sprintf(number2, "%s", expressionF);
						}
					}
					if (number2[0] == 'O') {
						if (isContained("O.", number2)) {
							replace("O.", "O0.", number2);
							sprintf(number2, "%s", expressionF);
						}
						if (isContained("O_.", number2)) {
							replace("O_.", "O_0.", number2);
							sprintf(number2, "%s", expressionF);
						}
					}
					if (number2[0] == 'H') {
						if (isContained("H.", number2)) {
							replace("H.", "H0.", number2);
							sprintf(number2, "%s", expressionF);
						}
						if (isContained("H_.", number2)) {
							replace("H_.", "H_0.", number2);
							sprintf(number2, "%s", expressionF);
						}
					}
					ampl[n] = numericalSystems<T>(number2);
				}
				if (number2[0] == '_' && (number2[1] == 'B' || number2[1] == 'O' || number2[1] == 'H')) {
					for (j = 0; j < abs((int)strlen(number2)); j++) {
						number2[j] = number2[j + 1];
					}
					number2[j] = '\0';
					if (number2[0] == 'B') {
						if (isContained("B.", number2)) {
							replace("B.", "B0.", number2);
							sprintf(number2, "%s", expressionF);
						}
						if (isContained("B_.", number2)) {
							replace("B_.", "B_0.", number2);
							sprintf(number2, "%s", expressionF);
						}
					}
					if (number2[0] == 'O') {
						if (isContained("O.", number2)) {
							replace("O.", "O0.", number2);
							sprintf(number2, "%s", expressionF);
						}
						if (isContained("O_.", number2)) {
							replace("O_.", "O_0.", number2);
							sprintf(number2, "%s", expressionF);
						}
					}
					if (number2[0] == 'H') {
						if (isContained("H.", number2)) {
							replace("H.", "H0.", number2);
							sprintf(number2, "%s", expressionF);
						}
						if (isContained("H_.", number2)) {
							replace("H_.", "H_0.", number2);
							sprintf(number2, "%s", expressionF);
						}
					}
					ampl[n] = numericalSystems<T>(number2) * -1;
				}
				j = 0;
				f = 0;
				sprintf(ex, "");
				if (number2[0] == 'p' && number2[1] == 'i') {
					ampl[n] = boost::math::constants::pi<T>();
				}
				if (number2[0] == '_' && number2[1] == 'p' && number2[2] == 'i') {
					ampl[n] = -boost::math::constants::pi<T>();
				}
				if (number2[0] == 'e') {
					ampl[n] = boost::math::constants::e<T>();
				}
				if (number2[0] == '_' && number2[1] == 'e') {
					ampl[n] = -boost::math::constants::e<T>();
				}
				if (isEqual(number2, "true")) {
					ampl[n] = (T)1;
					number2[0] = '\0';
				}
				if (isEqual(number2, "_true")) {
					ampl[n] = (T)-1;
					number2[0] = '\0';
				}
				if (isEqual(number2, "false") || isEqual(number2, "_false")) {
					ampl[n] = (T)0;
					number2[0] = '\0';
				}
				if (isEqual(number2, "INF")) {
					ampl[n] = precisionValueTo<T>(INF);
					number2[0] = '\0';
				}
				if (isEqual(number2, "_INF")) {
					ampl[n] = -precisionValueTo<T>(INF);
					number2[0] = '\0';
				}
				if (number2[0] == 'r' && number2[1] == 'e' && number2[2] == 's') {
					if (previousAnsType == 0) {
						ampl[n] = ansRV;
						amplI[n] = ansIV;
						if (equationSolverRunning || solverRunning) {
							ampl[n] = xValuesR;
							amplI[n] = xValuesI;
						}
					}
					else {
						convert2Vector(saveMatrixAns);
						check4Vector = 2;
					}
					complex = 2;
				}
				if (number2[0] == '_' && number2[1] == 'r' && number2[2] == 'e' && number2[3] == 's') {
					if (previousAnsType == 0) {
						ampl[n] = precisionValueTo<T>(ansRV) * -1;
						amplI[n] = precisionValueTo<T>(ansIV) * -1;
						if (equationSolverRunning || solverRunning) {
							ampl[n] = precisionValueTo<T>(xValuesR) * -1;
							amplI[n] = precisionValueTo<T>(xValuesI) * -1;
						}
					}
					else {
						convert2Vector(saveMatrixAns);
						PrecisionValue** res_vectorR, ** res_vectorI;
						res_vectorR = new PrecisionValue* [DIMTWOD];

						for (int i = 0; i < DIMTWOD; ++i) {
							res_vectorR[i] = getDynamicDoubleArray();
						}
						res_vectorI = new PrecisionValue* [DIMTWOD];

						for (int i = 0; i < DIMTWOD; ++i) {
							res_vectorI[i] = getDynamicDoubleArray();
						}
						char* answerString = getDynamicCharArray("", "answerString");
						fmmulr(numVectorLines, numVectorCols, vectorR, res_vectorR, -1.0, vectorI, res_vectorI, 0.0);
						sprintf(answerString, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines, numVectorCols));
						convert2Vector(answerString);
						check4Vector = 2;

						_Delete(res_vectorR, DIMTWOD, dime, "res_vectorR,DIMTWOD,dime");

						_Delete(res_vectorI, DIMTWOD, dime, "res_vectorI,DIMTWOD,dime");
						_delete(answerString, "answerString"); answerString = nullptr;

					}
					complex = 2;
				}
				if (facto > 0) {
					if (precisionValueTo<T>(ampl[n]) < 0) {
						number2[0] = '_';
					}
					while (facto > 0) {
						ampl[n] = fact<T>(abs(precisionValueTo<T>(ampl[n])));
						facto--;
					}
					if (number2[0] == '_') {
						ampl[n] = precisionValueTo<T>(ampl[n]) * -1;
					}
				}
				while (trigon1[i] != '+' && trigon1[i] != '-' && trigon1[i] != '*' && trigon1[i] != '/' && trigon1[i] != '^' && trigon1[i] != '=' && i < abs((int)strlen(trigon1))) { i++; }
				amp[n] = trigon1[i];
				if (complex == 1) {
					amplI[n] = ampl[n];
					ampl[n] = 0;
					if (negImag == 1) {
						negImag = 0;
						amplI[n] = precisionValueTo<T>(amplI[n]) * -1;
					}
				}
				else {
					if (complex != 2) {
						amplI[n] = T(0);
					}
				}
			}
		}

		n++;
		sprintf(number2, "");
		res = 0;
	}
	int a = 0;
	int fr;
	so = 0;
	int ca = 0;
	T asdf = 0, asdfI = 0;
	for (so = 0; so < n; so++) {
		int sa = so;
		int b = 0;
		if (amp[so] == '^' && amp[so + 1] == '^') {
			while (amp[so] == '^' && a != 1) {
				if (amp[so + 1] != '^' && amp[so - 1] == '^' && a != 2) {
					asdf = precisionValueTo<T>(ampl[so + 1]);
					asdfI = precisionValueTo<T>(amplI[so + 1]);
					if (precisionValueTo<T>(ampl[so]) < 0 || precisionValueTo<T>(amplI[so]) < 0) {
						sig[so] = 0;
					}
					else { sig[so] = 1; }
					exponentiation<T>(precisionValueTo<T>(ampl[so]), precisionValueTo<T>(amplI[so]), asdf, asdfI, sig[so]);
					asdf = precisionValueTo<T>(resultR);
					asdfI = precisionValueTo<T>(resultI);
					ampl[so + 1] = 1;
					ampl[so] = 1;
					amplI[so + 1] = 0;
					amplI[so] = 0;
					amp[so] = '*';
					so--;
					a = 2;
				}
				else {
					if (amp[so + 1] == '^' && a == 0) {
						so++;
						fr = so;
					}
					else {
						if (a == 2) {
							while (a != 1) {
								if (precisionValueTo<T>(ampl[so]) < 0 || (precisionValueTo<T>(amplI[so]) < 0 && precisionValueTo<T>(ampl[so]) == 0)) {
									sig[so] = 0;
								}
								else { sig[so] = 1; }
								exponentiation<T>(precisionValueTo<T>(ampl[so]), precisionValueTo<T>(amplI[so]), asdf, asdfI, sig[so]);
								asdf = precisionValueTo<T>(resultR);
								asdfI = precisionValueTo<T>(resultI);
								ampl[so] = 1;
								amplI[so] = 0;
								amp[so] = '*';
								so--;
								if (amp[so] != '^') {
									a = 1;
									so = fr++;
								}
							}
						}
					}
				}
				if (a == 1) {
					ampl[sa] = asdf; a = 0;
					amplI[sa] = asdfI;
				}
			}
		}
		else {
			if (amp[so] == '^' && amp[so + 1] != '^') {
				while (amp[so] == '^') {
					if (precisionValueTo<T>(ampl[sa]) < 0 || (precisionValueTo<T>(amplI[sa]) < 0 && precisionValueTo<T>(ampl[sa]) == 0)) {
						sig[sa] = 0;
					}
					else { sig[sa] = 1; }
					exponentiation<T>(precisionValueTo<T>(ampl[sa]), precisionValueTo<T>(amplI[sa]), precisionValueTo<T>(ampl[so + 1]), precisionValueTo<T>(amplI[so + 1]), sig[sa]);
					ampl[sa] = resultR;
					amplI[sa] = resultI;
					ampl[so + 1] = 1;
					amplI[so + 1] = 0;
					amp[so] = '*';
					so++;
				}
			}
		}
	}
	char* simplified = getDynamicCharArray("", "simplified");
	int RF = 0;
	for (RF = 0; RF < n; RF++) {
		convertComplex2Exponential(ampl[RF], amplI[RF]);
		if (precisionValueTo<T>(ampl[RF]) > 0 && precisionValueTo<T>(amplI[RF]) < 0) {
			sprintf(simplified, "%s(%s%si)%c", simplified, respR, respI, amp[RF]);
		}
		else {
			if (precisionValueTo<T>(ampl[RF]) < 0 && precisionValueTo<T>(amplI[RF]) > 0) {
				sprintf(simplified, "%s(%s+%si)%c", simplified, respR, respI, amp[RF]);
			}
			else {
				if (precisionValueTo<T>(ampl[RF]) < 0 && precisionValueTo<T>(amplI[RF]) < 0) {
					sprintf(simplified, "%s(%s%si)%c", simplified, respR, respI, amp[RF]);
				}
				else {
					if (precisionValueTo<T>(ampl[RF]) == 0 && precisionValueTo<T>(amplI[RF]) == 0) {
						sprintf(simplified, "%s%s%c", simplified, convert2Exponential<T>(precisionValueTo<T>(ampl[RF])), amp[RF]);
					}
					else {
						if (precisionValueTo<T>(ampl[RF]) == 0 && precisionValueTo<T>(amplI[RF]) != 0) {
							sprintf(simplified, "%s%si%c", simplified, convert2Exponential<T>(precisionValueTo<T>(amplI[RF])), amp[RF]);
						}
						else {
							if (precisionValueTo<T>(ampl[RF]) != 0 && precisionValueTo<T>(amplI[RF]) == 0) {
								sprintf(simplified, "%s%s%c", simplified, convert2Exponential<T>(precisionValueTo<T>(ampl[RF])), amp[RF]);
							}
							else {
								sprintf(simplified, "%s(%s+%si)%c", simplified, respR, respI, amp[RF]);
							}
						}
					}
				}
			}
		}
	}
	rasf = abs((int)strlen(simplified));
	while (simplified[rasf - 2] == '+' && simplified[rasf - 1] == '0') {
		rasf = rasf - 2;
		simplified[rasf] = '\0';
	}
	simplified[abs((int)strlen(simplified))] = '\0';
	replace("=", "", simplified);
	sprintf(simplified, "%s", expressionF);
	if (verbose == 1 && solving) {
		printf("\nSimplified expression by arithSolver: %s\n\n", verboseDisplayExpression(simplified).c_str());
	}
	for (so = 0; so < n; so++) {
		int sa = so;
		while (amp[so] == '/') {
			division<T>(precisionValueTo<T>(ampl[sa]), precisionValueTo<T>(amplI[sa]), precisionValueTo<T>(ampl[so + 1]), precisionValueTo<T>(amplI[so + 1]));
			ampl[sa] = resultR;
			amplI[sa] = resultI;
			ampl[so + 1] = 1;
			amplI[so + 1] = 0;
			amp[so] = '*';
			so++;
		}
	}
	for (so = 0; so < n; so++) {
		int sa = so;
		while (amp[so] == '*') {
			multiplication<T>(precisionValueTo<T>(ampl[sa]), precisionValueTo<T>(amplI[sa]), precisionValueTo<T>(ampl[so + 1]), precisionValueTo<T>(amplI[so + 1]));
			ampl[sa] = resultR;
			amplI[sa] = resultI;
			ampl[so + 1] = 1;
			amplI[so + 1] = 0;
			amp[so] = '*';
			so++;
		}
	}
	for (h = 0; h < n; h++) {
		if (h == 0) {
			result1 = precisionValueTo<T>(ampl[0]);
			result2 = precisionValueTo<T>(amplI[0]);
		}
		if (amp[h] == '^') {
			exponentiation<T>(result1, result2, precisionValueTo<T>(ampl[h + 1]), precisionValueTo<T>(amplI[h + 1]), 1);
			result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		}
		if (amp[h] == '*') {
			multiplication<T>(result1, result2, precisionValueTo<T>(ampl[h + 1]), precisionValueTo<T>(amplI[h + 1]));
			result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		}
		if (amp[h] == '/') {
			division<T>(result1, result2, precisionValueTo<T>(ampl[h + 1]), precisionValueTo<T>(amplI[h + 1]));
			result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		}
		if (amp[h] == '-') {
			subtraction<T>(result1, result2, precisionValueTo<T>(ampl[h + 1]), precisionValueTo<T>(amplI[h + 1]));
			result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		}
		if (amp[h] == '+') {
			sum<T>(result1, result2, precisionValueTo<T>(ampl[h + 1]), precisionValueTo<T>(amplI[h + 1]));
			result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		}
	}
	resultR = result1;
	resultI = result2;
	result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	_delete(number2, "number2"); number2 = nullptr;
	_delete(ex, "ex"); ex = nullptr;
	_delete(simplified, "simplified"); simplified = nullptr;
	_delete(amp, "amp"); amp = nullptr;
	_delete(prefCalc, "prefCalc"); prefCalc = nullptr;
	_delete(trigon, "trigon"); trigon = nullptr;
	_delete(sig, "sig"); sig = nullptr;
	_delete(ampl, "ampl"); ampl = nullptr;
	_delete(amplI, "amplI"); amplI = nullptr;
	return result1;


}
template <typename T>
T functionProcessor(char* trigon, PrecisionValue result, PrecisionValue amplitude, int res, char* argNotNumber) {
	char* saveArgument = getDynamicCharArray(expressionF, "saveArgument");
	if (verbose == 1 && solving) {
		printf("\n\n==> functionProcessor <==\n\nFunction: %s\n", trigon);
	}
	int i = 0, var = 0, j = 0, n = 0, count = 0, opt = 0, l = 0, p = 0, cn = 0, s, rad = 1, jg = 1, gon = 0, tri = 0, co = 0, trigono = 0, paren = 1, pare = 0, parent = 0, e = 0, f = 0, kl = 0, ar = 0, deg = 0, type = 0, g = 0;
	char* trig = getDynamicCharArray("0", "trig"); char* base = getDynamicCharArray("", "base"); char* number = getDynamicCharArray("0", "number");
	char* number1 = getDynamicCharArray("0", "number1"); char* number2 = getDynamicCharArray("0", "number2");
	char* op = getDynamicCharArray("0", "op"); char signal = '*'; char* numb = getDynamicCharArray("0", "numb"); char sig = '0'; char point = '0';
	char* cieNot = getDynamicCharArray("0", "cieNot");
	char* arg = getDynamicCharArray("0", "arg"); char* amp = getDynamicCharArray("0", "amp"); char* trigon1 = getDynamicCharArray("0", "trigon1"); char* ex = getDynamicCharArray("", "ex");
	char* trig1 = getDynamicCharArray("", "trig1");
	char* function = getDynamicCharArray("cos,acos,sin,asin,tan,atan,sec,asec,cosec,acosec,cotan,acotan,log,ln,rest,quotient,sqrt,cbrt,afact,cosh,acosh,sinh,asinh,tanh,atanh,sech,asech,cosech,acosech,cotanh,acotanh,sinc,gerror,gerrorinv,gerrorc,gerrorcinv,qfunc,qfuncinv,cbrt,sqrt,atc,i,res,pi,e,solver,det,abs,strlen,countoccurrences,iscontained,iscontainedbyindex,iscontainedvariable,isequal,isvariable,istowrite,for,calc,max,min,linsnum,colsnum,getlins,getcols,avg,", "function");
	T num = 0, exp = 1, result1 = 0, baLog = 0, dgrt = 0, result2 = 0, dgrt2 = 0;
	PrecisionValue* v = getDynamicDoubleArray(); PrecisionValue* vI = getDynamicDoubleArray(); PrecisionValue* argu = getDynamicDoubleArray(); PrecisionValue* ampl = getDynamicDoubleArray();
		char* userFunc = getDynamicCharArray("", "userFunc"); char* atcFunc = getDynamicCharArray("", "atcFunc"); char* funcU = getDynamicCharArray("", "funcU");
	char* saveFunction = getDynamicCharArray("", "saveFunction");
	sprintf(saveFunction, "%s%s", function, usRFuncTrans);
	sprintf(function, "%s", saveFunction);


	for (i = 0; trigon[i] != '?' && i < abs((int)strlen(trigon)); i++) {
		atcFunc[i] = trigon[i];
	}
	atcFunc[i] = '\0';
	if (atcFunc[0] == 'a' && atcFunc[1] == 't' && atcFunc[2] == 'c' && atcFunc[3] == '_') {
		for (i = 0; i + 4 < abs((int)strlen(atcFunc)); i++) {
			atcFunc[i] = atcFunc[i + 4];
		}
		atcFunc[i] = '\0';

		char* propFunc = getDynamicCharArray("", "propFunc");
		sprintf(propFunc, "%s,", atcFunc);
		if (isContained(propFunc, usRFuncTrans)) {
			int start = strStart;
			int end = strEnd;
			int k = 0;
			int y = start;
			while (y < end - 1) {
				atcFunc[k] = usRFunctions[y];
				y++; k++;
			}
			atcFunc[k] = '\0';
		}
		int hi = 0;
		for (hi = 0; hi < abs((int)strlen(atcFunc)); hi++) {
			funcU[hi] = atcFunc[hi];
		}
		funcU[hi] = '\0';
		FILE* open = NULL;

		sprintf(userFunc, "%s\\User functions\\%s.txt", atcPath, atcFunc);
		if (open != NULL) {
			fclose(open);
			open = NULL;
		}
		open = fopen(userFunc, "r");
		if (open != NULL) {
			fclose(open);
			sprintf(function, "%satc_%s", function, atcFunc);
		}

		_delete(propFunc, "propFunc"); propFunc = nullptr;

	}
	for (i = 0; i < abs((int)strlen(trigon)); i++) {
		if (trigon[i] == '?') {
			var = 1;
			trigon[i] = '\0';

		}
	}
	v[0] = 0; v[1] = 0; v[7] = 0; vI[0] = 0; vI[1] = 0; vI[7] = 0;
	if (trigon[0] == '_') {
		jg = -1;
		for (s = 0; s < abs((int)strlen(trigon)); s++) {
			trigon[s] = trigon[s + 1];
		}
	}
	if (Mode == 0) {
		opt = applySettings(4);
		if (opt == 3) {
			deg = 0;
			rad = 0;
			gon = 1;
		}
		if (opt == 2) {
			deg = 1;
			rad = 0;
			gon = 0;
		}
		if (opt == 1) {
			rad = 1;
			deg = 0;
			gon = 0;
		}
	}
	for (s = 0; s < abs((int)strlen(trigon)); s++) {
		v[s] = 0;
		argu[s] = 0;
		ampl[s] = 0;
	}
	v[0] = amplitude;
	v[1] = result;
	vI[0] = resultR;
	vI[1] = resultI;
	if (verbose == 1 && solving) {
		puts("\nFunction arguments:");
		printVerboseComplexValue<T>("Evaluated argument", precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
	}
	result = 0;
	if (trigon[0] == 'r' && trigon[1] == 'a' && trigon[2] == 'd') {
		rad = 1;
		deg = 0;
		gon = 0;
		for (s = 0; s < abs((int)strlen(trigon)); s++) {
			trigon[s] = trigon[s + 3];
		}
		trigon[s] = '\0';
	}
	if (trigon[0] == 'd' && trigon[1] == 'e' && trigon[2] == 'g') {
		deg = 1;
		rad = 0;
		gon = 0;
		for (s = 0; s < abs((int)strlen(trigon)); s++) {
			trigon[s] = trigon[s + 3];
		}
		trigon[s] = '\0';
	}
	if (trigon[0] == 'g' && trigon[1] == 'o' && trigon[2] == 'n') {
		gon = 1;
		deg = 0;
		rad = 0;
		for (s = 0; s < abs((int)strlen(trigon)); s++) {
			trigon[s] = trigon[s + 3];
		}
		trigon[s] = '\0';
	}
	if (isEqual("strlen", trigon)) {
		_delete(v, "v"); v = nullptr;
		_delete(vI, "vI"); vI = nullptr;
		_delete(argu, "argu"); argu = nullptr;
		_delete(ampl, "ampl"); ampl = nullptr;
		_delete(saveArgument, "saveArgument"); saveArgument = nullptr;
		_delete(saveFunction, "saveFunction"); saveFunction = nullptr;
		_delete(arg, "arg"); arg = nullptr;
		_delete(cieNot, "cieNot"); cieNot = nullptr;
		_delete(number1, "number1"); number1 = nullptr;
		_delete(op, "op"); op = nullptr;
		_delete(trig, "trig"); trig = nullptr;
		_delete(trig1, "trig1"); trig1 = nullptr;
		_delete(userFunc, "userFunc"); userFunc = nullptr;
		_delete(number2, "number2");
		_delete(ex, "ex");
		_delete(trigon1, "trigon1");
		_delete(base, "base");
		_delete(number, "number");
		_delete(numb, "numb");
		_delete(amp, "amp");
		_delete(atcFunc, "atcFunc");
		_delete(funcU, "funcU");
		_delete(function, "function");
		return 0.5;
	}
	if (var == 1) {
		if (trigon[0] == 'a' && trigon[1] == 't' && trigon[2] == 'c' && trigon[3] == '_') {

			for (i = 0; trigon[i + 4] != '\0'; i++) {
				trigon[i] = trigon[i + 4];
			}
			trigon[i] = '\0';
		}
		if ((isEqual("rtDD", trigon)) || (isEqual("logbb", trigon))) {
			_delete(v, "v"); v = nullptr;
			_delete(vI, "vI"); vI = nullptr;
			_delete(argu, "argu"); argu = nullptr;
			_delete(ampl, "ampl"); ampl = nullptr;
			_delete(saveArgument, "saveArgument"); saveArgument = nullptr;
			_delete(saveFunction, "saveFunction"); saveFunction = nullptr;
			_delete(arg, "arg"); arg = nullptr;
			_delete(cieNot, "cieNot"); cieNot = nullptr;
			_delete(number1, "number1"); number1 = nullptr;
			_delete(op, "op"); op = nullptr;
			_delete(trig, "trig"); trig = nullptr;
			_delete(trig1, "trig1"); trig1 = nullptr;
			_delete(userFunc, "userFunc"); userFunc = nullptr;
			_delete(number2, "number2");
			_delete(ex, "ex");
			_delete(trigon1, "trigon1");
			_delete(base, "base");
			_delete(number, "number");
			_delete(numb, "numb");
			_delete(amp, "amp");
			_delete(atcFunc, "atcFunc");
			_delete(funcU, "funcU");
			_delete(function, "function");

			return 0.5;
		}
		for (i = 0; i < abs((int)strlen(function)); i++) {
			j = 0; g = 0;
			if (function[i] == trigon[j]) {
				j = 0; g = 0;
				while (i < abs((int)strlen(function)) && function[i] != ',') {
					if (function[i] == trigon[j]) {
						j++;
					}
					i++;
					g++;
				}
				if (j == abs((int)strlen(trigon)) && g == j) {
					_delete(v, "v"); v = nullptr;
					_delete(vI, "vI"); vI = nullptr;
					_delete(argu, "argu"); argu = nullptr;
					_delete(ampl, "ampl"); ampl = nullptr;
					_delete(saveArgument, "saveArgument"); saveArgument = nullptr;
					_delete(saveFunction, "saveFunction"); saveFunction = nullptr;
					_delete(arg, "arg"); arg = nullptr;
					_delete(cieNot, "cieNot"); cieNot = nullptr;
					_delete(number1, "number1"); number1 = nullptr;
					_delete(op, "op"); op = nullptr;
					_delete(trig, "trig"); trig = nullptr;
					_delete(trig1, "trig1"); trig1 = nullptr;
					_delete(userFunc, "userFunc"); userFunc = nullptr;
					_delete(number2, "number2");
					_delete(ex, "ex");
					_delete(trigon1, "trigon1");
					_delete(base, "base");
					_delete(number, "number");
					_delete(numb, "numb");
					_delete(amp, "amp");
					_delete(atcFunc, "atcFunc");
					_delete(funcU, "funcU");
					_delete(function, "function");

					return 0.5;
				}
			}
		}
	}
	i = 0; j = 0;
	for (s = 0; s < abs((int)strlen(trigon)); s++) {
		if (((trigon[s - 1] == 'g' && trigon[s] == 'b') && trigon[s - 1] != 'c') || (trigon[s - 1] == 't' && trigon[s] == 'D')) {
			j = s;
			s++;
			while ((trigon[s] == 'b' && trigon[s + 1] == '\0') == false && (trigon[s] == 'D' && trigon[s + 1] == '\0') == false && s < abs((int)strlen(trigon))) {
				base[i] = trigon[s];
				i++; s++;
			}
			base[i] = '+'; base[i + 1] = '0'; base[i + 2] = '\0';
			resultR = 0; resultI = 0;
			baLog = 0;
			baLog = initialProcessor<T>(base, (T)0);
			dgrt = baLog;
			dgrt2 = precisionValueTo<T>(resultI);
			resultI = 0; resultR = 0; baLog = 0;
			trigon[j] = '\0';
		}
	}
	sprintf(op, "%s", trigon);
	int h = 0;
	for (i = 0; i < abs((int)strlen(op)); i++) {
		if (op[i] == 'h') {
			h = 1;
		}
	}
	char* funC = getDynamicCharArray("", "funC");
	sprintf(funC, "%s,", op);
	if (h == 0 && op[0] != 'a' && isContained(funC, "cos, sin, tan, sec, cosec, cotan,")) {
		if (rad == 1) {
			// Parte Real: Converte para graus, reduz o período de 360, e volta a radianos
			v[7] = ((precisionValueTo<T>(v[1]) * 180) / M_PI);
			if (precisionValueTo<T>(v[7]) < 0) {
				v[7] = re(precisionValueTo<T>(v[7]), (T)-360);
			}
			else if (precisionValueTo<T>(v[7]) >= 0) {
				v[7] = re(precisionValueTo<T>(v[7]), (T)360);
			}
			v[1] = precisionValueTo<T>(v[7]) * M_PI / 180;

			// Parte Imaginária: NÃO sofre redução periódica, apenas mantém a consistência se necessário
			// Se vI[1] veio a zero, o ruído microscópico de PI será limpo no fim
		}

		if (deg == 1) {
			// Parte Real: Reduz diretamente no domínio dos graus
			v[7] = v[1];
			if (precisionValueTo<T>(v[7]) < 0) {
				v[7] = re(precisionValueTo<T>(v[7]), (T)-360);
			}
			else if (precisionValueTo<T>(v[7]) >= 0) {
				v[7] = re(precisionValueTo<T>(v[7]), (T)360);
			}
			v[1] = v[7];
		}

		if (gon == 1) {
			// Parte Real: Converte para escala de 360 para o 're' funcionar, e reverte
			v[7] = precisionValueTo<T>(v[1]) * 0.9;
			if (precisionValueTo<T>(v[7]) < 0) {
				v[7] = re(precisionValueTo<T>(v[7]), (T)-360);
			}
			else if (precisionValueTo<T>(v[7]) >= 0) {
				v[7] = re(precisionValueTo<T>(v[7]), (T)360);
			}
			v[1] = precisionValueTo<T>(v[7]) / 0.9;
		}

		// Blindagem de precisão: Limpa o ruído gerado por floats em entradas puramente reais
		if (fabs((double)precisionValueTo<T>(vI[1])) < 1e-14) {
			vI[1] = 0.0;
		}
	}
	if (isEqual("log", op)) {
		if (dgrt != 0 || dgrt2 != 0) {
			complex_log(dgrt, dgrt2);
			T baR = precisionValueTo<T>(resultR), baI = precisionValueTo<T>(resultI);
			complex_log(precisionValueTo<T>(v[1]), result2);
			division<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), baR, baI);
			result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		}
		else {
			complex_log((T)10.0, (T)0);
			T baR = precisionValueTo<T>(resultR), baI = precisionValueTo<T>(resultI);
			complex_log(precisionValueTo<T>(v[1]), result2);
			division<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), baR, baI);
			result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		}
	}
	if (isEqual("rt", op)) {
		division<T>((T)1, (T)0, dgrt, dgrt2);
		exponentiation<T>(precisionValueTo<T>(v[1]), result2, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), 1);
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("sqrt", op)) {
		exponentiation<T>(precisionValueTo<T>(v[1]), result2, (T)(1 / 2.0), (T)0, 1);
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("cbrt", op)) {
		exponentiation<T>(precisionValueTo<T>(v[1]), result2, (T)(1 / 3.0), (T)0, 1);
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("ln", op)) {
		complex_log(precisionValueTo<T>(v[1]), result2);
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("abs", op)) {
		resultR = abs_complex(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		resultI = 0;
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		type = 1;
	}
	if (isEqual("cosec", op)) {
		if (deg == 1) {
			v[1] = ((precisionValueTo<T>(v[1]) * M_PI) / 180);
			vI[1] = ((precisionValueTo<T>(vI[1]) * M_PI) / 180);
		}
		if (gon == 1) {
			v[1] = precisionValueTo<T>(v[1]) * (M_PI / 200);
			vI[1] = precisionValueTo<T>(vI[1]) * (M_PI / 200);
		}
		cosec(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("cosech", op)) {
		cosech(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("sec", op)) {
		if (deg == 1) {
			v[1] = ((precisionValueTo<T>(v[1]) * M_PI) / 180);
			vI[1] = ((precisionValueTo<T>(vI[1]) * M_PI) / 180);
		}
		if (gon == 1) {
			v[1] = precisionValueTo<T>(v[1]) * (M_PI / 200);
			vI[1] = precisionValueTo<T>(vI[1]) * (M_PI / 200);
		}
		sec(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("sech", op)) {
		sech(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("cotan", op)) {
		if (deg == 1) {
			v[1] = ((precisionValueTo<T>(v[1]) * M_PI) / 180);
			vI[1] = ((precisionValueTo<T>(vI[1]) * M_PI) / 180);
		}
		if (gon == 1) {
			v[1] = precisionValueTo<T>(v[1]) * (M_PI / 200);
			vI[1] = precisionValueTo<T>(vI[1]) * (M_PI / 200);
		}
		cotan(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("cotanh", op)) {
		cotanh(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("acos", op)) {
		complex_acos(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("asin", op)) {
		complex_asin(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("atan", op)) {
		complex_atan(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("cos", op)) {
		if (deg == 1) {
			v[1] = ((precisionValueTo<T>(v[1]) * M_PI) / 180);
			vI[1] = ((precisionValueTo<T>(vI[1]) * M_PI) / 180);
		}
		if (gon == 1) {
			v[1] = precisionValueTo<T>(v[1]) * (M_PI / 200);
			vI[1] = precisionValueTo<T>(vI[1]) * (M_PI / 200);
		}
		complex_cos(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		if (precisionValueTo<T>(v[7]) == 270 || precisionValueTo<T>(v[7]) == 90 || precisionValueTo<T>(v[7]) == -90 || precisionValueTo<T>(v[7]) == -270) {
			result1 = precisionValueTo<T>(v[0]) * sqrt(1 - (sin(precisionValueTo<T>(v[1])) * sin(precisionValueTo<T>(v[1]))));
		}
	}
	if (isEqual("cosh", op)) {
		complex_cosh(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("sin", op)) {
		if (deg == 1) {
			v[1] = ((precisionValueTo<T>(v[1]) * M_PI) / 180);
			vI[1] = ((precisionValueTo<T>(vI[1]) * M_PI) / 180);
		}
		if (gon == 1) {
			v[1] = precisionValueTo<T>(v[1]) * (M_PI / 200);
			vI[1] = precisionValueTo<T>(vI[1]) * (M_PI / 200);
		}
		complex_sin(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		if ((precisionValueTo<T>(v[7]) == 180 || precisionValueTo<T>(v[7]) == 0 || precisionValueTo<T>(v[7]) == -180) &&precisionValueTo<T>( vI[7]) == 0) {
			result1 = precisionValueTo<T>(v[0]) * sqrt(1 - (cos(precisionValueTo<T>(v[1])) * cos(precisionValueTo<T>(v[1]))));
		}
	}
	if (isEqual("sinh", op)) {
		complex_sinh(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("sinc", op)) {
		sinc(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("tan", op)) {
		if (deg == 1) {
			v[1] = ((precisionValueTo<T>(v[1]) * M_PI) / 180);
			vI[1] = ((precisionValueTo<T>(vI[1]) * M_PI) / 180);
		}
		if (gon == 1) {
			v[1] = precisionValueTo<T>(v[1]) * (M_PI / 200);
			vI[1] = precisionValueTo<T>(vI[1]) * (M_PI / 200);
		}
		complex_tan(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		if ((precisionValueTo<T>(v[7]) == 90 || precisionValueTo<T>(v[7]) == -90 || precisionValueTo<T>(v[7]) == 270 || precisionValueTo<T>(v[7]) == -270 || precisionValueTo<T>(v[7]) == 0 || precisionValueTo<T>(v[7]) == 180 || precisionValueTo<T>(v[7]) == -180) && precisionValueTo<T>(vI[7]) == 0) {
			result1 = precisionValueTo<T>(v[0]) * (sqrt(1 - cos(precisionValueTo<T>(v[1])) * cos(precisionValueTo<T>(v[1]))) / sqrt(1 - sin(precisionValueTo<T>(v[1])) * sin(precisionValueTo<T>(v[1]))));
		}
	}
	if (isEqual("tanh", op)) {
		complex_tanh(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		type = 1;
	}
	if (isEqual("asinh", op)) {
		arsinh(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		type = 1;
	}
	if (isEqual("acosh", op)) {
		arcosh(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		type = 1;
	}
	if (isEqual("atanh", op)) {
		artanh(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		type = 1;
	}
	if (isEqual("acotanh", op)) {
		arcoth(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		type = 1;
	}
	if (isEqual("asech", op)) {
		arsech(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		type = 1;
	}
	if (isEqual("acosech", op)) {
		arcsch(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		type = 1;
	}
	if (isEqual("quotient", op)) {
		qu_complex(precisionValueTo<T>(v[0]), precisionValueTo<T>(vI[0]), precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("rest", op)) {
		re_complex(precisionValueTo<T>(v[0]), precisionValueTo<T>(vI[0]), precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("acosec", op)) {
		arcosec(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("asec", op)) {
		arcsec(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("acotan", op)) {
		arcotg(precisionValueTo<T>(v[1]), precisionValueTo<T>(vI[1]));
		result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
	}
	if (isEqual("qfunc", op)) {
		result1 = precisionValueTo<T>(v[0]) * qfunc(precisionValueTo<T>(v[1]));
	}
	if (isEqual("qfuncinv", op)) {
		result1 = precisionValueTo<T>(v[0]) * qfuncinv(precisionValueTo<T>(v[1]));
	}
	if (isEqual("gerror", op)) {
		result1 = precisionValueTo<T>(v[0]) * gerror(precisionValueTo<T>(v[1]));
	}
	if (isEqual("gerrorc", op)) {
		result1 = precisionValueTo<T>(v[0]) * gerrorc(precisionValueTo<T>(v[1]));
	}
	if (isEqual("gerrorinv", op)) {
		result1 = precisionValueTo<T>(v[0]) * gerrorinv(precisionValueTo<T>(v[1]));
	}
	if (isEqual("gerrorcinv", op)) {
		result1 = precisionValueTo<T>(v[0]) * gerrorcinv(precisionValueTo<T>(v[1]));
	}
	if (isEqual("afact", op)) {
		result1 = precisionValueTo<T>(v[0]) * arcfact(precisionValueTo<T>(v[1]));
		type = 1;
	}
	if (trigon[0] == 'a' && trigon[1] == 't' && trigon[2] == 'c' && trigon[3] == '_') {

		runningUserFunction = 1;
		char* comm = getDynamicCharArray("", "comm");
		if (atcFunc[0] == 'a' && atcFunc[1] == 't' && atcFunc[2] == 'c' && atcFunc[3] == '_') {
			for (i = 0; atcFunc[i + 4] != '\0'; i++) {
				atcFunc[i] = atcFunc[i + 4];
			}
			atcFunc[i] = '\0';
		}
		resultR = v[1];
		resultI = vI[1];

		int inputs = countOccurrences("\\", saveArgument);
		char* letters = getDynamicCharArray("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "letters"); char* value = getDynamicCharArray("", "value");
		int y = 0, x = 0, entered = 0;
		char* toEnter = getDynamicCharArray("", "toEnter");
		sprintf(toEnter, "%s", saveArgument);
		while (entered <= inputs) {
			y = 0;
			while (toEnter[x] != '\\' && toEnter[x] != '=' && x < abs((int)strlen(toEnter))) {
				value[y] = toEnter[x];
				y++; x++;
			}
			value[y] = '\0';
			if (abs((int)strlen(value)) > 0) {

				char* variable = getDynamicCharArray("", "variable");
				sprintf(expressionF, "Input%c", letters[entered]);
				variableValidator<T>(expressionF);
				char* eXpress = getDynamicCharArray("", "eXpress");
				sprintf(eXpress, "%s=%s", revariable, value);
				calcNow<T>(eXpress, (T)0, (T)0);//to set variable
				calcNow<T>(eXpress, (T)0, (T)0);//to put on dynamic variable char array as memory
			}
			entered++;
			x++;
			sprintf(value, "");
		}

		processTxt<T>(userFunc, res);

		if (!(abs((int)strlen(matrixValue)) > 0 || abs((int)strlen(matrixResult)) > 0) || isEqual("script", context)) {
			result1 = precisionValueTo<T>(resultR);
		result2 = precisionValueTo<T>(resultI);
		}
		char* txtSolved = getDynamicCharArray("", "txtSolved");
		char* txtTryDelete = getDynamicCharArray("", "txtTryDelete");
		sprintf(userFunc, "%s\\User functions\\%s.txt", atcPath, funcU);
		sprintf(txtSolved, "del \"%s\\User functions\\%s_answers.txt\"", atcPath, funcU);
		sprintf(txtTryDelete, "%s\\User functions\\%s_answers.txt", atcPath, funcU);
		FILE* file = NULL;
		file = fopen(txtTryDelete, "r");
		if (file != NULL) {
			fclose(file);
			system(txtSolved);
		}
		type = 1;
		sprintf(function, "cos,acos,sin,asin,tan,atan,sec,asec,cosec,acosec,cotan,acotan,log,ln,rest,quotient,sqrt,cbrt,afact,cosh,acosh,sinh,asinh,tanh,atanh,sech,asech,cosech,acosech,cotanh,acotanh,sinc,gerror,gerrorinv,gerrorc,gerrorcinv,qfunc,qfuncinv,cbrt,sqrt,atc,solver,det,abs,strlen,countoccurrences,iscontained,iscontainedbyindex,iscontainedvariable,isequal,isvariable,istowrite,for,calc,max,min,linsnum,colsnum,getlins,getcols,avg,");
		runningUserFunction = 0;
		_delete(comm, "comm"); comm = nullptr;
		_delete(v, "v"); v = nullptr;
		_delete(vI, "vI"); vI = nullptr;
		_delete(argu, "argu"); argu = nullptr;
		_delete(ampl, "ampl"); ampl = nullptr;
		if (letters != nullptr) {
			_delete(letters, "letters"); letters = nullptr;
		}
		_delete(toEnter, "toEnter"); toEnter = nullptr;
		_delete(txtSolved, "txtSolved"); txtSolved = nullptr;
		_delete(txtTryDelete, "txtTryDelete"); txtTryDelete = nullptr;
		_delete(saveArgument, "saveArgument"); saveArgument = nullptr;
		_delete(saveFunction, "saveFunction"); saveFunction = nullptr;
		_delete(funC, "funC"); funC = nullptr;
		_delete(arg, "arg"); arg = nullptr;
		_delete(cieNot, "cieNot"); cieNot = nullptr;
		_delete(number1, "number1"); number1 = nullptr;
		_delete(op, "op"); op = nullptr;
		_delete(trig, "trig"); trig = nullptr;
		_delete(trig1, "trig1"); trig1 = nullptr;
		_delete(userFunc, "userFunc"); userFunc = nullptr;
		_delete(number2, "number2");
		_delete(ex, "ex");
		_delete(trigon1, "trigon1");
		_delete(base, "base");
		_delete(number, "number");
		_delete(numb, "numb");
		_delete(amp, "amp");
		_delete(atcFunc, "atcFunc");
		_delete(funcU, "funcU");
		_delete(function, "function");
		_delete(value, "value");

		return result1;
	}
	if (op[0] == 'a' && type == 0) {
		if (deg == 1) {
			result1 = ((result1 * 180) / M_PI);
			result2 = ((result2 * 180) / M_PI);
		}
		if (gon == 1) {
			result1 = result1 * (200 / M_PI);
			result2 = result2 * (200 / M_PI);
		}
	}
	sprintf(trigon, "%s", "");
	result1 = result1 * jg;
	result2 = result2 * jg;
	resultR = result1;
	resultI = result2;
	if (verbose == 1 && solving) {
		puts("\nFunction processing result:");
		printVerboseComplexValue<T>("Function result", result1, result2);
	}
	_delete(v, "v"); v = nullptr;
	_delete(vI, "vI"); vI = nullptr;
	_delete(ampl, "ampl"); ampl = nullptr;
	_delete(saveArgument, "saveArgument"); saveArgument = nullptr;
	_delete(vI, "vI"); vI = nullptr;
	_delete(v, "v"); v = nullptr;
	_delete(saveFunction, "saveFunction"); saveFunction = nullptr;
	_delete(funC, "funC"); funC = nullptr;
	_delete(arg, "arg"); arg = nullptr;
	_delete(cieNot, "cieNot"); cieNot = nullptr;
	_delete(number1, "number1"); number1 = nullptr;
	_delete(op, "op"); op = nullptr;
	_delete(trig, "trig"); trig = nullptr;
	_delete(trig1, "trig1"); trig1 = nullptr;
	_delete(userFunc, "userFunc"); userFunc = nullptr;
	_delete(number2, "number2");
	_delete(ex, "ex");
	_delete(trigon1, "trigon1");
	_delete(base, "base");
	_delete(number, "number");
	_delete(numb, "numb");
	_delete(amp, "amp");
	_delete(atcFunc, "atcFunc");
	_delete(funcU, "funcU");
	_delete(function, "function");

	return result1;
}

template <>
PrecisionValue initialProcessor<PrecisionValue>(char* arithTrig, PrecisionValue result) {
    if (higherPrecision == 1) {
        return initialProcessor<mp_float>(arithTrig, precisionValueTo<mp_float>(result));
    }
    return initialProcessor<double>(arithTrig, precisionValueTo<double>(result));
}
