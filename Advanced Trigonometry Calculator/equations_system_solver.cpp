#include "stdafx.h"

template <typename T>

int matrixToValues(char* matrix, T result, T** values, T** valuesI, T** valuesS, T** valuesSI) {
	int i = 0, j = 0, k = 0, l = 0;
	for (i = 0; i < abs((int)strlen(matrix)); i++) {
		if (matrix[i] == ';') {
			count++;
		}
	}
	for (i = 0; i < count - 1; i++) {
		for (j = 0; j < count; j++) {
			char* value = getDynamicCharArray("", "value");
			values[i][j] = 0;
			valuesI[i][j] = 0;
			l = 0;
			while (k < abs((int)strlen(matrix)) && matrix[k] != ';' && matrix[k] != '\\') {
				value[l] = matrix[k];
				k++; l++;
			}
			value[l] = '\0';
			k++;
			calcNow<T>(value, result, 0);
			if (value != nullptr) {
				_delete(value, "value");
				value = nullptr;
			}
			if (verified == 1) {
				values[i][j] = precisionValueTo<T>(resultR);
				valuesS[i][j] = values[i][j];
				valuesI[i][j] = precisionValueTo<T>(resultI);
				valuesSI[i][j] = valuesI[i][j];
			}
			else {
				return 0;
			}
		}
	}
	return 1;
}
template<typename T>
void solveSystem(T** values, T** valuesI) {
	int i = 0, j = 0, jC = 0, iC = 0, iS = 0, jS = 0, g = 0, countVal = 0;
	T divider = 0, dividerI = 0, * valuesToiC = getDynamicArray<T>(DIMDOUBLE), * dividedi = getDynamicArray<T>(DIMDOUBLE), real = 0, imag = 0;
	while (i < count - 1) {
		valuesToiC[i] = 100;
		i++;
	}
	while (jC < count - 1 || countVal != 1 && jC != count - 1) {
		while (i < count - 1) {
			dividedi[i] = 100;
			i++;
		}
		j = jC;
		for (i = iC; i < count - 1; i++) {
			j = jC;
			if ((values[i][j] != 0 || valuesI[i][j] != 0) && valuesToiC[i] != 200) {
				divider = values[i][j];
				dividerI = valuesI[i][j];
				dividedi[i] = 200;
				for (j = 0; j < count; j++) {
					division<T>(values[i][j], valuesI[i][j], divider, dividerI);
					values[i][j] = precisionValueTo<T>(resultR);
					valuesI[i][j] = precisionValueTo<T>(resultI);
				}
				countVal = 0;
				for (g = 0; g < count - 1; g++) {
					if (values[i][g] != 0 || valuesI[i][g] != 0) {
						countVal++;
					}
				}
			}
		}
		if (countVal != 1) {
			i = 0;
			while (i < count - 1) {
				if (values[i][jC] == 1 && valuesI[i][jC] == 0 && i == jC) {
					iC = i;
					valuesToiC[iC] = 200;
					break;
				}
				i++;
			}
			for (i = (iC + 1) % (count - 1); i < count - 1; i++) {
				if (values[i][jC] != 0 || valuesI[i][jC] != 0) {
					for (j = 0; j < count; j++) {
						if (valuesToiC[i] != 200 && dividedi[i] == 200 && dividedi[iC] == 200) {
							subtraction<T>(values[i][j], valuesI[i][j], values[iC][j], valuesI[iC][j]);
							values[i][j] = precisionValueTo<T>(resultR);
							valuesI[i][j] = precisionValueTo<T>(resultI);
						}
					}
				}
			}
			for (i = 0; i < count - 1; i++) {
				if (values[i][jC] == 0 && valuesI[i][jC] == 0) {
					iC = i;
					break;
				}
			}
		}
		jC++;
	}

	// Apenas libertar os arrays temporários locais para evitar fugas em execuções contínuas
	if (valuesToiC != nullptr) _delete(valuesToiC, "valuesToiC");
	if (dividedi != nullptr) _delete(dividedi, "dividedi");
}
template <typename T>

void rearrangeValues<T>(T** valInd, T** values, T** valuesI, T** valuesF, T** valuesFI) {
	int i = 0, j = 0, * weight = getDynamicIntArray();
	for (i = 0; i < count - 1; i++) {
		for (j = 0; j < count - 1; j++) {
			valInd[i][j] = 0;
		}
	}
	for (i = 0; i < count - 1; i++) {
		for (j = 0; j < count - 1; j++) {
			if (values[i][j] != 0 || valuesI[i][j] != 0) {
				valInd[i][j] = j;
			}
			else {
				valInd[i][j] = -1;
			}
		}
	}
	for (i = 0; i < count - 1; i++) {
		weight[i] = 0;
		for (j = 0; j < count - 1; j++) {
			weight[i] = (int)(weight[i] + valInd[i][j]);
		}
	}
	T valSave = 0;
	int* arrangeOrder = getDynamicIntArray();
	int* equa = getDynamicIntArray();
	for (i = 0; i < count - 1; i++) {
		arrangeOrder[i] = -1;
		equa[i] = 1;
	}
	int index = 0;
	int wei = 5000;
	for (i = 0; i < count - 1; i++) {
		wei = 5000;
		index = 0;
		for (j = 0; j < count - 1; j++) {
			if (valInd[j][i] == i && arrangeOrder[i] == -1 && equa[j] == 1) {
				if (wei > weight[j]) {
					wei = weight[j];
					index = j;
				}
			}
		}
		arrangeOrder[i] = index;
		equa[index] = 0;
	}
	for (i = 0; i < count - 1; i++) {
		for (j = 0; j < count; j++) {
			valuesF[i][j] = values[arrangeOrder[i]][j];
			valuesFI[i][j] = valuesI[arrangeOrder[i]][j];
		}
	}
	for (i = 0; i < count - 1; i++) {
		for (j = 0; j < count; j++) {
			values[i][j] = valuesF[i][j];
			valuesI[i][j] = valuesFI[i][j];
		}
	}

	// Apenas libertar arrays locais temporários
	if (weight != nullptr) _delete(weight, "weight");
	if (arrangeOrder != nullptr) _delete(arrangeOrder, "arrangeOrder");
	if (equa != nullptr) _delete(equa, "equa");
}
template<typename T>
void showSolutions<T>(FILE* fout, int correct, T** valInd, T** valuesS, T** valuesSI, T** values, T** valuesI, T** valuesF, T** valuesFI) {

	int q = 0;
	T solutionR = 0, solutionI = 0;
	for (int p = 0; p < count - 1; p++) {
		solutionR = 0;
		solutionI = 0;
		for (q = 0; q < count; q++) {
			multiplication<T>(valuesS[p][q], valuesSI[p][q], values[q][count - 1], valuesI[q][count - 1]);
			solutionR = solutionR + precisionValueTo<T>(resultR);
			solutionI = solutionI + precisionValueTo<T>(resultI);
		}
		char* Value = getDynamicCharArray("", "Value");
		sprintf(Value, "");
		sprintf(Value, "%s", convert2Exponential(solutionR));
		for (int v = 0; v < abs((int)strlen(Value)); v++) {
			if (Value[v] == '-')
				Value[v] = '_';
		}
		solutionR = calcNow<T>(Value, 0, 0);
		sprintf(Value, "%s", convert2Exponential(valuesS[p][count - 1]));
		for (int v = 0; v < abs((int)strlen(Value)); v++) {
			if (Value[v] == '-') {
				Value[v] = '_';
			}
			if (Value[v] == '+') {
				Value[v] = '0';
			}
		}
		valuesS[p][count - 1] = calcNow<T>(Value, 0, 0);
		sprintf(Value, "%s", convert2Exponential(solutionI));
		for (int v = 0; v < abs((int)strlen(Value)); v++) {
			if (Value[v] == '-')
				Value[v] = '_';
		}
		solutionI = calcNow<T>(Value, 0, 0);
		sprintf(Value, "%s", convert2Exponential(valuesSI[p][count - 1]));
		for (int v = 0; v < abs((int)strlen(Value)); v++) {
			if (Value[v] == '-') {
				Value[v] = '_';
			}
			if (Value[v] == '+') {
				Value[v] = '0';
			}
		}
		valuesSI[p][count - 1] = calcNow<T>(Value, 0, 0);
		if (solutionR != valuesS[p][count - 1] || solutionI != valuesSI[p][count - 1]) {
			printf("\n==> Unsolvable system. <==\n\n");
			fprintf(fout, "\n==> Unsolvable system. <==\n\n");
			correct = 0;
			_delete(Value, "Value");
			break;
		}
		solutionR = 0;
		solutionI = 0;
		_delete(Value, "Value");
		Value = nullptr;
	}
	if (correct == 1) {
		puts("");
		for (int p = 0; p < count - 1; p++) {
			char* Value = getDynamicCharArray("", "Value");
			sprintf(Value, "");
			sprintf(Value, "%s", convert2Exponential(values[p][count - 1]));
			for (int v = 0; v < abs((int)strlen(Value)); v++) {
				if (Value[v] == '-')
					Value[v] = '_';
			}
			values[p][count - 1] = calcNow<T>(Value, 0, 0);
			convertComplex2Exponential(values[p][count - 1], valuesI[p][count - 1]);
			if (values[p][count - 1] >= 0 && valuesI[p][count - 1] > 0) {
				printf("x%d=%s+%si\n", p + 1, respR, respI);
				fprintf(fout, "x%d=%s+%si\n", p + 1, respR, respI);
			}
			else {
				if (values[p][count - 1] >= 0 && valuesI[p][count - 1] < 0) {
					printf("x%d=%s%si\n", p + 1, respR, respI);
					fprintf(fout, "x%d=%s%si\n", p + 1, respR, respI);
				}
				else {
					if (values[p][count - 1] < 0 && valuesI[p][count - 1] < 0) {
						printf("x%d=%s%si\n", p + 1, respR, respI);
						fprintf(fout, "x%d=%s%si\n", p + 1, respR, respI);
					}
					else {
						if (values[p][count - 1] < 0 && valuesI[p][count - 1] > 0) {
							printf("x%d=%s+%si\n", p + 1, respR, respI);
							fprintf(fout, "x%d=%s+%si\n", p + 1, respR, respI);
						}
						else {
							if (values[p][count - 1] == 0 && valuesI[p][count - 1] != 0) {
								printf("x%d=%si\n", p + 1, respI);
								fprintf(fout, "x%d=%si\n", p + 1, respI);
							}
							else {
								if (valuesI[p][count - 1] == 0) {
									printf("x%d=%s\n", p + 1, respR);
									fprintf(fout, "x%d=%s\n", p + 1, respR);
								}
							}
						}
					}
				}
			}
			_delete(Value, "Value");
			Value = nullptr;
		}
		puts("");
		fputs("", fout);
		for (int vi = 0; vi < count; vi++) {
			for (int vj = 0; vj < count; vj++) {
				valInd[vi][vj] = 0;
				values[vi][vj] = 0;
				valuesS[vi][vj] = 0;
				valuesSI[vi][vj] = 0;
				valuesF[vi][vj] = 0;
				valuesFI[vi][vj] = 0;
				valuesI[vi][vj] = 0;
			}
		}
		count = 0;
	}
}
template <typename T>
void getSolutions<T>(T** values, T** valuesI) {
	int j = 0, i = 0, jS = 0, iS = 0;
	j = count - 1;
	i = count - 2;
	jS = j;
	iS = i;
	i--;
	while (j - 1 >= 1) {
		while (i >= 0) {
			resultR = 0; resultI = 0;
			multiplication<T>(values[i][j - 1], valuesI[i][j - 1], values[iS][jS], valuesI[iS][jS]);
			subtraction<T>(values[i][count - 1], valuesI[i][count - 1], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
			values[i][count - 1] = precisionValueTo<T>(resultR);
			valuesI[i][count - 1] = precisionValueTo<T>(resultI);
			values[i][j - 1] = 0; valuesI[i][j - 1] = 0;
			i--;
		}
		j--;
		iS--;
		i = iS - 1;
	}
}
template <typename T>

void processor(int p, int i, int countL, int countR, char* arithTrig, char* matrix, FILE* fout,int correct,T result1) {
	p = 0;
	while (arithTrig[i] != ')' && i < abs((int)strlen(arithTrig)) || countR > 0) {
		if (arithTrig[i] == '(' || arithTrig[i] == '{') {
			countL--;
		}
		if (arithTrig[i] == ')' || arithTrig[i] == '}') {
			countR--;
		}
		matrix[p] = arithTrig[i];
		p++;
		i++;
	}
	matrix[p] = '\0';
	if (arithTrig[i] == '\0') {
		printf("\n==> The character ')' is missing. <==\n\n");
		fprintf(fout, "\n==> The character ')' is missing. <==\n\n");
	}
	else {
		int lines = 0, cols = 0;
		for (p = 0; p < abs((int)strlen(matrix)); p++) {
			if (matrix[p] == '\\') {
				cols++;
			}
			if (matrix[p] == ';') {
				lines++;
			}
		}
		lines++;
		if (lines * lines == cols) {
			T** valInd = new T* [DIMTWOD];
			for (int i = 0; i < DIMTWOD; ++i) {
				valInd[i] = getDynamicArray<T>(DIMDOUBLE);
			}T** values = new T* [DIMTWOD];
			for (int i = 0; i < DIMTWOD; ++i) {
				values[i] = getDynamicArray<T>(DIMDOUBLE);
			}
			T** valuesI = new T* [DIMTWOD];
			for (int i = 0; i < DIMTWOD; ++i) {
				valuesI[i] = getDynamicArray<T>(DIMDOUBLE);
			}
			T** valuesS = new T* [DIMTWOD];
			for (int i = 0; i < DIMTWOD; ++i) {
				valuesS[i] = getDynamicArray<T>(DIMDOUBLE);
			}
			T** valuesSI = new T* [DIMTWOD];
			for (int i = 0; i < DIMTWOD; ++i) {
				valuesSI[i] = getDynamicArray<T>(DIMDOUBLE);
			}
			T** valuesF = new T* [DIMTWOD];
			for (int i = 0; i < DIMTWOD; ++i) {
				valuesF[i] = getDynamicArray<T>(DIMDOUBLE);
			}
			T** valuesFI = new T* [DIMTWOD];
			for (int i = 0; i < DIMTWOD; ++i) {
				valuesFI[i] = getDynamicArray<T>(DIMDOUBLE);
			}
			int syntax = matrixToValues<T>(matrix, result1, values, valuesI, valuesS, valuesSI);
			if (syntax == 1) {
				rearrangeValues<T>(valInd, values, valuesI, valuesF, valuesFI);
				solveSystem<T>(values, valuesI);
				getSolutions<T>(values, valuesI);
				showSolutions<T>(fout, correct, valInd, valuesS, valuesSI, values, valuesI, valuesF, valuesFI);
			}
			_Delete(valInd, DIMTWOD, DIMDOUBLE, "valInd");
			_Delete(values, DIMTWOD, DIMDOUBLE, "values");
			_Delete(valuesI, DIMTWOD, DIMDOUBLE, "valuesI");
			_Delete(valuesS, DIMTWOD, DIMDOUBLE, "valuesS");
			_Delete(valuesSI, DIMTWOD, DIMDOUBLE, "valuesSI");
			_Delete(valuesF, DIMTWOD, DIMDOUBLE, "valuesF");
			_Delete(valuesFI, DIMTWOD, DIMDOUBLE, "valuesFI");
		}
		else {
			printf("\nError in the introduction of the system of equations matrix.\n ==> Based in the number of rows is concluded that some elements are in fault or they are more than the needed.\n\n");
			fprintf(fout, "\nError in the introduction of the system of equations matrix.\n ==> Based in the number of rows is concluded that some elements are in fault or they are more than the needed.\n\n");
		}
	}
}
template void processor<double>(int, int, int, int, char*, char*, FILE*, int, double);
