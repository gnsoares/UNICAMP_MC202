#include "treap.h"

p_treap *treaps = NULL;
int n_treaps = 0;

/**
 * Compare strings
 * @param  node1 node 1
 * @param  node2 node 2
 * @return       0 if str1 < str 2, 1 if str1 >= str2
 */
static int compare(p_node node1, p_node node2) {
    return node1->key >= node2->key;
}

/**
 * is equal
 * @param  node1 node 1
 * @param  node2 node 2
 * @return       1 if equal 0 if not
 */
static int equals(p_node node1, p_node node2) {
    if (node1 == NULL || node2 == NULL)
        return 0;
    return node1->key == node2->key;
}

/**
 * has left
 * @param  node node to be checked
 * @return      1 if does, 0 otherwise
 */
static int has_left(p_node node) {return node->left != NULL;}

/**
 * has right
 * @param  node node to be checked
 * @return      1 if does, 0 otherwise
 */
static int has_right(p_node node) {return node->right != NULL;}

/**
 * min in relation to node
 * @param  node node to be evaluated
 * @return      node to the furthest left
 */
static p_node min(p_node root) {
    if (root == NULL)
        return root;
    while (has_left(root))
        root = root->left;
    return root;
}

/**
 * max in relation to node
 * @param  node node to be evaluated
 * @return      node to the furthest right
 */
static p_node max(p_node root) {
    if (root == NULL)
        return root;
    while (has_right(root))
        root = root->right;
    return root;
}

/**
 * is empty
 * @param  treap tree to be checked
 * @return     1 if empty, 0 otherwise
 */
static int is_empty(p_treap treap) {return treap->root == NULL;}

/**
 * create node
 * @param  value node value
 * @return       pointer to new node
 */
static p_node create_node(long int key) {
    p_node new = malloc(sizeof(struct Node));
    new->key = key;
    new->priority = rand();
    new->left = NULL;
    new->right = NULL;
    return new;
}

/*
 * rotate right
 * @param   node to be rotated
 * @return      rotate tree
 */
static p_node rotate_right(p_node A) {
    p_node B = A->left;

    A->left = B->right;
    B->right = A;
    return B;
}

/*
 * rotate left
 * @param   node to be rotated
 * @return      rotate tree
 */
static p_node rotate_left(p_node B) {
    p_node A = B->right;

    B->right = A->left;
    A->left = B;
    return A;
}

/**
 * insert new node
 * @param root root
 * @param node    node to be inserted
 */
static p_node insert_new(p_node root, p_node node) {
    if (root == NULL)
        return node;
    if (compare(root, node)) {
        root->left = insert_new(root->left, node);
        if (root->left->priority > root->priority)
            root = rotate_right(root);
    }
    else {
        root->right = insert_new(root->right, node);
        if (root->right->priority > root->priority)
            root = rotate_left(root);
    }
    return root;
}

/**
 * find node
 * @param  root current root
 * @param  node node to be found (by value, not reference)
 * @return      pointer to equivalent node inside tree
 */
static p_node find_node(p_node root, p_node node) {
    while (root != NULL && !equals(root, node)) {
        if (compare(root, node))
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

/**
 * delete node from tree
 * @param  root root of the tree
 * @param  node node to be deleted
 * @return      root of the new tree
 */
static p_node delete_node(p_node root, p_node node) {
    p_node temp;

    if (root == NULL)
        return root;
    if (root != node) {
        if (compare(root, node))
            root->left = delete_node(root->left, node);
        else
            root->right = delete_node(root->right, node);
    }
    else if (!has_right(root)) {
        temp = root->left;
        free(root);
        root = temp;
    }
    else if (!has_left(root)) {
        temp = root->right;
        free(root);
        root = temp;
    }
    else if (root->left->priority < root->right->priority) {
        root = rotate_left(root);
        root->left = delete_node(root->left, node);
    }
    else {
        root = rotate_right(root);
        root->right = delete_node(root->right, node);
    }
    return root;
}

/**
 * create tree
 * @return  pointer to tree
 */
p_treap create_treap(void) {
    p_treap treap = malloc(sizeof(Treap));
    p_treap *tmp = realloc(treaps, sizeof(Treap) * (n_treaps + 1));
    srand(time(NULL));
    treaps = tmp;
    treaps[n_treaps] = treap;
    n_treaps++;
    treap->root = NULL;
    return treap;
}

/**
 * push to tree
 * @param treap     tree
 * @param key   key to be pushed
 */
void push(p_treap treap, long int key) {
    p_node new = create_node(key);
    if (is_empty(treap)) {
        treap->root = new;
        return;
    }
    treap->root = insert_new(treap->root, new);
}

/**
 * search tree
 * @param  treap   tree
 * @param  value value to be found
 * @return       pointer to found node
 */
p_node search(p_treap treap, long int key) {
    p_node tmp = create_node(key);
    p_node node = find_node(treap->root, tmp);
    free(tmp);
    return node;
}

/**
 * get min
 * @param  treap  tree
 * @return      node with lowest key
 */
p_node get_min(p_treap treap) {
    return min(treap->root);
}

/**
 * get max
 * @param  treap  tree
 * @return      node with max key
 */
p_node get_max(p_treap treap) {
    return max(treap->root);
}

/**
 * pop
 * @param treap  tree
 * @param node node to be removed
 */
void pop(p_treap treap, p_node node) {
    p_node tmp;
    tmp = delete_node(treap->root, node);
    treap->root = tmp;
}

/**
 * Frees a treap using DFS
 * @param node node of treap to free
 */
void free_treap(p_node node) {
    if (node == NULL)
        return;
    free_treap(node->left);
    free_treap(node->right);
    free(node);
}

/**
 * Frees all initialized treaps
 */
void free_treaps(void) {
    int i;
    for (i = 0; i < n_treaps; i++) {
        free_treap(treaps[i]->root);
        free(treaps[i]);
    }
    free(treaps);
}
