#ifndef JOGADOR_H
#define JOGADOR_H

/* Interface de uma estrutura JOGADOR:
	* Cada jogador tem um estado: "Hit" ou "Stand", representado por caracter;
	* Cada jogador tem sua pilha de cartas que representa sua mao;
 */

#include "pilha.h"

typedef struct {
	char state;
	Stack *hand;
} Player;

/* Funcao que cria um novo jogador com a mao vazia e retorna o seu endereco */
Player * createPlayer();

/* Funcao que atualiza o estado de um jogador */
void setState(Player *player, char state);

/* Funcao que devolve o numero de pontos de um jogador baseado na sua mao */
int playerPoints(Player *player);

/* Funcao que libera o espaco alocado por um jogador */
void freePlayer(Player *player);

#endif