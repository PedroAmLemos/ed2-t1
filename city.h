#ifndef CITY_H_
#define CITY_H_
#include "hash_table.h"
#include "avl_tree.h"
#include <stdio.h>

typedef void *City_t;

City_t create_city();

void insert_city_people_table(City_t  _city, HashTable_t _people);

void insert_city_residents_table(City_t _city, HashTable_t _residents);

void insert_city_lease_table(City_t _city, HashTable_t _lease);

void insert_city_blocks_table(City_t _city, HashTable_t _blocksTable);

void insert_city_blocks_tree(City_t _city, AvlTreeNode_t _blocksTree);

HashTable_t get_city_people_table(City_t _city);

HashTable_t get_city_resident_table(City_t _city);

HashTable_t get_city_leases_table(City_t _city);

HashTable_t get_city_blocks_table(City_t _city);

AvlTree_t get_city_blocks_tree(City_t _city);

#endif //CITY_H_
