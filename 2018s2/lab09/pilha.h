#ifndef PILHA_H
#define PILHA_H

#define MAX_CARD_LENGTH 3

/* Interface de uma PILHA DE CARTAS:
	* Cada carta e representada por uma string;
	* Cada no aponta apenas para o seu proximo;
 */

typedef struct nodeS {
	char card[MAX_CARD_LENGTH];
	struct nodeS *next;
} NodeS;

typedef struct {
	NodeS *top;
} Stack;

/* Funcao que cria uma pilha vazia e retorna o seu endereco */
Stack * createStack();

/* Funcao que empilha uma carta em uma pilha */
void pushCard(Stack *stack, char card[MAX_CARD_LENGTH]);

/* Funcao que le do teclado uma serie de cartas e as empilha */
void getCards(Stack *stack, int n);

/* Funcao que desempilha uma carta de uma pilha e a guarda em uma string passada como parametro */
void popCard(Stack *stack, char card[MAX_CARD_LENGTH]);

/* Funcao que libera o espaco alocado por uma pilha de cartas */
void freeStack(Stack *stack);

#endif