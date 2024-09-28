#include "errors.h"

void LogErrors(kState code) {
	printf("Error:\n");
	switch (code) {
		case kS_OK: {
			printf("Success!\n");
			break;
		}
		case kE_INVALID_INPUT: {
			printf("Invalid input\n");
			break;
		}
		case kE_INVALID_BASE: {
			printf("Invalid base for last number\n");
			break;
		}
		default: {
			printf("Unknown error\n");
			break;
		}
	}
}