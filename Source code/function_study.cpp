
#include "stdafx.h"

boolean studyFunction = false;

void functionStudy(char function[DIM]) {
	replaceTimes = 0;
	if (isContained("(x)", function)) {
		replace("(x)", "x", function);
		sprintf(function, "%s", expressionF);
	}
	if (countOccurrences("/", function) > 1) {
		puts("\nError: Simplify your fractions first. You only can insert a fraction (a numerator divided by a denominator).\n");
	}
	else {
		studyFunction = true;
		double coDomain[dim];
		int u = 0;
		char saveFunctionF[DIM] = "";
		sprintf(saveFunctionF, "%s", function);
		char originalFunction[DIM] = "";
		sprintf(originalFunction, "%s", function);
		if (isContained("x", saveFunctionF)) {
			replaceTimes = 1;
			if (saveFunctionF[strEnd] != '^') {
				replace("x", "X^1", saveFunctionF);
				replace("X", "x", saveFunctionF);
				sprintf(saveFunctionF, "%s", expressionF);
			}
			replaceTimes = 0;
		}
		sprintf(function, "");
		double poleZerosR[dim], poleZerosI[dim];
		double intersectYY = 0, horizontalAssimptote = 0;
		int pl = 0;
		char numerator[DIM] = "", denominator[DIM] = "";
		if (isContained("/", saveFunctionF)) {
			int g = 0;
			while (saveFunctionF[g] != '/') {
				numerator[g] = saveFunctionF[g];
				g++;
			}
			numerator[g] = '\0';
			int h = strStart + 2;
			g = 0;
			while (saveFunctionF[h] != '\0') {
				denominator[g] = saveFunctionF[h];
				g++;
				h++;
			}
			denominator[g] = '\0';
			if (isContained("((", numerator) && !dataVerifier(numerator, 0, 0, 0, 1)) {
				replace("((", "(", numerator);
				sprintf(numerator, "%s", expressionF);
			}
			if (isContained("))", numerator) && !dataVerifier(numerator, 0, 0, 0, 1)) {
				replace("))", ")", numerator);
				sprintf(numerator, "%s", expressionF);
			}
			if (isContained("(((", numerator) && !dataVerifier(numerator, 0, 0, 0, 1)) {
				replace("(((", "((", numerator);
				sprintf(numerator, "%s", expressionF);
			}
			if (isContained(")))", numerator) && !dataVerifier(numerator, 0, 0, 0, 1)) {
				replace(")))", "))", numerator);
				sprintf(numerator, "%s", expressionF);
			}
			if (isContained("(((", denominator) && !dataVerifier(denominator, 0, 0, 0, 1)) {
				replace("(((", "((", denominator);
				sprintf(denominator, "%s", expressionF);
			}
			if (isContained(")))", denominator) && !dataVerifier(denominator, 0, 0, 0, 1)) {
				replace(")))", "))", denominator);
				sprintf(denominator, "%s", expressionF);
			}
			sprintf(saveFunctionF, "(%s)/(%s)", numerator, denominator);
			if (isContained("((", saveFunctionF) && !dataVerifier(saveFunctionF, 0, 0, 0, 1)) {
				replace("((", "(", saveFunctionF);
				sprintf(saveFunctionF, "%s", expressionF);
			}
			simplifyExpression(numerator);
			sprintf(numerator, "%s*(0x^1+1)", expressionF);
			simpleSimplifyPolynomial(numerator);
			sprintf(numerator, "%s", expressionF);
			simplifyExpression(denominator);
			sprintf(denominator, "(%s)*(0x^1+1)", expressionF);
			simpleSimplifyPolynomial(denominator);
			sprintf(denominator, "%s", expressionF);
		}
		else {
			simplifyExpression(saveFunctionF);
			sprintf(saveFunctionF, "(%s)*(0x^1+1)", expressionF);
			simpleSimplifyPolynomial(saveFunctionF);
			sprintf(saveFunctionF, "%s", expressionF);
		}
		if (strlen(denominator) > 0) {
			equationSolver(denominator);
			puts("\n==> Domain <==\n");
			printf("\nDf=R\\{");
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
				if (isContained("=", saveExpF)) {
					printf("%s,", value);
				}
				else {
					printf("%s}\n", value);
				}
				if (isContained("-", value)) {
					replace("-", "_", value);
					sprintf(value, "%s", expressionF);
				}
				math_processor(value);
				zeroR[z] = resultR; zeroI[z] = resultI;
				poleZerosR[pl] = resultR; poleZerosI[pl] = resultI;
				pl++;
				z++;
			}
		}
		char saveFunction[DIM] = "";
		if (strlen(numerator) > 0) {
			sprintf(saveFunction, "%s", numerator);
		}
		else {
			sprintf(saveFunction, "%s", saveFunctionF);
		}
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
			poleZerosR[pl] = resultR; poleZerosI[pl] = resultI;
			pl++;
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
		math_processor(originalFunction);
		puts("\n\nIt intersects the yy-axis in the point below:\n");
		printf("\n(0,%.3f)\n", resultR);
		intersectYY = resultR;
		coDomain[u] = intersectYY;
		u++;
		printf("\n==> Asymptotes <==\n");
		char verticalAsymptotes[DIM] = "";
		if (strlen(denominator) > 0) {
			equationSolver(denominator);
			int i = 0, j = 0, z = 0;
			char value[dim] = "";
			replaceTimes = 0;
			char saveExpF[DIM] = "";
			sprintf(verticalAsymptotes, "%s", expressionF);
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
				printf("\n");
			}
			else {
				puts("\nIt does not have vertical asymptotes, so, the Domain is R.");
			}
		}
		processVariable("x");
		saveResultR = resultR; saveResultI = resultI;
		resultR = 1E50; resultI = 0;
		variableController("x", 0);
		math_processor(originalFunction);
		char valueF[500] = "";
		sprintf(valueF, "%.3f", resultR);
		if (isContained("-", valueF)) {
			replace("-", "_", valueF);
			sprintf(valueF, "%s", expressionF);
		}
		math_processor(valueF);
		if (abs(resultR) < 1E50) {
			printf("\nHas a horizontal asymptote when lim x-> +inf: %.3f\n", resultR);
			horizontalAssimptote = resultR;
			coDomain[u] = horizontalAssimptote;
			u++;
		}
		else {
			puts("\nIt does not have a horizontal asymptote when lim x-> +inf");
		}
		resultR = -1E50; resultI = 0;
		variableController("x", 0);
		math_processor(originalFunction);
		sprintf(valueF, "%.3f", resultR);
		if (isContained("-", valueF)) {
			replace("-", "_", valueF);
			sprintf(valueF, "%s", expressionF);
		}
		math_processor(valueF);
		if (abs(resultR) < 1E50) {
			printf("\nHas a horizontal asymptote when lim x-> -inf: %.3f\n", resultR);
			horizontalAssimptote = resultR;
		}
		else {
			puts("\nIt does not have a horizontal asymptote when lim x-> -inf");
		}
		printf("\n==> Symmetries <==\n");
		char saveDenominator[DIM] = "";
		sprintf(saveDenominator, "%s", denominator);
		double  minusfx[dim], fxminusx[dim], fx[dim];
		int y = 0, p = 0;
		while (y < 10000) {
			resultR = y - 5000;
			resultI = 0;
			variableController("x", 0);
			if (strlen(denominator) > 0 && (int)math_processor(denominator) == 0) {
				fx[p] = resultR;
				fxminusx[p] = resultR;
			}
			else {
				fx[p] = math_processor(saveFunction);
				resultR = (y - 5000)*-1;
				resultI = 0;
				variableController("x", 0);
				fxminusx[p] = math_processor(saveFunction);
			}
			minusfx[p] = fx[p] * -1;
			y = y + 1000;
			p++;
		}
		y = 0;
		int yy = 0;
		p = 0;
		while (y < 10000) {
			if (fxminusx[p] == fx[p]) {
				while (fxminusx[p] == fx[p] && y < 10000) {
					yy = yy + 1000; y = y + 1000;
					p++;
				}
			}
			else {
				y = y + 1000;
				p++;
			}
		}
		int neitherEvenAndOdd = 0;
		if (yy == 10000) {
			puts("\nThe function is even.");
		}
		else {
			neitherEvenAndOdd++;
			puts("\nThe function is not even.");
		}
		yy = 0;
		y = 0;
		p = 0;
		while (y < 10000) {
			if (fxminusx[p] == minusfx[p]) {
				while (fxminusx[p] == minusfx[p] && y < 10000) {
					yy = yy + 1000; y = y + 1000;
					p++;
				}
			}
			else {
				y = y + 1000;
				p++;
			}
		}
		if (yy == 10000) {
			puts("\nThe function is odd.");
		}
		else {
			neitherEvenAndOdd++;
			puts("\nThe function is not odd.");
		}
		if (neitherEvenAndOdd == 2) {
			puts("\nThere is no symmetry of the graph with respect to the yy axis or the origin.");
		}
		sprintf(denominator, "%s", saveDenominator);
		printf("\n==> Function signal <==\n\n");
		if (strlen(numerator) == 0 && strlen(denominator) == 0) {
			z = 0;
			char yLessThanZero[DIM] = "", yMoreThanZero[DIM] = "";
			resultR = -1000; resultI = 0;
			variableController("x", 0);
			double negativeMax = math_processor(saveFunction);
			resultR = 1000; resultI = 0;
			variableController("x", 0);
			double positiveMax = math_processor(saveFunction);
			if (negativeMax < 0 && positiveMax < 0) {
				sprintf(yLessThanZero, "%s\n f(x) < 0 if x E ]-inf,%.3f[ U", yLessThanZero, sortZeroR[0]);
				sprintf(yMoreThanZero, "%s f(x) > 0 if x E", yMoreThanZero);
				while (z + 1 < saveZ) {
					if (z + 3 < saveZ) {
						if (z % 2 == 0) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ U", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ U", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
					else {
						if (z % 2 == 0) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ ", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ ", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
				}
				if (yLessThanZero[strlen(yLessThanZero) - 1] == 'U') {
					sprintf(yLessThanZero, "%s ]%.3f,+inf[\n", yLessThanZero, sortZeroR[saveZ - 1]);
				}
				else {
					sprintf(yLessThanZero, "%sU ]%.3f,+inf[\n", yLessThanZero, sortZeroR[saveZ - 1]);
				}
				puts(yLessThanZero);
				puts(yMoreThanZero);
			}
			if (negativeMax > 0 && positiveMax > 0) {
				sprintf(yMoreThanZero, "%s\n f(x) > 0 if x E ]-inf,%.3f[ U", yMoreThanZero, sortZeroR[0]);
				sprintf(yLessThanZero, "%s f(x) < 0 if x E", yLessThanZero);
				while (z + 1 < saveZ) {
					if (z + 3 < saveZ) {
						if (z % 2 == 1) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ U", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ U", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
					else {
						if (z % 2 == 1) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ ", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ ", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
				}
				if (yMoreThanZero[strlen(yMoreThanZero) - 1] == 'U') {
					sprintf(yMoreThanZero, "%s ]%.3f,+inf[\n", yMoreThanZero, sortZeroR[saveZ - 1]);
				}
				else {
					sprintf(yMoreThanZero, "%sU ]%.3f,+inf[\n", yMoreThanZero, sortZeroR[saveZ - 1]);
				}
				puts(yLessThanZero);
				puts(yMoreThanZero);
			}
			if (negativeMax > 0 && positiveMax < 0) {
				sprintf(yMoreThanZero, "%s\n f(x) > 0 if x E ]-inf,%.3f[ U", yMoreThanZero, sortZeroR[0]);
				sprintf(yLessThanZero, "%s f(x) < 0 if x E", yLessThanZero);
				while (z + 1 < saveZ) {
					if (z + 3 < saveZ) {
						if (z % 2 == 1) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ U", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ U", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
					else {
						if (z % 2 == 1) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ ", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ ", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
				}
				if (yLessThanZero[strlen(yLessThanZero) - 1] == 'U') {
					sprintf(yLessThanZero, "%s ]%.3f,+inf[\n", yLessThanZero, sortZeroR[saveZ - 1]);
				}
				else {
					sprintf(yLessThanZero, "%sU ]%.3f,+inf[\n", yLessThanZero, sortZeroR[saveZ - 1]);
				}
				puts(yLessThanZero);
				puts(yMoreThanZero);
			}
			if (negativeMax < 0 && positiveMax> 0) {
				sprintf(yLessThanZero, "%s\n f(x) < 0 if x E ]-inf,%.3f[ U", yLessThanZero, sortZeroR[0]);
				sprintf(yMoreThanZero, "%s f(x) > 0 if x E", yMoreThanZero);
				while (z + 1 < saveZ) {
					if (z + 3 < saveZ) {
						if (z % 2 == 0) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ U", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ U", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
					else {
						if (z % 2 == 0) {
							sprintf(yMoreThanZero, "%s ]%.3f,%.3f[ ", yMoreThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
						else {
							sprintf(yLessThanZero, "%s ]%.3f,%.3f[ ", yLessThanZero, sortZeroR[z], sortZeroR[z + 1]);
							z++;
						}
					}
				}
				if (yMoreThanZero[strlen(yMoreThanZero) - 1] == 'U') {
					sprintf(yMoreThanZero, "%s ]%.3f,+inf[\n", yMoreThanZero, sortZeroR[saveZ - 1]);
				}
				else {
					sprintf(yMoreThanZero, "%sU ]%.3f,+inf[\n", yMoreThanZero, sortZeroR[saveZ - 1]);
				}
				puts(yLessThanZero);
				puts(yMoreThanZero);
			}
		}
		else {
			double sortZeroR[dim], sortZeroI[dim];
			double theSmallerR, theSmallerI = 0;
			int  saveZ = pl;
			int o = 0, saveIndex = -1;
			while (o < saveZ) {
				theSmallerR = 1E12;
				theSmallerI = 0;
				for (z = 0; z < saveZ; z++) {
					if (theSmallerR > poleZerosR[z]) {
						theSmallerR = poleZerosR[z];
						theSmallerI = poleZerosI[z];
						saveIndex = z;
					}
				}
				poleZerosR[saveIndex] = 1E12;
				poleZerosI[saveIndex] = 0;
				sortZeroR[o] = theSmallerR;
				sortZeroI[o] = theSmallerI;
				o++;
			}
			removeTriplPars(numerator);
			sprintf(numerator, "%s", expressionF);
			removeDuplPars(numerator);
			sprintf(numerator, "%s", expressionF);
			printf("\nNumerator-> %s\n", numerator);
			sprintf(expressionF, "(%s)*(0x^1+1)", numerator);
			sprintf(numerator, "%s", expressionF);
			printf("\nDenominator-> %s\n", denominator);
			sprintf(expressionF, "(%s)*(0x^1+1)", denominator);
			sprintf(denominator, "%s", expressionF);
			printf("\nx\t\t-inf\t");
			o = 0;
			while (o < saveZ) {
				if (o < saveZ - 1) {
					printf("%.3f\t\t", sortZeroR[o]);
				}
				else {
					printf("%.3f\t", sortZeroR[o]);
				}
				o++;
			}
			printf("+inf\n");
			printf("\nNumerator\t");
			resultR = sortZeroR[0] - 1000; resultI = 0;
			variableController("x", 0);
			math_processor(numerator);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				variableController("x", 0);
				math_processor(numerator);
				if (abs(resultR) < 0.1) {
					printf("0\t");
				}
				else {
					if (resultR > 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
				}
				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					variableController("x", 0);
					math_processor(numerator);
					if (resultR > 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
					y++;
				}
			}
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			variableController("x", 0);
			math_processor(numerator);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			printf("\nDenominator\t");
			resultR = sortZeroR[0] - 1000; resultI = 0;
			variableController("x", 0);
			math_processor(denominator);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				variableController("x", 0);
				math_processor(denominator);
				if (abs(resultR) < 0.1) {
					printf("0\t");
				}
				else {
					if (resultR > 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
				}
				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					variableController("x", 0);
					math_processor(denominator);
					if (resultR > 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
					y++;
				}
			}
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			variableController("x", 0);
			math_processor(denominator);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			printf("\nf(x)\t\t");
			resultR = sortZeroR[0] - 1000; resultI = 0;
			variableController("x", 0);
			resultR = math_processor(numerator) / math_processor(denominator);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				variableController("x", 0);
				resultR = math_processor(numerator) / math_processor(denominator);
				if (abs(resultR) > 1E4 || abs(resultI) > 1E4) {
					resultR = pow(10, 400);
					printf("%.2f\t", resultR);
				}
				else {
					char expre[dim] = "";
					sprintf(expre, "%.2f\t", resultR);
					if (isContained("ind", expre)) {
						printf("ind\t");
					}
					else {
						printf("%s", expre);
					}
				}
				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					variableController("x", 0);
					resultR = math_processor(numerator) / math_processor(denominator);
					if (resultR > 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
					y++;
				}
			}
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			variableController("x", 0);
			resultR = math_processor(numerator) / math_processor(denominator);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
		}
		puts(" ");
		printf("\n==> Monotony interval and relative extremes <==\n");
		char new_derivate[DIM] = "";
		char new_numerator[DIM] = "";
		char new_denominator[DIM] = "";
		if (strlen(numerator) == 0 && strlen(denominator) == 0) {
			removeTriplPars(saveFunction);
			printf("\nf(x)=%s\n", expressionF);
			char* derivate = getDerivative(saveFunction);
			printf("\nf'(x)=%s\n", derivate);
			printf("\nx\t-inf\t");
			replaceTimes = 0;
			char data[DIM] = "";
			sprintf(data, "%s", derivate);
			equationSolver(data);
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
				printf("%.3f\t", sortZeroR[o]);
				o++;
				y++;
				if (o < saveZ) {
					printf("\t");
					y++;
				}
			}
			printf("+inf\n");
			printf("\nf'(x)\t");
			resultR = sortZeroR[0] - 1000; resultI = 0;
			variableController("x", 0);
			math_processor(data);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				printf("0\t");
				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					variableController("x", 0);
					math_processor(data);
					if (resultR > 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
					y++;
				}
			}
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			variableController("x", 0);
			math_processor(data);
			if (resultR > 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			printf("\nf(x)\t");
			resultR = sortZeroR[0] - 1000; resultI = 0;
			variableController("x", 0);
			math_processor(data);
			if (resultR > 0) {
				printf("/^\t");
			}
			else {
				printf("\\v\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				variableController("x", 0);
				math_processor(saveFunction);
				printf("%.3f\t", resultR);
				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					variableController("x", 0);
					math_processor(data);
					if (resultR > 0) {
						printf("/^\t");
					}
					else {
						printf("\\v\t");
					}
					y++;
				}
			}
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			variableController("x", 0);
			math_processor(data);
			if (resultR > 0) {
				printf("/^\t");
			}
			else {
				printf("\\v\t");
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
		}
		else {
			char new_numerator_1[DIM] = "";
			char new_numerator_2[DIM] = "";
			pl = 0;
			simpleSimplifyPolynomial(numerator);
			sprintf(numerator, "%s", expressionF);
			char * d_numerator = getDerivative(expressionF);
			char de_numerator[DIM] = "";
			sprintf(de_numerator, "%s", d_numerator);
			simpleSimplifyPolynomial(denominator);
			sprintf(denominator, "%s", expressionF);
			sprintf(saveFunctionF, "%s/%s", numerator, denominator);
			removeTriplPars(saveExpressionF);
			printf("\nf(x)=%s\n", expressionF);
			char * d_denominator = getDerivative(denominator);
			char de_denominator[DIM] = "";
			sprintf(de_denominator, "%s", d_denominator);
			if (isContained("x-", numerator)) {
				replace("x-", "x^1-", numerator);
				sprintf(numerator, "%s", expressionF);
			}
			sprintf(new_numerator_1, "(%s)*%s", denominator, de_numerator);
			sprintf(new_numerator_2, "%s*%s", numerator, de_denominator);
			removeTriplPars(new_numerator_1);
			sprintf(new_numerator_1, "%s", expressionF);
			simpleSimplifyPolynomial(new_numerator_1);
			sprintf(new_numerator_1, "%s", expressionF);
			removeTriplPars(new_numerator_2);
			sprintf(new_numerator_2, "%s", expressionF);
			simpleSimplifyPolynomial(new_numerator_2);
			sprintf(new_numerator_2, "%s", expressionF);
			sprintf(new_numerator, "%s-%s", new_numerator_1, new_numerator_2);
			removeTriplPars(new_numerator);
			sprintf(new_numerator, "%s", expressionF);
			simpleSimplifyPolynomial(new_numerator);
			sprintf(new_numerator, "%s", expressionF);
			sprintf(new_denominator, "(%s)*(%s)", denominator, denominator);
			removeTriplPars(new_denominator);
			sprintf(new_denominator, "%s", expressionF);
			simpleSimplifyPolynomial(new_denominator);
			sprintf(new_denominator, "%s", expressionF);
			if (isContained("x^1)", new_numerator) && strlen(new_numerator) == strEnd) {
				new_numerator[strlen(new_numerator) - 1] = '\0';
			}
			if (isContained("x^1)", new_denominator) && strlen(new_denominator) == strEnd) {
				new_denominator[strlen(new_denominator) - 1] = '\0';
			}
			sprintf(new_derivate, "%s/%s", new_numerator, new_denominator);
			printf("\nf'(x)=%s\n", new_derivate);
			printf("\nx\t-inf\t");
			replaceTimes = 0;
			removeDuplPars(new_numerator);
			sprintf(new_numerator, "%s", expressionF);
			equationSolver(new_numerator);
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
				if (isContained("-", value)) {
					replace("-", "_", value);
					sprintf(value, "%s", expressionF);
				}
				math_processor(value);
				zeroR[z] = resultR; zeroI[z] = resultI;
				poleZerosR[pl] = resultR; poleZerosI[pl] = resultI;
				pl++;
				z++;
			}
			equationSolver(denominator);
			i = 0; j = 0; z = 0;
			replaceTimes = 0;
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
				if (isContained("-", value)) {
					replace("-", "_", value);
					sprintf(value, "%s", expressionF);
				}
				math_processor(value);
				zeroR[z] = resultR; zeroI[z] = resultI;
				poleZerosR[pl] = resultR; poleZerosI[pl] = resultI;
				pl++;
				z++;
			}
			double sortZeroR[dim], sortZeroI[dim];
			double theSmallerR, theSmallerI = 0;
			int  saveZ = pl;
			int o = 0, saveIndex = -1;
			while (o < saveZ) {
				theSmallerR = 1E12;
				theSmallerI = 0;
				for (z = 0; z < saveZ; z++) {
					if (theSmallerR > poleZerosR[z]) {
						theSmallerR = poleZerosR[z];
						theSmallerI = poleZerosI[z];
						saveIndex = z;
					}
				}
				poleZerosR[saveIndex] = 1E12;
				poleZerosI[saveIndex] = 0;
				if (sortZeroR[o - 1] != theSmallerR && theSmallerR != 1E12 || o - 1 == -1) {
					sortZeroR[o] = theSmallerR;
					sortZeroI[o] = theSmallerI;
					o++;
				}
				else {
					saveZ--;
				}
			}
			saveZ = o;
			o = 0;
			y = 0;
			while (o < saveZ) {
				printf("%.3f\t", sortZeroR[o]);
				o++;
				y++;
				if (o < saveZ) {
					printf("\t");
					y++;
				}
			}
			printf("+inf\n");
			printf("\nf'(x)\t");
			resultR = sortZeroR[0] - 1000; resultI = 0;
			variableController("x", 0);
			removeDuplPars(new_numerator);
			sprintf(new_numerator, "%s", expressionF);
			removeDuplPars(new_denominator);
			sprintf(new_denominator, "%s", expressionF);
			resultR = math_processor(new_numerator) / math_processor(new_denominator);
			if (resultR >= 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				variableController("x", 0);
				resultR = math_processor(new_numerator) / math_processor(new_denominator);
				if (abs(resultR) > 1E4 || abs(resultI) > 1E4) {
					resultR = pow(10, 400);
					printf("%.2f\t", resultR);
				}
				else {
					char expre[dim] = "";
					sprintf(expre, "%.2f\t", resultR);
					if (isContained("ind", expre)) {
						printf("ind\t");
					}
					else {
						printf("%s", expre);
					}
				}
				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					variableController("x", 0);
					resultR = math_processor(new_numerator) / math_processor(new_denominator);
					if (resultR >= 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
					y++;
				}
			}
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			variableController("x", 0);
			resultR = math_processor(new_numerator) / math_processor(new_denominator);
			if (resultR >= 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			printf("\nf(x)\t");
			double slopeHelper = 0;
			resultR = sortZeroR[0] - 1000; resultI = 0;
			variableController("x", 0);
			resultR = math_processor(originalFunction);
			if (resultR >= 0) {
				printf("/^\t");
			}
			else {
				printf("\\v\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				variableController("x", 0);
				resultR = math_processor(originalFunction);
				if (abs(resultR) > 1E6 || abs(resultI) > 1E6) {
					resultR = pow(10, 400);
				}
				printf("%.3f\t", resultR);
				o++;
				y++;
				if (o < saveZ) {
					resultR = sortZeroR[o - 1] - 0.25; resultI = 0;
					slopeHelper = math_processor(originalFunction);
					resultR = sortZeroR[o - 1] + 0.77; resultI = 0;
					variableController("x", 0);
					resultR = math_processor(originalFunction);
					if (resultR > slopeHelper) {
						printf("/^\t");
					}
					else {
						printf("\\v\t");
					}
					y++;
				}
			}
			resultR = sortZeroR[o - 1] - 0.25; resultI = 0;
			slopeHelper = math_processor(originalFunction);
			resultR = sortZeroR[o - 1] + 1000; resultI = 0;
			variableController("x", 0);
			resultR = math_processor(originalFunction);
			if (resultR > slopeHelper) {
				printf("/^\t");
			}
			else {
				printf("\\v\t");
			}
			o = 0;
			puts(" ");
		}
		if (strlen(numerator) == 0 && strlen(denominator) == 0) {
			printf("\n==> Codomain and absolute extremes <==\n");
			if (saveZ != 1) {
				printf("\nCodomain: ]-inf,");
			}
			else {
				printf("\nCodomain: ]-inf");
			}
			while (o < saveZ) {
				resultR = sortZeroR[o];
				resultI = sortZeroI[o];
				variableController("x", 0);
				resultR = math_processor(saveFunction);
				if (saveZ == 1) {
					printf(",%.3f]", resultR);
				}
				else {
					if (o % 2 == 0) {
						printf("%.3f[", resultR);
					}
					else {
						printf("U]%.3f,", resultR);
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
				if (resultR >= 0) {
					printf("\nMax: (%.3f,%.3f)\n", sortZeroR[o], resultR);
				}
				else {
					printf("\nMin: (%.3f,%.3f)\n", sortZeroR[o], resultR);
				}
				o++;
			}
			puts("");
		}
		else {
			puts(" ");
			printf("\n==> Direction of concavity and inflection points <==\n");
			pl = 0;
			char * d_numerator = getDerivative(new_numerator);
			char de_numerator[DIM] = "";
			sprintf(de_numerator, "%s", d_numerator);
			sprintf(saveFunctionF, "(%s)/%s", new_numerator, new_denominator);
			printf("\nf'(x)=%s\n", saveFunctionF);
			char * d_denominator = getDerivative(new_denominator);
			char de_denominator[DIM] = "";
			sprintf(de_denominator, "%s", d_denominator);
			char sec_new_derivate[DIM] = "";
			char sec_new_numerator[DIM] = "";
			char sec_new_numerator_1[DIM] = "";
			char sec_new_numerator_2[DIM] = "";
			char sec_new_denominator[DIM] = "";
			sprintf(sec_new_numerator_1, "(%s)*%s", new_denominator, de_numerator);
			sprintf(sec_new_numerator_2, "%s*(%s)", de_denominator, new_numerator);
			simpleSimplifyPolynomial(sec_new_numerator_1);
			sprintf(sec_new_numerator_1, "%s", expressionF);
			sprintf(expressionF, "%s/(%s)", sec_new_numerator_1, denominator);
			if (isContained("(((", expressionF)) {
				replace("(((", "((", expressionF);
			}
			if (isContained(")))", expressionF)) {
				replace(")))", "))", expressionF);
			}
			simpleSimplifyPolynomial(expressionF);
			sprintf(sec_new_numerator_1, "%s", expressionF);
			simpleSimplifyPolynomial(sec_new_numerator_2);
			sprintf(sec_new_numerator_2, "%s", expressionF);
			sprintf(expressionF, "%s/(%s)", sec_new_numerator_2, denominator);
			if (isContained("(((", expressionF)) {
				replace("(((", "((", expressionF);
			}
			if (isContained(")))", expressionF)) {
				replace(")))", "))", expressionF);
			}
			simpleSimplifyPolynomial(expressionF);
			sprintf(sec_new_numerator_2, "%s", expressionF);
			sprintf(sec_new_numerator, "%s-%s", sec_new_numerator_1, sec_new_numerator_2);
			simpleSimplifyPolynomial(sec_new_numerator);
			sprintf(sec_new_numerator, "%s", expressionF);
			sprintf(sec_new_denominator, "(%s)*(%s)*(%s)", denominator, denominator, denominator);
			simpleSimplifyPolynomial(sec_new_denominator);
			sprintf(sec_new_denominator, "%s", expressionF);
			if (isContained("x^1)", sec_new_numerator) && strlen(sec_new_numerator) == strEnd) {
				sec_new_numerator[strlen(sec_new_numerator) - 1] = '\0';
			}
			if (isContained("x^1)", sec_new_denominator) && strlen(sec_new_denominator) == strEnd) {
				sec_new_denominator[strlen(sec_new_denominator) - 1] = '\0';
			}
			sprintf(sec_new_derivate, "(%s)/(%s)", sec_new_numerator, sec_new_denominator);
			sprintf(expressionF, "%s", sec_new_derivate);
			if (isContained("(((", expressionF)) {
				replace("(((", "((", expressionF);
			}
			if (isContained(")))", expressionF)) {
				replace(")))", "))", expressionF);
			}
			sprintf(sec_new_derivate, "%s", expressionF);
			printf("\nf''(x)=%s\n", sec_new_derivate);
			printf("\nx\t-inf\t");
			replaceTimes = 0;
			sprintf(expressionF, "");
			equationSolver(sec_new_numerator);
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
				if (isContained("-", value)) {
					replace("-", "_", value);
					sprintf(value, "%s", expressionF);
				}
				math_processor(value);
				zeroR[z] = resultR; zeroI[z] = resultI;
				poleZerosR[pl] = resultR; poleZerosI[pl] = resultI;
				pl++;
				z++;
			}
			equationSolver(denominator);
			i = 0; j = 0; z = 0;
			replaceTimes = 0;
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
				if (isContained("-", value)) {
					replace("-", "_", value);
					sprintf(value, "%s", expressionF);
				}
				math_processor(value);
				char ValueR[DIM] = "";
				sprintf(ValueR, convertToString("%.2f"), resultR);
				for (int v = 0; v < abs((int)(strlen(ValueR))); v++) {
					if (ValueR[v] == '-')
						ValueR[v] = '_';
				}
				math_processor(ValueR);
				zeroR[z] = resultR; zeroI[z] = resultI;
				poleZerosR[pl] = resultR; poleZerosI[pl] = resultI;
				pl++;
				z++;
			}
			double sortZeroR[dim], sortZeroI[dim];
			double theSmallerR, theSmallerI = 0;
			int  saveZ = pl;
			int o = 0, saveIndex = -1;
			while (o < saveZ) {
				theSmallerR = 1E12;
				theSmallerI = 0;
				for (z = 0; z < pl; z++) {
					if (theSmallerR > poleZerosR[z]) {
						theSmallerR = poleZerosR[z];
						theSmallerI = poleZerosI[z];
						saveIndex = z;
					}
				}
				poleZerosR[saveIndex] = 1E12;
				poleZerosI[saveIndex] = 0;
				if (sortZeroR[o - 1] != theSmallerR && theSmallerR != 1E12 || o - 1 == -1) {
					sortZeroR[o] = theSmallerR;
					sortZeroI[o] = theSmallerI;
					o++;
				}
				else {
					saveZ--;
				}
			}
			saveZ = o;
			o = 0;
			y = 0;
			while (o < saveZ) {
				printf("%.3f\t", sortZeroR[o]);
				o++;
				y++;
				if (o < saveZ) {
					printf("\t");
					y++;
				}
			}
			printf("+inf\n");
			printf("\nf''(x)\t");
			resultR = -1000; resultI = 0;
			variableController("x", 0);
			resultR = math_processor(sec_new_derivate);
			if (resultR >= 0) {
				printf("+\t");
			}
			else {
				printf("-\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				variableController("x", 0);
				resultR = math_processor(sec_new_derivate);
				if (abs(resultR) > 1E4 || abs(resultI) > 1E4) {
					resultR = pow(10, 400);
					printf("%.2f\t", resultR);
				}
				else {
					char expre[dim] = "";
					sprintf(expre, "%.2f\t", resultR);
					if (isContained("ind", expre)) {
						printf("ind\t");
					}
					else {
						printf("%s", expre);
					}
				}
				y++;
				if (o < saveZ) {
					if (saveZ - o >= 1) {
						resultR = sortZeroR[o] + 0.77; resultI = 0;
					}
					else {
						resultR = 1000; resultI = 0;
					}
					variableController("x", 0);
					resultR = math_processor(sec_new_derivate);
					if (resultR >= 0) {
						printf("+\t");
					}
					else {
						printf("-\t");
					}
					y++;
				}
				o++;
			}
			printf("\nf(x)\t");
			resultR = -1000; resultI = 0;
			variableController("x", 0);
			resultR = math_processor(sec_new_derivate);
			if (resultR < 0) {
				printf("/^\\\t");
			}
			else {
				printf("\\_/\t");
			}
			y = 0;
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o]; resultI = 0;
				variableController("x", 0);
				resultR = math_processor(originalFunction);
				if (abs(resultR) > 1E4 || abs(resultI) > 1E4) {
					resultR = pow(10, 400);
					printf("%.2f\t", resultR);
				}
				else {
					char expre[dim] = "";
					sprintf(expre, "%.2f\t", resultR);
					if (isContained("ind", expre)) {
						printf("ind\t");
					}
					else {
						printf("%s", expre);
					}
				}
				y++;
				if (o < saveZ) {
					if (saveZ - o >= 1) {
						resultR = sortZeroR[o] + 0.77; resultI = 0;
					}
					else {
						resultR = 1000; resultI = 0;
					}
					variableController("x", 0);
					resultR = math_processor(sec_new_derivate);
					if (resultR < 0) {
						printf("/^\\\t");
					}
					else {
						printf("\\_/\t");
					}
					y++;
				}
				o++;
			}
			puts(" ");
			resultR = saveResultR;  resultI = saveResultI;
			variableController("x", 0);
			printf("\n==> Codomain and absolute extremes <==\n");
			puts(" ");
			o = 0; saveIndex = -1;
			saveZ = u;
			while (o < saveZ) {
				theSmallerR = 1E12;
				theSmallerI = 0;
				for (z = 0; z < u; z++) {
					if (theSmallerR > coDomain[z]) {
						theSmallerR = coDomain[z];
						saveIndex = z;
					}
				}
				coDomain[saveIndex] = 1E12;
				if (sortZeroR[o - 1] != theSmallerR && theSmallerR != 1E12 || o - 1 == -1) {
					sortZeroR[o] = theSmallerR;
					sortZeroI[o] = theSmallerI;
					o++;
				}
				else {
					saveZ--;
				}
			}
			saveZ = u;
			o = 0;
			printf("\nCodomain: ]-inf,");
			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o];
				resultI = sortZeroI[o];
				if (saveZ == 1) {
					printf("%.3f]", resultR);
				}
				else {
					if (o % 2 == 0) {
						printf("%.3f[", resultR);
					}
					else {
						printf("U]%.3f,", resultR);
					}
				}
				o++;
			}
			if (saveZ != 1) {
				printf("+inf[\n");
			}
			o = 0;
			saveZ = pl;
			saveIndex = -1;
			while (o < saveZ) {
				theSmallerR = 1E12;
				theSmallerI = 0;
				for (z = 0; z < pl; z++) {
					if (theSmallerR > poleZerosR[z]) {
						theSmallerR = poleZerosR[z];
						theSmallerI = poleZerosI[z];
						saveIndex = z;
					}
				}
				poleZerosR[saveIndex] = 1E12;
				poleZerosI[saveIndex] = 0;
				if (sortZeroR[o - 1] != theSmallerR && theSmallerR != 1E12 || o - 1 == -1) {
					sortZeroR[o] = theSmallerR;
					sortZeroI[o] = theSmallerI;
					o++;
				}
				else {
					saveZ--;
				}
			}
			saveZ = o;
			equationSolver(new_numerator);
			i = 0, j = 0, z = 0;
			replaceTimes = 0;
			sprintf(saveExpF, "%s", expressionF);
			pl = 0;
			while (isContained("=", saveExpF)) {
				j = 0;
				i = strEnd;
				saveExpF[strStart] = ' ';
				while (saveExpF[i] != '\0'&&saveExpF[i] != '\n') {
					value[j] = saveExpF[i];
					i++; j++;
				}
				value[j] = '\0';
				if (isContained("-", value)) {
					replace("-", "_", value);
					sprintf(value, "%s", expressionF);
				}
				math_processor(value);
				zeroR[z] = resultR; zeroI[z] = resultI;
				poleZerosR[pl] = resultR; poleZerosI[pl] = resultI;
				pl++;
				z++;
			}
			saveZ = pl;
			o = 0, saveIndex = -1;
			while (o < saveZ) {
				theSmallerR = 1E12;
				theSmallerI = 0;
				for (z = 0; z < pl; z++) {
					if (theSmallerR > poleZerosR[z]) {
						theSmallerR = poleZerosR[z];
						theSmallerI = poleZerosI[z];
						saveIndex = z;
					}
				}
				poleZerosR[saveIndex] = 1E12;
				poleZerosI[saveIndex] = 0;
				if (sortZeroR[o - 1] != theSmallerR && theSmallerR != 1E12 || o - 1 == -1) {
					sortZeroR[o] = theSmallerR;
					sortZeroI[o] = theSmallerI;
					o++;
				}
				else {
					saveZ--;
				}
			}
			saveZ = o;

			o = 0;
			while (o < saveZ) {
				resultR = sortZeroR[o];
				resultI = sortZeroI[o];
				variableController("x", 0);
				resultR = math_processor(originalFunction);
				if (resultR >= 0) {
					printf("\nMax: (%.3f,%.3f)\n", sortZeroR[o], resultR);
				}
				else {
					printf("\nMin: (%.3f,%.3f)\n", sortZeroR[o], resultR);
				}
				o++;
			}
			puts("");
		}
		studyFunction = false;
	}
}