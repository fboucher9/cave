/* See LICENSE for license details */

#ifndef cv_specific_h_
#define cv_specific_h_

/*
 *
 */

#include <cv_thread/cv_specific_pred.h>
#include <cv_misc/cv_bool.h>

#if defined cv_have_pthread_
#include <pthread.h>
#endif /* #if defined cv_have_pthread_ */

typedef void (cv_specific_destructor)( void * p_value);

/*
 *
 */

struct cv_specific {
    union cv_specific_data {
#if defined cv_have_pthread_
        void * a_padding[
            (sizeof(pthread_key_t) + sizeof(void *) - 1) /
                sizeof(void *)];
        pthread_key_t o_handle;
#else /* #if defined cv_have_pthread_ */
        void * a_padding[1u];
        union cv_specific_handle {
            void const * pc_value;
            void * p_value;
        } o_handle;
#endif /* #if defined cv_have_pthread_ */
    } u;
};

#define cv_specific_initializer_ { { { 0 } } }

cv_bool cv_specific_init( struct cv_specific * p_this,
    cv_specific_destructor * p_destructor);

void cv_specific_cleanup( struct cv_specific * p_this);

void cv_specific_set( struct cv_specific * p_this, void const * p_value);

void * cv_specific_get( struct cv_specific * p_this);

#endif /* #ifndef cv_specific_h_ */

/* end-of-file: cv_specific.h */
