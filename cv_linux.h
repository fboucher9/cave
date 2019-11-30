/* See LICENSE for license details */

#ifndef cv_linux_h_
#define cv_linux_h_

#if defined cv_linux_

long cv_linux_read(
    int i_file_index,
    void * p_buffer,
    long i_buffer_length);

long cv_linux_write(
    int i_file_index,
    void const * p_buffer,
    long i_buffer_length);

#endif /* #if defined cv_linux_ */

#endif /* #ifndef cv_linux_h_ */

/* end-of-file: cv_linux.h */
