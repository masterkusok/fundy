#include <limits.h>
#include <time.h>

#include "parseArgs.h"
#include "vector.h"

const int ARR_LEN = 10;

void PrintArray(int* array) {
	for (int i = 0; i < ARR_LEN; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void MaxMinOnePass(int* array) {
	int max = INT_MIN, min = INT_MAX, maxIndex = 0, minIndex = 0;
	for (int i = 0; i < ARR_LEN; i++) {
		if (array[i] < min) {
			min = array[i];
			minIndex = i;
		}
		if (array[i] > max) {
			max = array[i];
			maxIndex = i;
		}
	}
	printf("Max: %d\nMin: %d\n", max, min);
	int temp = array[minIndex];
	array[minIndex] = array[maxIndex];
	array[maxIndex] = temp;
	printf("Index swaped!\n");
}

int main(int argc, char** args) {
	int a, b;
	kState code = ParseArgs(argc, args, &a, &b);

	if (code != kS_OK) {
		LogErrors(code);
		return code;
	}

	srand(time(NULL));
	printf("Point 1\n");
	int array[ARR_LEN];
	for (int i = 0; i < ARR_LEN; i++) {
		array[i] = a + rand() % b;
	}
	PrintArray(array);
	MaxMinOnePass(array);
	PrintArray(array);

	printf("Point 2\n");
	int sizeA = 10 + rand() % 9991, sizeB = 10 + rand() % 9991;
	// int sizeA = 10, sizeB = 3;
	Vector* A = CreateVector(sizeA);
	Vector* B = CreateVector(sizeB);

	for (int i = 0; i < sizeA; i++) {
		VectorPush(A, -1000 + rand() % 2001);
	}

	for (int i = 0; i < sizeB; i++) {
		VectorPush(B, -1000 + rand() % 2001);
	}
	PrintVector(A);
	PrintVector(B);

	Vector* C = CreateVector(sizeA);
	Iterator* iter = CreateIterator(A);
	while (!IterIsLast(iter)) {
		int valueA = IterValue(iter);
		int currentClosest = 0;
		int currentDistance = INT_MAX;
		Iterator* subIter = CreateIterator(B);
		while (!IterIsLast(subIter)) {
			int valueB = IterValue(subIter);
			if (abs(valueA - valueB) < currentDistance) {
				currentClosest = valueB;
				currentDistance = abs(valueA - valueB);
			}
			IterNext(subIter);
		}
		DestroyIterator(subIter);
		VectorPush(C, valueA + currentClosest);
		IterNext(iter);
	}

	PrintVector(C);
	DestroyVector(C);
	DestroyVector(A);
	DestroyVector(B);
	DestroyIterator(iter);
	return 0;
}