/* See LICENSE for license details */

#include <cv_array_tool.h>

#include <cv_memory.h>

#include <cv_debug.h>

cv_bool cv_array_compare(
    cv_array const * p_left,
    cv_array const * p_right)
{
    cv_bool b_result = cv_false;
    if (p_left && p_right)
    {
        if (0 == cv_memory_compare(
                p_left->o_min.pc_void,
                cv_array_len(p_left),
                p_right->o_min.pc_void,
                cv_array_len(p_right)))
        {
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_zero(
    cv_array const * p_this)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        cv_memory_zero(
            p_this->o_min.p_void,
            cv_array_len(p_this));
        b_result = cv_true;
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_fill(
    cv_array const * p_this,
    unsigned char c_value)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        if (!c_value)
        {
            cv_debug_msg_("consider using cv_array_zero");
        }

        cv_memory_fill(
            p_this->o_min.p_void,
            cv_array_len(p_this),
            c_value);
        b_result = cv_true;
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

