#include <stdio.h>

#include "functions.h"

int main() {
	// double res = calculatePolynom(2.0, 4, 5.0, 4.0, 3.0, 2.0, 1.0);
	// printf("%lf\n", res);

	// bool res = isConvexPolygon(4, 0.0, 0.0, 4.0, 0.0, 1.0, 1.0, 0.0, 3.0);
	// if (res) {
	// 	printf("convex");
	// } else {
	// 	printf("not convex");
	// }

	kState code;
	bool* result = findKaprekarNumbers(&code, 10, 3, "8", "45", "297");
	if (code != kS_OK) {
		return code;
	}
	
	// for (int i = 0; i < 3; i++) {
	// 	printf("%d\n", result[i]);
	// }

	return 0;
}