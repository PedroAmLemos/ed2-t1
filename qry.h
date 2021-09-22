#ifndef QRY_H_
#define QRY_H_
#include <stdio.h>
#include "hash_table.h"
#include "avl_tree.h"
#include "linked_list.h"

void qry_treat(HashTable_t _people, HashTable_t _residents, HashTable_t _blocksTable, AvlTree_t _blocksTree, FILE *qryFile, FILE *qrySVGFile, FILE *qryTXTFile);

#endif //QRY_H_
