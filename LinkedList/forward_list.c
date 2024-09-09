#include "forward_list.h"
#include <stdlib.h>
#include <stdio.h>

ForwardList *forward_list_construct(){
    ForwardList* l = (ForwardList*)calloc(1, sizeof(ForwardList));
    l->head=NULL;
    // l->last = NULL;
    return l;
}

int forward_list_size(ForwardList *l){
    return l->size;
}

void forward_list_push_front(ForwardList *l, data_type data){
    l->head=node_construct(data, l->head);
    l->size++;
    // if (l->size == 1)
    //     l->last = l->head;
}

// void forward_list_push_back(ForwardList *l, data_type data){
//     Node *new_node = node_construct(data, NULL);
//     // if (l->last == NULL)
//     //     l->head = l->last = new_node;
//     // else {
//     //     l->last->next = new_node;
//     //     l->last = new_node;
//     //     }
//     // l->size++;
// }

void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){
    printf("[");
    Node* n = l->head;
    while(n!=NULL){
        print_fn(node_value(n));
        n=node_next(n);
        if(n!=NULL){
            printf(", ");
        }
    }
    printf("]");
}

data_type forward_list_get(ForwardList *l, int i){
    if(i<0 || i>=l->size){
        exit(printf("ERRO!! INDICE INVALIDO!!\n"));
    }
    int j;
    Node* n =l->head;
    for(j=0;j<i;j++,n=(node_next(n)));
    return node_value(n);
}

data_type forward_list_pop_front(ForwardList *l){
    data_type d = node_value(l->head);
    Node * n=node_next(l->head);
    node_destroy(l->head);
    l->head=n;
    l->size--;
    // if (l->size <= 1)
    //     l->last = l->head;
    return d;
}

void forward_list_remove(ForwardList *l, data_type val){
    int j;
    Node* n =l->head;
    Node* ant =NULL;
    int num = l->size;
    for(j=0;j<num;j++){
        if(node_value(n)==val){
            if(ant != NULL){
                ant->next=n->next;
                node_destroy(n);
                n=ant->next;
            }
            else{
                l->head=n->next;
                node_destroy(n);
                n=l->head;
            }
            l->size--;
        }
        else {
        ant=n;
        n=(node_next(n));
        }
    }
}

ForwardList *forward_list_reverse(ForwardList *l){
    ForwardList *new_list = forward_list_construct();
    Node *n = l->head;
    while (n != NULL)
        {
        forward_list_push_front(new_list, n->value);
        n = n->next;
        }
    return new_list;
}

void forward_list_clear(ForwardList *l){
    int n_itens = l->size;
    for (int i = 0; i < n_itens; i++)
        forward_list_pop_front(l);
}

void forward_list_cat(ForwardList *l, ForwardList *m){
    Node *n = m->head;
    while (n != NULL)
        {
        forward_list_push_front(l, n->value);
        n = n->next;
        }
}

void forward_list_destroy(ForwardList *l){
    Node* next;
    while(l->head != NULL){
        next=node_next(l->head);
        node_destroy(l->head);
        l->head=next;
    }
    
    free(l);
}

ListIterator *list_iterator_construct(ForwardList *l) {
    ListIterator *it =
    (ListIterator *)calloc(1, sizeof(ListIterator));
    it->current = l->head;
    return it;
}

data_type* list_iterator_next(ListIterator *it){
    data_type *n = &(it->current->value);
    it->current = it->current->next;
    return n;
}

bool list_iterator_is_over(ListIterator *it){
    return (it->current == NULL);
}

void list_iterator_destroy(ListIterator *it) {
    free(it);
}