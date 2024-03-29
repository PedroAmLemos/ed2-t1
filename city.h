#ifndef CITY_H_
#define CITY_H_
#include "hash_table.h"
#include "avl_tree.h"
#include <stdio.h>

typedef void *City_t;

/*
 * Função responsável por criar uma struct cidade e inicializar as tabelas e a árvore necessários.
 * Pré: o número de pessoas.
 * Pós: um ponteiro do tipo void* para a cidade criada.
 */
City_t create_city(int nx);

/*
 * Função responsável por desalocar toda memória alocada para a cidade e os seus componentes.
 * Pré: um ponteiro do tipo void* para a cidade.
 * Pós:
 */
void delete_city(City_t _city);

/*
 * Getters: Retorna o atributo do título da função.
 * Pré: Objeto.
 * Pós: Atributo especificado.
*/
HashTable_t get_city_people_table(City_t _city);
HashTable_t get_city_resident_table(City_t _city);
HashTable_t get_city_lease_table(City_t _city);
HashTable_t get_city_blocks_table(City_t _city);
AvlTree_t get_city_blocks_tree(City_t _city);


#endif //CITY_H_

