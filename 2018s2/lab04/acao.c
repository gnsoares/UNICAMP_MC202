#include "acao.h"
#include <stdio.h>
#include <string.h>

double valor_final(acao a) {
	/* Funcao que calcula o valor final do investimento
	 * em uma acao a baseado no valor investido e nas
	 * variacoes da acao
	 */

	int i;
	double resultado = a.investimento;

	for (i = 0; i < a.n_variacoes; i++) {
		resultado *= 1 + (a.variacoes[i]/100);
	}

	return resultado;
}

acao criar_acao(char *nome, double investimento) {
	/* Funcao que inicializa uma acao vazia */

	acao a;

	strcpy(a.nome, nome);
	a.investimento = investimento;
	a.n_variacoes = 0;

	return a;
}

acao adicionar_variacao(acao a, double variacao) {
	/* Funcao que adiciona uma variacao percentual a acao a */

	a.variacoes[a.n_variacoes] = variacao;
	a.n_variacoes++;

	return a;
}

void reportar_acao(acao a) {
	/* Funcao que imprime na tela o resultado do investimento em um acao a */

	printf("%s %.2f ", a.nome, valor_final(a));
	if (valor_final(a) > a.investimento)
		printf("GANHO\n");
	else
		printf("PERDA\n");
}