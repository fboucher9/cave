/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_chunk_it.h>
#include <cv_algo/cv_chunk_root.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_chunk_it, "cv_chunk_it", sizeof(cv_chunk_it));

/*
 *
 */

void cv_chunk_it_init(cv_chunk_it * p_this, cv_chunk_root const * p_root) {
    cv_debug_construct_(g_chunk_it, p_this);
    cv_list_it_init(&p_this->o_list_it, &p_root->o_root);
}

/*
 *
 */

void cv_chunk_it_cleanup(cv_chunk_it * p_this) {
    cv_list_it_cleanup(&p_this->o_list_it);
    cv_debug_destruct_(g_chunk_it, p_this);
}

/*
 *
 */

cv_bool cv_chunk_it_next(cv_chunk_it * p_this, cv_chunk_ptr * r_ptr) {
    return cv_list_it_next(&p_this->o_list_it, &r_ptr->o_list_ptr);
}

/* end-of-file: cv_chunk_it.c */
