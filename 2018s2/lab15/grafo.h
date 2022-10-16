#ifndef GRAFO_H
#define GRAFO_H

/* Interface de um grafo que usa matriz de adjcacencias */

typedef struct graph_s {
	int **adj;
	int n_v;
} graph_t;

/* Criacao do grafo */
graph_t *graph_create(int n_v);
/* Insercao de aresta no grafo */
void graph_edge_insert(graph_t *graph, int u, int v);
/* Percurso em largura */
void graph_bfs(graph_t *graph, int src, int *dist);
/* Destruicao do grafo */
void graph_free(graph_t *graph);

#endif