/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_pool_desc.h>
#include <cv_debug.h>
#include <cv_sizeof.h>

/*
 *
 */

void cv_pool_desc_init( cv_pool_desc * p_desc) {
    cv_debug_init_(p_desc, cv_sizeof_(*p_desc));
    p_desc->i_len = 0;
}

/*
 *
 */

void cv_pool_desc_cleanup( cv_pool_desc * p_desc) {
    cv_debug_cleanup_(p_desc, cv_sizeof_(*p_desc));
}

/* end-of-file: cv_pool_desc.c */
