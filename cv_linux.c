/* See LICENSE for license details */

#if defined cv_linux_

#include <cv_linux.h>

#include <cv_cast.h>

#include <cv_debug.h>

#include <unistd.h>

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

#else /* #if defined cv_linux_ */

typedef void cv_avoid_empty_unit;

#endif /* #if defined cv_linux_ */
