#include "stdafx.h"

void financialCalculations() {
	int op = 0, op1 = 1;
	do {
		fflush(NULL);
		puts("\nWhat to calculate?");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Annual Percentage Yield -> 5\t\t\tAnnuity (FV)- Solve for n -> 25\t\tAnnuity (PV)- Solve for n -> 19");
		puts("Annuity Due Payment - FV -> 42\t\t\tAnnuity Due Payment - PV -> 43\t\tAnnuity Payment (FV) -> 41");
		puts("Annuity Payment (PV) -> 20\t\t\tAnnuity Payment Factor - PV -> 37\tAsset to Sales Ratio -> 45");
		puts("Asset Turnover Ratio -> 46\t\t\tAverage Collection Period -> 47");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Balloon Balance of a Loan -> 35\t\t\tBid Ask Spread -> 48\t\t\tBond Equivalent Yield -> 49");
		puts("Book Value per Share -> 50");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Capital Asset Pricing Model -> 51\t\tCapital Gains Yield -> 52\t\tCompound Interest -> 4");
		puts("Continuous Compounding -> 6\t\t\tContribution Margin -> 53\t\tCurrent Ratio -> 54");
		puts("Current Yield -> 55");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Days in Inventory -> 56\t\t\t\tDebt Coverage Ratio -> 57\t\tDebt Ratio -> 58");
		puts("Debt to Equity Ratio (D/E) -> 59\t\tDebt to Income Ratio -> 60\t\tDiluted Earnings per Share -> 61");
		puts("Discounted Payback Period -> 18\t\t\tDividend Payout Ratio -> 62\t\tDividend Yield (Stock) -> 63");
		puts("Dividends Per Share -> 64\t\t\tDoubling Time -> 27\t\t\tDoubling Time - Continuous Compounding -> 29");
		puts("Doubling Time - Simple Interest -> 26");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Earnings Per Share -> 65\t\t\tEquity Multiplier -> 66\t\t\tEquivalent Annual Annuity -> 17");
		puts("Estimated Earnings -> 67");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Free Cash Flow to Equity -> 68\t\t\tFree Cash Flow to Firm (FCFF) -> 69\tFuture Value -> 2");
		puts("Future Value of Annuity -> 24\t\t\tFuture Value of Annuity Due -> 44\tFuture Value of Growing Annuity -> 38");
		puts("FV of Annuity - Continuous Compounding -> 32\tFV - Continuous Compounding -> 15\tFuture Value Factor -> 14");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Geometric Mean Return -> 7\t\t\tGrowing Annuity Payment - FV -> 39\tGrowing Annuity Payment - PV -> 40");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Holding Period Return -> 8");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Interest Coverage Ratio -> 71\t\t\tInventory Turnover Ratio -> 72");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Loan Payment -> 34\t\t\t\tLoan to Deposit Ratio -> 73\t\tLoan to Value Ratio -> 74");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Net Asset Value -> 75\t\t\t\tNet Present Value -> 10\t\t\tNet Profit Margin -> 76");
		puts("Net Working Capital -> 77");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Payback Period -> 16\t\t\t\tPayments on a Balloon Loan -> 36\tPresent Value -> 1");
		puts("Present Value Factor -> 9\t\t\tPresent Value of Annuity -> 11\t\tPresent Value Annuity Factor -> 21");
		puts("Present Value of Annuity Due -> 22\t\tPV of a Growing Annuity -> 23\t\tPV of Growing Perpetuity -> 70");
		puts("PV - Continuous Compounding -> 12\t\tPV of Perpetuity -> 78\t\t\tPreferred Stock -> 79");
		puts("Price to Book Value -> 80\t\t\tPrice to Earnings Ratio -> 81\t\tPrice to Sales Ratio -> 82");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Quick Ratio -> 83");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Rate of Inflation -> 84\t\t\t\tReal Rate of Return -> 85\t\tReceivables Turnover Ratio -> 86");
		puts("Retention Ratio -> 87\t\t\t\tReturn on Assets -> 88\t\t\tReturn on Equity (ROE) -> 89");
		puts("Return on Investment -> 31\t\t\tRemaining Balance on Loan -> 33\t\tRisk Premium -> 90");
		puts("Rule of 72 -> 28");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Solve for Number of Periods - PV & FV -> 13\tSimple Interest -> 3\t\t\tStock - PV with Constant Growth -> 91");
		puts("Stock - PV with Zero Growth -> 92");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Tax Equivalent Yield -> 93\t\t\tTotal Stock Return -> 94");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Weighted Average -> 30");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Yield to Maturity -> 95");
		puts("_________________________________________________________________________________________________________________________________________");
		puts("Zero Coupon Bond Value -> 96\t\t\tZero Coupon Bond Effective Yield -> 97");
		puts("_________________________________________________________________________________________________________________________________________");
		puts(" ");
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
			printf("\nEquivalent Annual Annuity: $%.2f\n", equivalent_annual_annuity);
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
		if (op == 45) {
			puts("Total Assets?");
			double total_assets = getValue();
			puts("Sales Revenue?");
			double sales_revenue = getValue();
			double asset_to_sales = total_assets / sales_revenue;
			printf("\nAsset to Sales Ratio: %G\n", asset_to_sales);
		}
		if (op == 46) {
			puts("Sales Revenue?");
			double sales_revenue = getValue();
			puts("Total Assets?");
			double total_assets = getValue();
			double asset_turnover = sales_revenue / total_assets;
			printf("\nAsset Turnover Ratio: %G\n", asset_turnover);
		}
		if (op == 47) {
			puts("Receivables Turnover?");
			double receivables_turnover = getValue();
			double avg_collection_period = 365 / receivables_turnover;
			printf("\nAverage Collection Period: %G\n", avg_collection_period);
		}
		if (op == 48) {
			puts("Ask Price?");
			double ask_price = getValue();
			puts("Bid Price?");
			double bid_price = getValue();
			double bid_ask_spread = ask_price - bid_price;
			printf("\nBid-Ask Spread: $%.2f\n", bid_ask_spread);
		}
		if (op == 49) {
			puts("Face Value?");
			double face_value = getValue();
			puts("Price?");
			double price = getValue();
			puts("Days to maturity?");
			double d = getValue();
			double bond_equivalent_yield = ((face_value - price) / price)*(365 / d);
			printf("\nBond Equivalent Yield: %.3f%%\n", bond_equivalent_yield * 100);
		}
		if (op == 50) {
			puts("Total Common Stockholder's Equity?");
			double total_common_stockholder_equity = getValue();
			puts("Number of Common Shares?");
			double number_common_shares = getValue();
			double book_value_per_share = total_common_stockholder_equity / number_common_shares;
			printf("\nBook Value per Share: $%.3f\n", book_value_per_share);
		}
		if (op == 51) {
			puts("Risk free rate (%)?");
			double risk_free_rate = getValue() / 100;
			puts("Beta?");
			double beta = getValue();
			puts("Return on the market (%)?");
			double return_market = getValue() / 100;
			double capm = risk_free_rate + beta * (return_market - risk_free_rate);
			printf("\nCapital Asset Pricing Model: %.3f%%\n", capm * 100);
		}
		if (op == 52) {
			puts("Initial Stock Price?");
			double initial_stock_price = getValue();
			puts("Stock Price after 1st period?");
			double stock_price_after_1st_period = getValue();
			double capital_gains_yield = (stock_price_after_1st_period - initial_stock_price) / initial_stock_price;
			printf("\nCapital Gains Yield: %.3f%%\n", capital_gains_yield * 100);
		}
		if (op == 53) {
			puts("Price per Product?");
			double price_per_product = getValue();
			puts("Variable Cost per Product?");
			double variable_cost_per_product = getValue();
			double contribution_margin = price_per_product - variable_cost_per_product;
			printf("\nContribution Margin: $%.2f\n", contribution_margin);
		}
		if (op == 54) {
			puts("Current Assets?");
			double current_assets = getValue();
			puts("Current Liabilities?");
			double current_liabilities = getValue();
			double current_ratio = current_assets / current_liabilities;
			printf("\nCurrent Ratio: %G\n", current_ratio);
		}
		if (op == 55) {
			puts("Annual Coupons?");
			double annual_coupons = getValue();
			puts("Current Bond Price?");
			double current_bond_price = getValue();
			double current_yield = annual_coupons / current_bond_price;
			printf("\nCurrent Yield: %.3f%%\n", current_yield * 100);
		}
		if (op == 56) {
			puts("Inventory Turnover?");
			double inventory_turnover = getValue();
			double inventory_days = 365 / inventory_turnover;
			printf("\nDays in Inventory: %G\n", inventory_days);
		}
		if (op == 57) {
			puts("Net Operation Income?");
			double net_operation_income = getValue();
			puts("Debt Service?");
			double debt_service = getValue();
			double debt_coverage_ratio = net_operation_income / debt_service;
			printf("\nDebt Coverage Ratio: $%.3f\n", debt_coverage_ratio);
		}
		if (op == 58) {
			puts("Total Liabilities?");
			double total_liabilities = getValue();
			puts("Total Assets?");
			double total_assets = getValue();
			double debt_ratio = total_liabilities / total_assets;
			printf("\nDebt Ratio: %.4f\n", debt_ratio);
		}
		if (op == 59) {
			puts("Total Liabilities?");
			double total_liabilities = getValue();
			puts("Total Equity?");
			double total_equity = getValue();
			double debt_to_equity = total_liabilities / total_equity;
			printf("\nDebt to Equity Ratio (D/E): %.4f\n", debt_to_equity);
		}
		if (op == 60) {
			puts("Monthly Debt Payments?");
			double monthly_debt_payments = getValue();
			puts("Gross Monthly Income?");
			double gross_monthly_income = getValue();
			double debt_to_income = monthly_debt_payments / gross_monthly_income;
			printf("\nDebt to Income Ratio: %.2f%%\n", debt_to_income * 100);
		}
		if (op == 61) {
			puts("Net Income?");
			double net_income = getValue();
			puts("Average Shares?");
			double average_shares = getValue();
			puts("Other Convertible Instruments?");
			double other_convertible_instruments = getValue();
			double diluted_eps = net_income / (average_shares + other_convertible_instruments);
			printf("\nDiluted Earnings per Share: $%.2f\n", diluted_eps);
		}
		if (op == 62) {
			puts("Dividends?");
			double dividends = getValue();
			puts("Net Income?");
			double net_income = getValue();
			double dividend_payout_ratio = dividends / net_income;
			printf("\nDividend Payout Ratio: %.3f%%\n", dividend_payout_ratio * 100);
		}
		if (op == 63) {
			puts("Dividends for the period?");
			double dividends_for_the_period = getValue();
			puts("Initial Price for the Period?");
			double initial_price_for_the_period = getValue();
			double dividend_yield = dividends_for_the_period / initial_price_for_the_period;
			printf("\nDividend Yield (Stock): %.3f%%\n", dividend_yield * 100);
		}
		if (op == 64) {
			puts("Dividends?");
			double dividends = getValue();
			puts("Number of Shares?");
			double number_of_shares = getValue();
			double dps = dividends / number_of_shares;
			printf("\nDividends Per Share: $%.2f\n", dps);
		}
		if (op == 65) {
			puts("Net Income?");
			double net_income = getValue();
			puts("Weighted Average Outstanding Shares?");
			double weighted_avg_outstanding_shares = getValue();
			double eps = net_income / weighted_avg_outstanding_shares;
			printf("\nEarnings Per Share: $%.2f\n", eps);
		}
		if (op == 66) {
			puts("Total Assets?");
			double total_assets = getValue();
			puts("Stockholder's Equity?");
			double stockholders_equity = getValue();
			double equity_multiplier = total_assets / stockholders_equity;
			printf("\nEquity Multiplier: %.3f\n", equity_multiplier);
		}
		if (op == 67) {
			puts("Projected Sales?");
			double projected_sales = getValue();
			puts("Projected Net Profit Margin (%)?");
			double projected_net_profit_margin = getValue() / 100;
			double estimated_earnings = projected_sales * projected_net_profit_margin;
			printf("\nEstimated Earnings: $%.2f\n", estimated_earnings);
		}
		if (op == 68) {
			puts("Net Income?");
			double net_income = getValue();
			puts("Capital Expenditures?");
			double capital_expenditures = getValue();
			puts("Change in Working Capital?");
			double change_in_working_capital = getValue();
			puts("Net Borrowing?");
			double net_borrowing = getValue();
			double fcfe = net_income - capital_expenditures - change_in_working_capital + net_borrowing;
			printf("\nFree Cash Flow to Equity: $%.2f\n", fcfe);
		}
		if (op == 69) {
			puts("EBIT?");
			double ebit = getValue();
			puts("Tax Rate (%)?");
			double tax_rate = getValue() / 100;
			puts("Capital Expenditures?");
			double capital_expenditures = getValue();
			puts("Change in Working Capital?");
			double change_in_working_capital = getValue();
			double fcff = ebit * (1 - tax_rate) - capital_expenditures - change_in_working_capital;
			printf("\nFree Cash Flow to Firm (FCFF): $%.2f\n", fcff);
		}
		if (op == 70) {
			puts("Dividend or Coupon at period 1?");
			double dividend = getValue();
			puts("Discount rate (%)?");
			double discount_rate = getValue() / 100;
			puts("Growth rate (%)?");
			double growth_rate = getValue() / 100;
			double pv_of_growing_perpetuity = dividend / (discount_rate - growth_rate);
			printf("\nPresent Value of Growing Perpetuity: $%.2f\n", pv_of_growing_perpetuity);
		}
		if (op == 71) {
			puts("EBIT?");
			double ebit = getValue();
			puts("Interest Expense?");
			double interest_expense = getValue();
			double interest_coverage_ratio = ebit / interest_expense;
			printf("\nInterest Coverage Ratio: %.2f\n", interest_coverage_ratio);
		}
		if (op == 72) {
			puts("Sales?");
			double sales = getValue();
			puts("Inventory?");
			double inventory = getValue();
			double inventory_turnover = sales / inventory;
			printf("\nInventory Turnover Ratio: %.2f\n", inventory_turnover);
		}
		if (op == 73) {
			puts("Loans?");
			double loans = getValue();
			puts("Deposits?");
			double deposits = getValue();
			double loan_to_deposit_ratio = loans / deposits;
			printf("\nLoan to Deposit Ratio: %.2f%%\n", loan_to_deposit_ratio * 100);
		}
		if (op == 74) {
			puts("Loan Amount?");
			double loan_amount = getValue();
			puts("Value of Collateral?");
			double value_of_collateral = getValue();
			double ltv_ratio = loan_amount / value_of_collateral;
			printf("\nLoan to Value Ratio: %.2f%%\n", ltv_ratio * 100);
		}
		if (op == 75) {
			puts("Fund Assets?");
			double fund_assets = getValue();
			puts("Fund Liabilities?");
			double fund_liabilities = getValue();
			puts("Outstanding Shares?");
			double outstanding_shares = getValue();
			double nav = (fund_assets - fund_liabilities) / outstanding_shares;
			printf("\nNet Asset Value: $%.2f\n", nav);
		}
		if (op == 76) {
			puts("Net Income?");
			double net_income = getValue();
			puts("Sales Revenue?");
			double sales_revenue = getValue();
			double net_profit_margin = net_income / sales_revenue;
			printf("\nNet Profit Margin: %.2f%%\n", net_profit_margin * 100);
		}
		if (op == 77) {
			puts("Current Assets?");
			double current_assets = getValue();
			puts("Current Liabilities?");
			double current_liabilities = getValue();
			double net_working_capital = current_assets - current_liabilities;
			printf("\nNet Working Capital: $%.2f\n", net_working_capital);
		}
		if (op == 78) {
			puts("Dividend or Coupon per period?");
			double dividend = getValue();
			puts("Discount rate (%)?");
			double discount_rate = getValue() / 100;
			double pv_of_perpetuity = dividend / discount_rate;
			printf("\nPV of Perpetuity: $%.2f\n", pv_of_perpetuity);
		}
		if (op == 79) {
			puts("Dividend?");
			double dividend = getValue();
			puts("Discount rate (%)?");
			double discount_rate = getValue() / 100;
			double preferred_stock_value = dividend / discount_rate;
			printf("\nPreferred Stock: $%.2f\n", preferred_stock_value);
		}
		if (op == 80) {
			puts("Market Price per Share?");
			double market_price_per_share = getValue();
			puts("Book Value per Share?");
			double book_value_per_share = getValue();
			double price_to_book_value = market_price_per_share / book_value_per_share;
			printf("\nPrice to Book Value: %.3f\n", price_to_book_value);
		}
		if (op == 81) {
			puts("Price per Share?");
			double price_per_share = getValue();
			puts("Earnings per Share?");
			double earnings_per_share = getValue();
			double price_to_earning_ratio = price_per_share / earnings_per_share;
			printf("\nPrice to Earnings Ratio: %.3f\n", price_to_earning_ratio);
		}
		if (op == 82) {
			puts("Share Price?");
			double share_price = getValue();
			puts("Sales Per Share?");
			double sales_per_share = getValue();
			double price_to_sales_ratio = share_price / sales_per_share;
			printf("\nPrice to Sales Ratio: %.3f\n", price_to_sales_ratio);
		}
		if (op == 83) {
			puts("Quick Assets?");
			double quick_assets = getValue();
			puts("Current Liabilities?");
			double current_liabilities = getValue();
			double quick_ratio = quick_assets / current_liabilities;
			printf("\nQuick Ratio: %.3f\n", quick_ratio);
		}
		if (op == 84) {
			puts("Ending CPI?");
			double ending_cpi = getValue();
			puts("Initial CPI?");
			double initial_cpi = getValue();
			double rate_of_inflation = (ending_cpi - initial_cpi) / initial_cpi;
			printf("\nRate of Inflation: %.3f%%\n", rate_of_inflation * 100);
		}
		if (op == 85) {
			puts("Nominal Rate (%)?");
			double nominal_rate = getValue() / 100;
			puts("Inflation Rate (%)?");
			double inflation_rate = getValue() / 100;
			double real_rate_of_return = (1 + nominal_rate) / (1 + inflation_rate) - 1;
			printf("\nReal Rate of Return: %.3f%%\n", real_rate_of_return * 100);
		}
		if (op == 86) {
			puts("Sales Revenue?");
			double sales_revenue = getValue();
			puts("Average Accounts Receivable?");
			double avg_accounts_receivable = getValue();
			double receivables_turnover = sales_revenue / avg_accounts_receivable;
			printf("\nReceivables Turnover Ratio: %.3f\n", receivables_turnover);
		}
		if (op == 87) {
			puts("Net Income?");
			double net_income = getValue();
			puts("Dividends?");
			double dividends = getValue();
			double retention_ratio = (net_income - dividends) / net_income;
			printf("\nRetention Ratio: %.3f%%\n", retention_ratio * 100);
		}
		if (op == 88) {
			puts("Net Income?");
			double net_income = getValue();
			puts("Average Total Assets?");
			double average_total_assets = getValue();
			double roa = net_income / average_total_assets;
			printf("\nReturn on Assets: %.3f\n", roa);
		}
		if (op == 89) {
			puts("Net Income?");
			double net_income = getValue();
			puts("Average Stockholder's Equity?");
			double avg_stockholders_equity = getValue();
			double roe = net_income / avg_stockholders_equity;
			printf("\nReturn on Equity (ROE): %.3f\n", roe);
		}
		if (op == 90) {
			puts("Beta?");
			double beta = getValue();
			puts("Risk Free Return (%)?");
			double risk_free_return = getValue() / 100;
			puts("Market Return (%)?");
			double market_return = getValue() / 100;
			double risk_premium = beta * (market_return - risk_free_return);
			printf("\nRisk Premium: %.3f%%\n", risk_premium * 100);
		}
		if (op == 91) {
			puts("Estimated Dividends for Next Period?");
			double dividends = getValue();
			puts("Required Rate of Return (%)?");
			double required_rate_of_return = getValue() / 100;
			puts("Growth Rate (%)?");
			double growth_rate = getValue() / 100;
			double price_of_stock = dividends / (required_rate_of_return - growth_rate);
			printf("\nPresent Value of Stock - Constant Growth: $%.2f\n", price_of_stock);
		}
		if (op == 92) {
			puts("Dividend?");
			double dividend = getValue();
			puts("Required Return (%)?");
			double required_return = getValue() / 100;
			double price = dividend / required_return;
			printf("\nPresent Value of Stock - Zero Growth: $%.3f\n", price);
		}
		if (op == 93) {
			puts("Tax Free Yield (%)?");
			double tax_free_yield = getValue() / 100;
			puts("Tax Rate (%)?");
			double tax_rate = getValue() / 100;
			double tax_equivalent_yield = tax_free_yield / (1 - tax_rate);
			printf("\nTax Equivalent Yield: %.3f%%\n", tax_equivalent_yield * 100);
		}
		if (op == 94) {
			puts("Initial Stock Price?");
			double initial_stock_price = getValue();
			puts("Ending Stock Price (Period 1)?");
			double ending_stock_price = getValue();
			puts("Dividends?");
			double dividends = getValue();
			double total_stock_return = ((ending_stock_price - initial_stock_price) + dividends) / initial_stock_price;
			printf("\nTotal Stock Return: %.3f%%\n", total_stock_return * 100);
		}
		if (op == 95) {
			puts("Coupon / Interest Payment?");
			double coupon = getValue();
			puts("Face Value?");
			double face_value = getValue();
			puts("Price?");
			double price = getValue();
			puts("Years to maturity?");
			double years_to_maturity = getValue();
			double approx_ytm = (coupon + ((face_value - price) / years_to_maturity)) / ((face_value + price) / 2);
			printf("\nYield to Maturity: %.3f%%\n", approx_ytm * 100);
		}
		if (op == 96) {
			puts("Face Value of Bond?");
			double face_value_of_bond = getValue();
			puts("Rate or Yield (%)?");
			double rate_or_yield = getValue() / 100;
			puts("Time to Maturity?");
			double time_to_maturity = getValue();
			double zero_coupon_bond_value = face_value_of_bond / pow(1 + rate_or_yield, time_to_maturity);
			printf("\nZero Coupon Bond Value: $%.2f\n", zero_coupon_bond_value);
		}
		if (op == 97) {
			puts("Face Value?");
			double face_value = getValue();
			puts("Present Value?");
			double present_value = getValue();
			puts("Number of Periods?");
			double number_of_periods = getValue();
			double zero_coupon_bond_yield = pow(face_value / present_value, 1 / number_of_periods) - 1;
			printf("\nZero Coupon Bond Effective Yield: %.3f%%\n", zero_coupon_bond_yield * 100);
		}
		if (op < 1 || op>97) {
			puts("\n\nError: Incorrect option id.\n\n");
		}
		fflush(NULL);
		printf("\nContinue? (Yes -> 1 / No -> 0)\n");
		op1 = (int)getValue();
	} while (op1 != 0);
}