#include "pm_treat.h"
#include <string.h>
#include "people.h"
#include "resident.h"

void pm_treat(HashTable_t people_, HashTable_t residents_, FILE *pmFile){
    char aux[5];
    char cpf[20];
    char nome[30], sobrenome[30], nasc[11];
    char cep[20], face, compl[25];
    char sex;
    int num;
    while(fscanf(pmFile,"%s", aux)!= EOF){
        if((strcmp(aux,"p")) == 0){
            fscanf(pmFile, "%s %s %s %c %s", cpf, nome, sobrenome, &sex, nasc);
            People_t people = create_people(cpf, nome, sobrenome, sex, nasc);
            insert_hash(people_, get_people_cpf(people), people);
        }
        if((strcmp(aux,"m")) == 0) {
            fscanf(pmFile, "%s %s %s %d %s", cpf, cep, &face, &num, compl);
            Resident_t resident = create_resident(cpf, cep, face, num, compl);
            insert_hash(residents_, get_resident_cpf(resident), resident);
        }
    }
}
