/* See LICENSE for license details */

#include <cv_file.h>

#include <cv_array.h>

#if defined cv_linux_
#include <cv_linux.h>
#endif /* #if defined cv_linux_ */

#include <cv_debug.h>

long cv_file_read(
    cv_file const * p_this,
    cv_array const * p_array)
{
    long i_result = -1;
    cv_debug_assert_(
        p_this && p_array,
        "null ptr");
    {
        long const i_array_len = cv_array_len(p_array);
        if (i_array_len > 0)
        {
#if defined cv_linux_
            if (p_this->i_index >= 0)
            {
                i_result = cv_linux_read(
                    p_this->i_index,
                    p_array->o_min.p_void,
                    i_array_len);
            }
#endif /* #if defined cv_linux_ */
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
                i_result = cv_linux_write(
                    p_this->i_index,
                    p_array->o_min.p_void,
                    i_array_len);
            }
#endif /* #if defined cv_have_libc_ */
        }
    }
    return i_result;
}

