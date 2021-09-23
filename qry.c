#include "qry.h"
#include "svg.h"
#include "property_lease.h"
#include "block.h"
#include "resident.h"
#include "wrapper.h"
#include "people.h"
#include <string.h>
#include <stdio.h>

void del(HashTable_t _residents, HashTable_t _blockTable, HashTable_t _propertyTable, AvlTree_t _blockTree, char *cep, FILE *qryTXTFile, FILE *qrySVGFile) {
    Block_t block = get_item(_blockTable, cep);
    if(block != NULL){
        fprintf(qryTXTFile, "Bloco removido\ncep: %s\nponto: x = %.2lf, y = %.2lf\nlargura = %.2lf, "
                            "altura = %.2lf\nespessura da borda: %s, cor de preenchimento: %s, cor da borda: %s\n\n",
                            get_block_cep(block), get_block_x(block), get_block_y(block), get_block_width(block),
                            get_block_height(block), get_block_sw(block), get_block_fill(block), get_block_stroke(block));
        fprintf(qrySVGFile, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"0\" stroke=\"black\" opacity=\"0.6\"/>\n",
                (get_block_x(block) + get_block_width(block)/2), (get_block_y(block) + get_block_height(block)/2), (get_block_x(block) + get_block_width(block)/2));
        fprintf(qrySVGFile, "\t<text x=\"%.2lf\" y=\"%.2lf\">%s</text>\n", (get_block_x(block) + get_block_width(block)/2), 15.0, get_block_cep(block));
        remove_block(_blockTable, _blockTree, remove_hash_table_tree, cep);
    }

    List_t residentsToRemove = get_cep_residents(_residents, cep);
    Resident_t resident;
    for(Node_t node = get_list_first(residentsToRemove); node != NULL; node = get_list_next(node)){
        resident = get_item(_residents, get_list_info(node));
        fprintf(qryTXTFile, "Morador removido\ncpf: %s\ncep: %s\nface: %c\nnumero: %d\ncomplemento: %s\n\n",
               get_resident_cpf(resident), get_resident_cep(resident), get_resident_face(resident), get_resident_number(resident),
               get_resident_compl(resident));
        remove_item(_residents, get_list_info(node), 1);
    }
    remove_list(residentsToRemove, NULL);

    List_t propertyToRemove = get_lease_ids(_propertyTable, cep);
    Lease_t property;
    for(Node_t node = get_list_first(propertyToRemove); node != NULL; node = get_list_next(node)){
        property = get_item(_propertyTable, get_list_info(node));
        fprintf(qryTXTFile, "Locação removida\nid: %s\ncep: %s\ncomplemento: %s\nlado: %c\nnumero: %d\narea: %.2lf\nvalor "
                            "mensal: %.2lf reais\n\n", get_property_id(property), get_property_cep(property),
                get_property_compl(property), get_property_side(property), get_property_number(property),
                get_property_ar(property), get_property_v(property));
        remove_item(_propertyTable, get_list_info(node), 1);
    }
    remove_list(propertyToRemove, NULL);
}

void m(HashTable_t _residents, HashTable_t _people, HashTable_t _blocksTable, char cep[], FILE *qryTXTFile){
    Block_t block = get_item(_blocksTable, cep);
    if(block == NULL){
        printf("Erro - quadra não encontrada");
        return;
    }
    List_t residentsToPrint = get_cep_residents(_residents, cep);
    Resident_t resident;
    People_t person;
    for(Node_t node = get_list_first(residentsToPrint); node != NULL; node = get_list_next(node)){
        resident = get_item(_residents, get_list_info(node));
        person   = get_item(_people, get_list_info(node));
        fprintf(qryTXTFile, "\nNome e sobrenome: %s %s, sexo: %c, cpf: %s, data de nascimento: %s\nEndereço: cep: %s, face: %c, numero: %d, complemento: %s\n",
                get_person_name(person), get_person_sobrenome(person), get_person_sex(person), get_person_cpf(person),
                get_person_nasc(person), get_resident_cep(resident), get_resident_face(resident), get_resident_number(resident),
                get_resident_compl(resident));
    }
    remove_list(residentsToPrint, NULL);
}

void dm(HashTable_t _residents, HashTable_t _people, HashTable_t _blocksTable, char cpf[], FILE *qryTXTFile, FILE *qrySVGFile){
    Resident_t resident = get_item(_residents, cpf);
    People_t person     = get_item(_people, cpf);
    if(person == NULL || resident == NULL){
        fprintf(qryTXTFile, " Morador não existe\n");
        return;
    }
    fprintf(qryTXTFile, "\nNome e sobrenome: %s %s, sexo: %c, cpf: %s, data de nascimento: %s\nEndereço: cep: %s, face: %c, numero: %d, complemento: %s, ",
            get_person_name(person), get_person_sobrenome(person), get_person_sex(person), get_person_cpf(person),
            get_person_nasc(person), get_resident_cep(resident), get_resident_face(resident), get_resident_number(resident),
            get_resident_compl(resident));
    if(is_person_renting(resident)){
        fprintf(qryTXTFile, "A moradia é alugada\n");
    }else{
        fprintf(qryTXTFile, "A moradia não é alugada\n");
    }
    Block_t block = get_item(_blocksTable, get_resident_cep(resident));
    fprintf(qrySVGFile, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"0\" stroke=\"black\" opacity=\"0.6\"/>\n",
            (get_block_x(block) + get_block_width(block)/2), (get_block_y(block) + get_block_height(block)/2), (get_block_x(block) + get_block_width(block)/2));
    fprintf(qrySVGFile, "\t<text x=\"%.2lf\" y=\"%.2lf\">cpf: %s, name: %s, cep: %s, num: %d, face: %c, compl: %s</text>\n",
            (get_block_x(block) + get_block_width(block)/2), 15.0, get_block_cep(block), get_person_name(person),
            get_resident_cep(resident), get_resident_number(resident), get_resident_face(resident), get_resident_compl(resident));
}

void qry_treat(HashTable_t _people, HashTable_t _residents, HashTable_t _blocksTable, AvlTree_t _blocksTree, FILE *qryFile, FILE *qrySVGFile, FILE *qryTXTFile){
    char aux[5], cep[25], cpf[20];
    open_svg(qrySVGFile);
    HashTable_t propertyLeaseTable = NULL;

    while(fscanf(qryFile, "%s", aux) != EOF){
        if(strcmp(aux, "del") == 0) {
            fprintf(qryTXTFile, "del\n");
            fscanf(qryFile, "%s", cep);
            del(_residents, _blocksTable, propertyLeaseTable, _blocksTree, cep, qryTXTFile, qrySVGFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "m?") == 0){
            fprintf(qryTXTFile, "m?");
            fscanf(qryFile, "%s", cep);
            m(_residents, _people, _blocksTable, cep, qryTXTFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "dm?")==0){
            fprintf(qryTXTFile, "dm?");
            fscanf(qryFile, "%s", cpf);
            dm(_residents, _people, _blocksTable, cpf, qryTXTFile, qrySVGFile);
            fprintf(qryTXTFile, "\n\n");
        }

    }
    print_tree(get_tree_root(_blocksTree), qrySVGFile, print_block);
    close_svg(qrySVGFile);

}
