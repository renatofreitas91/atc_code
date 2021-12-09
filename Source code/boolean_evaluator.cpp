
#include "stdafx.h"

boolean advancedEvaluator(char expression[DIM]) {
	int h = 0;
	boolean result = false;
	int cp = 0, mark = 0;
	int c = 0, d = 0, l = 0, parent[DIM];
	int s = 0, k = 0, g = 0;
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
	int klp = s;
	expression[s] = '\0';
	int curPar = 0, cur = 0;
	int i = 0;
	for (i = 0; expression[i] != '\0'; i++) {
		if (expression[i] == '(' || expression[i] == ')') {
			curPar = 1;
		}
	}
	expression[i] = '\0';
	if (curPar == 0) {
		result = simpleEvaluator(expression);
		sprintf(expression, "");
		return result;
	}
	replaceTimes = 0;
	char amp[DIM] = "";
	int j = 0;
	l = 0; k = 0;
	int a = 0;
	int de = 0, ju = 0;
	c = 0;
	char pas[DIM] = "";
	int se = 0;
	int thj = 0;
	char newExpression[DIM] = "";
	if (curPar == 1) {
		for (i = 0; i < abs((int)strlen(expression)); i++) {
			a = 0;
			while (!isContainedByIndex("&&", expression, i) && !isContainedByIndex("||", expression, i) && parent[i] == 0 && i < abs((int)strlen(expression))) {
				pas[a] = expression[i];
				a++;
				i++;
				if (!parent[i] == 0) {
					if (countOccurrences("(", pas) > countOccurrences(")", pas)) {
						sprintf(pas, "%s)", pas);
						i++;
						a = abs((int)strlen(pas));
					}
					else {
						pas[a] = '\0';
						a--;
						while (verifyLetter(pas[a])) {
							a--;
						}
						a++;
						char function[DIM] = "";
						int x = 0;
						while (verifyLetter(pas[a])) {
							function[x] = pas[a];
							x++; a++;
						}
						function[x] = '?'; function[x + 1] = '\0';
						double funcF = functionProcessor(function, 2, 7, 12, "");
						if (funcF == 0.5) {
							pas[a] = expression[i];
							a++;
							i++;
						}
					}
				}
			}
			pas[a] = '\0';
			if (strlen(pas) > 0) {
				result = simpleEvaluator(pas);
				if (result) {
					if (isContainedByIndex("&&", expression, i)) {
						sprintf(newExpression, "%s1==1&&", newExpression);
					}
					else {
						if (isContainedByIndex("||", expression, i)) {
							sprintf(newExpression, "%s1==1||", newExpression);
						}
					}
				}
				else {
					if (isContainedByIndex("&&", expression, i)) {
						sprintf(newExpression, "%s1==2&&", newExpression);
					}
					else {
						if (isContainedByIndex("||", expression, i)) {
							sprintf(newExpression, "%s1==2||", newExpression);
						}
					}
				}
				pas[0] = '\0';
			}
			pas[a] = '\0';
			cur = parent[i];
			j = i;
			if (parent[i] == cur) {
				i = j;
				a = 0;
				i++;
				while (parent[i] != cur && i < abs((int)strlen(expression))) {
					pas[a] = expression[i];
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
					if (strlen(pas) > 0) {
						result = simpleEvaluator(pas);
						if (result) {
							if (isContainedByIndex("&&", expression, i)) {
								sprintf(newExpression, "%s1==1&&", newExpression);
							}
							else {
								if (isContainedByIndex("||", expression, i)) {
									sprintf(newExpression, "%s1==1||", newExpression);
								}
							}
						}
						else {
							if (isContainedByIndex("&&", expression, i)) {
								sprintf(newExpression, "%s1==2&&", newExpression);
							}
							else {
								if (isContainedByIndex("||", expression, i)) {
									sprintf(newExpression, "%s1==2||", newExpression);
								}
							}
						}
					}
					pas[0] = '\0';
					ju = 0;

				}
				if (kl == 1) {
					if (strlen(pas) > 0) {
						result = advancedEvaluator(pas);
						if (result) {
							if (isContainedByIndex("&&", expression, i)) {
								sprintf(newExpression, "%s1==1&&", newExpression);
							}
							else {
								if (isContainedByIndex("||", expression, i)) {
									sprintf(newExpression, "%s1==1||", newExpression);
								}
							}
						}
						else {
							if (isContainedByIndex("&&", expression, i)) {
								sprintf(newExpression, "%s1==2&&", newExpression);
							}
							else {
								if (isContainedByIndex("||", expression, i)) {
									sprintf(newExpression, "%s1==2||", newExpression);
								}
							}
						}
					}
				}
			}
		}
	}
	return result;
}

boolean simpleEvaluator(char expression[DIM]) {
	renamer(expression);
	sprintf(expression, "%s", expressionF);
	int i = 0;
	if (isContained("iscontained(", expression)) {
		i = strEnd;
		int saveStrStart = strStart;
		int j = 0;
		char to_find[DIM] = "", data[DIM] = "";
		if (countOccurrences("\\", expression) == 1) {
			while (expression[i] != '\\') {
				to_find[j] = expression[i];
				i++; j++;
			}
			to_find[j] = '\0';
			stringVariableToString(to_find);
			sprintf(to_find, "%s", variableSTring);
			i++;
			j = 0;
			while (expression[i] != ')'&&expression[i] != '\0') {
				data[j] = expression[i];
				i++; j++;
			}
			data[j] = '\0';
			stringVariableToString(data);
			sprintf(data, "%s", variableSTring);
			int save_i = i + 1;
			char toReplace[DIM] = "";
			i = saveStrStart;
			j = 0;
			while (i < save_i) {
				toReplace[j] = expression[i];
				i++; j++;
			}
			toReplace[j] = '\0';
			char replacement[DIM] = "";
			if (isContained(to_find, data)) {
				sprintf(replacement, "1==1");
			}
			else {
				sprintf(replacement, "1==0");
			}
			replace(toReplace, replacement, expression);
			sprintf(expression, "%s", expressionF);
		}
		else {
			puts("\nError: Please use one time \"\\\" to separate the two variables.\n");
		}
	}
	if (isContained("iscontainedbyindex(", expression)) {
		i = strEnd;
		int saveStrStart = strStart;
		int j = 0;
		char to_find[DIM] = "", data[DIM] = "", index[DIM] = "";
		if (countOccurrences("\\", expression) == 2) {
			while (expression[i] != '\\') {
				to_find[j] = expression[i];
				i++; j++;
			}
			to_find[j] = '\0';
			stringVariableToString(to_find);
			sprintf(to_find, "%s", variableSTring);
			i++;
			j = 0;
			while (expression[i] != '\\') {
				data[j] = expression[i];
				i++; j++;
			}
			data[j] = '\0';
			stringVariableToString(data);
			sprintf(data, "%s", variableSTring);
			i++;
			j = 0;
			while (expression[i] != ')'&&expression[i] != '\0') {
				index[j] = expression[i];
				i++; j++;
			}
			index[j] = '\0';
			int index_num = (int)calcNow(index, 0, 0);
			int save_i = i + 1;
			char toReplace[DIM] = "";
			i = saveStrStart;
			j = 0;
			while (i < save_i) {
				toReplace[j] = expression[i];
				i++; j++;
			}
			toReplace[j] = '\0';
			char replacement[DIM] = "";
			if (isContainedByIndex(to_find, data, index_num)) {
				sprintf(replacement, "1==1");
			}
			else {
				sprintf(replacement, "1==0");
			}
			replace(toReplace, replacement, expression);
			sprintf(expression, "%s", expressionF);
		}
		else {
			puts("\nError: Please use two times \"\\\" to separate the three variables.\n");
		}
	}
	if (isContained("iscontainedvariable(", expression)) {
		i = strEnd;
		int saveStrStart = strStart;
		int j = 0;
		char to_find[DIM] = "", data[DIM] = "";
		if (countOccurrences("\\", expression) == 1) {
			while (expression[i] != '\\') {
				to_find[j] = expression[i];
				i++; j++;
			}
			to_find[j] = '\0';
			renamer(to_find);
			sprintf(to_find, "%s", expressionF);
			i++;
			j = 0;
			while (expression[i] != ')'&&expression[i] != '\0') {
				data[j] = expression[i];
				i++; j++;
			}
			data[j] = '\0';
			stringVariableToString(data);
			sprintf(data, "%s", variableSTring);
			renamer(data);
			sprintf(data, "%s", expressionF);
			int save_i = i + 1;
			char toReplace[DIM] = "";
			i = saveStrStart;
			j = 0;
			while (i < save_i) {
				toReplace[j] = expression[i];
				i++; j++;
			}
			toReplace[j] = '\0';
			char replacement[DIM] = "";
			if (isContainedVariable(to_find, data)) {
				sprintf(replacement, "1==1");
			}
			else {
				sprintf(replacement, "1==0");
			}
			replace(toReplace, replacement, expression);
			sprintf(expression, "%s", expressionF);
		}
		else {
			puts("\nError: Please use one time \"\\\" to separate the two variables.\n");
		}
	}
	if (isContained("isequal(", expression)) {
		i = strEnd;
		int saveStrStart = strStart;
		int j = 0;
		char to_find[DIM] = "", data[DIM] = "";
		if (countOccurrences("\\", expression) == 1) {
			while (expression[i] != '\\') {
				to_find[j] = expression[i];
				i++; j++;
			}
			to_find[j] = '\0';
			stringVariableToString(to_find);
			sprintf(to_find, "%s", variableSTring);
			i++;
			j = 0;
			while (expression[i] != ')'&&expression[i] != '\0') {
				data[j] = expression[i];
				i++; j++;
			}
			data[j] = '\0';
			stringVariableToString(data);
			sprintf(data, "%s", variableSTring);
			int save_i = i + 1;
			char toReplace[DIM] = "";
			i = saveStrStart;
			j = 0;
			while (i < save_i) {
				toReplace[j] = expression[i];
				i++; j++;
			}
			toReplace[j] = '\0';
			char replacement[DIM] = "";
			if (isEqual(to_find, data)) {
				sprintf(replacement, "1==1");
			}
			else {
				sprintf(replacement, "1==0");
			}
			replace(toReplace, replacement, expression);
			sprintf(expression, "%s", expressionF);
		}
		else {
			puts("\nError: Please use one time \"\\\" to separate the two variables.\n");
		}
	}
	if (isContained("isvariable(", expression)) {
		i = strEnd;
		int saveStrStart = strStart;
		int j = 0;
		char verify[DIM] = "";
		while (expression[i] != ')') {
			verify[j] = expression[i];
			i++; j++;
		}
		verify[j] = '\0';
		renamer(verify);
		sprintf(verify, "%s", expressionF);
		int save_i = i + 1;
		char toReplace[DIM] = "";
		i = saveStrStart;
		j = 0;
		while (i < save_i) {
			toReplace[j] = expression[i];
			i++; j++;
		}
		toReplace[j] = '\0';
		char replacement[DIM] = "";
		if (isVariable(verify)) {
			sprintf(replacement, "1==1");
		}
		else {
			sprintf(replacement, "1==0");
		}
		replace(toReplace, replacement, expression);
		sprintf(expression, "%s", expressionF);
	}
	if (isContained("istowrite(", expression)) {
		i = strEnd;
		int saveStrStart = strStart;
		int j = 0;
		char verify[DIM] = "";
		while (expression[i] != ')'&&expression[i] != '\0') {
			verify[j] = expression[i];
			i++; j++;
		}
		verify[j] = '\0';
		stringVariableToString(verify);
		sprintf(verify, "%s", variableSTring);
		int save_i = i + 1;
		char toReplace[DIM] = "";
		i = saveStrStart;
		j = 0;
		while (i < save_i) {
			toReplace[j] = expression[i];
			i++; j++;
		}
		toReplace[j] = '\0';
		char replacement[DIM] = "";
		if (isToWrite(verify)) {
			sprintf(replacement, "1==1");
		}
		else {
			sprintf(replacement, "1==0");
		}
		replace(toReplace, replacement, expression);
		sprintf(expression, "%s", expressionF);
	}
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
		char newSymbol[DIM] = "";
		char getSymbol[DIM] = "";
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
			if (valuesToExtract[g] != ','&&valuesToExtract[g] != '\0') {
				while (valuesToExtract[g] != ','&&valuesToExtract[g] != '\0') {
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
			results[h] = 1;
			h++;
		}
		h = 0;
		g = 0;
		while (verifyNumber(newSymbol[h])) {
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
		while (verifyNumber(newSymbol[g])) {
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

char* convertToSpaces(char* data) {
	char spaces[DIM] = "";
	int y = 0;
	while (y < abs((int)strlen(data))) {
		spaces[y] = ' ';
		y++;
	}
	spaces[y] = '\0';
	return spaces;
}