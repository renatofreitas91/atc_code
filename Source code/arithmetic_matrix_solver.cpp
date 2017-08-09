

#include "stdafx.h"

void arithmeticMatrixSolver() {
	fflush(NULL);
	double vMS[dim][dim], uMS[dim][dim], rMS[dim][dim], real = 0, vMSI[dim][dim], uMSI[dim][dim], rMSI[dim][dim], reI;
	int cols = 0, lins = 0, i = 0, j = 0, op = 0, op1 = 1;
	char express[DIM] = "";
	do {
		fflush(NULL);
		printf("\nWhat to do?\n\n");
		printf("Sum of Matrices -> 1\n");
		printf("Subtraction of Matrices -> 2\n");
		printf("Multiply a Matrix by a complex/real number -> 3\n");
		printf("Multiplication of Matrices -> 4\n");
		op = (int)getValue();
		puts("");
		switch (op) {
		case 1:
			printf("How many lines? ");
			lins = (int)getValue();
			printf("How many columns? ");
			cols = (int)getValue();
			printf("\nFirst matrix:\n");
			for (i = 0; i < lins; i++) {
				for (j = 0; j < cols; j++) {
					printf("Enter m1(%d,%d): ", i, j);
					getValue();
					vMS[i][j] = resultR;
					vMSI[i][j] = resultI;
				}
			}
			printf("\nSecond Matrix:\n");
			for (i = 0; i < lins; i++) {
				for (j = 0; j < cols; j++) {
					printf("Enter m2(%d,%d): ", i, j);
					getValue();
					uMS[i][j] = resultR;
					uMSI[i][j] = resultI;
				}
			}
			printf("\nMatrix sum:\n");
			fmsum(lins, cols, vMS, uMS, rMS, vMSI, uMSI, rMSI);
			break;
		case 2:
			printf("How many lines? ");
			lins = (int)getValue();
			printf("How many columns? ");
			cols = (int)getValue();
			printf("\nFirst Matrix:\n");
			for (i = 0; i < lins; i++) {
				for (j = 0; j < cols; j++) {
					printf("Enter m1(%d,%d): ", i, j);
					getValue();
					vMS[i][j] = resultR;
					vMSI[i][j] = resultI;
				}
			}
			printf("\nSecond Matrix:\n");
			for (i = 0; i < lins; i++) {
				for (j = 0; j < cols; j++) {
					printf("Enter m2(%d,%d): ", i, j);
					getValue();
					uMS[i][j] = resultR;
					uMSI[i][j] = resultI;
				}
			}
			printf("\nMatrix subtraction:\n");
			fmsubt(lins, cols, vMS, uMS, rMS, vMSI, uMSI, rMSI);
			break;
		case 3:
			printf("Matrix:\n\nHow many lines?\n");
			lins = (int)getValue();
			printf("How many columns?\n");
			cols = (int)getValue();
			printf("What's the real number?\n");
			getValue();
			real = resultR;
			reI = resultI;
			for (i = 0; i < lins; i++) {
				for (j = 0; j < cols; j++) {
					printf("Enter m(%d,%d)", i, j);
					getValue();
					vMS[i][j] = resultR;
					vMSI[i][j] = resultI;
				}
			}
			fmmulr(lins, cols, vMS, rMS, real, vMSI, rMSI, reI);
			break;
		case 4:
			int i, j, lins1, cols1, lins2, cols2;
			printf("First Matrix:\n\nHow many lines?\n");
			lins1 = (int)getValue();
			printf("How many columns?\n");
			cols1 = (int)getValue();
			for (i = 0; i < lins1; i++) {
				for (j = 0; j < cols1; j++) {
					printf("Enter m1(%d,%d)", i, j);
					getValue();
					vMS[i][j] = resultR;
					vMSI[i][j] = resultI;
				}
			}
			printf("\nSecond Matrix:\n\nHow many lines?\n");
			lins2 = (int)getValue();
			printf("How many columns?\n");
			cols2 = (int)getValue();
			for (i = 0; i < lins2; i++) {
				for (j = 0; j < cols2; j++) {
					printf("Enter m2(%d,%d)", i, j);
					getValue();
					uMS[i][j] = resultR;
					uMSI[i][j] = resultI;
				}
			}
			fmmulm(lins2, cols1, lins1, cols2, vMS, uMS, rMS, vMSI, uMSI, rMSI);
			break;
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
		printf("Error: The number of columns of first Matrix differs from the numbers of rows of second Matrix!");
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