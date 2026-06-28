

#include "stdafx.h"
#include "atc_functions.h"



bool haveCreatedDynamicMatrix = false, mainRoutine = false, toIntegrateOnCalculus = false;
PrecisionValue ansIV = 0, ansRV = 0, resultFI = 0, resultR = 0, resultI = 0, intVal = 0;
PrecisionValue lastElement = 0, lastElementI = 0, lastDividerR = 1, lastDividerI = 0, natureValue = 1;
PrecisionValue* ans = nullptr, * ansI = nullptr;
char** ansMatrices, * lastCommand = getDynamicCharArray("", "lastCommand"), * atcPath = getDynamicCharArray("", "atcPath"), * customFolderPath = getDynamicCharArray("", "customFolderPath"), * saveATCPath = getDynamicCharArray("", "saveATCPath"), * varRename = getDynamicCharArray("", "varRename"), * revariable = getDynamicCharArray(" ", "matrixValue"), * pathNAme = getDynamicCharArray("", "pathNAme"), * variableSTring = getDynamicCharArray("", "variableSTring"), * expressionF2 = getDynamicCharArray("", "expressionF2"), * expressionF = getDynamicCharArrayLong(""), * usRFunctions = getDynamicCharArray(",", "usRFunctions"), * usRFuncTrans = getDynamicCharArray(",", "usRFuncTrans");
char* context = getDynamicCharArray("", "context"), * forsprintf = nullptr;
int higherPrecision = 0, countDeleteorGetDynamic = 0, replaceTimes = 0, processingOK = 1, executedSolver = 0, isFromMain = 0, solutioned = 0, verify = 0, arG = 1, Mode = 0, isFromSolveNow = 0, valid = 0, validVar = 0, count = 2, synTest = 0, valRenamedVar = 0, continu = 1, cleanhistory = 0, rf = 0, verified = 0, nPlaces = 0, verbose = 0, feedbackValidation = 0;
clock_t start_processing, end_processing;
char* savePathF = getDynamicCharArray("", "savePathF"), * validChars = getDynamicCharArray(" qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM123456789.0/*-+\\!#(,)[]{}^_;=", "validChars");
int runningUserFunction = 0, creatingMatrix = 0, toSendCommand = 0, indexI = -1, indexJ = -1, fromCalcNow = 0;
PrecisionValue **saveResultR = nullptr, **saveResultI = nullptr;
DynamicAllocation dynamicAllocation;
bool manageDynamicAllocations = false, processingTxtFile = false;
float memFactor = 1.0f;
extern char* appVersion;
extern char* polyNo;
extern char* stringHelper;


int DIM = 3100;
int dime = 1000;
int SHORTDIM = 3100;
int LONGDIM = 3100;
int DIMTWOD = 150;
int DIMDOUBLE = 1000;

static void cleanupSessionDynamicAllocations() {
	if (saveResultR != nullptr) _Delete(saveResultR, DIMTWOD, DIMDOUBLE, "saveResultR");
	if (saveResultI != nullptr) _Delete(saveResultI, DIMTWOD, DIMDOUBLE, "saveResultI");
	if (vectorR != nullptr) _Delete(vectorR, DIMTWOD, DIMDOUBLE, "vectorR");
	if (vectorI != nullptr) _Delete(vectorI, DIMTWOD, DIMDOUBLE, "vectorI");
	if (ans != nullptr) _delete(ans, "ans");
	if (ansI != nullptr) _delete(ansI, "ansI");
	if (ansMatrices != nullptr) _Delete(ansMatrices, DIMTWOD, DIM, "ansMatrices");
	if (splitResult != nullptr) _Delete(splitResult, DIMTWOD, DIM, "splitResult");
}

static void cleanupStaticDynamicAllocations() {
	cleanupSessionDynamicAllocations();
	if (parentPol != nullptr) _delete(parentPol, "parentPol");
	if (appVersion != nullptr) _delete(appVersion, "appVersion");
	if (calendarStr != nullptr) _deleteLong(calendarStr, "calendarStr");
	if (charMaster != nullptr) _deleteShort(charMaster, "charMaster");
	if (roots != nullptr) _deleteShort(roots, "roots");
	if (answers != nullptr) _deleteShort(answers, "answers");
	if (polyNo != nullptr) _deleteShort(polyNo, "polyNo");
	if (stringHelper != nullptr) _deleteShort(stringHelper, "stringHelper");
	if (saveExpressionF != nullptr) _delete(saveExpressionF, "saveExpressionF");
	if (lastCommand != nullptr) _delete(lastCommand, "lastCommand");
	if (atcPath != nullptr) _delete(atcPath, "atcPath");
	if (customFolderPath != nullptr) _delete(customFolderPath, "customFolderPath");
	if (saveATCPath != nullptr) _delete(saveATCPath, "saveATCPath");
	if (varRename != nullptr) _delete(varRename, "varRename");
	if (revariable != nullptr) _delete(revariable, "revariable");
	if (pathNAme != nullptr) _delete(pathNAme, "pathNAme");
	if (variableSTring != nullptr) _delete(variableSTring, "variableSTring");
	if (expressionF2 != nullptr) _delete(expressionF2, "expressionF2");
	if (usRFunctions != nullptr) _delete(usRFunctions, "usRFunctions");
	if (usRFuncTrans != nullptr) _delete(usRFuncTrans, "usRFuncTrans");
	if (context != nullptr) _delete(context, "context");
	if (forsprintf != nullptr) _delete(forsprintf, "forsprintf");
	if (savePathF != nullptr) _delete(savePathF, "savePathF");
	if (validChars != nullptr) _delete(validChars, "validChars");
}

int loadHigherPrecisionState() {
	getATCPath();
	char* value = getDynamicCharArray("0", "value");
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\higherPrecision.txt", atcPath);
	FILE* open = fopen(toOpen, "r");
	if (open != NULL) {
		fgets(value, 10, open);
		fclose(open);
	}
	else {
		open = fopen(toOpen, "w");
		if (open != NULL) {
			fprintf(open, "0");
			fclose(open);
		}
	}
	int savedState = atoi(value);
	higherPrecision = savedState == 1 ? 1 : 0;
	if (savedState != higherPrecision) {
		open = fopen(toOpen, "w");
		if (open != NULL) {
			fprintf(open, "%d", higherPrecision);
			fclose(open);
		}
	}
	_delete(value, "value");
	value = nullptr;
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
	return higherPrecision;
}


void main(int argc, char* argv[]) {

		try {

			char* value = getDynamicCharArray("", "value");
			char* toOpen = getDynamicCharArray("", "toOpen");
			FILE* open = NULL;
			int precisionState = loadHigherPrecisionState();
			sprintf(value, "%d", precisionState);
			sprintf(toOpen, "%s\\higherPrecision.txt", atcPath);
			if (precisionState == 1) {
				mainType<mp_float>(value, toOpen, open, argc, argv);
			}
			else {
				mainType<double>(value, toOpen, open, argc, argv);
			}



		exit(0);
	}
	catch (const std::exception& e) {
		// Captura qualquer coisa que herde de std::exception (runtime_error, logic_error, etc.)
		std::cerr << "Exceção C++ capturada (std::exception): " << e.what() << std::endl;
	}
	catch (...) {
		// Captura "catch-all": deteta qualquer outra coisa que não herde de std::exception 
		// (ex: 'throw 10;' ou 'throw "erro";')
		std::cerr << "Exceção C++ desconhecida ou não standard capturada." << std::endl;
	}

}

template<typename T>
void mainType(char* value, char* toOpen, FILE* open,int argc, char* argv[]) {
	ansIV = T(0);
	ansRV = T(0);
	resultFI = T(0);
	resultR = T(0);
	resultI = T(0);
	intVal = T(0);
	lastDividerR = T(1);
	lastDividerI = T(0);
	natureValue = T(1);
	lastElement = T(0);
	lastElementI = T(0);
	saveResultR = getDynamic2DDoubleArray();
	saveResultI = getDynamic2DDoubleArray();
	ans = getDynamicDoubleArray();
	ansI = getDynamicDoubleArray();
	vectorR = getDynamic2DDoubleArray();
	vectorI = getDynamic2DDoubleArray();
	applyMemFactor();
	force_legacy_console_mode();
	if (forsprintf == nullptr) {
		forsprintf = getDynamicCharArray("", "forsprintf");
	}
	forsprintf[0] = '\0';
	ansMatrices = new char* [DIMTWOD];

	for (int i = 0; i < DIMTWOD; i++) {
		ansMatrices[i] = getDynamicCharArray("", "ansMatrices[i]");
	}
	countDeleteorGetDynamic = 0;

	int Colors = 1, tD = 0, i = 0;

	char* path = getDynamicCharArray("", "path");
	char* trigData = getDynamicCharArray("", "trigData");

	T result1 = 0, result2 = 0;
	splitResult = new char* [DIMTWOD];
	for (int i = 0; i < DIMTWOD; ++i) {
		splitResult[i] = getDynamicCharArray("", "splitResult[i]");
	}
	char* currentProcess = getDynamicCharArray("", "currentProcess");
	char* commandF = getDynamicCharArray("", "commandF");
	char* vari = getDynamicCharArray("", "vari");

	char* state = getDynamicCharArray("", "state");
	char* savePreviousAns = getDynamicCharArray("", "savePreviousAns");
	char* boolVar = getDynamicCharArray("true", "boolVar");
	char* yea = getDynamicCharArray("", "yea");
	char* da = getDynamicCharArray("", "da");
	char* Path = getDynamicCharArray("", "Path");
	char* Min = getDynamicCharArray("", "Min");
	char* hou = getDynamicCharArray("", "hou");
	char* sec = getDynamicCharArray("", "sec");
	char* toTitle = getDynamicCharArray("", "toTitle");

	getATCPath();
	if (argc < 2) {
		HANDLE ProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		bool foundATClauncher = false;
		PROCESSENTRY32W pe = { 0 };
		pe.dwSize = sizeof(pe);

		if (Process32FirstW(ProcSnap, &pe)) {
			do {
				if (!wcscmp(pe.szExeFile, L"atc_launcher.exe")) {
					foundATClauncher = true;
					break;
				}
			} while (Process32NextW(ProcSnap, &pe));
		}
		if (!foundATClauncher) {

			sprintf(commandF, "%s\\atc_launcher.exe", atcPath);
			using namespace std;
			std::string s = string(commandF);
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			ShellExecute(NULL, _T("open"), sw, NULL, NULL, SW_SHOW);

		}
		on_start();
		applySettings(Colors);
		sprintf(forsprintf, "Advanced Trigonometry Calculator v2.1.7 (Mem Factor: %.3f)", memFactor);
		applyConsoleTitleSafe(forsprintf);

		sprintf(commandF, "%s\\aboutDisabled.txt", atcPath);
		FILE* ab = NULL;
		ab = fopen(commandF, "r");
		if (ab != NULL) {
			fclose(ab);
		}
		if (ab == NULL && !shouldDisableATCIntroByDefault()) {
			continu = about();
		}
		else {
			continu = 1;
			applyStartupConsoleLayoutSafe();
		}

	}
	if (continu == 1) {
		sprintf(forsprintf, "Advanced Trigonometry Calculator v2.1.7 (Mem Factor: %.3f)        ==) ATC is ready to process data. (==", memFactor);
		applyConsoleTitleSafe(forsprintf);
		sprintf(forsprintf, "%s\\temp.txt", atcPath);
		sprintf(toOpen, "%s", forsprintf);

		if (open != NULL) {
			sprintf(vari, "");
			for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
			vari[i] = '\0';
			fclose(open);
			saveVariablesTextFile = getRenewDynamicCharArray(vari, &saveVariablesTextFile);

		}
		else {
			if (open == NULL) {
				open = fopen(toOpen, "w");
			}
			if (open != NULL) {
				fclose(open);
			}
		}
		sprintf(toOpen, "%s\\variables.txt", atcPath);
		open = fopen(toOpen, "r");
		if (open != NULL) {
			printf(vari, "");
			for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
			vari[i] = '\0';
			fclose(open);
			sprintf(saveVariablesTextFile, "%s", vari);

		}
		else {
			if (open == NULL) {
				open = fopen(toOpen, "w");
			}
			if (open != NULL) {
				fclose(open);
			}
		}
		sprintf(toOpen, "%s\\verboseResolution.txt", atcPath);
		open = fopen(toOpen, "r");
		if (open != NULL) {
			fgets(verboseRes, 10, open);
			verbose = 0;
			fclose(open);
		}
		else {
			if (open == NULL) {
				open = fopen(toOpen, "w");
			}
			if (open != NULL) {
				fclose(open);
			}
		}
		sprintf(toOpen, "%s\\numSystems.txt", atcPath);
		open = fopen(toOpen, "r");
		if (open != NULL) {
			fgets(numSys, 10, open);
			fclose(open);
		}
		sprintf(toOpen, "%s\\higherPrecision.txt", atcPath);
		open = fopen(toOpen, "r");
		if (open != NULL) {
			sprintf(value, "");
			fgets(value, 10, open);
			higherPrecision = (int)convertToNumber<T>(value);
			fclose(open);

		}
		sprintf(toOpen, "%s\\siPrefixes.txt", atcPath);
		open = fopen(toOpen, "r");
		if (open != NULL) {
			fgets(siPref, 10, open);
			fclose(open);
		}
		sprintf(toOpen, "%s\\actualTime.txt", atcPath);
		open = fopen(toOpen, "r");
		if (open != NULL) {
			fgets(actualTime, 10, open);
			fclose(open);
		}
		sprintf(toOpen, "%s\\renamedVar.txt", atcPath);
		open = fopen(toOpen, "r");
		if (open != NULL) {
			for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
			vari[i] = '\0';
			fclose(open);
			sprintf(saveRenamedVariablesTextFile, "%s", vari);

		}
		else {
			if (open == NULL) {
				open = fopen(toOpen, "w");
			}
			if (open != NULL) {
				fclose(open);
			}
		}

		mainRoutine = true;
		do {
			if (manageDynamicAllocations) {
				CheckForNotDeleted();
			}
			FILE* fout = NULL;
			if (expressionF != nullptr) {
				_deleteLong(expressionF, "expressionF");
			}
			expressionF = getDynamicCharArray("", "expressionF");
			sprintf(trigData, "");
			int savePreviousAnsType = previousAnsType;
			sprintf(savePreviousAns, "%s", saveMatrixAns);
			isFromMain = 1;

			resultR = 1; resultI = 0;
			int hk = variableValidator<T>(boolVar);
			if (hk == 1) {

				processVariable<T>(revariable);
				sprintf(boolVar, "%s", revariable);
				resultR = 1; resultI = 0;
				variableController(boolVar);
			}
			if (hk == 2) {
				sprintf(boolVar, "%s", revariable);
				resultR = 1; resultI = 0;
				variableController(boolVar);
			}
			sprintf(boolVar, "false");
			resultR = 0; resultI = 0;
			hk = variableValidator<T>(boolVar);
			if (hk == 1) {
				processVariable<T>(revariable);
				sprintf(boolVar, "%s", revariable);
				resultR = 0; resultI = 0;
				variableController(boolVar);
			}
			if (hk == 2) {
				sprintf(boolVar, "%s", revariable);
				resultR = 0; resultI = 0;
				variableController(boolVar);
			}

			sprintf(saveMatrixAns, "%s", savePreviousAns);
			sprintf(context, "main");
			sprintf(savePathF, "");
			sprintf(forsprintf, "%s", saveATCPath);
			sprintf(atcPath, "%s", forsprintf);
			sprintf(renamedVariable, "");
			resultR = 0; resultI = 0;
			feedbackValidation = 0;
			usRFunctions[0] = ','; usRFuncTrans[0] = ',';
			usRFunctions[1] = '\0'; usRFuncTrans[1] = '\0';
			fflush(NULL);
			tD = 0;
			toSolve<T>(rf);
			resultR = 0; resultI = 0;
			if (argc < 2) {

				Pressed = 0;
				if (executedSolver == 1) {
					executedSolver = 0;
					cls();
				}
				readConsoleInputWithTabCompletion(trigData, DIM);
				start_processing = clock();
				sprintf(forsprintf, "Advanced Trigonometry Calculator v2.1.7 (Mem Factor: %.3f)       ==) Processing... (==", memFactor);
				applyConsoleTitleSafe(forsprintf);
			}
			else {
				arG = 1;
				sprintf(trigData, "");
				while (arG < argc) {
					sprintf(trigData, "%s%s", trigData, argv[arG]);
					arG++;
				}
				addATCPath();
			}
			sprintf(path, "%s\\history.txt", atcPath);
			if (fout != NULL) {
				fclose(fout);
				fout = NULL;
			}
			fout = NULL;

			while (fout == NULL) {
				fout = fopen(path, "a+");

			}
			for (tD = 0; tD < abs((int)strlen(trigData)); tD++) {
				previousAnsType = savePreviousAnsType;
				sprintf(forsprintf, "%s", saveATCPath);
				sprintf(atcPath, "%s", forsprintf);
				sprintf(expressionF, "");
				replaceTimes = 0;
				runningScript = false;
				fflush(NULL);
				useForVariables = false;
				matrixMode = 0;
				sprintf(varRename, "");
				haveCreatedDynamicMatrix = false;
				sprintf(revariable, "");
				validVar = 1; 	processingOK = 1;
				sprintf(varRename, "");
				sprintf(matrixValue, "");
				sprintf(roots, "");

				indexI = -1; indexJ = -1;
				char* fTrig = getDynamicCharArray("", "fTrig"); char* arithTrig = getDynamicCharArray("", "arithTrig");


				i = 0;
				int fl = 1, fr = 0;
				while (tD < abs((int)strlen(trigData)) && trigData[tD] != ',' && tD < abs((int)strlen(trigData))) {

					if (trigData[tD - 6] == 'p' && trigData[tD - 5] == 'r' && trigData[tD - 4] == 'i' && trigData[tD - 3] == 'n' && trigData[tD - 2] == 't' && trigData[tD - 1] == '(') {
						arithTrig[i] = trigData[tD];
						i++; tD++;
						while (fl > fr && tD < abs((int)strlen(trigData))) {
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
				bool useMaxPrecisionForCommand = false;
				if (isContained("maxprec", arithTrig) && !isContained("maxprecision", arithTrig)) {
					replaceTimes = 1;
					useForVariables = true;
					useMaxPrecisionForCommand = true;
					replace("maxprec", "maxprecision", arithTrig);
					sprintf(arithTrig, "%s", expressionF);
					sprintf(expressionF, "");
				}

				if (isContained("maxprecision", arithTrig)) {
					replaceTimes = 1;
					useForVariables = true;
					useMaxPrecisionForCommand = true;
					replace("maxprecision", "", arithTrig);
					sprintf(arithTrig, "%s", expressionF);
					sprintf(expressionF, "");
				}

				if (variableControllersUsed || abs((int)strlen(saveVariablesTextFile)) == 0 || abs((int)strlen(saveRenamedVariablesTextFile)) == 0 || runningUserFunction) {
					sprintf(toOpen, "%s\\variables.txt", atcPath);
					if (open != NULL) {
						fclose(open);
					}
					open = fopen(toOpen, "w");
					if (open != NULL) {
						fprintf(open, "%s", saveVariablesTextFile);
						fclose(open);
					}
					sprintf(toOpen, "%s\\renamedVar.txt", atcPath);
					open = fopen(toOpen, "w");
					if (open != NULL) {
						fprintf(open, "%s", saveRenamedVariablesTextFile);
						fclose(open);
					}
					variableControllersUsed = false;
				}
				if (isContained("open txt", arithTrig)) {
					replaceTimes = 1;
					replace(" ", "", arithTrig);
					sprintf(arithTrig, "%s", expressionF);
				}
				if (isContained("opentxt", arithTrig)) {
					if (isContained(" ", arithTrig)) {
						replaceTimes = 0;
						replace(" ", "RASF", arithTrig);
						sprintf(arithTrig, "%s", expressionF);
					}
				}
				printf(matrixResult, "");
				resultR = sqrt(DBL_MAX);
				variableController("INF");
				processVariable<T>("x");
				if (validVar == 0) {
					resultR = 0;
					variableController("x");
				}

				processVariable<T>("x");
				variableController("x");
				processVariable<T>("T");
				if (validVar == 0) {
					resultR = 0;
					variableController("T");
				}
				processVariable<T>("T");
				variableController("T");
				processVariable<T>("R");
				if (validVar == 0) {
					resultR = 0;
					variableController("R");
				}
				processVariable<T>("R");
				variableController("R");
				normalizeSolverCommandExpression(arithTrig);
				sprintf(fTrig, "%s", arithTrig); verbose = 0;
				if (useMaxPrecisionForCommand) {
					int previousHigherPrecision = higherPrecision;
					higherPrecision = 1;
					main_core<mp_float>(arithTrig, fTrig, fout, path, precisionValueTo<mp_float>(ansRV), precisionValueTo<mp_float>(ansIV), 1);
					higherPrecision = previousHigherPrecision;
				}
				else {
					main_core<T>(arithTrig, fTrig, fout, path, precisionValueTo<T>(ansRV), precisionValueTo<T>(ansIV), 1);
				}
				sprintf(arithTrig, ""); sprintf(fTrig, "");
				if (verified == 1) {
					result1 = precisionValueTo<T>(ansRV);
					result2 = precisionValueTo<T>(ansIV);
					verified = 0;
				}
				fflush(NULL);
				_delete(arithTrig, "arithTrig");
				if (fTrig != nullptr) {
					_delete(fTrig, "fTrig");
				}
			}
			if (fout != NULL) {
				fclose(fout);
				fout = NULL;
			}
			if (continu != 1 && fout != NULL) {
				fclose(fout);
			}
			if (argc >= 2) {
				if (expressionF != nullptr) {
					_delete(expressionF, "expressionF");
				}
				continu = 0;
				break;
			}

			sprintf(Path, "%s\\temp.txt", atcPath);
			FILE* Try = NULL;
			Try = fopen(Path, "r");
			if (Try != NULL) {
				fclose(Try);
				Try = fopen(Path, "w");
				fclose(Try);
			}
			end_processing = clock();
			T time_ms = (end_processing - start_processing) / (CLOCKS_PER_SEC / 1000);
			T time_s = qu(time_ms, T(1000));
			T time_ms_final = re(time_ms, T(1000));

			time_t hourF;
			time(&hourF);
			char* tim;
			tim = ctime(&hourF);
			tim[24] = '\0';
			sprintf(hou, "%c%c%c", tim[11], tim[12], '\0');
			int Hours = atoi(hou);
			sprintf(Min, "%c%c%c", tim[14], tim[15], '\0');
			int Minutes = atoi(Min);
			sprintf(sec, "%c%c%c", tim[17], tim[18], '\0');
			int Seconds = atoi(sec);
			sprintf(toOpen, "");
			sprintf(toOpen, "%s\\history.txt", atcPath);
			fout = NULL;
			while (fout == NULL) {
				fout = fopen(toOpen, "a+");
			}
			sprintf(forsprintf, "%c%c%c%c%c", tim[20], tim[21], tim[22], tim[23], '\0');
			sprintf(yea, "%s", forsprintf);
			int years = atoi(yea);
			sprintf(forsprintf, "%c%c%c", tim[8], tim[9], '\0');
			sprintf(da, "%s", forsprintf);
			int days = atoi(da);
			int months = 0;
			if (tim[4] == 'J' && tim[5] == 'a' && tim[6] == 'n') {
				months = 1;
			}
			if (tim[4] == 'F' && tim[5] == 'e' && tim[6] == 'b') {
				months = 2;
			}
			if (tim[4] == 'M' && tim[5] == 'a' && tim[6] == 'r') {
				months = 3;
			}
			if (tim[4] == 'A' && tim[5] == 'p' && tim[6] == 'r') {
				months = 4;
			}
			if (tim[4] == 'M' && tim[5] == 'a' && tim[6] == 'y') {
				months = 5;
			}
			if (tim[4] == 'J' && tim[5] == 'u' && tim[6] == 'n') {
				months = 6;
			}
			if (tim[4] == 'J' && tim[5] == 'u' && tim[6] == 'l') {
				months = 7;
			}
			if (tim[4] == 'A' && tim[5] == 'u' && tim[6] == 'g') {
				months = 8;
			}
			if (tim[4] == 'S' && tim[5] == 'e' && tim[6] == 'p') {
				months = 9;
			}
			if (tim[4] == 'O' && tim[5] == 'c' && tim[6] == 't') {
				months = 10;
			}
			if (tim[4] == 'N' && tim[5] == 'o' && tim[6] == 'v') {
				months = 11;
			}
			if (tim[4] == 'D' && tim[5] == 'e' && tim[6] == 'c') {
				months = 12;
			}

			convertComplex2Exponential(time_s, time_ms_final);
			sprintf(state, "Advanced Trigonometry Calculator v2.1.7 (Mem Factor: %.3f)       ==) Processed in %ss and %sms. ATC is ready to process more data. Latest ATC response was at %04d/%02d/%02d %02d:%02d:%02d (==", memFactor, respR, respI, years, months, days, Hours, Minutes, Seconds);
			applyConsoleTitleSafe(state);

			if (fout != NULL) {
				fclose(fout);
				fout = NULL;
			}




			if (expressionF != nullptr) {
				_delete(expressionF, "expressionF");
			}

		} while (continu == 1);
		mainRoutine = false;

	}
	_delete(value, "value");
	value = nullptr;
	_delete(currentProcess, "currentProcess"); currentProcess = nullptr;
	_delete(commandF, "commandF"); commandF = nullptr;

	_delete(commandF, "commandF");
	commandF = nullptr;
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
	_delete(savePreviousAns, "savePreviousAns");
	savePreviousAns = nullptr;
	_delete(boolVar, "boolVar");
	boolVar = nullptr;
	_delete(Path, "Path");
	Path = nullptr;
	_delete(state, "state");
	state = nullptr;
	_delete(hou, "hou");
	hou = nullptr;
	_delete(Min, "Min");
	Min = nullptr;
	_delete(sec, "sec");
	sec = nullptr;
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
	_delete(yea, "yea");
	yea = nullptr;
	_delete(da, "da");
	da = nullptr;

	_delete(vari, "vari");
	vari = nullptr;

	_delete(path, "path");
	path = nullptr;
	_delete(trigData, "trigData");
	trigData = nullptr;
	cleanupStaticDynamicAllocations();
}
template bool processTxt<double>(char* path, int re);
template bool processTxt<mp_float>(char* path, int re);

template<typename T>
bool processTxt(char* path, int re) {
	bool previousProcessingTxtFile = processingTxtFile;
	processingTxtFile = true;
	char* toOpen = getDynamicCharArray("", "toOpen");
	FILE* open;
	char* folder = getDynamicCharArray("", "folder");
	if (!isContained("User functions", path)) {
		sprintf(folder, "%s", path);
		if (isContained(".txt", folder) && !isContained("\\temp\\", path)) {
			rf = 0;
			FILE* check = NULL;
			replace(".txt", "", folder);
			sprintf(folder, "%s", expressionF);
			if (isContained("\"", folder)) {
				replace("\"", "", folder);
				sprintf(folder, "%s", expressionF);
			}
			sprintf(atcPath, "%s", folder);
			if (abs((int)strlen(savePathF)) == 0) {
				sprintf(savePathF, "%s", atcPath);
			}
			sprintf(customFolderPath, "%s", folder);
			char* hasFolder = getDynamicCharArray("", "hasFolder");
			sprintf(hasFolder, "%s\\hasFolder.txt", folder);

			check = fopen(hasFolder, "r");
			if (check == NULL) {
				char* toOpen = getDynamicCharArray("", "toOpen");
				sprintf(toOpen, "/C mkdir \"%s\"&mkdir \"%s\\Strings\"", folder, folder);
				using namespace std;
				std::string s = string(toOpen);
				std::wstring stemp = std::wstring(s.begin(), s.end());
				LPCWSTR sw = stemp.c_str();
				ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), sw, NULL, SW_SHOW);
				Sleep(333);
				check = fopen(hasFolder, "w");
				if (check != NULL) {
					fclose(check);
				}
				_delete(toOpen, "toOpen");
				toOpen = nullptr;
			}
			else {
				fclose(check);
			}
			_delete(hasFolder, "hasFolder");
			hasFolder = nullptr;
		}
	}
	else {
		sprintf(context, "main");
	}
	if (isEqual(saveATCPath, atcPath)) {
		sprintf(context, "main");
	}
	if (isContained("User functions", path) && isEqual(context, "script")) {
		sprintf(context, "main");
	}
	sprintf(toOpen, "%s\\variables.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		char* vari = getDynamicCharArray("", "vari");
		int i = 0;
		for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
		vari[i] = '\0';
		fclose(open);
		sprintf(saveTxtVariablesTextFile, "%s", vari);
		_delete(vari, "vari"); vari = nullptr;
	}
	else {
		if (open == NULL) {
			open = fopen(toOpen, "w");
		}
		if (open != NULL) {
			fclose(open);
		}
	}
	sprintf(toOpen, "%s\\renamedVar.txt", atcPath);
	open = fopen(toOpen, "r");
	if (open != NULL) {
		char* vari = getDynamicCharArray("", "vari");
		int i = 0;
		for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
		vari[i] = '\0';
		fclose(open);
		sprintf(saveRenamedTxtVariablesTextFile, "%s", vari);
		_delete(vari, "vari"); vari = nullptr;

	}
	else {
		if (open == NULL) {
			open = fopen(toOpen, "w");
		}
		if (open != NULL) {
			fclose(open);
		}
	}
	 PrecisionValue result1 = 0, result2 = 0, *anstxt = getDynamicDoubleArray(), *anstxtI = getDynamicDoubleArray();
	FILE* fin = NULL, * fout = NULL, * read = NULL;
	char* addBar = getDynamicCharArray("", "addBar"); char* savePath = getDynamicCharArray("", "savePath"); char* arith = getDynamicCharArray("", "arith"); char* sendFunc = getDynamicCharArray("", "sendFunc");
	char* resp = getDynamicCharArray("_answers.txt", "resp"); char* varLetters = getDynamicCharArray("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", "varLetters");
	int tD = 0, i, j, cP = 0, k, d, e, f, space = 0, v = 0, l = 0, m = 0, re1 = 0, save_rf = rf;
	bool toWrite = true;
	i = 0;
	while (i < abs((int)strlen(path))) {
		savePath[i] = path[i];
		i++;
	}
	savePath[i] = '\0';
	i = 0;
	while (i < re && re != 0) {
		anstxt[i] = ans[i];
		anstxtI[i] = ansI[i];
		i++;
	}
	i = 0;
	for (i = 0; i < abs((int)strlen(path)); i++) {
		if (path[i] == '"') {
			i++;
			j = i;
			while (i < abs((int)strlen(path))) {
				path[i - 1] = path[i];
				i++;
			}
			i = j;
		}
	}
	for (i = 0; i < abs((int)strlen(path)); i++) {
		if (path[i] == '"') {
			path[i] = '\0';
		}
	}
	j = 0;
	for (i = 0; i < abs((int)strlen(path)); i++) {
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
	for (i = 0; i < abs((int)strlen(addBar)); i++) {
		path[i] = addBar[i];
	}
	path[i] = '\0';
	i = 0;
	if (read != NULL) {
		fclose(read);
	}
	read = NULL;
	char* saveSendFunc = getDynamicCharArray("", "saveSendFunc");
	while (read == NULL && i < 100) {
		read = fopen(path, "a+");
		i++;
	}
	if (i < 100) {
		char* sD = getDynamicCharArray("", "sD");
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
			sprintf(toOpen, "");
			sprintf(toOpen, "%s\\variables.txt", atcPath);
			FILE* open = fopen(toOpen, "r");
			if (open != NULL) {
				char* vari = getDynamicCharArray("", "vari");
				int i = 0;
				for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
				vari[i] = '\0';
				fclose(open);
				sprintf(saveScriptVariablesTextFile, "%s", vari);
				_delete(vari, "vari");
				vari = nullptr;
			}
			else {
				if (open == NULL) {
					open = fopen(toOpen, "w");
				}
				if (open != NULL) {
					fclose(open);
				}
			}
			sprintf(toOpen, "%s\\renamedVar.txt", atcPath);
			open = fopen(toOpen, "r");
			if (open != NULL) {
				char* vari = getDynamicCharArray("", "vari");
				int i = 0;
				for (i = 0; (vari[i] = fgetc(open)) != EOF; i++);
				vari[i] = '\0';
				fclose(open);
				sprintf(saveScriptRenamedVariablesTextFile, "%s", vari);
				_delete(vari, "vari");
				vari = nullptr;
			}
			else {
				if (open == NULL) {
					open = fopen(toOpen, "w");
				}
				if (open != NULL) {
					fclose(open);
				}
			}
			countBreak = countOccurrences("break", sendFunc);
			countReturn = countOccurrences("return", sendFunc);
			countUseBreak = 0;
			countUseReturn = 0;
			returnedR = 0;
			returnedI = 0;
			Break = 0;
			atcProgramming<T>(sendFunc);
			resultR = returnedR; resultI = returnedI;
			toWrite = false;
			_delete(toOpen, "toOpen");
			toOpen = nullptr;
			_delete(folder, "folder");
			folder = nullptr;
			_delete(addBar, "addBar");
			addBar = nullptr;
			_delete(savePath, "savePath");
			savePath = nullptr;
			_delete(arith, "arith");
			arith = nullptr;
			_delete(sendFunc, "sendFunc");
			sendFunc = nullptr;
			_delete(resp, "resp");
			resp = nullptr;
			_delete(varLetters, "varLetters");
			varLetters = nullptr;
			_delete(saveSendFunc, "saveSendFunc");
			saveSendFunc = nullptr;
			_delete(arith, "arith");
			rf = re;
			_delete(sD, "sD");
			sD = nullptr;
			return toWrite;
		}
		else {
			m = 0;
			l = 0;
			while (m == 0) {
				if (path[l] == '.' && path[l + 1] == 't' && path[l + 2] == 'x' && path[l + 3] == 't' && path[l + 4] == '\0') {
					m = 1;
				}
				l++;
			}
			m = 0;
			l--;
			while (m < abs((int)strlen(resp))) {
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
			char* variable = getDynamicCharArray("", "variable");
			for (k = 0; k < cP; k++) {
				int savePreviousAnsType = previousAnsType;
				char* savePreviousAns = getDynamicCharArray("", "savePreviousAns");
				sprintf(savePreviousAns, "%s", saveMatrixAns);
				char* boolVar = getDynamicCharArray("true", "boolVar");
				resultR = 1; resultI = 0;
				int hk = variableValidator<T>(boolVar);
				if (hk == 1) {
					processVariable<T>(revariable);
					sprintf(boolVar, "%s", revariable);
					resultR = 1; resultI = 0;
					variableController(boolVar);
				}
				if (hk == 2) {
					sprintf(boolVar, "%s", revariable);
					resultR = 1; resultI = 0;
					variableController(boolVar);
				}
				sprintf(boolVar, "false");
				resultR = 0; resultI = 0;
				hk = variableValidator<T>(boolVar);
				if (hk == 1) {
					processVariable<T>(revariable);
					sprintf(boolVar, "%s", revariable);
					resultR = 0; resultI = 0;
					variableController(boolVar);
				}
				if (hk == 2) {
					sprintf(boolVar, "%s", revariable);
					resultR = 0; resultI = 0;
					variableController(boolVar);
				}
				previousAnsType = savePreviousAnsType;
				sprintf(saveMatrixAns, "%s", savePreviousAns);
				char* trigData = getDynamicCharArray("", "trigData");
				tD = 0;
				e = 0;
				for (f = d; sendFunc[f] != '\n' && f < abs((int)strlen(sendFunc)); f++) {
					trigData[e] = sendFunc[f];
					e++;
				}
				f++;
				d = f;
				trigData[e] = '\0';
				fflush(NULL);
				tD = 0;
				for (tD = 0; tD < abs((int)strlen(trigData)); tD++) {
					replaceTimes = 0;
					fflush(NULL);
					matrixMode = 0;
					useForVariables = false;
					sprintf(varRename, "");
					sprintf(revariable, "");
					feedbackValidation = 0;
					validVar = 1;   processingOK = 1;
					sprintf(varRename, "");
					i = 0;
					char* arith = getDynamicCharArray("", "arith");
					matrixMode = 0;
					int fl = 1, fr = 0;
					while (tD < abs((int)strlen(trigData)) && trigData[tD] != ',') {
						if (trigData[tD - 6] == 'p' && trigData[tD - 5] == 'r' && trigData[tD - 4] == 'i' && trigData[tD - 3] == 'n' && trigData[tD - 2] == 't' && trigData[tD - 1] == '(') {
							arith[i] = trigData[tD];
							i++; tD++;
							while (fl > fr && tD < abs((int)strlen(trigData))) {
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
					if (variableControllersUsed || abs((int)strlen(saveTxtVariablesTextFile)) == 0 || abs((int)strlen(saveRenamedTxtVariablesTextFile)) == 0) {
						char* toOpen = getDynamicCharArray("", "toOpen");
						FILE* open;
						sprintf(toOpen, "%s\\variables.txt", atcPath);
						open = fopen(toOpen, "w");
						if (open != NULL) {
							fprintf(open, "%s", saveTxtVariablesTextFile);
							fclose(open);
						}
						sprintf(toOpen, "%s\\renamedVar.txt", atcPath);
						open = fopen(toOpen, "w");
						if (open != NULL) {
							fprintf(open, "%s", saveRenamedTxtVariablesTextFile);
							fclose(open);
						}
						variableControllersUsed = false;
						_delete(toOpen, "toOpen"); toOpen = nullptr;
					}

					sprintf(matrixResult, "");
					resultR = sqrt(DBL_MAX);
					variableController("INF");
					processVariable<T>("x");
					if (validVar == 0) {
						resultR = 0;
						variableController("x");
					}
					processVariable<T>("x");
					variableController("x");
					processVariable<T>("T");
					if (validVar == 0) {
						resultR = 0;
						variableController("T");
					}
					processVariable<T>("R");
					if (validVar == 0) {
						resultR = 0;
						variableController("R");
					}
					processVariable<T>("R");
					variableController("R");
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
						if (isContained("open txt", arith)) {
							replaceTimes = 1;
							replace(" ", "", arith);
							sprintf(arith, "%s", expressionF);
						}
						if (isContained("opentxt", arith)) {
							if (isContained(" ", arith)) {
								replaceTimes = 0;
								replace(" ", "RASF", arith);
								sprintf(arith, "%s", expressionF);
							}
						}
						if (isContained("atc", arith)) {
							sprintf(atcPath, "%s", saveATCPath);
						}
						if (!isContained("atc", arith) && (!isContained("User functions", path)) && !runningScript) {
							sprintf(atcPath, "%s", savePathF);
						}
						main_core<T>(arith, arith, fin, path, precisionValueTo<T>(result1), precisionValueTo<T>(result2), 0);
						sprintf(arith, "");
						if (verified == 1) {
							result1 = resultR;
							result2 = resultI;
							verified = 0;
						}
					}
					else {
						_delete(arith, "arith");
						_delete(savePreviousAns, "savePreviousAns");
						savePreviousAns = nullptr;
						_delete(boolVar, "boolVar");
						boolVar = nullptr;
						_delete(trigData, "trigData");
						trigData = nullptr;
						_delete(sD, "sD");
						sD = nullptr;
						break;
					}
					fflush(NULL);
					sprintf(arith, "");
					if (fin != NULL) {
						fclose(fin);
					}
					_delete(arith, "arith");
					arith = nullptr;
				}
				if (fin != NULL) {
					fclose(fin);
				}
				_delete(savePreviousAns, "savePreviousAns");
				savePreviousAns = nullptr;
				_delete(boolVar, "boolVar");
				boolVar = nullptr;
				_delete(trigData, "trigData");
				trigData = nullptr;
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
			_delete(variable, "variable");
			variable = nullptr;
		}
		_delete(sD, "sD");
		sD = nullptr;
	}

	int h;
	for (h = 0; h < abs((int)strlen(path)); h++) {
		expressionF[h] = path[h];
	}
	expressionF[h] = '\0';
	if (fin != NULL) { fclose(fin); }if (fout != NULL) { fclose(fout); }if (open != NULL) { fclose(open); } if (read != NULL) { fclose(read); }
	rf = save_rf;
	if (!toWrite) {
		char* eliminate = getDynamicCharArray("", "eliminate");
		if (savePath[0] == '\"') {
			int y = 0;
			while (savePath[y + 1] != '\0') {
				savePath[y] = savePath[y + 1];
				y++;
			}
			savePath[y] = '\0';
		}
		if (savePath[abs((int)strlen(savePath)) - 1] == '\"') {
			savePath[abs((int)strlen(savePath)) - 1] = '\0';
		}
		savePath[abs((int)strlen(savePath)) - 4] = '\0';
		sprintf(eliminate, "del \"%s_answers.txt\"", savePath);
		system(eliminate);
		_delete(eliminate, "eliminate");
		eliminate = nullptr;
	}
	_delete(arith, "arith");
	_delete(toOpen, "toOpen");
	toOpen = nullptr;
	_delete(folder, "folder");
	folder = nullptr;
	_delete(addBar, "addBar");
	addBar = nullptr;
	_delete(savePath, "savePath");
	savePath = nullptr;
	_delete(arith, "arith");
	arith = nullptr;
	_delete(sendFunc, "sendFunc");
	sendFunc = nullptr;
	_delete(resp, "resp");
	resp = nullptr;
	_delete(varLetters, "varLetters");
	varLetters = nullptr;
	_delete(saveSendFunc, "saveSendFunc");
	saveSendFunc = nullptr;
	processingTxtFile = previousProcessingTxtFile;
	rf = re;
	return toWrite;
}
template<typename T>
bool dataVerifier(char* data, T result1, T result2, int comment, int verify) {
	char* variable = getDynamicCharArray("", "variable");
	replaceTimes = 0;
	if (abs((int)strlen(data)) == 0 || data == nullptr) {
		_delete(variable, "variable");
		return true;
	}

	bool decision = true;
	if (isContained("()", data)) {
		decision = false;
		if (comment == 1) {
			printf("\nError in parentheses. \n ==> ATC has detected an empty open and close parantheses, i.e. \"()\".\n");
		}
		_delete(variable, "variable");
		return decision;
	}

	int lastCharIndex = 0;

	int h = 0;
	while (h < abs((int)strlen(data))) {
		if (data[h] == '{') {
			data[h] = '(';
		}
		if (data[h] == '}') {
			data[h] = ')';
		}
		h++;
	}
	replaceTimes = 0;
	if (abs((int)strlen(data)) > 0) {
		int kg = 0, kc = 0, i = 0;
		for (i = 0; i < abs((int)strlen(data)); i++) {
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
				_delete(variable, "variable");

				return decision;
			}
			decision = false;
			if (comment == 1) {
				printf("\nError in parentheses. \n ==> The number of left and right parenthesis entered must be equal.\n ==> Enter \"[\" or \"{\" is the same as \"(\" and \"]\" or \"}\" is the same as \")\".\n ==> The expression that you entered has %d left parenthesis and %d right parenthesis.\n", kg, kc);
			}
			_delete(variable, "variable");
			return decision;
		}
		else {
			if (data[0] == 's' && data[1] == 'o' && data[2] == 'l' && data[3] == 'v' && data[4] == 'e' && data[5] == 'r' && data[6] == '(') {
				int solverDepth = 0;
				bool fullSolverExpression = true;
				for (int solverIndex = 6; solverIndex < abs((int)strlen(data)); solverIndex++) {
					if (data[solverIndex] == '(') {
						solverDepth++;
					}
					else if (data[solverIndex] == ')') {
						solverDepth--;
						if (solverDepth == 0 && solverIndex != abs((int)strlen(data)) - 1) {
							fullSolverExpression = false;
							break;
						}
					}
					if (solverDepth < 0) {
						fullSolverExpression = false;
						break;
					}
				}
				if (fullSolverExpression && solverDepth == 0) {
					_delete(variable, "variable");
					return true;
				}
			}
			int cp = 0, mark = 0;
			int c = 0, d = 0, k = 0, l = 0, h = 0, s = 0;
			int* parent = getDynamicIntArray();
			for (s = 0; s < abs((int)strlen(data)); s++) {
				parent[s] = 0;
			}
			for (s = 0; s < abs((int)strlen(data)) && s < abs((int)strlen(data)); s++) {
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
			s = 0;
			bool skipNestedParenthesisWarning = true;
			replaceTimes = 0;
			for (s = 0; !skipNestedParenthesisWarning && s < abs((int)strlen(data)); s++) {
				if (parent[s] != 0 && parent[s + 1] == parent[s] + 1) {
					savePar = s;
					s++;
					while (parent[s] != parent[savePar] && s < abs((int)strlen(data))) {
						s++;
					}
					s--;
					if (parent[s] == parent[s + 1] + 1) {
						decision = false;
						if (comment == 1) {
							printf("\nError in parentheses. \n ==> The number of left and right parenthesis entered must be equal.\n ==> You can not have a valid math expression where a close parenthesis \")\" is found before its open parenthesis \"(\".\n ==> Enter \"[\" or \"{\" is the same as \"(\" and \"]\" or \"}\" is the same as \")\".\n ==> The expression that you entered has %d left parenthesis and %d right parenthesis.\n ==> You should use just the required number of parenthesis. <== ", kg, kc);
							printf("\n");
						}
						_delete( parent, "parent"); parent = nullptr;
						_delete(variable, "variable");
						return decision;
					}
					else {
						s = savePar;
					}
				}
			}
			_delete( parent, "parent"); parent = nullptr;
		}
		int j = 0, k = 0, l = 0, kr = 0, kl = 0, v = 0, cChars = 0, fr = 0, ra = 0, nDot = 0, g = 0, d = 0, w = 0, y = 0, t = 0, space = 0;
		char* function = getDynamicCharArray("", "function"); char* expression = getDynamicCharArray("", "expression"); char* text = getDynamicCharArray("", "text");
		char* value = getDynamicCharArray("", "value"); char* saveVar = getDynamicCharArray("", "saveVar");
		char* numsysData = getDynamicCharArray("", "numsysData");
		int u = 0, p = 0;
		if (synTest == 0) {
			int y = 0, r = 0;
			char* funcToCheck = getDynamicCharArray("", "funcToCheck");
			if (isContained("logb", data)) {
				y = strStart;
				while ((data[y - 1] == 'b' && data[y] == '(') == false && y < abs((int)strlen(data))) {
					y++;
				}
				r = y + 1;
			}
			if (isContained("rtD", data)) {
				y = strStart;
				while ((data[y - 1] == 'D' && data[y] == '(') == false && y < abs((int)strlen(data))) {
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
					_delete(function, "function"); function = nullptr;
					_delete(variable, "variable"); variable = nullptr;
					_delete(expression, "expression"); expression = nullptr;
					_delete(text, "text"); text = nullptr;
					_delete(value, "value"); value = nullptr;
					_delete(saveVar, "saveVar"); saveVar = nullptr;
					_delete(numsysData, "numsysData"); numsysData = nullptr;
					_delete(funcToCheck, "funcToCheck"); funcToCheck = nullptr;

					return decision;
				}
				if (nPlaces == 8000) {
					if (comment == 1) {
						puts("\nOctal places number entered with errors.\n");
					}
					decision = false;
					_delete(function, "function"); function = nullptr;
					_delete(variable, "variable"); variable = nullptr;
					_delete(expression, "expression"); expression = nullptr;
					_delete(text, "text"); text = nullptr;
					_delete(value, "value"); value = nullptr;
					_delete(saveVar, "saveVar"); saveVar = nullptr;
					_delete(numsysData, "numsysData"); numsysData = nullptr;
					_delete(funcToCheck, "funcToCheck"); funcToCheck = nullptr;

					return decision;
				}
				if (nPlaces == 10000) {
					if (comment == 1) {
						puts("\nDecimal places number entered with errors.\n");
					}
					decision = false;
					_delete(function, "function"); function = nullptr;
					_delete(variable, "variable"); variable = nullptr;
					_delete(expression, "expression"); expression = nullptr;
					_delete(text, "text"); text = nullptr;
					_delete(value, "value"); value = nullptr;
					_delete(saveVar, "saveVar"); saveVar = nullptr;
					_delete(numsysData, "numsysData"); numsysData = nullptr;
					return decision;
				}
				if (nPlaces == 16000) {
					if (comment == 1) {
						puts("\nHexadecimal places number entered with errors.\n");
					}
					decision = false;
					_delete(function, "function"); function = nullptr;
					_delete(variable, "variable"); variable = nullptr;
					_delete(expression, "expression"); expression = nullptr;
					_delete(text, "text"); text = nullptr;
					_delete(value, "value"); value = nullptr;
					_delete(saveVar, "saveVar"); saveVar = nullptr;
					_delete(numsysData, "numsysData"); numsysData = nullptr;
					_delete(funcToCheck, "funcToCheck"); funcToCheck = nullptr;

					return decision;
				}
			}
			for (w = 0; w < abs((int)strlen(data)); w++) {
				if ((data[w] == 'B' || data[w] == 'O' || data[w] == 'H' || data[w] == 'P' || data[w] == '#') && (w == 0 || data[w - 1] == '+' || data[w - 1] == '-' || data[w - 1] == '*' || data[w - 1] == '/' || data[w - 1] == '^' || data[w - 1] == '(')) {
					w++;
					if (data[w - 1] == 'B') {
						if (data[w] == '_' || data[w] == '-') {
							w++;
						}
						y = 0;
						while (data[w] != '+' && data[w] != '-' && data[w] != '*' && data[w] != '/' && data[w] != '^' && data[w] != ')' && data[w - 1] != 'b' && data[w] != '(' && data[w - 1] != 'D' && data[w] != '(' && w < abs((int)strlen(data))) {
							numsysData[y] = data[w];
							w++; y++;
						}
						numsysData[y] = '\0';
						t = 0;
						for (y = 0; y < abs((int)strlen(numsysData)); y++) {
							if (numsysData[y] == '1' || numsysData[y] == '0' || numsysData[y] == '.') {
								t++;
							}
						}
						if (t != abs((int)strlen(numsysData))) {
							decision = false;
							if (comment == 1) {
								puts("\nBinary number entered with errors.\n");
							}
							_delete(function, "function"); function = nullptr;
							_delete(variable, "variable"); variable = nullptr;
							_delete(expression, "expression"); expression = nullptr;
							_delete(text, "text"); text = nullptr;
							_delete(value, "value"); value = nullptr;
							_delete(saveVar, "saveVar"); saveVar = nullptr;
							_delete(numsysData, "numsysData"); numsysData = nullptr;
							_delete(funcToCheck, "funcToCheck"); funcToCheck = nullptr;

							return decision;
						}
					}
					if (data[w - 1] == 'O') {
						if (data[w] == '_' || data[w] == '-') {
							w++;
						}
						y = 0;
						while (data[w] != '+' && data[w] != '-' && data[w] != '*' && data[w] != '/' && data[w] != '^' && data[w] != ')' && data[w - 1] != 'b' && data[w] != '(' && data[w - 1] != 'D' && data[w] != '(' && w < abs((int)strlen(data))) {
							numsysData[y] = data[w];
							w++; y++;
						}
						numsysData[y] = '\0';
						t = 0;
						for (y = 0; y < abs((int)strlen(numsysData)); y++) {
							if (numsysData[y] == '0' || numsysData[y] == '1' || numsysData[y] == '2' || numsysData[y] == '3' || numsysData[y] == '4' || numsysData[y] == '5' || numsysData[y] == '6' || numsysData[y] == '7' || numsysData[y] == '.') {
								t++;
							}
						}
						if (t != abs((int)strlen(numsysData))) {
							decision = false;
							if (comment == 1) {
								puts("\nOctal number entered with errors.\n");
							}
							_delete(function, "function"); function = nullptr;
							_delete(variable, "variable"); variable = nullptr;
							_delete(expression, "expression"); expression = nullptr;
							_delete(text, "text"); text = nullptr;
							_delete(value, "value"); value = nullptr;
							_delete(saveVar, "saveVar"); saveVar = nullptr;
							_delete(numsysData, "numsysData"); numsysData = nullptr;
							_delete(funcToCheck, "funcToCheck"); funcToCheck = nullptr;

							return decision;
						}
					}
					if (data[w - 1] == 'H') {
						if (data[w] == '_' || data[w] == '-') {
							w++;
						}
						y = 0;
						while (data[w] != '+' && data[w] != '-' && data[w] != '*' && data[w] != '/' && data[w] != '^' && data[w] != ')' && data[w - 1] != 'b' && data[w] != '(' && data[w] != '(' && w < abs((int)strlen(data))) {
							numsysData[y] = data[w];
							w++; y++;
						}
						numsysData[y] = '\0';
						t = 0;
						for (y = 0; y < abs((int)strlen(numsysData)); y++) {
							if (numsysData[y] == '0' || numsysData[y] == '1' || numsysData[y] == '2' || numsysData[y] == '3' || numsysData[y] == '4' || numsysData[y] == '5' || numsysData[y] == '6' || numsysData[y] == '7' || numsysData[y] == '8' || numsysData[y] == '9' || numsysData[y] == 'A' || numsysData[y] == 'B' || numsysData[y] == 'C' || numsysData[y] == 'D' || numsysData[y] == 'E' || numsysData[y] == 'F' || numsysData[y] == '.') {
								t++;
							}
						}
						if (t != abs((int)strlen(numsysData))) {
							decision = false;
							if (comment == 1) {
								puts("\nHexadecimal number entered with errors.\n");
							}
							_delete(function, "function"); function = nullptr;
							_delete(variable, "variable"); variable = nullptr;
							_delete(expression, "expression"); expression = nullptr;
							_delete(text, "text"); text = nullptr;
							_delete(value, "value"); value = nullptr;
							_delete(saveVar, "saveVar"); saveVar = nullptr;
							_delete(numsysData, "numsysData"); numsysData = nullptr;
							_delete(funcToCheck, "funcToCheck"); funcToCheck = nullptr;

							return decision;
						}
					}
					if (data[w - 1] == 'P') {
						y = 0;
						while (data[w] != '+' && data[w] != '-' && data[w] != '*' && data[w] != '/' && data[w] != '^' && data[w] != ')' && data[w - 1] != 'b' && data[w] != '(' && data[w - 1] != 'D' && data[w] != '(' && w < abs((int)strlen(data))) {
							numsysData[y] = data[w];
							w++; y++;
						}
						numsysData[y] = '\0';
						decision = verifyPrefix(numsysData);
						if (decision == 0) {
							if (comment == 1) {
								puts("\nSI prefix entered with errors.\n");
							}
							_delete(function, "function"); function = nullptr;
							_delete(variable, "variable"); variable = nullptr;
							_delete(expression, "expression"); expression = nullptr;
							_delete(text, "text"); text = nullptr;
							_delete(value, "value"); value = nullptr;
							_delete(saveVar, "saveVar"); saveVar = nullptr;
							_delete(numsysData, "numsysData"); numsysData = nullptr;
							_delete(funcToCheck, "funcToCheck"); funcToCheck = nullptr;

							return decision;
						}
					}
					if (data[w - 1] == '#') {
						y = 0;
						while (verifyNumber(data[w]) == 1 && data[w] != '+' && data[w] != '-' && data[w] != '*' && data[w] != '/' && data[w] != '^' && data[w] != ')' && data[w - 1] != 'b' && data[w] != '(' && data[w - 1] != 'D' && data[w] != '(' && w < abs((int)strlen(data))) {
							numsysData[y] = data[w];
							w++; y++;
						}
						numsysData[y] = '+'; numsysData[y + 1] = '0'; numsysData[y + 2] = '\0';
						int reIndex = (int)arithSolver<T>(numsysData, (T)0);
						if (reIndex >= rf) {
							if (comment == 1) {
								puts("\nResult indentifier not found.\n");
							}
							decision = false;
							_delete(function, "function"); function = nullptr;
							_delete(variable, "variable"); variable = nullptr;
							_delete(expression, "expression"); expression = nullptr;
							_delete(text, "text"); text = nullptr;
							_delete(value, "value"); value = nullptr;
							_delete(saveVar, "saveVar"); saveVar = nullptr;
							_delete(numsysData, "numsysData"); numsysData = nullptr;
							_delete(funcToCheck, "funcToCheck"); funcToCheck = nullptr;

							return decision;
						}
					}
				}
			}
			w = abs((int)strlen(data)) - 3;
			if ((data[w] == '+' || data[w] == '-' || data[w] == '*' || data[w] == '/' || data[w] == '^') && isContainedByIndex("+0", data, w - 1) && !isContainedByIndex("+0)", data, w - 1)) {
				bool detectedDoubleZero = false;
				if (isContainedByIndex("00", data, abs((int)strlen(data) - 2))) {
					detectedDoubleZero = true;
				}
				if (!detectedDoubleZero) {
					verify = 0;
					if (comment == 1) {
						puts("\nYour expression is terminating with an arithmetic symbol.\n");
					}
					sprintf(data, "%s+0", data);
					decision = false;
					_delete(function, "function"); function = nullptr;
					_delete(variable, "variable"); variable = nullptr;
					_delete(expression, "expression"); expression = nullptr;
					_delete(text, "text"); text = nullptr;
					_delete(value, "value"); value = nullptr;
					_delete(saveVar, "saveVar"); saveVar = nullptr;
					_delete(numsysData, "numsysData"); numsysData = nullptr;
					_delete(funcToCheck, "funcToCheck"); funcToCheck = nullptr;

					return decision;
				}

			}
			for (w = 0; w < abs((int)strlen(data)); w++) {
				if ((data[w] == '+' || data[w] == '-' || data[w] == '*' || data[w] == '/' || data[w] == '^') && (data[w + 1] == '+' || data[w + 1] == '-' && data[w - 2] != '1' && data[w - 1] != '0' || data[w + 1] == '*' || data[w + 1] == '/' || data[w + 1] == '^' || data[w + 1] == '!')) {
					verify = 0;
					if (comment == 1) {
						puts("\nYour expression has consecutive arithmetic symbols.\n");
					}
					decision = false;
					_delete(function, "function"); function = nullptr;
					_delete(variable, "variable"); variable = nullptr;
					_delete(expression, "expression"); expression = nullptr;
					_delete(text, "text"); text = nullptr;
					_delete(value, "value"); value = nullptr;
					_delete(saveVar, "saveVar"); saveVar = nullptr;
					_delete(numsysData, "numsysData"); numsysData = nullptr;
					_delete(funcToCheck, "funcToCheck"); funcToCheck = nullptr;
					return decision;
				}
			}
			_delete(funcToCheck, "funcToCheck"); funcToCheck = nullptr;
		}

		u = 0;
		char* varValidator = getDynamicCharArray("", "varValidator");
		for (u; u < abs((int)strlen(data)); u++) {
			int r = 0, f = 0;
			p = 0;
			sprintf(varValidator, "");
			if (verifyLetter(data[u]) == 1) {
				if (data[u] == 'B' || data[u] == 'O' || data[u] == 'H' || data[u] == 'P') {
					varValidator[p] = data[u];
					u++; p++;
					if (data[u] == '-' || data[u] == '_') {
						varValidator[p] = data[u];
						u++; p++;
					}
					while (data[u] != ')' && data[u] != '(' && data[u] != '+' && data[u] != '-' && data[u] != '*' && data[u] != '/' && data[u] != '^' && u < abs((int)strlen(data)) && firstLetterFunction(data[u]) == 0) {
						varValidator[p] = data[u];
						u++; p++;
					}
				}
				while (verifyLetter(data[u]) == 1 && (data[u] == 'b' && data[u - 1] == 'g') == false && (data[u] == 'D' && data[u - 1] == 't') == false && u < abs((int)strlen(data))) {
					varValidator[p] = data[u];
					u++; p++;
				}
				if (data[u - 1] == 't' && data[u] == 'D' || data[u - 1] == 'g' && data[u] == 'b') {
					varValidator[p] = data[u];
					u++; p++;
					while ((data[u] == 'b' && data[u + 1] == '(') == false && (data[u] == 'D' && data[u + 1] == '(') == false && u < abs((int)strlen(data))) {
						varValidator[p] = data[u];
						u++; p++;
					}
					varValidator[p] = data[u];
					u++; p++;
				}
				varValidator[p] = '\0';
				bool notProcessAsVariable = false;
				if (data[u] == '[') {
					notProcessAsVariable = true;
				}
				p = 0;
				for (p = 0; p < abs((int)strlen(varValidator)); p++) {
					saveVar[p] = varValidator[p];
				}
				saveVar[p] = '\0';
				if (!notProcessAsVariable && abs((int)strlen(varValidator)) > 0) {
					processVariable<T>(varValidator);
					int df = p;
					varValidator[p] = '\0';
					if (varValidator[0] == 'r' && varValidator[1] == 't' && varValidator[2] == 'D') {
						p = 3;
						while (p < abs((int)strlen(varValidator)) && p < abs((int)strlen(varValidator))) {
							if (varValidator[p] == 'D') {
								varValidator[3] = 'D'; varValidator[4] = '?'; varValidator[5] = '\0';
							}
							p++;
						}
					}
					if (varValidator[0] == 'l' && varValidator[1] == 'o' && varValidator[2] == 'g' && varValidator[3] == 'b') {
						p = 4;
						while (p < abs((int)strlen(varValidator)) && p < abs((int)strlen(varValidator))) {
							if (varValidator[p] == 'b') {
								varValidator[4] = 'b'; varValidator[5] = '?'; varValidator[6] = '\0';
							}
							p++;
						}
					}
					T funcF = 0;
					char* saveExpr = getDynamicCharArray("", "saveExpr");
						bool hasSolverArgumentX = true;
						replaceTimes = 0;
					if (df == p) {
						varValidator[p] = '?'; varValidator[p + 1] = '\0';


						sprintf(saveExpr, "%s", varValidator);

						funcF = functionProcessor<T>(varValidator, 2, 7, 12, "");
						if (funcF == 0.5 && isContained("solver", varValidator)) {
							if (!hasSolverArgumentX) {
								if (comment == 1) {
									puts("\nError: No 'x' detected in the argument of your solver function.\n");
								}
								decision = false;
								_delete(function, "function"); function = nullptr;
								_delete(variable, "variable"); variable = nullptr;
								_delete(expression, "expression"); expression = nullptr;
								_delete(text, "text"); text = nullptr;
								_delete(value, "value"); value = nullptr;
								_delete(saveVar, "saveVar"); saveVar = nullptr;
								_delete(numsysData, "numsysData"); numsysData = nullptr;
								_delete(varValidator, "varValidator");
								_delete(saveExpr, "saveExpr");
								return decision;
							}
						}
						if (funcF == 0.5 && isContained("det", varValidator)) {
							char* matrix = getDynamicCharArray("", "matrix");
							if (isContained("det", data)) {
								int det = strEnd;
								int t = 0, rCount = 0, lCount = 0;
								if (data[det] == '(') {
									lCount++;
									det++;
									while (lCount > rCount && det < abs((int)strlen(data))) {
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
								check4Vector = 1;

								calcNow<T>(matrix, (T)0, (T)0);
								if (abs((int)strlen(matrixResult)) > 0) {
									sprintf(expressionF, "%s", matrixResult);
									replaceTimes = 0;
									matrixMode = 1;
									if (isContained(":", expressionF)) {
										replace(":", "\\", expressionF);

									}
									if (isContained("*", expressionF)) {
										replace("*", ";", expressionF);
									}
									sprintf(matrix, "%s", expressionF);
								}
								int mIndex = 0, ff = 0, cols = 1, lins = 1, saveCols = -1, errorCols = 0;
								do {

									ff = 0;
									while (matrix[mIndex] != '\\' && matrix[mIndex] != ';' && mIndex < abs((int)strlen(matrix)) - 1) {
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
											if (mIndex < abs((int)strlen(matrix))) {
												lins++;
												cols = 1;
											}
										}
									}
									mIndex++;
								} while (mIndex < abs((int)strlen(matrix)));
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
									_delete(function, "function"); function = nullptr;
									_delete(variable, "variable"); variable = nullptr;
									_delete(expression, "expression"); expression = nullptr;
									_delete(text, "text"); text = nullptr;
									_delete(value, "value"); value = nullptr;
									_delete(saveVar, "saveVar"); saveVar = nullptr;
									_delete(numsysData, "numsysData"); numsysData = nullptr;
									_delete(varValidator, "varValidator");
									_delete(saveExpr, "saveExpr");

									return decision;
								}
							}
							_delete(matrix, "matrix"); matrix = nullptr;
						}
					}
					sprintf(varValidator, "%s", saveExpr);

					if (funcF != 0.5) {
						if (validVar == 0) {
							if (varValidator[0] == 'E' || varValidator[0] == 'B' || varValidator[0] == 'O' || varValidator[0] == 'H' || varValidator[0] == 'P' || varValidator[0] == 'e' || varValidator[0] == 'p' && varValidator[1] == 'i' || varValidator[0] == 'I' && varValidator[1] == 'N' && varValidator[2] == 'F') {
								if (varValidator[0] == 'E' || varValidator[0] == 'B' || varValidator[0] == 'O' || varValidator[0] == 'H' || initialProcessor<T>(varValidator, (T)0) != 0) {
									decision = true;
								}
								else {
									decision = false;
									if (isEqual("nan", saveVar)) {
										decision = true;
										_delete(function, "function"); function = nullptr;
										_delete(variable, "variable"); variable = nullptr;
										_delete(expression, "expression"); expression = nullptr;
										_delete(text, "text"); text = nullptr;
										_delete(value, "value"); value = nullptr;
										_delete(saveVar, "saveVar"); saveVar = nullptr;
										_delete(numsysData, "numsysData"); numsysData = nullptr;
										_delete(varValidator, "varValidator");
										_delete(saveExpr, "saveExpr");

										return decision;
									}
									if (comment == 1) {
										printf("\nThe variable \"%s\" is not created yet.\n", saveVar);
									}
									_delete(function, "function"); function = nullptr;
									_delete(variable, "variable"); variable = nullptr;
									_delete(expression, "expression"); expression = nullptr;
									_delete(text, "text"); text = nullptr;
									_delete(value, "value"); value = nullptr;
									_delete(saveVar, "saveVar"); saveVar = nullptr;
									_delete(numsysData, "numsysData"); numsysData = nullptr;
									_delete(varValidator, "varValidator");
									_delete(saveExpr, "saveExpr");

									return decision;
								}
							}
							else {
								sprintf(text, "calc(%s)", saveVar);
								if (isContained(text, data)) {
									renamer(saveVar);
									sprintf(saveVar, "%s", expressionF);
									stringVariableToString(saveVar);
									if (validVar == 0) {
										if (comment == 1) {
											printf("\nThe string variable \"%s\" is not created yet.\n", saveVar);
										}
										decision = false;
									}
								}
								else {
									sprintf(text, "strlen(%s)", saveVar);
									if (isContained(text, data)) {
										renamer(saveVar);
										sprintf(saveVar, "%s", expressionF);
										stringVariableToString(saveVar);
										if (validVar == 0) {
											if (comment == 1) {
												printf("\nThe string variable \"%s\" is not created yet.\n", saveVar);
											}
											decision = false;
										}
									}
									else {
										sprintf(text, "countoccurrences");
										if (isContained(text, data)) {
											if (!(countOccurrences("\\", data) == 1)) {
												if (comment == 1) {
													printf("\nThe string variable \"%s\" is not created yet.\n", saveVar);
												}
												decision = false;
											}
										}
										else {
											decision = false;
											if (isEqual("nan", saveVar)) {
												decision = true;
												_delete(function, "function"); function = nullptr;
												_delete(variable, "variable"); variable = nullptr;
												_delete(expression, "expression"); expression = nullptr;
												_delete(text, "text"); text = nullptr;
												_delete(value, "value"); value = nullptr;
												_delete(saveVar, "saveVar"); saveVar = nullptr;
												_delete(numsysData, "numsysData"); numsysData = nullptr;
												_delete(varValidator, "varValidator");
												_delete(saveExpr, "saveExpr");

												return decision;
											}
											if (comment == 1) {
												printf("\nThe variable \"%s\" is not created yet.\n", saveVar);
											}
											_delete(function, "function"); function = nullptr;
											_delete(variable, "variable"); variable = nullptr;
											_delete(expression, "expression"); expression = nullptr;
											_delete(text, "text"); text = nullptr;
											_delete(value, "value"); value = nullptr;
											_delete(saveVar, "saveVar"); saveVar = nullptr;
											_delete(numsysData, "numsysData"); numsysData = nullptr;
											_delete(varValidator, "varValidator");
											_delete(saveExpr, "saveExpr");

											return decision;
										}
									}
								}
							}
						}
					}
					_delete(saveExpr, "saveExpr");

				}
				else {
					u++;
				}
			}

		}

		for (d = 0; d < abs((int)strlen(data)); d++) {
			g = 0; nDot = 0;
			while ((data[d] == '.' || data[d] == '0' || data[d] == '1' || data[d] == '2' || data[d] == '3' || data[d] == '4' || data[d] == '5' || data[d] == '6' || data[d] == '7' || data[d] == '8' || data[d] == '9' || data[d] == 'A' || data[d] == 'B' || data[d] == 'C' || data[d] == 'D' || data[d] == 'E' || data[d] == 'F') && d < abs((int)strlen(data))) {
				value[g] = data[d];
				d++; g++;
			}
			value[g] = '\0';
			for (g = 0; g < abs((int)strlen(value)); g++) {
				if (value[g] == '.') {
					nDot++;
				}
			}
			if (nDot > 1) {
				decision = false;
				if (comment == 1) {
					puts("\nYou entered more than one dot on the entered value.\n");
				}
				_delete(function, "function"); function = nullptr;
				_delete(variable, "variable"); variable = nullptr;
				_delete(expression, "expression"); expression = nullptr;
				_delete(text, "text"); text = nullptr;
				_delete(value, "value"); value = nullptr;
				_delete(saveVar, "saveVar"); saveVar = nullptr;
				_delete(numsysData, "numsysData"); numsysData = nullptr;
				_delete(varValidator, "varValidator");

				return decision;
			}
		}
		for (ra = 0; ra < abs((int)strlen(data)); ra++) {
			if (data[ra] == '_' && data[ra - 1] == '_') {
				decision = false;
				if (comment == 1) {
					puts("\nYou don't need to enter \"__\", please use only a symbol \"_\" to represent negative values.\n");
				}
				_delete(function, "function"); function = nullptr;
				_delete(variable, "variable"); variable = nullptr;
				_delete(expression, "expression"); expression = nullptr;
				_delete(text, "text"); text = nullptr;
				_delete(value, "value"); value = nullptr;
				_delete(saveVar, "saveVar"); saveVar = nullptr;
				_delete(numsysData, "numsysData"); numsysData = nullptr;
				_delete(varValidator, "varValidator");

				return decision;
			}
			for (fr = 0; fr < abs((int)strlen(validChars)); fr++) {
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
			_delete(function, "function"); function = nullptr;
			_delete(variable, "variable"); variable = nullptr;
			_delete(expression, "expression"); expression = nullptr;
			_delete(text, "text"); text = nullptr;
			_delete(value, "value"); value = nullptr;
			_delete(saveVar, "saveVar"); saveVar = nullptr;
			_delete(numsysData, "numsysData"); numsysData = nullptr;
			_delete(varValidator, "varValidator");

			return decision;
		}
		if ((data[0] == '+' || data[0] == '-' || data[0] == '*' || data[0] == '/' || data[0] == '^') && (data[1] == '0' && data[2] == '\0')) {
			decision = false;
			if (comment == 1) {
				puts("\nYou are trying relate the previous expression with zero (0).\n");
			}
			_delete(function, "function"); function = nullptr;
			_delete(variable, "variable"); variable = nullptr;
			_delete(expression, "expression"); expression = nullptr;
			_delete(text, "text"); text = nullptr;
			_delete(value, "value"); value = nullptr;
			_delete(saveVar, "saveVar"); saveVar = nullptr;
			_delete(numsysData, "numsysData"); numsysData = nullptr;
			_delete(varValidator, "varValidator");
			return decision;
		}
		for (i = 0; i < abs((int)strlen(data)); i++) {
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
			while (i < abs((int)strlen(data))) {
				if (firstLetterVariable(data[i]) == 1 && (letterVariables(data[i - 1]) == 0 || i == 0)) {
					while (letterVariables(data[i]) == 1 && i < abs((int)strlen(data))) {
						text[v] = ' ';
						v++;
						i++;
					}
				}
				if ((data[i - 1] == 'O' || data[i - 1] == 'H' || data[i - 1] == 'B') && data[i] == '_') {
					data[i] = '-';
				}
				if (data[i] != '1' && data[i] != '2' && data[i] != '3' && data[i] != '4' && data[i] != '5' && data[i] != '6' && data[i] != '7' && data[i] != '8' && data[i] != '9' && data[i] != '0' && data[i] != '.' && data[i] != '_' && data[i] != '!' && data[i] != 'A' && data[i] != 'B' && data[i] != 'C' && data[i] != 'D' && (data[i - 1] == 't' && data[i + 1] == '(') && data[i] != 'E' && data[i] != 'F' && data[i] != 'O' && data[i] != 'H' && data[i] != '(' && data[i] != ')') {
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
			if (abs((int)strlen(text)) > 0) {
				decision = dataVerifier(text, result1, result2, comment, verify);
				if (decision == 0) {
					if (comment == 1) {
						puts("\nYou entered invalid values.\n");
					}
					_delete(function, "function"); function = nullptr;
					_delete(variable, "variable"); variable = nullptr;
					_delete(expression, "expression"); expression = nullptr;
					_delete(text, "text"); text = nullptr;
					_delete(value, "value"); value = nullptr;
					_delete(saveVar, "saveVar"); saveVar = nullptr;
					_delete(numsysData, "numsysData"); numsysData = nullptr;
					_delete(varValidator, "varValidator");
					return decision;
				}
			}
		}
		for (i = 0; i < abs((int)strlen(data)); i++) {
			if (data[i] == '"' || data[i] == '%' || data[i] == '&' || data[i] == '"' || data[i] == '?' || data[i] == '@' || data[i] == '£' || data[i] == '§' || data[i] == '\'' || data[i] == '€' || data[i] == '¨' || data[i] == '´' || data[i] == '`' || data[i] == 'ª' || data[i] == 'º' || data[i] == '~' || data[i] == ',' || data[i] == ':' || data[i] == '«' || data[i] == '»') {
				decision = false;
				if (comment == 1) {
					puts("\nYou entered invalid characters.\n");

				}
				_delete(function, "function"); function = nullptr;
				_delete(variable, "variable"); variable = nullptr;
				_delete(expression, "expression"); expression = nullptr;
				_delete(text, "text"); text = nullptr;
				_delete(value, "value"); value = nullptr;
				_delete(saveVar, "saveVar"); saveVar = nullptr;
				_delete(numsysData, "numsysData"); numsysData = nullptr;
				_delete(varValidator, "varValidator");
				return decision;
			}
			if (data[i] == '{') {
				data[i] = '(';
			}
			if (data[i] == '}') {
				data[i] = ')';
			}
			if (data[i] == '(') {
				kl++;
				if (data[i + 1] == '+' || data[i + 1] == '-' || data[i + 1] == '*' || data[i + 1] == '/' || data[i + 1] == '^' || data[i + 1] == '!') {
					decision = false;
					if (comment == 1) {
						puts("\nYou entered an arithmetic symbol next to \"(\".\n");
					}
					_delete(function, "function"); function = nullptr;
					_delete(variable, "variable"); variable = nullptr;
					_delete(expression, "expression"); expression = nullptr;
					_delete(text, "text"); text = nullptr;
					_delete(value, "value"); value = nullptr;
					_delete(saveVar, "saveVar"); saveVar = nullptr;
					_delete(numsysData, "numsysData"); numsysData = nullptr;
					_delete(varValidator, "varValidator");
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
					_delete(function, "function"); function = nullptr;
					_delete(variable, "variable"); variable = nullptr;
					_delete(expression, "expression"); expression = nullptr;
					_delete(text, "text"); text = nullptr;
					_delete(value, "value"); value = nullptr;
					_delete(saveVar, "saveVar"); saveVar = nullptr;
					_delete(numsysData, "numsysData"); numsysData = nullptr;
					_delete(varValidator, "varValidator");
					return decision;
				}
			}
		}
		if (kr != kl) {
			decision = false;
			_delete(function, "function"); function = nullptr;
			_delete(variable, "variable"); variable = nullptr;
			_delete(expression, "expression"); expression = nullptr;
			_delete(text, "text"); text = nullptr;
			_delete(value, "value"); value = nullptr;
			_delete(saveVar, "saveVar"); saveVar = nullptr;
			_delete(numsysData, "numsysData"); numsysData = nullptr;
			_delete(varValidator, "varValidator");
			return decision;
		}
		for (i = 0; i < abs((int)strlen(data)); i++) {
			j = 0;
			if (data[i] == 'r' && data[i + 1] == 'e' && data[i + 2] == 's' && data[i + 3] != 't') {
				decision = true;
				i = i + 3;
			}
			if (data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4' || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9' || data[i] == '.' || data[i] == '_' || data[i] == '!' || data[i] == '+' || data[i] == '-' || data[i] == '/' || data[i] == '*' || data[i] == '^' || data[i] == 'e' || data[i] == 'p' && data[i + 1] == 'i' || data[i - 1] == 'p' && data[i] == 'i') {
				j = 0;
				while (data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4' || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9' || data[i] == '.' || data[i] == '_' || data[i] == '!' || data[i] == '+' || data[i] == '-' || data[i] == '/' || data[i] == '*' || data[i] == '^' || data[i] == 'e' || data[i] == 'p' && data[i + 1] == 'i' || data[i - 1] == 'p' && data[i] == 'i') {
					i++;
					decision = true;
					j++;
				}
			}
			if (data[i] == 'l' && data[i + 1] == 'i' && data[i + 2] == 'n' && data[i + 3] == 's' && data[i + 4] == 'n' && data[i + 5] == 'u' && data[i + 6] == 'm') {
				decision = true;
				i = i + 6;
			}
			if (data[i] == 'c' && data[i + 1] == 'o' && data[i + 2] == 'l' && data[i + 3] == 's' && data[i + 4] == 'n' && data[i + 5] == 'u' && data[i + 6] == 'm') {
				decision = true;
				i = i + 6;
			}
			if (data[i] == 'r' && data[i + 1] == 'e' && data[i + 2] == 's' && data[i + 3] != 't') {
				decision = true;
				i = i + 3;
			}
			if (data[i] == 'a' && data[i + 1] == 'b' && data[i + 2] == 's') {
				decision = true;
				i = i + 2;
			}
			if (data[i] == 'c' && data[i + 1] == 'a' && data[i + 2] == 'l' && data[i + 3] == 'c') {
				decision = true;
				i = i + 4;
			}
			if (data[i] == 's' && data[i + 1] == 't' && data[i + 2] == 'r' && data[i + 3] == 'l' && data[i + 4] == 'e' && data[i + 5] == 'n') {
				decision = true;
				i = i + 5;
			}
			if (data[i] == 'a' || data[i] == 's' && data[i - 1] != 'e' && data[i - 2] != 'r' || data[i] == 'c' || data[i] == 't' || data[i] == 'g' || data[i] == 'd' || data[i] == 'l' || data[i] == 'q' || data[i] == 'r' || data[i] == 'm') {
				decision = true;
				j = 0;
				while (data[i] != '(' && i < abs((int)strlen(data)) && i < abs((int)strlen(data))) {
					k = 0;
					if (data[i] == 'b' && data[i - 1] != 'c' && data[i - 1] != 'm') {
						function[j] = data[i];
						j++; i++;
						k++;
						l = 0;
						while ((data[i] == 'b' && data[i + 1] == '(') == false && i < abs((int)strlen(data))) {
							function[j] = data[i];
							expression[l] = function[j];
							j++; i++; l++;
						}
						expression[l] = '\0';
						int p = 0;
						if (abs((int)strlen(expression)) == 0) {
							decision = false;
							if (comment == 1) {
								puts("\nLogarithm base is null.\n");
							}
							if (decision == 0) {
								_delete(function, "function"); function = nullptr;
								_delete(variable, "variable"); variable = nullptr;
								_delete(expression, "expression"); expression = nullptr;
								_delete(text, "text"); text = nullptr;
								_delete(value, "value"); value = nullptr;
								_delete(saveVar, "saveVar"); saveVar = nullptr;
								_delete(numsysData, "numsysData"); numsysData = nullptr;
								_delete(varValidator, "varValidator");
								return decision;
							}
						}
						manageExpression(expression, result1, result2, verify);
						for (p = 0; p < abs((int)strlen(expressionF)); p++) {
							expression[p] = expressionF[p];
						}
						expression[p] = '\0';
						if (abs((int)strlen(expression)) > 0) {

							decision = dataVerifier(expression, result1, result2, comment, verify);
							if (decision == 0) {
								_delete(function, "function"); function = nullptr;
								_delete(variable, "variable"); variable = nullptr;
								_delete(expression, "expression"); expression = nullptr;
								_delete(text, "text"); text = nullptr;
								_delete(value, "value"); value = nullptr;
								_delete(saveVar, "saveVar"); saveVar = nullptr;
								_delete(numsysData, "numsysData"); numsysData = nullptr;
								_delete(varValidator, "varValidator");
								return decision;
							}
						}
						if (data[i] == 'b' && data[i - 1] != 'a' && data[i + 1] != 's') {
							k++;
						}
						if (k != 2) {
							decision = false;
							if (comment == 1) {
								puts("\nNumber of \"bs\" for advanced logarithmic function can't be different of 2.\n");
							}
							_delete(function, "function"); function = nullptr;
							_delete(variable, "variable"); variable = nullptr;
							_delete(expression, "expression"); expression = nullptr;
							_delete(text, "text"); text = nullptr;
							_delete(value, "value"); value = nullptr;
							_delete(saveVar, "saveVar"); saveVar = nullptr;
							_delete(numsysData, "numsysData"); numsysData = nullptr;
							_delete(varValidator, "varValidator");
							return decision;
						}
					}
					k = 0;
					if (data[i] == 'D') {
						function[j] = data[i];
						j++; i++;
						k++;
						l = 0;
						while ((data[i] == 'D' && data[i + 1] == '(') == false && i < abs((int)strlen(data))) {
							function[j] = data[i];
							expression[l] = function[j];
							j++; i++; l++;
							if ((data[i] == 'D' && data[i + 1] == '(') == false && data[i + 1] != '(') {
								function[j] = data[i];
								expression[l] = function[j];
								if (data[i] == 'D' && data[i + 1] == '(') {
									i--;
								}
								j++; i++; l++;
							}
						}
						expression[l] = '\0';
						if (abs((int)strlen(expression)) == 0) {
							decision = false;
							if (comment == 1) {
								puts("\nRoot degree is null.\n");
							}
							if (decision == 0) {
								_delete(function, "function"); function = nullptr;
								_delete(variable, "variable"); variable = nullptr;
								_delete(expression, "expression"); expression = nullptr;
								_delete(text, "text"); text = nullptr;
								_delete(value, "value"); value = nullptr;
								_delete(saveVar, "saveVar"); saveVar = nullptr;
								_delete(numsysData, "numsysData"); numsysData = nullptr;
								_delete(varValidator, "varValidator");
								return decision;
							}
						}
						manageExpression(expression, result1, result2, verify);
						for (p = 0; p < abs((int)strlen(expressionF)); p++) {
							expression[p] = expressionF[p];
						}
						expression[p] = '\0';
						if (abs((int)strlen(expression)) > 0) {

							decision = dataVerifier(expression, result1, result2, comment, verify);
							if (decision == 0) {
								_delete(function, "function"); function = nullptr;
								_delete(variable, "variable"); variable = nullptr;
								_delete(expression, "expression"); expression = nullptr;
								_delete(text, "text"); text = nullptr;
								_delete(value, "value"); value = nullptr;
								_delete(saveVar, "saveVar"); saveVar = nullptr;
								_delete(numsysData, "numsysData"); numsysData = nullptr;
								_delete(varValidator, "varValidator");
								return decision;
							}
						}
						if (data[i] == 'D') {
							k++;
						}
						if (k != 2) {
							decision = false;
							if (comment == 1) {
								puts("\nNumber of \"Ds\" for advanced root function can't be different of 2.\n");
							}
							_delete(function, "function"); function = nullptr;
							_delete(variable, "variable"); variable = nullptr;
							_delete(expression, "expression"); expression = nullptr;
							_delete(text, "text"); text = nullptr;
							_delete(value, "value"); value = nullptr;
							_delete(saveVar, "saveVar"); saveVar = nullptr;
							_delete(numsysData, "numsysData"); numsysData = nullptr;
							_delete(varValidator, "varValidator");
							return decision;
						}
					}
					function[j] = data[i];
					j++; i++;
				}
				function[j] = '\0';
				j = 0;
				if (verifyLetter(function[0]) == 1) {
					while ((verifyLetter(function[j]) == 1 || function[j] == '_') && j < abs((int)strlen(function))) {
						if (function[j] == 'b' && function[j - 1] != 'c') {
							j++;
							while ((function[j] == 'b' && function[j + 1] == '\0') == false && j < abs((int)strlen(function))) {
								j++;
							}
							if (function[j + 1] != '\0') {
								decision = false;
								_delete(function, "function"); function = nullptr;
								_delete(variable, "variable"); variable = nullptr;
								_delete(expression, "expression"); expression = nullptr;
								_delete(text, "text"); text = nullptr;
								_delete(value, "value"); value = nullptr;
								_delete(saveVar, "saveVar"); saveVar = nullptr;
								_delete(numsysData, "numsysData"); numsysData = nullptr;
								_delete(varValidator, "varValidator");
								return decision;
							}
						}
						if (function[j] == 'D') {
							j++;
							while ((function[j] == 'D' && function[j + 1] == '\0') == false && j < abs((int)strlen(function))) {
								j++;
							}
							if (function[j + 1] != '\0') {
								decision = false;
								_delete(function, "function"); function = nullptr;
								_delete(variable, "variable"); variable = nullptr;
								_delete(expression, "expression"); expression = nullptr;
								_delete(text, "text"); text = nullptr;
								_delete(value, "value"); value = nullptr;
								_delete(saveVar, "saveVar"); saveVar = nullptr;
								_delete(numsysData, "numsysData"); numsysData = nullptr;
								_delete(varValidator, "varValidator");
								return decision;
							}
						}
						j++;
					}
					if (j != abs((int)strlen(function))) {
						decision = false;
						_delete(function, "function"); function = nullptr;
						_delete(variable, "variable"); variable = nullptr;
						_delete(expression, "expression"); expression = nullptr;
						_delete(text, "text"); text = nullptr;
						_delete(value, "value"); value = nullptr;
						_delete(saveVar, "saveVar"); saveVar = nullptr;
						_delete(numsysData, "numsysData"); numsysData = nullptr;
						_delete(varValidator, "varValidator");
						return decision;
					}
				}
				resultI = 0.5;
				int ko = abs((int)strlen(function));
				function[ko] = '?'; function[ko + 1] = '\0';

				if (functionProcessor<T>(function, 0.2, 1.0, 0, "") != 0 || function[0] == 'r' && function[1] == 'e' && function[2] == 's' && function[3] == 't' && function[4] == '\0' || function[0] == 'q' && function[1] == 'u' && function[2] == 'o' && function[3] == 't' && function[4] == 'i' && function[5] == 'e' && function[6] == 'n' && function[7] == 't' && function[8] == '\0' || function[0] == 'a' && function[1] == 'c' && function[2] == 'o' && function[3] == 's' && function[4] == 'h' && function[5] == '\0' || function[0] == 'a' && function[1] == 'c' && function[2] == 'o' && function[3] == 't' && function[4] == 'a' && function[5] == 'n' && function[6] == 'h' && function[7] == '\0') {
					decision = true;
				}
				else {
					if (abs((int)strlen(function)) > 0) {
						if (comment == 1) {
							puts("\nInvalid function entered.\n");
						}
						decision = false;
					}
					_delete(function, "function"); function = nullptr;
					_delete(variable, "variable"); variable = nullptr;
					_delete(expression, "expression"); expression = nullptr;
					_delete(text, "text"); text = nullptr;
					_delete(value, "value"); value = nullptr;
					_delete(saveVar, "saveVar"); saveVar = nullptr;
					_delete(numsysData, "numsysData"); numsysData = nullptr;
					_delete(varValidator, "varValidator");
					return decision;
				}
			}
			if (data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4' || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9' || data[i] == '.' || data[i] == '_' || data[i] == '!' || data[i] == '+' || data[i] == '-' || data[i] == '/' || data[i] == '*' || data[i] == '^' || data[i] == 'e' || data[i] == 'p' && data[i + 1] == 'i' || data[i - 1] == 'p' && data[i] == 'i') {
				j = 0;
				while ((data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4' || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9' || data[i] == '.' || data[i] == '_' || data[i] == '!' || data[i] == '+' || data[i] == '-' || data[i] == '/' || data[i] == '*' || data[i] == '^' || data[i] == 'e' || data[i] == 'p' && data[i + 1] == 'i' || data[i - 1] == 'p' && data[i] == 'i') && i < abs((int)strlen(data))) {
					i++;
					decision = true;
					j++;
				}
			}
			j = 0;
			if (data[i] == 'r' && data[i + 1] == 'e' && data[i + 2] == 's' && data[i + 3] != 't') {
				decision = true;
				i = i + 3;
			}
			if (data[i] == 'B' || data[i] == 'O' || data[i] == 'H' || data[i] == 'Q' || data[i] == 'W' || data[i] == 'R' || data[i] == 'T' || data[i] == 'Y' || data[i] == 'U' || data[i] == 'I' || data[i] == 'P' || data[i] == 'A' || data[i] == 'S' || data[i] == 'D' || data[i] == 'F' || data[i] == 'G' || data[i] == 'J' || data[i] == 'K' || data[i] == 'L' || data[i] == 'Z' || data[i] == 'X' || data[i] == 'C' || data[i] == 'V' || data[i] == 'N' || data[i] == 'M' || data[i] == 'm' || data[i] == 'n' || data[i] == 'b' || data[i] == 'v' || data[i] == 'z' || data[i] == 'k' || data[i] == 'j' || data[i] == 'h' || data[i] == 'f' || data[i] == 'a' || data[i] == 'p' || data[i] == 'o' || data[i] == 'u' || data[i] == 'y' || data[i] == 'w') {
				j = 0;
				sprintf(variable, "");
				int pR = 0, pL = 0;
				while ((verifyLetter(data[i]) || pR < pL) && i < abs((int)strlen(data))) {
					variable[j] = data[i];
					if (data[i] == '[') {
						pL++;
					}
					if (data[i] == ']') {
						pR++;
					}
					j++;
					i++;
				}
				variable[j] = '\0';
				if (isContained("][", variable)) {
					if (isContained("[", variable)) {
						char* variableF = getDynamicCharArray("", "variableF");
						int p = strStart + 1, m = 0;
						if (p > 1) {
							if (p - 2 > 0 && verifyLetter(variable[p - 2])) {
								int k = p - 2;
								while (k > 0 && verifyLetter(variable[k])) {
									k--;
								}

								int v = 0;
								while (variable[k] != '[' && k < abs((int)strlen(variable))) {
									variableF[v] = variable[k];
									k++; v++;
								}
								variableF[v] = '\0';
								if ((variable[k] != '[' || countOccurrences("]", variable) % 2 == 1 || countOccurrences("[", variable) % 2 == 1) && comment == 1) {

									printf("\n==> Error: Be careful with the syntax of matrix indices. <==\n\n");
									decision = false;
									return decision;
								}
								checkMatrixIndex = true;
								processVariable<T>(variableF);

								checkMatrixIndex = false;
							}
						}
						char* firstInt = getDynamicCharArray("", "firstInt"); char* secondInt = getDynamicCharArray("", "secondInt");
						while (variable[p] != ']' && p < abs((int)strlen(variable))) {
							firstInt[m] = variable[p];
							m++; p++;
						}
						firstInt[m] = '\0';
						p += 2; m = 0;
						while (variable[p] != ']' && p < abs((int)strlen(variable))) {
							secondInt[m] = variable[p];
							m++; p++;
						}

						secondInt[m] = '\0';
						printf("\n2416firstInt-> %s\n", firstInt);
						printf("\n2417secondInt-> %s\n", secondInt);
						int indexIF = (int)solveMath<T>(firstInt);

						int	indexJF = (int)solveMath<T>(secondInt);

						if (comment == 1) {
							if (indexIF >= numVectorLines) {
								printf("\n==> Error: Wrong number for the lines of matrix index. Matrix \"%s\" maximum index: %d <==\n\n", variable, numVectorLines - 1);
								decision = false;
							}

							if (indexIF >= numVectorCols) {
								printf("\n==> Error: Wrong number for the columns of matrix index. Matrix \"%s\" maximum index: %d <==\n\n", variable, numVectorCols - 1);
								decision = false;
							}
							if ((variable[p] != ']' || countOccurrences("]", variable) % 2 == 1 || countOccurrences("[", variable) % 2 == 1) && comment == 1) {

								printf("\n==> Error: Be careful with the syntax of matrices indices. <==\n\n");
								decision = false;
							}
						}
						_delete(variableF, "variableF"); variableF = nullptr;
						_delete(firstInt, "firstInt"); firstInt = nullptr;
						_delete(secondInt, "secondInt"); secondInt = nullptr;
						_delete(function, "function"); function = nullptr;
						_delete(variable, "variable"); variable = nullptr;
						_delete(expression, "expression"); expression = nullptr;
						_delete(text, "text"); text = nullptr;
						_delete(value, "value"); value = nullptr;
						_delete(saveVar, "saveVar"); saveVar = nullptr;
						_delete(numsysData, "numsysData"); numsysData = nullptr;
						_delete(varValidator, "varValidator");
						return decision;

					}
				}
				else {
					if (isContained("[", variable)) {
						int p = strStart + 1, m = 0;
						char* variableF = getDynamicCharArray("", "variableF");
						if (p > 1) {
							if (p - 2 > 0 && verifyLetter(variable[p - 2])) {
								int k = p - 2;
								while (k > 0 && verifyLetter(variable[k])) {
									k--;
								}

								int v = 0;
								while (variable[k] != '[' && k < abs((int)strlen(variable))) {
									variableF[v] = variable[k];
									k++; v++;
								}
								variableF[v] = '\0';
								if ((variable[k] != '[' && variable[k] != '\0' || countOccurrences("]", variable) % 2 == 0 || countOccurrences("[", variable) % 2 == 0) && comment == 1) {

									printf("\n==> Error: Be careful with the syntax of vector index. <==\n\n");
									decision = false;
									return decision;
								}
								checkMatrixIndex = true;
								processVariable<T>(variableF);


								checkMatrixIndex = false;
							}
						}
						char* firstInt = getDynamicCharArray("", "firstInt"); char* secondInt = getDynamicCharArray("", "secondInt");
						while (variable[p] != ']' && p < abs((int)strlen(variable))) {
							firstInt[m] = variable[p];
							m++; p++;
						}
						firstInt[m] = '\0';
						lastCharIndex = p;
						printf("\n2492firstInt-> %s\n", firstInt);
						int indexIF = (int)solveMath<T>(firstInt);
						int indexJF = -1;
						if (indexIF >= numVectorCols && comment == 1) {
							printf("\n==> Error: Wrong number for the vector index. Maximum index: %d <==\n\n", numVectorCols - 1);
							decision = false;
						}
						if ((variable[p] != ']' || countOccurrences("]", variable) % 2 == 0 || countOccurrences("[", variable) % 2 == 0) && comment == 1) {

							printf("\n==> Error: Be careful with the syntax of vector index. <==\n\n");
							decision = false;
						}
						sprintf(variable, "%s", variableF);
						_delete(variableF, "variableF"); variableF = nullptr;
						_delete(firstInt, "firstInt"); firstInt = nullptr;
						_delete(secondInt, "secondInt"); secondInt = nullptr;
						_delete(function, "function"); function = nullptr;
						_delete(variable, "variable"); variable = nullptr;
						_delete(expression, "expression"); expression = nullptr;
						_delete(text, "text"); text = nullptr;
						_delete(value, "value"); value = nullptr;
						_delete(saveVar, "saveVar"); saveVar = nullptr;
						_delete(numsysData, "numsysData"); numsysData = nullptr;
						_delete(varValidator, "varValidator");
						return decision;

					}


				}
				if (initialProcessor(variable, result1) != 0) {
					decision = true;
					variable[j] = '\0';
				}
				else {
					variable[j] = '\0';
					int w = 0;
					while (letterVariables(variable[w]) == 1 && w < abs((int)strlen(variable))) {
						w++;
					}
					variable[w] = '\0';
					processVariable<T>(variable);
					if (validVar == 1) {
						_delete(expression, "expression"); expression = nullptr;
						_delete(text, "text"); text = nullptr;
						_delete(saveVar, "saveVar"); saveVar = nullptr;
						_delete(numsysData, "numsysData"); numsysData = nullptr;
						decision = true;
					}
				}
			}

		}

		_delete(function, "function"); function = nullptr;
		_delete(variable, "variable"); variable = nullptr;
		_delete(expression, "expression"); expression = nullptr;
		_delete(text, "text"); text = nullptr;
		_delete(value, "value"); value = nullptr;
		_delete(saveVar, "saveVar"); saveVar = nullptr;
		_delete(numsysData, "numsysData"); numsysData = nullptr;
		_delete(varValidator, "varValidator");
		return decision;
	}
	else {
		decision = false;
		printf("\nData for verification is null.\n");
		_delete(variable, "variable");
		return decision;
	}
}

bool atcFunctions(char* functionName) {
	int i = 0, j = 0, funcIndex = 0, g = 0, h = 0;
	bool isFunction = false;
	char* namesForFunctions = getDynamicCharArray("initialProcessor,functionProcessor", "namesForFunctions"); char* saveFunction = getDynamicCharArray("", "saveFunction");
	for (j = 0; j < abs((int)strlen(functionName)); j++) {
		saveFunction[j] = functionName[j];
	}
	saveFunction[j] = '\0';
	functionName[abs((int)strlen(functionName)) - 2] = '\0';
	for (j = 0; j < abs((int)strlen(functionName)); j++) {
		if (functionName[j] == '(') {
			functionName[j] = '\0';
			break;
		}
	}
	for (i = 0; i < abs((int)strlen(namesForFunctions)); i++) {
		j = 0;
		if (namesForFunctions[i] == functionName[j]) {
			j = 0; g = 0;
			while (i < abs((int)strlen(namesForFunctions)) && namesForFunctions[i] != ',') {
				if (namesForFunctions[i] == functionName[j]) {
					j++;
				}
				i++;
				g++;
			}
			if (g == j && j == abs((int)strlen(functionName))) {
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
		printf("\nThis is the function number %d in the list of atc functions.\n", funcIndex);
	}
	for (j = 0; j < abs((int)strlen(saveFunction)); j++) {
		functionName[j] = saveFunction[j];
	}
	functionName[j] = '\0';
	_delete(namesForFunctions, "namesForFunctions"); namesForFunctions = nullptr;
	_delete(saveFunction, "saveFunction"); saveFunction = nullptr;
	return isFunction;
}


void printCounter() {
	printf("\n%d\n", countDeleteorGetDynamic++);
}





template bool dataVerifier<double>(char*, double, double, int, int);
template bool dataVerifier<mp_float>(char*, mp_float, mp_float, int, int);
