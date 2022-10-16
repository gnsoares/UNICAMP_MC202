#include "estoque.h"
#include <string.h>

stock_t stock_create() {
	stock_t new;
	new.n_products = 0;
	return new;
}

stock_t stock_cpy(stock_t stock) {
	stock_t new;
	for (int i = 0; i < stock.n_products; i++)
		new.products[i] = stock.products[i];
	new.n_products = stock.n_products;
	return new;
}

stock_t stock_add_product(stock_t stock, product_t prod) {
	stock_t new;
	new = stock_cpy(stock);
	new.products[new.n_products++] = prod;
	return new;
}

product_t stock_find_product(stock_t stock, char name[]) {
	for (int i = 0; i < stock.n_products; i++)
		if (!strcmp(stock.products[i].name, name))
			return stock.products[i];
	return product_create("", 0.0, 0, date_create(0, 0, 0));
}