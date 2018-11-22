#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"

#define DEBUG 1

int main()
{
	int i, j, k, n_students, n_groups, *v, **links;
	graph_t *groups_graph;

	scanf("%d %d", &n_students, &n_groups);
	groups_graph = graph_create(n_students);
	links = malloc(n_students * sizeof(int *));
	if (!links) exit(1);
	for (i = 0; i < n_students; i++) {
		links[i] = malloc(n_students * sizeof(int));
		if (!links[i]) exit(1);
	}
	for (i = 0; i < n_students; i++)
		for (j = 0; j < n_students; j++)
			links[i][j] = (i == j) ? 1 : 98;
	printf("n = %d\n", n_students);

	v = malloc(n_students * sizeof(int));
	if (!v) exit(1);
	for (i = 0; i < n_groups; i++) {
		scanf("%d", &n_students);
		for (j = 0; j < n_students; j++)
			scanf("%d", &v[j]);
		for (j = 0; j < n_students; j++)
			for (k = j+1; k < n_students; k++)
				graph_edge_insert(groups_graph, v[j], v[k]);
	}
		
	graph_bfs(groups_graph, 0);
	/*print_mat(links, groups_graph->n_v); printf("\n");

	for (i = 0; i < groups_graph->n_v; i++)
		for (j = i+1; j < groups_graph->n_v; j++)
			links[j][i] = links[i][j] = graph_bfs(groups_graph, links, i, j);
		
	print_mat(links, groups_graph->n_v); printf("\n");*/

	/*for (i = 0; i < groups_graph->n_v-1; i++)
		for (j = i+2; j < groups_graph->n_v; j++)
			links[i][j] = links[j][i] = (links[i][j-1] && links[j-1][j]) || (!links[i][j-1] && !links[j-1][j]) ? 98 : 0;

	print_mat(links, groups_graph->n_v); printf("\n");

	for (i = 0; i < groups_graph->n_v; i++)
		for (j = 0; j < groups_graph->n_v; j++)
			if ((i - j > 1 || i - j < -1) && links[i][j])
				graph_bfs(groups_graph, links, i, j);
		
	print_mat(links, groups_graph->n_v); printf("\n");*/

/*	for (i = 0; i < groups_graph->n_v; i++) {
		for (j = 0; j < groups_graph->n_v; j++)
			if (links[i][j] == 0)
				printf("%d ", j);
		printf("\n");
	}
*/
	free(v);
	printf("rodou\n");
	return 0;
}