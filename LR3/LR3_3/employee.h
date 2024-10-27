#ifndef LR3_3_EMPLOYEE_H
#define LR3_3_EMPLOYEE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint64_t ID;
    char* Name;
    char* Surname;
    double Salary;
} Employee;

typedef enum {
    kVALID,
    kEMPTY_NAME,
    kEMPTY_SURNAME,
    kINVALID_NAME,
    kINVALID_SURNAME,
    kNEGATIVE_SALARY
} kValidationError;

void DestroyEmployee(Employee*);
Employee* NewEmployee(uint64_t, char*, char*, double);
kValidationError ValidateEmployee(Employee*);

#endif
