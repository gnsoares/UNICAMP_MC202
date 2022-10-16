#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

/** Metodos relevantes apenas para a implementacao: **/
/* Metodos para caixa: */

/**
 * Imprime o produto e o peso da caixa
 * @param box caixa a ser impressa
 */
void print_box(Box box);

/* Metodos para fila de prioridades: */

/**
 * troca caixas de posicao
 * @param a box 1
 * @param b box 2
 */
void swap(Box *a, Box *b);

/**
 * Cria heap vazio
 * @param capacity tamanho maximo
 * @param type max ou min
 * @return heap
 */
Heap *create_heap(int capacity, Type_heap type);

/**
 * Acha o pai
 * @param i posicao do no
 * @return posicao do pai
 */
int get_parent(int i);

/**
 * Acha o filho esquerdo
 * @param i posicao do no
 * @return posicao do filho esquerdo
 */
int get_left_child(int i);

/**
 * Tem filho esquerdo?
 * @param heap heap a procurar
 * @param i posicao do no
 * @return 1 se sim 0 se nao
 */
int has_left_child(Heap *heap, int i);

/**
 * Acha o filho direito
 * @param i posicao do no
 * @return posicao do filho direito
 */
int get_right_child(int i);

/**
 * Tem filho direito?
 * @param heap heap a procurar
 * @param i posicao do no
 * @return 1 se sim 0 se nao
 */
int has_right_child(Heap *heap, int i);

/**
 * Subir em um min-heap
 * @param heap heap a procurar
 * @param i posicao do no
 */
void min_heapify_up(Heap *heap, int i);

/**
 * Subir em um max-heap
 * @param heap heap a procurar
 * @param i posicao do no
 */
void max_heapify_up(Heap *heap, int i);

/**
 * Descer em um min-heap
 * @param heap heap a procurar
 * @param i posicao do no
 */
void min_heapify_down(Heap *heap, int i);

/**
 * Descer em um max-heap
 * @param heap heap a procurar
 * @param i posicao do no
 */
void max_heapify_down(Heap *heap, int i);

/**
 * Adiciona caixa no heap
 * @param heap heap a procurar
 * @param box caixa a adicionar
 */
void heap_add(Heap *heap, Box box);

/**
 * Remove a caixa do topo
 * @param heap heap a procurar
 * @return caixa
 */
Box heap_remove(Heap *heap);

/**
 * Olha a caixa do topo
 * @param heap heap a procurar
 * @return caixa
 */
Box heap_peek(Heap *heap);

/**
 * Libera o heap alocado
 * @param heap heap a liberar
 */
void free_heap(Heap *heap);

/* Metodos para lote: */

/**
 * Mantem o lote balanceado
 * @param lot lote a ser balanceado
 */
void rebalance(Lot *lot);


void print_box(Box box) {
	printf("%s: %d\n", box.product, box.weight);
}

void swap(Box *a, Box *b) {
	Box t = *a;
	*a = *b;
	*b = t;
}

Heap *create_heap(int capacity, Type_heap type) {
	Heap *heap = malloc(sizeof(Heap));
	if (!heap) exit(1);
	heap->v = malloc(capacity * sizeof(Box));
	if (!heap->v) exit(1);
	heap->size = 0;
	heap->capacity = capacity; 
	heap->type = type;
	return heap;
}

int get_parent(int i) { return (i-1)/2; }

int get_left_child(int i) { return 2*i + 1; }

int has_left_child(Heap *heap, int i) { return get_left_child(i) < heap->size; }

int get_right_child(int i) { return 2*i + 2; }

int has_right_child(Heap *heap, int i) { return get_right_child(i) < heap->size; }

void min_heapify_up(Heap *heap, int i) {
	if (i > 0 && heap->v[get_parent(i)].weight > heap->v[i].weight) {
		swap(&heap->v[i], &heap->v[get_parent(i)]);
		min_heapify_up(heap, get_parent(i));
	}
}

void max_heapify_up(Heap *heap, int i) {
	if (i > 0 && heap->v[get_parent(i)].weight < heap->v[i].weight) {
		swap(&heap->v[i], &heap->v[get_parent(i)]);
		max_heapify_up(heap, get_parent(i));
	}
}

void min_heapify_down(Heap *heap, int i) {
	int smaller_child;
	if (has_left_child(heap, i)) {
		smaller_child = get_left_child(i);
		if (has_right_child(heap, i)
		 && heap->v[get_left_child(i)].weight > heap->v[get_right_child(i)].weight)
			smaller_child = get_right_child(i);
		if (heap->v[i].weight > heap->v[smaller_child].weight) {
			swap(&heap->v[i], &heap->v[smaller_child]);
			min_heapify_down(heap, smaller_child);
		}
	}

}

void max_heapify_down(Heap *heap, int i) {
	int bigger_child;
	if (has_left_child(heap, i)) {
		bigger_child = get_left_child(i);
		if (has_right_child(heap, i)
		 && heap->v[get_left_child(i)].weight < heap->v[get_right_child(i)].weight)
			bigger_child = get_right_child(i);
		if (heap->v[i].weight < heap->v[bigger_child].weight) {
			swap(&heap->v[i], &heap->v[bigger_child]);
			max_heapify_down(heap, bigger_child);
		}
	}
}

void heap_add(Heap *heap, Box box) {
	heap->v[heap->size++] = box;
	if (heap->type == MIN) min_heapify_up(heap, heap->size-1);
	if (heap->type == MAX) max_heapify_up(heap, heap->size-1);
}

Box heap_remove(Heap *heap) {
	Box box = heap->v[0];
	swap(&heap->v[0], &heap->v[--heap->size]);
	if (heap->type == MIN) min_heapify_down(heap, 0);
	if (heap->type == MAX) max_heapify_down(heap, 0);
	return box;
}

Box heap_peek(Heap *heap) {
	return heap->v[0];
}

void free_heap(Heap *heap) {
	if (heap) {
		free(heap->v);
		free(heap);
	}
}

Lot *create_lot(int capacity) {
	Lot *lot = malloc(sizeof(Lot));
	if (!lot) exit(1);
	lot->lowers = create_heap(capacity, MAX);
	lot->highers = create_heap(capacity, MIN);
	return lot;
}

void lot_add(Lot *lot, char *product, int weight) {
	Box box;
	strcpy(box.product, product);
	box.weight = weight;

	/* Adicionar no heap correto */
	if (lot->lowers->size == 0 || weight < heap_peek(lot->lowers).weight)
		heap_add(lot->lowers, box);
	else
		heap_add(lot->highers, box);

	/* Garantir que o lote sempre esteja balanceado */
	rebalance(lot);
}

void rebalance(Lot *lot) {
	Heap *bigger_heap = lot->lowers->size > lot->highers->size ? lot->lowers : lot->highers;
	Heap *smaller_heap = lot->lowers->size > lot->highers->size ? lot->highers : lot->lowers;

	/* Se a diferenca de tamanho entre os dois heaps for maior que 1,
	 * a mediana nao se encontra no topo. Rebalancear.
	 */
	if (bigger_heap->size - smaller_heap->size > 1)
		heap_add(smaller_heap, heap_remove(bigger_heap));
}

void print_selected_boxes(Lot *lot) {
	Heap *bigger_heap = lot->lowers->size > lot->highers->size ? lot->lowers : lot->highers;
	Heap *smaller_heap = lot->lowers->size > lot->highers->size ? lot->highers : lot->lowers;

	/* Se os dois tem o mesmo tamanho, o numero de caixas e par: selecionar duas */
	if (smaller_heap->size == bigger_heap->size) {
		print_box(heap_peek(lot->lowers));
		print_box(heap_peek(lot->highers));
	/* Senao, a diferenca e de 1: o topo do heap maior guarda a mediana */
	} else {
		print_box(heap_peek(bigger_heap));
	}
}

void free_lot(Lot *lot) {
	free_heap(lot->lowers);
	free_heap(lot->highers);
	free(lot);
}