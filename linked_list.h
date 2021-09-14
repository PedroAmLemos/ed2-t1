#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef void *List_t;

typedef void *Info_t;

typedef void *Node_t;

List_t create_list();

void insert_list(List_t _list, Info_t _info);

Node_t get_first(List_t list_);

Node_t get_next(Node_t node_);

Info_t get_info(Node_t node_);

int get_list_size(List_t _list);

void remove_list(List_t *_list, void(*remove)(void*));

void remove_node(List_t list_, Node_t node_, void (*remove)(void*));

#endif // LINKED_LIST_H_
