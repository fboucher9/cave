/* See LICENSE for license details */

#ifndef cv_heap_pool_impl_h_
#define cv_heap_pool_impl_h_

/*
 *
 */

#include <cv_heap/cv_heap_pred.h>
#include <cv_thread/cv_mutex.h>
#include <cv_algo/cv_list_root.h>
#include <cv_misc/cv_null.h>

/*
 *
 */

union cv_heap_pool_ptr
{
    void const * pc_void;
    void * p_void;
    cv_heap_pool const * pc_heap_pool;
    cv_heap_pool * p_heap_pool;
};

/*
 *
 */

struct cv_heap_pool
{
    cv_mutex o_mutex; /* safety first */
    /* -- */
    cv_list_root o_free_list; /* list of unused */
    /* -- */
    long i_len;
    long l_padding[1u];
};

#define cv_heap_pool_initializer_ { \
    cv_mutex_initializer_, \
    cv_list_root_initializer_, \
    0, \
    { 0 } }

cv_bool cv_heap_pool_init(
    cv_heap_pool * p_this,
    long i_len);

void cv_heap_pool_cleanup(
    cv_heap_pool * p_this);

#endif /* #ifndef cv_heap_pool_impl_h_ */
