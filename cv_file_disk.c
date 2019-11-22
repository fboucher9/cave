/* See LICENSE for license details */

#include <cv_file_disk.h>

#include <cv_file_disk_desc.h>

#include <cv_memory.h>

#include <cv_sizeof.h>

#include <cv_string0.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

static int cv_file_disk_convert_flags(
    cv_file_disk_desc const * p_desc)
{
    int i_open_flags = O_CLOEXEC | O_NONBLOCK;

    if (cv_file_disk_flag_read ==
        (p_desc->i_flags & (cv_file_disk_flag_read |
            cv_file_disk_flag_write)))
    {
        i_open_flags |= O_RDONLY;
    }
    else if (
        cv_file_disk_flag_write ==
        (p_desc->i_flags & (cv_file_disk_flag_read |
            cv_file_disk_flag_write)))
    {
        i_open_flags |= O_WRONLY | O_CREAT;
    }
    else if (
        (cv_file_disk_flag_read | cv_file_disk_flag_write) ==
        (p_desc->i_flags & (cv_file_disk_flag_read |
            cv_file_disk_flag_write)))
    {
        i_open_flags |= O_RDWR | O_CREAT;
    }

    if (cv_file_disk_flag_append & p_desc->i_flags)
    {
        i_open_flags |= O_APPEND;
    }

    return i_open_flags;
}

cv_bool cv_file_disk_init(
    cv_file_disk * p_this,
    cv_file_disk_desc const * p_desc)
{
    cv_bool b_result = cv_false_;
    if (p_this && p_desc)
    {
        cv_memory_zero(p_this, cv_sizeof_(*p_this));
        p_this->o_file.i_index = -1;
        /* Setup call to open */
        {
            cv_string0 o_name0 = cv_string0_initializer_;

            if (cv_string0_init(&o_name0, &p_desc->o_name))
            {
                char const * const p_open_pathname =
                    cv_string0_get(&o_name0);

                int const i_open_flags =
                    cv_file_disk_convert_flags(p_desc);

                mode_t const i_open_mode =
                    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

                p_this->o_file.i_index = open(p_open_pathname, i_open_flags,
                    i_open_mode);

                if (p_this->o_file.i_index >= 0)
                {
                    b_result = cv_true_;
                }

                cv_string0_cleanup(&o_name0);
            }
        }
    }
    return b_result;
}

void cv_file_disk_cleanup(
    cv_file_disk * p_this)
{
    if (p_this)
    {
        /* Setup call to close */
        if (p_this->o_file.i_index >= 0)
        {
            close(p_this->o_file.i_index);
            p_this->o_file.i_index = -1;
        }
    }
}

/* end-of-file: cv_file_disk.c */
