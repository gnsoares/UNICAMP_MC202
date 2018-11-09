#ifndef HASH_H
#define HASH_H

#define MAX 2039
#define MAX_NAMES_LEN 42
#define PRIME 2029

/* Interface de uma TABELA DE ESPALHAMENTO implementada usando vetores */

typedef struct entry_s {
	/* Chave: nome de dois autores separado por virgula */
	char key[MAX_NAMES_LEN];
	/* Valor: 1 se ja colaboraram, senao 0 */
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