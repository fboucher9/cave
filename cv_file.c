/* See LICENSE for license details */

#include <cv_file.h>

#include <cv_array.h>

#if defined cv_have_libc_
#include <unistd.h>
#endif /* #if defined cv_have_libc_ */

long cv_file_read(
    cv_file const * p_this,
    cv_array const * p_array)
{
    long i_result = -1;
    if (p_this && p_array)
    {
        long const i_array_len = cv_array_len(p_array);
        if (i_array_len >= 0)
        {
#if defined cv_have_libc_
            if (p_this->i_index >= 0)
            {
                ssize_t i_read_result = -1;
                size_t i_read_len = cv_cast_(size_t, i_array_len);
                i_read_result = read(p_this->i_index,
                    p_array->o_min.p_void,
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
    cv_array const * p_array)
{
    long i_result = -1;
    if (p_this && p_array)
    {
        long const i_array_len = cv_array_len(p_array);
        if (i_array_len >= 0)
        {
#if defined cv_have_libc_
            if (p_this->i_index >= 0)
            {
                ssize_t i_write_result = -1;
                size_t i_write_len = cv_cast_(size_t, i_array_len);
                i_write_result = write(p_this->i_index,
                    p_array->o_min.pc_void,
                    i_write_len);
                i_result = cv_cast_(long, i_write_result);
            }
#endif /* #if defined cv_have_libc_ */
        }
    }
    return i_result;
}

