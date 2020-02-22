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
union cv_mutex_data {
#if defined cv_have_pthread_
    pthread_mutex_t o_private;

    void * a_padding[
        (sizeof(pthread_mutex_t) + sizeof(void *) - 1) /
            sizeof(void *) ];
#else /* #if defined cv_have_pthread_ */
    void * o_private;
#endif /* #if defined cv_have_pthread_ */

};

/*
 *
 */

struct cv_mutex {
    union cv_mutex_data * p_data;
    union cv_mutex_data o_storage;
};

int cv_mutex_impl_init(
    cv_mutex * p_this);

int cv_mutex_impl_cleanup(
    cv_mutex * p_this);

int cv_mutex_impl_lock(
    cv_mutex * p_this);

int cv_mutex_impl_unlock(
    cv_mutex * p_this);

#endif /* #ifndef cv_mutex_impl_h_ */
