#include <stdio.h>
#include <string.h>
#include "pilha.h"
#include "jogador.h"
#include "fila.h"

int main() {
	
	int i;	/* Variavel de contagem */
	char current[MAX_CARD_LENGTH]; /* Buffer de leitura de strings OU temporaria para cartas */
	int nCards, nPlayers;
	Player *currentPlayer; /* Variavel de percorrimento da lista de jogadores */
	Stack *cards = createStack(); /*Pilha de cartas */
	Queue *players = createQueue(), *rotation = createQueue(); /* Filas de jogadores */

	/* Leitura e preenchimento inicial das estruturas */
	scanf("%d %d", &nCards, &nPlayers);
	getCards(cards, nCards);
	getPlayers(players, nPlayers + 1);
	copyQueue(rotation, players);

	/* Primeiras 2 rodadas de compra de cartas */
	for (i = 0; i < 2 * (nPlayers + 1); i++) {

		currentPlayer = popPlayer(rotation);
		/* Remocao da carta da pilha geral para inclusao na mao do jogador */
		popCard(cards, current);
		pushCard(currentPlayer->hand, current);

		/* Se o jogador ainda nao terminou suas
		 * jogadas, reincluir na rotacao
		 */
		if (currentPlayer->state == 'H' && playerPoints(currentPlayer) < 21)
			pushPlayer(rotation, currentPlayer);
	}

	/* Rodadas seguintes em que os jogadores escolhem se compram ou nao mais cartas */
	strcpy(current, "");
	while (strcmp(current, "#")) {

		/* Leitura do comando */
		scanf("%s", current);

		/* Caso o comando nao seja nenhum desses, o dealer adicionou uma carta a pilha */
		if (strcmp(current, "S")
		 && strcmp(current, "H")) {
			pushCard(cards, current);
			continue;
		}

		/* Desenfileiramento */
		currentPlayer = popPlayer(rotation);

		/* Se a rotacao foi esvaziada, receber proximo comando */
		if (!currentPlayer)
			continue;

		/* Atualizacao do estado do jogador atual */
		setState(currentPlayer, current[0]);

		/* Se o estado for "Hit", comprar carta */
		if (currentPlayer->state == 'H') {
			popCard(cards, current);
			pushCard(currentPlayer->hand, current);
		}

		/* Se o jogador ainda nao terminou suas
		 * jogadas, reincluir na rotacao
		 */
		if (currentPlayer->state == 'H' && playerPoints(currentPlayer) < 21)
			pushPlayer(rotation, currentPlayer);	
	}

	/* Caso o jogo termine antes da rotacao esvaziar */
	while(rotation->head)
		popPlayer(rotation);

	/* Impressao da pontuacao final */	
	printPoints(players);

	/* Liberacao do espaco alocado */
	freeStack(cards);
	freeQueue(players);
	freeQueue(rotation);

	return 0;
}