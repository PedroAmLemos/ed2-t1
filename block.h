#ifndef BLOCK_H_
#define BLOCK_H_
#include "avl_tree.h"
#include "block.h"
#include "hash_table.h"
#include <stdio.h>
typedef void *Block_t;

Block_t create_block(char cep[], double x, double y, double width, double height, char sw[], char stroke[], char fill[]);

void print_block(Block_t block_, FILE *svgFile);

void remove_block(HashTable_t hashTable, AvlTree_t _tree, void(*remover)(void*, void*, void*, int), void *parameter);

void print_block_txt(Block_t _block, FILE *qryTXTFile);

int is_block_inside_rect(Block_t _block, double x, double y, double w, double h);

char *get_block_cep(Block_t block_);

double get_block_x(Block_t block_);

double get_block_y(Block_t block_);

double *get_block_point(Block_t _block);

double get_block_width(Block_t _block);

double get_block_height(Block_t _block);

char *get_block_sw(Block_t _block);

char *get_block_stroke(Block_t _block);

char *get_block_fill(Block_t _block);

#endif //BLOCK_H_
