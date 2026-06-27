

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
			T a = solveMath(getValue);
			d++;
			e = 0;
			sprintf(getValue, "");
			while (expression[d] != '\\') {
				getValue[e] = expression[d];
				e++;
				d++;
			}
			getValue[e] = '\0';
			T b = solveMath(getValue);
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
	bool to_solve = dataVerifier(equation, 0, 0, 0, 1);
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
			advancedSolver(data);
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

				return resultR;
			}
			else {
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
				equationSolver(data);
				int i = 0, j = 0, z = 0;
				T* zeroR = getDynamicDoubleArray();
				T* zeroI = getDynamicDoubleArray();
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
					solveMath(value);
					zeroR[z] = resultR; zeroI[z] = resultI;
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
				solveMath(equation);
				if (abs(resultR) < 1E-2 && abs(resultI) < 1E-2) {
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
					return resultR;
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
			while (isSolved() == false && timesEvaluated < timesToEvaluate) {
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
				while (resultR != 0 && resultFR < (saveResultR * -1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0) {
					timesEvaluated++;
					xValuesR = resultFR; xValuesI = resultFI;
					solveMath(equation);
					if (resultR < 0) {
						do {
							timesEvaluated++;
							if (resultR < 0) {
								resultFR = resultFR + precisionR;
								xValuesR = resultFR; xValuesI = resultFI;
								solveMath(equation);
							}
							if (resultR > 0) {
								resultFR = resultFR - precisionR;
								precisionR = precisionR / 10;
								xValuesR = resultFR; xValuesI = resultFI;
								solveMath(equation);
							}
						} while (resultR != 0 && resultFR < (saveResultR * -1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
					}
					else {
						do {
							timesEvaluated++;
							if (resultR > 0) {
								resultFR = resultFR + precisionR;
								xValuesR = resultFR; xValuesI = resultFI;
								solveMath(equation);
							}
							else {
								if (resultR < 0) {
									resultFR = resultFR - precisionR;
									precisionR = precisionR / 10;
									xValuesR = resultFR; xValuesI = resultFI;
									solveMath(equation);
								}
							}
						} while (resultR != 0 && resultFR < (saveResultR * -1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
					}
					if (resultR == 0) {
						break;
					}
				}
				timesEvaluated++;
				if (retrySolver) {
					while (resultI != 0 && resultFI < (saveResultI * -1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0) {
						timesEvaluated++;
						xValuesR = resultFR; xValuesI = resultFI;
						solveMath(equation);
						if (resultI < 0) {
							do {
								timesEvaluated++;
								if (resultI < 0) {
									resultFI = resultFI + precisionI;
									xValuesR = resultFR; xValuesI = resultFI;
									solveMath(equation);
								}
								if (resultI > 0) {
									resultFI = resultFI - precisionI;
									precisionI = precisionI / 10;
									xValuesR = resultFR; xValuesI = resultFI;
									solveMath(equation);
								}
							} while (resultI != 0 && resultFI < (saveResultI * -1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
						}
						else {
							do {
								timesEvaluated++;
								if (resultI > 0) {
									resultFI = resultFI + precisionI;
									xValuesR = resultFR; xValuesI = resultFI;
									solveMath(equation);
								}
								else {
									if (resultI < 0) {
										resultFI = resultFI - precisionI;
										precisionI = precisionI / 10;
										xValuesR = resultFR; xValuesI = resultFI;
										solveMath(equation);
									}
								}
							} while (resultI != 0 && resultFI < (saveResultI * -1) && timesEvaluated < timesToEvaluate && timesEvaluated % interactions != 0);
						}
						if (resultI == 0) {
							break;
						}
					}
				}
			}
		}
		else {
			if (retrySolver_2 && retrySolver == (bool)false && retrySolver_3 == (bool)false) {
				xValuesR = 1E9; xValuesI = 0;
				solveMath(equation);
				T minMaxR = resultR, minMaxI = resultI;
				int i = 0, j = 0, interval = 499, c = 1, d = 0;
				int* x_values = getDynamicArray<int>(1000);
				T* y_valuesR = getDynamicArray<T>(1000);
				T* y_valuesI = getDynamicArray<T>(1000);
				int firstValueR = 0, secondValueR = 0, selected_X = 0;
				for (i = -interval; i < interval; i++) {
					xValuesR = (T)i; xValuesI = 0;
					solveMath(equation);
					x_values[j] = i;
					y_valuesR[j] = resultR;
					y_valuesI[j] = resultI;
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
							T negYR = solveMath(equation);
							T negYI = resultI;
							xValuesR = secondValueR; xValuesI = 0;
							T posYR = solveMath(equation);
							T posYI = resultI;
							T dividend = (((negYR + negYI) - (posYR + posYI)) * -1) / 2;
							division(dividend, 0, minMaxR, minMaxI);
							multiplication(resultR, resultI, -1, 0);
							sum(resultR, resultI, selected_X, 0);
							if (resultR > mINF && resultR<INF && resultI>mINF && resultI < INF) {
								resultFR = resultR; resultFI = resultI;
								if (physics == (bool)false) {
								}
								xValuesR = resultFR; xValuesI = resultFI;
								solveMath(equation);
								c++;
							}
						}
						d = i + 1;
					}
					i++;
				}
				xValuesR = resultFR; xValuesI = resultFI;
				solveMath(equation);
				_delete(x_values, "x_values");
				x_values = nullptr;
				_delete(y_valuesR, "y_valuesR");
				y_valuesR = nullptr;
				_delete(y_valuesI, "y_valuesI");
				y_valuesI = nullptr;
			}
		}
		if ((retrySolver == (bool)false && retrySolver_2 == (bool)false && retrySolver_3 == (bool)false && ((resultR > -1E-2 && resultR < 1E-2) == false || (resultI > -1E-2 && resultI < 1E-2) == false)) && equationSolverRunning == (bool)false) {
			retrySolver = true;
			solverRunning = true;
			solver(expression);
			resultFR = resultR; resultFI = resultI;
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
		if ((retrySolver && retrySolver_2 == (bool)false && retrySolver_3 == (bool)false && ((resultR > -1E-7 && resultR < 1E-7) == false || (resultI > -1E-7 && resultI < 1E-7) == false)) && equationSolverRunning == (bool)false) {
			retrySolver = false;
			retrySolver_2 = true;
			solverRunning = true;
			solver(expression);
			resultFR = resultR; resultFI = resultI;
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
		if ((retrySolver == (bool)false && retrySolver_2 && retrySolver_3 == (bool)false && ((resultR > -1 && resultR < 1) == false || (resultI > -1 && resultI < 1) == false)) && equationSolverRunning == (bool)false) {
			retrySolver_2 = false;
			retrySolver_3 = true;
			solverRunning = true;
			solver(expression);
			resultFR = resultR; resultFI = resultI;
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
			printf("\nCould not solve the expression: %s\n\n", notSolvedEquation);
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
	T initialAngle = (T)(M_PI / 2);
	xValuesR = initialAngle; xValuesI = 0;
	T xValueR = initialAngle, xValueI = 0, previousSolR = initialAngle, previousSolI = 0;
	int i = 0;
	T deltaxR = initialAngle, deltaxI = 0;
	char* toSolve = getDynamicCharArray("", "toSolve"); 	char* toHelp = getDynamicCharArray("", "toHelp");
	T fxDevR = 1, fxDevI = 0;
	replaceTimes = 0;
	replace("x", "res", expression);
	sprintf(toSolve, "%s", expressionF);
	solverRunning = true;
	T solR = 1, solI = 0;
	while (i < 175) {
		xValuesR = xValueR; xValuesI = xValueI;
		initialProcessor(toSolve, 0);
		T fxR = resultR, fxI = resultI;
		xValuesR = xValueR + deltaxR;
		xValuesI = xValueI + deltaxI;

		initialProcessor(toSolve, 0);
		T fxplusaR = resultR, fxplusaI = resultI;

		subtraction(fxplusaR, fxplusaI, fxR, fxI);
		division(resultR, resultI, deltaxR, deltaxI);
		if (resultR != 0 || resultI != 0) {
			fxDevR = resultR, fxDevI = resultI;
		}

		division(fxR, fxI, fxDevR, fxDevI);
		subtraction(xValueR, xValueI, resultR, resultI);
		if (abs(previousSolR - solR) < 1E-6 && abs(previousSolI - solI) < 1E-6) {
			T xR1, xR2, xI1, xI2, resR1, resR2, resI1, resI2;
			if (abs(resultR) < 1E-6)
			{
				resultR = 0;
			}
			if (abs(resultI) < 1E-6)
			{
				resultI = 0;
			}
			xR1 = quo(resultR); xI1 = quo(resultI);
			xR2 = resultR; xI2 = resultI;

			xValuesR = xR1; xValuesI = xI1;
			initialProcessor(toSolve, 0);
			resR1 = resultR; resI1 = resultI;
			xValuesR = xR2; xValuesI = xI2;
			initialProcessor(toSolve, 0);
			resR2 = resultR; resI2 = resultI;
			if (abs(resR2) >= abs(resR1) && abs(resI2) >= abs(resI1)) {
				solR = xR1; solI = xI1;

			}
			else {
				solR = xR2; solI = xI2;
			}
			break;

		}
		else {
			xValueR = resultR; xValueI = resultI;
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
				re_complex(saveResultR, saveResultI, 2 * M_PI, 0.0);
			}
			if (mode == 2) {
				re_complex(saveResultR, saveResultI, 360, 0.0);
			}
			if (mode == 3) {
				re_complex(saveResultR, saveResultI, 400, 0.0);
			}
			T savePossibleSolR = resultR, savePossibleSolI = resultI;
			xValuesR = savePossibleSolR; xValuesI = savePossibleSolI;
			initialProcessor(toSolve, 0);
			T fxR = resultR, fxI = resultI;
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

static std::complex<double> convertSolverGuessToInternalDomain(std::complex<double> guess, bool angularFunction) {
	if (!angularFunction) {
		return guess;
	}
	int angularMode = applySettings(4);
	if (angularMode == 2) {
		return guess * (M_PI / 180.0);
	}
	if (angularMode == 3) {
		return guess * (M_PI / 200.0);
	}
	return guess;
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
	const char* functions[] = { "sin", "cos", "tan", "sinh", "cosh", "tanh" };
	for (int functionIndex = 0; functionIndex < 6; ++functionIndex) {
		bool angularFunction = functionIndex < 3;
		std::string invertedSameFunctionArgument;
		if (extractSolverFunctionTargetMinusFunctionX(text, functions[functionIndex], invertedSameFunctionArgument)) {
			std::complex<double> argumentValue;
			if (evaluateSolverTargetExpression(invertedSameFunctionArgument, argumentValue)) {
				rootR = argumentValue.real();
				rootI = argumentValue.imag();
				return true;
			}
		}
		std::string prefix = std::string(functions[functionIndex]) + "(x)";
		if (text.compare(0, prefix.size(), prefix) != 0 || text.size() <= prefix.size()) {
			continue;
		}
		std::complex<double> preferredGuess(0.0, 0.0);
		bool hasPreferredGuess = false;
		std::string sameFunctionArgument;
		if (extractSolverSameFunctionArgument(text.substr(prefix.size()), functions[functionIndex], sameFunctionArgument)) {
			std::complex<double> argumentValue;
			if (evaluateSolverTargetExpression(sameFunctionArgument, argumentValue)) {
				preferredGuess = convertSolverGuessToInternalDomain(argumentValue, angularFunction);
				hasPreferredGuess = true;
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
			hasPreferredGuess ? preferredGuess : std::complex<double>(0.0, 0.0),
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
					rootR = x.real();
					rootI = x.imag();
					if (angularFunction) {
						int angularMode = applySettings(4);
						if (angularMode == 2) {
							rootR = rootR * 180.0 / M_PI;
							rootI = rootI * 180.0 / M_PI;
						}
						if (angularMode == 3) {
							rootR = rootR * 200.0 / M_PI;
							rootI = rootI * 200.0 / M_PI;
						}
					}
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

static char* getNormalizedSolverExpression(char* expression) {
	std::string normalized(expression == nullptr ? "" : expression);
	size_t position = 0;
	while ((position = normalized.find("((1000))", position)) != std::string::npos) {
		normalized.replace(position, 8, "(x)");
		position += 3;
	}
	position = 0;
	while ((position = normalized.find("(1000)", position)) != std::string::npos) {
		normalized.replace(position, 6, "x");
		position += 1;
	}
	position = 0;
	while ((position = normalized.find("_(1000)", position)) != std::string::npos) {
		normalized.replace(position, 7, "_x");
		position += 2;
	}
	return getDynamicCharArray(const_cast<char*>(normalized.c_str()), "normalizedSolverExpression");
}

template <typename T>
static T solveByNumericalDerivative(char* expression) {
	std::string equationTemplate(expression == nullptr ? "" : expression);
	char* evaluationExpression = getDynamicCharArray("", "evaluationExpression");
	T lastEvaluationI = (T)0;
	bool previousSolverRunning = solverRunning;
	solverRunning = true;
	auto evaluate = [&](T x) {
		std::ostringstream valueStream;
		valueStream << std::setprecision(30) << x;
		std::string value = valueStream.str();
		std::string concreteExpression;
		for (size_t index = 0; index < equationTemplate.size(); ++index) {
			if (equationTemplate[index] == 'x') {
				concreteExpression += "(";
				if (!value.empty() && value[0] == '-') {
					concreteExpression += "0";
				}
				concreteExpression += value;
				concreteExpression += ")";
			}
			else {
				concreteExpression += equationTemplate[index];
			}
		}
		sprintf(evaluationExpression, "%s", concreteExpression.c_str());
		initialProcessor<T>(evaluationExpression, (T)0);
		lastEvaluationI = precisionValueTo<T>(resultI);
		return precisionValueTo<T>(resultR);
	};
	T tolerance = (T)1E-7;
	T root = (T)0;
	bool found = false;

	T guesses[] = { (T)0, (T)1, (T)-1, (T)10, (T)-10 };
	for (int guessIndex = 0; guessIndex < 5 && !found; ++guessIndex) {
		T x = guesses[guessIndex];
		T delta = solverAbs(x) > (T)1 ? solverAbs(x) * (T)1E-3 : (T)1E-3;
		for (int iteration = 0; iteration < 20; ++iteration) {
			T fx = evaluate(x);
			if (solverAbs(fx) < tolerance && solverAbs(lastEvaluationI) < tolerance) {
				root = x;
				found = true;
				break;
			}
			T derivative = (evaluate(x + delta) - fx) / delta;
			if (solverAbs(derivative) < (T)1E-18) {
				delta *= (T)10;
				continue;
			}
			T next = x - fx / derivative;
			if (solverAbs((T)(next - x)) < tolerance) {
				x = next;
				if (solverAbs(evaluate(x)) < (T)1E-7 && solverAbs(lastEvaluationI) < (T)1E-7) {
					root = x;
					found = true;
				}
				break;
			}
			x = next;
			delta = solverAbs(x) > (T)1 ? solverAbs(x) * (T)1E-3 : (T)1E-3;
		}
	}

	if (!found) {
		T previousX = (T)0;
		T previousY = evaluate(previousX);
		if (solverAbs(previousY) < tolerance && solverAbs(lastEvaluationI) < tolerance) {
			root = previousX;
			found = true;
		}
		for (int direction = 0; !found && direction < 2; direction++) {
			previousX = (T)0;
			previousY = evaluate(previousX);
			for (int i = 1; i <= 100 && !found; i++) {
				T currentX = direction == 0 ? (T)i : (T)-i;
				T currentY = evaluate(currentX);
				if (solverAbs(currentY) < tolerance && solverAbs(lastEvaluationI) < tolerance) {
					root = currentX;
					found = true;
					break;
				}
				if ((previousY < (T)0 && currentY > (T)0) || (previousY > (T)0 && currentY < (T)0)) {
					T left = previousX;
					T right = currentX;
					T leftY = previousY;
					for (int iteration = 0; iteration < 80; iteration++) {
						T middle = (left + right) / (T)2;
						T middleY = evaluate(middle);
						if (solverAbs(middleY) < (T)1E-12) {
							left = middle;
							right = middle;
							break;
						}
						if ((leftY < (T)0 && middleY > (T)0) || (leftY > (T)0 && middleY < (T)0)) {
							right = middle;
						}
						else {
							left = middle;
							leftY = middleY;
						}
					}
					root = (left + right) / (T)2;
					found = true;
				}
				previousX = currentX;
				previousY = currentY;
			}
		}
	}
	if (!found) {
		resultR = (T)-765432;
		resultI = (T)234567;
		solverRunning = previousSolverRunning;
		_delete(evaluationExpression, "evaluationExpression");
		evaluationExpression = nullptr;
		return (T)-765432;
	}
	double rootAsDouble = precisionValueTo<double>(root);
	if (std::fabs(rootAsDouble - std::round(rootAsDouble)) < 1E-9) {
		root = (T)std::round(rootAsDouble);
	}
	resultR = root;
	resultI = (T)0;
	solverRunning = previousSolverRunning;
	_delete(evaluationExpression, "evaluationExpression");
	evaluationExpression = nullptr;
	return root;
}

template <>
double solver<double>(char* expression) {
	char* normalizedExpression = getNormalizedSolverExpression(expression);
	double rootR = 0.0, rootI = 0.0;
	std::string solverExpression(normalizedExpression != nullptr ? normalizedExpression : "");
	std::string reducedRationalProduct;
	if (reduceExactRationalProductExpression(solverExpression.c_str(), reducedRationalProduct)) {
		solverExpression = reducedRationalProduct;
	}
	std::complex<long double> complexLinearSolution(0.0L, 0.0L);
	if (trySolveSolverLinearExpressionComplex(solverExpression, complexLinearSolution) ||
		trySolveSolverLinearProductExpressionComplex(solverExpression, complexLinearSolution)) {
		resultR = (double)complexLinearSolution.real();
		resultI = (double)complexLinearSolution.imag();
		_delete(normalizedExpression, "normalizedSolverExpression");
		normalizedExpression = nullptr;
		return (double)complexLinearSolution.real();
	}
	if (trySolveLinearXExpression(normalizedExpression, rootR, rootI)) {
		resultR = rootR;
		resultI = rootI;
		_delete(normalizedExpression, "normalizedSolverExpression");
		normalizedExpression = nullptr;
		return rootR;
	}
	if (trySolveSimpleFunctionByDerivative(normalizedExpression, rootR, rootI)) {
		resultR = rootR;
		resultI = rootI;
		_delete(normalizedExpression, "normalizedSolverExpression");
		normalizedExpression = nullptr;
		return rootR;
	}
	double value = solveByNumericalDerivative<double>(normalizedExpression);
	_delete(normalizedExpression, "normalizedSolverExpression");
	normalizedExpression = nullptr;
	return value;
}

template <>
mp_float solver<mp_float>(char* expression) {
	char* normalizedExpression = getNormalizedSolverExpression(expression);
	double rootR = 0.0, rootI = 0.0;
	std::string solverExpression(normalizedExpression != nullptr ? normalizedExpression : "");
	std::string reducedRationalProduct;
	if (reduceExactRationalProductExpression(solverExpression.c_str(), reducedRationalProduct)) {
		solverExpression = reducedRationalProduct;
	}
	std::complex<long double> complexLinearSolution(0.0L, 0.0L);
	if (trySolveSolverLinearExpressionComplex(solverExpression, complexLinearSolution) ||
		trySolveSolverLinearProductExpressionComplex(solverExpression, complexLinearSolution)) {
		resultR = (mp_float)complexLinearSolution.real();
		resultI = (mp_float)complexLinearSolution.imag();
		_delete(normalizedExpression, "normalizedSolverExpression");
		normalizedExpression = nullptr;
		return (mp_float)complexLinearSolution.real();
	}
	if (trySolveLinearXExpression(normalizedExpression, rootR, rootI)) {
		resultR = rootR;
		resultI = rootI;
		_delete(normalizedExpression, "normalizedSolverExpression");
		normalizedExpression = nullptr;
		return (mp_float)rootR;
	}
	if (trySolveSimpleFunctionByDerivative(normalizedExpression, rootR, rootI)) {
		resultR = rootR;
		resultI = rootI;
		_delete(normalizedExpression, "normalizedSolverExpression");
		normalizedExpression = nullptr;
		return (mp_float)rootR;
	}
	mp_float value = solveByNumericalDerivative<mp_float>(normalizedExpression);
	_delete(normalizedExpression, "normalizedSolverExpression");
	normalizedExpression = nullptr;
	return value;
}

