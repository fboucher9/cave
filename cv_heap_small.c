/* See LICENSE for license details */

#include <cv_heap_small.h>

#include <cv_heap_pool.h>

#include <cv_heap_node_ptr.h>

#include <cv_heap_node.h>

#include <cv_heap_primary.h>

#include <cv_null.h>

#include <cv_sizeof.h>

#include <cv_debug.h>

cv_bool cv_heap_small_init(cv_heap_small * p_this) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    cv_debug_init_(p_this, cv_sizeof_(*p_this));
    {
        long i_pool_index = 0;
        b_result = cv_true;
        while (b_result && (i_pool_index < cv_heap_small_count_)) {
            if (cv_heap_pool_init(p_this->a_pool + i_pool_index,
                    (i_pool_index + 1) * cv_heap_small_align_)) {
                i_pool_index ++;
            } else {
                while (i_pool_index) {
                    i_pool_index --;
                    cv_heap_pool_cleanup(p_this->a_pool + i_pool_index);
                }
                cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
                b_result = cv_false;
            }
        }
    }
    return b_result;
}

void cv_heap_small_cleanup(cv_heap_small * p_this) {
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    {
        long i_pool_index = 0;
        while (i_pool_index < cv_heap_small_count_) {
            cv_heap_pool_cleanup(p_this->a_pool + i_pool_index);
            i_pool_index ++;
        }
    }
    cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
}

cv_heap_node * cv_heap_small_lookup( cv_heap_small * p_this, long i_len) {
    cv_heap_node * p_result = cv_null_;
    cv_debug_assert_(i_len > 0, cv_debug_code_invalid_length);
    {
        /* Align len to multiple */
        long const i_aligned_len =
            cv_sizeof_align(i_len, cv_heap_small_align_);
        /* Locate pool */
        long const i_pool_index = (i_aligned_len - 1) / cv_heap_small_align_;
        if ((i_pool_index >= 0) && (i_pool_index < cv_heap_small_count_)) {
            cv_heap_pool * const p_heap_pool =
                p_this->a_pool + i_pool_index;
            p_result = cv_heap_pool_lookup(p_heap_pool);
        }
    }

    return p_result;
}

cv_heap_node * cv_heap_small_alloc( cv_heap_node_mgr * p_heap_node_mgr,
    long i_len) {
    cv_heap_node * p_result = cv_null_;
    cv_debug_assert_(i_len > 0, cv_debug_code_invalid_length);
    {
        /* Align len to multiple */
        long const i_aligned_len =
            cv_sizeof_align(i_len, cv_heap_small_align_);
        /* Locate pool */
        long const i_pool_index = (i_aligned_len - 1) / cv_heap_small_align_;
        if ((i_pool_index >= 0) && (i_pool_index < cv_heap_small_count_)) {
            p_result = cv_heap_pool_alloc( p_heap_node_mgr, i_aligned_len);
        }
    }
    return p_result;
}

void cv_heap_small_free( cv_heap_small * p_this, cv_heap_node * p_heap_node) {
    cv_debug_assert_(!!p_heap_node, cv_debug_code_null_ptr);
    {
        long const i_len = cv_array_len(&p_heap_node->o_payload);
        long const i_pool_index = (i_len - 1) / cv_heap_small_align_;
        if ((i_pool_index >= 0) && (i_pool_index < cv_heap_small_count_)) {
            cv_heap_pool * const p_heap_pool =
                p_this->a_pool + i_pool_index;
            cv_heap_pool_free(p_heap_pool, p_heap_node);
        }
    }
}

