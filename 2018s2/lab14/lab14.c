#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>

/* Funcao que verifica se um grupo de 3 pessoas esta entediado */
int is_bored(int age1, int age2, int age3) {
	double average = ( (double) (age1 + age2 + age3) ) / 3.0;
	if (average > 2*age1 || average > 2*age2 || average > 2*age3)
		return 1;
	return 0;
}

/* Funcao que verifica se um determinado elemento pertence a um vetor */
int in(int *v, int v_size, int x) {
	int i;
	for (i = 0; i < v_size; i++)
		if (v[i] == x)
			return 1;
	return 0;
}

int main() {
	
	int i, vertex1, vertex2, n_people, n_links, k = 0;
	int *ages; /* Vetor que associa a ordem da pessoa a sua idade */
	int *bored_people; /* Vetor que guarda as pessoas entediadas */
	list_node_t *curr1, *curr2;
	graph_t *graph;

	/* Leitura e construcao das estruturas usadas */
	scanf("%d %d", &n_people, &n_links);
	ages = malloc(n_people * sizeof(int));
	bored_people = malloc(n_people * sizeof(int));
	if (!ages || !bored_people) exit(1);
	for (i = 0; i < n_people; i++)
		scanf("%d", &ages[i]);
	graph = graph_create(n_people);
	/* Insercao das arestas */
	for (i = 0; i < n_links; i++) {
		scanf("%d %d", &vertex1, &vertex2);
		graph_edge_insert(graph, vertex1, vertex2);
	}
	
	/* Verificacao de quais pessoas estao entediadas */
	for (i = 0; i < n_people; i++) {
		/* Para cada 2 pessoas ligadas a atual, verificar se as duas estao ligadas
		 * Se estiverem, um grupo de 3 pessoas foi encontrado
		 * Verificar se estao entediados
		 */
		for (curr1 = graph->adjacency[i]; curr1; curr1 = curr1->next) {
			/* Caso a pessoa ja esteja na lista de entediados, procurar a proxima */
			if (in(bored_people, k, i))
				break;
			for (curr2 = curr1->next; curr2; curr2 = curr2->next) {
				if (has_edge(graph, curr1->value, curr2->value))
					if (is_bored(ages[i], ages[curr1->value], ages[curr2->value])) {
						bored_people[k++] = i;
						break;
					}
			}
		}
	}

	/* Imprimir todos os entediados */
	for (i = 0; i < k; i++) {
		printf("%d\n", bored_people[i]);
	}

	/* Liberacao do espaco alocado */
	graph_free(graph);
	free(ages);
	free(bored_people);

	return 0;
}