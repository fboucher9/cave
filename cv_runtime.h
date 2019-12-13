/* See LICENSE for license details */

#ifndef cv_runtime_h_
#define cv_runtime_h_

/*
 *  Module: cv_runtime.h
 *
 *  Description: Wrappers for standard library services.
 */

void * cv_runtime_malloc( long i_malloc_len);

void cv_runtime_free( void * p_buffer);

#if defined __GNUC__
__attribute__((format(printf, 1, 2)))
#endif /* #if defined __GNUC__ */
void cv_runtime_printf( char const * p_format0, ...);

void cv_runtime_memset( void * p_buf, unsigned char c_fill_value,
    long i_buf_len);

void cv_runtime_memcpy( void * p_dst, void const * p_src, long i_copy_len);

void const * cv_runtime_memchr( void const * p_src,
    unsigned char c_value, long i_src_len);

int cv_runtime_memcmp( void const * p_left, void const * p_right,
    long i_len);

int cv_runtime_stdin_fileno(void);

int cv_runtime_stdout_fileno(void);

int cv_runtime_stderr_fileno(void);

int cv_runtime_open_read( char const * p_name_0);

int cv_runtime_open_write( char const * p_name_0);

int cv_runtime_open_append( char const * p_name_0);

int cv_runtime_close( int i_file_index);

long cv_runtime_read( int i_file_index, void * p_buffer,
    long i_buffer_length);

long cv_runtime_write( int i_file_index, void const * p_buffer,
    long i_buffer_length);

void cv_runtime_exit(int i_exit_code);

#endif /* #ifndef cv_runtime_h_ */

/* end-of-file: cv_runtime.h */
