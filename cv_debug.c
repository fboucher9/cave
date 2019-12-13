/* See LICENSE for license details */

#include <cv_debug.h>

#if defined cv_debug_

#include <cv_runtime.h>

#include <cv_memory.h>

#include <cv_algo/cv_array.h>

#include <cv_algo/cv_array_tool.h>

#include <cv_misc/cv_cast.h>

#include <cv_misc/cv_limits.h>

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

static void cv_runtime_print_ld(int fd, long i_signed) {
    static unsigned char const a_digit[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    if (0 == i_signed) {
        cv_runtime_write(fd, a_digit, 1);
    } else {
        unsigned long i_unsigned = 0;
        if (i_signed < 0) {
            static unsigned char const a_sign[] = { '-' };
            i_unsigned = cv_cast_(unsigned long, -i_signed);
            cv_runtime_write(fd, a_sign, cv_sizeof_(a_sign));
        } else {
            i_unsigned = cv_cast_(unsigned long, i_signed);
        }
        {
            unsigned long i_shift = 1000000000ul;
            while (i_shift) {
                if (i_unsigned >= i_shift) {
                    cv_runtime_write(fd, a_digit + ((i_unsigned/i_shift)%10ul), 1);
                }
                i_shift /= 10ul;
            }
        }
    }
}

void xx_debug_msg( cv_debug_code e_code, char const * p_file, int i_line) {
    if (e_code) {
        static unsigned char const a_prefix[] = {
            '*', '*', '*', ' ' };
        static unsigned char const a_colon[] = {
            ':' };
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

static long g_init_count = 0;

#if defined cv_debug_verbose_
static unsigned char const g_debug_init_text[] = {
    'c', 'v', '_', 'd', 'e', 'b', 'u', 'g', '_', 'i', 'n', 'i', 't' };
static unsigned char const g_debug_cleanup_text[] = {
    'c', 'v', '_', 'd', 'e', 'b', 'u', 'g', '_', 'c', 'l', 'e', 'a', 'n', 'u',
    'p' };
static cv_array const g_debug_init_array =
cv_array_text_initializer_(g_debug_init_text);
static cv_array const g_debug_cleanup_array =
cv_array_text_initializer_(g_debug_cleanup_text);

static void cv_debug_verbose_trace( cv_array const * p_name_0) {
    static unsigned char const a_middle[] = {
        ':', ' ' };
    static unsigned char const a_suffix[] = {
        '\n' };
    int i_stdout = cv_runtime_stdout_fileno();
    cv_runtime_write(i_stdout, p_name_0->o_min.pc_void,
        cv_array_len(p_name_0));
    cv_runtime_write(i_stdout, a_middle, cv_sizeof_(a_middle));
    cv_runtime_print_ld(i_stdout, g_init_count);
    cv_runtime_write(i_stdout, a_suffix, cv_sizeof_(a_suffix));
}
#endif /* #if defined cv_debug_verbose_ */

static cv_debug_class g_debug_class_footer = cv_debug_class_initializer_;

static cv_debug_class * g_debug_class_list = &g_debug_class_footer;

void xx_debug_init( void * p_buf, long i_buf_len) {
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
    cv_debug_verbose_trace(&g_debug_init_array);
#endif /* #if defined cv_debug_verbose_ */
}

void xx_debug_cleanup( void * p_buf, long i_buf_len) {
    g_init_count --;
#if defined cv_debug_verbose_
    cv_debug_verbose_trace(&g_debug_cleanup_array);
#endif
    if (p_buf && i_buf_len) {
        cv_runtime_memset(p_buf, 0xcd, i_buf_len);
    } else {
        /* Print report of class leaks */
        {
            cv_debug_class * p_iterator = g_debug_class_list;
            while (p_iterator && p_iterator != &g_debug_class_footer) {
                if (p_iterator->i_init_count) {
                    cv_runtime_printf("%s:%ld:%ld\n",
                        p_iterator->p_file,
                        p_iterator->i_line,
                        p_iterator->i_init_count);
                }
                p_iterator = p_iterator->p_next;
            }
        }
        cv_debug_assert_(0 == g_init_count, cv_debug_code_leak);
    }
}

static void xx_debug_class_register( cv_debug_class * p_class,
    char const * p_file, int i_line) {
    if (p_class->p_next) {
    } else {
        /* lock */
        p_class->p_file = p_file;
        p_class->i_line = i_line;
        p_class->p_next = g_debug_class_list;
        g_debug_class_list = p_class;
        /* unlock */
    }

}

void xx_debug_class_init( cv_debug_class * p_class,
    char const * p_file, int i_line) {
    xx_debug_class_register(p_class, p_file, i_line);
    p_class->i_init_count ++;
}

void xx_debug_class_cleanup( cv_debug_class * p_class,
    char const * p_file, int i_line) {
    xx_debug_class_register(p_class, p_file, i_line);
    p_class->i_init_count --;
}

#endif /* #if defined cv_debug_ */
