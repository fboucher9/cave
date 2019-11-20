/* See LICENSE for license details */

#include <cv_memory.h>

#include <cv_cast.h>

#include <string.h>

void cv_memory_zero(
    void * p_buf,
    long i_buf_len)
{
    size_t const i_memset_len = cv_cast_(size_t, i_buf_len);

    memset(p_buf, 0, i_memset_len);
}

long cv_memory_copy(
    void * p_dst,
    long i_dst_len,
    void const * p_src,
    long i_src_len)
{
    long i_copy_len;
    i_copy_len = i_src_len;
    if (i_copy_len > i_dst_len)
    {
        i_copy_len = i_dst_len;
    }
    if (i_copy_len > 0)
    {
        size_t const i_memcpy_len = cv_cast_(size_t, i_copy_len);
        memcpy(p_dst, p_src, i_memcpy_len);
    }
    else
    {
        i_copy_len = 0;
    }
    return i_copy_len;
}

long cv_memory_find0(
    void const * p_src,
    long i_src_len)
{
    long i_find_len;
    i_find_len = 0;
    if (p_src && i_src_len > 0)
    {
        void const * p_memchr_result;
        size_t const i_memchr_len = cv_cast_(size_t, i_src_len);
        p_memchr_result = memchr(p_src, '\000', i_memchr_len);
        if (p_memchr_result)
        {
            char const * const pc_min_char =
                cv_cast_(char const *, p_src);
            char const * const pc_max_char =
                cv_cast_(char const *, p_memchr_result);
            i_find_len = cv_cast_(long, pc_max_char - pc_min_char);
        }
    }
    return i_find_len;
}

