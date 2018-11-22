#ifndef GRAFO_H
#define GRAFO_H

typedef struct list_node_s {
	int value;
	struct list_node_s *next;
} list_node_t;

typedef struct graph_s {
	list_node_t **adjacency;
	int n_v;
} graph_t;

list_node_t *list_add(list_node_t *list, int x);
void list_free(list_node_t *list);
graph_t *graph_create(int n_v);
void graph_edge_insert(graph_t *graph, int u, int v);
int has_edge(graph_t *graph, int u, int v);
void graph_free(graph_t *graph);

#endif