
#ifndef _DEQUE_H_
#define _DEQUE_H_

typedef struct Deque Deque;

Deque *deque_construct();
void deque_push_back( void *v, void* item);
void deque_push_front( void *v, void* item);
void* deque_pop_back( void *v);
void* deque_pop_front( void *v);
void deque_destroy( void *v);

#endif