#ifndef WRAPPER_H_
#define WRAPPER_H_
#include "avl_tree.h"
#include "hash_table.h"
#include "people.h"
#include "resident.h"

typedef void *Char_t;
typedef void *Int_t;

void remove_hash_table_tree(HashTable_t _hashTable, AvlTree_t _tree, Char_t cep, int flag);

void remove_tree_hash_table(HashTable_t _hashTable, AvlTree_t _tree, Int_t point, int flag);

void print_person_resident_txt(Resident_t _resident, People_t _person, FILE *txtFile);

#endif //WRAPPER_H_
