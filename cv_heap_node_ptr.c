/* See LICENSE for license details */

#include <cv_heap_node_ptr.h>

#include <cv_heap_node.h>

#include <cv_cast.h>

cv_heap_node * cv_heap_node_from_payload(
    void * p_void)
{
    cv_heap_node_ptr o_heap_ptr = cv_ptr_null_;
    o_heap_ptr.p_void = p_void;
    return o_heap_ptr.p_heap_node - 1;
}

