#include "retangulo.h"
#include <stdlib.h>
#include <math.h>

#define MAX(x,  y) (((x) > (y)) ? (x) : (y))
#define MIN(x,  y) (((x) < (y)) ? (x) : (y))


retangulo* retangulo_criar(double px, double py, double qx, double qy) {
	retangulo * new;
	if ( !( new = malloc( sizeof(retangulo) ) ) )
		exit(1);

	new->sup_esq = vetor_criar(px, py);
	new->inf_dir = vetor_criar(qx, qy);

	return new;
}

void retangulo_destruir(retangulo* r) {
	vetor_destruir(r->sup_esq);
	vetor_destruir(r->inf_dir);
	free(r);
}

double retangulo_largura(retangulo const* r) {
	return fabs( r->inf_dir->x - r->sup_esq->x );
}

double retangulo_altura(retangulo const* r) {
	return fabs( r->sup_esq->y - r->inf_dir->y );
}

double retangulo_area(retangulo const* r) {
	return retangulo_largura(r) * retangulo_altura(r);
}

void retangulo_transladar(retangulo* r, vetor const* v) {
	vetor_somar(r->sup_esq, v, r->sup_esq);
	vetor_somar(r->inf_dir, v, r->inf_dir);
}

int retangulo_intersectam(retangulo const* a, retangulo const* b) {
	if (a == NULL || b == NULL)
		return 0;
	return
        // intersection on x-axis
	       a->sup_esq->x <= b->inf_dir->x
	    && a->inf_dir->x >= b->sup_esq->x
	    // intersection on y-axis
	    && a->inf_dir->y <= b->sup_esq->y
	    && a->sup_esq->y >= b->inf_dir->y;
}

retangulo* retangulo_interseccao(retangulo const* a, retangulo const* b) {
	if (!retangulo_intersectam(a, b))
		return NULL;

	double px, py, qx, qy;

	px = MAX(a->sup_esq->x, b->sup_esq->x);
	py = MIN(a->sup_esq->y, b->sup_esq->y);
	qx = MIN(a->inf_dir->x, b->inf_dir->x);
	qy = MAX(a->inf_dir->y, b->inf_dir->y);

	return retangulo_criar(px, py, qx, qy);
}