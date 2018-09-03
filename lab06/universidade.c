#include "universidade.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

p_professor criarProfessor(char nome[], char sobrenome[], double salario, char disciplina[]) {

	p_professor p;

	p = (p_professor) malloc(sizeof(Professor));

	strcpy(p->nome, nome);
	strcpy(p->sobrenome, sobrenome);
	p->salario = salario;
	strcpy(p->disciplina, disciplina);

	return p;
}

void destruirProfessor(p_professor professor) {
	free(professor);
}

p_aluno criarAluno(char nome[], char sobrenome[]) {

	p_aluno a;

	a = (p_aluno) malloc(sizeof(Aluno));

	strcpy(a->nome, nome);
	strcpy(a->sobrenome, sobrenome);
	a->qtd_disciplinas = 0;

	return a;
}

void adicionarDisciplina(p_aluno aluno, char disciplina[], double nota) {

	strcpy(aluno->disciplinas[aluno->qtd_disciplinas], disciplina);
	aluno->notas[aluno->qtd_disciplinas] = nota;
	aluno->qtd_disciplinas++;
}

void destruirAluno(p_aluno aluno) {
	free(aluno);
}

void obterNotasExtremas(p_aluno alunos[], int qtd_alunos, char disciplina[], double *nota_min, double *nota_max) {

	int i, j;
	int boolDisc; /* Variavel para verificacao se o aluno pertence a disciplina */

	*nota_min = 10;
	*nota_max = 0;

	for (i = 0; i < qtd_alunos; i++) {

		boolDisc = 0;

		/* Determinacao se o aluno i participa ou nao da disciplina;
		 * Se sim, qual a posicao esta sua nota nela;
		 */
		for (j = 0; j < alunos[i]->qtd_disciplinas; j++) {
			if (!strcmp(alunos[i]->disciplinas[j], disciplina)) {
				boolDisc = 1;
				break;
			}
		}
		
		/* Determinacao das notas maxima e minima */
		if (boolDisc) {
			if (alunos[i]->notas[j] < *nota_min)
				*nota_min = alunos[i]->notas[j];
			if (alunos[i]->notas[j] > *nota_max)
				*nota_max = alunos[i]->notas[j];
		}
	}
}

void reajusteSalario(p_professor professor, double media_notas) {

	if (media_notas == 10)
		professor->salario *= 1.15;
	else if (media_notas >= 9)
		professor->salario *= 1.10;
	else if (media_notas >= 8.5)
		professor->salario *= 1.05;
}

void imprimirProfessor(p_professor professor) {
	printf("%s %s %.2f\n", professor->nome, professor->sobrenome, professor->salario);
}

