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

enum cv_linux_open_flags {
    /* O_RDONLY */
    cv_linux_flag_rdonly = 1,
    /* O_WRONLY */
    cv_linux_flag_wronly = 2,
    /* O_RDWR */
    cv_linux_flag_rdwr = 4,
    /* O_CREAT */
    cv_linux_flag_creat = 8,
    /* O_APPEND */
    cv_linux_flag_append = 16,
    /* O_CLOEXEC */
    cv_linux_flag_cloexec = 32,
    /* O_NONBLOCK */
    cv_linux_flag_nonblock = 64
};

enum cv_linux_open_mode {
    /* S_IRUSR */
    cv_linux_mode_user_read = 1,
    /* S_IWUSR */
    cv_linux_mode_user_write = 2,
    /* S_IRGRP */
    cv_linux_mode_group_read = 4,
    /* S_IWGRP */
    cv_linux_mode_group_write = 8,
    /* S_IROTH */
    cv_linux_mode_other_read = 16,
    /* S_IWOTH */
    cv_linux_mode_other_write = 32
};

int cv_linux_open(
    char const * p_name_0,
    int i_flags,
    int i_mode);

int cv_linux_close(
    int i_file_index);

#endif /* #if defined cv_linux_ */

#endif /* #ifndef cv_linux_h_ */

/* end-of-file: cv_linux.h */
