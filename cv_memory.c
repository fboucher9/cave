/* See LICENSE for license details */

#include <cv_memory.h>

#include <cv_cast.h>

#include <cv_null.h>

#include <cv_bool.h>

#include <cv_array.h>

#include <cv_runtime.h>

void cv_memory_zero(
    void * p_buf,
    long i_buf_len)
{
    if (p_buf && i_buf_len)
    {
        cv_runtime_memset(p_buf, 0, i_buf_len);
    }
}

long cv_memory_copy(
    void * p_dst,
    long i_dst_len,
    void const * p_src,
    long i_src_len)
{
    long i_copy_len =
        (i_src_len < i_dst_len)
        ? i_src_len
        : i_dst_len;
    if (i_copy_len > 0)
    {
        cv_runtime_memcpy(p_dst, p_src, i_copy_len);
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
    long i_find_len = 0;
    if (p_src && i_src_len > 0)
    {
        cv_array o_array = cv_array_initializer_;
        o_array.o_min.pc_void = p_src;
        o_array.o_max.pc_void = cv_runtime_memchr(p_src, '\000', i_src_len);
        if (o_array.o_max.pc_void)
        {
            i_find_len = cv_array_char_count(&o_array);
        }
    }
    return i_find_len;
}

