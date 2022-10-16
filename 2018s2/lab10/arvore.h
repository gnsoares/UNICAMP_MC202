#ifndef ARVORE_H
#define ARVORE_H

/* Interface de uma ARVORE BINARIA DE EXPRESSAO */

/* Numero de caracteres maximo em um operador ou operando */
#define MAX_LEN_OPE 10

/* Estrututa de um no de arvore binaria */
typedef struct nodeT {
	char key[MAX_LEN_OPE];
	struct nodeT *left, *right;
} NodeT;

/* Funcao que cria uma arvore. Tem como parametros:
 	* String da raiz;
 	* Endereco da subarvore esquerda;
 	* Endereco da subarvore direita;
 */
NodeT * create_tree(char *c, NodeT *left, NodeT *right);

/* Funcao que recebe um vetor de strings com a expressao
 * e devolve o endereco de uma arvore binaria que a representa
 */
NodeT * expression_tree(char **expression, int beg, int end);

/* Funcao que simplifica uma arvore binaria com uma expressao */
NodeT * simplify(NodeT *root);

/* Funcao que imprime uma expressao de uma arvore binaria */
void print_expression(NodeT *root);

/* Funcao que libera o espaco alocado por uma arvore binaria */
void free_tree(NodeT *root);

#endif