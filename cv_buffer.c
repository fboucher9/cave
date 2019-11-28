/* See LICENSE for license details */

#include <cv_buffer.h>

#include <cv_heap.h>

#include <cv_null.h>

#include <cv_debug.h>

static cv_bool cv_buffer_realloc(
    cv_buffer * p_this,
    long i_length)
{
    cv_bool b_result = cv_false;
    if (p_this && i_length)
    {
        char * const p_array = cv_new_array_(char, i_length);
        if (p_array)
        {
            if (cv_array_init_vector(&p_this->o_array,
                    p_array,
                    i_length))
            {
                b_result = cv_true;
            }
        }
        else
        {
            cv_debug_msg_("out of memory");
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

/*

*/
cv_bool cv_buffer_init(
    cv_buffer * p_this,
    long i_length)
{
    cv_bool b_result = cv_false;
    if (p_this && i_length)
    {
        cv_debug_init(p_this, cv_sizeof_(*p_this));

        if (cv_buffer_realloc(p_this, i_length))
        {
            b_result = cv_true;
        }

        if (!b_result)
        {
            cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
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
        }
        cv_array_cleanup(&p_this->o_array);
        cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
    }
} /* _cleanup() */

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
