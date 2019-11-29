/* See LICENSE for license details */

#ifndef cv_heap_node_h_
#define cv_heap_node_h_

#include <cv_heap_pred.h>

#include <cv_node.h>

#include <cv_bool.h>

struct cv_heap_node
{
    cv_node o_node;
    /* -- */
    char const * a_stack[4u];
    /* -- */
    long i_len;
    long l_padding[1u];
    /* -- */
    /* payload follows ... */
};

void cv_heap_node_init(
    cv_heap_node * p_this,
    long i_len);

void cv_heap_node_cleanup(
    cv_heap_node * p_this);

cv_heap_node * cv_heap_node_create(
    long i_len);

#endif /* #ifndef cv_heap_node_h_ */
