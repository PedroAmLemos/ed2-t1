#include "avl_tree.h"
#include "block.h"
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode {

    List_t list;
    int height;
    struct TreeNode* left;
    struct TreeNode* right;
    double key;
    double lesserX;
    double biggerX;

}TreeNode;

typedef struct Tree{

    TreeNode* root;
    int size;

}Tree;

// Cria e retorna uma árvore
AvlTree_t create_tree(){
    Tree* new = (Tree* ) malloc(sizeof(Tree));

    new->root = NULL;
    new->size = 0;

    return new;
}

// Encerra recursivamente nó por nó da árvore
void delete_tree_nodes(TreeNode* root){

    if(root == NULL){
        return;
    }

    delete_tree_nodes(root->left);
    delete_tree_nodes(root->right);

    remove_list(root->list, 0);
    free(root);
}

// Encerra toda a árvore
int delete_tree(AvlTree_t _tree){
    Tree* treeAux = (Tree* ) _tree;

    if(treeAux == NULL){
        return 0;
    }

    delete_tree_nodes(treeAux->root);

    free(treeAux);

    return 1;
}

// Retorna a altura do nó, caso o nó não exista retorna -1
int get_node_height(TreeNode* node){
    if(node == NULL){
        return -1;
    }else{
        return node->height;
    }
}

// Retorna o fator de balanceamento;
int get_node_factor(TreeNode* node){
    return (int) labs(get_node_height(node->left) - get_node_height(node->right));
}

// Retorna o maior valor dentre 2 inteiros
int biggest(int x, int y){
    if(x > y){
        return x;
    }else{
        return y;
    }
}

// Rotaciona a arvore tipo esquerda esquerda
void rotate_l_l(TreeNode** root){
    TreeNode* node;
    node = (*root)->left;

    (*root)->left = node->right;

    node->right = (*root);

    (*root)->height = biggest(get_node_height((*root)->left), get_node_height((*root)->right)) + 1;

    node->height = biggest(get_node_height((*root)->left), (*root)->height) + 1;

    *root = node;
}

// Rotaciona a arvore tipo direita direita
void rotate_r_r(TreeNode** root){
    TreeNode* node;
    node = (*root)->right;

    (*root)->right = node->left;

    node->left = (*root);

    (*root)->height = biggest(get_node_height((*root)->left), get_node_height((*root)->right)) + 1;

    node->height = biggest(get_node_height((*root)->right), (*root)->height) + 1;

    *root = node;
}

// Rotaciona a arvore tipo Esquerda Direita
void rotate_l_r(TreeNode** root){
    rotate_r_r(&(*root)->left);
    rotate_l_l(root);
}

// Rotaciona a arvore tipo Direita Esquerda
void rotate_r_l(TreeNode** root){
    rotate_l_l(&(*root)->right);
    rotate_r_r(root);
}

// Função de inserção recursiva
int insert_tree_util(TreeNode** root, Info_t info, double key){
    int res;
    // Nó folha ou primeiro nó
    if(*root == NULL){
        TreeNode* new = (TreeNode* ) malloc(sizeof(TreeNode));
        if(new == NULL){
            return 0;
        }

        new->list = create_list();
        insert_list(new->list, info);
        new->left = NULL;
        new->right = NULL;
        new->height = 0;
        new->key = key;
        new->biggerX = key;
        new->lesserX = key;
        *root = new;

        return 1;
    }

    TreeNode* this = *root;


    // Enquanto for passando pelos nós atualiza o maior e menor :)
    if(this->biggerX < key){
        this->biggerX = key;
    }
    if(this->lesserX > key){
        this->lesserX = key;
    }

    // Adiciona a esquerda e se precisar rotaciona a arvore
    if(key < this->key){
        if((res= insert_tree_util(&this->left, info, key)) == 1){
            if(get_node_factor(this) >= 2){
                if(key < this->left->key){
                    rotate_l_l(root);
                }else{
                    rotate_l_r(root);
                }
            }
        }
    }else{
        // Adiciona a direita e se precisar rotaciona a arvore
        if(key > this->key){
            if((res = insert_tree_util(&this->right, info, key)) == 1){
                if(get_node_factor(this) >= 2){
                    if(key > this->right->key){
                        rotate_r_r(root);
                    }else{
                        rotate_r_l(root);
                    }
                }
            }
        }else{
            insert_list(this->list, info);
            return 0;
        }
    }

    this->height = biggest(get_node_height(this->left), get_node_height(this->right)) + 1;

    return res;
}

// Chama a função recursiva de inserir
int insert_tree(AvlTree_t tree, Info_t info, double key){
    Tree* treeAux = (Tree* ) tree;
    int aux = insert_tree_util(&treeAux->root, info, key);

    if(aux == 1){
        treeAux->size++;
    }

    return aux;

}

// Busca o menor nó
TreeNode* get_smallest(TreeNode* this){
    if(this == NULL)
        return NULL;
    TreeNode* node1 = this;
    TreeNode* node2 = this->left;

    while(node2 != NULL){
        node1 = node2;
        node2 = node2->left;
    }

    return node1;
}

// Busca o maior nó
TreeNode* get_biggest(TreeNode* this){
    if(this == NULL)
        return NULL;
    TreeNode* node1 = this;
    TreeNode* node2 = this->right;

    while(node2 != NULL){
        node1 = node2;
        node2 = node2->right;
    }

    return node1;
}

// Recursivamente busca com a key a lista com os valores
List_t search_tree_util(TreeNode* root, double key){
    if(root == NULL){
        return  NULL;
    }

    if(root->key == key){
        return root->list;
    }

    List_t aux = NULL;

    if(key > root->key){
        aux = search_tree_util(root->right, key);
    }else{
        aux = search_tree_util(root->left, key);
    }

    return aux;
}

// Chama a função que retorna a lista
List_t search_tree(AvlTree_t tree, double key){
    Tree* treeAux = (Tree* ) tree;

    return search_tree_util(treeAux->root, key);
}

AvlTreeNode_t get_left(AvlTreeNode_t node_){
    TreeNode* node = (TreeNode * ) node_;
    return node->left;
}

AvlTreeNode_t get_right(AvlTreeNode_t node_){
    TreeNode* node = (TreeNode * ) node_;
    return node->right;
}

Info_t get_node_list(AvlTreeNode_t node_){
    TreeNode* node = (TreeNode * ) node_;
    return node->list;
}

AvlTreeNode_t get_tree_root(AvlTree_t tree_){
    Tree * tree = (Tree*) tree_;
    return tree->root;
}

void print_tree_node(AvlTreeNode_t node_, FILE *svgFile, void(*print)(void*, FILE*)){
    TreeNode* node = (TreeNode *) node_;
    for(Node_t list_node = get_list_first(node->list); list_node != NULL; list_node = get_list_next(list_node)){
        print(get_list_info(list_node), svgFile);
    }
}

Block_t get_tree_node_list_info(AvlTreeNode_t _avlTree, const double *point, double*(*get_point)(void*)){
    double x = point[0];
    double y = point[1];
    double *nodeListInfoPoint;
    List_t nodeList = search_tree(_avlTree, x);
    for(Node_t node = get_list_first(nodeList); node != NULL; node = get_list_next(node)) {
         nodeListInfoPoint = get_point(get_list_info(node));
         if(x == nodeListInfoPoint[0] && y == nodeListInfoPoint[1]){
             return get_list_info(node);
         }
   }
    return NULL;
}

List_t get_tree_list(AvlTreeNode_t _avlTree){
    TreeNode* node = (TreeNode * ) _avlTree;
    return node->list;
}

int remove_tree_util(TreeNode *avlNode, double x, double y){
    int res = 0;
    if(avlNode == NULL ){
        return 0;
    }
    if(x > avlNode->biggerX || x < avlNode->lesserX){
        return 0;
    }

    // if so, continues to left, balancing if needed
    if(x < avlNode->key){
        res = remove_tree_util(avlNode->left, x, y);
        if(res){
            if(get_node_factor(avlNode) >= 2) {
                if(get_node_height(avlNode->right->left) <= get_node_height(avlNode->right->right)){
                    rotate_r_r(&avlNode);
                }else{
                    rotate_l_r(&avlNode);
                }
            }
        }
    }

    // does the same for the right
    if(x > avlNode->key){
        res = remove_tree_util(avlNode->right, x, y);
        if(res){
            if(get_node_factor(avlNode) >= 2){
                if(get_node_height(avlNode->left->right) <= get_node_height(avlNode->left->left)){
                    rotate_l_l(&avlNode);
                }else{
                    rotate_l_r(&avlNode);
                }
            }
        }
    }

    // achou
    if(x == avlNode->key){
        List_t list = get_tree_list(avlNode);
        Block_t block = NULL;
        double blockPoint[2];
        for(Node_t node = get_list_first(list); node != NULL; node = get_list_next(node)){
            block = get_list_info(node);
            blockPoint[0] = get_block_x(block);
            blockPoint[1] = get_block_y(block);
            if(blockPoint[0] == x && blockPoint[1] == y){
                remove_list_node(list, node, NULL);
                if(get_list_size(list) == 0){
                    remove_list(list, NULL);
                    avlNode->list = NULL;
                }
                break;
            }
        }
        if(avlNode->list == NULL){
            if(avlNode->left == NULL || avlNode->right == NULL){
                TreeNode *old = avlNode;
                if(avlNode->left != NULL){
                    avlNode = avlNode->left;
                }else{
                    avlNode = avlNode->right;
                }
                free(old);
            }else{
                TreeNode *temp = get_smallest(avlNode->right);
                avlNode->list = temp->list;
                remove_tree_util(avlNode->right, avlNode->key, y);
                if(get_node_factor(avlNode) >= 2){
                    if(get_node_height(avlNode->left->right) <= get_node_height(avlNode->left->left)){
                        rotate_l_l(&avlNode);
                    }else{
                        rotate_l_r(&avlNode);
                    }
                }
            }
        }
        return 1;
    }
    TreeNode *big = get_biggest(avlNode->right);
    TreeNode *less= get_smallest(avlNode->left);
    if(big != NULL){
        avlNode->biggerX = big->key;
    }
    if(less != NULL){
        avlNode->lesserX = less->key;
    }
    return res;
}

/*
 * from point
 */
void remove_tree_fp(AvlTree_t _avlTree, const double *point){
    Tree *tree = (Tree*) _avlTree;
    remove_tree_util(tree->root, point[0], point[1]);
}

void print_dmpt(AvlTreeNode_t _node, FILE *dmptFILE){
    TreeNode * node = (TreeNode *) _node;

    if(node == NULL || node->list == NULL){
        return;
    }
    char *edge = " -> ";
    char *NullNode = " [shape=point, style=\"invis\"]";
    char *invisEdge = " [style=\"invis\"]";
    char *ident = "   ";

    char cep1[20];
    char cep2[20];
    int qtdQuadras = get_list_size(node->list);
    int fb = get_node_factor(node);
    double xMin = node->lesserX;
    double xMax = node->biggerX;

    strcpy(cep1, get_block_cep(get_list_info(get_list_first(node->list))));
    if(qtdQuadras >= 2)
        strcpy(cep2, get_block_cep(get_list_info(get_list_next(get_list_first(node->list)))));

    char rtkey[100];
    char rtlabel[500];
    sprintf(rtkey,"%f", node->key);

    if(qtdQuadras == 1)
        sprintf(rtlabel, "%s [label=\"X: %.2lf\nQtd de quadras: %d\nCEP: %s\nAltura: %d FB: %d\nX min: %.2lf\nX max: %.2lf\"]", rtkey, node->key, qtdQuadras, cep1, node->height, fb, xMin, xMax);
    else
        if(qtdQuadras == 2){
            sprintf(rtlabel, "%s [label=\"X: %.2lf\nQtd de quadras: %d\nCEP 1: %s\nCEP 2: %s\nAltura: %d FB: %d\nX min: %.2lf\nX max: %.2lf\"]", rtkey, node->key, qtdQuadras, cep1, cep2, node->height, fb, xMin, xMax);
        }
        else{
            sprintf(rtlabel, "%s [label=\"X: %.2lf\nQtd de quadras: %d\nCEP 1: %s\nCEP 2: %s\n(...)\nAltura: %d FB: %d\nX min: %.2lf\nX max: %.2lf\"]", rtkey, node->key, qtdQuadras, cep1, cep2, node->height, fb, xMin, xMax);
        }
    char lst[550];
    char rst[550];

    char lkey[100];
    char rkey[100];
    char lpreamb[200];
    char rpreamb[200];
    char lpost[100];
    char rpost[100];

    if(node->left != NULL){
        sprintf(lpreamb, "");
        sprintf(lkey, "%f", node->left->key);
        sprintf(lpost, "");
    }
    else {
        /* Nao existe sub-arvore esquerda. Coloca uma
        "folha falsa" invisivel para tentar garantir
        que a sub-arvore direita  seja desenhada um pouco
        para a direita */

        sprintf(lkey, "null");
        sprintf(lpreamb, "%s%s%s;\n", ident, lkey, NullNode);
        sprintf(lpost, "%s", invisEdge);
    }

    if(node->right != NULL){
        sprintf(rpreamb, "");
        sprintf(rkey, "%f", node->right->key);
        sprintf(rpost, "");
    }
    else{
        /* NÃ£o existe sub-arvore direita. Coloca "folha falsa" invisivel" */
        sprintf(rkey, "null");
        sprintf(rpreamb, "%s%s%s;\n", ident, rkey, NullNode);
        sprintf(rpost, "%s", invisEdge);
    }
    sprintf(lst, "%s%s%s%s%s%s ;\n", lpreamb, ident, rtkey, edge, lkey, lpost);
    sprintf(rst, "%s%s%s%s%s%s ;\n", rpreamb, ident, rtkey, edge, rkey, rpost);
    fprintf(dmptFILE, "%s", rtlabel);
    fprintf(dmptFILE, "%s", lst);
    fprintf(dmptFILE, "%s", rst);

    print_dmpt(node->left, dmptFILE);
    print_dmpt(node->right, dmptFILE);
}

void get_inside_util(AvlTreeNode_t _node, List_t storage, double x, double y, double w, double h){
    if(_node == NULL){
        return;
    }

    TreeNode *node = (TreeNode*) _node;

    get_inside_util(node->left, storage, x, y, w, h);
    get_inside_util(node->right, storage, x, y, w, h);
    List_t list = node->list;
    Block_t block = NULL;


    for(Node_t listNode = get_list_first(list); listNode != NULL; listNode = get_list_next(listNode)) {
        block = get_list_info(listNode);
        if(is_block_inside_rect(block, x, y, w, h)) {
            insert_list(storage, get_block_cep(block));
        }
    }
}

List_t get_inside(AvlTree_t _tree, double x, double y, double w, double h){
    List_t inside = create_list();
    Tree *tree = (Tree *) _tree;
    get_inside_util(tree->root, inside, x, y, w, h);
    return inside;
}
