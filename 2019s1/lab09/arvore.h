#ifndef ARVORE_H
#define ARVORE_H

enum { RED, BLACK };

typedef int color_t;

typedef struct rbbst_node_s {
	int value;
	color_t color;
	struct rbbst_node_s *right, *left, *parent;
} * rbbst_node_t;

typedef struct rbbst_s {
	rbbst_node_t root;
} * rbbst_t;


//=================================================================
// Tree creation and destruction
//=================================================================

/* initialization of a redblack binary search tree
 * @return pointer to tree
 */
rbbst_t rbbst_init();
/* creation of a node
 * @param parent node of parent of new node
 * @param x value value of new node
 * @return pointer to node
 */
rbbst_node_t rbbst_create(rbbst_node_t parent, int x);
/* destruction of tree
 * @param tree pointer to tree
 */
void rbbst_free(rbbst_t tree);


//=================================================================
// Tree manipulation
//=================================================================

/* search of node given value
 * @param tree pointer to tree
 * @param x value to search
 * @return if in tree: node of value, else: null
 */
rbbst_node_t rbbst_find(rbbst_t tree, int x);
/* insert value in tree
 * @param tree pointer to tree
 * @param x value to insert
 */
void rbbst_insert(rbbst_t tree, int x);
/* remove value from tree
 * @param tree pointer to tree
 * @param x value to remove
 */
void rbbst_remove(rbbst_t tree, int x);


//=================================================================
// Extracting information from a tree
//=================================================================

/* finds max value in tree
 * @param tree pointer to tree
 * @return node of max value
 */
rbbst_node_t rbbst_max(rbbst_t tree);
/* finds successor of node
 * @param tree pointer to tree
 * @return node of successor
 */
rbbst_node_t successor(rbbst_node_t node);
/* finds grandparent of node
 * @param node
 * @return grandparent of node
 */
rbbst_node_t rbbst_grandparent(rbbst_node_t node);
/* finds uncle of node
 * @param node
 * @return uncle of node
 */
rbbst_node_t rbbst_uncle(rbbst_node_t node);
/* finds sibling of node
 * @param node
 * @return sibling of node
 */
rbbst_node_t rbbst_sibling(rbbst_node_t node);


#endif