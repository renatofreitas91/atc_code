

#include "stdafx.h"

bool notSolved = true, fromEquationSolver = false, equationSolverRunning = false, polySimplifier = false, solveMultiPoly = false, simplifying = true, progress = false, product = false;
char* charMaster = getDynamicCharArrayShort("", "charMaster"), * roots = getDynamicCharArrayShort("", "roots"), * answers = getDynamicCharArrayShort("", "answers"), * polyNo = getDynamicCharArrayShort("", "polyNo"), * stringHelper = getDynamicCharArrayShort("", "stringHelper");
int* parentPol = getDynamicIntArray();
int nrRoots = 0, rootIndex = 1, maxExponent = 0, _rf = 0;

template<typename T>
void solveQuadraticEquation(char* arithTrig, T result1, T result2, int index) {
	char* values = getDynamicCharArrayShort("", "values"); char* value = getDynamicCharArrayShort("", "value"); char* saveValue = getDynamicCharArrayShort("", "saveValue");
	int v = 0, ct = 0;
	T aR = 0, aI = 0, bR = 0, bI = 0, cR = 0, cI = 0;
	int i = 23;
	while (i < abs((int)strlen(arithTrig)) && arithTrig[i] != ')') {
		if (arithTrig[i] == '\\') {
			ct++;
		}
		values[v] = arithTrig[i];
		v++;
		i++;
	}
	values[v] = '\0';
	if (ct != 2) {
		puts("\nError: You must include a, b and c values.\n");
	}
	else {
		v = 0;
		i = 0;
		while (values[i] != '\\') {
			value[v] = values[i];
			i++;
			v++;
		}
		value[v] = '\0';
		solveMath<T>(value);
		if (verified == 1) {
			aR = precisionValueTo<T>(resultR);
			aI = precisionValueTo<T>(resultI);
			i++;
			v = 0;
			while (values[i] != '\\') {
				value[v] = values[i];
				i++;
				v++;
			}
			value[v] = '\0';
			solveMath<T>(value);
			if (verified == 1) {
				bR = precisionValueTo<T>(resultR);
				bI = precisionValueTo<T>(resultI);
				i++;
				v = 0;
				while (i < abs((int)strlen(values))) {
					value[v] = values[i];
					i++;
					v++;
				}
				value[v] = '\0';
				solveMath<T>(value);
				if (verified == 1) {
					cR = precisionValueTo<T>(resultR);
					cI = precisionValueTo<T>(resultI);
					multiplication<T>(T(-1), T(0), bR, bI);
					T minusbR = precisionValueTo<T>(resultR), minusbI = precisionValueTo<T>(resultI);
					multiplication<T>(bR, bI, bR, bI);
					T bRquad = precisionValueTo<T>(resultR), bIquad = precisionValueTo<T>(resultI);
					multiplication<T>(aR, aI, cR, cI);
					T acR = precisionValueTo<T>(resultR), acI = precisionValueTo<T>(resultI);
					multiplication<T>(2, 0, aR, aI);
					T twoaR = precisionValueTo<T>(resultR), twoaI = precisionValueTo<T>(resultI);
					multiplication<T>(4, 0, acR, acI);
					T fouracR = precisionValueTo<T>(resultR), fouracI = precisionValueTo<T>(resultI);
					subtraction<T>(bRquad, bIquad, fouracR, fouracI);
					T radicandR = precisionValueTo<T>(resultR), radicandI = precisionValueTo<T>(resultI);
					exponentiation<T>(radicandR, radicandI, 0.5, 0, 1);
					T sqrtR = precisionValueTo<T>(resultR), sqrtI = precisionValueTo<T>(resultI);
					subtraction<T>(minusbR, minusbI, sqrtR, sqrtI);
					T minusR = precisionValueTo<T>(resultR), minusI = precisionValueTo<T>(resultI);
					sum<T>(minusbR, minusbI, sqrtR, sqrtI);
					T plusR = precisionValueTo<T>(resultR), plusI = precisionValueTo<T>(resultI);
					division<T>(plusR, plusI, twoaR, twoaI);
					T x1R = precisionValueTo<T>(resultR), x1I = precisionValueTo<T>(resultI);
					division<T>(minusR, minusI, twoaR, twoaI);
					T x2R = precisionValueTo<T>(resultR), x2I = precisionValueTo<T>(resultI);
					convertComplex2Exponential(x1R, x1I);
					if (x1R > 0 && x1I > 0) {
						printf("x%d=%s+%si\n", index, respR, respI);
					}
					else {
						if (x1R > 0 && x1I < 0) {
							printf("x%d=%s%si\n", index, respR, respI);
						}
						else {
							if (x1R < 0 && x1I > 0) {
								printf("x%d=%s+%si\n", index, respR, respI);
							}
							else {
								if (x1R < 0 && x1I < 0) {
									printf("x%d=%s%si\n", index, respR, respI);
								}
								else {
									if (x1R == 0 && x1I == 0) {
										printf("x%d=%s\n", index, respR);
									}
									else {
										if (x1R == 0 && x1I != 0) {
											printf("x%d=%si\n", index, respI);
										}
										else {
											if (x1R != 0 && x1I == 0) {
												printf("x%d=%s\n", index, respR);
											}
											else {
												printf("x%d=%s+%si\n", index, respR, respI);
											}
										}
									}
								}
							}
						}
					}
					index++;
					convertComplex2Exponential(x2R, x2I);
					if (x2R > 0 && x2I > 0) {
						printf("x%d=%s+%si\n", index, respR, respI);
					}
					else {
						if (x2R > 0 && x2I < 0) {
							printf("x%d=%s%si\n", index, respR, respI);
						}
						else {
							if (x2R < 0 && x2I > 0) {
								printf("x%d=%s+%si\n", index, respR, respI);
							}
							else {
								if (x2R < 0 && x2I < 0) {
									printf("x%d=%s%si\n", index, respR, respI);
								}
								else {
									if (x2R == 0 && x2I == 0) {
										printf("x%d=%s\n", index, respR);
									}
									else {
										if (x2R == 0 && x2I != 0) {
											printf("x%d=%si\n", index, respI);
										}
										else {
											if (x2R != 0 && x2I == 0) {
												printf("x%d=%s\n", index, respR);
											}
											else {
												printf("x%d=%s+%si\n", index, respR, respI);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	_deleteShort(values, "values");
	values = nullptr;
	if (value != nullptr) {
		_deleteShort(value, "value");
		value = nullptr;
	}
	_deleteShort(saveValue, "saveValue");
	saveValue = nullptr;
}
template <typename T>

void rootsToPolynomial(char* rootsF) {
	for (int i = 0; i < DIMTWOD; ++i) {
		for (int j = 0; j < DIMDOUBLE; j++) {
			saveResultR[i][j] = 0;
			saveResultI[i][j] = 0;
		}
	}
	isDivisible = true;
	char* report = getDynamicCharArray("", "report");
	sprintf(report, "");
	char* Report = getDynamicCharArray("", "Report");
	char* toValue = getDynamicCharArray("", "toValue");
	char* value = getDynamicCharArray("", "value");
	char* toSimplify = getDynamicCharArray("", "toSimplify");
	char* finalPolynomial = getDynamicCharArray("", "finalPolynomial");
	T* valuesRootsR = getDynamicArray<T>(DIMDOUBLE); T* valuesRootsI = getDynamicArray<T>(DIMDOUBLE); T* polynomialR = getDynamicArray<T>(DIMDOUBLE); T* polynomialI = getDynamicArray<T>(DIMDOUBLE); T* newPolynomialR = getDynamicArray<T>(DIMDOUBLE); T* newPolynomialI = getDynamicArray<T>(DIMDOUBLE);
	T* rearrangeValuesR = getDynamicArray<T>(DIMDOUBLE); T* rearrangeValuesI = getDynamicArray<T>(DIMDOUBLE);
	T* polynomialRF = getDynamicArray<T>(DIMDOUBLE); T* polynomialIF = getDynamicArray<T>(DIMDOUBLE);

	int i = 0, numberRoots = 0, rootIndex = 1, saveNumberRoots = 0;
	int lenRootsF = abs((int)strlen(rootsF));

	for (i = 0; i < lenRootsF; i++) {
		if (rootsF[i] == '\\') {
			numberRoots++;
		}
	}
	numberRoots++;

	if (numberRoots == 1) {
		replaceTimes = 0;
		calcNow<double>(rootsF, 0.0, 0.0);
		multiplication<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), precisionValueTo<T>(lastDividerR), precisionValueTo<T>(lastDividerI));

		sprintf(Report, "");
		sprintf(Report, convertToString("%s(%G+%Gi)x^1-(%G+%Gi)"), report, precisionValueTo<T>(lastDividerR), precisionValueTo<T>(lastDividerI), precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
		if (isContained("E", Report)) {
			sprintf(Report, convertToString("%s(%f+%fi)x^1-(%f+%fi)"), report, precisionValueTo<T>(lastDividerR), precisionValueTo<T>(lastDividerI), precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
		}
		sprintf(report, "%s", Report);
		if (isContained("(-", report)) {
			replace("(-", "(_", report);
			sprintf(report, "%s", expressionF);
		}
		if (isContained("+-", report)) {
			replace("+-", "-", report);
			sprintf(report, "%s", expressionF);
		}
		if (isContained("-(-", report)) {
			replace("-(-", "-(_", report);
			sprintf(report, "%s", expressionF);
		}
		if (isContained(".000000", report)) {
			replace(".000000", "", report);
			sprintf(report, "%s", expressionF);
		}
		if (isContained(")))", report)) {
			replace(")))", "))", report);
			sprintf(report, "%s", expressionF);
		}
		if (isContained("(((", report)) {
			replace("(((", "((", report);
			sprintf(report, "%s", expressionF);
		}
		sprintf(expressionF, "(%s)", report);
	}
	else {
		// Inicialização limpa de arrays até ao tamanho seguro de coeficientes (numberRoots + 1)
		for (i = 0; i < numberRoots + 2; i++) {
			valuesRootsR[i] = 0; valuesRootsI[i] = 0;
			polynomialR[i] = 0;  polynomialI[i] = 0;
			polynomialRF[i] = 0; polynomialIF[i] = 0;
		}

		int members = 0;
		i = 0;

		while (members < numberRoots && i <= lenRootsF) {
			int b = 0;
			while (i < lenRootsF && rootsF[i] != '\\') {
				toValue[b] = rootsF[i];
				b++;
				i++;
			}
			toValue[b] = '\0';
			if (b == 0 && i >= lenRootsF) {
				break;
			}
			calcNow<double>(toValue, 0.0, 0.0);
			valuesRootsR[members] = precisionValueTo<T>(resultR);
			valuesRootsI[members] = precisionValueTo<T>(resultI);
			members++;
			sprintf(toValue, "");
			if (i < lenRootsF && rootsF[i] == '\\') {
				i++;
			}
			else if (i >= lenRootsF) {
				break;
			}
		}
		numberRoots = members;

		// Filtragem e Rearranjo direto (Otimizado sem conversões string redundantes)
		int g = 0;
		// 1. Raízes Zero
		for (i = 0; i < members; i++) {
			if (valuesRootsR[i] == 0 && valuesRootsI[i] == 0) {
				rearrangeValuesR[g] = 0; rearrangeValuesI[g] = 0;
				g++;
			}
		}
		// 2. Raízes Reais Puras (com verificação de aproximação analítica se necessário via re_complex)
		for (i = 0; i < members; i++) {
			if (valuesRootsR[i] != 0 && valuesRootsI[i] == 0) {
				re_complex<T>(valuesRootsR[i], valuesRootsI[i], 1.0, 0.0);
				if (abs((int)precisionValueTo<T>(resultR)) == 0 && abs((int)precisionValueTo<T>(resultI)) == 0) {
					rearrangeValuesR[g] = valuesRootsR[i]; rearrangeValuesI[g] = valuesRootsI[i];
					valuesRootsR[i] = 0; valuesRootsI[i] = 0;
					g++;
				}
			}
		}
		// 3. Raízes Imaginárias Puras
		for (i = 0; i < members; i++) {
			if (valuesRootsR[i] == 0 && valuesRootsI[i] != 0) {
				re_complex<T>(valuesRootsR[i], valuesRootsI[i], 0.0, 1.0);
				if (abs((int)precisionValueTo<T>(resultR)) == 0 && abs((int)precisionValueTo<T>(resultI)) == 0) {
					rearrangeValuesR[g] = valuesRootsR[i]; rearrangeValuesI[g] = valuesRootsI[i];
					valuesRootsR[i] = 0; valuesRootsI[i] = 0;
					g++;
				}
			}
		}
		// 4. Restantes Raízes Complexas
		for (i = 0; i < members; i++) {
			if (valuesRootsR[i] != 0 || valuesRootsI[i] != 0) {
				rearrangeValuesR[g] = valuesRootsR[i];
				rearrangeValuesI[g] = valuesRootsI[i];
				g++;
			}
		}
		// Copiar de volta para o array principal
		for (i = 0; i < members; i++) {
			valuesRootsR[i] = rearrangeValuesR[i];
			valuesRootsI[i] = rearrangeValuesI[i];
		}

		// --- ALGORITMO CORRIGIDO DE MULTIPLICAÇÃO POLINOMIAL ---
		// Representa (x - r_0) inicialmente
		polynomialR[0] = 1.0; polynomialI[0] = 0.0;
		polynomialR[1] = valuesRootsR[0] * -1.0;
		polynomialI[1] = valuesRootsI[0] * -1.0;

		// Itera sobre as restantes raízes para expandir o polinómio
		for (int m = 1; m < numberRoots; m++) {
			// Executa a expansão de trás para a frente no próprio array para evitar overflows de índices
			for (int k = m + 1; k > 0; k--) {
				T prodR, prodI;
				// Multiplica o coeficiente anterior polynomial[k-1] pela raiz atual (com sinal invertido: -r_m)
				multiplication<T>(polynomialR[k - 1], polynomialI[k - 1], valuesRootsR[m] * -1.0, valuesRootsI[m] * -1.0);
				prodR = precisionValueTo<T>(resultR); prodI = precisionValueTo<T>(resultI);

				// polynomial[k] = polynomial[k] + (polynomial[k-1] * -r_m)
				polynomialR[k] += prodR;
				polynomialI[k] += prodI;
			}
		}

		// Copiar o resultado final consolidado para polynomialRF/IF para compatibilidade com o teu construtor de strings
		for (i = 0; i <= numberRoots; i++) {
			polynomialRF[i] = polynomialR[i];
			polynomialIF[i] = polynomialI[i];
		}

		// --- GERAÇÃO DO REPORT (STRING FINAL) ---
		int exp = numberRoots;
		for (int pol = 0; pol <= numberRoots; pol++) {
			multiplication<T>(polynomialRF[pol], polynomialIF[pol], precisionValueTo<T>(lastDividerR), precisionValueTo<T>(lastDividerI));
			sprintf(toSimplify, "");
			convertComplex2Exponential(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
			sprintf(toSimplify, convertToString("%s+%si"), respR, respI);
			if (isContained("E", toSimplify)) {
				sprintf(toSimplify, convertToString("%f+%fi"), precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
			}
			if (isContained("-", toSimplify)) {
				replace("-", "_", toSimplify);
				sprintf(toSimplify, "%s", expressionF);
			}
			calcNow<double>(toSimplify, 0.0, 0.0);
			convertComplex2Exponential(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));

			if (exp > 1) {
				sprintf(Report, convertToString("%s(%s+%si)x^%d+"), report, respR, respI, exp);
				if (isContained("E", Report)) {
					sprintf(Report, convertToString("%s(%f+%fi)x^%d+"), report, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), exp);
				}
			}
			else if (exp == 1) {
				sprintf(Report, convertToString("%s(%s+%si)x^1+"), report, respR, respI);
				if (isContained("E", Report)) {
					sprintf(Report, convertToString("%s(%f+%fi)x^1+"), report, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
				}
			}
			else if (exp == 0) {
				sprintf(Report, convertToString("%s(%s+%si)"), report, respR, respI);
				if (isContained("E", Report)) {
					sprintf(Report, convertToString("%s(%f+%fi)"), report, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
				}
			}

			sprintf(report, "%s", Report);
			exp--;

			if (isContained("(-", report)) {
				replace("(-", "(_", report);
				sprintf(report, "%s", expressionF);
			}
			replaceTimes = 0;
			if (isContained(".000000", report)) {
				replace(".000000", "", report);
				sprintf(report, "%s", expressionF);
			}
			if (isContained("+-", report)) {
				replace("+-", "-", report);
				sprintf(report, "%s", expressionF);
			}
		}

		// Remoção segura do '+' terminal, validando o tamanho da string
		int finalLen = abs((int)strlen(report));
		if (finalLen > 0 && report[finalLen - 1] == '+') {
			report[finalLen - 1] = '\0';
		}

		sprintf(expressionF, "%s", report);
		if (polySimplifier == true) {
			sprintf(finalPolynomial, "");
			int h = 0, g_idx = 0;
			while (g_idx < abs((int)strlen(report))) {
				finalPolynomial[h] = report[g_idx];
				g_idx++;
				h++;
			}
			finalPolynomial[h] = '\0';
			sprintf(expressionF, "(%s)", finalPolynomial);
		}
	}

	// Liberação de Memória Dinâmica Alocada de forma segura
	if (value != nullptr) { _delete(value, "value"); value = nullptr; }
	_delete(toValue, "toValue"); toValue = nullptr;
	_delete(toSimplify, "toSimplify"); toSimplify = nullptr;
	_delete(Report, "Report"); Report = nullptr;
	_delete(report, "report"); report = nullptr;
	_delete(valuesRootsR, "valuesRootsR"); valuesRootsR = nullptr;
	_delete(valuesRootsI, "valuesRootsI"); valuesRootsI = nullptr;
	if (polynomialR != nullptr) { _delete(polynomialR, "polynomialR"); polynomialR = nullptr; }
	if (polynomialI != nullptr) { _delete(polynomialI, "polynomialI"); polynomialI = nullptr; }
	_delete(newPolynomialR, "newPolynomialR"); newPolynomialR = nullptr;
	_delete(newPolynomialI, "newPolynomialI"); newPolynomialI = nullptr;
	_delete(finalPolynomial, "finalPolynomial"); finalPolynomial = nullptr;
	_delete(rearrangeValuesR, "rearrangeValuesR"); rearrangeValuesR = nullptr;
	_delete(rearrangeValuesI, "rearrangeValuesI"); rearrangeValuesI = nullptr;
	_delete(polynomialRF, "polynomialRF"); polynomialRF = nullptr;
	_delete(polynomialIF, "polynomialIF"); polynomialIF = nullptr;
}

template<typename T>
T equationSolver(char* equation) {
	try {
		putsAndPause("1");
		bool hasFloatNum = false;
		char* originalEquation = getDynamicCharArrayShort(equation, "originalEquation");
		int SaveMaxExponent = 0;
		maxExponent = 0;
		char* toCalcX = getDynamicCharArrayShort("", "toCalcX");
		sprintf(toCalcX, "");
		char* toReplace = getDynamicCharArrayShort("", "toReplace");
		int i = 0;
		rootIndex = 1;
		sprintf(answers, "");
		char* expression = getDynamicCharArrayShort("", "expression");
		if (isContained("x)", equation) && abs((int)strlen(equation)) == strEnd) {
			equation[abs((int)strlen(equation)) - 1] = '\0';
		}
		T rootR = 0, rootI = 0;
		int saveMaxExponent = 0;
		char* divider = getDynamicCharArrayShort(" ", "divider");
		char* saveToZeroDiv = getDynamicCharArrayShort("", "saveToZeroDiv");
		char* saveEquation = getDynamicCharArrayShort("", "saveEquation");
		char* exponent = getDynamicCharArrayShort("", "exponent");
		char* newExpre = getDynamicCharArrayShort("", "newExpre");
		char* toNoDivider = getDynamicCharArrayShort("", "toNoDivider");
		char* helpExtract = getDynamicCharArrayShort("", "helpExtract");
		char* saveHelper = getDynamicCharArrayShort("", "saveHelper");
		char* toCalcLastEle = getDynamicCharArrayShort("", "toCalcLastEle");
		lastElement = 0;
		lastElementI = 0;
		T* SolutionR = getDynamicArray<T>(DIMDOUBLE); T* SolutionI = getDynamicArray<T>(DIMDOUBLE);
		T* expressionCoefR = getDynamicArray<T>(DIMDOUBLE);
		T* expressionCoefI = getDynamicArray<T>(DIMDOUBLE);
		T* saveExpressionCoefR = getDynamicArray<T>(DIMDOUBLE); T* saveExpressionCoefI = getDynamicArray<T>(DIMDOUBLE);
		T* valuesEqR = getDynamicArray<T>(DIMDOUBLE); T* valuesEqI = getDynamicArray<T>(DIMDOUBLE);
		T* RootR = getDynamicArray<T>(DIMDOUBLE); T* RootI = getDynamicArray<T>(DIMDOUBLE);
		T* resultSubR = getDynamicArray<T>(DIMDOUBLE);
		T* resultSubI = getDynamicArray<T>(DIMDOUBLE);
		T* expDerivateR = getDynamicArray<T>(DIMDOUBLE); T* expDerivateI = getDynamicArray<T>(DIMDOUBLE); T* saveExpDerivateR = getDynamicArray<T>(DIMDOUBLE); T* saveExpDerivateI = getDynamicArray<T>(DIMDOUBLE);
		T* saveExpressionCoefRN = getDynamicArray<T>(DIMDOUBLE); T* saveExpressionCoefIN = getDynamicArray<T>(DIMDOUBLE);
		bool isFirstDegree = false;
		char* ValueR = getDynamicCharArrayShort("", "ValueR");
		char* ValueI = getDynamicCharArrayShort("", "ValueI");
		char* newEquation = getDynamicCharArrayShort("", "newEquation");
		char* maxExpX = getDynamicCharArrayShort("", "maxExpX");
		char* value = getDynamicCharArrayShort("", "value"); char* valueF = getDynamicCharArrayShort("", "valueF");
		char* maxExp = getDynamicCharArrayShort("", "maxExp");
		char* saveToCalcX = getDynamicCharArrayShort("", "saveToCalcX");
		putsAndPause("2");

		if (!isDivisible) {
			isDivisible = false;
			equationSolverRunning = true;
			sprintf(expressionF, "%s", saveExpressionF);
		}
		else {
			if (isContained("\\", originalEquation)) {
				sprintf(saveEquation, "%s", originalEquation);
				maxExponent = 0;
				sprintf(expression, "%s", originalEquation);
				equationSolverRunning = true;
				solving = false;
				for (i = 0; i < abs((int)strlen(originalEquation)); i++) {
					if (originalEquation[i] == '\\') {
						maxExponent++;
					}
				}
				int members = maxExponent;
				i = 0;

				sprintf(expressionF, "");
				while (members >= 0) {
					int b = 0;
					while (originalEquation[i] != '\\' && i < abs((int)strlen(originalEquation))) {
						expressionF[b] = originalEquation[i];
						b++;
						i++;
					}
					expressionF[b] = '\0';
					solveMath<T>(expressionF);
					if (resultR == -7777777) {
						sprintf(expressionF, "");
						puts("\nError: Empty input.");
						_delete(SolutionR, "SolutionR");
						SolutionR = nullptr;
						_delete(SolutionI, "SolutionI");
						SolutionI = nullptr;

						_delete(saveExpressionCoefR, "saveExpressionCoefR");
						saveExpressionCoefR = nullptr;
						_delete(saveExpressionCoefI, "saveExpressionCoefI");
						saveExpressionCoefI = nullptr;
						_deleteShort(toCalcX, "toCalcX");
						_deleteShort(toReplace, "toReplace"); toReplace = nullptr;
						toCalcX = nullptr;
						_deleteShort(originalEquation, "originalEquation");
						originalEquation = nullptr;
						_deleteShort(expression, "expression"); expression = nullptr;
						_deleteShort(saveToZeroDiv, "saveToZeroDiv"); saveToZeroDiv = nullptr;
						if (divider != nullptr) {
							_deleteShort(divider, "divider");
							divider = nullptr;
						}
						_deleteShort(exponent, "exponent");
						exponent = nullptr;
						_deleteShort(newEquation, "newEquation");
						_deleteShort(maxExpX, "maxExpX");
						_deleteShort(valueF, "valueF"); valueF = nullptr;
						_deleteShort(saveToCalcX, "saveToCalcX");
						_deleteShort(ValueR, "ValueR");
						ValueR = nullptr;
						_deleteShort(ValueI, "ValueI");
						ValueI = nullptr;
						_deleteShort(toCalcLastEle, "toCalcLastEle");
						_delete(saveHelper, "saveHelper");
						_deleteShort(toNoDivider, "toNoDivider");
						_deleteShort(saveEquation, "saveEquation");
						_deleteShort(newExpre, "newExpre");
						_deleteShort(helpExtract, "helpExtract");
						_delete(expressionCoefR, "expressionCoefR");
						_delete(expressionCoefI, "expressionCoefI");
						return 0;
					}
					valuesEqR[members] = precisionValueTo<T>(resultR);
					valuesEqI[members] = precisionValueTo<T>(resultI);
					members--;
					i++;
					sprintf(expressionF, "");
				}

				i = maxExponent;
				T maxValueR = valuesEqR[maxExponent], maxValueI = valuesEqI[maxExponent];
				for (i = maxExponent; i >= 0; i--) {
					division<T>(valuesEqR[i], valuesEqI[i], maxValueR, maxValueI);
					valuesEqR[i] = precisionValueTo<T>(resultR);
					valuesEqI[i] = precisionValueTo<T>(resultI);
				}
				saveMaxExponent = maxExponent;

				putsAndPause("3");

				for (i = maxExponent; i > 0; i--) {
					sprintf(ValueR, "%f", valuesEqR[i]);

					for (int v = 0; v < abs((int)(abs((int)strlen(ValueR)))); v++) {
						if (ValueR[v] == '-')
							ValueR[v] = '_';
					}
					sprintf(ValueI, "%f", valuesEqI[i]);
					for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
						if (ValueI[v] == '-')
							ValueI[v] = '_';
					}
					sprintf(expressionF, "%s(%s+%si)1*(res)^%d+", toCalcX, ValueR, ValueI, i);
					sprintf(toCalcX, "%s", expressionF);

				}

				lastDividerR = valuesEqR[0];
				lastDividerI = valuesEqI[0];
				sprintf(ValueR, "%f", valuesEqR[i]);
				for (int v = 0; v < abs((int)strlen(ValueR)); v++) {
					if (ValueR[v] == '-')
						ValueR[v] = '_';
				}
				sprintf(ValueI, "%f", valuesEqI[i]);
				for (int v = 0; v < abs((int)strlen(ValueI)); v++) {
					if (ValueI[v] == '-')
						ValueI[v] = '_';
				}
				sprintf(expressionF, "%s(%s+%si)", toCalcX, ValueR, ValueI);
				_deleteShort(ValueR, "ValueR");
				ValueR = nullptr;
				_deleteShort(ValueI, "ValueI");
				ValueI = nullptr;
				sprintf(toCalcX, "%s", expressionF);
				if (isContained(".000000", toCalcX)) {
					replace(".000000", "", toCalcX);
					sprintf(toCalcX, "%s", expressionF);
				}
				sprintf(expressionF, "(%s)", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
				_delete(valuesEqR, "valuesEqR");
				valuesEqR = nullptr;
				_delete(valuesEqI, "valuesEqI");
				valuesEqI = nullptr;
				_deleteShort(ValueR, "ValueR");
				ValueR = nullptr;
				_deleteShort(ValueI, "ValueI");
				ValueI = nullptr;
			}
			else {
				sprintf(saveEquation, "%s", originalEquation);
				sprintf(equation, "%s", originalEquation);
				if (isContained("-x", equation)) {
					replace("-x", "+_x", equation);
					sprintf(equation, "%s", expressionF);
				}
				sprintf(toCalcX, "%s", "");
				sprintf(saveToZeroDiv, "%s", equation);
				replaceTimes = 0;
				if (isContained(")*(", equation) || isContained(")(", equation) ||
					isContained(")/(", equation)) {
					if (isContained(")(", equation)) {
						replace(")(", ")*(", equation);
						sprintf(equation, "%s", expressionF);
					}
					resultR = 0;
					resultI = 0;
					product = true;
					simplifyPolynomial<T>(equation);
					product = false;
					sprintf(saveEquation, "%s", expressionF);
					sprintf(equation, "%s", expressionF);
				}

				replaceTimes = 0;
				if (isContained("((", equation)) {
					replace("((", "(", equation);
					sprintf(equation, "%s", expressionF);
				}

				if (isContained("))", equation)) {
					replace("))", ")", equation);
					sprintf(equation, "%s", expressionF);
				}

				sprintf(expression, "%s", expressionF);
				int countLeft = countOccurrences("(", equation);
				int countRight = countOccurrences(")", equation);
				if (countLeft > countRight) {
					sprintf(newEquation, "%s)", equation);
					sprintf(equation, "%s", newEquation);
					_deleteShort(newEquation, "newEquation");
					newEquation = nullptr;
				}

				if (countLeft < countRight) {
					sprintf(newEquation, "(%s", equation);
					sprintf(equation, "%s", newEquation);
					_deleteShort(newEquation, "newEquation");
					newEquation = nullptr;
				}
				putsAndPause("4");

				replaceTimes = 0;
				if (isContained("x", equation) && !isContained("x^", equation)) {
					replace("x", "X^1", equation);
					replace("X", "x", expressionF);
					sprintf(equation, "%s", expressionF);
				}

				replaceTimes = 0;
				if (isContained("[", equation)) {
					replace("[", "(", equation);
					sprintf(equation, "%s", expressionF);
				}

				if (isContained("]", equation)) {
					replace("]", ")", equation);
					sprintf(equation, "%s", expressionF);
				}

				if (isContained("(((", equation)) {
					replace("(((", "((", equation);
					sprintf(equation, "%s", expressionF);
				}

				if (isContained(")))", equation)) {
					replace(")))", "))", equation);
					sprintf(equation, "%s", expressionF);
				}

				replaceTimes = 0;
				sprintf(expressionF, "");
				if (isContained("[", equation)) {
					replace("[", "(", equation);
					sprintf(equation, "%s", expressionF);
				}

				if (isContained("]", equation)) {
					replace("]", ")", equation);
					sprintf(equation, "%s", expressionF);
				}
				removeTriplPars(equation);

				sprintf(equation, "%s", expressionF);
				if (isContained("+)", equation)) {
					replace("+)", ")", equation);
					sprintf(equation, "%s", expressionF);
				}

				if (isContained("++", equation)) {
					replace("++", "", equation);
					sprintf(equation, "%s", expressionF);
				}

				if (isContained("(*", equation)) {
					replace("(*", "(", equation);
					sprintf(equation, "%s", expressionF);
				}

				if (isContained("(*(", equation)) {
					replace("(*(", "((", equation);
					sprintf(equation, "%s", expressionF);
				}

				if (isContained("(*(", equation)) {
					replace("(*(", "((", equation);
					sprintf(equation, "%s", expressionF);
				}

				if (!dataVerifier<double>(equation, 0.0, 0.0, 0, 1)) {
					if (countOccurrences(")", equation) > countOccurrences("(", equation)) {
						int u = countOccurrences(")", equation) - countOccurrences("(", equation);
						if (u == 1) {
							equation[abs((int)strlen(equation)) - 1] = '\0';
						}
					}

					if (countOccurrences(")", equation) < countOccurrences("(", equation)) {
						int u = countOccurrences("(", equation) - countOccurrences(")", equation);
						if (u == 1) {
							int b = 0;
							while (b < abs((int)strlen(equation))) {
								equation[b] = equation[b + 1];
								b++;
							}
							equation[b] = '\0';
						}

					}
				}
				putsAndPause("5");

				sprintf(saveEquation, "%s", equation);
				sprintf(toCalcX, "%s", equation);
				solving = false;
				equationSolverRunning = true;
				sprintf(toCalcX, "%s", saveEquation);
				maxExponent = 0;
				int g = 0, k = 0;
				for (g = 0; g < abs((int)strlen(equation)); g++) {
					if (equation[g - 1] == 'x' && equation[g] == '^') {
						int saveG = g - 2;
						g++;
						k = 0;
						while (verifyNumber(equation[g])) {
							exponent[k] = equation[g];
							k++;
							g++;
						}
						exponent[k] = '\0';
						solveMath<T>(exponent);
						if ((int)precisionValueTo<T>(resultR) > maxExponent) {
							maxExponent = (int)precisionValueTo<T>(resultR);
						}
					}
				}
				_deleteShort(exponent, "exponent");
				exponent = nullptr;
				sprintf(charMaster, "nothingL");
				sprintf(maxExpX, "");
				sprintf(maxExpX, "x^%d", maxExponent);
				while (isContained(maxExpX, toCalcX) && verifyLetter(toCalcX[strStart - 1]) == false &&
					verifyNumber(toCalcX[strStart - 1]) == false) {
					sprintf(value, "x^%d", maxExponent);
					sprintf(valueF, "1*(res)^%d", maxExponent);
					replace(value, valueF, toCalcX);
					sprintf(toCalcX, "%s", expressionF);

				}
				sprintf(charMaster, "");
				while (isContained(maxExpX, toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
					sprintf(value, "%cx^%d", toCalcX[strStart - 1], maxExponent);
					sprintf(valueF, "%c*1*(res)^%d", toCalcX[strStart - 1], maxExponent);
					replace(value, valueF, toCalcX);
					sprintf(toCalcX, "%s", expressionF);
				}
				if (isContained("x+", toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
					replace("x+", "*1*(res)^1+", toCalcX);
					sprintf(toCalcX, "%s", expressionF);
				}
				if (isContained("x-", toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
					replace("x-", "*1*(res)^1-", toCalcX);
					sprintf(toCalcX, "%s", expressionF);
				}
				if (isContained("x", toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
					replace("x", "*1*(res)", toCalcX);
					sprintf(toCalcX, "%s", expressionF);
				}
				sprintf(charMaster, "");
				if (isContained("x+", toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
					replace("x+", "*1*(res)^1+", toCalcX);
					sprintf(toCalcX, "%s", expressionF);
				}
				if (isContained("x-", toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
					replace("x-", "*1*(res)^1-", toCalcX);
					sprintf(toCalcX, "%s", expressionF);
				}
				if (isContained("x", toCalcX) && verifyNumber(toCalcX[strStart - 1])) {
					replace("x", "*1*(res)", toCalcX);
					sprintf(toCalcX, "%s", expressionF);
				}
				if (isContained("x", toCalcX) && !verifyNumber(toCalcX[strStart - 1])) {
					replace("x", "1*(res)", toCalcX);
					sprintf(toCalcX, "%s", expressionF);
				}
				if (value != nullptr) {
					_deleteShort(value, "value"); value = nullptr;
				}
			}
			sprintf(saveToCalcX, "%s", toCalcX);
			sprintf(maxExp, "");
			sprintf(maxExp, ")^%d", maxExponent);
			if (maxExponent > 0) {
				sprintf(expressionF, ")1*(res%s", maxExp);
				if (countOccurrences(maxExp, saveToCalcX) > 1 || !isContained(expressionF, saveToCalcX)) {
					maxExponent = getCorrectExponent<double>(saveToCalcX, maxExp, maxExponent);
				}
				else {
					sprintf(expressionF, ")1*(res%s", maxExp);
					if (isContained(expressionF, saveToCalcX)) {
						int t = strStart;
						while (saveToCalcX[t] != '(') {
							t--;
						}
						t++;
						int v = 0;
						while (saveToCalcX[t] != ')') {
							expressionF[v] = saveToCalcX[t];
							v++; t++;
						}
						expressionF[v] = '\0';
						solveMath<T>(expressionF);
						lastDividerR = precisionValueTo<T>(resultR); lastDividerI = precisionValueTo<T>(resultI);
					}
				}
			}
			_deleteShort(maxExp, "maxExp");
			maxExp = nullptr;
			if (isContained(".", toCalcX)) {
				hasFloatNum = true;
			}

			if (lastElement == 0 && lastElementI == 0) {
				sprintf(expressionF, "%s+(0.00000000000000001)/(1)", toCalcX);
				sprintf(toCalcX, "%s", expressionF);
				sprintf(saveToCalcX, "%s", expressionF);
			}
			putsAndPause("6");

			int g = 0, k = 0;
			if ((precisionValueTo<T>(lastDividerR) != 0 || precisionValueTo<T>(lastDividerI) != 0) && maxExponent > 0) {
				int maxMaxExponent = maxExponent;
				sprintf(expressionF, "(%f+%fi)", precisionValueTo<T>(lastDividerR), precisionValueTo<T>(lastDividerI));
				sprintf(divider, "%s", expressionF);
				for (int y = 0; y < abs((int)strlen(divider)); y++) {
					if (divider[y] == '-') {
						divider[y] = '_';
					}
				}
				if (isContained(".000000", divider)) {
					replace(".000000", "", divider);
					sprintf(divider, "%s", expressionF);
				}

				sprintf(toNoDivider, "%s", toCalcX);
				replaceTimes = 0;
				if (isContained("(*(", toCalcX)) {
					replace("(*(", "((", toCalcX);
					sprintf(toCalcX, "%s", expressionF);

				}
				if (!dataVerifier<double>(toCalcX, 0.0, 0.0, 0, 1)) {
					removeDuplPars(toCalcX);
					sprintf(toCalcX, "%s", expressionF);

				}
				sprintf(expressionF, "(%s)/%s", toCalcX, divider);
				sprintf(newExpre, "%s", expressionF);
				if (dataVerifier<double>(newExpre, 0.0, 0.0, 0, 1)) {
					sprintf(toCalcX, "%s", newExpre);

				}
				else {
					sprintf(expressionF, "%s/%s", toCalcX, divider);
					sprintf(toCalcX, "%s", expressionF);
				}


				if (isContained(".000000", expression)) {
					replace(".000000", "", expression);
					sprintf(expression, "%s", expressionF);
				}
				int u = 0, t = 0, v = 0;
				sprintf(helpExtract, "%s", toNoDivider);
				replaceTimes = 0;
				if (isContained("(((", helpExtract)) {
					replace("(((", "((", helpExtract);
					sprintf(helpExtract, "%s", expressionF);
				}

				if (isContained(")))", helpExtract)) {
					replace(")))", "))", helpExtract);
					sprintf(helpExtract, "%s", expressionF);
				}
				sprintf(saveToCalcX, "%s", toCalcX);

				sprintf(saveHelper, "%s", helpExtract);

				sprintf(toCalcLastEle, "%s", saveHelper);
				if (isContained("res", toCalcLastEle)) {
					replaceTimes = 0;
					replace("res", "0", toCalcLastEle);
					sprintf(toCalcLastEle, "%s", expressionF);
					solveMath<T>(toCalcLastEle);
					lastElement = precisionValueTo<T>(resultR); lastElementI = precisionValueTo<T>(resultI);
				}
				T posLastElement = 0, posLastElementI = 0;
				multiplication<T>(-1.0, 0.0, precisionValueTo<T>(lastElement), precisionValueTo<T>(lastElementI));
				posLastElement = precisionValueTo<T>(resultR); posLastElementI = precisionValueTo<T>(resultI);
				char* posLastEle = getDynamicCharArrayShort("", "posLastEle");
				char* LastEle = getDynamicCharArrayShort("", "LastEle");
				char* value = getDynamicCharArrayShort("", "value");
				char* forSummatory = getDynamicCharArrayShort("", "forSummatory"); char* forExpressionMax = getDynamicCharArrayShort("", "forExpressionMax");
				char* lastFx = getDynamicCharArrayShort("", "lastFx"); char* currentFx = getDynamicCharArrayShort("", "currentFx");
				char* result = getDynamicCharArrayShort("", "result");
				char* result_I = getDynamicCharArrayShort("", "result_I");
				char* rootRExp = getDynamicCharArrayShort("", "rootRExp");
				char* rootIExp = getDynamicCharArrayShort("", "rootIExp");


				sprintf(expressionF, "%f+%fi", posLastElement, posLastElementI);
				sprintf(posLastEle, "%s", expressionF);
				replaceTimes = 0;
				if (isContained("-", posLastEle)) {
					replace("-", "_", posLastEle);
					sprintf(posLastEle, "%s", expressionF);
				}
				if (isContained(".000000", posLastEle)) {
					replace(".000000", "", posLastEle);
					sprintf(posLastEle, "%s", expressionF);
				}
				_deleteShort(posLastEle, "posLastEle"); posLastEle = nullptr;
				int findToRemove = 0;
				if (isContained(")x^1+(", equation)) {
					replaceTimes = 0;

					sprintf(expressionF, "^1+(%f+%fi)", precisionValueTo<T>(lastElement), precisionValueTo<T>(lastElementI));
					sprintf(LastEle, "%s", expressionF);
					replaceTimes = 0;
					if (isContained("-", LastEle)) {
						replace("-", "_", LastEle);
						sprintf(LastEle, "%s", expressionF);
					}
					if (isContained(".000000", LastEle)) {
						replace(".000000", "", LastEle);
						sprintf(LastEle, "%s", expressionF);
					}
					replaceTimes = 1;
					if (isContained(LastEle, saveHelper)) {
						replace(LastEle, "^1+(0+0i)", saveHelper);
						sprintf(saveHelper, "%s", expressionF);
						findToRemove = 1;
					}
					_deleteShort(LastEle, "LastEle");
					LastEle = nullptr;
				}
				if (maxExponent > 0) {
					int hasImaginary = false;
					sprintf(expression, "%s", "");
					while (u < maxExponent) {
						replaceTimes = 0;
						resultR = 0; resultI = 0;
						sprintf(helpExtract, "%s", saveHelper);
						sprintf(expressionF, "1*(res)^%d+", maxExponent - u);
						sprintf(toReplace, "%s", expressionF);
						if (isContained(toReplace, helpExtract)) {
							replace(toReplace, "1*(1)+", helpExtract);
							sprintf(helpExtract, "%s", expressionF);
							if (isContained("res", helpExtract)) {
								replace("res", "0", helpExtract);
								sprintf(helpExtract, "%s", expressionF);
							}
							solveMath<T>(helpExtract);
							if (findToRemove == 0) {
								sum<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), posLastElement, posLastElementI);
							}
							division<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), precisionValueTo<T>(lastDividerR), precisionValueTo<T>(lastDividerI));
							sprintf(expressionF, "%s\\%f+%fi", expression, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
							sprintf(expression, "%s", expressionF);
							expressionCoefR[u] = precisionValueTo<T>(resultR); expressionCoefI[u] = precisionValueTo<T>(resultI);
							if (precisionValueTo<T>(resultI) != 0) {
								hasImaginary = true;
							}
						}
						else {
							replaceTimes = 0;
							resultR = 0; resultI = 0;
							sprintf(helpExtract, "%s", saveHelper);
							sprintf(expressionF, "1*(res)^%d", maxExponent - u);
							sprintf(toReplace, "%s", expressionF);
							if (isContained(toReplace, helpExtract)) {
								replace(toReplace, "1*(1)", helpExtract);
								sprintf(helpExtract, "%s", expressionF);

								if (isContained("res", helpExtract)) {
									replace("res", "0", helpExtract);
									sprintf(helpExtract, "%s", expressionF);
								}
								solveMath<T>(helpExtract);
								if (findToRemove == 0) {
									sum<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), posLastElement, posLastElementI);
								}
								division<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), precisionValueTo<T>(lastDividerR), precisionValueTo<T>(lastDividerI));
								sprintf(expressionF, "%s\\%f+%fi", expression, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
								sprintf(expression, "%s", expressionF);
								expressionCoefR[u] = precisionValueTo<T>(resultR); expressionCoefI[u] = precisionValueTo<T>(resultI);
								if (precisionValueTo<T>(resultI) != 0) {
									hasImaginary = true;
								}
							}
							else {
								resultR = 0; resultI = 0;
								sprintf(expressionF, "%s\\%f+%fi", expression, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
								sprintf(expression, "%s", expressionF);
								expressionCoefR[u] = precisionValueTo<T>(resultR); expressionCoefI[u] = precisionValueTo<T>(resultI);
							}
						}
						u++;
					}

					division<T>(precisionValueTo<T>(lastElement), precisionValueTo<T>(lastElementI), precisionValueTo<T>(lastDividerR), precisionValueTo<T>(lastDividerI));
					lastElement = precisionValueTo<T>(resultR); lastElementI = precisionValueTo<T>(resultI);
					sprintf(expressionF, "%s\\%f+%fi", expression, precisionValueTo<T>(lastElement), precisionValueTo<T>(lastElementI));
					sprintf(expression, "%s", expressionF);
					expressionCoefR[u] = precisionValueTo<T>(lastElement); expressionCoefI[u] = precisionValueTo<T>(lastElementI);

					if (precisionValueTo<T>(resultI) != 0) {
						hasImaginary = true;
					}
					if (isContained("-", expression)) {
						replace("-", "_", expression);
						sprintf(expression, "%s", expressionF);
					}
					if (expression[0] == '\\') {
						int y = 1;
						for (y = 1; y < abs((int)strlen(expression)); y++) {
							expression[y - 1] = expression[y];
						}
						expression[y - 1] = '\0';
					}
					if (isContained(".000000", expression)) {
						replaceTimes = 0;
						replace(".000000", "", expression);
						sprintf(expression, "%s", expressionF);
					}
					replaceTimes = 0;
					int solvedIndex = 0;

					for (int uu = 0; uu <= maxExponent; uu++) {
						saveExpressionCoefR[uu] = 0.0;
						saveExpressionCoefI[uu] = 0.0;
					}
					for (int uu = 0; uu <= maxExponent; uu++) {
						saveExpressionCoefR[uu] = expressionCoefR[uu];
						saveExpressionCoefI[uu] = expressionCoefI[uu];
					}

					if (maxExponent == 1) {
						replaceTimes = 0;
						replace("res", "0", toCalcX);
						solveMath<T>(expressionF);
						multiplication<T>(-1.0, 0.0, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
						RootR[0] = precisionValueTo<T>(resultR); RootI[0] = precisionValueTo<T>(resultI);
						SolutionR[0] = precisionValueTo<T>(resultR); SolutionI[0] = precisionValueTo<T>(resultI);
						solvedIndex++;
						notSolved = false;
						maxExponent--;
					}
					else {
						resultR = 0; resultI = 0;
						int x = 0;
						putsAndPause("7");

						sprintf(value, "");
						int n = 1;
						int countSolutions = 0;
						float local = 0;
						int step = 0;
						int saveProgress = 0;
						int Progress = 0;
						int count = 0;
						int saveG = -1;
						g = 0;
						replaceTimes = 0;
						countSolutions = 0;
						int precisionN = 8;
						int z = 0, h = 0;
						T saveExpressionCoefR_1 = 0, saveExpressionCoefR_Max = 0;

						int k = 0;
						if (!hasFloatNum) {
							saveMaxExponent = maxExponent;
							g = 0;
							int countEnterings = 0;
							int f = 1;
							saveExpressionCoefR_1 = 0, saveExpressionCoefR_Max = 0;
							int p = maxExponent;
							if (abs(expressionCoefR[p]) < 1E-9 && abs(expressionCoefI[p]) < 1E-9) {
								while (abs(expressionCoefR[p]) < 1E-9 && abs(expressionCoefI[p]) < 1E-9) {
									SolutionR[solvedIndex] = 0;
									SolutionI[solvedIndex] = 0;
									solvedIndex++;
									maxExponent--;
									p--;
								}
							}
							int m = solvedIndex;
							int nCycle = 0;
							int lastRootR = 0, lastRootI = 0;
							putsAndPause("8");

							do {
								if (maxExponent > 1) {
									saveExpressionCoefR_1 = 0, saveExpressionCoefR_Max = 0;
									saveExpressionCoefR_Max = expressionCoefR[maxExponent];
									sprintf(forExpressionMax, "%s", convert2Exponential(expressionCoefR[maxExponent]));
									saveExpressionCoefR_1 = expressionCoefR[1];
									z = 0;
									g = 0;
									h = lastRootR + 1;
									for (h; g < maxExponent && z < 500; h++) {
										int _rf = 0;
										T SummatoryR = 0, SummatoryI = 0;
										while (_rf < maxExponent) {
											resultR = pot<T>(h, maxExponent - _rf, 1);
											resultR = expressionCoefR[_rf] * precisionValueTo<T>(resultR);
											SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
											SummatoryI = SummatoryI + 0;
											_rf++;
										}
										sprintf(forSummatory, "%s", convert2Exponential(SummatoryR * -1));
										if (isEqual(forSummatory, forExpressionMax)) {
											lastRootR = abs(h);
											RootR[g] = h; RootI[g] = 0;
											xValuesR = RootR[g];
											xValuesI = RootI[g];
											int _rf = 0;
											T SummatoryR = 0, SummatoryI = 0;
											while (_rf < maxExponent) {
												exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), (T)maxExponent - _rf, 0.0, 1);
												multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
												SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
												SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
												_rf++;
											}
											sum<T>(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
											SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
											if (abs(SummatoryR) < 0.1 && abs(SummatoryI) < 0.1) {
												SolutionR[solvedIndex] = RootR[g];
												SolutionI[solvedIndex] = RootI[g];
												solvedIndex++;
												saveExpressionCoefR_Max = saveExpressionCoefR_Max / h;
												saveExpressionCoefR_1 = saveExpressionCoefR_1 + h;
												g++;
											}

										}
										h = h * -1;
										_rf = 0;
										SummatoryR = 0, SummatoryI = 0;
										while (_rf < maxExponent) {
											resultR = pot<T>(h, maxExponent - _rf, 1);
											resultR = expressionCoefR[_rf] * precisionValueTo<T>(resultR);
											SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
											SummatoryI = SummatoryI + 0;
											_rf++;
										}
										sprintf(forSummatory, "%s", convert2Exponential(SummatoryR * -1));
										if (isEqual(forSummatory, forExpressionMax)) {
											lastRootR = abs(h);
											RootR[g] = h; RootI[g] = 0;
											xValuesR = RootR[g];
											xValuesI = RootI[g];
											int _rf = 0;
											T SummatoryR = 0, SummatoryI = 0;
											while (_rf < maxExponent) {
												exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), (T)maxExponent - _rf, 0.0, 1);
												multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
												SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
												SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
												_rf++;
											}
											sum<T>(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
											SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
											if (abs(SummatoryR) < 0.1 && abs(SummatoryI) < 0.1) {
												SolutionR[solvedIndex] = RootR[g];
												SolutionI[solvedIndex] = RootI[g];
												solvedIndex++;
												saveExpressionCoefR_Max = saveExpressionCoefR_Max / h;
												saveExpressionCoefR_1 = saveExpressionCoefR_1 + h;
												g++;
											}

										}
										h = h * -1;
										z++;
									}

									k = 0;
									if (k < g) {
										while (k < g) {
											int y = 1;
											while (y - 1 < maxExponent) {
												multiplication<T>(expressionCoefR[y - 1], expressionCoefI[y - 1], SolutionR[m], SolutionI[m]);
												sum<T>(expressionCoefR[y], expressionCoefI[y], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
												expressionCoefR[y] = precisionValueTo<T>(resultR); expressionCoefI[y] = precisionValueTo<T>(resultI);
												y++;
											}
											maxExponent--;
											k++;
											m++;
										}
									}
								}
								if (maxExponent > 1) {
									saveExpressionCoefR_1 = 0, saveExpressionCoefR_Max = 0;
									int real = 0;
									g = 0;
									saveExpressionCoefR_1 = 0; saveExpressionCoefR_Max = 0;
									if (abs(expressionCoefI[maxExponent]) >= 1) {
										saveExpressionCoefR_Max = expressionCoefI[maxExponent];
										sprintf(forExpressionMax, "%s", convert2Exponential(abs(expressionCoefI[maxExponent])));
										real = 1;
									}
									else {
										saveExpressionCoefR_Max = expressionCoefR[maxExponent];
										sprintf(forExpressionMax, "%s", convert2Exponential(abs(expressionCoefR[maxExponent])));
									}
									saveExpressionCoefR_1 = expressionCoefI[1];
									z = 0;

									h = lastRootI + 1;
									for (h; g < maxExponent && z < 500; h++) {
										int _rf = 0;
										T SummatoryR = 0, SummatoryI = 0;
										while (_rf < maxExponent) {
											exponentiation<T>(0, h, maxExponent - _rf, 0.0, 1);
											multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
											SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
											SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
											_rf++;
										}
										sprintf(forSummatory, "%s", convert2Exponential(abs(SummatoryI)));
										if (isEqual(forSummatory, forExpressionMax)) {
											RootR[g] = 0; RootI[g] = h;
											xValuesR = RootR[g];
											xValuesI = RootI[g];
											int _rf = 0;
											T SummatoryR = 0, SummatoryI = 0;
											while (_rf < maxExponent) {
												exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), (T)maxExponent - _rf, 0.0, 1);
												multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
												SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
												SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
												_rf++;
											}
											sum<T>(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
											SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
											if (abs(SummatoryR) < 0.1 && abs(SummatoryI) < 0.1) {
												SolutionR[solvedIndex] = RootR[g];
												SolutionI[solvedIndex] = RootI[g];
												solvedIndex++;
												saveExpressionCoefR_Max = saveExpressionCoefR_Max / h;
												saveExpressionCoefR_1 = saveExpressionCoefR_1 + h;
												g++;
											}

										}
										else {
											sprintf(forSummatory, "%s", convert2Exponential(abs(SummatoryR)));
											if (isEqual(forSummatory, forExpressionMax) && abs(SummatoryI) < 1 && real == 1) {
												RootR[g] = 0; RootI[g] = h;
												xValuesR = RootR[g];
												xValuesI = RootI[g];
												int _rf = 0;
												T SummatoryR = 0, SummatoryI = 0;
												while (_rf < maxExponent) {
													exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), (T)maxExponent - _rf, 0.0, 1);
													multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
													SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
													SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
													_rf++;
												}
												sum<T>(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
												SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
												if (abs(SummatoryR) < 0.1 && abs(SummatoryI) < 0.1) {
													SolutionR[solvedIndex] = RootR[g];
													SolutionI[solvedIndex] = RootI[g];
													solvedIndex++;
													saveExpressionCoefR_Max = saveExpressionCoefR_Max / h;
													saveExpressionCoefR_1 = saveExpressionCoefR_1 + h;
													g++;
												}

											}
										}
										h = h * -1;
										_rf = 0;
										SummatoryR = 0, SummatoryI = 0;
										while (_rf < maxExponent) {
											exponentiation<T>(0, h, maxExponent - _rf, 0.0, 1);
											multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
											SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
											SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
											_rf++;
										}
										sprintf(forSummatory, "%s", convert2Exponential(abs(SummatoryI)));
										if (isEqual(forSummatory, forExpressionMax)) {
											RootR[g] = 0; RootI[g] = h;
											xValuesR = RootR[g];
											xValuesI = RootI[g];
											int _rf = 0;
											T SummatoryR = 0, SummatoryI = 0;
											while (_rf < maxExponent) {
												exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), (T)maxExponent - _rf, 0.0, 1);
												multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
												SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
												SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
												_rf++;
											}
											sum<T>(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
											SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
											if (abs(SummatoryR) < 0.1 && abs(SummatoryI) < 0.1) {
												SolutionR[solvedIndex] = RootR[g];
												SolutionI[solvedIndex] = RootI[g];
												solvedIndex++;
												saveExpressionCoefR_Max = saveExpressionCoefR_Max / h;
												saveExpressionCoefR_1 = saveExpressionCoefR_1 + h;
												g++;
											}

										}
										else {
											sprintf(forSummatory, "%s", convert2Exponential(abs(SummatoryR)));
											if (isEqual(forSummatory, forExpressionMax) && abs(SummatoryI) < 1 && real == 1) {
												RootR[g] = 0; RootI[g] = h;
												xValuesR = RootR[g];
												xValuesI = RootI[g];
												int _rf = 0;
												T SummatoryR = 0, SummatoryI = 0;
												while (_rf < maxExponent) {
													exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), (T)maxExponent - _rf, 0.0, 1);
													multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
													SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
													SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
													_rf++;
												}
												sum<T>(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
												SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
												if (abs(SummatoryR) < 0.1 && abs(SummatoryI) < 0.1) {
													SolutionR[solvedIndex] = RootR[g];
													SolutionI[solvedIndex] = RootI[g];
													solvedIndex++;
													saveExpressionCoefR_Max = saveExpressionCoefR_Max / h;
													saveExpressionCoefR_1 = saveExpressionCoefR_1 + h;
													g++;
												}

											}
										}
										h = h * -1;
										z++;
									}

									k = 0;
									if (k < g) {
										while (k < g) {
											int y = 1;
											while (y - 1 < maxExponent) {
												multiplication<T>(expressionCoefR[y - 1], expressionCoefI[y - 1], SolutionR[m], SolutionI[m]);
												sum<T>(expressionCoefR[y], expressionCoefI[y], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
												expressionCoefR[y] = precisionValueTo<T>(resultR); expressionCoefI[y] = precisionValueTo<T>(resultI);
												y++;
											}
											maxExponent--;
											k++;
											m++;
										}
									}

								}
								nCycle++;
								if (nCycle < solvedIndex) {
									nCycle = solvedIndex;
								}
								if (maxExponent > 0 && nCycle < maxExponent) {
									solvedIndex = saveMaxExponent - maxExponent;
									m = solvedIndex;
								}
							} while (maxExponent > 0 && nCycle < maxExponent);
							g = 0;
							int gg = 0;
							while (g < solvedIndex && solvedIndex < maxMaxExponent && gg < maxMaxExponent * 2) {
								xValuesR = SolutionR[g];
								xValuesI = SolutionI[g];
								int _rf = 0;
								T SummatoryR = 0, SummatoryI = 0;
								while (_rf < maxExponent) {
									exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), maxExponent - _rf, 0.0, 1);
									multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
									SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
									SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
									_rf++;
								}
								sum<T>(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
								SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
								if (abs(SummatoryR) < 1E-9 && abs(SummatoryI) < 1E-9) {
									SolutionR[solvedIndex] = precisionValueTo<T>(xValuesR);
									SolutionI[solvedIndex] = precisionValueTo<T>(xValuesI);
									int y = 1;
									while (y - 1 < maxExponent) {
										multiplication<T>(expressionCoefR[y - 1], expressionCoefI[y - 1], SolutionR[solvedIndex], SolutionI[solvedIndex]);
										sum<T>(expressionCoefR[y], expressionCoefI[y], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
										expressionCoefR[y] = precisionValueTo<T>(resultR); expressionCoefI[y] = precisionValueTo<T>(resultI);
										y++;
									}
									solvedIndex++;
									maxExponent--;
									g = 0;
								}
								g++;
								gg++;
							}
							precisionN = 8;
							if (maxExponent == 1) {
								int _rf = 0;
								T SummatoryR = 0, SummatoryI = 0;
								while (_rf < maxExponent) {
									exponentiation<T>(0, 0, maxExponent - _rf, 0.0, 1);
									multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
									SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
									SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
									_rf++;
								}
								sum<T>(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
								SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
								multiplication<T>(-1, 0, SummatoryR, SummatoryI);
								SolutionR[solvedIndex] = precisionValueTo<T>(resultR); SolutionI[solvedIndex] = precisionValueTo<T>(resultI);
								solvedIndex++;
							}

						}
						putsAndPause("9");

						if (maxExponent > 1 || maxExponent == maxMaxExponent) {
					


							int saveMaxExponent = maxExponent;
							while (_rf <= maxExponent) {
								saveExpressionCoefRN[_rf] = expressionCoefR[_rf];
								saveExpressionCoefIN[_rf] = expressionCoefI[_rf];
								_rf++;
							}


							rasf = 0;

							int count = 0;
							T deltaxR = 1, deltaxI = 0;
							int i = 0;
							T* expressCoefR = getDynamicArray<T>(DIMDOUBLE);
							T* expressCoefI = getDynamicArray<T>(DIMDOUBLE);
							T* expresR = getDynamicArray<T>(DIMDOUBLE);
							T* expresI = getDynamicArray<T>(DIMDOUBLE);
							do {
								i = 0;
								T xValueR = 0, xValueI = 0, solR = 0, solI = 0;

								T fxDevR = 0, fxDevI = 0;
								sprintf(lastFx, ""); ;
								sprintf(currentFx, "");
								while (i < 150) {
									xValuesR = xValueR; xValuesI = xValueI;
									int _rf = 0;
									T SummatoryR = 0, SummatoryI = 0;
									while (_rf < maxExponent) {
										exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), (T)maxExponent - _rf, 0.0, 1);
										multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));

										SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
										SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
										_rf++;
									}
									sum<T>(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
									T fxR = precisionValueTo<T>(resultR), fxI = precisionValueTo<T>(resultI);
									sprintf(currentFx, "%G+%Gi", abs(fxR), abs(fxI));
									if (isEqual(currentFx, lastFx) && abs(fxR) < 1E-6 && abs(fxI) < 1E-6 && i > 10) {
										break;
									}

									xValuesR = xValueR + deltaxR;
									xValuesI = xValueI + deltaxI;
									_rf = 0;
									SummatoryR = 0; SummatoryI = 0;
									while (_rf < maxExponent) {
										exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), (T)maxExponent - _rf, 0.0, 1);
										multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));

										SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
										SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
										_rf++;
									}
									sum<T>(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
									T fxplusaR = precisionValueTo<T>(resultR), fxplusaI = precisionValueTo<T>(resultI);
									subtraction<T>(fxplusaR, fxplusaI, fxR, fxI);
									division<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), deltaxR, deltaxI);

									if (precisionValueTo<T>(resultR) != 0 || precisionValueTo<T>(resultI) != 0) {
										fxDevR = precisionValueTo<T>(resultR), fxDevI = precisionValueTo<T>(resultI);
									}

									division<T>(fxR, fxI, fxDevR, fxDevI);
									subtraction<T>(xValueR, xValueI, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
									if (i < 5) {
										xValueR = quo(precisionValueTo<T>(resultR)); xValueI = quo(precisionValueTo<T>(resultI));
									}
									else {
										xValueR = precisionValueTo<T>(resultR); xValueI = precisionValueTo<T>(resultI);
									}

									solR = xValueR; solI = xValueI;

									sprintf(lastFx, "%s", currentFx);
									i++;
								}
								if (i <= 150) {

									RootR[count] = solR + 0.7; RootI[count] = solI + 0.7;

									int y = 1;
									while (y - 1 < maxExponent) {
										multiplication<T>(expressionCoefR[y - 1], expressionCoefI[y - 1], RootR[count], RootI[count]);
										sum<T>(expressionCoefR[y], expressionCoefI[y], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
										expressionCoefR[y] = precisionValueTo<T>(resultR); expressionCoefI[y] = precisionValueTo<T>(resultI);
										y++;
									}
									maxExponent--;
									count++;
								}
							} while (maxExponent > 0);

							_deleteShort(lastFx, "lastFx");
							lastFx = nullptr;
							_deleteShort(currentFx, "currentFx");
							currentFx = nullptr;
							maxExponent = saveMaxExponent;
							_rf = 0;
							while (_rf <= maxExponent) {
								expressionCoefR[_rf] = saveExpressionCoefRN[_rf];
								expressionCoefI[_rf] = saveExpressionCoefIN[_rf];
								_rf++;
							}

							_rf = 0;
							resultR = 0; resultI = 0;
							int x = 0;

							sprintf(value, "");
							int n = 1;
							float local = 0;
							int step = 0;
							int saveProgress = 0;
							int Progress = 0;
							count = 0;
							int saveG = -1;
							g = 0;
							int totalCalc = 0;
							replaceTimes = 0;
							countSolutions = 0;
							precisionN = 6;
							T summaR = 0, summaI = 0;

							int r = 0;
							for (r = 0; r <= maxExponent; r++) {
								expresR[r] = expressionCoefR[r];
								expresI[r] = expressionCoefI[r];
							}
							int breakAction = 0;
							T saveRootR, saveRootI;
							notSolved = true;
							putsAndPause("10");

							if (maxMaxExponent <= 68) {
								while (((!notSolved && n < breakAction) || (notSolved && countSolutions < maxMaxExponent - 1)) && n < 7777) {
									g = 0;
									putsAndPause("11");

									if (maxExponent > 0 && n % (maxExponent * 3) == 0) {
										getRoots(expressionCoefR, expressionCoefI, RootR, RootI, maxExponent, g);
									}
									T sumRootsR = 0, sumRootsI = 0;
									while (g < maxExponent) {
										putsAndPause("12");

										xValuesR = RootR[g];
										xValuesI = RootI[g];
										saveRootR = RootR[g];
										saveRootI = RootI[g];
										int _rf = 0;
										T SummatoryR = 0, SummatoryI = 0;
										while (_rf < maxExponent) {
											exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), (T)maxExponent - _rf, 0.0, 1);
											multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));


											SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
											SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
											_rf++;
										}

										sum<T>(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);

										summaR = precisionValueTo<T>(resultR); summaI = precisionValueTo<T>(resultI);
										char* pointer = nullptr;
										sprintf(value, "%s", convert2Exponential(RootR[g]));
										SolutionR[solvedIndex] = strtod(value, &pointer);
										sprintf(value, "%s", convert2Exponential(RootI[g]));
										SolutionI[solvedIndex] = strtod(value, &pointer);

										if (abs(SolutionR[solvedIndex]) < 1E-5) {
											SolutionR[solvedIndex] = 0;
										}
										if (abs(SolutionI[solvedIndex]) < 1E-5) {
											SolutionI[solvedIndex] = 0;
										}
										memcpy(expressCoefR,
											expressionCoefR,
											DIMDOUBLE * sizeof(T));

										memcpy(expressCoefI,
											expressionCoefI,
											DIMDOUBLE * sizeof(T));
										T saveLastR = expressionCoefR[maxExponent], saveLastI = expressionCoefI[maxExponent];

										expressCoefR[0] = 1; expressCoefI[0] = 0;
										int y = 1;
										while (y - 1 < maxExponent) {
											putsAndPause("12.2");
											multiplication<T>(expressCoefR[y - 1], expressCoefI[y - 1], SolutionR[solvedIndex], SolutionI[solvedIndex]);
											sum<T>(expressCoefR[y], expressCoefI[y], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
											expressCoefR[y] = precisionValueTo<T>(resultR); expressCoefI[y] = precisionValueTo<T>(resultI);
											y++;
										}
										T saveResultR = expressCoefR[y - 2], saveResultI = expressCoefI[y - 2];

										xValuesR = M_PI;
										xValuesI = 0;
										T SummatoryCR = 0, SummatoryCI = 0;
										_rf = 0;
										while (_rf < (maxExponent - 1)) {

											exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), (maxExponent - 1) - _rf, 0.0, 1);
											multiplication<T>(expressCoefR[_rf], expressCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
											SummatoryCR = SummatoryCR + precisionValueTo<T>(resultR);
											SummatoryCI = SummatoryCI + precisionValueTo<T>(resultI);
											_rf++;
										}
										sum<T>(SummatoryCR, SummatoryCI, expressCoefR[_rf], expressCoefI[_rf]);
										SummatoryCR = precisionValueTo<T>(resultR); SummatoryCI = precisionValueTo<T>(resultI);
										_rf = 0;
										SummatoryR = 0; SummatoryI = 0;
										while (_rf < maxExponent) {
											exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), maxExponent - _rf, 0.0, 1);
											multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
											SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
											SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
											_rf++;
										}
										sum<T>(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
										SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
										multiplication<T>(SummatoryCR, SummatoryCI, precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI));
										T saveR = precisionValueTo<T>(resultR), saveI = precisionValueTo<T>(resultI);
										multiplication<T>(SummatoryCR, SummatoryCI, SolutionR[solvedIndex], SolutionI[solvedIndex]);
										subtraction<T>(saveR, saveI, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
										division<T>(SummatoryR, SummatoryI, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));

										sprintf(result, "%s", convert2Exponential(precisionValueTo<T>(resultR)));

										sprintf(result_I, "%s", convert2Exponential(precisionValueTo<T>(resultI)));

										if (isEqual("1", result) && isEqual("0", result_I) && (summaR == 0 || summaI == 0) && maxExponent < 5) {

											re_complex<T>(expressionCoefR[maxExponent], expressionCoefI[maxExponent], SolutionR[solvedIndex], SolutionI[solvedIndex]);
											sprintf(result, "%s", convert2Exponential(precisionValueTo<T>(resultR)));
											sprintf(result_I, "%s", convert2Exponential(precisionValueTo<T>(resultI)));
											if (isEqual("0", result) && isEqual("0", result_I)) {
												int v = 0, u = 0;
												while (v < maxExponent) {
													if (v != g) {
														RootR[u] = RootR[v];
														RootI[u] = RootI[v];
														u++;
													}
													v++;
												}
												countSolutions++;
												n = 0;
												g = 0;
												solvedIndex++;
												maxExponent--;
												int y = 1;
												while (y - 1 < maxExponent) {
													expressionCoefR[y] = expressCoefR[y]; expressionCoefI[y] = expressCoefI[y];
													y++;
												}
											}
										}
										else {
											T numR = summaR, numI = summaI, denR = 1, denI = 0;
											int w = 0, h = 0;
											while (w < maxExponent) {
												if (w != g) {
													subtraction<T>(RootR[g], RootI[g], RootR[w], RootI[w]);
													resultSubR[h] = precisionValueTo<T>(resultR);
													resultSubI[h] = precisionValueTo<T>(resultI);
													h++;
												}
												w++;
											}
											int k = h;
											h = 1;
											while (h < k) {
												multiplication<T>(resultSubR[0], resultSubI[0], resultSubR[h], resultSubI[h]);
												resultSubR[0] = precisionValueTo<T>(resultR);
												resultSubI[0] = precisionValueTo<T>(resultI);
												h++;
											}
											denR = resultSubR[0];
											denI = resultSubI[0];
											division<T>(numR, numI, denR, denI);
											subtraction<T>(RootR[g], RootI[g], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
											RootR[g] = precisionValueTo<T>(resultR);
											RootI[g] = precisionValueTo<T>(resultI);

											T res_1 = 0, res_2 = 0, res_1Conj = 0, res_2Conj = 0;
											if (g % 2 == 1 && maxExponent > 4) {
												res_1 = RootR[g] - saveRootR;
												res_2 = RootI[g] - saveRootI;
												xValuesR = RootR[g - 1];
												xValuesI = RootI[g - 1];
												T saveRootR2 = RootR[g - 1];
												T	saveRootI2 = RootI[g - 1];
												int _rf = 0;
												T SummatoryR = 0, SummatoryI = 0;
												while (_rf < maxExponent) {
													exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), (T)maxExponent - _rf, 0.0, 1);
													multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
													expressCoefR[_rf] = expressionCoefR[_rf];
													expressCoefI[_rf] = expressionCoefI[_rf];
													SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
													SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
													_rf++;
												}
												sum<T>(SummatoryR, SummatoryI, expressionCoefR[_rf], expressionCoefI[_rf]);
												expressCoefR[_rf] = expressionCoefR[_rf];
												expressCoefI[_rf] = expressionCoefI[_rf];
												summaR = precisionValueTo<T>(resultR); summaI = precisionValueTo<T>(resultI);
												T numR = summaR, numI = summaI, denR = 1, denI = 0;
												int w = 0, h = 0;
												while (w < maxExponent) {
													if (w != g - 1) {
														subtraction<T>(RootR[g - 1], RootI[g - 1], RootR[w], RootI[w]);
														resultSubR[h] = precisionValueTo<T>(resultR);
														resultSubI[h] = precisionValueTo<T>(resultI);
														h++;
													}
													w++;
												}
												int k = h;
												h = 1;
												while (h < k) {
													multiplication<T>(resultSubR[0], resultSubI[0], resultSubR[h], resultSubI[h]);
													resultSubR[0] = precisionValueTo<T>(resultR);
													resultSubI[0] = precisionValueTo<T>(resultI);
													h++;
												}
												denR = resultSubR[0];
												denI = resultSubI[0];
												division<T>(numR, numI, denR, denI);
												subtraction<T>(RootR[g - 1], RootI[g - 1], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
												RootR[g - 1] = precisionValueTo<T>(resultR);
												RootI[g - 1] = precisionValueTo<T>(resultI);
												res_1Conj = RootR[g - 1] - saveRootR2;
												res_2Conj = RootI[g - 1] - saveRootI2;
											}
											if (abs(res_1) < 1E-16 && abs(res_2) < 1E-16 && maxExponent > 2 && n > 117 && g % 2 == 1 && maxExponent > 4) {
												if (abs(res_1Conj) < 1E-16 && abs(res_2Conj) < 1E-16 && maxExponent > 2 && n > 117) {
													int y = 1;
													while (y - 1 < maxExponent - 1) {
														multiplication<T>(expressionCoefR[y - 1], expressionCoefI[y - 1], RootR[g - 1], RootI[g - 1]);
														sum<T>(expressionCoefR[y], expressionCoefI[y], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
														expressionCoefR[y] = precisionValueTo<T>(resultR); expressionCoefI[y] = precisionValueTo<T>(resultI);
														y++;
													}

													y = 1;
													while (y - 1 < maxExponent - 2) {
														multiplication<T>(expressionCoefR[y - 1], expressionCoefI[y - 1], SolutionR[solvedIndex], SolutionI[solvedIndex]);
														sum<T>(expressionCoefR[y], expressionCoefI[y], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
														expressionCoefR[y] = precisionValueTo<T>(resultR); expressionCoefI[y] = precisionValueTo<T>(resultI);
														y++;
													}
													solvedIndex++;
													SolutionR[solvedIndex] = RootR[g - 1]; SolutionI[solvedIndex] = RootI[g - 1];
													solvedIndex++;
													int v = 0, u = 0;
													while (v < maxExponent) {
														if (v != g - 1 && v != g) {
															RootR[u] = RootR[v];
															RootI[u] = RootI[v];
															u++;
														}
														v++;
													}
													maxExponent = maxExponent - 2;
													countSolutions = countSolutions + 2;
													n = 0;
													g = 0;
												}
												else {
													int y = 1;
													while (y - 1 < maxExponent - 1) {
														multiplication<T>(expressionCoefR[y - 1], expressionCoefI[y - 1], SolutionR[solvedIndex], SolutionI[solvedIndex]);
														sum<T>(expressionCoefR[y], expressionCoefI[y], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
														expressionCoefR[y] = precisionValueTo<T>(resultR); expressionCoefI[y] = precisionValueTo<T>(resultI);
														y++;
													}
													solvedIndex++;
													int v = 0, u = 0;
													while (v < maxExponent) {
														if (v != g) {
															RootR[u] = RootR[v];
															RootI[u] = RootI[v];
															u++;
														}
														v++;
													}
													maxExponent--;
													countSolutions++;
													n = 0;
													g = 0;
												}
											}
											else {
												if (notSolved) {
													for (r = 0; r <= maxExponent; r++) {
														expresR[r] = expressionCoefR[r];
														expresI[r] = expressionCoefI[r];
													}
													sumRootsR = 0; sumRootsI = 0;
													for (int kw = 0; kw < maxExponent; kw++) {
														if (kw != g) {
															int y = 1;
															while (y - 1 < maxExponent) {
																multiplication<T>(expresR[y - 1], expresI[y - 1], RootR[kw], RootI[kw]);
																sum<T>(expresR[y], expresI[y], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
																expresR[y] = precisionValueTo<T>(resultR); expresI[y] = precisionValueTo<T>(resultI);
																y++;
															}
														}
														sum<T>(sumRootsR, sumRootsI, RootR[kw], RootI[kw]);
														sumRootsR = precisionValueTo<T>(resultR); sumRootsI = precisionValueTo<T>(resultI);
														division<T>(sumRootsR, sumRootsI, expressCoefR[1], expressCoefI[1]);
														if (abs(precisionValueTo<T>(resultR)) <= 1 && abs(precisionValueTo<T>(resultR)) > 0.99999 && abs(precisionValueTo<T>(resultI)) < 0.0001) {
															notSolved = false;
															breakAction = n + 237;
														}
													}
													multiplication<T>(-1.0, 0.0, expresR[1], expresI[1]);
													T helperR = precisionValueTo<T>(resultR), helperI = precisionValueTo<T>(resultI);
													T fromHelperR, fromHelperI;
													T fromAlgR, fromAlgI;
													multiplication<T>(0.73, 0.0, helperR, helperI);
													fromHelperR = precisionValueTo<T>(resultR); fromHelperI = precisionValueTo<T>(resultI);
													multiplication<T>(0.27, 0.0, RootR[g], RootI[g]);
													fromAlgR = precisionValueTo<T>(resultR); fromAlgI = precisionValueTo<T>(resultI);
													sum<T>(fromAlgR, fromAlgI, fromHelperR, fromHelperI);
													RootR[g] = precisionValueTo<T>(resultR);
													RootI[g] = precisionValueTo<T>(resultI);

												}
												if (g >= 1) {
													putsAndPause("16");

													T rootR1, rootI1, rootR2, rootI2;
													multiplication<T>(RootR[g - 1], RootI[g - 1], -1.0, 0.0);
													rootR1 = precisionValueTo<T>(resultR); rootI1 = precisionValueTo<T>(resultI);
													multiplication<T>(RootR[g], RootI[g], -1.0, 0.0);
													rootR2 = precisionValueTo<T>(resultR); rootI2 = precisionValueTo<T>(resultI);
													T bR, bI, cR, cI;
													sum<T>(rootR1, rootI1, rootR2, rootI2);
													bR = precisionValueTo<T>(resultR); bI = precisionValueTo<T>(resultI);
													multiplication<T>(rootR1, rootI1, rootR2, rootI2);
													cR = precisionValueTo<T>(resultR); cI = precisionValueTo<T>(resultI);
													multiplication<T>(-1, 0, bR, bI);
													T minusbR = precisionValueTo<T>(resultR), minusbI = precisionValueTo<T>(resultI);
													multiplication<T>(bR, bI, bR, bI);
													T bRquad = precisionValueTo<T>(resultR), bIquad = precisionValueTo<T>(resultI);
													multiplication<T>(1.0, 0.0, cR, cI);
													T acR = precisionValueTo<T>(resultR), acI = precisionValueTo<T>(resultI);
													multiplication<T>(2, 0, 1.0, 0.0);
													T twoaR = precisionValueTo<T>(resultR), twoaI = precisionValueTo<T>(resultI);
													multiplication<T>(4, 0, acR, acI);
													T fouracR = precisionValueTo<T>(resultR), fouracI = precisionValueTo<T>(resultI);
													subtraction<T>(bRquad, bIquad, fouracR, fouracI);
													T radicandR = precisionValueTo<T>(resultR), radicandI = precisionValueTo<T>(resultI);
													exponentiation<T>(radicandR, radicandI, 0.5, 0, 1);
													T sqrtR = precisionValueTo<T>(resultR), sqrtI = precisionValueTo<T>(resultI);
													subtraction<T>(minusbR, minusbI, sqrtR, sqrtI);
													T minusR = precisionValueTo<T>(resultR), minusI = precisionValueTo<T>(resultI);
													sum<T>(minusbR, minusbI, sqrtR, sqrtI);
													T plusR = precisionValueTo<T>(resultR), plusI = precisionValueTo<T>(resultI);
													division<T>(plusR, plusI, twoaR, twoaI);
													T x1R = precisionValueTo<T>(resultR), x1I = precisionValueTo<T>(resultI);
													division<T>(minusR, minusI, twoaR, twoaI);
													T x2R = precisionValueTo<T>(resultR), x2I = precisionValueTo<T>(resultI);
													RootR[g - 1] = x1R; RootI[g - 1] = x1I;
													RootR[g] = x2R; RootI[g] = x2I;
													
													}
												}
											
										}

										g++;

									}
									n++;
								}

							}

							else {

								if (maxExponent > 68) {
									saveMaxExponent = maxExponent;
									g = 0;

									_rf = 0;
									while (_rf < maxExponent) {
										multiplication<T>(expressionCoefR[_rf], expressionCoefI[_rf], (T)maxExponent - _rf, 0.0);
										expDerivateR[_rf] = precisionValueTo<T>(resultR);
										expDerivateI[_rf] = precisionValueTo<T>(resultI);
										saveExpDerivateR[_rf] = precisionValueTo<T>(resultR);
										saveExpDerivateI[_rf] = precisionValueTo<T>(resultI);
										_rf++;
									}
									_rf = 0;

									while (_rf <= maxExponent) {
										saveExpressionCoefRN[_rf] = expressionCoefR[_rf];
										saveExpressionCoefIN[_rf] = expressionCoefI[_rf];
										expressCoefR[_rf] = expressionCoefR[_rf];
										expressCoefI[_rf] = expressionCoefI[_rf];
										_rf++;
									}
									int countSolutions = 0;
									_rf = 0;
									while (_rf <= maxExponent) {
										expressCoefR[_rf] = expressionCoefR[_rf];
										expressCoefI[_rf] = expressionCoefI[_rf];
										_rf++;
									}
									saveMaxExponent = maxExponent;
									n = 0;
									RootR[g] = 0; RootI[g] = 0;
									while (countSolutions < saveMaxExponent) {
										if (n == 2000) {
											countSolutions++;
											n = 0;

											int y = 1;
											while (y - 1 < maxExponent) {
												multiplication<T>(expressCoefR[y - 1], expressCoefI[y - 1], RootR[g], RootI[g]);
												sum<T>(expressCoefR[y], expressCoefI[y], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
												expressCoefR[y] = precisionValueTo<T>(resultR); expressCoefI[y] = precisionValueTo<T>(resultI);
												y++;
											}
											_rf = 0;
											while (_rf < maxExponent) {
												multiplication<T>(expressCoefR[_rf], expressCoefI[_rf], (T)maxExponent - _rf, 0.0);
												expDerivateR[_rf] = precisionValueTo<T>(resultR);
												expDerivateI[_rf] = precisionValueTo<T>(resultI);
												_rf++;
											}
											g++;
											RootR[g] = RootR[g - 1]; RootI[g] = RootI[g - 1];
											maxExponent--;
										}
										else {
											T SummDerivateR = 0, SummDerivateI = 0;
											xValuesR = RootR[g];
											xValuesI = RootI[g];
											_rf = 0;
											T SummatoryR = 0, SummatoryI = 0;
											while (_rf < maxExponent) {
												exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), maxExponent - _rf, 0.0, 1);
												multiplication<T>(expressCoefR[_rf], expressCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
												SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
												SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
												_rf++;
											}
											sum<T>(SummatoryR, SummatoryI, expressCoefR[_rf], expressCoefI[_rf]);
											SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
											SummDerivateR = 0; SummDerivateI = 0;
											_rf = 0;
											while (_rf < maxExponent - 1) {
												exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), maxExponent - _rf - 1, 0.0, 1);
												multiplication<T>(expDerivateR[_rf], expDerivateI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
												SummDerivateR = SummDerivateR + precisionValueTo<T>(resultR);
												SummDerivateI = SummDerivateI + precisionValueTo<T>(resultI);
												_rf++;
											}
											sum<T>(SummDerivateR, SummDerivateI, expDerivateR[_rf], expDerivateI[_rf]);
											SummDerivateR = precisionValueTo<T>(resultR); SummDerivateI = precisionValueTo<T>(resultI);
											division<T>(SummatoryR, SummatoryI, SummDerivateR, SummDerivateI);
											subtraction<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
											RootR[g] = precisionValueTo<T>(resultR);
											RootI[g] = precisionValueTo<T>(resultI);
											if (n > 1000) {
												xValuesR = RootR[g];
												xValuesI = RootI[g];
												_rf = 0;
												SummatoryR = 0; SummatoryI = 0;
												while (_rf < saveMaxExponent) {
													exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), saveMaxExponent - _rf, 0.0, 1);
													multiplication<T>(saveExpressionCoefRN[_rf], saveExpressionCoefIN[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
													SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
													SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
													_rf++;
												}
												sum<T>(SummatoryR, SummatoryI, saveExpressionCoefRN[_rf], saveExpressionCoefIN[_rf]);
												SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
												SummDerivateR = 0; SummDerivateI = 0;
												_rf = 0;
												while (_rf < saveMaxExponent - 1) {
													exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), saveMaxExponent - _rf - 1, 0.0, 1);
													multiplication<T>(saveExpDerivateR[_rf], saveExpDerivateI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
													SummDerivateR = SummDerivateR + precisionValueTo<T>(resultR);
													SummDerivateI = SummDerivateI + precisionValueTo<T>(resultI);
													_rf++;
												}
												sum<T>(SummDerivateR, SummDerivateI, saveExpDerivateR[_rf], saveExpDerivateI[_rf]);
												SummDerivateR = precisionValueTo<T>(resultR); SummDerivateI = precisionValueTo<T>(resultI);
												division<T>(SummatoryR, SummatoryI, SummDerivateR, SummDerivateI);
												subtraction<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
												RootR[g] = precisionValueTo<T>(resultR);
												RootI[g] = precisionValueTo<T>(resultI);
											}
										}

										n++;
									}
									maxExponent = saveMaxExponent;
									_delete(expDerivateR, "expDerivateR");
									expDerivateR = nullptr;
									_delete(expDerivateI, "expDerivateI");
									expDerivateI = nullptr;
									_delete(saveExpDerivateR, "saveExpDerivateR");
									saveExpDerivateR = nullptr;
									_delete(saveExpDerivateI, "saveExpDerivateI");
									saveExpDerivateI = nullptr;


								}
							}
							_delete(expressCoefR, "expressCoefR"); _delete(expressCoefI, "expressCoefI");
							_delete(expresR, "expresR"); _delete(expresI, "expresI");
							_delete(saveExpressionCoefRN, "saveExpressionCoefRN");
							saveExpressionCoefRN = nullptr;
							_delete(saveExpressionCoefIN, "saveExpressionCoefIN");
							saveExpressionCoefIN = nullptr;

							_delete(saveExpressionCoefRN, "saveExpressionCoefRN"); saveExpressionCoefRN = nullptr;
							_delete(saveExpressionCoefIN, "saveExpressionCoefIN"); saveExpressionCoefIN = nullptr;

							_delete(result, "result"); result = nullptr;
							_delete(result_I, "result_I"); result_I = nullptr;
						}

						_deleteShort(forSummatory, "forSummatory");
						forSummatory = nullptr;
					}
					int y = 0;
					sprintf(value, "");
								if (maxExponent == 0) {
						notSolved = false;
					}
					char* pointer = nullptr;
					while (y < maxExponent) {
						sprintf(value, "%s", convert2Exponential(RootR[y]));
						RootR[y] = strtod(value, &pointer);
						sprintf(value, "%s", convert2Exponential(RootI[y]));
						RootI[y] = strtod(value, &pointer);
						SolutionR[solvedIndex] = RootR[y];
						SolutionI[solvedIndex] = RootI[y];
						solvedIndex++; y++;
					}


					maxExponent = maxMaxExponent;
					if (maxExponent >= 2 && !notSolved && SolutionR[0] != 0 && SolutionI[0] != 0) {
						int n = 0;
						while (n < 100) {
							g = 0;
							while (g < maxExponent) {
								xValuesR = SolutionR[g];
								xValuesI = SolutionI[g];
								int _rf = 0;
								T SummatoryR = 0, SummatoryI = 0;
								while (_rf < maxExponent) {
									exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), (T)maxExponent - _rf, 0.0, 1);
									multiplication<T>(saveExpressionCoefR[_rf], saveExpressionCoefI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
									SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
									SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
									_rf++;
								}
								sum<T>(SummatoryR, SummatoryI, saveExpressionCoefR[_rf], saveExpressionCoefI[_rf]);
								T numR = precisionValueTo<T>(resultR), numI = precisionValueTo<T>(resultI), denR = 1, denI = 0;
								int w = 0, h = 0;
								while (w < maxExponent) {
									if (w != g) {
										subtraction<T>(SolutionR[g], SolutionI[g], SolutionR[w], SolutionI[w]);
										resultSubR[h] = precisionValueTo<T>(resultR);
										resultSubI[h] = precisionValueTo<T>(resultI);
										h++;
									}
									w++;
								}
								int k = h;
								h = 1;
								while (h < k) {
									multiplication<T>(resultSubR[0], resultSubI[0], resultSubR[h], resultSubI[h]);
									resultSubR[0] = precisionValueTo<T>(resultR);
									resultSubI[0] = precisionValueTo<T>(resultI);
									h++;
								}
								denR = resultSubR[0];
								denI = resultSubI[0];
								division<T>(numR, numI, denR, denI);
								subtraction<T>(SolutionR[g], SolutionI[g], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
								SolutionR[g] = precisionValueTo<T>(resultR);
								SolutionI[g] = precisionValueTo<T>(resultI);
								g++;
							}
							n++;
						}
					}
					if (maxExponent >= 2 && !notSolved && SolutionR[0] != 0) {
						int zz = 0;
						do {
							for (int ii = 1; ii < maxExponent; ii++) {
								T rootR1, rootI1, rootR2, rootI2;
								multiplication<T>(SolutionR[ii - 1], SolutionI[ii - 1], -1.0, 0.0);
								rootR1 = precisionValueTo<T>(resultR); rootI1 = precisionValueTo<T>(resultI);
								multiplication<T>(SolutionR[ii], SolutionI[ii], -1.0, 0.0);
								rootR2 = precisionValueTo<T>(resultR); rootI2 = precisionValueTo<T>(resultI);
								T bR, bI, cR, cI;
								sum<T>(rootR1, rootI1, rootR2, rootI2);
								bR = precisionValueTo<T>(resultR); bI = precisionValueTo<T>(resultI);
								multiplication<T>(rootR1, rootI1, rootR2, rootI2);
								cR = precisionValueTo<T>(resultR); cI = precisionValueTo<T>(resultI);
								multiplication<T>(-1, 0, bR, bI);
								T minusbR = precisionValueTo<T>(resultR), minusbI = precisionValueTo<T>(resultI);
								multiplication<T>(bR, bI, bR, bI);
								T bRquad = precisionValueTo<T>(resultR), bIquad = precisionValueTo<T>(resultI);
								multiplication<T>(1.0, 0.0, cR, cI);
								T acR = precisionValueTo<T>(resultR), acI = precisionValueTo<T>(resultI);
								multiplication<T>(2, 0, 1.0, 0.0);
								T twoaR = precisionValueTo<T>(resultR), twoaI = precisionValueTo<T>(resultI);
								multiplication<T>(4, 0, acR, acI);
								T fouracR = precisionValueTo<T>(resultR), fouracI = precisionValueTo<T>(resultI);
								subtraction<T>(bRquad, bIquad, fouracR, fouracI);
								T radicandR = precisionValueTo<T>(resultR), radicandI = precisionValueTo<T>(resultI);
								exponentiation<T>(radicandR, radicandI, 0.5, 0, 1);
								T sqrtR = precisionValueTo<T>(resultR), sqrtI = precisionValueTo<T>(resultI);
								subtraction<T>(minusbR, minusbI, sqrtR, sqrtI);
								T minusR = precisionValueTo<T>(resultR), minusI = precisionValueTo<T>(resultI);
								sum<T>(minusbR, minusbI, sqrtR, sqrtI);
								T plusR = precisionValueTo<T>(resultR), plusI = precisionValueTo<T>(resultI);
								division<T>(plusR, plusI, twoaR, twoaI);
								T x1R = precisionValueTo<T>(resultR), x1I = precisionValueTo<T>(resultI);
								division<T>(minusR, minusI, twoaR, twoaI);
								T x2R = precisionValueTo<T>(resultR), x2I = precisionValueTo<T>(resultI);
								SolutionR[ii - 1] = x1R; SolutionI[ii - 1] = x1I;
								SolutionR[ii] = x2R; SolutionI[ii] = x2I;
							}
							zz++;
						} while (zz < 100);
					}


					g = 0;
					rootIndex = 1;
					sprintf(answers, "");
					while (g < maxExponent) {
						rootR = SolutionR[g];
						rootI = SolutionI[g];
						if (isContained("\\", saveEquation) || isContained("x^", saveEquation) ||
							(equation_solver == (bool)true && isContained("x", saveEquation) &&
								isContained("x^", equation) == (bool)false)) {
							convertComplex2Exponential(rootR, rootI);
							if (abs(rootR) < 1E-4) {
								rootR = 0;
							}
							if (abs(rootI) < 1E-4) {
								rootI = 0;
							}
							if (rootR > 0 && rootI > 0) {
								sprintf(answers, "%sx%d=%s+%si\n", answers, rootIndex, respR, respI);
								sprintf(roots, "%s\\%s+%si", roots, respR, respI);
							}
							else {
								if (rootR > 0 && rootI < 0) {
									sprintf(answers, "%sx%d=%s%si\n", answers, rootIndex, respR, respI);
									sprintf(roots, "%s\\%s%si", roots, respR, respI);
								}
								else {
									if (rootR < 0 && rootI > 0) {
										sprintf(answers, "%sx%d=%s+%si\n", answers, rootIndex, respR, respI);

										sprintf(rootRExp, "%s", respR);
										replace("-", "_", rootRExp);
										sprintf(rootRExp, "%s", expressionF);
										sprintf(roots, "%s\\%s+%si", roots, rootRExp, respI);

									}
									else {
										if (rootR < 0 && rootI < 0) {
											sprintf(answers, "%sx%d=%s%si\n", answers, rootIndex, respR, respI);
											sprintf(rootRExp, "%s", respR);
											replace("-", "_", rootRExp);
											sprintf(rootRExp, "%s", expressionF);
											sprintf(roots, "%s\\%s%si", roots, rootRExp, respI);

										}
										else {
											if (rootR == 0 && rootI == 0) {
												sprintf(answers, "%sx%d=%s\n", answers, rootIndex, respR);
												sprintf(roots, "%s\\%s", roots, respR);
											}
											else {
												if (rootR == 0 && rootI != 0) {
													sprintf(answers, "%sx%d=%si\n", answers, rootIndex, respI);
													sprintf(rootIExp, "%si", respI);
													if (isContained("-", rootIExp)) {
														replace("-", "_", rootIExp);
														sprintf(rootIExp, "%s", expressionF);
													}
													sprintf(roots, "%s\\%s", roots, rootIExp);

												}
												else {
													if (rootR != 0 && rootI == 0) {
														sprintf(answers, "%sx%d=%s\n", answers, rootIndex,
															respR);
														sprintf(rootRExp, "%s", respR);
														if (isContained("-", rootRExp)) {
															replace("-", "_", rootRExp);
															sprintf(rootRExp, "%s", expressionF);
														}
														sprintf(roots, "%s\\%s", roots, rootRExp);

													}
													else {
														sprintf(answers, "%sx%d=%s+%si\n", answers, rootIndex,
															respR, respI);
														sprintf(roots, "%s\\%s+%si", roots, respR, respI);
													}
												}
											}
										}
									}
								}
							}
						}
						rootIndex++;
						g++;
						if (roots[0] == '\\') {
							int y = 1;
							for (y = 1; y < abs((int)strlen(roots)); y++) {
								roots[y - 1] = roots[y];
							}
							roots[y - 1] = '\0';
						}
						if (isContained(".000000", roots)) {
							replace(".000000", "", roots);
							sprintf(roots, "%s", expressionF);
						}
						if (isContained(".000000", answers)) {
							replace(".000000", "", answers);
							sprintf(answers, "%s", expressionF);
						}
					}


					if (isContained("__", roots)) {
						replace("__", "_", roots);
						sprintf(roots, "%s", expressionF);
					}
					if (polySimplifier == (bool)false) {
						if (isContained(".000000", answers)) {
							replace(".000000", "", answers);
							sprintf(answers, "%s", expressionF);
						}
						sprintf(expressionF, "%s", answers);
					}

					_delete(RootR, "RootR"); RootR = nullptr;
					_delete(RootI, "RootI"); RootI = nullptr;
					_delete(resultSubR, "resultSubR"); resultSubR = nullptr;
					_delete(resultSubI, "resultSubI"); resultSubI = nullptr;
					_delete(saveExpDerivateR, "saveExpDerivateR"); saveExpDerivateR = nullptr;
					_delete(saveExpDerivateI, "saveExpDerivateI"); saveExpDerivateI = nullptr;
					_delete(saveHelper, "saveHelper"); saveHelper = nullptr;
					_deleteShort(toCalcLastEle, "toCalcLastEle"); toCalcLastEle = nullptr;

					_deleteShort(toNoDivider, "toNoDivider");
					toNoDivider = nullptr;
					_deleteShort(rootRExp, "rootRExp");
					rootRExp = nullptr;
					_deleteShort(rootIExp, "rootIExp");
					rootIExp = nullptr;
					_deleteShort(LastEle, "LastEle");
					_deleteShort(value, "value");

					_deleteShort(forSummatory, "forSummatory");

					_deleteShort(forExpressionMax, "forExpressionMax");

					_deleteShort(lastFx, "lastFx");

					_deleteShort(currentFx, "currentFx");

					_deleteShort(result, "result");

					_deleteShort(result_I, "result_I");

					_deleteShort(posLastEle, "posLastEle");
				}
				else {
					if (isContained(".000000", answers)) {
						replace(".000000", "", answers);
						sprintf(answers, "%s", expressionF);
					}
					sprintf(expressionF, "%s", answers);
					_delete(SolutionR, "SolutionR");
					SolutionR = nullptr;
					_delete(SolutionI, "SolutionI");
					SolutionI = nullptr;

					_delete(saveExpressionCoefR, "saveExpressionCoefR");
					saveExpressionCoefR = nullptr;
					_delete(saveExpressionCoefI, "saveExpressionCoefI");
					saveExpressionCoefI = nullptr;

					_deleteShort(toCalcX, "toCalcX");
					_deleteShort(toReplace, "toReplace"); toReplace = nullptr;
					toCalcX = nullptr;
					_deleteShort(saveToCalcX, "saveToCalcX");
					saveToCalcX = nullptr;
					_deleteShort(originalEquation, "originalEquation");
					originalEquation = nullptr;

					_delete(SolutionR, "SolutionR");
					SolutionR = nullptr;
					_delete(SolutionI, "SolutionI");
					SolutionI = nullptr;

					_delete(saveExpressionCoefR, "saveExpressionCoefR");
					saveExpressionCoefR = nullptr;
					_delete(saveExpressionCoefI, "saveExpressionCoefI");
					saveExpressionCoefI = nullptr;

					_deleteShort(toCalcX, "toCalcX");
					toCalcX = nullptr;
					_deleteShort(saveToCalcX, "saveToCalcX");
					saveToCalcX = nullptr;
					_deleteShort(expression, "expression"); expression = nullptr;
					_deleteShort(saveToZeroDiv, "saveToZeroDiv"); saveToZeroDiv = nullptr;
					_deleteShort(rootRExp, "rootRExp");
					rootRExp = nullptr;
					_deleteShort(rootIExp, "rootIExp");
					rootIExp = nullptr;
					if (divider != nullptr) {
						_deleteShort(divider, "divider");
						divider = nullptr;
					}
					_deleteShort(exponent, "exponent");
					exponent = nullptr;
					_deleteShort(newEquation, "newEquation");
					_deleteShort(maxExpX, "maxExpX");
					_deleteShort(valueF, "valueF"); valueF = nullptr;
					_deleteShort(ValueR, "ValueR");
					ValueR = nullptr;
					_deleteShort(ValueI, "ValueI");
					ValueI = nullptr;
					_deleteShort(toCalcLastEle, "toCalcLastEle");
					_delete(saveHelper, "saveHelper");
					_deleteShort(toNoDivider, "toNoDivider");
					_deleteShort(saveEquation, "saveEquation");
					_deleteShort(newExpre, "newExpre");
					_deleteShort(helpExtract, "helpExtract");
					_delete(expressionCoefR, "expressionCoefR");
					_delete(expressionCoefI, "expressionCoefI");
					return precisionValueTo<T>(resultR);
				}
				_deleteShort(saveHelper, "saveHelper"); saveHelper = nullptr;
				_deleteShort(toCalcLastEle, "toCalcLastEle"); toCalcLastEle = nullptr;
				_deleteShort(newExpre, "newExpre");
				newExpre = nullptr;

				_deleteShort(toNoDivider, "toNoDivider");
				toNoDivider = nullptr;
				_deleteShort(rootRExp, "rootRExp");
				rootRExp = nullptr;
				_deleteShort(rootIExp, "rootIExp");
				rootIExp = nullptr;
				_deleteShort(LastEle, "LastEle");
				_deleteShort(value, "value");

				_deleteShort(forSummatory, "forSummatory");

				_deleteShort(forExpressionMax, "forExpressionMax");

				_deleteShort(lastFx, "lastFx");

				_deleteShort(currentFx, "currentFx");

				_deleteShort(result, "result");

				_deleteShort(result_I, "result_I");

				_deleteShort(posLastEle, "posLastEle");


			}
			else {
				solving = true;
				equationSolverRunning = false;
				removeDuplPars(saveToZeroDiv);
				sprintf(saveToZeroDiv, "%s", expressionF);
				if (isContained("(-", saveToZeroDiv)) {
					replace("(-", "(_", saveToZeroDiv);
					sprintf(saveToZeroDiv, "%s", expressionF);
				}
				if (isContained("+-", saveToZeroDiv)) {
					replace("+-", "+_", saveToZeroDiv);
					sprintf(saveToZeroDiv, "%s", expressionF);
				}
				replaceTimes = 0;
				if (isContained("(res)", toCalcX)) {
					replace("(res)", "x", toCalcX);
					sprintf(saveToZeroDiv, "%s", expressionF);
				}
				solveMath<T>(saveToZeroDiv);
				lastDividerI = precisionValueTo<T>(resultI);
				lastDividerR = precisionValueTo<T>(resultR);

			}
		}
		_delete(SolutionR, "SolutionR");
		SolutionR = nullptr;
		_delete(SolutionI, "SolutionI");
		SolutionI = nullptr;
		if (value != nullptr) {
			_deleteShort(value, "value");
		}
		value = nullptr;
		_delete(valuesEqR, "valuesEqR"); valuesEqR = nullptr;
		_delete(valuesEqI, "valuesEqI"); valuesEqI = nullptr;
		_delete(saveExpressionCoefR, "saveExpressionCoefR");
		saveExpressionCoefR = nullptr;
		_delete(saveExpressionCoefI, "saveExpressionCoefI");
		saveExpressionCoefI = nullptr;

		if (divider != nullptr) {
			_deleteShort(divider, "divider");
			divider = nullptr;
		}
		_deleteShort(toCalcX, "toCalcX");
		_deleteShort(toReplace, "toReplace"); toReplace = nullptr;
		toCalcX = nullptr;
		_deleteShort(originalEquation, "originalEquation");
		originalEquation = nullptr;
		_deleteShort(expression, "expression"); expression = nullptr;
		_deleteShort(saveToZeroDiv, "saveToZeroDiv"); saveToZeroDiv = nullptr;
		equationSolverRunning = false;
		solving = true;
		if (divider != nullptr) {
			_deleteShort(divider, "divider");
			divider = nullptr;
		}
		_deleteShort(exponent, "exponent");
		exponent = nullptr;
		_deleteShort(newEquation, "newEquation");
		_deleteShort(maxExpX, "maxExpX");
		_deleteShort(valueF, "valueF"); valueF = nullptr;
		_deleteShort(saveToCalcX, "saveToCalcX");
		_deleteShort(ValueR, "ValueR");
		ValueR = nullptr;
		_deleteShort(ValueI, "ValueI");
		ValueI = nullptr;
		_deleteShort(toCalcLastEle, "toCalcLastEle");
		_delete(saveHelper, "saveHelper");
		_deleteShort(toNoDivider, "toNoDivider");
		_deleteShort(saveEquation, "saveEquation");
		_deleteShort(newExpre, "newExpre");
		_deleteShort(helpExtract, "helpExtract");

		_delete(expressionCoefR, "expressionCoefR");
		_delete(expressionCoefI, "expressionCoefI");
		return 0;
	}
	catch (const std::exception& e) {
		std::cerr << "Exceção C++ capturada (std::exception): " << e.what() << std::endl;
		return 1;
	}
	catch (...) {

		std::cerr << "Exceção C++ desconhecida ou não standard capturada." << std::endl;
		return 1;
	}

	return 0;
}



template<typename T>
void simpleSimplifyPolynomial<T>(char* expression) {
	isDivisible = true;
	replaceTimes = 0;
	int countLeft = countOccurrences("(", expression);
	int countRight = countOccurrences(")", expression);
	if (countRight > countLeft) {
		sprintf(expressionF, "(%s", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (countRight < countLeft) {
		sprintf(expressionF, "%s)", expression);
		sprintf(expression, "%s", expressionF);
	}
	lastDividerR = 1;
	LastDividerR = 1;
	sprintf(roots, "");
	char* expressionS = getDynamicCharArrayShort("", "expressionS");
	sprintf(expressionS, "%s", expression);
	if (isContained(")(", expressionS)) {
		replace(")(", ")*(", expressionS);
		sprintf(expressionS, "%s", expressionF);
	}
	int saveStrEnd = 0;
	int i = 0, j = 0;
	char* newExpression = getDynamicCharArrayShort("", "newExpression");
	int v = 0, vv = 0, vvv = 0, po = 0;
	char* operaTor = getDynamicCharArrayShort("", "operaTor");
	char* operators = getDynamicCharArrayShort("", "operators");
	int error = 0;
	char** polys;
	polys = new char* [DIMTWOD];
	for (int i = 0; i < DIMTWOD; ++i) {
		polys[i] = getDynamicCharArrayShort("", "polys[i]");
	}
	while (v < abs((int)strlen(expressionS))) {
		sprintf(operaTor, "%c%c%c", expressionS[v], expressionS[v + 1], expressionS[v + 2]);

		if (expressionS[v] == '(' && expressionS[v + 1] == '/') {
			v = v + 2;
			error = 1;
		}
		if (expressionS[v] == ')' && expressionS[v + 1] == ')' && error == 1) {
			v++;
			error = 0;
		}
		polys[vv][po] = expressionS[v];
		po++;

		if (isEqual(")+(", operaTor)) {
			operators[vv] = '+';
			polys[vv][po] = '\0';
			vv++;
			v++;
			po = 0;
		}
		if (isEqual(")*(", operaTor)) {
			operators[vv] = '*';
			polys[vv][po] = '\0';
			vv++;
			v++;
			po = 0;
		}
		if (isEqual(")/(", operaTor)) {
			operators[vv] = '/';
			polys[vv][po] = '\0';
			vv++;
			v++;
			po = 0;
		}
		if (isEqual(")-(", operaTor)) {
			operators[vv] = '-';
			polys[vv][po] = '\0';
			vv++;
			v++;
			po = 0;
		}
		v++;
		vvv++;
	}
	polys[vv][po] = '\0';
	if (vv == 0) {
		sprintf(expressionF, "%s", expressionS);
	}
	else {
		char* polyN = getDynamicCharArrayShort("", "polyN");
		int m = 0, n = 0;
		for (n = 0; n <= vv; n++) {
			for (m = 0; m < abs((int)strlen(polys[n])); m++) {
				sprintf(polyN, "%s%c", polyN, polys[n][m]);
			}
			sprintf(polyN, "");
		}
		operators[vv] = '\0';
		replaceTimes = 0;

		int g = 0;
		int so = 0;
		char* poly_1 = getDynamicCharArrayShort("", "poly_1"); char* poly_2 = getDynamicCharArrayShort("", "poly_2");
		for (so = 0; so < vv; so++) {
			int sa = so;
			while (operators[so] == '/') {
				g = 0;
				while (g < abs((int)strlen(polys[sa]))) {
					poly_1[g] = polys[sa][g];
					g++;
				}
				poly_1[g] = '\0';
				g = 0;
				while (g < abs((int)strlen(polys[so + 1]))) {
					poly_2[g] = polys[so + 1][g];
					g++;
				}
				poly_2[g] = '\0';
				div_polynomial<T>(poly_1, poly_2);
				sprintf(poly_1, "%s", expressionF);
				sprintf(poly_2, "%s", "(0x^1+1)");
				g = 0;
				while (g < abs((int)strlen(poly_1))) {
					polys[sa][g] = poly_1[g];
					g++;
				}
				polys[sa][g] = '\0';
				g = 0;
				while (g < abs((int)strlen(poly_2))) {
					polys[so + 1][g] = poly_2[g];
					g++;
				}
				polys[so + 1][g] = '\0';
				operators[so] = '*';
				so++;
			}
		}
		operators[so] = '\0';
		for (so = 0; so < vv; so++) {
			int sa = so;
			while (operators[so] == '*') {
				g = 0;
				while (g < abs((int)strlen(polys[sa]))) {
					poly_1[g] = polys[sa][g];
					g++;
				}
				poly_1[g] = '\0';
				g = 0;
				while (g < abs((int)strlen(polys[so + 1]))) {
					poly_2[g] = polys[so + 1][g];
					g++;
				}
				poly_2[g] = '\0';
				multi_polynomial<T>(poly_1, poly_2);
				sprintf(poly_1, "%s", expressionF);
				sprintf(poly_2, "%s", "(0x^1+1)");

				g = 0;
				while (g < abs((int)strlen(poly_1))) {
					polys[sa][g] = poly_1[g];
					g++;
				}
				polys[sa][g] = '\0';
				g = 0;
				while (g < abs((int)strlen(poly_2))) {
					polys[so + 1][g] = poly_2[g];
					g++;
				}
				polys[so + 1][g] = '\0';
				operators[so] = '*';
				so++;
			}
		}

		int h = 0;
		for (h = 0; h < vv; h++) {
			if (h == 0) {
				g = 0;
				while (g < abs((int)strlen(polys[h]))) {
					poly_1[g] = polys[h][g];
					g++;
				}
				poly_1[g] = '\0';
			}
			if (operators[h] == '*') {
				g = 0;
				while (g < abs((int)strlen(polys[h + 1]))) {
					poly_2[g] = polys[h + 1][g];
					g++;
				}
				poly_2[g] = '\0';
				multi_polynomial<T>(poly_1, poly_2);
				sprintf(poly_1, "%s", expressionF);
			}
			if (operators[h] == '/') {
				g = 0;
				while (g < abs((int)strlen(polys[h + 1]))) {
					poly_2[g] = polys[h + 1][g];
					g++;
				}
				poly_2[g] = '\0';
				div_polynomial<T>(poly_1, poly_2);
				sprintf(poly_1, "%s", expressionF);
			}
			if (operators[h] == '-') {
				g = 0;
				while (g < abs((int)strlen(polys[h + 1]))) {
					poly_2[g] = polys[h + 1][g];
					g++;
				}
				poly_2[g] = '\0';
				sub_polynomial<T>(poly_1, poly_2);
				sprintf(poly_1, "%s", expressionF);
			}
			if (operators[h] == '+') {
				g = 0;
				while (g < abs((int)strlen(polys[h + 1]))) {
					poly_2[g] = polys[h + 1][g];
					g++;
				}
				poly_2[g] = '\0';
				sum_polynomial<T>(poly_1, poly_2);
				sprintf(poly_1, "%s", expressionF);
			}
		}
		removeDuplPars(poly_1);
		sprintf(poly_1, "%s", expressionF);
		sprintf(expressionF, "(%s)", poly_1);
		if (isContained(".000000", expressionF)) {
			replace(".000000", "", expressionF);
		}

		_deleteShort(polyN, "polyN");
		polyN = nullptr;
		_deleteShort(poly_1, "poly_1");
		poly_1 = nullptr;
		_deleteShort(poly_2, "poly_2");
		poly_2 = nullptr;
	}

	_Delete(polys, DIMTWOD, dime, "polys[i]");
	polys = nullptr;
	_deleteShort(expressionS, "expressionS");
	expressionS = nullptr;
	_deleteShort(newExpression, "newExpression");
	newExpression = nullptr;
	_deleteShort(operaTor, "operaTor");
	operaTor = nullptr;
	_deleteShort(operators, "operators");
	operators = nullptr;
}
template<typename T>
void simplifyPolynomial(char* expression) {
	char** parentNum;
	parentNum = new char* [DIMTWOD];
	for (int i = 0; i < DIMTWOD; ++i) {
		parentNum[i] = getDynamicCharArrayShort("", "parentNum[i]");
	}
	if (isContained(")+0", expression) && expression[strEnd] == '\0') {
		expression[strStart + 1] = '\0';
	}
	if (!isContained("((", expression) && !isContained("))", expression)) {
		simpleSimplifyPolynomial<T>(expression);
	}
	else {
		replaceTimes = 0;
		int parL = countOccurrences("(", expression);
		int parR = countOccurrences(")", expression);
		if (parL == 1 && parR == 1 && !isContained("[", expression)) {
			replace("(", "", expression);
			replace(")", "", expressionF);
			sprintf(expression, "%s", expressionF);
		}
		isDivisible = true;
		sprintf(roots, "");
		char* expressionS = getDynamicCharArrayShort("", "expressionS");
		sprintf(expressionS, "%s", expression);
		int i = 0, j = 0;
		replaceTimes = 0;
		if (isContained(")(", expressionS)) {
			replace(")(", ")*(", expressionS);
			sprintf(expressionS, "%s", expressionF);
		}
		int* parent = getDynamicIntArray();
		for (int y = 0; y < DIM; y++) {
			parent[y] = 0;
		}
		int s = 0;
		for (s = 0; s < abs((int)strlen(expressionS)); s++) {
			parent[s] = 0;
		}
		getNumerationPol(expressionS);
		int maxPar = 0;
		for (s = 0; s < abs((int)strlen(expressionS)); s++) {
			parent[s] = parentPol[s];
			if (parent[s] > maxPar) {
				maxPar = parent[s];
			}
		}
		int countMax = 0;
		for (s = 0; s < abs((int)strlen(expressionS)); s++) {
			parent[s] = parentPol[s];
			if (parent[s] == maxPar) {
				countMax++;
			}
		}
		int y = 0, u = 0, d = 0;
		char* splitPoly = getDynamicCharArrayShort("", "splitPoly");
		char* operators = getDynamicCharArrayShort("", "operators");
		char* getSimpleExpression = getDynamicCharArrayShort("", "getSimpleExpression");
		char* getRestExpression = getDynamicCharArrayShort("", "getRestExpression");

		int* type = getDynamicIntArray();
		for (int y = 0; y < DIM; y++) {
			type[y] = 0;
		}
		if (maxPar > 0) {
			if (parent[0] == 0) {
				y = 0;
				while (parent[y] == 0 && y < abs((int)strlen(expressionS))) {
					getSimpleExpression[y] = expressionS[y];
					y++;
				}
				y--;
				getSimpleExpression[y] = '\0';
				int c = 0;
				while (y < (int)abs((int)strlen(expressionS))) {
					getRestExpression[c] = expressionS[y];
					c++;
					y++;
				}
				getRestExpression[c] = '\0';
				sprintf(expressionF, "((%s)*(0x^1+1))%s", getSimpleExpression, getRestExpression);
				sprintf(expressionS, "%s", expressionF);
				getNumerationPol(expressionS);
				maxPar = 0;
				for (s = 0; s < abs((int)strlen(expressionS)); s++) {
					parent[s] = parentPol[s];
					if (parent[s] > maxPar) {
						maxPar = parent[s];
					}
				}
			}
			if (parent[abs((int)strlen(expressionS)) - 1] == 0) {
				int c = 0;
				y = (int)abs((int)strlen(expressionS)) - 1;
				while (parent[y] == 0) {
					y--;
				}
				y = y + 2;
				int d = y;
				c = 0;
				while (parent[y] == 0 && y < abs((int)strlen(expressionS))) {
					getSimpleExpression[c] = expressionS[y];
					c++;
					y++;
				}
				getSimpleExpression[c] = '\0';
				c = 0;
				y = 0;
				while (y < d) {
					getRestExpression[c] = expressionS[y];
					c++;
					y++;
				}
				getRestExpression[c] = '\0';
				sprintf(expressionF, "%s(%s*(0x^1+1))", getRestExpression, getSimpleExpression);
				sprintf(expressionS, "%s", expressionF);
				getNumerationPol(expressionS);
				maxPar = 0;
				for (s = 0; s < abs((int)strlen(expressionS)); s++) {
					parent[s] = parentPol[s];
					if (parent[s] > maxPar) {
						maxPar = parent[s];
					}
				}
			}
			y = 0;
			while (y < abs((int)strlen(expressionS))) {
				if (parent[y] == 0) {
					d = 0;
					while (parent[y] == 0) {
						parentNum[u][d] = expressionS[y];
						y++;
						d++;
					}
					if ((expressionS[y - 1] == '+' || expressionS[y - 1] == '-' ||
						expressionS[y - 1] == '*' || expressionS[y - 1] == '/') && expressionS[y] == '(') {
						operators[u] = expressionS[y - 1];
						y--;
						d--;
					}
					parentNum[u][d] = '\0';
					for (d = 0; d < abs((int)strlen(parentNum[u])); d++) {
						sprintf(splitPoly, "%s%c", splitPoly, parentNum[u][d]);
					}
					sprintf(splitPoly, "%s\n%c", splitPoly, operators[u]);
					type[u] = 0;
					u++;
				}
				else {
					d = 0;
					int h = parent[y];
					y++;
					while (parent[y] != h && y < abs((int)strlen(expressionS))) {
						parentNum[u][d] = expressionS[y];
						y++;
						d++;
					}
					if ((expressionS[y + 1] == '+' || expressionS[y + 1] == '-' ||
						expressionS[y + 1] == '*' || expressionS[y + 1] == '/') && expressionS[y] == ')') {
						operators[u] = expressionS[y + 1];
						y++;
					}
					parentNum[u][d] = '\0';
					for (d = 0; d < abs((int)strlen(parentNum[u])); d++) {
						sprintf(splitPoly, "%s%c", splitPoly, parentNum[u][d]);
					}
					sprintf(splitPoly, "%s\n", splitPoly);
					type[u] = 1;
					u++;
				}
				y++;
			}
			_deleteShort(expressionS, "expressionS");
			expressionS = nullptr;
			char* expr = getDynamicCharArrayShort("", "expr");
			y = 0;
			int* size = getDynamicArray<int>(DIMDOUBLE);
			for (int y = 0; y < DIMDOUBLE; y++) {
				size[y] = 0;
			}
			while (y < u) {
				d = 0;
				while (d < abs((int)strlen(parentNum[y]))) {
					expr[d] = parentNum[y][d];
					d++;
				}
				expr[d] = '\0';
				if (type[y] == 1) {
					simplifyPolynomial<T>(expr);
					size[y] = (int)abs((int)strlen(expressionF));
				}
				else {
					simpleSimplifyPolynomial<T>(expr);
					size[y] = (int)abs((int)strlen(expressionF));
				}
				d = 0;
				while (d < abs((int)strlen(expressionF))) {
					parentNum[y][d] = expressionF[d];
					d++;
				}
				parentNum[y][d] = '\0';
				y++;
			}
			y = 0;
			d = 0;
			int p = 0;
			char* newExpression = getDynamicCharArrayShort("", "newExpression");
			while (y < u) {
				d = 0;
				if (!(parentNum[y][d] == '(' && parentNum[y][d + 1] == '(')) {
					newExpression[p] = '(';
					p++;
				}
				while (d < size[y]) {
					newExpression[p] = parentNum[y][d];
					d++;
					p++;
				}
				if (!(parentNum[y][d - 1] == ')' && parentNum[y][d - 2] == ')')) {
					newExpression[p] = ')';
					p++;
				}
				if (operators[y] == '+' || operators[y] == '-' ||
					operators[y] == '*' || operators[y] == '/') {
					newExpression[p] = operators[y];
					p++;
				}
				y++;
			}
			newExpression[p] = '\0';
			simpleSimplifyPolynomial<T>(newExpression);
			_deleteShort(expr, "expr");
			expr = nullptr;
			_deleteShort(newExpression, "newExpression");
			newExpression = nullptr;
			_delete(size, "size"); size = nullptr;
			size = nullptr;
		}
		else {
			simpleSimplifyPolynomial<T>(expression);
		}
		if (!isDivisible) {
			sprintf(expressionF, "%s", saveExpressionF);
		}
		if (isContained(".000000", expressionF)) {
			replace(".000000", "", expressionF);
		}
		_deleteShort(expressionS, "expressionS");
		expressionS = nullptr;
		_deleteShort(splitPoly, "splitPoly");
		splitPoly = nullptr;
		_deleteShort(operators, "operators");
		operators = nullptr;
		_deleteShort(getSimpleExpression, "getSimpleExpression");
		getSimpleExpression = nullptr;
		_deleteShort(getRestExpression, "getRestExpression");
		getRestExpression = nullptr;
		_delete(parent, "parent");
		_delete(type, "type");
	}



	_Delete(parentNum, DIMTWOD, dime, "parentNum[i]");
	parentNum = nullptr;
}

void getNumerationPol(char* expressionS) {
	int* parent = getDynamicIntArray();
	int s = 0, c, d, k, l, h;
	for (s = 0; s < abs((int)strlen(expressionS)); s++) {
		parent[s] = 0;
	}
	int cp = 0, mark = 0;
	c = 0;
	d = 0;
	k = 0;
	l = 0;
	h = 0;
	for (s = 0; s < abs((int)strlen(expressionS)); s++) {
		if (expressionS[s] == '(' && expressionS[s + 1] == '(') {
			d = 0;
			c++;
			parent[s] = c;
			d = 1;
			k = c;
		}
		else {
			if (expressionS[s] == ')' && expressionS[s - 1] == ')') {
				d = 0;
				h = 0;
				l = 2;
				do {
					l = 0;
					h = 0;
					while (h < abs((int)strlen(expressionS))) {
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
				while (l != 1 && h < abs((int)strlen(expressionS))) {
					h = 0;
					l = 0;
					while (h < abs((int)strlen(expressionS))) {
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
			else {
				parent[s] = 0;
			}
		}
	}

	char* pare = getDynamicCharArrayShort("", "pare"); char* pareF = getDynamicCharArrayShort("", "pareF");
	for (s = 0; s < abs((int)strlen(expressionS)); s++) {
		parentPol[s] = parent[s];
		sprintf(pareF, "%s%d", pare, parent[s]);
		sprintf(pare, "%s", pareF);
	}
	_deleteShort(pare, "pare");
	pare = nullptr;
	_deleteShort(pareF, "pareF");
	pareF = nullptr;
	_delete( parent, "parent"); parent = nullptr;
}
template <typename T>
int getCorrectExponent(char* expression, char* maxExp, int maxExponent) {
	replaceTimes = 0;
	char* saveToCalcX = getDynamicCharArrayShort("", "saveToCalcX");
	sprintf(saveToCalcX, "%s", expression);
	char* to_replace = getDynamicCharArrayShort("", "to_replace");
	char* replacement = getDynamicCharArrayShort("", "replacement");
	char* saveEquationF = getDynamicCharArrayShort("", "saveEquationF");
	do {
		sprintf(saveToCalcX, "%s", expression);

		sprintf(expressionF, "(res)^%d", maxExponent);
		sprintf(to_replace, "%s", expressionF);
		if (!isContained(to_replace, saveToCalcX)) {
			while (!isContained(to_replace, saveToCalcX)) {
				maxExponent--;
				sprintf(expressionF, "(res)^%d", maxExponent);
				sprintf(to_replace, "%s", expressionF);
			}
		}
		sprintf(expressionF, "(aaaa)^%d", maxExponent);
		sprintf(replacement, "%s", expressionF);
		if (isContained(to_replace, saveToCalcX)) {
			replace(to_replace, replacement, saveToCalcX);
			if (isContained("res", expressionF)) {
				replace("res", "0", expressionF);
				sprintf(saveToCalcX, "%s", expressionF);
			}
			else {
				sprintf(saveToCalcX, "%s", expressionF);
			}
		}

		sprintf(saveEquationF, "%s", saveToCalcX);
		if (isContained("aaaa", saveToCalcX)) {
			replace("aaaa", "0", saveToCalcX);
			sprintf(saveToCalcX, "%s", expressionF);
		}
		solveMath<T>(saveToCalcX);
		sprintf(saveToCalcX, "%s", saveEquationF);
		lastElement = precisionValueTo<T>(resultR), lastElementI = precisionValueTo<T>(resultI);
		if (isContained("aaaa", saveToCalcX)) {
			replace("aaaa", "1", saveToCalcX);
			sprintf(saveToCalcX, "%s", expressionF);
		}
		solveMath<T>(saveToCalcX);
		subtraction<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), precisionValueTo<T>(lastElement), precisionValueTo<T>(lastElementI));
		lastDividerR = precisionValueTo<T>(resultR); lastDividerI = precisionValueTo<T>(resultI);

		if (lastDividerR == 0 && lastDividerI == 0 && maxExponent > 1) {
			maxExponent--;
		}
		else {
			_deleteShort(saveToCalcX, "saveToCalcX");
			saveToCalcX = nullptr;
			_deleteShort(to_replace, "to_replace");
			to_replace = nullptr;
			_deleteShort(replacement, "replacement");
			replacement = nullptr;
			_deleteShort(saveEquationF, "saveEquationF");

			saveEquationF = nullptr;

			return maxExponent;
		}
	} while (lastDividerR == 0 && lastDividerI == 0 && maxExponent >= 1);
	_deleteShort(saveToCalcX, "saveToCalcX");
	saveToCalcX = nullptr;
	_deleteShort(to_replace, "to_replace");
	to_replace = nullptr;
	_deleteShort(replacement, "replacement");
	replacement = nullptr;
	_deleteShort(saveEquationF, "saveEquationF");
	saveEquationF = nullptr;

	return maxExponent;
}


template<typename T>
void simplifyExpression(char* data) {
	bool toSimplify = true;
	char* expression = getDynamicCharArrayShort("", "expression");
	sprintf(expression, "");
	sprintf(expression, "%s", data);
	isDivisible = true;
	sprintf(expressionF, "");
	sprintf(roots, "");
	sprintf(answers, "");
	replaceTimes = 0;
	if (isEqual("x", expression)) {
		replace("x", "(X-0)", expression);
		sprintf(expression, "%s", expressionF);
		replace("X", "x", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("*1i", expression)) {
		replace("*1i", "i", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("-x", expression)) {
		replace("-x", "+_1x", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("+x", expression)) {
		replace("+x", "+1x", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("(x)", expression)) {
		replace("(x)", "X", expression);
		replace("X", "x", expressionF);
		sprintf(expression, "%s", expressionF);
	}
	replaceTimes = 0;
	if (isContained(")-(", expression)) {
		replace(")-(", ")+_1*(", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("(-", expression)) {
		replace("(-", "(_", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("-", expression)) {
		replace("-", "+_", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained(")_(", expression)) {
		replace(")_(", ")-(", expression);
		sprintf(expression, "%s", expressionF);
	}
	replaceTimes = 0;
	if (isContained("*x", expression)) {
		replace("*x", "x", expression);
		sprintf(expression, "%s", expressionF);
	}
	replaceTimes = 1;
	while (isContained("x", expression)) {
		if (isContained("x", expression) && expression[strEnd] != '^') {
			replace("x", "X^1", expression);
			sprintf(expression, "%s", expressionF);
		}
		else {
			expression[strStart] = 'X';
		}
	}
	replaceTimes = 0;
	if (isContained("X", expression)) {
		replace("X", "x", expression);
		sprintf(expression, "%s", expressionF);
	}
	bool hasSimpleDivisions = false;
	char* collectChars = getDynamicCharArrayShort("", "collectChars");
	char* replacement = getDynamicCharArrayShort("", "replacement");
	char* addPars = getDynamicCharArrayShort("", "addPars");
	char* saveNum = getDynamicCharArrayShort("", "saveNum");
	char* number = getDynamicCharArrayShort("", "number");
	char* toReplace = getDynamicCharArrayShort("", "toReplace");
	char* getExp = getDynamicCharArrayShort("", "getExp");
	char* poly = getDynamicCharArrayShort("", "poly");
	char* polyNum = getDynamicCharArrayShort("", "polyNum");
	char* alphabet = getDynamicCharArrayShort("", "alphabet");
	char** saveConversions;
	char* num = getDynamicCharArrayShort("", "num");
	char* new_expression = getDynamicCharArrayShort("", "new_expression");
	char* expr = getDynamicCharArrayShort("", "expr");
	char* saveExpr = getDynamicCharArrayShort("", "saveExpr");
	char* extractText = getDynamicCharArrayShort("", "extractText");
	char* simplify = getDynamicCharArrayShort("", "simplify");
	char* simplified = getDynamicCharArrayShort("", "simplified");
	char* saveSimplify = getDynamicCharArrayShort("", "saveSimplify");
	saveConversions = new char* [DIMTWOD];
	char* den = getDynamicCharArrayShort("", "den");
	char* saveDen = getDynamicCharArrayShort("", "saveDen");
	char* value = getDynamicCharArrayShort("", "value");
	char* expressioN = getDynamicCharArrayShort("", "expressioN");
	char* dataBeforeX = getDynamicCharArrayShort("", "dataBeforeX");
	char* saveDataBeforeX = getDynamicCharArrayShort("", "saveDataBeforeX");
	char* numbersData = getDynamicCharArrayShort("", "numbersData");
	char* smallText = getDynamicCharArrayShort("", "smallText");
	char* pieceExpre = getDynamicCharArrayShort("", "pieceExpre");
	char* newNumber = getDynamicCharArrayShort("", "newNumber");
	char* saveNumber = getDynamicCharArrayShort("", "saveNumber");
	char* greatDenominator = getDynamicCharArrayShort("", "greatDenominator");
	char* saveExpressionSS = getDynamicCharArrayShort("", "saveExpressionSS");
	char* expressionToSimplify = getDynamicCharArrayShort("", "expressionToSimplify");
	char* expressionSimplified = getDynamicCharArrayShort("", "expressionSimplified");
	char** saveCharResult;
	saveCharResult = new char* [DIMTWOD];
	for (int i = 0; i < DIMTWOD; ++i) {
		saveCharResult[i] = getDynamicCharArrayShort("", "saveCharResult[i]");
	}
	for (int i = 0; i < DIMTWOD; ++i) {
		saveConversions[i] = getDynamicCharArrayShort("", "saveConversions[i]");
	}

	char** numerator, ** denominator;
	numerator = new char* [DIMTWOD];

	for (int i = 0; i < DIMTWOD; ++i) {
		numerator[i] = getDynamicCharArrayShort("", "numerator[i]");
	}
	denominator = new char* [DIMTWOD];

	for (int i = 0; i < DIMTWOD; ++i) {
		denominator[i] = getDynamicCharArrayShort("", "denominator[i]");
	}

	char* intermediate = getDynamicCharArrayShort("", "intermediate");
	char* equa = getDynamicCharArrayShort("", "equa");
	char* newEquation = getDynamicCharArrayShort("", "newEquation");
	char* equaSimplified = getDynamicCharArrayShort("", "equaSimplified");

	if ((isContained("/", expression)) && studyFunction == false) {
		if (!isContained("/x", expression) && isContained("/", expression)) {
			int i = 0;
			for (i = 0; i < abs((int)strlen(expression)); i++) {
				if (expression[i] == '(') {
					int y = 0;
					bool hasOperators = false;
					while ((verifyNumber(expression[i]) || (expression[i] == '/' && expression[i + 1] != 'x') || expression[i] == '*' || expression[i] == '^' || expression[i] == '+' || expression[i] == '(' || expression[i] == ')' || expression[i] == 'i') && i < abs((int)strlen(expression))) {
						collectChars[y] = expression[i];
						if (expression[i] == '/' || expression[i] == '*' || expression[i] == '^') {
							hasOperators = true;
						}
						y++, i++;
					}
					collectChars[y] = '\0';


					if (abs((int)(abs((int)strlen(collectChars)))) > 0 && hasOperators) {
						solveMath<T>(collectChars);
						sprintf(replacement, "%G+%Gi", precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
						replaceTimes = 0;
						if (isContained("-", replacement)) {
							replace("-", "_", replacement);
							sprintf(replacement, "%s", expressionF);
						}
						replaceTimes = 1;
						replace(collectChars, replacement, expression);
						sprintf(expression, "%s", expressionF);
						i = 0;

					}

				}
			}
		}
		if (isContained("/", expression)) {

			sprintf(addPars, "");
			int y = 0, w = 0;
			bool division = false;
			while (y < abs((int)strlen(expression))) {
				if (expression[y] == '(') {
					addPars[w] = expression[y]; w++, y++;
					while (expression[y] != ')') {
						addPars[w] = expression[y];
						w++; y++;
					}
				}
				if (verifyForNumbers(expression[y])) {
					if (expression[y - 1] == '/') {
						division = true;
					}
					else {
						division = false;
					}
					addPars[w] = '('; w++;
					while (verifyForNumbers(expression[y])) {
						addPars[w] = expression[y];
						w++; y++;
					}
					addPars[w] = ')'; w++;

					if ((expression[y] == '+' || y == abs((int)strlen(expression)) || expression[y] == ')') && !division) {

						addPars[w] = '/'; w++;
						addPars[w] = '('; w++;
						addPars[w] = '1'; w++;
						addPars[w] = ')'; w++;
					}
					addPars[w] = expression[y];
					w++;
				}
				else {
					addPars[w] = expression[y];
					division = false;
					w++;
				}
				y++;
			}
			sprintf(expression, "%s", addPars);

			if (verifyNumber(expression[abs((int)strlen(expression)) - 1]) || expression[abs((int)strlen(expression)) - 1] == 'x') {
				int u = abs((int)strlen(expression)) - 1;
				while (u > 0 && verifyNumber(expression[u])) {
					u--;
				}
				if (expression[u] == '+') {
					sprintf(expression, "%s/1", expression);
				}
			}
			for (int h = 0; h < abs((int)strlen(expression)); h++) {
				if (verifyForNumber(expression[h]) && (h == 0 || expression[h - 1] == '+')) {
					sprintf(saveNum, "");
					int k = 0;
					if (expression[h - 1] == '+') {
						saveNum[k] = '+'; k++;
					}
					while (verifyForNumber(expression[h]) && expression[h] != '+' && expression[h] != '/' && h < abs((int)strlen(expression))) {
						saveNum[k] = expression[h];
						k++; h++;
					}
					saveNum[k] = '\0';
					char nextChar = expression[h];
					if (expression[h] == '+' || (h == abs((int)strlen(expression)) && saveNum[0] == '+')) {
						sprintf(replacement, "");
						sprintf(replacement, "%s/1%c", saveNum, nextChar);
						replaceTimes = 1;
						sprintf(saveNum, "%s%c", saveNum, nextChar);
						replace(saveNum, replacement, expression);
						sprintf(expression, "%s", expressionF);

					}
					if (expression[h] == '/' && verifyNumber(expression[h + 1])) {
						h++;
						while (verifyNumber(expression[h]) && h < abs((int)strlen(expression))) {
							h++;
						}
					}

				}
			}
		}
	}
	replaceTimes = 0;
	if (isContained(")D(", expression)) {
		replace(")D(", ")/(", expression);
		sprintf(expression, "%s", expressionF);
	}

	if (isContained("/x+", expression) && studyFunction == (bool)false) {
		replace("/x+", "/(x+0)+", expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("/x", expression) && strEnd == abs((int)strlen(expression)) && studyFunction == (bool)false) {
		replace("/x", "/(x+0)", expression);
		sprintf(expression, "%s", expressionF);
	}
	replaceTimes = 1;
	while (isContained("/", expression) && studyFunction == (bool)false) {
		if (isContained("/", expression) && strStart > 0 && verifyNumber(expression[strStart - 1])) {
			int y = strStart - 1;
			while (y > 0 && verifyNumber(expression[y])) {
				y--;
			}
			if (y == 0 || expression[y] == '+' || expression[y] == '*') {
				int w = 0;
				if (y > 0) {
					y++;
				}
				while (verifyNumber(expression[y])) {
					number[w] = expression[y];
					w++; y++;
				}
				number[w] = '\0';
				sprintf(replacement, "");
				sprintf(toReplace, "");
				sprintf(toReplace, "%s/", number);
				sprintf(replacement, "(0x+%s)D", number);
				replace(toReplace, replacement, expression);
				sprintf(expression, "%s", expressionF);

			}
			else {
				if (isContained("/", expression)) {
					expression[strStart] = 'D';
				}
			}
		}
		else {
			if (isContained("/", expression)) {
				expression[strStart] = 'D';
			}
		}
	}
	replaceTimes = 0;
	if (isContained("D", expression)) {
		replace("D", "/", expression);
		sprintf(expression, "%s", expressionF);
	}
	replaceTimes = 1;
	while (isContained("/", expression) && studyFunction == (bool)false) {
		if (isContained("/", expression) && verifyNumber(expression[strStart + 1])) {
			int y = strStart + 1;
			int w = 0;
			sprintf(number, "");
			while (verifyNumber(expression[y])) {
				number[w] = expression[y];
				w++; y++;
			}
			number[w] = '\0';
			sprintf(replacement, "");
			sprintf(toReplace, "");
			sprintf(toReplace, "/%s", number);
			sprintf(replacement, "/(0x+%s)", number);
			replace(toReplace, replacement, expression);
			sprintf(expression, "%s", expressionF);

		}
		else {
			if (isContained("/", expression)) {
				expression[strStart] = 'D';
			}
		}
	}
	replaceTimes = 0;
	if (isContained("D", expression)) {
		replace("D", "/", expression);
		sprintf(expression, "%s", expressionF);
	}

	if (isContained("M", expression)) {
		replace("M", "*", expression);
		sprintf(expression, "%s", expressionF);
	}

	if (!isContained("/x", expression) && !isContained("x/", expression) && studyFunction == (bool)false) {
		sprintf(expression, "%s+0", expression);
	}
	if (isContained("))/(", expression) && toSimplify == (bool)true) {
		sprintf(expressionF, "%s", expression);
		simplifyPolynomial<T>(expressionF);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("/", expression) && studyFunction == (bool)false && toSimplify == (bool)true) {
		if (isContained("x", expression)) {
			replaceTimes = 1;
			while (isContained("x", expression)) {
				if (verifyNumber(expression[strStart - 1])) {
					replace("x", "*X", expression);
					sprintf(expression, "%s", expressionF);
				}
				else {
					if (expression[strStart - 1] == '/' && !(expression[strEnd] == '^')) {
						replace("x", "X", expression);
						sprintf(expression, "%s", expressionF);
					}
					else {
						if (expression[strEnd] == '^') {
							sprintf(getExp, "");
							int h = 0, m = strEnd + 1;
							while (verifyNumber(expression[m]) && m < abs((int)strlen(expression))) {
								getExp[h] = expression[m];
								h++; m++;
							}
							getExp[h] = '\0';
							sprintf(replacement, "");
							sprintf(toReplace, "");
							sprintf(replacement, "(X^%sS0)", getExp);
							sprintf(toReplace, "x^%s", getExp);
							replace(toReplace, replacement, expression);
							sprintf(expression, "%s", expressionF);

						}
						else {
							replace("x", "X", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
				}
			}
			replaceTimes = 0;
			if (isContained("X", expression)) {
				replace("X", "x", expression);
				sprintf(expression, "%s", expressionF);
			}
		}
		replaceTimes = 0;
		if (isContained("X", expression)) {
			replace("X", "x", expression);
			sprintf(expression, "%s", expressionF);
		}
		replaceTimes = 0;
		if (isContained("X", expression)) {
			replace("X", "x", expression);
			sprintf(expression, "%s", expressionF);
		}
		replaceTimes = 1;
		if (isContained("x", expression) && strStart == 0) {
			replace("x", "1x", expression);
			sprintf(expression, "%s", expressionF);
		}
		replaceTimes = 0;
		if (isContained("_x", expression)) {
			replace("_x", "_1x", expression);
			sprintf(expression, "%s", expressionF);
		}
		if (isContained("+x", expression)) {
			replace("+x", "+1x", expression);
			sprintf(expression, "%s", expressionF);
		}
		replaceTimes = 0;
		if (isContained("_(", expression)) {
			replace("_(", "(_1)(", expression);
			sprintf(expression, "%s", expressionF);
		}
		replaceTimes = 1;
		if (isContained("/", expression) && studyFunction == (bool)false) {
			replaceTimes = 1;
			if (isContained(")/(", expression)) {
				replaceTimes = 0;
				if (isContained("+_(", expression)) {
					replaceTimes = 1;
					while (isContained("+_(", expression)) {
						sprintf(poly, "");
						int i = strEnd, h = 0;
						int kr = 0, kl = 1;
						while (kr != kl) {
							poly[h] = expression[i];
							i++; h++;
							if (expression[i] == ')') {
								kr++;
							}
							if (expression[i] == '(') {
								kl++;
							}
						}
						sprintf(polyNum, "_(%s)", poly);
						sprintf(expressionF, "(0x^1-1)*(%s)", poly);
						simplifyPolynomial<T>(expressionF);
						removeTriplPars(expressionF);
						sprintf(poly, "%s", expressionF);
						replaceTimes = 1;
						replace(polyNum, poly, expression);
						sprintf(expression, "%s", expressionF);
						replaceTimes = 0;

					}
				}
				sprintf(alphabet, "ABCDEFGHIJKLMNOPQRSTUWVXYZabcdefghijklmnopqrstuwvxyz");


				int z = 0;
				for (z = 0; z < abs((int)strlen(expression)); z++) {
					if (verifyNumerator(expression[z - 1]) && expression[z] == '/' && verifyNumerator(expression[z + 1])) {
						expression[z] = '!';
					}
				}
				z = 0;
				while (!(isContained("/", expression) && verifyNumberExpression(expression[strStart - 1]) && verifyNumberExpression(expression[strEnd]))) {
					replaceTimes = 1;
					replace("/", "!", expression);
					sprintf(expression, "%s", expressionF);
				}
				replaceTimes = 0;
				if (isContained(")/(", expression)) {
					replaceTimes = 0;
					if (isContained("*(", expression)) {
						replace("*(", "(", expression);
						sprintf(expression, "%s", expressionF);
					}
					if (isContained("(", expression)) {
						replaceTimes = 1;
						int i = 0;
						while (isContainedByIndex("(", expression, i)) {
							if (isContainedByIndex("(", expression, i) && verifyNumerator(expression[strStart - 1])) {
								while (isContainedByIndex("(", expression, i) && verifyNumerator(expression[strStart - 1])) {
									expression[strStart] = 'P';
									i = strStart - 1;
									sprintf(num, "");
									while (verifyNumerator(expression[i])) {
										i--;
									}
									i++;
									int v = i;
									int p = 0;
									while (verifyNumerator(expression[i])) {
										num[p] = expression[i];
										p++; i++;
									}
									num[p] = '\0';
									sprintf(new_expression, "");
									sprintf(new_expression, "%s", num);
									sprintf(toReplace, "");
									solveMath<T>(num);
									sprintf(num, "%f+%fi", precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
									replaceTimes = 0;
									if (isContained("-", num)) {
										replace("-", "_", num);
										sprintf(num, "%s", expressionF);
									}
									replaceTimes = 1;
									if (abs((int)strlen(num)) == 0) {
										sprintf(num, "0");
									}
									sprintf(toReplace, "(0x+%s)*", num);
									replaceTimes = 1;
									replace(new_expression, toReplace, expression);
									sprintf(expression, "%s", expressionF);
									sprintf(expr, "");
									int o = 0;
									if (isContainedByIndex("/", expression, i)) {
										int u = strStart;
										o = 0;
										while (v < u) {
											expr[o] = expression[v];
											v++; o++;
										}
										expr[o] = '\0';
										sprintf(saveExpr, "");
										sprintf(saveExpr, "%s", expr);
										if (isContained("P", expr)) {
											replace("P", "(", expr);
											sprintf(expr, "%s", expressionF);
										}
										simpleSimplifyPolynomial<T>(expr);
										replaceTimes = 0;
										if (isContained("+", expressionF)) {
											replace("+", "S", expressionF);
										}
										replaceTimes = 0;
										if (isContained("(((", expressionF)) {
											replace("(((", "((", expressionF);
										}
										if (isContained(")))", expressionF)) {
											replace(")))", "))", expressionF);
										}
										if (isContained("(", expressionF)) {
											replace("(", "P", expressionF);
										}
										replaceTimes = 1;
										replace(saveExpr, expressionF, expression);
										sprintf(expression, "%s", expressionF);
										if (isContained("(((", expression)) {
											replace("(((", "((", expression);
											sprintf(expression, "%s", expressionF);
										}
										if (isContained(")))", expression)) {
											replace(")))", "))", expression);
											sprintf(expression, "%s", expressionF);
										}
										if (isContainedByIndex("/", expression, i)) {
											expression[strStart] = 'D';
										}

									}

								}
							}
							else {
								if (expression[strStart] == '(') {
									expression[strStart] = 'P';
								}
							}
						}
						replaceTimes = 0;
						if (isContained("P", expression)) {
							replace("P", "(", expression);
							sprintf(expression, "%s", expressionF);
						}
						if (isContained("P", expression)) {
							replace("P", "(", expression);
							sprintf(expression, "%s", expressionF);
						}
						if (isContained("!", expression)) {
							replace("!", "/", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
					replaceTimes = 0;
					replaceTimes = 0;
					if (isContained(")*", expression)) {
						replace(")*", ")", expression);
						sprintf(expression, "%s", expressionF);
					}
					if (isContained(")", expression)) {
						replaceTimes = 1;
						while (isContained(")", expression)) {
							if (isContained(")", expression) && verifyNumerator(expression[strStart + 1])) {
								while (isContained(")", expression) && verifyNumerator(expression[strStart + 1])) {
									expression[strStart] = 'P';
									int i = strStart + 1;
									sprintf(num, "");
									int v = i;
									int p = 0;
									while (verifyNumerator(expression[i])) {
										num[p] = expression[i];
										p++; i++;
									}
									num[p] = '\0';
									int f = 0;
									int countDivs = countOccurrences("/", expression) + countOccurrences("D", expression);
									if (countDivs > 1) {
										while ((expression[i - 1] == 'P' && expression[i] == 'D') == false && (expression[i - 1] == 'P' && expression[i] == '/') == false && i > 0) {
											i--;
										}
										i--;
										while ((expression[i - 1] == 'P' && expression[i] == 'D') == false && (expression[i - 1] == 'P' && expression[i] == '/') == false && i > 0 && expression[i] != '+') {
											i--;
										}
										if (expression[i] == '+') {
											i++;
										}
									}
									else {
										while ((expression[i - 1] == 'P' && expression[i] == 'D') == false && (expression[i - 1] == 'P' && expression[i] == '/') == false && i > 0 && expression[i] != '+') {
											i--;
										}
										i--;
										while (i > 0) {
											i--;
										}
									}
									int l = 0;
									sprintf(extractText, "");
									while (((expression[i] == '/' || expression[i] == 'D') && expression[i + 1] == '(') == false) {
										extractText[l] = expression[i];
										i++; l++;
									}
									extractText[l] = '\0';
									replaceTimes = 0;
									if (isContained("P", extractText)) {
										replace("P", ")", extractText);
										sprintf(extractText, "%s", expressionF);
									}
									replaceTimes = 1;


									sprintf(new_expression, "");
									sprintf(new_expression, "%s", num);

									sprintf(simplify, "");

									sprintf(simplified, "");

									sprintf(toReplace, "");
									solveMath<T>(num);
									sprintf(num, "%f+%fi", precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
									if (abs((int)strlen(num)) == 0) {
										sprintf(num, "0");
									}
									replaceTimes = 0;
									if (isContained("-", num)) {
										replace("-", "_", num);
										sprintf(num, "%s", expressionF);
									}
									replaceTimes = 1;
									if (abs((int)strlen(num)) == 0) {
										sprintf(num, "0");
									}
									if (expression[i] == '/') {
										sprintf(toReplace, "%s*(0x+%s)/", extractText, num);
									}
									if (expression[i] == 'D') {
										sprintf(toReplace, "%s*(0x+%s)D", extractText, num);
									}
									sprintf(simplify, "%s*(0x+%s)", extractText, num);
									sprintf(saveSimplify, "");
									sprintf(saveSimplify, "%s", simplify);
									if (isContained("(x)", simplify)) {
										replace("(x)", "X", simplify);
										replace("X", "x", expressionF);
										sprintf(simplify, "%s", expressionF);
									}
									if (isContained("S", toReplace)) {
										replaceTimes = 0;
										replace("S", "+", toReplace);
										sprintf(toReplace, "%s", expressionF);
									}
									if (isContained("S", simplify)) {
										replaceTimes = 0;
										replace("S", "+", simplify);
										sprintf(simplify, "%s", expressionF);
									}
									simpleSimplifyPolynomial<T>(simplify);
									sprintf(simplified, "%s", expressionF);
									if (expression[i] == '/') {
										sprintf(extractText, "%s/", extractText);
									}
									if (expression[i] == 'D') {
										sprintf(extractText, "%sD", extractText);
									}
									replaceTimes = 0;
									if (isContained("P", expression)) {
										replace("P", ")", expression);
										sprintf(expression, "%s", expressionF);
									}
									replaceTimes = 1;
									replace(extractText, toReplace, expression);
									sprintf(expression, "%s", expressionF);
									replaceTimes = 0;
									if (isContained("S", saveSimplify)) {
										replaceTimes = 0;
										replace("S", "+", saveSimplify);
										sprintf(saveSimplify, "%s", expressionF);
									}
									replaceTimes = 1;
									replace(saveSimplify, simplified, expression);
									sprintf(expression, "%s", expressionF);
									if (isContained("(((", expression)) {
										replace("(((", "((", expression);
										sprintf(expression, "%s", expressionF);
									}
									if (isContained(")))", expression)) {
										replace(")))", "))", expression);
										sprintf(expression, "%s", expressionF);
									}
									replaceTimes = 0;
									if (isContained("P", toReplace)) {
										replace("P", ")", toReplace);
										sprintf(toReplace, "%s", expressionF);
									}
									replaceTimes = 1;
									sprintf(expressionF, ")%s", new_expression);
									sprintf(new_expression, "%s", expressionF);
									replace(new_expression, ")", expression);
									sprintf(expression, "%s", expressionF);

								}
								replaceTimes = 1;
							}
							else {
								if (expression[strStart] == ')') {
									expression[strStart] = 'P';
								}
							}
						}
						replaceTimes = 0;
					}
					if (isContained("P", expression)) {
						replace("P", ")", expression);
						sprintf(expression, "%s", expressionF);
					}
					replaceTimes = 0;
					if (isContained("P", expression)) {
						replace("P", ")", expression);
						sprintf(expression, "%s", expressionF);
					}
					if (isContained("D", expression)) {
						replace("D", "/", expression);
						sprintf(expression, "%s", expressionF);
					}
					if (isContained("(x)", expression)) {
						replace("(x)", "X", expression);
						replace("X", "x", expressionF);
						sprintf(expression, "%s", expressionF);
					}
					replaceTimes = 0;
					if (isContained("(x)", expression)) {
						replaceTimes = 1;
						while (isContained("(x)", expression)) {
							if (verifyNumber(expression[strStart - 1])) {
								replace("(x)", "*X", expression);
							}
							else {
								replace("(x)", "X", expression);
							}
							sprintf(expression, "%s", expressionF);
						}
						replaceTimes = 0;
						if (isContained("X", expression)) {
							replace("X", "x", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
					if (isContained("X", expression)) {
						replace("X", "x", expression);
						sprintf(expression, "%s", expressionF);
					}
					while (isContained(")/(", expression)) {

						sprintf(num, "");
						int i = strStart, j = strStart + 1, h = 0;
						int kr = 1, kl = 0;
						while (kr != kl) {
							i--;
							if (expression[i] == ')') {
								kr++;
							}
							if (expression[i] == '(') {
								kl++;
							}
						}
						h = 0;
						while (i < j) {
							num[h] = expression[i];
							i++; h++;
						}
						num[h] = '\0';
						sprintf(saveNum, "");
						sprintf(saveNum, "%s", num);
						sprintf(expressionF, "(%s)*(0x^1+1)", num);
						if (isContained("S", expressionF)) {
							replaceTimes = 0;
							replace("S", "+", expressionF);
							sprintf(num, "%s", expressionF);
						}
						simplifyPolynomial<T>(expressionF);
						removeTriplPars(expressionF);
						sprintf(num, "%s", expressionF);
						if (isContained("+", num)) {
							replaceTimes = 0;
							replace("+", "S", num);
							sprintf(num, "%s", expressionF);
						}
						replaceTimes = 1;
						replace(saveNum, num, expression);
						sprintf(expression, "%s", expressionF);
						if (isContained(")/(", expression)) {
							expression[strStart + 1] = 'D';
							i = strEnd - 1, h = 0;
							sprintf(den, "");
							kr = 0, kl = 1;
							while (kr != kl) {
								den[h] = expression[i];
								i++; h++;
								if (expression[i] == ')') {
									kr++;
								}
								if (expression[i] == '(') {
									kl++;
								}
							}
							den[h] = ')';
							den[h + 1] = '\0';
							sprintf(saveDen, "%s", den);
							sprintf(expressionF, "(%s)*(0x^1+1)", den);
							if (isContained("S", expressionF)) {
								replaceTimes = 0;
								replace("S", "+", expressionF);
								sprintf(den, "%s", expressionF);
							}
							simplifyPolynomial<T>(expressionF);
							removeTriplPars(expressionF);
							sprintf(den, "%s", expressionF);
							if (isContained("+", den)) {
								replaceTimes = 0;
								replace("+", "S", den);
								sprintf(den, "%s", expressionF);
							}
							replaceTimes = 1;
							replace(saveDen, den, expression);
							sprintf(expression, "%s", expressionF);

						}

					}
					replaceTimes = 0;
					if (isContained("D", expression)) {
						replace("D", "/", expression);
						sprintf(expression, "%s", expressionF);
					}

					replaceTimes = 0;
					if (isContained("X", expression)) {
						replace("X", "x", expression);
						sprintf(expression, "%s", expressionF);
					}
				}

				if (isContained("+", expression)) {
					replace("+", "S", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("*x/", expression)) {
					while (isContained("*x/", expression)) {
						int y = strEnd;
						int p = 0;
						sprintf(value, "");
						while (verifyValue(expression[y])) {
							value[p] = expression[y];
							p++; y++;
						}
						value[p] = '\0';
						sprintf(toReplace, "");
						sprintf(toReplace, "*x/%s", value);
						sprintf(expressionF, "*1/%s*x", value);
						replaceTimes = 1;
						replace(toReplace, expressionF, expression);
						sprintf(expression, "%s", expressionF);

					}
				}
				if (isContained("*", expression)) {
					while (isContained("*", expression)) {
						replaceTimes = 1;
						int y = strStart - 1, w = 0;
						sprintf(expressioN, "");
						while (verifyValue(expression[y])) {
							y--;
						}
						y++;
						w = 0;
						while (expression[y] != '+' && y < abs((int)strlen(expression))) {
							expressioN[w] = expression[y];
							w++; y++;
						}
						expressioN[w] = '\0';
						sprintf(expressionF, "(%s)*(0x^1+1)", expressioN);
						replaceTimes = 0;
						if (isContained("S", expressionF)) {
							replace("S", "+", expressionF);
						}
						if (isContained("((", expressionF)) {
							replace("((", "([", expressionF);
						}
						if (isContained("))", expressionF)) {
							replace("))", "])", expressionF);
						}
						simpleSimplifyPolynomial<T>(expressionF);
						replaceTimes = 0;
						if (isContained("(((", expressionF)) {
							replace("(((", "((", expressionF);
						}
						if (isContained(")))", expressionF)) {
							replace(")))", "))", expressionF);
						}
						if (isContained("+", expressionF)) {
							replace("+", "S", expressionF);
						}
						replaceTimes = 1;
						sprintf(expressionF, "%s/(0x^1S1)", expressionF);
						replace(expressioN, expressionF, expression);
						sprintf(expression, "%s", expressionF);

					}
				}
				replaceTimes = 1;
				if (isContained("x", expression)) {
					replaceTimes = 1;
					while (isContained("x", expression)) {
						if (isContained("x", expression) && (verifyOperator(expression[strEnd]) || verifyOperator(expression[strStart - 1]))) {
							while (isContained("x", expression) && (verifyOperator(expression[strEnd]) || verifyOperator(expression[strStart - 1]))) {
								replace("x", "X", expression);
								sprintf(expression, "%s", expressionF);
							}
						}
						else {
							if (isContained("x", expression) && !(verifyOperator(expression[strEnd]) && verifyOperator(expression[strStart - 1]))) {
								replace("x", "X/1", expression);
								sprintf(expression, "%s", expressionF);
							}
							else {
								if (isContained("x", expression) && strStart == 0 && !verifyOperator(expression[strEnd])) {
									replace("x", "X/1", expression);
									sprintf(expression, "%s", expressionF);
								}
								else {
									replace("x", "X", expression);
									sprintf(expression, "%s", expressionF);
								}
							}
						}
					}
					replaceTimes = 0;
					if (isContained("X", expression)) {
						replace("X", "x", expression);
						sprintf(expression, "%s", expressionF);
					}
				}
				replaceTimes = 1;
				while (isContained("*x", expression)) {
					if (!(isContained("*x", expression) && verifyNumber(expression[strStart - 1]))) {
						while (!(isContained("*x", expression) && verifyNumber(expression[strStart - 1]))) {
							replaceTimes = 1;
							replace("*x", "x", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
					if (isContained("*x", expression) && verifyNumber(expression[strStart - 1])) {
						while (isContained("*x", expression) && verifyNumber(expression[strStart - 1])) {
							replaceTimes = 1;
							sprintf(dataBeforeX, "");
							if (verifyValue(expression[strStart - 1])) {
								int y = strStart - 1;
								while (verifyValue(expression[y])) {
									y--;
								}
								int v = 0;
								y++;
								while (verifyValue(expression[y]) && expression[y] != '*') {
									dataBeforeX[v] = expression[y];
									v++; y++;
								}
								dataBeforeX[v] = '\0';
								if (abs((int)strlen(dataBeforeX)) == 0) {
									sprintf(dataBeforeX, "0");
								}
								sprintf(saveDataBeforeX, "");
								sprintf(saveDataBeforeX, "%s*x", dataBeforeX);
								sprintf(expressionF, "(0x+%s)*(x+0)", dataBeforeX);
								simpleSimplifyPolynomial<T>(expressionF);
								removeTriplPars(expressionF);
								replaceTimes = 0;
								if (isContained("+", expressionF)) {
									replace("+", "S", expressionF);
								}
								replaceTimes = 1;
								sprintf(expressionF, "%s/(0x^1S1)", expressionF);
								replace(saveDataBeforeX, expressionF, expression);
								sprintf(expression, "%s", expressionF);

							}

						}
					}
				}
				replaceTimes = 1;
				if (isContained("/", expression)) {
					while (!(isContained("/", expression) && verifyNumberExpression(expression[strStart - 1]) && verifyNumberExpression(expression[strEnd])) && isContained("/", expression)) {
						replace("/", "D", expression);
						sprintf(expression, "%s", expressionF);
					}
					replaceTimes = 0;
					if (isContained("D", expression)) {
						replace("D", "/", expression);
						sprintf(expression, "%s", expressionF);
					}
					replaceTimes = 1;
					if (isContained("/", expression)) {
						sprintf(numbersData, "");
						int y = 0, c = 0;
						for (y; y < abs((int)strlen(expression)); y++) {
							if (isContainedByIndex("/", expression, y)) {
								while (isContainedByIndex("/", expression, y)) {
									y = strEnd;
									while (expression[y] != '+' && y < abs((int)strlen(expression))) {
										y++;
									}
									if (expression[y] == '\0') {
										break;
									}
								}
								if (expression[y] == '\0') {
									break;
								}
							}
							if (expression[y] == '\0') {
								break;
							}
						}
						replaceTimes = 0;

					}
				}
				if (isContained("D", expression)) {
					replace("D", "/", expression);
					sprintf(expression, "%s", expressionF);
				}
				z = 0;
				replaceTimes = 0;
				if (isContained(")S(", expression)) {
					replace(")S(", ")+(", expression);
					sprintf(expression, "%s", expressionF);
				}
				while (!(isContained("/", expression) && verifyNumberExpression(expression[strStart - 1]) && verifyNumberExpression(expression[strEnd]))) {
					replaceTimes = 1;
					replace("/", "!", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("/", expression) && verifyNumberExpression(expression[strStart - 1]) && verifyNumberExpression(expression[strEnd])) {
					while (isContained("/", expression) && verifyNumberExpression(expression[strStart - 1]) && verifyNumberExpression(expression[strEnd])) {
						if (isContained("/", expression) && verifyNumberExpression(expression[strStart - 1]) && verifyNumberExpression(expression[strEnd])) {
							sprintf(num, "");
							int i = strStart - 1, j = strStart, h = 0, k = 0;
							int kr = 1, kl = 0;
							while (verifyNumberExpression(expression[i])) {
								i--;
							}
							i++;
							k = i;
							h = 0;
							while (i < j) {
								num[h] = expression[i];
								i++; h++;
							}
							num[h] = '\0';

							sprintf(saveNum, "");

							sprintf(saveNum, "%s", num);
							if (isContained("S", num)) {
								replace("S", "+", num);
								sprintf(num, "%s", expressionF);
							}
							replaceTimes = 0;

							if (!isContained("x", num)) {
								sprintf(expressionF, "(0x^1+%s)*(0x^1+1)", num);
							}
							else {
								sprintf(expressionF, "(%s)*(0x^1+1)", num);
							}
							simpleSimplifyPolynomial<T>(expressionF);
							removeTriplPars(expressionF);
							replaceTimes = 0;
							if (isContained("+", expressionF)) {
								replace("+", "S", expressionF);
							}
							sprintf(saveConversions[z], "%s", expressionF);
							replaceTimes = 1;
							sprintf(smallText, "");
							sprintf(smallText, "%c", alphabet[z]);
							replaceByIndex(saveNum, smallText, expression, k);
							z++;
							sprintf(expression, "%s", expressionF);
							if (isContained("/", expression)) {
								expression[strStart] = '!';
								i = strEnd, h = 0; j = strStart;

								sprintf(den, "");
								if (!(expression[strEnd] == '(')) {
									while (verifyNumberExpression(expression[i])) {
										den[h] = expression[i];
										i++; h++;
									}
									den[h] = '\0';
								}
								else {
									int kr = 0, kl = 1;
									den[h] = expression[i];
									h++;
									i++;
									while (i < abs((int)strlen(expression)) && kr < kl) {
										den[h] = expression[i];
										i++; h++;
										if (den[h - 1] == ')') {
											kr++;
										}
										if (den[h - 1] == '(') {
											kl++;
										}
									}
									den[h] = '\0';
								}
								sprintf(saveDen, "");

								sprintf(saveDen, "%s", den);
								replaceTimes = 0;
								if (isContained("S", den)) {
									replace("S", "+", den);
									sprintf(den, "%s", expressionF);
								}

								if (!isContained("x", den)) {
									sprintf(expressionF, "(0x^1+%s)*(0x^1+1)", den);
								}
								else {
									sprintf(expressionF, "(%s)*(0x^1+1)", den);
								}
								simpleSimplifyPolynomial<T>(expressionF);
								removeTriplPars(expressionF);


								replaceTimes = 0;
								if (isContained("+", expressionF)) {
									replace("+", "S", expressionF);
								}

								sprintf(saveConversions[z], "%s", expressionF);
								replaceTimes = 0;
								if (isContained("+", den)) {
									replace("+", "S", den);
									sprintf(den, "%s", expressionF);
								}

								replaceTimes = 1;
								sprintf(smallText, "");
								sprintf(smallText, "%c", alphabet[z]);
								replace(saveDen, smallText, expression);
								z++;
								sprintf(expression, "%s", expressionF);
								replaceTimes = 0;
								if (isContained("+", num)) {
									replace("+", "S", num);
									sprintf(num, "%s", expressionF);
								}

							}

						}
						else {
							replaceTimes = 1;
							replace("/", "!", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
					replaceTimes = 0;
					if (isContained("!", expression)) {
						replace("!", "/", expression);
						sprintf(expression, "%s", expressionF);
					}
					removeTriplPars(expression);
					sprintf(expression, "%s", expressionF);
					int lettersTotal = z;
					z = 0;
					replaceTimes = 1;
					while (z < lettersTotal) {
						sprintf(smallText, "");
						sprintf(smallText, "%c", alphabet[z]);
						replace(smallText, saveConversions[z], expression);
						sprintf(expression, "%s", expressionF);

						z++;
					}
					replaceTimes = 0;
					if (isContained("!", expression)) {
						replace("!", "/", expression);
						sprintf(expression, "%s", expressionF);
					}

				}
				replaceTimes = 0;
				if (isContained("D", expression)) {
					replace("D", "/", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("A", expression)) {
					replace("A", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained(")(", expression)) {
					replace(")(", ")*(", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("x", expression) && verifyValue(expression[strStart - 1]) && verifyNumber(expression[strStart - 1])) {
					replaceTimes = 1;
					do {
						if (isContained("x", expression) && verifyValue(expression[strStart - 1]) && verifyNumber(expression[strStart - 1])) {
							int i = strStart - 1;
							sprintf(num, "");
							while (verifyValue(expression[i])) {
								i--;
							}
							i++;
							int p = 0;
							while (verifyValue(expression[i])) {
								num[p] = expression[i];
								p++; i++;
							}
							num[p] = '\0';
							solveMath<T>(num);
							sprintf(num, "%sx", num);
							sprintf(expressionF, "((%fS%fi)X^1S(0S0i))", precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
							replaceTimes = 0;
							if (isContained("-", expressionF)) {
								replace("-", "_", expressionF);
							}
							if (isContained(".0000000000000", expressionF)) {
								replace(".0000000000000", "", expressionF);
							}
							replace(num, expressionF, expression);
							sprintf(expression, "%s", expressionF);

						}
						else {
							replaceTimes = 0;
							replace("x", "X", expression);
							sprintf(expression, "%s", expressionF);
						}
					} while (isContained("x", expression));
					replaceTimes = 0;
					if (isContained("X", expression)) {
						replace("X", "x", expression);
						sprintf(expression, "%s", expressionF);
					}
				}
				replaceTimes = 0;
				if (isContained("X", expression)) {
					replace("X", "x", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("/", expression)) {
					replaceTimes = 1;
					while (isContained("/", expression)) {
						if (isContained("/", expression) && verifyNumber(expression[strStart - 1])) {
							while (isContained("/", expression) && verifyNumber(expression[strStart - 1])) {
								int i = strStart - 1;
								sprintf(num, "");
								while (verifyNumber(expression[i])) {
									i--;
								}
								i++;
								int p = 0;
								while (verifyNumber(expression[i])) {
									num[p] = expression[i];
									p++; i++;
								}
								num[p] = '\0';

								sprintf(new_expression, "%s/", num);
								sprintf(toReplace, "");
								sprintf(toReplace, "(0xS%s)D", num);
								replaceTimes = 1;
								replace(new_expression, toReplace, expression);
								sprintf(expression, "%s", expressionF);

							}
						}
						else {
							replace("/", "D", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
					replaceTimes = 0;
					replace("D", "/", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("/", expression)) {
					replaceTimes = 1;
					while (isContained("/", expression)) {
						if (isContained("/", expression) && verifyNumber(expression[strEnd])) {
							while (isContained("/", expression) && verifyNumber(expression[strEnd])) {
								int i = strEnd;
								sprintf(den, "");
								int p = 0;
								while (verifyNumber(expression[i])) {
									den[p] = expression[i];
									p++; i++;
								}
								den[p] = '\0';
								sprintf(new_expression, "");
								sprintf(new_expression, "/%s", den);
								sprintf(toReplace, "");
								sprintf(toReplace, "D(0xS%s)", den);
								replace(new_expression, toReplace, expression);
								sprintf(expression, "%s", expressionF);

							}
						}
						else {
							replace("/", "D", expression);
							sprintf(expression, "%s", expressionF);
						}
					}
					replaceTimes = 0;
					replace("D", "/", expression);
					sprintf(expression, "%s", expressionF);
				}
				_Delete(saveConversions, DIMTWOD, SHORTDIM, "saveConversions[i]");
			}

			replaceTimes = 1;
			int b = 0;

			if (isContained("*(", expression)) {
				while (isContained("*(", expression)) {
					if (verifyForNumber(expression[strStart - 1])) {
						int h = strEnd;
						int v = 0;
						sprintf(pieceExpre, "");
						int kl = 1, kr = 0;
						while (kl != kr) {
							if (expression[h] == '(') {
								kl++;
							}
							if (expression[h] == ')') {
								kr++;
							}
							if (kl != kr) {
								pieceExpre[v] = expression[h];
								h++; v++;
							}
						}
						pieceExpre[v] = '\0';
						replaceTimes = 1;
						sprintf(number, "");
						sprintf(value, "");
						int b = 0, c = 0, d = 0;
						int r = strStart - 1;
						while (verifyForNumber(expression[r])) {
							r--;
						}
						r++;
						if (verifyForNumber(expression[r])) {
							b = 0;
							d = 0;
							c = r;
							while (verifyForNumber(expression[c])) {
								number[b] = expression[c];
								value[d] = expression[c];
								c++; b++; d++;
							}
							value[d] = '\0';
							while (c <= strStart) {
								number[b] = expression[c];
								c++; b++;
							}
						}
						number[b] = '\0';
						value[d] = '\0';
						sprintf(newNumber, "");
						if (expression[strStart] == '*') {
							sprintf(newNumber, "(0x^1S%s)M", value);
						}
						replace(number, newNumber, expression);
						sprintf(expression, "%s", expressionF);


					}
					if (expression[strStart] == '*') {
						expression[strStart] = 'M';
					}
					if (expression[strStart] == '/') {
						expression[strStart] = 'D';
					}
				}
				replaceTimes = 0;
				if (isContained("S", expression)) {
					replace("S", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("M", expression)) {
					replace("M", "*", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("D", expression)) {
					replace("D", "/", expression);
					sprintf(expression, "%s", expressionF);
				}
			}
			if (isContained("D", expression)) {
				replace("D", "/", expression);
				sprintf(expression, "%s", expressionF);
			}
			if (isContained("M", expression)) {
				replace("M", "*", expression);
				sprintf(expression, "%s", expressionF);
			}
			b = 0;
			if (isContained("+", expression)) {
				replaceTimes = 1;
				while (isContained("+", expression)) {
					if (expression[strStart - 1] == ')' && expression[strEnd] == '(') {
						expression[strStart] = 'A';
					}
					else {
						expression[strStart] = 'S';
					}
				}
				replaceTimes = 0;
				if (isContained("A", expression)) {
					replace("A", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
			}
			if (isContained("+", expression)) {
				while (isContained("+", expression)) {
					if (isContainedByIndex("+", expression, b)) {
						expression[strStart] = 'P';
						sprintf(number, "");
						int n = 0;
						b = strStart - 1;
						while (verifyValue(expression[b])) {
							b--;
						}
						b++;
						while (verifyValue(expression[b])) {
							number[n] = expression[b];
							n++; b++;
						}
						number[n] = '\0';
						if (abs((int)strlen(number)) > 0) {
							sprintf(saveNumber, "");
							sprintf(saveNumber, "%s", number);
							if (isContained("x", number)) {
								sprintf(expressionF, "(%s)/(0xS1)", number);
							}
							else {
								sprintf(expressionF, "(0xS%s)/(0xS1)", number);
							}
							sprintf(number, "%s", expressionF);
							replaceTimes = 1;
							replaceByIndex(saveNumber, number, expression, b - (int)abs((int)strlen(saveNumber)));
							sprintf(expression, "%s", expressionF);

						}

					}
					else {
						expression[strStart] = 'P';
						b = strStart;
					}
				}
				replaceTimes = 0;
				if (isContained("P", expression)) {
					replace("P", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
			}
			replaceTimes = 0;
			T great = 0;
			if (isContained("/", expression)) {
				T Exponent = 0, Divider = 0, saveExponent = 0, saveDivider = 0;
				sprintf(saveExpressionSS, "");
				sprintf(saveExpressionSS, "%s", expression);
				sprintf(saveSimplification, "%s", expression);
				countSplits = countOccurrences("+", expression);
				split("+", expression);

				sprintf(expressionToSimplify, "");
				sprintf(expressionSimplified, "");

				int v = 0;
				while (v < countSplits) {
					sprintf(expressionToSimplify, "%s", splitResult[v]);
					sprintf(expressionSimplified, "%s", splitResult[v]);
					replaceTimes = 0;
					replace("S", "+", expressionSimplified);
					sprintf(expressionSimplified, "%s", expressionF);
					if (countOccurrences("0x", expressionSimplified) < 2) {
						sprintf(expressionF, "%s", expressionSimplified);
						sprintf(expressionSimplified, "%s", expressionF);
						simpleSimplifyPolynomial<T>(expressionSimplified);
						if (isDivisible) {
							sprintf(expressionSimplified, "%s", expressionF);
							if (!isContained("/", expressionSimplified)) {
								sprintf(expressionSimplified, "%s/(0x+1)", expressionSimplified);
							}
						}
						replaceTimes = 0;
						replace("+", "S", expressionSimplified);
						sprintf(expressionSimplified, "%s", expressionF);
						sprintf(expression, "%s", saveExpressionSS);
						replaceTimes = 1;
						replace(expressionToSimplify, expressionSimplified, saveExpressionSS);
						sprintf(saveExpressionSS, "%s", expressionF);
					}
					sprintf(expression, "%s", saveExpressionSS);
					v++;
					sprintf(expressionSimplified, "");
				}
				replaceTimes = 0;
				removeTriplPars(expression);
				sprintf(expression, "%s", expressionF);
				int u = 0;
				countSplits = countOccurrences("+", expression);
				split("+", expression);

				while (u <= countSplits) {
					sprintf(saveCharResult[u], "%s", splitResult[u]);
					u++;
				}
				u = 0;

				while (u <= countSplits) {
					split("/", saveCharResult[u]);
					if (!isContained("x", splitResult[0])) {
						sprintf(numerator[u], "(0xS%s)", splitResult[0]);
					}
					else {
						sprintf(numerator[u], "(%s)", splitResult[0]);
					}
					if (!isContained("x", splitResult[1])) {
						sprintf(denominator[u], "(0xS%s)", splitResult[1]);
					}
					else {
						sprintf(denominator[u], "(%s)", splitResult[1]);
					}
					u++;
				}
				replaceTimes = 0;

				int m = 0;
				int c = 0;
				int equalNum = 0;
				replaceTimes = 0;
				sprintf(intermediate, "");
				sprintf(expression, "");
				while (c <= countSplits) {
					replaceTimes = 0;
					equalNum = 0;
					if (isContained("S", numerator[c])) {
						replace("S", "+", numerator[c]);
						sprintf(numerator[c], "%s", expressionF);
					}
					if (isContained("(((", numerator[c])) {
						replace("(((", "((", numerator[c]);
						sprintf(numerator[c], "%s", expressionF);
					}
					if (isContained(")))", numerator[c])) {
						replace(")))", "))", numerator[c]);
						sprintf(numerator[c], "%s", expressionF);
					}
					sprintf(expressionF, "(%s)*(0x^1+1)", numerator[c]);
					simpleSimplifyPolynomial<T>(expressionF);
					sprintf(roots, "");
					sprintf(numerator[c], "%s", expressionF);
					if (isContained("(((", numerator[c]) && isContained(")))", numerator[c])) {
						replace("(((", "((", numerator[c]);
						sprintf(numerator[c], "%s", expressionF);
						replace(")))", "))", numerator[c]);
						sprintf(numerator[c], "%s", expressionF);
					}
					sprintf(intermediate, "%s", numerator[c]);
					m = 0;
					while (m <= countSplits) {
						if (isContained("S", denominator[m])) {
							replace("S", "+", denominator[m]);
							sprintf(denominator[m], "%s", expressionF);
						}
						if (isContained("(((", denominator[m])) {
							replace("(((", "((", denominator[m]);
							sprintf(denominator[m], "%s", expressionF);
						}
						if (isContained(")))", denominator[m])) {
							replace(")))", "))", denominator[m]);
							sprintf(denominator[m], "%s", expressionF);
						}
						sprintf(expressionF, "(%s)*(0x^1+1)", denominator[m]);
						simpleSimplifyPolynomial<T>(expressionF);
						sprintf(roots, "");
						sprintf(denominator[m], "%s", expressionF);
						if (m != c && (!isContained(denominator[m], intermediate) || (isEqual(numerator[c], denominator[m]) && equalNum == 0))) {
							if (isEqual(numerator[c], denominator[m])) {
								equalNum++;
							}
							if (!isEqual(denominator[m], denominator[c])) {
								sprintf(intermediate, "%s*%s", intermediate, denominator[m]);
							}
						}
						m++;
					}
					if (c == 0) {
						sprintf(expression, "%s", intermediate);
					}
					else {
						if (c <= countSplits) {
							sprintf(expression, "%s+%s", expression, intermediate);
						}
					}
					c++;
				}
				replaceTimes = 0;
				if (isContained("S", expression)) {
					replace("S", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
				replaceTimes = 0;
				if (isContained("(((", expression)) {
					replace("(((", "((", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained(")))", expression)) {
					replace(")))", "))", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("S", expression)) {
					replace("S", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
				replaceTimes = 0;
				if (isContained("+(", expression)) {
					replace("+(", "+[", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained(")x", expression)) {
					replace(")x", "]x", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained(")+[", expression)) {
					replace(")+[", ")+(", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("ix", expression)) {
					replace("ix", "i]x", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("((", expression)) {
					replace("((", "([", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("))", expression)) {
					replace("))", "])", expression);
					sprintf(expression, "%s", expressionF);
				}
				replaceTimes = 0;
				if (isContained("{", expression)) {
					replace("{", "(", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("}", expression)) {
					replace("}", ")", expression);
					sprintf(expression, "%s", expressionF);
				}
				simplifyPolynomial<T>(expression);
				sprintf(expression, "%s", expressionF);
				replaceTimes = 0;
				if (isContained("S", expression)) {
					replace("S", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
				sprintf(expressionF, "%s", expression);


			}
			else {
				replaceTimes = 0;
				if (isContained("(x)", expression)) {
					replace("(x)", "X", expression);
					replace("X", "x", expressionF);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("_x", expression)) {
					replace("_x", "_1x", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("-", expression)) {
					replace("-", "+_", expression);
					sprintf(expression, "%s", expressionF);
				}
				replaceTimes = 0;
				if (isContained("*", expression)) {
					replace("*", "", expression);
					sprintf(expression, "%s", expressionF);
				}
				if (isContained("S", expression)) {
					replaceTimes = 0;
					replace("S", "+", expression);
					sprintf(expression, "%s", expressionF);
				}
				sprintf(expression, "%s", expressionF);

			}

			if (isContained("(x)", expression)) {
				replace("(x)", "X", expression);
				replace("X", "x", expressionF);
				sprintf(expression, "%s", expressionF);
			}
			replaceTimes = 1;
			if (isContained("x", expression) && strStart == 0) {
				replace("x", "1x", expression);
				sprintf(expression, "%s", expressionF);
			}
			replaceTimes = 0;
			if (isContained("_x", expression)) {
				replace("_x", "_1x", expression);
				sprintf(expression, "%s", expressionF);
			}
			if (isContained("+x", expression)) {
				replace("+x", "+1x", expression);
				sprintf(expression, "%s", expressionF);
			}
			replaceTimes = 0;
			if (isContained("i)", expression)) {
				replace("i)", "i]", expression);
				sprintf(expression, "%s", expressionF);
				int i = 0;
				while (i < abs((int)strlen(expression))) {
					if (expression[i] == '(' && verifyValue(expression[i + 1]) && expression[i - 2] != ')') {
						expression[i] = '[';
					}
					i++;
				}
				sprintf(expressionF, "%s", expression);
			}
			else {
				replaceTimes = 0;
				if (isContained("*", expression)) {
					replace("*", "", expression);
					sprintf(expression, "%s", expressionF);
				}

				bool putPars = true;

				sprintf(newEquation, "");

				sprintf(value, "");
				int q = 0, p = 0;
				while (p < abs((int)strlen(expression))) {
					if (verifyValue(expression[p])) {
						if (expression[p - 1] == 'x' && expression[p] == '^' && verifyValue(expression[p + 1])) {
							equa[q] = ' ';
							p++; q++;
							while (verifyValue(expression[p])) {
								equa[q] = ' ';
								q++; p++;
							}
						}
						if ((expression[p - 1] == ')' || verifyValue(expression[p - 1])) && (expression[p] == '*' || expression[p] == '/') && (expression[p + 1] == '(' || expression[p + 1] == 'x')) {
							equa[q] = ' ';
						}
						else {
							equa[q] = expression[p];
						}
					}
					else {
						equa[q] = ' ';
					}
					p++; q++;
				}
				equa[q] = '\0';
				sprintf(equaSimplified, "");
				p = 0, q = 0;
				while (p < abs((int)strlen(equa))) {
					if (verifyValue(equa[p])) {
						q = 0;
						while (verifyValue(equa[p])) {
							value[q] = equa[p];
							p++; q++;
						}
						p--;
						value[q] = '\0';
						solveMath<T>(value);
						if (putPars) {
							sprintf(value, convertToString("[%f+%fi]"), precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
						}
						else {
							sprintf(value, convertToString("[%f+%fi]"), precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
							putPars = true;
						}
						if (isContained("+-", value)) {
							replace("+-", "+_", value);
							sprintf(value, "%s", expressionF);
						}
						if (isContained("-", value)) {
							replace("-", "_", value);
							sprintf(value, "%s", expressionF);
						}
						sprintf(equaSimplified, "%s%s", equaSimplified, value);
					}
					else {
						if (expression[p] == 'x') {
							putPars = false;
						}
						sprintf(equaSimplified, "%s%c", equaSimplified, equa[p]);
					}
					p++;
				}
				equaSimplified[abs((int)strlen(equaSimplified))] = '\0';
				p = 0; q = 0;
				while (p < abs((int)strlen(equaSimplified))) {
					if (equaSimplified[p] == ' ') {
						if (expression[q - 1] == 'x' && expression[q] == '^' && verifyValue(expression[q + 1])) {
							equaSimplified[p] = expression[q];
							p++;
							q++;
							while (verifyValue(expression[q])) {
								equaSimplified[p] = expression[q];
								q++; p++;
							}

						}
						if ((expression[q - 1] == ')' || verifyValue(expression[q - 1])) && (expression[q] == '*' || expression[q] == '/') && (expression[q + 1] == '(' || expression[q + 1] == 'x')) {
							equaSimplified[p] = expression[q];
							p++;
							q++;
						}
						if (verifyValue(expression[q])) {
							while (verifyValue(expression[q])) {
								q++;
							}
						}
						equaSimplified[p] = expression[q];
						q++;
					}
					p++;
				}
				equaSimplified[p] = '\0';
				sprintf(expressionF, "%s", equaSimplified);
				if (isContained(".000000", equaSimplified)) {
					replace(".000000", "", equaSimplified);
					sprintf(equaSimplified, "%s", expressionF);
				}
				if (isContained("(x", equaSimplified)) {
					replace("(x", "([1+0i]x", equaSimplified);
					sprintf(equaSimplified, "%s", expressionF);
				}
				if (isContained("(", equaSimplified)) {
					sprintf(expressionF, "%s", equaSimplified);
				}
				else {
					sprintf(expressionF, "(%s)", equaSimplified);
				}
				_deleteShort(equaSimplified, "equaSimplified");
				equaSimplified = nullptr;
				_deleteShort(equa, "equa");
				equa = nullptr;

			}

			replaceTimes = 0;
			if (isContained("[", expression)) {
				replace("[", "(", expression);
				sprintf(expression, "%s", expressionF);
			}
			if (isContained("]", expression)) {
				replace("]", ")", expression);
				sprintf(expression, "%s", expressionF);
			}
			sprintf(expressionF, "%s", expression);


		}
	}
	_Delete(numerator, DIMTWOD, SHORTDIM, "numerator[i]");
	_Delete(denominator, DIMTWOD, SHORTDIM, "denominator[i]");

	sprintf(expressionF, "%s", expression);
	_deleteShort(expression, "expression");
	_deleteShort(collectChars, "collectChars");
	_deleteShort(replacement, "replacement");
	_deleteShort(addPars, "addPars");
	_deleteShort(saveNum, "saveNum");
	_deleteShort(number, "number");
	_deleteShort(toReplace, "toReplace");
	_deleteShort(getExp, "getExp");
	_deleteShort(poly, "poly");
	_deleteShort(polyNum, "polyNum");
	_deleteShort(alphabet, "alphabet");
	_deleteShort(num, "num");
	_deleteShort(new_expression, "new_expression");
	_deleteShort(expr, "expr");
	_deleteShort(saveExpr, "saveExpr");
	_deleteShort(extractText, "extractText");
	_deleteShort(simplify, "simplify");
	_deleteShort(simplified, "simplified");
	_deleteShort(saveSimplify, "saveSimplify");
	_deleteShort(den, "den");
	_deleteShort(saveDen, "saveDen");
	_deleteShort(value, "value");
	_deleteShort(expressioN, "expressioN");
	_deleteShort(dataBeforeX, "dataBeforeX");
	_deleteShort(saveDataBeforeX, "saveDataBeforeX");
	_deleteShort(numbersData, "numbersData");
	_deleteShort(smallText, "smallText");
	_deleteShort(pieceExpre, "pieceExpre");
	_deleteShort(newNumber, "newNumber");
	_deleteShort(saveNumber, "saveNumber");
	_deleteShort(greatDenominator, "greatDenominator");
	_deleteShort(saveExpressionSS, "saveExpressionSS");
	_deleteShort(expressionToSimplify, "expressionToSimplify");
	_deleteShort(expressionSimplified, "expressionSimplified");
	_deleteShort(intermediate, "intermediate");
	_deleteShort(equa, "equa");
	_deleteShort(newEquation, "newEquation");
	_deleteShort(equaSimplified, "equaSimplified");
	_Delete(saveConversions, DIMTWOD, SHORTDIM, "saveConversions[i]");
	_Delete(saveCharResult, DIMTWOD, SHORTDIM, "saveCharResult[i]");
}


char* convertToString(char* string) {
	sprintf(stringHelper, "%s", string);
	return stringHelper;
}
template<typename T>
void getRoots(T* expressionR, T* expressionI, T* rootsR, T* rootsI, int maxExponent, int rootIndex) {
	// Alocação dinâmica de buffers locais usando o motor ATC
	T* _expressionR = getDynamicArray<T>(DIMDOUBLE);
	T* _expressionI = getDynamicArray<T>(DIMDOUBLE);
	T* expDerivateR = getDynamicArray<T>(DIMDOUBLE);
	T* expDerivateI = getDynamicArray<T>(DIMDOUBLE);

	int i = 0;
	for (i = 0; i <= maxExponent; i++) {
		_expressionR[i] = expressionR[i];
		_expressionI[i] = expressionI[i];
	}

	if (i == maxExponent + 1 && maxExponent > 2) {
		int countRoots = 0;
		T SummDerivateR = 0, SummDerivateI = 0;
		int _rf = 0;
		T SummatoryR = 0, SummatoryI = 0;
		int y = 1, index = 0;

		while (countRoots < maxExponent - 1) {
			// Correção de Fuga de Memória: Se houver uma saída antecipada (break),
			// o fluxo saía do bloco sem libertar a memória se os deletes estivessem mal posicionados.
			// Além disso, previne loops infinitos se a parte imaginária for nula.
			if (fabs(rootsI[index]) < 1E-5) {
				break;
			}

			if (index == rootIndex) {
				index++;
			}
			index = index % (maxExponent + 1);

			_rf = 0;
			// Calcula a derivada do polinómio atual (deflacionado)
			while (_rf < maxExponent - countRoots) {
				multiplication<T>(_expressionR[_rf], _expressionI[_rf], (T)maxExponent - _rf - countRoots, 0.0);
				expDerivateR[_rf] = precisionValueTo<T>(resultR);
				expDerivateI[_rf] = precisionValueTo<T>(resultI);
				_rf++;
			}

			SummDerivateR = 0; SummDerivateI = 0;
			xValuesR = rootsR[index];
			xValuesI = rootsI[index];

			_rf = 0;
			SummatoryR = 0; SummatoryI = 0;
			// Avalia o polinómio no ponto atual (Método de Horner / Newton-Raphson)
			while (_rf < maxExponent - countRoots) {
				exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), maxExponent - _rf - countRoots, 0.0, 1);
				multiplication<T>(_expressionR[_rf], _expressionI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
				SummatoryR = SummatoryR + precisionValueTo<T>(resultR);
				SummatoryI = SummatoryI + precisionValueTo<T>(resultI);
				_rf++;
			}

			// Correção de Limites (Out-of-bounds): Garante que _rf não acede a uma posição inválida
			// caso o grau do polinómio em processamento tenha sido reduzido.
			if (_rf < maxExponent - countRoots) {
				sum<T>(SummatoryR, SummatoryI, _expressionR[_rf], _expressionI[_rf]);
				SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
			}

			SummDerivateR = 0; SummDerivateI = 0;
			_rf = 0;
			while (_rf < maxExponent - 1 - countRoots) {
				exponentiation<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), maxExponent - _rf - 1 - countRoots, 0.0, 1);
				multiplication<T>(expDerivateR[_rf], expDerivateI[_rf], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
				SummDerivateR = SummDerivateR + precisionValueTo<T>(resultR);
				SummDerivateI = SummDerivateI + precisionValueTo<T>(resultI);
				_rf++;
			}

			sum<T>(SummDerivateR, SummDerivateI, expDerivateR[_rf], expDerivateI[_rf]);
			SummDerivateR = precisionValueTo<T>(resultR); SummDerivateI = precisionValueTo<T>(resultI);

			// Prevenção contra Divisão por Zero no plano complexo
			if (fabs(SummDerivateR) < 1E-12 && fabs(SummDerivateI) < 1E-12) {
				SummDerivateR = 1E-12;
				SummDerivateI = 0.0;
			}

			division<T>(SummatoryR, SummatoryI, SummDerivateR, SummDerivateI);
			subtraction<T>(precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI), precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
			xValuesR = precisionValueTo<T>(resultR);
			xValuesI = precisionValueTo<T>(resultI);

			// Deflação Polinomial (Divisão Sintética) utilizando a aproximação convergida
			y = 1;
			while (y - 1 < maxExponent - countRoots) {
				multiplication<T>(_expressionR[y - 1], _expressionI[y - 1], precisionValueTo<T>(xValuesR), precisionValueTo<T>(xValuesI));
				sum<T>(_expressionR[y], _expressionI[y], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
				_expressionR[y] = precisionValueTo<T>(resultR); _expressionI[y] = precisionValueTo<T>(resultI);
				y++;
			}

			// Validação de convergência da raiz antes de atualizar o mapa de raízes
			if (fabs(precisionValueTo<T>(resultR)) <= 1E-6 && fabs(precisionValueTo<T>(resultI)) < 1E-6) {
				rootsR[index] = precisionValueTo<T>(xValuesR);
				rootsI[index] = precisionValueTo<T>(xValuesI);
			}

			countRoots++;
			index++;
		}

		// Resolução do termo quadrático/linear restante pós-deflação
		if (fabs(_expressionR[2]) < 1E-6 && fabs(_expressionI[2]) < 1E-6 && countRoots == maxExponent - 1) {
			multiplication<T>(_expressionR[1], _expressionI[1], -1.0, 0.0);
			rootsR[rootIndex] = precisionValueTo<T>(resultR);
			rootsI[rootIndex] = precisionValueTo<T>(resultI);
		}
	}

	// Correção de Diagnóstico e Logs: Passagem explícita dos nomes das variáveis para a rotina _delete
	_delete(_expressionR, "_expressionR");
	_delete(_expressionI, "_expressionI");
	_delete(expDerivateR, "expDerivateR");
	_delete(expDerivateI, "expDerivateI");
}

template void solveQuadraticEquation<double>(char*, double, double, int);
template double equationSolver<double>(char*);
template void simplifyPolynomial<double>(char*);


void rootsToPolynomial(char* rootsF) { rootsToPolynomial<double>(rootsF); }
template void rootsToPolynomial<double>(char*);
template int getCorrectExponent<double>(char*, char*, int);
