#include "functions.h"

void logErrors(kState code) {
	switch (code) {
		case kE_INVALID_ARGUMENT: {
			printf("error: invalid argument\n");
			break;
		}
		case kE_TYPE_OVERFLOW: {
			printf("error: type overflow\n");
			break;
		}
		case kE_BAD_ALLOCATION: {
			printf("error: bad malloc\n");
			break;
		}
		default: {
			printf("unknown error code\n");
			break;
		}
	}
}

int getRotateDirection(double ax, double ay, double bx, double by, double cx, double cy) {
	double abx = bx - ax;
	double aby = by - ay;
	double bcx = cx - bx;
	double bcy = cy - by;
	double prod = abx * bcy - aby * bcx;
	if (prod > 0.0) {
		return 1;
	} else if (prod < 0.0) {
		return -1;
	}
	return 0;
}

bool isConvexPolygon(int numPoints, ...) {
	if (numPoints < 3) return false;

	va_list args;
	va_start(args, numPoints);

	double x1, y1, x2, y2, x3, y3, firstX, firstY, secondX, secondY;

	x1 = firstX = va_arg(args, double);
	y1 = firstY = va_arg(args, double);
	x2 = secondX = va_arg(args, double);
	y2 = secondY = va_arg(args, double);
	x3 = va_arg(args, double);
	y3 = va_arg(args, double);

	int currentDirection = getRotateDirection(x1, y1, x2, y2, x3, y3);

	for (int i = 3; i < numPoints; i++) {
		x1 = x2;
		x2 = x3;
		y1 = y2;
		y2 = y3;
		x3 = va_arg(args, double);
		y3 = va_arg(args, double);
		int dir = getRotateDirection(x1, y1, x2, y2, x3, y3);

		if (dir == 0) {
			continue;
		}
		if (dir != currentDirection) {
			va_end(args);
			return false;
		}
	}
	va_end(args);

	return getRotateDirection(x2, y2, x3, y3, firstX, firstY) == currentDirection &&
		   getRotateDirection(x3, y3, firstX, firstY, secondX, secondY) == currentDirection;
}

// k5 * x^5 + k4 * x^4 + k3 * x^3 + k2*x^2 + k1*x + k0  --- считаем таким спсобом
// x(x(x(x(k5*x+k4) + k3) + k2) + k1) + k0

kState calculatePolynom(double *result, double x, int n, ...) {
	va_list args;
	va_start(args, n);
	double current = 0.0;
	for (int i = 0; i <= n; i++) {
		double k = va_arg(args, double);
		current *= x;
		if (current > DBL_MAX || current < -DBL_MAX) {
			return kE_TYPE_OVERFLOW;
		}
		current += k;
		if (current > DBL_MAX || current < -DBL_MAX) {
			return kE_TYPE_OVERFLOW;
		}
	}
	va_end(args);
	*result = current;
	return kS_OK;
}

// проверка чисел Капрекара

int parseToDecimal(const char *str, int base) {
	int num = 0;
	while (*str) {
		char digit = *str++;
		int value;

		if (digit >= '0' && digit <= '9') {
			value = digit - '0';
		} else if (digit >= 'A' && digit <= 'Z') {
			value = digit - 'A' + 10;
		} else if (digit >= 'a' && digit <= 'z') {
			value = digit - 'a' + 10;
		} else {
			return -1;
		}

		if (value >= base) {
			return -1;
		}

		num = num * base + value;
	}
	return num;
}

void convertFromDecimal(int num, int base, char *result) {
	char buffer[65];
	int index = 0;

	while (num > 0) {
		int remainder = num % base;
		buffer[index++] = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'A');
		num /= base;
	}

	for (int i = 0; i < index; i++) {
		result[i] = buffer[index - i - 1];
	}
	result[index] = '\0';
}

char *substring(const char *str, int index, kState *code) {
	if (index < 0 || index > strlen(str)) {
		return NULL;
	}

	char *result = malloc((index + 1) * sizeof(char));
	if (result == NULL) {
		*code = kE_BAD_ALLOCATION;
		return NULL;
	}

	strncpy(result, str, index);
	result[index] = '\0';

	return result;
}

bool isKaprekar(int num, int base, kState *code) {
	if (num == 1) return true;

	int square = num * num;
	char squareStr[65];
	convertFromDecimal(square, base, squareStr);

	int len = strlen(squareStr);
	for (int i = 1; i < len; i++) {
		int left = 0, right = 0;
		char *leftSubstr = substring(squareStr, i, code);
		if (*code != kS_OK) {
			return false;
		}
		left = parseToDecimal(leftSubstr, base);
		right = parseToDecimal(squareStr + i, base);

		if (right > 0 && left + right == num) {
			return true;
		}
	}
	return false;
}

bool *findKaprekarNumbers(kState *code, int base, int numArgs, ...) {
	*code = kS_OK;
	va_list args;
	va_start(args, numArgs);
	bool *kaprekars = malloc(sizeof(bool) * numArgs);
	if (!kaprekars) {
		*code = kE_BAD_ALLOCATION;
		return NULL;
	}
	for (int i = 0; i < numArgs; i++) {
		const char *strNum = va_arg(args, const char *);
		int decimalNum = parseToDecimal(strNum, base);
		if (decimalNum < 0) {
			*code = kE_INVALID_ARGUMENT;
			free(kaprekars);
			return NULL;
		}
		kaprekars[i] = isKaprekar(decimalNum, base, code);
		if (*code != kS_OK) {
			free(kaprekars);
			return NULL;
		}
	}

	va_end(args);
	return kaprekars;
}