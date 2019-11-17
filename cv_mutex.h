/* See LICENSE for license details */

#ifndef cv_mutex_h_
#define cv_mutex_h_

#include <cv_mutex_pred.h>

/* see cv_mutex_impl.h for cv_mutex members */

cv_mutex * cv_mutex_create(void);

void cv_mutex_destroy(
    cv_mutex * p_this);

void cv_mutex_lock(
    cv_mutex * p_this);

void cv_mutex_unlock(
    cv_mutex * p_this);

#if 0

long cv_mutex_get_handle_len(void);

void * cv_mutex_get_handle(
    cv_mutex * p_this);

#endif

#endif /* #ifndef cv_mutex_h_ */
