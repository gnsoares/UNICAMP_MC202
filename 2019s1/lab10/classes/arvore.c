#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

bst_node_t * bst_create(int x, bst_node_t * left, bst_node_t * right) {
	bst_node_t * root = malloc(sizeof(bst_node_t));
	assert(root);
	root->key = x;
	root->attacks = 0;
	root->left = left;
	root->right = right;
	return root;
}

bst_node_t * bst_find(bst_node_t * root, int x) {
	if (!root || x == root->key)
		return root;
	if (x < root->key)
		return bst_find(root->left, x);
	return bst_find(root->right, x);
}

bst_node_t * bst_insert(bst_node_t * root, int x) {
	if (!root)
		return bst_create(x, NULL, NULL);
	if (x < root->key)
		root->left = bst_insert(root->left, x);
	else
		root->right = bst_insert(root->right, x);
	return root;
}

/* store the nodes of a bst in a sorted array
 * @param root pointer to bst
 * @param nodes array that keeps the nodes
 */
void store_nodes(bst_node_t * root, bst_node_t ** nodes) {
	int i;
	if (!root) return;
	store_nodes(root->left, nodes);
	for (i = 0; nodes[i]; i++);
	nodes[i] = root;
	store_nodes(root->right, nodes);
}

bst_node_t * bst_build(bst_node_t ** nodes, int beg, int end) {
	if (beg > end)
		return NULL;
	int mid = (beg + end)/2;
	bst_node_t * root = nodes[mid];
	root->left = bst_build(nodes, beg, mid-1);
	root->right = bst_build(nodes, mid+1, end);
	return root;
}

bst_node_t * bst_balance(bst_node_t * root, int n) {
	bst_node_t * new_bst;
	bst_node_t ** nodes = malloc(n * sizeof(bst_node_t *));
	assert(nodes);
	for (int i = 0; i < n; nodes[i++] = NULL);
	store_nodes(root, nodes);
	new_bst = bst_build(nodes, 0, n-1);
	free(nodes);
	return new_bst;		
}

void bst_free(bst_node_t * root) {
	if (!root) return;
	bst_free(root->left);
	bst_free(root->right);
	free(root);
}

void bst_preorder(bst_node_t * root) {
	if (!root) return;
	printf("%d %d\n", root->key, root->attacks);
	bst_preorder(root->left);
	bst_preorder(root->right);
}