#include <stdio.h>

#define MAX_LENGTH 100

int lenString(char str[]) {
	/* Funcao que retorna o tamanho de uma string */
	int i = 0;
	for (i = 0; str[i] != '\0'; i++);
	return i;
}

int compString(char str1[], char str2[]) {
	/* Funcao que compara duas strings;
	 * Retorna 0 caso alguma diferenca seja encontrada;
	 * Retorna 1 caso contrario;
	 */
	int i = 0;
	if (lenString(str1) != lenString(str2))
		return 0;
	for (i = 0; str1[i] != '\0'; i++)
		if (str1[i] != str2[i])
			return 0;
	return 1;
}

void catString(char str1[], char str2[]) {
	/* Funcao que concatena a string 1 com a string 2 */
	int i = 0, size = 0;
	size = lenString(str1);
	for (i = 0; str2[i] != '\0'; i++)
		str1[size + i] = str2[i];
	str1[size + i] = '\0';
}

void subString(char str[], int pos, int size) {
	/* Funcao que substitui uma string por uma substring dela;
	 * Recebe a posicao inicial e o tamanho da substring e
	 * altera a string original;
	 */
	int i = 0;
	for (i = 0; i < size; i++)
		str[i] = str[pos + i];
	str[i] = '\0';
}

int main() {

	int argPos, argTam;
	char buffer[MAX_LENGTH], command[MAX_LENGTH], argS[MAX_LENGTH];

	/* Inicializacao do buffer vazio */
	buffer[0] = '\0';

	while (1) {
		scanf("%s", command);

		/* Comando CONCATENAR */
		if (compString(command, "CAT")) {
			scanf("%s", argS);
			catString(buffer, argS);
			printf("%s\n", buffer);

		/* Comando COMPARAR */
		} else if (compString(command, "CMP")) {
			scanf("%s", argS);
			if (compString(buffer, argS)) {
				printf("IGUAL\n");
			} else {
				printf("DIFERENTE\n");
			}

		/* Comando SUBSTITUIR */
		} else if (compString(command, "SUB")) {
			scanf("%d %d", &argPos, &argTam);
			subString(buffer, argPos, argTam);
			printf("%s\n", buffer);

		/* Comando TERMINAR */	
		} else if (compString(command, "END")) {
			break;
		}
	}
		
	return 0;
}
