

#include "stdafx.h"
#include "atc_functions.h"

double ansIV = 0, ansRV = 0, ans[DIM], ansI[DIM], valInd[DIM][DIM], values[DIM][DIM], resultFI = 0, valuesS[DIM][DIM], valuesSI[DIM][DIM], valuesF[DIM][DIM], valuesFI[DIM][DIM], valuesI[DIM][DIM], resultR = 0, resultI = 0, intVal = 0;
char atcPath[DIM] = "", varRename[DIM] = "", revariable[DIM] = "", pathNAme[DIM] = "", variableSTring[DIM] = "", expressionF[DIM] = "", usRFunctions[DIM] = ",", usRFuncTrans[DIM] = ",";
int processingOK = 1, executedSolver = 0, isFromMain = 0, solutioned = 0, verify = 0, arG = 1, Mode = 0, isFromSolveNow = 0, valid = 0, validVar = 0, count = 2, synTest = 0, valRenamedVar = 0, continu = 1, cleanhistory = 0, rf = 0, verified = 0, nPlaces = 0, verbose = 0, feedbackValidation = 0;
clock_t start_processing, end_processing;

void main(int argc, char *argv[]) {
	char dataToSolve[DIM] = "";
	FILE *fout = NULL;
	int Colors = 1, tD = 0, i = 0;
	char  path[DIM] = "", trigData[DIM] = "";
	double result1 = 0, result2 = 0;
	getATCPath();
	if (argc < 2) {
		char commandF[400] = "";
		sprintf(commandF, "%s\\atc_launcher.exe", atcPath);
		using namespace std;
		std::string s = string(commandF);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), sw, NULL, NULL, SW_SHOW);
		on_start();
		applySettings(Colors);
		system("title Advanced Trigonometry Calculator v1.9.8");
		continu = about();
	}
	if (continu == 1) {
		system("title Advanced Trigonometry Calculator v1.9.8       ==) ATC is ready to process data. (==");
		do {
			usRFunctions[0] = ','; usRFuncTrans[0] = ',';
			usRFunctions[1] = '\0'; usRFuncTrans[1] = '\0';
			fflush(NULL);
			tD = 0;
			toSolve(rf);
			if (argc < 2) {
				sprintf(trigData, "");
				printf(">");
				if (executedSolver == 1) {
					executedSolver = 0;
					cls();
				}
				gets_s(trigData);
				start_processing = clock();
				system("title Advanced Trigonometry Calculator v1.9.8       ==) Processing... (==");
			}
			else {
				arG = 1;
				trigData[0] = '\0';
				while (arG < argc) {
					sprintf(trigData, "%s%s", trigData, argv[arG]);
					arG++;
				}
				addATCPath();
			}
			sprintf(path, "%s\\history.txt", atcPath);
			if (fout != NULL) {
				fclose(fout);
			}
			fout = NULL;
			while (fout == NULL) {
				fout = fopen(path, "a+");
			}
			for (tD = 0; trigData[tD] != '\0'; tD++) {
				runningScript = false;
				fflush(NULL);
				char fTrig[DIM] = "", arithTrig[DIM] = "";
				varRename[0] = '\0'; revariable[0] = '\0';
				validVar = 1; 	processingOK = 1;
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
				resultR = sqrt(DBL_MAX);
				variableController("INF", resultR);
				processVariable("x");
				if (validVar == 0) {
					resultR = 0;
					variableController("x", 0);
				}
				processVariable("x");
				variableController("x", 0);
				sprintf(fTrig, "%s", arithTrig); verbose = 0;
				main_core(arithTrig, fTrig, fout, path, result1, result2, 1);
				sprintf(arithTrig, ""); sprintf(fTrig, ""); arithTrig[0] = '\0'; fTrig[0] = '\0';
				if (verified == 1) {
					result1 = resultR;
					result2 = resultI;
					verified = 0;
				}
				fflush(NULL);
				sprintf(arithTrig, "");
			}
			if (fout != NULL) {
				fclose(fout);
			}
			if (continu != 1) {
				fclose(fout);
			}
			if (argc >= 2) {
				exit(0);
			}
			char Path[DIM] = "";
			sprintf(Path, "%s\\temp.txt", atcPath);
			FILE *Try = NULL;
			Try = fopen(Path, "r");
			if (Try != NULL) {
				fclose(Try);
				Try = fopen(Path, "w");
				fclose(Try);
			}
			end_processing = clock();
			double time_ms = (end_processing - start_processing) / (CLOCKS_PER_SEC / 1000);
			double time_s = qu(time_ms, 1000);
			double time_ms_final = re(time_ms, 1000);
			char state[DIM] = "";
			time_t hourF;
			time(&hourF);
			char *tim;
			tim = ctime(&hourF);
			tim[24] = '\0';
			char hou[3] = { tim[11], tim[12], '\0' };
			int Hours = atoi(hou);
			char min[3] = { tim[14], tim[15], '\0' };
			int Minutes = atoi(min);
			char sec[3] = { tim[17], tim[18], '\0' };
			int Seconds = atoi(sec);
			char toOpen[DIM] = "";
			sprintf(toOpen, "%s\\history.txt", atcPath);
			fout = fopen(toOpen, "a+");
			char yea[5] = { tim[20], tim[21], tim[22], tim[23], '\0' };
			int years = atoi(yea);
			char da[3] = { tim[8], tim[9], '\0' };
			int days = atoi(da);
			int months = 0;
			if (tim[4] == 'J'&&tim[5] == 'a'&&tim[6] == 'n') {
				months = 1;
			}
			if (tim[4] == 'F'&&tim[5] == 'e'&&tim[6] == 'b') {
				months = 2;
			}
			if (tim[4] == 'M'&&tim[5] == 'a'&&tim[6] == 'r') {
				months = 3;
			}
			if (tim[4] == 'A'&&tim[5] == 'p'&&tim[6] == 'r') {
				months = 4;
			}
			if (tim[4] == 'M'&&tim[5] == 'a'&&tim[6] == 'y') {
				months = 5;
			}
			if (tim[4] == 'J'&&tim[5] == 'u'&&tim[6] == 'n') {
				months = 6;
			}
			if (tim[4] == 'J'&&tim[5] == 'u'&&tim[6] == 'l') {
				months = 7;
			}
			if (tim[4] == 'A'&&tim[5] == 'u'&&tim[6] == 'g') {
				months = 8;
			}
			if (tim[4] == 'S'&&tim[5] == 'e'&&tim[6] == 'p') {
				months = 9;
			}
			if (tim[4] == 'O'&&tim[5] == 'c'&&tim[6] == 't') {
				months = 10;
			}
			if (tim[4] == 'N'&&tim[5] == 'o'&&tim[6] == 'v') {
				months = 11;
			}
			if (tim[4] == 'D'&&tim[5] == 'e'&&tim[6] == 'c') {
				months = 12;
			}
			char toTitle[DIM] = "";
			sprintf(state, "title Advanced Trigonometry Calculator v1.9.8       ==) Processed in %Gs and %Gms. ATC is ready to process more data. Latest ATC response was at %04d/%02d/%02d %02d:%02d:%02d (==", time_s, time_ms_final, years, months, days, Hours, Minutes, Seconds);
			system(state);
		} while (continu == 1);
	}
	exit(0);
}

boolean processTxt(char path[DIM], int re) {
	double result1 = 0, result2 = 0, anstxt[DIM], anstxtI[DIM];
	FILE *fin = NULL, *fout = NULL, *open = NULL, *read = NULL;
	char addBar[DIM] = "", savePath[DIM] = "", arith[DIM] = "", sendFunc[DIM] = "", resp[30] = "_answers.txt", varLetters[DIM] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
	int tD = 0, i, j, cP = 0, k, d, e, f, space = 0, v = 0, l = 0, m = 0, re1 = 0, save_rf = rf;
	boolean toWrite = true;
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
	char saveSendFunc[DIM] = "";
	while (read == NULL && i < 100) {
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
		sprintf(saveSendFunc, sendFunc);
		if (isContained("script", sendFunc) && strStart == 0) {
			atcProgramming(sendFunc);
			toWrite = false;
			return toWrite;
		}
		else {
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
				fflush(NULL);
				tD = 0;
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
					resultR = sqrt(DBL_MAX);
					variableController("INF", resultR);
					processVariable("x");
					if (validVar == 0) {
						resultR = 0;
						variableController("x", 0);
					}
					processVariable("x");
					variableController("x", 0);
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
					if (isContained("script", saveSendFunc) && strStart == 0) {
						toWrite = false;
					}
					if (toWrite) {
						verbose = 0;
						if (isContained("solver", arith)) {
							if (isContained("x", arith)) {
								resultR = 0; resultI = 0;
							}
						}
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
					fflush(NULL);
					sprintf(arith, "");
					if (fin != NULL) {
						fclose(fin);
					}
				}
				if (fin != NULL) {
					fclose(fin);
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
	}
	int h;
	for (h = 0; path[h] != '\0'; h++) {
		expressionF[h] = path[h];
	}
	expressionF[h] = '\0';
	if (fin != NULL) { fclose(fin); }if (fout != NULL) { fclose(fout); }if (open != NULL) { fclose(open); } if (read != NULL) { fclose(read); }
	rf = save_rf;
	if (!toWrite) {
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

boolean dataVerifier(char data[DIM], double result1, double result2, int comment, int verify) {
	boolean decision = true;
	if (abs((int)strlen(data)) > 0) {
		int kg = 0, kc = 0, i = 0;
		for (i = 0; data[i] != '\0'; i++) {
			if (data[i] == '(') {
				kg++;
			}
			if (data[i] == ')') {
				kc++;
			}
			if (kc > kg) {
				break;
			}
		}
		if (kg != kc) {
			if (kc > kg) {
				decision = false;
				if (comment == 1) {
					printf("\nError in parentheses. \n ==> The number of left and right parenthesis entered must be equal.\n ==> You can not have a valid math expression where a close parenthesis \")\" is found before its open parenthesis \"(\".\n ==> Enter \"[\" or \"{\" is the same as \"(\" and \"]\" or \"}\" is the same as \")\".\n ==> The expression that you entered has %d left parenthesis and %d right parenthesis.\n", kg, kc);
				}
				return decision;
			}
			decision = false;
			if (comment == 1) {
				printf("\nError in parentheses. \n ==> The number of left and right parenthesis entered must be equal.\n ==> Enter \"[\" or \"{\" is the same as \"(\" and \"]\" or \"}\" is the same as \")\".\n ==> The expression that you entered has %d left parenthesis and %d right parenthesis.\n", kg, kc);
			}
			return decision;
		}
		else {
			int cp = 0, mark = 0;
			int c = 0, d = 0, k = 0, l = 0, h = 0, s = 0;
			int parent[DIM];
			for (s = 0; s < abs((int)strlen(data)); s++) {
				parent[s] = 0;
			}
			for (s = 0; data[s] != '\0'&&s < abs((int)strlen(data)); s++) {
				if (data[s] == '(') {
					d = 0;
					c++;
					parent[s] = c;
					d = 1;
					k = c;
				}
				else {
					if (data[s] == ')') {
						d = 0;
						h = 0;
						l = 2;
						do {
							l = 0;
							h = 0;
							while (h < abs((int)strlen(data))) {
								if (parent[h] == k) {
									l++;
								}
								if (l == 2) {
									l = 0;
									k--;
								}
								h++;
							}

						} while (l == 2);
						h = 0;
						while (l != 1 && h < abs((int)strlen(data))) {
							h = 0;
							l = 0;
							while (h < abs((int)strlen(data))) {
								if (parent[h] == k) {
									l++;
								}
								if (l == 2) {
									k--;
									h = 0;
									l = 0;
								}
								h++;
							}
						}
						parent[s] = k;
					}
					else {
						parent[s] = 0;
					}
				}
			}
			int klp = s, savePar = 0;
			data[s] = '\0';
			for (s = 0; data[s] != '\0'; s++) {
				if (parent[s + 1] == parent[s] + 1 && parent[s] != 0) {
					savePar = s;
					s++;
					while (parent[s] != parent[savePar] && s < abs((int)strlen(data))) {
						s++;
					}
					if (parent[s - 1] == parent[s] + 1 && parent[s - 1] != 0) {
						decision = false;
						if (comment == 1) {
							printf("\nError in parentheses. \n ==> The number of left and right parenthesis entered must be equal.\n ==> You can not have a valid math expression where a close parenthesis \")\" is found before its open parenthesis \"(\".\n ==> Enter \"[\" or \"{\" is the same as \"(\" and \"]\" or \"}\" is the same as \")\".\n ==> The expression that you entered has %d left parenthesis and %d right parenthesis.\n", kg, kc);
						}
						return decision;
					}
					else {
						s = savePar;
					}
				}
			}
		}
		int j = 0, k = 0, l = 0, kr = 0, kl = 0, v = 0, cChars = 0, fr = 0, ra = 0, nDot = 0, g = 0, d = 0, w = 0, y = 0, t = 0, space = 0;
		char function[DIM] = "", variable[DIM] = "", expression[DIM] = "", text[DIM] = "", value[DIM] = "", saveVar[DIM] = "";
		char validChars[DIM] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM123456789.0/*-+\\!#()[]{} ^_;";
		char numsysData[DIM] = "";
		int u = 0, p = 0;
		if (synTest == 0) {
			int y = 0, r = 0;
			char funcToCheck[DIM] = "";
			if (isContained("logb", data)) {

				y = strStart;
				while ((data[y - 1] == 'b'&&data[y] == '(') == false && data[y] != '\0') {
					y++;
				}
				r = y + 1;
			}
			if (isContained("rtD", data)) {
				y = strStart;
				while ((data[y - 1] == 'D'&&data[y] == '(') == false && data[y] != '\0') {
					y++;

				}
				r = y + 1;
			}
			decision = true;
			synTest = 1;
			if (nPlaces != 0) {
				if (nPlaces == 1000) {
					if (comment == 1) {
						puts("\nBinary places number entered with errors.\n");
					}
					decision = false;
					return decision;
				}
				if (nPlaces == 8000) {
					if (comment == 1) {
						puts("\nOctal places number entered with errors.\n");
					}
					decision = false;
					return decision;
				}
				if (nPlaces == 10000) {
					if (comment == 1) {
						puts("\nDecimal places number entered with errors.\n");
					}
					decision = false;
					return decision;
				}
				if (nPlaces == 16000) {
					if (comment == 1) {
						puts("\nHexadecimal places number entered with errors.\n");
					}
					decision = false;
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
							decision = false;
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
							decision = false;
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
							decision = false;
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
							decision = false;
							return decision;
						}
					}
				}
			}
			w = abs((int)strlen(data)) - 4;
			if ((data[w - 1] == '+' || data[w - 1] == '-' || data[w - 1] == '*' || data[w - 1] == '/' || data[w - 1] == '^') && data[w] == '+'&&data[w + 1] == '0'&&data[w + 2] == '+'&&data[w + 3] == '0'&&data[w + 4] == '\0') {
				verify = 0;
				if (comment == 1) {
					puts("\nYour expression is terminating with an arithmetic symbol.\n");
				}
				decision = false;
				return decision;
			}
			for (w = 0; data[w] != '\0'; w++) {
				if ((data[w] == '+' || data[w] == '-' || data[w] == '*' || data[w] == '/' || data[w] == '^') && (data[w + 1] == '+' || data[w + 1] == '-'&&data[w - 2] != '1'&&data[w - 1] != '0' || data[w + 1] == '*' || data[w + 1] == '/' || data[w + 1] == '^' || data[w + 1] == '!')) {
					verify = 0;
					if (comment == 1) {
						puts("\nYour expression has consecutive arithmetic symbols.\n");
					}
					decision = false;
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
					if (funcF == 0.5&&isContained("solver", varValidator)) {
						if (!isContained("x", data)) {
							if (comment == 1) {
								puts("\nError: No 'x' detected in the argument of your solver function.\n");
							}
							decision = false;
							return decision;
						}
					}
					if (funcF == 0.5&&isContained("det", varValidator)) {
						char matrix[DIM] = "";
						if (isContained("det", data)) {
							int det = strEnd;
							int t = 0, rCount = 0, lCount = 0;
							if (data[det] == '(') {
								lCount++;
								det++;
								while (lCount > rCount&&data[det] != '\0') {
									if (data[det] == '(') {
										lCount++;
									}
									if (data[det] == ')') {
										rCount++;
									}
									if (lCount != rCount) {
										matrix[t] = data[det];
										t++;
									}
									det++;
								}
								matrix[t] = '\0';
							}
							int mIndex = 0, ff = 0, cols = 1, lins = 1, saveCols = -1, errorCols = 0;
							do {
								char value[DIM] = "";
								ff = 0;
								while (matrix[mIndex] != '\\'&&matrix[mIndex] != ';'&&matrix[mIndex] != '\0') {
									value[ff] = matrix[mIndex];
									ff++; mIndex++;
								}
								value[ff] = '\0';
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
								decision = true;
							}
							else {
								if (comment == 1) {
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
								decision = false;
								return decision;
							}
						}
					}
					sprintf(varValidator, "%s", saveExpr);
					if (funcF != 0.5) {
						if (validVar == 0) {
							if (varValidator[0] == 'E' || varValidator[0] == 'B' || varValidator[0] == 'O' || varValidator[0] == 'H' || varValidator[0] == 'P' || varValidator[0] == 'e' || varValidator[0] == 'p'&&varValidator[1] == 'i' || varValidator[0] == 'I'&&varValidator[1] == 'N'&&varValidator[2] == 'F') {
								if (varValidator[0] == 'E' || varValidator[0] == 'B' || varValidator[0] == 'O' || varValidator[0] == 'H' || initialProcessor(varValidator, 0) != 0) {
									decision = true;
								}
								else {
									decision = false;
									if (comment == 1) {
										printf("\nThe variable \"%s\" is not created yet.\n", saveVar);
									}
									return decision;
								}
							}
							else {
								decision = false;
								if (comment == 1) {
									printf("\nThe variable \"%s\" is not created yet.\n", saveVar);
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
				decision = false;
				if (comment == 1) {
					puts("\nYou entered more than one dot on the entered value.\n");
				}
				return decision;
			}
		}
		for (ra = 0; data[ra] != '\0'; ra++) {
			if (data[ra] == '_'&&data[ra - 1] == '_') {
				decision = false;
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
			decision = false;
			if (comment == 1) {
				puts("\nYou entered invalid characters.\n");
			}
			return decision;
		}
		if ((data[0] == '+' || data[0] == '-' || data[0] == '*' || data[0] == '/' || data[0] == '^') && (data[1] == '0'&&data[2] == '\0')) {
			decision = false;
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
			if (data[i] == '"' || data[i] == '%' || data[i] == '&' || data[i] == '"' || data[i] == '=' || data[i] == '?' || data[i] == '@' || data[i] == '£' || data[i] == '§' || data[i] == '\'' || data[i] == '€' || data[i] == '¨' || data[i] == '´' || data[i] == '`' || data[i] == 'ª' || data[i] == 'º' || data[i] == '~' || data[i] == ',' || data[i] == ':' || data[i] == '«' || data[i] == '»') {
				decision = false;
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
				if (data[i + 1] == '+' || data[i + 1] == '-' || data[i + 1] == '*' || data[i + 1] == '/' || data[i + 1] == '^' || data[i + 1] == '!') {
					decision = false;
					if (comment == 1) {
						puts("\nYou entered an arithmetic symbol next to \"(\".\n");
					}
					return decision;
				}
			}
			if (data[i] == ')') {
				kr++;
				if (data[i - 1] == '+' || data[i - 1] == '-' || data[i - 1] == '*' || data[i - 1] == '/' || data[i - 1] == '^') {
					decision = false;
					if (comment == 1) {
						puts("\nYou entered an arithmetic symbol previous to \")\".\n");
					}
					return decision;
				}
			}
		}
		if (kr != kl) {
			decision = false;
			return decision;
		}
		for (i = 0; data[i] != '\0'; i++) {
			j = 0;
			if (data[i] == 'r'&&data[i + 1] == 'e'&&data[i + 2] == 's'&&data[i + 3] != 't') {
				decision = true;
				i = i + 3;
			}
			if (data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4' || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9' || data[i] == '.' || data[i] == '_' || data[i] == '!' || data[i] == '+' || data[i] == '-' || data[i] == '/' || data[i] == '*' || data[i] == '^' || data[i] == 'e' || data[i] == 'p'&&data[i + 1] == 'i' || data[i - 1] == 'p'&&data[i] == 'i') {
				j = 0;
				while (data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4' || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9' || data[i] == '.' || data[i] == '_' || data[i] == '!' || data[i] == '+' || data[i] == '-' || data[i] == '/' || data[i] == '*' || data[i] == '^' || data[i] == 'e' || data[i] == 'p'&&data[i + 1] == 'i' || data[i - 1] == 'p'&&data[i] == 'i') {
					i++;
					decision = true;
					j++;
				}
			}
			if (data[i] == 'r'&&data[i + 1] == 'e'&&data[i + 2] == 's'&&data[i + 3] != 't') {
				decision = true;
				i = i + 3;
			}
			if (data[i] == 'a' || data[i] == 's'&&data[i - 1] != 'e'&&data[i - 2] != 'r' || data[i] == 'c' || data[i] == 't' || data[i] == 'g' || data[i] == 'd' || data[i] == 'l' || data[i] == 'q' || data[i] == 'r') {
				decision = true;
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
							decision = false;
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
							decision = false;
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
							decision = false;
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
							decision = false;
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
								decision = false;
								return decision;
							}
						}
						if (function[j] == 'D') {
							j++;
							while ((function[j] == 'D'&&function[j + 1] == '\0') == false && function[j] != '\0') {
								j++;
							}
							if (function[j + 1] != '\0') {
								decision = false;
								return decision;
							}
						}
						j++;
					}
					if (j != strlen(function)) {
						decision = false;
						return decision;
					}
				}
				resultI = 0.5;
				int ko = abs((int)strlen(function));
				function[ko] = '?'; function[ko + 1] = '\0';
				if (functionProcessor(function, 0.2, 1.0, result1) != 0 || function[0] == 'r'&&function[1] == 'e'&&function[2] == 's'&&function[3] == 't'&&function[4] == '\0' || function[0] == 'q'&&function[1] == 'u'&&function[2] == 'o'&&function[3] == 't'&&function[4] == 'i'&&function[5] == 'e'&&function[6] == 'n'&&function[7] == 't'&&function[8] == '\0' || function[0] == 'a'&&function[1] == 'c'&&function[2] == 'o'&&function[3] == 's'&&function[4] == 'h'&&function[5] == '\0' || function[0] == 'a'&&function[1] == 'c'&&function[2] == 'o'&&function[3] == 't'&&function[4] == 'a'&&function[5] == 'n'&&function[6] == 'h'&&function[7] == '\0') {
					decision = true;
				}
				else {
					if (strlen(function) > 0) {
						if (comment == 1) {
							puts("\nInvalid function entered.\n");
						}
						decision = false;
					}
					return decision;
				}
			}
			if (data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4' || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9' || data[i] == '.' || data[i] == '_' || data[i] == '!' || data[i] == '+' || data[i] == '-' || data[i] == '/' || data[i] == '*' || data[i] == '^' || data[i] == 'e' || data[i] == 'p'&&data[i + 1] == 'i' || data[i - 1] == 'p'&&data[i] == 'i') {
				j = 0;
				while ((data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4' || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9' || data[i] == '.' || data[i] == '_' || data[i] == '!' || data[i] == '+' || data[i] == '-' || data[i] == '/' || data[i] == '*' || data[i] == '^' || data[i] == 'e' || data[i] == 'p'&&data[i + 1] == 'i' || data[i - 1] == 'p'&&data[i] == 'i') && data[i] != '\0') {
					i++;
					decision = true;
					j++;
				}
			}
			j = 0;
			if (data[i] == 'r'&&data[i + 1] == 'e'&&data[i + 2] == 's'&&data[i + 3] != 't') {
				decision = true;
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
					decision = true;
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
						decision = true;
					}
				}
			}
		}
		return decision;
	}
	else {
		decision = false;
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
			if (g == j && j == strlen(functionName)) {
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