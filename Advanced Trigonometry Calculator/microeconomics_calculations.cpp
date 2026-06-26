#include "stdafx.h"


template <typename T>
void microeconomicsCalculations() {
	int op = 0, op1 = 1;
	do {
		fflush(NULL);
		puts("\nWhat to calculate?\n");
		puts("Midpoint Method for Price Elasticity of Demand -> 1");
		puts("Average Fixed Cost -> 2");
		puts("Average Variable cost -> 3");
		puts("Average Total cost -> 4");
		puts("Unit Cost / Average Total cost -> 5");
		puts("Profit -> 6");
		puts("Profit based on Price, Avg Unit Cost and Quantity -> 7");
		puts("Economic Profit -> 8");
		puts("Cross-Price Elasticity of Demand -> 9");
		puts("Income Elasticity of Demand -> 10");
		puts("Price Elasticity of Demand -> 11");
		puts("Consumer Surplus -> 12");
		puts("Producer Surplus -> 13");
		puts("Price Elasticity of Supply -> 14");
		puts("Total Surplus -> 15");
		puts("Accounting Profit -> 16");
		op = (int)getValue<T>();
		puts("");
		if (op == 1) {
			puts("Price Point 1?");
			T price_point_1 = getValue<T>();
			puts("Quantity Point 1?");
			T quantity_point_1 = getValue<T>();
			puts("Price Point 2?");
			T price_point_2 = getValue<T>();
			puts("Quantity Point 2?");
			T quantity_point_2 = getValue<T>();
			T ped = ((quantity_point_2 - quantity_point_1) / ((quantity_point_2 + quantity_point_1) / 2)) / ((price_point_2 - price_point_1) / ((price_point_2 + price_point_1) / 2));
			printf("\nPrice Elasticity of Demand: %s\n", convert2Exponential(ped));
		}
		if (op == 2) {
			puts("Total Fixed cost?");
			T total_fixed_cost = getValue<T>();
			puts("Quantity of Output?");
			T quantity_of_output = getValue<T>();
			T average_fixed_cost = total_fixed_cost / quantity_of_output;
			printf("\nAverage Fixed cost: %s\n", convert2Exponential(average_fixed_cost));
		}
		if (op == 3) {
			puts("Variable cost?");
			T variable_cost = getValue<T>();
			puts("Quantity of the Ouput/Good?");
			T quantity = getValue<T>();
			T average_variable_cost = variable_cost / quantity;
			printf("\nAverage Variable cost: %s\n", convert2Exponential(average_variable_cost));
		}
		if (op == 4) {
			puts("Fixed costs?");
			T fixed_costs = getValue<T>();
			puts("Variable costs?");
			T variable_costs = getValue<T>();
			puts("Quantity pf Output/Goods?");
			T quantity_of_output = getValue<T>();
			T average_total_cost = fixed_costs / quantity_of_output + variable_costs / quantity_of_output;
			printf("\nAverage Total cost: %s\n", convert2Exponential(average_total_cost));
		}
		if (op == 5) {
			puts("Total costs?");
			T total_costs = getValue<T>();
			puts("Quantity of Goods?");
			T quantity = getValue<T>();
			T unit_cost = total_costs / quantity;
			printf("\nUnit cost (Average Total cost): %s\n", convert2Exponential(unit_cost));
		}
		if (op == 6) {
			puts("Total Revenue?");
			T total_revenue = getValue<T>();
			puts("Total Expenses?");
			T total_expenses = getValue<T>();
			T profit = total_revenue - total_expenses;
			printf("\nProfit: %s\n", convert2Exponential(profit));
		}
		if (op == 7) {
			puts("Unit Price?");
			T unit_price = getValue<T>();
			puts("Average Unit Cost that is also referred to as Unit Cost?");
			T unit_cost = getValue<T>();
			puts("Quantity Produced?");
			T quantity_produced = getValue<T>();
			T profit = (unit_price - unit_cost)*quantity_produced;
			printf("\nProfit: %s\n", convert2Exponential(profit));
		}
		if (op == 8) {
			puts("Total Revenue?");
			T total_revenue = getValue<T>();
			puts("Explicit costs?");
			T explicit_costs = getValue<T>();
			puts("Implicit costs?");
			T implicit_costs = getValue<T>();
			T economic_profit = total_revenue - (explicit_costs + implicit_costs);
			printf("\nEconomic Profit: %s\n", convert2Exponential(economic_profit));
		}
		if (op == 9) {
			puts("Percentage change in quantity demanded of a certain Good A?");
			T cda = getValue<T>();
			puts("Percentage change in the price of a certain Good A?");
			T cpb = getValue<T>();
			T cped = cda / cpb;
			printf("\nCross-Price Elasticity of Demand: %s\n", convert2Exponential(cped));
		}
		if (op == 10) {
			puts("Percentage Change in Quantity Demand?");
			T pcqd = getValue<T>();
			puts("Percentage Change in Income?");
			T pci = getValue<T>();
			T ied = pcqd / pci;
			printf("\nIncome Elasticity of Demand: %s\n", convert2Exponential(ied));
		}
		if (op == 11) {
			puts("Change in Quantity Demanded?");
			T cqd = getValue<T>();
			puts("Change in Price?");
			T cp = getValue<T>();
			T ped = cqd / cp;
			printf("\nPrice Elasticity of Demand: %s\n", convert2Exponential(ped));
		}
		if (op == 12) {
			puts("Value to Buyers?");
			T value_buyers = getValue<T>();
			puts("Amount Paid by Buyers?");
			T amount_paid_buyers = getValue<T>();
			T consumer_surplus = value_buyers - amount_paid_buyers;
			printf("\nConsumer Surplus: %s\n", convert2Exponential(consumer_surplus));
		}
		if (op == 13) {
			puts("Amount Received by the Seller?");
			T amount_received_seller = getValue<T>();
			puts("Cost to the Seller?");
			T cost_seller = getValue<T>();
			T consumer_surplus = amount_received_seller - cost_seller;
			printf("\nProducer Surplus: %s\n", convert2Exponential(consumer_surplus));
		}
		if (op == 14) {
			puts("Change in Quantity of Supply?");
			T change_quantity_supply = getValue<T>();
			puts("Price Change?");
			T price_change = getValue<T>();
			T price_elasticity_supply = change_quantity_supply / price_change;
			printf("\nPrice Elasticity of Supply: %s\n", convert2Exponential(price_elasticity_supply));
		}
		if (op == 15) {
			puts("Value to Buyers?");
			T value_buyers = getValue<T>();
			puts("Amount Paid by Buyers?");
			T amount_paid_buyers = getValue<T>();
			puts("Amount Received by Seller?");
			T amount_received_seller = getValue<T>();
			puts("Cost to the Seller?");
			T cost_seller = getValue<T>();
			T total_surplus = (value_buyers - amount_paid_buyers) + (amount_received_seller - cost_seller);
			printf("\nTotal Surplus: %s\n", convert2Exponential(total_surplus));
		}
		if (op == 16) {
			puts("Total Revenue?");
			T total_revenue = getValue<T>();
			puts("Total Explicit cost or Expenses?");
			T expenses = getValue<T>();
			T accounting_profit = total_revenue - expenses;
			printf("\nAccounting Profit: %s\n", convert2Exponential(accounting_profit));
		}
		if (op < 1 || op>16) {
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


void microeconomicsCalculations() { microeconomicsCalculations<double>(); }
template void microeconomicsCalculations<double>();
