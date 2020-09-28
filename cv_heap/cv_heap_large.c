/* See LICENSE for license details */

#include <cv_heap/cv_heap_large.h>
#include <cv_heap/cv_heap_node.h>
#include <cv_heap/cv_heap_node_ptr.h>
#include <cv_algo/cv_list_it.h>
#include <cv_misc/cv_sizeof.h>
#include <cv_runtime.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_heap_large", sizeof(cv_heap_large));

cv_bool cv_heap_large_init( cv_heap_large * p_this ) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    if (cv_mutex_init(&p_this->o_mutex)) {
        cv_list_root_init(&p_this->o_free_list);
        b_result = cv_true;
    } else {
        cv_debug_destruct_(g_class, p_this);
    }
    return b_result;
}

static void cv_heap_large_empty_free_list( cv_heap_large * p_this) {
    cv_list_it o_list_it = {0};
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_list_it_init(&o_list_it, &p_this->o_free_list);
    {
        cv_heap_node_ptr o_heap_ptr = {0};
        while (cv_list_it_first(&o_list_it, &o_heap_ptr.o_list_ptr)) {
            void * const p_payload =
                o_heap_ptr.pc_heap_node->o_payload.o_min.p_void;
            /* Detach from free list */
            cv_list_join( o_heap_ptr.o_list_ptr.p_node,
                o_heap_ptr.o_list_ptr.p_node);
            /* Cleanup the node */
            cv_heap_node_cleanup(o_heap_ptr.p_heap_node);
            /* Free memory */
            cv_runtime_free(p_payload);
        }
    }
    cv_list_it_cleanup(&o_list_it);
}

void cv_heap_large_cleanup( cv_heap_large * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    /* Free all items ... */
    cv_heap_large_empty_free_list(p_this);
    cv_list_root_cleanup(&p_this->o_free_list);
    cv_mutex_cleanup(&p_this->o_mutex);
    cv_debug_destruct_(g_class, p_this);
}

static cv_uptr cv_heap_large_align( cv_uptr i_len) {
    cv_uptr const i_total_len = i_len;
    cv_uptr const i_aligned_len = cv_sizeof_align(i_total_len, 4096);
    return i_aligned_len;
}

static cv_heap_node * cv_heap_large_find_existing( cv_heap_large * p_this,
    cv_uptr i_aligned_len)
{
    cv_heap_node_ptr o_heap_ptr = {0};
    cv_list_it o_free_it = {0};
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

static cv_heap_node * cv_heap_large_lookup_cb( cv_heap_large * p_this,
    cv_uptr i_len) {
    cv_heap_node * p_result = 0;
    cv_debug_assert_(i_len > 0, cv_debug_code_invalid_length);
    {
        cv_uptr const i_aligned_len = cv_heap_large_align(i_len);
        cv_heap_node_ptr o_heap_ptr = {0};
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
            /* Attach to used list */
            /* ... */
            p_result = o_heap_ptr.p_heap_node;
        }
    }
    return p_result;
}

static void cv_heap_large_free_cb( cv_heap_large * p_this,
    cv_heap_node * p_heap_node) {
    cv_debug_assert_(p_heap_node, cv_debug_code_null_ptr);
    /* Detach from used list */
    cv_list_join( &p_heap_node->o_node, &p_heap_node->o_node);
    /* Attach to free list */
    cv_list_join( &p_heap_node->o_node, & p_this->o_free_list.o_node);
}

cv_heap_node * cv_heap_large_lookup( cv_heap_large * p_this,
    cv_uptr i_len) {
    cv_heap_node * p_result = 0;
    cv_debug_assert_(i_len > 4096L, cv_debug_code_invalid_length);
    cv_mutex_lock(&p_this->o_mutex);
    p_result = cv_heap_large_lookup_cb(p_this, i_len);
    cv_mutex_unlock(&p_this->o_mutex);
    return p_result;
}

cv_heap_node * cv_heap_large_alloc( cv_heap_secondary * p_heap_secondary,
    cv_uptr i_len) {
    cv_heap_node * p_result = 0;
    cv_debug_assert_(i_len > 0, cv_debug_code_invalid_length);
    {
        cv_uptr const i_aligned_len = cv_heap_large_align(i_len);
        void * const p_payload = cv_runtime_malloc(i_aligned_len);
        if (p_payload) {
            cv_array o_payload = {0};
            cv_array_init_vector(&o_payload, p_payload, i_len);
            p_result = cv_heap_node_create(
                p_heap_secondary, &o_payload);
            cv_array_cleanup(&o_payload);
        }
    }
    return p_result;
}


void cv_heap_large_free( cv_heap_large * p_this,
    cv_heap_node * p_heap_node) {
    cv_debug_assert_(p_heap_node, cv_debug_code_null_ptr);
    cv_mutex_lock(&p_this->o_mutex);
    cv_heap_large_free_cb(p_this, p_heap_node);
    cv_mutex_unlock(&p_this->o_mutex);
}

