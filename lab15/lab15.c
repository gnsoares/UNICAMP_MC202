#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/* Verificacao se um elemento esta em um vetor */
int in(int *v, int v_size, int x) {
	int i;
	for (i = 0; i < v_size; i++)
		if (v[i] == x)
			return 1;
	return 0;
}

/* Busca pelo maior elemento de um vetor */
int max(int *v, int v_size) {
	int i, max = v[0];
	for (i = 1; i < v_size; i++)
		if (v[i] > max)
			max = v[i];
	return max;
}

int main() {
	int i, j, k, n_students, n_groups, *v;
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
		for (j = 0; j < graph->n_v; j++)
			if (v[j] == -1)
				printf("%d ", j);
		printf("- %d\n", max(v, graph->n_v));
	}

	/* Liberacao do espaco alocado */
	free(v);
	graph_free(graph);

	return 0;
}