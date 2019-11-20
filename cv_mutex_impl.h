/* See LICENSE for license details */

#ifndef cv_mutex_impl_h_
#define cv_mutex_impl_h_

#include <cv_mutex_pred.h>

#include <cv_types.h>

#include <pthread.h>

/*

Members for cv_mutex object.

*/
union cv_mutex
{
    pthread_mutex_t o_private;

    cv_ull a_padding[
        (sizeof(pthread_mutex_t) + sizeof(cv_ull) - 1) /
            sizeof(cv_ull) ];

};

/* Macro used to initialize a static instance of cv_mutex object */
#define cv_mutex_initializer_ { PTHREAD_MUTEX_INITIALIZER }

#endif /* #ifndef cv_mutex_impl_h_ */
