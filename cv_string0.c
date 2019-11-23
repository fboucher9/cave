/* See LICENSE for license details */

#include <cv_string0.h>

#include <cv_string.h>

#include <cv_heap.h>

#include <cv_sizeof.h>

#include <cv_unused.h>

#include <cv_null.h>

#include <cv_memory.h>

/*

Convert cv_string object to a zero-terminated string.  The cv_string0 object
holds resources allocated for zero-terminated string.

*/
cv_bool cv_string0_init(
    cv_string0 * p_this,
    cv_string const * p_string)
{
    cv_bool b_result = cv_false_;

    /* Validate input parameters */
    if (p_this)
    {
        /* Get length of string */
        long const i_length = p_string ? cv_string_len(p_string) : 0;
        if (cv_string1_init(
                &(p_this->o_buf1),
                i_length + 1))
        {
            if (i_length)
            {
                cv_memory_copy(
                    p_this->o_buf1.o_buf.o_min.p_void,
                    i_length,
                    p_string->o_min.pc_void,
                    i_length);
            }
            p_this->o_buf1.o_buf.o_min.p_char[i_length] = '\000';
            b_result = cv_true_;
        }
    }
    return b_result;
}

void cv_string0_cleanup(
    cv_string0 * p_this)
{
    if (p_this)
    {
        cv_string1_cleanup(
            &(p_this->o_buf1));
    }
}

char const * cv_string0_get(
    cv_string0 const * p_this)
{
    char const * p_result = cv_null_;
    if (p_this)
    {
        p_result = p_this->o_buf1.o_buf.o_min.pc_char;
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
        i_len = cv_string1_len(&(p_this->o_buf1));
        if (i_len > 0)
        {
            i_len --;
        }
    }
    return i_len;
}

