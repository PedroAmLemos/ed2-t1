#ifndef PEOPLE_H_
#define PEOPLE_H_

typedef void *People_t;

People_t create_resident(char cpf[], char nome[], char sobrenome[], char nasc[], char sex);

char* get_cpf(People_t _people);

char* get_nome(People_t _people);

char* get_sobrenome(People_t _people);

char* get_nasc(People_t _people);

char get_sex(People_t _people);

#endif //PEOPLE_H_
