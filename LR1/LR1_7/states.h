#ifndef STATES_H
#define STATES_H

typedef enum {
	kS_OK,
	kE_BAD_ALLOCATION,
	kE_INVALID_NUMBER_OF_ARGS,
	kE_UNKNOWN_FLAG,
	kE_INVALID_FLAG,
	kE_FILE_NOT_EXIST
} kState;

#endif