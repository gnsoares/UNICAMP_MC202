#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "digrafo.h"

/* calculates the liquid flux between two points
 * @param g_out graph that indicates the flux outgoing of each vertex
 * @param g_in graph that indicates the flux ingoing of each vertex
 * @param n index of vertex
 * @return value of liquid flux (> 0 if waste)
 */
int get_liquid_flux(graph_t g_out, graph_t g_in, int n) {
	int res = 0;
	list_node_t node;
	for (node = g_out->adjacency[n]; node; node = node->next)
		res -= node->flux;
	for (node = g_in->adjacency[n]; node; node = node->next)
		res += node->flux;
	return res;
}
/* verifies if a value is in an array
 * @param v array
 * @param n size of array
 * @param x value
 * @return 1 if value is in array else 0
 */
int is_in(int *v, int n, int x) {
	for (int i = 0; i < n; i++)
		if (v[i] == x)
			return 1;
	return 0;
}


int main(void) {
	
	int n_v, n_e, n_src, n_out, total_waste = 0; // size of problem
	int org, dest, flux;
	int * src, * out, * liquid_flux; // arrays
	graph_t g_out, g_in; // graphs of outgoing and ingoing flux


	// Input read and structure construction
	scanf("%d\n%d", &n_v, &n_e);
	assert(liquid_flux = malloc(n_v * sizeof(int)));
	g_out = graph_create(n_v);
	g_in = graph_create(n_v);

	for(int i = 0; i < n_e; i++) {
		scanf("%d %d %d", &org, &dest, &flux);
		graph_edge_insert(g_out, org, dest, flux);
		graph_edge_insert(g_in, dest, org, flux);
	}

	scanf("%d", &n_src);
	assert(src = malloc(n_src * sizeof(int)));
	for (int i = 0; i < n_src; i++)
		scanf("%d", &src[i]);

	scanf("%d", &n_out);
	assert(out = malloc(n_out * sizeof(int)));
	for (int i = 0; i < n_out; i++)
		scanf("%d", &out[i]);


	// Calculation of waste
	for(int i = 0; i < n_v; i++)
		liquid_flux[i] = get_liquid_flux(g_out, g_in, i);
	for(int i = 0; i < n_src; i++)
		total_waste -= liquid_flux[src[i]];
	for(int i = 0; i < n_out; i++)
		total_waste -= liquid_flux[out[i]];


	// Print output
	printf("%d\n", total_waste);
	for(int i = 0; i < n_v; i++)
		if (liquid_flux[i] > 0 && !is_in(src, n_src, i) && !is_in(out, n_out, i))
			printf("%d %d\n", i, liquid_flux[i]);


	// Free allocated memory
	graph_free(g_out);
	graph_free(g_in);
	free(src);
	free(out);
	free(liquid_flux);

	return 0;
}