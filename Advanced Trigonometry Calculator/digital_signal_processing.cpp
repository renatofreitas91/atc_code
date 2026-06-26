

#include "stdafx.h"
#include "calc.h"

template <typename T>
void sinc(T x, T y) {
	if (x == 0.0 && y == 0.0) {
		resultR = 1.0; resultI = 0;
	}
	else {
		if (x != 0.0 || y != 0.0) {
			complex_sin<T>(M_PI * x, M_PI * y);
			division<T>(precisionValueTo<T>(resultR), precisionValueTo<T>(resultI), M_PI * x, M_PI * y);
		}
		else {
			if (rasf > 0.0) {
				printf("\nError in function domain.\n\n ==> For normalized sinc function the valid domain is [-INF, INF].\n\n");
				printf(" ==> Your function argument: ");
				complexNumber<T>(x, y);
			}
		}
	}
}
template <typename T>
void fft(char* values) {
	int initialCountSplits = 0;
	char** saveSplitResult;
	saveSplitResult = new char* [DIMTWOD];
	for (int i = 0; i < DIMTWOD; ++i) {
		saveSplitResult[i] = getDynamicCharArray("", "saveSplitResult[i]");
	}

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
	T* X_k_R = getDynamicArray<T>(N), * X_k_I = getDynamicArray<T>(N);
	T* xR = getDynamicArray<T>(N); T* xI = getDynamicArray<T>(N);
	split("\\", values);
	i = 0;
	char** value;


	value = new char* [DIMTWOD];

	for (int i = 0; i < DIMTWOD; ++i) {
		value[i] = getDynamicCharArray("", "value[i]");
	}

	while (i <= countSplits) {
		sprintf(value[i], "%s", splitResult[i]);
		i++;
	}
	i = 0;
	while (i <= countSplits) {
		solveMath<T>(value[i]);
		xR[i] = precisionValueTo<T>(resultR); xI[i] = precisionValueTo<T>(resultI);
		i++;
	}
	int k = 0;
	if (N % 2 == 0) {
		T SummatoryR = 0, SummatoryI = 0;
		int m = 0;
		k = 0;
		int halfN = N / 2;
		T exponent = 0; T* DFT_EvenR = getDynamicArray<T>(halfN); T* DFT_OddR = getDynamicArray<T>(halfN); T* DFT_EvenI = getDynamicArray<T>(halfN); T* DFT_OddI = getDynamicArray<T>(halfN);
		while (k < halfN) {
			m = 0;
			SummatoryR = 0; SummatoryI = 0;
			while (m < halfN) {
				exponent = ((-1 * 2 * M_PI) / halfN) * m * k;
				exponentiation<T>(M_E, 0.0, 0.0, exponent, 1);
				multiplication<T>(xR[2 * m], xI[2 * m], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
				sum<T>(SummatoryR, SummatoryI, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
				SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
				m++;
			}
			DFT_EvenR[k] = SummatoryR; DFT_EvenI[k] = SummatoryI;
			m = 0;
			SummatoryR = 0; SummatoryI = 0;
			while (m < halfN) {
				exponent = ((-1 * 2 * M_PI) / halfN) * m * k;
				exponentiation<T>(M_E, 0.0, 0.0, exponent, 1);
				multiplication<T>(xR[2 * m + 1], xI[2 * m + 1], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
				sum<T>(SummatoryR, SummatoryI, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
				SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
				m++;
			}
			DFT_OddR[k] = SummatoryR; DFT_OddI[k] = SummatoryI;
			exponent = ((-1 * 2 * M_PI) / N) * k;
			exponentiation<T>(M_E, 0.0, 0.0, exponent, 1);
			T factoredR = precisionValueTo<T>(resultR), factoredI = precisionValueTo<T>(resultI);
			multiplication<T>(factoredR, factoredI, DFT_OddR[k], DFT_OddI[k]);
			T OddR = precisionValueTo<T>(resultR), OddI = precisionValueTo<T>(resultI);
			sum<T>(DFT_EvenR[k], DFT_EvenI[k], OddR, OddI);
			X_k_R[k] = precisionValueTo<T>(resultR); X_k_I[k] = precisionValueTo<T>(resultI);
			subtraction<T>(DFT_EvenR[k], DFT_EvenI[k], OddR, OddI);
			X_k_R[k + halfN] = precisionValueTo<T>(resultR); X_k_I[k + halfN] = precisionValueTo<T>(resultI);
			k++;
		}
		_delete(DFT_EvenR, "DFT_EvenR"); DFT_EvenR = nullptr;
		_delete(DFT_OddR, "DFT_OddR"); DFT_OddR = nullptr;
		_delete(DFT_EvenI, "DFT_EvenI"); DFT_EvenI = nullptr;
		_delete(DFT_OddI, "DFT_OddI"); DFT_OddI = nullptr;
	}
	else {
		T SummatoryR = 0, SummatoryI = 0;
		int n = 0;
		k = 0;
		T exponent = 0;
		while (k <= N - 1) {
			n = 0;
			SummatoryR = 0; SummatoryI = 0;
			while (n <= N - 1) {
				exponent = ((-1 * 2 * M_PI) / N) * n * k;
				exponentiation<T>(M_E, 0.0, 0.0, exponent, 1);
				multiplication<T>(xR[n], xI[n], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
				sum<T>(SummatoryR, SummatoryI, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
				SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
				n++;
			}
			X_k_R[k] = SummatoryR;  X_k_I[k] = SummatoryI;
			k++;
		}
	}
	if (!fromEquationSolver) {
		k = 0;
		puts("\n");
		T rootR = 0, rootI = 0;
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
				sprintf(answers, "%sX[%d]=%f+%fi\n", answers, rootIndex, precisionDisplayDouble(rootR), precisionDisplayDouble(rootI));
			}
			else {
				if (rootR > 0 && rootI < 0) {
					sprintf(answers, "%sX[%d]=%f%fi\n", answers, rootIndex, precisionDisplayDouble(rootR), precisionDisplayDouble(rootI));
				}
				else {
					if (rootR < 0 && rootI > 0) {
						sprintf(answers, "%sX[%d]=%f+%fi\n", answers, rootIndex, precisionDisplayDouble(rootR), precisionDisplayDouble(rootI));
					}
					else {
						if (rootR < 0 && rootI < 0) {
							sprintf(answers, "%sX[%d]=%f%fi\n", answers, rootIndex, precisionDisplayDouble(rootR), precisionDisplayDouble(rootI));
						}
						else {
							if (rootR == 0 && rootI == 0) {
								sprintf(answers, "%sX[%d]=%f\n", answers, rootIndex, precisionDisplayDouble(rootR));
							}
							else {
								if (rootR == 0 && rootI != 0) {
									sprintf(answers, "%sX[%d]=%fi\n", answers, rootIndex, precisionDisplayDouble(rootI));
								}
								else {
									if (rootR != 0 && rootI == 0) {
										sprintf(answers, "%sX[%d]=%f\n", answers, rootIndex,
											precisionDisplayDouble(rootR));
									}
									else {
										sprintf(answers, "%sX[%d]=%f+%fi\n", answers, rootIndex,
											precisionDisplayDouble(rootR), precisionDisplayDouble(rootI));
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

	_Delete(saveSplitResult, DIMTWOD, dime, "saveSplitResult[i]");
	saveSplitResult = nullptr;

	_Delete(value, DIMTWOD, dime, "value[i]");
	value = nullptr;
	_delete(xR, "xR"); xR = nullptr; _delete(xI, "xI"); xI = nullptr;
	_delete(X_k_R, "X_k_R"); X_k_R = nullptr; _delete(X_k_I, "X_k_I"); X_k_I = nullptr;
}
template <typename T>
void ifft(char* values) {
	int initialCountSplits = 0;
	char** saveSplitResult;
	saveSplitResult = new char* [DIMTWOD];

	for (int i = 0; i < DIMTWOD; ++i) {
		saveSplitResult[i] = getDynamicCharArray("", "saveSplitResult[i]");
	}
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
	T* XR = getDynamicArray<T>(N); T* XI = getDynamicArray<T>(N);
	split("\\", values);
	i = 0;
	char** value;
	value = new char* [DIMTWOD];

	for (int i = 0; i < DIMTWOD; ++i) {
		value[i] = getDynamicCharArray("", "value[i]");
	}

	while (i <= countSplits) {
		sprintf(value[i], "%s", splitResult[i]);
		i++;
	}
	i = 0;
	while (i <= countSplits) {
		solveMath<T>(value[i]);
		XR[i] = precisionValueTo<T>(resultR); XI[i] = precisionValueTo<T>(resultI);
		i++;
	}
	T* x_k_R = getDynamicArray<T>(N); T* x_k_I = getDynamicArray<T>(N);
	int k = 0;
	T SummatoryR = 0, SummatoryI = 0;
	int n = 0;
	k = 0;
	T exponent = 0;
	while (k <= N - 1) {
		n = 0;
		SummatoryR = 0; SummatoryI = 0;
		while (n <= N - 1) {
			exponent = (2 * M_PI * n * k) / N;
			exponentiation<T>(M_E, 0.0, 0.0, exponent, 1);
			multiplication<T>(XR[n], XI[n], precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
			sum<T>(SummatoryR, SummatoryI, precisionValueTo<T>(resultR), precisionValueTo<T>(resultI));
			SummatoryR = precisionValueTo<T>(resultR); SummatoryI = precisionValueTo<T>(resultI);
			n++;
		}
		multiplication<T>(1 / (T)N, 0.0, SummatoryR, SummatoryI);
		x_k_R[k] = precisionValueTo<T>(resultR);  x_k_I[k] = precisionValueTo<T>(resultI);
		k++;
	}

	k = 0;
	puts("\n");
	T rootR = 0, rootI = 0;
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
			sprintf(answers, "%sx[%d]=%f+%fi\n", answers, rootIndex, precisionDisplayDouble(rootR), precisionDisplayDouble(rootI));
		}
		else {
			if (rootR > 0 && rootI < 0) {
				sprintf(answers, "%sx[%d]=%f%fi\n", answers, rootIndex, precisionDisplayDouble(rootR), precisionDisplayDouble(rootI));
			}
			else {
				if (rootR < 0 && rootI > 0) {
					sprintf(answers, "%sx[%d]=%f+%fi\n", answers, rootIndex, precisionDisplayDouble(rootR), precisionDisplayDouble(rootI));
				}
				else {
					if (rootR < 0 && rootI < 0) {
						sprintf(answers, "%sx[%d]=%f%fi\n", answers, rootIndex, precisionDisplayDouble(rootR), precisionDisplayDouble(rootI));
					}
					else {
						if (rootR == 0 && rootI == 0) {
							sprintf(answers, "%sx[%d]=%f\n", answers, rootIndex, precisionDisplayDouble(rootR));
						}
						else {
							if (rootR == 0 && rootI != 0) {
								sprintf(answers, "%sx[%d]=%fi\n", answers, rootIndex, precisionDisplayDouble(rootI));
							}
							else {
								if (rootR != 0 && rootI == 0) {
									sprintf(answers, "%sx[%d]=%f\n", answers, rootIndex,
										precisionDisplayDouble(rootR));
								}
								else {
									sprintf(answers, "%sx[%d]=%f+%fi\n", answers, rootIndex,
										precisionDisplayDouble(rootR), precisionDisplayDouble(rootI));
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

	_Delete(saveSplitResult, DIMTWOD, dime, "saveSplitResult[i]");

	_Delete(value, DIMTWOD, DIM, "value[i]");
	_delete(XR, "XR"); XR = nullptr; _delete(XI, "XI"); XI = nullptr;
	_delete(x_k_R, "x_k_R"); x_k_R = nullptr; _delete(x_k_I, "x_k_I"); x_k_I = nullptr;
}

template void sinc<double>(double, double);
template void sinc<mp_float>(mp_float, mp_float);
template void fft<double>(char*);
template void fft<mp_float>(char*);
template void ifft<double>(char*);
template void ifft<mp_float>(char*);


void fft(char* values) { fft<double>(values); }
void ifft(char* values) { ifft<double>(values); }
