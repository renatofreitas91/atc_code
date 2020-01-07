

#include "stdafx.h"
HANDLE hStdin;
DWORD fdwSaveOldMode;
int strStart = 0, strEnd = 0, Pressed = 0;
char dimensionsTxt[300] = "", windowTxt[300] = "";
using namespace std;
void numSystemsController() {
	FILE *open;
	int state = -1;
	while (state != 1 && state != 0) {
		I_O = true;
		printf("Enable -> 1\nDisable -> 0\n");
		state = (int)getValue();
		if (state != 1 && state != 0) {
			printf("Error, incorrect choice.\n");
		}
	}
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\numSystems.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d", state);
	fclose(open);
}

void verboseResolutionController() {
	FILE *open;
	int state = -1;
	while (state != 1 && state != 0) {
		I_O = true;
		printf("Enable -> 1\nDisable -> 0\n");
		state = (int)getValue();
		if (state != 1 && state != 0) {
			printf("Error, incorrect choice.\n");
		}
	}
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\verboseResolution.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d", state);
	fclose(open);
}

void siPrefixController() {
	FILE *open;
	int state = -1;
	while (state != 1 && state != 0) {
		I_O = true;
		printf("Enable -> 1\nDisable -> 0\n");
		state = (int)getValue();
		if (state != 1 && state != 0) {
			printf("Error, incorrect choice.\n");
		}
	}
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\siPrefixes.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d", state);
	fclose(open);
}

void actualTimeController() {
	FILE *open;
	int state = -1;
	while (state != 1 && state != 0) {
		I_O = true;
		printf("Enable -> 1\nDisable -> 0\n");
		state = (int)getValue();
		if (state != 1 && state != 0) {
			printf("Error, incorrect choice.\n");
		}
	}
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\actualTime.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d", state);
	fclose(open);
}

void variableController(char variable[DIM], double result) {
	FILE *open = NULL;
	char va[DIM] = "", vari[DIM] = "";
	int i = 0, f = 0;
	vari[0] = '\0';
	int y = 0, h = 0, k = 0, g = 0;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\variables.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open == NULL) {
		open = fopen(toOpen, "w");
	}
	if (open != NULL) {
		fclose(open);
	}
	open = NULL;
	while (open == NULL && i < 100) {
		open = fopen(toOpen, "a+");
		i++;
	}
	if (i < 100) {
		for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
		fclose(open);
		vari[i] = '\0';
		char toSearch_1[DIM] = "";
		sprintf(toSearch_1, "\n%s ", variable);
		char toSearch_2[DIM] = "";
		sprintf(toSearch_2, "%s ", variable);
		if (isContained(toSearch_1, vari)) {
			int i = strStart + 1;
			int h = 0;
			char variableData[DIM] = "";
			while (vari[i] != '\n'&&vari[i] != '\0') {
				variableData[h] = vari[i];
				h++;
				i++;
			}
			variableData[h] = '\n'; variableData[h + 1] = '\0';
			replaceTimes = 1;
			replace(variableData, "", vari);
			replaceTimes = 0;
			sprintf(vari, "%s", expressionF);
			open = fopen(toOpen, "w");
			fputs(vari, open);
			fclose(open);
		}
		else {
			if (isContained(toSearch_2, vari)) {
				int i = strStart;
				int h = 0;
				char variableData[DIM] = "";
				while (vari[i] != '\n'&&vari[i] != '\0') {
					variableData[h] = vari[i];
					h++;
					i++;
				}
				variableData[h] = '\n'; variableData[h + 1] = '\0';
				replaceTimes = 1;
				replace(variableData, "", vari);
				replaceTimes = 0;
				sprintf(vari, "%s", expressionF);
				open = fopen(toOpen, "w");
				fputs(vari, open);
				fclose(open);
			}
		}
		open = NULL;
		while (open == NULL) {
			open = fopen(toOpen, "a+");
		}
		fprintf(open, "%s %G %G\n", variable, resultR, resultI);
		fclose(open);
	}
}

void prefixDeterminator(double n, char path[DIM]) {
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\history.txt", atcPath);
	double result = 0;
	FILE *open;
	int a = 0;
	open = fopen(path, "a+");
	if (isEqual(path, toOpen)) {
		a = 1;
	}
	int y = 0;
	if (n < 0) {
		n = n * -1;
		y = 1;
	}
	char character = character_to_prefDet(n);
	switch (character)
	{
	case 'A':
		result = n / 1E-24;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%Gy (yocto-)\n", result);
		if (a == 1) {
			printf("=%Gy (yocto-)\n", result);
		}
		break;
	case 'B':
		result = n / 1E-21;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%Gz (zepto-)\n", result);
		if (a == 1) {
			printf("=%Gz (zepto-)\n", result);
		}
		break;
	case 'C':
		result = n / 1E-18;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%Ga (atto-)\n", result);
		if (a == 1) {
			printf("=%Ga (atto-)\n", result);
		}
		break;
	case 'D':
		result = n / 1E-15;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%Gf (femto-)\n", result);
		if (a == 1) {
			printf("=%Gf (femto-)\n", result);
		}
		break;
	case 'E':
		result = n / 1E-12;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%Gp (pico-)\n", result);
		if (a == 1) {
			printf("=%Gp (pico-)\n", result);
		}
		break;
	case 'F':
		result = n / 1E-9;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%Gn (nano-)\n", result);
		if (a == 1) {
			printf("=%Gn (nano-)\n", result);
		}
		break;
	case 'G':
		result = n / 1E-6;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%Gµ (micro-)\n", result);
		if (a == 1) {
			printf("=%G%c (micro-)\n", result, 230);
		}
		break;
	case 'H':
		result = n / 1E-3;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%Gm (milli-)\n", result);
		if (a == 1) {
			printf("=%Gm (milli-)\n", result);
		}
		break;
	case 'I':
		result = n / 1E-2;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%Gc (centi-)\n", result);
		if (a == 1) {
			printf("=%Gc (centi-)\n", result);
		}
		break;
	case 'J':
		result = n / 1E-1;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%Gd (deci-)\n", result);
		if (a == 1) {
			printf("=%Gd (deci-)\n", result);
		}
		break;
	case 'K':
		result = n / 1E1;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%Gda (deca-)\n", result);
		if (a == 1) {
			printf("=%Gda (deca-)\n", result);
		}
		break;
	case 'L':
		result = n / 1E2;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%Gh (hecto-)\n", result);
		if (a == 1) {
			printf("=%Gh (hecto-)\n", result);
		}
		break;
	case 'M':
		result = n / 1E3;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%Gk (kilo-)\n", result);
		if (a == 1) {
			printf("=%Gk (kilo-)\n", result);
		}
		break;
	case 'N':
		result = n / 1E6;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%GM (mega-)\n", result);
		if (a == 1) {
			printf("=%GM (mega-)\n", result);
		}
		break;
	case 'O':
		result = n / 1E9;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%GG (giga-)\n", result);
		if (a == 1) {
			printf("=%GG (giga-)\n", result);
		}
		break;
	case 'P':
		result = n / 1E12;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%GT (tera-)\n", result);
		if (a == 1) {
			printf("=%GT (tera-)\n", result);
		}
		break;
	case 'Q':
		result = n / 1E15;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%GP (peta-)\n", result);
		if (a == 1) {
			printf("=%GP (peta-)\n", result);
		}
		break;
	case 'R':
		result = n / 1E18;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%GE (exa-)\n", result);
		if (a == 1) {
			printf("=%GE (exa-)\n", result);
		}
		break;
	case 'S':
		result = n / 1E21;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%GZ (zetta-)\n", result);
		if (a == 1) {
			printf("=%GZ (zetta-)\n", result);
		}
		break;
	case 'T':
		result = n / 1E24;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%GY (yotta-)\n", result);
		if (a == 1) {
			printf("=%GY (yotta-)\n", result);
		}
		break;
	default:
		break;
	}
	fclose(open);
}

void replace(char toReplace[DIM], char replacement[DIM], char string[DIM]) {
	char expression[DIM] = "", expressionG[DIM] = "", check_for_variable[DIM] = "";
	int i = 0, g = 0, j = 0, is_variable = 0, k = 0, n = 0;
	sprintf(expression, "%s", string);
	sprintf(expressionG, "%s", string);
	isContained(toReplace, expressionG);
	if (replaceTimes == 0) {
		do {
			i = strStart; j = 0;
			while (j < abs((int)strlen(replacement)) && i < DIM)
			{
				expression[i] = replacement[j];
				i++; j++;
			}
			g = strEnd;
			while (g < abs((int)strlen(expressionG)) && g < DIM&&i < DIM) {
				expression[i] = expressionG[g];
				g++;
				i++;
			}
			if (i < DIM) {
				expression[i] = '\0';
			}
			sprintf(expressionG, "%s", expression);
		} while (isContained(toReplace, expressionG) && i < DIM&&g < DIM);
		sprintf(expressionF, "%s", expressionG);
	}
	else {
		i = strStart; j = 0;
		while (j < abs((int)strlen(replacement)) && i < DIM)
		{
			expression[i] = replacement[j];
			i++; j++;
		}
		g = strEnd;
		while (g < abs((int)strlen(expressionG)) && g < DIM&&i < DIM) {
			expression[i] = expressionG[g];
			g++;
			i++;
		}
		if (i < DIM) {
			expression[i] = '\0';
		}
		sprintf(expressionF, "%s", expression);
	}
}

void replaceByIndex(char toReplace[DIM], char replacement[DIM], char string[DIM], int index) {
	char expression[DIM] = "", expressionG[DIM] = "", check_for_variable[DIM] = "";
	int i = 0, g = 0, j = 0, is_variable = 0, k = 0, n = 0;
	sprintf(expression, "%s", string);
	sprintf(expressionG, "%s", string);
	isContainedByIndex(toReplace, expressionG, index);
	if (replaceTimes == 0) {
		do {
			i = strStart; j = 0;
			while (j < abs((int)strlen(replacement)) && i < DIM)
			{
				expression[i] = replacement[j];
				i++; j++;
			}
			g = strEnd;
			while (g < abs((int)strlen(expressionG)) && g < DIM&&i < DIM) {
				expression[i] = expressionG[g];
				g++;
				i++;
			}
			if (i < DIM) {
				expression[i] = '\0';
			}
			sprintf(expressionG, "%s", expression);
		} while (isContainedByIndex(toReplace, expressionG, index) && i < DIM&&g < DIM);
		sprintf(expressionF, "%s", expressionG);
	}
	else {
		i = strStart; j = 0;
		while (j < abs((int)strlen(replacement)) && i < DIM)
		{
			expression[i] = replacement[j];
			i++; j++;
		}
		g = strEnd;
		while (g < abs((int)strlen(expressionG)) && g < DIM&&i < DIM) {
			expression[i] = expressionG[g];
			g++;
			i++;
		}
		if (i < DIM) {
			expression[i] = '\0';
		}
		sprintf(expressionF, "%s", expression);
	}
}

void renamer(char expression[DIM]) {
	expressionF[0] = '\0';
	char varLetters[DIM] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", varToRename[DIM] = "";
	int j = 0, k = 0, sd = 0, i = 0;
	for (k = 0; expression[k] != '\0'; k++) {
		for (i = 0; varLetters[i] != '\0'; i++) {
			if (expression[k] == varLetters[i]) {
				varToRename[j] = expression[k];
				j++;
				break;
			}
		}
		if (j > 0 && expression[k] != varLetters[i] && expression[k] != '\0') {
			varToRename[j] = '\0';
			varRename[0] = '\0';
			variableRenamer(varToRename);
			varToRename[0] = '\0';
			sd = k - j;
			j = 0;
			while (varRename[j] != '\0') {
				expression[sd] = varRename[j];
				j++; sd++;
			}
			j = 0;
		}
	}
	for (i = 0; expression[i] != '\0'&&i < abs((int)strlen(expression)) && i < DIM; i++) {
		expressionF[i] = expression[i];
	}
	expressionF[i] = '\0';
}



void variableRenamer(char variable[DIM]) {
	valRenamedVar = 0;
	sprintf(varRename, "");
	char vari[DIM] = "";
	int i = 0, j = 0;
	FILE *open = NULL;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\renamedVar.txt", atcPath);
	while (open == NULL && i < 50) {
		open = fopen(toOpen, "a+");
		i++;
	}
	if (open != NULL) {
		for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
		vari[i] = '\0';
		fclose(open);
		for (i = 0; vari[i] != '\0'; i++) {
			j = 0;
			if (variable[j] == vari[i] && (i == 0 || vari[i - 1] == '\n')) {
				while (variable[j] == vari[i] && vari[i] != '\0') {
					j++; i++;
				}
				if (strlen(variable) == j) {
					if (variable[j] == '\0'&&vari[i] == ' ') {
						valRenamedVar = 1;
						i++;
						j = 0;
						while (vari[i] != '\n'&&vari[i] != '\0') {
							varRename[j] = vari[i];
							j++; i++;
						}
						varRename[j] = '\0';
					}
				}
			}
		}
	}
}

void pathNameToPath(char pathName[DIM]) {
	FILE *open = NULL;
	int i = 0, j = 0, k = 0;
	char data[DIM] = "";
	pathNAme[0] = '\0';
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\pathName.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open == NULL) {
		puts("\n==> No path abbreviation created! <==\n");
	}
	else {
		for (i = 0; (data[i] = fgetc(open)) != EOF; i++);
		fclose(open);
		for (i = 0; data[i] != '\0'; i++) {
			if (data[i] == pathName[j] && (data[i - 1] == '\n' || i == 0)) {
				while (data[i] == pathName[j]) {
					j++;
					i++;
				}
				if (j == strlen(pathName) && data[i] == ' ') {
					i++;
					while (data[i] != '\n') {
						pathNAme[k] = data[i];
						k++; i++;
					}
					pathNAme[k] = '\0';
				}
			}
			else {
				j = 0;
			}
		}
		if (strlen(pathNAme) == 0) {
			puts("\n==> This path abbreviation not exist! <==\n");
		}
	}
}

void pathNameController(char pathName[DIM], char path[DIM]) {
	FILE *save = NULL;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\pathName.txt", atcPath);
	while (save == NULL) {
		save = fopen(toOpen, "a+");
	}
	char data[DIM] = "", paName[DIM] = "";
	int i = 0, j = 0, k = 0, y = 0, w = 0, l = 0;
	for (i = 0; (data[i] = fgetc(save)) != EOF; i++);
	data[i] = '\0';
	for (i = 0; data[i] != '\0'; i++) {
		if (data[i] == pathName[j] && (data[i - 1] == '\n' || i == 0)) {
			y = i;
			while (data[i] == pathName[j]) {
				j++;
				i++;
			}
			if (j == strlen(pathName) && data[i] == ' ') {
				i++;
				while (data[i] != '\n') {
					paName[k] = data[i];
					k++; i++;
				}
				paName[k] = '\0';
				w = abs((int)strlen(pathName)) + abs((int)strlen(paName)) + 3;
				for (l = y; data[l + w] != '\0'; l++) {
					data[l] = data[l + w];
				}
				data[l] = '\0';
				fclose(save);
				save = fopen(toOpen, "w");
				fputs(data, save);
				fclose(save);
			}
		}
		else {
			j = 0;
		}
	}
	save = fopen(toOpen, "a+");
	fprintf(save, "%s %s\n", pathName, path);
	fclose(save);
}

void stringVariableToString(char stringVariable[DIM]) {
	variableRenamer(stringVariable);
	if (valRenamedVar == 1) {
		sprintf(stringVariable, "%s", varRename);
	}
	validVar = 1;
	FILE *open = NULL;
	int i = 0, j = 0, k = 0;
	char data[DIM] = "";
	variableSTring[0] = '\0';
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\stringVariable.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open == NULL) {
		puts("\n==> No string variable created! <==\n");
		validVar = 0;
	}
	else {
		for (i = 0; (data[i] = fgetc(open)) != EOF; i++);
		data[i] = '\0';
		fclose(open);
		for (i = 0; data[i] != '\0'; i++) {
			j = 0;
			if (data[i] == stringVariable[j] && j == 0) {
				while (data[i] == stringVariable[j]) {
					j++;
					i++;
				}
				if (j == strlen(stringVariable)) {
					validVar = 1;
					char directory[MAX_PATH] = "";
					sprintf(directory, "%s\\Strings\\%s.txt", atcPath, stringVariable);
					open = fopen(directory, "a+");
					if (open != NULL) {
						for (k = 0; (variableSTring[k] = fgetc(open)) != EOF; k++);
						variableSTring[k] = '\0';
						fclose(open);
					}
				}
			}
		}

		if (!isContained(stringVariable, data)) {
			puts("\n==> This string variable doesn't exist! <==\n");
			validVar = 0;
		}
	}
}

void stringVariableController(char variable[DIM], char string[DIM]) {
	FILE *open = NULL;
	char va[DIM] = "", vari[DIM] = "";
	int i = 0, f = 0;
	vari[0] = '\0';
	int y = 0, h = 0, k = 0, g = 0;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\stringVariable.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open == NULL) {
		open = fopen(toOpen, "w");
	}
	if (open != NULL) {
		fclose(open);
	}
	open = NULL;
	while (open == NULL && i < 100) {
		open = fopen(toOpen, "a+");
		i++;
	}
	if (i < 100) {
		for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
		fclose(open);
		vari[i] = '\0';
		char toSearch_1[DIM] = "";
		sprintf(toSearch_1, "\n%s\n", variable);
		char toSearch_2[DIM] = "";
		sprintf(toSearch_2, "%s\n", variable);
		if (isContained(toSearch_1, vari)) {
			int i = strStart + 1;
			int h = 0;
			char variableData[DIM] = "";
			while (vari[i] != '\n'&&vari[i] != '\0') {
				variableData[h] = vari[i];
				h++;
				i++;
			}
			variableData[h] = '\n'; variableData[h + 1] = '\0';
			replaceTimes = 1;
			replace(variableData, "", vari);
			replaceTimes = 0;
			sprintf(vari, "%s", expressionF);
			open = fopen(toOpen, "w");
			fputs(vari, open);
			fclose(open);
		}
		else {
			if (isContained(toSearch_2, vari)) {
				int i = strStart;
				int h = 0;
				char variableData[DIM] = "";
				while (vari[i] != '\n'&&vari[i] != '\0') {
					variableData[h] = vari[i];
					h++;
					i++;
				}
				variableData[h] = '\n'; variableData[h + 1] = '\0';
				replaceTimes = 1;
				replace(variableData, "", vari);
				replaceTimes = 0;
				sprintf(vari, "%s", expressionF);
				open = fopen(toOpen, "w");
				fputs(vari, open);
				fclose(open);
			}
		}
		open = NULL;
		while (open == NULL) {
			open = fopen(toOpen, "a+");
		}
		fprintf(open, "%s\n", variable);
		fclose(open);
		char directory[MAX_PATH] = "";
		sprintf(directory, "%s\\Strings\\%s.txt", atcPath, variable);
		open = fopen(directory, "w");
		if (open != NULL) {
			fputs(string, open);
			fclose(open);
		}
	}
}

void variableToMultiply(char expression[DIM]) {
	int i = 0, j = 0, k = 0, v = -7, u = 0, d = 0, l = 0;
	char variable[DIM] = "", saveVariable[DIM] = "";
	while (expression[i] != '\0') {
		v = -7;
		if (verifyLetter(expression[i]) && (verifyLetter(expression[i - 1]) == false || i == 0)) {
			j = 0;
			u = i;
			validVar = 0;
			if (verifyLetter(expression[i])) {
				j = 0;
				variable[j] = expression[i];
				variable[j + 1] = '\0';
				while (isContained(variable, expression) && verifyLetter(expression[i])) {
					variable[j] = expression[i];
					variable[j + 1] = '\0';
					for (d = 0; variable[d] != '\0'; d++) {
						saveVariable[d] = variable[d];
					}
					saveVariable[d] = '\0';
					processVariable(variable);
					if (validVar == 0) {
						variableRenamer(variable);
						for (k = 0; varRename[k] != '\0'; k++) {
							variable[k] = varRename[k];
						}
						variable[k] = '\0';
						processVariable(variable);
					}
					for (d = 0; saveVariable[d] != '\0'; d++) {
						variable[d] = saveVariable[d];
					}
					variable[d] = '\0';
					if (validVar == 1) {
						l = abs((int)strlen(expression));
						v = i;
					}
					j++; i++;
				}
			}
			if (v > 0) {
				k = l;
				expression[k + 1] = '\0';
				for (k; k - 1 > v; k--) {
					expression[k] = expression[k - 1];
				}
				if (verifyNumber(expression[k + 1]) || verifyLetter(expression[k + 1])) {
					expression[k] = '*';
				}
				else {
					for (k; expression[k + 1] != '\0'; k++) {
						expression[k] = expression[k + 1];
					}
					expression[k] = '\0';
				}
				i = v;
			}
		}
		i++;
	}
	int y = 0;
	for (y = 0; expression[y] != '\0'; y++) {
		expressionF[y] = expression[y];
	}
	expressionF[y] = '\0';
}

void toMultiply(char expression[DIM], double result1, double result2) {
	char vari[DIM] = "";
	FILE *open;
	char variablesTxt[DIM] = "";
	sprintf(variablesTxt, "%s\\variables.txt", atcPath);
	open = fopen(variablesTxt, "a+");

	int i = 0, verify = 0, verifys = 0, j = 0;
	for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
	vari[i] = '\0';
	fclose(open);
	i = 0;
	char saveSplitResult[200][200];
	int initialCountSplits = 0;
	if (countSplits > 0) {
		initialCountSplits = countSplits;
		while (i < countSplits) {
			sprintf(saveSplitResult[i], "%s", splitResult[i]);
			i++;
		}
	}
	replaceTimes = 0;
	countSplits = countOccurrences("\n", vari);
	int saveCountSplits = countSplits;
	split("\n", vari);
	i = 0;
	j = 0;
	char saveLines[200][200];
	while (i < countSplits) {
		sprintf(saveLines[i], "%s", splitResult[i]);
		i++;
	}
	countSplits = countOccurrences(" ", saveLines[i]);
	split(" ", saveLines[i]);
	char variables[DIM] = ",";
	i = 0;
	while (i < saveCountSplits) {
		countSplits = countOccurrences(" ", saveLines[i]);
		split(" ", saveLines[i]);
		sprintf(variables, "%s%s,", variables, splitResult[0]);
		i++;
	}
	i = 0;
	countSplits = initialCountSplits;
	while (i < countSplits) {
		sprintf(splitResult[i], "%s", saveSplitResult[i]);
		i++;
	}
	i = 0;
	char value[DIM] = "", saveValue[DIM] = "";
	while (expression[i] != '\0') {
		if (expression[i] == '+'&&expression[i + 1] == '0'&&expression[i + 2] == '\0') {
			value[j] = expression[i];
			value[j + 1] = '0'; value[j + 2] = '\0';
			j++; i = i + 2;
		}
		else {
			if (verifyNumber(expression[i])) {
				while (verifyNumber(expression[i]) && expression[i] != '\0' || expression[i] == 'i'&&expression[i - 1] == '1') {
					value[j] = expression[i];
					value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
					j++; i++;
				}
			}
			else {
				if (verifyLetter(expression[i - 1]) == 0 && firstLetterVariable(expression[i])) {
					while (verifyLetter(expression[i]) && expression[i] != '\0') {
						value[j] = expression[i];
						j++; i++;
					}
					value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
					synTest = 0;
					verify = dataVerifier(value, result1, result2, 0, verify);
				}
				else {
					if (verifyLetter(expression[i - 1]) == 0 && firstLetterFunction(expression[i])) {
						value[j] = expression[i];
						value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
						j++; i++;
						synTest = 0;
						verify = dataVerifier(value, result1, result2, 0, verify);
						while (verify == 0 && expression[i] != '\0') {
							if (expression[i] == 'b') {
								value[j] = expression[i];
								j++; i++;
								while ((expression[i] == 'b'&&expression[i + 1] == '(') == false && expression[i] != '\0') {
									value[j] = expression[i];
									j++; i++;
								}
							}
							else {
								if (expression[i] == 'D') {
									value[j] = expression[i];
									j++; i++;
									while ((expression[i] == 'D'&&expression[i + 1] == '(') == false && expression[i] != '\0') {
										value[j] = expression[i];
										j++; i++;
									}
								}
								else {
									value[j] = expression[i];
									value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
									synTest = 0;
									verify = dataVerifier(value, result1, result2, 0, verify);
									j++; i++;
								}
							}
						}
					}
					else {
						if (verifyLetter(expression[i]) == 0 && verifyNumber(expression[i]) == 0) {
							while (verifyLetter(expression[i]) == 0 && verifyNumber(expression[i]) == 0 && expression[i] != '\0') {
								value[j] = expression[i];
								value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
								j++; i++;
								if (expression[i] == 'i') {
									value[j] = expression[i];
									value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
									j++; i++;
								}
							}
						}
						else {
							if (expression[i] == 'i') {
								value[j] = expression[i];
								j++; i++;
								value[j] = expression[i];
								value[j + 1] = '\0'; j++;
							}
							else {
								value[j] = expression[i];
								value[j + 1] = '\0';
							}
							synTest = 0;
							verify = dataVerifier(value, result1, result2, 0, verify);
							if (verify == 1 && firstLetterFunction(value[j]) == false && verifyLetter(value[j]) && value[j] != 'i') {
								j++; i++;
								while (verify == 1 && expression[i] != '\0') {
									value[j] = expression[i];
									value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
									synTest = 0;
									verify = dataVerifier(value, result1, result2, 0, verify);
									j++; i++;
								}
								if (verify == 0) {
									value[j - 1] = '+'; value[j] = '0'; value[j + 1] = '\0';
								}
								if (expression[i] != '\\'&&expression[i] != '+'&&expression[i] != '-'&&expression[i] != '*'&&expression[i] != '/'&&expression[i] != '^'&&expression[i] != '\0') {
									j--;
									if (expression[i] != '\\'&&expression[i - 1] != '+'&&expression[i - 1] != '-'&&expression[i - 1] != '*'&&expression[i - 1] != '/'&&expression[i - 1] != '^') {
										value[j] = '*';
										value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
										j++;
									}
									i--;
								}
							}
							else {
								value[j] = expression[i];
								value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
								synTest = 0;
								verify = dataVerifier(value, result1, result2, 0, verify);
								if (verify == 0) {
									j++; i++;
									while (verify == 0 && expression[i] != '\0') {
										value[j] = expression[i];
										value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
										synTest = 0;
										verify = dataVerifier(value, result1, result2, 0, verify);
										value[j + 1] = expression[i + 1]; value[j + 2] = '+'; value[j + 3] = '0'; value[j + 4] = '\0';
										int verifyS = dataVerifier(value, result1, result2, 0, verify);
										value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
										if (verify == verifyS && verify == 1 && verifyLetter(expression[i + 1])) {
											verify = 0;
										}
										j++; i++;
									}
									if (expression[i] != '\\'&&expression[i] != '+'&&expression[i] != '-'&&expression[i] != '*'&&expression[i] != '/'&&expression[i] != '^'&&expression[i] != '\0') {
										value[j] = '*';
										value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
										j++;
									}
								}
								else {
									i++;
								}
							}
						}
					}
				}
			}
		}
	}

	if (expression[0] == '('&&expression[1] == '('&&isContained("))", expression) && !dataVerifier(expression, 0, 0, 0, 1)) {
		int n = 0;
		while (n < abs((int)strlen(expression))) {
			expression[n] = expression[n + 1];
			n++;
		}
		expression[n] = '\0';

		if (expression[strlen(expression) - 1] == ')'&&expression[strlen(expression) - 2] == ')') {
			expression[strlen(expression) - 1] = '\0';
		}
		else {
			if (isContained("))", expression)) {
				int n = strStart;
				while (n < abs((int)strlen(expression))) {
					expression[n] = expression[n + 1];
					n++;
				}
				expression[n] = '\0';
			}
		}
	}
	replaceTimes = 0;
	if (!dataVerifier(expression, 0, 0, 0, 1)) {
		if (countOccurrences("(", expression) > countOccurrences(")", expression)) {
			while (countOccurrences("(", expression) > countOccurrences(")", expression)) {
				replaceTimes = 1;
				if (isContained("((", expression)) {
					replace("((", "(", expression);
					sprintf(expression, "%s", expressionF);
				}
				else {
					if (expression[0] == '(') {
						replace("(", "", expression);
						sprintf(expression, "%s", expressionF);
					}
				}

			}
		}
	}
	replaceTimes = 0;
	if (!dataVerifier(expression, 0, 0, 0, 1)) {
		if (countOccurrences(")", expression) > countOccurrences("(", expression)) {
			while (countOccurrences(")", expression) > countOccurrences("(", expression)) {
				if (isContained("))", expression)) {
					replace("))", ")", expression);
					sprintf(expression, "%s", expressionF);
				}
				else {
					if (expression[strlen(expression) - 1] == ')') {
						expression[strlen(expression) - 1] = '\0';
					}
					else {
						if (expression[strlen(expression) - 1] == '0'&&expression[strlen(expression) - 2] == '+'&&expression[strlen(expression) - 3] == ')') {
							expression[strlen(expression) - 3] = '\0';
						}
					}
				}
			}
		}
	}
	replaceTimes = 0;
	i = 0; j = 0;
	sprintf(value, ""); sprintf(saveValue, "");
	while (expression[i] != '\0') {
		if (firstLetterFunction(expression[i])) {
			while (verifyLetter(expression[i])) {
				i++;
			}
		}
		if (firstLetterVariable(expression[i])) {
			value[j] = expression[i];
			value[j + 1] = '\0';
			processVariable(value);
			if (validVar == 1) {
				while (validVar == 1 && letterVariables(expression[i + 1]) && expression[i] != '\0') {
					sprintf(saveValue, value);
					j++; i++;
					value[j] = expression[i];
					value[j + 1] = '\0';
					processVariable(value);
					if (validVar == 0) {
						sprintf(value, saveValue);
					}
					if (verifyLetter(expression[i + 1])) {
						int count = 0;
						count = countOccurrences(value, variables);
						if (count == 1) {
							char toReplace[10] = "", replacement[10] = "";
							sprintf(toReplace, "%s%c", value, expression[i + 1]);
							sprintf(replacement, "%s*%c", value, expression[i + 1]);
							replace(toReplace, replacement, expression);
							sprintf(expression, expressionF);
							sprintf(value, "");
						}
						else {
							validVar = 0;
							sprintf(value, "");
							while (verifyLetter(expression[i]) && validVar == 0) {
								sprintf(value, "%s%c", value, expression[i]);
								i++;
								char verifyVariable[200] = "";
								sprintf(verifyVariable, ",%s,", value);
								count = countOccurrences(value, variables);
								replaceTimes = 1;
								if (isContained(verifyVariable, variables) && count == 1) {
									isContained(value, expression);
									if (verifyLetter(expression[strStart - 1])) {
										char replacement[100] = "";
										sprintf(replacement, "*%s", value);

										replace(value, replacement, expression);
										sprintf(expression, "%s", expressionF);
									}
									isContained(value, expression);
									if (verifyLetter(expression[strEnd])) {
										char replacement[100] = "";
										sprintf(replacement, "%s*", value);
										replace(value, replacement, expression);
										sprintf(expression, "%s", expressionF);
									}

								}
							}
						}
					}
				}
			}
			j = 0;
		}
		i++;
	}
	sprintf(expressionF, expression);
}


void customFuncRenamer(char variable[DIM]) {
	int i = 0;
	for (i = 0; variable[i] != '\0'; i++) {
		if (i == 0 && (variable[i] == 's' || variable[i] == 'c' || variable[i] == 't' || variable[i] == 'a' || variable[i] == 'l' || variable[i] == 'r' || variable[i] == 'q' || variable[i] == 'g' || variable[i] == 'd')) {
			if (variable[i] == 's') {
				revariable[i] = 'S';
			}
			if (variable[i] == 'c') {
				revariable[i] = 'W';
			}
			if (variable[i] == 't') {
				revariable[i] = 'J';
			}
			if (variable[i] == 'a') {
				revariable[i] = 'k';
			}
			if (variable[i] == 'l') {
				revariable[i] = 'L';
			}
			if (variable[i] == 'r') {
				revariable[i] = 'R';
			}
			if (variable[i] == 'q') {
				revariable[i] = 'Q';
			}
			if (variable[i] == 'g') {
				revariable[i] = 'G';
			}
			if (variable[i] == 'd') {
				revariable[i] = 'K';
			}
		}
		else {
			if (variable[i] == 'i' || variable[i] == 'e' || variable[i] == 'D' || variable[i] == 'b') {
				if (variable[i] == 'i') {
					revariable[i] = 'Z';
				}
				if (variable[i] == 'e') {
					revariable[i] = 'w';
				}
				if (variable[i] == 'D') {
					revariable[i] = 'T';
				}
				if (variable[i] == 'b') {
					revariable[i] = 'u';
				}
			}
			else {
				if (i == 0 && (variable[i] == 'B' || variable[i] == 'O' || variable[i] == 'H' || variable[i] == 'P')) {
					if (variable[i] == 'B') {
						revariable[i] = 'N';
					}
					if (variable[i] == 'O') {
						revariable[i] = 'M';
					}
					if (variable[i] == 'H') {
						revariable[i] = 'V';
					}
					if (variable[i] == 'P') {
						revariable[i] = 'I';
					}
				}
				else {
					if (variable[i] == 'A' || variable[i] == 'B' || variable[i] == 'C' || variable[i] == 'E' || variable[i] == 'P' || (variable[i - 2] == 'I'&&variable[i - 1] == 'N') == false && variable[i] == 'F') {
						if (variable[i] == 'A') {
							revariable[i] = 'X';
						}
						if (variable[i] == 'B') {
							revariable[i] = 'N';
						}
						if (variable[i] == 'C') {
							revariable[i] = 'v';
						}
						if (variable[i] == 'E') {
							revariable[i] = 'Y';
						}
						if (variable[i] == 'F') {
							revariable[i] = 'U';
						}
						if (variable[i] == 'P') {
							revariable[i] = 'I';
						}
					}
					else {
						revariable[i] = variable[i];
					}
				}
			}
		}
	}
	revariable[i] = '\0';
}

void manageExpression(char arithTrig[DIM], double result1, double result2, int verify) {
	renamer(arithTrig);
	sprintf(arithTrig, expressionF);
	int i = 0, j = 0, s = 0, f = 0;
	variableToMultiply(arithTrig);
	toMultiply(arithTrig, result1, result2);
	variableToMultiply(arithTrig);
	renamer(arithTrig);
	sprintf(arithTrig, "%s", expressionF);
	variableToMultiply(arithTrig);
	for (i = 0; expressionF[i] != '\0'; i++) {
		arithTrig[i] = expressionF[i];
	}
	arithTrig[i] = '\0';
	char letterScan[DIM] = "";
	for (i = 0; arithTrig[i] != '\0'; i++) {
		if (verifyLetter(arithTrig[i])) {
			letterScan[i] = arithTrig[i];
		}
		else {
			letterScan[i] = ' ';
		}
	}
	letterScan[i] = '\0';
	char toTest[DIM] = "";
	int savePosition = 0;
	for (i = 0; letterScan[i] != '\0'; i++) {
		if (verifyLetter(letterScan[i])) {
			f = 0;
			savePosition = i;
			while (verifyLetter(letterScan[i])) {
				toTest[f] = letterScan[i];
				i++; f++;
			}
			toTest[f] = '\0';
			char usRFunc[DIM] = "";
			sprintf(usRFunc, "%s\\User functions\\%s.txt", atcPath, toTest);
			FILE *test = NULL;
			test = fopen(usRFunc, "r");
			if (test != NULL && (letterScan[savePosition - 4] == 'a'&&letterScan[savePosition - 3] == 't'&&letterScan[savePosition - 2] == 'c'&&letterScan[savePosition - 1] == ' ') == true) {
				customFuncRenamer(toTest);
				char renaFunc[DIM] = "";
				for (f = 0; revariable[f] != '\0'; f++) {
					renaFunc[f] = revariable[f];
				}
				renaFunc[f] = '\0';
				sprintf(usRFunctions, "%s%s,", usRFunctions, toTest);
				sprintf(usRFuncTrans, "%s%s,", usRFuncTrans, renaFunc);
				int p = 0;
				f = savePosition;
				for (p = 0; renaFunc[p] != '\0'; p++) {
					letterScan[f] = renaFunc[p];
					f++;
				}
			}
		}
	}
	for (i = 0; arithTrig[i] != '\0'; i++) {
		if (verifyLetter(arithTrig[i])) {
			arithTrig[i] = letterScan[i];
		}
	}
	renamer(arithTrig);
	for (i = 0; expressionF[i] != '\0'; i++) {
		arithTrig[i] = expressionF[i];
	}
	arithTrig[i] = '\0';
	variableToMultiply(arithTrig);
	for (i = 0; expressionF[i] != '\0'; i++) {
		arithTrig[i] = expressionF[i];
	}
	arithTrig[i] = '\0';
	renamer(arithTrig);
	for (i = 0; expressionF[i] != '\0'; i++) {
		arithTrig[i] = expressionF[i];
	}
	arithTrig[i] = '\0';

	renamer(arithTrig);
	for (i = 0; expressionF[i] != '\0'; i++) {
		arithTrig[i] = expressionF[i];
	}
	arithTrig[i] = '\0';
	int needOne = 1;
	while (needOne == 1) {
		needOne = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (arithTrig[i] == 'B' || arithTrig[i] == 'O' || arithTrig[i] == 'H') {
				i++;
				while (verifyNumerical(arithTrig[i])) {
					i++;
				}
				if (arithTrig[i - 1] == '1'&&arithTrig[i] == 'i') {
					j = i;
					i = abs((int)strlen(arithTrig)) + 1;
					while (i > j) {
						arithTrig[i] = arithTrig[i - 2];
						i--;
					}
					arithTrig[i] = '*'; arithTrig[i + 1] = '1';
					i = abs((int)strlen(arithTrig));
				}
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (arithTrig[i] == 'B' || arithTrig[i] == 'O' || arithTrig[i] == 'H') {
				i++;
				while (verifyNumerical(arithTrig[i])) {
					i++;
				}
				if (arithTrig[i - 1] == '1'&&arithTrig[i] == 'i') {
					needOne = 1;
				}
			}
		}
	}
	renamer(arithTrig);
	for (i = 0; expressionF[i] != '\0'; i++) {
		arithTrig[i] = expressionF[i];
	}
	arithTrig[i] = '\0';
	needOne = 1;
	while (needOne == 1) {
		needOne = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != '1'&& arithTrig[i - 1] != 'i'&&arithTrig[i - 1] != 'p'&& arithTrig[i] == 'i'&& verifyLetter(arithTrig[i + 1]) == 0 && verifyNumber(arithTrig[i + 1]) == false) {
				j = i;
				i = abs((int)strlen(arithTrig)) + 1;
				while (i > j) {
					arithTrig[i] = arithTrig[i - 2];
					i--;
				}
				arithTrig[i] = '*'; arithTrig[i + 1] = '1';
				i = abs((int)strlen(arithTrig));
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != '1'&& arithTrig[i - 1] != 'i'&&arithTrig[i - 1] != 'p'&& arithTrig[i] == 'i'&& verifyLetter(arithTrig[i + 1]) == 0 && verifyNumber(arithTrig[i + 1]) == false) {
				needOne = 1;
			}
		}
	}
	renamer(arithTrig);
	for (i = 0; expressionF[i] != '\0'; i++) {
		arithTrig[i] = expressionF[i];
	}
	arithTrig[i] = '\0';
	int needAst = 1;
	needAst = 1;
	while (needAst == 1) {
		needAst = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'e'&&verifyLetter(arithTrig[i + 1])) {
				j = i + 1;
				i = abs((int)strlen(arithTrig));
				while (i > j) {
					arithTrig[i] = arithTrig[i - 1];
					i--;
				}
				arithTrig[i] = '*';
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'e'&&verifyLetter(arithTrig[i + 1])) {
				needAst = 1;
			}
		}
	}
	needAst = 1;
	while (needAst == 1) {
		needAst = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'p'&& arithTrig[i + 1] == 'i'&&verifyLetter(arithTrig[i + 2])) {
				j = i + 2;
				i = abs((int)strlen(arithTrig));
				while (i > j) {
					arithTrig[i] = arithTrig[i - 1];
					i--;
				}
				arithTrig[i] = '*';
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'p'&& arithTrig[i + 1] == 'i'&&verifyLetter(arithTrig[i + 2])) {
				needAst = 1;
			}
		}
	}
	needAst = 1;
	while (needAst == 1) {
		needAst = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != 'b'&&arithTrig[i - 1] != 'D'&&arithTrig[i - 2] != 't'&&arithTrig[i - 3] != 'r' && arithTrig[i] == 'p'&& arithTrig[i + 1] == 'i'&&verifyLetter(arithTrig[i + 2]) == false) {
				j = i;
				i = abs((int)strlen(arithTrig));
				while (i > j) {
					arithTrig[i] = arithTrig[i - 1];
					i--;
				}
				arithTrig[i] = '*';
				i = abs((int)strlen(arithTrig));
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != 'b'&&arithTrig[i - 1] != 'D'&&arithTrig[i - 2] != 't'&&arithTrig[i - 3] != 'r' && arithTrig[i] == 'p'&& arithTrig[i + 1] == 'i'&&verifyLetter(arithTrig[i + 2]) == false) {
				needAst = 1;
			}
		}
	}
	needAst = 1;
	while (needAst == 1) {
		needAst = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'e'&&verifyLetter(arithTrig[i + 1]) == false) {
				j = i;
				i = abs((int)strlen(arithTrig));
				while (i > j) {
					arithTrig[i] = arithTrig[i - 1];
					i--;
				}
				arithTrig[i] = '*';
				i = abs((int)strlen(arithTrig));
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'e'&&verifyLetter(arithTrig[i + 1]) == false) {
				needAst = 1;
			}
		}
	}
	renamer(arithTrig);
	for (i = 0; expressionF[i] != '\0'; i++) {
		arithTrig[i] = expressionF[i];
	}
	arithTrig[i] = '\0';
	needAst = 1;
	while (needAst == 1) {
		needAst = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'p'&& arithTrig[i + 1] == 'i'&&verifyLetter(arithTrig[i + 2])) {
				if (arithTrig[i - 1] == 'D' || arithTrig[i - 1] == 'b') {
					while (verifyLetter(arithTrig[i])) {
						i--;
					}
					i++;
					int lo = 0;
					char func[DIM] = "";
					while (verifyLetter(arithTrig[i]) && arithTrig[i] != 'b'&&arithTrig[i] != 'D') {
						func[lo] = arithTrig[i];
						lo++; i++;
					}
					func[lo] = arithTrig[i]; lo++;
					func[lo] = arithTrig[i]; lo++;
					func[lo] = '?'; lo++;
					func[lo] = '\0';
					if (functionProcessor(func, 0, 0, 0) == 0.5) {
						i = i + 2;
					}
				}
			}
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'p'&& arithTrig[i + 1] == 'i'&&verifyLetter(arithTrig[i + 2])) {
				j = i;
				i = abs((int)strlen(arithTrig));
				while (i > j) {
					arithTrig[i] = arithTrig[i - 1];
					i--;
				}
				arithTrig[i] = '*';
				j = j + 3;
				i = abs((int)strlen(arithTrig));
				while (i > j) {
					arithTrig[i] = arithTrig[i - 1];
					i--;
				}
				arithTrig[i] = '*';
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'p'&& arithTrig[i + 1] == 'i'&&verifyLetter(arithTrig[i + 2])) {
				if (arithTrig[i - 1] == 'D' || arithTrig[i - 1] == 'b') {
					while (verifyLetter(arithTrig[i])) {
						i--;
					}
					i++;
					int lo = 0;
					char func[DIM] = "";
					while (verifyLetter(arithTrig[i]) && arithTrig[i] != 'b'&&arithTrig[i] != 'D') {
						func[lo] = arithTrig[i];
						lo++; i++;
					}
					func[lo] = arithTrig[i]; lo++;
					func[lo] = arithTrig[i]; lo++;
					func[lo] = '?'; lo++;
					func[lo] = '\0';
					if (functionProcessor(func, 0, 0, 0) == 0.5) {
						i = i + 2;
					}
				}
			}
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'p'&& arithTrig[i + 1] == 'i'&&verifyLetter(arithTrig[i + 2])) {
				needAst = 1;
			}
		}
	}
	renamer(arithTrig);
	for (i = 0; expressionF[i] != '\0'; i++) {
		arithTrig[i] = expressionF[i];
	}
	arithTrig[i] = '\0';
	needOne = 1;
	while (needOne == 1) {
		needOne = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i'&& verifyLetter(arithTrig[i + 1]) && arithTrig[i + 1] != 'D'&&arithTrig[i + 1] != 'b') {
				j = i + 1;
				i = abs((int)strlen(arithTrig));
				while (i > j) {
					arithTrig[i] = arithTrig[i - 1];
					i--;
				}
				arithTrig[i] = '*';
				i = abs((int)strlen(arithTrig));
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i'&& verifyLetter(arithTrig[i + 1]) && arithTrig[i + 1] != 'D'&&arithTrig[i + 1] != 'b') {
				needOne = 1;
			}
		}
	}
	needOne = 1;
	while (needOne == 1) {
		needOne = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != '1'&&arithTrig[i - 1] != 'p'&& arithTrig[i] == 'i'&& verifyLetter(arithTrig[i + 1]) == 0 && verifyNumber(arithTrig[i + 1]) == 0) {
				j = i;
				i = abs((int)strlen(arithTrig));
				while (i > j) {
					arithTrig[i] = arithTrig[i - 1];
					i--;
				}
				arithTrig[i] = '1';
				i = abs((int)strlen(arithTrig));
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != '1'&&arithTrig[i - 1] != 'p'&& arithTrig[i] == 'i'&& verifyLetter(arithTrig[i + 1]) == 0 && verifyNumber(arithTrig[i + 1]) == 0) {
				needOne = 1;
			}
		}
	}
	needAst = 1;
	int mark = 0, mark1 = 0, napier = 0, n = 0, m = 0;
	float isFunc = 0;
	char functionP[DIM] = "";
	while (needAst == 1) {
		valRenamedVar = 0;
		for (i = mark1; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'e'&& verifyLetter(arithTrig[i + 1]) && needAst == 1) {
				if (arithTrig[i - 1] == 'D' || arithTrig[i - 1] == 'b') {
					while (verifyLetter(arithTrig[i])) {
						i--;
					}
					i++;
					int lo = 0;
					char func[DIM] = "";
					while (verifyLetter(arithTrig[i]) && arithTrig[i] != 'b'&&arithTrig[i] != 'D') {
						func[lo] = arithTrig[i];
						lo++; i++;
					}
					func[lo] = arithTrig[i]; lo++;
					func[lo] = arithTrig[i]; lo++;
					func[lo] = '?'; lo++;
					func[lo] = '\0';
					if (functionProcessor(func, 0, 0, 0) == 0.5) {
						i = i + 2;
					}
				}
			}
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'e'&& verifyLetter(arithTrig[i + 1]) && needAst == 1) {
				mark1 = i + 1;
				j = i;
				i = abs((int)strlen(arithTrig));
				int p = j;
				while (verifyLetter(arithTrig[p])) {
					p--;
				}
				if (j != p) {
					p++;
					char function[DIM] = "";
					int y = 0;
					while (verifyLetter(arithTrig[p]) && p < abs((int)strlen(arithTrig))) {
						function[y] = arithTrig[p];
						p++; y++;
					}
					function[y] = '?'; function[y + 1] = '\0';
					isFunc = (float)functionProcessor(function, 0, 0, 0);
					if (isFunc == 0.5) {
						break;
					}
					else {
						function[y] = '\0';
						valRenamedVar = 0;
						n = 0, m = 0;
						m = 0;
						for (n = 0; function[n] != '\0'&&n < abs((int)strlen(function)); n++) {
							while (function[n] != 'e'&&function[n] != '\0'&&n < abs((int)strlen(function))) {
								functionP[m] = function[n];
								n++; m++;
							}
							functionP[m] = '\0';
							valRenamedVar = 0;
							variableRenamer(functionP);
							if (valRenamedVar == 1) {
								isFunc = 0;
								break;
							}
							else {
								functionP[m] = function[n];
								napier = 1;
								m++;
							}
						}
						if (valRenamedVar == 1) {
							isFunc = 0;
						}
					}
				}
				if (isFunc == 0 && napier == 0) {
					int l = 0;
					for (l = 0; l < abs((int)strlen(arithTrig)); l++) {
						if (arithTrig[l] == 'r'&&arithTrig[l + 1] == 'e'&&arithTrig[l + 2] == 's') {
							l = 0; break;
						}
					}
					if (l != 0) {
						while (i > j) {
							arithTrig[i] = arithTrig[i - 1];
							i--;
						}
						arithTrig[i] = '*';
						j = j + 2;
						i = abs((int)strlen(arithTrig));
						while (i > j) {
							arithTrig[i] = arithTrig[i - 1];
							i--;
						}
						arithTrig[i] = '*';
					}
				}
				if (napier == 1) {
					n = 0; m = 0;
					for (n = 0; arithTrig[n] != '\0'; n++) {
						if (arithTrig[n] == functionP[m]) {
							m = 0;
							while (arithTrig[n] == functionP[m]) {
								n++; m++;
							}
							int z = abs((int)strlen(arithTrig)), nj = n, nc = 0;
							nc = z;
							if (arithTrig[nj + 1] != '(') {
								if ((arithTrig[nj - 3] == 'l'&&arithTrig[nj - 2] == 'o'&&arithTrig[nj - 1] == 'g'&&arithTrig[nj] == 'b') == false && (arithTrig[nj - 2] == 'r'&&arithTrig[nj - 1] == 't'&&arithTrig[nj] == 'D') == false) {
									while (nj < nc) {
										arithTrig[nc] = arithTrig[nc - 1];
										nc--;
									}
									arithTrig[nj] = '*';
									z = abs((int)strlen(arithTrig));
									nj = n + 2;
									if (arithTrig[nj - 1] != '(') {
										while (nj < z) {
											arithTrig[z] = arithTrig[z - 1];
											z--;
										}
										if (arithTrig[z] != '\0') {
											arithTrig[z] = '*';
										}
									}
								}
							}
						}
					}
				}
			}
		}
		for (i = mark; arithTrig[i] != '\0'; i++) {
			needAst = 0;
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'e'&& verifyLetter(arithTrig[i + 1])) {
				if (arithTrig[i - 1] == 'D' || arithTrig[i - 1] == 'b') {
					while (verifyLetter(arithTrig[i])) {
						i--;
					}
					i++;
					int lo = 0;
					char func[DIM] = "";
					while (verifyLetter(arithTrig[i]) && arithTrig[i] != 'b'&&arithTrig[i] != 'D') {
						func[lo] = arithTrig[i];
						lo++; i++;
					}
					func[lo] = arithTrig[i]; lo++;
					func[lo] = arithTrig[i]; lo++;
					func[lo] = '?'; lo++;
					func[lo] = '\0';
					if (functionProcessor(func, 0, 0, 0) == 0.5) {
						i = i + 2;
					}
				}
			}
			if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'e'&&verifyLetter(arithTrig[i + 1])) {
				mark = i + 1;
				needAst = 1;
			}
		}
	}
	renamer(arithTrig);
	for (i = 0; expressionF[i] != '\0'; i++) {
		arithTrig[i] = expressionF[i];
	}
	arithTrig[i] = '\0';
	char paTrig[DIM] = "";
	int u = 0;
	for (u = 0; arithTrig[u] != '\0'; u++) {
		paTrig[u] = arithTrig[u];
	}
	paTrig[u] = '\0';
	u = 0;
	for (u; paTrig[u] != '\0'; u++) {
		if (verifyLetter(paTrig[u]) == 0) {
			while (verifyLetter(paTrig[u]) == 0 && paTrig[u] != '\0') {
				u++;
			}
		}
		if (verifyLetter(paTrig[u]) && firstLetterVariable(paTrig[u]) == 0) {
			while (verifyLetter(paTrig[u])) {
				u++;
			}
		}
		if (firstLetterVariable(paTrig[u]) && firstLetterVariable(paTrig[u - 1]) == 0 && paTrig[u + 1] != 'i') {
			u++;
			while (verifyLetter(paTrig[u])) {
				u++;
			}
			if (paTrig[u] != '\\'&&paTrig[u] != '*'&&paTrig[u] != '+'&&paTrig[u] != '-'&&paTrig[u] != '/'&&paTrig[u] != '^'&&paTrig[u] != '!'&&paTrig[u] != ')') {
				double check = 0;
				if (verifyLetter(paTrig[u - 1])) {
					int z = u - 1, v = 0;
					char toVal[DIM] = "";
					while (verifyLetter(paTrig[z])) {
						z--;
					}
					z++;
					while (verifyLetter(paTrig[z])) {
						toVal[v] = paTrig[z];
						z++; v++;
					}
					toVal[v] = '?'; toVal[v + 1] = '\0';
					check = functionProcessor(toVal, 0, 0, 0);
				}
				if (check != 0.5) {
					arithTrig[u] = '*';
					for (u; paTrig[u] != '\0'; u++) {
						arithTrig[u + 1] = paTrig[u];
					}
					arithTrig[u + 1] = '\0';
					u = 0;
					for (u = 0; arithTrig[u] != '\0'; u++) {
						paTrig[u] = arithTrig[u];
					}
					paTrig[u] = '\0';
					u = 0;
				}
			}
		}
	}
	needAst = 1;
	while (needAst == 1) {
		needAst = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i - 1] != '(' && arithTrig[i] == 'i'&&verifyLetter(arithTrig[i + 1]) && arithTrig[i + 1] != 'D'&& arithTrig[i + 1] != 'b') {
				j = i + 1;
				i = abs((int)strlen(arithTrig));
				int comp = 0;
				if (verifyNumber(arithTrig[j - 2]) == 0) {
					i++;
					comp = 1;
				}
				if (comp == 0) {
					while (i > j) {
						arithTrig[i] = arithTrig[i - 1];
						i--;
					}
					arithTrig[i] = '*';
				}
				else {
					while (i > j) {
						arithTrig[i] = arithTrig[i - 2];
						i--;
					}
					arithTrig[i] = '1'; arithTrig[i + 1] = '*';
				}
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i - 1] != '('&&arithTrig[i] == 'i'&&verifyLetter(arithTrig[i + 1]) && arithTrig[i + 1] != 'D'&& arithTrig[i + 1] != 'b') {
				needAst = 1;
			}
		}
	}
	needAst = 1;
	replaceTimes = 1;
	while (needAst == 1) {
		needAst = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (isContained("_i", arithTrig)) {
				replace("_i", "_1i", arithTrig);
				sprintf(arithTrig, "%s", expressionF);
				i = strEnd;
			}
			else {
				if ((verifyLetter(arithTrig[i - 1]) || verifyNumber(arithTrig[i - 1])) && arithTrig[i - 1] != 'p' && arithTrig[i - 1] != 'D'&& arithTrig[i - 1] != 'b'&& arithTrig[i] == 'i'&&arithTrig[i - 1] != '1'&&arithTrig[i - 1] != '('&&verifyLetter(arithTrig[i + 1]) == 0) {
					j = i;
					i = abs((int)strlen(arithTrig)) + 1;
					while (i > j) {
						arithTrig[i] = arithTrig[i - 2];
						i--;
					}
					arithTrig[i] = '*'; arithTrig[i + 1] = '1';
					i = abs((int)strlen(arithTrig));
				}
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if ((verifyLetter(arithTrig[i - 1]) || verifyNumber(arithTrig[i - 1])) && arithTrig[i - 1] != 'p' && arithTrig[i - 1] != 'D'&& arithTrig[i - 1] != 'b'&& arithTrig[i] == 'i'&&arithTrig[i - 1] != '1'&&arithTrig[i - 1] != '('&&verifyLetter(arithTrig[i + 1]) == 0) {
				needAst = 1;
			}
		}
	}
	replaceTimes = 0;
	needAst = 1;
	while (needAst == 1) {
		needAst = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (arithTrig[i - 1] == ')' && arithTrig[i] == 'i'&&verifyLetter(arithTrig[i + 1]) == 0) {
				j = i;
				i = abs((int)strlen(arithTrig)) + 1;
				while (i > j) {
					arithTrig[i] = arithTrig[i - 2];
					i--;
				}
				arithTrig[i] = '*'; arithTrig[i + 1] = '1';
				i = abs((int)strlen(arithTrig));
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (arithTrig[i - 1] == ')' && arithTrig[i] == 'i'&&verifyLetter(arithTrig[i + 1]) == 0) {
				needAst = 1;
			}
		}
	}
	needAst = 1;
	while (needAst == 1) {
		needAst = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i'&&arithTrig[i + 1] == '(') {
				j = i + 1;
				i = abs((int)strlen(arithTrig));
				int comp = 0;
				if (verifyNumber(arithTrig[j - 2]) == 0) {
					i++;
					comp = 1;
				}
				if (comp == 0) {
					while (i > j) {
						arithTrig[i] = arithTrig[i - 1];
						i--;
					}
					arithTrig[i] = '*';
				}
				else {
					while (i > j) {
						arithTrig[i] = arithTrig[i - 2];
						i--;
					}
					arithTrig[i] = '1'; arithTrig[i + 1] = '*';
				}
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i'&&arithTrig[i + 1] == '(') {
				needAst = 1;
			}
		}
	}
	renamer(arithTrig);
	for (i = 0; expressionF[i] != '\0'; i++) {
		arithTrig[i] = expressionF[i];
	}
	arithTrig[i] = '\0';
	needAst = 1;
	while (needAst == 1) {
		needAst = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) == 0 && verifyNumber(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i'&& arithTrig[i + 1] != '1' && (verifyLetter(arithTrig[i + 1]) || verifyNumber(arithTrig[i + 1]))) {
				j = i + 1;
				i = abs((int)strlen(arithTrig)) + 1;
				while (i > j) {
					arithTrig[i] = arithTrig[i - 2];
					i--;
				}
				arithTrig[i] = '1'; arithTrig[i + 1] = '*';
			}
		}
		needAst = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (verifyLetter(arithTrig[i - 1]) == 0 && verifyNumber(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i'&& arithTrig[i + 1] != '1' && (verifyLetter(arithTrig[i + 1]) || verifyNumber(arithTrig[i + 1]))) {
				needAst = 1;
			}
		}
	}
	needOne = 1;
	while (needOne == 1) {
		needOne = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if ((verifyLetter(arithTrig[i - 1]) == 0 || arithTrig[i - 1] == 'D' || arithTrig[i - 1] == 'b') && verifyNumber(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i'&& verifyNumber(arithTrig[i + 1]) == 0 && (verifyLetter(arithTrig[i + 1]) == 0 || arithTrig[i + 1] == 'D' || arithTrig[i + 1] == 'b')) {
				j = i;
				i = abs((int)strlen(arithTrig));
				while (i > j) {
					arithTrig[i] = arithTrig[i - 1];
					i--;
				}
				arithTrig[i] = '1';
				i = abs((int)strlen(arithTrig));
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if ((verifyLetter(arithTrig[i - 1]) == 0 || arithTrig[i - 1] == 'D' || arithTrig[i - 1] == 'b') && verifyNumber(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i'&& verifyNumber(arithTrig[i + 1]) == 0 && (verifyLetter(arithTrig[i + 1]) == 0 || arithTrig[i + 1] == 'D' || arithTrig[i + 1] == 'b')) {
				needOne = 1;
			}
		}
	}
	needAst = 1;
	while (needAst == 1) {
		needAst = 0;
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (arithTrig[i - 1] == '1' && arithTrig[i] == 'i' && (verifyLetter(arithTrig[i + 1]) && arithTrig[i + 1] != 'D'&&arithTrig[i + 1] != 'b' || verifyNumber(arithTrig[i + 1]))) {
				j = i + 1;
				i = abs((int)strlen(arithTrig));
				while (i > j) {
					arithTrig[i] = arithTrig[i - 1];
					i--;
				}
				arithTrig[i] = '*';
			}
		}
		for (i = 0; arithTrig[i] != '\0'; i++) {
			if (arithTrig[i - 1] == '1' && arithTrig[i] == 'i' && (verifyLetter(arithTrig[i + 1]) && arithTrig[i + 1] != 'D'&&arithTrig[i + 1] != 'b' || verifyNumber(arithTrig[i + 1]))) {
				needAst = 1;
			}
		}
	}
	s = 0;
	for (s = 0; arithTrig[s] != '\0'; s++) {
		paTrig[s] = arithTrig[s];
	}
	paTrig[s] = '\0';
	s = 0;
	for (s; paTrig[s] != '\0'; s++) {
		if ((paTrig[s] == 'e'&&paTrig[s + 1] != 'b' || paTrig[s] == 'i'&&paTrig[s - 1] == 'p'&&paTrig[s + 1] != 'b' || paTrig[s] == '1' || paTrig[s] == '2' || paTrig[s] == '3' || paTrig[s] == '4' || paTrig[s] == '5' || paTrig[s] == '6' || paTrig[s] == '7' || paTrig[s] == '8' || paTrig[s] == '9' || paTrig[s] == '0' || paTrig[s] == '.') && (paTrig[s + 1] == '#' || paTrig[s + 1] == 'w' || paTrig[s + 1] == 'y' || paTrig[s + 1] == 'u' || paTrig[s + 1] == 'o' || paTrig[s + 1] == 'p' || paTrig[s + 1] == 'f' || paTrig[s + 1] == 'h' || paTrig[s + 1] == 'j' || paTrig[s + 1] == 'k' || paTrig[s + 1] == 'z' || paTrig[s + 1] == 'v' || paTrig[s + 1] == 'm' || paTrig[s + 1] == 'Q' || paTrig[s + 1] == 'W' || paTrig[s + 1] == 'R' || paTrig[s + 1] == 'T' || paTrig[s + 1] == 'Y' || paTrig[s + 1] == 'U' || paTrig[s + 1] == 'I' || paTrig[s + 1] == 'S' || paTrig[s + 1] == 'G' || paTrig[s + 1] == 'J' || paTrig[s + 1] == 'K' || paTrig[s + 1] == 'L' || paTrig[s + 1] == 'Z' || paTrig[s + 1] == 'X' || paTrig[s + 1] == 'V' || paTrig[s + 1] == 'N' || paTrig[s + 1] == 'M')) {
			s++;
			arithTrig[s] = '*';
			for (s; paTrig[s] != '\0'; s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; arithTrig[s] != '\0'; s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; paTrig[s] != '\0'; s++) {
		if ((paTrig[s + 1] == 'e'&&paTrig[s] != 'b'&&paTrig[s] != 'c' && (paTrig[s] == 'l'&&paTrig[s - 1] == 'r'&&paTrig[s - 2] == 't'&&paTrig[s - 3] == 's'&&paTrig[s + 2] == 'n') == false && (paTrig[s] == 'v'&&paTrig[s - 1] == 'l'&&paTrig[s - 2] == 'o'&&paTrig[s - 3] == 's'&&paTrig[s + 2] == 'r') == false || paTrig[s + 1] == 'p'&&paTrig[s + 2] == 'i'&&paTrig[s] != 'b' || paTrig[s + 1] == '1' || paTrig[s + 1] == '2' || paTrig[s + 1] == '3' || paTrig[s + 1] == '4' || paTrig[s + 1] == '5' || paTrig[s + 1] == '6' || paTrig[s + 1] == '7' || paTrig[s + 1] == '8' || paTrig[s + 1] == '9' || paTrig[s + 1] == '0' || paTrig[s + 1] == '.') && (paTrig[s] == 'q' || paTrig[s] == 'w' || paTrig[s] == 't' || paTrig[s] == 'y' || paTrig[s] == 'u' || paTrig[s] == 'o' || paTrig[s] == 'p' || paTrig[s] == 'a' || paTrig[s] == 'f' || paTrig[s] == 'h' || paTrig[s] == 'j' || paTrig[s] == 'k' || paTrig[s] == 'l' || paTrig[s] == 'z' || paTrig[s] == 'c' || paTrig[s] == 'v' || paTrig[s] == 'n' || paTrig[s] == 'm' || paTrig[s] == 'Q' || paTrig[s] == 'W' || paTrig[s] == 'R' || paTrig[s] == 'T' || paTrig[s] == 'Y' || paTrig[s] == 'U' || paTrig[s] == 'I' || paTrig[s] == 'S' || paTrig[s] == 'G' || paTrig[s] == 'J' || paTrig[s] == 'K' || paTrig[s] == 'L' || paTrig[s] == 'Z' || paTrig[s] == 'X' || paTrig[s] == 'V' || paTrig[s] == 'N' || paTrig[s] == 'M')) {
			s++;
			arithTrig[s] = '*';
			for (s; paTrig[s] != '\0'; s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; arithTrig[s] != '\0'; s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	if (isContained("ans", arithTrig)) {
		replace("ans", "res", arithTrig);
		sprintf(arithTrig, expressionF);
	}
	for (i = 0; arithTrig[i] != '\0'; i++) {
		if (verifyLetter(arithTrig[i])) {
			letterScan[i] = arithTrig[i];
		}
		else {
			letterScan[i] = ' ';
		}
	}
	letterScan[i] = '\0';
	i = 0;
	j = 0;

	int h = 0;
	while (h < abs((int)strlen(arithTrig))) {
		if (arithTrig[h] == '[' || arithTrig[h] == '{') {
			arithTrig[h] = '(';
		}
		if (arithTrig[h] == ']' || arithTrig[h] == '}') {
			arithTrig[h] = ')';
		}
		h++;
	}
	char varCandidate[DIM] = "";
	char finalReplacement[DIM] = "";
	char readLetter[DIM] = "";
	int v = 0;
	int varState = 0;

	for (i = 0; letterScan[i] != '\0'; i++) {
		readLetter[v] = letterScan[i];
	}
	readLetter[v] = '\0';
	varState = 0;
	j = 0;
	for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
		if (verifyLetter(letterScan[i])) {
			j = 0;
			while (verifyLetter(letterScan[i]) && i < abs((int)strlen(arithTrig))) {
				varCandidate[j] = letterScan[i];
				i++; j++;
			}
			varCandidate[j] = '\0';
		}
		char replaceVariable[DIM] = "";
		if (abs((int)strlen(varCandidate) != 0)) {
			sprintf(finalReplacement, "(%s)", varCandidate);
			if (isContained("res", arithTrig)) {
				if (isContained("^_res", arithTrig) == (boolean)false && isContained("res", arithTrig)) {
					if (arithTrig[strEnd] != 't') {
						replace("res", "(\\\\\\\\)", arithTrig);
						replace("\\\\\\\\", "res", expressionF);
						sprintf(arithTrig, "%s", expressionF);
						char isDuplicatedParent[DIM] = "";
						sprintf(finalReplacement, "(res)");
						sprintf(isDuplicatedParent, "(%s)", finalReplacement);
						if (isContained(isDuplicatedParent, arithTrig)) {
							replace(isDuplicatedParent, finalReplacement, arithTrig);
							sprintf(arithTrig, "%s", expressionF);
						}
					}
				}
				if (isContained("^_res", arithTrig)) {
					if (arithTrig[strEnd] != 't') {
						replace("^_res", "^(\\\\\\\\)", arithTrig);
						replace("\\\\\\\\", "_res", expressionF);
						sprintf(arithTrig, "%s", expressionF);
						char isDuplicatedParent[DIM] = "";
						sprintf(finalReplacement, "(_res)");
						sprintf(isDuplicatedParent, "(_%s)", finalReplacement);
						if (isContained(isDuplicatedParent, arithTrig)) {
							replace(isDuplicatedParent, finalReplacement, arithTrig);
							sprintf(arithTrig, "%s", expressionF);
						}
					}
				}
			}
		}
	}
	if (isContained("#", arithTrig)) {
		if (isContained("^_#", arithTrig) == (boolean)false && isContained("#", arithTrig)) {
			int i = strStart + 1, v = 1;
			char result_name[DIM] = "";
			result_name[0] = arithTrig[strStart];
			while (verifyNumber(arithTrig[i])) {
				result_name[v] = arithTrig[i];
				v++; i++;
				if (i > strStart + 1) {
					if (arithTrig[i] == '#') {
						break;
					}
				}
			}
			result_name[v] = '\0';
			char replacement[DIM] = "";
			sprintf(finalReplacement, "(%s)", result_name);
			sprintf(replacement, "(////////)");
			replace(result_name, replacement, arithTrig);
			replace("////////", result_name, expressionF);
			sprintf(arithTrig, "%s", expressionF);
			char isDuplicatedParent[DIM] = "";
			sprintf(isDuplicatedParent, "(%s)", finalReplacement);
			if (isContained(isDuplicatedParent, arithTrig)) {
				replace(isDuplicatedParent, finalReplacement, arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
		}
		if (isContained("^_#", arithTrig)) {
			int i = strStart + 3, v = 0;
			char result_name[DIM] = "";
			result_name[0] = arithTrig[strStart + 2];
			v = 1;
			while (verifyNumber(arithTrig[i])) {
				result_name[v] = arithTrig[i];
				v++; i++;
				if (i > strStart + 1) {
					if (arithTrig[i] == '#') {
						break;
					}
				}
			}
			result_name[v] = '\0';
			char replacement[DIM] = "";
			sprintf(finalReplacement, "(_%s)", result_name);
			sprintf(replacement, "^(_////////)");
			char toReplace[DIM] = "";
			sprintf(toReplace, "^_%s", result_name);
			replace(toReplace, replacement, arithTrig);
			replace("////////", result_name, expressionF);
			sprintf(arithTrig, "%s", expressionF);
			char isDuplicatedParent[DIM] = "";
			sprintf(isDuplicatedParent, "(_%s)", finalReplacement);
			if (isContained(isDuplicatedParent, arithTrig)) {
				replace(isDuplicatedParent, finalReplacement, arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
		}
	}
	if (isContained("B", arithTrig)) {
		if (verifyNumerical(arithTrig[strStart - 1]) == (boolean)false && verifyLetter(arithTrig[strStart - 1]) == (boolean)false) {
			if (isContained("^_B", arithTrig) == (boolean)false && isContained("B", arithTrig)) {
				int i = strStart, v = 0;
				char result_name[DIM] = "";
				while ((verifyNumber(arithTrig[i]) || verifyLetter(arithTrig[i]) || (arithTrig[i] == '-' && (arithTrig[i - 1] == 'B' || arithTrig[i - 1] == 'O' || arithTrig[i - 1] == 'H')) || arithTrig[i] == '.') && firstLetterFunction(arithTrig[i]) == false) {
					result_name[v] = arithTrig[i];
					v++; i++;
					if (i > strStart + 1) {
						if (arithTrig[i] == 'B') {
							break;
						}
					}
				}
				result_name[v] = '\0';
				char replacement[DIM] = "";
				sprintf(finalReplacement, "(%s)", result_name);
				sprintf(replacement, "(////////)");
				replace(result_name, replacement, arithTrig);
				replace("////////", result_name, expressionF);
				sprintf(arithTrig, "%s", expressionF);
				char isDuplicatedParent[DIM] = "";
				sprintf(isDuplicatedParent, "(%s)", finalReplacement);
				if (isContained(isDuplicatedParent, arithTrig)) {
					replace(isDuplicatedParent, finalReplacement, arithTrig);
					sprintf(arithTrig, "%s", expressionF);
				}
			}
			if (isContained("^_B", arithTrig)) {
				int i = strStart + 2, v = 0;
				char result_name[DIM] = "";
				while ((verifyNumber(arithTrig[i]) || verifyLetter(arithTrig[i]) || (arithTrig[i] == '-' && (arithTrig[i - 1] == 'B' || arithTrig[i - 1] == 'O' || arithTrig[i - 1] == 'H')) || arithTrig[i] == '.') && firstLetterFunction(arithTrig[i]) == false) {
					result_name[v] = arithTrig[i];
					v++; i++;
					if (i > strStart + 1) {
						if (arithTrig[i] == 'B') {
							break;
						}
					}
				}
				result_name[v] = '\0';
				char replacement[DIM] = "";
				char toReplace[DIM] = "";
				sprintf(toReplace, "^_%s", result_name);
				sprintf(finalReplacement, "(_%s)", result_name);
				sprintf(replacement, "^(_////////)");
				replace(toReplace, replacement, arithTrig);
				replace("////////", result_name, expressionF);
				sprintf(arithTrig, "%s", expressionF);
				char isDuplicatedParent[DIM] = "";
				sprintf(isDuplicatedParent, "(_%s)", finalReplacement);
				if (isContained(isDuplicatedParent, arithTrig)) {
					replace(isDuplicatedParent, finalReplacement, arithTrig);
					sprintf(arithTrig, "%s", expressionF);
				}
			}
		}
	}
	if (isContained("O", arithTrig)) {
		if (isContained("^_O", arithTrig) == (boolean)false && isContained("O", arithTrig)) {
			int i = strStart, v = 0;
			char result_name[DIM] = "";
			while ((verifyNumber(arithTrig[i]) || verifyLetter(arithTrig[i]) || (arithTrig[i] == '-' && (arithTrig[i - 1] == 'B' || arithTrig[i - 1] == 'O' || arithTrig[i - 1] == 'H')) || arithTrig[i] == '.') && firstLetterFunction(arithTrig[i]) == false) {
				result_name[v] = arithTrig[i];
				v++; i++;
				if (i > strStart + 1) {
					if (arithTrig[i] == 'O') {
						break;
					}
				}
			}
			result_name[v] = '\0';
			char replacement[DIM] = "";
			sprintf(finalReplacement, "(%s)", result_name);
			sprintf(replacement, "(////////)");
			replace(result_name, replacement, arithTrig);
			replace("////////", result_name, expressionF);
			sprintf(arithTrig, "%s", expressionF);
			char isDuplicatedParent[DIM] = "";
			sprintf(isDuplicatedParent, "(%s)", finalReplacement);
			if (isContained(isDuplicatedParent, arithTrig)) {
				replace(isDuplicatedParent, finalReplacement, arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
		}
		if (isContained("^_O", arithTrig)) {
			int i = strStart + 2, v = 0;
			char result_name[DIM] = "";
			while ((verifyNumber(arithTrig[i]) || verifyLetter(arithTrig[i]) || (arithTrig[i] == '-' && (arithTrig[i - 1] == 'B' || arithTrig[i - 1] == 'O' || arithTrig[i - 1] == 'H')) || arithTrig[i] == '.') && firstLetterFunction(arithTrig[i]) == false) {
				result_name[v] = arithTrig[i];
				v++; i++;
				if (i > strStart + 1) {
					if (arithTrig[i] == 'O') {
						break;
					}
				}
			}
			result_name[v] = '\0';
			char replacement[DIM] = "";
			char toReplace[DIM] = "";
			sprintf(toReplace, "^_%s", result_name);
			sprintf(finalReplacement, "(_%s)", result_name);
			sprintf(replacement, "^(_////////)");
			replace(toReplace, replacement, arithTrig);
			replace("////////", result_name, expressionF);
			sprintf(arithTrig, "%s", expressionF);
			char isDuplicatedParent[DIM] = "";
			sprintf(isDuplicatedParent, "(_%s)", finalReplacement);
			if (isContained(isDuplicatedParent, arithTrig)) {
				replace(isDuplicatedParent, finalReplacement, arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
		}
	}
	if (isContained("H", arithTrig)) {
		if (isContained("^_H", arithTrig) == (boolean)false && isContained("H", arithTrig)) {
			int i = strStart, v = 0;
			char result_name[DIM] = "";
			while ((verifyNumber(arithTrig[i]) || verifyLetter(arithTrig[i]) || (arithTrig[i] == '-' && (arithTrig[i - 1] == 'B' || arithTrig[i - 1] == 'O' || arithTrig[i - 1] == 'H')) || arithTrig[i] == '.') && firstLetterFunction(arithTrig[i]) == false) {
				result_name[v] = arithTrig[i];
				v++; i++;
				if (i > strStart + 1) {
					if (arithTrig[i] == 'H') {
						break;
					}
				}
			}
			result_name[v] = '\0';
			char replacement[DIM] = "";
			sprintf(finalReplacement, "(%s)", result_name);
			sprintf(replacement, "(////////)");
			replace(result_name, replacement, arithTrig);
			replace("////////", result_name, expressionF);
			sprintf(arithTrig, "%s", expressionF);
			char isDuplicatedParent[DIM] = "";
			sprintf(isDuplicatedParent, "(%s)", finalReplacement);
			if (isContained(isDuplicatedParent, arithTrig)) {
				replace(isDuplicatedParent, finalReplacement, arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
		}
		if (isContained("^_H", arithTrig)) {
			int i = strStart + 2, v = 0;
			char result_name[DIM] = "";
			while ((verifyNumber(arithTrig[i]) || verifyLetter(arithTrig[i]) || (arithTrig[i] == '-' && (arithTrig[i - 1] == 'B' || arithTrig[i - 1] == 'O' || arithTrig[i - 1] == 'H')) || arithTrig[i] == '.') && firstLetterFunction(arithTrig[i]) == false) {
				result_name[v] = arithTrig[i];
				v++; i++;
				if (i > strStart + 1) {
					if (arithTrig[i] == 'H') {
						break;
					}
				}
			}
			result_name[v] = '\0';
			char replacement[DIM] = "";
			char toReplace[DIM] = "";
			sprintf(toReplace, "^_%s", result_name);
			sprintf(finalReplacement, "(_%s)", result_name);
			sprintf(replacement, "^(_////////)");
			replace(toReplace, replacement, arithTrig);
			replace("////////", result_name, expressionF);
			sprintf(arithTrig, "%s", expressionF);
			char isDuplicatedParent[DIM] = "";
			sprintf(isDuplicatedParent, "(_%s)", finalReplacement);
			if (isContained(isDuplicatedParent, arithTrig)) {
				replace(isDuplicatedParent, finalReplacement, arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
		}
	}
	if (isContained("P", arithTrig)) {
		if (isContained("^_P", arithTrig) == (boolean)false && isContained("P", arithTrig)) {
			int i = strStart, v = 0;
			char result_name[DIM] = "P", prefixes[DIM] = "PY,PZ,PE,PP,PT,PG,PM,Pk,Ph,Pda,Pd,Pc,Pm,Pu,Pn,Pp,Pf,Pa,Pz,Py,", toTest[DIM] = "P";
			while (verifyLetter(arithTrig[i]) && isContained(toTest, prefixes)) {
				result_name[v] = arithTrig[i];
				v++; i++;
				sprintf(toTest, "%s%c", toTest, arithTrig[i]);
			}
			result_name[v] = '\0';
			char replacement[DIM] = "";
			sprintf(finalReplacement, "(%s)", result_name);
			sprintf(replacement, "(////////)");
			replace(result_name, replacement, arithTrig);
			replace("////////", result_name, expressionF);
			sprintf(arithTrig, "%s", expressionF);
			char isDuplicatedParent[DIM] = "";
			sprintf(isDuplicatedParent, "(%s)", finalReplacement);
			if (isContained(isDuplicatedParent, arithTrig)) {
				replace(isDuplicatedParent, finalReplacement, arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
		}
		if (isContained("^_P", arithTrig)) {
			int i = strStart + 2, v = 0;
			char result_name[DIM] = "P", prefixes[DIM] = "PY,PZ,PE,PP,PT,PG,PM,Pk,Ph,Pda,Pd,Pc,Pm,Pu,Pn,Pp,Pf,Pa,Pz,Py,", toTest[DIM] = "P";
			while (verifyLetter(arithTrig[i]) && isContained(toTest, prefixes)) {
				result_name[v] = arithTrig[i];
				v++; i++;
				sprintf(toTest, "%s%c", toTest, arithTrig[i]);
			}
			result_name[v] = '\0';
			char replacement[DIM] = "";
			char toReplace[DIM] = "";
			sprintf(toReplace, "^_%s", result_name);
			sprintf(finalReplacement, "(_%s)", result_name);
			sprintf(replacement, "^(_////////)");
			replace(toReplace, replacement, arithTrig);
			replace("////////", result_name, expressionF);
			sprintf(arithTrig, "%s", expressionF);
			char isDuplicatedParent[DIM] = "";
			sprintf(isDuplicatedParent, "(_%s)", finalReplacement);
			if (isContained(isDuplicatedParent, arithTrig)) {
				replace(isDuplicatedParent, finalReplacement, arithTrig);
				sprintf(arithTrig, "%s", expressionF);
			}
		}
	}
	char newArithTrig[DIM] = "";
	char variableCheck[DIM] = "";
	s = 0;
	int y = 0, z = 0;
	for (i = 0; arithTrig[i] != '\0'; i++) {
		if (firstLetterVariable(arithTrig[i]) && (i == 0 || verifyLetter(arithTrig[i - 1]) == (boolean)false) && (arithTrig[i] == 'i'&&arithTrig[i - 1] == 'p') == false) {
			s = 0;
			while (letterVariables(arithTrig[i]) && arithTrig[i] != '\0') {
				variableCheck[s] = arithTrig[i];
				s++;
				i++;
			}
			variableCheck[s] = '\0';
			if (isVariable(variableCheck)) {
				if (arithTrig[i - strlen(variableCheck) - 1] != '(' || arithTrig[i] != ')') {
					sprintf(newArithTrig, "%s(%s)", newArithTrig, variableCheck);
				}
				else {
					sprintf(newArithTrig, "%s%s)", newArithTrig, variableCheck);
					i++; y++;
				}
				y = abs((int)strlen(newArithTrig));
				if (letterVariables(arithTrig[i]) == (boolean)false) {
					while (firstLetterVariable(arithTrig[i]) == (boolean)false && arithTrig[i] != '\0') {
						newArithTrig[y] = arithTrig[i];
						y++; i++;
					}
					newArithTrig[y] = '\0';
					i--;
				}
			}
			else {
				sprintf(newArithTrig, "%s%s", newArithTrig, variableCheck);
				y = abs((int)strlen(newArithTrig));
				while (firstLetterVariable(arithTrig[i]) == (boolean)false && arithTrig[i] != '\0') {
					newArithTrig[y] = arithTrig[i];
					y++; i++;
				}
				newArithTrig[y] = '\0';
				i--;
			}
		}
		else {
			newArithTrig[y] = arithTrig[i];
			y++;
		}
	}
	newArithTrig[y] = '\0';
	sprintf(arithTrig, newArithTrig);
	renamer(arithTrig);
	sprintf(arithTrig, expressionF);
	while (isContained("^_(", arithTrig) && validVar == 1) {
		validVar = 0;
		if (isContained("^_(", arithTrig)) {
			int i = strEnd, v = 0;
			char check_variable[DIM] = "";
			while (letterVariables(arithTrig[i]) && arithTrig[i] != '\0') {
				check_variable[v] = arithTrig[i];
				v++; i++;
			}
			check_variable[v] = '\0';
			if (isVariable(check_variable) && arithTrig[i] == ')') {
				char toReplace[DIM] = "";
				sprintf(toReplace, "^_(%s)", check_variable);
				char replacement[DIM] = "";
				sprintf(replacement, "^(_%s)", check_variable);
				replace(toReplace, replacement, arithTrig);
				sprintf(arithTrig, expressionF);
			}
		}
	}
}

void openTxt() {
	FILE *open = NULL;
	open = fopen(expressionF, "r");
	char openFile[DIM] = "";
	if (open != NULL) {
		fclose(open);
		sprintf(openFile, "notepad.exe %s", expressionF);
		system(openFile);
	}
}

boolean isVariable(char variable[DIM]) {
	renamer(variable);
	char variableF[DIM] = "";
	sprintf(variableF, expressionF);
	processVariable(variableF);
	if (validVar == 1) {
		return true;
	}
	return false;
}

void leftClick()
{
	INPUT    Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}
void cls()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	if (!FillConsoleOutputCharacter(hConsole,
		(TCHAR) ' ',
		dwConSize,
		coordScreen,
		&cCharsWritten))
	{
		return;
	}
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}
	if (!FillConsoleOutputAttribute(hConsole,
		csbi.wAttributes,
		dwConSize,
		coordScreen,
		&cCharsWritten))
	{
		return;
	}
	SetConsoleCursorPosition(hConsole, coordScreen);
}

void addATCPath() {
	FILE *open = NULL, *pathReader = NULL;
	char contents[DIM] = "", atcName[DIM] = "\\Advanced Trigonometry Calculator", atcPAth[DIM] = "";
	int w = 0, i = 0, s = 0, j = 0, tested = 0;
	open = fopen("atc_path.txt", "r");
	FILE *test = NULL;
	char testPath[DIM] = "";
	if (open != NULL) {
		fgets(atcPath, DIM, open);
		sprintf(testPath, "%s\\License.txt", atcPath);
		test = fopen(testPath, "r");
		tested = 1;
	}
	if (open == NULL || (test == NULL && open != NULL && tested == 1)) {
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"echo %PATH% > PATH_paths.txt\""), NULL, SW_SHOW);
		Sleep(200);
		pathReader = fopen("PATH_paths.txt", "r");
		if (pathReader != NULL) {
			for (w = 0; (contents[w] = fgetc(pathReader)) != EOF; w++);
			contents[w] = '\0';
			fclose(pathReader);
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"del PATH_paths.txt\""), NULL, SW_SHOW);
			for (w = 0; contents[w] != '\0'; w++) {
				if (contents[w] == atcName[0]) {
					s = w;
					i = 0;
					while (contents[w] == atcName[i] && contents[w] != '\0') {
						i++; w++;
					}
					if (i == strlen(atcName)) {
						w = s;
						while (contents[w] != ';'&&w != 0) {
							w--;
						}
						w++;
						j = 0;
						while (contents[w] != ';'&&contents[w] != '\0') {
							atcPAth[j] = contents[w];
							w++; j++;
						}
						atcPAth[j] = '\0';
						if (atcPAth[strlen(atcPAth) - 2] == ' ') {
							atcPAth[strlen(atcPAth) - 2] = '\0';
						}
						open = NULL;
						while (open == NULL) {
							open = fopen("atc_path.txt", "w");
						}
						fprintf(open, "%s", atcPAth);
						fclose(open);
						sprintf(atcPath, "%s", atcPAth);
					}
				}
			}
		}
	}
	if (test != NULL) {
		fclose(test);
	}
	if (open != NULL) {
		fclose(open);
	}
}

void getATCPath() {
	FILE *aPath = NULL;
	aPath = fopen("atc_path.txt", "r");
	if (aPath == NULL) {
		aPath = fopen("atc_path.txt", "w");
		TCHAR NPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, NPath);
		wcstombs(atcPath, NPath, wcslen(NPath) + 1);
		fprintf(aPath, "%s", atcPath);
		fclose(aPath);
	}
	else {
		fgets(atcPath, DIM, aPath);
		fclose(aPath);
		if (atcPath[strlen(atcPath) - 2] == ' ') {
			atcPath[strlen(atcPath) - 2] = '\0';
		}
		FILE *test = NULL;
		char testPath[DIM] = "";
		sprintf(testPath, "%s\\License.txt", atcPath);
		test = fopen(testPath, "r");
		if (test == NULL) {
			test = fopen("atc_path.txt", "w");
			TCHAR NPath[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, NPath);
			wcstombs(atcPath, NPath, wcslen(NPath) + 1);
			fprintf(test, "%s", atcPath);
			fclose(test);
		}
	}
}

void getCharArray() {
	char value[DIM] = "";
	sprintf(expressionF, "");
	double Value = getValue();
	if (isEqual("x", expressionF)) {
		sprintf(value, "x");
	}
	else {
		sprintf(value, "%G", Value);
	}
	if (isContained("-", value)) {
		replace("-", "_", value);
	}
	else {
		sprintf(expressionF, value);
	}
}

double solve(char equation[DIM]) {
	char colectCoeff[DIM] = "";
	int p = 0;
	if (isContained("x", equation)) {
		int i = strStart - 1;
		if (verifyValue(equation[i])) {
			while (verifyValue(equation[i])) {
				i--;
			}
			i++;
			p = 0;
			if (equation[i - 1] == '-') {
				colectCoeff[p] = '_';
				p++;
			}
		}
		else {
			i++;
			colectCoeff[0] = '1';
			i++;
			p = 1;
		}
		while (verifyValue(equation[i]) && verifyLetter(equation[i + 1]) == (boolean)false) {
			colectCoeff[p] = equation[i];
			p++;
			i++;
			if (equation[i] == 'x') {
				colectCoeff[p] = '1';
				p++;
				i++;
			}
		}
		colectCoeff[p] = '\0';
		char equationF[DIM] = "";
		sprintf(equationF, "(%s)/(%s)", equation, colectCoeff);
		double answer = solver(equationF);
		return answer;
	}
	return 0;
}

int toSolve(int re) {
	FILE *file = NULL;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\disable_txt_detector.txt", atcPath);
	int retry = 0;
	while (file == NULL && retry < 7) {
		file = fopen(toOpen, "r");
		retry++;
	}
	if (file == NULL) {
		char option[30] = "", directory[DIM] = "";
		sprintf(directory, "%s\\To solve\\", atcPath);
		int k = 0, numFiles = 0, i = 0, numFilesSolved = 0;
		DIR *d;
		struct dirent *dir;
		d = opendir(directory);
		char filename[DIM] = "";
		char txtFiles[DIM] = "";
		if (d)
		{
			while ((dir = readdir(d)) != NULL)
			{
				if (dir->d_type == DT_REG)
				{
					sprintf(filename, "%s", dir->d_name);
					if (searchExtension(filename, ".txt")) {
						int h = abs((int)strlen(filename)) - 1;
						if (isContained("_answers.txt", filename) == false) {
							char path[DIM] = "";
							sprintf(path, "%s%s", directory, filename);
							int b = 0, m = 0;
							char addChars[DIM] = "_answers.txt";
							while ((path[b] == '.'&&path[b + 1] == 't'&&path[b + 2] == 'x'&&path[b + 3] == 't') == false) {
								b++;
							}
							while (addChars[m] != '\0') {
								path[b] = addChars[m];
								b++; m++;
							}
							path[b] = '\0';
							retry = 0;
							file = NULL;
							while (file == NULL && retry < 7) {
								file = fopen(path, "r");
								Sleep(10);
								retry++;
							}
							if (file == NULL) {
								sprintf(txtFiles, "%s\n%s", txtFiles, filename);
								numFiles++;
							}
							else {
								fclose(file);
							}
						}
						else {
							numFilesSolved++;
						}
					}
				}
			}
			for (k = 0; txtFiles[k + 1] != '\0'; k++) {
				txtFiles[k] = txtFiles[k + 1];
			}
			txtFiles[k] = '\0';
			closedir(d);
			int action = -1;
			if (numFiles != 0) {
				printf("\n==> ATC has detected %d file(s) in the \"To solve\" folder. <==\n\nDo you want to solve the file(s)? (Yes -> 1 / No -> 0)\n", numFiles);
				while (action != 0 && action != 1) {
					I_O = true;
					action = (int)getValue();
					if (action != 0 && action != 1) {
						puts("(Yes -> 1 / No -> 0)");
					}
				}
				puts(" ");
				if (action == 1) {
					char path[DIM] = "";
					char fileName[DIM] = "";
					int i = 0, j = 0;
					while (numFiles > 0) {
						j = 0;
						while (txtFiles[i] != '\n'&&txtFiles[i] != '\0') {
							fileName[j] = txtFiles[i];
							j++; i++;
						}
						fileName[j] = '\0';
						i++;
						numFiles--;
						sprintf(path, "%s%s", directory, fileName);
						processTxt(path, re);
					}
					printf("==> Check the folder \"To solve\" to see the answers file(s) generated. Enter \"to solve\". <== \n\n");
				}
				if (action == 0) {
					int disable = -1;
					printf("Do you want to disable the feature? (Yes -> 1 / No -> 0)\n");
					while (disable != 0 && disable != 1) {
						I_O = true;
						disable = (int)getValue();
						if (disable != 0 && disable != 1) {
							puts("(Yes -> 1 / No -> 0)");
						}
					}
					puts(" ");
					if (disable == 1) {
						FILE *dis = NULL;
						char toOpen[DIM] = "";
						sprintf(toOpen, "%s\\disable_txt_detector.txt", atcPath);
						retry = 0;
						while (dis == NULL && retry < 7) {
							dis = fopen(toOpen, "w");
							Sleep(10);
							retry++;
						}
						if (dis != NULL) {
							fclose(dis);
						}
						puts("==> To enable the feature later enter \"enable txt detector\" <==\n");
					}
				}
			}
			else {
				return 0;
			}
		}
	}
	else {
		if (file != NULL) {
			fclose(file);
		}
	}
	return 0;
}

void currentSettings() {
	solving = false;
	FILE *open = NULL;
	puts("");
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\mode.txt", atcPath);
	open = fopen(toOpen, "r");
	char info[DIM] = "";
	int state = 0;
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		state = (int)calcNow(info, 0, 0);
		switch (state) {
		case 1:
			puts("Mode------------------------------------> RADIAN Degree Gradian | Info: Enter \"mode\" to change.");
			break;
		case 2:
			puts("Mode------------------------------------> Radian DEGREE Gradian | Info: Enter \"mode\" to change.");
			break;
		case 3:
			puts("Mode------------------------------------> Radian Degree GRADIAN | Info: Enter \"mode\" to change.");
			break;
		}
	}
	else {
		puts("Mode------------------------------------> Radian DEGREE Gradian | Info: Enter \"mode\" to change.");
	}
	open = NULL;
	sprintf(toOpen, "%s\\numSystems.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		state = (int)calcNow(info, 0, 0);
		switch (state) {
		case 0:
			puts("Numerical Systems Response--------------> Enabled DISABLED | Info: Enter \"numerical systems\" to change.");
			break;
		case 1:
			puts("Numerical Systems Response--------------> ENABLED Disabled | Info: Enter \"numerical systems\" to change.");
			break;
		}
	}
	else {
		puts("Numerical Systems Response--------------> Enabled DISABLED | Info: Enter \"numerical systems\" to change.");
	}
	open = NULL;
	sprintf(toOpen, "%s\\siPrefixes.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		state = (int)calcNow(info, 0, 0);
		switch (state) {
		case 0:
			puts("SI Prefixes Response--------------------> Enabled DISABLED | Info: Enter \"si prefixes\" to change.");
			break;
		case 1:
			puts("SI Prefixes Response--------------------> ENABLED Disabled | Info: Enter \"si prefixes\" to change.");
			break;
		}
	}
	else {
		puts("SI Prefixes Response--------------------> Enabled DISABLED | Info: Enter \"si prefixes\" to change.");
	}
	open = NULL;
	sprintf(toOpen, "%s\\actualTime.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		state = (int)calcNow(info, 0, 0);
		switch (state) {
		case 0:
			puts("Actual Time Response--------------------> Enabled DISABLED | Info: Enter \"actual time response\" to change.");
			break;
		case 1:
			puts("Actual Time Response--------------------> ENABLED Disabled | Info: Enter \"actual time response\" to change.");
			break;
		}
	}
	else {
		puts("Actual Time Response--------------------> Enabled DISABLED | Info: Enter \"actual time response\" to change.");
	}
	open = NULL;
	sprintf(toOpen, "%s\\verboseResolution.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		state = (int)calcNow(info, 0, 0);
		switch (state) {
		case 0:
			puts("Verbose Resolution----------------------> Enabled DISABLED | Info: Enter \"verbose resolution\" to change.");
			break;
		case 1:
			puts("Verbose Resolution----------------------> ENABLED Disabled | Info: Enter \"verbose resolution\" to change.");
			break;
		}
	}
	else {
		puts("Verbose Resolution----------------------> Enabled DISABLED | Info: Enter \"verbose resolution\" to change.");
	}
	open = NULL;
	sprintf(toOpen, "%s\\colors.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		printf("Colors----------------------------------> Text: "); idColorToName(info[7]); printf(" - Background: "); idColorToName(info[6]); printf(" | Info: Enter \"colors\" to change.\n");
	}
	else {
		puts("Colors----------------------------------> Text: AQUA - Background: WHITE | Info: Enter \"colors\" to change.");
	}
	open = NULL;
	sprintf(toOpen, "%s\\window.txt", atcPath);
	open = fopen(toOpen, "r");
	int i = 0, e = 0, x, y, width, height, a = 1;
	char value[10] = "";
	if (open != NULL) {
		for (i = 0; (info[i] = fgetc(open)) != EOF; i++) {
			value[e] = info[i];
			if (info[i] != '\n') {
				e++;
			}
			if (value[e] == '\n'&&a == 1) {
				value[e] = '\0';
				x = atoi(value);
				a = 2; e = 0;
			}
			if (value[e] == '\n'&&a == 2) {
				value[e] = '\0';
				y = atoi(value);
				a = 3; e = 0;
			}
			if (value[e] == '\n'&&a == 3) {
				value[e] = '\0';
				width = atoi(value);
				a = 4; e = 0;
			}
			if (value[e] == '\n'&&a == 4) {
				value[e] = '\0';
				height = atoi(value);
				a = 5; e = 0;
			}
		}
		printf("Window----------------------------------> x: %d - y: %d - Width: %d - Height: %d | Info: Enter \"window\" to change.\n", x, y, width, height);
	}
	else {
		puts("Window----------------------------------> x: 0 - y: 0 - Width: 1000 - Height: 1000 | Info: Enter \"window\" to change.");
	}
	open = NULL;
	sprintf(toOpen, "%s\\dimensions.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		int lines = 0, columns = 0;
		fgets(info, 200, open);
		fclose(open);
		isContained("con cols=", info);
		i = strEnd;
		int j = 0;
		while (verifyNumber(info[i])) {
			value[j] = info[i];
			j++;
			i++;
		}
		value[j] = '\0';
		columns = atoi(value);
		isContained("lines=", info);
		i = strEnd;
		j = 0;
		while (verifyNumber(info[i])) {
			value[j] = info[i];
			j++;
			i++;
		}
		value[j] = '\0';
		lines = atoi(value);
		printf("Dimensions------------------------------> Lines: %d - Columns: %d | Info: Enter \"dimensions\" to change.\n", lines, columns);
	}
	else {
		puts("Dimensions------------------------------> Lines: 5000 - Columns: 167 | Info: Enter \"dimensions\" to change.");
	}
}

void on_start() {
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
	sprintf(Path, "%s\\temp_answers.txt", atcPath);
	Try = fopen(Path, "r");
	if (Try != NULL) {
		fclose(Try);
		char toOpen[DIM] = "";
		sprintf(toOpen, "del \"%s\"", Path);
		system(toOpen);
	}
	FILE *open = NULL;
	char onStart[100] = "";
	int Colors = 1, Dimensions = 2, Window = 3;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\onStart.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(onStart, 100, open);
		fclose(open);
		if (onStart[0] == 'r'&&onStart[1] == 'e'&&onStart[2] == 's'&&onStart[3] == 'e'&&onStart[4] == 't'&&onStart[5] == 'a'&&onStart[6] == 'l'&&onStart[7] == 'l'&&onStart[8] == '\0') {
			char toOpen[DIM] = "";
			sprintf(toOpen, "/C \"del \"%s\\history.txt\"&del \"%s\\graph.txt\"&del \"%s\\variables.txt\"&del \"%s\\renamedVar.txt\"&del \"%s\\pathName.txt\"&del \"%s\\predefinedTxt.txt\"&del \"%s\\calendar.txt\"&del \"%s\\numSystems.txt\"&del \"%s\\siPrefixes.txt\"&rmdir /Q /S \"%s\\Strings\"&del \"%s\\actualTime.txt\"&del \"%s\\colors.txt\"&del \"%s\\dimensions.txt\"& del \"%s\\verboseResolution.txt\"&del \"%s\\window.txt\"&del \"%s\\mode.txt\"&del \"%s\\onStart.txt\"&del \"%s\\disable_txt_detector.txt\"&del \"%s\\stringVariable.txt\"&mkdir \"%s\\Strings\"&del \"%s\\atc_path.txt\"", atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath);
			using namespace std;
			std::string s = string(toOpen);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
			Sleep(1000);
			applySettings(Colors);
			applySettings(Window);
			applySettings(Dimensions);
		}
		if (onStart[0] == 'r'&&onStart[1] == 'e'&&onStart[2] == 's'&&onStart[3] == 'e'&&onStart[4] == 't'&&onStart[5] == 's'&&onStart[6] == 'e'&&onStart[7] == 't'&&onStart[8] == 't'&&onStart[9] == 'i'&&onStart[10] == 'n'&&onStart[11] == 'g'&&onStart[12] == 's'&&onStart[13] == '\0') {
			char toOpen[DIM] = "";
			sprintf(toOpen, "/C \"del \"%s\\numSystems.txt\"&del \"%s\\graph.txt\"&del \"%s\\siPrefixes.txt\"&del \"%s\\actualTime.txt\"&del \"%s\\colors.txt\"&del \"%s\\dimensions.txt\"&del \"%s\\window.txt\"&del \"%s\\mode.txt\"&del \"%s\\verboseResolution.txt\"&del \"%s\\onStart.txt\"\"", atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath);
			using namespace std;
			std::string s = string(toOpen);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
			Sleep(1000);
			applySettings(Colors);
			applySettings(Window);
			applySettings(Dimensions);
		}
	}
}

void idColorToName(char color) {
	switch (color) {
	case '0':
		printf("BLACK");
		break;
	case '1':
		printf("BLUE");
		break;
	case '2':
		printf("GREEN");
		break;
	case '3':
		printf("AQUA");
		break;
	case '4':
		printf("RED");
		break;
	case '5':
		printf("PURPLE");
		break;
	case '6':
		printf("YELLOW");
		break;
	case '7':
		printf("WHITE");
		break;
	case '8':
		printf("GRAY");
		break;
	case '9':
		printf("LIGHT BLUE");
		break;
	case 'a':
		printf("LIGHT GREEN");
		break;
	case 'b':
		printf("LIGHT AQUA");
		break;
	case 'c':
		printf("LIGHT RED");
		break;
	case 'd':
		printf("LIGHT PURPLE");
		break;
	case 'e':
		printf("LIGHT YELLOW");
		break;
	case 'f':
		printf("BRIGHT WHITE");
		break;
	}
}

void ShowConsoleCursor(BOOL bShow)
{
	static HANDLE hOut;
	static BOOL firstTime = TRUE;
	CONSOLE_CURSOR_INFO cursorInfo;
	if (firstTime)
	{
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		firstTime = FALSE;
	}
	cursorInfo.dwSize = 10;
	cursorInfo.bVisible = bShow;
	SetConsoleCursorInfo(hOut, &cursorInfo);
}

void complexNumber(double a, double b) {
	if (solverRunning == (boolean)false) {
		processingOK = -1;
	}
	verify = 0;
	if (a > 0 && b > 0) {
		printf("%G+%Gi\n", a, b);
	}
	else {
		if (a > 0 && b < 0) {
			printf("%G%Gi\n", a, b);
		}
		else {
			if (a < 0 && b > 0) {
				printf("%G+%Gi\n", a, b);
			}
			else {
				if (a < 0 && b < 0) {
					printf("%G%Gi\n", a, b);
				}
				else {
					if (a == 0 && b == 0) {
						printf("%G\n", a);
					}
					else {
						if (a == 0 && b != 0) {
							printf("%Gi\n", b);
						}
						else {
							if (a != 0 && b == 0) {
								printf("%G\n", a);
							}
							else {
								printf("%G+%Gi\n", a, b);
							}
						}
					}
				}
			}
		}
	}
	resultR = -7; resultI = -7;
	if (rasf > 0) {
		puts("");
	}
	if (solverRunning) {
		processingOK = 1;
	}
}

boolean IsPreviousToWindowsVista()
{
	boolean previousToVista = false;

	OSVERSIONINFOEX osversion;
	ZeroMemory(&osversion, sizeof(OSVERSIONINFOEX));
	osversion.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (GetVersionEx((OSVERSIONINFO*)&osversion))
	{
		const DWORD VistaVersion = 6;
		if ((osversion.dwPlatformId == VER_PLATFORM_WIN32_NT) && (osversion.dwMajorVersion < VistaVersion))
		{
			previousToVista = true;
		}
	}
	return previousToVista;
}

char character_to_prefDet(double n) {
	if (n < 1E-21)
		return 'A';
	else
		if (n < 1E-18)
			return 'B';
		else
			if (n < 1E-15)
				return 'C';
			else
				if (n < 1E-12)
					return 'D';
				else
					if (n < 1E-9)
						return 'E';
					else
						if (n < 1E-6)
							return 'F';
						else
							if (n < 1E-3)
								return 'G';
							else
								if (n < 1E-2)
									return 'H';
								else
									if (n < 1E-1)
										return 'I';
									else
										if (n < 1E1)
											return 'J';
										else
											if (n < 1E2)
												return 'K';
											else
												if (n < 1E3)
													return 'L';
												else
													if (n < 1E6)
														return 'M';
													else
														if (n < 1E9)
															return 'N';
														else
															if (n < 1E12)
																return 'O';
															else
																if (n < 1E15)
																	return 'P';
																else
																	if (n < 1E18)
																		return 'Q';
																	else
																		if (n < 1E21)
																			return 'R';
																		else
																			if (n < 1E24)
																				return 'S';
																			else
																				if (n >= 1E24)
																					return 'T';
	return 'U';
}

int variableValidator(char variable[DIM]) {
	int validate = 0, i = 0, h = -1, abc = 0, j = 0, k = 0, sD = 0;
	char variableT[DIM], varLetters[DIM] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
	double arith = 0, func = 0;
	for (k = 0; variable[k] != '\0'; k++) {
		for (i = 0; varLetters[i] != '\0'; i++) {
			if (variable[k] == varLetters[i]) {
				j++;
				break;
			}
		}
	}
	FILE *user = NULL;
	char path_user[DIM] = "";
	sprintf(path_user, "%s\\User functions\\%s.txt", atcPath, variable);
	user = fopen(path_user, "r");
	boolean variable_inside_user_function;
	variable_inside_user_function = isContainedInUserFunction(variable);
	if (j != strlen(variable) || j == 0 && strlen(variable) == 0 || user != NULL || variable_inside_user_function) {
		if (user != NULL) {
			fclose(user);
		}
		user = NULL;
		h = 0;
		return h;
	}
	revariable[0] = '\0';
	FILE *var = NULL, *var1 = NULL;
	i = 0;
	abc = abs((int)strlen(variable));
	valid = 0;
	for (i = 0; variable[i] != '\0'; i++) {
		if (i == 0 && (variable[i] == 's' || variable[i] == 'c' || variable[i] == 't' || variable[i] == 'a' || variable[i] == 'l' || variable[i] == 'r' || variable[i] == 'q' || variable[i] == 'g' || variable[i] == 'd')) {
			if (variable[i] == 's') {
				revariable[i] = 'S';
			}
			if (variable[i] == 'c') {
				revariable[i] = 'W';
			}
			if (variable[i] == 't') {
				revariable[i] = 'J';
			}
			if (variable[i] == 'a') {
				revariable[i] = 'k';
			}
			if (variable[i] == 'l') {
				revariable[i] = 'L';
			}
			if (variable[i] == 'r') {
				revariable[i] = 'R';
			}
			if (variable[i] == 'q') {
				revariable[i] = 'Q';
			}
			if (variable[i] == 'g') {
				revariable[i] = 'G';
			}
			if (variable[i] == 'd') {
				revariable[i] = 'K';
			}
			h = 1;
		}
		else {
			if (variable[i] == 'i' || variable[i] == 'e' || variable[i] == 'D' || variable[i] == 'b') {
				if (variable[i] == 'i') {
					revariable[i] = 'Z';
				}
				if (variable[i] == 'e') {
					revariable[i] = 'w';
				}
				if (variable[i] == 'D') {
					revariable[i] = 'T';
					if (isEqual("D", variable)) {
						return 2;
					}
				}
				if (variable[i] == 'b') {
					revariable[i] = 'u';
					if (isEqual("b", variable)) {
						return 2;
					}
				}
				h = 1;
			}
			else {
				if (i == 0 && (variable[i] == 'B' || variable[i] == 'O' || variable[i] == 'H' || variable[i] == 'P')) {
					if (variable[i] == 'B') {
						revariable[i] = 'N';
					}
					if (variable[i] == 'O') {
						revariable[i] = 'M';
					}
					if (variable[i] == 'H') {
						revariable[i] = 'V';
					}
					if (variable[i] == 'P') {
						revariable[i] = 'I';
					}
					h = 1;
				}
				else {
					if (variable[i] == 'A' || variable[i] == 'B' || variable[i] == 'C' || variable[i] == 'E' || variable[i] == 'P' || (variable[i - 2] == 'I'&&variable[i - 1] == 'N') == false && variable[i] == 'F') {
						if (variable[i] == 'A') {
							revariable[i] = 'X';
						}
						if (variable[i] == 'B') {
							revariable[i] = 'N';
						}
						if (variable[i] == 'C') {
							revariable[i] = 'v';
						}
						if (variable[i] == 'E') {
							revariable[i] = 'Y';
						}
						if (variable[i] == 'F') {
							revariable[i] = 'U';
						}
						if (variable[i] == 'P') {
							revariable[i] = 'I';
						}
						h = 1;
					}
					else {
						revariable[i] = variable[i];
					}
				}
			}
		}
	}
	revariable[i] = '\0';
	i = 0;
	variable[abc] = '\0';
	processVariable(variable);
	variable[abc] = '\0';
	arith = arithSolver(variable, 0);
	if ((variable[0] == 'E' || variable[0] == 'B' || variable[0] == 'O' || variable[0] == 'H' || variable[0] == 'P') && variable[1] == '=') {
		arith = 10;
	}
	variable[abc] = '\0';
	for (i = 0; variable[i] != '\0'; i++) {
		variableT[i] = variable[i];
	}
	variableT[i] = '?'; variableT[i + 1] = '\0';
	char testPrefix[DIM] = "";
	for (i = 0; variable[i] != '\0'; i++) {
		testPrefix[i] = variable[i];
	}
	testPrefix[i] = '\0';
	double prefix = 0;
	if (testPrefix[0] == 'P') {
		testPrefix[0] = '1';
		for (i = 1; testPrefix[i] != '\0'; i++) {
			testPrefix[i] = testPrefix[i - 1];
		}
		testPrefix[i] = '\0';
		prefix = arithSolver(testPrefix, 0);
	}
	func = functionProcessor(variableT, 0.3, 1.0, 0);
	variable[abc] = '\0';
	processVariable(variable);
	if (h == 1 && valid == 0 && arith == 0 && func == 0 && prefix == 0) {
		i = 0;
		FILE *var1 = NULL;
		if (var1 != NULL) {
			fclose(var1);
		}
		var1 = NULL;
		char toOpen[DIM] = "";
		sprintf(toOpen, "%s\\renamedVar.txt", atcPath);
		while (var1 == NULL && i < 100) {
			var1 = fopen(toOpen, "a+");
			i++;
		}
		char vari[DIM] = "";
		i = 0;
		for (i = 0; (vari[i] = fgetc(var1)) != EOF; i++);
		vari[i] = '\0';
		fclose(var1);
		var1 = NULL;
		i = 0;
		while (var1 == NULL && i < 100) {
			var1 = fopen(toOpen, "w");
			i++;
		}
		if (i < 100) {
			char line[DIM] = "";
			sprintf(line, "%s %s\n", variable, revariable);
			if (!(isContained(line, vari) && (strStart == 0 || vari[strStart - 1] == '\n'))) {
				fputs(line, var1);
			}
			fputs(vari, var1);
			fclose(var1);
		}
		i = 0;
	}
	else {
		if (h == 1 && valid == 0 && (arith != 0 || func != 0 || prefix != 0)) {
			h = 2;
		}
	}
	return h;
}

double prefToNumber(char prefix) {
	double result = 0;
	if (prefix == 'Y') {
		result = pow(10.0, 24.0);
		return result;
	}
	if (prefix == 'Z') {
		result = pow(10.0, 21.0);
		return result;
	}
	if (prefix == 'E') {
		result = pow(10.0, 18.0);
		return result;
	}
	if (prefix == 'P') {
		result = pow(10.0, 15.0);
		return result;
	}
	if (prefix == 'T') {
		result = pow(10.0, 12.0);
		return result;
	}
	if (prefix == 'G') {
		result = pow(10.0, 9.0);
		return result;
	}
	if (prefix == 'M') {
		result = pow(10.0, 6.0);
		return result;
	}
	if (prefix == 'k') {
		result = pow(10.0, 3.0);
		return result;
	}
	if (prefix == 'h') {
		result = pow(10.0, 2.0);
		return result;
	}
	if (prefix == 'D') {
		result = pow(10.0, 1.0);
		return result;
	}
	if (prefix == 'd') {
		result = pow(10.0, -1.0);
		return result;
	}
	if (prefix == 'c') {
		result = pow(10.0, -2.0);
		return result;
	}
	if (prefix == 'm') {
		result = pow(10.0, -3.0);
		return result;
	}
	if (prefix == 'u') {
		result = pow(10.0, -6.0);
		return result;
	}
	if (prefix == 'n') {
		result = pow(10.0, -9.0);
		return result;
	}
	if (prefix == 'p') {
		result = pow(10.0, -12.0);
		return result;
	}
	if (prefix == 'f') {
		result = pow(10.0, -15.0);
		return result;
	}
	if (prefix == 'a') {
		result = pow(10.0, -18.0);
		return result;
	}
	if (prefix == 'z') {
		result = pow(10.0, -21.0);
		return result;
	}
	if (prefix == 'y') {
		result = pow(10.0, -24.0);
		return result;
	}
	return result;
}

double numericalSystems(char numSystem[DIM]) {
	double result = 0;
	char system = ' ';
	int i, j = 0;
	system = numSystem[0];
	if (numSystem[1] == '_') {
		numSystem[1] = '-';
	}
	for (i = 1; numSystem[i] != '\0'; i++) {
		numSystem[i - 1] = numSystem[i];
		if (numSystem[i - 1] == '.') {
			j++;
			if (j == 2) {
				numSystem[i - 1] = '\0';
			}
		}
	}
	numSystem[i - 1] = '\0';
	if (system == 'B') {
		result = binaryToDecimal(numSystem);
	}
	if (system == 'O') {
		result = octalToDecimal(numSystem);
	}
	if (system == 'H') {
		result = hexadecimalToDecimal(numSystem);
	}
	return result;
}

double processVariable(char variable[DIM]) {
	validVar = 0;
	FILE *open = NULL;
	int i, g, h, y, l = 0, lth = 0, cou = 0;
	double varValue = 0;
	char vari[DIM] = "", va[DIM] = "", value[DIM] = "";
	char *pointer;
	i = 0;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\variables.txt", atcPath);
	open = fopen(toOpen, "a+");
	while (open == NULL && cou < 10) {
		open = fopen(toOpen, "a+");
		cou++;
	}
	if (cou < 10) {
		i = 0;
		for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
		vari[i] = '\0';
		lth = abs((int)strlen(vari));
		fclose(open);
		i = 0;
		for (i = 0; vari[i] != '\0'; i++) {
			g = 0;
			int j = i;
			while (vari[j] != ' '&&vari[j] != '\0') {
				j++;
			}
			j = j - i;
			if (vari[i] == variable[g] && (i == 0 || vari[i - 1] == '\n')) {
				while (vari[i] == variable[g]) {
					if (vari[i] == variable[g]) {
						va[g] = vari[i];
					}i++; g++;
				}
				if (vari[i] != ' ') {
					while (vari[i] != ' ') {
						va[g] = vari[i];
						g++; i++;
					}
				}
				va[g] = '\0';
			}
			l = i;
			g = 0;
			for (y = 0; va[y] != '\0'; y++) {
				if (va[y] == variable[y]) {
					g++;
				}
			}
			vari[lth] = '\0';
			if (g == strlen(va) && strlen(variable) == g && j == g && g != 0) {
				int space = 0;
				valid = 1; validVar = 1;
				int gh = l;
				while (vari[gh] != '\n') {
					gh++;
				}
				h = gh;
				gh = l + 1;
				y = 0;
				for (gh; gh < h; gh++) {
					value[y] = vari[gh];
					if (value[y] == ' ') {
						space = 1;
					}
					y++;
				}
				value[y] = '\0';
				if (space == 0) {
					resultR = strtod(value, &pointer);
				}
				else {
					char real[DIM] = "", imag[DIM] = "";
					y = 0;
					while (value[y] != ' ') {
						real[y] = value[y];
						y++;
					}
					real[y] = '\0';
					y++;
					gh = 0;
					while (value[y] != '\0') {
						imag[gh] = value[y];
						y++; gh++;
					}
					imag[gh] = '\0';
					resultR = strtod(real, &pointer);
					resultI = strtod(imag, &pointer);
					varValue = resultR;
				}
				break;
			}
		}
	}
	return varValue;
}

double convertToNumber(char number[DIM]) {
	int i = 0, j = 0, num = 0, k = 0, l = 0, sig = 1, h = 0, m = 0, f = 0;
	char nu[DIM] = "";
	double result = 0, exp = 0;
	for (h = 0; number[h] != '\0'; h++) {
		if (number[h] == 'E') {
			m = h;
			h++;
			f = 0;
			if (number[h] == '-') {
				sig = -1;
				h++;
			}
			while (number[h] != '\0') {
				nu[f] = number[h];
				f++; h++;
			}
			nu[f] = '\0';
			exp = convertToNumber(nu);
			number[m] = '.';
			number[m + 1] = '0';
			number[m + 2] = '\0';
		}
	}
	i = 0;
	while (number[i] != '.'&&number[i] != '\0') {
		i++;
	}
	i--;
	j = i;
	k = i;
	i++;
	while (number[i] != '\0') {
		i++;
	}
	l = abs((int)strlen(number)) - j - 4;
	for (i = 0; j >= 0; i++) {
		nu[0] = number[i];
		nu[1] = '.';
		nu[2] = '0';
		nu[3] = '\0';
		num = atoi(nu);
		result = result + num * pot(10.0, j, 1);
		j--;
	}
	k = k + 2;
	i = 1;
	for (k; i <= l && number[k] != '\0'&&k < abs((int)strlen(number)); k++) {
		nu[0] = number[k];
		nu[1] = '.';
		nu[2] = '0';
		nu[3] = '\0';
		num = atoi(nu);
		result = result + num * pot(10.0, i*-1, 1);
		i++;
	}
	result = result * pot(10.0, exp*sig, 1);
	return result;
}

double calcNow(char toCalc[DIM], double result1, double result2) {
	if (strlen(toCalc) != 0) {
		char expression[DIM] = "";
		sprintf(expression, "%s", toCalc);
		feedbackValidation = 1;
		resultR = 0; resultI = 0;
		resultR = solveNow(expression, result1, result2);
		feedbackValidation = 0;
		if (verified == 0) {
			printf("Invalid expression: %s\n\n", toCalc);
		}
	}
	else {
		verified = 1; resultR = 0; resultI = 0;
	}
	return resultR;
}

boolean firstLetterVariable(char letter) {
	char letters[100] = "QWRTYUISGJKLZXVNMwyuofhjkxzvnmp";
	int i = 0;
	for (i = 0; i < abs((int)strlen(letters)); i++) {
		if (letter == letters[i]) {
			return true;
		}
	}
	return false;
}

boolean letterVariables(char letter) {
	char letters[100] = "QWRTYUIOSGHJKLZXVNMqwrtyuopasxdfghjklzcvnm";
	int i = 0;
	for (i = 0; i < abs((int)strlen(letters)); i++) {
		if (letter == letters[i]) {
			return true;
		}
	}
	return false;
}

boolean verifyLetter(char letter) {
	char letters[DIM] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
	int i = 0;
	for (i = 0; i < abs((int)strlen(letters)); i++) {
		if (letter == letters[i]) {
			return true;
		}
	}
	return false;
}

boolean verifyNumber(char number) {
	char numbers[DIM] = "_0.123456789E";
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			return true;
		}
	}
	return false;
}

boolean verifyOperator(char operatorF) {
	char numbers[DIM] = "+_^/*S)";
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (operatorF == numbers[i]) {
			return true;
		}
	}
	return false;
}
boolean verifyOperators(char operatorF) {
	char numbers[DIM] = "+-*/^";
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (operatorF == numbers[i]) {
			return true;
		}
	}
	return false;
}

boolean verifyNumberExpression(char number) {
	char numbers[DIM] = "_0.123456789Epiex(^)S";
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			return true;
		}
	}
	return false;
}

int countOccurrences(char to_find[DIM], char expression[DIM]) {
	char expressionR[DIM] = "";
	char to_findR[DIM] = "";
	int numberOccurrences = 0;
	replaceTimes = 0;
	sprintf(expressionR, "%s", expression);
	sprintf(to_findR, "%s", to_find);
	if (isContained(to_findR, expressionR)) {
		while (isContained(to_findR, expressionR)) {
			numberOccurrences++;
			char cuttedExpression[DIM] = "";
			int i = 0;
			int j = 0;
			while (i < strStart) {
				cuttedExpression[j] = expressionR[i];
				i++; j++;
			}
			i = strEnd;
			while (expressionR[i] != '\0') {
				cuttedExpression[j] = expressionR[i];
				j++; i++;
			}
			cuttedExpression[j] = '\0';
			sprintf(expressionR, "%s", cuttedExpression);
		}
	}
	return numberOccurrences;
}

int deleteXOccurrences(char to_find[DIM], char expression[DIM], int x) {
	char expressionR[DIM] = "";
	char to_findR[DIM] = "";
	int numberOccurrences = 1;
	sprintf(expressionR, expression);
	sprintf(to_findR, to_find);
	if (isContained(to_findR, expressionR) && countOccurrences(to_findR, expressionR) >= x) {
		while (isContained(to_findR, expressionR) && numberOccurrences < x) {
			numberOccurrences++;
			char cuttedExpression[DIM] = "";
			int i = 0;
			int j = 0;
			while (i < strStart) {
				cuttedExpression[j] = expressionR[i];
				i++; j++;
			}
			i = strEnd;
			while (expressionR[i] != '\0') {
				cuttedExpression[j] = expressionR[i];
				j++; i++;
			}
			cuttedExpression[j] = '\0';
			sprintf(expressionR, cuttedExpression);
		}
	}
	sprintf(expressionF, expressionR);
	return numberOccurrences;
}

boolean verifyValue(char number) {
	char numbers[DIM] = "_.0123456789*/^Epie";
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			return true;
		}
	}
	return false;
}

boolean verifyNumerator(char number) {
	char numbers[DIM] = "_.0123456789*^Epie";
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			return true;
		}
	}
	return false;
}
boolean verifyFraction(char number) {
	char numbers[DIM] = "_.0123456789Epie/";
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			return true;
		}
	}
	return false;
}
boolean verifyMultiplication(char number) {
	char numbers[DIM] = "_.0123456789Epie*";
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			return true;
		}
	}
	return false;
}

boolean verifyForNumber(char number) {
	char numbers[DIM] = "_.0123456789Epie";
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			return true;
		}
	}
	return false;
}

boolean verifyCoefficient(char number) {
	char numbers[DIM] = "_.0123456789*Epie";
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			return true;
		}
	}
	return false;
}

boolean verifyNumerical(char number) {
	char numbers[DIM] = "_-.0123456789ABCDEF";
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			return true;
		}
	}
	return false;
}

boolean verify4Printf(char chars) {
	char printfChars[DIM] = "0123456789diuoxXfFeEgGaAcspn%-+#*.hljztL\"";
	int i = 0;
	for (i = 0; i < abs((int)strlen(printfChars)); i++) {
		if (chars == printfChars[i]) {
			return true;
		}
	}
	return false;
}

boolean verifySpecifier(char chars) {
	char printfChars[DIM] = "diuoxXfFeEgGaAcsp";
	int i = 0;
	for (i = 0; i < abs((int)strlen(printfChars)); i++) {
		if (chars == printfChars[i]) {
			return true;
		}
	}
	return false;
}

boolean isToWrite(char arith[DIM]) {
	if (isEqual("NO_ANSWERS_FILE", arith)) {
		return false;
	}
	else {
		return true;
	}
}

boolean verifyPrefix(char prefix[DIM]) {
	char prefixes[DIM] = "Y,Z,E,P,T,G,M,k,h,da,d,c,m,u,n,p,f,a,z,y,";
	int i = 0, j = 0;
	for (i = 0; prefix[i] != '\0'; i++) {
		for (j = 0; prefixes[j] != '\0'; j++) {
			if (prefix[i] == prefixes[j] && i == 0) {
				while (prefix[i] == prefixes[j]) {
					i++; j++;
				}
				if (prefix[i] == '\0'&&prefixes[j] == ',') {
					return true;
				}
				i = 0;
			}
		}
	}
	return false;
}

boolean firstLetterFunction(char letter) {
	char letters[100] = "castlrqgd";
	int i = 0;
	for (i = 0; i < abs((int)strlen(letters)); i++) {
		if (letter == letters[i]) {
			return true;
		}
	}
	return false;
}

boolean searchExtension(char filename[DIM], char extension[DIM]) {
	int i = abs((int)strlen(filename)) - 1, j = abs((int)strlen(extension)) - 1;
	while (extension[j] == filename[i]) {
		i--; j--;
	}
	i++; j++;
	if (extension[j] == filename[i] && extension[j] == '.') {
		return true;
	}
	else {
		return false;
	}
}

boolean readyToSolve(char paTh[DIM]) {
	FILE *open = NULL;
	char pathToFile[DIM] = "", dataFromFile[DIM] = "";
	int i = 0;
	replace("\"", "", paTh);
	replace("\\", "RASF", expressionF);
	replace("RASF", "\\\\", expressionF);
	sprintf(pathToFile, "%s", expressionF);
	open = fopen(pathToFile, "r");
	if (open != NULL) {
		for (i = 0; (dataFromFile[i] = fgetc(open)) != EOF; i++);
		fclose(open);
		dataFromFile[i] = '\0';
		boolean has_flag = isContained("SOLVE_NOW", dataFromFile);
		if (has_flag) {
			replace("SOLVE_NOW", "", dataFromFile);
			open = NULL;
			open = fopen(pathToFile, "w");
			if (open != NULL) {
				fprintf(open, "%s", expressionF);
				fclose(open);
			}
		}
		return has_flag;
	}
	else {
		return false;
	}
	return false;
}

boolean isContainedVariable(char to_find[DIM], char string[DIM]) {
	int i = 0, j = 0, k = 0;
	char check_variable[DIM] = "";
	for (i = 0; i < abs((int)strlen(string)); i++) {
		for (j = 0; j < abs((int)strlen(to_find)); j++) {
			if (to_find[j] == string[i] && firstLetterVariable(to_find[j]) && j == 0) {
				while (to_find[j] == string[i] && to_find[j] != '\0'&&string[i] != '\0') {
					j++;
					i++;
				}
				int l = j - 1;
				while (letterVariables(string[l])) {
					l--;
				}
				l++;
				k = 0;
				while (letterVariables(string[l])) {
					check_variable[k] = string[l];
					l++; k++;
				}
				check_variable[k] = '\0';
				if (isVariable(check_variable) == (boolean)false) {
					return false;
				}
				else {
					if (isContained(to_find, string) && strlen(to_find) != strlen(string)) {
						return true;
					}
					else {
						return false;
					}
				}
			}
		}
	}
	return false;
}

boolean isContainedByIndex(char to_find[DIM], char string[DIM], int index) {
	int i = 0, j = 0;
	sprintf(charMaster, "");
	if (strlen(charMaster) == 0) {
		for (i = index; i < abs((int)strlen(string)); i++) {
			for (j = 0; j < abs((int)strlen(to_find)); j++) {
				if (to_find[j] == string[i] && j == 0) {
					strStart = i;
					while (to_find[j] == string[i] && to_find[j] != '\0'&&string[i] != '\0') {
						j++;
						i++;
					}
					if (j == strlen(to_find)) {
						strEnd = i;
						return true;
					}
					else {
						i = strStart;
						break;
					}
				}
			}
		}
	}
	return false;
}
boolean isContained(char to_find[DIM], char string[DIM]) {
	int i = 0, j = 0;
	if (strlen(charMaster) == 0) {
		for (i = 0; i < abs((int)strlen(string)); i++) {
			for (j = 0; j < abs((int)strlen(to_find)); j++) {
				if (to_find[j] == string[i] && j == 0) {
					strStart = i;
					while (to_find[j] == string[i] && to_find[j] != '\0'&&string[i] != '\0') {
						j++;
						i++;
					}
					if (j == strlen(to_find)) {
						strEnd = i;
						return true;
					}
					else {
						i = strStart;
						break;
					}
				}
			}
		}
	}
	else {
		if (isEqual("nothingL", charMaster)) {
			for (i = 0; i < abs((int)strlen(string)); i++) {
				for (j = 0; j < abs((int)strlen(to_find)); j++) {
					if (to_find[j] == string[i] && j == 0 && verifyLetter(string[i - 1]) == (boolean)false && verifyNumber(string[i - 1]) == (boolean)false) {
						strStart = i;
						while (to_find[j] == string[i] && to_find[j] != '\0'&&string[i] != '\0') {
							j++;
							i++;
						}
						if (j == strlen(to_find)) {
							strEnd = i;
							return true;
						}
						else {
							i = strStart;
							break;
						}
					}
				}
			}
		}
		else {
			if (isEqual("nothingR", charMaster)) {
				for (i = 0; i < abs((int)strlen(string)); i++) {
					for (j = 0; j < abs((int)strlen(to_find)); j++) {
						if (to_find[j] == string[i] && j == 0) {
							strStart = i;
							while (to_find[j] == string[i] && to_find[j] != '\0'&&string[i] != '\0') {
								j++;
								i++;
							}
							if (j == strlen(to_find) && verifyLetter(string[i - 1]) == (boolean)false && verifyNumber(string[i - 1]) == (boolean)false) {
								strEnd = i;
								return true;
							}
							else {
								i = strStart;
								break;
							}
						}
					}
				}
			}
			else {
				char saveTo_find[DIM] = "";
				sprintf(saveTo_find, to_find);
				sprintf(to_find, "%s%s", charMaster, saveTo_find);
				for (i = 0; i < abs((int)strlen(string)); i++) {
					for (j = 0; j < abs((int)strlen(to_find)); j++) {
						if (to_find[j] == string[i] && j == 0) {
							strStart = i;
							while (to_find[j] == string[i] && to_find[j] != '\0'&&string[i] != '\0') {
								j++;
								i++;
							}
							if (j == strlen(to_find)) {
								strEnd = i;
								return true;
							}
							else {
								i = strStart;
								break;
							}
						}
					}
				}
				sprintf(to_find, "%s%s", saveTo_find, charMaster);
				for (i = 0; i < abs((int)strlen(string)); i++) {
					for (j = 0; j < abs((int)strlen(to_find)); j++) {
						if (to_find[j] == string[i] && j == 0) {
							strStart = i;
							while (to_find[j] == string[i] && to_find[j] != '\0'&&string[i] != '\0') {
								j++;
								i++;
							}
							if (j == strlen(to_find)) {
								strEnd = i;
								return true;
							}
							else {
								i = strStart;
								break;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

boolean isEqual(char to_find[DIM], char string[DIM]) {
	int i = 0;
	while (to_find[i] == string[i] && string[i] != '\0') {
		i++;
	}
	if (to_find[i] == string[i] && to_find[i] == '\0') {
		return true;
	}
	return false;
}

int trackMouse() {
	POINT p;
	GetCursorPos(&p);
	MouseMove(100, 100);
	leftClick();
	MouseMove(p.x, p.y);
	return 0;
}

int getReady() {
	int x = 0, y = 0, maxX = 0, maxY = 0, saveX, saveY = 0, minX = -1, minY = -1, columns = 0, rows = 0, saveColumns = -1, saveRows = -1;
	Pressed = 0;
	do {
		fflush(NULL);
		FILE *open = NULL;
		POINT p;
		GetWindowPos(&x, &y, &maxX, &maxY);
		GetCursorPos(&p);
		if (x != minX || y != minY) {
			setWindow(x, y);
		}
		if (WindowFromPoint(p) == GetConsoleWindow()) {
			if (GetKeyState(VK_RBUTTON) < 0) {
				if (x + 50 < p.x&& y + 50 < p.y&&p.x < maxX - 50 && p.y < maxY - 50) {
					GetActiveWindow();
					Pressed = 1;
				}
			}
		}
		if (WindowFromPoint(p) == GetConsoleWindow()) {
			if (GetKeyState(VK_LBUTTON) < 0) {
				if (x + 50 < p.x&& y + 50 < p.y&&p.x < maxX - 50 && p.y < maxY - 50) {
					GetActiveWindow();
					Pressed = 1;
				}
			}
		}
		if (WindowFromPoint(p) == GetConsoleWindow()) {
			for (int cha = 0; cha < abs((int)strlen(validChars)); cha++) {
				if (GetKeyState(validChars[cha]) < 0) {
					HKL KeyBoard = GetKeyboardLayout(0);
					INPUT input = { 0 };
					input.type = INPUT_KEYBOARD;
					input.ki.time = 0;
					input.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
					input.ki.wScan = 0;
					input.ki.wVk = VkKeyScanEx(validChars[cha], KeyBoard);
					input.ki.dwExtraInfo = 0;
					SendInput(1, &input, sizeof(INPUT));
					Pressed = 1;
				}
				if (GetKeyState(VK_RIGHT) < 0 || GetKeyState(VK_LEFT) < 0 || GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_UP) < 0) {
					Pressed = 1;
				}
			}
		}
		if (GetKeyState(VK_LBUTTON) < 0) {
			while (GetKeyState(VK_LBUTTON) < 0) {
				Sleep(100);
			}
			GetWindowPos(&x, &y, &maxX, &maxY);
			GetCursorPos(&p);
			if (WindowFromPoint(p) == GetConsoleWindow()) {
				if (x + 50 < p.x&& y + 50 < p.y&&p.x < maxX - 50 && p.y < maxY - 50 && p.x != saveX && p.y != saveY) {
					GetActiveWindow();
					leftClick();
					INPUT ip;
					ip.type = INPUT_KEYBOARD;
					ip.ki.time = 0;
					ip.ki.dwFlags = KEYEVENTF_UNICODE;
					ip.ki.wScan = VK_RETURN;
					ip.ki.wVk = 0;
					ip.ki.dwExtraInfo = 0;
					SendInput(1, &ip, sizeof(INPUT));
					Pressed = 1;
				}
			}
		}
		char readCommand[DIM] = "";
		char toOpen[DIM] = "";
		sprintf(toOpen, "%s\\sendCommand.txt", atcPath);
		int i = 0;
		open = NULL;
		open = fopen(toOpen, "r");
		if (open != NULL) {
			for (i = 0; (readCommand[i] = fgetc(open)) != EOF; i++);
			readCommand[i] = '\0';
			fclose(open);
			open = NULL;
			while (open == NULL) {
				open = fopen(toOpen, "w");
			}
			fclose(open);
			if (!isEqual(readCommand, "dimensions") && !isEqual(readCommand, "window") && abs((int)strlen(readCommand)) > 0) {
				sprintf(expressionF, "%s", readCommand);
				Pressed = 2;
			}
			else {
				if (isEqual(readCommand, "dimensions")) {
					int Window = 3, Dimensions = 2;
					applySettings(Dimensions);
					printf(">");
				}
				else {
					if (isEqual(readCommand, "window")) {
						int Window = 3, Dimensions = 2;
						applySettings(Window);
					}
				}
			}
		}
		saveX = p.x;
		saveY = p.y;
		Sleep(77);
	} while (Pressed == 0);
	return 0;
}

void setWindow(int x, int y) {
	FILE *open;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\window.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d\n%d\n%d\n%d\n", x, y, widthATC, heightATC);
	fclose(open);
	xATC = x;
	yATC = y;
}

void setDimensions(int cols, int lines) {
	FILE *open = NULL;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\dimensions.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "MODE con cols=%d lines=%d", cols, lines);
	colsATC = cols;
	linesATC = lines;
	fclose(open);
}

void GetWindowPos(int *x, int *y, int *maxX, int *maxY) {
	RECT rect = { NULL };
	if (GetWindowRect(GetConsoleWindow(), &rect)) {
		*x = rect.left;
		*y = rect.top;
		*maxX = rect.right;
		*maxY = rect.bottom;
	}
}

void MouseMove(int x, int y)
{
	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
	double fx = x * (65535.0f / fScreenWidth);
	double fy = y * (65535.0f / fScreenHeight);
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = (long)fx;
	Input.mi.dy = (long)fy;
	::SendInput(1, &Input, sizeof(INPUT));
}


void split(char splitter[DIM], char data[DIM]) {
	int i = 0, x = 0, y = 0, k = 0;
	while (i <= countSplits) {
		sprintf(splitResult[i], "");
		i++;
	}
	i = 0;
	if (isContained(splitter, data)) {
		while (isContained(splitter, data)) {
			i = 0;
			x = 0;
			while (i < strStart) {
				splitResult[y][x] = data[i];
				x++; i++;
			}
			splitResult[y][x] = '\0';
			y++;
			k = 0;
			while (data[k + strEnd] != '\0') {
				data[k] = data[k + strEnd];
				k++;
			}
			data[k] = '\0';
			if (abs((int)strlen(data)) > 0 && !isContained(splitter, data)) {
				sprintf(splitResult[y], "%s", data);
			}
		}
	}
}

void clearKeyboardBuffer()
{
	while (_kbhit())
	{
		_getche();
	}
}

void ClearConsoleInputBuffer()
{
	PINPUT_RECORD ClearingVar1 = new INPUT_RECORD[256];
	DWORD ClearingVar2;
	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), ClearingVar1, 256, &ClearingVar2);
	delete[] ClearingVar1;
}

void show(HWND hwnd)
{
	WINDOWPLACEMENT place = { sizeof(WINDOWPLACEMENT) };
	GetWindowPlacement(hwnd, &place);
	switch (place.showCmd)
	{
	case SW_SHOWMAXIMIZED:
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		break;
	case SW_SHOWMINIMIZED:
		ShowWindow(hwnd, SW_RESTORE);
		break;
	default:
		ShowWindow(hwnd, SW_NORMAL);
		break;
	}
	SetWindowPos(0, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
	SetForegroundWindow(hwnd);
}

boolean isContainedInUserFunction(char variable[DIM]) {
	FILE *file = NULL;
	char option[30] = "", directory[DIM] = "";
	sprintf(directory, "%s\\User functions\\", atcPath);
	int k = 0, numFiles = 0, i = 0, numFilesSolved = 0;
	DIR *d;
	int retry = 0;
	struct dirent *dir;
	d = opendir(directory);
	char filename[DIM] = "";
	char txtFiles[DIM] = "";
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_type == DT_REG)
			{
				sprintf(filename, "%s", dir->d_name);
				if (searchExtension(filename, ".txt")) {
					int h = abs((int)strlen(filename)) - 1;
					if (isContained(".txt", filename)) {
						filename[strStart] = '\0';
						if (isContained(variable, filename) || isEqual(variable, filename)) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
