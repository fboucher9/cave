/* See LICENSE for license details */

#include <cv_debug.h>

#if defined cv_debug_

#include <cv_runtime.h>

#include <cv_memory.h>

#include <cv_array_tool.h>

#include <cv_cast.h>

#if defined cv_debug_verbose_
#include <execinfo.h>
#endif /* #if defined cv_debug_verbose_ */

void xx_debug_msg(
    cv_debug_code e_code)
{
    cv_runtime_printf("*** ouch! %d ***\n",
        e_code);
}

void xx_debug_assert(
    cv_bool b_expr,
    cv_debug_code e_code)
{
    if (!b_expr) {
        xx_debug_break(e_code);
    }
}

void xx_debug_break(
    cv_debug_code e_code)
{
    cv_runtime_printf("*** assert! %d ***\n",
        e_code);
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

void xx_debug_init(
    void * p_buf,
    long i_buf_len)
{
    if (p_buf && i_buf_len) {
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

void xx_debug_cleanup(
    void * p_buf,
    long i_buf_len)
{
    g_init_count --;
#if defined cv_debug_verbose_
    cv_debug_verbose_trace("cv_debug_cleanup");
#endif
    if (p_buf && i_buf_len) {
        cv_runtime_memset(p_buf, 0xcd, i_buf_len);
    } else {
        cv_runtime_printf("*** %ld cleanup remain ***\n",
            g_init_count);
    }
}

#endif /* #if defined cv_debug_ */
