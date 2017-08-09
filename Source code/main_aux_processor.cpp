

#include "stdafx.h"

int rasf = 0, maxLength = 0;

double main_core(char arithTrig[DIM], char fTrig[DIM], FILE *fout, char path[DIM], double result1, double result2, int isFromMain) {
	fflush(NULL);
	verbose = 0;
	verified = 0;
	rasf = 0;
	resultR = 0; resultI;
	int txt = 0, command = 0, var = 0, str = 0, s = 0, i = 0, space = 0, v = 0, j = 0, valGet = 0, h = 0, run_del_space = 1, strIndex = 0;
	char variable[DIM] = "", getVarName[DIM] = "", getVar[DIM] = "", savefTrig[DIM] = "";
	cleanhistory = 0;
	txt = 0;
	valid = 1;
	validVar = 1;
	str = 0;
	nPlaces = 0;
	sprintf(savefTrig, "%s", fTrig);
	if (arithTrig[0] == 'g'&&arithTrig[1] == 'e'&&arithTrig[2] == 't'&&arithTrig[3] == '(') {
		i = 4;
		for (i = 4; arithTrig[i] != '\0'; i++) {
			if (arithTrig[i] == ')') {
				valGet = 1;
				break;
			}
		}
		if (valGet == 1) {
			h = 0;
			i = 4;
			while (arithTrig[i] != ')'&&arithTrig[i] != '\0') {
				getVarName[h] = arithTrig[i];
				h++; i++;
			}
			getVarName[h] = '\0';
			strIndex = 0;
			for (int ks = 0; getVarName[ks] != '\0'; ks++) {
				if (verifyNumber(getVarName[ks]) || verifyLetter(getVarName[ks])) {
					strIndex++;
				}
			}
			if (strIndex == strlen(getVarName)) {
				gets_s(getVar);
			}
			else {
				puts("\nTo create string variables only letters from latin alphabet and digits 0-9 can be used.\nTo create numerical variables only letters from latin alphabet can be used.");
				command = 1;
				arithTrig[0] = '\0';
			}
			sprintf(arithTrig, "%s=%s", getVarName, getVar);
			command = 0;
		}
		else {
			puts("\nError in syntax in get function.\n");
			command = 1;
			arithTrig[0] = '\0';
		}
	}
	variable[0] = '\0';
	for (i = 0; arithTrig[i] != '\0'; i++) {
		if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == ':'&&arithTrig[i + 1] == '\\') {
			txt = 1;
		}
	}
	for (i = 0; arithTrig[i] != '\0'; i++) {
		if (arithTrig[i] == '=') {
			var = 1;
			if (valGet == 1) {
				puts(" ");
			}
		}
		if (arithTrig[i] == '\"'&&arithTrig[strlen(arithTrig) - 1] == '\"'&&txt != 1) {
			str = 1;
		}
		else {
			if ((arithTrig[i - 6] == 'p'&&arithTrig[i - 5] == 'r'&&arithTrig[i - 4] == 'i'&&arithTrig[i - 3] == 'n'&&arithTrig[i - 2] == 't'&&arithTrig[i - 1] == '(') == true) {
				run_del_space = 0;
			}
		}
	}
	if (txt == 1) {
		int p = 0;
		char pathName[DIM] = "";
		if (var == 1) {
			var = 0;
			while (arithTrig[p] != '=') {
				pathName[p] = arithTrig[p];
				p++;
			}
			pathName[p] = '\0';
			for (p = 0; pathName[p] != ' '&&pathName[p] != ')'&&pathName[p] != '\0'; p++);
			if (p == abs((int)strlen(pathName))) {
				int lenPath = abs((int)strlen(pathName)) + 1;
				for (p = lenPath; arithTrig[p] != '\0'; p++) {
					arithTrig[p - lenPath] = arithTrig[p];
				}
				arithTrig[p - lenPath] = '\0';
				pathNameController(pathName, arithTrig);
			}
			else {
				printf("\n==> Invalid abbreviation! <==\n\n");
				fprintf(fout, "\n==> Invalid abbreviation! <==\n\n");
				arithTrig[0] = '\0';
			}
		}
		if (arithTrig[0] != '\0') {
			command = 1;
			boolean toWrite = processTxt(arithTrig, rf);
			if (toWrite) {
				printf("\n==> Close the file with the answers to continue. <==\n\n");
				fprintf(fout, "\n==> Close the file with the answers to continue. <==\n\n");
				openTxt();
			}
			arithTrig[0] = '\0';
		}
	}
	if (str == 1) {
		str = 0;
		int p = 0;
		char variableString[DIM] = "";
		p = 0;
		if (var == 1) {
			var = 0;
			while (arithTrig[p] != '=') {
				variableString[p] = arithTrig[p];
				p++;
			}
			variableString[p] = '\0';
			for (p = 0; variableString[p] != ' '&&variableString[p] != ')'&&variableString[p] != '\0'&&p < abs((int)strlen(variableString)); p++);
			if (strIndex == strlen(variableString)) {
				int lenStr = abs((int)strlen(variableString)) + 1;
				p++;
				if (arithTrig[lenStr] == '\"') {
					arithTrig[p - lenStr] = arithTrig[p];
					lenStr++;
					p++;
				}
				for (p = lenStr; arithTrig[p] != '\0'&&arithTrig[p] != '\"'&&p < abs((int)strlen(arithTrig)); p++) {
					arithTrig[p - lenStr] = arithTrig[p];
				}
				arithTrig[p - lenStr] = '\0';
				stringVariableController(variableString, arithTrig);
				if (valGet == 0) {
					puts(" ");
				}
			}
			else {
				printf("\n==> Invalid string name! Only letters from latin alphabet and digits 0-9 can be used. <==\n\n");
				fprintf(fout, "\n==> Invalid string name! Only letters from latin alphabet and digits 0-9 can be used. <==\n\n");
				arithTrig[0] = '\0';
			}
		}
		if (arithTrig[0] != '\0') {
			command = 1;
			arithTrig[0] = '\0';
		}
	}
	else {

		if (strlen(arithTrig) > 0) {
			arithTrig[i] = '+'; arithTrig[i + 1] = '0'; arithTrig[i + 2] = '\0';
		}

		verify = 0;
		for (s = 0; arithTrig[s] != '\0'; s++) {
			if (arithTrig[s] == 'B' || arithTrig[s] == 'O' || arithTrig[s] == 'H' || arithTrig[s] == '_' || arithTrig[s] == '{' || arithTrig[s] == '[' || arithTrig[s] == '(' || arithTrig[s] == '+' || arithTrig[s] == '-' || arithTrig[s] == '*' || arithTrig[s] == '/' || arithTrig[s] == '^' || arithTrig[s] == '0' || arithTrig[s] == '1' || arithTrig[s] == '2' || arithTrig[s] == '3' || arithTrig[s] == '4' || arithTrig[s] == '5' || arithTrig[s] == '6' || arithTrig[s] == '7' || arithTrig[s] == '8' || arithTrig[s] == '9' || (arithTrig[s] == 'r'&&arithTrig[s + 1] == 'e'&&arithTrig[s + 2] == 's') || (arithTrig[s] == 'a'&&arithTrig[s + 1] == 'n'&&arithTrig[s + 2] == 's') || (arithTrig[s] == 'e' && ((arithTrig[s + 1] == 'e' || arithTrig[s + 1] == '\0'&&s == 0 || arithTrig[s + 1] == ')' || arithTrig[s + 1] == 'p' || arithTrig[s - 1] == '_') || (arithTrig[s - 1] == 'e' || arithTrig[s - 1] == '(' || arithTrig[s - 1] == 'i'&&arithTrig[s - 2] != 't'))) || (arithTrig[s] == 'p'&&arithTrig[s + 1] == 'i' && ((arithTrig[s + 2] == 'e' || arithTrig[s + 2] == '\0'&&s == 0 || arithTrig[s + 2] == ')' || arithTrig[s + 2] == 'p' || arithTrig[s - 1] == '_') || (arithTrig[s - 1] == 'e' || arithTrig[s - 1] == '(' || arithTrig[s - 1] == 'i')))) {
				verify = 1;
			}
		}
		if (var == 1) {
			for (i = 0; arithTrig[i] != '='; i++) {
				if (arithTrig[i] == ' ') {
					v = 1;
				}
			}
			i++;
			if (arithTrig[i] == '+'&&arithTrig[i + 1] == '0'&&arithTrig[i + 2] == '\0') {
				verify = 0;
				var = 0;
			}
		}
		boolean isFunction = atcFunctions(arithTrig);
		if (isFunction == false) {
			for (i = 0; arithTrig[i] != '\0'; i++) {
				if (arithTrig[i] == ' ') {
					space = 1;
					break;
				}
				else {
					space = 0;
				}
			}
			if (space == 1 && run_del_space == 1) {
				while (space == 1) {
					for (i = 0; arithTrig[i] != '\0'; i++) {
						if (arithTrig[i] == ' ') {
							j = i;
							while (arithTrig[i] != '\0') {
								arithTrig[i] = arithTrig[i + 1];
								i++;
							}
							i = j;
						}
					}
					for (i = 0; arithTrig[i] != '\0'; i++) {
						if (arithTrig[i] == ' ') {
							space = 1;
							break;
						}
						else {
							space = 0;
						}
					}
				}
			}
			if (verify == 1) {
				fprintf(fout, ">%s\n", savefTrig);
			}
			if (fout != NULL) {
				fclose(fout);
			}
			command = commands(arithTrig, path, result1, result2);
			fflush(NULL);
			fout = NULL;
			while (fout == NULL) {
				fout = fopen(path, "a+");
			}
			if (command == false && continu) {

				main_sub_core(arithTrig, fout, verify, path, txt, variable, v, j, result1, result2, isFromMain, var, valGet, command);
				sprintf(arithTrig, ""); sprintf(fTrig, ""); arithTrig[0] = '\0'; fTrig[0] = '\0';
			}
		}
	}
	return result1;
}

double main_sub_core(char arithTrig[DIM], FILE *fout, int verify, char path[DIM], int txt, char variable[DIM], int v, int j, double result1, double result2, int isFromMain, int var, int valGet, int command) {
	FILE *open = NULL;
	int  g = 0, Dimensions = 2, Window = 3, r = 0, i = 0, s = 0;
	char exit[DIM] = "", res, varLetters[DIM] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", saveArithTr[DIM] = "";;
	res = arithTrig[0];
	if (res == '+' || res == '-' || res == '/' || res == '*' || res == '^') {
		for (i = 0; arithTrig[i] != '\0'; i++) {
			arithTrig[i] = arithTrig[i + 1];
		}
	}
	if (var == 1) {
		for (i = 0; arithTrig[i] != '='&&arithTrig[i] != '\0'; i++) {
			variable[i] = arithTrig[i];
		}
		variable[i] = '\0';
		g = i + 1;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			arithTrig[i] = arithTrig[i + g];
		}
		arithTrig[i] = '\0';
		sprintf(saveArithTr, "%s", arithTrig);
		sprintf(arithTrig, "");
		i = 0;
		int hk = variableValidator(variable);
		if (hk == 1 || v == 1) {
			processVariable(revariable);
		}
		if (hk == 2) {
			if (isFromMain == 1) {
				printf("\n==> Your variable was renamed to \"%s\". <==\n\n", revariable);
			}
			fprintf(fout, "\n==> Your variable was renamed to \"%s\". <==\n\n", revariable);
		}
		if (hk == 0) {
			if (isFromMain == 1) {
				printf("\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
			}
			fprintf(fout, "\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
			var = 0;
		}
		sprintf(arithTrig, "%s", saveArithTr);
	}
	char dP[DIM] = "", bP[DIM] = "", oP[DIM] = "", hP[DIM] = "";
	int dp = -1, bp = -1, op = -1, hp = -1;
	while ((arithTrig[0] == 'd' &&arithTrig[1] == 'p' || arithTrig[0] == 'b' &&arithTrig[1] == 'p' || arithTrig[0] == 'o' &&arithTrig[1] == 'p' || arithTrig[0] == 'h' &&arithTrig[1] == 'p') && arithTrig[i] != '\0'&&i < abs((int)strlen(arithTrig))) {
		if (arithTrig[0] == 'd' &&arithTrig[1] == 'p') {
			i = 2;
			while ((arithTrig[i] == 'd'&&arithTrig[i + 1] == 'p') == false && arithTrig[i] != '\0') {
				dP[i - 2] = arithTrig[i];
				i++;
			}
			dP[i - 2] = '\0';
			if (arithTrig[i] != '\0') {
				dp = (int)solveNow(dP, result1, result2);
				i = i + 2;
				int b = 0;
				for (b = 0; arithTrig[b] != '\0'; b++) {
					arithTrig[b] = arithTrig[b + i];
				}
			}
			else {
				dp = 10000;
				nPlaces = dp;
			}
		}
		if (arithTrig[0] == 'b' &&arithTrig[1] == 'p') {
			i = 2;
			while ((arithTrig[i] == 'b'&&arithTrig[i + 1] == 'p') == false && arithTrig[i] != '\0') {
				bP[i - 2] = arithTrig[i];
				i++;
			}
			bP[i - 2] = '\0';
			if (arithTrig[i] != '\0') {
				bp = (int)solveNow(bP, result1, result2);
				i = i + 2;
				int b = 0;
				for (b = 0; arithTrig[b] != '\0'; b++) {
					arithTrig[b] = arithTrig[b + i];
				}
			}
			else {
				bp = 1000;
				nPlaces = bp;
			}
		}
		if (arithTrig[0] == 'o' &&arithTrig[1] == 'p') {
			i = 2;
			while ((arithTrig[i] == 'o'&&arithTrig[i + 1] == 'p') == false && arithTrig[i] != '\0') {
				oP[i - 2] = arithTrig[i];
				i++;
			}
			oP[i - 2] = '\0';
			if (arithTrig[i] != '\0') {
				op = (int)solveNow(oP, result1, result2);
				i = i + 2;
				int b = 0;
				for (b = 0; arithTrig[b] != '\0'; b++) {
					arithTrig[b] = arithTrig[b + i];
				}
			}
			else {
				op = 8000;
				nPlaces = op;
			}
		}
		if (arithTrig[0] == 'h' &&arithTrig[1] == 'p') {
			i = 2;
			while ((arithTrig[i] == 'h'&&arithTrig[i + 1] == 'p') == false && arithTrig[i] != '\0') {
				hP[i - 2] = arithTrig[i];
				i++;
			}
			hP[i - 2] = '\0';
			if (arithTrig[i] != '\0') {
				hp = (int)solveNow(hP, result1, result2);
				i = i + 2;
				int b = 0;
				for (b = 0; arithTrig[b] != '\0'; b++) {
					arithTrig[b] = arithTrig[b + i];
				}
			}
			else {
				hp = 16000;
				nPlaces = hp;
			}
		}
	}
	for (i = 0; arithTrig[i] != '\0'; i++) {
		if (arithTrig[i] == 'a'&&arithTrig[i + 1] == 'n'&&arithTrig[i + 2] == 's') {
			arithTrig[i] = 'r'; arithTrig[i + 1] = 'e'; arithTrig[i + 2] = 's';
			i = i + 3;
		}
	}
	s = 0;
	if (verify == 1) {
		synTest = 0;
		manageExpression(arithTrig, result1, result2, verify);
		for (i = 0; expressionF[i] != '\0'; i++) {
			arithTrig[i] = expressionF[i];
		}
		arithTrig[i] = '\0';
		synTest = 0;
		verify = dataVerifier(arithTrig, result1, result2, isFromMain, verify);
	}
	fclose(fout);
	if (arithTrig[0] != '\0'&&isFromMain == 1 && feedbackValidation == 0) {
		Clock(0);
	}
	if (continu == 1) {
		_flushall();
		if (cleanhistory == 0) {
			if (arithTrig[0] != '\0'&&verify == 1) {
				char toOpen[DIM] = "";
				sprintf(toOpen, "%s\\verboseResolution.txt", atcPath);
				open = fopen(toOpen, "r");
				char verboseRes[DIM] = "";
				if (open != NULL) {
					fgets(verboseRes, 10, open);
					verbose = atoi(verboseRes);
					fclose(open);
				}
				else {
					verbose = 0;
				}
				rasf = abs((int)strlen(arithTrig));
				while (arithTrig[rasf - 2] == '+'&&arithTrig[rasf - 1] == '0') {
					rasf = rasf - 2;
					arithTrig[rasf] = '\0';
				}
				maxLength = (int)strlen(arithTrig);
				initialProcessor(arithTrig, result1);
				verbose = 0;
			}
		}
		if (arithTrig[0] != '\0'&&txt != 1 && processingOK == 1) {
			if (verify == 1) {
				if (res == '+') {
					sum(result1, result2, resultR, resultI);
				}
				if (res == '-') {
					subtraction(result1, result2, resultR, resultI);
				}
				if (res == '/') {
					division(result1, result2, resultR, resultI);
				}
				if (res == '*') {
					multiplication(result1, result2, resultR, resultI);
				}
				if (res == '^') {
					exponentiation(result1, result2, resultR, resultI, 1);
				}
				verified = 1;
				round_complex();
				result1 = resultR;
				result2 = resultI;
				resultFI = result2;
				if (isFromSolveNow == 0) {
					ans[rf] = result1;
					ansI[rf] = result2;
					ansRV = result1;
					ansIV = result2;
				}
				if (var == 1) {
					variableController(revariable, result1);
				}
				if (valGet == 0 && feedbackValidation == 0) {
					if (dp == -1) {
						if (isFromMain == 1) {
							if (result1 > 0 && result2 > 0) {
								printf("#%d=%G+%Gi\n", rf, result1, result2);
							}
							else {
								if (result1 > 0 && result2 < 0) {
									printf("#%d=%G%Gi\n", rf, result1, result2);
								}
								else {
									if (result1 < 0 && result2 > 0) {
										printf("#%d=%G+%Gi\n", rf, result1, result2);
									}
									else {
										if (result1 < 0 && result2 < 0) {
											printf("#%d=%G%Gi\n", rf, result1, result2);
										}
										else {
											if (result1 == 0 && result2 == 0) {
												printf("#%d=%G\n", rf, result1);
											}
											else {
												if (result1 == 0 && result2 != 0) {
													printf("#%d=%Gi\n", rf, result2);
												}
												else {
													if (result1 != 0 && result2 == 0) {
														printf("#%d=%G\n", rf, result1);
													}
													else {
														printf("#%d=%G+%Gi\n", rf, result1, result2);
													}
												}
											}
										}
									}
								}
							}
						}
						if (fout != NULL) {
							fclose(fout);
						}
						fout = NULL;
						while (fout == NULL) {
							fout = fopen(path, "a+");
						}
						if (result1 > 0 && result2 > 0) {
							fprintf(fout, "#%d=%G+%Gi\n", rf, result1, result2);
						}
						else {
							if (result1 > 0 && result2 < 0) {
								fprintf(fout, "#%d=%G%Gi\n", rf, result1, result2);
							}
							else {
								if (result1 < 0 && result2 > 0) {
									fprintf(fout, "#%d=%G+%Gi\n", rf, result1, result2);
								}
								else {
									if (result1 < 0 && result2 < 0) {
										fprintf(fout, "#%d=%G%Gi\n", rf, result1, result2);
									}
									else {
										if (result1 == 0 && result2 == 0) {
											fprintf(fout, "#%d=%G\n", rf, result1);
										}
										else {
											if (result1 == 0 && result2 != 0) {
												fprintf(fout, "#%d=%Gi\n", rf, result2);
											}
											else {
												if (result1 != 0 && result2 == 0) {
													fprintf(fout, "#%d=%G\n", rf, result1);
												}
												else {
													fprintf(fout, "#%d=%G+%Gi\n", rf, result1, result2);
												}
											}
										}
									}
								}
							}
						}

						fclose(fout);
						if (isFromSolveNow == 0) {
							rf++;
						}
					}
					if (dp > -1) {
						if (result1 > 0 && result2 > 0) {
							sprintf(dP, "#%d=%%.%df+%%.%dfi\n", rf, dp, dp);
							if (isFromMain == 1) {
								printf(dP, result1, result2);
							}
						}
						if (result1 > 0 && result2 < 0) {
							sprintf(dP, "#%d=%%.%df%%.%dfi\n", rf, dp, dp);
							if (isFromMain == 1) {
								printf(dP, result1, result2);
							}
						}
						if (result1 < 0 && result2 > 0) {
							sprintf(dP, "#%d = %%.%df+%%.%dfi\n", rf, dp, dp);
							if (isFromMain == 1) {
								printf(dP, result1, result2);
							}
						}
						if (result1 < 0 && result2 < 0) {
							sprintf(dP, "#%d=%%.%df%%.%dfi\n", rf, dp, dp);
							if (isFromMain == 1) {
								printf(dP, result1, result2);
							}
						}
						if (result1 == 0 && result2 == 0) {
							sprintf(dP, "#%d=%%.%df\n", rf, dp);
							if (isFromMain == 1) {
								printf(dP, result1);
							}
						}

						if (result1 == 0 && result2 != 0) {
							sprintf(dP, "#%d=%%.%dfi\n", rf, dp);
							if (isFromMain == 1) {
								printf(dP, result2);
							}
						}
						if (result1 != 0 && result2 == 0) {
							sprintf(dP, "#%d=%%.%df\n", rf, dp);
							if (isFromMain == 1) {
								printf(dP, result1);
							}
						}
						if (fout != NULL) {
							fclose(fout);
						}
						fout = NULL;
						while (fout == NULL) {
							fout = fopen(path, "a+");
						}
						fprintf(fout, dP, result1);
						fclose(fout);
						if (isFromSolveNow == 0) {
							rf++;
						}
					}
					char toOpen[DIM] = "";
					sprintf(toOpen, "%s\\numSystems.txt", atcPath);
					open = fopen(toOpen, "r");
					char numSys[DIM] = "";
					int numeriSys = 0;
					if (open != NULL || bp != -1 || op != -1 || hp != -1) {
						if (open != NULL) {
							fgets(numSys, 10, open);
							numeriSys = atoi(numSys);
							fclose(open);
						}
						if (numeriSys == 1 || bp != -1 || op != -1 || hp != -1) {
							char syst[DIM] = "";
							sprintf(syst, "%G", result1);
							if (isEqual(syst, "-NAN(IND)")) {
								if (isFromMain == 1) {
									puts("");
									puts("In binary=-NAN(IND)");
									puts("In octal=-NAN(IND)");
									puts("In hexadecimal=-NAN(IND)");
								}
								open = fopen(path, "a+");
								fputs("", open);
								fputs("In binary=-NAN(IND)\n", open);
								fputs("In octal=-NAN(IND)\n", open);
								fputs("In hexadecimal=-NAN(IND)\n", open);
								fclose(open);
							}
							else {
								if (syst[0] == 'I'&&syst[1] == 'N'&&syst[2] == 'F') {
									if (isFromMain == 1) {
										puts("");
										puts("In binary=INF");
										puts("In octal=INF");
										puts("In hexadecimal=INF");
									}
									open = fopen(path, "a+");
									fputs("", open);
									fputs("In binary=INF\n", open);
									fputs("In octal=INF\n", open);
									fputs("In hexadecimal=INF\n", open);
									fclose(open);
								}
								else {
									if (syst[0] == '-'&&syst[1] == 'I'&&syst[2] == 'N'&&syst[3] == 'F') {
										if (isFromMain == 1) {
											puts("");
											puts("In binary=-INF");
											puts("In octal=-INF");
											puts("In hexadecimal=-INF");
										}
										open = fopen(path, "a+");
										fputs("", open);
										fputs("In binary=-INF\n", open);
										fputs("In octal=-INF\n", open);
										fputs("In hexadecimal=-INF\n", open);
										fclose(open);
									}
									else {
										if (result1 != 0 && result2 == 0 || result1 == 0 && result2 == 0) {
											open = fopen(path, "a+");
											fputs("\nReal part:\n", open);
											if (isFromMain == 1) {
												puts("\nReal part:\n");
											}
											fclose(open);
											decimalToBinary(result1, path, bp);
											decimalToOctal(result1, path, op);
											decimalToHexadecimal(result1, path, hp);
										}
										else {
											if (result1 != 0 && result2 != 0) {
												open = fopen(path, "a+");
												fputs("\nReal part:\n", open);
												if (isFromMain == 1) {
													puts("\nReal part:\n");
												}
												fclose(open);
												decimalToBinary(result1, path, bp);
												decimalToOctal(result1, path, op);
												decimalToHexadecimal(result1, path, hp);
												open = fopen(path, "a+");
												fputs("\nImaginary part:\n", open);
												if (isFromMain == 1) {
													puts("\nImaginary part:\n");
												}
												fclose(open);
												decimalToBinary(result2, path, bp);
												decimalToOctal(result2, path, op);
												decimalToHexadecimal(result2, path, hp);
											}
											else {
												if (result2 != 0) {
													open = fopen(path, "a+");
													fputs("\nImaginary part:\n", open);
													if (isFromMain == 1) {
														puts("\nImaginary part:\n");
													}
													fclose(open);
													decimalToBinary(result2, path, bp);
													decimalToOctal(result2, path, op);
													decimalToHexadecimal(result2, path, hp);
												}
											}
										}
									}
								}
							}
						}
					}
					toOpen[0] = '\0';
					sprintf(toOpen, "%s\\siPrefixes.txt", atcPath);
					open = fopen(toOpen, "r");
					char siPref[DIM] = "";
					int niPrefix = 0;
					if (open != NULL) {
						fgets(siPref, 10, open);
						fclose(open);
						niPrefix = atoi(siPref);
						if (niPrefix == 1) {
							char pref[DIM] = "";
							sprintf(pref, "%G", result1);
							char Value[DIM] = "";
							if (result1 != 0 || result1 == 0 && result2 == 0) {
								open = fopen(path, "a+");
								fputs("\nReal part:\n", open);
								if (isFromMain == 1) {
									puts("\nReal part:\n");
								}
								fclose(open);
								char pref[DIM] = "";
								sprintf(pref, "%G", result1);
								if (isEqual(pref, "-NAN(IND)")) {
									if (isFromMain == 1) {
										puts("=-NAN(IND)");
									}
									open = fopen(path, "a+");
									fputs("=-NAN(IND)\n", open);
									fclose(open);
								}
								else {
									if (pref[0] == 'I'&&pref[1] == 'N'&&pref[2] == 'F') {
										if (isFromMain == 1) {
											puts("=INF");
										}
										open = fopen(path, "a+");
										fputs("=INF\n", open);
										fclose(open);
									}
									else {
										if (pref[0] == '-'&&pref[1] == 'I'&&pref[2] == 'N'&&pref[3] == 'F') {
											if (isFromMain == 1) {
												puts("=-INF");
											}
											open = fopen(path, "a+");
											fputs("=-INF\n", open);
											fclose(open);
										}
										else {
											prefixDeterminator(result1, path);
										}
									}
								}
							}
							if (result2 != 0) {
								open = fopen(path, "a+");
								fputs("\nImaginary part:\n", open);
								if (isFromMain == 1) {
									puts("\nImaginary part:\n");
								}
								fclose(open);
								char pref[DIM] = "";
								sprintf(pref, "%G", result2);
								if (isEqual(pref, "-NAN(IND)")) {
									if (isFromMain == 1) {
										puts("=-NAN(IND)");
									}
									open = fopen(path, "a+");
									fputs("=-NAN(IND)\n", open);
									fclose(open);
								}
								else {
									if (pref[0] == 'I'&&pref[1] == 'N'&&pref[2] == 'F') {
										if (isFromMain == 1) {
											puts("=INF");
										}
										open = fopen(path, "a+");
										fputs("=INF\n", open);
										fclose(open);
									}
									else {
										if (pref[0] == '-'&&pref[1] == 'I'&&pref[2] == 'N'&&pref[3] == 'F') {
											if (isFromMain == 1) {
												puts("=-INF");
											}
											open = fopen(path, "a+");
											fputs("=-INF\n", open);
											fclose(open);
										}
										else {
											prefixDeterminator(result2, path);
										}
									}
								}
							}
						}
					}
					sprintf(toOpen, "%s\\actualTime.txt", atcPath);
					open = fopen(toOpen, "r");
					char actualTime[DIM] = "";
					int nactualTime = 0;
					if (open != NULL) {
						fgets(actualTime, 10, open);
						fclose(open);
						nactualTime = atoi(actualTime);
						if (nactualTime == 1 && isFromMain == 1) {
							puts("");
							Clock(1);
							puts("");
						}
					}
					if (isFromMain == 1) {
						printf("\n");
					}
					FILE *fout = NULL;
					while (fout == NULL) {
						fout = fopen(path, "a+");
					}
					fputs("\n", fout);
					fclose(fout);
				}
			}
			else {
				if (valGet == 0) {
					if (isFromMain == 1) {
						printf("\nError in syntax.\n\n");
					}
					FILE *fout = NULL;
					while (fout == NULL) {
						fout = fopen(path, "a+");
					}
					fprintf(fout, "\nError in syntax.\n\n");
					fclose(fout);
				}
			}
		}
	}
	return result1;
}
