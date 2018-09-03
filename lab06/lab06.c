#include <stdio.h>
#include <stdlib.h>
#include "universidade.h"

int main() {
	
	/* Variaveis de contagem */	
	int i, j;
	/* Variaveis de quantidade */
	int n_professores, n_alunos, n_disciplinas;
	double nota_min, nota_max;
	/* Variaveis buffer */
	char nome[MAX_NOME], sobrenome[MAX_NOME], disciplina[MAX_CODIGO];
	double salario, nota;
	/* Vetores de registros */
	p_professor *profs;
	p_aluno *alunos;

	/* Leitura + criacao dos registros de professores */
	scanf("%d", &n_professores);
	profs = (p_professor *) malloc(n_professores * sizeof(Professor));

	for (i = 0; i < n_professores; i++) {
		scanf("%s %s %lf %s", nome, sobrenome, &salario, disciplina);
		profs[i] = criarProfessor(nome, sobrenome, salario, disciplina);
	}

	/* Leitura + criacao dos registros de alunos */
	scanf("%d", &n_alunos);
	alunos = (p_aluno *) malloc(n_alunos * sizeof(Aluno));

	for (i = 0; i < n_alunos; i++) {
		
		scanf("%s %s", nome, sobrenome);
		alunos[i] = criarAluno(nome, sobrenome);

		scanf("%d", &n_disciplinas);

		for (j = 0; j < n_disciplinas; j++) {
			scanf("%s %lf", disciplina, &nota);
			adicionarDisciplina(alunos[i], disciplina, nota);
		}
	}

	/* Impressao dos resultados + liberacao de memoria alocada */
	for (i = 0; i < n_professores; i++) {

		obterNotasExtremas(alunos, n_alunos, profs[i]->disciplina, &nota_min, &nota_max);
		reajusteSalario(profs[i], (nota_min+nota_max)/2);
		imprimirProfessor(profs[i]);
		destruirProfessor(profs[i]);
	}
	free(profs);

	for (i = 0; i < n_alunos; i++)
		destruirAluno(alunos[i]);
	free(alunos);

	return 0;
}