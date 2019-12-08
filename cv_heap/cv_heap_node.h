/* See LICENSE for license details */

#ifndef cv_heap_node_h_
#define cv_heap_node_h_

/*
 *
 */

#include <cv_heap/cv_heap_pred.h>
#include <cv_algo/cv_list_node.h>
#include <cv_algo/cv_array.h>
#include <cv_bool.h>
#include <cv_heap/cv_heap_section_lock.h>

/*
 *
 */

struct cv_heap_node {
    cv_list_node o_node;
    /* -- */
    cv_array o_payload;
    /* -- */
    /* statistics ... */
    /* stack ... */
};

void cv_heap_node_cleanup( cv_heap_node * p_heap_node);

cv_heap_node * cv_heap_node_create( cv_heap_secondary * p_heap_secondary,
    cv_array const * p_payload);

#endif /* #ifndef cv_heap_node_h_ */
