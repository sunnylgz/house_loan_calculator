#ifndef _HOUSE_LOAN_H
#define _HOUSE_LOAN_H

#include <math.h>

typedef struct {
	double base;
	double interest;
} t_mon_pay;

double constant_payment(int total, int month, double interest, t_mon_pay *pay_list);
int average_capital(int total, int month, double interest, t_mon_pay *pay_list);

#endif // _HOUSE_LOAN_H
