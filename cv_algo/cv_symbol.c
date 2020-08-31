/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_symbol.h>
#include <cv_algo/cv_array.h>

enum cv_symbol_const {
    cv_symbol_key_max = 1024
};

static cv_bool g_symbol_valid[cv_symbol_key_max] = {0};

static cv_array g_symbol_name[cv_symbol_key_max];

static unsigned short g_symbol_count = 0;

/*
 *
 */

void cv_symbol_load(void) {
    static unsigned char const g_symbol_null[] = { 'n', 'u', 'l', 'l' };
    cv_array_init_vector(g_symbol_name + 0u, g_symbol_null,
        sizeof g_symbol_null);
    g_symbol_valid[0u] = cv_true;
    g_symbol_count = 1;
}

/*
 *
 */

void cv_symbol_unload(void) {
    unsigned short i_symbol_key = 0;
    while (i_symbol_key < g_symbol_count) {
        if (g_symbol_valid[i_symbol_key]) {
            cv_array_cleanup(g_symbol_name + i_symbol_key);
            g_symbol_valid[i_symbol_key] = cv_false;
        }
        i_symbol_key ++;
    }
}

/*
 *
 */

unsigned short cv_symbol_register( cv_array const * p_name) {
    unsigned short i_symbol_key = 0;
    if (p_name) {
        if (g_symbol_count < cv_symbol_key_max) {
            i_symbol_key = g_symbol_count;
            g_symbol_count ++;
            cv_array_init_ref(g_symbol_name + i_symbol_key, p_name);
            g_symbol_valid[i_symbol_key] = cv_true;
        }
    }
    return i_symbol_key;
}

/*
 *
 */

void cv_symbol_unregister(unsigned short i_symbol_key) {
    if (i_symbol_key < g_symbol_count) {
        if (g_symbol_valid[i_symbol_key]) {
            cv_array_cleanup(g_symbol_name + i_symbol_key);
            g_symbol_valid[i_symbol_key] = cv_false;
        }
    }
}

/*
 *
 */

cv_bool cv_symbol_query( unsigned short i_symbol_key, cv_array * r_name) {
    cv_bool b_result = cv_false;
    if (i_symbol_key < g_symbol_count) {
        if (g_symbol_valid[i_symbol_key]) {
            *r_name = g_symbol_name[i_symbol_key];
            b_result = cv_true;
        }
    }
    return b_result;
}

/* end-of-file: cv_symbol.c */
