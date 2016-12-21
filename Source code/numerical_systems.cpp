

#include "stdafx.h"



void decimalToBinary(double decimal, char path[DIM], int bp) {
	FILE *open = NULL;
	int i = 0, j = 0, rest = 0, h = 0, res = 0, ct = 0, cou, c = 0;
	double decimal1 = 0, quotient = 2, quotient1 = 2, mult = 0, mul = 0, decimal2 = 0;
	double sN = 0, sN1 = 0, sN2 = 0;
	char binary[DIM] = "", binary2[DIM] = "", binaryexp[DIM] = "";
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\history.txt", atcPath);
	if (decimal >= 0) {
		sN = log10(decimal) / log10(2.0);
		sN1 = quo(sN);
		sN2 = pow(2.0, multi(sN));
	}
	else {
		if (decimal < 0) {
			decimal = decimal*-1;
			sN = log10(decimal) / log10(2.0);
			sN1 = quo(sN);
			sN2 = pow(2.0, multi(sN))*-1;
			decimal = decimal*-1;
		}
	}
	if (sN1 <= 5 && sN1 >= -4 || decimal == 0 || bp != -1) {
		decimal1 = decimal;
		if (decimal < 0) {
			c = 0;
			decimal1 = decimal1*-1;
			while (quotient1 > 1) {
				quotient1 = decimal1 / 2;
				decimal1 = quotient1;
				c++;
			}
			c++;
			while (c % 8 != 0) {
				c++;
			}
			decimal1 = pot(2.000, c, 1) + decimal;
		}
		while (quotient > 1) {
			quotient = decimal1 / 2;
			rest = (int)re(decimal1, 2);
			binary[i] = rest + '0';
			decimal1 = quotient;
			i++;
		}
		binary[i] = (char)quotient + '0'; i++;
		binary[i] = '\0';
		i--;
		while (i != -1) {
			binary2[j] = binary[i];
			i--;
			j++;
		}
		binary2[j] = '\0';
		mult = multi(decimal);
		if (mult < 0 && bp != 0) {
			mult = mult*-1;
		}
		if (mult > 0 && bp != 0) {
			i = 0;
			cou = 0;
			while (binary2[i] != '\0') { i++; }
			binary2[i] = '.';
			i++;
			while (res == 0) {
				mult = mult * 2;
				res = (int)quo(mult);
				binary2[i] = res + '0';
				mult = multi(mult);
				i++;
			}
			while (cou < 20 && bp == -1 || cou < bp - 1) {
				mult = mult * 2;
				res = (int)quo(mult);
				binary2[i] = res + '0';
				mult = multi(mult);
				i++;
				cou++;
			}
			binary2[i] = '\0';
		}
		if (binary2[0] == '0') {
			i = 0;
			while (binary2[i] != '\0') {
				binary2[i] = binary2[i + 1];
				i++;
			}
		}
		while (open == NULL) {
			open = fopen(path, "a+");
		}
		if (multi(decimal) == 0 || bp == 0) {
			if (decimal >= 0) {
				fprintf(open, "In binary=%s\n", binary2);
				if (isEqual(path, toOpen))
					printf("In binary=%s\n", binary2);
			}
			if (decimal < 0) {
				fprintf(open, "In binary=-%s\n", binary2);
				if (isEqual(path, toOpen))
					printf("In binary=-%s\n", binary2);
			}
		}
		else {
			for (i = 0; binary2[i] != '\0'; i++) {
			}
			i--;
			if (binary2[i] == '0') {
				while (binary2[i] == '0') {
					i--;
				}
				i++;
				binary2[i] = '\0';
			}
			if (decimal >= 0) {
				fprintf(open, "In binary=%s\n", binary2);
				if (isEqual(path, toOpen))
					printf("In binary=%s\n", binary2);
			}
			if (decimal < 0) {
				fprintf(open, "In binary=-%s\n", binary2);
				if (isEqual(path, toOpen))
					printf("In binary=-%s\n", binary2);
			}
		}
		fclose(open);
	}
	else {
		decimal = sN2;
		decimal1 = decimal;
		if (decimal < 0) {
			c = 0;
			decimal1 = decimal1*-1;
			while (quotient1 > 1) {
				quotient1 = decimal1 / 2;
				decimal1 = quotient1;
				c++;
			}
			c++;
			while (c % 8 != 0) {
				c++;
			}
			decimal1 = pot(2.000, c, 1) + decimal;
		}
		while (quotient > 1) {
			quotient = decimal1 / 2;
			rest = (int)re(decimal1, 2);
			binary[i] = rest + '0';
			decimal1 = quotient;
			i++;
		}
		binary[i] = (char)quotient + '0'; i++;
		binary[i] = '\0';
		i--;
		while (i != -1) {
			binary2[j] = binary[i];
			i--;
			j++;
		}
		binary2[j] = '\0';
		mult = multi(decimal);
		if (mult < 0) {
			mult = mult*-1;
		}
		if (mult != 0) {
			i = 0;
			cou = 0;
			while (binary2[i] != '\0') { i++; }
			binary2[i] = '.';
			i++;
			while (res == 0) {
				mult = mult * 2;
				res = (int)quo(mult);
				binary2[i] = res + '0';
				mult = multi(mult);
				i++;
			}
			while (cou < 20) {
				mult = mult * 2;
				res = (int)quo(mult);
				binary2[i] = res + '0';
				mult = multi(mult);
				i++;
				cou++;
			}
			binary2[i] = '\0';
		}
		if (binary2[0] == '0') {
			i = 0;
			while (binary2[i] != '\0') {
				binary2[i] = binary2[i + 1];
				i++;
			}
		}
		i = 0; j = 0; rest = 0; h = 0; res = 0; ct = 0; cou; c = 0;
		decimal1 = 0; quotient = 2; quotient1 = 2; mult = 0; mul = 0;
		binary[0] = '\0';
		decimal2 = sN1;
		decimal1 = decimal2;
		if (decimal2 < 0) {
			c = 0;
			decimal1 = decimal1*-1;
			while (quotient1 > 1) {
				quotient1 = decimal1 / 2;
				decimal1 = quotient1;
				c++;
			}
			c++;
			while (c % 8 != 0) {
				c++;
			}
			decimal1 = pot(2.000, c, 1) + decimal2;
		}
		while (quotient > 1) {
			quotient = decimal1 / 2;
			rest = (int)re(decimal1, 2);
			binary[i] = rest + '0';
			decimal1 = quotient;
			i++;
		}
		binary[i] = (char)quotient + '0'; i++;
		binary[i] = '\0';
		i--;
		while (i != -1) {
			binaryexp[j] = binary[i];
			i--;
			j++;
		}
		binaryexp[j] = '\0';
		mult = multi(decimal2);
		if (mult < 0) {
			mult = mult*-1;
		}
		if (mult > 0) {
			i = 0;
			cou = 0;
			while (binaryexp[i] != '\0') { i++; }
			binaryexp[i] = '.';
			i++;
			while (res == 0) {
				mult = mult * 2;
				res = (int)quo(mult);
				binaryexp[i] = res + '0';
				mult = multi(mult);
				i++;
			}
			while (cou < 20) {
				mult = mult * 2;
				res = (int)quo(mult);
				binaryexp[i] = res + '0';
				mult = multi(mult);
				i++;
				cou++;
			}
			binaryexp[i] = '\0';
		}
		if (binaryexp[0] == '0') {
			i = 0;
			while (binaryexp[i] != '\0') {
				binaryexp[i] = binaryexp[i + 1];
				i++;
			}
		}

		while (open == NULL) {
			open = fopen(path, "a+");
		}
		if (multi(decimal) == 0) {
			if (decimal >= 0 && decimal2 >= 0) {
				fprintf(open, "In binary=%sx10^%s\n", binary2, binaryexp);
				if (isEqual(path, toOpen))
					printf("In binary=%sx10^%s\n", binary2, binaryexp);
			}
			if (decimal < 0 && decimal2 < 0) {
				fprintf(open, "In binary=-%sx10^-%s\n", binary2, binaryexp);
				if (isEqual(path, toOpen))
					printf("In binary=-%sx10^-%s\n", binary2, binaryexp);
			}
			if (decimal >= 0 && decimal2 < 0) {
				fprintf(open, "In binary=%sx10^-%s\n", binary2, binaryexp);
				if (isEqual(path, toOpen))
					printf("In binary=%sx10^-%s\n", binary2, binaryexp);
			}
			if (decimal < 0 && decimal2 >= 0) {
				fprintf(open, "In binary=-%sx10^%s\n", binary2, binaryexp);
				if (isEqual(path, toOpen))
					printf("In binary=-%sx10^%s\n", binary2, binaryexp);
			}
		}
		else {
			for (i = 0; binary2[i] != '\0'; i++) {
			}
			i--;
			if (binary2[i] == '0') {
				while (binary2[i] == '0') {
					i--;
				}
				i++;
				binary2[i] = '\0';
			}
			if (decimal >= 0 && decimal2 >= 0) {
				fprintf(open, "In binary=%sx10^%s\n", binary2, binaryexp);
				if (isEqual(path, toOpen))
					printf("In binary=%sx10^%s\n", binary2, binaryexp);
			}
			if (decimal < 0 && decimal2 < 0) {
				fprintf(open, "In binary=-%sx10^-%s\n", binary2, binaryexp);
				if (isEqual(path, toOpen))
					printf("In binary=-%sx10^-%s\n", binary2, binaryexp);
			}
			if (decimal >= 0 && decimal2 < 0) {
				fprintf(open, "In binary=%sx10^-%s\n", binary2, binaryexp);
				if (isEqual(path, toOpen))
					printf("In binary=%sx10^-%s\n", binary2, binaryexp);
			}
			if (decimal < 0 && decimal2 >= 0) {
				fprintf(open, "In binary=-%sx10^%s\n", binary2, binaryexp);
				if (isEqual(path, toOpen))
					printf("In binary=-%sx10^%s\n", binary2, binaryexp);
			}
		}
		fclose(open);
	}
}

void decimalToOctal(double decimal, char path[DIM], int op) {
	FILE *open = NULL;
	char octal[DIM] = "", octal2[DIM] = "", octalexp[DIM] = "";
	double quotient, quotient1, decimal1, decimal2 = 0, mult, sN = 0, sN1 = 0, sN2 = 0;
	int c, j, i, rest, cou, res = 0;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\history.txt", atcPath);
	decimal1 = decimal; i = 0; j = 0; quotient = 8; quotient1 = 8;
	if (decimal >= 0) {
		sN = log10(decimal) / log10(8.0);
		sN1 = quo(sN);
		sN2 = pow(8.0, multi(sN));
	}
	else {
		if (decimal < 0) {
			decimal = decimal*-1;
			sN = log10(decimal) / log10(8.0);
			sN1 = quo(sN);
			sN2 = pow(8.0, multi(sN))*-1;
			decimal = decimal*-1;
		}
	}
	if (sN1 <= 5 && sN1 >= -4 || decimal == 0 || op != -1) {
		if (decimal < 0) {
			c = 0;
			decimal1 = decimal1*-1;
			while (quotient1 > 7) {
				quotient1 = decimal1 / 8;
				decimal1 = quotient1;
				c++;
			}
			c++;
			while (c % 8 != 0) {
				c++;
			}
			decimal1 = pot(8.000, c, 1) + decimal;
		}
		while (quotient > 7) {
			quotient = decimal1 / 8;
			rest = (int)re(decimal1, 8);
			octal[i] = rest + '0';
			decimal1 = quotient;
			i++;
		}
		octal[i] = (char)+'0'; i++;
		octal[i] = '\0';
		i--;
		while (i != -1) {
			octal2[j] = octal[i];
			i--;
			j++;
		}
		octal2[j] = '\0';
		mult = multi(decimal);
		if (mult < 0 && op != 0) {
			mult = mult*-1;
		}
		if (mult > 0 && op != 0) {
			i = 0;
			cou = 0;
			while (octal2[i] != '\0') { i++; }
			octal2[i] = '.';
			i++;
			while (res == 0) {
				mult = mult * 8;
				res = (int)quo(mult);
				octal2[i] = res + '0';
				mult = multi(mult);
				i++;
			}
			while (cou < 20 && op == -1 || cou < op - 1) {
				mult = mult * 8;
				res = (int)quo(mult);
				octal2[i] = res + '0';
				mult = multi(mult);
				i++;
				cou++;
			}
			octal2[i] = '\0';
		}
		if (octal2[0] == '0') {
			i = 0;
			while (octal2[i] != '\0') {
				octal2[i] = octal2[i + 1];
				i++;
			}
		}
		while (open == NULL) {
			open = fopen(path, "a+");
		}
		if (multi(decimal) == 0 || op == 0) {
			if (decimal >= 0) {
				fprintf(open, "In octal=%s\n", octal2);
				if (isEqual(path, toOpen))
					printf("In octal=%s\n", octal2);
			}
			if (decimal < 0) {
				fprintf(open, "In octal=-%s\n", octal2);
				if (isEqual(path, toOpen))
					printf("In octal=-%s\n", octal2);
			}
		}
		else {
			for (i = 0; octal2[i] != '\0'; i++) {
			}
			i--;
			if (octal2[i] == '0') {
				while (octal2[i] == '0') {
					i--;
				}
				i++;
				octal2[i] = '\0';
			}
			if (decimal >= 0) {
				fprintf(open, "In octal=%s\n", octal2);
				if (isEqual(path, toOpen))
					printf("In octal=%s\n", octal2);
			}
			if (decimal < 0) {
				fprintf(open, "In octal=-%s\n", octal2);
				if (isEqual(path, toOpen))
					printf("In octal=-%s\n", octal2);
			}
		}
		fclose(open);
	}
	else {
		decimal = sN2;
		decimal1 = decimal;
		if (decimal < 0) {
			c = 0;
			decimal1 = decimal1*-1;
			while (quotient1 > 7) {
				quotient1 = decimal1 / 8;
				decimal1 = quotient1;
				c++;
			}
			c++;
			while (c % 8 != 0) {
				c++;
			}
			decimal1 = pot(8.000, c, 1) + decimal;
		}
		while (quotient > 7) {
			quotient = decimal1 / 8;
			rest = (int)re(decimal1, 8);
			octal[i] = rest + '0';
			decimal1 = quotient;
			i++;
		}
		octal[i] = (char)quotient + '0'; i++;
		octal[i] = '\0';
		i--;
		while (i != -1) {
			octal2[j] = octal[i];
			i--;
			j++;
		}
		octal2[j] = '\0';
		mult = multi(decimal);
		if (mult < 0) {
			mult = mult*-1;
		}
		if (mult > 0) {
			i = 0;
			cou = 0;
			while (octal2[i] != '\0') { i++; }
			octal2[i] = '.';
			i++;
			while (res == 0) {
				mult = mult * 8;
				res = (int)quo(mult);
				octal2[i] = res + '0';
				mult = multi(mult);
				i++;
			}
			while (cou < 20) {
				mult = mult * 8;
				res = (int)quo(mult);
				octal2[i] = res + '0';
				mult = multi(mult);
				i++;
				cou++;
			}
			octal2[i] = '\0';
		}
		if (octal2[0] == '0') {
			i = 0;
			while (octal2[i] != '\0') {
				octal2[i] = octal2[i + 1];
				i++;
			}
		}
		octal[0] = '\0';
		quotient = 8; quotient1 = 8; mult = 0;
		c = 0; j = 0; i = 0; rest = 0; cou = 15; res = 0;

		decimal2 = sN1;
		decimal1 = decimal2;
		if (decimal2 < 0) {
			c = 0;
			decimal1 = decimal1*-1;
			while (quotient1 > 7) {
				quotient1 = decimal1 / 8;
				decimal1 = quotient1;
				c++;
			}
			c++;
			while (c % 8 != 0) {
				c++;
			}
			decimal1 = pot(8.000, c, 1) + decimal2;
		}
		while (quotient > 7) {
			quotient = decimal1 / 8;
			rest = (int)re(decimal1, 8);
			octal[i] = rest + '0';
			decimal1 = quotient;
			i++;
		}
		octal[i] = (char)quotient + '0'; i++;
		octal[i] = '\0';
		i--;
		while (i != -1) {
			octalexp[j] = octal[i];
			i--;
			j++;
		}
		octalexp[j] = '\0';

		mult = multi(decimal2);
		if (mult < 0) {
			mult = mult*-1;
		}
		if (mult > 0) {
			i = 0;
			cou = 0;
			while (octalexp[i] != '\0') { i++; }
			octalexp[i] = '.';
			i++;
			while (res == 0) {
				mult = mult * 8;
				res = (int)quo(mult);
				octalexp[i] = res + '0';
				mult = multi(mult);
				i++;
			}
			while (cou < 20) {
				mult = mult * 8;
				res = (int)quo(mult);
				octalexp[i] = res + '0';
				mult = multi(mult);
				i++;
				cou++;
			}
			octalexp[i] = '\0';
		}
		if (octalexp[0] == '0') {
			i = 0;
			while (octalexp[i] != '\0') {
				octalexp[i] = octalexp[i + 1];
				i++;
			}
		}
		while (open == NULL) {
			open = fopen(path, "a+");
		}
		if (multi(decimal) == 0) {
			if (decimal >= 0 && decimal2 >= 0) {
				fprintf(open, "In octal=%sx10^%s\n", octal2, octalexp);
				if (isEqual(path, toOpen))
					printf("In octal=%sx10^%s\n", octal2, octalexp);
			}
			if (decimal < 0 && decimal2 < 0) {
				fprintf(open, "In octal=-%sx10^-%s\n", octal2, octalexp);
				if (isEqual(path, toOpen))
					printf("In octal=-%sx10^-%s\n", octal2, octalexp);
			}
			if (decimal >= 0 && decimal2 < 0) {
				fprintf(open, "In octal=%sx10^-%s\n", octal2, octalexp);
				if (isEqual(path, toOpen))
					printf("In octal=%sx10^-%s\n", octal2, octalexp);
			}
			if (decimal < 0 && decimal2 >= 0) {
				fprintf(open, "In octal=-%sx10^%s\n", octal2, octalexp);
				if (isEqual(path, toOpen))
					printf("In octal=-%sx10^%s\n", octal2, octalexp);
			}
		}
		else {
			for (i = 0; octal2[i] != '\0'; i++) {
			}
			i--;
			if (octal2[i] == '0') {
				while (octal2[i] == '0') {
					i--;
				}
				i++;
				octal2[i] = '\0';
			}
			if (decimal >= 0 && decimal2 >= 0) {
				fprintf(open, "In octal=%sx10^%s\n", octal2, octalexp);
				if (isEqual(path, toOpen))
					printf("In octal=%sx10^%s\n", octal2, octalexp);
			}
			if (decimal < 0 && decimal2 < 0) {
				fprintf(open, "In octal=-%sx10^-%s\n", octal2, octalexp);
				if (isEqual(path, toOpen))
					printf("In octal=-%sx10^-%s\n", octal2, octalexp);
			}
			if (decimal >= 0 && decimal2 < 0) {
				fprintf(open, "In octal=%sx10^-%s\n", octal2, octalexp);
				if (isEqual(path, toOpen))
					printf("In octal=%sx10^-%s\n", octal2, octalexp);
			}
			if (decimal < 0 && decimal2 >= 0) {
				fprintf(open, "In octal=-%sx10^%s\n", octal2, octalexp);
				if (isEqual(path, toOpen))
					printf("In octal=-%sx10^%s\n", octal2, octalexp);
			}
		}
		fclose(open);
	}
}

void decimalToHexadecimal(double decimal, char path[DIM], int hp) {
	FILE *open = NULL;
	char hexadecimal[DIM] = "", hexadecimal2[DIM] = "", hexadecimalexp[DIM] = "";
	double decimal1 = decimal, decimal2 = 0, quotient = 16, quotient1 = 16, mult, sN = 0, sN1 = 0, sN2 = 0;
	int res = 0, cou = 0, c = 0, rest = 0, i = 0, j = 0;
	char toOpen[DIM] = "";
	sprintf(toOpen, "%s\\history.txt", atcPath);
	if (decimal >= 0) {
		sN = log10(decimal) / log10(16.0);
		sN1 = quo(sN);
		sN2 = pow(16.0, multi(sN));
	}
	else {
		if (decimal < 0) {
			decimal = decimal*-1;
			sN = log10(decimal) / log10(16.0);
			sN1 = quo(sN);
			sN2 = pow(16.0, multi(sN))*-1;
			decimal = decimal*-1;
		}
	}
	if (sN1 <= 5 && sN1 >= -4 || decimal == 0 || hp != -1) {
		if (decimal < 0) {
			c = 0;
			decimal1 = decimal1*-1;
			while (quotient1 > 15) {
				quotient1 = decimal1 / 16;
				decimal1 = quotient1;
				c++;
			}
			c++;
			while (c % 8 != 0) {
				c++;
			}
			decimal1 = pow(16.000, c) + decimal;
		}
		while (quotient > 15) {
			quotient = decimal1 / 16;
			rest = (int)re(decimal1, 16);
			if (rest < 10) {
				hexadecimal[i] = rest + '0';
			}
			if (rest >= 10) {
				if (rest == 10) {
					hexadecimal[i] = 'A';
				}
				if (rest == 11) {
					hexadecimal[i] = 'B';
				}
				if (rest == 12) {
					hexadecimal[i] = 'C';
				}
				if (rest == 13) {
					hexadecimal[i] = 'D';
				}
				if (rest == 14) {
					hexadecimal[i] = 'E';
				}
				if (rest == 15) {
					hexadecimal[i] = 'F';
				}
			}
			if (decimal < 1E10) {
				quotient = quo(quotient);
			}
			decimal1 = quotient;
			i++;
		}
		if (quotient < 10) {
			hexadecimal[i] = (char)quotient + '0';
		}
		if (quotient == 10) {
			hexadecimal[i] = 'A';
		}
		if (quotient == 11) {
			hexadecimal[i] = 'B';
		}
		if (quotient == 12) {
			hexadecimal[i] = 'C';
		}
		if (quotient == 13) {
			hexadecimal[i] = 'D';
		}
		if (quotient == 14) {
			hexadecimal[i] = 'E';
		}
		if (quotient == 15) {
			hexadecimal[i] = 'F';
		}
		i++;
		hexadecimal[i] = '\0';
		i--;
		while (i != -1) {
			hexadecimal2[j] = hexadecimal[i];
			i--;
			j++;
		}
		hexadecimal2[j] = '\0';

		mult = multi(decimal);
		if (mult < 0 && hp != 0) {
			mult = mult*-1;
		}
		if (mult > 0 && hp != 0) {
			i = 0;
			cou = 0;
			while (hexadecimal2[i] != '\0') { i++; }
			hexadecimal2[i] = '.';
			i++;
			while (res == 0) {
				mult = mult * 16;
				res = (int)quo(mult);
				if (res < 10) {
					hexadecimal2[i] = res + '0';
				}
				if (res >= 10) {
					if (res == 10) {
						hexadecimal2[i] = 'A';
					}
					if (res == 11) {
						hexadecimal2[i] = 'B';
					}
					if (res == 12) {
						hexadecimal2[i] = 'C';
					}
					if (res == 13) {
						hexadecimal2[i] = 'D';
					}
					if (res == 14) {
						hexadecimal2[i] = 'E';
					}
					if (res == 15) {
						hexadecimal2[i] = 'F';
					}
				}
				mult = multi(mult);
				i++;
			}
			while (cou < 20 && hp == -1 || cou < hp - 1) {
				mult = mult * 16;
				res = (int)quo(mult);
				if (res < 10) {
					hexadecimal2[i] = res + '0';
				}
				if (res >= 10) {
					if (res == 10) {
						hexadecimal2[i] = 'A';
					}
					if (res == 11) {
						hexadecimal2[i] = 'B';
					}
					if (res == 12) {
						hexadecimal2[i] = 'C';
					}
					if (res == 13) {
						hexadecimal2[i] = 'D';
					}
					if (res == 14) {
						hexadecimal2[i] = 'E';
					}
					if (res == 15) {
						hexadecimal2[i] = 'F';
					}
				}
				mult = multi(mult);
				i++;
				cou++;
			}
			hexadecimal2[i] = '\0';
		}
		if (hexadecimal2[0] == '0') {
			i = 0;
			while (hexadecimal2[i] != '\0') {
				hexadecimal2[i] = hexadecimal2[i + 1];
				i++;
			}
		}
		open = fopen(path, "a+");
		if (multi(decimal) == 0 || hp == 0) {
			if (decimal >= 0) {
				fprintf(open, "In hexadecimal=%s\n", hexadecimal2);
				if (isEqual(path, toOpen))
					printf("In hexadecimal=%s\n", hexadecimal2);
			}
			if (decimal < 0) {
				fprintf(open, "In hexadecimal=-%s\n", hexadecimal2);
				if (isEqual(path, toOpen))
					printf("In hexadecimal=-%s\n", hexadecimal2);
			}
		}
		else {
			for (i = 0; hexadecimal2[i] != '\0'; i++) {
			}
			i--;
			if (hexadecimal2[i] == '0') {
				while (hexadecimal2[i] == '0') {
					i--;
				}
				i++;
				hexadecimal2[i] = '\0';
			}
			if (decimal >= 0) {
				fprintf(open, "In hexadecimal=%s\n", hexadecimal2);
				if (isEqual(path, toOpen))
					printf("In hexadecimal=%s\n", hexadecimal2);
			}
			if (decimal < 0) {
				fprintf(open, "In hexadecimal=-%s\n", hexadecimal2);
				if (isEqual(path, toOpen))
					printf("In hexadecimal=-%s\n", hexadecimal2);
			}
		}
		fclose(open);
	}
	else {
		decimal = sN2;
		decimal1 = decimal;
		if (decimal < 0) {
			c = 0;
			decimal1 = decimal1*-1;
			while (quotient1 > 15) {
				quotient1 = decimal1 / 16;
				decimal1 = quotient1;
				c++;
			}
			c++;
			while (c % 8 != 0) {
				c++;
			}
			decimal1 = pow(16.000, c) + decimal;
		}
		while (quotient > 15) {
			quotient = decimal1 / 16;
			rest = (int)re(decimal1, 16);
			if (rest < 10) {
				hexadecimal[i] = rest + '0';
			}
			if (rest >= 10) {
				if (rest == 10) {
					hexadecimal[i] = 'A';
				}
				if (rest == 11) {
					hexadecimal[i] = 'B';
				}
				if (rest == 12) {
					hexadecimal[i] = 'C';
				}
				if (rest == 13) {
					hexadecimal[i] = 'D';
				}
				if (rest == 14) {
					hexadecimal[i] = 'E';
				}
				if (rest == 15) {
					hexadecimal[i] = 'F';
				}
			}
			if (decimal < 1E10) {
				quotient = quo(quotient);
			}
			decimal1 = quotient;
			i++;
		}
		if (quotient < 10) {
			hexadecimal[i] = (char)quotient + '0';
		}
		if (quotient == 10) {
			hexadecimal[i] = 'A';
		}
		if (quotient == 11) {
			hexadecimal[i] = 'B';
		}
		if (quotient == 12) {
			hexadecimal[i] = 'C';
		}
		if (quotient == 13) {
			hexadecimal[i] = 'D';
		}
		if (quotient == 14) {
			hexadecimal[i] = 'E';
		}
		if (quotient == 15) {
			hexadecimal[i] = 'F';
		}
		i++;
		hexadecimal[i] = '\0';
		i--;
		while (i != -1) {
			hexadecimal2[j] = hexadecimal[i];
			i--;
			j++;
		}
		hexadecimal2[j] = '\0';

		mult = multi(decimal);
		if (mult < 0) {
			mult = mult*-1;
		}
		if (mult > 0) {
			i = 0;
			cou = 0;
			while (hexadecimal2[i] != '\0') { i++; }
			hexadecimal2[i] = '.';
			i++;
			while (res == 0) {
				mult = mult * 16;
				res = (int)quo(mult);
				if (res < 10) {
					hexadecimal2[i] = res + '0';
				}
				if (res >= 10) {
					if (res == 10) {
						hexadecimal2[i] = 'A';
					}
					if (res == 11) {
						hexadecimal2[i] = 'B';
					}
					if (res == 12) {
						hexadecimal2[i] = 'C';
					}
					if (res == 13) {
						hexadecimal2[i] = 'D';
					}
					if (res == 14) {
						hexadecimal2[i] = 'E';
					}
					if (res == 15) {
						hexadecimal2[i] = 'F';
					}
				}
				mult = multi(mult);
				i++;
			}
			while (cou < 20) {
				mult = mult * 16;
				res = (int)quo(mult);
				if (res < 10) {
					hexadecimal2[i] = res + '0';
				}
				if (res >= 10) {
					if (res == 10) {
						hexadecimal2[i] = 'A';
					}
					if (res == 11) {
						hexadecimal2[i] = 'B';
					}
					if (res == 12) {
						hexadecimal2[i] = 'C';
					}
					if (res == 13) {
						hexadecimal2[i] = 'D';
					}
					if (res == 14) {
						hexadecimal2[i] = 'E';
					}
					if (res == 15) {
						hexadecimal2[i] = 'F';
					}
				}
				mult = multi(mult);
				i++;
				cou++;
			}
			hexadecimal2[i] = '\0';
		}
		if (hexadecimal2[0] == '0') {
			i = 0;
			while (hexadecimal2[i] != '\0') {
				hexadecimal2[i] = hexadecimal2[i + 1];
				i++;
			}
		}
		hexadecimal[0] = '\0';
		quotient = 16; quotient1 = 16; mult = 0;
		res = 0; cou = 0; c = 0; rest = 0; i = 0; j = 0;
		decimal2 = sN1;
		decimal1 = decimal2;

		if (decimal2 < 0) {
			c = 0;
			decimal1 = decimal1*-1;
			while (quotient1 > 15) {
				quotient1 = decimal1 / 16;
				decimal1 = quotient1;
				c++;
			}
			c++;
			while (c % 8 != 0) {
				c++;
			}
			decimal1 = pow(16.000, c) + decimal2;
		}
		while (quotient > 15) {
			quotient = decimal1 / 16;
			rest = (int)re(decimal1, 16);
			if (rest < 10) {
				hexadecimal[i] = rest + '0';
			}
			if (rest >= 10) {
				if (rest == 10) {
					hexadecimal[i] = 'A';
				}
				if (rest == 11) {
					hexadecimal[i] = 'B';
				}
				if (rest == 12) {
					hexadecimal[i] = 'C';
				}
				if (rest == 13) {
					hexadecimal[i] = 'D';
				}
				if (rest == 14) {
					hexadecimal[i] = 'E';
				}
				if (rest == 15) {
					hexadecimal[i] = 'F';
				}
			}
			if (decimal < 1E10) {
				quotient = quo(quotient);
			}
			decimal1 = quotient;
			i++;
		}
		if (quotient < 10) {
			hexadecimal[i] = (char)quotient + '0';
		}
		if (quotient == 10) {
			hexadecimal[i] = 'A';
		}
		if (quotient == 11) {
			hexadecimal[i] = 'B';
		}
		if (quotient == 12) {
			hexadecimal[i] = 'C';
		}
		if (quotient == 13) {
			hexadecimal[i] = 'D';
		}
		if (quotient == 14) {
			hexadecimal[i] = 'E';
		}
		if (quotient == 15) {
			hexadecimal[i] = 'F';
		}
		i++;
		hexadecimal[i] = '\0';
		i--;
		while (i != -1) {
			hexadecimalexp[j] = hexadecimal[i];
			i--;
			j++;
		}
		hexadecimalexp[j] = '\0';

		mult = multi(decimal2);
		if (mult < 0) {
			mult = mult*-1;
		}
		if (mult > 0) {
			i = 0;
			cou = 0;
			while (hexadecimalexp[i] != '\0') { i++; }
			hexadecimalexp[i] = '.';
			i++;
			while (res == 0) {
				mult = mult * 16;
				res = (int)quo(mult);
				if (res < 10) {
					hexadecimalexp[i] = res + '0';
				}
				if (res >= 10) {
					if (res == 10) {
						hexadecimalexp[i] = 'A';
					}
					if (res == 11) {
						hexadecimalexp[i] = 'B';
					}
					if (res == 12) {
						hexadecimalexp[i] = 'C';
					}
					if (res == 13) {
						hexadecimalexp[i] = 'D';
					}
					if (res == 14) {
						hexadecimalexp[i] = 'E';
					}
					if (res == 15) {
						hexadecimalexp[i] = 'F';
					}
				}
				mult = multi(mult);
				i++;
			}
			while (cou < 20) {
				mult = mult * 16;
				res = (int)quo(mult);
				if (res < 10) {
					hexadecimalexp[i] = res + '0';
				}
				if (res >= 10) {
					if (res == 10) {
						hexadecimalexp[i] = 'A';
					}
					if (res == 11) {
						hexadecimalexp[i] = 'B';
					}
					if (res == 12) {
						hexadecimalexp[i] = 'C';
					}
					if (res == 13) {
						hexadecimalexp[i] = 'D';
					}
					if (res == 14) {
						hexadecimalexp[i] = 'E';
					}
					if (res == 15) {
						hexadecimalexp[i] = 'F';
					}
				}
				mult = multi(mult);
				i++;
				cou++;
			}
			hexadecimalexp[i] = '\0';
		}
		if (hexadecimalexp[0] == '0') {
			i = 0;
			while (hexadecimalexp[i] != '\0') {
				hexadecimalexp[i] = hexadecimalexp[i + 1];
				i++;
			}
		}
		while (open == NULL) {
			open = fopen(path, "a+");
		}
		if (multi(decimal) == 0) {
			if (decimal >= 0 && decimal2 >= 0) {
				fprintf(open, "In hexadecimal=%sx10^%s\n", hexadecimal2, hexadecimalexp);
				if (isEqual(path, toOpen))
					printf("In hexadecimal=%sx10^%s\n", hexadecimal2, hexadecimalexp);
			}
			if (decimal < 0 && decimal2 < 0) {
				fprintf(open, "In hexadecimal=-%sx10^-%s\n", hexadecimal2, hexadecimalexp);
				if (isEqual(path, toOpen))
					printf("In hexadecimal=-%sx10^-%s\n", hexadecimal2, hexadecimalexp);
			}
			if (decimal >= 0 && decimal2 < 0) {
				fprintf(open, "In hexadecimal=-%sx10^-%s\n", hexadecimal2, hexadecimalexp);
				if (isEqual(path, toOpen))
					printf("In hexadecimal=%sx10^-%s\n", hexadecimal2, hexadecimalexp);
			}
			if (decimal < 0 && decimal2 >= 0) {
				fprintf(open, "In hexadecimal=-%sx10^%s\n", hexadecimal2, hexadecimalexp);
				if (isEqual(path, toOpen))
					printf("In hexadecimal=-%sx10^%s\n", hexadecimal2, hexadecimalexp);
			}
		}
		else {
			for (i = 0; hexadecimal2[i] != '\0'; i++) {
			}
			i--;
			if (hexadecimal2[i] == '0') {
				while (hexadecimal2[i] == '0') {
					i--;
				}
				i++;
				hexadecimal2[i] = '\0';
			}
			if (decimal >= 0 && decimal2 >= 0) {
				fprintf(open, "In hexadecimal=%sx10^%s\n", hexadecimal2, hexadecimalexp);
				if (isEqual(path, toOpen))
					printf("In hexadecimal=%sx10^%s\n", hexadecimal2, hexadecimalexp);
			}
			if (decimal < 0 && decimal2 < 0) {
				fprintf(open, "In hexadecimal=-%sx10^-%s\n", hexadecimal2, hexadecimalexp);
				if (isEqual(path, toOpen))
					printf("In hexadecimal=-%sx10^-%s\n", hexadecimal2, hexadecimalexp);
			}
			if (decimal >= 0 && decimal2 < 0) {
				fprintf(open, "In hexadecimal=%sx10^-%s\n", hexadecimal2, hexadecimalexp);
				if (isEqual(path, toOpen))
					printf("In hexadecimal=%sx10^-%s\n", hexadecimal2, hexadecimalexp);
			}
			if (decimal < 0 && decimal2 >= 0) {
				fprintf(open, "In hexadecimal=-%sx10^%s\n", hexadecimal2, hexadecimalexp);
				if (isEqual(path, toOpen))
					printf("In hexadecimal=-%sx10^%s\n", hexadecimal2, hexadecimalexp);
			}
		}
		fclose(open);
	}
}

double binaryToDecimal(char binary[DIM]) {
	char binary2[DIM] = "", floa[DIM] = "";
	double decimal = 0, negDec = 0, flo = 0;
	int count = 0, j = 0, i = 0, f = 0, g = 0, h = 0, count1 = 0, d = 0, k = 0;
	while (binary[d] != '\0'&&binary[d] != '.') { d++; }
	d--;
	if (binary[0] == '-') {
		while (binary[k] != '\0') {
			binary[k] = binary[k + 1];
			k++;
		}
		k = 0;
		while (binary[k] == '0') {
			d--;
			k++;
		}
		negDec = pot(2.000, d*1.000, 1);
	}
	while (binary[i] != '\0'&&binary[i] != '.') {
		i++;
	}
	i--;
	count = i;
	h = i;
	while (binary[h] != '\0') {
		floa[g] = binary[h + 2];
		g++;
		h++;
	}
	g--;
	count1 = g;
	while (i >= 0) {
		binary2[j] = binary[i];
		i--;
		j++;
	}
	binary2[j] = '\0';
	while (i <= count) {
		if (binary2[i] == '1') {
			decimal = decimal + pot(2.000, i, 1);
		}
		i++;
	}
	h = -1;
	g = 0;
	while (g <= count1) {
		if (floa[g] == '1') {
			flo = flo + pot(2.000, h, 1);
		}
		g++;
		h--;
	}
	decimal = decimal + flo;
	if (negDec > 0) {
		decimal = (decimal - negDec);
		if (flo > 0) {
			double f = fl(decimal);
			f = 1 - f;
			decimal = returnDeciPart(decimal) - f;
		}
	}
	return decimal;
}

double octalToDecimal(char octal[DIM]) {
	char octal2[DIM], floa[DIM] = "";
	int count = 0, j = 0, i = 0, h = 0, g = 0, count1, d = 0, k = 0;
	double decimal = 0, flo = 0, negDec = 0;
	while (octal[d] != '\0'&&octal[d] != '.') { d++; }
	d--;
	if (octal[0] == '-') {
		while (octal[k] != '\0') {
			octal[k] = octal[k + 1];
			k++;
		}
		k = 0;
		while (octal[k] == '0') {
			d--;
			k++;
		}
		negDec = pot(8.000, d*1.000, 1);
	}
	while (octal[i] != '\0'&&octal[i] != '.') {
		i++;
	}
	i--;
	count = i;
	h = i;
	while (octal[h] != '\0') {
		floa[g] = octal[h + 2];
		g++;
		h++;
	}
	g--;
	count1 = g;
	while (i >= 0) {
		octal2[j] = octal[i];
		i--;
		j++;
	}
	octal2[j] = '\0';
	while (i <= count) {
		if (octal2[i] == '1') {
			decimal = decimal + pot(8.000, i, 1);
		}
		if (octal2[i] == '2') {
			decimal = decimal + 2 * pot(8.000, i, 1);
		}
		if (octal2[i] == '3') {
			decimal = decimal + 3 * pot(8.000, i, 1);
		}
		if (octal2[i] == '4') {
			decimal = decimal + 4 * pot(8.000, i, 1);
		}
		if (octal2[i] == '5') {
			decimal = decimal + 5 * pot(8.000, i, 1);
		}
		if (octal2[i] == '6') {
			decimal = decimal + 6 * pot(8.000, i, 1);
		}
		if (octal2[i] == '7') {
			decimal = decimal + 7 * pot(8.000, i, 1);
		}

		i++;
	}
	h = -1;
	g = 0;
	while (g <= count1) {
		if (floa[g] == '1') {
			flo = flo + pot(8.000, h, 1);
		}
		if (floa[g] == '2') {
			flo = flo + 2 * pot(8.000, h, 1);
		}
		if (floa[g] == '3') {
			flo = flo + 3 * pot(8.000, h, 1);
		}
		if (floa[g] == '4') {
			flo = flo + 4 * pot(8.000, h, 1);
		}
		if (floa[g] == '5') {
			flo = flo + 5 * pot(8.000, h, 1);
		}
		if (floa[g] == '6') {
			flo = flo + 6 * pot(8.000, h, 1);
		}
		if (floa[g] == '7') {
			flo = flo + 7 * pot(8.000, h, 1);
		}
		g++;
		h--;
	}
	decimal = decimal + flo;
	if (negDec > 0) {
		decimal = (decimal - negDec);
		if (flo > 0) {
			double f = fl(decimal);
			f = 1 - f;
			decimal = returnDeciPart(decimal) - f;
		}
	}
	return decimal;
}

double hexadecimalToDecimal(char hexadecimal[DIM]) {
	char hexadecimal2[DIM], floa[DIM];
	int count = 0, j = 0, i = 0, h = 0, g = 0, count1 = 0, k = 0, d = 0;
	double decimal = 0, flo = 0, negDec = 0;
	while (hexadecimal[d] != '\0'&&hexadecimal[d] != '.') { d++; }
	d--;
	if (hexadecimal[0] == '-') {
		while (hexadecimal[k] != '\0') {
			hexadecimal[k] = hexadecimal[k + 1];
			k++;
		}
		k = 0;
		while (hexadecimal[k] == '0') {
			d--;
			k++;
		}
		negDec = pot(16.000, d*1.000, 1);
	}
	while (hexadecimal[i] != '\0'&&hexadecimal[i] != '.') {
		if (hexadecimal[i] == 'a') {
			hexadecimal[i] = 'A';
		}
		if (hexadecimal[i] == 'b') {
			hexadecimal[i] = 'B';
		}
		if (hexadecimal[i] == 'c') {
			hexadecimal[i] = 'C';
		}
		if (hexadecimal[i] == 'd') {
			hexadecimal[i] = 'D';
		}
		if (hexadecimal[i] == 'e') {
			hexadecimal[i] = 'E';
		}
		if (hexadecimal[i] == 'f') {
			hexadecimal[i] = 'F';
		}
		i++;

	}
	i--;
	count = i;
	h = i;
	while (hexadecimal[h] != '\0') {
		floa[g] = hexadecimal[h + 2];
		g++;
		h++;
	}
	g--;
	count1 = g;

	while (i >= 0) {
		hexadecimal2[j] = hexadecimal[i];
		i--;
		j++;
	}
	hexadecimal2[j] = '\0';
	while (i <= count) {
		if (hexadecimal2[i] == '1') {
			decimal = decimal + pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == '2') {
			decimal = decimal + 2 * pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == '3') {
			decimal = decimal + 3 * pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == '4') {
			decimal = decimal + 4 * pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == '5') {
			decimal = decimal + 5 * pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == '6') {
			decimal = decimal + 6 * pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == '7') {
			decimal = decimal + 7 * pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == '8') {
			decimal = decimal + 8 * pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == '9') {
			decimal = decimal + 9 * pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == 'A') {
			decimal = decimal + 10 * pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == 'B') {
			decimal = decimal + 11 * pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == 'C') {
			decimal = decimal + 12 * pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == 'D') {
			decimal = decimal + 13 * pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == 'E') {
			decimal = decimal + 14 * pot(16.000, i, 1);
		}
		if (hexadecimal2[i] == 'F') {
			decimal = decimal + 15 * pot(16.000, i, 1);
		}

		i++;
	}
	h = -1;
	g = 0;
	while (g <= count1) {
		if (floa[g] == '1') {
			flo = flo + pot(16.000, h, 1);
		}
		if (floa[g] == '2') {
			flo = flo + 2 * pot(16.000, h, 1);
		}
		if (floa[g] == '3') {
			flo = flo + 3 * pot(16.000, h, 1);
		}
		if (floa[g] == '4') {
			flo = flo + 4 * pot(16.000, h, 1);
		}
		if (floa[g] == '5') {
			flo = flo + 5 * pot(16.000, h, 1);
		}
		if (floa[g] == '6') {
			flo = flo + 6 * pot(16.000, h, 1);
		}
		if (floa[g] == '7') {
			flo = flo + 7 * pot(16.000, h, 1);
		}
		if (floa[g] == '8') {
			flo = flo + 8 * pot(16.000, h, 1);
		}
		if (floa[g] == '9') {
			flo = flo + 9 * pot(16.000, h, 1);
		}
		if (floa[g] == 'A') {
			flo = flo + 10 * pot(16.000, h, 1);
		}
		if (floa[g] == 'B') {
			flo = flo + 11 * pot(16.000, h, 1);
		}
		if (floa[g] == 'C') {
			flo = flo + 12 * pot(16.000, h, 1);
		}
		if (floa[g] == 'D') {
			flo = flo + 13 * pot(16.000, h, 1);
		}
		if (floa[g] == 'E') {
			flo = flo + 14 * pot(16.000, h, 1);
		}
		if (floa[g] == 'F') {
			flo = flo + 15 * pot(16.000, h, 1);
		}
		g++;
		h--;
	}
	decimal = decimal + flo;
	if (negDec > 0) {
		decimal = (negDec - decimal)*-1;
		if (flo > 0) {
			double f = fl(decimal);
			f = 1 - f;
			decimal = returnDeciPart(decimal) - f;
		}
	}
	return decimal;
}