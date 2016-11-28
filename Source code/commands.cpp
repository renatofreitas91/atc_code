#include "stdafx.h"

int commands(char arithTrig[DIM], char path[DIM], double result1, double result2) {
	FILE *fout = NULL, *fclean = NULL;
	char stringV[DIM] = "";
	fout = NULL;
	while (fout == NULL) {
		fout = fopen(path, "a+");
	}
	int command = 0, i = 0, r = 0, year = 0, s = 0;
	i = 0;
	if (isCommand(arithTrig, "donate")) {
		command = 1;
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"start https://sourceforge.net/p/advantrigoncalc/donate/?source=navbar\""), NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "atcfacebook")) {
		command = 1;
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"start https://www.facebook.com/advantrigoncalc/\""), NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "atcsourceforge")) {
		command = 1;
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"start https://sourceforge.net/projects/advantrigoncalc/\""), NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "atcfromcmd")) {
		command = 1;
		char comm[300] = "";
		sprintf(comm, "/C \"setx /M PATH \"%%PATH%%;%s\"", atcPath);
		using namespace std;
		std::string s = string(comm);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("runas"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		puts("\n==> You can now run cmd.exe and enter e.g. \"atc time\" <==\n");
		puts("");
	}

	if (isCommand(arithTrig, "autosolvetxt")) {
		command = 1;
		int p = 0;
		char paTH[DIM] = "";
		i = 0;
		puts("\n==> Drag to here the file for automatic processing and press the button \"Enter\" <==\n");
		while (strlen(paTH) == 0) {
			gets_s(paTH);
		}
		puts("\n==> Waiting for the flag \"SOLVE_NOW\" be detected in the last line of this file. <==\n");
		boolean ready = false;
		while (ready == readyToSolve(paTH)) {
			Sleep(2000);
		}
		processTxt(paTH, rf);
		printf("\n==> Close the file with the answers to continue. <==\n\n");
		fprintf(fout, "\n==> Close the file with the answers to continue. <==\n\n");
		openTxt();

	}
	if (isCommand(arithTrig, "solvequadraticequation") && arithTrig[i + 22] == '(') {
		command = 1;
		char values[DIM] = "", value[DIM] = "", saveValue[DIM] = "";
		int v = 0, ct = 0;
		double aR = 0, aI = 0, bR = 0, bI = 0, cR = 0, cI = 0;
		i = 23;
		while (arithTrig[i] != '\0'&&arithTrig[i] != ')') {
			if (arithTrig[i] == '\\') {
				ct++;
			}
			values[v] = arithTrig[i];
			v++; i++;
		}
		values[v] = '\0';
		if (ct != 2) {
			puts("\nError: You must include a, b and c values.\n");
		}
		else {
			puts(" ");
			v = 0;
			i = 0;
			while (values[i] != '\\') {
				value[v] = values[i];
				i++; v++;
			}
			value[v] = '\0';
			solveNow(value, 0, 0);
			aR = resultR;
			aI = resultI;
			i++; v = 0;
			while (values[i] != '\\') {
				value[v] = values[i];
				i++; v++;
			}
			value[v] = '\0';
			solveNow(value, 0, 0);
			bR = resultR;
			bI = resultI;
			i++; v = 0;
			while (values[i] != '\0') {
				value[v] = values[i];
				i++; v++;
			}
			value[v] = '\0';
			solveNow(value, 0, 0);
			cR = resultR;
			cI = resultI;
			multiplication(-1, 0, bR, bI);
			double minusbR = resultR, minusbI = resultI;
			multiplication(bR, bI, bR, bI);
			double bRquad = resultR, bIquad = resultI;
			multiplication(aR, aI, cR, cI);
			double acR = resultR, acI = resultI;
			multiplication(2, 0, aR, aI);
			double twoaR = resultR, twoaI = resultI;
			multiplication(4, 0, acR, acI);
			double fouracR = resultR, fouracI = resultI;
			subtraction(bRquad, bIquad, fouracR, fouracI);
			double radicandR = resultR, radicandI = resultI;
			exponentiation(radicandR, radicandI, 0.5, 0, 1);
			double sqrtR = resultR, sqrtI = resultI;
			subtraction(minusbR, minusbI, sqrtR, sqrtI);
			double minusR = resultR, minusI = resultI;
			sum(minusbR, minusbI, sqrtR, sqrtI);
			double plusR = resultR, plusI = resultI;
			division(plusR, plusI, twoaR, twoaI);
			double x1R = resultR, x1I = resultI;
			division(minusR, minusI, twoaR, twoaI);
			double x2R = resultR, x2I = resultI;
			if (x1R > 0 && x1I > 0) {
				printf("x1=%G+%Gi\n", x1R, x1I);
			}
			else {
				if (x1R > 0 && x1I < 0) {
					printf("x1=%G%Gi\n", x1R, x1I);
				}
				else {
					if (x1R < 0 && x1I > 0) {
						printf("x1=%G+%Gi\n", x1R, x1I);
					}
					else {
						if (x1R < 0 && x1I < 0) {
							printf("x1=%G%Gi\n", x1R, x1I);
						}
						else {
							if (x1R == 0 && x1I == 0) {
								printf("x1=%G\n", x1R);
							}
							else {
								if (x1R == 0 && x1I != 0) {
									printf("x1=%Gi\n", x1I);
								}
								else {
									if (x1R != 0 && x1I == 0) {
										printf("x1=%G\n", x1R);
									}
									else {
										printf("x1=%G+%Gi\n", x1R, x1I);
									}
								}
							}
						}
					}
				}
			}
			if (x2R > 0 && x2I > 0) {
				printf("x2=%G+%Gi\n", x2R, x2I);
			}
			else {
				if (x2R > 0 && x2I < 0) {
					printf("x2=%G%Gi\n", x2R, x2I);
				}
				else {
					if (x2R < 0 && x2I > 0) {
						printf("x2=%G+%Gi\n", x2R, x2I);
					}
					else {
						if (x2R < 0 && x2I < 0) {
							printf("x2=%G%Gi\n", x2R, x2I);
						}
						else {
							if (x2R == 0 && x2I == 0) {
								printf("x2=%G\n", x2R);
							}
							else {
								if (x2R == 0 && x2I != 0) {
									printf("x2=%Gi\n", x2I);
								}
								else {
									if (x2R != 0 && x2I == 0) {
										printf("x2=%G\n", x2R);
									}
									else {
										printf("x2=%G+%Gi\n", x2R, x2I);
									}
								}
							}
						}
					}
				}
			}
			puts(" ");
		}
	}
	if (isCommand(arithTrig, "sprint") && arithTrig[i + 6] == '(') {
		char vaString[DIM] = "";
		int x = 0, y = 0;
		y = i + 7;
		for (x = 0; arithTrig[y] != '\0' && (arithTrig[y - 1] == ')'&&arithTrig[y] == '+'&&arithTrig[y + 1] == '0'&&arithTrig[y + 2] == '\0') == false; x++) {
			stringV[x] = arithTrig[y];
			y++;
		}
		stringV[x] = '\0';
		stringV[strlen(stringV) - 1] = '\0';
		sprint(stringV, result1, result2);
		puts(" ");
		arithTrig[0] = '\0'; command = 1;
	}

	if (isCommand(arithTrig, "print") && arithTrig[i + 5] == '(') {
		char vaString[DIM] = "";
		int x = 0, y = 0;
		y = i + 6;
		if (arithTrig[i + 6] != '\"') {
			for (x = 0; arithTrig[y] != ')' && ((arithTrig[y] == '+'&&arithTrig[y + 1] == '0'&&arithTrig[y + 2] == '\0') == false); x++) {
				vaString[x] = arithTrig[y];
				y++;
			}
			vaString[x] = '\0';
			stringVariableToString(vaString);
			if (strlen(variableSTring) != 0) {
				print(variableSTring, result1, result2);
				puts(" ");
			}
		}
		else {
			y = i + 7;
			for (x = 0; arithTrig[y] != '\0' && (arithTrig[y] == ')'&&arithTrig[y] == '+'&&arithTrig[y + 1] == '0'&&arithTrig[y + 2] == '\0') == false; x++) {
				stringV[x] = arithTrig[y];
				y++;
			}
			stringV[x] = '\0';
			stringV[strlen(stringV) - 3] = '\0';
			print(stringV, result1, result2);
			puts(" ");
		}
		arithTrig[0] = '\0'; command = 1;
	}
	if (isCommand(arithTrig, "clockctd")) {
		command = 1;
		char comm[300] = "";
		sprintf(comm, "/C \"explorer.exe %s\\Extra\\ctd.exe\"", atcPath);
		using namespace std;
		std::string s = string(comm);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		puts("");
	}
	if (isCommand(arithTrig, "logoff")) {
		continu = 0;
		command = 1;
		if (IsPreviousToWindowsVista()) {
			system("C:\\WINDOWS\\System32\\shutdown -l");
		}
		else {
			system("C:\\WINDOWS\\System32\\shutdown /l");
		}
	}
	if (isCommand(arithTrig, "enabletxtdetector")) {
		command = 1;
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"del disable_txt_detector.txt\""), NULL, SW_SHOW);
		Sleep(200);
		puts(" ");
	}
	if (isCommand(arithTrig, "history")) {
		command = 1;
		puts(" ");
		printf("\n==> Close the history to continue. <==\n\n");
		char path4ATC[DIM] = "";
		sprintf(path4ATC, "notepad.exe %s\\history.txt", atcPath);
		system(path4ATC);
	}
	if (isCommand(arithTrig, "resetall")) {
		command = 1;
		puts(" ");
		FILE *start;
		char path4ATC[DIM] = "";
		sprintf(path4ATC, "%s\\onStart.txt", atcPath);
		start = fopen(path4ATC, "w");
		fprintf(start, "resetall");
		fclose(start);
		printf("\n==> Restart the application to apply changes entering \"restart atc\". <==\n\n");
	}
	if (isCommand(arithTrig, "resetsettings")) {
		command = 1;
		puts(" ");
		FILE *start;
		char path4ATC[DIM] = "";
		sprintf(path4ATC, "%s\\onStart.txt", atcPath);
		start = fopen(path4ATC, "w");
		fprintf(start, "resetsettings");
		fclose(start);
		printf("\n==> Restart the application to apply changes entering \"restart atc\". <==\n\n");
	}
	if (isCommand(arithTrig, "atcfolder")) {
		command = 1;
		char comm[300] = "";
		sprintf(comm, "/C \"explorer %s\"", atcPath);
		using namespace std;
		std::string s = string(comm);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		puts("");

	}

	if (isCommand(arithTrig, "sourcecode")) {
		command = 1;
		char comm[300] = "";
		sprintf(comm, "/C \"explorer %s\\Source code\\\"", atcPath);
		using namespace std;
		std::string s = string(comm);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		puts("");
	}
	if (isCommand(arithTrig, "scriptsexamples")) {
		command = 1;
		char comm[300] = "";
		sprintf(comm, "/C \"explorer %s\\Scripts examples\\\"", atcPath);
		using namespace std;
		std::string s = string(comm);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		puts("");
	}
	if (isCommand(arithTrig, "strings")) {
		command = 1;
		char comm[300] = "";
		sprintf(comm, "/C \"explorer %s\\Strings\\\"", atcPath);
		using namespace std;
		std::string s = string(comm);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		puts("");
	}
	if (isCommand(arithTrig, "userfunctions")) {
		command = 1;
		char comm[300] = "";
		sprintf(comm, "/C \"explorer %s\\User functions\\\"", atcPath);
		using namespace std;
		std::string s = string(comm);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		puts("");
	}

	if (isCommand(arithTrig, "tosolve")) {
		command = 1;
		char comm[300] = "";
		sprintf(comm, "/C \"explorer %s\\To solve\\\"", atcPath);
		using namespace std;
		std::string s = string(comm);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
		puts("");
	}

	if (isCommand(arithTrig, "restartatc")) {
		command = 1;
		continu = 0;
		char path4ATC[DIM] = "";
		sprintf(path4ATC, "%s\\atc.exe", atcPath);
		using namespace std;
		std::string s = string(path4ATC);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), sw, NULL, NULL, SW_SHOW);
	}

	if (isCommand(arithTrig, "runatc")) {
		command = 1;
		puts(" ");
		char path4ATC[DIM] = "";
		sprintf(path4ATC, "%s\\atc.exe", atcPath);
		using namespace std;
		std::string s = string(path4ATC);
		std::wstring stemp = std::wstring(s.begin(), s.end());
		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, _T("open"), sw, NULL, NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "updateportable")) {
		command = 1;
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"start http://sourceforge.net/projects/advantrigoncalc/files/Advanced%20Trigonometry%20Calculator.zip/download\""), NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "update")) {
		command = 1;
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"start http://sourceforge.net/projects/advantrigoncalc/files/Setup%20Advanced%20Trigonometry%20Calculator.exe/download\""), NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "userguide")) {
		command = 1;
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("Advanced Trigonometry Calculator - User Guide.pdf"), NULL, NULL, SW_SHOW);
	}
	if (isCommand(arithTrig, "sleep")) {
		command = 1;
		puts(" ");
		ShellExecute(NULL, _T("runas"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"powercfg -hibernate off\""), NULL, SW_SHOW);
		Sleep(5000);
		system("C:\\WINDOWS\\System32\\Rundll32.exe powrprof.dll,SetSuspendState Sleep");
	}
	if (isCommand(arithTrig, "lock")) {
		command = 1;
		puts(" ");
		system("C:\\WINDOWS\\System32\\Rundll32.exe User32.dll,LockWorkStation");
	}

	if (isCommand(arithTrig, "hibernate")) {
		command = 1;
		puts(" ");
		ShellExecute(NULL, _T("runas"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"powercfg -hibernate on\""), NULL, SW_SHOW);
		Sleep(5000);
		system("C:\\WINDOWS\\System32\\rundll32.exe PowrProf.dll,SetSuspendState Hibernate");
	}
	if (isCommand(arithTrig, "shutdown")) {
		continu = 0;
		command = 1;
		if (IsPreviousToWindowsVista()) {
			system("C:\\WINDOWS\\System32\\shutdown -s");
		}
		else {
			system("C:\\WINDOWS\\System32\\shutdown /s");
		}
	}
	if (isCommand(arithTrig, "restartpc")) {
		continu = 0;
		command = 1;
		if (IsPreviousToWindowsVista()) {
			system("C:\\WINDOWS\\System32\\shutdown -r");
		}
		else {
			system("C:\\WINDOWS\\System32\\shutdown /r");
		}
	}
	if (isCommand(arithTrig, "exit")) {
		continu = 0;
		fprintf(fout, "\n");
		command = 1;
	}
	if (isCommand(arithTrig, "clean")) {
		cls(); command = 1;
		arithTrig[0] = '\0';
		fprintf(fout, "\n");
	}
	if (isCommand(arithTrig, "about")) {
		arithTrig[0] = '\0'; command = 1;
		cls();
		about2();
		fprintf(fout, "\n");
	}
	if (isCommand(arithTrig, "mode")) {
		arithTrig[0] = '\0'; command = 1;
		printf("\n==> Configuration of mode <==\n\n");
		fprintf(fout, "\n==> Configuration of mode <==\n\n");
		mode();
		fprintf(fout, "\n");
		printf("\n");
	}
	if (isCommand(arithTrig, "cleanhistory")) {
		fclean = NULL;
		while (fclean == NULL) {
			fclean = fopen(path, "w");
		}command = 1;
		fclose(fclean);
		printf("\n==> The history was cleaned sucessfully. <==\n\n");
		fprintf(fout, "\n==> The history was cleaned sucessfully. <==\n\n");
		arithTrig[0] = '\0';
		cleanhistory = 1;
	}
	if (isCommand(arithTrig, "colors")) {
		arithTrig[0] = '\0'; command = 1;
		printf("\n==> Configuration of background and text colors <==\n\n");
		fprintf(fout, "\n==> Configuration of background and text colors <==\n\n");
		colors();
	}
	if (isCommand(arithTrig, "dimensions")) {
		arithTrig[0] = '\0'; command = 1;
		printf("\n==> Dimensional configuration of the application window <==\n\n");
		fprintf(fout, "\n==> Dimensional configuration of the application window <==\n\n");
		dimensions();
	}
	if (isCommand(arithTrig, "window")) {
		arithTrig[0] = '\0'; command = 1;
		printf("\n==> Configuration of the position, width and height of the application window <==\n\n");
		fprintf(fout, "\n==> Configuration of the position, width and height of the application window <==\n\n");
		window();
	}
	if (isCommand(arithTrig, "solveequationssystem") && arithTrig[i + 20] == '(') {
		int correct = 1, vi = 0, vj = 0;

		count = 2;
		if (arithTrig[i + 25] == '(') {
			i = i + 26;
		}
		else {
			if (arithTrig[i + 20] == '(') {
				i = i + 21;
			}
		}
		char matrix[DIM] = "";
		int p = 0, countR = 0, countL = 0;
		for (p = i; arithTrig[p] != '\0'; p++) {
			if (arithTrig[p] == '(' || arithTrig[p] == '[' || arithTrig[p] == '{') {
				countL++;
			}
			if (arithTrig[p] == ')' || arithTrig[p] == ']' || arithTrig[p] == '}') {
				countR++;
			}
		}
		if (countR > 0) {
			countR--;
		}
		if (countL == countR) {
			p = 0;
			while (arithTrig[i] != ')'&&arithTrig[i] != '\0' || countR > 0) {
				if (arithTrig[i] == '(' || arithTrig[i] == '[' || arithTrig[i] == '{') {
					countL--;
				}
				if (arithTrig[i] == ')' || arithTrig[i] == ']' || arithTrig[i] == '}') {
					countR--;
				}
				matrix[p] = arithTrig[i];
				p++;
				i++;
			}
			matrix[p] = '\0';
			if (arithTrig[i] == '\0') {
				printf("\n==> The character ')' is missing. <==\n\n");
				fprintf(fout, "\n==> The character ')' is missing. <==\n\n");
			}
			else {
				int lines = 0, cols = 0;
				for (p = 0; matrix[p] != '\0'; p++) {
					if (matrix[p] == '\\') {
						cols++;
					}
					if (matrix[p] == ';') {
						lines++;
					}
				}
				lines++;
				if (lines*lines == cols) {
					matrixToValues(matrix, result1);
					rearrangeValues();
					solveSystem();
					getSolutions();

					int q = 0;
					double solutionR = 0, solutionI = 0;
					for (p = 0; p < count - 1; p++) {
						solutionR = 0;
						solutionI = 0;
						for (q = 0; q < count; q++) {
							multiplication(valuesS[p][q], valuesSI[p][q], values[q][count - 1], valuesI[q][count - 1]);

							solutionR = solutionR + resultR;
							solutionI = solutionI + resultI;

						}

						char Value[DIM] = "";
						sprintf(Value, "%G", solutionR);
						for (int v = 0; Value[v]; v++) {
							if (Value[v] == '-')
								Value[v] = '_';
						}
						solutionR = initialProcessor(Value, 0);
						sprintf(Value, "%G", valuesS[p][count - 1]);
						for (int v = 0; Value[v]; v++) {
							if (Value[v] == '-') {
								Value[v] = '_';
							}
							if (Value[v] == '+') {
								Value[v] = '0';
							}
						}
						valuesS[p][count - 1] = initialProcessor(Value, 0);


						sprintf(Value, "%G", solutionI);
						for (int v = 0; Value[v]; v++) {
							if (Value[v] == '-')
								Value[v] = '_';
						}
						solutionI = initialProcessor(Value, 0);
						sprintf(Value, "%G", valuesSI[p][count - 1]);
						for (int v = 0; Value[v]; v++) {
							if (Value[v] == '-') {
								Value[v] = '_';
							}
							if (Value[v] == '+') {
								Value[v] = '0';
							}
						}
						valuesSI[p][count - 1] = initialProcessor(Value, 0);
						if (solutionR != valuesS[p][count - 1] || solutionI != valuesSI[p][count - 1]) {
							printf("\n==> Unsolvable system. <==\n\n");
							fprintf(fout, "\n==> Unsolvable system. <==\n\n");
							correct = 0;
							break;
						}
						solutionR = 0;
						solutionI = 0;
					}
					if (correct == 1) {
						puts("");
						for (p = 0; p < count - 1; p++) {
							char Value[DIM] = "";
							sprintf(Value, "%f", values[p][count - 1]);
							for (int v = 0; Value[v]; v++) {
								if (Value[v] == '-')
									Value[v] = '_';
							}
							values[p][count - 1] = initialProcessor(Value, 0);
							if (values[p][count - 1] >= 0 && valuesI[p][count - 1] > 0) {
								printf("x%d=%G+%Gi\n", p + 1, values[p][count - 1], valuesI[p][count - 1]);
								fprintf(fout, "x%d=%G+%Gi\n", p + 1, values[p][count - 1], valuesI[p][count - 1]);
							}
							else {
								if (values[p][count - 1] >= 0 && valuesI[p][count - 1] < 0) {
									printf("x%d=%G%Gi\n", p + 1, values[p][count - 1], valuesI[p][count - 1]);
									fprintf(fout, "x%d=%G%Gi\n", p + 1, values[p][count - 1], valuesI[p][count - 1]);
								}
								else {
									if (values[p][count - 1] < 0 && valuesI[p][count - 1] < 0) {
										printf("x%d=%G%Gi\n", p + 1, values[p][count - 1], valuesI[p][count - 1]);
										fprintf(fout, "x%d=%G%Gi\n", p + 1, values[p][count - 1], valuesI[p][count - 1]);
									}
									else {
										if (values[p][count - 1] < 0 && valuesI[p][count - 1] > 0) {
											printf("x%d=%G+%Gi\n", p + 1, values[p][count - 1], valuesI[p][count - 1]);
											fprintf(fout, "x%d=%G+%Gi\n", p + 1, values[p][count - 1], valuesI[p][count - 1]);
										}
										else {
											if (values[p][count - 1] == 0 && valuesI[p][count - 1] != 0) {
												printf("x%d=%Gi\n", p + 1, valuesI[p][count - 1]);
												fprintf(fout, "x%d=%Gi\n", p + 1, valuesI[p][count - 1]);
											}
											else {
												if (valuesI[p][count - 1] == 0) {
													printf("x%d=%G\n", p + 1, values[p][count - 1]);
													fprintf(fout, "x%d=%G\n", p + 1, values[p][count - 1]);
												}
											}

										}
									}
								}
							}
						}
						puts("");
						fputs("", fout);
						for (vi = 0; vi < count; vi++) {
							for (vj = 0; vj < count; vj++) {
								valInd[vi][vj] = 0;
								values[vi][vj] = 0;
								valuesS[vi][vj] = 0;
								valuesSI[vi][vj] = 0;
								valuesF[vi][vj] = 0;
								valuesFI[vi][vj] = 0;
								valuesI[vi][vj] = 0;
							}
						}
						count = 0;
					}

				}
				else {
					printf("\nError in the introduction of the system of equations matrix.\n ==> Based in the number of rows is concluded that some elements are in fault or they are more than the needed.\n\n");
					fprintf(fout, "\nError in the introduction of the system of equations matrix.\n ==> Based in the number of rows is concluded that some elements are in fault or they are more than the needed.\n\n");
				}
			}
		}
		else {
			printf("\nError in parentheses. \n ==> The number of left and right parenthesis entered must be equal.\n ==> Enter \"[\" or \"{\" is the same as \"(\" and \"]\" or \"}\" is the same as \")\".\n ==> The expression that you entered has %d left parenthesis and %d right parenthesis.\n\n\n", countL, countR);
			fprintf(fout, "\nError in parentheses. \n ==> The number of left and right parenthesis entered must be equal.\n ==> Enter \"[\" or \"{\" is the same as \"(\" and \"]\" or \"}\" is the same as \")\".\n ==> The expression that you entered has %d left parenthesis and %d right parenthesis.\n\n\n", countL, countR);
		}
		arithTrig[0] = '\0'; command = 1;
	}
	if (isCommand(arithTrig, "eliminatevariables")) {
		FILE *open = NULL;
		int r = 0;
		char toPath[DIM] = "";
		sprintf(toPath, "%s\\variables.txt", atcPath);
		while (open == NULL&&r < 100) {
			open = fopen(toPath, "w");
			r++;
		}
		if (r < 100) {
			command = 1;
			fclose(open);
			open = NULL;
			r = 0;
			char toPath[DIM] = "";
			sprintf(toPath, "%s\\renamedVar.txt", atcPath);
			while (open == NULL&&r < 100) {
				open = fopen(toPath, "w");
				r++;
			}
			if (r < 100) {
				fclose(open);
				printf("\n==> The variables were eliminated sucessfully. <==\n\n");
				fprintf(fout, "\n==> The variables were eliminated sucessfully. <==\n\n");
				arithTrig[0] = '\0';
			}
		}
	}

	if (isCommand(arithTrig, "eliminatestrings")) {
		FILE *open = NULL;
		int r = 0;
		char toPath[DIM] = "";
		sprintf(toPath, "%s\\stringVariable.txt", atcPath);
		while (open == NULL&&r < 100) {
			open = fopen(toPath, "w");
			r++;
		}
		if (r < 100) {
			command = 1;
			fclose(open);
			fclose(open);
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"rmdir /Q /S Strings&mkdir Strings\""), NULL, SW_SHOW);
			printf("\n==> The strings were eliminated sucessfully. <==\n\n");
			fprintf(fout, "\n==> The strings were eliminated sucessfully. <==\n\n");
			arithTrig[0] = '\0';
		}
	}

	if (isCommand(arithTrig, "stopwatch") && arithTrig[i + 9] == '(') {
		printf("\nPress \"Enter\" button to mark time.\n");
		fprintf(fout, "\nPress \"Enter\" button to mark time.\n");
		int ct = 0, countT = 0;
		char countTimes[DIM] = "", pause[1000] = "";
		double stopTime = 0;
		if (arithTrig[i] == 'c') {
			i = i + 11;
		}
		else {
			i = i + 10;
		}
		ct = 0;
		while (arithTrig[i] != '\0'&&arithTrig[i] != ')') {
			countTimes[ct] = arithTrig[i];
			ct++; i++;
		}
		countTimes[ct] = '\0';
		countT = abs((int)initialProcessor(countTimes, result1));
		clock_t start, end;
		start = clock();
		ct = 0;
		while (ct < countT) {
			char pause[1000] = "";
			gets_s(pause);
			end = clock();
			stopTime = (double)(end - start) / CLOCKS_PER_SEC;
			int days = (int)qu(stopTime, 86400);
			int hours = (int)qu(re(stopTime, 86400), 3600);
			int minutes = (int)qu(re(re(stopTime, 86400), 3600), 60);
			int seconds = (int)re(re(re(stopTime, 86400), 3600), 60);
			int miliseconds = (int)(1000 * (stopTime - qu(stopTime, 1)));
			printf("t%d=", ct + 1);
			fprintf(fout, "t%d=", ct + 1);
			if (days != 0) {
				printf("%dd ", days);
				fprintf(fout, "%dd ", days);
			}
			if (hours != 0) {
				printf("%dh ", hours);
				fprintf(fout, "%dh ", hours);
			}
			if (minutes != 0) {
				printf("%dm ", minutes);
				fprintf(fout, "%dm ", minutes);
			}

			if (seconds != 0) {
				printf("%ds ", seconds);
				fprintf(fout, "%ds ", seconds);
			}
			if (miliseconds != 0) {
				printf("%dms ", miliseconds);
				fprintf(fout, "%dms ", miliseconds);
			}
			printf("\n");
			fprintf(fout, "\n");
			ct++;
		}
		puts("");
		fputs("\n", fout);
		command = 1;
		arithTrig[0] = '\0';
	}

	if (isCommand(arithTrig, "eliminateresults")) {
		r = 0; command = 1;
		while (r < rf) {
			ans[r] = 0;
			ansI[r] = 0;
			r++;
		}
		rf = 0;
		printf("\n==> The results were eliminated successfully. <==\n\n");
		fprintf(fout, "\n==> The results were eliminated successfully. <==\n\n");
		arithTrig[0] = '\0';
	}

	if (isCommand(arithTrig, "seestrings")) {
		FILE *open = NULL;
		int r = 0;
		char toOpen[DIM] = "";
		sprintf(toOpen, "%s\\stringVariable.txt", atcPath);
		while (open == NULL&&r < 100) {
			open = fopen(toOpen, "a+");
			r++;
		}
		if (r < 100) {
			command = 1;
			int w;
			char seeVar[DIM] = "";
			for (w = 0; (seeVar[w] = fgetc(open)) != EOF; w++);
			seeVar[w] = '\0';
			fclose(open);
			if (seeVar[0] != '\0') {
				printf("\nString name\n\n%s\n", seeVar);
				fprintf(fout, "\nString name\n\n%s\n", seeVar);
			}
			else {
				printf("\n==> No string created! <==\n\n");
				fprintf(fout, "\n==> No string created! <==\n\n");
			}
			arithTrig[0] = '\0';
		}
	}

	if (isCommand(arithTrig, "seevariables")) {
		FILE *open = NULL;
		int r = 0;
		char toOpen[DIM] = "";
		sprintf(toOpen, "%s\\variables.txt", atcPath);
		while (open == NULL&&r < 100) {
			open = fopen(toOpen, "a+");
			r++;
		}
		if (r < 100) {
			command = 1;
			int w;
			char seeVar[DIM] = "";
			for (w = 0; (seeVar[w] = fgetc(open)) != EOF; w++);
			seeVar[w] = '\0';
			fclose(open);
			if (seeVar[0] != '\0') {
				printf("\nVariable value\n\n%s\n", seeVar);
				fprintf(fout, "\nVariable value\n\n%s\n", seeVar);
			}
			else {
				printf("\n==> No variable created! <==\n\n");
				fprintf(fout, "\n==> No variable created! <==\n\n");
			}
			arithTrig[0] = '\0';
		}
	}
	if (isCommand(arithTrig, "eliminateabbreviations")) {
		FILE *open = NULL;	 command = 1;
		char toOpen[DIM] = "";
		sprintf(toOpen, "%s\\pathName.txt", atcPath);
		while (open == NULL) {
			open = fopen(toOpen, "w");
		}
		printf("\n==> The abbreviations were eliminated successfully. <==\n\n");
		fprintf(fout, "\n==> The abbreviations were eliminated successfully. <==\n\n");
		arithTrig[0] = '\0';
		fclose(open);
	}
	if (isCommand(arithTrig, "seeabbreviations")) {
		FILE *open = NULL;	   command = 1;
		char toOpen[DIM] = "";
		sprintf(toOpen, "%s\\pathName.txt", atcPath);
		while (open == NULL) {
			open = fopen(toOpen, "a+");
		}
		char dataPath[DIM] = "";
		int b = 0;
		for (b = 0; (dataPath[b] = fgetc(open)) != EOF; b++);
		dataPath[b] = '\0';
		arithTrig[0] = '\0'; command = 1;
		if (dataPath[0] != '\0') {
			printf("\nAbbreviations paths\n\n%s\n", dataPath);
			fprintf(fout, "\nAbbreviations paths\n\n%s\n", dataPath);
		}
		else {
			printf("\n==> No abbreviation created! <==\n\n");
			fprintf(fout, "\n==> No abbreviation created! <==\n\n");
		}
		fclose(open);
	}
	if (isCommand(arithTrig, "seeresults")) {
		arithTrig[0] = '\0'; command = 1;
		if (rf > 0) {
			printf("\nResult value\n\n");
			fprintf(fout, "\nResult value\n\n");
			r = 0;
			while (r < rf) {
				if (ans[r] > 0 && ansI[r] > 0) {
					printf("#%d=%G+%Gi\n", r, ans[r], ansI[r]);
					fprintf(fout, "#%d=%G+%Gi\n", r, ans[r], ansI[r]);
				}
				if (ans[r] > 0 && ansI[r] < 0) {
					printf("#%d=%G%Gi\n", r, ans[r], ansI[r]);
					fprintf(fout, "#%d=%G%Gi\n", r, ans[r], ansI[r]);
				}
				if (ans[r] < 0 && ansI[r] > 0) {
					printf("#%d=%G+%Gi\n", r, ans[r], ansI[r]);
					fprintf(fout, "#%d=%G+%Gi\n", r, ans[r], ansI[r]);
				}
				if (ans[r] < 0 && ansI[r] < 0) {
					printf("#%d=%G%Gi\n", r, ans[r], ansI[r]);
					fprintf(fout, "#%d=%G%Gi\n", r, ans[r], ansI[r]);
				}
				if (ans[r] == 0 && ansI[r] == 0) {
					printf("#%d=%G\n", r, ans[r]);
					fprintf(fout, "#%d=%G\n", r, ans[r]);
				}
				if (ans[r] == 0 && ansI[r] != 0) {
					printf("#%d=%Gi\n", r, ansI[r]);
					fprintf(fout, "#%d=%Gi\n", r, ansI[r]);
				}
				if (ans[r] != 0 && ansI[r] == 0) {
					printf("#%d=%G\n", r, ans[r]);
					fprintf(fout, "#%d=%G\n", r, ans[r]);
				}


				r++;
			}
			printf("\n");
			fprintf(fout, "\n");
		}
		else {
			printf("\n==> No calculated result! <==\n\n");
			fprintf(fout, "\n==> No calculated result! <==\n\n");
		}

	}
	if (isCommand(arithTrig, "renamedvariables")) {
		arithTrig[0] = '\0'; command = 1;
		FILE *open = NULL;
		int r = 0;
		char toOpen[DIM] = "";
		sprintf(toOpen, "%s\\renamedVar.txt", atcPath);
		while (open == NULL&&r < 100) {
			open = fopen(toOpen, "a+");
			r++;
		}
		if (r < 100) {
			int w;
			char seeVar[DIM] = "";
			for (w = 0; (seeVar[w] = fgetc(open)) != EOF; w++);
			seeVar[w] = '\0';
			fclose(open);
			if (seeVar[0] != '\0') {
				printf("\nVariable renaming\n\n%s\n", seeVar);
				fprintf(fout, "\nVariable renaming\n\n%s\n", seeVar);
			}
			else {
				printf("\n==> No variable created! <==\n\n");
				fprintf(fout, "\n==> No variable created! <==\n\n");
			}
		}
	}
	if (isCommand(arithTrig, "numericalsystems")) {
		char arithTrig[DIM] = ""; command = 1;
		arithTrig[0] = '\0';
		printf("\n==> Configuration of numerical systems response <==\n\n");
		fprintf(fout, "\n==> Configuration of numerical systems response <==\n\n");
		numSystemsController();
		fprintf(fout, "\n");
		printf("\n");
	}
	if (isCommand(arithTrig, "timer") && arithTrig[i + 5] == '(') {
		if (arithTrig[i + 12] == '(') {
			i = i + 13;
		}
		else {
			if (arithTrig[i + 5] == '(') {
				i = i + 6;

			}
		}
		int t = i, p = 0;
		for (t; arithTrig[t] != '\0'; t++) {
			if (arithTrig[t] == ')') {
				p++;
			}
		}
		if (p != 1) {
			printf("\n\n==> You need to terminate the expression with ')' character. <==\n\n");
		}
		else {
			char time[DIM] = "", expression[DIM] = "";
			t = 0;
			int b = i;
			while (arithTrig[b] != ')') {
				expression[t] = arithTrig[b];
				b++; t++;
			}
			expression[t] = '\0';
			b = 0;
			int sep = 0;
			for (t = 0; expression[t] != '\0'; t++) {
				if (expression[t] == ':' || expression[t] == '0' || expression[t] == '1' || expression[t] == '2' || expression[t] == '3' || expression[t] == '4' || expression[t] == '5' || expression[t] == '6' || expression[t] == '7' || expression[t] == '8' || expression[t] == '9') {
					b++;
					if (expression[t] == ':') {
						sep++;
					}
				}
			}
			if (b == strlen(expression) && sep == 2) {
				sprintf(time, "");
				t = 0;
				while (arithTrig[i] != ':'&&arithTrig[i] != ')') {
					time[t] = arithTrig[i];
					t++; i++;
				}
				i++;
				time[t] = '\0';
				int hours = (int)solveNow(time, 0, 0);
				sprintf(time, "");
				t = 0;
				while (arithTrig[i] != ':'&&arithTrig[i] != ')'&&arithTrig[i] != '\0'&&i < abs((int)strlen(arithTrig))) {
					time[t] = arithTrig[i];
					t++; i++;
				}
				time[t] = '\0';
				i++;
				int minutes = (int)solveNow(time, 0, 0);
				sprintf(time, "");
				t = 0;
				while (arithTrig[i] != ')'&&arithTrig[i] != '\0') {
					time[t] = arithTrig[i];
					t++; i++;
				}
				time[t] = '\0';
				int seconds = (int)solveNow(time, 0, 0);
				sprintf(time, "");
				clock_t start, end, syn1, syn2;
				int timePassed = 0, totalTime = hours * 3600 + minutes * 60 + seconds;
				int timeActual = 50, timepass = 0, time2syn = 0;
				start = clock();
				if (totalTime > 0) {
					while (timeActual > 0) {

						end = clock();
						timePassed = (end - start) / CLOCKS_PER_SEC;
						if (timePassed == 0) {
							syn1 = clock();
							while (timepass == timePassed) {
								end = clock();
								timePassed = (end - start) / CLOCKS_PER_SEC;
								Sleep(1);
							}
							syn2 = clock();
							time2syn = (int)(((double)(end - start) / CLOCKS_PER_SEC) * 1000);
						}
						else {
							Sleep(time2syn - 50);
							while (timepass == timePassed) {
								end = clock();
								timePassed = (end - start) / CLOCKS_PER_SEC;
								Sleep(3);
							}
						}
						timeActual = totalTime - timePassed;
						int thours = timeActual / 3600;
						int tminutes = (timeActual % 3600) / 60;
						int tseconds = (timeActual % 3600) % 60;
						timepass = timePassed;
						printTimer(thours, tminutes, tseconds);
					}
				}
				i = 0;
				Sleep(400);
				while (i < 25) {
					Beep(777, 400);
					Sleep(400);
					i++;
				}
			}
			else {
				printf("\n==> Your expression has syntax errors. <==\n\n");
			}
		}
		arithTrig[0] = '\0'; command = 1;
	}


	if (isCommand(arithTrig, "clock") && arithTrig[i + 5] == '(') {
		if (arithTrig[i + 7] == '(') {
			i = i + 8;
		}
		else {
			if (arithTrig[i + 5] == '(') {
				i = i + 6;

			}
		}
		int t = i, p = 0;
		for (t; arithTrig[t] != '\0'; t++) {
			if (arithTrig[t] == ')') {
				p++;
			}
		}
		if (p != 1) {
			printf("\n\n==> You need to terminate the expression with ')' character. <==\n\n");
		}
		else {
			char timE[DIM] = "", expression[DIM] = "";
			t = 0;
			int b = i;
			while (arithTrig[b] != ')') {
				expression[t] = arithTrig[b];
				b++; t++;
			}
			expression[t] = '\0';
			b = 0;
			int sep = 0;
			for (t = 0; expression[t] != '\0'; t++) {
				if (expression[t] == ':' || expression[t] == '0' || expression[t] == '1' || expression[t] == '2' || expression[t] == '3' || expression[t] == '4' || expression[t] == '5' || expression[t] == '6' || expression[t] == '7' || expression[t] == '8' || expression[t] == '9') {
					b++;
					if (expression[t] == ':') {
						sep++;
					}
				}
			}
			if (b == strlen(expression) && sep == 2) {
				t = 0;
				sprintf(timE, "");
				while (arithTrig[i] != ':'&&arithTrig[i] != ')') {
					timE[t] = arithTrig[i];
					t++; i++;
				}
				i++;
				timE[t] = '\0';
				int hours = (int)solveNow(timE, 0, 0);
				sprintf(timE, "");
				t = 0;
				while (arithTrig[i] != ':'&&arithTrig[i] != ')'&&arithTrig[i] != '\0') {
					timE[t] = arithTrig[i];
					t++; i++;
				}
				timE[t] = '\0';
				i++;
				int minutes = (int)solveNow(timE, 0, 0);
				sprintf(timE, "");
				t = 0;
				while (arithTrig[i] != ')'&&arithTrig[i] != '\0'&&i < abs((int)strlen(arithTrig))) {
					timE[t] = arithTrig[i];
					t++; i++;
				}
				timE[t] = '\0';
				int seconds = (int)solveNow(timE, 0, 0);
				sprintf(timE, "");
				clock_t start, end, syn1, syn2;
				int timePassed = 0, totalTime = hours * 3600 + minutes * 60 + seconds;
				int timeActual = 50, timepass = 0, time2syn = 0;
				int sec = 0;
				char seco[3] = "";
				char *tim;
				time_t hour1;
				time(&hour1);
				tim = ctime(&hour1);
				tim[24] = '\0';
				seco[0] = tim[17]; seco[1] = tim[18]; seco[2] = '\0';
				sec = atoi(seco);
				wait(sec);
				start = clock();
				if (totalTime > 0) {
					while (timeActual > 0) {

						end = clock();
						timePassed = (end - start) / CLOCKS_PER_SEC;
						if (timePassed == 0) {
							syn1 = clock();
							while (timepass == timePassed) {
								end = clock();
								timePassed = (end - start) / CLOCKS_PER_SEC;
								Sleep(1);
							}
							syn2 = clock();
							time2syn = (int)(((double)(end - start) / CLOCKS_PER_SEC) * 1000);
						}
						else {
							Sleep(time2syn - 50);
							while (timepass == timePassed) {
								end = clock();
								timePassed = (end - start) / CLOCKS_PER_SEC;
								Sleep(3);
							}
						}
						timeActual = totalTime - timePassed;
						int thours = timeActual / 3600;
						int tminutes = (timeActual % 3600) / 60;
						int tseconds = (timeActual % 3600) % 60;
						if (tseconds == -1) { tseconds = 0; }
						timepass = timePassed;
						time_t hour;
						time(&hour);
						char *tim;
						tim = ctime(&hour);
						tim[24] = '\0';
						char hou[3] = { tim[11], tim[12], '\0' };
						int Hours = atoi(hou);
						char min[3] = { tim[14], tim[15], '\0' };
						int Minutes = atoi(min);
						char sec[3] = { tim[17], tim[18], '\0' };
						int Seconds = atoi(sec);
						printTimer(Hours, Minutes, Seconds);
						printf("\n\n%02d:%02d:%02d\n\n", thours, tminutes, tseconds);
					}
				}

			}
			else {
				printf("\n==> Your expression has syntax errors. <==\n\n");
			}
		}
		arithTrig[0] = '\0'; command = 1;
	}

	if (isCommand(arithTrig, "siprefixes")) {
		arithTrig[0] = '\0'; command = 1;
		printf("\n==> Configuration of SI prefixes response <==\n\n");
		fprintf(fout, "\n==> Configuration of SI prefixes response <==\n\n");
		siPrefixController();
		fprintf(fout, "\n");
		printf("\n");
	}
	if (isCommand(arithTrig, "time")) {
		arithTrig[0] = '\0'; command = 1;
		Clock(1);
		puts("");
	}
	if (isCommand(arithTrig, "actualtimeresponse")) {
		arithTrig[0] = '\0'; command = 1;
		printf("\n==> Configuration of actual time response <==\n\n");
		fprintf(fout, "\n==> Configuration of actual time response <==\n\n");
		actualTimeController();
		fprintf(fout, "\n");
		printf("\n");
	}
	if (isCommand(arithTrig, "dayofweek") && arithTrig[i + 9] == '(') {
		arithTrig[0] = '\0'; command = 1;
		char Day[DIM] = "", Month[DIM] = "", Year[DIM] = "";
		double plusYears = 0;
		int r = 0;
		double day = 0, day1 = 0, day1S = 0, month = 0, month1 = 0, month1S = 0, year = 0, year1 = 0, year1S = 0, dayS = 0, monthS = 0, yearS = 0;
		if (arithTrig[i + 9] == '(' || arithTrig[i + 9] == '[' || arithTrig[i + 9] == '{') {
			i = i + 10;
		}
		if (arithTrig[i + 11] == '(' || arithTrig[i + 11] == '[' || arithTrig[i + 11] == '{') {
			i = i + 12;
		}
		int p = 0, countR = 0, countL = 0;
		for (p = i; arithTrig[p] != '\0'; p++) {
			if (arithTrig[p] == '(' || arithTrig[p] == '[' || arithTrig[p] == '{') {
				countL++;
			}
			if (arithTrig[p] == ')' || arithTrig[p] == ']' || arithTrig[p] == '}') {
				countR++;
			}
		}
		int limit = p - 3;
		countR--;
		while (arithTrig[i] != ')'&&arithTrig[i] != ']'&&arithTrig[i] != '}'&&arithTrig[i] != '\0' || countR > 0) {
			if (arithTrig[i] == 'd'&&day == 0) {
				r = 0;
				i++;
				while (arithTrig[i] != 'y'&&arithTrig[i] != 'm'&&arithTrig[i] != 'a'&&i < limit&&arithTrig[i] != '\0'&&arithTrig[i] != '-') {
					if (arithTrig[i] == '(' || arithTrig[i] == '[' || arithTrig[i] == '{') {
						countL--;
					}
					if (arithTrig[i] == ')' || arithTrig[i] == ']' || arithTrig[i] == '}') {
						countR--;
					}
					Day[r] = arithTrig[i];
					r++; i++;
				}
				if (arithTrig[i] == '-') {
					Day[r] = '+'; Day[r + 1] = '0'; Day[r + 2] = '\0';
					day = initialProcessor(Day, 0);
					dayS = day;
					r = 0;
					i++;
					char Day[DIM] = "";
					while (arithTrig[i] != 'y'&&arithTrig[i] != 'm'&&arithTrig[i] != 'a'&&i < limit&&arithTrig[i] != '\0') {
						Day[r] = arithTrig[i];
						r++; i++;
					}
					Day[r] = '+'; Day[r + 1] = '0'; Day[r + 2] = '\0';
					day1 = initialProcessor(Day, 0);
					day1S = day1;
				}
				else {
					Day[r] = '+'; Day[r + 1] = '0'; Day[r + 2] = '\0';
					day = initialProcessor(Day, 0);

				}
			}

			if (arithTrig[i] == 'm'&&month == 0) {
				r = 0;
				i++;
				while (arithTrig[i] != 'y'&&arithTrig[i] != 'd'&&arithTrig[i] != 'a'&&i < limit&&arithTrig[i] != '\0'&&arithTrig[i] != '-') {
					if (arithTrig[i] == '(' || arithTrig[i] == '[' || arithTrig[i] == '{') {
						countL--;
					}
					if (arithTrig[i] == ')' || arithTrig[i] == ']' || arithTrig[i] == '}') {
						countR--;
					}
					Month[r] = arithTrig[i];
					r++; i++;
				}
				if (arithTrig[i] == '-') {
					Month[r] = '+'; Month[r + 1] = '0'; Month[r + 2] = '\0';
					month = initialProcessor(Month, 0);
					monthS = month;
					r = 0;
					i++;
					char Month[DIM] = "";
					while (arithTrig[i] != 'y'&&arithTrig[i] != 'd'&&arithTrig[i] != 'a'&&i < limit&&arithTrig[i] != '\0') {
						Month[r] = arithTrig[i];
						r++; i++;
					}
					Month[r] = '+'; Month[r + 1] = '0'; Month[r + 2] = '\0';
					month1 = initialProcessor(Month, 0);
					month1S = month1;
				}
				else {
					Month[r] = '+'; Month[r + 1] = '0'; Month[r + 2] = '\0';
					month = initialProcessor(Month, 0);

				}
			}
			if ((arithTrig[i] == 'y' || arithTrig[i] == 'a') && year == 0) {
				r = 0;
				i++;
				while (arithTrig[i] != 'm'&&arithTrig[i] != 'd'&&i < limit&&arithTrig[i] != '\0'&&arithTrig[i] != '-') {
					if (arithTrig[i] == '(' || arithTrig[i] == '[' || arithTrig[i] == '{') {
						countL--;
					}
					if (arithTrig[i] == ')' || arithTrig[i] == ']' || arithTrig[i] == '}') {
						countR--;
					}
					Year[r] = arithTrig[i];
					r++; i++;
				}
				if (arithTrig[i] == '-') {
					Year[r] = '+'; Year[r + 1] = '0'; Year[r + 2] = '\0';
					year = initialProcessor(Year, 0);
					yearS = year;
					r = 0;
					i++;
					char Year[DIM] = "";
					while (arithTrig[i] != 'm'&&arithTrig[i] != 'd'&&i < limit&&arithTrig[i] != '\0') {
						Year[r] = arithTrig[i];
						r++; i++;
					}
					Year[r] = '+'; Year[r + 1] = '0'; Year[r + 2] = '\0';
					year1 = initialProcessor(Year, 0);
					year1S = year1;

				}
				else {
					Year[r] = '+'; Year[r + 1] = '0'; Year[r + 2] = '\0';
					year = initialProcessor(Year, 0);

				}
			}
			if (arithTrig[i] != 'd'&&arithTrig[i] != 'm'&&arithTrig[i] != 'y'&&arithTrig[i] != 'a') {
				i++;
			}
		}
		if (day1 == 0) {
			if (month > 12) {
				plusYears = qu(month, 12);
				year = year + plusYears;
				month = qu(re(month, 12), 1);
			}
			if (month == 0) {
				month = 12;
				year--;
			}


			while (day > 29 && (qu(re(year, 4), 1) == 0 && (qu(re(year, 100), 1) != 0) || qu(re(year, 400), 1) == 0) && month == 2 || day > 28 && month == 2 && (qu(re(year, 4), 1) != 0 || qu(re(year, 100), 1) == 0 && qu(re(year, 400), 1) != 0) || (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31 || day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {

				if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
					day = day - 31;

				}
				else {
					if (month == 2) {
						if ((qu(re(year, 4), 1) == 0 && qu(re(year, 100), 1) != 0) || qu(re(year, 400), 1) == 0) {
							day = day - 29;

						}
						else {
							day = day - 28;

						}

					}


					else {
						day = day - 30;

					}

				}

				month++;
				if (month > 12) {
					year++;
					month = qu(re(month, 12), 1);
				}



			}
		}
		else {


			while (day1 > 29 && (qu(re(year, 4), 1) == 0 && (qu(re(year, 100), 1) != 0) || qu(re(year, 400), 1) == 0) && month == 2 || day1 > 28 && month == 2 && (qu(re(year, 4), 1) != 0 || qu(re(year, 100), 1) == 0 && qu(re(year, 400), 1) != 0) || (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day1 > 31 || day1 > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {
				if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day1 > 31) {
					day1 = day1 - 31;


				}
				else {
					if (month == 2) {
						if (qu(re(year, 4), 1) == 0) {
							if (qu(re(year, 400), 1) == 0 && day1 > 29) {
								day1 = day1 - 29;
							}
							else {
								if (qu(re(year, 100), 1) == 0 && day1 > 28) {
									day1 = day1 - 28;
								}
								else {
									if (day1 > 29) {
										day1 = day1 - 29;
									}
								}
							}
						}
						else {
							if (day1 > 28) {
								day1 = day1 - 28;
							}
						}

					}


					else {
						if (day1 > 30) {
							day1 = day1 - 30;
						}
					}

				}
				month--;
				if (month == 0) {
					year--;
					month = 12;
				}

			}


			day = day - day1;
			if (day < 0) {
				month--;
				int sumDay = 0;


				if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day1 > 31) {
					sumDay = 31;

				}
				else {
					if (month == 2) {
						if (qu(re(year, 4), 1) == 0) {
							if (qu(re(year, 400), 1) == 0) {
								sumDay = 29;
							}
							else {
								if (qu(re(year, 100), 1) == 0) {
									sumDay = 28;
								}
								else {
									sumDay = 29;
								}
							}
						}
						else {
							sumDay = 28;
						}

					}


					else {
						sumDay = 30;
					}

				}


				day = sumDay + day;
			}

			year = year - year1;

			month = month - month1;

			if (month > 12) {
				plusYears = qu(month, 12);
				year = year + plusYears;
				month = qu(re(month, 12), 1);
				if (month == 0) {
					month = 12;
				}
			}
			else {
				if (month <= 0) {
					plusYears = qu((month - 12), 12);
					year = year + plusYears;
					month = 12 - abs(qu(re(month, 12), 1));
					if (month == 0) {
						month = 12;
						year++;
					}
				}
			}

			day = day - datePreciser(day + day1S, month + month1S, year + year1S, dayS, monthS, yearS);


		}
		char tim[DIM] = "";
		sprintf(tim, "%G", day);
		int daY = (int)initialProcessor(tim, 0);
		sprintf(tim, "%G", month);
		int montH = (int)initialProcessor(tim, 0);
		sprintf(tim, "%G", year);
		int yeaR = (int)initialProcessor(tim, 0);
		if (daY < 1 || daY>31) {
			printf("\nError entering the day.\n ==> In a month, the days only vary between 1 and 31.\n\n");
			fprintf(fout, "\nError entering the day.\n ==> In a month, the days only vary between 1 and 31.\n\n");
		}
		else {
			if (montH < 1 || montH>12) {
				printf("\nError entering the month.\n ==> In a year, the months only vary between 1 and 12.\n\n");
				fprintf(fout, "\nError entering the month.\n == > In a year, the months only vary between 1 and 12.\n\n");
			}
			else {
				if (yeaR < 1760) {
					printf("\nError entering the year.\n ==> The minimal year to evaluate is 1760.\n\n");
					fprintf(fout, "\nError entering the year.\n ==> The minimal year to evaluate is 1760.\n\n");
				}
				else {
					if ((montH == 2 || montH == 4 || montH == 6 || montH == 9 || montH == 11) && daY == 31) {
						printf("\nError entering the month.\n ==> The entered month doesn't have the duration of 31 days.\n\n");
						fprintf(fout, "\nError entering the month.\n == > The entered month doesn't have the duration of 31 days.\n\n");
					}
					else {
						if (montH == 2 && daY > 29) {
							printf("\nError entering the day.\n ==> The month of February has a maximal duration of 29 days.\n\n");
							fprintf(fout, "\nError entering the day.\n ==> The month of February has a maximal duration of 29 days.\n\n");
						}
						else {
							if ((montH == 2 && daY == 29) && (yeaR % 4 != 0 && yeaR % 400 != 0)) {
								printf("\nError entering the day.\n ==> The month of February in %d has a maximal duration of 28 days.\n\n", yeaR);
								fprintf(fout, "\nError entering the day.\n ==> The month of February in %d has a maximal duration of 28 days.\n\n", yeaR);
							}
							else {
								printf("y%dm%dd%d=", yeaR, montH, daY);
								int h = 0;
								h = ((int)(daY + floor((((montH + 1) * 26) / 10)*1.000) + yeaR + floor((yeaR / 4)*1.0000) + 6 * floor((yeaR / 100)*1.0000) + floor((yeaR / 400)*1.0000)) % 7);
								if (montH < 3) {
									if (montH == 1) {
										montH = 13;
									}
									if (montH == 2) {
										montH = 14;
									}
									yeaR--;
									h = ((int)(daY + floor((((montH + 1) * 26) / 10)*1.000) + (yeaR)+floor(((yeaR) / 4)*1.0000) + 6 * floor(((yeaR) / 100)*1.0000) + floor(((yeaR) / 400)*1.0000)) % 7);

								}

								if (h == 1) {
									printf("Sunday\n\n");
									fprintf(fout, "Sunday\n\n");
								}
								if (h == 2) {
									printf("Monday\n\n");
									fprintf(fout, "Monday\n\n");
								}
								if (h == 3) {
									printf("Tuesday\n\n");
									fprintf(fout, "Tuesday\n\n");
								}
								if (h == 4) {
									printf("Wednesday\n\n");
									fprintf(fout, "Wednesday\n\n");
								}
								if (h == 5) {
									printf("Thursday\n\n");
									fprintf(fout, "Thursday\n\n");
								}
								if (h == 6) {
									printf("Friday\n\n");
									fprintf(fout, "Friday\n\n");
								}
								if (h == 0) {
									printf("Saturday\n\n");
									fprintf(fout, "Saturday\n\n");
								}

							}
						}
					}
				}
			}
		}
	}
	if (isCommand(arithTrig, "predefinetxt")) {
		arithTrig[0] = '\0'; command = 1;
		printf("\n==> Drag to here the file to predefine and press the button \"Enter\" <==\n");
		fprintf(fout, "\n==> Drag to here the file to predefine and press the button \"Enter\" <==\n");
		char predTxt[DIM] = "";
		int y = 0;
		gets_s(predTxt);
		if (predTxt[y] == '"') {
			while (predTxt[y + 1] != '"'&&predTxt[y + 1] != '\0') {
				predTxt[y] = predTxt[y + 1];
				y++;
			}
			predTxt[y] = '\0';
		}
		FILE *pred = NULL;
		char toOpen[DIM] = "";
		sprintf(toOpen, "%s\\predefinedTxt.txt", atcPath);
		while (pred == NULL) {
			pred = fopen(toOpen, "w");
		}
		fprintf(pred, "%s", predTxt);
		fclose(pred);
		printf("\n");
		fprintf(fout, "\n");
	}

	if (isCommand(arithTrig, "solvetxt") && (arithTrig[i + 10] == '\0' || arithTrig[i + 8] == '(')) {
		arithTrig[0] = '\0'; command = 1;
		FILE *readPred = NULL;
		char readPath[DIM] = "";
		if (arithTrig[i + 8] != '('&&arithTrig[i + 11] != '(') {
			char toOpen[DIM] = "";
			sprintf(toOpen, "%s\\predefinedTxt.txt", atcPath);
			readPred = fopen(toOpen, "r");
			if (readPred == NULL) {
				printf("\n==> The file was not yet predefined! <==\n\n");
				fprintf(fout, "\n==> The file was not yet predefined! <==\n\n");
			}
			else {
				fgets(readPath, DIM, readPred);
				fclose(readPred);
				processTxt(readPath, rf);
				FILE *open = NULL;
				open = fopen(expressionF, "r");
				char openFile[DIM] = "";
				if (open != NULL) {
					fclose(open);
					printf("\n==> Close the file with the answers to continue. <==\n\n");
					fprintf(fout, "\n==> Close the file with the answers to continue. <==\n\n");
				}
				openTxt();
			}
		}
		else {
			char paName[DIM] = "";
			int x = 0, y = 0;
			if (arithTrig[i + 8] == '(' || arithTrig[i + 11] == '(') {
				if (arithTrig[i + 8] == '(') {
					y = i + 9;
				}
				if (arithTrig[i + 11] == '(') {
					y = i + 12;
				}
				for (x = 0; arithTrig[y] != ')'&&arithTrig[y] != '\0'&&arithTrig[y] != '+'; x++) {
					paName[x] = arithTrig[y];
					y++;
				}
				paName[x] = '\0';
				pathNameToPath(paName);
				if (strlen(pathNAme) != 0) {
					processTxt(pathNAme, rf);
					FILE *open = NULL;
					open = fopen(expressionF, "r");
					char openFile[DIM] = "";
					if (open != NULL) {
						fclose(open);
						printf("\n==> Close the file with the answers to continue. <==\n\n");
						fprintf(fout, "\n==> Close the file with the answers to continue. <==\n\n");
					}
					openTxt();
				}

			}
		}
	}
	if (isCommand(arithTrig, "calendar") && (arithTrig[i + 8] == '(' || arithTrig[i + 8] == '+')) {
		char ye[100], calendar[DIM];
		int k = 0;
		int p = 0, countR = 0, countL = 0;
		for (p = 0; arithTrig[p] != '\0'; p++) {
			if (arithTrig[p] == '(' || arithTrig[p] == '[' || arithTrig[p] == '{') {
				countL++;
			}
			if (arithTrig[p] == ')' || arithTrig[p] == ']' || arithTrig[p] == '}') {
				countR++;
			}
		}
		if (countR == countL) {
			if (arithTrig[i + 8] == '(' || arithTrig[i + 8] == '[' || arithTrig[i + 8] == '{') {
				i = i + 9;
				for (p = i; arithTrig[p] != '\0'; p++);
				int limit = p - 3;
				if (arithTrig[limit] != ')') {
					limit++;
				}
				k = 0;
				countR = 0; countL = 0;
				while (i < limit) {
					if (arithTrig[i] == '(' || arithTrig[i] == '[' || arithTrig[i] == '{') {
						countL++;
					}
					if (arithTrig[i] == ')' || arithTrig[i] == ']' || arithTrig[i] == '}') {
						countR++;
					}
					ye[k] = arithTrig[i];
					k++; i++;
				}
				ye[k] = '\0';
				if (countR == countL) {
					year = (int)initialProcessor(ye, 0);
				}

			}
			else {
				if (arithTrig[i + 10] == '(' || arithTrig[i + 10] == '[' || arithTrig[i + 10] == '{') {
					i = i + 11;
					for (p = i; arithTrig[p] != '\0'; p++);

					int limit = p - 3;
					if (arithTrig[limit] != ')') {
						limit++;
					}
					k = 0;
					countR = 0; countL = 0;
					while (i < limit) {
						if (arithTrig[i] == '(' || arithTrig[i] == '[' || arithTrig[i] == '{') {
							countL++;
						}
						if (arithTrig[i] == ')' || arithTrig[i] == ']' || arithTrig[i] == '}') {
							countR++;
						}
						ye[k] = arithTrig[i];
						k++; i++;
					}
					ye[k] = '\0';
					if (countR == countL) {
						year = (int)initialProcessor(ye, 0);
					}


				}
				else {
					time_t hour;
					time(&hour);
					char *tim;
					tim = ctime(&hour);
					tim[24] = '\0';
					char yea[7] = { tim[20], tim[21], tim[22], tim[23], '.', '0', '\0' };
					year = (int)convertToNumber(yea);
				}
			}
			arithTrig[0] = '\0'; command = 1;

			if (year > 1759) {
				char toOpen[DIM] = "";
				sprintf(toOpen, "%s\\calendar.txt", atcPath);
				Calendar(toOpen, year);
				for (s = 0; calendarStr[s] != '\0'; s++) {
					calendar[s] = calendarStr[s];
				}
				calendar[s] = '\0';
				char cald[DIM] = "";
				int yu = 0, liN = 0, liR = 0;
				for (s = 0; s < abs((int)strlen(calendar)); s++) {
					liR = 0;
					liN = 0;
					while (calendar[s] != '\n'&&s < abs((int)strlen(calendar))) {
						cald[yu] = calendar[s];
						yu++; s++;
						liN++;
					}
					liR = 124 - liN;
					while (liR > 0) {
						cald[yu] = ' ';
						yu++;
						liR--;
					}
					cald[yu] = '\n';
					yu++;
				}
				cald[yu] = '\0';
				int ca = 0;
				for (yu = 0; cald[yu] != '\0'; yu++) {
					calendar[yu] = cald[yu];
					if (calendar[yu] == '\n') {
						ca++;
					}
					if (calendar[yu] == ' ' && ca % 2 == 0 && ca >= 10) {
						calendar[yu] = 176;
					}
					if (calendar[yu] == ' ' && (ca % 2 == 1 || ca < 10)) {
						calendar[yu] = 177;
					}
					if (calendar[yu] == '|') {
						calendar[yu] = 179;
					}
				}
				calendar[yu] = '\0';

				ca = 0;
				for (s = 0; calendar[s] != '\0'; s++) {
					if (calendar[s] == '\n') {
						ca++;
						if (ca > 4) {
							calendar[s + 28] = 179;
							calendar[s + 34] = 179;
							calendar[s + 49] = 179;
							calendar[s + 55] = 179;
							calendar[s + 70] = 179;
							calendar[s + 76] = 179;
							calendar[s + 91] = 179;
							calendar[s + 97] = 179;
							calendar[s + 112] = 179;
							calendar[s + 118] = 179;
						}
					}

				}

				for (s = 0; calendar[s] != '\0'; s++) {
					if (calendar[s] == 's'&&calendar[s + 3] == 'd'&&calendar[s + 4] == 'o') {
						calendar[s + 1] = 'a';
					}
					if (calendar[s] == 'm'&&calendar[s + 1] == 'a'&&calendar[s + 2] == 'r'&&calendar[s + 4] == 'o') {
						calendar[s + 3] = 'c';
					}
				}
				calendar[s] = '\0';
				printf("\n");
				printf("%s\n\n", calendar);

				for (s = 0; calendarStr[s] != '\0'; s++) {
					calendar[s] = calendarStr[s];
				}
				calendar[s] = '\0';

				fprintf(fout, "\n");
				fprintf(fout, "%s\n\n", calendar);
			}
			else {
				printf("\n");
				printf("Please enter years after 1759\n\n");
				fprintf(fout, "\n");
				fprintf(fout, "Please enter years after 1759\n\n");
			}
		}
	}
	fclose(fout);
	return command;
}

boolean isCommand(char forTesting[DIM], char command[DIM]) {
	char toTest[DIM] = "";
	int i = 0;
	while (verifyLetter(forTesting[i]) == 1) {
		toTest[i] = forTesting[i];
		i++;
	}
	toTest[i] = '\0';
	if (isEqual(toTest, command)) {
		if (forTesting[strlen(toTest)] == '(' || (forTesting[strlen(toTest)] == '+'&&forTesting[strlen(toTest) + 1] == '0'&&forTesting[strlen(toTest) + 2] == '\0')) {
			if (forTesting[strlen(toTest)] == '(') {
				i = strlen(toTest) + 1;
				int rP = 0, lP = 0;
				while (forTesting[i] != '\0'&&i < abs((int)strlen(forTesting))) {
					if (forTesting[i] == '(') {
						lP++;
					}
					if (forTesting[i] == ')') {
						rP++;
					}
					i++;
				}
				if (rP == lP + 1) {
					return true;
				}
				else {
					return false;
				}
			}
			return true;
		}
		return false;
	}
	else {
		return false;
	}
}