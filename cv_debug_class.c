/* See LICENSE for license details */

/*
 *
 */

#include <cv_debug_class.h>
#include <cv_debug_plugin.h>

#if defined cv_debug_

#include <cv_file/cv_file_std.h>
#include <cv_file/cv_file_print.h>
#include <cv_thread/cv_mutex_impl.h>
#include <cv_runtime.h>
#include <cv_misc/cv_limits.h>
#include <cv_number_desc.h>

static long g_debug_class_count = 0;

static cv_debug_class g_debug_class_footer = cv_debug_class_initializer_;

static cv_debug_class * g_debug_class_list = &g_debug_class_footer;

static cv_mutex g_debug_class_mutex = cv_mutex_initializer_;

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

void xx_debug_class_construct( cv_debug_class * p_class,
    char const * p_file, int i_line,
    void * p_buf, long i_buf_len) {
    cv_mutex_impl_lock(&g_debug_class_mutex);
    cv_runtime_memset(p_buf, 0xcc, i_buf_len);
    cv_debug_class_register(p_class, p_file, i_line);
    p_class->i_init_count ++;
    g_debug_class_count ++;
    cv_mutex_impl_unlock(&g_debug_class_mutex);
}

/*
 *
 */

void xx_debug_class_destruct( cv_debug_class * p_class,
    char const * p_file, int i_line,
    void * p_buf, long i_buf_len) {
    cv_mutex_impl_lock(&g_debug_class_mutex);
    cv_runtime_memset(p_buf, 0xcd, i_buf_len);
    cv_debug_class_register(p_class, p_file, i_line);
    p_class->i_init_count --;
    g_debug_class_count --;
    cv_mutex_impl_unlock(&g_debug_class_mutex);
}

/*
 *
 */

static void cv_debug_class_report_node(cv_debug_class const * p_iterator) {
    if (p_iterator->i_init_count) {
        cv_file const * p_stderr = cv_file_std_err();
        cv_file_print_0(p_stderr, p_iterator->p_file, cv_signed_short_max_);
        cv_file_print_char(p_stderr, ':');
        cv_file_print_signed(p_stderr, p_iterator->i_line,
            cv_number_format_dec());
        cv_file_print_char(p_stderr, ':');
        cv_file_print_signed(p_stderr, p_iterator->i_init_count,
            cv_number_format_dec());
        cv_file_print_nl(p_stderr);
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
    if (0 != g_debug_class_count)
    {
        cv_runtime_exit(43);
    }
#endif /* #if defined cv_debug_ */
}

/* end-of-file: cv_debug_class.c */
