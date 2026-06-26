#include "stdafx.h"
template <typename T>

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
		op = (int)getValue<T>();
		puts("");

		// ==========================================
		// CATEGORY 1: LENGTH (Base Unit: Meter)
		// ==========================================
		if (op == 1) {
			int opLength, opLength1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Meter -> 1\nKilometer -> 2\nCentimeter -> 3\nMillimeter -> 4");
				puts("Micrometer -> 5\nNanometer -> 6\nMile -> 7\nYard -> 8");
				puts("Foot -> 9\nInch -> 10\nLight Year -> 11");
				opLength = (int)getValue<T>();

				if (opLength < 1 || opLength > 11) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("\nValue?");
					T value = getValue<T>();
					T valueInMeters = 0;

					switch (opLength) {
					case 1:  valueInMeters = value; break;
					case 2:  valueInMeters = value * 1000.0; break;
					case 3:  valueInMeters = value * 0.01; break;
					case 4:  valueInMeters = value * 0.001; break;
					case 5:  valueInMeters = value * 1E-6; break;
					case 6:  valueInMeters = value * 1E-9; break;
					case 7:  valueInMeters = value * 1609.344; break; // Exact International Mile
					case 8:  valueInMeters = value * 0.9144; break;   // Exact International Yard
					case 9:  valueInMeters = value * 0.3048; break;   // Exact International Foot
					case 10: valueInMeters = value * 0.0254; break;   // Exact International Inch
					case 11: valueInMeters = value * 9460730472580800.0; break; // Astronomical Julian Light Year
					}

					printf("\nMeter: %s", convert2Exponential(valueInMeters));
					printf("\nKilometer: %s", convert2Exponential(valueInMeters * 0.001));
					printf("\nCentimeter: %s", convert2Exponential(valueInMeters * 100.0));
					printf("\nMillimeter: %s", convert2Exponential(valueInMeters * 1000.0));
					printf("\nMicrometer: %s", convert2Exponential(valueInMeters * 1E6));
					printf("\nNanometer: %s", convert2Exponential(valueInMeters * 1E9));
					printf("\nMile: %s", convert2Exponential(valueInMeters / 1609.344));
					printf("\nYard: %s", convert2Exponential(valueInMeters / 0.9144));
					printf("\nFoot: %s", convert2Exponential(valueInMeters / 0.3048));
					printf("\nInch: %s", convert2Exponential(valueInMeters / 0.0254));
					printf("\nLight Year: %s", convert2Exponential(valueInMeters / 9460730472580800.0));
				}
				fflush(NULL);
				opLength1 = -1;
				while (opLength1 != 0 && opLength1 != 1) {
					I_O = true;
					printf("\n\nContinue with Length conversions? (Yes -> 1 / No -> 0)\n");
					opLength1 = (int)getValue<T>();
				}
			} while (opLength1 != 0);
		}

		// ==========================================
		// CATEGORY 2: TEMPERATURE (Base Unit: Kelvin)
		// ==========================================
		else if (op == 2) {
			int opTemp, opTemp1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Celsius -> 1\nFahrenheit -> 2\nKelvin -> 3");
				opTemp = (int)getValue<T>();

				if (opTemp < 1 || opTemp > 3) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("\nValue?");
					T value = getValue<T>();
					T valueInKelvin = 0;

					switch (opTemp) {
					case 1: valueInKelvin = value + 273.15; break;
					case 2: valueInKelvin = (value - 32.0) * 5.0 / 9.0 + 273.15; break;
					case 3: valueInKelvin = value; break;
					}

					printf("\nCelsius: %s", convert2Exponential(valueInKelvin - 273.15));
					printf("\nFahrenheit: %s", convert2Exponential((valueInKelvin - 273.15) * 9.0 / 5.0 + 32.0));
					printf("\nKelvin: %s", convert2Exponential(valueInKelvin));
				}
				fflush(NULL);
				opTemp1 = -1;
				while (opTemp1 != 0 && opTemp1 != 1) {
					I_O = true;
					printf("\n\nContinue with Temperature conversions? (Yes -> 1 / No -> 0)\n");
					opTemp1 = (int)getValue<T>();
				}
			} while (opTemp1 != 0);
		}

		// ==========================================
		// CATEGORY 3: AREA (Base Unit: Square Meter)
		// ==========================================
		else if (op == 3) {
			int opArea, opArea1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Square Meter -> 1\nSquare Kilometer -> 2\nSquare Centimeter -> 3\nSquare Millimeter -> 4");
				puts("Hectare -> 5\nAcre -> 6\nSquare Mile -> 7\nSquare Yard -> 8\nSquare Foot -> 9\nSquare Inch -> 10");
				opArea = (int)getValue<T>();

				if (opArea < 1 || opArea > 10) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("\nValue?");
					T value = getValue<T>();
					T valueInSqMeters = 0;

					switch (opArea) {
					case 1:  valueInSqMeters = value; break;
					case 2:  valueInSqMeters = value * 1E6; break;
					case 3:  valueInSqMeters = value * 1E-4; break;
					case 4:  valueInSqMeters = value * 1E-6; break;
					case 5:  valueInSqMeters = value * 10000.0; break;
					case 6:  valueInSqMeters = value * 4046.8564224; break;      // Exact International Acre
					case 7:  valueInSqMeters = value * 2589988.110336; break;   // Exact Square Mile (1609.344^2)
					case 8:  valueInSqMeters = value * 0.83612736; break;       // Exact Square Yard (0.9144^2)
					case 9:  valueInSqMeters = value * 0.09290304; break;       // Exact Square Foot (0.3048^2)
					case 10: valueInSqMeters = value * 0.00064516; break;       // Exact Square Inch (0.0254^2)
					}

					printf("\nSquare Meter: %s", convert2Exponential(valueInSqMeters));
					printf("\nSquare Kilometer: %s", convert2Exponential(valueInSqMeters * 1E-6));
					printf("\nSquare Centimeter: %s", convert2Exponential(valueInSqMeters * 1E4));
					printf("\nSquare Millimeter: %s", convert2Exponential(valueInSqMeters * 1E6));
					printf("\nHectare: %s", convert2Exponential(valueInSqMeters * 1E-4));
					printf("\nAcre: %s", convert2Exponential(valueInSqMeters / 4046.8564224));
					printf("\nSquare Mile: %s", convert2Exponential(valueInSqMeters / 2589988.110336));
					printf("\nSquare Yard: %s", convert2Exponential(valueInSqMeters / 0.83612736));
					printf("\nSquare Foot: %s", convert2Exponential(valueInSqMeters / 0.09290304));
					printf("\nSquare Inch: %s", convert2Exponential(valueInSqMeters / 0.00064516));
				}
				fflush(NULL);
				opArea1 = -1;
				while (opArea1 != 0 && opArea1 != 1) {
					I_O = true;
					printf("\n\nContinue with Area conversions? (Yes -> 1 / No -> 0)\n");
					opArea1 = (int)getValue<T>();
				}
			} while (opArea1 != 0);
		}

		// ==========================================
		// CATEGORY 4: VOLUME (Base Unit: Cubic Meter)
		// ==========================================
		else if (op == 4) {
			int opVol, opVol1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Cubic Meter -> 1\nCubic Kilometer -> 2\nCubic Centimeter -> 3\nCubic Millimeter -> 4");
				puts("Liter -> 5\nMilliliter -> 6\nUS Gallon -> 7\nImperial Gallon -> 8");
				puts("Cubic Mile -> 9\nCubic Foot -> 10\nCubic Inch -> 11");
				opVol = (int)getValue<T>();

				if (opVol < 1 || opVol > 11) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("\nValue?");
					T value = getValue<T>();
					T valueInCubicMeters = 0;

					switch (opVol) {
					case 1:  valueInCubicMeters = value; break;
					case 2:  valueInCubicMeters = value * 1E9; break;
					case 3:  valueInCubicMeters = value * 1E-6; break;
					case 4:  valueInCubicMeters = value * 1E-9; break;
					case 5:  valueInCubicMeters = value * 0.001; break;
					case 6:  valueInCubicMeters = value * 1E-6; break;
					case 7:  valueInCubicMeters = value * 0.003785411784; break; // US Fluid Gallon (exactly 231 cu in)
					case 8:  valueInCubicMeters = value * 0.00454609; break;     // Imperial Gallon (exact legal definition)
					case 9:  valueInCubicMeters = value * 4168181825.440579584; break; // Cubic Mile (1609.344^3)
					case 10: valueInCubicMeters = value * 0.028316846592; break; // Cubic Foot (0.3048^3)
					case 11: valueInCubicMeters = value * 1.6387064E-5; break;   // Cubic Inch (0.0254^3)
					}

					printf("\nMeters Cubed: %s", convert2Exponential(valueInCubicMeters));
					printf("\nKilometers Cubed: %s", convert2Exponential(valueInCubicMeters * 1E-9));
					printf("\nCentimeters Cubed: %s", convert2Exponential(valueInCubicMeters * 1E6));
					printf("\nMillimeters Cubed: %s", convert2Exponential(valueInCubicMeters * 1E9));
					printf("\nLiter: %s", convert2Exponential(valueInCubicMeters * 1000.0));
					printf("\nMilliliter: %s", convert2Exponential(valueInCubicMeters * 1E6));
					printf("\nUS Gallon: %s", convert2Exponential(valueInCubicMeters / 0.003785411784));
					printf("\nImperial Gallon: %s", convert2Exponential(valueInCubicMeters / 0.00454609));
					printf("\nCubic Mile: %s", convert2Exponential(valueInCubicMeters / 4168181825.440579584));
					printf("\nCubic Foot: %s", convert2Exponential(valueInCubicMeters / 0.028316846592));
					printf("\nCubic Inch: %s", convert2Exponential(valueInCubicMeters / 1.6387064E-5));
				}
				fflush(NULL);
				opVol1 = -1;
				while (opVol1 != 0 && opVol1 != 1) {
					I_O = true;
					printf("\n\nContinue with Volume conversions? (Yes -> 1 / No -> 0)\n");
					opVol1 = (int)getValue<T>();
				}
			} while (opVol1 != 0);
		}

		// ==========================================
		// CATEGORY 5: WEIGHT/MASS (Base Unit: Kilogram)
		// ==========================================
		else if (op == 5) {
			int opWeight, opWeight1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Kilogram -> 1\nGram -> 2\nMilligram -> 3\nMetric Ton -> 4");
				puts("Pound (lb) -> 5\nOunce (oz) -> 6\nStone -> 7\nShort Ton (US) -> 8");
				opWeight = (int)getValue<T>();

				if (opWeight < 1 || opWeight > 8) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("\nValue?");
					T value = getValue<T>();
					T valueInKg = 0;

					switch (opWeight) {
					case 1: valueInKg = value; break;
					case 2: valueInKg = value * 0.001; break;
					case 3: valueInKg = value * 1E-6; break;
					case 4: valueInKg = value * 1000.0; break;
					case 5: valueInKg = value * 0.45359237; break;     // Exact International Avoirdupois Pound
					case 6: valueInKg = value * 0.028349523125; break; // Exact Avoirdupois Ounce (Pound / 16)
					case 7: valueInKg = value * 6.35029318; break;     // Exact Stone (Pound * 14)
					case 8: valueInKg = value * 907.18474; break;      // Exact US Short Ton (Pound * 2000)
					}

					printf("\nKilogram: %s", convert2Exponential(valueInKg));
					printf("\nGram: %s", convert2Exponential(valueInKg * 1000.0));
					printf("\nMilligram: %s", convert2Exponential(valueInKg * 1E6));
					printf("\nMetric Ton: %s", convert2Exponential(valueInKg * 0.001));
					printf("\nPound (lb): %s", convert2Exponential(valueInKg / 0.45359237));
					printf("\nOunce (oz): %s", convert2Exponential(valueInKg / 0.028349523125));
					printf("\nStone: %s", convert2Exponential(valueInKg / 6.35029318));
					printf("\nShort Ton (US): %s", convert2Exponential(valueInKg / 907.18474));
				}
				fflush(NULL);
				opWeight1 = -1;
				while (opWeight1 != 0 && opWeight1 != 1) {
					I_O = true;
					printf("\n\nContinue with Weight conversions? (Yes -> 1 / No -> 0)\n");
					opWeight1 = (int)getValue<T>();
				}
			} while (opWeight1 != 0);
		}

		// ==========================================
		// CATEGORY 6: TIME (Base Unit: Second)
		// ==========================================
		else if (op == 6) {
			int opTime, opTime1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Second -> 1\nMillisecond -> 2\nMicrosecond -> 3\nNanosecond -> 4");
				puts("Minute -> 5\nHour -> 6\nDay -> 7\nWeek -> 8\nMonth -> 9\nYear -> 10");
				opTime = (int)getValue<T>();

				if (opTime < 1 || opTime > 10) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("\nValue?");
					T value = getValue<T>();
					T valueInSeconds = 0;

					switch (opTime) {
					case 1:  valueInSeconds = value; break;
					case 2:  valueInSeconds = value * 0.001; break;
					case 3:  valueInSeconds = value * 1E-6; break;
					case 4:  valueInSeconds = value * 1E-9; break;
					case 5:  valueInSeconds = value * 60.0; break;
					case 6:  valueInSeconds = value * 3600.0; break;
					case 7:  valueInSeconds = value * 86400.0; break;
					case 8:  valueInSeconds = value * 604800.0; break;
					case 9:  valueInSeconds = value * 2629800.0; break; // Average Gregorian Month (365.2425 days / 12)
					case 10: valueInSeconds = value * 31556952.0; break; // Average Gregorian Year (365.2425 days)
					}

					printf("\nSecond: %s", convert2Exponential(valueInSeconds));
					printf("\nMillisecond: %s", convert2Exponential(valueInSeconds * 1000.0));
					printf("\nMicrosecond: %s", convert2Exponential(valueInSeconds * 1E6));
					printf("\nNanosecond: %s", convert2Exponential(valueInSeconds * 1E9));
					printf("\nMinute: %s", convert2Exponential(valueInSeconds / 60.0));
					printf("\nHour: %s", convert2Exponential(valueInSeconds / 3600.0));
					printf("\nDay: %s", convert2Exponential(valueInSeconds / 86400.0));
					printf("\nWeek: %s", convert2Exponential(valueInSeconds / 604800.0));
					printf("\nMonth: %s", convert2Exponential(valueInSeconds / 2629800.0));
					printf("\nYear: %s", convert2Exponential(valueInSeconds / 31556952.0));
				}
				fflush(NULL);
				opTime1 = -1;
				while (opTime1 != 0 && opTime1 != 1) {
					I_O = true;
					printf("\n\nContinue with Time conversions? (Yes -> 1 / No -> 0)\n");
					opTime1 = (int)getValue<T>();
				}
			} while (opTime1 != 0);
		}

		// ==========================================
		// CATEGORY 7: ANGLE (Base Unit: Degree)
		// ==========================================
		else if (op == 7) {
			int opAngle, opAngle1 = 1;
			do {
				fflush(NULL);
				puts("\nYour unit?\n");
				puts("Degree -> 1\nRadian -> 2\nGradian -> 3\nRevolution -> 4\nMinutes -> 5");
				puts("Seconds -> 6\nOctant -> 7\nSextant -> 8\nQuadrant -> 9\nNATO Mil -> 10");
				opAngle = (int)getValue<T>();

				if (opAngle < 1 || opAngle > 10) {
					puts("\n\nError: Incorrect option id.\n\n");
				}
				else {
					puts("\nValue?");
					T value = getValue<T>();
					T valueInDegree = 0;

					switch (opAngle) {
					case 1:  valueInDegree = value; break;
					case 2:  valueInDegree = value * 180.0 / M_PI; break;
					case 3:  valueInDegree = value * 0.9; break;
					case 4:  valueInDegree = value * 360.0; break;
					case 5:  valueInDegree = value / 60.0; break;
					case 6:  valueInDegree = value / 3600.0; break;
					case 7:  valueInDegree = value * 45.0; break;
					case 8:  valueInDegree = value * 60.0; break;
					case 9:  valueInDegree = value * 90.0; break;
					case 10: valueInDegree = value * 360.0 / 6400.0; break;
					}

					printf("\nDegree: %s", convert2Exponential(valueInDegree));
					printf("\nRadian: %s", convert2Exponential(valueInDegree * M_PI / 180.0));
					printf("\nGradian: %s", convert2Exponential(valueInDegree / 0.9));
					printf("\nRevolution: %s", convert2Exponential(valueInDegree / 360.0));
					printf("\nMinutes: %s", convert2Exponential(valueInDegree * 60.0));
					printf("\nSeconds: %s", convert2Exponential(valueInDegree * 3600.0));
					printf("\nOctant: %s", convert2Exponential(valueInDegree / 45.0));
					printf("\nSextant: %s", convert2Exponential(valueInDegree / 60.0));
					printf("\nQuadrant: %s", convert2Exponential(valueInDegree / 90.0));
					printf("\nNATO Mil: %s", convert2Exponential(valueInDegree * 6400.0 / 360.0));
				}
				fflush(NULL);
				opAngle1 = -1;
				while (opAngle1 != 0 && opAngle1 != 1) {
					I_O = true;
					printf("\n\nContinue with Angle Conversions? (Yes -> 1 / No -> 0)\n");
					opAngle1 = (int)getValue<T>();
				}
			} while (opAngle1 != 0);
		}

		// Check for global main menu escape bounds
		if (op < 1 || op > 7) {
			puts("\n\nError: Incorrect option id.\n\n");
		}

		fflush(NULL);
		op1 = -1;
		while (op1 != 0 && op1 != 1) {
			I_O = true;
			printf("\nContinue? (Yes -> 1 / No -> 0)\n");
			op1 = (int)getValue<T>();
		}
	} while (op1 != 0);
}

template void unitConversions<double>();
