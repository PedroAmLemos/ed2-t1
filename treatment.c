#include <stdio.h>
#include "treatment.h"
#include "string.h"
#include "hash_table.h"
#include "pm_treat.h"
#include "avl_tree.h"
#include "block.h"
#include "svg.h"

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
    }

    // print da arvore no svg
    open_svg(geoSVGFile);
    print_tree(get_tree_root(blocksTree), geoSVGFile, print_block);
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
