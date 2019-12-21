/* See LICENSE for license details */

/*
 *
 */

#include <cv_debug/cv_debug.h>

#if defined cv_debug_

#include <cv_runtime.h>

#if defined cv_have_libc_
#include <stdio.h>
#endif /* #if defined cv_have_libc_ */

/*
 *
 */

void xx_debug_msg( cv_debug_code e_code, char const * p_file, int i_line) {
#if defined cv_have_libc_
    fprintf(stderr, "*** %s:%d:%s ***\n", p_file, i_line, e_code);
#else /* #if defiend cv_have_libc_ */
    (void)(e_code);
    (void)(p_file);
    (void)(i_line);
#endif /* #if defined cv_have_libc_ */
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
