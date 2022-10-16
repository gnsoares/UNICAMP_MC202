#include "vetor.h"
#include <stdlib.h>

vetor* vetor_criar(double x, double y) {
	vetor * new;
	if ( !( new = malloc( sizeof(vetor) ) ) )
		exit(1);

	new->x = x;
	new->y = y;

	return new;
}

void vetor_destruir(vetor* v) {
	free(v);
}

void vetor_somar(vetor const* a, vetor const* b, vetor* c) {
	c->x = a->x + b->x;
	c->y = a->y + b->y;
}