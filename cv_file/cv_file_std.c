/* See LICENSE for license details */

/*
 *
 */

#include <cv_file/cv_file_std.h>
#include <cv_file/cv_file.h>
#include <cv_thread/cv_once.h>
#include <cv_runtime.h>

static cv_file g_file_std_in = {0};
static cv_file g_file_std_out = {0};
static cv_file g_file_std_err = {0};
static struct cv_once g_once = {0};

/*
 *
 */

static void cv_file_std_once(void) {
    if (cv_once_lock(&g_once)) {
        cv_file_set_index(&g_file_std_err, cv_runtime_stderr_fileno());
        cv_file_set_index(&g_file_std_out, cv_runtime_stdout_fileno());
        cv_file_set_index(&g_file_std_in, cv_runtime_stdin_fileno());
        cv_once_unlock(&g_once);
    }
}

/*
 *
 */

cv_file const * cv_file_std_in(void) {
    cv_file_std_once();
    return &g_file_std_in;
}

/*
 *
 */

cv_file const * cv_file_std_out(void) {
    cv_file_std_once();
    return &g_file_std_out;
}

/*
 *
 */

cv_file const * cv_file_std_err(void) {
    cv_file_std_once();
    return &g_file_std_err;
}

/* end-of-file: cv_file_std.c */
