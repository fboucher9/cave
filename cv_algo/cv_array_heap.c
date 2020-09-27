/* See LICENSE for license details */

#include <cv_algo/cv_array_heap.h>

#include <cv_heap/cv_heap.h>

#include <cv_debug/cv_debug.h>

#include <cv_algo/cv_unique.h>

cv_debug_decl_(g_class);

static cv_bool cv_array_heap_realloc(
    cv_array_heap * p_this,
    cv_uptr i_length,
    cv_unique const * p_unique)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_debug_assert_( i_length > 0, cv_debug_code_invalid_length);
    {
        cv_array_ptr o_array_ptr;
        o_array_ptr.p_void = 0;
        if (p_unique) {
            o_array_ptr.p_void = cv_heap_alloc(i_length, p_unique);
        } else {
            static unsigned char const a_array_heap_class[] = {
                'a', 'r', 'r', 'a', 'y', '_', 'h', 'e', 'a', 'p'
            };
            static cv_unique g_array_heap_unique =
                cv_unique_initializer_(a_array_heap_class);
            cv_unique_next(&g_array_heap_unique);
            o_array_ptr.p_void = cv_heap_alloc(i_length, &g_array_heap_unique);
        }
        if (o_array_ptr.p_void) {
            cv_array_init_vector(&p_this->o_array,
                o_array_ptr.p_void, i_length);
            b_result = cv_true;
        } else {
            cv_debug_msg_(cv_debug_code_out_of_memory);
        }
    }
    return b_result;
}

/*

*/
cv_bool cv_array_heap_init(
    cv_array_heap * p_this,
    cv_uptr i_length,
    cv_unique const * p_unique)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_debug_assert_( i_length > 0, cv_debug_code_invalid_length);
    {
        cv_debug_construct_(g_class, p_this);
        if (cv_array_heap_realloc(p_this, i_length, p_unique)) {
            b_result = cv_true;
        }
        if (!b_result) {
            cv_debug_destruct_(g_class, p_this);
        }
    }
    return b_result;
} /* _init() */

/*

Free resources allocated for cv_array_heap object.

*/
void cv_array_heap_cleanup(
    cv_array_heap * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    if (p_this->o_array.o_min.pc_void) {
        cv_heap_free(p_this->o_array.o_min.p_void);
    }
    cv_array_cleanup(&p_this->o_array);
    cv_debug_destruct_(g_class, p_this);
} /* _cleanup() */

/* Get length of array_heap */
cv_uptr cv_array_heap_len(
    cv_array_heap const * p_this)
{
    cv_uptr i_len = 0;
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    i_len = cv_array_len( &p_this->o_array);
    return i_len;
}

/* eof: cv_array_heap.c */
