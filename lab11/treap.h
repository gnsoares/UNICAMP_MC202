#ifndef TREAP_H
#define TREAP_H

#include <stdlib.h>
#include <time.h>

struct Node {
    struct Node * left;
    struct Node * right;
    long int key;
    int priority;
};

typedef struct Node * p_node;

typedef struct {
    p_node root;
} Treap;

typedef Treap * p_treap;


extern p_treap *treaps;
extern int n_treaps;

/**
 * create tree
 * @return  pointer to tree
 */
p_treap create_treap(void);

/**
 * push to tree
 * @param treap   tree
 * @param key key to be pushed
 */
void push(p_treap treap, long int key);

/**
 * search tree
 * @param  treap   tree
 * @param  value value to be found
 * @return       pointer to found node
 */
p_node search(p_treap treap, long int key);

/**
 * get min
 * @param  treap  tree
 * @return      node with lowest key
 */
p_node get_min(p_treap treap);

/**
 * get max
 * @param  treap  tree
 * @return      node with max key
 */
p_node get_max(p_treap treap);

/**
 * pop
 * @param treap  tree
 * @param node node to be removed
 */
void pop(p_treap treap, p_node node);

/**
 * Frees all initialized treaps
 */
void free_treaps(void) __attribute__((destructor));

#endif
