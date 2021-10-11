#ifndef RESIDENT_H_
#define RESIDENT_H_

typedef void *Resident_t;
#include "hash_table.h"
#include "linked_list.h"


/*
 * Aloca memória para a struct morador e atribui os valores passados a ela.
 * Pré: os parâmetros para criação da struct.
 * Pós: retorna um ponteiro do tipo void* para o morador que foi criado.
 */
Resident_t create_resident(char cpf[], char cep[], char face, int num, char compl[]);

/*
 * Muda o residente para o status de alugado.
 * Pré: um residente.
 * Pós:
 */
void change_resident_to_rent(Resident_t _resident);

/*
 * Muda o endereço de um residente.
 * Pré: um residente e os dados da mudança.
 * Pós:
 */
void change_resident_address(Resident_t _resident, char *newCEP, char *newCPF, char face, int num, char *compl);

/*
 * Retorna se a pessoa está alugando ou não.
 * Pré: um morador.
 * Pós: 1 para está alugando, 0 para o contrário.
 */
int is_person_renting(Resident_t _resident);


/*
 * Getters: Retorna o atributo do título da função.
 * Pré: Objeto.
 * Pós: Atributo especificado.
 */
char* get_resident_cpf(Resident_t _resident);
char* get_resident_cep(Resident_t _resident);
char get_resident_face(Resident_t _resident);
int get_resident_number(Resident_t _resident);
char* get_resident_compl(Resident_t _resident);
List_t get_cep_residents(HashTable_t _residentTable, char *cep);

#endif //RESIDENT_H_
