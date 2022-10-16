#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Queue * createQueue() {
	Queue *new = malloc(sizeof(Queue));

	if (!new)
		exit(1);

	/* Ponteiros da fila nulos porque e uma fila vazia */
	new->head = NULL;
	new->tail = NULL;

	return new;
}

void copyQueue(Queue *queue1, Queue *queue2) {
	NodeQ *current;
	for (current = queue2->head; current; current = current->next)
		pushPlayer(queue1, current->player);
}

void pushPlayer(Queue *queue, Player *player) {
	NodeQ *new = malloc(sizeof(Queue));

	if (!new)
		exit(1);

	new->player = player;

	/* Se a lista estiver vazia, ambos ponteiros de referem ao novo no;
	 * Caso contrario, incluir no final;
	 */
	if (!queue->tail) {
		queue->head = new;
		queue->tail = new;
	} else {
		queue->tail->next = new;
		queue->tail = new;
	}

	new->next = NULL;
}

Player * popPlayer(Queue *queue) {
	Player *player;
	NodeQ *pop;

	/* Desenfileirar apenas caso não vazia */
	if (queue->head) {
		player = queue->head->player;
		pop = queue->head;
		queue->head = pop->next;
		if (!queue->head)
			queue->tail = NULL;
		free(pop);
		return player;
	}
	return NULL;	
}

void getPlayers(Queue *queue, int n) {
	int i;
	for (i = 0; i < n; i++)
		pushPlayer(queue, createPlayer());
}

void printPoints(Queue *queue) {
	NodeQ *current;
	for (current = queue->head; current; current = current->next)
		printf("%d\n", playerPoints(current->player));
}

void freeQueue(Queue *queue) {
	Player *current;
	/* Percorrimento da lista para liberacao de cada no */
	while (queue->head) {
		current = popPlayer(queue);
		freePlayer(current);
	}
	free(queue);
}