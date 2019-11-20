/* See LICENSE for license details */

#ifndef cv_heap_pool_impl_h_
#define cv_heap_pool_impl_h_

#include <cv_heap_pred.h>

#include <cv_mutex_pred.h>

#include <cv_list.h>

#include <cv_null.h>

union cv_heap_pool_ptr
{
    void const * pc_void;
    void * p_void;
    cv_heap_pool const * pc_heap_pool;
    cv_heap_pool * p_heap_pool;
};

#define cv_heap_pool_ptr_null_ { cv_null_ }

struct cv_heap_pool
{
    cv_mutex * p_mutex; /* safety first */
    void * pv_padding[1u];
    /* -- */
    cv_list o_used_list; /* list of allocations */
    /* -- */
    cv_list o_free_list; /* list of unused */
    /* -- */
    long i_len;
    long l_padding[1u];
};

#define cv_heap_pool_initializer_ { \
    cv_null_, \
    { 0 }, \
    cv_list_initializer_, \
    cv_list_initializer_, \
    0, \
    { 0 }

char cv_heap_pool_init(
    cv_heap_pool * p_this,
    long i_len);

void cv_heap_pool_cleanup(
    cv_heap_pool * p_this);

#endif /* #ifndef cv_heap_pool_impl_h_ */
