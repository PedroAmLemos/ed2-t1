#include <malloc.h>
#include <string.h>
#include "property_lease.h"

typedef struct {
    char id[50];
    char cep[25];
    char compl[50];
    char side;
    int num;
    double ar;
    double v;


}Lease;

Lease_t create_lease(char id[50], char cep[25], char compl[50], char side, int number, double ar, double v){
    Lease *newLease = (Lease*) malloc(sizeof(Lease));
    strcpy(newLease->cep, cep);
    strcpy(newLease->id, id);
    strcpy(newLease->compl, compl);
    newLease->side=side;
    newLease->num=number;
    newLease->ar=ar;
    newLease->v=v;
    return newLease;
}

char *get_property_cep(Lease_t _property){
    Lease *property = (Lease*) _property;
    return property->cep;
}

char *get_property_id(Lease_t _property) {
    Lease *property = (Lease*) _property;
    return property->id;
}

char *get_property_compl(Lease_t _property){
    Lease *property = (Lease*) _property;
    return property->compl;
}

char get_property_side(Lease_t _property){
    Lease *property = (Lease*) _property;
    return property->side;
}

int get_property_number(Lease_t _property){
    Lease *property = (Lease*) _property;
    return property->num;
}

double get_property_ar(Lease_t _property){
    Lease *property = (Lease*) _property;
    return property->ar;
}

double get_property_v(Lease_t _property){
    Lease *property = (Lease*) _property;
    return property->v;
}

List_t get_lease_ids(HashTable_t _property, char *cep){
    Lease *property = (Lease*) _property;
    List_t propertyToRemove = create_list();
    if(property == NULL )
        return propertyToRemove;
    for(Node_t node = get_list_first(get_table_list(property, cep)); node != NULL; node = get_list_next(node)){
        if(strcmp(get_property_cep(get_item_info(get_list_info(node))), cep) == 0){
            insert_list(propertyToRemove, get_property_id(get_item_info));
        }
    }
    return propertyToRemove;
}

void print_property(Lease_t *_property, FILE *TXTFile){
    Lease *property = (Lease*) _property;
    fprintf(TXTFile, "Dados da locação: cep: %s, id: %s, face: %c, num: %d, complemento: %s, area: %.2lf e valor: %.2lf\n",
            property->cep, property->id, property->side, property->num, property->compl, property->ar, property->v);

}

