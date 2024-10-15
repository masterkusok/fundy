#include "equatationCalculation.h"
#include "limitCalculation.h"
#include "parsing.h"
#include "rowCalculation.h"
#include "stdio.h"

int main(int argc, char** args) {
	double epsilon;
	int code = ParseArgs(argc, args, &epsilon);
	if (code != kS_OK) {
		LogErrors(code);
		return code;
	}

	long double resultL;
	printf("Calculation epsilon will be not more than %f\n", epsilon);
	code = limitE(epsilon, &resultL);
	if (code != kS_OK) {
		LogErrors(code);
	} else {
		printf("e ~ %Lf\n", resultL);
	}

	code = limitPi(epsilon, &resultL);
	if (code != kS_OK) {
		LogErrors(code);
	} else {
		printf("pi ~ %Lf\n", resultL);
	}

	code = limitLn2(epsilon, &resultL);
	if (code != kS_OK) {
		LogErrors(code);
	} else {
		printf("ln2 ~ %Lf\n", resultL);
	}

	code = limitSqrt2(epsilon, &resultL);
	if (code != kS_OK) {
		LogErrors(code);
	} else {
		printf("sqrt(2) ~ %Lf\n", resultL);
	}

	code = limitGamma(epsilon, &resultL);
	if (code != kS_OK) {
		LogErrors(code);
	} else {
		printf("gamma ~ %Lf\n", resultL);
	}

	printf("\n\n");
	printf("Constant calculation, using rows:\n");
	double result;
	code = calculateRow(&result, 0, 1, rowDeltaE, epsilon);
	if (code != kS_OK) {
		LogErrors(code);
	} else {
		printf("e ~ %lf\n", result);
	}

	code = calculateRow(&result, 1, 4, rowDeltaPi, epsilon);
	if (code != kS_OK) {
		LogErrors(code);
	} else {
		printf("pi ~ %lf\n", result);
	}

	code = calculateRow(&result, 1, 1, rowDeltaLn2, epsilon);
	if (code != kS_OK) {
		LogErrors(code);
	} else {
		printf("ln2 ~ %lf\n", result);
	}

	code = calculateSqrt2Row(&result, epsilon);
	if (code != kS_OK) {
		LogErrors(code);
	} else {
		printf("sqrt2 ~ %lf\n", result);
	}

	printf("gamma ~ %Lf\n", calculateRowGamma(epsilon));
	printf("\n\n");

	printf("Constant calculation, using equatations:\n");
	printf("e ~ %Lf\n", solveEquatation(epsilon, eEquatation, 0.000001, 10.0));
	printf("pi ~ %Lf\n", solveEquatation(epsilon, piEquatation, M_PI / 4.0, 7.0 * M_PI / 4.0));
	printf("ln2 ~ %Lf\n", solveEquatation(epsilon, ln2Equatation, 0.000001, 10.0));
	printf("sqrt(2) ~ %Lf\n", solveEquatation(epsilon, sqrt2Equatation, 0.000001, 10.0));
	printf("gamma ~ %Lf\n", solveEquatation(epsilon, gammaEquatation, 0.000001, 10.0));
	return 0;
}