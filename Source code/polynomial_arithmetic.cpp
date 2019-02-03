
#include "stdafx.h"
#include "calc.h"

double LastDividerR = 1, LastDividerI = 1;
boolean isDivisible = true;


void sum_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]) {
	/*sprintf(expressionF, "%s*(0x+1)",polynomial_1);
	simpleSimplifyPolynomial(expressionF);
	sprintf(polynomial_1, "%s",expressionF);
	sprintf(expressionF, "%s*(0x+1)", polynomial_2);
	simpleSimplifyPolynomial(expressionF);
	sprintf(polynomial_2, "%s",expressionF);*/
	lastDividerR = 1;
	lastDividerI = 0;
	LastDividerR = 1;
	LastDividerI = 0;
	sprintf(roots, "");
	char polynomial_sum[DIM] = "";
	sprintf(polynomial_sum, "%s+%s+(0x+0)", polynomial_1, polynomial_2);
	equationSolver(polynomial_sum);
	sprintf(expressionF, "");
	if (isContained("\\", roots) || strlen(roots) > 0) {
		rootsToPolynomial(roots);
	}
	else {
		sprintf(expressionF, "((%G+%Gi)x+(%G+%Gi))", 0.0, 0.0, lastDividerR, lastDividerI);
		if (isContained("+-", expressionF)) {
			replaceTimes = 0;
			replace("+-", "+_", expressionF);
		}
		if (isContained("(-", expressionF)) {
			replaceTimes = 0;
			replace("(-", "(_", expressionF);
		}
	}
	replaceTimes = 0;
}

void sub_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]) {
	sprintf(expressionF, "%s*(0x+1)", polynomial_1);
	simpleSimplifyPolynomial(expressionF);
	sprintf(polynomial_1, "%s", expressionF);
	sprintf(expressionF, "%s*(0x+1)", polynomial_2);
	simpleSimplifyPolynomial(expressionF);
	sprintf(polynomial_2, "%s", expressionF);
	if (!isEqual(polynomial_1, polynomial_2)) {
		int v = 0;
		char to_replace[DIM] = "";
		if (polynomial_1[v + 1] == polynomial_2[v + 1]) {
			while (polynomial_1[v + 2] == polynomial_2[v + 2] && polynomial_2[v + 2] != '(') {
				to_replace[v] = polynomial_1[v + 1];
				v++;
			}
			if (polynomial_1[v + 2] == polynomial_2[v + 2]) {
				to_replace[v] = polynomial_2[v + 1];
				v++;
			}
			to_replace[v] = '\0';
			if (strlen(to_replace) > 0) {
				replace(to_replace, "", polynomial_1);
				sprintf(polynomial_1, "%s", expressionF);
				replace(to_replace, "", polynomial_2);
				sprintf(polynomial_2, "%s", expressionF);
			}
		}
		sprintf(expressionF, "%s*(0x-1)", polynomial_2);
		simpleSimplifyPolynomial(expressionF);
		sprintf(polynomial_2, "%s", expressionF);
		sum_polynomial(polynomial_1, polynomial_2);
	}
	else {
		sprintf(expressionF, "(0x+0)");
	}
	replaceTimes = 0;
}

void multi_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]) {
	sprintf(expressionF, "%s", polynomial_1);
	if (isContained("((", polynomial_1)) {
		replace("((", "(", polynomial_1);
		sprintf(polynomial_1, "%s", expressionF);
	}
	if (isContained("))", polynomial_1)) {
		replace("))", ")", polynomial_1);
		sprintf(polynomial_1, "%s", expressionF);
	}
	sprintf(expressionF, "%s", polynomial_2);
	if (isContained("((", polynomial_2)) {
		replace("((", "(", polynomial_2);
		sprintf(polynomial_2, "%s", expressionF);
	}
	if (isContained("))", polynomial_2)) {
		replace("))", ")", polynomial_2);
		sprintf(polynomial_2, "%s", expressionF);
	}
	sprintf(expressionF, "%s", polynomial_1);
	char express[DIM] = "";
	sprintf(express, "(%s)", polynomial_1);
	if (isContained("/", express)) {
		replace("/", ")\\(", express);
		replace("\\", "/", expressionF);
		sprintf(polynomial_1, "%s", expressionF);
	}
	else {
		sprintf(roots, "");
		replaceTimes = 0;
		equationSolver(polynomial_1);
		if (abs(lastDividerR) != 0 || abs(lastDividerI) != 0) {
			LastDividerR = lastDividerR;
			LastDividerI = lastDividerI;
		}
		else {
			LastDividerR = 0;
			LastDividerI = 0;
		}
		equationSolver(polynomial_2);
		multiplication(LastDividerR, LastDividerI, lastDividerR, lastDividerI);
		LastDividerR = resultR;
		LastDividerI = resultI;
		lastDividerR = LastDividerR;
		lastDividerI = LastDividerI;
		if (isContained("\\", roots)) {
			rootsToPolynomial(roots);
		}
		else {
			if (strlen(roots) > 0) {
				math_processor(roots);
				multiplication(-1, 0, resultR, resultI);
				if (abs(LastDividerI) != 0 || abs(LastDividerR) != 0) {
					multiplication(LastDividerR, LastDividerI, resultR, resultI);
				}
				sprintf(expressionF, "(%G+%Gi)x+(%G+%Gi)", LastDividerR, LastDividerI, resultR,
					resultI);
				if (isContained("+-", expressionF)) {
					replaceTimes = 0;
					replace("+-", "+_", expressionF);
				}
				if (isContained("(-", expressionF)) {
					replaceTimes = 0;
					replace("(-", "(_", expressionF);
				}
			}
			else {
				sprintf(expressionF, "(%G+%Gi)x+(%G+%Gi)", 0.0, 0.0, resultR, resultI);
				if (isContained("+-", expressionF)) {
					replaceTimes = 0;
					replace("+-", "+_", expressionF);
				}
				if (isContained("(-", expressionF)) {
					replaceTimes = 0;
					replace("(-", "(_", expressionF);
				}
			}
		}
		lastDividerR = 0;
		LastDividerR = 0;
		lastDividerI = 0;
		LastDividerI = 0;
		if (isContained("\n", expressionF)) {
			replace("\n", "", expressionF);
		}
		char expression[DIM] = "";
		sprintf(expression, "(%s)", expressionF);
		sprintf(expressionF, "%s", expression);
		if (dataVerifier(expression, 0, 0, 0, 1)) {
			sprintf(expressionF, "%s", expression);
		}
		replaceTimes = 0;
	}
}

void div_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]) {
	if (!dataVerifier(polynomial_1, 0, 0, 0, 1)) {
		if (isContained("((", polynomial_1)) {
			replace("((", "(", polynomial_1);
			sprintf(polynomial_1, "%s", expressionF);
		}
		if (isContained("))", polynomial_1)) {
			replace("))", ")", polynomial_1);
			sprintf(polynomial_1, "%s", expressionF);
		}
	}
	if (!dataVerifier(polynomial_2, 0, 0, 0, 1)) {
		if (isContained("((", polynomial_2)) {
			replace("((", "(", polynomial_2);
			sprintf(polynomial_2, "%s", expressionF);
		}
		if (isContained("))", polynomial_2)) {
			replace("))", ")", polynomial_2);
			sprintf(polynomial_2, "%s", expressionF);
		}
	}
	replaceTimes = 0;
	char rootsPoly1[DIM] = "", rootsPoly2[DIM] = "";
	sprintf(roots, "");
	equationSolver(polynomial_1);
	LastDividerR = lastDividerR;
	LastDividerI = lastDividerI;
	sprintf(rootsPoly1, "%s", roots);
	sprintf(roots, "");
	equationSolver(polynomial_2);
	division(LastDividerR, LastDividerI, lastDividerR, lastDividerI);
	sprintf(expressionF, "(%G+%Gi)/(%G+%Gi)", LastDividerR, LastDividerI, lastDividerR, lastDividerI);
	if (isContained("(-", expressionF)) {
		replace("(-", "(_", expressionF);
	}
	if (isContained("-", expressionF)) {
		replace("-", "+_", expressionF);
	}
	lastDividerR = resultR;
	lastDividerI = resultI;
	sprintf(rootsPoly2, "%s", roots);
	char rootChar[DIM] = "";
	double rootR2[dim], rootI2[dim];
	double rootR1[dim], rootI1[dim];
	int i = 0, p = 0, r = 0;
	while (rootsPoly2[i] != '\0') {
		p = 0;
		while (rootsPoly2[i] != '\\' && rootsPoly2[i] != '\0') {
			rootChar[p] = rootsPoly2[i];
			p++;
			i++;
		}
		rootChar[p] = '\0';
		math_processor(rootChar);
		rootR2[r] = resultR;
		rootI2[r] = resultI;
		r++;
		i++;
	}
	i = 0, p = 0;
	int s = 0;
	while (rootsPoly1[i] != '\0') {
		p = 0;
		while (rootsPoly1[i] != '\\' && rootsPoly1[i] != '\0') {
			rootChar[p] = rootsPoly1[i];
			p++;
			i++;
		}
		rootChar[p] = '\0';
		math_processor(rootChar);
		rootR1[s] = resultR;
		rootI1[s] = resultI;
		s++;
		i++;
	}
	char roots_2[DIM] = "";
	int j = 0;
	int count = 0;
	for (i = 0; i < s; i++) {
		for (j = 0; j < r; j++) {
			if (rootR1[i] == rootR2[j] && rootI1[i] == rootI2[j]) {
				rootR1[i] = -7777;
				rootR2[j] = -7777;
				rootI1[i] = -7777;
				rootI2[j] = -7777;
				count++;
				isDivisible = true;
			}
		}
	}
	if (count == 0) {
		isDivisible = false;
	}
	if (isDivisible) {
		int k = 0;
		sprintf(roots, "");
		for (i = 0; i < s; i++) {
			if (rootR1[i] != -7777) {
				sprintf(roots, "%s%G+%Gi\\", roots, rootR1[i], rootI1[i]);
			}
		}
		if (strlen(roots) >= 1) {
			roots[strlen(roots) - 1] = '\0';
		}
		if (isContained("-", roots)) {
			replace("-", "_", roots);
			sprintf(roots, "%s", expressionF);
		}
		sprintf(roots_2, "");
		for (i = 0; i < s; i++) {
			if (rootR2[i] != -7777) {
				sprintf(roots_2, "%s%G+%Gi\\", roots_2, rootR2[i], rootI2[i]);
			}
		}
		if (strlen(roots_2) >= 1) {
			roots_2[strlen(roots_2) - 1] = '\0';
		}
		if (isContained("-", roots_2)) {
			replace("-", "_", roots_2);
			sprintf(roots_2, "%s", expressionF);
		}
		if (strlen(roots) > 0) {
			char expSimplified[DIM] = "";
			if (strlen(roots) > 0) {
				rootsToPolynomial(roots);
				if (isContained("\n", expressionF)) {
					replace("\n", "", expressionF);
				}
				char expression[DIM] = "";
				sprintf(expSimplified, "%s", expressionF);
			}
		}
		else {
			sprintf(expressionF, "(0x+%G+%Gi)", lastDividerR, lastDividerI);
			if (isContained("+-", expressionF)) {
				replaceTimes = 0;
				replace("+-", "+_", expressionF);
			}
			if (isContained("(-", expressionF)) {
				replaceTimes = 0;
				replace("(-", "(_", expressionF);
			}
		}
		replaceTimes = 0;
		sprintf(roots, "");
	}
	else {
		sprintf(expressionF, "(%s)/(%s)", polynomial_1, polynomial_2);
	}
}