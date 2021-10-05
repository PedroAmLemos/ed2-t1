#ifndef QRY_UTILITY_FUNCTIONS_H_
#define QRY_UTILITY_FUNCTIONS_H_

#include <stdio.h>
#include "property_lease.h"
#include "people.h"
#include "city.h"

void loc_print(People_t person, Lease_t property, FILE *qrySVGFile, double x);

void catac_remove(City_t city, char *cep, FILE *qryTXTFile);

#endif //QRY_UTILITY_FUNCTIONS_H_
