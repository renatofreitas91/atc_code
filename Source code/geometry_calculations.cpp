#include "stdafx.h"

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
		op = (int)getPosValue();
		puts("");
		if (op == 1) {
			puts("Side?");
			double side = getPosValue();
			double area = side * side;
			double perimeter = 4 * side;
			printf("\nArea: %G\nPerimeter: %G\n", area, perimeter);
		}
		if (op == 2) {
			puts("Length?");
			double length = getPosValue();
			puts("Width?");
			double width = getPosValue();
			double area = length * width;
			double perimeter = 2 * length + 2 * width;
			printf("\nArea: %G\nPerimeter: %G\n", area, perimeter);
		}
		if (op == 3) {
			puts("Length?");
			double length = getPosValue();
			puts("Width?");
			double width = getPosValue();
			puts("Height?");
			double height = getPosValue();
			if ((length + width) > height || (length + height) > width || (width + height) > length) {
				double area = length * height;
				double perimeter = 2 * length + 2 * width;
				printf("\nArea: %G\nPerimeter: %G\n", area, perimeter);
			}
			else {
				puts("\n\nError: Invalid dimensions\n\n");
			}
		}
		if (op == 4) {
			puts("Height?");
			double height = getPosValue();
			puts("Base 1");
			double base_1 = getPosValue();
			puts("Base 2");
			double base_2 = getPosValue();
			puts("Side 1");
			double side_1 = getPosValue();
			puts("Side 2");
			double side_2 = getPosValue();
			if ((height+base_1+base_2+side_1)> side_2|| (height + base_1 + base_2 + side_2) > side_1 || (side_1 + base_1 + base_2 + side_2) > height|| (side_1 + height + base_2 + side_2) > base_1|| (side_1 + base_1 + height + side_2) >base_2){
				double area = 0.5*height*(base_1 + base_2);
				double perimeter = side_1 + side_2 + base_1 + base_2;
			}
			else {
				puts("\n\nError: Invalid dimensions\n\n");
			}
		}
		if (op == 5) {
			puts("Base?");
			double base = getPosValue();
			puts("Height?");
			double height = getPosValue();
			puts("Side 1?");
			double side_1 = getPosValue();
			puts("Side 2?");
			double side_2 = getPosValue();
			if ((height+side_1+side_2)> base || (base + side_1 + side_2) > height || (base + height + side_2) > side_1 || (base + height + side_1) > side_2) {
				double area = 0.5*base*height;
				double perimeter = side_1 + side_2 + base;
				printf("\nArea: %G\nPerimeter: %G\n", area, perimeter);
			}
			else {
				puts("\n\nError: Invalid dimensions\n\n");
			}
		}
		if (op == 6) {
			puts("Radius?");
			double radius = getPosValue();
			double area = M_PI * pow(radius, 2.0);
			double perimeter = 2 * M_PI*radius;
			printf("\nArea: %G\nCircumference (Perimeter of a circle): %G\n", area, perimeter);
		}
		if (op == 7) {
			puts("Length?");
			double length = getPosValue();
			puts("Width?");
			double width = getPosValue();
			puts("Height?");
			double height = getPosValue();
			double volume = length * width*height;
			double surface_area = 2 * length*height + 2 * width*height + 2 * width*length;
			printf("\nVolume: %G\nSurface Area: %G\n", volume, surface_area);
		}
		if (op == 8) {
			puts("Side?");
			double side = getPosValue();
			double volume = pow(side, 3.0);
			double surface_area = 6 * pow(side, 2.0);
			printf("\nVolume: %G\nSurface Area: %G\n", volume, surface_area);
		}
		if (op == 9) {
			puts("Radius?");
			double radius = getPosValue();
			puts("Height?");
			double height = getPosValue();
			double volume = M_PI * pow(radius, 2.0)*height;
			double surface_area = 2 * M_PI*radius*height + 2 * M_PI*pow(radius, 2.0);
			printf("\nVolume: %G\nSurface Area: %G\n", volume, surface_area);
		}
		if (op == 10) {
			puts("Radius?");
			double radius = getPosValue();
			double volume = (4.0 / 3.0)*M_PI*pow(radius, 3.0);
			double surface_area = 4.0*M_PI*pow(radius, 2.0);
			printf("\nVolume: %G\nSurface Area: %G\n", volume, surface_area);
		}
		if (op == 11) {
			puts("Radius?");
			double radius = getPosValue();
			puts("Height?");
			double height = getPosValue();
			double volume = (1.0 / 3.0)*M_PI*pow(radius, 2.0)*height;
			double surface_area = M_PI * radius*sqrt(pow(radius, 2.0) + pow(height, 2.0));
			printf("\nVolume: %G\nSurface Area: %G\n", volume, surface_area);
		}
		if (op == 12) {
			puts("Length?");
			double length = getPosValue();
			puts("Width?");
			double width = getPosValue();
			puts("Height?");
			double height = getPosValue();
			double volume = (1.0 / 3.0)*length*width*height;
			double surface_area = (((2 * width + 2 * length)*height) / 2)+(length*width);
			printf("\nVolume: %G\nSurface Area: %G\n", volume, surface_area);
		}
		if (op == 13) {
			puts("Radius of the upper base?");
			double radius_upper_base = getPosValue();
			puts("Radius of the lower base?");
			double radius_lower_base = getPosValue();
			puts("Height?");
			double height = getPosValue();
			puts("Side?");
			double side = getPosValue();
			double volume = (M_PI*(pow(radius_upper_base, 2.0) + radius_upper_base * radius_lower_base + pow(radius_lower_base, 2.0))*height) / 3.0;
			double surface_area = M_PI * side*(radius_lower_base + radius_upper_base);
			printf("\nVolume: %G\nSurface Area: %G\n", volume, surface_area);
		}
		if (op < 1 || op>13) {
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

double getPosValue() {
	double value = -1;
	while (value < 0) {
		value = getValue();
		if (value <= 0) {
			puts("\n\nError: Value must be positive.\n\n");
		}
	}
	return value;
}