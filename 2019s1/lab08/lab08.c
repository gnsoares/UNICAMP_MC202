#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main(void) {

	int n_ships, n_attacks, input;
	bst_node_t * squad; // bst that keeps the shipd
	bst_node_t ** nodes; // array that keeps the nodes used to build bst

	// input reading and structure assembling
	scanf("%d", &n_ships);
	nodes = malloc(n_ships * sizeof(bst_node_t *));
	assert(nodes);
	for (int i = 0; i < n_ships; i++) {
		scanf("%d", &input);
		nodes[i] = bst_create(input, NULL, NULL);
	}

	// with the array of sorted nodes, build the bst
	squad = bst_build(nodes, 0, n_ships-1);

	// keep record of ship attacks
	scanf("%d", &n_attacks);
	for (int i = 0; i < n_attacks; i++) {
		scanf("%d", &input);
		bst_find(squad, input)->attacks++;
	}

	// print results and free space
	bst_preorder(squad);
	free(nodes);
	bst_free(squad);

	return 0;
}