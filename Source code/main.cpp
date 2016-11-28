#include "stdafx.h"
#include "atc_functions.h"

double ansIV = 0, ansRV = 0, ans[DIM], ansI[DIM], valInd[DIM][DIM], values[DIM][DIM], resultFI = 0, valuesS[DIM][DIM], valuesSI[DIM][DIM], valuesF[DIM][DIM], valuesFI[DIM][DIM], valuesI[DIM][DIM], resultR = 0, resultI = 0, intVal = 0;
char atcPath[DIM] = "", varRename[DIM] = "", revariable[DIM] = "", pathNAme[DIM] = "", variableSTring[DIM] = "", expressionF[DIM] = "", usRFunctions[DIM] = ",", usRFuncTrans[DIM] = ",";
int Mode = 0, isFromSolveNow = 0, valid = 0, validVar = 0, count = 2, synTest = 0, valRenamedVar = 0, continu = 1, cleanhistory = 0, rf = 0, verified = 0, nPlaces = 0;



int main(int argc, char *argv[]) {
	char dataToSolve[DIM] = "";
	FILE *fout = NULL;
	int Colors = 1, tD = 0, i = 0;
	char  path[DIM] = "", trigData[DIM] = "";
	double result1 = 0, result2 = 0;

	getATCPath();

	if (argc < 2) {
		on_start();
		applySettings(Colors);
		system("title Advanced Trigonometry Calculator v1.8.7");
		continu = about();
		system("title Advanced Trigonometry Calculator v1.8.7                                                             ==) Enter data (==              ");
	}
	if (continu == 1) {
		do {
			usRFunctions[0] = ','; usRFuncTrans[0] = ',';
			usRFunctions[1] = '\0'; usRFuncTrans[1] = '\0';
			fflush(NULL);
			tD = 0;
			if (argc < 2) {
				sprintf(trigData, "");
				printf(">");
				gets_s(trigData);

			}
			else {
				int arG = 1;
				trigData[0] = '\0';
				while (arG < argc) {
					sprintf(trigData, "%s%s", trigData, argv[arG]);
					arG++;
				}
				addATCPath();
			}
			sprintf(path, "%s\\history.txt", atcPath);
			toSolve(rf);

			for (tD = 0; trigData[tD] != 0; tD++) {
				if (trigData[tD] == '{' || trigData[tD] == '[') {
					trigData[tD] = '(';
				}
				if (trigData[tD] == '}' || trigData[tD] == ']') {
					trigData[tD] = ')';
				}
			}
			for (tD = 0; trigData[tD] != '\0'; tD++) {
				fflush(NULL);
				char fTrig[DIM] = "", arithTrig[DIM] = "";
				fout = NULL;
				while (fout == NULL) {
					fout = fopen(path, "a+");
				}
				varRename[0] = '\0'; revariable[0] = '\0';
				validVar = 1;
				fTrig[0] = '\0';
				i = 0;
				int fl = 1, fr = 0;
				while (trigData[tD] != '\0'&&trigData[tD] != ','&&tD < abs((int)strlen(trigData))) {
					if (trigData[tD - 6] == 'p'&&trigData[tD - 5] == 'r'&&trigData[tD - 4] == 'i'&&trigData[tD - 3] == 'n'&&trigData[tD - 2] == 't'&&trigData[tD - 1] == '(') {
						arithTrig[i] = trigData[tD];
						i++; tD++;
						while (fl > fr && trigData[tD] != '\0') {
							if (trigData[tD] == '(') {
								fl++;
							}
							if (trigData[tD] == ')') {
								fr++;
							}
							arithTrig[i] = trigData[tD];
							i++; tD++;
						}
						arithTrig[i] = '\0';
					}
					else {
						arithTrig[i] = trigData[tD];
						i++; tD++;
					}
				}
				arithTrig[i] = '\0';
				sprintf(fTrig, "%s", arithTrig);
				main_core(arithTrig, fTrig, fout, path, result1, result2, 1);
				sprintf(arithTrig, ""); sprintf(fTrig, ""); arithTrig[0] = '\0'; fTrig[0] = '\0';
				if (verified == 1) {
					result1 = resultR;
					result2 = resultI;
					verified = 0;
				}
			}
			if (continu != 1) {
				fclose(fout);
			}
			if (argc >= 2) {
				exit(0);
				return 0;
			}
			char Path[DIM] = "";
			sprintf(Path, "%s\\temp.txt", atcPath);
			FILE *Try = NULL;
			Try = fopen(Path, "r");
			if (Try != NULL) {
				fclose(Try);
				char toOpen[DIM] = "";
				sprintf(toOpen, "del \"%s\"", Path);
				system(toOpen);
			}
		} while (continu == 1);
	}
	exit(0);
	return 0;
}

int processTxt(char path[DIM], int re) {
	double result1 = 0, result2 = 0, anstxt[DIM], anstxtI[DIM];
	FILE *fin = NULL, *fout = NULL, *open = NULL, *read = NULL;
	char addBar[DIM] = "", savePath[DIM] = "", arith[DIM] = "", sendFunc[DIM] = "", resp[30] = "_answers.txt", varLetters[DIM] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
	int tD = 0, i, j, cP = 0, k, d, e, f, space = 0, v = 0, l = 0, m = 0, re1 = 0, save_rf = rf, toWrite = 1;
	rf = 0;
	i = 0;
	while (path[i] != '\0') {
		savePath[i] = path[i];
		i++;
	}
	savePath[i] = '\0';
	i = 0;
	while (i < re) {
		anstxt[i] = ans[i];
		anstxtI[i] = ansI[i];
		i++;
	}
	i = 0;
	for (i = 0; path[i] != '\0'; i++) {
		if (path[i] == '"') {
			i++;
			j = i;
			while (path[i] != '\0') {
				path[i - 1] = path[i];
				i++;
			}
			i = j;
		}
	}
	for (i = 0; path[i] != '\0'; i++) {
		if (path[i] == '"') {
			path[i] = '\0';
		}
	}
	j = 0;

	for (i = 0; path[i] != '\0'; i++) {
		if (path[i] != '\\') {
			addBar[j] = path[i];
			j++;
		}
		else {
			if (path[i] == '\\') {
				addBar[j] = path[i];
				addBar[j + 1] = '\\';
				j = j + 2;
			}
		}
	}
	addBar[j] = '\0';
	for (i = 0; addBar[i] != '\0'; i++) {
		path[i] = addBar[i];
	}
	path[i] = '\0';
	i = 0;
	if (read != NULL) {
		fclose(read);
	}
	read = NULL;
	while (read == NULL&&i < 100) {
		read = fopen(path, "a+");
		i++;
	}
	if (i < 100) {
		char sD[DIM] = "";
		for (i = 0; (sendFunc[i] = fgetc(read)) != EOF; i++) {
			if (sendFunc[i] == '\n') {
				cP++;
			}
		}
		if (read != NULL) {
			fclose(read);
		}
		sendFunc[i] = '\0';
		if (sendFunc[i - 1] != '\n') {
			sendFunc[i] = '\n'; sendFunc[i + 1] = '\0';
			cP++;
		}
		m = 0;
		l = 0;
		while (m == 0) {
			if (path[l] == '.'&&path[l + 1] == 't'&&path[l + 2] == 'x'&&path[l + 3] == 't'&&path[l + 4] == '\0') {
				m = 1;
			}
			l++;
		}
		m = 0;
		l--;
		while (resp[m] != '\0') {
			path[l] = resp[m];
			l++; m++;
		}
		path[l] = '\0';
		while (fin == NULL) {
			fin = fopen(path, "w");
		}
		fclose(fin);
		d = 0;
		tD = 0;
		char variable[DIM] = "";
		for (k = 0; k < cP; k++) {

			char trigData[DIM] = "";
			tD = 0;
			e = 0;
			for (f = d; sendFunc[f] != '\n'&&sendFunc[f] != '\0'; f++) {
				trigData[e] = sendFunc[f];
				e++;
			}
			f++;
			d = f;
			trigData[e] = '\0';

			for (e = 0; trigData[e] != 0; e++) {
				if (trigData[e] == '{' || trigData[e] == '[') {
					trigData[e] = '(';
				}
				if (trigData[e] == '}' || trigData[e] == ']') {
					trigData[e] = ')';
				}
			}
			for (tD = 0; trigData[tD] != '\0'; tD++) {
				i = 0;
				char arith[DIM] = "";
				int fl = 1, fr = 0;
				while (trigData[tD] != '\0'&&trigData[tD] != ',') {
					if (trigData[tD - 6] == 'p'&&trigData[tD - 5] == 'r'&&trigData[tD - 4] == 'i'&&trigData[tD - 3] == 'n'&&trigData[tD - 2] == 't'&&trigData[tD - 1] == '(') {
						arith[i] = trigData[tD];
						i++; tD++;
						while (fl > fr && trigData[tD] != '\0') {
							if (trigData[tD] == '(') {
								fl++;
							}
							if (trigData[tD] == ')') {
								fr++;
							}
							arith[i] = trigData[tD];
							i++; tD++;
						}
						arith[i] = '\0';
					}
					else {
						arith[i] = trigData[tD];
						i++; tD++;
					}
				}
				arith[i] = '\0';
				valid = 0;
				validVar = 1;
				if (fin != NULL) {
					fclose(fin);
				}
				fin = NULL;
				while (fin == NULL) {
					fin = fopen(path, "a+");
				}
				toWrite = isToWrite(arith);
				if (toWrite == 1) {
					main_core(arith, arith, fin, path, result1, result2, 0);
					if (verified == 1) {
						result1 = resultR;
						result2 = resultI;
						verified = 0;
					}
				}
				else {
					break;
				}
			}
		}
		if (fin != NULL) {
			fclose(fin);
		}
		if (read != NULL) {
			fclose(read);
		}
		i = 0;
		while (i < re) {
			ans[i] = anstxt[i];
			ansI[i] = anstxtI[i];
			i++;
		}
	}
	int h;
	for (h = 0; path[h] != '\0'; h++) {
		expressionF[h] = path[h];
	}
	expressionF[h] = '\0';
	if (fin != NULL) { fclose(fin); }if (fout != NULL) { fclose(fout); }if (open != NULL) { fclose(open); } if (read != NULL) { fclose(read); }
	rf = save_rf;
	if (toWrite == 0) {
		char eliminate[200] = "";
		if (savePath[0] == '\"') {
			int y = 0;
			while (savePath[y + 1] != '\0') {
				savePath[y] = savePath[y + 1];
				y++;
			}
			savePath[y] = '\0';
		}
		if (savePath[strlen(savePath) - 1] == '\"') {
			savePath[strlen(savePath) - 1] = '\0';
		}
		savePath[strlen(savePath) - 4] = '\0';
		sprintf(eliminate, "del \"%s_answers.txt\"", savePath);
		system(eliminate);
	}
	return toWrite;
}

int dataVerifier(char data[DIM], double result1, double result2, int comment, int verify) {
	int decision = 1;

	if (abs((int)strlen(data)) > 0) {
		int i = 0, j = 0, k = 0, l = 0, kr = 0, kl = 0, v = 0, cChars = 0, fr = 0, ra = 0, nDot = 0, g = 0, d = 0, w = 0, y = 0, t = 0, space = 0;
		char function[DIM] = "", variable[DIM] = "", expression[DIM] = "", text[DIM] = "", value[DIM] = "", saveVar[DIM] = "";
		char validChars[DIM] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM123456789.0/*-+\\!#()[]{} ^_";
		char numsysData[DIM] = "";
		int u = 0, p = 0;
		if (synTest == 0) {
			int y = 0, r = 0;
			char funcToCheck[DIM] = "";
			if (isContained("logb", data)) {

				y = (int)resultR;
				while ((data[y - 1] == 'b'&&data[y] == '(') == false && data[y] != '\0') {
					y++;
				}
				r = y + 1;
			}
			if (isContained("rtD", data)) {
				y = (int)resultR;
				while ((data[y - 1] == 'D'&&data[y] == '(') == false && data[y] != '\0') {
					y++;

				}
				r = y + 1;
			}

			int as = 0;
			char argument[DIM] = "";
			if (isContained("logb", data) || isContained("rtD", data)) {
				while (data[r] != ')'&&data[r] != '\0'&&r < abs((int)strlen(data))) {
					argument[as] = data[r];
					as++; r++;
				}
				argument[as] = '+'; argument[as + 1] = '('; argument[as + 2] = '0'; argument[as + 3] = ')'; argument[as + 4] = '\0';
				initialProcessor(argument, result1);
				double argumentR = resultR;
				double argumentI = resultI;
				char systR[DIM] = "";
				sprintf(systR, "%G", argumentR);
				char systI[DIM] = "";
				sprintf(systI, "%G", argumentI);
				if (isEqual(systR, "INF") || isEqual(systR, "-INF") || isEqual(systI, "INF") || isEqual(systI, "-INF")) {
					decision = 0;
					if (comment == 1) {
						printf("\nFunction argument is too big. Unable to process it.\n");
					}
					return decision;
				}
			}
			decision = 1;
			synTest = 1;
			if (nPlaces != 0) {
				if (nPlaces == 1000) {
					if (comment == 1) {
						puts("\nBinary places number entered with errors.\n");
					}
					decision = 0;
					return decision;
				}
				if (nPlaces == 8000) {
					if (comment == 1) {
						puts("\nOctal places number entered with errors.\n");
					}
					decision = 0;
					return decision;
				}
				if (nPlaces == 10000) {
					if (comment == 1) {
						puts("\nDecimal places number entered with errors.\n");
					}
					decision = 0;
					return decision;
				}
				if (nPlaces == 16000) {
					if (comment == 1) {
						puts("\nHexadecimal places number entered with errors.\n");
					}
					decision = 0;
					return decision;
				}
			}
			for (w = 0; data[w] != '\0'; w++) {
				if ((data[w] == 'B' || data[w] == 'O' || data[w] == 'H' || data[w] == 'P' || data[w] == '#') && (w == 0 || data[w - 1] == '+' || data[w - 1] == '-' || data[w - 1] == '*' || data[w - 1] == '/' || data[w - 1] == '^' || data[w - 1] == '(')) {
					w++;

					if (data[w - 1] == 'B') {
						if (data[w] == '_' || data[w] == '-') {
							w++;
						}
						y = 0;
						while (data[w] != '+'&&data[w] != '-'&&data[w] != '*'&&data[w] != '/'&&data[w] != '^'&&data[w] != ')'&&data[w - 1] != 'b'&&data[w] != '('&&data[w - 1] != 'D'&&data[w] != '('&&data[w] != '\0') {
							numsysData[y] = data[w];
							w++; y++;
						}
						numsysData[y] = '\0';
						t = 0;
						for (y = 0; numsysData[y] != '\0'; y++) {
							if (numsysData[y] == '1' || numsysData[y] == '0' || numsysData[y] == '.') {
								t++;
							}
						}

						if (t != strlen(numsysData)) {
							decision = 0;
							if (comment == 1) {
								puts("\nBinary number entered with errors.\n");
							}
							return decision;
						}

					}

					if (data[w - 1] == 'O') {
						if (data[w] == '_' || data[w] == '-') {
							w++;
						}
						y = 0;
						while (data[w] != '+'&&data[w] != '-'&&data[w] != '*'&&data[w] != '/'&&data[w] != '^'&&data[w] != ')'&&data[w - 1] != 'b'&&data[w] != '('&&data[w - 1] != 'D'&&data[w] != '('&&data[w] != '\0') {
							numsysData[y] = data[w];
							w++; y++;
						}
						numsysData[y] = '\0';
						t = 0;
						for (y = 0; numsysData[y] != '\0'; y++) {
							if (numsysData[y] == '0' || numsysData[y] == '1' || numsysData[y] == '2' || numsysData[y] == '3' || numsysData[y] == '4' || numsysData[y] == '5' || numsysData[y] == '6' || numsysData[y] == '7' || numsysData[y] == '.') {
								t++;
							}
						}
						if (t != strlen(numsysData)) {
							decision = 0;
							if (comment == 1) {
								puts("\nOctal number entered with errors.\n");
							}
							return decision;
						}

					}

					if (data[w - 1] == 'H') {
						if (data[w] == '_' || data[w] == '-') {
							w++;
						}
						y = 0;
						while (data[w] != '+'&&data[w] != '-'&&data[w] != '*'&&data[w] != '/'&&data[w] != '^'&&data[w] != ')'&&data[w - 1] != 'b'&&data[w] != '('&&data[w] != '('&&data[w] != '\0') {
							numsysData[y] = data[w];
							w++; y++;
						}
						numsysData[y] = '\0';
						t = 0;
						for (y = 0; numsysData[y] != '\0'; y++) {
							if (numsysData[y] == '0' || numsysData[y] == '1' || numsysData[y] == '2' || numsysData[y] == '3' || numsysData[y] == '4' || numsysData[y] == '5' || numsysData[y] == '6' || numsysData[y] == '7' || numsysData[y] == '8' || numsysData[y] == '9' || numsysData[y] == 'A' || numsysData[y] == 'B' || numsysData[y] == 'C' || numsysData[y] == 'D' || numsysData[y] == 'E' || numsysData[y] == 'F' || numsysData[y] == '.') {
								t++;
							}
						}
						if (t != strlen(numsysData)) {
							decision = 0;
							if (comment == 1) {
								puts("\nHexadecimal number entered with errors.\n");
							}
							return decision;
						}

					}

					if (data[w - 1] == 'P') {
						y = 0;
						while (data[w] != '+'&&data[w] != '-'&&data[w] != '*'&&data[w] != '/'&&data[w] != '^'&&data[w] != ')'&&data[w - 1] != 'b'&&data[w] != '('&&data[w - 1] != 'D'&&data[w] != '('&&data[w] != '\0') {
							numsysData[y] = data[w];
							w++; y++;
						}
						numsysData[y] = '\0';
						decision = verifyPrefix(numsysData);
						if (decision == 0) {
							if (comment == 1) {
								puts("\nSI prefix entered with errors.\n");
							}
							return decision;
						}
					}
					if (data[w - 1] == '#') {
						y = 0;
						while (verifyNumber(data[w]) == 1 && data[w] != '+'&&data[w] != '-'&&data[w] != '*'&&data[w] != '/'&&data[w] != '^'&&data[w] != ')'&&data[w - 1] != 'b'&&data[w] != '('&&data[w - 1] != 'D'&&data[w] != '('&&data[w] != '\0') {
							numsysData[y] = data[w];
							w++; y++;
						}
						numsysData[y] = '+'; numsysData[y + 1] = '0'; numsysData[y + 2] = '\0';
						int reIndex = (int)arithSolver(numsysData, 0);
						if (reIndex >= rf) {
							if (comment == 1) {
								puts("\nResult indentifier not found.\n");
							}
							decision = 0;
							return decision;
						}
					}

				}

			}
			w = strlen(data) - 4;
			if ((data[w - 1] == '+' || data[w - 1] == '-' || data[w - 1] == '*' || data[w - 1] == '/' || data[w - 1] == '^') && data[w] == '+'&&data[w + 1] == '0'&&data[w + 2] == '+'&&data[w + 3] == '0'&&data[w + 4] == '\0') {
				verify = 0;
				if (comment == 1) {
					puts("\nYour expression is terminating with an arithmetic symbol.\n");
				}
				decision = 0;
				return decision;
			}
			for (w = 0; data[w] != '\0'; w++) {
				if ((data[w] == '+' || data[w] == '-' || data[w] == '*' || data[w] == '/' || data[w] == '^') && (data[w + 1] == '+' || data[w + 1] == '-'&&data[w - 2] != '1'&&data[w - 1] != '0' || data[w + 1] == '*' || data[w + 1] == '/' || data[w + 1] == '^' || data[w + 1] == '!')) {
					verify = 0;
					if (comment == 1) {
						puts("\nYour expression has consecutive arithmetic symbols.\n");
					}
					decision = 0;
					return decision;
				}
			}
		}
		u = 0;
		for (u; data[u] != '\0'; u++) {
			int r = 0, f = 0;
			p = 0;
			char varValidator[DIM] = "";
			if (verifyLetter(data[u]) == 1) {
				if (data[u] == 'B' || data[u] == 'O' || data[u] == 'H' || data[u] == 'P') {
					varValidator[p] = data[u];
					u++; p++;
					if (data[u] == '-' || data[u] == '_') {
						varValidator[p] = data[u];
						u++; p++;
					}
					while (data[u] != ')'&&data[u] != '('&&data[u] != '+'&&data[u] != '-'&&data[u] != '*'&&data[u] != '/'&&data[u] != '^'&&data[u] != '\0'&&firstLetterFunction(data[u]) == 0) {
						varValidator[p] = data[u];
						u++; p++;
					}
				}

				while (verifyLetter(data[u]) == 1 && (data[u] == 'b'&&data[u - 1] == 'g') == false && (data[u] == 'D'&&data[u - 1] == 't') == false && data[u] != '\0') {
					varValidator[p] = data[u];
					u++; p++;
				}
				if (data[u - 1] == 't'&&data[u] == 'D' || data[u - 1] == 'g'&&data[u] == 'b') {
					varValidator[p] = data[u];
					u++; p++;
					while ((data[u] == 'b'&&data[u + 1] == '(') == false && (data[u] == 'D'&&data[u + 1] == '(') == false && data[u] != '\0') {
						varValidator[p] = data[u];
						u++; p++;
					}
					varValidator[p] = data[u];
					u++; p++;
				}
				varValidator[p] = '\0';
				p = 0;
				for (p = 0; varValidator[p] != '\0'; p++) {
					saveVar[p] = varValidator[p];
				}
				saveVar[p] = '\0';

				if (strlen(varValidator) > 0) {
					processVariable(varValidator);
					int df = p;
					varValidator[p] = '\0';
					if (varValidator[0] == 'r'&&varValidator[1] == 't'&&varValidator[2] == 'D') {
						p = 3;
						while (varValidator[p] != '\0'&&p < abs((int)strlen(varValidator))) {
							if (varValidator[p] == 'D') {
								varValidator[3] = 'D'; varValidator[4] = '?'; varValidator[5] = '\0';
							}
							p++;
						}
					}
					if (varValidator[0] == 'l'&&varValidator[1] == 'o'&&varValidator[2] == 'g'&&varValidator[3] == 'b') {
						p = 4;
						while (varValidator[p] != '\0'&&p < abs((int)strlen(varValidator))) {
							if (varValidator[p] == 'b') {
								varValidator[4] = 'b'; varValidator[5] = '?'; varValidator[6] = '\0';
							}
							p++;
						}
					}
					if (df == p) {
						varValidator[p] = '?'; varValidator[p + 1] = '\0';
					}
					char saveExpr[DIM] = "";
					sprintf(saveExpr, "%s", varValidator);


					double funcF = functionProcessor(varValidator, 2, 7, 12);
					sprintf(varValidator, "%s", saveExpr);

					if (funcF != 0.5) {
						if (validVar == 0) {
							if (varValidator[0] == 'E' || varValidator[0] == 'B' || varValidator[0] == 'O' || varValidator[0] == 'H' || varValidator[0] == 'P' || varValidator[0] == 'e' || varValidator[0] == 'p'&&varValidator[1] == 'i') {
								if (varValidator[0] == 'E' || varValidator[0] == 'B' || varValidator[0] == 'O' || varValidator[0] == 'H' || initialProcessor(varValidator, 0) != 0) {
									decision = 1;
								}
								else {
									decision = 0;
									if (comment == 1) {
										printf("\nThe variable \"%s\" is not created yet.\n", saveVar);
									}
									return decision;
								}
							}
							else {
								decision = 0;
								if (comment == 1) {
									printf("\nThe variable \"%s\" is not created yet.\n", saveVar);
								}
								return decision;
							}
						}
					}
					else {
						int y = 0;
						char funcToCheck[DIM] = "";
						if (isContained("logb", data)) {
							y = (int)resultR;
							while (data[y - 1] != 'b'&&data[y] != '('&&data[y] != '\0') {
								y++;
							}
						}
						if (isContained("rtD", data)) {
							y = (int)resultR;
							while (data[y - 1] != 'D'&&data[y] != '('&&data[y] != '\0') {
								y++;
							}
						}
						replace("?", "", varValidator);
						sprintf(funcToCheck, "%s", expressionF);
						if (isContained(funcToCheck, data)) {
							char argument[DIM] = "";
							int as = 0;
							if (y > 0) {
								r = y + 1;
							}
							else {
								r = (int)resultI + 1;
							}
							as = 0;
							while (data[r] != ')'&&data[r] != '\0'&&r < abs((int)strlen(data))) {
								argument[as] = data[r];
								as++; r++;
							}
							argument[as] = '+'; argument[as + 1] = '('; argument[as + 2] = '0'; argument[as + 3] = ')'; argument[as + 4] = '\0';
							initialProcessor(argument, result1);
							double argumentR = resultR;
							double argumentI = resultI;
							char systR[DIM] = "";
							sprintf(systR, "%G", argumentR);
							char systI[DIM] = "";
							sprintf(systI, "%G", argumentI);
							if (isEqual(systR, "INF") || isEqual(systR, "-INF") || isEqual(systI, "INF") || isEqual(systI, "-INF")) {
								decision = 0;
								if (comment == 1) {
									printf("\nFunction argument is too big. Unable to process it.\n");
								}
								return decision;
							}
						}
					}
				}
			}
		}


		for (d = 0; data[d] != '\0'; d++) {
			g = 0; nDot = 0;
			while ((data[d] == '.' || data[d] == '0' || data[d] == '1' || data[d] == '2' || data[d] == '3' || data[d] == '4' || data[d] == '5' || data[d] == '6' || data[d] == '7' || data[d] == '8' || data[d] == '9' || data[d] == 'A' || data[d] == 'B' || data[d] == 'C' || data[d] == 'D' || data[d] == 'E' || data[d] == 'F') && data[d] != '\0') {
				value[g] = data[d];
				d++; g++;
			}
			value[g] = '\0';
			for (g = 0; value[g] != '\0'; g++) {
				if (value[g] == '.') {
					nDot++;
				}
			}
			if (nDot > 1) {
				decision = 0;
				if (comment == 1) {
					puts("\nYou entered more than one dot on the entered value.\n");
				}
				return decision;
			}
		}
		for (ra = 0; data[ra] != '\0'; ra++) {
			if (data[ra] == '_'&&data[ra - 1] == '_') {
				decision = 0;
				if (comment == 1) {
					puts("\nYou don't need to enter \"__\", please use only a symbol \"_\" to represent negative values.\n");
				}
				return decision;
			}
			for (fr = 0; validChars[fr] != '\0'; fr++) {
				if (data[ra] == validChars[fr]) {
					cChars++;
				}
			}
		}
		if (cChars != ra) {
			decision = 0;
			if (comment == 1) {
				puts("\nYou entered invalid characters.\n");
			}
			return decision;
		}
		if ((data[0] == '+' || data[0] == '-' || data[0] == '*' || data[0] == 'x' || data[0] == '/' || data[0] == '^') && (data[1] == '0'&&data[2] == '\0')) {
			decision = 0;
			if (comment == 1) {
				puts("\nYou are trying relate the previous expression with zero (0).\n");
			}
			return decision;
		}
		for (i = 0; data[i] != '\0'; i++) {
			if ((data[i - 1] == 'O' || data[i - 1] == 'H' || data[i - 1] == 'B') && data[i] == '_') {
				data[i] = '-';
			}

			if (data[i] == 'A' || data[i] == 'B' || data[i] == 'C' || (data[i] == 'D' && (data[i - 1] == 't' || data[i + 1] == '(')) || data[i] == 'E' || data[i] == 'F' || data[i] == 'O' || data[i] == 'H' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4' || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9' || data[i] == '0' || data[i] == '.' || data[i] == '_' || data[i] == '!') {
				v = 1;
				break;
			}
		}
		if (v == 1) {
			v = 0;
			i = 0;
			while (data[i] != '\0') {
				if (firstLetterVariable(data[i]) == 1 && (letterVariables(data[i - 1]) == 0 || i == 0)) {
					while (letterVariables(data[i]) == 1 && data[i] != '\0') {
						text[v] = ' ';
						v++;
						i++;
					}
				}
				if ((data[i - 1] == 'O' || data[i - 1] == 'H' || data[i - 1] == 'B') && data[i] == '_') {
					data[i] = '-';
				}
				if (data[i] != '1'&&data[i] != '2'&&data[i] != '3'&&data[i] != '4'&&data[i] != '5'&&data[i] != '6'&&data[i] != '7'&&data[i] != '8'&&data[i] != '9'&&data[i] != '0'&&data[i] != '.'&&data[i] != '_'&&data[i] != '!'&&data[i] != 'A'&&data[i] != 'B'&&data[i] != 'C' && data[i] != 'D' && (data[i - 1] == 't' && data[i + 1] == '(') && data[i] != 'E'&&data[i] != 'F'&&data[i] != 'O'&&data[i] != 'H'&&data[i] != '('&&data[i] != ')') {
					text[v] = data[i];
					v++;
					i++;
				}
				else {
					text[v] = ' ';
					v++;
					i++;
				}
			}
			text[v] = '\0';
			decision = dataVerifier(text, result1, result2, comment, verify);
			if (decision == 0) {
				if (comment == 1) {
					puts("\nYou entered invalid values.\n");
				}
				return decision;
			}
		}
		for (i = 0; data[i] != '\0'; i++) {
			if (data[i] == '"' || data[i] == '%' || data[i] == '&' || data[i] == '"' || data[i] == '=' || data[i] == '?' || data[i] == '@' || data[i] == '�' || data[i] == '�' || data[i] == '\'' || data[i] == '�' || data[i] == '�' || data[i] == '�' || data[i] == '`' || data[i] == '�' || data[i] == '�' || data[i] == '~' || data[i] == ',' || data[i] == ';' || data[i] == ':' || data[i] == '�' || data[i] == '�') {
				decision = 0;
				if (comment == 1) {
					puts("\nYou entered invalid characters.\n");
				}
				return decision;
			}

			if (data[i] == '[' || data[i] == '{') {
				data[i] = '(';
			}
			if (data[i] == ']' || data[i] == '}') {
				data[i] = ')';
			}
			if (data[i] == '(') {
				kl++;
				if (data[i + 1] == '+' || data[i + 1] == '-' || data[i + 1] == '*' || data[i + 1] == 'x' || data[i + 1] == '/' || data[i + 1] == '^' || data[i + 1] == '!') {
					decision = 0;
					if (comment == 1) {
						puts("\nYou entered an arithmetic symbol next to \"(\".\n");
					}
					return decision;
				}
			}
			if (data[i] == ')') {
				kr++;
				if (data[i - 1] == '+' || data[i - 1] == '-' || data[i - 1] == '*' || data[i - 1] == 'x' || data[i - 1] == '/' || data[i - 1] == '^') {
					decision = 0;
					if (comment == 1) {
						puts("\nYou entered an arithmetic symbol previous to \")\".\n");
					}
					return decision;
				}
			}
		}
		if (kr != kl) {
			decision = 0;
			return decision;
		}
		for (i = 0; data[i] != '\0'; i++) {
			j = 0;
			if (data[i] == 'r'&&data[i + 1] == 'e'&&data[i + 2] == 's'&&data[i + 3] != 't') {
				decision = 1;
				i = i + 3;
			}
			if (data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4' || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9' || data[i] == '.' || data[i] == '_' || data[i] == '!' || data[i] == '+' || data[i] == '-' || data[i] == '/' || data[i] == '*' || data[i] == 'x' || data[i] == '^' || data[i] == 'e' || data[i] == 'p'&&data[i + 1] == 'i' || data[i - 1] == 'p'&&data[i] == 'i') {
				j = 0;
				while (data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4' || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9' || data[i] == '.' || data[i] == '_' || data[i] == '!' || data[i] == '+' || data[i] == '-' || data[i] == '/' || data[i] == '*' || data[i] == 'x' || data[i] == '^' || data[i] == 'e' || data[i] == 'p'&&data[i + 1] == 'i' || data[i - 1] == 'p'&&data[i] == 'i') {
					i++;
					decision = 1;
					j++;
				}
			}
			if (data[i] == 'r'&&data[i + 1] == 'e'&&data[i + 2] == 's'&&data[i + 3] != 't') {
				decision = 1;
				i = i + 3;
			}

			if (data[i] == 'a' || data[i] == 's'&&data[i - 1] != 'e'&&data[i - 2] != 'r' || data[i] == 'c' || data[i] == 't' || data[i] == 'g' || data[i] == 'd' || data[i] == 'l' || data[i] == 'q' || data[i] == 'r') {
				decision = 1;
				j = 0;
				while (data[i] != '('&&data[i] != '\0'&&i < abs((int)strlen(data))) {
					k = 0;
					if (data[i] == 'b'&&data[i - 1] != 'c') {
						function[j] = data[i];
						j++; i++;
						k++;
						l = 0;
						while ((data[i] == 'b'&&data[i + 1] == '(') == false && data[i] != '\0') {
							function[j] = data[i];
							expression[l] = function[j];
							j++; i++; l++;
						}
						expression[l] = '\0';
						int p = 0;
						if (strlen(expression) == 0) {
							decision = 0;
							if (comment == 1) {
								puts("\nLogarithm base is null.\n");
							}
							if (decision == 0) {
								return decision;
							}
						}
						manageExpression(expression, result1, result2, verify);
						for (p = 0; expressionF[p] != '\0'; p++) {
							expression[p] = expressionF[p];
						}
						expression[p] = '\0';

						decision = dataVerifier(expression, result1, result2, comment, verify);
						if (decision == 0) {
							return decision;
						}
						if (data[i] == 'b') {
							k++;
						}
						if (k != 2) {
							decision = 0;
							if (comment == 1) {
								puts("\nNumber of \"bs\" for advanced logarithmic function can't be different of 2.\n");
							}

							return decision;
						}
					}
					k = 0;
					if (data[i] == 'D') {
						function[j] = data[i];
						j++; i++;
						k++;
						l = 0;
						while ((data[i] == 'D'&&data[i + 1] == '(') == false && data[i] != '\0') {
							function[j] = data[i];
							expression[l] = function[j];
							j++; i++; l++;
							if ((data[i] == 'D'&&data[i + 1] == '(') == false && data[i + 1] != '(') {
								function[j] = data[i];
								expression[l] = function[j];
								if (data[i] == 'D'&&data[i + 1] == '(') {
									i--;
								}
								j++; i++; l++;
							}
						}
						expression[l] = '\0';
						if (strlen(expression) == 0) {
							decision = 0;
							if (comment == 1) {
								puts("\nRoot degree is null.\n");
							}
							if (decision == 0) {
								return decision;
							}
						}
						manageExpression(expression, result1, result2, verify);
						for (p = 0; expressionF[p] != '\0'; p++) {
							expression[p] = expressionF[p];
						}
						expression[p] = '\0';
						decision = dataVerifier(expression, result1, result2, comment, verify);
						if (decision == 0) {
							return decision;
						}
						if (data[i] == 'D') {
							k++;
						}
						if (k != 2) {
							decision = 0;
							if (comment == 1) {
								puts("\nNumber of \"Ds\" for advanced root function can't be different of 2.\n");
							}
							return decision;
						}
					}
					function[j] = data[i];
					j++; i++;
				}
				function[j] = '\0';
				j = 0;
				if (verifyLetter(function[0]) == 1) {
					while ((verifyLetter(function[j]) == 1 || function[j] == '_') && function[j] != '\0') {
						if (function[j] == 'b'&&function[j - 1] != 'c') {
							j++;
							while ((function[j] == 'b'&&function[j + 1] == '\0') == false && function[j] != '\0') {
								j++;
							}
							if (function[j + 1] != '\0') {
								decision = 0;
								return decision;
							}
						}
						if (function[j] == 'D') {
							j++;
							while ((function[j] == 'D'&&function[j + 1] == '\0') == false && function[j] != '\0') {
								j++;
							}
							if (function[j + 1] != '\0') {
								decision = 0;
								return decision;
							}
						}
						j++;
					}
					if (j != strlen(function)) {
						decision = 0;
						return decision;
					}
				}
				resultI = 0.5;
				int ko = strlen(function);
				function[ko] = '?'; function[ko + 1] = '\0';
				if (functionProcessor(function, 0.2, 1.0, result1) != 0 || function[0] == 'r'&&function[1] == 'e'&&function[2] == 's'&&function[3] == 't'&&function[4] == '\0' || function[0] == 'q'&&function[1] == 'u'&&function[2] == 'o'&&function[3] == 't'&&function[4] == 'i'&&function[5] == 'e'&&function[6] == 'n'&&function[7] == 't'&&function[8] == '\0' || function[0] == 'a'&&function[1] == 'c'&&function[2] == 'o'&&function[3] == 's'&&function[4] == 'h'&&function[5] == '\0' || function[0] == 'a'&&function[1] == 'c'&&function[2] == 'o'&&function[3] == 't'&&function[4] == 'a'&&function[5] == 'n'&&function[6] == 'h'&&function[7] == '\0') {
					decision = 1;
				}
				else {
					if (strlen(function) > 0) {
						if (comment == 1) {
							puts("\nInvalid function entered.\n");
						}
						decision = 0;
					}
					return decision;
				}
			}
			if (data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4' || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9' || data[i] == '.' || data[i] == '_' || data[i] == '!' || data[i] == '+' || data[i] == '-' || data[i] == '/' || data[i] == '*' || data[i] == 'x' || data[i] == '^' || data[i] == 'e' || data[i] == 'p'&&data[i + 1] == 'i' || data[i - 1] == 'p'&&data[i] == 'i') {
				j = 0;
				while ((data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4' || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9' || data[i] == '.' || data[i] == '_' || data[i] == '!' || data[i] == '+' || data[i] == '-' || data[i] == '/' || data[i] == '*' || data[i] == 'x' || data[i] == '^' || data[i] == 'e' || data[i] == 'p'&&data[i + 1] == 'i' || data[i - 1] == 'p'&&data[i] == 'i') && data[i] != '\0') {
					i++;
					decision = 1;
					j++;
				}
			}
			j = 0;
			if (data[i] == 'r'&&data[i + 1] == 'e'&&data[i + 2] == 's'&&data[i + 3] != 't') {
				decision = 1;
				i = i + 3;
			}
			if (data[i] == 'B' || data[i] == 'O' || data[i] == 'H' || data[i] == 'Q' || data[i] == 'W' || data[i] == 'R' || data[i] == 'T' || data[i] == 'Y' || data[i] == 'U' || data[i] == 'I' || data[i] == 'P' || data[i] == 'A' || data[i] == 'S' || data[i] == 'D' || data[i] == 'F' || data[i] == 'G' || data[i] == 'J' || data[i] == 'K' || data[i] == 'L' || data[i] == 'Z' || data[i] == 'X' || data[i] == 'C' || data[i] == 'V' || data[i] == 'N' || data[i] == 'M' || data[i] == 'm' || data[i] == 'n' || data[i] == 'b' || data[i] == 'v' || data[i] == 'z' || data[i] == 'k' || data[i] == 'j' || data[i] == 'h' || data[i] == 'f' || data[i] == 'a' || data[i] == 'p' || data[i] == 'o' || data[i] == 'u' || data[i] == 'y' || data[i] == 'w') {
				j = 0;
				while (data[i] != '+'&&data[i] != '-'&&data[i] != '*'&&data[i] != '/'&&data[i] != '^'&&data[i] != ')'&&data[i] != '(' && data[i] != '\0') {
					variable[j] = data[i];
					j++;
					i++;
				}
				variable[j] = '\0';
				if (initialProcessor(variable, result1) != 0) {
					decision = 1;
					variable[j] = '\0';
				}
				else {
					variable[j] = '\0';
					int w = 0;
					while (letterVariables(variable[w]) == 1 && variable[w] != '\0') {
						w++;
					}
					variable[w] = '\0';
					processVariable(variable);
					if (validVar == 1) {
						decision = 1;
					}
				}
			}
		}
		return decision;
	}
	else {
		decision = 0;
		printf("\nData for verification is null.\n");
		return decision;
	}
}

boolean atcFunctions(char functionName[DIM]) {
	int i = 0, j = 0, funcIndex = 0, g = 0, h = 0;
	boolean isFunction = false;
	char namesForFunctions[DIM] = "initialProcessor,functionProcessor", saveFunction[DIM] = "";
	for (j = 0; functionName[j] != '\0'; j++) {
		saveFunction[j] = functionName[j];
	}
	saveFunction[j] = '\0';
	functionName[strlen(functionName) - 2] = '\0';
	for (j = 0; functionName[j] != '\0'; j++) {
		if (functionName[j] == '(') {
			functionName[j] = '\0';
			break;
		}
	}
	for (i = 0; namesForFunctions[i] != '\0'; i++) {
		j = 0;
		if (namesForFunctions[i] == functionName[j]) {
			j = 0; g = 0;
			while (namesForFunctions[i] != '\0'&&namesForFunctions[i] != ',') {
				if (namesForFunctions[i] == functionName[j]) {
					j++;
				}
				i++;
				g++;
			}
			if (g == j&&j == strlen(functionName)) {
				isFunction = true;
				h = i;
			}
		}
	}
	if (isFunction) {
		for (j = 0; j <= h; j++) {
			if (namesForFunctions[j] == ',' || namesForFunctions[j] == '\0') {
				funcIndex++;
			}
		}
		printf("\nThis is the function number %d in the list of atc functions!\n", funcIndex);
	}
	for (j = 0; saveFunction[j] != '\0'; j++) {
		functionName[j] = saveFunction[j];
	}
	functionName[j] = '\0';
	return isFunction;
}