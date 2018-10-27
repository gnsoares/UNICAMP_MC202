#ifndef TREAP_H
#define TREAP_H

typedef struct treap_node {
	int key, priority;
	struct treap_node *left, *right;
} TreapNode;

/* Funcao que cria uma arvore. Tem como parametros:
 	* String da raiz;
 	* Endereco da subarvore esquerda;
 	* Endereco da subarvore direita;
 */
TreapNode * create_tree(int x, TreapNode *left, TreapNode *right);

TreapNode * join(TreapNode *r1, TreapNode *r2);

/* Funcao que libera o espaco alocado por uma arvore binaria */
void free_tree(TreapNode *root);

#endif