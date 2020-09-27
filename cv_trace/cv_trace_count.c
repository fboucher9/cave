/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_count.h>
#include <cv_debug/cv_debug.h>
#include <cv_algo/cv_list_root.h>

cv_debug_decl_(g_trace_count_class, "cv_trace_count");

static cv_list_root g_trace_count_root = {0};

/*
 *
 */

void cv_trace_count_load(void) {
    cv_list_root_init(&g_trace_count_root);
}

/*
 *
 */

void cv_trace_count_unload(void) {
    cv_list_root_cleanup(&g_trace_count_root);
}

/*
 *
 */

void cv_trace_count_init( cv_trace_count * p_this, cv_array const * p_parent,
    cv_array const * p_name ) {
    cv_debug_construct_(g_trace_count_class, p_this);
    cv_list_node_init(&p_this->o_node);
    /* lock of global list */
    cv_list_root_append(&g_trace_count_root, &p_this->o_node);
    /* unlock of global list */
    cv_array_init_ref(&p_this->o_parent, p_parent);
    cv_array_init_ref(&p_this->o_name, p_name);
    p_this->i_summary_count = 0;
    p_this->i_period_count = 0;
}

/*
 *
 */

void cv_trace_count_cleanup( cv_trace_count * p_this ) {
    /* lock of global list */
    /* detach from linked list */
    cv_list_join(&p_this->o_node, &p_this->o_node);
    /* unlock of global list */
    p_this->i_summary_count = 0;
    p_this->i_period_count = 0;
    cv_array_cleanup(&p_this->o_name);
    cv_array_cleanup(&p_this->o_parent);
    cv_list_node_cleanup(&p_this->o_node);
    cv_debug_destruct_(g_trace_count_class, p_this);
}

/*
 *
 */

void cv_trace_count_add( cv_trace_count * p_this,
    cv_ull i_increment) {
    p_this->i_summary_count += i_increment;
    p_this->i_period_count += i_increment;
}

/*
 *
 */

void cv_trace_count_it_init( cv_trace_count_it * p_this ) {
    cv_list_it_init(&p_this->o_list_it, &g_trace_count_root);
}

/*
 *
 */

void cv_trace_count_it_cleanup( cv_trace_count_it * p_this ) {
    cv_list_it_cleanup(&p_this->o_list_it);
}

/*
 *
 */

cv_bool cv_trace_count_it_next( cv_trace_count_it * p_this,
    cv_trace_count_ptr * r_trace_count_ptr) {
    return cv_list_it_next(&p_this->o_list_it,
        &r_trace_count_ptr->o_list_ptr);
}

/* end-of-file: cv_trace_count.c */
