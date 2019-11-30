/* See LICENSE for license details */

#include <cv_string_it.h>

#include <cv_memory.h>

#include <cv_debug.h>

#include <cv_sizeof.h>

#include <cv_array_tool.h>

void cv_string_it_init(
    cv_string_it * p_string_it,
    cv_array const * p_array)
{
    cv_debug_assert_( p_string_it && p_array, "null ptr");
    cv_debug_init_(p_string_it, cv_sizeof_(*p_string_it));
    cv_array_init_ref(&p_string_it->o_array, p_array);
}

void cv_string_it_cleanup(
    cv_string_it * p_string_it)
{
    cv_debug_assert_ ( !!p_string_it, "null ptr");
    cv_array_cleanup(&p_string_it->o_array);
    cv_debug_cleanup_(p_string_it, cv_sizeof_(*p_string_it));
}

cv_bool cv_string_it_write_char(
    cv_string_it * p_string_it,
    unsigned char c_data)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( !!p_string_it, "null ptr");
    if (p_string_it->o_array.o_min.p_uchar !=
        p_string_it->o_array.o_max.p_uchar) {
        *(p_string_it->o_array.o_min.p_uchar) = c_data;
        p_string_it->o_array.o_min.p_uchar ++;
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_string_it_read_char(
    cv_string_it * p_string_it,
    unsigned char * r_data)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_string_it && r_data, "null ptr");
    if (p_string_it->o_array.o_min.pc_uchar !=
        p_string_it->o_array.o_max.pc_uchar) {
        *(r_data) = *(p_string_it->o_array.o_min.pc_uchar);
        p_string_it->o_array.o_min.pc_uchar ++;
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_string_it_write_array(
    cv_string_it * p_string_it,
    cv_array const * p_array)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_string_it && p_array, "null ptr");
    {
        long const i_array_len = cv_array_len(p_array);
        if ((p_string_it->o_array.o_min.p_uchar + i_array_len)
            <= p_string_it->o_array.o_max.p_uchar) {
            cv_array_copy(
                &p_string_it->o_array,
                p_array);
            p_string_it->o_array.o_min.p_uchar += i_array_len;
            b_result = cv_true;
        }
    }
    return b_result;
}

cv_bool cv_string_it_read_array(
    cv_string_it * p_string_it,
    cv_array const * p_array)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_string_it && p_array, "null ptr");
    {
        long const i_array_len = cv_array_len(p_array);
        if ((p_string_it->o_array.o_min.pc_uchar + i_array_len)
            <= p_string_it->o_array.o_max.pc_uchar) {
            cv_array_copy(
                p_array,
                &p_string_it->o_array);
            p_string_it->o_array.o_min.pc_uchar += i_array_len;
            b_result = cv_true;
        }
    }
    return b_result;
}

/* end-of-file: cv_string_it.c */
