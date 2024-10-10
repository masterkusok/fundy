#ifndef STATES_H
#define STATES_H

typedef enum {
	kS_OK,
	kE_INVALID_NUMBER_OF_ARGS,
	kE_INVALID_ARG,
	kE_UNKNOWN_FLAG,
	kE_BAD_ALLOCATION,
} kState;

#endif