/* See LICENSE for license details */

#if defined cv_windows_

#include <cv_windows.h>
#include <cv_misc/cv_unused.h>
#include <cv_misc/cv_limits.h>
#include <io.h>
#include <stdio.h>

int cv_windows_stdin_fileno(void) {
    return _fileno(stdin);
}

int cv_windows_stdout_fileno(void) {
    return _fileno(stdout);
}

int cv_windows_stderr_fileno(void) {
    return _fileno(stderr);
}

long cv_windows_read( int i_file_index, void * p_buffer,
    long i_buffer_length) {
    long i_result = -1;
    if (i_buffer_length > 0) {
        unsigned long int const u_buffer_length =
            (i_buffer_length & cv_signed_long_max_);
        i_result = _read(i_file_index, p_buffer, u_buffer_length);
    }
    return i_result;
}

long cv_windows_write( int i_file_index, void const * p_buffer,
    long i_buffer_length) {
    long i_result = -1;
    if (i_buffer_length > 0) {
        unsigned long int const u_buffer_length =
            (i_buffer_length & cv_signed_long_max_);
        i_result = _write(i_file_index, p_buffer, u_buffer_length);
    }
    return i_result;
}

int cv_windows_open_read( char const * p_name_0) {
    cv_unused_(p_name_0);
    return -1;
}

int cv_windows_open_write( char const * p_name_0) {
    cv_unused_(p_name_0);
    return -1;
}

int cv_windows_open_append( char const * p_name_0) {
    cv_unused_(p_name_0);
    return -1;
}

int cv_windows_close( int i_file_index) {
    cv_unused_(i_file_index);
    return -1;
}

#else /* #if defined cv_windows_ */

typedef void cv_avoid_empty_unit;

#endif /* #if defined cv_windows_ */

/* end-of-file: cv_windows.c */
