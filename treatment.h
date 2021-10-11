#ifndef TREATMENT_H_
#define TREATMENT_H_
#include <stdio.h>

/*
 * Função resposntável pelo tratamento e realização do programa em si, criação da cidade, leitura do arquivo.geo, etc.
 */
void main_treatment(FILE *geoFile, FILE *qryFile, FILE *geoSVGFile, FILE *qrySVGFile, FILE *qryTXTFile, FILE *pmFile, char *outPath);

#endif
