/* See LICENSE for license details */

#ifndef cv_linux_h_
#define cv_linux_h_

#if defined cv_linux_

#include <cv_misc/cv_types.h>

int cv_linux_stdin_fileno(void);

int cv_linux_stdout_fileno(void);

int cv_linux_stderr_fileno(void);

cv_sptr cv_linux_read(
    int i_file_index,
    void * p_buffer,
    cv_uptr i_buffer_length);

cv_sptr cv_linux_write(
    int i_file_index,
    void const * p_buffer,
    cv_uptr i_buffer_length);

int cv_linux_open_read(
    char const * p_name_0);

int cv_linux_open_write(
    char const * p_name_0);

int cv_linux_open_append(
    char const * p_name_0);

int cv_linux_close(
    int i_file_index);

void cv_linux_exit(int i_exit_code);

#endif /* #if defined cv_linux_ */

#endif /* #ifndef cv_linux_h_ */

/* end-of-file: cv_linux.h */
