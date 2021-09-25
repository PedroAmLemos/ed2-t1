#ifndef QRY_FUNCTIONS_H_
#define QRY_FUNCTIONS_H_


#include "hash_table.h"
#include "avl_tree.h"

void del(HashTable_t _residents, HashTable_t _blockTable, HashTable_t _propertyTable, AvlTree_t _blockTree, char *cep, FILE *qryTXTFile, FILE *qrySVGFile);

void m(HashTable_t _residents, HashTable_t _people, HashTable_t _blocksTable, char cep[], FILE *qryTXTFile);

void dm(HashTable_t _residents, HashTable_t _people, HashTable_t _blocksTable, char cpf[], FILE *qryTXTFile, FILE *qrySVGFile);

void mud(HashTable_t _residents, HashTable_t _people, HashTable_t _blocksTable, char cpf[], char cep[], char face, int num, char compl[], FILE *qryTXTFile, FILE *qrySVGFile);

void oloc(HashTable_t propertyLeaseTable, char id[], char cep[], char side, int num, char compl[], double ar, double v);

void oloc_i(HashTable_t propertyLeaseTable, HashTable_t _blocksTable, double x, double y, double w, double h, FILE *qryTXTFile, FILE *qrySVGFile);

void loc(HashTable_t _blocksTable, HashTable_t _people, HashTable_t _residents, HashTable_t propertyLeaseTable, char id[], char cpf[], FILE *qryTXTFile, FILE *qrySVGFile);

#endif //QRY_FUNCTIONS_H_
