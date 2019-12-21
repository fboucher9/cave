/* See LICENSE for license details */

/*
 *
 */

#include <cv_thread/cv_mutex_impl.h>

/*
 *
 */

int cv_mutex_impl_init(
    cv_mutex * p_this) {
    int i_pthread_result = 0;
#if defined cv_have_pthread_
    i_pthread_result = pthread_mutex_init(&p_this->o_private,
        0);
#else /* #if defined cv_have_pthread_ */
    (void)(p_this);
#endif /* #if defined cv_have_pthread_ */
    return i_pthread_result;
}

/*
 *
 */

int cv_mutex_impl_cleanup(
    cv_mutex * p_this) {
    int i_pthread_result = 0;
#if defined cv_have_pthread_
    i_pthread_result = pthread_mutex_destroy(&p_this->o_private);
#else /* #if defined cv_have_pthread_ */
    (void)(p_this);
#endif /* #if defined cv_have_pthread_ */
    return i_pthread_result;
}

/*
 *
 */

int cv_mutex_impl_lock(
    cv_mutex * p_this) {
    int i_pthread_result = 0;
#if defined cv_have_pthread_
    i_pthread_result = pthread_mutex_lock(
        &p_this->o_private);
#else /* #if defined cv_have_pthread_ */
    (void)(p_this);
#endif /* #if defined cv_have_pthread_ */
    return i_pthread_result;
}

/*
 *
 */

int cv_mutex_impl_unlock(
    cv_mutex * p_this) {
    int i_pthread_result = 0;
#if defined cv_have_pthread_
    i_pthread_result = pthread_mutex_unlock(
        &p_this->o_private);
#else /* #if defined cv_have_pthread_ */
    (void)(p_this);
#endif /* #if defined cv_have_pthread_ */
    return i_pthread_result;
}

/* end-of-file: cv_mutex_impl.c */
