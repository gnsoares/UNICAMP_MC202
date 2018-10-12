#ifndef NUMERO_ASTRONOMICO_H
#define NUMERO_ASTRONOMICO_H

/* Interface de um tipo abstrato de dados que representa numeros astronomicos;
 	* Usa LISTAS CIRCULARES DUPLAMENTE LIGADAS para guarda-los;
 	* Cada no da lista representa um algarismo do numero;
 	* O ponteiro para a lista de algarismos sempre para o PRIMEIRO algarismo;
 */

/* Estrutura que representa um algarismo de um numero astronomico */
typedef struct node {
	int digit;
	struct node *next, *prev;
} Node;

typedef Node * pNode;

/* Funcao que cria uma lista dos algarismos de um numero astronomico vazia
 * e retorna o endereco dessa lista */ 
pNode createAstro();

/* Funcao que le do teclado uma serie de caracteres numericos em uma mesma linha
 * e os guarda em uma lista dos algarismos de um numero astronomico e retorna o
 * endereco dessa lista
 */
pNode readAstro();

/* Funcao que recebe os enderecos de duas listas de algarismos de numeros astronomicos
 * e retorna o endereco de uma lista com a soma dos dois numeros */
pNode sumAstro(pNode a, pNode b);

/* Funcao que recebe o endereco de uma lista de algarismos de um numero astronomico
 * e um valor a ser incluido na primeira posicao dela. Retorna o endereco de uma nova
 * lista com esse valor adicionado */
pNode pushAstro(pNode a, int x);

/* Funcao que recebe o endereco de uma lista de algarismos de um numero astronomico
 * e imprime os seus algarismos em ordem */
void printAstro(pNode a);

/* Funcao que libera o espaco alocado por uma lista de algarismos de um numero astronomico */
void freeAstro(pNode a);

#endif