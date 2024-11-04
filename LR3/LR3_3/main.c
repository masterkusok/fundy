#include <stdio.h>
#include <string.h>
#include "employee.h"
#include "vector.h"
#include "arguments.h"

kState ParseFile(const char *path, Vector *result) {
    FILE *in = fopen(path, "r");
    if (!in) {
        return kE_CANNOT_OPEN_FILE;
    }
    uint64_t id;
    char *name;
    char *surname;
    double salary;


    while (fscanf(in, "%lu %ms %ms %lf", &id, &name, &surname, &salary) == 4) {
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

    if (fscanf(in, "%lu %ms %ms %lf", &id, &name, &surname, &salary) != EOF) {
        fclose(in);
        return kE_PARSING_ERROR;
    }

    fclose(in);
    return kS_OK;
}

kState WriteResult(Vector *v, const char *path) {
    FILE *out = fopen(path, "w");
    if (!out) {
        return kE_CANNOT_OPEN_FILE;
    }
    FprintVector(v, out);
    fclose(out);
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
    kState code = ParseFile(args->InputPath, vector);
    if (code != kS_OK) {
        DestroyVector(vector);
        free(args);
        return code;
    }

    ComparatorCallback comparators[2];
    comparators[kOptA] = ascendingComp;
    comparators[kOptD] = descendingComp;

    SortVector(vector, comparators[args->Option]);
    code = WriteResult(vector, args->OutputPath);
    if (code != kS_OK) {
        DestroyVector(vector);
        free(args);
        return code;
    }
    DestroyVector(vector);
    free(args);
    return 0;
}
