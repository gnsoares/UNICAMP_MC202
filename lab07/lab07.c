#include <stdio.h>
#include <stdlib.h>

void getLineMaze(char *line, int n) {
	int i;
	for (i = 0; i < n; i++)
		scanf(" %c", &line[i]);
}

int isValid(char **maze, int lt, int ct, int le, int ce, char **ans) {
	if (
		le < 0 ||
		ce < 0 ||
		le >= lt ||
		ce >= ct ||
		maze[le][ce] == 'X' ||
		ans[le][ce] == '*'
	)
		return 0;
	return 1;
}

int ansMaze(char **maze, int lt, int ct, int le, int ce, int ls, int cs, char **ans) {

	if (isValid(maze, lt, ct, le, ce, ans)) {

		ans[le][ce] = '*';

		if (le == ls && ce == cs)
			return 1;
		if (ansMaze(maze, lt, ct, le - 1, ce, ls, cs, ans))
			return 1;
		if (ansMaze(maze, lt, ct, le, ce - 1, ls, cs, ans))
			return 1;
		if (ansMaze(maze, lt, ct, le + 1, ce, ls, cs, ans))
			return 1;
		if (ansMaze(maze, lt, ct, le, ce + 1, ls, cs, ans))
			return 1;

		ans[le][ce] = ' ';
	}

	return 0;
}

int main() {

	int i, j;
	int lt, ct, le, ce, ls, cs;
	char **maze, **ans;

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

	/* Inicializacao da matriz resposta */
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

	
	if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans))
		for (i = 0; i < lt; i++) {
			for (j = 0; j < ct; j++)
				printf("%c", ans[i][j]);
			printf("\n");
		}

	for (i = 0; i < lt; i++) {
		free(maze[i]);
		free(ans[i]);
	}
	free(maze);
	free(ans);

	return 0;
}