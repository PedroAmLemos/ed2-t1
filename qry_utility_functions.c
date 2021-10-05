#include <string.h>
#include "qry_utility_functions.h"
void loc_print(People_t person, Lease_t property, FILE *qrySVGFile, double x){

    if(person != NULL){
        fprintf(qrySVGFile, "\t<text x=\"%.2f\" y=\"%.2f\">Nome e sobrenome: %s %s, sexo: %c, cpf: %s, data de nascimento: %s</text>\n",
                x, 10.0,
                get_person_name(person), get_person_sobrenome(person), get_person_sex(person), get_person_cpf(person),
                get_person_nasc(person));
    }
    fprintf(qrySVGFile, "\t<text x=\"%.2f\" y=\"%.2f\">Dados da locação: cep: %s, id: %s, face: %c, num: %d, complemento: %s, area: %.2lf e valor: %.2lf</text>\n",
            x, 20.0, get_property_cep(property), get_property_id(property),
            get_property_side(property), get_property_number(property), get_property_compl(property), get_property_ar(property),
            get_property_v(property));
}
