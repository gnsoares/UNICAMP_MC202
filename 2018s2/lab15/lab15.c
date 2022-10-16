#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main() {
	int i, j, k, max, n_students, n_groups, *v;
	graph_t *graph;

	/* Leitura e construcao das estruturas usadas */
	scanf("%d %d", &n_students, &n_groups);
	graph = graph_create(n_students);
	/* Insercao das arestas do grafo */
	v = malloc(n_students * sizeof(int));
	if (!v) exit(1);
	for (i = 0; i < n_groups; i++) {
		scanf("%d", &n_students);
		for (j = 0; j < n_students; j++)
			scanf("%d", &v[j]);
		for (j = 0; j < n_students; j++)
			for (k = j; k < n_students; k++)
				graph_edge_insert(graph, v[j], v[k]);
	}

	/* Obtencao das distancias e dos caminhos possiveis juntamente com a impressao */
	for (i = 0; i < graph->n_v; i++) {
		graph_bfs(graph, i, v);
		max = 0;
		for (j = 0; j < graph->n_v; j++) {
			if (v[j] == -1)
				printf("%d ", j);
			if (v[j] > max)
				max = v[j];
		}
		printf("- %d\n", max);
	}

	/* Liberacao do espaco alocado */
	free(v);
	graph_free(graph);

	return 0;
}