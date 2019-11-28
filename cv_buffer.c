/* See LICENSE for license details */

#include <cv_buffer.h>

#include <cv_heap.h>

#include <cv_null.h>

/*

*/
cv_bool cv_buffer_init(
    cv_buffer * p_this)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        if (cv_array_init(&p_this->o_array))
        {
            b_result = cv_true;
        }
    }
    return b_result;
} /* _init() */

/*

Free resources allocated for cv_buffer object.

*/
void cv_buffer_cleanup(
    cv_buffer * p_this)
{
    if (p_this)
    {
        if (p_this->o_array.o_min.pc_void)
        {
            cv_delete_(p_this->o_array.o_min.p_void);
            cv_array_cleanup(&p_this->o_array);
        }
    }
} /* _cleanup() */

cv_bool cv_buffer_realloc(
    cv_buffer * p_this,
    long i_length)
{
    cv_bool b_result = cv_false;
    if (i_length)
    {
        long const i_old_length = cv_buffer_len(p_this);
        if (i_length != i_old_length)
        {
            cv_buffer_cleanup(p_this);
            {
                char * const p_array = cv_new_array_(char, i_length);
                if (p_array)
                {
                    if (cv_array_init_range(&p_this->o_array,
                            p_array,
                            p_array + i_length))
                    {
                        b_result = cv_true;
                    }
                }
            }
        }
        else
        {
            b_result = cv_true;
        }
    }
    else
    {
        cv_buffer_cleanup(p_this);
        b_result = cv_true;
    }
    return b_result;
}

/* Get length of buffer */
long cv_buffer_len(
    cv_buffer const * p_this)
{
    long i_len = 0;
    if (p_this)
    {
        i_len = cv_array_len(
            &(p_this->o_array));
    }
    return i_len;
}

/* eof: cv_buffer.c */
