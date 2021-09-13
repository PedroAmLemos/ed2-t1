#include "treatment.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "hash_table.h"

void main_treatment(FILE *geoFile, FILE *qryFile, FILE *geoSVGFile, FILE *qrySVGFile, FILE *qryTXTFile, FILE *pmFile){
    int nx = 0;
    double x = 0, y = 0, w = 0, h = 0;
    char aux[5], cep[25], sw[25] = "1.0px", fill[25] = "blue", stroke[25] = "green";

    // Leitura do arquivo.geo
    while(fscanf(geoFile, "%s", aux)!=EOF){
        if((strcmp(aux,"nx"))==0) {
            fscanf(geoFile, "%d", &nx);
        }
        if((strcmp(aux,"q"))==0) {
            fscanf(geoFile, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
        }
        if((strcmp(aux,"cq"))==0) {
            fscanf(geoFile, "%s %s %s", sw, fill, stroke);
        }
    }

    if(pmFile){
        HashTable_t people = create_hash_table(nx);
        HashTable_t residents = create_hash_table(nx);
    }

}
