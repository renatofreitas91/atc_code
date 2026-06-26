#include "stdafx.h"


template <typename T>
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
		op = (int)getValue<T>();
		puts(" ");
		if (op == 1) {
			int answer = 0;
			answer = -1;
			while (answer != 0 && answer != 1) {
				I_O = true;
				puts("Do you have the Cash Flow at period 1?  (Yes -> 1 / No -> 0)");
				answer = (int)getValue<T>();
			}
			if (answer == 1) {
				puts("Cash Flow at period 1?");
				T c_1 = getValue<T>();
				puts("Rate of return (%)?");
				T return_rate = getValue<T>();
				puts("Number of periods?");
				T number_periods = getValue<T>();
				T den = (1 + (return_rate / 100));
				den = pot(den, number_periods, 1);
				T present_value = c_1 / den;
				printf("\nPresent Value: $%.2f\n", present_value);
			}
			else {
				answer = -1;
				while (answer != 0 && answer != 1) {
					I_O = true;
					puts("Do you have the Future Value?  (Yes -> 1 / No -> 0)");
					answer = (int)getValue<T>();
				}
				if (answer == 1) {
					puts("Future Value?");
					T future_value = getValue<T>();
					puts("Rate of return (%)?");
					T return_rate = getValue<T>();
					puts("Number of periods?");
					T number_periods = getValue<T>();
					T den = (1 + (return_rate / 100));
					den = 1 / pot(den, number_periods, 1);
					T present_value = future_value * den;
					printf("\nPresent Value: $%.2f\n", present_value);
				}
				else {
					puts("\n\nError: Can not calculate Present Value.\n\n");
				}
			}
		}
		if (op == 2) {
			int answer = 0;
			answer = -1;
			while (answer != 0 && answer != 1) {
				I_O = true;
				puts("Do you have the Cash Flow at period 0?  (Yes -> 1 / No -> 0)");
				answer = (int)getValue<T>();
			}
			if (answer == 1) {
				puts("Cash Flow at period 0?");
				T c_0 = getValue<T>();
				puts("Rate of return (%)?");
				T return_rate = getValue<T>();
				puts("Number of periods?");
				T number_periods = (int)getValue<T>();
				T num = (1 + (return_rate / 100));
				num = pot(num, number_periods, 1);
				T future_value = c_0 * num;
				printf("\nFuture Value: $%.2f\n", future_value);
			}
			else {
				answer = -1;
				while (answer != 0 && answer != 1) {
					I_O = true;
					puts("Do you have the Present Value?  (Yes -> 1 / No -> 0)");
					answer = (int)getValue<T>();
				}
				if (answer == 1) {
					puts("Present Value?");
					T present_value = getValue<T>();
					puts("Rate of return (%)?");
					T return_rate = getValue<T>();
					puts("Number of periods?");
					T number_periods = getValue<T>();
					T num = (1 + (return_rate / 100));
					num = pot(num, number_periods, 1);
					T future_value = present_value * num;
					printf("\nFuture Value: $%.2f\n", future_value);
				}
				else {
					puts("\n\nError: Can not calculate Future Value.\n\n");
				}
			}
		}
		if (op == 3) {
			puts("Principal?");
			T principal = getValue<T>();
			puts("Rate (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Time?");
			T time = getValue<T>();
			T simple_interest = principal * rate*time;
			printf("\nSimple Interest: $%.2f\n", simple_interest);
		}
		if (op == 4) {
			puts("Principal (original balance)?");
			T principal = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T compound_interest = principal * (pot((1 + rate), number_periods, 1) - 1);
			printf("\nCompound Interest: $%.2f\n", compound_interest);
		}
		if (op == 5) {
			puts("Stated annual interest rate?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Number of times compounded?");
			T number_times = getValue<T>();
			T annual_percentage_yield = pot((1 + rate / number_times), number_times, 1) - 1;
			printf("\nAnnual Percentage Yield: %.2f%%\n", annual_percentage_yield * 100);
		}
		if (op == 6) {
			puts("Principal (original balance)?");
			T principal = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("time (number of periods)?");
			T number_times = getValue<T>();
			T continuous_compounding = principal * pot(M_E, rate*number_times, 1);
			printf("\nContinuous Compounding: $%.2f\n", continuous_compounding);
		}
		if (op == 7) {
			puts("Rate of return (%)?\nInfo: separate rates by using '\\'. Example: \"2\\4\\3\"");
			char* return_rates = getDynamicCharArray("", "return_rates");
			gets_s(return_rates, DIM);
			T* rates = getDynamicArray<T>(DIMDOUBLE);
			int i = 0, number_periods = 1;
			for (i = 0; i < abs((int)strlen(return_rates)); i++) {
				if (return_rates[i] == '\\') {
					number_periods++;
				}
			}
			int members = number_periods;
			i = 0;
			char* toValue = getDynamicCharArray("", "toValue");
			while (members >= 0) {
				int b = 0;
				while (return_rates[i] != '\\'&&i < abs((int)strlen(return_rates))) {
					toValue[b] = return_rates[i];
					b++; i++;
				}
				toValue[b] = '\0';
				solveMath<T>(toValue);
				rates[members] = precisionValueTo<T>(resultR) / 100;
				members--;
				sprintf(toValue, "");
				i++;
			}
			members = number_periods;
			T base = 1;
			while (members > 0) {
				base = base * (1 + rates[members]);
				members--;
			}
			T geometric_return = pot(base, (T)1 / number_periods, 1) - 1;
			printf("\nGeometric Mean Return: %.2f%%\n", geometric_return * 100);
			_delete(return_rates, "return_rates");
			return_rates = nullptr;
			_delete(toValue, "toValue");
			toValue = nullptr;
			_delete(rates, "rates");
			rates = nullptr;
		}
		if (op == 8) {
			puts("Rate per return (%)?\nInfo: separate rates by using '\\'. Example: \"2\\4\\3\"");
			char* return_rates = getDynamicCharArray("", "return_rates");
			gets_s(return_rates, DIM);
			T* rates = getDynamicArray<T>(DIMDOUBLE);
			int i = 0, number_periods = 1;
			for (i = 0; i < abs((int)strlen(return_rates)); i++) {
				if (return_rates[i] == '\\') {
					number_periods++;
				}
			}
			int members = number_periods;
			i = 0;
			char* toValue = getDynamicCharArray("", "toValue");
			while (members >= 0) {
				int b = 0;
				while (return_rates[i] != '\\'&&i < abs((int)strlen(return_rates))) {
					toValue[b] = return_rates[i];
					b++; i++;
				}
				toValue[b] = '\0';
				solveMath<T>(toValue);
				rates[members] = precisionValueTo<T>(resultR) / 100;
				members--;
				sprintf(toValue, "");
				i++;
			}
			members = number_periods;
			T base = 1;
			while (members > 0) {
				base = base * (1 + rates[members]);
				members--;
			}
			T holding_return = base - 1;
			printf("\nHolding Period Return: %.2f%%\n", holding_return * 100);
			_delete(return_rates, "return_rates");
			return_rates = nullptr;
			_delete(toValue, "toValue");
			toValue = nullptr;
			_delete(rates, "rates");
			rates = nullptr;
		}
		if (op == 9) {
			puts("Rate of return (%)?");
			T return_rate = getValue<T>();
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T den = (1 + (return_rate / 100));
			den = pot(den, number_periods, 1);
			T present_value_factor = 1 / den;
			printf("\nPresent Value Factor: %.2f\n", present_value_factor);
		}
		if (op == 10) {
			puts("Initial Investment?");
			T initial_investment = getValue<T>();
			puts("Discount Rate (%)?");
			T discount_rate = getValue<T>();
			discount_rate = discount_rate / 100;
			puts("Cash Flows?\nInfo: separate Cash Flows by using '\\'. Example: \"200\\400\\300\"");
			char* cash_flows = getDynamicCharArray("", "cash_flows");
			gets_s(cash_flows, DIM);
			T* cashFlow = getDynamicArray<T>(DIMDOUBLE);
			int i = 0, number_periods = 1;
			for (i = 0; i < abs((int)strlen(cash_flows)); i++) {
				if (cash_flows[i] == '\\') {
					number_periods++;
				}
			}
			int members = number_periods;
			i = 0;
			char* toValue = getDynamicCharArray("", "toValue");
			int p = 0;
			while (p < members) {
				int b = 0;
				while (cash_flows[i] != '\\'&&i < abs((int)strlen(cash_flows))) {
					toValue[b] = cash_flows[i];
					b++; i++;
				}
				toValue[b] = '\0';
				solveMath<T>(toValue);
				cashFlow[p] = precisionValueTo<T>(resultR);
				p++;
				sprintf(toValue, "");
				i++;
			}
			members = number_periods;
			int k = 1;
			T baseCF = 0;
			while (k <= members) {
				baseCF = baseCF + cashFlow[k - 1] / pot(1 + discount_rate, (T)k, 1);
				k++;
			}
			T net_present_value = baseCF - initial_investment;
			printf("\nNet Present Value: $%.2f\n", net_present_value);
			_delete(toValue, "toValue");
			toValue = nullptr;
			_delete(cash_flows, "cash_flows");
			cash_flows = nullptr;
			_delete(cashFlow, "cashFlow");
			cashFlow = nullptr;
		}
		if (op == 11) {
			puts("Periodic Payment?");
			T periodic_payment = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T present_value_annuity = periodic_payment * ((1 - pot(1 + rate, number_periods*-1, 1)) / rate);
			printf("\nPresent Value of Annuity: $%.2f\n", present_value_annuity);
		}
		if (op == 12) {
			puts("Cash Flow?");
			T cash_flow = getValue<T>();
			puts("Rate (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Time?");
			T time = getValue<T>();
			T pv_continuous_compounding = cash_flow / pot(M_E, rate*time, 1);
			printf("\nPV - Continuous Compounding: $%.2f\n", pv_continuous_compounding);
		}
		if (op == 13) {
			puts("Future Value?");
			T future_value = getValue<T>();
			puts("Present Value?");
			T present_value = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			T number_periods = ln(future_value / present_value) / ln(1 + rate);
			printf("\nNumber of Periods: %.2f\n", number_periods);
		}
		if (op == 14) {
			puts("Rate per period (%)?");
			T rate_per_period = getValue<T>();
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T future_value_factor = pot(1 + rate_per_period / 100, number_periods, 1);
			printf("\nFuture Value Factor: %.2f\n", future_value_factor);
		}
		if (op == 15) {
			puts("Present Value?");
			T present_value = getValue<T>();
			puts("Rate (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Time?");
			T time = getValue<T>();
			T fv_continuous_compounding = present_value * pot(M_E, rate*time, 1);
			printf("\nFV - Continuous Compounding: $%.2f\n", fv_continuous_compounding);
		}
		if (op == 16) {
			puts("Initial Investment?");
			T initial_investment = getValue<T>();
			puts("Periodic Cash Flow?");
			T periodic_cash_flow = getValue<T>();
			T payback_period = initial_investment / periodic_cash_flow;
			printf("\nPayback Period: %.2f\n", payback_period);
		}
		if (op == 17) {
			puts("Net Present Value?");
			T net_present_value = getValue<T>();
			puts("Rate per period (%)?");
			T rate_per_period = getValue<T>();
			rate_per_period = rate_per_period / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T equivalent_annual_annuity = (rate_per_period*net_present_value) / (1 - pot(1 + rate_per_period, -1 * number_periods, 1));
			printf("\nEquivalent Annual Annuity: $%.2f\n", equivalent_annual_annuity);
		}
		if (op == 18) {
			puts("Initial Investment (Outflow)?");
			T initial_investment = getValue<T>();
			puts("Rate (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Periodic Cash Flow?");
			T periodic_cash_flow = getValue<T>();
			T discounted_payback_period = ln(1 / (1 - (initial_investment*rate) / periodic_cash_flow)) / ln(1 + rate);
			printf("\nDiscounted Payback Period: %.2f\n", discounted_payback_period);
		}
		if (op == 19) {
			puts("Present Value (of Annuity)?");
			T present_value_annuity = getValue<T>();
			puts("Rate (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Payment/Cash Flows?");
			T payment_cash_flows = getValue<T>();
			T number_periods = ln(pot(1 - (present_value_annuity*rate) / payment_cash_flows, (T)-1, 1)) / ln(1 + rate);
			printf("\nAnnuity (PV)- Solve for n: %.2f\n", number_periods);
		}
		if (op == 20) {
			puts("Present Value?");
			T present_value = getValue<T>();
			puts("Rate (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T annuity_payment_pv = (rate*present_value) / (1 - pot(1 + rate, -1 * number_periods, 1));
			printf("\nAnnuity Payment (PV): $%.2f\n", annuity_payment_pv);
		}
		if (op == 21) {
			puts("Rate per period (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T annuity_pv_factor = (1 - pot(1 + rate, -1 * number_periods, 1)) / rate;
			printf("\nPresent Value Annuity Factor: %.2f\n", annuity_pv_factor);
		}
		if (op == 22) {
			puts("Periodic Payment?");
			T periodic_payment = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T pv_annuity_due = periodic_payment + periodic_payment * ((1 - pot(1 + rate, -1 * (number_periods - 1), 1)) / rate);
			printf("\nPresent Value of Annuity Due: $%.2f\n", pv_annuity_due);
		}
		if (op == 23) {
			puts("First Payment?");
			T first_payment = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Growth rate (%)?");
			T growth_rate = getValue<T>();
			growth_rate = growth_rate / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T pv_growing_annuity = (first_payment / (rate - growth_rate))*(1 - pot((1 + growth_rate) / (1 + rate), number_periods, 1));
			printf("\nPresent Value of a Growing Annuity: $%.2f\n", pv_growing_annuity);
		}
		if (op == 24) {
			puts("Periodic Payment?");
			T periodic_payment = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T fv_value_of_annuity = periodic_payment * ((pot(1 + rate, number_periods, 1) - 1) / rate);
			printf("\nFuture Value of Annuity: $%.2f\n", fv_value_of_annuity);
		}
		if (op == 25) {
			puts("Future Value (of Annuity)?");
			T future_value_annuity = getValue<T>();
			puts("Rate (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Payment/Cash Flows?");
			T payment_cash_flows = getValue<T>();
			T number_periods = ln(1 + (future_value_annuity*rate) / payment_cash_flows) / ln(1 + rate);
			printf("\nAnnuity (FV)- Solve for n: %.2f\n", number_periods);
		}
		if (op == 26) {
			puts("Rate (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			T doubling_time_without_compounding = 1 / rate;
			printf("\nDoubling Time - Simple Interest: %.2f\n", doubling_time_without_compounding);
		}
		if (op == 27) {
			puts("Rate of return (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			T doubling_time = log10(2) / log10(1 + rate);
			printf("\nDoubling Time: %.2f\n", doubling_time);
		}
		if (op == 28) {
			puts("Rate expressed as a whole number (%)?");
			T rate = getValue<T>();
			T rule_of_72 = 72 / rate;
			printf("\nRule of 72: %.2f\n", rule_of_72);
		}
		if (op == 29) {
			puts("Rate (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			T dt_continuos_compounding = ln((T)2) / rate;
			printf("\nDoubling Time - Continuous Compounding: %.2f\n", dt_continuos_compounding);
		}
		if (op == 30) {
			puts("Relative weight (%)?\nInfo: separate relative weights by using '\\'. Example: \"2\\4\\3\"");
			char* relative_weight = getDynamicCharArray("", "relative_weight");
			gets_s(relative_weight, DIM);
			T* w = getDynamicArray<T>(DIMDOUBLE);
			int i = 0, number_periods = 1;
			for (i = 0; i < abs((int)strlen(relative_weight)); i++) {
				if (relative_weight[i] == '\\') {
					number_periods++;
				}
			}
			int members = number_periods;
			i = 0;
			char* toValue = getDynamicCharArray("", "toValue");
			while (members >= 0) {
				int b = 0;
				while (relative_weight[i] != '\\'&&i < abs((int)strlen(relative_weight))) {
					toValue[b] = relative_weight[i];
					b++; i++;
				}
				toValue[b] = '\0';
				solveMath<T>(toValue);
				w[members] = precisionValueTo<T>(resultR) / 100;
				members--;
				sprintf(toValue, "");
				i++;
			}
			puts("Values?\nInfo: separate values by using '\\'. Example: \"2\\4\\3\"");
			char* values = getDynamicCharArray("", "values");
			gets_s(values, DIM);
			T* x = getDynamicArray<T>(DIMDOUBLE);
			i = 0; number_periods = 1;
			for (i = 0; i < abs((int)strlen(values)); i++) {
				if (values[i] == '\\') {
					number_periods++;
				}
			}
			members = number_periods;
			i = 0;
			sprintf(toValue, "");
			while (members >= 0) {
				int b = 0;
				while (values[i] != '\\'&&i < abs((int)strlen(values))) {
					toValue[b] = values[i];
					b++; i++;
				}
				toValue[b] = '\0';
				solveMath<T>(toValue);
				x[members] = precisionValueTo<T>(resultR);
				members--;
				sprintf(toValue, "");
				i++;
			}
			T weighted_average = 0;
			i = 0;
			while (i <= number_periods) {
				weighted_average = weighted_average + x[i] * w[i];
				i++;
			}
			printf("\nWeighted Average: %.2f%%\n", weighted_average * 100);
			_delete(relative_weight, "relative_weight");
			relative_weight = nullptr;
			_delete(toValue, "toValue");
			toValue = nullptr;
			_delete(values, "values");
			values = nullptr;
			_delete(w, "w");
			w = nullptr;
			_delete(x, "x");
			x = nullptr;
		}
		if (op == 31) {
			puts("Earnings?");
			T earnings = getValue<T>();
			puts("Initial Investment?");
			T initial_investment = getValue<T>();
			T return_on_investment = (earnings - initial_investment) / initial_investment;
			printf("\nReturn on Investment: %.2f%%\n", return_on_investment * 100);
		}
		if (op == 32) {
			puts("Cash Flow?");
			T cash_flow = getValue<T>();
			puts("Rate (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Time?");
			T time = getValue<T>();
			T fv_annuity_continuos_compounding = cash_flow * ((pot(M_E, rate*time, 1) - 1) / (pot(M_E, rate, 1) - 1));
			printf("\nFV of Annuity - Continuous Compounding: $%.2f\n", fv_annuity_continuos_compounding);
		}
		if (op == 33) {
			puts("Present Value (Original Balance)?");
			T present_value = getValue<T>();
			puts("Payment?");
			T payment = getValue<T>();
			puts("Rate per payment (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Number of payments?");
			T number_payments = getValue<T>();
			T fv_remaining_balance = present_value * pot(1 + rate, number_payments, 1) - payment * ((pot(1 + rate, number_payments, 1) - 1) / rate);
			printf("\nRemaining Balance on Loan: $%.2f\n", fv_remaining_balance);
		}
		if (op == 34) {
			puts("Present Value?");
			T present_value = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T loan_payment = (rate*present_value) / (1 - pot(1 + rate, -1 * number_periods, 1));
			printf("\nLoan Payment: $%.2f\n", loan_payment);
		}
		if (op == 35) {
			puts("Present Value (Original Balance)?");
			T present_value = getValue<T>();
			puts("Payment?");
			T payment = getValue<T>();
			puts("Rate per payment (%)?");
			T rate = getValue<T>();
			rate = rate / 100;
			puts("Number of payments?");
			T number_payments = getValue<T>();
			T fv_balloon_balance = present_value * pot(1 + rate, number_payments, 1) - payment * ((pot(1 + rate, number_payments, 1) - 1) / rate);
			printf("\nBalloon Balance of a Loan: $%.2f\n", fv_balloon_balance);
		}
		if (op == 36) {
			puts("Present Value?");
			T present_value = getValue<T>();
			puts("Balloon Amount?");
			T balloon_amount = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>() / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T payment_balloon_loan = (present_value - balloon_amount / pot(1 + rate, number_periods, 1))*rate / (1 - pot(1 + rate, -1 * number_periods, 1));
			printf("\nPayments on a Balloon Loan: $%.2f\n", payment_balloon_loan);
		}
		if (op == 37) {
			puts("Rate per period (%)?");
			T rate = getValue<T>() / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T payment_factor = rate / (1 - pot(1 + rate, -1 * number_periods, 1));
			printf("\nAnnuity Payment Factor - PV: %.2f\n", payment_factor);
		}
		if (op == 38) {
			puts("First Payment?");
			T first_payment = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>() / 100;
			puts("Growth rate (%)?");
			T growth_rate = getValue<T>() / 100;
			puts("Number of periods");
			T number_periods = getValue<T>();
			T fv_growing_annuity = first_payment * ((pot(1 + rate, number_periods, 1) - pot(1 + growth_rate, number_periods, 1)) / (rate - growth_rate));
			printf("\nFuture Value of Growing Annuity: $%.2f\n", fv_growing_annuity);
		}
		if (op == 39) {
			puts("Future Value?");
			T future_value = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>() / 100;
			puts("Growth rate (%)?");
			T growth_rate = getValue<T>() / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T growing_annuity_payment_fv = future_value * ((rate - growth_rate) / (pot(1 + rate, number_periods, 1) - pot(1 + growth_rate, number_periods, 1)));
			printf("\nGrowing Annuity Payment - FV: $%.2f\n", growing_annuity_payment_fv);
		}
		if (op == 40) {
			puts("Present Value?");
			T present_value = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>() / 100;
			puts("Growth rate (%)?");
			T growth_rate = getValue<T>() / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T initial_payment = present_value * ((rate - growth_rate) / (1 - pot((1 + growth_rate) / (1 + rate), number_periods, 1)));
			printf("\nGrowing Annuity Payment - PV: $%.2f\n", initial_payment);
		}
		if (op == 41) {
			puts("Future Value?");
			T future_value = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>() / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T payment = (future_value*rate) / (pot(1 + rate, number_periods, 1) - 1);
			printf("\nAnnuity Payment - FV: $%.2f\n", payment);
		}
		if (op == 42) {
			puts("Future Value?");
			T future_value = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>() / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T payment = future_value * (rate / (pot(1 + rate, number_periods, 1) - 1))*(1 / (1 + rate));
			printf("\nAnnuity Due Payment - FV: $%.2f\n", payment);
		}
		if (op == 43) {
			puts("Present Value?");
			T present_value = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>() / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T payment = present_value * (rate / (1 - pot(1 + rate, -1 * number_periods, 1)))*(1 / (1 + rate));
			printf("\nAnnuity Due Payment - PV: $%.2f\n", payment);
		}
		if (op == 44) {
			puts("Periodic Payment?");
			T periodic_payment = getValue<T>();
			puts("Rate per period (%)?");
			T rate = getValue<T>() / 100;
			puts("Number of periods?");
			T number_periods = getValue<T>();
			T fv_annuity_due = (1 + rate)*periodic_payment*((pot(1 + rate, number_periods, 1) - 1) / rate);
			printf("\nFuture Value of Annuity Due: $%.2f\n", fv_annuity_due);
		}
		if (op == 45) {
			puts("Total Assets?");
			T total_assets = getValue<T>();
			puts("Sales Revenue?");
			T sales_revenue = getValue<T>();
			T asset_to_sales = total_assets / sales_revenue;
			printf("\nAsset to Sales Ratio: %s\n", convert2Exponential(asset_to_sales));
		}
		if (op == 46) {
			puts("Sales Revenue?");
			T sales_revenue = getValue<T>();
			puts("Total Assets?");
			T total_assets = getValue<T>();
			T asset_turnover = sales_revenue / total_assets;
			printf("\nAsset Turnover Ratio: %s\n", convert2Exponential(asset_turnover));
		}
		if (op == 47) {
			puts("Receivables Turnover?");
			T receivables_turnover = getValue<T>();
			T avg_collection_period = 365 / receivables_turnover;
			printf("\nAverage Collection Period: %s\n", convert2Exponential(avg_collection_period));
		}
		if (op == 48) {
			puts("Ask Price?");
			T ask_price = getValue<T>();
			puts("Bid Price?");
			T bid_price = getValue<T>();
			T bid_ask_spread = ask_price - bid_price;
			printf("\nBid-Ask Spread: $%.2f\n", bid_ask_spread);
		}
		if (op == 49) {
			puts("Face Value?");
			T face_value = getValue<T>();
			puts("Price?");
			T price = getValue<T>();
			puts("Days to maturity?");
			T d = getValue<T>();
			T bond_equivalent_yield = ((face_value - price) / price)*(365 / d);
			printf("\nBond Equivalent Yield: %.3f%%\n", bond_equivalent_yield * 100);
		}
		if (op == 50) {
			puts("Total Common Stockholder's Equity?");
			T total_common_stockholder_equity = getValue<T>();
			puts("Number of Common Shares?");
			T number_common_shares = getValue<T>();
			T book_value_per_share = total_common_stockholder_equity / number_common_shares;
			printf("\nBook Value per Share: $%.3f\n", book_value_per_share);
		}
		if (op == 51) {
			puts("Risk free rate (%)?");
			T risk_free_rate = getValue<T>() / 100;
			puts("Beta?");
			T beta = getValue<T>();
			puts("Return on the market (%)?");
			T return_market = getValue<T>() / 100;
			T capm = risk_free_rate + beta * (return_market - risk_free_rate);
			printf("\nCapital Asset Pricing Model: %.3f%%\n", capm * 100);
		}
		if (op == 52) {
			puts("Initial Stock Price?");
			T initial_stock_price = getValue<T>();
			puts("Stock Price after 1st period?");
			T stock_price_after_1st_period = getValue<T>();
			T capital_gains_yield = (stock_price_after_1st_period - initial_stock_price) / initial_stock_price;
			printf("\nCapital Gains Yield: %.3f%%\n", capital_gains_yield * 100);
		}
		if (op == 53) {
			puts("Price per Product?");
			T price_per_product = getValue<T>();
			puts("Variable Cost per Product?");
			T variable_cost_per_product = getValue<T>();
			T contribution_margin = price_per_product - variable_cost_per_product;
			printf("\nContribution Margin: $%.2f\n", contribution_margin);
		}
		if (op == 54) {
			puts("Current Assets?");
			T current_assets = getValue<T>();
			puts("Current Liabilities?");
			T current_liabilities = getValue<T>();
			T current_ratio = current_assets / current_liabilities;
			printf("\nCurrent Ratio: %s\n", convert2Exponential(current_ratio));
		}
		if (op == 55) {
			puts("Annual Coupons?");
			T annual_coupons = getValue<T>();
			puts("Current Bond Price?");
			T current_bond_price = getValue<T>();
			T current_yield = annual_coupons / current_bond_price;
			printf("\nCurrent Yield: %.3f%%\n", current_yield * 100);
		}
		if (op == 56) {
			puts("Inventory Turnover?");
			T inventory_turnover = getValue<T>();
			T inventory_days = 365 / inventory_turnover;
			printf("\nDays in Inventory: %s\n", convert2Exponential(inventory_days));
		}
		if (op == 57) {
			puts("Net Operation Income?");
			T net_operation_income = getValue<T>();
			puts("Debt Service?");
			T debt_service = getValue<T>();
			T debt_coverage_ratio = net_operation_income / debt_service;
			printf("\nDebt Coverage Ratio: $%.3f\n", debt_coverage_ratio);
		}
		if (op == 58) {
			puts("Total Liabilities?");
			T total_liabilities = getValue<T>();
			puts("Total Assets?");
			T total_assets = getValue<T>();
			T debt_ratio = total_liabilities / total_assets;
			printf("\nDebt Ratio: %.4f\n", debt_ratio);
		}
		if (op == 59) {
			puts("Total Liabilities?");
			T total_liabilities = getValue<T>();
			puts("Total Equity?");
			T total_equity = getValue<T>();
			T debt_to_equity = total_liabilities / total_equity;
			printf("\nDebt to Equity Ratio (D/E): %.4f\n", debt_to_equity);
		}
		if (op == 60) {
			puts("Monthly Debt Payments?");
			T monthly_debt_payments = getValue<T>();
			puts("Gross Monthly Income?");
			T gross_monthly_income = getValue<T>();
			T debt_to_income = monthly_debt_payments / gross_monthly_income;
			printf("\nDebt to Income Ratio: %.2f%%\n", debt_to_income * 100);
		}
		if (op == 61) {
			puts("Net Income?");
			T net_income = getValue<T>();
			puts("Average Shares?");
			T average_shares = getValue<T>();
			puts("Other Convertible Instruments?");
			T other_convertible_instruments = getValue<T>();
			T diluted_eps = net_income / (average_shares + other_convertible_instruments);
			printf("\nDiluted Earnings per Share: $%.2f\n", diluted_eps);
		}
		if (op == 62) {
			puts("Dividends?");
			T dividends = getValue<T>();
			puts("Net Income?");
			T net_income = getValue<T>();
			T dividend_payout_ratio = dividends / net_income;
			printf("\nDividend Payout Ratio: %.3f%%\n", dividend_payout_ratio * 100);
		}
		if (op == 63) {
			puts("Dividends for the period?");
			T dividends_for_the_period = getValue<T>();
			puts("Initial Price for the Period?");
			T initial_price_for_the_period = getValue<T>();
			T dividend_yield = dividends_for_the_period / initial_price_for_the_period;
			printf("\nDividend Yield (Stock): %.3f%%\n", dividend_yield * 100);
		}
		if (op == 64) {
			puts("Dividends?");
			T dividends = getValue<T>();
			puts("Number of Shares?");
			T number_of_shares = getValue<T>();
			T dps = dividends / number_of_shares;
			printf("\nDividends Per Share: $%.2f\n", dps);
		}
		if (op == 65) {
			puts("Net Income?");
			T net_income = getValue<T>();
			puts("Weighted Average Outstanding Shares?");
			T weighted_avg_outstanding_shares = getValue<T>();
			T eps = net_income / weighted_avg_outstanding_shares;
			printf("\nEarnings Per Share: $%.2f\n", eps);
		}
		if (op == 66) {
			puts("Total Assets?");
			T total_assets = getValue<T>();
			puts("Stockholder's Equity?");
			T stockholders_equity = getValue<T>();
			T equity_multiplier = total_assets / stockholders_equity;
			printf("\nEquity Multiplier: %.3f\n", equity_multiplier);
		}
		if (op == 67) {
			puts("Projected Sales?");
			T projected_sales = getValue<T>();
			puts("Projected Net Profit Margin (%)?");
			T projected_net_profit_margin = getValue<T>() / 100;
			T estimated_earnings = projected_sales * projected_net_profit_margin;
			printf("\nEstimated Earnings: $%.2f\n", estimated_earnings);
		}
		if (op == 68) {
			puts("Net Income?");
			T net_income = getValue<T>();
			puts("Capital Expenditures?");
			T capital_expenditures = getValue<T>();
			puts("Change in Working Capital?");
			T change_in_working_capital = getValue<T>();
			puts("Net Borrowing?");
			T net_borrowing = getValue<T>();
			T fcfe = net_income - capital_expenditures - change_in_working_capital + net_borrowing;
			printf("\nFree Cash Flow to Equity: $%.2f\n", fcfe);
		}
		if (op == 69) {
			puts("EBIT?");
			T ebit = getValue<T>();
			puts("Tax Rate (%)?");
			T tax_rate = getValue<T>() / 100;
			puts("Capital Expenditures?");
			T capital_expenditures = getValue<T>();
			puts("Change in Working Capital?");
			T change_in_working_capital = getValue<T>();
			T fcff = ebit * (1 - tax_rate) - capital_expenditures - change_in_working_capital;
			printf("\nFree Cash Flow to Firm (FCFF): $%.2f\n", fcff);
		}
		if (op == 70) {
			puts("Dividend or Coupon at period 1?");
			T dividend = getValue<T>();
			puts("Discount rate (%)?");
			T discount_rate = getValue<T>() / 100;
			puts("Growth rate (%)?");
			T growth_rate = getValue<T>() / 100;
			T pv_of_growing_perpetuity = dividend / (discount_rate - growth_rate);
			printf("\nPresent Value of Growing Perpetuity: $%.2f\n", pv_of_growing_perpetuity);
		}
		if (op == 71) {
			puts("EBIT?");
			T ebit = getValue<T>();
			puts("Interest Expense?");
			T interest_expense = getValue<T>();
			T interest_coverage_ratio = ebit / interest_expense;
			printf("\nInterest Coverage Ratio: %.2f\n", interest_coverage_ratio);
		}
		if (op == 72) {
			puts("Sales?");
			T sales = getValue<T>();
			puts("Inventory?");
			T inventory = getValue<T>();
			T inventory_turnover = sales / inventory;
			printf("\nInventory Turnover Ratio: %.2f\n", inventory_turnover);
		}
		if (op == 73) {
			puts("Loans?");
			T loans = getValue<T>();
			puts("Deposits?");
			T deposits = getValue<T>();
			T loan_to_deposit_ratio = loans / deposits;
			printf("\nLoan to Deposit Ratio: %.2f%%\n", loan_to_deposit_ratio * 100);
		}
		if (op == 74) {
			puts("Loan Amount?");
			T loan_amount = getValue<T>();
			puts("Value of Collateral?");
			T value_of_collateral = getValue<T>();
			T ltv_ratio = loan_amount / value_of_collateral;
			printf("\nLoan to Value Ratio: %.2f%%\n", ltv_ratio * 100);
		}
		if (op == 75) {
			puts("Fund Assets?");
			T fund_assets = getValue<T>();
			puts("Fund Liabilities?");
			T fund_liabilities = getValue<T>();
			puts("Outstanding Shares?");
			T outstanding_shares = getValue<T>();
			T nav = (fund_assets - fund_liabilities) / outstanding_shares;
			printf("\nNet Asset Value: $%.2f\n", nav);
		}
		if (op == 76) {
			puts("Net Income?");
			T net_income = getValue<T>();
			puts("Sales Revenue?");
			T sales_revenue = getValue<T>();
			T net_profit_margin = net_income / sales_revenue;
			printf("\nNet Profit Margin: %.2f%%\n", net_profit_margin * 100);
		}
		if (op == 77) {
			puts("Current Assets?");
			T current_assets = getValue<T>();
			puts("Current Liabilities?");
			T current_liabilities = getValue<T>();
			T net_working_capital = current_assets - current_liabilities;
			printf("\nNet Working Capital: $%.2f\n", net_working_capital);
		}
		if (op == 78) {
			puts("Dividend or Coupon per period?");
			T dividend = getValue<T>();
			puts("Discount rate (%)?");
			T discount_rate = getValue<T>() / 100;
			T pv_of_perpetuity = dividend / discount_rate;
			printf("\nPV of Perpetuity: $%.2f\n", pv_of_perpetuity);
		}
		if (op == 79) {
			puts("Dividend?");
			T dividend = getValue<T>();
			puts("Discount rate (%)?");
			T discount_rate = getValue<T>() / 100;
			T preferred_stock_value = dividend / discount_rate;
			printf("\nPreferred Stock: $%.2f\n", preferred_stock_value);
		}
		if (op == 80) {
			puts("Market Price per Share?");
			T market_price_per_share = getValue<T>();
			puts("Book Value per Share?");
			T book_value_per_share = getValue<T>();
			T price_to_book_value = market_price_per_share / book_value_per_share;
			printf("\nPrice to Book Value: %.3f\n", price_to_book_value);
		}
		if (op == 81) {
			puts("Price per Share?");
			T price_per_share = getValue<T>();
			puts("Earnings per Share?");
			T earnings_per_share = getValue<T>();
			T price_to_earning_ratio = price_per_share / earnings_per_share;
			printf("\nPrice to Earnings Ratio: %.3f\n", price_to_earning_ratio);
		}
		if (op == 82) {
			puts("Share Price?");
			T share_price = getValue<T>();
			puts("Sales Per Share?");
			T sales_per_share = getValue<T>();
			T price_to_sales_ratio = share_price / sales_per_share;
			printf("\nPrice to Sales Ratio: %.3f\n", price_to_sales_ratio);
		}
		if (op == 83) {
			puts("Quick Assets?");
			T quick_assets = getValue<T>();
			puts("Current Liabilities?");
			T current_liabilities = getValue<T>();
			T quick_ratio = quick_assets / current_liabilities;
			printf("\nQuick Ratio: %.3f\n", quick_ratio);
		}
		if (op == 84) {
			puts("Ending CPI?");
			T ending_cpi = getValue<T>();
			puts("Initial CPI?");
			T initial_cpi = getValue<T>();
			T rate_of_inflation = (ending_cpi - initial_cpi) / initial_cpi;
			printf("\nRate of Inflation: %.3f%%\n", rate_of_inflation * 100);
		}
		if (op == 85) {
			puts("Nominal Rate (%)?");
			T nominal_rate = getValue<T>() / 100;
			puts("Inflation Rate (%)?");
			T inflation_rate = getValue<T>() / 100;
			T real_rate_of_return = (1 + nominal_rate) / (1 + inflation_rate) - 1;
			printf("\nReal Rate of Return: %.3f%%\n", real_rate_of_return * 100);
		}
		if (op == 86) {
			puts("Sales Revenue?");
			T sales_revenue = getValue<T>();
			puts("Average Accounts Receivable?");
			T avg_accounts_receivable = getValue<T>();
			T receivables_turnover = sales_revenue / avg_accounts_receivable;
			printf("\nReceivables Turnover Ratio: %.3f\n", receivables_turnover);
		}
		if (op == 87) {
			puts("Net Income?");
			T net_income = getValue<T>();
			puts("Dividends?");
			T dividends = getValue<T>();
			T retention_ratio = (net_income - dividends) / net_income;
			printf("\nRetention Ratio: %.3f%%\n", retention_ratio * 100);
		}
		if (op == 88) {
			puts("Net Income?");
			T net_income = getValue<T>();
			puts("Average Total Assets?");
			T average_total_assets = getValue<T>();
			T roa = net_income / average_total_assets;
			printf("\nReturn on Assets: %.3f\n", roa);
		}
		if (op == 89) {
			puts("Net Income?");
			T net_income = getValue<T>();
			puts("Average Stockholder's Equity?");
			T avg_stockholders_equity = getValue<T>();
			T roe = net_income / avg_stockholders_equity;
			printf("\nReturn on Equity (ROE): %.3f\n", roe);
		}
		if (op == 90) {
			puts("Beta?");
			T beta = getValue<T>();
			puts("Risk Free Return (%)?");
			T risk_free_return = getValue<T>() / 100;
			puts("Market Return (%)?");
			T market_return = getValue<T>() / 100;
			T risk_premium = beta * (market_return - risk_free_return);
			printf("\nRisk Premium: %.3f%%\n", risk_premium * 100);
		}
		if (op == 91) {
			puts("Estimated Dividends for Next Period?");
			T dividends = getValue<T>();
			puts("Required Rate of Return (%)?");
			T required_rate_of_return = getValue<T>() / 100;
			puts("Growth Rate (%)?");
			T growth_rate = getValue<T>() / 100;
			T price_of_stock = dividends / (required_rate_of_return - growth_rate);
			printf("\nPresent Value of Stock - Constant Growth: $%.2f\n", price_of_stock);
		}
		if (op == 92) {
			puts("Dividend?");
			T dividend = getValue<T>();
			puts("Required Return (%)?");
			T required_return = getValue<T>() / 100;
			T price = dividend / required_return;
			printf("\nPresent Value of Stock - Zero Growth: $%.3f\n", price);
		}
		if (op == 93) {
			puts("Tax Free Yield (%)?");
			T tax_free_yield = getValue<T>() / 100;
			puts("Tax Rate (%)?");
			T tax_rate = getValue<T>() / 100;
			T tax_equivalent_yield = tax_free_yield / (1 - tax_rate);
			printf("\nTax Equivalent Yield: %.3f%%\n", tax_equivalent_yield * 100);
		}
		if (op == 94) {
			puts("Initial Stock Price?");
			T initial_stock_price = getValue<T>();
			puts("Ending Stock Price (Period 1)?");
			T ending_stock_price = getValue<T>();
			puts("Dividends?");
			T dividends = getValue<T>();
			T total_stock_return = ((ending_stock_price - initial_stock_price) + dividends) / initial_stock_price;
			printf("\nTotal Stock Return: %.3f%%\n", total_stock_return * 100);
		}
		if (op == 95) {
			puts("Coupon / Interest Payment?");
			T coupon = getValue<T>();
			puts("Face Value?");
			T face_value = getValue<T>();
			puts("Price?");
			T price = getValue<T>();
			puts("Years to maturity?");
			T years_to_maturity = getValue<T>();
			T approx_ytm = (coupon + ((face_value - price) / years_to_maturity)) / ((face_value + price) / 2);
			printf("\nYield to Maturity: %.3f%%\n", approx_ytm * 100);
		}
		if (op == 96) {
			puts("Face Value of Bond?");
			T face_value_of_bond = getValue<T>();
			puts("Rate or Yield (%)?");
			T rate_or_yield = getValue<T>() / 100;
			puts("Time to Maturity?");
			T time_to_maturity = getValue<T>();
			T zero_coupon_bond_value = face_value_of_bond / pot(1 + rate_or_yield, time_to_maturity, 1);
			printf("\nZero Coupon Bond Value: $%.2f\n", zero_coupon_bond_value);
		}
		if (op == 97) {
			puts("Face Value?");
			T face_value = getValue<T>();
			puts("Present Value?");
			T present_value = getValue<T>();
			puts("Number of Periods?");
			T number_of_periods = getValue<T>();
			T zero_coupon_bond_yield = pot(face_value / present_value, 1 / number_of_periods, 1) - 1;
			printf("\nZero Coupon Bond Effective Yield: %.3f%%\n", zero_coupon_bond_yield * 100);
		}
		if (op < 1 || op>97) {
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

void financialCalculations() { financialCalculations<double>(); }
