#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linked_list.h"
#include "hash_table.h"

typedef struct{
    int size;
    List_t *table;
}Hash;

typedef struct{
    char key[25];
    Info_t info;
}Item;

void delete_item(void *item_){
    Item *item = (Item*) item_;
    free(item->info);
    free(item);
}

HashTable_t create_hash_table(int size){
    Hash *hashTable = (Hash*) malloc(sizeof(Hash));
    int i;

    hashTable->size = size;
    hashTable->table = (List_t*)malloc(sizeof(List_t)*size);

    for (i = 0; i < size; i++) {
        hashTable->table[i] = create_list();
    }

    return hashTable;
}

unsigned long int hash_function(char *_key, int size){
    unsigned int hash = 5381;
    unsigned char *key = (unsigned char*) _key;
    int c;
    while ((c = *key++)) {
        if (isupper(c)) {
            c = c + 32;
        }
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

void insert_hash(HashTable_t _hashTable, char key[], Info_t _info){
    Hash *hashTable = (Hash*) _hashTable;
    unsigned long int hash = hash_function(key, hashTable->size);

    Item *info_s = (Item*) malloc(sizeof(Item));
    info_s->info = _info;
    strcpy(info_s->key, key);

    insert_list(hashTable->table[hash], info_s);
}

//int get_table_size(HashTable_t *_hashtable){
//    Hash *hashTable = (Hash*)_hashtable;
//    return hashTable->size;
//}

Item_t get_item(HashTable_t _hashtable, char key[]) {
    Hash *hashTable = (Hash*) _hashtable;
    unsigned long int hashKey = hash_function(key, hashTable->size);
    for(Node_t aux = get_first(hashTable->table[hashKey]); aux != NULL; aux = get_next(aux)){
        Item *item = (Item*) get_info(aux);
        if(strcmp(item->key, key) == 0) {
            return item->info;
        }
    }
    return NULL;
}

void remove_item(HashTable_t _hashTable, char key[], int flag){
    Hash *hashTable = (Hash*) _hashTable;
    unsigned long int hashKey = hash_function(key, hashTable->size);
    void (*carlos[2])(void*) = {free, delete_item};

    for(Node_t aux = get_first(hashTable->table[hashKey]); aux != NULL; aux = get_next(aux)){
        Item *item = (Item*) get_info(aux);
        if(strcmp(item->key, key) == 0) {
            remove_node(hashTable->table[hashKey], aux, carlos[flag]);
            return;
        }
    }
}

void delete_hash_table(HashTable_t _hashTable, int flag){
    void (*carlos[2])(void*) = {free, delete_item};
    Hash *hashTable = (Hash*)_hashTable;
    int i;
    List_t *lists = hashTable->table;
    for (i = 0; i < hashTable->size; i++) {
        remove_list(lists[i], carlos[flag]);
    }
    free(lists);
    free(hashTable);
}