#ifndef PRODUTO_H
#define PRODUTO_H

#include "data.h"

#define MAX_NAME_PRODUCT 21

typedef struct product_s {
	char name[MAX_NAME_PRODUCT];
	float price;
	int quantity;
	date_t expiration;
} product_t;

/*
 * creates a new product from params
 * @param name product's name
 * @param price product's price
 * @param quantity
 * @param expiration product's expiration date
 * @return product object
 */
product_t product_create(char name[], float price, int quantity, date_t expiration);

/*
 * creates a new product from keyboard input
 * @return product object
 */
product_t product_read();

/*
 * checks if a product will be expired in a specific date
 * @param prod product object
 * @param date date object
 * @return if expired: 1; else: 0
 */
int product_is_expired(product_t prod, date_t date);

#endif
