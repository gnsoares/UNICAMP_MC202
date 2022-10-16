#ifndef GRAFO_H
#define GRAFO_H

/* Interface de uma estrutura de GRAFO que usa listas ligadas para guardar as arestas */

typedef struct list_node_s {
	int value;
	struct list_node_s *next;
} list_node_t;

typedef struct graph_s {
	list_node_t **adjacency;
	int n_v;
} graph_t;

/* Adiciona na lista */
list_node_t *list_add(list_node_t *list, int x);
/* Destroi a lista */
void list_free(list_node_t *list);
/* Criacao do grafo */
graph_t *graph_create(int n_v);
/* Insercao de aresta no grafo */
void graph_edge_insert(graph_t *graph, int u, int v);
/* Verificacao se ha aresta entre dois vertices */
int has_edge(graph_t *graph, int u, int v);
/* Destroi o grafo */
void graph_free(graph_t *graph);

#endif