#include "qry.h"
#include "svg.h"
#include "block.h"
#include <string.h>
#include <stdio.h>
#include "qry_functions.h"

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
        if(strcmp(aux, "loc?") == 0){
	        fprintf(qryTXTFile, "loc?\n");
            fscanf(qryFile, "%s", id);
        }


    }
    delete_hash_table(propertyLeaseTable, 1);
    print_tree(get_tree_root(_blocksTree), qrySVGFile, print_block);
    close_svg(qrySVGFile);

}
