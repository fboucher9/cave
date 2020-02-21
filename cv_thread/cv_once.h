/* See LICENSE for license details */

#ifndef cv_once_h_
#define cv_once_h_

/*
 *  Module: cv_once.h
 *
 *  Description: Simplified version of pthread_once_t
 */

#include <cv_thread/cv_once_pred.h>
#include <cv_thread/cv_mutex.h>
#include <cv_misc/cv_bool.h>

/*
 *  Structure: cv_once
 *
 *  Description: Storage for simplified pthread_once_t
 */

struct cv_once {
    cv_mutex o_mutex;
    /* -- */
    union cv_once_done {
        cv_bool b_done;
        void * pv_padding[1u];
    } o_done;
};

#define cv_once_initializer_ { cv_mutex_initializer_ }

void cv_once_init(struct cv_once * p_this);

void cv_once_cleanup(struct cv_once * p_this);

cv_bool cv_once_lock(struct cv_once * p_this);

void cv_once_unlock(struct cv_once * p_this);

#endif /* #ifndef cv_once_h_ */

/* end-of-file: cv_once.h */
