/* See LICENSE for license details */

#ifndef cv_mutex_impl_h_
#define cv_mutex_impl_h_

#include <cv_thread/cv_mutex_pred.h>

#if defined cv_have_pthread_
#include <pthread.h>
#endif /* #if defined cv_have_pthread_ */

/*

Members for cv_mutex object.

*/
union cv_mutex
{
#if defined cv_have_pthread_
    pthread_mutex_t o_private;

    void * a_padding[
        (sizeof(pthread_mutex_t) + sizeof(void *) - 1) /
            sizeof(void *) ];
#else /* #if defined cv_have_pthread_ */
    void * o_private;
#endif /* #if defined cv_have_pthread_ */

};

/* Macro used to initialize a static instance of cv_mutex object */
#if defined cv_have_pthread_
#define cv_mutex_initializer_ { PTHREAD_MUTEX_INITIALIZER }
#else /* #if defined cv_have_pthread_ */
#define cv_mutex_initializer_ { 0 }
#endif /* #if defined cv_have_pthread_ */

int cv_mutex_impl_init(
    cv_mutex * p_this);

int cv_mutex_impl_cleanup(
    cv_mutex * p_this);

int cv_mutex_impl_lock(
    cv_mutex * p_this);

int cv_mutex_impl_unlock(
    cv_mutex * p_this);

#endif /* #ifndef cv_mutex_impl_h_ */
