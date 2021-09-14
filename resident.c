#include "resident.h"
#include <stdlib.h>
#include <string.h>

typedef struct Resident {
    char cpf[20];
    char cep[25];
    char face;
    int num;
    char compl[25];
}Resident;

Resident_t create_resident(char cpf[], char cep[], char face, int num, char compl[]){
    Resident *resident = (Resident*) malloc(sizeof(Resident));

    strcpy(resident->cpf, cpf);
    strcpy(resident->cep, cep);
    resident->face = face;
    resident->num = num;
    strcpy(resident->compl, compl);

    return resident;
}

char* get_resident_cpf(Resident_t _resident){
    Resident *resident = (Resident*) _resident;
    return resident->cpf;
}

char* get_cep(Resident_t _resident){
    Resident *resident = (Resident*) _resident;
    return resident->cep;
}

char get_face(Resident_t _resident){
    Resident *resident = (Resident*) _resident;
    return resident->face;
}

int get_num(Resident_t _resident){
    Resident *resident = (Resident*) _resident;
    return resident->num;
}

char* get_compl(Resident_t _resident) {
    Resident *resident = (Resident*) _resident;
    return resident->compl;
}