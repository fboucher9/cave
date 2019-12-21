/* See LICENSE for license details */

#ifndef cv_runtime_h_
#define cv_runtime_h_

/*
 *  Module: cv_runtime.h
 *
 *  Description: Wrappers for standard library services.
 */

#include <cv_misc/cv_types.h>

void * cv_runtime_malloc( cv_uptr i_malloc_len);

void cv_runtime_free( void * p_buffer);

void cv_runtime_memset( void * p_buf, unsigned char c_fill_value,
    cv_uptr i_buf_len);

void cv_runtime_memcpy( void * p_dst, void const * p_src, cv_uptr i_copy_len);

void const * cv_runtime_memchr( void const * p_src,
    unsigned char c_value, cv_uptr i_src_len);

int cv_runtime_memcmp( void const * p_left, void const * p_right,
    cv_uptr i_len);

int cv_runtime_stdin_fileno(void);

int cv_runtime_stdout_fileno(void);

int cv_runtime_stderr_fileno(void);

int cv_runtime_open_read( char const * p_name_0);

int cv_runtime_open_write( char const * p_name_0);

int cv_runtime_open_append( char const * p_name_0);

int cv_runtime_close( int i_file_index);

cv_sptr cv_runtime_read( int i_file_index, void * p_buffer,
    cv_uptr i_buffer_length);

cv_sptr cv_runtime_write( int i_file_index, void const * p_buffer,
    cv_uptr i_buffer_length);

void cv_runtime_exit(int i_exit_code);

#endif /* #ifndef cv_runtime_h_ */

/* end-of-file: cv_runtime.h */
