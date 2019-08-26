

#include "stdafx.h"

void trianglesRectanglesSolver() {
	int continuF = 0;
	puts(" ");
	puts("This solver will give to you all trigonometrics unknowns in any triangle rectangle.\n");
	puts("If you don't know how to answer to a request, please enter '_1' and hit 'Enter';\nIf you know how to answer, enter the answer and hit 'Enter';\n\nYou must enter angles in degrees because, if not, you will get wrong results.");
	puts("\nLet's start!\n");
	do {
		_flushall();
		double hypotenuse, opposite, angleH, adjacent, angleH1, slopeH, allcorrect = 0, perslope;
		printf("Enter the hypotenuse value: ");
		hypotenuse = getValue();
		_flushall();
		if (hypotenuse > 0) {
			printf("Enter the angle formed by the hypotenuse with the adjacent: ");
			angleH = getValue();
			if (angleH > 0 && angleH < 90) {
				angleH = (angleH*M_PI) / 180;
				angleH1 = M_PI - (M_PI / 2) - angleH;
				opposite = hypotenuse * sin(angleH);
				adjacent = hypotenuse * cos(angleH);
				allcorrect = 1;
			}
			else {
				printf("Enter the adjacent value: ");
				adjacent = getValue();
				if (adjacent > 0) {
					slopeH = adjacent / hypotenuse;
					angleH = acos(slopeH);
					angleH1 = M_PI - (M_PI / 2) - angleH;
					opposite = hypotenuse * sin(angleH);
					allcorrect = 1;
				}
				else {
					printf("Enter the angle formed by the hypotenuse with the opposite: ");
					angleH1 = getValue();
					if (angleH1 > 0 && angleH1 < 90) {
						angleH1 = (angleH1*M_PI) / 180;
						angleH = M_PI - (M_PI / 2) - angleH1;
						opposite = hypotenuse * sin(angleH);
						adjacent = hypotenuse * cos(angleH);
						allcorrect = 1;
					}
					else {
						printf("Enter the opposite value: ");
						opposite = getValue();
						if (opposite > 0) {
							slopeH = opposite / hypotenuse;
							angleH = asin(slopeH);
							angleH1 = M_PI - (M_PI / 2) - angleH;
							adjacent = hypotenuse * cos(angleH);
							allcorrect = 1;
						}
						else {
							printf("Enter the slope percentage: ");
							perslope = getValue();
							if (perslope > 0 && perslope < 100) {
								perslope = (perslope / 100);
								angleH = atan(perslope);
								angleH1 = M_PI - (M_PI / 2) - angleH;
								adjacent = hypotenuse * cos(angleH);
								opposite = hypotenuse * sin(angleH);
								allcorrect = 1;
							}
						}
					}
				}
			}
		}
		else {
			printf("Enter the opposite value: ");
			opposite = getValue();
			if (opposite > 0) {
				printf("Enter the angle formed by the hypotenuse with the opposite: ");
				angleH1 = getValue();
				if (angleH1 > 0 && angleH1 < 90) {
					angleH1 = (angleH1*M_PI) / 180;
					angleH = M_PI - (M_PI / 2) - angleH1;
					hypotenuse = opposite / cos(angleH);
					adjacent = hypotenuse * cos(angleH);
					allcorrect = 1;
				}
				else {
					printf("Enter the angle formed by the hypotenuse with the adjacent: ");
					angleH = getValue();
					if (angleH > 0 && angleH < 90) {
						angleH = (angleH*M_PI) / 180;
						angleH1 = M_PI - (M_PI / 2) - angleH;
						hypotenuse = opposite / sin(angleH);
						adjacent = hypotenuse * cos(angleH);
						allcorrect = 1;
					}
					else {
						printf("Enter the adjacent value: ");
						adjacent = getValue();
						if (adjacent > 0) {
							slopeH = opposite / adjacent;
							angleH = atan(slopeH);
							angleH1 = M_PI - (M_PI / 2) - angleH;
							hypotenuse = adjacent / cos(angleH);
							allcorrect = 1;
						}
						else {
							printf("Enter the slope percentage: ");
							perslope = getValue();
							if (perslope > 0 && perslope < 100) {
								perslope = (perslope / 100);
								angleH = atan(perslope);
								angleH1 = M_PI - (M_PI / 2) - angleH;
								adjacent = (opposite / tan(angleH));
								hypotenuse = (adjacent / cos(angleH));
								allcorrect = 1;
							}
						}
					}
				}
			}
			else {
				printf("Enter the adjacent value: ");
				adjacent = getValue();
				if (adjacent > 0) {
					printf("Enter the angle formed by the hypotenuse with the adjacent: ");
					angleH = getValue();
					if (angleH > 0 && angleH < 90) {
						angleH = (angleH*M_PI) / 180;
						angleH1 = M_PI - (M_PI / 2) - angleH;
						hypotenuse = adjacent / cos(angleH);
						opposite = hypotenuse * sin(angleH);
						allcorrect = 1;
					}
					else {
						printf("Enter the angle formed by the hypotenuse with the opposite: ");
						angleH1 = getValue();
						if (angleH1 > 0 && angleH1 < 90) {
							angleH1 = (angleH1*M_PI) / 180;
							angleH = M_PI - (M_PI / 2) - angleH1;
							hypotenuse = adjacent / cos(angleH);
							opposite = hypotenuse * sin(angleH);
							allcorrect = 1;
						}
						else {
							printf("Enter the slope percentage: ");
							perslope = getValue();
							if (perslope > 0 && perslope < 100) {
								perslope = (perslope / 100);
								angleH = atan(perslope);
								angleH1 = M_PI - (M_PI / 2) - angleH;
								opposite = adjacent * tan(angleH);
								hypotenuse = adjacent / cos(angleH);
								allcorrect = 1;
							}
						}
					}
				}
				else {
					printf("Error: It is impossible to calculate all the unknowns without at least the value of the adjacent or the hypotenuse or the opposite!\n\n");
				}
			}
		}
		if (allcorrect == 1) {
			angleH = (angleH * 180) / M_PI;
			angleH1 = (angleH1 * 180) / M_PI;
			perslope = opposite / adjacent;
			perslope = perslope * 100;
			char report[DIM] = "";
			sprintf(report, "\n\nReport of results\n\nThe percentage of slope is equal to %lf percent;\nThe adjacent is equal to %G;\nThe opposite is equal to %G;\nThe hypotenuse is equal to %G;\nThe angle formed by the hypotenuse with the adjacent is equal to %G;\nThe angle formed by the hypotenuse with the opposite is equal to %G.\n\n", perslope, adjacent, opposite, hypotenuse, angleH, angleH1);
			int reportOption = 0;
			puts(report);
			reportOption = -1;
			while (reportOption != 0 && reportOption != 1) {
				I_O = true;
				printf("\nDo you want to export the report? (Yes -> 1 / No -> 0)\n");
				reportOption = (int)getValue();
			}
			fflush(NULL);
			if (reportOption == 1) {
				saveToReport(report);
			}
		}
		continuF = -1;
		while (continuF != 0 && continuF != 1) {
			I_O = true;
			printf("Do you want to analyze more some triangles rectangles?\n(Yes -> 1 / No -> 0)\n");
			continuF = (int)getValue();
		}
	} while (continuF == 1);
}

void saveToReport(char report[DIM]) {
	FILE *save = NULL;
	char pathName[DIM] = "";
	printf("\nDrag-and-drop to here your txt file to save the report.\n");
	getReady();
	while (save == NULL) {
		gets_s(pathName);
		if (isContained("\\", pathName)) {
			if (isContained("\"", pathName)) {
				replace("\"", "", pathName);
			}
			else {
				sprintf(expressionF, pathName);
			}
			replace("\\", "AZ", expressionF);
			replace("AZ", "\\\\", expressionF);
			sprintf(pathName, "%s", expressionF);
		}
		save = fopen(pathName, "r");
		if (save == NULL) {
			printf("\nDrag-and-drop to here your txt file to save the report.\n");
			getReady();
		}
	}
	if (save != NULL) {
		fclose(save);
	}
	save = NULL;
	while (save == NULL) {
		save = fopen(pathName, "w");
	}
	fputs(report, save);
	fclose(save);
	printf("\n==> Your report was saved successfully. <==\n\n");
}