/* See LICENSE for license details */

#ifndef cv_heap_node_h_
#define cv_heap_node_h_

#include <cv_heap_pred.h>
#include <cv_list_node.h>
#include <cv_array.h>
#include <cv_bool.h>

struct cv_heap_node
{
    cv_list_node o_node;
    /* -- */
    char const * a_stack[4u];
    /* -- */
    cv_array o_payload;
    /* -- */
    /* payload follows ... */
};

cv_bool cv_heap_node_load(void);

void cv_heap_node_unload(void);

void cv_heap_node_cleanup(
    cv_heap_node * p_this);

cv_heap_node * cv_heap_node_create(
    cv_array const * p_payload);

#endif /* #ifndef cv_heap_node_h_ */
