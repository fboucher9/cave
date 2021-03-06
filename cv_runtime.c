/* See LICENSE for license details */

#include <cv_runtime.h>
#if defined cv_have_libc_
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif /* #if defined cv_have_libc_ */
#include <cv_misc/cv_bool.h>
#include <cv_linux.h>
#include <cv_windows.h>
#include <cv_misc/cv_convert.h>
#include <cv_algo/cv_array_ptr.h>
#include <cv_misc/cv_limits.h>

void * cv_runtime_malloc( cv_uptr i_buffer_len) {
    void * p_buffer = 0;
#if defined cv_have_libc_
    if (i_buffer_len > 0) {
        size_t const i_malloc_len = i_buffer_len;
        p_buffer = malloc(i_malloc_len);
    }
#else /* #if defined cv_have_libc_ */
    (void)(i_buffer_len);
#endif /* #if defined cv_have_libc_ */
    return p_buffer;
}

void cv_runtime_free( void * p_buffer) {
#if defined cv_have_libc_
    free(p_buffer);
#else /* #if defined cv_have_libc_ */
    (void)(p_buffer);
#endif /* #if defined cv_have_libc_ */
}

void cv_runtime_memset( void * p_buf, unsigned char c_value, cv_uptr i_buf_len) {
#if defined cv_have_libc_
    if (i_buf_len > 0) {
        size_t const i_memset_len = i_buf_len;
        memset(p_buf, c_value, i_memset_len);
    }
#else /* #if defined cv_have_libc_ */
    cv_array_ptr o_buf_it = {0};
    o_buf_it.p_void = p_buf;
    if (i_buf_len > 0) {
        unsigned char * const p_buf_end = o_buf_it.p_uchar + i_buf_len;
        while (o_buf_it.p_uchar < p_buf_end) {
            *(o_buf_it.p_uchar) = c_value;
            o_buf_it.p_uchar ++;
        }
    }
#endif /* #if defined cv_have_libc_ */
}

void cv_runtime_memcpy( void * p_dst, void const * p_src, cv_uptr i_copy_len) {
#if defined cv_have_libc_
    if (i_copy_len > 0) {
        size_t const i_memcpy_len = i_copy_len;
        memcpy(p_dst, p_src, i_memcpy_len);
    }
#else /* #if defined cv_have_libc_ */
    cv_array_ptr o_dst_it = {0};
    cv_array_ptr o_src_it = {0};
    cv_uptr i_remain = i_copy_len;
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

void const * cv_runtime_memchr( void const * p_src, unsigned char c_value,
    cv_uptr i_src_len) {
    void const * p_memchr_result = 0;
#if defined cv_have_libc_
    if (i_src_len > 0) {
        size_t const i_memchr_len = i_src_len;
        p_memchr_result = memchr(p_src, c_value, i_memchr_len);
    }
#else /* #if defined cv_have_libc_ */
    cv_bool b_found = cv_false;
    cv_array_ptr o_src_it = {0};
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

int cv_runtime_memcmp( void const * p_left, void const * p_right,
    cv_uptr i_len) {
    int i_memcmp_result = -1;
#if defined cv_have_libc_
    if (i_len > 0) {
        size_t const i_memcmp_len = i_len;
        i_memcmp_result = memcmp(p_left, p_right, i_memcmp_len);
    }
#else /* #if defined cv_have_libc_ */
    (void)(p_left);
    (void)(p_right);
    (void)(i_len);
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
    (void)(p_name_0);
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
    (void)(p_name_0);
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
    (void)(p_name_0);
#endif /* #if defined cv_linux_ */
    return i_file_index;
}

int cv_runtime_close( int i_file_index) {
#if defined cv_linux_
    cv_linux_close(i_file_index);
#elif defined cv_windows_
    cv_windows_close(i_file_index);
#else /* #if defined cv_linux_ */
    (void)(i_file_index);
#endif /* #if defined cv_linux_ */
    return 0;
}

cv_sptr cv_runtime_read( int i_file_index, void * p_buffer,
    cv_uptr i_buffer_length) {
    cv_sptr i_result = -1;
#if defined cv_linux_
    i_result = cv_linux_read(i_file_index, p_buffer, i_buffer_length);
#elif defined cv_windows_
    i_result = cv_windows_read(i_file_index, p_buffer, i_buffer_length);
#else /* #if defined cv_linux_ */
    (void)(i_file_index);
    (void)(p_buffer);
    (void)(i_buffer_length);
#endif /* #if defined cv_linux_ */
    return i_result;
}

cv_sptr cv_runtime_write( int i_file_index, void const * p_buffer,
    cv_uptr i_buffer_length) {
    cv_sptr i_result = -1;
#if defined cv_linux_
    i_result = cv_linux_write(i_file_index, p_buffer, i_buffer_length);
#else /* #if defined cv_linux_ */
#if defined cv_windows_
    i_result = cv_windows_write(i_file_index, p_buffer, i_buffer_length);
#else /* #if defined cv_linux_ */
    (void)(i_file_index);
    (void)(p_buffer);
    (void)(i_buffer_length);
#endif /* #if defined cv_windows_ */
#endif /* #if defined cv_linux_ */
    return i_result;
}

void cv_runtime_exit( int i_exit_code) {
    if (i_exit_code) {
#if defined cv_linux_
        cv_linux_exit(i_exit_code);
#else /* #if defined cv_linux_ */
#if defined cv_have_libc_
        exit(i_exit_code);
#endif /* #if defined cv_have_libc_ */
#endif /* #if defined cv_linux_ */
    }
}

/* end-of-file: cv_runtime.c */
