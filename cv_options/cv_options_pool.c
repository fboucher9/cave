/* See LICENSE for license details */

/*

Module: cv_options_pool.c

Description: Memory allocation pool for cv_options_node objects.

*/

#include <cv_options/cv_options_pool.h>
#include <cv_algo/cv_pool_lock.h>
#include <cv_options/cv_options_node.h>
#include <cv_options/cv_options_node_ptr.h>
#include <cv_misc/cv_sizeof.h>
#include <cv_debug.h>

cv_debug_decl_(g_class);

typedef struct cv_options_pool cv_options_pool;

struct cv_options_pool {
    cv_pool_lock o_pool;
};

#define cv_options_pool_initializer_ \
{ cv_pool_lock_initializer_ }

static cv_bool g_options_pool_loaded = cv_false;
static cv_options_pool g_options_pool = cv_options_pool_initializer_;

/*
 *
 */

cv_bool cv_options_pool_load(void) {
    cv_bool b_result = cv_false;
    cv_debug_assert_( !g_options_pool_loaded, cv_debug_code_already_loaded);
    cv_debug_construct_(g_class, &g_options_pool);
    {
        cv_pool_desc o_desc = cv_pool_desc_initializer_;
        o_desc.i_len = cv_sizeof_(cv_options_node);
        if (cv_pool_lock_init(&g_options_pool.o_pool, &o_desc)) {
            g_options_pool_loaded = cv_true;
            b_result = cv_true;
        }
    }
    return b_result;
}

/*
 *
 */

void cv_options_pool_unload(void) {
    cv_debug_assert_( g_options_pool_loaded, cv_debug_code_already_unloaded);
    cv_pool_lock_cleanup(&g_options_pool.o_pool);
    cv_debug_destruct_(g_class, &g_options_pool);
    g_options_pool_loaded = cv_false;
}

/*
 *
 */

cv_options_node * cv_options_pool_alloc(void) {
    cv_options_node_ptr o_placement = cv_ptr_null_;
    cv_debug_assert_( g_options_pool_loaded, cv_debug_code_not_loaded);
    o_placement.o_list_ptr.p_void = cv_pool_lock_alloc(
        &g_options_pool.o_pool);
    return o_placement.p_options_node;
}

/*
 *
 */

void cv_options_pool_free( cv_options_node * p_options_node) {
    cv_debug_assert_( g_options_pool_loaded, cv_debug_code_not_loaded);
    cv_debug_assert_( p_options_node, cv_debug_code_null_ptr);
    {
        cv_options_node_ptr o_placement = cv_ptr_null_;
        o_placement.p_options_node = p_options_node;
        cv_pool_lock_free(&g_options_pool.o_pool,
            o_placement.o_list_ptr.p_void);
    }
}

