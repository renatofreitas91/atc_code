

#include "stdafx.h"

int rasf = 0, maxLength = 0, vectorType = 0, check4Vector = 0, numVectorLines = 0, numVectorCols = 0, matrixMode = 0, previousAnsType = 0;
bool solving = true;

template<typename T>
std::string formatCoreFixedPrecisionValue(const T& value, int places) {
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(places) << value;
	return stream.str();
}

template<typename T>
int parseCorePlacesValue(char* places, T result1, T result2) {
	bool simpleInteger = abs((int)strlen(places)) > 0;
	for (int i = 0; i < abs((int)strlen(places)); i++) {
		if (places[i] < '0' || places[i] > '9') {
			simpleInteger = false;
			break;
		}
	}
	if (simpleInteger) {
		return atoi(places);
	}
	PrecisionValue savedResultR = resultR;
	PrecisionValue savedResultI = resultI;
	int value = (int)precisionValueTo<double>(solveNow<T>(places, result1, result2));
	resultR = savedResultR;
	resultI = savedResultI;
	return value;
}

static void normalizeMainCoreBooleanInfinityConstants(char* expression) {
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

static void normalizeMainCoreScientificNotation(char* expression) {
	if (expression == nullptr || abs((int)strlen(expression)) == 0) {
		return;
	}
	std::string source(expression);
	std::string normalized;
	normalized.reserve(source.size());
	for (size_t i = 0; i < source.size();) {
		size_t start = i;
		bool startsNumber = std::isdigit((unsigned char)source[i]) || source[i] == '.' ||
			(source[i] == '_' && i + 1 < source.size() && (std::isdigit((unsigned char)source[i + 1]) || source[i + 1] == '.'));
		if (!startsNumber) {
			normalized += source[i++];
			continue;
		}
		size_t mantissaStart = i;
		if (source[i] == '_') {
			i++;
		}
		bool hasMantissaDigit = false;
		while (i < source.size() && (std::isdigit((unsigned char)source[i]) || source[i] == '.')) {
			if (std::isdigit((unsigned char)source[i])) {
				hasMantissaDigit = true;
			}
			i++;
		}
		if (!hasMantissaDigit || i >= source.size() || source[i] != 'E') {
			normalized.append(source, start, i - start);
			continue;
		}
		size_t exponentMarker = i++;
		size_t exponentStart = i;
		if (i < source.size() && (source[i] == '+' || source[i] == '-' || source[i] == '_')) {
			i++;
		}
		size_t exponentDigitsStart = i;
		while (i < source.size() && std::isdigit((unsigned char)source[i])) {
			i++;
		}
		if (exponentDigitsStart == i) {
			normalized.append(source, start, exponentMarker - start + 1);
			i = exponentStart;
			continue;
		}
		std::string mantissa = source.substr(mantissaStart, exponentMarker - mantissaStart);
		std::string exponent = source.substr(exponentStart, i - exponentStart);
		if (!exponent.empty() && exponent[0] == '+') {
			exponent.erase(0, 1);
		}
		if (!exponent.empty() && exponent[0] == '_') {
			exponent[0] = '-';
		}
		if (!exponent.empty() && exponent[0] == '-') {
			exponent[0] = '_';
		}
		normalized += "(" + mantissa + "*10^(" + exponent + "))";
	}
	if (normalized.size() < (size_t)DIM) {
		sprintf(expression, "%s", normalized.c_str());
	}
}

static std::string compactAtcExpression(const char* expression) {
	std::string compactExpression;
	if (expression == nullptr) {
		return compactExpression;
	}
	for (size_t index = 0; index < strlen(expression); index++) {
		if (expression[index] != ' ' && expression[index] != '\t') {
			compactExpression.push_back(expression[index]);
		}
	}
	return compactExpression;
}

template<typename T>
static bool handleDirectInfinityExpression(const char* expression, FILE* fout, int isFromMain) {
	std::string compactExpression = compactAtcExpression(expression);
	if (compactExpression != "INF" && compactExpression != "_INF" && compactExpression != "INF/INF") {
		return false;
	}
	T directResult = (T)0;
	const char* directText = "0";
	if (compactExpression == "INF") {
		directResult = std::numeric_limits<T>::infinity();
		directText = "INF";
	}
	if (compactExpression == "_INF") {
		directResult = -std::numeric_limits<T>::infinity();
		directText = "-INF";
	}
	if (compactExpression == "INF/INF") {
		directResult = (T)1;
		directText = "1";
	}
	resultR = directResult;
	resultI = (T)0;
	ans[rf] = directResult;
	ansI[rf] = (T)0;
	ansRV = directResult;
	ansIV = (T)0;
	previousAnsType = 0;
	sprintf(saveMatrixAns, "");
	sprintf(ansMatrices[rf], "");
	if (isFromMain == 1) {
		printf("#%d=%s\n", rf, directText);
	}
	if (fout != NULL) {
		fprintf(fout, "#%d=%s\n", rf, directText);
	}
	rf++;
	return true;
}

char* saveArithTrig = getDynamicCharArray("", "saveArithTrig"), * actualTime = getDynamicCharArray("", "actualTime"), * siPref = getDynamicCharArray("", "siPref"), * verboseRes = getDynamicCharArray("", "verboseRes"), * saveExpressionFF = getDynamicCharArray("", "saveExpressionFF"), * renamedVariable = getDynamicCharArray("", "renamedVariable"), * vectorString = getDynamicCharArray("", "vectorString"), * saveMatrixAns = getDynamicCharArray("", "saveMatrixAns"), * matrixVariable = getDynamicCharArray("", "matrixVariable");

static bool extractSolverArgumentForFastPath(const char* expression, std::string& argument) {
	if (expression == nullptr) {
		return false;
	}
	std::string text(expression);
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

static std::string stripSolverFastPathOuterParentheses(const std::string& source) {
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

static bool selectFirstLinearSolverFactor(const std::string& expression, std::string& factor) {
	std::string text = stripSolverFastPathOuterParentheses(expression);
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
				std::string candidate = stripSolverFastPathOuterParentheses(text.substr(1, i - 1));
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

template<typename T>
T main_core(char* arithTrig, char* fTrig, FILE* fout, char* path, T result1, T result2, int isFromMain) {
	if (rf > 0) {
		ansRV = ans[rf - 1];
		ansIV = ansI[rf - 1];
	}
	fflush(NULL);
	verbose = 0;
	verified = 0;
	rasf = 0;
	resultR = 0; resultI = 0;
	int txt = 0, var = 0, str = 0, s = 0, i = 0, space = 0, v = 0, j = 0, valGet = 0, h = 0, run_del_space = 1, strIndex = 0, StringManual = 0;
	char* variable = getDynamicCharArray("", "variable");  char* getVar = getDynamicCharArray("", "getVar"); char* savefTrig = getDynamicCharArray(" ", "savefTrig");
	bool command = 0, cleanhistory = 0;
	txt = 0;
	valid = 1;
	validVar = 1;
	str = 0;
	nPlaces = 0;
	sprintf(savefTrig, "%s", fTrig);
	replaceTimes = 0;
	char* withoutSpaces = getDynamicCharArray("", "withoutSpaces");
	replaceTimes = 0;
	if (isContained(" ", arithTrig)) {
		replaceTimes = 0;
		replace(" ", "", arithTrig);
		sprintf(withoutSpaces, "%s", expressionF);
	}
	else {
		sprintf(withoutSpaces, "%s", arithTrig);
	}
	T solverFastPathResult = 0;
	if (!solverRunning && !equationSolverRunning && tryEvaluateSolverFastPath(withoutSpaces, solverFastPathResult)) {
		convertComplex2Exponential(resultR, resultI);
		if (abs(precisionValueTo<double>(resultI)) < 1E-18) {
			sprintf(arithTrig, "%s", respR);
		}
		else if (resultI > 0) {
			sprintf(arithTrig, "(%s+%si)", respR, respI);
		}
		else {
			sprintf(arithTrig, "(%s%si)", respR, respI);
		}
		sprintf(fTrig, "%s", arithTrig);
		sprintf(withoutSpaces, "%s", arithTrig);
	}
	std::string solverArgumentForFastPath;
	if (extractSolverArgumentForFastPath(withoutSpaces, solverArgumentForFastPath)) {
		std::string reducedSolverArgument;
		std::string linearSolverFactor;
		std::string solverFactorSource = solverArgumentForFastPath;
		if (reduceExactRationalProductExpression(solverArgumentForFastPath.c_str(), reducedSolverArgument)) {
			solverFactorSource = reducedSolverArgument;
		}
		if (selectFirstLinearSolverFactor(solverFactorSource, linearSolverFactor)) {
			std::string normalizedSolver = "solver(" + linearSolverFactor + ")";
			if (normalizedSolver.size() < (size_t)DIM) {
				sprintf(arithTrig, "%s", normalizedSolver.c_str());
				sprintf(fTrig, "%s", normalizedSolver.c_str());
				sprintf(withoutSpaces, "%s", normalizedSolver.c_str());
				T selectedSolverFastPathResult = 0;
				if (tryEvaluateSolverFastPath(withoutSpaces, selectedSolverFastPathResult)) {
					convertComplex2Exponential(resultR, resultI);
					if (abs(precisionValueTo<double>(resultI)) < 1E-18) {
						sprintf(arithTrig, "%s", respR);
					}
					else if (resultI > 0) {
						sprintf(arithTrig, "(%s+%si)", respR, respI);
					}
					else {
						sprintf(arithTrig, "(%s%si)", respR, respI);
					}
					sprintf(fTrig, "%s", arithTrig);
					sprintf(withoutSpaces, "%s", arithTrig);
				}
			}
		}
	}
	int getString = 0;
	if (arithTrig[0] == 'g' && arithTrig[1] == 'e' && arithTrig[2] == 't' && arithTrig[3] == '(') {
		i = 4;
		for (i = 4; i < abs((int)strlen(arithTrig)); i++) {
			if (arithTrig[i] == ')') {
				valGet = 1;
				break;
			}
		}
		if (valGet == 1) {
			char* getVarName = getDynamicCharArray("", "getVarName");

			h = 0;
			i = 4;
			while (arithTrig[i] != ')' && i < abs((int)strlen(arithTrig))) {
				getVarName[h] = arithTrig[i];
				h++; i++;
			}
			getVarName[h] = '\0';
			strIndex = 0;
			for (int ks = 0; ks < abs((int)strlen(getVarName)); ks++) {
				if (verifyNumber(getVarName[ks]) || verifyLetter(getVarName[ks])) {
					strIndex++;
				}
			}
			if (strIndex == abs((int)strlen(getVarName))) {
				gets_s(getVar, DIM);
				arithTrig[0] = '\0';
			}
			else {
				puts("\nTo create string variables only letters from latin alphabet and digits 0-9 can be used.\nTo create numerical variables only letters from latin alphabet can be used.");
				command = 1;
				arithTrig[0] = '\0';
			}
			sprintf(arithTrig, "%s=%s", getVarName, getVar);
			if (isContained("\"", arithTrig)) {
				getString = 1;
			}
			command = 0;
			if (getVarName != nullptr) {
				_delete(getVarName, "getVarName"); getVarName = nullptr;
			}
		}
		else {
			puts("\nError in syntax in get function.\n");
			command = 1;
		}

	}
	if (isContained("opentxt", withoutSpaces) == false && isContained(":\\", withoutSpaces) == false && (isContained("=\"", withoutSpaces) || isContained("=replace(", withoutSpaces) || isContained("=replacebyindex(", withoutSpaces) || isContained("=deletexoccurrences(", withoutSpaces))) {
		StringManual = 1;
		if (isContained("=deletexoccurrences(", arithTrig)) {
			renamer(arithTrig);
			sprintf(arithTrig, "%s", expressionF);
			int i = strEnd, j = 0;
			char* to_find = getDynamicCharArray("", "to_find"); char* value = getDynamicCharArray("", "value"); char* string = getDynamicCharArray("", "string");
			if (countOccurrences("\\", arithTrig) == 2) {
				while (arithTrig[i] != '\\') {
					to_find[j] = arithTrig[i];
					j++; i++;
				}
				to_find[j] = '\0';
				stringVariableToString(to_find);
				sprintf(to_find, "%s", variableSTring);
				i++;
				j = 0;
				while (arithTrig[i] != '\\') {
					string[j] = arithTrig[i];
					j++; i++;
				}
				string[j] = '\0';
				stringVariableToString(string);
				sprintf(string, "%s", variableSTring);
				i++;
				j = 0;
				while (arithTrig[i] != ')' && i < abs((int)strlen(arithTrig))) {
					value[j] = arithTrig[i];
					j++; i++;
				}
				value[j] = '\0';
				int times = (int)precisionValueTo<double>(solveMath<T>(value));
				replaceTimes = 0;
				deleteXOccurrences(to_find, string, times);
				replaceTimes = 0;
				char* stringObtained = getDynamicCharArray("", "stringObtained");
				sprintf(stringObtained, "%s", expressionF);
				char* variableString = getDynamicCharArray("", "variableString");
				int p = 0;
				i = 0;
				while (arithTrig[i] != '=') {
					variableString[p] = arithTrig[i];
					p++; i++;
				}
				variableString[p] = '\0';
				int hk = variableValidator<T>(variableString);
				char* variableFeedback = getDynamicCharArray("", "variableFeedback");
				if (hk == 1) {
					processVariable<T>(revariable);
					sprintf(variableString, "%s", revariable);
					stringVariableController(variableString, stringObtained);
				}
				if (hk == 2) {
					sprintf(variableFeedback, "\n==> Your variable was renamed to \"%s\". <==\n\n",
						revariable);
					sprintf(variableString, "%s", revariable);
					stringVariableController(variableString, stringObtained);
				}
				if (hk == 0) {
					sprintf(variableFeedback,
						"\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
					var = 0;
				}
				puts(variableFeedback);
				stringVariableController(variableString, stringObtained);
				_delete(stringObtained, "stringObtained"); stringObtained = nullptr;
				_delete(variableString, "variableString"); variableString = nullptr;
				_delete(variableFeedback, "variableFeedback"); variableFeedback = nullptr;
			}
			else {
				puts("\nError: Please use two \"\\\" to separate the variables.\n");
			}
			arithTrig[0] = '\0';
			_delete(to_find, "to_find"); to_find = nullptr;
			_delete(value, "value"); value = nullptr;
			_delete(string, "string"); string = nullptr;
		}
		else {
			if (isContained("=replacebyindex(", arithTrig)) {
				renamer(arithTrig);
				sprintf(arithTrig, "%s", expressionF);
				int i = strEnd, j = 0;
				char* to_find = getDynamicCharArray("", "to_find"); char* replacement = getDynamicCharArray("", "replacement"); char* value = getDynamicCharArray("", "value"); char* string = getDynamicCharArray("", "string");
				if (countOccurrences("\\", arithTrig) == 4) {
					while (arithTrig[i] != '\\') {
						to_find[j] = arithTrig[i];
						j++; i++;
					}
					to_find[j] = '\0';
					renamer(to_find);
					sprintf(to_find, "%s", expressionF);
					stringVariableToString(to_find);
					sprintf(to_find, "%s", variableSTring);
					i++;
					j = 0;
					while (arithTrig[i] != '\\') {
						replacement[j] = arithTrig[i];
						j++; i++;
					}
					replacement[j] = '\0';
					renamer(replacement);
					sprintf(replacement, "%s", expressionF);
					stringVariableToString(replacement);
					sprintf(replacement, "%s", variableSTring);
					i++;
					j = 0;
					while (arithTrig[i] != '\\') {
						string[j] = arithTrig[i];
						j++; i++;
					}
					string[j] = '\0';
					renamer(string);
					sprintf(string, "%s", expressionF);
					stringVariableToString(string);
					sprintf(string, "%s", variableSTring);
					i++;
					j = 0;
					while (arithTrig[i] != '\\') {
						value[j] = arithTrig[i];
						j++; i++;
					}
					value[j] = '\0';
					int index = (int)precisionValueTo<double>(solveMath<T>(value));
					j = 0;
					while (arithTrig[i] != ')' && i < abs((int)strlen(arithTrig))) {
						value[j] = arithTrig[i];
						j++; i++;
					}
					value[j] = '\0';
					replaceTimes = (int)precisionValueTo<double>(solveMath<T>(value));
					replaceByIndex(to_find, replacement, string, index);
					replaceTimes = 0;
					char* stringObtained = getDynamicCharArray("", "stringObtained");
					sprintf(stringObtained, "%s", expressionF);
					char* variableString = getDynamicCharArray("", "variableString");
					int p = 0;
					i = 0;
					while (arithTrig[i] != '=') {
						variableString[p] = arithTrig[i];
						p++; i++;
					}
					variableString[p] = '\0';
					int hk = variableValidator<T>(variableString);
					char* variableFeedback = getDynamicCharArray("", "variableFeedback");
					if (hk == 1) {
						processVariable<T>(revariable);
						sprintf(variableString, "%s", revariable);
						stringVariableController(variableString, stringObtained);
					}
					if (hk == 2) {
						sprintf(variableFeedback, "\n==> Your variable was renamed to \"%s\". <==\n\n",
							revariable);
						sprintf(variableString, "%s", revariable);
						stringVariableController(variableString, stringObtained);
					}
					if (hk == 0) {
						sprintf(variableFeedback,
							"\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
						var = 0;
					}
					puts(variableFeedback);
					stringVariableController(variableString, stringObtained);
					_delete(stringObtained, "stringObtained"); stringObtained = nullptr;
					_delete(variableString, "variableString"); variableString = nullptr;
					_delete(variableFeedback, "variableFeedback"); variableFeedback = nullptr;
				}
				else {
					puts("\nError: Please use four \"\\\" to separate the variables.\n");
				}
				arithTrig[0] = '\0';
				_delete(to_find, "to_find"); to_find = nullptr;
				_delete(replacement, "replacement"); replacement = nullptr;
				_delete(value, "value"); value = nullptr;
				_delete(string, "string"); string = nullptr;
			}
			else {
				if (isContained("=replace(", arithTrig)) {
					renamer(arithTrig);
					sprintf(arithTrig, "%s", expressionF);
					int i = strEnd, j = 0;
					char* to_find = getDynamicCharArray("", "to_find"); char* replacement = getDynamicCharArray("", "replacement"); char* value = getDynamicCharArray("", "value"); char* string = getDynamicCharArray("", "string");
					if (countOccurrences("\\", arithTrig) == 3) {
						while (arithTrig[i] != '\\') {
							to_find[j] = arithTrig[i];
							j++; i++;
						}
						to_find[j] = '\0';
						renamer(to_find);
						sprintf(to_find, "%s", expressionF);
						stringVariableToString(to_find);
						sprintf(to_find, "%s", variableSTring);
						i++;
						j = 0;
						while (arithTrig[i] != '\\') {
							replacement[j] = arithTrig[i];
							j++; i++;
						}
						replacement[j] = '\0';
						renamer(replacement);
						sprintf(replacement, "%s", expressionF);
						stringVariableToString(replacement);
						sprintf(replacement, "%s", variableSTring);
						i++;
						j = 0;
						while (arithTrig[i] != '\\') {
							string[j] = arithTrig[i];
							j++; i++;
						}
						string[j] = '\0';
						renamer(string);
						sprintf(string, "%s", expressionF);
						stringVariableToString(string);
						sprintf(string, "%s", variableSTring);
						i++;
						j = 0;
						while (arithTrig[i] != ')' && i < abs((int)strlen(arithTrig))) {
							value[j] = arithTrig[i];
							j++; i++;
						}
						value[j] = '\0';
						replaceTimes = (int)precisionValueTo<double>(solveMath<T>(value));
						replace(to_find, replacement, string);
						replaceTimes = 0;
						char* stringObtained = getDynamicCharArray("", "stringObtained");
						sprintf(stringObtained, "%s", expressionF);
						char* variableString = getDynamicCharArray("", "variableString");
						int p = 0;
						i = 0;
						while (arithTrig[i] != '=') {
							variableString[p] = arithTrig[i];
							p++; i++;
						}
						variableString[p] = '\0';
						int hk = variableValidator<T>(variableString);
						char* variableFeedback = getDynamicCharArray("", "variableFeedback");
						if (hk == 1) {
							processVariable<T>(revariable);
							sprintf(variableString, "%s", revariable);
							stringVariableController(variableString, stringObtained);
						}
						if (hk == 2) {
							sprintf(variableFeedback, "\n==> Your variable was renamed to \"%s\". <==\n\n",
								revariable);
							sprintf(variableString, "%s", revariable);
							stringVariableController(variableString, stringObtained);
						}
						if (hk == 0) {
							sprintf(variableFeedback,
								"\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
							var = 0;
						}
						stringVariableController(variableString, stringObtained);
						_delete(stringObtained, "stringObtained"); stringObtained = nullptr;
						_delete(variableString, "variableString"); variableString = nullptr;
						_delete(variableFeedback, "variableFeedback"); variableFeedback = nullptr;
					}
					else {
						puts("\nError: Please use three \"\\\" to separate the variables.\n");
					}
					arithTrig[0] = '\0';
					_delete(to_find, "to_find"); to_find = nullptr;
					_delete(replacement, "replacement"); replacement = nullptr;
					_delete(value, "value"); value = nullptr;
					_delete(string, "string"); string = nullptr;
				}
			}
		}
	}
	sprintf(withoutSpaces, "");
	for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
		if (arithTrig[i] == '=' && arithTrig[i + 1] == '"') {
			str = 0;
			int p = 0;
			char* variableString = getDynamicCharArray("", "variableString");
			i = 0;
			while (arithTrig[i] != '=') {
				variableString[p] = arithTrig[i];
				p++; i++;
			}
			variableString[p] = '\0';
			i++;
			char* string = getDynamicCharArray("", "string");
			p = 0;
			while (i < abs((int)strlen(arithTrig))) {
				string[p] = arithTrig[i];
				i++;
				p++;
			}
			string[p] = '\0';
			replaceTimes = 0;
			if (isContained("\"", string)) {
				replace("\"", "", string);
				sprintf(string, "%s", expressionF);
			}
			p = 0;
			while (verifyLetter(variableString[p])) {
				p++;
			}
			p++;
			int hk = variableValidator<T>(variableString);
			char* variableFeedback = getDynamicCharArray("", "variableFeedback");
			if (p == abs((int)strlen(variableString))) {
				char* toReplace = getDynamicCharArray("", "toReplace");
				sprintf(toReplace, "%s=", variableString);
				replace(toReplace, "", arithTrig);
				sprintf(arithTrig, "%s", expressionF);
				puts(" ");
				_delete(toReplace, "toReplace"); toReplace = nullptr;
			}

			if (hk == 1) {
				processVariable<T>(revariable);
				sprintf(variableString, "%s", revariable);
				stringVariableController(variableString, string);
			}
			if (hk == 2) {
				sprintf(variableFeedback, "\n==> Your variable was renamed to \"%s\". <==\n\n",
					revariable);
				sprintf(variableString, "%s", revariable);
				stringVariableController(variableString, string);
			}
			if (hk == 0) {
				sprintf(variableFeedback,
					"\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
				var = 0;
			}
			puts(variableFeedback);
			sprintf(variableString, "%s", revariable);
			stringVariableController(variableString, string);
			_delete(variableString, "variableString"); variableString = nullptr;
			_delete(string, "string"); string = nullptr;
			_delete(variableFeedback, "variableFeedback"); variableFeedback = nullptr;
		}
	}
	if (isContained("getposvalue(", arithTrig) && arithTrig[0] == 'g' && 0 == strStart) {
		char* getVarName = getDynamicCharArray("", "getVarName");

		i = strEnd;
		for (i; i < abs((int)strlen(arithTrig)); i++) {
			if (arithTrig[i] == ')') {
				valGet = 1;
				break;
			}
		}
		if (valGet == 1) {
			h = 0;
			i = strEnd;
			while (arithTrig[i] != ')' && i < abs((int)strlen(arithTrig))) {
				getVarName[h] = arithTrig[i];
				h++; i++;
			}
			getVarName[h] = '\0';

			strIndex = 0;
			for (int ks = 0; ks < abs((int)strlen(getVarName)); ks++) {
				if (verifyLetter(getVarName[ks])) {
					strIndex++;
				}
			}
			T value;
			if (strIndex == abs((int)strlen(getVarName))) {
				value = getPosValue<T>();
			}
			else {
				puts("\nTo create variables only letters from latin alphabet can be used.");
				command = 1;
				arithTrig[0] = '\0';
			}
			sprintf(arithTrig, "%s=%s", getVarName, convert2Exponential(value));
			if (isContained("-", arithTrig)) {
				replaceTimes = 0;
				replace("-", "_", arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
			command = 0;
			if (getVarName != nullptr) {
				_delete(getVarName, "getVarName"); getVarName = nullptr;
			}
		}
		else {
			puts("\nError in syntax in get function.\n");
			command = 1;
			arithTrig[0] = '\0';
		}

	}
	variable[0] = '\0';
	if (!isContained("opentxt", arithTrig) && !isContained("open txt", arithTrig)) {
		for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == ':' && arithTrig[i + 1] == '\\') {
				txt = 1;
			}
		}
	}



	for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
		if (arithTrig[i] == '=' && arithTrig[i + 1] != '=' && arithTrig[i + 1] != '!') {
			var = 1;
			if (valGet == 1) {
				puts(" ");
			}
		}

		if (arithTrig[i] == '\"' && arithTrig[abs((int)strlen(arithTrig)) - 1] == '\"' && txt != 1) {
			str = 1;
		}
		else {
			if ((arithTrig[i - 6] == 'p' && arithTrig[i - 5] == 'r' && arithTrig[i - 4] == 'i' && arithTrig[i - 3] == 'n' && arithTrig[i - 2] == 't' && arithTrig[i - 1] == '(') == true) {
				run_del_space = 0;
			}
		}
	}
	if (txt == 1) {
		int p = 0;
		char* pathName = getDynamicCharArray("", "pathName");
		if (var == 1) {
			var = 0;
			while (arithTrig[p] != '=') {
				pathName[p] = arithTrig[p];
				p++;
			}
			pathName[p] = '\0';
			for (p = 0; pathName[p] != ' ' && pathName[p] != ')' && p < abs((int)strlen(pathName)); p++);
			if (p == abs((int)strlen(pathName))) {
				int lenPath = abs((int)strlen(pathName)) + 1;
				for (p = lenPath; p < abs((int)strlen(arithTrig)); p++) {
					arithTrig[p - lenPath] = arithTrig[p];
				}
				arithTrig[p - lenPath] = '\0';
				pathNameController(pathName, arithTrig);
			}
			else {
				printf("\n==> Invalid abbreviation! <==\n\n");
				fprintf(fout, "\n==> Invalid abbreviation! <==\n\n");
				arithTrig[0] = '\0';
			}
		}
		if (0 < abs((int)strlen(arithTrig))) {
			command = 1;
			bool toWrite = processTxt<T>(arithTrig, rf);
			fout = fopen(path, "a+");
			if (toWrite) {
				printf("\n==> Close the file with the answers to continue. <==\n\n");
				fputs("\n==> Close the file with the answers to continue. <==\n", fout);
				openTxt();
			}
			if (abs((int)strlen(arithTrig)) >= 1) {
				arithTrig[0] = '\0';
			}
		}
		_delete(pathName, "pathName"); pathName = nullptr;
	}
	if (str == 1 || getString == 1) {
		int p = 0;
		char* variableString = getDynamicCharArray("", "variableString");
		p = 0;
		if (var == 1 && StringManual == 0) {
			var = 0;
			while (arithTrig[p] != '=') {
				variableString[p] = arithTrig[p];
				p++;
			}
			variableString[p] = '\0';
			for (p = 0; variableString[p] != ' ' && variableString[p] != ')' && p < abs((int)strlen(variableString)) && p < abs((int)strlen(variableString)); p++);
			if (strIndex == abs((int)strlen(variableString))) {
				int lenStr = abs((int)strlen(variableString)) + 1;
				p++;
				if (arithTrig[lenStr] == '\"') {
					arithTrig[p - lenStr] = arithTrig[p];
					lenStr++;
					p++;
				}
				for (p = lenStr; p < abs((int)strlen(arithTrig)) && arithTrig[p] != '\"' && p < abs((int)strlen(arithTrig)); p++) {
					arithTrig[p - lenStr] = arithTrig[p];
				}
				arithTrig[p - lenStr] = '\0';
				p = 0;
				while (verifyLetter(variableString[p])) {
					p++;
				}
				int hk = variableValidator<T>(variableString);
				char* variableFeedback = getDynamicCharArray("", "variableFeedback");
				if (hk == 1) {
					processVariable<T>(revariable);
					sprintf(variableString, "%s", revariable);
					stringVariableController(variableString, arithTrig);
				}
				if (hk == 2) {
					sprintf(variableFeedback, "\n==> Your variable was renamed to \"%s\". <==\n\n",
						revariable);
					sprintf(variableString, "%s", revariable);
					stringVariableController(variableString, arithTrig);
				}
				if (hk == 0) {
					sprintf(variableFeedback,
						"\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
					var = 0;
				}
				stringVariableController(variableString, arithTrig);
				puts(variableFeedback);
				if (valGet == 0) {
					puts(" ");
				}
				_delete(variableFeedback, "variableFeedback"); variableFeedback = nullptr;

			}
			else {
				if (isFromMain == 1) {
					printf("\n==> Invalid string name! Only letters from latin alphabet and digits 0-9 can be used. <==\n\n");
				}
				fprintf(fout, "\n==> Invalid string name! Only letters from latin alphabet and digits 0-9 can be used. <==\n\n");
				arithTrig[0] = '\0';
			}
		}
		if (0 < abs((int)strlen(arithTrig))) {
			command = 1;
			arithTrig[0] = '\0';
		}
		_delete(variableString, "variableString"); variableString = nullptr;
	}

	else {
		normalizeMainCoreBooleanInfinityConstants(arithTrig);
		if (abs((int)strlen(arithTrig)) > 0) {
			i = abs((int)strlen(arithTrig));
			arithTrig[i] = '+'; arithTrig[i + 1] = '0'; arithTrig[i + 2] = '\0';
		}
		verify = 0;
		for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
			if (arithTrig[s] == 'B' || arithTrig[s] == 'O' || arithTrig[s] == 'H' || arithTrig[s] == '_' || arithTrig[s] == '{' || arithTrig[s] == '(' || arithTrig[s] == '+' || arithTrig[s] == '-' || arithTrig[s] == '*' || arithTrig[s] == '/' || arithTrig[s] == '^' || arithTrig[s] == '0' || arithTrig[s] == '1' || arithTrig[s] == '2' || arithTrig[s] == '3' || arithTrig[s] == '4' || arithTrig[s] == '5' || arithTrig[s] == '6' || arithTrig[s] == '7' || arithTrig[s] == '8' || arithTrig[s] == '9' || (arithTrig[s] == 'r' && arithTrig[s + 1] == 'e' && arithTrig[s + 2] == 's') || (arithTrig[s] == 'a' && arithTrig[s + 1] == 'n' && arithTrig[s + 2] == 's') || (arithTrig[s] == 'e' && ((arithTrig[s + 1] == 'e' || arithTrig[s + 1] == '\0' && s == 0 || arithTrig[s + 1] == ')' || arithTrig[s + 1] == 'p' || arithTrig[s - 1] == '_') || (arithTrig[s - 1] == 'e' || arithTrig[s - 1] == '(' || arithTrig[s - 1] == 'i' && arithTrig[s - 2] != 't'))) || (arithTrig[s] == 'p' && arithTrig[s + 1] == 'i' && ((arithTrig[s + 2] == 'e' || arithTrig[s + 2] == '\0' && s == 0 || arithTrig[s + 2] == ')' || arithTrig[s + 2] == 'p' || arithTrig[s - 1] == '_') || (arithTrig[s - 1] == 'e' || arithTrig[s - 1] == '(' || arithTrig[s - 1] == 'i')))) {
				verify = 1;
			}
		}
		if (var == 1) {
			for (i = 0; arithTrig[i] != '='; i++) {
				if (arithTrig[i] == ' ') {
					v = 1;
				}
			}
			i++;
			if (arithTrig[i] == '+' && arithTrig[i + 1] == '0' && arithTrig[i + 2] == '\0') {
				verify = 0;
				var = 0;
			}
		}
		bool isFunction = atcFunctions(arithTrig);
		if (isFunction == false) {
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (arithTrig[i] == ' ') {
					space = 1;
					break;
				}
				else {
					space = 0;
				}
			}
			if (space == 1 && run_del_space == 1) {
				while (space == 1) {
					for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
						if (arithTrig[i] == ' ') {
							j = i;
							while (i < abs((int)strlen(arithTrig))) {
								arithTrig[i] = arithTrig[i + 1];
								i++;
							}
							i = j;
						}
					}
					for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
						if (arithTrig[i] == ' ') {
							space = 1;
							break;
						}
						else {
							space = 0;
						}
					}

				}
			}
		}
		if (fout != NULL) {
			fclose(fout);
		}
		fout = NULL;
		while (fout == NULL) {
			fout = fopen(path, "a+");
		}
		fprintf(fout, ">%s\n", savefTrig);

		if (handleDirectInfinityExpression<T>(savefTrig, fout, isFromMain)) {
			command = true;
			arithTrig[0] = '\0';
		}
		else {
			command = commands<double>(arithTrig, path, precisionValueTo<double>((PrecisionValue)result1), precisionValueTo<double>((PrecisionValue)result2), fout);
		}

		if (command == (bool)false && continu && abs((int)strlen(arithTrig)) > 0) {
			main_sub_core(arithTrig, fout, verify, path, txt, variable, v, j, result1, result2, isFromMain, var, valGet, command);
			sprintf(arithTrig, ""); sprintf(fTrig, ""); arithTrig[0] = '\0'; fTrig[0] = '\0';
		}

		if (fout != NULL) {
			fclose(fout);
		}
	}
	if (variable != nullptr) {

		_delete(variable, "variable"); variable = nullptr;
	}

	if (getVar != nullptr) {
		_delete(getVar, "getVar"); getVar = nullptr;
	}
	if (savefTrig != nullptr) {
		_delete(savefTrig, "savefTrig"); savefTrig = nullptr;
	}
	_delete(withoutSpaces, "withoutSpaces"); withoutSpaces = nullptr;
	return result1;
}
template <typename T>
T main_sub_core(char* arithTrig, FILE* fout, int verify, char* path, int txt, char* variable, int v, int j, T result1, T result2, int isFromMain, int var, int valGet, int command) {
	int vectorType = 0;
	char* vectorString = getDynamicCharArray("", "vectorString");
	FILE* open = NULL;
	if (isContained("solver", arithTrig)) {
		if (isContainedByIndex("-x", arithTrig, 1)) {
			replace("-x", "+_x", arithTrig);
			sprintf(arithTrig, "%s", expressionF);
		}
	}
	int  g = 0, Dimensions = 2, Window = 3, r = 0, i = 0, s = 0;
	char* exit = getDynamicCharArray("", "exit"); char res = ' '; char* varLetters = getDynamicCharArray("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", "varLetters");
	char* saveArithTr = getDynamicCharArray("", "saveArithTr");
	if (!solverRunning && !equationSolverRunning) {
		res = arithTrig[0];
		if (res == '+' || res == '-' || res == '/' || res == '*' || res == '^') {
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				arithTrig[i] = arithTrig[i + 1];
			}
		}
	}
	bool foundCustomValueMatrixAndChanged = false, foundCustomValueMatrix = false;
	if (var == 1) {
		if (isContained("==", arithTrig) == (bool)false && isContained("!=", arithTrig) == (bool)false) {
			for (i = 0; arithTrig[i] != '=' && i < abs((int)strlen(arithTrig)); i++) {
				variable[i] = arithTrig[i];
			}
			variable[i] = '\0';
			char* saveVariableData = getDynamicCharArray("", "saveVariableData");
			char* saveArithTrigExpression = getDynamicCharArray("", "saveArithTrigExpression");
			sprintf(saveArithTrigExpression, "%s", arithTrig);
			sprintf(saveVariableData, "%s=", variable);
			renamer(variable);
			sprintf(variable, "%s", expressionF);
			int lastCharIndex = 0;
			if (isContained("][", variable)) {
				if (isContained("[", variable)) {
					foundCustomValueMatrix = true;
					char* variableF = getDynamicCharArray("", "variableF");
					int p = strStart + 1, m = 0;
					if (p > 1) {
						if (p - 2 > 0 && verifyLetter(variable[p - 2])) {
							int k = p - 2;
							while (k > 0 && verifyLetter(variable[k])) {
								k--;
							}

							int v = 0;
							while (variable[k] != '[') {
								variableF[v] = variable[k];
								k++; v++;
							}
							variableF[v] = '\0';
							checkMatrixIndex = true;
							processVariable<T>(variableF);
							sprintf(matrixVariable, "%s", variableF);

							checkMatrixIndex = false;
						}
					}
					char* firstInt = getDynamicCharArray("", "firstInt"); char* secondInt = getDynamicCharArray("", "secondInt");
					while (variable[p] != ']') {
						firstInt[m] = variable[p];
						m++; p++;
					}
					firstInt[m] = '\0';
					p += 2; m = 0;
					while (variable[p] != ']') {
						secondInt[m] = variable[p];
						m++; p++;
					}

					secondInt[m] = '\0';
					indexI = (int)precisionValueTo<double>(solveMath<T>(firstInt));
					indexJ = (int)precisionValueTo<double>(solveMath<T>(secondInt));
					if (indexI >= numVectorLines) {
						printf("\n==> Error: Wrong number for the lines of matrix index. Maximum index: %d <==\n\n", numVectorLines - 1);
					}

					if (indexI >= numVectorCols) {
						printf("\n==> Error: Wrong number for the columns of matrix index. Maximum index: %d <==\n\n", numVectorCols - 1);
					}
					sprintf(variable, "%s", variableF);
					if (isContained("=", arithTrig)) {
						lastCharIndex = strStart;
					}
					_delete(variableF, "variableF"); variableF = nullptr;
					_delete(firstInt, "firstInt"); firstInt = nullptr;
					_delete(secondInt, "secondInt"); secondInt = nullptr;
				}
			}
			else {
				if (isContained("[", variable)) {
					foundCustomValueMatrix = true;
					int p = strStart + 1, m = 0;
					char* variableF = getDynamicCharArray("", "variableF");
					if (p > 1) {
						if (p - 2 > 0 && verifyLetter(variable[p - 2])) {
							int k = p - 2;
							while (k > 0 && verifyLetter(variable[k])) {
								k--;
							}

							int v = 0;
							while (variable[k] != '[') {
								variableF[v] = variable[k];
								k++; v++;
							}
							variableF[v] = '\0';
							checkMatrixIndex = true;
							processVariable<T>(variableF);
							sprintf(matrixVariable, "%s", variableF);

							checkMatrixIndex = false;
						}
					}
					char* firstInt = getDynamicCharArray("", "firstInt"); char* secondInt = getDynamicCharArray("", "secondInt");
					while (variable[p] != ']') {
						firstInt[m] = variable[p];
						m++; p++;
					}
					firstInt[m] = '\0';
					lastCharIndex = p;

					indexI = (int)precisionValueTo<double>(solveMath<T>(firstInt));
					indexJ = -1;
					if (indexI >= numVectorCols) {
						printf("\n==> Error: Wrong number for the vector index. Maximum index: %d <==\n\n", numVectorCols - 1);
					}
					sprintf(variable, "%s", variableF);
					if (isContained("=", arithTrig)) {
						lastCharIndex = strStart;
					}
					_delete(variableF, "variableF"); variableF = nullptr;
					_delete(firstInt, "firstInt"); firstInt = nullptr;
					_delete(secondInt, "secondInt"); secondInt = nullptr;
				}
			}

			if (feedbackValidation == 0) {
				useForVariables = true;
			}
			if (lastCharIndex != 0) {
				g = lastCharIndex + 1;
			}
			else {
				g = i + 1;

			}
			sprintf(saveArithTr, "%s", arithTrig);

			int hk = 0;

			replaceTimes = 0;

			if (strlen(saveVariableData) > 0) {
				if (isContained(saveVariableData, saveArithTrigExpression)) {
					replace(saveVariableData, "", saveArithTrigExpression);
					sprintf(saveArithTrigExpression, "%s", expressionF);

				}
			}

			sprintf(saveArithTr, "%s", saveArithTrigExpression);
			sprintf(arithTrig, "%s", saveArithTr);
			manageExpression<T>(arithTrig, (T)0, (T)0, 1);
			sprintf(saveArithTr, "%s", expressionF);
			if (isContained(arithTrig, saveArithTrigExpression)) {
				if (!isEqual(arithTrig, saveArithTr)) {
					replace(arithTrig, saveArithTr, saveArithTrigExpression);
					sprintf(saveArithTrigExpression, "%s", expressionF);
					foundCustomValueMatrixAndChanged = true;
				}


			}
			sprintf(saveArithTr, "%s", saveArithTrigExpression);

			i = 0;
			hk = variableValidator<T>(variable);
			if (hk == 1 || v == 1) {
				processVariable<T>(revariable);
			}
			if (hk == 2) {
				if (isFromMain == 1) {
					printf("\n==> Your variable was renamed to \"%s\". <==\n\n", revariable);
				}
				fprintf(fout, "\n==> Your variable was renamed to \"%s\". <==\n\n", revariable);
			}
			if (hk == 0) {
				if (isFromMain == 1) {
					printf("\n==> Invalid variable. Use only latin alphabet letters and be careful to avoid the same name for variables and user functions. <==\n\n");
				}
				fprintf(fout, "\n==> Invalid variable. Use only latin alphabet letters and be careful to avoid the same name for variables and user functions. <==\n\n");
				var = 0;
			}

			sprintf(arithTrig, "%s", saveArithTr);
			_delete(saveArithTr, "saveArithTr");
			if (isContained("\\", arithTrig) && isContained(";", arithTrig) && !runningScript) {
				if (isContained("+0", arithTrig) && arithTrig[strEnd] == '\0') {
					arithTrig[strStart] = '\0';
				}
				matrixMode = 1;
				vectorType = 2;
				int initialCountSplits = 0;
				char** saveSplitResult;

				saveSplitResult = new char* [DIMTWOD];

				for (int i = 0; i < DIMTWOD; ++i) {
					saveSplitResult[i] = getDynamicCharArray("", "saveSplitResult[i]");
				}
				int i = 0;
				if (countSplits > 0) {
					initialCountSplits = countSplits;
					while (i < countSplits) {
						sprintf(saveSplitResult[i], "%s", splitResult[i]);
						sprintf(splitResult[i], "");
						i++;
					}
				}

				countSplits = countOccurrences(";", arithTrig);
				int N = countSplits + 1;
				split(";", arithTrig);
				i = 0;
				char** value, ** lines;
				value = new char* [DIMTWOD];

				for (int i = 0; i < DIMTWOD; ++i) {
					value[i] = getDynamicCharArray("", "value[i]");
				}

				lines = new char* [DIMTWOD];

				for (int i = 0; i < DIMTWOD; ++i) {
					lines[i] = getDynamicCharArray("", "lines[i]");
				}
				i = 0;
				while (i <= countSplits) {
					sprintf(lines[i], "%s", splitResult[i]);
					sprintf(splitResult[i], "");
					i++;
				}
				int l = 0;
				int countLines = countSplits;
				PrecisionValue* VectorR = getDynamicDoubleArray(); PrecisionValue* VectorI = getDynamicDoubleArray();
				int previousNumCols = 0;
				while (l <= countLines) {
					int initialCountSplits = 0;
					int i = 0;
					if (countSplits > 0) {
						initialCountSplits = countSplits;
						while (i < countSplits) {
							sprintf(saveSplitResult[i], "%s", splitResult[i]);
							sprintf(splitResult[i], "");
							i++;
						}
					}
					countSplits = countOccurrences("\\", lines[l]);
					int N = countSplits + 1;
					if (previousNumCols == 0) {
						previousNumCols = N;
					}
					else {
						if (N != previousNumCols) {
							if (isFromMain == 1) {
								printf("\n==> Error: You are probably missing some members of the matrix. <==\n\n");
							}
							fprintf(fout, "\n==> Error: You are probably missing some members of the matrix. <==\n\n");
							validVar = 0;
							verify = 0;
							break;
						}
					}
					split("\\", lines[l]);
					i = 0;

					while (i <= countSplits) {
						sprintf(value[i], "%s", splitResult[i]);
						i++;
					}
					i = 0;
					while (i <= countSplits) {
						calcNow<T>(value[i], (T)0, (T)0);
						VectorR[i] = resultR; VectorI[i] = resultI;
						if (i < countSplits) {
							convertComplex2Exponential(VectorR[i], VectorI[i]);
							sprintf(vectorString, "%s%s+%si\\", vectorString, respR, respI);
						}
						else {
							convertComplex2Exponential(VectorR[i], VectorI[i]);
							sprintf(vectorString, "%s%s+%si", vectorString, respR, respI);
						}
						i++;
					}
					if (l < countLines) {
						sprintf(vectorString, "%s;", vectorString);
					}
					l++;
				}
				if (hk != 0 && verify == 1) {
					sprintf(expressionF, "%s", vectorString);
					sprintf(matrixResult, "%s", vectorString);
					variableController(revariable);
					sprintf(expressionF, "");
				}
				sprintf(matrixResult, "%s", vectorString);

				_Delete(saveSplitResult, DIMTWOD, dime, "saveSplitResult[i]");
				_Delete(lines, DIMTWOD, DIM, "lines[i]");

				_Delete(value, DIMTWOD, DIM, "value[i]");
				_delete(VectorR, "VectorR"); VectorR = nullptr;
				_delete(VectorI, "VectorI"); VectorI = nullptr;
			}
			else {
				if (isContained("\\", arithTrig) && !isContained(";", arithTrig) && !runningScript && !isContained("getcols", arithTrig) && !isContained("getlins", arithTrig)) {
					matrixMode = 1;
					vectorType = 1;
					PrecisionValue vectorR[100], vectorI[100];
					int initialCountSplits = 0;
					char** saveSplitResult;

					saveSplitResult = new char* [DIMTWOD];

					for (int i = 0; i < DIMTWOD; ++i) {
						saveSplitResult[i] = getDynamicCharArray("", "saveSplitResult[i]");
					}

					int i = 0;
					if (countSplits > 0) {
						initialCountSplits = countSplits;
						while (i < countSplits) {
							sprintf(saveSplitResult[i], "%s", splitResult[i]);
							sprintf(splitResult[i], "");
							i++;
						}
					}
					countSplits = countOccurrences("\\", arithTrig);
					int N = countSplits + 1;
					split("\\", arithTrig);
					i = 0;
					char** value;
					value = new char* [DIMTWOD];

					for (int i = 0; i < DIMTWOD; ++i) {
						value[i] = getDynamicCharArray("", "value[i]");
					}
					i = 0;
					while (i <= countSplits) {
						sprintf(value[i], "%s", splitResult[i]);
						i++;
					}
					i = 0;
					while (i <= countSplits) {
						calcNow<T>(value[i], (T)0, (T)0);
						vectorR[i] = resultR; vectorI[i] = resultI;
						if (i < countSplits) {
							convertComplex2Exponential(vectorR[i], vectorI[i]);
							sprintf(vectorString, "%s%s+%si\\", vectorString, respR, respI);
						}
						else {
							convertComplex2Exponential(vectorR[i], vectorI[i]);
							sprintf(vectorString, "%s%s+%si", vectorString, respR, respI);
						}
						i++;
					}
					if (hk != 0 && verify == 1) {
						sprintf(expressionF, "%s", vectorString);
						sprintf(matrixResult, "%s", vectorString);
						variableController(revariable);
						sprintf(expressionF, "");
					}
					sprintf(matrixResult, "%s", vectorString);

					_Delete(saveSplitResult, DIMTWOD, dime, "saveSplitResult[i]");
					_Delete(value, DIMTWOD, DIM, "value[i]");
				}
				else {
					if (!isContained("\\", arithTrig) && isContained(";", arithTrig) && !runningScript) {
						matrixMode = 1;
						vectorType = 1;
						PrecisionValue vectorR[100], vectorI[100];
						int initialCountSplits = 0;
						char** saveSplitResult;

						saveSplitResult = new char* [DIMTWOD];

						for (int i = 0; i < DIMTWOD; ++i) {
							saveSplitResult[i] = getDynamicCharArray("", "saveSplitResult[i]");
						}


						int i = 0;
						if (countSplits > 0) {
							initialCountSplits = countSplits;
							while (i < countSplits) {
								sprintf(saveSplitResult[i], "%s", splitResult[i]);
								sprintf(splitResult[i], "");
								i++;
							}
						}
						countSplits = countOccurrences(";", arithTrig);
						int N = countSplits + 1;
						split(";", arithTrig);
						i = 0;
						char** value;
						value = new char* [DIMTWOD];

						for (int i = 0; i < DIMTWOD; ++i) {
							value[i] = getDynamicCharArray("", "value[i]");
						}
						while (i <= countSplits) {
							sprintf(value[i], "%s", splitResult[i]);
							i++;
						}
						i = 0;
						while (i <= countSplits) {
							calcNow<T>(value[i], (T)0, (T)0);
							vectorR[i] = resultR; vectorI[i] = resultI;
							convertComplex2Exponential(vectorR[i], vectorI[i]);
							if (i < countSplits) {
								sprintf(vectorString, "%s%s+%si;", vectorString, respR, respI);
							}
							else {
								sprintf(vectorString, "%s%s+%si", vectorString, respR, respI);
							}
							i++;
						}
						if (hk != 0 && verify == 1) {
							sprintf(expressionF, "%s", vectorString);
							sprintf(matrixResult, "%s", vectorString);
							variableController(revariable);
							sprintf(expressionF, "");
						}
						sprintf(matrixResult, "%s", vectorString);

						_Delete(saveSplitResult, DIMTWOD, dime, "saveSplitResult[i]");

						_Delete(value, DIMTWOD, DIM, "value[i]");
					}
				}
			}

			sprintf(saveArithTrig, "%s", arithTrig);
			_delete(saveVariableData, "saveVariableData");
			_delete(saveArithTrigExpression, "saveArithTrigExpression");

		}

	}

	char* dP = getDynamicCharArray("", "dP"); char* bP = getDynamicCharArray("", "bP"); char* oP = getDynamicCharArray("", "oP"); char* hP = getDynamicCharArray("", "hP");
	int dp = -1, bp = -1, op = -1, hp = -1;
	while ((arithTrig[0] == 'd' && arithTrig[1] == 'p' || arithTrig[0] == 'b' && arithTrig[1] == 'p' || arithTrig[0] == 'o' && arithTrig[1] == 'p' || arithTrig[0] == 'h' && arithTrig[1] == 'p') && i < abs((int)strlen(arithTrig)) && i < abs((int)strlen(arithTrig))) {
		if (arithTrig[0] == 'd' && arithTrig[1] == 'p') {
			i = 2;
			while ((arithTrig[i] == 'd' && arithTrig[i + 1] == 'p') == false && i < abs((int)strlen(arithTrig))) {
				dP[i - 2] = arithTrig[i];
				i++;
			}
			dP[i - 2] = '\0';
			if (i < abs((int)strlen(arithTrig))) {
				dp = parseCorePlacesValue<T>(dP, result1, result2);
				i = i + 2;
				int b = 0;
				for (b = 0; b < abs((int)strlen(arithTrig)); b++) {
					arithTrig[b] = arithTrig[b + i];
				}
			}
			else {
				dp = 10000;
				nPlaces = dp;
			}
		}
		if (arithTrig[0] == 'b' && arithTrig[1] == 'p') {
			i = 2;
			while ((arithTrig[i] == 'b' && arithTrig[i + 1] == 'p') == false && i < abs((int)strlen(arithTrig))) {
				bP[i - 2] = arithTrig[i];
				i++;
			}
			bP[i - 2] = '\0';
			if (i < abs((int)strlen(arithTrig))) {
				bp = parseCorePlacesValue<T>(bP, result1, result2);
				i = i + 2;
				int b = 0;
				for (b = 0; b < abs((int)strlen(arithTrig)); b++) {
					arithTrig[b] = arithTrig[b + i];
				}
			}
			else {
				bp = 1000;
				nPlaces = bp;
			}
		}
		if (arithTrig[0] == 'o' && arithTrig[1] == 'p') {
			i = 2;
			while ((arithTrig[i] == 'o' && arithTrig[i + 1] == 'p') == false && i < abs((int)strlen(arithTrig))) {
				oP[i - 2] = arithTrig[i];
				i++;
			}
			oP[i - 2] = '\0';
			if (i < abs((int)strlen(arithTrig))) {
				op = parseCorePlacesValue<T>(oP, result1, result2);
				i = i + 2;
				int b = 0;
				for (b = 0; b < abs((int)strlen(arithTrig)); b++) {
					arithTrig[b] = arithTrig[b + i];
				}
			}
			else {
				op = 8000;
				nPlaces = op;
			}
		}
		if (arithTrig[0] == 'h' && arithTrig[1] == 'p') {
			i = 2;
			while ((arithTrig[i] == 'h' && arithTrig[i + 1] == 'p') == false && i < abs((int)strlen(arithTrig))) {
				hP[i - 2] = arithTrig[i];
				i++;
			}
			hP[i - 2] = '\0';
			if (i < abs((int)strlen(arithTrig))) {
				hp = parseCorePlacesValue<T>(hP, result1, result2);
				i = i + 2;
				int b = 0;
				for (b = 0; b < abs((int)strlen(arithTrig)); b++) {
					arithTrig[b] = arithTrig[b + i];
				}
			}
			else {
				hp = 16000;
				nPlaces = hp;
			}
		}
	}
	normalizeMainCoreBooleanInfinityConstants(arithTrig);
	normalizeMainCoreScientificNotation(arithTrig);
	for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
		if (arithTrig[i] == 'a' && arithTrig[i + 1] == 'n' && arithTrig[i + 2] == 's') {
			arithTrig[i] = 'r'; arithTrig[i + 1] = 'e'; arithTrig[i + 2] = 's';
			i = i + 3;
		}
	}
	s = 0;

	T solverFastPathSolution = 0;
	if (!solverRunning && !equationSolverRunning && tryEvaluateSolverFastPath(arithTrig, solverFastPathSolution)) {
		convertComplex2Exponential(resultR, resultI);
		if (abs(precisionValueTo<double>(resultI)) < 1E-18) {
			sprintf(arithTrig, "%s", respR);
		}
		else if (resultI > 0) {
			sprintf(arithTrig, "(%s+%si)", respR, respI);
		}
		else {
			sprintf(arithTrig, "(%s%si)", respR, respI);
		}
		sprintf(saveExpressionFF, "%s", arithTrig);
	}

	bool foundMatrixVariable = false;
	if (verify == 1 && !isContained("\\", arithTrig)) {
		char* matrixVariableProbe = getDynamicCharArray("", "matrixVariableProbe");
		char* savedMatrixValue = getDynamicCharArray(matrixValue, "savedMatrixValue");
		char* savedMatrixResult = getDynamicCharArray(matrixResult, "savedMatrixResult");
		char* savedVectorString = getDynamicCharArray(vectorString, "savedVectorString");
		PrecisionValue savedResultR = resultR;
		PrecisionValue savedResultI = resultI;
		int savedValidVar = validVar;
		int savedValid = valid;
		int savedMatrixMode = matrixMode;
		int savedCheck4Vector = check4Vector;
		for (i = 0; i < abs((int)strlen(arithTrig)) && !foundMatrixVariable; i++) {
			if (verifyLetter(arithTrig[i]) && (i == 0 || !verifyLetter(arithTrig[i - 1]))) {
				int probeIndex = 0;
				while (verifyLetter(arithTrig[i]) && i < abs((int)strlen(arithTrig))) {
					matrixVariableProbe[probeIndex] = arithTrig[i];
					probeIndex++;
					i++;
				}
				matrixVariableProbe[probeIndex] = '\0';
				processVariable<T>(matrixVariableProbe);
				foundMatrixVariable = validVar == 1 && abs((int)strlen(matrixValue)) > 0;
				sprintf(matrixVariableProbe, "");
			}
		}
		resultR = savedResultR;
		resultI = savedResultI;
		validVar = savedValidVar;
		valid = savedValid;
		matrixMode = savedMatrixMode;
		check4Vector = savedCheck4Vector;
		sprintf(matrixValue, "%s", savedMatrixValue);
		sprintf(matrixResult, "%s", savedMatrixResult);
		sprintf(vectorString, "%s", savedVectorString);
		_delete(savedMatrixValue, "savedMatrixValue"); savedMatrixValue = nullptr;
		_delete(savedMatrixResult, "savedMatrixResult"); savedMatrixResult = nullptr;
		_delete(savedVectorString, "savedVectorString"); savedVectorString = nullptr;
		_delete(matrixVariableProbe, "matrixVariableProbe"); matrixVariableProbe = nullptr;
	}
	bool foundMatrixVariableArithmetic = foundMatrixVariable && (isContained("+", arithTrig) || isContained("-", arithTrig) || isContained("*", arithTrig) || isContained("/", arithTrig) || isContained("^", arithTrig));
	if (verify == 1 && !isContained("\\", arithTrig)) {
		if ((equationSolverRunning == false && solverRunning == false) && isContained("==", arithTrig) == (bool)false && isContained("!=", arithTrig) == (bool)false && !foundCustomValueMatrixAndChanged && !foundCustomValueMatrix && !foundMatrixVariable || isContained("]i", arithTrig)) {
			sprintf(saveArithTrig, "%s", arithTrig);
			sprintf(expressionF, "");
			manageExpression<T>(arithTrig, (T)0, (T)0, 1);
			sprintf(arithTrig, "%s", expressionF);
			sprintf(saveArithTrig, "%s", arithTrig);
			sprintf(saveExpressionFF, "%s", expressionF);
			synTest = 0;

			verify = dataVerifier<T>(arithTrig, (T)0, (T)0, isFromMain, 1);
		}
		else {
			if ((equationSolverRunning || solverRunning)) {
				sprintf(arithTrig, "%s", saveExpressionFF);
				verify = 1;
			}
		}
	}
	if (verify == 1) {
		verified = 1;
	}
	if (fout != NULL) {
		fclose(fout);
	}
	if (0 < abs((int)strlen(arithTrig)) && isFromMain == 1 && feedbackValidation == 0 && creatingMatrix == 0) {
		Clock(0);
	}
	char* toOpen = getDynamicCharArray("", "toOpen");
	if (continu == 1) {
		_flushall();
		if (cleanhistory == 0) {
			if (0 < abs((int)strlen(arithTrig)) && verify == 1) {
				sprintf(toOpen, "%s\\verboseResolution.txt", atcPath);
				open = fopen(toOpen, "r");
				char* verboseRes = getDynamicCharArray("", "verboseRes");
				if (open != NULL) {
					fgets(verboseRes, 10, open);
					verbose = atoi(verboseRes);
					fclose(open);
				}
				else {
					verbose = 0;
				}

				initialProcessor<T>(arithTrig, result1);

				verbose = 0;
				_delete(verboseRes, "verboseRes"); verboseRes = nullptr;
			}
		}
		if (0 < abs((int)strlen(arithTrig)) && txt != 1 && processingOK == 1) {
			if (verify == 1) {
				if (previousAnsType == 0 && abs((int)strlen(matrixResult)) == 0) {
					if (res == '+') {
						sum<T>(result1, result2, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
					}
					if (res == '-') {
						subtraction<T>(result1, result2, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
					}
					if (res == '/') {
						division<T>(result1, result2, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
					}
					if (res == '*') {
						multiplication<T>(result1, result2, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
					}
					if (res == '^') {
						exponentiation<T>(result1, result2, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), 1);
					}
				}
				else {
					PrecisionValue resultRM = resultR, resultIM = resultI;
					PrecisionValue** res_vectorR = new PrecisionValue* [DIMTWOD];

					for (int i = 0; i < DIMTWOD; ++i) {
						res_vectorR[i] = getDynamicDoubleArray();
					}
					PrecisionValue** res_vectorI = new PrecisionValue* [DIMTWOD];

					for (int i = 0; i < DIMTWOD; ++i) {
						res_vectorI[i] = getDynamicDoubleArray();
					}
					PrecisionValue** vector1_R = new PrecisionValue* [DIMTWOD];

					for (int i = 0; i < DIMTWOD; ++i) {
						vector1_R[i] = getDynamicDoubleArray();
					}
					PrecisionValue** vector1_I = new PrecisionValue* [DIMTWOD];

					for (int i = 0; i < DIMTWOD; ++i) {
						vector1_I[i] = getDynamicDoubleArray();
					}

					int numVectorCols1 = 0, numVectorLines1 = 0;
					T resRank = 0;
					if (res == '^') {
						if (abs((int)strlen(matrixResult)) == 0 && abs((int)strlen(saveMatrixAns)) > 0) {
							matrixMode = 1;
							convert2Vector(saveMatrixAns);
							if ((int)precisionValueTo<double>(resultRM) == -7654321 || (int)precisionValueTo<double>(resultRM) == -7654320) {
								fmtranspose(numVectorLines, numVectorCols, vectorR, vectorI, res_vectorR, res_vectorI);
								int savenumVectorCols = numVectorCols;
								numVectorCols = numVectorLines;
								numVectorLines = savenumVectorCols;
							}
							if ((int)precisionValueTo<double>(resultRM) == -1) {
								fminverse(numVectorLines, numVectorCols, vectorR, vectorI, res_vectorR, res_vectorI);
							}
							if (((int)precisionValueTo<double>(resultRM) >= 0 || (int)precisionValueTo<double>(resultRM) < -1) && ((int)precisionValueTo<double>(resultRM)) != -7654321 && ((int)precisionValueTo<double>(resultRM)) != -7654320 && ((int)precisionValueTo<double>(resultRM)) != -1234567) {
								fmpowerm(vectorR, vectorI, res_vectorR, res_vectorI, (int)precisionValueTo<double>(resultRM), numVectorLines, numVectorCols);
							}
							if ((int)precisionValueTo<double>(resultRM) == -1234567) {
								convert2Vector(saveMatrixAns);
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
								resultR = (T)fmrank(numVectorLines1, numVectorCols1, vector1_R, vector1_I);
								resultI = 0;
							}
							else {
								sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines, numVectorCols));
							}
						}
					}
					if (res == '*') {
						if (abs((int)strlen(matrixResult)) > 0 && abs((int)strlen(saveMatrixAns)) > 0) {
							convert2Vector(saveMatrixAns);
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
							convert2Vector(matrixResult);
							fmmulm(numVectorLines, numVectorCols1, numVectorLines1, numVectorCols, vector1_R, vectorR, res_vectorR, vector1_I, vectorI, res_vectorI);
							sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));

						}
						else {
							if (abs((int)strlen(matrixResult)) > 0 && abs((int)strlen(saveMatrixAns)) == 0) {

								convert2Vector(matrixResult);
								fmmulr(numVectorLines, numVectorCols, vectorR, res_vectorR, result1, vectorI, res_vectorI, result2);
								numVectorCols1 = numVectorCols;
								numVectorLines1 = numVectorLines;
								sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
							}
							else {
								if (abs((int)strlen(matrixResult)) == 0 && abs((int)strlen(saveMatrixAns)) > 0) {
									convert2Vector(saveMatrixAns);
									matrixMode = 1;
									fmmulr(numVectorLines, numVectorCols, vectorR, res_vectorR, resultRM, vectorI, res_vectorI, resultIM);
									numVectorCols1 = numVectorCols;
									numVectorLines1 = numVectorLines;
									sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
								}
							}
						}
					}
					if (res == '/') {
						if (abs((int)strlen(matrixResult)) == 0 && abs((int)strlen(saveMatrixAns)) > 0) {
							convert2Vector(saveMatrixAns);
							division<PrecisionValue>((PrecisionValue)1.0, (PrecisionValue)0.0, resultRM, resultIM);
							matrixMode = 1;
							fmmulr(numVectorLines, numVectorCols, vectorR, res_vectorR, resultR, vectorI, res_vectorI, resultI);
							numVectorCols1 = numVectorCols;
							numVectorLines1 = numVectorLines;
							sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));

						}
						else {
							if (abs((int)strlen(matrixResult)) > 0 && abs((int)strlen(saveMatrixAns)) > 0) {
								convert2Vector(saveMatrixAns);
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
								convert2Vector(matrixResult);
								if (fmdivm(numVectorLines, numVectorCols1, numVectorLines1, numVectorCols, vector1_R, vectorR, vector1_I, vectorI)) {
									result1 = precisionValueTo<T>(resultR);
									result2 = precisionValueTo<T>(resultI);
								}
								else {
									if (isFromMain == 1) {
										printf("\nError: The quotient of matrices is not consistent over all matrices members.");
									}
								}
							}

						}
					}
					if (res == '-') {
						if (abs((int)strlen(matrixResult)) > 0 && abs((int)strlen(saveMatrixAns)) > 0) {
							convert2Vector(saveMatrixAns);
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
							convert2Vector(matrixResult);
							fmsubt(numVectorLines, numVectorCols, vector1_R, vectorR, res_vectorR, vector1_I, vectorI, res_vectorI);
							sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));

						}

					}
					if (res == '+') {
						if (abs((int)strlen(matrixResult)) > 0 && abs((int)strlen(saveMatrixAns)) > 0) {
							convert2Vector(saveMatrixAns);
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
							convert2Vector(matrixResult);
							fmsum(numVectorLines, numVectorCols, vector1_R, vectorR, res_vectorR, vector1_I, vectorI, res_vectorI);
							sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
						}

					}
					_Delete(vector1_R, DIMTWOD, DIMDOUBLE, "vector1_R");
					_Delete(vector1_I, DIMTWOD, DIMDOUBLE, "vector1_I");

				}
				verified = 1;
				roundSolution();
				result1 = precisionValueTo<T>(resultR);
				result2 = precisionValueTo<T>(resultI);
				resultFI = result2;

				ans[rf] = result1;
				ansI[rf] = result2;
				ansRV = result1;
				ansIV = result2;
				if (abs((int)strlen(matrixResult)) > 0) {
					previousAnsType = 1;
					sprintf(saveMatrixAns, "%s", matrixResult);
					sprintf(ansMatrices[rf], "%s", matrixResult);
				}
				else {
					previousAnsType = 0;
					sprintf(saveMatrixAns, "");
					sprintf(ansMatrices[rf], "");
				}
				if (var == 1) {

					if (indexI != -1 || indexJ != -1) {
						processVariable<T>(matrixVariable);
						if (indexJ == -1) {
							vectorR[0][indexI] = result1;
							vectorI[0][indexI] = result2;
						}
						else {
							vectorR[indexI][indexJ] = result1;
							vectorI[indexI][indexJ] = result2;

						}
						char* response = convertVector2String(vectorR, vectorI, numVectorLines, numVectorCols);
						sprintf(expressionF, "%s", response);
						variableController(matrixVariable);
					}
					else {
						char* saveMatrixResult = getDynamicCharArray("", "saveMatrixResult");
						if (matrixMode == 1) {
							sprintf(saveMatrixResult, "%s", matrixResult);
						}
						if (matrixMode == 1) {

							convert2Vector(matrixResult);
							char* report = getDynamicCharArray("", "report");
							for (i = 0; i < numVectorLines; i++) {
								for (int k = 0; k < numVectorCols; k++) {
									convertComplex2Exponential(vectorR[i][k], vectorI[i][k]);
									sprintf(report, "%s%s+%si ", report, respR, respI);
								}
								sprintf(report, "%s\n", report);
							}
							_delete(report, "report"); report = nullptr;

						}
						if (matrixMode == 1) {
							sprintf(matrixResult, "%s", saveMatrixResult);
						}
						if (abs((int)strlen(matrixResult)) > 0) {
							replaceTimes = 0;
							if (isContained("*", matrixResult)) {
								replace("*", ";", matrixResult);
								sprintf(matrixResult, "%s", expressionF);
							}
							if (isContained(":", matrixResult)) {
								replace(":", "\\", matrixResult);
								sprintf(matrixResult, "%s", expressionF);
							}
							sprintf(expressionF, "%s", matrixResult);
						}

						if ((matrixMode == 0 || matrixMode == 2 || abs((int)strlen(matrixResult)) > 0) && verify == 1) {
							if (abs((int)strlen(matrixResult)) == 0) {
								sprintf(expressionF, "");
							}
							variableController(revariable);
						}
						_delete(saveMatrixResult, "saveMatrixResult"); saveMatrixResult = nullptr;
					}
				}
				if (var == 1) {
					if ((isContained(";", matrixResult) || isContained("\\", matrixResult)) && runningUserFunction == 0) {
						calcNow<T>(revariable, (T)0, (T)0);
					}
				}
				if (verify == 1 && verified == 1 && runningUserFunction == 1 && isFromSolveNow == 0) {
					rf--;
				}
				else {
					if (verify == 1 && verified == 1 && isFromSolveNow == 0 && creatingMatrix == 1) {
						rf--;
					}
					else {
						if (verify == 1 && verified == 1 && haveCreatedDynamicMatrix == 1) {
							rf--;
						}

					}

				}

				if (valGet == 0 && feedbackValidation == 0) {
					if (abs((int)strlen(renamedVariable)) > 0 && isContained("atc_", arithTrig) && abs((int)strlen(variable)) > 0) {
						variableController(renamedVariable);

					}
					if (matrixMode == 1 && abs((int)strlen(matrixResult) > 0)) {

						convert2Vector(matrixResult);
						char* report = getDynamicCharArray("", "report");
						for (i = 0; i < numVectorLines; i++) {
							for (int k = 0; k < numVectorCols; k++) {
								convertComplex2Exponential(vectorR[i][k], vectorI[i][k]);
								sprintf(report, "%s%s+%si ", report, respR, respI);
							}
							sprintf(report, "%s\n", report);
						}
						if (isFromMain == 1) {
							printf("#%d=\n", rf);
							puts(report);
						}
						if (fout != NULL) {
							fclose(fout);
						}
						fout = NULL;
						while (fout == NULL) {
							fout = fopen(path, "a+");
						}
						if (fout != NULL) {
							fprintf(fout, "#%d=\n%s", rf, report);
							fclose(fout);
						}
						_delete(report, "report"); report = nullptr;
					}

					if (matrixMode == 0 || matrixMode == 2 || abs((int)strlen(matrixResult) == 0)) {
						if (dp == -1) {
							if (isFromMain == 1) {
								convertComplex2Exponential(result1, result2);
								if (result1 > 0 && result2 > 0) {
									printf("#%d=%s+%si\n", rf, respR, respI);
								}
								else {
									if (result1 > 0 && result2 < 0) {
										printf("#%d=%s%si\n", rf, respR, respI);
									}
									else {
										if (result1 < 0 && result2 > 0) {
											printf("#%d=%s+%si\n", rf, respR, respI);
										}
										else {
											if (result1 < 0 && result2 < 0) {
												printf("#%d=%s%si\n", rf, respR, respI);
											}
											else {
												if (result1 == 0 && result2 == 0) {
													printf("#%d=%s\n", rf, convert2Exponential(result1));
												}
												else {
													if (result1 == 0 && result2 != 0) {
														printf("#%d=%si\n", rf, convert2Exponential(result2));
													}
													else {
														if (result1 != 0 && result2 == 0) {
															printf("#%d=%s\n", rf, convert2Exponential(result1));
														}
														else {
															printf("#%d=%s+%si\n", rf, respR, respI);
														}
													}
												}
											}
										}
									}
								}
							}
							if (fout != NULL) {
								fclose(fout);
							}
							fout = NULL;
							while (fout == NULL) {
								fout = fopen(path, "a+");
							}
							convertComplex2Exponential(result1, result2);
							if (result1 > 0 && result2 > 0) {
								fprintf(fout, "#%d=%s+%si\n", rf, respR, respI);
							}
							else {
								if (result1 > 0 && result2 < 0) {
									fprintf(fout, "#%d=%s%si\n", rf, respR, respI);
								}
								else {
									if (result1 < 0 && result2 > 0) {
										fprintf(fout, "#%d=%s+%si\n", rf, respR, respI);
									}
									else {
										if (result1 < 0 && result2 < 0) {
											fprintf(fout, "#%d=%s%si\n", rf, respR, respI);
										}
										else {
											if (result1 == 0 && result2 == 0) {
												fprintf(fout, "#%d=%s\n", rf, convert2Exponential(result1));
											}
											else {
												if (result1 == 0 && result2 != 0) {
													fprintf(fout, "#%d=%si\n", rf, convert2Exponential(result2));
												}
												else {
													if (result1 != 0 && result2 == 0) {
														fprintf(fout, "#%d=%s\n", rf, convert2Exponential(result1));
													}
													else {
														fprintf(fout, "#%d=%s+%si\n", rf, respR, respI);
													}
												}
											}
										}
									}
								}
							}


						}
                        if (dp > -1) {
                            std::string realFormatted = formatCoreFixedPrecisionValue<T>(result1, dp);
                            std::string imagFormatted = formatCoreFixedPrecisionValue<T>(result2, dp);
                            char* ansFormatted = getDynamicCharArray("", "ansFormatted");
                            if (result1 > 0 && result2 > 0) {
                                sprintf(ansFormatted, "#%d=%s+%si\n", rf, realFormatted.c_str(), imagFormatted.c_str());
                            }
                            if (result1 > 0 && result2 < 0) {
                                sprintf(ansFormatted, "#%d=%s%si\n", rf, realFormatted.c_str(), imagFormatted.c_str());
                            }
                            if (result1 < 0 && result2 > 0) {
                                sprintf(ansFormatted, "#%d=%s+%si\n", rf, realFormatted.c_str(), imagFormatted.c_str());
                            }
                            if (result1 < 0 && result2 < 0) {
                                sprintf(ansFormatted, "#%d=%s%si\n", rf, realFormatted.c_str(), imagFormatted.c_str());
                            }
                            if (result1 == 0 && result2 == 0) {
                                sprintf(ansFormatted, "#%d=%s\n", rf, realFormatted.c_str());
                            }
                            if (result1 == 0 && result2 != 0) {
                                sprintf(ansFormatted, "#%d=%si\n", rf, imagFormatted.c_str());
                            }
                            if (result1 != 0 && result2 == 0) {
                                sprintf(ansFormatted, "#%d=%s\n", rf, realFormatted.c_str());
                            }
                            if (isFromMain == 1) {
                                printf("%s", ansFormatted);
                            }
                            if (fout != NULL) {
                                fclose(fout);
                            }
                            fout = NULL;
                            while (fout == NULL) {
                                fout = fopen(path, "a+");
                            }
                            fprintf(fout, "%s", ansFormatted);
                            fclose(fout);
                            _delete(ansFormatted, "ansFormatted"); ansFormatted = nullptr;
                        }
					}
					int numLines = 0, numCols = 0;
					if (abs((int)strlen(matrixResult)) == 0) {
						numLines = 1; numCols = 1;
					}
					else {
						convert2Vector(matrixResult);
						numLines = numVectorLines;
						numCols = numVectorCols;
					}
					char* toOpen = getDynamicCharArray("", "toOpen");
					sprintf(toOpen, "%s\\numSystems.txt", atcPath);
					open = fopen(toOpen, "r");
					char* numSys = getDynamicCharArray("", "numSys");
					int numeriSys = 0;
					if (open != NULL || bp != -1 || op != -1 || hp != -1) {
						if (open != NULL) {
							fgets(numSys, 10, open);
							numeriSys = atoi(numSys);
							fclose(open);
						}
						if (numeriSys == 1 || bp != -1 || op != -1 || hp != -1) {
							int w = 0, y = 0;
							for (w = 0; w < numLines; w++) {
								for (y = 0; y < numCols; y++) {
									if (numLines > 1 || numCols > 1) {
										if (isFromMain == 1) {
											printf("\nm(%d,%d)=\n", w, y);
										}
										open = fopen(path, "a+");
										fputs("", open);
										fprintf(open, "\nm(%d,%d)=\n", w, y);
										fclose(open);
									}
									char* syst = getDynamicCharArray("", "syst");
									sprintf(syst, "%s", convert2Exponential(result1));
									if (isEqual(syst, "-NAN(IND)")) {
										if (isFromMain == 1) {
											puts("");
											puts("In binary=-NAN(IND)");
											puts("In octal=-NAN(IND)");
											puts("In hexadecimal=-NAN(IND)");
										}
										open = fopen(path, "a+");
										fputs("", open);
										fputs("In binary=-NAN(IND)\n", open);
										fputs("In octal=-NAN(IND)\n", open);
										fputs("In hexadecimal=-NAN(IND)\n", open);
										fclose(open);
									}
									else {
										if (syst[0] == 'I' && syst[1] == 'N' && syst[2] == 'F') {
											if (isFromMain == 1) {
												puts("");
												puts("In binary=INF");
												puts("In octal=INF");
												puts("In hexadecimal=INF");
											}
											open = fopen(path, "a+");
											fputs("", open);
											fputs("In binary=INF\n", open);
											fputs("In octal=INF\n", open);
											fputs("In hexadecimal=INF\n", open);
											fclose(open);
										}
										else {
											if (syst[0] == '-' && syst[1] == 'I' && syst[2] == 'N' && syst[3] == 'F') {
												if (isFromMain == 1) {
													puts("");
													puts("In binary=-INF");
													puts("In octal=-INF");
													puts("In hexadecimal=-INF");
												}
												open = fopen(path, "a+");
												fputs("", open);
												fputs("In binary=-INF\n", open);
												fputs("In octal=-INF\n", open);
												fputs("In hexadecimal=-INF\n", open);
												fclose(open);
											}
											else {
												if (result1 != 0 && result2 == 0 || result1 == 0 && result2 == 0) {
													open = fopen(path, "a+");
													fputs("\nReal part:\n", open);
													if (isFromMain == 1) {
														puts("\nReal part:\n");
													}
													fclose(open);
													decimalToBinary(result1, path, bp);
													decimalToOctal(result1, path, op);
													decimalToHexadecimal(result1, path, hp);
												}
												else {
													if (result1 != 0 && result2 != 0) {
														open = fopen(path, "a+");
														fputs("\nReal part:\n", open);
														if (isFromMain == 1) {
															puts("\nReal part:\n");
														}
														fclose(open);
														decimalToBinary(result1, path, bp);
														decimalToOctal(result1, path, op);
														decimalToHexadecimal(result1, path, hp);
														open = fopen(path, "a+");
														fputs("\nImaginary part:\n", open);
														if (isFromMain == 1) {
															puts("\nImaginary part:\n");
														}
														fclose(open);
														decimalToBinary(result2, path, bp);
														decimalToOctal(result2, path, op);
														decimalToHexadecimal(result2, path, hp);
													}
													else {
														if (result2 != 0) {
															open = fopen(path, "a+");
															fputs("\nImaginary part:\n", open);
															if (isFromMain == 1) {
																puts("\nImaginary part:\n");
															}
															fclose(open);
															decimalToBinary(result2, path, bp);
															decimalToOctal(result2, path, op);
															decimalToHexadecimal(result2, path, hp);
														}
													}
												}
											}
										}
									}
									_delete(syst, "syst"); syst = nullptr;
								}
							}
						}

					}
					toOpen[0] = '\0';
					sprintf(toOpen, "%s\\siPrefixes.txt", atcPath);
					open = fopen(toOpen, "r");
					char* siPref = getDynamicCharArray("", "siPref");
					int niPrefix = 0;
					if (open != NULL) {
						fgets(siPref, 10, open);
						fclose(open);
						niPrefix = atoi(siPref);
						if (niPrefix == 1) {
							int w = 0, y = 0;
							for (w = 0; w < numLines; w++) {
								for (y = 0; y < numCols; y++) {
									if (numLines > 1 || numCols > 1) {
										if (isFromMain == 1) {
											printf("\nm(%d,%d)=\n", w, y);
										}
										open = fopen(path, "a+");
										fputs("", open);
										fprintf(open, "\nm(%d,%d)=\n", w, y);
										fclose(open);
									}
									char* pref = getDynamicCharArray("", "pref");
									sprintf(pref, "%s", convert2Exponential(result1));
									char* Value = getDynamicCharArray("", "Value");
									if (result1 != 0 || result1 == 0 && result2 == 0) {
										open = fopen(path, "a+");
										fputs("\nReal part:\n", open);
										if (isFromMain == 1) {
											puts("\nReal part:\n");
										}
										fclose(open);
										char* pref = getDynamicCharArray("", "pref");
										sprintf(pref, "%s", convert2Exponential(result1));
										if (isEqual(pref, "-NAN(IND)")) {
											if (isFromMain == 1) {
												puts("=-NAN(IND)");
											}
											open = fopen(path, "a+");
											fputs("=-NAN(IND)\n", open);
											fclose(open);
										}
										else {
											if (pref[0] == 'I' && pref[1] == 'N' && pref[2] == 'F') {
												if (isFromMain == 1) {
													puts("=INF");
												}
												open = fopen(path, "a+");
												fputs("=INF\n", open);
												fclose(open);
											}
											else {
												if (pref[0] == '-' && pref[1] == 'I' && pref[2] == 'N' && pref[3] == 'F') {
													if (isFromMain == 1) {
														puts("=-INF");
													}
													open = fopen(path, "a+");
													fputs("=-INF\n", open);
													fclose(open);
												}
												else {
													prefixDeterminator(result1, path);
												}
											}
										}
										_delete(pref, "pref"); pref = nullptr;
									}
									if (result2 != 0) {
										open = fopen(path, "a+");
										fputs("\nImaginary part:\n", open);
										if (isFromMain == 1) {
											puts("\nImaginary part:\n");
										}
										fclose(open);
										char* pref = getDynamicCharArray("", "pref");
										sprintf(pref, "%s", convert2Exponential(result2));
										if (isEqual(pref, "-NAN(IND)")) {
											if (isFromMain == 1) {
												puts("=-NAN(IND)");
											}
											open = fopen(path, "a+");
											fputs("=-NAN(IND)\n", open);
											fclose(open);
										}
										else {
											if (pref[0] == 'I' && pref[1] == 'N' && pref[2] == 'F') {
												if (isFromMain == 1) {
													puts("=INF");
												}
												open = fopen(path, "a+");
												fputs("=INF\n", open);
												fclose(open);
											}
											else {
												if (pref[0] == '-' && pref[1] == 'I' && pref[2] == 'N' && pref[3] == 'F') {
													if (isFromMain == 1) {
														puts("=-INF");
													}
													open = fopen(path, "a+");
													fputs("=-INF\n", open);
													fclose(open);
												}
												else {
													prefixDeterminator(result2, path);
												}
											}
										}
										_delete(pref, "pref"); pref = nullptr;
									}
									_delete(pref, "pref"); pref = nullptr;
									_delete(Value, "Value"); Value = nullptr;

								}
							}
						}
					}
					if (verify == 1 && verified == 1 && isFromSolveNow == 0) {
						rf++;
					}


					sprintf(toOpen, "%s\\actualTime.txt", atcPath);
					open = fopen(toOpen, "r");
					char* actualTime = getDynamicCharArray("", "actualTime");
					int nactualTime = 0;
					if (open != NULL) {
						fgets(actualTime, 10, open);
						fclose(open);
						nactualTime = atoi(actualTime);
						if (nactualTime == 1 && isFromMain == 1 && creatingMatrix == 0) {
							puts("");
							Clock(1);
							puts("");
						}
					}
					if (isFromMain == 1) {
						printf("\n");
					}
					FILE* fout = NULL;
					while (fout == NULL) {
						fout = fopen(path, "a+");
					}
					fputs("\n", fout);
					fclose(fout);
					_delete(toOpen, "toOpen"); toOpen = nullptr;
					_delete(numSys, "numSys"); numSys = nullptr;
					_delete(siPref, "siPref"); siPref = nullptr;
					_delete(actualTime, "actualTime");  actualTime = nullptr;
				}
			}
			else {
				if (valGet == 0) {
					if (isFromMain == 1) {
						printf("\nError in syntax.\n\n");
					}
					FILE* fout = NULL;
					while (fout == NULL) {
						fout = fopen(path, "a+");
					}
					fprintf(fout, "\nError in syntax.\n\n");
					fclose(fout);
				}
			}
		}
	}
	_delete(vectorString, "vectorString"); vectorString = nullptr;
	_delete(exit, "exit"); exit = nullptr;
	_delete(varLetters, "varLetters"); varLetters = nullptr;
	_delete(saveArithTr, "saveArithTr"); saveArithTr = nullptr;
	_delete(dP, "dP"); dP = nullptr;
	_delete(bP, "bP"); bP = nullptr;
	_delete(oP, "oP"); oP = nullptr;
	_delete(hP, "hP"); hP = nullptr;
	_delete(toOpen, "toOpen"); toOpen = nullptr;

	return result1;
}
template double main_core<double>(char*, char*, FILE*, char*, double, double, int);
template mp_float main_core<mp_float>(char*, char*, FILE*, char*, mp_float, mp_float, int);





