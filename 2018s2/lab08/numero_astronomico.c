#include <stdio.h>
#include <stdlib.h>
#include "numero_astronomico.h"

/* Funcoes auxiliares usadas apenas na implementacao 
 	* Ambas alteram a propria lista passada como parametro
 */

/* Funcao que remove zeros do inicio de uma lista de algarismos de um numero astronomico */
pNode removeZeros(pNode a);

/* Funcao que inverte os algarismos de um numero astronomico e retorna o endereco da lista invertida */
pNode reverseAstro(pNode a);

/* Implementacao das funcoes da interface */ 

pNode createAstro() {
	return NULL;
}

pNode readAstro() {
	char current = '\0'; /* variavel que guarda o caracter lido a cada iteracao da leitura */ 
	pNode new = createAstro(); /* nova lista a ser retornada */

	while (current != '\n') {
		scanf("%c", &current);

		/* Se o caracter lido for numerico, deve ser adicionado */
		if (current >= '0' && current <= '9')
			new = pushAstro(new, current - '0');
	}

	/* Como os algarismos foram adicionados na ordem inversa, inverter o numero */
	new = reverseAstro(new);
	/* Caso o numero tenha zeros na entrada, remove-los */
	new = removeZeros(new);

	return new;
}

pNode sumAstro(pNode a, pNode b) {
	pNode new = createAstro(); /* nova lista a ser retornada */
	pNode curA = a->prev; /* ponteiro para percorrer o numero a inversamente */
	pNode curB = b->prev; /* ponteiro para percorrer o numero b inversamente */
	int sum, carry = 0; /* variavel da soma e variavel do valor a ser carregado para a proxima soma */

	/* Se for recebida alguma lista vazia, retornar a outra */
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;

	/* Soma dos digitos ate que um dos numeros acabe */
	do {
		sum = curA->digit + curB->digit + carry;
		carry = sum/10;
		sum %= 10;

		new = pushAstro(new, sum);

		curA = curA->prev;
		curB = curB->prev;
	} while (curA != a->prev && curB != b->prev);

	/* Se a acabar mas b ainda tiver digitos a serem somados */
	if (curA == a->prev) {
		while (curB != b->prev) {
			sum = curB->digit + carry;
			carry = sum/10;
			sum %= 10;

			new = pushAstro(new, sum);

			curB = curB->prev;
		}
	}

	/* Se b acabar mas a ainda tiver digitos a serem somados */
	if (curB == b->prev) {
		while (curA != a->prev) {
			sum = curA->digit + carry;
			carry = sum/10;
			sum %= 10;

			new = pushAstro(new, sum);

			curA = curA->prev;		
		}
	}

	/* Se houver um digito ainda a ser carregado (resultado de uma soma > 9) */
	if (carry > 0)
		new = pushAstro(new, carry);

	return new;
}

pNode pushAstro(pNode a, int x) {
	pNode new = malloc(sizeof(Node));

	if (new == NULL)
		exit(1);

	new->digit = x;

	/* Se for recebida uma lista vazia, o no unico aponta para si proprio */
	if (a == NULL) {
		new->next = new;
		new->prev = new;
	/* Caso contrario, o novo e adicionado na primeira posicao */
	} else {
		new->next = a;
		new->prev = a->prev;
		a->prev->next = new;
		a->prev = new;
	}

	return new;
}

void printAstro(pNode a) {
	pNode current; /* ponteiro que percorre a lista a */

	for (current = a; current->next != a; current = current->next) {
		printf("%d", current->digit);
	}
	printf("%d\n", current->digit);	
}

void freeAstro(pNode a) {
	pNode current = a; /* ponteiro que percorre a lista a */
	pNode original = a; /* ponteiro que guarda o endereco original da lista */

	do {
		a = a->next;
		free(current);
		current = a;
	} while (current != original);
}

pNode removeZeros(pNode a) {
	pNode new = a;

	/* Caso o primeiro digito seja 0, apontar para o proximo */
	while (new->digit == 0) {
		new->next->prev = new->prev;
		new = new->next;
	}

	return new;
}

pNode reverseAstro(pNode a) {
	pNode new = createAstro();
	pNode current = a; /* ponteiro que percorre a lista a */

	/* Se for recebida uma lista vazia, retorna-la */
	if (current == NULL)
		return NULL;

	/* A partir do primeiro digito, cada digito e adicionado na primeira
	 * posicao disponivel do novo */
	for (current = a; current->next != a; current = current->next)
		new = pushAstro(new, current->digit);
	new = pushAstro(new, current->digit);

	/* O endereco da lista original nao sera mais usado */
	freeAstro(a);

	return new;
}