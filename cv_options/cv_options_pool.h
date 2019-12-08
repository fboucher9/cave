/* See LICENSE for license details */

#ifndef cv_options_pool_h_
#define cv_options_pool_h_

#include <cv_options/cv_options_pred.h>

#include <cv_bool.h>

cv_bool cv_options_pool_load(void);

void cv_options_pool_unload(void);

cv_options_node * cv_options_pool_alloc(void);

void cv_options_pool_free(
    cv_options_node * p_options_node);

#endif /* #ifndef cv_options_pool_h_ */

/* end-of-file: cv_options_pool.h */
