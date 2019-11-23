/* See LICENSE for license details */

#include <cv_string_it.h>

#include <cv_memory.h>

cv_bool cv_string_it_init(
    cv_string_it * p_string_it,
    cv_string const * p_string)
{
    cv_bool b_result = cv_false_;
    if (p_string_it && p_string)
    {
        if (cv_string_init(&p_string_it->o_string))
        {
            p_string_it->o_string = *p_string;
            b_result = cv_true_;
        }
    }
    return b_result;
}

void cv_string_it_cleanup(
    cv_string_it * p_string_it)
{
    if (p_string_it)
    {
        cv_string_cleanup(&p_string_it->o_string);
    }
}

cv_bool cv_string_it_write_char(
    cv_string_it * p_string_it,
    unsigned char c_data)
{
    cv_bool b_result = cv_false_;
    if (p_string_it)
    {
        if (p_string_it->o_string.o_min.p_uchar !=
            p_string_it->o_string.o_max.p_uchar)
        {
            *(p_string_it->o_string.o_min.p_uchar) = c_data;
            p_string_it->o_string.o_min.p_uchar ++;
            b_result = cv_true_;
        }
    }
    return b_result;
}

cv_bool cv_string_it_read_char(
    cv_string_it * p_string_it,
    unsigned char * r_data)
{
    cv_bool b_result = cv_false_;
    if (p_string_it && r_data)
    {
        if (p_string_it->o_string.o_min.pc_uchar !=
            p_string_it->o_string.o_max.pc_uchar)
        {
            *(r_data) = *(p_string_it->o_string.o_min.pc_uchar);
            p_string_it->o_string.o_min.pc_uchar ++;
            b_result = cv_true_;
        }
    }
    return b_result;
}

cv_bool cv_string_it_write_array(
    cv_string_it * p_string_it,
    cv_string const * p_string)
{
    cv_bool b_result = cv_false_;
    if (p_string_it && p_string)
    {
        long const i_string_len = cv_string_len(p_string);
        if ((p_string_it->o_string.o_min.p_uchar + i_string_len)
            <= p_string_it->o_string.o_max.p_uchar)
        {
            cv_memory_copy(
                p_string_it->o_string.o_min.p_void,
                i_string_len,
                p_string->o_min.pc_void,
                i_string_len);
            p_string_it->o_string.o_min.p_uchar += i_string_len;
            b_result = cv_true_;
        }
    }
    return b_result;
}

cv_bool cv_string_it_read_array(
    cv_string_it * p_string_it,
    cv_string const * p_string)
{
    cv_bool b_result = cv_false_;
    if (p_string_it && p_string)
    {
        long const i_string_len = cv_string_len(p_string);
        if ((p_string_it->o_string.o_min.pc_uchar + i_string_len)
            <= p_string_it->o_string.o_max.pc_uchar)
        {
            cv_memory_copy(
                p_string->o_min.p_void,
                i_string_len,
                p_string_it->o_string.o_min.pc_void,
                i_string_len);
            p_string_it->o_string.o_min.pc_uchar += i_string_len;
            b_result = cv_true_;
        }
    }
    return b_result;
}

/* end-of-file: cv_string_it.c */
