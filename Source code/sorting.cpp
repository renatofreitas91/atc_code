

#include "stdafx.h"
void ascendingOrder(char values[DIM]) {
	char report[DIM] = "";
	int i = 0, number_of_values = 1;
	for (i = 0; values[i] != '\0'; i++) {
		if (values[i] == '\\') {
			number_of_values++;
		}
	}
	int members = number_of_values;
	i = 0;
	char toValue[DIM] = "";
	double sValues[DIM], sValuesI[DIM];
	int p = 0;
	while (p < members) {
		int b = 0;
		while (values[i] != '\\'&&values[i] != '\0') {
			toValue[b] = values[i];
			b++; i++;
		}
		toValue[b] = '\0';
		calcNow(toValue, 0, 0);
		sValues[p] = resultR;
		sValuesI[p] = resultI;
		p++;
		sprintf(toValue, "");
		i++;
	}
	i = 0;
	double lowest = DBL_MAX, lowestI = DBL_MAX;
	double orderR[DIM], orderI[DIM];
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

			if (j < end - 1 || end < number_of_values) {
				if (lowestI >= 0) {
					sprintf(report, "%s%G+%Gi, ", report, lowest, lowestI);
				}
				else {
					sprintf(report, "%s%G%Gi, ", report, lowest, lowestI);
				}
			}
			else {
				if (lowestI >= 0) {
					sprintf(report, "%s%G+%Gi, ", report, lowest, lowestI);
				}
				else {
					sprintf(report, "%s%G%Gi, ", report, lowest, lowestI);
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
		option = (int)getValue();
	}
	if (option == 1) {
		saveToReport(report);
	}
	puts(" ");
}

void descendingOrder(char values[DIM]) {
	char report[DIM] = "";
	int i = 0, number_of_values = 1;
	for (i = 0; values[i] != '\0'; i++) {
		if (values[i] == '\\') {
			number_of_values++;
		}
	}
	int members = number_of_values;
	i = 0;
	char toValue[DIM] = "";
	double sValues[DIM], sValuesI[DIM];
	int p = 0;
	while (p < members) {
		int b = 0;
		while (values[i] != '\\'&&values[i] != '\0') {
			toValue[b] = values[i];
			b++; i++;
		}
		toValue[b] = '\0';
		calcNow(toValue, 0, 0);
		sValues[p] = resultR;
		sValuesI[p] = resultI;
		p++;
		sprintf(toValue, "");
		i++;
	}
	i = 0;
	double biggest = -DBL_MAX, biggestI = -DBL_MAX;
	double orderR[DIM], orderI[DIM];
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
			if (j < end - 1 || end < number_of_values) {
				if (biggestI >= 0) {
					sprintf(report, "%s%G+%Gi, ", report, biggest, biggestI);
				}
				else {
					sprintf(report, "%s%G%Gi, ", report, biggest, biggestI);
				}
			}
			else {
				if (biggestI >= 0) {
					sprintf(report, "%s%G+%Gi, ", report, biggest, biggestI);
				}
				else {
					sprintf(report, "%s%G%Gi, ", report, biggest, biggestI);
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
		option = (int)getValue();
	}
	if (option == 1) {
		saveToReport(report);
	}
	puts(" ");
}


void maximum(char values[DIM]) {
	char matrixExpr[DIM] = "";
	if (strlen(values) > 0) {
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
		if (isContained(" ", values)) {
			sprintf(matrixExpr, "%si", matrixExpr);
		}
		sprintf(values, "%s", matrixExpr);
		matrixMode = 1;
		char report[DIM] = "";
		int i = 0, number_of_values = 1;
		for (i = 0; values[i] != '\0'; i++) {
			if (values[i] == '\\') {
				number_of_values++;
			}
		}
		int members = number_of_values;
		i = 0;
		char toValue[DIM] = "";
		double sValues[DIM], sValuesI[DIM];
		int p = 0;
		while (p < members) {
			int b = 0;
			while (values[i] != '\\'&&values[i] != '\0') {
				toValue[b] = values[i];
				b++; i++;
			}
			toValue[b] = '\0';
			calcNow(toValue, 0, 0);
			sValues[p] = resultR;
			sValuesI[p] = resultI;
			p++;
			sprintf(toValue, "");
			i++;
		}
		i = 0;
		double biggest = -DBL_MAX, biggestI = -DBL_MAX;
		double orderR[DIM], orderI[DIM];
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
		resultR = orderR[0];
		resultI = orderI[0];
	}
}

void minimum(char values[DIM]) {
	char matrixExpr[DIM] = "";
	if (strlen(values) > 0) {
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
		if (isContained(" ", values)) {
			sprintf(matrixExpr, "%si", matrixExpr);
		}
		sprintf(matrixValue, "not_checking");
		matrixMode = 1;


		if (strlen(matrixExpr) > 0) {
			sprintf(values, "%s", matrixExpr);
		}
		char report[DIM] = "";
		int i = 0, number_of_values = 1;
		for (i = 0; values[i] != '\0'; i++) {
			if (values[i] == '\\') {
				number_of_values++;
			}
		}
		int members = number_of_values;
		i = 0;
		char toValue[DIM] = "";
		double sValues[DIM], sValuesI[DIM];
		int p = 0;
		while (p < members) {
			int b = 0;
			while (values[i] != '\\'&&values[i] != '\0') {
				toValue[b] = values[i];
				b++; i++;
			}
			toValue[b] = '\0';
			calcNow(toValue, 0, 0);
			sValues[p] = resultR;
			sValuesI[p] = resultI;
			p++;
			sprintf(toValue, "");
			i++;
		}
		i = 0;
		double lowest = DBL_MAX, lowestI = DBL_MAX;
		double orderR[DIM], orderI[DIM];
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
		resultR = orderR[0];
		resultI = orderI[0];
	}
}

void average(char values[DIM]) {
	char matrixExpr[DIM] = "";
	if (strlen(values) > 0) {
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
		if (isContained(" ", values)) {
			sprintf(matrixExpr, "%si", matrixExpr);
		}
		sprintf(values, "%s", matrixExpr);
		matrixMode = 1;
		char report[DIM] = "";
		int i = 0, number_of_values = 1;
		for (i = 0; values[i] != '\0'; i++) {
			if (values[i] == '\\') {
				number_of_values++;
			}
		}
		int members = number_of_values;
		i = 0;
		char toValue[DIM] = "";
		double sValues[DIM], sValuesI[DIM];
		int p = 0;
		while (p < members) {
			int b = 0;
			while (values[i] != '\\'&&values[i] != '\0') {
				toValue[b] = values[i];
				b++; i++;
			}
			toValue[b] = '\0';
			calcNow(toValue, 0, 0);
			sValues[p] = resultR;
			sValuesI[p] = resultI;
			p++;
			sprintf(toValue, "");
			i++;
		}
		int j = 0;
		double sumR = 0, sumI = 0;
		for (i = 0; i < number_of_values; i++)
		{
			sum(sumR, sumI, sValues[i], sValuesI[i]);
			sumR = resultR; sumI = resultI;
		}
		division(sumR, sumI, (double)number_of_values, 0.0);
	}
}


void asciiOrder() {
	int continu = 1;
	do {
		puts("\nSeperate your expressions by \"\\\" and in the final press \"Enter\"\n");
		char expressions[DIM] = "";
		char expressionList[dim][dim], expressionListS[dim][dim];
		double expressionEquivalent[dim];
		gets_s(expressions);
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
		char letters[DIM] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
		int length = (int)strlen(letters);
		srand((int)NULL);
		while (i < z) {
			int r = rand() % length;
			char toFind[3] = { expressionListS[i][0],expressionListS[i][1],'\0' };
			char toReplace[2] = { expressionListS[i][0],'\0' };
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
			double Summatory = 0;
			while (j < abs((int)strlen(expressionListS[i]))) {
				Summatory = Summatory + (static_cast<unsigned char>(expressionListS[i][j]))*pow(summatorial((maximum - j) + 1), 20.0);
				j++;
			}
			while (j < maximum) {
				Summatory = Summatory + abs(maximum - (int)strlen(expressionListS[i]) + 1)*pow(summatorial((maximum - j) + 1), 20.0);
				j++;
			}
			expressionEquivalent[i] = Summatory;
			i++;
		}
		i = 0;
		double lowest = DBL_MAX;
		int savePosition = -1;
		j = 0;
		char report[DIM] = "";
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
			option = (int)getValue();
		}
		if (option == 1) {
			saveToReport(report);
		}
		puts(" ");
		continu = -1;
		while (continu != 0 && continu != 1) {
			I_O = true;
			puts("\nContinue? (Yes -> 1 \\ No -> 0)");
			continu = (int)getValue();
		}
	} while (continu == 1);
}

void inverseAsciiOrder() {
	int continu = 1;
	do {
		puts("\nSeperate your expressions by \"\\\" and in the final press \"Enter\"\n");
		char expressions[DIM] = "";
		char expressionList[dim][dim], expressionListS[dim][dim];
		double expressionEquivalent[dim];
		gets_s(expressions);
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
		char letters[DIM] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
		int length = (int)strlen(letters);
		srand((int)NULL);
		while (i < z) {
			int r = rand() % length;
			char toFind[3] = { expressionListS[i][0],expressionListS[i][1],'\0' };
			char toReplace[2] = { expressionListS[i][0],'\0' };
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
			double Summatory = 0;
			while (j < abs((int)strlen(expressionListS[i]))) {
				Summatory = Summatory + (static_cast<unsigned char>(expressionListS[i][j]))*pow(summatorial((maximum - j) + 1), 20.0);
				j++;
			}
			while (j < maximum) {
				Summatory = Summatory + abs(maximum - (int)strlen(expressionListS[i]) + 1)*pow(summatorial((maximum - j) + 1), 20.0);
				j++;
			}
			expressionEquivalent[i] = Summatory;
			i++;
		}
		i = 0;
		double biggest = -DBL_MAX;
		int savePosition = -1;
		j = 0;
		char report[DIM] = "";
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
			option = (int)getValue();
		}
		if (option == 1) {
			saveToReport(report);
		}
		puts(" ");
		continu = -1;
		while (continu != 0 && continu != 1) {
			I_O = true;
			puts("\nContinue? (Yes -> 1 \\ No -> 0)");
			continu = (int)getValue();
		}
	} while (continu == 1);
}

