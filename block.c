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

char *get_block_cep(Block_t block_) {
    Block *block = (Block*) block_;
    return block->cep;
}

double get_block_x(Block_t block_) {
    Block *block = (Block*) block_;
    return block->point[0];
}

double get_block_y(Block_t block_) {
    Block *block = (Block*) block_;
    return block->point[1];
}

double *get_block_point(Block_t _block){
    Block *block = (Block*) _block;
    return block->point;
}

void print_block(Block_t block_, FILE *svgFile) {
    Block *block = (Block*) block_;
    fprintf(svgFile,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" opacity=\"0.5\" stroke=\"%s\" stroke-width=\"%s\"/>\n",
            block->point[0], block->point[1], block->width, block->height, block->fill, block->stroke, block->sw);
}
void remove_block(HashTable_t _hashTable, AvlTree_t _tree, void(*remove)(void*, void*, void*, int), void *parameter){
    remove(_hashTable, _tree, parameter, 1);
}
