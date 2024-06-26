

#include "stdafx.h"
#include "atc_functions.h"
boolean starting = true;
int x, y, maxX, maxY, saveX, saveY;
int xATC, yATC, colsATC, linesATC, widthATC, heightATC;

void colors() {
	FILE *open;
	char bGround = ' ', cTxt = ' ', express[DIM] = "color 73";
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
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\colors.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%s", express);
	fclose(open);
}

void dimensions() {
	FILE *open;
	double nlins, ncols;
	char lins[DIM] = "", cols[DIM] = "", express[DIM] = "MODE con cols=";
	int i = 0, e = 0, toDo = 2;
	printf("\nNumber of lines: ");
	nlins = getValue();
	printf("Number of columns: ");
	ncols = getValue();
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\dimensions.txt", atcPath);
	open = fopen(toOpen, "w");
	convertComplex2Exponential(ncols, nlins);
	fprintf(open, "MODE con cols=%s lines=%s", respR, respI);
	fclose(open);
	applySettings(toDo);
}

void window() {
	FILE *open;
	int x = 601, y = 601, width = 2001, height = 2001;
	char value[DIM] = " ";
	HWND w;
	w = GetConsoleWindow();
	while (x > 600 || x < 0) {
		printf("X-axis value -> [0, 600]: ");
		x = (int)getValue();
	}
	while (y > 600 || y < 0) {
		printf("Y-axis value -> [0, 600]: ");
		y = (int)getValue();
	}
	while (width > 2000 || width < 200) {
		printf("Width value -> [200, 2000]: ");
		width = (int)getValue();
	}
	while (height > 2000 || height < 200) {
		printf("Height value -> [200, 2000]: ");
		height = (int)getValue();
	}
	printf("\n");
	MoveWindow(w, x, y, width, height, FALSE);
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\window.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d\n%d\n%d\n%d\n", x, y, width, height);
	fclose(open);
}

void mode() {
	FILE *open = NULL;
	int option = 0;
	char value[DIM] = "";
	while (option != 1 && option != 2 && option != 3) {
		printf("radian -> 1\ndegree -> 2\ngradian -> 3\n"); I_O = true;
		option = (int)getValue();
		if (option > 3 || option < 1) {
			printf("Error, incorrect choice.\n");
		}
	}
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\mode.txt", atcPath);
	while (open == NULL) {
		open = fopen(toOpen, "w");
	}
	fprintf(open, "%d", option);
	fclose(open);
}

void about2() {
	system("title Advanced Trigonometry Calculator v2.1.5");
	system("MODE con cols=90 lines=15");
	cls();
	FILE *open = NULL;
	char about[15000] = "";
	int i;
	while (open == NULL) {
		open = fopen("About execution of application.txt", "a+");
	}
	for (i = 0; (about[i] = fgetc(open)) != EOF; i++) {
	}
	about[i] = '\0';
	printf("%s\n\n     PRESS THE BUTTON \"Enter\" TO ACCESS THE ENVIRONMENT-RESOLUTION CALCULATIONS \n\n", about);
	gets_s(about);
	int Window = 3, Dimensions = 2;
	applySettings(Window);
	applySettings(Dimensions);
	system("title Advanced Trigonometry Calculator v2.1.5                                                             ==) Enter data (==              ");
}

void graphSettings() {
	FILE *graph = NULL;
	char toOpen[DIM] = "";
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
		char data[DIM] = "";
		int i = 0;
		for (i = 0; (data[i] = fgetc(graph)) != EOF; i++);
		data[i] = '\0';
		puts("\nCurrent settings:\n");
		i = 0; int j = 0;
		char value[20] = "";
		while (data[i] != '\n'&&data[i] != '\0') {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		printf("Xmin: %s\n", value);
		i++;
		j = 0;
		while (data[i] != '\n'&&data[i] != '\0') {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		printf("Xmax: %s\n", value);
		i++;
		j = 0;
		while (data[i] != '\n'&&data[i] != '\0') {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		printf("Xscale: %s\n", value);
		i++;
		j = 0;
		while (data[i] != '\n'&&data[i] != '\0') {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		printf("Ymin: %s\n", value);
		i++;
		j = 0;
		while (data[i] != '\n'&&data[i] != '\0') {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		printf("Ymax: %s\n", value);
		i++;
		j = 0;
		while (data[i] != '\n'&&data[i] != '\0') {
			value[j] = data[i];
			i++; j++;
		}
		value[j] = '\0';
		printf("Yscale: %s\n", value);
		j = 0;
		i++;
		while (data[i] != '\n'&&data[i] != '\0') {
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
		while (data[i] != '\n'&&data[i] != '\0') {
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
	}
	int op = -1;
	while (op > 1 || op < 0) {
		I_O = true;
		puts("Would you like to change them? (Yes -> 1 \\ No -> 0)");
		op = (int)getValue();
	}
	if (op == 1) {
		int error = -1;
		while (error == -1) {
			int auto_x_axis = -1;
			while (auto_x_axis != 1 && auto_x_axis != 0) {
				puts("Auto X-axis? (Enable -> 1 \\ Disable -> 0)");
				auto_x_axis = (int)getValue();
			}
			double Xmin = -10;
			double Xmax = 10;
			double Xscale = 1;
			if (auto_x_axis == 0) {
				puts("Xmin?");
				double Xmin = getValue();
				puts("Xmax?");
				double Xmax = getValue();
				double Xscale = 0.00000000001;
				while (Xscale < (Xmax - Xmin) / 120) {
					printf("Xscale? (minimum: %s)\n", convert2Exponential(abs(Xmax - Xmin) / 120));
					Xscale = getValue();
				}
			}
			int auto_y_axis = -1;
			while (auto_y_axis != 1 && auto_y_axis != 0) {
				puts("Auto Y-axis? (Enable -> 1 \\ Disable -> 0)");
				auto_y_axis = (int)getValue();
			}
			double Ymin = -1E-20;
			double Ymax = 1E-20;
			double Yscale = 0.05;
			if (auto_y_axis == 0) {
				puts("Ymin?");
				Ymin = getValue();
				puts("Ymax?");
				Ymax = getValue();
				while (Yscale < (Ymax - Ymin) / 60) {
					printf("Yscale? (minimum: %s)\n", convert2Exponential(abs(Ymax - Ymin) / 60));
					Yscale = getValue();
				}
			}
			char settingsGraph[DIM] = "";
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
		}

	}
}

int applySettings(int toDo) {
	FILE *open = NULL;
	char setting[DIM];
	if (toDo == 1) {
		char toOpen[DIM] = "";
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
		return 0;
	}
	if (toDo == 2) {
		char toOpen[DIM] = "";
		sprintf(toOpen, "%s\\dimensions.txt", atcPath);
		if (fopen(toOpen, "r") == NULL) {
			system("MODE con cols=160 lines=300");
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
				sprintf(dimensionsTxt, "%s", setting);
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
		return 0;
	}
	if (toDo == 3) {

		int i = 0, e = 0;
		int x, y, width, height, a = 1;
		char value[DIM];
		char toOpen[DIM] = "";
		sprintf(toOpen, "%s\\window.txt", atcPath);
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
			char toOpen[DIM] = "";
			sprintf(toOpen, "%s\\window.txt", atcPath);
			open = NULL;
			while (open == NULL) {
				open = fopen(toOpen, "w");
				Sleep(10);
			}
			fprintf(open, "%d\n%d\n%d\n%d\n", 0, 0, width, height);
			fclose(open);
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
			char setting[300] = "";
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
		return 0;
	}
	if (toDo == 4) {
		int option = 0;
		char opt[DIM] = "";
		char toOpen[DIM] = "";
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
		return option;
	}
	return 0;
}

boolean about() {
	ShowConsoleCursor(FALSE);
	system("title Advanced Trigonometry Calculator v2.1.5");
	HWND a;
	a = GetConsoleWindow();
	MoveWindow(a, 0, 0, 1000, 1000, FALSE);
	system("MODE con cols=84 lines=43");
	_flushall();
	char exit[DIM] = "";
	boolean continu = true;
	puts("\n\n\n\n");
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
	printf("                                  %c%c%c%c%c       %c   %c%c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("                                      %c       %c   %c    \n", 177, 177, 177);
	printf("                            %c   %c %c%c%c%c%c       %c   %c%c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("                             %c %c  %c           %c       %c\n", 177, 177, 177, 177, 177);
	printf("                              %c   %c%c%c%c%c %c     %c %c %c%c%c%c%c\n", 177, 177, 177, 177, 177, 177,177, 177, 177, 177, 177, 177, 177, 177);
	puts("\n                        by Renato Alexandre dos Santos Freitas\n\n                                    Made in Portugal\n\n            To know how to use this application please enter \"user guide\"\n");
	printf("                   After this run, ATC is available by \"Ctrl+Alt+K\"\n\n");
	trackMouse();
	clock_t start, end;
	start = clock();
	end = clock();
	puts("        Keep your ATC application up to date by entering \"check for updates\"\n");
	puts("Press \"Enter\" to continue or wait 10 seconds . . .\n");

	int saveSecond = 0, second = 0, i = 0;
	char getEnter[20] = "";
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
			gets_s(getEnter);
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
	if (isEqual(exit, "user guide")) {
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("Advanced Trigonometry Calculator - User Guide.pdf"), NULL, NULL, SW_SHOW);
	}
	if (isEqual(exit, "donate")) {
		puts(" ");
		ShellExecute(NULL, _T("open"), _T("C:\\WINDOWS\\system32\\cmd.exe"), _T("/C \"start https://sourceforge.net/p/advantrigoncalc/donate/?source=navbar\""), NULL, SW_SHOW);
	}
	if (continu) {
		cls();
	}
	if (continu) {
		int Window = 3, Dimensions = 2;
		applySettings(Window);
		applySettings(Dimensions);
	}

	return continu;
}

void getDimensions() {
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\dimensions.txt", atcPath);
	char setting[200] = "";
	FILE * open = NULL;
	if (fopen(toOpen, "r") == NULL) {
		system("MODE con cols=160 lines=300");
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
			char value[10] = "";
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
		}
		fclose(open);
	}
	int i = 0, e = 0;
	int a = 1;
	char value[DIM];
	sprintf(toOpen, "%s\\window.txt", atcPath);
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
			if (value[e] == '\n'&&a == 1) {
				value[e] = '\0';
				xATC = atoi(value);
				a = 2; e = 0;
			}
			if (value[e] == '\n'&&a == 2) {
				value[e] = '\0';
				yATC = atoi(value);
				a = 3; e = 0;
			}
			if (value[e] == '\n'&&a == 3) {
				value[e] = '\0';
				widthATC = atoi(value);
				a = 4; e = 0;
			}
			if (value[e] == '\n'&&a == 4) {
				value[e] = '\0';
				heightATC = atoi(value);
				a = 5; e = 0;
			}
		}
		setting[i] = '\0';
		fclose(open);
	}
}