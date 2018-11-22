#include <stdlib.h>
#include "grafo.h"

graph_t *graph_create(int n_v) {
	int i, j;
	graph_t *graph = malloc(sizeof(graph_t));
	if (!graph) exit(1);
	graph->n_v = n_v;
	graph->adj = malloc(n_v * sizeof(int *));
	if (!graph->adj) exit(1);
	for (i = 0; i < n_v; i++) {
		graph->adj[i] = malloc(n_v *sizeof(int));
		if (!graph->adj[i]) exit(1);
	}
	for (i = 0; i < n_v; i++)
		for (j = 0; j < n_v; j++)
			graph->adj[i][j] = 0;
	return graph;
}

void graph_edge_insert(graph_t *graph, int u, int v) {
	graph->adj[u][v] = graph->adj[v][u] = 1;
}

void graph_free(graph_t *graph) {
	int i;
	for (i = 0; i < graph->n_v; i++)
		free(graph->adj[i]);
	free(graph->adj);
	free(graph);
}

/* Implementacao de uma fila usando lista ligada a ser usada no percurso em largura */
typedef struct list_node_s {
	int value;
	struct list_node_s *next;
} list_node_t;

typedef struct queue_s {
	list_node_t *head, *tail;
} queue_t;

/* Criacao da fila */
queue_t *queue_create(void) {
	queue_t *new = malloc(sizeof(queue_t));
	if (!new) exit(1);
	new->head = new->tail = NULL;
	return new;
}

/* Verificacao se a fila esta vazia */
int queue_is_empty(queue_t *queue) {
	return !queue->head;
}

/* Adicao de elemento na fila */
void queue_queue(queue_t *queue, int x) {
	list_node_t *new = malloc(sizeof(list_node_t));
	if (!new) exit(1);
	new->value = x;
	new->next = NULL;
	if (queue_is_empty(queue)) queue->head = new;
	else queue->tail->next = new;
	queue->tail = new;
}

/* Remocao de elemento da fila */
int queue_dequeue(queue_t *queue) {
	int r;
	list_node_t *node;
	r = queue->head->value;
	node = queue->head;
	if (queue->head == queue->tail) queue->tail = NULL;
	queue->head = queue->head->next;
	free(node);
	return r;
}

/* Liberacao do espaco alocado pela fila */
void queue_free(queue_t *queue) {
	while (!queue_is_empty(queue))
		queue_dequeue(queue);
	free(queue);
}

/* Percurso em largura do grafo:
	@param: graph - estrutura do grafo (usando matriz de adjacencias) 
	@param: src - posicao inicial do percurso
	@param: dist - vetor em que cada posicao e a menor distancia da
				   origem a essa posicao
*/
void graph_bfs(graph_t *graph, int src, int *dist) {
	int i, j;
	int *visited = malloc(graph->n_v * sizeof(int));
	queue_t *queue = queue_create();

	for (i = 0; i < graph->n_v; i++) {
		visited[i] = 0;
		dist[i] = -1;
	}

	queue_queue(queue, src);
	visited[src] = 1;
	dist[src] = 0;
	while (!queue_is_empty(queue)) {
		i = queue_dequeue(queue);
		for (j = 0; j < graph->n_v; j++)
			if (graph->adj[i][j] && !visited[j]) {
				visited[j] = 1;
				dist[j] = dist[i] + 1;
				queue_queue(queue, j);
			}
	}

	queue_free(queue);
	free(visited);
}