

#include "stdafx.h"

double initialProcessor(char arithTrig[DIM], double result) {
	int rasf = abs((int)strlen(arithTrig));
	while (arithTrig[rasf - 2] == '+'&&arithTrig[rasf - 1] == '0') {
		rasf = rasf - 2;
		arithTrig[rasf] = '\0';
	}
	if (verbose == 1 && solving) {
		printf("\n\n==> initialProcessor <==\n\nExpression: %s", arithTrig);
	}
	if (strlen(arithTrig) == 0) {
		return 0;
	}
	char arTrig[DIM] = "", trigon[DIM] = "", trig[DIM] = "", paRect[DIM] = "", cN[DIM] = "", ex[DIM] = "", art[DIM] = "";
	int parent[DIM], facto = 0, sig[DIM], s = 0, rectPar = 0, h = 0, i = 0, rePar = 0, so = 0, j = 0, g = 0, count = 0, e = 0, d = 0, th = 0, f = 0, trigo = 1, trigono = 0, co = 0, k = 0, l = 0, tr = 0, pa = 0, paren = 1, pare = 0, tg = 0, p = 0, a = 0, c = 1, r = 0, iN = 0, iL = 0;
	double triArith[DIM], triArithI[DIM], exp = 1, result1, result2, amplitude = 1;
	for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
		triArith[s] = 0;
		triArithI[s] = 0;
		sig[s] = -1;
	}
	for (i = 0; arithTrig[i] != '\0'; i++) {
		if (arithTrig[i] == '[' || arithTrig[i] == '{') {
			arithTrig[i] = '(';
		}
		if (arithTrig[i] == ']' || arithTrig[i] == '}') {
			arithTrig[i] = ')';
		}
		if (arithTrig[i] == '^'&&arithTrig[i + 1] == '-') {
			arithTrig[i + 1] = '_';
		}
		if (arithTrig[i] == 'E'&&arithTrig[i + 1] == '_') {
			arithTrig[i + 1] = '-';
		}
		if ((arithTrig[i] == 'B' || arithTrig[i] == 'O' || arithTrig[i] == 'H') && arithTrig[i + 1] == '_') {
			arithTrig[i + 1] = '-';
		}
	}
	arithTrig[i] = '+'; arithTrig[i + 1] = '('; arithTrig[i + 2] = '0'; arithTrig[i + 3] = ')'; arithTrig[i + 4] = '\0';
	for (s = 0; arithTrig[s] != '\0'; s++) {
		if (arithTrig[s] == '+'&&arithTrig[s - 1] == 'E'&&arithTrig[s - 2] != 'P') {
			r = s;
			s--;
			while (arithTrig[s] != '*'&&arithTrig[s] != '/'&&arithTrig[s] != '^'&&arithTrig[s] != '+' && (arithTrig[s] != '-'&&arithTrig[s - 1] != 'H') && arithTrig[s] != 'H') {
				s--;
			}
			s--;
			if (arithTrig[s] != 'H') {
				int k = r;
				while (arithTrig[k + 1] != '\0') {
					arithTrig[k] = arithTrig[k + 1];
					k++;
				}
				arithTrig[k] = '\0';
			}
			s = r;
		}
	}
	char paTrig[DIM] = "";
	for (s = 0; arithTrig[s] != '\0'; s++) {
		paTrig[s] = arithTrig[s];
	}
	paTrig[s] = '\0';
	s = 0;
	for (s; paTrig[s] != '\0'; s++) {
		if ((paTrig[s] == 'E' || paTrig[s] == 'P') && (s == 0 || paTrig[s - 1] == '_' || paTrig[s - 1] == '*' || paTrig[s - 1] == '/' || paTrig[s - 1] == '^' || paTrig[s - 1] == '+' || (paTrig[s - 1] == '-'&&paTrig[s - 2] != 'H') || paTrig[s - 1] == '(')) {
			arithTrig[s] = '1';
			for (s; paTrig[s] != '\0'; s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; arithTrig[s] != '\0'; s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; paTrig[s] != '\0'; s++) {
		if ((paTrig[s] == 'i'&&paTrig[s - 1] == 'p' || paTrig[s] == 'e' || paTrig[s] == ')' || arithTrig[s] == 'a' || arithTrig[s] == 'c' || arithTrig[s] == 'd' || arithTrig[s] == 'f' || arithTrig[s] == 'g' || arithTrig[s] == 'h' || arithTrig[s] == 'j' || arithTrig[s] == 'k' || arithTrig[s] == 'm' || arithTrig[s] == 'n' || arithTrig[s] == 'o' || arithTrig[s] == 'p' || arithTrig[s] == 'q' || arithTrig[s] == 'r' || arithTrig[s] == 's' || arithTrig[s] == 't' || arithTrig[s] == 'u' || arithTrig[s] == 'w' || arithTrig[s] == 'v' || arithTrig[s] == 'y' || arithTrig[s] == 'z' || arithTrig[s] == 'G' || arithTrig[s] == 'I' || arithTrig[s] == 'J' || arithTrig[s] == 'K' || arithTrig[s] == 'L' || arithTrig[s] == 'M' || arithTrig[s] == 'N' || arithTrig[s] == 'O' || arithTrig[s] == 'Q' || arithTrig[s] == 'R' || arithTrig[s] == 'S' || arithTrig[s] == 'T' || arithTrig[s] == 'U' || arithTrig[s] == 'V' || arithTrig[s] == 'Y' || arithTrig[s] == 'Z') && (paTrig[s + 1] == 'E' || paTrig[s + 1] == 'P')) {
			s++;
			arithTrig[s] = '1';
			for (s; paTrig[s] != '\0'; s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; arithTrig[s] != '\0'; s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	int u = 0;
	for (u = 0; arithTrig[u] != '\0'; u++) {
		paTrig[u] = arithTrig[u];
	}
	paTrig[u] = '\0';
	u = 0;
	for (u; paTrig[u] != '\0'; u++) {
		if (verifyLetter(paTrig[u]) == 0) {
			while (verifyLetter(paTrig[u]) == 0 && paTrig[u] != '\0') {
				u++;
			}
		}
		if (verifyLetter(paTrig[u]) == 1 && firstLetterVariable(paTrig[u]) == 0) {
			while (verifyLetter(paTrig[u]) == 1) {
				u++;
			}
		}
		if (firstLetterVariable(paTrig[u]) == 1 && firstLetterVariable(paTrig[u - 1]) == 0 && paTrig[u + 1] != 'i') {
			u++;
			while (verifyLetter(paTrig[u]) == 1) {
				u++;
			}
			if (paTrig[u] != '\\'&&paTrig[u] != '*'&&paTrig[u] != '+'&&paTrig[u] != '-'&&paTrig[u] != '/'&&paTrig[u] != '^'&&paTrig[u] != '!'&&paTrig[u] != ')') {
				double check = 0;
				if (verifyLetter(paTrig[u - 1]) == 1) {
					int z = u - 1, v = 0;
					char toVal[DIM] = "";
					while (verifyLetter(paTrig[z]) == 1) {
						z--;
					}
					z++;
					while (verifyLetter(paTrig[z]) == 1) {
						toVal[v] = paTrig[z];
						z++; v++;
					}
					toVal[v] = '?'; toVal[v + 1] = '\0';
					check = functionProcessor(toVal, 0, 0, 0);
				}
				if (check != 0.5) {
					arithTrig[u] = '*';
					for (u; paTrig[u] != '\0'; u++) {
						arithTrig[u + 1] = paTrig[u];
					}
					arithTrig[u + 1] = '\0';
					u = 0;
					for (u = 0; arithTrig[u] != '\0'; u++) {
						paTrig[u] = arithTrig[u];
					}
					paTrig[u] = '\0';
					u = 0;
				}
			}
		}
	}
	s = 0;
	for (s; paTrig[s] != '\0'; s++) {
		if (paTrig[s] == ')'&&paTrig[s + 1] == '(') {
			s++;
			arithTrig[s] = '*';
			for (s; paTrig[s] != '\0'; s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; arithTrig[s] != '\0'; s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; paTrig[s] != '\0'; s++) {
		if ((arithTrig[s] == 'G' || arithTrig[s] == 'I' || arithTrig[s] == 'J' || arithTrig[s] == 'K' || arithTrig[s] == 'L' || arithTrig[s] == 'M' || arithTrig[s] == 'N' || arithTrig[s] == 'O' || arithTrig[s] == 'P' || arithTrig[s] == 'Q' || arithTrig[s] == 'R' || arithTrig[s] == 'S' || arithTrig[s] == 'T' || arithTrig[s] == 'U' || arithTrig[s] == 'V' || arithTrig[s] == 'X' || arithTrig[s] == 'Y' || arithTrig[s] == 'Z' || arithTrig[s] == 'a' || arithTrig[s] == 'c' || arithTrig[s] == 'd' || arithTrig[s] == 'f' || arithTrig[s] == 'g' || arithTrig[s] == 'h' || arithTrig[s] == 'j' || arithTrig[s] == 'k' || arithTrig[s] == 'm' || arithTrig[s] == 'n' || arithTrig[s] == 'o' || arithTrig[s] == 'p' || arithTrig[s] == 'q' || arithTrig[s] == 'r' || arithTrig[s] == 's' || arithTrig[s] == 't' || arithTrig[s] == 'u' || arithTrig[s] == 'w' || arithTrig[s] == 'v' || arithTrig[s] == 'y' || arithTrig[s] == 'z') && (paTrig[s + 1] == '1'&&paTrig[s + 2] == 'E')) {
			s++;
			arithTrig[s] = '*';
			for (s; paTrig[s] != '\0'; s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; arithTrig[s] != '\0'; s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; paTrig[s] != '\0'; s++) {
		if ((paTrig[s] == '1' || paTrig[s] == '2' || paTrig[s] == '3' || paTrig[s] == '4' || paTrig[s] == '5' || paTrig[s] == '6' || paTrig[s] == '7' || paTrig[s] == '8' || paTrig[s] == '9' || paTrig[s] == '0' || paTrig[s] == 'i'&&paTrig[s + 1] != 'e'&&paTrig[s - 1] == 'p' || (paTrig[s - 1] == 'v'&&paTrig[s - 2] == 'l'&&paTrig[s - 3] == 'o'&&paTrig[s - 4] == 's'&&paTrig[s + 1] == 'r') == false && paTrig[s] == 'e'&&paTrig[s - 1] != 'c'&&paTrig[s - 1] != 'd'&&paTrig[s - 1] != 'r'&&paTrig[s - 1] != 's'&&paTrig[s - 1] != 'i'&&paTrig[s + 2] != 't' || paTrig[s] == ')') && (paTrig[s + 1] == '(' || paTrig[s + 1] == 'a' || paTrig[s + 1] == 's' || paTrig[s + 1] == 'c' || paTrig[s + 1] == 't' || paTrig[s + 1] == 'l' || paTrig[s + 1] == 'p' || paTrig[s + 1] == 'e' || paTrig[s + 1] == 'r'&&paTrig[s + 2] != 'r' || paTrig[s + 1] == 'd' || paTrig[s + 1] == 'q' || paTrig[s + 1] == 'g'&&paTrig[s - 1] != 'd')) {
			s++;
			arithTrig[s] = '*';
			for (s; paTrig[s] != '\0'; s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; arithTrig[s] != '\0'; s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; paTrig[s] != '\0'; s++) {
		if ((paTrig[s] == '1' || paTrig[s] == '2' || paTrig[s] == '3' || paTrig[s] == '4' || paTrig[s] == '5' || paTrig[s] == '6' || paTrig[s] == '7' || paTrig[s] == '8' || paTrig[s] == '9' || paTrig[s] == '0' || paTrig[s] == 'p' || paTrig[s] == 'e' || verifyLetter(paTrig[s]) == 1 && paTrig[s] != 'b'&&paTrig[s] != 'D') && (paTrig[s - 1] == ')')) {
			arithTrig[s] = '*';
			for (s; paTrig[s] != '\0'; s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; arithTrig[s] != '\0'; s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; paTrig[s] != '\0'; s++) {
		if ((paTrig[s + 1] == '1' || paTrig[s + 1] == '2' || paTrig[s + 1] == '3' || paTrig[s + 1] == '4' || paTrig[s + 1] == '5' || paTrig[s + 1] == '6' || paTrig[s + 1] == '7' || paTrig[s + 1] == '8' || paTrig[s + 1] == '9' || paTrig[s + 1] == '0' || paTrig[s + 1] == 'p' || paTrig[s + 1] == 'e') && (paTrig[s - 1] == 'p'&&paTrig[s] == 'i'&&paTrig[s + 1] != 'e' || paTrig[s] == 'e'&&paTrig[s - 1] != 'i')) {
			s++;
			arithTrig[s] = '*';
			for (s; paTrig[s] != '\0'; s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; arithTrig[s] != '\0'; s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; paTrig[s] != '\0'; s++) {
		if (paTrig[s] == '_' && (paTrig[s + 1] == '(' || paTrig[s + 1] == 'r'&&paTrig[s + 2] == 'e'&&paTrig[s + 3] == 's')) {
			arithTrig[s + 1] = '1'; arithTrig[s + 2] = '*'; s++;
			for (s; paTrig[s] != '\0'; s++) {
				arithTrig[s + 2] = paTrig[s];
			}
			arithTrig[s + 2] = '\0';
			s = 0;
			for (s = 0; arithTrig[s] != '\0'; s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; paTrig[s] != '\0'; s++) {
		if ((paTrig[s - 2] == 'r'&&paTrig[s - 1] == 'e'&&paTrig[s] == 's'&&paTrig[s + 2] != '('&&paTrig[s + 1] != '!'&&verifyLetter(paTrig[s + 1]) == 0) && (paTrig[s + 1] != '+'&&paTrig[s + 1] != '-'&&paTrig[s + 1] != '*'&&paTrig[s + 1] != '/'&&paTrig[s + 1] != '^'&&paTrig[s + 1] != ')'&&paTrig[s + 1] != 'b')) {
			s++;
			arithTrig[s] = '*';
			for (s; paTrig[s] != '\0'; s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; arithTrig[s] != '\0'; s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; paTrig[s] != '\0'; s++) {
		if ((paTrig[s] == 'e' || paTrig[s - 1] == 'p'&&paTrig[s] == 'i') && (paTrig[s + 1] == 'p'&&paTrig[s + 2] == 'i' || paTrig[s + 1] == 'e')) {
			s++;
			arithTrig[s] = '*';
			for (s; paTrig[s] != '\0'; s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; arithTrig[s] != '\0'; s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	s = 0;
	for (s; paTrig[s] != '\0'; s++) {
		if (paTrig[s + 1] == '_'&&paTrig[s] != '\\'&&paTrig[s] != ';'&&paTrig[s] != '+'&&paTrig[s] != '-'&&paTrig[s] != '*'&&paTrig[s] != '/'&&paTrig[s] != '^'&&paTrig[s] != '(' && (paTrig[s] != 'D'&&paTrig[s - 1] != 't'&&paTrig[s - 2] != 'r') && (paTrig[s] != 'b'&&paTrig[s - 1] != 'g'&&paTrig[s - 2] != 'o'&&paTrig[s - 3] != 'l')) {
			s++;
			arithTrig[s] = '*';
			for (s; paTrig[s] != '\0'; s++) {
				arithTrig[s + 1] = paTrig[s];
			}
			arithTrig[s + 1] = '\0';
			s = 0;
			for (s = 0; arithTrig[s] != '\0'; s++) {
				paTrig[s] = arithTrig[s];
			}
			paTrig[s] = '\0';
			s = 0;
		}
	}
	for (s = 0; s < abs((int)strlen(arithTrig)); s++) {
		parent[s] = 0;
	}
	int cp = 0, mark = 0;
	c = 0; d = 0; k = 0; l = 0; h = 0;
	for (s = 0; arithTrig[s] != '\0'&&s < abs((int)strlen(arithTrig)); s++) {
		if (arithTrig[s] == '(') {
			d = 0;
			c++;
			parent[s] = c;
			d = 1;
			k = c;
		}
		else {
			if (arithTrig[s] == ')') {
				d = 0;
				h = 0;
				l = 2;
				do {
					l = 0;
					h = 0;
					while (h < abs((int)strlen(arithTrig))) {
						if (parent[h] == k) {
							l++;
						}
						if (l == 2) {
							l = 0;
							k--;
						}
						h++;
					}
				} while (l == 2);
				h = 0;
				while (l != 1 && h < abs((int)strlen(arithTrig))) {
					h = 0;
					l = 0;
					while (h < abs((int)strlen(arithTrig))) {
						if (parent[h] == k) {
							l++;
						}
						if (l == 2) {
							k--;
							h = 0;
							l = 0;
						}
						h++;
					}
				}
				parent[s] = k;
			}
			else {
				parent[s] = 0;
			}
		}
	}
	int klp = s;
	arithTrig[s] = '\0';
	int curPar = 0, cur = 0;
	for (i = 0; arithTrig[i] != '\0'; i++) {
		if (arithTrig[i] == '(' || arithTrig[i] == ')') {
			curPar = 1;
		}
	}
	arithTrig[i] = '\0';
	if (curPar == 0) {
		result1 = arithSolver(arithTrig, result);
		return result1;
	}
	a = 0;
	int de = 0, b = 0, ju = 0;
	c = 0;
	char pas[DIM] = "";
	int se = 0;
	int thj = 0;
	if (curPar == 1) {
		for (i = 0; i < abs((int)strlen(arithTrig)); i++) {
			int jk = 0;
			char op[DIM] = "";
			while (parent[i] < 1 && i <= klp && i < DIM) {
				if (arithTrig[i] == '_' && (arithTrig[i + 1] == 'g' || arithTrig[i + 1] == 's' || arithTrig[i + 1] == 'c' || arithTrig[i + 1] == 't' || arithTrig[i + 1] == 'a' || arithTrig[i + 1] == 'l' || arithTrig[i + 1] == 'd' || arithTrig[i + 1] == 'r') || arithTrig[i] == 'q' || arithTrig[i] == 's' || arithTrig[i] == 'c' || arithTrig[i] == 't' || arithTrig[i] == 'a' || arithTrig[i] == 'r' && (arithTrig[i + 3] == 't'&&arithTrig[i + 4] != 'g'&&arithTrig[i + 4] != 'a' || arithTrig[i + 1] == 'a'&&arithTrig[i + 2] == 'd' || arithTrig[i + 1] == 't'&&arithTrig[i + 2] == 'D') || arithTrig[i] == 'd' || arithTrig[i] == 'l' || arithTrig[i] == 'g') {
					if (arithTrig[i] == '_') {
						thj = 1;
					}
					if (arithTrig[i - 1] == '1' || arithTrig[i - 1] == '2' || arithTrig[i - 1] == '3' || arithTrig[i - 1] == '4' || arithTrig[i - 1] == '5' || arithTrig[i - 1] == '6' || arithTrig[i - 1] == '7' || arithTrig[i - 1] == '8' || arithTrig[i - 1] == '9' || arithTrig[i - 1] == '0' || arithTrig[i - 1] == 'i' || arithTrig[i - 1] == 'e' || arithTrig[i - 1] == ')') {
						jk = 1;
					}ju = 0;
					while (arithTrig[i] != '('&&arithTrig[i] != '\0') {
						if ((arithTrig[i] == 'b'&&arithTrig[i - 1] != 'c'&&arithTrig[i - 1] != 'a') || arithTrig[i] == 'D') {
							op[ju] = arithTrig[i];
							ju++; i++;
							while ((arithTrig[i] == 'b'&&arithTrig[i + 1] == '(') == false && (arithTrig[i] == 'D'&&arithTrig[i + 1] == '(') == false && arithTrig[i] != '\0') {
								op[ju] = arithTrig[i];
								ju++; i++;
							}
						}
						op[ju] = arithTrig[i];
						ju++; i++;
					}
					op[ju] = '\0';
				}
				else {
					a = 0; if (arithTrig[i] == '_'&&arithTrig[i + 1] != 's'&&arithTrig[i + 1] != 'c'&&arithTrig[i + 1] != 't'&&arithTrig[i + 1] != 'a'&&arithTrig[i + 1] != 'l'&&arithTrig[i + 1] != 'd'&&arithTrig[i + 1] != 'r'&&arithTrig[i + 1] != 'g') {
						pas[a] = arithTrig[i]; a++; i++;
					}
					while (arithTrig[i] != '+'&&arithTrig[i] != '-'&&arithTrig[i] != '*'&&arithTrig[i] != '/'&&arithTrig[i] != '^'&&arithTrig[i] != '!') {
						pas[a] = arithTrig[i];
						a++;
						i++;
						if (arithTrig[i] == '-'&&arithTrig[i - 1] == 'E' || arithTrig[i] == '-'&&arithTrig[i - 1] == 'O' || arithTrig[i] == '-'&&arithTrig[i - 1] == 'B' || arithTrig[i] == '-'&&arithTrig[i - 1] == 'H') {
							pas[a] = arithTrig[i];
							a++;
							i++;
						}
					}
				}
				pas[a] = '\0';
				if (jk == 1) {
					arTrig[c] = '*';
				}
				if (arithTrig[i] == '+' || arithTrig[i] == '-' || arithTrig[i] == '*' || arithTrig[i] == '/' || arithTrig[i] == '^' || arithTrig[i] == '!') {
					arTrig[c] = arithTrig[i]; c++;
				}
				if (strlen(pas) > 0) {
					triArith[b] = arithSolver(pas, result);
					triArithI[b] = resultI;
					pas[0] = '\0';
					b++;
				}
				i++;
				if (strlen(op) > 0) {
					i--;
				}
			}
			pas[a] = '\0';
			cur = parent[i];
			j = i;
			if (parent[i] == cur) {
				i = j;
				a = 0;
				i++;
				while (parent[i] != cur && i < abs((int)strlen(arithTrig))) {
					pas[a] = arithTrig[i];
					a++; i++;
				}
				pas[a] = '\0';
				int kl = 0;
				for (de = 0; pas[de] != '\0'; de++) {
					if (pas[de] == '(' || pas[de] == ')') {
						kl = 1;
					}
				}
				a = 0;
				if (kl == 0) {
					renamer(pas);
					sprintf(pas, "%s", expressionF);
					if (isContained("det", op)) {
						startDetProcessing(pas);
						triArith[b] = resultR;
						triArithI[b] = resultI;
						if (op[0] == '_') {
							triArith[b] = triArith[b] * -1;
							triArithI[b] = triArithI[b] * -1;
							sig[b] = 0;
						}
					}
					else {
						if (isContained("strlen", op)) {
							triArith[b] = (double)strlength(pas);
							triArithI[b] = 0;
						}
						else {
							if (isContained("countoccurrences", op)) {
								if (countOccurrences("\\", arithTrig) == 1) {
									renamer(pas);
									sprintf(pas, "%s", expressionF);
									int p = 0, q = 0;
									char string[DIM] = "";
									char to_find[DIM] = "";
									while (pas[p] != '\\') {
										to_find[p] = pas[p];
										p++;
									}
									to_find[p] = '\0';
									renamer(to_find);
									sprintf(to_find, "%s", expressionF);
									p++;
									q = 0;
									while (pas[p] != '\0') {
										string[q] = pas[p];
										p++; q++;
									}
									string[q] = '\0';
									renamer(string);
									sprintf(string, "%s", expressionF);
									stringVariableToString(to_find);
									sprintf(to_find, "%s", variableSTring);
									stringVariableToString(string);
									sprintf(string, "%s", variableSTring);
									triArith[b] = (double)countOccurrences(to_find, string);
									triArithI[b] = 0;
								}
								else {
									puts("\nError: Please use a \"\\\" to separate the variables.\n");
								}
							}
							else {
								if (isContained("calc", op)) {
									renamer(pas);
									sprintf(pas, "%s", expressionF);
									stringVariableToString(pas);
									sprintf(pas, "%s", variableSTring);
									calcNow(pas, 0, 0);
									triArith[b] = resultR;
									triArithI[b] = resultI;;
								}
								else {
									triArith[b] = arithSolver(pas, result);
									sprintf(expressionF, pas);
									triArithI[b] = resultI;
									sig[b] = 1;
									pas[0] = '\0';
									ju = 0;
									if (strlen(op) > 0) {
										if (op[3] == 't' && (op[2] == 's' || op[2] == 'o'&&op[1] != 'c')) {
											resultI = triArithI[b]; resultR = triArithI[b - 1];
											triArith[b - 1] = functionProcessor(op, triArith[b], triArith[b - 1], rf);
											triArith[b] = 0;
											triArithI[b - 1] = resultI;
											triArithI[b] = 0;
											arTrig[b - 1] = '+';
										}
										else {
											triArith[b] = functionProcessor(op, triArith[b], amplitude, rf);
											triArithI[b] = resultI;
										}
										if (thj == 1) { thj = 0; sig[b] = 0; }
										else {
											sig[b] = 1;
										}
										pas[0] = '\0';
										ju = 0;
									}
								}
							}
						}
					}
				}
				if (kl == 1) {
					renamer(pas);
					sprintf(pas, "%s", expressionF);
					if (isContained("solver", op)) {
						retrySolver = false; retrySolver_2 = false; retrySolver_3 = false; equation_solver = true;
						poly = true;
						replaceTimes = 0;
						rtIndex = 0;
						sprintf(roots, ""), sprintf(answers, "");
						triArith[b] = solver(pas);
						rtIndex = 0;
						sprintf(roots, ""), sprintf(answers, "");
						equation_solver = false;
						triArithI[b] = resultI;
						if (op[0] == '_') {
							triArith[b] = triArith[b] * -1;
							triArithI[b] = triArithI[b] * -1;
							sig[b] = 0;
						}
					}
					else {
						if (isContained("det", op)) {
							startDetProcessing(pas);
							triArith[b] = resultR;
							triArithI[b] = resultI;
							if (op[0] == '_') {
								triArith[b] = triArith[b] * -1;
								triArithI[b] = triArithI[b] * -1;
								sig[b] = 0;
							}
						}
						else {
							if (isContained("strlen", op)) {
								triArith[b] = (double)strlength(pas);
								triArithI[b] = 0;
							}
							else {
								if (isContained("countoccurrences", op)) {
									if (countOccurrences("\\", arithTrig) == 1) {
										renamer(pas);
										sprintf(pas, "%s", expressionF);
										int p = 0, q = 0;
										char string[DIM] = "";
										char to_find[DIM] = "";
										while (pas[p] != '\\') {
											to_find[p] = pas[p];
											p++;
										}
										to_find[p] = '\0';
										renamer(to_find);
										sprintf(to_find, "%s", expressionF);
										p++;
										q = 0;
										while (pas[p] != '\0') {
											string[q] = pas[p];
											p++; q++;
										}
										string[q] = '\0';
										renamer(string);
										sprintf(string, "%s", expressionF);
										stringVariableToString(to_find);
										sprintf(to_find, "%s", variableSTring);
										stringVariableToString(string);
										sprintf(string, "%s", variableSTring);
										triArith[b] = (double)countOccurrences(to_find, string);
										triArithI[b] = 0;
									}
									else {
										puts("\nError: Please use a \"\\\" to separate the variables.\n");
									}
								}
								else {
									if (isContained("calc", op)) {
										renamer(pas);
										sprintf(pas, "%s", expressionF);
										stringVariableToString(pas);
										sprintf(pas, "%s", variableSTring);
										calcNow(pas, 0, 0);
										triArith[b] = resultR;
										triArithI[b] = resultI;;
									}
									else {
										triArith[b] = initialProcessor(pas, result);
										sprintf(expressionF, pas);
										triArithI[b] = resultI;
										sig[b] = 1;
										char pas[DIM] = "";
										if (strlen(op) > 0) {
											resultI = triArithI[b];
											triArith[b] = functionProcessor(op, triArith[b], amplitude, rf);
											triArithI[b] = resultI;
											if (thj == 1) { thj = 0; sig[b] = 0; }
											else {
												sig[b] = 1;
											}
											pas[0] = '\0';
										}
										ju = 0;
									}
								}
							}
						}
					}
				}
				b++;
			}
		}
		arTrig[c] = '=';
	}
	int negFact = 0;
	for (s = 0; s < c; s++) {
		if (arTrig[s] == '!') {
			if (triArith[s] < 0) {
				negFact = 1;
			}
			while (arTrig[s] == '!') {
				triArith[s] = fact(abs(triArith[s]));
				while (s < c) {
					arTrig[s] = arTrig[s + 1];
					s++;
				}
				s = 0;
			}
			if (negFact == 1) {
				triArith[s] = triArith[s] * -1;
			}
		}
	}
	a = 0;
	int fr;
	so = 0;
	int ca = 0;
	double asdf = 0, asdfI = 0;
	for (so = 0; so < c; so++) {
		int sa = so;
		int b = 0;
		if (arTrig[so] == '^'&&arTrig[so + 1] == '^') {
			while (arTrig[so] == '^'&&a != 1) {
				if (arTrig[so + 1] != '^'&&arTrig[so - 1] == '^'&&a != 2) {
					asdf = triArith[so + 1];
					asdfI = triArithI[so + 1];
					if (sig[so] == -1) {
						if ((triArith[so] < 0 || triArithI[so] < 0) && !equationSolverRunning) {
							sig[so] = 0;
						}
						else { sig[so] = 1; }
					}
					exponentiation(triArith[so], triArithI[so], asdf, asdfI, sig[so]);
					asdf = resultR;
					asdfI = resultI;
					triArith[so + 1] = 1;
					triArith[so] = 1;
					triArithI[so + 1] = 0;
					triArithI[so] = 0;
					arTrig[so] = '*';
					so--;
					a = 2;
				}
				else {
					if (arTrig[so + 1] == '^'&&a == 0) {
						so++;
						fr = so;
					}
					else {
						if (a == 2) {
							while (a != 1) {
								if (sig[so] == -1) {
									if ((triArith[so] < 0 || triArithI[so] < 0) && !equationSolverRunning) {
										sig[so] = 0;
									}
									else { sig[so] = 1; }
								}
								exponentiation(triArith[so], triArithI[so], asdf, asdfI, sig[so]);
								asdf = resultR;
								asdfI = resultI;
								triArith[so] = 1; triArithI[so] = 0;
								arTrig[so] = '*';
								so--;
								if (arTrig[so] != '^') {
									a = 1;
									so = fr++;
								}
							}
						}
					}
				}
				if (a == 1) {
					triArith[sa] = asdf; a = 0;
					triArithI[sa] = asdfI;
				}
			}
		}
		else {
			if (arTrig[so] == '^'&&arTrig[so + 1] != '^') {
				while (arTrig[so] == '^') {
					if (sig[sa] == -1) {
						if ((triArith[sa] < 0 || triArithI[sa] < 0) && !equationSolverRunning) {
							sig[sa] = 0;
						}
						else { sig[sa] = 1; }
					}
					exponentiation(triArith[sa], triArithI[sa], triArith[so + 1], triArithI[so + 1], sig[sa]);
					triArith[sa] = resultR; triArithI[sa] = resultI;
					triArith[so + 1] = 1; triArithI[so + 1] = 0;
					arTrig[so] = '*';
					so = so + 1;
				}
			}
		}
	}
	char simplified[DIM] = "";
	int RF = 0;
	for (RF = 0; RF < c; RF++) {
		if (triArith[RF] > 0 && triArithI[RF] < 0) {
			sprintf(simplified, "%s(%G%Gi)%c", simplified, triArith[RF], triArithI[RF], arTrig[RF]);
		}
		else {
			if (triArith[RF] < 0 && triArithI[RF] > 0) {
				sprintf(simplified, "%s(%G+%Gi)%c", simplified, triArith[RF], triArithI[RF], arTrig[RF]);
			}
			else {
				if (triArith[RF] < 0 && triArithI[RF] < 0) {
					sprintf(simplified, "%s(%G%Gi)%c", simplified, triArith[RF], triArithI[RF], arTrig[RF]);
				}
				else {
					if (triArith[RF] == 0 && triArithI[RF] == 0) {
						sprintf(simplified, "%s%G%c", simplified, triArith[RF], arTrig[RF]);
					}
					else {
						if (triArith[RF] == 0 && triArithI[RF] != 0) {
							sprintf(simplified, "%s%Gi%c", simplified, triArithI[RF], arTrig[RF]);
						}
						else {
							if (triArith[RF] != 0 && triArithI[RF] == 0) {
								sprintf(simplified, "%s%G%c", simplified, triArith[RF], arTrig[RF]);
							}
							else {
								sprintf(simplified, "%s(%G+%Gi)%c", simplified, triArith[RF], triArithI[RF], arTrig[RF]);
							}
						}
					}
				}
			}
		}
	}
	rasf = abs((int)strlen(simplified));
	while (simplified[rasf - 1] == '+'&&simplified[rasf] == '0') {
		rasf = rasf - 2;
		simplified[rasf] = '\0';
	}
	rasf = abs((int)strlen(simplified));
	if (simplified[rasf - 1] == '+') {
		simplified[rasf - 1] = '\0';
	}
	if (verbose == 1 && solving) {
		printf("\nSimplified expression by initialProcessor: %s\n\n", simplified);
	}
	for (so = 0; so < c; so++) {
		int sa = so;
		while (arTrig[so] == '/') {
			division(triArith[sa], triArithI[sa], triArith[so + 1], triArithI[so + 1]);
			triArith[sa] = resultR; triArithI[sa] = resultI;
			triArith[so + 1] = 1; triArithI[so + 1] = 0;
			arTrig[so] = '*';
			so++;
		}
	}
	for (so = 0; so < c; so++) {
		int sa = so;
		while (arTrig[so] == '*') {
			multiplication(triArith[sa], triArithI[sa], triArith[so + 1], triArithI[so + 1]);
			triArith[sa] = resultR; triArithI[sa] = resultI;
			triArith[so + 1] = 1; triArithI[so + 1] = 0;
			arTrig[so] = '*';
			so++;
		}
	}
	char func[DIM] = "";
	int lo = 0;
	for (j = 0; j < c; j++) {
		if (j == 0) {
			result1 = triArith[0];
			result2 = triArithI[0];
		}
		if (arTrig[j] == '^') {
			exponentiation(result1, result2, triArith[j + 1], triArithI[j + 1], 1);
			result1 = resultR;
			result2 = resultI;
		}
		if (arTrig[j] == '*') {
			multiplication(result1, result2, triArith[j + 1], triArithI[j + 1]);
			result1 = resultR;
			result2 = resultI;
		}
		if (arTrig[j] == '/') {
			division(result1, result2, triArith[j + 1], triArithI[j + 1]);
			result1 = resultR;
			result2 = resultI;
		}
		if (arTrig[j] == '-') {
			subtraction(result1, result2, triArith[j + 1], triArithI[j + 1]);
			result1 = resultR;
			result2 = resultI;
		}
		if (arTrig[j] == '+') {
			sum(result1, result2, triArith[j + 1], triArithI[j + 1]);
			result1 = resultR;
			result2 = resultI;
		}
	}
	resultR = result1;
	resultI = result2;
	round_complex();
	result1 = resultR;
	result2 = resultI;
	return result1;
}

double arithSolver(char trigon1[DIM], double result) {
	if (isEqual("0", trigon1)) {
		resultR = 0;
		resultI = 0;
		return 0;
	}
	int rasf = abs((int)strlen(trigon1));
	while (trigon1[rasf - 2] == '+'&&trigon1[rasf - 1] == '0') {
		rasf = rasf - 2;
		trigon1[rasf] = '\0';
	}
	if (verbose == 1 && solving) {
		printf("\n\n==> arithSolver <==\n\nExpression: %s", trigon1);
	}
	resultR = 0; resultI = 0;
	int i = 0, negImag = 0, j = 0, e = 0, f = 0, h = 0, so = 0, sa = 0, n = 0, c = 0, sig[DIM], sign = 0, s = 0, facto = 0, y = 0, sif = 0, res = 0, v = 0;
	char number2[DIM] = "", ex[DIM] = "", trigon[DIM] = "", amp[DIM] = "", prefCalc[10] = "";
	double exp = 1, ampl[DIM], amplI[DIM], result1 = 0, result2 = 0, fa = 0;
	for (i = 0; trigon1[i] != '\0'; i++) {
		ampl[i] = 0; amplI[i] = 0;
	}
	if (trigon1[i - 1] != '=') {
		trigon1[i] = '='; trigon1[i + 1] = '\0';
	}
	i = 0;
	for (i = 0; trigon1[i] != '\0'; i++) {
		if (trigon1[i] == '-' && (trigon1[i - 1] == 'B' || trigon1[i - 1] == 'O' || trigon1[i - 1] == 'H') && (trigon1[i - 2] == '_' || trigon1[i - 2] == '+' || trigon1[i - 2] == '-' || trigon1[i - 2] == '*' || trigon1[i - 2] == '/' || trigon1[i - 2] == '^' || i - 1 == 0)) {
			trigon1[i] = '_';
		}
	}
	int si = 0;
	j = 0;
	for (i = 0; trigon1[i] != '\0'; i++) {
		if (trigon1[i] != '*'&&trigon1[i] != '+'&&trigon1[i] != '-'&&trigon1[i] != '/'&&trigon1[i] != '^'&&trigon1[i] != '=') {
			if (trigon1[i] == '_') {
				number2[j] = trigon1[i];
				j++; i++;
			}
			if ((trigon1[i] == 'B' || trigon1[i] == 'O' || trigon1[i] == 'H') && trigon1[i + 1] == '-') {
				number2[j] = trigon1[i];
				j++; i++;
				number2[j] = trigon1[i];
				j++; i++;
				number2[j] = trigon1[i];
				j++; i++;
				while (trigon1[i] != '*'&&trigon1[i] != '+'&&trigon1[i] != '-'&&trigon1[i] != '/'&&trigon1[i] != '^'&&trigon1[i] != '=') {
					number2[j] = trigon1[i];
					j++; i++;
				}
				number2[j] = '\0';
			}
			while (trigon1[i] != '*'&&trigon1[i] != '+'&&trigon1[i] != '-'&&trigon1[i] != '/'&&trigon1[i] != '^'&&trigon1[i] != '=') {
				if (((trigon1[i] == 'B' || trigon1[i] == 'O' || trigon1[i] == 'H') && trigon1[i + 1] != '-' && trigon1[i + 1] != '+'&&trigon1[i + 1] != '*'&&trigon1[i + 1] != '/'&&trigon1[i + 1] != '^'&&trigon1[i + 1] != '=') || (trigon1[i] == 'E'&&trigon1[i + 1] != '=')) {
					number2[j] = trigon1[i];
					number2[j + 1] = trigon1[i + 1];
					j = j + 2; i = i + 2;
					while (trigon1[i] != '*'&&trigon1[i] != '+'&&trigon1[i] != '-'&&trigon1[i] != '/'&&trigon1[i] != '^'&&trigon1[i] != '=') {
						if (trigon1[i] == '=') { number2[j] = '\0'; j++; i++; sif = 1; }
						number2[j] = trigon1[i];
						j++; i++;
					}
				}
				else {
					number2[j] = trigon1[i];
					j++; i++;
				}
			}
			i--;
			if (sif == 0) {
				number2[j] = '.';
				number2[j + 1] = '0';
				number2[j + 2] = '\0';
			}
		}
		int complex = 0;
		if (number2[0] == 'i') {
			complex = 1;
			for (y = 0; number2[y + 1] != '\0'; y++) {
				number2[y] = number2[y + 1];
			}
			number2[y] = '\0';
		}
		if (number2[0] == '_'&&number2[1] == 'i'&&number2[2] == '1') {
			complex = 1;
			for (y = 0; number2[y + 1] != '\0'; y++) {
				number2[y] = number2[y + 1];
			}
			number2[y] = '\0';
			negImag = 1;
		}
		if (number2[strlen(number2) - 4] != 'p'&&number2[strlen(number2) - 3] == 'i') {
			complex = 1;
			for (y = abs((int)strlen(number2)) - 3; number2[y + 1] != '\0'; y++) {
				number2[y] = number2[y + 1];
			}
			number2[y] = '\0';
		}
		for (y = 0; number2[y] != '\0'; y++) {
			if (number2[y] == '=') {
				number2[y] = '\0';
				break;
			}
		}
		for (y = 0; number2[y] != '\0'; y++) {
			if (number2[y] == '!') {
				facto++;
			}
		}
		if (facto > 0) {
			y = 0;
			while (number2[y] != '!') {
				y++;
			}
			number2[y] = '.'; number2[y + 1] = '0'; number2[y + 2] = '\0';
		}
		v = 0;
		for (j = 0; number2[j] != '\0'; j++) {
			if (number2[j] == 'P') {
				y = j;
				while (number2[j] != '.') {
					prefCalc[v] = number2[j];
					v++; j++;
				}
				prefCalc[v] = '\0';
				number2[y] = '.'; number2[y + 1] = '0'; number2[y + 2] = '\0';
			}
		}
		if (number2[0] == '#') {
			res = 1;
			for (y = 0; number2[y + 1] != '\0'&&number2[y + 1] != 'E'; y++) {
				number2[y] = number2[y + 1];
			}
			number2[y] = '\0';
			ampl[n] = convertToNumber(number2);
			ampl[n] = ans[(int)ampl[n]];
			amplI[n] = convertToNumber(number2);
			amplI[n] = ansI[(int)amplI[n]];
			complex = 2;
			y++;
			if (number2[y] == 'E') {
				number2[0] = '1';
				j = 1;
				while (number2[y] != '\0') {
					number2[j] = number2[y];
					j++; y++;
				}
				number2[j] = '\0';
				ampl[n] = ampl[n] * convertToNumber(number2);
			}
			number2[0] = '\0';
		}
		if (number2[0] == '_'&&number2[1] == '#') {
			res = 1;
			for (y = 0; number2[y + 2] != '\0'&&number2[y + 2] != 'E'; y++) {
				number2[y] = number2[y + 2];
			}
			number2[y] = '\0';
			ampl[n] = convertToNumber(number2);
			ampl[n] = ans[(int)ampl[n]] * -1;
			amplI[n] = convertToNumber(number2);
			amplI[n] = ansI[(int)amplI[n]] * -1;
			y = y + 2;
			if (number2[y] == 'E') {
				number2[0] = '1';
				j = 1;
				while (number2[y] != '\0') {
					number2[j] = number2[y];
					j++; y++;
				}
				number2[j] = '\0';
				ampl[n] = ampl[n] * convertToNumber(number2);
			}
			number2[0] = '\0';
		}
		sif = 0;
		int df = j;
		j = 0;
		if (number2[0] != 'B'&&number2[0] != 'O'&&number2[0] != 'H'&&number2[0] != 'P') {
			if (number2[0] == '_'&&number2[1] != 'e'&&number2[1] != 'p'&&number2[1] != 'B'&&number2[1] != 'O'&&number2[1] != 'H' && (number2[1] == 'I'&&number2[2] == 'N'&&number2[3] == 'F') == false) {
				if (number2[1] == '.') {
					j = abs((int)strlen(number2));
					while (j > 1) {
						number2[j] = number2[j - 1];
						j--;
					}
					number2[j] = '0';
				}
				for (j = 0; number2[j] != '\0'; j++) {
					number2[j] = number2[j + 1];
				}
				if (number2[0] != '0'&&number2[0] != '1'&&number2[0] != '2'&&number2[0] != '3'&&number2[0] != '4'&&number2[0] != '5'&&number2[0] != '6'&&number2[0] != '7'&&number2[0] != '8'&&number2[0] != '9') {
					sign = 1;
					for (j = 0; number2[j] != '\0'; j++) {
						if (number2[j] == '.') {
							number2[j] = '\0';
						}
					}
				}
				if (res == 0) {
					ampl[n] = -1 * convertToNumber(number2);
				}
			}
			else {
				if (res == 0 && number2[0] != '_') {
					ampl[n] = convertToNumber(number2);
				}
			}
			if (prefCalc[0] == 'P') {
				if (prefCalc[1] == 'd'&&prefCalc[2] == 'a') {
					prefCalc[1] = 'D';
				}
				ampl[n] = ampl[n] * prefToNumber(prefCalc[1]);
			}
			number2[df] = '\0';
		}
		double var = 0;
		if (firstLetterVariable(number2[0])) {
			for (j = 0; number2[j] != '\0'; j++) {
				if (number2[j] == '.') {
					number2[j] = '\0';
				}
			}
			processVariable(number2);
			if (resultR != 0) {
				ampl[n] = resultR;
				if (sign == 1) {
					sign = 0;
					ampl[n] = ampl[n] * -1;
				}
			}
			if (resultI != 0) {
				complex = 2;
				amplI[n] = resultI;
				if (sign == 1) {
					sign = 0;
					amplI[n] = amplI[n] * -1;
				}
			}
		}
		if (number2[1] == 'f' || number2[1] == 'h' || number2[1] == 'j' || number2[1] == 'k' || number2[1] == 'm' || number2[1] == 'n' || number2[1] == 'o' || number2[1] == 'p' &&number2[2] != 'i' || number2[1] == 'u' || number2[1] == 'w' || number2[1] == 'v' || number2[1] == 'y' || number2[1] == 'z' || number2[1] == 'G' || number2[1] == 'I' || number2[1] == 'J' || number2[1] == 'K' || number2[1] == 'L' || number2[1] == 'M' || number2[1] == 'N' || number2[1] == 'Q' || number2[1] == 'R' || number2[1] == 'S' || number2[1] == 'T' || number2[1] == 'U' || number2[1] == 'V' || number2[1] == 'X' || number2[1] == 'Y' || number2[1] == 'Z' || number2[0] == 'x') {
			if (number2[0] == '_') {
				for (j = 0; number2[j + 1] != '\0'; j++) {
					number2[j] = number2[j + 1];
				}
				number2[j] = '\0';
				sign = 1;
				for (j = 0; number2[j] != '\0'; j++) {
					if (number2[j] == '.') {
						number2[j] = '\0';
					}
				}
				processVariable(number2);
				ampl[n] = resultR;
				amplI[n] = resultI;
				if (sign == 1) {
					sign = 0;
					ampl[n] = ampl[n] * -1;
					amplI[n] = amplI[n] * -1;
				}
			}
		}
		if (number2[0] == 'B' || number2[0] == 'O' || number2[0] == 'H') {
			if (number2[0] == 'B') {
				if (isContained("B.", number2)) {
					replace("B.", "B0.", number2);
					sprintf(number2, "%s", expressionF);
				}
				if (isContained("B_.", number2)) {
					replace("B_.", "B_0.", number2);
					sprintf(number2, "%s", expressionF);
				}
			}
			if (number2[0] == 'O') {
				if (isContained("O.", number2)) {
					replace("O.", "O0.", number2);
					sprintf(number2, "%s", expressionF);
				}
				if (isContained("O_.", number2)) {
					replace("O_.", "O_0.", number2);
					sprintf(number2, "%s", expressionF);
				}
			}
			if (number2[0] == 'H') {
				if (isContained("H.", number2)) {
					replace("H.", "H0.", number2);
					sprintf(number2, "%s", expressionF);
				}
				if (isContained("H_.", number2)) {
					replace("H_.", "H_0.", number2);
					sprintf(number2, "%s", expressionF);
				}
			}
			ampl[n] = numericalSystems(number2);
		}
		if (number2[0] == '_' && (number2[1] == 'B' || number2[1] == 'O' || number2[1] == 'H')) {
			for (j = 0; number2[j] != '\0'; j++) {
				number2[j] = number2[j + 1];
			}
			number2[j] = '\0';
			if (number2[0] == 'B') {
				if (isContained("B.", number2)) {
					replace("B.", "B0.", number2);
					sprintf(number2, "%s", expressionF);
				}
				if (isContained("B_.", number2)) {
					replace("B_.", "B_0.", number2);
					sprintf(number2, "%s", expressionF);
				}
			}
			if (number2[0] == 'O') {
				if (isContained("O.", number2)) {
					replace("O.", "O0.", number2);
					sprintf(number2, "%s", expressionF);
				}
				if (isContained("O_.", number2)) {
					replace("O_.", "O_0.", number2);
					sprintf(number2, "%s", expressionF);
				}
			}
			if (number2[0] == 'H') {
				if (isContained("H.", number2)) {
					replace("H.", "H0.", number2);
					sprintf(number2, "%s", expressionF);
				}
				if (isContained("H_.", number2)) {
					replace("H_.", "H_0.", number2);
					sprintf(number2, "%s", expressionF);
				}
			}
			ampl[n] = numericalSystems(number2)*-1;
		}
		j = 0;
		f = 0;
		char ex[DIM] = "";
		if (number2[0] == 'p'&&number2[1] == 'i') {
			ampl[n] = M_PI;
		}
		if (number2[0] == '_'&&number2[1] == 'p'&&number2[2] == 'i') {
			ampl[n] = (-1)*(M_PI);
		}
		if (number2[0] == 'e') {
			ampl[n] = M_E;
		}
		if (number2[0] == '_'&&number2[1] == 'e') {
			ampl[n] = (-1)*(M_E);
		}
		if (number2[0] == 'r'&&number2[1] == 'e'&&number2[2] == 's' || number2[0] == '['&&number2[1] == 'r'&&number2[2] == 'e'&&number2[3] == 's') {
			ampl[n] = ansRV;
			amplI[n] = ansIV;
			if (equationSolverRunning || solverRunning) {
				ampl[n] = xValuesR;
				amplI[n] = xValuesI;
			}
			complex = 2;
		}
		if (number2[0] == '_'&&number2[1] == 'r'&&number2[2] == 'e'&&number2[3] == 's' || number2[0] == '['&&number2[1] == '_'&&number2[2] == 'r'&&number2[3] == 'e'&&number2[4] == 's') {
			ampl[n] = ansRV * -1;
			amplI[n] = ansIV * -1;
			if (equationSolverRunning || solverRunning) {
				ampl[n] = xValuesR * -1;
				amplI[n] = xValuesI * -1;
			}
			complex = 2;
		}
		if (facto > 0) {
			if (ampl[n] < 0) {
				number2[0] = '_';
			}
			while (facto > 0) {
				ampl[n] = fact(abs(ampl[n]));
				facto--;
			}
			if (number2[0] == '_') {
				ampl[n] = ampl[n] * -1;
			}
		}
		while (trigon1[i] != '+'&&trigon1[i] != '-'&&trigon1[i] != '*'&&trigon1[i] != '/'&&trigon1[i] != '^'&&trigon1[i] != '='&&trigon1[i] != '\0') { i++; }
		amp[n] = trigon1[i];
		if (complex == 1) {
			amplI[n] = ampl[n];
			ampl[n] = 0;
			if (negImag == 1) {
				negImag = 0;
				amplI[n] = amplI[n] * -1;
			}
		}
		else {
			if (complex != 2) {
				amplI[n] = 0;
			}
		}
		n++;
		char number2[DIM] = "";
		char trigon1[] = "";
		res = 0;
	}
	int a = 0;
	int fr;
	so = 0;
	int ca = 0;
	double asdf = 0, asdfI = 0;
	for (so = 0; so < n; so++) {
		int sa = so;
		int b = 0;
		if (amp[so] == '^'&&amp[so + 1] == '^') {
			while (amp[so] == '^'&&a != 1) {
				if (amp[so + 1] != '^'&&amp[so - 1] == '^'&&a != 2) {
					asdf = ampl[so + 1];
					asdfI = amplI[so + 1];
					if (ampl[so] < 0 || amplI[so] < 0) {
						sig[so] = 0;
					}
					else { sig[so] = 1; }
					exponentiation(ampl[so], amplI[so], asdf, asdfI, sig[so]);
					asdf = resultR;
					asdfI = resultI;
					ampl[so + 1] = 1;
					ampl[so] = 1;
					amplI[so + 1] = 0;
					amplI[so] = 0;
					amp[so] = '*';
					so--;
					a = 2;
				}
				else {
					if (amp[so + 1] == '^'&&a == 0) {
						so++;
						fr = so;
					}
					else {
						if (a == 2) {
							while (a != 1) {
								if ((ampl[so] < 0 || amplI[so] < 0) && !equationSolverRunning) {
									sig[so] = 0;
								}
								else { sig[so] = 1; }
								exponentiation(ampl[so], amplI[so], asdf, asdfI, sig[so]);
								asdf = resultR;
								asdfI = resultI;
								ampl[so] = 1;
								amplI[so] = 0;
								amp[so] = '*';
								so--;
								if (amp[so] != '^') {
									a = 1;
									so = fr++;
								}
							}
						}
					}
				}
				if (a == 1) {
					ampl[sa] = asdf; a = 0;
					amplI[sa] = asdfI;
				}
			}
		}
		else {
			if (amp[so] == '^'&&amp[so + 1] != '^') {
				while (amp[so] == '^') {
					if ((ampl[sa] < 0 || amplI[sa] < 0) && !equationSolverRunning) {
						sig[sa] = 0;
					}
					else { sig[sa] = 1; }
					exponentiation(ampl[sa], amplI[sa], ampl[so + 1], amplI[so + 1], sig[sa]);
					ampl[sa] = resultR;
					amplI[sa] = resultI;
					ampl[so + 1] = 1;
					amplI[so + 1] = 0;
					amp[so] = '*';
					so++;
				}
			}
		}
	}
	char simplified[DIM] = "";
	int RF = 0;
	for (RF = 0; RF < n; RF++) {
		if (ampl[RF] > 0 && amplI[RF] < 0) {
			sprintf(simplified, "%s(%G%Gi)%c", simplified, ampl[RF], amplI[RF], amp[RF]);
		}
		else {
			if (ampl[RF] < 0 && amplI[RF] > 0) {
				sprintf(simplified, "%s(%G+%Gi)%c", simplified, ampl[RF], amplI[RF], amp[RF]);
			}
			else {
				if (ampl[RF] < 0 && amplI[RF] < 0) {
					sprintf(simplified, "%s(%G%Gi)%c", simplified, ampl[RF], amplI[RF], amp[RF]);
				}
				else {
					if (ampl[RF] == 0 && amplI[RF] == 0) {
						sprintf(simplified, "%s%G%c", simplified, ampl[RF], amp[RF]);
					}
					else {
						if (ampl[RF] == 0 && amplI[RF] != 0) {
							sprintf(simplified, "%s%Gi%c", simplified, amplI[RF], amp[RF]);
						}
						else {
							if (ampl[RF] != 0 && amplI[RF] == 0) {
								sprintf(simplified, "%s%G%c", simplified, ampl[RF], amp[RF]);
							}
							else {
								sprintf(simplified, "%s(%G+%Gi)%c", simplified, ampl[RF], amplI[RF], amp[RF]);
							}
						}
					}
				}
			}
		}
	}
	rasf = abs((int)strlen(simplified));
	while (simplified[rasf - 2] == '+'&&simplified[rasf - 1] == '0') {
		rasf = rasf - 2;
		simplified[rasf] = '\0';
	}
	simplified[abs((int)strlen(simplified))] = '\0';
	replace("=", "", simplified);
	sprintf(simplified, "%s", expressionF);
	if (verbose == 1 && solving) {
		printf("\nSimplified expression by arithSolver: %s\n\n", simplified);
	}
	for (so = 0; so < n; so++) {
		int sa = so;
		while (amp[so] == '/') {
			division(ampl[sa], amplI[sa], ampl[so + 1], amplI[so + 1]);
			ampl[sa] = resultR;
			amplI[sa] = resultI;
			ampl[so + 1] = 1;
			amplI[so + 1] = 0;
			amp[so] = '*';
			so++;
		}
	}
	for (so = 0; so < n; so++) {
		int sa = so;
		while (amp[so] == '*') {
			multiplication(ampl[sa], amplI[sa], ampl[so + 1], amplI[so + 1]);
			ampl[sa] = resultR;
			amplI[sa] = resultI;
			ampl[so + 1] = 1;
			amplI[so + 1] = 0;
			amp[so] = '*';
			so++;
		}
	}
	for (h = 0; h < n; h++) {
		if (h == 0) {
			result1 = ampl[0];
			result2 = amplI[0];
		}
		if (amp[h] == '^') {
			exponentiation(result1, result2, ampl[h + 1], amplI[h + 1], 1);
			result1 = resultR;
			result2 = resultI;
		}
		if (amp[h] == '*') {
			multiplication(result1, result2, ampl[h + 1], amplI[h + 1]);
			result1 = resultR;
			result2 = resultI;
		}
		if (amp[h] == '/') {
			division(result1, result2, ampl[h + 1], amplI[h + 1]);
			result1 = resultR;
			result2 = resultI;
		}
		if (amp[h] == '-') {
			subtraction(result1, result2, ampl[h + 1], amplI[h + 1]);
			result1 = resultR;
			result2 = resultI;
		}
		if (amp[h] == '+') {
			sum(result1, result2, ampl[h + 1], amplI[h + 1]);
			result1 = resultR;
			result2 = resultI;
		}
	}
	resultR = result1;
	resultI = result2;
	round_complex();
	result1 = resultR;
	result2 = resultI;
	return result1;
}

double functionProcessor(char trigon[DIM], double result, double amplitude, int res) {
	char saveArgument[DIM] = "";
	sprintf(saveArgument, "%s", expressionF);
	if (verbose == 1 && solving) {
		printf("\n\n==> functionProcessor <==\n\nFunction: %s", trigon);
	}
	int i = 0, var = 0, j = 0, n = 0, count = 0, opt = 0, l = 0, p = 0, cn = 0, s, rad = 1, jg = 1, gon = 0, tri = 0, co = 0, trigono = 0, paren = 1, pare = 0, parent = 0, e = 0, f = 0, kl = 0, ar = 0, deg = 0, type = 0, g = 0;
	char trig[DIM] = "0", base[DIM], number[DIM] = "0", number1[DIM] = "0", number2[DIM] = "0", op[DIM] = "0", signal = '*', numb[DIM] = "0", sig = '0', point = '0', cieNot[DIM] = "0", arg[DIM] = "0", amp[DIM] = "0", trigon1[DIM] = "0", ex[DIM] = "", eX[DIM] = "", trig1[DIM] = "", function[DIM] = "cos,acos,sin,asin,tan,atan,sec,asec,cosec,acosec,cotan,acotan,log,ln,rest,quotient,sqrt,cbrt,afact,cosh,acosh,sinh,asinh,tanh,atanh,sech,asech,cosech,acosech,cotanh,acotanh,sinc,gerror,gerrorinv,gerrorc,gerrorcinv,qfunc,qfuncinv,cbrt,sqrt,atc,i,res,pi,e,solver,det,abs,strlen,countoccurrences,iscontained,iscontainedbyindex,iscontainedvariable,isequal,isvariable,istowrite,for,calc,";
	double num = 0, v[DIM], vI[DIM], argu[DIM], ampl[DIM], exp = 1, result1 = 0, baLog = 0, dgrt = 0, result2 = resultI, dgrt2 = 0;
	char userFunc[DIM] = "", atcFunc[DIM] = "", funcU[DIM] = "";
	char saveFunction[DIM] = "";
	sprintf(saveFunction, "%s%s", function, usRFuncTrans);
	sprintf(function, saveFunction);
	for (i = 0; trigon[i] != '?'&&trigon[i] != '\0'; i++) {
		atcFunc[i] = trigon[i];
	}
	atcFunc[i] = '\0';
	if (atcFunc[0] == 'a'&&atcFunc[1] == 't'&&atcFunc[2] == 'c'&&atcFunc[3] == '_') {
		for (i = 0; atcFunc[i + 4] != '\0'; i++) {
			atcFunc[i] = atcFunc[i + 4];
		}
		atcFunc[i] = '\0';
		char propFunc[DIM] = "";
		sprintf(propFunc, "%s,", atcFunc);
		if (isContained(propFunc, usRFuncTrans)) {
			int start = strStart;
			int end = strEnd;
			int k = 0;
			int y = start;
			while (y < end - 1) {
				atcFunc[k] = usRFunctions[y];
				y++; k++;
			}
			atcFunc[k] = '\0';
		}
		int hi = 0;
		for (hi = 0; atcFunc[hi] != '\0'; hi++) {
			funcU[hi] = atcFunc[hi];
		}
		funcU[hi] = '\0';
		FILE *open = NULL;
		char directory[MAX_PATH] = "";
		char savePath[300] = "";
		char comm[300] = "";
		sprintf(userFunc, "%s\\User functions\\%s.txt", atcPath, atcFunc);
		if (open != NULL) {
			fclose(open);
			open = NULL;
		}
		open = fopen(userFunc, "r");
		if (open != NULL) {
			fclose(open);
			sprintf(function, "%satc_%s", function, atcFunc);
		}
	}
	for (i = 0; trigon[i] != '\0'; i++) {
		if (trigon[i] == '?') {
			var = 1;
			trigon[i] = '\0';
			break;
		}
	}
	v[0] = 0; v[1] = 0; v[7] = 0; vI[0] = 0; vI[1] = 0; vI[7] = 0;
	if (trigon[0] == '_') {
		jg = -1;
		for (s = 0; trigon[s] != '\0'; s++) {
			trigon[s] = trigon[s + 1];
		}
	}
	if (Mode == 0) {
		opt = applySettings(4);
		if (opt == 3) {
			deg = 0;
			rad = 0;
			gon = 1;
		}
		if (opt == 2) {
			deg = 1;
			rad = 0;
			gon = 0;
		}
		if (opt == 1) {
			rad = 1;
			deg = 0;
			gon = 0;
		}
	}
	for (s = 0; s < abs((int)strlen(trigon)); s++) {
		v[s] = 0;
		argu[s] = 0;
		ampl[s] = 0;
	}
	v[0] = amplitude;
	v[1] = result;
	vI[0] = resultR;
	vI[1] = resultI;
	if (verbose == 1 && solving) {
		puts("\nFunction arguments:\n1st interactor: \n");
		if (v[0] > 0 && vI[0] > 0) {
			printf("=%G+%Gi\n", v[0], vI[0]);
		}
		else {
			if (v[0] > 0 && vI[0] < 0) {
				printf("=%G%Gi\n", v[0], vI[0]);
			}
			else {
				if (v[0] < 0 && vI[0] > 0) {
					printf("=%G+%Gi\n", v[0], vI[0]);
				}
				else {
					if (v[0] < 0 && vI[0] < 0) {
						printf("=%G%Gi\n", v[0], vI[0]);
					}
					else {
						if (v[0] == 0 && vI[0] == 0) {
							printf("=%G\n", v[0]);
						}
						else {
							if (v[0] == 0 && vI[0] != 0) {
								printf("=%Gi\n", vI[0]);
							}
							else {
								if (v[0] != 0 && vI[0] == 0) {
									printf("=%G\n", v[0]);
								}
								else {
									printf("=%G+%Gi\n", v[0], vI[0]);
								}
							}
						}
					}
				}
			}
		}
		puts("\n\n2nd interactor: \n");
		if (v[1] > 0 && vI[1] > 0) {
			printf("=%G+%Gi\n", v[1], vI[1]);
		}
		else {
			if (v[1] > 0 && vI[1] < 0) {
				printf("=%G%Gi\n", v[1], vI[1]);
			}
			else {
				if (v[1] < 0 && vI[1] > 0) {
					printf("=%G+%Gi\n", v[1], vI[1]);
				}
				else {
					if (v[1] < 0 && vI[1] < 0) {
						printf("=%G%Gi\n", v[1], vI[1]);
					}
					else {
						if (v[1] == 0 && vI[1] == 0) {
							printf("=%G\n", v[1]);
						}
						else {
							if (v[1] == 0 && vI[1] != 0) {
								printf("=%Gi\n", vI[1]);
							}
							else {
								if (v[1] != 0 && vI[1] == 0) {
									printf("=%G\n", v[1]);
								}
								else {
									printf("=%G+%Gi\n", v[1], vI[1]);
								}
							}
						}
					}
				}
			}
		}
	}
	result = 0;
	if (trigon[0] == 'r'&&trigon[1] == 'a'&&trigon[2] == 'd') {
		rad = 1;
		deg = 0;
		gon = 0;
		for (s = 0; trigon[s] != '\0'; s++) {
			trigon[s] = trigon[s + 3];
		}
		trigon[s] = '\0';
	}
	if (trigon[0] == 'd'&&trigon[1] == 'e'&&trigon[2] == 'g') {
		deg = 1;
		rad = 0;
		gon = 0;
		for (s = 0; trigon[s] != '\0'; s++) {
			trigon[s] = trigon[s + 3];
		}
		trigon[s] = '\0';
	}
	if (trigon[0] == 'g'&&trigon[1] == 'o'&&trigon[2] == 'n') {
		gon = 1;
		deg = 0;
		rad = 0;
		for (s = 0; trigon[s] != '\0'; s++) {
			trigon[s] = trigon[s + 3];
		}
		trigon[s] = '\0';
	}
	if (isEqual("strlen", trigon)) {
		return 0.5;
	}
	if (var == 1) {
		if (trigon[0] == 'a'&&trigon[1] == 't'&&trigon[2] == 'c'&&trigon[3] == '_') {
			for (i = 0; trigon[i + 4] != '\0'; i++) {
				trigon[i] = trigon[i + 4];
			}
			trigon[i] = '\0';
		}
		if ((isEqual("rtDD", trigon)) || (isEqual("logbb", trigon))) {
			return 0.5;
		}
		for (i = 0; function[i] != '\0'; i++) {
			j = 0; g = 0;
			if (function[i] == trigon[j]) {
				j = 0; g = 0;
				while (function[i] != '\0'&&function[i] != ',') {
					if (function[i] == trigon[j]) {
						j++;
					}
					i++;
					g++;
				}
				if (j == strlen(trigon) && g == j) {
					return 0.5;
				}
			}
		}
	}
	i = 0; j = 0;
	for (s = 0; trigon[s] != '\0'; s++) {
		if (((trigon[s - 1] == 'g'&&trigon[s] == 'b') && trigon[s - 1] != 'c') || (trigon[s - 1] == 't'&&trigon[s] == 'D')) {
			j = s;
			s++;
			while ((trigon[s] == 'b'&&trigon[s + 1] == '\0') == false && (trigon[s] == 'D'&&trigon[s + 1] == '\0') == false && trigon[s] != '\0') {
				base[i] = trigon[s];
				i++; s++;
			}
			base[i] = '+'; base[i + 1] = '0'; base[i + 2] = '\0';
			resultR = 0; resultI = 0;
			baLog = 0;
			baLog = solveNow(base, 0, 0);
			dgrt = baLog;
			dgrt2 = resultI;
			resultI = 0; resultR = 0; baLog = 0;
			trigon[j] = '\0';
		}
	}
	sprintf(op, "%s", trigon);
	int h = 0;
	for (i = 0; op[i] != '\0'; i++) {
		if (op[i] == 'h') {
			h = 1;
		}
	}
	char funC[10] = "";
	sprintf(funC, "%s,", op);
	if (h == 0 && op[0] != 'a'&&isContained(funC, "cos, acos, sin, asin, tan, atan, sec, asec, cosec, acosec, cotan, acotan,")) {
		if (rad == 1) {
			v[7] = ((v[1] * 180) / M_PI);
			if (v[7] < 0) {
				v[7] = re(v[7], -360);
			}
			else {
				if (v[7] >= 0) {
					v[7] = re(v[7], 360);
				}
			}

			vI[7] = ((vI[1] * 180) / M_PI);
			if (vI[7] < 0) {
				vI[7] = re(vI[7], -360);
			}
			else {
				if (vI[7] >= 0) {
					vI[7] = re(vI[7], 360);
				}
			}
			v[1] = v[7] * M_PI / 180;
			vI[1] = vI[7] * M_PI / 180;
		}
		if (deg == 1) {
			v[7] = v[1];
			if (v[7] < 0) {
				v[7] = re(v[7], -360);
			}
			else {
				if (v[7] >= 0) {
					v[7] = re(v[7], 360);
				}
			}
			vI[7] = vI[1];
			if (vI[7] < 0) {
				vI[7] = re(vI[7], -360);
			}
			else {
				if (vI[7] >= 0) {
					vI[7] = re(vI[7], 360);
				}
			}
			v[1] = v[7];
			vI[1] = vI[7];
		}
		if (gon == 1) {
			v[7] = v[1] * 0.9;
			if (v[7] < 0) {
				v[7] = re(v[7], -360);
			}
			else {
				if (v[7] >= 0) {
					v[7] = re(v[7], 360);
				}
			}
			vI[7] = vI[1] * 0.9;
			if (vI[7] < 0) {
				vI[7] = re(vI[7], -360);
			}
			else {
				if (vI[7] >= 0) {
					vI[7] = re(vI[7], 360);
				}
			}
			v[1] = v[7] * 1 / 0.9;
			vI[1] = vI[7] * 1 / 0.9;
		}
	}
	if (isEqual("log", op)) {
		if (dgrt != 0 || dgrt2 != 0) {
			complex_log(dgrt, dgrt2);
			double baR = resultR, baI = resultI;
			complex_log(v[1], result2);
			division(resultR, resultI, baR, baI);
			result1 = resultR;
			result2 = resultI;
		}
		else {
			complex_log(10.0, 0);
			double baR = resultR, baI = resultI;
			complex_log(v[1], result2);
			division(resultR, resultI, baR, baI);
			result1 = resultR;
			result2 = resultI;
		}
	}
	if (isEqual("rt", op)) {
		division(1, 0.0, dgrt, dgrt2);
		exponentiation(v[1], result2, resultR, resultI, 1);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("sqrt", op)) {
		exponentiation(v[1], result2, 1 / 2.0, 0, 1);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("cbrt", op)) {
		exponentiation(v[1], result2, 1 / 3.0, 0, 1);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("ln", op)) {
		complex_log(v[1], result2);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("abs", op)) {
		resultR = abs_complex(v[1], vI[1]);
		resultI = 0;
		result1 = resultR;
		result2 = resultI;
		type = 1;
	}
	if (isEqual("cosec", op)) {
		if (deg == 1) {
			v[1] = ((v[1] * M_PI) / 180);
			vI[1] = ((vI[1] * M_PI) / 180);
		}
		if (gon == 1) {
			v[1] = v[1] * (M_PI / 200);
			vI[1] = vI[1] * (M_PI / 200);
		}
		cosec(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("cosech", op)) {
		cosech(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("sec", op)) {
		if (deg == 1) {
			v[1] = ((v[1] * M_PI) / 180);
			vI[1] = ((vI[1] * M_PI) / 180);
		}
		if (gon == 1) {
			v[1] = v[1] * (M_PI / 200);
			vI[1] = vI[1] * (M_PI / 200);
		}
		sec(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("sech", op)) {
		sech(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("cotan", op)) {
		if (deg == 1) {
			v[1] = ((v[1] * M_PI) / 180);
			vI[1] = ((vI[1] * M_PI) / 180);
		}
		if (gon == 1) {
			v[1] = v[1] * (M_PI / 200);
			vI[1] = vI[1] * (M_PI / 200);
		}
		cotan(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("cotanh", op)) {
		cotanh(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("acos", op)) {
		complex_acos(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("asin", op)) {
		complex_asin(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("atan", op)) {
		complex_atan(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("cos", op)) {
		if (deg == 1) {
			v[1] = ((v[1] * M_PI) / 180);
			vI[1] = ((vI[1] * M_PI) / 180);
		}
		if (gon == 1) {
			v[1] = v[1] * (M_PI / 200);
			vI[1] = vI[1] * (M_PI / 200);
		}
		complex_cos(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
		if (v[7] == 270 || v[7] == 90 || v[7] == -90 || v[7] == -270) {
			result1 = v[0] * sqrt(1 - (sin(v[1])*sin(v[1])));
		}
	}
	if (isEqual("cosh", op)) {
		complex_cosh(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("sin", op)) {
		if (deg == 1) {
			v[1] = ((v[1] * M_PI) / 180);
			vI[1] = ((vI[1] * M_PI) / 180);
		}
		if (gon == 1) {
			v[1] = v[1] * (M_PI / 200);
			vI[1] = vI[1] * (M_PI / 200);
		}
		complex_sin(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
		if ((v[7] == 180 || v[7] == 0 || v[7] == -180) && vI[7] == 0) {
			result1 = v[0] * sqrt(1 - (cos(v[1])*cos(v[1])));
		}
	}
	if (isEqual("sinh", op)) {
		complex_sinh(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("sinc", op)) {
		sinc(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("tan", op)) {
		if (deg == 1) {
			v[1] = ((v[1] * M_PI) / 180);
			vI[1] = ((vI[1] * M_PI) / 180);
		}
		if (gon == 1) {
			v[1] = v[1] * (M_PI / 200);
			vI[1] = vI[1] * (M_PI / 200);
		}
		complex_tan(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
		if ((v[7] == 90 || v[7] == -90 || v[7] == 270 || v[7] == -270 || v[7] == 0 || v[7] == 180 || v[7] == -180) && vI[7] == 0) {
			result1 = v[0] * (sqrt(1 - cos(v[1])*cos(v[1])) / sqrt(1 - sin(v[1])*sin(v[1])));
		}
	}
	if (isEqual("tanh", op)) {
		complex_tanh(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
		type = 1;
	}
	if (isEqual("asinh", op)) {
		arsinh(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
		type = 1;
	}
	if (isEqual("acosh", op)) {
		arcosh(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
		type = 1;
	}
	if (isEqual("atanh", op)) {
		artanh(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
		type = 1;
	}
	if (isEqual("acotanh", op)) {
		arcoth(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
		type = 1;
	}
	if (isEqual("asech", op)) {
		arsech(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
		type = 1;
	}
	if (isEqual("acosech", op)) {
		arcsch(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
		type = 1;
	}
	if (isEqual("quotient", op)) {
		qu_complex(v[0], vI[0], v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("rest", op)) {
		re_complex(v[0], vI[0], v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("acosec", op)) {
		arcosec(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("asec", op)) {
		arcsec(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("acotan", op)) {
		arcotg(v[1], vI[1]);
		result1 = resultR;
		result2 = resultI;
	}
	if (isEqual("qfunc", op)) {
		result1 = v[0] * qfunc(v[1]);
	}
	if (isEqual("qfuncinv", op)) {
		result1 = v[0] * qfuncinv(v[1]);
	}
	if (isEqual("gerror", op)) {
		result1 = v[0] * gerror(v[1]);
	}
	if (isEqual("gerrorc", op)) {
		result1 = v[0] * gerrorc(v[1]);
	}
	if (isEqual("gerrorinv", op)) {
		result1 = v[0] * gerrorinv(v[1]);
	}
	if (isEqual("gerrorcinv", op)) {
		result1 = v[0] * gerrorcinv(v[1]);
	}
	if (isEqual("afact", op)) {
		result1 = v[0] * arcfact(v[1]);
		type = 1;
	}
	if (trigon[0] == 'a'&&trigon[1] == 't'&&trigon[2] == 'c'&&trigon[3] == '_') {
		char comm[300] = "";
		if (atcFunc[0] == 'a'&&atcFunc[1] == 't'&&atcFunc[2] == 'c'&&atcFunc[3] == '_') {
			for (i = 0; atcFunc[i + 4] != '\0'; i++) {
				atcFunc[i] = atcFunc[i + 4];
			}
			atcFunc[i] = '\0';
		}
		resultR = v[1];
		resultI = vI[1];
		int inputs = countOccurrences("\\", saveArgument);
		char letters[30] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", value[DIM] = "";
		int y = 0, x = 0, entered = 0;
		char toEnter[DIM] = "";
		sprintf(toEnter, "%s", saveArgument);
		while (entered <= inputs) {
			y = 0;
			while (toEnter[x] != '\\'&&toEnter[x] != '='&&toEnter[x] != '\0') {
				value[y] = toEnter[x];
				y++; x++;
			}
			value[y] = '\0';
			calcNow(value, 0, 0);
			char variable[20] = "";
			sprintf(variable, "Input%c", letters[entered]);
			variableController(variable, resultR);
			entered++;
			x++;
			sprintf(value, "");
		}
		processTxt(userFunc, res);
		result1 = resultR;
		result2 = resultI;
		char txtSolved[DIM] = "";
		char txtTryDelete[DIM] = "";
		sprintf(userFunc, "%s\\User functions\\%s.txt", atcPath, funcU);
		sprintf(txtSolved, "del \"%s\\User functions\\%s_answers.txt\"", atcPath, funcU);
		sprintf(txtTryDelete, "%s\\User functions\\%s_answers.txt", atcPath, funcU);
		FILE *file = NULL;
		file = fopen(txtTryDelete, "r");
		if (file != NULL) {
			fclose(file);
			system(txtSolved);
		}
		type = 1;
		char function[DIM] = "cos,acos,sin,asin,tan,atan,sec,asec,cosec,acosec,cotan,acotan,log,ln,rest,quotient,sqrt,cbrt,afact,cosh,acosh,sinh,asinh,tanh,atanh,sech,asech,cosech,acosech,cotanh,acotanh,sinc,gerror,gerrorinv,gerrorc,gerrorcinv,qfunc,qfuncinv,cbrt,sqrt,atc,solver,det,abs,strlen,countoccurrences,iscontained,iscontainedbyindex,iscontainedvariable,isequal,isvariable,istowrite,for,calc,";
		return result1;
	}
	if (op[0] == 'a'&&type == 0) {
		if (deg == 1) {
			result1 = ((result1 * 180) / M_PI);
			result2 = ((result2 * 180) / M_PI);
		}
		if (gon == 1) {
			result1 = result1 * (200 / M_PI);
			result2 = result2 * (200 / M_PI);
		}
	}
	sprintf(trigon, "");
	result1 = result1 * jg;
	result2 = result2 * jg;
	resultR = result1;
	resultI = result2;
	round_complex();
	if (verbose == 1 && solving) {
		puts("\nResult of function processing:\n");
		if (resultR > 0 && resultI > 0) {
			printf("=%G+%Gi\n", resultR, resultI);
		}
		else {
			if (resultR > 0 && resultI < 0) {
				printf("=%G%Gi\n", resultR, resultI);
			}
			else {
				if (resultR < 0 && resultI > 0) {
					printf("=%G+%Gi\n", resultR, resultI);
				}
				else {
					if (resultR < 0 && resultI < 0) {
						printf("=%G%Gi\n", resultR, resultI);
					}
					else {
						if (resultR == 0 && resultI == 0) {
							printf("=%G\n", resultR);
						}
						else {
							if (resultR == 0 && resultI != 0) {
								printf("=%Gi\n", resultI);
							}
							else {
								if (resultR != 0 && resultI == 0) {
									printf("=%G\n", resultR);
								}
								else {
									printf("=%G+%Gi\n", resultR, resultI);
								}
							}
						}
					}
				}
			}
		}
	}
	return result1;
}