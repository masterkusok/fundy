#include "functions.h"

int main() {
	char* result;
	oversprintf(result, "%Zr", 88, 16);
    printf(result);
	return 0;
}