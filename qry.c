#include "qry.h"
#include "svg.h"
#include "property_lease.h"
#include "block.h"
#include "resident.h"
#include "wrapper.h"
#include <string.h>
#include <stdio.h>

void del(HashTable_t _residents, HashTable_t _blockTable, HashTable_t _propertyTable, AvlTree_t _blockTree, char *cep, FILE *qryTXTFile, FILE *qrySVGFile) {
    Block_t block = get_item(_blockTable, cep);
    if(block != NULL){
        fprintf(qryTXTFile, "Bloco removido\n");
        print_block_txt(block, qryTXTFile);
        double x1 = (get_block_x(block) + get_block_width(block)/2);
        double y1 = (get_block_y(block) + get_block_height(block)/2);
        double x2 = (get_block_x(block) + get_block_width(block)/2);
        print_line(x1, y1, x2, 0.0, "black", qrySVGFile);
        print_text(x1, 15.0, get_block_cep(block), qrySVGFile);
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
        print_person_resident_txt(resident, person, qryTXTFile);
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
    print_person_resident_txt(resident, person, qryTXTFile);
    if(is_person_renting(resident)){
        fprintf(qryTXTFile, "A moradia é alugada\n");
    }else{
        fprintf(qryTXTFile, "A moradia não é alugada\n");
    }
    Block_t block = get_item(_blocksTable, get_resident_cep(resident));
    double x1 = (get_block_x(block) + get_block_width(block)/2);
    double y1 = (get_block_y(block) + get_block_height(block)/2);
    double x2 = (get_block_x(block) + get_block_width(block)/2);
    print_line(x1, y1, x2, 0.0, "black", qrySVGFile);
    fprintf(qrySVGFile, "\t<text x=\"%.2lf\" y=\"%.2lf\">cpf: %s, name: %s, cep: %s, num: %d, face: %c, compl: %s</text>\n",
            (get_block_x(block) + get_block_width(block)/2), 15.0, get_block_cep(block), get_person_name(person),
            get_resident_cep(resident), get_resident_number(resident), get_resident_face(resident), get_resident_compl(resident));
}

void mud(HashTable_t _residents, HashTable_t _people, HashTable_t _blocksTable, char cpf[], char cep[], char face, int num, char compl[], FILE *qryTXTFile, FILE *qrySVGFile){
    Resident_t resident = get_item(_residents, cpf);
    People_t person = get_item(_people, cpf);
    Block_t oldBlock = get_item(_blocksTable, get_resident_cep(resident));
    Block_t newBlock = get_item(_blocksTable, cep);

    print_person_resident_txt(resident, person, qryTXTFile);

    double cx = (get_block_x(oldBlock) + get_block_width(oldBlock)/2);
    double cy = (get_block_y(oldBlock) + get_block_height(oldBlock)/2);
    print_circle(cx, cy, 10.0, "white", "red", "5px", qrySVGFile);

    fprintf(qrySVGFile, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" ", (get_block_x(oldBlock) + get_block_width(oldBlock)/ 2),
            (get_block_y(oldBlock) + get_block_height(oldBlock)/2));

    change_resident_address(resident, cep, cpf, face, num, compl);
    fprintf(qryTXTFile, "Endereço novo: cep: %s, face: %c, num: %d, complemento: %s\n", get_resident_cep(resident),
            get_resident_face(resident), get_resident_number(resident), get_resident_compl(resident));
    fprintf(qrySVGFile, "x2=\"%.2lf\" y2=\"%.2lf\" stroke=\"red\" fill=\"red\" stroke-width=\"5px\"/>\n", (get_block_x(newBlock) + get_block_width(newBlock)/2), (get_block_y(newBlock) + get_block_height(newBlock)/2));

    cx = (get_block_x(newBlock) + get_block_width(newBlock)/2);
    cy = (get_block_y(newBlock) + get_block_height(newBlock)/2);
    print_circle(cx, cy, 10.0, "white", "red", "5px", qrySVGFile);
}

void oloc(HashTable_t propertyLeaseTable, char id[], char cep[], char side, int num, char compl[], double ar, double v){
    Lease_t newLease = create_lease(id, cep, compl, side, num, ar, v);
    insert_hash(propertyLeaseTable, id, newLease);
}

void oloc_i(HashTable_t propertyLeaseTable, HashTable_t _blocksTable, double x, double y, double w, double h, FILE *qryTXTFile, FILE *qrySVGFile){
    char face;
    List_t propertyLeaseList = NULL;
    Block_t block = NULL;
    Lease_t property = NULL;
    print_rectangle_dashed(x, y, w, h, qrySVGFile);
    for (int i = 0; i < get_table_size(propertyLeaseTable); ++i) {
        propertyLeaseList = get_index_list(propertyLeaseTable, i);
        for(Node_t node = get_list_first(propertyLeaseList); node != NULL; node = get_list_next(node)){
            property = get_item_info(get_list_info(node));
            block = get_info_from_key(_blocksTable, get_property_cep(property));
            if(block != NULL){
                if(is_block_inside_rect(block, x, y, w, h)){
                    print_property(property, qryTXTFile);
                    print_rectangle_dashed(x, y, w, h, qrySVGFile);
                    face = get_property_side(property);
                    if(face == 'N'){
                        print_text(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + get_block_height(block), "*", qrySVGFile);
                    }
                    else if(face == 'S'){
                        print_text(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + 20, "*", qrySVGFile);
                    }
                    else if(face == 'L'){
                        print_text(get_block_x(block) + 8, get_block_y(block) + get_block_height(block) * 0.5, "*", qrySVGFile);
                    }
                    else if(face == 'O'){
                        print_text(get_block_x(block) + get_block_width(block) - 10, get_block_y(block) + get_block_height(block) * 0.5, "*", qrySVGFile);
                    }
                }
            }
        }
    }

}

void loc(HashTable_t _blocksTable, HashTable_t _people, HashTable_t _residents, HashTable_t propertyLeaseTable, char id[], char cpf[], FILE *qryTXTFile, FILE *qrySVGFile){
    Lease_t property = get_item(propertyLeaseTable, id);
    People_t person = get_item(_people, cpf);
    Resident_t resident = create_resident(cpf, get_property_cep(property), get_property_side(property), get_property_number(property), get_property_compl(property));
    Block_t block = get_item(_blocksTable, get_property_cep(property));
    change_resident_to_rent(resident);
    insert_hash(_residents, cpf, resident);
    change_property_status(property, 1);
    print_property(property, qryTXTFile);
    print_person_resident_txt(resident, person, qryTXTFile);
    char face = get_property_side(property);
    if(face == 'N'){
        print_line(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + get_block_height(block),
                   get_block_x(block) + get_block_width(block)/2, 10, "black", qrySVGFile);
        fprintf(qrySVGFile, "\t<text x=\"%.2f\" y=\"%.2f\">Nome e sobrenome: %s %s, sexo: %c, cpf: %s, data de nascimento: %s</text>\n",
                get_block_x(block) + get_block_width(block)/2, 10.0,
                get_person_name(person), get_person_sobrenome(person), get_person_sex(person), get_person_cpf(person),
                get_person_nasc(person));
        fprintf(qrySVGFile, "\t<text x=\"%.2f\" y=\"%.2f\">Dados da locação: cep: %s, id: %s, face: %c, num: %d, complemento: %s, area: %.2lf e valor: %.2lf</text>\n",
                get_block_x(block) + get_block_width(block)/2, 10.0, get_property_cep(property), get_property_id(property),
                get_property_side(property), get_property_number(property), get_property_compl(property), get_property_ar(property),
                get_property_v(property));
    }
    else if(face == 'S'){
        print_line(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + 20,
                   get_block_x(block) + get_block_width(block)/2, 10, "black", qrySVGFile);
        fprintf(qrySVGFile, "\t<text x=\"%.2f\" y=\"%.2f\">Nome e sobrenome: %s %s, sexo: %c, cpf: %s, data de nascimento: %s</text>\n",
                get_block_x(block) + get_block_width(block)/2, 10.0,
                get_person_name(person), get_person_sobrenome(person), get_person_sex(person), get_person_cpf(person),
                get_person_nasc(person));
        fprintf(qrySVGFile, "\t<text x=\"%.2f\" y=\"%.2f\">Dados da locação: cep: %s, id: %s, face: %c, num: %d, complemento: %s, area: %.2lf e valor: %.2lf</text>\n",
                get_block_x(block) + get_block_width(block)/2, 10.0, get_property_cep(property), get_property_id(property),
                get_property_side(property), get_property_number(property), get_property_compl(property), get_property_ar(property),
                get_property_v(property));
    }
    else if(face == 'L'){
        print_line(get_block_x(block) + 8, get_block_y(block) + get_block_height(block) * 0.5,
                   get_block_x(block) + 8, 10, "black", qrySVGFile);
        fprintf(qrySVGFile, "\t<text x=\"%.2f\" y=\"%.2f\">Nome e sobrenome: %s %s, sexo: %c, cpf: %s, data de nascimento: %s</text>\n",
                get_block_x(block) + 8, 10.0,
                get_person_name(person), get_person_sobrenome(person), get_person_sex(person), get_person_cpf(person),
                get_person_nasc(person));
        fprintf(qrySVGFile, "\t<text x=\"%.2f\" y=\"%.2f\">Dados da locação: cep: %s, id: %s, face: %c, num: %d, complemento: %s, area: %.2lf e valor: %.2lf</text>\n",
                get_block_x(block) + get_block_width(block)/2, 10.0, get_property_cep(property), get_property_id(property),
                get_property_side(property), get_property_number(property), get_property_compl(property), get_property_ar(property),
                get_property_v(property));
    }
    else if(face == 'O'){
        print_line(get_block_x(block) + get_block_width(block) - 10, get_block_y(block) + get_block_height(block) * 0.5,
                   get_block_x(block) + get_block_width(block) - 10, 10, "black", qrySVGFile);
        fprintf(qrySVGFile, "\t<text x=\"%.2f\" y=\"%.2f\">Nome e sobrenome: %s %s, sexo: %c, cpf: %s, data de nascimento: %s</text>\n",
                get_block_x(block) + get_block_width(block) - 10 + 8, 10.0,
                get_person_name(person), get_person_sobrenome(person), get_person_sex(person), get_person_cpf(person),
                get_person_nasc(person));
        fprintf(qrySVGFile, "\t<text x=\"%.2f\" y=\"%.2f\">Dados da locação: cep: %s, id: %s, face: %c, num: %d, complemento: %s, area: %.2lf e valor: %.2lf</text>\n",
                get_block_x(block), 10.0, get_property_cep(property), get_property_id(property),
                get_property_side(property), get_property_number(property), get_property_compl(property), get_property_ar(property),
                get_property_v(property));
    }
    fprintf(qryTXTFile, "\n");
}

void qry_treat(HashTable_t _people, HashTable_t _residents, HashTable_t _blocksTable, AvlTree_t _blocksTree, FILE *qryFile, FILE *qrySVGFile, FILE *qryTXTFile){
    char aux[5], cep[25], cpf[20], side, compl[25], id[50];
    double ar, v, x, y, w, h;
    int num;
    open_svg(qrySVGFile);
    HashTable_t propertyLeaseTable = create_hash_table(1117);

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
        if(strcmp(aux, "mud") == 0){
            fprintf(qryTXTFile, "mud\n");
            fscanf(qryFile, "%s %s %c %d %s", cpf, cep, &side, &num, compl);
            mud(_residents, _people, _blocksTable, cpf, cep, side, num, compl, qryTXTFile, qrySVGFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "oloc") == 0){
            fprintf(qryTXTFile, "oloc\n");
            fscanf(qryFile, "%s %s %c %d %s %lf %lf", id, cep, &side, &num, compl, &ar, &v);
            oloc(propertyLeaseTable, id, cep, side, num, compl, ar, v);
        }
        if(strcmp(aux, "oloc?") == 0){
            fprintf(qryTXTFile, "oloc?\n");
            fscanf(qryFile, "%lf %lf %lf %lf", &x, &y, &w, &h);
            oloc_i(propertyLeaseTable, _blocksTable, x, y,w, h, qryTXTFile, qrySVGFile);
        }
        if(strcmp(aux, "loc") == 0){
            fprintf(qryTXTFile, "\nloc\n");
            fscanf(qryFile, "%s %s", id, cpf);
             loc(_blocksTable, _people, _residents, propertyLeaseTable, id, cpf, qryTXTFile, qrySVGFile);
        }



    }
    delete_hash_table(propertyLeaseTable, 1);
    print_tree(get_tree_root(_blocksTree), qrySVGFile, print_block);
    close_svg(qrySVGFile);

}
