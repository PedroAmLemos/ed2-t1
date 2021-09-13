#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

typedef void *HashTable_t;

HashTable_t create_hash_table(int size);

void insert_hash_table(HashTable_t _hashTable, int value);

unsigned long int hash_function(char *key, int size);

int get_table_size(HashTable_t *_hashtable);

void remove_hash_table(HashTable_t _hashTable);

#endif // HASH_TABLE_H_
