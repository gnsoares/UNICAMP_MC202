#ifndef GRAFO_H
#define GRAFO_H

typedef struct graph_s {
	int **adj;
	int n_v;
} graph_t;

graph_t *graph_create(int n_v);
void graph_edge_insert(graph_t *graph, int u, int v);
void graph_bfs(graph_t *graph, int src, int *dist);
void graph_free(graph_t *graph);

#endif