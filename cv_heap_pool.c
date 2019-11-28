/* See LICENSE for license details */

#include <cv_heap_pool.h>

#include <cv_heap_pool_impl.h>

#include <cv_heap_primary.h>

#include <cv_heap_node.h>

#include <cv_heap_node_ptr.h>

#include <cv_heap_it.h>

#include <cv_mutex.h>

#include <cv_mutex_mgr.h>

#include <cv_memory.h>

#include <cv_sizeof.h>

#include <cv_null.h>

#include <cv_debug.h>

cv_bool cv_heap_pool_init(
    cv_heap_pool * p_this,
    long i_len)
{
    cv_bool b_result = cv_false;
    if (p_this && i_len)
    {
        cv_debug_init_(p_this, cv_sizeof_(*p_this));
        p_this->p_mutex = cv_mutex_mgr_acquire();
        if (p_this->p_mutex)
        {
            if (cv_list_init(&p_this->o_used_list))
            {
                if (cv_list_init(&p_this->o_free_list))
                {
                    p_this->i_len = i_len;
                    b_result = cv_true;
                }
            }
        }
        if (!b_result)
        {
            cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
        }
    }
    return b_result;
}

void cv_heap_pool_cleanup(
    cv_heap_pool * p_this)
{
    if (p_this)
    {
        /* Detect leaks ... */
        /* Discard all free nodes */
        cv_node_join(
            &p_this->o_free_list.o_node,
            &p_this->o_free_list.o_node);
        cv_list_cleanup(&p_this->o_used_list);
        cv_list_cleanup(&p_this->o_free_list);
        if (p_this->p_mutex)
        {
            cv_mutex_mgr_release(p_this->p_mutex);
            p_this->p_mutex = cv_null_;
        }
        cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
    }
}

static void * cv_heap_pool_alloc_cb(
    cv_heap_pool * p_this,
    long i_len)
{
    void * p_result = cv_null_;
    if (p_this)
    {
        /* Look for free compatible item */
        cv_heap_it o_heap_it = cv_heap_it_initializer_;
        if (cv_heap_it_init(&o_heap_it, &p_this->o_free_list))
        {
            cv_heap_node_ptr o_heap_ptr = cv_ptr_null_;
            if (cv_heap_it_next(&o_heap_it, &o_heap_ptr))
            {
                /* Detach from free list */
                cv_node_join(
                    o_heap_ptr.o_node_ptr.p_node,
                    o_heap_ptr.o_node_ptr.p_node);
            }
            else
            {
                /* Create new item */
                o_heap_ptr.p_heap_node =
                    cv_heap_node_create(p_this->i_len);
            }
            if (o_heap_ptr.p_heap_node)
            {
                /* Attach to used list */
                cv_node_join(
                    o_heap_ptr.o_node_ptr.p_node,
                    &p_this->o_used_list.o_node);
                /* Set actual len */
                o_heap_ptr.p_heap_node->i_len = i_len;
                /* Get payload */
                p_result = cv_heap_node_to_payload(
                    o_heap_ptr.p_heap_node);
            }
            cv_heap_it_cleanup(&o_heap_it);
        }
    }
    return p_result;
}

void * cv_heap_pool_alloc(
    cv_heap_pool * p_this,
    long i_len)
{
    void * p_result = cv_null_;
    if (p_this)
    {
        cv_mutex_lock(p_this->p_mutex);

        p_result = cv_heap_pool_alloc_cb(p_this, i_len);

        cv_mutex_unlock(p_this->p_mutex);
    }
    return p_result;
}

void cv_heap_pool_free(
    cv_heap_pool * p_this,
    void * p_buf)
{
    if (p_this && p_buf)
    {
        cv_mutex_lock(p_this->p_mutex);
        {
            cv_heap_node * const p_heap_node =
                cv_heap_node_from_payload(p_buf);

            /* Detach from used list */
            cv_node_join(
                &p_heap_node->o_node,
                &p_heap_node->o_node);
            /* Attach to free list */
            cv_node_join(
                &p_heap_node->o_node,
                &p_this->o_free_list.o_node);
        }
        cv_mutex_unlock(p_this->p_mutex);
    }
}

cv_heap_pool * cv_heap_pool_load(
    long i_len)
{
    cv_heap_pool_ptr o_heap_pool_ptr = cv_ptr_null_;
    o_heap_pool_ptr.p_void = cv_heap_primary_alloc(cv_sizeof_(cv_heap_pool));
    if (o_heap_pool_ptr.p_void)
    {
        if (cv_heap_pool_init(o_heap_pool_ptr.p_heap_pool, i_len))
        {
        }
        else
        {
            o_heap_pool_ptr.p_void = cv_null_;
        }
    }
    return o_heap_pool_ptr.p_heap_pool;
}

void cv_heap_pool_unload(
    cv_heap_pool * p_this)
{
    cv_heap_pool_cleanup(p_this);
    /* Memory is not freed */
}

