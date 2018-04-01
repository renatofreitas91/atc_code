
#include "stdafx.h"

boolean advancedEvaluator(char expression[DIM]) {
	int toSolve = 0;
	char saveExpression[DIM] = "";
	int d = 0, kl = 0, kr = 0;
	for (d = 0; expression[d] != '\0'; d++) {
		if (expression[d] == '(') {
			if (verifyLetter(expression[d + 1]) || verifyNumber(expression[d + 1])) {
				if (expression[d - 1] != '&'&&expression[d - 1] != '|') {
					expression[d] = '[';
					kl++;
				}
			}
		}
		if (expression[d] == ')') {
			if (verifyLetter(expression[d - 1]) || verifyNumber(expression[d - 1]) || kr < kl) {
				if ((expression[d + 1] != '&'&&expression[d + 1] != '|'&&d != strlen(expression) - 1) || kr < kl) {
					expression[d] = ']';
					kr++;
				}
			}
		}
	}
	sprintf(saveExpression, expression);
	sprintf(expressionF, expression);
	if (isContained("==", expressionF)) {
		toSolve = 1;
		replace("==", "  ", expressionF);
	}
	if (isContained("!=", expressionF)) {
		toSolve = 1;
		replace("!=", "  ", expressionF);
	}
	if (isContained("<=", expressionF)) {
		toSolve = 1;
		replace("<=", "  ", expressionF);
	}
	if (isContained(">=", expressionF)) {
		toSolve = 1;
		replace(">=", "  ", expressionF);
	}
	if (isContained(">", expressionF)) {
		toSolve = 1;
		replace(">", " ", expressionF);
	}
	if (isContained("<", expressionF)) {
		toSolve = 1;
		replace("<", " ", expressionF);
	}
	if (isContained("&&", expressionF)) {
		toSolve = 1;
		replace("&&", "  ", expressionF);
	}
	if (isContained("||", expressionF)) {
		toSolve = 1;
		replace("||", "  ", expressionF);
	}
	if (toSolve == 1) {
		char valuesToExtract[DIM] = "";
		char saveValues[DIM] = "";
		sprintf(valuesToExtract, expressionF);
		char symbols[DIM] = "";
		int g = 0, h = 0, kl = 0, kr = 0;
		for (g = 0; valuesToExtract[g] != '\0'; g++) {
			kl = 0; kr = 0;
			while (valuesToExtract[g] != ' '&&valuesToExtract[g] != '\0') {
				if (valuesToExtract[g] == '[') {
					kl++;
				}
				if (valuesToExtract[g] == ']') {
					kr++;
				}
				g++;
			}
			if (kl != kr) {
				if (kr > kl) {
					while (expression[g] != ']'&&g > 0) {
						g--;
					}
					expression[g] = ')';
					valuesToExtract[g] = ')';
				}
				if (kl > kr) {
					g--;
					while (expression[g] != ' '&&g > 0) {
						g--;
					}
					while (expression[g] != '['&&expression[g] != '\0') {
						g++;
					}
					expression[g] = '(';
					valuesToExtract[g] = '(';
				}
			}
		}
		for (g = 0; valuesToExtract[g] != '\0'; g++) {
			if (valuesToExtract[g] == ' ') {
				while (valuesToExtract[g] == ' ') {
					symbols[h] = saveExpression[g];
					h++; g++;
				}
				symbols[h] = ',';
				h++;
			}
		}
		symbols[h] = '\0';
		char newSymbol[dim] = "";
		char getSymbol[dim] = "";
		int s = 0, t = 0, k = 0;
		for (s = 0; symbols[s] != '\0'; s++) {
			t = 0;
			while (symbols[s] != ','&&symbols[s] != '\0') {
				getSymbol[t] = symbols[s];
				t++; s++;
			}
			getSymbol[t] = '\0';
			if (isEqual("==", getSymbol)) {
				newSymbol[k] = '0';
				k++;
			}
			if (isEqual("!=", getSymbol)) {
				newSymbol[k] = '1';
				k++;
			}
			if (isEqual("<=", getSymbol)) {
				newSymbol[k] = '2';
				k++;
			}
			if (isEqual(">=", getSymbol)) {
				newSymbol[k] = '3';
				k++;
			}
			if (isEqual(">", getSymbol)) {
				newSymbol[k] = '4';
				k++;
			}
			if (isEqual("<", getSymbol)) {
				newSymbol[k] = '5';
				k++;
			}
			if (isEqual("&&", getSymbol)) {
				newSymbol[k] = '6';
				k++;
			}
			if (isEqual("||", getSymbol)) {
				newSymbol[k] = '7';
				k++;
			}
		}
		sprintf(expressionF, valuesToExtract);
		if (isContained("  ", expressionF)) {
			replace("  ", ",", valuesToExtract);
		}
		if (isContained(" ", expressionF)) {
			replace(" ", ",", expressionF);
		}
		sprintf(valuesToExtract, expressionF);


		double valuesR[dim], valuesI[dim];
		char values[DIM] = "";
		int f = 0;
		for (g = 0; valuesToExtract[g] != '\0'; g++) {
			h = 0;
			while (valuesToExtract[g] == '(') {
				g++;
			}
			if (valuesToExtract[g] != ','&&valuesToExtract[g] != '\0'&&valuesToExtract[g] != ')') {
				while (valuesToExtract[g] != ','&&valuesToExtract[g] != '\0'&&valuesToExtract[g] != ')') {
					values[h] = valuesToExtract[g];
					h++; g++;
				}
				values[h] = '\0';
				if (isContained(" ", values)) {
					replace(" ", "", values);
					sprintf(values, expressionF);
				}
				calcNow(values, 0, 0);
				valuesR[f] = resultR;
				valuesI[f] = resultI;
				f++;
			}
		}
		h = 0;
		boolean results[dim];
		while (h < f) {
			results[h] = 0;
			h++;
		}
		boolean result = false;
		int cp = 0, mark = 0;
		int c = 0, d = 0, l = 0, parent[DIM];
		s = 0; k = 0; h = 0; g = 0;
		for (s = 0; s < abs((int)strlen(expression)); s++) {
			parent[s] = 0;
		}
		for (s = 0; expression[s] != '\0'&&s < abs((int)strlen(expression)); s++) {
			if (expression[s] == '(') {
				d = 0;
				c++;
				parent[s] = c;
				d = 1;
				k = c;
			}
			else {
				if (expression[s] == ')') {
					d = 0;
					h = 0;
					l = 2;
					do {
						l = 0;
						h = 0;
						while (h < abs((int)strlen(expression))) {
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
					while (l != 1 && h < abs((int)strlen(expression))) {
						h = 0;
						l = 0;
						while (h < abs((int)strlen(expression))) {
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
		h = 0;
		char amp[DIM] = "";
		int j = 0;
		l = 0; k = 0;
		char expToSolve[DIM] = "";
		for (j = 0; j < s; j++) {
			if (parent[j] == 0) {
				k = 0;
				while (parent[j] == 0 && j < s) {
					expToSolve[k] = expression[j];
					j++; k++;
				}
				expToSolve[k] = '\0';
				simpleEvaluator(expToSolve);
			}
			else {
				k = 0;
				l = parent[j];
				j++;
				while (parent[j] != l && j < s) {
					expToSolve[k] = expression[j];
					j++; k++;
				}
				expToSolve[k] = '\0';
				advancedEvaluator(expToSolve);
			}
		}
		h = 0;
		g = 0;
		while (h < k) {
			if (newSymbol[h] == '0') {
				if (valuesR[g] == valuesR[g + 1] && valuesI[g] == valuesI[g + 1]) {
					results[h] = true;
				}
				else {
					results[h] = false;
				}
				char df[5] = "";
				sprintf(df, "%c", newSymbol[h + 1]);
				if (atoi(df) > 5) {
					g = g + 2;
					h++;
				}
			}
			if (newSymbol[h] == '1') {
				if (valuesR[g] != valuesR[g + 1] || valuesI[g] != valuesI[g + 1]) {
					results[h] = true;
				}
				else {
					results[h] = false;
				}
				char df[5] = "";
				sprintf(df, "%c", newSymbol[h + 1]);
				if (atoi(df) > 5) {
					g = g + 2;
					h++;
				}
			}
			if (newSymbol[h] == '2') {
				if (valuesR[g] <= valuesR[g + 1] && valuesI[g] <= valuesI[g + 1]) {
					results[h] = true;
				}
				else {
					results[h] = false;
				}
				char df[5] = "";
				sprintf(df, "%c", newSymbol[h + 1]);
				if (atoi(df) > 5) {
					g = g + 2;
					h++;
				}
			}
			if (newSymbol[h] == '3') {
				if (valuesR[g] >= valuesR[g + 1] && valuesI[g] >= valuesI[g + 1]) {
					results[h] = true;
				}
				else {
					results[h] = false;
				}
				char df[5] = "";
				sprintf(df, "%c", newSymbol[h + 1]);
				if (atoi(df) > 5) {
					g = g + 2;
					h++;
				}
			}
			if (newSymbol[h] == '4') {
				if (valuesR[g] > valuesR[g + 1]) {
					results[h] = true;
				}
				else {
					if (valuesR[g] == valuesR[g + 1] && valuesI[g] > valuesI[g + 1]) {
						results[h] = true;
					}
					else {
						results[h] = false;
					}
				}
				char df[5] = "";
				sprintf(df, "%c", newSymbol[h + 1]);
				if (atoi(df) > 5) {
					g = g + 2;
					h++;
				}
			}
			if (newSymbol[h] == '5') {
				if (valuesR[g] < valuesR[g + 1]) {
					results[h] = true;
				}
				else {
					if (valuesR[g] == valuesR[g + 1] && valuesI[g] < valuesI[g + 1]) {
						results[h] = true;
					}
					else {
						results[h] = false;
					}
				}
				char df[5] = "";
				sprintf(df, "%c", newSymbol[h + 1]);
				if (atoi(df) > 5) {
					g = g + 2;
					h++;
				}
			}
			h++;
		}
		g = 0;
		int i = 0;
		boolean finalResult = results[g];
		while (g < h) {
			if (newSymbol[g] == '6') {
				if (finalResult && results[g + 1]) {
					finalResult = true;
				}
				else {
					finalResult = false;
				}
			}
			if (newSymbol[g] == '7') {
				if (finalResult || results[g + 1]) {
					finalResult = true;
				}
				else {
					finalResult = false;
				}
			}
			g++;
		}
		return finalResult;
	}
	return false;
}

boolean simpleEvaluator(char expression[DIM]) {
	int toSolve = 0;
	char saveExpression[DIM] = "";

	sprintf(expressionF, expression);
	if (isContained("==", expressionF)) {
		toSolve = 1;
		replace("==", "  ", expressionF);
	}
	if (isContained("!=", expressionF)) {
		toSolve = 1;
		replace("!=", "  ", expressionF);
	}
	if (isContained("<=", expressionF)) {
		toSolve = 1;
		replace("<=", "  ", expressionF);
	}
	if (isContained(">=", expressionF)) {
		toSolve = 1;
		replace(">=", "  ", expressionF);
	}
	if (isContained(">", expressionF)) {
		toSolve = 1;
		replace(">", " ", expressionF);
	}
	if (isContained("<", expressionF)) {
		toSolve = 1;
		replace("<", " ", expressionF);
	}
	if (isContained("&&", expressionF)) {
		toSolve = 1;
		replace("&&", "  ", expressionF);
	}
	if (isContained("||", expressionF)) {
		toSolve = 1;
		replace("||", "  ", expressionF);
	}
	char valuesToExtract[DIM] = "";
	sprintf(valuesToExtract, expressionF);
	int s = 0, k = 0;
	for (s = 0; valuesToExtract[s] != '\0'; s++) {
		if (valuesToExtract[s] != ' '&&valuesToExtract[s] != '\0') {
			k = 0;
			char toReplace[DIM] = "";
			while (valuesToExtract[s] != ' '&&valuesToExtract[s] != '\0') {
				toReplace[k] = valuesToExtract[s];
				k++;
				s++;
			}
			toReplace[k] = '\0';
			char finalReplace[DIM] = "";
			sprintf(finalReplace, "(%s)", toReplace);
			if (isContained(finalReplace, expression) == (boolean)false) {
				char replacement[DIM] = "ABC CBA";
				sprintf(replacement, "ABC CBA");
				toReplace[k] = '\0';
				replace(toReplace, replacement, expression);
				replace("ABC", "(", expressionF);
				replace("CBA", ")", expressionF);
				replace(" ", toReplace, expressionF);
				sprintf(expression, expressionF);
			}
		}
	}
	sprintf(expressionF, expression);
	if (isContained("==", expressionF)) {
		toSolve = 1;
		replace("==", "  ", expressionF);
	}
	if (isContained("!=", expressionF)) {
		toSolve = 1;
		replace("!=", "  ", expressionF);
	}
	if (isContained("<=", expressionF)) {
		toSolve = 1;
		replace("<=", "  ", expressionF);
	}
	if (isContained(">=", expressionF)) {
		toSolve = 1;
		replace(">=", "  ", expressionF);
	}
	if (isContained(">", expressionF)) {
		toSolve = 1;
		replace(">", " ", expressionF);
	}
	if (isContained("<", expressionF)) {
		toSolve = 1;
		replace("<", " ", expressionF);
	}
	if (isContained("&&", expressionF)) {
		toSolve = 1;
		replace("&&", "  ", expressionF);
	}
	if (isContained("||", expressionF)) {
		toSolve = 1;
		replace("||", "  ", expressionF);
	}
	sprintf(valuesToExtract, expressionF);
	sprintf(saveExpression, expression);
	if (toSolve == 1) {
		char saveValues[DIM] = "";
		sprintf(valuesToExtract, expressionF);
		char symbols[DIM] = "";
		int g = 0, h = 0;
		for (g = 0; valuesToExtract[g] != '\0'; g++) {
			if (valuesToExtract[g] == ' ') {
				while (valuesToExtract[g] == ' ') {
					symbols[h] = saveExpression[g];
					h++; g++;
				}
				symbols[h] = ',';
				h++;
			}
		}
		symbols[h] = '\0';
		char newSymbol[dim] = "";
		char getSymbol[dim] = "";
		int s = 0, t = 0, k = 0;
		for (s = 0; symbols[s] != '\0'; s++) {
			t = 0;
			while (symbols[s] != ','&&symbols[s] != '\0') {
				getSymbol[t] = symbols[s];
				t++; s++;
			}
			getSymbol[t] = '\0';
			if (isEqual("==", getSymbol)) {
				newSymbol[k] = '0';
				k++;
			}
			if (isEqual("!=", getSymbol)) {
				newSymbol[k] = '1';
				k++;
			}
			if (isEqual("<=", getSymbol)) {
				newSymbol[k] = '2';
				k++;
			}
			if (isEqual(">=", getSymbol)) {
				newSymbol[k] = '3';
				k++;
			}
			if (isEqual(">", getSymbol)) {
				newSymbol[k] = '4';
				k++;
			}
			if (isEqual("<", getSymbol)) {
				newSymbol[k] = '5';
				k++;
			}
			if (isEqual("&&", getSymbol)) {
				newSymbol[k] = '6';
				k++;
			}
			if (isEqual("||", getSymbol)) {
				newSymbol[k] = '7';
				k++;
			}
		}
		sprintf(expressionF, valuesToExtract);
		if (isContained("  ", expressionF)) {
			replace("  ", ",", valuesToExtract);
		}
		if (isContained(" ", expressionF)) {
			replace(" ", ",", expressionF);
		}
		sprintf(valuesToExtract, expressionF);
		double valuesR[dim], valuesI[dim];
		char values[DIM] = "";
		int f = 0;
		for (g = 0; valuesToExtract[g] != '\0'; g++) {
			h = 0;
			while (valuesToExtract[g] == '(') {
				g++;
			}
			if (valuesToExtract[g] != ','&&valuesToExtract[g] != '\0'&&valuesToExtract[g] != ')') {
				while (valuesToExtract[g] != ','&&valuesToExtract[g] != '\0'&&valuesToExtract[g] != ')') {
					values[h] = valuesToExtract[g];
					h++; g++;
				}
				values[h] = '\0';
				if (isContained(" ", values)) {
					replace(" ", "", values);
					sprintf(values, expressionF);
				}
				calcNow(values, 0, 0);
				valuesR[f] = resultR;
				valuesI[f] = resultI;
				f++;
			}
		}
		h = 0;
		boolean results[dim];
		while (h < f) {
			results[h] = 0;
			h++;
		}
		h = 0;
		g = 0;
		while (h < k) {
			if (newSymbol[h] == '0') {
				if (valuesR[g] == valuesR[g + 1] && valuesI[g] == valuesI[g + 1]) {
					results[h] = true;
				}
				else {
					results[h] = false;
				}
				char df[5] = "";
				sprintf(df, "%c", newSymbol[h + 1]);
				if (atoi(df) > 5) {
					g = g + 2;
					h++;
				}
			}
			if (newSymbol[h] == '1') {
				if (valuesR[g] != valuesR[g + 1] || valuesI[g] != valuesI[g + 1]) {
					results[h] = true;
				}
				else {
					results[h] = false;
				}
				char df[5] = "";
				sprintf(df, "%c", newSymbol[h + 1]);
				if (atoi(df) > 5) {
					g = g + 2;
					h++;
				}
			}
			if (newSymbol[h] == '2') {
				if (valuesR[g] <= valuesR[g + 1] && valuesI[g] <= valuesI[g + 1]) {
					results[h] = true;
				}
				else {
					results[h] = false;
				}
				char df[5] = "";
				sprintf(df, "%c", newSymbol[h + 1]);
				if (atoi(df) > 5) {
					g = g + 2;
					h++;
				}
			}
			if (newSymbol[h] == '3') {
				if (valuesR[g] >= valuesR[g + 1] && valuesI[g] >= valuesI[g + 1]) {
					results[h] = true;
				}
				else {
					results[h] = false;
				}
				char df[5] = "";
				sprintf(df, "%c", newSymbol[h + 1]);
				if (atoi(df) > 5) {
					g = g + 2;
					h++;
				}
			}
			if (newSymbol[h] == '4') {
				if (valuesR[g] > valuesR[g + 1]) {
					results[h] = true;
				}
				else {
					if (valuesR[g] == valuesR[g + 1] && valuesI[g] > valuesI[g + 1]) {
						results[h] = true;
					}
					else {
						results[h] = false;
					}
				}
				char df[5] = "";
				sprintf(df, "%c", newSymbol[h + 1]);
				if (atoi(df) > 5) {
					g = g + 2;
					h++;
				}
			}
			if (newSymbol[h] == '5') {
				if (valuesR[g] < valuesR[g + 1]) {
					results[h] = true;
				}
				else {
					if (valuesR[g] == valuesR[g + 1] && valuesI[g] < valuesI[g + 1]) {
						results[h] = true;
					}
					else {
						results[h] = false;
					}
				}
				char df[5] = "";
				sprintf(df, "%c", newSymbol[h + 1]);
				if (atoi(df) > 5) {
					g = g + 2;
					h++;
				}
			}
			h++;
		}
		g = 0;
		int i = 0;
		boolean finalResult = results[g];
		while (g < h) {
			if (newSymbol[g] == '6') {
				if (finalResult && results[g + 1]) {
					finalResult = true;
				}
				else {
					finalResult = false;
				}
			}
			if (newSymbol[g] == '7') {
				if (finalResult || results[g + 1]) {
					finalResult = true;
				}
				else {
					finalResult = false;
				}
			}
			g++;
		}
		return finalResult;
	}
	return false;
}