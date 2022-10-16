#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "fila_de_prioridade.h"


int main(void) {

	int n_arrays, tmp, sum = 0;
	int ** elements; // matrix of elements
	int * n_elements; // array of number of elements of each array
	int * indexes; // array of current index of each array
	heap_t h;

	// input read and structure construction
	scanf("%d", &n_arrays);
	h = heap_create(n_arrays);
	assert(n_elements = malloc(n_arrays * sizeof(int)));
	assert(elements = malloc(n_arrays * sizeof(int *)));
	assert(indexes = malloc(n_arrays * sizeof(int)));
	for (int i = 0; i < n_arrays; indexes[i++] = 0);
	for (int i = 0; i < n_arrays; i++) {
		scanf("%d", &n_elements[i]);
		assert(elements[i] = malloc(n_elements[i] * sizeof(int)));
		sum += n_elements[i];
	}

	for (int i = 0; i < n_arrays; i++)
		for (int j = 0; j < n_elements[i]; j++)
			scanf("%d", &elements[i][j]);
	
	// including each element at index 0
	for (int i = 0; i < n_arrays; heap_push(h, elements[i][0], i), i++);

	// print result
	for (int i = 0; i < sum - 1; i++) {
		printf("%d ", heap_pop(h, &tmp));
		indexes[tmp]++;
		if (indexes[tmp] < n_elements[tmp])
			heap_push(h, elements[tmp][indexes[tmp]], tmp);
	}
	printf("%d\n", heap_pop(h, &tmp));

	// memory freeing
	heap_free(h);
	free(n_elements);

	return 0;
}
