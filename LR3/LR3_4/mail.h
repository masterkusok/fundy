#ifndef LR3_4_MAIL_H
#define LR3_4_MAIL_H

#include "string.h"
#include <stdio.h>

typedef struct {
    String *City, *Street, *Building, *PostIndex;
    unsigned short House, Flat;
} Address;

typedef struct {
    Address *Receiver;
    double Weight;
    String *ID, *CreationTime, *ReceiveTime;
} Mail;

Address *CreateAddress(char *city, char *street, unsigned short house, unsigned short flat, char *building,
                       char *postIndex);

Mail *CreateMail(Address *address, double weight, char *id, char *create, char *receive);

bool ValidateAddress(Address *);

bool ValidateMail(Mail *);

void PrintAddress(Address *);

void PrintMail(Mail *);

void DestroyAddress(Address *);

void DestroyMail(Mail *);

#endif