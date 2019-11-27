/* See LICENSE for license details */

#include <cv_array_it.h>

#include <cv_memory.h>

#include <cv_debug.h>

cv_bool cv_array_it_init(
    cv_array_it * p_this,
    cv_array const * p_array)
{
    cv_bool b_result = cv_false;
    if (p_this && p_array)
    {
        if (cv_array_init(&p_this->o_array))
        {
            p_this->o_array = *p_array;
            b_result = cv_true;
        }
        else
        {
            cv_debug_msg_("failed init");
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

void cv_array_it_cleanup(
    cv_array_it * p_this)
{
    if (p_this)
    {
        cv_array_cleanup(&p_this->o_array);
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
}

cv_bool cv_array_it_get_next_char(
    cv_array_it * p_this,
    cv_array_ptr * r_value)
{
    cv_bool b_result = cv_false;
    if (p_this && r_value)
    {
        if (p_this->o_array.o_min.pc_uchar !=
            p_this->o_array.o_max.pc_uchar)
        {
            *r_value = p_this->o_array.o_min;
            p_this->o_array.o_min.pc_uchar ++;
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_it_get_next_ptr(
    cv_array_it * p_this,
    cv_array_ptr * r_value)
{
    cv_bool b_result = cv_false;
    if (p_this && r_value)
    {
        if (p_this->o_array.o_min.pcpc_void <
            p_this->o_array.o_max.pcpc_void)
        {
            *r_value = p_this->o_array.o_min;
            p_this->o_array.o_min.pcpc_void ++;
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_it_get_next_array(
    cv_array_it * p_this,
    long i_array_len,
    cv_array_ptr * r_value)
{
    cv_bool b_result = cv_false;
    if (p_this && i_array_len && r_value)
    {
        if ((p_this->o_array.o_min.pc_uchar + i_array_len)
            <= p_this->o_array.o_max.pc_uchar)
        {
            *r_value = p_this->o_array.o_min;
            p_this->o_array.o_min.pc_uchar += i_array_len;
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_it_read_next_char(
    cv_array_it * p_this,
    unsigned char * r_value)
{
    cv_bool b_result = cv_false;
    if (p_this && r_value)
    {
        if (p_this->o_array.o_min.pc_uchar !=
            p_this->o_array.o_max.pc_uchar)
        {
            *(r_value) = *(p_this->o_array.o_min.pc_uchar);
            p_this->o_array.o_min.pc_uchar ++;
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_it_read_next_ptr(
    cv_array_it * p_this,
    void const * * r_value)
{
    cv_bool b_result = cv_false;
    if (p_this && r_value)
    {
        if (p_this->o_array.o_min.pcpc_void <
            p_this->o_array.o_max.pcpc_void)
        {
            *(r_value) = *(p_this->o_array.o_min.pcpc_void);
            p_this->o_array.o_min.pcpc_void ++;
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_it_read_next_array(
    cv_array_it * p_this,
    cv_array const * p_array)
{
    cv_bool b_result = cv_false;
    if (p_this && p_array)
    {
        long const i_array_len = cv_array_char_count(p_array);
        if ((p_this->o_array.o_min.pc_uchar + i_array_len)
            <= p_this->o_array.o_max.pc_uchar)
        {
            cv_memory_copy(
                p_array->o_min.p_void,
                i_array_len,
                p_this->o_array.o_min.pc_void,
                i_array_len);
            p_this->o_array.o_min.pc_uchar += i_array_len;
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_it_write_next_char(
    cv_array_it * p_this,
    unsigned char c_data)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        if (p_this->o_array.o_min.p_uchar !=
            p_this->o_array.o_max.p_uchar)
        {
            *(p_this->o_array.o_min.p_uchar) = c_data;
            p_this->o_array.o_min.p_uchar ++;
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_it_write_next_ptr(
    cv_array_it * p_this,
    void const * pc_void)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        if (p_this->o_array.o_min.ppc_void !=
            p_this->o_array.o_max.ppc_void)
        {
            *(p_this->o_array.o_min.ppc_void) = pc_void;
            p_this->o_array.o_min.ppc_void ++;
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_it_write_next_array(
    cv_array_it * p_this,
    cv_array const * p_array)
{
    cv_bool b_result = cv_false;
    if (p_this && p_array)
    {
        long const i_array_len = cv_array_char_count(p_array);
        if ((p_this->o_array.o_min.p_uchar + i_array_len)
            <= p_this->o_array.o_max.p_uchar)
        {
            cv_memory_copy(
                p_this->o_array.o_min.p_void,
                i_array_len,
                p_array->o_min.pc_void,
                i_array_len);
            p_this->o_array.o_min.p_uchar += i_array_len;
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

/* end-of-file: cv_array_it.c */
