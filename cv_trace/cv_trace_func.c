/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_func.h>
#include <cv_debug/cv_debug.h>
#include <cv_algo/cv_list_root.h>
#include <cv_algo/cv_callstack.h>

cv_debug_decl_(cv_trace_func_class);

static cv_list_root g_trace_func_list = {0};

/*
 *
 */

void cv_trace_func_load(void) {
    cv_list_root_init(&g_trace_func_list);
}

/*
 *
 */

void cv_trace_func_unload(void) {
    cv_list_root_cleanup(&g_trace_func_list);
}

/*
 *
 */

void cv_trace_func_init( cv_trace_func * p_this,
    cv_array const * p_name) {
    cv_debug_construct_(cv_trace_func_class, p_this);
    cv_list_node_init(&p_this->o_node);
    cv_array_init_ref(&p_this->o_symbol, p_name);
    p_this->i_count = 0;
    p_this->i_elapsed = 0;
    /* lock of global mutex */
    cv_list_join(&p_this->o_node, &g_trace_func_list.o_node);
    /* unlock of global mutex */
}

/*
 *
 */

void cv_trace_func_cleanup( cv_trace_func * p_this) {
    /* lock of global mutex */
    cv_list_join(&p_this->o_node, &p_this->o_node);
    /* unlock of global mutex */
    cv_array_cleanup(&p_this->o_symbol);
    cv_list_node_cleanup(&p_this->o_node);
    cv_debug_destruct_(cv_trace_func_class, p_this);
}

/*
 *
 */

cv_array const * cv_trace_func_get_symbol( cv_trace_func const * p_this) {
    return &p_this->o_symbol;
}

/*
 *
 */

void cv_trace_func_enter( cv_trace_func * p_this) {
    cv_callstack_push(&p_this->o_symbol);
}

/*
 *
 */

void cv_trace_func_leave(void) {
    cv_callstack_pop();
}

/*
 *
 */

void cv_trace_func_pause(void) {
}

/*
 *
 */

void cv_trace_func_resume(void) {
}

/* end-of-file: cv_trace_func.c */
