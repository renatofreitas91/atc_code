
#include "stdafx.h"

void functionStudy(char function[DIM]) {
	char saveFunction[DIM] = "";
	sprintf(saveFunction, "%s", function);
	equationSolver(saveFunction);
	printf("\n==> Zeros and intersection with yy-axis <==\n");
	puts("\nIt intersects the xx-axis in the points below:");
	int i = 0, j = 0, z = 0;
	double zeroR[dim], zeroI[dim];
	char value[dim] = "";
	replaceTimes = 0;
	char saveExpF[DIM] = "";
	sprintf(saveExpF, "%s", expressionF);
	while (isContained("=", saveExpF)) {
		j = 0;
		i = strEnd;
		saveExpF[strStart] = ' ';
		while (saveExpF[i] != '\0'&&saveExpF[i] != '\n') {
			value[j] = saveExpF[i];
			i++; j++;
		}
		value[j] = '\0';
		printf("\n(%s,0)", value);
		if (isContained("-", value)) {
			replace("-", "_", value);
			sprintf(value, "%s", expressionF);
		}
		math_processor(value);
		zeroR[z] = resultR; zeroI[z] = resultI;
		z++;
	}
	double sortZeroR[dim], sortZeroI[dim];
	double theSmallerR, theSmallerI = 0;
	int  saveZ = z;
	int o = 0, saveIndex = -1;
	while (o < saveZ) {
		theSmallerR = 1E12;
		theSmallerI = 0;
		for (z = 0; z < saveZ; z++) {
			if (theSmallerR > zeroR[z]) {
				theSmallerR = zeroR[z];
				theSmallerI = zeroI[z];
				saveIndex = z;
			}
		}
		zeroR[saveIndex] = 1E12;
		zeroI[saveIndex] = 0;
		sortZeroR[o] = theSmallerR;
		sortZeroI[o] = theSmallerI;
		o++;
	}
	double saveResultR, saveResultI;
	processVariable("x");
	saveResultR = resultR; saveResultI = resultI;
	resultR = 0; resultI = 0;
	variableController("x", 0);
	math_processor(function);
	puts("\n\nIt intersects the yy-axis in the point below:\n");
	printf("\n(0,%G)\n", resultR);
	resultR = saveResultR; resultI = saveResultI;
	variableController("x", 0);
	printf("\n==> Asymptotes <==\n");
	char verticalAsymptotes[dim] = "";
	double resultFR = -0.1, resultFI = 0;
	xValuesR = 1E9; xValuesI = 0;
	math_processor(function);
	double minMaxR = resultR, minMaxI = resultI;
	int interval = 9, c = 1, d = 0;
	int x_values[1000];
	double y_valuesR[1000];
	double y_valuesI[1000];
	j = 0;
	int firstValueR = 0, secondValueR = 0, selected_X = 0;
	for (i = -interval; i < interval; i++) {
		xValuesR = (double)i; xValuesI = 0;
		math_processor(function);
		x_values[j] = i;
		y_valuesR[j] = resultR;
		y_valuesI[j] = resultI;
		j++;
	}
	boolean zero = false;
	while (i < 2 * interval - 2) {
		for (i = d; i < 2 * interval - 2; i++) {
			if (y_valuesR[i] > y_valuesR[i + 1] && y_valuesR[i + 3] > y_valuesR[i + 4] && y_valuesR[i + 3] > y_valuesR[i + 1]) {
				firstValueR = x_values[i + 2];
				secondValueR = x_values[i + 4];
				selected_X = x_values[i + 3];
				zero = true;
				break;
			}
			if (y_valuesR[i] < y_valuesR[i + 1] && y_valuesR[i + 3] < y_valuesR[i + 4] && y_valuesR[i + 3] < y_valuesR[i + 1]) {
				firstValueR = x_values[i + 2];
				secondValueR = x_values[i + 4];
				selected_X = x_values[i + 3];
				zero = true;
				break;
			}
		}
		if (zero) {
			zero = false;
			if (y_valuesR[firstValueR] != INF * 2 && y_valuesR[secondValueR] != INF * 2 && y_valuesR[selected_X] != INF * 2) {
				xValuesR = firstValueR; xValuesI = 0;
				double negYR = math_processor(function);
				double negYI = resultI;
				xValuesR = secondValueR; xValuesI = 0;
				double posYR = math_processor(function);
				double posYI = resultI;
				double dividend = (((negYR + negYI) - (posYR + posYI))*-1) / 2;
				division(dividend, 0, minMaxR, minMaxI);
				multiplication(resultR, resultI, -1, 0);
				sum(resultR, resultI, selected_X, 0);
				if (resultR > mINF&&resultR<INF&&resultI>mINF&&resultI < INF) {
					resultFR = resultR; resultFI = resultI;
					if (physics == (boolean)false) {
						complexNumber(resultFR, resultFI);
						sprintf(verticalAsymptotes, "%s\nx%d=%G", verticalAsymptotes, c, resultFR);
					}
					xValuesR = resultFR; xValuesI = resultFI;
					math_processor(function);
					c++;
				}
			}
			d = i + 1;
		}
		i++;
	}
	xValuesR = resultFR; xValuesI = resultFI;
	math_processor(function);
	if (strlen(verticalAsymptotes) > 0) {
		puts("\nHas as vertical asymptotes the lines below:");
		while (isContained("=", verticalAsymptotes)) {
			j = 0;
			i = strEnd;
			verticalAsymptotes[strStart] = ' ';
			while (verticalAsymptotes[i] != '\0'&&verticalAsymptotes[i] != '\n') {
				value[j] = verticalAsymptotes[i];
				i++; j++;
			}
			value[j] = '\0';
			printf("\nx=%s", value);
		}
	}
	else {
		puts("\nIt does not have vertical asymptotes, so, the Domain is R.");
	}
	processVariable("x");
	saveResultR = resultR; saveResultI = resultI;
	resultR = 1E50; resultI = 0;
	variableController("x", 0);
	math_processor(function);
	if (abs(resultR) < 1E50) {
		printf("\nHas a horizontal asymptote when lim x-> +inf: %G\n", resultR);
	}
	else {
		puts("\nIt does not have a horizontal asymptote when lim x-> +inf");
	}
	resultR = -1E50; resultI = 0;
	variableController("x", 0);
	math_processor(function);
	if (abs(resultR) < 1E50) {
		printf("\nHas a horizontal asymptote when lim x-> -inf: %G\n", resultR);
	}
	else {
		puts("\nIt does not have a horizontal asymptote when lim x-> -inf");
	}
	printf("\n==> Symmetries <==\n");
	double  minusfx[dim], fxminusx[dim], fx[dim];
	int y = 0;
	while (y < 100) {
		resultR = y - 50;
		variableController("x", 0);
		fx[y] = math_processor(function);
		minusfx[y] = fx[y] * -1;
		resultR = (y - 50)*-1;
		variableController("x", 0);
		fxminusx[y] = math_processor(function);
		y++;
	}
	y = 0;
	int yy = 0;
	while (y < 100) {
		if (fxminusx[y] == fx[y]) {
			while (fxminusx[y] == fx[y] && y < 100) {
				yy++; y++;
			}
		}
		else {
			y++;
		}
	}
	int neitherEvenAndOdd = 0;
	if (yy == 100) {
		puts("\nThe function is even.");
	}
	else {
		neitherEvenAndOdd++;
		puts("\nThe function is not even.");
	}
	yy = 0;
	y = 0;
	while (y < 100) {
		if (fxminusx[y] == minusfx[y]) {
			while (fxminusx[y] == minusfx[y] && y < 100) {
				yy++; y++;
			}
		}
		else {
			y++;
		}
	}
	if (yy == 100) {
		puts("\nThe function is odd.");
	}
	else {
		neitherEvenAndOdd++;
		puts("\nThe function is not odd.");
	}
	if (neitherEvenAndOdd == 2) {
		puts("\nThere is no symmetry of the graph with respect to the yy axis or the origin.");
	}
	printf("\n==> Function signal <==\n");
	z = 0;
	char yLessThanZero[DIM] = "", yMoreThanZero[DIM] = "";
	if (fx[0] < 0 && fx[100 - 1] < 0) {
		sprintf(yLessThanZero, "%s\n f(x) < 0 if x E ]-inf,%G[ U", yLessThanZero, sortZeroR[0]);
		sprintf(yMoreThanZero, "%s f(x) > 0 if x E", yMoreThanZero);
		while (z + 1 < saveZ) {
			if (z + 3 < saveZ) {
				sprintf(yMoreThanZero, "%s ]%G,%G[ U", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
				z++;
				sprintf(yLessThanZero, "%s ]%G,%G[ U", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
				z++;
			}
			else {
				sprintf(yMoreThanZero, "%s ]%G,%G[ ", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
				z++;
				sprintf(yLessThanZero, "%s ]%G,%G[ ", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
				z++;
			}
		}
		sprintf(yLessThanZero, "%sU ]%G, +inf[\n", yLessThanZero, sortZeroR[saveZ - 1]);
		puts(yLessThanZero);
		puts(yMoreThanZero);
	}
	if (fx[0] > 0 && fx[100 - 1] > 0) {
		printf("\n f(x) > 0 if x E ]-inf,%G[ U ]%G,+inf[\n", sortZeroR[0], sortZeroR[saveZ - 1]);
	}
	if (fx[0] > 0 && fx[100 - 1] < 0) {
		printf("\n f(x) > 0 if x E ]-inf,%G]\n", sortZeroR[0]);
		printf("\n f(x) < 0 if x E [%G,+inf[\n", sortZeroR[saveZ - 1]);
	}
	if (fx[0] < 0 && fx[100 - 1] > 0) {
		printf("\n f(x) < 0 if x E ]-inf,%G]\n", sortZeroR[0]);
		printf("\n f(x) > 0 if x E [%G,+inf[\n", sortZeroR[saveZ - 1]);
	}
	printf("\n==> Monotony interval and relative extremes <==\n");
	char toSimplify[DIM] = "";
	sprintf(toSimplify, "(%s)*(0x+1)", function);
	simpleSimplifyPolynomial(toSimplify);
	char simplifiedPoly[DIM] = "";
	sprintf(simplifiedPoly, "%s", expressionF);
	printf("\nf(x)=%s\n", simplifiedPoly);
	char* derivate = getDerivative(simplifiedPoly);
	printf("\nf'(x)=%s\n", derivate);
	printf("\n\tx\t\t-inf\t\t");
	replaceTimes = 0;
	char data[DIM] = "";
	sprintf(data, "%s", derivate);
	if (!isContained("\\", data)) {
		synTest = 0;
		if (dataVerifier(data, 0, 0, 0, 1)) {
			sprintf(OutputText, "");
			replaceTimes = 0;
			if (!isContained("(", data)) {
				char saveData[dim] = "";
				sprintf(saveData, "(%s)+(0x+0)", data);
				sprintf(data, "%s", saveData);
			}
			else {
				if (isContained("((", data) && isContained("))", data)) {
					char saveData[dim] = "";
					sprintf(saveData, "%s", data);
					sprintf(data, "%s", saveData);
				}
				else {
					char saveData[dim] = "";
					sprintf(saveData, "%s", data);
					sprintf(data, "%s", saveData);
				}
			}
			lastDividerR = 1;
			LastDividerR = 1;
			lastDividerI = 0;
			LastDividerI = 0;
			simplifyExpression(data);
			sprintf(data, "%s", expressionF);
		}
	}
	equationSolver(data);
	//puts(expressionF);
	sprintf(saveExpF, "%s", expressionF);
	z = 0;
	while (isContained("=", saveExpF)) {
		j = 0;
		i = strEnd;
		saveExpF[strStart] = ' ';
		while (saveExpF[i] != '\0'&&saveExpF[i] != '\n') {
			value[j] = saveExpF[i];
			i++; j++;
		}
		value[j] = '\0';
		//printf("\n(%s,0)", value);
		if (isContained("-", value)) {
			replace("-", "_", value);
			sprintf(value, "%s", expressionF);
		}
		math_processor(value);
		zeroR[z] = resultR; zeroI[z] = resultI;
		z++;
	}
	saveZ = z;
	o = 0; saveIndex = -1;
	while (o < saveZ) {
		theSmallerR = 1E12;
		theSmallerI = 0;
		for (z = 0; z < saveZ; z++) {
			if (theSmallerR > zeroR[z]) {
				theSmallerR = zeroR[z];
				theSmallerI = zeroI[z];
				saveIndex = z;
			}
		}
		zeroR[saveIndex] = 1E12;
		zeroI[saveIndex] = 0;
		sortZeroR[o] = theSmallerR;
		sortZeroI[o] = theSmallerI;
		o++;
	}
	o = 0;
	y = 0;
	while (o < saveZ) {
		printf("%.3f\t\t", sortZeroR[o]);
		o++;
		y++;
		if (o < saveZ) {
			printf("\t\t");
			y++;
		}
	}
	printf("+inf\n");
	printf("\n\tf'(x)\t\t");
	resultR = sortZeroR[0] - 1000; resultI = 0;
	variableController("x", 0);
	math_processor(data);
	if (resultR > 0) {
		printf("+\t\t");
	}
	else {
		printf("-\t\t");
	}
	y = 0;
	o = 0;
	while (o < saveZ) {
		printf("0\t\t");
		o++;
		y++;
		if (o < saveZ) {
			resultR = (sortZeroR[o - 1] + sortZeroR[o]) / 2; resultI = 0;
			variableController("x", 0);
			math_processor(data);
			if (resultR > 0) {
				printf("+\t\t");
			}
			else {
				printf("-\t\t");
			}
			y++;
		}
	}
	resultR = sortZeroR[o - 1] + 1000; resultI = 0;
	variableController("x", 0);
	math_processor(data);
	if (resultR > 0) {
		printf("+\t\t");
	}
	else {
		printf("-\t\t");
	}
	printf("\n\tf(x)\t\t");
	resultR = sortZeroR[0] - 1000; resultI = 0;
	variableController("x", 0);
	math_processor(data);
	if (resultR > 0) {
		printf("/^\t\t");
	}
	else {
		printf("\\v\t\t");
	}
	y = 0;
	o = 0;
	while (o < saveZ) {
		resultR = sortZeroR[o]; resultI = 0;
		variableController("x", 0);
		math_processor(saveFunction);
		printf("%.3f\t\t", resultR);
		o++;
		y++;
		if (o < saveZ) {
			resultR = (sortZeroR[o - 1] + sortZeroR[o]) / 2; resultI = 0;
			variableController("x", 0);
			math_processor(data);
			if (resultR > 0) {
				printf("/^\t\t");
			}
			else {
				printf("\\v\t\t");
			}
			y++;
		}
	}
	resultR = sortZeroR[o - 1] + 1000; resultI = 0;
	variableController("x", 0);
	math_processor(data);
	if (resultR > 0) {
		printf("/^\t\t");
	}
	else {
		printf("\\v\t\t");
	}
	o = 0;
	puts(" ");
	printf("\n==> Direction of concavity and inflection points <==\n");
	printf("\nf'(x)=%s\n", data);
	derivate = getDerivative(data);
	printf("\nf''(x)=%s\n", derivate);
	if (!isContained("x", derivate)) {
		if (isContained("_", derivate)) {
			puts("\nThe function has no inflection points and the concavity is always facing down.\n");
		}
		else {
			puts("\nThe function has no inflection points and the concavity is always facing up.\n");
		}
	}
	printf("\n==> Codomain and absolute extremes <==\n");
	printf("\nCodomain: ]-inf,");
	while (o < saveZ) {
		resultR = sortZeroR[o];
		resultI = sortZeroI[o];
		variableController("x", 0);
		resultR = math_processor(saveFunction);
		if (resultR > 0) {
			if (saveZ == 1) {
				printf("%G]", resultR);
			}
			else {
				if (o % 2 == 0) {
					printf("%G[", resultR);
				}
				else {
					printf("U]%G,", resultR);
				}
			}
		}
		else {
			if (saveZ == 1) {
				printf(",%G]", resultR);
			}
			else {
				if (o % 2 == 0) {
					printf("%G[", resultR);
				}
				else {
					printf("U]%G,", resultR);
				}
			}
		}
		o++;
	}
	if (saveZ != 1) {
		printf("+inf[\n");
	}
	o = 0;
	while (o < saveZ) {
		resultR = sortZeroR[o];
		resultI = sortZeroI[o];
		variableController("x", 0);
		resultR = math_processor(saveFunction);
		if (resultR > 0) {
			printf("\nMax: (%G,%G)\n", sortZeroR[o], resultR);
		}
		else {
			printf("\nMin: (%G,%G)\n", sortZeroR[o], resultR);
		}
		o++;
	}
	resultR = saveResultR; resultI = saveResultI;
	variableController("x", 0);
	puts("");
}