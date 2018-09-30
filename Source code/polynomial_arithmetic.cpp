
#include "stdafx.h"
#include "calc.h"

void sum_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]) {
	sprintf(roots, "");
	char polynomial_sum[DIM] = "";
	sprintf(polynomial_sum, "%s+%s", polynomial_1, polynomial_2);
	replaceTimes = 0;
	equationSolver(polynomial_sum);
	rootsToPolynomial(roots);
	sprintf(expressionF, "%s", expressionF);
	if (isContained("\n", expressionF)) {
		replace("\n", "", expressionF);
	}
	replaceTimes = 1;
	char toTest[DIM] = "";
	sprintf(toTest, "(%s)", expressionF);
	boolean testNeedPar = dataVerifier(toTest, 0, 0, 0, 1);
	if (testNeedPar) {
		sprintf(expressionF, toTest);
	}
}

void sub_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]) {
	sprintf(roots, "");
	char polynomial_sub[DIM] = "";
	sprintf(expressionF, "%s", polynomial_2);
	replaceTimes = 0;
	if (isContained("(x", expressionF)) {
		replace("(x", "(_1*X", expressionF);
	}
	if (isContained("x", expressionF)) {
		replace("x", "*_1*X", expressionF);
	}
	if (isContained(")", expressionF)) {
		replace(")", "*_1]", expressionF);
	}
	if (isContained("X", expressionF)) {
		replace("X", "x", expressionF);
	}
	if (isContained("]", expressionF)) {
		replace("]", ")", expressionF);
	}
	if (isContained("-*", expressionF)) {
		replace("-*", "-", expressionF);
	}
	replaceTimes = 1;
	sprintf(polynomial_2, expressionF);
	sprintf(polynomial_sub, "%s+%s", polynomial_1, polynomial_2);
	sprintf(roots, "");
	replaceTimes = 0;
	equationSolver(polynomial_sub);
	rootsToPolynomial(roots);
	if (isContained("\n", expressionF)) {
		replace("\n", "", expressionF);
	}
	replaceTimes = 1;
	char toTest[DIM] = "";
	sprintf(toTest, "(%s)", expressionF);
	boolean testNeedPar = dataVerifier(toTest, 0, 0, 0, 1);
	if (testNeedPar) {
		sprintf(expressionF, toTest);
	}
}

void multi_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]) {
	sprintf(roots, "");
	replaceTimes = 0;
	equationSolver(polynomial_1);
	equationSolver(polynomial_2);
	rootsToPolynomial(roots);
	if (isContained("\n", expressionF)) {
		replace("\n", "", expressionF);
	}
	sprintf(expressionF, "(%s)", expressionF);
	replaceTimes = 1;
}

void div_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]) {
	sprintf(roots, "");
	char expressionS[DIM] = "";
	char divExpression[DIM] = "";
	char exprProcessed[DIM] = "";
	sprintf(expressionS, "%s/%s", polynomial_1, polynomial_2);
	int j = 0;
	isContained(")/(", expressionS);
	sprintf(roots, "");
	int i = strStart - 1;
	int saveStrEnd = strEnd;
	int kr = 1, kl = 0;
	while (kr != kl && expressionS[i] != '\0') {
		if (expressionS[i] == ')') {
			kr++;
		}
		if (expressionS[i] == '(') {
			kl++;
		}
		i--;
	}
	i++;
	j = 0;
	while ((expressionS[i] == '/'&&expressionS[i + 1] == '(') == false && expressionS[i] != '\0') {
		divExpression[j] = expressionS[i];
		j++; i++;
	}
	divExpression[j] = '\0';
	sprintf(exprProcessed, "%s%s/", exprProcessed, divExpression);
	j = 0;
	sprintf(roots, "");
	replaceTimes = 0;
	equationSolver(divExpression);
	replaceTimes = 1;
	sprintf(divExpression, "");
	if (roots[0] == '\\') {
		int y = 1;
		for (y = 1; y < abs((int)strlen(roots)); y++) {
			roots[y - 1] = roots[y];
		}
		roots[y - 1] = '\0';
	}
	replaceTimes = 0;
	rootsToPolynomial(roots);
	replaceTimes = 1;
	char simplifiedMulti[DIM] = "";
	char newPolynomial[DIM] = "";
	int y = 0;
	int k = 0;
	while (expressionF[k] != '\0') {
		newPolynomial[y] = expressionF[k];
		y++; k++;
	}
	newPolynomial[y] = '\0';
	double valuesR[dim] = { 0,0,0 }, valuesI[dim] = { 0,0,0 };
	y = 0;
	int r = 0, s = 0;
	char value[DIM] = "";
	while (newPolynomial[y] != '\0') {
		if (newPolynomial[y] == '(') {
			y++;
			r = 0;
			while (newPolynomial[y] != ')'&&newPolynomial[y] != '\0') {
				value[r] = newPolynomial[y];
				r++; y++;
			}
			value[r] = '\0';
			calcNow(value, 0, 0);
			sprintf(value, "");
			valuesR[s] = resultR; valuesI[s] = resultI;
			s++;
		}
		y++;
	}
	int maxExponent = s;
	y = s;
	s = 0;
	while (s < y) {
		s++;
	}
	i = saveStrEnd - 1;
	kr = 0; kl = 0;
	while (kr != kl || (kl == 0 && kr == 0)) {
		if (expressionS[i] == ')') {
			kr++;
		}
		if (expressionS[i] == '(') {
			kl++;
		}
		divExpression[j] = expressionS[i];
		j++; i++;
	}
	divExpression[j] = '\0';
	j = 0;
	sprintf(roots, "");
	replaceTimes = 0;
	equationSolver(divExpression);
	replaceTimes = 1;
	sprintf(exprProcessed, "%s%s", exprProcessed, divExpression);
	sprintf(divExpression, "");
	if (roots[0] == '\\') {
		y = 1;
		for (y = 1; y < abs((int)strlen(roots)); y++) {
			roots[y - 1] = roots[y];
		}
		roots[y - 1] = '\0';
	}
	double rootsR[dim] = { 0,0,0 }, rootsI[dim] = { 0,0,0 };
	int d = 0;
	int o = 0;
	char rValues[DIM] = "";
	sprintf(rValues, "");
	int numberRoots = countOccurrences("\\", roots) + 1;
	while (roots[d] != '\0'&&numberRoots > 0) {
		r = 0;
		sprintf(rValues, "");
		while (roots[d] != '\\'&&roots[d] != '\0'&&numberRoots > 0) {
			rValues[r] = roots[d];
			r++; d++;
		}
		rValues[r] = '\0';
		calcNow(rValues, 0, 0);
		rootsR[o] = resultR; rootsI[o] = resultI;
		o++;
		d++;
		numberRoots--;
	}
	int hj = s;
	int f = 0;
	int ro = 0, po = 0;
	double resR = 0, resI = 0;
	int kk = s, m = 0;
	while (ro < o) {
		resR = rootsR[ro]; resI = rootsI[ro];
		double ValueR = valuesR[0], ValueI = valuesI[0];
		multiplication(resR, resI, ValueR, ValueI);
		for (po = 1; po < s; po++) {
			sum(valuesR[po], valuesI[po], resultR, resultI);
			valuesR[po] = resultR; valuesI[po] = resultI;
			multiplication(resR, resI, resultR, resultI);
		}
		ro++;
		s--;
	}
	maxExponent = maxExponent - o - 1;
	char polynomial[DIM] = "";
	f = 0;
	while (maxExponent >= 0) {
		if (maxExponent > 1) {
			sprintf(polynomial, "%s(%G+%Gi)x^%d+", polynomial, valuesR[f], valuesI[f], maxExponent);
		}
		else {
			if (maxExponent == 1) {
				sprintf(polynomial, "%s(%G+%Gi)x+", polynomial, valuesR[f], valuesI[f]);
			}
			else {
				sprintf(polynomial, "%s(%G+%Gi)", polynomial, valuesR[f], valuesI[f]);
			}
		}
		maxExponent--;
		f++;
	}
	replaceTimes = 0;
	if (isContained("-", polynomial)) {
		replace("-", "_", polynomial);
		sprintf(polynomial, expressionF);
	}
	sprintf(expressionF, polynomial);
	if (isContained("\n", expressionF)) {
		replace("\n", "", expressionF);
	}
	replaceTimes = 1;
	char toTest[DIM] = "";
	sprintf(toTest, "(%s)", expressionF);
	boolean testNeedPar = dataVerifier(toTest, 0, 0, 0, 1);
	if (testNeedPar) {
		sprintf(expressionF, toTest);
	}
}