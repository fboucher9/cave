/* See LICENSE for license details */

#if defined cv_linux_

#include <cv_linux.h>

#include <cv_cast.h>

#include <cv_debug.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

/*
 *
 */

long cv_linux_read(
    int i_file_index,
    void * p_buffer,
    long i_buffer_length)
{
    long i_result = -1;
    ssize_t i_read_result = -1;
    size_t i_read_len = cv_cast_(size_t, i_buffer_length);
    cv_debug_assert_(
        ((i_file_index >= 0) && (p_buffer) && (i_buffer_length > 0)),
        "invalid param");
    i_read_result = read(
        i_file_index,
        p_buffer,
        i_read_len);
    i_result = cv_cast_(long, i_read_result);
    return i_result;
}

/*
 *
 */

long cv_linux_write(
    int i_file_index,
    void const * p_buffer,
    long i_buffer_length)
{
    long i_result = -1;
    ssize_t i_write_result = -1;
    size_t i_write_len = cv_cast_(size_t, i_buffer_length);
    cv_debug_assert_(
        ((i_file_index >= 0) && (p_buffer) && (i_buffer_length > 0)),
        "invalid param");
    i_write_result = write(
        i_file_index,
        p_buffer,
        i_write_len);
    i_result = cv_cast_(long, i_write_result);
    return i_result;
}

int cv_linux_open(
    char const * p_name_0,
    int i_flags,
    int i_mode)
{
    int i_file_index = -1;

    int const i_converted_flags =
        ((i_flags & cv_linux_flag_rdonly) ? O_RDONLY : 0)
        | ((i_flags & cv_linux_flag_wronly) ? O_WRONLY : 0)
        | ((i_flags & cv_linux_flag_rdwr) ? O_RDWR : 0)
        | ((i_flags & cv_linux_flag_creat) ? O_CREAT : 0)
        | ((i_flags & cv_linux_flag_append) ? O_APPEND : 0)
        | ((i_flags & cv_linux_flag_cloexec) ? O_CLOEXEC : 0)
        | ((i_flags & cv_linux_flag_nonblock) ? O_NONBLOCK : 0);

    mode_t const i_converted_mode =
        cv_cast_(mode_t,
            ((i_mode & cv_linux_mode_user_read) ? S_IRUSR : 0)
            | ((i_mode & cv_linux_mode_user_write) ? S_IWUSR : 0)
            | ((i_mode & cv_linux_mode_group_read) ? S_IRGRP : 0)
            | ((i_mode & cv_linux_mode_group_write) ? S_IWGRP : 0)
            | ((i_mode & cv_linux_mode_other_read) ? S_IROTH : 0)
            | ((i_mode & cv_linux_mode_other_write) ? S_IWOTH : 0));

    i_file_index = open(p_name_0,
        i_converted_flags,
        i_converted_mode);

    return i_file_index;
}

int cv_linux_close(
    int i_file_index)
{
    int i_close_result = -1;
    cv_debug_assert_(i_file_index >= 0, "invalid param");
    i_close_result = close(i_file_index);
    return i_close_result;
}

#else /* #if defined cv_linux_ */

typedef void cv_avoid_empty_unit;

#endif /* #if defined cv_linux_ */
