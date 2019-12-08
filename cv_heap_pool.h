/* See LICENSE for license details */

#ifndef cv_heap_pool_h_
#define cv_heap_pool_h_

#include <cv_heap_pred.h>

cv_heap_pool * cv_heap_pool_load(
    long i_len);

void cv_heap_pool_unload(
    cv_heap_pool * p_this);

cv_heap_node * cv_heap_pool_alloc(
    cv_heap_pool * p_this,
    cv_heap_node_mgr * p_heap_node_mgr,
    long i_len);

void cv_heap_pool_free(
    cv_heap_pool * p_this,
    cv_heap_node * p_heap_node);

#endif /* #ifndef cv_heap_pool_h_ */
