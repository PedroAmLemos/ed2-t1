#include "block.h"
#include <string.h>
#include <stdlib.h>

typedef struct Block{
    char cep[20];
    double point[2];
    double width;
    double height;
    char sw[10];
    char stroke[25];
    char fill[25];
}Block;

Block_t create_block(char cep[], double x, double y, double width, double height, char sw[], char stroke[], char fill[]){
    Block *block = (Block*) malloc(sizeof(Block));
    strcpy(block->cep, cep);
    strcpy(block->sw, sw);
    strcpy(block->stroke, stroke);
    strcpy(block->fill, fill);
    block->width = width;
    block->height = height;
    block->point[0] =x;
    block->point[1] =y;

    return block;
}