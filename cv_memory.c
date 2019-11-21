/* See LICENSE for license details */

#include <cv_memory.h>

#include <cv_cast.h>

#include <cv_null.h>

#if defined cv_have_libc_
#include <string.h>
#endif /* #if defined cv_have_libc_ */

void cv_memory_zero(
    void * p_buf,
    long i_buf_len)
{
    if (p_buf && i_buf_len)
    {
#if defined cv_have_libc_
        size_t const i_memset_len = cv_cast_(size_t, i_buf_len);

        memset(p_buf, 0, i_memset_len);
#else /* #if defined cv_have_libc_ */
        char * p_buf_it = cv_cast_(char *, p_buf);
        char * const p_buf_end = p_buf_it + i_buf_len;
        while (p_buf_it < p_buf_end)
        {
            *p_buf_it = '\000';
            p_buf_it ++;
        }
#endif /* #if defined cv_have_libc_ */
    }
}

long cv_memory_copy(
    void * p_dst,
    long i_dst_len,
    void const * p_src,
    long i_src_len)
{
    long i_copy_len = i_src_len;
    if (i_copy_len > i_dst_len)
    {
        i_copy_len = i_dst_len;
    }
    if (i_copy_len > 0)
    {
#if defined cv_have_libc_
        size_t const i_memcpy_len = cv_cast_(size_t, i_copy_len);
        memcpy(p_dst, p_src, i_memcpy_len);
#else /* #if defined cv_have_libc_ */
        char * p_dst_it = cv_cast_(char *, p_dst);
        char const * p_src_it = cv_cast_(char const *, p_src);
        long i_remain = i_copy_len;
        while (i_remain > 0)
        {
            *p_dst_it = *p_src_it;
            p_dst_it ++;
            p_src_it ++;
            i_remain --;
        }
#endif /* #if defined cv_have_libc_ */
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
        void const * p_memchr_result = cv_null_;
#if defined cv_have_libc_
        size_t const i_memchr_len = cv_cast_(size_t, i_src_len);
        p_memchr_result = memchr(p_src, '\000', i_memchr_len);
#else /* #if defined cv_have_libc_ */
        char b_found = 0;
        char const * p_src_it = cv_cast_(char const *, p_src);
        char const * p_src_end = p_src_it + i_src_len;
        while (!b_found && (p_src_it < p_src_end))
        {
            if ('\000' == *p_src_it)
            {
                p_memchr_result = cv_cast_(void const *, p_src_it);
                b_found = 1;
            }
            else
            {
                p_src_it ++;
            }
        }
#endif /* #if defined cv_have_libc_ */
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

