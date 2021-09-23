#ifndef PEOPLE_H_
#define PEOPLE_H_

typedef void *People_t;

People_t create_people(char cpf[], char nome[], char sobrenome[], char sex, char nasc[]);

char* get_person_cpf(People_t _resident);

char* get_person_name(People_t _people);

char* get_person_sobrenome(People_t _people);

char* get_person_nasc(People_t _people);

char get_person_sex(People_t _people);

#endif //PEOPLE_H_
