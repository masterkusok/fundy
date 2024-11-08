#include "mail.h"

bool validateDateStr(const char *dateStr) {
    for (int i = 0; i < 19; i++) {
        if (i == 2 || i == 5) {
            if (dateStr[i] != ':') {
                return false;
            }
        } else if (i == 10) {
            if (dateStr[i] != ' ') {
                return false;
            }
        } else if (i == 13 || i == 16) {
            if (dateStr[i] != ':') {
                return false;
            }
        } else {
            if (dateStr[i] > '9' || dateStr[i] < '0') {
                return false;
            }
        }
    }

    int day = (dateStr[0] - '0') * 10 + (dateStr[1] - '0');
    int month = (dateStr[3] - '0') * 10 + (dateStr[4] - '0');
    int year =
            (dateStr[6] - '0') * 1000 + (dateStr[7] - '0') * 100 + (dateStr[8] - '0') * 10 + (dateStr[9] - '0');
    int hour = (dateStr[11] - '0') * 10 + (dateStr[12] - '0');
    int minute = (dateStr[14] - '0') * 10 + (dateStr[15] - '0');
    int second = (dateStr[17] - '0') * 10 + (dateStr[18] - '0');

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31 || hour < 0 || hour > 23 || minute < 0 ||
        minute > 59 || second < 0 || second > 59) {
        return false;
    }
    int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[1] = 29;
    }

    if (day > days_in_month[month - 1]) {
        return false;
    }

    return true;
}

bool ValidateAddress(Address *address) {
    if (!address->City->Len) {
        return false;
    }

    if (!address->Street->Len) {
        return false;
    }

    if (address->PostIndex->Len != 6) {
        return false;
    }

    for (int i = 0; i < address->PostIndex->Len; i++) {
        if (address->PostIndex->buffer[i] > '9' || address->PostIndex->buffer[i] < '0') {
            return false;
        }
    }
    return true;
}

bool ValidateMail(Mail *mail) {
    if (!ValidateAddress(mail->Receiver)) {
        return false;
    }

    if (mail->Weight <= 0.0) {
        return false;
    }

    if (mail->ID->Len != 14) {
        return false;
    }

    for (int i = 0; i < mail->ID->Len; i++) {
        if (mail->ID->buffer[i] > '9' || mail->ID->buffer[i] < '0') {
            return false;
        }
    }

    if (!validateDateStr(mail->CreationTime->buffer)) {
        return false;
    }

    if (!validateDateStr(mail->CreationTime->buffer)) {
        return false;
    }

    return true;
}

void PrintAddress(Address *addr) {
    printf("Адресс %s\n %s\n %u\n %s\n %u\n %s\n", addr->City->buffer, addr->Street->buffer,
           addr->House, addr->Building->buffer, addr->Flat, addr->PostIndex->buffer);
}

void PrintMail(Mail *mail) {
    printf("Письмо %s:\n", mail->ID->buffer);
    printf("Время отправления: %s\nВремя получения: %s\nВес: %lfкг\n", mail->CreationTime->buffer,
           mail->ReceiveTime->buffer, mail->Weight);
    PrintAddress(mail->Receiver);
}

Address *CreateAddress(char *city, char *street, unsigned short house, unsigned short flat, char *building,
                       char *postIndex) {
    Address *result = malloc(sizeof(Address));
    if (!result) {
        return NULL;
    }
    result->City = NewString(city);
    result->Street = NewString(street);
    result->House = house;
    result->Flat = flat;
    result->Building = NewString(building);
    result->PostIndex = NewString(postIndex);
    return result;
}

Mail *CreateMail(Address *address, double weight, char *id, char *create, char *receive) {
    Mail *result = malloc(sizeof(Mail));
    if (!result) {
        return NULL;
    }
    result->Delivered = false;
    result->Receiver = address;
    result->Weight = weight;
    result->ID = NewString(id);
    result->CreationTime = NewString(create);
    result->ReceiveTime = NewString(receive);
    return result;
}

void DestroyAddress(Address *a) {
    DeleteString(a->PostIndex);
    DeleteString(a->Street);
    DeleteString(a->City);
    DeleteString(a->Building);
    free(a);
}

void DestroyMail(Mail *m) {
    DestroyAddress(m->Receiver);
    DeleteString(m->ID);
    DeleteString(m->CreationTime);
    DeleteString(m->ReceiveTime);
    free(m);
}