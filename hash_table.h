#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "linked_list.h"

typedef void *HashTable_t;
typedef void *Item_t;

void delete_item(void *item_);

HashTable_t create_hash_table(int size);

void insert_hash(HashTable_t _hashTable, char *key, Info_t _info);

unsigned long int hash_function(char *key, int size);

int get_table_size(HashTable_t *_hashtable);

void delete_hash_table(HashTable_t _hashTable, int flag);

void remove_item(HashTable_t _hashTable, char key[], int flag);

List_t *get_table(HashTable_t _hashTable);

void *get_item_info(Item_t _item);

/* TODO função de remover da hash table com
 *
 */

#endif // HASH_TABLE_H_
