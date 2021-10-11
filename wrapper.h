#ifndef WRAPPER_H_
#define WRAPPER_H_
#include "avl_tree.h"
#include "hash_table.h"
#include "people.h"
#include "resident.h"

typedef void *Char_t;
typedef void *Int_t;

/*
 * Função que realiza a remoção de uma quadra a partir de um cep.
 * Pré: recebe um ponteiro para a hash table, outro para a árvore, um cep, e uma flag que indica a desalocação de
 * memória.
 * Pós:
 */
void remove_hash_table_tree(HashTable_t _hashTable, AvlTree_t _tree, Char_t cep, int flag);

/*
 * Função que realiza a remoção de uma quadra a partir de um ponto.
 * Pré: recebe um ponteiro para a árvore, outro para a hash table, um ponto, e uma flag que indica a desalocação de
 * memória.
 *
 */
void remove_tree_hash_table(HashTable_t _hashTable, AvlTree_t _tree, Int_t point, int flag);

/*
 * Imprime os dados de um residente e uma pessoa em um arquivo.txt.
 * Pré: recebe um morador, uma pessoa e o arquivo.txt para impressão.
 * Pós:
 */
void print_person_resident_txt(Resident_t _resident, People_t _person, FILE *txtFile);

#endif //WRAPPER_H_
