

#include "stdafx.h"
#include "calc.h"
double X_k_R[dime], X_k_I[dime];

void sinc(double x, double y) {
	if (x == 0.0 && y == 0.0) {
		resultR = 1.0; resultI = 0;
	}
	else {
		if (x != 0.0 || y != 0.0) {
			complex_sin(M_PI*x, M_PI*y);
			division(resultR, resultI, M_PI*x, M_PI*y);
		}
		else {
			if (rasf > 0.0) {
				printf("\nError in function domain.\n\n ==> For normalized sinc function the valid domain is [-INF, INF].\n\n");
				printf(" ==> Your function argument: ");
				complexNumber(x, y);
			}
		}
	}
}

void fft(char values[DIM]) {
	double xR[dime], xI[dime];
	int initialCountSplits = 0;
	char saveSplitResult[200][200];
	int i = 0;
	if (countSplits > 0) {
		initialCountSplits = countSplits;
		while (i < countSplits) {
			sprintf(saveSplitResult[i], "%s", splitResult[i]);
			sprintf(splitResult[i], "");
			i++;
		}
	}
	countSplits = countOccurrences("\\", values);
	int N = countSplits + 1;
	split("\\", values);
	i = 0;
	char value[DIM][DIM];
	while (i <= countSplits) {
		sprintf(value[i], "%s", splitResult[i]);
		i++;
	}
	i = 0;
	while (i <= countSplits) {
		solveMath(value[i]);
		xR[i] = resultR; xI[i] = resultI;
		i++;
	}
	int k = 0;
	if (N % 2 == 0) {
		double SummatoryR = 0, SummatoryI = 0;
		int m = 0;
		k = 0;
		double exponent = 0, DFT_EvenR[dime], DFT_OddR[dime], DFT_EvenI[dime], DFT_OddI[dime];
		while (k <= N / 2) {
			m = 0;
			SummatoryR = 0; SummatoryI = 0;
			while (m <= N / 2) {
				exponent = ((-1 * 2 * M_PI) / (N / 2))*m*k;
				exponentiation(M_E, 0.0, 0.0, exponent, 1);
				multiplication(xR[2 * m], xI[2 * m], resultR, resultI);
				sum(SummatoryR, SummatoryI, resultR, resultI);
				SummatoryR = resultR; SummatoryI = resultI;
				m++;
			}
			DFT_EvenR[k] = SummatoryR; DFT_EvenI[k] = SummatoryI;
			m = 0;
			SummatoryR = 0; SummatoryI = 0;
			while (m <= N / 2) {
				exponent = ((-1 * 2 * M_PI) / (N / 2))*m*k;
				exponentiation(M_E, 0.0, 0.0, exponent, 1);
				multiplication(xR[2 * m + 1], xI[2 * m + 1], resultR, resultI);
				sum(SummatoryR, SummatoryI, resultR, resultI);
				SummatoryR = resultR; SummatoryI = resultI;
				m++;
			}
			DFT_OddR[k] = SummatoryR; DFT_OddI[k] = SummatoryI;
			exponent = ((-1 * 2 * M_PI) / N)*k;
			exponentiation(M_E, 0.0, 0.0, exponent, 1);
			double factoredR = resultR, factoredI = resultI;
			multiplication(factoredR, factoredI, DFT_OddR[k], DFT_OddI[k]);
			double OddR = resultR, OddI = resultI;
			sum(DFT_EvenR[k], DFT_EvenI[k], OddR, OddI);
			X_k_R[k] = resultR; X_k_I[k] = resultI;
			subtraction(DFT_EvenR[k], DFT_EvenI[k], OddR, OddI);
			X_k_R[k + N / 2] = resultR; X_k_I[k + N / 2] = resultI;
			k++;
		}
	}
	else {
		double SummatoryR = 0, SummatoryI = 0;
		int n = 0;
		k = 0;
		double exponent = 0;
		while (k <= N - 1) {
			n = 0;
			SummatoryR = 0; SummatoryI = 0;
			while (n <= N - 1) {
				exponent = ((-1 * 2 * M_PI) / N)*n*k;
				exponentiation(M_E, 0.0, 0.0, exponent, 1);
				multiplication(xR[n], xI[n], resultR, resultI);
				sum(SummatoryR, SummatoryI, resultR, resultI);
				SummatoryR = resultR; SummatoryI = resultI;
				n++;
			}
			X_k_R[k] = SummatoryR;  X_k_I[k] = SummatoryI;
			k++;
		}
	}
	if (!fromEquationSolver) {
		k = 0;
		puts("\n");
		double rootR = 0, rootI = 0;
		int rootIndex = 0;
		sprintf(answers, "");
		while (k < N) {
			rootR = X_k_R[k];
			rootI = X_k_I[k];
			rootIndex = k;
			if (abs(rootR) < 1E-6) {
				rootR = 0;
			}
			if (abs(rootI) < 1E-6) {
				rootI = 0;
			}
			if (rootR > 0 && rootI > 0) {
				sprintf(answers, "%sX[%d]=%f+%fi\n", answers, rootIndex, rootR, rootI);
			}
			else {
				if (rootR > 0 && rootI < 0) {
					sprintf(answers, "%sX[%d]=%f%fi\n", answers, rootIndex, rootR, rootI);
				}
				else {
					if (rootR < 0 && rootI > 0) {
						sprintf(answers, "%sX[%d]=%f+%fi\n", answers, rootIndex, rootR, rootI);
					}
					else {
						if (rootR < 0 && rootI < 0) {
							sprintf(answers, "%sX[%d]=%f%fi\n", answers, rootIndex, rootR, rootI);
						}
						else {
							if (rootR == 0 && rootI == 0) {
								sprintf(answers, "%sX[%d]=%f\n", answers, rootIndex, rootR);
							}
							else {
								if (rootR == 0 && rootI != 0) {
									sprintf(answers, "%sX[%d]=%fi\n", answers, rootIndex, rootI);
								}
								else {
									if (rootR != 0 && rootI == 0) {
										sprintf(answers, "%sX[%d]=%f\n", answers, rootIndex,
											rootR);
									}
									else {
										sprintf(answers, "%sX[%d]=%f+%fi\n", answers, rootIndex,
											rootR, rootI);
									}
								}
							}
						}
					}
				}
			}
			k++;
		}
		replaceTimes = 0;
		if (isContained(".000000", answers)) {
			replace(".000000", "", answers);
			sprintf(answers, "%s", expressionF);
		}
		puts(answers);
		sprintf(answers, "");
		puts("\n");
	}
	i = 0;
	countSplits = initialCountSplits;
	while (i < countSplits) {
		sprintf(splitResult[i], "%s", saveSplitResult[i]);
		i++;
	}
}

void ifft(char values[DIM]) {
	double XR[dime], XI[dime];
	int initialCountSplits = 0;
	char saveSplitResult[200][dime];
	int i = 0;
	if (countSplits > 0) {
		initialCountSplits = countSplits;
		while (i < countSplits) {
			sprintf(saveSplitResult[i], "%s", splitResult[i]);
			sprintf(splitResult[i], "");
			i++;
		}
	}
	countSplits = countOccurrences("\\", values);
	int N = countSplits + 1;
	split("\\", values);
	i = 0;
	char value[DIM][DIM];
	while (i <= countSplits) {
		sprintf(value[i], "%s", splitResult[i]);
		i++;
	}
	i = 0;
	while (i <= countSplits) {
		solveMath(value[i]);
		XR[i] = resultR; XI[i] = resultI;
		i++;
	}
	double x_k_R[dime], x_k_I[dime];
	int k = 0;
	double SummatoryR = 0, SummatoryI = 0;
	int n = 0;
	k = 0;
	double exponent = 0;
	while (k <= N - 1) {
		n = 0;
		SummatoryR = 0; SummatoryI = 0;
		while (n <= N - 1) {
			exponent = (2 * M_PI*n*k) / N;
			exponentiation(M_E, 0.0, 0.0, exponent, 1);
			multiplication(XR[n], XI[n], resultR, resultI);
			sum(SummatoryR, SummatoryI, resultR, resultI);
			SummatoryR = resultR; SummatoryI = resultI;
			n++;
		}
		multiplication(1 / (double)N, 0.0, SummatoryR, SummatoryI);
		x_k_R[k] = resultR;  x_k_I[k] = resultI;
		k++;
	}

	k = 0;
	puts("\n");
	double rootR = 0, rootI = 0;
	int rootIndex = 0;
	sprintf(answers, "");
	while (k < N) {
		rootR = x_k_R[k];
		rootI = x_k_I[k];
		rootIndex = k;
		if (abs(rootR) < 1E-6) {
			rootR = 0;
		}
		if (abs(rootI) < 1E-6) {
			rootI = 0;
		}
		if (rootR > 0 && rootI > 0) {
			sprintf(answers, "%sx[%d]=%f+%fi\n", answers, rootIndex, rootR, rootI);
		}
		else {
			if (rootR > 0 && rootI < 0) {
				sprintf(answers, "%sx[%d]=%f%fi\n", answers, rootIndex, rootR, rootI);
			}
			else {
				if (rootR < 0 && rootI > 0) {
					sprintf(answers, "%sx[%d]=%f+%fi\n", answers, rootIndex, rootR, rootI);
				}
				else {
					if (rootR < 0 && rootI < 0) {
						sprintf(answers, "%sx[%d]=%f%fi\n", answers, rootIndex, rootR, rootI);
					}
					else {
						if (rootR == 0 && rootI == 0) {
							sprintf(answers, "%sx[%d]=%f\n", answers, rootIndex, rootR);
						}
						else {
							if (rootR == 0 && rootI != 0) {
								sprintf(answers, "%sx[%d]=%fi\n", answers, rootIndex, rootI);
							}
							else {
								if (rootR != 0 && rootI == 0) {
									sprintf(answers, "%sx[%d]=%f\n", answers, rootIndex,
										rootR);
								}
								else {
									sprintf(answers, "%sx[%d]=%f+%fi\n", answers, rootIndex,
										rootR, rootI);
								}
							}
						}
					}
				}
			}
		}
		k++;
	}
	replaceTimes = 0;
	if (isContained(".000000", answers)) {
		replace(".000000", "", answers);
		sprintf(answers, "%s", expressionF);
	}
	puts(answers);
	sprintf(answers, "");
	puts("\n");
	i = 0;
	countSplits = initialCountSplits;
	while (i < countSplits) {
		sprintf(splitResult[i], "%s", saveSplitResult[i]);
		i++;
	}
}