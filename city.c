#include <malloc.h>
#include "city.h"
#include "hash_table.h"
#include "avl_tree.h"

typedef struct City {
    HashTable_t hashTable;
    AvlTree_t avlTree;
}City;

City_t create_city(HashTable_t hashTable, AvlTree_t avlTree){
    City *city = (City*) malloc(sizeof(City));
    city->avlTree = avlTree;
    city->hashTable = hashTable;
    return city;
}

