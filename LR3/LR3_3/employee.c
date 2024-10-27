#include "employee.h"

kValidationError ValidateEmployee(Employee *employee) {
    if (!employee->Name) {
        return kEMPTY_NAME;
    }

    if (!employee->Surname) {
        return kEMPTY_SURNAME;
    }

    if (employee->Salary < 0.0) {
        return kNEGATIVE_SALARY;
    }

    for (char *i = employee->Name; *i; i++) {
        if (((*i > 'Z' || *i < 'A') && (*i > 'z' || *i < 'a'))) {
            return kINVALID_NAME;
        }
    }

    for (char *i = employee->Name; *i; i++) {
        if (((*i > 'Z' || *i < 'A') && (*i > 'z' || *i < 'a'))) {
            return kINVALID_SURNAME;
        }
    }

    return kVALID;
}

Employee *NewEmployee(uint64_t id, char *name, char *surname, double salary) {
    Employee *result = malloc(sizeof(Employee));
    if (!result) {
        return NULL;
    }

    result->ID = id;
    result->Name = strdup(name);
    if (!result->Name) {
        free(result);
        return NULL;
    }

    result->Surname = strdup(surname);
    if (!result->Surname) {
        free(result->Name);
        free(result);
        return NULL;
    }

    result->Salary = salary;
    return result;
}


void DestroyEmployee(Employee *employee) {
    free(employee->Name);
    free(employee->Surname);
    free(employee);
}