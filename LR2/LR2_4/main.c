#include <stdio.h>

#include "functions.h"

int main() {
	double res = calculatePolynom(2.0, 4, 5.0, 4.0, 3.0, 2.0, 1.0);
	printf("%lf\n", res);
	return 0;
}