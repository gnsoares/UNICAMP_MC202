#include <stdio.h>
#include "arvore.h"


int main(void) {

	rbbst_t tree = rbbst_init();
	int n_processes, n_processors, tmp;
	
	// input reading and tree construction
	scanf("%d", &n_processes);
	for (int i = 0; i < n_processes; i++) {
		scanf("%d", &tmp);
		rbbst_insert(tree, tmp);
	}
	scanf("%d", &n_processors);

	for (int i = 0; i < n_processors; i++) {
		// print the process with biggest wait time,
		// remove it from tree
		tmp = rbbst_max(tree)->value;
		printf("%d\n", tmp);
		rbbst_remove(tree, tmp);
	}

	// free allocated memory
	rbbst_free(tree);

	return 0;
}
