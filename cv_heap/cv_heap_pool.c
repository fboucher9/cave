/* See LICENSE for license details */

/*
 *
 */

#include <cv_heap/cv_heap_pool.h>
#include <cv_heap/cv_heap_pool_impl.h>
#include <cv_heap/cv_heap_primary.h>
#include <cv_heap/cv_heap_node.h>
#include <cv_heap/cv_heap_node_ptr.h>
#include <cv_heap/cv_heap_it.h>
#include <cv_thread/cv_mutex.h>
#include <cv_memory.h>
#include <cv_sizeof.h>
#include <cv_null.h>
#include <cv_debug.h>

cv_bool cv_heap_pool_init(
    cv_heap_pool * p_this,
    long i_len)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(i_len > 0, cv_debug_code_invalid_length);
    cv_debug_init_(p_this, cv_sizeof_(*p_this));
    if (cv_mutex_init(&p_this->o_mutex)) {
        cv_list_root_init(&p_this->o_free_list);
        p_this->i_len = i_len;
        b_result = cv_true;
    }
    if (!b_result) {
        cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
    }
    return b_result;
}

void cv_heap_pool_cleanup(
    cv_heap_pool * p_this)
{
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    /* Detect leaks ... */
    /* Discard all free nodes */
    {
        cv_list_it o_list_it = cv_list_it_initializer_;
        cv_list_it_init(&o_list_it, &p_this->o_free_list);
        {
            cv_heap_node_ptr o_ptr = cv_ptr_null_;
            while (cv_list_it_first(&o_list_it, &o_ptr.o_list_ptr)) {
                cv_heap_node_cleanup(o_ptr.p_heap_node);
            }
        }
        cv_list_it_cleanup(&o_list_it);
    }

    cv_list_join(
        &p_this->o_free_list.o_node,
        &p_this->o_free_list.o_node);
    cv_list_root_cleanup(&p_this->o_free_list);
    cv_mutex_cleanup(&p_this->o_mutex);
    cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
}

static cv_heap_node * cv_heap_pool_lookup_cb(
    cv_heap_pool * p_this) {
    cv_heap_node * p_result = cv_null_;
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    {
        /* Look for free compatible item */
        cv_heap_it o_heap_it = cv_heap_it_initializer_;
        cv_heap_it_init(&o_heap_it, &p_this->o_free_list);
        {
            cv_heap_node_ptr o_heap_ptr = cv_ptr_null_;
            if (cv_heap_it_next(&o_heap_it, &o_heap_ptr)) {
                /* Detach from free list */
                cv_list_join(
                    o_heap_ptr.o_list_ptr.p_node,
                    o_heap_ptr.o_list_ptr.p_node);
                p_result = o_heap_ptr.p_heap_node;
            }
        }
        cv_heap_it_cleanup(&o_heap_it);
    }
    return p_result;
}

cv_heap_node * cv_heap_pool_lookup(
    cv_heap_pool * p_this) {
    cv_heap_node * p_result = cv_null_;
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    cv_mutex_lock(&p_this->o_mutex);
    p_result = cv_heap_pool_lookup_cb(p_this);
    cv_mutex_unlock(&p_this->o_mutex);
    return p_result;
}

cv_heap_node * cv_heap_pool_alloc(
    cv_heap_primary * p_heap_primary,
    cv_heap_secondary * p_heap_secondary,
    long i_len)
{
    cv_heap_node * p_result = cv_null_;
    cv_debug_assert_(!!p_heap_secondary, cv_debug_code_null_ptr);
    {
        /* Allocate memory from primary */
        void * const p_payload = cv_heap_primary_alloc(p_heap_primary, i_len);
        if (p_payload) {
            /* Create new item */
            cv_array o_payload = cv_array_null_;
            cv_array_init_vector(&o_payload, p_payload, i_len);
            p_result = cv_heap_node_create(p_heap_secondary,
                &o_payload);
            cv_array_cleanup(&o_payload);
        }
        /* Get payload */
    }
    return p_result;
}

static void cv_heap_pool_free_cb(
    cv_heap_pool * p_this,
    cv_heap_node * p_heap_node)
{
    cv_debug_assert_(p_this && p_heap_node, cv_debug_code_null_ptr);
    {
        /* Detach from used list */
        cv_list_join(
            &p_heap_node->o_node,
            &p_heap_node->o_node);
        /* Attach to free list */
        cv_list_join(
            &p_heap_node->o_node,
            &p_this->o_free_list.o_node);
    }
}

void cv_heap_pool_free(
    cv_heap_pool * p_this,
    cv_heap_node * p_heap_node)
{
    cv_debug_assert_(p_this && p_heap_node, cv_debug_code_null_ptr);
    cv_mutex_lock(&p_this->o_mutex);
    cv_heap_pool_free_cb(p_this, p_heap_node);
    cv_mutex_unlock(&p_this->o_mutex);
}

