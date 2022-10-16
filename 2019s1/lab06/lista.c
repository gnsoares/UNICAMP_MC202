#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lista.h"

int_list_t * int_list_create(void) {
	int_list_t * new = malloc(sizeof(int_list_t));
	assert(new);
	new->head = NULL;
	return new;
}

void int_list_insert(int_list_t * list, int x) {
	int_node_t * new  = malloc(sizeof(int_node_t));
	assert(new);
	new->data = x;
	new->next = list->head;
	list->head = new;
}

void int_list_insert_sorted(int_list_t * list, int x) {
	int_node_t * prev, * tmp, * new  = malloc(sizeof(int_node_t));
	assert(new);
	new->data = x;

	// if the list has 0 or 1 element >= x, insert at the head
	if (!list->head || list->head->data >= x) {
		new->next = list->head;
		list->head = new;
		return;
	}
	// else, find the right spot and insert
	for (tmp = list->head;
		 tmp && tmp->data < x;
		 prev = tmp, tmp = tmp->next);
	prev->next = new;
	new->next = tmp;
}

void int_list_remove(int_list_t * list) {
	int_node_t * tmp;
	if (list->head) {
		tmp = list->head->next;
		free(list->head);
		list->head = tmp;
	}
}

void int_list_print(int_list_t * list) {
	for (int_node_t * tmp = list->head; tmp; tmp = tmp->next)
		printf("%d\n", tmp->data);
}

void int_list_free(int_list_t * list) {
	while (list->head)
		int_list_remove(list);
	free(list);
}