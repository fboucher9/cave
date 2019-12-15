/* See LICENSE for license details */

/*
 *
 */

#include <cv_debug/cv_debug.h>

#if defined cv_debug_

#include <cv_runtime.h>
#include <cv_algo/cv_array.h>
#include <cv_misc/cv_limits.h>
#include <cv_number_desc.h>
#include <cv_file/cv_file_std.h>
#include <cv_file/cv_file_print.h>

/*
 *
 */

void xx_debug_msg( cv_debug_code e_code, char const * p_file, int i_line) {
    static unsigned char const a_prefix[] = {
        '*', '*', '*', ' ' };
    static unsigned char const a_suffix[] = {
        ' ', '*', '*', '*' };
    cv_file const * p_stderr = cv_file_std_err();
    cv_file_print_range(p_stderr, a_prefix, a_prefix + sizeof(a_prefix));
    cv_file_print_0(p_stderr, p_file, cv_signed_short_max_);
    cv_file_print_char(p_stderr, ':');
    cv_file_print_signed(p_stderr, i_line,
        cv_number_format_dec());
    cv_file_print_char(p_stderr, ':');
    cv_file_print_array(p_stderr, e_code);
    cv_file_print_range(p_stderr, a_suffix, a_suffix + sizeof(a_suffix));
    cv_file_print_nl(p_stderr);
}

/*
 *
 */

void xx_debug_break( cv_debug_code e_code, char const * p_file, int i_line) {
    xx_debug_msg(e_code, p_file, i_line);
    cv_runtime_exit(42);
}

/*
 *
 */

void xx_debug_assert( cv_bool b_expr, cv_debug_code e_code,
    char const * p_file, int i_line) {
    if (!b_expr) {
        xx_debug_break(e_code, p_file, i_line);
    }
}

#endif /* #if defined cv_debug_ */

/* end-of-file: cv_debug.c */
