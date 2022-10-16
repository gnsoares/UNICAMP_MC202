#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "arvore.h"


rbbst_t rbbst_init() {
	rbbst_t new = malloc(sizeof(struct rbbst_s));
	assert(new);
	new->root = NULL;
	return new;
}

rbbst_node_t rbbst_create(rbbst_node_t parent, int x) {
	rbbst_node_t root = malloc(sizeof(struct rbbst_node_s));
	assert(root);
	root->left = root->right = NULL;
	root->parent = parent;
	root->value = x;
	root->color = RED; // Node starts red, aux function fixes if not correct
	return root;	
}

rbbst_node_t rbbst_grandparent(rbbst_node_t node) {
	if (!node || !node->parent)
		return NULL;
	return node->parent->parent;
}

rbbst_node_t rbbst_uncle(rbbst_node_t node) {
	rbbst_node_t gparent = rbbst_grandparent(node);
	if (!node || !gparent)
		return NULL;
	if (node->parent == gparent->left)
		return gparent->right;
	return gparent->left;
}

rbbst_node_t rbbst_sibling(rbbst_node_t node) {
	if (node == node->parent->left)
		return node->parent->right;
	return node->parent->left;	
}

rbbst_node_t rbbst_find(rbbst_t tree, int x) {
	rbbst_node_t node;
	for (node = tree->root;
		 node && node->value != x;
		 node = (node->value > x ? node->left : node->right));
	return node;
}

/* rotates a node to the right
 * @param tree pointer to tree
 * @param node to rotate
 */
void rbbst_rotate_right(rbbst_t tree, rbbst_node_t node) {
	rbbst_node_t child = node->left,
				 parent = node->parent;

	if (node == tree->root)
		tree->root = child;

	if (child->right)
		child->right->parent = node;

	node->left = child->right;
	node->parent = child;
	child->right = node;
	child->parent = parent;

	if (parent) {
		if (parent->right == node)
			parent->right = child;
		else
			parent->left = child;
	}
}
/* rotates a node to the left
 * @param tree pointer to tree
 * @param node to rotate
 */
void rbbst_rotate_left(rbbst_t tree, rbbst_node_t node) {
	rbbst_node_t child = node->right,
				 parent = node->parent;

	if (node == tree->root)
		tree->root = child;

	if (child->left)
		child->left->parent = node;

	node->right = child->left;
	node->parent = child;
	child->left = node;
	child->parent = parent;

	if (parent) {
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
}

rbbst_node_t successor(rbbst_node_t node) {
	rbbst_node_t temp = node->right;
	while (temp->left) 
		temp = temp->left;
	return temp;
}

/* node has red child?
 * @param node
 * @return if yes: 1, else: 0
 */
int has_red_child(rbbst_node_t node) {
	return (node->left && node->left->color == RED) || 
		(node->right && node->right->color == RED);
}

/* finds the replacement of node when node is removed
 * @param node
 * @return node of replacement
 */
rbbst_node_t replacement(rbbst_node_t node) {
	// when node have 2 children 
	if (node->left && node->right) 
		return successor(node);

	// when leaf 
	if (!node->left && !node->right) 
		return NULL;

	// when single child 
	if (node->left) 
		return node->left;
	return node->right;
}

/* fixes when replacement and node are both black
 * @param tree pointer to tree
 * @param node
 */
void fix_double_black(rbbst_t tree, rbbst_node_t node) {
	if (node == tree->root) 
		// Reached root 
		return;

	rbbst_node_t sibling = rbbst_sibling(node), parent = node->parent;
	if (!sibling) {
		// No sibling, double black pushed up 
		fix_double_black(tree, parent);
	} else {
		if (sibling->color == RED) {
			// Sibling red 
			parent->color = RED;
			sibling->color = BLACK;
			if (sibling == sibling->parent->left)
				rbbst_rotate_right(tree, parent);
			else
				rbbst_rotate_left(tree, parent);
			fix_double_black(tree, node);
		} else {
			// Sibling black 
			if (has_red_child(sibling)) {
				// at least 1 red children 
				if (sibling->left && sibling->left->color == RED) {
					if (sibling == sibling->parent->left) {
						// left left 
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						rbbst_rotate_right(tree, parent);
					} else {
						// right left 
						sibling->left->color = parent->color;
						rbbst_rotate_right(tree, sibling);
						rbbst_rotate_left(tree, parent);
					}
				} else {
					if (sibling == sibling->parent->left) {
						// left right 
						sibling->right->color = parent->color;
						rbbst_rotate_left(tree, sibling);
						rbbst_rotate_right(tree, parent);
					} else {
						// right right 
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						rbbst_rotate_left(tree, parent);
					}
				}
				parent->color = BLACK;
			} else {
				// 2 black children 
				sibling->color = RED;
				if (parent->color == BLACK) 
					fix_double_black(tree, parent);
				else
					parent->color = BLACK;
			}
		}
	}
}

/* swaps values of two nodes
 * @param u node 1
 * @param v node 2
 */
void swap_values(rbbst_node_t u, rbbst_node_t v) { 
	int temp; 
	temp = u->value; 
	u->value = v->value; 
	v->value = temp; 
} 

/* aux function that fixes insertion
 * @param tree pointer to tree
 * @param node inserted
 */
void insert_util(rbbst_t tree, rbbst_node_t node) {
	rbbst_node_t uncle = rbbst_uncle(node),
				 gparent = rbbst_grandparent(node),
				 parent = node->parent;

	if (!parent)
	// Node is root -> root has to be black
		node->color = BLACK;
	else if (parent->color == BLACK)
	// Parent is black -> ok
		return;
	else if (uncle && uncle->color == RED) {
	// Uncle and parent red
		parent->color = BLACK;
		uncle->color = BLACK;
		gparent->color = RED;
		insert_util(tree, gparent);
	} else {
	// Uncle black and parent red
		if (node == parent->right && parent == gparent->left) {
			rbbst_rotate_left(tree, parent);
			node = node->left;
		}
		else if (node == parent->left && parent == gparent->right) {
			rbbst_rotate_right(tree, parent);
			node = node->right;
		}
		gparent = rbbst_grandparent(node);
		parent = node->parent;
		parent->color = BLACK;
		gparent->color = RED;
		// keep fixing up
		if (node == parent->left)
			rbbst_rotate_right(tree, gparent);
		else
			rbbst_rotate_left(tree, gparent);
	}
}
void rbbst_insert(rbbst_t tree, int x) {
	int is_left_child = 0;
	rbbst_node_t tmp, parent = NULL, new;

	// Insertion replicates search
	for (tmp = tree->root; tmp;
	parent = tmp, tmp = ((is_left_child = (tmp->value > x)) ? tmp->left : tmp->right));

	// Create node
	new = rbbst_create(parent, x);

	if (parent)
		(is_left_child) ? (parent->left = new) : (parent->right = new);

	// Fix balance and colors
	insert_util(tree, new);

	// Going up to fix root
	for (tmp = new; tmp; parent = tmp, tmp = tmp->parent);
	tree->root = parent;
}

/* removes node from tree
 * @param tree pointer to tree
 * @param node
 */
void rbbst_remove_node(rbbst_t tree, rbbst_node_t node) {
	rbbst_node_t replace = replacement(node);

	// 1 when replace and node are both black 
	int both_black = ((!replace || replace->color == BLACK) && (node->color == BLACK));
	rbbst_node_t parent = node->parent;

	if (!replace) {
	// replace is NULL -> node is leaf 
		if (node == tree->root) { 
		// v is root, making root null 
			tree->root = NULL; 
		} else {
			if (both_black) {
			// replace and node both black
			// node is leaf, fix double black at node 
				fix_double_black(tree, node);
			} else if (rbbst_sibling(node)) {
			// sibling is not null, make it red
				rbbst_sibling(node)->color = RED;
			}

			// remove node from the tree 
			if (node == node->parent->left)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		free(node);
		return;
	}

	if (!node->left || !node->right) {
		// node has 1 child 
		if (node == tree->root) {
			// node is root, assign the value of replace to node, and free replace
			node->value = replace->value;
			node->left = node->right = NULL;
			free(replace);
		} else {
			// Detach node from tree and move replace up 
			if (node == node->parent->left) {
				parent->left = replace;
			} else {
				parent->right = replace;
			}
			free(node);
			replace->parent = parent;
			if (both_black) {
				// replace and node both black, fix double black at replace 
				fix_double_black(tree, replace);
			} else {
				// replace or node red, color replace black 
				replace->color = BLACK;
			}
		}
		return;
	}

	// node has 2 children, swap values with successor and recurse 
	swap_values(replace, node);
	rbbst_remove_node(tree, replace);
}
void rbbst_remove(rbbst_t tree, int x) {
	rbbst_remove_node(tree, rbbst_find(tree, x));
}	

rbbst_node_t rbbst_max(rbbst_t tree) {
	rbbst_node_t node;
	for (node = tree->root;
		 node && node->right;
		 node = node->right);
	return node;
}

/* destroys nodes from tree
 * @param tree pointer to tree
 * @param 
 */
void rbbst_free_nodes(rbbst_node_t root) {
	if (!root) return;
	rbbst_free_nodes(root->left);
	rbbst_free_nodes(root->right);
	free(root);
}
void rbbst_free(rbbst_t tree) {
	rbbst_free_nodes(tree->root);
	free(tree);
}
