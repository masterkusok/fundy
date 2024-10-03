#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"

int fromBase(char num[99], int len, int base) {
	int result = 0;
	len--;
	for (int i = len; i >= 0; i--) {
		if (i == 0 && num[i] == '-') {
			return -result;
		}
		int mult = 0;
		if ('0' <= num[i] && num[i] <= '9') {
			mult = num[i] - '0';
		} else if ('A' <= num[i] && num[i] <= 'Z') {
			mult = num[i] - 55;
		} else if ('a' <= num[i] && num[i] <= 'z') {
			mult = num[i] - 87;
		}
		result += pow(base, len - i) * mult;
	}
	return result;
}

void writeInBase(int decimalNum, int base) {
	printf("In base %d:\n", base);
	int currentLen = 0;
	char str[99];
	if (decimalNum < 0) {
		printf("-");
		decimalNum *= -1;
	}
	while (decimalNum > 0) {
		int currentDigit = decimalNum % base;
		if (currentDigit <= 9) {
			str[currentLen] = '0' + currentDigit;
		} else {
			str[currentLen] = 'A' + (currentDigit - 10);
		}
		currentLen++;
		decimalNum /= base;
	}
	for (int i = currentLen - 1; i >= 0; i--) {
		printf("%c", str[i]);
	}

	printf("\n");
}

int main(int argc, char** args) {
	int base;
	fscanf(stdin, "%d", &base);
	if (base < 2 || base > 36) {
		printf("Base is out of bounds [2..36]");
		return 1;
	}
	char c;
	char current[99];
	int currentLen = 0;
	int max = INT_MIN;
	kState code = kS_OK;
	while (true) {
		memset(current, 0, sizeof(current));
		currentLen = 0;

		while ((c = getchar()) != '\n' && c != '\t' && c != ' ') {
			current[currentLen] = c;
			currentLen++;
		}
		if (currentLen == 0) {
			continue;
		}

		if (currentLen == 4 && strncmp(current, "Stop", 4) == 0) {
			code = kS_OK;
			break;
		}

		// валидируем прочитанное слово. Ищем инородные символы + чекаем минимальное основание системы счисления
		for (int i = 0; i < currentLen; i++) {
			if (current[i] == '-' && i == 0) {
				continue;
			} else if (current[i] <= '9' && current[i] >= '0') {
				if (current[i] - '0' >= base) {
					code = kE_INVALID_BASE;
				}
			} else if (current[i] >= 'A' && current[i] <= 'Z') {
				if (current[i] - 'A' + 10 >= base) {
					code = kE_INVALID_BASE;
				}
			} else {
				code = kE_INVALID_INPUT;
				break;
			}
		}

		if (code != kS_OK) {
			break;
		}

		int decimal = fromBase(current, currentLen, base);
		if (abs(decimal) > abs(max)) {
			max = decimal;
		}
	}

	if (code != kS_OK) {
		LogErrors(code);
		return code;
	}

	printf("Max:\n");
	writeInBase(max, base);
	for (int i = 1; i < 5; i++) {
		writeInBase(max, 9 * i);
	}

	return 0;
}