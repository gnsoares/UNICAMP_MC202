#ifndef FILA_H
#define FILA_H

/* Interface de uma FILA DE JOGADORES:
	* Cada jogador e representado por uma estrutura;
	* Cada no aponta apenas para o seu proximo;
	* A fila aponta para o seu inicio e para o seu fim;
 */

#include "jogador.h"

typedef struct nodeQ {
	Player *player;
	struct nodeQ *next;
} NodeQ;

typedef struct {
	NodeQ *head, *tail;
} Queue;

/* Funcao que cria uma fila vazia e retorna o seu endereco */
Queue * createQueue();

/* Funcao que copia os dados da queue2 para a queue1 */
void copyQueue(Queue *queue1, Queue *queue2);

/* Funcao que adiciona um jogador no fim da fila */
void pushPlayer(Queue *queue, Player *player);

/* Funcao que retira um jogador do inicio da fila */
Player * popPlayer(Queue *queue);

/* Funcao que inclui n jogadores em uma fila */
void getPlayers(Queue *queue, int n);

/* Funcao que imprime a pontuacao de todos os jogadores em uma fila */
void printPoints(Queue *queue);

/* Funcao que libera o espaco alocado por uma fila */
void freeQueue(Queue *queue);

#endif