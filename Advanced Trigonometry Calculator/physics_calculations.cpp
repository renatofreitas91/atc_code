#include "stdafx.h"

bool physics = false;
template<typename T>
void physicsCalculations() {
	physics = true;
	int op = 0, op1 = 1;
	do {
		fflush(NULL);
		puts("\nWhat to calculate?\n");
		puts("Acceleration -> 1\t\t\t\t\tBuoyancy Force -> 2");
		puts("Centripetal Force -> 3\t\t\t\t\tElastic Collision -> 4");
		puts("Density -> 5\t\t\t\t\t\tDisplacement -> 6");
		puts("Free fall distance without air resistance -> 7\t\tFree fall velocity without air resistance -> 8");
		puts("Free fall distance with air resistance -> 9\t\tFree fall velocity with air resistance -> 10");
		puts("Newton's 2nd law -> 11\t\t\t\t\tFriction -> 12");
		puts("Weight/Force Mass Gravity -> 13\t\t\t\tGravitational Force -> 14");
		puts("Impact Force -> 15\t\t\t\t\tKinematics -> 16");
		puts("Lever Force -> 17\t\t\t\t\tTrajectory -> 18");
		puts("Momentum -> 19\t\t\t\t\t\tSimple Pendulum -> 20");
		puts("Projectile Motion -> 21\t\t\t\t\tResultant Vector -> 22");
		puts("Torque -> 23\t\t\t\t\t\tVelocity -> 24");
		puts("Average Velocity -> 25\t\t\t\t\t");
		op = (int)getValue<T>();
		if (op == 1) {
			puts("Enter the unknown value as 'x'");
			puts("Initial Speed (m/s)?");
			char* initial_speed = getDynamicCharArray("", "initial_speed");
			getCharArray<T>();
			sprintf(initial_speed, expressionF);
			puts("Final Speed (m/s)?");
			char* final_speed = getDynamicCharArray("", "final_speed");
			getCharArray<T>();
			sprintf(final_speed, expressionF);
			puts("Time (s)?");
			char* time = getDynamicCharArray("", "time");
			getCharArray<T>();
			sprintf(time, expressionF);
			puts("Acceleration (m/s^2)?");
			char* acceleration = getDynamicCharArray("", "acceleration");
			getCharArray<T>();
			sprintf(acceleration, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s*%s-(%s-%s)", acceleration, time, final_speed, initial_speed);
			T answer = solve<T>(equation);
			if (isEqual("x", acceleration)) {
				printf("\nAcceleration: %s (m/s^2)\n", convert2Exponential(answer));
			}
			if (isEqual("x", time)) {
				printf("\nTime: %s (s)\n", convert2Exponential(answer));
			}
			if (isEqual("x", final_speed)) {
				printf("\nFinal Speed: %s (m/s)\n", convert2Exponential(answer));
			}
			if (isEqual("x", initial_speed)) {
				printf("\nInitial Speed: %s (m/s)\n", convert2Exponential(answer));
			}
			_delete(initial_speed, "initial_speed"); initial_speed = nullptr;
			_delete(final_speed, "final_speed"); final_speed = nullptr;
			_delete(time, "time"); time = nullptr;
			_delete(acceleration, "acceleration"); acceleration = nullptr;
			_delete(equation, "equation"); equation = nullptr;

		}
		if (op == 2) {
			puts("Enter the unknown value as 'x'");
			puts("Density of Fluid (kg/m^3)?");
			char* density_of_fluid = getDynamicCharArray("", "density_of_fluid");
			getCharArray<T>();
			sprintf(density_of_fluid, expressionF);
			puts("Displaced Volume (kg/m^3)?");
			char* displaced_volume = getDynamicCharArray("", "displaced_volume");
			getCharArray<T>();
			sprintf(displaced_volume, expressionF);
			puts("Buoyancy Force (N)?");
			char* buoyancy_force = getDynamicCharArray("", "buoyancy_force");
			getCharArray<T>();
			sprintf(buoyancy_force, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			T gravity = 9.80665;
			sprintf(equation, "%s-%s*%s*%s", buoyancy_force, density_of_fluid, displaced_volume, convert2Exponential(gravity));
			T answer = solve<T>(equation);
			if (isEqual("x", buoyancy_force)) {
				printf("\nBuoyancy Force: %s N\n", convert2Exponential(answer));
			}
			if (isEqual("x", displaced_volume)) {
				printf("\nDisplaced Volume: %s (kg/m^3)\n", convert2Exponential(answer));
			}
			if (isEqual("x", density_of_fluid)) {
				printf("\nDensity of Fluid: %s (kg/m^3)\n", convert2Exponential(answer));
			}
			_delete(density_of_fluid, "density_of_fluid"); density_of_fluid = nullptr;
			_delete(displaced_volume, "displaced_volume"); displaced_volume = nullptr;
			_delete(buoyancy_force, "buoyancy_force"); buoyancy_force = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 3) {
			puts("Mass (kg)?");
			char* mass = getDynamicCharArray("", "mass");
			getCharArray<T>();
			sprintf(mass, expressionF);
			puts("Radius (m)?");
			char* radius = getDynamicCharArray("", "radius");
			getCharArray<T>();
			sprintf(radius, expressionF);
			puts("Velocity (m/s)?");
			char* velocity = getDynamicCharArray("", "velocity");
			getCharArray<T>();
			sprintf(velocity, expressionF);
			puts("Centripetal Force (N)?");
			char* centripetal_force = getDynamicCharArray("", "centripetal_force");
			getCharArray<T>();
			sprintf(centripetal_force, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s*%s-%s*%s^2", centripetal_force, radius, mass, velocity);
			T answer = solve<T>(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %s (kg)\n", convert2Exponential(answer));
			}
			if (isEqual("x", radius)) {
				printf("\nRadius: %s (m)\n", convert2Exponential(answer));
			}
			if (isEqual("x", velocity)) {
				printf("\nFinal Speed: %s (m/s)\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", centripetal_force)) {
				printf("\nCentripetal Force: %s N\n", convert2Exponential(answer));
			}
			_delete(mass, "mass"); mass = nullptr;
			_delete(radius, "radius"); radius = nullptr;
			_delete(velocity, "velocity"); velocity = nullptr;
			_delete(centripetal_force, "centripetal_force"); centripetal_force = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 4) {
			puts("Mass of Moving Object (kg)?");
			T mass = getValue<T>();
			puts("Velocity of Moving Object (m/s)?");
			T velocity = getValue<T>();
			puts("Mass of Stationary Object (kg)?");
			T mass_stationary = getValue<T>();
			T v_1 = ((mass - mass_stationary) / (mass + mass_stationary))*velocity;
			T v_2 = (2 * mass / (mass + mass_stationary))*velocity;
			convertComplex2Exponential(v_1, v_2);
			printf("\nVelocities after collision:\nThe moving object: %s (m/s)\nThe stationary object: %s (m/s)\n", respR, respI);
		}
		if (op == 5) {
			puts("Enter the unknown value as 'x'");
			puts("Density (kg/m^3)?");
			char* density = getDynamicCharArray("", "density");
			getCharArray<T>();
			sprintf(density, expressionF);
			puts("Volume (m^3)?");
			char* volume = getDynamicCharArray("", "volume");
			getCharArray<T>();
			sprintf(volume, expressionF);
			puts("Mass (kg)?");
			char* mass = getDynamicCharArray("", "mass");
			getCharArray<T>();
			sprintf(mass, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s-%s*%s", mass, density, volume);
			T answer = solve<T>(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %s kg\n", convert2Exponential(answer));
			}
			if (isEqual("x", density)) {
				printf("\nDensity: %s (kg/m^3)\n", convert2Exponential(answer));
			}
			if (isEqual("x", volume)) {
				printf("\nVolume: %s (m^3)\n", convert2Exponential(answer));
			}
			_delete(density, "density"); density = nullptr;
			_delete(volume, "volume"); volume = nullptr;
			_delete(mass, "mass"); mass = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 6) {
			puts("Enter the unknown value as 'x'");
			puts("Average Velocity (m/s)?");
			char* avg_velocity = getDynamicCharArray("", "avg_velocity");
			getCharArray<T>();
			sprintf(avg_velocity, expressionF);
			puts("Time (s)?");
			char* time = getDynamicCharArray("", "time");
			getCharArray<T>();
			sprintf(time, expressionF);
			puts("Displacement (m)?");
			char* displacement = getDynamicCharArray("", "displacement");
			getCharArray<T>();
			sprintf(displacement, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s-%s*%s", displacement, avg_velocity, time);
			T answer = solve<T>(equation);
			if (isEqual("x", displacement)) {
				printf("\nDisplacement: %s m\n", convert2Exponential(answer));
			}
			if (isEqual("x", time)) {
				printf("\nTime: %s s\n", convert2Exponential(answer));
			}
			if (isEqual("x", avg_velocity)) {
				printf("\nAverage Velocity: %s (m/s)\n", convert2Exponential(answer));
			}
			_delete(avg_velocity, "avg_velocity"); avg_velocity = nullptr;
			_delete(time, "time"); time = nullptr;
			_delete(displacement, "displacement"); displacement = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 7) {
			puts("Enter the unknown value as 'x'");
			puts("Gravity (m/s^2)?");
			char* gravity = getDynamicCharArray("", "gravity");
			getCharArray<T>();
			sprintf(gravity, expressionF);
			puts("Free fall time (s)?");
			char* time = getDynamicCharArray("", "time");
			getCharArray<T>();
			sprintf(time, expressionF);
			puts("Free fall distance (m)?");
			char* height = getDynamicCharArray("", "height");
			getCharArray<T>();
			sprintf(height, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s-1/2*%s*%s^2", height, gravity, time);
			T answer = solve<T>(equation);
			if (isEqual("x", height)) {
				printf("\nFree fall distance: %s m\n", convert2Exponential(answer));
			}
			if (isEqual("x", time)) {
				printf("\nTime: %s s\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", gravity)) {
				printf("\nGravity: %s (m/s^2)\n", convert2Exponential(answer));
			}
			_delete(gravity, "gravity"); gravity = nullptr;
			_delete(time, "time"); time = nullptr;
			_delete(height, "height"); height = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 8) {
			puts("Enter the unknown value as 'x'");
			puts("Gravity (m/s^2)?");
			char* gravity = getDynamicCharArray("", "gravity");
			getCharArray<T>();
			sprintf(gravity, expressionF);
			puts("Free fall time (s)?");
			char* time = getDynamicCharArray("", "time");
			getCharArray<T>();
			sprintf(time, expressionF);
			puts("Free fall velocity (m/s)?");
			char* velocity = getDynamicCharArray("", "velocity");
			getCharArray<T>();
			sprintf(velocity, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s-%s*%s", velocity, gravity, time);
			T answer = solve<T>(equation);
			if (isEqual("x", velocity)) {
				printf("\nFree fall velocity: %s (m/s)\n", convert2Exponential(answer));
			}
			if (isEqual("x", time)) {
				printf("\nFree fall time: %s s\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", gravity)) {
				printf("\nGravity: %s (m/s^2)\n", convert2Exponential(answer));
			}
			_delete(gravity, "gravity"); gravity = nullptr;
			_delete(time, "time"); time = nullptr;
			_delete(velocity, "velocity"); velocity = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 9) {
			rasf = 0;
			puts("Enter the unknown value as 'x'");
			puts("Mass (kg)?");
			char* mass = getDynamicCharArray("", "mass");
			getCharArray<T>();
			sprintf(mass, expressionF);
			puts("Free fall time (s)?");
			char* time = getDynamicCharArray("", "time");
			getCharArray<T>();
			sprintf(time, expressionF);
			puts("Air resistance (kg/m)?");
			char* air_resistance = getDynamicCharArray("", "air_resistance");
			getCharArray<T>();
			sprintf(air_resistance, expressionF);
			puts("Gravity (m/s^2)?");
			char* gravity = getDynamicCharArray("", "gravity");
			getCharArray<T>();
			sprintf(gravity, expressionF);
			puts("Free fall distance (m)?");
			char* height = getDynamicCharArray("", "height");
			getCharArray<T>();
			sprintf(height, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s-(%s/%s)*ln(cosh(%s/sqrt(%s/(%s*%s))))", height, mass, air_resistance, time, mass, gravity, air_resistance);
			T answer = solver<T>(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %s (kg)\n", convert2Exponential(answer));
			}
			if (isEqual("x", air_resistance)) {
				printf("\nAir resistance: %s (kg/m)\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", time)) {
				printf("\nFree fall time: %s s\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", gravity)) {
				printf("\nGravity: %s (m/s^2)\n", convert2Exponential(answer));
			}
			if (isEqual("x", height)) {
				printf("\nFree fall distance: %s m\n", convert2Exponential(answer));
			}
			_delete(gravity, "gravity"); gravity = nullptr;
			_delete(time, "time"); time = nullptr;
			_delete(mass, "mass"); mass = nullptr;
			_delete(air_resistance, "air_resistance"); air_resistance = nullptr;
			_delete(height, "height"); height = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 10) {
			rasf = 0;
			puts("Enter the unknown value as 'x'");
			puts("Mass (kg)?");
			char* mass = getDynamicCharArray("", "mass");
			getCharArray<T>();
			sprintf(mass, expressionF);
			puts("Free fall time (s)?");
			char* time = getDynamicCharArray("", "time");
			getCharArray<T>();
			sprintf(time, expressionF);
			puts("Air resistance (kg/m)?");
			char* air_resistance = getDynamicCharArray("", "air_resistance");
			getCharArray<T>();
			sprintf(air_resistance, expressionF);
			puts("Gravity (m/s^2)?");
			char* gravity = getDynamicCharArray("", "gravity");
			getCharArray<T>();
			sprintf(gravity, expressionF);
			puts("Free fall velocity (m/s)?");
			char* velocity = getDynamicCharArray("", "velocity");
			getCharArray<T>();
			sprintf(velocity, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s-sqrt((%s*%s)/%s)*tanh(%s/sqrt(%s/(%s*%s)))", velocity, mass, gravity, air_resistance, time, mass, gravity, air_resistance);
			T answer = solver<T>(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %s (kg)\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", air_resistance)) {
				printf("\nAir resistance: %s (kg/m)\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", time)) {
				printf("\nFree fall time: %s s\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", gravity)) {
				printf("\nGravity: %s (m/s^2)\n", convert2Exponential(answer));
			}
			if (isEqual("x", velocity)) {
				printf("\nFree fall velocity: %s m\n", convert2Exponential(answer));
			}
			_delete(gravity, "gravity"); gravity = nullptr;
			_delete(time, "time"); time = nullptr;
			_delete(mass, "mass"); mass = nullptr;
			_delete(air_resistance, "air_resistance"); air_resistance = nullptr;
			_delete(velocity, "velocity"); velocity = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 11) {
			puts("Enter the unknown value as 'x'");
			puts("Mass (kg)?");
			char* mass = getDynamicCharArray("", "mass");
			getCharArray<T>();
			sprintf(mass, expressionF);
			puts("Acceleration (m/s^2)?");
			char* acceleration = getDynamicCharArray("", "acceleration");
			getCharArray<T>();
			sprintf(acceleration, expressionF);
			puts("Force (N)?");
			char* force = getDynamicCharArray("", "force");
			getCharArray<T>();
			sprintf(force, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s-%s*%s", force, acceleration, mass);
			T answer = solve<T>(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %s kg\n", convert2Exponential(answer));
			}
			if (isEqual("x", force)) {
				printf("\nForce: %s N\n", convert2Exponential(answer));
			}
			if (isEqual("x", acceleration)) {
				printf("\nAcceleration: %s (m/s^2)\n", convert2Exponential(answer));
			}
			_delete(mass, "mass"); mass = nullptr;
			_delete(acceleration, "acceleration"); acceleration = nullptr;
			_delete(force, "force"); force = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 12) {
			puts("Enter the unknown value as 'x'");
			puts("Friction Coefficient (N)?");
			char* friction_coefficient = getDynamicCharArray("", "friction_coefficient");
			getCharArray<T>();
			sprintf(friction_coefficient, expressionF);
			puts("Normal Force (N)?");
			char* normal_force = getDynamicCharArray("", "normal_force");
			getCharArray<T>();
			sprintf(normal_force, expressionF);
			puts("Frictional Force (N)?");
			char* frictional_force = getDynamicCharArray("", "frictional_force");
			getCharArray<T>();
			sprintf(frictional_force, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s-%s*%s", frictional_force, friction_coefficient, normal_force);
			T answer = solve<T>(equation);
			if (isEqual("x", frictional_force)) {
				printf("\nFrictional Force: %s N\n", convert2Exponential(answer));
			}
			if (isEqual("x", normal_force)) {
				printf("\nNormal Force: %s N\n", convert2Exponential(answer));
			}
			if (isEqual("x", friction_coefficient)) {
				printf("\nFriction Coefficient: %s N\n", convert2Exponential(answer));
			}
			_delete(friction_coefficient, "friction_coefficient"); friction_coefficient = nullptr;
			_delete(normal_force, "normal_force"); normal_force = nullptr;
			_delete(frictional_force, "frictional_force"); frictional_force = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 13) {
			puts("Enter the unknown value as 'x'");
			puts("Mass (kg)?");
			char* mass = getDynamicCharArray("", "mass");
			getCharArray<T>();
			sprintf(mass, expressionF);
			puts("Gravity (m/s^2)?");
			char* gravity = getDynamicCharArray("", "gravity");
			getCharArray<T>();
			sprintf(gravity, expressionF);
			puts("Weight/Force (N)?");
			char* weight_force = getDynamicCharArray("", "weight_force");
			getCharArray<T>();
			sprintf(weight_force, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s-%s*%s", weight_force, mass, gravity);
			T answer = solve<T>(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %s kg\n", convert2Exponential(answer));
			}
			if (isEqual("x", gravity)) {
				printf("\nGravity: %s (m/s^2)\n", convert2Exponential(answer));
			}
			if (isEqual("x", weight_force)) {
				printf("\nWeight/Force: %s N\n", convert2Exponential(answer));
			}
			_delete(mass, "mass"); mass = nullptr;
			_delete(gravity, "gravity"); gravity = nullptr;
			_delete(weight_force, "weight_force"); weight_force = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 14) {
			rasf = 0;
			puts("Enter the unknown value as 'x'");
			puts("Mass of first object (kg)?");
			char* mass_1 = getDynamicCharArray("", "mass_1");
			getCharArray<T>();
			sprintf(mass_1, expressionF);
			puts("Mass of second object (kg)?");
			char* mass_2 = getDynamicCharArray("", "mass_2");
			getCharArray<T>();
			sprintf(mass_2, expressionF);
			puts("Distance between the objects (m)?");
			char* distance_between_objects = getDynamicCharArray("", "distance_between_objects");
			getCharArray<T>();
			sprintf(distance_between_objects, expressionF);
			puts("Gravitational force (N)?");
			char* gravitational_force = getDynamicCharArray("", "gravitational_force");
			getCharArray<T>();
			sprintf(gravitational_force, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "6.6726E_11*%s*%s-%s*%s^2", mass_1, mass_2, gravitational_force, distance_between_objects);
			T answer = solve<T>(equation);
			if (isEqual("x", mass_1)) {
				printf("\nMass of fist object: %s kg\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", mass_2)) {
				printf("\nMass of second object: %s kg\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", distance_between_objects)) {
				printf("\nDistance between the objects: %s m\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", gravitational_force)) {
				printf("\nGravitational force: %s N\n", convert2Exponential(answer));
			}
			_delete(mass_1, "mass_1"); mass_1 = nullptr;
			_delete(mass_2, "mass_2"); mass_2 = nullptr;
			_delete(distance_between_objects, "distance_between_objects"); distance_between_objects = nullptr;
			_delete(gravitational_force, "gravitational_force"); gravitational_force = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 15) {
			puts("Enter the unknown value as 'x'");
			puts("Mass (kg)?");
			char* mass = getDynamicCharArray("", "mass");
			getCharArray<T>();
			sprintf(mass, expressionF);
			puts("Velocity at Impact (m/s)?");
			char* velocity_impact = getDynamicCharArray("", "velocity_impact");
			getCharArray<T>();
			sprintf(velocity_impact, expressionF);
			puts("Time Contact during Impact (s)?");
			char* time = getDynamicCharArray("", "time");
			getCharArray<T>();
			sprintf(time, expressionF);
			puts("Impact Force (N)?");
			char* impact_force = getDynamicCharArray("", "impact_force");
			getCharArray<T>();
			sprintf(impact_force, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "2*%s*%s-%s*%s", mass, velocity_impact, impact_force, time);
			T answer = solve<T>(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %s kg\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", velocity_impact)) {
				printf("\nVelocity at Impact: %s (m/s)\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", time)) {
				printf("\nTime Contact during Impact: %s s\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", impact_force)) {
				printf("\nImpact force: %s N\n", convert2Exponential(answer));
			}
			_delete(mass, "mass"); mass = nullptr;
			_delete(velocity_impact, "velocity_impact"); velocity_impact = nullptr;
			_delete(time, "time"); time = nullptr;
			_delete(impact_force, "impact_force"); impact_force = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 16) {
			puts("Enter the unknown value as 'x'");
			puts("Final Velocity (m/s)?");
			char* final_velocity = getDynamicCharArray("", "final_velocity");
			getCharArray<T>();
			sprintf(final_velocity, expressionF);
			puts("Initial Velocity (m/s)?");
			char* initial_velocity = getDynamicCharArray("", "initial_velocity");
			getCharArray<T>();
			sprintf(initial_velocity, expressionF);
			puts("Acceleration (m/s^2)?");
			char* acceleration = getDynamicCharArray("", "acceleration");
			getCharArray<T>();
			sprintf(acceleration, expressionF);
			puts("Time (s)?");
			char* time = getDynamicCharArray("", "time");
			getCharArray<T>();
			sprintf(time, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s+%s*%s-%s", initial_velocity, acceleration, time, final_velocity);
			T answer = solve<T>(equation);
			if (isEqual("x", initial_velocity)) {
				printf("\nInitial Velocity: %s (m/s)\n", convert2Exponential(abs(answer)));
				sprintf(initial_velocity, "%s", convert2Exponential(answer));
			}
			if (isEqual("x", final_velocity)) {
				printf("\nFinal Velocity: %s (m/s)\n", convert2Exponential(abs(answer)));
				sprintf(final_velocity, "%s", convert2Exponential(answer));
			}
			if (isEqual("x", time)) {
				printf("\nTime: %s s\n", convert2Exponential(abs(answer)));
				sprintf(time, "%s", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", acceleration)) {
				printf("\nAcceleration: %s (m/s^2)\n", convert2Exponential(answer));
				sprintf(acceleration, "%s", convert2Exponential(answer));
			}
			sprintf(equation, "%s*%s+(%s*%s^2)/2", initial_velocity, time, acceleration, time);
			T displacement = solve<T>(equation);
			printf("\nDisplacement: %s m\n", convert2Exponential(displacement));
			_delete(final_velocity, "final_velocity"); final_velocity = nullptr;
			_delete(initial_velocity, "initial_velocity"); initial_velocity = nullptr;
			_delete(acceleration, "acceleration"); acceleration = nullptr;
			_delete(time, "time"); time = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 17) {
			puts("Enter the unknown value as 'x'");
			puts("Effort Force (N)?");
			char* effort_force = getDynamicCharArray("", "effort_force");
			getCharArray<T>();
			sprintf(effort_force, expressionF);
			puts("Distance of Effort Force (m)?");
			char* distance_of_effort_force = getDynamicCharArray("", "distance_of_effort_force");
			getCharArray<T>();
			sprintf(distance_of_effort_force, expressionF);
			puts("Load Force (N)?");
			char* load_force = getDynamicCharArray("", "load_force");
			getCharArray<T>();
			sprintf(load_force, expressionF);
			puts("Distance of Load Force?");
			char* distance_of_load_force = getDynamicCharArray("", "distance_of_load_force");
			getCharArray<T>();
			sprintf(distance_of_load_force, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s*%s-%s*%s", effort_force, distance_of_effort_force, load_force, distance_of_load_force);
			T answer = solve<T>(equation);
			if (isEqual("x", effort_force)) {
				printf("\nEffort Force: %s N\n", convert2Exponential(answer));
			}
			if (isEqual("x", distance_of_effort_force)) {
				printf("\nDistance of Effort Force: %s m\n", convert2Exponential(answer));
			}
			if (isEqual("x", load_force)) {
				printf("\nLoad Force: %s N\n", convert2Exponential(answer));
			}
			if (isEqual("x", distance_of_load_force)) {
				printf("\nDistance of Load Force: %s m\n", convert2Exponential(answer));
			}
			_delete(effort_force, "effort_force"); effort_force = nullptr;
			_delete(distance_of_effort_force, "distance_of_effort_force"); distance_of_effort_force = nullptr;
			_delete(load_force, "load_force"); load_force = nullptr;
			_delete(distance_of_load_force, "distance_of_load_force"); distance_of_load_force = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 18) {
			puts("Angle (degrees)?");
			char* angle_degrees = getDynamicCharArray("", "angle_degrees");
			getCharArray<T>();
			sprintf(angle_degrees, expressionF);
			puts("Release Velocity (m/s)?");
			char* release_velocity = getDynamicCharArray("", "release_velocity");
			getCharArray<T>();
			sprintf(release_velocity, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s*%s*degsin(%s)*degsin(%s)-x*2*9.80665", release_velocity, release_velocity, angle_degrees, angle_degrees);
			T maximum_height = solve<T>(equation);
			printf("\nMaximum Height: %s m\n", convert2Exponential(maximum_height));
			sprintf(equation, "%s*%s*degsin(2*%s)-x*9.80665", release_velocity, release_velocity, angle_degrees);
			T distance_traveled = solve<T>(equation);
			printf("\nDistance Traveled: %s m\n", convert2Exponential(distance_traveled));
			sprintf(equation, "2*%s*degsin(%s)-x*9.80665", release_velocity, angle_degrees);
			T time_taken = solve<T>(equation);
			printf("\nTime Taken: %s s\n", convert2Exponential(time_taken));
			_delete(angle_degrees, "angle_degrees"); angle_degrees = nullptr;
			_delete(release_velocity, "release_velocity"); release_velocity = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 19) {
			puts("Enter the unknown value as 'x'");
			puts("Mass (kg)?");
			char* mass = getDynamicCharArray("", "mass");
			getCharArray<T>();
			sprintf(mass, expressionF);
			puts("Velocity (m/s)?");
			char* velocity = getDynamicCharArray("", "velocity");
			getCharArray<T>();
			sprintf(velocity, expressionF);
			puts("Momentum (kg.m/s)?");
			char* momentum = getDynamicCharArray("", "momentum");
			getCharArray<T>();
			sprintf(momentum, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s-%s*%s", momentum, mass, velocity);
			T answer = solve<T>(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %s kg\n", convert2Exponential(answer));
			}
			if (isEqual("x", velocity)) {
				printf("\nVelocity: %s (m/s)\n", convert2Exponential(answer));
			}
			if (isEqual("x", momentum)) {
				printf("\nMomentum: %s (kg.m/s)\n", convert2Exponential(answer));
			}
			_delete(mass, "mass"); mass = nullptr;
			_delete(velocity, "velocity"); velocity = nullptr;
			_delete(momentum, "momentum"); momentum = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 20) {
			puts("Enter the unknown value as 'x'");
			puts("Length (m)?");
			char* length = getDynamicCharArray("", "length");
			getCharArray<T>();
			sprintf(length, expressionF);
			puts("Acceleration of Gravity (m/s^2)?");
			char* acceleration_of_gravity = getDynamicCharArray("", "acceleration_of_gravity");
			getCharArray<T>();
			sprintf(acceleration_of_gravity, expressionF);
			puts("Period (s)?");
			char* period = getDynamicCharArray("", "period");
			getCharArray<T>();
			sprintf(period, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s*%s^2-2*pi*2*pi*%s", acceleration_of_gravity, period, length);
			T answer = solver<T>(equation);
			if (isEqual("x", period)) {
				printf("\nPeriod: %s s\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", acceleration_of_gravity)) {
				printf("\nAcceleration of Gravity: %s (m/s^2)\n", convert2Exponential(answer));
			}
			if (isEqual("x", length)) {
				printf("\nLength: %s m\n", convert2Exponential(answer));
			}
			_delete(length, "length"); length = nullptr;
			_delete(acceleration_of_gravity, "acceleration_of_gravity"); acceleration_of_gravity = nullptr;
			_delete(period, "period"); period = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 21) {
			puts("Enter the unknown value as 'x'");
			puts("Range (m)?");
			char* range = getDynamicCharArray("", "range");
			getCharArray<T>();
			sprintf(range, expressionF);
			puts("Initial Velocity (m/s)?");
			char* initial_velocity = getDynamicCharArray("", "initial_velocity");
			getCharArray<T>();
			sprintf(initial_velocity, expressionF);
			puts("Acceleration of Gravity (m/s^2)?");
			char* acceleration_of_gravity = getDynamicCharArray("", "acceleration_of_gravity");
			getCharArray<T>();
			sprintf(acceleration_of_gravity, expressionF);
			puts("Angle (Degree)?");
			char* angle_degree = getDynamicCharArray("", "angle_degree");
			getCharArray<T>();
			sprintf(angle_degree, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			if (isEqual("x", angle_degree) == (bool)false) {
				T angle = solveMath<T>(angle_degree);
				sprintf(equation, "%s*%s-%s^2*degsin(%s)", range, acceleration_of_gravity, initial_velocity, convert2Exponential(angle * 2));
			}
			else {
				sprintf(equation, "%s-degasin((%s*%s)/(%s^2))", angle_degree, range, acceleration_of_gravity, initial_velocity);
			}
			T answer = solve<T>(equation);
			if (isEqual("x", range)) {
				printf("\nRange: %s m\n", convert2Exponential(answer));
			}
			if (isEqual("x", acceleration_of_gravity)) {
				printf("\nAcceleration of Gravity: %s (m/s^2)\n", convert2Exponential(answer));
			}
			if (isEqual("x", initial_velocity)) {
				printf("\nInitial Velocity: %s (m/s)\n", convert2Exponential(abs(answer)));
			}
			if (isEqual("x", angle_degree)) {
				printf("\nAngle: %s (Degree)\n", convert2Exponential(answer / 2));
			}
			_delete(range, "range"); range = nullptr;
			_delete(initial_velocity, "initial_velocity"); initial_velocity = nullptr;
			_delete(acceleration_of_gravity, "acceleration_of_gravity"); acceleration_of_gravity = nullptr;
			_delete(angle_degree, "angle_degree"); angle_degree = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 22) {
			puts("Enter the unknown value as 'x'");
			puts("First Vector?");
			char* first_vector = getDynamicCharArray("", "first_vector");
			getCharArray<T>();
			sprintf(first_vector, expressionF);
			puts("Second Vector?");
			char* second_vector = getDynamicCharArray("", "second_vector");
			getCharArray<T>();
			sprintf(second_vector, expressionF);
			puts("Resultant Vector?");
			char* resultant_vector = getDynamicCharArray("", "resultant_vector");
			getCharArray<T>();
			sprintf(resultant_vector, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s^2+%s^2-%s^2", first_vector, second_vector, resultant_vector);
			T answer = abs(solve<T>(equation));
			if (isEqual("x", resultant_vector)) {
				printf("\nResultant Vector: %s\n", convert2Exponential(answer));
			}
			if (isEqual("x", first_vector)) {
				printf("\nFirst vector: %s\n", convert2Exponential(answer));
			}
			if (isEqual("x", second_vector)) {
				printf("\nSecond Vector: %s\n", convert2Exponential(answer));
			}
			_delete(first_vector, "first_vector"); first_vector = nullptr;
			_delete(second_vector, "second_vector"); second_vector = nullptr;
			_delete(resultant_vector, "resultant_vector"); resultant_vector = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 23) {
			puts("Enter the unknown value as 'x'");
			puts("Force (N)?");
			char* force = getDynamicCharArray("", "force");
			getCharArray<T>();
			sprintf(force, expressionF);
			puts("Distance or Length (m)?");
			char* distance_or_length = getDynamicCharArray("", "distance_or_length");
			getCharArray<T>();
			sprintf(distance_or_length, expressionF);
			puts("Torque (N.m)?");
			char* torque = getDynamicCharArray("", "torque");
			getCharArray<T>();
			sprintf(torque, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s*%s-%s", force, distance_or_length, torque);
			T answer = solve<T>(equation);
			if (isEqual("x", torque)) {
				printf("\nTorque: %s N.m\n", convert2Exponential(answer));
			}
			if (isEqual("x", force)) {
				printf("\nForce: %s N\n", convert2Exponential(answer));
			}
			if (isEqual("x", distance_or_length)) {
				printf("\nDistance or length: %s m\n", convert2Exponential(answer));
			}
			_delete(force, "force"); force = nullptr;
			_delete(distance_or_length, "distance_or_length"); distance_or_length = nullptr;
			_delete(torque, "torque"); torque = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 24) {
			puts("Enter the unknown value as 'x'");
			puts("Initial Velocity (m/s)?");
			char* initial_velocity = getDynamicCharArray("", "initial_velocity");
			getCharArray<T>();
			sprintf(initial_velocity, expressionF);
			puts("Acceleration (m/s^2)?");
			char* acceleration = getDynamicCharArray("", "acceleration");
			getCharArray<T>();
			sprintf(acceleration, expressionF);
			puts("Time (s)?");
			char* time = getDynamicCharArray("", "time");
			getCharArray<T>();
			sprintf(time, expressionF);
			puts("Velocity (m/s)?");
			char* velocity = getDynamicCharArray("", "velocity");
			getCharArray<T>();
			sprintf(velocity, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s+%s*%s-%s", initial_velocity, acceleration, time, velocity);
			T answer = solve<T>(equation);
			if (isEqual("x", initial_velocity)) {
				printf("\nInitial Velocity: %s (m/s)\n", convert2Exponential(answer));
			}
			if (isEqual("x", velocity)) {
				printf("\nVelocity: %s (m/s)\n", convert2Exponential(answer));
			}
			if (isEqual("x", acceleration)) {
				printf("\nAcceleration: %s (m/s^2)\n", convert2Exponential(answer));
			}
			if (isEqual("x", time)) {
				printf("\nTime: %s s\n", convert2Exponential(answer));
			}
			_delete(initial_velocity, "initial_velocity"); initial_velocity = nullptr;
			_delete(acceleration, "acceleration"); acceleration = nullptr;
			_delete(time, "time"); time = nullptr;
			_delete(velocity, "velocity"); velocity = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op == 25) {
			puts("Enter the unknown value as 'x'");
			puts("Initial Velocity (m/s)?");
			char* initial_velocity = getDynamicCharArray("", "initial_velocity");
			getCharArray<T>();
			sprintf(initial_velocity, expressionF);
			puts("Velocity (m/s)?");
			char* velocity = getDynamicCharArray("", "velocity");
			getCharArray<T>();
			sprintf(velocity, expressionF);
			puts("Average Velocity (m/s)?");
			char* average_velocity = getDynamicCharArray("", "average_velocity");
			getCharArray<T>();
			sprintf(average_velocity, expressionF);
			char* equation = getDynamicCharArray("", "equation");
			sprintf(equation, "%s+%s-2*%s", initial_velocity, velocity, average_velocity);
			T answer = solve<T>(equation);
			if (isEqual("x", average_velocity)) {
				printf("\nAverage Velocity: %s (m/s)\n", convert2Exponential(answer));
			}
			if (isEqual("x", initial_velocity)) {
				printf("\nInitial Velocity: %s (m/s)\n", convert2Exponential(answer));
			}
			if (isEqual("x", velocity)) {
				printf("\nVelocity: %s (m/s)\n", convert2Exponential(answer));
			}
			_delete(initial_velocity, "initial_velocity"); initial_velocity = nullptr;
			_delete(velocity, "velocity"); velocity = nullptr;
			_delete(average_velocity, "average_velocity"); average_velocity = nullptr;
			_delete(equation, "equation"); equation = nullptr;
		}
		if (op < 1 || op>25) {
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
	physics = false;
}

void physicsCalculations() { physicsCalculations<double>(); }
