#include <stdio.h>

#include "functions.h"

int main() {
	// double res;
	// kState code = calculatePolynom(&res, 2.0, 4, 1.0, 1.0, 1.0, 1.0, 1.0);
	// if (code != kS_OK) {
	// 	return code;
	// }
	// printf("%lf\n", res);

	bool resultB = isConvexPolygon(6, 1.0, 2.0, 2.0, 4.0, 4.0, 4.0, 5.0, 2.0, 3.0, 1.0, 3.0, 2.0);
	if (resultB) {
		printf("convex");
	} else {
		printf("not convex");
	}

	// // kState code;
	// // bool* result = findKaprekarNumbers(&code, 10, 1, "8");
	// // if (code != kS_OK) {
	// // 	return code;
	// // }

	// // for (int i = 0; i < 1; i++) {
	// // 	printf("%d\n", result[i]);
	// // }

	// return 0;
}