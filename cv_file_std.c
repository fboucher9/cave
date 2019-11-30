/* See LICENSE for license details */

#include <cv_file_std.h>

#include <cv_array.h>

#include <cv_array_tool.h>

#include <cv_debug.h>

static cv_file_std g_file_std_in = cv_file_std_initializer_;

static cv_file_std g_file_std_out = cv_file_std_initializer_;

static cv_file_std g_file_std_err = cv_file_std_initializer_;

cv_bool cv_file_std_load(void)
{
    g_file_std_in.o_file.i_index = 0;
    g_file_std_out.o_file.i_index = 1;
    g_file_std_err.o_file.i_index = 2;
    return cv_true;
}

void cv_file_std_unload(void)
{
    g_file_std_in.o_file.i_index = -1;
    g_file_std_out.o_file.i_index = -1;
    g_file_std_err.o_file.i_index = -1;
}

cv_file_std const * cv_file_std_in(void)
{
    return &g_file_std_in;
}

cv_file_std const * cv_file_std_out(void)
{
    return &g_file_std_out;
}

cv_file_std const * cv_file_std_err(void)
{
    return &g_file_std_err;
}

cv_bool cv_file_std_print(
    cv_array const * p_array)
{
    cv_bool b_result = cv_true;
    cv_array o_array_it = cv_array_null_;
    cv_debug_assert_(!!p_array, "null ptr");
    o_array_it = *p_array;
    while (b_result &&
        (o_array_it.o_min.pc_char != o_array_it.o_max.pc_char)) {
        long const i_write_result = cv_file_write(
            & g_file_std_out.o_file,
            & o_array_it);
        if (i_write_result > 0) {
            o_array_it.o_min.pc_char += i_write_result;
        } else {
            b_result = cv_false;
        }
    }
    return b_result;
}

cv_bool cv_file_std_print_0(
    char const * const p_msg0,
    long i_msg0_max_len)
{
    cv_bool b_result = cv_false;
    cv_array o_array = cv_array_null_;
    cv_debug_assert_(p_msg0 && (i_msg0_max_len > 0), "null ptr");
    cv_array_init_0(&o_array, p_msg0, i_msg0_max_len);
    b_result = cv_file_std_print(&o_array);
    cv_array_cleanup(&o_array);
    return b_result;
}

cv_bool cv_file_std_print_nl(void)
{
    static char const g_nl_text[] = {
        '\n'
    };
    static cv_array const g_nl_array =
        cv_array_text_initializer_(g_nl_text);
    cv_bool b_result = cv_false;
    if (cv_file_std_print(&g_nl_array)) {
        b_result = cv_true;
    }
    return b_result;
}

