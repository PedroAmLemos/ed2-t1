#include "qry_functions.h"
#include "svg.h"
#include "property_lease.h"
#include "qry_utility_functions.h"
#include "block.h"
#include "resident.h"
#include "wrapper.h"
#include "reading_utility.h"
#include <string.h>
#include <stdio.h>

void del(City_t city, char *cep, FILE *qryTXTFile, FILE *qrySVGFile) {
    HashTable_t _blockTable = get_city_blocks_table(city);
    HashTable_t _residents = get_city_resident_table(city);
    HashTable_t _propertyTable = get_city_lease_table(city);
    AvlTree_t _blockTree = get_city_blocks_tree(city);

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

void m(City_t city, char cep[], FILE *qryTXTFile){
    HashTable_t _blocksTable = get_city_blocks_table(city);
    HashTable_t _residents = get_city_resident_table(city);
    HashTable_t _people = get_city_people_table(city);

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

void dm(City_t city, char cpf[], FILE *qryTXTFile, FILE *qrySVGFile){
    HashTable_t _blocksTable = get_city_blocks_table(city);
    HashTable_t _residents = get_city_resident_table(city);
    HashTable_t _people = get_city_people_table(city);
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

void mud(City_t city, char cpf[], char cep[], char face, int num, char compl[], FILE *qryTXTFile, FILE *qrySVGFile){
    HashTable_t _blocksTable = get_city_blocks_table(city);
    HashTable_t _residents = get_city_resident_table(city);
    HashTable_t _people = get_city_people_table(city);
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

void oloc(City_t city, char id[], char cep[], char side, int num, char compl[], double ar, double v){
    HashTable_t propertyLeaseTable = get_city_lease_table(city);
    Lease_t newLease = create_lease(id, cep, compl, side, num, ar, v);
    insert_hash(propertyLeaseTable, id, newLease);
}

void oloc_i(City_t city, double x, double y, double w, double h, FILE *qryTXTFile, FILE *qrySVGFile){
    HashTable_t _blocksTable = get_city_blocks_table(city);
    HashTable_t propertyLeaseTable = get_city_lease_table(city);
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
                }
            }
        }
    }
}

void loc(City_t city, char id[], char cpf[], FILE *qryTXTFile, FILE *qrySVGFile){

    HashTable_t _blocksTable = get_city_blocks_table(city);
    HashTable_t _residents = get_city_resident_table(city);
    HashTable_t _people = get_city_people_table(city);
    HashTable_t propertyLeaseTable = get_city_lease_table(city);

    Lease_t property = get_item(propertyLeaseTable, id);
    if(property == NULL){
        return;
    }
    People_t person = get_item(_people, cpf);
    Block_t block = get_item(_blocksTable, get_property_cep(property));

    Resident_t resident = create_resident(cpf, get_property_cep(property), get_property_side(property), get_property_number(property), get_property_compl(property));

    change_resident_to_rent(resident);
    insert_hash(_residents, cpf, resident);
    change_property_status(property, 1);
    add_lessee(property, cpf);

    print_property(property, qryTXTFile);
    print_person_resident_txt(resident, person, qryTXTFile);
    char face = get_property_side(property);
    if(face == 'N'){
        print_line(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + get_block_height(block),
                   get_block_x(block) + get_block_width(block)/2, 10, "black", qrySVGFile);
        loc_print(person, property, qrySVGFile, (get_block_x(block) + get_block_width(block)/2));
    }
    else if(face == 'S'){
        print_line(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + 20,
                   get_block_x(block) + get_block_width(block)/2, 10, "black", qrySVGFile);
        loc_print(person, property, qrySVGFile, get_block_x(block) + get_block_width(block)/2);
    }
    else if(face == 'L'){
        print_line(get_block_x(block) + 8, get_block_y(block) + get_block_height(block) * 0.5,
                   get_block_x(block) + 8, 10, "black", qrySVGFile);
        loc_print(person, property, qrySVGFile, get_block_x(block) + 8);
    }
    else if(face == 'O'){
        print_line(get_block_x(block) + get_block_width(block) - 10, get_block_y(block) + get_block_height(block) * 0.5,
                   get_block_x(block) + get_block_width(block) - 10, 10, "black", qrySVGFile);
        loc_print(person, property, qrySVGFile, get_block_x(block) + get_block_width(block) - 10 + 8);
    }
    fprintf(qryTXTFile, "\n");
}

void loc_i(City_t city, char id[], FILE *txtFile, FILE *svgFile){
    HashTable_t propertyLeaseTable = get_city_lease_table(city);
    HashTable_t blocksTable = get_city_blocks_table(city);
    Lease_t property = get_item(propertyLeaseTable, id);
    if(property == NULL){
        return;
    }
    Block_t block = get_item(blocksTable, get_property_cep(property));

    int status = get_property_status(property);
    char face = get_property_side(property);
    if(status == 0){
        // não alugada
        fprintf(txtFile, "Casa não alugada\n");
        print_property(property, txtFile);

        if(face == 'N'){
            print_text(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + get_block_height(block),
                       "*", svgFile);
        }
        else if(face == 'S'){
            print_text(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + 20,
                       "*", svgFile);
        }
        else if(face == 'L'){
            print_text(get_block_x(block) + 8, get_block_y(block) + get_block_height(block) * 0.5,
                       "*", svgFile);
        }
        else if(face == 'O'){
            print_text(get_block_x(block) + get_block_width(block) - 10, get_block_y(block) + get_block_height(block) * 0.5,
                       "*", svgFile);
        }
    }
    else if(status == 1){
        fprintf(txtFile, "Casa alugada\n");
        print_property(property, txtFile);
        if(face == 'N'){
            print_text(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + get_block_height(block),
                       "$", svgFile);
        }
        else if(face == 'S'){
            print_text(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + 20,
                       "$", svgFile);
        }
        else if(face == 'L'){
            print_text(get_block_x(block) + 8, get_block_y(block) + get_block_height(block) * 0.5,
                       "$", svgFile);
        }
        else if(face == 'O'){
            print_text(get_block_x(block) + get_block_width(block) - 10, get_block_y(block) + get_block_height(block) * 0.5,
                       "$", svgFile);
        }
    }
}

void dloc(City_t city, char id[], FILE *txtFile, FILE *svgFile){
    HashTable_t propertyLeaseTable = get_city_lease_table(city);
    HashTable_t blocksTable = get_city_blocks_table(city);
    HashTable_t residentsTable = get_city_resident_table(city);
    HashTable_t peopleTable = get_city_people_table(city);

    Lease_t property = get_item(propertyLeaseTable, id);

    Resident_t resident = get_item(residentsTable, get_lessee(property));
    People_t person = get_item(peopleTable, get_lessee(property));
    Block_t block = get_item(blocksTable, get_property_cep(property));

    change_property_status(property, 2);
    fprintf(txtFile, "Locação com o contrato encerrado:\n");
    print_property(property, txtFile);
    if(get_property_status(property) != 1){
        fprintf(txtFile, "Propriedade sem morador\n");
    }else{
        fprintf(txtFile, "Morador removido:\n");
        print_person_resident_txt(resident, person, txtFile);
        remove_item(residentsTable, get_lessee(property), 1);
    }

    char face = get_property_side(property);
    if(face == 'N'){
        print_line(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + get_block_height(block),
                   get_block_x(block) + get_block_width(block)/2, 10, "black", svgFile);
        loc_print(person, property, svgFile, (get_block_x(block) + get_block_width(block)/2));
    }
    else if(face == 'S'){
        print_line(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + 20,
                   get_block_x(block) + get_block_width(block)/2, 10, "black", svgFile);
        loc_print(person, property, svgFile, get_block_x(block) + get_block_width(block)/2);
    }
    else if(face == 'L'){
        print_line(get_block_x(block) + 8, get_block_y(block) + get_block_height(block) * 0.5,
                   get_block_x(block) + 8, 10, "black", svgFile);
        loc_print(person, property, svgFile, get_block_x(block) + 8);
    }
    else if(face == 'O'){
        print_line(get_block_x(block) + get_block_width(block) - 10, get_block_y(block) + get_block_height(block) * 0.5,
                   get_block_x(block) + get_block_width(block) - 10, 10, "black", svgFile);
        loc_print(person, property, svgFile, get_block_x(block) + get_block_width(block) - 10 + 8);
    }

    remove_item(propertyLeaseTable, id, 1);
    fprintf(txtFile, "\n");
}

void hom(City_t city, double x, double y, double w, double h, FILE *txtFile, FILE *qrySVGFile){
    HashTable_t _blocksTable = get_city_blocks_table(city);
    HashTable_t propertyLeaseTable = get_city_lease_table(city);
    char face;
    List_t propertyLeaseList = NULL;
    Block_t block = NULL;
    Lease_t property = NULL;
    for (int i = 0; i < get_table_size(propertyLeaseTable); ++i) {
        propertyLeaseList = get_index_list(propertyLeaseTable, i);
        for(Node_t node = get_list_first(propertyLeaseList); node != NULL; node = get_list_next(node)){
            property = get_item_info(get_list_info(node));
            block = get_info_from_key(_blocksTable, get_property_cep(property));
            if(block != NULL){
                if(is_block_inside_rect(block, x, y, w, h) && get_property_status(property) == 1){
                    print_property(property, txtFile);
                    print_person_resident_txt(get_item(get_city_resident_table(city), get_lessee(property)), get_item(get_city_people_table(city), get_lessee(property)), txtFile);
                    face = get_property_side(property);
                    if(face == 'N'){
                        print_circle(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + get_block_height(block), 2, "black", "blue", "2px", qrySVGFile);
                    }
                    else if(face == 'S'){
                        print_circle(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + 20, 2, "black", "blue", "2px", qrySVGFile);
                    }
                    else if(face == 'L'){
                        print_circle(get_block_x(block) + 8, get_block_y(block) + get_block_height(block) * 0.5, 2, "black", "blue", "2px", qrySVGFile);
                    }
                    else if(face == 'O'){
                        print_circle(get_block_x(block) + get_block_width(block) - 10, get_block_y(block) + get_block_height(block) * 0.5, 2, "black", "blue", "2px", qrySVGFile);
                    }
                }
            }
        }
    }


}

void mul(City_t city, double x, double y, double w, double h, FILE *txtFile, FILE *qrySVGFile){
    HashTable_t _blocksTable = get_city_blocks_table(city);
    HashTable_t propertyLeaseTable = get_city_lease_table(city);
    char face;
    List_t propertyLeaseList = NULL;
    Block_t block = NULL;
    Lease_t property = NULL;
    for (int i = 0; i < get_table_size(propertyLeaseTable); ++i) {
        propertyLeaseList = get_index_list(propertyLeaseTable, i);
        for(Node_t node = get_list_first(propertyLeaseList); node != NULL; node = get_list_next(node)){
            property = get_item_info(get_list_info(node));
            block = get_info_from_key(_blocksTable, get_property_cep(property));
            if(block != NULL){
                if(is_block_inside_rect(block, x, y, w, h) && get_property_status(property) == 1){
                    print_property(property, txtFile);
                    print_person_resident_txt(get_item(get_city_resident_table(city), get_lessee(property)), get_item(get_city_people_table(city), get_lessee(property)), txtFile);
                    face = get_property_side(property);
                    if(face == 'N'){
                        print_circle(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + get_block_height(block), 2, "black", "pink", "2px", qrySVGFile);
                    }
                    else if(face == 'S'){
                        print_circle(get_block_x(block) + get_block_width(block)/2, get_block_y(block) + 20, 2, "black", "pink", "2px", qrySVGFile);
                    }
                    else if(face == 'L'){
                        print_circle(get_block_x(block) + 8, get_block_y(block) + get_block_height(block) * 0.5, 2, "black", "pink", "2px", qrySVGFile);
                    }
                    else if(face == 'O'){
                        print_circle(get_block_x(block) + get_block_width(block) - 10, get_block_y(block) + get_block_height(block) * 0.5, 2, "black", "pink", "2px", qrySVGFile);
                    }
                }
            }
        }
    }


}

void dmpt(City_t city, char *fileName, char *outPath){
    char *dmptFile = NULL;
    char *dmptFilePath = NULL;
    dmptFilePath = concat_path_file(outPath, fileName);
    dmptFile = malloc(sizeof(char) * (strlen(dmptFilePath)+ 9));

    strcpy(dmptFile, dmptFilePath);
    strcat(dmptFile, "-sfx.dot");

    FILE *dmpt = fopen(dmptFile, "w");
    AvlTreeNode_t root = get_tree_root(get_city_blocks_tree(city));
    int size = get_table_size(get_city_blocks_table(city));

    fprintf(dmpt,"digraph T {\n");
    fprintf(dmpt, "\tsize=\"%d\"\n", size*20);
    fprintf(dmpt, "\tnode [color=purple, style=filled]\n");

    print_dmpt(root, dmpt);

    fprintf(dmpt,"}\n");
    fclose(dmpt);
    free(dmptFilePath);
    free(dmptFile);



}

void catac(City_t city, double x, double y, double w, double h, FILE *txtFile, FILE *svgFile){
    HashTable_t blocksTable = get_city_blocks_table(city);
    AvlTree_t tree = get_city_blocks_tree(city);
    Block_t block;
    char *cep;
    print_rectangle_dashed(0, 0, 1500, 1500, svgFile);

    List_t cepsToRemove = get_inside(tree, x, y, w, h);

    for(Node_t node = get_list_first(cepsToRemove); node != NULL; node = get_list_next(node)){
        cep = get_list_info(node);
        block = get_item(blocksTable, cep);
        print_catac_block(block, svgFile);
        catac_remove(city, cep, txtFile);
    }



    remove_list(cepsToRemove, NULL);
}