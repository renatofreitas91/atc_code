

#include "stdafx.h"

template <typename T>

void ascendingOrder(char* values) {
	char* report = getDynamicCharArray("", "report");
	int i = 0, number_of_values = 1;
	for (i = 0; i < abs((int)strlen(values)); i++) {
		if (values[i] == '\\') {
			number_of_values++;
		}
	}
	int members = number_of_values;
	int allocatedValues = number_of_values + 1;
	i = 0;
	char* toValue = getDynamicCharArray("", "toValue");
	T* sValues = getDynamicArray<T>(allocatedValues);
	T* sValuesI = getDynamicArray<T>(allocatedValues);
	int p = 0;
	while (p < members) {
		int b = 0;
		while (values[i] != '\\'&&i < abs((int)strlen(values))) {
			toValue[b] = values[i];
			b++; i++;
		}
		toValue[b] = '\0';
		solveMath<T>(toValue);
		sValues[p] = precisionValueTo<T>(resultR);
		sValuesI[p] = precisionValueTo<T>(resultI);
		p++;
		sprintf(toValue, "");
		i++;
	}
	i = 0;
	T lowest = DBL_MAX, lowestI = DBL_MAX;
	T* orderR = getDynamicArray<T>(allocatedValues);
	T* orderI = getDynamicArray<T>(allocatedValues);
	int savePosition = -1;
	int j = 0;
	do
	{
		for (i = 0; i < number_of_values; i++)
		{
			if (lowest > sValues[i] && i != savePosition || savePosition == -1)
			{
				lowest = sValues[i];
				lowestI = sValuesI[i];
				savePosition = i;
			}
		}
		orderR[j] = lowest;
		orderI[j] = lowestI;
		lowest = DBL_MAX;
		lowestI = DBL_MAX;
		sValues[savePosition] = lowest;
		sValuesI[savePosition] = lowestI;
		j++;

	} while (j < number_of_values);
	savePosition = -1;
	j = 0;
	for (j = 0; j < number_of_values; j++) {
		sValues[j] = orderR[j];
		sValuesI[j] = orderI[j];
	}
	lowest = DBL_MAX;
	lowestI = DBL_MAX;
	j = 0;
	sprintf(report, "");

	for (int h = 0; h < number_of_values; h++) {
		int start = h;
		while (sValues[h] == sValues[h + 1]) {
			h++;
		}
		int end = ++h;
		do
		{
			for (i = start; i < end; i++)
			{
				if (lowestI > sValuesI[i] && i != savePosition || savePosition == -1)
				{
					lowest = sValues[i];
					lowestI = sValuesI[i];
					savePosition = i;
				}
			}
			convertComplex2Exponential(lowest, lowestI);
			if (j < end - 1 || end < number_of_values) {
				if (lowestI >= 0) {
					sprintf(report, "%s%s+%si, ", report, respR, respI);
				}
				else {
					sprintf(report, "%s%s%si, ", report, respR, respI);
				}
			}
			else {
				if (lowestI >= 0) {
					sprintf(report, "%s%s+%si ", report, respR, respI);
				}
				else {
					sprintf(report, "%s%s%si ", report, respR, respI);
				}
			}
			orderR[j] = lowest;
			orderI[j] = lowestI;
			j++;
			lowest = DBL_MAX;
			lowestI = DBL_MAX;
			sValues[savePosition] = lowest;
			sValuesI[savePosition] = lowestI;
			h = j - 1;
		} while (j < end);


	}
	puts(" ");
	puts(report);
	puts(" ");
	int option = -1;
	while (option != 0 && option != 1) {
		I_O = true;
		puts("\nExport result? (Yes -> 1 \\ No -> 0)");
		option = (int)getValue<T>();
	}
	if (option == 1) {
		saveToReport(report);
	}
	puts(" ");
	_delete(report, "report"); report = nullptr;
	_delete(toValue, "toValue"); toValue = nullptr;
	_delete(sValues, "sValues"); sValues = nullptr;
	_delete(sValuesI, "sValuesI"); sValuesI = nullptr;
	_delete(orderR, "orderR"); orderR = nullptr;
	_delete(orderI, "orderI"); orderI = nullptr;
}


template <typename T>

void descendingOrder(char* values) {
	char* report = getDynamicCharArray("", "report");
	int i = 0, number_of_values = 1;
	for (i = 0; i < abs((int)strlen(values)); i++) {
		if (values[i] == '\\') {
			number_of_values++;
		}
	}
	int members = number_of_values;
	int allocatedValues = number_of_values + 1;
	i = 0;
	char* toValue = getDynamicCharArray("", "toValue");
	T* sValues = getDynamicArray<T>(allocatedValues);
	T* sValuesI = getDynamicArray<T>(allocatedValues);
	int p = 0;
	while (p < members) {
		int b = 0;
		while (values[i] != '\\'&&i < abs((int)strlen(values))) {
			toValue[b] = values[i];
			b++; i++;
		}
		toValue[b] = '\0';
		solveMath<T>(toValue);
		sValues[p] = precisionValueTo<T>(resultR);
		sValuesI[p] = precisionValueTo<T>(resultI);
		p++;
		sprintf(toValue, "");
		i++;
	}
	i = 0;
	T biggest = -DBL_MAX, biggestI = -DBL_MAX;
	T* orderR = getDynamicArray<T>(allocatedValues);
	T* orderI = getDynamicArray<T>(allocatedValues);
	int savePosition = -1;
	int j = 0;
	do
	{
		for (i = 0; i < number_of_values; i++)
		{
			if (biggest < sValues[i] && i != savePosition || savePosition == -1)
			{
				biggest = sValues[i];
				biggestI = sValuesI[i];
				savePosition = i;
			}
		}
		orderR[j] = biggest;
		orderI[j] = biggestI;
		biggest = -DBL_MAX;
		biggestI = -DBL_MAX;
		sValues[savePosition] = biggest;
		sValuesI[savePosition] = biggestI;
		j++;

	} while (j < number_of_values);
	savePosition = -1;
	j = 0;
	for (j = 0; j < number_of_values; j++) {
		sValues[j] = orderR[j];
		sValuesI[j] = orderI[j];
	}
	biggest = -DBL_MAX;
	biggestI = -DBL_MAX;
	j = 0;
	sprintf(report, "");

	for (int h = 0; h < number_of_values; h++) {
		int start = h;
		while (sValues[h] == sValues[h + 1]) {
			h++;
		}
		int end = ++h;
		do
		{
			for (i = start; i < end; i++)
			{
				if (biggestI < sValuesI[i] && i != savePosition || savePosition == -1)
				{
					biggest = sValues[i];
					biggestI = sValuesI[i];
					savePosition = i;
				}
			}
			convertComplex2Exponential(biggest, biggestI);
			if (j < end - 1 || end < number_of_values) {
				if (biggestI >= 0) {
					sprintf(report, "%s%s+%si, ", report, respR, respI);
				}
				else {
					sprintf(report, "%s%s%si, ", report, respR, respI);
				}
			}
			else {
				if (biggestI >= 0) {
					sprintf(report, "%s%s+%si ", report, respR, respI);
				}
				else {
					sprintf(report, "%s%s%si ", report, respR, respI);
				}
			}
			orderR[j] = biggest;
			orderI[j] = biggestI;
			j++;
			biggest = -DBL_MAX;
			biggestI = -DBL_MAX;
			sValues[savePosition] = biggest;
			sValuesI[savePosition] = biggestI;
			h = j - 1;
		} while (j < end);


	}
	puts(" ");
	puts(report);
	puts(" ");
	int option = -1;
	while (option != 0 && option != 1) {
		I_O = true;
		puts("\nExport result? (Yes -> 1 \\ No -> 0)");
		option = (int)getValue<T>();
	}
	if (option == 1) {
		saveToReport(report);
	}
	puts(" ");
	_delete(report, "report"); report = nullptr;
	_delete(toValue, "toValue"); toValue = nullptr;
	_delete(sValues, "sValues"); sValues = nullptr;
	_delete(sValuesI, "sValuesI"); sValuesI = nullptr;
	_delete(orderR, "orderR"); orderR = nullptr;
	_delete(orderI, "orderI"); orderI = nullptr;
}

template <typename T>

void extremum(char* values, int findMax) {
	char* matrixExpr = getDynamicCharArray("", "matrixExpr");
	if (abs((int)strlen(values)) > 0) {
		sprintf(matrixExpr, "%s", values);
		sprintf(matrixValue, "");
		replaceTimes = 0;

		if (isContained("*", matrixExpr) || isContained(":", matrixExpr)) {
			if (isContained("*", matrixExpr)) {
				replace("*", "i\\", matrixExpr);
				sprintf(matrixExpr, "%s", expressionF);
			}
			if (isContained(":", matrixExpr)) {
				replace(":", "i\\", matrixExpr);
				sprintf(matrixExpr, "%s", expressionF);
			}
			if (isContained(" ", matrixExpr)) {
				replace(" ", "+", matrixExpr);
				sprintf(matrixExpr, "%s", expressionF);
			}
			if (isContained("-", matrixExpr)) {
				replace("-", "_", matrixExpr);
				sprintf(matrixExpr, "%s", expressionF);
			}
			if (!isContainedByIndex("i", matrixExpr, abs((int)strlen(matrixExpr)) - 1)) {
				sprintf(matrixExpr, "%si", matrixExpr);
			}
		}

		matrixMode = 1;
		char* report = getDynamicCharArray("", "report");
		char* toValue = getDynamicCharArray("", "toValue");

		int number_of_values = 1;
		for (int i = 0; i < abs((int)strlen(matrixExpr)); i++) {
			if (matrixExpr[i] == '\\') number_of_values++;
		}

		T* sValues = getDynamicArray<T>(number_of_values);
		T* sValuesI = getDynamicArray<T>(number_of_values);
		int i = 0, p = 0;

		while (p < number_of_values) {
			int b = 0;
			while (matrixExpr[i] != '\\' && i < abs((int)strlen(matrixExpr))) {
				toValue[b++] = matrixExpr[i++];
			}
			toValue[b] = '\0';
			solveMath<T>(toValue);
			sValues[p] = precisionValueTo<T>(resultR);
			sValuesI[p] = precisionValueTo<T>(resultI);
			sprintf(toValue, "");
			i++; p++;
		}

		T extremumR = findMax ? -DBL_MAX : DBL_MAX;
		T extremumI = findMax ? -DBL_MAX : DBL_MAX;
		T* orderR = getDynamicArray<T>(number_of_values);
		T* orderI = getDynamicArray<T>(number_of_values);
		int savePosition = -1, j = 0;

		do {
			for (i = 0; i < number_of_values; i++) {
				int condition = (findMax ? (sValues[i] > extremumR) : (sValues[i] < extremumR));
				if ((condition && i != savePosition) || savePosition == -1) {
					extremumR = sValues[i];
					extremumI = sValuesI[i];
					savePosition = i;
				}
			}
			orderR[j] = extremumR;
			orderI[j] = extremumI;
			sValues[savePosition] = findMax ? -DBL_MAX : DBL_MAX;
			sValuesI[savePosition] = findMax ? -DBL_MAX : DBL_MAX;
			extremumR = findMax ? -DBL_MAX : DBL_MAX;
			extremumI = findMax ? -DBL_MAX : DBL_MAX;
			j++;
		} while (j < number_of_values);

		for (j = 0; j < number_of_values; j++) {
			sValues[j] = orderR[j];
			sValuesI[j] = orderI[j];
		}

		j = 0;
		extremumR = findMax ? -DBL_MAX : DBL_MAX;
		extremumI = findMax ? -DBL_MAX : DBL_MAX;
		savePosition = -1;

		for (int h = 0; h < number_of_values; h++) {
			int start = h;
			while (h + 1 < number_of_values && sValues[h] == sValues[h + 1]) h++;
			int end = h + 1;

			do {
				for (i = start; i < end; i++) {
					int condition = (findMax ? (sValuesI[i] > extremumI) : (sValuesI[i] < extremumI));
					if ((condition && i != savePosition) || savePosition == -1) {
						extremumR = sValues[i];
						extremumI = sValuesI[i];
						savePosition = i;
					}
				}
				orderR[j] = extremumR;
				orderI[j] = extremumI;
				sValues[savePosition] = findMax ? -DBL_MAX : DBL_MAX;
				sValuesI[savePosition] = findMax ? -DBL_MAX : DBL_MAX;
				extremumR = findMax ? -DBL_MAX : DBL_MAX;
				extremumI = findMax ? -DBL_MAX : DBL_MAX;
				j++;
				h = j - 1;
			} while (j < end);
		}

		resultR = orderR[0];
		resultI = orderI[0];

		_delete(report, "report"); report = nullptr;
		_delete(toValue, "toValue"); toValue = nullptr;
		_delete(sValues, "sValues"); sValues = nullptr;
		_delete(sValuesI, "sValuesI"); sValuesI = nullptr;
		_delete(orderR, "orderR"); orderR = nullptr;
		_delete(orderI, "orderI"); orderI = nullptr;
	}
	_delete(matrixExpr, "matrixExpr"); matrixExpr = nullptr;
}
template <typename T>
void maximum(char* values) {
	extremum<T>(values, 1);
}
template <typename T>
void minimum(char* values) {
	extremum<T>(values, 0);
}
template <typename T>
void average(char* values) {
	char* matrixExpr = getDynamicCharArray("", "matrixExpr");
	if (abs((int)strlen(values)) > 0) {
		sprintf(matrixExpr, "%s", values);
		sprintf(matrixValue, "");
		replaceTimes = 0;
		if (isContained("*", matrixExpr)) {
			replace("*", "i\\", matrixExpr);
			sprintf(matrixExpr, "%s", expressionF);
		}
		if (isContained(":", matrixExpr)) {
			replace(":", "i\\", matrixExpr);
			sprintf(matrixExpr, "%s", expressionF);
		}
		if (isContained(" ", matrixExpr)) {
			replace(" ", "+", matrixExpr);
			sprintf(matrixExpr, "%s", expressionF);
		}
		if (isContained("-", matrixExpr)) {
			replace("-", "_", matrixExpr);
			sprintf(matrixExpr, "%s", expressionF);
		}
		if (!isContainedByIndex("i", matrixExpr, abs((int)strlen(matrixExpr)) - 1)) {
			sprintf(matrixExpr, "%si", matrixExpr);
		}
		matrixMode = 1;
		char* report = getDynamicCharArray("", "report");
		int i = 0, number_of_values = 1;
		for (i = 0; i < abs((int)strlen(matrixExpr)); i++) {
			if (matrixExpr[i] == '\\') {
				number_of_values++;
			}
		}
		int members = number_of_values;
		i = 0;
		char* toValue = getDynamicCharArray("", "toValue");
		T* sValues = getDynamicArray<T>(number_of_values);
		T* sValuesI = getDynamicArray<T>(number_of_values);
		int p = 0;
		while (p < members) {
			int b = 0;
			while (matrixExpr[i] != '\\'&&i < abs((int)strlen(matrixExpr))) {
				toValue[b] = matrixExpr[i];
				b++; i++;
			}
			toValue[b] = '\0';
			solveMath<T>(toValue);
			sValues[p] = precisionValueTo<T>(resultR);
			sValuesI[p] = precisionValueTo<T>(resultI);
			p++;
			sprintf(toValue, "");
			i++;
		}
		int j = 0;
		T sumR = 0, sumI = 0;
		for (i = 0; i < number_of_values; i++)
		{
			sum<T>(sumR, sumI, sValues[i], sValuesI[i]);
			sumR = precisionValueTo<T>(resultR); sumI = precisionValueTo<T>(resultI);
		}
		division<T>(sumR, sumI, (T)number_of_values, 0.0);
		_delete(report, "report"); report = nullptr;
		_delete(toValue, "toValue"); toValue = nullptr;
		_delete(sValues, "sValues"); sValues = nullptr;
		_delete(sValuesI, "sValuesI"); sValuesI = nullptr;
	}
	_delete(matrixExpr, "matrixExpr"); matrixExpr = nullptr;

}

template <typename T>
void asciiOrder() {
	int continu = 1;
	do {
		puts("\nSeperate your expressions by \"\\\" and in the final press \"Enter\"\n");
		char* expressions = getDynamicCharArray("", "expressions");
		char** expressionList, ** expressionListS;
		expressionList = new char*[DIMTWOD];

		for (int i = 0; i < DIMTWOD; ++i) {
			expressionList[i] = getDynamicCharArray("", "expressionList[i]");
		}
		expressionListS = new char*[DIMTWOD];

		for (int i = 0; i < DIMTWOD; ++i) {
			expressionListS[i] = getDynamicCharArray("", "expressionListS[i]");
		}
		T* expressionEquivalent = getDynamicArray<T>(DIMDOUBLE);
		gets_s(expressions, DIM);
		int i = 0, j = 0, maximum = 0, z = 0;
		while (i < abs((int)strlen(expressions))) {
			while (expressions[i] != '\\'&&i < abs((int)strlen(expressions))) {
				expressionList[z][j] = expressions[i];
				i++;
				j++;
			}
			expressionList[z][j] = '\0';
			sprintf(expressionListS[z], "%s", expressionList[z]);
			if (maximum < j) {
				maximum = j;
			}
			j = 0;
			i++;
			z++;
		}
		i = 0;
		replaceTimes = 1;
		int found = 0;
		char* letters = getDynamicCharArray("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", "letters");
		int length = (int)abs((int)strlen(letters));
		srand((int)NULL);
		while (i < z) {
			int r = rand() % length;
			char* toFind = getDynamicCharArrayFixedLenght("", 3);
			char* toReplace = getDynamicCharArrayFixedLenght("", 2);
			toFind[0] = expressionListS[i][0];
			toFind[1] = expressionListS[i][1];
			toFind[2] = '\0';
			toReplace[0] = expressionListS[i][0];
			toReplace[1] = '\0';
			found = 0;
			int len = (int)strlen(expressionListS[i]);
			j = i + 1;
			while (j < z) {
				if (isContained(toFind, expressionListS[j]) && strStart == 0 && len == (int)strlen(expressionListS[j]) && strEnd != (int)strlen(expressionListS[j])) {
					found = 1;
					replace(toFind, toReplace, expressionListS[j]);
					sprintf(expressionListS[j], "%s", expressionF);
				}
				j++;
			}
			if (found == 0) {
				i++;
			}
			else {
				replace(toFind, toReplace, expressionListS[i]);
				sprintf(expressionListS[i], "%s", expressionF);
			}
			_delete(toFind, "toFind");
			toFind = nullptr;
			_delete(toReplace, "toReplace");
			toReplace = nullptr;
		}
		maximum = 0;
		i = 0;
		while (i < z) {
			if (abs((int)strlen(expressionListS[i]) > maximum)) {
				maximum = abs((int)strlen(expressionListS[i]));
			}
			i++;
		}
		i = 0, j = 0;
		int r = 0;
		while (i < z) {
			int y = (int)strlen(expressionListS[i]);
			while (y < maximum) {
				r = rand() % length;
				expressionListS[i][y] = letters[r];
				y++;
			}
			i++;
		}
		i = 0, j = 0;
		while (i < z) {
			j = 0;
			T Summatory = 0;
			while (j < abs((int)strlen(expressionListS[i]))) {
				Summatory = Summatory + (expressionListS[i][j])*pot<T>(summatorial((maximum - j) + 1), 20.0, 1);
				j++;
			}
			while (j < maximum) {
				Summatory = Summatory + abs(maximum - (int)strlen(expressionListS[i]) + 1)*pot<T>(summatorial((maximum - j) + 1), 20.0, 1);
				j++;
			}
			expressionEquivalent[i] = Summatory;
			i++;
		}
		i = 0;
		T lowest = DBL_MAX;
		int savePosition = -1;
		j = 0;
		char* report = getDynamicCharArray("", "report");
		do
		{
			for (i = 0; i < z; i++)
			{
				if (lowest > expressionEquivalent[i] && i != savePosition || savePosition == -1)
				{
					lowest = expressionEquivalent[i];
					savePosition = i;
				}
			}
			if (j < z - 1) {
				sprintf(report, "%s%s\n", report, expressionList[savePosition]);
			}
			else {
				sprintf(report, "%s%s", report, expressionList[savePosition]);
			}
			j++;
			lowest = DBL_MAX;
			expressionEquivalent[savePosition] = lowest;
		} while (j < z);
		puts(" ");
		puts(report);
		puts(" ");
		int option = -1;
		while (option != 0 && option != 1) {
			I_O = true;
			puts("\nExport result? (Yes -> 1 \\ No -> 0)");
			option = (int)getValue<T>();
		}
		if (option == 1) {
			saveToReport(report);
		}
		puts(" ");
		continu = -1;
		while (continu != 0 && continu != 1) {
			I_O = true;
			puts("\nContinue? (Yes -> 1 \\ No -> 0)");
			continu = (int)getValue<T>();
		}

		_Delete(expressionList, DIMTWOD, dime, "expressionList[i]");


		_Delete(expressionListS, DIMTWOD, dime, "expressionListS[i]");
		_delete(expressions, "expressions"); expressions = nullptr;
		if (letters != nullptr) {
			_delete(letters, "letters"); letters = nullptr;
		}
		_delete(report, "report"); report = nullptr;
		_delete(expressionEquivalent, "expressionEquivalent"); expressionEquivalent = nullptr;
	} while (continu == 1);
}

template void ascendingOrder<double>(char*);
template void descendingOrder<double>(char*);
template <typename T>
void inverseAsciiOrder() {
	int continu = 1;
	do {
		puts("\nSeperate your expressions by \"\\\" and in the final press \"Enter\"\n");
		char* expressions = getDynamicCharArray("", "expressions");
		char** expressionList, ** expressionListS;

		expressionList = new char*[DIMTWOD];

		for (int i = 0; i < DIMTWOD; ++i) {
			expressionList[i] = getDynamicCharArray("", "expressionList[i]");
		}
		expressionListS = new char*[DIMTWOD];

		for (int i = 0; i < DIMTWOD; ++i) {
			expressionListS[i] = getDynamicCharArray("", "expressionListS[i]");
		}
		T* expressionEquivalent = getDynamicArray<T>(DIMDOUBLE);
		gets_s(expressions, DIM);
		int i = 0, j = 0, maximum = 0, z = 0;
		while (i < abs((int)strlen(expressions))) {
			while (expressions[i] != '\\'&&i < abs((int)strlen(expressions))) {
				expressionList[z][j] = expressions[i];
				i++;
				j++;
			}
			expressionList[z][j] = '\0';
			sprintf(expressionListS[z], "%s", expressionList[z]);
			if (maximum < j) {
				maximum = j;
			}
			j = 0;
			i++;
			z++;
		}
		i = 0;
		replaceTimes = 1;
		int found = 0;
		char* letters = getDynamicCharArray("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm", "letters");
		int length = (int)abs((int)strlen(letters));
		srand((int)NULL);
		while (i < z) {
			int r = rand() % length;
			char* toFind = getDynamicCharArrayFixedLenght("", 3);
			char* toReplace = getDynamicCharArrayFixedLenght("", 2);
			toFind[0] = expressionListS[i][0];
			toFind[1] = expressionListS[i][1];
			toFind[2] = '\0';
			toReplace[0] = expressionListS[i][0];
			toReplace[1] = '\0';
			found = 0;
			int len = (int)strlen(expressionListS[i]);
			j = i + 1;
			while (j < z) {
				if (isContained(toFind, expressionListS[j]) && strStart == 0 && len == (int)strlen(expressionListS[j]) && strEnd != (int)strlen(expressionListS[j])) {
					found = 1;
					replace(toFind, toReplace, expressionListS[j]);
					sprintf(expressionListS[j], "%s", expressionF);
				}
				j++;
			}
			if (found == 0) {
				i++;
			}
			else {
				replace(toFind, toReplace, expressionListS[i]);
				sprintf(expressionListS[i], "%s", expressionF);
			}
			_delete(toFind, "toFind");
			toFind = nullptr;
			_delete(toReplace, "toReplace");
			toReplace = nullptr;
		}
		maximum = 0;
		i = 0;
		while (i < z) {
			if (abs((int)strlen(expressionListS[i]) > maximum)) {
				maximum = abs((int)strlen(expressionListS[i]));
			}
			i++;
		}
		i = 0, j = 0;
		int r = 0;
		while (i < z) {
			int y = (int)strlen(expressionListS[i]);
			while (y < maximum) {
				r = rand() % length;
				expressionListS[i][y] = letters[r];
				y++;
			}
			i++;
		}
		i = 0, j = 0;
		while (i < z) {
			j = 0;
			T Summatory = 0;
			while (j < abs((int)strlen(expressionListS[i]))) {
				Summatory = Summatory + (static_cast<unsigned char>(expressionListS[i][j]))*pot<T>(summatorial((maximum - j) + 1), 20.0, 1);
				j++;
			}
			while (j < maximum) {
				Summatory = Summatory + abs(maximum - (int)strlen(expressionListS[i]) + 1)*pot<T>(summatorial((maximum - j) + 1), 20.0, 1);
				j++;
			}
			expressionEquivalent[i] = Summatory;
			i++;
		}
		i = 0;
		T biggest = -DBL_MAX;
		int savePosition = -1;
		j = 0;
		char* report = getDynamicCharArray("", "report");
		do
		{
			for (i = 0; i < z; i++)
			{
				if (biggest < expressionEquivalent[i] && i != savePosition || savePosition == -1)
				{
					biggest = expressionEquivalent[i];
					savePosition = i;
				}
			}
			if (j < z - 1) {
				sprintf(report, "%s%s\n", report, expressionList[savePosition]);
			}
			else {
				sprintf(report, "%s%s", report, expressionList[savePosition]);
			}
			j++;
			biggest = -DBL_MAX;
			expressionEquivalent[savePosition] = biggest;
		}

		while (j < z);
		puts(" ");
		puts(report);
		puts(" ");
		int option = -1;
		while (option != 0 && option != 1) {
			I_O = true;
			puts("\nExport result? (Yes -> 1 \\ No -> 0)");
			option = (int)getValue<T>();
		}
		if (option == 1) {
			saveToReport(report);
		}
		puts(" ");
		continu = -1;
		while (continu != 0 && continu != 1) {
			I_O = true;
			puts("\nContinue? (Yes -> 1 \\ No -> 0)");
			continu = (int)getValue<T>();
		}

		_Delete(expressionList, DIMTWOD, dime, "expressionList[i]");


		_Delete(expressionListS, DIMTWOD, dime, "expressionListS[i]");
		expressionListS = nullptr;
		_delete(expressions, "expressions"); expressions = nullptr;
		_delete(letters, "letters"); letters = nullptr;
		_delete(report, "report"); report = nullptr;
		_delete(expressionEquivalent, "expressionEquivalent"); expressionEquivalent = nullptr;
	} while (continu == 1);
}




void average(char* values) { average<double>(values); }
void maximum(char* values) { maximum<double>(values); }
void minimum(char* values) { minimum<double>(values); }
void asciiOrder() { asciiOrder<double>(); }
void inverseAsciiOrder() { inverseAsciiOrder<double>(); }
template void average<double>(char*);
template void maximum<double>(char*);
template void minimum<double>(char*);
template void asciiOrder<double>();
template void inverseAsciiOrder<double>();
