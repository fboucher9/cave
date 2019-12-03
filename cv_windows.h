/* See LICENSE for license details */

#ifndef cv_windows_h_
#define cv_windows_h_

#if defined cv_windows_

int cv_windows_stdin_fileno(void);

int cv_windows_stdout_fileno(void);

int cv_windows_stderr_fileno(void);

long cv_windows_read( int i_file_index, void * p_buffer,
    long i_buffer_length);

long cv_windows_write( int i_file_index, void const * p_buffer,
    long i_buffer_length);

int cv_windows_open_read( char const * p_name_0);

int cv_windows_open_write( char const * p_name_0);

int cv_windows_open_append( char const * p_name_0);

int cv_windows_close( int i_file_index);

#endif /* #if defined cv_windows_ */

#endif /* #ifndef cv_windows_h_ */

/* end-of-file: cv_windows.h */

