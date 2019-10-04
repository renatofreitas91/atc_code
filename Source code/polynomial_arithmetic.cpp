
#include "stdafx.h"
#include "calc.h"

double LastDividerR = 0, LastDividerI = 0;
boolean isDivisible = true;


void sum_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]) {
	//printf("\nsum-> %s | %s", polynomial_1, polynomial_2);
	sprintf(roots, "");
	if (isContained("((", polynomial_1) && isContained("))", polynomial_1)) {
		replace("((", "(", polynomial_1);
		sprintf(polynomial_1, "%s", expressionF);
		replace("))", ")", polynomial_1);
		sprintf(polynomial_1, "%s", expressionF);
	}
	if (isContained("((", polynomial_2) && isContained("))", polynomial_2)) {
		replace("((", "(", polynomial_2);
		sprintf(polynomial_2, "%s", expressionF);
		replace("))", ")", polynomial_2);
		sprintf(polynomial_2, "%s", expressionF);
	}
	removeDuplPars(polynomial_1);
	sprintf(polynomial_1, "%s", expressionF);
	sprintf(expressionF, "(%s)*(0x^1+1)", polynomial_1);
	simpleSimplifyPolynomial(expressionF);
	sprintf(polynomial_1, "%s", expressionF);
	sprintf(roots, "");
	removeDuplPars(polynomial_2);
	sprintf(polynomial_2, "%s", expressionF);
	sprintf(expressionF, "(%s)*(0x^1+1)", polynomial_2);
	simpleSimplifyPolynomial(expressionF);
	sprintf(polynomial_2, "%s", expressionF);
	sprintf(roots, "");
	lastDividerR = 1;
	lastDividerI = 0;
	LastDividerR = 1;
	LastDividerI = 0;
	sprintf(roots, "");
	char polynomial_sum[DIM] = "";
	if (isContained("((", polynomial_1)) {
		replace("((", "(", polynomial_1);
		sprintf(polynomial_1, "%s", expressionF);
	}
	if (isContained("))", polynomial_1)) {
		replace("))", ")", polynomial_1);
		sprintf(polynomial_1, "%s", expressionF);
	}
	if (isContained("((", polynomial_2)) {
		replace("((", "(", polynomial_2);
		sprintf(polynomial_2, "%s", expressionF);
	}
	if (isContained("))", polynomial_2)) {
		replace("))", ")", polynomial_2);
		sprintf(polynomial_2, "%s", expressionF);
	}
	if (isContained("x^1)", polynomial_1) && strlen(polynomial_1) == strEnd) {
		polynomial_1[strlen(polynomial_1) - 1] = '\0';
	}
	if (isContained("x^1)", polynomial_2) && strlen(polynomial_2) == strEnd) {
		polynomial_2[strlen(polynomial_2) - 1] = '\0';
	}
	sprintf(roots, "");
	sprintf(polynomial_sum, "%s+%s", polynomial_1, polynomial_2);
	equationSolver(polynomial_sum);
	if (isContained("\\", roots) || strlen(roots) > 0) {
		rootsToPolynomial(roots);
	}
	else {
		sprintf(expressionF, "((%f+%fi)x^1+(%f+%fi))", 0.0, 0.0, lastDividerR, lastDividerI);
		if (isContained("+-", expressionF)) {
			replaceTimes = 0;
			replace("+-", "-", expressionF);
		}
		if (isContained("(-", expressionF)) {
			replaceTimes = 0;
			replace("(-", "(_", expressionF);
		}
	}
	replaceTimes = 0;
	sprintf(roots, "");
}

void sub_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]) {
	sprintf(roots, "");
	removeDuplPars(polynomial_1);
	sprintf(polynomial_1, "%s", expressionF);
	sprintf(expressionF, "(%s)*(0x^1+1)", polynomial_1);
	simpleSimplifyPolynomial(expressionF);
	sprintf(polynomial_1, "%s", expressionF);
	sprintf(roots, "");
	removeDuplPars(polynomial_2);
	sprintf(polynomial_2, "%s", expressionF);
	sprintf(expressionF, "(%s)*(0x^1+1)", polynomial_2);
	simpleSimplifyPolynomial(expressionF);
	sprintf(polynomial_2, "%s", expressionF);
	sprintf(roots, "");
	sprintf(expressionF, "(%s)*(0x^1-1)", polynomial_2);
	simpleSimplifyPolynomial(expressionF);
	sprintf(polynomial_2, "%s", expressionF);
	sprintf(roots, "");
	sum_polynomial(polynomial_1, polynomial_2);
	replaceTimes = 0;
}

void multi_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]) {
	//printf("\nmulti-> %s | %s", polynomial_1, polynomial_2);
	sprintf(roots, "");
	if (isEqual(polynomial_2, "(0+0i)") || isEqual(polynomial_1, "(0+0i)")) {
		sprintf(expressionF, "(0+0i)");
	}
	else {
		sprintf(roots, "");
		if (isContained("((", polynomial_1)) {
			replace("((", "(", polynomial_1);
			sprintf(polynomial_1, "%s", expressionF);
		}
		if (isContained("))", polynomial_1)) {
			replace("))", ")", polynomial_1);
			sprintf(polynomial_1, "%s", expressionF);
		}
		if (isContained("((", polynomial_2)) {
			replace("((", "(", polynomial_2);
			sprintf(polynomial_2, "%s", expressionF);
		}
		if (isContained("))", polynomial_2)) {
			replace("))", ")", polynomial_2);
			sprintf(polynomial_2, "%s", expressionF);
		}

		replaceTimes = 0;
		sprintf(roots, "");
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
				sprintf(expressionF, "(%f+%fi)x^1+(%f+%fi)", LastDividerR, LastDividerI, resultR,
					resultI);
				if (isContained("+-", expressionF)) {
					replaceTimes = 0;
					replace("+-", "-", expressionF);
				}
				if (isContained("(-", expressionF)) {
					replaceTimes = 0;
					replace("(-", "(_", expressionF);
				}
			}
			else {
				sprintf(expressionF, "(%f+%fi)x^1+(%f+%fi)", 0.0, 0.0, lastDividerR, lastDividerI);
				if (isContained("+-", expressionF)) {
					replaceTimes = 0;
					replace("+-", "+_", expressionF);
				}
				if (isContained("(-", expressionF)) {
					replaceTimes = 0;
					replace("(-", "(_", expressionF);
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
			char saveExpression[DIM] = "";
			sprintf(saveExpression, "%s", expressionF);
			sprintf(expression, "(%s)", expressionF);
			sprintf(expressionF, "%s", expression);
			if (dataVerifier(expression, 0, 0, 0, 1)) {
				sprintf(expressionF, "%s", expression);
			}
			else {
				sprintf(expressionF, "%s", saveExpression);
			}
		}
		replaceTimes = 0;
		sprintf(roots, "");
	}
}

void div_polynomial(char polynomial_1[DIM], char polynomial_2[DIM]) {
	//printf("\npolynomial_1-> %s", polynomial_1);
	//printf("\npolynomial_2-> %s", polynomial_2);
	isDivisible = true;
	if ((!isEqual(polynomial_2, "((0+0i)x^1+(0+0i))") && isEqual(polynomial_1, "((0+0i)x^1+(0+0i))")) || (!isEqual(polynomial_2, "((0+0i))") && isEqual(polynomial_1, "((0+0i))"))) {
		sprintf(expressionF, "(0+0i)");
	}
	else {
		sprintf(roots, "");
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
		sprintf(expressionF, "(%f+%fi)/(%f+%fi)", LastDividerR, LastDividerI, lastDividerR, lastDividerI);
		if (isContained("(-", expressionF)) {
			replace("(-", "(_", expressionF);
		}
		if (isContained("-", expressionF)) {
			replace("-", "-", expressionF);
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
			if (abs(resultR) < 1E-4) {
				resultR = 0;
			}
			if (abs(resultI) < 1E-4) {
				resultI = 0;
			}
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
			if (abs(resultR) < 1E-4) {
				resultR = 0;
			}
			if (abs(resultI) < 1E-4) {
				resultI = 0;
			}
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
			//puts("ENTROU");
			int k = 0;
			sprintf(roots, "");
			for (i = 0; i < s; i++) {
				if (rootR1[i] != -7777) {
					sprintf(roots, "%s%f+%fi\\", roots, rootR1[i], rootI1[i]);
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
			for (i = 0; i < r; i++) {
				if (rootR2[i] != -7777) {
					sprintf(roots_2, "%s%f+%fi\\", roots_2, rootR2[i], rootI2[i]);
				}
			}
			if (strlen(roots_2) >= 1) {
				roots_2[strlen(roots_2) - 1] = '\0';
			}
			if (isContained("-", roots_2)) {
				replace("-", "_", roots_2);
				sprintf(roots_2, "%s", expressionF);
			}
			/*puts(roots);
			puts("\n");
			puts(roots_2);
			puts("\n");*/
			char expSimplified[DIM] = "";
			char expSimplified_2[DIM] = "";
			if (strlen(roots) > 0 || strlen(roots_2) > 0) {
				if (strlen(roots) > 0) {
					rootsToPolynomial(roots);
					if (isContained("\n", expressionF)) {
						replace("\n", "", expressionF);
					}
					char expression[DIM] = "";
					sprintf(expSimplified, "%s", expressionF);
				}
				if (strlen(roots_2) > 0) {
					rootsToPolynomial(roots_2);
					if (isContained("\n", expressionF)) {
						replace("\n", "", expressionF);
					}
					char expression[DIM] = "";
					sprintf(expSimplified_2, "%s", expressionF);
					sprintf(expressionF, "(%s)/(%s)", expSimplified, expSimplified_2);
				}
			}
			else {
				sprintf(expressionF, "(0x^1+%f+%fi)", lastDividerR, lastDividerI);
				if (isContained("+-", expressionF)) {
					replaceTimes = 0;
					replace("+-", "-", expressionF);
				}
				if (isContained("(-", expressionF)) {
					replaceTimes = 0;
					replace("(-", "(_", expressionF);
				}
			}
			replaceTimes = 0;
			sprintf(roots, "");
			sprintf(roots_2, "");
		}
		else {
			sprintf(saveExpressionF, "(%s)/(%s)", polynomial_1, polynomial_2);
		}
		
		sprintf(roots, "");
		sprintf(roots_2, "");
	}
}

void removeDuplPars(char expression[DIM]) {
	replaceTimes = 0;
	if (isContained("((", expression)) {
		replace("((", "(", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("))", expression)) {
		replace("))", ")", expression);
		sprintf(expression, "%s", expressionF);
	}
	sprintf(expressionF, "%s", expression);
}

void removeTriplPars(char expression[DIM]) {
	replaceTimes = 0;
	if (isContained("(((", expression)) {
		replace("(((", "((", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained(")))", expression)) {
		replace(")))", "))", expression);
		sprintf(expression, "%s", expressionF);
	}
	sprintf(expressionF, "%s", expression);
}