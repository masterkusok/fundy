#include "constantCalculation.h"
#include "parsing.h"
#include "stdio.h"

int main(int argc, char** args) {
	double fault;
	int code = ParseArgs(argc, args, &fault);
	if (code != kS_OK) {
		LogErrors(code);
		return code;
	}

	printf("Calculation fault will be not more than %f\n", fault);

	printf("Constant calculation, using limits:\n");
	printf("e ~ %Lf\n", calculateLimit(fault, limitE));
	printf("pi ~ %Lf\n", calculateLimit(fault, limitPi));
	printf("ln2 ~ %Lf\n", calculateLimit(fault, limitLn2));
	printf("sqrt(2) ~ %Lf\n", calculateLimit(fault, limitSqrt2));
	printf("gamma ~ %Lf\n", calculateLimit(fault, limitGamma));
	printf("\n\n");

	printf("Constant calculation, using rows:\n");
	printf("e ~ %Lf\n", calculateRowE(fault));
	printf("pi ~ %Lf\n", calculateRowPi(fault));
	printf("ln2 ~ %Lf\n", calculateRowLn2(fault));
	printf("sqrt(2) ~ %Lf\n", calculateRowSqrt2(fault));
	printf("gamma ~ %Lf\n", calculateRowGamma(fault));
	printf("\n\n");

	printf("Constant calculation, using equatations:\n");
	printf("e ~ %Lf\n", solveEquatation(fault, eEquatation, 0.000001, 10.0));
	printf("pi ~ %Lf\n", piEquatation(fault));
	printf("ln2 ~ %Lf\n", solveEquatation(fault, ln2Equatation, 0.000001, 10.0));
	printf("sqrt(2) ~ %Lf\n", solveEquatation(fault, sqrt2Equatation, 0.000001, 10.0));
	printf("gamma ~ %Lf\n", solveEquatation(fault, gammaEquatation, 0.000001, 10.0));
	return 0;
}