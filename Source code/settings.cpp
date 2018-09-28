

#include "stdafx.h"
#include "atc_functions.h"

void colors() {
	FILE *open;
	char bGround = ' ', cTxt = ' ', express[DIM] = "color 73", value[DIM] = "";
	printf("\n Symbol -> Color corresponding to\n\n 0 -> black\n 1 -> blue\n 2 -> green\n 3 -> aqua\n 4 -> red\n 5 -> purple\n 6 -> yellow\n 7 -> white\n 8 -> gray\n 9 -> light blue\n a -> light green\n b -> light aqua\n c -> light red\n d -> light purple\n e -> light yellow\n f -> bright white\n\n");
	printf("Background color: ");
	while (strlen(value) != 1) {
		gets_s(value);
	}
	bGround = value[0];
	value[0] = '\0';
	printf("Text color: ");
	while (strlen(value) != 1) {
		gets_s(value);
	}
	cTxt = value[0];
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
	fprintf(open, "MODE con cols=%G lines=%G", ncols, nlins);
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
		printf("radian -> 1\ndegree -> 2\ngradian -> 3\n");
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
	system("title Advanced Trigonometry Calculator v2.0.0");
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
	system("title Advanced Trigonometry Calculator v2.0.0                                                             ==) Enter data (==              ");
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
		puts("");
	}
	int op = -1;
	while (op > 1 || op < 0) {
		puts("Would you like to change them? (Yes -> 1 \\ No -> 0)");
		op = (int)getValue();
	}
	if (op == 1) {
		int error = -1;
		while (error == -1) {
			puts("Xmin?");
			double Xmin = getValue();
			puts("Xmax?");
			double Xmax = getValue();
			double Xscale = 0.00001;
			while (Xscale < (Xmax - Xmin) / 120) {
				printf("Xscale? (minimum: %G)\n", abs(Xmax - Xmin) / 120);
				Xscale = getValue();
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
					printf("Yscale? (minimum: %G)\n", abs(Ymax - Ymin) / 60);
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
							sprintf(settingsGraph, "%G\n%G\n%G\n%G\n%G\n%G\n%d\n", Xmin, Xmax, Xscale, Ymin, Ymax, Yscale, auto_y_axis);
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
			system("MODE con cols=150 lines=150");
		}
		else {
			open = fopen(toOpen, "r");
			fgets(setting, 40, open);
			fclose(open);
			system(setting);
		}
		return 0;
	}
	if (toDo == 3) {
		int i = 0, e = 0;
		int x, y, width, height, a = 1;
		char value[DIM];
		char toOpen[DIM] = "";
		sprintf(toOpen, "%s\\window.txt", atcPath);
		if (fopen(toOpen, "r") == NULL) {
			HWND a;
			a = GetConsoleWindow();
			MoveWindow(a, 0, 0, 1000, 1000, FALSE);
		}
		else {
			open = fopen(toOpen, "r");
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
			HWND w;
			w = GetConsoleWindow();
			MoveWindow(w, (int)x, (int)y, (int)width, (int)height, FALSE);
		}
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
	system("title Advanced Trigonometry Calculator v2.0.0");
	HWND a;
	a = GetConsoleWindow();
	MoveWindow(a, 0, 0, 1000, 1000, FALSE);
	system("MODE con cols=84 lines=40");
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
	printf("                                  %c%c%c%c%c    %c%c%c     %c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("                                      %c   %c   %c   %c   %c\n", 177, 177, 177, 177, 177);
	printf("                            %c   %c %c%c%c%c%c   %c   %c   %c   %c \n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("                             %c %c  %c       %c   %c   %c   %c\n", 177, 177, 177, 177, 177, 177, 177);
	printf("                              %c   %c%c%c%c%c %c  %c%c%c  %c  %c%c%c  \n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	puts("\n                        by Renato Alexandre dos Santos Freitas\n\n         To support the development of this application please enter \"donate\"\n\n            To know how to use this application please enter \"user guide\"\n");
	printf("                   After this run, ATC is available by \"Ctrl+Alt+K\"\n\n");
	printf("     PRESS THE BUTTON \"Enter\" TO ACCESS THE ENVIRONMENT-RESOLUTION CALCULATIONS\n");
	ShowConsoleCursor(TRUE);
	gets_s(exit);
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