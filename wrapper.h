#ifndef WRAPPER_H_
#define WRAPPER_H_
#include "avl_tree.h"
#include "hash_table.h"

/*
 * TODO fazer a função que remove o block com o cep
 * recebe o cep, a table, a árvore e flag 1; pega o ponto, remove da árvore com flag 0 (não chama a remove hash) e
 * desaloca da tabela;
 */
void remove_hash_table_tree(HashTable_t _hashTable, AvlTree_t _tree, void* cep, int flag);

/*
 * TODO fazer a função que remove o block com o ponto
 * recebe o ponto, a table, a árvore flag 1; pega o cep, remove o node da árvore, e chama o remove_hash com flag 0 (não
 * chama a remove tree);
 *
 */
void remove_tree_hash_table(HashTable_t _hashTable, AvlTree_t _tree, void* point, int flag);

#endif //WRAPPER_H_
