#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resident.h"

typedef struct Resident {
    char cpf[20];
    char cep[25];
    char face;
    int rent;
    int num;
    char compl[25];
}Resident;

Resident_t create_resident(char cpf[], char cep[], char face, int num, char compl[]){
    Resident *resident = (Resident*) malloc(sizeof(Resident));

    strcpy(resident->cpf, cpf);
    strcpy(resident->cep, cep);
    resident->face = face;
    resident->num = num;
    resident->rent = 0;
    strcpy(resident->compl, compl);

    return resident;
}

char* get_resident_cpf(Resident_t _resident){
    Resident *resident = (Resident*) _resident;
    return resident->cpf;
}

void change_resident_to_rent(Resident_t _resident){
    Resident *resident = (Resident*) _resident;
    resident->rent = 1;
}

void change_resident_from_rent(Resident_t _resident){
    Resident *resident = (Resident*) _resident;
    resident->rent = 0;
}

int is_person_renting(Resident_t _resident){
    Resident *resident = (Resident*) _resident;
    return resident->rent == 1;
}

char* get_resident_cep(Resident_t _resident){
    Resident *resident = (Resident*) _resident;
    return resident->cep;
}

char get_resident_face(Resident_t _resident){
    Resident *resident = (Resident*) _resident;
    return resident->face;
}

int get_resident_number(Resident_t _resident){
    Resident *resident = (Resident*) _resident;
    return resident->num;
}

char* get_resident_compl(Resident_t _resident) {
    Resident *resident = (Resident*) _resident;
    return resident->compl;
}

List_t get_cep_residents(HashTable_t _residentTable, char *cep) {
    List_t idListToRemove = create_list();
    if(_residentTable == NULL){
        return idListToRemove;
    }
    HashTable_t *table = get_table(_residentTable);
    int tableSize = get_table_size(_residentTable);

    List_t tableList;
    for (int i = 0; i < tableSize; i++){
        tableList = get_index_list(_residentTable, i);
        if(tableList != NULL){
            for(Node_t node = get_list_first(tableList); node != NULL; node = get_list_next(node)){
                if(strcmp(get_resident_cep(get_item_info(get_list_info(node))), cep) == 0){
                    insert_list(idListToRemove, get_resident_cpf(get_item_info(get_list_info(node))));
                }
            }
        }
    }
    return idListToRemove;
}

void change_resident_address(Resident_t _resident, char *newCEP, char *newCPF, char face, int num, char *compl){
    Resident *resident = (Resident*) _resident;
    strcpy(resident->cep, newCEP);
    strcpy(resident->cpf, newCPF);
    strcpy(resident->compl, compl);
    resident->face = face;
    resident->num = num;
}