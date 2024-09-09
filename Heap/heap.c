#include "heap.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

struct Heap
{
    Vector* v;
    int (*cmp_fn)(const void *, const void *);
    int size;
};

Heap *heap_constructor(int (*cmp_fn)(const void *, const void *)){
    Heap* heap = (Heap*)calloc(1, sizeof(Heap));
    heap->v= vector_construct();
    heap->cmp_fn = cmp_fn;
    return heap;
}

void heap_push( void* v,  void *data){
    Heap* heap = (Heap*)v;
    vector_insert(heap->v, heap->size, data);
    heap->size++;
    int parent, idx = heap->size-1;
    while (idx > 0) {
        parent = (idx - 1) / 2;
        if (heap->cmp_fn(vector_get(heap->v, idx), vector_get(heap->v, parent)) > 0)
            vector_swap(heap->v, idx, parent);
        else break;
        idx = parent;
    }
}

int heap_size(Heap *heap){
    return heap->size;
}

void *heap_pop( void* v){
    Heap* heap = (Heap*)v;
    if (heap->size < 1)
        exit(printf("Error::heap is empty\n"));

    void *max_data = vector_get(heap->v, 0);
    if (heap->size >= 2)
        vector_swap(heap->v, 0, heap->size -1);
    heap->size--;
    
    int max, left_child, right_child, idx = 0;
    while (1) {
        max = idx;
        left_child = 2 * idx + 1;
        right_child = 2 * idx + 2;
        if ((left_child < heap->size) &&
            heap->cmp_fn(vector_get(heap->v, left_child), vector_get(heap->v, max)) > 0)
            max = left_child;
        
        if ((right_child < heap->size) &&
            heap->cmp_fn(vector_get(heap->v, right_child), vector_get(heap->v, max)) > 0)
            max = right_child;
        
        if (max != idx) {
            vector_swap(heap->v, idx, max);
            idx = max;
            }
        else
        break;
    }
    return max_data;
}

void heap_destroy( void* v){
    Heap* heap = (Heap*)v;
    vector_destroy(heap->v);
    free(heap);
}

