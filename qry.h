#ifndef QRY_H_
#define QRY_H_
#include <stdio.h>
#include "city.h"
#include "hash_table.h"
#include "avl_tree.h"
#include "linked_list.h"

/*
 * Função responsável por ler e realizar os comandos do qry.
 * Pré: ponteiro do tipo void* para a cidade, os arquivos para leitura e impressão do qry, e o caminho de saída.
 * Pós:
 */
void qry_treat(City_t city, FILE *qryFile, FILE *qrySVGFile, FILE *qryTXTFile, char *outPath);

#endif //QRY_H_
