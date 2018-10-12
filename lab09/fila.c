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
	NodeQ *currentNode = queue->head; /* Variavel de percorrimento */

	/* Percorrimento da lista para liberacao de cada no */
	while (queue->head) {
		queue->head = queue->head->next;
		freePlayer(currentNode->player);
		free(currentNode);
		currentNode = queue->head;
	}
	free(queue);
}

int doAllStand(Queue *queue) {
	NodeQ * currentNode = queue->head;

	/* Se no minimo um jogador estiver em "Hit", retornar 0 */
	while (currentNode) {
		if (currentNode->player->state == 'H')
			return 0;
		currentNode = currentNode->next;
	}
	/* Caso todos estiverem em "Stand", retornar 1 */
	return 1;
}