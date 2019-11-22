/* See LICENSE for license details */

#include <cv_file.h>

#include <cv_string.h>

#if defined cv_have_libc_
#include <unistd.h>
#endif /* #if defined cv_have_libc_ */

long cv_file_read(
    cv_file const * p_this,
    cv_string const * p_string)
{
    long i_result = -1;
    if (p_this && p_string)
    {
        long const i_string_len = cv_string_len(p_string);
        if (i_string_len >= 0)
        {
#if defined cv_have_libc_
            if (p_this->i_index >= 0)
            {
                ssize_t i_read_result = -1;
                size_t i_read_len = cv_cast_(size_t, i_string_len);
                i_read_result = read(p_this->i_index,
                    p_string->o_min.p_void,
                    i_read_len);
                i_result = cv_cast_(long, i_read_result);
            }
#endif /* #if defined cv_have_libc_ */
        }
    }
    return i_result;
}

long cv_file_write(
    cv_file const * p_this,
    cv_string const * p_string)
{
    long i_result = -1;
    if (p_this && p_string)
    {
        long const i_string_len = cv_string_len(p_string);
        if (i_string_len >= 0)
        {
#if defined cv_have_libc_
            if (p_this->i_index >= 0)
            {
                ssize_t i_write_result = -1;
                size_t i_write_len = cv_cast_(size_t, i_string_len);
                i_write_result = write(p_this->i_index,
                    p_string->o_min.pc_void,
                    i_write_len);
                i_result = cv_cast_(long, i_write_result);
            }
#endif /* #if defined cv_have_libc_ */
        }
    }
    return i_result;
}

