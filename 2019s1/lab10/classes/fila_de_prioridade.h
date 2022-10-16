#ifndef FILA_DE_PRIORIDADE
#define FILA_DE_PRIORIDADE

typedef struct heap_s {
	int size; // max number of elements
	int count; // current number of elements
	int *v; // elements array
} * heap_t;

/* create a heap
 * @param size max number of elements
 * @return pointer to heap
 */
heap_t heap_create(int size);
/* insert element in heap
 * @param h heap pointer
 * @param x element to insert
 */
void heap_push(heap_t h, int x);
/* remove element from top of heap
 * @param h heap pointer
 * @return element on top of heap
 */
int heap_pop(heap_t h);
/* free memory allocated to heap
 * @param h heap pointer
 */
void heap_free(heap_t h);

#endif
