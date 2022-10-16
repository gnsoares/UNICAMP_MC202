#include "produto.h"
#include <stdio.h>
#include <string.h>

product_t product_create(char name[], float price, int quantity, date_t expiration) {
	product_t new;
	strcpy(new.name, name);
	new.price = price;
	new.quantity = quantity;
	new.expiration = expiration;
	return new;
}

product_t product_read() {
	product_t new;
	char name[MAX_NAME_PRODUCT];
	float price;
	int quantity;
	date_t expiration;
	scanf("%s %f %d", name, &price, &quantity);
	expiration = date_read();
	new = product_create(name, price, quantity, expiration);
	return new;
}

int product_is_expired(product_t prod, date_t date) {
	return date_compare(prod.expiration, date) == -1 ? 1 : 0; 
}
