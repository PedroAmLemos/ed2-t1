#include "qry.h"
#include "svg.h"
#include "property_lease.h"
#include "block.h"
#include "resident.h"
#include "wrapper.h"
#include <string.h>
#include <malloc.h>

void del(HashTable_t _residents, HashTable_t _blockTable, HashTable_t _propertyTable, AvlTree_t _blockTree, char *cep, FILE *qryTXTFile, FILE *qrySVGFile) {
    remove_block(_blockTable, _blockTree, remove_hash_table_tree, cep);

    List_t residentsToRemove = get_cep_residents(_residents, cep);
    for(Node_t node = get_list_first(residentsToRemove); node != NULL; node = get_list_next(node)){
        remove_item(_residents, get_list_info(node), 1);
    }
    remove_list(residentsToRemove, NULL);

    List_t propertyToRemove = get_lease_ids(_propertyTable, cep);
    for(Node_t node = get_list_first(propertyToRemove); node != NULL; node = get_list_next(node)){
        remove_item(_propertyTable, get_list_info(node), 1);
    }
    remove_list(propertyToRemove, NULL);
}

void qry_treat(HashTable_t _people, HashTable_t _residents, HashTable_t _blocksTable, AvlTree_t _blocksTree, FILE *qryFile, FILE *qrySVGFile, FILE *qryTXTFile){
    char aux[5], cep[20];
    open_svg(qrySVGFile);
    HashTable_t propertyLeaseTable = NULL;

    while(fscanf(qryFile, "%s", aux) != EOF){
        if(strcmp(aux, "del") == 0) {
            fprintf(qryTXTFile, "del\n");
            fscanf(qryFile, "%s", cep);
            del(_residents, _blocksTable, propertyLeaseTable, _blocksTree, cep, qryTXTFile, qrySVGFile);
        }

    }
    print_tree(get_tree_root(_blocksTree), qrySVGFile, print_block);
    close_svg(qrySVGFile);

}
