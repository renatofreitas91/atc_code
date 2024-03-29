

#include "stdafx.h"

void arithmeticMatrixSolver() {
	int op = 0, op1 = 1;
	char express[DIM] = "";
	do {
		char matrix[DIM] = "";
		int mIndex = 0, ff = 0, lins = 1, cols = 1, lins1 = 1, cols1 = 1, saveCols = -1, saveCols1 = -1, errorCols = 0, errorCols1 = 0, i = 0, j = 0;
		double vMS[dime][dime], uMS[dime][dime], vMSI[dime][dime], uMSI[dime][dime], rMSI[dime][dime], rMS[dime][dime];
		double 	real = 0, reI;
		fflush(NULL);
		puts("\nWhat to do?");
		puts("Sum of Matrices -> 1");
		puts("Subtraction of Matrices -> 2");
		puts("Multiply a Matrix by a complex/real number -> 3");
		puts("Multiplication of Matrices -> 4");
		puts("Transpose a Matrix -> 5");
		puts("Inverse a Matrix -> 6");
		puts("Power a Matrix -> 7");
		puts("Matrix Rank -> 8");
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
						if (saveCols != cols && saveCols != -1) {
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
						if (saveCols1 != cols1 && saveCols1 != -1) {
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
			if (lins == lins1 && cols == cols1 && errorCols == 0 && errorCols1 == 0) {
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
						if (saveCols != cols && saveCols != -1) {
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
						if (saveCols1 != cols1 && saveCols1 != -1) {
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
			if (lins == lins1 && cols == cols1 && errorCols == 0 && errorCols1 == 0) {
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
						if (saveCols != cols && saveCols != -1) {
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
						if (saveCols != cols && saveCols != -1) {
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
						if (saveCols1 != cols1 && saveCols1 != -1) {
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
						if (saveCols != cols && saveCols != -1) {
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
				fmtranspose(lins, cols, vMS, vMSI, rMS, rMSI);
			}
			else {
				puts("\nError: The numbers of columns per line in the matrix is not the same in the lines.\n");
			}
		}
		if (op == 6) {
			printf("\nMatrix:\n");
			gets_s(matrix);
			int mIndex = 0, ff = 0, lins = 1, cols = 1, lins1 = 1, cols1 = 1, saveCols = -1, saveCols1 = -1, errorCols = 0, errorCols1 = 0, i = 0, j = 0;
			double vMS[dime][dime], vMSI[dime][dime];
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
						if (saveCols != cols && saveCols != -1) {
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
			if (errorCols == 0 && cols == lins && cols >= 2) {
				char detChecker[DIM] = "";
				sprintf(detChecker, "det(%s)", matrix);
				atcProg(detChecker);
				if (resultR == 0 && resultI == 0) {
					printf("\nError: Your matrix does not have a inverse.\n--> det(%s)=0\n\n", matrix);
				}
				else {
					printf("\nMatrix Inverse:\n");
					fminverse(lins, cols, vMS, vMSI, rMS, rMSI);
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
		if (op == 7) {
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
						if (saveCols != cols && saveCols != -1) {
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
			if (errorCols == 1) {
				puts("\nError: The numbers of columns per line in the matrix is not the same in the lines.\n");
			}
			else {
				printf("\nPower:\n");
				int power = (int)getValue();
				if (power < 2) {
					puts("\nError: The power must be a positive integer >=2.\n");
				}
				else {
					fmpowerm(vMS, vMSI, rMS, rMSI, power, lins, cols);
				}
			}
		}
		if (op == 8) {
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
						if (saveCols != cols && saveCols != -1) {
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
				printf("\nMatrix Rank:\n");
				fmrank(lins, cols, vMS, vMSI);
			}
			else {
				puts("\nError: The numbers of columns per line in the matrix is not the same in the lines.\n");
			}
		}
		if (op < 1 || op>8) {
			puts("\n\nError: Incorrect option id.\n\n");
		}
		fflush(NULL);
		op1 = -1;
		while (op1 != 0 && op1 != 1) {
			I_O = true;
			printf("\nContinue? (Yes -> 1 / No -> 0)\n");
			op1 = (int)getValue();
		}
	} while (op1 != 0);
}

void fmsum(int lins, int cols, double v[dime][dime], double u[dime][dime], double r[dime][dime], double vI[dime][dime], double uI[dime][dime], double rI[dime][dime]) {
	int i, j;
	char report[DIM] = "";
	for (i = 0; i < lins; i++) {
		for (j = 0; j < cols; j++) {
			sum(v[i][j], vI[i][j], u[i][j], uI[i][j]);
			r[i][j] = resultR;
			rI[i][j] = resultI;
			convertComplex2Exponential(resultR, resultI);
			sprintf(report, "%s%s+%si ", report, respR, respI);
		}
		sprintf(report, "%s\n", report);
	}
	if (matrixMode == 0) {
		puts(report);
		int option = -1;
		while (option != 0 && option != 1) {
			I_O = true;
			puts("Export result? (Yes -> 1 \\ No -> 0)");
			option = (int)getValue();
		}
		if (option == 1) {
			saveToReport(report);
		}
	}
}

void fmsubt(int lins, int cols, double v[dime][dime], double u[dime][dime], double r[dime][dime], double vI[dime][dime], double uI[dime][dime], double rI[dime][dime]) {
	int i, j;
	char report[DIM] = "";
	for (i = 0; i < lins; i++) {
		for (j = 0; j < cols; j++) {
			subtraction(v[i][j], vI[i][j], u[i][j], uI[i][j]);
			r[i][j] = resultR;
			rI[i][j] = resultI;
			convertComplex2Exponential(resultR, resultI);
			sprintf(report, "%s%s+%si ", report, respR, respI);
		}
		sprintf(report, "%s\n", report);
	}
	if (matrixMode == 0) {
		puts(report);
		int option = -1;
		while (option != 0 && option != 1) {
			I_O = true;
			puts("Export result? (Yes -> 1 \\ No -> 0)");
			option = (int)getValue();
		}
		if (option == 1) {
			saveToReport(report);
		}
	}
}

void fmmulr(int lins, int cols, double v[dime][dime], double r[dime][dime], double re, double vI[dime][dime], double rI[dime][dime], double reI) {
	int i, j;
	char report[DIM] = "";
	for (i = 0; i < lins; i++) {
		for (j = 0; j < cols; j++) {
			multiplication(v[i][j], vI[i][j], re, reI);
			r[i][j] = resultR;
			rI[i][j] = resultI;
			convertComplex2Exponential(resultR, resultI);
			sprintf(report, "%s%s+%si ", report, respR, respI);
		}
		sprintf(report, "%s\n", report);
	}
	if (matrixMode == 0) {
		puts(report);
		int option = -1;
		while (option != 0 && option != 1) {
			I_O = true;
			puts("Export result? (Yes -> 1 \\ No -> 0)");
			option = (int)getValue();
		}
		if (option == 1) {
			saveToReport(report);
		}
	}
}

void fmmulm(int lins2, int cols1, int lins1, int cols2, double v[dime][dime], double u[dime][dime], double r[dime][dime], double vI[dime][dime], double uI[dime][dime], double rI[dime][dime]) {
	int k, i, j;
	char report[DIM] = "";
	double prod, prodI;
	if (lins2 != cols1) {
		printf("\nError: The number of columns of first Matrix differs from the number of rows of second Matrix.\n");
	}
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
				convertComplex2Exponential(r[i][k], rI[i][k]);
				sprintf(report, "%s%s+%si ", report, respR, respI);
			}
			sprintf(report, "%s\n", report);
		}
		if (matrixMode == 0) {
			puts(report);
			int option = -1;
			while (option != 0 && option != 1) {
				I_O = true;
				puts("Export result? (Yes -> 1 \\ No -> 0)");
				option = (int)getValue();
			}
			if (option == 1) {
				saveToReport(report);
			}
		}
	}
}

boolean fmdivm(int lins2, int cols1, int lins1, int cols2, double v[dime][dime], double u[dime][dime], double vI[dime][dime], double uI[dime][dime]) {
	int k, i;
	boolean  divisible = false;
	char report[DIM] = "";
	if (cols1 != cols2)
		printf("\nError: The number of columns of first Matrix differs from the numbers of columns of second Matrix.\n");
	else
		if (lins1 != lins2)
			printf("\nError: The number of lines of first Matrix differs from the numbers of lines of second Matrix.\n");
		else {
			int countEquals = 0;
			char value[DIM] = "";
			char * pointer;
			double quotientR = 0, quotientI = 0;
			for (i = 0; i < lins1; i++) {
				for (k = 0; k < cols1; k++) {
					if ((v[i][k] != 0 || vI[i][k] != 0) && (u[i][k] != 0 || uI[i][k] != 0)) {
						division(v[i][k], vI[i][k], u[i][k], uI[i][k]);
						sprintf(value, "%s", convert2Exponential(resultR));
						resultR = strtod(value, &pointer);
						sprintf(value, "%s", convert2Exponential(resultI));
						resultI = strtod(value, &pointer);
						quotientR = resultR; quotientI = resultI;
						i = lins1;
						k = cols1;
					}
				}
			}
			for (i = 0; i < lins1; i++) {
				for (k = 0; k < cols1; k++) {
					if ((v[i][k] != 0 || vI[i][k] != 0) && (u[i][k] != 0 || uI[i][k] != 0)) {
						division(v[i][k], vI[i][k], u[i][k], uI[i][k]);
						sprintf(value, "%s", convert2Exponential(resultR));
						resultR = strtod(value, &pointer);
						sprintf(value, "%s", convert2Exponential(resultI));
						resultI = strtod(value, &pointer);
						if (resultR == quotientR && resultI == quotientI) {
							countEquals++;
						}
					}
					else {
						countEquals++;
					}
				}
			}
			if (countEquals == lins1 * cols1) {
				resultR = quotientR;
				resultI = quotientI;
				divisible = true;
				matrixMode = 2;
				return divisible;
			}
			return divisible;
		}
	return divisible;
}

void fmtranspose(int lins, int  cols, double vMS[dime][dime], double vMSI[dime][dime], double mTransposeR[dime][dime], double mTransposeI[dime][dime]) {
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
			convertComplex2Exponential(mTransposeR[i][j], mTransposeI[i][j]);
			sprintf(report, "%s%s+%si ", report, respR, respI);
		}
		sprintf(report, "%s\n", report);
	}
	if (matrixMode == 0) {
		puts(report);
		int option = -1;
		while (option != 0 && option != 1) {
			I_O = true;
			puts("Export result? (Yes -> 1 \\ No -> 0)");
			option = (int)getValue();
		}
		if (option == 1) {
			saveToReport(report);
		}
	}
}

void fmdeterminant(int lins, int  cols, double vMS[dime][dime], double vMSI[dime][dime]) {
	int multiplier = 0;
	do {
		double newMatrixR[dime][dime], newMatrixI[dime][dime];
		double lineMultipliedR[dime], lineMultipliedI[dime], lineResultR[dime], lineResultI[dime];
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
	check4Vector = 1;
	calcNow(matrix, 0, 0);
	if (strlen(matrixResult) > 0) {
		sprintf(expressionF, "%s", matrixResult);
		replaceTimes = 0;
		matrixMode = 1;
		if (isContained(":", expressionF)) {
			replace(":", "\\", expressionF);
		}
		if (isContained("*", expressionF)) {
			replace("*", ";", expressionF);
		}
		sprintf(matrix, "%s", expressionF);
	}
	int mIndex = 0, ff = 0, lins = 1, cols = 1, lins1 = 1, cols1 = 1, saveCols = -1, saveCols1 = -1, errorCols = 0, errorCols1 = 0, i = 0, j = 0;
	double vMS[dime][dime], vMSI[dime][dime];
	do {
		char value[DIM] = "";
		ff = 0;
		int imag = 0;
		while (matrix[mIndex] != '\\'&&matrix[mIndex] != ';'&&matrix[mIndex] != '\0') {
			if (matrix[mIndex] == ' ') {
				matrix[mIndex] = '+';
				imag = 1;
			}
			if (matrix[mIndex] == '-'&&matrix[mIndex - 1] == '+') {
				matrix[mIndex] = '_';
			}
			value[ff] = matrix[mIndex];
			ff++; mIndex++;
		}
		if (imag == 0) {
			value[ff] = '\0';
		}
		else {
			value[ff] = 'i';
			value[ff + 1] = '\0';
		}
		if (value[0] == '-') {
			value[0] = '_';
		}
		calcNow(value, 0, 0);
		vMS[i][j] = resultR;
		vMSI[i][j] = resultI;
		if (matrix[mIndex] == '\\') {
			j++; cols++;
		}
		else {
			if (matrix[mIndex] == ';' || matrix[mIndex] == '\0') {
				j = 0; i++;
				if (saveCols != cols && saveCols != -1) {
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
	matrixMode = 2;
}

void fminverse(int lins, int  cols, double vMS[dime][dime], double vMSI[dime][dime], double inverseR[dime][dime], double inverseI[dime][dime]) {
	int saveLins = lins, saveCols = cols;
	double vMSF[dime][dime], vMSIF[dime][dime];
	int i = 0, j = 0, one = saveCols, pivot = 0;
	for (i = 0; i < saveLins; i++) {
		for (j = 0; j < saveCols; j++) {
			vMSF[i][j] = vMS[i][j];
			vMSIF[i][j] = vMSI[i][j];
		}
	}


	i = 0; j = 0;
	while (i < saveCols) {
		for (j = saveCols; j < saveCols * 2; j++) {
			if (one == j) {
				vMSF[i][j] = 1; vMSIF[i][j] = 0;
			}
			else {
				vMSF[i][j] = 0; vMSIF[i][j] = 0;
			}
		}
		one++;
		i++;
	}
	do {
		i = pivot;
		while (vMSF[i][pivot] == 0 && vMSIF[i][pivot] == 0 && i < cols) {
			i++;
		}
		if (i == saveCols) {
			i = 0;
			while (vMSF[i][pivot] == 0 && vMSIF[i][pivot] == 0 && i < pivot) {
				i++;
			}
		}
		if (i != pivot) {
			int t = 0;
			double saveLineR[dime], saveLineI[dime];
			for (t = 0; t < saveCols * 2; t++) {
				saveLineR[t] = vMSF[i][t];
				saveLineI[t] = vMSIF[i][t];
			}
			for (t = 0; t < saveCols * 2; t++) {
				vMSF[i][t] = vMSF[pivot][t];
				vMSIF[i][t] = vMSIF[pivot][t];
			}
			for (t = 0; t < saveCols * 2; t++) {
				vMSF[pivot][t] = saveLineR[t];
				vMSIF[pivot][t] = saveLineI[t];
			}
		}
		i = pivot;
		double pivotR = 0, pivotI = 0;
		int linePivot = i, nextCol = linePivot + 1;
		if (i == pivot) {
			pivotR = vMSF[i][i]; pivotI = vMSIF[i][i];
			for (j = 0; j < saveCols * 2; j++) {
				division(vMSF[pivot][j], vMSIF[pivot][j], pivotR, pivotI);
				vMSF[pivot][j] = resultR; vMSIF[pivot][j] = resultI;
			}
		}
		for (i = linePivot + 1; i < saveCols; i++) {
			for (j = 0; j < saveCols + nextCol; j++) {
				multiplication(vMSF[i][pivot], vMSIF[i][pivot], vMSF[pivot][j], vMSIF[pivot][j]);
				subtraction(vMSF[i][j], vMSIF[i][j], resultR, resultI);
				if (j != pivot) {
					vMSF[i][j] = resultR; vMSIF[i][j] = resultI;
				}
			}
			vMSF[i][pivot] = 0; vMSIF[i][pivot] = 0;
		}
		for (i = 0; i < pivot; i++) {
			for (j = 0; j < saveCols + nextCol; j++) {
				multiplication(vMSF[i][pivot], vMSIF[i][pivot], vMSF[pivot][j], vMSIF[pivot][j]);
				subtraction(vMSF[i][j], vMSIF[i][j], resultR, resultI);
				if (j != pivot) {
					vMSF[i][j] = resultR; vMSIF[i][j] = resultI;
				}
			}
			vMSF[i][pivot] = 0; vMSIF[i][pivot] = 0;
		}
		pivot++;
	} while (pivot < saveCols);
	for (i = 0; i < saveLins; i++) {
		for (j = 0; j < saveCols; j++) {
			inverseR[i][j] = vMSF[i][j + saveCols];
			inverseI[i][j] = vMSIF[i][j + saveCols];
		}
	}
	if (matrixMode == 0) {
		char report[DIM] = "";
		for (i = 0; i < saveLins; i++) {
			for (j = 0; j < saveCols; j++) {
				convertComplex2Exponential(inverseR[i][j], inverseI[i][j]);
				sprintf(report, "%s%s+%si ", report, respR, respI);
			}
			sprintf(report, "%s\n", report);
		}
		puts(report);
		int option = -1;
		while (option != 0 && option != 1) {
			I_O = true;
			puts("Export result? (Yes -> 1 \\ No -> 0)");
			option = (int)getValue();
		}
		if (option == 1) {
			saveToReport(report);
		}
	}
}

void fmpowerm(double v[dime][dime], double vI[dime][dime], double r[dime][dime], double rI[dime][dime], int power, int lins, int cols) {
	int k = 0, i = 0, j = 0, negative = 0;
	char report[DIM] = "";
	double prod = 0, prodI = 0;
	double  u[dime][dime], uI[dime][dime];
	for (i = 0; i < lins; i++) {
		for (k = 0; k < cols; k++) {
			u[i][k] = v[i][k];
			uI[i][k] = vI[i][k];
		}
	}
	if (lins != cols) {
		printf("\nError: The number of columns and lines are not equal.\n");
	}
	else {
		if (matrixMode == 0) {
			printf("\nMatrix Power:\n");
		}
		if (power < 0) {
			power = power * -1;
			negative = 1;
		}
		if (negative == 1) {
			fminverse(lins, cols, v, vI, r, rI);
			for (i = 0; i < lins; i++) {
				for (k = 0; k < cols; k++) {
					v[i][k] = r[i][k];
					vI[i][k] = rI[i][k];
				}
			}
			for (i = 0; i < lins; i++) {
				for (k = 0; k < cols; k++) {
					u[i][k] = v[i][k];
					uI[i][k] = vI[i][k];
				}
			}
			negative = 0;
		}
		if (power > 1) {
			while (power > 1) {
				for (i = 0; i < lins; i++) {
					for (k = 0; k < cols; k++) {
						prod = 0; prodI = 0;
						for (j = 0; j < cols; j++) {
							multiplication(v[i][j], vI[i][j], u[j][k], uI[j][k]);
							prod = prod + resultR;
							prodI = prodI + resultI;
						}
						r[i][k] = prod;
						rI[i][k] = prodI;
					}
				}
				for (i = 0; i < lins; i++) {
					for (k = 0; k < cols; k++) {
						v[i][k] = r[i][k];
						vI[i][k] = rI[i][k];
					}
				}
				power--;
			}
		}
		else {
			if (power == 1) {
				for (i = 0; i < lins; i++) {
					for (k = 0; k < cols; k++) {
						r[i][k] = v[i][k];
						rI[i][k] = vI[i][k];
					}
				}
			}
			else {
				if (power == 0) {
					for (i = 0; i < lins; i++) {
						for (k = 0; k < cols; k++) {
							if (i == k) {
								r[i][k] = 1;
								rI[i][k] = 0;
							}
							else {
								r[i][k] = 0;
								rI[i][k] = 0;
							}
						}
					}
				}
			}
		}
		for (i = 0; i < lins; i++) {
			for (k = 0; k < cols; k++) {
				convertComplex2Exponential(r[i][k], rI[i][k]);
				sprintf(report, "%s%s+%si ", report, respR, respI);
			}
			sprintf(report, "%s\n", report);
		}
		if (matrixMode == 0) {
			puts(report);
			int option = -1;
			while (option != 0 && option != 1) {
				I_O = true;
				puts("Export result? (Yes -> 1 \\ No -> 0)");
				option = (int)getValue();
			}
			if (option == 1) {
				saveToReport(report);
			}
		}
	}
}

int fmrank(int lins, int cols, double vMS[dime][dime], double vMSI[dime][dime]) {
	int i = 0, j = 0, one = cols, pivot = 0;
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
			double saveLineR[dime], saveLineI[dime];
			for (t = 0; t < cols; t++) {
				saveLineR[t] = vMS[i][t];
				saveLineI[t] = vMSI[i][t];
			}
			for (t = 0; t < cols; t++) {
				vMS[i][t] = vMS[pivot][t];
				vMSI[i][t] = vMSI[pivot][t];
			}
			for (t = 0; t < cols; t++) {
				vMS[pivot][t] = saveLineR[t];
				vMSI[pivot][t] = saveLineI[t];
			}
		}
		i = pivot + 1;
		double pivotR = 0, pivotI = 0;
		while (i < lins) {
			division(vMS[i][pivot], vMSI[i][pivot], vMS[pivot][pivot], vMSI[pivot][pivot]);
			pivotR = resultR; pivotI = resultI;
			for (j = pivot; j < cols; j++) {
				multiplication(vMS[pivot][j], vMSI[pivot][j], pivotR, pivotI);
				subtraction(vMS[i][j], vMSI[i][j], resultR, resultI);
				vMS[i][j] = resultR; vMSI[i][j] = resultI;
			}
			i++;
		}
		pivot++;
	} while (pivot < lins - 1);
	int rank = 0;
	double sumR = 0, sumI;
	char report[DIM] = "";
	for (i = 0; i < lins; i++) {
		sumR = 0; sumI = 0;
		for (j = 0; j < cols; j++) {
			sum(vMS[i][j], vMSI[i][j], sumR, sumI);
			sumR = resultR; sumI = resultI;
			convertComplex2Exponential(vMS[i][j], vMSI[i][j]);
			sprintf(report, "%s%s+%si ", report, respR, respI);
		}
		if (sumR != 0 || sumI != 0) {
			rank++;
		}
		sprintf(report, "%s\n", report);
	}
	sprintf(report, "%s\nRank: %d\n", report, rank);
	if (matrixMode == 0) {
		puts(report);
		int option = -1;
		while (option != 0 && option != 1) {
			I_O = true;
			puts("Export result? (Yes -> 1 \\ No -> 0)");
			option = (int)getValue();
		}
		if (option == 1) {
			saveToReport(report);
		}
	}
	matrixMode = 2;
	return rank;
}

