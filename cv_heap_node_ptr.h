/* See LICENSE for license details */

#ifndef cv_heap_ptr_h_
#define cv_heap_ptr_h_

#include <cv_heap_pred.h>

#include <cv_node_ptr.h>

#include <cv_ptr.h>

union cv_heap_node_ptr
{
    void const * pc_void;
    void * p_void;
    cv_node_ptr o_node_ptr;
    cv_heap_node * p_heap_node;
    cv_heap_node const * pc_heap_node;
};

void * cv_heap_node_to_payload(
    cv_heap_node * p_heap_node);

cv_heap_node * cv_heap_node_from_payload(
    void * p_void);

#endif /* #ifndef cv_heap_ptr_h_ */
