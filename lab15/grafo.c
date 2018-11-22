#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"

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
	graph->adj = malloc(n_v * sizeof(list_node_t *));
	if (!graph->adj) exit(1);
	for (i = 0; i < n_v; i++)
		graph->adj[i] = NULL;
	return graph;
}

void graph_edge_insert(graph_t *graph, int u, int v) {
	if (has_edge(graph, u, v)) return;
	graph->adj[u] = list_add(graph->adj[u], v);
	graph->adj[v] = list_add(graph->adj[v], u);
}

void graph_edge_remove(graph_t *graph, int u, int v) {
	graph->adj[u] = list_remove(graph->adj[u], v);
	graph->adj[v] = list_remove(graph->adj[v], u);	
}

int has_edge(graph_t *graph, int u, int v) {
	list_node_t *curr;
	if (u == v) return 1;
	for (curr = graph->adj[u]; curr; curr = curr->next)
		if (curr->value == v)
			return 1;
	return 0;
}

void print_edges(graph_t *graph) {
	int u;
	list_node_t *t;
	for (u = 0; u < graph->n_v; u++)
		for (t = graph->adj[u]; t != NULL; t = t->next)
			printf("{%d,%d}\n", u, t->value);
}

void graph_free(graph_t *graph) {
	int i;
	for (i = 0; i < graph->n_v; i++)
		list_free(graph->adj[i]);
	free(graph->adj);
	free(graph);
}

typedef struct queue_s {
	list_node_t *head, *tail;
} queue_t;

queue_t *queue_create(void) {
	queue_t *new = malloc(sizeof(queue_t));
	if (!new) exit(1);
	new->head = new->tail = NULL;
	return new;
}

int queue_is_empty(queue_t *queue) {
	return !queue->head;
}

void queue_queue(queue_t *queue, int x) {
	list_node_t *new = malloc(sizeof(list_node_t));
	if (!new) exit(1);
	new->value = x;
	new->next = NULL;
	if (queue->tail) queue->tail->next = new;
	else queue->head = new;
	queue->tail = new;
}

int queue_dequeue(queue_t *queue) {
	int r;
	list_node_t *node;
	if (!queue->head) return -1;
	r = queue->head->value;
	node = queue->head;
	if (queue->head == queue->tail) queue->tail = NULL;
	queue->head = queue->head->next;
	free(node); 
	return r;
}

void list_print(list_node_t *list) {
	if (list) {
		printf("%d ", list->value);
		list_print(list->next);
	}
}

void print_queue(queue_t *queue) {
	if (queue->head) {
		printf("fila: ");
		list_print(queue->head);
	}
	printf("\n");
}

void queue_free(queue_t *queue) {
	while (queue->head)
		queue_dequeue(queue);
	free(queue);
}

/*int graph_bfs(graph_t *graph, int **mat, int source, int destination) {
	int i, found = 0, len = 0;
	int *visit = malloc(graph->n_v * sizeof(int));
	int *dist = malloc(graph->n_v * sizeof(int));
	list_node_t *curr;
	queue_t *queue = queue_create();
	
	for (i = 0; i < graph->n_v; i++) {
		visit[i] = 0;
		dist[i] = 98;
	}
	dist[source] = 0;
	queue_queue(queue, source);
	while (!queue_is_empty(queue)) {
		i = queue_dequeue(queue);
		if (i == destination) {
			found = 1;
		}
		if (visit[i] == 1)
			continue;
		visit[i] = 1;
		for (curr = graph->adj[i]; curr; curr = curr->next) {
			if (dist[curr->value] == 98 || dist[curr->value] > dist[i] + 1) dist[curr->value] = dist[i] + 1;
			queue_queue(queue, curr->value);
		}
	}

	queue_free(queue);
	len = dist[destination];
	free(visit); free(dist);
	print_mat(mat, graph->n_v); printf("\n");
	if (found) return len;
	return 0;
}*/

void graph_bfs(graph_t *graph, int s) {
	int w, v;
	int *pai = malloc(graph->n_v * sizeof(int));
	int *visitado = malloc(graph->n_v * sizeof(int));
	queue_t *f = queue_create();
	list_node_t *node;

	for (v = 0; v < graph->n_v; v++) {
		pai[v] = -1;
		visitado[v] = 0;
	}

	queue_queue(f,s);
	pai[s] = s;
	visitado[s] = 1;
	while (!queue_is_empty(f)) {
		v = queue_dequeue(f);
		for (w = 0, node = graph->adj[v]; w < graph->n_v && node; w++, node = node->next)
			if (node && !visitado[w]) {
				visitado[w] = 1;/* evita repetição na fila */
				pai[w] = v;
				queue_queue(f, w);
			}
	}
	queue_free(f);
	free(visitado);
	for (v = 0; v < graph->n_v; v++) {
		if (pai[v] != -1)
			printf("%d ", pai[v]);
	}
	printf("\n");
	/*return pai;*/
}

void print_mat(int **mat, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++)
			if (mat[i][j] > 9)
				printf("%d|", mat[i][j]);
			else
				printf(" %d|", mat[i][j]);
		printf("\n");
	}
}