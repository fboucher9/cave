/* See LICENSE for license details */

#include <cv_file_std.h>
#include <cv_file.h>
#include <cv_array.h>
#include <cv_array_tool.h>
#include <cv_debug.h>

static cv_file g_file_std_in = cv_file_initializer_;
static cv_file g_file_std_out = cv_file_initializer_;
static cv_file g_file_std_err = cv_file_initializer_;

cv_bool cv_file_std_load(void) {
    cv_file_init(&g_file_std_err);
#if defined cv_linux_
    g_file_std_err.i_index = 2;
#endif /* #if defined cv_linux_ */
    cv_file_init(&g_file_std_out);
#if defined cv_linux_
    g_file_std_out.i_index = 1;
#endif /* #if defined cv_linux_ */
    cv_file_init(&g_file_std_in);
#if defined cv_linux_
    g_file_std_in.i_index = 0;
#endif /* #if defined cv_linux_ */
    return cv_true;
}

void cv_file_std_unload(void) {
    cv_file_cleanup(&g_file_std_in);
    cv_file_cleanup(&g_file_std_out);
    cv_file_cleanup(&g_file_std_err);
}

cv_file const * cv_file_std_in(void) {
    return &g_file_std_in;
}

cv_file const * cv_file_std_out(void) {
    return &g_file_std_out;
}

cv_file const * cv_file_std_err(void) {
    return &g_file_std_err;
}

/* end-of-file: cv_file_std.c */
