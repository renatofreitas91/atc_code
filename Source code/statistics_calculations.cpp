#include "calc.h"
#include "stdafx.h"

void statisticsCalculations() {
	int op = 0, op1 = 1;
	do {
		fflush(NULL);
		puts("\nWhat to calculate?\n");
		puts("Population Measures (Mean, Variance and Standard Deviation) -> 1");
		puts("Sampling (Sample mean, Sample variance,  Standard Deviation) -> 2");
		puts("\nNumber Sequence\n");
		puts("Arithmetic Sequence -> 3");
		puts("Geometric Sequence -> 4");
		puts("Fibonacci Sequence -> 5");
		puts("\nSample Size\n");
		puts("Find out the sample size -> 6");
		puts("Find out the confidence interval -> 7");
		puts("\nProbability\n");
		puts("Probability of Two Events -> 8");
		puts("Probability of a Normal Distribution -> 9");
		puts("\nPermutation and Combination -> 10\n");
		puts("\nMean, Median, Mode and Range -> 11\n");
		op = (int)getValue();
		puts("");
		if (op == 1) {
			puts("Population?\nInfo: separate values by using '\\'. Example: \"20\\30\\60\"");
			char population[DIM] = "";
			gets_s(population);
			double values[DIM];
			int i = 0, number_of_population = 1;
			for (i = 0; population[i] != '\0'; i++) {
				if (population[i] == '\\') {
					number_of_population++;
				}
			}
			int members = number_of_population;
			i = 0;
			char toValue[DIM] = "";
			int p = 0;
			while (p < members) {
				int b = 0;
				while (population[i] != '\\'&&population[i] != '\0') {
					toValue[b] = population[i];
					b++; i++;
				}
				toValue[b] = '\0';
				solveMath(toValue);
				values[p] = resultR;
				p++;
				sprintf(toValue, "");
				i++;
			}
			int b = 0;
			double summatory = 0;
			for (b = 0; b < number_of_population; b++) {
				summatory = summatory + values[b];
			}
			double mean = summatory / number_of_population;
			printf("\nMean: %s\n", convert2Exponential(mean));
			summatory = 0;
			for (b = 0; b < number_of_population; b++) {
				summatory = summatory + pot(values[b] - mean, 2.0, 1);
			}
			double variance = ((double)1.0 / number_of_population)*summatory;
			printf("\nVariance: %s\n", convert2Exponential(variance));
			double standard_deviation = sqrt(variance);
			printf("\nStandard Deviation: %s\n", convert2Exponential(standard_deviation));
		}
		if (op == 2) {
			puts("Sampling population?\nInfo: separate values by using '\\'. Example: \"20\\30\\60\"");
			char population[DIM] = "";
			gets_s(population);
			double values[DIM];
			int i = 0, number_of_population = 1;
			for (i = 0; population[i] != '\0'; i++) {
				if (population[i] == '\\') {
					number_of_population++;
				}
			}
			int members = number_of_population;
			i = 0;
			char toValue[DIM] = "";
			int p = 0;
			while (p < members) {
				int b = 0;
				while (population[i] != '\\'&&population[i] != '\0') {
					toValue[b] = population[i];
					b++; i++;
				}
				toValue[b] = '\0';
				solveMath(toValue);
				values[p] = resultR;
				p++;
				sprintf(toValue, "");
				i++;
			}
			int b = 0;
			double summatory = 0;
			for (b = 0; b < number_of_population; b++) {
				summatory = summatory + values[b];
			}
			double mean = summatory / number_of_population;
			printf("\nSample mean: %s\n", convert2Exponential(mean));
			summatory = 0;
			for (b = 0; b < number_of_population; b++) {
				summatory = summatory + pot(values[b] - mean, 2.0, 1);
			}
			double variance = (double)1.0 / (number_of_population - 1)*summatory;
			printf("\nSample variance: %s\n", convert2Exponential(variance));
			double standard_deviation = sqrt(variance);
			printf("\nSample standard deviation: %s\n", convert2Exponential(standard_deviation));
		}
		if (op == 3) {
			puts("First number?");
			double first_number = getValue();
			puts("Common difference?");
			double common_difference = getValue();
			puts("The n.th to obtain?");
			int n_th = (int)getValue();
			double aValues[DIM] = { 0, 0 };
			double summation = first_number;
			int b = 0;
			aValues[b] = first_number;
			for (b = 1; b < n_th; b++) {
				aValues[b] = first_number + common_difference * b;
				summation = summation + aValues[b];
			}
			printf("\nsequence: ");
			for (b = 0; b < n_th; b++) {
				printf("%.f, ", aValues[b]);
			}
			b--;
			puts("");
			printf("%dth value: %.f", n_th, aValues[b]);
			puts(" ");
			printf("Result of the sum of all numbers until %dth: %.f", n_th, summation);
			puts(" ");
		}
		if (op == 4) {
			puts("First number?");
			double first_number = getValue();
			puts("Common ratio?");
			double common_ratio = getValue();
			puts("The n.th to obtain?");
			int n_th = (int)getValue();
			double aValues[DIM] = { 0, 0 };
			double summation = first_number;
			int b = 0;
			aValues[b] = first_number;
			for (b = 1; b < n_th; b++) {
				aValues[b] = aValues[b - 1] * common_ratio;
				summation = summation + aValues[b];
			}
			printf("\nsequence: ");
			for (b = 0; b < n_th; b++) {
				printf("%.f, ", aValues[b]);
			}
			b--;
			puts("");
			printf("%dth value: %.f", n_th, aValues[b]);
			puts(" ");
			printf("Result of the sum of all numbers until %dth: %.f", n_th, summation);
			puts(" ");
		}
		if (op == 5) {
			puts("The n.th to obtain?");
			int n_th = (int)getValue();
			double aValues[DIM] = { 1, 1 };
			int b = 0;
			double summation = 2;
			for (b = 2; b < n_th; b++) {
				aValues[b] = aValues[b - 1] + aValues[b - 2];
				summation = summation + aValues[b];
			}
			printf("\nsequence: ");
			for (b = 0; b < n_th; b++) {
				printf("%.f, ", aValues[b]);
			}
			b--;
			puts("");
			printf("%dth value: %.f", n_th, aValues[b]);
			puts(" ");
			printf("Result of the sum of all numbers until %dth: %.f", n_th, summation);
			puts(" ");
		}
		if (op == 6) {
			puts("Confidence Level (%)?");
			double confidence_level = getValue() / 100;
			puts("Confidence Interval (%)?");
			double confidence_interval = getValue() / 100;
			puts("Population Proportion (%)?");
			double population_proportion = getValue() / 100;
			puts("Population Size? Info: Enter \"0\" if the size of population is unlimited.");
			double population_size = getValue();
			double z = confidenceLevelToZscore(confidence_level);
			if (z != -77777) {
				double unlimited_population = (pot(z, 2.0, 1)*population_proportion*(1 - population_proportion)) / pot(confidence_interval, 2.0, 1);
				if (population_size == 0) {
					printf("\nYou will need to measure %s or more samples.\n", convert2Exponential(unlimited_population));
				}
				else {
					double finite_population = unlimited_population / (1 + unlimited_population * (1 / population_size));
					finite_population = ceil(finite_population);
					printf("\nYou will need to measure %.f or more samples.\n", finite_population);
				}
			}
			else {
				puts("\nError: Invalid confidence level.\n");
			}
		}
		if (op == 7) {
			puts("Confidence Level (%)?");
			double confidence_level = getValue() / 100;
			puts("Sample Size?");
			double sample_size = getValue();
			puts("Population Proportion (%)?");
			double population_proportion = getValue() / 100;
			puts("Population Size? Info: Enter \"0\" if the size of population is unlimited.");
			double population_size = getValue();
			double z = confidenceLevelToZscore(confidence_level);
			if (z != -77777) {
				if (population_size == 0) {
					double interval = z * sqrt((population_proportion*(1 - population_proportion)) / sample_size);
					printf("The confidence interval is:  %.2f%% - %.2f%%.", (population_proportion - interval) * 100, (population_proportion + interval) * 100);
				}
				else {
					double interval = z * sqrt(((population_proportion*(1 - population_proportion)) / sample_size)*((population_size - sample_size) / (population_size - 1)));
					printf("The confidence interval is:  %.2f%% - %.2f%%.", (population_proportion - interval) * 100, (population_proportion + interval) * 100);
				}
			}
			else {
				puts("\nError: Invalid confidence level.\n");
			}
		}
		if (op == 8) {
			puts("Probability of event A?");
			double probability_event_a = getValue();
			puts("Probability of event B?");
			double probability_event_b = getValue();
			if (probability_event_a >= 0 && probability_event_a <= 1 && probability_event_b >= 0 && probability_event_b <= 1) {
				puts("");
				double a_complement = 1 - probability_event_a;
				double b_complement = 1 - probability_event_b;
				printf("The probability that event A does not occur is %s\n", convert2Exponential(a_complement));
				printf("The probability that event B does not occur is %s\n", convert2Exponential(b_complement));
				double intersection_a_with_b = probability_event_a * probability_event_b;
				double union_a_with_b = probability_event_a + probability_event_b - intersection_a_with_b;
				double exclusive_or_of_a_and_b = union_a_with_b - 2 * intersection_a_with_b;
				printf("The probability that event A and/or event B occurs is %s\n", convert2Exponential(union_a_with_b));
				printf("The probability that event A and event B both occur is %s\n", convert2Exponential(intersection_a_with_b));
				printf("The probability that either A or event B occurs, but not both is %s\n", convert2Exponential(exclusive_or_of_a_and_b));
			}
			else {
				puts("\nError: The probability of an event needs to be a number between 0 and 1.\n");
			}
		}
		if (op == 9) {
			int i = 0;
			puts("Mean?");
			double mean = getValue();
			puts("Standard Deviation?");
			double standard_deviation = getValue();
			puts("Left Bound?");
			double left_bound = getValue();
			puts("Right Bound?");
			double right_bound = getValue();
			double left_probability = 0.5*(1 + gerror((left_bound - mean) / (standard_deviation*sqrt(2.0))));
			double right_probability = 0.5*(1 + gerror((right_bound - mean) / (standard_deviation*sqrt(2.0))));
			puts("");
			convertComplex2Exponential(left_bound, right_bound);
			printf("The probability between %s and %s is %f\n", respR, respI, right_probability - left_probability);
			printf("The probability outside of %s and %s is 1 - %G = %f\n", respR, respI, (right_probability - left_probability), 1 - (right_probability - left_probability));
			printf("The probability of %s or less (<=%s) is %f\n", respR, respR, left_probability);
			printf("The probability of %s or more (>=%s) is %f\n", respI, respI, 1 - right_probability);
		}
		if (op == 10) {
			puts("Total Amount in a Set?");
			int n = (int)getValue();
			puts("Amount in each Sub-Set?");
			int r = (int)getValue();
			double permutations = fact(n) / fact(n - r);
			double combinations = fact(n) / (fact(r)*fact(n - r));
			printf("Permutations: %.f\n", permutations);
			printf("Combinations: %.f\n", combinations);
		}
		if (op == 11) {
			puts("Population?\nInfo: separate values by using '\\'. Example: \"20\\30\\60\"");
			char population[DIM] = "";
			gets_s(population);
			double values[DIM];
			int i = 0, number_of_population = 1;
			for (i = 0; population[i] != '\0'; i++) {
				if (population[i] == '\\') {
					number_of_population++;
				}
			}
			int members = number_of_population;
			i = 0;
			char toValue[DIM] = "";
			int p = 0;
			while (p < members) {
				int b = 0;
				while (population[i] != '\\'&&population[i] != '\0') {
					toValue[b] = population[i];
					b++; i++;
				}
				toValue[b] = '\0';
				solveMath(toValue);
				values[p] = resultR;
				p++;
				sprintf(toValue, "");
				i++;
			}
			int b = 0;
			double summatory = 0;
			for (b = 0; b < number_of_population; b++) {
				summatory = summatory + values[b];
			}
			double mean = summatory / number_of_population;
			printf("\nMean: %s", convert2Exponential(mean));
			if (number_of_population % 2 == 1) {
				int index = (number_of_population + 1) / 2;
				printf("\nMedian: %s", convert2Exponential(values[index - 1]));
			}
			else {
				int index_1 = number_of_population / 2;
				int index_2 = index_1 + 1;
				double median = (values[index_1 - 1] + values[index_2 - 1]) / 2;
				printf("\nMedian: %s", convert2Exponential(median));
			}
			i = 0;
			int j = 0;
			int count = 0;
			int valuesF[DIM] = { 0 };
			double valuesS[DIM] = { 0 };
			int t = 0;
			while (i < number_of_population) {
				double value = values[i];
				j = 0;
				count = 0;
				while (j < number_of_population) {
					if (value == valuesS[j]) {
						count++;
					}
					j++;
				}
				if (count == 0) {
					j = 0;
					while (j < number_of_population) {
						if (value == values[j]) {
							count++;
						}
						j++;
					}
					valuesF[t] = count;
					valuesS[t] = value;
					t++;
				}
				i++;
			}
			i = 0;
			int max = 0;
			while (i < number_of_population) {
				if (max < valuesF[i]) {
					max = valuesF[i];
				}
				i++;
			}
			printf("\nMode: ");
			i = 0;
			int k = 0;
			while (i < number_of_population) {
				if (max == valuesF[i]) {
					printf("%s ", convert2Exponential(valuesS[i]));
					k++;
				}
				i++;
			}
			if (k > 1) {
				printf("-> each appeared %d times", max);
			}
			else {
				printf("-> appeared %d times", max);
			}
			double smallest = values[0], largest = values[0];
			i = 0;
			while (i < number_of_population) {
				if (values[i] > largest) {
					largest = values[i];
				}
				if (values[i] < smallest) {
					smallest = values[i];
				}
				i++;
			}
			printf("\nRange: %s", convert2Exponential(largest - smallest));
			printf("\nLargest: %s", convert2Exponential(largest));
			printf("\nSmallest: %s", convert2Exponential(smallest));
			printf("\nSum: %s", convert2Exponential(summatory));
			printf("\nCount %d", number_of_population);
		}
		if (op < 1 || op>11) {
			puts("\n\nError: Incorrect option id.\n\n");
		}
		fflush(NULL);
		op1 = -1;
		while (op1 != 0 && op1 != 1) {
			I_O = true;
			printf("\nContinue? (Yes -> 1 / No -> 0)\n");
			op1 = (int)getValue();
		}
	} while (op1 != 0);
}

double confidenceLevelToZscore(double confidence_level) {
	double confidence[12] = { 0.7,0.75,0.8,0.85,0.92,0.95,0.96,0.98,0.99,0.999,0.9999,0.99999 };
	double z[12] = { 1.04,1.15,1.28,1.44,1.75,1.96,2.05,2.33,2.58,3.29,3.89,4.42 };
	double z_score = 0;
	int i = 0;
	while (i < 12 && confidence_level != confidence[i]) {
		i++;
	}
	if (confidence_level == confidence[i]) {
		return z[i];
	}
	else {
		return -77777;
	}
}