/* See LICENSE for license details */

#include <cv_file/cv_file_std.h>
#include <cv_file/cv_file.h>
#include <cv_algo/cv_array.h>
#include <cv_algo/cv_array_tool.h>
#include <cv_debug.h>
#include <cv_runtime.h>

static cv_file g_file_std_in = cv_file_initializer_;
static cv_file g_file_std_out = cv_file_initializer_;
static cv_file g_file_std_err = cv_file_initializer_;

cv_bool cv_file_std_load(void) {
    cv_file_init(&g_file_std_err);
    g_file_std_err.i_index = cv_runtime_stderr_fileno();
    cv_file_init(&g_file_std_out);
    g_file_std_out.i_index = cv_runtime_stdout_fileno();
    cv_file_init(&g_file_std_in);
    g_file_std_in.i_index = cv_runtime_stdin_fileno();
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
