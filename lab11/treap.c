#include <stdio.h>
#include <stdlib.h>
#include "treap.h"

TreapNode * create_tree(int key, TreapNode *left, TreapNode *right) {
	TreapNode *root = new_node(key, rand());
	if (root) {
		root->left = left;
		root->right = right;
	}
	return root;
}

TreapNode * new_node(int key, int priority) {
	TreapNode *new = malloc(sizeof(TreapNode));
	if (!new) exit(1);
	new->key = key;
	new->priority = priority;
	new->left = new->right = NULL;
	return new;
}

TreapNode * rotate_right(TreapNode *root) {
    TreapNode *r2 = root->left;

    root->left = r2->right;
    r2->right = root;
    return r2;
}

TreapNode * rotate_left(TreapNode *root) {
    TreapNode *r2 = root->right;

    root->right = r2->left;
    r2->left = root;
    return r2;
}

/* Recursive implementation of insertion in Treap */
TreapNode * insert(TreapNode* root, int key)  { 
	// If root is NULL, create a new node and return it 
	if (!root) 
		return new_node(key, rand());

	// If key is smaller than root 
	if (key <= root->key) { 
		// Insert in left subtree 
		root->left = insert(root->left, key); 

		// Fix Heap property if it is violated 
		if (root->left->priority > root->priority) 
			root = rotate_right(root); 
	} else {// If key is greater 
		// Insert in right subtree 
		root->right = insert(root->right, key); 

		// Fix Heap property if it is violated 
		if (root->right->priority > root->priority) 
			root = rotate_left(root); 
	}
	return root; 
}


void swap(TreapNode **r1, TreapNode **r2) {
	TreapNode *t = *r1;
	*r1 = *r2;
	*r2 = t;
}

TreapNode * split(TreapNode **less, TreapNode **gtr, TreapNode *r, int key) {

	TreapNode *root;
	if (r == NULL) {
		*less = *gtr = NULL;
		return NULL;
	}

	root = new_node(r->key, r->priority);
	if (r->key < key) {
		*less = root;
		return split(&(root->right), gtr, r->right, key);
	} else if (r->key > key) {
		*gtr = root;
		return split(less, &(root->left), r->left, key);
	} else {
		*less = r->left;
		*gtr = r->right;
		return root;
	}
}

TreapNode * join(TreapNode *r1, TreapNode *r2) {

	TreapNode *root;

	if (r1 == NULL) return r2;
	if (r2 == NULL) return r1;

	if (r1->priority < r2->priority) {
		root = new_node(r1->key, r1->priority);
		root->left = r1->left;
		root->right = join(r1->right, r2);
	} else {
		root = new_node(r2->key, r2->priority);
		root->left = join(r1, r2->left);
		root->right = r1->right;
	}
	return root;
}

TreapNode * diff(TreapNode *r1, TreapNode *r2, int r2_is_subtr) {
	TreapNode *root, *less, *gtr, *left, *right, *duplicate;
	if ((r1 == NULL) || (r2 == NULL))
		return r2_is_subtr ? r1 : r2;
	if (r1->priority < r2->priority) {
		r2_is_subtr = !r2_is_subtr;
		swap(&r1, &r2);
	}
	duplicate = split(&less, &gtr, r2, r1->key);
	left = diff(r1->left, less, r2_is_subtr);
	right = diff(r1->right, gtr, r2_is_subtr);
	/* Keep r1 if no dupl. and subtracting r2 */
	if ((duplicate == NULL) && r2_is_subtr) {
		root = new_node(r1->key, r1->priority);
		root->left = left;
		root->right = right;
		return root;
	} else { /* Delete r1 */
		return join(left, right);
	}
}

TreapNode * union(TreapNode *r1, TreapNode *r2) {
	TreapNode *root, *less, *gtr, *duplicate;

	if (r1 == NULL) return r2;
	if (r2 == NULL) return r1;

	if (r1->priority < r2->priority)
		swap(&r1, &r2);
	duplicate = split(&less, &gtr, r2, r1->key);

	root = new_node(r1->key, r1->priority);
	root->left = union(r1->left, less);
	root->right = union(r1->right, gtr);
	return root;
}