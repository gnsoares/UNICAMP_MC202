#include "fila_de_prioridade.h"
#include <stdlib.h>
#include <assert.h>

#define bool int

heap_t heap_create(int size) {
	heap_t h = malloc(sizeof(struct heap_s));
	assert(h);
	assert(h->v = malloc(size * sizeof(int)));
	h->count = 0;
	h->size = size;
	return h;
}

int get_left_child(int index) {
	return 2 * index + 1;
}
int get_right_child(int index) {
	return 2 * index + 2;
}
int get_parent(int index) {
	return (index - 1) / 2;
}
bool has_left_child(heap_t h, int index) {
	return get_left_child(index) < h->count;
}
bool has_right_child(heap_t h, int index) {
	return get_right_child(index) < h->count;
}
bool has_parent(heap_t h, int index) {
	return get_parent(index) >= 0;
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
	while (has_parent(h, i) && h->v[parent = get_parent(i)] > h->v[i]) {
		swap(&h->v[parent], &h->v[i]);
		i = parent;
	}
}

/* fixes heap from top to bottom
 * @param h heap pointer
 */
void heapify_down(heap_t h) {
	int min_child, i = 0;
	while (has_left_child(h, i)) {
		min_child = get_left_child(i);
		if (has_right_child(h, i) && h->v[get_right_child(i)] < h->v[min_child])
			min_child = get_right_child(i);
		if (h->v[i] >= h->v[min_child])
			swap(&h->v[i], &h->v[min_child]);
		else
			break;
		i = min_child;
	}
}

void heap_push(heap_t h, int x) {
	if (h->count >= h->size) return;
	h->v[h->count++] = x;
	heapify_up(h);
}

int heap_pop(heap_t h) {
	int out = h->v[0];
	h->v[0] = h->v[h->count-- - 1];
	heapify_down(h);
	return out;
}

void heap_free(heap_t h) {
	if (h) {
		free(h->v);
		free(h);
	}
}

