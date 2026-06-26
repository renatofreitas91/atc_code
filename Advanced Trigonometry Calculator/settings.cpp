

#include "stdafx.h"
#include "atc_functions.h"
bool starting = true;
int x, y, maxX, maxY, saveX, saveY;
int xATC, yATC, colsATC, linesATC, widthATC, heightATC;

void colors() {
	FILE* open;
	char bGround = ' ', cTxt = ' ';
	char* express = getDynamicCharArray("color 73", "express");
	printf("\n Symbol -> Color corresponding to\n\n 0 -> black\n 1 -> blue\n 2 -> green\n 3 -> aqua\n 4 -> red\n 5 -> purple\n 6 -> yellow\n 7 -> white\n 8 -> gray\n 9 -> light blue\n a -> light green\n b -> light aqua\n c -> light red\n d -> light purple\n e -> light yellow\n f -> bright white\n\n");
	printf("Background color: ");
	bGround = _getch();
	printf("%c\n", bGround);
	printf("Text color: ");
	cTxt = _getch();
	printf("%c\n", cTxt);
	express[6] = bGround;
	express[7] = cTxt;
	printf("\n");
	system(express);
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\colors.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%s", express);
	fclose(open);
	_delete(express, "express"); express = nullptr;
	_delete(toOpen, "toOpen"); toOpen = nullptr;

}
template <typename T>

void dimensions() {
	FILE* open;
	T nlins, ncols;
	char* lins = getDynamicCharArray("", "lins"); char* cols = getDynamicCharArray("", "cols"); char* express = getDynamicCharArray("MODE con cols=", "express");
	int i = 0, e = 0, toDo = 2;
	printf("\nNumber of lines: ");
	nlins = getValue<T>();
	printf("Number of columns: ");
	ncols = getValue<T>();
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\dimensions.txt", atcPath);
	open = fopen(toOpen, "w");
	convertComplex2Exponential(ncols, nlins);
	fprintf(open, "MODE con cols=%s lines=%s", respR, respI);
	fclose(open);
	applySettings(toDo);
	_delete(toOpen, "toOpen"); toOpen = nullptr;
	_delete(lins, "lins"); lins = nullptr;
	_delete(cols, "cols"); cols = nullptr;
	_delete(express, "express"); express = nullptr;

}
template <typename T>

void window() {
	FILE* open;
	int x = 601, y = 601, width = 2001, height = 2001;
	char* value = getDynamicCharArray("", "value");
	HWND w;
	w = GetConsoleWindow();
	while (x > 600 || x < 0) {
		printf("X-axis value -> [0, 600]: ");
		x = (int)getValue<T>();
	}
	while (y > 600 || y < 0) {
		printf("Y-axis value -> [0, 600]: ");
		y = (int)getValue<T>();
	}
	while (width > 2000 || width < 200) {
		printf("Width value -> [200, 2000]: ");
		width = (int)getValue<T>();
	}
	while (height > 2000 || height < 200) {
		printf("Height value -> [200, 2000]: ");
		height = (int)getValue<T>();
	}
	printf("\n");
	MoveWindow(w, x, y, width, height, FALSE);
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\window.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d\n%d\n%d\n%d\n", x, y, width, height);
	fclose(open);
	_delete(toOpen, "toOpen"); toOpen = nullptr;
	_delete(value, "value"); value = nullptr;
}
template <typename T>

void mode() {
	FILE* open = NULL;
	int option = 0;
	char* value = getDynamicCharArray("", "value");
	while (option != 1 && option != 2 && option != 3) {
		printf("radian -> 1\ndegree -> 2\ngradian -> 3\n"); I_O = true;
		option = (int)getValue<T>();
		if (option > 3 || option < 1) {
			printf("Error, incorrect choice.\n");
		}
	}
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\mode.txt", atcPath);
	while (open == NULL) {
		open = fopen(toOpen, "w");
	}
	fprintf(open, "%d", option);
	fclose(open);
	_delete(toOpen, "toOpen"); toOpen = nullptr;
	_delete(value, "value"); value = nullptr;
}

void about2() {
	sprintf(forsprintf, "title Advanced Trigonometry Calculator v2.1.7 (Mem Factor: %.3f)", memFactor);
	system(forsprintf);
	system("MODE con cols=90 lines=15");
	cls();
	FILE* open = NULL;
	char* about = getDynamicCharArray("", "about");
	int i;
	while (open == NULL) {
		open = fopen("About execution of application.txt", "a+");
	}
	for (i = 0; (about[i] = fgetc(open)) != EOF; i++) {
	}
	about[i] = '\0';
	printf("%s\n\n     PRESS THE BUTTON \"Enter\" TO ACCESS THE ENVIRONMENT-RESOLUTION CALCULATIONS \n\n", about);
	gets_s(about, 15000);
	int Window = 3, Dimensions = 2;
	applySettings(Window);
	applySettings(Dimensions);
	sprintf(forsprintf, "title Advanced Trigonometry Calculator v2.1.7 (Mem Factor: %.3f)                                                            ==) Enter data (==              ", memFactor);
	system(forsprintf);
	_delete(about, "about"); about = nullptr;
}
template<typename T>
void graphSettings() {
	FILE* graph = NULL;
	char* toOpen = getDynamicCharArray("", "toOpen");
	sprintf(toOpen, "%s\\graph.txt", atcPath);
	graph = fopen(toOpen, "r");
	if (graph == NULL) {
		puts("\nCurrent settings:\n");
		puts("Xmin: _10");
		puts("Xmax: 10");
		puts("Xscale: 1");
		puts("Ymin: _1E-20");
		puts("Ymax: 1E-20");
		puts("Yscale: 1E-21");
		puts("Auto Y-axis: Enabled");
		puts("Auto X-axis: Enabled");
		puts("");
	}
	else {
		char* data = getDynamicCharArray("", "data");
		int i = 0;
		for (i = 0; (data[i] = fgetc(graph)) != EOF; i++);
		data[i] = '\0';
		puts("\nCurrent settings:\n");
		i = 0; int j = 0;
		char* value = getDynamicCharArray("", "value");
		while (data[i] != '\n' && i < abs((int)strlen(data))) {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		printf("Xmin: %s\n", value);
		i++;
		j = 0;
		while (data[i] != '\n' && i < abs((int)strlen(data))) {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		printf("Xmax: %s\n", value);
		i++;
		j = 0;
		while (data[i] != '\n' && i < abs((int)strlen(data))) {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		printf("Xscale: %s\n", value);
		i++;
		j = 0;
		while (data[i] != '\n' && i < abs((int)strlen(data))) {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		printf("Ymin: %s\n", value);
		i++;
		j = 0;
		while (data[i] != '\n' && i < abs((int)strlen(data))) {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		printf("Ymax: %s\n", value);
		i++;
		j = 0;
		while (data[i] != '\n' && i < abs((int)strlen(data))) {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		printf("Yscale: %s\n", value);
		j = 0;
		i++;
		while (data[i] != '\n' && i < abs((int)strlen(data))) {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		if (isEqual("1", value)) {
			printf("Auto Y-axis: Enabled\n");
		}
		if (isEqual("0", value)) {
			printf("Auto Y-axis: Disabled\n");
		}
		j = 0;
		i++;
		while (data[i] != '\n' && i < abs((int)strlen(data))) {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		if (isEqual("1", value)) {
			printf("Auto X-axis: Enabled\n");
		}
		if (isEqual("0", value)) {
			printf("Auto X-axis: Disabled\n");
		}
		puts("");
		_delete(data, "data"); data = nullptr;
		_delete(value, "value"); value = nullptr;

	}
	int op = -1;
	while (op > 1 || op < 0) {
		I_O = true;
		puts("Would you like to change them? (Yes -> 1 \\ No -> 0)");
		op = (int)getValue<T>();
	}
	if (op == 1) {
		int error = -1;
		while (error == -1) {
			int auto_x_axis = -1;
			while (auto_x_axis != 1 && auto_x_axis != 0) {
				puts("Auto X-axis? (Enable -> 1 \\ Disable -> 0)");
				auto_x_axis = (int)getValue<T>();
			}
			T Xmin = -10;
			T Xmax = 10;
			T Xscale = 1;
			if (auto_x_axis == 0) {
				puts("Xmin?");
				Xmin = getValue<T>();
				puts("Xmax?");
				Xmax = getValue<T>();
				Xscale = 0.00000000001;
				while (Xscale < (Xmax - Xmin) / 120) {
					printf("Xscale? (minimum: %s)\n", convert2Exponential(abs(Xmax - Xmin) / 120));
					Xscale = getValue<T>();
				}
			}
			int auto_y_axis = -1;
			while (auto_y_axis != 1 && auto_y_axis != 0) {
				puts("Auto Y-axis? (Enable -> 1 \\ Disable -> 0)");
				auto_y_axis = (int)getValue<T>();
			}
			T Ymin = -1E-20;
			T Ymax = 1E-20;
			T Yscale = 0.05;
			if (auto_y_axis == 0) {
				puts("Ymin?");
				Ymin = getValue<T>();
				puts("Ymax?");
				Ymax = getValue<T>();
				while (Yscale < (Ymax - Ymin) / 60) {
					printf("Yscale? (minimum: %s)\n", convert2Exponential(abs(Ymax - Ymin) / 60));
					Yscale = getValue<T>();
				}
			}
			char* settingsGraph = getDynamicCharArray("", "settingsGraph");
			if (Ymax <= Ymin) {
				puts("\nError: Ymax <= Ymin  -> Must be the opposite.\n");
			}
			else {
				if (Xmax <= Xmin) {
					puts("\nError: Xmax <= Xmin  -> Must be the opposite.\n");
				}
				else {
					if (Xscale <= 0) {
						puts("\nError: X scale must be greater than 0.\n");
					}
					else {
						if (Yscale <= 0) {
							puts("\nError: Y scale must be greater than 0.\n");
						}
						else {
							error = 0;
							graph = fopen(toOpen, "w");
							sprintf(settingsGraph, "%G\n%G\n%G\n%G\n%G\n%G\n%d\n%d\n", Xmin, Xmax, Xscale, Ymin, Ymax, Yscale, auto_y_axis, auto_x_axis);
							if (isContained("-", settingsGraph)) {
								replace("-", "_", settingsGraph);
								sprintf(settingsGraph, expressionF);
							}
							fputs(settingsGraph, graph);
							fclose(graph);
						}
					}
				}
			}

			_delete(settingsGraph, "settingsGraph"); settingsGraph = nullptr;
		}

	}
	_delete(toOpen, "toOpen"); toOpen = nullptr;

}int applySettings(int toDo) {
	FILE* open = NULL;
	char* setting = getDynamicCharArray(" ", "setting");
	if (toDo == 1) {
		char* toOpen = getDynamicCharArray("", "toOpen");
		sprintf(toOpen, "%s\\colors.txt", atcPath);
		if (fopen(toOpen, "r") == NULL) {
			system("color 73");
		}
		else {
			open = fopen(toOpen, "r");
			fgets(setting, 9, open);
			fclose(open);
			system(setting);
		}
		if (toOpen != nullptr) {
			_delete(toOpen, "toOpen"); toOpen = nullptr;
			_delete(setting, "setting"); setting = nullptr;
		}
		return 0;
	}
	if (toDo == 2) {
		sprintf(forsprintf, "%s\\dimensions.txt", atcPath);
		char* toOpen = getDynamicCharArray(forsprintf, "toOpen");
		if (fopen(toOpen, "r") == NULL) {
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD initialSize = { 160, 300 };
			SetConsoleScreenBufferSize(hOut, initialSize);
		}
		else {
			open = NULL;
			while (open == NULL) {
				open = fopen(toOpen, "r");
				Sleep(10);
			}
			if (open != NULL) {
				int i = 0;
				for (i = 0; (setting[i] = fgetc(open)) != EOF; i++);
				setting[i] = '\0';
				fclose(open);
				system(setting);
				sprintf(forsprintf, "%s", setting);
				sprintf(dimensionsTxt, "%s", forsprintf);
				getDimensions();
				HWND hwnd = GetConsoleWindow();
				RECT rect;
				if (GetWindowRect(hwnd, &rect))
				{
					widthATC = (rect.right - rect.left);
					heightATC = (rect.bottom - rect.top);
					sprintf(toOpen, "%s\\window.txt", atcPath);
					open = NULL;
					while (open == NULL) {
						open = fopen(toOpen, "w");
						Sleep(10);
					}
					fprintf(open, "%d\n%d\n%d\n%d\n", xATC, yATC, widthATC, heightATC);
					fclose(open);
				}
			}
		}
		HWND b;
		b = GetConsoleWindow();
		ShowWindow(b, SW_SHOWMAXIMIZED);
		if (setting != nullptr) {
			_delete(setting, "setting"); setting = nullptr;
		}
		if (toOpen != nullptr) {
			_delete(toOpen, "toOpen"); toOpen = nullptr;
		}
		return 0;
	}
	if (toDo == 3) {

		int i = 0, e = 0;
		int x, y, width, height, a = 1;
		char* value = getDynamicCharArray("", "value");
		sprintf(forsprintf, "%s\\window.txt", atcPath);
		char* toOpen = getDynamicCharArray(forsprintf, "toOpen");

		if (fopen(toOpen, "r") == NULL) {
			system("MODE con cols=4000 lines=4000");
			int x = 0, y = 0, maxX = 0, maxY = 0;
			HWND b;
			b = GetConsoleWindow();
			ShowWindow(b, SW_SHOWMAXIMIZED);
			int width, height;
			HWND hwnd = GetConsoleWindow();
			RECT rect;
			if (GetWindowRect(hwnd, &rect))
			{
				width = rect.right - rect.left;
				height = rect.bottom - rect.top;
			}
			sprintf(toOpen, "%s\\window.txt", atcPath);
			FILE* open = NULL;
			int k = 0;
			while (open == NULL && k < 20) {
				open = fopen(toOpen, "w");
				Sleep(10);
				k++;
			}

			if (open != NULL) {
				fprintf(open, "%d\n%d\n%d\n%d\n", 0, 0, width, height);
				fclose(open);
			}
			else {
				FILE* open1 = fopen(toOpen, "w");
				fprintf(open1, "%d\n%d\n%d\n%d\n", 0, 0, width, height);
				fclose(open1);
			}
			sprintf(windowTxt, "%d\n%d\n%d\n%d\n", 0, 0, width, height);
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			int columns, rows;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			columns = (int)((csbi.srWindow.Right - csbi.srWindow.Left));
			if (columns < 0) {
				columns = (int)((csbi.srWindow.Left + csbi.srWindow.Right));
			}
			rows = 5000;
			sprintf(toOpen, "%s\\dimensions.txt", atcPath);
			sprintf(setting, "");
			open = NULL;
			while (open == NULL) {
				open = fopen(toOpen, "w");
				Sleep(10);
			}
			sprintf(setting, "MODE con cols=%d lines=%d", columns, rows);
			system(setting);
			sprintf(dimensionsTxt, "%s", setting);
			fputs(setting, open);
			fclose(open);
			b = GetConsoleWindow();
			ShowWindow(b, SW_SHOWMAXIMIZED);
		}
		else {
			open = NULL;
			while (open == NULL) {
				open = fopen(toOpen, "r");
				Sleep(10);
			}
			if (open != NULL) {
				for (i = 0; (setting[i] = fgetc(open)) != EOF; i++) {
					value[e] = setting[i];
					if (setting[i] != '\n') {
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
				setting[i] = '\0';
				HWND w;
				w = GetConsoleWindow();
				MoveWindow(w, (int)x, (int)y, (int)width, (int)height, FALSE);
				sprintf(windowTxt, "%s", setting);
			}
		}
		HWND b;
		b = GetConsoleWindow();
		ShowWindow(b, SW_SHOWMAXIMIZED);
		_delete(toOpen, "toOpen"); toOpen = nullptr;
		_delete(value, "value"); value = nullptr;
		_delete(setting, "setting"); setting = nullptr;
		return 0;
	}
	if (toDo == 4) {
		int option = 0;
		char* opt = getDynamicCharArray("", "opt");
		char* toOpen = getDynamicCharArray("", "toOpen");
		sprintf(toOpen, "%s\\mode.txt", atcPath);
		open = NULL;
		int g = 0;
		while (open == NULL && g < 10) {
			open = fopen(toOpen, "r");
			g++;
		}
		if (open == NULL) {
			option = 2;
		}
		else {
			fgets(opt, 2, open);
			option = atoi(opt);
			fclose(open);
		}
		_delete(toOpen, "toOpen"); toOpen = nullptr;
		_delete(opt, "opt"); opt = nullptr;
		_delete(setting, "setting"); setting = nullptr;
		return option;
	}
	_delete(setting, "setting"); setting = nullptr;
	return 0;
}

bool about() {
	ShowConsoleCursor(FALSE);
	sprintf(forsprintf, "title Advanced Trigonometry Calculator v2.1.7 (Mem Factor: %.3f)", memFactor);
	system(forsprintf);

	HWND a;
	a = GetConsoleWindow();
	MoveWindow(a, 0, 0, 760, 760, FALSE);
	system("MODE con cols=84 lines=37");
	_flushall();
	bool continu = true;
	puts("\n\n\n");
	printf("                   %c%c%c  %c%c%c%c  %c   %c  %c%c%c  %c   %c  %c%c%c  %c%c%c%c%c %c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("                  %c   %c %c   %c %c   %c %c   %c %c%c  %c %c   %c %c     %c   %c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("                  %c%c%c%c%c %c   %c %c   %c %c%c%c%c%c %c %c %c %c     %c%c%c   %c   %c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("                  %c   %c %c   %c  %c %c  %c   %c %c  %c%c %c   %c %c     %c   %c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("                  %c   %c %c%c%c%c    %c   %c   %c %c   %c  %c%c%c  %c%c%c%c%c %c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	puts("");
	printf("      %c%c%c%c%c %c%c%c%c  %c%c%c%c%c  %c%c%c%c  %c%c%c  %c   %c  %c%c%c  %c   %c %c%c%c%c%c %c%c%c%c%c %c%c%c%c  %c   %c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("        %c   %c   %c   %c   %c     %c   %c %c%c  %c %c   %c %c%c %c%c %c       %c   %c   %c %c   %c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("        %c   %c%c%c%c    %c   %c %c%c%c %c   %c %c %c %c %c   %c %c %c %c %c%c%c     %c   %c%c%c%c   %c %c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("        %c   %c   %c   %c   %c   %c %c   %c %c  %c%c %c   %c %c   %c %c       %c   %c   %c   %c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("        %c   %c   %c %c%c%c%c%c  %c%c%c   %c%c%c  %c   %c  %c%c%c  %c   %c %c%c%c%c%c   %c   %c   %c   %c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	puts("");
	printf("             %c%c%c   %c%c%c  %c      %c%c%c  %c   %c %c      %c%c%c  %c%c%c%c%c  %c%c%c  %c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("            %c   %c %c   %c %c     %c   %c %c   %c %c     %c   %c   %c   %c   %c %c   %c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("            %c     %c%c%c%c%c %c     %c     %c   %c %c     %c%c%c%c%c   %c   %c   %c %c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("            %c   %c %c   %c %c     %c   %c %c   %c %c     %c   %c   %c   %c   %c %c   %c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("             %c%c%c  %c   %c %c%c%c%c%c  %c%c%c   %c%c%c  %c%c%c%c%c %c   %c   %c    %c%c%c  %c   %c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	puts("");
	puts("                                      v2.1.7");
	puts("\n                        by Renato Alexandre dos Santos Freitas\n\n                                    Made in Portugal\n\n            To know how to use this application please enter \"user guide\"\n");
	printf("                   After this run, ATC is available by \"Ctrl+Alt+K\"\n\n");
	trackMouse();
	clock_t start, end;
	start = clock();
	end = clock();
	puts("        Keep your ATC application up to date by entering \"check for updates\"\n");
	puts("Press \"Enter\" to continue or wait 10 seconds . . .\n");

	int saveSecond = 0, second = 0, i = 0;
	char* getEnter = getDynamicCharArray("", "getEnter");
	printf("\r");
	while (i < 84 - 4) {
		printf("%c", 177);
		i++;
	}
	printf("%02ds", 10);
	while (second < 10) {
		second = (end - start) / CLOCKS_PER_SEC;
		Sleep(100);
		end = clock();
		if (GetKeyState(VK_RETURN) < 0) {
			gets_s(getEnter, 20);
			break;
		}
		if (saveSecond != second) {
			printf("\r");
			i = 0;
			while (i < second * 8) {
				printf("%c", 178);
				i++;
			}
			while (i < 84 - 4) {
				printf("%c", 177);
				i++;
			}
			printf("%02ds", 10 - second);
		}
		saveSecond = second;
	}
	Sleep(333);
	ShowConsoleCursor(TRUE);
	if (continu) {
		cls();
	}
	if (continu) {
		int Window = 3, Dimensions = 2;
		applySettings(Window);
		applySettings(Dimensions);
	}

	if (getEnter != nullptr) {
		_delete(getEnter, "getEnter"); getEnter = nullptr;
	}
	return continu;
}

void getDimensions() {
	sprintf(forsprintf, "%s\\dimensions.txt", atcPath);
	char* toOpen = getDynamicCharArray(forsprintf, "toOpen");
	char* setting = getDynamicCharArray("", "setting");
	FILE* open = NULL;
	if ((open = fopen(toOpen, "r")) == NULL) {
		system("MODE con cols=160 lines=300");
	}
	else {

		if (open != NULL) {
			int i = 0;
			for (i = 0; (forsprintf[i] = fgetc(open)) != EOF; i++);
			forsprintf[i] = '\0';
			sprintf(setting, "%s", forsprintf);
			fclose(open);
			char* value = getDynamicCharArray("", "value");
			sprintf(value, "");
			int l = 0, m = strEnd;
			if (isContained("MODE con cols=", setting)) {
				l = 0; m = strEnd;
				while (verifyNumber(setting[m])) {
					value[l] = setting[m];
					m++; l++;
				}
				value[l] = '\0';
				colsATC = atoi(value);
			}
			if (isContained("lines=", setting)) {
				l = 0; m = strEnd;
				while (verifyNumber(setting[m])) {
					value[l] = setting[m];
					m++; l++;
				}
				value[l] = '\0';
				linesATC = atoi(value);
			}
			_delete(value, "value"); value = nullptr;

		}
		fclose(open);
	}
	int i = 0, e = 0;
	int a = 1;
	char* value = getDynamicCharArray("", "value");
	sprintf(value, "");
	sprintf(setting, "%s\\window.txt", atcPath);
	sprintf(toOpen, "%s", setting);
	open = NULL;
	while (open == NULL) {
		open = fopen(toOpen, "r");
		Sleep(10);
	}
	if (open != NULL) {
		for (i = 0; (setting[i] = fgetc(open)) != EOF; i++) {
			value[e] = setting[i];
			if (setting[i] != '\n') {
				e++;
			}
			if (value[e] == '\n' && a == 1) {
				value[e] = '\0';
				xATC = atoi(value);
				a = 2; e = 0;
			}
			if (value[e] == '\n' && a == 2) {
				value[e] = '\0';
				yATC = atoi(value);
				a = 3; e = 0;
			}
			if (value[e] == '\n' && a == 3) {
				value[e] = '\0';
				widthATC = atoi(value);
				a = 4; e = 0;
			}
			if (value[e] == '\n' && a == 4) {
				value[e] = '\0';
				heightATC = atoi(value);
				a = 5; e = 0;
			}
		}
		setting[i] = '\0';

	}
	_delete(toOpen, "toOpen");
}

template void graphSettings<double>();


void mode() { mode<double>(); }
void dimensions() { dimensions<double>(); }
void window() { window<double>(); }
template void mode<double>();
template void dimensions<double>();
template void window<double>();
