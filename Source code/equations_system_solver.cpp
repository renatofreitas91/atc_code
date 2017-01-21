

#include "stdafx.h"



int matrixToValues(char matrix[DIM], double result) {
	int i = 0, j = 0, k = 0, l = 0;
	for (i = 0; matrix[i] != '\0'; i++) {
		if (matrix[i] == ';') {
			count++;
		}
	}
	for (i = 0; i < count - 1; i++) {
		for (j = 0; j < count; j++) {
			char value[DIM] = "";	  char valueF[DIM] = "";
			values[i][j] = 0;
			valuesI[i][j] = 0;
			l = 0;

			while (matrix[k] != '\0'&&matrix[k] != ';'&&matrix[k] != '\\') {
				value[l] = matrix[k];
				k++; l++;
			}
			value[l] = '\0';
			k++;
			calcNow(value, result, 0);
			if (verified == 1) {
				values[i][j] = resultR;
				valuesS[i][j] = values[i][j];
				valuesI[i][j] = resultI;
				valuesSI[i][j] = valuesI[i][j];
			}
			else {
				return 0;
			}
		}
	}
	return 1;
}

void solveSystem() {
	int i = 0, j = 0, jC = 0, iC = 0, iS = 0, jS = 0, g = 0, countVal = 0;
	double divider = 0, dividerI = 0, valuesToiC[DIM], dividedi[DIM], real = 0, imag = 0;
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
					division(values[i][j], valuesI[i][j], divider, dividerI);
					values[i][j] = resultR;
					valuesI[i][j] = resultI;
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
							subtraction(values[i][j], valuesI[i][j], values[iC][j], valuesI[iC][j]);
							values[i][j] = resultR;
							valuesI[i][j] = resultI;
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
}

void rearrangeValues() {
	int i = 0, j = 0, weight[DIM];
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


	double valSave = 0;
	int arrangeOrder[DIM], equa[DIM];
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
}

void getSolutions() {
	int j = 0, i = 0, jS = 0, iS = 0;
	j = count - 1;
	i = count - 2;
	jS = j;
	iS = i;
	i--;
	while (j - 1 >= 1) {
		while (i >= 0) {
			resultR = 0; resultI = 0;
			multiplication(values[i][j - 1], valuesI[i][j - 1], values[iS][jS], valuesI[iS][jS]);
			subtraction(values[i][count - 1], valuesI[i][count - 1], resultR, resultI);
			values[i][count - 1] = resultR;
			valuesI[i][count - 1] = resultI;
			values[i][j - 1] = 0; valuesI[i][j - 1] = 0;
			i--;
		}
		j--;
		iS--;
		i = iS - 1;
	}
}

void showValues() {
	int i = 0, j = 0;
	puts(".......................................");
	for (i = 0; i < count - 1; i++) {
		for (j = 0; j < count; j++) {
			printf("%G+%Gi|", values[i][j], valuesI[i][j]);
		}
		printf("\n");
	}
	puts(".......................................");

}