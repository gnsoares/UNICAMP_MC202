#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 30

typedef struct {
	char name[MAX_NAME_LENGTH];
	int phoneNo;
} client;

client clientCreate(char *name, int number) {
	/* Funcao que inicializa um cliente */

	client c;

	strcpy(c.name, name);
	c.phoneNo = number;

	return c;
}

int clientMin(client *list, int beg, int end) {
	/* Funcao que encontra a posicao em um vetor
	 * de clientes do cliente com o menor numero
	 * de telefone
	 */

	int i;
	int min = beg;

	for (i = beg + 1; i <= end; i++)
		if (list[i].phoneNo < list[min].phoneNo)
			min = i;

	return min;
}

void clientCopy(client *list1, client *list2, int n) {
	/* Funcao que copia todo o conteudo de um vetor de
	 * clientes list2 de n elementos para outro vetor
	 * list1
	 */

	int i;

	for (i = 0; i < n; i++) {
		strcpy(list1[i].name, list2[i].name);
		list1[i].phoneNo = list2[i].phoneNo;
	}
}

void clientSelectionSort(client *list, int n) {
	/* Funcao que ordena um vetor de clientes de
	 * tamanho n baseado no numero de telefone de
	 * cada elemento
	 */

	int i;
	int min;
	client aux;

	for (i = 0; i < n; i++) {
		min = clientMin(list, i, n - 1);
		aux = list[i];
		list[i] = list[min];
		list[min] = aux;
	}
}

void clientWinner(client *list, int k) {
	/* Funcao que imprime o nome e o numero do telefone do cliente k sorteado */
	printf("%s %d\n", list[k - 1].name, list[k - 1].phoneNo);
}

int main() {

	int n; /* numero de elementos do vetor de clientes */
	int nMax; /* tamanho maximo do vetor de clientes */
	char name[MAX_NAME_LENGTH]; /* buffer dos nomes */
	int number; /* buffer dos numeros de telefone */
	client *list, *aux; /* vetores que guardam os clientes */

	/* Inicializacao das variaveis */
	n = 0;
	nMax = 4 * sizeof(client);
	list = malloc(nMax);
	aux = malloc(nMax);

	/* Loop de leitura dos clientes */
	while (1) {

		scanf("%s %d", name, &number);

		/* Condicao de encerramento da execucao */
		if (!strcmp(name, "fim")) {
			clientSelectionSort(list, n);
			clientWinner(list, number);
			break;
		}

		/* Realocacao de memoria para o vetor */
		if (n * sizeof(client) == nMax) {
			nMax *= 2;
			clientCopy(aux, list, n);
			list = malloc(nMax);
			clientCopy(list, aux, n);
			aux = malloc(nMax);
		}

		list[n] = clientCreate(name, number);
		n++;
	}

	/* Liberacao do espaco alocado */
	free(list);
	free(aux);

	return 0;
}