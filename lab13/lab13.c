#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/* Lista ligada usada para armazenar os autores de um artigo */
typedef struct list_node_s {
	char key[MAX_NAMES_LEN/2+1];
	struct list_node_s *next;
} list_node_t;

list_node_t *list_add(list_node_t *list, char *key) {
	list_node_t *new = malloc(sizeof(list_node_t));
	if (!new) exit(1);
	strcpy(new->key, key);
	new->next = list;
	return new;
}

void list_free(list_node_t *list) {
	if (!list) return;
	list_free(list->next);
	free(list);
}

/* Le do teclado os autores de um artigo e retorna uma lista com eles */
list_node_t *build_author_list(void) {

	list_node_t *list = NULL;
	char initial, surname[MAX_NAMES_LEN/2], ponctuation = ',', name[MAX_NAMES_LEN/2+1];

	while (ponctuation != '.') {
		scanf(" %c. %[^.,]%c", &initial, surname, &ponctuation);
		sprintf(name, "%c%s", initial, surname);
		list = list_add(list, name);
	}
	return list;
}

/* Inclui em uma tabela de espalhamento as colaboracoes entre autores */
void ht_set_collab(hashtable_t *hashtable, list_node_t *list) {

	char collab[MAX_NAMES_LEN+2];
	list_node_t *curr1, *curr2;

	for (curr1 = list; curr1; curr1 = curr1->next)
		for (curr2 = curr1->next; curr2; curr2 = curr2->next)
			if (curr1 != curr2) {
				sprintf(collab, "%s,%s", curr1->key, curr2->key);
				ht_set(hashtable, collab, 1);
			}
}

/* Altera uma string para conter o nome de um autor digitado pelo usuario */
void request_name(char name[MAX_NAMES_LEN/2+1]) {	

	char initial, surname[MAX_NAMES_LEN/2];
	
	scanf(" %c. %[^,.]", &initial, surname);
	sprintf(name, "%c%s", initial, surname);
}

/* Com os nomes de dois autores, procura na tabela de espalhamento se os dois ja colaboraram */
int ht_get_collab(hashtable_t *hashtable, char *author1, char *author2) {

	char request1[MAX_NAMES_LEN+2], request2[MAX_NAMES_LEN+2];

	sprintf(request1, "%s,%s", author1, author2);
	sprintf(request2, "%s,%s", author2, author1);

	return (ht_get(hashtable, request1) || ht_get(hashtable, request2));
}

int main() {
	
	int i, n_papers, n_requests;
	/* Variaveis para armazenar os nomes dos autores */
	char name1[MAX_NAMES_LEN/2+1], name2[MAX_NAMES_LEN/2+1];
	/* A lista dos autores de um certo artigo e armazenada em uma lista ligada */
	list_node_t *list = NULL;
	/* Inicializacao da tabela */
	hashtable_t *hashtable = ht_create();

	/* Leitura e construcao da tabela de espalhamento */
	scanf("%d %d", &n_papers, &n_requests);
	for (i = 0; i < n_papers; i++) {
		list = build_author_list();
		ht_set_collab(hashtable, list);
		list_free(list);
	}

	/* Verificacao das consultas feitas */
	for (i = 0; i < n_requests; i++) {
		request_name(name1); scanf(",");
		request_name(name2); scanf(".");
		printf("%c\n", ht_get_collab(hashtable, name1, name2) ? 'S' : 'N');
	}

	/* Liberacao do espaco alocado */
	ht_free(hashtable);

	return 0;
}