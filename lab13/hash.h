#ifndef HASH_H
#define HASH_H

#define MAX 3037
#define MAX_NAMES_LEN 42
#define PRIME 3023

/* Interface de uma TABELA DE ESPALHAMENTO implementada usando vetores */

typedef struct entry_s {
	/* A chave e o nome de dois autores. O valor e 1 se ja colaboraram, senao 0 */
	char key[MAX_NAMES_LEN];
	int bool_collab;
} entry_t;

typedef struct hashtable_s {
	entry_t table[MAX];	
} hashtable_t;

/* Criacao de uma tabela de espalhamento */
hashtable_t *ht_create(void);
/* Alteracao do valor de uma certa entrada */
void ht_set(hashtable_t *hashtable, char *key, int value);
/* Obtencao do valor de uma certa entrada */
int ht_get(hashtable_t *hashtable, char *key);
/* Liberacao de espaco alocado */
void ht_free(hashtable_t *hashtable);

#endif