#ifndef PROPERTY_LEASE_H_
#define PROPERTY_LEASE_H_

typedef void *Lease_t;
#include "linked_list.h"
#include "hash_table.h"

char *get_property_cep(Lease_t _property);

char *get_property_id(Lease_t _property);

List_t get_lease_ids(HashTable_t _property, char *cep);

#endif //PROPERTY_LEASE_H_
