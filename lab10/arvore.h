#ifndef ARVORE_H
#define ARVORE_H

#define MAX_LEN_OPE 10

typedef struct nodeT {
	char key[MAX_LEN_OPE];
	struct nodeT *left, *right;
} NodeT;

NodeT * create_tree(char *c, NodeT *left, NodeT *right);
NodeT * expression_tree(char **expression, int beg, int end);
NodeT * simplify(NodeT *root);
void print_expression(NodeT *root);
void free_tree(NodeT *root);

#endif