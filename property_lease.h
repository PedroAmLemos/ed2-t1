#ifndef PROPERTY_LEASE_H_
#define PROPERTY_LEASE_H_

typedef void *Lease_t;
#include "linked_list.h"
#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Aloca memória para a struct locação e atribui os valores passados a ela.
 * Pré: os parâmetros para criação da struct.
 * Pós: retorna um ponteiro do tipo void* para a locação criada.
 */
Lease_t create_lease(char id[50], char cep[25], char compl[50], char side, int number, double ar, double v);

/*
 * Adiciona um locador para a locação passada.
 * Pré: um ponteiro do tipo void* para a locação e o cpf do locador.
 * Pós:
 */
void add_lessee(Lease_t _property, char cpf[20]);

/*
 * Muda o status da propriedade.
 * Pré: uma propriedade e o status novo (1 para locado e 0 para não alugado).
 * Pós:
 */
void change_property_status(Lease_t _property, int status);

/*
 * Imprime os dados da locação em um arquivo txt.
 * Pré: uma locação e o ponteiro para o arquivo.txt.
 * Pós:
 */
void print_property(Lease_t *_property, FILE *TXTFile);


/*
 * Getters: Retorna o atributo do título da função.
 * Pré: Objeto.
 * Pós: Atributo especificado.
 */
char *get_property_cep(Lease_t _property);
char *get_property_id(Lease_t _property);
List_t get_lease_ids(HashTable_t _property, char *cep);
char *get_property_compl(Lease_t _property);
char get_property_side(Lease_t _property);
int get_property_number(Lease_t _property);
double get_property_ar(Lease_t _property);
double get_property_v(Lease_t _property);
char *get_lessee(Lease_t _property);
int get_property_status(Lease_t _property);


#endif //PROPERTY_LEASE_H_
