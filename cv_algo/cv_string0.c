/* See LICENSE for license details */

#include <cv_algo/cv_string0.h>

#include <cv_algo/cv_array.h>

#include <cv_algo/cv_array_tool.h>

#include <cv_heap/cv_heap.h>

#include <cv_misc/cv_sizeof.h>

#include <cv_misc/cv_unused.h>

#include <cv_misc/cv_null.h>

#include <cv_memory.h>

#include <cv_debug.h>

/*

Convert cv_array object to a zero-terminated string.  The cv_string0 object
holds resources allocated for zero-terminated string.

*/
cv_bool cv_string0_init(
    cv_string0 * p_this,
    cv_array const * p_string)
{
    cv_bool b_result = cv_false;

    /* Validate input parameters */
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    {
        /* Get length of string */
        long const i_length = p_string ? cv_array_len(p_string) : 0;
        if (cv_buffer_init(
                &p_this->o_buffer,
                i_length + 1)) {
            if (i_length) {
                cv_array_copy(
                    &p_this->o_buffer.o_array,
                    p_string);
            }
            p_this->o_buffer.o_array.o_min.p_char[i_length] = '\000';
            b_result = cv_true;
        }
    }
    return b_result;
}

void cv_string0_cleanup(
    cv_string0 * p_this)
{
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_buffer_cleanup( &p_this->o_buffer);
}

char const * cv_string0_get(
    cv_string0 const * p_this)
{
    char const * p_result = cv_null_;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    p_result = p_this->o_buffer.o_array.o_min.pc_char;
    return p_result;
}

/* Get length of buffer without terminating null character */
long cv_string0_len(
    cv_string0 const * p_this)
{
    long i_len = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    i_len = cv_buffer_len(&p_this->o_buffer);
    if (i_len > 0) {
        i_len --;
    }
    return i_len;
}

