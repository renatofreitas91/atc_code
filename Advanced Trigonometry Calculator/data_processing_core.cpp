#include "stdafx.h"
HANDLE hStdin;
DWORD fdwSaveOldMode;
int strStart = 0, strEnd = 0, Pressed = 0;
char* dimensionsTxt = getDynamicCharArray("", "dimensionsTxt"), * windowTxt = getDynamicCharArray("", "windowTxt");
// Usamos dois asteriscos (**) porque getDynamic2DDoubleArray() aloca uma matriz 2D
PrecisionValue** vectorR = nullptr;
PrecisionValue** vectorI =nullptr;
using namespace std;
char* saveVariablesTextFile = getDynamicCharArray("", "saveVariablesTextFile");
char* saveRenamedVariablesTextFile = getDynamicCharArray("", "saveRenamedVariablesTextFile");
char* saveTxtVariablesTextFile = getDynamicCharArray("", "saveTxtVariablesTextFile");
char* saveRenamedTxtVariablesTextFile = getDynamicCharArray("", "saveRenamedTxtVariablesTextFile");
char* saveScriptRenamedVariablesTextFile = getDynamicCharArray("", "saveScriptRenamedVariablesTextFile");
char* saveScriptVariablesTextFile = getDynamicCharArray("", "saveScriptVariablesTextFile");
char* saveUserFunctionsRenamedVariablesTextFile = getDynamicCharArray("", "saveUserFunctionsRenamedVariablesTextFile");
char* saveUserFunctionsVariablesTextFile = getDynamicCharArray("", "saveUserFunctionsVariablesTextFile");
char* numSys = getDynamicCharArray("", "numSys");
char* stringF = getDynamicCharArray("", "stringF");
char* resp = getDynamicCharArray("", "resp"), * respR = getDynamicCharArray("", "respR"), * respI = getDynamicCharArray("", "respI");
char** splitResult;
bool variableControllersUsed = true, notUseHigherPrecison = false, useForVariables = false;

template <typename T>
size_t returnDynamicArraySize(int level) {
	return (size_t)(pot((T)level, (T)level, 1));
}

void putsAndPause(char* text) {
	//puts(text);
//	system("pause");
}
void restoreWindowPosition() {
	char* path = getDynamicCharArray("", "path");
	sprintf(path, "%s\\window.txt", atcPath);

	FILE* file = fopen(path, "r");
	if (file == nullptr) {
		_delete(path, "path");
		return;
	}

	int x = 0, y = 0, width = 0, height = 0;
	if (fscanf(file, "%d\n%d\n%d\n%d\n", &x, &y, &width, &height) != 4) {
		fclose(file);
		_delete(path, "path");
		return;
	}
	fclose(file);

	HWND hwnd = GetConsoleWindow();

	applyConsoleDimensionsSafe(width / 8, 2000);
	applyConsoleWindowSafe(x, y, width, height);
	Sleep(100);

	_delete(path, "path");
}

template <typename T>

void higherPrecisionController(int requestedState) {
	FILE* open = NULL;
	int state = requestedState;
	while (state != 1 && state != 0) {
		I_O = true;
		printf("Enable -> 1\nDisable -> 0\n");
		state = (int)getValue<T>();
		if (state != 1 && state != 0) {
			printf("Error, incorrect choice.\n");
		}
	}
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\higherPrecision.txt", atcPath);
	open = fopen(toOpen, "w");
	if (open != NULL) {
		fprintf(open, "%d", state);
		fclose(open);
		higherPrecision = state;
		if (state == 1) {
			printf("\nHigher Precision saved: Boost mp_float will be used after restarting ATC.\n");
		}
		else {
			printf("\nHigher Precision saved: double will be used after restarting ATC.\n");
		}
	}
	else {
		printf("\nError: unable to save higher precision setting.\n");
	}
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
}

template <typename T>
void numSystemsController() {
	FILE* open;
	int state = -1;
	while (state != 1 && state != 0) {
		I_O = true;
		printf("Enable -> 1\nDisable -> 0\n");
		state = (int)getValue<T>();
		if (state != 1 && state != 0) {
			printf("Error, incorrect choice.\n");
		}
	}
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\numSystems.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d", state);
	sprintf(numSys, "%d", state);
	fclose(open);
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
}

 void setMemFactor1(float memFactor) {
	FILE* open;
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\memFactor.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%f", memFactor);
	fclose(open);
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
	char* path4ATC = getDynamicCharArray("", "path4ATC");
	sprintf(path4ATC, "");
	sprintf(path4ATC, "%s\\atc.exe", atcPath);
	using namespace std;
	std::string s = string(path4ATC);
	std::wstring stemp = std::wstring(s.begin(), s.end());
	LPCWSTR sw = stemp.c_str();
	_delete(path4ATC, "path4ATC");
	path4ATC = nullptr;
	int decision = -1;
	do {
		printf("\nATC needs to be restarted to apply the new memory factory.\nDo you want do it right now? (Yes-> 1 \\ No -> 0)\n");
		scanf("%d", &decision);
	} while (decision != 0 && decision != 1);
	if (decision == 1) {
		ShellExecute(NULL, _T("open"), sw, NULL, NULL, SW_SHOW);
		exit(0);
	}
	else {
		puts("\nThe new memory factor will be applied when ATC has been restarted.\n");
	}
}
 float getMemFactor1() {
	FILE* open;
	float memFactor = 1.0;
	char* toOpen = getDynamicCharArray("", "toOpen");
	getATCPath();
	sprintf(toOpen, "%s\\memFactor.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fscanf(open, "%f", &memFactor);
		fclose(open);
	}
	else{
		memFactor = 1.0; // Default value if file doesn't exist
	}
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
	return memFactor;
}
 template <typename T>
void verboseResolutionController(int requestedState) {
	FILE* open;
	int state = requestedState;
	while (state != 1 && state != 0) {
		I_O = true;
		printf("Enable -> 1\nDisable -> 0\n");
		state = (int)getValue<T>();
		if (state != 1 && state != 0) {
			printf("Error, incorrect choice.\n");
		}
	}
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\verboseResolution.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d", state);
	sprintf(verboseRes, "%d", state);
	verbose = 0;
	fclose(open);
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
}

template <typename T>
void siPrefixController() {
	FILE* open;
	int state = -1;
	while (state != 1 && state != 0) {
		I_O = true;
		printf("Enable -> 1\nDisable -> 0\n");
		state = (int)getValue<T>();
		if (state != 1 && state != 0) {
			printf("Error, incorrect choice.\n");
		}
	}
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\siPrefixes.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d", state);
	sprintf(siPref, "%d", state);
	fclose(open);
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
}
template <typename T>
static std::string formatVariableScalarValue(T value) {
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(17) << precisionValueTo<double>(value);
	std::string text = stream.str();
	if (text.find('.') != std::string::npos) {
		while (!text.empty() && text[text.size() - 1] == '0') {
			text.erase(text.size() - 1);
		}
		if (!text.empty() && text[text.size() - 1] == '.') {
			text.erase(text.size() - 1);
		}
	}
	if (text.empty() || text == "-0") {
		text = "0";
	}
	return text;
}
template <typename T>
static std::string formatVariableScalarExpressionValue(T value) {
	std::string text = formatVariableScalarValue(value);
	if (!text.empty() && text[0] == '-') {
		text[0] = '_';
	}
	return text;
}
template<typename T>
void actualTimeController() {
	FILE* open;
	int state = -1;
	while (state != 1 && state != 0) {
		I_O = true;
		printf("Enable -> 1\nDisable -> 0\n");
		state = (int)getValue<T>();
		if (state != 1 && state != 0) {
			printf("Error, incorrect choice.\n");
		}
	}
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\actualTime.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d", state);
	sprintf(actualTime, "%d", state);
	fclose(open);
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
}
void variableController(char* variable) {
	variableControllersUsed = false;
	if (abs((int)strlen(variable)) > 0) {
		char* saveExpression = getDynamicCharArray("", "saveExpression");

		if (!runningScript || !haveCreatedDynamicMatrix) {
			sprintf(saveExpression, "%s", expressionF);
			replaceTimes = 0;
			while (isContained(";", saveExpression) || isContained("\\", saveExpression)) {
				if (isContained("+", saveExpression)) {
					replace("+", " ", saveExpression);
					sprintf(saveExpression, "%s", expressionF);
				}
				if (isContained("i", saveExpression)) {
					replace("i", "", saveExpression);
					sprintf(saveExpression, "%s", expressionF);
				}
				if (isContained("\\", saveExpression)) {
					replace("\\", ":", saveExpression);
					sprintf(saveExpression, "%s", expressionF);
				}
				if (isContained(";", saveExpression)) {
					replace(";", "*", saveExpression);
					sprintf(saveExpression, "%s", expressionF);
				}

			}
			sprintf(expressionF, "");
		}
		FILE* open = NULL;
		char* va = getDynamicCharArray("", "va");
		char* vari = getDynamicCharArray("", "vari");
		int i = 0, f = 0;
		vari[0] = '\0';
		int y = 0, h = 0, k = 0, g = 0;
		bool defaultVariable = false;
		if (isEqual(context, "main")) {
			sprintf(vari, "%s", saveVariablesTextFile);
			defaultVariable = true;
		}
		if (isEqual(context, "processTxt")) {
			sprintf(vari, "%s", saveTxtVariablesTextFile);
			defaultVariable = true;
		}
		if (isEqual(context, "script")) {
			sprintf(vari, "%s", saveScriptVariablesTextFile);
			defaultVariable = true;
		}
		if (isEqual(context, "userFunctions")) {
			sprintf(vari, "%s", saveUserFunctionsVariablesTextFile);
			defaultVariable = true;
		}

		if (!defaultVariable) {
			char* toOpen = getDynamicCharArray("", "toOpen");
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
				open = fopen(toOpen, "r");
				i++;
			}
			_delete(toOpen, "toOpen");
			toOpen = nullptr;
		}
		if (i < 100) {
			if (!defaultVariable) {
				for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
				fclose(open);
				vari[i] = '\0';
			}



			sprintf(expressionF, "\n%s ", variable);
			char* toSearch_1 = getDynamicCharArray(expressionF, "toSearch_1");
			char* toSearch_2 = getDynamicCharArray(variable, "toSearch_2");
			if (isContained(toSearch_1, vari)) {
				variableControllersUsed = true;
				int i = strStart + 1;
				int h = 0;
				char* variableData = getDynamicCharArray("", "variableData");
				while (vari[i] != '\n' && i < abs((int)strlen(vari))) {
					variableData[h] = vari[i];
					h++;
					i++;
				}

				variableData[h] = '\n'; variableData[h + 1] = '\0';


				replaceTimes = 1;
				if (isContained(variableData, vari)) {
					replace(variableData, "", vari);
					sprintf(vari, "%s", expressionF);
				}
				_delete(variableData, "variableData");
				replaceTimes = 0;
			}
			else {
				if (isContained(toSearch_2, vari) && strStart == 0) {
					variableControllersUsed = true;
					int i = strStart;
					int h = 0;
					char* variableData = getDynamicCharArray("", "variableData");
					while (vari[i] != '\n' && i < abs((int)strlen(vari))) {
						variableData[h] = vari[i];
						h++;
						i++;
					}

					variableData[h] = '\n'; variableData[h + 1] = '\0';


					replaceTimes = 1;
					if (isContained(variableData, vari)) {
						replace(variableData, "", vari);
						sprintf(vari, "%s", expressionF);
					}
					replaceTimes = 0;
					_delete(variableData, "variableData");
				}
			}
			if (!defaultVariable) {
				char* toOpen = getDynamicCharArray("", "toOpen");
				sprintf(toOpen, "%s\\variables.txt", atcPath);
				open = NULL;
				while (open == NULL) {
					open = fopen(toOpen, "w");
				}
				_delete(toOpen, "toOpen");
				toOpen = nullptr;
			}
			if ((isContained("*", saveExpression) || isContained(":", saveExpression)) && (!runningScript || !haveCreatedDynamicMatrix)) {
				sprintf(vari, "%s%s %s\n", vari, variable, saveExpression);
				sprintf(saveExpression, "");
				sprintf(expressionF, "");
			}
			else {
				std::string realVariableValue = formatVariableScalarValue(resultR);
				std::string imagVariableValue = formatVariableScalarValue(resultI);
				sprintf(vari, "%s%s %s %s\n", vari, variable, realVariableValue.c_str(), imagVariableValue.c_str());
				sprintf(saveExpression, "");
				sprintf(expressionF, "");
			}
			if (!defaultVariable) {
				fputs(vari, open);
				fclose(open);
			}
			else {
				if (isEqual(context, "main")) {
					sprintf(saveVariablesTextFile, "%s", vari);
				}

				if (isEqual(context, "processTxt")) {
					sprintf(saveTxtVariablesTextFile, "%s", vari);
				}

				if (isEqual(context, "script")) {
					sprintf(saveScriptVariablesTextFile, "%s", vari);
				}
				if (isEqual(context, "userFunctions")) {
					sprintf(saveUserFunctionsVariablesTextFile, "%s", vari);
				}
				if (!defaultVariable) {
					if (open != NULL) {
						fputs(vari, open);
						fclose(open);
					}
				}

			}
			_delete(toSearch_1, "toSearch_1"); toSearch_1 = nullptr;
			_delete(toSearch_2, "toSearch_2"); toSearch_2 = nullptr;

		}
		_delete(va, "va");
		_delete(vari, "vari");

		_delete(saveExpression, "saveExpression");
		saveExpression = nullptr;


	}

}

template <typename T>
void prefixDeterminator(T n, char* path) {
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\history.txt", atcPath);
	T result = 0;
	FILE* open;
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
		fprintf(open, "=%sy (yocto-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sy (yocto-)\n", convert2Exponential(result));
		}
		break;
	case 'B':
		result = n / 1E-21;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sz (zepto-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sz (zepto-)\n", convert2Exponential(result));
		}
		break;
	case 'C':
		result = n / 1E-18;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sa (atto-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sa (atto-)\n", convert2Exponential(result));
		}
		break;
	case 'D':
		result = n / 1E-15;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sf (femto-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sf (femto-)\n", convert2Exponential(result));
		}
		break;
	case 'E':
		result = n / 1E-12;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sp (pico-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sp (pico-)\n", convert2Exponential(result));
		}
		break;
	case 'F':
		result = n / 1E-9;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sn (nano-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sn (nano-)\n", convert2Exponential(result));
		}
		break;
	case 'G':
		result = n / 1E-6;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sµ (micro-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%s%c (micro-)\n", convert2Exponential(result), 230);
		}
		break;
	case 'H':
		result = n / 1E-3;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sm (milli-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sm (milli-)\n", convert2Exponential(result));
		}
		break;
	case 'I':
		result = n / 1E-2;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sc (centi-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sc (centi-)\n", convert2Exponential(result));
		}
		break;
	case 'J':
		result = n / 1E-1;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sd (deci-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sd (deci-)\n", convert2Exponential(result));
		}
		break;
	case 'K':
		result = n / 1E1;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sda (deca-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sda (deca-)\n", convert2Exponential(result));
		}
		break;
	case 'L':
		result = n / 1E2;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sh (hecto-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sh (hecto-)\n", convert2Exponential(result));
		}
		break;
	case 'M':
		result = n / 1E3;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sk (kilo-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sk (kilo-)\n", convert2Exponential(result));
		}
		break;
	case 'N':
		result = n / 1E6;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sM (mega-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sM (mega-)\n", convert2Exponential(result));
		}
		break;
	case 'O':
		result = n / 1E9;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sG (giga-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sG (giga-)\n", convert2Exponential(result));
		}
		break;
	case 'P':
		result = n / 1E12;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sT (tera-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sT (tera-)\n", convert2Exponential(result));
		}
		break;
	case 'Q':
		result = n / 1E15;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sP (peta-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sP (peta-)\n", convert2Exponential(result));
		}
		break;
	case 'R':
		result = n / 1E18;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sE (exa-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sE (exa-)\n", convert2Exponential(result));
		}
		break;
	case 'S':
		result = n / 1E21;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sZ (zetta-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sZ (zetta-)\n", convert2Exponential(result));
		}
		break;
	case 'T':
		result = n / 1E24;
		if (y == 1) {
			result = result * -1;
		}
		fprintf(open, "=%sY (yotta-)\n", convert2Exponential(result));
		if (a == 1) {
			printf("=%sY (yotta-)\n", convert2Exponential(result));
		}
		break;
	default:
		break;
	}
	fclose(open);
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
}

void replace(char* toReplace, char* replacement, char* string) {
	char* expression = getDynamicCharArray("", "expression"); char* expressionG = getDynamicCharArray("", "expressionG");
	char* check_for_variable = getDynamicCharArray("", "check_for_variable");
	int i = 0, g = 0, j = 0, is_variable = 0, k = 0, n = 0;
	sprintf(expression, "%s", string);
	sprintf(expressionG, "%s", string);
	if (isContained(toReplace, expressionG)) {
		if (replaceTimes == 0) {
			do {
				i = strStart; j = 0;
				while (j < abs((int)strlen(replacement)) && i < DIM)
				{
					expression[i] = replacement[j];
					i++; j++;
				}
				g = strEnd;
				while (g < abs((int)strlen(expressionG)) && g < DIM && i < DIM) {
					expression[i] = expressionG[g];
					g++;
					i++;
				}
				if (i < DIM) {
					expression[i] = '\0';
				}
				sprintf(expressionG, "%s", expression);
			} while (isContained(toReplace, expressionG) && i < DIM && g < DIM);
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
			while (g < abs((int)strlen(expressionG)) && g < DIM && i < DIM) {
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
	else {
		sprintf(expressionF, "%s", expression);
	}
	_delete(expression, "expression");
	expression = nullptr;
	_delete(expressionG, "expressionG");
	expressionG = nullptr;
	if (check_for_variable != nullptr) {
		_delete(check_for_variable, "check_for_variable");
		check_for_variable = nullptr;
	}
}
void replaceLong(char* toReplace, char* replacement, char* string) {
	char* expression = getDynamicCharArrayLong(""); char* expressionG = getDynamicCharArrayLong("");
	char* check_for_variable = getDynamicCharArrayLong("");
	int i = 0, g = 0, j = 0, is_variable = 0, k = 0, n = 0;
	sprintf(expression, "%s", string);
	sprintf(expressionG, "%s", string);
	if (isContained(toReplace, expressionG)) {
		if (replaceTimes == 0) {
			do {
				i = strStart; j = 0;
				while (j < abs((int)strlen(replacement)) && i < DIM)
				{
					expression[i] = replacement[j];
					i++; j++;
				}
				g = strEnd;
				while (g < abs((int)strlen(expressionG)) && g < DIM && i < DIM) {
					expression[i] = expressionG[g];
					g++;
					i++;
				}
				if (i < DIM) {
					expression[i] = '\0';
				}
				sprintf(expressionG, "%s", expression);
			} while (isContained(toReplace, expressionG) && i < DIM && g < DIM);
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
			while (g < abs((int)strlen(expressionG)) && g < DIM && i < DIM) {
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
	else {
		sprintf(expressionF, "%s", expression);
	}
	_deleteLong(expression, "expression");
	expression = nullptr;
	_deleteLong(expressionG, "expressionG");
	expressionG = nullptr;
	if (check_for_variable != nullptr) {
		_deleteLong(check_for_variable, "check_for_variable");
		check_for_variable = nullptr;
	}
}
void replaceByIndex(char* toReplace, char* replacement, char* string, int index) {
	char* expression = getDynamicCharArray("", "expression"); char* expressionG = getDynamicCharArray("", "expressionG");
	char* check_for_variable = getDynamicCharArray("", "check_for_variable");
	int i = 0, g = 0, j = 0, is_variable = 0, k = 0, n = 0;
	sprintf(expression, "%s", string);
	sprintf(expressionG, "%s", string);
	if (isContainedByIndex(toReplace, expressionG, index)) {
		if (replaceTimes == 0) {
			do {
				i = strStart; j = 0;
				while (j < abs((int)strlen(replacement)) && i < DIM)
				{
					expression[i] = replacement[j];
					i++; j++;
				}
				g = strEnd;
				while (g < abs((int)strlen(expressionG)) && g < DIM && i < DIM) {
					expression[i] = expressionG[g];
					g++;
					i++;
				}
				if (i < DIM) {
					expression[i] = '\0';
				}
				sprintf(expressionG, "%s", expression);
			} while (isContainedByIndex(toReplace, expressionG, index) && i < DIM && g < DIM);
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
			while (g < abs((int)strlen(expressionG)) && g < DIM && i < DIM) {
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
	else {
		sprintf(expressionF, "%s", expression);
	}
	_delete(expression, "expression");
	expression = nullptr;
	_delete(expressionG, "expressionG");
	expressionG = nullptr;
	if (check_for_variable != nullptr) {
		_delete(check_for_variable, "check_for_variable");
		check_for_variable = nullptr;
	}
}

void renamer(char* expression) {
	sprintf(expressionF, "");
	expressionF[0] = '\0';
	char* varLetters = getDynamicCharArray("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", "varLetters");
	char* varToRename = getDynamicCharArray("  ", "varToRename");
	int j = 0, k = 0, sd = 0, i = 0;
	for (k = 0; k < abs((int)strlen(expression)); k++) {
		for (i = 0; i < abs((int)strlen(varLetters)); i++) {
			if (expression[k] == varLetters[i]) {
				varToRename[j] = expression[k];
				j++;
				break;
			}
		}
		if (j > 0 && expression[k] != varLetters[i] && k < abs((int)strlen(expression))) {
			varToRename[j] = '\0';
			varRename[0] = '\0';
			variableRenamer(varToRename);
			varToRename[0] = '\0';
			sd = k - j;
			j = 0;
			while (j < abs((int)strlen(varRename))) {
				expression[sd] = varRename[j];
				j++; sd++;
			}
			j = 0;
		}
	}
	for (i = 0; i < abs((int)strlen(expression)) && i < abs((int)strlen(expression)) && i < DIM; i++) {
		expressionF[i] = expression[i];
	}
	expressionF[i] = '\0';
	_delete(varLetters, "varLetters");
	varLetters = nullptr;
	_delete(varToRename, "varToRename");
	varToRename = nullptr;
}

void variableRenamer(char* variable) {
	valRenamedVar = 0;
	sprintf(varRename, "");
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\renamedVar.txt", atcPath);

	char* vari = getDynamicCharArray("", "vari");
	int i = 0, j = 0;
	bool defaultVariable = false;
	if (isEqual(context, "main")) {
		sprintf(vari, "%s", saveRenamedVariablesTextFile);
		defaultVariable = true;
	}
	if (isEqual(context, "processTxt")) {
		sprintf(vari, "%s", saveRenamedTxtVariablesTextFile);
		defaultVariable = true;
	}
	if (isEqual(context, "script")) {
		sprintf(vari, "%s", saveScriptRenamedVariablesTextFile);
		defaultVariable = true;
	}
	if (isEqual(context, "userFunctions")) {
		sprintf(vari, "%s", saveUserFunctionsRenamedVariablesTextFile);
		defaultVariable = true;
	}
	if (!defaultVariable) {
		FILE* open = NULL;

		while (open == NULL && i < 50) {
			open = fopen(toOpen, "a+");
			i++;
		}
		if (open != NULL) {
			for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
			vari[i] = '\0';
			fclose(open);
		}
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
	}
	for (i = 0; i < abs((int)strlen(vari)); i++) {
		j = 0;
		if (variable[j] == vari[i] && (i == 0 || vari[i - 1] == '\n')) {
			while (variable[j] == vari[i] && i < abs((int)strlen(vari))) {
				j++; i++;
			}
			if (abs((int)strlen(variable)) == j) {
				if (variable[j] == '\0' && vari[i] == ' ') {
					valRenamedVar = 1;
					i++;
					j = 0;
					while (vari[i] != '\n' && i < abs((int)strlen(vari))) {
						varRename[j] = vari[i];
						j++; i++;
					}
					varRename[j] = '\0';
				}
			}
		}
	}
	if (valRenamedVar != 1 && abs((int)strlen(saveRenamedVariablesTextFile)) > 0) {
		sprintf(vari, "%s", saveRenamedVariablesTextFile);
		for (i = 0; i < abs((int)strlen(vari)); i++) {
			j = 0;
			if (variable[j] == vari[i] && (i == 0 || vari[i - 1] == '\n')) {
				while (variable[j] == vari[i] && i < abs((int)strlen(vari))) {
					j++; i++;
				}
				if (abs((int)strlen(variable)) == j) {
					if (variable[j] == '\0' && vari[i] == ' ') {
						valRenamedVar = 1;
						i++;
						j = 0;
						while (vari[i] != '\n' && i < abs((int)strlen(vari))) {
							varRename[j] = vari[i];
							j++; i++;
						}
						varRename[j] = '\0';
					}
				}
			}
		}
	}
	_delete(vari, "vari");
	_delete(toOpen, "toOpen");
}


void pathNameToPath(char* pathName) {
	FILE* open = NULL;
	int i = 0, j = 0, k = 0;
	pathNAme[0] = '\0';
	char* data = getDynamicCharArray("", "data");
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\pathName.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open == NULL) {
		puts("\n==> No path abbreviation created! <==\n");
	}
	else {
		for (i = 0; (data[i] = fgetc(open)) != EOF; i++);
		fclose(open);
		for (i = 0; i < abs((int)strlen(data)); i++) {
			if (data[i] == pathName[j] && (data[i - 1] == '\n' || i == 0)) {
				while (data[i] == pathName[j]) {
					j++;
					i++;
				}
				if (j == abs((int)strlen(pathName)) && data[i] == ' ') {
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
		if (abs((int)strlen(pathNAme)) == 0) {
			puts("\n==> This path abbreviation not exist! <==\n");
		}
	}
	_delete(data, "data");
	data = nullptr;
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
}

void pathNameController(char* pathName, char* path) {
	FILE* save = NULL;
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\pathName.txt", atcPath);
	while (save == NULL) {
		save = fopen(toOpen, "a+");
	}
	char* data = getDynamicCharArray("", "data"); char* paName = getDynamicCharArray("", "paName");
	int i = 0, j = 0, k = 0, y = 0, w = 0, l = 0;
	for (i = 0; (data[i] = fgetc(save)) != EOF; i++);
	data[i] = '\0';
	for (i = 0; i < abs((int)strlen(data)); i++) {
		if (data[i] == pathName[j] && (data[i - 1] == '\n' || i == 0)) {
			y = i;
			while (data[i] == pathName[j]) {
				j++;
				i++;
			}
			if (j == abs((int)strlen(pathName)) && data[i] == ' ') {
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
	_delete(data, "data");
	data = nullptr;
	_delete(paName, "paName");
	paName = nullptr;
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
}

void stringVariableToString(char* stringVariable) {
	variableRenamer(stringVariable);
	if (valRenamedVar == 1) {
		sprintf(stringVariable, "%s", varRename);
	}
	validVar = 1;
	FILE* open = NULL;
	int i = 0, j = 0, k = 0;
	variableSTring[0] = '\0';
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\stringVariable.txt", atcPath);
	char* data = getDynamicCharArray("", "data");

	open = fopen(toOpen, "r");
	if (open == NULL) {
		puts("\n==> No string variable created! <==\n");
		validVar = 0;
	}
	else {
		for (i = 0; (data[i] = fgetc(open)) != EOF; i++);
		data[i] = '\0';
		fclose(open);
		for (i = 0; i < abs((int)strlen(data)); i++) {
			j = 0;
			if (data[i] == stringVariable[j] && j == 0) {
				while (data[i] == stringVariable[j]) {
					j++;
					i++;
				}
				if (j == abs((int)strlen(stringVariable))) {
					validVar = 1;
					char* directory = getDynamicCharArray("", "directory");
					sprintf(directory, "%s\\Strings\\%s.txt", atcPath, stringVariable);
					open = fopen(directory, "a+");
					if (open != NULL) {
						for (k = 0; (variableSTring[k] = fgetc(open)) != EOF; k++);
						variableSTring[k] = '\0';
						fclose(open);
					}
					_delete(directory, "directory");
					directory = nullptr;
				}
			}
		}

		if (!isContained(stringVariable, data)) {
			puts(stringVariable);

			puts("\n==> This string variable doesn't exist! <==\n");
			validVar = 0;
		}
	}
	if (validVar != 1) {
		sprintf(toOpen, "%s\\stringVariable.txt", saveATCPath);
		open = fopen(toOpen, "r");
		if (open == NULL) {
			puts("\n==> No string variable created! <==\n");
			validVar = 0;
		}
		else {
			for (i = 0; (data[i] = fgetc(open)) != EOF; i++);
			data[i] = '\0';
			fclose(open);
			for (i = 0; i < abs((int)strlen(data)); i++) {
				j = 0;
				if (data[i] == stringVariable[j] && j == 0) {
					while (data[i] == stringVariable[j]) {
						j++;
						i++;
					}
					if (j == abs((int)strlen(stringVariable))) {
						validVar = 1;
						char* directory = getDynamicCharArray("", "directory");
						sprintf(directory, "%s\\Strings\\%s.txt", atcPath, stringVariable);
						open = fopen(directory, "a+");
						if (open != NULL) {
							for (k = 0; (variableSTring[k] = fgetc(open)) != EOF; k++);
							variableSTring[k] = '\0';
							fclose(open);
						}
						_delete(directory, "directory");
						directory = nullptr;
					}
				}
			}

			if (!isContained(stringVariable, data)) {
				puts(stringVariable);
				puts("\n==> This string variable doesn't exist! <==\n");
				validVar = 0;
			}
		}
	}
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
	_delete(data, "data");
	data = nullptr;
}


void stringVariableController(char* variable, char* string) {
	FILE* open = NULL;
	char* va = getDynamicCharArray("", "va");
	int i = 0, f = 0;
	int y = 0, h = 0, k = 0, g = 0;
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\stringVariable.txt", atcPath);
	char* vari = getDynamicCharArray("", "vari");

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
		char* toSearch_1 = getDynamicCharArray("", "toSearch_1");
		sprintf(toSearch_1, "\n%s\n", variable);
		char* toSearch_2 = getDynamicCharArray("", "toSearch_2");
		sprintf(toSearch_2, "%s\n", variable);
		if (isContained(toSearch_1, vari)) {
			int i = strStart + 1;
			int h = 0;
			char* variableData = getDynamicCharArray("", "variableData");
			while (vari[i] != '\n' && i < abs((int)strlen(vari))) {
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
			_delete(variableData, "variableData");
			variableData = nullptr;
		}
		else {
			if (isContained(toSearch_2, vari)) {
				int i = strStart;
				int h = 0;
				char* variableData = getDynamicCharArray("", "variableData");
				while (vari[i] != '\n' && i < abs((int)strlen(vari))) {
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
				_delete(variableData, "variableData");
				variableData = nullptr;
			}
		}
		open = NULL;
		while (open == NULL) {
			open = fopen(toOpen, "a+");
		}
		fprintf(open, "%s\n", variable);
		fclose(open);
		char* directory = getDynamicCharArray("", "directory");
		sprintf(directory, "%s\\Strings\\%s.txt", atcPath, variable);
		open = fopen(directory, "w");
		if (open != NULL) {
			fputs(string, open);
			fclose(open);
		}
		_delete(toSearch_1, "toSearch_1");
		toSearch_1 = nullptr;
		_delete(toSearch_2, "toSearch_2");
		toSearch_2 = nullptr;
		_delete(directory, "directory");
		directory = nullptr;
	}
	_delete(va, "va");
	va = nullptr;
	_delete(vari, "vari");
	vari = nullptr;
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
}
bool isInsideDelimitedFunctionHeader(const char* expression, int index) {
	if (expression == nullptr || index < 0) return false;
	int len = abs((int)strlen(expression));
	if (index >= len) return false;
	for (int start = index; start >= 0; start--) {
		if (strncmp(&expression[start], "rtD", 3) == 0) {
			int cursor = start + 3;
			while (cursor < len && expression[cursor] != '(' && expression[cursor] != '\0') {
				if (expression[cursor] == 'D') {
					return index >= start && index <= cursor;
				}
				cursor++;
			}
		}
		if (strncmp(&expression[start], "logb", 4) == 0) {
			int cursor = start + 4;
			while (cursor < len && expression[cursor] != '(' && expression[cursor] != '\0') {
				if (expression[cursor] == 'b') {
					return index >= start && index <= cursor;
				}
				cursor++;
			}
		}
		if (expression[start] == '(' || expression[start] == ')' || expression[start] == '+' || expression[start] == '-' || expression[start] == '*' || expression[start] == '/' || expression[start] == '^' || expression[start] == '\\') {
			break;
		}
	}
	return false;
}
template<typename T>
void substituteExistingScalarVariables(char* expression) {
	PrecisionValue savedResultR = resultR;
	PrecisionValue savedResultI = resultI;
	char* savedMatrixValue = getDynamicCharArray(matrixValue, "savedMatrixValue");
	char* rebuilt = getDynamicCharArray("", "rebuilt");
	char* variable = getDynamicCharArray("", "variable");
	int i = 0;
	while (i < abs((int)strlen(expression))) {
		if (verifyLetter(expression[i]) && (i == 0 || !verifyLetter(expression[i - 1])) && !isInsideDelimitedFunctionHeader(expression, i)) {
			int start = i;
			int v = 0;
			while (verifyLetter(expression[i]) && i < abs((int)strlen(expression)) && !isInsideDelimitedFunctionHeader(expression, i)) {
				variable[v] = expression[i];
				v++; i++;
			}
			variable[v] = '\0';
			if (start == 0 && expression[i] == '=') {
				sprintf(rebuilt, "%s%s", rebuilt, variable);
				continue;
			}
			sprintf(matrixValue, "");
			processVariable<T>(variable);
			if (validVar == 1 && abs((int)strlen(matrixValue)) == 0) {
				std::string realVariableValue = formatVariableScalarExpressionValue(resultR);
				std::string imagVariableValue = formatVariableScalarExpressionValue(resultI);
				if (precisionValueTo<double>(resultI) == 0.0) {
					sprintf(rebuilt, "%s(%s)", rebuilt, realVariableValue.c_str());
				}
				else {
					if (precisionValueTo<double>(resultI) >= 0.0) {
						sprintf(rebuilt, "%s(%s+%si)", rebuilt, realVariableValue.c_str(), imagVariableValue.c_str());
					}
					else {
						sprintf(rebuilt, "%s(%s%si)", rebuilt, realVariableValue.c_str(), imagVariableValue.c_str());
					}
				}
			}
			else {
				sprintf(rebuilt, "%s%s", rebuilt, variable);
			}
		}
		else {
			int len = abs((int)strlen(rebuilt));
			rebuilt[len] = expression[i];
			rebuilt[len + 1] = '\0';
			i++;
		}
	}
	sprintf(expression, "%s", rebuilt);
	sprintf(expressionF, "%s", expression);
	resultR = savedResultR;
	resultI = savedResultI;
	sprintf(matrixValue, "%s", savedMatrixValue);
	_delete(savedMatrixValue, "savedMatrixValue"); savedMatrixValue = nullptr;
	_delete(rebuilt, "rebuilt"); rebuilt = nullptr;
	_delete(variable, "variable"); variable = nullptr;
}
void expandDelimitedFunctionSyntax(char* expression) {
	char* rebuilt = getDynamicCharArray("", "rebuilt");
	char* base = getDynamicCharArray("", "base");
	char* argument = getDynamicCharArray("", "argument");
	int i = 0;
	while (i < abs((int)strlen(expression))) {
		if (strncmp(&expression[i], "rtD", 3) == 0 || strncmp(&expression[i], "logb", 4) == 0) {
			bool isRoot = strncmp(&expression[i], "rtD", 3) == 0;
			int baseStart = i + (isRoot ? 3 : 4);
			int delimiter = baseStart;
			char delimiterChar = isRoot ? 'D' : 'b';
			while (expression[delimiter] != '\0' && expression[delimiter] != delimiterChar && expression[delimiter] != '(') {
				delimiter++;
			}
			if (expression[delimiter] == delimiterChar && expression[delimiter + 1] == '(') {
				int b = 0;
				for (int c = baseStart; c < delimiter; c++) {
					base[b] = expression[c];
					b++;
				}
				base[b] = '\0';
				int open = delimiter + 1;
				int close = open;
				int depth = 0;
				while (expression[close] != '\0') {
					if (expression[close] == '(') depth++;
					if (expression[close] == ')') {
						depth--;
						if (depth == 0) break;
					}
					close++;
				}
				if (expression[close] == ')') {
					int a = 0;
					for (int c = open + 1; c < close; c++) {
						argument[a] = expression[c];
						a++;
					}
					argument[a] = '\0';
					if (isRoot) {
						sprintf(rebuilt, "%s((%s)^(1/(%s)))", rebuilt, argument, base);
					}
					else {
						sprintf(rebuilt, "%s(ln(%s)/ln(%s))", rebuilt, argument, base);
					}
					i = close + 1;
					continue;
				}
			}
		}
		int len = abs((int)strlen(rebuilt));
		rebuilt[len] = expression[i];
		rebuilt[len + 1] = '\0';
		i++;
	}
	sprintf(expression, "%s", rebuilt);
	sprintf(expressionF, "%s", expression);
	_delete(rebuilt, "rebuilt"); rebuilt = nullptr;
	_delete(base, "base"); base = nullptr;
	_delete(argument, "argument"); argument = nullptr;
}
template<typename T>
void variableToMultiply(char* expression) {
	int i = 0, j = 0, k = 0, v = -7, u = 0, d = 0, l = 0;
	char* variable = getDynamicCharArray("", "variable"); char* saveVariable = getDynamicCharArray("", "saveVariable");
	if (!isContained("[", expression)) {
		while (i < abs((int)strlen(expression))) {
			v = -7;
			if ((strncmp(&expression[i], "rtD", 3) == 0) || (strncmp(&expression[i], "logb", 4) == 0)) {
				while (expression[i] != '(' && expression[i] != '\0') {
					i++;
				}
			}
			if (verifyLetter(expression[i]) && (verifyLetter(expression[i - 1]) == false || i == 0) && !isInsideDelimitedFunctionHeader(expression, i)) {
				j = 0;
				u = i;
				validVar = 0;
				if (verifyLetter(expression[i])) {
					j = 0;
					variable[j] = expression[i];
					variable[j + 1] = '\0';
					while (isContained(variable, expression) && verifyLetter(expression[i])) {
						if (expression[i + 1] != '[') {
							variable[j] = expression[i];
							variable[j + 1] = '\0';
							for (d = 0; d < abs((int)strlen(variable)); d++) {
								saveVariable[d] = variable[d];
							}
							saveVariable[d] = '\0';
							processVariable<T>(variable);
							if (validVar == 0) {
								variableRenamer(variable);
								for (k = 0; k < abs((int)strlen(varRename)); k++) {
									variable[k] = varRename[k];
								}
								variable[k] = '\0';
								processVariable<T>(variable);
							}
							for (d = 0; d < abs((int)strlen(saveVariable)); d++) {
								variable[d] = saveVariable[d];
							}
							variable[d] = '\0';
							if (validVar == 1) {
								l = abs((int)strlen(expression));
								v = i;
							}
							j++; i++;
						}
						else {
							break;
						}
					}
				}
				if (v >= 0) {
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
	}
	int y = 0;
	for (y = 0; y < abs((int)strlen(expression)); y++) {
		expressionF[y] = expression[y];
	}
	expressionF[y] = '\0';
	_delete(variable, "variable");
	variable = nullptr;
	_delete(saveVariable, "saveVariable");
	saveVariable = nullptr;
}
template<typename T>
void toMultiply(char* expression, T result1, T result2) {

	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\variables.txt", atcPath);
	char* vari = getDynamicCharArray("", "vari");
	int i = 0, verify = 0, verifys = 0, j = 0;

	FILE* open;
	bool defaultVariable = false;
	if (isEqual(context, "main")) {
		sprintf(vari, "%s", saveVariablesTextFile);
		defaultVariable = true;
		if (variableControllersUsed || abs((int)strlen(saveVariablesTextFile)) == 0 || abs((int)strlen(saveRenamedVariablesTextFile)) == 0) {

			open = fopen(toOpen, "w");
			if (open != NULL) {
				fprintf(open, "%s", saveVariablesTextFile);
				fclose(open);
			}
			sprintf(toOpen, "%s\\renamedVar.txt", atcPath);
			open = NULL;
			open = fopen(toOpen, "w");
			if (open != NULL) {
				fprintf(open, "%s", saveRenamedVariablesTextFile);
				fclose(open);
			}
			variableControllersUsed = false;
		}
	}
	if (isEqual(context, "processTxt")) {
		sprintf(vari, "%s", saveTxtVariablesTextFile);
		defaultVariable = true;
	}
	if (isEqual(context, "script")) {
		sprintf(vari, "%s", saveScriptVariablesTextFile);
		defaultVariable = true;
	}
	if (isEqual(context, "userFunctions")) {
		sprintf(vari, "%s", saveUserFunctionsVariablesTextFile);
		defaultVariable = true;
	}
	if (!defaultVariable) {
		char* toOpen = getDynamicCharArray("", "toOpen");
		sprintf(toOpen, "%s\\variables.txt", atcPath);
		FILE* open;
		open = fopen(toOpen, "r");
		if (open == NULL) {
			open = fopen(toOpen, "w");
		}
		if (open != NULL) {
			fclose(open);
		}
		open = NULL;
		while (open == NULL && i < 100) {
			open = fopen(toOpen, "r");
			i++;
		}
		if (i < 100) {
			if (!defaultVariable) {
				for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
				fclose(open);
				vari[i] = '\0';
			}
		}
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
	}
	i = 0;
	char** saveSplitResult = new char* [DIMTWOD];

	for (int i = 0; i < DIMTWOD; ++i) {
		saveSplitResult[i] = getDynamicCharArray("", "saveSplitResult[i]");
	}
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
	char** saveLines;
	saveLines = new char* [DIMTWOD];

	for (int i = 0; i < DIMTWOD; ++i) {
		saveLines[i] = getDynamicCharArray("", "saveLines[i]");
		sprintf(saveLines[i], "");
	}
	while (i < countSplits) {
		sprintf(saveLines[i], "%s", splitResult[i]);
		i++;
	}
	countSplits = countOccurrences(" ", saveLines[i]);
	split(" ", saveLines[i]);
	char* variables = getDynamicCharArray("", "variables");
	sprintf(variables, ",");
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


	_Delete(saveSplitResult, DIMTWOD, dime, "saveSplitResult[i]");

	_Delete(saveLines, DIMTWOD, dime, "saveLines[i]");
	saveLines = nullptr;
	i = 0;
	char* value = getDynamicCharArray("", "value"); char* saveValue = getDynamicCharArray("", "saveValue");
	while (i < abs((int)strlen(expression))) {
		if (expression[i] == '+' && expression[i + 1] == '0' && expression[i + 2] == '\0') {
			value[j] = expression[i];
			value[j + 1] = '0'; value[j + 2] = '\0';
			j++; i = i + 2;
		}
		else {
			if (verifyNumber(expression[i])) {
				while (verifyNumber(expression[i]) && i < abs((int)strlen(expression)) || expression[i] == 'i' && expression[i - 1] == '1') {
					value[j] = expression[i];
					value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
					j++; i++;
				}
			}
			else {
				if (verifyLetter(expression[i - 1]) == 0 && firstLetterVariable(expression[i]) && !isInsideDelimitedFunctionHeader(expression, i)) {
					while (verifyLetter(expression[i]) && i < abs((int)strlen(expression)) && !isInsideDelimitedFunctionHeader(expression, i)) {
						value[j] = expression[i];
						j++; i++;
					}
					value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
					synTest = 0;
					if (expression[i] != '[') {
						verify = dataVerifier(value, result1, result2, 0, verify);
					}
				}
				else {
					if (verifyLetter(expression[i - 1]) == 0 && firstLetterFunction(expression[i])) {
						while (verifyLetter(expression[i])) {
							value[j] = expression[i];
							j++; i++;
						}
						value[j] = '+'; value[j + 1] = '0'; value[j + 2] = '\0';
						j++;
						synTest = 0;
						verify = dataVerifier(value, result1, result2, 0, verify);
						while (verify == 0 && i < abs((int)strlen(expression))) {
							if (expression[i] == 'b') {
								value[j] = expression[i];
								j++; i++;
								while ((expression[i] == 'b' && expression[i + 1] == '(') == false && i < abs((int)strlen(expression))) {
									value[j] = expression[i];
									j++; i++;
								}
							}
							else {
								if (expression[i] == 'D') {
									value[j] = expression[i];
									j++; i++;
									while ((expression[i] == 'D' && expression[i + 1] == '(') == false && i < abs((int)strlen(expression))) {
										value[j] = expression[i];
										j++; i++;
									}
								}
								else {
									if (verifyLetter(expression[i])) {
										while (verifyLetter(expression[i])) {
											value[j] = expression[i];
											i++; j++;
										}
									}
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
							while (verifyLetter(expression[i]) == 0 && verifyNumber(expression[i]) == 0 && i < abs((int)strlen(expression))) {
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
								while (verify == 1 && i < abs((int)strlen(expression))) {
									value[j] = expression[i];
									value[j + 1] = '+'; value[j + 2] = '0'; value[j + 3] = '\0';
									synTest = 0;

									verify = dataVerifier(value, result1, result2, 0, verify);

									j++; i++;
								}
								if (verify == 0) {
									value[j - 1] = '+'; value[j] = '0'; value[j + 1] = '\0';
								}
								if (expression[i] != '\\' && expression[i] != '+' && expression[i] != '-' && expression[i] != '*' && expression[i] != '/' && expression[i] != '^' && i < abs((int)strlen(expression))) {
									j--;
									if (expression[i] != '\\' && expression[i - 1] != '+' && expression[i - 1] != '-' && expression[i - 1] != '*' && expression[i - 1] != '/' && expression[i - 1] != '^') {
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
									while (verify == 0 && i < abs((int)strlen(expression))) {
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
									if (expression[i] != '\\' && expression[i] != '+' && expression[i] != '-' && expression[i] != '*' && expression[i] != '/' && expression[i] != '^' && i < abs((int)strlen(expression))) {
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
	if (expression[0] == '(' && expression[1] == '(' && isContained("))", expression) && !dataVerifier<double>(expression, 0.0, 0.0, 0, 1)) {

		int n = 0;
		while (n < abs((int)strlen(expression))) {
			expression[n] = expression[n + 1];
			n++;
		}
		expression[n] = '\0';

		if (expression[abs((int)strlen(expression)) - 1] == ')' && expression[abs((int)strlen(expression)) - 2] == ')') {
			expression[abs((int)strlen(expression)) - 1] = '\0';
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
	if (!dataVerifier<double>(expression, 0.0, 0.0, 0, 1)) {

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

	if (!dataVerifier<double>(expression, 0.0, 0.0, 0, 1)) {
		if (countOccurrences(")", expression) > countOccurrences("(", expression)) {
			while (countOccurrences(")", expression) > countOccurrences("(", expression)) {
				if (isContained("))", expression)) {
					replace("))", ")", expression);
					sprintf(expression, "%s", expressionF);
				}
				else {
					if (expression[abs((int)strlen(expression)) - 1] == ')') {
						expression[abs((int)strlen(expression)) - 1] = '\0';
					}
					else {
						if (expression[abs((int)strlen(expression)) - 1] == '0' && expression[abs((int)strlen(expression)) - 2] == '+' && expression[abs((int)strlen(expression)) - 3] == ')') {
							expression[abs((int)strlen(expression)) - 3] = '\0';
						}
					}
				}
			}
		}
	}
	replaceTimes = 0;
	i = 0; j = 0;
	sprintf(value, ""); sprintf(saveValue, "");
	while (i < abs((int)strlen(expression))) {
		if (firstLetterFunction(expression[i])) {
			int functionStart = i;
			char* possibleVariable = getDynamicCharArray("", "possibleVariable");
			int possibleIndex = 0;
			while (verifyLetter(expression[i])) {
				possibleVariable[possibleIndex] = expression[i];
				possibleIndex++;
				i++;
			}
			possibleVariable[possibleIndex] = '\0';
			processVariable<T>(possibleVariable);
			if (validVar == 1) {
				i = functionStart;
			}
			_delete(possibleVariable, "possibleVariable"); possibleVariable = nullptr;
		}
		if (firstLetterVariable(expression[i])) {
			value[j] = expression[i];
			value[j + 1] = '\0';
			processVariable<T>(value);
			if (validVar == 1) {
				while (validVar == 1 && letterVariables(expression[i + 1]) && i < abs((int)strlen(expression))) {
					sprintf(saveValue, value);
					j++; i++;
					value[j] = expression[i];
					value[j + 1] = '\0';

					processVariable<T>(value);
					if (validVar == 0) {
						sprintf(value, saveValue);
					}
					if (verifyLetter(expression[i + 1])) {
						int count = 0;
						count = countOccurrences(value, variables);
						if (count == 1) {
							char* toReplace = getDynamicCharArray("", "toReplace"); char* replacement = getDynamicCharArray("", "replacement");
							sprintf(toReplace, "%s%c", value, expression[i + 1]);
							sprintf(replacement, "%s*%c", value, expression[i + 1]);
							replace(toReplace, replacement, expression);
							sprintf(expression, expressionF);
							sprintf(value, "");
							_delete(toReplace, "toReplace");
							toReplace = nullptr;
							_delete(replacement, "replacement");
							replacement = nullptr;
						}
						else {
							validVar = 0;
							sprintf(value, "");
							while (verifyLetter(expression[i]) && validVar == 0) {
								sprintf(value, "%s%c", value, expression[i]);
								i++;
								char* verifyVariable = getDynamicCharArray("", "verifyVariable");
								sprintf(verifyVariable, ",%s,", value);
								count = countOccurrences(value, variables);
								replaceTimes = 1;
								if (isContained(verifyVariable, variables) && count == 1) {
									isContained(value, expression);
									if (verifyLetter(expression[strStart - 1])) {
										char* replacement = getDynamicCharArray("", "replacement");
										sprintf(replacement, "*%s", value);

										replace(value, replacement, expression);
										sprintf(expression, "%s", expressionF);
										_delete(replacement, "replacement");
										replacement = nullptr;
									}
									isContained(value, expression);
									if (verifyLetter(expression[strEnd])) {
										char* replacement = getDynamicCharArray("", "replacement");
										sprintf(replacement, "%s*", value);
										replace(value, replacement, expression);
										sprintf(expression, "%s", expressionF);
										_delete(replacement, "replacement");
										replacement = nullptr;
									}

								}
								_delete(verifyVariable, "verifyVariable");
								verifyVariable = nullptr;
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
	_delete(vari, "vari");
	vari = nullptr;
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
	_delete(value, "value");
	value = nullptr;
	_delete(saveValue, "saveValue");
	saveValue = nullptr;
	_delete(variables, "variables");
	variables = nullptr;
}


void customFuncRenamer(char* variable) {
	int i = 0;
	for (i = 0; i < abs((int)strlen(variable)); i++) {
		if (i == 0 && (variable[i] == 's' || variable[i] == 'c' || variable[i] == 't' || variable[i] == 'a' || variable[i] == 'l' || variable[i] == 'r' || variable[i] == 'q' || variable[i] == 'g' || variable[i] == 'd' || variable[i] == 'm')) {
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
			if (variable[i] == 'm') {
				revariable[i] = 'M';
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
					if (variable[i] == 'A' || variable[i] == 'B' || variable[i] == 'C' || variable[i] == 'E' || variable[i] == 'P' || (variable[i - 2] == 'I' && variable[i - 1] == 'N') == false && variable[i] == 'F') {
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
template<typename T>
void manageExpression(char* arithTrig, T result1, T result2, int verify) {

	if (abs((int)strlen(arithTrig)) > 0) {
		if (isContained("[", arithTrig) && isContained("]i", arithTrig)) {
			replace("]i", "]*1i", arithTrig);
			sprintf(arithTrig, "%s", expressionF);
		}
		if (isContained("[", arithTrig) && isContained("]1i", arithTrig)) {
			replace("]1i", "]*1i", arithTrig);
			sprintf(arithTrig, "%s", expressionF);
		}

		renamer(arithTrig);
		sprintf(arithTrig, expressionF);
		substituteExistingScalarVariables<T>(arithTrig);
		sprintf(arithTrig, expressionF);
		expandDelimitedFunctionSyntax(arithTrig);
		sprintf(arithTrig, expressionF);

		int i = 0, j = 0, s = 0, f = 0;
		variableToMultiply<T>(arithTrig);
		sprintf(arithTrig, "%s", expressionF);

		toMultiply(arithTrig, result1, result2);

		variableToMultiply<T>(arithTrig);
		sprintf(arithTrig, "%s", expressionF);
		renamer(arithTrig);
		sprintf(arithTrig, "%s", expressionF);

		variableToMultiply<T>(arithTrig);
		for (i = 0; i < abs((int)strlen(expressionF)); i++) {
			arithTrig[i] = expressionF[i];
		}
		arithTrig[i] = '\0';

		char* letterScan = getDynamicCharArray("", "letterScan");
		for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
			if (verifyLetter(arithTrig[i])) {
				letterScan[i] = arithTrig[i];
			}
			else {
				letterScan[i] = ' ';
			}
		}

		letterScan[i] = '\0';
		char* toTest = getDynamicCharArray("", "toTest");
		int savePosition = 0;
		for (i = 0; i < abs((int)strlen(letterScan)); i++) {
			if (verifyLetter(letterScan[i])) {
				f = 0;
				savePosition = i;
				while (verifyLetter(letterScan[i])) {
					toTest[f] = letterScan[i];
					i++; f++;
				}
				toTest[f] = '\0';
				char* usRFunc = getDynamicCharArray("", "usRFunc");
				sprintf(usRFunc, "%s\\User functions\\%s.txt", atcPath, toTest);
				FILE* test = NULL;
				test = fopen(usRFunc, "r");
				if (test != NULL && (letterScan[savePosition - 4] == 'a' && letterScan[savePosition - 3] == 't' && letterScan[savePosition - 2] == 'c' && letterScan[savePosition - 1] == ' ') == true) {
					customFuncRenamer(toTest);
					char* renaFunc = getDynamicCharArray("", "renaFunc");
					for (f = 0; f < abs((int)strlen(revariable)); f++) {
						renaFunc[f] = revariable[f];
					}
					renaFunc[f] = '\0';
					sprintf(usRFunctions, "%s%s,", usRFunctions, toTest);
					sprintf(usRFuncTrans, "%s%s,", usRFuncTrans, renaFunc);
					int p = 0;
					f = savePosition;
					for (p = 0; p < abs((int)strlen(renaFunc)); p++) {
						letterScan[f] = renaFunc[p];
						f++;
					}
					fclose(test);
					_delete(renaFunc, "renaFunc");
					renaFunc = nullptr;
				}
				_delete(usRFunc, "usRFunc");
				usRFunc = nullptr;
			}
		}
		for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
			if (verifyLetter(arithTrig[i])) {
				arithTrig[i] = letterScan[i];
			}
		}
		renamer(arithTrig);
		for (i = 0; i < abs((int)strlen(expressionF)); i++) {
			arithTrig[i] = expressionF[i];
		}
		arithTrig[i] = '\0';
		variableToMultiply<T>(arithTrig);
		for (i = 0; i < abs((int)strlen(expressionF)); i++) {
			arithTrig[i] = expressionF[i];
		}
		arithTrig[i] = '\0';
		renamer(arithTrig);
		for (i = 0; i < abs((int)strlen(expressionF)); i++) {
			arithTrig[i] = expressionF[i];
		}
		arithTrig[i] = '\0';

		renamer(arithTrig);
		for (i = 0; i < abs((int)strlen(expressionF)); i++) {
			arithTrig[i] = expressionF[i];
		}
		arithTrig[i] = '\0';

		int needOne = 1;
		while (needOne == 1) {
			needOne = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (arithTrig[i] == 'B' || arithTrig[i] == 'O' || arithTrig[i] == 'H') {
					i++;
					while (verifyNumerical(arithTrig[i])) {
						i++;
					}
					if (arithTrig[i - 1] == '1' && arithTrig[i] == 'i') {
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
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (arithTrig[i] == 'B' || arithTrig[i] == 'O' || arithTrig[i] == 'H') {
					i++;
					while (verifyNumerical(arithTrig[i])) {
						i++;
					}
					if (arithTrig[i - 1] == '1' && arithTrig[i] == 'i') {
						needOne = 1;
					}
				}
			}
		}
		renamer(arithTrig);
		for (i = 0; i < abs((int)strlen(expressionF)); i++) {
			arithTrig[i] = expressionF[i];
		}
		arithTrig[i] = '\0';
		needOne = 1;

		while (needOne == 1) {
			needOne = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != '1' && arithTrig[i - 1] != 'i' && arithTrig[i - 1] != 'p' && arithTrig[i] == 'i' && verifyLetter(arithTrig[i + 1]) == 0 && verifyNumber(arithTrig[i + 1]) == false) {
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
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != '1' && arithTrig[i - 1] != 'i' && arithTrig[i - 1] != 'p' && arithTrig[i] == 'i' && verifyLetter(arithTrig[i + 1]) == 0 && verifyNumber(arithTrig[i + 1]) == false) {
					needOne = 1;
				}
			}
		}
		renamer(arithTrig);
		for (i = 0; i < abs((int)strlen(expressionF)); i++) {
			arithTrig[i] = expressionF[i];
		}
		arithTrig[i] = '\0';

		int needAst = 1;
		needAst = 1;
		while (needAst == 1) {
			needAst = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'e' && verifyLetter(arithTrig[i + 1])) {
					j = i + 1;
					i = abs((int)strlen(arithTrig));
					while (i > j) {
						arithTrig[i] = arithTrig[i - 1];
						i--;
					}
					arithTrig[i] = '*';
				}
			}
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'e' && verifyLetter(arithTrig[i + 1])) {
					needAst = 1;
				}
			}
		}
		needAst = 1;

		while (needAst == 1) {
			needAst = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'p' && arithTrig[i + 1] == 'i' && verifyLetter(arithTrig[i + 2])) {
					j = i + 2;
					i = abs((int)strlen(arithTrig));
					while (i > j) {
						arithTrig[i] = arithTrig[i - 1];
						i--;
					}
					arithTrig[i] = '*';
				}
			}
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'p' && arithTrig[i + 1] == 'i' && verifyLetter(arithTrig[i + 2])) {
					needAst = 1;
				}
			}
		}

		needAst = 1;
		while (needAst == 1) {
			needAst = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != 'b' && arithTrig[i - 1] != 'D' && arithTrig[i - 2] != 't' && arithTrig[i - 3] != 'r' && arithTrig[i] == 'p' && arithTrig[i + 1] == 'i' && verifyLetter(arithTrig[i + 2]) == false) {
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
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != 'b' && arithTrig[i - 1] != 'D' && arithTrig[i - 2] != 't' && arithTrig[i - 3] != 'r' && arithTrig[i] == 'p' && arithTrig[i + 1] == 'i' && verifyLetter(arithTrig[i + 2]) == false) {
					needAst = 1;
				}
			}
		}

		needAst = 1;
		while (needAst == 1) {
			needAst = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'e' && verifyLetter(arithTrig[i + 1]) == false) {
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
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'e' && verifyLetter(arithTrig[i + 1]) == false) {
					needAst = 1;
				}
			}
		}
		renamer(arithTrig);
		for (i = 0; i < abs((int)strlen(expressionF)); i++) {
			arithTrig[i] = expressionF[i];
		}
		arithTrig[i] = '\0';
		needAst = 1;
		while (needAst == 1) {
			needAst = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'p' && arithTrig[i + 1] == 'i' && verifyLetter(arithTrig[i + 2])) {
					if (arithTrig[i - 1] == 'D' || arithTrig[i - 1] == 'b') {
						while (verifyLetter(arithTrig[i])) {
							i--;
						}
						i++;
						int lo = 0;
						char* func = getDynamicCharArray("", "func");
						while (verifyLetter(arithTrig[i]) && arithTrig[i] != 'b' && arithTrig[i] != 'D') {
							func[lo] = arithTrig[i];
							lo++; i++;
						}
						func[lo] = arithTrig[i]; lo++;
						func[lo] = arithTrig[i]; lo++;
						func[lo] = '?'; lo++;
						func[lo] = '\0';

						if (functionProcessor<T>(func, 0, 0, 0, "") == 0.5) {
							i = i + 2;
						}
						_delete(func, "func");
						func = nullptr;
					}
				}
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'p' && arithTrig[i + 1] == 'i' && verifyLetter(arithTrig[i + 2])) {
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
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'p' && arithTrig[i + 1] == 'i' && verifyLetter(arithTrig[i + 2])) {
					if (arithTrig[i - 1] == 'D' || arithTrig[i - 1] == 'b') {
						while (verifyLetter(arithTrig[i])) {
							i--;
						}
						i++;
						int lo = 0;
						char* func = getDynamicCharArray("", "func");
						while (verifyLetter(arithTrig[i]) && arithTrig[i] != 'b' && arithTrig[i] != 'D') {
							func[lo] = arithTrig[i];
							lo++; i++;
						}
						func[lo] = arithTrig[i]; lo++;
						func[lo] = arithTrig[i]; lo++;
						func[lo] = '?'; lo++;
						func[lo] = '\0';

						if (functionProcessor<T>(func, 0, 0, 0, "") == 0.5) {
							i = i + 2;
						}
						_delete(func, "func");
						func = nullptr;
					}
				}
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'p' && arithTrig[i + 1] == 'i' && verifyLetter(arithTrig[i + 2])) {
					needAst = 1;
				}
			}
		}
		renamer(arithTrig);
		for (i = 0; i < abs((int)strlen(expressionF)); i++) {
			arithTrig[i] = expressionF[i];
		}
		arithTrig[i] = '\0';
		needOne = 1;
		while (needOne == 1) {
			needOne = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i' && verifyLetter(arithTrig[i + 1]) && arithTrig[i + 1] != 'D' && arithTrig[i + 1] != 'b') {
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
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i' && verifyLetter(arithTrig[i + 1]) && arithTrig[i + 1] != 'D' && arithTrig[i + 1] != 'b') {
					needOne = 1;
				}
			}
		}
		needOne = 1;
		while (needOne == 1) {
			needOne = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != '1' && arithTrig[i - 1] != 'p' && arithTrig[i] == 'i' && verifyLetter(arithTrig[i + 1]) == 0 && verifyNumber(arithTrig[i + 1]) == 0) {
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
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != '1' && arithTrig[i - 1] != 'p' && arithTrig[i] == 'i' && verifyLetter(arithTrig[i + 1]) == 0 && verifyNumber(arithTrig[i + 1]) == 0) {
					needOne = 1;
				}
			}
		}

		needAst = 1;
		int mark = 0, mark1 = 0, napier = 0, n = 0, m = 0;
		float isFunc = 0;
		char* functionP = getDynamicCharArray("", "functionP");
		int w = 0;
		while (needAst == 1) {
			valRenamedVar = 0;
			bool entered = false;
			for (i = mark1; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'e' && verifyLetter(arithTrig[i + 1]) && needAst == 1 && (arithTrig[i - 1] == 'D' || arithTrig[i - 1] == 'b')) {
					int countB = countOccurrences("b", arithTrig);
					int countD = countOccurrences("D", arithTrig);
					if (countB >= 2 || countD >= 2) {

						entered = true;
						while (verifyLetter(arithTrig[i])) {
							i--;
						}
						i++;
						int lo = 0;
						char* func = getDynamicCharArray("", "func");
						while (verifyLetter(arithTrig[i]) && arithTrig[i] != 'b' && arithTrig[i] != 'D') {
							func[lo] = arithTrig[i];
							lo++; i++;
						}
						func[lo] = arithTrig[i]; lo++;
						func[lo] = arithTrig[i]; lo++;
						func[lo] = '?'; lo++;
						func[lo] = '\0';

						if (functionProcessor<T>(func, 0, 0, 0, "") == 0.5) {

							i = i + 2;
						}
						_delete(func, "func");
						func = nullptr;
					}
				}
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i] == 'e' && verifyLetter(arithTrig[i + 1]) && needAst == 1) {

					entered = true;
					mark1 = i + 1;
					j = i;
					i = abs((int)strlen(arithTrig));
					int p = j;
					while (verifyLetter(arithTrig[p])) {
						p--;
					}
					if (j != p) {

						p++;
						char* function = getDynamicCharArray("", "function");
						int y = 0;
						while (verifyLetter(arithTrig[p]) && p < abs((int)strlen(arithTrig))) {
							function[y] = arithTrig[p];
							p++; y++;
						}
						function[y] = '?'; function[y + 1] = '\0';

						isFunc = (float)functionProcessor<T>(function, 0, 0, 0, "");
						if (isFunc == 0.5) {
							_delete(function, "function");

							break;
						}
						else {

							function[y] = '\0';
							valRenamedVar = 0;
							n = 0, m = 0;
							m = 0;
							for (n = 0; n < abs((int)strlen(function)) && n < abs((int)strlen(function)); n++) {

								while (function[n] != 'e' && n < abs((int)strlen(function)) && n < abs((int)strlen(function))) {
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
						_delete(function, "function");
						function = nullptr;
					}
					if (isFunc == 0 && napier == 0) {
						int l = 0;

						for (l = 0; l < abs((int)strlen(arithTrig)); l++) {
							if (arithTrig[l] == 'r' && arithTrig[l + 1] == 'e' && arithTrig[l + 2] == 's') {
								l = 0;

								break;
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
						for (n = 0; n < abs((int)strlen(arithTrig)); n++) {
							if (arithTrig[n] == functionP[m]) {
								m = 0;

								while (arithTrig[n] == functionP[m]) {
									n++; m++;
								}
								int z = abs((int)strlen(arithTrig)), nj = n, nc = 0;
								nc = z;
								if (arithTrig[nj + 1] != '(') {

									if ((arithTrig[nj - 3] == 'l' && arithTrig[nj - 2] == 'o' && arithTrig[nj - 1] == 'g' && arithTrig[nj] == 'b') == false && (arithTrig[nj - 2] == 'r' && arithTrig[nj - 1] == 't' && arithTrig[nj] == 'D') == false) {

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
											if (z < abs((int)strlen(arithTrig))) {

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

			for (i = mark; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != 'r' && arithTrig[i] == 'e' && arithTrig[i + 1] != 's' && verifyLetter(arithTrig[i + 1]) && (arithTrig[i - 1] == 'D' || arithTrig[i - 1] == 'b')) {
					int countB = countOccurrences("b", arithTrig);
					int countD = countOccurrences("D", arithTrig);
					if (countB >= 2 || countD >= 2) {
						entered = true;
						while (verifyLetter(arithTrig[i])) {

							i--;
						}
						i++;
						int lo = 0;
						char* func = getDynamicCharArray("", "func");
						while (verifyLetter(arithTrig[i]) && arithTrig[i] != 'b' && arithTrig[i] != 'D') {

							func[lo] = arithTrig[i];
							lo++; i++;
						}
						func[lo] = arithTrig[i]; lo++;
						func[lo] = arithTrig[i]; lo++;
						func[lo] = '?'; lo++;
						func[lo] = '\0';

						if (functionProcessor<T>(func, 0, 0, 0, "") == 0.5) {
							i = i + 2;
						}
						_delete(func, "func");
						func = nullptr;
					}
				}

				if (verifyLetter(arithTrig[i - 1]) && arithTrig[i - 1] != 'r' && arithTrig[i] == 'e' && arithTrig[i + 1] != 's' && verifyLetter(arithTrig[i + 1]) && entered) {
					mark = i + 1;
					needAst = 1;
				}
				else {
					needAst = 0;
				}
			}
			w++;
		}
		renamer(arithTrig);
		for (i = 0; i < abs((int)strlen(expressionF)); i++) {
			arithTrig[i] = expressionF[i];
		}
		arithTrig[i] = '\0';

		char* paTrig = getDynamicCharArray("", "paTrig");
		int u = 0;
		for (u = 0; u < abs((int)strlen(arithTrig)); u++) {
			paTrig[u] = arithTrig[u];
		}
		paTrig[u] = '\0';
		u = 0;
		for (u; u < abs((int)strlen(paTrig)); u++) {
			if ((strncmp(&paTrig[u], "rtD", 3) == 0) || (strncmp(&paTrig[u], "logb", 4) == 0)) {
				while (paTrig[u] != '(' && paTrig[u] != '\0') {
					u++;
				}
			}
			if (verifyLetter(paTrig[u]) == 0) {
				while (verifyLetter(paTrig[u]) == 0 && u < abs((int)strlen(paTrig))) {
					u++;
				}
			}
			if (verifyLetter(paTrig[u]) && firstLetterVariable(paTrig[u]) == 0) {
				while (verifyLetter(paTrig[u])) {
					u++;
				}
			}
			if (firstLetterVariable(paTrig[u]) && firstLetterVariable(paTrig[u - 1]) == 0 && paTrig[u + 1] != 'i' && !isInsideDelimitedFunctionHeader(paTrig, u)) {
				u++;
				while (verifyLetter(paTrig[u])) {
					u++;
				}
				if (paTrig[u] != '\\' && paTrig[u] != '*' && paTrig[u] != '+' && paTrig[u] != '-' && paTrig[u] != '/' && paTrig[u] != '^' && paTrig[u] != '!' && paTrig[u] != ')' && paTrig[u] != '[' && paTrig[u] != ']' && paTrig[u] != '.' && paTrig[u] != '\0') {
					T check = 0;
					if (verifyLetter(paTrig[u - 1])) {
						int z = u - 1, v = 0;
						char* toVal = getDynamicCharArray("", "toVal");
						while (verifyLetter(paTrig[z])) {
							z--;
						}
						z++;
						while (verifyLetter(paTrig[z])) {
							toVal[v] = paTrig[z];
							z++; v++;
						}
						toVal[v] = '?'; toVal[v + 1] = '\0';

						check = functionProcessor<T>(toVal, 0, 0, 0, "");
						_delete(toVal, "toVal");
					}
					if (check != 0.5) {
						arithTrig[u] = '*';
						for (u; u < abs((int)strlen(paTrig)); u++) {
							arithTrig[u + 1] = paTrig[u];
						}
						arithTrig[u + 1] = '\0';
						u = 0;
						for (u = 0; u < abs((int)strlen(arithTrig)); u++) {
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
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i - 1] != '(' && arithTrig[i] == 'i' && verifyLetter(arithTrig[i + 1]) && arithTrig[i + 1] != 'D' && arithTrig[i + 1] != 'b') {
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
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i - 1] != '(' && arithTrig[i] == 'i' && verifyLetter(arithTrig[i + 1]) && arithTrig[i + 1] != 'D' && arithTrig[i + 1] != 'b') {
					needAst = 1;
				}
			}
		}

		needAst = 1;
		replaceTimes = 1;
		while (needAst == 1) {
			needAst = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (isContained("_i", arithTrig)) {
					replace("_i", "_1i", arithTrig);
					sprintf(arithTrig, "%s", expressionF);
					i = strEnd;
				}
				else {
					if ((verifyLetter(arithTrig[i - 1]) || verifyNumber(arithTrig[i - 1])) && arithTrig[i - 1] != 'p' && arithTrig[i - 1] != 'D' && arithTrig[i - 1] != 'b' && arithTrig[i] == 'i' && arithTrig[i - 1] != '1' && arithTrig[i - 1] != '(' && verifyLetter(arithTrig[i + 1]) == 0) {
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
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if ((verifyLetter(arithTrig[i - 1]) || verifyNumber(arithTrig[i - 1])) && arithTrig[i - 1] != 'p' && arithTrig[i - 1] != 'D' && arithTrig[i - 1] != 'b' && arithTrig[i] == 'i' && arithTrig[i - 1] != '1' && arithTrig[i - 1] != '(' && verifyLetter(arithTrig[i + 1]) == 0) {
					needAst = 1;
				}
			}
		}
		replaceTimes = 0;
		needAst = 1;
		while (needAst == 1) {
			needAst = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if ((arithTrig[i - 1] == ')' || arithTrig[i - 1] == ']') && arithTrig[i] == 'i' && verifyLetter(arithTrig[i + 1]) == 0) {
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
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if ((arithTrig[i - 1] == ')' || arithTrig[i - 1] == ']') && arithTrig[i] == 'i' && verifyLetter(arithTrig[i + 1]) == 0) {
					needAst = 1;
				}
			}
		}

		needAst = 1;
		while (needAst == 1) {
			needAst = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i' && arithTrig[i + 1] == '(') {
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
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i' && arithTrig[i + 1] == '(') {
					needAst = 1;
				}
			}
		}
		renamer(arithTrig);
		for (i = 0; i < abs((int)strlen(expressionF)); i++) {
			arithTrig[i] = expressionF[i];
		}
		arithTrig[i] = '\0';
		needAst = 1;
		while (needAst == 1) {
			needAst = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) == 0 && verifyNumber(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i' && (verifyLetter(arithTrig[i + 1]) || verifyNumber(arithTrig[i + 1]) || arithTrig[i + 1] == '#')) {
					j = i;
					i = abs((int)strlen(arithTrig)) + 1;
					while (i > j) {
						arithTrig[i] = arithTrig[i - 2];
						i--;
					}
					arithTrig[i] = '1'; arithTrig[i + 1] = 'i'; arithTrig[i + 2] = '*';
				}
			}
			needAst = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (verifyLetter(arithTrig[i - 1]) == 0 && verifyNumber(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i' && (verifyLetter(arithTrig[i + 1]) || verifyNumber(arithTrig[i + 1]) || arithTrig[i + 1] == '#')) {
					needAst = 1;
				}
			}
		}

		needOne = 1;
		while (needOne == 1) {
			needOne = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if ((verifyLetter(arithTrig[i - 1]) == 0 || arithTrig[i - 1] == 'D' || arithTrig[i - 1] == 'b') && verifyNumber(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i' && verifyNumber(arithTrig[i + 1]) == 0 && (verifyLetter(arithTrig[i + 1]) == 0 || arithTrig[i + 1] == 'D' || arithTrig[i + 1] == 'b')) {
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
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if ((verifyLetter(arithTrig[i - 1]) == 0 || arithTrig[i - 1] == 'D' || arithTrig[i - 1] == 'b') && verifyNumber(arithTrig[i - 1]) == 0 && arithTrig[i] == 'i' && verifyNumber(arithTrig[i + 1]) == 0 && (verifyLetter(arithTrig[i + 1]) == 0 || arithTrig[i + 1] == 'D' || arithTrig[i + 1] == 'b')) {
					needOne = 1;
				}
			}
		}
		bool imaginary = false;
		for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
			if (arithTrig[i - 1] == '/' && (verifyLetter(arithTrig[i]) || verifyNumber(arithTrig[i]) || arithTrig[i] == '#' || arithTrig[i] == '1' && arithTrig[i + 1] == 'i')) {
				int y = 0;
				char* express = getDynamicCharArray("", "express");
				if (arithTrig[i] == '1' && arithTrig[i + 1] == 'i') {
					express[y] = arithTrig[i]; imaginary = true;
					i++; y++;
					express[y] = arithTrig[i];
					i++; y++;
					express[y] = arithTrig[i];
					i++; y++;
				}
				if (verifyNumber(arithTrig[i])) {
					while (verifyNumber(arithTrig[i])) {
						express[y] = arithTrig[i];
						i++; y++;
						if (arithTrig[i] == '*') {
							int kl = 1, kr = 0;
							express[y] = arithTrig[i];
							i++; y++;
							if (arithTrig[i] == '1' && arithTrig[i + 1] == 'i') {
								express[y] = arithTrig[i]; imaginary = true;
								i++; y++;
								express[y] = arithTrig[i];
								i++; y++;

							}
						}

					}
				}

				else {
					if (arithTrig[i] == '#' && verifyNumber(arithTrig[i + 1])) {
						express[y] = arithTrig[i];
						i++; y++;
						while (verifyNumber(arithTrig[i])) {
							express[y] = arithTrig[i];
							i++; y++;
							if (arithTrig[i] == '*') {
								int kl = 1, kr = 0;
								express[y] = arithTrig[i];
								i++; y++;
								if (arithTrig[i] == '1' && arithTrig[i + 1] == 'i') {
									express[y] = arithTrig[i]; imaginary = true;
									i++; y++;
									express[y] = arithTrig[i];
									i++; y++;

								}
							}

						}
					}
					else {
						if (arithTrig[i] == 'B' || arithTrig[i] == 'O' || arithTrig[i] == 'H') {
							express[y] = arithTrig[i];
							i++; y++;
							while (verifyNumber(arithTrig[i]) || verifyLetter(arithTrig[i])) {
								express[y] = arithTrig[i];
								i++; y++;
								if (arithTrig[i] == '*') {
									int kl = 1, kr = 0;
									express[y] = arithTrig[i];
									i++; y++;
									if (arithTrig[i] == '1' && arithTrig[i + 1] == 'i') {
										express[y] = arithTrig[i]; imaginary = true;
										i++; y++;
										express[y] = arithTrig[i];
										i++; y++;

									}
								}

							}
						}
						else {
							while (verifyLetter(arithTrig[i])) {
								express[y] = arithTrig[i];
								i++; y++;
								if (arithTrig[i] == '(') {
									int kl = 1, kr = 0;
									express[y] = arithTrig[i];
									i++; y++;
									while (kl > kr)
									{
										if (arithTrig[i] == '(') {
											kl++;
										}
										if (arithTrig[i] == ')') {
											kr++;
										}
										express[y] = arithTrig[i];
										i++; y++;
									}

								}
								if (arithTrig[i] == '*' && arithTrig[i + 1] == '1' && arithTrig[i + 2] == 'i') {
									express[y] = arithTrig[i]; imaginary = true;
									i++; y++;
									express[y] = arithTrig[i];
									i++; y++;
									express[y] = arithTrig[i];
									i++; y++;

								}
							}
						}
					}
				}
				express[y] = '\0';
				if (imaginary) {
					replaceTimes = 1;
					char* exp2Replace = getDynamicCharArray("", "exp2Replace"); char* expReplacement = getDynamicCharArray("", "expReplacement");
					sprintf(exp2Replace, "/%s%c", express, arithTrig[i]);
					sprintf(expReplacement, "/(%s)%c", express, arithTrig[i]);
					replace(exp2Replace, expReplacement, arithTrig);
					sprintf(arithTrig, "%s", expressionF);
					imaginary = false;
					i = 0;
					_delete(exp2Replace, "exp2Replace");
					exp2Replace = nullptr;
					_delete(expReplacement, "expReplacement");
					expReplacement = nullptr;
				}
				_delete(express, "express");
				express = nullptr;
			}
		}
		needAst = 1;
		while (needAst == 1) {
			needAst = 0;
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (arithTrig[i - 1] == '1' && arithTrig[i] == 'i' && (verifyLetter(arithTrig[i + 1]) && arithTrig[i + 1] != 'D' && arithTrig[i + 1] != 'b' || verifyNumber(arithTrig[i + 1]))) {
					j = i + 1;
					i = abs((int)strlen(arithTrig));
					while (i > j) {
						arithTrig[i] = arithTrig[i - 1];
						i--;
					}
					arithTrig[i] = '*';
				}
			}
			for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
				if (arithTrig[i - 1] == '1' && arithTrig[i] == 'i' && (verifyLetter(arithTrig[i + 1]) && arithTrig[i + 1] != 'D' && arithTrig[i + 1] != 'b' || verifyNumber(arithTrig[i + 1]))) {
					needAst = 1;
				}
			}
		}
		s = 0;
		for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
			paTrig[s] = arithTrig[s];
		}
		paTrig[s] = '\0';

		s = 0;
		for (s; s < abs((int)strlen(paTrig)); s++) {
			if (!isInsideDelimitedFunctionHeader(paTrig, s) && !isInsideDelimitedFunctionHeader(paTrig, s + 1) && (paTrig[s] == 'e' && paTrig[s + 1] != 'b' || paTrig[s] == 'i' && paTrig[s - 1] == 'p' && paTrig[s + 1] != 'b' || paTrig[s] == '1' || paTrig[s] == '2' || paTrig[s] == '3' || paTrig[s] == '4' || paTrig[s] == '5' || paTrig[s] == '6' || paTrig[s] == '7' || paTrig[s] == '8' || paTrig[s] == '9' || paTrig[s] == '0') && (paTrig[s + 1] == '#' || paTrig[s + 1] == 'w' || paTrig[s + 1] == 'y' || paTrig[s + 1] == 'u' || paTrig[s + 1] == 'o' || paTrig[s + 1] == 'p' || paTrig[s + 1] == 'f' || paTrig[s + 1] == 'h' || paTrig[s + 1] == 'j' || paTrig[s + 1] == 'k' || paTrig[s + 1] == 'z' || paTrig[s + 1] == 'v' || paTrig[s + 1] == 'm' || paTrig[s + 1] == 'Q' || paTrig[s + 1] == 'W' || paTrig[s + 1] == 'R' || paTrig[s + 1] == 'T' || paTrig[s + 1] == 'Y' || paTrig[s + 1] == 'U' || paTrig[s + 1] == 'I' || paTrig[s + 1] == 'S' || paTrig[s + 1] == 'G' || paTrig[s + 1] == 'J' || paTrig[s + 1] == 'K' || paTrig[s + 1] == 'L' || paTrig[s + 1] == 'Z' || paTrig[s + 1] == 'X' || paTrig[s + 1] == 'V' || paTrig[s + 1] == 'N' || paTrig[s + 1] == 'M')) {
				s++;
				arithTrig[s] = '*';
				for (s; s < abs((int)strlen(paTrig)); s++) {
					arithTrig[s + 1] = paTrig[s];
				}
				arithTrig[s + 1] = '\0';
				s = 0;
				for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
					paTrig[s] = arithTrig[s];
				}
				paTrig[s] = '\0';
				s = 0;
			}
		}

		s = 0;
		for (s; s < abs((int)strlen(paTrig)); s++) {
			if (!isInsideDelimitedFunctionHeader(paTrig, s) && !isInsideDelimitedFunctionHeader(paTrig, s + 1) && (paTrig[s + 1] == 'e' && paTrig[s] != 'b' && paTrig[s] != 'c' && (paTrig[s] == 'l' && paTrig[s - 1] == 'r' && paTrig[s - 2] == 't' && paTrig[s - 3] == 's' && paTrig[s + 2] == 'n') == false && (paTrig[s] == 'v' && paTrig[s - 1] == 'l' && paTrig[s - 2] == 'o' && paTrig[s - 3] == 's' && paTrig[s + 2] == 'r') == false || paTrig[s + 1] == 'p' && paTrig[s + 2] == 'i' && paTrig[s] != 'b' || paTrig[s + 1] == '1' || paTrig[s + 1] == '2' || paTrig[s + 1] == '3' || paTrig[s + 1] == '4' || paTrig[s + 1] == '5' || paTrig[s + 1] == '6' || paTrig[s + 1] == '7' || paTrig[s + 1] == '8' || paTrig[s + 1] == '9' || paTrig[s + 1] == '0') && (paTrig[s] == 'q' || paTrig[s] == 'w' || paTrig[s] == 't' || paTrig[s] == 'y' || paTrig[s] == 'u' || paTrig[s] == 'o' || paTrig[s] == 'p' || paTrig[s] == 'a' || paTrig[s] == 'f' || paTrig[s] == 'h' || paTrig[s] == 'j' || paTrig[s] == 'k' || paTrig[s] == 'l' || paTrig[s] == 'z' || paTrig[s] == 'c' || paTrig[s] == 'v' || paTrig[s] == 'n' || paTrig[s] == 'm' || paTrig[s] == 'Q' || paTrig[s] == 'W' || paTrig[s] == 'R' || paTrig[s] == 'T' || paTrig[s] == 'Y' || paTrig[s] == 'U' || paTrig[s] == 'I' || paTrig[s] == 'S' || paTrig[s] == 'G' || paTrig[s] == 'J' || paTrig[s] == 'K' || paTrig[s] == 'L' || paTrig[s] == 'Z' || paTrig[s] == 'X' || paTrig[s] == 'V' || paTrig[s] == 'N' || paTrig[s] == 'M')) {
				s++;
				arithTrig[s] = '*';
				for (s; s < abs((int)strlen(paTrig)); s++) {
					arithTrig[s + 1] = paTrig[s];
				}
				arithTrig[s + 1] = '\0';
				s = 0;
				for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
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
		for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
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
			if (arithTrig[h] == '{') {
				arithTrig[h] = '(';
			}
			if (arithTrig[h] == '}') {
				arithTrig[h] = ')';
			}
			h++;
		}

		char* varCandidate = getDynamicCharArray("", "varCandidate");
		char* finalReplacement = getDynamicCharArray("", "finalReplacement");
		char* readLetter = getDynamicCharArray("", "readLetter");
		int v = 0;
		int varState = 0;

		for (i = 0; i < abs((int)strlen(letterScan)); i++) {
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
			char* replaceVariable = getDynamicCharArray("", "replaceVariable");
			if (abs((int)strlen(varCandidate) != 0)) {
				sprintf(finalReplacement, "(%s)", varCandidate);
				if (isContained("res", arithTrig)) {
					if (isContained("^_res", arithTrig) == (bool)false && isContained("res", arithTrig)) {
						if (arithTrig[strEnd] != 't') {
							replace("res", "(\\\\\\\\)", arithTrig);
							replace("\\\\\\\\", "res", expressionF);
							sprintf(arithTrig, "%s", expressionF);
							char* isDuplicatedParent = getDynamicCharArray("", "isDuplicatedParent");
							sprintf(finalReplacement, "(res)");
							sprintf(isDuplicatedParent, "(%s)", finalReplacement);
							if (isContained(isDuplicatedParent, arithTrig)) {
								replace(isDuplicatedParent, finalReplacement, arithTrig);
								sprintf(arithTrig, "%s", expressionF);
							}
							_delete(isDuplicatedParent, "isDuplicatedParent");
							isDuplicatedParent = nullptr;
						}
					}
					if (isContained("^_res", arithTrig)) {
						if (arithTrig[strEnd] != 't') {
							replace("^_res", "^(\\\\\\\\)", arithTrig);
							replace("\\\\\\\\", "_res", expressionF);
							sprintf(arithTrig, "%s", expressionF);
							char* isDuplicatedParent = getDynamicCharArray("", "isDuplicatedParent");
							sprintf(finalReplacement, "(_res)");
							sprintf(isDuplicatedParent, "(_%s)", finalReplacement);
							if (isContained(isDuplicatedParent, arithTrig)) {
								replace(isDuplicatedParent, finalReplacement, arithTrig);
								sprintf(arithTrig, "%s", expressionF);
							}
							_delete(isDuplicatedParent, "isDuplicatedParent");
							isDuplicatedParent = nullptr;
						}
					}
				}
			}
			_delete(replaceVariable, "replaceVariable");
			replaceVariable = nullptr;
		}

		if (isContained("#", arithTrig)) {
			if (isContained("^_#", arithTrig) == (bool)false && isContained("#", arithTrig)) {
				int i = strStart + 1, v = 1;
				char* result_name = getDynamicCharArray("", "result_name");
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
				char* replacement = getDynamicCharArray("", "replacement");
				sprintf(finalReplacement, "(%s)", result_name);
				sprintf(replacement, "(////////)");
				replace(result_name, replacement, arithTrig);
				replace("////////", result_name, expressionF);
				sprintf(arithTrig, "%s", expressionF);
				char* isDuplicatedParent = getDynamicCharArray("", "isDuplicatedParent");
				sprintf(isDuplicatedParent, "(%s)", finalReplacement);
				if (isContained(isDuplicatedParent, arithTrig)) {
					replace(isDuplicatedParent, finalReplacement, arithTrig);
					sprintf(arithTrig, "%s", expressionF);
				}
				_delete(isDuplicatedParent, "isDuplicatedParent");
				isDuplicatedParent = nullptr;
				_delete(result_name, "result_name");
				result_name = nullptr;
				_delete(replacement, "replacement");
				replacement = nullptr;
			}
			if (isContained("^_#", arithTrig)) {
				int i = strStart + 3, v = 0;
				char* result_name = getDynamicCharArray("", "result_name");
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
				char* replacement = getDynamicCharArray("", "replacement");
				sprintf(finalReplacement, "(_%s)", result_name);
				sprintf(replacement, "^(_////////)");
				char* toReplace = getDynamicCharArray("", "toReplace");
				sprintf(toReplace, "^_%s", result_name);
				replace(toReplace, replacement, arithTrig);
				replace("////////", result_name, expressionF);
				sprintf(arithTrig, "%s", expressionF);
				char* isDuplicatedParent = getDynamicCharArray("", "isDuplicatedParent");
				sprintf(isDuplicatedParent, "(_%s)", finalReplacement);
				if (isContained(isDuplicatedParent, arithTrig)) {
					replace(isDuplicatedParent, finalReplacement, arithTrig);
					sprintf(arithTrig, "%s", expressionF);
				}
				_delete(result_name, "result_name");
				result_name = nullptr;
				_delete(replacement, "replacement");
				replacement = nullptr;
				_delete(toReplace, "toReplace");
				toReplace = nullptr;
				_delete(isDuplicatedParent, "isDuplicatedParent");
				isDuplicatedParent = nullptr;
			}
		}

		if (isContained("B", arithTrig)) {
			if (verifyNumerical(arithTrig[strStart - 1]) == (bool)false && verifyLetter(arithTrig[strStart - 1]) == (bool)false) {
				if (isContained("^_B", arithTrig) == (bool)false && isContained("B", arithTrig)) {
					int i = strStart, v = 0;
					char* result_name = getDynamicCharArray("", "result_name");
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
					char* replacement = getDynamicCharArray("", "replacement");
					sprintf(finalReplacement, "(%s)", result_name);
					sprintf(replacement, "(////////)");
					replace(result_name, replacement, arithTrig);
					replace("////////", result_name, expressionF);
					sprintf(arithTrig, "%s", expressionF);
					char* isDuplicatedParent = getDynamicCharArray("", "isDuplicatedParent");
					sprintf(isDuplicatedParent, "(%s)", finalReplacement);
					if (isContained(isDuplicatedParent, arithTrig)) {
						replace(isDuplicatedParent, finalReplacement, arithTrig);
						sprintf(arithTrig, "%s", expressionF);
					}
					_delete(result_name, "result_name");
					result_name = nullptr;
					_delete(replacement, "replacement");
					replacement = nullptr;
					_delete(isDuplicatedParent, "isDuplicatedParent");
					isDuplicatedParent = nullptr;
				}
				if (isContained("^_B", arithTrig)) {
					int i = strStart + 2, v = 0;
					char* result_name = getDynamicCharArray("", "result_name");
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
					char* replacement = getDynamicCharArray("", "replacement");
					char* toReplace = getDynamicCharArray("", "toReplace");
					sprintf(toReplace, "^_%s", result_name);
					sprintf(finalReplacement, "(_%s)", result_name);
					sprintf(replacement, "^(_////////)");
					replace(toReplace, replacement, arithTrig);
					replace("////////", result_name, expressionF);
					sprintf(arithTrig, "%s", expressionF);
					char* isDuplicatedParent = getDynamicCharArray("", "isDuplicatedParent");
					sprintf(isDuplicatedParent, "(_%s)", finalReplacement);
					if (isContained(isDuplicatedParent, arithTrig)) {
						replace(isDuplicatedParent, finalReplacement, arithTrig);
						sprintf(arithTrig, "%s", expressionF);
					}
					_delete(result_name, "result_name");
					result_name = nullptr;
					_delete(replacement, "replacement");
					replacement = nullptr;
					_delete(toReplace, "toReplace");
					toReplace = nullptr;
					_delete(isDuplicatedParent, "isDuplicatedParent");
					isDuplicatedParent = nullptr;
				}
			}
		}
		if (isContained("O", arithTrig)) {
			if (isContained("^_O", arithTrig) == (bool)false && isContained("O", arithTrig)) {
				int i = strStart, v = 0;
				char* result_name = getDynamicCharArray("", "result_name");
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
				char* replacement = getDynamicCharArray("", "replacement");
				sprintf(finalReplacement, "(%s)", result_name);
				sprintf(replacement, "(////////)");
				replace(result_name, replacement, arithTrig);
				replace("////////", result_name, expressionF);
				sprintf(arithTrig, "%s", expressionF);
				char* isDuplicatedParent = getDynamicCharArray("", "isDuplicatedParent");
				sprintf(isDuplicatedParent, "(%s)", finalReplacement);
				if (isContained(isDuplicatedParent, arithTrig)) {
					replace(isDuplicatedParent, finalReplacement, arithTrig);
					sprintf(arithTrig, "%s", expressionF);
				}
				_delete(result_name, "result_name");
				result_name = nullptr;
				_delete(replacement, "replacement");
				replacement = nullptr;
				_delete(isDuplicatedParent, "isDuplicatedParent");
				isDuplicatedParent = nullptr;
			}
			if (isContained("^_O", arithTrig)) {
				int i = strStart + 2, v = 0;
				char* result_name = getDynamicCharArray("", "result_name");
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
				char* replacement = getDynamicCharArray("", "replacement");
				char* toReplace = getDynamicCharArray("", "toReplace");
				sprintf(toReplace, "^_%s", result_name);
				sprintf(finalReplacement, "(_%s)", result_name);
				sprintf(replacement, "^(_////////)");
				replace(toReplace, replacement, arithTrig);
				replace("////////", result_name, expressionF);
				sprintf(arithTrig, "%s", expressionF);
				char* isDuplicatedParent = getDynamicCharArray("", "isDuplicatedParent");
				sprintf(isDuplicatedParent, "(_%s)", finalReplacement);
				if (isContained(isDuplicatedParent, arithTrig)) {
					replace(isDuplicatedParent, finalReplacement, arithTrig);
					sprintf(arithTrig, "%s", expressionF);
				}
				_delete(result_name, "result_name");
				result_name = nullptr;
				_delete(toReplace, "toReplace");
				toReplace = nullptr;
				_delete(replacement, "replacement");
				replacement = nullptr;
				_delete(isDuplicatedParent, "isDuplicatedParent");
				isDuplicatedParent = nullptr;
			}
		}
		if (isContained("H", arithTrig)) {
			if (isContained("^_H", arithTrig) == (bool)false && isContained("H", arithTrig)) {
				int i = strStart, v = 0;
				char* result_name = getDynamicCharArray("", "result_name");
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
				char* replacement = getDynamicCharArray("", "replacement");
				sprintf(finalReplacement, "(%s)", result_name);
				sprintf(replacement, "(////////)");
				replace(result_name, replacement, arithTrig);
				replace("////////", result_name, expressionF);
				sprintf(arithTrig, "%s", expressionF);
				char* isDuplicatedParent = getDynamicCharArray("", "isDuplicatedParent");
				sprintf(isDuplicatedParent, "(%s)", finalReplacement);
				if (isContained(isDuplicatedParent, arithTrig)) {
					replace(isDuplicatedParent, finalReplacement, arithTrig);
					sprintf(arithTrig, "%s", expressionF);
				}
				_delete(result_name, "result_name");
				result_name = nullptr;
				_delete(replacement, "replacement");
				replacement = nullptr;
				_delete(isDuplicatedParent, "isDuplicatedParent");
				isDuplicatedParent = nullptr;
			}
			if (isContained("^_H", arithTrig)) {
				int i = strStart + 2, v = 0;
				char* result_name = getDynamicCharArray("", "result_name");
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
				char* replacement = getDynamicCharArray("", "replacement");
				char* toReplace = getDynamicCharArray("", "toReplace");
				sprintf(toReplace, "^_%s", result_name);
				sprintf(finalReplacement, "(_%s)", result_name);
				sprintf(replacement, "^(_////////)");
				replace(toReplace, replacement, arithTrig);
				replace("////////", result_name, expressionF);
				sprintf(arithTrig, "%s", expressionF);
				char* isDuplicatedParent = getDynamicCharArray("", "isDuplicatedParent");
				sprintf(isDuplicatedParent, "(_%s)", finalReplacement);
				if (isContained(isDuplicatedParent, arithTrig)) {
					replace(isDuplicatedParent, finalReplacement, arithTrig);
					sprintf(arithTrig, "%s", expressionF);
				}
				_delete(result_name, "result_name");
				result_name = nullptr;
				_delete(toReplace, "toReplace");
				toReplace = nullptr;
				_delete(replacement, "replacement");
				replacement = nullptr;
				_delete(isDuplicatedParent, "isDuplicatedParent");
				isDuplicatedParent = nullptr;
			}
		}
		if (isContained("P", arithTrig)) {
			if (isContained("^_P", arithTrig) == (bool)false && isContained("P", arithTrig)) {
				int i = strStart, v = 0;
				char* result_name = getDynamicCharArray("P", "result_name"); char* prefixes = getDynamicCharArray("PY,PZ,PE,PP,PT,PG,PM,Pk,Ph,Pda,Pd,Pc,Pm,Pu,Pn,Pp,Pf,Pa,Pz,Py,", "prefixes"); char* toTest = getDynamicCharArray("P", "toTest");
				while (verifyLetter(arithTrig[i]) && isContained(toTest, prefixes)) {
					result_name[v] = arithTrig[i];
					v++; i++;
					sprintf(toTest, "%s%c", toTest, arithTrig[i]);
				}
				result_name[v] = '\0';
				char* replacement = getDynamicCharArray("", "replacement");
				sprintf(finalReplacement, "(%s)", result_name);
				sprintf(replacement, "(////////)");
				replace(result_name, replacement, arithTrig);
				replace("////////", result_name, expressionF);
				sprintf(arithTrig, "%s", expressionF);
				char* isDuplicatedParent = getDynamicCharArray("", "isDuplicatedParent");
				sprintf(isDuplicatedParent, "(%s)", finalReplacement);
				if (isContained(isDuplicatedParent, arithTrig)) {
					replace(isDuplicatedParent, finalReplacement, arithTrig);
					sprintf(arithTrig, "%s", expressionF);
				}
				_delete(result_name, "result_name");
				result_name = nullptr;
				_delete(replacement, "replacement");
				replacement = nullptr;
				_delete(isDuplicatedParent, "isDuplicatedParent");
				isDuplicatedParent = nullptr;
				_delete(prefixes, "prefixes");
				prefixes = nullptr;
				_delete(toTest, "toTest");
				toTest = nullptr;
			}
			if (isContained("^_P", arithTrig)) {
				int i = strStart + 2, v = 0;
				char* result_name = getDynamicCharArray("P", "result_name"); char* prefixes = getDynamicCharArray("PY,PZ,PE,PP,PT,PG,PM,Pk,Ph,Pda,Pd,Pc,Pm,Pu,Pn,Pp,Pf,Pa,Pz,Py,", "prefixes"); char* toTest = getDynamicCharArray("P", "toTest");
				while (verifyLetter(arithTrig[i]) && isContained(toTest, prefixes)) {
					result_name[v] = arithTrig[i];
					v++; i++;
					sprintf(toTest, "%s%c", toTest, arithTrig[i]);
				}
				result_name[v] = '\0';
				char* replacement = getDynamicCharArray("", "replacement");
				char* toReplace = getDynamicCharArray("", "toReplace");
				sprintf(toReplace, "^_%s", result_name);
				sprintf(finalReplacement, "(_%s)", result_name);
				sprintf(replacement, "^(_////////)");
				replace(toReplace, replacement, arithTrig);
				replace("////////", result_name, expressionF);
				sprintf(arithTrig, "%s", expressionF);
				char* isDuplicatedParent = getDynamicCharArray("", "isDuplicatedParent");
				sprintf(isDuplicatedParent, "(_%s)", finalReplacement);
				if (isContained(isDuplicatedParent, arithTrig)) {
					replace(isDuplicatedParent, finalReplacement, arithTrig);
					sprintf(arithTrig, "%s", expressionF);
				}
				_delete(result_name, "result_name");
				result_name = nullptr;
				_delete(replacement, "replacement");
				replacement = nullptr;
				_delete(isDuplicatedParent, "isDuplicatedParent");
				isDuplicatedParent = nullptr;
				_delete(prefixes, "prefixes");
				prefixes = nullptr;
				_delete(toTest, "toTest");
				toTest = nullptr;
			}
		}

		char* newArithTrig = getDynamicCharArray("", "newArithTrig");
		char* variableCheck = getDynamicCharArray("", "variableCheck");
		s = 0;

		int y = 0, z = 0;
		for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
			if (firstLetterVariable(arithTrig[i]) && (i == 0 || verifyLetter(arithTrig[i - 1]) == (bool)false) && (arithTrig[i] == 'i' && arithTrig[i - 1] == 'p') == false) {
				s = 0;
				while (letterVariables(arithTrig[i]) && i < abs((int)strlen(arithTrig))) {
					variableCheck[s] = arithTrig[i];
					s++;
					i++;
				}
				variableCheck[s] = '\0';
				if (arithTrig[i] != '[' && arithTrig[i] != ']' && isVariable(variableCheck) && i != abs((int)strlen(arithTrig))) {
					if (arithTrig[i - abs((int)strlen(variableCheck)) - 1] != '(' || arithTrig[i] != ')') {
						sprintf(newArithTrig, "%s(%s)", newArithTrig, variableCheck);
					}
					else {
						sprintf(newArithTrig, "%s%s)", newArithTrig, variableCheck);
						i++; y++;
					}
					y = abs((int)strlen(newArithTrig));
					if (letterVariables(arithTrig[i]) == (bool)false) {
						while (firstLetterVariable(arithTrig[i]) == (bool)false && i < abs((int)strlen(arithTrig))) {
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
					while (firstLetterVariable(arithTrig[i]) == (bool)false && i < abs((int)strlen(arithTrig))) {
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
				char* check_variable = getDynamicCharArray("", "check_variable");
				while (letterVariables(arithTrig[i]) && i < abs((int)strlen(arithTrig))) {
					check_variable[v] = arithTrig[i];
					v++; i++;
				}
				check_variable[v] = '\0';
				if (isVariable(check_variable) && arithTrig[i] == ')') {
					char* toReplace = getDynamicCharArray("", "toReplace");
					sprintf(toReplace, "^_(%s)", check_variable);
					char* replacement = getDynamicCharArray("", "replacement");
					sprintf(replacement, "^(_%s)", check_variable);
					replace(toReplace, replacement, arithTrig);
					sprintf(arithTrig, expressionF);
					_delete(toReplace, "toReplace");
					toReplace = nullptr;
					_delete(replacement, "replacement");
					replacement = nullptr;
				}
				_delete(check_variable, "check_variable");
				check_variable = nullptr;
			}
		}
		replaceTimes = 0;
		_delete(letterScan, "letterScan");
		letterScan = nullptr;
		_delete(toTest, "toTest");
		toTest = nullptr;
		_delete(functionP, "functionP");
		functionP = nullptr;
		_delete(paTrig, "paTrig");
		paTrig = nullptr;
		_delete(varCandidate, "varCandidate");
		varCandidate = nullptr;
		_delete(finalReplacement, "finalReplacement");
		finalReplacement = nullptr;
		_delete(readLetter, "readLetter");
		readLetter = nullptr;
		_delete(newArithTrig, "newArithTrig");
		newArithTrig = nullptr;
		_delete(variableCheck, "variableCheck");
		variableCheck = nullptr;
		sprintf(expressionF, "%s", arithTrig);
	}
}
void openTxt() {
	FILE* open = NULL;
	open = fopen(expressionF, "r");
	char* openFile = getDynamicCharArray("", "openFile");
	if (open != NULL) {
		fclose(open);
		sprintf(openFile, "notepad.exe %s", expressionF);
		system(openFile);
	}
	_delete(openFile, "openFile");
	openFile = nullptr;
}
bool isVariable(char* variable) {
	renamer(variable);
	char* variableF = getDynamicCharArray("", "variableF");
	sprintf(variableF, expressionF);
	if (higherPrecision == 1) {
		processVariable<mp_float>(variableF);
	}
	else {
		processVariable<double>(variableF);
	}
	_delete(variableF, "variableF");
	variableF = nullptr;

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
		(TCHAR)' ',
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
	FILE* open = NULL, * pathReader = NULL;
	char* contents = getDynamicCharArray("", "contents");
	char* atcName = getDynamicCharArray("\\Advanced Trigonometry Calculator", "atcName");
	char* atcPAth = getDynamicCharArray("", "atcPAth");
	int w = 0, i = 0, s = 0, j = 0, tested = 0;
	open = fopen("atc_path.txt", "r");
	FILE* test = NULL;
	char* testPath = getDynamicCharArray("", "testPath");
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
			for (w = 0; w < abs((int)strlen(contents)); w++) {
				if (contents[w] == atcName[0]) {
					s = w;
					i = 0;
					while (contents[w] == atcName[i] && w < abs((int)strlen(contents))) {
						i++; w++;
					}
					if (i == abs((int)strlen(atcName))) {
						w = s;
						while (contents[w] != ';' && w != 0) {
							w--;
						}
						w++;
						j = 0;
						while (contents[w] != ';' && w < abs((int)strlen(contents))) {
							atcPAth[j] = contents[w];
							w++; j++;
						}
						atcPAth[j] = '\0';
						if (atcPAth[abs((int)strlen(atcPAth)) - 2] == ' ') {
							atcPAth[abs((int)strlen(atcPAth)) - 2] = '\0';
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
	_delete(contents, "contents"); contents = nullptr;
	_delete(atcName, "atcName"); atcName = nullptr;
	_delete(atcPAth, "atcPAth"); atcPAth = nullptr;
	_delete(testPath, "testPath"); testPath = nullptr;
}

void getATCPath() {
	if (forsprintf == nullptr) {
		forsprintf = getDynamicCharArray("", "forsprintf");
	}
	FILE* aPath = NULL;
	aPath = fopen("atc_path.txt", "r");
	if (aPath == NULL) {
		aPath = fopen("atc_path.txt", "w");
		TCHAR NPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, NPath);
		wcstombs(atcPath, NPath, wcslen(NPath) + 1);
		fprintf(aPath, "%s", atcPath);
		sprintf(forsprintf, "%s", atcPath);
		sprintf(saveATCPath, "%s", forsprintf);
		fclose(aPath);
	}
	else {
		fgets(atcPath, DIM, aPath);
		fclose(aPath);
		if (atcPath[abs((int)strlen(atcPath)) - 2] == ' ') {
			atcPath[abs((int)strlen(atcPath)) - 2] = '\0';
		}
		sprintf(forsprintf, "%s", atcPath);
		sprintf(saveATCPath, "%s", forsprintf);
		FILE* test = NULL;
		char* testPath = getDynamicCharArray("", "testPath");
		sprintf(forsprintf, "%s\\License.txt", atcPath);
		sprintf(testPath, "%s", forsprintf);
		test = fopen(testPath, "r");
		if (test == NULL) {
			test = fopen("atc_path.txt", "w");
			TCHAR NPath[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, NPath);
			wcstombs(atcPath, NPath, wcslen(NPath) + 1);
			fprintf(test, "%s", atcPath);
			sprintf(saveATCPath, "%s", atcPath);
			fclose(test);
		}
		if (testPath != nullptr) {
			_delete(testPath, "testPath");
			testPath = nullptr;
		}
	}
}

template <typename T>
void getCharArray() {
	replaceTimes = 0;
	char* value = getDynamicCharArray("", "value");
	sprintf(expressionF, "");
	T Value = getValue<T>();
	if (isEqual("x", expressionF)) {
		sprintf(value, "x");
	}
	else {
		sprintf(value, "%s", convert2Exponential(Value));
	}
	if (isContained("-", value)) {
		replace("-", "_", value);
	}
	else {
		sprintf(expressionF, value);
	}
	_delete(value, "value");
	value = nullptr;
}

template <typename T>
T solve(char* equation) {
	char* colectCoeff = getDynamicCharArray("", "colectCoeff");
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
		while (verifyValue(equation[i]) && verifyLetter(equation[i + 1]) == (bool)false) {
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
		char* equationF = getDynamicCharArray("", "equationF");
		sprintf(equationF, "(%s)/(%s)", equation, colectCoeff);
		T answer = solver<T>(equationF);
		_delete(colectCoeff, "colectCoeff");
		colectCoeff = nullptr;
		_delete(equationF, "equationF");
		equationF = nullptr;
		return answer;
	}
	_delete(colectCoeff, "colectCoeff");
	colectCoeff = nullptr;
	return 0;
}
template void getCharArray<double>();
template void getCharArray<mp_float>();
template double solve<double>(char*);
template mp_float solve<mp_float>(char*);
template int toSolve<mp_float>(int re);
template  int toSolve<double>(int re);
template <typename T>
int toSolve(int re) {
	FILE* file = NULL;
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\disable_txt_detector.txt", atcPath);
	int retry = 0;
	while (file == NULL && retry < 7) {
		file = fopen(toOpen, "r");
		retry++;
	}
	if (file == NULL) {
		char* option = getDynamicCharArray("", "option"); char* directory = getDynamicCharArray("", "directory");
		sprintf(directory, "%s\\To solve\\", atcPath);
		int k = 0, numFiles = 0, i = 0, numFilesSolved = 0;
		DIR* d;
		struct dirent* dir;
		d = opendir(directory);
		char* filename = getDynamicCharArray("", "filename");
		char* txtFiles = getDynamicCharArray("", "txtFiles");
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
							char* path = getDynamicCharArray("", "path");
							sprintf(path, "%s%s", directory, filename);
							int b = 0, m = 0;
							char* addChars = getDynamicCharArray("_answers.txt", "addChars");
							while ((path[b] == '.' && path[b + 1] == 't' && path[b + 2] == 'x' && path[b + 3] == 't') == false) {
								b++;
							}
							while (m < abs((int)strlen(addChars))) {
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
							_delete(path, "path");
							path = nullptr;
							_delete(addChars, "addChars");
							addChars = nullptr;
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
					action = (int)getValue<T>();
					if (action != 0 && action != 1) {
						puts("(Yes -> 1 / No -> 0)");
					}
				}
				puts(" ");
				if (action == 1) {
					char* path = getDynamicCharArray("", "path");
					char* fileName = getDynamicCharArray("", "fileName");
					int i = 0, j = 0;
					while (numFiles > 0) {
						j = 0;
						while (txtFiles[i] != '\n' && i < abs((int)strlen(txtFiles))) {
							fileName[j] = txtFiles[i];
							j++; i++;
						}
						fileName[j] = '\0';
						i++;
						numFiles--;
						sprintf(path, "%s%s", directory, fileName);
						processTxt<T>(path, re);
					}
					printf("==> Check the folder \"To solve\" to see the answers file(s) generated. Enter \"to solve\". <== \n\n");
					_delete(path, "path");
					path = nullptr;
					_delete(fileName, "fileName");
					fileName = nullptr;
				}
				if (action == 0) {
					int disable = -1;
					printf("Do you want to disable the feature? (Yes -> 1 / No -> 0)\n");
					while (disable != 0 && disable != 1) {
						I_O = true;
						disable = (int)getValue<T>();
						if (disable != 0 && disable != 1) {
							puts("(Yes -> 1 / No -> 0)");
						}
					}
					puts(" ");
					if (disable == 1) {
						FILE* dis = NULL;
						char* toOpen = getDynamicCharArray("", "toOpen");
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
						_delete(toOpen, "toOpen");
						toOpen = nullptr;
					}
				}
			}
			else {
				_delete(toOpen, "toOpen");
				toOpen = nullptr;
				_delete(option, "option");
				option = nullptr;
				_delete(directory, "directory");
				directory = nullptr;
				_delete(filename, "filename");
				filename = nullptr;
				_delete(txtFiles, "txtFiles");
				txtFiles = nullptr;
				return 0;
			}
		}
		_delete(option, "option");
		option = nullptr;
		_delete(directory, "directory");
		directory = nullptr;
		_delete(filename, "filename");
		filename = nullptr;
		_delete(txtFiles, "txtFiles");
		txtFiles = nullptr;
	}
	else {
		if (file != NULL) {
			fclose(file);
		}
	}
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
	return 0;
}

template <typename T>
void currentSettings() {
	solving = false;
	FILE* open = NULL;
	puts("");
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\mode.txt", atcPath);
	open = fopen(toOpen, "r");
	char* info = getDynamicCharArray("", "info");
	int state = 0;
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		state = (int)solveMath<T>(info);
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
		state = (int)solveMath<T>(info);
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
		state = (int)solveMath<T>(info);
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
		state = (int)solveMath<T>(info);
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
	sprintf(toOpen, "%s\\higherPrecision.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		state = (int)solveMath<T>(info);
		switch (state) {
		case 0:
			puts("Higher Precision------------------------> Enabled DISABLED | Info: Enter \"higher precision\" to change.");
			break;
		case 1:
			puts("Higher Precision------------------------> ENABLED Disabled | Info: Enter \"higher precision\" to change.");
			break;
		}
	}
	else {
		puts("Higher Precision------------------------> Enabled DISABLED | Info: Enter \"higher precision\" to change.");
	}
	open = NULL;
	sprintf(toOpen, "%s\\verboseResolution.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(info, 200, open);
		fclose(open);
		state = (int)solveMath<T>(info);
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
	char* value = getDynamicCharArray("", "value");
	if (open != NULL) {
		for (i = 0; (info[i] = fgetc(open)) != EOF; i++) {
			value[e] = info[i];
			if (info[i] != '\n') {
				e++;
			}
			if (value[e] == '\n' && a == 1) {
				value[e] = '\0';
				x = atoi(value);
				a = 2; e = 0;
			}
			if (value[e] == '\n' && a == 2) {
				value[e] = '\0';
				y = atoi(value);
				a = 3; e = 0;
			}
			if (value[e] == '\n' && a == 3) {
				value[e] = '\0';
				width = atoi(value);
				a = 4; e = 0;
			}
			if (value[e] == '\n' && a == 4) {
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
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
	_delete(info, "info");
	info = nullptr;
	_delete(value, "value");
	value = nullptr;
}



void on_start() {
	char* Path = getDynamicCharArray("", "Path");
	sprintf(Path, "%s\\temp.txt", atcPath);
	FILE* Try = NULL;
	Try = fopen(Path, "r");
	if (Try != NULL) {
		fclose(Try);
		char* toOpen = getDynamicCharArray("", "toOpen");
		sprintf(toOpen, "del \"%s\"", Path);
		system(toOpen);
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
	}
	sprintf(Path, "%s\\temp_answers.txt", atcPath);
	Try = fopen(Path, "r");
	if (Try != NULL) {
		fclose(Try);
		char* toOpen = getDynamicCharArray("", "toOpen");
		sprintf(toOpen, "del \"%s\"", Path);
		system(toOpen);
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
	}
	FILE* open = NULL;
	char* onStart = getDynamicCharArray("", "onStart");
	int Colors = 1, Dimensions = 2, Window = 3;
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\onStart.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(onStart, 100, open);
		fclose(open);
		if (isContained("enableatcintro", onStart)) {
			char* toOpen = getDynamicCharArray("", "toOpen");
			sprintf(toOpen, "/C \"del \"%s\\aboutDisabled.txt\" &del \"%s\\onStart.txt\"", atcPath, atcPath);
			using namespace std;
			std::string s = string(toOpen);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
			Sleep(1000);
			_delete(toOpen, "toOpen");
			toOpen = nullptr;

		}
		if (onStart[0] == 'r' && onStart[1] == 'e' && onStart[2] == 's' && onStart[3] == 'e' && onStart[4] == 't' && onStart[5] == 'a' && onStart[6] == 'l' && onStart[7] == 'l' && onStart[8] == '\0') {
			char* toOpen = getDynamicCharArray("", "toOpen");
			sprintf(toOpen, "/C \"del \"%s\\history.txt\"&del \"%s\\graph.txt\"&del \"%s\\variables.txt\"&del \"%s\\higherPrecision.txt\"&del \"%s\\renamedVar.txt\"&del \"%s\\pathName.txt\"&del \"%s\\predefinedTxt.txt\"&del \"%s\\calendar.txt\"&del \"%s\\numSystems.txt\"&del \"%s\\siPrefixes.txt\"&rmdir /Q /S \"%s\\Strings\"&del \"%s\\actualTime.txt\"&del \"%s\\colors.txt\"&del \"%s\\dimensions.txt\"& del \"%s\\verboseResolution.txt\"&del \"%s\\window.txt\"&del \"%s\\mode.txt\"&del \"%s\\onStart.txt\"&del \"%s\\disable_txt_detector.txt\"&del \"%s\\stringVariable.txt\"&mkdir \"%s\\Strings\"&del \"%s\\atc_path.txt\"&del \"%s\\aboutDisabled.txt\"", atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath);
			using namespace std;
			std::string s = string(toOpen);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
			Sleep(1000);
			applySettings(Colors);
			applySettings(Window);
			applySettings(Dimensions);
			_delete(toOpen, "toOpen");
			toOpen = nullptr;
		}
		if (onStart[0] == 'r' && onStart[1] == 'e' && onStart[2] == 's' && onStart[3] == 'e' && onStart[4] == 't' && onStart[5] == 's' && onStart[6] == 'e' && onStart[7] == 't' && onStart[8] == 't' && onStart[9] == 'i' && onStart[10] == 'n' && onStart[11] == 'g' && onStart[12] == 's' && onStart[13] == '\0') {
			char* toOpen = getDynamicCharArray("", "toOpen");
			sprintf(toOpen, "/C \"del \"%s\\numSystems.txt\"&del \"%s\\graph.txt\"&del \"%s\\siPrefixes.txt\"&del \"%s\\higherPrecision.txt\"&del \"%s\\actualTime.txt\"&del \"%s\\colors.txt\"&del \"%s\\dimensions.txt\"&del \"%s\\window.txt\"&del \"%s\\mode.txt\"&del \"%s\\verboseResolution.txt\"&del \"%s\\onStart.txt\"\"", atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath, atcPath);
			using namespace std;
			std::string s = string(toOpen);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
			Sleep(1000);
			applySettings(Colors);
			applySettings(Window);
			applySettings(Dimensions);
			_delete(toOpen, "toOpen");
			toOpen = nullptr;
		}
	}
	_delete(Path, "Path");
	Path = nullptr;
	_delete(onStart, "onStart");
	onStart = nullptr;
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
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

template <typename T>
void complexNumber(T a, T b) {
	if (solverRunning == (bool)false) {
		processingOK = -1;
	}
	verify = 0;
	convertComplex2Exponential(a, b);
	if (a > 0 && b > 0) {
		printf("%s+%si\n", respR, respI);
	}
	else {
		if (a > 0 && b < 0) {
			printf("%s%si\n", respR, respI);
		}
		else {
			if (a < 0 && b > 0) {
				printf("%s+%si\n", respR, respI);
			}
			else {
				if (a < 0 && b < 0) {
					printf("%s%si\n", respR, respI);
				}
				else {
					if (a == 0 && b == 0) {
						printf("%s\n", convert2Exponential(a));
					}
					else {
						if (a == 0 && b != 0) {
							printf("%si\n", convert2Exponential(b));
						}
						else {
							if (a != 0 && b == 0) {
								printf("%s\n", convert2Exponential(a));
							}
							else {
								printf("%s+%si\n", respR, respI);
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

bool IsPreviousToWindowsVista()
{
	bool previousToVista = false;

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
bool IsWindows11OrGreater()
{
	typedef LONG(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);
	HMODULE ntdll = GetModuleHandleA("ntdll.dll");
	if (ntdll == NULL) {
		return false;
	}
	RtlGetVersionPtr rtlGetVersion = (RtlGetVersionPtr)GetProcAddress(ntdll, "RtlGetVersion");
	if (rtlGetVersion == NULL) {
		return false;
	}
	RTL_OSVERSIONINFOW versionInfo;
	ZeroMemory(&versionInfo, sizeof(versionInfo));
	versionInfo.dwOSVersionInfoSize = sizeof(versionInfo);
	if (rtlGetVersion(&versionInfo) != 0) {
		return false;
	}
	return versionInfo.dwMajorVersion > 10 ||
		(versionInfo.dwMajorVersion == 10 && versionInfo.dwBuildNumber >= 22000);
}

bool shouldDisableATCIntroByDefault()
{
	return IsWindows11OrGreater();
}
template<typename T>
char character_to_prefDet(T n) {
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
template int variableValidator<double>(char* variable);
template int variableValidator<mp_float>(char* variable);

bool isReservedVariableName(const char* variable) {
	if (variable == nullptr || variable[0] == '\0') {
		return true;
	}
	const char* reservedNames[] = {
		"i", "e", "pi", "INF",
		"B", "O", "H", "P", "D", "b",
		"res", "atc",
		"cos", "acos", "sin", "asin", "tan", "atan",
		"sec", "asec", "cosec", "acosec", "cotan", "acotan",
		"log", "ln", "rest", "quotient", "sqrt", "cbrt", "afact",
		"cosh", "acosh", "sinh", "asinh", "tanh", "atanh",
		"sech", "asech", "cosech", "acosech", "cotanh", "acotanh",
		"sinc", "gerror", "gerrorinv", "gerrorc", "gerrorcinv",
		"qfunc", "qfuncinv", "solver", "det", "abs",
		"strlen", "countoccurrences", "iscontained", "iscontainedbyindex",
		"iscontainedvariable", "isequal", "isvariable", "istowrite",
		"for", "calc", "max", "min", "avg",
		"linsnum", "colsnum", "getlins", "getcols"
	};
	for (int i = 0; i < (int)(sizeof(reservedNames) / sizeof(reservedNames[0])); i++) {
		if (strcmp(variable, reservedNames[i]) == 0) {
			return true;
		}
	}
	return false;
}
template <typename T>
int variableValidator(char* variableFF) {
	char* variableG = getDynamicCharArray("", "variableG");
	sprintf(variableG, "%s", variableFF);
	int validate = 0, i = 0, h = -1, abc = 0, j = 0, k = 0, sD = 0;

	char* varLetters = getDynamicCharArray("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", "varLetters");
	T arith = 0, func = 0;
	for (k = 0; k < abs((int)strlen(variableG)); k++) {
		for (i = 0; i < abs((int)strlen(varLetters)); i++) {
			if (variableG[k] == varLetters[i]) {
				j++;
				break;
			}
		}
	}
	FILE* user = NULL;
	char* path_user = getDynamicCharArray("", "path_user");
	sprintf(path_user, "%s\\User functions\\%s.txt", atcPath, variableG);
	user = fopen(path_user, "r");
	bool variable_inside_user_function;
	variable_inside_user_function = isContainedInUserFunction(variableG);
	if (j != abs((int)strlen(variableG)) || j == 0 && abs((int)strlen(variableG)) == 0 || user != NULL || variable_inside_user_function) {
		if (user != NULL) {
			fclose(user);
		}
		user = NULL;
		h = 0;
		_delete(variableG, "variableG");
		variableG = nullptr;
		_delete(varLetters, "varLetters");
		varLetters = nullptr;
		_delete(path_user, "path_user");
		path_user = nullptr;
		return h;
	}
	FILE* var = NULL, * var1 = NULL;
	i = 0;
	abc = abs((int)strlen(variableG));
	valid = 0;
	if (isReservedVariableName(variableG)) {
		_delete(variableG, "variableG");
		variableG = nullptr;
		_delete(varLetters, "varLetters");
		varLetters = nullptr;
		_delete(path_user, "path_user");
		path_user = nullptr;
		return 0;
	}
	sprintf(revariable, "%s", variableG);
	i = 0;
	variableG[abc] = '\0';
	processVariable<T>(revariable);
	char* saveVariable = getDynamicCharArray(variableG, "saveVariable");
	renamer(variableG);
	sprintf(variableG, "%s", expressionF);
	arith = initialProcessor<T>(variableG, (T)0);

	if ((variableG[0] == 'E' || variableG[0] == 'B' || variableG[0] == 'O' || variableG[0] == 'H' || variableG[0] == 'P') && variableG[1] == '=') {
		arith = 10;
	}
	matrixMode = 0;
	sprintf(matrixResult, "");

	sprintf(forsprintf, "%s?", variableG);
	if (abs((int)strlen(variableG)) >= 0) {
		if (abs((int)strlen(forsprintf)) >= 0) {
			char* variableT = getDynamicCharArray(forsprintf, "variableT");
			char* testPrefix = getDynamicCharArray("", "testPrefix");
			for (i = 0; i < abs((int)strlen(variableG)); i++) {
				testPrefix[i] = variableG[i];
			}
			testPrefix[i] = '\0';
			T prefix = 0;
			if (testPrefix[0] == 'P') {
				testPrefix[0] = '1';
				for (i = 1; i < abs((int)strlen(testPrefix)); i++) {
					testPrefix[i] = testPrefix[i - 1];
				}
				testPrefix[i] = '\0';

				prefix = arithSolver<T>(testPrefix, (T)0);
			}
			func = functionProcessor<T>(variableT, 0.3, 1.0, 0, "");
			_delete(variableT, "variableT");
			variableT = nullptr;

			processVariable<T>(revariable);
			if (h == 1 && valid == 0 && arith == 0 && func == 0 && prefix == 0) {
				i = 0;
				char* vari = getDynamicCharArray("", "vari");
				if (isEqual(context, "main")) {
					sprintf(vari, "%s", saveRenamedVariablesTextFile);
				}
				if (isEqual(context, "processTxt")) {
					sprintf(vari, "%s", saveRenamedTxtVariablesTextFile);
				}
				if (isEqual(context, "script")) {
					sprintf(vari, "%s", saveScriptRenamedVariablesTextFile);
				}
				if (isEqual(context, "userFunctions")) {
					sprintf(vari, "%s", saveUserFunctionsRenamedVariablesTextFile);
				}
				char* line = getDynamicCharArray("", "line");

				sprintf(line, "%s %s\n", saveVariable, revariable);
				if (!(isContained(line, vari) && (strStart == 0 || vari[strStart - 1] == '\n'))) {
					if (isEqual(context, "main")) {
						sprintf(saveRenamedVariablesTextFile, "%s%s", saveRenamedVariablesTextFile, line);
					}
					if (isEqual(context, "processTxt")) {
						sprintf(saveRenamedTxtVariablesTextFile, "%s%s", saveRenamedTxtVariablesTextFile, line);
					}
					if (isEqual(context, "script")) {
						sprintf(saveScriptRenamedVariablesTextFile, "%s%s", saveScriptRenamedVariablesTextFile, line);
					}
					if (isEqual(context, "userFunctions")) {
						sprintf(saveUserFunctionsRenamedVariablesTextFile, "%s%s", saveUserFunctionsRenamedVariablesTextFile, line);
					}
				}
				i = 0;
				_delete(line, "line");
				line = nullptr;
				_delete(vari, "vari");
				vari = nullptr;
			}
			else {
				if (h == 1 && valid == 0 && (arith != 0 || func != 0 || prefix != 0)) {
					h = 2;
				}
			}
			_delete(testPrefix, "testPrefix");
		}
	}
	_delete(variableG, "variableG");
	variableG = nullptr;

	_delete(varLetters, "varLetters");
	varLetters = nullptr;
	_delete(path_user, "path_user");
	_delete(saveVariable, "saveVariable");
	saveVariable = nullptr;
	return h;
}

template <typename T>

T prefToNumber(char prefix) {
	T result = 0;
	if (prefix == 'Y') {
		result = pot(10.0, 24.0, 1);
		return result;
	}
	if (prefix == 'Z') {
		result = pot(10.0, 21.0, 1);
		return result;
	}
	if (prefix == 'E') {
		result = pot(10.0, 18.0, 1);
		return result;
	}
	if (prefix == 'P') {
		result = pot(10.0, 15.0, 1);
		return result;
	}
	if (prefix == 'T') {
		result = pot(10.0, 12.0, 1);
		return result;
	}
	if (prefix == 'G') {
		result = pot(10.0, 9.0, 1);
		return result;
	}
	if (prefix == 'M') {
		result = pot(10.0, 6.0, 1);
		return result;
	}
	if (prefix == 'k') {
		result = pot(10.0, 3.0, 1);
		return result;
	}
	if (prefix == 'h') {
		result = pot(10.0, 2.0, 1);
		return result;
	}
	if (prefix == 'D') {
		result = pot(10.0, 1.0, 1);
		return result;
	}
	if (prefix == 'd') {
		result = pot(10.0, -1.0, 1);
		return result;
	}
	if (prefix == 'c') {
		result = pot(10.0, -2.0, 1);
		return result;
	}
	if (prefix == 'm') {
		result = pot(10.0, -3.0, 1);
		return result;
	}
	if (prefix == 'u') {
		result = pot(10.0, -6.0, 1);
		return result;
	}
	if (prefix == 'n') {
		result = pot(10.0, -9.0, 1);
		return result;
	}
	if (prefix == 'p') {
		result = pot(10.0, -12.0, 1);
		return result;
	}
	if (prefix == 'f') {
		result = pot(10.0, -15.0, 1);
		return result;
	}
	if (prefix == 'a') {
		result = pot(10.0, -18.0, 1);
		return result;
	}
	if (prefix == 'z') {
		result = pot(10.0, -21.0, 1);
		return result;
	}
	if (prefix == 'y') {
		result = pot(10.0, -24.0, 1);
		return result;
	}
	return result;
}

template <typename T>
T numericalSystems(char* numSystem) {
	T result = 0;
	char system = ' ';
	int i, j = 0;
	system = numSystem[0];
	if (numSystem[1] == '_') {
		numSystem[1] = '-';
	}
	for (i = 1; i < abs((int)strlen(numSystem)); i++) {
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
		result = binaryToDecimal<T>(numSystem);
	}
	if (system == 'O') {
		result = octalToDecimal<T>(numSystem);
	}
	if (system == 'H') {
		result = hexadecimalToDecimal<T>(numSystem);
	}
	return result;
}

template <typename T>
T processVariable(char* variable) {
	validVar = 0;
	T varValue = 0;
	FILE* open = NULL;
	int i, g, h, y, l = 0, lth = 0, cou = 0;

	char* vari = getDynamicCharArray("", "vari"); char* va = getDynamicCharArray("", "va"); char* value = getDynamicCharArray("", "value");
	char* pointer;
	i = 0;
	bool defaultVariable = false;
	if (isEqual(context, "main")) {
		sprintf(vari, "%s", saveVariablesTextFile);
		defaultVariable = true;
	}
	if (isEqual(context, "processTxt")) {
		sprintf(vari, "%s", saveTxtVariablesTextFile);
		defaultVariable = true;
	}
	if (isEqual(context, "script")) {
		sprintf(vari, "%s", saveScriptVariablesTextFile);
		defaultVariable = true;
	}
	if (isEqual(context, "userFunctions")) {
		sprintf(vari, "%s", saveUserFunctionsVariablesTextFile);
		defaultVariable = true;
	}
	if (!defaultVariable) {
		char* toOpen = getDynamicCharArray("", "toOpen");
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
			open = fopen(toOpen, "r");
			i++;
		}
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
	}
	if (i < 100) {
		if (!defaultVariable) {
			for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
			fclose(open);
			vari[i] = '\0';
		}
	}
	lth = abs((int)strlen(vari));
	i = 0;
	char* real = getDynamicCharArray("", "real"); char* imag = getDynamicCharArray("", "imag");

	for (i = 0; i < abs((int)strlen(vari)); i++) {
		g = 0;
		int j = i;
		while (vari[j] != ' ' && j < abs((int)strlen(vari))) {
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
		for (y = 0; y < abs((int)strlen(va)); y++) {
			if (va[y] == variable[y]) {
				g++;
			}
		}
		vari[lth] = '\0';

		if (g == abs((int)strlen(va)) && abs((int)strlen(variable)) == g && j == g && g != 0) {
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
			if ((isContained(":", value) || isContained("*", value)) && check4Vector == 1 && (!runningScript || !haveCreatedDynamicMatrix)) {
				convert2Vector(value);
				check4Vector = 1;

				if (!checkMatrixIndex) {
					check4Vector = 2;
					sprintf(matrixValue, "%s", value);
				}
				else {
					matrixMode = 2;
					sprintf(matrixResult, "");
					sprintf(matrixValue, "");

				}


			}
			if (space == 0) {
				resultR = strtod(value, &pointer);
			}
			else {
				y = 0;
				while (value[y] != ' ') {
					real[y] = value[y];
					y++;
				}
				real[y] = '\0';
				y++;
				gh = 0;
				while (y < abs((int)strlen(value))) {
					imag[gh] = value[y];
					y++; gh++;
				}
				imag[gh] = '\0';
				resultR = strtod(real, &pointer);
				resultI = strtod(imag, &pointer);
				if (!runningScript) {
					if (isEqual("T", variable) && (abs((int)strlen(matrixResult)) || abs((int)strlen(saveMatrixAns)) > 0)) {
						resultR = -7654321;
						resultI = 0;
					}
					if (isEqual("R", variable) && (abs((int)strlen(matrixResult)) || abs((int)strlen(saveMatrixAns)) > 0)) {
						resultR = -1234567;
						resultI = 0;
					}
				}
				varValue = precisionValueTo<T>(resultR);

			}
			break;
		}
	}

	if (validVar != 1 && abs((int)strlen(saveVariablesTextFile)) > 0) {
		sprintf(vari, "%s", saveVariablesTextFile);
		lth = abs((int)strlen(vari));
		i = 0;
		for (i = 0; i < abs((int)strlen(vari)); i++) {
			g = 0;
			int j = i;
			while (vari[j] != ' ' && j < abs((int)strlen(vari))) {
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
			for (y = 0; y < abs((int)strlen(va)); y++) {
				if (va[y] == variable[y]) {
					g++;
				}
			}
			vari[lth] = '\0';
			if (g == abs((int)strlen(va)) && abs((int)strlen(variable)) == g && j == g && g != 0) {
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
				if ((isContained(":", value) || isContained("*", value)) && check4Vector == 1 && (!runningScript || !haveCreatedDynamicMatrix)) {
					convert2Vector(value);
					check4Vector = 1;
					if (!checkMatrixIndex) {
						check4Vector = 2;
						sprintf(matrixValue, "%s", value);

					}
					else {
						matrixMode = 2;
						sprintf(matrixResult, "");
						sprintf(matrixValue, "");

					}

				}
				if (space == 0) {
					resultR = strtod(value, &pointer);
				}
				else {
					y = 0;
					while (value[y] != ' ') {
						real[y] = value[y];
						y++;
					}
					real[y] = '\0';
					y++;
					gh = 0;
					while (y < abs((int)strlen(value))) {
						imag[gh] = value[y];
						y++; gh++;
					}
					imag[gh] = '\0';
					resultR = strtod(real, &pointer);
					resultI = strtod(imag, &pointer);
					if (!runningScript) {
						if (isEqual("T", variable) && (abs((int)strlen(matrixResult)) || abs((int)strlen(saveMatrixAns)) > 0)) {
							resultR = -7654321;
							resultI = 0;
						}
						if (isEqual("R", variable) && (abs((int)strlen(matrixResult)) || abs((int)strlen(saveMatrixAns)) > 0)) {
							resultR = -1234567;
							resultI = 0;
						}
					}
					varValue = precisionValueTo<T>(resultR);

				}
				break;
			}
		}
	}
	if (vari != NULL) {
		_delete(vari, "vari");
	}
	if (va != NULL) {
		_delete(va, "va");
	}
	if (value != NULL) {
		_delete(value, "value");
	}
	if (real != nullptr) {
		_delete(real, "real");
		real = nullptr;
	}
	if (imag != nullptr) {
		_delete(imag, "imag");
		imag = nullptr;
	}
	return varValue;
}
template double convertToNumber<double>(char* number);
template mp_float convertToNumber<mp_float>(char* number);
template <typename T>
T convertToNumber(char* number) {
	if (number[abs((int)strlen(number)) - 1] == '0' && number[abs((int)strlen(number)) - 2] == '.') {
		number[abs((int)strlen(number)) - 2] = '\0';
	}
	char* beforeDot = getDynamicCharArray("", "beforeDot");
	sprintf(beforeDot, "");
	char* afterDot = getDynamicCharArray("", "afterDot");
	sprintf(afterDot, "");
	char* afterExponent = getDynamicCharArray("", "afterExponent");
	sprintf(afterExponent, "");
	int i = 0;
	while (number[i] != '.' && number[i] != 'E' && i < abs((int)strlen(number))) {
		beforeDot[i] = number[i];
		i++;
	}
	beforeDot[i] = '\0';
	if (number[i] == '.') {
		i++;
		int j = 0;
		while (i < abs((int)strlen(number)) && number[i] != 'E') {
			afterDot[j] = number[i];
			j++; i++;
		}
		afterDot[j] = '\0';
	}
	int k = 0;
	if (number[i] == 'E') {
		i++;
		while (i < abs((int)strlen(number))) {
			afterExponent[k] = number[i];
			i++; k++;
		}
		afterExponent[k] = '\0';
	}
	T beforeDotNum = 0;
	int maxP = abs((int)strlen(beforeDot)) - 1;
	if (maxP >= 0) {
		int m = maxP, n = 0;
		while (n < abs((int)strlen(beforeDot))) {
			int d = beforeDot[n] - '0';
			beforeDotNum = beforeDotNum + d * pot<T>(10.0, (T)m, 1);
			n++;
			m--;
		}
	}
	T afterDotNum = 0;
	int minP = abs((int)strlen(afterDot)) - 1;
	if (minP >= 0) {
		int m = minP, n = 0;
		while (n < abs((int)strlen(afterDot))) {
			int d = afterDot[n] - '0';
			afterDotNum = afterDotNum + d * pot<T>(10.0, (T)(n + 1) * -1.0, 1);
			n++;
			m--;
		}
	}
	T afterExponentNum = 0;
	if (abs((int)strlen(afterExponent)) > 0) {
		if (afterExponent[0] == '-') {
			int h = 0;
			while (afterExponent[h + 1] != '\0' && h + 1 < abs((int)strlen(afterExponent))) {
				afterExponent[h] = afterExponent[h + 1];
				h++;
			}
			afterExponent[h] = '\0';
			afterExponentNum = convertToNumber<T>(afterExponent) * -1;
		}
		else {
			afterExponentNum = convertToNumber<T>(afterExponent);
		}
	}
	T result = afterDotNum + beforeDotNum;
	result = result * pot<T>(10.0, afterExponentNum, 1);
	_delete(beforeDot, "beforeDot");
	beforeDot = nullptr;
	_delete(afterDot, "afterDot");
	afterDot = nullptr;
	_delete(afterExponent, "afterExponent");
	afterExponent = nullptr;
	return result;
}

template <typename T>

T calcNow(char* toCalc, T result1, T result2) {
	if (creatingMatrix == 1) {
		sprintf(atcPath, "%s", saveATCPath);
	}
	sprintf(renamedVariable, "");
	resultR = 0; resultI = 0;
	feedbackValidation = 0;

	if (abs((int)strlen(toCalc)) != 0) {

		if (creatingMatrix) {
			runningScript = false;
		}
		char* expression = getDynamicCharArray(toCalc, "expression");
		feedbackValidation = 1;
		isFromSolveNow = true;
		solveNow<T>(expression, (T)0, (T)0);
		feedbackValidation = 0;
		if (verified == 0) {
			printf("Invalid expression: %s\n\n", toCalc);
		}
		_delete(expression, "expression");
		expression = nullptr;
	}
	else {
		verified = 1; resultR = 0; resultI = 0;
	}
	if (creatingMatrix == 1) {
		getATCPath();
	}
	return precisionValueTo<T>(resultR);
}

bool firstLetterVariable(char letter) {
	char* letters = getDynamicCharArray("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", "letters");
	int i = 0;
	for (i = 0; i < abs((int)strlen(letters)); i++) {
		if (letter == letters[i]) {
			_delete(letters, "letters");
			letters = nullptr;
			return true;
		}
	}
	_delete(letters, "letters");
	letters = nullptr;
	return false;
}

bool letterVariables(char letter) {
	char* letters = getDynamicCharArray("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", "letters");
	int i = 0;
	for (i = 0; i < abs((int)strlen(letters)); i++) {
		if (letter == letters[i]) {
			_delete(letters, "letters");
			letters = nullptr;
			return true;
		}
	}
	_delete(letters, "letters");
	letters = nullptr;
	return false;
}

bool verifyLetter(char letter) {
	char* letters = getDynamicCharArray("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", "letters");
	int i = 0;
	for (i = 0; i < abs((int)strlen(letters)); i++) {
		if (letter == letters[i]) {
			_delete(letters, "letters");
			letters = nullptr;
			return true;
		}
	}
	_delete(letters, "letters");
	letters = nullptr;
	return false;
}

bool verifyNumber(char number) {
	char* numbers = getDynamicCharArray("_0.123456789E", "numbers");
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			_delete(numbers, "numbers");
			numbers = nullptr;
			return true;
		}
	}
	_delete(numbers, "numbers");
	numbers = nullptr;
	return false;
}

bool verifyOperator(char operatorF) {
	char* numbers = getDynamicCharArray("+_^/*S,)", "numbers");
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (operatorF == numbers[i]) {
			_delete(numbers, "numbers");
			numbers = nullptr;
			return true;
		}
	}
	_delete(numbers, "numbers");
	numbers = nullptr;
	return false;
}
bool verifyOperators(char operatorF) {
	char* numbers = getDynamicCharArray("+-*/^", "numbers");
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (operatorF == numbers[i]) {
			_delete(numbers, "numbers");
			numbers = nullptr;
			return true;
		}
	}
	_delete(numbers, "numbers");
	numbers = nullptr;
	return false;
}
bool verifyForNumbers(char number) {
	char* numbers = getDynamicCharArray("_0.123456789E^xi", "numbers");
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			_delete(numbers, "numbers");
			numbers = nullptr;
			return true;
		}
	}
	_delete(numbers, "numbers");
	numbers = nullptr;
	return false;
}
bool verifyNumberExpression(char number) {
	char* numbers = getDynamicCharArray("_0.123456789Epiex(^)S", "numbers");
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			_delete(numbers, "numbers");
			numbers = nullptr;
			return true;
		}
	}
	_delete(numbers, "numbers");
	numbers = nullptr;
	return false;
}

int countOccurrences(char* to_find, char* expression) {
	char* expressionR = getDynamicCharArray("", "expressionR");
	char* to_findR = getDynamicCharArray("", "to_findR");
	int numberOccurrences = 0;
	replaceTimes = 0;
	sprintf(expressionR, "%s", expression);
	sprintf(to_findR, "%s", to_find);
	if (isContained(to_findR, expressionR)) {
		while (isContained(to_findR, expressionR)) {
			numberOccurrences++;
			char* cuttedExpression = getDynamicCharArray("", "cuttedExpression");
			int i = 0;
			int j = 0;
			while (i < strStart) {
				cuttedExpression[j] = expressionR[i];
				i++; j++;
			}
			i = strEnd;
			while (i < abs((int)strlen(expressionR))) {
				cuttedExpression[j] = expressionR[i];
				j++; i++;
			}
			cuttedExpression[j] = '\0';
			sprintf(expressionR, "%s", cuttedExpression);
			_delete(cuttedExpression, "cuttedExpression");
			cuttedExpression = nullptr;
		}
	}
	_delete(expressionR, "expressionR");
	expressionR = nullptr;
	_delete(to_findR, "to_findR");
	to_findR = nullptr;
	return numberOccurrences;
}


int deleteXOccurrences(char* to_find, char* expression, int x) {
	char* expressionR = getDynamicCharArray("", "expressionR");
	char* to_findR = getDynamicCharArray("", "to_findR");
	int numberOccurrences = 1;
	sprintf(expressionR, expression);
	sprintf(to_findR, to_find);
	if (isContained(to_findR, expressionR) && countOccurrences(to_findR, expressionR) >= x) {
		while (isContained(to_findR, expressionR) && numberOccurrences < x) {
			numberOccurrences++;
			char* cuttedExpression = getDynamicCharArray("", "cuttedExpression");
			int i = 0;
			int j = 0;
			while (i < strStart) {
				cuttedExpression[j] = expressionR[i];
				i++; j++;
			}
			i = strEnd;
			while (i < abs((int)strlen(expressionR))) {
				cuttedExpression[j] = expressionR[i];
				j++; i++;
			}
			cuttedExpression[j] = '\0';
			sprintf(expressionR, cuttedExpression);
			_delete(cuttedExpression, "cuttedExpression");
			cuttedExpression = nullptr;
		}
	}
	sprintf(expressionF, expressionR);
	_delete(expressionR, "expressionR");
	expressionR = nullptr;
	_delete(to_findR, "to_findR");
	to_findR = nullptr;
	return numberOccurrences;
}

bool verifyValue(char number) {
	char* numbers = getDynamicCharArray("_.0123456789*/^Epie", "numbers");
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			_delete(numbers, "numbers");
			numbers = nullptr;
			return true;
		}
	}
	_delete(numbers, "numbers");
	numbers = nullptr;
	return false;
}

bool verifyNumerator(char number) {
	char* numbers = getDynamicCharArray("_.0123456789*^Epie", "numbers");
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			_delete(numbers, "numbers");
			numbers = nullptr;
			return true;
		}
	}
	_delete(numbers, "numbers");
	numbers = nullptr;
	return false;
}
bool verifyFraction(char number) {
	char* numbers = getDynamicCharArray("_.0123456789Epie/", "numbers");
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			_delete(numbers, "numbers");
			numbers = nullptr;
			return true;
		}
	}
	_delete(numbers, "numbers");
	numbers = nullptr;
	return false;
}
bool verifyMultiplication(char number) {
	char* numbers = getDynamicCharArray("_.0123456789Epie*", "numbers");
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			_delete(numbers, "numbers");
			numbers = nullptr;
			return true;
		}
	}
	_delete(numbers, "numbers");
	numbers = nullptr;
	return false;
}

bool verifyForNumber(char number) {
	char* numbers = getDynamicCharArray("_.0123456789Epie", "numbers");
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			_delete(numbers, "numbers");
			numbers = nullptr;
			return true;
		}
	}
	_delete(numbers, "numbers");
	numbers = nullptr;
	return false;
}

bool verifyCoefficient(char number) {
	char* numbers = getDynamicCharArray("_.0123456789*Epie", "numbers");
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			_delete(numbers, "numbers");
			numbers = nullptr;
			return true;
		}
	}
	_delete(numbers, "numbers");
	numbers = nullptr;
	return false;
}

bool verifyNumerical(char number) {
	char* numbers = getDynamicCharArray("_-.0123456789ABCDEF", "numbers");
	int i = 0;
	for (i = 0; i < abs((int)strlen(numbers)); i++) {
		if (number == numbers[i]) {
			_delete(numbers, "numbers");
			numbers = nullptr;
			return true;
		}
	}
	_delete(numbers, "numbers");
	numbers = nullptr;
	return false;
}

bool verify4Printf(char chars) {
	char* printfChars = getDynamicCharArray("0123456789diuoxXfFeEgGaAcspn%-+#*.hljztL\"", "printfChars");
	int i = 0;
	for (i = 0; i < abs((int)strlen(printfChars)); i++) {
		if (chars == printfChars[i]) {
			_delete(printfChars, "printfChars");
			printfChars = nullptr;
			return true;
		}
	}
	_delete(printfChars, "printfChars");
	printfChars = nullptr;
	return false;
}

bool verifySpecifier(char chars) {
	char* printfChars = getDynamicCharArray("diuoxXfFeEgGaAcsp", "printfChars");
	int i = 0;
	for (i = 0; i < abs((int)strlen(printfChars)); i++) {
		if (chars == printfChars[i]) {
			_delete(printfChars, "printfChars");
			printfChars = nullptr;
			return true;
		}
	}
	_delete(printfChars, "printfChars");
	printfChars = nullptr;
	return false;
}

bool isToWrite(char* arith) {
	if (isEqual("NO_ANSWERS_FILE", arith)) {
		return false;
	}
	else {
		return true;
	}
}

bool verifyPrefix(char* prefix) {
	char* prefixes = getDynamicCharArray("Y,Z,E,P,T,G,M,k,h,da,d,c,m,u,n,p,f,a,z,y,", "prefixes");
	int i = 0, j = 0;
	for (i = 0; i < abs((int)strlen(prefix)); i++) {
		for (j = 0; j < abs((int)strlen(prefixes)); j++) {
			if (prefix[i] == prefixes[j] && i == 0) {
				while (prefix[i] == prefixes[j]) {
					i++; j++;
				}
				if (prefix[i] == '\0' && prefixes[j] == ',') {
					_delete(prefixes, "prefixes");
					prefixes = nullptr;
					return true;
				}
				i = 0;
			}
		}
	}
	_delete(prefixes, "prefixes");
	prefixes = nullptr;
	return false;
}

bool firstLetterFunction(char letter) {
	char* letters = getDynamicCharArray("castlrqgdm", "letters");
	int i = 0;
	for (i = 0; i < abs((int)strlen(letters)); i++) {
		if (letter == letters[i]) {
			_delete(letters, "letters");
			letters = nullptr;
			return true;
		}
	}
	_delete(letters, "letters");
	letters = nullptr;
	return false;
}

bool searchExtension(char* filename, char* extension) {
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

bool readyToSolve(char* paTh) {
	FILE* open = NULL;
	char* pathToFile = getDynamicCharArray("", "pathToFile");

	replaceTimes = 0;
	replace("\"", "", paTh);

	sprintf(pathToFile, "%s", expressionF);
	char* dataFromFile = getDynamicCharArray("", "dataFromFile");
	int i = 0;
	open = fopen(pathToFile, "r");
	if (open != NULL) {
		for (i = 0; (dataFromFile[i] = fgetc(open)) != EOF; i++);
		fclose(open);
		dataFromFile[i] = '\0';
		bool has_flag = isContained("SOLVE_NOW", dataFromFile);
		if (has_flag) {
			replace("SOLVE_NOW", "", dataFromFile);
			open = NULL;
			open = fopen(pathToFile, "w");
			if (open != NULL) {
				fprintf(open, "%s", expressionF);
				fclose(open);
			}
		}
		_delete(pathToFile, "pathToFile");
		pathToFile = nullptr;
		_delete(dataFromFile, "dataFromFile");
		dataFromFile = nullptr;
		return has_flag;
	}
	else {
		_delete(pathToFile, "pathToFile");
		pathToFile = nullptr;
		_delete(dataFromFile, "dataFromFile");
		dataFromFile = nullptr;
		return false;
	}
	_delete(pathToFile, "pathToFile");
	pathToFile = nullptr;
	_delete(dataFromFile, "dataFromFile");
	dataFromFile = nullptr;
	return false;
}

bool isContainedVariable(char* to_find, char* string) {
	int i = 0, j = 0, k = 0;
	char* check_variable = getDynamicCharArray("", "check_variable");
	for (i = 0; i < abs((int)strlen(string)); i++) {
		for (j = 0; j < abs((int)strlen(to_find)); j++) {
			if (to_find[j] == string[i] && firstLetterVariable(to_find[j]) && j == 0) {
				while (to_find[j] == string[i] && j < abs((int)strlen(to_find)) && i < abs((int)strlen(string))) {
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
				if (::isVariable(check_variable) == (bool)false) {
					_delete(check_variable, "check_variable");
					check_variable = nullptr;
					return false;
				}
				else {
					if (isContained(to_find, string) && abs((int)strlen(to_find)) != abs((int)strlen(string))) {
						_delete(check_variable, "check_variable");
						check_variable = nullptr;
						return true;
					}
					else {
						_delete(check_variable, "check_variable");
						check_variable = nullptr;
						return false;
					}
				}
			}
		}
	}
	_delete(check_variable, "check_variable");
	check_variable = nullptr;
	return false;
}

bool isContainedByIndex(char* to_find, char* string, int index) {
	int i = 0, j = 0;
	sprintf(charMaster, "");
	if (abs((int)strlen(charMaster)) == 0) {
		for (i = index; i < abs((int)strlen(string)); i++) {
			for (j = 0; j < abs((int)strlen(to_find)); j++) {
				if (to_find[j] == string[i] && j == 0) {
					strStart = i;
					while (to_find[j] == string[i] && j < abs((int)strlen(to_find)) && i < abs((int)strlen(string))) {
						j++;
						i++;
					}
					if (j == abs((int)strlen(to_find))) {
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
bool isContained(char* to_find, char* string) {
	int i = 0, j = 0;
	if (abs((int)strlen(charMaster)) == 0) {
		for (i = 0; i < abs((int)strlen(string)); i++) {
			for (j = 0; j < abs((int)strlen(to_find)); j++) {
				if (to_find[j] == string[i] && j == 0) {
					strStart = i;
					while (to_find[j] == string[i] && j < abs((int)strlen(to_find)) && i < abs((int)strlen(string))) {
						j++;
						i++;
					}
					if (j == abs((int)strlen(to_find))) {
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
					if (to_find[j] == string[i] && j == 0 && verifyLetter(string[i - 1]) == (bool)false && verifyNumber(string[i - 1]) == (bool)false) {
						strStart = i;
						while (to_find[j] == string[i] && j < abs((int)strlen(to_find)) && i < abs((int)strlen(string))) {
							j++;
							i++;
						}
						if (j == abs((int)strlen(to_find))) {
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
							while (to_find[j] == string[i] && j < abs((int)strlen(to_find)) && i < abs((int)strlen(string))) {
								j++;
								i++;
							}
							if (j == abs((int)strlen(to_find)) && verifyLetter(string[i - 1]) == (bool)false && verifyNumber(string[i - 1]) == (bool)false) {
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
				char* saveTo_find = getDynamicCharArray(to_find, "saveTo_find");
				sprintf(forsprintf, "%s%s", charMaster, saveTo_find);
				to_find = getDynamicCharArray(forsprintf, "to_find");
				for (i = 0; i < abs((int)strlen(string)); i++) {
					for (j = 0; j < abs((int)strlen(to_find)); j++) {
						if (to_find[j] == string[i] && j == 0) {
							strStart = i;
							while (to_find[j] == string[i] && j < abs((int)strlen(to_find)) && i < abs((int)strlen(string))) {
								j++;
								i++;
							}
							if (j == abs((int)strlen(to_find))) {
								strEnd = i;
								if (saveTo_find != nullptr) {
									_delete(saveTo_find, "saveTo_find");
									saveTo_find = nullptr;
								}
								return true;
							}
							else {
								i = strStart;
								break;
							}
						}
					}
				}
				sprintf(forsprintf, "%s%s", saveTo_find, charMaster);
				to_find = getDynamicCharArray(forsprintf, "to_find");
				for (i = 0; i < abs((int)strlen(string)); i++) {
					for (j = 0; j < abs((int)strlen(to_find)); j++) {
						if (to_find[j] == string[i] && j == 0) {
							strStart = i;
							while (to_find[j] == string[i] && j < abs((int)strlen(to_find)) && i < abs((int)strlen(string))) {
								j++;
								i++;
							}
							if (j == abs((int)strlen(to_find))) {
								strEnd = i;
								if (saveTo_find != nullptr) {
									_delete(saveTo_find, "saveTo_find");
									saveTo_find = nullptr;
								}
								return true;
							}
							else {
								i = strStart;
								break;
							}
						}
					}
				}
				if (saveTo_find != nullptr) {
					_delete(saveTo_find, "saveTo_find");
					saveTo_find = nullptr;
				}
			}
		}
	}
	return false;
}

bool isEqual(char* to_find, char* string) {
	int i = 0;
	while (to_find[i] == string[i] && i < abs((int)strlen(string)) && i < abs((int)strlen(to_find))) {
		i++;
	}
	if (to_find[i] == string[i] && to_find[i] == '\0' && string[i] == '\0') {
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

static int clampConsoleValue(int value, int minimum, int maximum) {
	if (value < minimum) {
		return minimum;
	}
	if (value > maximum) {
		return maximum;
	}
	return value;
}

static bool hasConsoleHandle(HANDLE handle) {
	DWORD mode = 0;
	return handle != INVALID_HANDLE_VALUE && handle != NULL && GetConsoleMode(handle, &mode);
}

static bool isWindowsTerminalHost() {
	char value[8] = "";
	return GetEnvironmentVariableA("WT_SESSION", value, sizeof(value)) > 0 ||
		GetEnvironmentVariableA("TERM_PROGRAM", value, sizeof(value)) > 0;
}

static bool enableWindowsTerminalVirtualSequences() {
	if (!isWindowsTerminalHost()) {
		return false;
	}
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD outMode = 0;
	if (!hasConsoleHandle(hOut) || !GetConsoleMode(hOut, &outMode)) {
		return false;
	}
	outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	return SetConsoleMode(hOut, outMode) != 0;
}

static int ansiColorFromConsoleColor(int color, bool background) {
	static const int ansiOrder[8] = { 0, 4, 2, 6, 1, 5, 3, 7 };
	int normalized = color & 0x07;
	int ansiColor = ansiOrder[normalized];
	if (color >= 8) {
		return (background ? 100 : 90) + ansiColor;
	}
	return (background ? 40 : 30) + ansiColor;
}

static const char* terminalRgbFromConsoleColor(int color) {
	static const char* rgb[16] = {
		"#000000", "#000080", "#008000", "#008080",
		"#800000", "#800080", "#808000", "#C0C0C0",
		"#808080", "#0000FF", "#00FF00", "#00FFFF",
		"#FF0000", "#FF00FF", "#FFFF00", "#FFFFFF"
	};
	return rgb[color & 0x0F];
}

void repaintConsoleViewportSafe() {
	if (!enableWindowsTerminalVirtualSequences()) {
		return;
	}
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		return;
	}
	int fg = csbi.wAttributes & 0x0F;
	int bg = (csbi.wAttributes >> 4) & 0x0F;
	printf("\x1b]10;%s\x07\x1b]11;%s\x07", terminalRgbFromConsoleColor(fg), terminalRgbFromConsoleColor(bg));
	printf("\x1b[%d;%dm\x1b[2J\x1b[H", ansiColorFromConsoleColor(fg, false), ansiColorFromConsoleColor(bg, true));
	fflush(stdout);
}

bool applyConsoleDimensionsSafe(int columns, int lines) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!hasConsoleHandle(hOut)) {
		return false;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		return false;
	}

	COORD largest = GetLargestConsoleWindowSize(hOut);
	if (largest.X <= 0) {
		largest.X = 160;
	}
	if (largest.Y <= 0) {
		largest.Y = 60;
	}

	SHORT currentColumns = (SHORT)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
	SHORT currentRows = (SHORT)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
	int targetColumns = clampConsoleValue(columns, 40, largest.X);
	int targetVisibleRows = lines <= 120 ? lines : largest.Y;
	targetVisibleRows = clampConsoleValue(targetVisibleRows, 20, largest.Y);
	if (isWindowsTerminalHost()) {
		targetColumns = clampConsoleValue(max(targetColumns, (int)currentColumns), 40, largest.X);
		targetVisibleRows = clampConsoleValue(max(targetVisibleRows, (int)currentRows), 20, largest.Y);
	}

	int targetBufferRows = lines;
	if (targetBufferRows < targetVisibleRows) {
		targetBufferRows = targetVisibleRows;
	}
	targetBufferRows = clampConsoleValue(targetBufferRows, targetVisibleRows, 2000);

	SMALL_RECT safeWindow = {
		0,
		0,
		(SHORT)(clampConsoleValue(currentColumns, 1, targetColumns) - 1),
		(SHORT)(clampConsoleValue(currentRows, 1, targetBufferRows) - 1)
	};
	SetConsoleWindowInfo(hOut, TRUE, &safeWindow);

	COORD bufferSize = { (SHORT)targetColumns, (SHORT)targetBufferRows };
	if (!SetConsoleScreenBufferSize(hOut, bufferSize)) {
		return false;
	}

	SMALL_RECT targetWindow = { 0, 0, (SHORT)(targetColumns - 1), (SHORT)(targetVisibleRows - 1) };
	SetConsoleWindowInfo(hOut, TRUE, &targetWindow);
	colsATC = targetColumns;
	linesATC = targetBufferRows;
	return true;
}

bool applyConsoleCommandDimensions(const char* setting) {
	if (setting == nullptr) {
		return false;
	}

	double parsedColumns = 0.0, parsedLines = 0.0;
	if (sscanf(setting, "MODE con cols=%lf lines=%lf", &parsedColumns, &parsedLines) != 2) {
		return false;
	}

	return applyConsoleDimensionsSafe((int)parsedColumns, (int)parsedLines);
}

bool applyConsoleWindowSafe(int x, int y, int width, int height) {
	HWND hwnd = GetConsoleWindow();
	if (hwnd == NULL || isWindowsTerminalHost()) {
		return false;
	}
	return MoveWindow(hwnd, x, y, width, height, FALSE) != 0;
}

void maximizeConsoleWindowSafe() {
	if (isWindowsTerminalHost()) {
		return;
	}
	HWND hwnd = GetConsoleWindow();
	if (hwnd == NULL) {
		return;
	}
	RECT workArea = { 0, 0, 0, 0 };
	int targetWidth = 1200;
	int targetHeight = 800;
	if (SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0)) {
		int workWidth = workArea.right - workArea.left;
		int workHeight = workArea.bottom - workArea.top;
		if (workWidth > 0 && targetWidth > workWidth - 80) {
			targetWidth = workWidth - 80;
		}
		if (workHeight > 0 && targetHeight > workHeight - 80) {
			targetHeight = workHeight - 80;
		}
	}
	if (targetWidth < 760) {
		targetWidth = 760;
	}
	if (targetHeight < 600) {
		targetHeight = 600;
	}
	ShowWindow(hwnd, SW_SHOWNORMAL);
	MoveWindow(hwnd, 0, 0, targetWidth, targetHeight, TRUE);
}

void applyStartupConsoleLayoutSafe() {
	if (isWindowsTerminalHost() || shouldDisableATCIntroByDefault()) {
		maximizeConsoleWindowSafe();
		repaintConsoleViewportSafe();
		return;
	}
	int Window = 3, Dimensions = 2;
	applySettings(Window);
	applySettings(Dimensions);
}

bool shouldUseLegacyConsoleWindowManagement() {
	return !isWindowsTerminalHost();
}

void applyConsoleTitleSafe(const char* title) {
	if (title == nullptr) {
		return;
	}
	SetConsoleTitleA(title);
}

void applyConsoleColorSafe(const char* colorCommand) {
	if (colorCommand == nullptr || strlen(colorCommand) < 8) {
		return;
	}

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!hasConsoleHandle(hOut)) {
		return;
	}

	char background = colorCommand[6];
	char foreground = colorCommand[7];
	int bg = isdigit((unsigned char)background) ? background - '0' : 10 + tolower((unsigned char)background) - 'a';
	int fg = isdigit((unsigned char)foreground) ? foreground - '0' : 10 + tolower((unsigned char)foreground) - 'a';
	if (bg < 0 || bg > 15 || fg < 0 || fg > 15) {
		return;
	}
	WORD attributes = (WORD)((bg << 4) | fg);
	SetConsoleTextAttribute(hOut, attributes);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hOut, &csbi)) {
		DWORD cells = (DWORD)csbi.dwSize.X * (DWORD)csbi.dwSize.Y;
		DWORD written = 0;
		COORD home = { 0, 0 };
		FillConsoleOutputAttribute(hOut, attributes, cells, home, &written);
	}
	repaintConsoleViewportSafe();
}

void openNewATCInstance() {
	char executablePath[4096];
	char wtPath[MAX_PATH];
	char wtParameters[4096];
	char cmdParameters[4096];
	executablePath[0] = '\0';
	wtPath[0] = '\0';
	wtParameters[0] = '\0';
	cmdParameters[0] = '\0';
	snprintf(executablePath, sizeof(executablePath), "%s\\atc.exe", atcPath);

	DWORD wtFound = SearchPathA(NULL, "wt.exe", NULL, MAX_PATH, wtPath, NULL);
	if (wtFound > 0 && wtFound < MAX_PATH) {
		snprintf(wtParameters, sizeof(wtParameters), "new-tab --title \"Advanced Trigonometry Calculator\" --startingDirectory \"%s\" \"%s\"", atcPath, executablePath);
		HINSTANCE result = ShellExecuteA(NULL, "open", wtPath, wtParameters, atcPath, SW_SHOWNORMAL);
		if ((INT_PTR)result > 32) {
			printf("\x0A==> New ATC tab opened. <==\x0A");
			return;
		}
	}

	snprintf(cmdParameters, sizeof(cmdParameters), "/K \"\"%s\"\"", executablePath);
	HINSTANCE result = ShellExecuteA(NULL, "open", "C:\\WINDOWS\\system32\\cmd.exe", cmdParameters, atcPath, SW_SHOWNORMAL);
	if ((INT_PTR)result > 32) {
		printf("\x0A==> New ATC window opened. <==\x0A");
	}
	else {
		printf("\x0AError: Unable to open a new ATC instance.\x0A");
	}
}
void force_legacy_console_mode() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	DWORD outMode = 0, inMode = 0;


	if (GetConsoleMode(hOut, &outMode)) {
		if (isWindowsTerminalHost()) {
			outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		}
		else {
			outMode &= ~ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			outMode &= ~DISABLE_NEWLINE_AUTO_RETURN;
		}
		SetConsoleMode(hOut, outMode);
	}

	if (GetConsoleMode(hIn, &inMode)) {
		inMode &= ~ENABLE_VIRTUAL_TERMINAL_INPUT;
		SetConsoleMode(hIn, inMode);
	}

	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());

	if (isWindowsTerminalHost()) {
		maximizeConsoleWindowSafe();
		repaintConsoleViewportSafe();
		return;
	}
	applyConsoleDimensionsSafe(84, 37);
}


int getReady() {
	int x = 0, y = 0, maxX = 0, maxY = 0, saveX, saveY = 0, minX = -1, minY = -1, columns = 0, rows = 0, saveColumns = -1, saveRows = -1;
	Pressed = 0;
	do {
		fflush(NULL);
		FILE* open = NULL;
		POINT p;
		GetWindowPos(&x, &y, &maxX, &maxY);
		GetCursorPos(&p);
		if (WindowFromPoint(p) == GetConsoleWindow()) {
			if (x != minX || y != minY) {
				setWindow(x, y);
			}
		}
		if (WindowFromPoint(p) == GetConsoleWindow()) {
			if (GetKeyState(VK_RBUTTON) < 0) {
				if (x + 50 < p.x && y + 50 < p.y && p.x < maxX - 50 && p.y < maxY - 50) {
					GetActiveWindow();
					Pressed = 1;
				}
			}
		}
		if (WindowFromPoint(p) == GetConsoleWindow()) {
			if (GetKeyState(VK_LBUTTON) < 0) {
				if (x + 50 < p.x && y + 50 < p.y && p.x < maxX - 50 && p.y < maxY - 50) {
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
				if (x + 50 < p.x && y + 50 < p.y && p.x < maxX - 50 && p.y < maxY - 50 && p.x != saveX && p.y != saveY) {
					GetActiveWindow();
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
		char* toOpen = getDynamicCharArray("", "toOpen");
		sprintf(toOpen, "%s\\sendCommand.txt", atcPath);
		char* readCommand = getDynamicCharArray("", "readCommand");
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
		_delete(readCommand, "readCommand");
		readCommand = nullptr;
		_delete(toOpen, "toOpen");
		toOpen = nullptr;
	} while (Pressed == 0);
	return 0;
}

void setWindow(int x, int y) {
	FILE* open;
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\window.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d\n%d\n%d\n%d\n", x, y, widthATC, heightATC);
	fclose(open);
	xATC = x;
	yATC = y;
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
}

void setDimensions(int cols, int lines) {
	FILE* open = NULL;
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\dimensions.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "MODE con cols=%d lines=%d", cols, lines);
	colsATC = cols;
	linesATC = lines;
	fclose(open);
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
}

void GetWindowPos(int* x, int* y, int* maxX, int* maxY) {
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


void split(char* splitter, char* data) {
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
	PINPUT_RECORD ClearingVar1 = new INPUT_RECORD[256] {};
	RegisterDynamicArray(ClearingVar1, 256);
	DWORD ClearingVar2;
	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), ClearingVar1, 256, &ClearingVar2);
	ZeroMemory(ClearingVar1, sizeof(INPUT_RECORD) * 256);
	UnregisterDynamicArray(ClearingVar1);
	delete[] ClearingVar1; ClearingVar1 = nullptr;
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




void autoAdjustWindow() {
	char* toOpen = getDynamicCharArray("", "toOpen");
	int Window = 3, Dimensions = 2;
	applyConsoleDimensionsSafe(160, 2000);
	int x = 0, y = 0, maxX = 0, maxY = 0;
	HWND b;
	b = GetConsoleWindow();
	ShowWindow(b, SW_SHOWMAXIMIZED);
	GetWindowPos(&x, &y, &maxX, &maxY);
	HWND hwnd = GetConsoleWindow();
	RECT rect;
	getDimensions();
	if (GetWindowRect(hwnd, &rect))
	{
		widthATC = rect.right - rect.left;
		heightATC = rect.bottom - rect.top;
		sprintf(toOpen, "%s\\window.txt", atcPath);
		FILE* open = NULL;
		while (open == NULL) {
			open = fopen(toOpen, "w");
			Sleep(10);
		}
		fprintf(open, "%d\n%d\n%d\n%d\n", x, y, widthATC, heightATC);
		fclose(open);
	}
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = (int)ceil((csbi.srWindow.Right - csbi.srWindow.Left));
	if (columns < 0) {
		columns = (int)ceil((csbi.srWindow.Left + csbi.srWindow.Right));
	}
	rows = 2000;
	sprintf(toOpen, "%s\\dimensions.txt", atcPath);
	char* setting = getDynamicCharArray("", "setting");
	FILE* open = NULL;
	while (open == NULL) {
		open = fopen(toOpen, "w");
		Sleep(10);
	}
	sprintf(setting, "MODE con cols=%d lines=%d", columns, rows);
	if (!applyConsoleCommandDimensions(setting)) {
		system(setting);
	}
	sprintf(dimensionsTxt, "%s", setting);
	fputs(setting, open);
	fclose(open);
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
	_delete(setting, "setting");
	setting = nullptr;
}

bool isContainedInUserFunction(char* variable) {
	FILE* file = NULL;
	char* option = getDynamicCharArray("", "option"); char* directory = getDynamicCharArray("", "directory");
	sprintf(directory, "%s\\User functions\\", atcPath);
	int k = 0, numFiles = 0, i = 0, numFilesSolved = 0;
	DIR* d;
	int retry = 0;
	struct dirent* dir;
	d = opendir(directory);
	char* filename = getDynamicCharArray("", "filename");
	char* txtFiles = getDynamicCharArray("", "txtFiles");
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
							_delete(option, "option"); option = nullptr;
							_delete(directory, "directory"); directory = nullptr;
							_delete(filename, "filename"); filename = nullptr;
							_delete(txtFiles, "txtFiles"); txtFiles = nullptr;
							return true;
						}
					}
				}
			}
		}
	}
	_delete(option, "option"); option = nullptr;
	_delete(directory, "directory"); directory = nullptr;
	_delete(filename, "filename"); filename = nullptr;
	_delete(txtFiles, "txtFiles"); txtFiles = nullptr;
	return false;
}
void convert2Vector(char* arithTrig) {
	if (!checkMatrixIndex && abs((int)strlen(matrixResult)) > 0) {
		matrixMode = 1;
	}
	char* saveArithTrig = getDynamicCharArray("", "saveArithTrig");
	sprintf(saveArithTrig, "%s", arithTrig);
	numVectorCols = 0;
	numVectorLines = 0;
	sprintf(vectorString, "");
	if (isContained(":", arithTrig) && !isContained("*", arithTrig)) {
		vectorType = 1;
		int initialCountSplits = 0;
		char** saveSplitResult = new char* [DIMTWOD];

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
		countSplits = countOccurrences(":", arithTrig);
		int N = countSplits + 1;
		split(":", arithTrig);
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
		char* pointer;
		char* real = getDynamicCharArray("", "real"); char* imag = getDynamicCharArray("", "imag");
		while (i <= countSplits) {
			sprintf(real, "");
			sprintf(imag, "");
			int y = 0;
			while (value[i][y] != ' ' && value[i][y] != '\0') {
				real[y] = value[i][y];
				y++;
			}
			real[y] = '\0';
			y++;
			int gh = 0;
			while (value[i][y] != '\0') {
				imag[gh] = value[i][y];
				y++; gh++;
			}
			imag[gh] = '\0';
			resultR = strtod(real, &pointer);
			resultI = strtod(imag, &pointer);
			vectorR[0][i] = resultR; vectorI[0][i] = resultI;
			if (i < countSplits) {
				convertComplex2Exponential(vectorR[0][i], vectorI[0][i]);
				sprintf(vectorString, "%s%s %s:", vectorString, respR, respI);
			}
			else {
				convertComplex2Exponential(vectorR[0][i], vectorI[0][i]);
				sprintf(vectorString, "%s%s %s", vectorString, respR, respI);
			}
			i++;
		}
		_delete(real, "real"); real = nullptr;
		_delete(imag, "imag"); imag = nullptr;
		numVectorLines = 1;
		numVectorCols = countSplits + 1;

		_Delete(value, DIMTWOD, DIM, "value[i]");


		_Delete(saveSplitResult, DIMTWOD, dime, "saveSplitResult[i]");
	}
	else {
		if (!isContained(":", arithTrig) && isContained("*", arithTrig)) {
			vectorType = 1;
			int initialCountSplits = 0;
			char** saveSplitResult = new char* [DIMTWOD];

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
			countSplits = countOccurrences("*", arithTrig);
			int N = countSplits + 1;
			split("*", arithTrig);
			i = 0;
			char** value;
			value = new char* [DIMTWOD];

			for (int i = 0; i < DIMTWOD; ++i) {
				value[i] = getDynamicCharArray("", "");
			}
			while (i <= countSplits) {
				sprintf(value[i], "%s", splitResult[i]);
				i++;
			}
			i = 0;
			char* pointer;
			char* real = getDynamicCharArray("", "real"); char* imag = getDynamicCharArray("", "imag");
			while (i <= countSplits) {
				sprintf(real, "");
				sprintf(imag, "");
				int y = 0;
				while (value[i][y] != ' ' && value[i][y] != '\0') {
					real[y] = value[i][y];
					y++;
				}
				real[y] = '\0';
				y++;
				int gh = 0;
				while (value[i][y] != '\0') {
					imag[gh] = value[i][y];
					y++; gh++;
				}
				imag[gh] = '\0';
				resultR = strtod(real, &pointer);
				resultI = strtod(imag, &pointer);
				vectorR[i][0] = resultR; vectorI[i][0] = resultI;
				if (i < countSplits) {
					convertComplex2Exponential(vectorR[i][0], vectorI[i][0]);
					sprintf(vectorString, "%s%s %s*", vectorString, respR, respI);
				}
				else {
					convertComplex2Exponential(vectorR[i][0], vectorI[i][0]);
					sprintf(vectorString, "%s%s %s", vectorString, respR, respI);
				}
				i++;
			}
			numVectorCols = 1;
			numVectorLines = countSplits + 1;
			_delete(real, "real"); real = nullptr;
			_delete(imag, "imag"); imag = nullptr;

			_Delete(saveSplitResult, DIMTWOD, dime, "saveSplitResult[i]");

			_Delete(value, DIMTWOD, DIM, "value[i]");
			value = nullptr;
		}
		else {
			if (isContained(":", arithTrig) && isContained("*", arithTrig)) {
				vectorType = 2;
				int initialCountSplits = 0;
				char** saveSplitResult = new char* [DIMTWOD];

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

				countSplits = countOccurrences("*", arithTrig);
				int N = countSplits + 1;
				split("*", arithTrig);
				i = 0;
				char** value, ** lines;
				value = new char* [DIMTWOD];

				for (int i = 0; i < DIMTWOD; ++i) {
					value[i] = getDynamicCharArray("", "value[i]");
				}

				lines = new char* [DIMTWOD];

				for (int i = 0; i < DIMTWOD; ++i) {
					lines[i] = getDynamicCharArray("", "lines[i]");
				}

				while (i <= countSplits) {
					sprintf(lines[i], "%s", splitResult[i]);
					sprintf(splitResult[i], "");
					i++;
				}
				int l = 0;
				int countLines = countSplits;
				char* real = getDynamicCharArray("", "real"); char* imag = getDynamicCharArray("", "imag");
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
					countSplits = countOccurrences(":", lines[l]);
					int N = countSplits + 1;
					split(":", lines[l]);
					i = 0;

					while (i <= countSplits) {
						sprintf(value[i], "%s", splitResult[i]);
						i++;
					}
					i = 0;
					char* pointer;
					while (i <= countSplits) {

						sprintf(real, "");
						sprintf(imag, "");
						int y = 0;
						while (value[i][y] != ' ') {
							real[y] = value[i][y];
							y++;
						}
						real[y] = '\0';
						y++;
						int gh = 0;
						while (value[i][y] != '\0') {
							imag[gh] = value[i][y];
							y++; gh++;
						}
						imag[gh] = '\0';
						resultR = strtod(real, &pointer);
						resultI = strtod(imag, &pointer);
						vectorR[l][i] = resultR; vectorI[l][i] = resultI;
						if (i < countSplits) {
							convertComplex2Exponential(vectorR[l][i], vectorI[l][i]);
							sprintf(vectorString, "%s%s %s:", vectorString, respR, respI);
						}
						else {
							convertComplex2Exponential(vectorR[l][i], vectorI[l][i]);
							sprintf(vectorString, "%s%s %s", vectorString, respR, respI);
						}
						i++;
					}
					if (numVectorCols < i) {
						numVectorCols = i;
					}

					if (l < countLines) {
						sprintf(vectorString, "%s*", vectorString);
					}
					l++;
				}
				_delete(real, "real"); real = nullptr;
				_delete(imag, "imag"); imag = nullptr;
				numVectorLines = l;

				_Delete(saveSplitResult, DIMTWOD, dime, "saveSplitResult[i]");

				_Delete(lines, DIMTWOD, dime, "lines[i]"); lines = nullptr;
				_Delete(value, DIMTWOD, dime, "value[i]");
			}
		}
	}
	sprintf(arithTrig, "%s", saveArithTrig);
	_delete(saveArithTrig, "saveArithTrig"); saveArithTrig = nullptr;
}

template <typename T>
char* convertVector2String(T** vectorR, T** vectorI, int numLines, int numCols) {
	char* string = getDynamicCharArray("", "string");
	string[0] = '\0';
	int i = 0, j = 0;
	for (i = 0; i < numLines; i++) {
		for (j = 0; j < numCols; j++) {
			if (j < numCols - 1) {
				convertComplex2Exponential(vectorR[i][j], vectorI[i][j]);
				sprintf(string, "%s%s %s:", string, respR, respI);
			}
			else {
				convertComplex2Exponential(vectorR[i][j], vectorI[i][j]);
				sprintf(string, "%s%s %s", string, respR, respI);
			}
		}
		if (i < numLines - 1) {
			sprintf(string, "%s*", string);
		}
	}
	sprintf(returnCharArray, "%s", string);
	_delete(string, "string"); string = nullptr;
	return returnCharArray;
}



int colsNumber(char* values) {
	if (higherPrecision == 1) initialProcessor<mp_float>(values, (mp_float)0); else initialProcessor<double>(values, 0.0);
	if (abs((int)strlen(matrixResult)) > 0) {
		sprintf(values, "%s", matrixResult);
	}
	matrixMode = 0;
	int numberCols = 0;
	if (isContained(":", values) && !isContained("*", values)) {
		numberCols = countOccurrences(":", values) + 1;
		return numberCols;
	}
	else {
		if (!isContained(":", values) && isContained("*", values)) {
			numberCols = 1;
			return numberCols;
		}
		else {
			if (isContained(":", values) && isContained("*", values)) {
				char* firstLine = getDynamicCharArray("", "firstLine");
				int i = 0;
				while (values[i] != '*') {
					firstLine[i] = values[i];
					i++;
				}
				firstLine[i] = '\0';
				numberCols = countOccurrences(":", firstLine) + 1;
				_delete(firstLine, "firstLine");
				firstLine = nullptr;
				return numberCols;
			}
			else {
				return 0;
			}

		}
	}

}

int linesNumber(char* values) {
	if (higherPrecision == 1) initialProcessor<mp_float>(values, (mp_float)0); else initialProcessor<double>(values, 0.0);
	if (abs((int)strlen(matrixResult)) > 0) {
		sprintf(values, "%s", matrixResult);
	}
	matrixMode = 0;
	int numberLines = 0;
	if (isContained(":", values) && !isContained("*", values)) {
		numberLines = 1;
		return numberLines;
	}
	else {
		if (!isContained(":", values) && isContained("*", values)) {
			numberLines = countOccurrences("*", values) + 1;
			return numberLines;
		}
		else {
			if (isContained(":", values) && isContained("*", values)) {
				numberLines = countOccurrences("*", values) + 1;
				return numberLines;
			}
			else {
				return 0;
			}

		}
	}
}

template <typename T>
void getCols(char* data) {
	int numberLines = 0, numberColumns = 0, startColIndex = 0, endColIndex = 0;
	if (!isContained("\\", data)) {
		check4Vector = 1;
		processVariable<double>(data);
		if (abs((int)strlen(matrixValue)) > 0) {
			convert2Vector(matrixValue);
			sprintf(matrixValue, "%s", convertVector2String(vectorR, vectorI, numVectorLines, numVectorCols));
		}
		return;
	}
	if (isContained("\\", data)) {
		int numberBars = countOccurrences("\\", data);
		if (numberBars == 2) {
			char* varName = getDynamicCharArray("", "varName");
			int i = 0;
			while (data[i] != '\\') {
				varName[i] = data[i];
				i++;
			}
			varName[i] = '\0';
			char* value = getDynamicCharArray("", "value");
			sprintf(value, "");
			i++;
			int j = 0;
			while (data[i] != '\\') {
				value[j] = data[i];
				i++; j++;
			}
			value[j] = '\0';
			startColIndex = (int)precisionValueTo<double>(solveMath<T>(value));
			i++;
			j = 0;
			while (i < abs((int)strlen(data))) {
				value[j] = data[i];
				i++; j++;
			}
			value[j] = '\0';
			endColIndex = (int)precisionValueTo<double>(solveMath<T>(value));
			check4Vector = 1;
			initialProcessor<T>(varName, (T)0);
			sprintf(matrixValue, "%s", matrixResult);
			convert2Vector(matrixValue);
			PrecisionValue** vector_R = new PrecisionValue* [DIMTWOD];

			for (int i = 0; i < DIMTWOD; ++i) {
				vector_R[i] = getDynamicDoubleArray();
			}
			PrecisionValue** vector_I = new PrecisionValue* [DIMTWOD];

			for (int i = 0; i < DIMTWOD; ++i) {
				vector_I[i] = getDynamicDoubleArray();
			}
			int n = 0;
			int m = 0;
			for (n = 0; n < numVectorLines; n++) {
				for (m = 0; m < numVectorCols; m++) {
					vector_R[n][m] = vectorR[n][m];
					vector_I[n][m] = vectorI[n][m];
				}
			}
			numberColumns = numVectorCols;
			numberLines = numVectorLines;
			if (startColIndex <= endColIndex && endColIndex < numberColumns) {
				int i = 0, j = 0;
				numVectorLines = numberLines; numVectorCols = 0;
				for (i = 0; i < numberLines; i++) {
					numVectorCols = 0;
					for (j = startColIndex; j <= endColIndex; j++) {
						vectorR[i][j - startColIndex] = vector_R[i][j];
						vectorI[i][j - startColIndex] = vector_I[i][j];
						numVectorCols++;
					}

				}
				sprintf(matrixValue, "%s", convertVector2String(vectorR, vectorI, numVectorLines, numVectorCols));
			}

			_Delete(vector_R, DIMTWOD, dime, "vector_R, DIMTWOD, dime");

			_Delete(vector_I, DIMTWOD, dime, "vector_I, DIMTWOD, dime");
			_delete(value, "value"); value = nullptr;
			_delete(varName, "varName"); varName = nullptr;
		}
	}
}

template <typename T>

void getLines(char* data) {
	int numberLines = 0, numberColumns = 0, startLineIndex = 0, endLineIndex = 0;
	char* saveRestExpr = getDynamicCharArray("", "saveRestExpr");
	if (isContained(")\\", data)) {
		int i = 0;
		while (i <= strStart) {
			saveRestExpr[i] = data[i];
			i++;
		}
		saveRestExpr[i] = '\0';
		initialProcessor<T>(saveRestExpr, (T)0);
		sprintf(matrixValue, "%s", matrixResult);
	}
	else {
		if (!isContained("\\", data)) {
			check4Vector = 1;
			processVariable<double>(data);
			if (abs((int)strlen(matrixValue)) > 0) {
				convert2Vector(matrixValue);
				sprintf(matrixValue, "%s", convertVector2String(vectorR, vectorI, numVectorLines, numVectorCols));
			}
		}
		else if (isContained("\\", data)) {
			int numberBars = countOccurrences("\\", data);
			if (numberBars == 2) {
				char* varName = getDynamicCharArray("", "varName");
				int i = 0;
				while (data[i] != '\\') {
					varName[i] = data[i];
					i++;
				}
				varName[i] = '\0';
				char* value = getDynamicCharArray("", "value");
				sprintf(value, "");
				i++;
				int j = 0;
				while (data[i] != '\\') {
					value[j] = data[i];
					i++; j++;
				}
				value[j] = '\0';
				startLineIndex = (int)precisionValueTo<double>(solveMath<T>(value));
				i++;
				j = 0;
				while (i < abs((int)strlen(data))) {
					value[j] = data[i];
					i++; j++;
				}
				value[j] = '\0';
				endLineIndex = (int)precisionValueTo<double>(solveMath<T>(value));
				check4Vector = 1;
				initialProcessor<T>(varName, (T)0);
				sprintf(matrixValue, "%s", matrixResult);
				convert2Vector(matrixValue);
				PrecisionValue** vector_R = new PrecisionValue* [DIMTWOD];

				for (int i = 0; i < DIMTWOD; ++i) {
					vector_R[i] = getDynamicDoubleArray();
				}
				PrecisionValue** vector_I = new PrecisionValue* [DIMTWOD];

				for (int i = 0; i < DIMTWOD; ++i) {
					vector_I[i] = getDynamicDoubleArray();
				}
				int n = 0;
				int m = 0;
				for (n = 0; n < numVectorLines; n++) {
					for (m = 0; m < numVectorCols; m++) {
						vector_R[n][m] = vectorR[n][m];
						vector_I[n][m] = vectorI[n][m];
					}
				}
				numberColumns = numVectorCols;
				numberLines = numVectorLines;
				if (startLineIndex <= endLineIndex && endLineIndex < numberLines) {
					int i = 0, j = 0;
					numVectorLines = 0; numVectorCols = numberColumns;
					for (i = startLineIndex; i <= endLineIndex; i++) {
						for (j = 0; j < numberColumns; j++) {
							vectorR[i - startLineIndex][j] = vector_R[i][j];
							vectorI[i - startLineIndex][j] = vector_I[i][j];
						}
						numVectorLines++;
					}
					sprintf(matrixValue, "%s", convertVector2String(vectorR, vectorI, numVectorLines, numVectorCols));
				}
				_Delete(vector_R, DIMTWOD, dime, "vector_R, DIMTWOD, dime");

				_Delete(vector_I, DIMTWOD, dime, "vector_I, DIMTWOD, dime");
				_delete(value, "value");
				_delete(varName, "varName"); varName = nullptr;
			}

		}
	}
	_delete(saveRestExpr, "saveRestExpr");	saveRestExpr = nullptr;
}
template<typename T>
char* convert2Exponential(T value) {
	sprintf(resp, "%G", precisionDisplayDouble(value));
	if ((higherPrecision == 1 && !notUseHigherPrecison && solving) || useForVariables && solving) {
		sprintf(resp, "%.15E", precisionDisplayDouble(value));
		if (isContained("E", resp)) {
			int i = strStart + 1;
			char* exp = getDynamicCharArray("", "exp");
			if (resp[i] == '+') {
				i++;
			}
			int p = 0;
			while (i < abs((int)strlen(resp))) {
				exp[p] = resp[i];
				p++; i++;
			}
			exp[p] = '\0';

			int exponent = atoi(exp);
			char* floatChar = getDynamicCharArray("", "floatChar");
			p = 0;
			while (resp[p] != 'E') {
				floatChar[p] = resp[p];
				p++;
			}
			floatChar[p] = '\0';

			if (floatChar[abs((int)strlen(floatChar)) - 1] == '0') {
				int h = abs((int)strlen(floatChar)) - 1;
				while (floatChar[h] == '0') {
					h--;
				}
				if (floatChar[h] == '.') {
					floatChar[h] = '\0';
				}
				else {
					floatChar[h + 1] = '\0';
				}
			}
			if (exponent != 0) {
				sprintf(resp, "%sE%d", floatChar, exponent);
			}
			else {
				sprintf(resp, "%s", floatChar);
			}

			replaceTimes = 0;
			_delete(exp, "exp"); exp = nullptr;
			_delete(floatChar, "floatChar"); floatChar = nullptr;

		}
	}
	sprintf(expressionF, "");
	return resp;
}



template<typename T>
void roundSolution() {
	if ((int)log10(abs(precisionValueTo<double>(resultR))) == -16 || (int)log10(abs(precisionValueTo<double>(resultR))) == -15) {
		resultR = 0;
	}
	if ((int)log10(abs(precisionValueTo<double>(resultI))) == -16 || (int)log10(abs(precisionValueTo<double>(resultI))) == -15) {
		resultI = 0;
	}
}
template<typename T>
const char* createMatrix(char* matrixName, int linsNumber, int colsNumber, char* mathExpression) {
	char* matrix = getDynamicCharArray("", "matrix");
	sprintf(matrix, "%s", matrixName);

	manageExpression<T>(mathExpression, (T)0, (T)0, 0);
	sprintf(mathExpression, "%s", expressionF);
	char* result = getDynamicCharArray("", "result");
	if (linsNumber > 0 && colsNumber > 0 && !(linsNumber == 1 && colsNumber == 1)) {
		creatingMatrix = 1;
		sprintf(result, "");
		for (int i = 0; i < linsNumber; i++) {
			for (int j = 0; j < colsNumber; j++) {
				calcNow<T>(mathExpression, (T)0, (T)0);

				vectorR[i][j] = resultR;
				vectorI[i][j] = resultI;
				if (j < colsNumber - 1) {
					sprintf(result, "%s%G+%Gi\\", result, precisionValueTo<double>(resultR), precisionValueTo<double>(resultI));
				}
				else {
					sprintf(result, "%s%G+%Gi", result, precisionValueTo<double>(resultR), precisionValueTo<double>(resultI));
				}
			}
			if (i < linsNumber - 1) {
				sprintf(result, "%s;", result);
			}
		}

		replaceTimes = 0;
		if (isContained("-", result)) {
			replace("-", "_", result);
			sprintf(result, "%s", expressionF);
		}
		char* finalExpr = getDynamicCharArray("", "finalExpr");
		sprintf(finalExpr, "%s=%s", matrix, result);

		creatingMatrix = 0;
		sprintf(context, "main");
		calcNow<T>(finalExpr, (T)0, (T)0);

		calcNow<T>(matrixName, (T)0, (T)0);

		_delete(result, "result"); result = nullptr;
		static std::string str = finalExpr;
		const char* _str = str.c_str();

		_delete(matrix, "matrix"); matrix = nullptr;
		_delete(finalExpr, "finalExpr"); finalExpr = nullptr;

		return _str;
	}
	else {
		_delete(result, "result"); result = nullptr;
		_delete(matrix, "matrix"); matrix = nullptr;
		return "";
	}
}


template char* convert2Exponential<double>(double);
template char* convert2Exponential<mp_float>(mp_float);
template char* convert2Exponential<PrecisionValue>(PrecisionValue);
template char* convertVector2String<PrecisionValue>(PrecisionValue**, PrecisionValue**, int, int);

void getCols(char* data) {
    getCols<PrecisionValue>(data);
}

void getLines(char* data) {
    getLines<PrecisionValue>(data);
}

template <>
PrecisionValue calcNow<PrecisionValue>(char* toCalc, PrecisionValue result1, PrecisionValue result2) {
	if (higherPrecision == 1) {
		return calcNow<mp_float>(toCalc, precisionValueTo<mp_float>(result1), precisionValueTo<mp_float>(result2));
	}
	return calcNow<double>(toCalc, precisionValueTo<double>(result1), precisionValueTo<double>(result2));
}

template void higherPrecisionController<double>(int);
template void higherPrecisionController<mp_float>(int);
template void verboseResolutionController<double>(int);
template void verboseResolutionController<mp_float>(int);
template void numSystemsController<double>();
template void numSystemsController<mp_float>();
template void manageExpression<double>(char*, double, double, int);
template void manageExpression<mp_float>(char*, mp_float, mp_float, int);
template double processVariable<double>(char*);
template mp_float processVariable<mp_float>(char*);
template void complexNumber<double>(double, double);
template void complexNumber<mp_float>(mp_float, mp_float);
template void prefixDeterminator<double>(double, char*);
template void prefixDeterminator<mp_float>(mp_float, char*);
template double prefToNumber<double>(char);
template mp_float prefToNumber<mp_float>(char);
template double numericalSystems<double>(char*);
template mp_float numericalSystems<mp_float>(char*);
template void roundSolution<double>();
template double calcNow<double>(char*, double, double);
template mp_float calcNow<mp_float>(char*, mp_float, mp_float);
template PrecisionValue calcNow<PrecisionValue>(char*, PrecisionValue, PrecisionValue);



template const char* createMatrix<double>(char*, int, int, char*);

void simplifyExpression(char* data) { manageExpression<double>(data, 0.0, 0.0, 1); }
void roundSolution() { roundSolution<double>(); }
void currentSettings() { currentSettings<double>(); }
void verboseResolutionController() { verboseResolutionController<double>(-1); }
void siPrefixController() { siPrefixController<double>(); }
void actualTimeController() { actualTimeController<double>(); }
