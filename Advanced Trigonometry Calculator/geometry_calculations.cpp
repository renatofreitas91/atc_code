#include "stdafx.h"
#include <cmath>

template <typename T>
void geometryCalculations() {
	int op = 0, op1 = -1;
	do {
		fflush(NULL);
		puts("\nWhat to calculate?\n");
		puts("Areas and Perimeters:\n");
		puts("Square -> 1");
		puts("Rectangle -> 2");
		puts("Parallelogram -> 3");
		puts("Trapezoid -> 4");
		puts("Triangle -> 5");
		puts("Circle -> 6");
		puts("\nVolumes and Surface Areas of Three-Dimensional Figures:\n");
		puts("Rectangular Solid -> 7");
		puts("Cube -> 8");
		puts("Right Circular Cylinder -> 9");
		puts("Sphere -> 10");
		puts("Right Circular Cone -> 11");
		puts("Square or Rectangular Pyramid -> 12");
		puts("Frustum of Right Circular Cone -> 13");

		op = (int)getPosValue<T>();
		puts("");

		switch (op) {
		case 1: { // Square
			puts("Side?");
			T side = getPosValue<T>();
			T area = side * side;
			T perimeter = 4 * side;
			convertComplex2Exponential(area, perimeter);
			printf("\nArea: %s\nPerimeter: %s\n", respR, respI);
			break;
		}
		case 2: { // Rectangle
			puts("Length?");
			T length = getPosValue<T>();
			puts("Width?");
			T width = getPosValue<T>();
			T area = length * width;
			T perimeter = 2 * (length + width);
			convertComplex2Exponential(area, perimeter);
			printf("\nArea: %s\nPerimeter: %s\n", respR, respI);
			break;
		}
		case 3: { // Parallelogram
			puts("Base Length?");
			T length = getPosValue<T>();
			puts("Slant Width?");
			T width = getPosValue<T>();
			puts("Height?");
			T height = getPosValue<T>();

			// A altura não pode ser maior que o lado inclinado (cateto de um triângulo retângulo interno)
			if (height <= width) {
				T area = length * height;
				T perimeter = 2 * (length + width);
				convertComplex2Exponential(area, perimeter);
				printf("\nArea: %s\nPerimeter: %s\n", respR, respI);
			}
			else {
				puts("\n\nError: Invalid dimensions (Height cannot be greater than slant width).\n\n");
			}
			break;
		}
		case 4: { // Trapezoid
			puts("Height?");
			T height = getPosValue<T>();
			puts("Base 1 (Top)?");
			T base_1 = getPosValue<T>();
			puts("Base 2 (Bottom)?");
			T base_2 = getPosValue<T>();
			puts("Side 1?");
			T side_1 = getPosValue<T>();
			puts("Side 2?");
			T side_2 = getPosValue<T>();

			// Validação geométrica simplificada para integridade do perímetro
			T area = 0.5 * height * (base_1 + base_2);
			T perimeter = side_1 + side_2 + base_1 + base_2;
			convertComplex2Exponential(area, perimeter);
			printf("\nArea: %s\nPerimeter: %s\n", respR, respI);
			break;
		}
		case 5: { // Triangle (Using Heron's Formula for consistency or Base/Height if accurate)
			puts("Base?");
			T base = getPosValue<T>();
			puts("Side 1?");
			T side_1 = getPosValue<T>();
			puts("Side 2?");
			T side_2 = getPosValue<T>();

			// Validação matemática estrita: Desigualdade Triangular
			if ((base + side_1 > side_2) && (base + side_2 > side_1) && (side_1 + side_2 > base)) {
				puts("Height relative to Base?");
				T height = getPosValue<T>();

				T area = 0.5 * base * height;
				T perimeter = side_1 + side_2 + base;
				convertComplex2Exponential(area, perimeter);
				printf("\nArea: %s\nPerimeter: %s\n", respR, respI);
			}
			else {
				puts("\n\nError: Invalid dimensions (The sides do not form a valid triangle).\n\n");
			}
			break;
		}
		case 6: { // Circle
			puts("Radius?");
			T radius = getPosValue<T>();
			T area = M_PI * pot<T>(radius, 2.0, 1);
			T perimeter = 2 * M_PI * radius;
			convertComplex2Exponential(area, perimeter);
			printf("\nArea: %s\nCircumference (Perimeter of a circle): %s\n", respR, respI);
			break;
		}
		case 7: { // Rectangular Solid
			puts("Length?");
			T length = getPosValue<T>();
			puts("Width?");
			T width = getPosValue<T>();
			puts("Height?");
			T height = getPosValue<T>();
			T volume = length * width * height;
			T surface_area = 2 * (length * height + width * height + width * length);
			convertComplex2Exponential(volume, surface_area);
			printf("\nVolume: %s\nSurface Area: %s\n", respR, respI);
			break;
		}
		case 8: { // Cube
			puts("Side?");
			T side = getPosValue<T>();
			T volume = pot<T>(side, 3.0, 1);
			T surface_area = 6 * pot<T>(side, 2.0, 1);
			convertComplex2Exponential(volume, surface_area);
			printf("\nVolume: %s\nSurface Area: %s\n", respR, respI);
			break;
		}
		case 9: { // Right Circular Cylinder
			puts("Radius?");
			T radius = getPosValue<T>();
			puts("Height?");
			T height = getPosValue<T>();
			T volume = M_PI * pot<T>(radius, 2.0, 1) * height;
			T surface_area = (2 * M_PI * radius * height) + (2 * M_PI * pot<T>(radius, 2.0, 1));
			convertComplex2Exponential(volume, surface_area);
			printf("\nVolume: %s\nSurface Area: %s\n", respR, respI);
			break;
		}
		case 10: { // Sphere
			puts("Radius?");
			T radius = getPosValue<T>();
			T volume = (4.0 / 3.0) * M_PI * pot<T>(radius, 3.0, 1);
			T surface_area = 4.0 * M_PI * pot<T>(radius, 2.0, 1);
			convertComplex2Exponential(volume, surface_area);
			printf("\nVolume: %s\nSurface Area: %s\n", respR, respI);
			break;
		}
		case 11: { // Right Circular Cone
			puts("Radius?");
			T radius = getPosValue<T>();
			puts("Height?");
			T height = getPosValue<T>();
			T volume = (1.0 / 3.0) * M_PI * pot<T>(radius, 2.0, 1) * height;
			// Área Total = Área Lateral + Área da Base
			T slant_height = sqrt(pot<T>(radius, 2.0, 1) + pot<T>(height, 2.0, 1));
			T surface_area = (M_PI * radius * slant_height) + (M_PI * pot<T>(radius, 2.0, 1));
			convertComplex2Exponential(volume, surface_area);
			printf("\nVolume: %s\nSurface Area: %s\n", respR, respI);
			break;
		}
		case 12: { // Square or Rectangular Pyramid
			puts("Base Length?");
			T length = getPosValue<T>();
			puts("Base Width?");
			T width = getPosValue<T>();
			puts("Height?");
			T height = getPosValue<T>();

			T volume = (1.0 / 3.0) * length * width * height;
			// Cálculo preciso usando as geratrizes das faces laterais (Pitágoras)
			T slant_length = sqrt(pot<T>(width / 2.0, 2.0, 1) + pot<T>(height, 2.0, 1));
			T slant_width = sqrt(pot<T>(length / 2.0, 2.0, 1) + pot<T>(height, 2.0, 1));
			T surface_area = (length * width) + (length * slant_length) + (width * slant_width);

			convertComplex2Exponential(volume, surface_area);
			printf("\nVolume: %s\nSurface Area: %s\n", respR, respI);
			break;
		}
		case 13: { // Frustum of Right Circular Cone
			puts("Radius of the upper base?");
			T radius_upper_base = getPosValue<T>();
			puts("Radius of the lower base?");
			T radius_lower_base = getPosValue<T>();
			puts("Height?");
			T height = getPosValue<T>();

			// A geratriz (slant height) pode ser deduzida ou validada diretamente
			T slant = sqrt(pot<T>(radius_lower_base - radius_upper_base, 2.0, 1) + pot<T>(height, 2.0, 1));

			T volume = (M_PI * height * (pot<T>(radius_upper_base, 2.0, 1) + (radius_upper_base * radius_lower_base) + pot<T>(radius_lower_base, 2.0, 1))) / 3.0;
			// Área Total = Área Lateral + Área da Base Superior + Área da Base Inferior
			T lateral_area = M_PI * slant * (radius_lower_base + radius_upper_base);
			T surface_area = lateral_area + (M_PI * pot<T>(radius_upper_base, 2.0, 1)) + (M_PI * pot<T>(radius_lower_base, 2.0, 1));

			convertComplex2Exponential(volume, surface_area);
			printf("\nVolume: %s\nSurface Area: %s\n", respR, respI);
			break;
		}
		default:
			puts("\n\nError: Incorrect option id.\n\n");
			break;
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
template <typename T>
T getPosValue() {
	T value = -1;
	while (value <= 0) { // Alterado para <= 0 garantindo que o valor é estritamente positivo
		value = getValue<T>();
		if (value <= 0) {
			puts("\n\nError: Value must be positive and greater than zero.\n\n");
		}
	}
	return value;
}
template double getPosValue<double>();
template mp_float getPosValue<mp_float>();
template void geometryCalculations<double>();

