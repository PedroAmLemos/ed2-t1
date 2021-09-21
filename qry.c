#include "qry.h"
#include "svg.h"
#include <string.h>
void del(HashTable_t _residents, HashTable_t _blockTable, AvlTree_t _blockTree, char *cep) {
    // TODO: remover a quadra cep
    // TODO: remover os moradores que residem em cep
    // TODO: remover as ofertas de locação
    //remover

}

void qry_treat(HashTable_t _people, HashTable_t _residents, HashTable_t _blocksTable, AvlTree_t _blocksTree, FILE *qryFile, FILE *qrySVGFile, FILE *qryTXTFile){
    char aux[5], cep[20];
    open_svg(qrySVGFile);
    while(fscanf(qryFile, "%s", aux) != EOF){
        if(strcmp(aux, "del") == 0) {
            fprintf(qryTXTFile, "del\n");
            fscanf(qryFile, "%s", cep);
            //comando
        }

    }



}
