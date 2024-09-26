#include "callbacks.h"

int fromBase(char num[99], int len, int base) {
	int result = 0;
	len--;
	for (int i = len; i >= 0; i--) {
		int mult = 0;
		if ('0' <= num[i] <= '9') {
			mult = num[i] - '0';
		} else {
			mult = num[i] - 7 - '0';
		}
		result += pow(base, len - i) * mult;
	}
	return result;
}

kState Handle(char* inputFile, char* outputFile) {
	FILE* in = fopen(inputFile, "r");
	FILE* out = fopen(outputFile, "w");

	if (!in || !out) {
		return kE_FILE_NOT_EXIST;
	}

	char ch;
	int minBase = 0;
	char current[99];
	int currentLen = 0;
	while ((ch = fgetc(in)) != EOF) {
		if (ch == ' ' || ch == '\t' || ch == '\n') {
			if (currentLen == 0) {
				continue;
			}

			int i = 0;
			while (current[i] == '0' && i + 1 < currentLen) {
				i++;
			}

			while (i < currentLen) {
				fputc(current[i], out);
				i++;
			}
			minBase++;
			if (minBase == 1) {
				fprintf(out, " 2 0\n");
				continue;
			}
			int base10 = fromBase(current, currentLen, minBase);
			fprintf(out, " %d %d\n", minBase, base10);
			memset(current, 0, sizeof(current));
			currentLen = 0;
			minBase = 0;
			continue;
		}

		if (ch >= '0' && ch <= '9') {
			if (ch - '0' > minBase) {
				// Для каждого числа, ищем символ с максимальным ASCII-кодом - так мы сможем определить основание
				// минимальной системы счисления
				minBase = ch - '0';
			}
		} else if (ch >= 'a' && ch <= 'z') {
			if (ch - 39 - '0' > minBase) {
				minBase = ch - '0' - 39;
			}
		} else if (ch >= 'A' && ch <= 'Z') {
			if (ch - 7 - '0' > minBase) {
				minBase = ch - 7 - '9';
			}
		} else {
			fclose(in);
			fclose(out);
			return kE_INVALID_FILE_CONTENT;
		}

		current[currentLen] = ch;
		currentLen++;
	}

	fclose(in);
	fclose(out);

	return kS_OK;
}