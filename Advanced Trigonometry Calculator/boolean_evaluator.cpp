
#include "stdafx.h"
template <typename T>
bool advancedEvaluator(char* expression) {
	replaceTimes = 0;
	renamer(expression);
	sprintf(expression, "%s", expressionF);
	replaceTimes = 1;
	int h = 0;
	bool result = false;
	int cp = 0, mark = 0;
	int c = 0, cLogical = 0, d = 0, l = 0, *parent=getDynamicIntArray();
	int s = 0, k = 0, g = 0;
	for (s = 0; s < abs((int)strlen(expression)); s++) {
		parent[s] = 0;
	}
	char* validOperations = getDynamicCharArray("!(,, )==,)!=,)&&,)||", "validOperations");
	int w = 0;
	for (s = 0; s < abs((int)strlen(expression)) && s < abs((int)strlen(expression)); s++) {
		bool containsRightPar = false;
		if (s + 1 < abs((int)strlen(expression))) {
			containsRightPar = isContainedByIndex(")", expression, s + 1);
		}
		int y = 0;
		if (expression[s] == '(') {
			bool proceed = true;
			if (s > 0) {
				char* logic = getDynamicCharArray("", "logic");
				logic[0] = expression[s - 1];
				if (isContained(logic, validOperations)) {
					proceed = true;
				}
				else {
					proceed = false;
				}
				_delete(logic, "logic");
				logic = nullptr;
			}
			else {
				if (s != 0) {
					proceed = false;
				}
			}
			if (proceed) {
				w = s;
				y = w;
				w++;
				int kr = 0, kl = 1;
				while (kl != kr && w < abs((int)strlen(expression))) {
					if (expression[w] == ')') {
						kr++;
					}
					if (expression[w] == '(') {
						kl++;
					}
					w++;
				}
				if (w < abs((int)strlen(expression)) && expression[w] == ')') {
					proceed = false;
				}
				if (proceed) {
					if (kl == kr && w < abs((int)strlen(expression))) {
						w--;
						char* logic = getDynamicCharArray("", "logic");
						logic[0] = expression[w];
						if (isContained(logic, validOperations)) {
							if (expression[s - 1] != '(') {
								w++;
								d = 0;
								c++;
								parent[s] = c;
								d = 1;
								k = c;
								s = w - 2;
								w = w - 1;
							}
						}
						_delete(logic, "logic");
						logic = nullptr;
					}
					else {
						if (kl == kr && w == abs((int)strlen(expression))) {
							w--;
							d = 0;
							c++;
							parent[y] = c;
							d = 1;
							k = c;
							s = w - 2;

						}

					}
				}
			}
		}
		else {
			char* logic = getDynamicCharArray("", "logic");
			sprintf(logic, "");
			if (s + 1 < abs((int)strlen(expression))) {
				logic[0] = expression[s + 1];
				logic[1] = '\0';
			}
			if (expression[s] == ')' && s == w && c > 0 && ((s + 1 == abs((int)strlen(expression))) || (abs((int)strlen(logic)) >= 1 && isContained(logic, validOperations)))) {
				bool proceed = true;
				if (s > 0) {
					if (verifyLetter(expression[s + 1]) || verifyNumber(expression[s + 1])) {
						proceed = false;
					}
				}
				if (proceed) {
					d = 0;
					h = 0;
					l = 2;
					do {
						l = 0;
						h = 0;
						while (h < abs((int)strlen(expression))) {
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
					while (l != 1 && h < abs((int)strlen(expression))) {
						h = 0;
						l = 0;
						while (h < abs((int)strlen(expression))) {
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
			}
			else {
				parent[s] = 0;
			}
			_delete(logic, "logic");
			logic = nullptr;
		}
	}
	int klp = s;
	expression[s] = '\0';
	int curPar = 0, cur = 0;
	int i = 0;

	replaceTimes = 0;
	if (c > 0) {
		countSplits = countOccurrences(",", validOperations);
		split(",", validOperations);
		i = 0;

		while (i <= countSplits) {
			if (isContained(splitResult[i], expression)) {
				curPar = 1;
				break;
			}
			i++;
		}
	}
	_delete(validOperations, "validOperations");
	validOperations = nullptr;
	if (curPar == 0) {
		result = simpleEvaluator<T>(expression);
		return result;
	}
	replaceTimes = 0;
	char* amp = getDynamicCharArray("", "amp");
	sprintf(amp, "");
	int j = 0;
	l = 0; k = 0;
	int a = 0;
	int de = 0, ju = 0;
	c = 0;
	char* pas = getDynamicCharArray("", "pas");
	sprintf(pas, "");
	int se = 0;
	int thj = 0;
	if (curPar == 1) {
		char* newExpression = getDynamicCharArray("", "newExpression");
		sprintf(newExpression, "");
		char* finalExpression = getDynamicCharArray("", "finalExpression");
		sprintf(finalExpression, "");
		sprintf(newExpression, "%s", expression);
		sprintf(finalExpression, "%s", expression);
		for (i = 0; i < abs((int)strlen(expression)); i++) {
			a = 0;
			while (!isContainedByIndex("!=", expression, i) && !isContainedByIndex("==", expression, i) && !isContainedByIndex("&&", expression, i) && !isContainedByIndex("||", expression, i) && parent[i] == 0 && i < abs((int)strlen(expression))) {
				pas[a] = expression[i];
				a++;
				i++;
				if (!(parent[i] == 0)) {
					if (countOccurrences("(", pas) > countOccurrences(")", pas)) {
						sprintf(pas, "%s)", pas);
						i++;
						a = abs((int)strlen(pas));
					}
					else {
						pas[a] = '\0';
						a--;
						while (verifyLetter(pas[a])) {
							a--;
						}
						a++;
						char* function = getDynamicCharArray("", "function");
						sprintf(function, "");
						int x = 0;
						while (verifyLetter(pas[a])) {
							function[x] = pas[a];
							x++; a++;
						}
						function[x] = '?'; function[x + 1] = '\0';

						T funcF = functionProcessor<T>(function, 2, 7, 12, "");
						if (funcF == 0.5) {
							pas[a] = expression[i];
							a++;
							i++;
						}
						_delete(function, "function");
						function = nullptr;
					}
				}
			}
			pas[a] = '\0';
			if (abs((int)strlen(pas)) > 0) {
				result = simpleEvaluator<T>(pas);
				replaceTimes = 1;
				char* expr = getDynamicCharArray("", "expr");
				sprintf(expr, "");
				sprintf(expr, "(%s)", pas);
				if (isContained(expr, newExpression)) {
					if (result) {
						replace(expr, "true", finalExpression);
						sprintf(finalExpression, "%s", expressionF);
					}
					else {
						replace(expr, "false", finalExpression);
						sprintf(finalExpression, "%s", expressionF);
					}
				}
				else {
					sprintf(expr, "(%s", pas);
					if (isContained(expr, newExpression)) {
						if (result) {
							replace(expr, "true", finalExpression);
							sprintf(finalExpression, "%s", expressionF);
						}
						else {
							replace(expr, "false", finalExpression);
							sprintf(finalExpression, "%s", expressionF);
						}
					}
					else {
						sprintf(expr, "%s)", pas);
						if (isContained(expr, newExpression)) {
							if (result) {
								replace(expr, "true", finalExpression);
								sprintf(finalExpression, "%s", expressionF);
							}
							else {
								replace(expr, "false", finalExpression);
								sprintf(finalExpression, "%s", expressionF);
							}
						}
						else {
							if (isContained(expr, newExpression)) {
								if (result) {
									replace(expr, "true", finalExpression);
									sprintf(finalExpression, "%s", expressionF);
								}
								else {
									replace(expr, "false", finalExpression);
									sprintf(finalExpression, "%s", expressionF);
								}
							}
						}
					}
				}
				replaceTimes = 0;
				renamer(finalExpression);
				sprintf(finalExpression, "%s", expressionF);
				replaceTimes = 0;
				_delete(expr, "expr");
				expr = nullptr;
			}
			pas[a] = '\0';
			if (expression[i] == '!' && expression[i + 1] == '(') {
				i++;
			}
			cur = parent[i];
			j = i;
			if (parent[i] == cur) {
				i = j;
				a = 0;
				i++;
				while (parent[i] != cur && i < abs((int)strlen(expression))) {
					pas[a] = expression[i];
					a++; i++;
				}
				pas[a] = '\0';
				int kl = 0;
				int p = 0;

				while (p <= countSplits) {
					if (isContained(splitResult[p], pas)) {
						kl = 1;
						break;
					}
					p++;
				}
				a = 0;
				if (kl == 0) {
					if (abs((int)strlen(pas)) > 0) {
						bool removedLeft = false, removedRight = false;
						replaceTimes = 1;
						if (isContained("(", pas) && strStart == 0) {
							replace("(", "", pas);
							removedLeft = true;
							sprintf(pas, "%s", expressionF);
							replaceTimes = 1;
							if (isContained(")", pas) && strEnd == abs((int)strlen(pas)) - 1) {
								removedRight = true;
								pas[abs((int)strlen(pas)) - 1] = '\0';
							}
						}

						result = simpleEvaluator<T>(pas);
						replaceTimes = 1;
						char* expr = getDynamicCharArray("", "expr");
						sprintf(expr, "");
						if (removedLeft && removedRight) {
							sprintf(expr, "%s", pas);
						}
						if (!removedLeft && removedRight) {
							sprintf(expr, "(%s", pas);
						}
						if (removedLeft && !removedRight) {
							sprintf(expr, "%s)", pas);
						}
						if (!removedLeft && !removedRight) {
							sprintf(expr, "%s", pas);
						}
						if (isContained(expr, newExpression)) {
							if (result) {
								replace(expr, "true", finalExpression);
								sprintf(finalExpression, "%s", expressionF);
							}
							else {
								replace(expr, "false", finalExpression);
								sprintf(finalExpression, "%s", expressionF);
							}
						}
						else {

							if (isContained(expr, newExpression)) {
								if (result) {
									replace(expr, "true", finalExpression);
									sprintf(finalExpression, "%s", expressionF);
								}
								else {
									replace(expr, "false", finalExpression);
									sprintf(finalExpression, "%s", expressionF);
								}
							}
							else {
								if (isContained(expr, newExpression)) {
									if (result) {
										replace(expr, "true", finalExpression);
										sprintf(finalExpression, "%s", expressionF);
									}
									else {
										replace(expr, "false", finalExpression);
										sprintf(finalExpression, "%s", expressionF);
									}
								}
								else {
									if (isContained(expr, newExpression)) {
										if (result) {
											replace(expr, "true", finalExpression);
											sprintf(finalExpression, "%s", expressionF);
										}
										else {
											replace(expr, "false", finalExpression);
											sprintf(finalExpression, "%s", expressionF);
										}
									}
								}
							}
						}
						replaceTimes = 1;
						if (isContained("(true)", finalExpression)) {
							replace("(true)", "true", finalExpression);
							sprintf(finalExpression, "%s", expressionF);
						}
						if (isContained("(false)", finalExpression)) {
							replace("(false)", "false", finalExpression);
							sprintf(finalExpression, "%s", expressionF);
						}
						replaceTimes = 0;
						renamer(finalExpression);
						sprintf(finalExpression, "%s", expressionF);
						replaceTimes = 1;
						pas[0] = '\0';
						ju = 0;
					}
				}
				if (kl == 1) {
					if (abs((int)strlen(pas)) > 0) {

						result = advancedEvaluator<T>(pas);
						replaceTimes = 1;
						sprintf(expr, "(%s)", pas);
						if (isContained(expr, newExpression)) {
							if (result) {
								replace(expr, "true", finalExpression);
								sprintf(finalExpression, "%s", expressionF);
							}
							else {
								replace(expr, "false", finalExpression);
								sprintf(finalExpression, "%s", expressionF);
							}
						}
						else {
							if (isContained(expr, newExpression)) {
								if (result) {
									replace(expr, "true", finalExpression);
									sprintf(finalExpression, "%s", expressionF);
								}
								else {
									replace(expr, "false", finalExpression);
									sprintf(finalExpression, "%s", expressionF);
								}
							}
							else {
								if (isContained(expr, newExpression)) {
									if (result) {
										replace(expr, "true", finalExpression);
										sprintf(finalExpression, "%s", expressionF);
									}
									else {
										replace(expr, "false", finalExpression);
										sprintf(finalExpression, "%s", expressionF);
									}
								}
								else {
									if (isContained(expr, newExpression)) {
										if (result) {
											replace(expr, "true", finalExpression);
											sprintf(finalExpression, "%s", expressionF);
										}
										else {
											replace(expr, "false", finalExpression);
											sprintf(finalExpression, "%s", expressionF);
										}
									}
								}
							}
						}
						replaceTimes = 0;
						renamer(finalExpression);
						sprintf(finalExpression, "%s", expressionF);
						replaceTimes = 1;
					}
				}
			}
		}
		result = simpleEvaluator<T>(finalExpression);
		_delete(newExpression, "newExpression");
		newExpression = nullptr;
		_delete(finalExpression, "finalExpression");
		finalExpression = nullptr;
	}
	_delete(amp, "amp");
	amp = nullptr;
	_delete(pas, "pas");
	pas = nullptr;
	return result;
}
template<typename T>

bool simpleEvaluator(char* expression) {
	replaceTimes = 0;
	renamer(expression);
	sprintf(expression, "%s", expressionF);
	replaceTimes = 1;
	int i = 0;
	if (isContained("iscontained(", expression)) {
		i = strEnd;
		int saveStrStart = strStart;
		int j = 0;
		char* to_find = getDynamicCharArray("", "to_find");
		sprintf(to_find, "");
		char* data = getDynamicCharArray("", "data");
		sprintf(data, "");
		if (countOccurrences("\\", expression) == 1) {
			while (expression[i] != '\\') {
				to_find[j] = expression[i];
				i++; j++;
			}
			to_find[j] = '\0';
			stringVariableToString(to_find);
			sprintf(to_find, "%s", variableSTring);
			i++;
			j = 0;
			while (expression[i] != ')' && i < abs((int)strlen(expression))) {
				data[j] = expression[i];
				i++; j++;
			}
			data[j] = '\0';
			stringVariableToString(data);
			sprintf(data, "%s", variableSTring);
			int save_i = i + 1;
			char* toReplace = getDynamicCharArray("", "toReplace");
			sprintf(toReplace, "");
			i = saveStrStart;
			j = 0;
			while (i < save_i) {
				toReplace[j] = expression[i];
				i++; j++;
			}
			toReplace[j] = '\0';
			char* replacement = getDynamicCharArray("", "replacement");
			sprintf(replacement, "");
			if (isContained(to_find, data)) {
				sprintf(replacement, "true");
			}
			else {
				sprintf(replacement, "false");
			}
			replace(toReplace, replacement, expression);
			sprintf(expression, "%s", expressionF);
			_delete(toReplace, "toReplace");
			toReplace = nullptr;
			_delete(replacement, "replacement");
			replacement = nullptr;
		}
		else {
			puts("\nError: Please use one time \"\\\" to separate the two variables.\n");
		}
		_delete(to_find, "to_find");
		to_find = nullptr;
		_delete(data, "data");
		data = nullptr;
	}
	if (isContained("iscontainedbyindex(", expression)) {
		i = strEnd;
		int saveStrStart = strStart;
		int j = 0;
		char* to_find = getDynamicCharArray("", "to_find");
		sprintf(to_find, "");
		char* data = getDynamicCharArray("", "data");
		sprintf(data, "");
		char* index = getDynamicCharArray("", "index");
		sprintf(index, "");
		if (countOccurrences("\\", expression) == 2) {
			while (expression[i] != '\\') {
				to_find[j] = expression[i];
				i++; j++;
			}
			to_find[j] = '\0';
			stringVariableToString(to_find);
			sprintf(to_find, "%s", variableSTring);
			i++;
			j = 0;
			while (expression[i] != '\\') {
				data[j] = expression[i];
				i++; j++;
			}
			data[j] = '\0';
			stringVariableToString(data);
			sprintf(data, "%s", variableSTring);
			i++;
			j = 0;
			while (expression[i] != ')' && i < abs((int)strlen(expression))) {
				index[j] = expression[i];
				i++; j++;
			}
			index[j] = '\0';
			int index_num = (int)calcNow<T>(index, (T)0, (T)0);
			int save_i = i + 1;

			char* toReplace = getDynamicCharArray("", "toReplace");
			sprintf(toReplace, "");
			i = saveStrStart;
			j = 0;
			while (i < save_i) {
				toReplace[j] = expression[i];
				i++; j++;
			}
			toReplace[j] = '\0';
			char* replacement = getDynamicCharArray("", "replacement");
			sprintf(replacement, "");
			if (isContainedByIndex(to_find, data, index_num)) {
				sprintf(replacement, "true");
			}
			else {
				sprintf(replacement, "false");
			}
			replace(toReplace, replacement, expression);
			sprintf(expression, "%s", expressionF);
			_delete(toReplace, "toReplace");
			toReplace = nullptr;
			_delete(replacement, "replacement");
			replacement = nullptr;

		}
		else {
			puts("\nError: Please use two times \"\\\" to separate the three variables.\n");
		}
		_delete(to_find, "to_find");
		to_find = nullptr;
		_delete(data, "data");
		data = nullptr;
		_delete(index, "index");
		index = nullptr;
	}
	if (isContained("iscontainedvariable(", expression)) {
		i = strEnd;
		int saveStrStart = strStart;
		int j = 0;
		char* to_find = getDynamicCharArray("", "to_find");
		sprintf(to_find, "");
		char* data = getDynamicCharArray("", "data");
		sprintf(data, "");
		if (countOccurrences("\\", expression) == 1) {
			while (expression[i] != '\\') {
				to_find[j] = expression[i];
				i++; j++;
			}
			to_find[j] = '\0';
			renamer(to_find);
			sprintf(to_find, "%s", expressionF);
			i++;
			j = 0;
			while (expression[i] != ')' && i < abs((int)strlen(expression))) {
				data[j] = expression[i];
				i++; j++;
			}
			data[j] = '\0';
			stringVariableToString(data);
			sprintf(data, "%s", variableSTring);
			renamer(data);
			sprintf(data, "%s", expressionF);
			int save_i = i + 1;
			char* toReplace = getDynamicCharArray("", "toReplace");
			sprintf(toReplace, "");
			i = saveStrStart;
			j = 0;
			while (i < save_i) {
				toReplace[j] = expression[i];
				i++; j++;
			}
			toReplace[j] = '\0';
			char* replacement = getDynamicCharArray("", "replacement");
			sprintf(replacement, "");
			if (isContainedVariable(to_find, data)) {
				sprintf(replacement, "true");
			}
			else {
				sprintf(replacement, "false");
			}
			replace(toReplace, replacement, expression);
			sprintf(expression, "%s", expressionF);
			_delete(toReplace, "toReplace");
			toReplace = nullptr;
			_delete(replacement, "replacement");
			replacement = nullptr;
		}
		else {
			puts("\nError: Please use one time \"\\\" to separate the two variables.\n");
		}
		_delete(to_find, "to_find");
		to_find = nullptr;
		_delete(data, "data");
		data = nullptr;
	}
	if (isContained("isequal(", expression)) {
		i = strEnd;
		int saveStrStart = strStart;
		int j = 0;
		char* to_find = getDynamicCharArray("", "to_find");
		sprintf(to_find, "");
		char* data = getDynamicCharArray("", "data");
		sprintf(data, "");
		if (countOccurrences("\\", expression) == 1) {
			while (expression[i] != '\\') {
				to_find[j] = expression[i];
				i++; j++;
			}
			to_find[j] = '\0';
			stringVariableToString(to_find);
			sprintf(to_find, "%s", variableSTring);
			i++;
			j = 0;
			while (expression[i] != ')' && i < abs((int)strlen(expression))) {
				data[j] = expression[i];
				i++; j++;
			}
			data[j] = '\0';
			stringVariableToString(data);
			sprintf(data, "%s", variableSTring);
			int save_i = i + 1;
			char* toReplace = getDynamicCharArray("", "toReplace");
			sprintf(toReplace, "");
			i = saveStrStart;
			j = 0;
			while (i < save_i) {
				toReplace[j] = expression[i];
				i++; j++;
			}
			toReplace[j] = '\0';
			char* replacement = getDynamicCharArray("", "replacement");
			sprintf(replacement, "");
			if (isEqual(to_find, data)) {
				sprintf(replacement, "true");
			}
			else {
				sprintf(replacement, "false");
			}
			replace(toReplace, replacement, expression);
			sprintf(expression, "%s", expressionF);
			_delete(toReplace, "toReplace");
			toReplace = nullptr;
			_delete(replacement, "replacement");
			replacement = nullptr;
		}
		else {
			puts("\nError: Please use one time \"\\\" to separate the two variables.\n");
		}
		_delete(to_find, "to_find");
		to_find = nullptr;
		_delete(data, "data");
		data = nullptr;
	}
	if (isContained("isVariable<T>(", expression)) {
		i = strEnd;
		int saveStrStart = strStart;
		int j = 0;
		char* verify = getDynamicCharArray("", "verify");
		sprintf(verify, "");
		while (expression[i] != ')') {
			verify[j] = expression[i];
			i++; j++;
		}
		verify[j] = '\0';
		renamer(verify);
		sprintf(verify, "%s", expressionF);
		int save_i = i + 1;
		char* toReplace = getDynamicCharArray("", "toReplace");
		sprintf(toReplace, "");
		i = saveStrStart;
		j = 0;
		while (i < save_i) {
			toReplace[j] = expression[i];
			i++; j++;
		}
		toReplace[j] = '\0';
		char* replacement = getDynamicCharArray("", "replacement");
		sprintf(replacement, "");
		if (::isVariable(verify)) {
			sprintf(replacement, "true");
		}
		else {
			sprintf(replacement, "false");
		}
		replace(toReplace, replacement, expression);
		sprintf(expression, "%s", expressionF);
		_delete(verify, "verify");
		verify = nullptr;
		_delete(toReplace, "toReplace");
		toReplace = nullptr;
		_delete(replacement, "replacement");
		replacement = nullptr;
	}
	if (isContained("istowrite(", expression)) {
		i = strEnd;
		int saveStrStart = strStart;
		int j = 0;
		char* verify = getDynamicCharArray("", "verify");
		sprintf(verify, "");
		while (expression[i] != ')' && i < abs((int)strlen(expression))) {
			verify[j] = expression[i];
			i++; j++;
		}
		verify[j] = '\0';
		stringVariableToString(verify);
		sprintf(verify, "%s", variableSTring);
		int save_i = i + 1;
		char* toReplace = getDynamicCharArray("", "toReplace");
		sprintf(toReplace, "");
		i = saveStrStart;
		j = 0;
		while (i < save_i) {
			toReplace[j] = expression[i];
			i++; j++;
		}
		toReplace[j] = '\0';
		char* replacement = getDynamicCharArray("", "replacement");
		sprintf(replacement, "");
		if (isToWrite(verify)) {
			sprintf(replacement, "true");
		}
		else {
			sprintf(replacement, "false");
		}
		replace(toReplace, replacement, expression);
		sprintf(expression, "%s", expressionF);
		_delete(verify, "verify");
		verify = nullptr;
		_delete(toReplace, "toReplace");
		toReplace = nullptr;
		_delete(replacement, "replacement");
		replacement = nullptr;
	}
	int toSolve = 0;
	char* saveExpression = getDynamicCharArray("", "saveExpression");
	sprintf(saveExpression, "");
	replaceTimes = 0;
	sprintf(expressionF, expression);
	if (isContained("==", expressionF)) {
		toSolve = 1;
		replace("==", "  ", expressionF);
	}
	if (isContained("!=", expressionF)) {
		toSolve = 1;
		replace("!=", "  ", expressionF);
	}
	if (isContained("<=", expressionF)) {
		toSolve = 1;
		replace("<=", "  ", expressionF);
	}
	if (isContained(">=", expressionF)) {
		toSolve = 1;
		replace(">=", "  ", expressionF);
	}
	if (isContained(">", expressionF)) {
		toSolve = 1;
		replace(">", " ", expressionF);
	}
	if (isContained("<", expressionF)) {
		toSolve = 1;
		replace("<", " ", expressionF);
	}
	if (isContained("&&", expressionF)) {
		toSolve = 1;
		replace("&&", "  ", expressionF);
	}
	if (isContained("||", expressionF)) {
		toSolve = 1;
		replace("||", "  ", expressionF);
	}
	char* valuesToExtract = getDynamicCharArray("", "valuesToExtract");
	sprintf(valuesToExtract, "");
	sprintf(valuesToExtract, expressionF);
	int s = 0, k = 0;
	sprintf(expressionF, expression);



	if (isContained("==", expressionF)) {
		toSolve = 1;
		replace("==", "  ", expressionF);
	}
	if (isContained("!=", expressionF)) {
		toSolve = 1;
		replace("!=", "  ", expressionF);
	}
	if (isContained("!", expressionF)) {
		toSolve = 1;
		replace("!", " ", expressionF);
	}
	if (isContained("!", expressionF)) {
		toSolve = 1;
		replace("!", " ", expressionF);
	}
	if (isContained("<=", expressionF)) {
		toSolve = 1;
		replace("<=", "  ", expressionF);
	}
	if (isContained(">=", expressionF)) {
		toSolve = 1;
		replace(">=", "  ", expressionF);
	}
	if (isContained(">", expressionF)) {
		toSolve = 1;
		replace(">", " ", expressionF);
	}
	if (isContained("<", expressionF)) {
		toSolve = 1;
		replace("<", " ", expressionF);
	}
	if (isContained("&&", expressionF)) {
		toSolve = 1;
		replace("&&", "  ", expressionF);
	}
	if (isContained("||", expressionF)) {
		toSolve = 1;
		replace("||", "  ", expressionF);
	}
	sprintf(valuesToExtract, expressionF);
	sprintf(saveExpression, expression);
	if (toSolve == 1) {
		char* saveValues = getDynamicCharArray("", "saveValues");
		sprintf(saveValues, "");
		sprintf(valuesToExtract, expressionF);
		char* symbols = getDynamicCharArray("", "symbols");
		sprintf(symbols, "");
		int g = 0, h = 0;
		for (g = 0; g < abs((int)strlen(valuesToExtract)); g++) {
			if (valuesToExtract[g] == ' ') {
				while (valuesToExtract[g] == ' ') {
					symbols[h] = saveExpression[g];
					h++; g++;
				}
				symbols[h] = ',';
				h++;
			}
		}
		symbols[h] = '\0';
		char* newSymbol = getDynamicCharArray("", "newSymbol");
		sprintf(newSymbol, "");
		char* getSymbol = getDynamicCharArray("", "getSymbol");
		sprintf(getSymbol, "");
		int s = 0, t = 0, k = 0;
		for (s = 0; s < abs((int)strlen(symbols)); s++) {
			t = 0;
			while (symbols[s] != ',' && s < abs((int)strlen(symbols))) {
				getSymbol[t] = symbols[s];
				t++; s++;
			}
			getSymbol[t] = '\0';
			if (isEqual("==", getSymbol)) {
				newSymbol[k] = '0';
				k++;
			}
			if (isEqual("!=", getSymbol)) {
				newSymbol[k] = '1';
				k++;
			}
			if (isEqual("<=", getSymbol)) {
				newSymbol[k] = '2';
				k++;
			}
			if (isEqual(">=", getSymbol)) {
				newSymbol[k] = '3';
				k++;
			}
			if (isEqual(">", getSymbol)) {
				newSymbol[k] = '4';
				k++;
			}
			if (isEqual("<", getSymbol)) {
				newSymbol[k] = '5';
				k++;
			}
			if (isEqual("&&", getSymbol)) {
				newSymbol[k] = '6';
				k++;
			}
			if (isEqual("||", getSymbol)) {
				newSymbol[k] = '7';
				k++;
			}
			if (isEqual("!", getSymbol) || isContained("!!", getSymbol)) {
				int count = countOccurrences("!", getSymbol);
				if (count > 0) {
					while (count > 0) {
						newSymbol[k] = '8';
						k++;
						count--;
					}
				}
			}

		}
		newSymbol[k] = '\0';

		sprintf(expressionF, valuesToExtract);
		if (isContained("  ", expressionF)) {
			replace("  ", ",", valuesToExtract);
		}
		if (isContained(" ", expressionF)) {
			replace(" ", ",", expressionF);
		}
		sprintf(valuesToExtract, expressionF);
		h = 0;
		bool* results = getDynamicArray<bool>(DIM);
		while (h < DIM) {
			results[h] = 0;
			h++;
		}
		T* valuesR = getDynamicArray<T>(DIMDOUBLE); T* valuesI = getDynamicArray<T>(DIMDOUBLE);
		int* boolValue = getDynamicIntArray();
		h = 0;
		while (h < DIM) {
			boolValue[h] = -1;
			h++;
		}
		char* values = getDynamicCharArray("", "values");
		sprintf(values, "");
		sprintf(expressionF, "");
		int f = 0;
		for (g = 0; g < abs((int)strlen(valuesToExtract)); g++) {
			h = 0;
			if (valuesToExtract[g] != ',' && g < abs((int)strlen(valuesToExtract))) {
				while (valuesToExtract[g] != ',' && g < abs((int)strlen(valuesToExtract))) {
					values[h] = valuesToExtract[g];
					h++; g++;
				}
				values[h] = '\0';
				replaceTimes = 0;
				if (isContained(" ", values)) {
					replace(" ", "", values);
					sprintf(values, expressionF);
				}
				renamer(values);
				sprintf(values, "%s", expressionF);
				if (isContained("Jruw", values) || isContained("true", values)) {
					boolValue[f] = 1;
				}
				if (isContained("falsw", values) || isContained("false", values)) {
					boolValue[f] = 0;
				}
				calcNow<T>(values, (T)0, (T)0);
				char* pointer;
				char* value = getDynamicCharArray("", "value");
				sprintf(value, "");
				sprintf(value, "%G", precisionValueTo<double>(resultR));
				valuesR[f] = strtod(value, &pointer);
				sprintf(value, "%G", precisionValueTo<double>(resultI));
				valuesI[f] = strtod(value, &pointer);
				_delete(value, "value");
				f++;
			}
		}
		h = 0;
		g = 0;
		int b = 0;
		replaceTimes = 1;
		bool relational = false;
		while (h < f) {

			if (newSymbol[h] == '0') {
				if (boolValue[g] == -1 && boolValue[g + 1] == -1) {
					results[b] = valuesR[g] == valuesR[g + 1] && valuesI[g] == valuesI[g + 1];
					boolValue[b] = (int)results[b];
					replaceTimes = 1;
					replaceByIndex("0", "9", newSymbol, h);
					sprintf(newSymbol, "%s", expressionF);
					b++;
					g = g + 2;
				}
				else {
					if (boolValue[g] != -1 && boolValue[g + 1] != -1) {
						results[b] = (bool)valuesR[g] == (bool)valuesR[g + 1];
						boolValue[b] = (int)results[b];
						replaceTimes = 1;
						replaceByIndex("0", "9", newSymbol, h);
						sprintf(newSymbol, "%s", expressionF);
						b++;
						g = g + 2;
					}
					else {
						if (boolValue[g] != -1) {
							results[b] = (bool)valuesR[g];
							boolValue[b] = (int)results[b];
							b++;
							g++;
						}
						else {
							if (boolValue[g + 1] != -1) {
								b++;
								g++;
								results[b + 1] = (bool)valuesR[g + 1];
								boolValue[b + 1] = (int)results[b + 1];
								b++;
								g++;
							}
						}
					}
				}
			}

			if (newSymbol[h] == '1') {
				if (boolValue[g] == -1 && boolValue[g + 1] == -1) {
					results[b] = valuesR[g] != valuesR[g + 1] || valuesI[g] != valuesI[g + 1];
					boolValue[b] = (int)results[b];
					replaceTimes = 1;
					replaceByIndex("1", "9", newSymbol, h);
					sprintf(newSymbol, "%s", expressionF);
					b++;
					g = g + 2;
				}
				else {
					if (boolValue[g] != -1 && boolValue[g + 1] != -1) {
						results[b] = (bool)valuesR[g] != (bool)valuesR[g + 1];
						boolValue[b] = (int)results[b];
						b++;
						g = g + 2;
						replaceTimes = 1;
						replaceByIndex("1", "9", newSymbol, h);
						sprintf(newSymbol, "%s", expressionF);
					}
					else {
						if (boolValue[g] != -1) {
							results[b] = (bool)valuesR[g];
							boolValue[b] = (int)results[b];
							b++;
							g++;
						}
						else {
							if (boolValue[g + 1] != -1) {
								b++;
								g++;
								results[b + 1] = (bool)valuesR[g + 1];
								boolValue[b + 1] = (int)results[b + 1];
								b++;
								g++;
							}
						}
					}
				}
			}
			if (newSymbol[h] == '2') {
				results[b] = valuesR[g] <= valuesR[g + 1] && valuesI[g] <= valuesI[g + 1];
				boolValue[b] = (int)results[b];
				replaceTimes = 1;
				replaceByIndex("2", "9", newSymbol, h);
				sprintf(newSymbol, "%s", expressionF);
				b++;
				g = g + 2;

			}
			if (newSymbol[h] == '3') {
				results[b] = valuesR[g] >= valuesR[g + 1] && valuesI[g] >= valuesI[g + 1];
				boolValue[b] = (int)results[b];
				replaceTimes = 1;
				replaceByIndex("3", "9", newSymbol, h);
				sprintf(newSymbol, "%s", expressionF);
				b++;
				g = g + 2;
			}
			if (newSymbol[h] == '4') {
				results[b] = valuesR[g] > valuesR[g + 1] && valuesI[g] >= valuesI[g + 1];
				boolValue[b] = (int)results[b];
				replaceTimes = 1;
				replaceByIndex("4", "9", newSymbol, h);
				sprintf(newSymbol, "%s", expressionF);
				b++;
				g = g + 2;

			}
			if (newSymbol[h] == '5') {
				results[b] = valuesR[g] < valuesR[g + 1] && valuesI[g] <= valuesI[g + 1];
				boolValue[b] = (int)results[b];
				replaceTimes = 1;
				replaceByIndex("5", "9", newSymbol, h);
				sprintf(newSymbol, "%s", expressionF);
				b++;
				g = g + 2;

			}

			if (newSymbol[h] == '6') {

				if (boolValue[g] != -1 && boolValue[g + 1] != -1) {
					results[b] = (bool)valuesR[g] && (bool)valuesR[g + 1];
					boolValue[b] = (int)results[b];
					replaceTimes = 1;
					replaceByIndex("6", "9", newSymbol, h);
					sprintf(newSymbol, "%s", expressionF);
					b++;
					g = g + 2;
				}

				else {
					if (boolValue[g] != -1) {
						results[b] = (bool)valuesR[g];
						boolValue[b] = (int)results[b];
						replaceTimes = 1;
						replaceByIndex("6", "9", newSymbol, h);
						sprintf(newSymbol, "%s", expressionF);
						b++;
						g++;
					}
					else {
						if (boolValue[g + 1] != -1) {
							results[b + 1] = (bool)valuesR[g + 1];
							boolValue[b + 1] = (int)results[b + 1];
							replaceTimes = 1;
							replaceByIndex("6", "9", newSymbol, h);
							sprintf(newSymbol, "%s", expressionF);
							b = b + 2;
							g = g + 2;
						}
					}
				}
			}

			if (newSymbol[h] == '7') {
				if (boolValue[g] != -1 && boolValue[g + 1] != -1) {
					results[b] = (bool)valuesR[g] || (bool)valuesR[g + 1];
					boolValue[b] = (int)results[b];
					replaceTimes = 1;
					replaceByIndex("7", "9", newSymbol, h);
					sprintf(newSymbol, "%s", expressionF);
					b++;
					g = g + 2;
				}
				else {
					if (boolValue[g] != -1) {
						results[b] = (bool)valuesR[g];
						boolValue[b] = (int)results[b];
						replaceTimes = 1;
						replaceByIndex("6", "9", newSymbol, h);
						sprintf(newSymbol, "%s", expressionF);
						b++;
						g++;
					}
					else {
						if (boolValue[g + 1] != -1) {
							results[b + 1] = (bool)valuesR[g + 1];
							boolValue[b + 1] = (int)results[b];
							replaceTimes = 1;
							replaceByIndex("6", "9", newSymbol, h);
							sprintf(newSymbol, "%s", expressionF);
							b = b + 2;
							g = g + 2;
						}
					}
				}
			}

			if (newSymbol[h] == '8') {
				if (boolValue[g] != -1) {
					results[b] = (bool)valuesR[g];
					while (newSymbol[h] == '8') {
						results[b] = !results[b];
						boolValue[b] = (int)results[b];
						replaceTimes = 1;
						replace("8", "9", newSymbol);
						sprintf(newSymbol, "%s", expressionF);
					}
					b++;
					g++;
				}
			}

			h++;
		}
		if (isContained("9", newSymbol)) {
			replaceTimes = 0;
			replace("9", "", newSymbol);
			sprintf(newSymbol, "%s", expressionF);
			replaceTimes = 1;
		}


		replaceTimes = 1;
		g = 0;
		h = 0;
		while (g < b) {
			if (newSymbol[g] == '0' || newSymbol[g] == '1' || newSymbol[g] == '6' || newSymbol[g] == '7' || newSymbol[g] == '8') {
				if (boolValue[g] == 1) {
					results[h] = true;
					relational = true;
				}
				else {
					if (boolValue[g] == 0) {
						results[h] = false;
						relational = true;
					}
				}
			}
			if (newSymbol[g] == '0') {
				if (relational) {
					replaceTimes = 1;
					results[h] = results[g] == results[g + 1];
					replaceByIndex("0", "9", newSymbol, h);
					sprintf(newSymbol, "%s", expressionF);
					h++;
					relational = false;
				}
				else {
					results[h] = valuesR[g] == valuesR[g + 1] && valuesI[g] == valuesI[g + 1];
					replaceTimes = 1;
					replaceByIndex("0", "9", newSymbol, h);
					sprintf(newSymbol, "%s", expressionF);
					h++;
				}

			}

			if (newSymbol[g] == '1') {
				if (relational) {
					results[h] = results[g] != results[g + 1];
					replaceTimes = 1;
					replaceByIndex("1", "9", newSymbol, h);
					sprintf(newSymbol, "%s", expressionF);
					h++;
					relational = false;
				}
				else {
					results[h] = valuesR[g] != valuesR[g + 1] || valuesI[g] != valuesI[g + 1];
					replaceTimes = 1;
					replaceByIndex("1", "9", newSymbol, h);
					sprintf(newSymbol, "%s", expressionF);
					h++;
				}

			}
			if (newSymbol[g] == '2') {
				results[h] = valuesR[g] <= valuesR[g + 1] && valuesR[g] <= valuesI[g + 1];
				replaceTimes = 1;
				replaceByIndex("2", "9", newSymbol, h);
				sprintf(newSymbol, "%s", expressionF);
				h++;
			}
			if (newSymbol[g] == '3') {
				results[h] = valuesR[g] >= valuesR[g + 1] && valuesI[g] >= valuesI[g + 1];
				replaceTimes = 1;
				replaceByIndex("3", "9", newSymbol, h);
				sprintf(newSymbol, "%s", expressionF);
				h++;
			}
			if (newSymbol[g] == '4') {
				results[b] = valuesR[g] > valuesR[g + 1] && valuesI[g] >= valuesI[g + 1];
				replaceTimes = 1;
				replaceByIndex("4", "9", newSymbol, h);
				sprintf(newSymbol, "%s", expressionF);
				h++;
			}
			if (newSymbol[g] == '5') {
				results[h] = valuesR[g] < valuesR[g + 1] && valuesI[g] <= valuesI[g + 1];
				replaceTimes = 1;
				replaceByIndex("5", "9", newSymbol, h);
				sprintf(newSymbol, "%s", expressionF);
				h++;
			}
			if (newSymbol[g] == '6') {
				if (relational) {
					results[h] = results[g] && results[g + 1];
					replaceTimes = 1;
					replaceByIndex("6", "9", newSymbol, h);
					sprintf(newSymbol, "%s", expressionF);
					h++;
					relational = false;
				}

			}
			if (newSymbol[g] == '7') {
				if (relational) {
					results[h] = (results[g] || results[g + 1]);
					replaceTimes = 1;
					replaceByIndex("7", "9", newSymbol, h);
					sprintf(newSymbol, "%s", expressionF);
					h++;
					relational = false;
				}

			}
			if (newSymbol[g] == '8') {
				if (relational) {
					results[h] = !results[g];
					replaceTimes = 1;
					replaceByIndex("8", "9", newSymbol, h);
					sprintf(newSymbol, "%s", expressionF);
					h++;
					relational = false;
				}

			}
			char* df = getDynamicCharArray("", "df");
			sprintf(df, "");
			if (h + 1 < abs((int)strlen(newSymbol))) {
				sprintf(df, "%c", newSymbol[h + 1]);
				if (atoi(df) < 2 || atoi(df) > 5) {
					g++;
					if (boolValue[g] != -1) {
						relational = true;
					}
				}
				else {
					if (atoi(df) >= 2) {
						g++;
						relational = false;
					}

				}
			}
			_delete(df, "df");
			df = nullptr;
			g++;

		}
		if (isContained("9", newSymbol)) {
			replaceTimes = 0;
			replace("9", "", newSymbol);
			sprintf(newSymbol, "%s", expressionF);
			replaceTimes = 1;
		}
		g = 0;
		while (g < h) {
			if (newSymbol[g] == '0') {
				results[g] = results[g] == results[g + 1];
				int y = g + 1;
				while (y < f) {
					results[y] = results[y + 1];
					y++;
				}
				y = g;
				while (y < f) {
					newSymbol[y] = newSymbol[y + 1];
					y++;
				}
			}
			g = g + 2;
		}
		g = 0;

		while (g < h) {
			if (newSymbol[g] == '1') {
				results[g] = results[g] != results[g + 1];
				int y = g + 1;
				while (y < f) {
					results[y] = results[y + 1];
					y++;
				}
				y = g;
				while (y < f) {
					newSymbol[y] = newSymbol[y + 1];
					y++;
				}
			}
			g = g + 2;
		}
		g = 0;

		while (g < h) {
			if (newSymbol[g] == '8') {
				results[g] = !results[g];
				int y = g;
				while (y < f) {
					newSymbol[y] = newSymbol[y + 1];
					y++;
				}
			}
			g++;
		}
		g = 0;
		while (g < h) {
			if (newSymbol[g] == '6') {
				results[g] = results[g] && results[g + 1];
				int y = g + 1;
				while (y < f) {
					results[y] = results[y + 1];
					y++;
				}
				y = g;
				while (y < f) {
					newSymbol[y] = newSymbol[y + 1];
					y++;
				}
			}
			g = g + 2;
		}
		g = 0;
		while (g < h) {
			if (newSymbol[g] == '7') {
				results[g] = results[g] || results[g + 1];
				int y = g + 1;
				while (y < f) {
					results[y] = results[y + 1];
					y++;
				}
				y = g;
				while (y < f) {
					newSymbol[y] = newSymbol[y + 1];
					y++;
				}

			}
			g = g + 2;
		}
		bool result = results[0];
		if (results != nullptr) {
			_delete(results, "results"); results = nullptr;
		}
		if (valuesR != nullptr) {
			_delete(valuesR, "valuesR"); valuesR = nullptr;
		}
		if (valuesI != nullptr) {
			_delete(valuesI, "valuesI"); valuesI = nullptr;
		}
		_delete(boolValue, "boolValue"); boolValue = nullptr;
		_delete(saveExpression, "saveExpression");
		saveExpression = nullptr;
		_delete(valuesToExtract, "valuesToExtract");
		valuesToExtract = nullptr;
		_delete(saveValues, "saveValues");
		saveValues = nullptr;
		_delete(symbols, "symbols");
		symbols = nullptr;
		_delete(values, "values");
		values = nullptr;
		_delete(getSymbol, "getSymbol"); getSymbol = nullptr;
		_delete(newSymbol, "newSymbol"); newSymbol = nullptr;
		return result;
	}
	if (toSolve == 0) {
		_delete(saveExpression, "saveExpression");
		saveExpression = nullptr;
		_delete(valuesToExtract, "valuesToExtract");
		valuesToExtract = nullptr;
		T result = calcNow<T>(expression, (T)0, (T)0);
		if (resultR == 1 && resultI == 0) {
			return true;
		}
		if (resultR == 0 && resultI == 0) {
			return false;
		}
	}
	return false;
}

template bool advancedEvaluator<double>(char*);

