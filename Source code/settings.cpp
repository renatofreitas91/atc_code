

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
	gets_s(lins);
	nlins = arithSolver(lins, 0);
	printf("Number of columns: ");
	gets_s(cols);
	ncols = arithSolver(cols, 0);
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\dimensions.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "MODE con cols=%G lines=%G", ncols, nlins);
	fclose(open);
	applySettings(toDo);
}

void window() {
	FILE *open;
	double x = 601, y = 601, width = 2001, height = 2001;
	char value[DIM] = " ";
	HWND w;
	w = GetConsoleWindow();
	while (x > 600 || x < 0) {
		printf("X-axis value -> [0, 600]: ");
		gets_s(value);
		x = calcNow(value, 0, 0);
	}
	while (y > 600 || y < 0) {
		printf("Y-axis value -> [0, 600]: ");
		gets_s(value);
		y = calcNow(value, 0, 0);
	}
	while (width > 2000 || width < 200) {
		printf("Width value -> [200, 2000]: ");
		gets_s(value);
		width = calcNow(value, 0, 0);
	}
	while (height > 2000 || height < 200) {
		printf("Height value -> [200, 2000]: ");
		gets_s(value);
		height = calcNow(value, 0, 0);
	}
	printf("\n");
	MoveWindow(w, (int)x, (int)y, (int)width, (int)height, FALSE);
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\window.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%G\n%G\n%G\n%G\n", x, y, width, height);
	fclose(open);
}

void mode() {
	FILE *open;
	int option = 0;
	char value[DIM] = "";
	while (option != 1 && option != 2 && option != 3) {
		_flushall();
		printf("radian -> 1\ndegree -> 2\ngradian -> 3\n");
		gets_s(value);
		option = (int)solveNow(value, 0, 0);
		if (option > 3 || option < 1) {
			printf("Error, incorrect choice.\n");
		}
	}
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\mode.txt", atcPath);
	open = fopen(toOpen, "w");
	fprintf(open, "%d", option);
	fclose(open);
}

void about2() {
	system("title Advanced Trigonometry Calculator v1.9.0");
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
	system("title Advanced Trigonometry Calculator v1.9.0                                                             ==) Enter data (==              ");

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
		double x, y, width, height, a = 1;
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
					x = arithSolver(value, 0);
					a = 2; e = 0;
				}
				if (value[e] == '\n'&&a == 2) {
					value[e] = '\0';
					y = arithSolver(value, x);
					a = 3; e = 0;
				}
				if (value[e] == '\n'&&a == 3) {
					value[e] = '\0';
					width = arithSolver(value, y);
					a = 4; e = 0;
				}
				if (value[e] == '\n'&&a == 4) {
					value[e] = '\0';
					height = arithSolver(value, width);
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
		open = fopen(toOpen, "r");
		if (open == NULL) {
			option = 2;
		}
		else {
			fgets(opt, 2, open);
			option = atoi(opt);
		}
		return option;
	}
	return 0;
}

boolean about() {
	ShowConsoleCursor(FALSE);
	system("title Advanced Trigonometry Calculator v1.9.0");
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
	printf("                                     %c%c    %c%c%c     %c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177);
	printf("                                    %c %c   %c   %c   %c   %c\n", 177, 177, 177, 177, 177, 177);
	printf("                             %c   %c %c  %c    %c%c%c%c   %c   %c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("                              %c %c     %c       %c   %c   %c \n", 177, 177, 177, 177, 177, 177);
	printf("                               %c      %c %c  %c%c%c  %c  %c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);

	puts("\n                        by Renato Alexandre dos Santos Freitas\n\n         To support the development of this application please enter \"donate\"\n\n            To know how to use this application please enter \"user guide\"\n\n");
	printf("     PRESS THE BUTTON \"Enter\" TO ACCESS THE ENVIRONMENT-RESOLUTION CALCULATIONS\n\n");
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
	ShowConsoleCursor(TRUE);
	return continu;
}

