/* See LICENSE for license details */

#include <cv_file_disk.h>

#include <cv_file_disk_desc.h>

#include <cv_memory.h>

#include <cv_sizeof.h>

#include <cv_string0.h>

#include <cv_unused.h>

#include <cv_debug.h>

#if defined cv_linux_
#include <cv_linux.h>
#endif /* #if defined cv_linux_ */

#if defined cv_linux_
static int cv_file_disk_convert_flags(
    cv_file_disk_desc const * p_desc)
{
    int i_open_flags = cv_linux_flag_cloexec | cv_linux_flag_nonblock;
    if (cv_file_disk_flag_read ==
        (p_desc->i_flags & (cv_file_disk_flag_read |
            cv_file_disk_flag_write))) {
        i_open_flags |= cv_linux_flag_rdonly;
    } else if (
        cv_file_disk_flag_write ==
        (p_desc->i_flags & (cv_file_disk_flag_read |
            cv_file_disk_flag_write))) {
        i_open_flags |= cv_linux_flag_wronly | cv_linux_flag_creat;
    } else if (
        (cv_file_disk_flag_read | cv_file_disk_flag_write) ==
        (p_desc->i_flags & (cv_file_disk_flag_read |
            cv_file_disk_flag_write))) {
        i_open_flags |= cv_linux_flag_rdwr | cv_linux_flag_creat;
    }
    if (cv_file_disk_flag_append & p_desc->i_flags) {
        i_open_flags |= cv_linux_flag_append;
    }
    return i_open_flags;
}
#endif /* #if defined cv_linux_ */

cv_bool cv_file_disk_init(
    cv_file_disk * p_this,
    cv_file_disk_desc const * p_desc)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && p_desc, "null ptr");
    cv_memory_zero(p_this, cv_sizeof_(*p_this));
    p_this->o_file.i_index = -1;
    /* Setup call to open */
    {
        cv_string0 o_name0 = cv_string0_initializer_;
        if (cv_string0_init(&o_name0, &p_desc->o_name)) {
            char const * const p_open_pathname =
                cv_string0_get(&o_name0);

#if defined cv_linux_
            int const i_open_flags =
                cv_file_disk_convert_flags(p_desc);

            /* S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; */
            int const i_open_mode =
                cv_linux_mode_user_read |
                cv_linux_mode_user_write |
                cv_linux_mode_group_read |
                cv_linux_mode_other_read;

            p_this->o_file.i_index = cv_linux_open(p_open_pathname, i_open_flags,
                i_open_mode);
#else /* #if defined cv_linux_ */
            cv_unused_(p_open_pathname);
#endif /* #if defined cv_linux_ */

            if (p_this->o_file.i_index >= 0) {
                b_result = cv_true;
            }

            cv_string0_cleanup(&o_name0);
        }
    }
    return b_result;
}

void cv_file_disk_cleanup(
    cv_file_disk * p_this)
{
    cv_debug_assert_(!!p_this, "null ptr");
    /* Setup call to close */
    if (p_this->o_file.i_index >= 0)
    {
#if defined cv_have_libc_
        cv_linux_close(p_this->o_file.i_index);
#endif /* #if defined cv_have_libc_ */
        p_this->o_file.i_index = -1;
    }
}

/* end-of-file: cv_file_disk.c */
