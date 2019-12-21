/* See LICENSE for license details */

#ifndef cv_pool_desc_h_
#define cv_pool_desc_h_

/*
 *
 */

#include <cv_algo/cv_pool_pred.h>
#include <cv_misc/cv_types.h>

struct cv_pool_desc {
    cv_uptr i_len;
};

#define cv_pool_desc_initializer_ { 0 }

void cv_pool_desc_init( cv_pool_desc * p_desc);
void cv_pool_desc_cleanup( cv_pool_desc * p_desc);

#endif /* #ifndef cv_pool_desc_h_ */

/* end-of-file: cv_pool_desc.h */
