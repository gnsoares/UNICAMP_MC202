#include "portfolio.h"
#include <stdio.h>
#include <string.h>

portfolio criar_portfolio(char *nome, char *sobrenome) {
	/* Funcao que inicializa um portfolio vazio */

	portfolio p;

	strcpy(p.nome, nome);
	strcpy(p.sobrenome, sobrenome);
	p.n_acoes = 0;

	return p;
}

portfolio adicionar_acao(portfolio p, acao a) {
	/* Funcao que que adiciona uma acao a ao portfolio p */

	p.acoes[p.n_acoes] = a;
	p.n_acoes++;

	return p;
}

void criar_relatorio(portfolio p) {
	/* Funcao que imprime na tela os resultados dos investimentos
	 * nas acoes do portfolio p
	 */

	int i;
	
	printf("Relatorio de %s %s\n", p.nome, p.sobrenome);
	for (i = 0; i < p.n_acoes; i++)
		reportar_acao(p.acoes[i]);
}