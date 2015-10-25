#include <stdio.h>
#include <math.h>
#include "house_loan.h"

double constant_payment(int total, int month, double interest, t_mon_pay *pay_list) {
	double monthly_pay = 0.0;
	int i;

	total *= 10000;
	interest /= 100.0;
	interest /= 12;
	monthly_pay = total * interest * pow(1+interest, month) / (pow(1+interest, month) - 1);

	if (pay_list) {
		for (i = 0; i < month; i ++) {
			pay_list[i].interest = total * interest;
			pay_list[i].base     = monthly_pay - pay_list[i].interest;
			total -= pay_list[i].base;
		}
	}

	return monthly_pay;
}

int average_capital(int total, int month, double interest, t_mon_pay *pay_list) {
	return 0;
}

static double inc_list_sum(double base, double inc, int len) {
	if (inc < 0) {
		printf("[Error] Bad arguments!\n");
		return -1;
	}
	if (inc == 1) {
		return (base * len);
	} else {
		return (base * (1 - pow(inc, len)) / (1 - inc));
	}
}

static double math_calc(int year, double price, double year_rent, double inc_ratio) {
	return (price*pow(inc_ratio, year) - price + inc_list_sum(year_rent, inc_ratio, year));
}

static double newton_approach(int year, double price, double year_rent, double target) {
	double l = 1;
	double h = 10;
	double res = l;

	if (math_calc(year, price, year_rent, h) < target) {
		l = h;
		h *= 2;
	}

	do {
		double temp_val;
		res = (h - l) / 2 + l;
		temp_val = math_calc(year, price, year_rent, res);
		if (fabs(temp_val - target) < 1e-6) {
			break;
		}

		if (temp_val > target) {
			h = res;
		} else {
			l = res;
		}
	} while(1);
	return res;
}


// price * (1 + x)^n - price - loan_interest = down_pay * (1+invest_interest)^n - down_pay - sum(rent_pay)
// sum(rent_pay) = rent_pay*(1 - x^n)/(1 - x)
int loan_rent_compare(	int down_pay, int rent_pay,
						double invest_interest,
						int price, int year,
						t_mon_pay *pay_list) {
	double inc_ratio;
	double inv_income, rent_income, t_house_inc, buy_income;
	double loan_interest = 0;
	int i;

	down_pay *= 10000;
	price *= 10000;
	invest_interest /= 100.0;

	printf("rent pay: %d, year: %d\n", rent_pay, year);

	inv_income = down_pay* pow(1+invest_interest, year) - down_pay;
	for (i = 0; i < year * 12; i ++) {
		loan_interest += pay_list[i].interest;
	}

	t_house_inc = loan_interest + inv_income;
	inc_ratio = newton_approach(year, price, rent_pay*12, t_house_inc) - 1;
	rent_income = inv_income - inc_list_sum(rent_pay*12, 1+inc_ratio, year);
	buy_income = price*pow(1+inc_ratio, year) - price - loan_interest;

	printf("If buying house is better, need inc ratio is above %.3f%%\n", inc_ratio*100);
	printf("rent of the last year is %.2f, total rent pay is %.2f\n", rent_pay*pow(1+inc_ratio, year), inc_list_sum(rent_pay*12, 1+inc_ratio, year));
	printf("invest income is %.2f, rent income is %.2f\n", inv_income, rent_income);
	printf("house prive inc: %.2f\n", price*pow(1+inc_ratio, year) - price);
	printf("loan_interest: %.2f, buy_income: %.2f\n", loan_interest, buy_income);
	return 0;
}
