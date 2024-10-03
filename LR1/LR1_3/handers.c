#include "handers.h"

void solveEquatation(double a, double b, double c, double epsilon) {
	printf("Checking permutation: %lf %lf %lf\n", a, b, c);
	double discriminant = b * b - 4 * a * c;

	if (fabs(discriminant) < epsilon) {
		discriminant = 0;
	}

	if (discriminant < 0) {
		printf("No solutions\n");
	} else if (fabs(discriminant) < epsilon) {
		double root = -b / (2 * a);
		printf("Single solution: %lf\n", root);
	} else {
		double root1 = (-b + sqrt(discriminant)) / (2 * a);
		double root2 = (-b - sqrt(discriminant)) / (2 * a);
		printf("Two solutions: %lf and %lf\n", root1, root2);
	}
}

void handlerOptQ(double* nums) {
	double epsilon = nums[0], a = nums[1], b = nums[2], c = nums[3];
	double permutations[6][3] = {
		{a, b, c}, {a, c, b}, {b, a, c}, {b, c, a}, {c, b, a}, {c, a, b},
	};

	for (int i = 0; i < 6; i++) {
		solveEquatation(permutations[i][0], permutations[i][1], permutations[i][2], epsilon);
	}
}

void handlerOptM(double* nums) {
	int a = (int)nums[0], b = (int)nums[1];
	int compA = a, compB = b;
	if (a < 0) {
		compA *= -1;
	}
	if (b < 0) {
		compB *= -1;
	}

	if (b == 0) {
		printf("number b cant be 0\n");
		return;
	}
	for (int i = 1; compB * i <= compA; i++) {
		if (compB * i == compA) {
			printf("Yes, %d is multiple of %d\n", a, b);
			return;
		}
	}
	printf("No, %d is not multiple of %d\n", a, b);
}

void handlerOptT(double* nums) {
	double epsilon = nums[0], a = nums[1], b = nums[2], c = nums[3];
	if (a == 0 || a < 0 || b < epsilon || b < 0 || c < epsilon || c < 0) {
		printf("No, input values cant be sides of a triangle\n");
		return;
	}
	if (fabs(a * a - b * b - c * c) < epsilon || fabs(b * b - a * a - c * c) < epsilon ||
		fabs(c * c - b * b - a * a) < epsilon) {
		printf("Yes, input values can be sides of a triangle\n");
		return;
	}

	printf("No, input values cant be sides of a triangle\n");
}