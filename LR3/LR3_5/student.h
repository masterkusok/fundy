#ifndef LR3_5_STUDENT_H
#define LR3_5_STUDENT_H

#include <stdlib.h>
#include <string.h>

#define EXAMS 5

typedef struct {
    unsigned int ID;
    char *FirstName;
    char *LastName;
    char *Group;
    unsigned char *Grades;
} Student;

Student *NewStudent(unsigned int, char *, char *, char *, unsigned char *);

Student *CopyStudent(const Student *);

void DestroyStudent(Student *);

#endif
