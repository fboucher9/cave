/* See LICENSE for license details */

#include <cv_runtime.h>

#if defined cv_have_libc_
#include <stdarg.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>
#endif /* #if defined cv_have_libc_ */

#include <cv_bool.h>

#include <cv_null.h>

#include <cv_unused.h>

void * cv_runtime_malloc(
    long i_buffer_len)
{
    void * p_buffer = cv_null_;
#if defined cv_have_libc_
    size_t const i_malloc_len = cv_cast_(size_t, i_buffer_len);
    p_buffer = malloc(i_malloc_len);
#else /* #if defined cv_have_libc_ */
    cv_unused_(i_buffer_len);
#endif /* #if defined cv_have_libc_ */
    return p_buffer;
}

void cv_runtime_free(
    void * p_buffer)
{
#if defined cv_have_libc_
    free(p_buffer);
#else /* #if defined cv_have_libc_ */
    cv_unused_(p_buffer);
#endif /* #if defined cv_have_libc_ */
}

void cv_runtime_printf(
    char const * p_format0,
    ...)
{
#if defined cv_have_libc_
    va_list o_arg_list;
    va_start(o_arg_list, p_format0);
    vfprintf(stdout, p_format0, o_arg_list);
    fflush(stdout);
    va_end(o_arg_list);
#else /* #if defined cv_have_libc_ */
    cv_unused_(p_format0);
#endif /* #if defined cv_have_libc_ */
}

void cv_runtime_memset(
    void * p_buf,
    unsigned char c_value,
    long i_buf_len)
{
#if defined cv_have_libc_
    size_t const i_memset_len = cv_cast_(size_t, i_buf_len);
    memset(p_buf, c_value, i_memset_len);
#else /* #if defined cv_have_libc_ */
    unsigned char * p_buf_it = cv_cast_(unsigned char *, p_buf);
    unsigned char * const p_buf_end = p_buf_it + i_buf_len;
    while (p_buf_it < p_buf_end)
    {
        *p_buf_it = c_value;
        p_buf_it ++;
    }
#endif /* #if defined cv_have_libc_ */
}

void cv_runtime_memcpy(
    void * p_dst,
    void const * p_src,
    long i_copy_len)
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

void const * cv_runtime_memchr(
    void const * p_src,
    unsigned char c_value,
    long i_src_len)
{
    void const * p_memchr_result;
#if defined cv_have_libc_
    size_t const i_memchr_len = cv_cast_(size_t, i_src_len);
    p_memchr_result = memchr(p_src, c_value, i_memchr_len);
#else /* #if defined cv_have_libc_ */
    cv_bool b_found = cv_false;
    unsigned char const * p_src_it = cv_cast_(unsigned char const *, p_src);
    unsigned char const * p_src_end = p_src_it + i_src_len;
    while (!b_found && (p_src_it < p_src_end))
    {
        if (c_value == *p_src_it)
        {
            p_memchr_result = cv_cast_(void const *, p_src_it);
            b_found = cv_true;
        }
        else
        {
            p_src_it ++;
        }
    }
#endif /* #if defined cv_have_libc_ */
    return p_memchr_result;
}

int cv_runtime_memcmp(
    void const * p_left,
    void const * p_right,
    long i_len)
{
    int i_memcmp_result = -1;
#if defined cv_have_libc_
    size_t const i_memcmp_len = cv_cast_(size_t, i_len);
    i_memcmp_result = memcmp(p_left, p_right, i_memcmp_len);
#else /* #if defined cv_have_libc_ */
    cv_unused_(p_left);
    cv_unused_(p_right);
    cv_unused_(i_len);
#endif /* #if defined cv_have_libc_ */
    return i_memcmp_result;
}

/* end-of-file: cv_runtime.c */
