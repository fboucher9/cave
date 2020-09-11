/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_callstack.h>
#include <cv_misc/cv_thread_local.h>
#include <cv_misc/cv_limits.h>
#include <cv_algo/cv_array.h>

enum cv_callstack_const {
    cv_callstack_depth_max = 64
};

static cv_thread_local_ cv_array g_callstack_table[cv_callstack_depth_max];

static cv_thread_local_ unsigned long g_callstack_depth = 0;

void cv_callstack_push( cv_array const * p_symbol) {
    if (g_callstack_depth < cv_callstack_depth_max) {
        g_callstack_table[g_callstack_depth] = *p_symbol;
    }
    g_callstack_depth ++;
}

void cv_callstack_pop(void) {
    if (g_callstack_depth) {
        g_callstack_depth --;
    }
}

unsigned char cv_callstack_count(void) {
    unsigned char i_callback_depth = cv_callstack_depth_max;
    if (g_callstack_depth < cv_callstack_depth_max) {
        i_callback_depth = g_callstack_depth & cv_unsigned_char_max_;
    }
    return i_callback_depth;
}

cv_array const * cv_callstack_query( unsigned char i_index) {
    cv_array const * p_symbol = 0;
    if (i_index < g_callstack_depth) {
        p_symbol = g_callstack_table + g_callstack_depth - 1 - i_index;
    }
    return p_symbol;
}

