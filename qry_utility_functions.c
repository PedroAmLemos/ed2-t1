#include <string.h>
#include "qry_utility_functions.h"
#include "block.h"
#include "svg.h"
#include "wrapper.h"

void loc_print(People_t person, Lease_t property, FILE *qrySVGFile, double x){

    if(person != NULL){
        fprintf(qrySVGFile, "\t<text x=\"%.2f\" y=\"%.2f\">Nome e sobrenome: %s %s, sexo: %c, cpf: %s, data de nascimento: %s</text>\n",
                x, 10.0,
                get_person_name(person), get_person_sobrenome(person), get_person_sex(person), get_person_cpf(person),
                get_person_nasc(person));
    }
    fprintf(qrySVGFile, "\t<text x=\"%.2f\" y=\"%.2f\">Dados da locação: cep: %s, id: %s, face: %c, num: %d, complemento: %s, area: %.2lf e valor: %.2lf</text>\n",
            x, 20.0, get_property_cep(property), get_property_id(property),
            get_property_side(property), get_property_number(property), get_property_compl(property), get_property_ar(property),
            get_property_v(property));
}
void catac_remove(City_t city, char *cep, FILE *qryTXTFile) {
    HashTable_t _blockTable = get_city_blocks_table(city);
    HashTable_t _residents = get_city_resident_table(city);
    HashTable_t _propertyTable = get_city_lease_table(city);
    AvlTree_t _blockTree = get_city_blocks_tree(city);

    Block_t block = get_item(_blockTable, cep);
    if(block != NULL) {
        fprintf(qryTXTFile, "Bloco removido\n");
        print_block_txt(block, qryTXTFile);
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

    if(block != NULL){
        remove_block(_blockTable, _blockTree, remove_hash_table_tree, cep);
    }
}
