#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXAMS 5

typedef enum {
    kS_OK,
    kE_CAN_NOT_OPEN_FILE,
    kE_BAD_ALLOC
} kState;

typedef struct {
    unsigned int id;
    char *firstName;
    char *lastName;
    char *group;
    unsigned char *grades;
} Student;

kState readStudents(const char *filePath, Student **studentsPtr, int *studentCount) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        return kE_CAN_NOT_OPEN_FILE;
    }

    Student *students = NULL;
    *studentCount = 0;

    while (!feof(file)) {
        students = realloc(students, (*studentCount + 1) * sizeof(Student));
        if (students == NULL) {
            fclose(file);
            return kE_BAD_ALLOC;
        }

        Student *student = &students[*studentCount];
        student->grades = malloc(EXAMS * sizeof(unsigned char));
        if (student->grades == NULL) {
            fclose(file);
            return kE_BAD_ALLOC;
        }

        fscanf(file, "%u %ms %ms %ms", &student->id, &student->firstName, &student->lastName, &student->group);
        for (int i = 0; i < EXAMS; ++i) {
            fscanf(file, "%hhu", &student->grades[i]);
        }

        (*studentCount)++;
    }

    fclose(file);
    *studentsPtr = students;
    return kS_OK;
}

int compareById(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return studentA->id - studentB->id;
}

int compareByLastName(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return strcmp(studentA->lastName, studentB->lastName);
}

int compareByFirstName(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return strcmp(studentA->firstName, studentB->firstName);
}

int compareByGroup(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return strcmp(studentA->group, studentB->group);
}

void sortStudents(Student *students, int count, int (*comparator)(const void*, const void*)) {
    qsort(students, count, sizeof(Student), comparator);
}

void printStudentToFile(FILE *file, const Student *student) {
    fprintf(file, "ID: %u\nФамилия: %s\nИмя: %s\nГруппа: %s\n", student->id, student->lastName, student->firstName, student->group);
    fprintf(file, "Оценки: ");
    for (int i = 0; i < EXAMS; ++i) {
        fprintf(file, "%hhu ", student->grades[i]);
    }
    fprintf(file, "\n");
}

double calculateAverageGrade(const Student *student) {
    int sum = 0;
    for (int i = 0; i < EXAMS; ++i) {
        sum += student->grades[i];
    }
    return (double)sum / EXAMS;
}

Student *findStudentById(Student *students, int count, unsigned int id) {
    for (int i = 0; i < count; ++i) {
        if (students[i].id == id) {
            return &students[i];
        }
    }
    return NULL;
}

Student *findStudentByLastName(Student *students, int count, const char *lastName) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            return &students[i];
        }
    }
    return NULL;
}

Student *findStudentByFirstName(Student *students, int count, const char *firstName) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(students[i].firstName, firstName) == 0) {
            return &students[i];
        }
    }
    return NULL;
}

Student *findStudentByGroup(Student *students, int count, const char *group) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(students[i].group, group) == 0) {
            return &students[i];
        }
    }
    return NULL;
}

void DestroyStudent(Student *student) {
    free(student->firstName);
    free(student->lastName);
    free(student->group);
    free(student->grades);
}

void writeStudentsWithAboveAverage(FILE *file, Student *students, int count, double avg) {
    fprintf(file, "Студенты с оценками выше среднего балла:\n");
    for (int i = 0; i < count; ++i) {
        double studentAvg = calculateAverageGrade(&students[i]);
        if (studentAvg > avg) {
            fprintf(file, "Фамилия: %s, Имя: %s\n", students[i].lastName, students[i].firstName);
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

    int studentCount;
    Student *students;

    kState result = readStudents(inputFile, &students, &studentCount);
    if (result != kS_OK) {
        if (result == kE_CAN_NOT_OPEN_FILE) {
            fprintf(stderr, "Ошибка: не удалось открыть файл %s\n", inputFile);
        } else if (result == kE_BAD_ALLOC) {
            fprintf(stderr, "Ошибка: не удалось выделить память\n");
        }
        return EXIT_FAILURE;
    }

    FILE *output = fopen(outputFile, "w");
    if (output == NULL) {
        fprintf(stderr, "Ошибка: не удалось открыть выходной файл %s\n", outputFile);
        return EXIT_FAILURE;
    }

    int command;
    while (1) {
        printf("\nКоманды:\n");
        printf("1. Поиск по ID\n");
        printf("2. Поиск по фамилии\n");
        printf("3. Поиск по имени\n");
        printf("4. Поиск по группе\n");
        printf("5. Сортировка\n");
        printf("6. Вывести студентов с оценками выше среднего\n");
        printf("7. Выход\n");
        printf("Введите номер команды: ");
        scanf("%d", &command);

        if (command == 1) {
            unsigned int idToFind;
            printf("Введите ID студента: ");
            scanf("%u", &idToFind);

            Student *foundStudent = findStudentById(students, studentCount, idToFind);
            if (foundStudent) {
                printStudentToFile(output, foundStudent);
            } else {
                fprintf(output, "Студент с ID %u не найден\n", idToFind);
            }

        } else if (command == 2) {
            char lastName[50];
            printf("Введите фамилию студента: ");
            scanf("%s", lastName);

            Student *foundStudent = findStudentByLastName(students, studentCount, lastName);
            if (foundStudent) {
                printStudentToFile(output, foundStudent);
            } else {
                fprintf(output, "Студент с фамилией %s не найден\n", lastName);
            }

        } else if (command == 3) {
            char firstName[50];
            printf("Введите имя студента: ");
            scanf("%s", firstName);

            Student *foundStudent = findStudentByFirstName(students, studentCount, firstName);
            if (foundStudent) {
                printStudentToFile(output, foundStudent);
            } else {
                fprintf(output, "Студент с именем %s не найден\n", firstName);
            }

        } else if (command == 4) {
            char group[50];
            printf("Введите группу студента: ");
            scanf("%s", group);

            Student *foundStudent = findStudentByGroup(students, studentCount, group);
            if (foundStudent) {
                printStudentToFile(output, foundStudent);
            } else {
                fprintf(output, "Студент из группы %s не найден\n", group);
            }

        } else if (command == 5) {
            printf("Сортировка по:\n");
            printf("1. ID\n");
            printf("2. Фамилии\n");
            printf("3. Имени\n");
            printf("4. Группе\n");
            printf("Введите номер критерия сортировки: ");
            int sortOption;
            scanf("%d", &sortOption);

            if (sortOption == 1) {
                sortStudents(students, studentCount, compareById);
            } else if (sortOption == 2) {
                sortStudents(students, studentCount, compareByLastName);
            } else if (sortOption == 3) {
                sortStudents(students, studentCount, compareByFirstName);
            } else if (sortOption == 4) {
                sortStudents(students, studentCount, compareByGroup);
            }

            for (int i = 0; i < studentCount; ++i) {
                printStudentToFile(output, &students[i]);
            }

        } else if (command == 6) {
            double totalAvg = 0.0;
            for (int i = 0; i < studentCount; ++i) {
                totalAvg += calculateAverageGrade(&students[i]);
            }
            totalAvg /= studentCount;

            writeStudentsWithAboveAverage(output, students, studentCount, totalAvg);

        } else if (command == 7) {
            break;
        }
    }

    fclose(output);

    for (int i = 0; i < studentCount; ++i) {
        DestroyStudent(&students[i]);
    }
    free(students);

    return EXIT_SUCCESS;
}
