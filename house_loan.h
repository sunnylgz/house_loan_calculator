#ifndef _HOUSE_LOAN_H
#define _HOUSE_LOAN_H

#include <math.h>

typedef struct {
	double base;
	double interest;
} t_mon_pay;

double constant_payment(int total, int month, double interest, t_mon_pay *pay_list);
int average_capital(int total, int month, double interest, t_mon_pay *pay_list);

// function: loan_rent_compare()
// description: compare the loan of buying house w/ that rent one.
//		set the same increasing ratio between rent and house price
int loan_rent_compare(int down_pay, int rent_pay, double invest_interest, int price, int year, t_mon_pay *pay_list);

#endif // _HOUSE_LOAN_H
