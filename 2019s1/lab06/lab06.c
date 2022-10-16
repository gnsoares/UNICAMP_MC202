#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lista.h"


/* prints all the clients in a queue based on the priority
 * this function does not sort the elements of each list
 * @param queue array with each list of clients separate by priority
 * @param n_priorities number of priorities
 */
void print_clients(int_list_t ** queue, int n_priorities) {
	for (int i = n_priorities - 1; i >= 0; i--)
		for (int_node_t * tmp = queue[i]->head; tmp; tmp = tmp->next)
			printf("%d %d\n", tmp->data, i);
}


int main(void) {
	
	// problem size
	int n_priorities, n_clients;
	// arrival order and priority
	int c, p;
	// array that keeps each sorted list of clients
	// each list corresponds to a priority level
	int_list_t ** priorities_arr;

	// input reading and data structuring
	scanf("%d\n%d", &n_priorities, &n_clients);
	priorities_arr = malloc(n_priorities * sizeof(int_list_t *));
	assert(priorities_arr);
	for (int i = 0; i < n_priorities; i++)
		priorities_arr[i] = int_list_create();
	for (int i = 0; i < n_clients; i++) {
		scanf("%d %d", &c, &p);
		int_list_insert_sorted(priorities_arr[p], c);
	}

	// print calling order
	print_clients(priorities_arr, n_priorities);

	// allocated memory freeing
	for (int i = 0; i < n_priorities; i++)
		int_list_free(priorities_arr[i]);
	free(priorities_arr);

	return 0;
}