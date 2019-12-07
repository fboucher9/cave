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

static cv_bool g_heap_loaded = cv_false;

static long g_heap_count = 0L;

static cv_list_root g_heap_used_list = cv_list_root_initializer_;

cv_bool cv_heap_load(void)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(!g_heap_loaded, cv_debug_code_already_loaded);
    if (cv_heap_primary_load()) {
        if (cv_heap_node_load()) {
            if (cv_heap_small_load()) {
                if (cv_heap_large_load()) {
                    cv_list_root_init(&g_heap_used_list);
                    g_heap_loaded = cv_true;
                    b_result = cv_true;
                } else {
                    cv_debug_msg_(cv_debug_code_error);
                }
                if (!b_result) {
                    cv_heap_small_unload();
                }
            } else {
                cv_debug_msg_(cv_debug_code_error);
            }
            if (!b_result) {
                cv_heap_node_unload();
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

static cv_array const * report_prefix(void) {
    static unsigned char a_text[] = {
        '*', '*', '*', ' ' };
    static cv_array const g_text =
        cv_array_text_initializer_(a_text);
    return &g_text;
}

static cv_array const * report_suffix(void) {
    static unsigned char a_text[] = {
        ' ', 'l', 'e', 'a', 'k', 's', ' ', 'd',
        'e', 't', 'e', 'c', 't', 'e', 'd', ' ',
        '*', '*', '*' };
    static cv_array const g_text =
        cv_array_text_initializer_(a_text);
    return &g_text;
}

/*
 *
 */

static void cv_heap_print_leak_report(void)
{
    cv_file const * const p_std_err = cv_file_std_err();
    cv_file_print_array(p_std_err, report_prefix());
    cv_file_print_signed(p_std_err, g_heap_count, cv_number_format_dec());
    cv_file_print_array(p_std_err, report_suffix());
    cv_file_print_nl(p_std_err);
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
    cv_heap_print_leak_report();
    cv_list_root_cleanup(&g_heap_used_list);
    cv_heap_large_unload();
    cv_heap_small_unload();
    cv_heap_node_unload();
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
            p_heap_node = cv_heap_small_alloc(i_buffer_length);
        } else {
            p_heap_node = cv_heap_large_alloc(i_buffer_length);
        }
        if (p_heap_node) {
            /* Attach node to used list */
            cv_list_join(&p_heap_node->o_node, &g_heap_used_list.o_node);
            p_buffer = p_heap_node->o_payload.o_min.p_void;
            g_heap_count ++;
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
        cv_list_it o_list_it = cv_list_it_initializer_;
        cv_list_it_init(&o_list_it, &g_heap_used_list);
        {
            cv_bool b_found = cv_false;
            cv_heap_node_ptr o_heap_node_ptr = cv_ptr_null_;
            while (!b_found && cv_list_it_next(&o_list_it,
                    &o_heap_node_ptr.o_list_ptr)) {
                cv_heap_node * p_heap_node =
                    o_heap_node_ptr.p_heap_node;
                if (p_buffer == p_heap_node->o_payload.o_min.p_void) {
                    long const i_buffer_length = cv_array_len(&p_heap_node->o_payload);
                    if (i_buffer_length <= cv_heap_small_max_len_) {
                        cv_heap_small_free(p_heap_node);
                    } else {
                        cv_heap_large_free(p_heap_node);
                    }
                    b_found = cv_true;
                }
            }
            cv_debug_assert_(b_found, cv_debug_code_error);
        }
        cv_list_it_cleanup(&o_list_it);
        g_heap_count --;
    } else {
        cv_debug_msg_(cv_debug_code_null_ptr);
    }
}

