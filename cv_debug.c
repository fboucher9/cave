/* See LICENSE for license details */

#include <cv_debug.h>

#if defined cv_debug_

#include <cv_runtime.h>

#include <cv_memory.h>

#include <cv_algo/cv_array.h>

#include <cv_algo/cv_array_tool.h>

#include <cv_misc/cv_cast.h>

#include <cv_misc/cv_limits.h>

#include <cv_algo/cv_array_it.h>

#include <cv_algo/cv_array_print.h>

#include <cv_number_desc.h>

#include <cv_thread/cv_mutex_impl.h>

static long g_init_count = 0;

static cv_debug_class g_debug_class_footer = cv_debug_class_initializer_;

static cv_debug_class * g_debug_class_list = &g_debug_class_footer;

static cv_mutex g_debug_class_mutex = cv_mutex_initializer_;

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

static unsigned char const a_debug_code_leak[] = {
    'l', 'e', 'a', 'k'
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

static cv_array const g_debug_code_leak =
cv_array_text_initializer_(a_debug_code_leak);

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

cv_debug_code cv_debug_code_leak = &g_debug_code_leak;

void xx_debug_msg( cv_debug_code e_code, char const * p_file, int i_line) {
    static unsigned char const a_prefix[] = {
        '*', '*', '*', ' ' };
    static unsigned char const a_suffix[] = {
        ' ', '*', '*', '*' };
    unsigned char a_line[80u];
    cv_array_it o_array_it = cv_array_it_initializer_;
    cv_array_it_init_range(&o_array_it, a_line,
        a_line + sizeof(a_line));
    cv_array_print_range(&o_array_it, a_prefix,
        a_prefix + sizeof(a_prefix));
    cv_array_print_0(&o_array_it, p_file, cv_signed_short_max_);
    cv_array_print_char(&o_array_it, ':');
    cv_array_print_signed(&o_array_it, i_line,
        cv_number_format_dec());
    cv_array_print_char(&o_array_it, ':');
    cv_array_print(&o_array_it, e_code);
    cv_array_print_range(&o_array_it, a_suffix,
        a_suffix + sizeof(a_suffix));
    if (cv_array_print_nl(&o_array_it)) {
        int const i_stderr = cv_runtime_stderr_fileno();
        long const i_line_len = (o_array_it.o_array.o_min.pc_uchar -
            a_line) & cv_signed_long_max_;
        cv_runtime_write(i_stderr, a_line, i_line_len);
    }
    cv_array_it_cleanup(&o_array_it);
}

void xx_debug_assert( cv_bool b_expr, cv_debug_code e_code, char const * p_file,
    int i_line) {
    if (!b_expr) {
        xx_debug_break(e_code, p_file, i_line);
    }
}

void xx_debug_break( cv_debug_code e_code, char const * p_file, int i_line) {
    xx_debug_msg(e_code, p_file, i_line);
    cv_runtime_exit(42);
}

/*
 *
 */

static void cv_debug_class_register( cv_debug_class * p_class,
    char const * p_file, int i_line) {
    if (p_class->p_next) {
    } else {
        p_class->p_file = p_file;
        p_class->i_line = i_line;
        p_class->p_next = g_debug_class_list;
        g_debug_class_list = p_class;
    }
}

/*
 *
 */

void xx_debug_init( cv_debug_class * p_class,
    char const * p_file, int i_line,
    void * p_buf, long i_buf_len) {
    cv_debug_assert_(p_class && p_buf && i_buf_len, cv_debug_code_null_ptr);
    cv_mutex_impl_lock(&g_debug_class_mutex);
    cv_runtime_memset(p_buf, 0xcc, i_buf_len);
    cv_debug_class_register(p_class, p_file, i_line);
    p_class->i_init_count ++;
    g_init_count ++;
    cv_mutex_impl_unlock(&g_debug_class_mutex);
}

/*
 *
 */

void xx_debug_cleanup( cv_debug_class * p_class,
    char const * p_file, int i_line,
    void * p_buf, long i_buf_len) {
    cv_debug_assert_(p_class && p_buf && i_buf_len, cv_debug_code_null_ptr);
    cv_mutex_impl_lock(&g_debug_class_mutex);
    cv_runtime_memset(p_buf, 0xcd, i_buf_len);
    cv_debug_class_register(p_class, p_file, i_line);
    p_class->i_init_count --;
    g_init_count --;
    cv_mutex_impl_unlock(&g_debug_class_mutex);
}

/*
 *
 */

static void cv_debug_class_report_node(cv_debug_class const * p_iterator) {
    if (p_iterator->i_init_count) {
        unsigned char a_line[80];
        cv_array_it o_array_it = cv_array_it_initializer_;
        cv_array_it_init_range(&o_array_it, a_line,
            a_line + sizeof(a_line));
        cv_array_print_0(&o_array_it, p_iterator->p_file, cv_signed_short_max_);
        cv_array_print_char(&o_array_it, ':');
        cv_array_print_signed(&o_array_it, p_iterator->i_line,
            cv_number_format_dec());
        cv_array_print_char(&o_array_it, ':');
        cv_array_print_signed(&o_array_it, p_iterator->i_init_count,
            cv_number_format_dec());
        if (cv_array_print_nl(&o_array_it)) {
            int const i_stderr = cv_runtime_stderr_fileno();
            long const i_line_len = (o_array_it.o_array.o_min.pc_uchar -
                a_line) & cv_signed_long_max_;
            cv_runtime_write(i_stderr, a_line,
                i_line_len);
        }
        cv_array_it_cleanup(&o_array_it);
    }
}

/*
 *
 */

static void cv_debug_class_report(void) {
    cv_debug_class * p_iterator = g_debug_class_list;
    while (p_iterator && p_iterator != &g_debug_class_footer) {
        cv_debug_class_report_node(p_iterator);
        p_iterator = p_iterator->p_next;
    }
}

#endif /* #if defined cv_debug_ */

/*
 *
 */

void cv_debug_load(void) {
}

/*
 *
 */

void cv_debug_unload(void) {
    /* Print report of class leaks */
#if defined cv_debug_
    cv_debug_class_report();
#endif /* #if defined cv_debug_ */
    cv_debug_assert_(0 == g_init_count, cv_debug_code_leak);
}

/* end-of-file: cv_debug.c */
