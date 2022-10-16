#include <stdio.h>
#include "heap.h"

int main(int argc, char const *argv[]) {
	
	int i, n_boxes, weight;
	char read[MAX_STRING_LENGTH];
	Lot *lot;

	/* Leitura e construcao da estrutura */
	scanf("%d", &n_boxes);
	lot = create_lot(n_boxes);

	/* Adicao e selecao das caixas para analise */
	for (i = 0; i < n_boxes; i++) {
		scanf("%s %d", read, &weight);
		lot_add(lot, read, weight);
		print_selected_boxes(lot);
	}

	/* Liberacao do espaco alocado */
	free_lot(lot);

	return 0;
}