#include "people.h"
#include <stdlib.h>
#include <string.h>

typedef struct People {
    char cpf[20];
    char nome[30];
    char sobrenome[30];
    char nasc[11];
    char sex;
}People;

People_t create_people(char cpf[], char nome[], char sobrenome[], char sex, char nasc[]){
    People *people = (People*) malloc(sizeof(People));

    strcpy(people->cpf, cpf);
    strcpy(people->nome, nome);
    strcpy(people->sobrenome, sobrenome);
    strcpy(people->nasc, nasc);
    people->sex = sex;

    return people;
}

char* get_people_cpf(People_t _resident){
    People *people = (People*) _resident;
    return people->cpf;
}

char* get_nome(People_t _people){
    People *people = (People*) _people;
    return people->nome;
}

char* get_sobrenome(People_t _people){
    People *people = (People*) _people;
    return people->sobrenome;
}

char* get_nasc(People_t _people){
    People *people = (People*) _people;
    return people->nasc;
}

char get_sex(People_t _people){
    People *people = (People*) _people;
    return people->sex;
}
