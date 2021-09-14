#include "treatment.h"
#include <stdio.h>
#include "string.h"
#include "hash_table.h"
#include "pm_treat.h"

void main_treatment(FILE *geoFile, FILE *qryFile, FILE *geoSVGFile, FILE *qrySVGFile, FILE *qryTXTFile, FILE *pmFile){
    int nx = 0;
    double x = 0, y = 0, w = 0, h = 0;
    char aux[5], cep[25], sw[25] = "1.0px", fill[25] = "blue", stroke[25] = "green";
    HashTable_t people = NULL, residents = NULL;

    // Leitura do arquivo.geo
    while(fscanf(geoFile, "%s", aux)!=EOF){
        if((strcmp(aux,"nx"))==0) {
            fscanf(geoFile, "%d", &nx);
        }
        if((strcmp(aux,"q"))==0) {
            // Inserir uma quadra na árvore;
            fscanf(geoFile, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
        }
        if((strcmp(aux,"cq"))==0) {
            fscanf(geoFile, "%s %s %s", sw, fill, stroke);
        }
    }

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
}
