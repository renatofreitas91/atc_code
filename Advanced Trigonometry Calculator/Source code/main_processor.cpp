
#include "stdafx.h"

char *buf = (char *)malloc(300);
char bufText[DIM] = "", OutputText[DIM] = "", prefixing[DIM] = "", errorText[DIM] = "", variablesText[DIM] = "", renamedVariablesText[DIM] = "", numSys[DIM] = "", timeText[DIM] = "";
int isFromMainProcessor = 0, numSysNum = 0, modeNum = 0, timeNum = 0, prefixNum = 0;


void main_processor(char math_expression[DIM]) {
	isFromMainProcessor = 1;
	char variable[DIM] = "";
	sprintf(buf, "");
	sprintf(OutputText, "");
	int tD = 0;
	char trigData[DIM] = "";
	int i = 0;
	sprintf(trigData, "%s", math_expression);
	for (tD = 0; trigData[tD] != '\0'; tD++) {
		fflush(NULL);
		char arithTrig[DIM] = "";
		varRename[0] = '\0';
		revariable[0] = '\0';
		validVar = 1;
		processingOK = 1;
		i = 0;
		int fl = 1, fr = 0;
		while (trigData[tD] != '\0' && trigData[tD] != ',' && tD < abs((int)strlen(trigData))) {
			arithTrig[i] = trigData[tD];
			i++;
			tD++;
		}
		arithTrig[i] = '\0';
		if (strlen(arithTrig) > 0) {
			math_processor(arithTrig);
			char newBuf[DIM] = "";
			sprintf(newBuf, "%s%s", buf, bufText);
			sprintf(buf, "%s", newBuf);
		}
		sprintf(expressionF, "%s", buf);
	}
	isFromMainProcessor = 0;
}

double math_processor(char expression[DIM]) {
	fflush(NULL);
	varRename[0] = '\0';
	revariable[0] = '\0';
	validVar = 1;
	processingOK = 1;
	sprintf(bufText, "");
	char arithTrig[DIM] = "";
	char variable[DIM] = "";
	char res = ' ';
	sprintf(arithTrig, "%s", expression);
	if (!solverRunning && !equationSolverRunning) {
		res = arithTrig[0];
		int i = 0;
		if (res == '+' || res == '-' || res == '/' || res == '*' || res == '^') {
			for (i = 0; arithTrig[i + 1] != '\0'; i++) {
				arithTrig[i] = arithTrig[i + 1];
			}
			arithTrig[i] = '\0';
		}
	}
	resultR = 0;
	resultI = 0;
	int var = 0;
	int v = 0;
	verified = 0;
	rasf = 0;
	valid = 1;
	validVar = 1;
	verify = 0;
	sprintf(varRename, "");
	sprintf(revariable, "");
	validVar = 1;
	processingOK = 1;
	resultR = 0;
	resultI = 0;
	validVar = 1;
	char variableFeedback[DIM] = "";
	if (isContained("=", arithTrig)) {
		var = 1;
		int i = 0;
		for (i = 0; arithTrig[i] != '=' && arithTrig[i] != '\0'; i++) {
			variable[i] = arithTrig[i];
		}
		variable[i] = '\0';
		i = 0;
		int hk = variableValidator(variable);
		if (hk == 1) {
			processVariable(revariable);
		}
		if (hk == 2) {
			sprintf(variableFeedback, "\n==> Your variable was renamed to \"%s\". <==\n\n",
				revariable);
		}
		if (hk == 0) {
			sprintf(variableFeedback,
				"\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
			var = 0;
		}
		char toReplace[DIM] = "";
		sprintf(toReplace, "%s=", variable);
		replace(toReplace, "", arithTrig);
		sprintf(arithTrig, "%s", expressionF);
	}
	sprintf(arithTrig, "%s", arithTrig);
	char dP[DIM] = "", bP[DIM] = "", oP[DIM] = "", hP[DIM] = "";
	int dp = -1, bp = -1, op = -1, hp = -1, r = 0;
	char places[DIM] = "";
	while ((arithTrig[0] == 'd' && arithTrig[1] == 'p' ||
		arithTrig[0] == 'b' && arithTrig[1] == 'p' ||
		arithTrig[0] == 'o' && arithTrig[1] == 'p' ||
		arithTrig[0] == 'h' && arithTrig[1] == 'p') && arithTrig[r] != '\0' &&
		r < abs((int)strlen(arithTrig))) {
		if (arithTrig[0] == 'd' && arithTrig[1] == 'p') {
			r = 2;
			while ((arithTrig[r] == 'd' && arithTrig[r + 1] == 'p') == false &&
				arithTrig[r] != '\0') {
				dP[r - 2] = arithTrig[r];
				r++;
			}
			dP[r - 2] = '\0';
			if (arithTrig[r] != '\0') {
				if (isFromMainProcessor == 1) {
					isFromMainProcessor = 0;
					dp = (int)math_processor(dP);
					isFromMainProcessor = 1;
				}
				r = r + 2;
				int b = 0;
				for (b = 0; arithTrig[b] != '\0'; b++) {
					arithTrig[b] = arithTrig[b + r];
				}
			}
			else {
				dp = 10000;
				nPlaces = dp;
			}
		}
		if (arithTrig[0] == 'b' && arithTrig[1] == 'p') {
			r = 2;
			while ((arithTrig[r] == 'b' && arithTrig[r + 1] == 'p') == false &&
				arithTrig[r] != '\0') {
				bP[r - 2] = arithTrig[r];
				r++;
			}
			bP[r - 2] = '\0';
			if (arithTrig[r] != '\0') {
				if (isFromMainProcessor == 1) {
					isFromMainProcessor = 0;
					bp = (int)math_processor(bP);
					isFromMainProcessor = 1;
				}
				r = r + 2;
				int b = 0;
				for (b = 0; arithTrig[b] != '\0'; b++) {
					arithTrig[b] = arithTrig[b + r];
				}
			}
			else {
				bp = 1000;
				nPlaces = bp;
			}
		}
		if (arithTrig[0] == 'o' && arithTrig[1] == 'p') {
			r = 2;
			while ((arithTrig[r] == 'o' && arithTrig[r + 1] == 'p') == false &&
				arithTrig[r] != '\0') {
				oP[r - 2] = arithTrig[r];
				r++;
			}
			oP[r - 2] = '\0';
			if (arithTrig[r] != '\0') {
				op = (int)math_processor(oP);
				if (isFromMainProcessor == 1) {
					isFromMainProcessor = 0;
					op = (int)math_processor(oP);
					isFromMainProcessor = 1;
				}
				r = r + 2;
				int b = 0;
				for (b = 0; arithTrig[b] != '\0'; b++) {
					arithTrig[b] = arithTrig[b + r];
				}
			}
			else {
				op = 8000;
				nPlaces = op;
			}
		}
		if (arithTrig[0] == 'h' && arithTrig[1] == 'p') {
			r = 2;
			while ((arithTrig[r] == 'h' && arithTrig[r + 1] == 'p') == false &&
				arithTrig[r] != '\0') {
				hP[r - 2] = arithTrig[r];
				r++;
			}
			hP[r - 2] = '\0';
			if (arithTrig[r] != '\0') {
				if (isFromMainProcessor == 1) {
					isFromMainProcessor = 0;
					hp = (int)math_processor(hP);
					isFromMainProcessor = 1;
				}
				r = r + 2;
				int b = 0;
				for (b = 0; arithTrig[b] != '\0'; b++) {
					arithTrig[b] = arithTrig[b + r];
				}
			}
			else {
				hp = 16000;
				nPlaces = hp;
			}
		}
	}
	sprintf(expressionF, "");
	synTest = 0;
	if ((equationSolverRunning == false && solverRunning == false) || !isEqual(saveArithTrig, arithTrig)) {
		sprintf(saveArithTrig, "%s", arithTrig);
		manageExpression(arithTrig, 0, 0, 1);
		sprintf(arithTrig, "%s", expressionF);
		sprintf(saveExpressionFF, "%s", expressionF);
		synTest = 0;
		verify = dataVerifier(arithTrig, 0, 0, 1, 1);
	}
	else {
		if ((equationSolverRunning || solverRunning)) {
			sprintf(arithTrig, "%s", saveExpressionFF);
			verify = 1;
		}
	}
	if (verify == 1) {
		verified = 1;
		resultR = 0;
		resultI = 0;
		initialProcessor(arithTrig, resultR);
		if (resultR == 0 && solverRunning == false && equationSolverRunning == false) {
			initialProcessor(arithTrig, resultR);
		}
		if (resultR == 0 && solverRunning == false && equationSolverRunning == false) {
			initialProcessor(arithTrig, resultR);
		}
		if (resultR == 0 && solverRunning == false && equationSolverRunning == false) {
			initialProcessor(arithTrig, resultR);
		}
		sprintf(arithTrig, "");
		if (res == '+') {
			sum(ansRV, ansIV, resultR, resultI);
		}
		if (res == '-') {
			subtraction(ansRV, ansIV, resultR, resultI);
		}
		if (res == '/') {
			division(ansRV, ansIV, resultR, resultI);
		}
		if (res == '*') {
			multiplication(ansRV, ansIV, resultR, resultI);
		}
		if (res == '^') {
			exponentiation(ansRV, ansIV, resultR, resultI, 1);
		}
		if (isFromMainProcessor == 1) {
			if (dp == -1) {
				if (resultR > 0 && resultI > 0) {
					sprintf(bufText, "%s#%d=%G+%Gi\n", bufText, rf, resultR, resultI);
				}
				else {
					if (resultR > 0 && resultI < 0) {
						sprintf(bufText, "%s#%d=%G%Gi\n", bufText, rf, resultR, resultI);
					}
					else {
						if (resultR < 0 && resultI > 0) {
							sprintf(bufText, "%s#%d=%G+%Gi\n", bufText, rf, resultR, resultI);
						}
						else {
							if (resultR < 0 && resultI < 0) {
								sprintf(bufText, "%s#%d=%G%Gi\n", bufText, rf, resultR, resultI);
							}
							else {
								if (resultR == 0 && resultI == 0) {
									sprintf(bufText, "%s#%d=%G\n", bufText, rf, resultR);
								}
								else {
									if (resultR == 0 && resultI != 0) {
										sprintf(bufText, "%s#%d=%Gi\n", bufText, rf, resultI);
									}
									else {
										if (resultR != 0 && resultI == 0) {
											sprintf(bufText, "%s#%d=%G\n", bufText, rf, resultR);
										}
										else {
											sprintf(bufText, "%s#%d=%G+%Gi\n", bufText, rf, resultR,
												resultI);
										}
									}
								}
							}
						}
					}
				}
			}
			else {

				char ansFormatted[DIM] = "";
				if (resultR > 0 && resultI > 0) {
					sprintf(dP, "#%d=%%.%df+%%.%dfi\n", rf, dp, dp);

					sprintf(ansFormatted, dP, resultR, resultI);

				}
				if (resultR > 0 && resultI < 0) {
					sprintf(dP, "#%d=%%.%df%%.%dfi\n", rf, dp, dp);
					sprintf(ansFormatted, dP, resultR, resultI);
				}
				if (resultR < 0 && resultI > 0) {
					sprintf(dP, "#%d = %%.%df+%%.%dfi\n", rf, dp, dp);
					sprintf(ansFormatted, dP, resultR, resultI);
				}
				if (resultR < 0 && resultI < 0) {
					sprintf(dP, "#%d=%%.%df%%.%dfi\n", rf, dp, dp);
					sprintf(ansFormatted, dP, resultR, resultI);

				}
				if (resultR == 0 && resultI == 0) {
					sprintf(dP, "#%d=%%.%df\n", rf, dp);
					sprintf(ansFormatted, dP, resultR);

				}
				if (resultR == 0 && resultI != 0) {
					sprintf(dP, "#%d=%%.%dfi\n", rf, dp);
					sprintf(ansFormatted, dP, resultI);

				}
				if (resultR != 0 && resultI == 0) {
					sprintf(dP, "#%d=%%.%df\n", rf, dp);
					sprintf(ansFormatted, dP, resultR);
				}
				sprintf(bufText, "%s%s", bufText, ansFormatted);
			}
			ans[rf] = resultR;
			ansI[rf] = resultI;
			ansRV = resultR;
			ansIV = resultI;
			rf++;
			if (var == 1) {
				variableController(revariable, resultR);

			}
			sprintf(bufText, "%s%s", variableFeedback, bufText);
			char numSysText[DIM] = "";
			if (numSysNum == 1 || bp != -1 || op != -1 || hp != -1) {
				char syst[DIM] = "";
				sprintf(syst, "%G", resultR);
				if (isEqual(syst, "-NAN")) {
					sprintf(numSysText, "%s", numSysText);
					sprintf(numSysText, "%sIn binary=-NAN\n", numSysText);
					sprintf(numSysText, "%sIn octal=-NAN\n", numSysText);
					sprintf(numSysText, "%sIn hexadecimal=-NAN\n", numSysText);
				}
				else {
					if (syst[0] == 'I' && syst[1] == 'N' && syst[2] == 'F') {
						sprintf(numSysText, "%s", numSysText);
						sprintf(numSysText, "%sIn binary=INF\n", numSysText);
						sprintf(numSysText, "%sIn octal=INF\n", numSysText);
						sprintf(numSysText, "%sIn hexadecimal=INF\n", numSysText);
					}
					else {
						if (syst[0] == '-' && syst[1] == 'I' && syst[2] == 'N' && syst[3] == 'F') {
							puts("");
							sprintf(numSysText, "%sIn binary=-INF\n", numSysText);
							sprintf(numSysText, "%sIn octal=-INF\n", numSysText);
							sprintf(numSysText, "%sIn hexadecimal=-INF\n", numSysText);
						}
						else {
							if (resultR != 0 && resultI == 0 || resultR == 0 && resultI == 0) {
								sprintf(numSysText, "%s\nReal part:\n", numSysText);
								decimalToBinary(resultR, "history.txt", bp);
								sprintf(numSysText, "%s%s", numSysText, numSys);
								decimalToOctal(resultR, "history.txt", op);
								sprintf(numSysText, "%s%s", numSysText, numSys);
								decimalToHexadecimal(resultR, "history.txt", hp);
								sprintf(numSysText, "%s%s", numSysText, numSys);
							}
							else {
								if (resultR != 0 && resultI != 0) {
									sprintf(numSysText, "%s\nReal part:\n", numSysText);
									decimalToBinary(resultR, "history.txt", bp);
									sprintf(numSysText, "%s%s", numSysText, numSys);
									decimalToOctal(resultR, "history.txt", op);
									sprintf(numSysText, "%s%s", numSysText, numSys);
									decimalToHexadecimal(resultR, "history.txt", hp);
									sprintf(numSysText, "%s%s", numSysText, numSys);
									sprintf(numSysText, "%s\nImaginary part:\n", numSysText);
									decimalToBinary(resultI, "history.txt", bp);
									sprintf(numSysText, "%s%s", numSysText, numSys);
									decimalToOctal(resultI, "history.txt", op);
									sprintf(numSysText, "%s%s", numSysText, numSys);
									decimalToHexadecimal(resultI, "history.txt", hp);
									sprintf(numSysText, "%s%s", numSysText, numSys);
								}
								else {
									if (resultI != 0) {
										sprintf(numSysText, "%s\nImaginary part:\n", numSysText);
										decimalToBinary(resultI, "history.txt", bp);
										sprintf(numSysText, "%s%s", numSysText, numSys);
										decimalToOctal(resultI, "history.txt", op);
										sprintf(numSysText, "%s%s", numSysText, numSys);
										decimalToHexadecimal(resultI, "history.txt", hp);
										sprintf(numSysText, "%s%s", numSysText, numSys);
									}

								}
							}
						}
					}
				}
				sprintf(bufText, "%s\n%s", bufText, numSysText);
			}
			char prefixText[DIM] = "";
			if (prefixNum == 1) {
				char pref[DIM] = "";
				sprintf(pref, "%G", resultR);
				if (isEqual(pref, "-NAN")) {

					sprintf(prefixText, "%s=-NAN\n", prefixText);

				}
				else {
					if (pref[0] == 'I' && pref[1] == 'N' && pref[2] == 'F') {

						sprintf(prefixText, "%s=INF\n", prefixText);

					}
					else {
						if (pref[0] == '-' && pref[1] == 'I' && pref[2] == 'N' &&
							pref[3] == 'F') {
							sprintf(prefixText, "%s=-INF\n", prefixText);


						}
						else {
							sprintf(prefixText, "%s\nReal part:\n", prefixText);
							prefixDeterminator(resultR, "history.txt");
							sprintf(prefixText, "%s%s", prefixText, prefixing);
						}
					}
				}

				sprintf(pref, "%G", resultI);
				if (isEqual(pref, "-NAN(IND)")) {
					sprintf(prefixText, "%s=-NAN\n", prefixText);
				}
				else {
					if (pref[0] == 'I' && pref[1] == 'N' && pref[2] == 'F') {
						sprintf(prefixText, "%s=INF\n", prefixText);

					}
					else {
						if (pref[0] == '-' && pref[1] == 'I' && pref[2] == 'N' &&
							pref[3] == 'F') {
							sprintf(prefixText, "%s=-INF\n", prefixText);

						}
						else {
							sprintf(prefixText, "%s\nImaginary part:\n", prefixText);
							prefixDeterminator(resultI, "history.txt");
							sprintf(prefixText, "%s%s", prefixText, prefixing);
						}
					}
				}

				sprintf(bufText, "%s\n%s", bufText, prefixText);
			}
			if (timeNum == 1) {
				Clock(1);
				sprintf(bufText, "%s\n%s", bufText, timeText);
			}
		}
	}
	else {
		sprintf(bufText, "%s%s\n\nError in syntax\n\n%s\n", bufText, errorText, expression);
	}
	sprintf(expressionF, "%s", bufText);
	return resultR;
}

void print(char data[DIM]) {
	sprintf(OutputText, "%s\n%s", OutputText, data);
}