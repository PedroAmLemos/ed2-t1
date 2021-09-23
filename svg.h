#ifndef SVG_H_
#define SVG_H_
#include <stdio.h>
#include "avl_tree.h"
#include "hash_table.h"

void open_svg(FILE *svgFile);

void close_svg(FILE *svgFile);

void print_tree(AvlTree_t tree_, FILE *svgFile, void(*print)(void*, FILE*));

void print_hash_table(HashTable_t hashTable_, FILE *svgFile, void(*print)(void*, FILE*));

void print_line(double x1, double y1, double x2, double y2, char stroke[], FILE *svgFile);

void print_text(double x, double y, char text[], FILE *svgFile);

void print_circle(double cx, double cy, double r, char stroke[], char fill[], char sw[], FILE *svgFile);

#endif //SVG_H_
