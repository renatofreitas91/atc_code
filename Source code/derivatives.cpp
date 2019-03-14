

#include "stdafx.h"

char* getDerivative(char expression[DIM]) {
	double coefficient[dim], exponents[dim];
	char saveExpression[DIM] = "", value[DIM] = "";
	sprintf(saveExpression, "%s", expression);
	int i = 0, j = 0, k = 0;
	while (isContained("x^", saveExpression)) {
		i = strStart - 2;
		while (saveExpression[i] != '(') {
			i--;
		}
		i++;
		j = 0;
		while (saveExpression[i] != ')') {
			value[j] = saveExpression[i];
			j++; i++;
		}
		value[j] = '\0';
		math_processor(value);
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
		k++;
		char toReplace[DIM] = "";
		sprintf(toReplace, "x^%s", value);
		replace(toReplace, "   ", saveExpression);
		sprintf(saveExpression, "%s", expressionF);
	}
	if (isContained("x", saveExpression)) {
		i = strStart - 2;
		while (saveExpression[i] != '(') {
			i--;
		}
		i++;
		j = 0;
		while (saveExpression[i] != ')') {
			value[j] = saveExpression[i];
			j++; i++;
		}
		value[j] = '\0';
		math_processor(value);
		coefficient[k] = resultR;
		exponents[k] = 1;
		k++;
	}
	i = 0;
	sprintf(saveExpression, "");
	while (exponents[i] - 1 >= 1) {
		sprintf(saveExpression, "%s%Gx^%G+", saveExpression, exponents[i] * coefficient[i], exponents[i] - 1);
		i++;
	}
	sprintf(saveExpression, "%s%G", saveExpression, exponents[i] * coefficient[i]);
	if (isContained("-", saveExpression)) {
		replace("-", "_", saveExpression);
		sprintf(saveExpression, "%s", expressionF);
	}
	sprintf(expressionF, "%s", saveExpression);
	return expressionF;
}