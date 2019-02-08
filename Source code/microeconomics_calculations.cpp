#include "stdafx.h"

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
		op = (int)getValue();
		puts("");
		if (op == 1) {
			puts("Price Point 1?");
			double price_point_1 = getValue();
			puts("Quantity Point 1?");
			double quantity_point_1 = getValue();
			puts("Price Point 2?");
			double price_point_2 = getValue();
			puts("Quantity Point 2?");
			double quantity_point_2 = getValue();
			double ped = ((quantity_point_2 - quantity_point_1) / ((quantity_point_2 + quantity_point_1) / 2)) / ((price_point_2 - price_point_1) / ((price_point_2 + price_point_1) / 2));
			printf("\nPrice Elasticity of Demand: %G\n", ped);
		}
		if (op == 2) {
			puts("Total Fixed cost?");
			double total_fixed_cost = getValue();
			puts("Quantity of Output?");
			double quantity_of_output = getValue();
			double average_fixed_cost = total_fixed_cost / quantity_of_output;
			printf("\nAverage Fixed cost: %G\n", average_fixed_cost);
		}
		if (op == 3) {
			puts("Variable cost?");
			double variable_cost = getValue();
			puts("Quantity of the Ouput/Good?");
			double quantity = getValue();
			double average_variable_cost = variable_cost / quantity;
			printf("\nAverage Variable cost: %G\n", average_variable_cost);
		}
		if (op == 4) {
			puts("Fixed costs?");
			double fixed_costs = getValue();
			puts("Variable costs?");
			double variable_costs = getValue();
			puts("Quantity pf Output/Goods?");
			double quantity_of_output = getValue();
			double average_total_cost = fixed_costs / quantity_of_output + variable_costs / quantity_of_output;
			printf("\nAverage Total cost: %G\n", average_total_cost);
		}
		if (op == 5) {
			puts("Total costs?");
			double total_costs = getValue();
			puts("Quantity of Goods?");
			double quantity = getValue();
			double unit_cost = total_costs / quantity;
			printf("\nUnit cost (Average Total cost): %G\n", unit_cost);
		}
		if (op == 6) {
			puts("Total Revenue?");
			double total_revenue = getValue();
			puts("Total Expenses?");
			double total_expenses = getValue();
			double profit = total_revenue - total_expenses;
			printf("\nProfit: %G\n", profit);
		}
		if (op == 7) {
			puts("Unit Price?");
			double unit_price = getValue();
			puts("Average Unit Cost that is also referred to as Unit Cost?");
			double unit_cost = getValue();
			puts("Quantity Produced?");
			double quantity_produced = getValue();
			double profit = (unit_price - unit_cost)*quantity_produced;
			printf("\nProfit: %G\n", profit);
		}
		if (op == 8) {
			puts("Total Revenue?");
			double total_revenue = getValue();
			puts("Explicit costs?");
			double explicit_costs = getValue();
			puts("Implicit costs?");
			double implicit_costs = getValue();
			double economic_profit = total_revenue - (explicit_costs + implicit_costs);
			printf("\nEconomic Profit: %G\n", economic_profit);
		}
		if (op == 9) {
			puts("Percentage change in quantity demanded of a certain Good A?");
			double cda = getValue();
			puts("Percentage change in the price of a certain Good A?");
			double cpb = getValue();
			double cped = cda / cpb;
			printf("\nCross-Price Elasticity of Demand: %G\n", cped);
		}
		if (op == 10) {
			puts("Percentage Change in Quantity Demand?");
			double pcqd = getValue();
			puts("Percentage Change in Income?");
			double pci = getValue();
			double ied = pcqd / pci;
			printf("\nIncome Elasticity of Demand: %G\n", ied);
		}
		if (op == 11) {
			puts("Change in Quantity Demanded?");
			double cqd = getValue();
			puts("Change in Price?");
			double cp = getValue();
			double ped = cqd / cp;
			printf("\nPrice Elasticity of Demand: %G\n", ped);
		}
		if (op == 12) {
			puts("Value to Buyers?");
			double value_buyers = getValue();
			puts("Amount Paid by Buyers?");
			double amount_paid_buyers = getValue();
			double consumer_surplus = value_buyers - amount_paid_buyers;
			printf("\nConsumer Surplus: %G\n", consumer_surplus);
		}
		if (op == 13) {
			puts("Amount Received by the Seller?");
			double amount_received_seller = getValue();
			puts("Cost to the Seller?");
			double cost_seller = getValue();
			double consumer_surplus = amount_received_seller - cost_seller;
			printf("\nProducer Surplus: %G\n", consumer_surplus);
		}
		if (op == 14) {
			puts("Change in Quantity of Supply?");
			double change_quantity_supply = getValue();
			puts("Price Change?");
			double price_change = getValue();
			double price_elasticity_supply = change_quantity_supply / price_change;
			printf("\nPrice Elasticity of Supply: %G\n", price_elasticity_supply);
		}
		if (op == 15) {
			puts("Value to Buyers?");
			double value_buyers = getValue();
			puts("Amount Paid by Buyers?");
			double amount_paid_buyers = getValue();
			puts("Amount Received by Seller?");
			double amount_received_seller = getValue();
			puts("Cost to the Seller?");
			double cost_seller = getValue();
			double total_surplus = (value_buyers - amount_paid_buyers) + (amount_received_seller - cost_seller);
			printf("\nTotal Surplus: %G\n", total_surplus);
		}
		if (op == 16) {
			puts("Total Revenue?");
			double total_revenue = getValue();
			puts("Total Explicit cost or Expenses?");
			double expenses = getValue();
			double accounting_profit = total_revenue - expenses;
			printf("\nAccounting Profit: %G\n", accounting_profit);
		}
		if (op < 1 || op>16) {
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