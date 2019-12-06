/* See LICENSE for license details */

#ifndef cv_pool_desc_h_
#define cv_pool_desc_h_

/*
 *
 */

#include <cv_pool_pred.h>

struct cv_pool_desc {
    long i_len;
    long l_padding[1u];
};

#define cv_pool_desc_initializer_ { 0, {0} }

void cv_pool_desc_init( cv_pool_desc * p_desc);
void cv_pool_desc_cleanup( cv_pool_desc * p_desc);

#endif /* #ifndef cv_pool_desc_h_ */

/* end-of-file: cv_pool_desc.h */
