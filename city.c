#include "city.h"
#include <stdlib.h>

typedef struct City {
    HashTable_t peopleTable;
    HashTable_t residentsTable;
    HashTable_t leaseTable;
    HashTable_t blocksTable;
    AvlTree_t blocksTree;
}City;

City_t create_city(){
    City *city = (City*) malloc(sizeof(City));
    city->peopleTable = NULL;
    city->residentsTable = NULL;
    city->leaseTable = NULL;
    city->blocksTable = NULL;
    city->blocksTree = NULL;
    return city;
}

void insert_city_people_table(City_t  _city, HashTable_t _people){
    City *city = (City*) _city;
    city->peopleTable = _people;
}

void insert_city_residents_table(City_t _city, HashTable_t _residents){
    City *city = (City*) _city;
    city->residentsTable = _residents;
}

void insert_city_lease_table(City_t _city, HashTable_t _lease){
    City *city = (City*) _city;
    city->leaseTable = _lease;
}

void insert_city_blocks_table(City_t _city, HashTable_t _blocksTable){
    City *city = (City*) _city;
    city->blocksTable = _blocksTable;
}

void insert_city_blocks_tree(City_t _city, AvlTreeNode_t _blocksTree){
    City *city = (City*) _city;
    city->blocksTree = _blocksTree;
}

HashTable_t get_city_people_table(City_t _city){
    City *city = (City*) _city;
    return city->peopleTable;
}

HashTable_t get_city_resident_table(City_t _city){
    City *city = (City*) _city;
    return city->residentsTable;
 }

HashTable_t get_city_lease_table(City_t _city){
	City *city = (City*) _city;
    return city->leaseTable;
}

HashTable_t get_city_blocks_table(City_t _city){
	City *city = (City*) _city;
    return city->blocksTable;
}

AvlTree_t get_city_blocks_tree(City_t _city){
	City *city = (City*) _city;
    return city->blocksTree;
}

void delete_city(City_t _city){
    City *city = (City*) _city;
    delete_tree(city->blocksTree);
    delete_hash_table(city->peopleTable, 1);
    delete_hash_table(city->residentsTable, 1);
    delete_hash_table(city->blocksTable, 1);
    delete_hash_table(city->leaseTable, 1);
    free(_city);
}