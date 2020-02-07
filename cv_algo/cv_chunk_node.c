/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_chunk_node.h>
#include <cv_debug/cv_debug_class.h>

cv_debug_decl_(g_chunk_node_class);

/*
 *
 */

void cv_chunk_node_init(cv_chunk_node * p_this) {
    cv_debug_construct_(g_chunk_node_class, p_this);
    cv_list_node_init(&p_this->o_node);
}

/*
 *
 */

void cv_chunk_node_cleanup(cv_chunk_node * p_this) {
    cv_list_join(&p_this->o_node, &p_this->o_node);
    cv_list_node_cleanup(&p_this->o_node);
    cv_debug_destruct_(g_chunk_node_class, p_this);
}

/* end-of-file: cv_chunk_node.c */
