/* MC202 Estruturas de Dados - Laboratorio 07: Labirinto
 * 	Nome: Gustavo Nascimento Soares
 * 	RA: 217530
 * 	Programa que le um labirinto do teclado e imprime a sua
 * 	saida usando um algoritmo de backtracking para encontra-la
 */

#include <stdio.h>
#include <stdlib.h>

void getLineMaze(char *line, int n) {
	/* Funcao que le do teclado e guarda em uma linha
	 * de uma matriz uma linha de um labirinto;
	 *
	 * Recebe como parametro:
	 	* o endereco para a linha,
	 	* o numero de elementos dessa linha;
	 */
	int i;
	for (i = 0; i < n; i++)
		scanf(" %c", &line[i]);
}

int isValid(char **maze, int lt, int ct, int le, int ce, char **ans) {
	/* Funcao que verifica se um movimento
	 * dentro de um labirinto e valido;
	 *
	 * Recebe como parametro:
	 	* o endereco da matriz do labirinto,
	 	* as dimensoes do labirinto,
	 	* as coordenadas de entrada,
	 	* o endereco da matriz de resposta;
	 *
	 * Verifica as seguintes condicoes:
	 */
	if (
		le < 0 || ce < 0 || le >= lt || ce >= ct || /* Saiu do labirinto */
		maze[le][ce] == 'X' || /* Encontrou um obstaculo */
		ans[le][ce] == '*' /* Movimento repetido */
	)
		return 0;

	/* Caso contrario: movimento valido */
	return 1;
}

int ansMaze(char **maze, int lt, int ct, int le, int ce, int ls, int cs, char **ans) {
	/* Funcao que acha a saida de um labirinto a partir
	 * de um algoritmo de backtracking;
	 *
	 * Recebe como parametro:
	 	* o endereco da matriz do labirinto,
	 	* as dimensoes do labirinto,
	 	* as coordenadas de entrada e de saida,
	 	* o endereco da matriz de resposta;
	 */

	/* Se o movimento for valido, faca: */
	if (isValid(maze, lt, ct, le, ce, ans)) {

		/* Supor movimento valido */
		ans[le][ce] = '*';

		if (le == ls && ce == cs) /* Saida encontrada */
			return 1;
		/* Movimentos: */
		if (ansMaze(maze, lt, ct, le - 1, ce, ls, cs, ans)) /* Para cima */
			return 1;
		if (ansMaze(maze, lt, ct, le, ce - 1, ls, cs, ans)) /* Para esquerda */
			return 1;
		if (ansMaze(maze, lt, ct, le + 1, ce, ls, cs, ans)) /* Para baixo */
			return 1;
		if (ansMaze(maze, lt, ct, le, ce + 1, ls, cs, ans)) /* Para direita */
			return 1;

		ans[le][ce] = ' '; /* Sem saida */
	}

	 /* Caso contrario: movimento invalido */
	return 0;
}

int main() {

	int i, j; /* Variaveis de contagem */
	int lt, ct, le, ce, ls, cs; /* Dimensoes e coordenadas do labirinto */
	char **maze, **ans; /* Enderecos de matrizes do labirinto e da resposta */

	/* Leitura + alocacao do labirinto */
	scanf("%d %d %d %d %d %d", &lt, &ct, &le, &ce, &ls, &cs);

	maze = malloc(lt * sizeof(char *));	
	if (maze == NULL)
		exit(1);

	for (i = 0; i < lt; i++) {
		maze[i] = malloc(ct * sizeof(char));
		if (maze[i] == NULL)
			exit(1);
		getLineMaze(maze[i], ct);
	}

	/* Inicializacao + alocacao da matriz resposta */
	ans = malloc(lt * sizeof(char *));

	if (ans == NULL)
		exit(1);

	for (i = 0; i < lt; i++) {
		ans[i] = malloc(ct * sizeof(char));
		if (ans[i] == NULL)
			exit(1);
		for (j = 0; j < ct; j++)
			ans[i][j] = ' ';
	}

	/* Se o labirinto tiver saida, imprima a saida */
	if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans))
		for (i = 0; i < lt; i++) {
			for (j = 0; j < ct; j++)
				printf("%c", ans[i][j]);
			printf("\n");
		}

	/* Liberacao do espaco de memoria alocado */
	for (i = 0; i < lt; i++) {
		free(maze[i]);
		free(ans[i]);
	}
	free(maze);
	free(ans);

	return 0;
}