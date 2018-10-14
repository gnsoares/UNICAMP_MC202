#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NodeT * create_tree(char *c, NodeT *left, NodeT *right) {
	NodeT *root = malloc(sizeof(NodeT));
	if (!root)
		exit(1);
	strcpy(root->key, c);
	root->left = left;
	root->right = right;
	return root;
}

int inner_operator_pos(char **expression, int beg, int end) {
	int i, is_beg, is_end;

	is_beg = expression[beg+2][0] == '+' || expression[beg+2][0] == '-'
		  || expression[beg+2][0] == '*' || expression[beg+2][0] == '/';
	is_end = expression[end-2][0] == '+' || expression[end-2][0] == '-'
		  || expression[end-2][0] == '*' || expression[end-2][0] == '/';

	if (is_beg)
		return beg + 2;
	else if (is_end)
		return end - 2;
	else
		for (i = beg+1; i < end; i++)
			if ((expression[i-1][0] == ')') && (expression[i+1][0] == '('))
				return i;
	return 0;
}

NodeT * expression_tree(char **expression, int beg, int end) {
	int pos;
	NodeT *tree, *left, *right;

	if (expression[beg][0] == '(') {
		pos = inner_operator_pos(expression, beg, end);
		left = expression_tree(expression, beg+1, pos-1);
		right = expression_tree(expression, pos+1, end-1);
		tree = create_tree(expression[pos], left, right);
	} else if (beg == end) {
		tree = create_tree(expression[beg], NULL, NULL);
	} else {
		return NULL;
	}

	return tree;
}

int node_is_number(NodeT *root) {
	if (root)
		return (root->key[0] >= '0' && root->key[0] <= '9')
			|| (root->key[0] == '-' && root->key[1] >= '0' && root->key[1] <= '9');
	return 0;
}

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
		root->left = simplify(root->left);
		root->right = simplify(root->right);
		if (node_is_number(root->left) && node_is_number(root->right)) {
			if (root->key[0] == '+')
				result = atoi(root->left->key) + atoi(root->right->key);
			else if (root->key[0] == '-')
				result = atoi(root->left->key) - atoi(root->right->key);
			else if (root->key[0] == '*')
				result = atoi(root->left->key) * atoi(root->right->key);
			else if (root->key[0] == '/')
				result = atoi(root->left->key) / atoi(root->right->key);
			sprintf(root->key, "%d", result);
			free_tree(root->left);
			free_tree(root->right);
			root->left = NULL;
			root->right = NULL;
		}
	}
	return root;
}

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