#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include "linked_list.h"
#include <stdio.h>

typedef void *AvlTree_t;

typedef void *AvlTreeNode_t;

/*
 * Aloca memória e inicializa as listas da árvore com NULL.
 * PRÉ:
 * PÓS: ponteiro void* para a árvore vazia criada.
*/
AvlTree_t create_tree();

/*
 * Armazena a info na árvore passada, atribui os valos para a struct TreeNode e balanceia
 * PRÉ: ponteiro void* para a árvore, void* para a info, double com x, double com y e double com a largura.
 * PÓS: 1 para sucesso e 0 para falha.
 */
int insert_tree(AvlTree_t tree, Info_t info, double key, double width);


/*
 * Recebe uma árvore e uma chave, acha o nó com aquela chave e deleta da árvore passada.
 * Pré: ponteiro void* para a árvore, um double com a chave.
 * Pós: 1 para sucesso e 0 para falha.
*/
int remove_tree(AvlTree_t tree, double key);

/*
 * Recebe uma árvore e desaloca toda memória alocada nela.
 * Pré: ponteiro void* para a árvore.
 * Pós: 1 para sucesso e 0 para falha.
*/
int delete_tree(AvlTree_t _tree);

/*
 * Busca o node da árvore com a chave passada, e retorna a lista armazenada nesse node.
 * Pré: ponteiro void* para a árvore, double com a chave.
 * Pós: Lista armazenada no node com a chave passada.
*/
List_t search_tree(AvlTree_t tree, double key);

/*
 * Remove o node da árvore com o ponto passado.
 * Pré: ponteiro void* para a árvore, e um vetor do tipo double com o ponto para remoção.
 * Pós:
*/
void remove_tree_fp(AvlTree_t _avlTree, const double *point);

/*
 * Imprime o conteúdo de um node da árvore passada em um arquivo passado.
 * Pré: ponteiro void* para a árvore, um ponteiro para um arquivo, e um ponteiro para a
 * função responsável pela impressão
 * Pós:
 */
void print_tree_node(AvlTreeNode_t node_, FILE *svgFile, void(*print)(void*, FILE*));

/*
 * Imprime a árvore no arquivo.dot.
 * Pré: ponteiro void* para a árvore e ponteiro para o arquivo.dot.
 * Pós:
 */
void print_dmpt(AvlTreeNode_t _node, FILE *dmptFILE);

/*
 * Getters: Retorna o atributo do título da função.
 * Pré: Objeto.
 * Pós: Atributo especificado.
 */
AvlTreeNode_t get_tree_root(AvlTree_t tree_);
AvlTree_t get_left(AvlTree_t node_);
AvlTree_t get_right(AvlTree_t node_);
Info_t get_node_list(AvlTreeNode_t node_);
List_t get_tree_node_list_info(AvlTreeNode_t _avlTree, const double *point, double*(*get_point)(void*));
List_t get_inside(AvlTree_t _tree, double x, double y, double w, double h);

#endif //AVL_TREE_H_
