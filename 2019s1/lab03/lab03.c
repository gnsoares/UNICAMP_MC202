#include <stdio.h>
#include <string.h>
#include "data.h"
#include "produto.h"
#include "estoque.h"

int main(void) {

	int n_products, n_lines, quantity, is_expired;
	float cost;
	char name[MAX_NAME_PRODUCT];
	product_t product;
	date_t today;
	stock_t stock = stock_create();

	// stock filling
	today = date_read();
	scanf("%d", &n_products);
	for (int i = 0; i < n_products; i++)
		stock = stock_add_product(stock, product_read());

	// costs calculation
	scanf("%d", &n_lines);
	for (int i = 0; i < n_lines; i++) {
		cost = 0.0;
		scanf("%s %d", name, &quantity);
		product = stock_find_product(stock, name);
		if (!strcmp(product.name, ""))
			continue;
		is_expired = product_is_expired(product, today);
		if (is_expired)
			cost = quantity * product.price;
		else if (product.quantity < quantity)
			cost = (quantity - product.quantity) * product.price;
		printf("%s %.2f\n", name, cost);
	}

	return 0;
}