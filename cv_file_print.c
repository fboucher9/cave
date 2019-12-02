/* See LICENSE for license details */

/*
 *
 */

#include <cv_file_print.h>
#include <cv_file.h>
#include <cv_array.h>
#include <cv_array_tool.h>
#include <cv_debug.h>
#include <cv_sizeof.h>
#include <cv_string_it.h>
#include <cv_number_enc.h>

/*
 *
 */

void cv_file_print_array( cv_file const * p_file,
    cv_array const * p_array) {
    cv_bool b_result = cv_true;
    cv_array o_array_it = cv_array_null_;
    cv_debug_assert_(p_file && p_array, "null ptr");
    cv_array_init_ref(&o_array_it, p_array);
    while (b_result &&
        (o_array_it.o_min.pc_char != o_array_it.o_max.pc_char)) {
        long const i_write_result = cv_file_write(
            p_file,
            & o_array_it);
        if (i_write_result > 0) {
            o_array_it.o_min.pc_char += i_write_result;
        } else {
            b_result = cv_false;
        }
    }
    cv_array_cleanup(&o_array_it);
}

/*
 *
 */

void cv_file_print_number( cv_file const * p_file,
    cv_number_desc const * p_desc) {
    char c_buffer[64u];
    cv_array o_buffer = cv_array_null_;
    cv_debug_assert_(p_file && p_desc, "null ptr");
    cv_array_init_vector(&o_buffer, c_buffer, cv_sizeof_(c_buffer));
    {
        cv_array o_result = cv_array_null_;
        cv_array_init(&o_result);
        if (cv_number_status_done ==
            cv_number_enc_convert(p_desc, &o_buffer, &o_result)) {
            cv_file_print_array(p_file, &o_result);
        }
        cv_array_cleanup(&o_result);
    }
    cv_array_cleanup(&o_buffer);
}

/*
 *
 */

void cv_file_print_nl( cv_file const * p_file) {
    static unsigned char g_nl_text[] = { '\n' };
    static cv_array const g_nl_array = cv_array_text_initializer_(g_nl_text);
    cv_debug_assert_(!!p_file, "null ptr");
    cv_file_print_array(p_file, &g_nl_array);
}

/* end-of-file: cv_file_print.c */
