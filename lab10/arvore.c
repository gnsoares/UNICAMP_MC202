#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NodeT * create_tree(char *c, NodeT *left, NodeT *right) {
	NodeT *root = malloc(sizeof(NodeT));
	if (!root) exit(1);
	strcpy(root->key, c);
	root->left = left;
	root->right = right;
	return root;
}

/* Funcao que acha e devolve a posicao do operador
 * de uma expressao matematica */
int operator_pos(char **expression, int beg, int end) {
	int i, is_beg, is_end;

	is_beg = expression[beg+2][0] == '+' || expression[beg+2][0] == '-'
		  || expression[beg+2][0] == '*' || expression[beg+2][0] == '/';
	is_end = expression[end-2][0] == '+' || expression[end-2][0] == '-'
		  || expression[end-2][0] == '*' || expression[end-2][0] == '/';

	/* Caso o primeiro operando seja um numero */
	if (is_beg)
		return beg + 2;
	/* Caso o segundo operando seja um numero */
	else if (is_end)
		return end - 2;
	/* Caso ambos operandos sejam expressoes */
	else
		for (i = beg+1; i < end; i++)
			if ((expression[i-1][0] == ')') && (expression[i+1][0] == '('))
				return i;

	return 0;
}

NodeT * expression_tree(char **expression, int beg, int end) {
	int pos;
	NodeT *tree, *left, *right;

	/* Caso seja uma expressao com mais de um termo */
	if (expression[beg][0] == '(') {
		pos = operator_pos(expression, beg, end);
		left = expression_tree(expression, beg+1, pos-1);
		right = expression_tree(expression, pos+1, end-1);
		tree = create_tree(expression[pos], left, right);
	/* Caso a expressao possua apenas um termo */
	} else if (beg == end) {
		tree = create_tree(expression[beg], NULL, NULL);
	/* Caso nao seja uma expressao valida */
	} else {
		return NULL;
	}

	return tree;
}

/* Funcao que verifica se um no contem um numero */
int node_is_number(NodeT *root) {
	if (root)
		return (root->key[0] >= '0' && root->key[0] <= '9')
			|| (root->key[0] == '-' && root->key[1] >= '0' && root->key[1] <= '9');
	return 0;
}

/* Funcao que verifica se um no contem um operador */
int node_is_operator(NodeT *root) {
	if (root)
		return (root->key[0] == '+' || root->key[0] == '-'
			 || root->key[0] == '*' || root->key[0] == '/')
			 && root->key[1] == '\0';
	return 0;
}

NodeT * simplify(NodeT *root) {
	int result;
	if (root) {
		/* As subarvores devem estar simplificadas */
		root->left = simplify(root->left);
		root->right = simplify(root->right);

		/* Se os dois filhos sao numeros, simplificar */
		if (node_is_number(root->left) && node_is_number(root->right)) {

			/* Definicao da operacao */
			if (root->key[0] == '+')
				result = atoi(root->left->key) + atoi(root->right->key);
			else if (root->key[0] == '-')
				result = atoi(root->left->key) - atoi(root->right->key);
			else if (root->key[0] == '*')
				result = atoi(root->left->key) * atoi(root->right->key);
			else if (root->key[0] == '/')
				result = atoi(root->left->key) / atoi(root->right->key);

			/* Mudanca dos valores e remocao das subarvores */
			sprintf(root->key, "%d", result);
			free_tree(root->left);
			free_tree(root->right);
			root->left = NULL;
			root->right = NULL;
		}
	}
	return root;
}

/* Funcao auxiliar para impressao da expressao;
 * Imprime caso no seja operando;
 * Chama a funcao principal caso no seja expressao;
 */
void print_aux(NodeT *root) {
	if (node_is_operator(root))
		print_expression(root);
	else
		printf("%s ", root->key);
}

void print_expression(NodeT *root) {
	printf("( ");
	print_aux(root->left);
	printf("%s ", root->key);
	print_aux(root->right);
	printf(") ");	
}

void free_tree(NodeT *root) {
	if (root) {
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}