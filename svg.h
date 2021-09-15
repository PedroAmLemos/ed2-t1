#ifndef SVG_H_
#define SVG_H_
#include <stdio.h>
#include "avl_tree.h"

void open_svg(FILE *svgFile);

void close_svg(FILE *svgFile);

void print_tree(AvlTree_t tree_, FILE *svgFile, void(*print)(void*, FILE*));

#endif //SVG_H_
