#include <stdio.h>

#define MAX_ORDER 312

void getArrayInt(int arr[], int size) {
	/* Funcao que le do teclado valores
	 * inteiros e os guarda em um vetor;
	 */

	int i = 0;
	for (i = 0; i < size; i++)
		scanf("%d", &arr[i]);
}

void getMatrixDouble(double mat[][MAX_ORDER], int size) {
	/* Funcao que le do teclado valores
	 * flutuantes e os guardas em uma
	 * matriz quadrada (mat);
	 */

	int i = 0, j = 0;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++)
			scanf("%lf", &mat[i][j]);
	}
}

void permutationMatrix(int arr[], int mat[][MAX_ORDER], int size) {
	/* Funcao que obtem uma matriz quadrada
	 * de permutacao (mat) a partir de um
	 * vetor (arr) que e uma representacao
	 * reduzida da matriz;
	 */

	int i = 0, j = 0;	/* Variaveis de contagem */

	/* Para cada posicao da matriz e verificado
	 * se na mesma coluna do vetor arr estiver o
	 * valor da linha atual;
	 * Caso verdadeiro, essa posicao recebe 1;
	 * Caso contrario, recebe 0;
	 */
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (arr[j] == i + 1) {
				mat[i][j] = 1;
			} else {
				mat[i][j] = 0;
			}
		}
	}
}

void getPermutation(int mat1[][MAX_ORDER], double mat2[][MAX_ORDER], double mat3[][MAX_ORDER], int size) {
	/* Funcao que obtem a matriz permutada (mat3)
	 * de uma matriz quadrada (mat2) a partir de
	 * uma matriz de permutacao (mat1). Todas do
	 * mesmo tamanho;
	 */

	int i = 0, j = 0, k = 0;	/* Variaveis de contagem */

	/* Inicializacao da matriz resultado */
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			mat3[i][j] = 0;
		}
	}

	/* Realizacao da multiplicacao de matrizes */
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			for (k = 0; k < size; k++) {
				mat3[i][j] += (double) mat1[i][k] * mat2[k][j];
			}
		}
	}
}

void printMatrixDouble(double mat[][MAX_ORDER], int size) {
	/* Funcao que imprime uma matriz quadrada (mat)
	 * com seus valores separados por espacos;
	 */

	int i = 0, j = 0;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size - 1; j++)
			printf("%.1f ", mat[i][j]);
		printf("%.1f", mat[i][j]);
		printf("\n");
	}
}

int main() {
	
	int n;		/* Ordem da matriz quadrada */
	int vectorP[MAX_ORDER];	/* Representacao reduzida da matriz permutacao */
	int matrixA[MAX_ORDER][MAX_ORDER]; /* Matriz permutacao */
	double matrixB[MAX_ORDER][MAX_ORDER]; /* Matriz a ser permutada */
	double matrixAB[MAX_ORDER][MAX_ORDER];	/* Matriz resultado */

	/* Leitura da ordem da matriz */
	scanf("%d", &n);

	/* Leitura da representacao da matriz permutacao */
	getArrayInt(vectorP, n);

	/* Leitura da matriz a ser permutada */
	getMatrixDouble(matrixB, n);

	/* Obtencao da matriz permutacao */
	permutationMatrix(vectorP, matrixA, n);

	/* Obtencao da matriz permutada */
	getPermutation(matrixA, matrixB, matrixAB, n);

	/* Impressao da matriz permutada */
	printMatrixDouble(matrixAB, n);

	return 0;
}