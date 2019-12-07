/* See LICENSE for license details */

#include <cv_heap_node.h>
#include <cv_sizeof.h>
#include <cv_heap_primary.h>
#include <cv_heap_node_ptr.h>
#include <cv_null.h>
#include <cv_debug.h>
#include <cv_heap_section_lock.h>

static cv_heap_section_lock g_heap_node_section =
cv_heap_section_lock_initializer_;

static cv_bool g_heap_node_loaded = cv_false;

static long const g_heap_node_grow_len = 4096L;

cv_bool cv_heap_node_load(void) {
    cv_bool b_result = cv_false;
    cv_heap_section_desc o_desc = cv_heap_section_desc_initializer_;
    o_desc.i_grow_len = g_heap_node_grow_len;
    if (cv_heap_section_lock_init(&g_heap_node_section,
            &o_desc)) {
        g_heap_node_loaded = cv_true;
        b_result = cv_true;
    }
    return b_result;
}

void cv_heap_node_unload(void) {
    cv_heap_section_lock_cleanup(&g_heap_node_section);
    g_heap_node_loaded = cv_false;
}

static void cv_heap_node_init(
    cv_heap_node * p_this,
    cv_array const * p_payload)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    cv_debug_init_(p_this, cv_sizeof_(cv_heap_node));
    cv_list_node_init(&p_this->o_node);
    cv_array_init_ref(&p_this->o_payload, p_payload);
}

void cv_heap_node_cleanup(
    cv_heap_node * p_this)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    cv_array_cleanup(&p_this->o_payload);
    cv_list_node_cleanup(&p_this->o_node);
    cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
}

cv_heap_node * cv_heap_node_create(
    cv_array const * p_payload)
{
    cv_heap_node * p_this = cv_null_;
    if (p_payload) {
        cv_heap_node_ptr o_heap_ptr = cv_ptr_null_;
        long const i_node_len = cv_sizeof_(cv_heap_node);
        o_heap_ptr.o_list_ptr.p_void = cv_heap_primary_alloc(i_node_len);
        if (o_heap_ptr.o_list_ptr.p_void) {
            cv_heap_node_init(o_heap_ptr.p_heap_node, p_payload);
            p_this = o_heap_ptr.p_heap_node;
        }
    }
    return p_this;
}

