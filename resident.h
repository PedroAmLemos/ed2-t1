#ifndef RESIDENT_H_
#define RESIDENT_H_

typedef void *Resident_t;
#include "hash_table.h"
#include "linked_list.h"

Resident_t create_resident(char cpf[], char cep[], char face, int num, char compl[]);

char* get_resident_cpf(Resident_t _resident);

char* get_cep(Resident_t _resident);

char get_face(Resident_t _resident);

int get_num(Resident_t _resident);

char* get_compl(Resident_t _resident);

List_t get_cep_residents(HashTable_t _residentTable, char *cep);

#endif //RESIDENT_H_
