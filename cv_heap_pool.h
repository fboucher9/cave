/* See LICENSE for license details */

#ifndef cv_heap_pool_h_
#define cv_heap_pool_h_

#include <cv_heap_pred.h>

#include <cv_node.h>

#include <cv_mutex_impl.h>

struct cv_heap_pool
{
    cv_mutex o_mutex; /* safety first */
    /* -- */
    cv_list o_used_list; /* list of allocations */
    /* -- */
    cv_list o_free_list; /* list of unused */
    /* -- */
    long i_len;
    long l_padding[1u];
};

char cv_heap_pool_init(
    cv_heap_pool * p_this,
    long i_len);

void cv_heap_pool_cleanup(
    cv_heap_pool * p_this);

void * cv_heap_pool_alloc(
    cv_heap_pool * p_this,
    long i_len);

void cv_heap_pool_free(
    cv_heap_pool * p_this,
    void * p_buf);

#endif /* #ifndef cv_heap_pool_h_ */
