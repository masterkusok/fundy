#include "vector.h"

#include "vector.h"

Vector *CreateVector(int initialCapacity) {
    Vector *v = malloc(sizeof(Vector));
    if (!v) {
        return NULL;
    }

    v->buffer = malloc(sizeof(Mail *) * initialCapacity);
    if (!v->buffer) {
        return NULL;
    }

    v->capacity = initialCapacity;
    v->len = 0;
    return v;
}

void DestroyVector(Vector *v) {
    for (int i = 0; i < v->len; i++) {
        DestroyMail(v->buffer[i]);
    }
    free(v->buffer);
    free(v);
}

int compareMail(Mail *m1, Mail *m2) {
    if (StringEqual(m1->Receiver->PostIndex, m2->Receiver->PostIndex)) {
        return StringComp(m1->ID, m2->ID);
    }
    return StringComp(m1->Receiver->PostIndex, m2->Receiver->PostIndex);
}

bool VectorPush(Vector *v, Mail *value) {
    if (v->len + 1 >= v->capacity) {
        Mail **newBuffer = malloc(v->capacity * sizeof(Mail *) * 2);
        if (!newBuffer) {
            return false;
        }
        for (int i = 0; i < v->len; i++) {
            newBuffer[i] = v->buffer[i];
        }
        free(v->buffer);
        v->buffer = newBuffer;
        v->capacity *= 2;
    }

    int low = 0, high = v->len - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (compareMail(v->buffer[mid], value) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    for (int i = v->len; i > low; i--) {
        v->buffer[i] = v->buffer[i - 1];
    }

    v->buffer[low] = value;
    v->len++;

    return true;
}

void VectorPop(Vector *v, int index) {
    DestroyMail(v->buffer[index]);
    for (int i = index; i + 1 < v->len; i++) {
        v->buffer[i] = v->buffer[i + 1];
    }
    v->len--;
}
