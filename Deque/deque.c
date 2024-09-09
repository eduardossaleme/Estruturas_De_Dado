#include "deque.h"
#include <stdlib.h>

struct Deque{
    void **arr;
    int start;
    int end;
    int allocated,size;
};

Deque *deque_construct() {
    Deque *f = (Deque *)calloc(1, sizeof(Deque));
    f->allocated = 100;
    f->arr = (void** )calloc(100, sizeof(void*));
    f->start = 0;
    f->end = 0;
    f->size = 0;
    return f;
}

void deque_push_back(void *v, void* item) {
    Deque* f = (Deque*)v;
    if (f->size == f->allocated) {
        f->arr = (void **)realloc(f->arr, (f->allocated + 20) * sizeof(void*));
        f->allocated += 20;
    }
    f->arr[f->end] = item;
    f->end = (f->end + 1) % f->allocated;
    f->size++;
}

void deque_push_front( void* v, void* item) {
    Deque* f = (Deque*)v;
    if (f->size == f->allocated) {
        f->arr = (void **)realloc(f->arr, (f->allocated + 20) * sizeof(void*));
        f->allocated += 20;
    }
    f->start = (f->start - 1 + f->allocated) % f->allocated;
    f->arr[f->start] = item;
    f->size++;
}

void* deque_pop_back( void* v) {
    Deque* f = (Deque*)v;
    if (f->size == 0) {
        exit(1);// Indicar deque vazio de alguma forma
    }
    f->end = (f->end - 1 + f->allocated) % f->allocated;
    void* item = f->arr[f->end];
    
    f->size--;
    return item;
}

void* deque_pop_front( void* v) {
    Deque* f = (Deque*)v;
    if (f->size == 0) {
        exit(1); // Indicar deque vazio de alguma forma
    }
    void* item = f->arr[f->start];
    f->start = (f->start + 1) % f->allocated;
    f->size--;
    return item;
}

void deque_destroy( void *v) {
    Deque* f = (Deque*)v;
    free(f->arr);
    free(f);
}
