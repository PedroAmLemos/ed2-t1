#include "wrapper.h"
#include "block.h"

void remove_hash_table_tree(HashTable_t _hashTable, AvlTree_t _tree, Char_t _cep, int flag){
    char *cep = (char*) _cep;
    Block_t block = get_info_from_key(_hashTable, cep);
    double point[2];
    if(block != NULL){
        if(flag == 1){
            point[0] = get_block_x(block);
            point[1] = get_block_y(block);
            remove_tree_hash_table(_hashTable, _tree, point, 0);
        }
        remove_item(_hashTable, cep, 1);
    }
}

void remove_tree_hash_table(HashTable_t _hashTable, AvlTree_t _tree, Int_t _point, int flag){
    double *point = (double*) _point;
    char *cep = NULL;
    Block_t block = get_tree_node_list_info(_tree, point, get_block_point);
    cep = get_block_cep(block);
    if(block != NULL){
        remove_tree_fp(_tree, point);
        if(flag) {
            remove_hash_table_tree(_hashTable, _tree, cep, 0);
        }
    }
}

void print_person_resident_txt(Resident_t _resident, People_t _person, FILE *txtFile){
    fprintf(txtFile, "\nNome e sobrenome: %s %s, sexo: %c, cpf: %s, data de nascimento: %s\nEndereço: cep: %s, face: %c, numero: %d, complemento: %s\n", get_person_name(_person), get_person_sobrenome(_person), get_person_sex(_person), get_person_cpf(_person), get_person_nasc(_person), get_resident_cep(_resident), get_resident_face(_resident), get_resident_number(_resident), get_resident_compl(_resident));
}
