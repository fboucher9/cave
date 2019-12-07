/* See LICENSE for license details */

#include <cv_heap_large.h>
#include <cv_heap_node.h>
#include <cv_heap_node_ptr.h>
#include <cv_mutex.h>
#include <cv_list_root.h>
#include <cv_list_it.h>
#include <cv_sizeof.h>
#include <cv_unused.h>
#include <cv_runtime.h>
#include <cv_debug.h>

typedef struct cv_heap_large cv_heap_large;

struct cv_heap_large {
    cv_mutex o_mutex;
    cv_list_root o_free_list;
};

#define cv_heap_large_initializer_ \
{ cv_mutex_initializer_, cv_list_root_initializer_ }

static cv_heap_large g_heap_large = cv_heap_large_initializer_;

static cv_bool g_heap_large_loaded = cv_false;

static cv_bool cv_heap_large_init( cv_heap_large * p_this) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    cv_debug_init_(p_this, cv_sizeof_(*p_this));
    if (cv_mutex_init(&p_this->o_mutex)) {
        cv_list_root_init(&p_this->o_free_list);
        b_result = cv_true;
    }
    return b_result;
}

static void cv_heap_large_empty_free_list( cv_heap_large * p_this) {
    cv_list_it o_list_it = cv_list_it_initializer_;
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    cv_list_it_init(&o_list_it, &p_this->o_free_list);
    {
        cv_heap_node_ptr o_heap_ptr = cv_ptr_null_;
        while (cv_list_it_first(&o_list_it, &o_heap_ptr.o_list_ptr)) {
            /* Detach from free list */
            cv_list_join( o_heap_ptr.o_list_ptr.p_node,
                o_heap_ptr.o_list_ptr.p_node);
            /* Cleanup the node */
            cv_heap_node_cleanup(o_heap_ptr.p_heap_node);
            /* Free memory */
            cv_runtime_free(o_heap_ptr.p_void);
        }
    }
    cv_list_it_cleanup(&o_list_it);
}

static void cv_heap_large_cleanup( cv_heap_large * p_this) {
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    /* Free all items ... */
    cv_heap_large_empty_free_list(p_this);
    cv_list_root_cleanup(&p_this->o_free_list);
    cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
}

cv_bool cv_heap_large_load(void) {
    cv_bool b_result = cv_false;
    cv_heap_large * const p_this = &g_heap_large;
    cv_debug_assert_(!g_heap_large_loaded, cv_debug_code_already_loaded);
    if (cv_heap_large_init(p_this)) {
        g_heap_large_loaded = cv_true;
        b_result = cv_true;
    }
    return b_result;
}

void cv_heap_large_unload(void) {
    cv_heap_large * const p_this = &g_heap_large;
    cv_debug_assert_(g_heap_large_loaded, cv_debug_code_already_unloaded);
    /* Detect leaks */
    cv_heap_large_cleanup(p_this);
    g_heap_large_loaded = cv_false;
}

static long cv_heap_large_align( long i_len) {
    long const i_total_len = i_len + cv_sizeof_(cv_heap_node);
    long const i_aligned_len = cv_sizeof_align(i_total_len, 4096);
    return i_aligned_len;
}

static cv_heap_node * cv_heap_large_find_existing( cv_heap_large * p_this,
    long i_aligned_len)
{
    cv_heap_node_ptr o_heap_ptr = cv_ptr_null_;
    cv_list_it o_free_it = cv_list_it_initializer_;
    cv_list_it_init(&o_free_it, &p_this->o_free_list);
    {
        cv_bool b_found_existing = cv_false;
        while (!b_found_existing &&
            cv_list_it_next(&o_free_it, &o_heap_ptr.o_list_ptr)) {
            if (i_aligned_len == cv_heap_large_align(
                    cv_array_len(&o_heap_ptr.p_heap_node->o_payload))) {
                b_found_existing = 1;
            }
        }
    }
    cv_list_it_cleanup(&o_free_it);
    return o_heap_ptr.p_heap_node;
}

static cv_heap_node * cv_heap_large_alloc_cb( cv_heap_large * p_this,
    long i_len) {
    cv_heap_node * p_result = cv_null_;
    cv_debug_assert_(i_len > 0, cv_debug_code_invalid_length);
    {
        long const i_aligned_len = cv_heap_large_align(i_len);
        cv_heap_node_ptr o_heap_ptr = cv_ptr_null_;
        /* Look for free node */
        o_heap_ptr.p_heap_node = cv_heap_large_find_existing( p_this,
            i_aligned_len);
        if (o_heap_ptr.p_heap_node) {
            /* Detach from free list */
            cv_list_join( o_heap_ptr.o_list_ptr.p_node,
                o_heap_ptr.o_list_ptr.p_node);
            /* See actual length */
            o_heap_ptr.p_heap_node->o_payload.o_max.pc_char =
                o_heap_ptr.p_heap_node->o_payload.o_min.pc_char + i_len;
        } else {
            o_heap_ptr.p_void = cv_runtime_malloc(i_aligned_len);
            if (o_heap_ptr.p_void) {
                cv_heap_node_init( o_heap_ptr.p_heap_node, i_len);
            }
        }
        if (o_heap_ptr.p_void) {
            /* Attach to used list */
            /* ... */
            p_result = o_heap_ptr.p_heap_node;
        }
    }
    return p_result;
}

static void cv_heap_large_free_cb( cv_heap_large * p_this,
    cv_heap_node * p_heap_node) {
    cv_debug_assert_(!!p_heap_node, cv_debug_code_null_ptr);
    /* Detach from used list */
    cv_list_join( &p_heap_node->o_node, &p_heap_node->o_node);
    /* Attach to free list */
    cv_list_join( &p_heap_node->o_node, & p_this->o_free_list.o_node);
}

cv_heap_node * cv_heap_large_alloc( long i_len) {
    cv_heap_node * p_result = cv_null_;
    cv_heap_large * const p_this = &g_heap_large;
    cv_debug_assert_(g_heap_large_loaded, cv_debug_code_not_loaded);
    cv_debug_assert_(i_len > 4096L, cv_debug_code_invalid_length);
    cv_mutex_lock(&p_this->o_mutex);
    p_result = cv_heap_large_alloc_cb(p_this, i_len);
    cv_mutex_unlock(&p_this->o_mutex);
    return p_result;
}

void cv_heap_large_free( cv_heap_node * p_heap_node) {
    cv_heap_large * const p_this = &g_heap_large;
    cv_debug_assert_(g_heap_large_loaded, cv_debug_code_not_loaded);
    cv_debug_assert_(!!p_heap_node, cv_debug_code_null_ptr);
    cv_mutex_lock(&p_this->o_mutex);
    cv_heap_large_free_cb(p_this, p_heap_node);
    cv_mutex_unlock(&p_this->o_mutex);
}

