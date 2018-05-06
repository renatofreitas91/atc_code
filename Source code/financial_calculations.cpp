#include "stdafx.h"

void financialCalculations() {
	int op = 0, op1 = 1;
	do {
		fflush(NULL);
		puts("\nWhat to calculate?");
		puts("Annual Percentage Yield -> 5");
		puts("Annuity (FV)- Solve for n -> 25");
		puts("Annuity (PV)- Solve for n -> 19");
		puts("Annuity Due Payment - FV -> 42");
		puts("Annuity Due Payment - PV -> 43");
		puts("Annuity Payment (FV) -> 41");
		puts("Annuity Payment (PV) -> 20");
		puts("Annuity Payment Factor - PV -> 37");
		puts("Balloon Balance of a Loan -> 35");
		puts("Compound Interest -> 4");
		puts("Continuous Compounding -> 6");
		puts("Discounted Payback Period -> 18");
		puts("Doubling Time - Simple Interest -> 26");
		puts("Doubling Time -> 27");
		puts("Doubling Time - Continuous Compounding -> 29");
		puts("Equivalent Annual Annuity -> 17");
		puts("Future Value -> 2");
		puts("Future Value of Annuity -> 24");
		puts("Future Value of Annuity Due -> 44");
		puts("Future Value of Growing Annuity -> 38");
		puts("FV of Annuity - Continuous Compounding -> 32");
		puts("FV - Continuous Compounding -> 15");
		puts("Future Value Factor -> 14");
		puts("Geometric Mean Return -> 7");
		puts("Growing Annuity Payment - FV -> 39");
		puts("Growing Annuity Payment - PV -> 40");
		puts("Holding Period Return -> 8");
		puts("Loan Payment -> 34");
		puts("Net Present Value -> 10");
		puts("Payback Period -> 16");
		puts("Payments on a Balloon Loan -> 36");
		puts("Present Value -> 1");
		puts("Present Value Factor -> 9");
		puts("Present Value of Annuity -> 11");
		puts("Present Value Annuity Factor -> 21");
		puts("Present Value of Annuity Due -> 22");
		puts("Present Value of a Growing Annuity -> 23");
		puts("PV - Continuous Compounding -> 12");
		puts("Rule of 72 -> 28");
		puts("Return on Investment -> 31");
		puts("Remaining Balance on Loan -> 33");
		puts("Simple Interest -> 3");
		puts("Solve for Number of Periods - PV & FV -> 13");
		puts("Weighted Average -> 30");
		op = (int)getValue();
		puts(" ");
		if (op == 1) {
			int answer = 0;
			puts("Do you have the Cash Flow at period 1?  (Yes -> 1 / No -> 0)");
			answer = (int)getValue();
			if (answer == 1) {
				puts("Cash Flow at period 1?");
				double c_1 = getValue();
				puts("Rate of return (%)?");
				double return_rate = getValue();
				puts("Number of periods?");
				double number_periods = getValue();
				double den = (1 + (return_rate / 100));
				den = pow(den, number_periods);
				double present_value = c_1 / den;
				printf("\nPresent Value: $%.2f\n", present_value);
			}
			else {
				puts("Do you have the Future Value?  (Yes -> 1 / No -> 0)");
				answer = (int)getValue();
				if (answer == 1) {
					puts("Future Value?");
					double future_value = getValue();
					puts("Rate of return (%)?");
					double return_rate = getValue();
					puts("Number of periods?");
					double number_periods = getValue();
					double den = (1 + (return_rate / 100));
					den = 1 / pow(den, number_periods);
					double present_value = future_value * den;
					printf("\nPresent Value: $%.2f\n", present_value);
				}
				else {
					puts("\n\nError: Can not calculate Present Value.\n\n");
				}
			}
		}
		if (op == 2) {
			int answer = 0;
			puts("Do you have the Cash Flow at period 0?  (Yes -> 1 / No -> 0)");
			answer = (int)getValue();
			if (answer == 1) {
				puts("Cash Flow at period 0?");
				double c_0 = getValue();
				puts("Rate of return (%)?");
				double return_rate = getValue();
				puts("Number of periods?");
				double number_periods = (int)getValue();
				double num = (1 + (return_rate / 100));
				num = pow(num, number_periods);
				double future_value = c_0 * num;
				printf("\nFuture Value: $%.2f\n", future_value);
			}
			else {
				puts("Do you have the Present Value?  (Yes -> 1 / No -> 0)");
				answer = (int)getValue();
				if (answer == 1) {
					puts("Present Value?");
					double present_value = getValue();
					puts("Rate of return (%)?");
					double return_rate = getValue();
					puts("Number of periods?");
					double number_periods = getValue();
					double num = (1 + (return_rate / 100));
					num = pow(num, number_periods);
					double future_value = present_value * num;
					printf("\nFuture Value: $%.2f\n", future_value);
				}
				else {
					puts("\n\nError: Can not calculate Future Value.\n\n");
				}
			}
		}
		if (op == 3) {
			puts("Principal?");
			double principal = getValue();
			puts("Rate (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Time?");
			double time = getValue();
			double simple_interest = principal * rate*time;
			printf("\nSimple Interest: $%.2f\n", simple_interest);
		}
		if (op == 4) {
			puts("Principal (original balance)?");
			double principal = getValue();
			puts("Rate per period (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double compound_interest = principal * (pow((1 + rate), number_periods) - 1);
			printf("\nCompound Interest: $%.2f\n", compound_interest);
		}
		if (op == 5) {
			puts("Stated annual interest rate?");
			double rate = getValue();
			rate = rate / 100;
			puts("Number of times compounded?");
			double number_times = getValue();
			double annual_percentage_yield = pow((1 + rate / number_times), number_times) - 1;
			printf("\nAnnual Percentage Yield: %.2f%%\n", annual_percentage_yield * 100);
		}
		if (op == 6) {
			puts("Principal (original balance)?");
			double principal = getValue();
			puts("Rate per period (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("time (number of periods)?");
			double number_times = getValue();
			double continuous_compounding = principal * pow(M_E, rate*number_times);
			printf("\nContinuous Compounding: $%.2f\n", continuous_compounding);
		}
		if (op == 7) {
			puts("Rate of return (%)?\nInfo: separate rates by using '\\'. Example: \"2\\4\\3\"");
			char return_rates[DIM] = "";
			gets_s(return_rates);
			double rates[DIM];
			int i = 0, number_periods = 1;
			for (i = 0; return_rates[i] != '\0'; i++) {
				if (return_rates[i] == '\\') {
					number_periods++;
				}
			}
			int members = number_periods;
			i = 0;
			char toValue[DIM] = "";
			while (members >= 0) {
				int b = 0;
				while (return_rates[i] != '\\'&&return_rates[i] != '\0') {
					toValue[b] = return_rates[i];
					b++; i++;
				}
				toValue[b] = '\0';
				calcNow(toValue, 0, 0);
				rates[members] = resultR / 100;
				members--;
				sprintf(toValue, "");
				i++;
			}
			members = number_periods;
			double base = 1;
			while (members > 0) {
				base = base * (1 + rates[members]);
				members--;
			}
			double geometric_return = pot(base, (double)1 / number_periods, 1) - 1;
			printf("\nGeometric Mean Return: %.2f%%\n", geometric_return * 100);
		}
		if (op == 8) {
			puts("Rate per return (%)?\nInfo: separate rates by using '\\'. Example: \"2\\4\\3\"");
			char return_rates[DIM] = "";
			gets_s(return_rates);
			double rates[DIM];
			int i = 0, number_periods = 1;
			for (i = 0; return_rates[i] != '\0'; i++) {
				if (return_rates[i] == '\\') {
					number_periods++;
				}
			}
			int members = number_periods;
			i = 0;
			char toValue[DIM] = "";
			while (members >= 0) {
				int b = 0;
				while (return_rates[i] != '\\'&&return_rates[i] != '\0') {
					toValue[b] = return_rates[i];
					b++; i++;
				}
				toValue[b] = '\0';
				calcNow(toValue, 0, 0);
				rates[members] = resultR / 100;
				members--;
				sprintf(toValue, "");
				i++;
			}
			members = number_periods;
			double base = 1;
			while (members > 0) {
				base = base * (1 + rates[members]);
				members--;
			}
			double holding_return = base - 1;
			printf("\nHolding Period Return: %.2f%%\n", holding_return * 100);
		}
		if (op == 9) {
			puts("Rate of return (%)?");
			double return_rate = getValue();
			puts("Number of periods?");
			double number_periods = getValue();
			double den = (1 + (return_rate / 100));
			den = pow(den, number_periods);
			double present_value_factor = 1 / den;
			printf("\nPresent Value Factor: %.2f\n", present_value_factor);
		}
		if (op == 10) {
			puts("Initial Investment?");
			double initial_investment = getValue();
			puts("Discount Rate (%)?");
			double discount_rate = getValue();
			discount_rate = discount_rate / 100;
			puts("Cash Flows?\nInfo: separate Cash Flows by using '\\'. Example: \"200\\400\\300\"");
			char cash_flows[DIM] = "";
			gets_s(cash_flows);
			double cashFlow[DIM];
			int i = 0, number_periods = 1;
			for (i = 0; cash_flows[i] != '\0'; i++) {
				if (cash_flows[i] == '\\') {
					number_periods++;
				}
			}
			int members = number_periods;
			i = 0;
			char toValue[DIM] = "";
			int p = 0;
			while (p < members) {
				int b = 0;
				while (cash_flows[i] != '\\'&&cash_flows[i] != '\0') {
					toValue[b] = cash_flows[i];
					b++; i++;
				}
				toValue[b] = '\0';
				calcNow(toValue, 0, 0);
				cashFlow[p] = resultR;
				p++;
				sprintf(toValue, "");
				i++;
			}
			members = number_periods;
			int k = 1;
			double baseCF = 0;
			while (k <= members) {
				baseCF = baseCF + cashFlow[k - 1] / pow(1 + discount_rate, k);
				k++;
			}
			double net_present_value = baseCF - initial_investment;
			printf("\nNet Present Value: $%.2f\n", net_present_value);
		}
		if (op == 11) {
			puts("Periodic Payment?");
			double periodic_payment = getValue();
			puts("Rate per period (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double present_value_annuity = periodic_payment * ((1 - pow(1 + rate, number_periods*-1)) / rate);
			printf("\nPresent Value of Annuity: $%.2f\n", present_value_annuity);
		}
		if (op == 12) {
			puts("Cash Flow?");
			double cash_flow = getValue();
			puts("Rate (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Time?");
			double time = getValue();
			double pv_continuous_compounding = cash_flow / pow(M_E, rate*time);
			printf("\nPV - Continuous Compounding: $%.2f\n", pv_continuous_compounding);
		}
		if (op == 13) {
			puts("Future Value?");
			double future_value = getValue();
			puts("Present Value?");
			double present_value = getValue();
			puts("Rate per period (%)?");
			double rate = getValue();
			rate = rate / 100;
			double number_periods = ln(future_value / present_value) / ln(1 + rate);
			printf("\nNumber of Periods: %.2f\n", number_periods);
		}
		if (op == 14) {
			puts("Rate per period (%)?");
			double rate_per_period = getValue();
			puts("Number of periods?");
			double number_periods = getValue();
			double future_value_factor = pow(1 + rate_per_period / 100, number_periods);
			printf("\nFuture Value Factor: %.2f\n", future_value_factor);
		}
		if (op == 15) {
			puts("Present Value?");
			double present_value = getValue();
			puts("Rate (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Time?");
			double time = getValue();
			double fv_continuous_compounding = present_value * pow(M_E, rate*time);
			printf("\nFV - Continuous Compounding: $%.2f\n", fv_continuous_compounding);
		}
		if (op == 16) {
			puts("Initial Investment?");
			double initial_investment = getValue();
			puts("Periodic Cash Flow?");
			double periodic_cash_flow = getValue();
			double payback_period = initial_investment / periodic_cash_flow;
			printf("\nPayback Period: %.2f\n", payback_period);
		}
		if (op == 17) {
			puts("Net Present Value?");
			double net_present_value = getValue();
			puts("Rate per period (%)?");
			double rate_per_period = getValue();
			rate_per_period = rate_per_period / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double equivalent_annual_annuity = (rate_per_period*net_present_value) / (1 - pow(1 + rate_per_period, -1 * number_periods));
			printf("\nEquivalent Annual Annuity: %.2f\n", equivalent_annual_annuity);
		}
		if (op == 18) {
			puts("Initial Investment (Outflow)?");
			double initial_investment = getValue();
			puts("Rate (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Periodic Cash Flow?");
			double periodic_cash_flow = getValue();
			double discounted_payback_period = ln(1 / (1 - (initial_investment*rate) / periodic_cash_flow)) / ln(1 + rate);
			printf("\nDiscounted Payback Period: %.2f\n", discounted_payback_period);
		}
		if (op == 19) {
			puts("Present Value (of Annuity)?");
			double present_value_annuity = getValue();
			puts("Rate (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Payment/Cash Flows?");
			double payment_cash_flows = getValue();
			double number_periods = ln(pow(1 - (present_value_annuity*rate) / payment_cash_flows, -1)) / ln(1 + rate);
			printf("\nAnnuity (PV)- Solve for n: %.2f\n", number_periods);
		}
		if (op == 20) {
			puts("Present Value?");
			double present_value = getValue();
			puts("Rate (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double annuity_payment_pv = (rate*present_value) / (1 - pow(1 + rate, -1 * number_periods));
			printf("\nAnnuity Payment (PV): $%.2f\n", annuity_payment_pv);
		}
		if (op == 21) {
			puts("Rate per period (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double annuity_pv_factor = (1 - pow(1 + rate, -1 * number_periods)) / rate;
			printf("\nPresent Value Annuity Factor: %.2f\n", annuity_pv_factor);
		}
		if (op == 22) {
			puts("Periodic Payment?");
			double periodic_payment = getValue();
			puts("Rate per period (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double pv_annuity_due = periodic_payment + periodic_payment * ((1 - pow(1 + rate, -1 * (number_periods - 1))) / rate);
			printf("\nPresent Value of Annuity Due: $%.2f\n", pv_annuity_due);
		}
		if (op == 23) {
			puts("First Payment?");
			double first_payment = getValue();
			puts("Rate per period (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Growth rate (%)?");
			double growth_rate = getValue();
			growth_rate = growth_rate / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double pv_growing_annuity = (first_payment / (rate - growth_rate))*(1 - pow((1 + growth_rate) / (1 + rate), number_periods));
			printf("\nPresent Value of a Growing Annuity: $%.2f\n", pv_growing_annuity);
		}
		if (op == 24) {
			puts("Periodic Payment?");
			double periodic_payment = getValue();
			puts("Rate per period (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double fv_value_of_annuity = periodic_payment * ((pow(1 + rate, number_periods) - 1) / rate);
			printf("\nFuture Value of Annuity: $%.2f\n", fv_value_of_annuity);
		}
		if (op == 25) {
			puts("Future Value (of Annuity)?");
			double future_value_annuity = getValue();
			puts("Rate (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Payment/Cash Flows?");
			double payment_cash_flows = getValue();
			double number_periods = ln(1 + (future_value_annuity*rate) / payment_cash_flows) / ln(1 + rate);
			printf("\nAnnuity (FV)- Solve for n: %.2f\n", number_periods);
		}
		if (op == 26) {
			puts("Rate (%)?");
			double rate = getValue();
			rate = rate / 100;
			double doubling_time_without_compounding = 1 / rate;
			printf("\nDoubling Time - Simple Interest: %.2f\n", doubling_time_without_compounding);
		}
		if (op == 27) {
			puts("Rate of return (%)?");
			double rate = getValue();
			rate = rate / 100;
			double doubling_time = log10(2) / log10(1 + rate);
			printf("\nDoubling Time: %.2f\n", doubling_time);
		}
		if (op == 28) {
			puts("Rate expressed as a whole number (%)?");
			double rate = getValue();
			double rule_of_72 = 72 / rate;
			printf("\nRule of 72: %.2f\n", rule_of_72);
		}
		if (op == 29) {
			puts("Rate (%)?");
			double rate = getValue();
			rate = rate / 100;
			double dt_continuos_compounding = ln(2) / rate;
			printf("\nDoubling Time - Continuous Compounding: %.2f\n", dt_continuos_compounding);
		}
		if (op == 30) {
			puts("Relative weight (%)?\nInfo: separate relative weights by using '\\'. Example: \"2\\4\\3\"");
			char relative_weight[DIM] = "";
			gets_s(relative_weight);
			double w[DIM];
			int i = 0, number_periods = 1;
			for (i = 0; relative_weight[i] != '\0'; i++) {
				if (relative_weight[i] == '\\') {
					number_periods++;
				}
			}
			int members = number_periods;
			i = 0;
			char toValue[DIM] = "";
			while (members >= 0) {
				int b = 0;
				while (relative_weight[i] != '\\'&&relative_weight[i] != '\0') {
					toValue[b] = relative_weight[i];
					b++; i++;
				}
				toValue[b] = '\0';
				calcNow(toValue, 0, 0);
				w[members] = resultR / 100;
				members--;
				sprintf(toValue, "");
				i++;
			}
			puts("Values?\nInfo: separate values by using '\\'. Example: \"2\\4\\3\"");
			char values[DIM] = "";
			gets_s(values);
			double x[DIM];
			i = 0; number_periods = 1;
			for (i = 0; values[i] != '\0'; i++) {
				if (values[i] == '\\') {
					number_periods++;
				}
			}
			members = number_periods;
			i = 0;
			sprintf(toValue, "");
			while (members >= 0) {
				int b = 0;
				while (values[i] != '\\'&&values[i] != '\0') {
					toValue[b] = values[i];
					b++; i++;
				}
				toValue[b] = '\0';
				calcNow(toValue, 0, 0);
				x[members] = resultR;
				members--;
				sprintf(toValue, "");
				i++;
			}
			double weighted_average = 0;
			i = 0;
			while (i <= number_periods) {
				weighted_average = weighted_average + x[i] * w[i];
				i++;
			}
			printf("\nWeighted Average: %.2f%%\n", weighted_average * 100);
		}
		if (op == 31) {
			puts("Earnings?");
			double earnings = getValue();
			puts("Initial Investment?");
			double initial_investment = getValue();
			double return_on_investment = (earnings - initial_investment) / initial_investment;
			printf("\nReturn on Investment: %.2f%%\n", return_on_investment * 100);
		}
		if (op == 32) {
			puts("Cash Flow?");
			double cash_flow = getValue();
			puts("Rate (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Time?");
			double time = getValue();
			double fv_annuity_continuos_compounding = cash_flow * ((pow(M_E, rate*time) - 1) / (pow(M_E, rate) - 1));
			printf("\nFV of Annuity - Continuous Compounding: $%.2f\n", fv_annuity_continuos_compounding);
		}
		if (op == 33) {
			puts("Present Value (Original Balance)?");
			double present_value = getValue();
			puts("Payment?");
			double payment = getValue();
			puts("Rate per payment (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Number of payments?");
			double number_payments = getValue();
			double fv_remaining_balance = present_value * pow(1 + rate, number_payments) - payment * ((pow(1 + rate, number_payments) - 1) / rate);
			printf("\nRemaining Balance on Loan: $%.2f\n", fv_remaining_balance);
		}
		if (op == 34) {
			puts("Present Value?");
			double present_value = getValue();
			puts("Rate per period (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double loan_payment = (rate*present_value) / (1 - pow(1 + rate, -1 * number_periods));
			printf("\nLoan Payment: $%.2f\n", loan_payment);
		}
		if (op == 35) {
			puts("Present Value (Original Balance)?");
			double present_value = getValue();
			puts("Payment?");
			double payment = getValue();
			puts("Rate per payment (%)?");
			double rate = getValue();
			rate = rate / 100;
			puts("Number of payments?");
			double number_payments = getValue();
			double fv_balloon_balance = present_value * pow(1 + rate, number_payments) - payment * ((pow(1 + rate, number_payments) - 1) / rate);
			printf("\nBalloon Balance of a Loan: $%.2f\n", fv_balloon_balance);
		}
		if (op == 36) {
			puts("Present Value?");
			double present_value = getValue();
			puts("Balloon Amount?");
			double balloon_amount = getValue();
			puts("Rate per period (%)?");
			double rate = getValue() / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double payment_balloon_loan = (present_value - balloon_amount / pow(1 + rate, number_periods))*rate / (1 - pow(1 + rate, -1 * number_periods));
			printf("\nPayments on a Balloon Loan: $%.2f\n", payment_balloon_loan);
		}
		if (op == 37) {
			puts("Rate per period (%)?");
			double rate = getValue() / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double payment_factor = rate / (1 - pow(1 + rate, -1 * number_periods));
			printf("\nAnnuity Payment Factor - PV: %.2f\n", payment_factor);
		}
		if (op == 38) {
			puts("First Payment?");
			double first_payment = getValue();
			puts("Rate per period (%)?");
			double rate = getValue() / 100;
			puts("Growth rate (%)?");
			double growth_rate = getValue() / 100;
			puts("Number of periods");
			double number_periods = getValue();
			double fv_growing_annuity = first_payment * ((pow(1 + rate, number_periods) - pow(1 + growth_rate, number_periods)) / (rate - growth_rate));
			printf("\nFuture Value of Growing Annuity: $%.2f\n", fv_growing_annuity);
		}
		if (op == 39) {
			puts("Future Value?");
			double future_value = getValue();
			puts("Rate per period (%)?");
			double rate = getValue() / 100;
			puts("Growth rate (%)?");
			double growth_rate = getValue() / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double growing_annuity_payment_fv = future_value * ((rate - growth_rate) / (pow(1 + rate, number_periods) - pow(1 + growth_rate, number_periods)));
			printf("\nGrowing Annuity Payment - FV: $%.2f\n", growing_annuity_payment_fv);
		}
		if (op == 40) {
			puts("Present Value?");
			double present_value = getValue();
			puts("Rate per period (%)?");
			double rate = getValue() / 100;
			puts("Growth rate (%)?");
			double growth_rate = getValue() / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double initial_payment = present_value * ((rate - growth_rate) / (1 - pow((1 + growth_rate) / (1 + rate), number_periods)));
			printf("\nGrowing Annuity Payment - PV: $%.2f\n", initial_payment);
		}
		if (op == 41) {
			puts("Future Value?");
			double future_value = getValue();
			puts("Rate per period (%)?");
			double rate = getValue() / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double payment = (future_value*rate) / (pow(1 + rate, number_periods) - 1);
			printf("\nAnnuity Payment - FV: $%.2f\n", payment);
		}
		if (op == 42) {
			puts("Future Value?");
			double future_value = getValue();
			puts("Rate per period (%)?");
			double rate = getValue() / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double payment = future_value * (rate / (pow(1 + rate, number_periods) - 1))*(1 / (1 + rate));
			printf("\nAnnuity Due Payment - FV: $%.2f\n", payment);
		}
		if (op == 43) {
			puts("Present Value?");
			double present_value = getValue();
			puts("Rate per period (%)?");
			double rate = getValue() / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double payment = present_value * (rate / (1 - pow(1 + rate, -1 * number_periods)))*(1 / (1 + rate));
			printf("\nAnnuity Due Payment - PV: $%.2f\n", payment);
		}
		if (op == 44) {
			puts("Periodic Payment?");
			double periodic_payment = getValue();
			puts("Rate per period (%)?");
			double rate = getValue() / 100;
			puts("Number of periods?");
			double number_periods = getValue();
			double fv_annuity_due = (1 + rate)*periodic_payment*((pow(1 + rate, number_periods) - 1) / rate);
			printf("\nFuture Value of Annuity Due: $%.2f\n", fv_annuity_due);
		}
		if (op < 1 || op>44) {
			puts("\n\nError: Incorrect option id.\n\n");
		}
		fflush(NULL);
		printf("\nContinue? (Yes -> 1 / No -> 0)\n");
		op1 = (int)getValue();
	} while (op1 != 0);
}