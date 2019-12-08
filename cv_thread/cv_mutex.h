/* See LICENSE for license details */

#ifndef cv_mutex_h_
#define cv_mutex_h_

/*
 *
 */

#include <cv_thread/cv_mutex_pred.h>
#include <cv_thread/cv_mutex_impl.h>
#include <cv_misc/cv_bool.h>

/* see cv_mutex_impl.h for cv_mutex members */

cv_bool cv_mutex_init(
    cv_mutex * p_this);

void cv_mutex_cleanup(
    cv_mutex * p_this);

void cv_mutex_lock(
    cv_mutex * p_this);

void cv_mutex_unlock(
    cv_mutex * p_this);

#endif /* #ifndef cv_mutex_h_ */
