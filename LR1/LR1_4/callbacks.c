#include "callbacks.h"

void HandleOptD(char* input, char* output) {
	FILE* in = fopen(input, "r");
	FILE* out = fopen(output, "w");
	char ch;

	if (in && out) {
		while ((ch = fgetc(in)) != EOF) {
			if (ch < '0' || ch > '9') {
				fputc(ch, out);
			}
		}
	}
	fclose(in);
	fclose(out);
}

void HandleOptI(char* input, char* output) {
	FILE* in = fopen(input, "r");
	FILE* out = fopen(output, "w");
	char ch;
	int count = 0;

	if (in && out) {
		while ((ch = fgetc(in)) != EOF) {
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				count++;
			} else if (ch == '\n') {
				fprintf(out, "%d\n", count);
				count = 0;
			}
		}
		if (count > 0) fprintf(out, "%d\n", count);
	}
	fclose(in);
	fclose(out);
}

void HandleOptS(char* input, char* output) {
	FILE* in = fopen(input, "r");
	FILE* out = fopen(output, "w");
	char ch;
	int count = 0;

	if (in && out) {
		while ((ch = fgetc(in)) != EOF) {
			if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == ' ' ||
				  ch == '\n')) {
				if (ch == '\n') {
					count--;
				}
				count++;
			}
			if (ch == '\n') {
				fprintf(out, "%d\n", count);
				count = 0;
			}
		}
		if (count >= 0) {
			fprintf(out, "%d\n", count);
		}
	}
	fclose(in);
	fclose(out);
}

void writeInBase(int decimalNum, int base, FILE* output) {
	int currentLen = 0;
	char str[3];
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
		fputc(str[i], output);
	}
}

void HandleOptA(char* input, char* output) {
	FILE* in = fopen(input, "r");
	FILE* out = fopen(output, "w");
	char ch;

	if (in && out) {
		while ((ch = fgetc(in)) != EOF) {
			if (ch >= '0' && ch <= '9') {
				fputc(ch, out);
			} else {
				writeInBase(ch, 16, out);
			}
		}
	}
	fclose(in);
	fclose(out);
}