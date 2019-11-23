/* See LICENSE for license details */

#include <cv_runtime.h>

#if defined cv_have_libc_
#include <stdarg.h>

#include <stdio.h>

#include <stdlib.h>
#endif /* #if defined cv_have_libc_ */

#include <cv_null.h>

#include <cv_unused.h>

void * cv_runtime_malloc(
    long const i_buffer_len)
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
    vprintf(p_format0, o_arg_list);
    va_end(o_arg_list);
#else /* #if defined cv_have_libc_ */
    cv_unused_(p_format0);
#endif /* #if defined cv_have_libc_ */
}

