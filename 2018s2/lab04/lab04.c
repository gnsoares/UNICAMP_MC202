#include "portfolio.h"
#include "acao.h"
#include <stdio.h>

int main() {
	
	/* Variaveis de contagem */	
	int i, j;
	/* Variaveis de quantidade */
	int n_acoes, n_var;
	/* Variaveis buffer */
	char nome_inv[MAX_SIZE_NAME], sobrenome_inv[MAX_SIZE_NAME], nome_acao[MAX_SIZE_NAME];
	double inv, var;
	acao a;
	/* Registro do portfolio */
	portfolio p;
	

	/* Leitura + criacao do portfolio */
	scanf("%s %s", nome_inv, sobrenome_inv);
	p = criar_portfolio(nome_inv, sobrenome_inv);

	scanf("%d", &n_acoes);

	for (i = 0; i < n_acoes; i++) {
		/* Loop de preenchimento do portfolio */
		scanf("%s %lf %d", nome_acao, &inv, &n_var);
		a = criar_acao(nome_acao, inv);

		for (j = 0; j < n_var; j++) {
			/* Loop de preenchimento de cada acao */
			scanf("%lf", &var);
			a = adicionar_variacao(a, var);
		}

		p = adicionar_acao(p, a);
	}

	/* Impressao dos resultados */
	criar_relatorio(p);

	return 0;
}