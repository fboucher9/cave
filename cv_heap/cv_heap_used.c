/* See LICENSE for license details */

/*
 *
 */

#include <cv_heap/cv_heap_used.h>
#include <cv_heap/cv_heap_node.h>
#include <cv_heap/cv_heap_node_ptr.h>
#include <cv_debug/cv_debug.h>
#include <cv_misc/cv_sizeof.h>
#include <cv_algo/cv_list_it.h>
#include <cv_algo/cv_array_tool.h>
#include <cv_file/cv_file_std.h>
#include <cv_file/cv_file_print.h>
#include <cv_number_desc.h>

cv_debug_decl_(g_class);

/*
 *
 */

cv_bool cv_heap_used_init(
    cv_heap_used * p_this) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    if (cv_mutex_init(&p_this->o_mutex)) {
        cv_list_root_init(&p_this->o_used_list);
        p_this->i_count = 0L;
        b_result = cv_true;
    } else {
        cv_debug_destruct_(g_class, p_this);
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

static void cv_heap_print_leak_report(cv_heap_used * p_this) {
    if (p_this->i_count) {
        cv_file const * const p_std_err = cv_file_std_err();
        cv_file_print_array(p_std_err, report_prefix());
        cv_file_print_signed(p_std_err, p_this->i_count, cv_number_format_dec());
        cv_file_print_array(p_std_err, report_suffix());
        cv_file_print_nl(p_std_err);
    }
    cv_debug_assert_(0 == p_this->i_count, cv_debug_code_leak);
}

/*
 *
 */

void cv_heap_used_cleanup(
    cv_heap_used * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_heap_print_leak_report(p_this);
    cv_list_root_cleanup(&p_this->o_used_list);
    cv_mutex_cleanup(&p_this->o_mutex);
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

void cv_heap_used_join(
    cv_heap_used * p_this,
    cv_heap_node * p_heap_node) {
    cv_mutex_lock(&p_this->o_mutex);
    cv_list_join(&p_heap_node->o_node, &p_this->o_used_list.o_node);
    p_this->i_count ++;
    cv_mutex_unlock(&p_this->o_mutex);
}

/*
 *
 */

cv_heap_node * cv_heap_used_lookup(
    cv_heap_used * p_this,
    void * p_buffer) {
    cv_heap_node * p_result = cv_null_;
    cv_mutex_lock(&p_this->o_mutex);
    {
        cv_list_it o_list_it = cv_list_it_initializer_;
        cv_list_it_init(&o_list_it, &p_this->o_used_list);
        {
            cv_bool b_found = cv_false;
            cv_heap_node_ptr o_heap_node_ptr = cv_ptr_null_;
            while (!b_found && cv_list_it_next(&o_list_it,
                    &o_heap_node_ptr.o_list_ptr)) {
                cv_heap_node * p_heap_node =
                    o_heap_node_ptr.p_heap_node;
                if (p_buffer == p_heap_node->o_payload.o_min.p_void) {
                    p_this->i_count --;
                    p_result = p_heap_node;
                    b_found = cv_true;
                }
            }
            cv_debug_assert_(b_found, cv_debug_code_error);
        }
        cv_list_it_cleanup(&o_list_it);
    }
    cv_mutex_unlock(&p_this->o_mutex);
    return p_result;
}

/* end-of-file: cv_heap_used.c */
