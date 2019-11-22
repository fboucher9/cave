/* See LICENSE for license details */

#include <cv_file_std.h>

#include <fcntl.h>

static cv_file_std g_file_stdin = cv_file_std_initializer_;

static cv_file_std g_file_stdout = cv_file_std_initializer_;

static cv_file_std g_file_stderr = cv_file_std_initializer_;

cv_file_std const * cv_file_std_in(void)
{
    return & g_file_stdin;
}

cv_file_std const * cv_file_std_out(void)
{
    return & g_file_stdout;
}

cv_file_std const * cv_file_std_err(void)
{
    return & g_file_stderr;
}

static void cv_file_std_set_non_blocking(
    cv_file_std const * p_this)
{
    int i_flags = fcntl(p_this->o_file.i_index,
        F_GETFL, 0);
    fcntl(p_this->o_file.i_index,
        F_SETFL, i_flags | O_NONBLOCK);
}

cv_bool cv_file_std_load(void)
{
    g_file_stdin.o_file.i_index = 0;

    g_file_stdout.o_file.i_index = 1;

    g_file_stderr.o_file.i_index = 2;

    if (0)
    {
        cv_file_std_set_non_blocking(&g_file_stdin);

        cv_file_std_set_non_blocking(&g_file_stdout);

        cv_file_std_set_non_blocking(&g_file_stderr);
    }

    return cv_true_;
}

void cv_file_std_unload(void)
{
    g_file_stdin.o_file.i_index = -1;

    g_file_stdout.o_file.i_index = -1;

    g_file_stderr.o_file.i_index = -1;
}

