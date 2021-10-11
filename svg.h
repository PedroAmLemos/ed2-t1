#ifndef SVG_H_
#define SVG_H_
#include <stdio.h>
#include "avl_tree.h"
#include "hash_table.h"

/*
 * Função que abre a tag svg em um arquivo passado.
 * Pré: ponteiro para o arquivo svg.
 * Pós:
 */
void open_svg(FILE *svgFile);

/*
 * Função que fecha a tag svg em um arquivo passado.
 * Pré: ponteiro para o arquivo svg.
 * Pós:
 */
void close_svg(FILE *svgFile);

/*
 * Função que imprime as informações de uma árvore em um arquivo passado.
 * Pré: ponteiro do tipo void* para a árvore, ponteiro para o arquivo svg e uma função que realizará a impressão.
 * Pós:
 */
void print_tree(AvlTree_t tree_, FILE *svgFile, void(*print)(void*, FILE*));

/*
 * Função que imprime as informações de uma hash table em um arquivo passado.
 * Pré: ponteiro do tipo void* para a tabela, ponteiro para o arquivo svg e uma função que realizará a impressão.
 * Pós:
 */
void print_hash_table(HashTable_t hashTable_, FILE *svgFile, void(*print)(void*, FILE*));

/*
 * Imprime uma linha em um arquivo svg.
 * Pré: os valores para impressão da linha e o arquivo svg.
 * Pós:
 */
void print_line(double x1, double y1, double x2, double y2, char stroke[], FILE *svgFile);

/*
 * Imprime um texto em um arquivo svg.
 * Pré: os valores para a impressão do texto e o arquivo svg.
 * Pós:
 */
void print_text(double x, double y, char text[], FILE *svgFile);

/*
 * Imprime um círculo em um arquivo svg.
 * Pré: os valores para a impressão do círculo e o arquivo svg.
 * Pós:
 */
void print_circle(double cx, double cy, double r, char stroke[], char fill[], char sw[], FILE *svgFile);

#endif //SVG_H_
