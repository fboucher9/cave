/* See LICENSE for license details */

/*

Module: cv_heap.c

Description: Public memory allocation services.  This module is a replacement
for malloc and free.  The memory allocation strategy is simpler and less
efficient than libc however the design has less fragmentation.  The functions
are thread-safe.

*/

#include <cv_heap/cv_heap.h>
#include <cv_heap/cv_heap_plugin.h>
#include <cv_heap/cv_heap_small.h>
#include <cv_heap/cv_heap_large.h>
#include <cv_heap/cv_heap_node.h>
#include <cv_heap/cv_heap_primary.h>
#include <cv_heap/cv_heap_secondary.h>
#include <cv_heap/cv_heap_used.h>
#include <cv_misc/cv_null.h>
#include <cv_debug/cv_debug.h>
#include <cv_file/cv_file_print.h>
#include <cv_file/cv_file_std.h>
#include <cv_algo/cv_array.h>
#include <cv_algo/cv_array_tool.h>
#include <cv_number_desc.h>
#include <cv_algo/cv_list_root.h>
#include <cv_algo/cv_list_it.h>
#include <cv_misc/cv_sizeof.h>
#include <cv_trace/cv_trace_node.h>

cv_debug_decl_(g_class);

static cv_bool g_heap_loaded = cv_false;

/*
 *
 */

struct cv_heap_mgr {
    cv_heap_primary o_primary;
    cv_heap_secondary o_secondary;
    cv_heap_small o_small;
    cv_heap_large o_large;
    cv_heap_used o_used;
};

#define cv_heap_mgr_initializer_ { \
    cv_heap_primary_initializer_, \
    cv_heap_secondary_initializer_, \
    cv_heap_small_initializer_, \
    cv_heap_large_initializer_, \
    cv_heap_used_initializer_ }

static cv_bool cv_heap_mgr_init(cv_heap_mgr * p_this) {
    cv_bool b_result = cv_false;
    cv_debug_construct_(g_class, p_this);
    if (cv_heap_primary_init(&p_this->o_primary)) {
        if (cv_heap_secondary_init(&p_this->o_secondary)) {
            if (cv_heap_small_init(&p_this->o_small)) {
                if (cv_heap_large_init(&p_this->o_large)) {
                    cv_heap_used_init(&p_this->o_used);
                    b_result = cv_true;
                } else {
                    cv_debug_msg_(cv_debug_code_error);
                }
                if (!b_result) {
                    cv_heap_small_cleanup(&p_this->o_small);
                }
            } else {
                cv_debug_msg_(cv_debug_code_error);
            }
            if (!b_result) {
                cv_heap_secondary_cleanup(&p_this->o_secondary);
            }
        } else {
            cv_debug_msg_(cv_debug_code_error);
        }
        if (!b_result) {
            cv_heap_primary_cleanup(&p_this->o_primary);
        }
    } else {
        cv_debug_msg_(cv_debug_code_error);
    }
    if (!b_result) {
        cv_debug_destruct_(g_class, p_this);
    }
    return b_result;
}

static void cv_heap_mgr_cleanup(cv_heap_mgr * p_this) {
    cv_heap_used_cleanup(&p_this->o_used);
    cv_heap_large_cleanup(&p_this->o_large);
    cv_heap_small_cleanup(&p_this->o_small);
    cv_heap_secondary_cleanup(&p_this->o_secondary);
    cv_heap_primary_cleanup(&p_this->o_primary);
    cv_debug_destruct_(g_class, p_this);
}

static cv_heap_mgr g_heap_mgr = cv_heap_mgr_initializer_;

cv_bool cv_heap_load(void) {
    cv_bool b_result = cv_false;
    cv_heap_mgr * const p_this = &g_heap_mgr;
    cv_debug_assert_(!g_heap_loaded, cv_debug_code_already_loaded);
    if (cv_heap_mgr_init(p_this)) {
        g_heap_loaded = cv_true;
        b_result = cv_true;
    }
    return b_result;
}

/*

Function: cv_heap_unload()

Description: Unload of heap module.  Cleanup global resources allocated during
lifetime of module.

Parameters: none.

Returns: none.

Comments: none.

*/
void cv_heap_unload(void) {
    cv_heap_mgr * const p_this = &g_heap_mgr;
    cv_debug_assert_(g_heap_loaded, cv_debug_code_already_unloaded);
    cv_heap_mgr_cleanup(p_this);
    g_heap_loaded = cv_false;
}

void * cv_heap_alloc( long i_buffer_length) {
    void * p_buffer = cv_null_;
    cv_heap_mgr * const p_this = &g_heap_mgr;
    cv_debug_assert_(g_heap_loaded, cv_debug_code_not_loaded);
    cv_debug_assert_(i_buffer_length > 0, cv_debug_code_invalid_length);
    {
        cv_heap_node * p_heap_node = cv_null_;
        if (i_buffer_length <= cv_heap_small_max_len_) {
            p_heap_node = cv_heap_small_lookup(&p_this->o_small,
                i_buffer_length);
            if (!p_heap_node) {
                p_heap_node = cv_heap_small_alloc(&p_this->o_primary,
                    &p_this->o_secondary, i_buffer_length);
            }
        } else {
            p_heap_node = cv_heap_large_lookup(&p_this->o_large,
                i_buffer_length);
            if (!p_heap_node) {
                p_heap_node = cv_heap_large_alloc(&p_this->o_secondary,
                    i_buffer_length);
            }
        }
        if (p_heap_node) {
            /* Fill in stack info */
            cv_trace_node_stack_query(p_heap_node->a_stack,
                cv_heap_node_stack_max_);
            /* Attach node to used list */
            cv_heap_used_join(&p_this->o_used, p_heap_node);
            p_buffer = p_heap_node->o_payload.o_min.p_void;
        } else {
            cv_debug_msg_(cv_debug_code_out_of_memory);
        }
    }
    return p_buffer;
}

void cv_heap_free( void * p_buffer) {
    cv_heap_mgr * const p_this = &g_heap_mgr;
    cv_debug_assert_(g_heap_loaded, cv_debug_code_not_loaded);
    cv_debug_assert_(p_buffer, cv_debug_code_null_ptr);
    {
        cv_heap_node * const p_heap_node = cv_heap_used_lookup(&p_this->o_used,
            p_buffer);
        if (p_heap_node) {
            long const i_buffer_length = cv_array_len(&p_heap_node->o_payload);
            if (i_buffer_length <= cv_heap_small_max_len_) {
                cv_heap_small_free(&p_this->o_small, p_heap_node);
            } else {
                cv_heap_large_free(&p_this->o_large, p_heap_node);
            }
        }
    }
}

/* end-of-file: cv_heap.c */
