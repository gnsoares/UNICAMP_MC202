#include "fila_de_prioridade.h"
#include <stdlib.h>
#include <assert.h>

#define bool int
#define LEFT_C(i) (2 * i + 1)
#define RIGHT_C(i) (2 * i + 2)
#define PARENT(i) ((i - 1) / 2)

heap_t heap_create(int size) {
	heap_t h = malloc(sizeof(struct heap_s));
	assert(h);
	assert(h->v = malloc(size * sizeof(int)));
	assert(h->index = malloc(size * sizeof(int)));
	h->count = 0;
	h->size = size;
	return h;
}

void swap(int * a, int * b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

/* fixes heap from the bottom to the top
 * @param h heap pointer
 */
void heapify_up(heap_t h) {
	int parent, i = h->count - 1;
	// while the element has a parent and it is bigger -> swap
	while (PARENT(i) >= 0 && h->v[parent = PARENT(i)] > h->v[i]) {
		swap(&h->v[parent], &h->v[i]);
		swap(&h->index[parent], &h->index[i]);
		i = parent;
	}
}

/* fixes heap from top to bottom
 * @param h heap pointer
 */
void heapify_down(heap_t h) {
	int min_child, i = 0;
	// while the element has at least one child
	while (LEFT_C(i) < h->count) {
		// suppose left if smaller child
		min_child = LEFT_C(i);
		// if right is smaller child -> change
		if (RIGHT_C(i) < h->count && h->v[RIGHT_C(i)] < h->v[min_child])
			min_child = RIGHT_C(i);
		// if smaller child is smaller than parent -> swap
		if (h->v[i] > h->v[min_child]) {
			swap(&h->v[i], &h->v[min_child]);
			swap(&h->index[i], &h->index[min_child]);
		}
		else
			break;
		i = min_child;
	}
}

void heap_push(heap_t h, int x, int i) {
	if (h->count >= h->size)
		heap_double_cap(h);
	// insert at the end and fix position
	h->v[h->count] = x;
	h->index[h->count] = i;
	h->count++;
	heapify_up(h);
}

int heap_pop(heap_t h, int * i) {
	int out = h->v[0];
	*i = h->index[0];
	// move last element to top and fix position
	h->v[0] = h->v[h->count - 1];
	h->index[0] = h->index[h->count - 1];
	h->count--;
	heapify_down(h);
	return out;
}

void heap_double_cap(heap_t h) {
	assert(h->v = realloc(h->v, 2 * h->size * sizeof(int)));
	assert(h->index = realloc(h->v, 2 * h->size * sizeof(int)));
	h->size *= 2;
}

void heap_free(heap_t h) {
	if (h) {
		free(h->v);
		free(h->index);
		free(h);
	}
}

