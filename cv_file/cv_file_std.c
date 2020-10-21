/* See LICENSE for license details */

/*
 *
 */

#include <cv_file/cv_file_std.h>
#include <cv_file/cv_file.h>
#include <cv_thread/cv_once.h>
#include <cv_runtime.h>
#include <cv_debug/cv_debug.h>

static cv_file g_file_std_in = {0};
static cv_file g_file_std_out = {0};
static cv_file g_file_std_err = {0};
static cv_bool g_file_std_loaded = cv_false;

/*
 *
 */

void cv_file_std_load(void) {
    if (!g_file_std_loaded) {
        cv_file_set_index(&g_file_std_err, cv_runtime_stderr_fileno());
        cv_file_set_index(&g_file_std_out, cv_runtime_stdout_fileno());
        cv_file_set_index(&g_file_std_in, cv_runtime_stdin_fileno());
        g_file_std_loaded = cv_true;
    }
}

/*
 *
 */

void cv_file_std_unload(void) {
    if (g_file_std_loaded) {
        g_file_std_loaded = cv_false;
    }
}

/*
 *
 */

cv_file const * cv_file_std_in(void) {
    cv_debug_assert_(g_file_std_loaded, cv_debug_code_not_loaded);
    return &g_file_std_in;
}

/*
 *
 */

cv_file const * cv_file_std_out(void) {
    cv_debug_assert_(g_file_std_loaded, cv_debug_code_not_loaded);
    return &g_file_std_out;
}

/*
 *
 */

cv_file const * cv_file_std_err(void) {
    cv_debug_assert_(g_file_std_loaded, cv_debug_code_not_loaded);
    return &g_file_std_err;
}

/* end-of-file: cv_file_std.c */
