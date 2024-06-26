

#include "stdafx.h"

int rasf = 0, maxLength = 0, vectorType = 0, check4Vector = 0, numVectorLines = 0, numVectorCols = 0, matrixMode = 0, previousAnsType = 0;
boolean solving = true;
char saveArithTrig[DIM] = "", actualTime[DIM] = "", siPref[DIM] = "", verboseRes[DIM] = "", saveExpressionFF[DIM] = "", renamedVariable[DIM] = "", vectorString[DIM] = "", saveMatrixAns[DIM];

double main_core(char arithTrig[DIM], char fTrig[DIM], FILE *fout, char path[DIM], double result1, double result2, int isFromMain) {
	if (rf > 0) {
		ansRV = ans[rf - 1];
		ansIV = ansI[rf - 1];
	}
	fflush(NULL);
	verbose = 0;
	verified = 0;
	rasf = 0;
	resultR = 0; resultI;
	int txt = 0, var = 0, str = 0, s = 0, i = 0, space = 0, v = 0, j = 0, valGet = 0, h = 0, run_del_space = 1, strIndex = 0, StringManual = 0;
	char variable[DIM] = "", getVarName[DIM] = "", getVar[DIM] = "", savefTrig[DIM] = "";
	boolean command = 0, cleanhistory = 0;
	txt = 0;
	valid = 1;
	validVar = 1;
	str = 0;
	nPlaces = 0;
	sprintf(savefTrig, "%s", fTrig);
	replaceTimes = 0;
	char withoutSpaces[DIM] = "";
	replaceTimes = 0;
	if (isContained(" ", arithTrig)) {
		replaceTimes = 0;
		replace(" ", "", arithTrig);
		sprintf(withoutSpaces, "%s", expressionF);
	}
	else {
		sprintf(withoutSpaces, "%s", arithTrig);
	}
	int getString = 0;
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
				arithTrig[0] = '\0';
			}
			else {
				puts("\nTo create string variables only letters from latin alphabet and digits 0-9 can be used.\nTo create numerical variables only letters from latin alphabet can be used.");
				command = 1;
				arithTrig[0] = '\0';
			}
			sprintf(arithTrig, "%s=%s", getVarName, getVar);
			if (isContained("\"", arithTrig)) {
				getString = 1;
			}
			command = 0;
		}
		else {
			puts("\nError in syntax in get function.\n");
			command = 1;
		}

	}
	if (isContained("opentxt", withoutSpaces) == false && isContained(":\\", withoutSpaces) == false && (isContained("=\"", withoutSpaces) || isContained("=replace(", withoutSpaces) || isContained("=replacebyindex(", withoutSpaces) || isContained("=deletexoccurrences(", withoutSpaces))) {
		StringManual = 1;
		if (isContained("=deletexoccurrences(", arithTrig)) {
			renamer(arithTrig);
			sprintf(arithTrig, "%s", expressionF);
			int i = strEnd, j = 0;
			char to_find[DIM] = "", value[DIM] = "", string[DIM] = "";
			if (countOccurrences("\\", arithTrig) == 2) {
				while (arithTrig[i] != '\\') {
					to_find[j] = arithTrig[i];
					j++; i++;
				}
				to_find[j] = '\0';
				stringVariableToString(to_find);
				sprintf(to_find, "%s", variableSTring);
				i++;
				j = 0;
				while (arithTrig[i] != '\\') {
					string[j] = arithTrig[i];
					j++; i++;
				}
				string[j] = '\0';
				stringVariableToString(string);
				sprintf(string, "%s", variableSTring);
				i++;
				j = 0;
				while (arithTrig[i] != ')'&&arithTrig[i] != '\0') {
					value[j] = arithTrig[i];
					j++; i++;
				}
				value[j] = '\0';
				int times = (int)solveMath(value);
				replaceTimes = 0;
				deleteXOccurrences(to_find, string, times);
				replaceTimes = 0;
				char stringObtained[DIM] = "";
				sprintf(stringObtained, "%s", expressionF);
				char variableString[DIM] = "";
				int p = 0;
				i = 0;
				while (arithTrig[i] != '=') {
					variableString[p] = arithTrig[i];
					p++; i++;
				}
				variableString[p] = '\0';
				int hk = variableValidator(variableString);
				char variableFeedback[DIM] = "";
				if (hk == 1) {
					processVariable(revariable);
					sprintf(variableString, "%s", revariable);
					stringVariableController(variableString, stringObtained);
				}
				if (hk == 2) {
					sprintf(variableFeedback, "\n==> Your variable was renamed to \"%s\". <==\n\n",
						revariable);
					sprintf(variableString, "%s", revariable);
					stringVariableController(variableString, stringObtained);
				}
				if (hk == 0) {
					sprintf(variableFeedback,
						"\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
					var = 0;
				}
				puts(variableFeedback);
				stringVariableController(variableString, stringObtained);
			}
			else {
				puts("\nError: Please use two \"\\\" to separate the variables.\n");
			}
			arithTrig[0] = '\0';

		}
		else {
			if (isContained("=replacebyindex(", arithTrig)) {
				renamer(arithTrig);
				sprintf(arithTrig, "%s", expressionF);
				int i = strEnd, j = 0;
				char to_find[DIM] = "", replacement[DIM] = "", value[DIM] = "", string[DIM] = "";
				if (countOccurrences("\\", arithTrig) == 4) {
					while (arithTrig[i] != '\\') {
						to_find[j] = arithTrig[i];
						j++; i++;
					}
					to_find[j] = '\0';
					renamer(to_find);
					sprintf(to_find, "%s", expressionF);
					stringVariableToString(to_find);
					sprintf(to_find, "%s", variableSTring);
					i++;
					j = 0;
					while (arithTrig[i] != '\\') {
						replacement[j] = arithTrig[i];
						j++; i++;
					}
					replacement[j] = '\0';
					renamer(replacement);
					sprintf(replacement, "%s", expressionF);
					stringVariableToString(replacement);
					sprintf(replacement, "%s", variableSTring);
					i++;
					j = 0;
					while (arithTrig[i] != '\\') {
						string[j] = arithTrig[i];
						j++; i++;
					}
					string[j] = '\0';
					renamer(string);
					sprintf(string, "%s", expressionF);
					stringVariableToString(string);
					sprintf(string, "%s", variableSTring);
					i++;
					j = 0;
					while (arithTrig[i] != '\\') {
						value[j] = arithTrig[i];
						j++; i++;
					}
					value[j] = '\0';
					int index = (int)solveMath(value);
					j = 0;
					while (arithTrig[i] != ')'&&arithTrig[i] != '\0') {
						value[j] = arithTrig[i];
						j++; i++;
					}
					value[j] = '\0';
					replaceTimes = (int)solveMath(value);
					replaceByIndex(to_find, replacement, string, index);
					replaceTimes = 0;
					char stringObtained[DIM] = "";
					sprintf(stringObtained, "%s", expressionF);
					char variableString[DIM] = "";
					int p = 0;
					i = 0;
					while (arithTrig[i] != '=') {
						variableString[p] = arithTrig[i];
						p++; i++;
					}
					variableString[p] = '\0';
					int hk = variableValidator(variableString);
					char variableFeedback[DIM] = "";
					if (hk == 1) {
						processVariable(revariable);
						sprintf(variableString, "%s", revariable);
						stringVariableController(variableString, stringObtained);
					}
					if (hk == 2) {
						sprintf(variableFeedback, "\n==> Your variable was renamed to \"%s\". <==\n\n",
							revariable);
						sprintf(variableString, "%s", revariable);
						stringVariableController(variableString, stringObtained);
					}
					if (hk == 0) {
						sprintf(variableFeedback,
							"\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
						var = 0;
					}
					puts(variableFeedback);
					stringVariableController(variableString, stringObtained);
				}
				else {
					puts("\nError: Please use four \"\\\" to separate the variables.\n");
				}
				arithTrig[0] = '\0';
			}
			else {
				if (isContained("=replace(", arithTrig)) {
					renamer(arithTrig);
					sprintf(arithTrig, "%s", expressionF);
					int i = strEnd, j = 0;
					char to_find[DIM] = "", replacement[DIM] = "", value[DIM] = "", string[DIM] = "";
					if (countOccurrences("\\", arithTrig) == 3) {
						while (arithTrig[i] != '\\') {
							to_find[j] = arithTrig[i];
							j++; i++;
						}
						to_find[j] = '\0';
						renamer(to_find);
						sprintf(to_find, "%s", expressionF);
						stringVariableToString(to_find);
						sprintf(to_find, "%s", variableSTring);
						i++;
						j = 0;
						while (arithTrig[i] != '\\') {
							replacement[j] = arithTrig[i];
							j++; i++;
						}
						replacement[j] = '\0';
						renamer(replacement);
						sprintf(replacement, "%s", expressionF);
						stringVariableToString(replacement);
						sprintf(replacement, "%s", variableSTring);
						i++;
						j = 0;
						while (arithTrig[i] != '\\') {
							string[j] = arithTrig[i];
							j++; i++;
						}
						string[j] = '\0';
						renamer(string);
						sprintf(string, "%s", expressionF);
						stringVariableToString(string);
						sprintf(string, "%s", variableSTring);
						i++;
						j = 0;
						while (arithTrig[i] != ')'&&arithTrig[i] != '\0') {
							value[j] = arithTrig[i];
							j++; i++;
						}
						value[j] = '\0';
						replaceTimes = (int)solveMath(value);
						replace(to_find, replacement, string);
						replaceTimes = 0;
						char stringObtained[DIM] = "";
						sprintf(stringObtained, "%s", expressionF);
						char variableString[DIM] = "";
						int p = 0;
						i = 0;
						while (arithTrig[i] != '=') {
							variableString[p] = arithTrig[i];
							p++; i++;
						}
						variableString[p] = '\0';
						int hk = variableValidator(variableString);
						char variableFeedback[DIM] = "";
						if (hk == 1) {
							processVariable(revariable);
							sprintf(variableString, "%s", revariable);
							stringVariableController(variableString, stringObtained);
						}
						if (hk == 2) {
							sprintf(variableFeedback, "\n==> Your variable was renamed to \"%s\". <==\n\n",
								revariable);
							sprintf(variableString, "%s", revariable);
							stringVariableController(variableString, stringObtained);
						}
						if (hk == 0) {
							sprintf(variableFeedback,
								"\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
							var = 0;
						}
						stringVariableController(variableString, stringObtained);
					}
					else {
						puts("\nError: Please use three \"\\\" to separate the variables.\n");
					}
					arithTrig[0] = '\0';
				}
			}
		}
	}

	for (i = 0; arithTrig[i] != '\0'; i++) {
		if (arithTrig[i] == '='&&arithTrig[i + 1] == '"') {
			str = 0;
			int p = 0;
			char variableString[DIM] = "";
			i = 0;
			while (arithTrig[i] != '=') {
				variableString[p] = arithTrig[i];
				p++; i++;
			}
			variableString[p] = '\0';
			i++;
			char string[DIM] = "";
			p = 0;
			while (arithTrig[i] != '\0') {
				string[p] = arithTrig[i];
				i++;
				p++;
			}
			string[p] = '\0';
			replaceTimes = 0;
			if (isContained("\"", string)) {
				replace("\"", "", string);
				sprintf(string, "%s", expressionF);
			}
			p = 0;
			while (verifyLetter(variableString[p])) {
				p++;
			}
			p++;
			int hk = variableValidator(variableString);
			char variableFeedback[DIM] = "";

			if (p == strlen(variableString)) {
				char toReplace[DIM] = "";
				sprintf(toReplace, "%s=", variableString);
				replace(toReplace, "", arithTrig);
				sprintf(arithTrig, "%s", expressionF);
				puts(" ");
			}

			if (hk == 1) {
				processVariable(revariable);
				sprintf(variableString, "%s", revariable);
				stringVariableController(variableString, string);
			}
			if (hk == 2) {
				sprintf(variableFeedback, "\n==> Your variable was renamed to \"%s\". <==\n\n",
					revariable);
				sprintf(variableString, "%s", revariable);
				stringVariableController(variableString, string);
			}
			if (hk == 0) {
				sprintf(variableFeedback,
					"\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
				var = 0;
			}
			puts(variableFeedback);
			sprintf(variableString, "%s", revariable);
			stringVariableController(variableString, string);
		}
	}
	if (isContained("getposvalue(", arithTrig) && arithTrig[0] == 'g' && 0 == strStart) {
		i = strEnd;
		for (i; arithTrig[i] != '\0'; i++) {
			if (arithTrig[i] == ')') {
				valGet = 1;
				break;
			}
		}
		if (valGet == 1) {
			h = 0;
			i = strEnd;
			while (arithTrig[i] != ')'&&arithTrig[i] != '\0') {
				getVarName[h] = arithTrig[i];
				h++; i++;
			}
			getVarName[h] = '\0';
			strIndex = 0;
			for (int ks = 0; getVarName[ks] != '\0'; ks++) {
				if (verifyLetter(getVarName[ks])) {
					strIndex++;
				}
			}
			double value;
			if (strIndex == strlen(getVarName)) {
				value = getPosValue();
			}
			else {
				puts("\nTo create variables only letters from latin alphabet can be used.");
				command = 1;
				arithTrig[0] = '\0';
			}
			sprintf(arithTrig, "%s=%s", getVarName, convert2Exponential(value));
			if (isContained("-", arithTrig)) {
				replaceTimes = 0;
				replace("-", "_", arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
			command = 0;
		}
		else {
			puts("\nError in syntax in get function.\n");
			command = 1;
			arithTrig[0] = '\0';
		}
	}
	variable[0] = '\0';
	if (!isContained("opentxt", arithTrig) && !isContained("open txt", arithTrig)) {
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == ':'&&arithTrig[i + 1] == '\\') {
				txt = 1;
			}
		}
	}
	for (i = 0; arithTrig[i] != '\0'; i++) {
		if (arithTrig[i] == '='&&arithTrig[i + 1] != '='&&arithTrig[i + 1] != '!') {
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
			fout = fopen(path, "a+");
			if (toWrite) {
				printf("\n==> Close the file with the answers to continue. <==\n\n");
				fputs("\n==> Close the file with the answers to continue. <==\n", fout);
				openTxt();
			}
			if (strlen(arithTrig) >= 1) {
				arithTrig[0] = '\0';
			}
		}
	}
	if (str == 1 || getString == 1) {
		int p = 0;
		char variableString[DIM] = "";
		p = 0;
		if (var == 1 && StringManual == 0) {
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
				p = 0;
				while (verifyLetter(variableString[p])) {
					p++;
				}
				int hk = variableValidator(variableString);
				char variableFeedback[DIM] = "";
				if (hk == 1) {
					processVariable(revariable);
					sprintf(variableString, "%s", revariable);
					stringVariableController(variableString, arithTrig);
				}
				if (hk == 2) {
					sprintf(variableFeedback, "\n==> Your variable was renamed to \"%s\". <==\n\n",
						revariable);
					sprintf(variableString, "%s", revariable);
					stringVariableController(variableString, arithTrig);
				}
				if (hk == 0) {
					sprintf(variableFeedback,
						"\n==> Invalid variable. Use only latin alphabet letters. <==\n\n");
					var = 0;
				}
				stringVariableController(variableString, arithTrig);
				puts(variableFeedback);
				if (valGet == 0) {
					puts(" ");
				}
			}
			else {
				if (isFromMain == 1) {
					printf("\n==> Invalid string name! Only letters from latin alphabet and digits 0-9 can be used. <==\n\n");
				}
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
		}
		if (fout != NULL) {
			fclose(fout);
		}
		fout = NULL;
		while (fout == NULL) {
			fout = fopen(path, "a+");
		}
		if (verify == 1) {
			fprintf(fout, ">%s\n", savefTrig);
		}

		command = commands(arithTrig, path, result1, result2, fout);

		if (command == (boolean)false && continu&&strlen(arithTrig) > 0) {
			main_sub_core(arithTrig, fout, verify, path, txt, variable, v, j, result1, result2, isFromMain, var, valGet, command);
			sprintf(arithTrig, ""); sprintf(fTrig, ""); arithTrig[0] = '\0'; fTrig[0] = '\0';
		}

		if (fout != NULL) {
			fclose(fout);
		}
	}
	return result1;
}

double main_sub_core(char arithTrig[DIM], FILE *fout, int verify, char path[DIM], int txt, char variable[DIM], int v, int j, double result1, double result2, int isFromMain, int var, int valGet, int command) {
	int vectorType = 0;
	char vectorString[DIM] = "";
	FILE *open = NULL;
	if (isContained("solver", arithTrig)) {
		if (isContainedByIndex("-x", arithTrig, 1)) {
			replace("-x", "+_x", arithTrig);
			sprintf(arithTrig, "%s", expressionF);
		}
	}
	int  g = 0, Dimensions = 2, Window = 3, r = 0, i = 0, s = 0;
	char exit[DIM] = "", res = ' ', varLetters[DIM] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", saveArithTr[DIM] = "";
	if (!solverRunning && !equationSolverRunning) {
		res = arithTrig[0];
		if (res == '+' || res == '-' || res == '/' || res == '*' || res == '^') {
			for (i = 0; arithTrig[i] != '\0'; i++) {
				arithTrig[i] = arithTrig[i + 1];
			}
		}
	}
	if (var == 1) {
		if (isContained("==", arithTrig) == (boolean)false && isContained("!=", arithTrig) == (boolean)false) {
			for (i = 0; arithTrig[i] != '='&&arithTrig[i] != '\0'; i++) {
				variable[i] = arithTrig[i];
			}
			variable[i] = '\0';
			if (feedbackValidation == 0) {
				useForVariables = true;
			}
			g = i + 1;
			for (i = 0; arithTrig[i] != '\0'; i++) {
				arithTrig[i] = arithTrig[i + g];
			}
			arithTrig[i] = '\0';
			sprintf(saveArithTr, "%s", arithTrig);
			sprintf(arithTrig, "");
			i = 0;
			int hk = variableValidator(variable);
			if (isContained("atc_", saveArithTr)) {
				sprintf(renamedVariable, "%s", revariable);
			}
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
					printf("\n==> Invalid variable. Use only latin alphabet letters and be careful to avoid the same name for variables and user functions. <==\n\n");
				}
				fprintf(fout, "\n==> Invalid variable. Use only latin alphabet letters and be careful to avoid the same name for variables and user functions. <==\n\n");
				var = 0;
			}
			sprintf(arithTrig, "%s", saveArithTr);
			if (isContained("\\", arithTrig) && isContained(";", arithTrig) && !runningScript) {
				matrixMode = 1;
				vectorType = 2;
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

				countSplits = countOccurrences(";", arithTrig);
				int N = countSplits + 1;
				split(";", arithTrig);
				i = 0;
				char value[DIM][DIM], lines[DIM][DIM];
				while (i <= countSplits) {
					sprintf(lines[i], "%s", splitResult[i]);
					sprintf(splitResult[i], "");
					i++;
				}
				int l = 0;
				int countLines = countSplits;
				double vectorR[100], vectorI[100];
				int previousNumCols = 0;
				while (l <= countLines) {
					int initialCountSplits = 0;
					int i = 0;
					if (countSplits > 0) {
						initialCountSplits = countSplits;
						while (i < countSplits) {
							sprintf(saveSplitResult[i], "%s", splitResult[i]);
							sprintf(splitResult[i], "");
							i++;
						}
					}
					countSplits = countOccurrences("\\", lines[l]);
					int N = countSplits + 1;
					if (previousNumCols == 0) {
						previousNumCols = N;
					}
					else {
						if (N != previousNumCols) {
							if (isFromMain == 1) {
								printf("\n==> Error: You are probably missing some members of the matrix. <==\n\n");
							}
							fprintf(fout, "\n==> Error: You are probably missing some members of the matrix. <==\n\n");
							validVar = 0;
							verify = 0;
							break;
						}
					}
					split("\\", lines[l]);
					i = 0;

					while (i <= countSplits) {
						sprintf(value[i], "%s", splitResult[i]);
						i++;
					}
					i = 0;
					while (i <= countSplits) {
						calcNow(value[i], 0, 0);
						vectorR[i] = resultR; vectorI[i] = resultI;
						if (i < countSplits) {
							convertComplex2Exponential(vectorR[i], vectorI[i]);
							sprintf(vectorString, "%s%s+%si\\", vectorString, respR, respI);
						}
						else {
							convertComplex2Exponential(vectorR[i], vectorI[i]);
							sprintf(vectorString, "%s%s+%si", vectorString, respR, respI);
						}
						i++;
					}
					if (l < countLines) {
						sprintf(vectorString, "%s;", vectorString);
					}
					l++;
				}
				if (hk != 0 && verify == 1) {
					sprintf(expressionF, "%s", vectorString);
					sprintf(matrixResult, "%s", vectorString);
					variableController(revariable, 0);
					sprintf(expressionF, "");
				}
				sprintf(matrixResult, "%s", vectorString);
			}
			else {
				if (isContained("\\", arithTrig) && !isContained(";", arithTrig) && !runningScript && !isContained("getcols", arithTrig) && !isContained("getlins", arithTrig)) {
					matrixMode = 1;
					vectorType = 1;
					double vectorR[100], vectorI[100];
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
					countSplits = countOccurrences("\\", arithTrig);
					int N = countSplits + 1;
					split("\\", arithTrig);
					i = 0;
					char value[DIM][DIM];
					while (i <= countSplits) {
						sprintf(value[i], "%s", splitResult[i]);
						i++;
					}
					i = 0;
					while (i <= countSplits) {
						calcNow(value[i], 0, 0);
						vectorR[i] = resultR; vectorI[i] = resultI;
						if (i < countSplits) {
							convertComplex2Exponential(vectorR[i], vectorI[i]);
							sprintf(vectorString, "%s%s+%si\\", vectorString, respR, respI);
						}
						else {
							convertComplex2Exponential(vectorR[i], vectorI[i]);
							sprintf(vectorString, "%s%s+%si", vectorString, respR, respI);
						}
						i++;
					}
					if (hk != 0 && verify == 1) {
						sprintf(expressionF, "%s", vectorString);
						sprintf(matrixResult, "%s", vectorString);
						variableController(revariable, 0);
						sprintf(expressionF, "");
					}
					sprintf(matrixResult, "%s", vectorString);
				}
				else {
					if (!isContained("\\", arithTrig) && isContained(";", arithTrig) && !runningScript) {
						matrixMode = 1;
						vectorType = 1;
						double vectorR[100], vectorI[100];
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
						countSplits = countOccurrences(";", arithTrig);
						int N = countSplits + 1;
						split(";", arithTrig);
						i = 0;
						char value[DIM][DIM];
						while (i <= countSplits) {
							sprintf(value[i], "%s", splitResult[i]);
							i++;
						}
						i = 0;
						while (i <= countSplits) {
							calcNow(value[i], 0, 0);
							vectorR[i] = resultR; vectorI[i] = resultI;
							convertComplex2Exponential(vectorR[i], vectorI[i]);
							if (i < countSplits) {
								sprintf(vectorString, "%s%s+%si;", vectorString, respR, respI);
							}
							else {
								sprintf(vectorString, "%s%s+%si", vectorString, respR, respI);
							}
							i++;
						}
						if (hk != 0 && verify == 1) {
							sprintf(expressionF, "%s", vectorString);
							sprintf(matrixResult, "%s", vectorString);
							variableController(revariable, 0);
							sprintf(expressionF, "");
						}
						sprintf(matrixResult, "%s", vectorString);
					}
				}

			}
		}
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
	if (verify == 1 && !isContained("\\", arithTrig)) {
		if ((equationSolverRunning == false && solverRunning == false) || !isEqual(saveArithTrig, arithTrig)) {
			sprintf(saveArithTrig, "%s", arithTrig);
			manageExpression(arithTrig, 0, 0, 1);
			sprintf(arithTrig, "%s", expressionF);
			sprintf(saveExpressionFF, "%s", expressionF);
			synTest = 0;
			verify = dataVerifier(arithTrig, 0, 0, isFromMain, 1);
		}
		else {
			if ((equationSolverRunning || solverRunning)) {
				sprintf(arithTrig, "%s", saveExpressionFF);
				verify = 1;
			}
		}
	}
	if (verify == 1) {
		verified = 1;
	}
	if (fout != NULL) {
		fclose(fout);
	}
	if (arithTrig[0] != '\0'&&isFromMain == 1 && feedbackValidation == 0) {
		Clock(0);
	}
	char toOpen[DIM] = "";
	if (continu == 1) {
		_flushall();
		if (cleanhistory == 0) {
			if (arithTrig[0] != '\0'&&verify == 1) {
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
				if (resultR == 0 && solverRunning == false && equationSolverRunning == false) {
					initialProcessor(arithTrig, result1);
				}
				if (resultR == 0 && solverRunning == false && equationSolverRunning == false) {
					initialProcessor(arithTrig, result1);
				}
				if (resultR == 0 && solverRunning == false && equationSolverRunning == false) {
					initialProcessor(arithTrig, result1);
				}
				verbose = 0;
			}
		}
		if (arithTrig[0] != '\0'&&txt != 1 && processingOK == 1) {
			if (verify == 1) {
				if (previousAnsType == 0 && strlen(matrixResult) == 0) {
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
				}
				else {
					double resultRM = resultR, resultIM = resultI;
					double res_vectorR[dime][dime], res_vectorI[dime][dime], vector1_R[dime][dime], vector1_I[dime][dime];
					int numVectorCols1 = 0, numVectorLines1 = 0;
					double resRank = 0;
					if (res == '^') {
						if (strlen(matrixResult) == 0 && strlen(saveMatrixAns) > 0) {
							matrixMode = 1;
							convert2Vector(saveMatrixAns);
							if ((int)resultRM == -7654321 || (int)resultRM == -7654320) {
								fmtranspose(numVectorLines, numVectorCols, vectorR, vectorI, res_vectorR, res_vectorI);
								int savenumVectorCols = numVectorCols;
								numVectorCols = numVectorLines;
								numVectorLines = savenumVectorCols;
							}
							if ((int)resultRM == -1) {
								fminverse(numVectorLines, numVectorCols, vectorR, vectorI, res_vectorR, res_vectorI);
							}
							if (((int)resultRM >= 0 || (int)resultRM < -1) && ((int)resultRM) != -7654321 && ((int)resultRM) != -7654320 && ((int)resultRM) != -1234567) {
								fmpowerm(vectorR, vectorI, res_vectorR, res_vectorI, (int)resultRM, numVectorLines, numVectorCols);
							}
							if ((int)resultRM == -1234567) {
								convert2Vector(saveMatrixAns);
								int n = 0;
								int m = 0;
								for (n = 0; n < numVectorLines; n++) {
									for (m = 0; m < numVectorCols; m++) {
										vector1_R[n][m] = vectorR[n][m];
										vector1_I[n][m] = vectorI[n][m];
									}
								}
								numVectorCols1 = numVectorCols;
								numVectorLines1 = numVectorLines;
								resultR = (double)fmrank(numVectorLines1, numVectorCols1, vector1_R, vector1_I);
								resultI = 0;
							}
							else {
								sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines, numVectorCols));
							}
						}
					}
					if (res == '*') {
						if (strlen(matrixResult) > 0 && strlen(saveMatrixAns) > 0) {
							convert2Vector(saveMatrixAns);
							int n = 0;
							int m = 0;
							for (n = 0; n < numVectorLines; n++) {
								for (m = 0; m < numVectorCols; m++) {
									vector1_R[n][m] = vectorR[n][m];
									vector1_I[n][m] = vectorI[n][m];
								}
							}
							numVectorCols1 = numVectorCols;
							numVectorLines1 = numVectorLines;
							convert2Vector(matrixResult);
							fmmulm(numVectorLines, numVectorCols1, numVectorLines1, numVectorCols, vector1_R, vectorR, res_vectorR, vector1_I, vectorI, res_vectorI);
							sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));

						}
						else {
							if (strlen(matrixResult) > 0 && strlen(saveMatrixAns) == 0) {

								convert2Vector(matrixResult);
								fmmulr(numVectorLines, numVectorCols, vectorR, res_vectorR, result1, vectorI, res_vectorI, result2);

								sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
							}
							else {
								if (strlen(matrixResult) == 0 && strlen(saveMatrixAns) > 0) {
									convert2Vector(saveMatrixAns);
									fmmulr(numVectorLines, numVectorCols, vectorR, res_vectorR, resultRM, vectorI, res_vectorI, resultIM);
									sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
								}
							}
						}
					}
					if (res == '/') {
						if (strlen(matrixResult) == 0 && strlen(saveMatrixAns) > 0) {
							convert2Vector(saveMatrixAns);
							division(1.0, 0.0, resultRM, resultIM);
							fmmulr(numVectorLines, numVectorCols, vector1_R, res_vectorR, resultR, vector1_I, res_vectorI, resultI);
							sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
						}
						else {
							if (strlen(matrixResult) > 0 && strlen(saveMatrixAns) > 0) {
								convert2Vector(saveMatrixAns);
								int n = 0;
								int m = 0;
								for (n = 0; n < numVectorLines; n++) {
									for (m = 0; m < numVectorCols; m++) {
										vector1_R[n][m] = vectorR[n][m];
										vector1_I[n][m] = vectorI[n][m];
									}
								}
								numVectorCols1 = numVectorCols;
								numVectorLines1 = numVectorLines;
								convert2Vector(matrixResult);
								if (fmdivm(numVectorLines, numVectorCols1, numVectorLines1, numVectorCols, vector1_R, vectorR, vector1_I, vectorI)) {
									result1 = resultR;
									result2 = resultI;
								}
								else {
									if (isFromMain == 1) {
										printf("\nError: The quotient of matrices is not consistent over all matrices members.");
									}
								}
							}

						}
					}
					if (res == '-') {
						if (strlen(matrixResult) > 0 && strlen(saveMatrixAns) > 0) {
							convert2Vector(saveMatrixAns);
							int n = 0;
							int m = 0;
							for (n = 0; n < numVectorLines; n++) {
								for (m = 0; m < numVectorCols; m++) {
									vector1_R[n][m] = vectorR[n][m];
									vector1_I[n][m] = vectorI[n][m];
								}
							}
							numVectorCols1 = numVectorCols;
							numVectorLines1 = numVectorLines;
							convert2Vector(matrixResult);
							fmsubt(numVectorLines, numVectorCols, vector1_R, vectorR, res_vectorR, vector1_I, vectorI, res_vectorI);
							sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));

						}
					}
					if (res == '+') {
						if (strlen(matrixResult) > 0 && strlen(saveMatrixAns) > 0) {
							convert2Vector(saveMatrixAns);
							int n = 0;
							int m = 0;
							for (n = 0; n < numVectorLines; n++) {
								for (m = 0; m < numVectorCols; m++) {
									vector1_R[n][m] = vectorR[n][m];
									vector1_I[n][m] = vectorI[n][m];
								}
							}
							numVectorCols1 = numVectorCols;
							numVectorLines1 = numVectorLines;
							convert2Vector(matrixResult);
							fmsum(numVectorLines, numVectorCols, vector1_R, vectorR, res_vectorR, vector1_I, vectorI, res_vectorI);
							sprintf(matrixResult, "%s", convertVector2String(res_vectorR, res_vectorI, numVectorLines1, numVectorCols1));
						}
						if (strlen(matrixResult) > 0 && strlen(saveMatrixAns) == 0) {
							convert2Vector(matrixResult);
							sprintf(matrixResult, "%s", convertVector2String(vectorR, vectorI, numVectorLines, numVectorCols));
						}
						else {
							if (strlen(matrixResult) == 0 && strlen(saveMatrixAns) > 0) {
								convert2Vector(saveMatrixAns);
								sprintf(matrixResult, "%s", convertVector2String(vectorR, vectorI, numVectorLines, numVectorCols));
							}

						}

					}
				}
				verified = 1;
				roundSolution();
				result1 = resultR;
				result2 = resultI;
				resultFI = result2;

				ans[rf] = result1;
				ansI[rf] = result2;
				ansRV = result1;
				ansIV = result2;
				if (strlen(matrixResult) > 0) {
					previousAnsType = 1;
					sprintf(saveMatrixAns, "%s", matrixResult);
					sprintf(ansMatrices[rf], "%s", matrixResult);
				}
				else {
					previousAnsType = 0;
					sprintf(saveMatrixAns, "");
					sprintf(ansMatrices[rf], "");
				}
				if (var == 1) {

					char saveMatrixResult[DIM] = "";
					if (matrixMode == 1) {
						sprintf(saveMatrixResult, "%s", matrixResult);
					}
					if (matrixMode == 1 && isFromMain == 1) {

						convert2Vector(matrixResult);
						char report[DIM] = "";
						for (i = 0; i < numVectorLines; i++) {
							for (int k = 0; k < numVectorCols; k++) {
								convertComplex2Exponential(vectorR[i][k], vectorI[i][k]);
								sprintf(report, "%s%s+%si ", report, respR, respI);
							}
							sprintf(report, "%s\n", report);
						}
					}
					if (matrixMode == 1) {
						sprintf(matrixResult, "%s", saveMatrixResult);
					}
					if (strlen(matrixResult) > 0) {
						replaceTimes = 0;
						if (isContained("*", matrixResult)) {
							replace("*", ";", matrixResult);
							sprintf(matrixResult, "%s", expressionF);
						}
						if (isContained(":", matrixResult)) {
							replace(":", "\\", matrixResult);
							sprintf(matrixResult, "%s", expressionF);
						}
						sprintf(expressionF, "%s", matrixResult);
					}
					if ((matrixMode == 0 || matrixMode == 2 || strlen(matrixResult) > 0) && verify == 1) {
						variableController(revariable, result1);
					}
				}
				if (var == 1) {
					if ((isContained(";", matrixResult) || isContained("\\", matrixResult)) && !runningScript) {
						calcNow(revariable, 0, 0);
					}
				}
				if (valGet == 0 && feedbackValidation == 0) {
					if (strlen(renamedVariable) > 0 && isContained("atc_", arithTrig) && abs((int)strlen(variable)) > 0) {
						variableController(renamedVariable, result1);
					}
					if (matrixMode == 1) {
						convert2Vector(matrixResult);
						char report[DIM] = "";
						for (i = 0; i < numVectorLines; i++) {
							for (int k = 0; k < numVectorCols; k++) {
								convertComplex2Exponential(vectorR[i][k], vectorI[i][k]);
								sprintf(report, "%s%s+%si ", report, respR, respI);
							}
							sprintf(report, "%s\n", report);
						}
						if (isFromMain == 1) {
							printf("#%d=\n", rf);
							puts(report);
						}
						if (fout != NULL) {
							fclose(fout);
						}
						fout = NULL;
						while (fout == NULL) {
							fout = fopen(path, "a+");
						}
						if (fout != NULL) {
							fprintf(fout, "#%d=\n%s", rf, report);
							fclose(fout);
						}
					}

					if (matrixMode == 0 || (matrixMode == 2)) {
						if (dp == -1) {
							if (isFromMain == 1) {
								convertComplex2Exponential(result1, result2);
								if (result1 > 0 && result2 > 0) {
									printf("#%d=%s+%si\n", rf, respR, respI);
								}
								else {
									if (result1 > 0 && result2 < 0) {
										printf("#%d=%s%si\n", rf, respR, respI);
									}
									else {
										if (result1 < 0 && result2 > 0) {
											printf("#%d=%s+%si\n", rf, respR, respI);
										}
										else {
											if (result1 < 0 && result2 < 0) {
												printf("#%d=%s%si\n", rf, respR, respI);
											}
											else {
												if (result1 == 0 && result2 == 0) {
													printf("#%d=%s\n", rf, convert2Exponential(result1));
												}
												else {
													if (result1 == 0 && result2 != 0) {
														printf("#%d=%si\n", rf, convert2Exponential(result2));
													}
													else {
														if (result1 != 0 && result2 == 0) {
															printf("#%d=%s\n", rf, convert2Exponential(result1));
														}
														else {
															printf("#%d=%s+%si\n", rf, respR, respI);
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
							convertComplex2Exponential(result1, result2);
							if (result1 > 0 && result2 > 0) {
								fprintf(fout, "#%d=%s+%si\n", rf, respR, respI);
							}
							else {
								if (result1 > 0 && result2 < 0) {
									fprintf(fout, "#%d=%s%si\n", rf, respR, respI);
								}
								else {
									if (result1 < 0 && result2 > 0) {
										fprintf(fout, "#%d=%s+%si\n", rf, respR, respI);
									}
									else {
										if (result1 < 0 && result2 < 0) {
											fprintf(fout, "#%d=%s%si\n", rf, respR, respI);
										}
										else {
											if (result1 == 0 && result2 == 0) {
												fprintf(fout, "#%d=%s\n", rf, convert2Exponential(result1));
											}
											else {
												if (result1 == 0 && result2 != 0) {
													fprintf(fout, "#%d=%si\n", rf, convert2Exponential(result2));
												}
												else {
													if (result1 != 0 && result2 == 0) {
														fprintf(fout, "#%d=%s\n", rf, convert2Exponential(result1));
													}
													else {
														fprintf(fout, "#%d=%s+%si\n", rf, respR, respI);
													}
												}
											}
										}
									}
								}
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
					}
					int numLines = 0, numCols = 0;
					if (strlen(matrixResult) == 0) {
						numLines = 1; numCols = 1;
						vectorR[0][0] = result1; vectorI[0][0] = result2;
					}
					else {

						convert2Vector(matrixResult);
						numLines = numVectorLines;
						numCols = numVectorCols;
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
							int w = 0, y = 0;
							for (w = 0; w < numLines; w++) {
								for (y = 0; y < numCols; y++) {
									if (numLines > 1 || numCols > 1) {
										if (isFromMain == 1) {
											printf("\nm(%d,%d)=\n", w, y);
										}
										open = fopen(path, "a+");
										fputs("", open);
										fprintf(open, "\nm(%d,%d)=\n", w, y);
										fclose(open);
									}
									result1 = vectorR[w][y];
									result2 = vectorI[w][y];
									char syst[DIM] = "";
									sprintf(syst, "%s", convert2Exponential(result1));
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
							int w = 0, y = 0;
							for (w = 0; w < numLines; w++) {
								for (y = 0; y < numCols; y++) {
									if (numLines > 1 || numCols > 1) {
										if (isFromMain == 1) {
											printf("\nm(%d,%d)=\n", w, y);
										}
										open = fopen(path, "a+");
										fputs("", open);
										fprintf(open, "\nm(%d,%d)=\n", w, y);
										fclose(open);
									}
									result1 = vectorR[w][y];
									result2 = vectorI[w][y];
									char pref[DIM] = "";
									sprintf(pref, "%s", convert2Exponential(result1));
									char Value[DIM] = "";
									if (result1 != 0 || result1 == 0 && result2 == 0) {
										open = fopen(path, "a+");
										fputs("\nReal part:\n", open);
										if (isFromMain == 1) {
											puts("\nReal part:\n");
										}
										fclose(open);
										char pref[DIM] = "";
										sprintf(pref, "%s", convert2Exponential(result1));
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
										sprintf(pref, "%s", convert2Exponential(result2));
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
						}
					}
					if (isFromSolveNow == 0 && verify == 1 && verified == 1) {
						rf++;
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