#ifndef ARVORE_H
#define ARVORE_H

typedef struct bst_node_s {
	int key, attacks;
	struct bst_node_s * left, * right;
} bst_node_t;


/* creates a bst
 * @param key value of root
 * @param left pointer to left sub-tree
 * @param right pointer to right sub-tree
 * @return pointer to root
 */
bst_node_t * bst_create(int key, bst_node_t * left, bst_node_t * right);

/* finds the node of a given value
 * @param root root of bst
 * @param x value to be found
 * @return pointer to node
 */
bst_node_t * bst_find(bst_node_t * root, int x);

/* inserts a value in a bst
 * @param root root of bst
 * @param x value to be inserted
 * @return pointer to root
 */
bst_node_t * bst_insert(bst_node_t * root, int x);

/* builds a bst given an ordered array of nodes
 * @param nodes sorted array of bst nodes
 * @param beg position of array to begin building
 * @param end position of array to end building
 * @return pointer to root
 */
bst_node_t * bst_build(bst_node_t ** nodes, int beg, int end);

/* balances a bst
 * @param root pointer to original bst
 * @param n number of nodes
 * @return pointer to root of balanced bst
 */
bst_node_t * bst_balance(bst_node_t * root, int n);

/* frees a bst
 * @param root pointer to bst
 */
void bst_free(bst_node_t * root);

/* prints a bst using preorder
 * @param root pointer to bst
 */
void bst_preorder(bst_node_t * root);


#endif