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

static cv_thread_local_ unsigned short
g_callstack_table[cv_callstack_depth_max];

static cv_thread_local_ unsigned long g_callstack_depth = 0;

void cv_callstack_push( unsigned short i_symbol_key) {
    if (g_callstack_depth < cv_callstack_depth_max) {
        g_callstack_table[g_callstack_depth] = i_symbol_key;
    }
    g_callstack_depth ++;
}

void cv_callstack_pop(void) {
    if (g_callstack_depth) {
        g_callstack_depth --;
    }
}

unsigned char cv_callstack_count(void) {
    return g_callstack_depth & cv_unsigned_char_max_;
}

unsigned short cv_callstack_query( unsigned char i_index) {
    unsigned short i_symbol_key = 0;
    if (i_index < g_callstack_depth) {
        i_symbol_key = g_callstack_table[i_index];
    }
    return i_symbol_key;
}

