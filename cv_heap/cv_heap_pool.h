/* See LICENSE for license details */

#ifndef cv_heap_pool_h_
#define cv_heap_pool_h_

#include <cv_heap/cv_heap_pred.h>
#include <cv_heap/cv_heap_pool_impl.h>
#include <cv_misc/cv_types.h>

cv_heap_node * cv_heap_pool_lookup(
    cv_heap_pool * p_this);

cv_heap_node * cv_heap_pool_alloc(
    cv_heap_primary * p_heap_primary,
    cv_heap_secondary * p_heap_secondary,
    cv_uptr i_len);

void cv_heap_pool_free(
    cv_heap_pool * p_this,
    cv_heap_node * p_heap_node);

#endif /* #ifndef cv_heap_pool_h_ */
