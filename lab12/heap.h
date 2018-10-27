#ifndef HEAP_H
#define HEAP_H

/**
 * Interface de um tipo abstrato de dados de um lote de caixas;
 * Sao usados um MAX-HEAP e um MIN-HEAP para guardar as estruturas de caixas;
 * O min-heap guarda a metade com as caixas mais pesadas;
 * O max-heap guarda a metade com as caixas mais leves;
 */

#define MAX_STRING_LENGTH 20

typedef enum type_heap {MIN, MAX} Type_heap;

typedef struct {
	char product[MAX_STRING_LENGTH];
	int weight;
} Box;

typedef struct {
	Box *v;
	int size, capacity;
	Type_heap type;
} Heap;

typedef struct {
	Heap *lowers, *highers; 
} Lot;


/**
 * Cria um lote vazio de caixas
 * @param capacity numero de caixas do lote
 * @return lote
 */
Lot *create_lot(int capacity);

/**
 * Adiciona uma caixa no lote
 * @param lot lote
 * @param product nome do produto
 * @param weight peso do produto
 */
void lot_add(Lot *lot, char *product, int weight);

/**
 * Imprime as caixas que devem ser inspecionadas
 * @param lot lote
 */
void print_selected_boxes(Lot *lot);

/**
 * Libera o espaco alocado por um lote
 * @param lot lote
 */
void free_lot(Lot *lot);

#endif