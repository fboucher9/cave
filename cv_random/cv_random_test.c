/* See LICENSE for license details */

/*
 *
 */

#include <cv_random/cv_random_test.h>
#include <cv_random/cv_random.h>
#include <cv_random/cv_random_crypto.h>
#include <cv_debug/cv_debug.h>
#include <cv_test_print.h>
#include <cv_number/cv_number_format.h>
#include <cv_algo/cv_array_tool.h>
#include <cv_options/cv_options_it.h>

/*
 *
 */

static void cv_random_test_step(
    unsigned long i_seed,
    unsigned long i_count,
    unsigned long i_modulo,
    unsigned long i_result) {
    unsigned long i_value = 0;
    struct cv_random o_random = cv_random_initializer_;
    cv_random_init(&o_random, i_seed);
    while (i_count) {
        i_value = cv_random_pick(&o_random, i_modulo);
        i_count --;
    }
    cv_random_cleanup(&o_random);
    cv_debug_assert_(i_value == i_result, cv_debug_code_error);
}

/*
 *
 */

static void cv_random_test_crypto_1(void) {
    struct cv_random_crypto o_crypto = cv_random_crypto_initializer_;
    if (cv_random_crypto_init(&o_crypto)) {
        unsigned long const i_value = cv_random_crypto_pick(&o_crypto, 0);
        cv_print_unsigned(i_value, cv_number_format_hex8());
        cv_print_nl();
        cv_random_crypto_cleanup(&o_crypto);
    }
}

/*
 *
 */

void cv_random_test(cv_options_it * p_options_it) {
    cv_array o_array = cv_array_null_;
    cv_array_init(&o_array);
    if (cv_options_it_next(p_options_it, &o_array)) {
        static unsigned char const s_crypto_text[] = {
            'c', 'r', 'y', 'p', 't', 'o' };
        static cv_array const s_crypto_array =
            cv_array_text_initializer_(s_crypto_text);
        if (cv_array_compare(&o_array, &s_crypto_array)) {
            cv_random_test_crypto_1();
        }
    } else {
        cv_random_test_step(12345UL, 10, 52, 49);
    }
    cv_array_cleanup(&o_array);
}

/* end-of-file: cv_random_test.c */
