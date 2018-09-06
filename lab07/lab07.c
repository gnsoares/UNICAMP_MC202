#include <stdio.h>
#include <stdlib.h>

void getLineMaze(char *line, int n) {
	int i;
	for (i = 0; i < n; i++)
		scanf(" %c", line + i);
}

int isValid(char **maze, int lt, int ct, int le, int ce) {
	if (
		le < 0 ||
		ce < 0 ||
		le >= lt ||
		ce >= ct ||
		maze[le][ce] == 'X'
		)
		return 0;
	return 1;
}

int ansMaze(char **maze, int lt, int ct, int le, int ce, int ls, int cs, char **ans, char mov) {
	if (mov == 'l') {
		ce -= 1;
	} else if (mov == 'r') {
		ce += 1;
	} else if (mov == 'u') {
		le -= 1;
	} else if (mov == 'd') {
		le += 1;
	}

	if (isValid(maze, lt, ct, le, ce)) {

		ans[le][ce] = '*';

		if (le == ls && ce == cs)
			return 1;

		if (mov == 's') {
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'l'))
				return 1;
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'r'))
				return 1;
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'u'))
				return 1;
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'd'))
				return 1;
		} else if (mov == 'l') {
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'l'))
				return 1;
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'u'))
				return 1;
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'd'))
				return 1;
		} else if (mov == 'r') {
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'r'))
				return 1;
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'u'))
				return 1;
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'd'))
				return 1;
		} else if (mov == 'u') {
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'r'))
				return 1;
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'l'))
				return 1;
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'u'))
				return 1;
		} else if (mov == 'd') {
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'r'))
				return 1;
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'l'))
				return 1;
			if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 'd'))
				return 1;
		}
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
	/*
	printf("%d %d %d %d %d %d\n", lt, ct, le, ce, ls, cs);

	for (i = 0; i < lt; i++) {
		for (j = 0; j < ct; j++) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
	*/
	if (ansMaze(maze, lt, ct, le, ce, ls, cs, ans, 's'))
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