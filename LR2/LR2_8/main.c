#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 1000

typedef enum { kS_OK, kE_BAD_ALLOC, kE_INVALID_ARG } kState;

int charToValue(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
	if (c >= 'a' && c <= 'z') return c - 'a' + 10;
	return -1;
}

char valueToChar(int value) {
	if (value >= 0 && value <= 9) return '0' + value;
	if (value >= 10 && value <= 35) return 'A' + (value - 10);
	return '?';
}

kState baseToDigits(char *numberStr, int base, uint8_t digits[]) {
	if (!numberStr || base < 2 || base > 36) {
		return kE_INVALID_ARG;
	}

	int len = strlen(numberStr);
	memset(digits, 0, MAX_DIGITS * sizeof(uint8_t));

	for (int i = 0; i < len; i++) {
		int value = charToValue(numberStr[i]);
		if (value >= base || value < 0) {
			return kE_INVALID_ARG;
		}

		int carry = value;
		for (int j = 0; j < MAX_DIGITS; j++) {
			carry += digits[j] * base;
			digits[j] = carry % base;
			carry /= base;
		}
	}

	return kS_OK;
}

kState addLargeNumbers(uint8_t result[], uint8_t num1[], uint8_t num2[], int base) {
	int carry = 0;
	for (int i = 0; i < MAX_DIGITS; i++) {
		int sum = num1[i] + num2[i] + carry;
		result[i] = sum % base;
		carry = sum / base;
	}

	return kS_OK;
}

void printLargeNumber(uint8_t digits[], int base) {
	int i = MAX_DIGITS - 1;
	while (i >= 0 && digits[i] == 0) {
		i--;
	}

	if (i == -1) {
		printf("0");
	} else {
		for (; i >= 0; i--) {
			printf("%c", valueToChar(digits[i]));
		}
	}
	printf("\n");
}

kState sumBigNumbers(int base, int count, ...) {
	if (base < 2 || base > 36) {
		return kE_INVALID_ARG;
	}

	va_list args;
	va_start(args, count);

	uint8_t *sum = (uint8_t *)malloc(MAX_DIGITS * sizeof(uint8_t));
	if (!sum) {
		return kE_BAD_ALLOC;
	}
	memset(sum, 0, MAX_DIGITS * sizeof(uint8_t));

	for (int i = 0; i < count; i++) {
		char *numberStr = va_arg(args, char *);

		uint8_t *currentNumber = (uint8_t *)malloc(MAX_DIGITS * sizeof(uint8_t));
		if (!currentNumber) {
			free(sum);
			return kE_BAD_ALLOC;
		}

		kState state = baseToDigits(numberStr, base, currentNumber);
		if (state != kS_OK) {
			free(currentNumber);
			free(sum);
			return state;
		}

		state = addLargeNumbers(sum, sum, currentNumber, base);
		free(currentNumber);
		if (state != kS_OK) {
			free(sum);
			return state;
		}
	}

	va_end(args);

	printf("Sum: ");
	printLargeNumber(sum, base);
	free(sum);

	return kS_OK;
}

int main() {
	kState state;

	state = sumBigNumbers(2, 3, "101", "110", "11");
	if (state != kS_OK) {
		printf("Error occurred: %d\n", state);
	}

	state = sumBigNumbers(16, 3, "1A", "F", "23");
	if (state != kS_OK) {
		printf("Error occurred: %d\n", state);
	}

	return 0;
}
