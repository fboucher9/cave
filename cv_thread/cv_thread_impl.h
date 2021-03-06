/* See LICENSE for license details */

#ifndef cv_thread_impl_h_
#define cv_thread_impl_h_

/*
 *
 */

#include <cv_thread/cv_thread_pred.h>
#include <cv_thread/cv_thread_desc.h>
#include <cv_misc/cv_types.h>
#if defined cv_have_pthread_
#include <pthread.h>
#endif /* #if defined cv_have_pthread_ */

/*
 *
 */

union cv_thread {
#if defined cv_have_pthread_
    void * a_padding[
        (sizeof(pthread_t) + sizeof(void *) - 1) /
            sizeof(void *)];
    pthread_t o_handle;
#else /* #if defined cv_have_pthread_ */
    void * a_padding[1u];
    void * o_handle;
#endif /* #if defined cv_have_pthread_ */
};

#endif /* #ifndef cv_thread_impl_h_ */
