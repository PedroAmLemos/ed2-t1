#ifndef RESIDENT_H_
#define RESIDENT_H_

typedef void *Resident_t;
#include "hash_table.h"
#include "linked_list.h"

Resident_t create_resident(char cpf[], char cep[], char face, int num, char compl[]);

void change_resident_to_rent(Resident_t _resident);

void change_resident_from_rent(Resident_t _resident);

void change_resident_address(Resident_t _resident, char *newCEP, char *newCPF, char face, int num, char *compl);

int is_person_renting(Resident_t _resident);

char* get_resident_cpf(Resident_t _resident);

char* get_resident_cep(Resident_t _resident);

char get_resident_face(Resident_t _resident);

int get_resident_number(Resident_t _resident);

char* get_resident_compl(Resident_t _resident);

List_t get_cep_residents(HashTable_t _residentTable, char *cep);

#endif //RESIDENT_H_
