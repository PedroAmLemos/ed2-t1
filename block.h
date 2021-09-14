#ifndef BLOCK_H_
#define BLOCK_H_

typedef void *Block_t;

Block_t create_block(char cep[], double x, double y, double width, double height, char sw[], char stroke[], char fill[]);

#endif //BLOCK_H_
