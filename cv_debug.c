/* See LICENSE for license details */

#include <cv_debug.h>

#if defined cv_debug_

#include <cv_runtime.h>

#include <cv_memory.h>

#include <cv_array.h>

#include <cv_array_tool.h>

#include <cv_cast.h>

#if defined cv_debug_verbose_
#include <execinfo.h>
#endif /* #if defined cv_debug_verbose_ */

static unsigned char const a_debug_code_null_ptr[] = {
    'n', 'u', 'l', 'l', ' ', 'p', 't', 'r' };

static unsigned char const a_debug_code_error[] = {
    'e', 'r', 'r', 'o', 'r' };

static unsigned char const a_debug_code_already_loaded[] = {
    'a', 'l', 'r', 'e', 'a', 'd', 'y', ' ',
    'l', 'o', 'a', 'd', 'e', 'd' };

static unsigned char const a_debug_code_already_unloaded[] = {
    'a', 'l', 'r', 'e', 'a', 'd', 'y', ' ',
    'u', 'n', 'l', 'o', 'a', 'd', 'e', 'd' };

static unsigned char const a_debug_code_not_loaded[] = {
    'n', 'o', 't', ' ',
    'l', 'o', 'a', 'd', 'e', 'd' };

static unsigned char const a_debug_code_invalid_length[] = {
    'i', 'n', 'v', 'a', 'l', 'i', 'd', ' ',
    'l', 'e', 'n', 'g', 't', 'h' };

static unsigned char const a_debug_code_alternative[] = {
    'a', 'l', 't', 'e', 'r', 'n', 'a', 't', 'i', 'v', 'e' };

static unsigned char const a_debug_code_out_of_memory[] = {
    'o', 'u', 't', ' ', 'o', 'f', ' ', 'm', 'e', 'm', 'o', 'r', 'y' };

static unsigned char const a_debug_code_not_empty[] = {
    'n', 'o', 't', ' ',
    'e', 'm', 'p', 't', 'y' };

static unsigned char const a_debug_code_not_implemented[] = {
    'n', 'o', 't', ' ',
    'i', 'm', 'p', 'l', 'e', 'm', 'e', 'n', 't', 'e', 'd' };

static unsigned char const a_debug_code_invalid_parameter[] = {
    'i', 'n', 'v', 'a', 'l', 'i', 'd', ' ',
    'p', 'a', 'r', 'a', 'm', 'e', 't', 'e', 'r'
};

static unsigned char const a_debug_code_dont_panic[] = {
    'd', 'o', 'n', 't', ' ', 'p', 'a', 'n', 'i', 'c'
};

static cv_array const g_debug_code_null_ptr =
cv_array_text_initializer_(a_debug_code_null_ptr);

static cv_array const g_debug_code_error =
cv_array_text_initializer_(a_debug_code_error);

static cv_array const g_debug_code_already_loaded =
cv_array_text_initializer_(a_debug_code_already_loaded);

static cv_array const g_debug_code_already_unloaded =
cv_array_text_initializer_(a_debug_code_already_unloaded);

static cv_array const g_debug_code_not_loaded =
cv_array_text_initializer_(a_debug_code_not_loaded);

static cv_array const g_debug_code_invalid_length =
cv_array_text_initializer_(a_debug_code_invalid_length);

static cv_array const g_debug_code_alternative =
cv_array_text_initializer_(a_debug_code_alternative);

static cv_array const g_debug_code_out_of_memory =
cv_array_text_initializer_(a_debug_code_out_of_memory);

static cv_array const g_debug_code_not_empty =
cv_array_text_initializer_(a_debug_code_not_empty);

static cv_array const g_debug_code_not_implemented =
cv_array_text_initializer_(a_debug_code_not_implemented);

static cv_array const g_debug_code_invalid_parameter =
cv_array_text_initializer_(a_debug_code_invalid_parameter);

static cv_array const g_debug_code_dont_panic =
cv_array_text_initializer_(a_debug_code_dont_panic);

cv_debug_code cv_debug_code_null_ptr = &g_debug_code_null_ptr;

cv_debug_code cv_debug_code_error = &g_debug_code_error;

cv_debug_code cv_debug_code_already_loaded = &g_debug_code_already_loaded;

cv_debug_code cv_debug_code_already_unloaded = &g_debug_code_already_unloaded;

cv_debug_code cv_debug_code_not_loaded = &g_debug_code_not_loaded;

cv_debug_code cv_debug_code_invalid_length = &g_debug_code_invalid_length;

cv_debug_code cv_debug_code_alternative = &g_debug_code_alternative;

cv_debug_code cv_debug_code_out_of_memory = &g_debug_code_out_of_memory;

cv_debug_code cv_debug_code_not_empty = &g_debug_code_not_empty;

cv_debug_code cv_debug_code_not_implemented = &g_debug_code_not_implemented;

cv_debug_code cv_debug_code_invalid_parameter = &g_debug_code_invalid_parameter;

cv_debug_code cv_debug_code_dont_panic = &g_debug_code_dont_panic;

void xx_debug_msg(
    cv_debug_code e_code,
    char const * p_file,
    int i_line)
{
    cv_runtime_printf("*** ouch! %s (%s:%d) ***\n",
        e_code->o_min.pc_char,
        p_file,
        i_line);
}

void xx_debug_assert(
    cv_bool b_expr,
    cv_debug_code e_code,
    char const * p_file,
    int i_line)
{
    if (!b_expr) {
        xx_debug_break(e_code, p_file, i_line);
    }
}

void xx_debug_break(
    cv_debug_code e_code,
    char const * p_file,
    int i_line)
{
    cv_runtime_printf("*** assert! %s (%s:%d) ***\n",
        e_code->o_min.pc_char,
        p_file,
        i_line);
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
