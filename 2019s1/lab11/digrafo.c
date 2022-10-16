#include "digrafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

list_node_t list_add(list_node_t list, int dest, int flux) {
	list_node_t new = malloc(sizeof(struct list_node_s));
	assert(new);
	new->dest = dest;
	new->flux = flux;
	new->next = list;
	return new;
}

void list_free(list_node_t list) {
	if (!list) return;
	list_free(list->next);
	free(list);
}

graph_t graph_create(int n_v) {
	graph_t graph = malloc(sizeof(struct graph_s));
	assert(graph);
	graph->n_v = n_v;
	graph->adjacency = malloc(n_v * sizeof(struct list_node_s));
	assert(graph->adjacency);
	for (int i = 0; i < n_v; graph->adjacency[i++] = NULL);
	return graph;
}

void graph_edge_insert(graph_t graph, int org, int dest, int flux) {
	graph->adjacency[org] = list_add(graph->adjacency[org], dest, flux);
}

int has_edge(graph_t graph, int u, int v) {
	list_node_t n;
	for (n = graph->adjacency[u]; n; n = n->next)
		if (n->dest == v)
			return 1;
	return 0;
}

void graph_free(graph_t graph) {
	for (int i = 0; i < graph->n_v; list_free(graph->adjacency[i++]));
	free(graph->adjacency);
	free(graph);
}