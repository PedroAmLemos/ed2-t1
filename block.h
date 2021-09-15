#ifndef BLOCK_H_
#define BLOCK_H_

typedef void *Block_t;

#include <stdio.h>

Block_t create_block(char cep[], double x, double y, double width, double height, char sw[], char stroke[], char fill[]);

void print_block(Block_t block_, FILE *svgFile);

#endif //BLOCK_H_
