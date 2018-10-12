#include <stdlib.h>
#include <string.h>
#include "jogador.h"

Player * createPlayer() {
	Player *new = malloc(sizeof(Player));

	if (!new)
		exit(1);

	/* Novos jogadores sempre comecam em "Hit" e tem mao vazia */
	new->state = 'H';
	new->hand = createStack();

	return new;
}

void setState(Player *player, char state) {
	/* Se nao for um jogador nulo, atualizar estado */
	if (player)
		player->state = state;
}

int playerPoints(Player *player) {
	NodeS *currentCard;
	int points = 0, hasA = 0;

	for (currentCard = player->hand->top; currentCard; currentCard = currentCard->next) {
		if (!strcmp(currentCard->card, "A")) {
			/* As inicia valendo 11 pontos */
			points += 11;
			hasA++;
		} else if (
			/* Conjunto de cartas de 10 pontos */
			!strcmp(currentCard->card, "10") ||
			!strcmp(currentCard->card, "V") ||
			!strcmp(currentCard->card, "D") ||
			!strcmp(currentCard->card, "R")
		) {
			points += 10;
		} else if ('1' < currentCard->card[0] && currentCard->card[0] <= '9') {
			/* Cartas numericas tem valor igual ao seu numero */
			points += currentCard->card[0] - '0';
		}
	}

	/* Se necessario, alterar o valor do As */
	while (hasA > 0 && points > 21) {
		points -= 10;
		hasA--;
	}

	return points;
}

void freePlayer(Player *player) {
	/* Liberacao da mao e do jogador */
	freeStack(player->hand);
	free(player);
}
