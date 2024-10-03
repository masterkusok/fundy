#include "callbacks.h"

void HandleOptR(char* file1, char* file2, char* output) {
	FILE* in1 = fopen(file1, "r");
	FILE* in2 = fopen(file2, "r");
	FILE* out = fopen(output, "w");
	char ch1, ch2;

	if (!in1 || !in2 || !out) {
		fclose(in1);
		fclose(in2);
		fclose(out);
		return;
	}

	while ((ch1 = fgetc(in1)) != EOF && (ch2 = fgetc(in2)) != EOF) {
		while (ch1 == ' ' || ch1 == '\t' || ch1 == '\n') {
			if (ch1 == EOF) {
				break;
			}
			ch1 = fgetc(in1);
		}

		while (ch1 != ' ' && ch1 != '\t' && ch1 != '\n') {
			if (ch1 == EOF) {
				break;
			}
			fputc(ch1, out);
			ch1 = fgetc(in1);
		}
		fputc(' ', out);

		while (ch2 == ' ' || ch2 == '\t' || ch2 == '\n') {
			if (ch2 == EOF) {
				break;
			}
			ch2 = fgetc(in2);
		}
		while (ch2 != ' ' && ch2 != '\t' && ch2 != '\n') {
			if (ch2 == EOF) {
				break;
			}
			fputc(ch2, out);
			ch2 = fgetc(in2);
		}
		fputc(' ', out);
	}

	while ((ch1 = fgetc(in1)) != EOF) {
		while (ch1 == ' ' || ch1 == '\t' || ch1 == '\n') {
			if (ch1 == EOF) {
				break;
			}
			ch1 = fgetc(in1);
		}
		while (ch1 != ' ' && ch1 != '\t' && ch1 != '\n') {
			if (ch1 == EOF) {
				break;
			}
			fputc(ch1, out);
			ch1 = fgetc(in1);
		}
		fputc(' ', out);
	}
	while ((ch2 = fgetc(in2)) != EOF) {
		while (ch2 == ' ' || ch2 == '\t' || ch2 == '\n') {
			if (ch2 == EOF) {
				break;
			}
			ch2 = fgetc(in2);
		}
		while (ch2 != ' ' && ch2 != '\t' && ch2 != '\n') {
			if (ch2 == EOF) {
				break;
			}
			fputc(ch2, out);
			ch2 = fgetc(in2);
		}
		fputc(' ', out);
	}

	fclose(in1);
	fclose(in2);
	fclose(out);
}

int toBase(int number, int base) {
	int result = 0, mult = 1;
	while (number > 0) {
		result += mult * (number % base);
		mult *= 10;
		number /= base;
	}
	return result;
}

void HandleOptA(char* file1, char* file2, char* output) {
	FILE* in = fopen(file1, "r");
	FILE* out = fopen(output, "w");
	if (in && out) {
		int num = 1;
		char ch;
		char current[99];
		int currentLen = 0;
		while ((ch = fgetc(in)) != EOF) {
			if (currentLen > 99) {
				printf("Found lexema with length over 99\n");
				currentLen = 0;
				break;
			}
			if (ch != ' ' && ch != '\t' && ch != '\n') {
				current[currentLen] = ch;
				currentLen++;
				continue;
			}

			if (currentLen == 0) {
				continue;
			}

			if (num % 10 == 0) {
				for (int i = 0; i < currentLen; i++) {
					if (current[i] <= 'z' && current[i] >= 'a') {
						fprintf(out, "%d", toBase(current[i], 4));
					}
					if (current[i] <= 'Z' && current[i] >= 'A') {
						fprintf(out, "%d", toBase(current[i] + 32, 4));
					} else {
						fputc(current[i], out);
					}
				}
			} else if (num % 5 == 0) {
				for (int i = 0; i < currentLen; i++) {
					if ((current[i] >= 'a' && current[i] <= 'z') || (current[i] >= 'A' && current[i] <= 'Z')) {
						fprintf(out, "%d", toBase(current[i], 8));
					} else {
						fprintf(out, "%c", current[i]);
					}
				}
			} else if (num % 2 == 0) {
				for (int i = 0; i < currentLen; i++) {
					if (current[i] <= 'Z' && current[i] >= 'A') {
						fprintf(out, "%c", current[i] + 32);
					} else {
						fputc(current[i], out);
					}
				}
			} else {
				for (int i = 0; i < currentLen; i++) {
					fputc(current[i], out);
				}
			}
			fputc(' ', out);
			num++;
			memset(current, 0, sizeof(current));
			currentLen = 0;
		}

		if (currentLen != 0) {
			if (num % 10 == 0) {
				for (int i = 0; i < currentLen; i++) {
					if (current[i] <= 'z' && current[i] >= 'a') {
						fprintf(out, "%d", toBase(current[i], 4));
					}
					if (current[i] <= 'Z' && current[i] >= 'A') {
						fprintf(out, "%d", toBase(current[i] + 32, 4));
					} else {
						fputc(current[i], out);
					}
				}
			} else if (num % 5 == 0) {
				for (int i = 0; i < currentLen; i++) {
					if ((current[i] >= 'a' && current[i] <= 'z') || (current[i] >= 'A' && current[i] <= 'Z')) {
						fprintf(out, "%d", toBase(current[i], 8));
					} else {
						fprintf(out, "%c", current[i]);
					}
				}
			} else if (num % 2 == 0) {
				for (int i = 0; i < currentLen; i++) {
					if (current[i] <= 'Z' && current[i] >= 'A') {
						fprintf(out, "%c", current[i] + 32);
					} else {
						fputc(current[i], out);
					}
				}
			} else {
				for (int i = 0; i < currentLen; i++) {
					fputc(current[i], out);
				}
			}
		}
	}
	fclose(in);
	fclose(out);
}