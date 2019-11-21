/* See LICENSE for license details */

#ifndef cv_mutex_pool_h_
#define cv_mutex_pool_h_

#include <cv_mutex_pred.h>

#include <cv_bool.h>

cv_bool cv_mutex_pool_load(void);

void cv_mutex_pool_unload(void);

cv_mutex * cv_mutex_pool_alloc(void);

void cv_mutex_pool_free(
    cv_mutex * p_mutex);

#endif /* #ifndef cv_mutex_pool_h_ */

/* end-of-file: cv_mutex_pool.h */
