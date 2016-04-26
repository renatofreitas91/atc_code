#include "stdafx.h"

double main_core(char arithTrig[DIM], char fTrig[DIM], FILE *fout, char path[DIM], double result1, double result2, int isFromMain){
	int txt = 0, command = 0, var = 0, str = 0, s = 0, i = 0, space = 0, v = 0, j = 0, valGet = 0, h = 0, run_del_space = 1, strIndex = 0;
	char variable[DIM] = "", getVarName[DIM] = "", getVar[DIM] = "", savefTrig[DIM] = "";
	cleanhistory = 0;
	txt = 0;
	valid = 1;
	continu = 1;
	validVar = 1;
	str = 0;
	sprintf(savefTrig, "%s", fTrig);
	if (arithTrig[0] == 'g'&&arithTrig[1] == 'e'&&arithTrig[2] == 't'&&arithTrig[3] == '('){
		i = 4;
		for (i = 4; arithTrig[i] != '\0'; i++){
			if (arithTrig[i] == ')'){
				valGet = 1;
				break;
			}
		}
		if (valGet == 1){
			h = 0;
			i = 4;
			while (arithTrig[i] != ')'&&arithTrig[i] != '\0'){
				getVarName[h] = arithTrig[i];
				h++; i++;
			}
			getVarName[h] = '\0';
			strIndex = 0;
			for (int ks = 0; getVarName[ks] != '\0'; ks++){
				if (verifyNumber(getVarName[ks]) == 1 || verifyLetter(getVarName[ks]) == 1){
					strIndex++;
				}
			}
			if (strIndex == strlen(getVarName)){
				gets(getVar);
			}
			else{
				puts("\nTo create string variables only letters from latin alphabet and digits 0-9 can be used.\nTo create numerical variables only letters from latin alphabet can be used.");
				command = 1;
				arithTrig[0] = '\0';
			}
			sprintf(arithTrig, "%s=%s", getVarName, getVar);
			command = 0;
		}
		else{
			puts("\nError in syntax in get function.\n");
			command = 1;
			arithTrig[0] = '\0';
		}
	}
	variable[0] = '\0';
	for (i = 0; arithTrig[i] != '\0'; i++){
		if (arithTrig[i] == ':'&&arithTrig[i + 1] == '\\'){
			txt = 1;
		}
		if (arithTrig[i] == '='){
			var = 1;
			if (valGet == 1){
				puts(" ");
			}
		}
		if (arithTrig[i] == '\"'&&arithTrig[strlen(arithTrig) - 1] == '\"'){
			str = 1;
		}
		else{
			if ((arithTrig[i - 6] == 'p'&&arithTrig[i - 5] == 'r'&&arithTrig[i - 4] == 'i'&&arithTrig[i - 3] == 'n'&&arithTrig[i - 2] == 't'&&arithTrig[i - 1] == '(') == true){
				run_del_space = 0;
			}
		}
	}
	if (txt == 1){
		int p = 0;
		char pathName[DIM] = "";
		if (var == 1){
			var = 0;
			while (arithTrig[p] != '='){
				pathName[p] = arithTrig[p];
				p++;
			}
			pathName[p] = '\0';
			for (p = 0; pathName[p] != ' '&&pathName[p] != ')'&&pathName[p] != '\0'; p++);
			if (p == strlen(pathName)){
				int lenPath = strlen(pathName) + 1;
				for (p = lenPath; arithTrig[p] != '\0'; p++){
					arithTrig[p - lenPath] = arithTrig[p];
				}
				arithTrig[p - lenPath] = '\0';
				pathNameController(pathName, arithTrig);
			}
			else{
				printf("\n==> Invalid abbreviation! <==\n\n");
				fprintf(fout, "\n==> Invalid abbreviation! <==\n\n");
				arithTrig[0] = '\0';
			}
		}

		if (arithTrig[0] != '\0'){
			command = 1;
			int toWrite = processTxt(arithTrig, rf);
			if (toWrite == 1){
				printf("\n==> Close the file with the answers to continue. <==\n\n");
				fprintf(fout, "\n==> Close the file with the answers to continue. <==\n\n");
				openTxt();
			}
			arithTrig[0] = '\0';
		}
	}

	if (str == 1){
		str = 0;
		int p = 0;
		char variableString[DIM] = "";
		p = 0;
		if (var == 1){
			var = 0;
			while (arithTrig[p] != '='){
				variableString[p] = arithTrig[p];
				p++;
			}
			variableString[p] = '\0';
			for (p = 0; variableString[p] != ' '&&variableString[p] != ')'&&variableString[p] != '\0'&&p < strlen(variableString); p++);
			if (strIndex == strlen(variableString)){
				int lenStr = strlen(variableString) + 1;
				p++;
				if (arithTrig[lenStr] == '\"'){
					arithTrig[p - lenStr] = arithTrig[p];
					lenStr++;
					p++;
				}
				for (p = lenStr; arithTrig[p] != '\0'&&arithTrig[p] != '\"'&&p < strlen(arithTrig); p++){
					arithTrig[p - lenStr] = arithTrig[p];
				}
				arithTrig[p - lenStr] = '\0';
				stringVariableController(variableString, arithTrig);
				if (valGet == 0){
					puts(" ");
				}
			}
			else{
				printf("\n==> Invalid string name! Only letters from latin alphabet and digits 0-9 can be used. <==\n\n");
				fprintf(fout, "\n==> Invalid string name! Only letters from latin alphabet and digits 0-9 can be used. <==\n\n");
				arithTrig[0] = '\0';
			}
		}
		if (arithTrig[0] != '\0'){
			command = 1;
			arithTrig[0] = '\0';
		}
	}
	else{

		if (strlen(arithTrig) > 0){
			arithTrig[i] = '+'; arithTrig[i + 1] = '0'; arithTrig[i + 2] = '\0';
		}

		int verify = 0;
		for (s = 0; arithTrig[s] != '\0'; s++){
			if (arithTrig[s] == 'B' || arithTrig[s] == 'O' || arithTrig[s] == 'H' || arithTrig[s] == '_' || arithTrig[s] == '{' || arithTrig[s] == '[' || arithTrig[s] == '(' || arithTrig[s] == '+' || arithTrig[s] == '-' || arithTrig[s] == '*' || arithTrig[s] == '/' || arithTrig[s] == '^' || arithTrig[s] == '0' || arithTrig[s] == '1' || arithTrig[s] == '2' || arithTrig[s] == '3' || arithTrig[s] == '4' || arithTrig[s] == '5' || arithTrig[s] == '6' || arithTrig[s] == '7' || arithTrig[s] == '8' || arithTrig[s] == '9' || (arithTrig[s] == 'r'&&arithTrig[s + 1] == 'e'&&arithTrig[s + 2] == 's') || (arithTrig[s] == 'a'&&arithTrig[s + 1] == 'n'&&arithTrig[s + 2] == 's') || (arithTrig[s] == 'e' && ((arithTrig[s + 1] == 'e' || arithTrig[s + 1] == '\0'&&s == 0 || arithTrig[s + 1] == ')' || arithTrig[s + 1] == 'p' || arithTrig[s - 1] == '_') || (arithTrig[s - 1] == 'e' || arithTrig[s - 1] == '(' || arithTrig[s - 1] == 'i'&&arithTrig[s - 2] != 't'))) || (arithTrig[s] == 'p'&&arithTrig[s + 1] == 'i' && ((arithTrig[s + 2] == 'e' || arithTrig[s + 2] == '\0'&&s == 0 || arithTrig[s + 2] == ')' || arithTrig[s + 2] == 'p' || arithTrig[s - 1] == '_') || (arithTrig[s - 1] == 'e' || arithTrig[s - 1] == '(' || arithTrig[s - 1] == 'i')))){
				verify = 1;
			}
		}
		if (var == 1){
			for (i = 0; arithTrig[i] != '='; i++){
				if (arithTrig[i] == ' '){
					v = 1;
				}
			}
			i++;
			if (arithTrig[i] == '+'&&arithTrig[i + 1] == '0'&&arithTrig[i + 2] == '\0'){
				verify = 0;
				var = 0;
			}
		}
		boolean isFunction = atcFunctions(arithTrig);
		if (isFunction == false){
			for (i = 0; arithTrig[i] != '\0'; i++){
				if (arithTrig[i] == ' '){
					space = 1;
					break;
				}
				else{
					space = 0;
				}
			}
			if (space == 1 && run_del_space == 1){
				while (space == 1){
					for (i = 0; arithTrig[i] != '\0'; i++){
						if (arithTrig[i] == ' '){
							j = i;
							while (arithTrig[i] != '\0'){
								arithTrig[i] = arithTrig[i + 1];
								i++;
							}
							i = j;
						}
					}
					for (i = 0; arithTrig[i] != '\0'; i++){
						if (arithTrig[i] == ' '){
							space = 1;
							break;
						}
						else{
							space = 0;
						}
					}
				}
			}
			fprintf(fout, ">%s\n", savefTrig);
			command = commands(arithTrig, path, result1, result2);
			fclose(fout);
			fout = NULL;
			while (fout == NULL){
				fout = fopen(path, "a+");
			}
			if (command == 0){
				main_sub_core(arithTrig, fout, verify, path, txt, variable, v, j, result1, result2, isFromMain, var, valGet, command);
			}
		}
	}

	return result1;
}

double main_sub_core(char arithTrig[DIM], FILE *fout, int verify, char path[DIM], int txt, char variable[DIM], int v, int j, double result1, double result2, int isFromMain, int var, int valGet, int command){
	FILE *open = NULL;
	int  g = 0, Dimensions = 2, Window = 3, r = 0, i = 0, s = 0;
	char exit[DIM] = "", res, varLetters[DIM] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
	res = arithTrig[0];
	if (res == '+' || res == '-' || res == '/' || res == '*' || res == 'x' || res == '^'){
		for (i = 0; arithTrig[i] != '\0'; i++){
			arithTrig[i] = arithTrig[i + 1];
		}
	}
	if (var == 1){
		for (i = 0; arithTrig[i] != '='&&arithTrig[i] != '\0'; i++){
			variable[i] = arithTrig[i];
		}
		variable[i] = '\0';
		g = i + 1;
		for (i = 0; arithTrig[i] != '\0'; i++){
			arithTrig[i] = arithTrig[i + g];
		}
		arithTrig[i] = '\0';
		i = 0;
		int hk = variableValidator(variable);
		if (hk == 1 || v == 1){
			processVariable(revariable);
			if (validVar == 0 && valid == 0){
				//printf("\n==> Your variable was renamed to \"%s\", but you can continue using it with the same name that you chose. <==\n\n", revariable);
				fprintf(fout, "\n==> Your variable was renamed to \"%s\", but you can continue using it with the same name that you chose. <==\n\n", revariable);

			}
		}
		if (hk == 2){
			if (isFromMain == 1){
				printf("\n==> Your variable was renamed to \"%s\". <==\n\n", revariable);
			}
			fprintf(fout, "\n==> Your variable was renamed to \"%s\". <==\n\n", revariable);
		}
		if (hk == 0){
			if (isFromMain == 1){
				printf("\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
			}
			fprintf(fout, "\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
			var = 0;
		}
	}
	char dP[DIM] = "", bP[DIM] = "", oP[DIM] = "", hP[DIM] = "";
	int dp = -1, bp = -1, op = -1, hp = -1;
	while (arithTrig[0] == 'd' &&arithTrig[1] == 'p' || arithTrig[0] == 'b' &&arithTrig[1] == 'p' || arithTrig[0] == 'o' &&arithTrig[1] == 'p' || arithTrig[0] == 'h' &&arithTrig[1] == 'p')  {
		if (arithTrig[0] == 'd' &&arithTrig[1] == 'p'){
			i = 2;
			while (arithTrig[i] != 'd'&&arithTrig[i] != '\0'){
				dP[i - 2] = arithTrig[i];
				i++;
			}
			dP[i - 2] = '\0';
			dp = initialProcessor(dP, result1);
			i = i + 2;
			int b = 0;
			for (b = 0; arithTrig[b] != '\0'; b++){
				arithTrig[b] = arithTrig[b + i];
			}
		}
		if (arithTrig[0] == 'b' &&arithTrig[1] == 'p'){
			i = 2;
			while (arithTrig[i] != 'b'&&arithTrig[i] != '\0'){
				bP[i - 2] = arithTrig[i];
				i++;
			}
			bP[i - 2] = '\0';
			bp = initialProcessor(bP, result1);
			i = i + 2;
			int b = 0;
			for (b = 0; arithTrig[b] != '\0'; b++){
				arithTrig[b] = arithTrig[b + i];
			}
		}
		if (arithTrig[0] == 'o' &&arithTrig[1] == 'p'){
			i = 2;
			while (arithTrig[i] != 'o'&&arithTrig[i] != '\0'){
				oP[i - 2] = arithTrig[i];
				i++;
			}
			oP[i - 2] = '\0';
			op = initialProcessor(oP, result1);
			i = i + 2;
			int b = 0;
			for (b = 0; arithTrig[b] != '\0'; b++){
				arithTrig[b] = arithTrig[b + i];
			}
		}
		if (arithTrig[0] == 'h' &&arithTrig[1] == 'p'){
			i = 2;
			while (arithTrig[i] != 'h'&&arithTrig[i] != '\0'){
				hP[i - 2] = arithTrig[i];
				i++;
			}
			hP[i - 2] = '\0';
			hp = initialProcessor(hP, result1);
			i = i + 2;
			int b = 0;
			for (b = 0; arithTrig[b] != '\0'; b++){
				arithTrig[b] = arithTrig[b + i];
			}
		}
	}
	for (i = 0; arithTrig[i] != '\0'; i++){
		if (arithTrig[i] == 'a'&&arithTrig[i + 1] == 'n'&&arithTrig[i + 2] == 's'){
			arithTrig[i] = 'r'; arithTrig[i + 1] = 'e'; arithTrig[i + 2] = 's';
			i = i + 3;
		}
	}
	s = 0;
	if (verify == 1){
		for (i = 0; arithTrig[i] != '\0'; i++){
			if (arithTrig[i] == 'x'){
				arithTrig[i] = '*';
			}

		}
		arithTrig[i] = '\0';
		synTest = 0;
		manageExpression(arithTrig, result1, result2, verify);
		for (i = 0; expressionF[i] != '\0'; i++){
			arithTrig[i] = expressionF[i];
		}
		arithTrig[i] = '\0';
		synTest = 0;
		verify = dataVerifier(arithTrig, result1, result2, isFromMain, verify);
	}

	int kg = 0, kc = 0;
	for (i = 0; arithTrig[i] != '\0'; i++){
		if (arithTrig[i] == '(' || arithTrig[i] == '[' || arithTrig[i] == '{'){
			kg++;
		}
		if (arithTrig[i] == ')' || arithTrig[i] == ']' || arithTrig[i] == '}'){
			kc++;
		}
	}
	if (kg != kc){
		if (isFromMain == 1){
			printf("\nError in parentheses. \n ==> The number of left and right parenthesis entered must be equal.\n ==> Enter \"[\" or \"{\" is the same as \"(\" and \"]\" or \"}\" is the same as \")\".\n ==> The expression that you entered has %d left parenthesis and %d right parenthesis.\n\n\n", kg, kc);
		}
		fprintf(fout, "\nError in parentheses. \n ==> The number of left and right parenthesis entered must be equal.\n ==> Enter \"[\" or \"{\" is the same as \"(\" and \"]\" or \"}\" is the same as \")\".\n ==> The expression that you entered has %d left parenthesis and %d right parenthesis.\n\n\n", kg, kc);
		arithTrig[0] = '\0';
	}


	fclose(fout);
	if (arithTrig[0] != '\0'&&isFromMain == 1){
		Clock(0);
	}
	if (continu == 1){
		flushall();
		if (cleanhistory == 0){
			if (arithTrig[0] != '\0'&&verify == 1){
				if (isFromMain == 1){
					system("title Advanced Trigonometry Calculator v1.8.6                                                            ==) Calculating... (==              ");
				}
				initialProcessor(arithTrig, result1);
			}
		}
		if (arithTrig[0] != '\0'&&txt != 1){
			if (res == '+'){
				sum(result1, result2, resultR, resultI);
			}
			if (res == '-'){
				subtraction(result1, result2, resultR, resultI);
			}
			if (res == '/'){
				division(result1, result2, resultR, resultI);
			}
			if (res == '*' || res == 'x'){
				multiplication(result1, result2, resultR, resultI);
			}
			if (res == '^'){
				exponentiation(result1, result2, resultR, resultI, 1);
			}
			if (verify == 1){
				verified = 1;
				round_complex();
				result1 = resultR;
				result2 = resultI;
				resultFI = result2;

				if (var == 1){
					variableController(revariable, result1);
				}
				if (valGet == 0){
					if (dp == -1){
						ans[rf] = result1;
						ansI[rf] = result2;
						if (isFromMain == 1){
							if (result1 > 0 && result2 > 0){
								printf("#%d=%G+%Gi\n", rf, result1, result2);
							}
							else{
								if (result1 > 0 && result2 < 0){
									printf("#%d=%G%Gi\n", rf, result1, result2);
								}
								else{
									if (result1 < 0 && result2 > 0){
										printf("#%d=%G+%Gi\n", rf, result1, result2);
									}
									else{
										if (result1 < 0 && result2 < 0){
											printf("#%d=%G%Gi\n", rf, result1, result2);
										}
										else{
											if (result1 == 0 && result2 == 0){
												printf("#%d=%G\n", rf, result1);
											}
											else{
												if (result1 == 0 && result2 != 0){
													printf("#%d=%Gi\n", rf, result2);
												}
												else{
													if (result1 != 0 && result2 == 0){
														printf("#%d=%G\n", rf, result1);
													}
													else{
														printf("#%d=%G+%Gi\n", rf, result1, result2);
													}
												}
											}
										}
									}
								}
							}
						}
						if (fout != NULL){
							fclose(fout);
						}
						fout = NULL;
						while (fout == NULL){
							fout = fopen(path, "a+");
						}
						if (result1 > 0 && result2 > 0){
							fprintf(fout, "#%d=%G+%Gi\n", rf, result1, result2);
						}
						else{
							if (result1 > 0 && result2 < 0){
								fprintf(fout, "#%d=%G%Gi\n", rf, result1, result2);
							}
							else{
								if (result1 < 0 && result2 > 0){
									fprintf(fout, "#%d=%G+%Gi\n", rf, result1, result2);
								}
								else{
									if (result1 < 0 && result2 < 0){
										fprintf(fout, "#%d=%G%Gi\n", rf, result1, result2);
									}
									else{
										if (result1 == 0 && result2 == 0){
											fprintf(fout, "#%d=%G\n", rf, result1);
										}
										else{
											if (result1 == 0 && result2 != 0){
												fprintf(fout, "#%d=%Gi\n", rf, result2);
											}
											else{
												if (result1 != 0 && result2 == 0){
													fprintf(fout, "#%d=%G\n", rf, result1);
												}
												else{
													fprintf(fout, "#%d=%G+%Gi\n", rf, result1, result2);
												}
											}
										}
									}
								}
							}
						}

						fclose(fout);
						rf++;
					}
					if (dp > -1){
						ans[rf] = result1;
						ansI[rf] = resultFI;
						if (result1 > 0 && result2 > 0){
							sprintf(dP, "#%d=%%.%df+%%.%dfi\n", rf, dp, dp);
							if (isFromMain == 1){
								printf(dP, result1, result2);
							}
						}
						if (result1 > 0 && result2 < 0){
							sprintf(dP, "#%d=%%.%df%%.%dfi\n", rf, dp, dp);
							if (isFromMain == 1){
								printf(dP, result1, result2);
							}
						}
						if (result1 < 0 && result2 > 0){
							sprintf(dP, "#%d = %%.%df+%%.%dfi\n", rf, dp, dp);
							if (isFromMain == 1){
								printf(dP, result1, result2);
							}
						}
						if (result1 < 0 && result2 < 0){
							sprintf(dP, "#%d=%%.%df%%.%dfi\n", rf, dp, dp);
							if (isFromMain == 1){
								printf(dP, result1, result2);
							}
						}
						if (result1 == 0 && result2 == 0){
							sprintf(dP, "#%d=%%.%df\n", rf, dp);
							if (isFromMain == 1){
								printf(dP, result1);
							}
						}

						if (result1 == 0 && result2 != 0){
							sprintf(dP, "#%d=%%.%dfi\n", rf, dp);
							if (isFromMain == 1){
								printf(dP, result2);
							}
						}
						if (result1 != 0 && result2 == 0){
							sprintf(dP, "#%d=%%.%df\n", rf, dp);
							if (isFromMain == 1){
								printf(dP, result1);
							}
						}


						if (fout != NULL){
							fclose(fout);
						}
						fout = NULL;
						while (fout == NULL){
							fout = fopen(path, "a+");
						}
						fprintf(fout, dP, result1);
						fclose(fout);
						rf++;
					}
					open = fopen("numSystems.txt", "r");
					char numSys[DIM] = "";
					int numeriSys = 0;
					if (open != NULL || bp != -1 || op != -1 || hp != -1){
						if (open != NULL){
							fgets(numSys, 10, open);
							numeriSys = atoi(numSys);
							fclose(open);
						}
						if (numeriSys == 1 || bp != -1 || op != -1 || hp != -1){
							char syst[DIM] = "";
							sprintf(syst, "%G", result1);
							if (syst[0] == '1'&&syst[1] == '.'&&syst[2] == '#'&&syst[3] == 'I'&&syst[4] == 'N'&&syst[5] == 'F'){
								if (isFromMain == 1){
									puts("In binary=11111111111111111111111111111111.#INF");
									puts("In octal=77777777777777777777777777777777.#INF");
									puts("In hexadecimal=FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF.#INF");
								}
								open = fopen(path, "a+");
								fputs("In binary=11111111111111111111111111111111.#INF\n", open);
								fputs("In octal=77777777777777777777777777777777.#INF\n", open);
								fputs("In hexadecimal=FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF.#INF\n", open);
								fclose(open);
							}
							else{
								if (syst[0] == '-'&&syst[1] == '1'&&syst[2] == '.'&&syst[3] == '#'&&syst[4] == 'I'&&syst[5] == 'N'&&syst[6] == 'F'){
									if (isFromMain == 1){
										puts("In binary=-11111111111111111111111111111111.#INF");
										puts("In octal=-77777777777777777777777777777777.#INF");
										puts("In hexadecimal=-FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF.#INF");
									}
									open = fopen(path, "a+");
									fputs("In binary=-11111111111111111111111111111111.#INF\n", open);
									fputs("In octal=-77777777777777777777777777777777.#INF\n", open);
									fputs("In hexadecimal=-FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF.#INF\n", open);
									fclose(open);
								}
								else{
									char Value[DIM] = "";
									sprintf(Value, "%G", result1);
									for (int v = 0; Value[v]; v++){
										if (Value[v] == '-')  {
											Value[v] = '_';
										}
										if (Value[v] == '+')  {
											Value[v] = '0';
										}
									}
									result1 = initialProcessor(Value, 0);
									if (result1 != 0 || result1 == 0 && result2 == 0){
										open = fopen(path, "a+");
										fputs("\nReal part:\n", open);
										if (isFromMain == 1){
											puts("\nReal part:\n");
										}
										fclose(open);
										decimalToBinary(result1, path, bp);
										decimalToOctal(result1, path, op);
										decimalToHexadecimal(result1, path, hp);
									}
									if (result2 != 0){
										open = fopen(path, "a+");
										fputs("\nImaginary part:\n", open);
										if (isFromMain == 1){
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

					open = fopen("siPrefixes.txt", "r");
					char siPref[DIM] = "";
					int niPrefix = 0;
					if (open != NULL){
						fgets(siPref, 10, open);
						fclose(open);
						niPrefix = atoi(siPref);
						if (niPrefix == 1){
							if (result1 != 0 || result1 == 0 && result2 == 0){
								open = fopen(path, "a+");
								if (isFromMain == 1){
									printf("\nReal part");
								}
								fprintf(open, "\nReal part");
								fclose(open);
								prefDet(result1, path);
							}
							if (result2 != 0){
								open = fopen(path, "a+");
								if (isFromMain == 1){
									printf("\nImaginary part");
								}
								fprintf(open, "\nImaginary part");
								fclose(open);
								prefDet(result2, path);
							}
						}
					}

					open = fopen("actualTime.txt", "r");
					char actualTime[DIM] = "";
					int nactualTime = 0;
					if (open != NULL){
						fgets(actualTime, 10, open);
						fclose(open);
						nactualTime = atoi(actualTime);
						if (nactualTime == 1 && isFromMain == 1){
							puts("");
							Clock(1);
						}
					}
					if (isFromMain == 1){
						printf("\n");
					}
					FILE *fout = NULL;
					while (fout == NULL){
						fout = fopen(path, "a+");
					}
					fputs("\n", fout);
					fclose(fout);
					if (isFromMain == 1){
						system("title Advanced Trigonometry Calculator v1.8.6                                                      ==) Calculated, you can enter more data (==              ");
					}
				}
			}
			else{
				if (valGet == 0){
					if (isFromMain == 1){
						printf("\nError in syntax.\n\n");
					}
					FILE *fout = NULL;
					while (fout == NULL){
						fout = fopen(path, "a+");
					}
					fprintf(fout, "\nError in syntax.\n\n");
					fclose(fout);
					system("title Advanced Trigonometry Calculator v1.8.6                                                             ==) Enter data (==              ");
				}
			}
		}
	}
	return result1;
}
