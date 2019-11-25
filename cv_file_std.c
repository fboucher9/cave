/* See LICENSE for license details */

#include <cv_file_std.h>

#include <cv_string.h>

#include <cv_memory.h>

cv_file_std g_cv_file_std_in = cv_file_std_initializer_;

cv_file_std g_cv_file_std_out = cv_file_std_initializer_;

cv_file_std g_cv_file_std_err = cv_file_std_initializer_;

cv_bool cv_file_std_load(void)
{
    g_cv_file_std_in.o_file.i_index = 0;

    g_cv_file_std_out.o_file.i_index = 1;

    g_cv_file_std_err.o_file.i_index = 2;

    return cv_true;
}

void cv_file_std_unload(void)
{
    g_cv_file_std_in.o_file.i_index = -1;

    g_cv_file_std_out.o_file.i_index = -1;

    g_cv_file_std_err.o_file.i_index = -1;
}

cv_bool cv_file_std_out_write(
    cv_array const * p_array)
{
    cv_bool b_result = cv_true;
    cv_array o_array_it = cv_array_initializer_;
    o_array_it = *p_array;
    while (b_result &&
        (o_array_it.o_min.pc_char != o_array_it.o_max.pc_char))
    {
        long const i_write_result = cv_file_write(
            & g_cv_file_std_out.o_file,
            & o_array_it);
        if (i_write_result > 0)
        {
            o_array_it.o_min.pc_char += i_write_result;
        }
        else
        {
            b_result = cv_false;
        }
    }
    return b_result;
}

cv_bool cv_file_std_out_write0(
    char const * const p_msg0,
    long i_msg0_max_len)
{
    cv_bool b_result = cv_false;
    cv_string o_string = cv_string_initializer_;
    if (cv_string_init(&o_string))
    {
        if (cv_string_setup0(&o_string, p_msg0, i_msg0_max_len))
        {
            b_result = cv_file_std_out_write(&o_string.o_array);
        }
        cv_string_cleanup(&o_string);
    }
    return b_result;
}

