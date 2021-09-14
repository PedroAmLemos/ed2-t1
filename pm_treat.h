#ifndef PM_TREAT_H_
#define PM_TREAT_H_

#include <stdio.h>
#include <string.h>
#include "hash_table.h"
#include "people.h"
#include "resident.h"


void pm_treat(HashTable_t people, HashTable_t residents, FILE *pmFile);

#endif
