#ifndef __RETANGULO_H__
#define __RETANGULO_H__

#include "vetor.h"

typedef struct retangulo{
	vetor* sup_esq; // ponto superior esquerdo do retângulo
	vetor* inf_dir; // ponto superior direito do retângulo
}retangulo;

/*
 * aloca e inicializa um retângulo com os respectivos pontos
 * superior esquerdo e inferior direito p = (px, py), q = (qx, qy)
 */
retangulo* retangulo_criar(double px, double py, double qx, double qy);

/*
 * libera o espaço de memória alocado pela função
 * `retangulo_criar`
 */
void retangulo_destruir(retangulo* r);

/*
 * calcula a largura de um retângulo
 */
double retangulo_largura(retangulo const* r);

/*
 * calcula a altura de um retângulo
 */
double retangulo_altura(retangulo const* r);

/*
 * calcula a area de um retângulo
 */
double retangulo_area(retangulo const* r);

/*
 * translada o retângulo `r` por o movimento em `v`
 */
void retangulo_transladar(retangulo* r, vetor const* v);

/*
 * retorna 1 se os dois retângulos `a` e `b` se intersectam
 */
int retangulo_intersectam(retangulo const* a, retangulo const* b);

/*
 * retorna a intersecção entre a e b; caso a intersecção é vazia
 * retorna NULL
 */ 
retangulo* retangulo_interseccao(retangulo const* a, retangulo const* b);

#endif
