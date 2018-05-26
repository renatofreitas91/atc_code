#include "stdafx.h"

void designGraph(char function[DIM]) {
	if (isContained("x", function)) {
		replace("x", "res", function);
		sprintf(function, expressionF);
	}
	FILE *graph = NULL;
	char toOpen[DIM] = "";
	double Xmin, Xmax, Xscale, Ymin, Ymax, Yscale;
	sprintf(toOpen, "%s\\graph.txt", atcPath);
	graph = fopen(toOpen, "r");
	if (graph == NULL) {
		Xmin = -10;
		Xmax = 10;
		Xscale = 1;
		Ymin = -10;
		Ymax = 10;
		Yscale = 1;
	}
	else {
		char data[DIM] = "";
		int i = 0;
		for (i = 0; (data[i] = fgetc(graph)) != EOF; i++);
		data[i] = '\0';
		fclose(graph);
		i = 0; int j = 0;
		char value[20] = "";
		while (data[i] != '\n'&&data[i] != '\0') {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		Xmin = calcNow(value, 0, 0);
		i++;
		j = 0;
		while (data[i] != '\n'&&data[i] != '\0') {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		Xmax = calcNow(value, 0, 0);
		i++;
		j = 0;
		while (data[i] != '\n'&&data[i] != '\0') {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		Xscale = calcNow(value, 0, 0);
		i++;
		j = 0;
		while (data[i] != '\n'&&data[i] != '\0') {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		Ymin = calcNow(value, 0, 0);
		i++;
		j = 0;
		while (data[i] != '\n'&&data[i] != '\0') {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		Ymax = calcNow(value, 0, 0);
		i++;
		j = 0;
		while (data[i] != '\n'&&data[i] != '\0') {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		Yscale = calcNow(value, 0, 0);
	}
	double xDim = Xmax - Xmin;
	double valuePerxDim = 120 / xDim;
	double yDim = Ymax - Ymin;
	double valuePeryDim = 60 / yDim;
	double valueXPerXscale = Xscale * valuePerxDim;
	double valueYPerYscale = Yscale * valuePeryDim;
	solverRunning = true;
	solving = false;
	char Graph[60][120];
	int i = 0;
	int j = 0;
	for (i = 0; i < 60; i++) {
		for (j = 0; j < 120; j++) {
			Graph[i][j] = ' ';
		}
	}
	int y = (int)abs(Ymax);
	y = (int)(y / ((double)yDim / 60));
	int x = (int)abs(Xmin);
	x = (int)(x / ((double)xDim / 120));
	int commas = 1;
	if (isContained("\\", function)) {
		for (j = 0; function[j] != '\0'; j++) {
			if (function[j] == '\\') {
				commas++;
			}
		}
	}
	int x_scale = (int)(Xscale / (xDim / 120)), y_scale = (int)(Yscale / (yDim / 60));
	for (i = 0; i < 60; i++) {
		Graph[y][i] = '_';
		if (i%x_scale == 0) {
			Graph[y + 1][i] = (char)179;
		}
		Graph[i][x] = (char)179;
		if (i%y_scale == 0) {
			Graph[i][x + 1] = '_';
		}
	}
	for (i = 60; i < 120; i++) {
		Graph[y][i] = '_';
		if (i%x_scale == 0) {
			Graph[y + 1][i] = (char)179;
		}
	}
	char specFunction[DIM] = "";
	sprintf(specFunction, function);
	int r = 0, e = 0, count = 0;
	char info[DIM] = "";
	do {
		e = 0;
		while (function[r] != '\\'&&function[r] != '\0') {
			specFunction[e] = function[r];
			r++; e++;
		}
		specFunction[e] = '\0';
		r++;
		char symbols[35] = "XYZOABCDEFGHIJKLMNOPQRSTUVW/*-+_xo";
		double start = Xmin;
		int f = 0;
		double yValues[121] = { 0,0 };
		while (f < 120) {
			xValuesR = start; xValuesI = 0;
			calcNow(specFunction, 0, 0);
			yValues[f] = resultR;
			resultR = 0; resultI = 0;
			start = start + (double)xDim / 120;
			f++;
		}
		f = 0;
		int saveK = 0, saveKK = 0;
		while (f < 120) {
			double yValue = yValues[f];
			int k = 0;
			double yStart = Ymax;
			if (yValue > Ymin&&yValue < Ymax) {
				double l = Ymax, l_2 = 0;
				for (k = 0; k < 60; k++) {
					l = Ymax - k * (double)yDim / 60;
					l_2 = Ymax - (k + 2) * (double)yDim / 60;
					if (yValue<l&&yValue>l_2) {
						break;
					}
				}
				if (saveK != 0) {
					if (saveK > k + 1) {
						while (saveK > k + 1) {
							if (saveK != saveKK) {
								Graph[saveK][f - 1] = '|';
							}
							saveK--;
						}
					}
					else {
						while (saveK < k + 1) {
							if (saveK != saveKK) {
								Graph[saveK][f - 1] = '|';
							}
							saveK++;
						}
					}
				}
				Graph[k + 1][f] = symbols[count];
				saveK = k + 1;
				if (saveK == saveKK) {
					Graph[k + 1][f] = '-';
					Graph[k + 1][f - 1] = '-';
				}
				saveKK = k + 1;
			}
			f++;
		}
		if (isContained("res", specFunction)) {
			replace("res", "x", specFunction);
			sprintf(specFunction, expressionF);
		}
		sprintf(info, "%s\n%s -> %c", info, specFunction, symbols[count]);
		count++;
		commas--;
	} while (commas > 0);
	for (j = 0; j < 121; j++) {
		printf("_");
	}
	printf("\n");
	for (i = 0; i < 60; i++) {
		printf("%c", 179);
		for (j = 0; j < 120; j++) {
			printf("%c", Graph[i][j]);
		}
		printf("%c", 179);
		printf("\n");
	}
	printf("%c", 179);
	for (j = 0; j < 120; j++) {
		printf("_");
	}
	printf("%c", 179);
	printf("\n");
	puts("\nCurrent settings:\n");
	printf("%c Xmin: %G %c Xmax: %G %c Xscale: %G %c Ymin: %G %c Ymax: %G %c Yscale: %G %c\n", 179, Xmin, 179, Xmax, 179, Xscale, 179, Ymin, 179, Ymax, 179, Yscale, 179);
	puts("\nLegend:");
	puts(info);
	solverRunning = false;
	solving = true;
}