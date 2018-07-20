#include "stdafx.h"

boolean physics = false;

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
		op = (int)getValue();
		if (op == 1) {
			puts("Enter the unknown value as 'x'");
			puts("Initial Speed (m/s)?");
			char initial_speed[dim] = "";
			getCharArray();
			sprintf(initial_speed, expressionF);
			puts("Final Speed (m/s)?");
			char final_speed[dim] = "";
			getCharArray();
			sprintf(final_speed, expressionF);
			puts("Time (s)?");
			char time[dim] = "";
			getCharArray();
			sprintf(time, expressionF);
			puts("Acceleration (m/s^2)?");
			char acceleration[dim] = "";
			getCharArray();
			sprintf(acceleration, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s*%s-(%s-%s)", acceleration, time, final_speed, initial_speed);
			double answer = solve(equation);
			if (isEqual("x", acceleration)) {
				printf("\nAcceleration: %G (m/s^2)\n", answer);
			}
			if (isEqual("x", time)) {
				printf("\nTime: %G (s)\n", answer);
			}
			if (isEqual("x", final_speed)) {
				printf("\nFinal Speed: %G (m/s)\n", answer);
			}
			if (isEqual("x", initial_speed)) {
				printf("\nInitial Speed: %G (m/s)\n", answer);
			}
		}
		if (op == 2) {
			puts("Enter the unknown value as 'x'");
			puts("Density of Fluid (kg/m^3)?");
			char density_of_fluid[dim] = "";
			getCharArray();
			sprintf(density_of_fluid, expressionF);
			puts("Displaced Volume (kg/m^3)?");
			char displaced_volume[dim] = "";
			getCharArray();
			sprintf(displaced_volume, expressionF);
			puts("Buoyancy Force (N)?");
			char buoyancy_force[dim] = "";
			getCharArray();
			sprintf(buoyancy_force, expressionF);
			char equation[dim] = "";
			double gravity = 9.80665;
			sprintf(equation, "%s-%s*%s*%G", buoyancy_force, density_of_fluid, displaced_volume, gravity);
			double answer = solve(equation);
			if (isEqual("x", buoyancy_force)) {
				printf("\nBuoyancy Force: %G N\n", answer);
			}
			if (isEqual("x", displaced_volume)) {
				printf("\nDisplaced Volume: %G (kg/m^3)\n", answer);
			}
			if (isEqual("x", density_of_fluid)) {
				printf("\nDensity of Fluid: %G (kg/m^3)\n", answer);
			}
		}
		if (op == 3) {
			puts("Mass (kg)?");
			char mass[dim] = "";
			getCharArray();
			sprintf(mass, expressionF);
			puts("Radius (m)?");
			char radius[dim] = "";
			getCharArray();
			sprintf(radius, expressionF);
			puts("Velocity (m/s)?");
			char velocity[dim] = "";
			getCharArray();
			sprintf(velocity, expressionF);
			puts("Centripetal Force (N)?");
			char centripetal_force[dim] = "";
			getCharArray();
			sprintf(centripetal_force, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s*%s-%s*%s^2", centripetal_force, radius, mass, velocity);
			double answer = solve(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %G (kg)\n", answer);
			}
			if (isEqual("x", radius)) {
				printf("\nRadius: %G (m)\n", answer);
			}
			if (isEqual("x", velocity)) {
				printf("\nFinal Speed: %G (m/s)\n", abs(answer));
			}
			if (isEqual("x", centripetal_force)) {
				printf("\nCentripetal Force: %G N\n", answer);
			}
		}
		if (op == 4) {
			puts("Mass of Moving Object (kg)?");
			double mass = getValue();
			puts("Velocity of Moving Object (m/s)?");
			double velocity = getValue();
			puts("Mass of Stationary Object (kg)?");
			double mass_stationary = getValue();
			double v_1 = ((mass - mass_stationary) / (mass + mass_stationary))*velocity;
			double v_2 = (2 * mass / (mass + mass_stationary))*velocity;
			printf("\nVelocities after collision:\nThe moving object: %G (m/s)\nThe stationary object: %G (m/s)\n", v_1, v_2);
		}
		if (op == 5) {
			puts("Enter the unknown value as 'x'");
			puts("Density (kg/m^3)?");
			char density[dim] = "";
			getCharArray();
			sprintf(density, expressionF);
			puts("Volume (m^3)?");
			char volume[dim] = "";
			getCharArray();
			sprintf(volume, expressionF);
			puts("Mass (kg)?");
			char mass[dim] = "";
			getCharArray();
			sprintf(mass, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s-%s*%s", mass, density, volume);
			double answer = solve(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %G kg\n", answer);
			}
			if (isEqual("x", density)) {
				printf("\nDensity: %G (kg/m^3)\n", answer);
			}
			if (isEqual("x", volume)) {
				printf("\nVolume: %G (m^3)\n", answer);
			}
		}
		if (op == 6) {
			puts("Enter the unknown value as 'x'");
			puts("Average Velocity (m/s)?");
			char avg_velocity[dim] = "";
			getCharArray();
			sprintf(avg_velocity, expressionF);
			puts("Time (s)?");
			char time[dim] = "";
			getCharArray();
			sprintf(time, expressionF);
			puts("Displacement (m)?");
			char displacement[dim] = "";
			getCharArray();
			sprintf(displacement, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s-%s*%s", displacement, avg_velocity, time);
			double answer = solve(equation);
			if (isEqual("x", displacement)) {
				printf("\nDisplacement: %G m\n", answer);
			}
			if (isEqual("x", time)) {
				printf("\nTime: %G s\n", answer);
			}
			if (isEqual("x", avg_velocity)) {
				printf("\nAverage Velocity: %G (m/s)\n", answer);
			}
		}
		if (op == 7) {
			puts("Enter the unknown value as 'x'");
			puts("Gravity (m/s^2)?");
			char gravity[dim] = "";
			getCharArray();
			sprintf(gravity, expressionF);
			puts("Free fall time (s)?");
			char time[dim] = "";
			getCharArray();
			sprintf(time, expressionF);
			puts("Free fall distance (m)?");
			char height[dim] = "";
			getCharArray();
			sprintf(height, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s-1/2*%s*%s^2", height, gravity, time);
			double answer = solve(equation);
			if (isEqual("x", height)) {
				printf("\nFree fall distance: %G m\n", answer);
			}
			if (isEqual("x", time)) {
				printf("\nTime: %G s\n", abs(answer));
			}
			if (isEqual("x", gravity)) {
				printf("\nGravity: %G (m/s^2)\n", answer);
			}
		}
		if (op == 8) {
			puts("Enter the unknown value as 'x'");
			puts("Gravity (m/s^2)?");
			char gravity[dim] = "";
			getCharArray();
			sprintf(gravity, expressionF);
			puts("Free fall time (s)?");
			char time[dim] = "";
			getCharArray();
			sprintf(time, expressionF);
			puts("Free fall velocity (m/s)?");
			char velocity[dim] = "";
			getCharArray();
			sprintf(velocity, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s-%s*%s", velocity, gravity, time);
			double answer = solve(equation);
			if (isEqual("x", velocity)) {
				printf("\nFree fall velocity: %G (m/s)\n", answer);
			}
			if (isEqual("x", time)) {
				printf("\nFree fall time: %G s\n", abs(answer));
			}
			if (isEqual("x", gravity)) {
				printf("\nGravity: %G (m/s^2)\n", answer);
			}
		}
		if (op == 9) {
			rasf = 0;
			puts("Enter the unknown value as 'x'");
			puts("Mass (kg)?");
			char mass[dim] = "";
			getCharArray();
			sprintf(mass, expressionF);
			puts("Free fall time (s)?");
			char time[dim] = "";
			getCharArray();
			sprintf(time, expressionF);
			puts("Air resistance (kg/m)?");
			char air_resistance[dim] = "";
			getCharArray();
			sprintf(air_resistance, expressionF);
			puts("Gravity (m/s^2)?");
			char gravity[dim] = "";
			getCharArray();
			sprintf(gravity, expressionF);
			puts("Free fall distance (m)?");
			char height[dim] = "";
			getCharArray();
			sprintf(height, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s-(%s/%s)*ln(cosh(%s/sqrt(%s/(%s*%s))))", height, mass, air_resistance, time, mass, gravity, air_resistance);
			double answer = solver(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %G (kg)\n", answer);
			}
			if (isEqual("x", air_resistance)) {
				printf("\nAir resistance: %G (kg/m)\n", abs(answer));
			}
			if (isEqual("x", time)) {
				printf("\nFree fall time: %G s\n", abs(answer));
			}
			if (isEqual("x", gravity)) {
				printf("\nGravity: %G (m/s^2)\n", answer);
			}
			if (isEqual("x", height)) {
				printf("\nFree fall distance: %G m\n", answer);
			}
		}
		if (op == 10) {
			rasf = 0;
			puts("Enter the unknown value as 'x'");
			puts("Mass (kg)?");
			char mass[dim] = "";
			getCharArray();
			sprintf(mass, expressionF);
			puts("Free fall time (s)?");
			char time[dim] = "";
			getCharArray();
			sprintf(time, expressionF);
			puts("Air resistance (kg/m)?");
			char air_resistance[dim] = "";
			getCharArray();
			sprintf(air_resistance, expressionF);
			puts("Gravity (m/s^2)?");
			char gravity[dim] = "";
			getCharArray();
			sprintf(gravity, expressionF);
			puts("Free fall velocity (m/s)?");
			char velocity[dim] = "";
			getCharArray();
			sprintf(velocity, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s-sqrt((%s*%s)/%s)*tanh(%s/sqrt(%s/(%s*%s)))", velocity, mass, gravity, air_resistance, time, mass, gravity, air_resistance);
			double answer = solver(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %G (kg)\n", abs(answer));
			}
			if (isEqual("x", air_resistance)) {
				printf("\nAir resistance: %G (kg/m)\n", abs(answer));
			}
			if (isEqual("x", time)) {
				printf("\nFree fall time: %G s\n", abs(answer));
			}
			if (isEqual("x", gravity)) {
				printf("\nGravity: %G (m/s^2)\n", answer);
			}
			if (isEqual("x", velocity)) {
				printf("\nFree fall velocity: %G m\n", answer);
			}
		}
		if (op == 11) {
			puts("Enter the unknown value as 'x'");
			puts("Mass (kg)?");
			char mass[dim] = "";
			getCharArray();
			sprintf(mass, expressionF);
			puts("Acceleration (m/s^2)?");
			char acceleration[dim] = "";
			getCharArray();
			sprintf(acceleration, expressionF);
			puts("Force (N)?");
			char force[dim] = "";
			getCharArray();
			sprintf(force, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s-%s*%s", force, acceleration, mass);
			double answer = solve(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %G kg\n", answer);
			}
			if (isEqual("x", force)) {
				printf("\nForce: %G N\n", answer);
			}
			if (isEqual("x", acceleration)) {
				printf("\nAcceleration: %G (m/s^2)\n", answer);
			}
		}
		if (op == 12) {
			puts("Enter the unknown value as 'x'");
			puts("Friction Coefficient (N)?");
			char friction_coefficient[dim] = "";
			getCharArray();
			sprintf(friction_coefficient, expressionF);
			puts("Normal Force (N)?");
			char normal_force[dim] = "";
			getCharArray();
			sprintf(normal_force, expressionF);
			puts("Frictional Force (N)?");
			char frictional_force[dim] = "";
			getCharArray();
			sprintf(frictional_force, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s-%s*%s", frictional_force, friction_coefficient, normal_force);
			double answer = solve(equation);
			if (isEqual("x", frictional_force)) {
				printf("\nFrictional Force: %G N\n", answer);
			}
			if (isEqual("x", normal_force)) {
				printf("\nNormal Force: %G N\n", answer);
			}
			if (isEqual("x", friction_coefficient)) {
				printf("\nFriction Coefficient: %G N\n", answer);
			}
		}
		if (op == 13) {
			puts("Enter the unknown value as 'x'");
			puts("Mass (kg)?");
			char mass[dim] = "";
			getCharArray();
			sprintf(mass, expressionF);
			puts("Gravity (m/s^2)?");
			char gravity[dim] = "";
			getCharArray();
			sprintf(gravity, expressionF);
			puts("Weight/Force (N)?");
			char weight_force[dim] = "";
			getCharArray();
			sprintf(weight_force, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s-%s*%s", weight_force, mass, gravity);
			double answer = solve(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %G kg\n", answer);
			}
			if (isEqual("x", gravity)) {
				printf("\nGravity: %G (m/s^2)\n", answer);
			}
			if (isEqual("x", weight_force)) {
				printf("\nWeight/Force: %G N\n", answer);
			}
		}
		if (op == 14) {
			rasf = 0;
			puts("Enter the unknown value as 'x'");
			puts("Mass of first object (kg)?");
			char mass_1[dim] = "";
			getCharArray();
			sprintf(mass_1, expressionF);
			puts("Mass of second object (kg)?");
			char mass_2[dim] = "";
			getCharArray();
			sprintf(mass_2, expressionF);
			puts("Distance between the objects (m)?");
			char distance_between_objects[dim] = "";
			getCharArray();
			sprintf(distance_between_objects, expressionF);
			puts("Gravitational force (N)?");
			char gravitational_force[dim] = "";
			getCharArray();
			sprintf(gravitational_force, expressionF);
			char equation[dim] = "";
			sprintf(equation, "6.6726E_11*%s*%s-%s*%s^2", mass_1, mass_2, gravitational_force, distance_between_objects);
			double answer = solve(equation);
			if (isEqual("x", mass_1)) {
				printf("\nMass of fist object: %G kg\n", abs(answer));
			}
			if (isEqual("x", mass_2)) {
				printf("\nMass of second object: %G kg\n", abs(answer));
			}
			if (isEqual("x", distance_between_objects)) {
				printf("\nDistance between the objects: %G m\n", abs(answer));
			}
			if (isEqual("x", gravitational_force)) {
				printf("\nGravitational force: %G N\n", answer);
			}
		}
		if (op == 15) {
			puts("Enter the unknown value as 'x'");
			puts("Mass (kg)?");
			char mass[dim] = "";
			getCharArray();
			sprintf(mass, expressionF);
			puts("Velocity at Impact (m/s)?");
			char velocity_impact[dim] = "";
			getCharArray();
			sprintf(velocity_impact, expressionF);
			puts("Time Contact during Impact (s)?");
			char time[dim] = "";
			getCharArray();
			sprintf(time, expressionF);
			puts("Impact Force (N)?");
			char impact_force[dim] = "";
			getCharArray();
			sprintf(impact_force, expressionF);
			char equation[dim] = "";
			sprintf(equation, "2*%s*%s-%s*%s", mass, velocity_impact, impact_force, time);
			double answer = solve(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %G kg\n", abs(answer));
			}
			if (isEqual("x", velocity_impact)) {
				printf("\nVelocity at Impact: %G (m/s)\n", abs(answer));
			}
			if (isEqual("x", time)) {
				printf("\nTime Contact during Impact: %G s\n", abs(answer));
			}
			if (isEqual("x", impact_force)) {
				printf("\nImpact force: %G N\n", answer);
			}
		}
		if (op == 16) {
			puts("Enter the unknown value as 'x'");
			puts("Final Velocity (m/s)?");
			char final_velocity[dim] = "";
			getCharArray();
			sprintf(final_velocity, expressionF);
			puts("Initial Velocity (m/s)?");
			char initial_velocity[dim] = "";
			getCharArray();
			sprintf(initial_velocity, expressionF);
			puts("Acceleration (m/s^2)?");
			char acceleration[dim] = "";
			getCharArray();
			sprintf(acceleration, expressionF);
			puts("Time (s)?");
			char time[dim] = "";
			getCharArray();
			sprintf(time, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s+%s*%s-%s", initial_velocity, acceleration, time, final_velocity);
			double answer = solve(equation);
			if (isEqual("x", initial_velocity)) {
				printf("\nInitial Velocity: %G (m/s)\n", abs(answer));
				sprintf(initial_velocity, "%G", answer);
			}
			if (isEqual("x", final_velocity)) {
				printf("\nFinal Velocity: %G (m/s)\n", abs(answer));
				sprintf(final_velocity, "%G", answer);
			}
			if (isEqual("x", time)) {
				printf("\nTime: %G s\n", abs(answer));
				sprintf(time, "%G", abs(answer));
			}
			if (isEqual("x", acceleration)) {
				printf("\nAcceleration: %G (m/s^2)\n", answer);
				sprintf(acceleration, "%G", answer);
			}
			sprintf(equation, "%s*%s+(%s*%s^2)/2", initial_velocity, time, acceleration, time);
			double displacement = calcNow(equation, 0, 0);
			printf("\nDisplacement: %G m\n", displacement);
		}
		if (op == 17) {
			puts("Enter the unknown value as 'x'");
			puts("Effort Force (N)?");
			char effort_force[dim] = "";
			getCharArray();
			sprintf(effort_force, expressionF);
			puts("Distance of Effort Force (m)?");
			char distance_of_effort_force[dim] = "";
			getCharArray();
			sprintf(distance_of_effort_force, expressionF);
			puts("Load Force (N)?");
			char load_force[dim] = "";
			getCharArray();
			sprintf(load_force, expressionF);
			puts("Distance of Load Force?");
			char distance_of_load_force[dim] = "";
			getCharArray();
			sprintf(distance_of_load_force, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s*%s-%s*%s", effort_force, distance_of_effort_force, load_force, distance_of_load_force);
			double answer = solve(equation);
			if (isEqual("x", effort_force)) {
				printf("\nEffort Force: %G N\n", answer);
			}
			if (isEqual("x", distance_of_effort_force)) {
				printf("\nDistance of Effort Force: %G m\n", answer);
			}
			if (isEqual("x", load_force)) {
				printf("\nLoad Force: %G N\n", answer);
			}
			if (isEqual("x", distance_of_load_force)) {
				printf("\nDistance of Load Force: %G m\n", answer);
			}
		}
		if (op == 18) {
			puts("Angle (degrees)?");
			char angle_degrees[dim] = "";
			getCharArray();
			sprintf(angle_degrees, expressionF);
			puts("Release Velocity (m/s)?");
			char release_velocity[dim] = "";
			getCharArray();
			sprintf(release_velocity, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s*%s*degsin(%s)*degsin(%s)-x*2*9.80665", release_velocity, release_velocity, angle_degrees, angle_degrees);
			double maximum_height = solve(equation);
			printf("\nMaximum Height: %G m\n", maximum_height);
			sprintf(equation, "%s*%s*degsin(2*%s)-x*9.80665", release_velocity, release_velocity, angle_degrees);
			double distance_traveled = solve(equation);
			printf("\nDistance Traveled: %G m\n", distance_traveled);
			sprintf(equation, "2*%s*degsin(%s)-x*9.80665", release_velocity, angle_degrees);
			double time_taken = solve(equation);
			printf("\nTime Taken: %G s\n", time_taken);
		}
		if (op == 19) {
			puts("Enter the unknown value as 'x'");
			puts("Mass (kg)?");
			char mass[dim] = "";
			getCharArray();
			sprintf(mass, expressionF);
			puts("Velocity (m/s)?");
			char velocity[dim] = "";
			getCharArray();
			sprintf(velocity, expressionF);
			puts("Momentum (kg.m/s)?");
			char momentum[dim] = "";
			getCharArray();
			sprintf(momentum, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s-%s*%s", momentum, mass, velocity);
			double answer = solve(equation);
			if (isEqual("x", mass)) {
				printf("\nMass: %G kg\n", answer);
			}
			if (isEqual("x", velocity)) {
				printf("\nVelocity: %G (m/s)\n", answer);
			}
			if (isEqual("x", momentum)) {
				printf("\nMomentum: %G (kg.m/s)\n", answer);
			}
		}
		if (op == 20) {
			puts("Enter the unknown value as 'x'");
			puts("Length (m)?");
			char length[dim] = "";
			getCharArray();
			sprintf(length, expressionF);
			puts("Acceleration of Gravity (m/s^2)?");
			char acceleration_of_gravity[dim] = "";
			getCharArray();
			sprintf(acceleration_of_gravity, expressionF);
			puts("Period (s)?");
			char period[dim] = "";
			getCharArray();
			sprintf(period, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s*%s^2-2*pi*2*pi*%s", acceleration_of_gravity, period, length);
			double answer = solver(equation);
			if (isEqual("x", period)) {
				printf("\nPeriod: %G s\n", abs(answer));
			}
			if (isEqual("x", acceleration_of_gravity)) {
				printf("\nAcceleration of Gravity: %G (m/s^2)\n", answer);
			}
			if (isEqual("x", length)) {
				printf("\nLength: %G m\n", answer);
			}
		}
		if (op == 21) {
			puts("Enter the unknown value as 'x'");
			puts("Range (m)?");
			char range[dim] = "";
			getCharArray();
			sprintf(range, expressionF);
			puts("Initial Velocity (m/s)?");
			char initial_velocity[dim] = "";
			getCharArray();
			sprintf(initial_velocity, expressionF);
			puts("Acceleration of Gravity (m/s^2)?");
			char acceleration_of_gravity[dim] = "";
			getCharArray();
			sprintf(acceleration_of_gravity, expressionF);
			puts("Angle (Degree)?");
			char angle_degree[dim] = "";
			getCharArray();
			sprintf(angle_degree, expressionF);
			char equation[dim] = "";
			if (isEqual("x", angle_degree) == (boolean)false) {
				double angle = calcNow(angle_degree, 0, 0);
				sprintf(equation, "%s*%s-%s^2*degsin(%G)", range, acceleration_of_gravity, initial_velocity, angle * 2);
			}
			else {
				sprintf(equation, "%s-degasin((%s*%s)/(%s^2))", angle_degree, range, acceleration_of_gravity, initial_velocity);
			}
			double answer = solve(equation);
			if (isEqual("x", range)) {
				printf("\nRange: %G m\n", answer);
			}
			if (isEqual("x", acceleration_of_gravity)) {
				printf("\nAcceleration of Gravity: %G (m/s^2)\n", answer);
			}
			if (isEqual("x", initial_velocity)) {
				printf("\nInitial Velocity: %G (m/s)\n", abs(answer));
			}
			if (isEqual("x", angle_degree)) {
				printf("\nAngle: %G (Degree)\n", answer / 2);
			}
		}
		if (op == 22) {
			puts("Enter the unknown value as 'x'");
			puts("First Vector?");
			char first_vector[dim] = "";
			getCharArray();
			sprintf(first_vector, expressionF);
			puts("Second Vector?");
			char second_vector[dim] = "";
			getCharArray();
			sprintf(second_vector, expressionF);
			puts("Resultant Vector?");
			char resultant_vector[dim] = "";
			getCharArray();
			sprintf(resultant_vector, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s^2+%s^2-%s^2", first_vector, second_vector, resultant_vector);
			double answer = abs(solve(equation));
			if (isEqual("x", resultant_vector)) {
				printf("\nResultant Vector: %G\n", answer);
			}
			if (isEqual("x", first_vector)) {
				printf("\nFirst vector: %G\n", answer);
			}
			if (isEqual("x", second_vector)) {
				printf("\nSecond Vector: %G\n", answer);
			}
		}
		if (op == 23) {
			puts("Enter the unknown value as 'x'");
			puts("Force (N)?");
			char force[dim] = "";
			getCharArray();
			sprintf(force, expressionF);
			puts("Distance or Length (m)?");
			char distance_or_length[dim] = "";
			getCharArray();
			sprintf(distance_or_length, expressionF);
			puts("Torque (N.m)?");
			char torque[dim] = "";
			getCharArray();
			sprintf(torque, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s*%s-%s", force, distance_or_length, torque);
			double answer = solve(equation);
			if (isEqual("x", torque)) {
				printf("\nTorque: %G N.m\n", answer);
			}
			if (isEqual("x", force)) {
				printf("\nForce: %G N\n", answer);
			}
			if (isEqual("x", distance_or_length)) {
				printf("\nDistance or length: %G m\n", answer);
			}
		}
		if (op == 24) {
			puts("Enter the unknown value as 'x'");
			puts("Initial Velocity (m/s)?");
			char initial_velocity[dim] = "";
			getCharArray();
			sprintf(initial_velocity, expressionF);
			puts("Acceleration (m/s^2)?");
			char acceleration[dim] = "";
			getCharArray();
			sprintf(acceleration, expressionF);
			puts("Time (s)?");
			char time[dim] = "";
			getCharArray();
			sprintf(time, expressionF);
			puts("Velocity (m/s)?");
			char velocity[dim] = "";
			getCharArray();
			sprintf(velocity, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s+%s*%s-%s", initial_velocity, acceleration, time, velocity);
			double answer = solve(equation);
			if (isEqual("x", initial_velocity)) {
				printf("\nInitial Velocity: %G (m/s)\n", answer);
			}
			if (isEqual("x", velocity)) {
				printf("\nVelocity: %G (m/s)\n", answer);
			}
			if (isEqual("x", acceleration)) {
				printf("\nAcceleration: %G (m/s^2)\n", answer);
			}
			if (isEqual("x", time)) {
				printf("\nTime: %G s\n", answer);
			}
		}
		if (op == 25) {
			puts("Enter the unknown value as 'x'");
			puts("Initial Velocity (m/s)?");
			char initial_velocity[dim] = "";
			getCharArray();
			sprintf(initial_velocity, expressionF);
			puts("Velocity (m/s)?");
			char velocity[dim] = "";
			getCharArray();
			sprintf(velocity, expressionF);
			puts("Average Velocity (m/s)?");
			char average_velocity[dim] = "";
			getCharArray();
			sprintf(average_velocity, expressionF);
			char equation[dim] = "";
			sprintf(equation, "%s+%s-2*%s", initial_velocity, velocity, average_velocity);
			double answer = solve(equation);
			if (isEqual("x", average_velocity)) {
				printf("\nAverage Velocity: %G (m/s)\n", answer);
			}
			if (isEqual("x", initial_velocity)) {
				printf("\nInitial Velocity: %G (m/s)\n", answer);
			}
			if (isEqual("x", velocity)) {
				printf("\nVelocity: %G (m/s)\n", answer);
			}
		}
		if (op < 1 || op>25) {
			puts("\n\nError: Incorrect option id.\n\n");
		}
		fflush(NULL);
		printf("\nContinue? (Yes -> 1 / No -> 0)\n");
		op1 = (int)getValue();
	} while (op1 != 0);
	physics = false;
}
