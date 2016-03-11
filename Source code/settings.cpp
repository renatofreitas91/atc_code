
#include "stdafx.h"
#include "atc_functions.h"

void colors(){
	FILE *open;
	char bGround = ' ', cTxt = ' ', express[DIM] = "color 73", value[DIM] = "";
	printf("\n Symbol -> Color corresponding to\n\n 0 -> black\n 1 -> blue\n 2 -> green\n 3 -> aqua\n 4 -> red\n 5 -> purple\n 6 -> yellow\n 7 -> white\n 8 -> gray\n 9 -> light blue\n a -> light green\n b -> light aqua\n c -> light red\n d -> light purple\n e -> light yellow\n f -> bright white\n\n");
	printf("Background color: ");
	while (strlen(value) != 1){
		gets(value);
	}
	bGround = value[0];
	value[0] = '\0';
	printf("Text color: ");
	while (strlen(value) != 1){
		gets(value);
	}
	cTxt = value[0];
	express[6] = bGround;
	express[7] = cTxt;
	printf("\n");
	system(express);
	open = fopen("colors.txt", "w");
	fprintf(open, "%s", express);
	fclose(open);
}

void dimensions(){
	FILE *open;
	double nlins, ncols;
	char lins[DIM] = "", cols[DIM] = "", express[DIM] = "MODE con cols=";
	int i = 0, e = 0, toDo = 2;
	printf("\nNumber of lines: ");
	gets(lins);
	nlins = arithSolver(lins, 0);
	printf("Number of columns: ");
	gets(cols);
	ncols = arithSolver(cols, 0);
	open = fopen("dimensions.txt", "w");
	fprintf(open, "MODE con cols=%G lines=%G", ncols, nlins);
	fclose(open);
	applySettings(toDo);
}

void window(){
	FILE *open;
	double x, y, width, height;
	char value[DIM] = " ";
	HWND w;
	w = GetConsoleWindow();
	printf("X-axis value: ");
	gets(value);
	x = arithSolver(value, 0);
	printf("Y-axis value: ");
	gets(value);
	y = arithSolver(value, 0);
	printf("Width value: ");
	gets(value);
	width = arithSolver(value, 0);
	printf("Height value: ");
	gets(value);
	height = arithSolver(value, 0);
	printf("\n");
	MoveWindow(w, (int)x, (int)y, (int)width, (int)height, FALSE);
	open = fopen("window.txt", "w");
	fprintf(open, "%G\n%G\n%G\n%G\n", x, y, width, height);
	fclose(open);
}

int applySettings(int toDo){
	FILE *open = NULL;
	char setting[DIM];
	if (toDo == 1){
		if (fopen("colors.txt", "r") == NULL){
			system("color 73");
		}
		else{
			open = fopen("colors.txt", "r");
			fgets(setting, 9, open);
			fclose(open);
			system(setting);
		}
		return 0;
	}
	if (toDo == 2){
		if (fopen("dimensions.txt", "r") == NULL){
			system("MODE con cols=130 lines=57");
		}
		else{
			open = fopen("dimensions.txt", "r");
			fgets(setting, 40, open);
			fclose(open);
			system(setting);
		}
		return 0;
	}
	if (toDo == 3){
		int i = 0, e = 0;
		double x, y, width, height, a = 1;
		char value[DIM];
		if (fopen("window.txt", "r") == NULL){
			HWND a;
			a = GetConsoleWindow();
			MoveWindow(a, 0, 0, 1000, 1000, FALSE);
		}
		else{
			open = fopen("window.txt", "r");
			for (i = 0; (setting[i] = fgetc(open)) != EOF; i++){
				value[e] = setting[i];
				if (setting[i] != '\n'){
					e++;
				}
				if (value[e] == '\n'&&a == 1){
					value[e] = '\0';
					x = arithSolver(value, 0);
					a = 2; e = 0;
				}
				if (value[e] == '\n'&&a == 2){
					value[e] = '\0';
					y = arithSolver(value, x);
					a = 3; e = 0;
				}
				if (value[e] == '\n'&&a == 3){
					value[e] = '\0';
					width = arithSolver(value, y);
					a = 4; e = 0;
				}
				if (value[e] == '\n'&&a == 4){
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
	if (toDo == 4){
		int option = 0;
		char opt[DIM] = "";
		open = fopen("mode.txt", "r");
		if (open == NULL){
			option = 2;
		}
		else{
			fgets(opt, 2, open);
			option = atoi(opt);
		}
		return option;
	}
	return 0;
}

void mode(){
	FILE *open;
	int option = 0;
	while (option != 1 && option != 2 && option != 3){
		flushall();
		printf("radian -> 1\ndegree -> 2\ngradian -> 3\n");
		scanf("%d", &option);
		if (option > 3 || option < 1){
			printf("Error, incorrect choice.\n");
		}
	}
	open = fopen("mode.txt", "w");
	fprintf(open, "%d", option);
	fclose(open);
}

int about(){
	system("title Advanced Trigonometry Calculator v1.8.6");
	HWND a;
	a = GetConsoleWindow();
	MoveWindow(a, 0, 0, 1000, 1000, FALSE);
	system("MODE con cols=84 lines=40");
	flushall();
	char exit[DIM] = "";
	int i, continu = 1;
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
	printf("                                     %c%c    %c%c%c     %c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("                                    %c %c   %c   %c   %c   \n", 177, 177, 177, 177, 177);
	printf("                             %c   %c %c  %c    %c%c%c    %c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	printf("                              %c %c     %c   %c   %c   %c   %c\n", 177, 177, 177, 177, 177, 177, 177);
	printf("                               %c      %c %c  %c%c%c  %c  %c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);

	puts("\n                        by Renato Alexandre dos Santos Freitas\n\n            To know how to use this application please enter \"user guide\"\n\n");
	printf("     PRESS THE BUTTON \"Enter\" TO ACCESS THE ENVIRONMENT-RESOLUTION CALCULATIONS\n\n");
	gets(exit);
	for (i = 0; exit[i] != '\0'; i++){
		if (exit[i] == 'A'){
			exit[i] = 'a';
		}
		if (exit[i] == 'E'&&exit[i + 1] == 'N' || exit[i] == 'E'&&exit[i - 1] == 'l' || exit[i] == 'E'&&exit[i - 1] == 'L' || exit[i] == 'E'&&exit[i + 1] == 'n' || exit[i + 1] == 'E'&&exit[i + 1] == 'C' || exit[i] == 'E'&&exit[i + 1] == 'c' || exit[i] == 'E'&&exit[i + 1] == 'C'&&exit[i + 2] == 'H' || exit[i] == 'E'&&exit[i + 1] == 'c'&&exit[i + 2] == 'H' || exit[i] == 'E'&&exit[i + 1] == 'C'&&exit[i + 2] == 'h' || exit[i] == 'E'&&exit[i + 1] == 'x' || exit[i] == 'E'&&exit[i + 1] == 'X'){
			exit[i] = 'e';
		}
		if (exit[i] == 'C'){
			exit[i] = 'c';
		}
		if (exit[i] == 'R'){
			exit[i] = 'r';
		}
		if (exit[i] == 'F'){
			exit[i] = 'f';
		}
		if (exit[i] == 'H'){
			exit[i] = 'h';
		}
		if (exit[i] == 'X'&&exit[i + 1] == 'i' || exit[i] == 'X'&&exit[i + 1] == 'I'){
			exit[i] = 'x';
		}
		if (exit[i] == 'I'){
			exit[i] = 'i';
		}
		if (exit[i] == 'T'){
			exit[i] = 't';
		}
		if (exit[i] == 'S'){
			exit[i] = 's';
		}
	}
	for (i = 0; exit[i] != '\0'; i++){
		if (exit[i] == 's'&&exit[i + 1] == 'o'&&exit[i + 2] == 'b'&&exit[i + 3] == 'r'&&exit[i + 4] == 'e' || exit[i] == 'a'&&exit[i + 1] == 'b'&&exit[i + 2] == 'o'&&exit[i + 3] == 'u'&&exit[i + 4] == 't'){
			about2();
		}
		if (exit[i] == 'u'&&exit[i + 1] == 's'&&exit[i + 2] == 'e'&&exit[i + 3] == 'r'&&exit[i + 4] == ' '&&exit[i + 5] == 'g'&&exit[i + 6] == 'u'&&exit[i + 7] == 'i'&&exit[i + 8] == 'd'&&exit[i + 9] == 'e' || exit[i] == 'm'&&exit[i + 1] == 'a' && exit[i + 2] == 'n' || exit[i + 3] == 'u'&&exit[i + 4] == 'a'&&exit[i + 5] == 'l'){
			ShellExecute(NULL, _T("open"), _T("Advanced Trigonometry Calculator - User Guide.pdf"), NULL, NULL, SW_SHOW);
		}
	}

	if (continu == 1){
		cls();
	}
	if (continu == 1){
		int Window = 3, Dimensions = 2;
		applySettings(Window);
		applySettings(Dimensions);
		system("title Advanced Trigonometry Calculator v1.8.6                                                             ==) Enter data (==              ");
	}
	return continu;
}

void about2(){
	system("title Advanced Trigonometry Calculator v1.8.6");
	system("MODE con cols=90 lines=15");
	cls();
	FILE *open = NULL;
	char about[15000] = "";
	int i;
	while (open == NULL){
		open = fopen("About execution of application.txt", "a+");
	}
	for (i = 0; (about[i] = fgetc(open)) != EOF; i++){
	}
	about[i] = '\0';
	printf("%s\n\n     PRESS THE BUTTON \"Enter\" TO ACCESS THE ENVIRONMENT-RESOLUTION CALCULATIONS \n\n", about);
	gets(about);
	int Window = 3, Dimensions = 2;
	applySettings(Window);
	applySettings(Dimensions);
	system("title Advanced Trigonometry Calculator v1.8.6                                                             ==) Enter data (==              ");

}
