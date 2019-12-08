/* See LICENSE for license details */

#ifndef cv_mutex_impl_h_
#define cv_mutex_impl_h_

#include <cv_thread/cv_mutex_pred.h>

#include <cv_misc/cv_types.h>

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
#define cv_mutex_initializer_ { cv_null_ }
#endif /* #if defined cv_have_pthread_ */

#endif /* #ifndef cv_mutex_impl_h_ */
