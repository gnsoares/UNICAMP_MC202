#ifndef DATA_H
#define DATA_H

typedef struct date_s {
	int day;
	int month;
	int year;
} date_t;

/*
 * creates a new date from params
 * @param day
 * @param month
 * @param year
 * @return date object
 */
date_t date_create(int day, int month, int year);

/*
 * creates a new date from keyboard input
 * @return date object
 */
date_t date_read();

/*
 * compares two dates
 * @param date1
 * @param date2
 * @return if date1 before date2: -1; if date1 == date2: 0; if date1 after date2: 1
 */
int date_compare(date_t date1, date_t date2);

#endif
