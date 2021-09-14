#include "linked_list.h"
#include <stdlib.h>

typedef struct Node{
    Info_t info;
    struct Node *next;
}Node;

typedef struct{
    int size;
    Node *first;
    Node *last;
}List;

List_t create_list(){
    List *list = (List*) malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    return list;
}

void insert_list(List_t _list, Info_t _info){
    List *list = (List*) _list;
    Node *node  = (Node*) malloc(sizeof(Node));
    node->info = _info;
    node->next  = NULL;
    if(list->first==NULL){
        list->first = node;
    }else{
        list->last->next = node;
    }
    list->last = node;
    list->size++;
}

void remove_list(List_t *_list){
    List *list = (List*) _list;
    Node *node = list->first;
    Node *aux;
    while (node != NULL) {
        aux = node;
        node = node->next;
        free(aux->info);
        free(aux);
    }
    free(list);
}

__attribute__((unused)) int get_list_size(List_t _list){
    List *list = (List*) _list;
    return list->size;
}

