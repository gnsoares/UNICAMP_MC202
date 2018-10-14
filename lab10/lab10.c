#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

#define MAX_LEN_EXP 2e5

int get_expression(char **v_str) {
	int i;
	for (i = 0; scanf("%s", v_str[i]) > 0; i++);
	return i;
}

int	main() {

	int i, len_exp = 0;
	char **expression;
	NodeT *tree;

	expression = malloc(MAX_LEN_EXP * sizeof(char *));
	if (!expression)
		exit(1);
	for (i = 0; i < MAX_LEN_EXP; i++) {
		expression[i] = malloc(MAX_LEN_OPE * sizeof(char));
		if (!expression[i])
			exit(1);		
	}

	len_exp = get_expression(expression);

	tree = expression_tree(expression, 0, len_exp - 1);
	tree = simplify(tree);
	print_expression(tree);
	printf("\n");

	free_tree(tree);

	for (i = 0; i < MAX_LEN_EXP; i++) {
		free(expression[i]);
	}
	free(expression);

	return 0;
}