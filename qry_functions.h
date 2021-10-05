#ifndef QRY_FUNCTIONS_H_
#define QRY_FUNCTIONS_H_


#include "hash_table.h"
#include "avl_tree.h"
#include "city.h"

void del(City_t city, char *cep, FILE *qryTXTFile, FILE *qrySVGFile);

void m(City_t city, char cep[], FILE *qryTXTFile);

void dm(City_t _city, char cpf[], FILE *qryTXTFile, FILE *qrySVGFile);

void mud(City_t city, char cpf[], char cep[], char face, int num, char compl[], FILE *qryTXTFile, FILE *qrySVGFile);

void oloc(City_t city, char id[], char cep[], char side, int num, char compl[], double ar, double v);

void oloc_i(City_t _city, double x, double y, double w, double h, FILE *qryTXTFile, FILE *qrySVGFile);

void loc(City_t city, char id[], char cpf[], FILE *qryTXTFile, FILE *qrySVGFile);

void loc_i(City_t city, char id[], FILE *txtFile, FILE *svgFile);

void dloc(City_t city, char id[], FILE *txtFile, FILE *svgFile);


#endif //QRY_FUNCTIONS_H_
