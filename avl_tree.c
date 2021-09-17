#include "avl_tree.h"
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

    char type[20];
    TreeNode* root;
    int size;

}Tree;

// Cria e retorna uma árvore
AvlTree_t create_tree(char type[20]){
    Tree* new = (Tree* ) malloc(sizeof(Tree));

    strcpy(new->type, type);
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
    TreeNode* node1 = this;
    TreeNode* node2 = this->right;

    while(node2 != NULL){
        node1 = node2;
        node2 = node2->right;
    }

    return node1;
}

// Função de remoção recursiva
int remove_tree_util(TreeNode** root, double key){
    int res = 0;
    if(*root == NULL){
        return 0;
    }

    // Se for menor que o nó atual vai para a esquerda e balanceia se precisar
    if(key < (*root)->key){
        if((res = remove_tree_util(&(*root)->left, key)) == 1){
            if(get_node_factor((*root)) >= 2){
                if(get_node_height((*root)->right->left) <= get_node_height((*root)->right->right)){
                    rotate_r_r(root);
                }else{
                    rotate_r_l(root);
                }
            }
        }
    }

    // Se for maior que o nó atual vai para o nó da direita e balanceia se precisar
    if(key > (*root)->key){
        if((res = remove_tree_util(&(*root)->right, key)) == 1){
            if(get_node_factor(*root) >= 2){
                if(get_node_height((*root)->left->right) <= get_node_height((*root)->left->left)){
                    rotate_l_l(root);
                }else{
                    rotate_l_r(root);
                }
            }
        }
    }

    // Se for igual ao valor do nó o remove e balanceia se precisar
    if(key == (*root)->key){
        if((*root)->left == NULL || (*root)->right == NULL){
            TreeNode* oldNode = *root;
            if((*root)->left != NULL){
                (*root) = (*root)->left;
            }else{
                (*root) = (*root)->right;
            }

            remove_list(oldNode->list, 0);
            free(oldNode);
        }else{
            TreeNode* temp = get_smallest((*root)->right);
            (*root)->list = temp->list;
            remove_tree_util(&(*root)->right, (*root)->key);
            if(get_node_factor((*root)) >= 2){
                if(get_node_height((*root)->left->right) <= get_node_height((*root)->left->left)){
                    rotate_l_l(root);
                }else{
                    rotate_l_r(root);
                }
            }
        }
        return 1;
    }

    // Caso remova o nó troca os maiores e menores
    TreeNode* big = get_biggest((*root)->right);
    TreeNode* small = get_smallest((*root)->left);
    (*root)->biggerX = big->key;
    (*root)->lesserX = small->key;


    return res;
}

// Chama a função recursiva de remover
int remove_tree(AvlTree_t tree, double key){
    Tree* treeAux = (Tree* ) tree;
    int aux = remove_tree_util(&treeAux->root, key);

    if(aux == 1){
        treeAux->size--;
    }

    return aux;
}

// Recursivamente busca com a key a lista com os valores
List_t search_tree_util(TreeNode* root, double key){
    if(root == NULL){
        return  NULL;
    }

    if(root->key == key){
        return root->list;
    }

    if(key > root->biggerX || key < root->lesserX){
        return NULL;
    }

    List_t aux;

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
    TreeNode* node = (TreeNode * ) node_;
    for(Node_t list_node = get_first(node->list); list_node != NULL; list_node = get_next(list_node)){
        print(get_info(list_node), svgFile);
    }
}
