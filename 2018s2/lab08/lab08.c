#include <stdio.h>
#include "numero_astronomico.h"

int main() {
	
	pNode buffer, operand1, operand2;
	char command = '\0';

	/* Inicializacao do buffer com 0 */
	buffer = createAstro();
	buffer = pushAstro(buffer, 0);

	while (command != '#') {

		scanf("%c", &command);

		if (command == '+') {
			/* Execucao da soma */
			operand1 = buffer;
			operand2 = readAstro();
			
			buffer = sumAstro(operand1, operand2);
			printAstro(buffer);

			/* Os operandos nao serao mais usados */
			freeAstro(operand1);
			freeAstro(operand2);
		}
	}
	/* Liberacao do buffer */
	freeAstro(buffer);

	return 0;
}