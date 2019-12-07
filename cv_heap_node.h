/* See LICENSE for license details */

#ifndef cv_heap_node_h_
#define cv_heap_node_h_

/*
 *
 */

#include <cv_heap_pred.h>
#include <cv_list_node.h>
#include <cv_array.h>
#include <cv_bool.h>
#include <cv_heap_section_lock.h>

/*
 *
 */

struct cv_heap_node {
    cv_list_node o_node;
    /* -- */
    char const * a_stack[4u];
    /* -- */
    cv_array o_payload;
    /* -- */
    /* payload follows ... */
};

/*
 *
 */

struct cv_heap_node_mgr {
    cv_heap_section_lock o_heap_section_lock;
};

#define cv_heap_node_mgr_initializer_ \
{ cv_heap_section_lock_initializer_ }

cv_bool cv_heap_node_mgr_init( cv_heap_node_mgr * p_this);

void cv_heap_node_mgr_cleanup( cv_heap_node_mgr * p_this);

void cv_heap_node_mgr_release( cv_heap_node_mgr * p_heap_node_mgr,
    cv_heap_node * p_heap_node);

cv_heap_node * cv_heap_node_mgr_acquire( cv_heap_node_mgr * p_heap_node_mgr,
    cv_array const * p_payload);

#endif /* #ifndef cv_heap_node_h_ */
