/* See LICENSE for license details */

#ifndef cv_thread_impl_h_
#define cv_thread_impl_h_

#include <cv_thread_pred.h>

#include <cv_thread_desc.h>

#include <cv_types.h>

#if defined cv_have_pthread_
#include <pthread.h>
#endif /* #if defined cv_have_pthread_ */

struct cv_thread
{
    cv_thread_desc o_desc;
    /* -- */
#if defined cv_have_pthread_
    union cv_thread_handle
    {
        pthread_t o_handle;
        cv_ull a_padding[
            (sizeof(pthread_t) + sizeof(cv_ull) - 1) /
                sizeof(cv_ull)];
    } u;
#endif /* #if defined cv_have_pthread_ */
};

cv_bool cv_thread_init(
    cv_thread * p_this,
    cv_thread_desc const * p_thread_desc);

void cv_thread_cleanup(
    cv_thread * p_this);

#endif /* #ifndef cv_thread_impl_h_ */
