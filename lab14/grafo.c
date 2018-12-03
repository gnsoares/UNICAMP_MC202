#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

list_node_t *list_add(list_node_t *list, int x) {
	list_node_t *new = malloc(sizeof(list_node_t));
	if (!new) exit(1);
	new->value = x;
	new->next = list;
	return new;
}

list_node_t *list_remove(list_node_t *list, int x) {
	list_node_t *next;
	if (!list) return NULL;
	if (list->value == x) {
		next = list->next;
		free(list);
		return next;
	}
	list = list_remove(list->next, x);
	return list;
}

void list_free(list_node_t *list) {
	if (!list) return;
	list_free(list->next);
	free(list);
}

graph_t *graph_create(int n_v) {
	int i;
	graph_t *graph = malloc(sizeof(graph_t));
	if (!graph) exit(1);
	graph->n_v = n_v;
	graph->adjacency = malloc(n_v * sizeof(list_node_t *));
	if (!graph->adjacency) exit(1);
	for (i = 0; i < n_v; i++)
		graph->adjacency[i] = NULL;
	return graph;
}

void graph_edge_insert(graph_t *graph, int u, int v) {
	graph->adjacency[u] = list_add(graph->adjacency[u], v);
	graph->adjacency[v] = list_add(graph->adjacency[v], u);
}

int has_edge(graph_t *graph, int u, int v) {
	list_node_t *curr;
	for (curr = graph->adjacency[u]; curr; curr = curr->next)
		if (curr->value == v)
			return 1;
	return 0;
}

void graph_free(graph_t *graph) {
	int i;
	for (i = 0; i < graph->n_v; i++)
		list_free(graph->adjacency[i]);
	free(graph->adjacency);
	free(graph);
}

