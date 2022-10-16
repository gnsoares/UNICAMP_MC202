#include <stdio.h>
#include <stdlib.h>

#define MAXINT 1000
#define MAXK 500

int main() {

	int i, j, k; // iteradores
	int n, m, count = 0; // quantificadores
	int v_int[MAXINT], v_k[MAXK];

	// leitura da entrada
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", &v_int[i]);
	scanf("%d", &m);
	for (i = 0; i < m; i++)
		scanf("%d", &v_k[i]);

	// contagem e impressao do resultado
	for (k = 0; k < m; k++) {
		for (i = 0; i < n; i++)
			for (j = i+1; j < n; j++)
				if (abs(v_int[i] - v_int[j]) == v_k[k])
					count++;
		if (k != m-1) {
			printf("%d ", count);
			count = 0;
		}
	}
	printf("%d\n", count);

}