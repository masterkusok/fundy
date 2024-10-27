#include <stdio.h>
#include <string.h>
#include "employee.h"
#include "vector.h"
#include "arguments.h"

#define DEFAULT_BUFFER_SIZE 512

kState ParseFile(const char *path, Vector *result) {
    FILE *in = fopen(path, "r");
    if (!in) {
        return kE_CANNOT_OPEN_FILE;
    }
    char buffer[DEFAULT_BUFFER_SIZE];
    while (fgets(buffer, DEFAULT_BUFFER_SIZE, in)) {
        uint64_t id;
        char name[128];
        char surname[128];
        double salary;
        if (sscanf(buffer, "%lu %s %s %lf", &id, name, surname, &salary) != 4) {
            fclose(in);
            return kE_PARSING_ERROR;
        }
        Employee *employee = NewEmployee(id, name, surname, salary);
        if (!employee) {
            fclose(in);
            return kE_BAD_ALLOCATION;
        }
        kValidationError err = ValidateEmployee(employee);
        if (err != kVALID) {
            fclose(in);
            return KE_VALIDATION_ERROR;
        }
        VectorPush(result, employee);
    }

    fclose(in);
    return kS_OK;
}

int descendingComp(const void *a, const void *b) {
    const Employee *first = *((const Employee **) a);
    const Employee *second = *((const Employee **) b);
    if (first->Salary != second->Salary) {
        return first->Salary < second->Salary ? 1 : -1;
    }
    int comp = strcmp(first->Surname, second->Surname);
    if (comp != 0) {
        return comp;
    }
    comp = strcmp(first->Name, second->Name);
    if (comp != 0) {
        return comp;
    }
    return first->ID < second->ID;
}

int ascendingComp(const void *a, const void *b) {
    const Employee *first = *((const Employee **) a);
    const Employee *second = *((const Employee **) b);
    if (first->Salary != second->Salary) {
        return first->Salary > second->Salary ? 1 : -1;
    }
    int comp = strcmp(first->Surname, second->Surname);
    if (comp != 0) {
        return -comp;
    }
    comp = strcmp(first->Name, second->Name);
    if (comp != 0) {
        return -comp;
    }
    return first->ID > second->ID;
}

int main(int argc, char **argv) {
    Args *args = ParseArgs(argc, argv);
    if (!args) {
        return kE_BAD_ALLOCATION;
    }

    if (args->State != kS_OK) {
        return args->State;
    }

    Vector *vector = CreateVector(2);
    kState code = ParseFile(args->Path, vector);
    if (code != kS_OK) {
        return code;
    }

    ComparatorCallback comparators[2];
    comparators[kOptA] = ascendingComp;
    comparators[kOptD] = descendingComp;

    SortVector(vector, comparators[args->Option]);
    PrintVector(vector);
    DestroyVector(vector);
    free(args);
    return 0;
}
