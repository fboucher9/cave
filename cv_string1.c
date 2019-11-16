/* See LICENSE for license details */

#include <cv_string1.h>

#include <cv_heap.h>

#include <cv_null.h>

/*

*/
char cv_string1_init(
    cv_string1 * p_this,
    long i_length)
{
    char b_result = 0;
    if (p_this)
    {
        p_this->o_buf.o_min.p_void = cv_null_;
        p_this->o_buf.o_max.p_void = cv_null_;
        if (i_length)
        {
            char * const p_array = cv_new_array_(char, i_length);
            if (p_array)
            {
                p_this->o_buf.o_min.p_char = p_array;
                p_this->o_buf.o_max.p_char = p_array + i_length;
                b_result = 1;
            }
        }
        else
        {
            b_result = 1;
        }
    }
    return b_result;
} /* _init() */

/*

Free resources allocated for cv_string1 object.

*/
void cv_string1_cleanup(
    cv_string1 * p_this)
{
    if (p_this)
    {
        if (p_this->o_buf.o_min.pc_void)
        {
            cv_delete_(p_this->o_buf.o_min.p_void);
            p_this->o_buf.o_min.p_void = cv_null_;
            p_this->o_buf.o_max.p_void = cv_null_;
        }
    }
} /* _cleanup() */

/* Get length of buffer */
long cv_string1_len(
    cv_string1 const * p_this)
{
    long i_len = 0;
    if (p_this)
    {
        i_len = cv_string_len(
            &(p_this->o_buf));
    }
    return i_len;
}

/* eof: cv_string1.c */
