#include "student.h"

void DestroyStudent(Student *student) {
    free(student->FirstName);
    free(student->LastName);
    free(student->Group);
    free(student->Grades);
    free(student);
}

Student *NewStudent(unsigned int id, char *firstName, char *lastName, char *group, unsigned char *grades) {
    Student *result = malloc(sizeof(Student));
    if (!result) {
        return NULL;
    }
    result->ID = id;
    result->FirstName = firstName;
    result->LastName = lastName;
    result->Group = group;
    result->Grades = grades;
    return result;
}

Student *CopyStudent(const Student *student) {
    Student *result = malloc(sizeof(Student));
    if (!result) {
        return NULL;
    }
    unsigned char *buffer = malloc(sizeof(unsigned char) * EXAMS);
    if (!buffer) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < EXAMS; i++) {
        buffer[i] = student->Grades[i];
    }
    result->Grades = buffer;
    result->ID = student->ID;
    result->FirstName = strdup(student->FirstName);
    result->LastName = strdup(student->LastName);
    result->Group = strdup(student->Group);
    return result;
}