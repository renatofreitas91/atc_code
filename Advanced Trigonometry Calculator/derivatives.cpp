

#include "stdafx.h"
char* returnCharArray = getDynamicCharArray("", "returnCharArray");

template <typename T>
char* getDerivative(char* expression) {
	if (isContained("((", expression) && isContained("))", expression)) {
		replace("((", "(", expression);
		sprintf(expression, "%s", expressionF);
		replace("))", ")", expression);
		sprintf(expression, "%s", expressionF);
	}
	T* coefficient = getDynamicArray<T>(DIMDOUBLE); T* exponents = getDynamicArray<T>(DIMDOUBLE);
	char* saveExpression = getDynamicCharArray("", "saveExpression"); char* value = getDynamicCharArray("", "value");
	sprintf(saveExpression, "%s", expression);
	char* to_replace = getDynamicCharArray("", "to_replace");
	int i = 0, j = 0, k = 0;
	if (isContained("x-", saveExpression)) {
		replace("x-", "x^1-", saveExpression);
		sprintf(saveExpression, "%s", expressionF);
	}
	if (isContained("x+", saveExpression)) {
		replace("x+", "x^1+", saveExpression);
		sprintf(saveExpression, "%s", expressionF);
	}
	else {
		if (saveExpression[abs((int)strlen(saveExpression)) - 1] == 'x'&&abs((int)strlen(saveExpression)) - 1 == 0) {
			replace("x", "(1+0i)x^1", saveExpression);
			sprintf(saveExpression, "%s", expressionF);
		}
		else {
			if (isContained("x", saveExpression)) {
				replaceTimes = 1;
				if (saveExpression[strEnd] != '^') {
					replace("x", "X^1", saveExpression);
					replace("X", "x", saveExpression);
					sprintf(saveExpression, "%s", expressionF);
				}
				replaceTimes = 0;
			}
		}
	}
	replaceTimes = 1;
	while (isContained("x^", saveExpression)) {
		sprintf(value, "");
		i = strStart - 2;
		while (saveExpression[i] != '('&&i > 0) {
			i--;
		}
		j = 0;
		while (saveExpression[i] != 'x'&&i < abs((int)strlen(saveExpression))) {
			value[j] = saveExpression[i];
			j++; i++;
		}
		value[j] = '\0';
		solveMath<T>(value);
		sprintf(to_replace, "%s", value);
		sprintf(value, "");
		coefficient[k] = precisionValueTo<T>(resultR);
		isContained("x^", saveExpression);
		i = strEnd;
		j = 0;
		while (verifyNumber(saveExpression[i])) {
			value[j] = saveExpression[i];
			j++; i++;
		}
		value[j] = '\0';
		solveMath<T>(value);
		exponents[k] = precisionValueTo<T>(resultR);
		coefficient[k] = exponents[k] * coefficient[k];
		k++;
		char* toReplace = getDynamicCharArray("", "toReplace");
		sprintf(toReplace, "x^%s", value);
		replace(toReplace, "", saveExpression);
		sprintf(saveExpression, "%s", expressionF);
		replaceTimes = 1;
		replace(to_replace, "", saveExpression);
		sprintf(saveExpression, "%s", expressionF);
		replaceTimes = 1;
		if (isContained("+", saveExpression) && strStart == 0) {
			replace("+", "", saveExpression);
			sprintf(saveExpression, "%s", expressionF);
		}
		_delete(toReplace, "toReplace");
		toReplace = nullptr;
	}
	i = 0;
	sprintf(saveExpression, "");
	while (exponents[i] > 1) {
		convertComplex2Exponential(coefficient[i], exponents[i] - 1);
		sprintf(saveExpression, "%s(%s+0i)x^%s+", saveExpression, respR, respI);
		i++;
	}
	sprintf(saveExpression, "%s(%s+0i)", saveExpression, convert2Exponential(coefficient[i]));
	if (isContained("x^", saveExpression)) {
		sprintf(saveExpression, "(%s)", saveExpression);
	}
	replaceTimes = 0;
	if (isContained("-", saveExpression)) {
		replace("-", "_", saveExpression);
		sprintf(saveExpression, "%s", expressionF);
	}
	sprintf(expressionF, "");
	sprintf(returnCharArray, "%s", saveExpression);
	_delete(coefficient, "coefficient"); coefficient = nullptr;  _delete(exponents, "exponents"); exponents = nullptr;
	_delete(saveExpression, "saveExpression"); saveExpression = nullptr;
	if (value != nullptr) {
		_delete(value, "value"); value = nullptr;
	}
	_delete(to_replace, "to_replace"); to_replace = nullptr;
	return returnCharArray;
}


template char* getDerivative<double>(char*);
