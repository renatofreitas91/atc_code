

#include "stdafx.h"

char calendarStr[DIM] = "";

void Clock(int a)
{
	FILE *fout;
	int s = 0, m = 0, h = 0, d = 0, days = 0, seconds, minutes, hours, years, day = 0, initialTime = 0, dayss = 0, ho = 0, mi = 0, se = 0, signal = -1, Time = 0;
	time_t hour;
	time(&hour);
	char *tim;
	tim = ctime(&hour);
	tim[24] = '\0';
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\history.txt", atcPath);
	fout = fopen(toOpen, "a+");
	char Min[3] = { tim[14], tim[15], '\0' };
	minutes = atoi(Min);
	char hou[3] = { tim[11], tim[12], '\0' };
	hours = atoi(hou);
	char yea[5] = { tim[20], tim[21], tim[22], tim[23], '\0' };
	years = atoi(yea);
	char da[3] = { tim[8], tim[9], '\0' };
	days = atoi(da);
	if (tim[0] == 'M'&&tim[1] == 'o'&&tim[2] == 'n') {
		if (a == 0) {
			fprintf(fout, "Monday, ");
		}
		if (a == 1) {
			printf("Monday, ");
		}
	}
	if (tim[0] == 'T'&&tim[1] == 'u'&&tim[2] == 'e') {
		if (a == 0) {
			fprintf(fout, "Tuesday, ");
		}
		if (a == 1) {
			printf("Tuesday, ");
		}
	}
	if (tim[0] == 'W'&&tim[1] == 'e'&&tim[2] == 'd') {
		if (a == 0) {
			fprintf(fout, "Wednesday, ");
		}
		if (a == 1) {
			printf("Wednesday, ");
		}
	}
	if (tim[0] == 'T'&&tim[1] == 'h'&&tim[2] == 'u') {
		if (a == 0) {
			fprintf(fout, "Thursday, ");
		}
		if (a == 1) {
			printf("Thursday, ");
		}
	}
	if (tim[0] == 'F'&&tim[1] == 'r'&&tim[2] == 'i') {
		if (a == 0) {
			fprintf(fout, "Friday, ");
		}
		if (a == 1) {
			printf("Friday, ");
		}
	}
	if (tim[0] == 'S'&&tim[1] == 'a'&&tim[2] == 't') {
		if (a == 0) {
			fprintf(fout, "Saturday, ");
		}
		if (a == 1) {
			printf("Saturday, ");
		}
	}
	if (tim[0] == 'S'&&tim[1] == 'u'&&tim[2] == 'n') {
		if (a == 0) {
			fprintf(fout, "Sunday, ");
		}
		if (a == 1) {
			printf("Sunday, ");
		}
	}
	if (tim[4] == 'J'&&tim[5] == 'a'&&tim[6] == 'n') {
		if (a == 0) {
			fprintf(fout, "January");
		}
		if (a == 1) {
			printf("January");
		}
	}
	if (tim[4] == 'F'&&tim[5] == 'e'&&tim[6] == 'b') {
		if (a == 0) {
			fprintf(fout, "February");
		}
		if (a == 1) {
			printf("February");
		}
	}
	if (tim[4] == 'M'&&tim[5] == 'a'&&tim[6] == 'r') {
		if (a == 0) {
			fprintf(fout, "March");
		}
		if (a == 1) {
			printf("March");
		}
	}
	if (tim[4] == 'A'&&tim[5] == 'p'&&tim[6] == 'r') {
		if (a == 0) {
			fprintf(fout, "April");
		}
		if (a == 1) {
			printf("April");
		}
	}
	if (tim[4] == 'M'&&tim[5] == 'a'&&tim[6] == 'y') {
		if (a == 0) {
			fprintf(fout, "May");
		}
		if (a == 1) {
			printf("May");
		}
	}
	if (tim[4] == 'J'&&tim[5] == 'u'&&tim[6] == 'n') {
		if (a == 0) {
			fprintf(fout, "June");
		}
		if (a == 1) {
			printf("June");
		}
	}
	if (tim[4] == 'J'&&tim[5] == 'u'&&tim[6] == 'l') {
		if (a == 0) {
			fprintf(fout, "July");
		}
		if (a == 1) {
			printf("July");
		}
	}
	if (tim[4] == 'A'&&tim[5] == 'u'&&tim[6] == 'g') {
		if (a == 0) {
			fprintf(fout, "August");
		}
		if (a == 1) {
			printf("August");
		}
	}
	if (tim[4] == 'S'&&tim[5] == 'e'&&tim[6] == 'p') {
		if (a == 0) {
			fprintf(fout, "September");
		}
		if (a == 1) {
			printf("September");
		}
	}
	if (tim[4] == 'O'&&tim[5] == 'c'&&tim[6] == 't') {
		if (a == 0) {
			fprintf(fout, "October");
		}
		if (a == 1) {
			printf("October");
		}
	}
	if (tim[4] == 'N'&&tim[5] == 'o'&&tim[6] == 'v') {
		if (a == 0) {
			fprintf(fout, "November");
		}
		if (a == 1) {
			printf("November");
		}
	}
	if (tim[4] == 'D'&&tim[5] == 'e'&&tim[6] == 'c') {
		if (a == 0) {
			fprintf(fout, "December");
		}
		if (a == 1) {
			printf("December");
		}
	}
	if (a == 0) {
		fprintf(fout, " %02d", days);
	}
	if (a == 1) {
		printf(" %d", days);
	}
	if (tim[9] == '1'&&tim[8] != '1') {
		if (a == 0) {
			fputs("st", fout);
		}
		if (a == 1) {
			printf("st");
		}
	}
	else {
		if (tim[9] == '2'&&tim[8] != '1') {
			if (a == 0) {
				fputs("nd", fout);
			}
			if (a == 1) {
				printf("nd");
			}
		}
		else {
			if (tim[9] == '3'&&tim[8] != '1') {
				if (a == 0) {
					fputs("rd", fout);
				}
				if (a == 1) {
					printf("rd");
				}
			}
			else {
				if (a == 0) {
					fputs("th", fout);
				}
				if (a == 1) {
					printf("th");
				}
			}
		}
	}
	if (a == 0) {
		fprintf(fout, ", %04d,", years);
	}
	if (a == 1) {
		printf(", %04d,", years);
	}
	char sec[3] = { tim[17], tim[18], '\0' };
	seconds = atoi(sec);
	if (a == 0) {
		fprintf(fout, " %02dh %02dm %02ds\n", hours, minutes, seconds);
	}
	if (a == 1) {
		printf(" %02dh %02dm %02ds\n", hours, minutes, seconds);
	}
	fclose(fout);
}

void Calendar(char yearCalendar[DIM], int year) {
	calendarStr[0] = '\0';
	char string[DIM] = "";
	FILE *open;
	int w = 0;
	char m30[DIM] = "  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30", m31[DIM] = "  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31", m29[DIM] = "  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29", m28[DIM] = "  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28", weekdays[DIM] = " Mo Tu We Th Fr Sa Su Mo Tu We Th Fr Sa Su Mo Tu We Th Fr Sa Su Mo Tu We Th Fr Sa Su Mo Tu We Th Fr Sa Su Mo Tu";
	open = fopen(yearCalendar, "w");
	sprintf(string, "____________________________________________________________________________________________________________________________\n\n                                                            %d\n\n____________________________________________________________________________________________________________________________\n", year);
	sprintf(calendarStr, "%s%s", calendarStr, string);
	sprintf(string, "           |\n           |%s\n           |\n___________|________________________________________________________________________________________________________________\n           |\n", weekdays);
	sprintf(calendarStr, "%s%s", calendarStr, string);
	sprintf(string, " January   |");
	sprintf(calendarStr, "%s%s", calendarStr, string);
	DayofWeek(1, 1, year, yearCalendar);
	sprintf(string, "%s\n", m31);
	sprintf(calendarStr, "%s%s", calendarStr, string);
	sprintf(string, " February  |");
	sprintf(calendarStr, "%s%s", calendarStr, string);
	DayofWeek(1, 2, year, yearCalendar);
	if (year % 4 == 0) {
		if (year % 100 == 0 && year % 400 != 0) {
			sprintf(string, "%s\n", m28);
			sprintf(calendarStr, "%s%s", calendarStr, string);
		}
		else {
			sprintf(string, "%s\n", m29);
			sprintf(calendarStr, "%s%s", calendarStr, string);
		}
	}
	else {
		sprintf(string, "%s\n", m28);
		sprintf(calendarStr, "%s%s", calendarStr, string);
	}
	sprintf(string, " March     |");
	sprintf(calendarStr, "%s%s", calendarStr, string);
	DayofWeek(1, 3, year, yearCalendar);
	sprintf(string, "%s\n", m31);
	sprintf(calendarStr, "%s%s", calendarStr, string);
	sprintf(string, " April     |");
	sprintf(calendarStr, "%s%s", calendarStr, string);
	DayofWeek(1, 4, year, yearCalendar);
	sprintf(string, "%s\n", m30);
	sprintf(calendarStr, "%s%s", calendarStr, string);
	sprintf(string, " May       |");
	sprintf(calendarStr, "%s%s", calendarStr, string);
	DayofWeek(1, 5, year, yearCalendar);
	sprintf(string, "%s\n", m31);
	sprintf(calendarStr, "%s%s", calendarStr, string);
	sprintf(string, " June      |");
	sprintf(calendarStr, "%s%s", calendarStr, string);
	DayofWeek(1, 6, year, yearCalendar);
	sprintf(string, "%s\n", m30);
	sprintf(calendarStr, "%s%s", calendarStr, string);
	sprintf(string, " July      |");
	sprintf(calendarStr, "%s%s", calendarStr, string);
	DayofWeek(1, 7, year, yearCalendar);
	sprintf(string, "%s\n", m31);
	sprintf(calendarStr, "%s%s", calendarStr, string);
	sprintf(string, " August    |");
	sprintf(calendarStr, "%s%s", calendarStr, string);
	DayofWeek(1, 8, year, yearCalendar);
	open = fopen(yearCalendar, "a+");
	sprintf(string, "%s\n", m31);
	sprintf(calendarStr, "%s%s", calendarStr, string);
	sprintf(string, " September |");
	sprintf(calendarStr, "%s%s", calendarStr, string);
	DayofWeek(1, 9, year, yearCalendar);
	sprintf(string, "%s\n", m30);
	sprintf(calendarStr, "%s%s", calendarStr, string);
	sprintf(string, " October   |");
	sprintf(calendarStr, "%s%s", calendarStr, string);
	DayofWeek(1, 10, year, yearCalendar);
	sprintf(string, "%s\n", m31);
	sprintf(calendarStr, "%s%s", calendarStr, string);
	sprintf(string, " November  |");
	sprintf(calendarStr, "%s%s", calendarStr, string);
	DayofWeek(1, 11, year, yearCalendar);
	sprintf(string, "%s\n", m30);
	sprintf(calendarStr, "%s%s", calendarStr, string);
	sprintf(string, " December  |");
	sprintf(calendarStr, "%s%s", calendarStr, string);
	DayofWeek(1, 12, year, yearCalendar);
	sprintf(string, "%s\n", m31);
	sprintf(calendarStr, "%s%s", calendarStr, string);
	sprintf(string, "           |\n___________|________________________________________________________________________________________________________________");
	sprintf(calendarStr, "%s%s", calendarStr, string);
	fprintf(open, "%s", calendarStr);
	fclose(open);
}

void DayofWeek(int d, int m, int y, char calendar[DIM]) {
	char string[DIM] = "";
	int h;
	h = ((int)(d + floor((((m + 1) * 26) / 10)*1.000) + y + floor((y / 4)*1.0000) + 6 * floor((y / 100)*1.0000) + floor((y / 400)*1.0000)) % 7);
	if (m < 3) {
		if (m == 1) {
			m = 13;
		}
		if (m == 2) {
			m = 14;
		}
		y--;
		h = ((int)(d + floor((((m + 1) * 26) / 10)*1.000) + (y)+floor(((y) / 4)*1.0000) + 6 * floor(((y) / 100)*1.0000) + floor(((y) / 400)*1.0000)) % 7);
	}
	if (h == 3) {
		sprintf(string, "   ");
		sprintf(calendarStr, "%s%s", calendarStr, string);
	}
	if (h == 4) {
		sprintf(string, "      ");
		sprintf(calendarStr, "%s%s", calendarStr, string);
	}
	if (h == 5) {
		sprintf(string, "         ");
		sprintf(calendarStr, "%s%s", calendarStr, string);
	}
	if (h == 6) {
		sprintf(string, "            ");
		sprintf(calendarStr, "%s%s", calendarStr, string);
	}
	if (h == 0) {
		sprintf(string, "               ");
		sprintf(calendarStr, "%s%s", calendarStr, string);
	}
	if (h == 1) {
		sprintf(string, "                  ");
		sprintf(calendarStr, "%s%s", calendarStr, string);
	}
}

void printTimer(int hours, int minutes, int seconds) {
	GoToXY(0, 0);
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
	while (j < 5) {
		sprintf(text, "  %c%c%c%c  ", 177, 177, 219, 219);
		sprintf(display, "%s%s", display, text);
		for (i = 0; tiIn[i] != '\0'; i++) {
			if (tiIn[i] == '\n') {
				sprintf(text, " %c%c%c%c \n", 219, 219, 177, 177);
				sprintf(display, "%s%s", display, text);
			}
			if (tiIn[i] == ':') {
				if (j == 0 || j == 4 || j == 2) {
					sprintf(text, "   ");
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1 || j == 3) {
					sprintf(text, "%c%c ", 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '0') {
				if (j == 0 || j == 4) {
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1 || j == 3) {
					sprintf(text, "%c%c   %c%c ", 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2) {
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 177, 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '1') {
				if (j == 0 || j == 2 || j == 4) {
					sprintf(text, "%c%c%c%c%c%c%c ", 177, 177, 177, 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				else {
					sprintf(text, "%c%c   %c%c ", 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '2') {
				if (j == 0 || j == 2 || j == 4) {
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1) {
					sprintf(text, "%c%c   %c%c ", 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 3) {
					sprintf(text, "%c%c   %c%c ", 219, 219, 177, 177);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '3') {
				if (j == 0 || j == 4 || j == 2) {
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1 || j == 3) {
					sprintf(text, "%c%c   %c%c ", 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '4') {
				if (j == 0) {
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 177, 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1) {
					sprintf(text, "%c%c   %c%c ", 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2) {
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 3) {
					sprintf(text, "%c%c   %c%c ", 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 4) {
					sprintf(text, "%c%c%c%c%c%c%c ", 177, 177, 177, 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '5') {
				if (j == 0 || j == 2 || j == 4) {
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1) {
					sprintf(text, "%c%c   %c%c ", 219, 219, 177, 177);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 3) {
					sprintf(text, "%c%c   %c%c ", 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '6') {
				if (j == 0 || j == 2 || j == 4) {
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1) {
					sprintf(text, "%c%c   %c%c ", 219, 219, 177, 177);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 3) {
					sprintf(text, "%c%c   %c%c ", 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '7') {
				if (j == 0) {
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2) {
					sprintf(text, "%c%c%c%c%c%c%c ", 177, 177, 177, 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1 || j == 3) {
					sprintf(text, "%c%c   %c%c ", 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 4) {
					sprintf(text, "%c%c%c%c%c%c%c ", 177, 177, 177, 177, 177, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '8') {
				if (j == 0 || j == 4 || j == 2) {
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1 || j == 3) {
					sprintf(text, "%c%c   %c%c ", 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '9') {
				if (j == 0 || j == 2 || j == 4) {
					sprintf(text, "%c%c%c%c%c%c%c ", 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 1) {
					sprintf(text, "%c%c   %c%c ", 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 3) {
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
	sprintf(text, "  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	puts(display);
}

void printBigTimer(int hours, int minutes, int seconds) {
	GoToXY(0, 0);
	char tiIn[DIM] = "";
	char text[300] = "";
	char display[DIM] = "";
	int i = 0, j = 0;
	sprintf(tiIn, "%02d:%02d:%02d\n", hours, minutes, seconds);
	sprintf(text, "\n\n\n");
	sprintf(display, "%s%s", display, text);
	sprintf(text, "    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 177, 177, 177, 177, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 177, 177, 177, 177, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "    %c%c%c%c%c%c%c%c                                                                                                    %c%c%c%c%c%c%c%c \n", 177, 177, 177, 177, 219, 219, 219, 219, 219, 219, 219, 219, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "    %c%c%c%c%c%c%c%c                                                                                                    %c%c%c%c%c%c%c%c \n", 177, 177, 177, 177, 219, 219, 219, 219, 219, 219, 219, 219, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "meio");
	while (j < 10) {
		sprintf(text, "    %c%c%c%c%c%c%c%c   ", 177, 177, 177, 177, 219, 219, 219, 219);
		sprintf(display, "%s%s", display, text);
		for (i = 0; tiIn[i] != '\0'; i++) {
			if (tiIn[i] == '\n') {
				sprintf(text, " %c%c%c%c%c%c%c%c\n", 219, 219, 219, 219, 177, 177, 177, 177);
				sprintf(display, "%s%s", display, text);
			}
			if (tiIn[i] == ':') {
				if (j == 0 || j == 1 || j == 4 || j == 5 || j == 8 || j == 9) {
					sprintf(text, "      ");
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2 || j == 3 || j == 6 || j == 7) {
					sprintf(text, "%c%c%c%c  ", 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '0') {
				if (j == 0 || j == 8 || j == 9 || j == 1) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2 || j == 3 || j == 6 || j == 7) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 4 || j == 5) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 219, 219, 219, 219, 177, 177, 177, 177, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '1') {
				if (j == 1 || j == 0 || j == 8 || j == 9 || j == 4 || j == 5) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 177, 177, 177, 177, 177, 177, 177, 177, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2 || j == 3 || j == 6 || j == 7) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 177, 177, 177, 177, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '2') {
				if (j == 0 || j == 1 || j == 4 || j == 5 || j == 8 || j == 9) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2 || j == 3) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 177, 177, 177, 177, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 6 || j == 7) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 219, 219, 219, 219, 177, 177, 177, 177);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '3') {
				if (j == 0 || j == 1 || j == 4 || j == 5 || j == 8 || j == 9) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2 || j == 3 || j == 6 || j == 7) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 177, 177, 177, 177, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '4') {
				if (j == 0 || j == 1) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 219, 219, 219, 219, 177, 177, 177, 177, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2 || j == 3) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 4 || j == 5) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 6 || j == 7) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 177, 177, 177, 177, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 8 || j == 9) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 177, 177, 177, 177, 177, 177, 177, 177, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '5') {
				if (j == 0 || j == 1 || j == 4 || j == 5 || j == 8 || j == 9) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 6 || j == 7) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 177, 177, 177, 177, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2 || j == 3) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 219, 219, 219, 219, 177, 177, 177, 177);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '6') {
				if (j == 0 || j == 1 || j == 4 || j == 5 || j == 8 || j == 9) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2 || j == 3) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 219, 219, 219, 219, 177, 177, 177, 177);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 6 || j == 7) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '7') {
				if (j == 0 || j == 1) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 8 || j == 9 || j == 4 || j == 5) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 177, 177, 177, 177, 177, 177, 177, 177, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2 || j == 3 || j == 6 || j == 7) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 177, 177, 177, 177, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '8') {
				if (j == 0 || j == 8 || j == 9 || j == 1 || j == 4 || j == 5) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2 || j == 3 || j == 6 || j == 7) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
			if (tiIn[i] == '9') {
				if (j == 0 || j == 1 || j == 4 || j == 5 || j == 8 || j == 9) {
					sprintf(text, "%c%c%c%c%c%c%c%c%c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 2 || j == 3) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 219, 219, 219, 219, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
				if (j == 6 || j == 7) {
					sprintf(text, "%c%c%c%c    %c%c%c%c  ", 177, 177, 177, 177, 219, 219, 219, 219);
					sprintf(display, "%s%s", display, text);
				}
			}
		}
		j++;
	}
	sprintf(text, "    %c%c%c%c%c%c%c%c                                                                                                    %c%c%c%c%c%c%c%c \n", 177, 177, 177, 177, 219, 219, 219, 219, 219, 219, 219, 219, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "    %c%c%c%c%c%c%c%c                                                                                                    %c%c%c%c%c%c%c%c \n", 177, 177, 177, 177, 219, 219, 219, 219, 219, 219, 219, 219, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 177, 177, 177, 177, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 177, 177, 177, 177, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	sprintf(text, "    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177);
	sprintf(display, "%s%s", display, text);
	puts(display);
}

void wait(int seconds) {
	int sec = 0;
	char seco[3] = "";
	char *tim;
	time_t hour1;
	time(&hour1);
	tim = ctime(&hour1);
	tim[24] = '\0';
	seco[0] = tim[17]; seco[1] = tim[18]; seco[2] = '\0';
	sec = atoi(seco);
	if (seconds == sec) {
		while (seconds == sec) {
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

int datePreciser(double day, double month, double year, double dayS, double monthS, double yearS) {
	int plusYears = 0, k = 10, count = -1, flag = 1;
	double dayF = day, monthF = month, yearF = year, dayFF = day;
	while (day != dayS && k > 0) {
		day = dayF; month = monthF; year = yearF;
		if (month > 12) {
			plusYears = (int)qu(month, 12);
			year = year + plusYears;
			month = qu(re(month, 12), 1);
		}
		if (month == 0) {
			month = 12;
			year--;
		}
		while (day > 29 && (qu(re(year, 4), 1) == 0 && (qu(re(year, 100), 1) != 0) || qu(re(year, 400), 1) == 0) && month == 2 || day > 28 && month == 2 && (qu(re(year, 4), 1) != 0 || qu(re(year, 100), 1) == 0 && qu(re(year, 400), 1) != 0) || (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31 || day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
				day = day - 31;
			}
			else {
				if (month == 2) {
					if ((qu(re(year, 4), 1) == 0 && qu(re(year, 100), 1) != 0) || qu(re(year, 400), 1) == 0) {
						day = day - 29;
					}
					else {
						day = day - 28;
					}
				}
				else {
					day = day - 30;
				}
			}
			month++;
			if (month > 12) {
				year++;
				month = qu(re(month, 12), 1);
			}
		}
		if (flag == 1) {
			dayF--;
		}
		if (flag == 2) {
			dayF++;
		}
		k--;
		count++;
		if (k == 0 && flag == 1) {
			count = -1;
			k = 10;
			dayF = dayFF;
			flag = 2;
		}
	}
	if (flag == 2) {
		count = count * -1;
	}
	return count;
}

void timeDifferenceCalculations() {
	int toContinue = 1;
	int option;
	do {
		option = 0;
		while (option < 1 || option>3) {
			printf("\n\nTime difference between:");
			printf("\n\t\t\t o present time and past time-> 1");
			printf("\n\t\t\t o future time and present time-> 2");
			printf("\n\t\t\t o two different times-> 3\n");
			I_O = true;
			option = (int)getValue();
			I_O = false;
		}
		int bDay, bMonth, bYear, bHour, bMinutes, bSeconds;
		int countLeapYears = 0;
		int aHour = 0, aMinutes = 0, aSeconds = 0, aDay = 0, aMonth = 0, aYear = 0;
		if (option == 1) {
			printf("Enter the older time data:");
			bYear = 0;
			while (bYear < 1582) {
				printf("\nYear? (1582 minimum)\n");
				bYear = (int)getValue();
				if (bYear < 1582) {
					printf("\nError: You have entered a year previous to the indroduce of Gregorian calendar.\n");
				}
			}
			bMonth = 0;
			while ((bMonth < 1 || bMonth>12) || (bYear == 1582 && bMonth < 10)) {
				printf("\nMonth? (1-12)\n");
				bMonth = (int)getValue();
				if ((bYear == 1582 && bMonth < 10)) {
					printf("\nError: You have entered time data previous to the indroduce of Gregorian calendar.\n");
				}
				if (bMonth < 0 || bMonth>12) {
					printf("\nError: You have entered an invalid month.\n");
				}
			}
			bDay = 0;
			if (bMonth == 1 || bMonth == 3 || bMonth == 5 || bMonth == 7 || bMonth == 8 || bMonth == 10 || bMonth == 12) {
				while ((bDay < 1 || bDay>31) || (bMonth == 10 && bYear == 1582 && bDay < 15)) {
					printf("\nDay? (1-31)\n");
					bDay = (int)getValue();
					if (bDay < 1 || bDay>31) {
						printf("\nError: You have entered an invalid day for months with 31 duration days.\n");
					}
					if (bMonth == 10 && bYear == 1582 && bDay < 15) {
						printf("\nError: You have entered time data previous to the indroduce of Gregorian calendar.\n");
					}
				}
			}
			else {
				if (bMonth == 4 || bMonth == 6 || bMonth == 9 || bMonth == 11) {
					while ((bDay < 1 || bDay>30) || (bMonth < 10 && bYear == 1582)) {
						printf("\nDay? (1-30)\n");
						bDay = (int)getValue();
						if (bDay < 1 || bDay>30) {
							printf("\nError: You have entered an invalid day for months with 30 duration days.\n");
						}
						if (bMonth < 10 && bYear == 1582) {
							printf("\nError: You have entered time data previous to the indroduce of Gregorian calendar.\n");
						}
					}
				}
				else {
					if (bMonth == 2 && isLeapYear(bYear)) {
						while (bDay < 1 || bDay>29) {
							printf("\nDay? (1-29)\n");
							bDay = (int)getValue();
							if (bDay < 1 || bDay>29) {
								printf("\nError: You have entered a leap year, so February has 29 duration days.\n");
							}
						}
					}
					else {
						if (bMonth == 2 && !isLeapYear(bYear)) {
							while (bDay < 1 || bDay>28) {
								printf("\nDay? (1-28)\n");
								bDay = (int)getValue();
								if (bDay < 1 || bDay>28) {
									printf("\nError: You have entered a common year, so February has 28 duration days.\n");
								}
							}
						}
					}
				}
			}
			bHour = -1;
			while (bHour < 0 || bHour>23) {
				printf("\nHour? (0-23, i.e. Please consider the 24-hour clock.)\n");
				bHour = (int)getValue();
				if (bHour < 0 || bHour>23) {
					printf("\nError: The hour must be between 0 and 23, inclusively.\n");
				}
			}
			bMinutes = -1;
			while (bMinutes < 0 || bMinutes>59) {
				printf("\nMinute? (0-59)\n");
				bMinutes = (int)getValue();
				if (bMinutes < 0 || bMinutes>59) {
					printf("\nError: The minute must be between 0 and 59, inclusively.\n");
				}
			}
			bSeconds = -1;
			while (bSeconds < 0 || bSeconds>59) {
				printf("\nSecond? (0-59)\n");
				bSeconds = (int)getValue();
				if (bSeconds < 0 || bSeconds>59) {
					printf("\nError: The second must be between 0 and 59, inclusively.\n");
				}
			}
			time_t hour;
			time(&hour);
			char *tim;
			tim = ctime(&hour);
			tim[24] = '\0';
			char sec[3] = { tim[17], tim[18], '\0' };
			aSeconds = atoi(sec);
			char Min[3] = { tim[14], tim[15], '\0' };
			aMinutes = atoi(Min);
			char hou[3] = { tim[11], tim[12], '\0' };
			aHour = atoi(hou);
			char yea[5] = { tim[20], tim[21], tim[22], tim[23], '\0' };
			aYear = atoi(yea);
			char da[3] = { tim[8], tim[9], '\0' };
			aDay = atoi(da);
			if (tim[4] == 'J'&&tim[5] == 'a'&&tim[6] == 'n') {
				aMonth = 1;
			}
			if (tim[4] == 'F'&&tim[5] == 'e'&&tim[6] == 'b') {
				aMonth = 2;
			}
			if (tim[4] == 'M'&&tim[5] == 'a'&&tim[6] == 'r') {
				aMonth = 3;
			}
			if (tim[4] == 'A'&&tim[5] == 'p'&&tim[6] == 'r') {
				aMonth = 4;
			}
			if (tim[4] == 'M'&&tim[5] == 'a'&&tim[6] == 'y') {
				aMonth = 5;
			}
			if (tim[4] == 'J'&&tim[5] == 'u'&&tim[6] == 'n') {
				aMonth = 6;
			}
			if (tim[4] == 'J'&&tim[5] == 'u'&&tim[6] == 'l') {
				aMonth = 7;
			}
			if (tim[4] == 'A'&&tim[5] == 'u'&&tim[6] == 'g') {
				aMonth = 8;
			}
			if (tim[4] == 'S'&&tim[5] == 'e'&&tim[6] == 'p') {
				aMonth = 9;
			}
			if (tim[4] == 'O'&&tim[5] == 'c'&&tim[6] == 't') {
				aMonth = 10;
			}
			if (tim[4] == 'N'&&tim[5] == 'o'&&tim[6] == 'v') {
				aMonth = 11;
			}
			if (tim[4] == 'D'&&tim[5] == 'e'&&tim[6] == 'c') {
				aMonth = 12;
			}
		}
		if (option == 2) {
			printf("Enter the latter time data:");
			aYear = 0;
			while (aYear < 1582) {
				printf("\nYear? (1582 minimum)\n");
				aYear = (int)getValue();
				if (aYear < 1582) {
					printf("\nError: You have entered a year previous to the indroduce of Gregorian calendar.\n");
				}
			}
			aMonth = 0;
			while ((aMonth < 1 || aMonth>12) || (aYear == 1582 && aMonth < 10)) {
				printf("\nMonth? (1-12)\n");
				aMonth = (int)getValue();
				if ((aYear == 1582 && aMonth < 10)) {
					printf("\nError: You have entered time data previous to the indroduce of Gregorian calendar.\n");
				}
				if (aMonth < 0 || aMonth>12) {
					printf("\nError: You have entered an invalid month.\n");
				}
			}
			aDay = 0;
			if (aMonth == 1 || aMonth == 3 || aMonth == 5 || aMonth == 7 || aMonth == 8 || aMonth == 10 || aMonth == 12) {
				while ((aDay < 1 || aDay>31) || (aMonth == 10 && aYear == 1582 && aDay < 15)) {
					printf("\nDay? (1-31)\n");
					aDay = (int)getValue();
					if (aDay < 1 || aDay>31) {
						printf("\nError: You have entered an invalid day for months with 31 duration days.\n");
					}
					if (aMonth == 10 && aYear == 1582 && aDay < 15) {
						printf("\nError: You have entered time data previous to the indroduce of Gregorian calendar.\n");
					}
				}
			}
			else {
				if (aMonth == 4 || aMonth == 6 || aMonth == 9 || aMonth == 11) {
					while ((aDay < 1 || aDay>30) || (aMonth < 10 && aYear == 1582)) {
						printf("\nDay? (1-30)\n");
						aDay = (int)getValue();
						if (aDay < 1 || aDay>30) {
							printf("\nError: You have entered an invalid day for months with 30 duration days.\n");
						}
						if (aMonth < 10 && aYear == 1582) {
							printf("\nError: You have entered time data previous to the indroduce of Gregorian calendar.\n");
						}
					}
				}
				else {
					if (aMonth == 2 && isLeapYear(aYear)) {
						while (aDay < 1 || aDay>29) {
							printf("\nDay? (1-29)\n");
							aDay = (int)getValue();
							if (aDay < 1 || aDay>29) {
								printf("\nError: You have entered a leap year, so Fearuary has 29 duration days.\n");
							}
						}
					}
					else {
						if (aMonth == 2 && !isLeapYear(aYear)) {
							while (aDay < 1 || aDay>28) {
								printf("\nDay? (1-28)\n");
								aDay = (int)getValue();
								if (aDay < 1 || aDay>28) {
									printf("\nError: You have entered a common year, so February has 28 duration days.\n");
								}
							}
						}
					}
				}
			}
			aHour = -1;
			while (aHour < 0 || aHour>23) {
				printf("\nHour? (0-23, i.e. Please consider the 24-hour clock.)\n");
				aHour = (int)getValue();
				if (aHour < 0 || aHour>23) {
					printf("\nError: The hour must be between 0 and 23, inclusively.\n");
				}
			}
			aMinutes = -1;
			while (aMinutes < 0 || aMinutes>59) {
				printf("\nMinute? (0-59)\n");
				aMinutes = (int)getValue();
				if (aMinutes < 0 || aMinutes>59) {
					printf("\nError: The minute must be between 0 and 59, inclusively.\n");
				}
			}
			aSeconds = -1;
			while (aSeconds < 0 || aSeconds>59) {
				printf("\nSecond? (0-59)\n");
				aSeconds = (int)getValue();
				if (aSeconds < 0 || aSeconds>59) {
					printf("\nError: The second must be between 0 and 59, inclusively.\n");
				}
			}
			time_t hour;
			time(&hour);
			char *tim;
			tim = ctime(&hour);
			tim[24] = '\0';
			char sec[3] = { tim[17], tim[18], '\0' };
			bSeconds = atoi(sec);
			char Min[3] = { tim[14], tim[15], '\0' };
			bMinutes = atoi(Min);
			char hou[3] = { tim[11], tim[12], '\0' };
			bHour = atoi(hou);
			char yea[5] = { tim[20], tim[21], tim[22], tim[23], '\0' };
			bYear = atoi(yea);
			char da[3] = { tim[8], tim[9], '\0' };
			bDay = atoi(da);
			if (tim[4] == 'J'&&tim[5] == 'a'&&tim[6] == 'n') {
				bMonth = 1;
			}
			if (tim[4] == 'F'&&tim[5] == 'e'&&tim[6] == 'b') {
				bMonth = 2;
			}
			if (tim[4] == 'M'&&tim[5] == 'a'&&tim[6] == 'r') {
				bMonth = 3;
			}
			if (tim[4] == 'A'&&tim[5] == 'p'&&tim[6] == 'r') {
				bMonth = 4;
			}
			if (tim[4] == 'M'&&tim[5] == 'a'&&tim[6] == 'y') {
				bMonth = 5;
			}
			if (tim[4] == 'J'&&tim[5] == 'u'&&tim[6] == 'n') {
				bMonth = 6;
			}
			if (tim[4] == 'J'&&tim[5] == 'u'&&tim[6] == 'l') {
				bMonth = 7;
			}
			if (tim[4] == 'A'&&tim[5] == 'u'&&tim[6] == 'g') {
				bMonth = 8;
			}
			if (tim[4] == 'S'&&tim[5] == 'e'&&tim[6] == 'p') {
				bMonth = 9;
			}
			if (tim[4] == 'O'&&tim[5] == 'c'&&tim[6] == 't') {
				bMonth = 10;
			}
			if (tim[4] == 'N'&&tim[5] == 'o'&&tim[6] == 'v') {
				bMonth = 11;
			}
			if (tim[4] == 'D'&&tim[5] == 'e'&&tim[6] == 'c') {
				bMonth = 12;
			}
		}
		if (option == 3) {
			printf("Enter the older time data:");
			bYear = 0;
			while (bYear < 1582) {
				printf("\nYear? (1582 minimum)\n");
				bYear = (int)getValue();
				if (bYear < 1582) {
					printf("\nError: You have entered a year previous to the indroduce of Gregorian calendar.\n");
				}
			}
			bMonth = 0;
			while ((bMonth < 1 || bMonth>12) || (bYear == 1582 && bMonth < 10)) {
				printf("\nMonth? (1-12)\n");
				bMonth = (int)getValue();
				if ((bYear == 1582 && bMonth < 10)) {
					printf("\nError: You have entered time data previous to the indroduce of Gregorian calendar.\n");
				}
				if (bMonth < 0 || bMonth>12) {
					printf("\nError: You have entered an invalid month.\n");
				}
			}
			bDay = 0;
			if (bMonth == 1 || bMonth == 3 || bMonth == 5 || bMonth == 7 || bMonth == 8 || bMonth == 10 || bMonth == 12) {
				while ((bDay < 1 || bDay>31) || (bMonth == 10 && bYear == 1582 && bDay < 15)) {
					printf("\nDay? (1-31)\n");
					bDay = (int)getValue();
					if (bDay < 1 || bDay>31) {
						printf("\nError: You have entered an invalid day for months with 31 duration days.\n");
					}
					if (bMonth == 10 && bYear == 1582 && bDay < 15) {
						printf("\nError: You have entered time data previous to the indroduce of Gregorian calendar.\n");
					}
				}
			}
			else {
				if (bMonth == 4 || bMonth == 6 || bMonth == 9 || bMonth == 11) {
					while ((bDay < 1 || bDay>30) || (bMonth < 10 && bYear == 1582)) {
						printf("\nDay? (1-30)\n");
						bDay = (int)getValue();
						if (bDay < 1 || bDay>30) {
							printf("\nError: You have entered an invalid day for months with 30 duration days.\n");
						}
						if (bMonth < 10 && bYear == 1582) {
							printf("\nError: You have entered time data previous to the indroduce of Gregorian calendar.\n");
						}
					}
				}
				else {
					if (bMonth == 2 && isLeapYear(bYear)) {
						while (bDay < 1 || bDay>29) {
							printf("\nDay? (1-29)\n");
							bDay = (int)getValue();
							if (bDay < 1 || bDay>29) {
								printf("\nError: You have entered a leap year, so February has 29 duration days.\n");
							}
						}
					}
					else {
						if (bMonth == 2 && !isLeapYear(bYear)) {
							while (bDay < 1 || bDay>28) {
								printf("\nDay? (1-28)\n");
								bDay = (int)getValue();
								if (bDay < 1 || bDay>28) {
									printf("\nError: You have entered a common year, so February has 28 duration days.\n");
								}
							}
						}
					}
				}
			}
			bHour = -1;
			while (bHour < 0 || bHour>23) {
				printf("\nHour? (0-23, i.e. Please consider the 24-hour clock.)\n");
				bHour = (int)getValue();
				if (bHour < 0 || bHour>23) {
					printf("\nError: The hour must be between 0 and 23, inclusively.\n");
				}
			}
			bMinutes = -1;
			while (bMinutes < 0 || bMinutes>59) {
				printf("\nMinute? (0-59)\n");
				bMinutes = (int)getValue();
				if (bMinutes < 0 || bMinutes>59) {
					printf("\nError: The minute must be between 0 and 59, inclusively.\n");
				}
			}
			bSeconds = -1;
			while (bSeconds < 0 || bSeconds>59) {
				printf("\nSecond? (0-59)\n");
				bSeconds = (int)getValue();
				if (bSeconds < 0 || bSeconds>59) {
					printf("\nError: The second must be between 0 and 59, inclusively.\n");
				}
			}
			printf("Enter the latter time data:");
			aYear = 0;
			while (aYear < 1582) {
				printf("\nYear? (1582 minimum)\n");
				aYear = (int)getValue();
				if (aYear < 1582) {
					printf("\nError: You have entered a year previous to the indroduce of Gregorian calendar.\n");
				}
			}
			aMonth = 0;
			while ((aMonth < 1 || aMonth>12) || (aYear == 1582 && aMonth < 10)) {
				printf("\nMonth? (1-12)\n");
				aMonth = (int)getValue();
				if ((aYear == 1582 && aMonth < 10)) {
					printf("\nError: You have entered time data previous to the indroduce of Gregorian calendar.\n");
				}
				if (aMonth < 0 || aMonth>12) {
					printf("\nError: You have entered an invalid month.\n");
				}
			}
			aDay = 0;
			if (aMonth == 1 || aMonth == 3 || aMonth == 5 || aMonth == 7 || aMonth == 8 || aMonth == 10 || aMonth == 12) {
				while ((aDay < 1 || aDay>31) || (aMonth == 10 && aYear == 1582 && aDay < 15)) {
					printf("\nDay? (1-31)\n");
					aDay = (int)getValue();
					if (aDay < 1 || aDay>31) {
						printf("\nError: You have entered an invalid day for months with 31 duration days.\n");
					}
					if (aMonth == 10 && aYear == 1582 && aDay < 15) {
						printf("\nError: You have entered time data previous to the indroduce of Gregorian calendar.\n");
					}
				}
			}
			else {
				if (aMonth == 4 || aMonth == 6 || aMonth == 9 || aMonth == 11) {
					while ((aDay < 1 || aDay>30) || (aMonth < 10 && aYear == 1582)) {
						printf("\nDay? (1-30)\n");
						aDay = (int)getValue();
						if (aDay < 1 || aDay>30) {
							printf("\nError: You have entered an invalid day for months with 30 duration days.\n");
						}
						if (aMonth < 10 && aYear == 1582) {
							printf("\nError: You have entered time data previous to the indroduce of Gregorian calendar.\n");
						}
					}
				}
				else {
					if (aMonth == 2 && isLeapYear(aYear)) {
						while (aDay < 1 || aDay>29) {
							printf("\nDay? (1-29)\n");
							aDay = (int)getValue();
							if (aDay < 1 || aDay>29) {
								printf("\nError: You have entered a leap year, so Fearuary has 29 duration days.\n");
							}
						}
					}
					else {
						if (aMonth == 2 && !isLeapYear(aYear)) {
							while (aDay < 1 || aDay>28) {
								printf("\nDay? (1-28)\n");
								aDay = (int)getValue();
								if (aDay < 1 || aDay>28) {
									printf("\nError: You have entered a common year, so February has 28 duration days.\n");
								}
							}
						}
					}
				}
			}
			aHour = -1;
			while (aHour < 0 || aHour>23) {
				printf("\nHour? (0-23, i.e. Please consider the 24-hour clock.)\n");
				aHour = (int)getValue();
				if (aHour < 0 || aHour>23) {
					printf("\nError: The hour must be between 0 and 23, inclusively.\n");
				}
			}
			aMinutes = -1;
			while (aMinutes < 0 || aMinutes>59) {
				printf("\nMinute? (0-59)\n");
				aMinutes = (int)getValue();
				if (aMinutes < 0 || aMinutes>59) {
					printf("\nError: The minute must be between 0 and 59, inclusively.\n");
				}
			}
			aSeconds = -1;
			while (aSeconds < 0 || aSeconds>59) {
				printf("\nSecond? (0-59)\n");
				aSeconds = (int)getValue();
				if (aSeconds < 0 || aSeconds>59) {
					printf("\nError: The second must be between 0 and 59, inclusively.\n");
				}
			}
		}
		int diffSeconds = 0, diffMinutes = 0, diffHours = 0, diffMonths = 0, diffYears = 0;
		int days = 0;
		int diffMinusDays = 0, diffPlusDays = 0;
		if (bSeconds != 0) {
			diffSeconds = 60 - bSeconds;
		}
		if (bMinutes != 0) {
			if (bSeconds != 0) {
				diffMinutes = 60 - bMinutes - 1;
			}
			else {
				diffMinutes = 60 - bMinutes;
			}
		}
		if (bHour != 0) {
			if (bSeconds != 0 || bMinutes != 0) {
				diffHours = 24 - bHour - 1;
			}
			else {
				diffHours = 24 - bHour;
			}
		}
		int k = bMonth;
		if ((bYear == aYear && bMonth < aMonth) || bYear != aYear) {
			if (bMonth == 1) {
				days = days + (31 - bDay);
			}
			if (bMonth == 2 && isLeapYear(bYear) == 1) {
				days = days + (29 - bDay);
			}
			if (bMonth == 2 && isLeapYear(bYear) == 0) {
				days = days + (28 - bDay);
			}
			if (bMonth == 3) {
				days = days + (31 - bDay);
			}
			if (bMonth == 4) {
				days = days + (30 - bDay);
			}
			if (bMonth == 5) {
				days = days + (31 - bDay);
			}
			if (bMonth == 6) {
				days = days + (30 - bDay);
			}
			if (bMonth == 7) {
				days = days + (31 - bDay);
			}
			if (bMonth == 8) {
				days = days + (31 - bDay);
			}
			if (bMonth == 9) {
				days = days + (30 - bDay);
			}
			if (bMonth == 10) {
				days = days + (31 - bDay);
			}
			if (bMonth == 11) {
				days = days + (30 - bDay);
			}
			if (bMonth == 12) {
				days = days + (31 - bDay);
			}
			diffMinusDays = days;
			for (k = bMonth + 1; (k <= 12 && aYear != bYear) || (k < aMonth && aYear == bYear); k++) {
				if (k == 1) {
					days = days + 31;
				}
				if (k == 2 && isLeapYear(bYear) == 1) {
					countLeapYears++;
					days = days + 29;
				}
				if (k == 2 && isLeapYear(bYear) == 0) {
					days = days + 28;
				}
				if (k == 3) {
					days = days + 31;
				}
				if (k == 4) {
					days = days + 30;
				}
				if (k == 5) {
					days = days + 31;
				}
				if (k == 6) {
					days = days + 30;
				}
				if (k == 7) {
					days = days + 31;
				}
				if (k == 8) {
					days = days + 31;
				}
				if (k == 9) {
					days = days + 30;
				}
				if (k == 10) {
					days = days + 31;
				}
				if (k == 11) {
					days = days + 30;
				}
				if (k == 12) {
					days = days + 31;
				}
			}
		}
		int diffDays = 0;
		if (bYear != aYear) {
			int i = bYear + 1;
			while (i < aYear) {
				diffYears++;
				if (isLeapYear(i) == 1) {
					days = days + 366;
				}
				else {
					days = days + 365;
				}
				i++;
			}
			for (k = 1; k < aMonth; k++) {
				if (k == 1) {
					days = days + 31;
				}
				if (k == 2 && isLeapYear(aYear) == 1) {
					days = days + 29;
					countLeapYears++;
				}
				if (k == 2 && isLeapYear(aYear) == 0) {
					days = days + 28;
				}
				if (k == 3) {
					days = days + 31;
				}
				if (k == 4) {
					days = days + 30;
				}
				if (k == 5) {
					days = days + 31;
				}
				if (k == 6) {
					days = days + 30;
				}
				if (k == 7) {
					days = days + 31;
				}
				if (k == 8) {
					days = days + 31;
				}
				if (k == 9) {
					days = days + 30;
				}
				if (k == 10) {
					days = days + 31;
				}
				if (k == 11) {
					days = days + 30;
				}
				if (k == 12) {
					days = days + 31;
				}
			}
		}
		if (days != 0) {
			days = days + aDay;
		}
		diffYears = abs(aYear - bYear);
		if (aMonth >= bMonth) {
			diffMonths = aMonth - bMonth;
		}
		else {
			if (aMonth < bMonth) {
				diffMonths = aMonth + 12 - bMonth;
			}
		}
		if (aMonth < bMonth) {
			diffYears--;
		}
		else {
			if (aMonth == bMonth && aDay < bDay) {
				diffYears--;
			}
		}
		if (aMonth == bMonth) {
			if (aDay < bDay) {
				diffMonths--;
			}
		}
		else {
			if (aMonth > bMonth) {
				if (aDay < bDay) {
					diffMonths--;
				}
			}
			else {
				if (aMonth < bMonth) {
					if (aDay < bDay) {
						diffMonths--;
					}
				}
			}
		}
		if (aMonth == bMonth) {
			if (aDay < bDay) {
				diffDays = diffMinusDays + aDay - countLeapYears;
			}
			else {
				diffDays = aDay - bDay - countLeapYears;
			}
		}
		else {
			if (aMonth > bMonth) {
				if (aDay < bDay) {
					diffDays = diffMinusDays + aDay - countLeapYears;
				}
				else {
					diffDays = aDay - bDay - countLeapYears;
				}
			}
			else {
				if (bMonth > aMonth) {
					if (aDay < bDay) {
						diffDays = diffMinusDays + aDay - countLeapYears;
					}
					else {
						diffDays = aDay - bDay - countLeapYears;
					}
				}
			}
		}
		if (days == 0) {
			days = diffDays;
		}
		int diffTime = diffHours * 3600 + diffMinutes * 60 + diffSeconds;
		int  aTime = aHour * 3600 + aMinutes * 60 + aSeconds;
		diffSeconds = diffTime + aTime;
		if (diffDays > 0) {
			diffDays = diffDays - diffSeconds / 86400;
		}
		int saveDays = days;
		days = days - diffSeconds / 86400;
		diffHours = (diffSeconds / 3600) % 24;
		diffSeconds = diffSeconds % 3600;
		diffMinutes = diffSeconds / 60;
		diffSeconds = diffSeconds % 60;
		diffYears = diffYears + diffMonths / 12;
		diffMonths = diffMonths % 12;
		days = saveDays;
		char report[DIM] = "";
		sprintf(report, "%s\nTime difference: %d years, %d months, %d days, %d hours, %d minutes and %d seconds\n", report, diffYears, diffMonths, diffDays, diffHours, diffMinutes, diffSeconds);
		sprintf(report, "%s\nTime difference: %d months, %d days, %d hours, %d minutes and %d seconds\n", report, diffYears * 12 + diffMonths, diffDays, diffHours, diffMinutes, diffSeconds);
		sprintf(report, "%s\nTime difference: %d days , %d hours, %d minutes and %d seconds\n", report, days, diffHours, diffMinutes, diffSeconds);
		sprintf(report, "%s\nTime difference: %d hours, %d minutes and %d seconds\n", report, diffHours + 24 * days, diffMinutes, diffSeconds);
		sprintf(report, "%s\nTime difference: %d minutes and %d seconds\n", report, diffHours * 60 + 1440 * days + diffMinutes, diffSeconds);
		char toCalc[1000] = "";
		sprintf(toCalc, "(%d*60+1440*%d+%d)*60+%d", diffHours, days, diffMinutes, diffSeconds);
		math_processor(toCalc);
		sprintf(report, "%s\nTime difference: %.0f seconds\n", report, resultR);
		sprintf(report, "%s\nTime difference: %d weeks and %d days, %d hours, %d minutes and %d seconds\n", report, days / 7, days % 7, diffHours, diffMinutes, diffSeconds);
		if (bYear != aYear) {
			sprintf(report, "%s\nTime difference: %.2f%% of a common year (365 days)", report, ((float)days / (float)365) *(float)100);
		}
		else {
			if (isLeapYear(aYear) == 1) {
				sprintf(report, "%s\nTime difference: %.2f%% of %d", report, ((float)days / (float)366) *(float)100, aYear);
			}
			else {
				sprintf(report, "%s\nTime difference: %.2f%% of %d", report, ((float)days / (float)365) *(float)100, aYear);
			}
		}
		puts(report);
		int optionF = -1;
		while (optionF != 0 && optionF != 1) {
			I_O = true;
			puts("\nExport result? (Yes -> 1 \\ No -> 0)");
			optionF = (int)getValue();
		}
		if (optionF == 1) {
			saveToReport(report);
		}
		toContinue = -1;
		while (toContinue != 0 && toContinue != 1) {
			I_O = true;
			printf("\nContinue? (Yes -> 1 / No -> 0)\n");
			toContinue = (int)getValue();
		}
	} while (toContinue == 1);
}

boolean isLeapYear(int year) {
	if (year % 400 == 0) {
		return true;
	}
	else {
		if (year % 4 == 0 && year % 100 != 0) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}