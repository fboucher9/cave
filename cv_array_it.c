/* See LICENSE for license details */

#include <cv_array_it.h>

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
}

cv_bool cv_array_it_next(
    cv_array_it * p_this,
    long i_sizeof_object,
    cv_array_ptr * r_cur)
{
    cv_bool b_result = cv_false;
    if (p_this && i_sizeof_object && r_cur)
    {
        if ((p_this->o_array.o_min.pc_char + i_sizeof_object) <=
            p_this->o_array.o_max.pc_char)
        {
            *(r_cur) = p_this->o_array.o_min;
            p_this->o_array.o_min.pc_char += i_sizeof_object;
            b_result = cv_true;
        }
    }
    return b_result;
}

