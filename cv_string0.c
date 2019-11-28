/* See LICENSE for license details */

#include <cv_string0.h>

#include <cv_array.h>

#include <cv_heap.h>

#include <cv_sizeof.h>

#include <cv_unused.h>

#include <cv_null.h>

#include <cv_memory.h>

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
    if (p_this)
    {
        /* Get length of string */
        long const i_length = p_string ? cv_array_len(p_string) : 0;
        if (cv_buffer_init(
                &p_this->o_buffer,
                i_length + 1))
        {
            if (i_length)
            {
                cv_memory_copy(
                    p_this->o_buffer.o_array.o_min.p_void,
                    i_length,
                    p_string->o_min.pc_void,
                    i_length);
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
    if (p_this)
    {
        cv_buffer_cleanup(
            &p_this->o_buffer);
    }
}

char const * cv_string0_get(
    cv_string0 const * p_this)
{
    char const * p_result = cv_null_;
    if (p_this)
    {
        p_result = p_this->o_buffer.o_array.o_min.pc_char;
    }
    return p_result;
}

/* Get length of buffer without terminating null character */
long cv_string0_len(
    cv_string0 const * p_this)
{
    long i_len = 0;
    if (p_this)
    {
        i_len = cv_buffer_len(&p_this->o_buffer);
        if (i_len > 0)
        {
            i_len --;
        }
    }
    return i_len;
}

