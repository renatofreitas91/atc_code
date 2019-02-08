#include "stdafx.h"

void designGraph(char function[DIM]) {
	if (isContained("x", function)) {
		replace("x", "res", function);
		sprintf(function, expressionF);
	}
	FILE *graph = NULL;
	char toOpen[DIM] = "";
	double Xmin, Xmax, Xscale, Ymin, Ymax, Yscale, auto_y_axis;
	sprintf(toOpen, "%s\\graph.txt", atcPath);
	graph = fopen(toOpen, "r");
	if (graph == NULL) {
		Xmin = -10;
		Xmax = 10;
		Xscale = 1;
		Ymin = -1E-20;
		Ymax = 1E-20;
		Yscale = 1E-21;
		auto_y_axis = 1;
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
		i++;
		j = 0;
		while (data[i] != '\n'&&data[i] != '\0') {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		auto_y_axis = calcNow(value, 0, 0);
	}
	double yValuesAll[20][121];
	double xDim = Xmax - Xmin;
	double valuePerxDim = 120 / xDim;
	double yDim = Ymax - Ymin;
	double valuePeryDim = 60 / yDim;
	double valueXPerXscale = Xscale * valuePerxDim;
	double valueYPerYscale = Yscale * valuePeryDim;
	double x_scale = (Xscale / (xDim / 120)), y_scale = ((Yscale) / (yDim / 60));
	solverRunning = true;
	solving = false;
	int i = 0, j = 0;
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
	char specFunction[DIM] = "";
	sprintf(specFunction, function);
	int r = 0, e = 0, count = 0;
	char info[DIM] = "";
	if (auto_y_axis == 1) {
		do {
			e = 0;
			while (function[r] != '\\'&&function[r] != '\0') {
				specFunction[e] = function[r];
				r++; e++;
			}
			specFunction[e] = '\0';
			r++;
			double start = Xmin;
			int f = 0;
			double yValues[121] = { 0,0 };
			double newYmax = 1E-20, newYmin = -1E-20;
			while (f < 121) {
				xValuesR = start; xValuesI = 0;
				calcNow(specFunction, 0, 0);
				yValues[f] = resultR;
				yValuesAll[count][f] = resultR;
				if (yValues[f] < newYmin) {
					newYmin = yValues[f];
				}
				if (yValues[f] > newYmax) {
					newYmax = yValues[f];
				}
				resultR = 0; resultI = 0;
				start = start + (double)xDim / 120;
				f++;
			}
			if (newYmin < Ymin || newYmax > Ymax) {
				if (abs(newYmin) > newYmax) {
					newYmax = abs(newYmin);
				}
				else {
					newYmin = newYmax * -1;
				}
				Ymax = ceil(newYmax);
				Ymin = floor(newYmin);
				Yscale = abs(Ymax - Ymin) / 20;
				xDim = abs(Xmax - Xmin);
				valuePerxDim = 120 / xDim;
				yDim = abs(Ymax - Ymin);
				valuePeryDim = 60 / yDim;
				valueXPerXscale = Xscale * valuePerxDim;
				valueYPerYscale = Yscale * valuePeryDim;
				i = 0;
				j = 0;
				y = (int)abs(Ymax);
				y = (int)(y / ((double)yDim / 60));
				x = (int)abs(Xmin);
				x = (int)(x / ((double)xDim / 120));
			}
			x_scale = (Xscale / (xDim / 120)); y_scale = ((Yscale) / (yDim / 60));
			commas--;
			count++;
		} while (commas > 0);
	}
	commas = 1;
	if (isContained("\\", function)) {
		for (j = 0; function[j] != '\0'; j++) {
			if (function[j] == '\\') {
				commas++;
			}
		}
	}
	char Graph[60][120];
	i = 0; j = 0;
	for (i = 0; i < 60; i++) {
		for (j = 0; j < 120; j++) {
			Graph[i][j] = ' ';
		}
	}
	for (i = 0; i < 60; i++) {
		Graph[y][i] = '_';
		if (re(i, x_scale) == 0) {
			Graph[y + 1][i] = (char)179;
		}
		Graph[i][x] = (char)179;
		if (re(i, y_scale) == 0) {
			Graph[i][x + 1] = '_';
		}
	}
	for (i = 60; i < 120; i++) {
		Graph[y][i] = '_';
		if (re(i, x_scale) == 0) {
			Graph[y + 1][i] = (char)179;
		}
	}
	sprintf(specFunction, function);
	r = 0; e = 0; count = 0;
	char symbols[35] = "XYZOABCDEFGHIJKLMNOPQRSTUVW/*-+_xo";
	do {
		e = 0;
		while (function[r] != '\\'&&function[r] != '\0') {
			specFunction[e] = function[r];
			r++; e++;
		}
		specFunction[e] = '\0';
		r++;
		double start = Xmin;
		int f = 0;
		double yValues[121] = { 0,0 };
		while (f < 120) {
			if (auto_y_axis == 1) {
				yValues[f] = yValuesAll[count][f];
			}
			else {
				xValuesR = start; xValuesI = 0;
				calcNow(specFunction, 0, 0);
				yValues[f] = resultR;
			}
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
	int option = -1;
	while (option != 1 && option != 0) {
		I_O = true;
		puts("\nDo you want to see the graph data in table form? (Yes -> 1 \\ No -> 0)");
		option = (int)getValue();
	}
	if (option == 1) {
		char valueToText[DIM] = "";
		int k = 0, l = 0;
		puts(" ");
		printf("%cx", 179);
		int g = 0;
		while (g < 11) {
			printf(" ");
			g++;
		}
		k = 0;
		while (k < count) {
			printf("%c%c", 179, symbols[k]);
			int g = 0;
			while (g < 11) {
				printf(" ");
				g++;
			}
			k++;
		}
		printf("\n");
		double start = Xmin;
		while (l < 121) {
			k = 0;
			printf("%c%G", 179, start);
			sprintf(valueToText, "%c%G", 179, start);
			g = (int)strlen(valueToText);
			while (g < 13) {
				printf(" ");
				g++;
			}
			while (k < count) {
				printf("%c%G", 179, yValuesAll[k][l]);
				sprintf(valueToText, "%c%G", 179, yValuesAll[k][l]);
				g = (int)strlen(valueToText);
				while (g < 13) {
					printf(" ");
					g++;
				}
				k++;
			}
			printf("\n");
			start = start + (double)xDim / 120;
			l++;
		}
	}
}