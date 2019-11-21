/* See LICENSE for license details */

#ifndef cv_mutex_h_
#define cv_mutex_h_

#include <cv_mutex_pred.h>

#include <cv_bool.h>

/* see cv_mutex_impl.h for cv_mutex members */

long cv_mutex_sizeof(void);

cv_bool cv_mutex_init(
    cv_mutex * p_this);

void cv_mutex_cleanup(
    cv_mutex * p_this);

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
