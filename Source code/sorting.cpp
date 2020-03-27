

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
	double sValues[DIM];
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
		p++;
		sprintf(toValue, "");
		i++;
	}
	i = 0;
	double lowest = DBL_MAX;
	int savePosition = -1;
	int j = 0;
	do
	{
		for (i = 0; i < number_of_values; i++)
		{
			if (lowest > sValues[i] && i != savePosition || savePosition == -1)
			{
				lowest = sValues[i];
				savePosition = i;
			}
		}
		if (j < number_of_values - 1) {
			sprintf(report, "%s%G, ", report, lowest);
		}
		else {
			sprintf(report, "%s%G", report, lowest);
		}
		j++;
		lowest = DBL_MAX;
		sValues[savePosition] = lowest;
	} while (j < number_of_values);
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
	double sValues[DIM];
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
		p++;
		sprintf(toValue, "");
		i++;
	}
	i = 0;

	int k = 0;

	double biggest = -DBL_MAX;
	int savePosition = -1;
	int j = 0;
	do
	{
		for (i = 0; i < number_of_values; i++)
		{
			if (biggest < sValues[i] && i != savePosition || savePosition == -1)
			{
				biggest = sValues[i];
				savePosition = i;
			}
		}
		if (j < number_of_values - 1) {
			sprintf(report, "%s%G, ", report, biggest);
		}
		else {
			sprintf(report, "%s%G", report, biggest);
		}
		j++;
		biggest = -DBL_MAX;
		sValues[savePosition] = biggest;
	}

	while (j < number_of_values);
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