/* See LICENSE for license details */

#include <cv_string0.h>

#include <cv_string.h>

#include <cv_heap.h>

#include <cv_sizeof.h>

#include <cv_unused.h>

#include <cv_null.h>

#include <cv_memory.h>

#include <string.h>

/*

Convert cv_string object to a zero-terminated string.  The cv_string0 object
holds resources allocated for zero-terminated string.

*/
char cv_string0_init(
    cv_string0 * p_this,
    cv_string const * p_string)
{
    char b_result = 0;

    /* Validate input parameters */
    if (p_this)
    {
        /* Default init of cv_string0 object */
        p_this->o_buf.p_void = cv_null_;

        /* Validate input parameters */
        if (p_string)
        {
            /* Get length of string */
            long const i_length = cv_string_len(p_string);
            if (i_length)
            {
                p_this->o_buf.p_char = cv_new_array_(char, i_length + 1);
                if (p_this->o_buf.p_char)
                {
                    cv_memory_copy(
                        p_this->o_buf.p_void,
                        i_length,
                        p_string->o_min.pc_void,
                        i_length);
                    p_this->o_buf.p_char[i_length] = '\000';
                    b_result = 1;
                }
            }
        }
    }
    return b_result;
}

void cv_string0_cleanup(
    cv_string0 * p_this)
{
    if (p_this)
    {
        if (p_this->o_buf.p_void)
        {
            cv_delete_(p_this->o_buf.p_void);
            p_this->o_buf.p_void = cv_null_;
        }
    }
}

char const * cv_string0_get(
    cv_string0 const * p_this)
{
    char const * p_result = cv_null_;
    if (p_this)
    {
        p_result = p_this->o_buf.pc_char;
    }
    return p_result;
}

long cv_string0_len(
    char const * p_buf0)
{
    long i_len = 0;
    if (p_buf0)
    {
        i_len = cv_cast_(long, strlen(p_buf0));
    }
    return i_len;
}

