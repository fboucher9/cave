/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_pool_desc.h>
#include <cv_debug.h>
#include <cv_misc/cv_sizeof.h>

cv_debug_class_decl_(g_class);

/*
 *
 */

void cv_pool_desc_init( cv_pool_desc * p_desc) {
    cv_debug_construct_(p_desc);
    cv_debug_class_init_(g_class);
    p_desc->i_len = 0;
}

/*
 *
 */

void cv_pool_desc_cleanup( cv_pool_desc * p_desc) {
    cv_debug_destruct_(p_desc);
    cv_debug_class_cleanup_(g_class);
}

/* end-of-file: cv_pool_desc.c */
