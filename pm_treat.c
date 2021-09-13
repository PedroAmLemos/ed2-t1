#include "pm_treat.h"
#include "hash_table.h"
#include <string.h>
#include <stdio.h>

void pm_treat(HashTable_t people, HashTable_t residents, FILE *pmFile){
    char aux[5];
    char cpf[20];
    char nome[30], sobrenome[30], nasc[11];
    char cep[20], face, compl[25];
    char sex;
    int num;
    while(fscanf(pmFile,"%s", aux)!= EOF){
        if((strcmp(aux,"p")) == 0){
            fscanf(pmFile, "%s %s %s %c %s", cpf, nome, sobrenome, &sex, nasc);
            // adicionar pessoa na hash table people
        }
        if((strcmp(aux,"m")) == 0) {
            fscanf(pmFile, "%s %s %s %d %s", cpf, cep, &face, &num, compl);
            // adicionar o morador na hash table residents
        }
    }
}
