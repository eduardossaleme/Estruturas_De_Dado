
#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct Heap Heap;

Heap *heap_constructor(int (*cmp_fn)(const void *, const void *));
void heap_push( void* v,  void *data);
int heap_size(Heap *heap);
void *heap_pop( void* v);
void heap_destroy( void* v);


#endif
