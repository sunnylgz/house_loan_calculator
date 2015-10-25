#include <stdio.h>
#include <stdlib.h>
#include "house_loan.h"
//#include "common.h"

#define YEAR_PERIOD 20
#define PROVIDENT_FUND 50
#define COMMERCIAL_LOAN 90
#define PRO_INTEREST 3.25f
#define COM_INTEREST 4.9f
#define INV_INTEREST 3.0f
#define RENT_PRICE_RATIO 15		// (div 10000)

int print_pay_list(t_mon_pay *pay_list, int month) {
	int i;
	double total = .0;
	double base_total = .0;
	double interest_total = .0;

	if (pay_list == NULL || month <= 0) {
		printf("[Error] Bad arguments!\n");
		return -1;
	}

	printf("time\t\tmonth pay\tbase\t\tinterest\n");
	for (i = 0; i < month; i++) {
		printf("Y %2d m %2d\t%8.2f\t%8.2f\t%8.2f\n",
				i/12+1, i%12+1, pay_list[i].base+pay_list[i].interest, pay_list[i].base, pay_list[i].interest);
		total          += pay_list[i].base + pay_list[i].interest;
		base_total     += pay_list[i].base;
		interest_total += pay_list[i].interest;
	}


	printf("\ntotal:\t\t%f\n", total);
	printf("base total:\t%f\n", base_total);
	printf("interest total:\t%f\n", interest_total);

	return 0;
}
int main() {
	int loan_year = YEAR_PERIOD;
	int month = loan_year * 12;
	int provident_fund_part = PROVIDENT_FUND;
	int commercial_loan_part = COMMERCIAL_LOAN;
	int price = (provident_fund_part + commercial_loan_part) * 10 / 7;
	int rent_pay = price * RENT_PRICE_RATIO;
	int down_pay = price * 3 / 10;
	double monthly_pay;
	int year = 5;       // used to compare buying & renting
	int i;
	t_mon_pay *pay_list = NULL;
	t_mon_pay *pay_list2 = NULL;

	pay_list = (t_mon_pay*)malloc(2*month * sizeof(*pay_list));
	if (pay_list == NULL) {
		printf("[Error] allocate memory for pay_list failed!\n");
		return -1;
	}

	pay_list2 = pay_list + month;
	monthly_pay = constant_payment(provident_fund_part, month, PRO_INTEREST, pay_list);
	monthly_pay += constant_payment(commercial_loan_part, month, COM_INTEREST, pay_list2);
	for (i = 0; i < month; i++) {
		pay_list[i].base     += pay_list2[i].base;
		pay_list[i].interest += pay_list2[i].interest;
	}

	printf("constant payment: month pay is %.2f\n", monthly_pay);
	print_pay_list(pay_list, month);

	printf("compare buying & renting house\n");
	rent_pay = (rent_pay < 1500)? 1500: rent_pay;
	loan_rent_compare(down_pay, rent_pay, INV_INTEREST, price, year, pay_list);

	free(pay_list);
	return 0;
}
