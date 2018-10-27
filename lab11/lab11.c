#include "treap.h"
#include <stdio.h>

void build_set(void) {
    p_treap treap = create_treap();
    long int set_size, i, value;
    /* get set size */
    scanf(" %ld", &set_size);
    for (i = 0; i < set_size; i++) {
        scanf(" %ld", &value);
        push(treap, value);
    }
}

void build_symmetric_difference() {
    /* build the symmetric difference
     * between the last created set
     * and the on still in stdin
     */
    p_treap diff, old, new;
    p_node node1, node2;

    /* build the set from stdin */
    build_set();

    /* for each element from the
     * previous treap, check if it
     * exists within the newly created
     * one. if it does pop from both.
     * if it does not, pop from the previous
     * and add to diff
     *
     * after that, traverse the new treap
     * and add all of its elements to
     * diff.
     */

    old = treaps[n_treaps - 2];
    new = treaps[n_treaps - 1];

    /* create a new treap to hold the diff */
    diff = create_treap();

    while ((node1 = get_max(old)) != NULL) {
        if ((node2 = search(new, node1->key)) != NULL) {
            pop(new, node2);
        }
        else {
            push(diff, node1->key);
        }
        pop(old, node1);
    }
    while ((node2 = get_max(new)) != NULL) {
        push(diff, node2->key);
        pop(new, node2);
    }
}


int main(int argc, char const *argv[]) {
    p_treap last_diff;
    p_node node;
    long int n_sets, i;

    /* get number of sets */
    scanf(" %ld", &n_sets);

    /* for each set */
    for (i = 0; i < n_sets; i++) {
        if (i == 0)
            build_set();
        else
            build_symmetric_difference();
    }

    /* after all values have been set
     * traverse the last diff tree finding the max
     * values. if they have .found as 0, print them.
     * after that, pop and go to the next
     */

    last_diff = treaps[n_treaps - 1];

    while ((node = get_max(last_diff)) != NULL) {
        printf("%ld ", node->key);
        pop(last_diff, node);
    }
    printf("\n");
    return 0;
}
