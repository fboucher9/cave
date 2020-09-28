/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_func.h>
#include <cv_debug/cv_debug.h>
#include <cv_algo/cv_list_root.h>
#include <cv_algo/cv_callstack.h>
#include <cv_misc/cv_thread_local.h>
#include <cv_clock/cv_clock_tick.h>
#include <cv_clock/cv_clock_tool.h>

enum cv_trace_func_const {
    cv_trace_func_depth_max = 32
};

/*
 *
 */

struct cv_trace_func_stack {
    cv_trace_func * p_this;
    void * p_padding[1u];
    /* -- */
    cv_clock_tick o_clock;
};

/*
 *
 */

struct cv_trace_func_local {
    unsigned long i_depth;
    unsigned long l_padding[1u];
    /* -- */
    struct cv_trace_func_stack a_stack[cv_trace_func_depth_max];
};

cv_debug_decl_(g_trace_func_class, "cv_trace_func");

static cv_list_root g_trace_func_list = {0};

static cv_thread_local_ struct cv_trace_func_local g_local = {0};

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
    char const * p_name) {
    cv_debug_construct_(g_trace_func_class, p_this);
    cv_list_node_init(&p_this->o_node);
    p_this->p_symbol = p_name;
    cv_trace_count_init(&p_this->o_call, p_name, "call");
    cv_trace_count_init(&p_this->o_elapsed, p_name, "elapsed");
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
    cv_trace_count_cleanup(&p_this->o_elapsed);
    cv_trace_count_cleanup(&p_this->o_call);
    p_this->p_symbol = 0;
    cv_list_node_cleanup(&p_this->o_node);
    cv_debug_destruct_(g_trace_func_class, p_this);
}

/*
 *
 */

void cv_trace_func_enter( cv_trace_func * p_this) {
    cv_callstack_push(p_this->p_symbol);
    if (g_local.i_depth < cv_trace_func_depth_max) {
        g_local.a_stack[g_local.i_depth].p_this = p_this;
        cv_clock_tick_read(&g_local.a_stack[g_local.i_depth].o_clock);
    }
    g_local.i_depth ++;
}

/*
 *
 */

void cv_trace_func_leave(void) {
    cv_trace_func * p_this = 0;
    cv_callstack_pop();
    if (g_local.i_depth) {
        g_local.i_depth --;
        if (g_local.i_depth < cv_trace_func_depth_max) {
            cv_clock_tick o_enter_clock = {0};
            cv_clock_tick o_leave_clock = {0};
            cv_ull i_enter_clock = 0;
            cv_ull i_leave_clock = 0;
            cv_ull i_elapsed = 0;
            o_enter_clock = g_local.a_stack[g_local.i_depth].o_clock;
            i_enter_clock = cv_clock_get(&o_enter_clock.o_clock);
            cv_clock_tick_read(&o_leave_clock);
            i_leave_clock = cv_clock_get(&o_leave_clock.o_clock);
            i_elapsed = i_leave_clock - i_enter_clock;
            p_this = g_local.a_stack[g_local.i_depth].p_this;
            cv_trace_count_add(&p_this->o_call, 1);
            cv_trace_count_add(&p_this->o_elapsed, i_elapsed);
        }
    }
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

/*
 *
 */

void cv_trace_func_it_init( cv_trace_func_it * p_this ) {
    cv_list_it_init( &p_this->o_list_it, &g_trace_func_list);
}

/*
 *
 */

void cv_trace_func_it_cleanup( cv_trace_func_it * p_this ) {
    cv_list_it_cleanup( &p_this->o_list_it);
}

/*
 *
 */

cv_bool cv_trace_func_it_next( cv_trace_func_it * p_this,
    cv_trace_func_ptr * r_trace_func_ptr) {
    return cv_list_it_next( &p_this->o_list_it,
        &r_trace_func_ptr->o_list_ptr);
}

/* end-of-file: cv_trace_func.c */
