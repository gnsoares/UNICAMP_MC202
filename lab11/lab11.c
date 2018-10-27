#include <stdio.h>
#include <stdlib.h>
#include "treap.h"

int main()
{
	int i, n, read;
	TreapNode **v;

	scanf("%d", &n);
	v = malloc(n*sizeof(TreapNode *));

	for (i = 0; i < n; i++) {
		scanf("%d", &read);
		v[i] = create_tree(atoi(&read), NULL, NULL);
		
	}

	return 0;
}