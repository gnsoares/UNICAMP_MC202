#ifndef ESTOQUE_H
#define ESTOQUE_H

#include "produto.h"

#define MAX_PRODUCT_STOCK 100

typedef struct stock_s {
	product_t products[MAX_PRODUCT_STOCK];
	int n_products;
} stock_t;

/*
 * creates an empty stock
 * @return stock object
 */
stock_t stock_create();

/*
 * copies a stock
 * @param stock original stock
 * @return new stock object with same products
 */
stock_t stock_cpy(stock_t stock);

/*
 * adds a new product in a stock
 * @param stock original stock
 * @param prod new product
 * @return new stock object with product added
 */
stock_t stock_add_product(stock_t stock, product_t prod);

/*
 * finds a product inside a stock
 * @param stock
 * @param name product's name
 * @return product object
 */
product_t stock_find_product(stock_t stock, char name[]);

#endif
