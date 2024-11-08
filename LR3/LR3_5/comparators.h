#ifndef LR3_5_COMPARATORS_H
#define LR3_5_COMPARATORS_H

#include "stdbool.h"
#include "student.h"
#include "string.h"

typedef int (*StudentComparator)(const void *, const void *);

typedef bool (*StudentCriteria)(Student *, void *);

int compareById(const void *, const void *);

int compareByLastName(const void *, const void *);

int compareByFirstName(const void *, const void *);

int compareByGroup(const void *, const void *);

bool idCriteria(Student *student, void *id);

bool lastNameCriteria(Student *student, void *id);

bool firstNameCriteria(Student *student, void *id);

bool groupCriteria(Student *student, void *id);

#endif
