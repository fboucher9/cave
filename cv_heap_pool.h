/* See LICENSE for license details */

#ifndef cv_heap_pool_h_
#define cv_heap_pool_h_

#include <cv_heap_pred.h>

cv_heap_pool * cv_heap_pool_load(
    long i_len);

void cv_heap_pool_unload(
    cv_heap_pool * p_this);

void * cv_heap_pool_alloc(
    cv_heap_pool * p_this,
    long i_len);

void cv_heap_pool_free(
    cv_heap_pool * p_this,
    void * p_buf);

#endif /* #ifndef cv_heap_pool_h_ */
