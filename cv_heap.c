/* See LICENSE for license details */

/*

Module: cv_heap.c

Description: Public memory allocation services.  This module is a replacement
for malloc and free.  The memory allocation strategy is simpler and less
efficient than libc however the design has less fragmentation.  The functions
are thread-safe.

*/

#include <cv_heap.h>
#include <cv_heap_plugin.h>
#include <cv_heap_small.h>
#include <cv_heap_large.h>
#include <cv_heap_node.h>
#include <cv_heap_node_ptr.h>
#include <cv_heap_primary.h>
#include <cv_null.h>
#include <cv_debug.h>
#include <cv_file_print.h>
#include <cv_file_std.h>
#include <cv_array.h>
#include <cv_array_tool.h>
#include <cv_number_desc.h>
#include <cv_list_root.h>
#include <cv_list_it.h>
#include <cv_heap_used.h>

static cv_bool g_heap_loaded = cv_false;

static cv_heap_node_mgr g_heap_node_mgr = cv_heap_node_mgr_initializer_;

static cv_heap_used g_heap_used = cv_heap_used_initializer_;

static cv_heap_small g_heap_small = cv_heap_small_initializer_;

static cv_heap_large g_heap_large = cv_heap_large_initializer_;

cv_bool cv_heap_load(void)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(!g_heap_loaded, cv_debug_code_already_loaded);
    if (cv_heap_primary_load()) {
        if (cv_heap_node_mgr_init(&g_heap_node_mgr)) {
            if (cv_heap_small_init(&g_heap_small)) {
                if (cv_heap_large_init(&g_heap_large)) {
                    cv_heap_used_init(&g_heap_used);
                    g_heap_loaded = cv_true;
                    b_result = cv_true;
                } else {
                    cv_debug_msg_(cv_debug_code_error);
                }
                if (!b_result) {
                    cv_heap_small_cleanup(&g_heap_small);
                }
            } else {
                cv_debug_msg_(cv_debug_code_error);
            }
            if (!b_result) {
                cv_heap_node_mgr_cleanup(&g_heap_node_mgr);
            }
        } else {
            cv_debug_msg_(cv_debug_code_error);
        }
        if (!b_result) {
            cv_heap_primary_unload();
        }
    } else {
        cv_debug_msg_(cv_debug_code_error);
    }
    return b_result;
}

/*

Function: cv_heap_unload()

Description: Unload of heap module.  Cleanup global resources allocated during
lifetime of module.

Parameters: none.

Returns: none.

Comments: There's no thread safety for leak counter, some false detections
may occur.  The sub modules will produce correct leak reports.

*/
void cv_heap_unload(void)
{
    cv_debug_assert_(g_heap_loaded, cv_debug_code_already_unloaded);
    cv_heap_used_cleanup(&g_heap_used);
    cv_heap_large_cleanup(&g_heap_large);
    cv_heap_small_cleanup(&g_heap_small);
    cv_heap_node_mgr_cleanup(&g_heap_node_mgr);
    cv_heap_primary_unload();
    g_heap_loaded = cv_false;
}

void * cv_heap_alloc(
    long i_buffer_length)
{
    void * p_buffer = cv_null_;
    cv_debug_assert_(g_heap_loaded, cv_debug_code_not_loaded);
    if (i_buffer_length > 0) {
        cv_heap_node * p_heap_node = cv_null_;
        if (i_buffer_length <= cv_heap_small_max_len_) {
            p_heap_node = cv_heap_small_alloc(&g_heap_small, &g_heap_node_mgr,
                i_buffer_length);
        } else {
            p_heap_node = cv_heap_large_alloc(&g_heap_large, &g_heap_node_mgr,
                i_buffer_length);
        }
        if (p_heap_node) {
            /* Attach node to used list */
            cv_heap_used_join(&g_heap_used, p_heap_node);
            p_buffer = p_heap_node->o_payload.o_min.p_void;
        } else {
            cv_debug_msg_(cv_debug_code_out_of_memory);
        }
    } else {
        cv_debug_msg_(cv_debug_code_invalid_length);
    }
    return p_buffer;
}

void cv_heap_free(
    void * p_buffer)
{
    cv_debug_assert_(g_heap_loaded, cv_debug_code_not_loaded);
    if (p_buffer) {
        cv_heap_node * const p_heap_node = cv_heap_used_lookup(&g_heap_used,
            p_buffer);
        if (p_heap_node) {
            long const i_buffer_length = cv_array_len(&p_heap_node->o_payload);
            if (i_buffer_length <= cv_heap_small_max_len_) {
                cv_heap_small_free(&g_heap_small, p_heap_node);
            } else {
                cv_heap_large_free(&g_heap_large, p_heap_node);
            }
        }
    } else {
        cv_debug_msg_(cv_debug_code_null_ptr);
    }
}

