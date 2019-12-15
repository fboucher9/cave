/* See LICENSE for license details */

#include <cv_heap/cv_heap_node.h>
#include <cv_misc/cv_sizeof.h>
#include <cv_heap/cv_heap_primary.h>
#include <cv_heap/cv_heap_node_ptr.h>
#include <cv_misc/cv_null.h>
#include <cv_debug.h>
#include <cv_heap/cv_heap_secondary.h>

cv_debug_decl_(g_class);

static void cv_heap_node_init( cv_heap_node * p_this,
    cv_array const * p_payload)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    cv_list_node_init(&p_this->o_node);
    cv_array_init_ref(&p_this->o_payload, p_payload);
}

void cv_heap_node_cleanup( cv_heap_node * p_this) {
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_array_cleanup(&p_this->o_payload);
    cv_list_node_cleanup(&p_this->o_node);
    cv_debug_destruct_(g_class, p_this);
}

cv_heap_node * cv_heap_node_create(
    cv_heap_secondary * p_heap_secondary,
    cv_array const * p_payload)
{
    cv_heap_node * p_this = cv_null_;
    cv_debug_assert_( p_heap_secondary && p_payload,
        cv_debug_code_null_ptr);
    {
        cv_heap_node_ptr o_heap_ptr = cv_ptr_null_;
        long const i_node_len = cv_sizeof_(cv_heap_node);
        o_heap_ptr.o_list_ptr.p_void = cv_heap_secondary_alloc(
            p_heap_secondary, i_node_len);
        if (o_heap_ptr.o_list_ptr.p_void) {
            cv_heap_node_init(o_heap_ptr.p_heap_node, p_payload);
            p_this = o_heap_ptr.p_heap_node;
        }
    }
    return p_this;
}

