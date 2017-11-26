

#include "stdafx.h"

void arithmeticMatrixSolver() {
	int op = 0, op1 = 1;
	char express[DIM] = "";
	do {
		char matrix[DIM] = "";
		int mIndex = 0, ff = 0, lins = 1, cols = 1, lins1 = 1, cols1 = 1, saveCols = -1, saveCols1 = -1, errorCols = 0, errorCols1 = 0, i = 0, j = 0;
		double vMS[dim][dim], uMS[dim][dim], vMSI[dim][dim], uMSI[dim][dim], rMSI[dim][dim], rMS[dim][dim];
		double 	real = 0, reI;
		fflush(NULL);
		puts("\nWhat to do?");
		puts("Sum of Matrices -> 1");
		puts("Subtraction of Matrices -> 2");
		puts("Multiply a Matrix by a complex/real number -> 3");
		puts("Multiplication of Matrices -> 4");
		puts("Transpose a Matrix -> 5");
		puts("Inverse a Matrix -> 6");
		op = (int)getValue();
		puts("");
		if (op == 1) {
			printf("\nFirst matrix:\n");
			gets_s(matrix);
			do {
				char value[DIM] = "";
				ff = 0;
				while (matrix[mIndex] != '\\'&&matrix[mIndex] != ';'&&matrix[mIndex] != '\0') {
					value[ff] = matrix[mIndex];
					ff++; mIndex++;
				}
				value[ff] = '\0';
				calcNow(value, 0, 0);
				vMS[i][j] = resultR;
				vMSI[i][j] = resultI;
				if (matrix[mIndex] == '\\') {
					j++; cols++;
				}
				else {
					if (matrix[mIndex] == ';' || matrix[mIndex] == '\0') {
						j = 0; i++;
						if (saveCols != cols&&saveCols != -1) {
							errorCols = 1;
						}
						saveCols = cols;
						if (matrix[mIndex] != '\0') {
							lins++;
							cols = 1;
						}
					}
				}
				mIndex++;
			} while (matrix[mIndex] != '\0');
			printf("\nSecond Matrix:\n");
			gets_s(matrix);
			i = 0; j = 0;
			mIndex = 0; ff = 0;
			do {
				char value[DIM] = "";
				ff = 0;
				while (matrix[mIndex] != '\\'&&matrix[mIndex] != ';'&&matrix[mIndex] != '\0') {
					value[ff] = matrix[mIndex];
					ff++; mIndex++;
				}
				value[ff] = '\0';
				calcNow(value, 0, 0);
				uMS[i][j] = resultR;
				uMSI[i][j] = resultI;
				if (matrix[mIndex] == '\\') {
					j++; cols1++;
				}
				else {
					if (matrix[mIndex] == ';' || matrix[mIndex] == '\0') {
						j = 0; i++;
						if (saveCols1 != cols1&&saveCols1 != -1) {
							errorCols1 = 1;
						}
						saveCols1 = cols1;
						if (matrix[mIndex] != '\0') {
							lins1++;
							cols1 = 1;
						}
					}
				}
				mIndex++;
			} while (matrix[mIndex] != '\0');
			if (lins == lins1 && cols == cols1&&errorCols == 0 && errorCols1 == 0) {
				printf("\nMatrix sum:\n");
				fmsum(lins, cols, vMS, uMS, rMS, vMSI, uMSI, rMSI);
			}
			else {
				if (errorCols == 1 || errorCols1 == 1) {
					if (errorCols == 1) {
						puts("\nError: The numbers of columns per line in the first matrix is not the same in the lines.\n");
					}
					if (errorCols1 == 1) {
						puts("\nError: The numbers of columns per line in the second matrix is not the same in the lines.\n");
					}
				}
				else {
					puts("\nError: The numbers of columns and/or lines is not equal in the two matrices.\n");
				}
			}
		}
		if (op == 2) {
			printf("\nFirst matrix:\n");
			gets_s(matrix);
			do {
				char value[DIM] = "";
				ff = 0;
				while (matrix[mIndex] != '\\'&&matrix[mIndex] != ';'&&matrix[mIndex] != '\0') {
					value[ff] = matrix[mIndex];
					ff++; mIndex++;
				}
				value[ff] = '\0';
				calcNow(value, 0, 0);
				vMS[i][j] = resultR;
				vMSI[i][j] = resultI;
				if (matrix[mIndex] == '\\') {
					j++; cols++;
				}
				else {
					if (matrix[mIndex] == ';' || matrix[mIndex] == '\0') {
						j = 0; i++;
						if (saveCols != cols&&saveCols != -1) {
							errorCols = 1;
						}
						saveCols = cols;
						if (matrix[mIndex] != '\0') {
							lins++;
							cols = 1;
						}
					}
				}
				mIndex++;
			} while (matrix[mIndex] != '\0');
			printf("\nSecond Matrix:\n");
			gets_s(matrix);
			i = 0; j = 0;
			mIndex = 0; ff = 0;
			do {
				char value[DIM] = "";
				ff = 0;
				while (matrix[mIndex] != '\\'&&matrix[mIndex] != ';'&&matrix[mIndex] != '\0') {
					value[ff] = matrix[mIndex];
					ff++; mIndex++;
				}
				value[ff] = '\0';
				calcNow(value, 0, 0);
				uMS[i][j] = resultR;
				uMSI[i][j] = resultI;
				if (matrix[mIndex] == '\\') {
					j++; cols1++;
				}
				else {
					if (matrix[mIndex] == ';' || matrix[mIndex] == '\0') {
						j = 0; i++;
						if (saveCols1 != cols1&&saveCols1 != -1) {
							errorCols1 = 1;
						}
						saveCols1 = cols1;
						if (matrix[mIndex] != '\0') {
							lins1++;
							cols1 = 1;
						}
					}
				}
				mIndex++;
			} while (matrix[mIndex] != '\0');
			if (lins == lins1 && cols == cols1&&errorCols == 0 && errorCols1 == 0) {
				printf("\nMatrix subtraction:\n");
				fmsubt(lins, cols, vMS, uMS, rMS, vMSI, uMSI, rMSI);
			}
			else {
				if (errorCols == 1 || errorCols1 == 1) {
					if (errorCols == 1) {
						puts("\nError: The numbers of columns per line in the first matrix is not the same in the lines.\n");
					}
					if (errorCols1 == 1) {
						puts("\nError: The numbers of columns per line in the second matrix is not the same in the lines.\n");
					}
				}
				else {
					puts("\nError: The numbers of columns and/or lines is not equal in the two matrices.\n");
				}
			}
		}
		if (op == 3) {
			printf("\nMatrix:\n");
			gets_s(matrix);
			do {
				char value[DIM] = "";
				ff = 0;
				while (matrix[mIndex] != '\\'&&matrix[mIndex] != ';'&&matrix[mIndex] != '\0') {
					value[ff] = matrix[mIndex];
					ff++; mIndex++;
				}
				value[ff] = '\0';
				calcNow(value, 0, 0);
				vMS[i][j] = resultR;
				vMSI[i][j] = resultI;
				if (matrix[mIndex] == '\\') {
					j++; cols++;
				}
				else {
					if (matrix[mIndex] == ';' || matrix[mIndex] == '\0') {
						j = 0; i++;
						if (saveCols != cols&&saveCols != -1) {
							errorCols = 1;
						}
						saveCols = cols;
						if (matrix[mIndex] != '\0') {
							lins++;
							cols = 1;
						}
					}
				}
				mIndex++;
			} while (matrix[mIndex] != '\0');
			printf("\nWhat is the real/complex number?\n");
			getValue();
			real = resultR;
			reI = resultI;
			if (errorCols == 0) {
				printf("\nResulting matrix:\n");
				fmmulr(lins, cols, vMS, rMS, real, vMSI, rMSI, reI);
			}
			else {
				puts("\nError: The numbers of columns per line in the matrix is not the same in the lines.\n");
			}
		}
		if (op == 4) {
			printf("\nFirst matrix:\n");
			gets_s(matrix);
			do {
				char value[DIM] = "";
				ff = 0;
				while (matrix[mIndex] != '\\'&&matrix[mIndex] != ';'&&matrix[mIndex] != '\0') {
					value[ff] = matrix[mIndex];
					ff++; mIndex++;
				}
				value[ff] = '\0';
				calcNow(value, 0, 0);
				vMS[i][j] = resultR;
				vMSI[i][j] = resultI;
				if (matrix[mIndex] == '\\') {
					j++; cols++;
				}
				else {
					if (matrix[mIndex] == ';' || matrix[mIndex] == '\0') {
						j = 0; i++;
						if (saveCols != cols&&saveCols != -1) {
							errorCols = 1;
						}
						saveCols = cols;
						if (matrix[mIndex] != '\0') {
							lins++;
							cols = 1;
						}
					}
				}
				mIndex++;
			} while (matrix[mIndex] != '\0');
			printf("\nSecond Matrix:\n");
			gets_s(matrix);
			i = 0; j = 0;
			mIndex = 0; ff = 0;
			do {
				char value[DIM] = "";
				ff = 0;
				while (matrix[mIndex] != '\\'&&matrix[mIndex] != ';'&&matrix[mIndex] != '\0') {
					value[ff] = matrix[mIndex];
					ff++; mIndex++;
				}
				value[ff] = '\0';
				calcNow(value, 0, 0);
				uMS[i][j] = resultR;
				uMSI[i][j] = resultI;
				if (matrix[mIndex] == '\\') {
					j++; cols1++;
				}
				else {
					if (matrix[mIndex] == ';' || matrix[mIndex] == '\0') {
						j = 0; i++;
						if (saveCols1 != cols1&&saveCols1 != -1) {
							errorCols1 = 1;
						}
						saveCols1 = cols1;
						if (matrix[mIndex] != '\0') {
							lins1++;
							cols1 = 1;
						}
					}
				}
				mIndex++;
			} while (matrix[mIndex] != '\0');
			if (errorCols == 0 && errorCols1 == 0) {
				printf("\nMatrix multiplication:\n");
				fmmulm(lins1, cols, lins, cols1, vMS, uMS, rMS, vMSI, uMSI, rMSI);
			}
			else {
				if (errorCols == 1) {
					puts("\nError: The numbers of columns per line in the first matrix is not the same in the lines.\n");
				}
				if (errorCols1 == 1) {
					puts("\nError: The numbers of columns per line in the second matrix is not the same in the lines.\n");
				}
			}
		}
		if (op == 5) {
			printf("\nMatrix:\n");
			gets_s(matrix);
			do {
				char value[DIM] = "";
				ff = 0;
				while (matrix[mIndex] != '\\'&&matrix[mIndex] != ';'&&matrix[mIndex] != '\0') {
					value[ff] = matrix[mIndex];
					ff++; mIndex++;
				}
				value[ff] = '\0';
				calcNow(value, 0, 0);
				vMS[i][j] = resultR;
				vMSI[i][j] = resultI;
				if (matrix[mIndex] == '\\') {
					j++; cols++;
				}
				else {
					if (matrix[mIndex] == ';' || matrix[mIndex] == '\0') {
						j = 0; i++;
						if (saveCols != cols&&saveCols != -1) {
							errorCols = 1;
						}
						saveCols = cols;
						if (matrix[mIndex] != '\0') {
							lins++;
							cols = 1;
						}
					}
				}
				mIndex++;
			} while (matrix[mIndex] != '\0');
			if (errorCols == 0) {
				printf("\nMatrix transposed:\n");
				fmtranspose(lins, cols, vMS, vMSI);
			}
			else {
				puts("\nError: The numbers of columns per line in the matrix is not the same in the lines.\n");
			}
		}
		if (op == 6) {
			printf("\nMatrix:\n");
			gets_s(matrix);
			int mIndex = 0, ff = 0, lins = 1, cols = 1, lins1 = 1, cols1 = 1, saveCols = -1, saveCols1 = -1, errorCols = 0, errorCols1 = 0, i = 0, j = 0;
			double vMS[dim][dim], vMSI[dim][dim];
			do {
				char value[DIM] = "";
				ff = 0;
				while (matrix[mIndex] != '\\'&&matrix[mIndex] != ';'&&matrix[mIndex] != '\0') {
					value[ff] = matrix[mIndex];
					ff++; mIndex++;
				}
				value[ff] = '\0';
				calcNow(value, 0, 0);
				vMS[i][j] = resultR;
				vMSI[i][j] = resultI;
				if (matrix[mIndex] == '\\') {
					j++; cols++;
				}
				else {
					if (matrix[mIndex] == ';' || matrix[mIndex] == '\0') {
						j = 0; i++;
						if (saveCols != cols&&saveCols != -1) {
							errorCols = 1;
						}
						saveCols = cols;
						if (matrix[mIndex] != '\0') {
							lins++;
							cols = 1;
						}
					}
				}
				mIndex++;
			} while (matrix[mIndex] != '\0');
			if (errorCols == 0 && cols == lins&&cols >= 2) {
				char detChecker[DIM] = "";
				sprintf(detChecker, "det(%s)", matrix);
				atcProg(detChecker);
				if (resultR == 0 && resultI == 0) {
					printf("\nError: Your matrix does not have a inverse.\n--> det(%s)=0\n\n", matrix);
				}
				else {
					printf("\nMatrix Inverse:\n");
					fminverse(lins, cols, vMS, vMSI);
				}
			}
			else {
				if (errorCols == 1) {
					puts("\nError: The numbers of columns per line in the matrix is not the same in the lines.\n");
				}
				if (cols != lins) {
					puts("\nError: The number of lines and columns is not equal.\n");
				}
				if (cols < 2) {
					puts("\nError: Your matrix must be at minimum of type 2x2.\n");
				}
			}
		}
		if (op < 1 || op>6) {
			puts("\n\nError: Incorrect option id.\n\n");
		}
		fflush(NULL);
		printf("\nContinue? (Yes -> 1 / No -> 0)\n");
		op1 = (int)getValue();
	} while (op1 != 0);
}

void fmsum(int lins, int cols, double v[dim][dim], double u[dim][dim], double r[dim][dim], double vI[dim][dim], double uI[dim][dim], double rI[dim][dim]) {
	int i, j;
	char report[DIM] = "";
	for (i = 0; i < lins; i++) {
		for (j = 0; j < cols; j++) {
			sum(v[i][j], vI[i][j], u[i][j], uI[i][j]);
			r[i][j] = resultR;
			rI[i][j] = resultI;
			sprintf(report, "%s%G+%Gi ", report, r[i][j], rI[i][j]);
		}
		sprintf(report, "%s\n", report);
	}
	puts(report);
	puts("Export result? (Yes -> 1 \\ No -> 0)");
	int option = (int)getValue();
	if (option == 1) {
		saveToReport(report);
	}
}

void fmsubt(int lins, int cols, double v[dim][dim], double u[dim][dim], double r[dim][dim], double vI[dim][dim], double uI[dim][dim], double rI[dim][dim]) {
	int i, j;
	char report[DIM] = "";
	for (i = 0; i < lins; i++) {
		for (j = 0; j < cols; j++) {
			subtraction(v[i][j], vI[i][j], u[i][j], uI[i][j]);
			r[i][j] = resultR;
			rI[i][j] = resultI;
			sprintf(report, "%s%G+%Gi ", report, r[i][j], rI[i][j]);
		}
		sprintf(report, "%s\n", report);
	}
	puts(report);
	puts("Export result? (Yes -> 1 \\ No -> 0)");
	int option = (int)getValue();
	if (option == 1) {
		saveToReport(report);
	}
}

void fmmulr(int lins, int cols, double v[dim][dim], double r[dim][dim], double re, double vI[dim][dim], double rI[dim][dim], double reI) {
	int i, j;
	char report[DIM] = "";
	for (i = 0; i < lins; i++) {
		for (j = 0; j < cols; j++) {
			multiplication(v[i][j], vI[i][j], re, reI);
			r[i][j] = resultR;
			rI[i][j] = resultI;
			sprintf(report, "%s%G+%Gi ", report, r[i][j], rI[i][j]);
		}
		sprintf(report, "%s\n", report);
	}
	puts(report);
	puts("Export result? (Yes -> 1 \\ No -> 0)");
	int option = (int)getValue();
	if (option == 1) {
		saveToReport(report);
	}
}

void fmmulm(int lins2, int cols1, int lins1, int cols2, double v[dim][dim], double u[dim][dim], double r[dim][dim], double vI[dim][dim], double uI[dim][dim], double rI[dim][dim]) {
	int k, i, j;
	char report[DIM] = "";
	double prod, prodI;
	if (lins2 != cols1)
		printf("\nError: The number of columns of first Matrix differs from the numbers of rows of second Matrix!\n");
	else {
		for (i = 0; i < lins1; i++) {
			for (k = 0; k < cols2; k++) {
				prod = 0; prodI = 0;
				for (j = 0; j < cols1; j++) {
					multiplication(v[i][j], vI[i][j], u[j][k], uI[j][k]);
					prod = prod + resultR;
					prodI = prodI + resultI;
				}
				r[i][k] = prod;
				rI[i][k] = prodI;
			}
		}
		for (i = 0; i < lins1; i++) {
			for (k = 0; k < cols2; k++) {
				sprintf(report, "%s%G+%Gi ", report, r[i][k], rI[i][k]);
			}
			sprintf(report, "%s\n", report);
		}
		puts(report);
		puts("Export result? (Yes -> 1 \\ No -> 0)");
		int option = (int)getValue();
		if (option == 1) {
			saveToReport(report);
		}
	}
}

void fmtranspose(int lins, int  cols, double vMS[dim][dim], double vMSI[dim][dim]) {
	double mTransposeR[dim][dim], mTransposeI[dim][dim];
	int i = 0, j = 0;
	char report[DIM] = "";
	for (i = 0; i < cols; i++) {
		for (j = 0; j < lins; j++) {
			mTransposeR[i][j] = vMS[j][i];
			mTransposeI[i][j] = vMSI[j][i];
		}
	}
	for (i = 0; i < cols; i++) {
		for (j = 0; j < lins; j++) {
			sprintf(report, "%s%G+%Gi ", report, mTransposeR[i][j], mTransposeI[i][j]);
		}
		sprintf(report, "%s\n", report);
	}
	puts(report);
	puts("Export result? (Yes -> 1 \\ No -> 0)");
	int option = (int)getValue();
	if (option == 1) {
		saveToReport(report);
	}
}

void fmdeterminant(int lins, int  cols, double vMS[dim][dim], double vMSI[dim][dim]) {
	int multiplier = 0;
	do {
		double newMatrixR[dim][dim], newMatrixI[dim][dim];
		double lineMultipliedR[dim], lineMultipliedI[dim], lineResultR[dim], lineResultI[dim];
		int i = 0, j = 0, k = 0, needJacobi = 1, l = 0;
		if (lins > 2) {
			for (i = 0; i < lins; i++) {
				for (j = 0; j < cols; j++) {
					if (vMS[i][j] == 1 && vMSI[i][j] == 0) {
						needJacobi = 0;
					}
				}
			}
			if (needJacobi == 1) {
				int countNotZero = 0;
				j = 0;
				do {
					countNotZero = 0;
					i = 0;
					double jacobiMultiplierR = 0, jacobiMultiplierI = 0, jacobiGoalR = 0, jacobiGoalI = 0;
					while (vMS[i][j] == 0 && vMSI[i][j] == 0) {
						i++;
					}
					i++;
					if (vMS[i][j] != 0 || vMSI[i][j] != 0) {
						multiplication(-1, 0, vMS[i][j], vMSI[i][j]);
						countNotZero++;
					}
					sum(1, 0, resultR, resultI);
					jacobiGoalR = resultR;
					jacobiGoalI = resultI;
					if (vMS[i - 1][j] == 0 && vMSI[i - 1] == 0) {
						l = i + 1;
						while (vMS[l][j] == 0 && vMSI[l][j] == 0 && l < cols) {
							l++;
						}
						if (vMS[l][j] != 0 || vMSI[l][j] != 0) {
							countNotZero++;
							division(jacobiGoalR, jacobiGoalI, vMS[l][j], vMSI[l][j]);
						}
					}
					else {
						countNotZero++;
						division(jacobiGoalR, jacobiGoalI, vMS[i - 1][j], vMSI[i - 1][j]);
					}
					jacobiMultiplierR = resultR;
					jacobiMultiplierI = resultI;
					for (k = 0; k < cols; k++) {
						if (l == 0) {
							multiplication(jacobiMultiplierR, jacobiMultiplierI, vMS[i - 1][k], vMSI[i - 1][k]);
						}
						else {
							multiplication(jacobiMultiplierR, jacobiMultiplierI, vMS[l][k], vMSI[l][k]);
						}
						lineMultipliedR[k] = resultR;
						lineMultipliedI[k] = resultI;
						sum(lineMultipliedR[k], lineMultipliedI[k], vMS[i][k], vMSI[i][k]);
						lineResultR[k] = resultR;
						lineResultI[k] = resultI;
					}
					for (k = 0; k < cols; k++) {
						vMS[i][k] = lineResultR[k]; vMSI[i][k] = lineResultI[k];
					}
					if (countNotZero != 2) {
						j++;
					}
				} while (countNotZero != 2 && j != cols);
			}
			for (i = 0; i < lins; i++) {
				for (j = 0; j < cols; j++) {
					if (vMS[i][j] == 1 && vMSI[i][j] == 0) {
						break;
					}
				}
				if (vMS[i][j] == 1 && vMSI[i][j] == 0) {
					break;
				}
			}
			int m = 0, n = 0;
			multiplier = (int)pot(-1, (i + 1) + (j + 1), 1);
			for (m = 0; m < lins; m++) {
				if (m != i) {
					for (n = 0; n < cols; n++) {
						if (n != j) {
							multiplication(vMS[m][j], vMSI[m][j], vMS[i][n], vMSI[i][n]);
							subtraction(vMS[m][n], vMSI[m][n], resultR, resultI);
							multiplication(multiplier, 0, resultR, resultI);
							vMS[m][n] = resultR; vMSI[m][n] = resultI;
						}
					}
				}
			}
			int o = 0, p = 0;
			for (m = 0; m < lins; m++) {
				if (m == i) {
					m++;
				}
				for (n = 0; n < cols; n++) {
					if (n == j) {
						n++;
					}
					newMatrixR[o][p] = vMS[m][n]; newMatrixI[o][p] = vMSI[m][n];
					p++;
				}
				o++;
				p = 0;
			}
			lins--; cols--;
			for (m = 0; m < cols; m++) {
				for (n = 0; n < lins; n++) {
					vMS[m][n] = newMatrixR[m][n]; vMSI[m][n] = newMatrixI[m][n];
				}
			}
		}
		else {
			double adR = 0, adI = 0, cbR = 0, cbI = 0;
			multiplication(vMS[0][0], vMSI[0][0], vMS[1][1], vMSI[1][1]);
			adR = resultR; adI = resultI;
			multiplication(vMS[1][0], vMSI[1][0], vMS[0][1], vMSI[0][1]);
			cbR = resultR; cbI = resultI;
			subtraction(adR, adI, cbR, cbI);
			if (multiplier != 0) {
				multiplication(multiplier, 0, resultR, resultI);
			}
			lins--; cols--;
		}
	} while (lins > 1);
}

void startDetProcessing(char matrix[DIM]) {
	int mIndex = 0, ff = 0, lins = 1, cols = 1, lins1 = 1, cols1 = 1, saveCols = -1, saveCols1 = -1, errorCols = 0, errorCols1 = 0, i = 0, j = 0;
	double vMS[dim][dim], vMSI[dim][dim];
	do {
		char value[DIM] = "";
		ff = 0;
		while (matrix[mIndex] != '\\'&&matrix[mIndex] != ';'&&matrix[mIndex] != '\0') {
			value[ff] = matrix[mIndex];
			ff++; mIndex++;
		}
		value[ff] = '\0';
		calcNow(value, 0, 0);
		vMS[i][j] = resultR;
		vMSI[i][j] = resultI;
		if (matrix[mIndex] == '\\') {
			j++; cols++;
		}
		else {
			if (matrix[mIndex] == ';' || matrix[mIndex] == '\0') {
				j = 0; i++;
				if (saveCols != cols&&saveCols != -1) {
					errorCols = 1;
				}
				saveCols = cols;
				if (matrix[mIndex] != '\0') {
					lins++;
					cols = 1;
				}
			}
		}
		mIndex++;
	} while (matrix[mIndex] != '\0');
	fmdeterminant(lins, cols, vMS, vMSI);
}

void fminverse(int lins, int  cols, double vMS[dim][dim], double vMSI[dim][dim]) {
	int i = 0, j = 0, one = cols, pivot = 0;
	while (i < cols) {
		for (j = cols; j < cols * 2; j++) {
			if (one == j) {
				vMS[i][j] = 1; vMSI[i][j] = 0;
			}
			else {
				vMS[i][j] = 0; vMSI[i][j] = 0;
			}
		}
		one++;
		i++;
	}
	do {
		i = pivot;
		while (vMS[i][pivot] == 0 && vMSI[i][pivot] == 0 && i < cols) {
			i++;
		}
		if (i == cols) {
			i = 0;
			while (vMS[i][pivot] == 0 && vMSI[i][pivot] == 0 && i < pivot) {
				i++;
			}
		}
		if (i != pivot) {
			int t = 0;
			double saveLineR[dim], saveLineI[dim];
			for (t = 0; t < cols * 2; t++) {
				saveLineR[t] = vMS[i][t];
				saveLineI[t] = vMSI[i][t];
			}
			for (t = 0; t < cols * 2; t++) {
				vMS[i][t] = vMS[pivot][t];
				vMSI[i][t] = vMSI[pivot][t];
			}
			for (t = 0; t < cols * 2; t++) {
				vMS[pivot][t] = saveLineR[t];
				vMSI[pivot][t] = saveLineI[t];
			}
		}
		i = pivot;
		double pivotR = 0, pivotI = 0;
		int linePivot = i, nextCol = linePivot + 1;
		if (i == pivot) {
			pivotR = vMS[i][i]; pivotI = vMSI[i][i];
			for (j = 0; j < cols * 2; j++) {
				division(vMS[pivot][j], vMSI[pivot][j], pivotR, pivotI);
				vMS[pivot][j] = resultR; vMSI[pivot][j] = resultI;
			}
		}
		for (i = linePivot + 1; i < cols; i++) {
			for (j = 0; j < cols + nextCol; j++) {
				multiplication(vMS[i][pivot], vMSI[i][pivot], vMS[pivot][j], vMSI[pivot][j]);
				subtraction(vMS[i][j], vMSI[i][j], resultR, resultI);
				if (j != pivot) {
					vMS[i][j] = resultR; vMSI[i][j] = resultI;
				}
			}
			vMS[i][pivot] = 0; vMSI[i][pivot] = 0;
		}
		for (i = 0; i < pivot; i++) {
			for (j = 0; j < cols + nextCol; j++) {
				multiplication(vMS[i][pivot], vMSI[i][pivot], vMS[pivot][j], vMSI[pivot][j]);
				subtraction(vMS[i][j], vMSI[i][j], resultR, resultI);
				if (j != pivot) {
					vMS[i][j] = resultR; vMSI[i][j] = resultI;
				}
			}
			vMS[i][pivot] = 0; vMSI[i][pivot] = 0;
		}
		pivot++;
	} while (pivot < cols);
	double inverseR[dim][dim], inverseI[dim][dim];
	for (i = 0; i < cols; i++) {
		for (j = cols; j < cols * 2; j++) {
			inverseR[i][j - cols] = vMS[i][j];
			inverseI[i][j - cols] = vMSI[i][j];
		}
	}
	char report[DIM] = "";
	for (i = 0; i < cols; i++) {
		for (j = 0; j < lins; j++) {
			sprintf(report, "%s%G+%Gi ", report, inverseR[i][j], inverseI[i][j]);
		}
		sprintf(report, "%s\n", report);
	}
	puts(report);
	puts("Export result? (Yes -> 1 \\ No -> 0)");
	int option = (int)getValue();
	if (option == 1) {
		saveToReport(report);
	}
}