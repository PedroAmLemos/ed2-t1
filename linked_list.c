#include "linked_list.h"
#include "block.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    Info_t info;
    struct Node *next;
    struct Node *prev;
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
    node->info  = _info;
    if(list->first==NULL){
        node->prev  = NULL;
        list->first = node;
    }else{
        list->last->next = node;
        node->prev = list->last;
    }
    node->next = NULL;
    list->last = node;
    list->size++;
}

void remove_list_node(List_t list_, Node_t node_, void (*remove)(void*)){
    List *list = (List*) list_;
    Node *node = (Node*) node_;

    if(node->prev == NULL){
        list->first = node->next;
    }else{
        node->prev->next = node->next;
    }
    if(node->next == NULL) {
        list->last = node->prev;
    }else{
        node->next->prev = node->prev;
    }

    if(remove != NULL) remove(get_list_info(node));
    free(node);
    list->size--;
}

void remove_list(List_t _list, void(*remove)(void*)){
    List *list = (List*) _list;
    Node *node = list->first;
    Node *aux;
    while (node != NULL) {
        aux = node;
        node = node->next;
        if(remove != NULL)
            remove(aux->info);
        free(aux);
    }
    free(list);
}

Node_t get_list_first(List_t list_){
//    if(list_ == NULL) return NULL;
    List *list = (List*) list_;
    return list->first;
}

Node_t get_list_next(Node_t node_){
    Node *list = (Node*) node_;
    return list->next;
}

Info_t get_list_info(Node_t node_){
    if(node_ == NULL) return NULL;
    Node *list = (Node*) node_;

    return list->info;
}

int get_list_size(List_t _list){
    List *list = (List*) _list;
    return list->size;
}

void get_points_inside(List_t _list, List_t storage, double x, double y, double w, double h){
    List *list = (List*) _list;
    Block_t block = NULL;
    for(Node *node = list->first; node != NULL; node = node->next) {
        block = node->info;
        if(is_block_inside_rect(block, x, y, w, h)) {
            insert_list(storage, get_block_cep(block));
        }
    }

}

