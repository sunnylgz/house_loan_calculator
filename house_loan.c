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
}
