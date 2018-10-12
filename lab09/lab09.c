#include <stdio.h>
#include <string.h>
#include "pilha.h"
#include "jogador.h"
#include "fila.h"

int main() {
	
	int i;	/* Variavel de contagem */
	char current[MAX_CARD_LENGTH]; /* Buffer de leitura de strings OU temporaria para cartas */
	int nCards, nPlayers;
	NodeQ *currentPlayerNode; /* Variavel de percorrimento da lista de jogadores */
	Stack *cards = createStack(); /*Pilha de cartas */
	Queue *players = createQueue(); /* Fila de jogadores */

	/* Leitura e preenchimento inicial das estruturas */
	scanf("%d %d", &nCards, &nPlayers);
	getCards(cards, nCards);
	getPlayers(players, nPlayers + 1);

	/* Primeiras 2 rodadas de compra de cartas */
	currentPlayerNode = players->head;
	for (i = 0; i < 2 * (nPlayers + 1); i++) {

		if (!currentPlayerNode)
			currentPlayerNode = players->head;

		/* Remocao da carta da pilha geral para inclusao na mao do jogador */
		popCard(cards, current);
		pushCard(currentPlayerNode->player->hand, current);

		currentPlayerNode = currentPlayerNode->next;
	}

	/* Rodadas seguintes em que os jogadores escolhem se compram ou nao mais cartas */
	strcpy(current, "");
	currentPlayerNode = players->head;
	while (strcmp(current, "#")) {

		/* Se nenhum jogador for comprar mais cartas, sair do loop */
		if (doAllStand(players))
			break;

		/* Se tiver percorrido todos os jogadores, voltar ao primeiro */
		if (!currentPlayerNode)
			currentPlayerNode = players->head;

		/* Verificacao se o jogador atual pode ou nao jogar */	
		if (playerPoints(currentPlayerNode->player) > 20) {
			setState(currentPlayerNode->player, 'S');
		}
		if (currentPlayerNode->player->state == 'S') {
			currentPlayerNode = currentPlayerNode->next;
			continue;
		}

		/* Leitura do comando */
		scanf("%s", current);

		/* Caso o comando nao seja nenhum desses, o dealer adicionou uma carta a pilha */
		if (
			strcmp(current, "S") &&
			strcmp(current, "H") &&
			strcmp(current, "#")
		) {
			pushCard(cards, current);
			continue;
		}

		/* Atualizacao do estado do jogador atual */
		setState(currentPlayerNode->player, current[0]);

		/* Se o estado for "Hit", comprar carta */
		if (currentPlayerNode->player->state == 'H') {
			popCard(cards, current);
			pushCard(currentPlayerNode->player->hand, current);
		}

		currentPlayerNode = currentPlayerNode->next;		
	}

	/* Impressao da pontuacao final */	
	printPoints(players);

	/* Liberacao do espaco alocado */
	freeStack(cards);
	freeQueue(players);

	return 0;
}