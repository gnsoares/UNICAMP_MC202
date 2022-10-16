#include "data.h"
#include <stdio.h>

date_t date_create(int day, int month, int year) {
	date_t new;
	new.day = day;
	new.month = month;
	new.year = year;
	return new;
}

date_t date_read() {
	date_t new;
	int day, month, year;
	scanf("%d/%d/%d", &day, &month, &year);
	new = date_create(day, month, year);
	return new;
}

int date_compare(date_t date1, date_t date2) {
	if (date2.year > date1.year)
		return -1;
	if (date2.year < date1.year)
		return 1;
	if (date2.month > date1.month)
		return -1;
	if (date2.month < date1.month)
		return 1;
	if (date2.day > date1.day)
		return -1;
	if (date2.day < date1.day)
		return 1;
	return 0;
}