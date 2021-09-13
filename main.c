#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reading.h"

int main(int argc, char *argv[]) {
    int i = 1;
    char *entryPath = NULL; // bed diretorio de entrada - opcional
    char *outPath = NULL;   // bsd diretorio de saida - obrigatorio
    char *geo = NULL; // arquivo de descricao, sob o diretorio bed - obrigatorio
    char *qry = NULL; // arquivo de consultas, sob o diretorio bed - obrigatorio
    char *pm = NULL;
    while (i < argc) {
        if (strcmp("-e", argv[i]) == 0) {
            i++;
            if (argv[i] == NULL) {
                printf("Erro - Sem parametros em -e\n");
                exit(1);
            }
            entryPath = malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(entryPath, argv[i]);
        } else if (strcmp("-f", argv[i]) == 0) {
            i++;
            if (argv[i] == NULL) {
                printf("Erro - Sem Parametros em -f\n");
                exit(1);
            }
            geo = malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(geo, argv[i]);
        } else if (strcmp("-o", argv[i]) == 0) {
            i++;
            if (argv[i] == NULL) {
                printf("Erro - Sem Parameters em -o\n");
                exit(1);
            }
            outPath = malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(outPath, argv[i]);
        } else if (strcmp("-q", argv[i]) == 0) {
            i++;
            if (argv[i] == NULL) {
                printf("Erro - Sem parâmetros em -q\n");
                exit(1);
            }
            qry = malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(qry, argv[i]);
        } else if (strcmp("-pm", argv[i]) == 0) {
            i++;
            if (argv[i] == NULL) {
                printf("Erro - Sem parâmetros em -pm\n");
                exit(1);
            }
            pm = malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(pm, argv[i]);
        }
        i++;
    }
    read(entryPath, geo, qry, outPath, pm);
    free(geo);
    free(outPath);
    if (entryPath)
        free(entryPath);
    if (qry)
        free(qry);
    if (pm)
        free(pm);
    return 0;
}
