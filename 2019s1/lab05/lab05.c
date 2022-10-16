#include <stdio.h>
#include <stdlib.h>
#include "imagem.h"
#include <string.h>

#define FRACTAL_LEN 11

/******************************************************************************
 *
 * FUNCOES AUXILIARES QUE EXECUTAM AS REGRAS
 *
 ******************************************************************************/

void simples_f(imagem_p img, int len, int ang, int n_sub) {
	if (n_sub == 0) { // caso base
		andar_cabeca(img, len);
		return;
	}
	// chamadas recursivas
	simples_f(img, len, ang, n_sub-1);
	simples_f(img, len, ang, n_sub-1);
}

void sierpinski_g(imagem_p img, int len, int ang, int n_sub) {
	if (n_sub == 0) { // caso base
		andar_cabeca(img, len);
		return;
	}
	// chamadas recursivas
	sierpinski_g(img, len, ang, n_sub-1);
	sierpinski_g(img, len, ang, n_sub-1);	
}

void sierpinski_f(imagem_p img, int len, int ang, int n_sub) {
	if (n_sub == 0) { // caso base
		andar_cabeca(img, len);
		return;
	}
	// chamadas recursivas
	sierpinski_f(img, len, ang, n_sub-1);
	girar_cabeca(img, ang);
	sierpinski_g(img, len, ang, n_sub-1);
	girar_cabeca(img, -ang);
	sierpinski_f(img, len, ang, n_sub-1);
	girar_cabeca(img, -ang);
	sierpinski_g(img, len, ang, n_sub-1);
	girar_cabeca(img, ang);
	sierpinski_f(img, len, ang, n_sub-1);
}

void dragao_a(imagem_p img, int len, int ang, int n_sub);
void dragao_f(imagem_p img, int len, int ang, int n_sub);

void dragao_a(imagem_p img, int len, int ang, int n_sub) {
	if (n_sub == 0) { // caso base
		andar_cabeca(img, len);
		return;
	}
	// chamadas recursivas
	dragao_f(img, len, ang, n_sub-1);
	girar_cabeca(img, ang);
	dragao_a(img, len, ang, n_sub-1);
}

void dragao_f(imagem_p img, int len, int ang, int n_sub) {
	if (n_sub == 0) { // caso base
		andar_cabeca(img, len);
		return;
	}
	// chamadas recursivas
	dragao_f(img, len, ang, n_sub-1);
	girar_cabeca(img, -ang);
	dragao_a(img, len, ang, n_sub-1);
}

void gelo_f(imagem_p img, int len, int ang, int n_sub) {
	if (n_sub == 0) { // caso base
		andar_cabeca(img, len);
		return;
	}
	// chamadas recursivas
	gelo_f(img, len, ang, n_sub-1);
	gelo_f(img, len, ang, n_sub-1);
	girar_cabeca(img, ang);
	gelo_f(img, len, ang, n_sub-1);
	girar_cabeca(img, ang);
	girar_cabeca(img, ang);
	gelo_f(img, len, ang, n_sub-1);
	girar_cabeca(img, ang);
	gelo_f(img, len, ang, n_sub-1);	
}

void diamante_f(imagem_p img, int len, int ang, int n_sub) {
	if (n_sub == 0) { // caso base
		andar_cabeca(img, len);
		return;
	}
	// chamadas recursivas
	girar_cabeca(img, -ang);
	diamante_f(img, len, ang, n_sub-1);
	girar_cabeca(img, ang);
	diamante_f(img, len, ang, n_sub-1);
	girar_cabeca(img, ang);
	diamante_f(img, len, ang, n_sub-1);
	girar_cabeca(img, -ang);
}

/******************************************************************************
 *
 * FUNCOES PRINCIPAIS QUE EXECUTAM AS SEQUENCIAS INICIAIS
 *                        (ou a regra tambem se possivel)
 ******************************************************************************/

void simples(imagem_p img, int len, int ang, int n_sub) {
	// init: F+F+F
	// rule: F = FF
	simples_f(img, len, ang, n_sub);
	girar_cabeca(img, ang);
	simples_f(img, len, ang, n_sub);
	girar_cabeca(img, ang);
	simples_f(img, len, ang, n_sub);
}

void koch(imagem_p img, int len, int ang, int n_sub) {
	// init: F
	// rule: F = F+F--F+F
	if (n_sub == 0) { // caso base
		andar_cabeca(img, len);
		return;
	}
	// chamadas recursivas
	koch(img, len, ang, n_sub-1);
	girar_cabeca(img, ang);
	koch(img, len, ang, n_sub-1);
	girar_cabeca(img, -ang);
	girar_cabeca(img, -ang);
	koch(img, len, ang, n_sub-1);
	girar_cabeca(img, ang);
	koch(img, len, ang, n_sub-1);
}


void sierpinski(imagem_p img, int len, int ang, int n_sub) {
	// init: F+G+G
	// rule: F = F+G-F-G+F; G = GG
	sierpinski_f(img, len, ang, n_sub);
	girar_cabeca(img, ang);
	sierpinski_g(img, len, ang, n_sub);
	girar_cabeca(img, ang);
	sierpinski_g(img, len, ang, n_sub);
}

void dragao(imagem_p img, int len, int ang, int n_sub) {
	// init: FA
	// rule: F = F-A; A = F+A
	dragao_f(img, len, ang, n_sub);
	dragao_a(img, len, ang, n_sub);
}

void arvore(imagem_p img, int len, int ang, int n_sub) {
	// init: F
	// rule: F = F[+FF][-FF]F[-F][+F]F
	tartaruga cabeca; // permite que a tartaruga volte sem desenhar

	if (n_sub == 0) { // caso base
		andar_cabeca(img, len);
		return;
	}
	// chamadas recursivas

	// tronco
	arvore(img, len, ang, n_sub-1);
	// galho esquerdo
	cabeca = obter_tartaruga(img);
	girar_cabeca(img, ang);
	arvore(img, len, ang, n_sub-1);
	arvore(img, len, ang, n_sub-1);
	posicionar_tartaruga(img, cabeca);
	// galho direito
	girar_cabeca(img, -ang);
	arvore(img, len, ang, n_sub-1);
	arvore(img, len, ang, n_sub-1);
	posicionar_tartaruga(img, cabeca);
	// tronco
	arvore(img, len, ang, n_sub-1);
	// galho esquerdo
	cabeca = obter_tartaruga(img);
	girar_cabeca(img, -ang);
	arvore(img, len, ang, n_sub-1);
	posicionar_tartaruga(img, cabeca);
	// galho direito
	girar_cabeca(img, ang);
	arvore(img, len, ang, n_sub-1);
	posicionar_tartaruga(img, cabeca);
	// tronco
	arvore(img, len, ang, n_sub-1);
}

void gelo(imagem_p img, int len, int ang, int n_sub) {
	// init: F+F+F+F
	// rule: F = FF+F++F+F
	gelo_f(img, len, ang, n_sub);
	girar_cabeca(img, ang);
	gelo_f(img, len, ang, n_sub);
	girar_cabeca(img, ang);
	gelo_f(img, len, ang, n_sub);
	girar_cabeca(img, ang);
	gelo_f(img, len, ang, n_sub);
}

void diamante(imagem_p img, int len, int ang, int n_sub) {
	// init: F+F+F+F+F+F+
	// rule: F = -F+F+F-
	diamante_f(img, len, ang, n_sub);
	girar_cabeca(img, ang);
	diamante_f(img, len, ang, n_sub);
	girar_cabeca(img, ang);
	diamante_f(img, len, ang, n_sub);
	girar_cabeca(img, ang);
	diamante_f(img, len, ang, n_sub);
	girar_cabeca(img, ang);
	diamante_f(img, len, ang, n_sub);
	girar_cabeca(img, ang);
	diamante_f(img, len, ang, n_sub);
	girar_cabeca(img, ang);
}


int main(void) {

	imagem_p img = criar_imagem();
	char fractal[FRACTAL_LEN];
	int len, ang, n_sub;

	scanf("%s\n%d\n%d\n%d", fractal, &len, &ang, &n_sub);

	if (!strcmp(fractal, "simples")) {
		simples(img, len, ang, n_sub);
	} else if (!strcmp(fractal, "koch")) {
		koch(img, len, ang, n_sub);
	} else if (!strcmp(fractal, "sierpinski")) {
		sierpinski(img, len, ang, n_sub);
	} else if (!strcmp(fractal, "dragao")) {
		dragao(img, len, ang, n_sub);
	} else if (!strcmp(fractal, "arvore")) {
		arvore(img, len, ang, n_sub);
	} else if (!strcmp(fractal, "gelo")) {
		gelo(img, len, ang, n_sub);
	} else if (!strcmp(fractal, "diamante")) {
		diamante(img, len, ang, n_sub);
	} else {
		exit(1);
	}

	imprimir_imagem(img);
	liberar_imagem(img);

	return 0;
}