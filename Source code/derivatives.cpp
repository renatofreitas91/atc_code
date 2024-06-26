

#include "stdafx.h"
char returnCharArray[DIM] = "";

char* getDerivative(char expression[DIM]) {
	if (isContained("((", expression) && isContained("))", expression)) {
		replace("((", "(", expression);
		sprintf(expression, "%s", expressionF);
		replace("))", ")", expression);
		sprintf(expression, "%s", expressionF);
	}
	double coefficient[dime], exponents[dime];
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
		solveMath(value);
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
		solveMath(value);
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
	return returnCharArray;
}