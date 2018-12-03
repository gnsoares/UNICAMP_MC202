#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "hash.h"

hashtable_t *ht_create(void) {

	int i;
	hashtable_t *hashtable = malloc(sizeof(hashtable_t));

	if (!hashtable) exit(1);
	/* Inicializacao dos dados da tabela */
	for (i = 0; i < MAX; i++) {
		strcpy(hashtable->table[i].key, "");
		hashtable->table[i].bool_collab = 0;
	}

	return hashtable;	
}

int ht_hash1(char *key) {

	unsigned long int hashval = 0;
	int i = 0;

	/* Conversao da string em inteiro */
	while (hashval < ULONG_MAX && i < strlen(key)) {
		hashval = hashval << 8;
		hashval += key[i++];
	}

	return hashval % MAX;
}

int ht_hash2(char *key) {

	unsigned long int hashval = 0;
	int i = 0;

	/* Conversao da string em inteiro */
	while (hashval < ULONG_MAX && i < strlen(key)) {
		hashval = hashval << 8;
		hashval += key[i++];
	}

	return PRIME - hashval % PRIME;
}

/* Funcao de hashing principal */
int ht_hash(char *key, int i) {
	return (ht_hash1(key) + i*ht_hash2(key)) % MAX;
}

void ht_set(hashtable_t *hashtable, char *key, int value) {

	int i = 1;
	int index = ht_hash(key, i);

	/**
	 * Enquanto:
		* o indice nao for de um espaco vazio,
		* for diferente da chave pedida,
		* nao tiver percorrido a tabela inteira;
	 * Procurar um novo indice
	 */
	while (strcmp(hashtable->table[index].key, "")
			&& strcmp(hashtable->table[index].key, key)
			&& i < MAX)
		index = ht_hash(key, ++i);

	/* Se nao houver nenhuma posicao disponivel */
	if (i == MAX) return;

	/* Alterar o valor com o indice correto */
	strcpy(hashtable->table[index].key, key);
	hashtable->table[index].bool_collab = value;
}

int ht_get(hashtable_t *hashtable, char *key) {

	int i = 1;
	int index = ht_hash(key, i);

	/* E simulado o processo de insercao para obter o valor */
	while (strcmp(hashtable->table[index].key, "")
			&& strcmp(hashtable->table[index].key, key)
			&& i < MAX)
		index = ht_hash(key, ++i);

	/* Se nao houver nenhuma posicao disponivel */
	if (i == MAX) return 0;

	return hashtable->table[index].bool_collab;
}

void ht_free(hashtable_t *hashtable) {
	free(hashtable);
}