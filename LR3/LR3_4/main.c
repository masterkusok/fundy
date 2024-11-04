#include <stdio.h>
#include "string.h"
#include "mail.h"
#include "post.h"

#define MAX_STRING_SIZE 256

Address *inputAddressData() {
    char city[MAX_STRING_SIZE];
    char street[MAX_STRING_SIZE];
    char building[MAX_STRING_SIZE];
    char postIndex[7];
    unsigned short house, flat;

    printf("Введите город получателя: ");
    scanf("%s", city);

    printf("Введите улицу получателя: ");
    scanf("%s", street);

    printf("Введите номер дома: ");
    scanf("%hd", &house);

    printf("Введите корпус (если есть): ");
    scanf("%s", building);

    printf("Введите номер квартиры: ");
    scanf("%hd", &flat);

    printf("Введите индекс получателя (6 символов): ");
    scanf("%6s", postIndex);

    return CreateAddress(city, street, house, flat, building, postIndex);
}

Mail *inputMailData() {
    char id[15];
    char creationTime[20];
    char receiveTime[20];
    double weight;

    printf("Введите идентификатор (14 символов): ");
    scanf("%14s", id);

    printf("Введите вес посылки: ");
    scanf("%lf", &weight);

    getchar();
    printf("Введите время создания (dd:MM:yyyy hh:mm:ss): ");
    fgets(creationTime, 20, stdin);

    getchar();
    printf("Введите время вручения (dd:MM:yyyy hh:mm:ss): ");
    fgets(receiveTime, 20, stdin);

    Address *addr = inputAddressData();
    if (!addr) {
        printf("Ошибка при создании адреса.\n");
        return NULL;
    }

    return CreateMail(addr, weight, id, creationTime, receiveTime);
}

void interactiveDialog(Post *post) {
    int choice;
    char identifier[15];

    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавить отправление\n");
        printf("2. Удалить отправление\n");
        printf("3. Найти отправление по идентификатору\n");
        printf("4. Показать все отправления\n");
        printf("5. Найти все просроченные отправления\n");
        printf("0. Выйти\n");
        printf("Выберите опцию: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                Mail *mail = inputMailData();
                if (!mail) {
                    printf("Ошибка при добавлении отправления.\n");
                }
                else if (!ValidateMail(mail)) {
                    DestroyMail(mail);
                    printf("Введены некорректные данные\n");
                }
                else {
                    VectorPush(post->Mails, mail);
                    printf("Почта успешно добавлена.\n");
                }
                break;
            }
            case 2:
                printf("Введите идентификатор для удаления: ");
                scanf("%14s", identifier);
                if (RemoveElement(post, identifier) == true) {
                    printf("Отправление удалено.\n");
                } else {
                    printf("Отправление с идентификатором %s не найдено.\n", identifier);
                }
                break;
            case 3:
                printf("Введите идентификатор для поиска: ");
                scanf("%14s", identifier);
                Mail *m = FindElement(post, identifier);
                if (m != NULL) {
                    PrintMail(m);
                } else {
                    printf("Отправление не найдено\n");
                }
                break;
            case 4:
                DisplayAllMails(post);
                break;
            case 5:
                FindExpiredMails(post);
                break;
            case 0:
                printf("Выход из программы.\n");
                return;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
}

int main(void) {
    if (freopen("../input.txt", "r", stdin) == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }
    Address *postAddress = inputAddressData();
    Post *post = CreatePost(postAddress);
    interactiveDialog(post);
    DestroyPost(post);
    fclose(stdin);
    return 0;
}
