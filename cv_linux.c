/* See LICENSE for license details */

#if defined cv_linux_

#include <cv_linux.h>
#include <cv_misc/cv_limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

int cv_linux_stdin_fileno(void) {
    return STDIN_FILENO;
}

int cv_linux_stdout_fileno(void) {
    return STDOUT_FILENO;
}

int cv_linux_stderr_fileno(void) {
    return STDERR_FILENO;
}

/*
 *
 */

cv_sptr cv_linux_read(
    int i_file_index,
    void * p_buffer,
    cv_uptr i_buffer_length)
{
    cv_sptr i_result = -1;
    if (i_buffer_length > 0) {
        ssize_t i_read_result = -1;
        size_t const i_read_len = i_buffer_length;
        i_read_result = read(
            i_file_index,
            p_buffer,
            i_read_len);
        i_result = i_read_result;
    }
    return i_result;
}

/*
 *
 */

cv_sptr cv_linux_write(
    int i_file_index,
    void const * p_buffer,
    cv_uptr i_buffer_length)
{
    cv_sptr i_result = -1;
    ssize_t i_write_result = -1;
    if (i_buffer_length > 0) {
        size_t i_write_len = i_buffer_length;
        i_write_result = write(
            i_file_index,
            p_buffer,
            i_write_len);
        i_result = i_write_result;
    }
    return i_result;
}

int cv_linux_open_read( char const * p_name_0) {
    return open(p_name_0,
        O_RDONLY | O_CLOEXEC | O_NONBLOCK,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

int cv_linux_open_write( char const * p_name_0) {
    return open(p_name_0,
        O_RDWR | O_CREAT | O_CLOEXEC | O_NONBLOCK,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

int cv_linux_open_append( char const * p_name_0) {
    return open(p_name_0,
        O_RDWR | O_CREAT | O_APPEND | O_CLOEXEC | O_NONBLOCK,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

int cv_linux_close( int i_file_index) {
    int i_close_result = -1;
    i_close_result = close(i_file_index);
    return i_close_result;
}

static int g_linux_exit_code = 0;

static void cv_linux_sigint_handler(int i_signum) {
    if (SIGINT == i_signum) {
        exit(g_linux_exit_code);
    }
}

static void cv_linux_raise_sigint(void) {
    signal(SIGINT, & cv_linux_sigint_handler);
    raise(SIGINT);
}

void cv_linux_exit(int i_exit_code) {
    g_linux_exit_code = i_exit_code;
    cv_linux_raise_sigint();
}

#else /* #if defined cv_linux_ */

typedef void cv_avoid_empty_unit;

#endif /* #if defined cv_linux_ */
