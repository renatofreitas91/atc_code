

#include "stdafx.h"

void Clock(int a)
{
	FILE *fout;
	int s = 0, m = 0, h = 0, d = 0, days = 0, seconds, minutes, hours, years, day = 0, initialTime = 0, dayss = 0, ho = 0, mi = 0, se = 0, signal = -1, Time = 0;
	time_t hour;
	time(&hour);
	char *tim;
	tim = ctime(&hour);
	tim[24] = '\0';
	fout = fopen("history.txt", "a+");
	char min[3] = { tim[14], tim[15], '\0' };
	minutes = atoi(min);
	char hou[3] = { tim[11], tim[12], '\0' };
	hours = atoi(hou);
	char yea[5] = { tim[20], tim[21], tim[22], tim[23], '\0' };
	years = atoi(yea);
	char da[3] = { tim[8], tim[9], '\0' };
	days = atoi(da);
	if (tim[0] == 'M'&&tim[1] == 'o'&&tim[2] == 'n'){
		if (a == 0){
			fprintf(fout, "Monday, ");
		}
		if (a == 1){
			printf("Monday, ");
		}
	}
	if (tim[0] == 'T'&&tim[1] == 'u'&&tim[2] == 'e'){
		if (a == 0){
			fprintf(fout, "Tuesday, ");
		}
		if (a == 1){
			printf("Tuesday, ");
		}
	}
	if (tim[0] == 'W'&&tim[1] == 'e'&&tim[2] == 'd'){
		if (a == 0){
			fprintf(fout, "Wednesday, ");
		}
		if (a == 1){
			printf("Wednesday, ");
		}
	}
	if (tim[0] == 'T'&&tim[1] == 'h'&&tim[2] == 'u'){
		if (a == 0){
			fprintf(fout, "Thursday, ");
		}
		if (a == 1){
			printf("Thursday, ");
		}
	}
	if (tim[0] == 'F'&&tim[1] == 'r'&&tim[2] == 'i'){
		if (a == 0){
			fprintf(fout, "Friday, ");
		}
		if (a == 1){
			printf("Friday, ");
		}
	}
	if (tim[0] == 'S'&&tim[1] == 'a'&&tim[2] == 't'){
		if (a == 0){
			fprintf(fout, "Saturday, ");
		}
		if (a == 1){
			printf("Saturday, ");
		}
	}
	if (tim[0] == 'S'&&tim[1] == 'u'&&tim[2] == 'n'){
		if (a == 0){
			fprintf(fout, "Sunday, ");
		}
		if (a == 1){
			printf("Sunday, ");
		}
	}
	if (tim[4] == 'J'&&tim[5] == 'a'&&tim[6] == 'n'){
		if (a == 0){
			fprintf(fout, "January");
		}
		if (a == 1){
			printf("January");
		}
	}
	if (tim[4] == 'F'&&tim[5] == 'e'&&tim[6] == 'b'){
		if (a == 0){
			fprintf(fout, "February");
		}
		if (a == 1){
			printf("February");
		}
	}
	if (tim[4] == 'M'&&tim[5] == 'a'&&tim[6] == 'r'){
		if (a == 0){
			fprintf(fout, "March");
		}
		if (a == 1){
			printf("March");
		}
	}
	if (tim[4] == 'A'&&tim[5] == 'p'&&tim[6] == 'r'){
		if (a == 0){
			fprintf(fout, "April");
		}
		if (a == 1){
			printf("April");
		}
	}
	if (tim[4] == 'M'&&tim[5] == 'a'&&tim[6] == 'y'){
		if (a == 0){
			fprintf(fout, "May");
		}
		if (a == 1){
			printf("May");
		}
	}
	if (tim[4] == 'J'&&tim[5] == 'u'&&tim[6] == 'n'){
		if (a == 0){
			fprintf(fout, "June");
		}
		if (a == 1){
			printf("June");
		}
	}
	if (tim[4] == 'J'&&tim[5] == 'u'&&tim[6] == 'l'){
		if (a == 0){
			fprintf(fout, "July");
		}
		if (a == 1){
			printf("July");
		}
	}
	if (tim[4] == 'A'&&tim[5] == 'u'&&tim[6] == 'g'){
		if (a == 0){
			fprintf(fout, "August");
		}
		if (a == 1){
			printf("August");
		}
	}
	if (tim[4] == 'S'&&tim[5] == 'e'&&tim[6] == 'p'){
		if (a == 0){
			fprintf(fout, "September");
		}
		if (a == 1){
			printf("September");
		}
	}
	if (tim[4] == 'O'&&tim[5] == 'c'&&tim[6] == 't'){
		if (a == 0){
			fprintf(fout, "October");
		}
		if (a == 1){
			printf("October");
		}
	}
	if (tim[4] == 'N'&&tim[5] == 'o'&&tim[6] == 'v'){
		if (a == 0){
			fprintf(fout, "November");
		}
		if (a == 1){
			printf("November");
		}
	}
	if (tim[4] == 'D'&&tim[5] == 'e'&&tim[6] == 'c'){
		if (a == 0){
			fprintf(fout, "December");
		}
		if (a == 1){
			printf("December");
		}
	}
	if (a == 0){
		fprintf(fout, " %d", days);
	}
	if (a == 1){
		printf(" %d", days);
	}
	if (tim[9] == '1'&&tim[8] != '1'){
		if (a == 0){
			fputs("st", fout);
		}
		if (a == 1){
			printf("st");
		}
	}
	else{
		if (tim[9] == '2'&&tim[8] != '1'){
			if (a == 0){
				fputs("nd", fout);
			}
			if (a == 1){
				printf("nd");
			}
		}
		else{
			if (tim[9] == '3'&&tim[8] != '1'){
				if (a == 0){
					fputs("rd", fout);
				}
				if (a == 1){
					printf("rd");
				}
			}
			else{
				if (a == 0){
					fputs("th", fout);
				}
				if (a == 1){
					printf("th");
				}
			}
		}
	}
	if (a == 0){
		fprintf(fout, ", %d,", years);
	}
	if (a == 1){
		printf(", %d,", years);
	}
	char sec[3] = { tim[17], tim[18], '\0' };
	seconds = atoi(sec);
	if (a == 0){
		fprintf(fout, " %dh %dm %ds\n", hours, minutes, seconds);
	}
	if (a == 1){
		printf(" %dh %dm %ds\n", hours, minutes, seconds);
	}
	fclose(fout);
}

void Calendar(char yearCalendar[DIM], int year){
	FILE *open;
	int w = 0;
	char m30[DIM] = "  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30", m31[DIM] = "  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31", m29[DIM] = "  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29", m28[DIM] = "  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28", weekdays[DIM] = " Mo Tu We Th Fr Sa Su Mo Tu We Th Fr Sa Su Mo Tu We Th Fr Sa Su Mo Tu We Th Fr Sa Su Mo Tu We Th Fr Sa Su Mo Tu";
	open = fopen(yearCalendar, "w");
	fprintf(open, "____________________________________________________________________________________________________________________________\n\n                                                            %d\n\n____________________________________________________________________________________________________________________________\n", year);
	fprintf(open, "           |\n           |%s\n           |\n___________|________________________________________________________________________________________________________________\n           |\n", weekdays);
	fprintf(open, " January   |");
	fclose(open);
	DayofWeek(1, 1, year, yearCalendar);
	open = fopen(yearCalendar, "a+");
	fprintf(open, "%s\n", m31);
	fprintf(open, " February  |");
	fclose(open);
	DayofWeek(1, 2, year, yearCalendar);
	open = fopen(yearCalendar, "a+");
	if (year % 4 == 0){
		if (year % 100 == 0 && year % 400 != 0){
			fprintf(open, "%s\n", m28);
			fclose(open);
		}
		else{
			fprintf(open, "%s\n", m29);
			fclose(open);
		}
	}
	else{
		fprintf(open, "%s\n", m28);
		fclose(open);
	}
	open = fopen(yearCalendar, "a+");
	fprintf(open, " March     |");
	fclose(open);
	DayofWeek(1, 3, year, yearCalendar);
	open = fopen(yearCalendar, "a+");
	fprintf(open, "%s\n", m31);
	fprintf(open, " April     |");
	fclose(open);
	DayofWeek(1, 4, year, yearCalendar);
	open = fopen(yearCalendar, "a+");
	fprintf(open, "%s\n", m30);
	fprintf(open, " May       |");
	fclose(open);
	DayofWeek(1, 5, year, yearCalendar);
	open = fopen(yearCalendar, "a+");
	fprintf(open, "%s\n", m31);
	fprintf(open, " June      |");
	fclose(open);
	DayofWeek(1, 6, year, yearCalendar);
	open = fopen(yearCalendar, "a+");
	fprintf(open, "%s\n", m30);
	fprintf(open, " July      |");
	fclose(open);
	DayofWeek(1, 7, year, yearCalendar);
	open = fopen(yearCalendar, "a+");
	fprintf(open, "%s\n", m31);
	fprintf(open, " August    |");
	fclose(open);
	DayofWeek(1, 8, year, yearCalendar);
	open = fopen(yearCalendar, "a+");
	fprintf(open, "%s\n", m31);
	fprintf(open, " September |");
	fclose(open);
	DayofWeek(1, 9, year, yearCalendar);
	open = fopen(yearCalendar, "a+");
	fprintf(open, "%s\n", m30);
	fprintf(open, " October   |");
	fclose(open);
	DayofWeek(1, 10, year, yearCalendar);
	open = fopen(yearCalendar, "a+");
	fprintf(open, "%s\n", m31);
	fprintf(open, " November  |");
	fclose(open);
	DayofWeek(1, 11, year, yearCalendar);
	open = fopen(yearCalendar, "a+");
	fprintf(open, "%s\n", m30);
	fprintf(open, " December  |");
	fclose(open);
	DayofWeek(1, 12, year, yearCalendar);
	open = fopen(yearCalendar, "a+");
	fprintf(open, "%s\n", m31);
	fprintf(open, "           |\n___________|________________________________________________________________________________________________________________");
	fclose(open);
}

void DayofWeek(int d, int m, int y, char calendar[DIM]){
	FILE *open;
	open = fopen(calendar, "a+");
	int h;
	h = ((int)(d + floor((((m + 1) * 26) / 10)*1.000) + y + floor((y / 4)*1.0000) + 6 * floor((y / 100)*1.0000) + floor((y / 400)*1.0000)) % 7);
	if (m < 3){
		if (m == 1){
			m = 13;
		}
		if (m == 2){
			m = 14;
		}
		y--;
		h = ((int)(d + floor((((m + 1) * 26) / 10)*1.000) + (y)+floor(((y) / 4)*1.0000) + 6 * floor(((y) / 100)*1.0000) + floor(((y) / 400)*1.0000)) % 7);
	}
	if (h == 3){
		printf("   ");
		fprintf(open, "   ");
	}
	if (h == 4){
		printf("      ");
		fprintf(open, "      ");
	}
	if (h == 5){
		printf("         ");
		fprintf(open, "         ");
	}
	if (h == 6){
		printf("            ");
		fprintf(open, "            ");
	}
	if (h == 0){
		printf("               ");
		fprintf(open, "               ");
	}
	if (h == 1){
		printf("                  ");
		fprintf(open, "                  ");
	}
	fclose(open);
}

void printTimer(int hours, int minutes, int seconds){
	cls();
	char tiIn[DIM] = "";
	char text[100] = "";
	char display[755] = "";
	int i = 0, j = 0;
	sprintf(tiIn, "%02d:%02d:%02d\n", hours, minutes, seconds);
	sprintf(text, "\n");
	sprintf(display, "%s%s", display, text);
	sprintf(text, "  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 177, 177, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "  %c%c%c%c                                                         %c%c%c%c\n", 177, 177, 219, 219, 219, 219, 177, 177);
	sprintf(display, "%s%s", display, text);
	while (j < 5){
		sprintf(text, "  %c%c%c%c  ", 177, 177, 219, 219);
		sprintf(display, "%s%s", display, text);
		for (i = 0; tiIn[i] != '\0'; i++){
			if (tiIn[i] == '\n'){
				sprintf(text, " %c%c%c%c \n", 219, 219, 177, 177);
				sprintf(display, "%s%s", display, text);
			}

			if (tiIn[i] == ':'){
				if (j == 0 || j == 4 || j == 2){
					sprintf(text, "   ");
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1 || j == 3){
					sprintf(text, "%c%c ", 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}

			if (tiIn[i] == '0'){
				if (j == 0 || j == 4){
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1 || j == 3){
					sprintf(text, "%c%c   %c%c ", 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2){
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 177, 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);

				}
			}
			if (tiIn[i] == '1'){
				if (j == 0 || j == 2 || j == 4){
					sprintf(text, "%c%c%c%c%c%c%c ", 177, 177, 177, 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				else{
					sprintf(text, "%c%c   %c%c ", 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}

			}
			if (tiIn[i] == '2'){
				if (j == 0 || j == 2 || j == 4){
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1){
					sprintf(text, "%c%c   %c%c ", 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 3){
					sprintf(text, "%c%c   %c%c ", 219, 219, 177, 177);
					sprintf(display, "%s%s", display, text);
				}

			}
			if (tiIn[i] == '3'){
				if (j == 0 || j == 4 || j == 2){
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1 || j == 3){
					sprintf(text, "%c%c   %c%c ", 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}

			}
			if (tiIn[i] == '4'){
				if (j == 0){
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 177, 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1){
					sprintf(text, "%c%c   %c%c ", 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2){
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 3){
					sprintf(text, "%c%c   %c%c ", 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 4){
					sprintf(text, "%c%c%c%c%c%c%c ", 177, 177, 177, 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}

			}
			if (tiIn[i] == '5'){
				if (j == 0 || j == 2 || j == 4){
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1){
					sprintf(text, "%c%c   %c%c ", 219, 219, 177, 177);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 3){
					sprintf(text, "%c%c   %c%c ", 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}

			}
			if (tiIn[i] == '6'){
				if (j == 0 || j == 2 || j == 4){
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1){
					sprintf(text, "%c%c   %c%c ", 219, 219, 177, 177);
					sprintf(display, "%s%s", display, text);
				}

				if (j == 3){
					sprintf(text, "%c%c   %c%c ", 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}

			}
			if (tiIn[i] == '7'){
				if (j == 0){
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2){
					sprintf(text, "%c%c%c%c%c%c%c ", 177, 177, 177, 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1 || j == 3){
					sprintf(text, "%c%c   %c%c ", 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 4){
					sprintf(text, "%c%c%c%c%c%c%c ", 177, 177, 177, 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}


			}
			if (tiIn[i] == '8'){
				if (j == 0 || j == 4 || j == 2){
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1 || j == 3){
					sprintf(text, "%c%c   %c%c ", 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}


			}
			if (tiIn[i] == '9'){
				if (j == 0 || j == 2 || j == 4){
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1){
					sprintf(text, "%c%c   %c%c ", 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 3){
					sprintf(text, "%c%c   %c%c ", 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}

			}

		}
		j++;
	}
	sprintf(text, "  %c%c%c%c                                                         %c%c%c%c\n", 177, 177, 219, 219, 219, 219, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 177, 177, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	puts(display);
}

int datePreciser(double day, double month, double year, double dayS, double monthS, double yearS){
	int plusYears = 0, k = 10, count = -1, flag = 1;
	double dayF = day, monthF = month, yearF = year, dayFF = day;

	while (day != dayS&&k > 0){
		day = dayF; month = monthF; year = yearF;
		if (month > 12){
			plusYears = qu(month, 12);
			year = year + plusYears;
			month = qu(re(month, 12), 1);
		}
		if (month == 0){
			month = 12;
			year--;
		}


		while (day > 29 && (qu(re(year, 4), 1) == 0 && (qu(re(year, 100), 1) != 0) || qu(re(year, 400), 1) == 0) && month == 2 || day > 28 && month == 2 && (qu(re(year, 4), 1) != 0 || qu(re(year, 100), 1) == 0 && qu(re(year, 400), 1) != 0) || (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31 || day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {

			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
				day = day - 31;

			}
			else{
				if (month == 2){
					if ((qu(re(year, 4), 1) == 0 && qu(re(year, 100), 1) != 0) || qu(re(year, 400), 1) == 0){
						day = day - 29;

					}
					else{
						day = day - 28;

					}

				}


				else{
					day = day - 30;

				}

			}

			month++;
			if (month > 12){
				year++;
				month = qu(re(month, 12), 1);
			}


		}
		if (flag == 1){
			dayF--;
		}
		if (flag == 2){
			dayF++;
		}
		k--;
		count++;
		if (k == 0 && flag == 1){
			count = -1;
			k = 10;
			dayF = dayFF;
			flag = 2;
		}
	}
	if (flag == 2){
		count = count*-1;
	}
	return count;
}

void wait(int seconds){
	int sec = 0;
	char seco[3] = "";
	char *tim;
	time_t hour1;
	time(&hour1);
	tim = ctime(&hour1);
	tim[24] = '\0';
	seco[0] = tim[17]; seco[1] = tim[18]; seco[2] = '\0';
	sec = atoi(seco);
	if (seconds == sec){
		while (seconds == sec){
			char *tim;
			time_t hour1;
			time(&hour1);
			tim = ctime(&hour1);
			tim[24] = '\0';
			seco[0] = tim[17]; seco[1] = tim[18]; seco[2] = '\0';
			sec = atoi(seco);
			Sleep(1);
		}
	}
}

