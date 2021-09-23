#ifndef PROPERTY_LEASE_H_
#define PROPERTY_LEASE_H_

typedef void *Lease_t;
#include "linked_list.h"
#include "hash_table.h"

char *get_property_cep(Lease_t _property);

char *get_property_id(Lease_t _property);

List_t get_lease_ids(HashTable_t _property, char *cep);

char *get_property_compl(Lease_t _property);

char get_property_side(Lease_t _property);

int get_property_number(Lease_t _property);

double get_property_ar(Lease_t _property);

double get_property_v(Lease_t _property);

#endif //PROPERTY_LEASE_H_
