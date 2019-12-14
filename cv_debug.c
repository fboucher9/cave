/* See LICENSE for license details */

#include <cv_debug.h>

#if defined cv_debug_

#include <cv_runtime.h>

#include <cv_memory.h>

#include <cv_algo/cv_array.h>

#include <cv_algo/cv_array_tool.h>

#include <cv_misc/cv_cast.h>

#include <cv_misc/cv_limits.h>

#include <pthread.h>

static long g_init_count = 0;

static cv_debug_class g_debug_class_footer = cv_debug_class_initializer_;

static cv_debug_class * g_debug_class_list = &g_debug_class_footer;

static pthread_mutex_t g_debug_class_mutex = PTHREAD_MUTEX_INITIALIZER;

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

static unsigned char const a_colon[] = { ':' };

static unsigned char const a_newline[] = { '\n' };

/*
 *
 */

static void cv_debug_class_report_node(cv_debug_class const * p_iterator) {
    if (p_iterator->i_init_count) {
        int const i_stderr = cv_runtime_stderr_fileno();
        long const i_file_len = cv_memory_find_0(p_iterator->p_file,
            cv_signed_short_max_);
        cv_runtime_write(i_stderr, p_iterator->p_file,
            i_file_len);
        cv_runtime_write(i_stderr, a_colon,
            cv_sizeof_(a_colon));
        cv_runtime_print_ld(i_stderr, p_iterator->i_line);
        cv_runtime_write(i_stderr, a_colon,
            cv_sizeof_(a_colon));
        cv_runtime_print_ld(i_stderr, p_iterator->i_init_count);
        cv_runtime_write(i_stderr, a_newline,
            cv_sizeof_(a_newline));
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

void xx_debug_msg( cv_debug_code e_code, char const * p_file, int i_line) {
    if (e_code) {
        static unsigned char const a_prefix[] = {
            '*', '*', '*', ' ' };
        static unsigned char const a_suffix[] = {
            ' ', '*', '*', '*', '\n' };
        long const i_array_len = cv_array_len(e_code) & cv_signed_int_max_;
        int const i_stderr = cv_runtime_stderr_fileno();
        cv_runtime_write(i_stderr, a_prefix, cv_sizeof_(a_prefix));
        cv_runtime_write(i_stderr, p_file,
            cv_memory_find_0(p_file, cv_signed_short_max_));
        cv_runtime_write(i_stderr, a_colon, cv_sizeof_(a_colon));
        cv_runtime_print_ld(i_stderr, i_line);
        cv_runtime_write(i_stderr, a_colon, cv_sizeof_(a_colon));
        cv_runtime_write(i_stderr, e_code->o_min.pc_void, i_array_len);
        cv_runtime_write(i_stderr, a_suffix, cv_sizeof_(a_suffix));
    }
}

void xx_debug_assert( cv_bool b_expr, cv_debug_code e_code, char const * p_file,
    int i_line) {
    if (!b_expr) {
        xx_debug_break(e_code, p_file, i_line);
    }
}

void xx_debug_break( cv_debug_code e_code, char const * p_file, int i_line) {
    if (e_code) {
        xx_debug_msg(e_code, p_file, i_line);
        cv_runtime_exit(42);
    }
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
    pthread_mutex_lock(&g_debug_class_mutex);
    cv_runtime_memset(p_buf, 0xcc, i_buf_len);
    cv_debug_class_register(p_class, p_file, i_line);
    p_class->i_init_count ++;
    g_init_count ++;
    pthread_mutex_unlock(&g_debug_class_mutex);
}

/*
 *
 */

void xx_debug_cleanup( cv_debug_class * p_class,
    char const * p_file, int i_line,
    void * p_buf, long i_buf_len) {
    cv_debug_assert_(p_class && p_buf && i_buf_len, cv_debug_code_null_ptr);
    pthread_mutex_lock(&g_debug_class_mutex);
    cv_runtime_memset(p_buf, 0xcd, i_buf_len);
    cv_debug_class_register(p_class, p_file, i_line);
    p_class->i_init_count --;
    g_init_count --;
    pthread_mutex_unlock(&g_debug_class_mutex);
}

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
    cv_debug_class_report();
    cv_debug_assert_(0 == g_init_count, cv_debug_code_leak);
}

#endif /* #if defined cv_debug_ */
