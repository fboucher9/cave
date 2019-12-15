/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_pool_desc.h>
#include <cv_debug/cv_debug.h>
#include <cv_misc/cv_sizeof.h>

cv_debug_decl_(g_class);

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
    cv_unused_(p_desc);
    cv_debug_destruct_(g_class, p_desc);
}

/* end-of-file: cv_pool_desc.c */
