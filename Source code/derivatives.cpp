

#include "stdafx.h"

char* getDerivative(char expression[DIM]) {
	if (isContained("((", expression) && isContained("))", expression)) {
		replace("((", "(", expression);
		sprintf(expression, "%s", expressionF);
		replace("))", ")", expression);
		sprintf(expression, "%s", expressionF);
	}
	double coefficient[dim], exponents[dim];
	char saveExpression[DIM] = "", value[DIM] = "";
	sprintf(saveExpression, "%s", expression);
	char to_replace[DIM] = "";
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
		if (saveExpression[strlen(saveExpression) - 1] == 'x'&&strlen(saveExpression) - 1 == 0) {
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
		while (saveExpression[i] != 'x'&&saveExpression[i] != '\0') {
			value[j] = saveExpression[i];
			j++; i++;
		}
		value[j] = '\0';
		math_processor(value);
		sprintf(to_replace, "%s", value);
		sprintf(value, "");
		coefficient[k] = resultR;
		isContained("x^", saveExpression);
		i = strEnd;
		j = 0;
		while (verifyNumber(saveExpression[i])) {
			value[j] = saveExpression[i];
			j++; i++;
		}
		value[j] = '\0';
		math_processor(value);
		exponents[k] = resultR;
		coefficient[k] = exponents[k] * coefficient[k];
		k++;
		char toReplace[DIM] = "";
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
	}
	i = 0;
	sprintf(saveExpression, "");
	while (exponents[i] > 1) {
		sprintf(saveExpression, "%s(%G+0i)x^%G+", saveExpression, coefficient[i], exponents[i] - 1);
		i++;
	}
	sprintf(saveExpression, "%s(%G+0i)", saveExpression, coefficient[i]);
	if (isContained("x^", saveExpression)) {
		sprintf(expressionF, "(%s)", saveExpression);
	}
	else {
		sprintf(expressionF, "%s", saveExpression);
	}
	replaceTimes = 0;
	if (isContained("-", expressionF)) {
		replace("-", "_", expressionF);
	}
	return expressionF;
}