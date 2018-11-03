#include <stdio.h>

void printArrayInt(int arr[], int size) {
	/* Funcao que imprime os valores
	 * de um vetor de inteiros;
	 * Recebe como parametros o vetor a
	 * ser impresso e o seu tamanho;
	 */

	int i = 0;
	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);	
	}
	printf("\n");
}

void getSets(int arr1[], int arr2[], int size1, int size2) {
	/* Funcao que le do teclado os valores
	 * dos conjuntos A e B e os guarda em
	 * em dois vetores;
	 * Recebe como parametro os vetores em
	 * que os valores serao guardados e o 
	 * numero de elementos de cada conjunto;
	 */

	int i = 0;
	for (i = 0; i < size1; i++) {
		scanf("%d", &arr1[i]);
	}
	for (i = 0; i < size2; i++) {
		scanf("%d", &arr2[i]);
	}
}

int isIn(int arr[], int key, int size) {
	/* Funcao que veririfica se um determinado
	 * valor esta presente em um vetor;
	 * Tem como argumentos o vetor, a chave e 
	 * o tamanho do vetor;
	 * Retorna 1 caso verdadeiro e 0 caso falso;
	 */

	int i = 0;
	for (i = 0; i < size; i++) {
		if (arr[i] == key) 
			return 1;
	}
	return 0;
}

void SymmetricDifference(int arr1[], int arr2[], int* pointtoarr3, int size1, int size2, int* pointtosize3) {
	/* Funcao que executa a operacao diferenca simetrica
	 * de 2 vetores;
	 * Tem como argumentos os vetores a serem operados
	 * (1 e 2) e seus respectivos tamanhos, alem de um
	 * ponteiro para o vetor que guarda a solucao (3) e
	 * um ponteiro que guarda o tamanho da solucao;
	 * Altera um vetor de inteiros com o conjunto
	 * solucao e o seu tamanho;
	 */
	
	int i = 0, j = 0, k = 0;

	/* Para cada valor de cada vetor e verificada
	 * a sua presenca no outro vetor;
	 * Caso falso, esse valor e adicionado ao vetor
	 * que contem o conjunto solucao;
	 */

	while (j < size1) {
		if (!(isIn(arr2, arr1[j], size2))) {
			*pointtoarr3 = arr1[j];
			pointtoarr3++;
			i++;
		}
		j++;
	}
	while (k < size2) {
		if (!(isIn(arr1, arr2[k], size1))) {
			*pointtoarr3 = arr2[k];
			pointtoarr3++;
			i++;
		}
		k++;
	}

	/* Definicao do tamanho do conjunto solucao */
	*pointtosize3 = i;
}

int main() {

	int lenA = 0, lenB = 0, lenS = 0;     /* variaveis que indicam o numero de elementos dos conjuntos */
	int a[40], b[40], s[80];              /* vetores que guardam os conjuntos */

	/* Leitura dos tamanhos dos conjuntos */
	scanf("%d %d", &lenA, &lenB);

	/* Obtencao dos valores dos conjuntos */
	getSets(a, b, lenA, lenB);

	/* Definicao do conjunto solucao da diferenca simetrica */
	SymmetricDifference(a, b, s, lenA, lenB, &lenS);

	/* Impressao do resultado */
	printArrayInt(s, lenS);

	return 0;
}
