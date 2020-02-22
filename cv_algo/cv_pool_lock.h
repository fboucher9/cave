/* See LICENSE for license details */

#ifndef cv_pool_lock_h_
#define cv_pool_lock_h_

/*
 *  Module: cv_pool_lock.h
 *
 *  Description: Thread-safe version of cv_pool.
 */

#include <cv_algo/cv_pool_pred.h>
#include <cv_algo/cv_pool.h>
#include <cv_thread/cv_mutex.h>

struct cv_pool_lock {
    cv_mutex o_mutex;
    cv_pool o_pool;
};

cv_bool cv_pool_lock_init(
    cv_pool_lock * p_this,
    cv_pool_desc const * p_desc);

void cv_pool_lock_cleanup(
    cv_pool_lock * p_this);

void * cv_pool_lock_alloc(
    cv_pool_lock * p_this);

void cv_pool_lock_free(
    cv_pool_lock * p_this,
    void * p_buffer);

#endif /* #ifndef cv_pool_lock_h_ */

/* end-of-file: cv_pool_lock.h */
