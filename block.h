#ifndef BLOCK_H_
#define BLOCK_H_
#include "avl_tree.h"
#include "block.h"
#include "hash_table.h"
#include <stdio.h>
typedef void *Block_t;

Block_t create_block(char cep[], double x, double y, double width, double height, char sw[], char stroke[], char fill[]);

void print_block(Block_t block_, FILE *svgFile);

char *get_block_cep(Block_t block_);

double get_block_x(Block_t block_);

double get_block_y(Block_t block_);

double *get_block_point(Block_t _block);

void remove_block(HashTable_t hashTable, AvlTree_t _tree, void(*remover)(void*, void*, void*, int), void *parameter);

double get_block_width(Block_t _block);

double get_block_height(Block_t _block);

char *get_block_sw(Block_t _block);

char *get_block_stroke(Block_t _block);

char *get_block_fill(Block_t _block);

void print_block_txt(Block_t _block, FILE *qryTXTFile);

int is_block_inside_rect(Block_t _block, double x, double y, double w, double h);


/*
 * TODO Void remove block
 * vai receber a árvore e a hash table de blocks, e uma function pointer pra remover_tree ou remove_hash_table, e um
 * parâmetro (void*) que pode ser o cep ou a key da quadra que quer remover, se for um cep, vai chamar a função de
 * remover na hash table (vai achar na hash table o node com o cep, vai chamar a função de remover da árvore com o
 * point retirado do node, com flag 0), e depois vai desalocar e remover o node da hash table, se for um ponto vai
 * chamar a função de remover na árvore (vai achar na árvore, vai no node com o ponto, remover o node da lista
 * (node -> anterior = node -> próximo e node -> próximo -> anterior = node -> anterior) e chamar a função de remover
 * da hash table com uma flag de nao remover o tree node;
 */

#endif //BLOCK_H_
