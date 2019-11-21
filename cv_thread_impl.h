/* See LICENSE for license details */

#ifndef cv_thread_impl_h_
#define cv_thread_impl_h_

#include <cv_thread_pred.h>

#include <cv_thread_desc.h>

#include <pthread.h>

struct cv_thread
{
    cv_thread_desc o_desc;
    pthread_t o_handle;
};

cv_bool cv_thread_init(
    cv_thread * p_this,
    cv_thread_desc const * p_thread_desc);

void cv_thread_cleanup(
    cv_thread * p_this);

#endif /* #ifndef cv_thread_impl_h_ */
