#ifndef __VETOR_H__
#define __VETOR_H__

/*
 * interface da estrutura vetor que representa
 * um vetor de duas dimensões
 */

typedef struct vetor{
	double x;
	double y;
} vetor;

/**
  * aloca um vetor composto por `x` e `y`
  */
vetor* vetor_criar(double x, double y);

/*
 * libera o espaço de memória alocado pela função
 * `vetor_criar`
 */
void vetor_destruir(vetor* v);

/*
 * soma o vetor `a` e o vetor `b` e armazena o resultado em `c`
 */
void vetor_somar(vetor const* a, vetor const* b, vetor* c);

#endif
