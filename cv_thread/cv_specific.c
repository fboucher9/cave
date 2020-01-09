/* See LICENSE for license details */

/*
 *
 */

#include <cv_thread/cv_specific.h>

/*
 *
 */

cv_bool cv_specific_init( struct cv_specific * p_this,
    cv_specific_destructor * p_destructor) {
    cv_bool b_result = cv_false;
#if defined cv_have_pthread_
    int const i_pthread_result = pthread_key_create(&p_this->u.o_handle,
        p_destructor);
    if (0 == i_pthread_result) {
        b_result = cv_true;
    }
#else /* #if defined cv_have_pthread_ */
    (void)p_destructor;
    p_this->u.o_handle.p_value = 0;
    b_result = cv_true;
#endif /* #if defined cv_have_pthread_ */
    return b_result;
}

/*
 *
 */

void cv_specific_cleanup( struct cv_specific * p_this) {
    (void)p_this;
}

/*
 *
 */

void cv_specific_set( struct cv_specific * p_this, void const * p_value) {
#if defined cv_have_pthread_
    int const i_pthread_result = pthread_setspecific(
        p_this->u.o_handle, p_value);
    (void)i_pthread_result;
#else /* #if defined cv_have_pthread_ */
    p_this->u.o_handle.pc_value = p_value;
#endif /* #if defined cv_have_pthread_ */
}

/*
 *
 */

void * cv_specific_get( struct cv_specific * p_this) {
    void * p_value = 0;
#if defined cv_have_pthread_
    p_value = pthread_getspecific(p_this->u.o_handle);
#else /* #if defined cv_have_pthread_ */
    p_value = p_this->u.o_handle.p_value;
#endif /* #if defined cv_have_pthread_ */
    return p_value;
}

/* end-of-file: cv_specific.c */
