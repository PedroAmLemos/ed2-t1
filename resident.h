#ifndef RESIDENT_H_
#define RESIDENT_H_

typedef void *Resident_t;

Resident_t create_resident(char cpf[], char cep[], char face, int num, char compl[]);

char* get_cpf(Resident_t _resident);

char* get_cep(Resident_t _resident);

char get_face(Resident_t _resident);

int get_num(Resident_t _resident);

char* get_compl(Resident_t _resident);

#endif //RESIDENT_H_
