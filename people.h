#ifndef PEOPLE_H_
#define PEOPLE_H_

typedef void *People_t;

/*
 * Aloca memória para a struct pessoa e atribui os valores passados a ela.
 * Pré: os parâmetros para criação da struct.
 * Pós: retorna um ponteiro do tipo void* para a pessoa criada.
 */
People_t create_people(char cpf[], char nome[], char sobrenome[], char sex, char nasc[]);


/*
 * Getters: Retorna o atributo do título da função.
 * Pré: Objeto.
 * Pós: Atributo especificado.
 */
char* get_person_cpf(People_t _resident);
char* get_person_name(People_t _people);
char* get_person_sobrenome(People_t _people);
char* get_person_nasc(People_t _people);
char get_person_sex(People_t _people);

#endif //PEOPLE_H_
