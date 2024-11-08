#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "vector.h"
#include "comparators.h"

typedef enum {
    kS_OK,
    kE_CAN_NOT_OPEN_FILE,
    kE_BAD_ALLOC
} kState;

kState readStudents(const char *filePath, Vector *students) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        return kE_CAN_NOT_OPEN_FILE;
    }

    while (!feof(file)) {
        unsigned int id;
        char *firstName;
        char *lastName;
        char *group;

        unsigned char *grades = malloc(EXAMS * sizeof(unsigned char));
        if (grades == NULL) {
            fclose(file);
            return kE_BAD_ALLOC;
        }

        fscanf(file, "%u %ms %ms %ms", &id, &firstName, &lastName, &group);
        for (int i = 0; i < EXAMS; ++i) {
            fscanf(file, "%hhu", &grades[i]);
        }
        Student *student = NewStudent(id, firstName, lastName, group, grades);
        VectorPush(students, student);
    }

    fclose(file);
    return kS_OK;
}

void sortStudents(Vector *students, int (*comparator)(const void *, const void *)) {
    qsort(students->buffer, students->len, sizeof(Student *), comparator);
}

void FprintStudentsToFile(FILE *file, Vector *students) {
    for (int i = 0; i < students->len; i++) {
        fprintf(file, "ID: %u\nФамилия: %s\nИмя: %s\nГруппа: %s\n", students->buffer[i]->ID,
                students->buffer[i]->LastName, students->buffer[i]->FirstName,
                students->buffer[i]->Group);
        fprintf(file, "Оценки: ");
        for (int j = 0; j < EXAMS; ++j) {
            fprintf(file, "%hhu ", students->buffer[i]->Grades[j]);
        }
        fprintf(file, "\n");
    }
}

double calculateAverageGrade(const Student *student) {
    int sum = 0;
    for (int i = 0; i < EXAMS; ++i) {
        sum += student->Grades[i];
    }
    return (double) sum / EXAMS;
}

void FprintAboveAverage(FILE *file, Vector *students, double average) {
    fprintf(file, "Студенты, с средним баллом выше среднего:\n");
    for (int i = 0; i < students->len; i++) {
        double studAverage = calculateAverageGrade(students->buffer[i]);
        if (studAverage < average) {
            continue;
        }
        fprintf(file, "ID: %u\nФамилия: %s\nИмя: %s\nГруппа: %s\n", students->buffer[i]->ID,
                students->buffer[i]->LastName, students->buffer[i]->FirstName,
                students->buffer[i]->Group);
        fprintf(file, "Оценки: ");
        for (int i = 0; i < EXAMS; ++i) {
            fprintf(file, "%hhu ", students->buffer[i]->Grades[i]);
        }
        fprintf(file, "\n");
    }
}

Vector *findStudentsByCriteria(Vector *students, StudentCriteria criteria, void *arg) {
    Vector *result = CreateVector(2);
    if (!result) {
        return NULL;
    }
    for (int i = 0; i < students->len; ++i) {
        if (criteria(students->buffer[i], arg)) {
            VectorPush(result, CopyStudent(students->buffer[i]));
        }
    }
    return result;
}

void interactiveDialogue(Vector *students, FILE *output) {
    StudentCriteria criterias[4] = {
            idCriteria,
            lastNameCriteria,
            firstNameCriteria,
            groupCriteria,
    };

    StudentComparator comparators[4] = {
            compareById,
            compareByLastName,
            compareByFirstName,
            compareByGroup,
    };

    int command;
    while (1) {
        printf("\nКоманды:\n");
        printf("1. Поиск\n");
        printf("2. Сортировка\n");
        printf("3. Вывести студентов с оценками выше среднего\n");
        printf("4. Выход\n");
        printf("Введите номер команды: ");
        scanf("%d", &command);

        if (command == 1) {
            printf("Поиск по:\n");
            printf("1. ID\n");
            printf("2. Фамилии\n");
            printf("3. Имени\n");
            printf("4. Группе\n");
            printf("Введите номер критерия поиска: ");
            int searchOption;
            scanf("%d", &searchOption);
            if (searchOption < 1 || searchOption > 4) {
                printf("Неверный критерий поиска\n");
                continue;
            }
            void *searchArg;
            switch (searchOption) {
                case 1: {
                    unsigned int id;
                    if (!scanf("%u", &id)) {
                        printf("Ошибка ввода критерия");
                        continue;
                    };
                    searchArg = &id;
                    break;
                }
                case 2: {
                    char *lastName;
                    if (!scanf("%ms", &lastName)) {
                        printf("Ошибка ввода критерия");
                        continue;
                    };
                    searchArg = lastName;
                    break;
                }
                case 3: {
                    char *name;
                    if (!scanf("%ms", &name)) {
                        printf("Ошибка ввода критерия");
                        continue;
                    }
                    searchArg = name;
                    break;
                }
                case 4: {
                    char *group;
                    if (!scanf("%ms", &group)) {
                        printf("Ошибка ввода критерия");
                        continue;
                    }
                    searchArg = group;
                    break;
                }
                default: {
                    searchArg = NULL;
                    printf("unknown option");
                    break;
                }
            }
            Vector *filtered = findStudentsByCriteria(students, criterias[searchOption - 1], searchArg);
            if (searchOption != 1) {
                free(searchArg);
            }
            FprintStudentsToFile(output, filtered);
            DestroyVector(filtered);
        } else if (command == 2) {
            printf("Сортировка по:\n");
            printf("1. ID\n");
            printf("2. Фамилии\n");
            printf("3. Имени\n");
            printf("4. Группе\n");
            printf("Введите номер критерия сортировки: ");
            int searchOption;
            scanf("%d", &searchOption);
            if (searchOption < 1 || searchOption > 4) {
                printf("Неверный критерий сортировки\n");
                continue;
            }
            sortStudents(students, comparators[searchOption - 1]);
            FprintStudentsToFile(output, students);
        } else if (command == 3) {
            double average = 0;
            for (int i = 0; i < students->len; i++) {
                average += calculateAverageGrade(students->buffer[i]) / students->len;
            }
            FprintAboveAverage(output, students, average);
        } else if (command == 4) {
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Использование: %s <файл студентов> <выходной файл>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *inputFile = argv[1];
    const char *outputFile = argv[2];

    Vector *students = CreateVector(2);

    kState result = readStudents(inputFile, students);
    if (result != kS_OK) {
        if (result == kE_CAN_NOT_OPEN_FILE) {
            fprintf(stderr, "Ошибка: не удалось открыть файл %s\n", inputFile);
        } else {
            fprintf(stderr, "Ошибка: не удалось выделить память\n");
        }
        DestroyVector(students);
        return EXIT_FAILURE;
    }

    FILE *output = fopen(outputFile, "w");
    if (output == NULL) {
        fprintf(stderr, "Ошибка: не удалось открыть выходной файл %s\n", outputFile);
        DestroyVector(students);
        return EXIT_FAILURE;
    }

    interactiveDialogue(students, output);
    fclose(output);
    DestroyVector(students);
    printf("exit\n");
    return EXIT_SUCCESS;
}
