/* See LICENSE for license details */

#include <cv_debug.h>

#if defined cv_debug_

#include <cv_runtime.h>

#include <cv_memory.h>

#include <cv_array_tool.h>

#if defined cv_debug_verbose_
#include <execinfo.h>
#endif /* #if defined cv_debug_verbose_ */

void cv_debug_msg(
    char const * p_msg0)
{
    cv_runtime_printf("*** ouch! %s ***\n",
        p_msg0);
}

void cv_debug_assert(
    cv_bool b_expr,
    char const * p_msg0)
{
    if (!b_expr)
    {
        cv_debug_break(p_msg0);
    }
}

void cv_debug_break(
    char const * p_msg0)
{
    cv_runtime_printf("*** assert! %s ***\n",
        p_msg0);
}

static long g_init_count = 0;

#if defined cv_debug_verbose_
static void cv_debug_verbose_trace(
    char const * p_name_0)
{
    cv_runtime_printf("%s: count=%ld\n",
        p_name_0,
        g_init_count);
    {
        void * a_stack[8u];
        backtrace(a_stack, 8);
        backtrace_symbols_fd(a_stack, 8, 1);
    }
    cv_runtime_printf("^^^^^^^^\n");
}
#endif /* #if defined cv_debug_verbose_ */

void cv_debug_init(
    void * p_buf,
    long i_buf_len)
{
    if (p_buf && i_buf_len)
    {
        cv_array o_array = cv_array_null_;
        o_array.o_min.p_void = p_buf;
        o_array.o_max.p_char = o_array.o_min.p_char + i_buf_len;
        cv_array_fill(
            &o_array,
            0xcc);
    }
    g_init_count ++;
#if defined cv_debug_verbose_
    cv_debug_verbose_trace("cv_debug_init");
#endif /* #if defined cv_debug_verbose_ */
}

void cv_debug_cleanup(
    void * p_buf,
    long i_buf_len)
{
    g_init_count --;
#if defined cv_debug_verbose_
    cv_debug_verbose_trace("cv_debug_cleanup");
#endif
    if (p_buf && i_buf_len)
    {
        cv_array o_array = cv_array_null_;
        o_array.o_min.p_void = p_buf;
        o_array.o_max.p_char = o_array.o_min.p_char + i_buf_len;
        cv_array_fill(
            &o_array,
            0xcd);
    }
    else
    {
        cv_runtime_printf("*** %ld cleanup remain ***\n",
            g_init_count);
    }
}

#endif /* #if defined cv_debug_ */
