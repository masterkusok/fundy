#include "handlers.h"

#include <math.h>

int myStrLen(char* input) {
	int length = 0;
	for (char* i = input; *i; i++) {
		if (*i == '\0') {
			break;
		}
		length++;
	}
	return length;
}

kState HandlerOptL(Input* input, char** result) {
	// вернём строковое представление длины, для удобства опиания callback'ов
	int length = myStrLen(input->strings[0]);
	int numberLength = (int)log10(length) + 1;
	char* output = malloc(sizeof(char) * (numberLength + 1));
	if (!output) {
		return kE_BAD_ALLOCATION;
	}
	output[numberLength] = '\0';
	for (int i = 1; i <= numberLength; i++) {
		output[numberLength - i] = '0' + length % 10;
		length /= 10;
	}
	*result = output;
	return kS_OK;
}

kState HandlerOptR(Input* input, char** output) {
	int length = myStrLen(input->strings[0]);
	char* out = malloc(sizeof(char) * (length + 1));
	if (!out) {
		return kE_BAD_ALLOCATION;
	}
	out[length] = '\0';
	for (int i = 1; i <= length; i++) {
		out[length - i] = input->strings[0][i - 1];
	}
	*output = out;
	return kS_OK;
}

kState HandlerOptU(Input* input, char** output) {
	int length = myStrLen(input->strings[0]);
	char* out = malloc(sizeof(char) * (length + 1));
	if (!out) {
		return kE_BAD_ALLOCATION;
	}
	out[length] = '\0';
	for (int i = 0; i < length; i++) {
		if (i % 2 == 1 && input->strings[0][i] <= 'z' && input->strings[0][i] >= 'a') {
			out[i] = input->strings[0][i] - 32;
		} else {
			out[i] = input->strings[0][i];
		}
	}
	*output = out;
	return kS_OK;
}

kState HandlerOptN(Input* input, char** output) {
	int length = 0;
	int alphaNum = 0;
	int digitNum = 0;

	for (char* i = input->strings[0]; *i; i++) {
		if (*i == '\0') {
			break;
		}
		if (*i <= 'z' && *i >= 'a' || *i >= 'A' && *i <= 'Z') {
			alphaNum++;
		} else if (*i <= '9' && *i >= '0') {
			digitNum++;
		}
		length++;
	}

	char* out = malloc(sizeof(char) * (length + 1));
	if (!out) {
		return kE_BAD_ALLOCATION;
	}
	out[length] = '\0';
	int digitPointer = 0, alphaPointer = digitNum, otherPointer = digitNum + alphaNum;
	for (int i = 0; i < length; i++) {
		if (input->strings[0][i] <= 'z' && input->strings[0][i] >= 'a' ||
			input->strings[0][i] >= 'A' && input->strings[0][i] <= 'Z') {
			out[alphaPointer] = input->strings[0][i];
			alphaPointer++;
		} else if (input->strings[0][i] <= '9' && input->strings[0][i] >= '0') {
			out[digitPointer] = input->strings[0][i];
			digitPointer++;
		} else {
			out[otherPointer] = input->strings[0][i];
			otherPointer++;
		}
	}
	*output = out;
	return kS_OK;
}

void shuffleStrings(char** array, int n) {
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		char* temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

kState HandlerOptC(Input* input, char** output) {
	int totalLen = 0;
	srand(input->seed);
	shuffleStrings(input->strings, input->stringsLen);

	for (int i = 0; i < input->stringsLen; i++) {
		totalLen += myStrLen(input->strings[i]);
	}

	char* out = malloc((totalLen + 1) * sizeof(char));
	if (!out) {
		return kE_BAD_ALLOCATION;
	}

	out[totalLen] = '\0';
	int ptr = 0;
	for (int i = 0; i < input->stringsLen; i++) {
		for (char* j = input->strings[i]; *j; j++) {
			out[ptr++] = *j;
		}
	}

	*output = out;
	return kS_OK;
}