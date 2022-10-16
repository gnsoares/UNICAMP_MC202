#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

Stack * createStack() {
	Stack *new = malloc(sizeof(Stack));

	if (!new)
		exit(1);

	/* O topo nao aponta para nenhum no por ser uma pilha vazia */
	new->top = NULL;

	return new;
}

void pushCard(Stack *stack, char card[MAX_CARD_LENGTH]){
	NodeS *new = malloc(sizeof(NodeS));

	if (!new)
		exit(1);	

	strcpy(new->card, card);

	/* Se a pilha estiver vazia, esse sera o primeiro no;
	 * Senao, mover o topo atual;
	 */
	if (!stack->top)
		new->next = NULL;
	else
		new->next = stack->top;

	stack->top = new;
}

void getCards(Stack *stack, int n) {

	int i;
	char read[MAX_CARD_LENGTH];
	
	for (i = 0; i < n; i++) {
		scanf("%s", read);
		pushCard(stack, read);
	}
}

void popCard(Stack *stack, char card[MAX_CARD_LENGTH]){
	NodeS * pop;

	if (stack->top) {
		pop = stack->top;
		/* Copia e remocao da carta */
		strcpy(card, stack->top->card);
		stack->top = pop->next;

		/* Liberar o no porque ele nao sera mais usado */
		free(pop);
	}
}

void freeStack(Stack *stack) {
	/* Variavel temporaria apenas para chamada do pop */
	char placeholder[MAX_CARD_LENGTH];

	/* Percorrimento da pilha liberando cada no */
	while (stack->top)
		popCard(stack, placeholder);
	free(stack);
}
