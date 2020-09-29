/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_callstack.h>
#include <cv_misc/cv_thread_local.h>
#include <cv_misc/cv_limits.h>

enum cv_callstack_const {
    cv_callstack_depth_max = 64
};

static cv_thread_local_ unsigned char g_callstack_type[cv_callstack_depth_max];

static cv_thread_local_ union cv_callstack_value g_callstack_table[cv_callstack_depth_max];

static cv_thread_local_ unsigned long g_callstack_depth = 0;

static void cv_callstack_push( unsigned char e_type,
    union cv_callstack_value o_value) {
    if (g_callstack_depth < cv_callstack_depth_max) {
        g_callstack_type[g_callstack_depth] = e_type;
        g_callstack_table[g_callstack_depth] = o_value;
    }
    g_callstack_depth ++;
}

unsigned long cv_callstack_enter( char const * p_symbol) {
    unsigned long const i_stack_pointer = g_callstack_depth;
    union cv_callstack_value o_value;
    o_value.p_text = p_symbol;
    cv_callstack_push(cv_callstack_type_function, o_value);
    return i_stack_pointer;
}

void cv_callstack_push_string( char const * p_string) {
    union cv_callstack_value o_value;
    o_value.p_text = p_string;
    cv_callstack_push(cv_callstack_type_string, o_value);
}

void cv_callstack_push_number( cv_uptr i_number) {
    union cv_callstack_value o_value;
    o_value.i_number = i_number;
    cv_callstack_push(cv_callstack_type_number, o_value);
}

void cv_callstack_leave(unsigned long i_stack_pointer) {
    g_callstack_depth = i_stack_pointer;
}

unsigned char cv_callstack_count(void) {
    unsigned char i_callback_depth = cv_callstack_depth_max;
    if (g_callstack_depth < cv_callstack_depth_max) {
        i_callback_depth = g_callstack_depth & cv_unsigned_char_max_;
    }
    return i_callback_depth;
}

unsigned char cv_callstack_query( unsigned char i_index,
    union cv_callstack_value * r_value) {
    unsigned char e_type = 0;
    if (i_index < g_callstack_depth) {
        e_type = g_callstack_type [g_callstack_depth - 1 - i_index];
        *r_value = g_callstack_table [g_callstack_depth - 1 - i_index];
    }
    return e_type;
}

/* end-of-file: cv_callstack.c */
