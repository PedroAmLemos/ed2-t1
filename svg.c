#include "svg.h"
#include <stdio.h>

void open_svg(FILE *svgFile){
    fprintf(svgFile, "<!-- Pedro Antonio Messias Lemos -->\n");
    fprintf(svgFile, "<svg version=\"1.1\" baseProfile=\"full\" width=\"15000\" height=\"15000\" xmlns=\"http://www.w3.org/2000/svg\">\n");
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

void print_hash_table(HashTable_t hashTable_, FILE *svgFile, void(*print)(void*, FILE*)){
    List_t *list =  get_table(hashTable_);
    for(int i = 0; i < get_table_size(hashTable_); i++) {
        for(Node_t listNode = get_list_first(list[i]); listNode != NULL; listNode = get_list_next(listNode)){
            print(get_item_info(get_list_info(listNode)), svgFile);
        }
    }
}

void print_line(double x1, double y1, double x2, double y2, char stroke[], FILE *svgFile){
    fprintf(svgFile, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" opacity=\"0.6\"/>\n",
            x1, y1, x2, y2, stroke);
}

void print_text(double x, double y, char text[], FILE *svgFile){
   fprintf(svgFile, "\t<text x=\"%.2f\" y=\"%.2f\">%s</text>\n", x, y, text);
}

void print_circle(double cx, double cy, double r, char stroke[], char fill[], char sw[], FILE *svgFile){
    fprintf(svgFile, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", cx, cy, r, stroke, fill, sw);
}

void print_rectangle_dashed(double x, double y, double w, double h, FILE *svgFile){
    fprintf(svgFile,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" opacity=\"0.8\" fill=\"none\" stroke=\"black\" stroke-width=\"3px\" stroke-dasharray=\"20\"/>\n", x, y, w, h);
}