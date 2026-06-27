
#include "stdafx.h"

char* buf = (char*)malloc(300);
char* bufText = getDynamicCharArray("", "bufText"), * OutputText = getDynamicCharArray("", "OutputText"), * prefixing = getDynamicCharArray("", "prefixing"), * errorText = getDynamicCharArray("", "errorText"), * variablesText = getDynamicCharArray("", "variablesText"), * renamedVariablesText = getDynamicCharArray("", "renamedVariablesText"), * timeText = getDynamicCharArray("", "timeText");
int isFromMainProcessor = 0, numSysNum = 0, modeNum = 0, timeNum = 0, prefixNum = 0;

template<typename T>
std::string formatFixedPrecisionValue(const PrecisionValue& value, int places) {
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(places) << precisionValueTo<T>(value);
	return stream.str();
}


template<typename T>
int parsePlacesValue(char* places) {
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
	int value = (int)solveMath<T>(places);
	resultR = savedResultR;
	resultI = savedResultI;
	return value;
}

static void normalizeBooleanInfinityConstants(char* expression) {
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

static bool extractMainProcessorSolverArgument(const char* expression, std::string& argument) {
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

static std::string stripMainProcessorSolverOuterParentheses(const std::string& source) {
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

static bool selectMainProcessorFirstLinearSolverFactor(const std::string& expression, std::string& factor) {
	std::string text = stripMainProcessorSolverOuterParentheses(expression);
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
				std::string candidate = stripMainProcessorSolverOuterParentheses(text.substr(1, i - 1));
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

static void normalizeMainProcessorSolverFastPath(char* expression) {
	if (expression == nullptr) {
		return;
	}
	std::string solverArgument;
	if (!extractMainProcessorSolverArgument(expression, solverArgument)) {
		return;
	}
	std::string reducedSolverArgument;
	std::string linearSolverFactor;
	std::string solverFactorSource = solverArgument;
	if (reduceExactRationalProductExpression(solverArgument.c_str(), reducedSolverArgument)) {
		solverFactorSource = reducedSolverArgument;
	}
	if (selectMainProcessorFirstLinearSolverFactor(solverFactorSource, linearSolverFactor)) {
		std::string normalizedSolver = "solver(" + linearSolverFactor + ")";
		if (normalizedSolver.size() < (size_t)DIM) {
			sprintf(expression, "%s", normalizedSolver.c_str());
		}
	}
}

template<typename T>
void main_processor(char* math_expression) {
	buf = (char*)malloc(300);
	isFromMainProcessor = 1;
	char* variable = getDynamicCharArray("", "variable");
	sprintf(buf, "");
	sprintf(OutputText, "");
	int tD = 0;
	char* trigData = getDynamicCharArray("", "trigData");
	int i = 0;
	char* arithTrig = getDynamicCharArray("", "arithTrig");
	sprintf(trigData, "%s", math_expression);
	for (tD = 0; tD < abs((int)strlen(trigData)); tD++) {
		fflush(NULL);

		varRename[0] = '\0';
		revariable[0] = '\0';
		validVar = 1;
		processingOK = 1;
		i = 0;
		int fl = 1, fr = 0;
		while (tD < abs((int)strlen(trigData)) && trigData[tD] != ',' && tD < abs((int)strlen(trigData))) {
			arithTrig[i] = trigData[tD];
			i++;
			tD++;
		}
		arithTrig[i] = '\0';
		if (abs((int)strlen(arithTrig)) > 0) {
			math_processor(arithTrig);
			char* newBuf = getDynamicCharArray("", "newBuf");
			sprintf(newBuf, "%s%s", buf, bufText);
			sprintf(buf, "%s", newBuf);
			_delete(newBuf, "newBuf"); newBuf = nullptr;
		}
		sprintf(expressionF, "%s", buf);

	}
	_delete(arithTrig, "arithTrig"); arithTrig = nullptr;
	isFromMainProcessor = 0;
	free(buf);
	_delete(variable, "variable"); variable = nullptr;
	_delete(trigData, "trigData"); trigData = nullptr;
}

template<typename T>

T math_processor(char* expression) {
	if (abs((int)strlen(expression)) > 0) {
		fflush(NULL);
		varRename[0] = '\0';
		validVar = 1;
		processingOK = 1;
		sprintf(bufText, "");
		char* arithTrig = getDynamicCharArray("", "arithTrig");
		char* variable = getDynamicCharArray("", "variable");
		sprintf(arithTrig, "%s", expression);
		resultR = 0;
		resultI = 0;
		int var = 0;
		int v = 0;
		verified = 0;
		rasf = 0;
		valid = 1;
		validVar = 1;
		verify = 0;
		sprintf(varRename, "");
		validVar = 1;
		processingOK = 1;
		resultR = 0;
		resultI = 0;
		validVar = 1;
		char* variableFeedback = getDynamicCharArray("", "variableFeedback");
		if (isContained("=", arithTrig)) {
			var = 1;
			int i = 0;
			for (i = 0; arithTrig[i] != '=' && i < abs((int)strlen(arithTrig)); i++) {
				variable[i] = arithTrig[i];
			}
			variable[i] = '\0';
			i = 0;
			int hk = variableValidator(variable);
			if (hk == 1) {
				processVariable<T>(revariable);
			}
			if (hk == 2) {
				sprintf(variableFeedback, "\n==> Your variable was renamed to \"%s\". <==\n\n",
					revariable);
			}
			if (hk == 0) {
				sprintf(variableFeedback,
					"\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
				var = 0;
			}
			char* toReplace = getDynamicCharArray("", "toReplace");
			sprintf(toReplace, "%s=", variable);
			replace(toReplace, "", arithTrig);
			sprintf(arithTrig, "%s", expressionF);
			_delete(toReplace, "toReplace");
			toReplace = nullptr;
		}
		sprintf(arithTrig, "%s", arithTrig);
		char* dP = getDynamicCharArray("", "dP"); char* bP = getDynamicCharArray("", "bP"); char* oP = getDynamicCharArray("", "oP"); char* hP = getDynamicCharArray("", "hP");
		int dp = -1, bp = -1, op = -1, hp = -1, r = 0;
		char* places = getDynamicCharArray("", "places");
		while ((arithTrig[0] == 'd' && arithTrig[1] == 'p' ||
			arithTrig[0] == 'b' && arithTrig[1] == 'p' ||
			arithTrig[0] == 'o' && arithTrig[1] == 'p' ||
			arithTrig[0] == 'h' && arithTrig[1] == 'p') && r < abs((int)strlen(arithTrig)) &&
			r < abs((int)strlen(arithTrig))) {
			if (arithTrig[0] == 'd' && arithTrig[1] == 'p') {
				r = 2;
				while ((arithTrig[r] == 'd' && arithTrig[r + 1] == 'p') == false &&
					r < abs((int)strlen(arithTrig))) {
					dP[r - 2] = arithTrig[r];
					r++;
				}
				dP[r - 2] = '\0';
				if (r < abs((int)strlen(arithTrig))) {
					if (isFromMainProcessor == 1) {
						isFromMainProcessor = 0;
						dp = parsePlacesValue<T>(dP);
						isFromMainProcessor = 1;
					}
					r = r + 2;
					int b = 0;
					for (b = 0; b < abs((int)strlen(arithTrig)); b++) {
						arithTrig[b] = arithTrig[b + r];
					}
				}
				else {
					dp = 10000;
					nPlaces = dp;
				}
			}
			if (arithTrig[0] == 'b' && arithTrig[1] == 'p') {
				r = 2;
				while ((arithTrig[r] == 'b' && arithTrig[r + 1] == 'p') == false &&
					r < abs((int)strlen(arithTrig))) {
					bP[r - 2] = arithTrig[r];
					r++;
				}
				bP[r - 2] = '\0';
				if (r < abs((int)strlen(arithTrig))) {
					if (isFromMainProcessor == 1) {
						isFromMainProcessor = 0;
						bp = parsePlacesValue<T>(bP);
						isFromMainProcessor = 1;
					}
					r = r + 2;
					int b = 0;
					for (b = 0; b < abs((int)strlen(arithTrig)); b++) {
						arithTrig[b] = arithTrig[b + r];
					}
				}
				else {
					bp = 1000;
					nPlaces = bp;
				}
			}
			if (arithTrig[0] == 'o' && arithTrig[1] == 'p') {
				r = 2;
				while ((arithTrig[r] == 'o' && arithTrig[r + 1] == 'p') == false &&
					r < abs((int)strlen(arithTrig))) {
					oP[r - 2] = arithTrig[r];
					r++;
				}
				oP[r - 2] = '\0';
				if (r < abs((int)strlen(arithTrig))) {
					op = parsePlacesValue<T>(oP);
					if (isFromMainProcessor == 1) {
						isFromMainProcessor = 0;
						op = parsePlacesValue<T>(oP);
						isFromMainProcessor = 1;
					}
					r = r + 2;
					int b = 0;
					for (b = 0; b < abs((int)strlen(arithTrig)); b++) {
						arithTrig[b] = arithTrig[b + r];
					}
				}
				else {
					op = 8000;
					nPlaces = op;
				}
			}
			if (arithTrig[0] == 'h' && arithTrig[1] == 'p') {
				r = 2;
				while ((arithTrig[r] == 'h' && arithTrig[r + 1] == 'p') == false &&
					r < abs((int)strlen(arithTrig))) {
					hP[r - 2] = arithTrig[r];
					r++;
				}
				hP[r - 2] = '\0';
				if (r < abs((int)strlen(arithTrig))) {
					if (isFromMainProcessor == 1) {
						isFromMainProcessor = 0;
						hp = parsePlacesValue<T>(hP);
						isFromMainProcessor = 1;
					}
					r = r + 2;
					int b = 0;
					for (b = 0; b < abs((int)strlen(arithTrig)); b++) {
						arithTrig[b] = arithTrig[b + r];
					}
				}
				else {
					hp = 16000;
					nPlaces = hp;
				}
			}
		}
		normalizeBooleanInfinityConstants(arithTrig);
		normalizeMainProcessorSolverFastPath(arithTrig);
		synTest = 0;
		if ((equationSolverRunning == false && solverRunning == false) || !isEqual(saveArithTrig, arithTrig)) {
			sprintf(saveArithTrig, "%s", arithTrig);
			manageExpression<T>(arithTrig, (T)0, (T)0, 1);
			sprintf(arithTrig, "%s", expressionF);
			sprintf(saveExpressionFF, "%s", expressionF);
			synTest = 0;
			if (isContained("(*(", arithTrig)) {
				replace("(*(", "((", arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
			verify = dataVerifier<T>(arithTrig, (T)0, (T)0, 1, 1);
		}
		else {
			if ((equationSolverRunning || solverRunning)) {
				sprintf(arithTrig, "%s", saveExpressionFF);
				verify = 1;
			}
		}
		if (verify == 1) {
			verified = 1;
			resultR = 0;
			resultI = 0;
			resultR = initialProcessor<T>(arithTrig, (T)0);
			if (resultR == 0 && solverRunning == false && equationSolverRunning == false) {
				resultR = initialProcessor<T>(arithTrig, (T)0);
			}
			if (resultR == 0 && solverRunning == false && equationSolverRunning == false) {
				resultR = initialProcessor<T>(arithTrig, (T)0);
			}
			if (resultR == 0 && solverRunning == false && equationSolverRunning == false) {
				resultR = initialProcessor<T>(arithTrig, (T)0);
			}
			sprintf(arithTrig, "");
			if (isFromMainProcessor == 1) {
				if (dp == -1) {
					convertComplex2Exponential(resultR, resultI);
					if (resultR > 0 && resultI > 0) {
						sprintf(bufText, "%s#%d=%s+%si\n", bufText, rf, respR, respI);
					}
					else {
						if (resultR > 0 && resultI < 0) {
							sprintf(bufText, "%s#%d=%s%si\n", bufText, rf, respR, respI);
						}
						else {
							if (resultR < 0 && resultI > 0) {
								sprintf(bufText, "%s#%d=%s+%si\n", bufText, rf, respR, respI);
							}
							else {
								if (resultR < 0 && resultI < 0) {
									sprintf(bufText, "%s#%d=%s%si\n", bufText, rf, respR, respI);
								}
								else {
									if (resultR == 0 && resultI == 0) {
										sprintf(bufText, "%s#%d=%s\n", bufText, rf, convert2Exponential(resultR));
									}
									else {
										if (resultR == 0 && resultI != 0) {
											sprintf(bufText, "%s#%d=%si\n", bufText, rf, convert2Exponential(resultI));
										}
										else {
											if (resultR != 0 && resultI == 0) {
												sprintf(bufText, "%s#%d=%s\n", bufText, rf, convert2Exponential(resultR));
											}
											else {
												sprintf(bufText, "%s#%d=%s+%si\n", bufText, rf, respR,
													respI);
											}
										}
									}
								}
							}
						}
					}
				}
				else {

                    std::string realFormatted = formatFixedPrecisionValue<T>(resultR, dp);
                    std::string imagFormatted = formatFixedPrecisionValue<T>(resultI, dp);
                    char* ansFormatted = getDynamicCharArray("", "ansFormatted");
                    if (resultR > 0 && resultI > 0) {
                        sprintf(ansFormatted, "#%d=%s+%si\n", rf, realFormatted.c_str(), imagFormatted.c_str());
                    }
                    if (resultR > 0 && resultI < 0) {
                        sprintf(ansFormatted, "#%d=%s%si\n", rf, realFormatted.c_str(), imagFormatted.c_str());
                    }
                    if (resultR < 0 && resultI > 0) {
                        sprintf(ansFormatted, "#%d=%s+%si\n", rf, realFormatted.c_str(), imagFormatted.c_str());
                    }
                    if (resultR < 0 && resultI < 0) {
                        sprintf(ansFormatted, "#%d=%s%si\n", rf, realFormatted.c_str(), imagFormatted.c_str());
                    }
                    if (resultR == 0 && resultI == 0) {
                        sprintf(ansFormatted, "#%d=%s\n", rf, realFormatted.c_str());
                    }
                    if (resultR == 0 && resultI != 0) {
                        sprintf(ansFormatted, "#%d=%si\n", rf, imagFormatted.c_str());
                    }
                    if (resultR != 0 && resultI == 0) {
                        sprintf(ansFormatted, "#%d=%s\n", rf, realFormatted.c_str());
                    }
                    sprintf(bufText, "%s%s", bufText, ansFormatted);
                    _delete(ansFormatted, "ansFormatted"); ansFormatted = nullptr;
				}
				ans[rf] = resultR;
				ansI[rf] = resultI;
				ansRV = resultR;
				ansIV = resultI;
				if (var == 1) {
					variableController(revariable, resultR);
				}
				sprintf(bufText, "%s%s", variableFeedback, bufText);
				char* numSysText = getDynamicCharArray("", "numSysText");
				if (numSysNum == 1 || bp != -1 || op != -1 || hp != -1) {
					char* syst = getDynamicCharArray("", "syst");
					sprintf(syst, "%s", convert2Exponential(resultR));
					if (isEqual(syst, "-NAN")) {
						sprintf(numSysText, "%s", numSysText);
						sprintf(numSysText, "%sIn binary=-NAN\n", numSysText);
						sprintf(numSysText, "%sIn octal=-NAN\n", numSysText);
						sprintf(numSysText, "%sIn hexadecimal=-NAN\n", numSysText);
					}
					else {
						if (syst[0] == 'I' && syst[1] == 'N' && syst[2] == 'F') {
							sprintf(numSysText, "%s", numSysText);
							sprintf(numSysText, "%sIn binary=INF\n", numSysText);
							sprintf(numSysText, "%sIn octal=INF\n", numSysText);
							sprintf(numSysText, "%sIn hexadecimal=INF\n", numSysText);
						}
						else {
							if (syst[0] == '-' && syst[1] == 'I' && syst[2] == 'N' && syst[3] == 'F') {
								puts("");
								sprintf(numSysText, "%sIn binary=-INF\n", numSysText);
								sprintf(numSysText, "%sIn octal=-INF\n", numSysText);
								sprintf(numSysText, "%sIn hexadecimal=-INF\n", numSysText);
							}
							else {
								if (resultR != 0 && resultI == 0 || resultR == 0 && resultI == 0) {
									sprintf(numSysText, "%s\nReal part:\n", numSysText);
									decimalToBinary(resultR, "history.txt", bp);
									sprintf(numSysText, "%s%s", numSysText, numSys);
									decimalToOctal(resultR, "history.txt", op);
									sprintf(numSysText, "%s%s", numSysText, numSys);
									decimalToHexadecimal(resultR, "history.txt", hp);
									sprintf(numSysText, "%s%s", numSysText, numSys);
								}
								else {
									if (resultR != 0 && resultI != 0) {
										sprintf(numSysText, "%s\nReal part:\n", numSysText);
										decimalToBinary(resultR, "history.txt", bp);
										sprintf(numSysText, "%s%s", numSysText, numSys);
										decimalToOctal(resultR, "history.txt", op);
										sprintf(numSysText, "%s%s", numSysText, numSys);
										decimalToHexadecimal(resultR, "history.txt", hp);
										sprintf(numSysText, "%s%s", numSysText, numSys);
										sprintf(numSysText, "%s\nImaginary part:\n", numSysText);
										decimalToBinary(resultI, "history.txt", bp);
										sprintf(numSysText, "%s%s", numSysText, numSys);
										decimalToOctal(resultI, "history.txt", op);
										sprintf(numSysText, "%s%s", numSysText, numSys);
										decimalToHexadecimal(resultI, "history.txt", hp);
										sprintf(numSysText, "%s%s", numSysText, numSys);
									}
									else {
										if (resultI != 0) {
											sprintf(numSysText, "%s\nImaginary part:\n", numSysText);
											decimalToBinary(resultI, "history.txt", bp);
											sprintf(numSysText, "%s%s", numSysText, numSys);
											decimalToOctal(resultI, "history.txt", op);
											sprintf(numSysText, "%s%s", numSysText, numSys);
											decimalToHexadecimal(resultI, "history.txt", hp);
											sprintf(numSysText, "%s%s", numSysText, numSys);
										}

									}
								}
							}
						}
					}
					sprintf(bufText, "%s\n%s", bufText, numSysText);
					_delete(syst, "syst"); syst = nullptr;
				}
				char* prefixText = getDynamicCharArray("", "prefixText");
				if (prefixNum == 1) {
					char* pref = getDynamicCharArray("", "pref");
					sprintf(pref, "%s", convert2Exponential(resultR));
					if (isEqual(pref, "-NAN")) {

						sprintf(prefixText, "%s=-NAN\n", prefixText);

					}
					else {
						if (pref[0] == 'I' && pref[1] == 'N' && pref[2] == 'F') {

							sprintf(prefixText, "%s=INF\n", prefixText);

						}
						else {
							if (pref[0] == '-' && pref[1] == 'I' && pref[2] == 'N' &&
								pref[3] == 'F') {
								sprintf(prefixText, "%s=-INF\n", prefixText);


							}
							else {
								sprintf(prefixText, "%s\nReal part:\n", prefixText);
								prefixDeterminator(resultR, "history.txt");
								sprintf(prefixText, "%s%s", prefixText, prefixing);
							}
						}
					}

					sprintf(pref, "%s", convert2Exponential(resultI));
					if (isEqual(pref, "-NAN(IND)")) {
						sprintf(prefixText, "%s=-NAN\n", prefixText);
					}
					else {
						if (pref[0] == 'I' && pref[1] == 'N' && pref[2] == 'F') {
							sprintf(prefixText, "%s=INF\n", prefixText);

						}
						else {
							if (pref[0] == '-' && pref[1] == 'I' && pref[2] == 'N' &&
								pref[3] == 'F') {
								sprintf(prefixText, "%s=-INF\n", prefixText);

							}
							else {
								sprintf(prefixText, "%s\nImaginary part:\n", prefixText);
								prefixDeterminator(resultI, "history.txt");
								sprintf(prefixText, "%s%s", prefixText, prefixing);
							}
						}
					}
					sprintf(bufText, "%s\n%s", bufText, prefixText);
					_delete(pref, "pref"); pref = nullptr;
				}
				if (timeNum == 1) {
					Clock(1);
					sprintf(bufText, "%s\n%s", bufText, timeText);
				}
				_delete(numSysText, "numSysText"); numSysText = nullptr;
				_delete(prefixText, "prefixText"); prefixText = nullptr;
			}
		}
		else {
			sprintf(bufText, "%s%s\n\nError in syntax\n\n%s\n", bufText, errorText, expression);
		}
		sprintf(expressionF, "%s", bufText);
		if (arithTrig != nullptr && abs((int)strlen(arithTrig)) >= 0) {
			_delete(arithTrig, "arithTrig"); arithTrig = nullptr;
		}
		_delete(variable, "variable"); variable = nullptr;
		_delete(variableFeedback, "variableFeedback"); variableFeedback = nullptr;
		_delete(dP, "dP"); dP = nullptr;
		_delete(bP, "bP"); bP = nullptr;
		_delete(oP, "oP"); oP = nullptr;
		_delete(hP, "hP"); hP = nullptr;
		_delete(places, "places"); places = nullptr;
		return precisionValueTo<T>(resultR);
	}
	resultR = -7777777;
	return -7777777;
}

template<typename T>
T solveMath(char* expression) {
	if (abs((int)strlen(expression)) > 0) {
		fflush(NULL);
		validVar = 1;
		processingOK = 1;
		char* arithTrig = getDynamicCharArray("", "arithTrig");
		char* variable = getDynamicCharArray("", "variable");
		sprintf(arithTrig, "%s", expression);
		resultR = 0;
		resultI = 0;
		int var = 0;
		int v = 0;
		verified = 0;
		rasf = 0;
		valid = 1;
		validVar = 1;
		verify = 0;
		sprintf(varRename, "");
		validVar = 1;
		processingOK = 1;
		resultR = 0;
		resultI = 0;
		validVar = 1;
		synTest = 0;
		if ((equationSolverRunning == false && solverRunning == false) || !isEqual(saveArithTrig, arithTrig)) {
			sprintf(saveArithTrig, "%s", arithTrig);
			manageExpression<T>(arithTrig, (T)0, (T)0, 1);
			sprintf(arithTrig, "%s", expressionF);
			sprintf(saveExpressionFF, "%s", expressionF);
			synTest = 0;
			if (isContained("(*(", arithTrig)) {
				replace("(*(", "((", arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
			verify = dataVerifier<T>(arithTrig, (T)0, (T)0, 1, 1);
		}
		else {
			if ((equationSolverRunning || solverRunning)) {
				sprintf(arithTrig, "%s", saveExpressionFF);
				verify = 1;
			}
		}
		if (verify == 1) {
			verified = 1;
			resultR = 0;
			resultI = 0;
			resultR = initialProcessor<T>(arithTrig, (T)0);
			_delete(arithTrig, "arithTrig");
			_delete(variable, "variable");
			return precisionValueTo<T>(resultR);
		}
		_delete(arithTrig, "arithTrig");
		_delete(variable, "variable");

	}
	resultR = 0;

	return precisionValueTo<T>(resultR);
}

void print(char* data) {
	sprintf(OutputText, "%s\n%s", OutputText, data);
}
template double solveMath<double>(char*);
template mp_float solveMath<mp_float>(char*);


template <>
PrecisionValue solveMath<PrecisionValue>(char* expression) {
    if (higherPrecision == 1) {
        return solveMath<mp_float>(expression);
    }
    return solveMath<double>(expression);
}
