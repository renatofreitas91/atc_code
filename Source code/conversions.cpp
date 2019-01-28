#include "stdafx.h"

void unitConversions() {
	int op = 0, op1 = 1;
	do {
		fflush(NULL);
		puts("\nWhat to convert?\n");
		puts("Length -> 1");
		puts("Temperature -> 2");
		puts("Area -> 3");
		puts("Volume -> 4");
		puts("Weight -> 5");
		puts("Time -> 6");
		puts("Angle -> 7");
		op = (int)getValue();
		puts("");
		if (op == 1) {
			int opLength, opLength1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Meter -> 1");
				puts("Kilometer -> 2");
				puts("Centimeter -> 3");
				puts("Millimeter -> 4");
				puts("Micrometer -> 5");
				puts("Nanometer -> 6");
				puts("Mile -> 7");
				puts("Yard -> 8");
				puts("Foot -> 9");
				puts("Inch -> 10");
				puts("Light Year -> 11");
				opLength = (int)getValue();
				if (opLength < 1 || opLength>11) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("");
					double valueInMeters = 0;
					puts("Value?");
					double value = getValue();
					if (opLength == 1) {
						valueInMeters = value;
					}
					if (opLength == 2) {
						valueInMeters = value * 1000;
					}
					if (opLength == 3) {
						valueInMeters = value * 0.01;
					}
					if (opLength == 4) {
						valueInMeters = value * 0.001;
					}
					if (opLength == 5) {
						valueInMeters = value * 1E-6;
					}
					if (opLength == 6) {
						valueInMeters = value * 1E-9;
					}
					if (opLength == 7) {
						valueInMeters = value * 1609.35;
					}
					if (opLength == 8) {
						valueInMeters = value * 0.9144;
					}
					if (opLength == 9) {
						valueInMeters = value * 0.3048;
					}
					if (opLength == 10) {
						valueInMeters = value * 0.0254;
					}
					if (opLength == 11) {
						valueInMeters = value * 9.46066E15;
					}
					printf("\nMeter: %G", valueInMeters);
					printf("\nKilometer: %G", valueInMeters*0.001);
					printf("\nCentimeter: %G", valueInMeters * 100);
					printf("\nMillimeter: %G", valueInMeters * 1000);
					printf("\nMicrometer: %G", valueInMeters*1E6);
					printf("\nNanometer: %G", valueInMeters*1E9);
					printf("\nMile: %G", valueInMeters*0.0006213689);
					printf("\nYard: %G", valueInMeters*1.0936132983);
					printf("\nFoot: %G", valueInMeters*3.280839895);
					printf("\nInch: %G", valueInMeters*39.37007874);
					printf("\nLight Year: %G", valueInMeters * 1.057008707E-16);
				}
				fflush(NULL);
				printf("\n\nContinue with Length conversions? (Yes -> 1 / No -> 0)\n");
				opLength1 = (int)getValue();
			} while (opLength1 != 0);
		}
		if (op == 2) {
			int opTemperature, opTemperature1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Celsius -> 1");
				puts("Kelvin -> 2");
				puts("Fahrenheit -> 3");
				opTemperature = (int)getValue();
				if (opTemperature < 1 || opTemperature>3) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("");
					double valueInCelsius = 0;
					puts("Value?");
					double value = getValue();
					if (opTemperature == 1) {
						valueInCelsius = value;
					}
					if (opTemperature == 2) {
						valueInCelsius = value - 273.15;
					}
					if (opTemperature == 3) {
						valueInCelsius = (value - 32) / 1.8;
					}
					printf("\nCelsius: %G", valueInCelsius);
					printf("\nKelvin: %G", valueInCelsius + 273.15);
					printf("\nFahrenheit: %G", valueInCelsius*1.8 + 32);
				}
				fflush(NULL);
				printf("\n\nContinue with Temperature Conversions? (Yes -> 1 / No -> 0)\n");
				opTemperature1 = (int)getValue();
			} while (opTemperature1 != 0);
		}
		if (op == 3) {
			int opArea, opArea1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Square Meter -> 1");
				puts("Square Kilometer -> 2");
				puts("Square Centimeter -> 3");
				puts("Square Millimeter -> 4");
				puts("Square Micrometer -> 5");
				puts("Hectare -> 6");
				puts("Square Mile -> 7");
				puts("Square Yard -> 8");
				puts("Square Foot -> 9");
				puts("Square Inch -> 10");
				puts("Acre -> 11");
				opArea = (int)getValue();
				if (opArea < 1 || opArea>11) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("");
					double valueInSquareMeters = 0;
					puts("Value?");
					double value = getValue();
					if (opArea == 1) {
						valueInSquareMeters = value;
					}
					if (opArea == 2) {
						valueInSquareMeters = value * 1000000;
					}
					if (opArea == 3) {
						valueInSquareMeters = value * 0.0001;
					}
					if (opArea == 4) {
						valueInSquareMeters = value * 0.000001;
					}
					if (opArea == 5) {
						valueInSquareMeters = value * 1E-12;
					}
					if (opArea == 6) {
						valueInSquareMeters = value * 10000;
					}
					if (opArea == 7) {
						valueInSquareMeters = value * 2589990;
					}
					if (opArea == 8) {
						valueInSquareMeters = value * 0.83612736;
					}
					if (opArea == 9) {
						valueInSquareMeters = value * 0.09290304;
					}
					if (opArea == 10) {
						valueInSquareMeters = value * 0.00064516;
					}
					if (opArea == 11) {
						valueInSquareMeters = value * 4046.8564224;
					}
					printf("\nSquare Meter: %G", valueInSquareMeters);
					printf("\nSquare Kilometer: %G", valueInSquareMeters*0.000001);
					printf("\nSquare Centimeter: %G", valueInSquareMeters * 10000);
					printf("\nSquare Millimeter: %G", valueInSquareMeters * 1000000);
					printf("\nSquare Micrometer: %G", valueInSquareMeters * 1000000000000);
					printf("\nHectare: %G", valueInSquareMeters*0.0001);
					printf("\nSquare Mile: %G", valueInSquareMeters*3.861018768E-7);
					printf("\nSquare Yard: %G", valueInSquareMeters*1.1959900463);
					printf("\nSquare Foot: %G", valueInSquareMeters*10.763910417);
					printf("\nSquare Inch: %G", valueInSquareMeters*1550.0031);
					printf("\nAcre: %G", valueInSquareMeters * 0.0002471054);
				}
				fflush(NULL);
				printf("\n\nContinue with Area conversions? (Yes -> 1 / No -> 0)\n");
				opArea1 = (int)getValue();
			} while (opArea1 != 0);
		}
		if (op == 4) {
			int opVolume, opVolume1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Cubic Meter -> 1");
				puts("Cubic Kilometer -> 2");
				puts("Cubic Centimeter -> 3");
				puts("Cubic Millimeter -> 4");
				puts("Liter -> 5");
				puts("Milliliter -> 6");
				puts("US Gallon -> 7");
				puts("US Quart -> 8");
				puts("US Pint -> 9");
				puts("US Cup -> 10");
				puts("US Fluid Ounce -> 11");
				puts("US Table Spoon -> 12");
				puts("US Tea Spoon -> 13");
				puts("Imperial Gallon -> 14");
				puts("Imperial Quart -> 15");
				puts("Imperial Pint -> 16");
				puts("Imperial Fluid Ounce -> 17");
				puts("Imperial Table Spoon -> 18");
				puts("Imperial Tea Spoon -> 19");
				puts("Cubic Mile -> 20");
				puts("Cubic Yard -> 21");
				puts("Cubic Foot -> 22");
				puts("Cubic Inch -> 23");
				opVolume = (int)getValue();
				if (opVolume < 1 || opVolume>23) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("");
					double valueInCubicMeters = 0;
					puts("Value?");
					double value = getValue();
					if (opVolume == 1) {
						valueInCubicMeters = value;
					}
					if (opVolume == 2) {
						valueInCubicMeters = value * 1000000000;
					}
					if (opVolume == 3) {
						valueInCubicMeters = value * 0.000001;
					}
					if (opVolume == 4) {
						valueInCubicMeters = value * 1E-9;
					}
					if (opVolume == 5) {
						valueInCubicMeters = value * 0.001;
					}
					if (opVolume == 6) {
						valueInCubicMeters = value * 0.000001;
					}
					if (opVolume == 7) {
						valueInCubicMeters = value * 0.00378541;
					}
					if (opVolume == 8) {
						valueInCubicMeters = value * 0.0009463525;
					}
					if (opVolume == 9) {
						valueInCubicMeters = value * 0.0004731763;
					}
					if (opVolume == 10) {
						valueInCubicMeters = value * 0.0002365881;
					}
					if (opVolume == 11) {
						valueInCubicMeters = value * 0.0000295735;
					}
					if (opVolume == 12) {
						valueInCubicMeters = value * 0.0000147868;
					}
					if (opVolume == 13) {
						valueInCubicMeters = value * 0.0000049289;
					}
					if (opVolume == 14) {
						valueInCubicMeters = value * 0.00454609;
					}
					if (opVolume == 15) {
						valueInCubicMeters = value * 0.0011365225;
					}
					if (opVolume == 16) {
						valueInCubicMeters = value * 0.0005682613;
					}
					if (opVolume == 17) {
						valueInCubicMeters = value * 0.0000284131;
					}
					if (opVolume == 18) {
						valueInCubicMeters = value * 0.0000177582;
					}
					if (opVolume == 19) {
						valueInCubicMeters = value * 0.0000059194;
					}
					if (opVolume == 20) {
						valueInCubicMeters = value * 4168180000;
					}
					if (opVolume == 21) {
						valueInCubicMeters = value * 0.764554858;
					}
					if (opVolume == 22) {
						valueInCubicMeters = value * 0.0283168466;
					}
					if (opVolume == 23) {
						valueInCubicMeters = value * 0.0000163871;
					}
					printf("\nCubic Meter: %G", valueInCubicMeters);
					printf("\nCubic Kilometer: %G", valueInCubicMeters*1E-9);
					printf("\nCubic Centimeter: %G", valueInCubicMeters * 1000000);
					printf("\nCubic Millimeter: %G", valueInCubicMeters * 1000000000);
					printf("\nSquare Micrometer: %G", valueInCubicMeters * 1000000000000);
					printf("\nLiter: %G", valueInCubicMeters * 1000);
					printf("\nMilliliter: %G", valueInCubicMeters * 1000000);
					printf("\nUS Gallon: %G", valueInCubicMeters*264.17217686);
					printf("\nUS Quart: %G", valueInCubicMeters*1056.6887074);
					printf("\nUS Pint: %G", valueInCubicMeters*2113.3774149);
					printf("\nUS Cup: %G", valueInCubicMeters*4226.7548297);
					printf("\nUS Fluid Ounce: %G", valueInCubicMeters*33814.038638);
					printf("\nUS Table Spoon: %G", valueInCubicMeters*67628.077276);
					printf("\nUS Tea Spoon: %G", valueInCubicMeters*202884.23183);
					printf("\nImperial Gallon: %G", valueInCubicMeters*219.9692483);
					printf("\nImperial Quart: %G", valueInCubicMeters*879.8769932);
					printf("\nImperial Pint: %G", valueInCubicMeters*1759.7539864);
					printf("\nImperial Fluid Ounce: %G", valueInCubicMeters*35195.079728);
					printf("\nImperial Table Spoon: %G", valueInCubicMeters*56312.127565);
					printf("\nImperial Tea Spoon: %G", valueInCubicMeters*168936.38269);
					printf("\nCubic Mile: %G", valueInCubicMeters*2.399128636E-10);
					printf("\nCubic Yard: %G", valueInCubicMeters*1.3079506193);
					printf("\nCubic Foot: %G", valueInCubicMeters*35.314666721);
					printf("\nCubic Inch: %G", valueInCubicMeters*61023.744095);
				}
				fflush(NULL);
				printf("\n\nContinue with Volume conversions? (Yes -> 1 / No -> 0)\n");
				opVolume1 = (int)getValue();
			} while (opVolume1 != 0);
		}
		if (op == 5) {
			int opWeight, opWeight1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Kilogram -> 1");
				puts("Gram -> 2");
				puts("Milligram -> 3");
				puts("Metric Ton -> 4");
				puts("Long Ton -> 5");
				puts("Short Ton -> 6");
				puts("Pound -> 7");
				puts("Ounce -> 8");
				puts("Carrat -> 9");
				puts("Atomic Mass Unit -> 10");
				opWeight = (int)getValue();
				if (opWeight < 1 || opWeight>10) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("");
					double valueInKilograms = 0;
					puts("Value?");
					double value = getValue();
					if (opWeight == 1) {
						valueInKilograms = value;
					}
					if (opWeight == 2) {
						valueInKilograms = value * 0.001;
					}
					if (opWeight == 3) {
						valueInKilograms = value * 0.000001;
					}
					if (opWeight == 4) {
						valueInKilograms = value * 1000;
					}
					if (opWeight == 5) {
						valueInKilograms = value * 1016.04608;
					}
					if (opWeight == 6) {
						valueInKilograms = value * 907.184;
					}
					if (opWeight == 7) {
						valueInKilograms = value * 0.453592;
					}
					if (opWeight == 8) {
						valueInKilograms = value * 0.0283495;
					}
					if (opWeight == 9) {
						valueInKilograms = value * 0.0002;
					}
					if (opWeight == 10) {
						valueInKilograms = value * 1.660540199E-27;
					}
					printf("\nKilogram: %G", valueInKilograms);
					printf("\nGram: %G", valueInKilograms * 1000);
					printf("\nMilligram: %G", valueInKilograms * 1000000);
					printf("\nMetric Ton: %G", valueInKilograms * 0.001);
					printf("\nLong Ton: %G", valueInKilograms*0.0009842073);
					printf("\nShort Ton: %G", valueInKilograms*0.0011023122);
					printf("\nPound: %G", valueInKilograms*2.2046244202);
					printf("\nOunce: %G", valueInKilograms*35.273990723);
					printf("\nFoot: %G", valueInKilograms*3.280839895);
					printf("\nCarrat: %G", valueInKilograms * 5000);
					printf("\nAtomic Mass Unit: %G", valueInKilograms * 6.022136652E+26);
				}
				fflush(NULL);
				printf("\n\nContinue with Weight conversions? (Yes -> 1 / No -> 0)\n");
				opWeight1 = (int)getValue();
			} while (opWeight1 != 0);
		}
		if (op == 6) {
			int opTime, opTime1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Second -> 1");
				puts("Millisecond -> 2");
				puts("Microsecond -> 3");
				puts("Nanosecond -> 4");
				puts("Picosecond -> 5");
				puts("Minute -> 6");
				puts("Hour -> 7");
				puts("Day -> 8");
				puts("Week -> 9");
				puts("Month -> 10");
				puts("Year -> 11");
				opTime = (int)getValue();
				if (opTime < 1 || opTime>11) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("");
					double valueInSeconds = 0;
					puts("Value?");
					double value = getValue();
					if (opTime == 1) {
						valueInSeconds = value;
					}
					if (opTime == 2) {
						valueInSeconds = value * 0.001;
					}
					if (opTime == 3) {
						valueInSeconds = value * 0.000001;
					}
					if (opTime == 4) {
						valueInSeconds = value * 1E-9;
					}
					if (opTime == 5) {
						valueInSeconds = value * 1E-12;
					}
					if (opTime == 6) {
						valueInSeconds = value * 60;
					}
					if (opTime == 7) {
						valueInSeconds = value * 3600;
					}
					if (opTime == 8) {
						valueInSeconds = value * 86400;
					}
					if (opTime == 9) {
						valueInSeconds = value * 604800;
					}
					if (opTime == 10) {
						valueInSeconds = value * 2629800;
					}
					if (opTime == 11) {
						valueInSeconds = value * 31557600;
					}
					printf("\nSecond: %G", valueInSeconds);
					printf("\nMillisecond: %G", valueInSeconds * 1000);
					printf("\nMicrosecond: %G", valueInSeconds * 1000000);
					printf("\nNanosecond: %G", valueInSeconds * 1000000000);
					printf("\nPicosecond: %G", valueInSeconds * 1000000000000);
					printf("\nMinute: %G", valueInSeconds*0.0166666667);
					printf("\nHour: %G", valueInSeconds*0.0002777778);
					printf("\nDay: %G", valueInSeconds*0.0000115741);
					printf("\nWeek: %G", valueInSeconds*0.0000016534);
					printf("\nMonth: %G", valueInSeconds*3.802570537E-7);
					printf("\nYear: %G", valueInSeconds * 3.168808781E-8);
				}
				fflush(NULL);
				printf("\n\nContinue with Time conversions? (Yes -> 1 / No -> 0)\n");
				opTime1 = (int)getValue();
			} while (opTime1 != 0);
		}
		if (op == 7) {
			int opAngle, opAngle1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Degree -> 1");
				puts("Radian -> 2");
				puts("Gradian -> 3");
				puts("Revolution -> 4");
				puts("Minutes -> 5");
				puts("Seconds -> 6");
				puts("Octant -> 7");
				puts("Sextant -> 8");
				puts("Quadrant -> 9");
				puts("Milliradian -> 10");
				opAngle = (int)getValue();
				if (opAngle < 1 || opAngle>10) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("");
					double valueInDegree = 0;
					puts("Value?");
					double value = getValue();
					if (opAngle == 1) {
						valueInDegree = value;
					}
					if (opAngle == 2) {
						valueInDegree = value * 180 / M_PI;
					}
					if (opAngle == 3) {
						valueInDegree = value * 0.9;
					}
					if (opAngle == 4) {
						valueInDegree = value * 360;
					}
					if (opAngle == 5) {
						valueInDegree = value / 60;
					}
					if (opAngle == 6) {
						valueInDegree = value / 3600;
					}
					if (opAngle == 7) {
						valueInDegree = value * 45;
					}
					if (opAngle == 8) {
						valueInDegree = value * 60;
					}
					if (opAngle == 9) {
						valueInDegree = value * 90;
					}
					if (opAngle == 10) {
						valueInDegree = value * 360 / 6400;
					}
					printf("\nDegree: %G", valueInDegree);
					printf("\nRadian: %G", valueInDegree*M_PI / 180);
					printf("\nGradian: %G", valueInDegree / 0.9);
					printf("\nRevolution: %G", valueInDegree / 360);
					printf("\nMinutes: %G", valueInDegree * 60);
					printf("\nSeconds: %G", valueInDegree * 3600);
					printf("\nOctant: %G", valueInDegree / 45);
					printf("\nSextant: %G", valueInDegree / 60);
					printf("\nQuadrant: %G", valueInDegree / 90);
					printf("\nMilliradian: %G", valueInDegree * 6400 / 360);
				}
				fflush(NULL);
				printf("\n\nContinue with Angle Conversions? (Yes -> 1 / No -> 0)\n");
				opAngle1 = (int)getValue();
			} while (opAngle1 != 0);
		}
		if (op < 1 || op>7) {
			puts("\n\nError: Incorrect option id.\n\n");
		}
		fflush(NULL);
		op1 = -1;
		while (op1 != 0 && op1 != 1) {
			printf("\nContinue? (Yes -> 1 / No -> 0)\n");
			op1 = (int)getValue();
		}
	} while (op1 != 0);
}