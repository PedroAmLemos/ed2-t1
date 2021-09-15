#include "svg.h"

void open_svg(FILE *svgFile){
    fprintf(svgFile, "<!-- Pedro Antonio Messias Lemos -->\n");
    fprintf(svgFile, "<svg version=\"1.1\" baseProfile=\"full\" width=\"10000\" height=\"10000\" xmlns=\"http://www.w3.org/2000/svg\">\n");
}

void close_svg(FILE *svgFile) {
    fprintf(svgFile, "</svg>");
}

void print_tree(AvlTreeNode_t node_, FILE *svgFile, void(*print)(void*, FILE*)){
    if(node_ == NULL) {
        return;
    }
    print_tree_node(node_, svgFile, print);
    print_tree(get_left(node_), svgFile, print);
    print_tree(get_right(node_), svgFile, print);
}
