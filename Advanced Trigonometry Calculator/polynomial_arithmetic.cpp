
#include "stdafx.h"
#include "calc.h"

PrecisionValue LastDividerR = 0, LastDividerI = 0;
bool isDivisible = true;

template <typename T>
void sum_polynomial<T>(char* polynomial_1, char* polynomial_2) {
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
	simpleSimplifyPolynomial<T>(expressionF);
	sprintf(polynomial_1, "%s", expressionF);
	sprintf(roots, "");
	removeDuplPars(polynomial_2);
	sprintf(polynomial_2, "%s", expressionF);
	sprintf(expressionF, "(%s)*(0x^1+1)", polynomial_2);
	simpleSimplifyPolynomial<T>(expressionF);
	sprintf(polynomial_2, "%s", expressionF);
	sprintf(roots, "");
	lastDividerR = 1;
	lastDividerI = 0;
	LastDividerR = 1;
	LastDividerI = 0;
	sprintf(roots, "");
	char* polynomial_sum = getDynamicCharArray("", "polynomial_sum");
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
	if (isContained("x^1)", polynomial_1) && abs((int)strlen(polynomial_1)) == strEnd) {
		polynomial_1[abs((int)strlen(polynomial_1)) - 1] = '\0';
	}
	if (isContained("x^1)", polynomial_2) && abs((int)strlen(polynomial_2)) == strEnd) {
		polynomial_2[abs((int)strlen(polynomial_2)) - 1] = '\0';
	}
	sprintf(roots, "");
	sprintf(polynomial_sum, "%s+%s", polynomial_1, polynomial_2);
	equationSolver<T>(polynomial_sum);
	if (isContained("\\", roots) || abs((int)strlen(roots)) > 0) {
		rootsToPolynomial(roots);
	}
	else {
		sprintf(expressionF, "((%f+%fi)x^1+(%f+%fi))", 0.0, 0.0, precisionDisplayDouble(lastDividerR), precisionDisplayDouble(lastDividerI));
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
	_delete(polynomial_sum, "polynomial_sum"); polynomial_sum = nullptr;
}
template <typename T>	
void sub_polynomial<T>(char* polynomial_1, char* polynomial_2) {
	sprintf(roots, "");
	removeDuplPars(polynomial_1);
	sprintf(polynomial_1, "%s", expressionF);
	sprintf(expressionF, "(%s)*(0x^1+1)", polynomial_1);
	simpleSimplifyPolynomial<T>(expressionF);
	sprintf(polynomial_1, "%s", expressionF);
	sprintf(roots, "");
	removeDuplPars(polynomial_2);
	sprintf(polynomial_2, "%s", expressionF);
	sprintf(expressionF, "(%s)*(0x^1+1)", polynomial_2);
	simpleSimplifyPolynomial<T>(expressionF);
	sprintf(polynomial_2, "%s", expressionF);
	sprintf(roots, "");
	sprintf(expressionF, "(%s)*(0x^1-1)", polynomial_2);
	simpleSimplifyPolynomial<T>(expressionF);
	sprintf(polynomial_2, "%s", expressionF);
	sprintf(roots, "");
	sum_polynomial<T>(polynomial_1, polynomial_2);
	replaceTimes = 0;
}
template <typename T>
void multi_polynomial<T>(char* polynomial_1, char* polynomial_2) {
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
		equationSolver<T>(polynomial_1);
		if (abs(precisionValueTo<T>(lastDividerR)) != 0 || abs(precisionValueTo<T>(lastDividerI)) != 0) {
			LastDividerR = lastDividerR;
			LastDividerI = lastDividerI;
		}
		else {
			LastDividerR = 0;
			LastDividerI = 0;
		}
		equationSolver<T>(polynomial_2);
		multiplication(LastDividerR, LastDividerI, lastDividerR, lastDividerI);
		LastDividerR = precisionValueTo<T>(resultR);
		LastDividerI = precisionValueTo<T>(resultI);
		lastDividerR = LastDividerR;
		lastDividerI = LastDividerI;
		if (isContained("\\", roots) || abs((int)strlen(roots)) > 0) {
			rootsToPolynomial(roots);
		}
		else {
			sprintf(expressionF, "(%f+%fi)x^1+(%f+%fi)", 0.0, 0.0, precisionDisplayDouble(lastDividerR), precisionDisplayDouble(lastDividerI));
			if (isContained("+-", expressionF)) {
				replaceTimes = 0;
				replace("+-", "+_", expressionF);
			}
			if (isContained("(-", expressionF)) {
				replaceTimes = 0;
				replace("(-", "(_", expressionF);
			}
			lastDividerR = 0;
			LastDividerR = 0;
			lastDividerI = 0;
			LastDividerI = 0;
			if (isContained("\n", expressionF)) {
				replace("\n", "", expressionF);
			}
			char* expression = getDynamicCharArray("", "expression");
			char* saveExpression = getDynamicCharArray("", "saveExpression");
			sprintf(saveExpression, "%s", expressionF);
			sprintf(expression, "(%s)", expressionF);
			sprintf(expressionF, "%s", expression);
			if (dataVerifier<double>(expression, 0.0, 0.0, 0, 1)) {
				sprintf(expressionF, "%s", expression);
			}
			else {
				sprintf(expressionF, "%s", saveExpression);
			}
			_delete(expression, "expression"); expression = nullptr;
			_delete(saveExpression, "saveExpression"); saveExpression = nullptr;

		}
		replaceTimes = 0;
		sprintf(roots, "");
	}
}
template <typename T>
void div_polynomial<T>(char* polynomial_1, char* polynomial_2) {
	isDivisible = true;
	if ((!isEqual(polynomial_2, "((0+0i)x^1+(0+0i))") && isEqual(polynomial_1, "((0+0i)x^1+(0+0i))")) || (!isEqual(polynomial_2, "((0+0i))") && isEqual(polynomial_1, "((0+0i))"))) {
		sprintf(expressionF, "(0+0i)");
	}
	else {
		sprintf(roots, "");
		if (!dataVerifier<double>(polynomial_1, 0.0, 0.0, 0, 1)) {
			if (isContained("((", polynomial_1)) {
				replace("((", "(", polynomial_1);
				sprintf(polynomial_1, "%s", expressionF);
			}
			if (isContained("))", polynomial_1)) {
				replace("))", ")", polynomial_1);
				sprintf(polynomial_1, "%s", expressionF);
			}
		}
		if (!dataVerifier<double>(polynomial_2, 0.0, 0.0, 0, 1)) {
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
		char* rootsPoly1 = getDynamicCharArray("", "rootsPoly1"); char* rootsPoly2 = getDynamicCharArray("", "rootsPoly2");
		sprintf(roots, "");
		equationSolver<T>(polynomial_1);
		LastDividerR = lastDividerR;
		LastDividerI = lastDividerI;
		sprintf(rootsPoly1, "%s", roots);
		sprintf(roots, "");
		equationSolver<T>(polynomial_2);
		sprintf(rootsPoly2, "%s", roots);
		division(LastDividerR, LastDividerI, lastDividerR, lastDividerI);
		replaceTimes = 0;
		if (isContained("(-", expressionF)) {
			replace("(-", "(_", expressionF);
		}
		if (isContained("-", expressionF)) {
			replace("-", "_", expressionF);
		}
		lastDividerR = precisionValueTo<T>(resultR);
		lastDividerI = precisionValueTo<T>(resultI);


		char* rootChar = getDynamicCharArray("", "rootChar");
		T* rootR2 = getDynamicArray<T>(DIMDOUBLE); T* rootI2 = getDynamicArray<T>(DIMDOUBLE);
		T* rootR1 = getDynamicArray<T>(DIMDOUBLE); T* rootI1 = getDynamicArray<T>(DIMDOUBLE);
		int i = 0, p = 0, r = 0;
		if (abs((int)strlen(rootsPoly2)) > 0 && abs((int)strlen(rootsPoly1)) > 0) {
			while (i < abs((int)strlen(rootsPoly2))) {
				p = 0;
				while (rootsPoly2[i] != '\\' && i < abs((int)strlen(rootsPoly2))) {
					rootChar[p] = rootsPoly2[i];
					p++;
					i++;
				}
				rootChar[p] = '\0';
				solveMath<T>(rootChar);
				if (abs(precisionValueTo<T>(resultR)) < 1E-4) {
					resultR = 0;
				}
				if (abs(precisionValueTo<T>(resultI)) < 1E-4) {
					resultI = 0;
				}
				rootR2[r] = precisionValueTo<T>(resultR);
				rootI2[r] = precisionValueTo<T>(resultI);
				r++;
				i++;
			}
		}
		if (abs((int)strlen(rootsPoly2)) == 0 && abs((int)strlen(rootsPoly1)) > 0) {
			rootsToPolynomial(rootsPoly1);
		}
		else {
			if (abs((int)strlen(rootsPoly1)) == 0 && abs((int)strlen(rootsPoly2)) > 0) {
				isDivisible = false;
				sprintf(saveExpressionF, "(%s)/(%s)", polynomial_1, polynomial_2);
			}
			else {
				if (abs((int)strlen(rootsPoly1)) == 0 && abs((int)strlen(rootsPoly2)) == 0) {
					if (isEqual(polynomial_1, polynomial_2)) {
						sprintf(expressionF, "(0+0i)x^1+(1+0i)");
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
						sprintf(expressionF, "(0+0i)x^1+(%f+%fi)", precisionDisplayDouble(lastDividerR), precisionDisplayDouble(lastDividerI));
						if (isContained("+-", expressionF)) {
							replaceTimes = 0;
							replace("+-", "-", expressionF);
						}
						if (isContained("(-", expressionF)) {
							replaceTimes = 0;
							replace("(-", "(_", expressionF);
						}
					}
				}
				else {
					i = 0, p = 0;
					int s = 0;
					if (abs((int)strlen(rootsPoly1)) > 0) {
						while (i < abs((int)strlen(rootsPoly1))) {
							p = 0;
							while (rootsPoly1[i] != '\\' && i < abs((int)strlen(rootsPoly1))) {
								rootChar[p] = rootsPoly1[i];
								p++;
								i++;
							}
							rootChar[p] = '\0';
							solveMath<T>(rootChar);
							if (abs(precisionValueTo<T>(resultR)) < 1E-4) {
								resultR = 0;
							}
							if (abs(precisionValueTo<T>(resultI)) < 1E-4) {
								resultI = 0;
							}
							rootR1[s] = precisionValueTo<T>(resultR);
							rootI1[s] = precisionValueTo<T>(resultI);
							s++;
							i++;
						}
					}
					char* roots_2 = getDynamicCharArray("", "roots_2");
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
								sprintf(roots, "%s%f+%fi\\", roots, precisionDisplayDouble(rootR1[i]), precisionDisplayDouble(rootI1[i]));
							}
						}
						if (abs((int)strlen(roots)) >= 1) {
							roots[abs((int)strlen(roots)) - 1] = '\0';
						}
						if (isContained("-", roots)) {
							replace("-", "_", roots);
							sprintf(roots, "%s", expressionF);
						}
						sprintf(roots_2, "");
						for (i = 0; i < r; i++) {
							if (rootR2[i] != -7777) {
								sprintf(roots_2, "%s%f+%fi\\", roots_2, precisionDisplayDouble(rootR2[i]), precisionDisplayDouble(rootI2[i]));
							}
						}
						if (abs((int)strlen(roots_2)) >= 1) {
							roots_2[abs((int)strlen(roots_2)) - 1] = '\0';
						}
						if (isContained("-", roots_2)) {
							replace("-", "_", roots_2);
							sprintf(roots_2, "%s", expressionF);
						}
						char* expSimplified = getDynamicCharArray("", "expSimplified");
						char* expSimplified_2 = getDynamicCharArray("", "expSimplified_2");
						if (abs((int)strlen(roots)) > 0 || abs((int)strlen(roots_2)) > 0) {
							if (abs((int)strlen(roots)) > 0) {
								rootsToPolynomial(roots);
								if (isContained("\n", expressionF)) {
									replace("\n", "", expressionF);
								}
								sprintf(expSimplified, "%s", expressionF);
							}
							else {
								sprintf(expressionF, "(0x^1+%f+%fi)", precisionDisplayDouble(lastDividerR), precisionDisplayDouble(lastDividerI));
								if (isContained("+-", expressionF)) {
									replaceTimes = 0;
									replace("+-", "-", expressionF);
								}
								if (isContained("(-", expressionF)) {
									replaceTimes = 0;
									replace("(-", "(_", expressionF);
								}
								sprintf(expSimplified, "%s", expressionF);
							}
							if (abs((int)strlen(roots_2)) > 0) {
								rootsToPolynomial(roots_2);
								if (isContained("\n", expressionF)) {
									replace("\n", "", expressionF);
								}
								sprintf(expSimplified_2, "%s", expressionF);
								sprintf(expressionF, "(%s)/(%s)", expSimplified, expSimplified_2);
							}
						}
						else {
							sprintf(expressionF, "(0x^1+%f+%fi)", precisionDisplayDouble(lastDividerR), precisionDisplayDouble(lastDividerI));
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
						_delete(expSimplified, "expSimplified"); expSimplified = nullptr;
						_delete(expSimplified_2, "expSimplified_2"); expSimplified_2 = nullptr;

					}
					else {
						sprintf(saveExpressionF, "(%s)/(%s)", polynomial_1, polynomial_2);
					}
					sprintf(roots, "");
					sprintf(roots_2, "");
					_delete(roots_2, "roots_2"); roots_2 = nullptr;
				}
			}
		}
		_delete(rootsPoly1, "rootsPoly1"); rootsPoly1 = nullptr;
		_delete(rootsPoly2, "rootsPoly2"); rootsPoly2 = nullptr;
		_delete(rootChar, "rootChar"); rootChar = nullptr;
		_delete(rootR2, "rootR2"); rootR2 = nullptr;
		_delete(rootR1, "rootR1"); rootR1 = nullptr;
		_delete(rootI2, "rootI2"); rootI2 = nullptr;
		_delete(rootI1, "rootI1"); rootI1 = nullptr;

	}
}
void removeDuplPars(char* expression) {
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
template <typename T>
void removeTriplPars(char* expression) {
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
template void sum_polynomial<double>(char*, char*);
template void sub_polynomial<double>(char*, char*);
template void multi_polynomial<double>(char*, char*);
template void div_polynomial<double>(char*, char*);

void removeTriplPars(char* expression) { removeTriplPars<double>(expression); }
template void removeTriplPars<double>(char*);
