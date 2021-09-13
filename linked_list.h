#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef void *List_t;

typedef void *Info_t;

List_t create_list();

void insert_list(List_t _list, Info_t _info);

int get_list_size(List_t _list);

void remove_list(List_t *_list);

#endif // LINKED_LIST_H_
