#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include "linked_list.h"
#include <stdio.h>

typedef void *AvlTree_t;

typedef void *AvlTreeNode_t;

/*
Função: Cria uma estrutura de Árvore AVL e armazena o tipo;
Pré: char[20] com o que vai ser armazenado. Ex: "Retangulo";
Pós: Retorna um void* com o endereço da árvore.
*/
AvlTree_t create_tree();

/*
Função: Dado uma árvore, um ponteiro para Info e uma chave, insere na árvore e balanceia-a.
Pré: void* para a árvore, void* para a info, double com valor.
Pós: Retorna 1 caso bem sucedido ou 0 para key de valor igual.
*/
int insert_tree(AvlTree_t tree, Info_t info, double key);

/*
Função: Dado uma árvore e uma chave, acha o nó correspondete e o remove da árvore.
Pré: void* para a árvore, um double com valor.
Pós: Retorna 1 caso bem sucedido ou 0 para falha.
*/
int remove_tree(AvlTree_t tree, double key);

/*
Função: Dada uma árvore desaloca todos os nós e a própria árvore.
Pré: void* para a árvore.
Pós: Retorna 1 caso bem sucedido ou 0 para falha.
*/
int delete_tree(AvlTree_t _tree);

/*
Função: Busca e recupera a lista com todos os dados correspondete a key
Pré: void* para a árvore, double com valor
Pós:
*/
List_t search_tree(AvlTree_t tree, double key);

/*
Remove o node da árvore com o ponto passado
*/
void remove_tree_fp(AvlTree_t _avlTree, const double *point);

void print_tree_node(AvlTreeNode_t node_, FILE *svgFile, void(*print)(void*, FILE*));

AvlTreeNode_t get_tree_root(AvlTree_t tree_);

AvlTree_t get_left(AvlTree_t node_);

AvlTree_t get_right(AvlTree_t node_);

Info_t get_node_list(AvlTreeNode_t node_);

List_t get_tree_node_list_info(AvlTreeNode_t _avlTree, const double *point, double*(*get_point)(void*));

void print_dmpt(AvlTreeNode_t _node, FILE *dmptFILE);

List_t get_inside(AvlTree_t _tree, double x, double y, double w, double h);

#endif //AVL_TREE_H_
