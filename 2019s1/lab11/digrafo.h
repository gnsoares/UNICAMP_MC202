#ifndef DIGRAFO_H
#define DIGRAFO_H

typedef struct list_node_s {
	int dest, flux;
	struct list_node_s * next;
} * list_node_t;

typedef struct graph_s {
	list_node_t * adjacency;
	int n_v;
} * graph_t;

/* adds element to linked list 
 * @param list
 * @param dest index of destination vertex
 * @param flux value of flux between vertices
 * @return list
 */
list_node_t list_add(list_node_t list, int dest, int flux);
/* frees allocated memory of linked list
 * @param list
 */
void list_free(list_node_t list);
/* creates a graph
 * @param n_v number of vertices
 * @return graph
 */
graph_t graph_create(int n_v);
/* adds edge to graph
 * @param graph
 * @param org index of origin
 * @param dest index of destination
 * @param flux value of flux between vertices
 */
void graph_edge_insert(graph_t graph, int org, int dest, int flux);
/* verifies if exists edge between two vertices
 * @param graph
 * @param u index of origin
 * @param v index of destination
 * @return 1 if has edge else 0
 */
int has_edge(graph_t graph, int u, int v);
/* frees allocated memory of graph
 * @param graph
 */
void graph_free(graph_t graph);

#endif