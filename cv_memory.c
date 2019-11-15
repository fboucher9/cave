/* See LICENSE for license details */

#include <cv_memory.h>

#include <string.h>

void cv_memory_zero(
    void * p_buf,
    long i_buf_len)
{
    memset(p_buf, 0, (size_t)i_buf_len);
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
        memcpy(p_dst, p_src, (size_t)i_copy_len);
    }
    else
    {
        i_copy_len = 0;
    }
    return i_copy_len;
}

