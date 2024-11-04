#ifndef LR3_4_POST_H
#define LR3_4_POST_H

#include "mail.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    Address *CurrentAddress;
    Vector *Mails;
} Post;


Post *CreatePost(Address *);

void DisplayAllMails(Post *);

bool RemoveElement(Post *, char *);

Mail *FindElement(Post *, char *);

void FindExpiredMails(Post *);

void DestroyPost(Post *);

#endif
