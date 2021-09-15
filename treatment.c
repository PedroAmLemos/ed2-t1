#include <stdio.h>
#include "treatment.h"
#include "string.h"
#include "hash_table.h"
#include "avl_tree.h"
#include "block.h"
#include "svg.h"
#include "people.h"
#include "resident.h"

void pm_treat(HashTable_t people_, HashTable_t residents_, FILE *pmFile){
    char aux[5];
    char cpf[20];
    char nome[30], sobrenome[30], nasc[11];
    char cep[20], face, compl[25];
    char sex;
    int num;
    while(fscanf(pmFile,"%s", aux)!= EOF){
        if((strcmp(aux,"p")) == 0){
            fscanf(pmFile, "%s %s %s %c %s", cpf, nome, sobrenome, &sex, nasc);
            People_t people = create_people(cpf, nome, sobrenome, sex, nasc);
            insert_hash(people_, get_people_cpf(people), people);
        }
        if((strcmp(aux,"m")) == 0) {
            fscanf(pmFile, "%s %s %s %d %s", cpf, cep, &face, &num, compl);
            Resident_t resident = create_resident(cpf, cep, face, num, compl);
            insert_hash(residents_, get_resident_cpf(resident), resident);
        }
    }
}

void main_treatment(FILE *geoFile, FILE *qryFile, FILE *geoSVGFile, FILE *qrySVGFile, FILE *qryTXTFile, FILE *pmFile){
    int nx = 0;
    double x = 0, y = 0, w = 0, h = 0;
    char aux[5], cep[20], sw[25] = "1.0px", fill[25] = "blue", stroke[25] = "green";
    HashTable_t people = NULL, residents = NULL;
    AvlTree_t blocksTree = create_tree("Blocks");
    Block_t block = NULL;

    fscanf(geoFile, "%s", aux);
    if((strcmp(aux,"nx"))==0) {
        fscanf(geoFile, "%d", &nx);
    }else{
        nx = 5000;
        rewind(geoFile);
    }

    HashTable_t blocksTable = create_hash_table(nx);

    while(fscanf(geoFile, "%s", aux)!=EOF){
        if((strcmp(aux,"q"))==0) {
            fscanf(geoFile, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
            block = create_block(cep, x, y, w, h, sw, stroke, fill);
            insert_tree(blocksTree, block, x);
            insert_hash(blocksTable, cep, block);
        }
        if((strcmp(aux, "cq"))==0){
            fscanf(geoFile, "%s %s %s", sw, fill, stroke);
        }
    }

    // print da arvore no svg
    open_svg(geoSVGFile);
    // print_tree(get_tree_root(blocksTree), geoSVGFile, print_block);
    print_hash_table(blocksTable, geoSVGFile, print_block);
    close_svg(geoSVGFile);


    if(pmFile){
        people = create_hash_table(nx);
        residents = create_hash_table(nx);
        pm_treat(people, residents, pmFile);
    }


    // qry

    if(pmFile){
        delete_hash_table(people, 1);
        delete_hash_table(residents, 1);
    }

    delete_hash_table(blocksTable, 1);
    delete_tree(blocksTree);
}
