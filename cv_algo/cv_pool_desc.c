/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_pool_desc.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_pool_desc", sizeof(cv_pool_desc));

/*
 *
 */

void cv_pool_desc_init( cv_pool_desc * p_desc) {
    cv_debug_construct_(g_class, p_desc);
    p_desc->i_len = 0;
}

/*
 *
 */

void cv_pool_desc_cleanup( cv_pool_desc * p_desc) {
    (void)p_desc;
    cv_debug_destruct_(g_class, p_desc);
}

/* end-of-file: cv_pool_desc.c */
