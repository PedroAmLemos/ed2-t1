#ifndef QRY_H_
#define QRY_H_
#include <stdio.h>
#include "city.h"
#include "hash_table.h"
#include "avl_tree.h"
#include "linked_list.h"

void qry_treat(City_t city, FILE *qryFile, FILE *qrySVGFile, FILE *qryTXTFile, char *outPath);

#endif //QRY_H_
