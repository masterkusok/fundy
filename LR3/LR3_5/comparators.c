#include "comparators.h"

int compareById(const void *a, const void *b) {
    const Student *studentA = *(const Student **) a;
    const Student *studentB = *(const Student **) b;
    return (int) studentA->ID - (int) studentB->ID;
}

int compareByLastName(const void *a, const void *b) {
    const Student *studentA = *(const Student **) a;
    const Student *studentB = *(const Student **) b;
    return strcmp(studentA->LastName, studentB->LastName);
}

int compareByFirstName(const void *a, const void *b) {
    const Student *studentA = *(const Student **) a;
    const Student *studentB = *(const Student **) b;
    return strcmp(studentA->FirstName, studentB->FirstName);
}

int compareByGroup(const void *a, const void *b) {
    const Student *studentA = *(const Student **) a;
    const Student *studentB = *(const Student **) b;
    return strcmp(studentA->Group, studentB->Group);
}

bool idCriteria(Student* student, void* id) {
    unsigned int target = *(unsigned int*) id;
    return student->ID == target;
}

bool lastNameCriteria(Student* student, void* id) {
    char* target = (char*) id;
    return !strcmp(target, student->LastName);
}

bool firstNameCriteria(Student* student, void* id) {
    char* target = (char*) id;
    return !strcmp(target, student->FirstName);
}

bool groupCriteria(Student* student, void* id) {
    char* target = (char*) id;
    return !strcmp(target, student->Group);
}