#ifndef QRY_UTILITY_FUNCTIONS_H_
#define QRY_UTILITY_FUNCTIONS_H_

#include <stdio.h>
#include "property_lease.h"
#include "people.h"
#include "city.h"

/*
 * Função utilitária do comando loc para impressão no arquivo svg.
 * Pré: recebe um ponteiro do tipo void* para pessoa, outro para propriedade, o arquivo svg para impressão e um valor x.
 */
void loc_print(People_t person, Lease_t property, FILE *qrySVGFile, double x);

/*
 * Função utilitária do comando catac para as remoções de quadra, moradores, etc.
 * Pré: ponteiro para a cidade, o cep da quadra que será removida, o arquivo txt para impressão de dados.
 */
void catac_remove(City_t city, char *cep, FILE *qryTXTFile);
#endif //QRY_UTILITY_FUNCTIONS_H_
