#ifndef LISTA_H
#define LISTA_H

/* Implementation of a LINKED LIST of integers */

typedef struct int_node_s {
	int data;
	struct int_node_s * next;
} int_node_t;

typedef struct int_list_s {
	int_node_t * head;
} int_list_t;


/* creates an empty list
 * @return pointer to the new list
 */
int_list_t * int_list_create(void);

/* inserts an element at the head of the list
 * @param list list
 * @param x element
 */
void int_list_insert(int_list_t * list, int x);

/* inserts an element in the right order in a sorted list
 * only useful in increasing sorted lists
 * @param list list
 * @param x element
 */
void int_list_insert_sorted(int_list_t * list, int x);

/* removes the element at the head of a list
 * @param list list
 */
void int_list_remove(int_list_t * list);

/* prints all the elements of a list
 * @param list list
 */
void int_list_print(int_list_t * list);

/* frees the memory allocated to a list
 * @param list list
 */
void int_list_free(int_list_t * list);

#endif