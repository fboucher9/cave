/* See LICENSE for license details */

#include <cv_array_tool.h>

#include <cv_memory.h>

#include <cv_debug.h>

cv_bool cv_array_compare(
    cv_array const * p_left,
    cv_array const * p_right)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_left && p_right, "null ptr");
    {
        if (0 == cv_memory_compare(
                p_left->o_min.pc_void,
                cv_array_len(p_left),
                p_right->o_min.pc_void,
                cv_array_len(p_right))) {
            b_result = cv_true;
        }
    }
    return b_result;
}

void cv_array_zero(
    cv_array const * p_this)
{
    cv_debug_assert_( !!p_this, "null ptr");
    cv_memory_zero( p_this->o_min.p_void,
        cv_array_len(p_this));
}

void cv_array_fill(
    cv_array const * p_this,
    unsigned char c_value)
{
    cv_debug_assert_( !!p_this, "null ptr");
    if (!c_value) {
        cv_debug_msg_("consider using cv_array_zero");
    }
    cv_memory_fill( p_this->o_min.p_void,
        cv_array_len(p_this), c_value);
}

void cv_array_copy(
    cv_array const * p_dst,
    cv_array const * p_src)
{
    cv_debug_assert_( p_dst && p_src, "null ptr");
    {
        long const i_dst_len = cv_array_len(p_dst);
        long const i_src_len = cv_array_len(p_src);
        long const i_copy_len = (i_dst_len < i_src_len) ?
            i_dst_len : i_src_len;
        if (i_copy_len > 0) {
            cv_memory_copy(
                p_dst->o_min.p_void,
                i_copy_len,
                p_src->o_min.pc_void,
                i_copy_len);
        }
    }
}

