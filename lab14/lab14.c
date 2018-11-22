#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>

/* Verificacao se um grupo de 3 pessoas esta entediado */
int is_bored(int age1, int age2, int age3) {
	double average = ( (double) (age1 + age2 + age3) ) / 3;
	if (average > 2*age1 || average > 2*age2 || average > 2*age3)
		return 1;
	return 0;
}

/* Verificacao se um elemento esta em um vetor */
int in(int *v, int max, int x) {
	int i;
	for (i = 0; i < max; i++)
		if (v[i] == x)
			return 1;
	return 0;
}

int main() {
	
	int i, u, v, n_people, n_links;
	int *ages, *bored_people, k = 0;
	list_node_t *curr1, *curr2;
	graph_t *graph;

	scanf("%d %d", &n_people, &n_links);
	ages = malloc(n_people * sizeof(int));
	bored_people = malloc(n_people * sizeof(int));
	if (!ages || !bored_people) exit(1);
	for (i = 0; i < n_people; i++)
		scanf("%d", &ages[i]);
	graph = graph_create(n_people);

	for (i = 0; i < n_links; i++) {
		scanf("%d %d", &u, &v);
		graph_edge_insert(graph, u, v);
	}
	
	for (i = 0; i < n_people; i++) {
		for (curr1 = graph->adjacency[i]; curr1; curr1 = curr1->next) {
			if (in(bored_people, k, i))
				break;
			for (curr2 = curr1->next; curr2; curr2 = curr2->next) {
				if (has_edge(graph, curr1->value, curr2->value))
					if (is_bored(ages[i], ages[curr1->value], ages[curr2->value])) {
						bored_people[k++] = i;
						break;
					}
			}
		}
	}

	for (u = 0; u < k; u++) {
		printf("%d\n", bored_people[u]);
	}

	return 0;
}