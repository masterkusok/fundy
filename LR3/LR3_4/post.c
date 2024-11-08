#include "post.h"

Post *CreatePost(Address *current) {
    Post *post = malloc(sizeof(Post));
    if (!post) {
        return NULL;
    }
    post->CurrentAddress = current;
    post->Mails = CreateVector(2);
    if (!post->Mails) {
        free(post);
        return NULL;
    }
    return post;
}

void DisplayAllMails(Post *p) {
    for (int i = 0; i < p->Mails->len; i++) {
        PrintMail(p->Mails->buffer[i]);
    }
}

Mail *FindElement(Post *post, char *id) {
    String *compare = NewString(id);
    for (int i = 0; i < post->Mails->len; i++) {
        if (StringEqual(post->Mails->buffer[i]->ID, compare)) {
            DeleteString(compare);
            return post->Mails->buffer[i];
        }
    }
    DeleteString(compare);
    return NULL;
}

void FindDeliveredMails(Post *p) {
    printf("\nДоставленные отправления\n");
    for (int i = 0; i < p->Mails->len; i++) {
        if (p->Mails->buffer[i]->Delivered) {
            PrintMail(p->Mails->buffer[i]);
        }
    }
}

void FindExpiredMails(Post *p) {
    printf("\nПросроченные отправления\n");
    time_t now = time(NULL);
    struct tm sysTime = {0};

    localtime_r(&now, &sysTime);

    for (int i = 0; i < p->Mails->len; i++) {
        struct tm creationTime = {0};
        char *receiveTimeStr = p->Mails->buffer[i]->ReceiveTime->buffer;
        sscanf(receiveTimeStr, "%d:%d:%d %d:%d:%d",
               &creationTime.tm_mday, &creationTime.tm_mon, &creationTime.tm_year,
               &creationTime.tm_hour, &creationTime.tm_min, &creationTime.tm_sec);
        creationTime.tm_mon -= 1;
        creationTime.tm_year -= 1900;

        time_t creationTimeEpoch = mktime(&creationTime);

        if (difftime(now, creationTimeEpoch) > 0) {
            PrintMail(p->Mails->buffer[i]);
        }
    }
}


bool RemoveElement(Post *post, char *id) {
    String *compare = NewString(id);
    for (int i = 0; i < post->Mails->len; i++) {
        if (StringEqual(post->Mails->buffer[i]->ID, compare)) {
            VectorPop(post->Mails, i);
            DeleteString(compare);
            return true;
        }
    }
    DeleteString(compare);
    return false;
}

void DestroyPost(Post *p) {
    DestroyVector(p->Mails);
    DestroyAddress(p->CurrentAddress);
    free(p);
}