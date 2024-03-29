#include "qry.h"
#include "svg.h"
#include "block.h"
#include <string.h>
#include <stdio.h>
#include "qry_functions.h"

void qry_treat(City_t city, FILE *qryFile, FILE *qrySVGFile, FILE *qryTXTFile, char *outPath){
    char aux[5], cep[25], cpf[20], side, compl[25], id[50], dmptFilename[50];
    double ar, v, x, y, w, h;
    int num;

    open_svg(qrySVGFile);

    while(fscanf(qryFile, "%s", aux) != EOF){
        if(strcmp(aux, "del") == 0) {
            fprintf(qryTXTFile, "del\n");
            fscanf(qryFile, "%s", cep);
            del(city, cep, qryTXTFile, qrySVGFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "m?") == 0){
            fprintf(qryTXTFile, "m?");
            fscanf(qryFile, "%s", cep);
            m(city, cep, qryTXTFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "dm?")==0){
            fprintf(qryTXTFile, "dm?");
            fscanf(qryFile, "%s", cpf);
            dm(city, cpf, qryTXTFile, qrySVGFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "mud") == 0){
            fprintf(qryTXTFile, "mud\n");
            fscanf(qryFile, "%s %s %c %d %s", cpf, cep, &side, &num, compl);
            mud(city, cpf, cep, side, num, compl, qryTXTFile, qrySVGFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "oloc") == 0){
            fprintf(qryTXTFile, "oloc\n");
            fscanf(qryFile, "%s %s %c %d %s %lf %lf", id, cep, &side, &num, compl, &ar, &v);
            oloc(city, id, cep, side, num, compl, ar, v);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "oloc?") == 0){
            fprintf(qryTXTFile, "oloc?\n");
            fscanf(qryFile, "%lf %lf %lf %lf", &x, &y, &w, &h);
            oloc_i(city, x, y,w, h, qryTXTFile, qrySVGFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "loc") == 0){
            fprintf(qryTXTFile, "\nloc\n");
            fscanf(qryFile, "%s %s", id, cpf);
            loc(city, id, cpf, qryTXTFile, qrySVGFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "loc?") == 0){
	        fprintf(qryTXTFile, "loc?\n");
            fscanf(qryFile, "%s", id);
            loc_i(city, id, qryTXTFile, qrySVGFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "dloc") == 0){
            fprintf(qryTXTFile, "dloc\n");
            fscanf(qryFile, "%s", id);
            dloc(city, id, qryTXTFile, qrySVGFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "hom") == 0) {
            fprintf(qryTXTFile, "hom\n");
            fscanf(qryFile, "%lf %lf %lf %lf", &x, &y, &w, &h);
            hom(city, x, y, w, h, qryTXTFile, qrySVGFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "mul") == 0) {
            fprintf(qryTXTFile, "hom\n");
            fscanf(qryFile, "%lf %lf %lf %lf", &x, &y, &w, &h);
            mul(city, x, y, w, h, qryTXTFile, qrySVGFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "dmpt") == 0){
            fscanf(qryFile, "%s", dmptFilename);
            fprintf(qryTXTFile, "dmpt\n");
            dmpt(city, dmptFilename, outPath);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "catac") == 0){
            fscanf(qryFile, "%lf %lf %lf %lf", &x, &y, &w, &h);
            fprintf(qryTXTFile, "catac\n");
            catac(city, x, y, w, h, qryTXTFile, qrySVGFile);
            fprintf(qryTXTFile, "\n\n");
        }
    }
    print_hash_table(get_city_blocks_table(city), qrySVGFile, print_block);
    close_svg(qrySVGFile);

}
