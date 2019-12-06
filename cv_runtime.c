/* See LICENSE for license details */

#include <cv_runtime.h>
#if defined cv_have_libc_
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif /* #if defined cv_have_libc_ */
#include <cv_bool.h>
#include <cv_null.h>
#include <cv_unused.h>
#include <cv_linux.h>
#include <cv_windows.h>
#include <cv_convert.h>
#include <cv_array_ptr.h>

void * cv_runtime_malloc(
    long i_buffer_len)
{
    void * p_buffer = cv_null_;
#if defined cv_have_libc_
    unsigned long const u_buffer_len = cv_convert_l2u_(i_buffer_len);
    size_t const i_malloc_len = u_buffer_len;
    p_buffer = malloc(i_malloc_len);
#else /* #if defined cv_have_libc_ */
    cv_unused_(i_buffer_len);
#endif /* #if defined cv_have_libc_ */
    return p_buffer;
}

void cv_runtime_free(
    void * p_buffer)
{
#if defined cv_have_libc_
    free(p_buffer);
#else /* #if defined cv_have_libc_ */
    cv_unused_(p_buffer);
#endif /* #if defined cv_have_libc_ */
}

void cv_runtime_printf(
    char const * p_format0,
    ...)
{
#if defined cv_have_libc_
    va_list o_arg_list;
    va_start(o_arg_list, p_format0);
    vfprintf(stdout, p_format0, o_arg_list);
    fflush(stdout);
    va_end(o_arg_list);
#else /* #if defined cv_have_libc_ */
    cv_unused_(p_format0);
#endif /* #if defined cv_have_libc_ */
}

void cv_runtime_memset(
    void * p_buf,
    unsigned char c_value,
    long i_buf_len)
{
#if defined cv_have_libc_
    unsigned long const u_buf_len = cv_convert_l2u_(i_buf_len);
    size_t const i_memset_len = u_buf_len;
    memset(p_buf, c_value, i_memset_len);
#else /* #if defined cv_have_libc_ */
    cv_array_ptr o_buf_it = cv_ptr_null_;
    o_buf_it.p_void = p_buf;
    {
        unsigned char * const p_buf_end = o_buf_it.p_uchar + i_buf_len;
        while (o_buf_it.p_uchar < p_buf_end) {
            *(o_buf_it.p_uchar) = c_value;
            o_buf_it.p_uchar ++;
        }
    }
#endif /* #if defined cv_have_libc_ */
}

void cv_runtime_memcpy(
    void * p_dst,
    void const * p_src,
    long i_copy_len)
{
#if defined cv_have_libc_
    unsigned long int const u_copy_len = cv_convert_l2u_(i_copy_len);
    size_t const i_memcpy_len = u_copy_len;
    memcpy(p_dst, p_src, i_memcpy_len);
#else /* #if defined cv_have_libc_ */
    cv_array_ptr o_dst_it = cv_ptr_null_;
    cv_array_ptr o_src_it = cv_ptr_null_;
    long i_remain = i_copy_len;
    o_dst_it.p_void = p_dst;
    o_src_it.pc_void = p_src;
    while (i_remain > 0) {
        *o_dst_it.p_char = *o_src_it.pc_char;
        o_dst_it.p_char ++;
        o_src_it.pc_char ++;
        i_remain --;
    }
#endif /* #if defined cv_have_libc_ */
}

void const * cv_runtime_memchr(
    void const * p_src,
    unsigned char c_value,
    long i_src_len)
{
    void const * p_memchr_result = cv_null_;
#if defined cv_have_libc_
    unsigned long int const u_src_len = cv_convert_l2u_(i_src_len);
    size_t const i_memchr_len = u_src_len;
    p_memchr_result = memchr(p_src, c_value, i_memchr_len);
#else /* #if defined cv_have_libc_ */
    cv_bool b_found = cv_false;
    cv_array_ptr o_src_it = cv_ptr_null_;
    o_src_it.pc_void = p_src;
    {
        unsigned char const * p_src_end = o_src_it.pc_uchar + i_src_len;
        while (!b_found && (o_src_it.pc_uchar < p_src_end)) {
            if (c_value == *o_src_it.pc_uchar) {
                p_memchr_result = o_src_it.pc_void;
                b_found = cv_true;
            } else {
                o_src_it.pc_uchar ++;
            }
        }
    }
#endif /* #if defined cv_have_libc_ */
    return p_memchr_result;
}

int cv_runtime_memcmp(
    void const * p_left,
    void const * p_right,
    long i_len)
{
    int i_memcmp_result = -1;
#if defined cv_have_libc_
    unsigned long int const u_len = cv_convert_l2u_(i_len);
    size_t const i_memcmp_len = u_len;
    i_memcmp_result = memcmp(p_left, p_right, i_memcmp_len);
#else /* #if defined cv_have_libc_ */
    cv_unused_(p_left);
    cv_unused_(p_right);
    cv_unused_(i_len);
#endif /* #if defined cv_have_libc_ */
    return i_memcmp_result;
}

int cv_runtime_stdin_fileno(void) {
#if defined cv_linux_
    return cv_linux_stdin_fileno();
#elif defined cv_windows_
    return cv_windows_stdin_fileno();
#else /* #if defined cv_linux_ */
    return -1;
#endif /* #if defined cv_linux_ */
}

int cv_runtime_stdout_fileno(void) {
#if defined cv_linux_
    return cv_linux_stdout_fileno();
#elif defined cv_windows_
    return cv_windows_stdout_fileno();
#else /* #if defined cv_linux_ */
    return -1;
#endif /* #if defined cv_linux_ */
}

int cv_runtime_stderr_fileno(void) {
#if defined cv_linux_
    return cv_linux_stderr_fileno();
#elif defined cv_windows_
    return cv_windows_stderr_fileno();
#else /* #if defined cv_linux_ */
    return -1;
#endif /* #if defined cv_linux_ */
}

int cv_runtime_open_read( char const * p_name_0) {
    int i_file_index = -1;
#if defined cv_linux_
    i_file_index = cv_linux_open_read(p_name_0);
#elif defined cv_windows_
    i_file_index = cv_windows_open_read(p_name_0);
#else /* #if defined cv_linux_ */
    cv_unused_(p_name_0);
#endif /* #if defined cv_linux_ */
    return i_file_index;
}

int cv_runtime_open_write( char const * p_name_0) {
    int i_file_index = -1;
#if defined cv_linux_
    i_file_index = cv_linux_open_write(p_name_0);
#elif defined cv_windows_
    i_file_index = cv_windows_open_write(p_name_0);
#else /* #if defined cv_linux_ */
    cv_unused_(p_name_0);
#endif /* #if defined cv_linux_ */
    return i_file_index;
}

int cv_runtime_open_append( char const * p_name_0) {
    int i_file_index = -1;
#if defined cv_linux_
    i_file_index = cv_linux_open_append(p_name_0);
#elif defined cv_windows_
    i_file_index = cv_windows_open_append(p_name_0);
#else /* #if defined cv_linux_ */
    cv_unused_(p_name_0);
#endif /* #if defined cv_linux_ */
    return i_file_index;
}

int cv_runtime_close( int i_file_index) {
#if defined cv_linux_
    cv_linux_close(i_file_index);
#elif defined cv_windows_
    cv_windows_close(i_file_index);
#else /* #if defined cv_linux_ */
    cv_unused_(i_file_index);
#endif /* #if defined cv_linux_ */
    return 0;
}

long cv_runtime_read( int i_file_index, void * p_buffer,
    long i_buffer_length) {
    long i_result = -1;
#if defined cv_linux_
    i_result = cv_linux_read(i_file_index, p_buffer, i_buffer_length);
#elif defined cv_windows_
    i_result = cv_windows_read(i_file_index, p_buffer, i_buffer_length);
#else /* #if defined cv_linux_ */
    cv_unused_(i_file_index);
    cv_unused_(p_buffer);
    cv_unused_(i_buffer_length);
#endif /* #if defined cv_linux_ */
    return i_result;
}

long cv_runtime_write( int i_file_index, void const * p_buffer,
    long i_buffer_length) {
    long i_result = -1;
#if defined cv_linux_
    i_result = cv_linux_write(i_file_index, p_buffer, i_buffer_length);
#elif defined cv_windows_
    i_result = cv_windows_write(i_file_index, p_buffer, i_buffer_length);
#else /* #if defined cv_linux_ */
    cv_unused_(i_file_index);
    cv_unused_(p_buffer);
    cv_unused_(i_buffer_length);
#endif /* #if defined cv_linux_ */
    return i_result;
}

/* end-of-file: cv_runtime.c */
